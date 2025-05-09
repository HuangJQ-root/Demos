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
#include <mcdr/mcdr.h>
#include <discovery/sddp.h>
#include <discovery/sedp_agent.h>
#include <messages/message_factory.h>

#include <diag/diag.h>
#include <diag/query.h>

#include <diag/query_serialize.h>
#include <diag/query_deserialize.h>
#include <mvbs/diag/query.h>

#ifdef MVBS_DIAG_REQUEST_READER_ENABLE
static void query_deserialize_request_header(struct mvbs_cdr *cdr,
				struct rtps_guid *writer_guid,
				struct rtps_sn *query_sn,
				struct rtps_guid *reader_guid,
				int32_t *cmd_kind)
{
	char 		instance_name[256];
	uint32_t 	temp;

	// deserialize config opts
	// (void)msg_deser_config_opts(cdr);
	(void)mcdr_deserialize_uint32_t(cdr, &temp);
	(void)mcdr_deserialize_uint32_t(cdr, &temp);

	// deserialize writer_guid
	(void)query_deserialize_guid(cdr, writer_guid);
	// rtps_guid_print(writer_guid);

	// deserialize sn
	(void)mcdr_deserialize_int32_t(cdr, &query_sn->high);
	(void)mcdr_deserialize_uint32_t(cdr, &query_sn->low);

	// deserialize reader_guid
	(void)query_deserialize_guid(cdr, reader_guid);
	// rtps_guid_print(reader_guid);

	// skip instance name
	(void)mcdr_deserialize_string(cdr, instance_name, 256);

	// deserialize cmd_keyword
	(void)mcdr_deserialize_int32_t(cdr, cmd_kind);
}

int32_t query_request_on_data(struct participant_proxy *ptcp_proxy,
				const uint8_t *data, uint32_t size)
{
	int32_t ret 		= 0;
	struct mvbs_cdr		cdr;
	struct rtps_guid 	writer_guid;
	struct rtps_guid 	reader_guid;
	struct rtps_sn 		query_sn;
	int32_t cmd_kind 	= 0;
	uint32_t w_index 	= 0u;
	uint32_t r_index 	= 0u;
	struct rtps_guid 	target_id;
	char 			target_topic[64];
	struct query_reply_data_info data_info;


	struct participant *ptcp = ptcp_proxy_get_ptcp(ptcp_proxy);
	mcdr_init_buffer(&cdr, data, size);

	query_deserialize_request_header(&cdr, &writer_guid, &query_sn,
					&reader_guid, &cmd_kind);

	data_info.writer_id = (const struct rtps_entity_id *)&writer_guid;
	data_info.receiver = (const struct rtps_entity_id *)&reader_guid;
	data_info.query_sn = query_sn;
	data_info.ptcp_proxy = ptcp_proxy;
	data_info.ptcp = ptcp;
	data_info.cmd_kind = &cmd_kind;
	data_info.w_index = &w_index;
	data_info.r_index = &r_index;

	switch (cmd_kind) {
		case GET_WR_MATCH_GUIDS:
			cdr_deserialize_guid(&cdr, &target_id);
			data_info.cmd_arg = (void *)&target_id;
			ret = diag_reply_send_data(ptcp, ptcp_proxy,
					EXTRA_FLAGS_NORMAL,
					query_serialize_wr_match_guids_reply,
					&data_info);
			break;

		case GET_PTCP_WR_INFO:
			cdr_deserialize_guid(&cdr, &target_id);
			data_info.cmd_arg = (void *)&target_id;
			ret = diag_reply_send_data(ptcp, ptcp_proxy,
					EXTRA_FLAGS_NORMAL,
					query_serialize_ptcp_wr_info_reply,
					&data_info);
			break;

		case GET_W_SEND_INFO:
			cdr_deserialize_guid(&cdr, &target_id);
			data_info.cmd_arg = (void *)&target_id;
			ret = diag_reply_send_data(ptcp, ptcp_proxy,
					EXTRA_FLAGS_NORMAL,
					query_serialize_w_send_info_reply,
					&data_info);
			break;

		case GET_R_RECV_INFO:
			cdr_deserialize_guid(&cdr, &target_id);
			data_info.cmd_arg = (void *)&target_id;
			ret = diag_reply_send_data(ptcp, ptcp_proxy,
					EXTRA_FLAGS_NORMAL,
					query_serialize_r_recv_info_reply,
					&data_info);
			break;

		case GET_TOPIC_INFO:
			mcdr_deserialize_string(&cdr, target_topic, 64);
			data_info.cmd_arg = (void *)target_topic;
			ret = diag_reply_send_data(ptcp, ptcp_proxy,
					EXTRA_FLAGS_NORMAL,
					query_serialize_topic_info_reply,
					&data_info);
			break;
	}

	if (ret != 0) {
		pr_err(ERR_INVALID, "Send cmd reply error.");
	}

	return ret;
}
#else
int32_t query_request_on_data(struct participant_proxy *ptcp_proxy,
				const uint8_t *data, uint32_t size)
{
	(void)ptcp_proxy;
	(void)data;
	(void)size;

	return 0;
}
#endif

