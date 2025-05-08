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

#ifndef MVBS_POSIX_AUX_UTILS_H
#define MVBS_POSIX_AUX_UTILS_H

#include <stdint.h>

typedef void (*timer_loop_handler_t)(void *param);

struct mvbs_timer_loop *mvbs_timer_loop_create(timer_loop_handler_t fn,
					void *param, uint32_t peroid_ms);

#define MVBS_EV_TIMER				(1<<0)
#define MVBS_EV_RECV				(1<<1)
#define MVBS_EV_SEND				(1<<2)

static inline const char *mvbs_utils_event_string(uint32_t ev)
{
	static const char *string_tab[] = {
		"MVBS_EV_TIMER",
		"MVBS_EV_RECV",
		"MVBS_EV_RECV | MVBS_EV_TIMER",
		"MVBS_EV_SEND",
		"MVBS_EV_SEND | MVBS_EV_TIMER",
		"MVBS_EV_SEND | MVBS_EV_RECV",
		"MVBS_EV_SEND | MVBS_EV_RECV | MVBS_EV_TIMER",
	};

	if (ev > 7)
		return "Invalid Event";

	return string_tab[ev-1];
}

struct mvbs_event_loop *mvbs_event_loop_create(uint32_t peroid_ms);
uint32_t mvbs_event_loop_wait(struct mvbs_event_loop *loop);

#endif /* !MVBS_POSIX_AUX_UTILS_H */
