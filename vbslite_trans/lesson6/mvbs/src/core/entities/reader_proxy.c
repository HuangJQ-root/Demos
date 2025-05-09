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
#include <mvbs/errno.h>
#include <mvbs/utils/log.h>
#include <mvbs/rtps/sequence_number.h>

#if READER_PROXY_VERBOSE || RTPS_GLOBAL_VERBOSE
#undef MVBSLOG_LEVEL
#define MVBSLOG_LEVEL MVBSLOG_VERB
#endif

void reader_proxy_update_lowmark(struct reader_proxy *rproxy,
				 const struct rtps_sn *seq_num)
{
	if ((rproxy == NULL) || (seq_num == NULL) ||
	    (rproxy->flags.reliable == 0U)) {
		pr_err(ERR_INVALID, "Invalid parameter.");
		return;
	}

	rproxy->changes_lowmark = *seq_num;
}

void reader_proxy_add_change(struct reader_proxy *rproxy,
			     const struct rtps_sn *seq_num)
{
	struct rtps_sn offset;
	uint32_t shift;

	if ((rproxy == NULL) || (seq_num == NULL)
			     || (rproxy->flags.reliable == 0U)) {
		pr_err(ERR_INVALID, "Invalid parameter.");
		return;
	}

	if (rtps_sn_less(seq_num, &rproxy->changes_lowmark)) {
		pr_verb("CacheChange seq{0x%016llX} is smaller than LowMark{0x%016llX}.",
				rtps_sn_to_int64(seq_num),
				rtps_sn_to_int64(&rproxy->changes_lowmark));
		return;
	}

	offset = rtps_sn_sub(seq_num, &rproxy->changes_lowmark);

	size_t bitmap_range = reader_proxy_get_sent_map_size(rproxy) * 8 - 1U;
	if (rtps_sn_to_int64(&offset) > (int64_t)bitmap_range) {
		pr_err(ERR_FAULT, "Reader proxy add change err");
		return;
	}

	shift = (uint32_t)rtps_sn_to_int64(&offset);

	bitmap_set_bit(shift, reader_proxy_get_sent_map(rproxy));
}

void reader_proxy_del_change(struct reader_proxy *rproxy,
			     const struct rtps_sn *seq_num)
{
	struct rtps_sn offset;
	int64_t shift;
	uint32_t index;

	if ((rproxy == NULL) || (seq_num == NULL)
			     || (rproxy->flags.reliable == 0U)) {
		return;
	}

	if (rtps_sn_less(seq_num, &rproxy->changes_lowmark)) {
		return;
	}

	/* deleted change should be the oldest one */
	offset = rtps_sn_sub(seq_num, &rproxy->changes_lowmark);
	shift = rtps_sn_to_int64(&offset);

	rproxy->changes_lowmark = *seq_num;
	rtps_sn_increase(&rproxy->changes_lowmark);

	size_t bitmap_bytes = reader_proxy_get_sent_map_size(rproxy);
	size_t bitmap_size  = bitmap_bytes * 8;

	ulong_t *sent_map = reader_proxy_get_sent_map(rproxy);

	if ((shift < 0) || (shift > ((int64_t)bitmap_size - 1U))) {
		mvbs_memzero(sent_map, bitmap_bytes);
	} else {
		bitmap_shift_right(sent_map, sent_map,
				   (size_t)shift + 1U, bitmap_size);

		index = find_first_bit(sent_map, bitmap_size);
		if (index > 0UL) {
			bitmap_shift_right(sent_map, sent_map,
				   (uint32_t)index, bitmap_size);

			rproxy->changes_lowmark = rtps_sn_add_value(
						&rproxy->changes_lowmark,
						(uint32_t)index);
		}
	}

	pr_verb("new LowMark{%d.%u}.",
		rproxy->changes_lowmark.high, rproxy->changes_lowmark.low);
}

void reader_proxy_acked_changes_set(struct reader_proxy *rproxy,
				    const struct rtps_sn *seq_num)
{
	struct rtps_sn offset;
	int64_t shift;

	if ((rproxy == NULL) || (seq_num == NULL)
			     || (rproxy->flags.reliable == 0U)) {
		return;
	}

	if (!rtps_sn_less(&rproxy->changes_lowmark, seq_num)) {
		return ;
	}

	/* Remove all sent changes with a sequence lower than seq_num */
	offset = rtps_sn_sub(seq_num, &rproxy->changes_lowmark);
	shift  = rtps_sn_to_int64(&offset);

	size_t bitmap_bytes = reader_proxy_get_sent_map_size(rproxy);
	size_t bitmap_size  = bitmap_bytes * 8;
	ulong_t *sent_map = reader_proxy_get_sent_map(rproxy);

	if ((shift < 0) || (shift > ((int64_t)bitmap_size - 1U))) {
		mvbs_memzero(sent_map, bitmap_bytes);
	} else {
		bitmap_shift_right(sent_map, sent_map,
				(size_t)shift, bitmap_size);
	}

	/* Update low mark */
	rproxy->changes_lowmark = *seq_num;
	pr_verb("new LowMark{%d.%u}.",
		rproxy->changes_lowmark.high, rproxy->changes_lowmark.low);
}

void reader_proxy_init(struct reader_proxy *rproxy,
		       struct participant_proxy *ptcp_proxy,
		       const struct rtps_entity_id eid,
		       bool reliable,
		       uint8_t durability_kind)
{
	if (rproxy == NULL) {
		pr_err(ERR_INVALID, "proxy is null.");
		return;
	}

	mvbs_memzero(rproxy, sizeof(*rproxy));

	rproxy->ptcp_proxy		= ptcp_proxy;
	rproxy->eid			= eid;

	rproxy->acknack_count		= 0;

	rproxy->durability_kind		= durability_kind;

	rproxy->flags.reliable		= (reliable ? 1U : 0U);

	rtps_sn_set_value(&rproxy->changes_lowmark, 1);
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
