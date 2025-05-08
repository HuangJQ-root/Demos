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

#ifndef MVBS_CORE_TRANSPORT_LOCATOR_H
#define MVBS_CORE_TRANSPORT_LOCATOR_H

#include <mvbs/base_type.h>
#include <mvbs/rtps/locator.h>

struct locator {
	uint16_t	kind;		/* default LOCATOR_KIND_INVALID; */
	uint16_t	port;		/* default LOCATOR_PORT_INVALID; */
	uint8_t		ipv4_addr[4];	/* support ipv4 only */
};

typedef struct locator			 locator_t;

extern uint8_t local_ip_addr[4];
extern struct udp_info *loc_info;

#define LOCATOR_FMT		"%d/%d.%d.%d.%d:%d"
#define LOCATOR_MEMBERS(loc)	loc->kind, loc->ipv4_addr[0],		\
				loc->ipv4_addr[1], loc->ipv4_addr[2],	\
				loc->ipv4_addr[3], loc->port

int32_t locator_get_port(locator_t *loc);
uint32_t locator_get_ipv4_addr(locator_t *loc);

void locator_dump(locator_t *loc);

void locator_init_meta_uc_with_ip(locator_t *loc, uint8_t *remote_ip, uint8_t domainid);

void locator_set_invalid(locator_t *loc);

bool locator_has_valid_kind(locator_t *loc);

bool locator_is_local(locator_t *loc);

bool locator_is_zero_addr(locator_t *loc);
bool locator_is_multicast(locator_t *loc);
bool locator_is_meta_multicast_port(locator_t *loc, uint8_t domainid);
bool locator_is_user_multicast_port(locator_t *loc, uint8_t domainid);
bool locator_is_same_address(locator_t *loc, locator_t *loca);

bool locator_isMasterSubnet(locator_t *loc);
bool locator_isSameSubnet(locator_t *loc);

void locator_init(locator_t *loc, uint16_t loc_kind, uint8_t a, uint8_t b,
					uint8_t c, uint8_t d, uint16_t port);

void locator_create_user_multicast(locator_t *dst, locator_t *src, uint8_t domainid);

void locator_init_meta_multicast(locator_t *loc, uint8_t domainid);

#endif /* MVBS_CORE_TRANSPORT_LOCATOR_H */
