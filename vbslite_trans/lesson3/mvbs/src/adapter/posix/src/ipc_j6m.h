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

#ifndef MVBS_ADAPTER_IPC_J6M_H
#define MVBS_ADAPTER_IPC_J6M_H

#ifdef __cplusplus
extern "C" {
#endif

#include <mvbs/base_type.h>
#include <mvbs/errno.h>

#ifdef	TARGET_PRODUCT_J6M_ACORE
#define	MVBS_IPC_J6M_ENABLE
#endif

#ifdef MVBS_IPC_J6M_ENABLE

extern int32_t j6_ipc_mvbs_rx_indication(const uint8_t *data, uint16_t len);

extern int32_t j6_ipc_mvbs_sendto(void *buff, uint32_t size);

extern int32_t j6_ipc_init(void);

#else

static inline int32_t j6_ipc_init(void)
{
	return 0;
}

static inline int32_t j6_ipc_mvbs_rx_indication(const uint8_t *data,
						uint16_t len)
{
	(void)data;
	(void)len;

	return 0;
}

static inline int32_t j6_ipc_sendto(void *buff, uint32_t size)
{
	(void)buff;
	(void)size;

	return 0;
}

#endif

#ifdef __cplusplus
}
#endif

#endif


