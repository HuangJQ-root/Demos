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

#ifndef MVBS_UTILS_LOG_H
#define MVBS_UTILS_LOG_H

#include <mvbs/base_type.h>

void mvbs_log_print_post(uint32_t level, const char *message);
void mvbs_log_output(uint32_t level, const char *fmt, ...);
#ifdef __CTC__
void mvbs_log_output_errno(uint32_t level, const char *tag, uint32_t errno,
					  const char *fn,  uint32_t line,
					  const char *fmt, ...);
#endif

enum {
	MVBSLOG_FATAL = 0,
	MVBSLOG_ERR,
	MVBSLOG_WARN,
	MVBSLOG_INFO,
	MVBSLOG_DBG,
	MVBSLOG_VERB,
};

#define TAG "MVBS"

#define MVBSLOG_TAG_FATAL	"[" TAG "/F] "
#define MVBSLOG_TAG_ERR		"[" TAG "/E] "
#define MVBSLOG_TAG_WARN	"[" TAG "/W] "
#define MVBSLOG_TAG_INFO	"[" TAG "/I] "
#define MVBSLOG_TAG_DBG		"[" TAG "/D] "
#define MVBSLOG_TAG_VERB	"[" TAG "/V] "

#ifndef MVBSLOG_LEVEL
#define MVBSLOG_LEVEL		MVBSLOG_INFO
#endif

#define MVBSLOG_CATEGORY	(0x04 << 24U)
#define MVBSLOG_MODULE_DEFAULT	(0x00 << 16U)

#ifndef	MVBSLOG_MODULE
#define MVBSLOG_MODULE		MVBSLOG_MODULE_DEFAULT
#endif

static inline uint32_t mvbs_error_code(int32_t err)
{
	uint32_t code;

	code = (err < 0) ? -err:err;

	return MVBSLOG_CATEGORY | MVBSLOG_MODULE | (code & 0xFFFFU);
}

#ifndef pr_fmt
#define pr_fmt(prefix, fmt)	prefix "[%s:%d] " fmt, __func__, __LINE__
#endif

#ifndef pr_fmt_error
#define pr_fmt_error(prefix, err_code, fmt) 				\
	prefix "[0x%07X] [%s:%d] " fmt, mvbs_error_code(err_code),	\
					__func__, __LINE__
#endif


#ifdef __CTC__
/*
 * tasking compiler doesn't support "##" in macro, incase the "+gcc" compiler
 * configure is not set.
 */
#define pr_comm(level, tag, ...)					\
	do {								\
		if (level <= MVBSLOG_LEVEL) {				\
			mvbs_log_output(level, tag __VA_ARGS__);	\
		}							\
	} while (mvbs_false)

#define pr_comm_errno(level, tag, errno, fn, line, ...)					\
	do {										\
		if (level <= MVBSLOG_LEVEL) {						\
			mvbs_log_output_errno(level, tag, mvbs_error_code(errno),	\
							fn, line, __VA_ARGS__);		\
		}									\
	} while (mvbs_false)

#define pr_fal(err_code, ...)							\
	pr_comm_errno(MVBSLOG_FATAL, MVBSLOG_TAG_FATAL "[0x%07X] [%s:%d] ", 	\
				err_code, __func__, __LINE__, __VA_ARGS__)

#define pr_err(err_code, ...)							\
	pr_comm_errno(MVBSLOG_ERR, MVBSLOG_TAG_ERR "[0x%07X] [%s:%d] ", 	\
				err_code, __func__, __LINE__, __VA_ARGS__)

#define pr_warn(...) pr_comm(MVBSLOG_WARN, MVBSLOG_TAG_WARN, __VA_ARGS__)

#define pr_info(...) pr_comm(MVBSLOG_INFO, MVBSLOG_TAG_INFO, __VA_ARGS__)

#define pr_debug(...) pr_comm(MVBSLOG_DBG, MVBSLOG_TAG_DBG, __VA_ARGS__)

#define pr_verb(...) pr_comm(MVBSLOG_VERB, MVBSLOG_TAG_VERB, __VA_ARGS__)
#else
#define pr_comm(level, fmt, ...)						\
	do {									\
		if (level <= MVBSLOG_LEVEL) {					\
			mvbs_log_output(level, fmt, ##__VA_ARGS__);		\
		}								\
	} while (0)

#define pr_fal(err_code, fmt, ...)						\
	pr_comm(MVBSLOG_FATAL, pr_fmt_error(MVBSLOG_TAG_FATAL, err_code, fmt),	\
							     ##__VA_ARGS__);

#define pr_err(err_code, fmt, ...)						\
	pr_comm(MVBSLOG_ERR, pr_fmt_error(MVBSLOG_TAG_ERR, err_code, fmt),	\
							     ##__VA_ARGS__);

#define pr_warn(fmt, ...)							\
	pr_comm(MVBSLOG_WARN, pr_fmt(MVBSLOG_TAG_WARN, fmt), ##__VA_ARGS__)

#define pr_info(fmt, ...)							\
	pr_comm(MVBSLOG_INFO, pr_fmt(MVBSLOG_TAG_INFO, fmt), ##__VA_ARGS__)

#define pr_debug(fmt, ...)							\
	pr_comm(MVBSLOG_DBG, pr_fmt(MVBSLOG_TAG_DBG, fmt), ##__VA_ARGS__)

#define pr_verb(fmt, ...)							\
	pr_comm(MVBSLOG_VERB, pr_fmt(MVBSLOG_TAG_VERB, fmt), ##__VA_ARGS__)
#endif

static inline void mvbs_hex_dump(void *src, size_t len, unsigned long addr)
{
	uint32_t *data = (uint32_t *)src;
	size_t count;

	len = len / sizeof(*data);

	for (count = 0; count < len; count++) {
		if ((count & 7) == 0)
			mvbs_log_output(MVBSLOG_INFO, "  %08lX:", addr + count*(sizeof(*data)));
		mvbs_log_output(MVBSLOG_INFO, " %08x ", *data);
		data++;
		if ((count & 7) == 7)
			mvbs_log_output(MVBSLOG_INFO, "\n");
	}

	if ((count & 7) != 0)
		mvbs_log_output(MVBSLOG_INFO, "\n");
}

#endif
