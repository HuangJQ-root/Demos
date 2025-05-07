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

#ifndef MVBS_UTILS_MVBS_LIST_H
#define MVBS_UTILS_MVBS_LIST_H

#include <mvbs/utils/cdefs.h>

struct mvbs_list {
	struct mvbs_list *next, *prev;
};

#define MVBS_LIST_INIT(name)	{ &(name), &(name) }

#define MVBS_LIST_DEFINE(name)							\
	struct mvbs_list name = MVBS_LIST_INIT(name)

#define mvbs_list_entry(ptr, type, member)					\
	container_of(ptr, type, member)

#define mvbs_list_first_entry(ptr, type, member)				\
	mvbs_list_entry((ptr)->next, type, member)

#define mvbs_list_last_entry(ptr, type, member)					\
	mvbs_list_entry((ptr)->prev, type, member)

#define mvbs_list_next_entry(pos, member)					\
	mvbs_list_entry((pos)->member.next, __typeof__(*(pos)), member)

#define mvbs_list_prev_entry(pos, member)					\
	mvbs_list_entry((pos)->member.prev, __typeof__(*(pos)), member)

#define mvbs_list_for_each_entry(pos, head, member)				\
	for (pos = mvbs_list_first_entry(head, __typeof__(*pos), member);	\
	     &pos->member != (head);						\
	     pos = mvbs_list_next_entry(pos, member))

#define mvbs_list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = mvbs_list_first_entry(head, __typeof__(*pos), member),	\
		n = mvbs_list_next_entry(pos, member);				\
		&pos->member != (head);						\
		pos = n, n = mvbs_list_next_entry(n, member))

#define mvbs_list_for_each_pre_entry(pos, head, member)				\
	for (pos = mvbs_list_last_entry(head, __typeof__(*pos), member);	\
	     &pos->member != (head);						\
	     pos = mvbs_list_prev_entry(pos, member))


bool mvbs_list_empty(const struct mvbs_list *list);

void mvbs_list_add(struct mvbs_list *node, struct mvbs_list *list);

void mvbs_list_add_tail(struct mvbs_list *node, struct mvbs_list *list);

void mvbs_list_del(struct mvbs_list *node);

void mvbs_list_init(struct mvbs_list *list);

#endif
