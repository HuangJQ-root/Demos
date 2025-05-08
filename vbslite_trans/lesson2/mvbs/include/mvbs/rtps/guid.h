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

#ifndef MVBS_RTPS_GUID_H
#define MVBS_RTPS_GUID_H

#include <mvbs/base_type.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/log.h>

struct rtps_vendor_id {
	uint8_t id[2];
} __attribute__((packed));

struct rtps_version {
	uint8_t major;
	uint8_t minor;
} __attribute__((packed));


struct rtps_guid_prefix {
#define HOST_ID_OFF		0U
#define APP_ID_OFF		4U
#define INSTANCE_ID_OFF		8U

	uint8_t			id[12];
} __attribute__((packed));

struct rtps_entity_id {
	uint8_t			entity_key[3];
	uint8_t			entity_kind;
} __attribute__((packed));

struct rtps_guid {
	struct rtps_guid_prefix	prefix;
	struct rtps_entity_id	eid;
} __attribute__((packed));

typedef struct rtps_guid_prefix 		rtps_guid_prefix_t;
typedef struct rtps_entity_id			rtps_entity_id_t;
typedef struct rtps_guid			rtps_guid_t;

#define GUID_PREFIX_HOST_ID_FMT			"[%02X %02X %02X %02X]"
#define GUID_PREFIX_APP_ID_FMT			"[%02X %02X %02X %02X]"
#define GUID_PREFIX_INST_ID_FMT			"[%02X %02X %02X %02X]"
#define GUID_PREFIX_FMT				GUID_PREFIX_HOST_ID_FMT " "	\
						GUID_PREFIX_APP_ID_FMT " "	\
						GUID_PREFIX_INST_ID_FMT

#define GUID_PREFIX_HOST_ID_PARTS(id)		id[0], id[1], id[2], id[3]
#define GUID_PREFIX_APP_ID_PARTS(id)		id[4], id[5], id[6], id[7]
#define GUID_PREFIX_INST_ID_PARTS(id)		id[8], id[9], id[10], id[11]
#define GUID_PREFIX_PARTS(id)			GUID_PREFIX_HOST_ID_PARTS(id),	\
                                                GUID_PREFIX_APP_ID_PARTS(id),	\
                                                GUID_PREFIX_INST_ID_PARTS(id)

static inline void rtps_guid_prefix_print(struct rtps_guid_prefix prefix)
{
	pr_verb("[guid_prefix]: " GUID_PREFIX_FMT,
				  GUID_PREFIX_PARTS(prefix.id));
}


#define ENTITY_ID_FMT				"%02X %02X %02X: %02X"
#define ENTITY_ID_PARTS(eid)			eid.entity_key[0], \
						eid.entity_key[1], \
						eid.entity_key[2], \
						eid.entity_kind

static inline void rtps_entity_id_print(struct rtps_entity_id id)
{
	pr_verb("[entity_id]: " ENTITY_ID_FMT, ENTITY_ID_PARTS(id));
}

static inline void rtps_guid_print(struct rtps_guid *id)
{
	rtps_guid_prefix_print(id->prefix);
	rtps_entity_id_print(id->eid);
}

static inline bool rtps_guid_prefix_equal(const struct rtps_guid_prefix *id1,
					  const struct rtps_guid_prefix *id2)
{
	return mvbs_memcmp((const void *)id1, (const void *)id2, sizeof(*id1)) == 0;
}

static inline bool rtps_guid_equal(const struct rtps_guid *id1,
				   const struct rtps_guid *id2)
{
	return mvbs_memcmp((const void *)id1, (const void *)id2, sizeof(*id1)) == 0;
}

static inline bool rtps_entity_id_equal(const struct rtps_entity_id *eid1,
					const struct rtps_entity_id *eid2)
{
	return mvbs_memcmp((const void *)eid1, (const void *)eid2, sizeof(*eid1)) == 0;
}

static inline void rtps_entity_id_set_key(struct rtps_entity_id *id, uint32_t key)
{
	id->entity_key[0] = (uint8_t)(key>>16);
	id->entity_key[1] = (uint8_t)(key>>8);
	id->entity_key[2] = (uint8_t)(key>>0);
}

static inline uint32_t rtps_entity_id_get_key(struct rtps_entity_id id)
{
	return (id.entity_key[0] << 16) | (id.entity_key[1] << 8)
					| (id.entity_key[2]);
}

#endif /* !__MVBS_RTPS_GUID_H__ */
