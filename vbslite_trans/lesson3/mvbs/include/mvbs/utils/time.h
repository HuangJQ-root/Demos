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

#ifndef MVBS_UTILS_TIME_H
#define MVBS_UTILS_TIME_H

#include <mvbs/base_type.h>

#define TIME_MSEC_PER_SEC	(1000)
#define TIME_USEC_PER_MSEC	(1000)
#define TIME_NSEC_PER_USEC	(1000)
#define TIME_NSEC_PER_MSEC	((uint64_t)TIME_NSEC_PER_USEC * (uint64_t)TIME_USEC_PER_MSEC)
#define TIME_USEC_PER_SEC	((uint64_t)TIME_MSEC_PER_SEC  * (uint64_t)TIME_USEC_PER_MSEC)
#define TIME_NSEC_PER_SEC	((uint64_t)TIME_USEC_PER_SEC  * (uint64_t)TIME_NSEC_PER_USEC)

struct mvbs_timespec {
	int32_t tv_sec;
	uint32_t tv_nsec;
};

void mvbs_get_time(int32_t *sec, uint32_t *nanosec);

uint64_t mvbs_calculate_time_interval_till_now(int32_t sec, uint32_t nanosec);

uint64_t mvbs_calculate_time_from_now(int32_t diff_sec, uint32_t diff_nanosec);

uint64_t mvbs_calculate_time_from_ts(int32_t sec, uint32_t nanosec,
				   int32_t diff_sec, uint32_t diff_nanosec);

struct mvbs_measure {
	struct mvbs_timespec start;
	struct mvbs_timespec end;
	uint32_t elapsed_us;
	uint32_t max_elapsed_us;
};

int32_t mvbs_measure_start(struct mvbs_measure *m);
int32_t mvbs_measure_end(struct mvbs_measure *m);

#endif
