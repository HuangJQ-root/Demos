/*
 * Copyright (c) 2025 Li Auto Inc. and its affiliates
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <mvbs/sections/start_sec_code.h>
#include <mvbs/sections/start_sec_bss.h>
#include <mvbs/sections/start_sec_const.h>
#include <mvbs/sections/start_sec_data.h>

#include <core/core.h>
#include <mvbs/utils/log.h>
#include <mvbs/rtps/message.h>

/* This interface isn't used now, and it will be TBD. */
void ep_attr_init(endpoint_attr_t *ep_attr, const char *topic)
{
	if (ep_attr == NULL) {
		pr_err(ERR_INVALID, "Invaild parameter.\n");
		return;
	}

	if (topic == NULL) {
		ep_attr->topic_name[0]		= '\0';
	} else {
		mvbs_strncmp(ep_attr->topic_name, topic, MAX_TOPICNAME_LENGTH);
	}

	ep_attr->type				= NULL;

	ep_attr->qos.reliability_kind		= (uint16_t)BEST_EFFORT;
	ep_attr->reliability.max_blocking_time.seconds = 0;
	ep_attr->reliability.max_blocking_time.nanosec = 0U;

	ep_attr->qos.durability_kind		= (uint16_t)TRANSIENT_LOCAL;
	ep_attr->qos.history_kind		= (uint16_t)KEEP_LAST;
	ep_attr->history.depth			= 5U;
	ep_attr->resource_limit.max_samples	= 5U;
	ep_attr->resource_limit.max_instances	= 1U;
	ep_attr->resource_limit.max_samples_per_instance = 5U;
	ep_attr->lifespan.duration		= RTPS_TIME_INFINITE;
	ep_attr->deadline.duration		= RTPS_TIME_INFINITE;
	ep_attr->qos.ownership_kind		= (uint16_t)SHARED;
	ep_attr->ownership_strength.value	= 0U;
	ep_attr->qos.liveliness_kind		= (uint16_t)QOS_LIVE_AUTOMATIC;
	ep_attr->liveliness.lease_duration	= RTPS_TIME_INFINITE;
	ep_attr->liveliness.announcement_period = RTPS_TIME_INFINITE;
	ep_attr->locator_selector		= 0U;
	ep_attr->backup_enabled			= false;
	ep_attr->crc16_enabled			= false;
}

bool sedp_edp_deserialize(struct mvbs_cdr *cdr, struct endpoint_info *pin,
						struct participant *ptcp)
{
	uint32_t qos_kind = 0;
	uint16_t pid = 0;
	uint16_t length = 0;
	uint32_t topic_name_len;
	uint32_t type_name_len;

	uint32_t crc16_len;

	uint8_t uc_count = 0;

	uint32_t e2e_protection = 0;
	bool end_deser_success = false;

	if ((pin == NULL) || (cdr == NULL) || (ptcp == NULL)) {
		pr_err(ERR_INVALID, "Invaild parameter.\n");
		return false;
	}

	locator_set_invalid(&(pin->uc));
	locator_set_invalid(&(pin->mc));

