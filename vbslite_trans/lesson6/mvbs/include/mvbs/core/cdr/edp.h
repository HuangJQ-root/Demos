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

#ifndef MVBS_CORE_CDR_EDP_H
#define MVBS_CORE_CDR_EDP_H

#include <mvbs/base_type.h>
#include <mvbs/rtps/guid.h>

struct endpoint_attr;
struct participant;
struct participant_proxy;
struct mvbs_cdr;
struct endpoint_info;

int32_t cdr_serialize_sedp_edp(struct mvbs_cdr *cdr,
			       const struct participant *ptcp,
			       const struct endpoint_attr *attr,
			       struct rtps_entity_id eid);

int32_t cdr_serialize_sedp_edp_offline(struct mvbs_cdr *cdr,
				       struct rtps_guid_prefix *guid,
				       struct rtps_entity_id eid);

bool sedp_edp_deserialize(struct mvbs_cdr *cdr, struct endpoint_info *pin,
						struct participant *ptcp);

size_t cdr_serialize_sedp_edp_length(const struct endpoint_attr *attr);

size_t cdr_serialize_sedp_offline_edp_length(void);

#endif
