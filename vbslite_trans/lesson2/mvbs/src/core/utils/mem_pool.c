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

#include <mvbs/utils/mm.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/mem_pool.h>

static void *mem_pool_alloc_internal(struct mem_pool *pmp)
{
	struct mp_blk_hdr *pblk = NULL;

	if ((pmp == NULL) || (pmp->blk_list == NULL) || (pmp->blk_free == 0U)) {
		return NULL;
	}

	pmp->blk_free--;

	pblk		= pmp->blk_list;

	pmp->blk_list	= pblk->next;
	pblk->next	= static_cast_ptr(struct mp_blk_hdr, pmp);

	return mp_get_blk_data(pblk);
}

static void mem_pool_free_internal(const void *pdata)
{
	struct mem_pool		*pmp = NULL;
	struct mp_blk_hdr	*pblk = NULL;

	if (pdata == NULL) {
		return;
	}

	pblk = mp_get_blk_hdr(pdata);

	pmp = static_cast_ptr(struct mem_pool, pblk->next);

	if (pmp == NULL) {
		return;
	}

	pmp->blk_free++;

	pblk->next	= pmp->blk_list;
	pmp->blk_list	= pblk;
}

int32_t mem_pool_init(struct mem_pool *mp, uint32_t blk_size, uint32_t blk_cnt)
{
	uint32_t offset		= 0U;
	uint32_t block_size	= blk_size;
	struct mp_blk_hdr *pblk	= NULL;

	if ((mp == NULL) || (block_size == 0U )) {
		return -ERR_INVALID;
	}

	block_size = MVBS_MM_ALIGN(block_size, 4U);

	if (blk_cnt == 0U) {
		mp->mem_addr	= NULL;
		mp->mem_size	= 0;
		mp->blk_total	= 0;
		mp->blk_free	= 0;
		mp->blk_size	= block_size;
		mp->blk_list	= 0;

		return 0;
	}

	/* allocate memory for memory pool blocks */
	mp->mem_size = (uint16_t)blk_cnt * (uint16_t)(MP_BLK_HDR_SIZE + block_size);
	mp->mem_addr = mvbs_malloc(mp->mem_size, MVBS_MM_ALIGN_DEFAULT);
	if (mp->mem_addr == NULL) {
		return -ERR_NOMEM;
	}

	/* zero out all of memory region */
	mvbs_memzero(mp->mem_addr, mp->mem_size);

	mp->blk_total = (uint16_t)blk_cnt;
	mp->blk_free  = mp->blk_total;
	mp->blk_size  = (uint16_t)block_size;

	/* initialize free block list */
	for (offset = 0u; offset < ((uint32_t)mp->blk_total-1u); offset++) {
		pblk = MP_BLK_HDR(mp, offset);

		pblk->next = MP_BLK_HDR(mp, offset+1u);
	}

	pblk = MP_BLK_HDR(mp, ((uint32_t)mp->blk_total-1u));

	pblk->next = NULL;

	mp->blk_list = MP_BLK_HDR(mp, 0u);

	return 0;
}

void mem_pool_deinit(struct mem_pool *pmp)
{
	if (pmp == NULL) {
		return ;
	}

	if (pmp->mem_addr != NULL) {
		mvbs_free(pmp->mem_addr);

		pmp->mem_addr = NULL;
	}
}

int32_t mem_pool_reset(struct mem_pool *mp)
{
	uint32_t offset		= 0U;
	struct mp_blk_hdr *pblk	= NULL;

	if ((mp == NULL) || (mp->mem_addr == NULL)
			 || (mp->blk_total == 0U) || (mp->blk_size == 0U)) {
		return -ERR_INVALID;
	}

#if 0
	uint32_t block_size	= mp->blk_size;
	uint32_t blk_cnt	= mp->blk_total;

	mp->mem_size = (uint16_t)blk_cnt * (uint16_t)(MP_BLK_HDR_SIZE + block_size);
	mp->blk_free  = mp->blk_total;
#endif

	/* initialize free block list */
	for (offset = 0u; offset < ((uint32_t)mp->blk_total-1u); offset++) {
		pblk = MP_BLK_HDR(mp, offset);

		pblk->next = MP_BLK_HDR(mp, offset+1u);
	}

	pblk = MP_BLK_HDR(mp, ((uint32_t)mp->blk_total-1u));

	pblk->next = NULL;

	mp->blk_list = MP_BLK_HDR(mp, 0u);

	return 0;
}

void *mem_pool_alloc(struct mem_pool *pmp)
{
	return mem_pool_alloc_internal(pmp);
}

void mem_pool_free(const void *paddr)
{
	mem_pool_free_internal(paddr);
}

void mem_pool_del(struct mem_pool *pmp,  mem_pool_data_free_hk_pre fn,
		  mem_pool_data_cmp cmp_fn, void *cmp_param)
{
	void *pdata = NULL;

	if (pmp != NULL) {
		foreach_mempool_avail_data(pmp, pdata) {
			if (cmp_fn(cmp_param, pdata)) {
				if (fn != NULL) {
					fn(pdata);
				}

				mem_pool_free_internal(pdata);
			}
		}
	}
}

void mem_pool_del_all(struct mem_pool *pmp, mem_pool_data_free_hk_pre fn)
{
	void *pdata = NULL;

	if (pmp != NULL) {
		foreach_mempool_avail_data(pmp, pdata) {
			fn(pdata);
			mem_pool_free_internal(pdata);
		}
	}
}

bool mem_pool_find(struct mem_pool *pmp, mem_pool_data_cmp cmp_fn,
					 void *cmp_param)
{
	void *pdata = NULL;

	if (pmp == NULL) {
		return false;
	}

	foreach_mempool_avail_data(pmp, pdata) {
		if (cmp_fn(cmp_param, pdata)) {
			return true;
		}
	}

	return false;
}

bool mem_pool_get_copy(struct mem_pool *pmp, mem_pool_data_cmp cmp_fn,
		   void *cmp_param, void *copy_dest, uint32_t size)
{
	void *pdata = NULL;

	if (pmp == NULL) {
		return false;
	}

	foreach_mempool_avail_data(pmp, pdata) {
		if (cmp_fn(cmp_param, pdata)) {
			mvbs_memcpy(copy_dest, pdata, size);

			return true;
		}
	}

	return false;
}

/* can modify member, but need to use in lock*/
bool mem_pool_get_reference(struct mem_pool *pmp, mem_pool_data_cmp cmp_fn,
			  void *cmp_param, void **reference)
{
	void *pdata = NULL;

	if (pmp == NULL) {
		return false;
	}

	foreach_mempool_avail_data(pmp, pdata) {
		if (cmp_fn(cmp_param, pdata)) {
			if (reference != NULL) {
				*reference = pdata;
			}

			return true;
		}
	}

	return false;
}

void *mem_pool_find_blk(struct mem_pool *pmp, mem_pool_data_cmp cmp_fn,
							  void *cmp_param)
{
	void *pdata = NULL;

	if (pmp == NULL) {
		return NULL;
	}

	foreach_mempool_avail_data(pmp, pdata) {
		if (cmp_fn(cmp_param, pdata)) {
			return pdata;
		}
	}

	return NULL;
}

#if 0 /* FIXME: Test Code ? */
void memory_pool_test(struct mem_pool *pmp)
{
	void *pdata;

	if (pmp == NULL) {
		return;
	}

	foreach_mempool_avail_data(pmp, pdata) {
		pdata++;
	};
}
#endif

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
