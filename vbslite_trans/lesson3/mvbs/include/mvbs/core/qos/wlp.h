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

#ifndef MVBS_CORE_QOS_WLP_H
#define MVBS_CORE_QOS_WLP_H

#ifdef __MVBS_CORE_SOURCE__
#include <mvbs/base_type.h>

struct reader;
struct writer;
struct writer_proxy;
struct participant;
struct participant_proxy;
struct buildin_reader;
struct buildin_writer;
struct submessage_data;
struct submessage_data_extra;
struct submessage_heartbeat;
struct submessage_acknack;

/*
 * MAX_ANNOUNCE_SIZE =
 * SCHEME_PL_CDR_LE (4) + InstanceHandle (16) + Reserve (8)
 */
#define MAX_ANNOUNCE_SIZE      28

void p2p_reader_on_data(const struct buildin_reader *r,
			struct participant_proxy *ptcp_proxy,
			const struct submessage_data *msg,
			const struct submessage_data_extra *extra);

void p2p_reader_on_heartbeat(const struct buildin_reader *r,
				     struct participant_proxy *ptcp_proxy,
				     const struct submessage_heartbeat *msg);

void p2p_writer_on_acknack(const struct buildin_writer *w,
				  struct participant_proxy *ptcp_proxy,
				  const struct submessage_acknack *msg);

void p2p_reader_on_ptcp_online(const struct buildin_reader *r,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy);


void p2p_writer_on_ptcp_online(const struct buildin_writer *w,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy);

int32_t ptcp_wlp_init(struct participant *ptcp);

int32_t wlp_add_local_writer(struct writer *w);
void wlp_delete_local_writer(struct writer *w);

int32_t wlp_add_local_reader(struct reader *r, struct writer_proxy *wproxy);
void wlp_delete_local_reader(struct reader *r, struct writer_proxy *wproxy);

void wlp_writer_assert_liveliness(struct writer *w, bool heartbeat);
void wlp_reader_assert_liveliness(struct reader *r, struct writer_proxy *wproxy);

void wlp_reader_match_writer(struct reader *r);
void wlp_reader_detach_writer(struct reader *r);

#endif
#endif
