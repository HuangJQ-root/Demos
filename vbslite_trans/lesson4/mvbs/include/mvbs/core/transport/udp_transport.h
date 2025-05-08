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

#ifndef MVBS_CORE_TRANSPORT_UDP_H
#define MVBS_CORE_TRANSPORT_UDP_H

#include <mvbs/base_type.h>

struct participant;

void mvbs_udp_rx_buffer_max_usage_rate_update(struct participant *ptcp);
uint32_t mvbs_udp_rx_buffer_pkg_cnt(struct participant *ptcp);
uint32_t mvbs_udp_rx_buffer_unuse_size(struct participant *ptcp);
uint32_t mvbs_udp_rx_buffer_cur_usage_rate(struct participant *ptcp);
uint32_t mvbs_udp_rx_buffer_max_usage_rate(struct participant *ptcp);

#ifdef	__MVBS_CORE_SOURCE__
#include <mvbs/core/transport/transport.h>
#include <mvbs/utils/rx_buffer.h>
#include <mcdr/mcdr.h>

struct udp_rtps_link {
	/* FIXME: The int32_t maybe should be changed to mvbs_sock object */
	int32_t		sock_meta_mc;
	int32_t		sock_user_mc;	/* Not used now */
	int32_t		sock_meta_uc;
	int32_t		sock_user_uc;
#if 0
	locator_t	meta_mc_loc;
	locator_t	meta_uc_loc;
	locator_t	user_uc_loc;
#endif
};

struct udp_transport {
	struct transport	ops;

	struct mvbs_cdr		cdr;

	const struct transport_info_local	*cfg_local;
	const struct transport_info_udp		*cfg_udp;

	struct udp_rx_buffer	ringbuf_udp;
	struct udp_rx_buffer	ringbuf_local;

	uint8_t			*recv_buff;
	size_t			recv_size;

	uint16_t		domain_id;
	uint8_t			ptcp_id;

	transport_rx_cb		recv_callback;
	struct participant	*ptcp;

	int32_t			max_rate_udp_buf;
	int32_t			max_rate_local_buf;

	struct udp_rtps_link	links[2]; /* FIXME: TBD */
};

typedef struct udp_transport		udp_transport_t;

#endif

#endif
