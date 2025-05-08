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

#ifndef MVBS_CORE_TRANSPORT_IPC_H
#define MVBS_CORE_TRANSPORT_IPC_H

#ifdef	__MVBS_CORE_SOURCE__
#include <mvbs/base_type.h>
#include <mvbs/core/transport/transport.h>
#include <mvbs/utils/rx_buffer.h>
#include <mcdr/mcdr.h>

struct ipc_j6m_transport {
	struct transport	ops;

	struct mvbs_cdr		cdr;

	const struct transport_info_ipc_j6m	*cfg;

	struct udp_rx_buffer	rx_ringbuffer;

	locator_t		locator;

	uint8_t			*recv_buff;
	size_t			recv_size;

	transport_rx_cb		recv_callback;
	void			*recv_args;
};

typedef struct ipc_j6m_transport	ipc_j6m_transport_t;

#endif
#endif
