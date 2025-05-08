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
#include <mvbs/utils/cdefs.h>
#include <mvbs/utils/mm.h>
#include <mvbs/utils/time.h>
#include <mvbs/utils/timer.h>
#include <mvbs/utils/log.h>
#include <mvbs/utils/string.h>
#include <discovery/sddp.h>
#include <messages/message_factory.h>

#define AUTOMAITC_ANNOUNCE_ACTIVE      0x01U
#define MANUAL_ANNOUNCE_ACTIVE         0x02U

#define RESERVE_SIZE                   0x08
#define PAYLOAD_SIZE                   0x10
#define ACTIVE_OFFSET                  0x0f

extern const struct buildin_reader dpde_readers[];
extern const struct buildin_writer dpde_writers[];

static void wlp_assert_all_reader_liveliness_by_kind(participant_t *ptcp,
						  uint16_t liveliness_kind)
{
	struct liveliness_policy	liveliness;
	struct reader			*r;

	foreach_ptcp_reader(ptcp, r) {
		/* builtin reader */
		if (r->liveliness_td == TIMER_DESC_INVALID) {
			continue;
		}

		if (r->attr->ep_attr.qos.liveliness_kind != liveliness_kind) {
			continue;
		}

		liveliness = r->attr->ep_attr.liveliness;

		(void)mvbs_timer_update_timeout(ptcp, r->liveliness_td,
					MVBS_TIMER_RELTIME,
					liveliness.lease_duration.seconds,
					liveliness.lease_duration.nanosec);
	}
}

static inline void rtps_time_update(rtps_time_t *t)
{
	mvbs_get_time(&t->seconds, &t->nanosec);
}

static void send_liveliness_message(struct participant *ptcp,
				    struct instance_handle instance)
{
	struct participant_proxy	*proxy;
	locator_t			*loc;
	mvbs_cdr_t			*cdr;
	mvbs_cdr_t			buffer;
	struct rtps_time		ts;

	bool				ret;

	uint8_t m_buffer[MAX_ANNOUNCE_SIZE] = {0};

	/* step1: make a livelinsss message */
	mcdr_init_buffer(&buffer, m_buffer, (uint32_t)ARRAY_SIZE(m_buffer));

	(void)cdr_serialize_liveliness_msg(&buffer, instance);

	/* step2: Prepare a RTPS message to send the livelinsss message */
	cdr = ptcp_get_tx_buffer(ptcp);

	mcdr_reset_buffer(cdr);

	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

	rtps_time_update(&ts);

	/* INFO_TS submessage */
	ret = rtps_msg_add_submsg_timestamp(cdr, &ts);
	if (!ret) {
		return ;
	}

	rtps_sn_increase(&ptcp->wlp_handler.writer_sn);

	rtps_msg_add_submsg_data_raw(cdr, &ptcp->wlp_handler.writer_sn,
			mcdr_get_buffer(&buffer),
			mcdr_buffer_length(&buffer), false,
			&ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_WRITER,
			&ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_READER);

	foreach_ptcp_proxy(ptcp, proxy) {
		if (!ptcp_proxy_has_wlp_reader(proxy)) {
			continue;
		}

		loc = ptcp_proxy_get_meta_uc_loc(proxy);

		(void )ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
					   mcdr_buffer_length(cdr), loc, false);
	}

	pr_verb("send liveliness message\n");
}

static void writer_liveliness_expired(void *arg)
{
	struct writer *w = (struct writer *)arg;

	if (w == NULL) {
		pr_err(ERR_INVALID, "Invalid pwriter pointer.\n");
		return;
	}

	w->writer_status.lstatus = (uint8_t)NOT_ALIVE;

	pr_info("writer liveliness expired\n");
}

static void reader_liveliness_expired(void *arg)
{
	struct reader *r = (struct reader *)arg;

	if (r == NULL) {
		pr_err(ERR_INVALID, "Invalid reader pointer.\n");
		return;
	}

	if (reader_get_liveliness_kind(r) == (uint16_t)QOS_LIVE_AUTOMATIC) {
		r->auto_liveliness_status = (uint8_t)NOT_ALIVE;
	} else {
		r->liveliness_status = (uint8_t)NOT_ALIVE;
	}

	/* Update the ownership information when liveliness lost. */
	reader_ownership_update(r, NULL, false);

	pr_info("reader [%s] liveliness expired\n", reader_get_topicname(r));
}

