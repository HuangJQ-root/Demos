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
#include <mvbs/utils/time.h>
#include <mvbs/utils/log.h>
#include <mcdr/mcdr.h>
#include <discovery/sddp.h>
#include <discovery/sedp_agent.h>
#include <messages/message_factory.h>
#include "sedp.h"

#if SEDP_VERBOSE || RTPS_GLOBAL_VERBOSE
#undef MVBSLOG_LEVEL
#define MVBSLOG_LEVEL MVBSLOG_VERB
#endif

/*
 * TBD
 * 1. Must less equal to SNS_NUM_BITS
 * 2. It is best to be a multiple of 5, because 5
 *    EDP messages in mvbs exactly constitute one package.
 */
#define EDP_REQUEST_MAX_NUMBER		10

extern const struct buildin_reader dpde_readers[];
extern const struct buildin_writer dpde_writers[];

#pragma weak ptcp_remote_reader_on_change
void ptcp_remote_reader_on_change(const struct participant_proxy *ptcp_proxy,
				  const struct endpoint_info *ep_info)
{
	(void)ptcp_proxy;
	(void)ep_info;
}

#pragma weak ptcp_remote_writer_on_change
void ptcp_remote_writer_on_change(const struct participant_proxy *ptcp_proxy,
				  const struct endpoint_info *ep_info)
{
	(void)ptcp_proxy;
	(void)ep_info;
}

#pragma weak ptcp_remote_guid_on_offline
void ptcp_remote_guid_on_offline(const struct participant_proxy *ptcp_proxy,
				 const struct rtps_guid *guid)
{
	(void)ptcp_proxy;
	(void)guid;
}

static bool cdr_serialize_append_edp(struct mvbs_cdr *cdr,
				     const struct participant *ptcp,
				     const struct endpoint_attr *attr,
				     struct rtps_entity_id eid,
				     const struct rtps_entity_id *sender,
				     const struct rtps_entity_id *receiver,
				     struct rtps_sn sn)
{
	bool ret = true;
	struct mvbs_cdr cdr_bak;

	mcdr_copy_buffer(&cdr_bak, cdr);

	/* INFO_TS submessage */
	ret = rtps_msg_add_submsg_timestamp(&cdr_bak, &ptcp->start_time);
	if (!ret) {
		return ret;
	}

	/* DATA submessage */
	ret = rtps_msg_add_submsg_data_sedp_edp(&cdr_bak, sender, receiver,
						sn, ptcp, attr, eid);
	if (!ret) {
		return ret;
	}

	mcdr_copy_buffer(cdr, &cdr_bak);

	return ret;
}

void sedp_do_local_match(struct participant_proxy *ptcp_proxy,
			 struct writer *w, struct reader *r)
{
	struct writer_proxy *wproxy = NULL;
	struct reader_proxy *rproxy = NULL;

	struct rtps_entity_id	r_eid;
	struct rtps_entity_id	w_eid;

	uint8_t	durability;
	bool	reliable;

	if ((w == NULL) || (r == NULL)) {
		return ;
	}

	w_eid = writer_get_eid(w);
	r_eid = reader_get_eid(r);

	wproxy = writer_proxy_alloc(r);
	if (wproxy == NULL) {
		pr_err(ERR_NOMEM, "Fail to alloc writer proxy.\n");
		return;
	}

	rproxy = reader_proxy_alloc(w);
	if (rproxy == NULL) {
		pr_err(ERR_NOMEM, "Fail to alloc reader proxy.\n");

		writer_proxy_free(wproxy);
		return;
	}

	writer_proxy_init(wproxy, ptcp_proxy, w_eid,
			  w->attr->ep_attr.ownership_strength.value);

	if (!reader_add_proxy(r, wproxy)) {
		pr_warn("Failed to add new match writer.\n");

		writer_proxy_free(wproxy);
		reader_proxy_free(rproxy);

		return ;
	}

	reader_ownership_update(r, wproxy, true);

	reader_on_subscription_matched(r, true);

	reliable = r->attr->ep_attr.qos.reliability_kind == (uint16_t)RELIABLE;
	durability = (uint8_t)r->attr->ep_attr.qos.durability_kind;

	reader_proxy_init(rproxy, ptcp_proxy, r_eid, reliable, durability);

	writer_on_publication_matched(w, true);
}

void sedp_remove_remote_writer(struct participant *ptcp,
			       struct participant_proxy *ptcp_proxy,
			       struct rtps_entity_id writer_eid)
{
	struct reader	*r = NULL;

	if ((ptcp == NULL) && (ptcp_proxy == NULL)) {
		return ;
	}

	foreach_ptcp_reader(ptcp, r) {
		if (reader_remove_proxy(r, ptcp_proxy, writer_eid)) {
			return ;
		}
	}

	pr_err(ERR_NOENT, "Fail to find the writer_proxy with this id.\n");
}

void sedp_remove_remote_reader(struct participant *ptcp,
			       const struct participant_proxy *ptcp_proxy,
			       struct rtps_entity_id reader_eid)
{
	struct writer	*w = NULL;

	if ((ptcp == NULL) && (ptcp_proxy == NULL)) {
		return ;
	}

	foreach_ptcp_writer(ptcp, w) {
		if (writer_remove_proxy(w, ptcp_proxy, reader_eid)) {
			return ;
		}
	}

	pr_err(ERR_NOENT, "Fail to find the reader_proxy with this id.\n");
}

int32_t sedp_add_writer(struct participant *ptcp, struct writer *w, int16_t idx)
{
	uint8_t			writer_kind;

	(void)(idx);

	if ((ptcp == NULL) || (w == NULL)) {
		pr_err(ERR_INVALID, "Invalid parameter.\n");
		return -ERR_INVALID;
	}

	writer_kind	= writer_get_entity_kind(w);

	if ((writer_kind == (uint8_t)BUILD_IN_WRITER_WITH_KEY) ||
	    (writer_kind == (uint8_t)BUILD_IN_WRITER_WITHOUT_KEY)) {
		return 0;
	}

	pr_verb("Added new change to sedpPubWriter.\n");

	return 0;
}

