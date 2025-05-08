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

#include <mvbs/utils/log.h>
#include <mvbs/rtps/message.h>
#include <messages/message_receiver.h>
#include <discovery/sddp.h>
#include <diag/recorder.h>
#include <qos/e2e.h>

#if RECV_VERBOSE || RTPS_GLOBAL_VERBOSE
#undef MVBSLOG_LEVEL
#define MVBSLOG_LEVEL MVBSLOG_VERB
#endif

static bool msg_recv_process_header(struct message_processing_info *pmsg_info,
				    struct message_receiver *receiver)
{
	if (!msg_des_header(pmsg_info, &receiver->rtps_hdr)) {
		return false;
	}

	pr_verb("[MessageReceiver]: Received others message.\n");

	if (receiver->rtps_hdr.protocol_version.major != PROTOCOLVERSION.major) {
		return false;
	}

	pmsg_info->next_pos += msg_get_header_raw_size();

	return true;
}

static bool msg_recv_process_submsg_data(struct message_processing_info *pmsg_info,
					 const struct submessage_header *psubmsg_hdr,
					 struct message_receiver *receiver)
{
	struct submessage_data		submsg_data;
	struct rtps_guid		writer_guid;
	struct reader			*r;
	const uint8_t			*pdata;
	uint16_t			size;

	if (!msg_des_submsg_data(pmsg_info, psubmsg_hdr, &submsg_data)) {
		return false;
	}

	pdata = msg_get_cur_pos(pmsg_info) + msg_get_submsg_data_raw_size();

	size = submsg_data.header.octets_to_next_header
		- msg_get_submsg_data_raw_size()
		+ msg_get_submsg_header_raw_size();

	pr_verb("Received data message size %u\n", size);

	if (ptcp_dpde_on_data(receiver, &submsg_data, pdata, size)) {
		return true;
	}

	if (receiver->ptcp_proxy == NULL) {
		pr_verb("Fail to find ptcp proxy: " GUID_PREFIX_FMT,
			GUID_PREFIX_PARTS(receiver->rtps_hdr.ptcp_guid_prefix.id));

		return true;
	}

	if (rtps_entity_id_equal(&submsg_data.reader_id, &ENTITYID_UNKNOWN)) {
		pr_verb("Received ENTITYID_UNKNOWN readerID, searching for writer ID =\n");
		rtps_guid_print(&writer_guid);

		r = ptcp_get_reader_with_wproxy(receiver->ptcp,
						receiver->ptcp_proxy,
						submsg_data.writer_id);
		if (r != NULL) {
			pr_verb("Found reader!\n");
		}
	} else {
		r = ptcp_get_reader_with_eid(receiver->ptcp, submsg_data.reader_id);
	}

	if (r != NULL) {
		struct reader_data read_data;

		read_data.ptcp_proxy	= receiver->ptcp_proxy;
		read_data.reader_id	= submsg_data.reader_id;
		read_data.writer_id	= submsg_data.writer_id;
		read_data.wproxy	= NULL;
		read_data.sn		= submsg_data.writer_sn;
		read_data.data		= pdata;
		read_data.size		= size;
		read_data.e2e_new	= &receiver->info_e2e;
		read_data.data_flags	= submsg_data.header.flags;

		if (receiver->have_timestamp) {
			read_data.src_time		= receiver->info_ts;
		} else {
			read_data.src_time.seconds	= 0;
			read_data.src_time.nanosec	= 0;
		}

		reader_on_new_data(r, &read_data);

		void reader_record_hook(struct reader * r,
				struct message_processing_info * pmsg_info,
				uint8_t * data_addr, uint16_t data_size);

		reader_record_hook(r, pmsg_info, (uint8_t*)pdata, size);
	} else {
		pr_verb("Couldn't find a reader with id:\n");
		rtps_entity_id_print(submsg_data.reader_id);
	}

	return true;
}

static bool msg_recv_process_submsg_time(struct message_processing_info *pmsg_info,
					 const struct submessage_header *psubmsg_hdr,
					 struct message_receiver *receiver)
{
#ifndef MVBS_DES_TURBO
	(void)psubmsg_hdr;
	struct submessage_time submsg_time;

	if (!msg_des_submsg_time(pmsg_info, &submsg_time)) {
		return false;
	}

	receiver->have_timestamp = true;
	receiver->src_time = submsg_time.rtps_timestamp;
#else
	if (!msg_des_submsg_time_payload(pmsg_info, psubmsg_hdr, &receiver->info_ts)) {
		return false;
	}

	receiver->have_timestamp = true;

#endif

	return true;
}

