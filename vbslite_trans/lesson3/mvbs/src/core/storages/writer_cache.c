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

#include <mvbs/utils/time.h>
#include <qos/e2e.h>

#define to_writer_cache_change(cache)				\
	container_of(cache, struct writer_cache_change, cc)


struct writer_cache_change *writer_cache_get_oldest_cc(struct writer *w)
{
	struct writer_cache_change *wcc = NULL;
	struct cache_change *cc = NULL;

	cc = hc_get_first_cc(&w->history);
	if (cc != NULL) {
		wcc = to_writer_cache_change(cc);
	}

	return wcc;
}

struct writer_cache_change *writer_cache_get_cc(struct writer *w,
						struct rtps_sn sn)
{
	struct cache_change *cc = NULL;
	struct writer_cache_change *wcc = NULL;

	if (w == NULL) {
		return wcc;
	}

	cc = hc_get_cc_by_sn(&w->history, sn);

	if (cc != NULL) {
		wcc = to_writer_cache_change(cc);
	}

	return wcc;
}

void writer_cache_add_cc(struct writer *w, struct writer_cache_change *wcc)
{
	struct history_cache	*hc;
	struct cache_change	*cc;

	if ((w == NULL) || (wcc == NULL)) {
		return ;
	}

	hc = &w->history;
	cc = &wcc->cc;

	mvbs_list_add_tail(&cc->history_node, &hc->caches);

	rtps_sn_increase(&(w->last_used_sn));

	cc->sn = w->last_used_sn;

	mvbs_get_time(&(cc->ts.seconds), &(cc->ts.nanosec));
}

static void writer_cache_release_cc(struct cache_change *cc)
{
	struct writer_cache_change *wcc;

	wcc = to_writer_cache_change(cc);

	writer_cache_free_cc(wcc);
}

void writer_cache_del_cc_upto(struct writer *w, struct rtps_sn seq_num)
{
	if (w == NULL) {
		return;
	}

	hc_del_changes_upto(&w->history, seq_num, writer_cache_release_cc);
}

/* Remove the min from historycache */
void writer_cache_del_oldest_cc(struct writer *w)
{
	struct writer_cache_change	*wcc;
	struct cache_change		*cc;
	struct rtps_sn		old_min;

	if (writer_is_stateful(w)) {
		old_min = hc_get_min_seq(&w->history);
		sfwriter_change_removed_by_history(w, &old_min);
	}

	cc = hc_pop_first_cc(&w->history);
	if (cc != NULL) {
		wcc = to_writer_cache_change(cc);
		writer_cache_free_cc(wcc);
	}
}

void writer_cache_clean(struct writer *w)
{
	struct writer_cache_change	*wcc;
	struct cache_change		*cc = NULL, *tmp = NULL;

	mvbs_list_for_each_entry_safe(cc, tmp, &w->history.caches, history_node) {
		mvbs_list_del(&cc->history_node);

		wcc = to_writer_cache_change(cc);

		writer_cache_free_cc(wcc);
	}
}

int32_t writer_cache_init(struct writer *w, uint32_t sample_size)
{
	int32_t ret = -ERR_NOMEM;
#if 0
	const endpoint_attr_t *writer_ep;
	uint16_t samples;
	uint32_t blk_size = 0U;

	writer_ep = &(w->attr->ep_attr);

	/* Get nr samples, prepare to init cache change mempool */
	samples = writer_ep->resource_limit.max_samples;

	if (writer_ep->qos.history_kind == (uint16_t)KEEP_LAST) {
		samples = writer_ep->history.depth;

		if (writer_has_key(w)) {
			samples *= writer_ep->resource_limit.max_instances;
		}
	}

	blk_size = (uint32_t)sizeof(struct writer_cache_change) + sample_size;
	ret = mem_pool_init(writer_get_cache_change_pool(w), blk_size, samples);
	if (ret != 0) {
		pr_verb("Fail to init mem pool of writer's cache change: %d\n",
								     samples);
		history_cache_deinit(&w->history);
	}
#else
	(void)sample_size;

	ret = mem_pool_reset(writer_get_cache_change_pool(w));
	if (ret != 0) {
		pr_err(ret, "Fail to init writer cache change pool of [%s].",
						writer_get_topicname(w));

		return ret;
	}
#endif

	history_cache_init(&w->history);

	return ret;
}

uint16_t writer_cache_deinit(struct writer *w)
{
	uint16_t cnt = 0;

	writer_cache_clean(w);

	cnt = hc_get_cur_count(&w->history);

#if 0
	history_cache_deinit(&w->history);
#endif

	if (cnt != 0) {
		pr_err(ERR_FAULT, "Writer [%s] history cache leak %d.",
						writer_get_topicname(w), cnt);
	}

	return cnt;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