int32_t sedp_add_reader(struct participant *ptcp, struct reader *r, int16_t idx)
{
	uint8_t			reader_kind;

	(void)(idx);

	if ((ptcp == NULL) || (r == NULL)) {
		pr_err(ERR_INVALID, "Invalid parameter.\n");
		return -ERR_INVALID;
	}

	reader_kind	= reader_get_entity_kind(r);

	if ((reader_kind == (uint8_t)BUILD_IN_READER_WITH_KEY) ||
	    (reader_kind == (uint8_t)BUILD_IN_READER_WITHOUT_KEY)) {
		return 0;
	}

	pr_verb("Added new change to sedp_pubwriter.\n");

	return 0;
}

static bool cdr_serialize_append_offline_edp(struct mvbs_cdr *cdr,
				     const struct rtps_entity_id *sender,
				     const struct rtps_entity_id *receiver,
				     struct rtps_sn sn,
				     struct rtps_guid_prefix *guid,
				     struct rtps_entity_id  offline_eid)
{
	struct rtps_time	offline_time;
	struct mvbs_cdr		cdr_bak;
	bool ret = true;

	mcdr_copy_buffer(&cdr_bak, cdr);

	mvbs_get_time(&offline_time.seconds, &offline_time.nanosec);

	/* INFO_TS submessage */
	ret = rtps_msg_add_submsg_timestamp(&cdr_bak, &offline_time);
	if (!ret) {
		return ret;
	}

	/* DATA submessage */
	ret = rtps_msg_add_submsg_data_sedp_offline_edp(&cdr_bak, sender,
					receiver, sn, guid, offline_eid);
	if (!ret) {
		return ret;
	}

	mcdr_copy_buffer(cdr, &cdr_bak);

	return ret;
}

bool sedp_delete_writer(struct participant *ptcp, struct writer *w)
{
	static struct rtps_sn sn = {
		.high = -1,
		.low  = 0U,
	};

	struct mvbs_cdr		*cdr;
	struct reader_proxy	*proxy;
	struct rtps_entity_id	subwriter_eid;
	struct rtps_entity_id	subreader_eid;
	locator_t		*loc;
	bool ret = true;

	if ((ptcp == NULL) || (w == NULL)) {
		pr_err(ERR_INVALID, "Invaild parameter.\n");
		return false;
	}

	subwriter_eid = ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER;
	subreader_eid = ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER;

	cdr  = ptcp_get_tx_buffer(ptcp);
#if 0
	/* The EDP Cache Change has been removed. */
	ret = writer_del_cache(psedp->buildin_eps.sedp_pubwriter,
			pwriter->sedp_seq_num);
	if (!ret) {
		pr_err(ERR_FAULT, "Delete writer cache failed\n");
		return false;
	}
#endif

	if (rtps_sn_equal(&sn, &RTPS_SN_UNKNOWN)) {
		rtps_sn_set_value(&sn,
				(int64_t)ptcp_get_max_user_writers(ptcp));
	}

	rtps_sn_increase(&sn);

	mcdr_reset_buffer(cdr);

	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

	ret = cdr_serialize_append_offline_edp(cdr,
				&subwriter_eid, &subreader_eid, sn,
				&ptcp->guid_prefix, writer_get_eid(w));
	if (!ret) {
		return false;
	}

	foreach_writer_proxy(w, proxy) {
#if 1	/* unicast */
		loc = ptcp_proxy_get_meta_uc_loc(proxy->ptcp_proxy);
#else	/* multicast */
		loc = ptcp_proxy_get_meta_mc_loc(proxy->ptcp_proxy);
#endif
		(void)ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
						mcdr_buffer_length(cdr),
						loc, false);
	}

	return true;
}

bool sedp_delete_reader(struct participant *ptcp, struct reader *r)
{
	/* FIXME: SEQUENCENUMBER_UNKNOWN */
	static struct rtps_sn sn = {
		.high = -1,
		.low  = 0U,
	};

	struct mvbs_cdr		*cdr;
	struct rtps_entity_id	subwriter_eid;
	struct rtps_entity_id	subreader_eid;
	struct writer_proxy	*proxy;
	locator_t		*loc;
	bool ret = true;

	if ((ptcp == NULL) || (r == NULL)) {
		pr_err(ERR_INVALID, "Invaild parameter.\n");
		return false;
	}

	subwriter_eid = ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER;
	subreader_eid = ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER;

	cdr  = ptcp_get_tx_buffer(ptcp);
#if 0
	/* The EDP Cache Change has been removed. */
	ret = writer_del_cache(psedp->buildin_eps.sedp_subwriter,
						preader->sedp_seq_num);
	if (!ret) {
		pr_err(ERR_FAULT, "Delete reader cache failed\n");
		return false;
	}
#endif
	if (rtps_sn_equal(&sn, &RTPS_SN_UNKNOWN)) {
		rtps_sn_set_value(&sn,
				(int64_t)ptcp_get_max_user_readers(ptcp));
	}

	rtps_sn_increase(&sn);

	mcdr_reset_buffer(cdr);

	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

	ret = cdr_serialize_append_offline_edp(cdr,
				&subwriter_eid, &subreader_eid, sn,
				&ptcp->guid_prefix, reader_get_eid(r));
	if (!ret) {
		return false;
	}

	foreach_reader_proxy(r, proxy) {
#if 1	/* unicast */
		loc = ptcp_proxy_get_meta_uc_loc(proxy->ptcp_proxy);
#else	/* multicast */
		loc = ptcp_proxy_get_meta_mc_loc(proxy->ptcp_proxy);
#endif
                (void)ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
						mcdr_buffer_length(cdr),
						loc, false);
	}

	return true;
}

