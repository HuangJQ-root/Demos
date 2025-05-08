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
#include <mvbs/utils/mm.h>

struct history_cache *history_cache_alloc(void)
{
	struct history_cache *hc;

	hc = (struct history_cache *)mvbs_malloc(sizeof(struct history_cache), 0);
	if (hc == NULL) {
		return NULL;
	}

	history_cache_init(hc);

	return hc;
}

struct rtps_sn hc_get_min_seq(struct history_cache *hc)
{
	struct cache_change *fisrt;

	if ((hc == NULL) || hc_is_empty(hc)) {
		return RTPS_SN_UNKNOWN;
	}

	fisrt = mvbs_list_first_entry(&hc->caches, struct cache_change, history_node);

	return fisrt->sn;
}

struct rtps_sn hc_get_max_seq(struct history_cache *hc)
{
	struct cache_change *last;

	if ((hc == NULL) || hc_is_empty(hc)) {
		return RTPS_SN_UNKNOWN;
	}

	last = mvbs_list_last_entry(&hc->caches, struct cache_change, history_node);

	return last->sn;
}

struct rtps_sn hc_get_next_seq(struct history_cache *hc,
				struct rtps_sn sn)
{
	struct cache_change *cc;
	struct rtps_sn max_sn;
	struct rtps_sn min_sn;

	if (hc == NULL) {
		return RTPS_SN_UNKNOWN;
	}

	max_sn = hc_get_max_seq(hc);
	min_sn = hc_get_min_seq(hc);

	if (rtps_sn_less(&sn, &min_sn)
			|| rtps_sn_lessequal(&max_sn, &sn)) {
		return RTPS_SN_UNKNOWN;
	}

	mvbs_list_for_each_entry(cc, &hc->caches, history_node) {
		if (rtps_sn_equal(&cc->sn, &sn)) {
			struct cache_change  *next =
					mvbs_list_next_entry(cc, history_node);

			return next->sn;
		}
	}

	return RTPS_SN_UNKNOWN;
}

struct cache_change *hc_pop_first_cc(struct history_cache *hc)
{
	struct cache_change *first;

	if ((hc == NULL) || hc_is_empty(hc)) {
		return NULL;
	}

	/* the tail one is the first in list */
	first = mvbs_list_first_entry(&hc->caches,
				struct cache_change, history_node);

	mvbs_list_del(&first->history_node);

	return first;
}


void hc_del_changes_upto(struct history_cache *hc, struct rtps_sn sn,
						   cache_change_release cc_free)
{
	struct cache_change *cc = NULL, *tmp = NULL, *tail;
	struct rtps_sn max_sn = hc_get_max_seq(hc);

	if ((hc == NULL) || hc_is_empty(hc)) {
		return;
	}

	if (rtps_sn_less(&max_sn, &sn)) {
		mvbs_list_for_each_entry_safe(cc, tmp, &hc->caches, history_node) {
			mvbs_list_del(&cc->history_node);

			cc_free(cc);
		}

		return;
	}

	tail = mvbs_list_last_entry(&hc->caches, struct cache_change, history_node);

	while (rtps_sn_less(&tail->sn, &sn)) {
		cc_free(hc_pop_first_cc(hc));

		tail = mvbs_list_last_entry(&hc->caches, struct cache_change, history_node);
	}
}

struct cache_change *hc_get_first_cc(struct history_cache *hc)
{
	struct cache_change *cc;

	if ((hc == NULL) || hc_is_empty(hc)) {
		return NULL;
	}

	/* the oldest in the first of the list */
	cc = mvbs_list_first_entry(&hc->caches, struct cache_change, history_node);

	return cc;
}

/* FIXME:
 * For writer history cache, there is only one CC which has the SN.
 * For reader history cache, there maybe sevaral CCs which have the SN.
 * Currently, this interface only for writer.
 */
struct cache_change *hc_get_cc_by_sn(struct history_cache *hc,
				     struct rtps_sn sn)
{
	struct cache_change	*cc;
	struct rtps_sn	max_sn;
	struct rtps_sn	min_sn;

	if (hc == NULL) {
		return NULL;
	}

	max_sn = hc_get_max_seq(hc);
	min_sn = hc_get_min_seq(hc);

	if (rtps_sn_less(&sn, &min_sn)
				|| rtps_sn_less(&max_sn, &sn)) {
		return NULL;
	}

	mvbs_list_for_each_entry(cc, &hc->caches, history_node) {
		if (rtps_sn_equal(&cc->sn, &sn)) {
			return cc;
		}
	}

	return NULL;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
