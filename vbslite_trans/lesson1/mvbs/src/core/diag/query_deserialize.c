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
#include <mvbs/errno.h>
#include <mvbs/rtps/guid.h>
#include <mvbs/utils/cdefs.h>
#include <mvbs/utils/log.h>
#include <messages/message_factory.h>
#include <discovery/sddp.h>
#include <discovery/sedp_agent.h>
#include <mcdr/mcdr.h>

#include <diag/query_deserialize.h>
#include <mvbs/diag/query.h>

#define HEADER_LENGTH		(8 + 16 + 8 + 16 + 4 + 1 + 3 + 4)
#define MAX_WR_NUM		200
#define MAX_MATCH_NUM		10

#ifdef MVBS_DIAG_REPLY_WRITER_ENABLE
void __attribute__((weak)) print_guid(const struct rtps_guid *guid)
{
	(void)guid;
}

void __attribute__((weak)) print_ptcp_wr_info(struct writer_reader_info *info,
								uint32_t num)
{
	(void)info;
	(void)num;
}

void __attribute__((weak)) print_wr_match_guids(struct rtps_guid *guids,
							uint32_t num)
{
	(void)guids;
	(void)num;
}

void __attribute__((weak)) print_w_send_info(struct send_info *send_info)
{
	(void)send_info;
}

void __attribute__((weak)) print_r_recv_info(struct recv_info *recv_info)
{
	(void)recv_info;
}

void __attribute__((weak)) print_topic_info(struct topic_info *topic_info)
{
	(void)topic_info;
}

/* reply */
static void query_deserialize_reply_header(struct mvbs_cdr *cdr,
				struct rtps_guid *writer_guid,
				struct rtps_sn *sn,
				struct rtps_guid *reader_guid,
				int32_t *cmd_kind)
{
	char 		instance_name[5];
	uint32_t 	temp1;
	uint32_t 	temp2;

	// deserialize config opts
	// (void)msg_deser_config_opts(cdr);
	mcdr_deserialize_uint32_t(cdr, &temp1);
	mcdr_deserialize_uint32_t(cdr, &temp2);

	// deserialize writer_guid
	(void)query_deserialize_guid(cdr, writer_guid);

	// deserialize sn
	(void)mcdr_deserialize_int32_t(cdr, &sn->high);
	(void)mcdr_deserialize_uint32_t(cdr, &sn->low);

	// deserialize reader_guid
	(void)query_deserialize_guid(cdr, reader_guid);

	// skip instance name
	(void)mcdr_deserialize_string(cdr, instance_name, 1);

	// deserialize cmd_keyword
	(void)mcdr_deserialize_int32_t(cdr, cmd_kind);
}

static void query_deserialize_w_send_info_reply_payload(struct mvbs_cdr *cdr)
{
	struct send_info send_info;

	(void)mcdr_deserialize_uint32_t(cdr, &send_info.send_payload_length_avg);
	(void)mcdr_deserialize_uint32_t(cdr, &send_info.send_count);
	(void)mcdr_deserialize_uint32_t(cdr, &send_info.send_throughput);
	(void)mcdr_deserialize_int64_t(cdr, &send_info.last_pkt_timestamp);
	(void)mcdr_deserialize_int64_t(cdr, &send_info.first_pkt_timestamp);

	print_w_send_info(&send_info);
}

static void query_deserialize_ptcp_wr_info_reply_payload(struct mvbs_cdr *cdr)
{
	uint32_t wr_num = 0u;

	(void)mcdr_deserialize_uint32_t(cdr, &wr_num);
	struct writer_reader_info info[MAX_WR_NUM];

	for (uint32_t i = 0; i < wr_num; i++) {
		(void)mcdr_deserialize_uint8_t(cdr, &info[i].type);
		(void)mcdr_deserialize_int32_t(cdr, &info[i].matched);
		(void)query_deserialize_guid(cdr, &info[i].guid);
		(void)mcdr_deserialize_string(cdr, info[i].topic_name, 64);
		(void)mcdr_deserialize_string(cdr, info[i].type_name, 128);
	}

	print_ptcp_wr_info(info, wr_num);
}

