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

#ifndef MVBS_CORE_TRANSPORT_LOCAL_H
#define MVBS_CORE_TRANSPORT_LOCAL_H

#include <mvbs/base_type.h>

struct participant;

void mvbs_local_rx_buffer_max_usage_rate_update(struct participant *ptcp);
bool mvbs_local_rx_buffer_is_empty(struct participant *ptcp);
uint32_t mvbs_local_rx_buffer_get_size(struct participant *ptcp);
uint32_t mvbs_local_rx_buffer_total_size(struct participant *ptcp);
uint32_t mvbs_local_rx_buffer_pkg_count(struct participant *ptcp);
uint32_t mvbs_local_rx_buffer_unuse_size(struct participant *ptcp);
uint32_t mvbs_local_rx_buffer_cur_usage_rate(struct participant *ptcp);
uint32_t mvbs_local_rx_buffer_max_usage_rate(struct participant *ptcp);

#endif
