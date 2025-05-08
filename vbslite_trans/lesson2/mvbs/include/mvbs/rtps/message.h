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

#ifndef MVBS_RTPS_MESSAGE_H
#define MVBS_RTPS_MESSAGE_H

#include <mvbs/base_type.h>
#include <mvbs/rtps/guid.h>
#include <mvbs/rtps/time.h>
#include <mvbs/rtps/sequence_number.h>

#define MVBS_DES_TURBO

struct mvbs_cdr;

extern const uint8_t		SCHEME_CDR_LE[2];

/* TODO endian */
typedef uint16_t		ParameterId_t;

#define	PID_PAD						0x0000
#define	PID_SENTINEL					0x0001
#define	PID_USER_DATA					0x002c
#define	PID_TOPIC_NAME					0x0005
#define	PID_TYPE_NAME					0x0007
#define	PID_GROUP_DATA					0x002d
#define	PID_TOPIC_DATA					0x002e
#define	PID_DURABILITY					0x001d
#define	PID_DURABILITY_SERVICE				0x001e
#define	PID_DEADLINE					0x0023
#define	PID_LATENCY_BUDGET				0x0027
#define	PID_LIVELINESS					0x001b
#define	PID_RELIABILITY					0x001a
#define	PID_LIFESPAN					0x002b
#define	PID_DESTINATION_ORDER				0x0025
#define	PID_HISTORY					0x0040
#define	PID_RESOURCE_LIMITS				0x0041
#define	PID_OWNERSHIP					0x001f
#define	PID_OWNERSHIP_STRENGTH				0x0006
#define	PID_PRESENTATION				0x0021
#define	PID_PARTITION					0x0029
#define	PID_TIME_BASED_FILTER				0x0004
#define	PID_TRANSPORT_PRIORITY				0x0049
#define	PID_PROTOCOL_VERSION				0x0015
#define	PID_VENDORID					0x0016
#define	PID_UNICAST_LOCATOR				0x002f
#define	PID_MULTICAST_LOCATOR				0x0030
#define	PID_MULTICAST_IPADDRESS				0x0011
#define	PID_DEFAULT_UNICAST_LOCATOR			0x0031
#define	PID_DEFAULT_MULTICAST_LOCATOR			0x0048
#define	PID_METATRAFFIC_UNICAST_LOCATOR			0x0032
#define	PID_METATRAFFIC_MULTICAST_LOCATOR		0x0033
#define	PID_DEFAULT_UNICAST_IPADDRESS			0x000c
#define	PID_DEFAULT_UNICAST_PORT			0x000e
#define	PID_METATRAFFIC_UNICAST_IPADDRESS		0x0045
#define	PID_METATRAFFIC_UNICAST_PORT			0x000d
#define	PID_METATRAFFIC_MULTICAST_IPADDRESS		0x000b
#define	PID_METATRAFFIC_MULTICAST_PORT			0x0046
#define	PID_EXPECTS_INLINE_QOS				0x0043
#define	PID_PARTICIPANT_MANUAL_LIVELINESS_COUNT		0x0034
#define	PID_PARTICIPANT_BUILTIN_ENDPOINTS		0x0044
#define	PID_PARTICIPANT_LEASE_DURATION			0x0002
#define	PID_CONTENT_FILTER_PROPERTY			0x0035
#define	PID_PARTICIPANT_GUID				0x0050
#define	PID_PARTICIPANT_ENTITYID			0x0051
#define	PID_GROUP_GUID					0x0052
#define	PID_GROUP_ENTITYID				0x0053
#define	PID_BUILTIN_ENDPOINT_SET			0x0058
#define	PID_PROPERTY_LIST				0x0059
#define	PID_ENDPOINT_GUID				0x005a
#define	PID_TYPE_MAX_SIZE_SERIALIZED			0x0060
#define	PID_ENTITY_NAME					0x0062
#define	PID_KEY_HASH					0x0070
#define	PID_STATUS_INFO					0x0071
#define	PID_E2E_PROTECTION				0x9001
#define	PID_CRC16_IDL					0x9005
#define	PID_SESSION_ID					0x9006
#define	PID_VBS_VERTION					0x9007
#define	PID_AGENT_ENDPOINT				0x900c

