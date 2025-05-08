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

#ifndef MVBS_CORE_ENTITIES_WRITER_H
#define MVBS_CORE_ENTITIES_WRITER_H

#include <mvbs/base_type.h>
#include <mvbs/core/entities/ep_attr.h>

struct writer;

struct writer_matched_status {
	/* The num of current remote matched writers. */
	uint16_t current_count;

	/* The change of current_count since last listener is called. */
	int16_t current_count_change;
};

struct writer_deadline_missed_status {
	/*
	 * Missed deadlines accumulate, that is, each deadline period the
	 * total_count will be incremented by 1
	 */
	uint16_t total_count;
};

struct writer_listener {
	/*
	 * This method is called when the DataWriter is matched (or unmatched)
	 * against an endpoint.
	 */
	void (*on_matched)(struct writer *writer,
			   struct writer_matched_status *status);

	/*
	 * method called when a deadline is missed
	 */
	void (*on_deadline_missed)(struct writer *writer,
			           struct writer_deadline_missed_status *status);
#if 0
	/*
	 * This method is called when a new Reader is discovered, with a Topic
	 * that matches that of a local writer, but with a requested QoS that
	 * is incompatible with the one offered by the local struct writer
	 */
	void (*on_offered_incompatible_qos)(struct writer *writer, void *TBD);

	/*
	 * Method called when a sample has been removed unacknowledged
	 */
	void (*on_unacknowledged_sample_removed)(struct writer *writer, void *TBD);

	/*
	 * Method called when the liveliness of a writer is lost
	 */
	void (*on_liveliness_lost)(struct writer *writer, void *TBD);
#endif
};

/*
 * This structure is indicate the creation of struct writer and resource binded
 * with the writer.
 */
struct writer_attr {
	const char			*key;
	const struct type_plugin	*type;
	struct participant		*ptcp;

	struct endpoint_attr		ep_attr;

	struct writer_listener		listener;
	uint16_t			max_matched_readers;
	bool				enforce_unicast;
};

const char *writer_get_topicname(struct writer *w);
const char *writer_get_typename(struct writer *w);

struct rtps_sn writer_submit_instance_sample(struct writer *w,
					  instance_id id, const uint8_t *pdata,
					  uint16_t size);

struct rtps_sn writer_submit_sample(struct writer *w,
					    const uint8_t *pdata, uint16_t size);

int32_t writer_get_status(struct writer *w, struct mvbs_endpoint_stat *stats);


typedef uint16_t			TransferStatus;

enum {
	TRANS_CODE_INVALID,				/* invalid = 0 */

	TRANS_CODE_ALL_SUCCESS = 1,			/* transfer cachechange to all receivers success and get acks. */
	TRANS_CODE_ALL_SUCCESS_ALL_OUT,			/* cachechanges were sent out successfully, but the ack has not been received yet. */

	TRANS_CODE_PART_FAIL = 100,			/* not used. */
	TRANS_CODE_PART_FAIL_PART_OUT,			/* some cachechanges were not sent out. */
	TRANS_CODE_PART_FAIL_HAS_BEEN_RESENT,		/* some cachechanges send out fail, resend these cachechanges. */
	TRANS_CODE_PART_FAIL_PART_ACK,			/* some but not all cachechanges receive ack, maybe you need to wait for ack. */

	TRANS_CODE_ALL_FAIL = 200,			/* not used. */
	TRANS_CODE_ALL_FAIL_NO_PROXY_HAS_MATCHED,  	/* reason1, all failed to send out: the topic is matched, but no proxies. */
	TRANS_CODE_ALL_FAIL_NO_PROXY_NO_MATCHED, 	/* reason2, all failed to send out: the topic is not matched and no proxies. */
	TRANS_CODE_ALL_FAIL_PROXY_INVALID,    		/* reason3, all failed to send out: proxies exist, but invalid. */
	TRANS_CODE_ALL_FAIL_OTHERS,			/* other reasons, failed to send all cachechange out. */
	TRANS_CODE_ALL_FAIL_NONE_ACK,  			/* no ack has been received, maybe you need to wait for ack. */

	TRANS_CODE_NO_STATUS_CC_DELETED = 300,		/* cachechange has been deleted. */
	TRANS_CODE_UPPER_LIMIT				/* this value is placed at the end for valid value checking. */

