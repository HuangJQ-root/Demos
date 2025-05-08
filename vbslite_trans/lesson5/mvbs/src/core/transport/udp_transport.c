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

#include <core/core.h>
#include <mvbs/errno.h>
#include <mvbs/base_type.h>
#include <mvbs/utils/mm.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/log.h>
#include <mvbs/utils/tracepoint.h>
#include <mvbs/rtps/locator.h>
#include <mvbs/rtps/message.h>
#include <mvbs/adapter/adapter.h>
#include <mvbs/core/netio/socket.h>
#include <mvbs/core/netio/udp.h>

/* 239.255.0.1 --> 0xEF, 0xFF, 0x00, 0x01 */
static const uint8_t  mulicast_ip[4] = {239, 255, 0, 1};
static const uint32_t mulicast_ip_uint32_le = 0x0100FFEF;

static inline struct udp_rx_buffer *ptcp_get_udp_ringbuf(struct participant *ptcp)
{
	struct udp_transport	*trans = NULL;

	trans = (struct udp_transport *)ptcp->ptransport;

	return &trans->ringbuf_udp;
}

uint32_t mvbs_udp_rx_buffer_unuse_size(struct participant *ptcp)
{
	if (ptcp == NULL)
		return 0;

	return udp_rx_buffer_unused(ptcp_get_udp_ringbuf(ptcp));
}

uint32_t mvbs_udp_rx_buffer_pkg_cnt(struct participant *ptcp)
{
	if (ptcp == NULL)
		return 0;

	return udp_rx_buffer_get_pkg_count(ptcp_get_udp_ringbuf(ptcp));
}

uint32_t mvbs_udp_rx_buffer_cur_usage_rate(struct participant *ptcp)
{
	if (ptcp == NULL)
		return 0;

	return udp_rx_buffer_usage_rate(ptcp_get_udp_ringbuf(ptcp));
}

uint32_t mvbs_udp_rx_buffer_max_usage_rate(struct participant *ptcp)
{
	struct udp_transport	*trans = NULL;

	if (ptcp == NULL)
		return 0;

	trans = (struct udp_transport *)ptcp->ptransport;

	return trans->max_rate_udp_buf;
}

void mvbs_udp_rx_buffer_max_usage_rate_update(struct participant *ptcp)
{
	struct udp_transport	*trans = NULL;

	if (ptcp == NULL)
		return ;

	int32_t rate = mvbs_udp_rx_buffer_cur_usage_rate(ptcp);

	trans = (struct udp_transport *)ptcp->ptransport;

	if (trans->max_rate_udp_buf < rate) {
		trans->max_rate_udp_buf = rate;
	}
}

extern void transport_local_create(struct udp_transport *trans,
				struct participant *ptcp,
				const struct transport_info *trans_info,
				transport_rx_cb fn);

extern int32_t local_trans_send(struct udp_transport *trans,
				const void *buf,
				size_t length);

extern void local_trans_recv_handle(struct transport *this,
					uint32_t recv_max_pkg);


static inline int32_t udp_trans_get_meta_mc_loc(struct udp_transport *trans,
						locator_t *loc)
{
        mvbs_memcpy(loc->ipv4_addr, mulicast_ip, 4);
        loc->port = rtps_get_meta_multicast_port(trans->domain_id);
        loc->kind = (uint16_t)LOCATOR_KIND_UDPv4;

        return 0;
}

static inline int32_t udp_trans_get_meta_uc_loc(struct udp_transport *trans,
						locator_t *loc,
						uint16_t link_idx)
{
	const struct udp_info		*info;

	info = trans->cfg_udp->info + link_idx;

	mvbs_memcpy(loc->ipv4_addr, info->addr, 4);
	loc->port = rtps_get_meta_unicast_port(trans->domain_id, trans->ptcp_id);
	loc->kind = (uint16_t)LOCATOR_KIND_UDPv4;

        return 0;
}

