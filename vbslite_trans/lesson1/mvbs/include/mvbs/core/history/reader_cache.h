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

#ifndef MVBS_CORE_HISTORY_READER_CACHE_H
#define MVBS_CORE_HISTORY_READER_CACHE_H

#ifdef __MVBS_CORE_SOURCE__
#include <mvbs/base_type.h>
#include <mvbs/core/types.h>
#include <mvbs/core/entities/participant_proxy.h>
#include <mvbs/core/entities/writer_proxy.h>
#include <mvbs/core/history/history_cache.h>

#include <mvbs/utils/log.h>
#include <mvbs/utils/string.h>

struct reader;

struct reader_cache_change {
	struct cache_change		cc;		/* common part */

	struct writer_proxy		*source;	/* point to writer_proxy */
	struct rtps_time		ts_sent;	/* ts of writer_proxy send */

	uint16_t			counter;	/* e2e counter */
	uint16_t			e2e_status;	/* e2e status */
	uint16_t			recv_size;	/* recv data length */
};

static inline struct reader_cache_change *reader_cache_change_alloc(struct reader *r)
{
	struct reader_cache_change *rcc;

	rcc = (struct reader_cache_change *)mem_pool_alloc(reader_get_cc_pool(r));

	return rcc;
}

static inline void reader_cache_change_free(struct reader_cache_change *rcc)
{
	mem_pool_free((void *)rcc);
}

static inline void reader_cache_change_destroy(struct reader_cache_change *rcc)
{
	mvbs_list_del(&rcc->cc.history_node);

	reader_cache_change_free(rcc);
}

static inline void *reader_cache_change_payload(struct reader_cache_change *rcc)
{
	return (void *)(rcc + 1);
}

static inline bool reader_cache_change_copy(struct reader_cache_change *rcc,
					uint8_t *buffer, uint16_t dest_size)
{
	if ((rcc == NULL) || (buffer == NULL)) {
		return false;
	}

	if (dest_size < (uint16_t)rcc->recv_size) {
		pr_warn("The dest buffer is too small\n");
		return false;
	}

	mvbs_memcpy(buffer, reader_cache_change_payload(rcc), rcc->recv_size);

	return true;
}

static inline void reader_cachachange_get_info(struct reader_cache_change *rcc,
					       struct mvbs_entity_info *info)
{
	struct writer_proxy	*proxy = rcc->source;

	if ((proxy == NULL) || (proxy->ptcp_proxy == NULL)) {
		info->guid	  = GUID_UNKNOWN;
		info->remote_name = NULL;
	} else {
		writer_proxy_get_guid(proxy, &info->guid);
		info->remote_name = proxy->ptcp_proxy->ptcp_name;
	}
}

struct rtps_sn reader_cache_get_max_sn_with_wproxy(struct reader *r,
						   struct writer_proxy *proxy);

struct reader_cache_change *reader_cache_get_oldest_cc(struct reader *r);
void reader_cache_add_cc(struct reader *r, struct reader_cache_change *new_cc);
void reader_cache_del_oldest_cc(struct reader *r);

static inline bool reader_cache_is_full(struct reader *r)
{
	return hc_is_full(&r->history);
}

void reader_cache_clean(struct reader *r);

int32_t reader_cache_init(struct reader *r, uint32_t sample_size);
uint16_t reader_cache_deinit(struct reader *r);

#endif
#endif /* !MVBS_CORE_READER_CACHE_H */
