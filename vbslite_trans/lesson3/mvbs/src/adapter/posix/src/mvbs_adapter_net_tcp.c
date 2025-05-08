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

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifndef	__MVBS_CORE_SOURCE__
#define __MVBS_CORE_SOURCE__
#endif
#include <mvbs/core.h>
#include <mvbs/errno.h>
#include <mvbs/utils/cdefs.h>
#include <mvbs/utils/log.h>

#ifdef	TARGET_PRODUCT_MINGW
#include <winsock2.h>
#include <ws2tcpip.h>

extern int close(int fd);

#ifndef MSG_CONFIRM
#define MSG_CONFIRM				0
#endif
#else
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#include <mvbs_adapter.h>
#include <mvbs/utils/log.h>

#include "adapter_socket.h"

#define TCPIP_LISTEN_MAX			20

mvbs_net_err_t mvbs_tcp_socket_create(mvbs_socket_id_t *socket_id)
{
	struct adapter_socket *ms;

	if (socket_id == NULL)
		return MVBS_NET_ERR_INVPARAM;

	ms = adapter_socket_alloc_tcp();
	if (ms == NULL) {
		return MVBS_NET_ERR_MEM;
	}

	*socket_id = adapter_socket_get_index(ms);

	return MVBS_NET_E_OK;
}

mvbs_net_err_t mvbs_tcp_bind(mvbs_socket_id_t socket_id, uint32_t ipv4_addr,
							  uint16_t port)
{
	int  ret;
	sock_fd_t  fd;
	struct adapter_socket *ms;
	struct sockaddr_in addr = { 0 };

	(void)ipv4_addr;

	ms = adapter_socket_get(socket_id);

	fd = adapter_socket_get_fd(ms);
	if (sock_fd_is_invalid(fd))
		return MVBS_NET_ERR_INVPARAM;

	addr.sin_family		= AF_INET;
	addr.sin_addr.s_addr	= htonl(INADDR_ANY);
	addr.sin_port		= htons(port);

	ret = bind(fd, (const struct sockaddr *)&addr, sizeof(addr));
	pr_debug("socket_id=%d, port=%d, ret=%d", socket_id, port, ret);
	if (ret < 0) {
		pr_err(ERR_BIND, "failed!: %s", strerror(errno));
		return MVBS_NET_ERR_INVPARAM;
	}

	adapter_socket_set_port(ms, port);

	return MVBS_NET_E_OK;
}


static void adapter_socket_tcp_read(sock_fd_t fd, short events, struct adapter_socket *ms)
{
	char                    buffer[4096];
	struct sockaddr_in      ip_src = {0}; //TODO, FIXME
	int                     ret = 0;

	if (events & ADAPTER_SOCK_READ) {
		ret = recv(fd, buffer, sizeof(buffer), 0);
		if (ret == 0) {
			pr_info("connection closed.");

			mvbs_net_event_handler(adapter_socket_get_index(ms), MVBS_NET_EV_TCP_FIN_RECEIVED);

			adapter_socket_disconnected(ms);
		} else if(ret < 0){
			pr_warn("recv error.\n");
		} else {
			(void)mvbs_net_rx_indication(adapter_socket_get_index(ms),
						     (uint8_t *)buffer, ret,
						     ip_src.sin_addr.s_addr,
						     ip_src.sin_port);
		}
	}
}

static void adapter_socket_tcp_listen(sock_fd_t fd, short events, struct adapter_socket *ms)
{
	struct adapter_socket	*ms_new;
	struct sockaddr		in_addr;
	struct sockaddr_in*	addr;

	(void)fd;

	if (events & ADAPTER_SOCK_READ) {
		ms_new = adapter_socket_accept(ms, &in_addr, adapter_socket_tcp_read);

		addr = (struct sockaddr_in*)(&in_addr);
		mvbs_tcp_accepted(adapter_socket_get_index(ms),
				  adapter_socket_get_index(ms_new),
				  addr->sin_addr.s_addr, addr->sin_port);

		return ;
	}
}

mvbs_net_err_t mvbs_tcp_listen(mvbs_socket_id_t socket_id, uint16_t max_chans)
{
	struct adapter_socket *ms;
	int ret;

	if (max_chans > TCPIP_LISTEN_MAX) {
		return MVBS_NET_ERR_INVPARAM;
	}

	ms = adapter_socket_get(socket_id);

	ret = adapter_socket_listen(ms, max_chans, adapter_socket_tcp_listen);
	if (ret < 0) {
		pr_err(ERR_LISTEN, "failed!: %s", strerror(ret));
		return MVBS_NET_ERR_INVPARAM;
	}

	return MVBS_NET_E_OK;
}

static void adapter_socket_tcp_connect(sock_fd_t fd, short events, struct adapter_socket *ms)
{
	char			buffer[4096];
	struct sockaddr_in	ip_src = {0};
	int			ret;
	int err;
	socklen_t len = sizeof(err);

	getsockopt(fd, SOL_SOCKET, SO_ERROR, (void *)&err, &len);
	if (err != 0) {
		/* FIXME */
		pr_warn("connect failed");
		return ;
	}

	if (events & ADAPTER_SOCK_WRITE) {
		pr_debug("Connected.\n");

		adapter_socket_connected(ms);

		mvbs_tcp_connected(adapter_socket_get_index(ms));

		return ;
	}

	if (events & ADAPTER_SOCK_READ) {
		ret = recv(fd, buffer, sizeof(buffer), 0);
		if (ret == 0) {
			pr_debug("server closed connection.\n");

			mvbs_net_event_handler(adapter_socket_get_index(ms), MVBS_NET_EV_TCP_FIN_RECEIVED);
		} else {
			(void)mvbs_net_rx_indication(adapter_socket_get_index(ms),
						     (uint8_t *)buffer, ret,
						     ip_src.sin_addr.s_addr,
						     ip_src.sin_port);
		}
	}
}

mvbs_net_err_t mvbs_tcp_connect(mvbs_socket_id_t socket_id, uint32_t ipv4_addr,
							     uint16_t port)
{
	struct adapter_socket *ms;
	struct sockaddr_in server;
	int32_t ret;

	ms = adapter_socket_get(socket_id);

	server.sin_addr.s_addr	= ipv4_addr;
	server.sin_family	= AF_INET;
	server.sin_port		= port;

	ret = adapter_socket_connect(ms, &server, adapter_socket_tcp_connect);
	if (ret < 0 && errno != EINPROGRESS) {
		perror("connect");
		return MVBS_NET_ERR_CONN;
	}

	return MVBS_NET_E_OK;
}

mvbs_net_err_t mvbs_tcp_send(mvbs_socket_id_t socket_id, void *buff, uint16_t len)
{
	sock_fd_t fd;
	int ret;

	if (!buff)
		return MVBS_NET_ERR_INVPARAM;

	fd = adapter_socket_fd(socket_id);
	if (sock_fd_is_invalid(fd))
		return MVBS_NET_ERR_INVPARAM;

	ret = send(fd, (void *)buff, len, 0);
	if (ret < 0) {
		pr_err(ERR_SEND, "failed!: %s", strerror(errno));
		return MVBS_NET_ERR_TRANSDATA;
	}

	return MVBS_NET_E_OK;
}

mvbs_net_err_t mvbs_tcp_received(mvbs_socket_id_t socket_id, uint16_t len)
{
	(void)socket_id;
	(void)len;

	return MVBS_NET_E_OK;
}
