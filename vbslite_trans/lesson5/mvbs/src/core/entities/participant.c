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
#include <mvbs/utils/mm.h>
#include <mvbs/utils/timer.h>
#include <mvbs/utils/rand.h>
#include <mvbs/utils/log.h>
#include <mvbs/utils/time.h>
#include <mvbs/rtps/locator.h>
#include <mvbs/adapter/adapter.h>
#include <mvbs/core/netio/socket.h>
#include <discovery/dpse.h>
#include <discovery/sedp_agent.h>
#include <messages/message_receiver.h>

#if PARTICIPANT_VERBOSE && RTPS_GLOBAL_VERBOSE
#undef MVBSLOG_LEVEL
#define MVBSLOG_LEVEL MVBSLOG_VERB
#endif

struct reader *ptcp_get_reader_with_eid(participant_t *ptcp,
					rtps_entity_id_t reader_eid)
{
	uint32_t key;
	struct reader *r;

	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "ptcp is NULL.");
		return NULL;
	}

	key = rtps_entity_id_get_key(reader_eid);

	r = ptcp_get_reader_by_index(ptcp, key - 1);

	return r;
}

struct reader *ptcp_get_reader_with_wproxy(participant_t *ptcp,
				const struct participant_proxy *ptcp_proxy,
				struct rtps_entity_id writer_eid)
{
	struct reader		*r = NULL;
	struct writer_proxy	*proxy = NULL;

	if ((ptcp == NULL) || (ptcp_proxy == NULL)) {
		pr_err(ERR_INVALID, "ptcp or ptcp_proxy is NULL.");
		return NULL;
	}

	foreach_ptcp_reader(ptcp, r) {
		foreach_reader_proxy(r, proxy) {
			if (proxy->ptcp_proxy != ptcp_proxy) {
				continue;
			}

			if (rtps_entity_id_equal(&proxy->eid, &writer_eid)) {
				return r;
			}
		}
	}

	return NULL;
}

struct reader *ptcp_get_reader_with_topic(const participant_t *ptcp,
					  const char *topicname)
{
	struct reader *r = NULL;

	/* topicname[0] == '\0' is better then strlen(topicname) == 0 */
	if ((ptcp == NULL) || (topicname == NULL) || (topicname[0] == '\0')) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return NULL;
	}

	foreach_ptcp_reader(ptcp, r) {
		if (reader_topicname_equal(r, topicname) == 0) {
			return r;
		}
	}

	return NULL;
}

struct reader *ptcp_get_reader_with_type(struct participant *ptcp,
				           const char *type_name)
{
	struct reader *r = NULL;

	/* type_name[0] == '\0' is better then strlen(type_name) == 0 */
	if ((ptcp == NULL) || (type_name == NULL) || (type_name[0] == '\0')) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return NULL;
	}

	foreach_ptcp_reader(ptcp, r) {
		if (reader_typename_equal(r, type_name) == 0) {
			return r;
		}
	}

	return NULL;
}

struct reader *ptcp_get_reader_with_key(struct participant *ptcp,
					const char *key)
{
	struct reader *r = NULL;

	/* key[0] == '\0' is better then strlen(key) == 0 */
	if ((ptcp == NULL) || (key == NULL) || (key[0] == '\0')) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return NULL;
	}

	foreach_ptcp_reader(ptcp, r) {
		/* Filter out the builtin endpoint and readers without key */
		if (reader_key_equal(r, key) == 0) {
			return r;
		}
	}

	return NULL;
}

struct writer *ptcp_get_writer_with_eid(struct participant *ptcp,
					struct rtps_entity_id writer_eid)
{
	uint32_t key;
	struct writer *w;

	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "ptcp is NULL.");
		return NULL;
	}

	key = rtps_entity_id_get_key(writer_eid);

	w = ptcp_get_writer_by_index(ptcp, key - 1);

	return w;
}

struct writer *ptcp_get_writer_with_rproxy(struct participant *ptcp,
				const struct participant_proxy *ptcp_proxy,
				struct rtps_entity_id writer_eid)
{
	struct writer		*w = NULL;
	struct reader_proxy	*rproxy = NULL;