static inline int32_t udp_trans_get_user_uc_loc(struct udp_transport *trans,
						locator_t *loc,
						uint16_t link_idx)
{
	const struct udp_info		*info;

	info = trans->cfg_udp->info + link_idx;

	mvbs_memcpy(loc->ipv4_addr, info->addr, 4);
	loc->port = rtps_get_user_unicast_port(trans->domain_id, trans->ptcp_id);
	loc->kind = (uint16_t)LOCATOR_KIND_UDPv4;

        return 0;
}

static inline int32_t udp_trans_get_locator(struct udp_transport *trans,
						int32_t sockfd, locator_t *loc)
{
	const struct udp_rtps_link	*link;
	const struct udp_info		*info;

	for (uint16_t i = 0; i < trans->cfg_udp->info_cnt; i++) {
		link = trans->links + i;
		info = trans->cfg_udp->info + i;

		if (sockfd == link->sock_user_uc) {
			mvbs_memcpy(loc->ipv4_addr, info->addr, 4);
			loc->port      = rtps_get_user_unicast_port(trans->domain_id, trans->ptcp_id);
			loc->kind      = (uint16_t)LOCATOR_KIND_UDPv4;

			return 0;
		}

		if (sockfd == link->sock_meta_uc) {
			mvbs_memcpy(loc->ipv4_addr, info->addr, 4);
			loc->port      = rtps_get_meta_unicast_port(trans->domain_id, trans->ptcp_id);
			loc->kind      = (uint16_t)LOCATOR_KIND_UDPv4;

			return 0;
		}

		if (sockfd == link->sock_meta_mc) {
			mvbs_memcpy(loc->ipv4_addr, mulicast_ip, 4);
			loc->port      = rtps_get_meta_multicast_port(trans->domain_id);
			loc->kind      = (uint16_t)LOCATOR_KIND_UDPv4;

			return 0;
		}
	}

	return -ERR_NOENT;
}

static bool udp_trans_check_rtps_package(int32_t sockfd, char *buf, size_t len)
{
	(void)sockfd;
	(void)len;

	if (mvbs_strncmp(buf, "RTPS", 4) == 0) {
		return false;
	}

	return true;
}

static int32_t udp_trans_setup_buffer(struct udp_transport *udp_trans)
{
	const struct trans_buf_info *info_ring = &udp_trans->cfg_udp->buf_info;
	const struct trans_buf_info *info_tx = &udp_trans->cfg_udp->tx_buf;
	const struct trans_buf_info *info_rx = &udp_trans->cfg_udp->rx_buf;

	int32_t ret;

	mcdr_init_buffer(&udp_trans->cdr, info_tx->buffer, info_tx->buffer_size);

	udp_trans->recv_buff = info_rx->buffer;
	udp_trans->recv_size = info_rx->buffer_size;

	ret = udp_rx_buffer_init(&udp_trans->ringbuf_udp,
				info_ring->buffer, info_ring->buffer_size);

	return ret;
}

static void udp_trans_recv_indication(int32_t sockfd, void *buf, size_t len,
				      uint32_t src_addr, uint16_t src_port,
				      void *priv)
{
	(void)src_addr;
	(void)src_port;

	struct udp_transport *trans = priv;

	int32_t ret = 0;

	CHECKPOINT_LABEL("RX_INDICATION_START");

	if (udp_trans_check_rtps_package(sockfd, (char *)buf, len)) {
		CHECKPOINT_LABEL("RX_INDICATION_END");
		return;
	}

	ret = udp_rx_buffer_put_pkg(&trans->ringbuf_udp, sockfd, buf, len);
	if (ret != 0) {
		pr_err(ret, "UDP: udp_rx_buffer_put_pkg returns: %d, len=%d",
								   ret, len);
	}

	pr_verb("UDP RX ringbuffer: pkg: %d, recv: %d, buffer: %d",
				trans->ringbuf_udp.pkg_cnt,
				trans->ringbuf_udp.recv_cnt,
				udp_rx_buffer_len(&trans->ringbuf_udp));

	CHECKPOINT_LABEL("RX_INDICATION_END");
}

