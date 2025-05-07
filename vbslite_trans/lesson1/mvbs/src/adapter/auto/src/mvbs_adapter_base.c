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

struct mem_region * mvbs_get_heap_info(void)
{
	return autosar_get_heap_region();
}

void mvbs_log_print(uint32_t level, char *buffer)
{
	autosar_log_print(level, buffer);
}

bool mvbs_get_current_time(uint32_t *ts_sec, uint32_t *ts_nsec)
{
	uint8_t ret;
	struct autosar_timestamp current_time;

	if (ts_sec == NULL || ts_nsec == NULL) {
		return false;
	}

	ret = autosar_get_current_time(&current_time);
	if (ret != E_OK) {
		return false;
	}

	*ts_sec		= current_time.ts_sec;
	*ts_nsec	= current_time.ts_nanosec;

	return true;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
