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
#include <diag/recorder.h>
#include <mvbs/mvbs.h>
#include <mvbs/utils/time.h>
#include <mvbs/utils/timer.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/log.h>
#include <messages/message_factory.h>
#include <qos/e2e.h>

#if WRITER_VERBOSE || RTPS_GLOBAL_VERBOSE
#undef MVBSLOG_LEVEL
#define MVBSLOG_LEVEL MVBSLOG_VERB
#endif

const struct writer_listener *writer_listener_setup(struct writer *w,
					      const struct writer_listener *l)
{
	const struct writer_listener *temp = NULL;

	if (w != NULL) {
		temp		= w->listener;
		w->listener	= l;
	}

	return temp;
}

void writer_set_private(struct writer *w, void *priv_data)
{
	if (w == NULL) {
		return;
	}

	w->priv_data = priv_data;
}

void *writer_get_private(struct writer *w)
{
	if (w == NULL) {
		return NULL;
	}

	return w->priv_data;
}

const char *writer_get_topicname(struct writer *w)
{
	if ((w == NULL) || (w->attr == NULL)) {
		return NULL;
	}

	return w->attr->ep_attr.topic_name;
}

const char *writer_get_typename(struct writer *w)
{
	if (w == NULL) {
		return NULL;
	}

	return w->attr->type->name;
}

static inline uint16_t writer_get_payload_size(struct writer *w)
{
	struct mem_pool *cc_pool = writer_get_cache_change_pool(w);

	if (cc_pool == NULL) {
		return 0;
	}

	if (cc_pool->blk_size <= sizeof(struct writer_cache_change)) {
		pr_debug("The writer '%s' payload size invalid.",
						writer_get_topicname(w));
		return 0;
	}

	return cc_pool->blk_size - (uint16_t)sizeof(struct writer_cache_change);
}

int32_t writer_get_status(struct writer *w, struct mvbs_endpoint_stat *stats)
{
	if ((w == NULL) || (stats == NULL)) {
		return -ERR_INVALID;
	}

	stats->remotes_online		= writer_get_matched_count(w);
	stats->total_remotes_online	= writer_get_total_matched_count(w);
	stats->total_remotes_offline	= (stats->total_remotes_online - stats->remotes_online);

	stats->deadline_timeout		= writer_get_deadline_missed_count(w);

	stats->instances		= 0;

	stats->sample_committed		= writer_get_committed_sample(w);
	stats->sample_lost		= 0;
	stats->sample_rejected		= 0;

	return 0;
}

size_t writer_get_onlinepeers(struct writer *w,
			      struct mvbs_entity_info *peer, size_t n)
{
	participant_proxy_t	*ptcp_proxy;
	struct reader_proxy	*rproxy;
	size_t ret = 0;

	if (w == NULL) {
		return 0;
	}

	if ((peer == NULL) || (n == (size_t)0)) {
		return (size_t)(mem_pool_total_blk_cnt(&w->proxies) -
				mem_pool_free_blk_cnt(&w->proxies));
	}

	foreach_writer_proxy(w, rproxy) {
		if (ret >= n) {
			break;
		}

		reader_proxy_get_guid(rproxy, &peer[ret].guid);

		ptcp_proxy = rproxy->ptcp_proxy;
		if (ptcp_proxy != NULL) {
			peer[ret].remote_name = ptcp_proxy->ptcp_name;
		} else {
			peer[ret].remote_name = NULL;
		}

		ret++;
	}

	return ret;
}

static void writer_deadline_expired(void *arg)
{
	struct writer *w = (struct writer *)arg;
	struct writer_deadline_missed_status deadline_missed_status;

	if (w == NULL) {
		return;
	}

	pr_warn("Writer deadline missed!\n");

	writer_deadline_missed_count_increase(w);

	deadline_missed_status.total_count = writer_get_deadline_missed_count(w);

	writer_on_offered_deadline_missed(w, &deadline_missed_status);
}

static int32_t writer_deadline_init(struct writer *w)
{
	const endpoint_attr_t *writer_attrs;
	struct participant *ptcp;

	writer_attrs = &(w->attr->ep_attr);

	if (duration_is_infinite(&writer_attrs->deadline.duration)) {
		return 0;
	}

	ptcp = writer_get_ptcp(w);
	w->deadline_td = mvbs_timer_create(ptcp, writer_deadline_expired, w,
					   (uint8_t) false);
	if (w->deadline_td == TIMER_DESC_INVALID) {
		pr_err(ERR_NOMEM, "Writer deadline_timer init failed!\n");
		return -ERR_NOMEM;
	}

	return 0;
}

static void writer_deadline_restart(struct writer *w)
{
	/* deadline qos policy */
	struct participant *ptcp;

	if (w->deadline_td == TIMER_DESC_INVALID) {
		return ;
	}

	ptcp = writer_get_ptcp(w);

	/* Topic no key, just restart the deadline timer */
	(void)mvbs_timer_update_timeout(ptcp, w->deadline_td,
				MVBS_TIMER_RELTIME,
				w->attr->ep_attr.deadline.duration.seconds,
				w->attr->ep_attr.deadline.duration.nanosec);
}