	while (mcdr_buffer_remaining(cdr) >= 4U) {
		(void)mcdr_deserialize_uint16_t(cdr, &pid);
		(void)mcdr_deserialize_uint16_t(cdr, &length);

		if (mcdr_buffer_remaining(cdr) < length) {
			pr_err(ERR_INVALID, "Data length in cdr is invalid.\n");

			return false;
		}

		switch (pid) {
		case PID_ENDPOINT_GUID:
			cdr_deserialize_guid(cdr, &pin->ep_guid);
			break;

		case PID_RELIABILITY:
			(void)mcdr_deserialize_uint32_t(cdr, &qos_kind);
			pin->qos.reliability_kind = (uint16_t)qos_kind;
			cdr_deserialize_duration(cdr, NULL);
			/* TODO Skip 8 bytes. don't know what they are yet */
			break;

		case PID_DURABILITY:
			(void)mcdr_deserialize_uint32_t(cdr, &qos_kind);
			pin->qos.durability_kind = (uint16_t)qos_kind;
			break;

		case PID_DEADLINE:
			cdr_deserialize_duration(cdr, &pin->deadline.duration);
			break;

		case PID_OWNERSHIP:
			(void)mcdr_deserialize_uint32_t(cdr, &qos_kind);
			pin->qos.ownership_kind = (uint16_t)qos_kind;
			break;

		case PID_OWNERSHIP_STRENGTH:
			pin->ownership_strength = cdr_deserialize_uint32_t(cdr);
			break;

		case PID_LIVELINESS:
			(void)mcdr_deserialize_uint32_t(cdr, &qos_kind);
			pin->qos.liveliness_kind = (uint16_t)qos_kind;

			cdr_deserialize_duration(cdr, &pin->liveliness.lease_duration);
			break;

		case PID_TOPIC_NAME:
			topic_name_len = cdr_deserialize_uint32_t(cdr);
			if (topic_name_len > MAX_TOPICNAME_LENGTH) {
				pr_warn("the topic name is too long in edp\n");
				return false;
			}

			(void)mcdr_deserialize_array_char(cdr, pin->topic_name,
								topic_name_len);
			break;

		case PID_TYPE_NAME:
			type_name_len = cdr_deserialize_uint32_t(cdr);
			if (type_name_len > MAX_TYPENAME_LENGTH) {
				pr_warn("the type name is too long in edp\n");
				return false;
			}

			(void)mcdr_deserialize_array_char(cdr, pin->type_name,
								type_name_len);
			break;

		case PID_UNICAST_LOCATOR:
			if (cdr_deserialize_locator(cdr, &pin->uc) != 0) {
				pr_err(ERR_MCDR, "Fail to deserialize unicastLocator.\n");
				return false;
			}

			if (ptcp_detect_reachable(ptcp, &pin->uc) < 0) {
				pin->uc.kind = (uint16_t)LOCATOR_KIND_INVALID;

				break;
			}

			uc_count++;
			break;

		case PID_MULTICAST_LOCATOR:
			if (cdr_deserialize_locator(cdr, &pin->mc) != 0) {
				pr_err(ERR_MCDR, "Fail to deserialize multicastLocator.\n");
				return false;
			}

			if (ptcp_detect_reachable(ptcp, &pin->mc) < 0) {
				pin->mc.kind = (uint16_t)LOCATOR_KIND_INVALID;

				break;
			}

			break;

		case PID_STATUS_INFO:
			if (length != 4U) {
				/* Ignore Status Info */
				(void)mcdr_deserialize_array_uint8_t(cdr, NULL, length);
				break;
			}

			(void)mcdr_deserialize_uint32_t(cdr, &pin->status_info);
			break;

			/* only use case so far is deleting remote endpoints */
		case PID_KEY_HASH:
			if (length != 16U) {
				/* Ignore value */
				(void)mcdr_deserialize_array_uint8_t(cdr, NULL, length);
				break;
			}

			cdr_deserialize_guid(cdr, &pin->guid_from_key_hash);
			break;

		case PID_CRC16_IDL:
			(void)mcdr_deserialize_uint32_t(cdr, &crc16_len);
			if (crc16_len > MAX_CRC16_LENGTH) {
				pr_warn("Fail to deserialize crc16 for it's too long.\n");
				return false;
			}
			(void)mcdr_deserialize_array_char(cdr, pin->crc16,
								crc16_len);
			break;

		case PID_E2E_PROTECTION:
			pin->e2e.e2e_protection = false;

			(void)mcdr_deserialize_uint32_t(cdr, &e2e_protection);
			if (e2e_protection != 0U) {
				pin->e2e.e2e_protection = true;
			}

			break;

		case PID_AGENT_ENDPOINT:
			(void)mcdr_deserialize_uint32_t(cdr, &pin->agent_flag);
			break;

		case PID_SENTINEL:
			/* use participant_proxy->dfl_uc_loca directly */
			if (uc_count == 1U) {
				pin->backup_enabled = false;
			} else {
				pin->backup_enabled = true;
			}

			end_deser_success = true;
			break;

		default:
			(void)mcdr_deserialize_array_uint8_t(cdr, NULL, length);
			break;
		}

		if (end_deser_success) {
			return true;
		}

		mcdr_align_to_uint32(cdr);
		/* 4 Byte alignment per element */
	}

	return false;
}