	if ((ptcp == NULL) || (ptcp_proxy == NULL)) {
		pr_err(ERR_INVALID, "ptcp or ptcp_proxy is NULL.");
		return NULL;
	}

	foreach_ptcp_writer(ptcp, w) {
		foreach_writer_proxy(w, rproxy) {
			if (rproxy->ptcp_proxy != ptcp_proxy) {
				continue ;
			}

			if (rtps_entity_id_equal(&rproxy->eid, &writer_eid)) {
				return w;
			}
		}
	}

	return NULL;
}

struct writer *ptcp_get_writer_with_topic(const struct participant *ptcp,
					  const char *topicname)
{
	struct writer *w = NULL;

	/* topicname[0] == '\0' is better then strlen(topicname) == 0 */
	if ((ptcp == NULL) || (topicname == NULL) || (topicname[0] == '\0')) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return NULL;
	}

	foreach_ptcp_writer(ptcp, w) {
		if (writer_topicname_cmp(w, topicname) == 0) {
			return w;
		}
	}

	return NULL;
}

struct writer *ptcp_get_writer_with_type(struct participant *ptcp,
					 const char *type_name)
{
	struct writer *w = NULL;

	/* topicname[0] == '\0' is better then strlen(topicname) == 0 */
	if ((ptcp == NULL) || (type_name == NULL) || (type_name[0] == '\0')) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return NULL;
	}

	foreach_ptcp_writer(ptcp, w) {
		if (writer_typename_cmp(w, type_name) == 0) {
			return w;
		}
	}

	return NULL;
}

struct writer *ptcp_get_writer_with_key(struct participant *ptcp,
					const char *key)
{
	struct writer *w = NULL;

	/* key[0] == '\0' is better then strlen(key) == 0 */
	if ((ptcp == NULL) || (key == NULL) || (key[0] == '\0')) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return NULL;
	}

	foreach_ptcp_writer(ptcp, w) {
		/* Filter out the builtin endpoint and writers without key */
		if (writer_key_cmp(w, key) == 0) {
			return w;
		}
	}

	return NULL;
}

struct reader *ptcp_get_matching_reader(participant_t *ptcp,
					const endpoint_info_t *info)
{
	struct reader *r;

	if ((ptcp == NULL) || (info == NULL)) {
		pr_err(ERR_INVALID, "ptcp or info is NULL.");
		return NULL;
	}

	foreach_ptcp_reader(ptcp, r) {
		if (reader_match_ep_info(r, info)) {
			return r;
		}
	}

	return NULL;
}

struct writer *ptcp_get_matching_writer(participant_t *ptcp,
					const endpoint_info_t *info)
{
	struct writer *w;

	if ((ptcp == NULL) || (info == NULL)) {
		return NULL;
	}

	foreach_ptcp_writer(ptcp, w) {
		if (writer_match_ep_info(w, info)) {
			return w;
		}
	}

	return NULL;
}

const locator_t *ptcp_get_builtin_multicast(participant_t *ptcp)
{
	/* FIXME: This locator info should be provided by transport */
	static locator_t loc = {
		.kind = (uint16_t)LOCATOR_KIND_INVALID,
	};

	if (loc.kind != (uint16_t)LOCATOR_KIND_INVALID) {
		return &loc;
	}

	locator_init_meta_multicast(&loc, ptcp->attr->domain_id);
        if (ptcp->attr->trans_info.ipc_j6m != NULL) {
		loc.kind = (uint16_t)LOCATOR_KIND_IPC;
        }

	return &loc;
}

const endpoint_attr_t *ptcp_find_static_remote_reader(participant_t *ptcp,
						     int16_t user_id)
{
	const endpoint_attr_t *attr;

	if (ptcp == NULL) {
		return NULL;
	}

	for (uint8_t i = 0; i < ptcp->attr->static_reader_num; i++) {
		attr = &ptcp->attr->static_reader_attrs[i];

		if (user_id == attr->user_defined_id) {
			return attr;
		}
	}

	return NULL;
}