static void writer_lifespan_expired(void *arg)
{
	struct writer *w = (struct writer *)arg;
	struct writer_cache_change *wcc;
	struct participant *ptcp;
	const duration_t *lifespan;
	uint64_t lifespan_ns;

	if (w == NULL) {
		pr_err(ERR_INVALID, "The parameter writer is invalid.");

		return ;
	}

	ptcp = writer_get_ptcp(w);

	lifespan = &(w->attr->ep_attr.lifespan.duration);
	lifespan_ns = ((uint64_t)lifespan->seconds
		    * (uint64_t)TIME_NSEC_PER_SEC)
		    + (uint64_t)lifespan->nanosec;

	wcc = writer_cache_get_oldest_cc(w);
	while (wcc != NULL) {
		uint64_t elapse;

		elapse = mvbs_calculate_time_interval_till_now(
			wcc->cc.ts.seconds, wcc->cc.ts.nanosec);

		if (elapse < lifespan_ns) {
			/*
			 *  Time out remain: time to next time lifespan timer
			 *  timeout
			 */
			uint64_t to_remain = lifespan_ns - elapse;
			uint64_t seconds = to_remain / TIME_NSEC_PER_SEC;
			(void)mvbs_timer_update_timeout(ptcp, w->lifespan_td,
						   MVBS_TIMER_RELTIME,
						   (int32_t)(seconds),
						   (uint32_t)(to_remain % TIME_NSEC_PER_SEC));

			return;
		}

		pr_info("sample to delete: sn: %d:%u, elapse: %lu\n",
			 wcc->cc.sn.high, wcc->cc.sn.low, elapse);

		/* the earliest change has expired */
		writer_cache_del_oldest_cc(w);

		wcc = writer_cache_get_oldest_cc(w);
	}

	(void)mvbs_timer_update_timeout(ptcp, w->lifespan_td, MVBS_TIMER_RELTIME,
                                      lifespan->seconds, lifespan->nanosec);
}

static int32_t writer_lifespan_init(struct writer *w)
{
	const endpoint_attr_t *writer_attrs;
	struct participant *ptcp;

	writer_attrs = &(w->attr->ep_attr);

	if (duration_is_infinite(&writer_attrs->lifespan.duration)) {
		return 0;
	}

	ptcp = writer_get_ptcp(w);

	w->lifespan_td = mvbs_timer_create(ptcp, writer_lifespan_expired, w,
					   (uint8_t) true);
	if (w->lifespan_td == TIMER_DESC_INVALID) {
		pr_err(ERR_NOMEM, "Writer lifespan_timer init failed!\n");
		return -ERR_NOMEM;
	}

	return mvbs_timer_start(ptcp, w->lifespan_td, MVBS_TIMER_RELTIME,
				writer_attrs->lifespan.duration.seconds,
				writer_attrs->lifespan.duration.nanosec);
}

static struct writer_cache_change *writer_add_cache(struct writer *w,
			instance_id id, const uint8_t *data, uint16_t size)
{
	struct writer_cache_change	*wcc = NULL;
	struct serialized_payload	ser_payload;

	bool ret;

	(void)id;
	(void)size;

	if (writer_cache_is_full(w)) {
		writer_cache_del_oldest_cc(w);
	}

	wcc = writer_cache_alloc_cc(w);
	if (wcc == NULL) {
		pr_err(ERR_NOMEM, "has no space in writer mempool of cachechange\n");
		return NULL;
	}

	ser_payload.data	= writer_cache_get_cc_payload(wcc);
	ser_payload.length	= writer_get_payload_size(w);

	ret = writer_data_serialize(w, (void *)data, &ser_payload);
	if (!ret) {
		writer_cache_free_cc(wcc);

		pr_err(ERR_MCDR, "Failed to serialize writer [%s] data",
						writer_get_typename(w));
		return NULL;
	}

	wcc->real_size = (uint16_t)ser_payload.recv_size;

	writer_cache_add_cc(w, wcc);

	/* deadline qos policy */
	writer_deadline_restart(w);

	writer_committed_sample_increase(w);

	wlp_writer_assert_liveliness(w, false);

	return wcc;
}

static locator_t *writer_get_dest_info(struct writer *w,
				     struct reader_proxy *rproxy,
				     struct rtps_entity_id *eid)
{
	if ((w == NULL) || (rproxy == NULL)) {
		return NULL;
	}

	if (w->attr->enforce_unicast) {
		if (eid != NULL) {
			*eid = rproxy->eid;
		}

		return ptcp_proxy_get_user_uc_loc(rproxy->ptcp_proxy);
	}

	if ((rproxy->flags.use_multicast != 0U) ||
	    (rproxy->flags.suppress_unicast == (uint8_t) false)) {
		if (eid != NULL) {
			if ((rproxy->flags.use_multicast != (uint8_t)0) &&
				(rproxy->flags.suppress_unicast != (uint8_t)0)) {
				*eid = ENTITYID_UNKNOWN;
			} else {
				*eid = rproxy->eid;
			}
		}

		/* Decide whether multicast or not */
		if (rproxy->flags.use_multicast != (uint8_t)0) {
			return ptcp_proxy_get_user_mc_loc(rproxy->ptcp_proxy);
		} else {
			return ptcp_proxy_get_user_uc_loc(rproxy->ptcp_proxy);
		}
	}

	return NULL;
}

static bool cdr_serialize_data_submessage(struct mvbs_cdr *cdr,
				     struct writer *w,
				     const struct rtps_entity_id *reader_id,
				     struct writer_cache_change *wcc)
{
	bool ret = true;
	struct rtps_entity_id writer_id;
	struct serialized_payload ser_payload = {0U, 0U, NULL};

	writer_id = writer_get_eid(w);
	/* INFO_TS submessage */
	ret = rtps_msg_add_submsg_timestamp(cdr, &wcc->cc.ts);
	if (!ret) {
		return ret;
	}

