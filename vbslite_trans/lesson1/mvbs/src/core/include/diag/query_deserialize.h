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

#ifndef MVBS_DIAG_QUERY_DESERIALIZE_H
#define MVBS_DIAG_QUERY_DESERIALIZE_H

#include <core/core.h>
#include <mvbs/rtps/guid.h>

#define GET_PTCP_WR_INFO		0x40001001
#define	GET_WR_MATCH_GUIDS		0x40001002
#define	GET_W_SEND_INFO			0x40001003
#define GET_R_RECV_INFO			0x40001004
#define GET_TOPIC_INFO			0x40001005


static inline void query_deserialize_guid(struct mvbs_cdr *cdr,
					  struct rtps_guid *id)
{
	mcdr_deserialize_array_uint8_t(cdr, (void *)id, (uint32_t)sizeof(*id));
}

/* reply */
void query_deserialize_diag_reply(struct mvbs_cdr *cdr,
				struct rtps_guid *writer_guid,
				struct rtps_sn *sn,
				struct rtps_guid *reader_guid,
				int32_t *cmd_kind,
				uint16_t size);


#endif // MVBS_DIAG_QUERY_DESERIALIZE_H