#if 0
static void sddp_pub_all_subscriber(const struct participant *ptcp,
				    locator_t *loc, bool backup_enabled)
{
	struct rtps_entity_id	subwriter_eid;
	struct rtps_entity_id	subscriber_eid;
	struct mvbs_cdr		*cdr;
	struct reader		*r;
	struct rtps_sn	sn;

	size_t	 length = 0;
	uint16_t index = 0;
	bool	 ret = false;

	subwriter_eid  = ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER;
	subscriber_eid = ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER;

	cdr = ptcp_get_tx_buffer(ptcp);
	mcdr_reset_buffer(cdr);

	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

	foreach_ptcp_reader(ptcp, r) {
		index++;

		rtps_sn_set_value(&sn, (int64_t)index);

		ret = cdr_serialize_append_edp(cdr, ptcp, &r->attr->ep_attr,
					       reader_get_eid(r),
					       &subwriter_eid, &subscriber_eid, sn);
		if (!ret) {
			(void)ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
						length, loc, backup_enabled);

			mcdr_reset_buffer(cdr);

			(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

			ret = cdr_serialize_append_edp(cdr, ptcp,
					&r->attr->ep_attr, reader_get_eid(r),
					&subwriter_eid, &subscriber_eid, sn);
		}

		length = mcdr_buffer_length(cdr);
	}

	if (ret) {
		(void)ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
						mcdr_buffer_length(cdr),
						loc, backup_enabled);
	}
}

static void sddp_pub_all_publisher(const struct participant *ptcp,
				   locator_t *loc, bool backup_enabled)
{
	struct rtps_entity_id	w_eid;
	struct rtps_entity_id	r_eid;
	struct mvbs_cdr		*cdr;
	struct writer		*w;
	struct rtps_sn	sn;

	size_t	 length = 0;
	uint16_t index = 0;
	bool	 ret = false;

	w_eid = ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER;
	r_eid = ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER;

	cdr = ptcp_get_tx_buffer(ptcp);
	mcdr_reset_buffer(cdr);

	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

	foreach_ptcp_writer(ptcp, w) {
		index++;

		rtps_sn_set_value(&sn, (int64_t)index);

		ret = cdr_serialize_append_edp(cdr, ptcp, &w->attr->ep_attr,
					       writer_get_eid(w),
					       &w_eid, &r_eid, sn);
		if (!ret) {
			(void)ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
						length, loc, backup_enabled);

			mcdr_reset_buffer(cdr);

			(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

			ret = cdr_serialize_append_edp(cdr, ptcp,
					&w->attr->ep_attr, writer_get_eid(w),
					&w_eid, &r_eid, sn);
		}

		length = mcdr_buffer_length(cdr);
	}

	if (ret) {
		(void)ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
						mcdr_buffer_length(cdr),
						loc, backup_enabled);
	}
}
#endif

static void sedp_new_pub_process(struct participant *ptcp,
				 participant_proxy_t *ptcp_proxy,
				 const struct endpoint_info *ep_info)
{
	struct writer_proxy *wproxy;
	struct reader *r;

	pr_debug("Remote Writer: %s/%s", string_or_null(ep_info->topic_name),
					 string_or_null(ep_info->type_name));

	r = ptcp_get_matching_reader(ptcp, ep_info);
	if (r == NULL) {
		pr_debug("Fail to find a matched reader [%s, %s]",
					string_or_null(ep_info->topic_name),
					string_or_null(ep_info->type_name));

		return;
	}

	wproxy = reader_get_proxy(r, ptcp_proxy, ep_info->ep_guid.eid);
	if (wproxy != NULL) {
		pr_debug("%s: %s:" ENTITY_ID_FMT " has already matched",
						reader_get_topicname(r),
						wproxy->ptcp_proxy->ptcp_name,
						ENTITY_ID_PARTS(wproxy->eid));
		return;
	}

	wproxy = writer_proxy_alloc(r);
	if (wproxy == NULL) {
		pr_err(ERR_NOMEM, "[%s] Fail to alloc writer proxy.",
						reader_get_topicname(r));
		return;
	}

	writer_proxy_init(wproxy, ptcp_proxy, ep_info->ep_guid.eid,
					      ep_info->ownership_strength);

	if (!reader_add_proxy(r, wproxy)) {
		writer_proxy_free(wproxy);

		pr_err(ERR_FAULT, "[%s] Failed to add new match writer.",
						reader_get_topicname(r));
		return ;
	}

	pr_debug("%s: has new wproxy: %s:" ENTITY_ID_FMT,
					reader_get_topicname(r),
					wproxy->ptcp_proxy->ptcp_name,
					ENTITY_ID_PARTS(wproxy->eid));

	reader_ownership_update(r, wproxy, true);

	reader_on_subscription_matched(r, true);
}

static void sedp_new_sub_process(struct participant *ptcp,
				 participant_proxy_t *ptcp_proxy,
				 const endpoint_info_t *ep_info)
{
	const struct rtps_guid	*id;
	struct reader_proxy	*rproxy;
	struct writer		*w;

	bool reliable;

	pr_debug("Remote Reader: %s/%s", string_or_null(ep_info->topic_name),
					 string_or_null(ep_info->type_name));

	w = ptcp_get_matching_writer(ptcp, ep_info);
	if (w == NULL) {
		pr_debug("Fail to find a matched writer [%s, %s]",
					string_or_null(ep_info->topic_name),
					string_or_null(ep_info->type_name));
		return;
	}

	id = &ep_info->ep_guid;

	rproxy = writer_get_proxy(w, ptcp_proxy, id->eid);
	if (rproxy != NULL) {
		pr_debug("%s: %s:" ENTITY_ID_FMT " has already matched",
						writer_get_topicname(w),
						rproxy->ptcp_proxy->ptcp_name,
						ENTITY_ID_PARTS(rproxy->eid));
		return;
	}

	rproxy = reader_proxy_alloc(w);
	if (rproxy == NULL) {
		pr_err(ERR_NOMEM, "[%s] Fail to alloc reader proxy.",
						writer_get_topicname(w));
		return;
	}

	reliable = ep_info->qos.reliability_kind == (uint16_t)RELIABLE;

	reader_proxy_init(rproxy, ptcp_proxy, id->eid, reliable,
				(uint8_t)ep_info->qos.durability_kind);

	writer_add_proxy(w, rproxy);

	pr_debug("%s: has new rproxy: %s:" ENTITY_ID_FMT,
					writer_get_topicname(w),
					rproxy->ptcp_proxy->ptcp_name,
					ENTITY_ID_PARTS(rproxy->eid));

	writer_on_publication_matched(w, true);
}



