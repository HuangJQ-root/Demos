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

#include <mvbs/errno.h>
#include <mvbs/rtps/message.h>
#include <mcdr/mcdr.h>
#include <qos/e2e.h>

static uint16_t msg_get_submsg_header_raw_size_without_sn(void);


const uint8_t SCHEME_PL_CDR_LE[2] = { 0x00, 0x03 };

const char RTPS_PROTOCOL_NAME[4] = { 'R', 'T', 'P', 'S' };


const uint8_t *msg_get_cur_pos(const struct message_processing_info *pinfo)
{
	return pinfo->data + pinfo->next_pos;
}

static inline uint16_t msg_get_remaining_size(const struct message_processing_info *pinfo)
{
	return pinfo->size - pinfo->next_pos;
}

static void msg_do_copy(uint8_t *dst, const uint8_t **src, size_t size)
{
	mvbs_memcpy(dst, *src, size);
	*src += size;
}

bool msg_des_header(struct message_processing_info *info,
		    struct message_header *header)
{
	const uint8_t *current_pos = NULL;

	if (msg_get_remaining_size(info) < msg_get_header_raw_size()) {
		return false;
	}

	current_pos = msg_get_cur_pos(info);

	msg_do_copy((uint8_t *)header, &current_pos, sizeof(*header));

	return true;
}

bool msg_des_submsg_header(struct message_processing_info *info,
			   struct submessage_header *header)
{
	const uint8_t *current_pos = NULL;

	if (msg_get_remaining_size(info) < msg_get_submsg_header_raw_size()) {
		return false;
	}

	current_pos = msg_get_cur_pos(info);

	msg_do_copy((uint8_t *)header, &current_pos, sizeof(*header));

	return true;
}

bool msg_des_submsg_data(struct message_processing_info *info,
			 const struct submessage_header *psubmsg_hdr,
			 struct submessage_data *msg)
{
	const uint8_t *current_pos	= NULL;

	/* Check for length including data */
	if (msg_get_remaining_size(info) <
	    (msg_get_submsg_header_raw_size() + psubmsg_hdr->octets_to_next_header)) {
		return false;
	}

#ifndef MVBS_DES_TURBO

	current_pos = msg_get_cur_pos(info) + msg_get_submsg_header_raw_size();

	msg->header = *psubmsg_hdr;

	msg_do_copy((uint8_t *)(&(msg->extra_flags)), &current_pos,
			   sizeof(uint16_t));
	msg_do_copy((uint8_t *)(&(msg->octets_to_inlineqos)), &current_pos,
			   sizeof(uint16_t));
	msg_do_copy(msg->reader_id.entity_key, &current_pos,
			   sizeof(msg->reader_id.entity_key));
	msg->reader_id.entity_kind = (*current_pos);
	current_pos++;
	msg_do_copy(msg->writer_id.entity_key, &current_pos,
			   sizeof(msg->writer_id.entity_key));
	msg->writer_id.entity_kind = (*current_pos);
	current_pos++;
	msg_do_copy((uint8_t *)(&(msg->writer_sn.high)), &current_pos,
			   sizeof(msg->writer_sn.high));
	msg_do_copy((uint8_t *)(&(msg->writer_sn.low)), &current_pos,
			   sizeof(msg->writer_sn.low));

#else
	current_pos = msg_get_cur_pos(info);
	msg_do_copy((uint8_t*)(msg), &current_pos, sizeof(*msg));
#endif

	return true;
}

bool msg_des_submsg_time_payload(struct message_processing_info *info,
				 const struct submessage_header *psubmsg_hdr,
				 struct rtps_time *timestamp)
{
	const uint8_t *current_pos = NULL;

	if (msg_get_remaining_size(info) <
	    (msg_get_submsg_header_raw_size() + psubmsg_hdr->octets_to_next_header)) {
		return false;
	}

	current_pos = msg_get_cur_pos(info) + msg_get_submsg_header_raw_size();

	msg_do_copy((uint8_t *)(timestamp), &current_pos, sizeof(struct rtps_time));

	return true;
}

bool msg_des_submsg_time(struct message_processing_info *info,
			 struct submessage_time *msg)
{
	const uint8_t *current_pos = NULL;

