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
#include <mvbs/rtps/guid.h>
#include <mvbs/errno.h>
#include <mvbs/utils/cdefs.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/log.h>
#include <messages/message_factory.h>
#include <discovery/sddp.h>
#include <discovery/sedp_agent.h>
#include <mcdr/mcdr.h>

#include <diag/query_serialize.h>
#include <mvbs/diag/query.h>

#define MAX_DIAG_LENGTH 1024

static void set_weid_by_key(struct rtps_entity_id *id, uint32_t key)
{
	id->entity_key[0] = (uint8_t)(key>>16);
	id->entity_key[1] = (uint8_t)(key>>8);
	id->entity_key[2] = (uint8_t)(key>>0);
	id->entity_kind = USER_DEFINED_WRITER_WITHOUT_KEY;
}

static void set_reid_by_key(struct rtps_entity_id *id, uint32_t key)
{
	id->entity_key[0] = (uint8_t)(key>>16);
	id->entity_key[1] = (uint8_t)(key>>8);
	id->entity_key[2] = (uint8_t)(key>>0);
	id->entity_kind = USER_DEFINED_READER_WITHOUT_KEY;
}

struct diag_template diag_temp = {
	.reserve 		= 0,
	.encapsulation_kind 	= {0x00, 0x01},
	.encapsulation_options 	= 0,
};

/* public */

void query_serialize_guid(struct mvbs_cdr *cdr, struct rtps_guid *id)
{
	(void)mcdr_serialize_array_uint8_t(cdr, id->prefix.id,
					   (uint32_t)sizeof(id->prefix.id));
	(void)mcdr_serialize_array_uint8_t(cdr, id->eid.entity_key,
					   (uint32_t)sizeof(id->eid.entity_key));
	(void)mcdr_serialize_uint8_t(cdr, id->eid.entity_kind);
}

uint32_t get_diag_header_length(void)
{
	uint32_t length = 0;

	length += 8u;							// PL_CDR_LE
	length += mcdr_get_alignment(length, 4) + 16u;	// writer_guid
	length += mcdr_get_alignment(length, 4) + 8u;	// sn
	length += mcdr_get_alignment(length, 4) + 16u;	// reader_guid
	length += mcdr_get_alignment(length, 4) + 4u + 1u;	// string: ""
	length += mcdr_get_alignment(length, 4) + 4u;	// cmd_kind

	return length;	// 60
}

void query_serialize_header(const struct participant_proxy *ptcp_proxy,
				struct mvbs_cdr *cdr,
				const struct rtps_entity_id *sender,
				const struct rtps_entity_id *receiver,
				struct rtps_sn sn, int32_t *cmd_kind)
{
	struct rtps_guid writer_guid;
	struct rtps_guid reader_guid;

	mcdr_buffer_append_data(cdr, &diag_temp,
				(uint32_t)sizeof(struct diag_template));

	// add writer_guid / request guid
	writer_guid.prefix = ptcp_proxy->guid.prefix;

	(void)sender;
	struct rtps_entity_id request_eid = {{0x00, 0x03, 0x00}, 0xc3};
	writer_guid.eid = request_eid;
	query_serialize_guid(cdr, &writer_guid);

	// add sn
	(void)mcdr_serialize_int32_t(cdr, sn.high);
	(void)mcdr_serialize_uint32_t(cdr, sn.low);

	// add reader_guid
	reader_guid.prefix = ptcp_proxy->guid.prefix;
	reader_guid.eid = *receiver;
	query_serialize_guid(cdr, &reader_guid);

	// add string
	(void)mcdr_serialize_string(cdr, "");

	// add cmd
	(void)mcdr_serialize_int32_t(cdr, *cmd_kind);

}

