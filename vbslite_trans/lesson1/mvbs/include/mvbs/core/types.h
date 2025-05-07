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

#ifndef MVBS_CORE_TYPES_H
#define MVBS_CORE_TYPES_H

#include <mvbs/base_type.h>
#include <mvbs/rtps/guid.h>

struct serialized_payload {
	uint32_t 	recv_size;
	uint32_t	length;
	const void	*data;
};

typedef int8_t				instance_id;
#define INSTANCE_INVALID		-1

struct instance_handle {
	uint8_t		value[16];
};

extern const struct instance_handle	HANDLE_NIL;

typedef uint8_t			timer_desc_t;
#define TIMER_DESC_INVALID	UINT8_MAX

struct mvbs_entity_info {
	struct rtps_guid	guid;
	char			*remote_name;
};

struct mvbs_e2e_info {
	uint32_t	e2e_status;
	uint16_t	counter;
};

struct mvbs_endpoint_stat {
	size_t	instances;
	size_t	remotes_online;		/* rw current remote endpoint(reader/writer) */
	size_t	total_remotes_online;	/* rw match count */
	size_t	total_remotes_offline;	/* rw unmatch count */
	size_t	deadline_timeout;
	size_t	sample_lost;
	size_t	sample_committed;
	size_t	sample_rejected;
	size_t	event_bitmap;		/* unused */
};

#ifdef __MVBS_CORE_SOURCE__

#define	RTPS_GLOBAL_VERBOSE		0
#define	SFW_VERBOSE			0
#define	SPDP_VERBOSE			0
#define	PBUF_WRAP_VERBOSE		0
#define	SEDP_VERBOSE			0
#define	RECV_VERBOSE			0
#define	PARTICIPANT_VERBOSE		0
#define	UDP_DRIVER_VERBOSE		0
#define	READER_VERBOSE			0
#define	READER_PROXY_VERBOSE		0
#define	WRITER_VERBOSE			0
#define	WRITER_PROXY_VERBOSE		0

#define	USER_DEFINED_UNKNOWN		0x00U
#define	USER_DEFINED_WRITER_WITH_KEY	0x02U
#define	USER_DEFINED_WRITER_WITHOUT_KEY	0x03U
#define	USER_DEFINED_READER_WITHOUT_KEY	0x04U
#define	USER_DEFINED_READER_WITH_KEY	0x07U

#define	BUILD_IN_UNKNOWN		0xc0U
#define	BUILD_IN_PARTICIPANT		0xc1U
#define	BUILD_IN_WRITER_WITH_KEY	0xc2U
#define	BUILD_IN_WRITER_WITHOUT_KEY	0xc3U
#define	BUILD_IN_READER_WITHOUT_KEY	0xc4U
#define	BUILD_IN_READER_WITH_KEY	0xc7U

#define	VENDOR_SPEC_UNKNOWN		0x40U
#define	VENDOR_SPEC_PARTICIPANT		0x41U
#define	VENDOR_SPEC_WRITER_WITH_KEY	0x42U
#define	VENDOR_SPEC_WRITER_WITHOUT_KEY	0x43U
#define	VENDOR_SPEC_READER_WITHOUT_KEY	0x44U
#define	VENDOR_SPEC_READER_WITH_KEY	0x47U

#define	TIME_T_INFINITE_SECONDS		0x7fffffff
#define	TIME_T_INFINITE_NANOSECONDS	0xffffffffU

#define	PROPERTY_MAX_LEN		16U   /* property name max length */
#define	PROPERTY_LIST_MAX_COUNT		50
#define	PROPERTY_COUNT_PERPKT		30

typedef enum {
	READER = 0,
	WRITER = 1
} EndpointKind_t;

struct rtps_property {
	char name[PROPERTY_MAX_LEN];
	char value[PROPERTY_MAX_LEN];
};

struct rtps_property_info {
	struct rtps_property *property_list;
	uint8_t valid_count;
	uint8_t max_count;
};

/* Default Values */
extern const struct rtps_entity_id	ENTITYID_UNKNOWN;
extern const struct rtps_entity_id	ENTITYID_SEDP_BUILTIN_TOPIC_WRITER;
extern const struct rtps_entity_id	ENTITYID_SEDP_BUILTIN_TOPIC_READER;
extern const struct rtps_entity_id	ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER;
extern const struct rtps_entity_id	ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER;
extern const struct rtps_entity_id	ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER;
extern const struct rtps_entity_id	ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER;
extern const struct rtps_entity_id	ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER;
extern const struct rtps_entity_id	ENTITYID_SPDP_BUILTIN_PARTICIPANT_READER;
extern const struct rtps_entity_id	ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_WRITER;
extern const struct rtps_entity_id	ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_READER;

extern const struct rtps_entity_id	ENTITYID_BUILD_IN_PARTICIPANT;

extern const struct rtps_entity_id	ENTITYID_DIAG_REQUEST_WRITER;
extern const struct rtps_entity_id	ENTITYID_DIAG_REQUEST_READER;
extern const struct rtps_entity_id	ENTITYID_DIAG_REPLY_WRITER;
extern const struct rtps_entity_id	ENTITYID_DIAG_REPLY_READER;

extern const struct rtps_guid_prefix	GUIDPREFIX_UNKNOWN;
extern const struct rtps_guid		GUID_UNKNOWN;

extern const int8_t			PARTICIPANT_ID_INVALID;

extern const struct rtps_version	PROTOCOLVERSION;

extern const struct rtps_vendor_id	VENDOR_UNKNOWN;
extern const struct rtps_vendor_id	VENDOR_ID;

#endif
#endif
