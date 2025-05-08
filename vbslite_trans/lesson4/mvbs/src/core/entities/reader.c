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
#include <mvbs/mvbs.h>
#include <mvbs/errno.h>
#include <mvbs/utils/time.h>
#include <mvbs/utils/timer.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/mem_pool.h>
#include <mvbs/utils/log.h>
#include <mvbs/rtps/guid.h>
#include <messages/message_receiver.h>
#include <messages/message_factory.h>
#include <diag/recorder.h>
#include <qos/e2e.h>

#if READER_VERBOSE || RTPS_GLOBAL_VERBOSE
#undef MVBSLOG_LEVEL
#define MVBSLOG_LEVEL MVBSLOG_VERB
#endif

static bool reader_is_stateful(const struct reader *r)
{
	return (r->attr->ep_attr.qos.reliability_kind == (uint16_t)RELIABLE);
}

const struct reader_listener *reader_listener_setup(struct reader *r,
					      const struct reader_listener *l)
{
	const struct reader_listener *temp = NULL;

	if (r != NULL) {
		temp		= r->listener;
		r->listener	= l;
	}

	return temp;
}

void reader_set_private(struct reader *r, void *priv_data)
{
	if (r == NULL) {
		pr_err(ERR_INVALID, "reader is NULL.");
		return;
	}

	r->priv_data = priv_data;
}

void *reader_get_private(struct reader *r)
{
	if (r == NULL) {
		return NULL;
	}

	return r->priv_data;
}

/*
 * reader_get_topicname is a public interface, "static inline" isn't good to
 * hide the member of reader.
 */
const char *reader_get_topicname(const struct reader *r)
{
	if ((r == NULL) || (r->attr == NULL)) {
		pr_err(ERR_INVALID, "Reader or reader_attr is NULL.");
		return NULL;
	}

	return r->attr->ep_attr.topic_name;
}

/*
 * reader_get_typename is a public interface, "static inline" isn't good to
 * hide the member of reader.
 */
const char *reader_get_typename(const struct reader *r)
{
	if (r == NULL) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return NULL;
	}

	return r->attr->type->name;
}

static uint16_t reader_get_payload_size(struct reader *r)
{
	struct mem_pool* cc_pool = reader_get_cc_pool(r);

	if (cc_pool == NULL) {
		pr_err(ERR_NOMEM, "Fail to get '%s' reader_cache_change pool.",
						      reader_get_topicname(r));
		return 0;
	}

	if (cc_pool->blk_size <= sizeof(struct reader_cache_change)) {
		pr_debug("The reader '%s' payload size invalid.",
						reader_get_topicname(r));
		return 0;
	}

	return cc_pool->blk_size - (uint16_t)sizeof(struct reader_cache_change);
}

int32_t reader_get_status(struct reader *r, struct mvbs_endpoint_stat *stats)
{
	if ((r == NULL) || (stats == NULL)) {
		return -ERR_INVALID;
	}

	stats->remotes_online		= reader_get_matched_count(r);
	stats->total_remotes_online	= reader_get_total_matched_count(r);
	stats->total_remotes_offline	= stats->total_remotes_online
					- stats->remotes_online;

	stats->deadline_timeout		= reader_get_deadline_missed_count(r);

	stats->instances		= 0;

	stats->sample_committed		= reader_get_committed_sample(r);
	stats->sample_lost		= reader_get_lost_sample(r);
	stats->sample_rejected		= reader_get_rejected_sample(r);

	return 0;
}

size_t reader_get_onlinepeers(struct reader *r,
			      struct mvbs_entity_info *peer, size_t n)
{
	struct writer_proxy	*wproxy;
	size_t ret = 0;

	if (r == NULL) {
		return 0;
	}

	if ((peer == NULL) || (n == (size_t)0)) {
		return (size_t)(reader_get_onlinepeers_num(r));
	}

	foreach_reader_proxy(r, wproxy) {
		if (ret >= n) {
			break;
		}

		writer_proxy_get_guid(wproxy, &peer[ret].guid);

		peer[ret].remote_name = wproxy->ptcp_proxy->ptcp_name;

		ret++;
	}

	return ret;
}

