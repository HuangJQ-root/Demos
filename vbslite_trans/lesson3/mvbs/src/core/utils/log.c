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

#include <stdio.h>
#include <stdarg.h>
#include <mvbs/utils/cdefs.h>
#include <mvbs/utils/log.h>
#include <mvbs/adapter/adapter.h>

#pragma weak mvbs_log_print_post
void mvbs_log_print_post(uint32_t level, const char *message)
{
	(void)level;
	(void)message;
}

static char log_line[255];

static const mvbs_log_t log_level_trans_tab[6] = {
	[MVBSLOG_FATAL]	= MVBS_LOG_LEVEL_FATAL,
	[MVBSLOG_ERR]	= MVBS_LOG_LEVEL_ERROR,
	[MVBSLOG_WARN]	= MVBS_LOG_LEVEL_WARN,
	[MVBSLOG_INFO]	= MVBS_LOG_LEVEL_INFO,
	[MVBSLOG_DBG]	= MVBS_LOG_LEVEL_DEBUG,
	[MVBSLOG_VERB]	= MVBS_LOG_LEVEL_VERBOSE,
};

void mvbs_log_output(uint32_t level, const char *fmt, ...)
{
	va_list		arg;
	mvbs_log_t	mvbs_log_level;

	if (level >= ARRAY_SIZE(log_level_trans_tab)) {
		return ;
	}

	mvbs_log_level = log_level_trans_tab[level];

	va_start(arg, fmt);
	(void)vsnprintf(log_line, sizeof(log_line), fmt, arg);
	va_end(arg);

	mvbs_log_print(mvbs_log_level, log_line);
	mvbs_log_print_post(mvbs_log_level, log_line);
}

#ifdef __CTC__
static uint32_t mvbs_log_vsprint(char *log_line, uint32_t len, const char *fmt, ...)
{
	uint32_t	ret;
	va_list		arg;

	va_start(arg, fmt);
	len = vsnprintf(log_line, sizeof(log_line), fmt, arg);
	va_end(arg);

	return len;
}

void mvbs_log_output_errno(uint32_t level, const char *tag, uint32_t errno,
					  const char *fn,  uint32_t line,
					  const char *fmt, ...)
{
	uint32_t	len;
	va_list		arg;
	mvbs_log_t	mvbs_log_level;

	if (level >= ARRAY_SIZE(log_level_trans_tab)) {
		return ;
	}

	mvbs_log_level = log_level_trans_tab[level];

	len = mvbs_log_vsprint(log_line, sizeof(log_line),
						tag, errno, fn, log_line);

	va_start(arg, fmt);
	(void)vsnprintf(log_line + len, sizeof(log_line) - len, fmt, arg);
	va_end(arg);

	mvbs_log_print(mvbs_log_level, log_line);
	mvbs_log_print_post(mvbs_log_level, log_line);
}
#endif

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
