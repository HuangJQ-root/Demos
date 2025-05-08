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

#ifndef MVBS_CORE_ENTITIES_PARTICIPANT_PROXY_H
#define MVBS_CORE_ENTITIES_PARTICIPANT_PROXY_H

struct participant_proxy;

const struct rtps_guid *ptcp_proxy_get_guid(const struct participant_proxy *ptcp_proxy);

#ifdef __MVBS_CORE_SOURCE__

#include <mvbs/core/types.h>
#include <mvbs/core/discovery/buildin_proxy.h>
#include <mvbs/core/transport/locator.h>
#include <mvbs/rtps/time.h>
#include <mvbs/rtps/message.h>

struct participant;

#define MAX_PCTP_NAME_LEN			64U

struct participant_proxy {
	char ptcp_name[MAX_PCTP_NAME_LEN];	/* participant name */

	struct participant	*ptcp;		/* used for remote remote participant */

	struct rtps_version	proto_ver;	/* TBD */

	struct rtps_vendor_id	vendor_id;	/* TBD */

	struct rtps_guid	guid;		/* prefix */

	uint32_t		vbs_version;

	uint32_t		avail_builtin_eps;

	uint16_t		has_endpoints:1;
	uint16_t		preferred:1;
	uint16_t		expects_inline_qos:1;

	/* Discovery
	 * For compatibility with old discovery methods.
	 * If "Heartbeat_For_Discovery" has been sent, it will not
	 * respond to the other party's preemptive heartbeat.
	 */
	uint16_t		edp_sub_discov_hb:1;
	uint16_t		edp_pub_discov_hb:1;

	uint16_t		dserver_flag:1;
	uint16_t		dclient_flag:1;

	uint8_t			dfl_uc_selector;
	timer_desc_t		liveliness_td;

	duration_t		lease_duration;

	uint64_t		session_id;

	struct buildin_proxies	sddp_proxies;

	/* For redundant links:
	 *     +------ master link ------+
	 * A --+                         +---- B
	 *     +------ bakup  link ------+
	 *
	 * Multiple redundant links have a same multicast locator, and each
	 * link has a individual unicast locator.
	 */
	locator_t		meta_mc_loc;	/* buildin ep multicast */
	locator_t		dfl_mc_loc;	/* user    ep multicast */
};

typedef struct participant_proxy	participant_proxy_t;

/*   +=================+
 *   |                 |
 *   |   participant   |
 *   |                 |
 *   |     proxy       |
 *   |                 |     Redundant links means multiple locators
 *   +-----------------+
 *   | meta_uc_loc[0]  |     <---    ptcp_proxy_get_meta_uc_loc(proxy)
 *   | dfl_uc_loc[0]   |     <---    ptcp_proxy_get_user_uc_loc(proxy)
 *   +-----------------+
 *   | meta_uc_loc[1]  |     --->    buildin ep unicast location bakup 1
 *   | dfl_uc_loc[1]   |     --->    user    ep unicast location bakup 1
 *   +-----------------+
 *   | meta_uc_loc[2]  |     --->    buildin ep unicast location bakup ...
 *   | dfl_uc_loc[2]   |     --->    user    ep unicast location bakup ...
 *   +=================+
 */

static inline locator_t *ptcp_proxy_get_meta_uc_loc(const participant_proxy_t *proxy)
{
	return (locator_t *)(proxy + 1);
}

static inline locator_t *ptcp_proxy_get_user_uc_loc(const participant_proxy_t *proxy)
{
	return (locator_t *)(proxy + 1) + 1;
}

static inline locator_t *ptcp_proxy_get_next_uc_loc(locator_t *loc)
{
	return loc + 2;
}

static inline void ptcp_proxy_set_uc_locs_invalid(participant_proxy_t *proxy,
						  uint8_t max_loc_cnt)
{
	locator_t		*meta_uc_loc;
	locator_t		*user_uc_loc;

	meta_uc_loc = ptcp_proxy_get_meta_uc_loc(proxy);
	user_uc_loc = ptcp_proxy_get_user_uc_loc(proxy);

	for (uint8_t i = 0; i < max_loc_cnt; i++) {
		locator_set_invalid(meta_uc_loc);
		locator_set_invalid(user_uc_loc);

		meta_uc_loc = ptcp_proxy_get_next_uc_loc(meta_uc_loc);
		user_uc_loc = ptcp_proxy_get_next_uc_loc(user_uc_loc);
	}
}

static inline locator_t *ptcp_proxy_get_meta_mc_loc(participant_proxy_t *proxy)
{
	return &proxy->meta_mc_loc;
}

