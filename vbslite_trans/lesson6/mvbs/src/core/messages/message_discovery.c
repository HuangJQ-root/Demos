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
#include <mvbs/utils/string.h>
#include <mvbs/rtps/message.h>
#include <mcdr/mcdr.h>
#include <discovery/dpse.h>

#define CDR_ARRAY_PARAM(x)			(x), (const uint32_t)(ARRAY_SIZE(x))

#if 0
static int32_t cdr_serialize_guid(mvbs_cdr *cdr,
				  struct guid_prefix *ptcp_guid_prefix,
				  struct entity_id eid)
{
	(void)mcdr_serialize_uint16_t(cdr, PID_PARTICIPANT_GUID);

	(void)mcdr_serialize_uint16_t(cdr, ARRAY_SIZE(ptcp_guid_prefix->id)
					 + ARRAY_SIZE(eid.entity_key) + 1);

	(void)mcdr_serialize_array_uint8_t(cdr, ptcp_guid_prefix->id,
						ARRAY_SIZE(ptcp_guid_prefix->id));

	(void)mcdr_serialize_array_uint8_t(cdr, eid.entity_key,
						ARRAY_SIZE(eid.entity_key));

	(void)mcdr_serialize_uint8_t(cdr, eid.entity_kind);

	if (mcdr_buffer_has_error(cdr)) {
		return -ERR_NOMEM;
	}

	return 0;
}

static int32_t cdr_serialize_session_id(mvbs_cdr *cdr, participant_t *ptcp)
{
	(void)mcdr_serialize_uint16_t(cdr, PID_SESSION_ID);

	(void)mcdr_serialize_uint16_t(cdr, (uint16_t)sizeof(uint64_t));

	(void)mcdr_serialize_uint32_t(cdr, ptcp->session_id_high);
	(void)mcdr_serialize_uint32_t(cdr, ptcp->session_id_low);

	if (mcdr_buffer_has_error(cdr)) {
		return -ERR_NOMEM;
	}

	return 0;
}
#endif

static inline uint32_t cdr_serialize_locator_length(void)
{
	/*     PID		+	length	   + rtps locator */
	return sizeof(uint16_t) + sizeof(uint16_t) + sizeof(struct rtps_locator);
}

int32_t cdr_serialize_locator(mvbs_cdr_t *cdr, locator_t *loc, uint16_t pid)
{
	struct rtps_locator rtps_loc = {(uint32_t)LOCATOR_KIND_RESERVED, 0, {0}};
	bool ret;

	if ((cdr == NULL) || (loc == NULL)) {
		return -ERR_INVALID;
	}

	if (mcdr_buffer_remaining(cdr) < cdr_serialize_locator_length()) {
		return -ERR_NOMEM;
	}

	rtps_loc.kind		= loc->kind;
	rtps_loc.port		= loc->port;

	rtps_loc.address[12]	= loc->ipv4_addr[0];
	rtps_loc.address[13]	= loc->ipv4_addr[1];
	rtps_loc.address[14]	= loc->ipv4_addr[2];
	rtps_loc.address[15]	= loc->ipv4_addr[3];

	(void)mcdr_serialize_uint16_t(cdr, pid);
	(void)mcdr_serialize_uint16_t(cdr, (uint16_t)sizeof(rtps_loc));

	ret = mcdr_serialize_array_uint8_t(cdr, (uint8_t *)(&rtps_loc),
						      sizeof(rtps_loc));
	if (!ret) {
		return -ERR_NOMEM;
	}

	return 0;
}

static int32_t cdr_serialize_ptcp_locators(struct mvbs_cdr *cdr,
				      const participant_t *ptcp, uint16_t pid)
{
	if ((cdr == NULL) || (ptcp == NULL)) {
		return -ERR_INVALID;
	}

	ptcp->ptransport->serialize_locator(ptcp->ptransport, cdr, NULL, pid);
	if (mcdr_buffer_has_error(cdr)) {
		return -ERR_NOMEM;
	}

	return 0;
}

static inline int32_t cdr_serialize_name_length(const char *name)
{
	uint32_t name_size;

	if (name == NULL) {
		return 0;
	}

	name_size = mvbs_strlen(name) + 1U;
	name_size = (name_size + 3U) & (~3U);

	/*     PID		+	length	   + string length    + string */
	return sizeof(uint16_t) + sizeof(uint16_t) + sizeof(uint32_t) + name_size;
}

