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

#ifndef MVBS_UTILS_MM_H
#define MVBS_UTILS_MM_H

#include <mvbs/base_type.h>

/*
 * Save the LOG to the log.txt and run the following command:
 * $ sort -t ',' -k 2 log.txt | awk -F, '{print $1 $2 $3}' | uniq -f 9 -u
 *
 * If there is a memory leak, it shows who is apear the memory leak,
 * where is the leak memory pointer, and how many memory size to leak.
 */
#ifdef MEMORY_ALLOC_LOG
#undef MVBSLOG_LEVEL
#define MVBSLOG_LEVEL	MVBSLOG_DBG
#endif


#include <mvbs/utils/log.h>
#include <mvbs/utils/mm_stat.h>

#define MVBS_MM_ALIGN(x, a)		(((x) + (a)-1U) & ~(((uint32_t)a)-1U))

#define MVBS_MM_ALIGN_DEFAULT		(0)

#define mvbs_allocate_struct(dest_, type_)		\
	(*(dest_) = (type_ *)mvbs_calloc(1, sizeof(type_)))

#define mvbs_free_struct(dest_)		\
	do {				\
		mvbs_free(dest_); 	\
	} while (false)

#define mvbs_allocate_array(dest_, count_, type_) 	\
	(*(dest_) = (type_ *)mvbs_calloc(count_, sizeof(type_)))

#define mvbs_free_array(dest_)		\
	do {				\
		mvbs_free(dest_);	\
	} while (false)

#define mvbs_allocate_string(string_, size_) \
	(*(string_) = (char *)mvbs_calloc((size_) + 1, 1))

#define mvbs_free_string(string_)	\
	do {				\
		mvbs_free(string_);	\
	} while (false)

/**
 * Allocate memory block.
 *
 * @param size the size of the memory block in bytes
 * @param alignment parameter for memory alignment, the default value is MVBS_MM_ALIGN_DEFAULT
 * @return a pointer to the allocated memory if succeed, otherwise NULL
 */
void *__mvbs_malloc(size_t size, uint32_t alignment);

static inline void *mvbs_malloc(size_t size, uint32_t alignment)
{
	void *addr;

	addr = __mvbs_malloc(size, alignment);
	pr_debug("Alloc memory, address = %p, size = %dBytes\n", addr, size);
	return addr;
}

/**
 * Change the size of the memory block.
 *
 * @param ptr  pointer to previously allocated memory block
 * @param size new size of the memory block in bytes
 * @return a pointer to the reallocated memory if succeed, otherwise NULL
 */
void *__mvbs_realloc(void *ptr, size_t size);

static inline void *mvbs_realloc(void *ptr, size_t size)
{
	void *addr;

	addr = __mvbs_realloc(ptr, size);
	pr_debug("Realloc memory, address = %p -> %p, size = %dBytes\n",
	ptr, addr, size);
	return addr;
}

/**
 * Free the memory block.
 *
 * @param buffer  pointer to allocated memory block to be freed
 */
void __mvbs_free(void *buffer);

static inline void mvbs_free(void *buffer)
{
	__mvbs_free(buffer);
}

/**
 * Allocates an array in memory with elements initialized to 0.
 *
 * @param count number of elements
 * @param size length of each element in bytes
 * @return a pointer to the allocated memory if succeed, otherwise NULL
 */
void *__mvbs_calloc(uint32_t count, size_t size);

static inline void *mvbs_calloc(uint32_t count, size_t size)
{
	void *addr;

	addr = __mvbs_calloc(count, size);
	pr_debug("Alloc memory, address = %p, size = %ldBytes\n",
				  addr, (size_t)(count * size));
	return addr;
}

bool mvbs_mm_ptr_is_valid(void *ptr);
int32_t mvbs_mm_check_guard(void);
uint32_t mvbs_mm_get_total_mem_size(void);
int32_t mvbs_mm_dump_block_info(void);

void mvbs_mm_init(void);

#endif