static void remove_remote_writer(participant_t *ptcp, endpoint_info_t *info)
{
	struct rtps_guid *guid;
	participant_proxy_t *ptcp_proxy;

	guid = &info->guid_from_key_hash;

	ptcp_proxy = ptcp_get_proxy_with_guid_prefix(ptcp, &guid->prefix);
	if (ptcp_proxy == NULL) {
		pr_err(ERR_NOENT, "Fail to find ptcp_proxy with this id.");
		return ;
	}

	sedp_remove_remote_writer(ptcp, ptcp_proxy, guid->eid);
}

void pub_reader_on_data(const struct buildin_reader *r,
			struct participant_proxy *ptcp_proxy,
			const struct submessage_data *msg,
			const struct submessage_data_extra *extra)
{
	participant_proxy_t	*proxy;
	struct participant	*ptcp;
	struct rtps_guid	guid;
	struct endpoint_info	ep_info;
	struct mvbs_cdr		cdr;

	uint32_t		status_info;
	bool			ret;

	locator_t 		*loc = NULL;

	(void)r;
	/*
	 * In DServer Protocal, 'ptcp_proxy' represent DServer
	 */
	if (buildin_writer_proxy_test_sn(&ptcp_proxy->sddp_proxies.pub_reader,
					 &msg->writer_sn)) {
		return ;
	}

	ptcp = extra->ptcp;

	pr_debug("offline reader, ptcp proxy name = %s",proxy->ptcp_name);

	mcdr_init_buffer(&cdr, extra->data, extra->size);

	if ((msg->header.flags & (uint8_t)FLAG_INLINE_QOS) != 0U) {
		status_info = cdr_deserialize_inlineqos(&cdr, &guid);
		proxy = ptcp_get_proxy_with_guid_prefix(ptcp, &guid.prefix);
		if (status_info != 0) {
			pr_debug("offline reader, ptcp proxy name = %s",proxy->ptcp_name);

			ptcp_remote_guid_on_offline(proxy, &guid);

			sedp_remove_remote_writer(ptcp, proxy, guid.eid);
		}

		/*
	 	 * In DServer: 'ptcp_proxy' represents Dserver
		 * 	Update the bitmap of the Dserver proxy when receiving
		 *	the writer offline message
		 * In MVBS: 'ptcp_proxy' == other participant ('proxy')
		 * 	Update the bitmap of the normal proxy when receiving
		 *	the writer offline message
		 */
		buildin_writer_proxy_set_sn(
			&ptcp_proxy->sddp_proxies.pub_reader, &msg->writer_sn);

		if (mcdr_buffer_remaining(&cdr) <= 0) {
			return ;
		}
	}

	msg_deser_config_opts(&cdr);

	mvbs_memzero((void *)&ep_info, sizeof(ep_info));

	/* EDP shouldn't be sent by local buffer */
	ret = sedp_edp_deserialize(&cdr, &ep_info, ptcp);
	if (!ret) {
		pr_verb("Fail to deserialize EDP of remote writer.");
		return;
	}


	proxy = ptcp_get_proxy_with_guid_prefix(ptcp, &ep_info.ep_guid.prefix);
	if (proxy == NULL) {
		pr_err(ERR_NOENT, "Fail to find ptcp proxy of EDP.");

		return;
	}

	pr_debug("DATA(r) : rtps hdr proxy name = %s",ptcp_proxy->ptcp_name);
	pr_debug("DATA(r) : payload proxy name = %s",proxy->ptcp_name);

	ptcp_remote_writer_on_change(proxy, &ep_info);

	if (ep_info.status_info > 0u) {
		pr_debug("remove_remote_writer, ptcp proxy name = %s",proxy->ptcp_name);
		remove_remote_writer(ptcp, &ep_info);
		return;
	}

	loc = ptcp_proxy_get_user_uc_loc(proxy);
	if (!locator_has_valid_kind(&ep_info.uc)) {
		return;
	} else {
		if (ptcp_proxy_is_dserver(ptcp_proxy)) {
			mvbs_memcpy(loc, &ep_info.uc, sizeof(*loc));
		}
	}

	sedp_new_pub_process(ptcp, proxy, &ep_info);

	/*
	 * Update RTPS hdr proxy's bitmap in DServer
	 */
	pr_debug("[%s]'s proxy [%s]: update bitmap", r->name, proxy->ptcp_name);
	buildin_writer_proxy_set_sn(&ptcp_proxy->sddp_proxies.pub_reader,
							&msg->writer_sn);

#if 0
	buildin_writer_proxy_refine(&proxy->sddp_proxies.pub_reader);
#endif
}

static void remove_remote_reader(participant_t *ptcp, endpoint_info_t *info)
{
	struct rtps_guid *guid;
	participant_proxy_t *ptcp_proxy;

	guid = &info->guid_from_key_hash;

	ptcp_proxy = ptcp_get_proxy_with_guid_prefix(ptcp, &guid->prefix);
	if (ptcp_proxy == NULL) {
		pr_err(ERR_NOENT, "Fail to find ptcp_proxy with this id.");
		return ;
	}

	sedp_remove_remote_reader(ptcp, ptcp_proxy, guid->eid);
}