static int32_t cdr_serialize_name(struct mvbs_cdr *cdr,
				  const char *name, uint16_t pid)
{
	if ((cdr == NULL) || (name == NULL)) {
		return -ERR_INVALID;
	}

	const uint32_t name_size	= mvbs_strlen(name) + 1U;
	const uint32_t name_size_align	= (name_size + 3U) & (~3U);
	const uint32_t name_size_total	= sizeof(name_size) + name_size_align;

	(void)mcdr_serialize_uint16_t(cdr, pid);
	(void)mcdr_serialize_uint16_t(cdr, (uint16_t)name_size_total);
	(void)mcdr_serialize_uint32_t(cdr, name_size);
	(void)mcdr_serialize_array_char(cdr, name, name_size);
	mcdr_align_to(cdr, 4u);

	if (mcdr_buffer_has_error(cdr)) {
		return -ERR_NOMEM;
	}

	return 0;
}

static bool pdp_template_render(mvbs_cdr_t *cdr, struct participant *ptcp)
{
	struct discovery_pdp *pdp_template;

	if (mcdr_buffer_remaining(cdr) < sizeof(*pdp_template)) {
		pr_err(ERR_NOMEM, "buffer remaining is not enough");
		return false;
	}

	pdp_template = ptcp->pdp_template;

	pdp_template->ptcp_lease_duration_value	= ptcp->attr->discovery.lease_duration;

	pdp_template->ptcp_guid_value.prefix	= ptcp->guid_prefix;

	pdp_template->session_id_value_hi	= ptcp_get_session_id_hi(ptcp);
	pdp_template->session_id_value_lo	= ptcp_get_session_id_lo(ptcp);

	mcdr_buffer_append_data(cdr, pdp_template, sizeof(*pdp_template));

	return true;
}

void discovery_package_template_init(struct participant *ptcp)
{
	struct discovery_edp *edp_template;

	if (ptcp == NULL) {
		return ;
	}

	edp_template = ptcp->edp_template;

	edp_template->key_hash_value.prefix	= ptcp->guid_prefix;
	edp_template->guid_kind.prefix		= ptcp->guid_prefix;
}

static bool edp_template_render(mvbs_cdr_t *cdr, const struct participant *ptcp,
				const endpoint_attr_t *ep_attr,
				struct rtps_entity_id eid)
{
	struct discovery_edp *edp_template = ptcp->edp_template;

	if (mcdr_buffer_remaining(cdr) < sizeof(*edp_template)) {
		return false;
	}

	/* PID_KEY_HASH */
	edp_template->key_hash_value.eid	= eid;

	/* PID_ENDPOINT_GUID */
	edp_template->guid_kind.eid	= eid;

	/* PID_RELIABILITY */
	edp_template->reliability_kind	= ep_attr->qos.reliability_kind;

	/* PID_DURABILITY */
	edp_template->durability_kind	= ep_attr->qos.durability_kind;

	/* PID_DEADLINE */
	edp_template->deadline_kind	= ep_attr->deadline.duration;

	/* PID_LIVELINESS */
	edp_template->liveliness_kind	= ep_attr->qos.liveliness_kind;
	edp_template->lease_duration	= ep_attr->liveliness.lease_duration;

	/* PID_OWNERSHIP */
	edp_template->ownership_kind	= ep_attr->qos.ownership_kind;

	/* PID_OWNERSHIP_STRENGTH */
	edp_template->ownership_strength_value = ep_attr->ownership_strength.value;

	/* PID_E2E_PROTECTION */
	edp_template->e2e_kind		= ep_attr->e2e.e2e_protection ? 1U : 0U;

	/* PID_AGENT_ENDPOINT */
	edp_template->agent_value	= ep_attr->agent_flag;

	mcdr_buffer_append_data(cdr, edp_template, sizeof(*edp_template));

	return true;
}

size_t cdr_serialize_sedp_edp_length(const struct endpoint_attr *attr)
{
	size_t ret;

	if (attr == NULL) {
		pr_err(ERR_INVALID, "attr is null");
		return 0;
	}

	ret = sizeof(struct discovery_edp);

	ret += cdr_serialize_locator_length();	/* unicast locator */

	ret += cdr_serialize_name_length(attr->topic_name);

	ret += cdr_serialize_name_length(attr->type->name);

	ret += cdr_serialize_name_length(attr->type->crc16);

	ret += sizeof(uint16_t) + sizeof(uint16_t); /* PID_SENTINEL */

	return ret;
}

size_t cdr_serialize_sedp_offline_edp_length(void)
{
	return sizeof(uint16_t)		/* CDR Little is_le Option */
	     + sizeof(uint16_t)		/* Zero */
	     + sizeof(uint16_t)		/* PID_KEY_HASH */
	     + sizeof(uint16_t)		/* Length */
	     + sizeof(struct rtps_guid)	/* Value: guid */
	     + sizeof(uint16_t)		/* PID_STATUS_INFO */
	     + sizeof(uint16_t)		/* Length */
	     + sizeof(uint32_t)		/* Value: uint32_t */
	     + sizeof(uint16_t)		/* PID_SENTINEL */
	     + sizeof(uint16_t);	/* Length: 0 */
}