#ifdef MVBS_DIAG_REQUEST_WRITER_ENABLE
int32_t query_request_send_data(const struct buildin_writer *w,
				const struct participant_proxy *ptcp_proxy,
				int32_t *cmd_kind,
				void *cmd_arg)
{
	int32_t ret 		= 0;
	struct participant 	*ptcp;
	struct rtps_sn 		sn;
	struct query_request_data_info info;

	ptcp = ptcp_proxy_get_ptcp(ptcp_proxy);

	info.sender = &w->eid;
	info.receiver = &w->remote_eid;
	rtps_sn_set_value(&sn, 1);
	info.request_sn = sn;
	info.cmd_kind = cmd_kind;
	info.cmd_arg = cmd_arg;
	info.ptcp_proxy = ptcp_proxy;

	switch(*cmd_kind) {
		case GET_WR_MATCH_GUIDS:
			ret = diag_request_send_data(ptcp,
					(struct participant_proxy *)ptcp_proxy,
					EXTRA_FLAGS_NORMAL,
					query_serialize_request_by_guid,
					&info);
			break;

		case GET_PTCP_WR_INFO:
			ret = diag_request_send_data(ptcp,
					(struct participant_proxy *)ptcp_proxy,
					EXTRA_FLAGS_NORMAL,
					query_serialize_request_by_guid,
					&info);
			break;

		case GET_W_SEND_INFO:
			ret = diag_request_send_data(ptcp,
					(struct participant_proxy *)ptcp_proxy,
					EXTRA_FLAGS_NORMAL,
					query_serialize_request_by_guid,
					&info);
			break;

		case GET_R_RECV_INFO:
			ret = diag_request_send_data(ptcp,
					(struct participant_proxy *)ptcp_proxy,
					EXTRA_FLAGS_NORMAL,
					query_serialize_request_by_guid,
					&info);
			break;

		case GET_TOPIC_INFO:
			ret = diag_request_send_data(ptcp,
					(struct participant_proxy *)ptcp_proxy,
					EXTRA_FLAGS_NORMAL,
					query_serialize_request_by_topic,
					&info);
			break;
	}
	if (ret != 0) {
		pr_err(ERR_FAULT, "Send cmd request error.");
	}
	return ret;
}
#else
int32_t query_request_send_data(const struct buildin_writer *w,
				const struct participant_proxy *ptcp_proxy,
				int32_t *cmd_kind,
				void *cmd_arg)
{
	(void)ptcp_proxy;
	(void)w;
	(void)cmd_kind;
	(void)cmd_arg;

	return 0;
}
#endif

#ifdef MVBS_DIAG_REPLY_READER_ENABLE
void query_reply_on_data(const struct buildin_reader *r,
				struct participant_proxy *ptcp_proxy,
				const struct submessage_data *msg,
				const struct submessage_data_extra *extra)
{
	(void)r;
	(void)msg;
	(void)ptcp_proxy;

	struct mvbs_cdr		cdr;
	struct rtps_guid 	writer_guid;
	struct rtps_guid 	reader_guid;
	struct rtps_sn 		sn;
	int32_t 		cmd_kind;

	mcdr_init_buffer(&cdr, extra->data, extra->size);

	query_deserialize_diag_reply(&cdr, &writer_guid, &sn,
			&reader_guid, &cmd_kind, extra->size);

	return;
}
#else
void query_reply_on_data(const struct buildin_reader *r,
			struct participant_proxy *ptcp_proxy,
			const struct submessage_data *msg,
			const struct submessage_data_extra *extra)
{
	(void)r;
	(void)ptcp_proxy;
	(void)msg;
	(void)extra;
}
#endif

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