/* request */
bool query_serialize_request_by_topic(mvbs_cdr_t *cdr, void *arg)
{
	struct rtps_guid 	writer_guid;
	struct rtps_guid 	reader_guid;
	struct participant 	*ptcp;

	struct query_request_data_info *info = (struct query_request_data_info *)arg;

	// add template
	mcdr_buffer_append_data(cdr, &diag_temp,
				(uint32_t)sizeof(struct diag_template));


	ptcp = ptcp_proxy_get_ptcp(info->ptcp_proxy);

	// add writer_guid
	writer_guid.prefix = ptcp->guid_prefix;
	writer_guid.eid = *info->sender;
	query_serialize_guid(cdr, &writer_guid);

	// add sn
	(void)mcdr_serialize_int32_t(cdr, info->request_sn.high);
	(void)mcdr_serialize_uint32_t(cdr, info->request_sn.low);

	// add reader_guid
	reader_guid.prefix = info->ptcp_proxy->guid.prefix;
	reader_guid.eid = *info->receiver;
	query_serialize_guid(cdr, &reader_guid);

	// add string
	(void)mcdr_serialize_string(cdr, "");

	// add cmd
	(void)mcdr_serialize_int32_t(cdr, *info->cmd_kind);

	// add cmd payload
	(void)mcdr_serialize_string(cdr, (char *)info->cmd_arg);

	return true;

}

bool query_serialize_request_by_guid(mvbs_cdr_t *cdr, void *arg)
{
	struct query_request_data_info *info = (struct query_request_data_info *)arg;

	// add template
	mcdr_buffer_append_data(cdr, &diag_temp,
				(uint32_t)sizeof(struct diag_template));

	struct rtps_guid writer_guid;
	struct rtps_guid reader_guid;
	struct participant *ptcp;
	ptcp = ptcp_proxy_get_ptcp(info->ptcp_proxy);

	// add writer_guid
	writer_guid.prefix = ptcp->guid_prefix;
	writer_guid.eid = *info->sender;
	query_serialize_guid(cdr, &writer_guid);

	// add sn
	(void)mcdr_serialize_int32_t(cdr, info->request_sn.high);
	(void)mcdr_serialize_uint32_t(cdr, info->request_sn.low);

	// add reader_guid
	reader_guid.prefix = info->ptcp_proxy->guid.prefix;
	reader_guid.eid = *info->receiver;
	query_serialize_guid(cdr, &reader_guid);

	// add string
	(void)mcdr_serialize_string(cdr, "");

	// add cmd
	(void)mcdr_serialize_int32_t(cdr, *info->cmd_kind);

	// add cmd payload
	(void)query_serialize_guid(cdr, (struct rtps_guid *)info->cmd_arg);

	return true;

}

/* reply */
/* reply */
/* reply */

/* get reply length */

static uint32_t get_ptcp_wr_info_payload_length(struct writer_reader_info *info,
								uint32_t size)
{
	uint32_t previousSize = size; // 116

	size += mcdr_get_alignment(size, 1) + 1u;
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 1) + 12u + 4u;
	size += mcdr_get_alignment(size, 4) + 4u +
				(uint32_t)mvbs_strlen(info->topic_name) + 1u;
	size += mcdr_get_alignment(size, 4) + 4u
				+ (uint32_t)mvbs_strlen(info->type_name) + 1u;

	return size - previousSize;
}

/* serialize reply payload */

void diag_serialize_ptcp_wr_info(struct mvbs_cdr *cdr,
				struct writer_reader_info *info)
{
	(void)mcdr_serialize_uint8_t(cdr, info->type);
	(void)mcdr_serialize_int32_t(cdr, info->matched);
	(void)query_serialize_guid(cdr, &info->guid);
	(void)mcdr_serialize_string(cdr, info->topic_name);
	(void)mcdr_serialize_string(cdr, info->type_name);
}

void diag_serialize_recv_info(struct mvbs_cdr *cdr,
				struct recv_info *info)
{
	(void)mcdr_serialize_uint32_t(cdr, info->recv_count_size);
	(void)query_serialize_guid(cdr, &info->recv_count_guid);
	(void)mcdr_serialize_uint64_t(cdr, info->recv_count);

