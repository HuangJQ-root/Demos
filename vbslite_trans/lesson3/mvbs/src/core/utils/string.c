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

#include <string.h>	/* FIXME: libc */
#include <mvbs/base_type.h>
#include <mvbs/utils/string.h>

void mvbs_memcpy(void *dest, const void *src, size_t size)
{
	(void)memcpy(dest, src, size);
}

void mvbs_memzero(void *mem, size_t size)
{
	(void)memset(mem, 0, size);
}

int32_t mvbs_memcmp(const void *left, const void *right, size_t size)
{
	return memcmp((const char*)left, (const char*)right, size);
}

void mvbs_memmove(void *dest, const void *src, size_t size)
{
	(void)memmove(dest, src, size);
}

void *mvbs_memchr(const void *s, int32_t c, size_t n)
{
	return memchr(s, c, n);
}

size_t mvbs_strlen(const char *s)
{
	return strlen(s);
}

int32_t mvbs_strcmp(const char *left, const char *right)
{
	if ((left != NULL) && (right != NULL)) {
		return strcmp(left, right);
	}

	return -1;
}

int32_t mvbs_strncmp(const char *left, const char *right, size_t num)
{
	return strncmp(left, right, num);
}

char *mvbs_strcpy(char *dest, const char *src)
{
	return strcpy(dest, src);
}

char *mvbs_strncpy(char *dest, const char *src, size_t n)
{
	return strncpy(dest, src, n);
}

char *mvbs_strcat(char *dest, const char *src)
{
	return strcat(dest, src);
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
