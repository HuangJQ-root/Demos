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

#ifndef MVBS_CORE_NETIO_UTILS_H
#define MVBS_CORE_NETIO_UTILS_H

#include <mvbs/base_type.h>

#define SOCKET_FD_INVALID			((uint8_t)(~0U))

#ifdef MVBS_BIG_ENDIAN
#define mvbs_htons(x_) ((uint16_t)(x_))
#else
#define mvbs_htons(x_) ((uint16_t)((((((uint16_t)(x_))>>8U)&0x00ffU) | \
			((((uint16_t)(x_))<<8U)&0xff00U))))
#endif

int32_t mvbs_inet_aton(const char *src, uint32_t *inp);

static inline void mvbs_netio_print_stack_time(void) { }

void DDS_Transmit2Tcp_Prehook(const char *topic_name);
void DDS_Transmit2Tcp_Posthook(const char *topic_name);
void udp_transmit_hook_set_topicname(const char *topic_name);
void udp_transmit_hook_clr_topicname(void);
void udp_transmit_prev_hook(void);
void udp_transmit_post_hook(void);

#endif /* !MVBS_CORE_NETIO_UTILS_H */