static const struct mvbs_socket_ops rtps_recv_callbks = {
	.rx_indication = udp_trans_recv_indication,
};

static int32_t udp_trans_init_socket(uint32_t ipv4_addr, uint16_t port, void *priv)
{
	int32_t socket_fd;
	int32_t ret;

	socket_fd = mvbs_udp_socket_open();
	if (socket_fd < 0) {
		pr_err(socket_fd, "create socket fail!");
		return -ERR_INVALID;	/* FIXME */
	}

	ret = mvbs_socket_setup_ops(socket_fd, &rtps_recv_callbks, priv);
	if (ret < 0) {
		pr_err(socket_fd, "set socket callback fail!");

		goto ERROR;
	}

	if (rtps_port_is_meta_multicast(port)) {
		ret = mvbs_udp_socket_bind_multicast(socket_fd,
				mulicast_ip_uint32_le, ipv4_addr, port);
	} else {
		ret = mvbs_udp_socket_bind(socket_fd, ipv4_addr, port);
	}

	if (ret < 0) {
		pr_info("socket bind port[%d] no success!", port);

		goto ERROR;
	}

	return socket_fd;

ERROR:
	mvbs_udp_socket_close(socket_fd);

	return ret;
}

static int32_t udp_trans_single_link_create(struct udp_transport *trans,
					 uint8_t domainid, uint8_t ptcp_id,
					 uint16_t link_idx)
{
	struct udp_rtps_link	*link;
	uint32_t		ipv4_addr;
	uint16_t		port;
	uint16_t		i = 0;


	link		= trans->links + link_idx;
	ipv4_addr	= trans->cfg_udp->info[link_idx].addr_uint32_le;

	/* 1. meta multicast */
	port = rtps_get_meta_multicast_port(domainid);
	link->sock_meta_mc = udp_trans_init_socket(ipv4_addr, port, trans);
	if (link->sock_meta_mc < 0) {
		return -ERR_FAULT;	/* FIXME */
	}

	/* 2. user locator */
	while (i < PARTICIPANT_ID_MAX) {
		i++;

		if (ptcp_id == PARTICIPANT_ID_MAX) {
			ptcp_id = 0;
		}

		/* 2.1 meta unicast */
		port = rtps_get_meta_unicast_port(domainid, ptcp_id);
		link->sock_meta_uc = udp_trans_init_socket(ipv4_addr, port, trans);
		if (link->sock_meta_uc < 0) {
			ptcp_id++;

			continue;
		}

		/* 2.2 user unicast */
		port = rtps_get_user_unicast_port(domainid, ptcp_id);
		link->sock_user_uc = udp_trans_init_socket(ipv4_addr, port, trans);
		if (link->sock_user_uc < 0) {
			mvbs_udp_socket_close(link->sock_meta_uc);

			ptcp_id++;

			continue;
		}

		return (int32_t)ptcp_id;
	}

	if (i >= PARTICIPANT_ID_MAX) {
		pr_err(ERR_BIND, "No available ports!");
	}

	mvbs_udp_socket_close(link->sock_meta_mc);

	return -ERR_FAULT;	/* FIXME */
}

static int32_t udp_trans_link_create(struct udp_transport *trans,
				     uint8_t domainid, uint8_t ptcp_id)
{
	int32_t	 ret;
	uint16_t link_idx;
	uint8_t  id = ptcp_id;

	if (trans == NULL) {
		return -ERR_INVALID;
	}

	for (link_idx=0; link_idx < trans->cfg_udp->info_cnt; link_idx++) {
		ret = udp_trans_single_link_create(trans, domainid, id, link_idx);

		if (ret < 0) {
			return -ERR_FAULT; /* FIXME */
		}

		id = (uint8_t)ret;
	}

	return (int32_t)id;
}