static void query_deserialize_r_recv_info_reply_payload(struct mvbs_cdr *cdr)
{
	struct recv_info recv_info;

	(void)mcdr_deserialize_uint32_t(cdr, &recv_info.recv_count_size);
	(void)query_deserialize_guid(cdr, &recv_info.recv_count_guid);
	(void)mcdr_deserialize_uint64_t(cdr, &recv_info.recv_count);

	(void)mcdr_deserialize_uint32_t(cdr, &recv_info.lost_count_size);
	(void)query_deserialize_guid(cdr, &recv_info.lost_count_guid);
	(void)mcdr_deserialize_uint64_t(cdr, &recv_info.lost_count);

	(void)mcdr_deserialize_uint32_t(cdr, &recv_info.avg_latancy_size);
	(void)mcdr_deserialize_uint32_t(cdr, &recv_info.avg_throughput_size);
	(void)mcdr_deserialize_uint32_t(cdr, &recv_info.last_pkt_timestamp_size);
	(void)mcdr_deserialize_uint32_t(cdr, &recv_info.first_pkt_timestamp_size);
	(void)mcdr_deserialize_uint32_t(cdr, &recv_info.take_count_total);
	(void)mcdr_deserialize_uint32_t(cdr, &recv_info.untake_count);

	(void)mcdr_deserialize_uint32_t(cdr, &recv_info.rejected_count);

	print_r_recv_info(&recv_info);

}

static void query_deserialize_topic_info_reply_payload(struct mvbs_cdr *cdr)
{
	struct topic_info topic_info;

	(void)mcdr_deserialize_uint8_t(cdr, &topic_info.type);
	(void)query_deserialize_guid(cdr, &topic_info.guid);
	(void)mcdr_deserialize_uint32_t(cdr, &topic_info.send_count);
	(void)mcdr_deserialize_uint32_t(cdr, &topic_info.recv_count);
	(void)mcdr_deserialize_uint32_t(cdr, &topic_info.lost_count);
	(void)mcdr_deserialize_uint32_t(cdr, &topic_info.rejected_count);
	(void)mcdr_deserialize_string(cdr, topic_info.ptcp_name, 64);

	print_topic_info(&topic_info);
}

static void query_deserialize_wr_match_guids_reply_payload(struct mvbs_cdr *cdr)
{
	uint32_t match_num = 0;
	mcdr_deserialize_uint32_t(cdr, &match_num);
	struct rtps_guid guids[MAX_MATCH_NUM];

	for (uint32_t i = 0; i < match_num; i++) {
		(void)query_deserialize_guid(cdr, &guids[i]);
	}
	print_wr_match_guids(guids, match_num);
}

void query_deserialize_diag_reply(struct mvbs_cdr *cdr,
				struct rtps_guid *writer_guid,
				struct rtps_sn *sn,
				struct rtps_guid *reader_guid,
				int32_t *cmd_kind,
				uint16_t size)
{
	(void)size;

	query_deserialize_reply_header(cdr, writer_guid, sn,
					reader_guid, cmd_kind);

	switch(*cmd_kind) {
		case GET_PTCP_WR_INFO:
			query_deserialize_ptcp_wr_info_reply_payload(cdr);
			break;
		case GET_WR_MATCH_GUIDS:
			query_deserialize_wr_match_guids_reply_payload(cdr);
			break;

		case GET_W_SEND_INFO:
			query_deserialize_w_send_info_reply_payload(cdr);
			break;

		case GET_R_RECV_INFO:
			query_deserialize_r_recv_info_reply_payload(cdr);
			break;
		case GET_TOPIC_INFO:
			query_deserialize_topic_info_reply_payload(cdr);
			break;
		default:
			break;
	}
}
#else
void query_deserialize_diag_reply(struct mvbs_cdr *cdr,
				struct rtps_guid *writer_guid,
				struct rtps_sn *sn,
				struct rtps_guid *reader_guid,
				int32_t *cmd_kind,
				uint16_t size)
{
	(void)cdr;
	(void)writer_guid;
	(void)sn;
	(void)reader_guid;
	(void)cmd_kind;
	(void)size;
}
#endif

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
