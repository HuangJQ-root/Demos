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

#ifndef MVBS_CORE_QOS_E2E_H
#define MVBS_CORE_QOS_E2E_H

#include <mvbs/base_type.h>

enum E2E_P04CheckStatusType {
	E2E_P04STATUS_OK		= 0x00,
	E2E_P04STATUS_NONEWDATA 	= 0x01,
	E2E_P04STATUS_ERROR 		= 0x02,
	E2E_P04STATUS_REPEATED 		= 0x08,
	E2E_P04STATUS_OKSOMELOST 	= 0x20,
	E2E_P04STATUS_WRONGSEQUENCE 	= 0x40,
	E2E_P04STATUS_ERRORADDRESS 	= 0x80,
	E2E_P04STATTUS_NODATAAVAILABLE 	= 0x100
};

struct e2e_header {
	uint16_t	length;
	uint32_t	crc;
	bool		enable;
	bool		first_rcv;
};

struct e2e_p04_cfg {
	uint32_t	data_id;
	uint16_t	min_data_length;
	uint16_t	max_data_length;
	uint16_t	max_delta_counter;
};

#endif