static void writer_proxy_liveliness_expired(void *arg)
{
	struct writer_proxy *wproxy = (struct writer_proxy *)arg;
	struct reader *r = NULL;

	if (wproxy == NULL) {
		pr_err(ERR_INVALID, "Invalid pointer.\n");
		return;
	}

	r = writer_proxy_get_reader(wproxy);

	/*
	 * remote writer liveliness lost, a new owner should be selected only
	 * when the writer is current owner
	 */
	if (wproxy == r->owner) {
		reader_ownership_update(r, NULL, false);
	}

	wproxy->liveliness_status = NOT_ALIVE;

	pr_info("Wproxy [%s:" ENTITY_ID_FMT "] in reader [%s] liveliness expired.",
					ptcp_proxy_get_name(wproxy->ptcp_proxy),
					ENTITY_ID_PARTS(wproxy->eid),
					reader_get_typename(r));
}

static bool is_any_alive(struct participant *ptcp, uint16_t liveliness_kind)
{
	struct writer *w;

	foreach_ptcp_writer(ptcp, w) {
		if ((w->attr->ep_attr.qos.liveliness_kind == liveliness_kind) &&
		    (w->writer_status.lstatus == (uint8_t)ALIVING)) {
			return true;
		}
	}

	return false;
}

static void auto_announce(void *arg)
{
	struct participant *ptcp = (struct participant *)arg;

	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "Invalid participant pointer.\n");
		return;
	}

	if (ptcp->wlp_handler.auto_timer_refcnt == 0) {
		return;
	}

	send_liveliness_message(ptcp, ptcp->wlp_handler.auto_instance_handle);
}

static void ptcp_liveliness_announce(void *arg)
{
	struct participant *ptcp = (struct participant *)arg;

	if (ptcp->wlp_handler.ptcp_timer_refcnt == 0) {
		return;
	}

	if (is_any_alive(ptcp, QOS_LIVE_MANUAL_BY_PTCP)) {
		send_liveliness_message(ptcp, ptcp->wlp_handler.ptcp_instance_handle);
	}
}

int32_t ptcp_wlp_init(struct participant *ptcp)
{
	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "Invalid ptcp or endpoint pointer.\n");
		return -ERR_INVALID;
	}

	ptcp->wlp_handler.auto_td	= TIMER_DESC_INVALID;
	ptcp->wlp_handler.ptcp_td	= TIMER_DESC_INVALID;

	mvbs_memcpy(&ptcp->wlp_handler.auto_instance_handle, &ptcp->guid_prefix,
		  sizeof(ptcp->guid_prefix));

	ptcp->wlp_handler.auto_instance_handle.value[15] = AUTOMAITC_ANNOUNCE_ACTIVE;

	mvbs_memcpy(&ptcp->wlp_handler.ptcp_instance_handle, &ptcp->guid_prefix,
		  sizeof(ptcp->guid_prefix));

	ptcp->wlp_handler.ptcp_instance_handle.value[15] = MANUAL_ANNOUNCE_ACTIVE;

	rtps_sn_set_zero(&ptcp->wlp_handler.writer_sn);

	return 0;
}


static int32_t wlp_auto_liveliness_add_writer(struct participant *ptcp,
							struct writer *w)
{
	duration_t	announce_period;
	uint64_t	period_ms;

	announce_period = w->attr->ep_attr.liveliness.announcement_period;
	period_ms = duration_to_ms(&announce_period);

	if (ptcp->wlp_handler.auto_td == TIMER_DESC_INVALID) {
		ptcp->wlp_handler.auto_td = mvbs_timer_create(ptcp, auto_announce, ptcp, 1U);

		if (ptcp->wlp_handler.auto_td == TIMER_DESC_INVALID) {
			pr_err(ERR_NOMEM, "Create automatic timer failed.\n");
			return -ERR_NOMEM;
		}

		ptcp->wlp_handler.min_auto_ms = period_ms;

		(void)mvbs_timer_start(ptcp, ptcp->wlp_handler.auto_td,
				       MVBS_TIMER_RELTIME,
				       announce_period.seconds,
				       announce_period.nanosec);
	} else {
		if (period_ms > ptcp->wlp_handler.min_auto_ms) {
			ptcp->wlp_handler.min_auto_ms	= period_ms;
			(void)mvbs_timer_update_timeout(ptcp,
					ptcp->wlp_handler.auto_td,
					MVBS_TIMER_RELTIME,
					announce_period.seconds,
					announce_period.nanosec);
		}
	}