static bool msg_recv_process_submsg_heartbeat(struct message_processing_info *pmsg_info,
					      struct message_receiver *receiver)
{
	struct submessage_heartbeat	submsg_hb;
	struct reader			*r;

#ifndef MVBS_DES_TURBO
	if (!msg_des_submsg_heartbeat(pmsg_info, &submsg_hb)) {
		return false;
	}
#else
	if (!msg_des_submsg_heartbeat_payload(pmsg_info, &submsg_hb)) {
		return false;
	}
#endif
	if (receiver->ptcp_proxy == NULL) {
		pr_verb("Fail to find ptcp proxy: " GUID_PREFIX_FMT,
			GUID_PREFIX_PARTS(receiver->rtps_hdr.ptcp_guid_prefix.id));

		return true;
	}

	if (ptcp_dpde_on_heartbeat(receiver, &submsg_hb)) {
		return true;
	}

	if (rtps_entity_id_equal(&submsg_hb.reader_id, &ENTITYID_UNKNOWN)) {
		r = ptcp_get_reader_with_wproxy(receiver->ptcp,
						receiver->ptcp_proxy,
						submsg_hb.writer_id);
	} else {
		r = ptcp_get_reader_with_eid(receiver->ptcp, submsg_hb.reader_id);
	}

	if (r != NULL) {
		(void)reader_on_new_heartbeat(r, &submsg_hb, receiver->ptcp_proxy);
		return true;
	}

	return false;
}

static bool msg_recv_process_submsg_acknack(struct message_processing_info *pmsg_info,
					    const struct submessage_header *psubmsg_hdr,
					    const struct message_receiver *receiver)
{
	struct submessage_acknack	submsg_acknack;
	struct writer			*w;

#ifndef MVBS_DES_TURBO
	(void)psubmsg_hdr;
	if (!msg_des_submsg_acknack(pmsg_info, &submsg_acknack)) {
		return false;
	}
#else

	if (!msg_des_submsg_acknack_payload(pmsg_info, psubmsg_hdr, &submsg_acknack)) {
		return false;
	}
#endif
	if (receiver->ptcp_proxy == NULL) {
		pr_verb("Fail to find ptcp proxy: " GUID_PREFIX_FMT,
			GUID_PREFIX_PARTS(receiver->rtps_hdr.ptcp_guid_prefix.id));

		return true;
	}

	if (ptcp_dpde_on_acknack(receiver, &submsg_acknack)) {
		return true;
	}

	w = ptcp_get_writer_with_eid(receiver->ptcp, submsg_acknack.writer_id);
	if (w != NULL) {
		writer_on_new_acknack(w, &submsg_acknack, receiver->ptcp_proxy);

		return true;
	}

	return false;
}

static bool msg_recv_process_submsg_gap(struct message_processing_info *pmsg_info,
					const struct submessage_header *psubmsg_hdr,
					const struct message_receiver *receiver)
{
	struct submessage_gap		submsg_gap;
	struct reader			*r;
	bool				ret;

#ifndef MVBS_DES_TURBO
	(void)psubmsg_hdr;
	if (!msg_des_submsg_gap(pmsg_info, &submsg_gap)) {
		return false;
	}
#else
	if (!msg_des_submsg_gap_payload(pmsg_info, psubmsg_hdr, &submsg_gap)) {
		return false;
	}
#endif
	if (receiver->ptcp_proxy == NULL) {
		pr_verb("Fail to find ptcp proxy: " GUID_PREFIX_FMT,
			GUID_PREFIX_PARTS(receiver->rtps_hdr.ptcp_guid_prefix.id));

		return true;
	}

	if (ptcp_dpde_on_gap(receiver, &submsg_gap)) {
		return true;
	}

	if (rtps_entity_id_equal(&submsg_gap.reader_id, &ENTITYID_UNKNOWN)) {
		r = ptcp_get_reader_with_wproxy(receiver->ptcp,
						receiver->ptcp_proxy,
						submsg_gap.writer_id);
	} else {
		r = ptcp_get_reader_with_eid(receiver->ptcp, submsg_gap.reader_id);
	}

	if (r != NULL) {
		ret = reader_on_new_gap(r, &submsg_gap, receiver->ptcp_proxy);
		if (!ret) {
			pr_warn("reader on new gap fail!\n");
		}

		return true;
	}

	return false;
}

static bool msg_recv_process_submsg_e2e(struct message_processing_info *pmsg_info,
					struct message_receiver *receiver)
{
	struct submessage_e2e		submsg_e2e;
	const struct reader		*r;

