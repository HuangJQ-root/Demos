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

#ifndef MVBS_CORE_CDR_PDP_H
#define MVBS_CORE_CDR_PDP_H

#include <mvbs/base_type.h>

struct participant;
struct participant_proxy;
struct mvbs_cdr;
struct rtps_property;
struct rtps_property_info;

bool ptcp_proxy_parse(struct participant *ptcp,
		      struct participant_proxy *ptcp_proxy,
		      struct mvbs_cdr *cdr,
		      struct rtps_property_info *prop_info, uint32_t *status_info);

int32_t cdr_serialize_spdp_pdp(struct mvbs_cdr *cdr,
			       struct participant *ptcp,
			       struct rtps_property *property, int32_t propty_cnt);

int32_t cdr_serialize_spdp_pdp_offline(struct mvbs_cdr *cdr,
				       struct participant *ptcp);

size_t cdr_serialize_spdp_pdp_length(struct participant *ptcp,
				struct rtps_property *property, int32_t prop_cnt);

bool cdr_deserialize_ptcp_proxy(struct mvbs_cdr *cdr,
				struct participant_proxy *ptcp_proxy,
				struct participant *ptcp,
				struct rtps_property_info *prop_info,
				uint32_t *status_info);

#endif
