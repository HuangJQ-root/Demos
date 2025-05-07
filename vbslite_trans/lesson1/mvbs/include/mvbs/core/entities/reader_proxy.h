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

#ifndef MVBS_CORE_ENTITIES_READER_PROXY_H
#define MVBS_CORE_ENTITIES_READER_PROXY_H

#ifdef __MVBS_CORE_SOURCE__

#include <mvbs/utils/mem_pool.h>
#include <mvbs/utils/bitmap.h>
#include <mvbs/rtps/guid.h>
#include <mvbs/rtps/sequence_number.h>
#include <mvbs/core/entities/participant_proxy.h>
#include <mvbs/core/entities/writer.h>
#include <mvbs/core/qos/qos.h>

struct reader_proxy {
	struct participant_proxy	*ptcp_proxy;

	struct rtps_entity_id		eid;

	/* min SequenceNumber of UNACKED changes. */
	struct rtps_sn			changes_lowmark;
	struct rtps_sn			start_sn;

	int32_t				acknack_count;

	uint8_t				durability_kind;

	struct {
		uint8_t use_multicast:1;
		uint8_t suppress_unicast:1;
		uint8_t unknown_eid:1;
		uint8_t reliable:1;
	} flags;
};

/*   +====================+
 *   |                    |
 *   |     reader         |
 *   |                    |
 *   |     proxy          |
 *   |                    |
 *   +--------------------+
 *   |  ulong_t bitmap[x] | dynamic bitmap size 
 *   +====================+
 */
typedef struct reader_proxy		reader_proxy_t;

static inline void reader_proxy_get_guid(struct reader_proxy *rproxy,
					 struct rtps_guid *id)
{
	if (rproxy->ptcp_proxy != NULL) {
		id->prefix	= rproxy->ptcp_proxy->guid.prefix;
		id->eid		= rproxy->eid;
	} else {
		*id		= GUID_UNKNOWN;
	}
}

static inline struct rtps_guid_prefix *reader_proxy_get_prefix(struct reader_proxy *rproxy)
{
	return &rproxy->ptcp_proxy->guid.prefix;
}

static inline struct rtps_entity_id *reader_proxy_get_eid(struct reader_proxy *rproxy)
{
	return &rproxy->eid;
}

static inline struct reader_proxy *reader_proxy_alloc(struct writer *w)
{
	return mem_pool_alloc(&w->proxies);
}

static inline void reader_proxy_free(struct reader_proxy *rproxy)
{
	rproxy->ptcp_proxy = NULL;

	mem_pool_free(rproxy);
}

static inline struct writer *reader_proxy_get_writer(struct reader_proxy *rproxy)
{
	struct mem_pool	*proxy_pool;

	proxy_pool = mp_get_mp_from_blk_data(rproxy);

	return container_of(proxy_pool, struct writer, proxies);
}

static inline struct participant_proxy *reader_proxy_get_ptcp_proxy(struct reader_proxy *rproxy)
{
	struct participant_proxy	*ptcp_proxy;
	struct participant		*ptcp;
	struct writer			*w;
	struct rtps_guid_prefix		*prefix;

	w = reader_proxy_get_writer(rproxy);

	prefix = reader_proxy_get_prefix(rproxy);

	ptcp = writer_get_ptcp(w);

	ptcp_proxy = ptcp_get_proxy_with_guid_prefix(ptcp, prefix);

	return ptcp_proxy;
}

static inline uint16_t reader_proxy_get_sent_map_size(struct reader_proxy *rproxy)
{
	struct writer* w = reader_proxy_get_writer(rproxy);
	struct mem_pool *pool = &w->proxies;

	return pool->blk_size - (uint16_t)sizeof(struct reader_proxy);
}

static inline void *reader_proxy_get_sent_map(struct reader_proxy *rproxy)
{
	return (void *)(rproxy + 1);
}

static inline void reader_proxy_clear_sent_map(struct reader_proxy *rproxy)
{
	void     *map = reader_proxy_get_sent_map(rproxy);
	uint16_t size = reader_proxy_get_sent_map_size(rproxy);

	mvbs_memzero(map, size);
}

void reader_proxy_init(struct reader_proxy *rproxy,
		       struct participant_proxy *ptcp_proxy,
		       const struct rtps_entity_id eid,
		       bool reliable,
		       uint8_t durability_kind);

void reader_proxy_add_change(struct reader_proxy *rproxy,
			     const struct rtps_sn *seq_num);
void reader_proxy_del_change(struct reader_proxy *rproxy,
			     const struct rtps_sn *seq_num);

static inline void reader_proxy_del_all_change(struct reader_proxy *rproxy)
{
	if ((rproxy == NULL) || (rproxy->flags.reliable == 0U)) {
		return;
	}

	reader_proxy_clear_sent_map(rproxy);

	rtps_sn_set_value(&rproxy->changes_lowmark, 0);
}

static inline void reader_proxy_ack_change(struct reader_proxy *rproxy,
					   const struct rtps_sn *sn)
{
	int64_t sn_num	= rtps_sn_to_int64(sn);
	int64_t lowmark = rtps_sn_to_int64(&rproxy->changes_lowmark);
	int64_t offset	= sn_num - lowmark; /* FIXME */

	size_t bitmap_bytes = reader_proxy_get_sent_map_size(rproxy);
	size_t bitmap_range = bitmap_bytes * 8 - 1U;

	ulong_t *sent_map   = reader_proxy_get_sent_map(rproxy);

	if ((offset >= 0) && (offset <= (int64_t)bitmap_range)) {
		bitmap_clear_bit(offset, sent_map);
	}
}

void reader_proxy_acked_changes_set(struct reader_proxy *rproxy,
				    const struct rtps_sn *seq_num);

void reader_proxy_update_lowmark(struct reader_proxy *rproxy,
				   const struct rtps_sn *seq_num);

static inline void reader_proxy_destroy(struct reader_proxy *rproxy)
{
	struct writer *w;

	if (rproxy == NULL) {
		return ;
	}

	w = reader_proxy_get_writer(rproxy);

	reader_proxy_del_all_change(rproxy);

	writer_on_publication_matched(w, false);

	reader_proxy_free(rproxy);

	pr_verb("Reader proxy offline: %s: " ENTITY_ID_FMT,
					rproxy->ptcp_proxy->ptcp_name,
					ENTITY_ID_PARTS(rproxy->eid));
}

#endif
#endif
