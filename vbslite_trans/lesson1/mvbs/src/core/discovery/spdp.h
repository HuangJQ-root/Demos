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

#ifndef MVBS_CORE_SPDP_H
#define MVBS_CORE_SPDP_H

#include <discovery/sddp.h>

void ptcp_spdp_writer_send_pdp(struct participant *ptcp,
			       struct participant_proxy *ptcp_proxy, struct writer *delw,
			       struct reader *delr);

void ptcp_pdp_reader_on_data(const struct buildin_reader *r,
				struct participant_proxy *ptcp_proxy,
				const struct submessage_data *msg,
				const struct submessage_data_extra *extra);

void ptcp_spdp_announce_online(struct participant *ptcp,
			       struct writer *delw, struct reader *delr);

void ptcp_spdp_announce_offline(struct participant *ptcp);

#endif /* !MVBS_CORE_SEDP_H */
