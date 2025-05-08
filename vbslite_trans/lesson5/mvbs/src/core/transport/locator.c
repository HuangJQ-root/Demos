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
#include <mvbs/errno.h>
#include <mvbs/utils/string.h>
#include <mvbs/rtps/locator.h>

struct ip4_addr {
	/* transformIP4ToU32 has process the is_le */
	uint32_t addr;
};

typedef struct ip4_addr ip4_addr_t;

#define PP_HTONS(x)	((uint16_t)((((x) & (uint16_t)0x00ffU) << 8) |		\
				    (((x) & (uint16_t)0xff00U) >> 8)))

#define PP_NTOHS(x)	PP_HTONS(x)

#define PP_HTONL(x)	((((x) & (uint32_t)0x000000ffUL) << 24) |		\
			 (((x) & (uint32_t)0x0000ff00UL) << 8)  |		\
			 (((x) & (uint32_t)0x00ff0000UL) >> 8)  |		\
			 (((x) & (uint32_t)0xff000000UL) >> 24))

#define PP_NTOHL(x)	PP_HTONL(x)

#define ip4_addr_is_multicast(ip4_addr)						\
	(((ip4_addr)->addr & PP_HTONL(0xf0000000UL)) == PP_HTONL(0xe0000000UL))

#define ip4_addr_equal(addr1, addr2)		((addr1)->addr == (addr2)->addr)

static inline uint32_t locator_transform_ip4_to_u32(uint8_t MSB, uint8_t p2, uint8_t p1,
					   uint8_t LSB)
{
	uint32_t retval;

	retval = (((uint32_t)LSB << 24) | ((uint32_t)p1 << 16)
					| ((uint32_t)p2 << 8) | MSB);
	return retval;
}

void locator_dump(locator_t *loc)
{
	pr_verb("Locartor:");
	pr_verb("\tkind = %d, port = %u ip [%u,%u,%u,%u]\n", loc->kind,
		loc->port, loc->ipv4_addr[0], loc->ipv4_addr[1],
		loc->ipv4_addr[2], loc->ipv4_addr[3]);
}

void locator_set_invalid(locator_t *loc)
{
	if (loc == NULL) {
		return;
	}

	loc->kind = (uint16_t)LOCATOR_KIND_INVALID;
}

bool locator_is_local(locator_t *loc)
{
	if (loc == NULL) {
		return false;
	}

	return loc->kind == (uint16_t)LOCATOR_KIND_LOCAL;
}

bool locator_has_valid_kind(locator_t *loc)
{
	if (loc == NULL) {
		return false;
	}

	/* FIXME:
	 * If more kind has been supported, the following code lines should be
	 * updated.
	 */
	return (loc->kind == (uint16_t)LOCATOR_KIND_UDPv4) ||
	       (loc->kind == (uint16_t)LOCATOR_KIND_LOCAL) ||
	       (loc->kind == (uint16_t)LOCATOR_KIND_IPC);
}

static inline bool locator_port_is_meta_mc(uint16_t port, uint8_t domainid)
{
	const uint16_t id_without_base = port - RTPS_PORT_BASE
					    - (RTPS_PORT_DG * domainid);

	return (id_without_base == RTPS_PORT_META_MC);
}

bool locator_is_meta_multicast_port(locator_t *loc, uint8_t domainid)
{
	if (loc == NULL) {
		return false;
	}

	return locator_port_is_meta_mc(loc->port, domainid);
}

static inline bool port_is_user_mc(uint16_t port, uint8_t domainid)
{
	const uint16_t id_without_base = port - RTPS_PORT_BASE
					    - (RTPS_PORT_DG * domainid);

	return ((id_without_base >= RTPS_PORT_USER_MC)
					&& (id_without_base < RTPS_PORT_META_UC));
}

bool locator_is_user_multicast_port(locator_t *loc, uint8_t domainid)
{
	if (loc == NULL) {
		return false;
	}

	return port_is_user_mc(loc->port, domainid);
}

int32_t locator_get_port(locator_t *loc)
{
	if (loc == NULL) {
		return -ERR_INVALID;
	}

	return (int32_t)loc->port;
}

uint32_t locator_get_ipv4_addr(locator_t *loc)
{
	uint32_t ip = 0U;

	if (loc != NULL) {
		ip = locator_transform_ip4_to_u32(loc->ipv4_addr[0], loc->ipv4_addr[1],
				       loc->ipv4_addr[2], loc->ipv4_addr[3]);
	}

	return ip;
}

static ip4_addr_t locator_get_ip4_address(locator_t *loc)
{
	ip4_addr_t tmp_addr = {0};

	if (loc != NULL) {
		tmp_addr.addr = locator_transform_ip4_to_u32(loc->ipv4_addr[0],
						  loc->ipv4_addr[1],
						  loc->ipv4_addr[2],
						  loc->ipv4_addr[3]);
	}

	return tmp_addr;
}

static inline bool locator_is_zero_address(ip4_addr_t address)
{
	return (address.addr == 0U);
}

bool locator_is_zero_addr(locator_t *loc)
{
	if (loc == NULL) {
		return false;
	}

	ip4_addr_t address = locator_get_ip4_address(loc);

	return locator_is_zero_address(address);
}

bool locator_is_multicast(locator_t *loc)
{
	if (loc == NULL) {
		return false;
	}

	ip4_addr_t address = locator_get_ip4_address(loc);

	return ip4_addr_is_multicast(&address);
}

void locator_create_user_multicast(locator_t *dst, locator_t *src,
				  uint8_t domainid)
{
	if ((dst == NULL) || (src == NULL)) {
		return;
	}

	*dst = *src;

	dst->port = rtps_get_user_multicast_port(domainid);
}

bool locator_is_same_address(locator_t *loc, locator_t *loca)
{
	if ((loc == NULL) || (loca == NULL)) {
		return false;
	}

	ip4_addr_t ownaddress = locator_get_ip4_address(loc);
	ip4_addr_t address = locator_get_ip4_address(loca);

	return ip4_addr_equal(&ownaddress, &address);
}

void locator_init(locator_t *loc, uint16_t kind, uint8_t a, uint8_t b,
					uint8_t c, uint8_t d, uint16_t port)
{
	if (loc == NULL) {
		return;
	}

	loc->kind		= kind;

	loc->ipv4_addr[0]	= a;
	loc->ipv4_addr[1]	= b;
	loc->ipv4_addr[2]	= c;
	loc->ipv4_addr[3]	= d;

	loc->port		= (uint16_t)port;
}

void locator_init_meta_multicast(locator_t *loc, uint8_t domainid)
{
	const uint8_t multicast_ip_addr[4] = { 239, 255, 0, 1 };

	uint16_t port;

	if (loc == NULL) {
		return;
	}

	port = rtps_get_meta_multicast_port(domainid);

	locator_init(loc, LOCATOR_KIND_UDPv4,
			  multicast_ip_addr[0], multicast_ip_addr[1],
			  multicast_ip_addr[2], multicast_ip_addr[3], port);
}

void locator_init_meta_uc_with_ip(locator_t *loc, uint8_t *ip,
					uint8_t domainid)
{
	if ((loc == NULL) || (ip == NULL)) {
		return;
	}

	locator_init(loc, LOCATOR_KIND_UDPv4,
			  ip[0], ip[1], ip[2], ip[3],
			  rtps_get_meta_unicast_port(domainid, 0));
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
