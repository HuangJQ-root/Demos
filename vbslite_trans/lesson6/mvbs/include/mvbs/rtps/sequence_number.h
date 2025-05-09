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

#ifndef MVBS_RTPS_SEQUENCE_NUMBER_H
#define MVBS_RTPS_SEQUENCE_NUMBER_H

#include <mvbs/base_type.h>

struct rtps_sn {
	int32_t		high;
	uint32_t	low;
};

typedef struct rtps_sn		rtps_sn_t;

extern const struct rtps_sn	RTPS_SN_UNKNOWN;

#define RTPS_SEQUENCE_NUMBER(sn)				\
	(struct rtps_sn) {					\
		.high = (int32_t)(((uint64_t)sn) >> 32),	\
		.low  = (uint32_t)sn,				\
	}

static inline int64_t rtps_sn_to_int64(const struct rtps_sn *sn)
{
	uint64_t ret = 0;

	ret = ((uint64_t)sn->high << 32U) | (uint64_t)sn->low;

	return (int64_t)ret;
}

static inline void rtps_sn_set_value(struct rtps_sn *sn, int64_t value)
{
	sn->high = (int32_t)(((uint64_t)value) >> 32);
	sn->low  = (uint32_t)value;
}

static inline bool rtps_sn_is_invalid(struct rtps_sn *sn)
{
	return (uint64_t)rtps_sn_to_int64(sn) >= 0xFFFFFFFF00000000ULL;
}

static inline void rtps_sn_set_zero(struct rtps_sn *sn)
{
	sn->high = 0;
	sn->low	 = 0;
}

static inline bool rtps_sn_equal(const struct rtps_sn *sn1,
				 const struct rtps_sn *sn2)
{
	return (sn1->high == sn2->high) && (sn1->low == sn2->low);
}

static inline bool rtps_sn_equal_zero(const struct rtps_sn *sn)
{
	return (sn->high == 0) && (sn->low == 0);
}

static inline bool rtps_sn_less(const struct rtps_sn *sn1,
				const struct rtps_sn *sn2)
{
	return (sn1->high < sn2->high) ||
		((sn1->high == sn2->high) && (sn1->low < sn2->low));
}

static inline bool rtps_sn_lessequal(const struct rtps_sn *sn1,
				     const struct rtps_sn *sn2)
{
	return (rtps_sn_less(sn1, sn2) || rtps_sn_equal(sn1, sn2));
}

static inline void rtps_sn_increase(struct rtps_sn *sn)
{
	sn->low++;

	if (sn->low == 0u) {
		sn->high++;
	}
}

static inline struct rtps_sn rtps_sn_add_value(const struct rtps_sn *sn,
					       uint32_t inc)
{
	int64_t value;

	value = rtps_sn_to_int64(sn);

	value += (int64_t)inc;

	return RTPS_SEQUENCE_NUMBER(value);
}

static inline struct rtps_sn rtps_sn_sub_value(const struct rtps_sn *sn,
					       uint32_t inc)
{
	int64_t value;

	value = rtps_sn_to_int64(sn);

	if (value < (int64_t)inc) {
		return RTPS_SN_UNKNOWN;
	}

	value -= (int64_t)inc;

	return RTPS_SEQUENCE_NUMBER(value);
}

/* sn1 - sn2 */
static inline struct rtps_sn rtps_sn_sub(const struct rtps_sn *sn1,
					 const struct rtps_sn *sn2)
{
	struct rtps_sn ret;

	if (rtps_sn_less(sn1, sn2)) {
		ret = RTPS_SN_UNKNOWN;
	} else {
		if (sn1->low >= sn2->low) {
			ret.high = sn1->high - sn2->high;
			ret.low  = sn1->low  - sn2->low;
		} else {
			ret.high = sn1->high - sn2->high - 1;
			ret.low  = 0xFFFFFFFFu - (sn2->low - sn1->low - 1u);
		}
	}

	return ret;
}

#include <mvbs/utils/cdefs.h>
#include <mvbs/utils/bitmap.h>

#include <mvbs/utils/log.h>

#define SNS_NUM_BITS			256u
#define SNS_NITEMS			((SNS_NUM_BITS + 31u) / 32u)

struct rtps_sn_set {
	struct rtps_sn	base;

	uint32_t num_bits;
	uint32_t bitmap[SNS_NITEMS];
};

typedef struct rtps_sn_set		rtps_sn_set_t;

