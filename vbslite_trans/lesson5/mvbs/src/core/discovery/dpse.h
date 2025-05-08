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

#ifndef MVBS_CORE_DPSE_H
#define MVBS_CORE_DPSE_H

#include <mvbs/base_type.h>

struct participant;

int32_t ptcp_dpse_discovery_init(struct participant *ptcp);
int32_t ptcp_dpse_discovery_start(struct participant *ptcp);
int32_t ptcp_dpse_discovery_stop(struct participant *ptcp);

#endif /* !MVBS_CORE_SDDP_H */
