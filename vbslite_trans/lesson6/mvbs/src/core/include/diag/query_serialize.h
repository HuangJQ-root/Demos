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

#ifndef MVBS_QUERY_SERIALIZATION_H
#define MVBS_QUERY_SERIALIZATION_H

#include <core/core.h>
#include <mvbs/rtps/guid.h>
#include <discovery/sddp.h>

struct diag_template {
	uint32_t 	reserve;
	uint8_t 	encapsulation_kind[2];
	uint16_t 	encapsulation_options;
};

struct query_request_data_info {
	const struct participant_proxy	*ptcp_proxy;
	const struct rtps_entity_id 	*sender;
	const struct rtps_entity_id 	*receiver;
	struct rtps_sn 			request_sn;
	int32_t 			*cmd_kind;
	void 				*cmd_arg;
};

struct query_reply_data_info {
	const struct rtps_entity_id 	*writer_id;
	const struct rtps_entity_id 	*receiver;
	struct rtps_sn 			query_sn;
	const struct participant_proxy *ptcp_proxy;
	const struct participant 	*ptcp;
	int32_t 			*cmd_kind;
	void 				*cmd_arg;
	uint32_t 			*w_index;
	uint32_t 			*r_index;
};

/* public */
void query_serialize_header(const struct participant_proxy *ptcp_proxy,
				struct mvbs_cdr *cdr,
				const struct rtps_entity_id *sender,
				const struct rtps_entity_id *receiver,
				struct rtps_sn sn, int32_t *cmd_kind);

void query_serialize_guid(struct mvbs_cdr *cdr, struct rtps_guid *id);


/* request */

bool query_serialize_request_by_guid(mvbs_cdr_t *cdr, void *arg);

bool query_serialize_request_by_topic(mvbs_cdr_t *cdr, void *arg);

/* reply */

bool query_serialize_wr_match_guids_reply(mvbs_cdr_t *cdr, void *arg);
bool query_serialize_ptcp_wr_info_reply(mvbs_cdr_t *cdr, void *arg);

bool query_serialize_w_send_info_reply(struct mvbs_cdr *cdr, void *arg);

bool query_serialize_r_recv_info_reply(struct mvbs_cdr *cdr, void *arg);

bool query_serialize_topic_info_reply(struct mvbs_cdr *cdr, void *arg);


#endif // DIAG_SERIALIZATION_H
