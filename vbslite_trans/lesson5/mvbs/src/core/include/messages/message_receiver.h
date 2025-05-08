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

#ifndef MVBS_CORE_MESSAGE_RECEIVER_H
#define MVBS_CORE_MESSAGE_RECEIVER_H

#include <core/core.h>
#include <mvbs/rtps/message.h>

 /* This structure storing message parsing intermediate. */
struct message_receiver {
	struct participant		*ptcp;
	struct participant_proxy	*ptcp_proxy;	 /* Maybe NULL */

	struct message_header		rtps_hdr;

	struct rtps_time		info_ts;	/* INFO_TS */
	struct e2e_header		info_e2e;	/* INFO_E2E */

	bool				have_timestamp;
	bool				have_e2e;
};

 /* This structure storing data message parsing intermediate. */
struct reader_data {
	struct participant_proxy	*ptcp_proxy;

	struct rtps_entity_id		reader_id;
	struct rtps_entity_id		writer_id;

	struct writer_proxy		*wproxy;

	struct rtps_sn			sn;

	struct rtps_time		src_time;

	const void			*data;
	uint16_t			size;

	uint16_t			e2e_counter;
	uint32_t			e2e_status;
	struct e2e_header		*e2e_new;

	uint8_t				data_flags;
};

bool msg_recv_process(struct participant *ptcp, const uint8_t *data,
						uint16_t size,
						bool discard_own);
#endif

