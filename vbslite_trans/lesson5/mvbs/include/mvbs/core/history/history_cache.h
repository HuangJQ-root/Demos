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

#ifndef MVBS_CORE_HISTORY_HISTORY_CACHE_H
#define MVBS_CORE_HISTORY_HISTORY_CACHE_H

#ifdef __MVBS_CORE_SOURCE__
#include <mvbs/rtps/sequence_number.h>
#include <mvbs/rtps/time.h>
#include <mvbs/utils/mvbs_list.h>
#include <mvbs/utils/mem_pool.h>

struct history_cache {
	struct mvbs_list		caches;

	struct mem_pool			cache_change;	/* Pool of "struct cache_change + sample" */
};

struct cache_change {
	struct rtps_sn			sn;
	struct mvbs_list		history_node;
	struct rtps_time		ts;		/* time added in history cache */
};

static inline void history_cache_init(struct history_cache *hc)
{
	mvbs_list_init(&hc->caches);
}

static inline void history_cache_deinit(struct history_cache *hc)
{
	mem_pool_deinit(&hc->cache_change);
}

static inline uint16_t hc_get_max_count(struct history_cache *hc)
{
	return mem_pool_total_blk_cnt(&hc->cache_change);
}

static inline uint16_t hc_get_cur_count(struct history_cache *hc)
{
	return mem_pool_avail_blk_cnt(&hc->cache_change);
}

static inline bool hc_is_empty(struct history_cache *hc)
{
	uint16_t cur_size = hc_get_cur_count(hc);

	return (cur_size == 0U);
}

static inline bool hc_is_full(struct history_cache *hc)
{
	uint16_t cur_size = hc_get_cur_count(hc);
	uint16_t max_size = hc_get_max_count(hc);

	return (cur_size >= max_size);
}

typedef void (*cache_change_release)(struct cache_change *cc);

void hc_del_changes_upto(struct history_cache *hc, struct rtps_sn sn,
						   cache_change_release cc_free);

struct cache_change *hc_pop_first_cc(struct history_cache *hc);

struct rtps_sn hc_get_min_seq(struct history_cache *hc);

struct rtps_sn hc_get_max_seq(struct history_cache *hc);

struct rtps_sn hc_get_next_seq(struct history_cache *hc,
				       struct rtps_sn sn);

struct history_cache *history_cache_alloc(void);


/* cache_change operation */
struct cache_change *hc_get_cc_by_sn(struct history_cache *hc,
					 struct rtps_sn sn);

struct cache_change *hc_get_first_cc(struct history_cache *hc);

#endif
#endif
