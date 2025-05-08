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

#ifndef MVBS_UTILS_MEM_POOL_H
#define MVBS_UTILS_MEM_POOL_H

#include <mvbs/base_type.h>
#include <mvbs/errno.h>
#include <mvbs/utils/cdefs.h>

struct mp_blk_hdr {
	struct mp_blk_hdr	*next;
};

#define	MP_BLK_HDR_SIZE		sizeof(struct mp_blk_hdr)

struct mem_pool {
	void			*mem_addr;  /* memory pool address */
	uint16_t		mem_size;   /* memory pool size */
	uint16_t		blk_total;  /* memory block number total */
	uint16_t		blk_free;   /* memory block number unused */
	uint16_t		blk_size;   /* memory block size, except mp_blk_hdr */
	struct mp_blk_hdr	*blk_list;  /* memory block free list pointer */
};

#if 0
#include <mvbs/utils/log.h>

static inline void mem_pool_info_dump(struct mem_pool *mp)
{
	pr_info("mp->mem_addr:\t%p", mp->mem_addr);
	pr_info("mp->mem_size:\t%d", mp->mem_size);
	pr_info("mp->blk_total:\t%d", mp->blk_total);
	pr_info("mp->blk_free:\t%d", mp->blk_free);
	pr_info("mp->blk_size:\t%d", mp->blk_size);
	pr_info("mp->blk_list:\t%p", mp->mem_addr);
}
#endif

#define DEFINE_MEM_POOL(_name, _blk_size, _blk_total)				\
	struct mem_pool _name {							\
		.mem_addr = (char [_blk_size * _blk_total]){},			\
		.mem_size = _blk_size * _blk_total,				\
		.blk_total= _blk_total,						\
		.blk_free = 0,							\
		.blk_size = _blk_size,						\
		.blk_list = NULL,						\
	}

/*
 *  +--- mem_addr
 *  |
 *  |  block      block
 *  V  header     data
 *  +--------------+------+--------------+------+------------------+--------------+------+
 *  | mp_blk_hdr * | data | mp_blk_hdr * | data |       ....       | mp_blk_hdr * | data |
 *  +--------------+------+--------------+------+------------------+--------------+------+
 *         |              ^      |              ^                         |
 *         |  next        |      |  next        |                         |  next
 *         +--------------+      +--------------+                         +-------> NULL
 */

static inline void * mp_get_end_addr(const struct mem_pool *mp)
{
	return (uint8_t *)(mp->mem_addr) + mp->mem_size;
}

static inline uint32_t mp_get_blk_size(const struct mem_pool *mp)
{
	return mp->blk_size + MP_BLK_HDR_SIZE;
}

#define MP_BLK_HDR(mp, idx)	static_cast_ptr(struct mp_blk_hdr, ((uint8_t*)(mp)->mem_addr + ((idx) * mp_get_blk_size(mp))))

static inline struct mp_blk_hdr *mp_get_blk_hdr_by_idx(const struct mem_pool *mp, uint32_t idx)
{
	uint8_t *ptr = (uint8_t*)mp->mem_addr;

	if (idx >= mp->blk_total) {
		return NULL;
	}

	ptr += idx * mp_get_blk_size(mp);

	return static_cast_ptr(struct mp_blk_hdr, ptr);
}

static inline struct mp_blk_hdr *mp_get_blk_hdr(const void *pdata)
{
	return (struct mp_blk_hdr *)pdata -1;
}

static inline struct mp_blk_hdr *mp_get_next_blk_hdr(const void *pdata)
{
	return mp_get_blk_hdr(pdata)->next;
}

/* Note:
 * The block data pointed by pdata should not a free block.
 */
static inline struct mem_pool *mp_get_mp_from_blk_data(const void *pdata)
{
	const struct mp_blk_hdr *pblk;

	pblk = mp_get_blk_hdr(pdata);

	return static_cast_ptr(struct mem_pool, pblk->next);
}

static inline void * mp_get_blk_data(const struct mp_blk_hdr *blk_hdr)
{
	return (void *)(blk_hdr+1);
}

static inline void *mp_get_first_blk(const struct mem_pool *mp)
{
	return (struct mp_blk_hdr *)mp->mem_addr;
}

static inline struct mp_blk_hdr *mp_get_next_blk(const struct mem_pool *mp,
						 const struct mp_blk_hdr *blk_hdr)
{
	return (struct mp_blk_hdr *)((uint8_t *)blk_hdr + mp_get_blk_size(mp));
}

static inline void * mp_get_first_blk_data(const struct mem_pool *mp)
{
	return mp_get_blk_data((struct mp_blk_hdr *)mp->mem_addr);
}

static inline void * mp_get_next_blk_data(const struct mem_pool *mp,
					  const void *pdata)
{
	return (void *)((uint8_t *)pdata + mp_get_blk_size(mp));
}

static inline void * mp_get_blk_data_by_idx(const struct mem_pool *mp, uint32_t idx)
{
	struct mp_blk_hdr *ptr;

	ptr = mp_get_blk_hdr_by_idx(mp, idx);
	if (ptr == NULL) {
		return NULL;
	}

	if (ptr->next == (void *)mp) {
		return mp_get_blk_data(ptr);
	}

	return NULL;
}

