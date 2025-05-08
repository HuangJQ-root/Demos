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

#ifndef MVBS_CORE_DIAG_H
#define MVBS_CORE_DIAG_H

#include <mvbs/errno.h>
#include <discovery/sddp.h>

struct writer_proxy;
struct participant;

#ifdef MVBS_DIAG_REQUEST_READER_ENABLE
void diag_request_on_data(const struct buildin_reader *r,
                        struct participant_proxy *ptcp_proxy,
                        const struct submessage_data *msg,
                        const struct submessage_data_extra *extra);

void diag_request_on_heartbeat(const struct buildin_reader *r,
				     struct participant_proxy *ptcp_proxy,
				     const struct submessage_heartbeat *msg);

void diag_request_reader_on_ptcp_online(const struct buildin_reader *r,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy);

void diag_request_reader_on_ptcp_offline(const struct buildin_reader *r,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy);
#endif

#ifdef MVBS_DIAG_REQUEST_WRITER_ENABLE
int32_t diag_request_send_data(struct participant *ptcp,
			       struct participant_proxy *proxy,
			       uint16_t extra_flags,
			       bool (*send_data)(mvbs_cdr_t *cdr, void *arg),
			       void *arg);

void diag_request_on_acknack(const struct buildin_writer *w,
			     struct participant_proxy *ptcp_proxy,
			     const struct submessage_acknack *msg);

void diag_request_writer_on_ptcp_online(const struct buildin_writer *w,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy);

void diag_request_writer_on_ptcp_offline(const struct buildin_writer *w,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy);
#endif

#ifdef MVBS_DIAG_REPLY_READER_ENABLE
void diag_reply_on_data(const struct buildin_reader *r,
                        struct participant_proxy *ptcp_proxy,
                        const struct submessage_data *msg,
                        const struct submessage_data_extra *extra);

void diag_reply_on_heartbeat(const struct buildin_reader *r,
				struct participant_proxy *ptcp_proxy,
				const struct submessage_heartbeat *msg);

void diag_reply_reader_on_ptcp_online(const struct buildin_reader *r,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy);

void diag_reply_reader_on_ptcp_offline(const struct buildin_reader *w,
					struct participant *ptcp,
					struct participant_proxy *ptcp_proxy);
#endif

#ifdef MVBS_DIAG_REPLY_WRITER_ENABLE
int32_t diag_reply_send_data(struct participant *ptcp,
			     struct participant_proxy *proxy,
			     uint16_t extra_flags,
			     bool (*send_data)(mvbs_cdr_t *cdr, void *arg),
			     void *arg);

void diag_reply_on_acknack(const struct buildin_writer *w,
				struct participant_proxy *ptcp_proxy,
				const struct submessage_acknack *msg);

void diag_reply_writer_on_ptcp_online(const struct buildin_writer *w,
					struct participant *ptcp,
					struct participant_proxy *ptcp_proxy);

void diag_reply_writer_on_ptcp_offline(const struct buildin_writer *w,
					struct participant *ptcp,
					struct participant_proxy *ptcp_proxy);
#endif

int32_t ptcp_diag_init(struct participant *ptcp);

#endif
