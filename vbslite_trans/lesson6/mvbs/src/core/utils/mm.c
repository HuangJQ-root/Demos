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

#include <mvbs/errno.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/mm.h>
#include <mvbs/utils/mm_stat.h>
#include <mvbs/utils/log.h>
#include <mvbs/utils/cdefs.h>
#include <mvbs/adapter/adapter.h>

#define MM_ALIGN_SIZE_DEF		4U

#define SHM_BUF_GUARD_SET		0x5a
#define SHM_BUF_GUARD_CLR		0x6b

#define	MM_MAX_REGION_NUM		8

struct mem_control_block {
	uint32_t guard:8;
	uint32_t size:24;
	struct mem_control_block *p_next_mcb;
};
#define MALLOC_BLOCK_MEM_LIMIT		((1UL << 24) - 1U)

#define MM_MCB_SIZE			round_up(sizeof(struct mem_control_block), MM_ALIGN_SIZE_DEF)
#define MM_MIN_MB_SIZE			((uint32_t)(MM_MCB_SIZE << 1U))

#define MM_PTR_TO_MCB(ptr)		static_cast_ptr(struct mem_control_block, ((char *)ptr - MM_MCB_SIZE))
#define MM_MCB_TO_PTR(mcb)		((void *)((char *)mcb + MM_MCB_SIZE))

int32_t mvbs_mm_region_register(struct mem_region *p_mem_regions);

static struct mem_control_block mcb_free_head;
static struct mem_control_block *p_mcb_end;
static struct mem_control_block *mcb_first_in_region[MM_MAX_REGION_NUM];
static struct mem_control_block *mcb_end_in_region[MM_MAX_REGION_NUM];

static uint32_t g_total_mem_size;
static uint32_t g_free_mem_size;
static int32_t inited;

static int32_t ___insert_free_mcb(struct mem_control_block *p_mcb_insert)
{
	struct mem_control_block *p_mcb = NULL;
	int32_t i;

	p_mcb_insert->guard = SHM_BUF_GUARD_CLR;

	/* find a right memory region */
	for (i = 0; i < MM_MAX_REGION_NUM; i++) {
		if (mcb_first_in_region[i] == NULL) {
			pr_err(ERR_INVALID, "mcb_first_in_region[%d] is null.", i);
			goto failed;
		}

		if ((mcb_first_in_region[i] <= p_mcb_insert) &&
		    (p_mcb_insert < mcb_end_in_region[i])) {
				break;
			}

	}

	if (i >= MM_MAX_REGION_NUM) {
		pr_err(ERR_INVALID, "Can't find a right memory region(i=%d).", i);
		goto failed;
	}

	p_mcb = (i==0)? &mcb_free_head : mcb_end_in_region[i - 1];
	if (p_mcb == NULL) {
		pr_err(ERR_INVALID, "p_mcb(%p) is null. i(%d)", p_mcb, i);
		goto failed;
	}

	/*
	 * Iterate through the list until a block is found that has a higher address
	 * than the block being inserted.
	 */
	for (; p_mcb->p_next_mcb < p_mcb_insert; p_mcb = p_mcb->p_next_mcb) {
		/* Nothing to do here, just iterate to the right position. */
		if (p_mcb->guard != (uint32_t)SHM_BUF_GUARD_CLR) {
			pr_err(ERR_INVALID, "The mcb (%p) was trampled!\n", p_mcb);
			return -ERR_INVALID;
		}

		if (p_mcb->p_next_mcb > mcb_end_in_region[i]) {
			pr_err(ERR_INVALID, "Can't find a right position(i=%d). p_mcb(%p)", i, p_mcb);
			goto failed;
		}
	}

	/*
	 * Do the block being inserted, and the block it is being inserted after
	 * make a contiguous block of memory?
	 */
	if (((char *)p_mcb + p_mcb->size) == (char *)p_mcb_insert) {
		p_mcb->size += p_mcb_insert->size;
		p_mcb_insert = p_mcb;
	}

	/*
	 * Do the block being inserted, and the block it is being inserted before
	 * make a contiguous block of memory?
	 */
	if (((char *)p_mcb_insert + p_mcb_insert->size) == (char *)p_mcb->p_next_mcb) {
		if (p_mcb->p_next_mcb != mcb_end_in_region[i]) {
			p_mcb_insert->size += p_mcb->p_next_mcb->size;
			p_mcb_insert->p_next_mcb = p_mcb->p_next_mcb->p_next_mcb;
		} else {
			p_mcb_insert->p_next_mcb = mcb_end_in_region[i];
		}
	} else {
		p_mcb_insert->p_next_mcb = p_mcb->p_next_mcb;
	}

	/*
	 * If the block being inserted plugged a gab, so was merged with the block
	 * before and the block after, then it's p_next_mcb pointer will have
	 * already been set, and should not be set here as that would make it point
	 * to itself.
	 */
	if (p_mcb != p_mcb_insert) {
		p_mcb->p_next_mcb = p_mcb_insert;
	}

	return 0;

failed:
	return -ERR_INVALID;
}

