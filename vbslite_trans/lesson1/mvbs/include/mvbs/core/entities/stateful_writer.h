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

#ifndef MVBS_CORE_ENTITIES_STATEFUL_WRITER_H
#define MVBS_CORE_ENTITIES_STATEFUL_WRITER_H

#ifdef __MVBS_CORE_SOURCE__
#include <mvbs/core/types.h>
#include <mvbs/rtps/sequence_number.h>

struct writer;
struct reader_proxy;
struct participant_proxy;
struct rtps_sn_set;
struct submessage_acknack;


struct writer_status {
	uint32_t		hb_count;
	uint32_t		samples;

	timer_desc_t		heartbeat_td;

	uint8_t			hb_boost : 1;
	uint8_t			running : 1;
	uint8_t			record_mode : 2;
	uint8_t			lstatus : 2;
};

void sfwriter_change_removed_by_history(struct writer *w,
					struct rtps_sn *seq_num);

void sfwriter_check_change_ack_status(struct writer *w);

void sfwriter_on_new_acknack(struct writer *w,
			     const struct submessage_acknack *msg,
			     const struct participant_proxy  *ptcp_proxy);

void sfwriter_send_heartbeat(struct writer *w, bool liveliness);

void sfwriter_send_gap(struct writer *w,
		       struct reader_proxy *rproxy,
		       struct rtps_sn gap_start,
		       struct rtps_sn_set *gap_list);

int32_t sfwriter_init(struct writer *w);
void sfwriter_deinit(struct writer *w);

#endif
#endif
