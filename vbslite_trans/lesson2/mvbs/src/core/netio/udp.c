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

#include <mvbs/rtps/locator.h>
#include <mvbs/utils/rx_buffer.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/log.h>
#include <mvbs/core/netio/socket.h>
#include <mvbs/core/netio/utils.h>
#include <mvbs/core/netio/udp.h>
#include <mvbs/adapter/adapter.h>

static void mvbs_generic_rx_indication(int32_t socket_id, void *buf, size_t len,
				       uint32_t src_addr, uint16_t port,
				       void *priv)
{
	int32_t ret = 0;
	mvbs_socket_t *sock = NULL;

	(void)priv;

	sock = mvbs_socket_get(socket_id);
	if (sock == NULL) {
		pr_warn("sock get fail: %u", socket_id);
		return;
	}

	if (tcpip_rx_buffer_available(&sock->rx_buffer) == 0) {
		return;
	}

	ret = tcpip_rx_buffer_in(&sock->rx_buffer, (uint8_t *)&src_addr,
				 sizeof(src_addr));
	if (ret <= 0) {
		return;
	}

	ret = tcpip_rx_buffer_in(&sock->rx_buffer, (uint8_t *)&port,
				 sizeof(port));
	if (ret <= 0) {
		return;
	}

	ret = tcpip_rx_buffer_in(&sock->rx_buffer, buf, len);
	if (ret <= 0) {
		(void)tcpip_rx_buffer_out(&sock->rx_buffer,
					  (uint8_t *)&src_addr,
					  sizeof(src_addr));
		return;
	}
}

int32_t mvbs_udp_socket_open(void)
{
	static const struct mvbs_socket_ops mvbs_udp_ops = {
		.rx_indication = mvbs_generic_rx_indication,
	};

	int32_t sockfd			= 0;
	mvbs_socket_id_t sock_id	= 0;
	mvbs_net_err_t ret		= MVBS_NET_E_OK;
	mvbs_socket_t *sock		= NULL;

	ret = mvbs_udp_socket_create(&sock_id);
	if (ret != MVBS_NET_E_OK) {
		pr_warn("create udp socket fail, err = %d", (int32_t)ret);
		return -ERR_SOCK;
	}

	sock = mvbs_socket_alloc(sock_id);
	if (sock == NULL) {
		mvbs_socket_close(sock_id);
		return -ERR_NOMEM;
	}

	if (mvbs_socket_setup_ops((int32_t)sock_id, &mvbs_udp_ops, NULL) < 0) {
		mvbs_socket_close(sock_id);
		return -ERR_SOCK;
	}

	sockfd = (int32_t)sock_id;

	return sockfd;
}

int32_t mvbs_udp_socket_close(int32_t sockfd)
{
	mvbs_socket_id_t socket_id = (mvbs_socket_id_t)sockfd;

	mvbs_socket_close(socket_id);

	mvbs_socket_free(socket_id);

	return 0;
}

int32_t mvbs_udp_socket_bind(int32_t sockfd, uint32_t ipv4_addr, uint16_t port)
{
	mvbs_net_err_t ret		= MVBS_NET_E_OK;
	mvbs_socket_id_t socket_id	= (mvbs_socket_id_t)sockfd;

	ret = mvbs_udp_bind(socket_id, ipv4_addr, port);
	if (ret != MVBS_NET_E_OK) {
		return -ERR_BIND;
	}

	return 0;
}

int32_t mvbs_udp_socket_bind_multicast(int32_t sockfd, uint32_t multi_addr,
				       uint32_t ipv4_addr, uint16_t port)
{
	mvbs_net_err_t ret		= MVBS_NET_E_OK;
	mvbs_socket_id_t socket_id	= (mvbs_socket_id_t)sockfd;

	ret = mvbs_udp_bind_multicast(socket_id, multi_addr, ipv4_addr, port);
	if (ret != MVBS_NET_E_OK) {
		pr_warn("tcpip bind fail: %d", ret);
		return -ERR_BIND;
	}

	return 0;
}

int32_t mvbs_udp_socket_sendto(int32_t sockfd, const void *buf, size_t len,
			       uint32_t ipv4_addr, uint16_t port)
{
	char *data			= (char*)buf;
	mvbs_net_err_t ret		= MVBS_NET_E_OK;
	mvbs_socket_id_t socket_id	= (mvbs_socket_id_t)sockfd;

	if (buf == NULL) {
		return -ERR_INVALID;
	}

	udp_transmit_prev_hook();

	ret = mvbs_udp_send(socket_id, data, len, ipv4_addr, port);

	udp_transmit_post_hook();

	pr_debug("[SOCKET%d] >>> [UDP]: [%d]", socket_id, len);

	if (ret != MVBS_NET_E_OK) {
		pr_warn("udp transmit fail: %d, remote address: %08x:%d",
				ret, (uint32_t)ipv4_addr, mvbs_htons(port));
		return -ERR_SEND;
	}

	return (int32_t)len;
}

int32_t mvbs_udp_socket_recvfrom(int32_t sockfd, void *buf, size_t len,
				 uint32_t *src_addr, uint16_t *src_port)
{
	static uint32_t rx_handle_counter = 0;

	(void)src_port;

	mvbs_socket_id_t socket_id = (mvbs_socket_id_t)sockfd;
	mvbs_socket_t *sock = NULL;
	uint32_t ip_address = 0;
	uint16_t port = 0;
	int32_t ret = 0;

	if (buf == NULL) {
		return -ERR_INVALID;
	}

	sock = mvbs_socket_get(socket_id);
	if (sock == NULL) {
		pr_warn("sock get fail: %u", socket_id);
		return -ERR_SOCK;
	}

	if (tcpip_rx_buffer_available(&sock->rx_buffer) == 0) {
		return -ERR_NODATA;
	}

	ret = tcpip_rx_buffer_out(&sock->rx_buffer, (uint8_t *)&ip_address,
				  sizeof(ip_address));
	if (ret <= 0) {
		return ret;
	}

	ret = tcpip_rx_buffer_out(&sock->rx_buffer, (uint8_t *)&port,
				  sizeof(port));
	if (ret <= 0) {
		return ret;
	}

	ret = tcpip_rx_buffer_out(&sock->rx_buffer, buf, len);
	if (ret <= 0) {
		return ret;
	}

	pr_debug("[SOCKET%d] <<< [TCP/UDP]: [%u]", sock->id, ret);

	if (src_addr != NULL) {
		*src_addr = ip_address;
	}

	if (src_port != NULL) {
		*src_port = port;
	}

	rx_handle_counter++;

	pr_debug("rx_handle_counter=%d", rx_handle_counter);

	return ret;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
