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
#include <rpc/rpc.h>

int32_t rpc_header_serialize(struct mvbs_cdr *mcdr_stream,
			 uint32_t msg_type, uint32_t seq_no, uint32_t body_len)
{
	uint32_t magic		= RPC_HEAD_MAGIC;
	uint32_t reserve[4]	= {0};

	if (mcdr_stream == NULL) {
		return -ERR_INVALID;
	}

	if (!mcdr_serialize_uint32_t(mcdr_stream, magic)) {
		return -ERR_MCDR;
	}

	if (!mcdr_serialize_uint32_t(mcdr_stream, msg_type)) {
		return -ERR_MCDR;
	}

	if (!mcdr_serialize_uint32_t(mcdr_stream, seq_no)) {
		return -ERR_MCDR;
	}

	if (!mcdr_serialize_uint32_t(mcdr_stream, body_len)) {
		return -ERR_MCDR;
	}

	if (!mcdr_serialize_array_uint32_t(mcdr_stream, reserve, 4)) {
		return -ERR_MCDR;
	}

	return 0;
}

int32_t rpc_header_deserialize(struct mvbs_cdr *mcdr_stream, struct rpc_header *header)
{
	uint32_t reserve[4] = {0};

	if ((mcdr_stream == NULL) || (header == NULL)) {
		return -ERR_INVALID;
	}

	if (!mcdr_deserialize_uint32_t(mcdr_stream, &header->magic_num)) {
		return -ERR_MCDR;
	}

	if (!mcdr_deserialize_uint32_t(mcdr_stream, &header->msg_type)) {
		return -ERR_MCDR;
	}

	if (!mcdr_deserialize_uint32_t(mcdr_stream, &header->sn)) {
		return -ERR_MCDR;
	}

	if (!mcdr_deserialize_uint32_t(mcdr_stream, &header->body_len)) {
		return -ERR_MCDR;
	}

	if (!mcdr_deserialize_array_uint32_t(mcdr_stream, reserve, 4)) {
		return -ERR_MCDR;
	}

	return 0;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