static void reader_deadline_expired(void *arg)
{
	struct reader *r = (struct reader *)arg;

	if (r == NULL) {
		return;
	}

	pr_warn("Reader deadline missed!");

	/* FIXME:
	 * Update the ownership information when deadline missed.
	 */
	reader_ownership_update(r, NULL, false);

	reader_on_requested_deadline_missed(r);

	if ((reader_e2e_enabled(r)) && (reader_is_periodic(r))) {
		reader_on_e2e_exception(r, -1, E2E_P04STATUS_NONEWDATA);
	}
}

static int32_t reader_deadline_init(struct reader *r)
{
	const endpoint_attr_t *attr;
	struct participant *ptcp;

	attr = &(r->attr->ep_attr);

	if (duration_is_infinite(&attr->deadline.duration)) {
		pr_debug("Reader disable deadline timer: %s",
						reader_get_topicname(r));
		return 0;
	}

	ptcp = reader_get_ptcp(r);

	r->deadline_td = mvbs_timer_create(ptcp, reader_deadline_expired, r, 0U);
	if (r->deadline_td == TIMER_DESC_INVALID) {
		pr_err(ERR_NOMEM, "Fail to init deadline timer: %s",
						reader_get_topicname(r));
		return -ERR_NOMEM;
	}

	return 0;
}

static void reader_deadline_restart(struct reader *r)
{
	const duration_t *deadline;
	struct participant *ptcp;

	if (r->deadline_td == TIMER_DESC_INVALID) {
		pr_debug("Reader hasn't deadline timer: %s",
						reader_get_topicname(r));
		return ;
	}

	deadline = reader_get_deadline_duration(r);

	ptcp = reader_get_ptcp(r);

	/* Topic no key, just restart the deadline timer */
	(void)mvbs_timer_update_timeout(ptcp, r->deadline_td, MVBS_TIMER_RELTIME,
					deadline->seconds, deadline->nanosec);
}

static void reader_lifespan_expired(void *arg)

{
	struct reader *r = (struct reader *)arg;
	struct reader_cache_change *rcc = NULL;
	struct participant *ptcp;
	const duration_t *lifespan;
	uint64_t lifespan_ns;

	ptcp = reader_get_ptcp(r);

	lifespan = reader_get_lifespan_duration(r);

	lifespan_ns = duration_to_ns(lifespan);

	rcc = reader_cache_get_oldest_cc(r);
	while (rcc != NULL) {
		uint64_t elapse;

		elapse = mvbs_calculate_time_interval_till_now(rcc->ts_sent.seconds, rcc->ts_sent.nanosec);

		if (elapse < lifespan_ns) {
			uint64_t to_remain = lifespan_ns - elapse;
			uint64_t seconds = to_remain / TIME_NSEC_PER_SEC;

			(void)mvbs_timer_update_timeout(ptcp, r->lifespan_td,
						   MVBS_TIMER_RELTIME,
						   (int32_t)(seconds),
						   (uint32_t)(to_remain % TIME_NSEC_PER_SEC));

			return;
		}

		pr_debug("sample to delete: sn: %d:%u, elapse: %lu",
			 rcc->cc.sn.high, rcc->cc.sn.low, elapse);

		/* the earliest change has expired */
		reader_cache_del_oldest_cc(r);

		rcc = reader_cache_get_oldest_cc(r);
	}

	(void)mvbs_timer_update_timeout(ptcp, r->lifespan_td, MVBS_TIMER_RELTIME,
                                      lifespan->seconds, lifespan->nanosec);
}

static int32_t reader_lifespan_init(struct reader *r)
{
	const duration_t *lifespan;
	struct participant *ptcp;

	lifespan = reader_get_lifespan_duration(r);

	if (duration_is_infinite(lifespan)) {
		pr_debug("Reader disable lifespan timer: %s",
						reader_get_topicname(r));
		return 0;
	}

	ptcp = reader_get_ptcp(r);

	r->lifespan_td = mvbs_timer_create(ptcp, reader_lifespan_expired, r, 1U);
	if (r->lifespan_td == TIMER_DESC_INVALID) {
		pr_err(ERR_NOMEM, "Fail to init lifespan timer: %s",
						reader_get_topicname(r));
		return -ERR_NOMEM;
	}

	return mvbs_timer_start(ptcp, r->lifespan_td, MVBS_TIMER_RELTIME,
				lifespan->seconds, lifespan->nanosec);
}

