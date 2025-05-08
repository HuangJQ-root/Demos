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

#include <mvbs/utils/bitmap.h>
#include <mvbs/utils/mm.h>
#include <mvbs/utils/string.h>

/**
 * __bitmap_shift_left - logical left shift of the bits in a bitmap
 *   @dst : destination bitmap
 *   @src : source bitmap
 *   @shift : shift by this many bits
 *   @nbits : bitmap size, in bits
 *
 * Shifting left (multiplying) means moving bits in the LS -> MS
 * direction.  Zeros are fed into the vacated LS bit positions
 * and those MS bits shifted off the top are lost.
 */
void bitmap_shift_left(ulong_t *dst, const ulong_t *src, size_t shift,
							 size_t nbits)
{
	int32_t k;
	uint32_t lim = BITS_TO_ULONGS(nbits);
	uint32_t off = shift / BITS_PER_ULONG;
	uint32_t rem = shift % BITS_PER_ULONG;

	for (k = (int32_t)lim - (int32_t)off - 1; k >= 0; --k) {
		ulong_t upper, lower;

		/*
		 * If shift is not word aligned, take upper rem bits of
		 * word below and make them the bottom rem bits of result.
		 */
		if ((rem != 0U) && (k > 0)) {
			lower = src[k - 1] >> (BITS_PER_ULONG - rem);
		} else {
			lower = 0;
		}
		upper = src[k] << rem;
		dst[(uint32_t)k + off] = lower | upper;
	}

	if (off != 0U) {
		mvbs_memzero(dst, off*sizeof(ulong_t));
	}

}

/**
 * __bitmap_shift_right - logical right shift of the bits in a bitmap
 *   @dst : destination bitmap
 *   @src : source bitmap
 *   @shift : shift by this many bits
 *   @nbits : bitmap size, in bits
 *
 * Shifting right (dividing) means moving bits in the MS -> LS bit
 * direction.  Zeros are fed into the vacated MS positions and the
 * LS bits shifted off the bottom are lost.
 */
void bitmap_shift_right(ulong_t *dst, const ulong_t *src, size_t shift,
							  size_t nbits)
{
	uint32_t k;
	uint32_t lim = BITS_TO_ULONGS(nbits);
	uint32_t off = shift/BITS_PER_ULONG;
	uint32_t rem = shift%BITS_PER_ULONG;
	ulong_t mask = BITMAP_LAST_WORD_MASK(nbits);

	for (k = 0U; (off + k) < lim; ++k) {
		ulong_t upper, lower;

		/*
		 * If shift is not word aligned, take lower rem bits of
		 * word above and make them the top rem bits of result.
		 */
		if ((rem == 0U ) || ((off + k + 1U) >= lim)) {
			upper = 0U;
		} else {
			upper = src[off + k + 1U];
			if ((off + k + 1U) == (lim - 1U)) {
				upper &= mask;
			}
			upper <<= (BITS_PER_ULONG - rem);
		}

		lower = src[off + k];

		if ((off + k) == (lim - 1U)) {
			lower &= mask;
		}

		lower >>= rem;
		dst[k] = lower | upper;
	}

	if (off != 0U) {
		mvbs_memzero(&dst[lim - off], off*sizeof(ulong_t));
	}
}

/*
 * nbits:  The size of bitmao.
 *         For example: ulong_t bitmap[4], nbits = sizeof(ulong_t) * 8　* 4
 *
 * offset: skip offset bits. If offset is 0, it means that no bits will be
 *         skipped.
 *
 * invert: only two value is meaningful:
 *         0x00000000: This searching in bitmap is find out the next 1.
 *         0xFFFFFFFF: This searching in bitmap is find out the next 0.
 *
 * return the bit location: [0, nbits). If nbits is returned, it means not
 * found.
 *
 * find_next_bit_internal(0xFFFF0010, 32, 0, 0x00000000) = 4
 * find_next_bit_internal(0xFFFF0011, 32, 0, 0x00000000) = 0
 * find_next_bit_internal(0xFFFF0011, 32, 4, 0x00000000) = 4
 * find_next_bit_internal(0xFFFF0011, 32, 5, 0x00000000) = 16
 */