static void udp_trans_link_destory(struct udp_transport *trans)
{
	struct udp_rtps_link	*link;
	uint16_t i;

	if (trans == NULL) {
		return ;
	}

	for (i= 0; i<trans->cfg_udp->info_cnt; i++) {
		link = trans->links + i;

		mvbs_udp_socket_close(link->sock_meta_mc);
		mvbs_udp_socket_close(link->sock_meta_uc);
		mvbs_udp_socket_close(link->sock_user_uc);
	}
}

static int32_t udp_trans_send(struct udp_transport *trans, locator_t *loc,
					  const void *buffer, size_t len)
{
	uint32_t dest_addr;
	uint16_t dest_port;
	int32_t fd;
	int32_t ret = -ERR_INVALID;

	if ((trans == NULL) || (loc == NULL)
			    || (buffer == NULL) || (len <= 0U)) {
		return -ERR_INVALID;
	}

	dest_addr = locator_get_ipv4_addr(loc);
	dest_port = loc->port;

	if (rtps_port_is_meta_multicast(dest_port)) {
		int32_t ret_b;
		for (uint16_t i = 0; i < trans->cfg_udp->info_cnt; i++) {
			fd = trans->links[i].sock_meta_mc;

			ret_b = mvbs_udp_socket_sendto(fd, buffer, len,
						       dest_addr,
						       mvbs_htons(dest_port));
			if (ret_b >= 0) {
				ret = 0;
			}
		}
	} else {
		fd = trans->links[0].sock_user_uc; /* FIXME */

		ret = mvbs_udp_socket_sendto(fd, buffer, len, dest_addr,
					     mvbs_htons(dest_port));
	}

	if (ret < 0) {
		return -ERR_SEND;
	}

	return 0;
}

static int32_t udp_trans_recv(struct udp_transport *trans, uint8_t *buffer,
					size_t max_size, locator_t *dst)
{
	int32_t len		= 0;
	int32_t ret		= 0;
	uint8_t sockfd		= 0U;

	while (mvbs_true) {
		len = udp_rx_buffer_get_pkg(&trans->ringbuf_udp, &sockfd,
							buffer, max_size);
		if (len <= 0) {
			break;
		}

		ret = udp_trans_get_locator(trans, (int32_t)sockfd, dst);
		if (ret < 0) {
			continue;
		}

		return len;
	}

	return len;
}

static struct mvbs_cdr *udp_trans_get_tx_buffer(struct transport *this)
{
	struct udp_transport *udp_trans;

	if (this == NULL) {
		return NULL;
	}

	udp_trans = container_of(this, struct udp_transport, ops);

	return &udp_trans->cdr;
}

static int32_t udp_trans_sendto(struct transport *this, locator_t *dst,
					const void *buf, size_t length)
{
	struct udp_transport *udp_trans;

	if (this == NULL) {
		return -ERR_INVALID;
	}

	udp_trans = container_of(this, struct udp_transport, ops);

	if (dst->kind == (uint16_t)LOCATOR_KIND_LOCAL) {
		return local_trans_send(udp_trans, buf, length);
	} else {
		return udp_trans_send(udp_trans, dst, buf, length);
	}
}

static void udp_trans_recv_handle(struct transport *this, uint32_t recv_max_pkg)
{
	struct udp_transport	*trans;
	locator_t		loc;

	int32_t package_number 	= 0;
	int32_t ret		= 0;
	uint32_t i = 0;

	if (this == NULL) {
		pr_err(ERR_INVALID, "The param transport is null!\n");

		return;
	}

	trans = container_of(this, struct udp_transport, ops);

	CHECKPOINT_LABEL("RX_THREAD_START");

	local_trans_recv_handle(this, 0);

	if (recv_max_pkg == 0) {
		while (mvbs_true) {
			ret = udp_trans_recv(trans, trans->recv_buff,
							trans->recv_size, &loc);
			if (ret < 0) {
				break;
			}

			package_number++;

			trans->recv_callback(trans->ptcp,
					     trans->recv_buff, ret, &loc);
		}
	} else {
		for (i = 0; i < recv_max_pkg; i++) {
			ret = udp_trans_recv(trans, trans->recv_buff,
							trans->recv_size, &loc);
			if (ret < 0) {
				break;
			}

			package_number++;

			trans->recv_callback(trans->ptcp,
					     trans->recv_buff, ret, &loc);
		}
	}

	CHECKPOINT_LABEL("RX_THREAD_END");
	pr_debug("%d udp packages has been handled.", package_number);

	return;
}

