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

#ifndef MVBS_CORE_HISTORY_WRITER_CACHE_H
#define MVBS_CORE_HISTORY_WRITER_CACHE_H

#ifdef __MVBS_CORE_SOURCE__
#include <mvbs/core/entities/writer.h>
#include <mvbs/core/history/history_cache.h>

struct writer_cache_change {
	struct cache_change		cc;		/* common part */

	TransferStatus			send_status;	/* Tx status */
	uint16_t			real_size;	/* real data length */
};

static inline void *writer_cache_get_cc_payload(struct writer_cache_change *cc)
{
	return (void *)(cc + 1);
}

static inline int32_t cache_change_update_trans_status(struct writer_cache_change *wcc,
					 uint16_t status)
{
	if (!transferstatus_is_valid(status)) {
		return -ERR_INVALID;
	}

	wcc->send_status = status;

	return 0;
}

static inline bool writer_cache_is_full(struct writer *w)
{
	return hc_is_full(&w->history);
}

static inline struct rtps_sn writer_cache_get_min_sn(struct writer *w)
{
	return hc_get_min_seq(&w->history);
}

static inline struct rtps_sn writer_cache_get_max_sn(struct writer *w)
{
	return hc_get_max_seq(&w->history);
}

static inline struct rtps_sn writer_cache_get_next_sn(struct writer *w,
						     struct rtps_sn sn)
{
	return hc_get_next_seq(&w->history, sn);
}

static inline struct writer_cache_change *writer_cache_alloc_cc(struct writer *w)
{
	struct writer_cache_change *wcc = NULL;

	wcc = (struct writer_cache_change *)mem_pool_alloc(writer_get_cache_change_pool(w));

	return wcc;
}

static inline void writer_cache_free_cc(struct writer_cache_change *wcc)
{
	mem_pool_free((void *)wcc);
}

struct writer_cache_change *writer_cache_get_oldest_cc(struct writer *w);

struct writer_cache_change *writer_cache_get_cc(struct writer *w,
						struct rtps_sn sn);

void writer_cache_add_cc(struct writer *w, struct writer_cache_change *wcc);

void writer_cache_del_cc_upto(struct writer *w, struct rtps_sn seq_num);

void writer_cache_del_oldest_cc(struct writer *w);

void writer_cache_clean(struct writer *w);

int32_t writer_cache_init(struct writer *w, uint32_t cc_size);

uint16_t writer_cache_deinit(struct writer *w);

#endif
#endif /* !MVBS_CORE_WRITER_CACHE_H */