	/* INFO_E2E submessage */
	if (w->attr->ep_attr.e2e.e2e_protection) {
		ser_payload.data = writer_cache_get_cc_payload(wcc);
		ser_payload.recv_size = wcc->real_size;
		/* FIXME:
		 * e2e_count is equal to the value of last_used_sn minus 1.
		 * Ensure that when taking the last_used_sn value,
		 * the value needs to be greater than 0.
		 */

		ret = rtps_msg_add_submsg_e2e(cdr, &ser_payload, &writer_id, reader_id, &wcc->cc.sn);
		if (!ret) {
			return ret;
		}
	}

	/* DATA submessage */
	ret = rtps_msg_add_submsg_data(cdr, wcc, false, &writer_id, reader_id);
	if (!ret) {
		return ret;
	}

	return ret;
}

static int32_t writer_append_cc_to_cdr(struct writer *w,
				   const struct rtps_entity_id *reader_eid,
				   struct writer_cache_change *wcc,
				   struct mvbs_cdr *cdr)
{
	size_t buf_size_need = 0;
	bool ret = true;

	if (mcdr_buffer_has_error(cdr)) {
		pr_err(ERR_NOMEM, "Buffer in transport has error.");

		return -ERR_NOMEM;
	}

	/* INFO_TS + DATA header + DATA payload */
	uint16_t header_size = msg_get_submsg_time_raw_size() +
			       msg_get_submsg_data_raw_size();
	buf_size_need += (size_t)header_size;
	buf_size_need += (size_t)wcc->real_size;
	if (w->attr->ep_attr.e2e.e2e_protection) {
		buf_size_need += (size_t)24;
	}

	if (mcdr_buffer_remaining(cdr) < buf_size_need) {
		return -ERR_NOMEM;
	}

	/* Append  INFO_TS , DATA header , DATA payload */
	ret = cdr_serialize_data_submessage(cdr, w, reader_eid, wcc);
	if (!ret) {
		return -ERR_NOMEM;
	}

	return 0;
}

static void writer_send_history(struct writer *w, struct reader_proxy *rproxy)
{
	struct participant		*ptcp;
	struct mvbs_cdr			*cdr;
	struct writer_cache_change	*cc;
	struct rtps_sn			sn_to_send;
	struct rtps_entity_id		reader_eid;

	locator_t			*loc;
	int32_t				ret;

	loc = writer_get_dest_info(w, rproxy, &reader_eid);
	if (loc == NULL) {
		pr_err(ERR_FAULT, "Fail to get dest locator info.");
		return;
	}

	ptcp = writer_get_ptcp(w);

	/* send all samples in history */
	sn_to_send = writer_cache_get_min_sn(w);

	if (!rtps_sn_equal(&sn_to_send, &RTPS_SN_UNKNOWN)) {
		reader_proxy_update_lowmark(rproxy, &sn_to_send);
	}

	cdr = ptcp_get_tx_buffer(ptcp);
	mcdr_reset_buffer(cdr);
	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

	while (!rtps_sn_equal(&sn_to_send, &RTPS_SN_UNKNOWN)) {
		/* add reader proxy history */
		reader_proxy_add_change(rproxy, &sn_to_send);

		cc = writer_cache_get_cc(w, sn_to_send);

		ret = writer_append_cc_to_cdr(w, &reader_eid, cc, cdr);
		if (ret != 0) {
			(void)ptcp_send_buffer_to(ptcp,
					mcdr_get_buffer(cdr),
					mcdr_buffer_length(cdr), loc,
					w->attr->ep_attr.backup_enabled);

			mcdr_reset_buffer(cdr);
			(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);
			(void)writer_append_cc_to_cdr(w, &reader_eid, cc, cdr);
		}

		sn_to_send = writer_cache_get_next_sn(w, sn_to_send);
	}

	if (mcdr_buffer_length(cdr) > msg_get_header_raw_size()) {
		(void)ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
				    mcdr_buffer_length(cdr), loc,
				    w->attr->ep_attr.backup_enabled);
	}
}

static void writer_record_hook(struct writer *w, struct mvbs_cdr *cdr,
				struct writer_cache_change *wcc, locator_t *loc,
				uint32_t submessage_header_offset)
{
	struct participant *ptcp;
	int32_t ret;

	ptcp = writer_get_ptcp(w);

	ret = recorder_send_writer_record(ptcp, cdr, wcc, loc, w,
					  submessage_header_offset);
	if (ret != 0) {
		pr_err(ERR_INVALID,
		       "Fail to send writer[%s] reord (len: %lu) to monitor.",
		       writer_get_topicname(w), mcdr_get_buffer(cdr));
	}

	return;
}

static bool writer_send_rpts_data(struct writer *w, locator_t *dst_loc,
				const struct rtps_entity_id *reader_eid,
				struct writer_cache_change *wcc, bool mcast_loc)
{
	struct participant	*ptcp;
	struct mvbs_cdr		*cdr;
	bool    result;
	int32_t ret;

	ptcp = writer_get_ptcp(w);

	cdr = ptcp_get_tx_buffer(ptcp);

	mcdr_reset_buffer(cdr);

	result = rtps_msg_add_header(cdr, &ptcp->guid_prefix);
	if (result == false) {
		return false;
	}

	ret = writer_append_cc_to_cdr(w, reader_eid, wcc, cdr);
	if (ret != 0) {
		return false;
	}

