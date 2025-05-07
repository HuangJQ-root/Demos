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
#include <diag/diag.h>
#include <mvbs/utils/time.h>
#include <mvbs/utils/timer.h>
#include "spdp.h"
#include "sedp.h"

#ifdef MVBS_DIAG_REPLY_READER_ENABLE
#pragma weak ptcp_proxy_on_change
#endif
void ptcp_proxy_on_change(const struct participant_proxy *ptcp_proxy, bool online)
{
	(void)ptcp_proxy;
	(void)online;
}

/* FIXME:
 * The writer&reader should be change to dd_writer&dd_reader. And proxy object
 * should be change dd_writer_proxy & dd_reader_proxy.
 */

static void ptcp_dpde_reader_on_gap(const struct buildin_reader *r,
				  const struct participant_proxy *ptcp_proxy,
				  const struct submessage_gap *msg)
{
	(void)ptcp_proxy;
	(void)msg;

	pr_verb("EP: %s Get a gap.", r->name);

	return ;
}

const struct buildin_reader dpde_readers[] = {
	[PDP_READER] = {
		.name			= "MVBS::SPDP::pdp_reader",
		.eid			= {
			.entity_key	= { 0, 1, 0 },
			.entity_kind	= BUILD_IN_READER_WITH_KEY,
		},
		.remote_eid		= {
			.entity_key	= { 0, 1, 0 },
			.entity_kind	= BUILD_IN_WRITER_WITH_KEY,
		},
		.on_gap			= NULL,
		.on_hearbeat		= NULL,
		.on_data		= ptcp_pdp_reader_on_data,
		.on_ptcp_online		= NULL,
		.on_ptcp_offline	= NULL,
	},
	[PUB_READER] = {
		.name			= "MVBS::SEDP::pub_reader",
		.eid			= {
			/* ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER */
			.entity_key	= { 0, 0, 3 },
			.entity_kind	= BUILD_IN_READER_WITH_KEY,
		},
		.remote_eid		= {
			/* ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER */
			.entity_key	= { 0, 0, 3 },
			.entity_kind	= BUILD_IN_WRITER_WITH_KEY,
		},
		.on_gap			= ptcp_dpde_reader_on_gap,
		.on_hearbeat		= pub_reader_on_heartbeat,
		.on_data		= pub_reader_on_data,
		.on_ptcp_online		= pub_reader_on_ptcp_online,
		.on_ptcp_offline	= NULL,
	},
	[SUB_READER] = {
		.name			= "MVBS::SEDP::sub_reader",
		.eid			= {
			/* ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER */
			.entity_key	= { 0, 0, 4 },
			.entity_kind	= BUILD_IN_READER_WITH_KEY,
		},
		.remote_eid		= {
			/* ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER */
			.entity_key	= { 0, 0, 4 },
			.entity_kind	= BUILD_IN_WRITER_WITH_KEY,
		},
		.on_gap			= ptcp_dpde_reader_on_gap,
		.on_hearbeat		= sub_reader_on_heartbeat,
		.on_data		= sub_reader_on_data,
		.on_ptcp_online		= sub_reader_on_ptcp_online,
		.on_ptcp_offline	= NULL,
	},
	[P2P_READER] = {
		.name			= "MVBS::WLP::p2p_reader",
		.eid			= {
			/* ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_READER */
			.entity_key	= { 0, 2, 0 },
			.entity_kind	= BUILD_IN_READER_WITH_KEY,
		},
		.remote_eid		= {
			/* ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_WRITER */
			.entity_key	= { 0, 2, 0 },
			.entity_kind	= BUILD_IN_WRITER_WITH_KEY,
		},
		.on_gap			= ptcp_dpde_reader_on_gap,
		.on_hearbeat		= p2p_reader_on_heartbeat,
		.on_data		= p2p_reader_on_data,
		.on_ptcp_online		= p2p_reader_on_ptcp_online,
		.on_ptcp_offline	= NULL,
	},
#ifdef MVBS_DIAG_REQUEST_READER_ENABLE
	[DIAG_REQUEST_READER] = {
		.name			= "MVBS::DIAG::request_reader",
		.eid			= {
			/* ENTITYID_DIAG_REQUEST_READER */
			.entity_key	= { 0, 3, 0 },
			.entity_kind	= BUILD_IN_READER_WITHOUT_KEY,
		},
		.remote_eid		= {
			/* ENTITYID_DIAG_REQUEST_WRITER */
			.entity_key	= { 0, 3, 0 },
			.entity_kind	= BUILD_IN_WRITER_WITHOUT_KEY,
		},
		.on_gap			= NULL,
		.on_hearbeat		= diag_request_on_heartbeat,
		.on_data		= diag_request_on_data,
		.on_ptcp_online		= diag_request_reader_on_ptcp_online,
		.on_ptcp_offline	= diag_request_reader_on_ptcp_offline,
	},
#endif
#ifdef MVBS_DIAG_REPLY_READER_ENABLE
	[DIAG_REPLY_READER] = {
		.name			= "MVBS::DIAG::reply_reader",
		.eid			= {
			/* ENTITYID_DIAG_REPLY_READER */
			.entity_key	= { 0, 3, 1 },
			.entity_kind	= BUILD_IN_READER_WITHOUT_KEY,
		},
		.remote_eid		= {
			/* ENTITYID_DIAG_REPLY_WRITER */
			.entity_key	= { 0, 3, 1 },
			.entity_kind	= BUILD_IN_WRITER_WITHOUT_KEY,
		},
		.on_gap			= NULL,
		.on_hearbeat		= diag_reply_on_heartbeat,
		.on_data		= diag_reply_on_data,
		.on_ptcp_online		= diag_reply_reader_on_ptcp_online,
		.on_ptcp_offline	= diag_reply_reader_on_ptcp_offline,
	},
#endif
};