bool reader_match_ep_info(struct reader *r, const endpoint_info_t *info)
{
	if ((r == NULL) || (info == NULL)) {
		pr_err(ERR_INVALID, "Invaild parameter.\n");
		return false;
	}

	const endpoint_attr_t *rattr = &r->attr->ep_attr;

	if (mvbs_strcmp(info->topic_name, rattr->topic_name) != 0) {
		pr_debug("writer topic name:%s != reader topic name %s.\n",
					string_or_null(info->topic_name),
					string_or_null(rattr->topic_name));
		return false;
	}

	if (mvbs_strcmp(info->type_name, rattr->type->name) != 0) {
		pr_debug("writer type name:%s != reader type name %s.\n",
					string_or_null(info->type_name),
					string_or_null(rattr->type->name));
		return false;
	}

	if (info->agent_flag != rattr->agent_flag) {
		pr_debug("INCOMPATIBLE agent_flag for topic %s!\n",
			string_or_null(info->topic_name));
		return false;
	}

	if (info->qos.reliability_kind < rattr->qos.reliability_kind) {
		pr_info("INCOMPATIBLE Reliability QoS for topic %s!\n",
					string_or_null(info->topic_name));
		return false;
	}

	if (info->qos.durability_kind < rattr->qos.durability_kind) {
		pr_info("INCOMPATIBLE Durability QoS for topic %s!\n",
					string_or_null(info->topic_name));
		return false;
	}

        /* Invalid: Writer Deadline > Reader Deadline */
	if (duration_compare(&(info->deadline.duration),
				   &(rattr->deadline.duration)) == 1) {
		pr_info("INCOMPATIBLE Deadline QoS for topic %s!\n",
					string_or_null(info->topic_name));
		return false;
	}

	if (info->qos.ownership_kind != rattr->qos.ownership_kind) {
		pr_info("INCOMPATIBLE Ownership kind QoS for topic %s!\n",
					string_or_null(info->topic_name));
		return false;
	}

	if (info->qos.liveliness_kind < rattr->qos.liveliness_kind) {
		pr_info("INCOMPATIBLE Liveliness kind QoS for topic %s!\n",
					string_or_null(info->topic_name));
		return false;
	}

	if (duration_compare(&(info->liveliness.lease_duration),
				   &(rattr->liveliness.lease_duration)) == 1) {
		pr_info("INCOMPATIBLE Liveliness lease_duration for topic %s!\n",
					string_or_null(info->topic_name));
		return false;
	}

	if (mvbs_strcmp(info->crc16, rattr->type->crc16) != 0) {
		pr_info("Fail to IDL File crc16 checking for topic %s!\n",
					string_or_null(info->topic_name));
	}

	if (info->e2e.e2e_protection != rattr->e2e.e2e_protection) {
		pr_info("INCOMPATIBLE e2e config for topic %s!\n",
					string_or_null(info->topic_name));
		return false;
	}

	return true;
}

bool writer_match_ep_info(struct writer *w, const endpoint_info_t *info)
{
	if ((w == NULL) || (info == NULL)) {
		pr_err(ERR_INVALID, "Invaild parameter.\n");
		return false;
	}

	const endpoint_attr_t *wattr = &w->attr->ep_attr;

	if (mvbs_strcmp(info->topic_name, wattr->topic_name) != 0) {
		pr_debug("writer topic name:%s != reader topic name %s.\n",
					string_or_null(wattr->topic_name),
					string_or_null(info->topic_name));
		return false;
	}

	if (mvbs_strcmp(info->type_name, wattr->type->name) != 0) {
		pr_debug("writer type name:%s != reader type name %s.\n",
					string_or_null(wattr->type->name),
					string_or_null(info->type_name));
		return false;
	}

	if (info->agent_flag != wattr->agent_flag) {
		pr_debug("INCOMPATIBLE agent_flag for topic %s!\n",
			string_or_null(info->topic_name));
		return false;
	}

	if (info->qos.reliability_kind > wattr->qos.reliability_kind) {
		pr_info("INCOMPATIBLE Reliability QoS for topic %s!\n",
					string_or_null(info->topic_name));
		return false;
	}

	if (info->qos.durability_kind > wattr->qos.durability_kind) {
		pr_info("INCOMPATIBLE Durability QoS for topic %s!\n",
					string_or_null(info->topic_name));
		return false;
	}

        /* Invalid: Writer Deadline > Reader Deadline */
	if (duration_compare(&(wattr->deadline.duration),
                                &(info->deadline.duration)) == 1) {
		pr_info("INCOMPATIBLE Deadline QoS for topic %s!\n",
					string_or_null(info->topic_name));
		return false;
	}

	if (info->qos.ownership_kind != wattr->qos.ownership_kind) {
		pr_info("INCOMPATIBLE Ownership kind QoS for topic %s!\n",
					string_or_null(info->topic_name));
		return false;
	}

	if (info->qos.liveliness_kind > wattr->qos.liveliness_kind) {
		pr_info("INCOMPATIBLE Liveliness kind QoS for topic %s!\n",
					string_or_null(info->topic_name));
		return false;
	}

	if (duration_compare(&(wattr->liveliness.lease_duration),
				   &(info->liveliness.lease_duration)) == 1) {
		pr_info("INCOMPATIBLE Liveliness lease_duration for topic %s!\n",
					string_or_null(info->topic_name));
		return false;
	}

	if (mvbs_strcmp(info->crc16, wattr->type->crc16) != 0) {
		pr_verb("Fail to IDL File crc16 checking for topic %s!\n",
					string_or_null(info->topic_name));
	}

	if (info->e2e.e2e_protection != wattr->e2e.e2e_protection) {
		pr_info("INCOMPATIBLE e2e config for topic %s!\n",
					string_or_null(info->topic_name));
		return false;
	}

	return true;
}