	if (mcast_loc) {
		ret = ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
					  mcdr_buffer_length(cdr), dst_loc,
					  false);
	} else {
		ret = ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
					  mcdr_buffer_length(cdr), dst_loc,
					  w->attr->ep_attr.backup_enabled);
	}

	pr_debug("Writer [%s] SN:%ld TS:%d-%d -> " LOCATOR_FMT,
				string_or_null(writer_get_topicname(w)),
				rtps_sn_to_int64(&wcc->cc.sn),
				wcc->cc.ts.seconds, wcc->cc.ts.nanosec,
				LOCATOR_MEMBERS(dst_loc));

	if (ret < 0) {
		pr_err(ret, "Fail to transport send for writer [%s]",
				string_or_null(writer_get_topicname(w)));
	}

	return ret == 0;
}

static bool writer_send_ucast_data(struct writer *w,
				   struct reader_proxy *rproxy,
				   struct writer_cache_change *wcc)
{
	struct  locator *loc;

	if (((w == NULL) || (rproxy == NULL)) || (wcc == NULL)) {
		return false;
	}

	loc = ptcp_proxy_get_user_uc_loc(rproxy->ptcp_proxy);

	return writer_send_rpts_data(w, loc, &rproxy->eid, wcc, false);
}

static bool writer_send_mcast_data(struct writer *w,
				   struct reader_proxy *rproxy,
				   struct writer_cache_change *wcc)
{
	struct rtps_entity_id eid;
	locator_t	*loc;

	if ((w == NULL) || (rproxy == NULL) || (wcc == NULL)) {
		return false;
	}

	if ((rproxy->flags.use_multicast != 0U)
		|| (rproxy->flags.suppress_unicast == (uint8_t)false)) {

		/* Deceide whether multicast or not */
		if (rproxy->flags.use_multicast != (uint8_t)0) {
			loc = ptcp_proxy_get_user_mc_loc(rproxy->ptcp_proxy);

			if (rproxy->flags.suppress_unicast != (uint8_t)0) {
				eid = ENTITYID_UNKNOWN;
			} else {
				eid = rproxy->eid;
			}

			/* FIXME: Doesn't support link backup on multicast for
			 * user data sending.
			 */

			return writer_send_rpts_data(w, loc, &eid, wcc, true);
		} else {
			loc = ptcp_proxy_get_user_uc_loc(rproxy->ptcp_proxy);
			eid = rproxy->eid;

			return writer_send_rpts_data(w, loc, &eid, wcc, false);
		}
	}

	return true;
}

bool writer_send_data_to(struct writer *w, struct writer_cache_change *send,
			 struct reader_proxy *rproxy)
{
	if ((w == NULL) || (rproxy == NULL) || (send == NULL)) {
		return false;
	}

	if (!w->attr->enforce_unicast) {
		return writer_send_mcast_data(w, rproxy, send);
	} else {
		return writer_send_ucast_data(w, rproxy, send);
	}
}

static int32_t writer_set_wcc_statues(struct writer_cache_change *wcc,
				      int32_t proxies_cnt,
				      int32_t proxies_send_failed_cnt)
{
	int16_t	send_status = TRANS_CODE_ALL_SUCCESS_ALL_OUT;

	if (proxies_cnt == 0U) {
		send_status = TRANS_CODE_ALL_FAIL_PROXY_INVALID;
	} else {
		if (proxies_send_failed_cnt == 0U) {
			send_status = TRANS_CODE_ALL_SUCCESS_ALL_OUT;
		} else {
			if (proxies_cnt == proxies_send_failed_cnt) {
				send_status = TRANS_CODE_ALL_FAIL_OTHERS;
			} else {
				send_status = TRANS_CODE_PART_FAIL_PART_OUT;
			}
		}
	}

	(void)cache_change_update_trans_status(wcc, send_status);

	return (int32_t)send_status;
}

static bool writer_check_cdr_capacity_for_wcc(struct writer *w,
					      uint32_t cdr_remaining_size,
					      uint32_t wcc_real_size)
{
	uint16_t		header_size = 0U;
	size_t			buf_size_need = 0;

	header_size = msg_get_header_raw_size() +
		      msg_get_submsg_time_raw_size() +
		      msg_get_submsg_data_raw_size();

	buf_size_need += (size_t)header_size;
	buf_size_need += (size_t)wcc_real_size;

	if (writer_e2e_has_enabled(w)) {
		buf_size_need += (size_t)24;
	}

	if (cdr_remaining_size < buf_size_need) {
		pr_err(1, "Message payload too long");
		return false;
	}

	return true;
}

static bool writer_init_user_data_submsg(struct mvbs_cdr *cdr,
					 struct writer *w,
					 struct writer_cache_change *wcc,
					 struct mvbs_cdr *data_start_pos,
					 struct mvbs_cdr *e2e_start_pos)
{
	bool				cdr_ret = false;
	struct participant		*ptcp = writer_get_ptcp(w);
	struct rtps_entity_id		reader_id = { 0 };
	struct rtps_entity_id		writer_id = writer_get_eid(w);

	/* check length: RTPS Header + INFO_TS + DATA header + DATA payload */
	cdr_ret = writer_check_cdr_capacity_for_wcc(
		w, mcdr_buffer_remaining(cdr), wcc->real_size);
	if (!cdr_ret) {
		pr_err(1, "Message payload too long");
		return cdr_ret;
	}

	/* RTPS Header */
	cdr_ret = rtps_msg_add_header(cdr, &ptcp->guid_prefix);
	if (!cdr_ret) {
		return cdr_ret;
	}