static void *___malloc(uint32_t numbytes)
{
	struct mem_control_block *p_prev_mcb = NULL;
	struct mem_control_block *p_mcb = NULL;
	struct mem_control_block *p_mcb_new = NULL;
	void *p_ret = NULL;

	if (inited == 0) {
		pr_err(ERR_FAULT, "memory isn't initialized.");
		return NULL;
	}

	/* memory address alignment */
	numbytes = MVBS_MM_ALIGN(numbytes, MM_ALIGN_SIZE_DEF);
	if (numbytes == 0U) {
		pr_err(ERR_FAULT, "___malloc size must be aligned %d.\n", MM_ALIGN_SIZE_DEF);
		return NULL;
	}

	if (numbytes > MALLOC_BLOCK_MEM_LIMIT) {
		pr_err(ERR_FAULT, "The requested memory(%d) exceeds the upper limit(%ld).\n",
				numbytes, MALLOC_BLOCK_MEM_LIMIT);
		return NULL;
	}

	if (numbytes > g_free_mem_size) {
		pr_err(ERR_FAULT, "memory full!  The memory free size is (%d)bytes.\n", g_free_mem_size);
		return NULL;
	}

	numbytes += MM_MCB_SIZE;
	/*
	 * Traverse the list from the start (lowest address) block until
	 * one of adequate size is found.
	 */
	p_prev_mcb = &mcb_free_head;
	p_mcb = mcb_free_head.p_next_mcb;
	while ((p_mcb->size < numbytes) && (p_mcb->p_next_mcb != NULL)) {
		p_prev_mcb = p_mcb;
		p_mcb = p_mcb->p_next_mcb;
	}

	/*
	 * If the end marker was reached then a block of adequate size
	 * was not found.
	 */
	if (p_mcb == p_mcb_end) {
		pr_err(ERR_FAULT, "There is not enough contiguous memory(%u) for malloc. "
		       "total_free_memory(%u)\n", numbytes, g_free_mem_size);
		goto unlock;
	}

	/*
	 * Return the memory space pointed to - jumping over the
	 * mcb structure at its start.
	 */
	p_ret = (void *)((char *)p_mcb + MM_MCB_SIZE);

	/*
	 * This block is being returned for use so must be taken out
	 * of the list of free blocks.
	 */
	p_prev_mcb->p_next_mcb = p_mcb->p_next_mcb;

	/*
	 * If the block is larger than required it can be split into
	 * two.
	 */
	if ((p_mcb->size - numbytes) >= MM_MIN_MB_SIZE) {
		/*
		 * This block is to be split into two.  Create a new
		 * block following the number of bytes requested.
		 */
		p_mcb_new = (struct mem_control_block *)((char *)p_mcb + numbytes);
		p_mcb_new->size = p_mcb->size - numbytes;

		/*
		 * Insert the new block into the list of free blocks.
		 */
		(void)___insert_free_mcb(p_mcb_new);

		p_mcb->size = numbytes;
	}

	p_mcb->guard = SHM_BUF_GUARD_SET;
	p_mcb->p_next_mcb = NULL;

	g_free_mem_size -= p_mcb->size;

#ifdef MEMORY_ALLOC_STAT
	dynamic_mem_info_update(true, p_mcb->size);
#endif

unlock:
	return p_ret;
}

