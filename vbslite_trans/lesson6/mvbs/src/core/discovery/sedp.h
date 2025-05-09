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

#ifndef MVBS_CORE_SEDP_H
#define MVBS_CORE_SEDP_H

#include <core/core.h>
#include <discovery/sddp.h>

int32_t sedp_add_writer(struct participant *ptcp, struct writer *w, int16_t idx);
int32_t sedp_add_reader(struct participant *ptcp, struct reader *r, int16_t idx);

bool sedp_delete_writer(struct participant *ptcp, struct writer *w);
bool sedp_delete_reader(struct participant *ptcp, struct reader *r);

void sedp_remove_remote_reader(struct participant *ptcp,
			       const struct participant_proxy *ptcp_proxy,
			       struct rtps_entity_id reader_eid);

void sedp_remove_remote_writer(struct participant *ptcp,
			       struct participant_proxy *ptcp_proxy,
			       struct rtps_entity_id id);

void sedp_do_local_match(struct participant_proxy *ptcp_proxy, 
			 struct writer *w, struct reader *r);

void pub_reader_on_data(const struct buildin_reader *r,
			struct participant_proxy *ptcp_proxy,
			const struct submessage_data *msg,
			const struct submessage_data_extra *extra);

void sub_reader_on_data(const struct buildin_reader *r,
			struct participant_proxy *ptcp_proxy,
			const struct submessage_data *msg,
			const struct submessage_data_extra *extra);

void pub_reader_on_heartbeat(const struct buildin_reader *r,
				    struct participant_proxy *ptcp_proxy,
				    const struct submessage_heartbeat *msg);

void sub_reader_on_heartbeat(const struct buildin_reader *r,
				    struct participant_proxy *ptcp_proxy,
				    const struct submessage_heartbeat *msg);

void pub_writer_on_acknack(const struct buildin_writer *bw,
				  struct participant_proxy *ptcp_proxy,
				  const struct submessage_acknack *msg);

void sub_writer_on_acknack(const struct buildin_writer *bw,
				  struct participant_proxy *ptcp_proxy,
				  const struct submessage_acknack *msg);

void pub_writer_on_ptcp_online(const struct buildin_writer *w,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy);

void sub_writer_on_ptcp_online(const struct buildin_writer *w,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy);

void pub_reader_on_ptcp_online(const struct buildin_reader *r,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy);

void sub_reader_on_ptcp_online(const struct buildin_reader *r,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy);


void pub_reader_send_acknack(struct participant_proxy *ptcp_proxy,
						uint16_t sample_cnt);

void sub_reader_send_acknack(struct participant_proxy *ptcp_proxy,
						uint16_t sample_cnt);

void pub_writer_send_hearbeat(const struct participant_proxy *ptcp_proxy,
						     bool liveliness);

void sub_writer_send_hearbeat(const struct participant_proxy *ptcp_proxy,
						     bool liveliness);


#endif /* !MVBS_CORE_SEDP_H */