	/* INFO_TS submessage */
	cdr_ret = rtps_msg_add_submsg_timestamp(cdr, &wcc->cc.ts);
	if (!cdr_ret) {
		return cdr_ret;
	}

	/* INFO_E2E submessage */
	if (writer_e2e_has_enabled(w)) {
		/* FIXME:
		 * e2e_count is equal to the value of last_used_sn minus 1.
		 * Ensure that when taking the last_used_sn value,
		 * the value needs to be greater than 0.
		 */
		mcdr_copy_buffer(e2e_start_pos, cdr);

		cdr_ret = rtps_msg_init_submsg_e2e(cdr, wcc);
		if (!cdr_ret) {
			return cdr_ret;
		}
	}

	/* DATA submessage */
	mcdr_copy_buffer(data_start_pos, cdr);
	cdr_ret = rtps_msg_add_submsg_data(cdr, wcc, false, &writer_id,
					   &reader_id);
	if (!cdr_ret) {
		return cdr_ret;
	}

	return true;
}

int32_t writer_send_wcc(struct writer *w, struct writer_cache_change *wcc)
{
	bool				cdr_ret = false;
	int32_t				send_status = (int32_t)TRANS_CODE_ALL_FAIL;
	int32_t				ret_send = 0;
	uint32_t			proxies_cnt = 0;
	uint32_t			proxies_send_failed_cnt = 0;
	struct mvbs_cdr			data_start_pos = { 0 };
	struct mvbs_cdr			e2e_start_pos = { 0 };
	struct mvbs_cdr			*cdr = NULL;
	struct participant		*ptcp = NULL;
	struct reader_proxy		*proxy = NULL;
	locator_t			*loc = NULL;

	ptcp = writer_get_ptcp(w);

	cdr = ptcp_get_tx_buffer(ptcp);

	mcdr_reset_buffer(cdr);

	/* init RTPS Header, TS, E2E, DATA submsg */
	cdr_ret = writer_init_user_data_submsg(cdr, w, wcc, &data_start_pos, &e2e_start_pos);
	if (!cdr_ret) {
		pr_err(ERR_NOMEM, "Buffer in transport has error.");
		return TRANS_CODE_ALL_FAIL;
	}

	foreach_writer_proxy(w, proxy)
	{
		struct mvbs_cdr temp_e2e_cdr = { 0 };
		struct mvbs_cdr temp_data_cdr = { 0 };
		mcdr_copy_buffer(&temp_e2e_cdr, &e2e_start_pos);
		mcdr_copy_buffer(&temp_data_cdr, &data_start_pos);

		loc = ptcp_proxy_get_user_uc_loc(proxy->ptcp_proxy);

		/* Modify E2E reader_eid */
		if (writer_e2e_has_enabled(w)) {
			mcdr_serialize_array_uint8_t(&temp_e2e_cdr, NULL, 8);
			mcdr_align_to(&temp_e2e_cdr, 4U);
			rtps_msg_update_submsg_e2e(&temp_e2e_cdr, w, &proxy->eid, wcc);
		}
		/* Modify DATA reader_eid */
		mcdr_serialize_array_uint8_t(&temp_data_cdr, NULL, 8);
		mcdr_align_to(&temp_data_cdr, 2U);
		cdr_serialize_entity_id(&temp_data_cdr, &proxy->eid);

		ret_send = ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
					       mcdr_buffer_length(cdr), loc,
					       w->attr->ep_attr.backup_enabled);
		proxies_cnt++;

		if (writer_record_is_export(w)) {
			writer_record_hook(w, cdr, wcc, loc,
				data_start_pos.cur_pos - data_start_pos.start);
		}

		if (ret_send < 0) {
			proxies_send_failed_cnt++;
			pr_err(ret_send, "Fail to transport send for writer [%s]",
			       string_or_null(writer_get_topicname(w)));
		}

		pr_debug("Writer [%s] SN:%ld TS:%d-%d -> " LOCATOR_FMT,
			 string_or_null(writer_get_topicname(w)),
			 rtps_sn_to_int64(&wcc->cc.sn), wcc->cc.ts.seconds,
			 wcc->cc.ts.nanosec, LOCATOR_MEMBERS(loc));
	}

	if (writer_record_is_entrance(w)) {
		writer_record_hook(w, cdr, wcc, loc,
				data_start_pos.cur_pos - data_start_pos.start);
	}

	if (writer_is_stateful(w)) {
		send_status = writer_set_wcc_statues(wcc, proxies_cnt,
						     proxies_send_failed_cnt);
	}

	return send_status;
}

