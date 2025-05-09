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

#ifndef MVBS_UTILS_RX_BUFFER_H
#define MVBS_UTILS_RX_BUFFER_H

#include <mvbs/base_type.h>
#include <mvbs/errno.h>
#include <mvbs/utils/fifo.h>

struct udp_rx_buffer {
	uint32_t		pkg_cnt;
	uint32_t		recv_cnt;

	struct mvbs_fifo	buffer;
};

static inline int32_t udp_rx_buffer_unused(struct udp_rx_buffer *udp_rx)
{
	if (udp_rx == NULL) {
		return -ERR_INVALID;
	}

	return (int32_t)mvbs_fifo_unused(&udp_rx->buffer);
}

static inline int32_t udp_rx_buffer_len(struct udp_rx_buffer *udp_rx)
{
	if (udp_rx == NULL) {
		return -ERR_INVALID;
	}

	return mvbs_fifo_len(&udp_rx->buffer);
}

static inline int32_t udp_rx_buffer_size(struct udp_rx_buffer *udp_rx)
{
	if (udp_rx == NULL) {
		return -ERR_INVALID;
	}

	return mvbs_fifo_size(&udp_rx->buffer);
}

int32_t udp_rx_buffer_init(struct udp_rx_buffer *udp_rx, uint8_t *buffer, size_t size);

int32_t udp_rx_buffer_put_pkg(struct udp_rx_buffer *udp_rx, uint8_t socket_id,
					const uint8_t *data, size_t len);

int32_t udp_rx_buffer_get_pkg_count(struct udp_rx_buffer *udp_rx);

int32_t udp_rx_buffer_get_pkg(struct udp_rx_buffer *udp_rx, uint8_t *socket_id,
						uint8_t *data, size_t len);

int32_t udp_rx_buffer_peek_pkg(struct udp_rx_buffer *udp_rx, uint8_t *socket_id,
						uint8_t *data, size_t len);

int32_t udp_rx_buffer_usage_rate(struct udp_rx_buffer *udp_rx);

struct tcpip_rx_buffer {
	struct mvbs_fifo	buffer;
};

static inline int32_t tcpip_rx_buffer_available(struct tcpip_rx_buffer *tcpip_rx)
{
	if (tcpip_rx == NULL) {
		return -ERR_INVALID;
	}
	if (tcpip_rx->buffer.data == NULL) {
		return 0;
	}
	else {
		return -1;
	}
}

static inline int32_t tcpip_rx_buffer_unused(struct tcpip_rx_buffer *tcpip_rx)
{
	if (tcpip_rx == NULL) {
		return -ERR_INVALID;
	}

	return (int32_t)mvbs_fifo_unused(&tcpip_rx->buffer);
}

static inline int32_t tcpip_rx_buffer_len(struct tcpip_rx_buffer *tcpip_rx)
{
	if (tcpip_rx == NULL) {
		return -ERR_INVALID;
	}

	return mvbs_fifo_len(&tcpip_rx->buffer);
}

int32_t tcpip_rx_buffer_init(struct tcpip_rx_buffer *tcpip_rx, uint8_t *buffer, size_t size);

int32_t tcpip_rx_buffer_in(struct tcpip_rx_buffer *tcpip_rx, uint8_t *data, size_t len);

int32_t tcpip_rx_buffer_out(struct tcpip_rx_buffer *tcpip_rx, uint8_t *data, size_t len);

int32_t tcpip_rx_buffer_peek(struct tcpip_rx_buffer *tcpip_rx, uint8_t *data, size_t len);


#endif /* !MVBS_UTILS_RX_BUFFER_H */