static void ___free(void *ptr)
{
	struct mem_control_block *p_mcb = NULL;

	if (inited == 0) {
		pr_err(ERR_FAULT, "memory isn't initialized.");
		return;
	}

	if (ptr == NULL) {
		return;
	}

	p_mcb = MM_PTR_TO_MCB(ptr);
	if (p_mcb->guard != (uint32_t)SHM_BUF_GUARD_SET) {
		pr_err(ERR_FAULT, "the free addr(%p)'s mcb was trampled. size(%u)\n", ptr, p_mcb->size);
		return;
	}

	g_free_mem_size += p_mcb->size;

	pr_debug("Free memory, address = %p, size = %dBytes\n",
		  ptr, p_mcb->size);

#ifdef MEMORY_ALLOC_STAT
	dynamic_mem_info_update(false, p_mcb->size);
#endif

	(void)___insert_free_mcb(p_mcb);
}

void *__mvbs_malloc(size_t size, uint32_t alignment)
{
	void *buffer = NULL;
	size_t size_aligned = size;

	if (size_aligned == 0U) {
		pr_err(ERR_FAULT, "__mvbs_malloc size is zero.\n");
		goto ret;
	}

	if (alignment == (uint32_t)MVBS_MM_ALIGN_DEFAULT) {
		size_aligned = MVBS_MM_ALIGN(size_aligned, (size_t)MM_ALIGN_SIZE_DEF);
	}
	else {
		size_aligned = MVBS_MM_ALIGN(size_aligned, alignment);
	}

	buffer = ___malloc(size_aligned);
	if (buffer != NULL) {
		mvbs_memzero(buffer, size_aligned);
	}

ret:
	return buffer;
}

void *__mvbs_realloc(void *ptr, size_t size)
{
	void *new_ptr;
	uint32_t old_size;
	struct mem_control_block *mcb = NULL;

	if (ptr == NULL){
		if (size == 0u){
			pr_err(ERR_FAULT, "__mvbs_realloc ptr and size must not be zero.\n");
			return NULL;
		} else {
			return ___malloc(size);
		}
	}


	if (size == 0u) {
		__mvbs_free(ptr);
		return NULL;
	}

	/* get mcb of old ptr */
	mcb = MM_PTR_TO_MCB(ptr);
	if (mcb->guard != (uint32_t)SHM_BUF_GUARD_SET) {
		pr_err(ERR_FAULT, "memory overflow!\n");
		return NULL;
	}

	/* get old size */
	old_size = mcb->size;

	/* alloc new prt */
	new_ptr = ___malloc(size);
	if (new_ptr == NULL) {
		return NULL;
	}


	/* memory copy */
	mvbs_memcpy(new_ptr, ptr, (old_size <= (uint16_t)size) ? old_size : size);
	___free(ptr);

	return new_ptr;
}

void __mvbs_free(void *buffer)
{
	___free(buffer);
}

void *__mvbs_calloc(uint32_t count, size_t size)
{
	if ((count == 0u) || (size == 0u)) {
		return NULL;
	}

	return __mvbs_malloc(count * size, MM_ALIGN_SIZE_DEF);
}

bool mvbs_mm_ptr_is_valid(void *ptr)
{
	struct mem_control_block *p_mcb = NULL;

	if (ptr == NULL) {
		return false;
	}

	p_mcb = MM_PTR_TO_MCB(ptr);
	if (p_mcb->guard == (uint32_t)SHM_BUF_GUARD_SET) {
		return true;
	}

	if (p_mcb->guard != (uint32_t)SHM_BUF_GUARD_CLR) {
		pr_err(ERR_FAULT, "the addr(%p)'s mcb was trampled. size(%u)\n", ptr, p_mcb->size);
	}

	return false;
}

