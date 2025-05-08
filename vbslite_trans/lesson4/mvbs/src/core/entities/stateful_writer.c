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
#include <mvbs/utils/timer.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/log.h>
#include <mcdr/mcdr.h>
#include <messages/message_factory.h>

#if SFW_VERBOSE || RTPS_GLOBAL_VERBOSE
#undef MVBSLOG_LEVEL
#define MVBSLOG_LEVEL MVBSLOG_VERB
#endif

void sfwriter_change_removed_by_history(struct writer *w,
					struct rtps_sn *seq_num)
{
	struct reader_proxy *rproxy;

	if ((w == NULL) || (seq_num == NULL)) {
		pr_err(ERR_INVALID, "writer or seq_num is NULL");
		return;
	}

	foreach_writer_proxy(w, rproxy) {
		reader_proxy_del_change(rproxy, seq_num);
	}
}

void sfwriter_check_change_ack_status(struct writer *w)
{
	struct reader_proxy *rproxy;
	struct rtps_sn min_all_acked;
	bool has_min_allacked = false;

	if (w == NULL) {
		pr_err(ERR_INVALID, "Writer is NULL");
		return;
	}

	/* only process on VOLATILE mode */
	if (w->attr->ep_attr.qos.durability_kind != (uint16_t)VOLATILE) {
		return;
	}

	min_all_acked = writer_get_next_send_sn(w);

	/*
	 * Find out the min sn of all reader_proxy->changes_lowmark, and store
	 * it into min_all_acked.
	 */
	foreach_writer_proxy(w, rproxy) {
		if (rproxy->flags.reliable == 0U) {
			continue;
		}

		/* find the min seq all acked by all readers */
		if (!has_min_allacked) {
			has_min_allacked = true;
			min_all_acked	 = rproxy->changes_lowmark;

			continue;
		}

		if (rtps_sn_less(&rproxy->changes_lowmark, &min_all_acked)) {
			min_all_acked = rproxy->changes_lowmark;
		}
	}

	struct rtps_sn min_seq = hc_get_min_seq(&w->history);

	if (rtps_sn_less(&min_seq, &min_all_acked)) {
		/* delete all changes between minSeq to minAllacked-1 */
		writer_cache_del_cc_upto(w, min_all_acked);
	}
}

void sfwriter_on_new_acknack(struct writer *w,
			     const struct submessage_acknack *msg,
			     const struct participant_proxy  *ptcp_proxy)
{
	struct reader_proxy		*rproxy = NULL;
	struct writer_cache_change	*wcc_send = NULL;

	struct rtps_sn			gap_start = RTPS_SN_UNKNOWN;
	struct rtps_sn_set		gap_list;

	if ((w == NULL) || (msg == NULL) || (ptcp_proxy == NULL)) {
		pr_err(ERR_INVALID, "Writer or msg or ptcp_proxy is NULL");
		return;
	}

	/* Step1: Find out the reader proxy */
	rproxy = writer_get_proxy(w, ptcp_proxy, msg->reader_id);
	if (rproxy == NULL) {
		pr_info("Drop acknack from " ENTITY_ID_FMT "with in ptcp: %s",
					ENTITY_ID_PARTS(msg->reader_id),
					ptcp_proxy_get_name(ptcp_proxy));
		return;
	}

	/* Step2: Prevent Duplicate AckNack */
	if (msg->msg_count <= rproxy->acknack_count) {
		pr_verb("Count too small. Dropping acknack.");
		return;
	}

	rproxy->acknack_count = msg->msg_count;

	/* Step3: Preppare the gap_list */
	mvbs_memzero(&gap_list, sizeof(gap_list));

	/* Send missing packets */
	struct rtps_sn next_sn = msg->reader_sn_state.base;

	if (rtps_sn_lessequal(&next_sn, &rproxy->changes_lowmark)) {
		/* FIXME */
		// if ack, it should be OK.
		// if Nack , it should be send gap

		/* init this gap_list */
		rtps_sn_set_init(&gap_list, &next_sn);

		rtps_sn_set_add_range(&gap_list, &next_sn, &rproxy->changes_lowmark);
	}

	/* Step4: Preppare the gap_list */
	reader_proxy_acked_changes_set(rproxy, &msg->reader_sn_state.base);

	sfwriter_check_change_ack_status(w);

	/* Checking each bit in the acknack bitmap */
	for (uint32_t i = 0; i < msg->reader_sn_state.num_bits; i++) {
		/* Test the bit:
		 * 1: The sample of base_sn +i has been acked.
		 * 0: The sample of base_sn +i should be resent.
		 */
		if (!rtps_sn_set_is_valid(&msg->reader_sn_state, i)) {
			reader_proxy_ack_change(rproxy, &next_sn);
			rtps_sn_increase(&next_sn);

			continue;
		}

		/*Resend requested changes*/
		pr_verb("Send Packet on acknack seq:{%d.%u}.", next_sn.high, next_sn.low);
		wcc_send = writer_cache_get_cc(w, next_sn);

		if (wcc_send != NULL) {
			bool suces = writer_send_data_to(w, wcc_send, rproxy);
			if (suces) {
				(void)cache_change_update_trans_status(wcc_send,
						(uint16_t)TRANS_CODE_PART_FAIL_HAS_BEEN_RESENT);
			}
		} else {
			if (gap_list.num_bits == 0) {
				/* init this gap_list */
				rtps_sn_set_init(&gap_list, &next_sn);
				rtps_sn_set_set_bit(&gap_list, 0);

				gap_list.num_bits	= 1;

				gap_start		= next_sn;
			} else {
				rtps_sn_set_add(&gap_list, &next_sn);
			}
		}

		rtps_sn_increase(&next_sn);
	}

	/* send the gap msg */
	if (gap_list.num_bits != 0) {
		sfwriter_send_gap(w, rproxy, gap_start, &gap_list);
	}
}