int32_t cdr_serialize_sedp_edp(mvbs_cdr_t *cdr, const struct participant *ptcp,
			const struct endpoint_attr *attr, struct rtps_entity_id eid)
{
	int32_t retval;

	if ((cdr == NULL) || (attr == NULL)||(ptcp == NULL)) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return -ERR_INVALID;
	}

	if (!edp_template_render(cdr, ptcp, attr, eid)) {
		return -ERR_NOMEM;
	}

	retval = ptcp->ptransport->serialize_locator(ptcp->ptransport, cdr,
						attr, PID_UNICAST_LOCATOR);
	if (retval != 0) {
		pr_err(ERR_NOMEM, "Fail to serialize locator of ptcp (%s)",
							ptcp->attr->name);
		return -ERR_NOMEM;
	}

	/* Topic Name */
	retval = cdr_serialize_name(cdr, attr->topic_name, PID_TOPIC_NAME);
	if (retval != 0) {
		pr_err(ERR_NOMEM, "fail to serialize topic (%s)",
							attr->topic_name);
		return -ERR_NOMEM;
	}

	/* Type Name */
	retval = cdr_serialize_name(cdr, attr->type->name, PID_TYPE_NAME);
	if (retval != 0) {
		pr_err(ERR_NOMEM, "fail to serialize type (%s)",
							attr->type->name);
		return -ERR_NOMEM;
	}

	/* Crc16 */
	retval = cdr_serialize_name(cdr, attr->type->crc16, PID_CRC16_IDL);
	if (retval != 0) {
		pr_err(ERR_NOMEM, "fail to serialize crc16 (%s)",
							attr->type->crc16);
		return -ERR_NOMEM;
	}

	/* PID_SENTINEL */
	(void)mcdr_serialize_uint16_t(cdr, PID_SENTINEL);
	(void)mcdr_serialize_uint16_t(cdr, 0U);

	if (mcdr_buffer_has_error(cdr)) {
		return -ERR_NOMEM;
	}

	return 0;
}

static uint32_t calc_property_msg_length(struct rtps_property *property, int32_t prop_cnt)
{
	uint32_t len = 0;
	uint16_t len_aligment = 0U;

	for (int32_t i = 0; i < prop_cnt; i++) {
		len += 4U + 1U + mvbs_strlen(property[i].name);/* str_len + null_char + str_data */
		len = (len + 3U) & ~3U;
		len += 4U + 1U + mvbs_strlen(property[i].value);/* str_len + null_char + str_data */
		len = (len + 3U) & ~3U;
	}

	if ((len % 4U) != 0U) {
		len_aligment = (uint16_t)(4U - (len % 4U));
	}

	/* property data length + prop_cnt + padding */
	len = (uint16_t)(len + 4 + len_aligment);

	return len;
}

static int32_t cdr_serialize_static_property(struct mvbs_cdr *cdr,
					 struct rtps_property *property,
					 uint32_t prop_cnt)
{
	uint32_t i;
	uint32_t len = 0;

	if ((cdr == NULL) || (property == NULL) || (prop_cnt == 0)) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return -ERR_INVALID;
	}

	len = calc_property_msg_length(property, prop_cnt);

	(void)mcdr_serialize_uint16_t(cdr, PID_PROPERTY_LIST);
	(void)mcdr_serialize_uint16_t(cdr, (uint16_t)len);
	(void)mcdr_serialize_uint32_t(cdr, prop_cnt);

	for (i = 0; i < prop_cnt; i++) {
		len = 1U + mvbs_strlen(property[i].name);/* str_len + null_char + str_data */
		len = (len + 3U) & ~3U;

		(void)mcdr_serialize_uint32_t(cdr, (uint32_t)len);
		(void)mcdr_serialize_array_uint8_t(cdr,
				static_cast_ptr(void, property[i].name),
				(uint32_t)len);

		len = 1U + mvbs_strlen(property[i].value);/* str_len + null_char + str_data */
		len = (len + 3U) & ~3U;
		(void)mcdr_serialize_uint32_t(cdr, (uint32_t)len);
		(void)mcdr_serialize_array_uint8_t(cdr,
				static_cast_ptr(void, property[i].value),
				(uint32_t)len);
	}

	return 0;
}

size_t cdr_serialize_spdp_pdp_length(struct participant *ptcp,
				    struct rtps_property *property, int32_t prop_cnt)
{
	size_t ret;

	if ((ptcp == NULL) || (property == NULL)) {
		return 0;
	}

	ret = sizeof(struct discovery_pdp);

	ret += cdr_serialize_locator_length();	/* PID_DEFAULT_UNICAST_LOCATOR */