const endpoint_attr_t *ptcp_find_static_remote_writer(participant_t *ptcp,
						     int16_t user_id)
{
	const endpoint_attr_t *attr;

	if (ptcp == NULL) {
		return NULL;
	}

	for (uint8_t i = 0; i < ptcp->attr->static_writer_num; i++) {
		attr = &ptcp->attr->static_writer_attrs[i];

		if (user_id == attr->user_defined_id) {
			return attr;
		}
	}

	return NULL;
}

uint8_t ptcp_get_max_user_readers(const struct participant *ptcp)
{
	return ptcp->attr->reader_num;
}

uint8_t ptcp_get_max_user_writers(const struct participant *ptcp)
{
	return ptcp->attr->writer_num;
}

participant_proxy_t *ptcp_get_proxy_with_name(participant_t *ptcp,
						  char *ptcp_name)
{
	struct participant_proxy *ptcp_proxy = NULL;

	if ((ptcp == NULL) || (ptcp_name == NULL)) {
		return NULL;
	}

	foreach_ptcp_proxy(ptcp, ptcp_proxy) {
		if (mvbs_strcmp(ptcp_proxy->ptcp_name, ptcp_name) == 0) {
			return ptcp_proxy;
		}
	}

	return NULL;
}

participant_proxy_t *ptcp_get_proxy_with_guid_prefix(participant_t *ptcp,
					struct rtps_guid_prefix *prefix)
{
	struct participant_proxy *ptcp_proxy = NULL;

	if ((ptcp == NULL) || (prefix == NULL)) {
		return NULL;
	}

	foreach_ptcp_proxy(ptcp, ptcp_proxy) {
		if (rtps_guid_prefix_equal(&ptcp_proxy->guid.prefix, prefix)) {
			return ptcp_proxy;
		}
	}

	return NULL;
}

const uint8_t *ptcp_locator_udp_ipaddr(participant_t *ptcp, uint32_t index)
{
	if (ptcp == NULL) {
		return NULL;
	}

	if (ptcp->attr->trans_info.udp == NULL) {
		return NULL;
	}

	if (index < ptcp->attr->trans_info.udp->info_cnt) {
		return ptcp->attr->trans_info.udp->info[index].addr;
	}

	return NULL;
}

bool ptcp_detect_preferred_proxy(participant_t *ptcp,
				 participant_proxy_t *proxy)
{
	const char *preferred_item;
	size_t i = 0;

	for (i = 0; i < ptcp->attr->preferred_list_num; i++) {
		preferred_item = ptcp->attr->preferred_list[i];
		if (mvbs_strcmp(proxy->ptcp_name, preferred_item) == 0) {
			return true;
		}
	}

	return false;
}

static bool ptcp_proxy_deactivate(participant_t *ptcp,
				  participant_proxy_t *ptcp_proxy,
				  bool force)
{
	struct reader *r;
	struct writer *w;

	pr_debug("ptcp proxy name: %s, has_endpoints: %d",
			ptcp_proxy->ptcp_name, ptcp_proxy->has_endpoints);

	/* Cancel this comments when buildin ep removed from pool */
	if (ptcp_proxy->has_endpoints != 0) {
		if (!force) {
			return false;
		}
	}

	pr_debug("Remove all reader proxy from ptcp_proxy [%s]",
					ptcp_proxy->ptcp_name);
	foreach_ptcp_writer(ptcp, w) {
		pr_debug("Scan reader proxy of writer [%s]",
					writer_get_topicname(w));
		writer_remove_proxies_with_ptcp(w, ptcp_proxy);

	}

	pr_debug("Remove all writer proxy from ptcp_proxy [%s]",
					ptcp_proxy->ptcp_name);
	foreach_ptcp_reader(ptcp, r) {
		pr_debug("Scan writer proxy of reader [%s]",
					reader_get_topicname(r));
		reader_remove_proxies_with_ptcp(r, ptcp_proxy);
	}

	ptcp_proxy->has_endpoints = 0;

	if (ptcp_proxy->liveliness_td != TIMER_DESC_INVALID) {
		mvbs_timer_delete(ptcp, ptcp_proxy->liveliness_td);
	}

	return true;
}

static participant_proxy_t *ptcp_proxy_alloc(participant_t *ptcp)
{
	void *proxy;

	proxy = mem_pool_alloc(&ptcp->proxies);

	return (participant_proxy_t *)proxy;
}

