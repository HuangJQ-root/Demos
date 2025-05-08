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
#include <mvbs/rtps/message.h>
#include <messages/message_factory.h>
#include <mcdr/mcdr.h>
#include <qos/e2e.h>

/* The first bytes incl. submessagelength don't count */
static const uint8_t num_bytes_until_end_of_len = 4;

static inline uint16_t bitmap_size_align_up(uint32_t numbits)
{
	return (uint16_t)(4U * ((numbits + 31U) / 32U));
}

static bool rtps_msg_ser_header(struct mvbs_cdr *buffer,
				struct message_header *header)
{
	bool ret = true;
	ret = mcdr_serialize_array_uint8_t(buffer, header->protocol_name,
					   sizeof(header->protocol_name));
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize (protocol_name) in RTPS header.");
		return ret;
	}

	ret = mcdr_serialize_array_uint8_t(
		buffer, (const uint8_t *)(&(header->protocol_version)),
		sizeof(struct rtps_version));
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize (protocol_version) in RTPS header.");
		return ret;
	}

	ret = mcdr_serialize_array_uint8_t(buffer, header->vendor_id.id,
					   sizeof(struct rtps_vendor_id));
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize (vendor_id) in RTPS header.");
		return ret;
	}

	ret = mcdr_serialize_array_uint8_t(buffer, header->ptcp_guid_prefix.id,
					   sizeof(struct rtps_guid_prefix));
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize (guid_prefix) in RTPS header.");
		return ret;
	}

	return ret;
}

bool rtps_msg_add_header(struct mvbs_cdr *payload,
			 const struct rtps_guid_prefix *pprefix)
{
	struct message_header header;
	const char* str = "RTPS";

	mvbs_memcpy(header.protocol_name, str, 4);
	header.protocol_version = PROTOCOLVERSION;
	header.vendor_id	= VENDOR_ID;
	header.ptcp_guid_prefix = *pprefix;

	if (!rtps_msg_ser_header(payload, &header)) {
		pr_warn("Message serialize RTPS header fail.\n");
		return false;
	}

	return true;
}

static inline bool rtps_msg_ser_submsg_header(struct mvbs_cdr *cdr,
					      uint8_t submsg_id, uint8_t flags,
					      uint16_t octets_to_next_header)
{
	if (!mcdr_serialize_uint8_t(cdr, submsg_id)) {
		pr_err(ERR_MCDR, "Fail to serialize (submsg_id) in submsg header.");
		return false;
	}

	if (!mcdr_serialize_uint8_t(cdr, flags)) {
		pr_err(ERR_MCDR, "Fail to serialize (flags) in submsg header.");
		return false;
	}

	if (!mcdr_serialize_uint16_t(cdr, octets_to_next_header)) {
		pr_err(ERR_MCDR, "Fail to serialize (octets_to_next_header) in submsg header.");
		return false;
	}
	return true;
}

static inline bool rtps_msg_ser_entity_id(struct mvbs_cdr *cdr,
					  const struct rtps_entity_id *id)
{
	const struct rtps_entity_id *eid = (id == NULL)?&ENTITYID_UNKNOWN:id;

	if (!mcdr_serialize_array_uint8_t(cdr, eid->entity_key,
						  sizeof(eid->entity_key))) {
		pr_err(ERR_MCDR, "Fail to serialize eid->entity_key.");
		return false;
	}

	if (!mcdr_serialize_uint8_t(cdr, eid->entity_kind)) {
		pr_err(ERR_MCDR, "Fail to serialize eid->entity_kind.");
		return false;
	}

	return true;
}

static inline bool rtps_msg_ser_sn(struct mvbs_cdr *cdr,
				   const struct rtps_sn *sn)
{
	if (!mcdr_serialize_uint32_t(cdr, (uint32_t)sn->high)) {
		pr_err(ERR_MCDR, "Fail to serialize sn->high.");
		return false;
	}

	if (!mcdr_serialize_uint32_t(cdr, sn->low)) {
		pr_err(ERR_MCDR, "Fail to serialize sn->low.");
		return false;
	}

	return true;
}

