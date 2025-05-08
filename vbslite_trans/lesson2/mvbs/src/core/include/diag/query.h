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

#ifndef MVBS_CORE_QUERY_H
#define MVBS_CORE_QUERY_H

#include <core/core.h>
#include <mvbs/rtps/guid.h>
#include <discovery/sddp.h>

int32_t query_request_send_data(const struct buildin_writer *w,
				const struct participant_proxy *ptcp_proxy,
				int32_t *cmd_kind,
				void *cmd_arg);

int32_t query_request_on_data(struct participant_proxy *ptcp_proxy,
				const uint8_t *data,
				uint32_t size);

void query_reply_on_data(const struct buildin_reader *r,
				struct participant_proxy *ptcp_proxy,
				const struct submessage_data *msg,
				const struct submessage_data_extra *extra);

#endif