const struct buildin_writer dpde_writers[] = {
	[PDP_WRITER] = {
		.name			= "MVBS::SPDP::pdp_writer",
		.eid			= {
			.entity_key	= { 0, 1, 0 },
			.entity_kind	= BUILD_IN_WRITER_WITH_KEY,
		},
		.remote_eid		= {
			.entity_key	= { 0, 1, 0 },
			.entity_kind	= BUILD_IN_READER_WITH_KEY,
		},
		.backup_link_enabled	= false,
		.on_acknack		= NULL,
		.on_ptcp_online		= NULL,
		.on_ptcp_offline	= NULL,
	},
	[PUB_WRITER] = {
		.name			= "MVBS::SEDP::pub_writer",

		.eid			= {
			/* ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER */
			.entity_key	= { 0, 0, 3 },
			.entity_kind	= BUILD_IN_WRITER_WITH_KEY,
		},
		.remote_eid		= {
			/* ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER */
			.entity_key	= { 0, 0, 3 },
			.entity_kind	= BUILD_IN_READER_WITH_KEY,
		},
		.backup_link_enabled	= false,
		.on_acknack		= pub_writer_on_acknack,
		.on_ptcp_online		= pub_writer_on_ptcp_online,
		.on_ptcp_offline	= NULL,
	},
	[SUB_WRITER] = {
		.name			= "MVBS::SEDP::sub_writer",

		.eid			= {
			/* ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER */
			.entity_key	= { 0, 0, 4 },
			.entity_kind	= BUILD_IN_WRITER_WITH_KEY,
		},
		.remote_eid		= {
			/* ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER */
			.entity_key	= { 0, 0, 4 },
			.entity_kind	= BUILD_IN_READER_WITH_KEY,
		},
		.backup_link_enabled	= false,
		.on_acknack		= sub_writer_on_acknack,
		.on_ptcp_online		= sub_writer_on_ptcp_online,
		.on_ptcp_offline	= NULL,
	},
	[P2P_WRITER] = {
		.name			= "MVBS::WLP::p2p_writer",
		.eid			= {
			/* ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_WRITER */
			.entity_key	= { 0, 2, 0 },
			.entity_kind	= BUILD_IN_WRITER_WITH_KEY,
		},
		.remote_eid		= {
			/* ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_READER */
			.entity_key	= { 0, 2, 0 },
			.entity_kind	= BUILD_IN_READER_WITH_KEY,
		},
		.backup_link_enabled	= false,
		.on_acknack		= p2p_writer_on_acknack,
		.on_ptcp_online		= p2p_writer_on_ptcp_online,
		.on_ptcp_offline	= NULL,
	},
#ifdef MVBS_DIAG_REQUEST_WRITER_ENABLE
	[DIAG_REQUEST_WRITER] = {
		.name			= "MVBS::DIAG::request_writer",
		.eid			= {
			/* ENTITYID_DIAG_REQUEST_WRITER */
			.entity_key	= { 0, 3, 0 },
			.entity_kind	= BUILD_IN_WRITER_WITHOUT_KEY,
		},
		.remote_eid		= {
			/* ENTITYID_DIAG_REQUEST_READER */
			.entity_key	= { 0, 3, 0 },
			.entity_kind	= BUILD_IN_READER_WITHOUT_KEY,
		},
		.backup_link_enabled	= false,
		.on_acknack		= diag_request_on_acknack,
		.on_ptcp_online		= diag_request_writer_on_ptcp_online,
		.on_ptcp_offline	= diag_request_writer_on_ptcp_offline,
	},
#endif
#ifdef MVBS_DIAG_REPLY_WRITER_ENABLE
	[DIAG_REPLY_WRITER] = {
		.name			= "MVBS::DIAG::reply_writer",
		.eid			= {
			/* ENTITYID_DIAG_REPLY_WRITER */
			.entity_key	= { 0, 3, 1 },
			.entity_kind	= BUILD_IN_WRITER_WITHOUT_KEY,
		},
		.remote_eid		= {
			/* ENTITYID_DIAG_REPLY_READER */
			.entity_key	= { 0, 3, 1 },
			.entity_kind	= BUILD_IN_READER_WITHOUT_KEY,
		},
		.backup_link_enabled	= false,
		.on_acknack		= diag_reply_on_acknack,
		.on_ptcp_online		= diag_reply_writer_on_ptcp_online,
		.on_ptcp_offline	= diag_reply_writer_on_ptcp_offline,
	},
#endif
};

