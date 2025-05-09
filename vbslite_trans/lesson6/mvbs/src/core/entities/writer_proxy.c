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
#include <mvbs/utils/bitmap.h>
#include <mvbs/utils/timer.h>
#include <mvbs/utils/log.h>

#if WRITER_PROXY_VERBOSE || RTPS_GLOBAL_VERBOSE
#undef MVBSLOG_LEVEL
#define MVBSLOG_LEVEL MVBSLOG_VERB
#endif

/*
 * In Page65 of DDS-RTPS-v2.5-21-03-03.pdf, there is following description:
 *
 * Example 1. A Writer that has never written any samples before sending a
 * Heartbeat will send a Heartbeat with firstSN.value = 1, lastSN.value = 0.
 *
 * Example 4. A Writer that has written 10 samples before sending a Heartbeat
 * but does not have any samples available at the time of the Heartbeat will
 * send a Heartbeat with firstSN.value = 11, lastSN.value = 10.
 *
 * In this case (firstSN - 1 == lastSN), it means that the writer history is
 * empty, firstSN will be the SN of next sample.
 */
static bool writer_empty_lost_changes_update(struct writer_proxy *wproxy,
					     const struct rtps_sn *first_sn,
					     const struct rtps_sn *last_sn)
{
	struct rtps_sn last_send = rtps_sn_sub_value(first_sn, 1);

	if (!rtps_sn_equal(&last_send, last_sn)) {
		return false;
	}

	uint16_t received_map_size = writer_proxy_get_received_map_size(wproxy);
	ulong_t *received_map	   = writer_proxy_get_received_map(wproxy);

	if (rtps_sn_less(&wproxy->missing_lowmark, last_sn)) {
		wproxy->missing_lowmark = *last_sn;

		mvbs_memzero(received_map, received_map_size);

		if (rtps_sn_less(&wproxy->max_sn, last_sn)) {
			wproxy->max_sn = *last_sn;
		}
	}

	return true;
}

static uint16_t writer_get_lost_count(struct writer_proxy *wproxy, uint16_t bit_offset)
{
	uint16_t offset = bit_offset, idx, wcnt = 0;

	ulong_t *received_map = writer_proxy_get_received_map(wproxy);

	for (idx = 0; idx < (offset / BITS_PER_ULONG); idx++) {
		wcnt += hweight_ulong(received_map[idx]);
	}

	if ((offset % BITS_PER_ULONG) != 0U) {
		wcnt += hweight_ulong(received_map[idx] &
					    BITMAP_LAST_WORD_MASK(offset));
	}

	return bit_offset - wcnt;
}

