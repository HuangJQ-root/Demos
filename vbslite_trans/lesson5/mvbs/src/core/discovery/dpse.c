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

#include <stdlib.h>	/* FIXME: atoi */
#include <core/core.h>
#include <mvbs/errno.h>
#include <mvbs/utils/log.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/timer.h>
#include <mcdr/mcdr.h>
#include <discovery/dpse.h>
#include <discovery/sddp.h>

struct edp_static_property {
	char			m_endpoint_type[32];	/* Endpoint type */
	char			m_status[32];		/* Status */
	char			m_userid_str[64];	/* User ID as string */
	uint16_t		m_user_id;		/* User ID */
	struct rtps_entity_id	m_entity_id;		/* Entity ID */
};

static void static_new_remote_writer(struct reader *r, participant_t *ptcp,
                                     struct participant_proxy *ptcp_proxy,
				     struct rtps_entity_id writer_eid,
                                     int16_t userId)
{
	const endpoint_attr_t	*wattr;
	struct writer_proxy	*wproxy;

	/* The proxy object with this eid already exist. */
	if (reader_get_proxy(r, ptcp_proxy, writer_eid) != NULL) {
		return;
	}

	wattr = ptcp_find_static_remote_writer(ptcp, userId);
	if (wattr == NULL) {
		return;
	}

	if (mvbs_strcmp(r->attr->ep_attr.topic_name, wattr->topic_name) != 0) {
		return;
	}

	if (!ep_attr_match(wattr, &r->attr->ep_attr)) {
		return;
	}

	pr_debug("reader [%s] get a new writer with " ENTITY_ID_FMT "from %s",
			reader_get_topicname(r), ENTITY_ID_PARTS(writer_eid),
			ptcp_proxy->ptcp_name);

	wproxy = writer_proxy_alloc(r);
	if (wproxy == NULL) {
		pr_warn("mem pool has full");
		return;
	}

	writer_proxy_init(wproxy, ptcp_proxy, writer_eid,
			  wattr->ownership_strength.value);

	if (!reader_add_proxy(r, wproxy)) {
		writer_proxy_free(wproxy);

		pr_warn("Fail to add new match writer");

		return ;
	};

	pr_debug("%s -> Add new proxy from %s", reader_get_topicname(r),
					wproxy->ptcp_proxy->ptcp_name);

	reader_ownership_update(r, wproxy, true);

	reader_on_subscription_matched(r, true);
}

static void static_new_remote_reader(struct writer *w, participant_t *ptcp,
				     struct participant_proxy *ptcp_proxy,
				     struct rtps_entity_id reader_eid,
				     int16_t userid)
{
	const endpoint_attr_t	*rattr;
	struct reader_proxy	*rproxy;

	/* The proxy object with this eid already exist. */
	if (writer_get_proxy(w, ptcp_proxy, reader_eid) != NULL) {
		return;
	}

	rattr = ptcp_find_static_remote_reader(ptcp, userid);
	if (rattr == NULL) {
		pr_debug("Fail to find out reader attr with userId:%d", userid);
		return;
	}

	if (mvbs_strcmp(w->attr->ep_attr.topic_name, rattr->topic_name) != 0) {
		return;
	}

	if (!ep_attr_match(&w->attr->ep_attr, rattr)) {
		return;
	}

	pr_debug("writer [%s] get a new reader with " ENTITY_ID_FMT "from %s",
			writer_get_topicname(w), ENTITY_ID_PARTS(reader_eid),
			ptcp_proxy->ptcp_name);

	rproxy = reader_proxy_alloc(w);
	if (rproxy == NULL) {
		pr_warn("mem pool has full");
		return;
	}

	reader_proxy_init(rproxy, ptcp_proxy, reader_eid,
			(rattr->qos.reliability_kind == (uint16_t)RELIABLE),
			(uint8_t)rattr->qos.durability_kind);

	writer_add_proxy(w, rproxy);

	pr_debug("%s -> Add new proxy from %s", writer_get_topicname(w),
					rproxy->ptcp_proxy->ptcp_name);

	writer_on_publication_matched(w, true);
}

static void static_remove_remote_writer(struct reader *r,
					const struct participant_proxy *ptcp_proxy,
					struct rtps_entity_id id)
{
	if ((r == NULL) || (ptcp_proxy == NULL)) {
		return;
	}

	if (reader_remove_proxy(r, ptcp_proxy, id)) {
		pr_debug("Remove a writer_proxy.");
	}
}

