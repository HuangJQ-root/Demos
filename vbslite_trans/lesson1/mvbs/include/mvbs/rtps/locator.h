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

#ifndef MVBS_RTPS_LOCATOR_H
#define MVBS_RTPS_LOCATOR_H

#include <mvbs/base_type.h>

typedef enum {
	LOCATOR_KIND_INVALID	= -1,
	LOCATOR_KIND_RESERVED	= 0,
	LOCATOR_KIND_UDPv4	= 1,
	LOCATOR_KIND_UDPv6	= 2,
	LOCATOR_KIND_LOCAL	= 3,
	LOCATOR_KIND_IPC	= 32,
	LOCATOR_KIND_UDS	= 64,	/* DServer support UDS */
	LOCATOR_KIND_MAX
} LocatorKind_t;

/* standard rtps locator struct */
struct rtps_locator {
	uint32_t 	kind;
	uint32_t	port;
	uint8_t		address[16];
};

/* pid(u16) + size(u16) + sizeof(struct rtps_locator) = 28 */
#define UDR_BUFF_SIZE_PER_LOCATOR	(sizeof(uint16_t) + sizeof(uint16_t) + sizeof(struct rtps_locator))

#define PARTICIPANT_ID_MAX		120u	/* [0, 120) */
#define DOMAIN_ID_MAX			232u	/* [0, 232) */

#define RTPS_PORT_DG			250u	/* DomainId Gain	*/
#define RTPS_PORT_PG			2u	/* ParticipantId Gain	*/

/* Additional Offsets */
#define RTPS_PORT_META_MC			0u	/* meta multicast	*/
#define RTPS_PORT_USER_MC		1u	/* User multicast	*/

#define RTPS_PORT_META_UC			10u	/* meta unicast	*/
#define RTPS_PORT_USER_UC		11u	/* User unicast		*/

#define RTPS_PORT_BASE			7400U	/* Port Base Number	*/
#define RTPS_PORT_END			(7400U + (RTPS_PORT_DG * DOMAIN_ID_MAX))

static inline bool rtps_ptcp_id_is_invalid(uint8_t ptcp_id)
{
	return (ptcp_id >= PARTICIPANT_ID_MAX);
}

static inline bool rtps_domain_id_is_invalid(uint8_t domain_id)
{
	return (domain_id >= DOMAIN_ID_MAX);
}

static inline bool rtps_port_is_valid(uint16_t port)
{
	return (port >= RTPS_PORT_BASE) && (port < RTPS_PORT_END);
}

static inline uint8_t rtps_port_to_domain_id(uint16_t port)
{
	return (uint8_t)((port - RTPS_PORT_BASE) / RTPS_PORT_DG);
}

static inline uint8_t rtps_port_to_ptcp_id(uint16_t port)
{
	return (uint8_t)(((port - RTPS_PORT_BASE) % RTPS_PORT_DG) - RTPS_PORT_META_UC) / 2U;
}

static inline bool rtps_port_check_ptcp_ids(uint16_t port, uint8_t domain_id,
							   uint8_t ptcp_id)
{
	if (!rtps_port_is_valid(port)) {
		return false;
	}

	if (rtps_port_to_domain_id(port) != domain_id) {
		return false;
	}

	if (rtps_port_to_ptcp_id(port) != ptcp_id) {
		return false;
	}

	return true;
}

static inline uint16_t rtps_get_domain_port_base(uint8_t domain_id)
{
	return (uint16_t)(RTPS_PORT_BASE + (RTPS_PORT_DG * (uint16_t)domain_id));
}

static inline uint16_t rtps_get_ptcp_port_base(uint8_t domain_id,
						uint8_t ptcp_id)
{
	return (uint16_t)(RTPS_PORT_BASE + (RTPS_PORT_DG * (uint16_t)domain_id)
					 + (RTPS_PORT_PG * (uint16_t)ptcp_id));
}

static inline uint16_t rtps_get_meta_unicast_port(uint8_t domain_id,
						uint8_t ptcp_id)
{
	return rtps_get_ptcp_port_base(domain_id, ptcp_id) + RTPS_PORT_META_UC;
}

static inline uint16_t rtps_get_meta_multicast_port(uint8_t domain_id)
{
	return rtps_get_domain_port_base(domain_id) + RTPS_PORT_META_MC;
}

static inline uint16_t rtps_get_user_unicast_port(uint8_t domain_id, uint8_t ptcp_id)
{
	return rtps_get_ptcp_port_base(domain_id, ptcp_id) + RTPS_PORT_USER_UC;
}

static inline uint16_t rtps_get_user_multicast_port(uint8_t domain_id)
{
	return rtps_get_domain_port_base(domain_id) + RTPS_PORT_USER_MC;
}

static inline bool rtps_port_is_meta_multicast(uint16_t port)
{
	return ((port - RTPS_PORT_BASE) % RTPS_PORT_DG) == RTPS_PORT_META_MC;
}

#endif /* !LOCATOR_H */