	if (msg_get_remaining_size(info) < msg_get_submsg_time_raw_size()) {
		return false;
	}

	if (!msg_des_submsg_header(info, &(msg->header))) {
		return false;
	}

	/* Check for length including data */
	if (msg_get_remaining_size(info) <
	    (msg_get_submsg_header_raw_size() + msg->header.octets_to_next_header)) {
		return false;
	}

	current_pos = msg_get_cur_pos(info) + msg_get_submsg_header_raw_size();

	msg_do_copy((uint8_t *)(&(msg->rtps_timestamp)), &current_pos,
		    sizeof(msg->rtps_timestamp));

	return true;
}

bool msg_des_submsg_heartbeat(struct message_processing_info *info,
			      struct submessage_heartbeat *msg)
{
	if (msg_get_remaining_size(info) < msg_get_submsg_heartbeat_raw_size()) {
		return false;
	}

	if (!msg_des_submsg_header(info, &(msg->header))) {
		return false;
	}

	const uint8_t *current_pos = msg_get_cur_pos(info) +
                     msg_get_submsg_header_raw_size();

	msg_do_copy(msg->reader_id.entity_key, &current_pos,
			   sizeof(msg->reader_id.entity_key));
	msg->reader_id.entity_kind = (*current_pos);
	current_pos++;
	msg_do_copy(msg->writer_id.entity_key, &current_pos,
			   sizeof(msg->writer_id.entity_key));
	msg->writer_id.entity_kind = (*current_pos);
	current_pos++;
	msg_do_copy((uint8_t *)(&(msg->first_sn.high)), &current_pos,
			   sizeof(msg->first_sn.high));
	msg_do_copy((uint8_t *)(&(msg->first_sn.low)), &current_pos,
			   sizeof(msg->first_sn.low));
	msg_do_copy((uint8_t *)(&(msg->last_sn.high)), &current_pos,
			   sizeof(msg->last_sn.high));
	msg_do_copy((uint8_t *)(&(msg->last_sn.low)), &current_pos,
			   sizeof(msg->last_sn.low));
	msg_do_copy((uint8_t *)(&(msg->msg_count)), &current_pos, sizeof(msg->msg_count));

	return true;
}

bool msg_des_submsg_heartbeat_payload(struct message_processing_info *info,
				      struct submessage_heartbeat *msg)
{
	const uint8_t *current_pos = NULL;

	if (msg_get_remaining_size(info) < msg_get_submsg_heartbeat_raw_size()) {
		return false;
	}

	current_pos = msg_get_cur_pos(info);

	msg_do_copy((uint8_t *)msg, &current_pos, msg_get_submsg_heartbeat_raw_size());

	return true;
}

static inline uint16_t msg_get_bitmap_size(uint32_t numbits)
{
	return (uint16_t)(4U * ((numbits + 31U) / 32U));
}

bool msg_des_submsg_acknack(struct message_processing_info *info,
			    struct submessage_acknack *msg)
{
	uint16_t remain_size_at_begin = msg_get_remaining_size(info);

	if (remain_size_at_begin < msg_get_submsg_header_raw_size_without_sn()) {
		return false;
	}

	if (!msg_des_submsg_header(info, &(msg->header))) {
		return false;
	}

	const uint8_t *current_pos = msg_get_cur_pos(info) +
                     				msg_get_submsg_header_raw_size();

	msg_do_copy(msg->reader_id.entity_key, &current_pos,
			   sizeof(msg->reader_id.entity_key));
	msg->reader_id.entity_kind = (*current_pos);
	current_pos++;
	msg_do_copy(msg->writer_id.entity_key, &current_pos,
			   sizeof(msg->writer_id.entity_key));
	msg->writer_id.entity_kind = (*current_pos);
	current_pos++;
	msg_do_copy((uint8_t *)(&(msg->reader_sn_state.base.high)),
			   &current_pos, sizeof(msg->reader_sn_state.base.high));
	msg_do_copy((uint8_t *)(&(msg->reader_sn_state.base.low)),
			   &current_pos, sizeof(msg->reader_sn_state.base.low));
	msg_do_copy((uint8_t *)(&(msg->reader_sn_state.num_bits)),
			   &current_pos, sizeof(uint32_t));