void sub_reader_on_data(const struct buildin_reader *r,
			struct participant_proxy *ptcp_proxy,
			const struct submessage_data *msg,
			const struct submessage_data_extra *extra)
{
	participant_proxy_t	*proxy;
	struct participant	*ptcp;
	struct endpoint_info	ep_info;
	struct mvbs_cdr		cdr;
	struct rtps_guid	guid;
	uint32_t		status_info;
	bool			ret;
	locator_t 		*loc = NULL;

	(void)r;
	(void)ptcp_proxy;
	(void)msg;

	if (buildin_writer_proxy_test_sn(&ptcp_proxy->sddp_proxies.sub_reader,
					 &msg->writer_sn)) {
		return ;
	}

	ptcp = extra->ptcp;

	mcdr_init_buffer(&cdr, extra->data, extra->size);

	if ((msg->header.flags & (uint8_t)FLAG_INLINE_QOS) != 0U) {
		status_info = cdr_deserialize_inlineqos(&cdr, &guid);

		/*
		 * proxy should search by deserialized info
		 */
		proxy = ptcp_get_proxy_with_guid_prefix(ptcp, &guid.prefix);

		if (status_info != 0) {
			pr_debug("offline reader, ptcp proxy name = %s",proxy->ptcp_name);
			ptcp_remote_guid_on_offline(proxy, &guid);

			sedp_remove_remote_reader(ptcp, proxy, guid.eid);
		}

		/*
	 	 * In DServer: 'ptcp_proxy' represents Dserver
		 * 	Update the bitmap of the Dserver proxy when receiving
		 *	the reader offline message
		 * In MVBS: 'ptcp_proxy' == other participant ('proxy')
		 * 	Update the bitmap of the normal proxy when receiving
		 *	the reader offline message
		 */
		buildin_writer_proxy_set_sn(
			&ptcp_proxy->sddp_proxies.sub_reader, &msg->writer_sn);

		if (mcdr_buffer_remaining(&cdr) <= 0) {
			return ;
		}
	}

	msg_deser_config_opts(&cdr);

	mvbs_memzero((void *)&ep_info, sizeof(ep_info));

	/* EDP shouldn't be sent by local buffer */
	ret = sedp_edp_deserialize(&cdr, &ep_info, ptcp);
	if (!ret) {
		pr_verb("Fail to deserialize EDP of remote reader.");
		return;
	}

	proxy = ptcp_get_proxy_with_guid_prefix(ptcp, &ep_info.ep_guid.prefix);
	if (proxy == NULL) {
		pr_err(ERR_NOENT, "Fail to find ptcp proxy of EDP.");
		return;
	}

	pr_debug("DATA(r) : rtps hdr proxy name = %s",ptcp_proxy->ptcp_name);
	pr_debug("DATA(r) : payload proxy name = %s",proxy->ptcp_name);

	ptcp_remote_reader_on_change(proxy, &ep_info);

	if (ep_info.status_info > 0U) {
		pr_debug("remove_remote_reader, ptcp proxy name = %s",proxy->ptcp_name);
		remove_remote_reader(ptcp, &ep_info);
		return;
	}

	loc = ptcp_proxy_get_user_uc_loc(proxy);
	if (!locator_has_valid_kind(&ep_info.uc)) {
		return;
	} else {
		if (ptcp_proxy_is_dserver(ptcp_proxy)) {
			mvbs_memcpy(loc, &ep_info.uc, sizeof(*loc));
		}
	}

	sedp_new_sub_process(ptcp, proxy, &ep_info);

	/*
	 * Update RTPS hdr proxy's bitmap in DServer
	 */
	pr_debug("[%s]'s proxy [%s]: update bitmap", r->name, proxy->ptcp_name);
	buildin_writer_proxy_set_sn(&ptcp_proxy->sddp_proxies.sub_reader,
							&msg->writer_sn);
}

/*
 * To simplify the built-in nodes:
 * start_sn is the first one.
 * avail_bits indicates how many topics there are.
 * recv_map represents the parts that have not been received after start_sn.
 */
void pub_reader_on_heartbeat(const struct buildin_reader *r,
				    struct participant_proxy *ptcp_proxy,
				    const struct submessage_heartbeat *msg)
{
	struct buildin_writer_proxy *proxy;
	uint64_t first_sn;
	uint64_t last_sn;

	proxy = &ptcp_proxy->sddp_proxies.pub_reader;

	if (msg->msg_count <= proxy->heartbeat_count) {
		return;
	}

	proxy->heartbeat_count = msg->msg_count;

	first_sn = rtps_sn_to_int64(&msg->first_sn);
	last_sn  = rtps_sn_to_int64(&msg->last_sn);

	pr_debug(" --> %s: Get a heartbeat: %d:%d", r->name,
			(uint32_t)first_sn, (uint32_t)last_sn);

	if (first_sn - 1 == last_sn) {
		proxy->avail_bits = 0;

		proxy->start_sn = (uint16_t)last_sn;

		return ;
	}

	if (proxy->avail_bits != 0) {
		if (last_sn < proxy->start_sn + proxy->avail_bits) {
			pub_reader_send_acknack(ptcp_proxy, EDP_REQUEST_MAX_NUMBER);
			return ;
		}
	}

	proxy->start_sn   = (uint16_t)first_sn;

	if (proxy->avail_bits < last_sn - first_sn + 1) {
		proxy->avail_bits = last_sn - first_sn + 1;
	}

	pr_debug("%s: update the writer proxy: %d:%d",
			r->name, (uint32_t)proxy->start_sn, proxy->avail_bits);

	pub_reader_send_acknack(ptcp_proxy, EDP_REQUEST_MAX_NUMBER);

	return;
}

void sub_reader_on_heartbeat(const struct buildin_reader *r,
				    struct participant_proxy *ptcp_proxy,
				    const struct submessage_heartbeat *msg)
{
	struct buildin_writer_proxy *proxy;
	uint64_t first_sn;
	uint64_t last_sn;

	proxy = &ptcp_proxy->sddp_proxies.sub_reader;

	if (msg->msg_count <= proxy->heartbeat_count) {
		return;
	}

	proxy->heartbeat_count = msg->msg_count;

	first_sn = rtps_sn_to_int64(&msg->first_sn);
	last_sn  = rtps_sn_to_int64(&msg->last_sn);

	pr_debug(" --> %s: Get a heartbeat: %d:%d", r->name,
			(uint32_t)first_sn, (uint32_t)last_sn);

	if (first_sn - 1 == last_sn) {
		proxy->avail_bits = 0;

		proxy->start_sn = (uint16_t)last_sn;

		return ;
	}

	if (proxy->avail_bits != 0) {
		if (last_sn < proxy->start_sn + proxy->avail_bits) {
			sub_reader_send_acknack(ptcp_proxy,
						EDP_REQUEST_MAX_NUMBER);
			return ;
		}
	}

	proxy->start_sn   = (uint16_t)first_sn;

	if (proxy->avail_bits < last_sn - first_sn + 1) {
		proxy->avail_bits = last_sn - first_sn + 1;
	}

	pr_debug("ptcp proxy: %s -> writer: %s update startSN: %d, availbits: %d",
		ptcp_proxy->ptcp_name, r->name, (uint32_t)proxy->start_sn,
		proxy->avail_bits);

	sub_reader_send_acknack(ptcp_proxy, EDP_REQUEST_MAX_NUMBER);

	return ;
}

