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

#ifndef MVBS_CORE_ENTITIES_PARTICIPANT_H
#define MVBS_CORE_ENTITIES_PARTICIPANT_H

#include <mvbs/base_type.h>
#include <mvbs/rtps/guid.h>
#include <mvbs/core/qos/qos.h>
#include <mvbs/core/transport/transport.h>

struct participant;
struct participant_proxy;

struct endpoint_attr;
struct endpoint_info;

struct reader;
struct reader_attr;

struct writer;
struct writer_attr;

#define DYNAMIC_EDP    0U
#define STATIC_EDP     1U

struct participant_attr {
	char	name[64];

	uint8_t	domain_id;

	/* 1. Maximum number of each resource */
	uint8_t max_readers;
	uint8_t max_writers;

	uint8_t max_timers;
	uint8_t max_proxies;

	size_t	max_topic_size;

	/* 2. Configuration of Transport */
	struct transport_info	trans_info;

	/* 3. Configuration for Discovery */
	struct {
		duration_t	lease_duration;
		duration_t	lease_duration_announce_period;
		duration_t	initial_announce_period;
		uint16_t	initial_announce_count;

		uint16_t	edp_type;

		struct	heartbeat_policy	hb_policy;
	} discovery;

	/* 4. Configuration of Endpoints */
	uint8_t				reader_num;
	uint8_t				writer_num;

	uint8_t				static_reader_num;
	uint8_t				static_writer_num;

	const struct reader_attr	*reader_attrs;
	const struct writer_attr	*writer_attrs;

	const struct endpoint_attr	*static_reader_attrs;
	const struct endpoint_attr	*static_writer_attrs;

	/* 5. Entities list */
	struct reader			*readers;
	struct writer			*writers;

	/* 6. Configuration of preferred remote participant list */
	size_t preferred_list_num;
	const char * const * const	preferred_list;
};

typedef struct participant_attr		participant_attr_t;

struct writer *ptcp_get_writer_with_eid(struct participant *ptcp,
				      struct rtps_entity_id id);
struct writer *ptcp_get_writer_with_rproxy(struct participant *ptcp,
				const struct participant_proxy *ptcp_proxy,
				struct rtps_entity_id writer_eid);

struct writer *ptcp_get_writer_with_topic(const struct participant *ptcp,
				       const char *topicname);
struct writer *ptcp_get_writer_with_type(struct participant *ptcp,
					   const char *type_name);
struct writer *ptcp_get_writer_with_key(struct participant *ptcp,
				      const char *key);

struct reader *ptcp_get_reader_with_eid(struct participant *ptcp,
				      struct rtps_entity_id id);
struct reader *ptcp_get_reader_with_wproxy(struct participant *ptcp,
				const struct participant_proxy *ptcp_proxy,
				struct rtps_entity_id id);

struct reader *ptcp_get_reader_with_topic(const struct participant *ptcp,
				       const char *topicname);
struct reader *ptcp_get_reader_with_type(struct participant *ptcp,
					   const char *type_name);
struct reader *ptcp_get_reader_with_key(struct participant *ptcp,
				      const char *key);

struct writer *ptcp_create_writer(struct participant *ptcp,
				  const struct writer_attr *attr);
struct reader *ptcp_create_reader(struct participant *ptcp,
				  const struct reader_attr *attr);

bool ptcp_remove_writer(struct participant *ptcp, struct writer *w);
bool ptcp_remove_reader(struct participant *ptcp, struct reader *r);

int32_t ptcp_discovery_init(struct participant *ptcp);
int32_t ptcp_discovery_start(struct participant *ptcp);
int32_t ptcp_discovery_stop(struct participant *ptcp);

int32_t ptcp_enable(struct participant *ptcp);

int32_t ptcp_init(struct participant *ptcp, const participant_attr_t *attr);
void ptcp_deinit(struct participant *ptcp);

struct participant *ptcp_create(const participant_attr_t *attr);
bool ptcp_destroy(struct participant *ptcp);

/* The following are some prototype of weak function */
void ptcp_proxy_on_change(const struct participant_proxy *ptcp_proxy, bool online);

void ptcp_remote_reader_on_change(const struct participant_proxy *ptcp_proxy,
				  const struct endpoint_info *ep_info);

void ptcp_remote_writer_on_change(const struct participant_proxy *ptcp_proxy,
				  const struct endpoint_info *ep_info);

void ptcp_remote_guid_on_offline(const struct participant_proxy *ptcp_proxy,
				 const struct rtps_guid *guid);