participant_proxy_t *ptcp_proxy_create(participant_t *ptcp, bool force)
{
	participant_proxy_t *proxy;

	proxy = ptcp_proxy_alloc(ptcp);
	if (proxy != NULL) {
		return proxy;
	}

	if (!force) {
		return NULL;
	}

	foreach_ptcp_proxy(ptcp, proxy) {
		if (proxy->preferred != 0U) {
			continue;
		}

		if (ptcp_proxy_deactivate(ptcp, proxy, false)) {
			return proxy;
		}
	}

	foreach_ptcp_proxy(ptcp, proxy) {
		if (proxy->preferred != 0U) {
			continue;
		}

		if (ptcp_proxy_deactivate(ptcp, proxy, true)) {
			return proxy;
		}
	}

	return NULL;
}

void ptcp_proxy_destroy(participant_proxy_t *proxy)
{
	participant_t *ptcp;

	if (proxy == NULL) {
		return ;
	}

	ptcp = ptcp_proxy_get_ptcp(proxy);

	if (ptcp_proxy_deactivate(ptcp, proxy, true)) {
		pr_info("ptcp proxy destroy: %s", proxy->ptcp_name);

		ptcp_proxy_free(proxy);
	}

	ptcp_proxy_on_change(proxy, false);
}

static void ptcp_proxy_liveliness_lost(void *arg)
{
	participant_proxy_t *proxy = (participant_proxy_t *)arg;

	pr_info("ptcp proxy lost liveliness: %s", proxy->ptcp_name);

	ptcp_proxy_destroy(proxy);
}

bool ptcp_proxy_liveliness_enable(participant_proxy_t *proxy)
{
	struct participant *ptcp;
	int32_t ret = 0;

	if (proxy == NULL) {
		return false;
	}

	/* overflow */
	if (duration_is_infinite(&proxy->lease_duration)) {
		pr_debug("ptcp proxy liveliness disabled: %s",
						proxy->ptcp_name);

		return true;
	}

	ptcp = ptcp_proxy_get_ptcp(proxy);

	proxy->liveliness_td = mvbs_timer_create(ptcp,
						ptcp_proxy_liveliness_lost,
						proxy, 0);
	if (proxy->liveliness_td == TIMER_DESC_INVALID) {
		pr_err(ERR_NOMEM, "Fail to create timer for ptcp liveliness: %s",
						proxy->ptcp_name);

		return false;
	}

	ret = mvbs_timer_start(ptcp, proxy->liveliness_td, MVBS_TIMER_RELTIME,
			     proxy->lease_duration.seconds,
			     proxy->lease_duration.nanosec);
	if (ret < 0) {
		pr_err(ret, "Fail to start timer for ptcp [%s] liveliness.",
						proxy->ptcp_name);

		mvbs_timer_delete(ptcp, proxy->liveliness_td);

		return false;
	}

	pr_debug("ptcp proxy liveliness started: %s", proxy->ptcp_name);

	return true;
}

void ptcp_proxy_liveliness_reset(participant_proxy_t *proxy)
{
	struct participant *ptcp;
	int32_t ret;

	if (proxy == NULL) {
		return ;
	}

	if (proxy->liveliness_td == TIMER_DESC_INVALID) {
		pr_debug("ptcp liveliness disabled:%s", proxy->ptcp_name);
		return ;
	}

	ptcp = ptcp_proxy_get_ptcp(proxy);

	ret = mvbs_timer_update_timeout(ptcp, proxy->liveliness_td,
				      MVBS_TIMER_RELTIME,
				      proxy->lease_duration.seconds,
				      proxy->lease_duration.nanosec);
	if (ret == 0) {
		return ;
	}

	pr_err(ret, "Fail to restart ptcp liveliness timer: %s",
						proxy->ptcp_name);
}

static bool ptcp_delete_reader(struct participant *ptcp, struct reader *r)
{
	bool ret = true;

	if ((ptcp == NULL) || (r == NULL)) {
		return false;
	}

	if (ptcp->attr->discovery.edp_type == DYNAMIC_EDP) {
		ret = sedp_delete_reader(ptcp, r);
	} else {
		static_delete_reader(ptcp, r);
	}

	return ret;
}

