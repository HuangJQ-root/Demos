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

#include <core/core.h>
#include <mvbs/base_type.h>
#include <mvbs/errno.h>
#include <mvbs/utils/mvbs_list.h>
#include <mvbs/utils/mem_pool.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/log.h>
#include <mvbs/utils/mm.h>
#include <mvbs/utils/time.h>
#include <mvbs/utils/timer.h>


static void timer_calculate_tick(struct timer_handler *timer, uint32_t *p_remain_ticks);
static void timer_schedule_entry(struct participant *ptcp, struct timer_handler *timer);
static inline bool timer_is_over_max_interval(uint32_t timer_ticks);

static inline void timer_node_remove(struct participant *ptcp, struct mvbs_list *l_node);
static void timer_remove_entry(struct participant *ptcp, struct timer_handler *timer);

/*
 * for external interface
 * The wheel_node->is_update will set to true.
 */

static inline struct timer_handler *get_timer_handler_by_td(struct participant *ptcp,
								timer_desc_t td)
{
	struct timer_handler *timer = NULL;

	if (td == TIMER_DESC_INVALID) {
		return NULL;
	}

	timer = mp_get_blk_data_by_idx(&ptcp->timers, (uint32_t)td);

	return timer;
}

static inline uint64_t timer_to_us(int32_t sec, uint32_t ns)
{
	return ((uint64_t)sec * TIME_USEC_PER_SEC)
		+ (ns / (uint32_t)TIME_NSEC_PER_USEC);
}

static inline uint32_t timer_calculate_interval_ticks(struct participant *ptcp,
						      int32_t sec, uint32_t ns)
{
	return (uint32_t)(timer_to_us(sec, ns) / ptcp->timer_period_us);
}

static inline bool timer_is_over_max_interval(uint32_t timer_ticks)
{
	return timer_ticks > MVBS_TIMER_MAX_TICK;
}

static inline void timer_node_remove(struct participant *ptcp,
					struct mvbs_list *l_node)
{
	mvbs_list_del(l_node);

	ptcp->timer_wheel.active--;
}

static void timer_calculate_tick(struct timer_handler *timer,
				 uint32_t *p_remain_ticks)
{
	uint32_t ticks = 0;
	uint32_t wheel_count = 0;

	ticks		= timer->interval_ticks;

	wheel_count	= ticks / MVBS_TIMER_WHEEL_NUM;
	ticks		= ticks % MVBS_TIMER_WHEEL_NUM;

	/* less than resolution as 1 tick */
	if ((wheel_count == 0U) && (ticks == 0U)) {
		ticks = 1;
	}

	timer->wheel_count	= wheel_count;
	*p_remain_ticks		= ticks;
}

static void timer_schedule_entry(struct participant *ptcp,
				 struct timer_handler *timer)
{
	uint32_t ticks;
	uint32_t slot_num;
	struct mvbs_timer_wheel_node *wheel_node = NULL;

	timer_calculate_tick(timer, &ticks);

	if (timer->enabled == 0U) {
		/*
		 * Round up the first tick since it is unknown exactly where in a
		 * clock period the entry is scheduled. This means that the first
		 * tick can be up to 2 clock ticks late.
		 */
		++ticks;
		timer->enabled = true;
		if (ticks == MVBS_TIMER_WHEEL_NUM) {
			++timer->wheel_count;
			ticks = 0;
		}
	}

	slot_num = (ptcp->timer_wheel.current_slot + ticks) % MVBS_TIMER_WHEEL_NUM;

	/* If this is true then entry->wheel_count must >= 1 */
	if (slot_num == ptcp->timer_wheel.current_slot) {
		--timer->wheel_count;
	}

	wheel_node = &ptcp->timer_wheel.wheel[slot_num];

	if (timer->wheel_node != NULL) {
		pr_err(ERR_FAULT, "timer schedule entry error!");
	}

	mvbs_list_add_tail(&timer->l_node, &wheel_node->l_head[wheel_node->color]);

	timer->wheel_node = wheel_node;

	wheel_node->is_update = true;

	ptcp->timer_wheel.active++;
}

static void timer_remove_entry(struct participant *ptcp,
			       struct timer_handler *timer)
{
	struct mvbs_timer_wheel_node *wheel_node = NULL;

	wheel_node = timer->wheel_node;

	if (wheel_node != NULL) {
		timer->wheel_node = NULL;

		timer_node_remove(ptcp, &timer->l_node);

		wheel_node->is_update = true;
	}
}

