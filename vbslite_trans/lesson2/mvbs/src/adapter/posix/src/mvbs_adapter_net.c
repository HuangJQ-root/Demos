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

#include <mvbs_adapter.h>
#include "adapter_socket.h"

bool mvbs_net_is_ready(uint32_t addr)
{
	(void)addr;

	return true;
}

void mvbs_socket_close(mvbs_socket_id_t socket_id)
{
	struct adapter_socket *ms;

	ms = adapter_socket_get(socket_id);
	if (adapter_socket_is_invalid(ms)) {
		return;
	}

	adapter_socket_free(ms);

	return;
}