static inline void rtps_sn_set_dump(const struct rtps_sn_set *sn_set)
{
	uint32_t word = 0;

	pr_info("sn_set.base     = %d", (uint32_t)rtps_sn_to_int64(&sn_set->base));
	pr_info("sn_set.num_bits = %d", sn_set->num_bits);

	word = BIT_WORD(sn_set->num_bits + BITS_PER_ULONG - 1);

	for (uint32_t i = 0; i < word; i++) {
		pr_info("sn_set.bitmap[%d] = %08X", i, sn_set->bitmap[i]);
	}
}

static inline void rtps_sn_set_init(struct rtps_sn_set *sn_set,
				    const struct rtps_sn *firstMissing)
{
	if (firstMissing != NULL) {
		sn_set->base = *firstMissing;
	} else {
		rtps_sn_set_zero(&sn_set->base);
	}

	sn_set->num_bits = 0;

	for (uint32_t i = 0; i < ARRAY_SIZE(sn_set->bitmap); i++) {
		sn_set->bitmap[i] = 0;
	}
}

static inline bool rtps_sn_set_is_valid(const struct rtps_sn_set *sn_set,
					uint32_t bit)
{
	if (bit >= SNS_NUM_BITS) {
		return true;
	}

	uint8_t bucket	= (uint8_t)(bit / sizeof(__typeof__(sn_set->bitmap)));
	uint8_t pos	= (uint8_t)(bit % sizeof(__typeof__(sn_set->bitmap)));

	return (sn_set->bitmap[bucket] & ((uint32_t)1 << ((uint32_t)31 - (uint32_t)pos))) != 0u;
}

static inline void rtps_sn_set_set_bit(struct rtps_sn_set *sn_set, uint32_t bit)
{
	uint8_t bucket	= (uint8_t)(bit / sizeof(__typeof__(sn_set->bitmap)));
	uint8_t pos	= (uint8_t)(bit % sizeof(__typeof__(sn_set->bitmap)));

	sn_set->bitmap[bucket] |= ((uint32_t)1 << ((uint32_t)31 - (uint32_t)pos));
}

static inline void rtps_sn_set_add(struct rtps_sn_set *sn_set,
				   const struct rtps_sn *item)
{
	int64_t sn_set_base;
	int64_t sn_set_limit;
	int64_t sn_set_item;

	uint8_t bit;

	sn_set_base  = rtps_sn_to_int64(&sn_set->base);
	sn_set_item  = rtps_sn_to_int64(item);
	sn_set_limit = sn_set_base + (int64_t)SNS_NUM_BITS;

	/*      |---------------*-------------------|
	 *      ^               ^                   ^
	 *    base             item                limit
	 */

	/* if item out of range, exit */
	if ((sn_set_item < sn_set_base) || (sn_set_item > sn_set_limit)) {
		return ;
	}

	bit = (uint8_t)sn_set_item - (uint8_t)sn_set_base;

	uint8_t bucket	= (uint8_t)(bit / sizeof(__typeof__(sn_set->bitmap)));
	uint8_t pos	= (uint8_t)(bit % sizeof(__typeof__(sn_set->bitmap)));

	sn_set->bitmap[bucket] |= ((uint32_t)1 << ((uint32_t)31 - (uint32_t)pos));

	if (sn_set->num_bits < ((uint32_t)bit + 1u)) {
		sn_set->num_bits = (uint32_t)bit + 1u;
	}

	return ;
}

static inline void rtps_sn_set_add_range(struct rtps_sn_set *sn_set,
					 const struct rtps_sn *from,
					 const struct rtps_sn *to)
{
	int64_t base  = rtps_sn_to_int64(&sn_set->base);
	int64_t start = rtps_sn_to_int64(from);
	int64_t end   = rtps_sn_to_int64(to);

	if (start < base) {
		start = base;
	}

	if (end > (base + (int64_t)SNS_NUM_BITS)) {
		end = base + (int64_t)SNS_NUM_BITS;
	}


	if (end <= start) {
		return ;
	}

	if (sn_set->num_bits < ((uint32_t)end - (uint32_t)base)) {
		sn_set->num_bits = ((uint32_t)end - (uint32_t)base);
	}

	bitmap_set_bits(sn_set->bitmap, ((size_t)start - (size_t)base),
					((size_t)end - (size_t)start));
}

#endif /* !__MVBS_RTPS_SEQUENCE_NUMBER_H__ */