static inline bool rtps_msg_ser_sn_set(struct mvbs_cdr *cdr,
				       const struct rtps_sn_set *sn_set)
{
	if (!rtps_msg_ser_sn(cdr, &sn_set->base)) {
		pr_err(ERR_MCDR, "Fail to serialize sn_set->base.");
		return false;
	}

	if (!mcdr_serialize_uint32_t(cdr, sn_set->num_bits)) {
		pr_err(ERR_MCDR, "Fail to serialize sn_set->num_bits.");
		return false;
	}

	if (sn_set->num_bits != 0U) {
		uint16_t bitmap_size = bitmap_size_align_up(sn_set->num_bits);

		if (!mcdr_serialize_array_uint8_t(cdr,
					(const uint8_t *)(sn_set->bitmap),
					bitmap_size)) {

			pr_err(ERR_MCDR, "Fail to serialize sn_set->bitmap.");
			return false;
		}
	}

	return true;
}

static inline bool rtps_msg_ser_timestamp(struct mvbs_cdr *cdr,
				const struct rtps_time *rtps_timestamp)
{
	if (!mcdr_serialize_array_uint8_t(cdr,
					  (const uint8_t *)(&rtps_timestamp->seconds),
					  (uint16_t)sizeof(rtps_timestamp->seconds))) {
		pr_err(ERR_MCDR, "Fail to serialize timestamp->seconds.");
		return false;
	}

	if (!mcdr_serialize_array_uint8_t(cdr,
					  (const uint8_t *)(&rtps_timestamp->nanosec),
					  (uint16_t)sizeof(rtps_timestamp->nanosec))) {
		pr_err(ERR_MCDR, "Fail to serialize timestamp->nanosec.");
		return false;
	}

	return true;
}

bool rtps_msg_add_submsg_gap(struct mvbs_cdr *cdr,
			     const struct rtps_entity_id *writer_id,
			     const struct rtps_entity_id *reader_id,
			     struct rtps_sn gap_start,
			     struct rtps_sn_set *gap_list)
{
	bool ret;
	uint16_t octets_to_next_header;

	octets_to_next_header = msg_get_submsg_gap_raw_size(*gap_list) -
				num_bytes_until_end_of_len;

	ret = rtps_msg_ser_submsg_header(cdr, GAP, FLAG_MVBS_ENDIANESS,
					 octets_to_next_header);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize GAP (submsg_header).");
		return false;
	}

	ret = rtps_msg_ser_entity_id(cdr, reader_id);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize GAP (reader_id).");
		return false;
	}

	ret = rtps_msg_ser_entity_id(cdr, writer_id);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize GAP (writer_id).");
		return false;
	}

	ret = rtps_msg_ser_sn(cdr, &gap_start);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize GAP (gap_start).");
		return false;
	}

	ret = rtps_msg_ser_sn_set(cdr, gap_list);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize GAP (gap_list).");
		return false;
	}

	return true;
}

bool rtps_msg_add_submsg_acknack(struct mvbs_cdr *cdr,
				 const struct rtps_entity_id *writer_id,
				 const struct rtps_entity_id *reader_id,
				 const struct rtps_sn_set *sn_state,
				 int32_t acknack_count, bool final_flag)
{
	bool ret;
	uint8_t  flags = FLAG_MVBS_ENDIANESS;
	uint16_t octets_to_next_header;

	octets_to_next_header = msg_get_submsg_acknack_raw_size(*sn_state) -
				num_bytes_until_end_of_len;

	if (final_flag) {
		flags |= FLAG_FINAL;
	}

	ret = rtps_msg_ser_submsg_header(cdr, ACKNACK, flags,
					 octets_to_next_header);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize ACKNACK (submsg_header).");
		return false;
	}

	ret = rtps_msg_ser_entity_id(cdr, reader_id);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize ACKNACK (reader_id).");
		return false;
	}

	ret = rtps_msg_ser_entity_id(cdr, writer_id);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize ACKNACK (writer_id).");
		return false;
	}

	ret = rtps_msg_ser_sn_set(cdr, sn_state);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize ACKNACK (gap_list).");
		return false;
	}

	if (!mcdr_serialize_uint32_t(cdr, (uint32_t)acknack_count)) {
		pr_err(ERR_MCDR, "Fail to serialize ACKNACK (count).");
		return false;
	}

	return true;
}