#define	DISC_BIE_PARTICIPANT_ANNOUNCER			0x001U
#define	DISC_BIE_PARTICIPANT_DETECTOR			0x002U
#define	DISC_BIE_PUBLICATION_ANNOUNCER			0x004U
#define	DISC_BIE_PUBLICATION_DETECTOR			0x008U
#define	DISC_BIE_SUBSCRIPTION_ANNOUNCER			0x010U
#define	DISC_BIE_SUBSCRIPTION_DETECTOR			0x020U
#define	DISC_BIE_PARTICIPANT_PROXY_ANNOUNCER		0x040U
#define	DISC_BIE_PARTICIPANT_PROXY_DETECTOR		0x080U
#define	DISC_BIE_PARTICIPANT_STATE_ANNOUNCER		0x100U
#define	DISC_BIE_PARTICIPANT_STATE_DETECTOR		0x200U
#define	BIE_PARTICIPANT_MESSAGE_DATA_WRITER		0x400U
#define	BIE_PARTICIPANT_MESSAGE_DATA_READER		0x800U

#define	DISC_BIE_DIAG_REQUEST_WRITER			0x1000U
#define	DISC_BIE_DIAG_REQUEST_READER			0x2000U
#define	DISC_BIE_DIAG_REPLY_WRITER			0x4000U
#define	DISC_BIE_DIAG_REPLY_READER			0x8000U

/* TODO endian */
extern const uint8_t			SCHEME_PL_CDR_LE[2];
#define SCHEME_PL_CDR_LE_SIZE		ARRAY_SIZE(SCHEME_PL_CDR_LE)

#define PAD						0x01 /* Pad */
#define ACKNACK						0x06 /* AckNack */
#define HEARTBEAT					0x07 /* Heartbeat */
#define GAP						0x08 /* Gap */
#define INFO_TS						0x09 /* InfoTimestamp */
#define INFO_SRC					0x0c /* InfoSource */
#define INFO_REPLY_IP4					0x0d /* InfoReplyIp4 */
#define INFO_DST					0x0e /* InfoDestination */
#define INFO_REPLY					0x0f /* InfoReply */
#define NACK_FRAG					0x12 /* NackFrag */
#define HEARTBEAT_FRAG					0x13 /* HeartbeatFrag */
#define DATA						0x15 /* Data */
#define DATA_FRAG					0x16 /* DataFrag */
#define INFO_E2E					0xf0 /*E2E*/

typedef uint8_t SubMessageFlag_t;

#define FLAG_ENDIANESS					(uint8_t)(1U << 0U)
#define FLAG_BIG_ENDIAN					(uint8_t)(0U << 0U)
#define FLAG_LITTLE_ENDIAN				(uint8_t)(1U << 0U)
#define FLAG_INVALIDATE					(uint8_t)(1U << 1U)
#define FLAG_INLINE_QOS					(uint8_t)(1U << 1U)
#define FLAG_NO_PAYLOAD					(uint8_t)((0U << 3U) | (0U << 2U))
#define FLAG_DATA_PAYLOAD				(uint8_t)((0U << 3U) | (1U << 2U))
#define FLAG_FINAL					(uint8_t)(1U << 1U)
#define FLAG_HB_LIVELINESS				(uint8_t)(1U << 2U)

#ifdef MVBS_BIG_ENDIAN
#define FLAG_MVBS_ENDIANESS				(uint8_t)FLAG_BIG_ENDIAN
#else
#define FLAG_MVBS_ENDIANESS				(uint8_t)FLAG_LITTLE_ENDIAN
#endif

extern const char		RTPS_PROTOCOL_NAME[4];

struct message_header {
	uint8_t			protocol_name[4];
	struct rtps_version	protocol_version;
	struct rtps_vendor_id	vendor_id;
	struct rtps_guid_prefix	ptcp_guid_prefix;
} __attribute__((packed));

struct submessage_header {
	uint8_t			submessage_id;
	uint8_t			flags;
	uint16_t		octets_to_next_header;
} __attribute__((packed));