int32_t writer_send_data(struct writer *w, struct writer_cache_change *wcc_send)
{
	struct participant	*ptcp = NULL;

	int16_t	stat = TRANS_CODE_ALL_SUCCESS_ALL_OUT;
	int32_t ret;

	if ((w == NULL) || (wcc_send == NULL)) {
		return -ERR_INVALID;
	}

	if (writer_has_no_proxies(w)) {
		pr_verb("Skipping progress. No proxies.\n");

		if (writer_get_matched_count(w) != 0U) {
			stat = TRANS_CODE_ALL_FAIL_NO_PROXY_HAS_MATCHED;
		} else {
			stat = TRANS_CODE_ALL_FAIL_NO_PROXY_NO_MATCHED;
		}

		(void)cache_change_update_trans_status(wcc_send, stat);

		return stat;
	}

	/* Send cachechange to every reader proxy */
	ret = writer_send_wcc(w, wcc_send);

	/* Qos process */
	if (writer_is_stateful(w)) {
		ptcp = writer_get_ptcp(w);

		/* If it is RELIABLE QoS, send a heartbeat message to request an
		 * ACK message.
		 */
		w->writer_status.samples++;

		if (w->writer_status.samples >= ptcp_get_samples_before_hb(ptcp)) {
			sfwriter_send_heartbeat(w, false);

			/*
			 * FIXME: clean the writer_status.samples only when send
			 * heartbeat successfully.
			 */
			w->writer_status.samples = 0;
		}
	} else {
		if (writer_get_durability_kind(w) == (uint16_t)VOLATILE) {
			/* remove min change, min change is the
			 * m_nextSequenceNumberToSend on VOLATILE mode
			 */
			writer_cache_del_oldest_cc(w);
		}
	}

	return ret;
}

struct writer_cache_change *writer_submit_change(struct writer *w,
					     instance_id id, const uint8_t *change,
					     uint16_t size)
{
	struct writer_cache_change *wcc;

	if ((w == NULL) || (change == NULL)) {
		pr_err(ERR_INVALID, "Invalid parameters\n");
		return NULL;
	}

	wcc = writer_add_cache(w, id, change, size);
	if (wcc == NULL) {
		pr_err(ERR_NOMEM, "topic(%s) writer add cache failed\n",
		       string_or_null(w->attr->ep_attr.topic_name));
		return NULL;
	}

	(void)cache_change_update_trans_status(wcc, (uint16_t)TRANS_CODE_INVALID);

	if (writer_is_stateful(w)) {
		/* loop all matched readers, add change seq in readerproxy */
		struct reader_proxy *proxy;

		foreach_writer_proxy(w, proxy) {
			reader_proxy_add_change(proxy, &wcc->cc.sn);
		}
	}

	return wcc;
}

const struct writer_cache_change *writer_new_change(struct writer *w,
					     instance_id id, const uint8_t *change,
					     uint16_t size)
{
	struct writer_cache_change *wcc;

	if ((w == NULL) || (change == NULL)) {
		pr_err(ERR_INVALID, "Invalid parameters\n");
		return NULL;
	}

	wcc = writer_submit_change(w, id, change, size);
	if (wcc == NULL) {
		pr_err(ERR_NOMEM, "topic(%s) writer submit change failed\n",
		       string_or_null(w->attr->ep_attr.topic_name));
		return NULL;
	}

	pr_verb("Adding new data.\n");
	(void)writer_send_data(w, wcc);
	return wcc;
}

struct rtps_sn writer_submit_instance_sample(struct writer *w,
					  instance_id id, const uint8_t *pdata,
					  uint16_t size)
{
	const struct writer_cache_change *wcc;

	wcc = writer_new_change(w, id, pdata, size);

	return (wcc == NULL)?RTPS_SN_UNKNOWN:wcc->cc.sn;
}

struct rtps_sn writer_submit_sample(struct writer *w,
				    const uint8_t *pdata, uint16_t size)
{
	return writer_submit_instance_sample(w, INSTANCE_INVALID, pdata, size);
}

void writer_on_new_acknack(struct writer *w,
			   const struct submessage_acknack *msg,
			   const struct participant_proxy  *ptcp_proxy)
{
	if (w == NULL) {
		return;
	}

	if (writer_is_stateful(w)) {
		sfwriter_on_new_acknack(w, msg, ptcp_proxy);
	}
}

void writer_assert_liveliness(struct writer *w)
{
	if (w == NULL) {
		return;
	}

	wlp_writer_assert_liveliness(w, true);
}

