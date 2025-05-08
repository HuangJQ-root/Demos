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

#ifndef MVBS_CORE_ENTITIES_READER_H
#define MVBS_CORE_ENTITIES_READER_H

#include <mvbs/base_type.h>
#include <mvbs/core/entities/ep_attr.h>
#include <mvbs/rtps/sequence_number.h>

struct reader;

struct reader_matched_status {
	/* The num of current remote matched writers. */
	uint16_t current_count;

	/* The change of current_count since last listener is called. */
	int16_t current_count_change;
};

struct reader_deadline_missed_status {
	/*
	 * Missed deadlines accumulate, that is, each deadline period the
	 * total_count will be incremented by 1
	 */
	uint8_t total_count;
};

struct reader_listener {
	/*
	 * This method to be called when the subscriber is matched with a new Writer (or unmatched);
	 */
	void (*on_matched)(struct reader *r, struct reader_matched_status *status);

	/*
	 * This method will be implemented by the user containing the actions to be
	 * performed when new Data Messages are received.
	 */
	void (*on_data)(struct reader *r, instance_id id);

	/*
	 * This method will be called on when this topic data received in
	 * interrupt.
	 */
	void (*on_irq)(struct reader *r, void *data);

	/*
	 * Method called when abnormal information is reproted in e2e.
	 */
	void (*on_e2e_exception)(struct reader *r, int64_t sn, uint32_t e2e_status);

	/*
	 * Method to be called when a topic misses the deadline period
	 */
	void (*on_deadline_missed)(struct reader *r,
				   struct reader_deadline_missed_status *status);
#if 0
	/*
	 * Method called an incompatible QoS was requested.
	 */
	void (*on_requested_incompatible_qos)(struct reader *r, void *param);

	/*
	 * Method called when a sample was rejected.
	 */
	void (*on_sample_rejected)(struct reader *r, void *param);

	/*
	 * Method called when a sample was lost.
	 */
	void (*on_sample_lost)(struct reader *r, void *param);

	/*
	 * Method called when the liveliness status associated to a subscriber changes
	 */
	void (*on_liveliness_changed)(struct reader *r, void *param);
#endif
};

struct reader_attr {
	const char			*key;
	const struct type_plugin	*type;
	struct participant		*ptcp;

	struct endpoint_attr		ep_attr;
	uint16_t			max_matched_writers;	//define the size for writerproxy
	
	struct reader_listener		listener;
};

const char *reader_get_topicname(const struct reader *r);
const char *reader_get_typename(const struct reader *r);

struct sample_info {
	struct mvbs_entity_info		info_src;
	struct mvbs_e2e_info		info_e2e;
	struct rtps_sn			sn_info;
	LocatorKind_t			locator_kind;
};

bool reader_get_instance_sample(struct reader *r, instance_id id,
				uint8_t *buffer, uint16_t dest_size,
				struct sample_info *info, bool take);

bool reader_get_sample(struct reader *r, uint8_t *buffer, uint16_t dest_size,
					struct sample_info *info, bool take);

int32_t reader_get_status(struct reader *r, struct mvbs_endpoint_stat *stats);
size_t reader_get_onlinepeers(struct reader *r, struct mvbs_entity_info *peer,
								    size_t n);

void reader_set_private(struct reader *r, void *priv_data);
void *reader_get_private(struct reader *r);

const struct reader_listener *reader_listener_setup(struct reader *r,
					      const struct reader_listener *l);

#ifdef __MVBS_CORE_SOURCE__
#include <mvbs/core/types.h>
#include <mvbs/core/entities/participant.h>
#include <mvbs/core/history/history_cache.h>
#include <mvbs/utils/mem_pool.h>

#define MVBS_READER_STATE_RECORD

struct e2e_header;
struct reader_data;
struct writer_proxy;
struct reader_cache_change;

struct reader {
	const struct reader_attr		*attr;

	struct mem_pool				proxies;
	struct history_cache			history;

	struct writer_proxy			*owner;

	timer_desc_t				lifespan_td;
	timer_desc_t				deadline_td;
	timer_desc_t				liveliness_td;

	uint8_t					liveliness_status : 2;
	uint8_t					auto_liveliness_status : 2;
	uint8_t					record_mode:2;

#if defined (MVBS_READER_STATE_RECORD)
	uint16_t				total_matched_count;

