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
#include <mvbs/errno.h>
#include <mvbs/utils/time.h>
#include <mvbs/rtps/message.h>

static void ptcp_proxy_reset(participant_proxy_t *proxy, participant_t *ptcp)
{
	proxy->guid.prefix	  = GUIDPREFIX_UNKNOWN;
	proxy->guid.eid		  = ENTITYID_UNKNOWN;

	proxy->has_endpoints	  = 0;
	proxy->preferred	  = 0;
	proxy->expects_inline_qos = 0;

	locator_set_invalid(&(proxy->meta_mc_loc));
	locator_set_invalid(&(proxy->dfl_mc_loc));

	ptcp_proxy_set_uc_locs_invalid(proxy, ptcp_local_locator_count(ptcp));
}

bool ptcp_proxy_parse(struct participant *ptcp,
		      participant_proxy_t *ptcp_proxy, mvbs_cdr_t *cdr,
		      struct rtps_property_info *prop_info, uint32_t *status_info)
{
	bool ret;

	if ((ptcp_proxy == NULL) || (cdr == NULL) || (prop_info == NULL)) {
		pr_err(ERR_INVALID, "Invaild parameter, ptcp_name: %s.",
							ptcp->attr->name);
		return false;
	}

	ptcp_proxy_reset(ptcp_proxy, ptcp);

	ret = cdr_deserialize_ptcp_proxy(cdr, ptcp_proxy, ptcp, prop_info,
								status_info);

	return ret;
}

bool ptcp_proxy_update_default_uc_seclotor(participant_proxy_t *proxy,
					   struct participant *ptcp)
{
	locator_t *loc;
	uint8_t i;

	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "ptcp is NULL");
		return false;
	}

	if (proxy == NULL) {
		pr_err(ERR_INVALID, "ptcp_proxy is NULL, ptcp_name: %s.",
							ptcp->attr->name);
		return false;
	}

	loc = ptcp_proxy_get_user_uc_loc(proxy);

	for (i = 0; i < ptcp_local_locator_count(ptcp); i++) {
		if (ptcp_detect_master_link(ptcp, loc)) {
			proxy->dfl_uc_selector = i;

			return true;
		}

		loc = ptcp_proxy_get_next_uc_loc(loc);
	}

	return false;
}

const struct rtps_guid *ptcp_proxy_get_guid(const struct participant_proxy *proxy)
{
	return &proxy->guid;
}

void ptcp_proxy_init(participant_proxy_t *ptcp_proxy)
{
	if (ptcp_proxy == NULL) {
		pr_err(ERR_INVALID, "ptcp_proxy is NULL.");
		return;
	}

	ptcp_proxy->ptcp		= NULL;

	ptcp_proxy->proto_ver		= PROTOCOLVERSION;
	ptcp_proxy->vendor_id		= VENDOR_UNKNOWN;

	ptcp_proxy->guid.prefix		= GUIDPREFIX_UNKNOWN;
	ptcp_proxy->guid.eid		= ENTITYID_UNKNOWN;

	ptcp_proxy->expects_inline_qos	= false;
	ptcp_proxy->lease_duration	= SPDP_DEFAULT_REMOTE_LEASE_DURATION;

	ptcp_proxy->liveliness_td	= TIMER_DESC_INVALID;

	ptcp_proxy->edp_sub_discov_hb	= false;
	ptcp_proxy->edp_pub_discov_hb	= false;

	ptcp_proxy->has_endpoints	= false;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