	/* Now we can check for full size */
	if (remain_size_at_begin <
	    msg_get_submsg_acknack_raw_size(msg->reader_sn_state)) {
		return false;
	}

	if (msg->reader_sn_state.num_bits != 0U) {
		uint16_t bitmap_size = msg_get_bitmap_size(msg->reader_sn_state.num_bits);

		if (bitmap_size > sizeof(msg->reader_sn_state.bitmap)) {
			pr_err(ERR_FAULT, "bitmap info error!\n");
			msg_do_copy((uint8_t *)(msg->reader_sn_state.bitmap),
				&current_pos,
				sizeof(msg->reader_sn_state.bitmap));
			current_pos += bitmap_size - sizeof(msg->reader_sn_state.bitmap);
		} else {
			msg_do_copy((uint8_t *)(msg->reader_sn_state.bitmap),
				&current_pos,
				bitmap_size);
		}
	}

	msg_do_copy((uint8_t *)(&(msg->msg_count)), &current_pos, sizeof(msg->msg_count));

	return true;
}

bool msg_des_submsg_acknack_payload(struct message_processing_info *info,
				    const struct submessage_header *psubmsg_hdr,
				    struct submessage_acknack *msg)
{
	const uint8_t		*current_pos = NULL;
	uint16_t		size_before_bitmap = 0U;
	uint16_t		bitmap_size = 0U;

	if (msg_get_remaining_size(info) <
	    (psubmsg_hdr->octets_to_next_header + msg_get_submsg_header_raw_size())) {
		return false;
	}

	/* Desearilize from submessageId to numbits */
	current_pos = msg_get_cur_pos(info);
	size_before_bitmap = msg_get_submsg_acknack_size_before_bitmap();
	msg_do_copy((uint8_t *)msg, &current_pos, size_before_bitmap);

	if (msg->reader_sn_state.num_bits != 0U) {
		bitmap_size = msg_get_bitmap_size(msg->reader_sn_state.num_bits);

		if (bitmap_size > sizeof(msg->reader_sn_state.bitmap)) {
			pr_err(ERR_FAULT, "bitmap info error!\n");
			msg_do_copy((uint8_t *)(msg->reader_sn_state.bitmap),
				    &current_pos, sizeof(msg->reader_sn_state.bitmap));
			current_pos += bitmap_size - sizeof(msg->reader_sn_state.bitmap);
		} else {
			msg_do_copy((uint8_t *)(msg->reader_sn_state.bitmap),
				    &current_pos, bitmap_size);
		}
	}

	msg_do_copy((uint8_t *)(&(msg->msg_count)), &current_pos, sizeof(msg->msg_count));

	return true;
}

bool msg_des_submsg_gap(struct message_processing_info *info,
			struct submessage_gap *msg)
{
	uint16_t remain_size_at_begin = msg_get_remaining_size(info);

	if (remain_size_at_begin < msg_get_submsg_gap_raw_size_without_bitmap()) {
		return false;
	}

	if (!msg_des_submsg_header(info, &(msg->header))) {
		return false;
	}

	const uint8_t *current_pos = msg_get_cur_pos(info) +
				     msg_get_submsg_header_raw_size();

	msg_do_copy(msg->reader_id.entity_key, &current_pos,
			   sizeof(msg->reader_id.entity_key));

	msg->reader_id.entity_kind = (*current_pos);
	current_pos++;

	msg_do_copy(msg->writer_id.entity_key, &current_pos,
			   sizeof(msg->writer_id.entity_key));

	msg->writer_id.entity_kind = (*current_pos);
	current_pos++;

	msg_do_copy((uint8_t *)(&(msg->gap_start.high)), &current_pos,
			   sizeof(msg->gap_start.high));
	msg_do_copy((uint8_t *)(&(msg->gap_start.low)), &current_pos,
			   sizeof(msg->gap_start.low));
	msg_do_copy((uint8_t *)(&(msg->gap_list.base.high)),
			   &current_pos, sizeof(msg->gap_list.base.high));
	msg_do_copy((uint8_t *)(&(msg->gap_list.base.low)),
			   &current_pos, sizeof(msg->gap_list.base.low));
	msg_do_copy((uint8_t *)(&(msg->gap_list.num_bits)),
			   &current_pos, sizeof(uint32_t));

