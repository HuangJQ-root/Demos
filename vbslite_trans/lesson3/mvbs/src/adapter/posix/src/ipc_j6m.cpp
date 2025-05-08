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

#ifdef __cplusplus
extern "C" {
#endif

#include <pthread.h>
#include <mvbs/utils/log.h>

#ifdef __cplusplus
};
#endif

#include "ipc_j6m.h"

#ifdef MVBS_IPC_J6M_ENABLE

#include <lihal_ipcf_interface.h>

int32_t j6_ipc_mvbs_sendto(void *buff, uint32_t size)
{
	return lihal_ipcf_vbs_send((const uint8_t *)buff, size);
}

int32_t __attribute__((weak)) j6_ipc_mvbs_rx_indication(const uint8_t* data,
							     uint16_t len)
{
	(void)data;
	(void)len;


	return 0;
}

static void *ipc_recv_loop(void *arg)
{
	static uint8_t buffer[4096];

	int32_t ret;

	(void)arg;

	while(1) {
		ret = lihal_ipcf_vbs_recv(buffer, sizeof(buffer), -1);
		if (ret <= 0) {
			continue;
		}

		j6_ipc_mvbs_rx_indication(buffer, ret);
	}

	lihal_ipcf_vbs_deinit();

	return NULL;
}

static int32_t ipc_init(void)
{
	int32_t ret = 0;

	ret = lihal_ipcf_vbs_init();
	if (ret != 0) {
		pr_err(ERR_FAULT, "Fail to init mvbs IPC j6m.");
	}

	return ret;
}

int32_t j6_ipc_init(void)
{
	int32_t ret;

	pthread_t thd_id;
	pthread_attr_t attr;

	ret = ipc_init();
	if (ret != 0) {
		return -ERR_FAULT;
	}

	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);

	pthread_create(&thd_id, &attr, ipc_recv_loop, NULL);
	pthread_detach(thd_id);

	return 0;
}

#endif
