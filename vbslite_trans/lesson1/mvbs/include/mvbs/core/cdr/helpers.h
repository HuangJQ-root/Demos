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

#ifndef MVBS_CORE_CDR_HELPERS_H
#define MVBS_CORE_CDR_HELPERS_H

#include <mvbs/base_type.h>
#include <mvbs/core/types.h>
#include <mvbs/core/transport/locator.h>
#include <mvbs/rtps/time.h>
#include <mcdr/mcdr.h>

int32_t	mcdr_serialized_payload_header(struct mvbs_cdr *cdr,
					struct serialized_payload *payload);

int32_t mcdr_init_from_serialized_payload(struct mvbs_cdr *cdr,
					  struct serialized_payload *payload);

int32_t cdr_serialize_liveliness_msg(struct mvbs_cdr *cdr,
				     struct instance_handle instance);

int32_t cdr_serialize_locator(struct mvbs_cdr *cdr, locator_t *loc, uint16_t pid);


static inline bool cdr_deserialize_guid_prefix(struct mvbs_cdr *cdr,
					       struct rtps_guid_prefix *ptcp_guid)
{

	(void)mcdr_deserialize_array_uint8_t(cdr, ptcp_guid->id,
				(uint32_t)sizeof(ptcp_guid->id));

	return true;
}

static inline bool cdr_deserialize_entity_id(mvbs_cdr_t *cdr,
					     struct rtps_entity_id *eid)
{
	(void)mcdr_deserialize_array_uint8_t(cdr, (uint8_t *)eid,
					(uint32_t)sizeof(*eid));
	return true;
}

static inline bool cdr_serialize_entity_id(mvbs_cdr_t *cdr, struct rtps_entity_id *eid)
{
	(void)mcdr_serialize_array_uint8_t(cdr, (uint8_t *)eid->entity_key,
					   (uint32_t)sizeof(eid->entity_key));
	(void)mcdr_serialize_uint8_t(cdr, eid->entity_kind);

	return true;
}

static inline bool cdr_deserialize_guid(mvbs_cdr_t *cdr, struct rtps_guid *guid)
{
	(void)mcdr_deserialize_array_uint8_t(cdr, (uint8_t *)guid,
					(uint32_t)sizeof(*guid));
	return true;
}

static inline bool cdr_deserialize_duration(mvbs_cdr_t *cdr,
					    duration_t *duration)
{
	/* duration is null, skip 8 bytes */
	if (duration == NULL) {
		(void)mcdr_deserialize_int32_t(cdr, NULL);
		(void)mcdr_deserialize_uint32_t(cdr, NULL);
	} else {
		(void)mcdr_deserialize_int32_t(cdr, &duration->seconds);
		(void)mcdr_deserialize_uint32_t(cdr, &duration->nanosec);
	}

	return true;
}

static inline uint16_t cdr_deserialize_uint16_t(mvbs_cdr_t *cdr)
{
	uint16_t val;

	(void)mcdr_deserialize_uint16_t(cdr, &val);

	return val;
}

static inline uint32_t cdr_deserialize_uint32_t(mvbs_cdr_t *cdr)
{
	uint32_t val;

	(void)mcdr_deserialize_uint32_t(cdr, &val);

	return val;
}

uint32_t cdr_deserialize_inlineqos(struct mvbs_cdr *cdr, struct rtps_guid *guid);

int32_t cdr_deserialize_locator(struct mvbs_cdr *cdr, locator_t *loc);


#endif