bool rtps_msg_add_submsg_heartbeat(struct mvbs_cdr *cdr,
			     const struct rtps_entity_id *reader_id,
			     const struct rtps_entity_id *writer_id,
			     struct rtps_sn first_sn,
			     struct rtps_sn last_sn,
			     uint32_t acknack_count, bool liveliness)
{
	bool	ret;
	uint8_t	flags = FLAG_MVBS_ENDIANESS;
	uint16_t octets_to_next_header;

	octets_to_next_header = msg_get_submsg_heartbeat_raw_size() -
				num_bytes_until_end_of_len;

	/* FIXME */
	if (liveliness) {
		flags |= FLAG_FINAL;
	}

	ret = rtps_msg_ser_submsg_header(cdr, HEARTBEAT, flags,
					 octets_to_next_header);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize HEARTBEAT (submsg_header).");
		return false;
	}

	ret = rtps_msg_ser_entity_id(cdr, reader_id);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize HEARTBEAT (reader_id).");
		return false;
	}

	ret = rtps_msg_ser_entity_id(cdr, writer_id);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize HEARTBEAT (writer_id).");
		return false;
	}

	ret = rtps_msg_ser_sn(cdr, &first_sn);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize HEARTBEAT (first_sn).");
		return false;
	}

	ret = rtps_msg_ser_sn(cdr, &last_sn);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize HEARTBEAT (last_sn).");
		return false;
	}

	if (!mcdr_serialize_uint32_t(cdr, acknack_count)) {
		pr_err(ERR_MCDR, "Fail to serialize HEARTBEAT (count).");
		return false;
	}

	return true;
}

bool rtps_msg_add_submsg_timestamp(struct mvbs_cdr *cdr,
				   const struct rtps_time *ts)
{
	bool	ret;
	uint16_t octets_to_next_header;

	if (mcdr_buffer_remaining(cdr) < msg_get_submsg_time_raw_size()) {
		return false;
	}

	octets_to_next_header = (uint16_t)sizeof(struct rtps_time);

	ret = rtps_msg_ser_submsg_header(cdr, INFO_TS, FLAG_MVBS_ENDIANESS,
					 octets_to_next_header);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize INFO_TS (submsg_header).");
		return false;
	}

	ret = rtps_msg_ser_timestamp(cdr, ts);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize INFO_TS (timestamp).");
		return false;
	}

	return true;
}

bool rtps_msg_add_submsg_e2e(struct mvbs_cdr *cdr,
				  const struct serialized_payload *payload,
				  const struct rtps_entity_id *reader_id,
				  const struct rtps_entity_id *writer_id,
				  struct rtps_sn *sn)
{
	bool		ret;
	uint32_t	crc;

	ret = rtps_msg_ser_submsg_header(cdr, INFO_E2E, FLAG_MVBS_ENDIANESS, 8);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize INFO_E2E (submsg_header).");
		return false;
	}

	if (!mcdr_serialize_uint32_t(cdr, payload->recv_size)) {
		pr_err(ERR_MCDR, "Fail to serialize INFO_E2E (length).");
		return false;
	}

	crc = e2e_calculate_crc32P4(payload->data, payload->recv_size, reader_id, writer_id, sn);

	if (!mcdr_serialize_uint32_t(cdr, crc)) {
		pr_err(ERR_MCDR, "Fail to serialize INFO_E2E (CRC).");
		return false;
	}

	return true;
}

bool rtps_msg_update_submsg_e2e(struct mvbs_cdr *cdr,
				struct writer *w,
				struct rtps_entity_id *reader_id,
				struct writer_cache_change *wcc)
{
	uint32_t		crc = 0U;
	uint8_t			*data_ptr = writer_cache_get_cc_payload(wcc);

	struct rtps_entity_id	writer_id = {0};

	writer_id = writer_get_eid(w);

	if (mcdr_buffer_has_error(cdr)) {
		return false;
	}

	crc = e2e_calculate_crc32P4(data_ptr, wcc->real_size, reader_id, &writer_id, &wcc->cc.sn);

	/* 4. replace crc */
	if (!mcdr_serialize_uint32_t(cdr, crc)) {
		pr_err(ERR_MCDR, "Fail to serialize INFO_E2E (CRC).");
		return false;
	}

	return true;
}

bool rtps_msg_init_submsg_e2e(struct mvbs_cdr *cdr,
			    const struct writer_cache_change *wcc)
{
	bool				ret = false;
	uint32_t			crc = 0U;

	ret = rtps_msg_ser_submsg_header(cdr, INFO_E2E, FLAG_MVBS_ENDIANESS, 8);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize INFO_E2E (submsg_header).");
		return false;
	}

	if (!mcdr_serialize_uint32_t(cdr, wcc->real_size)) {
		pr_err(ERR_MCDR, "Fail to serialize INFO_E2E (length).");
		return false;
	}

	/* Just takes up buffer space */
	if (!mcdr_serialize_uint32_t(cdr, crc)) {
		pr_err(ERR_MCDR, "Fail to serialize INFO_E2E (CRC).");
		return false;
	}

	return true;
}