	/* TODO:
	 * wait for underlying support to get the reason for sending out failure.
	 */
};

static inline bool transferstatus_is_valid(TransferStatus transfer_status)
{
	if (transfer_status >= (TransferStatus)TRANS_CODE_UPPER_LIMIT) {
		return false;
	} else {
		return true;
	}
}

int32_t writer_get_sample_status(struct writer *w,
			     struct rtps_sn writersn,
			     TransferStatus *stats);

size_t writer_get_onlinepeers(struct writer *w,
			      struct mvbs_entity_info *peer, size_t n);

void writer_set_private(struct writer *w, void *priv_data);
void *writer_get_private(struct writer *w);

const struct writer_listener *writer_listener_setup(struct writer *w,
					      const struct writer_listener *l);

#ifdef __MVBS_CORE_SOURCE__

#include <mvbs/utils/mem_pool.h>
#include <mvbs/core/history/history_cache.h>
#include <mvbs/core/entities/participant.h>
#include <mvbs/core/entities/stateful_writer.h>


#define MVBS_WRITER_STATE_RECORD

struct reader_proxy;
struct writer_cache_change;

struct writer_sample_status {
	uint16_t committed_sample;
};

struct writer {
	const struct writer_attr	*attr;

	struct mem_pool			proxies; /* struct reader_proxy */
	struct history_cache		history;

	struct writer_status		writer_status;	/* used for statefull writer */

	struct rtps_sn			last_used_sn;

	timer_desc_t			lifespan_td;
	timer_desc_t			deadline_td;
	timer_desc_t			liveliness_td;

#if defined(MVBS_WRITER_STATE_RECORD)
	uint8_t				deadline_missed_count;

	uint16_t			total_matched_count;
	uint16_t			matched_count;
	int16_t				matched_count_change;
	uint16_t			committed_sample;
#endif
	const struct writer_listener	*listener;
	void				*priv_data;
};

static inline struct writer *ptcp_get_writer_by_index(const struct participant *ptcp, uint16_t index)
{
	if (ptcp == NULL) {
		return NULL;
	}

	if (index >= ptcp->attr->writer_num) {
		return NULL;
	}

	return ptcp->attr->writers + index;
}

#define foreach_ptcp_writer(ptcp, w)			\
	for (int wi_ = 0; (w = ptcp_get_writer_by_index(ptcp, wi_)); wi_++)

#define foreach_writer_proxy(writer, proxy)		\
	foreach_mempool_avail_data(&writer->proxies, proxy)

static inline participant_t *writer_get_ptcp(const struct writer *w)
{
	return w->attr->ptcp;
}

static inline struct rtps_sn writer_get_next_send_sn(struct writer *w)
{
	int64_t value = 0;

	if (w == NULL) {
		return RTPS_SN_UNKNOWN;
	}

	value = rtps_sn_to_int64(&w->last_used_sn);
	value++;

	return RTPS_SEQUENCE_NUMBER(value);
}

static inline struct mem_pool *writer_get_cache_change_pool(struct writer *w)
{
	if (w == NULL) {
		return NULL;
	}

	return &w->history.cache_change;
}

static inline bool writer_has_key(struct writer *w)
{
	(void)w;

	return false;
}

static inline uint8_t writer_get_entity_kind(struct writer *w)
{
	(void)w;

	return USER_DEFINED_WRITER_WITHOUT_KEY;
}

static inline struct rtps_entity_id writer_get_eid(struct writer *w)
{
	struct rtps_entity_id eid;

	eid.entity_kind   = writer_get_entity_kind(w);

	rtps_entity_id_set_key(&eid, w->attr->ep_attr.entity_id);

	return eid;
}

static inline struct rtps_guid_prefix *writer_get_prefix(struct writer *w)
{
	struct participant *ptcp;

	ptcp = writer_get_ptcp(w);

	return &ptcp->guid_prefix;
}

static inline bool writer_eid_equal(struct writer *w, const struct rtps_entity_id *id)
{
	struct rtps_entity_id eid;

	eid = writer_get_eid(w);

	return rtps_entity_id_equal(&eid, id);
}

static inline bool writer_has_no_proxies(struct writer *w)
{
	return mem_pool_has_not_avail_data(&w->proxies);
}

static inline int32_t writer_topicname_cmp(struct writer *w, const char *topicname)
{
	return mvbs_strcmp(w->attr->ep_attr.topic_name, topicname);
}