void sfwriter_send_gap(struct writer *w,
			struct reader_proxy *rproxy,
			struct rtps_sn gap_start,
			struct rtps_sn_set *gap_list)
{
	struct mvbs_cdr		*cdr;
	locator_t		*loc = NULL;
	struct participant	*ptcp = NULL;
	struct rtps_entity_id	eid;
	int32_t	ret = 0;

	if (w == NULL) {
		pr_err(ERR_INVALID, "Writer is NULL.");
		return;
	}

	loc = ptcp_proxy_get_user_uc_loc(rproxy->ptcp_proxy);

	ptcp = writer_get_ptcp(w);

	cdr = ptcp_get_tx_buffer(ptcp);

	mcdr_reset_buffer(cdr);

	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

	eid = writer_get_eid(w);

	(void)rtps_msg_add_submsg_gap(cdr, &eid, reader_proxy_get_eid(rproxy),
							gap_start, gap_list);

	ret = ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
					mcdr_buffer_length(cdr),
					loc, w->attr->ep_attr.backup_enabled);
	if (ret != 0) {
		pr_err(ret, "Fail to send submessage gap.");
	}
}

static void sfwriter_add_gaps_for_holes_in_history(struct writer *w)
{
	struct rtps_sn first_seq = hc_get_min_seq(&w->history);
	struct rtps_sn last_seq  = hc_get_max_seq(&w->history);
	struct rtps_sn sub_seq = rtps_sn_sub(&last_seq, &first_seq);

	if (!rtps_sn_equal(&first_seq, &RTPS_SN_UNKNOWN) &&
	    ((sub_seq.low + 1U) != hc_get_cur_count(&w->history))) {
		/* There are holes in the history. */
		struct rtps_sn gap_start = RTPS_SN_UNKNOWN;
		struct rtps_sn gap_base;
		struct rtps_sn_set gap_list;
		struct rtps_sn prev = first_seq;
		struct cache_change *cc;

		mvbs_memzero(&gap_list, sizeof(gap_list));

		mvbs_list_for_each_entry(cc, &w->history.caches, history_node) {
			while (!rtps_sn_equal(&prev, &cc->sn)) {
				if (rtps_sn_equal(&gap_start, &RTPS_SN_UNKNOWN)) {
					gap_start = prev;
					gap_base = rtps_sn_add_value(&gap_start, 1U);
					rtps_sn_set_init(&gap_list, &gap_base);
				} else {
					if (rtps_sn_equal(&prev, &gap_list.base)) {
						gap_list.base = rtps_sn_add_value(&prev, 1U);
					}
					else {
						rtps_sn_set_add(&gap_list, &prev);
					}

				}
				rtps_sn_increase(&prev);
			}
			rtps_sn_increase(&prev);
		}

		struct reader_proxy *proxy;

		foreach_writer_proxy(w, proxy) {
			sfwriter_send_gap(w, proxy, gap_start, &gap_list);
		}

		return;
	}
}