	ret += cdr_serialize_locator_length();	/* PID_METATRAFFIC_UNICAST_LOCATOR */

	ret += cdr_serialize_locator_length();	/* PID_METATRAFFIC_MULTICAST_LOCATOR */

	ret += cdr_serialize_name_length(ptcp->attr->name);  /*PID_ENTITY_NAME */

	if (ptcp->attr->discovery.edp_type == STATIC_EDP) {
		ret += calc_property_msg_length(property, prop_cnt) + 4;
	}

	ret += sizeof(uint16_t) + sizeof(uint16_t); /* PID_SENTINEL */

	return ret;
}

int32_t cdr_serialize_spdp_pdp(struct mvbs_cdr *cdr, struct participant *ptcp,
			   struct rtps_property *property, int32_t propty_cnt)
{
	int32_t  retval;
	bool ret;

	/* 1. serialize const data */
	ret = pdp_template_render(cdr, ptcp);
	if (!ret) {
		return -ERR_NOMEM;
	}

	/* 3.4 PID_DEFAULT_UNICAST_LOCATOR */
	(void)cdr_serialize_ptcp_locators(cdr, ptcp, PID_DEFAULT_UNICAST_LOCATOR);
	if (mcdr_buffer_has_error(cdr)) {
		return -ERR_NOMEM;
	}

	/* 3.5 PID_METATRAFFIC_UNICAST_LOCATOR */
	(void)cdr_serialize_ptcp_locators(cdr, ptcp, PID_METATRAFFIC_UNICAST_LOCATOR);
	if (mcdr_buffer_has_error(cdr)) {
		return -ERR_NOMEM;
	}

	/* 3.6 PID_METATRAFFIC_MULTICAST_LOCATOR */
	(void)cdr_serialize_ptcp_locators(cdr, ptcp, PID_METATRAFFIC_MULTICAST_LOCATOR);
	if (mcdr_buffer_has_error(cdr)) {
		return -ERR_NOMEM;
	}

	/* 3.12 PID_ENTITY_NAME */
	retval = cdr_serialize_name(cdr, ptcp->attr->name, PID_ENTITY_NAME);
	if (retval != 0) {
		return -ERR_NOMEM;
	}

	mcdr_align_to(cdr, sizeof(uint32_t));

	/* 3.13 STATIC Discovery */
	if (ptcp->attr->discovery.edp_type == STATIC_EDP) {
		(void)cdr_serialize_static_property(cdr, property, propty_cnt);
	}

	/* 3.14 PID_SENTINEL */
	(void)mcdr_serialize_uint16_t(cdr, PID_SENTINEL);
	(void)mcdr_serialize_uint16_t(cdr, 0U);
	if (mcdr_buffer_has_error(cdr)) {
		return -ERR_NOMEM;
	}

	return 0;
}

int32_t cdr_serialize_spdp_pdp_offline(mvbs_cdr_t *cdr, struct participant *ptcp)
{
	if ((cdr == NULL) || (ptcp == NULL)) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return -ERR_INVALID;
	}

	/* 1. CDR Little is_le */
	(void)mcdr_serialize_array_uint8_t(cdr, SCHEME_PL_CDR_LE,
					        SCHEME_PL_CDR_LE_SIZE);
	(void)mcdr_serialize_uint16_t(cdr, 0U);

	/* 2. Participant guid */
	(void)mcdr_serialize_uint16_t(cdr, PID_PARTICIPANT_GUID);
	(void)mcdr_serialize_uint16_t(cdr, 16U);

	(void)mcdr_serialize_array_uint8_t(cdr,
			CDR_ARRAY_PARAM(ptcp->guid_prefix.id));
	(void)mcdr_serialize_array_uint8_t(cdr,
			CDR_ARRAY_PARAM(ENTITYID_BUILD_IN_PARTICIPANT.entity_key));
	(void)mcdr_serialize_uint8_t(cdr,
			ENTITYID_BUILD_IN_PARTICIPANT.entity_kind);

	/* 3. Status Info */
	(void)mcdr_serialize_uint16_t(cdr, PID_STATUS_INFO);
	(void)mcdr_serialize_uint16_t(cdr, 4U);

	(void)mcdr_serialize_uint8_t(cdr, 0U);
	(void)mcdr_serialize_uint8_t(cdr, 0U);
	(void)mcdr_serialize_uint8_t(cdr, 0U);
	(void)mcdr_serialize_uint8_t(cdr, 3U);

	/* 4. Ends */
	(void)mcdr_serialize_uint16_t(cdr, PID_SENTINEL);
	(void)mcdr_serialize_uint16_t(cdr, 0U);

	return 0;
}

