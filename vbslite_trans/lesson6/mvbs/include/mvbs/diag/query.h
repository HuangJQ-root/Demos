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

#ifndef MVBS_DIAG_QUERY_H
#define MVBS_DIAG_QUERY_H

#include <mvbs/rtps/guid.h>
#include <mvbs/rtps/sequence_number.h>

struct participant;
struct endpoint_attr;
struct rtps_entity_id;

enum statistic_entity_type {
	STATICTIC_ENTITY_WRITER,
	STATICTIC_ENTITY_READER
};

struct writer_reader_info {
	uint8_t 		type;
	int32_t 		matched;
	struct rtps_guid 	guid;
	char 			topic_name[64];
	char 			type_name[128];
};

struct send_info {
	uint32_t 	send_payload_length_avg;
	uint32_t 	send_count;
	uint32_t 	send_throughput;
	int64_t 	last_pkt_timestamp;
	int64_t 	first_pkt_timestamp;
};

struct topic_info {
	uint8_t 		type;
	struct rtps_guid 	guid;
	uint32_t 		send_count;
	uint32_t 		recv_count;
	uint32_t 		lost_count;
	uint32_t 		rejected_count;
	char 			ptcp_name[64];
};

struct recv_info {
	uint32_t		recv_count_size;		// 1
	struct rtps_guid 	recv_count_guid;
	uint64_t		recv_count;
	uint32_t		lost_count_size;		// 1
	struct rtps_guid 	lost_count_guid;
	uint64_t		lost_count;
	uint32_t		avg_latancy_size;		// 0
	uint32_t		avg_throughput_size;		// 0
	uint32_t		last_pkt_timestamp_size;	// 0
	uint32_t		first_pkt_timestamp_size;	// 0
	uint32_t 		take_count_total;		// 0
	uint32_t 		untake_count;			// 0
	uint32_t		rejected_count;
};


/* print interface */
void print_guid(const struct rtps_guid *guid);

void print_ptcps_by_domain(struct rtps_guid *guid, char *ptcp_name, uint16_t index);

void print_ptcp_wr_info(struct writer_reader_info *info, uint32_t num);

void print_wr_match_guids(struct rtps_guid *guids, uint32_t num);

void print_w_send_info(struct send_info *send_info);

void print_r_recv_info(struct recv_info *recv_info);

void print_topic_info(struct topic_info *topic_info);


/* request interface*/
void get_ptcp_by_domain (uint8_t id);

void get_ptcp_detail_info(struct rtps_guid *target_ptcp_guid);

void get_wr_matched_guids(struct rtps_guid *target_guid);

void get_w_send_info(struct rtps_guid *target_guid);

void get_r_recv_info(struct rtps_guid *target_guid);

void get_topic_guids(char *target_topic);


#endif
