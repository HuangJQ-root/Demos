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

/*
 * These interfaces defined in this file are for EE2.5.
 */
#include <core/core.h>
#include <mvbs/rtps/guid.h>
#include <mvbs/mvbs.h>
#include <mvbs/diag/query.h>
#include <diag/query.h>

#ifdef MVBS_DIAG_REQUEST_WRITER_ENABLE
void __attribute__((weak)) print_ptcps_by_domain(struct rtps_guid *guid,
							char *ptcp_name,
							uint16_t index)
{
	(void)guid;
	(void)ptcp_name;
	(void)index;
}

/* request interface */

void get_ptcp_by_domain (uint8_t id)
{
	struct participant *ptcp 		= NULL;
	struct participant_proxy *ptcp_proxy 	= NULL;
	uint16_t index 				= 0u;
	ptcp = mvbs_get_ptcp();

	if (ptcp->attr->domain_id != id) {
		pr_warn("Error: Invalid domain_id\n");
		pr_warn("real_id: [%d]\n", ptcp->attr->domain_id);
		pr_warn("input_id: [%d]\n", id);
		return;
	}

	foreach_ptcp_proxy(ptcp, ptcp_proxy) {
		index++;
		print_ptcps_by_domain(&ptcp_proxy->guid,
					ptcp_proxy->ptcp_name,
					index);
	}
}

void get_ptcp_detail_info(struct rtps_guid *target_ptcp_guid)
{
	struct participant *ptcp 		= NULL;
	struct participant_proxy *ptcp_proxy	= NULL;
	int32_t cmd_kind 			= 0x40001001;
	const struct buildin_writer 		*w;

	ptcp = mvbs_get_ptcp();
	extern const struct buildin_writer dpde_writers[];
	w = &dpde_writers[DIAG_REQUEST_WRITER];

	foreach_ptcp_proxy(ptcp, ptcp_proxy) {

		if (!rtps_guid_equal(&ptcp_proxy->guid, target_ptcp_guid)) {
			continue;
		}
		query_request_send_data(w, ptcp_proxy,
				&cmd_kind,
				target_ptcp_guid);

	}

}

void get_wr_matched_guids(struct rtps_guid *target_guid)
{
	struct participant *ptcp 		= NULL;
	struct participant_proxy *ptcp_proxy 	= NULL;
	int32_t cmd_kind 			= 0x40001002;
	const struct buildin_writer 		*w;

	ptcp = mvbs_get_ptcp();
	extern const struct buildin_writer dpde_writers[];
	w = &dpde_writers[DIAG_REQUEST_WRITER];

	foreach_ptcp_proxy(ptcp, ptcp_proxy) {

		if (!rtps_guid_prefix_equal(&ptcp_proxy->guid.prefix,
						&target_guid->prefix)) {
			continue;
		}
		query_request_send_data(w, ptcp_proxy, &cmd_kind, target_guid);
	}

}

void get_w_send_info(struct rtps_guid *target_guid)
{
	struct participant *ptcp 		= NULL;
	struct participant_proxy *ptcp_proxy 	= NULL;
	int32_t cmd_kind 			= 0x40001003;
	const struct buildin_writer 		*w;

	ptcp = mvbs_get_ptcp();
	extern const struct buildin_writer dpde_writers[];
	w = &dpde_writers[DIAG_REQUEST_WRITER];

	foreach_ptcp_proxy(ptcp, ptcp_proxy) {

		if (!rtps_guid_prefix_equal(&ptcp_proxy->guid.prefix,
						&target_guid->prefix)) {
			continue;
		}
		query_request_send_data(w, ptcp_proxy, &cmd_kind, target_guid);
	}
}

void get_r_recv_info(struct rtps_guid *target_guid)
{
	struct participant *ptcp 		= NULL;
	struct participant_proxy *ptcp_proxy 	= NULL;
	int32_t cmd_kind 			= 0x40001004;
	const struct buildin_writer 		*w;

	ptcp = mvbs_get_ptcp();
	extern const struct buildin_writer dpde_writers[];
	w = &dpde_writers[DIAG_REQUEST_WRITER];

	foreach_ptcp_proxy(ptcp, ptcp_proxy) {
		if (!rtps_guid_prefix_equal(&ptcp_proxy->guid.prefix,
						&target_guid->prefix)) {
			continue;
		}
		query_request_send_data(w, ptcp_proxy, &cmd_kind, target_guid);
	}

}

void get_topic_guids(char *target_topic)
{
	struct participant *ptcp 		= NULL;
	struct participant_proxy *ptcp_proxy 	= NULL;
	int32_t cmd_kind 			= 0x40001005;
	const struct buildin_writer 		*w;

	ptcp = mvbs_get_ptcp();
	extern const struct buildin_writer dpde_writers[];
	w = &dpde_writers[DIAG_REQUEST_WRITER];

	foreach_ptcp_proxy(ptcp, ptcp_proxy) {
		query_request_send_data(w, ptcp_proxy, &cmd_kind, target_topic);
	}

}
#else
void get_ptcp_by_domain (uint8_t id)
{
	(void)id;
}

void get_ptcp_detail_info(struct rtps_guid *target_ptcp_guid)
{
	(void)target_ptcp_guid;
}

void get_wr_matched_guids(struct rtps_guid *target_guid)
{
	(void)target_guid;
}

void get_w_send_info(struct rtps_guid *target_guid)
{
	(void)target_guid;
}

void get_r_recv_info(struct rtps_guid *target_guid)
{
	(void)target_guid;
}

void get_topic_guids(char *target_topic)
{
	(void)target_topic;
}

#endif

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
