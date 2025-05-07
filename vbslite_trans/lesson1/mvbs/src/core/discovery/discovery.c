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

#include <core/core.h>
#include <mvbs/utils/log.h>
#include "dpse.h"
#include "dpde.h"

#if 0
#undef  MVBSLOG_LEVEL
#define MVBSLOG_LEVEL MVBSLOG_VERB
#endif

int32_t ptcp_discovery_init(struct participant *ptcp)
{
	int32_t ret;
	bool    result = false;

	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return -ERR_INVALID;
	}

	ret = ptcp_dpde_discovery_init(ptcp);
	if (ret == 0) {
		result = true;

		pr_info("participant [%s] DPDE inited successfully.",
							ptcp->attr->name);
	}

	ret = ptcp_dpse_discovery_init(ptcp);
	if (ret == 0) {
		result = true;

		pr_info("participant [%s] DPSE inited successfully.",
							ptcp->attr->name);
	}

	if (!result) {
		pr_info("Fail to init participant [%s] discovery.",
							ptcp->attr->name);
		return -ERR_INVALID;
	}

	return 0;
}

int32_t ptcp_discovery_start(struct participant *ptcp)
{
	int32_t ret;
	bool    result = false;

	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return -ERR_INVALID;
	}

	ret = ptcp_dpde_discovery_start(ptcp);
	if (ret == 0) {
		result = true;

		pr_info("participant [%s] DPDE start successfully.",
							ptcp->attr->name);
	}

	ret = ptcp_dpse_discovery_start(ptcp);
	if (ret == 0) {
		result = true;

		pr_info("participant [%s] DPSE start successfully.",
							ptcp->attr->name);
	}

	if (!result) {
		pr_info("Fail to start participant [%s] discovery.",
							ptcp->attr->name);
		return -ERR_INVALID;
	}

	return 0;
}

int32_t ptcp_discovery_stop(struct participant *ptcp)
{
	int32_t ret;
	bool    result = false;

	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return -ERR_INVALID;
	}

	ret = ptcp_dpde_discovery_stop(ptcp);
	if (ret == 0) {
		result = true;

		pr_info("participant [%s] DPDE stop successfully.",
							ptcp->attr->name);
	}

	ret = ptcp_dpse_discovery_stop(ptcp);
	if (ret == 0) {
		result = true;

		pr_info("participant [%s] DPSE stop successfully.",
							ptcp->attr->name);
	}

	if (!result) {
		pr_info("Fail to stop participant [%s] discovery.",
							ptcp->attr->name);
		return -ERR_INVALID;
	}

	return 0;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
