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

#ifndef MVBS_UTILS_TIMER_H
#define MVBS_UTILS_TIMER_H

#include <mvbs/base_type.h>
#include <mvbs/core/types.h>

struct timer_handler;
struct participant;

typedef void (*timer_handler_fn) (void *arg);

#define MVBS_TIMER_RELTIME		0x1U
#define MVBS_TIMER_ABSTIME		0x2U

/*
 * Create a timer handler
 *
 * If repeat is true, it's mean the timer is a periodic timer.
 *
 * If repeat is false, it's mean the timer is a oneshottimer.
 *
 */
timer_desc_t mvbs_timer_create(struct participant *ptcp, timer_handler_fn fn,
			       void *arg, uint8_t repeat);

/*
 * Delete a timer
 *
 */
void mvbs_timer_delete_internal(struct participant *ptcp, timer_desc_t td);

#define mvbs_timer_delete(ptcp, td)                   \
	do {                                          \
		mvbs_timer_delete_internal(ptcp, td); \
		td = TIMER_DESC_INVALID;              \
	} while (false)
/*
 * Start a timer
 *
 * Flag == MVBS_TIMER_RELTIME,
 * The sec and ns parameter are interpreted relative to the current time
 * on the timer's clock at the time of the call.
 *
 * Flag == MVBS_TIMER_ABSTIME,
 * The sec and ns parameter are interpreted as an absolute value as measured
 * on the timer's clock; that is, the timer will expire when the clock value
 * reaches the value specified.
 */
int32_t mvbs_timer_start(struct participant *ptcp, timer_desc_t td,
			 uint32_t timer_flag, int32_t sec, uint32_t ns);

/*
 * Update the timer timeout time
 */
static inline int32_t mvbs_timer_update_timeout(struct participant *ptcp,
						timer_desc_t td,
						uint32_t timer_flag,
						int32_t sec, uint32_t ns)
{
	return mvbs_timer_start(ptcp, td, timer_flag, sec, ns);
}

/*
 * Just set the timeout of timer, but not start it.
 */
int32_t mvbs_timer_settime(struct participant *ptcp, timer_desc_t td,
			   uint32_t timer_flag, int32_t sec, uint32_t ns);

/*
 * Restart a timer
 */
int32_t mvbs_timer_restart(struct participant *ptcp, timer_desc_t td);

/*
 * Stop a timer, but not free timer struct.
 *
 */
int32_t mvbs_timer_stop(struct participant *ptcp, timer_desc_t td);

/*
 * Get timer resolution, return us
 */
uint32_t mvbs_timer_get_resolution(struct participant *ptcp);

/*
 * Get timer count
 *
 * active: the count of active timers
 * total : the count of timers
 */
void mvbs_timer_get_count(struct participant *ptcp, uint32_t *total,
			  uint32_t *active);

/*
 * Timer tick callback in mvbs prcoess
 *
 * The frequency of calls must equeal to the 'microsecond' in mvbs_timer_init.
 */
void mvbs_timer_tick(struct participant *ptcp);

/*
 * Timer subsystem initialization
 */
int32_t mvbs_timer_init(struct participant *ptcp, int32_t us);

/*
 * Timer subsystem deinitialization
 */
void mvbs_timer_deinit(struct participant *ptcp);

#ifdef __MVBS_CORE_SOURCE__
#include <mvbs/core/types.h>
#include <mvbs/utils/mvbs_list.h>

#define MVBS_TIMER_DEFAULT_RESOLUTION	(5*TIME_USEC_PER_MSEC) /* 5ms = 5000 us*/

#define MVBS_TIMER_WHEEL_NUM		8U

#define MVBS_TIMER_MAX_TICK		((((uint32_t)1 << 27U) * MVBS_TIMER_WHEEL_NUM)	\
					+ ((uint32_t)1 << 3U) - 2U)

enum {
	E_TWNC_GREEN,
	E_TWNC_BLUE,
	E_TWNC_MAX,
};

struct timer_handler {
	timer_handler_fn handler;
	void		*user_data;

	uint32_t interval_ticks;
	uint32_t repeat:1;
	/* timer control info*/
	uint32_t enabled:1;
	uint32_t unused:3;	/* MVBS_TIMER_WHEEL_NUM */
	uint32_t wheel_count:27;

	struct mvbs_list		l_node;
	struct mvbs_timer_wheel_node	*wheel_node;
};

struct mvbs_timer_wheel_node {
	struct mvbs_list l_head[E_TWNC_MAX];
	uint16_t	 color;
	uint16_t	 is_update;
};

struct mvbs_timer_wheel {
	struct mvbs_timer_wheel_node wheel[MVBS_TIMER_WHEEL_NUM];
	uint32_t current_slot;
	uint16_t active;
	uint16_t total;
};

#endif

#endif
