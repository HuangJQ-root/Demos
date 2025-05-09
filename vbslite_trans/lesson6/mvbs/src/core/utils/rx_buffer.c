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

#include <mvbs/sections/start_sec_code.h>
#include <mvbs/sections/start_sec_bss.h>
#include <mvbs/sections/start_sec_const.h>
#include <mvbs/sections/start_sec_data.h>

#include <mvbs/errno.h>
#include <mvbs/utils/cdefs.h>
#include <mvbs/utils/rx_buffer.h>
#include <mvbs/utils/log.h>

#define UDP_PACK_GUARD		0xa5

struct udp_pack_info {
	uint8_t		guard;
	uint8_t 	socket_id;

	uint16_t	size;
	uint32_t	pkg_sn;
};

/*
 * for tasking compile error
 */
static void tcpip_rx_buffer_lock(void *rx_buffer)
{
	(void)rx_buffer;

	/* TODO: to be impl */
}

static void tcpip_rx_buffer_unlock(void *rx_buffer)
{
	(void)rx_buffer;

	/* TODO: to be impl */
}

int32_t udp_rx_buffer_init(struct udp_rx_buffer *udp_rx, uint8_t *buffer,
							 size_t size)
{
	/* check if the size is power of 2 */
	if ((udp_rx == NULL) || (buffer == NULL)
			     || (size == 0U) || ((size & (size - 1U)) != 0U)) {
		pr_err(ERR_INVALID, "null point or size invalid: %d\n", size);
		return -ERR_INVALID;
	}

	udp_rx->pkg_cnt  = 0;
	udp_rx->recv_cnt = 0;

	return mvbs_fifo_init(&udp_rx->buffer, buffer, size);
}

int32_t udp_rx_buffer_put_pkg(struct udp_rx_buffer *udp_rx, uint8_t socket_id,
					  const uint8_t *data, size_t len)
{
	struct udp_pack_info  pack_info;
	int32_t ret;

	if ((udp_rx == NULL) || (data == NULL) || (len == 0U)) {
		return -ERR_INVALID;
	}

	ret = udp_rx_buffer_unused(udp_rx);

	if ((ret < 0) || ((size_t)ret < (sizeof(pack_info) + len))) {
		return -ERR_NOBUFS;
	}

	tcpip_rx_buffer_lock(udp_rx);

	pack_info.guard		= UDP_PACK_GUARD;
	pack_info.socket_id	= socket_id;
	pack_info.size		= (uint16_t)len;
	pack_info.pkg_sn	= udp_rx->pkg_cnt;

	(void)mvbs_fifo_in(&udp_rx->buffer, &pack_info, sizeof(pack_info));
	(void)mvbs_fifo_in(&udp_rx->buffer, data, len);

	udp_rx->pkg_cnt++;

	tcpip_rx_buffer_unlock(udp_rx);

	return 0;
}

int32_t udp_rx_buffer_get_pkg(struct udp_rx_buffer *udp_rx, uint8_t *socket_id,
						uint8_t *data, size_t len)
{
	size_t l;
	int32_t buf_len;

	struct udp_pack_info pack_info;

	if ((udp_rx == NULL) || (data == NULL) || (len == 0U)) {
		return -ERR_INVALID;
	}

	buf_len = udp_rx_buffer_len(udp_rx);
	if (buf_len < 0) {
		return -ERR_NODATA;
	}

	if ((size_t)buf_len < sizeof(pack_info)) {
		return -ERR_NODATA;
	}

	(void)mvbs_fifo_peek(&udp_rx->buffer, &pack_info, sizeof(pack_info));

	/* FIXME:
	 * A better error handling should be introduced in.
	 */
	if (pack_info.pkg_sn != udp_rx->recv_cnt) {
		pr_err(ERR_FAULT, "socket(%u) packet sn(%u)/recv_nr(%u) isn't match.\n",
					pack_info.socket_id, pack_info.pkg_sn,
							   udp_rx->recv_cnt);
	}

	if ((size_t)buf_len < (sizeof(pack_info) + pack_info.size)) {
		return -ERR_NODATA;
	}

	l = min_size(len, (size_t)pack_info.size);

	tcpip_rx_buffer_lock(udp_rx);

	(void)mvbs_fifo_out_skip(&udp_rx->buffer, data, l, sizeof(pack_info));

	/* truncate packet data */
	if (pack_info.size > len) {
		(void)mvbs_fifo_skip(&udp_rx->buffer, (size_t)(pack_info.size - len));
	}

	udp_rx->recv_cnt++;

	if (socket_id != NULL) {
		*socket_id = pack_info.socket_id;
	}

	tcpip_rx_buffer_unlock(udp_rx);

	return (int32_t)l;
}