	ptcp->wlp_handler.auto_timer_refcnt++;

	return 0;
}

static int32_t wlp_ptcp_liveliness_add_writer(struct participant *ptcp,
							struct writer *w)
{
	struct liveliness_policy liveliness;
	duration_t		 announce_period;
	uint64_t		 period_ms;

	liveliness	= w->attr->ep_attr.liveliness;
	announce_period = w->attr->ep_attr.liveliness.announcement_period;
	period_ms	= duration_to_ms(&announce_period);

	if (ptcp->wlp_handler.ptcp_td == TIMER_DESC_INVALID) {
		ptcp->wlp_handler.ptcp_td = mvbs_timer_create(ptcp, ptcp_liveliness_announce, ptcp, 1U);

		if (ptcp->wlp_handler.ptcp_td == TIMER_DESC_INVALID) {
			pr_err(ERR_NOMEM, "Create participant timer failed.\n");
			return -ERR_NOMEM;
		}

		ptcp->wlp_handler.min_ptcp_ms = period_ms;
		(void)mvbs_timer_start(ptcp, ptcp->wlp_handler.ptcp_td,
						MVBS_TIMER_RELTIME,
						announce_period.seconds,
						announce_period.nanosec);
	} else {
		if (period_ms < ptcp->wlp_handler.min_ptcp_ms) {
			ptcp->wlp_handler.min_ptcp_ms = period_ms;

			(void)mvbs_timer_update_timeout(ptcp, ptcp->wlp_handler.ptcp_td,
						      MVBS_TIMER_RELTIME,
						      announce_period.seconds,
						      announce_period.nanosec);
		} else {
			if (w->liveliness_td != TIMER_DESC_INVALID) {
				pr_err(ERR_FAULT, "The writer livelinsss timer has been initialized\n");

				if ((ptcp->wlp_handler.ptcp_timer_refcnt == 0) &&
				    (ptcp->wlp_handler.ptcp_td != TIMER_DESC_INVALID)) {
					mvbs_timer_delete(ptcp, ptcp->wlp_handler.ptcp_td);
					return -ERR_EXIST;
				}
			}

			pr_verb("Added a relatively large lease duration for participant.\n");
		}
	}

	w->liveliness_td = mvbs_timer_create(ptcp, writer_liveliness_expired, w, 0U);
	if (w->liveliness_td == TIMER_DESC_INVALID) {
		if ((ptcp->wlp_handler.ptcp_timer_refcnt == 0) &&
			(ptcp->wlp_handler.ptcp_td != TIMER_DESC_INVALID)) {
			mvbs_timer_delete(ptcp, ptcp->wlp_handler.ptcp_td);
		}

		pr_err(ERR_NOMEM, "Create pwriter timer failed.\n");
		return -ERR_NOMEM;
	}

	(void)mvbs_timer_update_timeout(ptcp, w->liveliness_td, MVBS_TIMER_RELTIME,
					   liveliness.lease_duration.seconds,
					   liveliness.lease_duration.nanosec);

	ptcp->wlp_handler.ptcp_timer_refcnt++;

	return 0;
}

static int32_t wlp_topic_liveliness_add_writer(struct writer *w)
{
	struct liveliness_policy liveliness;
	struct participant *ptcp;

	liveliness	= w->attr->ep_attr.liveliness;

	ptcp = writer_get_ptcp(w);

	w->liveliness_td = mvbs_timer_create(ptcp, writer_liveliness_expired, w, 0U);
	if (w->liveliness_td == TIMER_DESC_INVALID) {
		pr_err(ERR_NOMEM, "Create pwriter timer failed.\n");
		return -ERR_NOMEM;
	}

	(void)mvbs_timer_update_timeout(ptcp, w->liveliness_td,
					MVBS_TIMER_RELTIME,
					liveliness.lease_duration.seconds,
					liveliness.lease_duration.nanosec);

	return 0;
}

