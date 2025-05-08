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
#include <messages/message_receiver.h>
#include <messages/message_factory.h>
#include <diag/diag.h>
#include <mvbs/adapter/adapter.h>

enum {
	SOA_CMD_DISABLE		= 0,
	SOA_CMD_ENTRANCE	= 1,
	SOA_CMD_EXPORT		= 2,
	UNKNOWN_CMD		= 3
};


#ifdef MVBS_DIAG_REQUEST_READER_ENABLE
static void entity_recorder_disable(struct participant *ptcp,
				    struct rtps_entity_id *eid, uint16_t count)
{
	struct writer *w;
	struct reader *r;

	for (uint16_t i=0; i<count; i++) {
		switch (eid->entity_kind) {
		case USER_DEFINED_WRITER_WITHOUT_KEY:
			w = ptcp_get_writer_with_eid(ptcp, *eid);
			if (w) {
				writer_record_disable(w);
			}

			break;

		case USER_DEFINED_READER_WITHOUT_KEY:
			r = ptcp_get_reader_with_eid(ptcp, *eid);
			if (r) {
				reader_record_disable(r);
			}

			break;

		default:
			pr_err(ERR_INVALID, "Unknown entity_kind: %d.",
			       eid->entity_kind);
			break;
		}

		eid++;
	}
}

static void entity_recorder_entrance_enable(struct participant *ptcp,
				   struct rtps_entity_id *eid, uint16_t count)
{
	struct writer *w;
	struct reader *r;

	for (uint16_t i=0; i<count; i++) {
		switch (eid->entity_kind) {
		case USER_DEFINED_WRITER_WITHOUT_KEY:
			w = ptcp_get_writer_with_eid(ptcp, *eid);
			if (w) {
				writer_record_entrance_enable(w);
			}

			break;

		case USER_DEFINED_READER_WITHOUT_KEY:
			r = ptcp_get_reader_with_eid(ptcp, *eid);
			if (r) {
				reader_record_entrance_enable(r);
			}

			break;

		default:
			pr_err(ERR_INVALID, "Unknown entity_kind: %d.",
			       eid->entity_kind);
			break;
		}

		eid++;
	}
}

static void entity_recorder_export_enable(struct participant *ptcp,
				   struct rtps_entity_id *eid, uint16_t count)
{
	struct writer *w;
	struct reader *r;

	for (uint16_t i=0; i<count; i++) {
		switch (eid->entity_kind) {
		case USER_DEFINED_WRITER_WITHOUT_KEY:
			w = ptcp_get_writer_with_eid(ptcp, *eid);
			if (w) {
				writer_record_export_enable(w);
			}

			break;

		case USER_DEFINED_READER_WITHOUT_KEY:
			r = ptcp_get_reader_with_eid(ptcp, *eid);
			if (r) {
				reader_record_export_enable(r);
			}

			break;

		default:
			pr_err(ERR_INVALID, "Unknown entity_kind: %d.",
			       eid->entity_kind);
			break;
		}

		eid++;
	}
}

void recorder_request_on_data(struct participant *ptcp,
			      const uint8_t *data, uint16_t size)
{
	struct rtps_entity_id	*eid;
	uint16_t		*cmd_type;
	uint16_t		*entity_cnt;

	cmd_type   = (uint16_t *)data;
	entity_cnt = cmd_type + 1;
	eid        = (struct rtps_entity_id *)(entity_cnt +1);

	while ((uint8_t *)cmd_type < data + size) {
		if (*cmd_type == SOA_CMD_ENTRANCE) {
			entity_recorder_entrance_enable(ptcp, eid, *entity_cnt);
		}

		if (*cmd_type == SOA_CMD_EXPORT) {
			entity_recorder_export_enable(ptcp, eid, *entity_cnt);
		}

		if (*cmd_type == SOA_CMD_DISABLE) {
			entity_recorder_disable(ptcp, eid, *entity_cnt);
		}

		cmd_type   = (uint16_t *)(eid + *entity_cnt);
		entity_cnt = cmd_type + 1;
		eid        = (struct rtps_entity_id *)(entity_cnt +1);
	}
}
#else
void recorder_request_on_data(struct participant *ptcp,
			      uint8_t *data, uint16_t size)
{
	(void)ptcp;
	(void)data;
	(void)size;
}
#endif

#ifdef MVBS_DIAG_REPLY_WRITER_ENABLE
static const uint16_t recorder_extra_flag = EXTRA_FLAGS_RECORDER_DATA;

static uint16_t get_app_id_from_ip(const uint8_t *addr)
{
	if (addr == NULL) {
		return 0;
	}

	return ((uint16_t)(addr[2]) << 8) | (uint16_t)(addr[3]);
}


struct reply_data_info {
	const uint8_t *data;
	uint16_t size;
};

static bool recorder_reply_request(mvbs_cdr_t *cdr, void *arg)
{
	struct reply_data_info *cmd_reply = (struct reply_data_info *)arg;

	mcdr_serialize_array_uint8_t(cdr, cmd_reply->data, cmd_reply->size);

	return true;
}

static int32_t recorder_reply_data_to_recorder(struct participant *ptcp,
					      const uint8_t *data, uint16_t size)
{
	mvbs_cdr_t	*cdr;
	int32_t		ret;

	struct reply_data_info cmd_reply;

	if (ptcp == NULL) {
		pr_info("Invalid parameters.");
		return -ERR_INVALID;
	}

	if (ptcp->recorder_proxy == NULL) {
		pr_info("Has no recorder_proxy.");
		return -ERR_INVALID;
	}

	cdr = ptcp_get_tx_buffer(ptcp);

	mcdr_reset_buffer(cdr);

	cmd_reply.data = data;
	cmd_reply.size = size;

	ret = diag_reply_send_data(ptcp, ptcp->recorder_proxy,
				   EXTRA_FLAGS_RECORDER_CMD,
				   recorder_reply_request,
				   &cmd_reply);
	if (ret != 0) {
		pr_err(ERR_INVALID, "Send cmd reply error.");
	}

        return ret;
}

