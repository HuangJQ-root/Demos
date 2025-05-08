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

#ifndef MVBS_CORE_ENTITIES_WRITER_PROXY_H
#define MVBS_CORE_ENTITIES_WRITER_PROXY_H

#ifdef __MVBS_CORE_SOURCE__

#include <mvbs/core/entities/reader.h>
#include <mvbs/core/entities/participant_proxy.h>
#include <mvbs/core/qos/qos.h>
#include <mvbs/core/qos/wlp.h>
#include <mvbs/utils/bitmap.h>
#include <mvbs/utils/mem_pool.h>

struct writer_proxy {
	struct participant_proxy	*ptcp_proxy;

	struct rtps_entity_id		eid;

	struct rtps_sn			max_sn;
	/* All cache changes with sn less than or equal to
	 * missing_lowmark have been received
	 */
	struct rtps_sn			missing_lowmark;

	int32_t				acknack_count;
	int32_t				hb_count;

	uint16_t			owner_strength;

	timer_desc_t			liveliness_td;

	uint16_t			liveliness_status : 2;
	uint16_t			e2e_first_rcv : 1;
	uint16_t 			last_e2e_err_flag : 1;

	int16_t				last_e2e_count;	/* TBD after e2e updated */
};

/*   +====================+
 *   |                    |
 *   |     writer         |
 *   |                    |
 *   |     proxy          |
 *   |                    |
 *   +--------------------+
 *   |  ulong_t bitmap[x] | dynamic bitmap size
 *   +====================+
 */

typedef struct writer_proxy		writer_proxy_t;

static inline struct writer_proxy *writer_proxy_alloc(struct reader *r)
{
	return mem_pool_alloc(&r->proxies);
}

static inline void writer_proxy_free(struct writer_proxy *wproxy)
{
	wproxy->ptcp_proxy = NULL;

	mem_pool_free(wproxy);
}

void writer_proxy_init(struct writer_proxy *wproxy,
		       struct participant_proxy *ptcp_proxy,
		       const struct rtps_entity_id eid,
		       uint32_t strength);

static inline struct reader *writer_proxy_get_reader(struct writer_proxy *wproxy)
{
	struct mem_pool	*proxy_pool;

	proxy_pool = mp_get_mp_from_blk_data(wproxy);

	return container_of(proxy_pool, struct reader, proxies);
}

static inline void writer_proxy_get_guid(struct writer_proxy *wproxy,
					 struct rtps_guid *id)
{
	if ((wproxy != NULL) && (wproxy->ptcp_proxy != NULL)) {
		id->prefix	= wproxy->ptcp_proxy->guid.prefix;
		id->eid		= wproxy->eid;
	} else {
		*id		= GUID_UNKNOWN;
	}
}

static inline struct rtps_guid_prefix *writer_proxy_get_prefix(struct writer_proxy *wproxy)
{
	return &wproxy->ptcp_proxy->guid.prefix;
}

static inline struct rtps_entity_id *writer_proxy_get_eid(struct writer_proxy *wproxy)
{
	return &wproxy->eid;
}

static inline int32_t writer_proxy_get_acknack_count(struct writer_proxy *wproxy)
{
	const int32_t tmp = wproxy->acknack_count;

	++(wproxy->acknack_count);

	return tmp;
}

static inline uint16_t writer_proxy_get_strength(const struct writer_proxy *wproxy)
{
	return wproxy->owner_strength;
}

static inline uint16_t writer_proxy_get_received_map_size(struct writer_proxy *wproxy)
{
	struct reader* r = writer_proxy_get_reader(wproxy);
	struct mem_pool *pool = &r->proxies;

	return pool->blk_size - (uint16_t)sizeof(struct writer_proxy);
}

static inline void *writer_proxy_get_received_map(struct writer_proxy *wproxy)
{
	return (void *)(wproxy + 1);
}

static inline void writer_proxy_clear_received_map(struct writer_proxy *wproxy)
{
	void     *map = writer_proxy_get_received_map(wproxy);
	uint16_t size = writer_proxy_get_received_map_size(wproxy);

	mvbs_memzero(map, size);
}

bool writer_proxy_need_send_ack(struct writer_proxy *wproxy);

bool writer_proxy_set_received_change(struct writer_proxy *wproxy,
				      const struct rtps_sn *seq_num);

uint16_t writer_proxy_lost_changes_update(struct writer_proxy *wproxy,
				      const struct rtps_sn *first_sn,
				      const struct rtps_sn *last_sn);

struct rtps_sn_set writer_proxy_get_missing(struct writer_proxy *wproxy);

static inline void writer_proxy_del_all_change(struct reader *r, struct writer_proxy *wproxy)
{
	if ((r == NULL) || (wproxy == NULL)) {
		pr_err(ERR_INVALID, "Invalid reader or wproxy pointer.\n");
		return;
	}

	writer_proxy_clear_received_map(wproxy);

	wproxy->missing_lowmark.high	= 0;
	wproxy->missing_lowmark.low	= 0;

	wproxy->max_sn.high		= 0;
	wproxy->max_sn.low		= 0;

	wlp_delete_local_reader(r, wproxy);
}

static inline void writer_proxy_destroy(struct writer_proxy *wproxy)
{
	struct reader *r;

	if (wproxy == NULL) {
		return ;
	}

	r = writer_proxy_get_reader(wproxy);

	writer_proxy_del_all_change(r, wproxy);

	void reader_cache_update_on_wproxy_offline(struct reader *r,
					   struct writer_proxy *proxy);

	reader_cache_update_on_wproxy_offline(r, wproxy);

	writer_proxy_free(wproxy);

	wlp_reader_detach_writer(r);

	/*
	 * remote participant offline, a new owner should be selected
	 * only when the writer is current owner
	 */
	if (wproxy == r->owner) {
		reader_ownership_update(r, NULL, false);
	}

	reader_on_subscription_matched(r, false);

	pr_verb("Writer proxy offline: %s: " ENTITY_ID_FMT,
					wproxy->ptcp_proxy->ptcp_name,
					ENTITY_ID_PARTS(wproxy->eid));
}
#endif

#endif
