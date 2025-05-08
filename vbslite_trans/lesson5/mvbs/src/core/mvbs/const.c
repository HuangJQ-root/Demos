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
#include <mvbs/mvbs.h>

#define HANDLE_NIL_NATIVE		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

const struct instance_handle HANDLE_NIL = {
	.value = HANDLE_NIL_NATIVE,
};

const int32_t  DURATION_INFINITE_SEC	= 0x7fffffff;
const uint32_t DURATION_INFINITE_NSEC	= 0x7fffffffu;
const int32_t  DURATION_ZERO_SEC;
const uint32_t DURATION_ZERO_NSEC;

const struct rtps_time RTPS_TIME_ZERO = {
	.seconds = 0,
	.nanosec = 0
};

const struct rtps_time RTPS_TIME_INVALID = {
	.seconds = RTPS_TIME_INVALID_SEC,
	.nanosec = RTPS_TIME_INVALID_NSEC
};

const struct rtps_time RTPS_TIME_INFINITE = {
	.seconds = RTPS_TIME_INFINITE_SEC,
	.nanosec = RTPS_TIME_INFINITE_NSEC
};

const uint8_t SCHEME_CDR_LE[2] = {0x00, 0x01};

const duration_t SPDP_DEFAULT_REMOTE_LEASE_DURATION = {
	.seconds = 100,
	.nanosec = 0
};

const duration_t SPDP_MAX_REMOTE_LEASE_DURATION = {
	.seconds = 180,
	.nanosec = 0
};

const struct rtps_entity_id ENTITYID_UNKNOWN = {
	.entity_key  = { 0 },
	.entity_kind = USER_DEFINED_UNKNOWN
};

const struct rtps_entity_id ENTITYID_BUILD_IN_PARTICIPANT = {
	.entity_key  = { 0, 0, 1 },
	.entity_kind = BUILD_IN_PARTICIPANT
};

const struct rtps_entity_id ENTITYID_SEDP_BUILTIN_TOPIC_WRITER = {
	.entity_key  = { 0, 0, 2 },
	.entity_kind = BUILD_IN_WRITER_WITH_KEY
};

const struct rtps_entity_id ENTITYID_SEDP_BUILTIN_TOPIC_READER = {
	.entity_key  = { 0, 0, 2 },
	.entity_kind = BUILD_IN_READER_WITH_KEY
};

const struct rtps_entity_id ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER = {
	.entity_key  = { 0, 0, 3 },
	.entity_kind = BUILD_IN_WRITER_WITH_KEY
};

const struct rtps_entity_id ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER = {
	.entity_key  = { 0, 0, 3 },
	.entity_kind = BUILD_IN_READER_WITH_KEY
};

const struct rtps_entity_id ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER = {
	.entity_key  = { 0, 0, 4 },
	.entity_kind = BUILD_IN_WRITER_WITH_KEY
};

const struct rtps_entity_id ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER = {
	.entity_key  = { 0, 0, 4 },
	.entity_kind = BUILD_IN_READER_WITH_KEY
};

const struct rtps_entity_id ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER = {
	.entity_key  = { 0, 1, 0 },
	.entity_kind = BUILD_IN_WRITER_WITH_KEY
};

const struct rtps_entity_id ENTITYID_SPDP_BUILTIN_PARTICIPANT_READER = {
	.entity_key  = { 0, 1, 0 },
	.entity_kind = BUILD_IN_READER_WITH_KEY
};

const struct rtps_entity_id ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_WRITER = {
	.entity_key  = { 0, 2, 0 },
	.entity_kind = BUILD_IN_WRITER_WITH_KEY
};

const struct rtps_entity_id ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_READER = {
	.entity_key  = { 0, 2, 0 },
	.entity_kind = BUILD_IN_READER_WITH_KEY
};

const struct rtps_entity_id ENTITYID_DIAG_REQUEST_WRITER = {
	.entity_key = { 0, 3, 0 },
	.entity_kind = BUILD_IN_WRITER_WITHOUT_KEY
};

const struct rtps_entity_id ENTITYID_DIAG_REQUEST_READER = {
	.entity_key = { 0, 3, 0 },
	.entity_kind = BUILD_IN_READER_WITHOUT_KEY
};

const struct rtps_entity_id ENTITYID_DIAG_REPLY_READER = {
	.entity_key = { 0, 3, 1 },
	.entity_kind = BUILD_IN_READER_WITHOUT_KEY
};

const struct rtps_entity_id ENTITYID_DIAG_REPLY_WRITER = {
	.entity_key = { 0, 3, 1 },
	.entity_kind = BUILD_IN_WRITER_WITHOUT_KEY
};

const struct rtps_guid_prefix GUIDPREFIX_UNKNOWN = {
	.id = { 0 }
};

const struct rtps_guid GUID_UNKNOWN = {
	.prefix = {
		.id          = { 0 }
	},
	.eid    = {
		.entity_key  = { 0 },
		.entity_kind = USER_DEFINED_UNKNOWN
	}
};

const int8_t PARTICIPANT_ID_INVALID = -1;

const struct rtps_version PROTOCOLVERSION = {
	.major = 2,
	.minor = 3
};

const struct rtps_sn RTPS_SN_UNKNOWN = {
	.high = -1,
	.low  = 0U
};

const struct rtps_vendor_id VENDOR_ID = {
	.id = {MVBS_VENDOR_ID_HIGH, MVBS_VENDOR_ID_LOW}
};

const struct rtps_vendor_id VENDOR_UNKNOWN = {
	.id = { 0x0, 0x0 }
};


#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