void sfwriter_send_heartbeat(struct writer *w, bool liveliness)
{
	struct rtps_sn	first_sn;
	struct rtps_sn	last_sn;
	struct reader_proxy	*proxy;
	struct mvbs_cdr		*cdr;
	locator_t		*loc;
	struct participant	*ptcp = NULL;
	struct rtps_entity_id	eid;
	bool	hb_boost;
	int32_t	ret = 0;

	if (w == NULL) {
		pr_err(ERR_INVALID, "Writer is NULL.");
		return;
	}

	ptcp = writer_get_ptcp(w);

	if (writer_has_no_proxies(w)) {
		pr_verb("Skipping heartbeat. No proxies.");
		return;
	}

	sfwriter_add_gaps_for_holes_in_history(w);

	hb_boost = w->writer_status.hb_boost;

	cdr = ptcp_get_tx_buffer(ptcp);

	foreach_writer_proxy(w, proxy) {
		if (proxy->flags.reliable == 0U) {
			continue;
		}

		loc = ptcp_proxy_get_user_uc_loc(proxy->ptcp_proxy);

                first_sn = hc_get_min_seq(&w->history);
                last_sn  = hc_get_max_seq(&w->history);

                /* if history is empty, fisrtsn is next_to_send, lastsn is fisrtsn -1 */
		if (rtps_sn_equal(&first_sn, &RTPS_SN_UNKNOWN) ||
		    rtps_sn_equal(&last_sn, &RTPS_SN_UNKNOWN)) {
			first_sn = writer_get_next_send_sn(w);
			last_sn  = rtps_sn_sub_value(&first_sn, 1U);
		}

		mcdr_reset_buffer(cdr);

		(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

		eid = writer_get_eid(w);

		(void)rtps_msg_add_submsg_heartbeat(cdr, reader_proxy_get_eid(proxy),
					&eid, first_sn, last_sn,
					w->writer_status.hb_count, liveliness);

		ret = ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
					  mcdr_buffer_length(cdr),
					  loc,
					  w->attr->ep_attr.backup_enabled);

		if (!hb_boost && (ret < 0)) {
			/* send heartbeat failed, set period to next 5ms*/
			uint64_t ns = TIME_NSEC_PER_MSEC;
			ns = ns * 5U;

			(void)mvbs_timer_update_timeout(ptcp,
				w->writer_status.heartbeat_td,
				MVBS_TIMER_RELTIME, 0, (uint32_t)ns);
			w->writer_status.hb_boost = true;
		} else {
			if ((ret >= 0) && hb_boost) {
				/* reset */
				int32_t sec;
				uint32_t hb_ms;
				uint32_t nsec;
				sec = (int32_t)ptcp->attr->discovery.hb_policy.period_sec;
				hb_ms = ptcp->attr->discovery.hb_policy.period_msec;

				nsec = (uint32_t)((hb_ms *
						(uint32_t)TIME_NSEC_PER_MSEC));
				(void)mvbs_timer_update_timeout(ptcp,
					w->writer_status.heartbeat_td,
					MVBS_TIMER_RELTIME, sec, nsec);

				w->writer_status.hb_boost = false;
			}
		}
	}

	if (ret >= 0) {
		w->writer_status.hb_count++;
	}
}

static void sfwriter_send_heartbeat_loop(struct writer *w)
{

	sfwriter_send_heartbeat(w, false);
	w->writer_status.samples = 0;
}

static void sfwriter_heartbeat_jumppad(void *sfw)
{
	struct writer *w = (struct writer *)(sfw);

	sfwriter_send_heartbeat_loop(w);
}

int32_t sfwriter_init(struct writer *w)
{
	int32_t ret, sec;
	uint32_t nsec;
	uint16_t hb_ms;
	struct participant *ptcp = NULL;

	if (w == NULL) {
		pr_err(ERR_INVALID, "Writer is NULL.");
		return -ERR_INVALID;
	}

	ptcp = writer_get_ptcp(w);
	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "Fail to get ptcp by writer of [%s].",
						writer_get_topicname(w));
		return -ERR_INVALID;
	}

	if (!writer_is_stateful(w)) {
		return 0;
	}

	sec   = (int32_t)ptcp->attr->discovery.hb_policy.period_sec;
	hb_ms = ptcp->attr->discovery.hb_policy.period_msec;

	nsec  = (uint32_t)(((uint32_t)hb_ms * (uint32_t)TIME_NSEC_PER_MSEC));

	w->writer_status.heartbeat_td
			= mvbs_timer_create(ptcp, sfwriter_heartbeat_jumppad, w, 1);
	if (w->writer_status.heartbeat_td == TIMER_DESC_INVALID) {
		pr_err(ERR_NOMEM, "sfwriter hbthread create error");
		return -ERR_NOMEM;
	}

	ret = mvbs_timer_start(ptcp,w->writer_status.heartbeat_td,
				MVBS_TIMER_RELTIME, sec, nsec);
	if ( ret < 0) {
		pr_err(ret, "timer start err");
		mvbs_timer_delete(ptcp, w->writer_status.heartbeat_td);
		return ret;
	}

	w->writer_status.hb_count = 1;
	w->writer_status.hb_boost = false;
	w->writer_status.running  = true;

	return 0;
}

void sfwriter_deinit(struct writer *w)
{
	struct participant *ptcp;

	if (w == NULL) {
		pr_err(ERR_INVALID, "Writer is NULL.");
		return;
	}

	ptcp = writer_get_ptcp(w);

	mvbs_timer_delete(ptcp, w->writer_status.heartbeat_td);
}
#undef SFW_VERBOSE

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
