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

#ifndef MVBS_CORE_TRANSPORT_H
#define MVBS_CORE_TRANSPORT_H

#include <mvbs/base_type.h>

struct participant;

/* FIXME:
 * Currently, transport_info_local hasn't been applied to mvbs transport
 * configure. And these members in transport_info_local have been inserted in
 * transport_info_udp CURRENTLY.
 */
struct trans_buf_info {
	uint32_t	 buffer_size;
	uint8_t		*buffer;
};

struct udp_info {
	uint8_t		addr[4];
	uint8_t		mask[4];

	uint32_t	addr_uint32_le;
	uint32_t	mask_uint32_le;
};

struct transport_info_local {
	struct trans_buf_info	buf_info;
};

struct transport_info_udp {
	struct trans_buf_info	buf_info;
	struct trans_buf_info	rx_buf;
	struct trans_buf_info	tx_buf;

	/* Indicate the count of udp_info */
	uint32_t		 info_cnt;
	const struct udp_info	*info;
};

struct transport_info_ipc_j6m {
	/* The buffer is for receive message for participant */
	struct trans_buf_info	buf_info;

	/* The buffer to store a pkg got from RingBuffer */
	struct trans_buf_info	rx_buf;

	/* The buffer for preparing a pkg to send */
	struct trans_buf_info	tx_buf;
};

struct transport_info {
	const struct transport_info_local	*local_comm;
	const struct transport_info_udp		*udp;
	const struct transport_info_ipc_j6m	*ipc_j6m;
};

#ifdef	__MVBS_CORE_SOURCE__
#include <mvbs/core/transport/locator.h>

struct mvbs_cdr;
struct endpoint_attr;

typedef void (*transport_rx_cb)(struct participant *ptcp,
				const uint8_t *buf, size_t len,
				locator_t *loc);

struct transport {
	struct mvbs_cdr *(*get_tx_buffer)(struct transport *this);

	int32_t	(*sendto)(struct transport *this, locator_t *dst,
					const void *buf, size_t size);
	void    (*recv)(struct transport *this, uint32_t recv_max_pkg);

	int32_t	(*serialize_locator)(struct transport *this,
				     struct mvbs_cdr *cdr,
				     const struct endpoint_attr *attr, uint16_t pid);

	bool	(*detect_master_link)(struct transport *this, locator_t *loc);
	int32_t	(*detect_reachable)(struct transport *this, locator_t *loc);

	void	(*destroy)(struct transport *this);
};

struct transport *transport_create(struct participant *ptcp,
				   const struct transport_info *trans_info,
				   transport_rx_cb fn);

struct transport *transport_udp_create(struct participant *ptcp,
				       const struct transport_info *trans_info,
				       transport_rx_cb fn);

struct transport *transport_ipc_j6m_create(struct participant *ptcp,
				       const struct transport_info *trans_info,
				       transport_rx_cb fn);
#endif
#endif