static bool reader_ownership_reject(struct reader *r,
				    const struct writer_proxy *wproxy)
{
	if (r == NULL) {
		pr_err(ERR_INVALID, "Parameter error, invalid reader.");
		return true;
	}

	if (wproxy == NULL) {
		pr_verb("No writer proxy, only suited for spdpReader for now.");
		return false;
	}

	if (r->attr->ep_attr.qos.ownership_kind == (uint16_t)SHARED) {
		return false;
	}

	if (r->owner == NULL) {
		reader_ownership_update(r, NULL, false);
	}

	if (r->owner != wproxy) {
		pr_verb("Reader [%s] Sample rejected by ownership policy: "
			"current [%u] > received [%u]", reader_get_typename(r),
					writer_proxy_get_strength(r->owner),
					writer_proxy_get_strength(wproxy));
		return true;
	}

	return false;
}

void reader_ownership_update(struct reader *r, struct writer_proxy *wproxy,
								bool on_line)
{
	if (r == NULL) {
		return ;
	}

	if (r->attr->ep_attr.qos.ownership_kind == (uint16_t)SHARED) {
		return;
	}

	if (on_line) {
		/*
		 * New matched remote writer online, update ownership information
		 * when it's the first writer or it's strength is larger than current owner
		 */
		if (r->owner == NULL) {
			r->owner = wproxy;
		} else {
			if (writer_proxy_get_strength(wproxy) >
					writer_proxy_get_strength(r->owner)) {
				r->owner = wproxy;
			}
		}
	} else {
		/*
		 * Remote writer offline, select a new owner based on the strength value
		 * Find the proxy with the highest strength except old_owner.
		 */
		struct writer_proxy *proxy = NULL;
		struct writer_proxy *old_owner = NULL;
		uint16_t max_strength = 0U;
		uint16_t new_strength = 0U;

		old_owner	= r->owner;
		r->owner	= NULL;

		foreach_reader_proxy(r, proxy) {
			new_strength = writer_proxy_get_strength(proxy);

			pr_debug("Reader '%s' -> cur strength: %u, new strength: %u",
				reader_get_topicname(r), max_strength, new_strength);

			if ((new_strength > max_strength)
						&& (proxy != old_owner)) {
				r->owner	= proxy;
				max_strength	= new_strength;
			}
		}
	}
}
/*
 * For reliable:
 *	Only reject when history cache is full.
 *	The repeated sn will be rejected when setting received change bitmap.
 *
 * For besteffort:
 *	reject the sn that < the max_sn received from the same writer.
 */
static bool reader_sn_reject(struct reader *r, const struct reader_data *pdata)
{
	struct rtps_sn max_sn;

	if (reader_is_stateful(r)) {
		if (reader_cache_is_full(r)) {
			return true;
		}
	} else {
		max_sn = reader_cache_get_max_sn_with_wproxy(r, pdata->wproxy);
		if (rtps_sn_lessequal(&pdata->sn, &max_sn)) {
			return true;
		}
	}

	return false;
}

static void reader_send_ack(struct reader *r, struct writer_proxy *wproxy,
							bool preemptive)
{
	struct rtps_sn_set	set;
	struct mvbs_cdr		*cdr  = NULL;
	struct participant	*ptcp = NULL;
	struct rtps_entity_id	eid;
	int32_t ret;
	locator_t *loc = NULL;

#if 0	/* FIXME: TBD */
	if (wproxy->ptcp_proxy == NULL) {
		return;
	}
#endif

	/* FIXME: Maybe multicast location could be introduced in. */
	loc  = ptcp_proxy_get_user_uc_loc(wproxy->ptcp_proxy);
	ptcp = reader_get_ptcp(r);
	cdr  = ptcp_get_tx_buffer(ptcp);

	mcdr_reset_buffer(cdr);

	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

	if (preemptive) {
		rtps_sn_set_value(&set.base, 0);

		set.num_bits = 0;
	} else {
		set = writer_proxy_get_missing(wproxy);
	}

	eid = reader_get_eid(r);

	(void)rtps_msg_add_submsg_acknack(cdr, &(wproxy->eid), &eid, &set,
		       writer_proxy_get_acknack_count(wproxy), false);

	ret = ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
				  mcdr_buffer_length(cdr), loc,
				  r->attr->ep_attr.backup_enabled);
	if (ret < 0) {
		pr_err(ret, "transport send acknack failed(%d)", ret);
	}
}