static inline uint16_t mp_get_blk_data_idx(const void *pdata)
{
	const struct mem_pool	*mp;
	const struct mp_blk_hdr	*pblk;
	size_t			offset;

	pblk = mp_get_blk_hdr(pdata);

	mp = static_cast_ptr(struct mem_pool, pblk->next);

	offset = (uint8_t *)pblk - (uint8_t *)mp->mem_addr;

	return (uint16_t)(offset / mp_get_blk_size(mp));
}

static inline bool mp_blk_data_is_valid(const struct mem_pool *mp, void *pdata)
{
	return mp_get_next_blk_hdr(pdata) == (void *)mp;
}

static inline void *mp_get_next_avail_blk_data(const struct mem_pool *mp, void *pdata)
{
	if (mp->mem_addr == NULL) {
		return NULL;
	}

	if (pdata == NULL) {
		pdata = mp_get_first_blk_data(mp);

		if (pdata > mp_get_end_addr(mp)) {
			return NULL;
		}

		if (mp_blk_data_is_valid(mp, pdata)) {
			return pdata;
		}
	}

	do {
		pdata = mp_get_next_blk_data(mp, pdata);

		if (pdata > mp_get_end_addr(mp)) {
			return NULL;
		}
	} while (!mp_blk_data_is_valid(mp, pdata));

	return pdata;
}

#define foreach_mempool_block(pmp, pblk)				\
	for (void *iter____ = mp_get_first_blk((pmp));			\
	     (iter____ < mp_get_end_addr((pmp))) && (pblk = iter____);	\
	     iter____ = mp_get_next_blk((pmp), iter____))

#define foreach_mempool_data(pmp, pblk)					\
	for (void *iter____= mp_get_first_blk_data((pmp));		\
	     (iter____ < mp_get_end_addr((pmp))) && (pblk = iter____);	\
	     iter____ = mp_get_next_blk_data((pmp), iter____))

#define foreach_mempool_avail_data(pmp, pdata)				\
	for (void *iter____ = mp_get_next_avail_blk_data((pmp), NULL);	\
	    (iter____ != NULL) && (pdata = iter____);			\
	     iter____ = mp_get_next_avail_blk_data((pmp), iter____))

typedef bool (*mem_pool_data_cmp)(void *cmp_param, void *pdata);
typedef void (*mem_pool_data_free_hk_pre)(void *pdata);


int32_t mem_pool_init(struct mem_pool *mp, uint32_t blk_size, uint32_t blk_cnt);
void mem_pool_deinit(struct mem_pool *pmp);

int32_t mem_pool_reset(struct mem_pool *mp);

static inline bool mem_pool_is_valid(const struct mem_pool *pmp)
{
	if (pmp == NULL) {
		return false;
	}

	if ((pmp->mem_addr == NULL) || (pmp->mem_size == 0)
				    || (pmp->blk_total == 0)
				    || (pmp->blk_size == 0)) {
		return false;
	}

	return true;
}

static inline bool mem_pool_is_empty(const struct mem_pool *pmp)
{
	if ((pmp != NULL) && (pmp->blk_free == 0U)) {
		return true;
	}

	return false;
}

static inline bool mem_pool_has_not_avail_data(const struct mem_pool *pmp)
{
	if ((pmp != NULL) && (pmp->blk_free == pmp->blk_total)) {
		return true;
	}

	return false;
}

static inline uint16_t mem_pool_total_blk_cnt(const struct mem_pool *pmp)
{
	if (pmp == NULL) {
		return (uint16_t)-1;
	}

	return pmp->blk_total;
}

static inline uint16_t mem_pool_avail_blk_cnt(const struct mem_pool *pmp)
{
	if (pmp == NULL) {
		return 0U;
	}

	return pmp->blk_total - pmp->blk_free;
}

static inline uint16_t mem_pool_free_blk_cnt(const struct mem_pool *pmp)
{
	if (pmp == NULL) {
		return 0U;
	}

	return pmp->blk_free;
}

void *mem_pool_alloc(struct mem_pool *pmp);
void mem_pool_free(const void *paddr);

void mem_pool_del(struct mem_pool *pmp,  mem_pool_data_free_hk_pre fn,
			mem_pool_data_cmp cmp_fn, void *cmp_param);

void mem_pool_del_all(struct mem_pool *pmp, mem_pool_data_free_hk_pre fn);

bool mem_pool_find(struct mem_pool *pmp, mem_pool_data_cmp cmp_fn,
					 void *cmp_param);

bool mem_pool_get_copy(struct mem_pool *pmp, mem_pool_data_cmp cmp_fn,
			void *cmp_param,
			void *copy_dest, uint32_t size);

bool mem_pool_get_reference(struct mem_pool *pmp, mem_pool_data_cmp cmp_fn,
			void *cmp_param, void **reference);

void *mem_pool_find_blk(struct mem_pool *pmp, mem_pool_data_cmp cmp_fn,
							  void *cmp_param);
#endif