bool ptcp_remove_reader(struct participant *ptcp, struct reader *r)
{
	if ((ptcp == NULL) || (r == NULL)) {
		return false;
	}

	if (!ptcp_delete_reader(ptcp, r)) {
		return false;
	}

	reader_deinit(r);

	return true;
}

static void ptcp_destroy_all_readers(participant_t *ptcp)
{
	struct reader *r;

	/* remove all readers */
	foreach_ptcp_reader(ptcp, r) {
		reader_deinit(r);
	}
}

static bool ptcp_delete_writer(participant_t *ptcp, struct writer *w)
{
	bool ret = true;

	if ((ptcp == NULL) || (w == NULL)) {
		return false;
	}

	if (ptcp->attr->discovery.edp_type == DYNAMIC_EDP) {
		ret = sedp_delete_writer(ptcp, w);
	} else {
		static_delete_writer(ptcp, w);
	}

	return ret;
}

bool ptcp_remove_writer(struct participant *ptcp, struct writer *w)
{
	if ((ptcp == NULL) || (w == NULL)) {
		return false;
	}

	if (!ptcp_delete_writer(ptcp, w)) {
		return false;
	}

	writer_deinit(w);

	ptcp_writer_free(w);

	return true;
}

static void ptcp_destroy_all_writers(participant_t *ptcp)
{
	struct writer *w;

	/* remove all writers */
	foreach_ptcp_writer(ptcp, w) {
		writer_deinit(w);

		ptcp_writer_free(w);
	}
}

static participant_proxy_t *ptcp_proxy_create_local_proxy(participant_t *ptcp)
{
	participant_proxy_t	*ptcp_proxy;
	locator_t		*meta_uc_loc;
	locator_t		*user_uc_loc;

	if (ptcp == NULL) {
		return NULL;
	}

	ptcp_proxy = ptcp_proxy_create(ptcp, true);
	if (ptcp_proxy == NULL) {
		pr_err(ERR_NOMEM, "Failed to add new participant as resource limit");
		return NULL;
	}

	meta_uc_loc = ptcp_proxy_get_meta_uc_loc(ptcp_proxy);
	user_uc_loc = ptcp_proxy_get_user_uc_loc(ptcp_proxy);

	/* FIXME:
	 * meta_uc_loc and dfl_uc_loc maybe doesn't make sense for local
	 * entity.
	 */
	ptcp_proxy->dfl_mc_loc.kind     = (uint16_t)LOCATOR_KIND_LOCAL;
	ptcp_proxy->meta_mc_loc.kind    = (uint16_t)LOCATOR_KIND_LOCAL;
	meta_uc_loc->kind		= (uint16_t)LOCATOR_KIND_LOCAL;
	user_uc_loc->kind		= (uint16_t)LOCATOR_KIND_LOCAL;

	ptcp_proxy->dfl_uc_selector	= 0;

	ptcp_proxy->guid.prefix		= ptcp->guid_prefix;

	ptcp_proxy->lease_duration	= RTPS_TIME_INFINITE;
	ptcp_proxy->liveliness_td	= TIMER_DESC_INVALID;

	ptcp_proxy->ptcp		= ptcp;

	ptcp_proxy->session_id		= ptcp->session_id;

#if 1
	ptcp_proxy->avail_builtin_eps   = 0;
#else
	ptcp_proxy->avail_builtin_eps   = DISC_BIE_PARTICIPANT_ANNOUNCER
					| DISC_BIE_PARTICIPANT_DETECTOR
					| DISC_BIE_PUBLICATION_ANNOUNCER
					| DISC_BIE_PUBLICATION_DETECTOR
					| DISC_BIE_SUBSCRIPTION_ANNOUNCER
					| DISC_BIE_SUBSCRIPTION_DETECTOR
					| BIE_PARTICIPANT_MESSAGE_DATA_READER
					| BIE_PARTICIPANT_MESSAGE_DATA_WRITER;
#endif

	(void)mvbs_strcpy(ptcp_proxy->ptcp_name, "MVBS::LOCAL");

	return ptcp_proxy;
}

