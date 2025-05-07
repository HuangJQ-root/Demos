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

#ifndef MVBS_CORE_NETIO_UDP_H
#define MVBS_CORE_NETIO_UDP_H

#include <mvbs/base_type.h>
#include <mvbs/core/netio/utils.h>

int32_t mvbs_udp_socket_open(void);

int32_t mvbs_udp_socket_close(int32_t sockfd);

int32_t mvbs_udp_socket_bind(int32_t sockfd, uint32_t ipv4_addr, uint16_t port);

int32_t mvbs_udp_socket_bind_multicast(int32_t sockfd, uint32_t multi_addr, uint32_t ipv4_addr, uint16_t port);

int32_t mvbs_udp_socket_sendto(int32_t sockfd, const void *buf, size_t len,
				uint32_t ipv4_addr, uint16_t port);

int32_t mvbs_udp_socket_recvfrom(int32_t sockfd, void *buf, size_t len,
			uint32_t *src_addr, uint16_t *src_port);
#endif