bool reader_on_new_heartbeat(struct reader *r,
			     struct submessage_heartbeat *msg,
			     const struct participant_proxy *ptcp_proxy)
{
	struct writer_proxy	*wproxy = NULL;
	struct rtps_entity_id	writer_eid;
	uint16_t lost_count;

	if (r == NULL) {
		return false;
	}

	if (!reader_is_stateful(r)) {
		return true;
	}

	if ((msg == NULL) || (ptcp_proxy == NULL)) {
		return false;
	}

	writer_eid = msg->writer_id;

	wproxy = reader_get_proxy(r, ptcp_proxy, writer_eid);
	if (wproxy == NULL) {
		pr_verb("Reader [%s] hasn't proxy: ["ENTITY_ID_FMT"] of [%s]",
			reader_get_topicname(r),
			ENTITY_ID_PARTS(msg->writer_id),
			ptcp_proxy_get_name(ptcp_proxy));

		return false;
	}

	/* handle liveliness heartbeat first. */
	if ((msg->header.flags & (uint8_t)FLAG_HB_LIVELINESS) != 0U) {
		pr_verb("["ENTITY_ID_FMT"] of %s -> [%s]: hb liveliness flag = 1",
			ENTITY_ID_PARTS(msg->writer_id),
			ptcp_proxy_get_name(ptcp_proxy),
			reader_get_topicname(r));

		wlp_reader_assert_liveliness(r, wproxy);
		return true;
	}

	if (msg_submsg_heartbeat_is_invalid(msg)) {
		pr_err(ERR_INVALID, "heartbeat is invalid");
		return false;
	}

	if (msg->msg_count <= wproxy->hb_count) {
		pr_verb("Ignore heartbeat. Count too low.");
		return false;
	}

	/*
	 * Update the missing_lowmark and max_sn value according to first_sn
	 * and last_sn information.
	 */
	lost_count = writer_proxy_lost_changes_update(wproxy, &msg->first_sn,
							      &msg->last_sn);
	reader_lost_sample_add_value(r,(uint8_t)lost_count);

	wproxy->hb_count = msg->msg_count;

	reader_send_ack(r, wproxy, false);

	return true;
}

bool reader_on_new_gap(struct reader *r, struct submessage_gap *msg,
				const struct participant_proxy *ptcp_proxy)
{
	struct rtps_sn		start_sn = {0};
	struct rtps_sn		base_sn = {0};
	struct writer_proxy	*wproxy = NULL;
	struct rtps_entity_id	writer_eid;

	if (r == NULL) {
		return false;
	}

	if (!reader_is_stateful(r)) {
		return true;
	}

	if ((msg == NULL) || (ptcp_proxy == NULL)) {
		return false;
	}

	writer_eid  = msg->writer_id;

	wproxy = reader_get_proxy(r, ptcp_proxy, writer_eid);
	if (wproxy == NULL) {
		pr_verb("Couldn't find a matching writer with id:");
		rtps_entity_id_print(msg->writer_id);

		return false;
	}

	start_sn = msg->gap_start;
	base_sn  = msg->gap_list.base;

	while (rtps_sn_less(&start_sn, &base_sn)) {
		(void)writer_proxy_set_received_change(wproxy, &start_sn);

		reader_lost_sample_increase(r); /* for reliable */

		rtps_sn_increase(&start_sn);
	}

	for (uint32_t i = 0; i < msg->gap_list.num_bits; i++) {
		if (rtps_sn_set_is_valid(&msg->gap_list, i)) {
			(void)writer_proxy_set_received_change(wproxy, &base_sn);

			reader_lost_sample_increase(r);  /* for reliable */
		}

		rtps_sn_increase(&base_sn);
	}

	return true;
}

bool reader_on_new_e2e(const struct submessage_e2e sub_msg, struct e2e_header *header_src)
{
	header_src->crc		= sub_msg.crc;
	header_src->length	= sub_msg.length;

	return true;
}

/* now just process offline(shall has statu_info and pid), evbs will send
 * offline info in inlineqos
 */