int32_t cdr_serialize_sedp_edp_offline(struct mvbs_cdr *cdr,
				       struct rtps_guid_prefix *guid,
				       struct rtps_entity_id eid)
{
	if ((cdr == NULL) || (guid == NULL)) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return -ERR_INVALID;
	}

	/* 1. CDR Little is_le */
	(void)mcdr_serialize_array_uint8_t(cdr, SCHEME_PL_CDR_LE,
						SCHEME_PL_CDR_LE_SIZE);
	(void)mcdr_serialize_uint16_t(cdr, 0U);

	/* 2. PID KEY: guid */
	(void)mcdr_serialize_uint16_t(cdr, PID_KEY_HASH);
	(void)mcdr_serialize_uint16_t(cdr, 16U);
	(void)mcdr_serialize_array_uint8_t(cdr, CDR_ARRAY_PARAM(guid->id));
	(void)mcdr_serialize_array_uint8_t(cdr, CDR_ARRAY_PARAM(eid.entity_key));
	(void)mcdr_serialize_uint8_t(cdr, eid.entity_kind);

	/* 3. Status Info */
	(void)mcdr_serialize_uint16_t(cdr, PID_STATUS_INFO);
	(void)mcdr_serialize_uint16_t(cdr, 4U);
	(void)mcdr_serialize_uint8_t(cdr, 0U);
	(void)mcdr_serialize_uint8_t(cdr, 0U);
	(void)mcdr_serialize_uint8_t(cdr, 0U);
	(void)mcdr_serialize_uint8_t(cdr, 3U);

	/* 4. Ends */
	(void)mcdr_serialize_uint16_t(cdr, PID_SENTINEL);
	(void)mcdr_serialize_uint16_t(cdr, 0U);

	if (mcdr_buffer_has_error(cdr)) {
		return -ERR_NOMEM;
	}

	return 0;
}

#define RESERVE_SIZE                   0x08

int32_t cdr_serialize_liveliness_msg(struct mvbs_cdr *cdr,
				 struct instance_handle instance)
{
	const uint16_t zero_options	= 0U;
	uint8_t reserve[RESERVE_SIZE] = { 0x0, 0x0, 0x0, 0x0,
					0x0, 0x0, 0x0, 0x0 };
	bool ret;

	if (cdr == NULL) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return -ERR_INVALID;
	}

	/* 1. encapsulation kind: PL_CDR_LE */
	ret = mcdr_serialize_array_uint8_t(cdr, SCHEME_PL_CDR_LE,
						SCHEME_PL_CDR_LE_SIZE);
	if (!ret) {
		return -ERR_NOMEM;
	}

	/* 2. encapsulation option */
	ret = mcdr_serialize_uint16_t(cdr, zero_options);
	if (!ret) {
		return -ERR_NOMEM;
	}

	ret = mcdr_serialize_array_uint8_t(cdr, CDR_ARRAY_PARAM(instance.value));
	if (!ret) {
		return -ERR_NOMEM;
	}

	ret = mcdr_serialize_array_uint8_t(cdr, CDR_ARRAY_PARAM(reserve));
	if (!ret) {
		return -ERR_NOMEM;
	}

	return 0;
}

int32_t cdr_deserialize_locator(struct mvbs_cdr *cdr, locator_t *loc)
{
	struct rtps_locator rtps_loc = {(uint32_t)LOCATOR_KIND_RESERVED, 0, {0}};
	bool ret;

	if ((cdr == NULL) || (loc == NULL)) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return -ERR_INVALID;
	}

	if (mcdr_buffer_remaining(cdr) < sizeof(rtps_loc)) {
		return -ERR_NOMEM;
	}

	/*
	 * Deserialize the common format locator
	 */
	ret = mcdr_deserialize_array_uint8_t(cdr, (void *)(&rtps_loc),
						     sizeof(rtps_loc));
	if (!ret) {
		return -ERR_NOMEM;
	}

	if (rtps_loc.kind == (uint32_t)LOCATOR_KIND_UDPv4) {
		loc->kind		= (uint16_t)rtps_loc.kind;
		loc->port		= (uint16_t)rtps_loc.port;
		loc->ipv4_addr[0]	= rtps_loc.address[12];
		loc->ipv4_addr[1]	= rtps_loc.address[13];
		loc->ipv4_addr[2]	= rtps_loc.address[14];
		loc->ipv4_addr[3]	= rtps_loc.address[15];

		return 0;
	}

	if ((rtps_loc.kind == (uint32_t)LOCATOR_KIND_LOCAL) ||
	    (rtps_loc.kind == (uint32_t)LOCATOR_KIND_IPC) ||
	    (rtps_loc.kind == (uint32_t)LOCATOR_KIND_UDS)) {
		loc->kind = (uint16_t)rtps_loc.kind;
		return 0;
	}

	loc->kind = (uint16_t)LOCATOR_KIND_INVALID;

	return 0;
}