static void static_remove_remote_reader(struct writer *w,
					const struct participant_proxy *ptcp_proxy,
					struct rtps_entity_id id)
{
	if ((w == NULL) || (ptcp_proxy == NULL)) {
		return;
	}

	writer_remove_proxy(w, ptcp_proxy, id);
}

static bool static_from_property(struct rtps_property prop, struct edp_static_property *pstatic_prop)
{
	uint32_t i, j = 1;

	if ((mvbs_strncmp(&prop.name[0], "W", 1) == 0) || (mvbs_strncmp(&prop.name[0], "R", 1) == 0)) {
		(void)mvbs_strncpy(pstatic_prop->m_endpoint_type, &prop.name[0], 1);
		(void)mvbs_strncpy(pstatic_prop->m_status, &prop.name[1], 1);
		(void)mvbs_strncpy(pstatic_prop->m_userid_str, &prop.name[2], 8);

		pstatic_prop->m_user_id = (uint16_t)atoi(pstatic_prop->m_userid_str);
		pstatic_prop->m_entity_id.entity_key[0] = (uint8_t)atoi(prop.value);

		for (i = 0; i < (PROPERTY_MAX_LEN - 1U); i++) {
			if (prop.value[i] == '\0') {
				break;
			}

			if (prop.value[i] == '.') {
				if (j < 3U) {
					pstatic_prop->m_entity_id.entity_key[j] =
							(uint8_t)atoi(&prop.value[i + 1U]);
					j++;
				} else {
					pstatic_prop->m_entity_id.entity_kind =
							(uint8_t)atoi(&prop.value[i + 1U]);
					break;
				}

				continue;
			}
		}

		return true;
	}

	return false;
}

void static_assign_remote_endpoints(struct participant_proxy *ptcp_proxy,
                                    struct rtps_property_info *prop_info)
{
	participant_t *ptcp;
	struct writer *w;
	struct reader *r;
	uint32_t i;

	if (ptcp_proxy == NULL) {
		pr_err(ERR_INVALID, "ptcp_proxy is NULL.");
		return;
	}

	if ((prop_info == NULL) || (prop_info->property_list == NULL)
                                || (prop_info->valid_count == 0U)) {
		return;
	}

	ptcp = ptcp_proxy_get_ptcp(ptcp_proxy);

	for (i = 0; i < prop_info->valid_count; i++) {
		struct edp_static_property ep_prop;

		mvbs_memzero(&ep_prop, sizeof(ep_prop));

		if (static_from_property(prop_info->property_list[i], &ep_prop)) {

			if ((mvbs_strncmp(ep_prop.m_endpoint_type, "R", 1) == 0)
				&& (mvbs_strncmp(ep_prop.m_status, "A", 1) == 0)) {
				pr_verb("assignRemote reader");

				foreach_ptcp_writer(ptcp, w) {
					static_new_remote_reader(w, ptcp, ptcp_proxy,
						ep_prop.m_entity_id,
						(int16_t)ep_prop.m_user_id);
				}
			} else if ((mvbs_strncmp(ep_prop.m_endpoint_type, "W", 1) == 0)
				&& (mvbs_strncmp(ep_prop.m_status, "A", 1) == 0)) {
				pr_verb("assignRemote writer");
				foreach_ptcp_reader(ptcp, r) {
					static_new_remote_writer(r, ptcp, ptcp_proxy,
							ep_prop.m_entity_id,
							(int16_t)ep_prop.m_user_id);
				}
			} else if ((mvbs_strncmp(ep_prop.m_endpoint_type, "W", 1) == 0)
				&& (mvbs_strncmp(ep_prop.m_status, "E", 1) == 0)) {
				pr_debug("end remote writer");
				foreach_ptcp_reader(ptcp, r) {
					static_remove_remote_writer(r, ptcp_proxy, ep_prop.m_entity_id);
				}
			} else if ((mvbs_strncmp(ep_prop.m_endpoint_type, "R", 1) == 0)
				&& (mvbs_strncmp(ep_prop.m_status, "E", 1) == 0)) {
				pr_debug("end remote reader");
				foreach_ptcp_writer(ptcp, w) {
					static_remove_remote_reader(w, ptcp_proxy, ep_prop.m_entity_id);
				}
			} else {
				pr_warn("EDPStaticProperty with type: %s and status %s not recognized",
					string_or_null(ep_prop.m_endpoint_type), string_or_null(ep_prop.m_status));
			}
		}
	}
}