static struct reader *ptcp_get_local_matching_reader(participant_t *ptcp,
							struct writer *w)
{
	struct reader *r;

	if ((ptcp == NULL) || (w == NULL)) {
		return NULL;
	}

	const endpoint_attr_t *wattr = &w->attr->ep_attr;

	foreach_ptcp_reader(ptcp, r) {
		if (ep_attr_match(wattr, &r->attr->ep_attr)) {
			return r;
		}
	}

	return NULL;
}

static void ptcp_match_local_endpoint(participant_t *ptcp,
				      participant_proxy_t *ptcp_proxy)
{
	struct reader *r;
	struct writer *w;

	if (ptcp->attr->discovery.edp_type == DYNAMIC_EDP) {
		foreach_ptcp_writer(ptcp, w)
		{
			r = ptcp_get_local_matching_reader(ptcp, w);
			if (r != NULL) {
				sedp_do_local_match(ptcp_proxy, w, r);
			}
		}

		return ;
	}

	if (ptcp->attr->discovery.edp_type == STATIC_EDP) {
		ptcp_dpse_local_ep_match(ptcp, ptcp_proxy);

		return ;
	}
}

void ptcp_local_comm_enable(struct participant *ptcp)
{
	participant_proxy_t *ptcp_proxy = NULL;
	bool ret;

	if (!ptcp_local_transport_enabled(ptcp)) {
		pr_info("Participant [%s] hasn't local communication.",
							ptcp->attr->name);
		return ;
	}

	ptcp_proxy = ptcp_proxy_create_local_proxy(ptcp);
	if (ptcp_proxy == NULL) {
		pr_info("Fail to create local ptcp proxy for Participant [%s] .",
							ptcp->attr->name);
		return ;
	}

	ret = ptcp_proxy_liveliness_enable(ptcp_proxy);
	if (!ret) {
		pr_info("Fail to enable local ptcp proxy [%s] liveliness.",
							ptcp_proxy->ptcp_name);
		ptcp_proxy_free(ptcp_proxy);

		return ;
	}

	ptcp_match_local_endpoint(ptcp, ptcp_proxy);

	pr_info("Participant [%s] local communication has been enabled.",
							ptcp_proxy->ptcp_name);

	return ;
}

int32_t ptcp_enable(struct participant *ptcp)
{
	int32_t ret;

	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "Participant info null.");
		return -ERR_INVALID;
	}

	ptcp->session_id = mvbs_get_session_id();

	ptcp_local_comm_enable(ptcp);

	mvbs_get_time(&ptcp->start_time.seconds, &ptcp->start_time.nanosec);

	ret = ptcp_discovery_start(ptcp);

	ptcp->started = true;

	return ret;
}

int32_t ptcp_recv_handler(struct participant *ptcp, uint32_t recv_max_pkg)
{
	if ((ptcp != NULL) && (ptcp->ptransport != NULL)) {
		ptcp->ptransport->recv(ptcp->ptransport, recv_max_pkg);
	}

	return mvbs_udp_rx_buffer_pkg_cnt(ptcp);
}

int32_t ptcp_local_recv_handler(struct participant *ptcp, uint32_t recv_max_pkg)
{
	extern void local_trans_recv_handle(struct transport *this,
					    uint32_t recv_max_pkg);

	if ((ptcp != NULL) && (ptcp->ptransport != NULL)) {
		local_trans_recv_handle(ptcp->ptransport, recv_max_pkg);
	}

	return mvbs_local_rx_buffer_pkg_count(ptcp);
}

int32_t ptcp_timer_handler(struct participant *ptcp)
{
	mvbs_udp_rx_buffer_max_usage_rate_update(ptcp);
	mvbs_local_rx_buffer_max_usage_rate_update(ptcp);

	mvbs_timer_tick(ptcp);

	return 0;
}

struct mvbs_cdr *ptcp_get_tx_buffer(const participant_t *ptcp)
{
#if 0
	if (ptcp->ptransport == NULL) {
		return NULL;
	}

	if (ptcp->ptransport->get_tx_buffer == NULL) {
		return NULL;
	}
#endif