static int32_t timer_set_time(struct participant *ptcp,
			      struct timer_handler *timer, uint32_t timer_flag,
			      int32_t sec, uint32_t ns)
{
	int32_t tmp_sec = 0;
	uint32_t tmp_nsec = 0;
	uint32_t timer_interval_ticks = 0;
	int32_t t_sec = sec;
	uint32_t t_ns = ns;

	if (t_sec < 0) {
		return -ERR_INVALID;
	}

	if (timer->handler == NULL) {
		pr_err(ERR_INVALID, "The timer callback is null!");
		return -ERR_INVALID;
	}

	if (timer_flag == MVBS_TIMER_ABSTIME) {
		mvbs_get_time(&tmp_sec, &tmp_nsec);
		if (t_ns < tmp_nsec) {
			t_sec -= 1;
			t_ns += (uint32_t)TIME_NSEC_PER_SEC;
		}

		tmp_sec = t_sec - tmp_sec;
		tmp_nsec = t_ns - tmp_nsec;
	} else {
		tmp_sec = t_sec;
		tmp_nsec = t_ns;
	}

	timer_interval_ticks = timer_calculate_interval_ticks(ptcp, tmp_sec,
								    tmp_nsec);

	if (timer_is_over_max_interval(timer_interval_ticks) == (bool)true) {
		pr_err(ERR_INVALID,
		       "The timer interval has reached the limit. max(%u)ticks, "
		       "the parameters sec(%d) ns(%u)",
		       MVBS_TIMER_MAX_TICK, tmp_sec, tmp_nsec);

		return -ERR_INVALID;
	}

	timer->interval_ticks = timer_interval_ticks;

	return 0;
}

timer_desc_t mvbs_timer_create(struct participant *ptcp, timer_handler_fn fn,
			       void *arg, uint8_t repeat)
{
	timer_desc_t	td = TIMER_DESC_INVALID;
	struct timer_handler *timer = NULL;

	if (fn == NULL) {
		return td;
	}

	timer = mem_pool_alloc(&ptcp->timers);
	if (timer == NULL) {
		return td;
	}

	mvbs_memzero(timer, sizeof(struct timer_handler));

	timer->handler		= fn;
	timer->user_data	= arg;
	if (repeat != 0u) {
		timer->repeat = 1u;
	} else {
		timer->repeat = 0u;
	}

	mvbs_list_init(&timer->l_node);

	ptcp->timer_wheel.total++;

	td = (timer_desc_t)mp_get_blk_data_idx(timer);

	return td;
}

void mvbs_timer_delete_internal(struct participant *ptcp, timer_desc_t td)
{
	struct timer_handler *timer = NULL;

	timer = get_timer_handler_by_td(ptcp, td);
	if (timer == NULL) {
		return;
	}

	timer_remove_entry(ptcp, timer);

	timer->enabled = 0;

	mem_pool_free(timer);

	ptcp->timer_wheel.total--;
}

/*
 * Just the set timeout of timer, but not start it.
 */
int32_t mvbs_timer_settime(struct participant *ptcp, timer_desc_t td,
			   uint32_t timer_flag, int32_t sec, uint32_t ns)
{
	struct timer_handler *timer = get_timer_handler_by_td(ptcp, td);

	if (timer == NULL) {
		return -ERR_INVALID;
	}

	return timer_set_time(ptcp, timer, timer_flag, sec, ns);
}

int32_t mvbs_timer_start(struct participant *ptcp, timer_desc_t td,
			 uint32_t timer_flag, int32_t sec, uint32_t ns)
{
	struct timer_handler *timer = NULL;
	int32_t ret = -ERR_INVALID;

	timer = get_timer_handler_by_td(ptcp, td);
	if (timer == NULL) {
		return ret;
	}

	ret = timer_set_time(ptcp, timer, timer_flag, sec, ns);
	if (ret != 0) {
		return ret;
	}

	timer_remove_entry(ptcp, timer);

	timer_schedule_entry(ptcp, timer);

	return 0;
}

int32_t mvbs_timer_restart(struct participant *ptcp, timer_desc_t td)
{
	struct timer_handler *timer = NULL;

	timer = get_timer_handler_by_td(ptcp, td);
	if (timer == NULL) {
		return -ERR_INVALID;
	}

	if (timer_is_over_max_interval(timer->interval_ticks)) {
		pr_err(ERR_FAULT,
		       "timer: restart timer failed! interval_ticks(%u)",
		       timer->interval_ticks);
		return -ERR_FAULT;
	}

	timer_remove_entry(ptcp, timer);

	timer_schedule_entry(ptcp, timer);

	return 0;
}

