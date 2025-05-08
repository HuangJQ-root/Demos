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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <pthread.h>

#include "event.h"

struct mvbs_event {
	pthread_mutex_t lock;
	pthread_cond_t	cond;

	volatile uint32_t event;
};

void mvbs_event_init(struct mvbs_event *event)
{
	if (event == NULL) {
		return;
	}

	pthread_mutex_init(&event->lock, NULL);
	pthread_cond_init(&event->cond, NULL);

	event->event = 0;
}

void mvbs_event_deinit(struct mvbs_event *event)
{
	if (event == NULL) {
		return;
	}

	pthread_mutex_destroy(&event->lock);
	pthread_cond_destroy(&event->cond);
}

struct mvbs_event *mvbs_event_create(void)
{
	struct mvbs_event *event;

	event = malloc(sizeof(*event));

	mvbs_event_init(event);

	return event;
}

void mvbs_event_destroy(struct mvbs_event *event)
{
	mvbs_event_deinit(event);
	free(event);
}

uint32_t mvbs_event_wait(struct mvbs_event *event)
{
	uint32_t flags;

	if (event == NULL) {
		return 0;
	}

	pthread_mutex_lock(&event->lock);

	while (event->event == 0) {
		pthread_cond_wait(&event->cond, &event->lock);
	}

	flags		= event->event;
	event->event	= 0;

	pthread_mutex_unlock(&event->lock);

	return flags;
}

void mvbs_event_send(struct mvbs_event *event, uint32_t ev)
{
	if (event == NULL)
		return;

	pthread_mutex_lock(&event->lock);

	event->event |= ev;

	pthread_cond_signal(&event->cond); /* wakeup target thread */
	pthread_mutex_unlock(&event->lock);
}
