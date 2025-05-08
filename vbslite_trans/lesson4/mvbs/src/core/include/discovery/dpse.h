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

#ifndef MVBS_CORE_DISCOVERY_DPSE_H
#define MVBS_CORE_DISCOVERY_DPSE_H

#include <core/core.h>

struct participant_proxy;

void ptcp_dpse_local_ep_match(struct participant *ptcp,
				struct participant_proxy *proxy);

void static_delete_writer(struct participant *ptcp, struct writer *static_writer);
void static_delete_reader(struct participant *ptcp, struct reader *static_reader);

void static_assign_remote_endpoints(struct participant_proxy *ptcp_proxy,
				    struct rtps_property_info *prop_info);

int16_t static_add_property(struct participant *ptcp,
			    struct writer *delw, struct reader *delr,
			    struct rtps_property *property);

#endif