int32_t mvbs_timer_stop(struct participant *ptcp, timer_desc_t td)
{
	struct timer_handler *timer = NULL;

	timer = get_timer_handler_by_td(ptcp, td);
	if (timer == NULL) {
		return -ERR_INVALID;
	}

	timer_remove_entry(ptcp, timer);

	timer->enabled = 0;

	return 0;
}

void mvbs_timer_tick(struct participant *ptcp)
{
	struct mvbs_timer_wheel_node *wheel_node= NULL;
	struct timer_handler *timer		= NULL;
	struct timer_handler *n			= NULL;
	int8_t retry				= 0;
	uint16_t old_color			= 0;

	if (ptcp == NULL) {
		return ;
	}

	ptcp->timer_wheel.current_slot = (ptcp->timer_wheel.current_slot + 1U) % MVBS_TIMER_WHEEL_NUM;
	wheel_node = &ptcp->timer_wheel.wheel[ptcp->timer_wheel.current_slot];

	old_color = wheel_node->color;

	if (old_color == (uint16_t)E_TWNC_GREEN) {
		wheel_node->color = ((uint16_t)E_TWNC_BLUE);
	} else {
		wheel_node->color = ((uint16_t)E_TWNC_GREEN);
	}

	wheel_node->is_update = 0;

	if (mvbs_list_empty(&wheel_node->l_head[old_color]) == (bool)true) {
		return;
	}

	do {
		retry = 0;

		mvbs_list_for_each_entry_safe(timer, n,
					&wheel_node->l_head[old_color], l_node) {
			timer_node_remove(ptcp, &timer->l_node);

			if (timer->wheel_count != 0U) {
				--timer->wheel_count;

				mvbs_list_add_tail(&timer->l_node,
					&wheel_node->l_head[wheel_node->color]);

				continue;
			}

			timer->wheel_node = NULL;

			if (timer->repeat != 0U) {
				timer_schedule_entry(ptcp, timer);
			}

			timer->handler(timer->user_data);

			if (wheel_node->is_update != 0u) {
				wheel_node->is_update = 0;
				retry = 1;
				break;
			}
		}
	} while (retry == 1);
}

uint32_t mvbs_timer_get_resolution(struct participant *ptcp)
{
	return ptcp->timer_period_us;
}

void mvbs_timer_get_count(struct participant *ptcp, uint32_t *total,
			  uint32_t *active)
{
	if (active != NULL) {
		*active = ptcp->timer_wheel.active;
	}

	if (total != NULL) {
		*total = ptcp->timer_wheel.total;
	}
}

int32_t mvbs_timer_init(struct participant *ptcp, int32_t us)
{
	uint32_t i;
	int32_t  ret;

	struct mvbs_timer_wheel_node *wheel_node = NULL;

	if ((ptcp == NULL) || (us <= 0)) {
		return -ERR_INVALID;
	}

	ret = mem_pool_reset(&ptcp->timers);
	if (ret != 0) {
		pr_err(ret, "Fail to init timer pool of: %s.", ptcp->attr->name);
		return -ERR_INVALID;
	}

	for (i = 0; i < ARRAY_SIZE(ptcp->timer_wheel.wheel); ++i) {
		wheel_node = &ptcp->timer_wheel.wheel[i];

		mvbs_list_init(&wheel_node->l_head[E_TWNC_GREEN]);
		mvbs_list_init(&wheel_node->l_head[E_TWNC_BLUE]);
	}

	ptcp->timer_period_us = (uint32_t)us;
	pr_info("Timer resolution: %dus", ptcp->timer_period_us);

	return 0;
}

void mvbs_timer_deinit(struct participant *ptcp)
{
	struct mvbs_timer_wheel_node *wheel_node = NULL;
	struct timer_handler *timer = NULL;
	struct timer_handler *next = NULL;
	uint32_t i;

	if (ptcp == NULL) {
		return ;
	}

	for (i = 0; i < ARRAY_SIZE(ptcp->timer_wheel.wheel); ++i) {
		wheel_node = &ptcp->timer_wheel.wheel[i];

		mvbs_list_for_each_entry_safe(timer, next,
				&wheel_node->l_head[E_TWNC_GREEN], l_node) {
			timer_node_remove(ptcp, &timer->l_node);
		}

		mvbs_list_for_each_entry_safe(timer, next,
				&wheel_node->l_head[E_TWNC_BLUE], l_node) {
			timer_node_remove(ptcp, &timer->l_node);
		}
	}
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