static int32_t udp_trans_serialize_locator(struct transport *this,
		mvbs_cdr_t *cdr, const endpoint_attr_t *attr, uint16_t pid)
{
	struct udp_transport *trans;
	locator_t	loc;
	uint32_t	idx;

	if (this == NULL) {
		return -ERR_INVALID;
	}

	trans = container_of(this, struct udp_transport, ops);

	switch (pid) {
	/* EDP */
	case PID_UNICAST_LOCATOR:
	case PID_MULTICAST_LOCATOR:	/* Not Support */
		if (attr == NULL) {
			return -ERR_INVALID;
		}

		if (!attr->backup_enabled) {
			udp_trans_get_user_uc_loc(trans, &loc,
						  attr->locator_selector);

			(void)cdr_serialize_locator(cdr, &loc, pid);

			break;
		}

		for (idx = 0; idx < trans->cfg_udp->info_cnt; idx++) {
			udp_trans_get_user_uc_loc(trans, &loc, idx);

			(void)cdr_serialize_locator(cdr, &loc, pid);
		}

		break;

	/* PDP */
	case PID_DEFAULT_UNICAST_LOCATOR:
		for (idx = 0; idx < trans->cfg_udp->info_cnt; idx++) {
			udp_trans_get_user_uc_loc(trans, &loc, idx);

			(void)cdr_serialize_locator(cdr, &loc, pid);
		}

		break;

	case PID_METATRAFFIC_UNICAST_LOCATOR:
		for (idx = 0; idx < trans->cfg_udp->info_cnt; idx++) {
			udp_trans_get_meta_uc_loc(trans, &loc, idx);

			(void)cdr_serialize_locator(cdr, &loc, pid);
		}

		break;

	case PID_DEFAULT_MULTICAST_LOCATOR:	/* Not Support */
	case PID_METATRAFFIC_MULTICAST_LOCATOR:
		udp_trans_get_meta_mc_loc(trans, &loc);

		(void)cdr_serialize_locator(cdr, &loc, pid);
		break;

	default:
		return -ERR_INVALID;
	}

        if (mcdr_buffer_has_error(cdr)) {
		return -ERR_NOMEM;
        }

        return 0;
}

static bool udp_trans_detect_master_link(struct transport *this,
					     locator_t *loc)
{
	struct udp_transport *udp_trans;
	uint32_t ip;
	uint32_t subnet;

	if (this == NULL) {
		return false;
	}

	if (loc == NULL) {
		return false;
	}

	udp_trans = container_of(this, struct udp_transport, ops);

	if (loc->kind != (uint16_t)LOCATOR_KIND_UDPv4) {
		return false;
	}

	const struct udp_info *info = udp_trans->cfg_udp->info;

	ip     = locator_get_ipv4_addr(loc);
	subnet = info[0].addr_uint32_le & info[0].mask_uint32_le;

	return (ip & info[0].mask_uint32_le) == subnet;
}

static int32_t udp_trans_detect_reachable(struct transport *this,
					      locator_t *loc)
{
	struct udp_transport	*udp_trans;
	const struct udp_info	*info;

	uint32_t ip;
	uint32_t subnet;

	if (this == NULL) {
		return -ERR_INVALID;
	}

	if (loc == NULL) {
		return -ERR_INVALID;
	}

	udp_trans = container_of(this, struct udp_transport, ops);

	if (loc->kind != (uint16_t)LOCATOR_KIND_UDPv4) {
		return false;
	}

	ip = locator_get_ipv4_addr(loc);

	if (ip == mulicast_ip_uint32_le) {
		return 0;
	}

	for (uint16_t i=0; i<udp_trans->cfg_udp->info_cnt; i++) {
		info = &udp_trans->cfg_udp->info[i];

		subnet = info->addr_uint32_le & info->mask_uint32_le;

		if ((ip & info->mask_uint32_le) == subnet) {
			return i+1;
		}
	}

	return -ERR_NOENT;
}