	if (remain_size_at_begin < msg_get_submsg_gap_raw_size(msg->gap_list)) {
		return false;
	}

	if (msg->gap_list.num_bits != 0U) {
		uint16_t bitmap_size = msg_get_bitmap_size(msg->gap_list.num_bits);

		if (bitmap_size > sizeof(msg->gap_list.bitmap)) {
			pr_err(ERR_FAULT, "bitmap info error!\n");
			msg_do_copy((uint8_t *)(msg->gap_list.bitmap), &current_pos,
			    sizeof(msg->gap_list.bitmap));
			current_pos += bitmap_size - sizeof(msg->gap_list.bitmap);
		} else {
			msg_do_copy((uint8_t *)(msg->gap_list.bitmap), &current_pos,
			    bitmap_size);
		}
	}

	return true;
}

bool msg_des_submsg_gap_payload(struct message_processing_info *info,
				const struct submessage_header *psubmsg_hdr,
				struct submessage_gap *msg)
{
	const uint8_t		*current_pos = NULL;
	uint16_t		size_before_bitmap = 0U;
	uint16_t		bitmap_size = 0U;

	if (msg_get_remaining_size(info) <
	    msg_get_submsg_header_raw_size() + psubmsg_hdr->octets_to_next_header) {
		return false;
	}

	current_pos = msg_get_cur_pos(info);
	size_before_bitmap = msg_get_submsg_heartbeat_size_before_bitmap();

	msg_do_copy((uint8_t *)msg, &current_pos, size_before_bitmap);

	if (msg->gap_list.num_bits != 0U) {
		bitmap_size = msg_get_bitmap_size(msg->gap_list.num_bits);

		if (bitmap_size > sizeof(msg->gap_list.bitmap)) {
			pr_err(ERR_FAULT, "bitmap info error!\n");
			msg_do_copy((uint8_t *)(msg->gap_list.bitmap), &current_pos,
				    sizeof(msg->gap_list.bitmap));
			current_pos += bitmap_size - sizeof(msg->gap_list.bitmap);
		} else {
			msg_do_copy((uint8_t *)(msg->gap_list.bitmap), &current_pos,
				    bitmap_size);
		}
	}

	return true;
}

bool msg_des_submsg_e2e(struct message_processing_info *info,
			struct submessage_e2e *msg)
{
	if (msg_get_remaining_size(info) < msg_get_submsg_e2e_raw_size()) {
		return false;
	}

	if (!msg_des_submsg_header(info, &(msg->header))) {
		return false;
	}

	const uint8_t *current_pos = msg_get_cur_pos(info) +
				     msg_get_submsg_header_raw_size();

	msg_do_copy((uint8_t *)(&(msg->length)), &current_pos,
				sizeof(msg->length));
	msg_do_copy((uint8_t *)(&(msg->crc)), &current_pos,
				sizeof(msg->crc));

	return true;
}

bool msg_des_submsg_e2e_payload(struct message_processing_info *info,
				struct submessage_e2e *msg)
{
	const uint8_t *current_pos = NULL;

	if (msg_get_remaining_size(info) < msg_get_submsg_e2e_raw_size()) {
		return false;
	}

	current_pos = msg_get_cur_pos(info);

	msg_do_copy((uint8_t *)msg, &current_pos, msg_get_submsg_e2e_raw_size());

	return true;
}

static uint16_t msg_get_submsg_header_raw_size_without_sn(void)
{
	return msg_get_submsg_header_raw_size() +
	       (uint16_t)((2 * 3) + (2 * 1)) /* EntityID */
	       + (uint16_t)sizeof(int32_t);
}

/*
 * submsg_acknack
 *	submsg header
 *	reader_id
 *	writer_id
 *	sn_set
 *	count
 */
