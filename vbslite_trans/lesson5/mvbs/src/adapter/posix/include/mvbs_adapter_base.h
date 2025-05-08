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

#ifndef MVBS_ADAPTER_BASE_H
#define MVBS_ADAPTER_BASE_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

struct mem_region {
	uint8_t		*mr_start;
	uint32_t	mr_size;
};

struct mem_region * mvbs_get_heap_info(void);

typedef enum {
	MVBS_LOG_LEVEL_DISABLE	= 0,
	MVBS_LOG_LEVEL_FATAL	= 1,
	MVBS_LOG_LEVEL_ERROR	= 2,
	MVBS_LOG_LEVEL_WARN	= 3,
	MVBS_LOG_LEVEL_INFO	= 4,
	MVBS_LOG_LEVEL_DEBUG	= 5,
	MVBS_LOG_LEVEL_VERBOSE	= 6
} mvbs_log_t;

void mvbs_log_print(uint32_t level, char *buffer);

bool mvbs_get_current_time(uint32_t *ts_sec, uint32_t *ts_nsec);

uint64_t mvbs_get_session_id(void);

#endif /* !MVBS_ADAPTER_BASE_H */