	(void)mcdr_serialize_uint32_t(cdr, info->lost_count_size);
	(void)query_serialize_guid(cdr, &info->lost_count_guid);
	(void)mcdr_serialize_uint64_t(cdr, info->lost_count);

	(void)mcdr_serialize_uint32_t(cdr, info->avg_latancy_size);
	(void)mcdr_serialize_uint32_t(cdr, info->avg_throughput_size);
	(void)mcdr_serialize_uint32_t(cdr, info->last_pkt_timestamp_size);
	(void)mcdr_serialize_uint32_t(cdr, info->first_pkt_timestamp_size);
	(void)mcdr_serialize_uint32_t(cdr, info->take_count_total);
	(void)mcdr_serialize_uint32_t(cdr, info->untake_count);

	(void)mcdr_serialize_uint32_t(cdr, info->rejected_count);
}

void diag_serialize_topic_info(struct mvbs_cdr *cdr,
				struct topic_info *topic_info)
{
	(void)mcdr_serialize_uint8_t(cdr, topic_info->type);
	(void)query_serialize_guid(cdr, &topic_info->guid);
	(void)mcdr_serialize_uint32_t(cdr, topic_info->send_count);
	(void)mcdr_serialize_uint32_t(cdr, topic_info->recv_count);
	(void)mcdr_serialize_uint32_t(cdr, topic_info->lost_count);
	(void)mcdr_serialize_uint32_t(cdr, topic_info->rejected_count);
	(void)mcdr_serialize_string(cdr, topic_info->ptcp_name);
}

void diag_serialize_send_info(struct mvbs_cdr *cdr, struct send_info* info)
{
	(void)mcdr_serialize_uint32_t(cdr, info->send_payload_length_avg);
	(void)mcdr_serialize_uint32_t(cdr, info->send_count);
	(void)mcdr_serialize_uint32_t(cdr, info->send_throughput);
	(void)mcdr_serialize_int64_t(cdr, info->last_pkt_timestamp);
	(void)mcdr_serialize_int64_t(cdr, info->first_pkt_timestamp);
}