void pub_writer_on_acknack(const struct buildin_writer *bw,
				  struct participant_proxy *ptcp_proxy,
				  const struct submessage_acknack *msg)
{
	const struct rtps_entity_id	*w_eid;
	const struct rtps_entity_id	*r_eid;

	struct buildin_reader_proxy	*proxy;
	struct participant		*ptcp;
	struct mvbs_cdr			*cdr;
	struct writer			*w;
	locator_t			*loc;

	struct rtps_sn			sn;

	uint32_t	i = 0;
	int64_t		base_sn = 0;
	bool		ret = false;

	/* Step1: Filter out invalid ACKNACK package */
	proxy = &ptcp_proxy->sddp_proxies.pub_writer;

	if (msg->msg_count <= proxy->acknack_count) {
		pr_debug("%s: Recv ACK CNT: %d, Last ACK CNT: %d",
						bw->name, msg->msg_count,
						proxy->acknack_count);
		return;
	}

	proxy->acknack_count = msg->msg_count;

	/* Step2: Preemptive ACK Handle */
	if (msg_acknack_is_preemtive(msg)) {
		pr_debug("%s: Recv preemptive ack, send heartbeat", bw->name);

		pub_writer_send_hearbeat(ptcp_proxy, false);

		return ;
	}

	/* Step3: Re-send out lost package. */
	w_eid = &bw->eid;
	r_eid = &bw->remote_eid;

	ptcp  = ptcp_proxy_get_ptcp(ptcp_proxy);
	cdr   = ptcp_get_tx_buffer(ptcp);

	pr_debug(" --> %s: send EDP data to %s", bw->name, ptcp_proxy->ptcp_name);
#if 0
	rtps_sn_set_dump(&msg->reader_sn_state);
#endif

	base_sn = rtps_sn_to_int64(&msg->reader_sn_state.base);
	loc     = ptcp_proxy_get_meta_uc_loc(ptcp_proxy);

	mcdr_reset_buffer(cdr);

	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

	for (i=0; i < msg->reader_sn_state.num_bits; i++) {
		/* 0 bit indicate its related package has been received */
		if (!rtps_sn_set_is_valid(&msg->reader_sn_state, i)) {
			continue;
		}

		/* 1 bit indicate its related package should be re-send */
		rtps_sn_set_value(&sn, base_sn + i);

		w = ptcp_get_writer_by_index(ptcp, base_sn + i - 1);
		if (w == NULL) {
			pr_err(ERR_FAULT, "Fail to get writer of %d", base_sn + i - 1);
			break;
		}

		pr_verb("SN: %d, TopicName: %s", base_sn+i, writer_get_topicname(w));

		ret = cdr_serialize_append_edp(cdr, ptcp, &w->attr->ep_attr,
					       writer_get_eid(w),
					       w_eid, r_eid, sn);

		if (!ret) {
			(void)ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
						mcdr_buffer_length(cdr), loc,
						bw->backup_link_enabled);

			mcdr_reset_buffer(cdr);
			(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

			ret = cdr_serialize_append_edp(cdr, ptcp,
					&w->attr->ep_attr, writer_get_eid(w),
					w_eid, r_eid, sn);
		}
	}

	if (ret) {
		(void)ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
						mcdr_buffer_length(cdr), loc,
						bw->backup_link_enabled);

		pub_writer_send_hearbeat(ptcp_proxy, false);
	}

	return ;
}

void sub_writer_on_acknack(const struct buildin_writer *bw,
			   struct participant_proxy  *ptcp_proxy,
			   const struct submessage_acknack *msg)
{
	const struct rtps_entity_id	*w_eid;
	const struct rtps_entity_id	*r_eid;

	struct buildin_reader_proxy	*proxy;
	struct participant		*ptcp;
	struct mvbs_cdr			*cdr;
	struct reader			*r;
	locator_t			*loc;

	struct rtps_sn			sn;

	uint32_t	i = 0;
	int64_t		base_sn = 0;
	bool		ret = false;

	/* Step1: Filter out invalid ACKNACK package */
	proxy = &ptcp_proxy->sddp_proxies.sub_writer;

	if (msg->msg_count <= proxy->acknack_count) {
		pr_debug("%s: Recv ACK CNT: %d, Last ACK CNT: %d",
						bw->name, msg->msg_count,
						proxy->acknack_count);
		return;
	}

	proxy->acknack_count = msg->msg_count;

	/* Step2: Preemptive ACK Handle */
	if (msg_acknack_is_preemtive(msg)) {
		pr_debug("%s: Recv preemptive ack, send heartbeat", bw->name);

		sub_writer_send_hearbeat(ptcp_proxy, false);

		return ;
	}

	/* Step3: Re-send out lost package. */
	w_eid = &bw->eid;
	r_eid = &bw->remote_eid;

	ptcp  = ptcp_proxy_get_ptcp(ptcp_proxy);
	cdr   = ptcp_get_tx_buffer(ptcp);

	pr_debug(" <<< %s: send EDP data to %s", bw->name, ptcp_proxy->ptcp_name);
#if 0
	rtps_sn_set_dump(&msg->reader_sn_state);
#endif

	base_sn = rtps_sn_to_int64(&msg->reader_sn_state.base);
	loc	= ptcp_proxy_get_meta_uc_loc(ptcp_proxy);

	mcdr_reset_buffer(cdr);

	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

	for (i=0; i < msg->reader_sn_state.num_bits; i++) {
		/* 0 bit indicate its related package has been received */
		if (!rtps_sn_set_is_valid(&msg->reader_sn_state, i)) {
			continue;
		}

		/* 1 bit indicate its related package has been lost */
		rtps_sn_set_value(&sn, base_sn + i);

		r = ptcp_get_reader_by_index(ptcp, base_sn + i - 1);
		if (r == NULL) {
			pr_err(ERR_FAULT, "Fail to get reader of %d", base_sn + i - 1);
			break;
		}

		pr_verb("SN: %d, TopicName: %s", base_sn+i, reader_get_topicname(r));

		ret = cdr_serialize_append_edp(cdr, ptcp, &r->attr->ep_attr,
					       reader_get_eid(r),
					       w_eid, r_eid, sn);

		if (!ret) {
			(void)ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
						mcdr_buffer_length(cdr), loc,
						bw->backup_link_enabled);

			mcdr_reset_buffer(cdr);
			(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

			ret = cdr_serialize_append_edp(cdr, ptcp,
					&r->attr->ep_attr, reader_get_eid(r),
					w_eid, r_eid, sn);
		}
	}

	if (ret) {
		(void)ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
						mcdr_buffer_length(cdr), loc,
						bw->backup_link_enabled);

		sub_writer_send_hearbeat(ptcp_proxy, false);
	}

	return ;
}