	uint16_t				matched_count;
	int16_t					matched_count_change;

	uint8_t					deadline_missed_count;

	/* reject number, cache_change arrive (Qos nomatch, deser fail) */
	uint8_t					rejected_sample;

	uint8_t					committed_sample;

	/* Undelivered count, cache_change not arrive (Gap, HeartBeat, no mem) */
	uint32_t				lost_sample;
#endif
	const struct reader_listener		*listener;

	void					*priv_data;
};

static inline struct reader *ptcp_get_reader_by_index(const struct participant *ptcp, uint16_t index)
{
	if (ptcp == NULL) {
		return NULL;
	}

	if (index >= ptcp->attr->reader_num) {
		return NULL;
	}

	return ptcp->attr->readers + index;
}

#define foreach_ptcp_reader(ptcp, r)			\
	for (int ri_ = 0; (r = ptcp_get_reader_by_index(ptcp, ri_)); ri_++)

#define foreach_reader_proxy(reader, proxy)		\
	foreach_mempool_avail_data(&reader->proxies, proxy)

static inline participant_t *reader_get_ptcp(const struct reader *r)
{
	return r->attr->ptcp;
}

static inline const char *reader_printable_topicname(const struct reader *r)
{
	if ((r == NULL) || (r->attr == NULL)) {
		return "NULL";
	}

	return r->attr->ep_attr.topic_name;
}

static inline struct mem_pool *reader_get_cc_pool(struct reader *r)
{
	if (r == NULL) {
		return NULL;
	}

	return &r->history.cache_change;
}

static inline uint16_t reader_get_onlinepeers_num(struct reader *r)
{
	return mem_pool_total_blk_cnt(&r->proxies)
		- mem_pool_free_blk_cnt(&r->proxies);
}

static inline int32_t reader_topicname_equal(const struct reader *r,
					     const char *topicname)
{
	return mvbs_strcmp(r->attr->ep_attr.topic_name, topicname);
}

static inline int32_t reader_typename_equal(const struct reader *r,
					    const char *type_name)
{
	return mvbs_strcmp(r->attr->type->name, type_name);
}

static inline int32_t reader_key_equal(const struct reader *r,
				       const char *key)
{
	return mvbs_strcmp(r->attr->key, key);
}

static inline bool reader_has_key(const struct reader *r)
{
	(void)r;

	return false;
}

static inline uint8_t reader_get_entity_kind(const struct reader *r)
{
	(void)r;

	return USER_DEFINED_READER_WITHOUT_KEY;
}

static inline struct rtps_entity_id reader_get_eid(const struct reader *r)
{
	struct rtps_entity_id eid;

	eid.entity_kind   = reader_get_entity_kind(r);

	rtps_entity_id_set_key(&eid, r->attr->ep_attr.entity_id);

	return eid;
}

static inline struct rtps_guid_prefix *reader_get_prefix(struct reader *r)
{
	struct participant *ptcp;

	ptcp = reader_get_ptcp(r);

	return &ptcp->guid_prefix;
}

static inline bool reader_eid_equal(struct reader *r,
				    const struct rtps_entity_id *id)
{
	struct rtps_entity_id eid;

	eid = reader_get_eid(r);

	return rtps_entity_id_equal(&eid, id);
}

static inline bool reader_e2e_enabled(const struct reader *r)
{
	return !!r->attr->ep_attr.e2e.e2e_protection;
}

static inline bool reader_is_periodic(const struct reader *r)
{
	return r->attr->ep_attr.period_ms != 0;
}

static inline bool reader_has_no_proxies(struct reader *r)
{
	return mem_pool_has_not_avail_data(&r->proxies);
}

static inline uint16_t reader_get_index(struct reader *r)
{
	return mp_get_blk_data_idx((void *)r);
}

static inline const duration_t *reader_get_deadline_duration(struct reader *r)
{
	return &(r->attr->ep_attr.deadline.duration);
}

static inline const duration_t *reader_get_lifespan_duration(struct reader *r)
{
	return &(r->attr->ep_attr.lifespan.duration);
}

static inline const duration_t *reader_get_liveliness_duration(struct reader *r)
{
	return &(r->attr->ep_attr.liveliness.lease_duration);
}

static inline bool reader_liveliness_duration_is_infinite(struct reader *r)
{
	const duration_t *liveliness;

	liveliness = reader_get_lifespan_duration(r);

	return duration_is_infinite(liveliness);
}

