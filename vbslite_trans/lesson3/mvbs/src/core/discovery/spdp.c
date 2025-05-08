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
#include <mvbs/utils/timer.h>
#include <mvbs/utils/log.h>
#include <messages/message_factory.h>
#include <discovery/dpse.h>
#include <discovery/sddp.h>

#if SPDP_VERBOSE || RTPS_GLOBAL_VERBOSE
#undef MVBSLOG_LEVEL
#define MVBSLOG_LEVEL MVBSLOG_VERB
#endif

static bool cdr_serialize_append_pdp(struct mvbs_cdr *cdr,
				     struct participant *ptcp,
				     const struct rtps_entity_id *sender,
				     const struct rtps_entity_id *receiver,
				     struct rtps_sn sn,
				     struct rtps_property *property,
				     int32_t propty_cnt)
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
	ret = rtps_msg_add_submsg_data_spdp_pdp(&cdr_bak, sender, receiver, sn,
						ptcp, property, propty_cnt);
	if (!ret) {
		return ret;
	}

	mcdr_copy_buffer(cdr, &cdr_bak);

	return ret;
}

void ptcp_spdp_writer_send_pdp(struct participant *ptcp,
			       struct participant_proxy *ptcp_proxy,
			       struct writer *delw, struct reader *delr)
{
	struct mvbs_cdr		*cdr;
	struct rtps_property	*property = NULL;
	struct rtps_entity_id	w_eid;
	struct rtps_entity_id	r_eid;
	struct rtps_sn		sn;
	locator_t loc;

	int32_t prop_cnt = 0, pktnum = 0, i = 0;
	int64_t index = 1;

	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "Invaild parameter.\n");
		return;
	}

	w_eid	= ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER;
	r_eid	= ENTITYID_SPDP_BUILTIN_PARTICIPANT_READER;

	if (ptcp->attr->discovery.edp_type == STATIC_EDP) {
		prop_cnt = static_add_property(ptcp, delw, delr,
					       ptcp->property.property_list);
	}

	do {
		if (((prop_cnt - i) / PROPERTY_COUNT_PERPKT) > 0) {
			pktnum = PROPERTY_COUNT_PERPKT;
		} else {
			pktnum = prop_cnt - i;
		}

		property = &ptcp->property.property_list[i];

		cdr = ptcp_get_tx_buffer(ptcp);
		mcdr_reset_buffer(cdr);

		(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

		rtps_sn_set_value(&sn, (int64_t)index);

		(void)cdr_serialize_append_pdp(cdr, ptcp, &w_eid, &r_eid,
					       sn, property, pktnum);

		if (ptcp_proxy != NULL) {
			loc = *ptcp_proxy_get_meta_uc_loc(ptcp_proxy);
		} else {
			locator_init_meta_multicast(&loc, ptcp->attr->domain_id);
		}

		if (ptcp->attr->trans_info.ipc_j6m != NULL) {
			loc.kind = (uint16_t)LOCATOR_KIND_IPC;
		}

		(void)ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
					mcdr_buffer_length(cdr), &loc, false);

		index++;

		i += pktnum;
	} while (i < prop_cnt);
}

void ptcp_spdp_announce_online(struct participant *ptcp,
				      struct writer *delw, struct reader *delr)
{
	ptcp_spdp_writer_send_pdp(ptcp, NULL, delw, delr);
}

void ptcp_spdp_announce_offline(struct participant *ptcp)
{
	struct mvbs_cdr *cdr;
	locator_t loc;

	cdr = ptcp_get_tx_buffer(ptcp);
	mcdr_reset_buffer(cdr);

	(void)cdr_serialize_spdp_pdp_offline(cdr, ptcp);


	locator_init_meta_multicast(&loc, ptcp->attr->domain_id);
	if (ptcp->attr->trans_info.ipc_j6m  != NULL) {
		loc.kind = (uint16_t)LOCATOR_KIND_IPC;
	}

	(void)ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
				mcdr_buffer_length(cdr), &loc, false);

	if (ptcp_local_transport_enabled(ptcp)) {
		loc.kind = (uint16_t)LOCATOR_KIND_LOCAL;

		(void)ptcp_send_buffer_to(ptcp, mcdr_get_buffer(cdr),
				mcdr_buffer_length(cdr), &loc, false);
	}
}

