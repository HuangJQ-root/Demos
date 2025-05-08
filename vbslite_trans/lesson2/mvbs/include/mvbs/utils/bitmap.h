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

#ifndef	MVBS_UTILS_BITMAP_H
#define	MVBS_UTILS_BITMAP_H

#include <mvbs/utils/cdefs.h>

/*
 * Note: The BITS_PER_LONG has been mantained by manual for this macro should
 * be only used to preprocessed.
 * The bitmap array should be defined with the type of ulong_t
 */
#define BITS_PER_LONG		32U
typedef uint32_t		ulong_t;
#define LONG_BITS_SHIFT		5

#define BITS_PER_BYTE		8U

#define BITS_PER_TYPE(type)	(sizeof(type) * BITS_PER_BYTE)
#define BITS_PER_ULONG		BITS_PER_TYPE(ulong_t)
#define BITS_TO_ULONGS(nr)	DIV_ROUND_UP(nr, BITS_PER_ULONG)
#define BITS_TO_BYTES(nr)	DIV_ROUND_UP(nr, BITS_PER_BYTE)

#define BIT_MASK(nr)		((ulong_t)(1) << ((nr) % BITS_PER_ULONG))
#define BIT_WORD(nr)		((nr) / BITS_PER_ULONG)

#define BITMAP_WORD(nr)		((nr) >> LONG_BITS_SHIFT)
#define BITMAP_BITS(nr)		((nr) & ((1<<LONG_BITS_SHIFT) -1))

#define BITMAP_FIRST_WORD_MASK(start)	(~(ulong_t)0 << ((start) & (BITS_PER_ULONG - (ulong_t)1)))
#define BITMAP_LAST_WORD_MASK(nbits)								\
	(											\
		(((nbits) % BITS_PER_ULONG) != (ulong_t)0) ?					\
			(((ulong_t)1<<((nbits) % BITS_PER_ULONG))-(ulong_t)1) : ~(ulong_t)0	\
	)

/*
 * The macro const_hweight8 is used to count the number of '1' in w.
 */
#define const_hweight8(w)			\
	((size_t)				\
	 (((((w) & (1ULL << 0u))==0u)?0U:1U) +	\
	  ((((w) & (1ULL << 1u))==0u)?0U:1U) +	\
	  ((((w) & (1ULL << 2u))==0u)?0U:1U) +	\
	  ((((w) & (1ULL << 3u))==0u)?0U:1U) +	\
	  ((((w) & (1ULL << 4u))==0u)?0U:1U) +	\
	  ((((w) & (1ULL << 5u))==0u)?0U:1U) +	\
	  ((((w) & (1ULL << 6u))==0u)?0U:1U) +	\
	  ((((w) & (1ULL << 7u))==0u)?0U:1U)))


#define const_hweight16(w) (const_hweight8(w)  + const_hweight8((w)  >> 8U ))
#define const_hweight32(w) (const_hweight16(w) + const_hweight16((w) >> 16U))
#define const_hweight64(w) (const_hweight32(w) + const_hweight32((w) >> 32U))

static inline uint32_t hweight8(uint8_t w)
{
	unsigned int res = w - ((w >> 1) & 0x55);
	res = (res & 0x33) + ((res >> 2) & 0x33);
	return (res + (res >> 4)) & 0x0F;
}

static inline uint32_t hweight16(uint16_t w)
{
	unsigned int res = w - ((w >> 1) & 0x5555);
	res = (res & 0x3333) + ((res >> 2) & 0x3333);
	res = (res + (res >> 4)) & 0x0F0F;
	return (res + (res >> 8)) & 0x00FF;
}