bool diag_serialize_ptcp_wr_info_payload(const struct participant *ptcp,
						struct mvbs_cdr *cdr,
						uint32_t *w_index,
						uint32_t *r_index,
						uint32_t query_head_offset)
{
	int32_t 		w_matched_num;
	int32_t 		r_matched_num;
	struct writer 		*w;
	struct reader 		*r;
	uint32_t length 	= 116;
	uint32_t w_r_num 	= 0;
	uint8_t send_finish_flag = 0x01; // not finish
	struct writer_reader_info info;
	struct mvbs_cdr 	cdr_tmp;

	mvbs_memzero((void *)&info, sizeof(info));
	mcdr_copy_buffer(&cdr_tmp, cdr);
	mcdr_serialize_uint32_t(cdr, w_r_num);
	length += sizeof(uint32_t);

	uint32_t w_nums = ptcp_get_max_user_writers(ptcp);
	uint32_t r_nums = ptcp_get_max_user_readers(ptcp);

	// query all writers
	for (uint32_t i = *w_index; i < w_nums; i++) {
		w = ptcp_get_writer_by_index(ptcp, i);

		// assemble
		w_matched_num = mem_pool_avail_blk_cnt(&w->proxies);
		info.type = STATICTIC_ENTITY_WRITER;
		info.matched = w_matched_num;
		info.guid.prefix = ptcp->guid_prefix;
		set_weid_by_key(&info.guid.eid,
				(uint32_t)w->attr->ep_attr.entity_id);

		mvbs_memcpy((void *)info.topic_name,
				w->attr->ep_attr.topic_name,
				sizeof(info.topic_name));
		mvbs_memcpy((void *)info.type_name,
				w->attr->type->name,
				sizeof(info.type_name));

		// get length
		uint32_t temp_length =  get_ptcp_wr_info_payload_length(&info,
									length);
		length += temp_length;
		if (length > MAX_DIAG_LENGTH) {
			// serialize match size
			(void)mcdr_buffer_append_data(&cdr_tmp,
							&w_r_num,
							sizeof(w_r_num));

			// set flag: send not finished
			(void)mcdr_fill_buffer_with_offset(cdr,query_head_offset,
							&send_finish_flag,
							sizeof(send_finish_flag));

			return false;
		}

		// serialize
		diag_serialize_ptcp_wr_info(cdr, &info);

		w_r_num++;

		(*w_index)++;
	}

	// query all readers
	for (uint32_t j = *r_index; j < r_nums; j++) {
		r = ptcp_get_reader_by_index(ptcp, j);

		// assemble
		r_matched_num = mem_pool_avail_blk_cnt(&r->proxies);
		info.type = STATICTIC_ENTITY_READER;
		info.matched = r_matched_num;
		info.guid.prefix = ptcp->guid_prefix;
		set_reid_by_key(&info.guid.eid,
				(uint32_t)r->attr->ep_attr.entity_id);

		mvbs_memcpy((void *)info.topic_name,
				r->attr->ep_attr.topic_name,
				sizeof(info.topic_name));
		mvbs_memcpy((void *)info.type_name,
				r->attr->type->name,
				sizeof(info.type_name));

		// get length
		uint32_t temp_length = get_ptcp_wr_info_payload_length(&info,
									length);
		length += temp_length;
		if (length > MAX_DIAG_LENGTH) {
			// serialize match size
			(void)mcdr_buffer_append_data(&cdr_tmp,
							&w_r_num,
							sizeof(w_r_num));

			// set flag: send not finished
			(void)mcdr_fill_buffer_with_offset(cdr,
							query_head_offset,
							&send_finish_flag,
							sizeof(send_finish_flag));

			return false;
		}
		// serialize
		diag_serialize_ptcp_wr_info(cdr, &info);
		w_r_num++;
		(*r_index)++;
	}
	// serialize match size
	(void)mcdr_buffer_append_data(&cdr_tmp, &w_r_num, sizeof(w_r_num));
	return true;
}

bool diag_serialize_r_recv_info_payload(const struct participant *ptcp,
						struct mvbs_cdr *cdr,
						struct rtps_guid *target_id)
{
	struct reader *local_reader 	= NULL;
	struct rtps_entity_id 		target_eid;
	struct recv_info 		recv_info;

	target_eid = target_id->eid;

	// find reader by eid
	local_reader = ptcp_get_reader_with_eid((struct participant *)ptcp,
								target_eid);
	if (local_reader == NULL) {
		pr_warn("find reader failed by guid");
		return -ERR_INVALID;
	}

	// assemble
	recv_info.recv_count_size = 1u;
	mvbs_memzero(&recv_info.recv_count_guid,
		sizeof(recv_info.recv_count_guid));
	recv_info.recv_count = reader_get_committed_sample(local_reader);

	recv_info.lost_count_size = 1u;
	mvbs_memzero(&recv_info.lost_count_guid,
		sizeof(recv_info.lost_count_guid));
	recv_info.lost_count = reader_get_lost_sample(local_reader);

	recv_info.avg_latancy_size = 0u;
	recv_info.avg_throughput_size = 0u;
	recv_info.last_pkt_timestamp_size = 0u;
	recv_info.first_pkt_timestamp_size = 0u;
	recv_info.take_count_total = 0u;
	recv_info.untake_count = 0u;

	recv_info.rejected_count = reader_get_rejected_sample(local_reader);

	// serialize
	diag_serialize_recv_info(cdr, &recv_info);

	return true;
}


