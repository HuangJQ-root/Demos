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

#ifndef MVBS_ADAPTER_IPC_H
#define MVBS_ADAPTER_IPC_H

#include "mvbs_adapter_base.h"

#define MVBS_IPC_J6M_ENABLED

#ifdef MVBS_IPC_J6M_ENABLED

#define MVBS_IPC_J6M_TXBUFSIZE		MVBS_IPC_TXBUFSIZE
#define MVBS_IPC_J6M_RXBUFSIZE		MVBS_IPC_RXBUFSIZE

bool mvbs_ipc_j6m_rx_indication(const uint8_t *buff, uint16_t len);

int32_t mvbs_ipc_j6m_send(void *buff, uint16_t size);

#endif

#endif /* !MVBS_ADAPTER_IPC_H */