bool rtps_msg_add_submsg_data_raw(struct mvbs_cdr *cdr, const struct rtps_sn *sn,
				  const uint8_t *data, uint16_t length,
				  bool contains_inline_qos,
				  const struct rtps_entity_id *writer_id,
				  const struct rtps_entity_id *reader_id)
{
	bool	ret;
	uint8_t	flags = FLAG_MVBS_ENDIANESS;
	uint16_t extra_flags = 0;
	uint16_t octets_to_inlineqos;
	uint16_t octets_to_next_header;

	octets_to_next_header = msg_get_submsg_data_raw_size() +
				length - num_bytes_until_end_of_len;

	if (contains_inline_qos) {
		flags |= FLAG_INLINE_QOS;
	}

	if (length > 0U) {
		flags |= FLAG_DATA_PAYLOAD;
	}

	ret = rtps_msg_ser_submsg_header(cdr, DATA, flags,
					 octets_to_next_header);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (submsg_header).");
		return false;
	}

	if (!mcdr_serialize_uint16_t(cdr, extra_flags)) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (extra_flags).");
		return false;
	}

	octets_to_inlineqos = 4 + 4 + 8; /* EntityIds + SequenceNumber*/
	if (!mcdr_serialize_uint16_t(cdr, octets_to_inlineqos)) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (octets_to_inlineqos).");
		return false;
	}

	ret = rtps_msg_ser_entity_id(cdr, reader_id);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (reader_id).");
		return false;
	}

	ret = rtps_msg_ser_entity_id(cdr, writer_id);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (writer_id).");
		return false;
	}

	ret = rtps_msg_ser_sn(cdr, sn);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (sequence_number).");
		return false;
	}

	if (!mcdr_serialize_array_uint8_t(cdr, data, length)) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (data).");
		return false;
	}

	return true;
}

bool rtps_msg_add_submsg_data_wrap(struct mvbs_cdr *cdr, uint16_t extra_flags,
				   const struct rtps_sn *sn,
				   const struct rtps_entity_id *writer_id,
				   const struct rtps_entity_id *reader_id,
				   bool (*fn)(struct mvbs_cdr *cdr, void *arg),
				   void *arg)
{
	bool	ret;
	uint8_t	flags = FLAG_MVBS_ENDIANESS;
	uint16_t octets_to_inlineqos;
	uint16_t octets_to_next_header;
	struct mvbs_cdr cdr_tmp;

	mcdr_copy_buffer(&cdr_tmp, cdr);

	mcdr_serialize_uint32_t(cdr, 0);

	if (!mcdr_serialize_uint16_t(cdr, extra_flags)) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (extra_flags).");
		return false;
	}

	octets_to_inlineqos = 4 + 4 + 8; /* EntityIds + SequenceNumber */
	if (!mcdr_serialize_uint16_t(cdr, octets_to_inlineqos)) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (octets_to_inlineqos).");
		return false;
	}

	ret = rtps_msg_ser_entity_id(cdr, reader_id);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (reader_id).");
		return false;
	}

	ret = rtps_msg_ser_entity_id(cdr, writer_id);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (writer_id).");
		return false;
	}

	ret = rtps_msg_ser_sn(cdr, sn);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (sequence_number).");
		return false;
	}

	fn(cdr, arg);

	octets_to_next_header = mcdr_buffer_length(cdr) - mcdr_buffer_length(&cdr_tmp) - 4;

	cdr = &cdr_tmp;

	flags |= FLAG_DATA_PAYLOAD;

	ret = rtps_msg_ser_submsg_header(cdr, DATA, flags,
					 octets_to_next_header);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (submsg_header).");
		return false;
	}

	return true;
}