uint16_t writer_proxy_lost_changes_update(struct writer_proxy *wproxy,
					  const struct rtps_sn *first_sn,
					  const struct rtps_sn *last_sn)
{
	struct rtps_sn first_missing;
	struct rtps_sn offset;
	size_t shift;
	uint16_t lost_count = 0U;

	if ((wproxy == NULL) || (first_sn == NULL) || (last_sn == NULL)) {
		return lost_count;
	}

	if (writer_empty_lost_changes_update(wproxy, first_sn, last_sn)) {
		/* FIXME: The lost_count is not exactly. */
		return lost_count;
	}

	uint16_t bitmap_size  = writer_proxy_get_received_map_size(wproxy) * 8;
	ulong_t *received_map = writer_proxy_get_received_map(wproxy);

	/*
	 * In Page65 of DDS-RTPS-v2.5-21-03-03.pdf, there is following
	 * description:
	 *
	 * Example 2. A Writer that has only one sample in its cache with
	 * sequence number SN will send a Heartbeat with
	 * firstSN.value = lastSN.value = SN.
	 *
	 * Example 3. A Writer that has written 10 samples and still has the
	 * last 5 samples in its cache will send a Heartbeat with
	 * firstSN.value = 6, lastSN.value = 10.
	 *
	 * In this case (firstSN - 1 == lastSN), it means that the writer
	 * history is empty, firstSN will be the SN of next sample.
	 */

	first_missing = rtps_sn_add_value(&wproxy->missing_lowmark, 1);

	if (rtps_sn_less(&first_missing, first_sn)) {
		offset = rtps_sn_sub(first_sn, &first_missing);

		if ((offset.high > 0) || (offset.low >= bitmap_size)) {
			/* FIXME: why not mvbs_memzero this bitmap !! */

			/*
			 * If the firstSN is too large, clear the bitmap, then
			 * update the missing_lowmark according to the firstSN
			 * value.
			 */
			bitmap_shift_right(received_map, received_map,
					   bitmap_size, bitmap_size);

			/* FIXME:
			 * lost_count += bitmap_size - offset.low
			 */
			lost_count = writer_get_lost_count(wproxy, bitmap_size);

			wproxy->missing_lowmark = rtps_sn_sub_value(first_sn, 1);
		} else {
			/*
			 * The fistSN value is inside the bitmap range, find the
			 * first zero bit from the firstSN bit. Which means:
			 * - If the firstSN bit is 0, clear the lower bits, then
			 *   update the missing_lowmark according to the firstSN
			 * - If the firstSN bit is 1, find the next zero bit, which
			 *   will be the new firstMissing sn.
			 */
			lost_count = writer_get_lost_count(wproxy, (uint16_t)offset.low);

			shift = find_next_zero_bit(received_map, bitmap_size,
						   offset.low);

			bitmap_shift_right(received_map, received_map, shift,
					   bitmap_size);

			wproxy->missing_lowmark = rtps_sn_add_value(
						&wproxy->missing_lowmark, shift);

		}
	}

	if (rtps_sn_less(&wproxy->max_sn, last_sn)) {
		wproxy->max_sn = *last_sn;
	}

	return lost_count;
}

bool writer_proxy_need_send_ack(struct writer_proxy *wproxy)
{
	size_t last;

	if (wproxy == NULL) {
		return false;
	}

	uint16_t bitmap_size  = writer_proxy_get_received_map_size(wproxy) * 8;
	ulong_t *received_map = writer_proxy_get_received_map(wproxy);

	last = find_last_bit(received_map, bitmap_size);

	if ((last != bitmap_size) && (last > (bitmap_size / 2UL))) {
		return true;
	}

	return false;
}

static bool writer_proxy_received_the_first(const struct writer_proxy *wproxy)
{
	if ((wproxy->hb_count == 0) && rtps_sn_equal_zero(&wproxy->max_sn)) {
		return true;
	}

	return false;
}

bool writer_proxy_set_received_change(struct writer_proxy *wproxy,
				      const struct rtps_sn *seq_num)
{
	struct rtps_sn first_missing;
	struct rtps_sn offset;
	uint32_t shift;

	if ((wproxy == NULL) || (seq_num == NULL)) {
		return false;
	}

	uint16_t bitmap_size  = writer_proxy_get_received_map_size(wproxy) * 8;
	ulong_t *received_map = writer_proxy_get_received_map(wproxy);

	if (writer_proxy_received_the_first(wproxy)) {
		/* FIXME:
		 * if the sn of the firstdata is bigger then (bitmap_size / 2),
		 * set the missing_lowmark to (seq_num - (bitmap_size / 2)), if the depth of
		 * the writer < (bitmap_size / 2), it always ok, the missing_lowmark
		 * will real update when received the heartbeat
		 */
		uint32_t firstdata_sn = bitmap_size / 2;
		if (rtps_sn_to_int64(seq_num) > (int64_t)(firstdata_sn)) {
			wproxy->missing_lowmark = rtps_sn_sub_value(seq_num, (bitmap_size / 2));
		}
	}

	first_missing = rtps_sn_add_value(&wproxy->missing_lowmark, 1);

	if (rtps_sn_less(seq_num, &first_missing)) {
		return false;
	}

	offset = rtps_sn_sub(seq_num, &first_missing);
	shift = offset.low;

	uint32_t bitmap_range = bitmap_size - 1U;
	/* If will be the last element, insert it at the end. */
	if (rtps_sn_less(&wproxy->max_sn, seq_num)) {
		/* If it is the next to be acknowledeg, not insert */
		if (rtps_sn_equal(seq_num, &first_missing)) {
			(void)rtps_sn_increase(&wproxy->missing_lowmark);
		} else {
			if ((offset.high > 0) || (shift > bitmap_range)) {
				pr_err(ERR_FAULT, "can not set in received bitmap\n");
				return false;
			}

			bitmap_set_bit(shift, received_map);
		}

		wproxy->max_sn = *seq_num;
	} else {
		/* Check if it is next to the last acknowledged */
		if (rtps_sn_equal(seq_num, &first_missing)) {
			size_t index;

			bitmap_set_bit(0, received_map);
			index = find_first_zero_bit(received_map, bitmap_size);
			bitmap_shift_right(received_map, received_map, index,
								bitmap_size);
			wproxy->missing_lowmark =
					rtps_sn_add_value(&wproxy->missing_lowmark, index);

		} else {
			if ((offset.high > 0) || (shift > bitmap_range)) {
				pr_err(ERR_FAULT, "can not set in received bitmap\n");
				return false;
			}

			/* Check if already received */
			if (bitmap_test_bit(shift, received_map)) {
				return false;
			}

			bitmap_set_bit(shift, received_map);
		}
	}

	return true;
}