int32_t writer_get_sample_status(struct writer *w, struct rtps_sn writersn,
				  			TransferStatus *stats)
{
	/* find the min seq all acked by all readers */
	struct reader_proxy *rproxy = NULL;
	struct writer_cache_change *cc;
	struct rtps_sn min_all_acked;

	uint32_t unack_cnt = 0;
	uint32_t reliable_reader_cnt = 0;
	bool has_min_allacked = false;

	if ((w == NULL) || (stats == NULL)) {
		return -ERR_INVALID;
	}

	/* only process on RELIABLE mode */
	if (!writer_is_stateful(w)) {
		return -ERR_INVALID;
	}

	min_all_acked = writer_get_next_send_sn(w);

	/* case1: cachechange has been deleted */
	cc = writer_cache_get_cc(w, writersn);
	if (cc == NULL) {
		*stats = (TransferStatus)TRANS_CODE_NO_STATUS_CC_DELETED;
		return 0;
	}

	foreach_writer_proxy(w, rproxy) {
		if (rproxy->flags.reliable == 0U) {
			continue;
		}

		reliable_reader_cnt++;

		/* Find the min seq all acked by all readers*/
		if (rtps_sn_less(&rproxy->changes_lowmark, &min_all_acked)
		    || (!has_min_allacked)) {
			has_min_allacked = true;
			min_all_acked = rproxy->changes_lowmark;
		}
	}

	/* case2: transfer cachechange to all receivers success and get acks. */
	if(rtps_sn_less(&writersn, &min_all_acked) && (reliable_reader_cnt > 0U)){
		(void)cache_change_update_trans_status(cc, (uint16_t)TRANS_CODE_ALL_SUCCESS);
		*stats = (TransferStatus)TRANS_CODE_ALL_SUCCESS;
		return 0;
	}

	reliable_reader_cnt = 0;

	/* case3: test part ack or not
	 * Prerequisites: writersn >= min_all_acked, otherwise sequence_number_sub is wrong
	 */

	ulong_t *sent_map;

	foreach_writer_proxy(w, rproxy) {
		if (rproxy->flags.reliable == 0U) {
			continue;
		}

		reliable_reader_cnt++;
		/* calculate the offset to reader's changes_lowmark */
		if(!rtps_sn_less(&writersn, &rproxy->changes_lowmark))
		{
			struct rtps_sn sn_offset = rtps_sn_sub(&writersn, &rproxy->changes_lowmark);
			uint32_t shift = sn_offset.low;

			uint32_t bitmap_range = reader_proxy_get_sent_map_size(rproxy) * 8 - 1U;

			sent_map = reader_proxy_get_sent_map(rproxy);

			if ((sn_offset.high > 0) || (shift > bitmap_range)) {
				/* out of send_map range, treate it as unack */
				unack_cnt++;
				continue;
			}

			/* it means that the cachechange has not been acked, if the 'shift' bit is 1 */
			if (bitmap_test_bit(shift, sent_map)) {
				unack_cnt++;
			}
		}
	}

	/* case3: judge none ack or not */
	if ((unack_cnt == 0U) && (reliable_reader_cnt != 0U)) {
		(void)cache_change_update_trans_status(cc, (uint16_t)TRANS_CODE_ALL_SUCCESS);
		*stats = (TransferStatus)TRANS_CODE_ALL_SUCCESS;
		return 0;
	}

	if(unack_cnt == reliable_reader_cnt){
		/* keep reasons for "None Send" */
		if ((cc->send_status > (TransferStatus)TRANS_CODE_ALL_FAIL) && (cc->send_status < (TransferStatus)TRANS_CODE_ALL_FAIL_NONE_ACK)){
			*stats = (TransferStatus)cc->send_status;
		} else {
			(void)cache_change_update_trans_status(cc, (uint16_t)TRANS_CODE_ALL_FAIL_NONE_ACK);
			*stats = (TransferStatus)TRANS_CODE_ALL_FAIL_NONE_ACK;
		}
	} else {
		/* keep reasons for "partial send"
		 * and statue of "has been resent out"
		 */
		if ((cc->send_status > (TransferStatus)TRANS_CODE_PART_FAIL) && (cc->send_status < (TransferStatus)TRANS_CODE_PART_FAIL_PART_ACK)){
			*stats = (TransferStatus)cc->send_status;
		} else {
			(void)cache_change_update_trans_status(cc, (uint16_t)TRANS_CODE_PART_FAIL_PART_ACK);
			*stats = (TransferStatus)TRANS_CODE_PART_FAIL_PART_ACK;
		}
	}

	return 0;
}

static void writer_add_new_match_reader(struct writer *w,
					     struct reader_proxy *rproxy)
{
	/* for reliable: send history or gap, for besteffort: do not send */
	if (rproxy->flags.reliable == (uint8_t)0) {
		return;
	}

	if (rproxy->durability_kind == (uint8_t)TRANSIENT_LOCAL) {
		pr_verb("Late Joiner! TRANSIENT_LOCAL pairs. Send all old samples.\n");
		/* send all samples in history */
		writer_send_history(w, rproxy);
	} else {
		/* Send a GAP of the whole history from minSeq to maxSeq. */
		struct rtps_sn min_seq = writer_cache_get_min_sn(w);
		struct rtps_sn next_send = writer_get_next_send_sn(w);

		rproxy->changes_lowmark = next_send;

		if (!rtps_sn_equal(&min_seq, &RTPS_SN_UNKNOWN) &&
		    !rtps_sn_equal(&next_send, &RTPS_SN_UNKNOWN) &&
		    rtps_sn_lessequal(&min_seq, &next_send)) {
			struct rtps_sn_set gapList;

			rtps_sn_set_init(&gapList, &next_send);
			sfwriter_send_gap(w, rproxy, min_seq, &gapList);
		}
	}
}

void writer_add_proxy(struct writer *w, struct reader_proxy *rproxy)
{
	if ((w == NULL) || (rproxy == NULL)) {
		return;
	}

	if (rproxy->ptcp_proxy == NULL) {
		pr_verb("Skip the reader proxy [%02x %02x %02x: %02x].",
						rproxy->eid.entity_key[0],
						rproxy->eid.entity_key[1],
						rproxy->eid.entity_key[2],
						rproxy->eid.entity_kind);
		return ;
	}

	pr_verb("New reader %s added with id:\n", writer_get_topicname(w));

        /* FIXME:
         * When multiple readers are subscribed to this writer, using multicast
         * for data transmission may improve efficiency. However, the
         * unicast/multicast policy must be dynamically adjusted when remote
         * proxies join or leave the network.
         *
         * The 'w->attr->enforce_unicast' flag is intended to force the writer
         * to use unicast even if multicast is available, ensuring policy
         * consistency when reader proxy changed.
         */

        writer_add_new_match_reader(w, rproxy);

	rproxy->ptcp_proxy->has_endpoints = 1;
}

struct reader_proxy *writer_get_proxy(struct writer *w,
				 const struct participant_proxy *ptcp_proxy,
				 struct rtps_entity_id reader_eid)
{
	struct reader_proxy *proxy = NULL;

	if ((w == NULL) || (ptcp_proxy == NULL)) {
		return NULL;
	}

