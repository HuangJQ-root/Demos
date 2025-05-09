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

#ifndef MVBS_UTILS_TRACEPOINT_H
#define MVBS_UTILS_TRACEPOINT_H

#include <mvbs/utils/mvbs_list.h>

struct checkpoint_args {
	const char		*key;
	int32_t			id;
	void			*args;
};

typedef	int32_t (*checkpoint_cb_t)(const void *buff, int32_t size);

struct checkpoint {
	uint32_t		num;
	const char		*str;
	checkpoint_cb_t		fn;

	struct mvbs_list	list;
};

#ifdef CHECKPOINT_ENABLE

#define CHECKPOINT_HOOK(num)	(void)checkpoint_hook(num, __FILE__, __LINE__, NULL)

#define CHECKPOINT_LABEL(str)								\
	do { 										\
		static uint32_t cp_label_##__LINE__;					\
		if (cp_label_##__LINE__ == 0U) {    					\
			cp_label_##__LINE__ = checkpoint_covert_tag(str);		\
		}                                					\
		(void)CHECKPOINT_HOOK(cp_label_##__LINE__);				\
	} while (mvbs_false)

#define CHECKPOINT_STRING(str)								\
	do { 										\
		static int32_t (*cp_str_##__LINE__)(const void *buff, int32_t size);	\
		if (cp_str_##__LINE__ == NULL) {    					\
			cp_str_##__LINE__ = checkpoint_find_fn(str);			\
		}                                					\
		(void)cp_str_##__LINE__(NULL, 0);					\
	} while (mvbs_false)


#define CHECKPOINT_PARAM(str, param) 							\
	do { 										\
		static uint32_t cp_label_##__LINE__; 					\
		if (cp_label_##__LINE__ == 0U) { 					\
			cp_label_##__LINE__ = checkpoint_covert_tag(str);		\
		}									\
		(void)checkpoint_hook(cp_label_##__LINE__, __FILE__, __LINE__, param);	\
	} while (mvbs_false);

int32_t checkpoint_register(struct checkpoint *cp);

int32_t checkpoint_unregister(struct checkpoint *cp);

uint32_t checkpoint_covert_tag(const char *str);

int32_t checkpoint_hook(uint32_t num, const char *key, int32_t id, void *args);

checkpoint_cb_t checkpoint_find_fn(const char *str);

#else

#define CHECKPOINT_HOOK(num)
#define CHECKPOINT_LABEL(str)
#define CHECKPOINT_STRING(str)

static inline int32_t checkpoint_register(struct checkpoint *cp)
{
	(void)cp;

	return -ERR_FAULT;
}

static inline int32_t checkpoint_unregister(struct checkpoint *cp)
{
	(void)cp;

	return -ERR_FAULT;
}

static inline int32_t checkpoint_covert_tag(const char *str)
{
	(void)str;

	return -ERR_FAULT;
}

static inline int32_t checkpoint_hook(int32_t num, const char *key, int32_t id, void *args)
{
	(void)num;
	(void)key;
	(void)id;
	(void)args;

	return -ERR_FAULT;
}

static inline checkpoint_cb_t checkpoint_find_fn(const char *str)
{
	(void)str;

	return NULL;
}

#endif /* CHECKPOINT_ENABLE */

#endif