static inline uint32_t hweight32(uint32_t w)
{
#ifdef CONFIG_ARCH_HAS_FAST_MULTIPLIER
	w -= (w >> 1) & 0x55555555;
	w =  (w & 0x33333333) + ((w >> 2) & 0x33333333);
	w =  (w + (w >> 4)) & 0x0f0f0f0f;
	return (w * 0x01010101) >> 24;
#else
	unsigned int res = w - ((w >> 1) & 0x55555555);
	res = (res & 0x33333333) + ((res >> 2) & 0x33333333);
	res = (res + (res >> 4)) & 0x0F0F0F0F;
	res = res + (res >> 8);
	return (res + (res >> 16)) & 0x000000FF;
#endif
}

static inline uint32_t hweight64(uint64_t w)
{
	return hweight32((uint32_t)(w >> 32)) + hweight32((uint32_t)w);
}

#if	BITS_PER_LONG == 64
#define hweight_ulong(w)		const_hweight64(w)
#elif	BITS_PER_LONG == 32
#define hweight_ulong(w)		const_hweight32(w)
#elif	BITS_PER_LONG == 16
#define hweight_ulong(w)		const_hweight16(w)
#elif	BITS_PER_LONG == 8
#define hweight_ulong(w)		const_hweight8(w)
#endif

static inline uint32_t mvbs_count_bits_set_8(uint8_t w)
{
	unsigned int res = w - ((w >> 1) & 0x55);
	res = (res & 0x33) + ((res >> 2) & 0x33);
	return (res + (res >> 4)) & 0x0F;
}

static inline uint32_t mvbs_count_bits_set_16(uint16_t w)
{
	unsigned int res = w - ((w >> 1) & 0x5555);
	res = (res & 0x3333) + ((res >> 2) & 0x3333);
	res = (res + (res >> 4)) & 0x0F0F;
	return (res + (res >> 8)) & 0x00FF;
}

static inline uint32_t mvbs_count_bits_set_32(uint32_t w)
{
#ifdef CONFIG_ARCH_HAS_FAST_MULTIPLIER
	w -= (w >> 1) & 0x55555555;
	w =  (w & 0x33333333) + ((w >> 2) & 0x33333333);
	w =  (w + (w >> 4)) & 0x0f0f0f0f;
	return (w * 0x01010101) >> 24;
#else
	unsigned int res = w - ((w >> 1) & 0x55555555);
	res = (res & 0x33333333) + ((res >> 2) & 0x33333333);
	res = (res + (res >> 4)) & 0x0F0F0F0F;
	res = res + (res >> 8);
	return (res + (res >> 16)) & 0x000000FF;
#endif
}

static inline uint32_t mvbs_count_bits_set_64(uint64_t w)
{
	return mvbs_count_bits_set_32((uint32_t)(w >> 32)) +
	       mvbs_count_bits_set_32((uint32_t)w);
}

/**
 * bitmap_ffs - find first bit in word.
 * @word: The word to search
 *
 * Undefined if no bit exists, so code should check against 0 first.
 *
 * For example:
 * bitmap_ffs(0x0001) = 0
 * bitmap_ffs(0x0002) = 1
 * bitmap_ffs(0x0003) = 0
 * bitmap_ffs(0x0004) = 2
 * bitmap_ffs(0x0008) = 3
 */
static inline size_t bitmap_ffs(ulong_t word)
{
	size_t num	= 0;
	ulong_t val	= word;

#if BITS_PER_LONG == 64
	if ((val & 0xffffffffULL) == 0ULL) {
		num += 32UL;
		val >>= 32UL;
	}
#endif
	if ((val & 0xffffULL) == 0ULL) {
		num += 16UL;
		val >>= 16UL;
	}

	if ((val & 0xffULL) == 0ULL) {
		num += 8UL;
		val >>= 8UL;
	}

	if ((val & 0xfULL) == 0ULL) {
		num += 4UL;
		val >>= 4UL;
	}

	if ((val & 0x3ULL) == 0ULL) {
		num += 2UL;
		val >>= 2UL;
	}

	if ((val & 0x1ULL) == 0ULL) {
		num += 1UL;
	}

	return num;
}

#define ffz(x) bitmap_ffs(~(x))


