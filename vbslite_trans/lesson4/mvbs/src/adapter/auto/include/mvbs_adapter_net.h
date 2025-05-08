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

#ifndef MVBS_ADAPTER_NET_H
#define MVBS_ADAPTER_NET_H

#include "mvbs_adapter_base.h"

typedef enum mvbs_net_err {
	MVBS_NET_E_OK,
	MVBS_NET_ERR_INVPARAM,
	MVBS_NET_ERR_CONN,
	MVBS_NET_ERR_MEM,
	MVBS_NET_ERR_ARPQUERY,
	MVBS_NET_ERR_OVERLEN,
	MVBS_NET_ERR_BUFREQ,
	MVBS_NET_ERR_COPYTXDATA,
	MVBS_NET_ERR_TRANSDATA,
	MVBS_NET_ERR_SNDBUF,
	MVBS_NET_ERR_SNDQUEUE,
	MVBS_NET_ERR_ARPFULL,
	MVBS_NET_ERR_GATWAT,
	MVBS_NET_ERR_OFFLINE,
	TBD,
} mvbs_net_err_t;

bool mvbs_net_is_ready(uint32_t addr);

bool mvbs_net_rx_indication(mvbs_socket_id_t socket_id, uint8_t *buff,
			     uint16_t len, uint32_t ipv4_addr, uint16_t port);


typedef enum mvbs_net_event {
	 MVBS_NET_EV_TCP_RESET,
	 MVBS_NET_EV_SOCK_CLOSED,
	 MVBS_NET_EV_TCP_FIN_RECEIVED,
} mvbs_net_event_t;

void mvbs_net_event_handler(mvbs_socket_id_t socket_id, mvbs_net_event_t event);

#define MVBS_NET_UDP_ENABLED

#ifdef MVBS_NET_UDP_ENABLED

mvbs_net_err_t mvbs_udp_socket_create(mvbs_socket_id_t *socket_id);

mvbs_net_err_t mvbs_udp_send(mvbs_socket_id_t socket_id, void *buff,
				uint16_t len, uint32_t ipv4_addr, uint16_t port);

mvbs_net_err_t mvbs_udp_bind(mvbs_socket_id_t socket_id, uint32_t ipv4_addr,
							uint16_t port);

mvbs_net_err_t mvbs_udp_bind_multicast(mvbs_socket_id_t socket_id,
					uint32_t multicast_addr,
					uint32_t ipv4_addr,
					uint16_t port);
#endif


#define MVBS_NET_TCP_ENABLED

#ifdef MVBS_NET_TCP_ENABLED

mvbs_net_err_t mvbs_tcp_socket_create(mvbs_socket_id_t *socket_id);

mvbs_net_err_t mvbs_tcp_send(mvbs_socket_id_t socket_id, void *buff, uint16_t len);

mvbs_net_err_t mvbs_tcp_received(mvbs_socket_id_t socket_id, uint16_t len);

mvbs_net_err_t mvbs_tcp_bind(mvbs_socket_id_t socket_id, uint32_t ipv4_addr,
							  uint16_t port);

mvbs_net_err_t mvbs_tcp_listen(mvbs_socket_id_t socket_id, uint16_t max_chans);

mvbs_net_err_t mvbs_tcp_connect(mvbs_socket_id_t socket_id, uint32_t ipv4_addr,
							     uint16_t port);


void mvbs_tcp_connected(mvbs_socket_id_t socket_id);

uint8_t mvbs_tcp_accepted(mvbs_socket_id_t socket_id,
			   mvbs_socket_id_t socket_id_connected,
			   uint32_t ipv4_addr, uint16_t port);

#endif

void mvbs_socket_close(mvbs_socket_id_t socket_id);

#endif /* !MVBS_ADAPTER_NET_H */