static void ptcp_spdp_create_ptcp_proxy(struct participant *ptcp,
					struct rtps_property_info *prop_info)
{
	bool ret;
	participant_proxy_t *proxy;

	if ((ptcp == NULL) || (prop_info == NULL)) {
		return;
	}

	if (ptcp_detect_preferred_proxy(ptcp, ptcp->pdp_received)) {
		ptcp->pdp_received->preferred = 1;
	} else {
		ptcp->pdp_received->preferred = 0;
	}

	proxy = ptcp_duplicate_proxy(ptcp, ptcp->pdp_received);
	if (proxy == NULL) {
		return;
	}

        ret = ptcp_proxy_liveliness_enable(proxy);
	if (!ret) {
		pr_err(ERR_FAULT, "Fail to add the new ptcp proxy: %s",
							proxy->ptcp_name);
		ptcp_proxy_free(proxy);

		return;
	}

	if (!ptcp_proxy_is_dclient(ptcp->pdp_received)) {
		if (ptcp->attr->discovery.edp_type == STATIC_EDP) {
			static_assign_remote_endpoints(proxy, prop_info);
		}

		ptcp_spdp_writer_send_pdp(ptcp, proxy, NULL, NULL);

		ptcp_dpde_on_remote_online(ptcp, proxy);
	}

	pr_info("Add new ptcp: %s", proxy->ptcp_name);

	return;
}

static void ptcp_pdp_reader_data_process(struct participant *ptcp,
					 struct rtps_property_info *prop_info,
					 uint32_t status_info)
{
	participant_proxy_t *pdp_received = ptcp->pdp_received;
	participant_proxy_t *proxy;
	bool ret;

#if 0
	ret = spdp_recv_process_local(ptcp, property_info);
	if (ret) {
		return ;
	}
#endif

	/* Handle PDP offline message */
	if (status_info != 0U) {
		proxy = ptcp_get_proxy_with_guid_prefix(ptcp,
						&pdp_received->guid.prefix);

		ptcp_proxy_destroy(proxy);

		return;
	}

	proxy = ptcp_get_proxy_with_name(ptcp, pdp_received->ptcp_name);
	if (proxy != NULL) {
		if (proxy->session_id == pdp_received->session_id) {
			pr_verb("The ptcp already exist: " GUID_PREFIX_FMT,
				GUID_PREFIX_PARTS(pdp_received->guid.prefix.id));

			ptcp_proxy_liveliness_reset(proxy);

			if (ptcp->attr->discovery.edp_type == STATIC_EDP) {
				static_assign_remote_endpoints(proxy, prop_info);
			}

			return;
		} else {
			pr_info("Remote ptcp restart Or Mutiple ptcp with same name: %s", proxy->ptcp_name);

			/* remove the old info and then add the new */
			ptcp_proxy_destroy(proxy);
		}
	}

	ret = ptcp_proxy_update_default_uc_seclotor(pdp_received, ptcp);
	if (!ret) {
		pr_err(ERR_NOENT, "Can not find master subnet locator");
		return;
	}

	ptcp_spdp_create_ptcp_proxy(ptcp, prop_info);
}

