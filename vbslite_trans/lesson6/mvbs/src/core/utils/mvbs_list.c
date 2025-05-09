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

#include <mvbs/utils/mvbs_list.h>

bool mvbs_list_empty(const struct mvbs_list *list)
{
	return READ_ONCE(list->next) == list;
}

static inline void mvbs_list_insert_node(struct mvbs_list *node,
				      struct mvbs_list *prev,
				      struct mvbs_list *next)
{
	next->prev = node;
	node->next = next;
	node->prev = prev;
	WRITE_ONCE(prev->next, node);
}

static inline void mvbs_list_remove_node(struct mvbs_list *prev,
				      struct mvbs_list *next)
{
	next->prev = prev;
	WRITE_ONCE(prev->next, next);
}

static inline void mvbs_list_del_node(struct mvbs_list *node)
{
	mvbs_list_remove_node(node->prev, node->next);
}

void mvbs_list_add(struct mvbs_list *node, struct mvbs_list *list)
{
	mvbs_list_insert_node(node, list, list->next);
}

void mvbs_list_add_tail(struct mvbs_list *node, struct mvbs_list *list)
{
	mvbs_list_insert_node(node, list->prev, list);
}

void mvbs_list_del(struct mvbs_list *node)
{
	mvbs_list_del_node(node);
	node->next = NULL;
	node->prev = NULL;
}

void mvbs_list_init(struct mvbs_list *list)
{
	WRITE_ONCE(list->next, list);
	list->prev = list;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