bool ptcp_dpde_on_acknack(const struct message_receiver *msg_info,
		     const struct submessage_acknack *acknack)
{
	uint32_t i=0;

	if (acknack->writer_id.entity_kind != BUILD_IN_WRITER_WITH_KEY &&
		acknack->writer_id.entity_kind != BUILD_IN_WRITER_WITHOUT_KEY) {
		return false;
	}

	if (msg_info->ptcp_proxy == NULL) {
		pr_debug("Fail to find related ptcp proxy.");
		return true;
	}

	if (msg_info->ptcp->attr->discovery.edp_type == STATIC_EDP) {
		return true;
	}

	for (i=0; i<ARRAY_SIZE(dpde_writers); i++) {
		const struct buildin_writer *w = &dpde_writers[i];

		if (!rtps_entity_id_equal(&acknack->writer_id, &w->eid)) {
			continue;
		}

		pr_debug("--> %s get acknack from %s", w->name,
				msg_info->ptcp_proxy->ptcp_name);

		if (w->on_acknack != NULL) {
			w->on_acknack(w, msg_info->ptcp_proxy, acknack);
		}

		break;
	}

	return true;
}

bool ptcp_dpde_on_heartbeat(const struct message_receiver *msg_info,
			       const struct submessage_heartbeat *hb)
{
	uint32_t i=0;

	if (hb->reader_id.entity_kind != BUILD_IN_READER_WITH_KEY &&
		hb->reader_id.entity_kind != BUILD_IN_READER_WITHOUT_KEY) {
		return false;
	}

	if (msg_info->ptcp_proxy == NULL) {
		pr_debug("Fail to find related ptcp proxy.");
		return true;
	}

	if (msg_info->ptcp->attr->discovery.edp_type == STATIC_EDP) {
		return true;
	}

	for (i = 0; i < ARRAY_SIZE(dpde_readers); i++) {
		const struct buildin_reader *r = &dpde_readers[i];

		if (!rtps_entity_id_equal(&hb->reader_id, &r->eid)) {
			continue;
		}

		pr_debug("--> %s get heartbeat from %s", r->name,
				msg_info->ptcp_proxy->ptcp_name);

		if (r->on_hearbeat != NULL) {
			r->on_hearbeat(r, msg_info->ptcp_proxy, hb);
		}

		break;
	}

	return true;
}