	(void)r;

#ifndef MVBS_DES_TURBO
	if (!msg_des_submsg_e2e(pmsg_info, &submsg_e2e)) {
		return false;
	}
#else
	if (!msg_des_submsg_e2e_payload(pmsg_info, &submsg_e2e)) {
		return false;
	}
#endif

#if 0
	/* FIXME: Maybe this reader object is not usefully for e2e? */

	if (rtps_entity_id_equal(&submsg_e2e.reader_id, &ENTITYID_UNKNOWN)) {
		r = ptcp_get_reader_with_wproxy(receiver->ptcp,
						receiver->ptcp_proxy,
						submsg_e2e.writer_id);
	} else {
		r = ptcp_get_reader_with_eid(receiver->ptcp, submsg_e2e.reader_id);
	}

	if (r == NULL) {
		pr_err(ERR_NOENT, "Fail to find the reader for E2E!\n");

		return false;
	}
#endif

	if (!reader_on_new_e2e(submsg_e2e, &receiver->info_e2e)) {
		pr_warn("Fail to parse e2e submessage!\n");
		return false;
	}

	receiver->info_e2e.enable = true;

	return true;
}

static bool msg_recv_process_submsg(struct message_processing_info *pmsg_info,
				    const struct submessage_header *psubmsg_hdr,
				    struct message_receiver *receiver)
{
	bool process_success = false;

	switch (psubmsg_hdr->submessage_id) {
	case ACKNACK:
		pr_verb("Processing AckNack submessage\n");
		process_success = msg_recv_process_submsg_acknack(pmsg_info, psubmsg_hdr, receiver);
		break;
	case DATA:
		pr_verb("Processing Data submessage\n");
		process_success = msg_recv_process_submsg_data(pmsg_info, psubmsg_hdr, receiver);
		break;
	case HEARTBEAT:
		pr_verb("Processing Heartbeat submessage\n");
		process_success = msg_recv_process_submsg_heartbeat(pmsg_info, receiver);
		break;
	case INFO_DST:
		pr_verb("Info_DST submessage not relevant.\n");
		process_success = true; /* Not relevant */
		break;
	case INFO_TS:
		pr_verb("Info_TS submessage not relevant.\n");
		process_success = msg_recv_process_submsg_time(pmsg_info, psubmsg_hdr, receiver);
		break;
	case GAP:
		pr_verb("Processing GAP submessage\n");
		process_success = msg_recv_process_submsg_gap(pmsg_info, psubmsg_hdr, receiver);
		break;
	case INFO_E2E:
		pr_verb("Processing INFO_E2E submessage\n");
		process_success = msg_recv_process_submsg_e2e(pmsg_info, receiver);
		break;
	default:
		pr_verb("Submessage of type %u currently not supported. Skipping..\n",
			(uint8_t)(psubmsg_hdr->submessage_id));
		process_success = false;
		break;
	}

	pmsg_info->next_pos += psubmsg_hdr->octets_to_next_header +
			       msg_get_submsg_header_raw_size();

	return process_success;
}

bool msg_recv_process(struct participant *ptcp, const uint8_t *data,
						uint16_t size, bool discard_own)
{
	struct message_receiver		recv;
	struct submessage_header	submsg_hdr;
	struct rtps_guid_prefix		*guid_prefix;
	struct message_processing_info	msg_info = {
		.data = data,
		.size = size,
		.next_pos = 0,
	};

	mvbs_memzero(&recv, sizeof(recv));

	recv.ptcp = ptcp;

	if (!msg_recv_process_header(&msg_info, &recv)) {
		return false;
	}

	if (discard_own) {
		if (rtps_guid_prefix_equal(&recv.rtps_hdr.ptcp_guid_prefix,
					   &recv.ptcp->guid_prefix)) {
			pr_verb("[MessageReceiver]: Received own message.\n");
			return false; /* Don't process our own packet */
		}
	}

	guid_prefix = &recv.rtps_hdr.ptcp_guid_prefix;

	recv.ptcp_proxy = ptcp_get_proxy_with_guid_prefix(ptcp, guid_prefix);

	if (recv.ptcp_proxy != NULL) {
		pr_debug("Get a message from %s", recv.ptcp_proxy->ptcp_name);
	} else {
		pr_debug("A new remote ptcp: " GUID_PREFIX_FMT,
					GUID_PREFIX_PARTS(guid_prefix->id));
	}

	while (msg_info.next_pos < msg_info.size) {
		if (!msg_des_submsg_header(&msg_info, &submsg_hdr)) {
			return false;
		}

		(void)msg_recv_process_submsg(&msg_info, &submsg_hdr, &recv);
	}

	return true;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