bool diag_serialize_topic_info_payload(const struct participant *ptcp,
						struct mvbs_cdr *cdr,
						char *target_topic)
{
	struct topic_info 		topic_info;
	struct writer *local_writer 	= NULL;
	struct reader *local_reader 	= NULL;

	// find writer/reader by topic
	local_writer = ptcp_get_writer_with_topic(ptcp, target_topic);
	local_reader = ptcp_get_reader_with_topic(ptcp, target_topic);

	// assemble
	if (local_writer != NULL && local_reader == NULL) {
		topic_info.type = STATICTIC_ENTITY_WRITER;
		topic_info.guid.prefix = ptcp->guid_prefix;
		set_weid_by_key(&topic_info.guid.eid,
			(uint32_t)local_writer->attr->ep_attr.entity_id);
		topic_info.send_count = writer_get_committed_sample(local_writer);
		topic_info.recv_count = 0u;
		topic_info.lost_count = 0u;
		topic_info.rejected_count = 0u;
		mvbs_memcpy(topic_info.ptcp_name, ptcp->attr->name, 64);
	}
	else if (local_writer == NULL && local_reader != NULL) {
		topic_info.type = STATICTIC_ENTITY_READER;
		topic_info.guid.prefix = ptcp->guid_prefix;
		set_reid_by_key(&topic_info.guid.eid,
			(uint32_t)local_reader->attr->ep_attr.entity_id);
		topic_info.send_count = 0u;
		topic_info.recv_count = reader_get_committed_sample(local_reader);
		topic_info.lost_count = reader_get_lost_sample(local_reader);
		topic_info.rejected_count = reader_get_rejected_sample(local_reader);
		mvbs_memcpy(topic_info.ptcp_name, ptcp->attr->name, 64);
	}
	else {
		pr_warn("find writer/reader failed by topic");
		return -ERR_NOENT;
	}

	//serialize
	diag_serialize_topic_info(cdr, &topic_info);

	return true;
}

bool diag_serialize_w_send_info_payload(const struct participant *ptcp,
						struct mvbs_cdr *cdr,
						struct rtps_guid *target_id)
{
	struct send_info 		send_info;
	struct writer *local_writer 	= NULL;
	struct rtps_entity_id 		target_eid;

	target_eid = target_id->eid;

	// find writer by eid
	local_writer = ptcp_get_writer_with_eid((struct participant *)ptcp,
						target_eid);

	if (local_writer == NULL) {
		pr_err(ERR_INVALID, "find local_writer failed");
		return -ERR_INVALID;
	}

	// assemble
	send_info.send_payload_length_avg = 0u;
	send_info.send_count = writer_get_committed_sample(local_writer);
	send_info.send_throughput = 0u;
	send_info.last_pkt_timestamp = 0;
	send_info.first_pkt_timestamp = 0;

	// serialize
	diag_serialize_send_info(cdr, &send_info);

	return true;
}

bool diag_serialize_wr_match_guids_payload(const struct participant *ptcp,
						struct mvbs_cdr *cdr,
						struct rtps_guid *target_id)
{
	struct rtps_guid 		guid;
	struct writer *local_writer 	= NULL;
	struct reader *local_reader 	= NULL;
	struct rtps_entity_id 		target_eid;
	struct mvbs_cdr cdr_tmp;

	struct reader_proxy *r_proxy;
	struct writer_proxy *w_proxy;

	target_eid = target_id->eid;

	uint32_t index = 0;
	mcdr_copy_buffer(&cdr_tmp, cdr);
	mcdr_serialize_uint32_t(cdr, index);

