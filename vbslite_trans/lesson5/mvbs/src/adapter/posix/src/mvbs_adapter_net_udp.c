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

#include "utils.h"
#include "adapter_socket.h"


static void adapter_socket_udp_read(sock_fd_t fd, short events, struct adapter_socket *ms)
{
	char			buffer[4096];
	struct sockaddr_in	ip_src;
	socklen_t		ip_src_len = sizeof(struct sockaddr);
	int			ret;

	if (! (events & ADAPTER_SOCK_READ))
		return ;

	ret = recvfrom(fd, buffer, sizeof(buffer), 0,
				(struct sockaddr *)&ip_src, &ip_src_len);
	if (ret < 0) {
		pr_info("UDP recvfrom error.\n");
	} else {
		(void)mvbs_net_rx_indication(adapter_socket_get_index(ms),
						(uint8_t *)buffer, ret,
						ip_src.sin_addr.s_addr,
						ip_src.sin_port);
	}
}

mvbs_net_err_t mvbs_udp_socket_create(mvbs_socket_id_t *socket_id)
{
	struct adapter_socket *ms;

	if (socket_id == NULL)
		return MVBS_NET_ERR_INVPARAM;

	ms = adapter_socket_alloc_udp(adapter_socket_udp_read);
	if (ms == NULL) {
		return MVBS_NET_ERR_MEM;
	}

	*socket_id = adapter_socket_get_index(ms);

	return MVBS_NET_E_OK;
}

mvbs_net_err_t mvbs_udp_bind(mvbs_socket_id_t socket_id, uint32_t ipv4_addr,
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
		pr_info("port[%d] %s", port, strerror(errno));
		return MVBS_NET_ERR_INVPARAM;
	}

	adapter_socket_set_port(ms, port);

	return MVBS_NET_E_OK;
}

static struct transport_info_udp	trans_info_udp;

void udp_trans_setup_cfg(struct udp_transport *trans,
				const struct transport_info *trans_info)
{
	const struct udp_info			*udp_info;

	trans_info_udp = *trans_info->udp;

	udp_info = mvbs_get_udp_info_from_env();

	if (udp_info != NULL) {
		trans_info_udp.info_cnt = 1;
		trans_info_udp.info	= udp_info;
	}

	trans->cfg_udp	 = &trans_info_udp;
	trans->cfg_local = trans_info->local_comm;
}

static int set_multicast(sock_fd_t fd, int index)
{
	const struct udp_info *loc_info;
	int	ret;

	loc_info = trans_info_udp.info;

	/* IMPORTANT: enable the reuse */
	int reuse = 1;
	ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
					 (void *)&reuse, sizeof(reuse));
	if (ret) {
		pr_err(ERR_SOCK, "Fail to REUSE ADDR: %d", ret);
		return MVBS_NET_ERR_INVPARAM;
	}

	/* Set the TTL */
	unsigned char ttl = 1;
	ret = setsockopt(fd, IPPROTO_IP, IP_MULTICAST_TTL,
					 (void *)&ttl, sizeof(ttl));
	if (ret) {
		pr_err(ERR_SOCK, "err: %d", ret);
	}

	/*
	 * Enable multicast loop
	 * Note: mvbs wouldn't received multicast message on windows platform
	 * when multicast-loop disabled.
	 */
	unsigned char mc_loop = 1;
	ret = setsockopt(fd, IPPROTO_IP, IP_MULTICAST_LOOP,
					 (void *)&mc_loop, sizeof(mc_loop));
	if (ret) {
		pr_err(ERR_SOCK, "err: %d", ret);
	}

	/* Set multicast packet send interface */
	struct in_addr multicast_if = { 0 };
	multicast_if.s_addr = htonl((uint32_t)loc_info[index].addr[0] << 24 |
				    (uint32_t)loc_info[index].addr[1] << 16 |
				    (uint32_t)loc_info[index].addr[2] << 8 |
				    (uint32_t)loc_info[index].addr[3] << 0);

	ret = setsockopt(fd, IPPROTO_IP, IP_MULTICAST_IF,
				(void *)&multicast_if, sizeof(multicast_if));
	if (ret) {
		pr_err(ERR_SOCK, "err: %d, please fix your host ip[%s] address in xml file.",
		       ret, inet_ntoa(multicast_if));
	}

	pr_info("Send multicast package by: ip[%s]. socket:%d",
						inet_ntoa(multicast_if), fd);

	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr = inet_addr("239.255.0.1");
	mreq.imr_interface.s_addr = htonl((uint32_t)loc_info[index].addr[0] << 24 |
					  (uint32_t)loc_info[index].addr[1] << 16 |
					  (uint32_t)loc_info[index].addr[2] << 8 |
					  (uint32_t)loc_info[index].addr[3]);

	ret = setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&mreq, sizeof(mreq));
	if (ret)
		pr_err(ERR_SOCK, "err: %s", strerror(errno));

	pr_info("Recv multicast package by: ip[%s]. socket:%d",
						inet_ntoa(mreq.imr_interface), fd);

	return 0;
}

mvbs_net_err_t mvbs_udp_bind_multicast(mvbs_socket_id_t socket_id,
					uint32_t multicast_addr,
					uint32_t ipv4_addr,
					uint16_t port)
{
	static int index = 0;
	int  ret;
	sock_fd_t  fd;
	struct adapter_socket *ms;
	struct sockaddr_in addr = { 0 };

	(void)ipv4_addr;
	(void)multicast_addr;

	ms = adapter_socket_get(socket_id);

	fd = adapter_socket_get_fd(ms);
	if (sock_fd_is_invalid(fd))
		return MVBS_NET_ERR_INVPARAM;

	ret = set_multicast(fd, index);
	if (ret) {
		pr_err(ERR_SOCK, "Failed to set multicast!: %s", strerror(errno));
		return MVBS_NET_ERR_INVPARAM;
	}

	index++;

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

mvbs_net_err_t mvbs_udp_send(mvbs_socket_id_t socket_id, void *buff,
				uint16_t len, uint32_t ipv4_addr, uint16_t port)
{
	sock_fd_t fd;
	int ret;
	struct sockaddr_in remote_addr = { 0 };

	if (!buff)
		return MVBS_NET_ERR_INVPARAM;

	fd = adapter_socket_fd(socket_id);

	remote_addr.sin_family		= AF_INET;
	remote_addr.sin_port		= port;
	remote_addr.sin_addr.s_addr	= ipv4_addr;

	ret = sendto(fd, buff, len, MSG_CONFIRM,
		     (const struct sockaddr *)&remote_addr,
		     sizeof(remote_addr));

	pr_verb("socket_id=%d:%d, %s:%d, ret=%d", socket_id, fd,
					       inet_ntoa(remote_addr.sin_addr),
					       ntohs(remote_addr.sin_port),
					       ret);
	if (ret < 0) {
		pr_err(ERR_SEND, "failed!: %s", strerror(errno));
		return MVBS_NET_ERR_TRANSDATA;
	}

	return MVBS_NET_E_OK;
}