void pub_writer_send_hearbeat(const struct participant_proxy *ptcp_proxy,
							bool liveliness)
{
	struct rtps_sn			first_sn;
	struct rtps_sn			last_sn;
	struct participant		*ptcp = NULL;
	struct mvbs_cdr			*cdr;
	const struct buildin_writer	*w;
	locator_t			*loc;
	/* struct buildin_reader_proxy	*proxy; */
	uint8_t				max_writers;
	int32_t				ret = 0;

	if (!ptcp_proxy_has_pub_reader(ptcp_proxy)) {
		return ;
	}

	ptcp	    = ptcp_proxy_get_ptcp(ptcp_proxy);
	max_writers = ptcp_get_max_user_writers(ptcp);

	w	    = &dpde_writers[PUB_WRITER];
	/* proxy	    = &ptcp_proxy->sddp_proxies.pub_writer; */

	cdr	    = ptcp_get_tx_buffer(ptcp);
	loc	    = ptcp_proxy_get_meta_uc_loc(ptcp_proxy);

	rtps_sn_set_value(&first_sn, 1);
	rtps_sn_set_value(&last_sn, (int64_t)max_writers);

	mcdr_reset_buffer(cdr);

	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

	(void)rtps_msg_add_submsg_heartbeat(cdr, &w->remote_eid, &w->eid,
					    first_sn, last_sn,
					    ptcp->pub_writer_hb_count,
					    liveliness);

	ret = ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
				  mcdr_buffer_length(cdr),
				  loc, w->backup_link_enabled);

	pr_debug("%s: send heartbeat to %s", w->name, ptcp_proxy->ptcp_name);

	if (ret == 0) {
		ptcp->pub_writer_hb_count++;
	} else {
		pr_err(ret, "%s: Fail to send heartbeat to %s.", w->name,
							ptcp_proxy->ptcp_name);
	}
}

void sub_writer_send_hearbeat(const struct participant_proxy *ptcp_proxy,
							     bool liveliness)
{
	struct rtps_sn			first_sn;
	struct rtps_sn			last_sn;
	const struct buildin_writer	*w;
	struct mvbs_cdr			*cdr;
	locator_t			*loc;
	struct participant		*ptcp = NULL;
	/* struct buildin_reader_proxy	*proxy; */
	uint8_t				max_readers;
	int32_t				ret = 0;

	if (!ptcp_proxy_has_sub_reader(ptcp_proxy)) {
		return ;
	}

	ptcp	    = ptcp_proxy_get_ptcp(ptcp_proxy);
	max_readers = ptcp_get_max_user_readers(ptcp);

	w	    = &dpde_writers[SUB_WRITER];
	/* proxy	    = &ptcp_proxy->sddp_proxies.pub_writer; */

	cdr	    = ptcp_get_tx_buffer(ptcp);
	loc	    = ptcp_proxy_get_meta_uc_loc(ptcp_proxy);

	rtps_sn_set_value(&first_sn, 1);
	rtps_sn_set_value(&last_sn, (int64_t)max_readers);

	mcdr_reset_buffer(cdr);

	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

	(void)rtps_msg_add_submsg_heartbeat(cdr, &w->remote_eid, &w->eid,
					    first_sn, last_sn,
					    ptcp->sub_writer_hb_count,
					    liveliness);

	ret = ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
				  mcdr_buffer_length(cdr),
				  loc, w->backup_link_enabled);

	pr_debug("%s: send heartbeat to %s", w->name, ptcp_proxy->ptcp_name);

	if (ret == 0) {
		ptcp->sub_writer_hb_count++;
	} else {
		pr_err(ret, "%s: Fail to send heartbeat to %s.", w->name,
							ptcp_proxy->ptcp_name);
	}
}

#if 0
static void sddp_writer_send_gap(const struct buildin_writer *w,
				 const struct participant_proxy *ptcp_proxy)
{
	(void)w;
	(void)ptcp_proxy;
}
#endif

/*
 * sample_cnt:
 * 0x0000: Send preemptive ACK
 * 0xFFFF: Request all package
 * ......:
 */
