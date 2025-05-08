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
#include <mvbs/errno.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/mm.h>
#include <mvbs/utils/timer.h>
#include <mvbs/utils/time.h>
#include <mvbs/rtps/message.h>
#include <mvbs/adapter/adapter.h>

static int32_t mvbs_core_init(struct participant *ptcp)
{
	int32_t ret = 0;
	size_t	i;

	const participant_attr_t *ptcp_attr = ptcp->attr;

	/* Init Participant */
	ret = ptcp_init(ptcp, ptcp_attr);
	if (ret < 0) {
		pr_err(ret, "Fail to initialized ptcp: %s", ptcp_attr->name);
		return ret;
	}

	/* create user reader */
	for (i = 0U; i < ptcp_attr->reader_num; i++) {
		ret = reader_init(&ptcp_attr->readers[i]);
		if (ret != 0) {
			pr_err(ret, "Fail to create user reader: %d/%d.\n", i,
							ptcp_attr->reader_num);

			goto ERROR_INIT_ENTITY;
		}
	}

	/* create user writer */
	for (i = 0U; i < ptcp_attr->writer_num; i++) {
		ret = writer_init(&ptcp_attr->writers[i]);
		if (ret != 0) {
			pr_err(ret, "Fail to create user writer: %d/%d\n", i,
						       ptcp_attr->writer_num);
			goto ERROR_INIT_ENTITY;
		}
	}

	return 0;

ERROR_INIT_ENTITY:
	ptcp_deinit(ptcp);

	return ret;
}

int32_t mvbs_participant_init(struct participant *ptcp)
{
	if (ptcp == NULL) {
		pr_err(ERR_INVALID, "participant hasn't provided!\n");
		return -ERR_INVALID;
	}

	return mvbs_core_init(ptcp);
}

void mvbs_participant_deinit(struct participant *ptcp)
{
	(void)ptcp_destroy(ptcp);
}

/* FIXME: used for test case */
uint16_t mvbs_get_rtps_header_size(void)
{
	return msg_get_header_raw_size();
}

int32_t mvbs_get_udp_rx_buffer_unuse_size(struct participant *ptcp)
{
	return mvbs_udp_rx_buffer_unuse_size(ptcp);
}

int32_t mvbs_get_local_rx_buffer_unuse_size(struct participant *ptcp)
{
	return mvbs_local_rx_buffer_unuse_size(ptcp);
}

int32_t mvbs_get_local_rx_buffer_total_size(struct participant *ptcp)
{
	return mvbs_local_rx_buffer_total_size(ptcp);
}

bool mvbs_recv_should_rework(struct participant *ptcp)
{
	return !mvbs_local_rx_buffer_is_empty(ptcp);
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