static inline int32_t writer_typename_cmp(struct writer *w, const char *type_name)
{
	return mvbs_strcmp(w->attr->type->name, type_name);
}

static inline int32_t writer_key_cmp(struct writer *w, const char *key)
{
	return mvbs_strcmp(w->attr->key, key);
}

static inline bool writer_is_enable_mulitlocators(struct writer *w)
{
	return w->attr->ep_attr.backup_enabled;
}

static inline uint16_t writer_get_index(struct writer *w)
{
	return mp_get_blk_data_idx((void *)w);
}

static inline const duration_t *writer_get_deadline_duration(struct writer *w)
{
	return &(w->attr->ep_attr.deadline.duration);
}

static inline const duration_t *writer_get_lifespan_duration(struct writer *w)
{
	return &(w->attr->ep_attr.lifespan.duration);
}

static inline const duration_t *writer_get_liveliness_duration(struct writer *w)
{
	return &(w->attr->ep_attr.liveliness.lease_duration);
}

static inline bool writer_liveliness_duration_is_infinite(struct writer *w)
{
	const duration_t *liveliness;

	liveliness = writer_get_lifespan_duration(w);

	return duration_is_infinite(liveliness);
}

static inline uint16_t writer_get_reliability_kind(const struct writer *w)
{
	return w->attr->ep_attr.qos.reliability_kind;
}

static inline uint16_t writer_get_history_kind(const struct writer *w)
{
	return w->attr->ep_attr.qos.history_kind;
}

static inline uint16_t writer_get_ownership_kind(const struct writer *w)
{
	return w->attr->ep_attr.qos.ownership_kind;
}

static inline uint16_t writer_get_liveliness_kind(const struct writer *w)
{
	return w->attr->ep_attr.qos.liveliness_kind;
}

static inline uint16_t writer_get_durability_kind(const struct writer *w)
{
	return w->attr->ep_attr.qos.durability_kind;
}

static inline const char *writer_get_crc16(struct writer *w)
{
	if (!w->attr->ep_attr.crc16_enabled)
		return "";

	return w->attr->type->crc16;
}

static inline bool writer_e2e_has_enabled(struct writer *w)
{
	return w->attr->ep_attr.e2e.e2e_protection;
}

static inline bool writer_is_stateful(struct writer *w)
{
	return writer_get_reliability_kind(w) == (uint16_t)RELIABLE;
}

/* Return this type data max size after serialized */
static inline uint32_t writer_get_type_size(struct writer *w)
{
	return w->attr->type->type_size();
}

static inline bool writer_data_serialize(struct writer *w, void *data,
					 struct serialized_payload *payload)
{
	return w->attr->type->serialize(data, payload);
}

bool writer_match_ep_info(struct writer *w, const endpoint_info_t *info);

bool writer_del_cache(struct writer *w, struct rtps_sn seq_num);

bool writer_send_data_to(struct writer *w, struct writer_cache_change *send,
			 struct reader_proxy *proxy);
int32_t writer_send_data(struct writer *w, struct writer_cache_change *wcc_send);

struct writer_cache_change *writer_submit_change(struct writer *w,
					     instance_id id, const uint8_t *change,
					     uint16_t size);

const struct writer_cache_change *writer_new_change(struct writer *w,
					     instance_id id,
					     const uint8_t *change, uint16_t size);

struct reader_proxy *writer_get_proxy(struct writer *w,
				 const struct participant_proxy *ptcp_proxy,
				 struct rtps_entity_id reader_eid);

void writer_add_proxy(struct writer *w, struct reader_proxy *proxy);
bool writer_remove_proxy(struct writer *w,
			 const struct participant_proxy *ptcp_proxy,
			 struct rtps_entity_id id);

void writer_remove_proxies_with_ptcp(struct writer *w,
				    struct participant_proxy *ptcp_proxy);

void writer_on_new_acknack(struct writer *w,
			   const struct submessage_acknack *msg,
			   const struct participant_proxy  *ptcp_proxy);

void writer_assert_liveliness(struct writer *w);

int32_t writer_init(struct writer *w);
void writer_deinit(struct writer *w);

#if defined (MVBS_WRITER_STATE_RECORD)

static inline void writer_matched_increase(struct writer *w)
{
	w->total_matched_count++;

	w->matched_count++;

	w->matched_count_change++;
}