static char *uint16_to_string(uint16_t value, char *dest)
{
	char	*p  = dest;
	uint16_t cnt = 10000u;	/* 65535 */
	uint8_t  dec;

	if (value == 0u) {
		*p = '0'; p++;

		return p;
	}

	while (cnt != 0u) {
		dec	= value/cnt;
		value	= value%cnt;
		cnt	= cnt / 10u;

		if (dec != 0u) {
			*p = (char)dec + '0'; p++;
			break;
		}
	}

	while (cnt != 0u) {
		dec	= value/cnt;
		value	= value%cnt;
		cnt	= cnt / 10u;

		*p	=  (char)dec + '0'; p++;
	}

	return p;
}

static char *uint8_to_string(uint8_t value, char *dest)
{
	char	*p  = dest;
	uint8_t cnt = 100u;	/* 255 */
	uint8_t dec;

	if (value == 0u) {
		*p = '0'; p++;

		return p;
	}

	while (cnt != 0u) {
		dec	= value/cnt;
		value	= value%cnt;
		cnt	= cnt / 10u;

		if (dec != 0u) {
			*p = (char)dec + '0'; p++;

			break;
		}
	}

	while (cnt != 0u) {
		dec	= value/cnt;
		value	= value%cnt;
		cnt	= cnt / 10u;

		*p	= (char)dec + '0'; p++;
	}

	return p;
}

static char *userid_to_string(uint16_t userid, char *dest)
{
	return uint16_to_string(userid, dest);
}

static char *entity_id_to_string(struct rtps_entity_id eid, char *dest)
{
	char *p = dest;

	p = uint8_to_string(eid.entity_key[0], p);

	*p = '.'; p++;

	p = uint8_to_string(eid.entity_key[1], p);

	*p = '.'; p++;

	p = uint8_to_string(eid.entity_key[2], p);

	*p = '.'; p++;

	p = uint8_to_string(eid.entity_kind, p);

	return p;
}

static void static_to_property(struct rtps_property *prop, char type, char stat,
			      uint16_t userid, struct rtps_entity_id eid)
{
	char *dest;

	dest = prop->name;

	*dest = type; dest++;
	*dest = stat; dest++;

	dest = userid_to_string(userid, dest);

	*dest = '\0'; dest++;

	dest = prop->value;

	dest = entity_id_to_string(eid, dest);

	*dest = '\0'; dest++;
}

int16_t static_add_property(struct participant *ptcp, struct writer *delw,
				struct reader *delr, struct rtps_property *property)
{
	struct reader		*r;
	struct writer		*w;
	struct rtps_entity_id	eid;
	int32_t			num = 0;

	if ((ptcp == NULL) || (property == NULL)) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return -ERR_INVALID;
	}

	foreach_ptcp_reader(ptcp, r) {
		if (r == delr) {
			continue;
		}

		eid = reader_get_eid(r);

		static_to_property(&(property[num]), 'R', 'A',
				  (uint16_t)r->attr->ep_attr.user_defined_id,
				  eid);
		num++;

		if (num > PROPERTY_LIST_MAX_COUNT) {
			return 0;
		}
	}

	foreach_ptcp_writer(ptcp, w) {
		if (w == delw) {
			continue;
		}

		eid = writer_get_eid(w);

		static_to_property(&(property[num]), 'W', 'A',
				(uint16_t)w->attr->ep_attr.user_defined_id,
				eid);

		num++;

		if (num > PROPERTY_LIST_MAX_COUNT) {
			return 0;
		}
	}

	if (delw != NULL) {
		eid = writer_get_eid(delw);

		static_to_property(&(property[num]), 'W', 'E',
				  (uint16_t)delw->attr->ep_attr.user_defined_id,
				  eid);
		num++;

		if (num > PROPERTY_LIST_MAX_COUNT) {
			return 0;
		}
	}

	if (delr != NULL) {
		eid = reader_get_eid(delr);

		static_to_property(&(property[num]), 'R', 'E',
				  (uint16_t)delr->attr->ep_attr.user_defined_id,
				  eid);
		num++;

		if (num > PROPERTY_LIST_MAX_COUNT) {
			return 0;
		}
	}

	return (int16_t)num;
}

void static_delete_writer(struct participant *ptcp, struct writer *static_writer)
{
	if ((ptcp == NULL) || (static_writer == NULL)) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return;
	}
}

void static_delete_reader(struct participant *ptcp, struct reader *static_reader)
{
	if ((ptcp == NULL) || (static_reader == NULL)) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return;
	}
}