static inline locator_t *ptcp_proxy_get_user_mc_loc(participant_proxy_t *proxy)
{
	return &proxy->dfl_mc_loc;
}

static inline const char *ptcp_proxy_get_name(const participant_proxy_t *proxy)
{
	return (proxy == NULL)?"NULL":proxy->ptcp_name;
}

static inline bool ptcp_proxy_has_pub_writer(const participant_proxy_t *proxy)
{
	if (proxy == NULL) {
		return false;
	}

	return !!(proxy->avail_builtin_eps & DISC_BIE_PUBLICATION_ANNOUNCER);
}

static inline bool ptcp_proxy_has_pdp_reader(const participant_proxy_t *proxy)
{
	if (proxy == NULL) {
		return false;
	}

	return !!(proxy->avail_builtin_eps & DISC_BIE_PARTICIPANT_DETECTOR);
}

static inline bool ptcp_proxy_has_pdp_writer(const participant_proxy_t *proxy)
{
	if (proxy == NULL) {
		return false;
	}

	return !!(proxy->avail_builtin_eps & DISC_BIE_PARTICIPANT_ANNOUNCER);
}

static inline bool ptcp_proxy_has_pub_reader(const participant_proxy_t *proxy)
{
	if (proxy == NULL) {
		return false;
	}

	return !!(proxy->avail_builtin_eps & DISC_BIE_PUBLICATION_DETECTOR);
}

static inline bool ptcp_proxy_has_sub_writer(const participant_proxy_t *proxy)
{
	if (proxy == NULL) {
		return false;
	}

	return !!(proxy->avail_builtin_eps & DISC_BIE_SUBSCRIPTION_ANNOUNCER);
}

static inline bool ptcp_proxy_has_sub_reader(const participant_proxy_t *proxy)
{
	if (proxy == NULL) {
		return false;
	}

	return !!(proxy->avail_builtin_eps & DISC_BIE_SUBSCRIPTION_DETECTOR);
}

static inline bool ptcp_proxy_has_wlp_reader(const participant_proxy_t *proxy)
{
	if (proxy == NULL) {
		return false;
	}

	return !!(proxy->avail_builtin_eps & BIE_PARTICIPANT_MESSAGE_DATA_READER);
}

static inline bool ptcp_proxy_has_wlp_writer(const participant_proxy_t *proxy)
{
	if (proxy == NULL) {
		return false;
	}

	return !!(proxy->avail_builtin_eps & BIE_PARTICIPANT_MESSAGE_DATA_WRITER);
}

static inline bool ptcp_proxy_has_diag_request_reader(const participant_proxy_t *proxy)
{
	if (proxy == NULL) {
		return false;
	}

	return !!(proxy->avail_builtin_eps & DISC_BIE_DIAG_REQUEST_READER);
}

static inline bool ptcp_proxy_has_diag_request_writer(const participant_proxy_t *proxy)
{
	if (proxy == NULL) {
		return false;
	}

	return !!(proxy->avail_builtin_eps & DISC_BIE_DIAG_REQUEST_WRITER);
}

static inline bool ptcp_proxy_has_diag_reply_reader(participant_proxy_t *proxy)
{
	if (proxy == NULL) {
		return false;
	}

	return !!(proxy->avail_builtin_eps & DISC_BIE_DIAG_REPLY_READER);
}

static inline bool ptcp_proxy_has_diag_reply_writer(participant_proxy_t *proxy)
{
	if (proxy == NULL) {
		return false;
	}

	return !!(proxy->avail_builtin_eps & DISC_BIE_DIAG_REPLY_WRITER);
}

static inline void ptcp_proxy_set_dserver_flag(participant_proxy_t *proxy)
{
	if (proxy == NULL) {
		return;
	}

	proxy->dserver_flag = 1U;
}

static inline bool ptcp_proxy_is_dserver(participant_proxy_t *proxy)
{
	if (proxy == NULL) {
		return false;
	}

	return (proxy->dserver_flag == 1U);
}

static inline void ptcp_proxy_set_dclient_flag(participant_proxy_t *proxy)
{
	if (proxy == NULL) {
		return;
	}

	proxy->dclient_flag = 1U;
}

static inline bool ptcp_proxy_is_dclient(participant_proxy_t *proxy)
{
	if (proxy == NULL) {
		return false;
	}

	return (proxy->dclient_flag == 1U);
}

bool ptcp_proxy_update_default_uc_seclotor(participant_proxy_t *proxy,
					   struct participant *ptcp);

void ptcp_proxy_init(participant_proxy_t *ptcp_proxy);

#endif
#endif
