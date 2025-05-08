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

#include <core/core.h>
#include <mvbs/utils/time.h>

#define to_reader_cache_change(cache)				\
	container_of(cache, struct reader_cache_change, cc)

struct reader_cache_change *reader_cache_get_oldest_cc(struct reader *r)
{
	struct reader_cache_change	*rcc = NULL;
	struct cache_change		*cc = NULL;

	if (r == NULL) {
		return NULL;
	}

	cc = hc_get_first_cc(&r->history);
	if(cc != NULL){
		rcc = to_reader_cache_change(cc);
	}

	return rcc;
}

/* Remove the sample with min SN in this history cache */
void reader_cache_del_oldest_cc(struct reader *r)
{
	struct reader_cache_change	*rcc;
	struct cache_change		*cc;

	cc = hc_pop_first_cc(&r->history);

	if (cc == NULL) {
		return ;
	}

	rcc = to_reader_cache_change(cc);

	reader_cache_change_free(rcc);
}

struct rtps_sn reader_cache_get_max_sn_with_wproxy(struct reader *r,
						   struct writer_proxy *proxy)
{
	struct cache_change *cc;
	struct reader_cache_change *rcc;

	if ((r == NULL) || hc_is_empty(&r->history) || (proxy == NULL)) {
		return RTPS_SN_UNKNOWN;
	}

	mvbs_list_for_each_pre_entry(cc, &r->history.caches, history_node) {
		rcc = to_reader_cache_change(cc);

		if (rcc->source == proxy) {
			return cc->sn;
		}
	}

	return RTPS_SN_UNKNOWN;
}

void reader_cache_remove_cc_with_wproxy(struct reader *r,
					struct writer_proxy *proxy)
{
	struct cache_change		*cc;
	struct reader_cache_change	*rcc;

	if ((r == NULL) || hc_is_empty(&r->history) || (proxy == NULL)) {
		return ;
	}

	mvbs_list_for_each_pre_entry(cc, &r->history.caches, history_node) {
		rcc = to_reader_cache_change(cc);

		if (rcc->source == proxy) {
			rcc->source = NULL;

			/* FIXME: This remove is not safe !!! */
			reader_cache_change_destroy(rcc);
		}
	}
}

void reader_cache_update_on_wproxy_offline(struct reader *r,
					   struct writer_proxy *proxy)
{
	struct cache_change *cc;
	struct reader_cache_change *rcc;

	if ((r == NULL) || hc_is_empty(&r->history) || (proxy == NULL)) {
		return ;
	}

	mvbs_list_for_each_pre_entry(cc, &r->history.caches, history_node) {
		rcc = to_reader_cache_change(cc);

		if (rcc->source == proxy) {
			rcc->source = NULL;
		}
	}
}

void reader_cache_add_cc(struct reader *r, struct reader_cache_change *new_cc)
{
	struct history_cache		*hc;
	struct reader_cache_change	*rcc = NULL;
	struct cache_change		*cc = NULL;
	bool insert = false;

	if ((r == NULL) || (new_cc == NULL)) {
		return;
	}

	hc = &r->history;

	mvbs_list_for_each_pre_entry(cc, &hc->caches, history_node){
		rcc = to_reader_cache_change(cc);

		if (rcc->source == new_cc->source) {
			if (rtps_sn_lessequal(&rcc->cc.sn, &new_cc->cc.sn)) {
				insert = true;
				break;
			}
		} else {
			if (duration_greater(&new_cc->ts_sent, &rcc->ts_sent)) {
				insert = true;
				break;
			}
		}
	}

	if (insert) {
		mvbs_list_add(&new_cc->cc.history_node, &rcc->cc.history_node);
	} else {
		mvbs_list_add(&new_cc->cc.history_node, &hc->caches);
	}

	mvbs_get_time(&(new_cc->cc.ts.seconds), &(new_cc->cc.ts.nanosec));
}

void reader_cache_clean(struct reader *r)
{
	struct reader_cache_change	*rcc;
	struct cache_change		*cc = NULL, *tmp = NULL;

	mvbs_list_for_each_entry_safe(cc, tmp, &r->history.caches, history_node) {
		mvbs_list_del(&cc->history_node);

		rcc = to_reader_cache_change(cc);

		reader_cache_change_free(rcc);
	}
}

int32_t reader_cache_init(struct reader *r, uint32_t sample_size)
{
	int32_t ret = -ERR_NOMEM;

#if 0
	const endpoint_attr_t *attr;
	uint32_t cache_size;
	uint16_t samples;

	attr = &(r->attr->ep_attr);

	samples = attr->resource_limit.max_samples;

	if (attr->qos.history_kind == (uint16_t)KEEP_LAST) {
		samples = attr->history.depth;

		if (reader_has_key(r)) {
			samples *= attr->resource_limit.max_instances;
		}
	}

	cache_size = sizeof(struct reader_cache_change) + sample_size;

	ret = mem_pool_init(reader_get_cc_pool(r), cache_size, samples);
	if (ret != 0) {
		pr_err(ret, "Fail to init cc pool of reader: %d\n", samples);

		history_cache_deinit(&r->history);

		return ret;
	}
#else
	(void)sample_size;

	ret = mem_pool_reset(reader_get_cc_pool(r));
	if (ret != 0) {
		pr_err(ret, "Fail to init reader cache change pool of [%s].",
						reader_get_topicname(r));

		return ret;
	}
#endif

	history_cache_init(&r->history);

	return 0;
}

uint16_t reader_cache_deinit(struct reader *r)
{
	uint16_t cnt = 0;

	reader_cache_clean(r);

	cnt = hc_get_cur_count(&r->history);

#if 0
	history_cache_deinit(&r->history);
#endif
	if (cnt != 0) {
		pr_err(ERR_FAULT, "Reader [%s] history cache leak %d.",
			reader_get_topicname(r), cnt);
	}

	return cnt;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