void ptcp_dpse_local_ep_match(participant_t *ptcp, participant_proxy_t *proxy)
{
	struct reader *r;
	struct writer *w;

	if ((ptcp == NULL) || (proxy == NULL)) {
		pr_info("Invalid parameters");
		return ;
	}

	foreach_ptcp_reader(ptcp, r) {
		foreach_ptcp_writer(ptcp, w) {
			static_new_remote_reader(w, ptcp, proxy,
					reader_get_eid(r),
					r->attr->ep_attr.user_defined_id);

			static_new_remote_writer(r, ptcp, proxy,
					writer_get_eid(w),
					w->attr->ep_attr.user_defined_id);
		}
	}
}

/* FIXME
 * The following three interfaces are currently referenced by both DPDE and
 * DPSE, and will be split into two instances in future.
 */
void ptcp_spdp_writer_send_pdp(struct participant *ptcp,
			       struct participant_proxy* ptcp_proxy,
			       struct writer *delw, struct reader *delr);

void ptcp_spdp_announce_online(struct participant *ptcp,
			       struct writer *delw, struct reader *delr);

void ptcp_spdp_announce_offline(struct participant *ptcp);

static void ptcp_dpse_announce_timer(void *args)
{
	struct participant	 *ptcp = (struct participant *)args;
	const participant_attr_t *attr = ptcp->attr;
	const duration_t	 *period;

	ptcp_spdp_writer_send_pdp(ptcp, NULL, NULL, NULL);

	ptcp->announce_count++;

	if (!ptcp->boost) {
		return ;
	}

	if (ptcp->announce_count >= attr->discovery.initial_announce_count) {
		period = &attr->discovery.lease_duration_announce_period;

		(void)mvbs_timer_update_timeout(ptcp, ptcp->pdp_announce_td,
					      MVBS_TIMER_RELTIME,
					      period->seconds, period->nanosec);

		ptcp->boost = false;
	}
}

int32_t ptcp_dpse_discovery_init(struct participant *ptcp)
{
	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "Invalid parameter.");
		return -ERR_INVALID;
	}

	if (ptcp->attr->discovery.edp_type != STATIC_EDP) {
		return -ERR_INVALID;
	}

	if (ptcp->pdp_announce_td != TIMER_DESC_INVALID) {
		pr_err(ERR_INVALID, "ptcp announce td has been already inited.");
		return -ERR_INVALID;
	}

	ptcp->pdp_announce_td = mvbs_timer_create(ptcp, ptcp_dpse_announce_timer, ptcp, 1);
	if (ptcp->pdp_announce_td == TIMER_DESC_INVALID) {
		pr_err(ERR_NOMEM, "Fail to create ptcp liveliness timer.");
		return -ERR_NOMEM;
	}

	(void)mvbs_timer_settime(ptcp, ptcp->pdp_announce_td, MVBS_TIMER_RELTIME,
			 ptcp->attr->discovery.initial_announce_period.seconds,
			 ptcp->attr->discovery.initial_announce_period.nanosec);

	(void)ptcp_wlp_init(ptcp);

	ptcp->dpse_inited = true;

	return 0;
}

int32_t ptcp_dpse_discovery_start(struct participant *ptcp)
{
	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "Invalid parameter.");
		return -ERR_INVALID;
	}

	if (ptcp->attr->discovery.edp_type != STATIC_EDP) {
		return -ERR_INVALID;
	}

	if (!ptcp->dpse_inited) {
		return -ERR_FAULT;
	}

	if (ptcp->pdp_announce_td == TIMER_DESC_INVALID) {
		pr_err(ERR_INVALID, "ptcp announce td hasn't been inited.");
		return -ERR_INVALID;
	}

	ptcp_spdp_announce_online(ptcp, NULL, NULL);

	void discovery_package_template_init(struct participant *ptcp);

	discovery_package_template_init(ptcp);

	(void)mvbs_timer_restart(ptcp, ptcp->pdp_announce_td);

	ptcp->dpse_started = true;

	return 0;
}

int32_t ptcp_dpse_discovery_stop(struct participant *ptcp)
{
	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "Invalid parameter.");
		return -ERR_INVALID;
	}

	if (ptcp->attr->discovery.edp_type != STATIC_EDP) {
		return -ERR_INVALID;
	}

	if (!ptcp->dpse_started) {
		return -ERR_FAULT;
	}

	if (ptcp->pdp_announce_td == TIMER_DESC_INVALID) {
		pr_err(ERR_INVALID, "ptcp announce td hasn't been inited.");
		return -ERR_INVALID;
	}

	ptcp_spdp_announce_offline(ptcp);

	(void)mvbs_timer_stop(ptcp, ptcp->pdp_announce_td);

	return 0;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