bool ptcp_dpde_on_gap(const struct message_receiver *msg_info,
			 const struct submessage_gap *gap)
{
	uint32_t i=0;

	if (gap->reader_id.entity_kind != BUILD_IN_READER_WITH_KEY &&
		gap->reader_id.entity_kind != BUILD_IN_READER_WITHOUT_KEY) {
		return false;
	}

	if (msg_info->ptcp_proxy == NULL) {
		pr_debug("Fail to find related ptcp proxy.");
		return true;
	}

	if (msg_info->ptcp->attr->discovery.edp_type == STATIC_EDP) {
		return true;
	}

	for (i=0; i<ARRAY_SIZE(dpde_readers); i++) {
		const struct buildin_reader *r = &dpde_readers[i];

		if (!rtps_entity_id_equal(&gap->reader_id, &r->eid)) {
			continue;
		}

		pr_debug("--> %s get gap from %s", r->name,
				msg_info->ptcp_proxy->ptcp_name);

		if (r->on_gap != NULL) {
			r->on_gap(r, msg_info->ptcp_proxy, gap);
		}

		break;
	}

	return true;
}

bool ptcp_dpde_on_data(const struct message_receiver *msg_info,
		       const struct submessage_data *msg,
		       const uint8_t *pdata, uint16_t size)
{
	uint32_t i = 0;

	const struct submessage_data_extra extra = {
		.ptcp		= msg_info->ptcp,
		.info_ts	= &msg_info->info_ts,
		.data		= pdata,
		.size		= size,
	};

	if (msg->reader_id.entity_kind != BUILD_IN_READER_WITH_KEY &&
		msg->reader_id.entity_kind != BUILD_IN_READER_WITHOUT_KEY &&
		msg->writer_id.entity_kind != BUILD_IN_WRITER_WITH_KEY &&
		msg->writer_id.entity_kind != BUILD_IN_WRITER_WITHOUT_KEY) {
		return false;
	}

	if (msg_info->ptcp->attr->discovery.edp_type == STATIC_EDP) {
		const struct buildin_reader *r = &dpde_readers[PDP_READER];

		if (rtps_entity_id_equal(&msg->reader_id, &r->eid)) {
			r->on_data(r, msg_info->ptcp_proxy, msg, &extra);
		}

		return true;
	}

	for (i = 0; i < ARRAY_SIZE(dpde_readers); i++) {
		/*
		 * Dsever PDP: reader_id is unknown,
		 * writer_id is PDP_BUILTIN_PARTICIPANT_WRITER
		 */
		if (rtps_entity_id_equal(&msg->writer_id,
					 &ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER)) {
			const struct buildin_reader *r = &dpde_readers[0];
			if (r->on_data != NULL) {
				r->on_data(r, msg_info->ptcp_proxy, msg, &extra);
			}
			break;
		}

		if (!rtps_entity_id_equal(&msg->reader_id,
					  &ENTITYID_SPDP_BUILTIN_PARTICIPANT_READER)) {
			if (msg_info->ptcp_proxy == NULL) {
				return false;
			}
		}

		const struct buildin_reader *r = &dpde_readers[i];

		if (!rtps_entity_id_equal(&msg->reader_id, &r->eid)) {
			continue;
		}

		pr_debug("--> %s get data from %s", r->name,
				msg_info->ptcp_proxy->ptcp_name);

		if (r->on_data != NULL) {
			r->on_data(r, msg_info->ptcp_proxy, msg, &extra);
		}

		break;
	}

	return true;
}

void ptcp_dpde_on_remote_online(struct participant *ptcp,
				 struct participant_proxy *ptcp_proxy)
{
	uint32_t i=0;

	if (ptcp->attr->discovery.edp_type == STATIC_EDP) {
		return;
	}

	for (i=0; i<ARRAY_SIZE(dpde_writers); i++) {
		const struct buildin_writer *w = &dpde_writers[i];

		if (w->on_ptcp_online == NULL) {
			continue;
		}

		w->on_ptcp_online(w, ptcp, ptcp_proxy);
	}