int32_t udp_rx_buffer_get_pkg_count(struct udp_rx_buffer *udp_rx)
{
	if (udp_rx == NULL) {
		return -ERR_INVALID;
	}

	if (udp_rx->pkg_cnt < udp_rx->recv_cnt) {
		return -ERR_NODATA;
	} else {
		return (int32_t)((int32_t)udp_rx->pkg_cnt - (int32_t)udp_rx->recv_cnt);
	}
}


int32_t udp_rx_buffer_peek_pkg(struct udp_rx_buffer *udp_rx, uint8_t *socket_id,
						  uint8_t *data, size_t len)
{
	size_t l;
	int32_t buf_len;

	struct udp_pack_info pack_info;

	if ((udp_rx == NULL) || (data == NULL) || (len == 0U)) {
		return -ERR_INVALID;
	}

	buf_len = udp_rx_buffer_len(udp_rx);
	if (buf_len < 0) {
		return -ERR_NODATA;
	}

	if ((uint32_t)buf_len < sizeof(pack_info)) {
		return -ERR_NODATA;
	}

	(void)mvbs_fifo_peek(&udp_rx->buffer, &pack_info, (uint32_t)sizeof(pack_info));

	/* FIXME:
	 * A better error handling should be introduced in.
	 */
	if (pack_info.pkg_sn != udp_rx->recv_cnt) {
		pr_err(ERR_FAULT, "socket(%u) packet sn(%u)/recv_nr(%u) isn't match.\n",
					pack_info.socket_id, pack_info.pkg_sn,
							   udp_rx->recv_cnt);
	}

	if ((size_t)buf_len < (sizeof(pack_info) + pack_info.size)) {
		return -ERR_NODATA;
	}

	l = min_size((size_t)len, (size_t)pack_info.size);

	(void)mvbs_fifo_peek_skip(&udp_rx->buffer, data, l, sizeof(pack_info));

	if (socket_id != NULL) {
		*socket_id = pack_info.socket_id;
	}

	return (int32_t)l;
}

int32_t udp_rx_buffer_usage_rate(struct udp_rx_buffer *udp_rx)
{
	int32_t usage_rate = 0;
	int32_t cur_len = udp_rx_buffer_len(udp_rx);
	int32_t total_size = udp_rx_buffer_size(udp_rx);

	if (cur_len >= 0 && total_size > 0) {
		usage_rate = (cur_len * 1000) / total_size;
	}

	return usage_rate;
}

int32_t tcpip_rx_buffer_init(struct tcpip_rx_buffer *tcpip_rx, uint8_t *buffer, size_t size)
{
	if ((tcpip_rx == NULL) || (buffer == NULL) || (size == 0U)) {
		return -ERR_INVALID;
	}

	return mvbs_fifo_init(&tcpip_rx->buffer, buffer, (uint32_t)size);
}

int32_t tcpip_rx_buffer_in(struct tcpip_rx_buffer *tcpip_rx, uint8_t *data, size_t len)
{
	int32_t ret;

	tcpip_rx_buffer_lock(tcpip_rx);

	ret = (int32_t)mvbs_fifo_in(&tcpip_rx->buffer, data, len);

	tcpip_rx_buffer_unlock(tcpip_rx);

	return ret;
}

int32_t tcpip_rx_buffer_out(struct tcpip_rx_buffer *tcpip_rx, uint8_t *data, size_t len)
{
	int32_t ret;

	tcpip_rx_buffer_lock(tcpip_rx);

	ret = (int32_t)mvbs_fifo_out(&tcpip_rx->buffer, data, len);

	tcpip_rx_buffer_unlock(tcpip_rx);

	return ret;
}

int32_t tcpip_rx_buffer_peek(struct tcpip_rx_buffer *tcpip_rx, uint8_t *data, size_t len)
{
	return (int32_t)mvbs_fifo_peek(&tcpip_rx->buffer, data, len);
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
