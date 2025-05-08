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

#ifndef MVBS_CORE_MESSAGE_FACTORY_H
#define MVBS_CORE_MESSAGE_FACTORY_H

#include <core/core.h>
#include <mvbs/rtps/message.h>

struct mvbs_cdr;
struct participant;
struct endpoint_attr;
struct rtps_entity_id;

bool rtps_msg_add_header(struct mvbs_cdr *payload,
			 const struct rtps_guid_prefix *pprefix);

bool rtps_msg_add_submsg_acknack(struct mvbs_cdr *cdr,
				 const struct rtps_entity_id *writer_id,
				 const struct rtps_entity_id *reader_id,
				 const struct rtps_sn_set *sn_state,
				 int32_t acknack_count, bool final_flag);

bool rtps_msg_add_submsg_heartbeat(struct mvbs_cdr *cdr,
				   const struct rtps_entity_id *reader_id,
				   const struct rtps_entity_id *writer_id,
				   struct rtps_sn first_sn,
				   struct rtps_sn last_sn,
				   uint32_t acknack_count, bool liveliness);

bool rtps_msg_add_submsg_gap(struct mvbs_cdr *cdr,
			     const struct rtps_entity_id *writer_id,
			     const struct rtps_entity_id *reader_id,
			     struct rtps_sn gap_start,
			     struct rtps_sn_set *gap_list);

bool rtps_msg_add_submsg_e2e(struct mvbs_cdr *cdr,
				  const struct serialized_payload *payload,
				  const struct rtps_entity_id *reader_id,
				  const struct rtps_entity_id *writer_id,
				  struct rtps_sn *sn);

bool rtps_msg_init_submsg_e2e(struct mvbs_cdr *cdr,
			    const struct writer_cache_change *wcc);

bool rtps_msg_update_submsg_e2e(struct mvbs_cdr *cdr,
				struct writer *w,
				struct rtps_entity_id *reader_id,
				struct writer_cache_change *wcc);

bool rtps_msg_add_submsg_timestamp(struct mvbs_cdr *cdr,
				   const struct rtps_time *ts);

bool rtps_msg_add_submsg_data_raw(struct mvbs_cdr *cdr, const struct rtps_sn *sn,
				  const uint8_t *data, uint16_t length,
				  bool contains_inline_qos,
				  const struct rtps_entity_id *writer_id,
				  const struct rtps_entity_id *reader_id);

bool rtps_msg_add_submsg_data_wrap(struct mvbs_cdr *cdr, uint16_t extra_flags,
				   const struct rtps_sn *sn,
				   const struct rtps_entity_id *writer_id,
				   const struct rtps_entity_id *reader_id,
				   bool (*fn)(struct mvbs_cdr *cdr, void *arg),
				   void *arg);

bool rtps_msg_add_submsg_data(struct mvbs_cdr *cdr,
			 struct writer_cache_change *cc,
			 bool contains_inline_qos,
			 const struct rtps_entity_id *writer_id,
			 const struct rtps_entity_id *reader_id);

bool rtps_msg_add_submsg_data_sedp_edp(struct mvbs_cdr *cdr,
				       const struct rtps_entity_id *sender,
				       const struct rtps_entity_id *receiver,
				       struct rtps_sn sn,
				       const struct participant *ptcp,
				       const struct endpoint_attr *attr,
				       struct rtps_entity_id eid);

bool rtps_msg_add_submsg_data_sedp_offline_edp(struct mvbs_cdr *cdr,
				       const struct rtps_entity_id *sender,
				       const struct rtps_entity_id *receiver,
				       struct rtps_sn sn,
				       struct rtps_guid_prefix *guid,
				       struct rtps_entity_id  offline_eid);

bool rtps_msg_add_submsg_data_spdp_pdp(struct mvbs_cdr *cdr,
				       const struct rtps_entity_id *sender,
				       const struct rtps_entity_id *receiver,
				       struct rtps_sn sn,
				       struct participant *ptcp,
				       struct rtps_property *property,
				       int32_t pktnum);

bool ptcp_send_submsg_data_wrap(struct participant *ptcp,
				locator_t *loc, bool link_bakup,
				struct mvbs_cdr *cdr,
				uint16_t extra_flags,
				struct rtps_sn *sn,
				const struct rtps_entity_id *writer_id,
				const struct rtps_entity_id *reader_id,
				bool (*fn)(struct mvbs_cdr *cdr, void *arg),
				void *arg);

#endif
