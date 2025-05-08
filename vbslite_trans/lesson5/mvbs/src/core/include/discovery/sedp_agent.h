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

#ifndef MVBS_CORE_DISCOVERY_SEDP_AGENT_H
#define MVBS_CORE_DISCOVERY_SEDP_AGENT_H

#include <core/core.h>
#include <mvbs/rtps/guid.h>

struct participant_proxy;
struct reader_proxy;

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

#endif
