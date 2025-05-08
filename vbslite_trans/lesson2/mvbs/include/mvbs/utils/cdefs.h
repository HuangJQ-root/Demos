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

#ifndef MVBS_UTILS_CDEFS_H
#define MVBS_UTILS_CDEFS_H

#include <mvbs/base_type.h>

#define UNUSED_ARG(x)			((void)(x))

#define	ARRAY_SIZE(arr)			(sizeof(arr) / sizeof((arr)[0]))

#define static_cast_ptr(type, ptr)	(type *)((void *)(ptr))

#ifndef READ_ONCE
#define READ_ONCE(x)			(*(const volatile __typeof__(x) *)&(x))
#endif

#ifndef WRITE_ONCE
#define WRITE_ONCE(x, val)		(*(volatile __typeof__(x) *)&(x) = (val))
#endif

#define ROUND_UP(x, n)			(((x) + (n)-1UL) & ~((n)-1UL))
#define ROUND_DOWN(x, n)		((x) & ~((n)-1UL))
#define DIV_ROUND_UP(n, d)		(((n) + (d) - 1UL) / (d))

#define round_mask(x, y)		((__typeof__(x))((y)-1U))
#define round_up(x, y)			((((x)-1U) | round_mask(x, y))+1U)
#define round_down(x, y)		((x) & ~round_mask(x, y))

#define ALIGN_UP_4(size)		(((size) + 3) & (~((__typeof__(size))0x3)))

#define CONCAT_STRAIGHT(a,b)		a##b
#define CONCAT(a,b)			CONCAT_STRAIGHT(a,b)

#define container_of(ptr, type, member)					\
	(static_cast_ptr(type, (char *)(ptr) - offsetof(type, member)))


static inline const char *string_or_null(const char *msg)
{
	return (msg == NULL) ? "NULL" : msg;
}

static inline size_t min_size(size_t a, size_t b)
{
	return (a < b) ? a : b;
}

static inline bool time_after(unsigned long a, unsigned long b)
{
	return ((long)((b) - (a)) < 0);
}

static inline bool time_before(unsigned long a, unsigned long b)
{
	return time_after(b, a);
}

static inline bool time_after_eq(unsigned long a, unsigned long b)
{
	return ((long)((a) - (b)) >= 0);
}

static inline bool time_before_eq(unsigned long a, unsigned long b)
{
	return time_after_eq(b, a);
}

#define MVBS_INCLUDE(header)		<header>

#endif /* !__MVBS_CDEFS_H__ */