int32_t mvbs_mm_region_register(struct mem_region *p_mem_regions)
{
	int32_t mr_index = 0;
	struct mem_region *p_mr = NULL;
	uintptr_t aligned_mem_block_end = 0;
	uintptr_t aligned_mem_block = 0;
	uint32_t aligned_mr_size = 0;
	struct mem_control_block *p_prev_mcb = NULL;
	struct mem_control_block *p_mcb = NULL;

	if (p_mem_regions == NULL) {
		return -ERR_INVALID;
	}

	p_mr = &p_mem_regions[mr_index];

	while ((mr_index < MM_MAX_REGION_NUM) && (p_mr->mr_size > 0u)) {

		/* aligned start addr */
		aligned_mem_block = round_up((uintptr_t)p_mr->mr_start, MM_ALIGN_SIZE_DEF);

		mcb_first_in_region[mr_index] = (void *)aligned_mem_block;
		/* aligned mr size */
		aligned_mr_size = p_mr->mr_size - (aligned_mem_block - (uintptr_t)p_mr->mr_start);
		aligned_mr_size = round_down(aligned_mr_size, MM_ALIGN_SIZE_DEF);

		if (mr_index == 0) {
			mcb_free_head.p_next_mcb = (struct mem_control_block *)aligned_mem_block;
			mcb_free_head.size = 0;
			mcb_free_head.guard = SHM_BUF_GUARD_CLR;
		}

		/*
		 * Remember the location of the end marker in the previous region, if any.
		 */
		p_prev_mcb = p_mcb_end;

		/*
		 * p_mcb_end is used to mark the end of the list of free blocks and is
		 * inserted at the end of the region space.
		 */
		aligned_mem_block_end = aligned_mem_block + aligned_mr_size;
		aligned_mem_block_end -= MM_MCB_SIZE;
		aligned_mem_block_end = round_down(aligned_mem_block_end, MM_ALIGN_SIZE_DEF);
		p_mcb_end = (struct mem_control_block *)aligned_mem_block_end;
		p_mcb_end->size = 0;
		p_mcb_end->guard = SHM_BUF_GUARD_CLR;
		p_mcb_end->p_next_mcb = NULL;
		mcb_end_in_region[mr_index] = p_mcb_end;

		/*
		 * To start with there is a single free block in this region that is
		 * sized to take up the entire heap region minus the space taken by the
		 * free block structure.
		 */
		p_mcb = (struct mem_control_block *)aligned_mem_block;
		p_mcb->size = (uint32_t) (aligned_mem_block_end - (uintptr_t)p_mcb);
		p_mcb->p_next_mcb = p_mcb_end;
		p_mcb->guard = SHM_BUF_GUARD_CLR;

		/*
		 * If this is not the first region that makes up the entire heap space
		 * then link the previous region to this region.
		 */
		if (p_prev_mcb != NULL) {
			p_prev_mcb->p_next_mcb = p_mcb;
		}

		pr_debug("mem_region[%d] first_mcb(%p) - end_mcb(%p)", mr_index,
			 mcb_first_in_region[mr_index], mcb_end_in_region[mr_index]);

		g_total_mem_size += p_mcb->size;

		/*
		 * Move onto the next memory region structure.
		 */
		mr_index++;
		p_mr = &p_mem_regions[mr_index];
	}

	if (mr_index == 0) {
		pr_err(ERR_FAULT, "mem_region must have valid mr_start and mr_size!\n");
		return -ERR_INVALID;
	}

	if ((mr_index >= MM_MAX_REGION_NUM) &&
	    ((p_mem_regions[mr_index].mr_start != NULL) ||
	     (p_mem_regions[mr_index].mr_size != 0u))) {
		pr_err(ERR_FAULT, "Memory region has reached the maximum limit, "
		       "currently supports up to (%u).\n", MM_MAX_REGION_NUM);
		return -ERR_INVALID;
	}

	g_free_mem_size = g_total_mem_size;

	return 0;
}