int32_t wlp_add_local_writer(struct writer *w)
{
	struct liveliness_policy liveliness;
	struct participant	*ptcp = NULL;
	int32_t			 ret;

	if (w == NULL) {
		pr_err(ERR_INVALID, "Invalid pwriter pointer.\n");
		return -ERR_INVALID;
	}

	ptcp		= writer_get_ptcp(w);
	liveliness	= w->attr->ep_attr.liveliness;

	/* builtin writer lease_duration is TIME_INFINITE */
	if (duration_is_infinite(&liveliness.lease_duration)) {
		pr_debug("writer [%s] hasn't been enable liveliness.\n",
						writer_get_topicname(w));
		return -ERR_OVERFLOW;
	}

	switch (w->attr->ep_attr.qos.liveliness_kind) {
	case (uint16_t)QOS_LIVE_AUTOMATIC:
		ret = wlp_auto_liveliness_add_writer(ptcp, w);
		break;

	case (uint16_t)QOS_LIVE_MANUAL_BY_PTCP:
		ret = wlp_ptcp_liveliness_add_writer(ptcp, w);
		break;

	case (uint16_t)QOS_LIVE_MANUAL_BY_TOPIC:
		ret = wlp_topic_liveliness_add_writer(w);
		break;

	default:
		pr_err(ERR_INVALID, "Unknown liveliness kind\n");

		return -ERR_INVALID;
	}

	return ret;
}

static void wlp_auto_liveliness_put(struct participant *ptcp)
{
	ptcp->wlp_handler.auto_timer_refcnt--;

	if (ptcp->wlp_handler.auto_timer_refcnt == 0) {
		mvbs_timer_delete(ptcp,ptcp->wlp_handler.auto_td);
	}

	return ;
}

static void wlp_ptcp_liveliness_put(struct participant *ptcp, struct writer *w)
{
	ptcp->wlp_handler.ptcp_timer_refcnt--;

	if (ptcp->wlp_handler.ptcp_timer_refcnt == 0) {
		mvbs_timer_delete(ptcp, ptcp->wlp_handler.ptcp_td);
	}

	mvbs_timer_delete(ptcp, w->liveliness_td);

	return ;
}

static void wlp_topic_liveliness_put(struct participant *ptcp, struct writer *w)
{
	mvbs_timer_delete(ptcp, w->liveliness_td);
}

void wlp_delete_local_writer(struct writer *w)
{
	struct liveliness_policy liveliness;
	struct participant	*ptcp = NULL;

	if (w == NULL) {
		pr_err(ERR_INVALID, "Invalid pwriter pointer.\n");
		return;
	}

	ptcp		= writer_get_ptcp(w);

	liveliness	= w->attr->ep_attr.liveliness;
	if (duration_is_infinite(&liveliness.lease_duration)) {
		return;
	}

	switch (w->attr->ep_attr.qos.liveliness_kind) {
	case (uint16_t)QOS_LIVE_AUTOMATIC:
		wlp_auto_liveliness_put(ptcp);
		break;

	case (uint16_t)QOS_LIVE_MANUAL_BY_PTCP:
		wlp_ptcp_liveliness_put(ptcp, w);
		break;

	case (uint16_t)QOS_LIVE_MANUAL_BY_TOPIC:
		wlp_topic_liveliness_put(ptcp, w);
		break;

	default:
		pr_err(ERR_NOENT, "Unknown liveliness kind\n");
		break;
	}
}

int32_t wlp_add_local_reader(struct reader *r, struct writer_proxy *wproxy)
{
	struct participant *ptcp;
	int32_t ret;

	if (r == NULL) {
		pr_err(ERR_INVALID, "Invalid reader pointer.\n");
		return -ERR_INVALID;
	}

	if (reader_liveliness_duration_is_infinite(r)) {
		return -ERR_OVERFLOW;
	}

	ret  = 0;
	ptcp = reader_get_ptcp(r);

	switch (reader_get_liveliness_kind(r)) {
	case (uint16_t)QOS_LIVE_AUTOMATIC:
	case (uint16_t)QOS_LIVE_MANUAL_BY_PTCP:
		if (r->liveliness_td == TIMER_DESC_INVALID) {
			r->liveliness_td = mvbs_timer_create(ptcp,
				reader_liveliness_expired, r, 0U);
		}

		if (r->liveliness_td == TIMER_DESC_INVALID) {
			pr_err(ERR_NOMEM, "Create reader liveliness timer failed.\n");
			ret = -ERR_NOMEM;
		}
		break;
	case (uint16_t)QOS_LIVE_MANUAL_BY_TOPIC:
		if (wproxy == NULL) {
			pr_err(ERR_INVALID,
				"Invalid wproxy for reader [%s] liveliness.\n",
				reader_get_topicname(r));

			return -ERR_INVALID;
		}

		wproxy->liveliness_td = mvbs_timer_create(ptcp,
						writer_proxy_liveliness_expired,
						wproxy, 0U);
		if (wproxy->liveliness_td == TIMER_DESC_INVALID) {
			pr_err(ERR_NOMEM, "Create write proxy liveliness timer failed.\n");
			ret = -ERR_NOMEM;
		}
		break;
	default:
		pr_err(ERR_INVALID, "Unknown liveliness kind\n");
		ret = -ERR_INVALID;
		break;
	}

	return ret;
}