static void udp_trans_deinit(struct udp_transport *trans)
{
	udp_trans_link_destory(trans);
}

static void udp_trans_destroy(struct transport *this)
{
	struct udp_transport *udp_trans;

	if (this == NULL) {
		return;
	}

	udp_trans = container_of(this, struct udp_transport, ops);

	udp_trans_deinit(udp_trans);
}

static void udp_trans_setup_ops(struct udp_transport *udp_trans,
					transport_rx_cb fn, void *args)
{
	udp_trans->ops.get_tx_buffer	  = udp_trans_get_tx_buffer;
	udp_trans->ops.sendto		  = udp_trans_sendto;
	udp_trans->ops.recv 		  = udp_trans_recv_handle;
	udp_trans->ops.serialize_locator  = udp_trans_serialize_locator;
	udp_trans->ops.detect_master_link = udp_trans_detect_master_link;
	udp_trans->ops.detect_reachable   = udp_trans_detect_reachable;
	udp_trans->ops.destroy		  = udp_trans_destroy;

	udp_trans->recv_callback	  = fn;
	udp_trans->ptcp		  = args;
}

#pragma weak udp_trans_setup_cfg
void udp_trans_setup_cfg(struct udp_transport *trans,
				const struct transport_info *trans_info)
{
	const struct transport_info_udp	*udp_info;

	udp_info	 = trans_info->udp;

	trans->cfg_udp	 = udp_info;
	trans->cfg_local = trans_info->local_comm;
}

static int32_t udp_trans_init(struct udp_transport *trans,
				const struct transport_info *trans_info,
				uint8_t domainid, uint8_t *ptcp_id,
				transport_rx_cb fn, void *args)
{
	int32_t		ret = 0;
	uint8_t		id = 0U;

	mvbs_memzero(trans, sizeof(*trans));

	udp_trans_setup_cfg(trans, trans_info);

	ret = udp_trans_setup_buffer(trans);
	if (ret != 0) {
		pr_err(ret, "Failed to init UDP ring buffer.");
		goto FAIL;
	}

	udp_trans_setup_ops(trans, fn, args);

	if (ptcp_id != NULL) {
		id = *ptcp_id;
	}

	ret = udp_trans_link_create(trans, domainid, id);
	if (ret < 0) {
		pr_err(ERR_FAULT, "Fail to create mvbs rtps link.");

		goto FAIL;
	}

	trans->domain_id = domainid;
	trans->ptcp_id   = (uint8_t)ret;

	pr_debug("This participant: domain id:%d, ptcp id: %d",
					trans->domain_id, trans->ptcp_id);

	if (ptcp_id != NULL) {
		*ptcp_id = trans->ptcp_id;
	}

	return 0;

FAIL:
	udp_trans_deinit(trans);

	return -ERR_FAULT;
}

struct transport *transport_udp_create(struct participant *ptcp,
				       const struct transport_info *trans_info,
				       transport_rx_cb fn)
{
	struct udp_transport	*trans = NULL;
	int32_t			ret;

	if (trans_info->udp->info_cnt == 0U) {
		pr_err(ERR_INVALID, "Invalid locator setting...");
		return NULL;
	}

	trans = (struct udp_transport *)ptcp->ptransport;

	ret = udp_trans_init(trans, trans_info, ptcp->attr->domain_id,
							&ptcp->id, fn, ptcp);
	if (ret < 0) {
		return NULL;
	}

	transport_local_create(trans, ptcp, trans_info, fn);

	return &trans->ops;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