	return ptcp->ptransport->get_tx_buffer(ptcp->ptransport);
}

int32_t ptcp_send_buffer_to(const participant_t *ptcp,
			    const void *buf, size_t length,
			    locator_t *loc, bool link_bakup)
{
	int32_t ret = 0;

	if ((ptcp == NULL) || (buf == NULL) || (length <= (size_t)0) ||
	    (loc == NULL)) {
		return -ERR_INVALID;
	}

	if (!link_bakup) {
		locator_dump(loc);

		return ptcp->ptransport->sendto(ptcp->ptransport, loc, buf, length);
	}

	for (uint8_t idx = 0; idx < ptcp_local_locator_count(ptcp); idx++) {
		if (loc->kind == (uint16_t)LOCATOR_KIND_INVALID) {
			break;
		}

		locator_dump(loc);

		ret = ptcp->ptransport->sendto(ptcp->ptransport, loc,
							buf, length);
		loc = ptcp_proxy_get_next_uc_loc(loc);
	}

	return ret;
}

static void ptcp_process_new_message(participant_t *ptcp,
				     const uint8_t *pdata, uint16_t size)
{
	(void)msg_recv_process(ptcp, pdata, size, true);
}

static void ptcp_process_loacl_new_message(participant_t *ptcp,
					   const uint8_t *pdata, uint16_t size)
{
	(void)msg_recv_process(ptcp, pdata, size, false);
}

static void ptcp_recv_cb(struct participant *ptcp, const uint8_t *buf,
						   size_t len, locator_t *loc)
{
	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "Participant info null.");
		return;
	}

	if ((buf == NULL) || (len <= (size_t)0) || (loc == NULL)) {
		pr_err(ERR_INVALID, "packet invalid.");
		return;
	}

	/* Case1: Handle packages from communication between local endpoints. */
	if (loc->kind == (uint16_t)LOCATOR_KIND_LOCAL) {
		ptcp_process_loacl_new_message(ptcp, buf, (uint16_t)len);

		return;
	}

	/* Case2: Handle packages from communication between IPC endpoints. */
	if (loc->kind == (uint16_t)LOCATOR_KIND_IPC) {
		ptcp_process_new_message(ptcp, buf, (uint16_t)len);

		return;
	}

	/* Case3: Handle packages from communication between local endpoints
         * with remote endpoints.
         */
	if (locator_is_meta_multicast_port(loc, ptcp->attr->domain_id)) {
		ptcp_process_new_message(ptcp, buf, (uint16_t)len);
	} else if (locator_is_user_multicast_port(loc, ptcp->attr->domain_id)) {
		/* FIXME:
		 * Currently, it's not support that receive user data from
		 * multicast.
		 */
	} else {
		if (rtps_port_check_ptcp_ids(loc->port, ptcp->attr->domain_id,
					     ptcp->id)) {
			ptcp_process_new_message(ptcp, buf, (uint16_t)len);
		} else {
			pr_verb("Domain: Got message to port %u: "
				"no matching participant",
				loc->port);
		}
	}
}

static struct rtps_guid_prefix ptcp_guid_prefix_generate(participant_t *ptcp)
{
	struct rtps_guid_prefix		prefix;
	int8_t id;

	id = (int8_t)ptcp->id;

	uint32_t inst_id = (uint32_t)id;

	for (uint8_t i = HOST_ID_OFF; i < APP_ID_OFF; i++) {
		prefix.id[i] = ptcp->attr->trans_info.udp->info[0].addr[i];
	}

	for (uint8_t i = APP_ID_OFF; i < INSTANCE_ID_OFF; i++) {
		prefix.id[i] = (uint8_t)(mvbs_rand() & 0xFF);
	}

	mvbs_memcpy((void *)&prefix.id[INSTANCE_ID_OFF], (void *)&inst_id, 4U);

	pr_info("ptcp guid_prefix: " GUID_PREFIX_FMT,
				     GUID_PREFIX_PARTS(prefix.id));

	return prefix;
}