static int32_t reader_process_inlineqos(struct reader *r, const uint8_t *data,
							  uint32_t len)
{
	struct mvbs_cdr cdr = {0};
	uint16_t pid = 0;
	uint16_t length = 0;
	struct rtps_guid guid;
	uint8_t status_info = 0;
	bool end_process = false;

	(void)r;

	mvbs_memzero(&guid, sizeof(struct rtps_guid));
	mcdr_init_buffer(&cdr, data, len);

	while (mcdr_buffer_remaining(&cdr) >= 4U) {
		(void)mcdr_deserialize_uint16_t(&cdr, &pid);
		(void)mcdr_deserialize_uint16_t(&cdr, &length);

		if (mcdr_buffer_remaining(&cdr) < length) {
			return -1;
		}

		switch (pid) {
			case PID_KEY_HASH:
				if (length != 16U) {
					/* Ignore value */
					(void)mcdr_deserialize_array_uint8_t(&cdr, NULL, length);
					break;
				}

				(void)cdr_deserialize_guid(&cdr, &guid);
				break;

			case PID_STATUS_INFO:
				if (length != 4U) {
					/* Ignore Status Info */
					(void)mcdr_deserialize_array_uint8_t(&cdr, NULL, length);
					break;
				}

				/*
				* skip first 3 bytes of status info as they are
				* reserved parameters
				*/
				(void)mcdr_deserialize_array_uint8_t(&cdr, NULL, 3U);
				(void)mcdr_deserialize_uint8_t(&cdr, &status_info);
				break;

			case PID_SENTINEL:
				/* Only pdp_reader, pub_reader and sub_reader is
				 * available here.
				 *
				 * reader_process_offline(r, &guid, status_info);
				 */
				end_process = true;
				break;

			default:
				(void)mcdr_deserialize_array_uint8_t(&cdr, NULL, length);
				break;
		}

		if (end_process) {
			return (int32_t)mcdr_buffer_length(&cdr);
		}
	}

	return -1;
}

/* just check appid and crc */
static uint32_t reader_e2e_check(struct reader *r,
				 struct e2e_header *e2e_new,
				 struct rtps_entity_id *rid,
				 struct rtps_entity_id *wid, struct rtps_sn *sn,
				 const uint8_t *pdata, uint16_t data_size)
{
	struct e2e_p04_cfg cfg;

	if ((r == NULL) || !reader_e2e_enabled(r)) {
		return (uint32_t)E2E_P04STATUS_OK;
	}

	if (!e2e_new->enable) {
		return (uint32_t)E2E_P04STATTUS_NODATAAVAILABLE;
	}

	// cfg.data_id		= r->attr->ep_attr.e2e.e2e_p04_data_id;
	cfg.min_data_length	= r->attr->ep_attr.e2e.e2e_p04_min_data_length;
	cfg.max_data_length	= r->attr->ep_attr.e2e.e2e_p04_max_data_length;
	cfg.max_delta_counter	= r->attr->ep_attr.e2e.e2e_p04_max_delta_counter;

	return e2e_do_checkP04(e2e_new, pdata, rid, wid, sn, cfg, data_size);
}

static inline struct reader_cache_change *reader_alloc_cache(struct reader *r)
{
	if (reader_cache_is_full(r)) {
		reader_lost_sample_increase(r);
		reader_cache_del_oldest_cc(r);
	}

	return reader_cache_change_alloc(r);
}

static struct reader_cache_change *reader_add_cache(struct reader *r,
				             struct reader_data *rdata)
{
	struct reader_cache_change *rcc;

	uint16_t payload_size;
	uint16_t length;

	if ((r == NULL) || (rdata == NULL)) {
		return NULL;
	}

	rcc = reader_alloc_cache(r);
	if (rcc == NULL) {
		pr_err(ERR_NOMEM, "Fail to alloc cache change: %s",
							reader_get_typename(r));
		reader_lost_sample_increase(r);

		return NULL;
	}

	length		= rdata->size;
	payload_size	= reader_get_payload_size(r);

	if (length > payload_size) {
		pr_warn("Reader '%s' recv data size %d > payload size %d",
				reader_get_topicname(r), length, payload_size);

		length = payload_size;
	}

	/* FIXME:
	 * Update it with reader_cache_change_copy ??
	 */
	mvbs_memcpy(reader_cache_change_payload(rcc), rdata->data, length);


