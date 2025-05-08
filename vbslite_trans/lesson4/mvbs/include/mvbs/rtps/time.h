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

#ifndef MVBS_RTPS_TIME_H
#define MVBS_RTPS_TIME_H

#include <mvbs/base_type.h>

#define RTPS_TIME_MS_PER_SEC	(uint32_t)(1000)
#define RTPS_TIME_US_PER_MS	(uint32_t)(1000)
#define RTPS_TIME_NS_PER_US	(uint32_t)(1000)

#define RTPS_TIME_US_PER_SEC	((uint32_t)(RTPS_TIME_MS_PER_SEC * RTPS_TIME_US_PER_MS))
#define RTPS_TIME_NS_PER_SEC	((uint32_t)(RTPS_TIME_US_PER_SEC * RTPS_TIME_NS_PER_US))
#define RTPS_TIME_NS_PER_MS	((uint32_t)(RTPS_TIME_NS_PER_US  * RTPS_TIME_US_PER_MS))

struct rtps_time {
	int32_t		seconds;	/* seconds */
	uint32_t	nanosec;	/* nanoseconds */
};

typedef struct rtps_time		rtps_time_t;

typedef struct rtps_time		duration_t;

#define RTPS_TIME_INVALID_SEC		-1
#define RTPS_TIME_INFINITE_SEC		0x7FFFFFFF

#define RTPS_TIME_INVALID_NSEC		0xFFFFFFFFU
#define RTPS_TIME_INFINITE_NSEC		0xFFFFFFFFU


extern const struct rtps_time		RTPS_TIME_ZERO;
extern const struct rtps_time		RTPS_TIME_INVALID;
extern const struct rtps_time		RTPS_TIME_INFINITE;

extern const int32_t			DURATION_INFINITE_SEC;
extern const uint32_t			DURATION_INFINITE_NSEC;
extern const int32_t			DURATION_ZERO_SEC;
extern const uint32_t			DURATION_ZERO_NSEC;

static inline uint64_t rtps_time_to_uint64(const struct rtps_time *t)
{
	return (((uint64_t)t->seconds) << 32) | (uint64_t)t->nanosec;
}

static inline uint64_t rtps_time_to_ns(const struct rtps_time *t)
{
	return ((uint64_t)t->seconds * RTPS_TIME_NS_PER_SEC) +
		(uint64_t)t->nanosec;
}

static inline uint64_t rtps_time_to_us(const struct rtps_time *t)
{
	return ((uint64_t)t->seconds * RTPS_TIME_US_PER_SEC) +
		((uint64_t)t->nanosec / RTPS_TIME_NS_PER_US);
}

static inline uint64_t rtps_time_to_ms(const struct rtps_time *t)
{
	return ((uint64_t)t->seconds * RTPS_TIME_MS_PER_SEC) +
		((uint64_t)t->nanosec / RTPS_TIME_NS_PER_MS);
}

static inline bool rtps_time_is_infinite(const struct rtps_time *t)
{
	return (t->seconds == RTPS_TIME_INFINITE.seconds) &&
		(t->nanosec == RTPS_TIME_INFINITE.nanosec);
}

static inline rtps_time_t rtps_time_diff(rtps_time_t t1, rtps_time_t t2)
{
	rtps_time_t delta;

	if (t1.nanosec > t2.nanosec) {
		delta.nanosec = t1.nanosec - t2.nanosec;
		delta.seconds = t1.seconds - t2.seconds;
	} else {
		delta.nanosec = RTPS_TIME_NS_PER_SEC - t2.nanosec + t1.nanosec;
		delta.seconds = t1.seconds - t2.seconds - 1;
	}

	return delta;
}

static inline bool rtps_time_equal(const rtps_time_t *t1, const rtps_time_t *t2)
{
	return ((t1->seconds == t2->seconds) && (t1->nanosec == t2->nanosec));
}

static inline int32_t rtps_time_cmp(rtps_time_t t1, rtps_time_t t2)
{
	if (t1.seconds > t2.seconds) {
		return 1;
	}

	if (t1.seconds < t2.seconds) {
		return -1;
	}

	/* t1.seconds == t2.seconds */
	if (t1.nanosec > t2.nanosec) {
		return 1;
	}

	if (t1.nanosec < t2.nanosec) {
		return -1;
	}

	return 0;
}

extern const duration_t			SPDP_DEFAULT_REMOTE_LEASE_DURATION;
extern const duration_t			SPDP_MAX_REMOTE_LEASE_DURATION;

static inline uint64_t duration_to_ns(const duration_t *duration)
{
	return rtps_time_to_ns(duration);
}

static inline uint64_t duration_to_us(const duration_t *duration)
{
	return rtps_time_to_us(duration);
}

static inline uint64_t duration_to_ms(const duration_t *duration)
{
	return rtps_time_to_ms(duration);
}

static inline bool duration_is_infinite(const duration_t *duration)
{
	return rtps_time_is_infinite(duration);
}

/*
 * return:
 *	left < right, return -1
 *	left = right, return 0
 *	left > right, return 1
 */
static inline int32_t duration_compare(const duration_t *left, const duration_t *right)
{
	if (duration_is_infinite(left)) {
		if (duration_is_infinite(right)) {
			return 0;
		} else {
			return 1;
		}
	}

	if (duration_is_infinite(right)) {
		return -1;
	}

	if (left->seconds > right->seconds) {
		return 1;
	} else if (left->seconds < right->seconds) {
		return -1;
	} else {
		if (left->nanosec > right->nanosec) {
			return 1;
		} else if (left->nanosec < right->nanosec) {
			return -1;
		} else {
			return 0;
		}
	}
}

static inline bool duration_greater(const duration_t *left,
				    const duration_t *right)
{
	return duration_compare(left, right) == 1;
}

static inline bool duration_less(const duration_t *left,
				 const duration_t *right)
{
	return duration_compare(left, right) == -1;
}

#endif /* !__MVBS_RTPS_TIME_H__ */
