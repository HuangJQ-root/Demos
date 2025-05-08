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

#ifndef MVBS_CORE_DISCOVERY_BUILDIN_PROXY_H
#define MVBS_CORE_DISCOVERY_BUILDIN_PROXY_H

#ifdef __MVBS_CORE_SOURCE__
#include <mvbs/base_type.h>
#include <mvbs/utils/bitmap.h>
#include <mvbs/rtps/sequence_number.h>

struct rtps_sn_set;

#define MAX_SUPPORT_READERS			256
#define MAX_SUPPORT_WRITERS			256

#define BUILDIN_READER_PROXY_BITMAP_SIZE	(256/BITS_PER_LONG)
#define BUILDIN_WRITER_PROXY_BITMAP_SIZE	(256/BITS_PER_LONG)

struct buildin_reader_proxy {
	/* This acknack_count records the max acknack_count received, and is
	 * used to reject the acknack package whose count <= acknack_count.
	 */
	int32_t			acknack_count;

	uint8_t			durability_kind;

	uint8_t			reliable:1;
	uint8_t			use_multicast:1;

	uint16_t		start_sn;
	uint16_t		avail_bits;
	ulong_t			sent_map[BUILDIN_READER_PROXY_BITMAP_SIZE];
};

struct buildin_writer_proxy {
	int32_t			acknack_count;
	int32_t			heartbeat_count;

	uint8_t			use_multicast:1;
	uint8_t			suppress_unicast:1;
	uint8_t			unknown_eid:1;
	uint8_t			reliable:1;

	uint16_t		start_sn;
	uint16_t		avail_bits;
	ulong_t			recv_map[BUILDIN_WRITER_PROXY_BITMAP_SIZE];
};

struct buildin_proxies {
	struct buildin_writer_proxy		pdp_reader;

	struct buildin_writer_proxy		pub_reader;
	struct buildin_writer_proxy		sub_reader;
	struct buildin_writer_proxy		p2p_reader;
	struct buildin_writer_proxy		request_reader;
	struct buildin_writer_proxy		reply_reader;
	struct buildin_writer_proxy		recorder_reader;

	struct buildin_reader_proxy		pub_writer;
	struct buildin_reader_proxy		sub_writer;
	struct buildin_reader_proxy		p2p_writer;
	struct buildin_reader_proxy		request_writer;
	struct buildin_reader_proxy		reply_writer;
	struct buildin_reader_proxy		recorder_writer;
};

void buildin_reader_proxy_init(struct buildin_reader_proxy *proxy,
				bool reliable,
				uint8_t durabilityKind);
void buildin_writer_proxy_init(struct buildin_writer_proxy *proxy);


void buildin_writer_proxy_set_sn(struct buildin_writer_proxy *proxy,
				        const struct rtps_sn *sn);

bool buildin_writer_proxy_test_sn(struct buildin_writer_proxy *proxy,
				        const struct rtps_sn *sn);

uint16_t buildin_writer_proxy_to_sn_set(struct buildin_writer_proxy *proxy,
					       struct rtps_sn_set *set,
					       uint16_t max_bits);
#endif

#endif