bool rtps_msg_add_submsg_data(struct mvbs_cdr *cdr,
			      struct writer_cache_change *wcc,
			      bool contains_inline_qos,
			      const struct rtps_entity_id *writer_id,
			      const struct rtps_entity_id *reader_id)
{
	bool	ret;
	uint8_t	flags = FLAG_MVBS_ENDIANESS;
	uint16_t extra_flags = 0;
	uint16_t octets_to_inlineqos;
	uint16_t octets_to_next_header;

	octets_to_next_header = msg_get_submsg_data_raw_size() +
				(uint16_t)wcc->real_size -
				num_bytes_until_end_of_len;

	if (contains_inline_qos) {
		flags |= FLAG_INLINE_QOS;
	}

	if (wcc->real_size > 0U) {
		flags |= FLAG_DATA_PAYLOAD;
	}

	ret = rtps_msg_ser_submsg_header(cdr, DATA, flags,
					 octets_to_next_header);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (submsg_header).");
		return false;
	}

	if (!mcdr_serialize_uint16_t(cdr, extra_flags)) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (extra_flags).");
		return false;
	}

	octets_to_inlineqos = 4 + 4 + 8; /* EntityIds + SequenceNumber */
	if (!mcdr_serialize_uint16_t(cdr, octets_to_inlineqos)) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (octets_to_inlineqos).");
		return false;
	}

	ret = rtps_msg_ser_entity_id(cdr, reader_id);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (reader_id).");
		return false;
	}

	ret = rtps_msg_ser_entity_id(cdr, writer_id);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (writer_id).");
		return false;
	}

	ret = rtps_msg_ser_sn(cdr, &wcc->cc.sn);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (sequence_number).");
		return false;
	}

	if (!mcdr_serialize_array_uint8_t(cdr,
				writer_cache_get_cc_payload(wcc),
				(uint16_t)wcc->real_size)) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (data).");
		return false;
	}

	return true;
}

static bool cdr_serialize_data_submessage_header(struct mvbs_cdr *cdr,
						size_t data_length,
						const struct rtps_entity_id *sender,
						const struct rtps_entity_id *receiver,
						struct rtps_sn sn)
{
	uint16_t extra_flags = 0;
	uint16_t octets_to_inlineqos;
	uint16_t octets_to_next_header;
	uint8_t	 flags = FLAG_MVBS_ENDIANESS;
	bool	 ret;

	octets_to_next_header = msg_get_submsg_data_raw_size() +
				data_length - num_bytes_until_end_of_len;

	flags |= FLAG_DATA_PAYLOAD;

	ret = rtps_msg_ser_submsg_header(cdr, DATA, flags,
					 octets_to_next_header);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (submsg_header).");
		return false;
	}

	if (!mcdr_serialize_uint16_t(cdr, extra_flags)) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (extra_flags).");
		return false;
	}

	octets_to_inlineqos = 4 + 4 + 8; /* EntityIds + SequenceNumber */
	if (!mcdr_serialize_uint16_t(cdr, octets_to_inlineqos)) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (octets_to_inlineqos).");
		return false;
	}

	ret = rtps_msg_ser_entity_id(cdr, receiver);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (reader_id).");
		return false;
	}

	ret = rtps_msg_ser_entity_id(cdr, sender);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (writer_id).");
		return false;
	}

	ret = rtps_msg_ser_sn(cdr, &sn);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (sequence_number).");
		return false;
	}

	return true;
}

bool rtps_msg_add_submsg_data_sedp_edp(struct mvbs_cdr *cdr,
				       const struct rtps_entity_id *sender,
				       const struct rtps_entity_id *receiver,
				       struct rtps_sn sn,
				       const struct participant *ptcp,
				       const struct endpoint_attr *attr,
				       struct rtps_entity_id eid)
{
	size_t	data_length;
	bool	ret;

	if ((cdr == NULL) || (ptcp == NULL) || (attr == NULL)) {
		return false;
	}

	data_length = cdr_serialize_sedp_edp_length(attr);

	if (mcdr_buffer_remaining(cdr) < data_length) {
		return false;
	}

	ret = cdr_serialize_data_submessage_header(cdr, data_length,
						   sender, receiver, sn);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize spdp_pdp (header).");
		return false;
	}

	if (cdr_serialize_sedp_edp(cdr, ptcp, attr, eid) != 0) {
		pr_debug("Fail to serialize DATA (data).");
		return false;
	}

	return true;
}

bool rtps_msg_add_submsg_data_sedp_offline_edp(struct mvbs_cdr *cdr,
				       const struct rtps_entity_id *sender,
				       const struct rtps_entity_id *receiver,
				       struct rtps_sn sn,
				       struct rtps_guid_prefix *guid,
				       struct rtps_entity_id  offline_eid)
{
	size_t	data_length;
	bool	ret;

	if ((cdr == NULL) || (guid == NULL)) {
		return false;
	}

	data_length = cdr_serialize_sedp_offline_edp_length();