/* uint32_t length + string */
static bool cdr_deserialize_string(mvbs_cdr_t *cdr, void *buf, size_t size)
{
	uint32_t length;

	(void)mcdr_deserialize_uint32_t(cdr, &length);

	if (length > size) {
		/* FIXME */
		(void)mcdr_deserialize_array_uint8_t(cdr, NULL, length);

		return false;
	}

	(void)mcdr_deserialize_array_uint8_t(cdr, buf, length);

	return true;
}

static bool cdr_deserialize_ptcp_proxy_property(mvbs_cdr_t *cdr,
						struct rtps_property_info *prop_info)
{
	struct rtps_property *property;
	uint32_t property_cnt = 0U;
	bool ret;
	bool name;
	bool value;

	if (prop_info->property_list == NULL) {
		return false;
	}

	ret = mcdr_deserialize_uint32_t(cdr, &property_cnt);
	if (!ret) {
		return false;
	}

	if (property_cnt > prop_info->max_count) {
		return false;
	}

	property = prop_info->property_list;

	for (uint8_t i = 0; i < property_cnt; i++) {
		name = cdr_deserialize_string(cdr, (void *)property->name,
						  sizeof(property->name));

		value = cdr_deserialize_string(cdr, (void *)property->value,
						   sizeof(property->value));

		if (name && value) {
			property++;
			prop_info->valid_count++;
		}
	}

	return true;
}

static bool propertyinfo_has_dclient_flag(struct rtps_property_info *propertyinfo)
{
	struct rtps_property *item = NULL;

	/* PropertyInfo
	 *  Key:  "PARTICIPANT_TYPE"  => Value: "CLIENT"	(For RTI)
	 *  Key:  "PARTICIPANTTYPE"  => Value: "CLIENT"		(For MVBS)
	 *  Key:  "DS_VERSION"  => Value: "2.0"	(Ignore this check here)
	 */

	for (int i = 0; i < propertyinfo->valid_count; i++) {
		item = &propertyinfo->property_list[i];
		if (mvbs_strcmp(item->name, "PARTICIPANT_TYPE") == 0 &&
		    mvbs_strcmp(item->value, "CLIENT") == 0) {
			return true;
		} else if (mvbs_strcmp(item->name, "PARTICIPANTTYPE") == 0 &&
			   mvbs_strcmp(item->value, "CLIENT") == 0) {
			return true;
		}
	}

	return false;
}

static bool propertyinfo_has_dserver_flag(struct rtps_property_info *propertyinfo)
{
	struct rtps_property *item = NULL;

	/* PropertyInfo
	 *  Key:  "PARTICIPANT_TYPE"  => Value: "SERVER"	(For RTI)
	 *  Key:  "PARTICIPANTTYPE"  => Value: "SERVER"		(For MVBS)
	 *  Key:  "DS_VERSION"  => Value: "2.0"	(Ignore this check here)
	 */

	for (int i = 0; i < propertyinfo->valid_count; i++) {
		item = &propertyinfo->property_list[i];
		if (mvbs_strcmp(item->name, "PARTICIPANT_TYPE") == 0 &&
		    mvbs_strcmp(item->value, "SERVER") == 0) {
			return true;
		} else if (mvbs_strcmp(item->name, "PARTICIPANTTYPE") == 0 &&
			   mvbs_strcmp(item->value, "SERVER") == 0) {
			return true;
		}
	}

	return false;
}

