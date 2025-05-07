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
#include <mvbs/utils/tracepoint.h>
#include <mvbs/utils/log.h>
#include <mvbs/utils/string.h>

#ifdef CHECKPOINT_ENABLE

static struct mvbs_list hook_list = {
	.prev = &hook_list,
	.next = &hook_list,
};

int32_t checkpoint_register(struct checkpoint *cp)
{
	struct checkpoint *item;

	if (cp == NULL) {
		return -ERR_INVALID;
	}

	mvbs_list_for_each_entry(item, &hook_list, list) {
		if (item->num > cp->num) {
			break;
		}
	}

	mvbs_list_add_tail(&cp->list, &item->list);

	return 0;
}

int32_t checkpoint_unregister(struct checkpoint *cp)
{
	if (cp == NULL) {
		return -ERR_INVALID;
	}

	mvbs_list_del(&cp->list);

	return 0;
}

uint32_t checkpoint_covert_tag(const char *str)
{
	uint32_t sum	= 0;
	const char *s	= str;

	while (*s != '\0') {
		sum += (uint32_t)*s;
		s++;
	}

	pr_debug("[%d]%s", sum, s);

	return sum;
}

int32_t checkpoint_hook(uint32_t num, const char *key, int32_t id, void *args)
{
	struct checkpoint *item;
	int32_t ret = 0;

	mvbs_list_for_each_entry(item, &hook_list, list) {
		if (item->fn == NULL) {
			continue;
		}

		if (item->num < num) {
			continue;
		}

		if (item->num > num) {
			return -ERR_INVALID;
		}

		struct checkpoint_args ch_args = {
			.key = key,
			.id = id,
			.args = args,
		};

		ret = item->fn(&ch_args, sizeof(ch_args));
		if (ret == 0) {
			return 0;
		}
	}

	return 0;
}

static int32_t checkpoint_hook_default(const void *buff, int32_t size)
{
	(void) buff;
	(void) size;

	return 0;
}

checkpoint_cb_t checkpoint_find_fn(const char *str)
{
	struct checkpoint *item;

	mvbs_list_for_each_entry(item, &hook_list, list) {
		if (item->fn == NULL) {
			continue;
		}

		if (mvbs_strcmp(item->str, str) == 0) {
			return item->fn;
		}
	}

	return checkpoint_hook_default;
}

#endif

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