int32_t ptcp_init(participant_t *ptcp, const participant_attr_t *attr)
{
	int32_t	ret;

	ptcp->pdp_announce_td   = TIMER_DESC_INVALID;
	ptcp->attr		= attr;
	ptcp->dpde_inited	= false;
	ptcp->dpse_inited	= false;
	ptcp->dpde_started	= false;
	ptcp->dpse_started	= false;

	ptcp->announce_count	= 0;
	ptcp->boost		= true;

	if (mvbs_netio_init() != 0) {
		return -ERR_AGAIN;
	}

	mvbs_mm_init();

	ret = mvbs_timer_init(ptcp, MVBS_SCHED_PERIOD_MS * TIME_USEC_PER_MSEC);
	if (ret != 0) {
		return -ERR_INVALID;
	}

	ret = mem_pool_reset(&ptcp->proxies);
	if (ret != 0) {
		pr_err(ret, "Fail to init memory pool of remote ptcp.");

		goto ERROR_INIT_TIMER;
	}

#if 0
	ret = mem_pool_init(&ptcp->writers, (uint32_t)sizeof(struct writer),
					    (uint32_t)attr->max_writers);
	if (ret != 0) {
		pr_err(ret, "Fail to init memory pool of writers.");
		goto ERROR_WRITERS_MP;
	}

	ret = mem_pool_init(&ptcp->readers, (uint32_t)sizeof(struct reader),
					    (uint32_t)attr->max_readers);
	if (ret != 0) {
		pr_err(ret, "Fail to init memory pool of readers.");
		goto ERROR_READERS_MP;
	}
#endif

	ptcp->id	 = 0;

	ptcp->ptransport = transport_create(ptcp, &attr->trans_info,
					    ptcp_recv_cb);
	if (ptcp->ptransport == NULL) {
		ret = ERR_NOMEM;

		pr_err(ERR_NOMEM, "Fail to initialized transport");
		goto ERROR_TRANSPORT;
	}

	ptcp->guid_prefix = ptcp_guid_prefix_generate(ptcp);

	ret = ptcp_discovery_init(ptcp);
	if (ret < 0) {
		pr_err(ret, "Fail to init simple dynamic protocol.");
		goto ERROR_DISCOVERY;
	}

	ptcp->inited = true;

	return 0;

ERROR_DISCOVERY:
	ptcp->ptransport->destroy(ptcp->ptransport);

ERROR_TRANSPORT:

#if 0
	mem_pool_deinit(&ptcp->readers);

ERROR_READERS_MP:
	mem_pool_deinit(&ptcp->writers);

ERROR_WRITERS_MP:
	mem_pool_deinit(&ptcp->remote_locators);

ERROR_REMOTE_LOCATORS_MP:
	mem_pool_deinit(&ptcp->proxies);
#endif

ERROR_INIT_TIMER:
	mvbs_timer_deinit(ptcp);

	return ret;
}

void ptcp_deinit(participant_t *ptcp)
{
	struct participant_proxy *ptcp_proxy;

	if (ptcp == NULL) {
		return;
	}

	foreach_ptcp_proxy(ptcp, ptcp_proxy) {
		ptcp_proxy_destroy(ptcp_proxy);
	}

	if (ptcp->ptransport != NULL) {
		ptcp->ptransport->destroy(ptcp->ptransport);
	}

	mvbs_timer_deinit(ptcp);
}

struct participant *ptcp_create(const participant_attr_t *attr)
{
	participant_t *ptcp;
	int32_t ret;

	if (attr == NULL) {
		return NULL;
	}

	ptcp = mvbs_malloc(sizeof(struct participant), 0);
	if (ptcp == NULL) {
		pr_err(ERR_NOMEM, "Fail to alloc participant object.");
		return NULL;
	}

	ret = ptcp_init(ptcp, attr);
	if (ret < 0) {
		pr_err(ret, "Fail to initialized ptcp(%d)", ret);

		mvbs_free(ptcp);
		return NULL;
	}

	return ptcp;
}

bool ptcp_destroy(struct participant *ptcp)
{
	if (ptcp == NULL) {
		return false;
	}

	ptcp_discovery_stop(ptcp);

	ptcp_destroy_all_writers(ptcp);
	ptcp_destroy_all_readers(ptcp);

	ptcp_deinit(ptcp);

	mvbs_free(ptcp);

	return true;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