struct submessage_data {
	struct submessage_header	header;

#define	EXTRA_FLAGS_NORMAL		0U
#define	EXTRA_FLAGS_RECORDER_DATA	1U
#define	EXTRA_FLAGS_RECORDER_CMD	2U

	uint16_t			extra_flags;
	uint16_t			octets_to_inlineqos;

	struct rtps_entity_id		reader_id;
	struct rtps_entity_id		writer_id;

	struct rtps_sn			writer_sn;
};

struct submessage_heartbeat {
	struct submessage_header	header;

	struct rtps_entity_id		reader_id;
	struct rtps_entity_id		writer_id;

	struct rtps_sn			first_sn;
	struct rtps_sn			last_sn;

	int32_t				msg_count;
};

struct submessage_acknack {
	struct submessage_header	header;

	struct rtps_entity_id		reader_id;
	struct rtps_entity_id		writer_id;

	struct rtps_sn_set		reader_sn_state;

	int32_t				msg_count;
};

struct submessage_gap {
	struct submessage_header	header;

	struct rtps_entity_id		reader_id;
	struct rtps_entity_id		writer_id;

	struct rtps_sn			gap_start;
	struct rtps_sn_set		gap_list;
};

struct submessage_time {
	struct submessage_header	header;

	struct rtps_time		rtps_timestamp;
};

struct submessage_e2e {
	struct submessage_header	header;

	uint32_t			length;
	uint32_t			crc;
};

struct message_processing_info {
	const uint8_t			*data;
	uint16_t			size;
	uint16_t			next_pos;
};

/*
 * according rtps v2.5: if fistsn <= 0 or lastsn < 0 or lastsn < firstsn -1,
 * the hearbeat is invalid
 */
static inline bool msg_submsg_heartbeat_is_invalid(struct submessage_heartbeat *msg)
{
	struct rtps_sn zero_seq = {0, 0};
	struct rtps_sn fisrt_cmp = rtps_sn_sub_value(&msg->first_sn, 1);

	return (rtps_sn_lessequal(&msg->first_sn, &zero_seq) ||
		rtps_sn_less(&msg->last_sn, &zero_seq) ||
		rtps_sn_less(&msg->last_sn, &fisrt_cmp));
}

/*
 * msg header:
 *	protocol name
 *	protocol version
 *	vendor id
 *	guid_prefix
 */
static inline uint16_t msg_get_header_raw_size(void)
{
	return 4u + (uint16_t)sizeof(struct rtps_version)
		  + (uint16_t)sizeof(struct rtps_vendor_id)
		  + (uint16_t)sizeof(struct rtps_guid_prefix);
}

/*
 * submsg header:
 *	submessage_id
 *	flags
 *	octets_to_next_header
 */
static inline uint16_t msg_get_submsg_header_raw_size(void)
{
	return (uint16_t)(sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint16_t));
}

/*
 * submsg time:
 *	submsg header
 *	time
 */
static inline uint16_t msg_get_submsg_time_raw_size(void)
{
	return msg_get_submsg_header_raw_size() + (uint16_t)sizeof(struct rtps_time);
}

/*
 * submsg data:
 *	submsg header
 *	extra_flags
 *	octets_to_inlineqos
 *	reader_id
 *	writer_id
 *	writer_sn
 */
static inline uint16_t msg_get_submsg_data_raw_size(void)
{
	return msg_get_submsg_header_raw_size()
		+ (uint16_t)sizeof(uint16_t)
		+ (uint16_t)sizeof(uint16_t) + (uint16_t)((2u * 3u) + (2u * 1u)) /* EntityID */
		+ (uint16_t)sizeof(struct rtps_sn);
}

/*
 * submsg heartbeat
 *	submsg header
 *	reader_id
 *	writer_id
 *	first_sn
 *	last_sn
 *	count
 */
static inline uint16_t msg_get_submsg_heartbeat_raw_size(void)
{
	return msg_get_submsg_header_raw_size()
		+ ((2u * 3u) + (2u * 1u)) /* EntityID */
		+ (2u * (uint16_t)sizeof(struct rtps_sn))
		+ (uint16_t)sizeof(int32_t);
}