uint16_t msg_get_submsg_acknack_raw_size(const struct rtps_sn_set set)
{
	uint16_t bitmap_size = msg_get_bitmap_size(set.num_bits);

	return msg_get_submsg_header_raw_size_without_sn() +
	       (uint16_t)sizeof(struct rtps_sn) + (uint16_t)sizeof(uint32_t) +
	       bitmap_size;
}

uint16_t msg_get_submsg_acknack_max_size(void)
{
	uint16_t bitmap_size = msg_get_bitmap_size(SNS_NUM_BITS);

	return msg_get_submsg_header_raw_size_without_sn() +
	       (uint16_t)sizeof(struct rtps_sn) + (uint16_t)sizeof(uint32_t) +
	       bitmap_size;
}

uint16_t msg_get_submsg_e2e_raw_size(void)
{
	return msg_get_submsg_header_raw_size() + msg_get_submsg_e2e_noheader_size();
}

/*
 * submsg_gap
 *	submsg header
 *	reader_id
 *	writer_id
 *	gap_start
 *	gap_list
 */
uint16_t msg_get_submsg_gap_raw_size(const struct rtps_sn_set set)
{
	uint16_t bitmap_size = msg_get_bitmap_size(set.num_bits);

	return msg_get_submsg_gap_raw_size_without_bitmap()
	       + bitmap_size;
}

uint16_t msg_get_submsg_gap_max_size(void)
{
	uint16_t bitmap_size = msg_get_bitmap_size(SNS_NUM_BITS);

	return msg_get_submsg_gap_raw_size_without_bitmap() + bitmap_size;
}

void msg_deser_config_opts(struct mvbs_cdr *buffer)
{
	uint8_t encapsulation[2]	= { 0 };
	const uint32_t len		= (uint32_t)ARRAY_SIZE(encapsulation);
	int32_t is_little_endian	= true; /* default is little endian */

	/* Endianness doesn't matter since those are single bytes */
	(void)mcdr_deserialize_array_uint8_t(buffer, encapsulation, len);

	for (uint8_t i = 0; i < len; i++) {
		if (encapsulation[i] != SCHEME_PL_CDR_LE[i]) {
			is_little_endian = false;
			break;
		}
	}

	(void)mcdr_buffer_set_little_endian(buffer, is_little_endian);

	/* Reuse encapsulation buffer to skip options */
	(void)mcdr_deserialize_array_uint8_t(buffer, encapsulation, len);
}

int32_t mcdr_init_from_serialized_payload(struct mvbs_cdr *cdr,
					  struct serialized_payload *payload)
{
	uint32_t psize;
	uint8_t *pdata;

	uint8_t *scheme;
	uint8_t *options;

	bool	is_little_endian;

	if ((cdr == NULL) || (payload == NULL))
		return -ERR_INVALID;

	if ((payload->data == NULL) || (payload->recv_size <= 4)) {
		return -ERR_INVALID;
	}

	scheme = (uint8_t *)payload->data;
	options = scheme + 2;

	if (scheme[1] == 0x00 || scheme[1] == 0x02) {
		is_little_endian = false;
	} else {
		is_little_endian = true;
	}

	pdata = (uint8_t *)payload->data + 4u;
	psize = payload->recv_size - 4u - options[1];

	mcdr_init_buffer_offset_endian(cdr, pdata, psize, 0U, is_little_endian);

	return 0;
}

int32_t mcdr_serialized_payload_header(struct mvbs_cdr *cdr,
			struct serialized_payload *payload)
{
	const uint32_t scheme_cdr_len = (const uint32_t)sizeof(SCHEME_CDR_LE);
	uint8_t zero_options[2] = {0x00, 0x00};

	uint32_t payload_data_size = mcdr_buffer_length(cdr);

	mcdr_align_to_uint32(cdr);

	payload->recv_size = mcdr_buffer_length(cdr) + 4;

	zero_options[1] =  mcdr_buffer_length(cdr) - payload_data_size;


	mcdr_init_buffer(cdr, payload->data, 4);

	if (!mcdr_serialize_array_uint8_t(cdr, SCHEME_CDR_LE, scheme_cdr_len)) {
		return false;
	}

	if (!mcdr_serialize_array_uint8_t(cdr, zero_options, (const uint32_t)2)) {
		return false;
	}

	return true;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