static inline void writer_matched_decrease(struct writer *w)
{
	w->matched_count--;

	w->matched_count_change--;
}

static inline uint16_t writer_get_total_matched_count(struct writer *w)
{
	return w->total_matched_count;
}

static inline uint16_t writer_get_matched_count(struct writer *w)
{
	return w->matched_count;
}

static inline int16_t writer_get_matched_count_change(struct writer *w)
{
	return w->matched_count_change;
}

static inline void writer_reset_matched_change_count(struct writer *w)
{
	w->matched_count_change = 0;
}

static inline uint8_t writer_get_deadline_missed_count(struct writer *w)
{
	return w->deadline_missed_count;
}

static inline void writer_deadline_missed_count_increase(struct writer *w)
{
	w->deadline_missed_count++;
}


static inline uint16_t writer_get_committed_sample(struct writer *w)
{
	return w->committed_sample;
}

static inline void writer_committed_sample_increase(struct writer *w)
{
	w->committed_sample++;
}

#else

static inline void writer_matched_increase(struct writer *w)
{
	(void)w;
}

static inline void writer_matched_decrease(struct writer *w)
{
	(void)w;
}

static inline uint16_t writer_get_total_matched_count(struct writer *w)
{
	(void)w;
	return 0U;
}

static inline uint16_t writer_get_matched_count(struct writer *w)
{
	(void)w;
	return 0U;
}

static inline int16_t writer_get_matched_count_change(struct writer *w)
{
	(void)w;
	return 0;
}

static inline void writer_reset_matched_change_count(struct writer *w)
{
	(void)w;
}

static inline uint8_t writer_get_deadline_missed_count(struct writer *w)
{
	(void)w;
	return 0U;
}

static inline void writer_deadline_missed_count_increase(struct writer *w)
{
	(void)w;
}

static inline uint8_t writer_get_committed_sample(struct writer *w)
{
	(void)w;
	return 0U;
}

static inline void writer_committed_sample_increase(struct writer *w)
{
	(void)w;
}

#endif

static inline void sedp_update_pub_matched_status(struct writer *w, bool match)
{
	if (w == NULL) {
		pr_err(ERR_INVALID, "Invaild parameter.\n");
		return;
	}

	if (match) {
		writer_matched_increase(w);
	} else {
		writer_matched_decrease(w);
	}
}

static inline void sedp_reset_pub_matched_status(struct writer *w)
{
	if (w == NULL) {
		pr_err(ERR_INVALID, "Invaild parameter.\n");
		return;
	}

	writer_reset_matched_change_count(w);
}

static inline void writer_on_publication_matched(struct writer *w, bool match)
{
	struct writer_matched_status status;

	if (w == NULL) {
		return ;
	}

	sedp_update_pub_matched_status(w, match);

	if (w->attr->listener.on_matched != NULL) {
		status.current_count	    = writer_get_matched_count(w);
		status.current_count_change = writer_get_matched_count_change(w);

		w->attr->listener.on_matched(w, &status);
	}

	sedp_reset_pub_matched_status(w);
}

static inline void writer_on_offered_deadline_missed(struct writer *w,
			struct writer_deadline_missed_status *status)
{
	if (w == NULL) {
		return ;
	}

	if (w->listener == NULL) {
		return ;
	}

	if (w->listener->on_deadline_missed == NULL) {
		return ;
	}

	w->listener->on_deadline_missed(w, status);

}

static inline void writer_record_entrance_enable(struct writer *w)
{
	w->writer_status.record_mode = 1;
}

static inline void writer_record_export_enable(struct writer *w)
{
	w->writer_status.record_mode = 2;
}

static inline void writer_record_disable(struct writer *w)
{
	w->writer_status.record_mode = 0;
}

static inline void writer_record_set(struct writer *w, const uint8_t mode)
{
	w->writer_status.record_mode = mode;
}

static inline uint8_t writer_record_is_entrance(struct writer *w)
{
	const uint8_t mode = w->writer_status.record_mode;
	const uint8_t cfg = w->attr->ep_attr.recorder_cfg;

	return (mode == 1 && cfg < 2) || (cfg == 1 && mode < 2);
}

static inline uint8_t writer_record_is_export(struct writer *w)
{
	return w->writer_status.record_mode == 2 ||
		w->attr->ep_attr.recorder_cfg == 2;
}

#endif
#endif