static inline uint16_t msg_get_submsg_e2e_noheader_size(void)
{
	/* datalength + crc */
	return 4u + 4u;
}

static inline uint16_t msg_get_submsg_gap_raw_size_without_bitmap(void)
{
	return msg_get_submsg_header_raw_size()
		+ ((2u * 3u) + (2u * 1u)) /* EntityID */
		+ (2u * (uint16_t)sizeof(struct rtps_sn))
		+ (uint16_t)sizeof(uint32_t);
}

/*
 * submsg_acknack
 *	submsg header
 *	  |_    submessage_id
 *	  |_    flags
 *	  |_    octets_to_next_header
 *	reader_id
 *	writer_id
 *	sn_set
 *	  |_    base
 *	  |_    numbits
 *	  |_    bitmap[0-4]
 *	count
 */
static inline uint16_t msg_get_submsg_acknack_size_before_bitmap(void)
{
	return msg_get_submsg_header_raw_size() + (sizeof(struct rtps_entity_id) * 2) +
	       sizeof(struct rtps_sn) + sizeof(uint32_t);
}

static inline uint16_t msg_get_submsg_heartbeat_size_before_bitmap(void)
{
	return msg_get_submsg_header_raw_size() + (sizeof(struct rtps_entity_id) * 2) +
	       sizeof(struct rtps_sn) + sizeof(struct rtps_sn) +
	       sizeof(uint32_t);
}

static inline bool msg_acknack_is_preemtive(const struct submessage_acknack *msg)
{
	if ((msg->reader_sn_state.base.high == 0) &&
		(msg->reader_sn_state.base.low == 0U) &&
		(msg->reader_sn_state.num_bits == 0U))  /* preemptive ACKNACK */
	{
		return true;
	}

	return false;
}

const uint8_t *msg_get_cur_pos(const struct message_processing_info *pinfo);
uint16_t msg_get_submsg_acknack_raw_size(const struct rtps_sn_set set);
uint16_t msg_get_submsg_acknack_max_size(void);
uint16_t msg_get_submsg_gap_raw_size(const struct rtps_sn_set set);
uint16_t msg_get_submsg_gap_max_size(void);
uint16_t msg_get_submsg_e2e_raw_size(void);

bool msg_des_header(struct message_processing_info *info, struct message_header *header);
bool msg_des_submsg_header(struct message_processing_info *info,
			   struct submessage_header *header);
bool msg_des_submsg_data(struct message_processing_info *info,
			 const struct submessage_header *psubmsg_hdr,
			 struct submessage_data *msg);

bool msg_des_submsg_heartbeat(struct message_processing_info *info,
			      struct submessage_heartbeat *msg);
bool msg_des_submsg_heartbeat_payload(struct message_processing_info *info,
				      struct submessage_heartbeat *msg);

bool msg_des_submsg_acknack(struct message_processing_info *info,
			    struct submessage_acknack *msg);
bool msg_des_submsg_acknack_payload(struct message_processing_info *info,
				    const struct submessage_header *psubmsg_hdr,
				    struct submessage_acknack *msg);

bool msg_des_submsg_gap(struct message_processing_info *info, struct submessage_gap *msg);
bool msg_des_submsg_gap_payload(struct message_processing_info *info,
				const struct submessage_header *psubmsg_hdr,
				struct submessage_gap *msg);

bool msg_des_submsg_e2e(struct message_processing_info *info, struct submessage_e2e *msg);
bool msg_des_submsg_e2e_payload(struct message_processing_info *info,
				struct submessage_e2e *msg);

bool msg_des_submsg_time_payload(struct message_processing_info *info,
				 const struct submessage_header *psubmsg_hdr,
				 struct rtps_time *timestamp);
bool msg_des_submsg_time(struct message_processing_info *info,
			 struct submessage_time *msg);

void msg_deser_config_opts(struct mvbs_cdr *buffer);



#endif /* !__MVBS_RTPS_MESSAGE_H__ */
