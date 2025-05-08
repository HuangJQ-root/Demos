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

#include <mvbs/utils/rx_buffer.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/log.h>
#include <mvbs/rtps/locator.h>
#include <mvbs/core/netio/socket.h>
#include <mvbs/core/netio/utils.h>
#include <mvbs/adapter/adapter.h>

#define SOCKET_MAX			(10u)

static mvbs_socket_t m_socks[SOCKET_MAX] = {
		[0] = {
			.id = SOCKET_FD_INVALID,
		},
		[1] = {
			.id = SOCKET_FD_INVALID,
		},
		[2] = {
			.id = SOCKET_FD_INVALID,
		},
		[3] = {
			.id = SOCKET_FD_INVALID,
		},
		[4] = {
			.id = SOCKET_FD_INVALID,
		},
		[5] = {
			.id = SOCKET_FD_INVALID,
		},
		[6] = {
			.id = SOCKET_FD_INVALID,
		},
		[7] = {
			.id = SOCKET_FD_INVALID,
		},
		[8] = {
			.id = SOCKET_FD_INVALID,
		},
		[9] = {
			.id = SOCKET_FD_INVALID,
		},
	};

static mvbs_socket_t *mvbs_get_core_socket(uint8_t index)
{
#if 0
	uint8_t core_id;

	core_id = mvbs_get_core_id();

	if (core_id >= 4) {
		return NULL;
	}

	return &m_socks[core_id][index];
#else
	return &m_socks[index];
#endif
}

int32_t mvbs_netio_init(void)
{
	if (mvbs_net_is_ready(0) == false) {
		return -ERR_FAULT;
	}

	return 0;
}

mvbs_socket_t *mvbs_socket_get(mvbs_socket_id_t socket_id)
{
	uint8_t i		= 0;
	uint8_t index		= 0;
	mvbs_socket_t *sock	= NULL;

	if (socket_id != SOCKET_FD_INVALID)
		index = socket_id % SOCKET_MAX;

	i = index;
	do {
		/* Take the current value of i for indexing */
		sock = mvbs_get_core_socket(i);
		i++;             /* Increment i for future use */
		if (sock->id == socket_id) {
			return sock;
		}
	} while (i < SOCKET_MAX);

	i = 0;
	do {
		/* Take the current value of i for indexing */
		sock = mvbs_get_core_socket(i);
		i++;             /* Increment i for future use */
		if (sock->id == socket_id) {
			return sock;
		}
	} while (i < index);

	pr_debug("sock find fail: %d", socket_id);

	return NULL;
}

mvbs_socket_t *mvbs_socket_alloc(mvbs_socket_id_t socket_id)
{
	mvbs_socket_t *sock = NULL;

	sock = mvbs_socket_get(SOCKET_FD_INVALID);
	if (sock == NULL) {
		pr_warn("sock alloc fail");
		return NULL;
	}

	sock->id	= socket_id;
	sock->ops	= NULL;

	mvbs_memzero(&sock->rx_buffer, sizeof(sock->rx_buffer));

	return sock;
}

void mvbs_socket_free(mvbs_socket_id_t socket_id)
{
	mvbs_socket_t *sock = NULL;

	sock = mvbs_socket_get(socket_id);
	if (sock == NULL) {
		return;
	}

	sock->id	= SOCKET_FD_INVALID;
	sock->ops	= NULL;

	mvbs_memzero(&sock->rx_buffer, sizeof(sock->rx_buffer));
}

int32_t mvbs_socket_setup_ops(int32_t sockfd, const struct mvbs_socket_ops *ops,
			      void *priv)
{
	mvbs_socket_id_t socket_id	= (mvbs_socket_id_t)sockfd;
	mvbs_socket_t *sock		= NULL;

	if (ops == NULL) {
		return -ERR_INVALID;
	}

	sock = mvbs_socket_get(socket_id);
	/*in case the child socket is not allocated*/
	if (sock == NULL) {
		sock = mvbs_socket_alloc(socket_id);
	}

	if (sock == NULL) {
		pr_warn("socket setcallbks fail");
		return -ERR_INVALID;
	}

	sock->id	= socket_id;
	sock->ops	= ops;
	sock->priv	= priv;

	return 0;
}

int32_t mvbs_socket_setup_rx_buffer(int32_t sockfd, void *buffer, uint32_t length)
{
	int32_t ret			= 0;
	mvbs_socket_id_t socket_id	= (mvbs_socket_id_t)sockfd;
	mvbs_socket_t *sock		= NULL;

	sock = mvbs_socket_get(socket_id);
	if (sock == NULL) {
		pr_warn("invalid param: sockfd=%u", socket_id);
		return -ERR_INVALID;
	}
	
	ret = tcpip_rx_buffer_init(&sock->rx_buffer, (uint8_t *)buffer, (size_t)length);
	if (ret != 0) {
		pr_debug("socket(%u) set private buffer fail.\n", socket_id);
		return ret;
	}

	pr_debug("socket(%u) set private buffer success.\n", socket_id);

	return 0;
}

bool mvbs_net_rx_indication(mvbs_socket_id_t socket_id, uint8_t *buff,
				uint16_t len, uint32_t ipv4_addr, uint16_t port)
{
	static uint32_t rx_incoming_counter = 0;

	mvbs_socket_t *sock = NULL;

	rx_incoming_counter++;

	pr_debug("rx_incoming_counter=%d", rx_incoming_counter);

	sock = mvbs_socket_get(socket_id);
	if ((sock == NULL) || (buff == NULL)) {
		return false;
	}
	if ((sock->ops == NULL) || (sock->ops->rx_indication == NULL)) {
		return false;
	}

	sock->ops->rx_indication((int32_t)socket_id, buff, len, ipv4_addr,
				     port, sock->priv);

	return true;
}

void mvbs_net_event_handler(mvbs_socket_id_t socket_id, mvbs_net_event_t event)
{
	mvbs_socket_t *sock = NULL;

	pr_info("SocketId=%d, Event=%d", socket_id, event);

	sock = mvbs_socket_get(socket_id);
	if ((sock == NULL) || (sock->ops == NULL) || (sock->ops->event == NULL)) {
		return;
	}

	sock->ops->event(socket_id, event);
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