#define DUMP_BIT				(3U)
#define DUMP_BIT_MASK				((1U << DUMP_BIT) - 1U)
#define DUMP_BIT_LINE				(3U + 2U )
#define DUMP_BIT_LINE_MASK			((1U << DUMP_BIT_LINE) - 1U)
int32_t mvbs_mm_dump_block_info(void)
{
	struct mem_control_block *p_mcb = NULL;
	int32_t mr_index = 0;

	char tmp_bit = ' ';
	const char *blank1 = "";
	const char *blank2 = "";

	int32_t ret = 0;
	uint32_t index = 0;

	pr_info("mem_region[%d] first_mcb(%p)", mr_index,
			    mcb_first_in_region[mr_index]);

	index = 0;
	p_mcb = mcb_first_in_region[mr_index];
	while (p_mcb != p_mcb_end) {
		if ((p_mcb->guard != (uint32_t)SHM_BUF_GUARD_SET) && (p_mcb->guard != (uint32_t)SHM_BUF_GUARD_CLR)) {
			pr_err(ERR_FAULT, "memory mcb(%p) was trampled. guard(%x)\n", p_mcb, p_mcb->guard);
			ret = -ERR_FAULT;
			goto out;
		}

		if (p_mcb->guard == (uint32_t)SHM_BUF_GUARD_SET) {
			tmp_bit = '1';
		} else {
			tmp_bit = '0';
		}

		if ((index & DUMP_BIT_LINE_MASK) == 0u) {
			blank1 = "        ";
		}

		if ((index & DUMP_BIT_MASK) == DUMP_BIT_MASK) {
			blank2 = " ";
		}

		if ((index & DUMP_BIT_LINE_MASK) == DUMP_BIT_LINE_MASK) {
			pr_info("%s%c%s", blank1, tmp_bit, blank2);
		}

		if (p_mcb->size != 0u) {
			++index;
			p_mcb = (void *)((char *)p_mcb + p_mcb->size);
		} else {
			if ((index & DUMP_BIT_LINE_MASK) == DUMP_BIT_LINE_MASK) {
				pr_info("%s%c%s", blank1, tmp_bit, blank2);
			}
			index = 0;

			++mr_index;
			p_mcb = mcb_first_in_region[mr_index];
			pr_info("mem_region[%d] first_mcb(%p)", mr_index,
					    mcb_first_in_region[mr_index]);
		}
	}

	pr_info("%s%c%s", blank1, tmp_bit, blank2);

out:
	return ret;
}

int32_t mvbs_mm_check_guard(void)
{
	struct mem_control_block *p_mcb = NULL;
	size_t check_size = 0;
	int32_t mr_index = 0;
	int32_t ret = 0;

	p_mcb = mcb_first_in_region[mr_index];
	while (p_mcb != p_mcb_end) {

		check_size += p_mcb->size;

		if ((p_mcb->guard != (uint32_t)SHM_BUF_GUARD_SET) && (p_mcb->guard != (uint32_t)SHM_BUF_GUARD_CLR)) {
			pr_err(ERR_FAULT, "memory mcb(%p) was trampled. guard(%x)\n", p_mcb, p_mcb->guard);
			ret = -ERR_FAULT;
			goto out;
		}


		if (p_mcb->size != 0u) {
			p_mcb = (void *)((char *)p_mcb + p_mcb->size);
		}
		else {
			++mr_index;
			p_mcb = mcb_first_in_region[mr_index];
		}
	}

	pr_info("memory guard check success. check_size(%lu) total_size(%u)\n", check_size, g_total_mem_size);

out:
	return ret;
}

uint32_t mvbs_mm_get_total_mem_size(void)
{
	return g_total_mem_size;
}

void mvbs_mm_init(void)
{
	if (inited != 0) {
		return ;
	}

	if (mvbs_mm_region_register(mvbs_get_heap_info()) == 0 ) {
		inited = 1;
		pr_info("memory initialization succeeded.");
	} else {
		pr_err(ERR_FAULT, "memory initialization failed.");
	}
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