int32_t recorder_reply_data(struct participant *ptcp,
			    const uint8_t *data, uint16_t size)
{
	return recorder_reply_data_to_recorder(ptcp, data, size);
}

int32_t recorder_send_writer_record(struct participant *ptcp,
				    mvbs_cdr_t *cdr,
				    struct writer_cache_change *wcc,
				    locator_t *loc,
				    struct writer *w,
				    uint32_t submessage_header_offset)
{
	locator_t *meta_uc_loc;

	if (ptcp == NULL || cdr == NULL || wcc == NULL || loc == NULL) {
		pr_info("Invalid parameters.");
		return -ERR_INVALID;
	}

	if (ptcp->recorder_proxy == NULL) {
		return -ERR_INVALID;
	}

	uint16_t destAddr = get_app_id_from_ip(loc->ipv4_addr);
	uint16_t srcAddr  = get_app_id_from_ip(ptcp_locator_udp_ipaddr(ptcp, 0));
	struct rtps_entity_id writer_id = writer_get_eid(w);
	size_t cdr_pos_size = mcdr_buffer_length(cdr);

	mcdr_buffer_append_data(cdr, &srcAddr, sizeof(uint16_t));
	mcdr_buffer_append_data(cdr, &destAddr, sizeof(uint16_t));

	int32_t extra_flag_offset = submessage_header_offset + 4;

	mcdr_fill_buffer_with_offset(cdr, extra_flag_offset + 4,
				     (void*)&ENTITYID_DIAG_REPLY_READER,
				     sizeof(rtps_entity_id_t));

	mcdr_fill_buffer_with_offset(cdr, extra_flag_offset,
				     (void*)&recorder_extra_flag,
				     sizeof(uint16_t));

	mcdr_buffer_append_data(cdr, &writer_id, sizeof(uint32_t));

	meta_uc_loc = ptcp_proxy_get_meta_uc_loc(ptcp->recorder_proxy);

	int32_t ret = ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
					 mcdr_buffer_length(cdr),
					 meta_uc_loc, false);

	mcdr_reset_buffer_offset(cdr, cdr_pos_size);

	if (ret != 0) {
		pr_err(ERR_INVALID, "Writer send soa log has error,\
				buffer size is %u", mcdr_buffer_size(cdr));
	}
	return ret;
}

int32_t recorder_send_reader_record(struct participant *ptcp,
				   struct message_processing_info *pmsg_info,
				   uint8_t* data_start_ptr,
				   uint16_t data_size,
				   struct reader *r)
{
	locator_t *loc;

	if (ptcp == NULL || pmsg_info == NULL || data_start_ptr == NULL) {
		pr_info("Invalid parameters.");
		return -ERR_INVALID;
	}

	if (ptcp->recorder_proxy == NULL) {
		pr_info("Soa log no remote recorder proxy or loc is NULL.");
		return -ERR_INVALID;
	}

	if (pmsg_info->size + 8 > MVBS_UDP_RXBUFSIZE) {
		pr_err(ERR_INVALID, "Reader send soa log error, need more buffer space!");
		return -ERR_INVALID;
	}

	loc = ptcp_proxy_get_meta_uc_loc(ptcp->recorder_proxy);

	uint16_t destAddr = get_app_id_from_ip(ptcp_locator_udp_ipaddr(ptcp, 0));
	uint16_t srcAddr  = get_app_id_from_ip(loc->ipv4_addr);
	struct rtps_entity_id reader_id = reader_get_eid(r);

	mvbs_memcpy(data_start_ptr + data_size, &srcAddr, sizeof(uint16_t));
	mvbs_memcpy(data_start_ptr + data_size + sizeof(uint16_t), &destAddr, sizeof(uint16_t));
	mvbs_memcpy(data_start_ptr + data_size + sizeof(uint32_t), &reader_id, sizeof(uint32_t));
	mvbs_memcpy(data_start_ptr - 8 - 8, &ENTITYID_DIAG_REPLY_READER, sizeof(rtps_entity_id_t));
	mvbs_memcpy(data_start_ptr - 8 - 8 - 4, &recorder_extra_flag, sizeof(uint16_t));

	pmsg_info->size += 8;

	return ptcp_send_buffer_to(ptcp, pmsg_info->data,
					 pmsg_info->size, loc, false);
}
#else
int32_t recorder_reply_data(struct participant *ptcp,
				uint8_t *data, uint16_t size)
{
	(void)ptcp;
	(void)data;
	(void)size;

	return 0;
}

int32_t recorder_send_writer_record(struct participant *ptcp,
				struct mvbs_cdr *cdr,
				struct writer_cache_change *wcc,
				locator_t *loc,
				struct writer *w,
				uint32_t submessage_header_offset)
{
	(void)ptcp;
	(void)cdr;
	(void)wcc;
	(void)loc;
	(void)w;
	(void)submessage_header_offset;

	return 0;
}

int32_t recorder_send_reader_record(struct participant *ptcp,
				   struct message_processing_info *pmsg_info,
				   uint8_t* data_start_ptr,
				   uint16_t data_size,
				   struct reader *r)
{
	(void)ptcp;
	(void)pmsg_info;
	(void)data_start_ptr;
	(void)data_size;
	(void)r;

	return 0;
}
#endif


#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