	ret = cdr_serialize_data_submessage_header(cdr, data_length,
						   sender, receiver, sn);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (submsg_header).");
		return false;
	}

	if (cdr_serialize_sedp_edp_offline(cdr, guid, offline_eid) != 0) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (data).");
	}

	return true;
}

bool rtps_msg_add_submsg_data_spdp_pdp(struct mvbs_cdr *cdr,
				       const struct rtps_entity_id *writer_id,
				       const struct rtps_entity_id *receiver,
				       struct rtps_sn sn,
				       struct participant *ptcp,
				       struct rtps_property *property,
				       int32_t pktnum)
{
	size_t data_length;

	if ((cdr == NULL) || (ptcp == NULL)) {
		return false;
	}

	data_length = cdr_serialize_spdp_pdp_length(ptcp, property, pktnum);

	if (mcdr_buffer_remaining(cdr) < data_length) {
		return false;
	}

	if (!cdr_serialize_data_submessage_header(cdr, data_length, writer_id, receiver, sn)) {
		pr_err(ERR_MCDR, "Fail to serialize spdp_pdp (header).");
		return false;
	}

	if (cdr_serialize_spdp_pdp(cdr, ptcp, property, pktnum) != 0) {
		pr_err(ERR_MCDR, "Fail to serialize spdp_pdp (data).");
		return false;
	}

	return true;
}

bool ptcp_send_submsg_data_wrap(struct participant *ptcp,
				locator_t *loc, bool link_bakup,
				struct mvbs_cdr *cdr,
				uint16_t extra_flags,
				struct rtps_sn *sn,
				const struct rtps_entity_id *writer_id,
				const struct rtps_entity_id *reader_id,
				bool (*fn)(struct mvbs_cdr *cdr, void *arg),
				void *arg)
{
	struct mvbs_cdr cdr_iter;
	uint32_t	octets_to_next_header_offset;
	uint16_t	octets_to_inlineqos;
	uint16_t	octets_to_next_header;
	uint8_t		flags = FLAG_MVBS_ENDIANESS;
	bool		ret;
	bool		repeat;

	if (!mcdr_serialize_uint8_t(cdr, DATA)) {
		pr_err(ERR_MCDR, "Fail to serialize (submsg_id) in submsg header.");
		return false;
	}

	flags |= FLAG_DATA_PAYLOAD;
	if (!mcdr_serialize_uint8_t(cdr, flags)) {
		pr_err(ERR_MCDR, "Fail to serialize (flags) in submsg header.");
		return false;
	}

	octets_to_next_header_offset = mcdr_buffer_length(cdr);

	mcdr_serialize_uint16_t(cdr, 0);

	if (!mcdr_serialize_uint16_t(cdr, extra_flags)) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (extra_flags).");
		return false;
	}

	octets_to_inlineqos = 4 + 4 + 8; /* EntityIds + SequenceNumber */
	if (!mcdr_serialize_uint16_t(cdr, octets_to_inlineqos)) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (octets_to_inlineqos).");
		return false;
	}

	ret = rtps_msg_ser_entity_id(cdr, reader_id);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (reader_id).");
		return false;
	}

	ret = rtps_msg_ser_entity_id(cdr, writer_id);
	if (!ret) {
		pr_err(ERR_MCDR, "Fail to serialize DATA (writer_id).");
		return false;
	}

	do {
		mcdr_copy_buffer(&cdr_iter, cdr);

		rtps_sn_increase(sn);

		ret = rtps_msg_ser_sn(&cdr_iter, sn);
                if (!ret) {
			pr_err(ERR_MCDR, "Fail to serialize DATA (sequence_number).");
			return false;
                }

		repeat = fn(&cdr_iter, arg);

		octets_to_next_header = mcdr_buffer_length(&cdr_iter) -
					octets_to_next_header_offset - 2;

		flags |= FLAG_DATA_PAYLOAD;

		mcdr_fill_buffer_with_offset(cdr, octets_to_next_header_offset,
					&octets_to_next_header, sizeof(octets_to_next_header));
		if (!ret) {
			pr_err(ERR_MCDR, "Fail to serialize DATA (submsg_header).");
			return false;
		}

		ptcp_send_buffer_to(ptcp, mcdr_get_buffer(&cdr_iter),
					  mcdr_buffer_length(&cdr_iter),
					  loc, link_bakup);
	} while (!repeat);

	mcdr_copy_buffer(cdr, &cdr_iter);

	return true;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