static void ptcp_pdp_reader_process_dclient_pdp(struct participant *ptcp,
					 struct rtps_property_info *prop_info,
					 uint32_t status_info)
{
	participant_proxy_t *pdp_received = ptcp->pdp_received;
	participant_proxy_t *proxy = NULL;

	/* Handle PDP offline message */
	if (status_info != 0U) {
		proxy = ptcp_get_proxy_with_guid_prefix(ptcp, &pdp_received->guid.prefix);

		ptcp_proxy_destroy(proxy);

		return;
	}

	proxy = ptcp_get_proxy_with_name(ptcp, pdp_received->ptcp_name);
	if (proxy != NULL) {
		if (proxy->session_id == pdp_received->session_id) {
			pr_verb("The ptcp already exist: " GUID_PREFIX_FMT,
				GUID_PREFIX_PARTS(pdp_received->guid.prefix.id));

			ptcp_proxy_liveliness_reset(proxy);

			return;
		} else {
			pr_info("Remote ptcp restart Or Mutiple ptcp with same name: %s", proxy->ptcp_name);

			/* remove the old info and then add the new */
			ptcp_proxy_destroy(proxy);
		}
	}

	ptcp_spdp_create_ptcp_proxy(ptcp, prop_info);
}

void ptcp_pdp_reader_on_data(const struct buildin_reader *r,
				struct participant_proxy *ptcp_proxy,
				const struct submessage_data *msg,
				const struct submessage_data_extra *extra)
{
	struct participant		*ptcp;
	struct mvbs_cdr			cdr;
	struct rtps_guid		guid;
	struct rtps_property_info	*property;

	locator_t		*loc;

	uint32_t		status_info;
	bool			ret;
	participant_proxy_t	*pproxy;

	(void)r;

#if 0
	/* Currently, DPSE also will reach here for discovery. */
	if (!ptcp->dpde_started) {
		pr_verb("The ptcp [%s] hasn't started.", ptcp->attr->name);
		return;
	}
#endif

	mcdr_init_buffer(&cdr, extra->data, extra->size);

	if ((msg->header.flags & (uint8_t)FLAG_INLINE_QOS) != 0U) {
		status_info = cdr_deserialize_inlineqos(&cdr, &guid);
		pproxy = ptcp_get_proxy_with_guid_prefix(extra->ptcp, &guid.prefix);
		if (status_info != 0) {
			/* FIXME ptcp_proxy should be indicated by guid */
			ptcp_proxy_destroy(pproxy);
		}

		if (mcdr_buffer_remaining(&cdr) <= 0) {
			return ;
		}
	}

	msg_deser_config_opts(&cdr);

	status_info	= 0;
	ptcp		= extra->ptcp;

	property	= &ptcp->property;

	ret = ptcp_proxy_parse(ptcp, ptcp->pdp_received, &cdr, property,
								&status_info);

	/*
	 * FIXME:
	 * DServer will forward the PDP of MVBS to MVBS, to be resolved
	 */
	if (mvbs_strcmp(ptcp->pdp_received->ptcp_name, ptcp->attr->name) == 0 &&
	    rtps_guid_prefix_equal(&ptcp->pdp_received->guid.prefix, &ptcp->guid_prefix)) {
		return;
	}

	if (ptcp_proxy_is_dclient(ptcp->pdp_received)) {
		/*
		 * The PDP message forwarded by the DServer from the DClient has
		 * the GUID of the DServer in the RTPS header, while the PID_PARTICIPANT_GUID
		 * in the payload is that of the DClient. These correspond to ptcp_proxy and
		 * ptcp->pdp_received, respectively.
		 *
		 * DClient pdp has no IPV4 Locator information
		 */
		if (ret) {
			pr_debug("Process DClient pdp");
			ptcp_pdp_reader_process_dclient_pdp(ptcp, property,
							    status_info);
		}
	} else if (ptcp_proxy_is_dserver(ptcp->pdp_received)) {
		if (ret) {
			pr_debug("Process Dserver pdp");
			ptcp_pdp_reader_data_process(ptcp, property, status_info);
		}
	} else {
		loc = ptcp_proxy_get_meta_uc_loc(ptcp->pdp_received);

		if (ret && locator_has_valid_kind(loc)) {
			pr_debug("Process Normal pdp");
			ptcp_pdp_reader_data_process(ptcp, property, status_info);
		}
	}

	/* FIXME: maybe recorder_proxy shouldn't be set at here. */
	if (msg->extra_flags == EXTRA_FLAGS_RECORDER_DATA) {
		ptcp->recorder_proxy = ptcp_proxy;
	}

	return ;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