bool cdr_deserialize_ptcp_proxy(mvbs_cdr_t *cdr,
				struct participant_proxy *ptcp_proxy,
				struct participant *ptcp,
				struct rtps_property_info *prop_info,
				uint32_t *status_info)
{
	locator_t	*meta_mc_loc;
	locator_t	*dfl_mc_loc;
	locator_t	*meta_uc_loc;
	locator_t	*dfl_uc_loc;
	uint8_t		meta_uc_cnt = 0;
	uint8_t		user_uc_cnt = 0;
	uint8_t		max_locators = 0;

	uint16_t	pid = 0;
	uint16_t	length = 0;

	bool end_process = false;
	bool ret;

	if ((cdr == NULL) || (ptcp_proxy == NULL)
			  || (ptcp == NULL) || (prop_info == NULL)) {
		pr_err(ERR_INVALID, "Invaild parameter.");
		return false;
	}

	meta_uc_loc = ptcp_proxy_get_meta_uc_loc(ptcp_proxy);
	dfl_uc_loc  = ptcp_proxy_get_user_uc_loc(ptcp_proxy);
	meta_mc_loc = ptcp_proxy_get_meta_mc_loc(ptcp_proxy);
	dfl_mc_loc  = ptcp_proxy_get_user_mc_loc(ptcp_proxy);

	max_locators = ptcp_local_locator_count(ptcp);

	prop_info->valid_count = 0;/* reset the valid count */

	while (mcdr_buffer_remaining(cdr) >= 4U) {
		(void)mcdr_deserialize_uint16_t(cdr, &pid);

		(void)mcdr_deserialize_uint16_t(cdr, &length);

		if (mcdr_buffer_remaining(cdr) < length) {
			return false;
		}

		switch (pid) {
			case PID_PROTOCOL_VERSION: {
				(void)mcdr_deserialize_uint8_t(cdr, &ptcp_proxy->proto_ver.major);

				if (ptcp_proxy->proto_ver.major < PROTOCOLVERSION.major) {
					return false;
				}

				(void)mcdr_deserialize_uint8_t(cdr, &ptcp_proxy->proto_ver.minor);

				break;
			}

			case PID_VENDORID: {
				(void)mcdr_deserialize_array_uint8_t(cdr,
						ptcp_proxy->vendor_id.id,
						(uint32_t)sizeof(ptcp_proxy->vendor_id));
				break;
			}

			case PID_EXPECTS_INLINE_QOS: {
				bool expects_inline_qos;
				(void)mcdr_deserialize_bool(cdr, &expects_inline_qos);

				ptcp_proxy->expects_inline_qos =
					(expects_inline_qos ? 1U : 0U);

				break;
			}

			case PID_PARTICIPANT_GUID: {
				if (cdr_deserialize_guid(cdr, &ptcp_proxy->guid) != true) {
					pr_err(ERR_MCDR, "Fail to deser guid.");
				}

				break;
			}

			case PID_METATRAFFIC_MULTICAST_LOCATOR: {
				if (cdr_deserialize_locator(cdr, meta_mc_loc) != 0) {
					pr_err(ERR_MCDR, "deserialize ipv4 locator meta_mc_loc fail.");
					return false;
				}

				if (ptcp_detect_reachable(ptcp, meta_mc_loc) < 0) {
					meta_mc_loc->kind = (uint16_t)LOCATOR_KIND_INVALID;
				}

				break;
			}

			case PID_DEFAULT_MULTICAST_LOCATOR: {
				if (cdr_deserialize_locator(cdr, dfl_mc_loc) != 0) {
					pr_err(ERR_MCDR, "deserialize ipv4 locator dfl_mc_loc fail.");
					return false;
				}

				if (ptcp_detect_reachable(ptcp, dfl_mc_loc) < 0) {
					dfl_mc_loc->kind = (uint16_t)LOCATOR_KIND_INVALID;
				}

				break;
			}

			case PID_METATRAFFIC_UNICAST_LOCATOR: {
				if (cdr_deserialize_locator(cdr, meta_uc_loc) != 0) {
					pr_err(ERR_MCDR, "deserialize ipv4 locator meta_uc_loc fail.");
					continue;
				}

				/* Skip invalid UDS address from DServer */
				if (meta_uc_loc->kind == LOCATOR_KIND_UDS) {
					meta_uc_loc->kind = LOCATOR_KIND_INVALID;
					break;
				}

				if (ptcp_detect_reachable(ptcp, meta_uc_loc) < 0) {
					meta_uc_loc->kind = (uint16_t)LOCATOR_KIND_INVALID;

					break;
				}

				meta_uc_cnt++;

				/* Redundant links are only for UDPv4 */
				if (meta_uc_cnt >= max_locators) {
					break;
				}

				meta_uc_loc = ptcp_proxy_get_next_uc_loc(meta_uc_loc);

				meta_uc_loc->kind = LOCATOR_KIND_INVALID;

				break;
			}

			case PID_DEFAULT_UNICAST_LOCATOR: {
				if (cdr_deserialize_locator(cdr, dfl_uc_loc) != 0) {
					pr_err(ERR_MCDR, "deserialize ipv4 locator dfl_uc_loc fail.");
					continue;
				}

				if (ptcp_detect_reachable(ptcp, dfl_uc_loc) < 0) {
					dfl_uc_loc->kind = (uint16_t)LOCATOR_KIND_INVALID;

					break;
				}

				user_uc_cnt++;

				/* Redundant links are only for UDPv4 */
				if (user_uc_cnt >= max_locators) {
					break;
				}

				dfl_uc_loc = ptcp_proxy_get_next_uc_loc(dfl_uc_loc);

				dfl_uc_loc->kind = (uint16_t)LOCATOR_KIND_INVALID;

				break;
			}

			case PID_PARTICIPANT_LEASE_DURATION: {
				(void)cdr_deserialize_duration(cdr,
						&ptcp_proxy->lease_duration);
				break;
			}

			case PID_BUILTIN_ENDPOINT_SET: {
				(void)mcdr_deserialize_uint32_t(cdr,
						&ptcp_proxy->avail_builtin_eps);
				break;
			}

			case PID_ENTITY_NAME: {
				cdr_deserialize_string(cdr,
						ptcp_proxy->ptcp_name,
						sizeof(ptcp_proxy->ptcp_name));
				break;
			}

			case PID_PROPERTY_LIST: {
				ret = cdr_deserialize_ptcp_proxy_property(cdr,
									prop_info);
				if (!ret) {
					return false;
				}

				break;
			}

			case PID_USER_DATA: {
				/* TODO */
				(void)mcdr_deserialize_array_uint8_t(cdr, NULL, length);
				break;
			}

			case PID_PAD: {
				(void)mcdr_deserialize_array_uint8_t(cdr, NULL, length);
				break;
			}

			case PID_SENTINEL: {
				bool is_dserver = propertyinfo_has_dserver_flag(prop_info);
				if (is_dserver) {
					ptcp_proxy_set_dserver_flag(ptcp_proxy);
					end_process = true;
					break;
				}

				bool is_dclient = propertyinfo_has_dclient_flag(prop_info);
				if (is_dclient) {
					ptcp_proxy_set_dclient_flag(ptcp_proxy);
					end_process = true;
					break;
				}

				meta_uc_loc = ptcp_proxy_get_meta_uc_loc(ptcp_proxy);
				dfl_uc_loc = ptcp_proxy_get_user_uc_loc(ptcp_proxy);

				/* Shall has one valid locator for meta_uc and dfl_uc */
				if (!locator_has_valid_kind(meta_uc_loc)) {
					return false;
				}

				if (!locator_has_valid_kind(dfl_uc_loc)) {
					return false;
				}

				end_process = true;

				break;
			}

			case PID_STATUS_INFO: {
				if (length != 4U) {
					/* Ignore Status Info */
					(void)mcdr_deserialize_array_uint8_t(cdr, NULL, length);
					break;
				}

				/*
				* skip first 3 bytes of status info as they are
				* reserved parameters
				*/
				(void)mcdr_deserialize_uint32_t(cdr, status_info);
				break;
			}

			case PID_SESSION_ID: {
				uint32_t session_id_hi;
				uint32_t session_id_lo;

				(void)mcdr_deserialize_uint32_t(cdr, &session_id_hi);
				(void)mcdr_deserialize_uint32_t(cdr, &session_id_lo);

				ptcp_proxy->session_id  = ((uint64_t)session_id_hi << 32)
							| session_id_lo;

				break;
			}

			case PID_VBS_VERTION: {
				(void)mcdr_deserialize_array_uint8_t(cdr,
							(uint8_t *)&ptcp_proxy->vbs_version, 4);
				break;
			}

			default: {
				(void)mcdr_deserialize_array_uint8_t(cdr, NULL, length);
				break;
			}
		}

		if (end_process) {
			return true;
		}

		/* Parameter lists are 4-byte aligned */
		mcdr_align_to_uint32(cdr);
	}

	return false;
}