#ifdef __MVBS_CORE_SOURCE__
#include <mvbs/utils/mem_pool.h>
#include <mvbs/utils/timer.h>
#include <mvbs/rtps/discovery.h>
#include <mvbs/core/types.h>
#include <mvbs/core/entities/ep_attr.h>
#include <mvbs/core/entities/participant_proxy.h>
#include <mvbs/core/discovery/buildin_proxy.h>
#include <mvbs/core/transport/transport.h>
#include <mvbs/core/transport/locator.h>

struct participant {
	const struct participant_attr	*attr;

	struct rtps_guid_prefix		guid_prefix;
	struct rtps_time		start_time;
	uint64_t			session_id;

	struct mem_pool			writers;
	struct mem_pool			readers;
	struct mem_pool			proxies;
	struct mem_pool			remote_locators;
	struct mem_pool			timers;

	struct transport		*ptransport;

	/* Store temp result of pdp message parsing */
	struct participant_proxy	*pdp_received;

	uint32_t			timer_period_us;
	struct mvbs_timer_wheel		timer_wheel;

	timer_desc_t			pdp_announce_td;

	timer_desc_t			pub_writer_hb_td;
	timer_desc_t			sub_writer_hb_td;
	timer_desc_t			p2p_writer_hb_td;

	uint32_t			pub_writer_hb_count;
	uint32_t			sub_writer_hb_count;
	uint32_t			p2p_writer_hb_count;

	struct wlp {
		struct rtps_sn		writer_sn;

		timer_desc_t		auto_td;	/* for AUTOMATIC announcement */
		timer_desc_t		ptcp_td;	/* for PARTICIPANT announcement */

		int16_t			auto_timer_refcnt;
		int16_t			ptcp_timer_refcnt;

		uint32_t		min_auto_ms;	/* AUTOMATIC announcement delivery period */
		uint32_t		min_ptcp_ms;	/* PARTICIPANT announcement delivery period */

		struct instance_handle	auto_instance_handle;
		struct instance_handle	ptcp_instance_handle;
	} wlp_handler;

	struct participant_proxy	*recorder_proxy;
	struct rtps_sn			diag_request_sn;/* for diag request writer */
	struct rtps_sn			diag_reply_sn;	/* for diag reply writer */

	struct discovery_pdp		*pdp_template;	
	struct discovery_edp		*edp_template;	

	struct rtps_property_info	property;

	uint8_t				announce_count;
	uint8_t				id;		/* participant id */

	bool				boost;

	bool				inited;
	bool				started;

	bool				dpde_inited;
	bool				dpse_inited;

	bool				dpde_started;
	bool				dpse_started;
};

typedef struct participant		participant_t;

#define foreach_ptcp_proxy(ptcp, proxy)			\
	foreach_mempool_avail_data(&ptcp->proxies, proxy)

static inline participant_t *ptcp_proxy_get_ptcp(const participant_proxy_t *proxy)
{
	const struct mem_pool	*ptcp_proxy_pool;

	ptcp_proxy_pool = mp_get_mp_from_blk_data(proxy);

	return container_of(ptcp_proxy_pool, struct participant, proxies);
}

static inline uint8_t ptcp_get_samples_before_hb(const participant_t *ptcp)
{
	return ptcp->attr->discovery.hb_policy.heartbeats_per_max_samples;
}

static inline uint32_t ptcp_get_session_id_hi(const participant_t *ptcp)
{
	return (ptcp->session_id >> 32) & 0xFFFFFFFF;
}

static inline uint32_t ptcp_get_session_id_lo(const participant_t *ptcp)
{
	return (ptcp->session_id) & 0xFFFFFFFF;
}

static inline bool ptcp_local_transport_enabled(const participant_t *ptcp)
{
	if (ptcp->attr->trans_info.ipc_j6m != NULL) {
		return false;
	}

	/* FIXME: Currently, local transport depends on UDP transport */
	return ptcp->attr->trans_info.local_comm != NULL;
}

static inline uint8_t ptcp_local_locator_count(const participant_t *ptcp)
{
	if (ptcp->attr->trans_info.ipc_j6m != NULL) {
		return (uint8_t)1U;
	}

	/* FIXME:
	 * Currently, if IPC transport hasn't enabled, udp transport must be
	 * enabled.
	 */
	return (uint8_t)ptcp->attr->trans_info.udp->info_cnt;
}

const uint8_t *ptcp_locator_udp_ipaddr(participant_t *ptcp, uint32_t index);