	rcc->recv_size	= rdata->size;
	rcc->ts_sent	= rdata->src_time;
	rcc->e2e_status	= (uint16_t)rdata->e2e_status;
	rcc->counter	= rdata->e2e_counter;
	rcc->source	= rdata->wproxy;

	rcc->cc.sn	= rdata->sn;

	reader_cache_add_cc(r, rcc);

	/* deadline qos policy */
	reader_deadline_restart(r);

	reader_committed_sample_increase(r);

	return rcc;
}

static bool reader_new_data_valid(struct reader *r, struct reader_data *data,
						    struct writer_proxy *wproxy)
{
	if (reader_ownership_reject(r, wproxy)) {
		reader_rejected_sample_increase(r);
		return false;
	}

	if (reader_sn_reject(r, data)) {
		reader_rejected_sample_increase(r);
		return false;
	}

	if (reader_is_stateful(r)) {
		if (!writer_proxy_set_received_change(wproxy, &data->sn)) {
			reader_rejected_sample_increase(r);
			return false;
		}

		/* FIXME: lost too much or the lost sn is too small, send ack, */
		if (writer_proxy_need_send_ack(wproxy)) {
			reader_send_ack(r, wproxy, false);
		}
	}

	if ((data->data_flags & (uint8_t)FLAG_INLINE_QOS) != 0U) {
		int32_t inline_qos_size = 0;
		const uint8_t *pdata = data->data;

		inline_qos_size = reader_process_inlineqos(r, pdata, data->size);
		if (inline_qos_size < 0) {
			pr_err(ERR_FAULT, "inline qos process error");
			return false;
		}

		pdata	   += inline_qos_size;
		data->data  = pdata;
		data->size -= (uint16_t)inline_qos_size;
	}

	if (data->size == 0U) {
		return false;
	}

	data->e2e_status = reader_e2e_check(r, data->e2e_new, &data->reader_id,
						&data->writer_id, &data->sn, data->data, data->size);

	return true;
}

struct reader_cache_change *reader_append_new_change(struct reader *r,
				struct reader_data *data, instance_id *inst_id)
{
	instance_id id = INSTANCE_INVALID;

	struct reader_cache_change *rcc;
	struct writer_proxy *wproxy = NULL;

	if ((r == NULL) || (data == NULL)) {
		return NULL;
	}

	wproxy = reader_get_proxy(r, data->ptcp_proxy, data->writer_id);
	if (wproxy == NULL) {
		pr_debug("No writer proxy for reader eid, change dropped."
				ENTITY_ID_FMT,
				ENTITY_ID_PARTS(reader_get_eid(r)));
		/* FIXME:
		 * Remove current print for fixed "data->ptcp_proxy == NULL"
		 * rtps_guid_prefix_print(data->ptcp_proxy->guid.prefix);
		 */

		return NULL;
	}

	data->wproxy = wproxy;

	/* FIXME: reader_new_data_valid */
	if (!reader_new_data_valid(r, data, wproxy)) {
		pr_debug("This sample isn't valid for this reader.");
		return NULL;
	}

	rcc = reader_add_cache(r, data);
	if (rcc == NULL) {
		pr_err(ERR_NOMEM, "reader add cache failed");
		return NULL;
	}

	wlp_reader_assert_liveliness(r, wproxy);

	if (inst_id != NULL) {
		*inst_id = id;
	}

	return rcc;
}

void reader_on_new_data(struct reader *r, struct reader_data *data)
{
	instance_id	id = INSTANCE_INVALID;
	struct reader_cache_change *rcc;

	if ((r == NULL) || (data == NULL)) {
		return ;
	}

	rcc = reader_append_new_change(r, data, &id);
	if (rcc == NULL) {
		pr_debug("Fail to append data in to [%s] cache.",
					reader_get_topicname(r));
		return ;
	}

	pr_debug("Success append data in to [%s] cache.",
					reader_get_topicname(r));

	reader_on_data_available(r, id);
}

void reader_record_hook(struct reader *r,
			struct message_processing_info *pmsg_info,
			uint8_t* data_addr,
			uint16_t data_size)
{
	struct participant		*ptcp;
	int32_t ret = 0;

	if (reader_record_has_enabled(r)  == 0) {
		return;
	}

	ptcp = reader_get_ptcp(r);

	ret = recorder_send_reader_record(ptcp, pmsg_info, data_addr, data_size, r);
	if (ret != 0) {
		pr_err(ERR_INVALID, "Send soa log by reader error.");
	}

	return;
}