void pub_reader_send_acknack(struct participant_proxy  *ptcp_proxy,
						uint16_t sample_cnt)
{
	const struct buildin_reader	*r;
	struct rtps_sn_set		set = {0};
	struct participant		*ptcp  = NULL;
	struct mvbs_cdr			*cdr   = NULL;
	struct buildin_writer_proxy	*proxy = NULL;
	locator_t			*loc   = NULL;

	int32_t		ret;
	uint16_t	count;

	if (!ptcp_proxy_has_pub_writer(ptcp_proxy)) {
		return ;
	}

	loc	= ptcp_proxy_get_meta_uc_loc(ptcp_proxy);
	r	= &dpde_readers[PUB_READER];
	proxy	= &ptcp_proxy->sddp_proxies.pub_reader;

	if (sample_cnt == 0) {
		rtps_sn_set_value(&set.base, 0);

		set.num_bits = 0;

		pr_debug("[%s] send preemptive acknack to [%s]", r->name,
							ptcp_proxy->ptcp_name);
	} else {
		count = buildin_writer_proxy_to_sn_set(proxy, &set, sample_cnt);

		pr_debug("[%s] request %d samples from [%s]", r->name, count,
							ptcp_proxy->ptcp_name);
		if (count == 0) {
			return;
		}
	}

	ptcp = ptcp_proxy_get_ptcp(ptcp_proxy);
	cdr  = ptcp_get_tx_buffer(ptcp);

	mcdr_reset_buffer(cdr);

	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

	(void)rtps_msg_add_submsg_acknack(cdr, &r->remote_eid, &r->eid, &set,
					       proxy->acknack_count, false);

	ret = ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
				  mcdr_buffer_length(cdr), loc,
				  r->backup_link_enabled);

	if (ret < 0) {
		pr_err(ret, "transport send acknack failed(%d)", ret);
	} else {
		proxy->acknack_count++;
	}
}

void sub_reader_send_acknack(struct participant_proxy  *ptcp_proxy,
						uint16_t sample_cnt)
{
	const struct buildin_reader	*r;
	struct rtps_sn_set		set;
	struct participant		*ptcp  = NULL;
	struct mvbs_cdr			*cdr   = NULL;
	struct buildin_writer_proxy	*proxy = NULL;
	locator_t			*loc   = NULL;

	int32_t		ret;
	uint16_t	count;

	if (!ptcp_proxy_has_sub_writer(ptcp_proxy)) {
		return ;
	}

	loc	= ptcp_proxy_get_meta_uc_loc(ptcp_proxy);
	r	= &dpde_readers[SUB_READER];
	proxy	= &ptcp_proxy->sddp_proxies.sub_reader;

	if (sample_cnt == 0) {
		rtps_sn_set_value(&set.base, 0);

		set.num_bits = 0;

		pr_debug("[%s] send preemptive acknack to [%s]", r->name,
							ptcp_proxy->ptcp_name);
	} else {
		count = buildin_writer_proxy_to_sn_set(proxy, &set, sample_cnt);

		pr_debug("[%s] request %d samples from [%s]", r->name, count,
							ptcp_proxy->ptcp_name);
		if (count == 0) {
			return;
		}
	}

	ptcp = ptcp_proxy_get_ptcp(ptcp_proxy);
	cdr  = ptcp_get_tx_buffer(ptcp);

	mcdr_reset_buffer(cdr);

	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);
	(void)rtps_msg_add_submsg_acknack(cdr, &r->remote_eid, &r->eid, &set,
					       proxy->acknack_count, false);

	ret = ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
				  mcdr_buffer_length(cdr), loc,
				  r->backup_link_enabled);

	if (ret < 0) {
		pr_err(ret, "transport send acknack failed(%d)", ret);
	} else {
		proxy->acknack_count++;
	}
}

void pub_writer_on_ptcp_online(const struct buildin_writer *w,
				struct participant *ptcp,
				struct participant_proxy *ptcp_proxy)
{
	(void)w;
	(void)ptcp;

	if (!ptcp_proxy_has_pub_reader(ptcp_proxy)) {
		return;
	}

	buildin_reader_proxy_init(&ptcp_proxy->sddp_proxies.pub_writer,
						true, TRANSIENT_LOCAL);
#if 0
	pr_debug("%s: send all writer edp to %s", w->name, ptcp_proxy->ptcp_name);

	sddp_pub_all_publisher(ptcp, ptcp_proxy_get_meta_uc_loc(ptcp_proxy),
						w->backup_link_enabled);
#endif

	pub_writer_send_hearbeat(ptcp_proxy, false);

	return;
}

void sub_writer_on_ptcp_online(const struct buildin_writer *w,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy)
{
	(void)w;
	(void)ptcp;

	if (!ptcp_proxy_has_sub_reader(ptcp_proxy)) {
		return;
	}

	buildin_reader_proxy_init(&ptcp_proxy->sddp_proxies.sub_writer,
						true, TRANSIENT_LOCAL);

#if 0
	pr_debug("%s: send all reader edp to %s", w->name, ptcp_proxy->ptcp_name);

	sddp_pub_all_subscriber(ptcp, ptcp_proxy_get_meta_uc_loc(ptcp_proxy),
						w->backup_link_enabled);
#endif

	sub_writer_send_hearbeat(ptcp_proxy, false);

	return;
}

void pub_reader_on_ptcp_online(const struct buildin_reader *r,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy)
{
	(void)r;
	(void)ptcp;

	if (!ptcp_proxy_has_pub_writer(ptcp_proxy)) {
		return;
	}

	buildin_writer_proxy_init(&ptcp_proxy->sddp_proxies.pub_reader);

	/*
	 * Mechanism Update: A preemptive ACK will now be sent only if
	 * no heartbeat is received from remote peer. So, the following
	 * operation has been removed.
	 */
#if 0
	pub_reader_send_acknack(ptcp_proxy, 0);
#endif
	return;
}

void sub_reader_on_ptcp_online(const struct buildin_reader *r,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy)
{
	(void)r;
	(void)ptcp;

	if (!ptcp_proxy_has_sub_writer(ptcp_proxy)) {
		return;
	}

	buildin_writer_proxy_init(&ptcp_proxy->sddp_proxies.sub_reader);

        /*
	 * Mechanism Update: A preemptive ACK will now be sent only if
	 * no heartbeat is received from remote peer. So, the following
	 * operation has been removed.
         */
#if 0
	sub_reader_send_acknack(ptcp_proxy, 0);
#endif

	return;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