	for (i=0; i<ARRAY_SIZE(dpde_readers); i++) {
		const struct buildin_reader *r = &dpde_readers[i];

		if (r->on_ptcp_online == NULL) {
			continue;
		}

		r->on_ptcp_online(r, ptcp, ptcp_proxy);
	}

	ptcp_proxy_on_change(ptcp_proxy, true);
}

void ptcp_dpde_on_remote_offline(struct participant *ptcp,
				  struct participant_proxy *ptcp_proxy)
{
	uint32_t i=0;

	if (ptcp->attr->discovery.edp_type == STATIC_EDP) {
		return;
	}

	for (i=0; i<ARRAY_SIZE(dpde_readers); i++) {
		const struct buildin_reader *r = &dpde_readers[i];

		if (r->on_ptcp_offline == NULL) {
			continue;
		}

		r->on_ptcp_offline(r, ptcp, ptcp_proxy);
	}

	for (i=0; i<ARRAY_SIZE(dpde_writers); i++) {
		const struct buildin_writer *w = &dpde_writers[i];

		if (w->on_ptcp_offline == NULL) {
			continue;
		}

		w->on_ptcp_offline(w, ptcp, ptcp_proxy);
	}

	ptcp_proxy_on_change(ptcp_proxy, false);
}

static void ptcp_dpde_announce_timer(void *args)
{
	struct participant	 *ptcp = (struct participant *)args;
	const participant_attr_t *attr = ptcp->attr;
	const duration_t	 *period;

	ptcp_spdp_writer_send_pdp(ptcp, NULL, NULL, NULL);

	ptcp->announce_count++;

	if (!ptcp->boost) {
		return ;
	}

	if (ptcp->announce_count >= attr->discovery.initial_announce_count) {
		period = &attr->discovery.lease_duration_announce_period;

		(void)mvbs_timer_update_timeout(ptcp, ptcp->pdp_announce_td,
					      MVBS_TIMER_RELTIME,
					      period->seconds, period->nanosec);

		ptcp->boost = false;
	}
}

static void ptcp_dpde_pub_writer_hb_timer(void *private)
{
	struct participant	 *ptcp = private;
	struct participant_proxy *proxy;

	foreach_ptcp_proxy(ptcp, proxy) {
		pub_writer_send_hearbeat(proxy, false);
	}
}

static void ptcp_dpde_sub_writer_hb_timer(void *private)
{
	struct participant	 *ptcp = private;
	struct participant_proxy *proxy;

	foreach_ptcp_proxy(ptcp, proxy) {
		sub_writer_send_hearbeat(proxy, false);
	}
}

static void ptcp_dpde_p2p_writer_hb_timer(void *private)
{
	struct participant	 *ptcp = private;
	struct participant_proxy *proxy;

	foreach_ptcp_proxy(ptcp, proxy) {
		p2p_writer_send_hearbeat(proxy, false);
	}
}

