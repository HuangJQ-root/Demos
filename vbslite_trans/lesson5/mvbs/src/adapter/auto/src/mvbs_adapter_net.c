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

bool mvbs_net_is_ready(uint32_t addr)
{
	(void)addr;

	uint8_t master_local_mc_addr_id = (mvbs_socket_id_t)autosar_get_multi_addr_id();

	if(mvbs_TcpIp_GetAssignmentStateOfLocalAddr(master_local_mc_addr_id)
					!= TCPIP_IPADDR_STATE_ASSIGNED) {
		return false;
	}

	return true;
}

void mvbs_socket_close(mvbs_socket_id_t socket_id)
{
	uint8_t ret_val = E_NOT_OK;

	ret_val = TcpIp_Close(socket_id, 0);
	if (ret_val != E_OK) {
		return;
	}
}

/* NOTE: these functions are called in interrupt */

int32_t mvbs_RxIndication(mvbs_socket_id_t SocketId, DDS_TcpIp_SockAddrType * RemoteAddrPtr,
			  uint8_t * BufPtr, uint16_t BufLength)
{
	uint16_t port				= 0;
	uint32_t ipv4_addr			= 0;
	DDS_TcpIp_SockAddrInetType *inetAddrPtr = NULL;

	inetAddrPtr	= (DDS_TcpIp_SockAddrInetType *)RemoteAddrPtr;
	port 		= inetAddrPtr->port;
	ipv4_addr	= inetAddrPtr->addr[0];

	mvbs_net_rx_indication(SocketId, BufPtr, BufLength, ipv4_addr, port);

	return 0;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
