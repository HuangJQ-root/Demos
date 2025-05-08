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

#ifndef MVBS_CORE_NETIO_SOCKET_H
#define MVBS_CORE_NETIO_SOCKET_H

#include <mvbs/base_type.h>
#include <mvbs/utils/rx_buffer.h>
#include <mvbs/core/netio/utils.h>
#include <mvbs/adapter/adapter.h>

#ifndef TEST_NETIO_STACK
#define TEST_NETIO_STACK			0
#endif

struct mvbs_socket_ops {
	void (*rx_indication)(int32_t sockfd, void *buf, size_t len,
			      uint32_t src_addr, uint16_t src_port, void *priv);
	void (*event)(int32_t sockfd, mvbs_net_event_t event);
};

typedef struct {
	mvbs_socket_id_t		id;
	struct tcpip_rx_buffer		rx_buffer;
	const struct mvbs_socket_ops	*ops;
	void				*priv;
} mvbs_socket_t;

int32_t mvbs_netio_init(void);

mvbs_socket_t *mvbs_socket_alloc(mvbs_socket_id_t socket_id);

mvbs_socket_t *mvbs_socket_get(mvbs_socket_id_t socket_id);;

void mvbs_socket_free(mvbs_socket_id_t socket_id);

int32_t mvbs_socket(uint16_t Domain, uint8_t Protocol);

int32_t mvbs_socket_setup_ops(int32_t sockfd, const struct mvbs_socket_ops *ops,
			      void *priv);

int32_t mvbs_socket_setup_rx_buffer(int32_t sockfd, void *buffer, uint32_t length);

#endif