int32_t ptcp_dpde_discovery_init(struct participant *ptcp)
{
	int32_t sec;
	int32_t nsec;

	if ((ptcp == NULL) || (ptcp->pdp_announce_td != TIMER_DESC_INVALID)) {
		pr_err(ERR_INVALID, "Invalid parameter.");
		return -ERR_INVALID;
	}

	if (ptcp->attr->discovery.edp_type != DYNAMIC_EDP) {
		return -ERR_INVALID;
	}

	ptcp->pdp_announce_td = mvbs_timer_create(ptcp, ptcp_dpde_announce_timer, ptcp, 1);
	if (ptcp->pdp_announce_td == TIMER_DESC_INVALID) {
		pr_err(ERR_NOMEM, "Fail to create ptcp liveliness timer.");
		return -ERR_NOMEM;
	}

	(void)mvbs_timer_settime(ptcp, ptcp->pdp_announce_td, MVBS_TIMER_RELTIME,
			 ptcp->attr->discovery.initial_announce_period.seconds,
			 ptcp->attr->discovery.initial_announce_period.nanosec);

	ptcp->pub_writer_hb_count = 1;
	ptcp->sub_writer_hb_count = 1;
	ptcp->p2p_writer_hb_count = 1;

	ptcp->pub_writer_hb_td = mvbs_timer_create(ptcp, ptcp_dpde_pub_writer_hb_timer, ptcp, 1);
	if (ptcp->pub_writer_hb_td == TIMER_DESC_INVALID) {
		pr_err(ERR_NOMEM, "Fail to create pub writer hb timer.");

		goto FAIL_PUB_HB_TIMER;
	}

	ptcp->sub_writer_hb_td = mvbs_timer_create(ptcp, ptcp_dpde_sub_writer_hb_timer, ptcp, 1);
	if (ptcp->sub_writer_hb_td == TIMER_DESC_INVALID) {
		pr_err(ERR_NOMEM, "Fail to create sub writer hb timer.");

		goto FAIL_SUB_HB_TIMER;
	}

	ptcp->p2p_writer_hb_td = mvbs_timer_create(ptcp, ptcp_dpde_p2p_writer_hb_timer, ptcp, 1);
	if (ptcp->p2p_writer_hb_td == TIMER_DESC_INVALID) {
		pr_err(ERR_NOMEM, "Fail to create p2p writer hb timer.");

		goto FAIL_P2P_HB_TIMER;
	}

	sec  = (int32_t)ptcp->attr->discovery.hb_policy.period_sec;
	nsec = ptcp->attr->discovery.hb_policy.period_msec * TIME_NSEC_PER_MSEC;

	(void)mvbs_timer_settime(ptcp, ptcp->pub_writer_hb_td, MVBS_TIMER_RELTIME, sec, nsec);
	(void)mvbs_timer_settime(ptcp, ptcp->sub_writer_hb_td, MVBS_TIMER_RELTIME, sec, nsec);
	(void)mvbs_timer_settime(ptcp, ptcp->p2p_writer_hb_td, MVBS_TIMER_RELTIME, sec, nsec);

	(void)ptcp_wlp_init(ptcp);
	(void)ptcp_diag_init(ptcp);

	ptcp->dpde_inited = true;

	return 0;

FAIL_P2P_HB_TIMER:
	mvbs_timer_delete(ptcp, ptcp->sub_writer_hb_td);

FAIL_SUB_HB_TIMER:
	mvbs_timer_delete(ptcp, ptcp->pub_writer_hb_td);

FAIL_PUB_HB_TIMER:
	mvbs_timer_delete(ptcp, ptcp->pdp_announce_td);

	return -ERR_NOMEM;
}

int32_t ptcp_dpde_discovery_start(struct participant *ptcp)
{
	if ((ptcp == NULL) || (ptcp->pdp_announce_td == TIMER_DESC_INVALID)) {
		pr_err(ERR_INVALID, "Invalid parameter.");
		return -ERR_INVALID;
	}

	if (ptcp->attr->discovery.edp_type != DYNAMIC_EDP) {
		return -ERR_INVALID;
	}

	if (!ptcp->dpde_inited) {
		return -ERR_FAULT;
	}

	ptcp_spdp_announce_online(ptcp, NULL, NULL);

	void discovery_package_template_init(struct participant *ptcp);

	discovery_package_template_init(ptcp);

	(void)mvbs_timer_restart(ptcp, ptcp->pdp_announce_td);

	(void)mvbs_timer_restart(ptcp, ptcp->pub_writer_hb_td);
	(void)mvbs_timer_restart(ptcp, ptcp->sub_writer_hb_td);
	(void)mvbs_timer_restart(ptcp, ptcp->p2p_writer_hb_td);

	ptcp->dpde_started = true;

	return 0;
}

int32_t ptcp_dpde_discovery_stop(struct participant *ptcp)
{
	if ((ptcp == NULL) || (ptcp->pdp_announce_td == TIMER_DESC_INVALID)) {
		pr_err(ERR_INVALID, "Invalid parameter.");
		return -ERR_INVALID;
	}

	if (ptcp->attr->discovery.edp_type != DYNAMIC_EDP) {
		return -ERR_INVALID;
	}

	if (!ptcp->dpde_started) {
		return -ERR_FAULT;
	}

	ptcp_spdp_announce_offline(ptcp);

	(void)mvbs_timer_stop(ptcp, ptcp->pdp_announce_td);

	return 0;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
