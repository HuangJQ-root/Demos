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

#ifndef MVBS_CORE_QOS_E2E_COMMON_H
#define MVBS_CORE_QOS_E2E_COMMON_H

#include <mvbs/base_type.h>
#include <core/core.h>

typedef enum appIdType {
	READERID	= 1,
	DATAID		= 2
} appIdType;

uint32_t e2e_calculate_crc32P4(const uint8_t* data_ptr,
				uint32_t data_length,
				const rtps_entity_id_t *reader_id,
				const rtps_entity_id_t *writer_id,
				struct rtps_sn *sn);

uint32_t e2e_do_checkP04(const struct e2e_header *header_src,
			 const uint8_t *pdata,
			 rtps_entity_id_t *reader_id,
			 rtps_entity_id_t *writer_id, struct rtps_sn *sn,
			 struct e2e_p04_cfg profile04_cfg, uint16_t data_size);

void e2e_increment_counter(uint16_t *counter);

void e2e_check_counter(struct reader *r, struct reader_cache_change *rcc,
			struct writer_proxy *wproxy);
#endif
