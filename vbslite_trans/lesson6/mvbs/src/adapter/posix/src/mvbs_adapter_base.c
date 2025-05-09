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

#include <mvbs_adapter.h>

#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

#ifndef TARGET_PRODUCT_MINGW
#include <unistd.h>
#endif

#define MVBS_HEAP_SIZE_L	(256 * 1024)
#define MVBS_HEAP_SIZE_S	(32 * 1024)

/* static uint8_t mvbs_heap_1[MVBS_HEAP_SIZE_S]; */
/* static uint8_t mvbs_heap_2[MVBS_HEAP_SIZE_S]; */
/* static uint8_t mvbs_heap_3[MVBS_HEAP_SIZE_S]; */
/* static uint8_t mvbs_heap_4[MVBS_HEAP_SIZE_S]; */
static uint8_t mvbs_heap_5[MVBS_HEAP_SIZE_L];

static struct mem_region mvbs_heap_region[] = {
	{
		.mr_start = mvbs_heap_5,
		.mr_size = MVBS_HEAP_SIZE_L,
	},
	{
		.mr_start = NULL,
		.mr_size = 0,
	}
};

struct mem_region * mvbs_get_heap_info(void)
{
	return mvbs_heap_region;
}

#ifndef TARGET_PRODUCT_MINGW
static inline void print_log_time(void)
{
	struct timeval	tv;
	struct tm	*tm_now;

	char timebuf[20];

	gettimeofday(&tv, NULL);

	tm_now = localtime(&tv.tv_sec);

	strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_now);

	printf("[%s.%06ld] ", timebuf, tv.tv_usec);
}
#else
#include <windows.h>
static inline void print_log_time(void)
{
	char currentTime[80] = { 0 };
	SYSTEMTIME sys;

	GetLocalTime(&sys);

	snprintf(currentTime, sizeof(currentTime),
			"%4d-%02d-%02d %02d:%02d:%02d.%03d",
			sys.wYear, sys.wMonth, sys.wDay, sys.wHour,
			sys.wMinute,sys.wSecond,sys.wMilliseconds);

	printf("[%s] ", currentTime);
}
#endif

void mvbs_log_print(uint32_t level, char *buffer)
{
	static const char * const log_level_colors[] = {
		"",	    /* DISABLE  */
		"\033[35m", /* FATAL	*/
		"\033[31m", /* ERROR	*/
		"\033[33m", /* WARN	*/
		"\033[32m", /* INFO	*/
		"\033[36m", /* DEBUG	*/
		"\033[94m"  /* VERBOSE	*/
	};

	static const char *log_colors_eof = "\033[0m";

	printf("%s ", log_level_colors[level]);
	print_log_time();
	printf("%s%s\n", buffer, log_colors_eof);

	fflush(stdout);
}

bool mvbs_get_current_time(uint32_t *ts_sec, uint32_t *ts_nsec)
{
	struct timeval now;

	if (ts_sec == NULL || ts_nsec == NULL) {
		return false;
	}

	gettimeofday(&now, NULL);

	*ts_sec		= now.tv_sec;
	*ts_nsec	= now.tv_usec * 1000;

	return true;
}

uint64_t mvbs_get_session_id(void)
{
	uint32_t ts_sec;
	uint32_t ts_nsec;
	uint64_t value = 0;
	bool  ret;

	ret = mvbs_get_current_time(&ts_sec, &ts_nsec);
	if (ret == true) {
		value = ts_sec;
		value = (value << 32) | ts_nsec;
	}

	return value;
}