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

#ifndef MVBS_RTPS_DISCOVERY_H
#define MVBS_RTPS_DISCOVERY_H

#include <mvbs/base_type.h>
#include <mvbs/rtps/guid.h>
#include <mvbs/rtps/time.h>

struct discovery_pdp {
	/* encapsulation options */
	uint8_t		encapsulation_kind[2];
	uint16_t	encapsulation_options;

	/* PID_PROTOCOL_VERSION */
	uint16_t	protocol_version_pid;
	uint16_t	protocol_version_length;
	uint8_t		protocol_version_major;
	uint8_t		protocol_version_minor;
	uint16_t	padding1;

	/* PID_VENDORID */
	uint16_t	vendorid_pid;
	uint16_t	vendorid_length;
	char		vendorid_value[2];
	uint16_t	padding2;

	/* PID_MVBS_VERTION */
	uint16_t	mvbs_version_pid;
	uint16_t	mvbs_version_length;
	uint8_t		mvbs_version_value[4];

	/* PID_BUILTIN_ENDPOINT_SET */
	uint16_t	builtin_endpoint_set_pid;
	uint16_t	builtin_endpoint_set_length;
	uint32_t	builtin_endpoint_set_value;

	/* PID_PARTICIPANT_LEASE_DURATION */
	uint16_t	ptcp_lease_duration_pid;
	uint16_t	ptcp_lease_duration_length;
	duration_t	ptcp_lease_duration_value;

	/* PID_PARTICIPANT_GUID */
	uint16_t	ptcp_guid_pid;
	uint16_t	ptcp_guid_length;
	struct rtps_guid 	ptcp_guid_value;

	/* PID_SESSION_ID */
	uint16_t	session_id_pid;
	uint16_t	session_id_length;
	uint32_t	session_id_value_hi;
	uint32_t	session_id_value_lo;
};

struct discovery_edp {
	/* encapsulation options */
	uint8_t		encapsulation_kind[2];
	uint16_t	encapsulation_options;

	/* PID_KEY_HASH */
	uint16_t	key_hash_pid;
	uint16_t	key_hash_pid_length;
	struct rtps_guid	key_hash_value;

	/* PID_ENDPOINT_GUID */
	uint16_t	guid_pid;
	uint16_t	guid_pid_length;
	struct rtps_guid	guid_kind;

	/* PID_RELIABILITY */
	uint16_t	reliability_pid;
	uint16_t	reliability_pid_length;
	uint32_t	reliability_kind;
	uint32_t	reliability_reserve1;
	uint32_t	reliability_reserve2;

	/* PID_DURABILITY */
	uint16_t	durability_pid;
	uint16_t	durability_pid_length;
	uint32_t	durability_kind;

	/* PID PID_DEADLINE */
	uint16_t	deadline_pid;
	uint16_t	deadline_pid_length;
	duration_t	deadline_kind;

	/* PID_LIVELINESS */
	uint16_t	liveliness_pid;
	uint16_t	liveliness_pid_length;
	uint32_t	liveliness_kind;
	duration_t	lease_duration;

	/* PID_OWNERSHIP */
	uint16_t	ownership_pid;
	uint16_t	ownership_pid_length;
	uint32_t	ownership_kind;

	/* PID_OWNERSHIP_STRENGTH */
	uint16_t	ownership_strength_pid;
	uint16_t	ownership_strength_pid_length;
	uint32_t	ownership_strength_value;

	/* PID_E2E_PROTECTION */
	uint16_t	e2e_pid;
	uint16_t	e2e_pid_length;
	uint32_t	e2e_kind;

	/* PID_AGENT_ENDPOINT */
	uint16_t	agent_pid;
	uint16_t	agent_length;
	uint32_t	agent_value;
	/* PID_TOPIC_NAME */
	/* PID_TYPE_NAME  */
	/* PID_CRC16_IDL  */
};

#endif
