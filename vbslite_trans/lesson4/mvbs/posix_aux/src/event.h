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

#ifndef MVBS_POSIX_AUX_EVENT_H
#define MVBS_POSIX_AUX_EVENT_H

#include <stdint.h>

struct mvbs_event;

struct mvbs_event *mvbs_event_create(void);
void mvbs_event_destroy(struct mvbs_event *event);

void mvbs_event_init(struct mvbs_event *event);
void mvbs_event_deinit(struct mvbs_event *event);

uint32_t mvbs_event_wait(struct mvbs_event *event);
void mvbs_event_send(struct mvbs_event *event, uint32_t ev);

#endif /* !MVBS_POSIX_AUX_EVENT_H */
