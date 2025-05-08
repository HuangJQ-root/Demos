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

#include <mvbs/errno.h>
#include <mvbs/core/transport/locator.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/log.h>

#ifndef	__MVBS_CORE_SOURCE__
#define __MVBS_CORE_SOURCE__
#endif
#include <mvbs/core/transport/udp_transport.h>

#include "utils.h"

#ifdef MVBS_ADAPTER_EXTRA_UTILS
#include <stdio.h>
#include <stdlib.h>

static int32_t extract_udp_info(const char* str, struct udp_info *udp_info)
{
	uint32_t a, b, c, d;
	uint32_t bits;

	uint32_t mask;

	sscanf(str, "%u.%u.%u.%u/%u", &a, &b, &c, &d, &bits);

	if ((a > 255) || (b > 255) || (c > 255) || (d > 255) || (bits > 32)) {
		pr_info("MVBS_LOCATOR_INFO: '%s' is invalid.", str);

		return -ERR_INVALID;
	}

	udp_info->addr[0] = (uint8_t)a;
	udp_info->addr[1] = (uint8_t)b;
	udp_info->addr[2] = (uint8_t)c;
	udp_info->addr[3] = (uint8_t)d;

	udp_info->addr_uint32_le = (d << 24) | (c << 16) | (b << 8) | a;

	mask = (0xFFFFFFFF << (32 - bits)) & 0xFFFFFFFF;

	udp_info->mask[0] = (uint8_t)(mask >> 24);
	udp_info->mask[1] = (uint8_t)(mask >> 16);
	udp_info->mask[2] = (uint8_t)(mask >> 8);
	udp_info->mask[3] = (uint8_t)mask;

	udp_info->mask_uint32_le = (udp_info->mask[3] << 24)
				 | (udp_info->mask[2] << 16)
				 | (udp_info->mask[1] << 8)
				 | (udp_info->mask[0]);
	return 0;
}

const struct udp_info *mvbs_get_udp_info_from_env(void)
{
	static struct udp_info	udp_info;
	int ret;
	char *preferred_locator = getenv("MVBS_LOCATOR_INFO");

	if (preferred_locator == NULL)
		return NULL;

	ret = extract_udp_info(preferred_locator, &udp_info);
	if (ret == 0) {
		pr_info("Locator has been change to:");
		pr_info("IP: %d.%d.%d.%d", udp_info.addr[0], udp_info.addr[1],
					   udp_info.addr[2], udp_info.addr[3]);
		pr_info("mask: %d.%d.%d.%d", udp_info.mask[0], udp_info.mask[1],
					     udp_info.mask[2], udp_info.mask[3]);
	}

	return &udp_info;
}

#endif
