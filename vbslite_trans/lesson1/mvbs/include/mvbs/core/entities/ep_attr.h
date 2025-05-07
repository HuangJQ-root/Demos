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

#ifndef MVBS_CORE_ENTITIES_EP_ATTR_H
#define MVBS_CORE_ENTITIES_EP_ATTR_H

#include <mvbs/base_type.h>
#include <mvbs/rtps/guid.h>
#include <mvbs/core/types.h>
#include <mvbs/core/qos/qos.h>
#include <mvbs/core/transport/locator.h>

#define MAX_TYPENAME_LENGTH		128U
#define MAX_TOPICNAME_LENGTH		64U
#define MAX_CRC16_LENGTH		5U

struct type_plugin {
	const char	*name;

	bool	 (*serialize)(void *data, struct serialized_payload *payload);
	bool	 (*deserialize)(void *data, struct serialized_payload *payload);

	uint32_t (*type_size)(void);

	char	crc16[MAX_CRC16_LENGTH];
};
struct endpoint_info {
	char topic_name[MAX_TOPICNAME_LENGTH];
	char type_name[MAX_TYPENAME_LENGTH];
	uint32_t			agent_flag;

	struct rtps_guid		ep_guid;
	struct rtps_guid		guid_from_key_hash;

	locator_t			mc;
	locator_t			uc;

	struct {
		uint16_t		reliability_kind:2;
		uint16_t		durability_kind:2;
		uint16_t		ownership_kind:2;
		uint16_t		liveliness_kind:2;
		uint16_t		history_kind:2;
	} qos;

	struct history_policy		history;
	struct reliability_policy	reliability;
	struct deadline_policy		deadline;
	struct liveliness_policy	liveliness;
	struct e2e_policy		e2e;
	uint32_t			ownership_strength;

	uint32_t			status_info;

	char				crc16[MAX_CRC16_LENGTH];

	uint16_t			locator_selector:4;
	uint16_t			backup_enabled:1;
	uint16_t			crc16_enabled:1;
};

typedef struct endpoint_info		endpoint_info_t;

struct endpoint_attr {
	char topic_name[MAX_TOPICNAME_LENGTH];
	const struct type_plugin		*type;
	uint32_t				agent_flag;
	uint16_t				period_ms;

	struct {
		uint16_t reliability_kind:2;
		uint16_t durability_kind:2;
		uint16_t ownership_kind:2;
		uint16_t liveliness_kind:2;
		uint16_t history_kind:2;
	} qos;

	struct history_policy			history;
	struct ownership_strength_policy	ownership_strength;
	struct reliability_policy		reliability;
	struct liveliness_policy		liveliness;
	struct resource_limit_policy		resource_limit;
	struct lifespan_policy			lifespan;
	struct e2e_policy			e2e;
	struct deadline_policy			deadline;

	uint16_t		entity_id;
	int16_t			user_defined_id; /* Used by static discovery */

	uint16_t		locator_selector:4;
	uint16_t		backup_enabled:1;
	uint16_t		crc16_enabled:1;
	uint8_t			recorder_cfg:2;
};

typedef struct endpoint_attr		endpoint_attr_t;


#define EP_ATTR_MEMBER_CLR()							\
	.topic_name					= {'\0'},		\
	.agent_flag 					= 0,			\
	.qos = {								\
		.reliability_kind			= 0,			\
		.durability_kind			= 0,			\
		.ownership_kind				= 0,			\
		.liveliness_kind			= 0,			\
		.history_kind				= 0,			\
	},									\
	.history.depth 					= 0,			\
	.ownership_strength.value 			= 0,			\
	.reliability.max_blocking_time			= {0, 0},		\
	.liveliness = {								\
		.lease_duration 			= {0, 0},		\
		.announcement_period 			= {0, 0},		\
	},									\
	.resource_limit = {							\
		.max_samples 				= 0,			\
		.max_instances 				= 0,			\
		.max_samples_per_instance		= 0,			\
	},									\
	.lifespan.duration 				= {0, 0},		\
	.e2e = {								\
		.e2e_protection				= 0,			\
		.e2e_p04_min_data_length		= 0,			\
		.e2e_p04_max_data_length		= 0,			\
		.e2e_p04_max_delta_counter		= 0,			\
		.e2e_liveliness_lease_duration		= {0, 0},		\
		.e2e_liveliness_kind			= 0,			\
		.e2e_deadline_counter			= 0,			\
	},									\
	.deadline.duration 				= {0, 0},		\
	.entity_id 					= 0,			\
	.user_defined_id 				= 0,			\
	.locator_selector 				= 0,			\
	.backup_enabled 				= 0,			\
	.crc16_enabled 					= 0,			\
	.recorder_cfg					= 0


#define EP_ATTR_INIT()								\
{										\
	EP_ATTR_MEMBER_CLR(),							\
}

void ep_attr_init(endpoint_attr_t *ep_attr, const char *topic);

bool ep_attr_match(const endpoint_attr_t *wr_ep, const endpoint_attr_t *rd_ep);

#endif