static size_t find_next_bit_internal(const ulong_t *addr,
				    size_t nbits, size_t offset,
				    ulong_t invert)
{
	ulong_t tmp;
	size_t start = offset;

	if ((nbits == 0UL ) || (start >= nbits)) {
		return nbits;
	}

	tmp = addr[start / BITS_PER_ULONG] ^ invert;

	/* Handle 1st word. */
	tmp &= BITMAP_FIRST_WORD_MASK(start);
	start = ROUND_DOWN(start, BITS_PER_ULONG);

	while (tmp == 0U) {
		start += BITS_PER_ULONG;

		if (start >= nbits) {
			return nbits;
		}

		tmp = addr[start / BITS_PER_ULONG] ^ invert;
	}

	return min_size(start + bitmap_ffs(tmp), nbits);
}


/*
 * Find the next set bit in a memory region.
 */
size_t find_next_bit(const ulong_t *addr, size_t size, size_t offset)
{
	return find_next_bit_internal(addr, size, offset, 0UL);
}

/*
 * Find the first set bit in a memory region.
 */
size_t find_first_bit(const ulong_t *addr, size_t size)
{
	uint32_t idx;
	size_t	 tmp;

	for (idx = 0U; (idx * BITS_PER_ULONG) < size; idx++) {
		if (addr[idx] != 0UL) {
			tmp = (idx * BITS_PER_ULONG) + bitmap_ffs(addr[idx]);

			return min_size(tmp, size);
		}
	}

	return size;
}

/*
 * Find the first cleared bit in a memory region.
 */
size_t find_first_zero_bit(const ulong_t *addr, size_t size)
{
	size_t	idx;
	size_t	tmp;

	for (idx = 0U; (idx * BITS_PER_ULONG) < size; idx++) {
		if (addr[idx] != (ulong_t)(~0UL)) {
			tmp = (idx * BITS_PER_ULONG) + ffz(addr[idx]);

			return min_size(tmp, size);
		}
	}

	return size;
}

size_t find_next_zero_bit(const ulong_t *addr, size_t size, size_t offset)
{
	return find_next_bit_internal(addr, size, offset, (ulong_t)(~0UL));
}

size_t find_last_bit(const ulong_t *addr, size_t size)
{
	if (size != 0UL) {
		ulong_t val = BITMAP_LAST_WORD_MASK(size);
		size_t  idx = (size - 1U) / BITS_PER_ULONG;

		do {
			val &= addr[idx];

			if (val != (ulong_t)0) {
				return (idx * BITS_PER_ULONG) + bitmap_fls(val);
			}

			val = ~(ulong_t)0;
		} while (idx-- != 0U);
	}

	return size;
}

#define WORD_BITS		(uint32_t)(8U * sizeof(uint32_t))
#define WORD_MASK		(~(uint32_t)0)

static inline uint32_t word_mask_shift(uint32_t n)
{
	return (n >= WORD_BITS)?0U:(WORD_MASK >> n);
}

/*
 * start: indicate a start postion. And the position is start with 0.
 */
void bitmap_set_bits(uint32_t *array, size_t start, size_t bits)
{
	uint32_t start_word, end_word;
	uint32_t start_bit, end_bit;
	size_t end = start + bits;

	if (end <= start) {
		return ;
	}

	/* Calculate the start and end word index in the array */
	start_word	= start / WORD_BITS;
	end_word	= end   / WORD_BITS;
	start_bit	= start % WORD_BITS;
	end_bit		= end   % WORD_BITS;

	/* Case1: If "start" and "end" are in the same word: */
	if (start_word == end_word) {
		/* Just set the corresponding bits. */
		array[start_word] |= (word_mask_shift(start_bit) ^
				      word_mask_shift(end_bit));
	} else {/*  Case2: If "start" and "end" span multiple words: */

		/*  step1: Set all the bits starting from "start" in the start
		 *  word
		 */
		array[start_word] |= word_mask_shift(start_bit);

		/* step2: For the complete words in the middle, set all the
		 * bits.
		 */
		for (uint32_t i = start_word + 1U; i < end_word; ++i) {
			array[i] = WORD_MASK;
		}

		/* step3: In the end word, set all the bits up to "end" */
		if (end_bit != 0) {
			array[end_word] |= ~word_mask_shift(end_bit);
		}
	}
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