/*
 */
bool ep_attr_match(const endpoint_attr_t *wr_ep, const endpoint_attr_t *rd_ep)
{
	if ((wr_ep == NULL) || (rd_ep == NULL)) {
		pr_err(ERR_INVALID, "Invaild parameter.\n");
		return false;
	}

	if (mvbs_strcmp(wr_ep->topic_name, rd_ep->topic_name) != 0) {
		pr_debug("writer topic name:%s != reader type name %s.\n",
			 string_or_null(wr_ep->topic_name),
			 string_or_null(rd_ep->topic_name));
		return false;
	}

	if (mvbs_strcmp(wr_ep->type->name, rd_ep->type->name) != 0) {
		pr_debug("writer type name:%s != reader type name %s.\n",
			 string_or_null(wr_ep->type->name),
			 string_or_null(rd_ep->type->name));
		return false;
	}

	if (wr_ep->agent_flag != rd_ep->agent_flag) {
		pr_debug("INCOMPATIBLE agent_flag for topic %s!\n",
			string_or_null(wr_ep->topic_name));
		return false;
	}

	if (wr_ep->qos.reliability_kind < rd_ep->qos.reliability_kind) {
		pr_info("INCOMPATIBLE Reliability QoS for topic %s!\n",
			string_or_null(wr_ep->topic_name));
		return false;
	}

	if (wr_ep->qos.durability_kind < rd_ep->qos.durability_kind) {
		pr_info("INCOMPATIBLE Durability QoS for topic %s!\n",
			string_or_null(wr_ep->topic_name));
		return false;
	}

	if (duration_compare(&(wr_ep->deadline.duration),
				   &(rd_ep->deadline.duration)) == 1) {
		pr_info("INCOMPATIBLE Deadline QoS for topic %s!\n",
			string_or_null(wr_ep->topic_name));
		return false;
	}

	if (wr_ep->qos.ownership_kind != rd_ep->qos.ownership_kind) {
		pr_info("INCOMPATIBLE Ownership kind QoS for topic %s!\n",
			string_or_null(wr_ep->topic_name));
		return false;
	}

	if (wr_ep->qos.liveliness_kind < rd_ep->qos.liveliness_kind) {
		pr_info("INCOMPATIBLE Liveliness kind QoS for topic %s!\n",
			string_or_null(wr_ep->topic_name));
		return false;
	}

	if (duration_compare(&(wr_ep->liveliness.lease_duration),
				   &(rd_ep->liveliness.lease_duration)) == 1) {
		pr_info("INCOMPATIBLE Liveliness lease_duration for topic %s!\n",
			string_or_null(wr_ep->topic_name));
		return false;
	}

	if (mvbs_strcmp(wr_ep->type->crc16, rd_ep->type->crc16) != 0) {
		pr_verb("IDL File crc16 check fail for topic %s!\n",
			string_or_null(wr_ep->topic_name));
	}

	if (wr_ep->e2e.e2e_protection != rd_ep->e2e.e2e_protection) {
		pr_info("INCOMPATIBLE e2e config for topic %s!\n",
			string_or_null(wr_ep->topic_name));
		return false;
	}

	return true;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
