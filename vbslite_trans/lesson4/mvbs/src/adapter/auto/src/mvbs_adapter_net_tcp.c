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

#include <mvbs_adapter.h>

mvbs_net_err_t mvbs_tcp_socket_create(mvbs_socket_id_t *socket_id)
{
	uint8_t ret_val		= E_NOT_OK;
	uint32_t buf_size	= 0;

	if (socket_id == NULL) {
		return MVBS_NET_ERR_INVPARAM;
	}

	ret_val = mvbs_GetSocket(AF_INET, TCPIP_IPPROTO_TCP, socket_id);
	if (ret_val != E_OK) {
		return MVBS_NET_ERR_MEM;
	}

	buf_size = MVBS_TCP_RXBUFSIZE;
	ret_val = TcpIp_ChangeParameter(*socket_id, TCPIP_PARAMID_TCP_RXWND_MAX, (uint8_t *)&buf_size);
	if (ret_val != E_OK) {
		return MVBS_NET_ERR_MEM;
	}

	buf_size = MVBS_TCP_TXBUFSIZE;
	ret_val = TcpIp_ChangeParameter(*socket_id, TCPIP_PARAMID_V_TCP_TXBUFSIZE, (uint8_t *)&buf_size);
	if (ret_val != E_OK) {
		return MVBS_NET_ERR_MEM;
	}

	return MVBS_NET_E_OK;
}

mvbs_net_err_t mvbs_tcp_bind(mvbs_socket_id_t socket_id, uint32_t ipv4_addr,
							  uint16_t port)
{
	(void)ipv4_addr;

	uint8_t ret_val		= E_NOT_OK;
	uint16_t Port		= port;
	uint8_t local_addr_id	= autosar_get_any_addr_id();

	ret_val = TcpIp_Bind(socket_id, local_addr_id, &Port);
	if (ret_val != E_OK) {
		return MVBS_NET_ERR_INVPARAM;
	}

	return MVBS_NET_E_OK;
}

mvbs_net_err_t mvbs_tcp_listen(mvbs_socket_id_t socket_id, uint16_t max_chans)
{
	uint8_t ret_val	= E_NOT_OK;

	ret_val = TcpIp_TcpListen(socket_id, max_chans);
	if (ret_val != E_OK) {
		return MVBS_NET_ERR_INVPARAM;
	}

	return MVBS_NET_E_OK;
}

mvbs_net_err_t mvbs_tcp_connect(mvbs_socket_id_t socket_id, uint32_t ipv4_addr,
							     uint16_t port)
{
	uint8_t ret_val	= E_NOT_OK;
	DDS_TcpIp_SockAddrInetType remote_addr;

	remote_addr.domain	= AF_INET;
	remote_addr.port	= port;
	remote_addr.addr[0]	= ipv4_addr;

	ret_val = TcpIp_TcpConnect(socket_id, (DDS_TcpIp_SockAddrInetType *)&remote_addr);
	if (ret_val != E_OK) {
		return MVBS_NET_ERR_CONN;
	}

	return MVBS_NET_E_OK;
}

mvbs_net_err_t mvbs_tcp_send(mvbs_socket_id_t socket_id, void *buff, uint16_t len)
{
	uint8_t ret_val	= E_NOT_OK;

	if (buff == NULL) {
		return MVBS_NET_ERR_INVPARAM;
	}

	/*ForceRetrieve is only valid if DataPtr is a NULL_PTR*/
	ret_val = TcpIp_TcpTransmit(socket_id, (uint8_t *)buff, len, (dds_boolean)TRUE);
	if (ret_val != E_OK) {
		return MVBS_NET_ERR_TRANSDATA;
	}

	return MVBS_NET_E_OK;
}

mvbs_net_err_t mvbs_tcp_received(mvbs_socket_id_t socket_id, uint16_t len)
{
	uint8_t ret_val	= E_NOT_OK;

	ret_val = TcpIp_TcpReceived(socket_id, len);
	if (ret_val != E_OK) {
		return MVBS_NET_ERR_OVERLEN;
	}

	return MVBS_NET_E_OK;
}

uint8_t mvbs_TcpAccepted(mvbs_socket_id_t SocketId, mvbs_socket_id_t SocketIdConnected,
			 DDS_TcpIp_SockAddrType * RemoteAddrPtr)
{
	DDS_TcpIp_SockAddrInetType *remote_address = (DDS_TcpIp_SockAddrInetType*)RemoteAddrPtr;
	uint32_t ip_address = remote_address->addr[0];
	uint32_t port = remote_address->port;

	return mvbs_tcp_accepted(SocketId, SocketIdConnected, ip_address, port);
}

void mvbs_TcpIpEvent(mvbs_socket_id_t SocketId, uint8_t Event)
{
	int8_t invalid = 0;
	mvbs_net_event_t event;

	switch (Event) {
		case TCPIP_TCP_CLOSED:
			event = MVBS_NET_EV_SOCK_CLOSED;
			break;
		case TCPIP_TCP_FIN_RECEIVED:
			event = MVBS_NET_EV_TCP_FIN_RECEIVED;
			break;
		case TCPIP_TCP_RESET:
			event = MVBS_NET_EV_TCP_RESET;
			break;
		default:
			invalid = 1;
			break;
	}

	if (invalid == 1) {
		return;
	}

	mvbs_net_event_handler(SocketId, event);
}

void mvbs_TcpConnected(mvbs_socket_id_t SocketId)
{
	mvbs_tcp_connected(SocketId);
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
