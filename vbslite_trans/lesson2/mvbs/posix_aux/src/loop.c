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

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>
#include <sched.h>

#ifdef	TARGET_PRODUCT_MINGW
#include <windows.h>
#endif

#include "event.h"

#include <mvbs_aux/mvbs_aux.h>

extern int adapter_socket_init(void);
extern void adapter_socket_loop(void);

int pc_cpu_load(void)
{
	return 0;
}

#define	THREAD_STACKSIZE_LIMIT		(1024*1024)

#ifdef	TARGET_PRODUCT_MINGW
static void mvbs_usleep(LONGLONG us)
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER startCounter;
	LARGE_INTEGER counter;

	/* get counter frequency */
	QueryPerformanceFrequency(&frequency);

	/* get current counter value */
	QueryPerformanceCounter(&startCounter);

	/* calculate target counter value */
	LONGLONG targetCount = startCounter.QuadPart + us * (frequency.QuadPart / 1000000);

	/* loop till microsecond */
	do {
		QueryPerformanceCounter(&counter);
	} while (counter.QuadPart < targetCount);
}
#else
static void mvbs_usleep(uint64_t us)
{
	struct timespec	sleep;
	sleep.tv_sec	= us/1000000;
	sleep.tv_nsec	= us%1000000 * 1000;
	nanosleep(&sleep, NULL);
}
#endif

static uint64_t get_curr_time_us(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);

	return now.tv_sec * 1000000 + now.tv_usec;
}

struct mvbs_timer_loop {
	timer_loop_handler_t	fn;
	void			*param;
	uint32_t		peroid_ms;
	pthread_t		thd_id;
};

static void *timer_loop_handle(void *arg)
{
	struct mvbs_timer_loop *t = (struct mvbs_timer_loop *)arg;

	const uint64_t interval_us = (uint64_t)t->peroid_ms*1000;

	uint64_t diff_us;

	uint64_t begin_us;
	uint64_t end_us;

	adapter_socket_init();

	while (1) {
		begin_us = get_curr_time_us();

		t->fn(t->param);

		end_us = get_curr_time_us();

		diff_us = end_us - begin_us;

		if (diff_us > interval_us)
			continue;

		diff_us = interval_us - diff_us;

		mvbs_usleep(diff_us);
	}

	return NULL;
}

struct mvbs_timer_loop *mvbs_timer_loop_create(timer_loop_handler_t fn,
					void *param, uint32_t peroid_ms)
{
	struct mvbs_timer_loop	*t;
	pthread_attr_t		attr;

	t = (struct mvbs_timer_loop *)malloc(sizeof(*t));

	if (t == NULL) {
		return NULL;
	}

	t->fn		= fn;
	t->param	= param;
	t->peroid_ms	= peroid_ms;

	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, THREAD_STACKSIZE_LIMIT);

	pthread_create(&t->thd_id, &attr, timer_loop_handle, t);
	pthread_detach(t->thd_id);

	return t;
}


struct mvbs_event_loop {
	struct mvbs_event	*ev;
	uint32_t		peroid_ms;

	pthread_t		sock_thrd;
	pthread_t		timer_thrd;
};

static void *timer_event_handle(void *arg)
{
	struct mvbs_event_loop *e = (struct mvbs_event_loop *)arg;

	const uint64_t interval_us = (uint64_t)e->peroid_ms*1000;

	uint64_t diff_us;

	uint64_t begin_us;
	uint64_t end_us;

	while (1) {
		begin_us = get_curr_time_us();

		mvbs_event_send(e->ev, MVBS_EV_TIMER);

		end_us = get_curr_time_us();

		diff_us = end_us - begin_us;

		if (diff_us > interval_us)
			continue;

		diff_us = interval_us - diff_us;

		mvbs_usleep(diff_us);
	}

	return NULL;
}

static void *socket_recv_loop(void *arg)
{
	struct mvbs_event_loop *e = (struct mvbs_event_loop *)arg;

	while (1) {
		adapter_socket_loop();

		mvbs_event_send(e->ev, MVBS_EV_RECV);
	}

	return NULL;
}

struct mvbs_event_loop *mvbs_event_loop_create(uint32_t peroid_ms)
{
	struct mvbs_event_loop	*e;
	pthread_attr_t		attr;

	e = (struct mvbs_event_loop *)malloc(sizeof(*e));

	if (e == NULL) {
		return NULL;
	}

	e->ev = mvbs_event_create();
	if (e->ev == NULL) {
		free(e);

		return NULL;
	}

	e->peroid_ms	= peroid_ms;

	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, THREAD_STACKSIZE_LIMIT);

	pthread_create(&e->timer_thrd, &attr, timer_event_handle, e);
	pthread_detach(e->timer_thrd);

	adapter_socket_init();

	pthread_create(&e->sock_thrd, &attr, socket_recv_loop, e);
	pthread_detach(e->sock_thrd);

	return e;
}

uint32_t mvbs_event_loop_wait(struct mvbs_event_loop *loop)
{
	if (loop == NULL) {
		return 0;
	}

	return mvbs_event_wait(loop->ev);
}
