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

#include <mvbs/base_type.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/log.h>
#include <mvbs/utils/mm_stat.h>

#ifdef MEMORY_ALLOC_STAT
struct dynamic_mem {
	size_t alloc_cnt;
	size_t free_cnt;

	size_t max_block_size;

	size_t cur_used_size;
	size_t max_used_size;
};

static struct dynamic_mem dynamic_mem_info = {
	.alloc_cnt	= 0,
	.free_cnt	= 0,
	.max_block_size	= 0,
	.cur_used_size	= 0,
	.max_used_size	= 0,
};

void dynamic_mem_info_update(bool alloc, size_t size)
{
	if (alloc) {
		dynamic_mem_info.alloc_cnt++;
		dynamic_mem_info.cur_used_size += size;

		if (dynamic_mem_info.max_block_size < size) {
			dynamic_mem_info.max_block_size = size;
		}

		if (dynamic_mem_info.max_used_size < dynamic_mem_info.cur_used_size) {
			dynamic_mem_info.max_used_size = dynamic_mem_info.cur_used_size;
		}
	} else {
		dynamic_mem_info.free_cnt++;
		dynamic_mem_info.cur_used_size -= size;
	}
}

void dynamic_mem_info_reset(void)
{
	(void)mvbs_memzero(&dynamic_mem_info, sizeof(struct dynamic_mem));
}

void dynamic_mem_info_show(const char *extra_info)
{
	if (extra_info != NULL) {
		pr_info("%s\n", extra_info);
	}

	pr_info("alloc count %d\n", dynamic_mem_info.alloc_cnt);
	pr_info("free  count %d\n", dynamic_mem_info.free_cnt);

	pr_info("max_block_size %dBytes(%dKB), LIMIT %dBytes(%dKB)\n",
		dynamic_mem_info.max_block_size,
		dynamic_mem_info.max_block_size / 1024U,
		0, 0);

	pr_info("cur_used_size %ldBytes(%ldKB), max_used_size %ldBytes(%ldKB), LIMIT %ldBytes(%ldKB)\n\n",
		dynamic_mem_info.cur_used_size,
		dynamic_mem_info.cur_used_size / 1024U,
		dynamic_mem_info.max_used_size,
		dynamic_mem_info.max_used_size / 1024U,
		0L, 0L);
}

/* no lock, just read */
size_t dynamic_mem_get_cur_used(void)
{
	return dynamic_mem_info.cur_used_size;
}

/* no lock, just read */
size_t dynamic_mem_get_max_used(void)
{
	return dynamic_mem_info.max_used_size;

}
#endif

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