void wlp_delete_local_reader(struct reader *r, struct writer_proxy *wproxy)
{
	struct participant *ptcp;

	if ((r == NULL) || (wproxy == NULL)) {
		pr_err(ERR_INVALID, "Invalid reader or wproxy pointer.\n");
		return;
	}

	if (wproxy->liveliness_td != TIMER_DESC_INVALID) {
		ptcp = reader_get_ptcp(r);
		mvbs_timer_delete(ptcp, wproxy->liveliness_td);
	}

	return;
}

static void wlp_writer_assert_liveliness_by_kind(struct participant *ptcp,
						 uint16_t kind)
{
	struct liveliness_policy liveliness;
	struct writer		*w;

	foreach_ptcp_writer(ptcp, w) {
		/* builtin w */
		if (w->liveliness_td == TIMER_DESC_INVALID) {
			continue;
		}

		if (w->attr->ep_attr.qos.liveliness_kind != kind) {
			continue ;
		}

		liveliness = w->attr->ep_attr.liveliness;

		(void)mvbs_timer_update_timeout(ptcp,
						w->liveliness_td,
						MVBS_TIMER_RELTIME,
						liveliness.lease_duration.seconds,
						liveliness.lease_duration.nanosec);
	}
}

void wlp_writer_assert_liveliness(struct writer *w, bool heartbeat)
{
	struct liveliness_policy liveliness;
	struct participant	*ptcp = NULL;
	uint16_t		liveliness_kind;

	if (w == NULL) {
		pr_err(ERR_INVALID, "Invalid pwriter pointer.\n");
		return;
	}

	/*
	 * QOS_LIVE_AUTOMATIC do not support assert_liveliness calls,
	 * so these writers timer is NULL, same as builtin writer.
	 * PARTICIPANT or TOPIC writer must be has owner timer.
	 */
	if (w->liveliness_td == TIMER_DESC_INVALID) {
		return;
	}

	liveliness = w->attr->ep_attr.liveliness;

	if (w->writer_status.lstatus != (uint8_t)ALIVING) {
		w->writer_status.lstatus = (uint8_t)ALIVING;
	}

	ptcp = writer_get_ptcp(w);

	liveliness_kind = w->attr->ep_attr.qos.liveliness_kind;

	switch (liveliness_kind) {
	case (uint16_t)QOS_LIVE_MANUAL_BY_PTCP:
		wlp_writer_assert_liveliness_by_kind(ptcp, liveliness_kind);
		break;

	case (uint16_t)QOS_LIVE_MANUAL_BY_TOPIC:
		(void)mvbs_timer_update_timeout(ptcp,
						w->liveliness_td,
						MVBS_TIMER_RELTIME,
						liveliness.lease_duration.seconds,
						liveliness.lease_duration.nanosec);

		/* TBD: statefulwriter send heartbeat with liveliness message */
		if (heartbeat && writer_is_stateful(w)) {
			pr_verb("wlp send heartbeat\n");

			sfwriter_send_heartbeat(w, true);
		}

		break;

	default:
		pr_err(ERR_FAULT, "Assert liveliness do not support!\n");
	}

	w->writer_status.lstatus = (uint8_t)ALIVING;

	return ;
}

