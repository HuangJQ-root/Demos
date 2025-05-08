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

#pragma weak autosar_get_slave_multi_addr_id
int32_t autosar_get_slave_multi_addr_id(void)
{
	return (int32_t)autosar_get_inv_addr_id();
}

mvbs_net_err_t mvbs_udp_socket_create(mvbs_socket_id_t *socket_id)
{
	uint8_t retVal = E_NOT_OK;

	if (socket_id == NULL) {
		return MVBS_NET_ERR_INVPARAM;
	}

	retVal = mvbs_GetSocket((uint16_t)AF_INET, TCPIP_IPPROTO_UDP, socket_id);
	if (retVal != E_OK) {
		return MVBS_NET_ERR_MEM;
	}

	return MVBS_NET_E_OK;
}

mvbs_net_err_t mvbs_udp_bind(mvbs_socket_id_t socket_id, uint32_t ipv4_addr,
				uint16_t port)
{
	(void)ipv4_addr;

	uint8_t ret_val		= E_NOT_OK;
	uint16_t autosar_port	= port;
	uint8_t local_addr_id	= autosar_get_any_addr_id();

	ret_val = TcpIp_Bind(socket_id, local_addr_id, &autosar_port);
	if (ret_val != E_OK) {
		return MVBS_NET_ERR_INVPARAM;
	}

	return MVBS_NET_E_OK;
}

mvbs_net_err_t mvbs_udp_bind_multicast(mvbs_socket_id_t socket_id,
					uint32_t multicast_addr,
					uint32_t ipv4_addr,
					uint16_t port)
{
	(void)multicast_addr;
	(void)ipv4_addr;

	static int32_t id = 0;

	uint16_t autosar_port	= port;
	uint8_t  ret_val	= E_NOT_OK;
	uint8_t  local_addr_id	= autosar_get_any_addr_id();

	if (id == 0) {
		local_addr_id = autosar_get_multi_addr_id();
	} else {
		local_addr_id = autosar_get_slave_multi_addr_id();
	}

	id++;

	if (local_addr_id == autosar_get_inv_addr_id()) {
		return MVBS_NET_ERR_INVPARAM;
	}

	ret_val = TcpIp_Bind(socket_id, local_addr_id, &autosar_port);
	if (ret_val != E_OK) {
		return MVBS_NET_ERR_INVPARAM;
	}

	return MVBS_NET_E_OK;
}

mvbs_net_err_t mvbs_udp_send(mvbs_socket_id_t socket_id, void *buff,
				uint16_t len, uint32_t ipv4_addr, uint16_t port)
{
	uint8_t ret		= E_NOT_OK;
	uint16_t TotalLength	= (uint16_t)len;
	char *DataPtr		= (char*)buff;
	DDS_TcpIp_SockAddrInetType RemoteAddrPtr;

	if (buff == NULL) {
		return MVBS_NET_ERR_INVPARAM;
	}

	RemoteAddrPtr.domain	= AF_INET;
	RemoteAddrPtr.port	= port;
	RemoteAddrPtr.addr[0]	= ipv4_addr;

	ret = TcpIp_UdpTransmit(socket_id, DataPtr,
			(DDS_TcpIp_SockAddrType*)&RemoteAddrPtr, TotalLength);
	if (ret != E_OK) {
		return MVBS_NET_ERR_TRANSDATA;
	}

	return MVBS_NET_E_OK;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