static inline uint16_t reader_get_reliability_kind(const struct reader *r)
{
	return r->attr->ep_attr.qos.reliability_kind;
}

static inline uint16_t reader_get_history_kind(const struct reader *r)
{
	return r->attr->ep_attr.qos.history_kind;
}

static inline uint16_t reader_get_ownership_kind(const struct reader *r)
{
	return r->attr->ep_attr.qos.ownership_kind;
}

static inline uint16_t reader_get_liveliness_kind(const struct reader *r)
{
	return r->attr->ep_attr.qos.liveliness_kind;
}

static inline uint16_t reader_get_durability_kind(const struct reader *r)
{
	return r->attr->ep_attr.qos.durability_kind;
}

static inline const char *reader_get_crc16(struct reader *r)
{
	if (!r->attr->ep_attr.crc16_enabled)
		return "";

	return r->attr->type->crc16;
}

/* Return this type data max size after serialized */
static inline uint32_t reader_get_type_size(struct reader *r)
{
	return r->attr->type->type_size();
}

static inline bool reader_data_deserialize(struct reader *r, void *data,
					   struct serialized_payload *payload)
{
	return r->attr->type->deserialize(data, payload);
}

bool reader_match_ep_info(struct reader *r, const endpoint_info_t *info);

int32_t reader_init(struct reader *r);
void reader_deinit(struct reader *r);

void reader_ownership_update(struct reader *r, struct writer_proxy *proxy,
							    bool on_line);

bool reader_add_proxy(struct reader *r, struct writer_proxy *new_proxy);
void reader_del_writer(struct reader *r, struct rtps_guid *writer_guid);

struct writer_proxy *reader_get_proxy(struct reader *r,
				 const struct participant_proxy *ptcp_proxy,
				 struct rtps_entity_id id);

bool reader_remove_proxy(struct reader *r,
			 const struct participant_proxy *ptcp_proxy,
			 struct rtps_entity_id id);

void reader_remove_proxies_with_ptcp(struct reader *r,
			     struct participant_proxy *ptcp_proxy);

bool reader_on_new_heartbeat(struct reader *r,
			     struct submessage_heartbeat *msg,
			     const struct participant_proxy *ptcp_proxy);

bool reader_on_new_gap(struct reader *r, struct submessage_gap *msg,
		       const struct participant_proxy *ptcp_proxy);

bool reader_on_new_e2e(const struct submessage_e2e sub_msg,
		       struct e2e_header *header_src);

void reader_on_new_data(struct reader *r, struct reader_data *data);

struct reader_cache_change *reader_append_new_change(struct reader *r,
				struct reader_data *data, instance_id *inst_id);

#if defined (MVBS_READER_STATE_RECORD)
/* reader.matched_count */

static inline void reader_matched_increase(struct reader *r)
{
	r->total_matched_count++;

	r->matched_count++;

	r->matched_count_change++;
}

static inline void reader_matched_decrease(struct reader *r)
{
	r->matched_count--;

	r->matched_count_change--;
}

static inline uint16_t reader_get_total_matched_count(struct reader *r)
{
	return r->total_matched_count;
}

static inline uint16_t reader_get_matched_count(struct reader *r)
{
	return r->matched_count;
}

static inline int16_t reader_get_matched_count_change(struct reader *r)
{
	return r->matched_count_change;
}

static inline void reader_reset_matched_change_count(struct reader *r)
{
	r->matched_count_change = 0;
}

static inline uint8_t reader_get_deadline_missed_count(struct reader *r)
{
	return r->deadline_missed_count;
}

static inline void reader_deadline_missed_count_increase(struct reader *r)
{
	r->deadline_missed_count++;
}

static inline uint8_t reader_get_lost_sample(struct reader *r)
{
	return r->lost_sample;
}

static inline void reader_lost_sample_increase(struct reader *r)
{
	r->lost_sample++;
}

static inline void reader_lost_sample_add_value(struct reader *r, uint8_t value)
{
	r->lost_sample += value;
}

static inline uint8_t reader_get_committed_sample(struct reader *r)
{
	return r->committed_sample;
}

static inline void reader_committed_sample_increase(struct reader *r)
{
	r->committed_sample++;
}