uint32_t cdr_deserialize_inlineqos(struct mvbs_cdr *cdr, struct rtps_guid *guid)
{
	uint16_t pid		= 0;
	uint16_t length		= 0;
	uint8_t  status_info	= 0;

	bool end_process	= false;

	if ((cdr == NULL) || (guid == NULL)) {
		return 0;
	}

	mvbs_memzero(guid, sizeof(struct rtps_guid));

	while (mcdr_buffer_remaining(cdr) >= 4U) {
		(void)mcdr_deserialize_uint16_t(cdr, &pid);
		(void)mcdr_deserialize_uint16_t(cdr, &length);

		if (mcdr_buffer_remaining(cdr) < length) {
			pr_err(ERR_INVALID, "Data length in CDR is invalid.");

			return 0;
		}

		switch (pid) {
			case PID_KEY_HASH:
				if (length != 16U) {
					/* Ignore value */
					(void)mcdr_deserialize_array_uint8_t(cdr, NULL, length);
					break;
				}

				(void)cdr_deserialize_guid(cdr, guid);
				break;

			case PID_STATUS_INFO:
				if (length != 4U) {
					/* Ignore Status Info */
					(void)mcdr_deserialize_array_uint8_t(cdr, NULL, length);
					break;
				}

				/*
				* skip first 3 bytes of status info as they are
				* reserved parameters
				*/
				(void)mcdr_deserialize_array_uint8_t(cdr, NULL, 3U);
				(void)mcdr_deserialize_uint8_t(cdr, &status_info);
				break;

			case PID_SENTINEL:
				end_process = true;
				break;

			default:
				(void)mcdr_deserialize_array_uint8_t(cdr, NULL, length);
				break;
		}

		if (end_process) {
			return (uint32_t)status_info;
		}
	}

	return 0;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