static inline locator_t *ptcp_remote_locator_alloc(participant_t *ptcp)
{
	void *p_locator;

	if (ptcp == NULL) {
		return NULL;
	}

	p_locator = mem_pool_alloc(&ptcp->remote_locators);

	return (locator_t *)p_locator;
}

static inline void ptcp_remote_locator_free(locator_t *p_locator)
{
	mem_pool_free(p_locator);
}

static inline struct reader *ptcp_reader_alloc(participant_t *ptcp)
{
	void *r;

	if (ptcp == NULL) {
		return NULL;
	}

	r = mem_pool_alloc(&ptcp->readers);

	return (struct reader *)r;
}

static inline void ptcp_reader_free(struct reader *r)
{
	mem_pool_free(r);
}

static inline struct writer *ptcp_writer_alloc(participant_t *ptcp)
{
	void *w;

	if (ptcp == NULL) {
		return NULL;
	}

	w = mem_pool_alloc(&ptcp->writers);

	return (struct writer *)w;
}

static inline void ptcp_writer_free(struct writer *w)
{
	mem_pool_free(w);
}

static inline bool ptcp_detect_master_link(participant_t *ptcp, locator_t *loc)
{
	struct transport *trans;

	if (ptcp == NULL) {
		return false;
	}

	trans = ptcp->ptransport;

	if (trans == NULL) {
		return false;
	}

	if (trans->detect_master_link == NULL) {
		return false;
	}

	return trans->detect_master_link(trans, loc);
}

static inline int32_t ptcp_detect_reachable(participant_t *ptcp, locator_t *loc)
{
	struct transport *trans;

	if (ptcp == NULL) {
		return false;
	}

	trans = ptcp->ptransport;

	if (trans == NULL) {
		return false;
	}

	if (trans->detect_reachable == NULL) {
		return false;
	}

	return trans->detect_reachable(trans, loc);
}

const locator_t *ptcp_get_builtin_multicast(participant_t *ptcp);

bool ptcp_detect_preferred_proxy(participant_t *ptcp,
				 participant_proxy_t *proxy);

/*
 * Internal users use the interface
 */
struct reader *ptcp_get_matching_reader(participant_t *ptcp,
					const endpoint_info_t *info);
struct writer *ptcp_get_matching_writer(participant_t *ptcp,
					const endpoint_info_t *info);

participant_proxy_t *ptcp_get_proxy_with_name(participant_t *ptcp,
						       char *ptcp_name);
participant_proxy_t *ptcp_get_proxy_with_guid_prefix(participant_t *ptcp,
					   struct rtps_guid_prefix *prefix);

static inline void ptcp_proxy_free(participant_proxy_t *proxy)
{
	mem_pool_free(proxy);
}

participant_proxy_t *ptcp_proxy_create(participant_t *ptcp, bool force);
void ptcp_proxy_destroy(participant_proxy_t *proxy);

void ptcp_proxy_liveliness_reset(participant_proxy_t *ptcp_proxy);
bool ptcp_proxy_liveliness_enable(participant_proxy_t *ptcp_proxy);

static inline participant_proxy_t *ptcp_duplicate_proxy(participant_t *ptcp,
							participant_proxy_t *proxy)
{
	participant_proxy_t *new_proxy;

	new_proxy = ptcp_proxy_create(ptcp, (proxy->preferred != 0U));
	if (new_proxy == NULL) {
		pr_err(ERR_NOMEM, "Failed to add new participant as resource limit\n");
		return NULL;
	}

	mvbs_memcpy(new_proxy, proxy, ptcp->proxies.blk_size);

	return new_proxy;
}

const endpoint_attr_t *ptcp_find_static_remote_reader(participant_t *ptcp,
						int16_t user_id);
const endpoint_attr_t *ptcp_find_static_remote_writer(participant_t *ptcp,
						int16_t user_id);

uint8_t ptcp_get_max_user_writers(const participant_t *ptcp);
uint8_t ptcp_get_max_user_readers(const participant_t *ptcp);

struct mvbs_cdr *ptcp_get_tx_buffer(const participant_t *ptcp);

int32_t ptcp_send_buffer_to(const participant_t *ptcp,
			    const void *buf, size_t length,
			    locator_t *loc, bool link_bakup);

int32_t ptcp_recv_handler(struct participant *ptcp, uint32_t recv_max_pkg);
int32_t ptcp_local_recv_handler(struct participant *ptcp, uint32_t recv_max_pkg);
int32_t ptcp_timer_handler(struct participant *ptcp);

#endif
#endif