static inline uint8_t reader_get_rejected_sample(struct reader *r)
{
	return r->rejected_sample;
}

static inline void reader_rejected_sample_increase(struct reader *r)
{
	r->rejected_sample++;
}

#else

static inline void reader_matched_increase(struct reader *r)
{
	(void)r;
}

static inline void reader_matched_decrease(struct reader *r)
{
	(void)r;
}

static inline uint16_t reader_get_total_matched_count(struct reader *r)
{
	(void)r;
	return 0U;
}

static inline uint16_t reader_get_matched_count(struct reader *r)
{
	(void)r;
	return 0U;
}

static inline int16_t reader_get_matched_count_change(struct reader *r)
{
	(void)r;
	return 0;
}

static inline void reader_reset_matched_change_count(struct reader *r)
{
	(void)r;
}

static inline uint8_t reader_get_deadline_missed_count(struct reader *r)
{
	(void)r;
	return 0U;
}

static inline void reader_deadline_missed_count_increase(struct reader *r)
{
	(void)r;
}

static inline uint8_t reader_get_lost_sample(struct reader *r)
{
	(void)r;
	return 0U;
}

static inline void reader_lost_sample_increase(struct reader *r)
{
	(void)r;
}

static inline void reader_lost_sample_add_value(struct reader *r, uint8_t value)
{
	(void)r;
	(void)value;
}

static inline uint8_t reader_get_committed_sample(struct reader *r)
{
	(void)r;
	return 0U;
}

static inline void reader_committed_sample_increase(struct reader *r)
{
	(void)r;
}

static inline uint8_t reader_get_rejected_sample(struct reader *r)
{
	(void)r;
	return 0U;
}

static inline void reader_rejected_sample_increase(struct reader *r)
{
	(void)r;
}

#endif

static inline void sedp_update_sub_matched_status(struct reader *r, bool match)
{

	if (r == NULL) {
		pr_err(ERR_INVALID, "Invaild parameter.\n");
		return;
	}

	if (match) {
		reader_matched_increase(r);
	} else {
		reader_matched_decrease(r);
	}
}

static inline void sedp_reset_sub_matched_status(struct reader *r)
{
	if (r == NULL) {
		pr_err(ERR_INVALID, "Invaild parameter.\n");
		return;
	}

	reader_reset_matched_change_count(r);
}

static inline void reader_on_subscription_matched(struct reader *r, bool match)
{
	struct reader_matched_status status;

	if (r == NULL) {
		return ;
	}

	sedp_update_sub_matched_status(r, match);

	if (r->attr->listener.on_matched != NULL) {
		status.current_count        = reader_get_matched_count(r);
		status.current_count_change = reader_get_matched_count_change(r);

		r->attr->listener.on_matched(r, &status);
	}

	sedp_reset_sub_matched_status(r);
}

static inline void reader_on_data_available(struct reader *r, instance_id id)
{
	if (r == NULL) {
		return ;
	}

	if (r->attr->listener.on_data == NULL) {
		return ;
	}

	r->attr->listener.on_data(r, id);
}

static inline void reader_on_requested_deadline_missed(struct reader *r)
{
	struct reader_deadline_missed_status	deadline_status;

	if (r == NULL) {
		return ;
	}

	reader_deadline_missed_count_increase(r);

	if (r->attr->listener.on_deadline_missed == NULL) {
		return ;
	}

	deadline_status.total_count = reader_get_deadline_missed_count(r);

	r->attr->listener.on_deadline_missed(r, &deadline_status);
}

static inline void reader_on_e2e_exception(struct reader *r,
					int64_t sn, uint32_t e2e_status)
{
	if (r == NULL) {
		return ;
	}

	if (r->attr->listener.on_e2e_exception == NULL) {
		return ;
	}

	r->attr->listener.on_e2e_exception(r, sn, e2e_status);
}

static inline void reader_record_entrance_enable(struct reader *r)
{
	r->record_mode = 1;
}

static inline void reader_record_export_enable(struct reader *r)
{
	r->record_mode = 2;
}

static inline void reader_record_disable(struct reader *r)
{
	r->record_mode = 0;
}

static inline void reader_record_set(struct reader *r, const uint8_t mode)
{
	r->record_mode = mode;
}

static inline uint8_t reader_record_has_enabled(struct reader *r)
{
	return r->record_mode;
}

#endif

#endif