static inline size_t bitmap_fls(ulong_t word)
{
	size_t num = BITS_PER_ULONG - 1UL;
	ulong_t val = word;

#if BITS_PER_LONG == 64UL
	if ((val & (~0uLL << 32)) == 0ULL) {
		num -= 32UL;
		val <<= 32UL;
	}
#endif
	if ((val & (~0uLL << (BITS_PER_ULONG - 16UL))) == 0ULL) {
		num -= 16UL;
		val <<= 16UL;
	}

	if ((val & (~0uLL << (BITS_PER_ULONG - 8UL))) == 0ULL) {
		num -= 8UL;
		val <<= 8UL;
	}

	if ((val & (~0uLL << (BITS_PER_ULONG - 4UL))) == 0ULL) {
		num -= 4UL;
		val <<= 4UL;
	}

	if ((val & (~0uLL << (BITS_PER_ULONG - 2UL))) == 0ULL) {
		num -= 2UL;
		val <<= 2UL;
	}

	if ( (val & (~0uLL << (BITS_PER_ULONG - 1UL))) == 0ULL) {
		num -= 1UL;
	}

	return num;
}

static inline void bitmap_set_bit(size_t nr, ulong_t *addr)
{
	ulong_t mask = BIT_MASK(nr);
	ulong_t *p = ((ulong_t *)addr) + BIT_WORD(nr);

	*p  |= mask;
}


static inline void bitmap_clear_bit(size_t nr, ulong_t *addr)
{
	ulong_t mask = BIT_MASK(nr);
	ulong_t *p = ((ulong_t *)addr) + BIT_WORD(nr);

	*p &= ~mask;
}

/**
 * _test_bit - Determine whether a bit is set
 * @nr: bit number to test
 * @addr: Address to start counting from
 */
static inline bool bitmap_test_bit(size_t nr, const volatile ulong_t *addr)
{
	if ((1UL & (addr[BIT_WORD(nr)] >> (nr & (BITS_PER_ULONG-1UL)))) != 0UL) {
		return true;
	} else {
		return false;
	}
}

#define BIT_POS_MIRROR(pos)			(BITS_PER_ULONG - pos - 1)


static inline void bitmap_set_bit_be(size_t bit, ulong_t *addr)
{
	uint8_t bucket	= BITMAP_WORD(bit);
	uint8_t pos	= BITMAP_BITS(bit);

	addr[bucket] |= ((ulong_t)1 << BIT_POS_MIRROR(pos));
}

static inline void bitmap_clear_bit_be(size_t bit, ulong_t *addr)
{
	uint8_t bucket	= BITMAP_WORD(bit);
	uint8_t pos	= BITMAP_BITS(bit);

	addr[bucket] &= ~((ulong_t)1 << BIT_POS_MIRROR(pos));
}

static inline bool bitmap_test_bit_be(size_t bit, ulong_t *addr)
{
	uint8_t bucket	= BITMAP_WORD(bit);
	uint8_t pos	= BITMAP_BITS(bit);

	return !! (addr[bucket] & ((ulong_t)1 << BIT_POS_MIRROR(pos)));
}

#define for_each_bit(bit, addr, size) \
		for ((bit) = 0; (bit) = find_next_bit((addr), (size), (bit)), (bit) < (size); (bit)++)

void bitmap_shift_left(ulong_t *dst, const ulong_t *src, size_t shift,
							 size_t nbits);

void bitmap_shift_right(ulong_t *dst, const ulong_t *src, size_t shift,
							  size_t nbits);

size_t find_first_bit(const ulong_t *addr, size_t size);
size_t find_next_bit(const ulong_t *addr, size_t size, size_t offset);

size_t find_first_zero_bit(const ulong_t *addr, size_t size);
size_t find_next_zero_bit(const ulong_t *addr, size_t size, size_t offset);

size_t find_last_bit(const ulong_t *addr, size_t size);

void bitmap_set_bits(uint32_t *array, size_t start, size_t bits);
#endif