struct rtps_sn_set writer_proxy_get_missing(struct writer_proxy *wproxy)
{
	struct rtps_sn		first_missing;
	struct rtps_sn		max_missing;
	struct rtps_sn		max_limit;
	struct rtps_sn		seq;
	struct rtps_sn_set	sns;
	size_t bit = 0;

	first_missing = rtps_sn_add_value(&wproxy->missing_lowmark, 1);
	max_missing   = rtps_sn_add_value(&wproxy->max_sn, 1);
	max_limit     = rtps_sn_add_value(&first_missing, SNS_NUM_BITS);

	uint16_t bitmap_size  = writer_proxy_get_received_map_size(wproxy) * 8;
	ulong_t *received_map = writer_proxy_get_received_map(wproxy);

	if (rtps_sn_less(&max_limit, &max_missing)) {
		max_missing = max_limit;
	}

	rtps_sn_set_init(&sns, &first_missing);

	for_each_bit(bit, received_map, bitmap_size) {
		seq = rtps_sn_add_value(&wproxy->missing_lowmark,
						(uint32_t)(bit + 1UL));

		rtps_sn_set_add_range(&sns, &first_missing, &seq);

		bit = find_next_zero_bit(received_map, bitmap_size, bit);

		first_missing = rtps_sn_add_value(&wproxy->missing_lowmark,
								bit + 1UL);

		if (rtps_sn_lessequal(&max_missing, &first_missing)) {
			struct rtps_sn offset;

			offset = rtps_sn_sub(&max_missing, &sns.base);
			if ((offset.high == 0) && (offset.low <= SNS_NUM_BITS)) {
				sns.num_bits = offset.low;
			}

			break;
		}
	}

	if (rtps_sn_less(&first_missing, &max_missing)) {
		rtps_sn_set_add_range(&sns, &first_missing, &max_missing);
	}

	return sns;
}

void writer_proxy_init(struct writer_proxy *wproxy,
		       struct participant_proxy *ptcp_proxy,
		       struct rtps_entity_id eid, uint32_t strength)
{
	if ((ptcp_proxy == NULL) && (wproxy == NULL)) {
		return;
	}

	wproxy->ptcp_proxy		= ptcp_proxy;
	wproxy->eid			= eid;

	rtps_sn_set_value(&wproxy->missing_lowmark, 0);
	rtps_sn_set_value(&wproxy->max_sn, 0);

	wproxy->acknack_count		= 1;
	wproxy->hb_count			= 0;

	wproxy->owner_strength		= (uint16_t)strength;

	wproxy->liveliness_td		= TIMER_DESC_INVALID;

	wproxy->e2e_first_rcv		= true;
	wproxy->last_e2e_err_flag	= false;
	wproxy->last_e2e_count		= 0;

	uint16_t received_map_size = writer_proxy_get_received_map_size(wproxy);
	ulong_t *received_map      = writer_proxy_get_received_map(wproxy);

	mvbs_memzero(received_map, received_map_size);
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