bool reader_get_instance_sample(struct reader *r, instance_id id,
				uint8_t *buffer, uint16_t dest_size,
				struct sample_info *info, bool take)
{
	struct reader_cache_change	*rcc;
	struct serialized_payload	ser_payload;
	int64_t sn;
	locator_t *loc;

	(void)id;

	if ((r == NULL) || (buffer == NULL)) {
		return false;
	}

	rcc = reader_cache_get_oldest_cc(r);
	if (rcc == NULL) {
		return false;
	}

	if ((info != NULL)&& (rcc->source)) {
		info->sn_info = rcc->cc.sn;
		loc = ptcp_proxy_get_user_uc_loc(rcc->source->ptcp_proxy);
		info->locator_kind = loc->kind;
	}

	if ((reader_e2e_enabled(r)) && (rcc->source)){
		if (take) {
			e2e_check_counter(r, rcc, rcc->source);

			if (info != NULL) {
				info->info_e2e.counter = rcc->counter;
				info->info_e2e.e2e_status = rcc->e2e_status;
			}

			sn = rtps_sn_to_int64(&rcc->cc.sn);

			if (rcc->e2e_status != E2E_P04STATUS_OK) {
				reader_on_e2e_exception(r, sn, rcc->e2e_status);
				rcc->source->last_e2e_err_flag = true;

				reader_cache_change_destroy(rcc);
				if (rcc->e2e_status != E2E_P04STATUS_OKSOMELOST) {
					/*Don't reject sample of E2E_P04STATUS_OKSOMELOST*/
					reader_rejected_sample_increase(r);
				}

				return false;
			}

			/*the first valid sample need to reset the flag and notify BSW */
			if (rcc->source->last_e2e_err_flag == true) {
				reader_on_e2e_exception(r, sn, rcc->e2e_status);
				rcc->source->last_e2e_err_flag = false;
			}
		} else {
			/* fixme, if read, we do not support get e2e info */
		}
	}

	ser_payload.data = reader_cache_change_payload(rcc);
	ser_payload.recv_size = (dest_size == 0)?rcc->recv_size:dest_size;

	if (!reader_data_deserialize(r, buffer, &ser_payload)) {

		reader_cache_change_destroy(rcc);
		reader_rejected_sample_increase(r);

		pr_err(ERR_MCDR, "%s deserialize data failed", reader_get_typename(r));
		return false;
	}

	if (info != NULL) {
		reader_cachachange_get_info(rcc, &info->info_src);
	}

	if (take) {
		reader_cache_change_destroy(rcc);
	}

	return true;
}

bool reader_get_sample(struct reader *r, uint8_t *buffer, uint16_t dest_size,
					struct sample_info *info, bool take)
{
	return reader_get_instance_sample(r, INSTANCE_INVALID, buffer,
							dest_size, info, take);
}

bool reader_add_proxy(struct reader *r, struct writer_proxy *wproxy)
{
	int32_t ret;

	if ((r == NULL) || (wproxy == NULL) || (wproxy->ptcp_proxy == NULL)) {
		return false;
	}

	pr_verb("reader '%s' add a writer proxy %s:" ENTITY_ID_FMT,
				string_or_null(r->attr->ep_attr.topic_name),
				string_or_null(wproxy->ptcp_proxy->ptcp_name),
				ENTITY_ID_PARTS(wproxy->eid));

	ret = wlp_add_local_reader(r, wproxy);
	if ((ret < 0) && (ret != -ERR_OVERFLOW)) {
		pr_err(ret, "Add wlp local reader failed");
		return false;
	}

#if 0
	/* FIXME:
	 * The following operations are not necessary.
	 * The sending of preemptive ACK should not be done here, and the processing
	 * of user preemptive ACK is not implemented according to the comments.
	 * Delete it here first and implement it elsewhere if you need to use it later.
	 */
	/* if reliable & translocal, send preemtive ack, writer will send history.
	 * for reliable & volitale, writer shall not send data in history
	 * for besteffort, do not need send preemtive ack
	 */
	 if (reader_is_stateful(r)) {
		reader_send_ack(r, wproxy, true);
	}
#endif
	wproxy->ptcp_proxy->has_endpoints = 1;

	return true;
}

