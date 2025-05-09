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

/*
 * These interfaces defined in this file are for AD.
 */
#include <core/core.h>
#include <mvbs/mvbs.h>
#include <mvbs/utils/mm.h>
#include <mvbs/rte/Dds_Adaptor_Interface.h>
#include <mvbs/core/netio/socket.h>

/* weak function */
extern Rte_Dds_Participant Rte_Dds_GetParticipant(void);

#pragma weak Rte_Dds_GetParticipant
Rte_Dds_Participant Rte_Dds_GetParticipant(void)
{
	return NULL;
}

static struct participant *ptcp;
static void *sample_buf = NULL;

static void dds_on_data_available(struct reader *r, instance_id id);

sint32 DDS_Init_Adaptor(void)
{
	struct participant *ptcp;
	struct reader *r;
	struct writer *w;
	int32_t ret;

	static const struct reader_listener ad_default_reader_listener = {
		.on_data		= dds_on_data_available,
		.on_matched		= NULL,
		.on_e2e_exception	= NULL,
	};

	static const struct writer_listener ad_default_writer_listener = {
		.on_matched		= NULL,
	};

	ptcp = Rte_Dds_GetParticipant();

	ret = mvbs_participant_init(ptcp);
	if (ret < 0) {
		return DDS_ERR_INVALID;
	}

	sample_buf = mvbs_malloc(ptcp->attr->max_topic_size, 0);
	if (sample_buf == NULL) {
		pr_err(ERR_NOMEM, "Fail to malloc a buffer for deserialize topic data.");
		return DDS_ERR_NOMEM;
	}

	foreach_ptcp_reader(ptcp, r) {
		reader_listener_setup(r, &ad_default_reader_listener);
	}

	foreach_ptcp_writer(ptcp, w) {
		writer_listener_setup(w, &ad_default_writer_listener);
	}

	ret = ptcp_enable(ptcp);
	if (ret < 0) {
		mvbs_free(sample_buf);

		/* Maybe deinit RTE writer, reader, transid config here */
		mvbs_participant_deinit(ptcp);
		return DDS_ERR_INVALID;
	}

	return 0;
}

sint32 DDS_Pub_Adaptor(const char *topic_name, void *sample, uint64 sn, uint64 timestamp)
{
	(void)sn;
	(void)timestamp;

	struct writer *w = NULL;
	struct writer_cache_change *cc = NULL;

	int32_t ret = (int32_t)TRANS_CODE_ALL_SUCCESS_ALL_OUT;

	if ((topic_name == NULL) || (sample == NULL)) {
		pr_err(ERR_INVALID, "input param null.\n");
		return DDS_ERR_INVALID;
	}

	w = ptcp_get_writer_with_topic(ptcp, topic_name);
	if (w == NULL) {
		pr_err(ERR_INVALID, "get writer(%s) info failed.\n",
		       string_or_null(topic_name));
		return DDS_ERR_NOENTITY;
	}

	cc = writer_submit_change(w, INSTANCE_INVALID, (const uint8_t *)sample, 0);
	if (cc == NULL) {
		pr_err(ERR_NOMEM, "topic:%s writer fail!\n",
		       string_or_null(topic_name));
		return DDS_ERR_NOMEM;
	}

	udp_transmit_hook_set_topicname(topic_name);

	ret = writer_send_data(w, cc);

	udp_transmit_hook_clr_topicname();

	if(ret != (int32_t)TRANS_CODE_ALL_SUCCESS_ALL_OUT){
		return DDS_ERR_SEND_ERR;
	}

	return 0;
}

#pragma weak DDS_Recv_Adaptor
void DDS_Recv_Adaptor(const char* topic_name, const void* payload, uint16 size)
{
	(void)topic_name;
	(void)payload;
	(void)size;
}

static void dds_on_data_available(struct reader *r, instance_id id)
{
	(void)id;
	bool retcode;
	const char* topic_name;

	topic_name = reader_get_topicname(r);
	if (topic_name == NULL) {
		pr_err(ERR_NOENT, "Fail to get reader type name.");
		return ;
	}

	retcode = reader_get_sample(r, sample_buf, 0U, NULL, true);
	if (!retcode) {
		pr_err(ERR_NOENT, "Fail to get reader [%s] sample.", string_or_null(topic_name));
		return ;
	}

	DDS_Recv_Adaptor(topic_name, sample_buf, (uint16_t)r->attr->ep_attr.type->type_size());
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
