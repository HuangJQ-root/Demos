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

#ifndef MVBS_CORE_DISCOVERY_SDDP_H
#define MVBS_CORE_DISCOVERY_SDDP_H

#include <mvbs/rtps/guid.h>
#include <mvbs/rtps/message.h>
#include <messages/message_receiver.h>

struct participant;
struct participant_proxy;

enum {
	PDP_READER = 0,
	PUB_READER,
	SUB_READER,
	P2P_READER,
	DIAG_REQUEST_READER,
	DIAG_REPLY_READER,
};

enum {
	PDP_WRITER = 0,
	PUB_WRITER,
	SUB_WRITER,
	P2P_WRITER,
	DIAG_REQUEST_WRITER,
	DIAG_REPLY_WRITER,
};

struct buildin_writer {
	char			*name;
	rtps_entity_id_t	eid;
	rtps_entity_id_t	remote_eid;

	bool			backup_link_enabled;

	void (*on_ptcp_online)(const struct buildin_writer *w,
			       struct participant *ptcp,
			       struct participant_proxy *ptcp_proxy);

	void (*on_ptcp_offline)(const struct buildin_writer *w,
				struct participant *ptcp,
				struct participant_proxy *ptcp_proxy);

	void (*on_acknack)(const struct buildin_writer *w,
			   struct participant_proxy  *ptcp_proxy,
			   const struct submessage_acknack *msg);
};

struct submessage_data_extra {
	struct participant	*ptcp;
	const struct rtps_time	*info_ts;	/* INFO_TS */
	const uint8_t		*data;
	uint16_t		size;
};

struct buildin_reader {
	char			*name;
	rtps_entity_id_t	eid;
	rtps_entity_id_t	remote_eid;

	bool			backup_link_enabled;

	void (*on_ptcp_online)(const struct buildin_reader *r,
			       struct participant *ptcp,
			       struct participant_proxy *ptcp_proxy);

	void (*on_ptcp_offline)(const struct buildin_reader *r,
				struct participant *ptcp,
				struct participant_proxy *ptcp_proxy);

	void (*on_data)(const struct buildin_reader *r,
			struct participant_proxy *ptcp_proxy,
			const struct submessage_data *msg,
			const struct submessage_data_extra *extra);

	void (*on_hearbeat)(const struct buildin_reader *r,
			    struct participant_proxy *ptcp_proxy,
                            const struct submessage_heartbeat *msg);

	void (*on_gap)(const struct buildin_reader *r,
		       const struct participant_proxy *ptcp_proxy,
		       const struct submessage_gap *msg);
};

bool ptcp_dpde_on_acknack(const struct message_receiver *receiver,
			  const struct submessage_acknack *acknack);
bool ptcp_dpde_on_heartbeat(const struct message_receiver *receiver,
			    const struct submessage_heartbeat *hb);
bool ptcp_dpde_on_gap(const struct message_receiver *receiver,
		      const struct submessage_gap *gap);
bool ptcp_dpde_on_data(const struct message_receiver *receiver,
		       const struct submessage_data *msg,
		       const uint8_t *pdata, uint16_t size);

void ptcp_dpde_on_remote_online(struct participant *ptcp,
			 struct participant_proxy *ptcp_proxy);
void ptcp_dpde_on_remote_offline(struct participant *ptcp,
			  struct participant_proxy *ptcp_proxy);

int32_t ptcp_discovery_init(struct participant *ptcp);
int32_t ptcp_discovery_start(struct participant *ptcp);
int32_t ptcp_discovery_stop(struct participant *ptcp);

void p2p_writer_send_hearbeat(const struct participant_proxy *ptcp_proxy,
	bool liveliness);

#endif /* !MVBS_CORE_SDDP_H */
