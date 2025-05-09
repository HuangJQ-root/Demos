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
#include <mvbs/utils/log.h>
#include <messages/message_factory.h>
#include <discovery/dpse.h>
#include <discovery/sddp.h>

#if 0
#undef  MVBSLOG_LEVEL
#define MVBSLOG_LEVEL MVBSLOG_VERB
#endif

void buildin_reader_proxy_init(struct buildin_reader_proxy *proxy,
				      bool reliable,
				      uint8_t durabilityKind)
{
	mvbs_memzero(proxy, sizeof(*proxy));

	proxy->acknack_count	= -1; /* Used to filter-out repeat acknack */

	proxy->durability_kind	= durabilityKind;
	proxy->reliable		= reliable;

	proxy->start_sn		= 1;
	proxy->avail_bits	= 0;
}

void buildin_writer_proxy_init(struct buildin_writer_proxy *proxy)
{
	mvbs_memzero(proxy, sizeof(*proxy));

	proxy->heartbeat_count	= -1; /* Used to filter-out repeat heartbeat */
	proxy->acknack_count	= 1;  /* Used to send acknack count */

	proxy->start_sn		= 1;
	proxy->avail_bits	= 0;
}


#if 0
static void buildin_writer_proxy_refine(struct buildin_writer_proxy *proxy)
{
	uint16_t wincnt	= 0;
	uint16_t offset	= 0;
	uint16_t i	= 0;
	uint16_t j	= 0;

	uint8_t  *bitmap = (uint8_t  *)proxy->recv_map;

	wincnt = proxy->avail_bits / BITS_PER_BYTE;

	for (i=0; i < wincnt; i++) {
		if (bitmap[i] != (uint8_t)(-1)) {
			break;
		}
	}

	if (i == 0) {
		return ;
	}

	offset = i;

	if ((proxy->avail_bits)%BITS_PER_BYTE) {
		wincnt++;
	}

	for (i=0; i < wincnt - offset; i++) {
		bitmap[i] = bitmap[i+offset];
	}

	for (j=0; j < offset; j++, i++) {
		bitmap[i] = 0;
	}

	proxy->start_sn	   = offset*BITS_PER_BYTE;
	proxy->avail_bits -= offset*BITS_PER_BYTE;

	return ;
}
#endif


void buildin_writer_proxy_set_sn(struct buildin_writer_proxy *proxy,
				        const struct rtps_sn *sn)
{
	uint16_t offset;
	int64_t  first_sn;
	int64_t  data_sn;

	first_sn = proxy->start_sn;
	data_sn  = rtps_sn_to_int64(sn);

	offset = data_sn - first_sn;

	pr_verb("first_sn: %d, avail_bits: %d", (uint32_t)first_sn,
		  				proxy->avail_bits);
	pr_verb("0x%08X  0x%08X 0x%08X", proxy->recv_map[0],
					 proxy->recv_map[1],
					 proxy->recv_map[2]);

	pr_debug("Recv Data SN: %d, bit offset: %d", (uint32_t)data_sn,
								offset);

	if (proxy->avail_bits < offset + 1) {
		proxy->avail_bits = offset + 1;
	}

	bitmap_set_bit_be(offset, proxy->recv_map);

	pr_verb("first_sn: %d, avail_bits: %d", (uint32_t)first_sn,
		  				proxy->avail_bits);
	pr_verb("0x%08X  0x%08X 0x%08X", proxy->recv_map[0],
					 proxy->recv_map[1],
					 proxy->recv_map[2]);
}

bool buildin_writer_proxy_test_sn(struct buildin_writer_proxy *proxy,
				        const struct rtps_sn *sn)
{
	uint16_t offset;
	int64_t  first_sn;
	int64_t  data_sn;

	first_sn = proxy->start_sn;
	data_sn  = rtps_sn_to_int64(sn);

	if (data_sn < first_sn) {
		return true;
	}

	offset = data_sn - first_sn;

	if (offset > proxy->avail_bits) {
		return false;
	}

	return bitmap_test_bit_be(offset, proxy->recv_map);
}

uint16_t buildin_writer_proxy_to_sn_set(struct buildin_writer_proxy *proxy,
					       struct rtps_sn_set *set,
					       uint16_t max_bits)
{
	uint16_t count		= 0;
	uint16_t start		= 0;
	uint16_t end		= 0;
	uint16_t start_w	= 0;
	uint16_t end_w		= 0;
	uint16_t i		= 0;

	pr_verb("avail_bits: %d, proxy->recv_map: 0x%08lX 0x%08lX 0x%08lX",
					proxy->avail_bits,
					proxy->recv_map[0],
					proxy->recv_map[1],
					proxy->recv_map[2]);


	for (i=0; i<proxy->avail_bits; i++) {
		if (bitmap_test_bit_be(i, proxy->recv_map)) {
			/* bit 1 indicate this package has been received */
			continue;
		}

		start = i;
		end   = i;
		count = 1;
		break;
	}

	for (i++; i<proxy->avail_bits; i++) {
		if (bitmap_test_bit_be(i, proxy->recv_map)) {
			/* bit 1 indicate this package has been received */
			continue;
		}

		count++;

		/*
		 * FIX BUG: Continuously update 'end' to prevent 'start = end'
		 * when 'proxy->avail_bits - i > max_bits'
		 * Usage:   Prevent one-by-one requests when the quantity of the remaining
		 * requested EDPs is less than max_bits.
		 */
		end = i;

		if (count >= max_bits) {
			end = i;
			break;
		}
	}

	pr_verb("start: %d, end :%d, count: %d",start, end, count);

	start_w = BIT_WORD(start);
	end_w   = BIT_WORD(end);

	rtps_sn_set_value(&set->base, proxy->start_sn + start_w * 32);

	i=0;

	for (; start_w < end_w; start_w++) {
		set->bitmap[i] = ~proxy->recv_map[start_w];
		i++;
	}

	pr_verb("start_w: %d, end_w :%d, i: %d",start_w, end_w, i);

	set->bitmap[i] = ~proxy->recv_map[start_w] &(~((1<<BIT_POS_MIRROR(BITMAP_BITS(end)))-1));
	set->num_bits = i*32 + BITMAP_BITS(end) + 1;

#if 0
	rtps_sn_set_dump(set);
#endif

	return count;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
