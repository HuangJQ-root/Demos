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

#ifndef MVBS_H
#define MVBS_H

#include <mvbs/core.h>
#include <mvbs/errno.h>

#define	MVBS_VERSION_MAJOR		2
#define	MVBS_VERSION_MINOR		1
#define	MVBS_VERSION_EXTRA		0
#define	MVBS_VERSION_PATCH		2

#define MVBS_VENDOR_ID_HIGH		0x0F
#define MVBS_VENDOR_ID_LOW		0x02

struct reader;
struct writer;
struct participant;
struct participant_attr;

int32_t mvbs_participant_init(struct participant *ptcp);
void mvbs_participant_deinit(struct participant *ptcp);

/*
 * These interfacs for mvbs intergration
 */
bool mvbs_recv_should_rework(struct participant *ptcp);

int32_t mvbs_get_udp_rx_buffer_unuse_size(struct participant *ptcp);
int32_t mvbs_get_local_rx_buffer_unuse_size(struct participant *ptcp);
int32_t mvbs_get_local_rx_buffer_total_size(struct participant *ptcp);

/* These interfaces are for mvbs test. */
uint16_t mvbs_get_rtps_header_size(void);

/* The following interface only for Linux. */
typedef void (*mvbs_loop_entry_t)(struct participant *ptcp);

int mvbs_loop_start(mvbs_loop_entry_t entry);

#endif