	foreach_writer_proxy(w, proxy) {
		if (proxy->ptcp_proxy != ptcp_proxy) {
			continue;
		}

		if (rtps_entity_id_equal(&proxy->eid, &reader_eid)) {
			return proxy;
		}
	}

	return NULL;
}

bool writer_remove_proxy(struct writer *w,
			 const struct participant_proxy *ptcp_proxy,
			 struct rtps_entity_id id)
{
	struct reader_proxy *proxy = NULL;

	if ((w == NULL) || (ptcp_proxy == NULL)) {
		return false;
	}

	proxy = writer_get_proxy(w, ptcp_proxy, id);
	if (proxy == NULL) {
		return false;
	}

	reader_proxy_destroy(proxy);

        /* FIXME:
         * When multiple readers are subscribed to this writer, using multicast
         * for data transmission may improve efficiency. However, the
         * unicast/multicast policy must be dynamically adjusted when remote
         * proxies join or leave the network.
         *
         * The 'w->attr->enforce_unicast' flag is intended to force the writer
         * to use unicast even if multicast is available, ensuring policy
         * consistency when reader proxy changed.
         */

	if (writer_is_stateful(w)) {
		sfwriter_check_change_ack_status(w);
	}

	return true;
}

void writer_remove_proxies_with_ptcp(struct writer *w,
				    struct participant_proxy *ptcp_proxy)
{
	struct reader_proxy *proxy;

	if ((w == NULL) || (ptcp_proxy == NULL)
		|| (!mem_pool_is_valid(&w->proxies))) {
		return;
	}

	foreach_writer_proxy(w, proxy) {
		if (proxy->ptcp_proxy != ptcp_proxy) {
			continue ;
		}

		reader_proxy_destroy(proxy);
	}

        /* FIXME:
         * When multiple readers are subscribed to this writer, using multicast
         * for data transmission may improve efficiency. However, the
         * unicast/multicast policy must be dynamically adjusted when remote
         * proxies join or leave the network.
         *
         * The 'w->attr->enforce_unicast' flag is intended to force the writer
         * to use unicast even if multicast is available, ensuring policy
         * consistency when reader proxy changed.
         */

	if (writer_is_stateful(w)) {
		sfwriter_check_change_ack_status(w);
	}
}

static inline int32_t writer_proxy_pool_init(struct writer *w,
					     uint16_t max_readers)
{
	if (max_readers <= 0U) {
		return 0;
	}

	return mem_pool_reset(&w->proxies);
}

static inline void writer_proxy_pool_deinit(struct writer *w)
{
	/* FIXME */
	mem_pool_deinit(&w->proxies);
}

int32_t writer_init(struct writer *w)
{
	const struct writer_attr *attr;
	struct participant *ptcp;
	uint32_t sample_max_size;
	int32_t ret = -ERR_NOMEM;

	if ((w == NULL) || (w->attr == NULL)) {
		return -ERR_INVALID;
	}

	ptcp = writer_get_ptcp(w);
	attr = w->attr;
	sample_max_size = attr->type->type_size();

	/* init reader proxy mempool */
	ret = writer_proxy_pool_init(w, attr->max_matched_readers);
	if (ret != 0) {
		pr_err(ret, "Fail to init mem pool of prproxy.\n");
		goto reader_proxy_failed;
	}

	/* init history cache and instance cache for app writer */
	ret = writer_cache_init(w, sample_max_size);
	if (ret < 0) {
		pr_err(ret, "Writer history init failed(%d)\n", ret);
		goto history_failed;
	}

	/* deadline qos policy */
	ret = writer_deadline_init(w);
	if (ret < 0) {
		pr_err(ret, "Writer deadline init failed(%d)\n", ret);
		goto deadline_failed;
	}

	/* lifespan qos policy */
	ret = writer_lifespan_init(w);
	if (ret < 0) {
		pr_err(ret, "Writer lifespan init failed!(%d)\n", ret);
		goto lifespan_failed;
	}

	/* liveliness qos policy */
	ret = wlp_add_local_writer(w);
	if ((ret < 0) && (ret != -ERR_OVERFLOW)) {
		pr_err(ret, "wlp add local writer failed(%d)\n", ret);
		goto wlp_failed;
	}

	ret = sfwriter_init(w);
	if (ret < 0) {
		pr_err(ret, "sfwriter init failed\n");
		goto wlp_failed;
	}

	writer_record_disable(w);

	w->last_used_sn	= RTPS_SEQUENCE_NUMBER(0);

	w->listener = NULL;

	return 0;

wlp_failed:
	mvbs_timer_delete(ptcp, w->lifespan_td);

lifespan_failed:
	mvbs_timer_delete(ptcp, w->deadline_td);

deadline_failed:
	(void)writer_cache_deinit(w);

history_failed:
	writer_proxy_pool_deinit(w);

reader_proxy_failed:
	return ret;
}

void writer_deinit(struct writer *w)
{
	struct reader_proxy *rproxy;
	struct participant *ptcp;

	if (w == NULL) {
		return;
	}

	wlp_delete_local_writer(w);

	ptcp = writer_get_ptcp(w);

	mvbs_timer_delete(ptcp, w->deadline_td);
	mvbs_timer_delete(ptcp, w->lifespan_td);

	if (writer_is_stateful(w)) {
		sfwriter_deinit(w);
	}

	(void)writer_cache_deinit(w);

        foreach_writer_proxy(w, rproxy) {
		reader_proxy_del_all_change(rproxy);

		writer_on_publication_matched(w, false);
        }

	/* FIXME */
	mem_pool_deinit(&w->proxies);
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