	// find writer by eid
	if (target_eid.entity_kind == USER_DEFINED_WRITER_WITHOUT_KEY) {
		local_writer = ptcp_get_writer_with_eid((struct participant *)ptcp,
							target_eid);
		if (local_writer == NULL) {
			pr_warn("find local_writer failed");
			return -ERR_NOENT;
		}

		foreach_writer_proxy(local_writer, r_proxy) {
			guid.prefix = r_proxy->ptcp_proxy->guid.prefix;
			guid.eid = r_proxy->eid;

			(void)query_serialize_guid(cdr, &guid);
			index++;
		}
	}
	// find reader by eid
	else if (target_eid.entity_kind == USER_DEFINED_READER_WITHOUT_KEY) {
		local_reader = ptcp_get_reader_with_eid((struct participant *)ptcp,
							target_eid);
		if (local_reader == NULL) {
			pr_warn("find local_reader failed");
			return -ERR_NOENT;
		}

		foreach_reader_proxy(local_reader, w_proxy) {
			guid.prefix = w_proxy->ptcp_proxy->guid.prefix;
			guid.eid = w_proxy->eid;

			(void)query_serialize_guid(cdr, &guid);
			index++;
		}
	}
	else {
		pr_warn("get WR_MatchGuids_reply failed!");
		return -ERR_INVALID;
	}

	// serialize match size
	(void)mcdr_buffer_append_data(&cdr_tmp, &index, sizeof(index));

	return true;
}


/* serialize reply */

bool query_serialize_wr_match_guids_reply(mvbs_cdr_t *cdr, void *arg)
{
	bool ret;
	struct query_reply_data_info *info = arg;
	if ((cdr == NULL) || (info->ptcp == NULL)) {
		return -ERR_INVALID;
	}

	query_serialize_header(info->ptcp_proxy, cdr,
				info->writer_id,info->receiver,
				info->query_sn, info->cmd_kind);
	ret = diag_serialize_wr_match_guids_payload(info->ptcp, cdr,
					(struct rtps_guid *)info->cmd_arg);

	return ret;
}

bool query_serialize_ptcp_wr_info_reply(mvbs_cdr_t *cdr, void *arg)
{
	bool ret;
	uint32_t query_head_offset;
	struct query_reply_data_info *info = arg;

	if ((cdr == NULL) || (info->ptcp == NULL)) {
		return -ERR_INVALID;
	}
	query_head_offset = mcdr_buffer_length(cdr);
	query_serialize_header(info->ptcp_proxy, cdr,
			info->writer_id, info->receiver,
			info->query_sn, info->cmd_kind);
	ret = diag_serialize_ptcp_wr_info_payload(info->ptcp, cdr,
					info->w_index, info->r_index,
						query_head_offset);

	return ret;

}

bool query_serialize_w_send_info_reply(mvbs_cdr_t *cdr, void *arg)
{
	bool ret;
	struct query_reply_data_info *info = arg;

	if ((cdr == NULL) || (info->ptcp == NULL)) {
		return -ERR_INVALID;
	}

	query_serialize_header(info->ptcp_proxy, cdr,
			info->writer_id, info->receiver,
				info->query_sn, info->cmd_kind);
	ret = diag_serialize_w_send_info_payload(info->ptcp, cdr,
					(struct rtps_guid *)info->cmd_arg);

	return ret;

}

bool query_serialize_r_recv_info_reply(mvbs_cdr_t *cdr, void *arg)
{
	bool ret;
	struct query_reply_data_info *info = arg;

	if ((cdr == NULL) || (info->ptcp == NULL)) {
		return -ERR_INVALID;
	}

	query_serialize_header(info->ptcp_proxy, cdr,
				info->writer_id, info->receiver,
				info->query_sn, info->cmd_kind);
	ret = diag_serialize_r_recv_info_payload(info->ptcp, cdr,
					(struct rtps_guid *)info->cmd_arg);

	return ret;
}

bool query_serialize_topic_info_reply(mvbs_cdr_t *cdr, void *arg)
{
	bool ret;
	struct query_reply_data_info *info = arg;

	if ((cdr == NULL) || (info->ptcp == NULL)) {
		return -ERR_INVALID;
	}

	query_serialize_header(info->ptcp_proxy, cdr,
			info->writer_id, info->receiver,
			info->query_sn, info->cmd_kind);
	ret = diag_serialize_topic_info_payload(info->ptcp, cdr,
						(char *)info->cmd_arg);

	return ret;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>