struct writer_proxy *reader_get_proxy(struct reader *r,
			      const struct participant_proxy *ptcp_proxy,
			      struct rtps_entity_id writer_eid)
{
	struct writer_proxy *proxy;

	if ((r == NULL) || (ptcp_proxy == NULL)) {
		return NULL;
	}

	foreach_reader_proxy(r, proxy) {
		if (proxy->ptcp_proxy != ptcp_proxy) {
			continue ;
		}

		if (rtps_entity_id_equal(&proxy->eid, &writer_eid)) {
			return proxy;
		}
	}

	return NULL;
}

bool reader_remove_proxy(struct reader *r,
			 const struct participant_proxy *ptcp_proxy,
			 struct rtps_entity_id id)
{
	struct writer_proxy *proxy = NULL;

	if ((r == NULL) || (ptcp_proxy == NULL)) {
		return false;
	}

	proxy = reader_get_proxy(r, ptcp_proxy, id);
	if (proxy == NULL) {
		return false;
	}

	writer_proxy_destroy(proxy);

	return true;
}

void reader_remove_proxies_with_ptcp(struct reader *r,
			     struct participant_proxy *ptcp_proxy)
{
	struct writer_proxy *proxy = NULL;

	if ((r == NULL) || (ptcp_proxy == NULL)
			|| (!mem_pool_is_valid(&r->proxies))) {
		return;
	}

	foreach_reader_proxy(r, proxy) {
		if (proxy->ptcp_proxy != ptcp_proxy) {
			continue;
		}

		writer_proxy_destroy(proxy);
	}
}

static inline int32_t reader_proxy_pool_init(struct reader *r,
					     uint16_t max_writers)
{
	if (max_writers <= 0U) {
		return 0;
	}

	return mem_pool_reset(&r->proxies);
}

static inline void reader_proxy_pool_deinit(struct reader *r)
{
	/* FIXME */
	mem_pool_deinit(&r->proxies);
}

int32_t reader_init(struct reader *r)
{
	const struct reader_attr *attr;
	struct participant *ptcp;
	uint32_t sample_max_size;

	int32_t ret = -ERR_NOMEM;

	if ((r == NULL) || (r->attr == NULL)) {
		return -ERR_INVALID;
	}

	attr = r->attr;
	sample_max_size = attr->type->type_size();

	/* for pdp reader, the max_matched_writers is 0. */
	ret = reader_proxy_pool_init(r, attr->max_matched_writers);
	if (ret != 0) {
		pr_err(ret, "Fail to init writer proxy pool of [%s].",
						reader_get_topicname(r));
		goto writer_proxy_failed;
	}

	ret = reader_cache_init(r, sample_max_size);
	if (ret < 0) {
		pr_err(ret, "Reader history init failed(ret)", ret);
		goto history_failed;
	}

	/* deadline qos policy */
	ret = reader_deadline_init(r);
	if (ret < 0) {
		pr_err(ret, "Reader deadline init failed(ret %d)", ret);
		goto deadline_failed;
	}

	/* lifespan qos policy */
	ret = reader_lifespan_init(r);
	if (ret < 0) {
		pr_err(ret, "Reader lifespan init failed(ret)", ret);
		goto lifespan_failed;
	}

	/* ownership qos policy */
	r->owner = NULL;

	r->listener = NULL;
	reader_record_disable(r);

	return 0;

lifespan_failed:
	ptcp = reader_get_ptcp(r);
	mvbs_timer_delete(ptcp, r->deadline_td);

deadline_failed:
	(void)reader_cache_deinit(r);

history_failed:
	reader_proxy_pool_deinit(r);

writer_proxy_failed:
	return ret;
}

void reader_deinit(struct reader *r)
{
	struct writer_proxy *wproxy;
	struct participant *ptcp;

	if (r == NULL) {
		return;
	}

	ptcp = reader_get_ptcp(r);

	mvbs_timer_delete(ptcp, r->deadline_td);
	mvbs_timer_delete(ptcp, r->lifespan_td);

	reader_cache_deinit(r);

	foreach_reader_proxy(r, wproxy) {
		writer_proxy_del_all_change(r, wproxy);
		writer_proxy_free(wproxy);
	}

	wlp_reader_detach_writer(r);

	/* FIXME */
	mem_pool_deinit(&r->proxies);
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
