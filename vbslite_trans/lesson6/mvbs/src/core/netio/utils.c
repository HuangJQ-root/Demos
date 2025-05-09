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
#include <mvbs/utils/string.h>
#include <mvbs/core/netio/utils.h>
#include <mvbs/core/netio/socket.h>

#define IS_DIGIT(ch) ((ch) >= '0' && (ch) <= '9')


int32_t mvbs_inet_aton(const char *src, uint32_t*inp)
{
	uint8_t tmp[sizeof(uint32_t)];

	int32_t octets		= 0;
	uint8_t *tp		= tmp;
	uint8_t *dst		= (uint8_t*)inp;
	uint32_t value		= 0;
	const char *tmp_src	= src;
	const char *end		= src + mvbs_strlen(src);

	if ((src == NULL) || (end == NULL) || (dst == NULL)) {
		return 0;
	}

	*tp = 0U;

	while (tmp_src < end) {
		char ch = *tmp_src;
		tmp_src++;

		if (ch == '.') {
			octets++;

			if (octets > 3) {
				return 0;
			}

			tp++;
			*tp = 0U;
		} else if (IS_DIGIT(ch)) {
			value = (*tp * 10U) + (ch - '0');

			if (value > 255U) {
				return 0;
			}

			*tp = (uint8_t)value;
		} else {
			return 0;
		}
	}

	if (octets != 3) {
		return 0;
	}

	mvbs_memcpy(dst, tmp, sizeof(uint32_t));

	return 1;
}

#define MVBS_ENABLE_BENCHMARK

#ifdef  MVBS_ENABLE_BENCHMARK

#pragma weak DDS_Transmit2Tcp_Prehook
void DDS_Transmit2Tcp_Prehook(const char *topic_name)
{
	(void)topic_name;
}

#pragma weak DDS_Transmit2Tcp_Posthook
void DDS_Transmit2Tcp_Posthook(const char *topic_name)
{
	(void)topic_name;
}

static const char *writer_topic_name = NULL;

void udp_transmit_hook_set_topicname(const char *topic_name)
{
	writer_topic_name = topic_name;
}

void udp_transmit_hook_clr_topicname(void)
{
	writer_topic_name = NULL;
}

void udp_transmit_prev_hook(void)
{
	if (writer_topic_name != NULL) {
		DDS_Transmit2Tcp_Prehook(writer_topic_name);
	}
}

void udp_transmit_post_hook(void)
{
	if (writer_topic_name != NULL) {
		DDS_Transmit2Tcp_Posthook(writer_topic_name);

		writer_topic_name = NULL;
	}
}
#else
void udp_transmit_hook_set_topicname(const char *topicname)
{
	(void)topic_name;
}

void udp_transmit_hook_clr_topicname(void)
{
}

static inline void udp_transmit_prev_hook(void)
{
}

static inline void udp_transmit_post_hook(void)
{
}
#endif

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
