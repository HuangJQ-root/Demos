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

#include <mvbs/errno.h>
#include <mvbs/utils/time.h>
#include <mvbs/utils/log.h>
#include <mvbs/adapter/adapter.h>

void mvbs_get_time(int32_t *sec, uint32_t *nanosec)
{
	/* TODO, FIXME */
	if (sec == NULL || nanosec == NULL) {
		pr_err(ERR_INVALID, "sec or nanosec is NULL");
		return;
	}

	uint32_t ts_sec		= 0;
	uint32_t ts_nsec	= 0;

	mvbs_get_current_time(&ts_sec, &ts_nsec);

	*sec 		= (int32_t)ts_sec;
	*nanosec	= ts_nsec;
}

uint64_t mvbs_calculate_time_interval_till_now(int32_t sec, uint32_t nanosec)
{
	int32_t tmp_sec = 0;
	uint32_t tmp_nanosec = 0;

	mvbs_get_time(&tmp_sec, &tmp_nanosec);

	return (((uint64_t)tmp_sec - (uint64_t)sec) * (uint64_t)TIME_NSEC_PER_SEC)
		+ ((uint64_t)tmp_nanosec - (uint64_t)nanosec);
}

uint64_t mvbs_calculate_time_from_now(int32_t diff_sec, uint32_t diff_nanosec)
{
	int32_t tmp_sec = 0;
	uint32_t tmp_nanosec = 0;

	mvbs_get_time(&tmp_sec, &tmp_nanosec);

	return (((uint64_t)tmp_sec + (uint64_t)diff_sec) * (uint64_t)TIME_NSEC_PER_SEC)
		+ ((uint64_t)tmp_nanosec + (uint64_t)diff_nanosec);
}

uint64_t mvbs_calculate_time_from_ts(int32_t sec, uint32_t nanosec,
				   int32_t diff_sec, uint32_t diff_nanosec)
{
	return (((uint64_t)sec + (uint64_t)diff_sec) * (uint64_t)TIME_NSEC_PER_SEC) +
	    	((uint64_t)nanosec + (uint64_t)diff_nanosec);
}

int32_t mvbs_measure_start(struct mvbs_measure *m)
{
	if (m == NULL) {
		return -ERR_INVALID;
	}

	mvbs_get_time(&m->start.tv_sec, &m->start.tv_nsec);

	return 0;
}

int32_t mvbs_measure_end(struct mvbs_measure *m)
{
	int32_t tmp_sec;
	uint32_t tmp_nsec;

	if (m == NULL) {
		return -ERR_INVALID;
	}

	mvbs_get_time(&m->end.tv_sec, &m->end.tv_nsec);

	tmp_sec = m->end.tv_sec - m->start.tv_sec;
	tmp_nsec = m->end.tv_nsec;

	if (tmp_nsec < m->start.tv_nsec) {
		tmp_sec--;
		tmp_nsec = (uint32_t)(tmp_nsec + TIME_NSEC_PER_SEC);
	}

	tmp_nsec -= m->start.tv_nsec;

	m->elapsed_us = (uint32_t)(((uint32_t)tmp_sec * TIME_USEC_PER_SEC)
		        	 + (tmp_nsec / (uint32_t)TIME_NSEC_PER_USEC));

	if (m->max_elapsed_us < m->elapsed_us) {
		m->max_elapsed_us = m->elapsed_us;
	}

	return 0;
}


#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