void wlp_reader_assert_liveliness(struct reader *r, struct writer_proxy *wproxy)
{
	struct liveliness_policy liveliness;
	participant_t * ptcp = NULL;

	if (r == NULL) {
		pr_err(ERR_INVALID, "Invalid reader pointer.\n");
		return;
	}

	/* builtin reader and lease_duration value is invalid */
	if ((r->liveliness_td == TIMER_DESC_INVALID) &&
	    ((wproxy == NULL) || (wproxy->liveliness_td == TIMER_DESC_INVALID))) {
		return;
	}

	ptcp = reader_get_ptcp(r);
	liveliness = r->attr->ep_attr.liveliness;

	switch(r->attr->ep_attr.qos.liveliness_kind) {
	case (uint16_t)QOS_LIVE_AUTOMATIC:
		wlp_assert_all_reader_liveliness_by_kind(ptcp, QOS_LIVE_AUTOMATIC);
		r->auto_liveliness_status = (uint8_t)ALIVING;
		break;

	case (uint16_t)QOS_LIVE_MANUAL_BY_PTCP:
		wlp_assert_all_reader_liveliness_by_kind(ptcp, QOS_LIVE_MANUAL_BY_PTCP);
		r->liveliness_status = (uint8_t)ALIVING;
		break;

	case (uint16_t)QOS_LIVE_MANUAL_BY_TOPIC:
		if (wproxy == NULL) {
			pr_err(ERR_INVALID, "Invalid pwriter proxy pointer.\n");
			return;
		}

		(void)mvbs_timer_update_timeout(ptcp,
						wproxy->liveliness_td,
						MVBS_TIMER_RELTIME,
						liveliness.lease_duration.seconds,
						liveliness.lease_duration.nanosec);

		wproxy->liveliness_status = ALIVING;
		break;

	default:
		/*
		 * In fact, the log here will never be printed,
		 */
		pr_err(ERR_FAULT, "Assert liveliness do not support!\n");
	}

	return ;
}

void wlp_reader_match_writer(struct reader *r)
{
	struct liveliness_policy liveliness;
	struct participant	 *ptcp;

	/* May be BuiltIn reader */
	if ((r == NULL) || (r->liveliness_td == TIMER_DESC_INVALID)) {
		pr_err(ERR_INVALID, "Invalid parameters.\n");
		return;
	}

	liveliness = r->attr->ep_attr.liveliness;

	ptcp = reader_get_ptcp(r);
	(void)mvbs_timer_update_timeout(ptcp, r->liveliness_td,
					MVBS_TIMER_RELTIME,
					liveliness.lease_duration.seconds,
					liveliness.lease_duration.nanosec);
}

void wlp_reader_detach_writer(struct reader *r)
{
	struct participant *ptcp;

	/* May be BuiltIn reader */
	if ((r == NULL) || (r->liveliness_td == TIMER_DESC_INVALID)) {
		return;
	}

	if (!reader_has_no_proxies(r)) {
		return;
	}

	ptcp = reader_get_ptcp(r);

	/* cancel timer */
	(void)mvbs_timer_stop(ptcp, r->liveliness_td);
}

void p2p_reader_on_data(const struct buildin_reader *r,
			struct participant_proxy *ptcp_proxy,
			const struct submessage_data *msg,
			const struct submessage_data_extra *extra)
{
	(void)r;
	(void)ptcp_proxy;
	(void)msg;

	struct participant	*ptcp = extra->ptcp;
	struct mvbs_cdr		cdr = { 0 };

	uint8_t payload[PAYLOAD_SIZE] = { 0 };

	if (!ptcp_proxy_has_wlp_writer(ptcp_proxy)) {
		return;
	}

	mcdr_init_buffer(&cdr, extra->data, extra->size);

	(void)mcdr_deserialize_array_uint8_t(&cdr, payload,
					     (uint32_t)sizeof(payload));

	/* if enable wlp auto_timer, update expired to next */
	wlp_assert_all_reader_liveliness_by_kind(ptcp, QOS_LIVE_AUTOMATIC);

	pr_verb("Receive automatic ANNOUNCE");

	if (payload[ACTIVE_OFFSET] == MANUAL_ANNOUNCE_ACTIVE) {
		wlp_assert_all_reader_liveliness_by_kind(ptcp, QOS_LIVE_MANUAL_BY_PTCP);

		pr_verb("Receive participant ANNOUNCE");
	}

	return ;
}

