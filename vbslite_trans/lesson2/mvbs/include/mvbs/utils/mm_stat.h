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

#ifndef MVBS_UTILS_MM_STAT_H
#define MVBS_UTILS_MM_STAT_H

#include <mvbs/base_type.h>

#define MEMORY_ALLOC_STAT

#ifdef MEMORY_ALLOC_STAT
void dynamic_mem_info_update(bool alloc, size_t size);
void dynamic_mem_info_reset(void);
void dynamic_mem_info_show(const char *extra_info);
size_t dynamic_mem_get_cur_used(void);
size_t dynamic_mem_get_max_used(void);
#else
static inline void dynamic_mem_info_update(bool alloc, size_t size)
{
	(void)alloc;
	(void)size;
}

static inline void dynamic_mem_info_reset(void)
{

}

static inline void dynamic_mem_info_show(const char *extra_info)
{
	(void)extra_info;
}

static inline size_t dynamic_mem_get_cur_used(void)
{
	return 0;
}

static inline size_t dynamic_mem_get_max_used(void)
{
	return 0;
}

#endif

#endif