void p2p_reader_on_heartbeat(const struct buildin_reader *r,
				struct participant_proxy *ptcp_proxy,
				const struct submessage_heartbeat *msg)
{
	struct buildin_writer_proxy *proxy;
	uint64_t first_sn;
	uint64_t last_sn;

	if (!ptcp_proxy_has_wlp_writer(ptcp_proxy)) {
		return;
	}

	proxy = &ptcp_proxy->sddp_proxies.p2p_reader;

	if (msg->msg_count <= proxy->heartbeat_count) {
		return;
	}

	proxy->heartbeat_count = msg->msg_count;

	first_sn = rtps_sn_to_int64(&msg->first_sn);
	last_sn  = rtps_sn_to_int64(&msg->last_sn);

	if (first_sn - 1 == last_sn) {
		proxy->avail_bits = 0;

		proxy->start_sn = (uint16_t)last_sn;

		return ;
	}

	if (last_sn < proxy->start_sn + proxy->avail_bits) {
		return ;
	}

	proxy->start_sn   = (uint16_t)first_sn;
	proxy->avail_bits = last_sn - first_sn + 1;

	pr_debug("EP: %s -> Get a heartbeat: %d:%d, avail_bits: %d",
			r->name, (uint32_t)first_sn, (uint32_t)last_sn, proxy->avail_bits);

	mvbs_memzero(proxy->recv_map, (proxy->avail_bits + 31)/32);
}

void p2p_writer_on_acknack(const struct buildin_writer *bw,
				  struct participant_proxy *ptcp_proxy,
				  const struct submessage_acknack *msg)
{
	struct buildin_reader_proxy	*proxy;

	if (!ptcp_proxy_has_wlp_reader(ptcp_proxy)) {
		return;
	}

	proxy = &ptcp_proxy->sddp_proxies.p2p_writer;

	if (msg->msg_count <= proxy->acknack_count) {
		pr_debug("%s: Recv ACK CNT: %d, Last ACK CNT: %d",
						bw->name, msg->msg_count,
						proxy->acknack_count);
		return;
	}

	proxy->acknack_count = msg->msg_count;

	/* Step1: Preemptive ACK Handle */
	if (msg_acknack_is_preemtive(msg)) {
		p2p_writer_send_hearbeat(ptcp_proxy, false);

		return ;
	}

	return ;
}

void p2p_writer_send_hearbeat(const struct participant_proxy *ptcp_proxy,
							     bool liveliness)
{
	struct rtps_sn			first_sn;
	struct rtps_sn			last_sn;
	const struct buildin_writer	*w;
	struct mvbs_cdr			*cdr;
	locator_t			*loc;
	struct participant		*ptcp = NULL;
	int32_t				ret = 0;

	if (!ptcp_proxy_has_wlp_reader(ptcp_proxy)) {
		return;
	}

	ptcp	    = ptcp_proxy_get_ptcp(ptcp_proxy);

	w	    = &dpde_writers[P2P_WRITER];

	cdr	= ptcp_get_tx_buffer(ptcp);
	loc	= ptcp_proxy_get_meta_uc_loc(ptcp_proxy);

	rtps_sn_set_value(&first_sn, 1);
	rtps_sn_set_value(&last_sn,  0);

	mcdr_reset_buffer(cdr);

	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

	(void)rtps_msg_add_submsg_heartbeat(cdr, &w->remote_eid, &w->eid,
					    first_sn, last_sn,
					    ptcp->p2p_writer_hb_count,
					    liveliness);

	ret = ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
				  mcdr_buffer_length(cdr),
				  loc, w->backup_link_enabled);

	pr_debug("%s: send heartbeat to %s", w->name, ptcp_proxy->ptcp_name);

	if (ret == 0) {
		ptcp->p2p_writer_hb_count++;
	} else {
		pr_err(ret, "%s: Fail to send heartbeat to %s.", w->name,
							ptcp_proxy->ptcp_name);
	}
}

void p2p_writer_on_ptcp_online(const struct buildin_writer *w,
				struct participant *ptcp,
				struct participant_proxy *ptcp_proxy)
{
	(void)w;
	(void)ptcp;

	if (!ptcp_proxy_has_wlp_reader(ptcp_proxy)) {
		return;
	}

	buildin_reader_proxy_init(&ptcp_proxy->sddp_proxies.p2p_writer,
						true, TRANSIENT_LOCAL);

	return;
}

void p2p_reader_on_ptcp_online(const struct buildin_reader *r,
				struct participant *ptcp,
				struct participant_proxy *ptcp_proxy)
{
	(void)r;
	(void)ptcp;

	if (!ptcp_proxy_has_wlp_writer(ptcp_proxy)) {
		return;
	}

	buildin_writer_proxy_init(&ptcp_proxy->sddp_proxies.p2p_reader);

	return;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
