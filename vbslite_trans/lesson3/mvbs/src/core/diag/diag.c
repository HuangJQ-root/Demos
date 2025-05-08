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
#include <diag/diag.h>
#include <diag/query.h>
#include <diag/recorder.h>
#include <mvbs/utils/time.h>
#include <messages/message_factory.h>

#ifdef MVBS_DIAG_REQUEST_READER_ENABLE
void diag_request_on_data(const struct buildin_reader *r,
                        struct participant_proxy *ptcp_proxy,
                        const struct submessage_data *msg,
                        const struct submessage_data_extra *extra)
{
	(void)r;
	(void)ptcp_proxy;
	(void)msg;
	(void)extra;

	if (!ptcp_proxy_has_diag_request_writer(ptcp_proxy)) {
		return;
	}

	if (msg->extra_flags == EXTRA_FLAGS_RECORDER_CMD) {
		if (extra->ptcp->recorder_proxy != ptcp_proxy) {
			extra->ptcp->recorder_proxy = ptcp_proxy;
		}

		if (extra->size) {
			recorder_request_on_data(extra->ptcp,
				(void *)(extra->data), extra->size);

			recorder_reply_data(extra->ptcp,
				(void *)(extra->data), extra->size);
		}
	}

	if (msg->extra_flags == EXTRA_FLAGS_NORMAL) {
		query_request_on_data(ptcp_proxy,
				(void *)extra->data, extra->size);
	}
}

void diag_request_on_heartbeat(const struct buildin_reader *r,
				     struct participant_proxy *ptcp_proxy,
				     const struct submessage_heartbeat *msg)
{
	(void)r;
	(void)ptcp_proxy;
	(void)msg;
}

void diag_request_reader_on_ptcp_online(const struct buildin_reader *r,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy)
{
	(void)r;
	(void)ptcp;

	if (!ptcp_proxy_has_diag_request_writer(ptcp_proxy)) {
		return ;
	}
}

void diag_request_reader_on_ptcp_offline(const struct buildin_reader *r,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy)
{
	(void)r;
	(void)ptcp;
	(void)ptcp_proxy;

	if (!ptcp_proxy_has_diag_request_writer(ptcp_proxy)) {
		return ;
	}
}
#endif


#ifdef MVBS_DIAG_REQUEST_WRITER_ENABLE
int32_t diag_request_send_data(struct participant *ptcp,
			       struct participant_proxy *proxy,
			       uint16_t extra_flags,
			       bool (*send_data)(mvbs_cdr_t *cdr, void *arg),
			       void *arg)
{
	struct rtps_time	cur_time;
	int32_t ret;
	locator_t *meta_uc_loc;

	if (ptcp == NULL) {
		pr_info("Invalid parameters.");
		return -ERR_INVALID;
	}

	if (proxy == NULL) {
		pr_info("Has no recorder_proxy.");
		return -ERR_INVALID;
	}

	mvbs_cdr_t *cdr;

	cdr = ptcp_get_tx_buffer(ptcp);

	mcdr_reset_buffer(cdr);

	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

	/* INFO_TS submessage */
	mvbs_get_time(&cur_time.seconds, &cur_time.nanosec);
	(void)rtps_msg_add_submsg_timestamp(cdr, &cur_time);

	meta_uc_loc = ptcp_proxy_get_meta_uc_loc(proxy);
	ret = ptcp_send_submsg_data_wrap(ptcp, meta_uc_loc,false,
					 cdr, extra_flags,
					 &ptcp->diag_request_sn,
					 &ENTITYID_DIAG_REQUEST_WRITER,
					 &ENTITYID_DIAG_REQUEST_READER,
					 send_data, arg);
	if (!ret) {
		pr_err(ERR_INVALID, "Send cmd reply error.");
		return -ERR_MCDR;
	}

        return 0;
}

void diag_request_on_acknack(const struct buildin_writer *w,
			     struct participant_proxy *ptcp_proxy,
			     const struct submessage_acknack *msg)
{
	(void)w;
	(void)ptcp_proxy;
	(void)msg;
}

void diag_request_writer_on_ptcp_online(const struct buildin_writer *w,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy)
{
	(void)w;
	(void)ptcp;

	if (!ptcp_proxy_has_diag_request_reader(ptcp_proxy)) {
		return ;
	}
}

void diag_request_writer_on_ptcp_offline(const struct buildin_writer *w,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy)
{
	(void)w;
	(void)ptcp;

	if (!ptcp_proxy_has_diag_request_reader(ptcp_proxy)) {
		return ;
	}
}
#endif

#ifdef MVBS_DIAG_REPLY_READER_ENABLE
void diag_reply_on_data(const struct buildin_reader *r,
                        struct participant_proxy *ptcp_proxy,
                        const struct submessage_data *msg,
                        const struct submessage_data_extra *extra)
{
	(void)r;
	(void)ptcp_proxy;
	(void)msg;
	(void)extra;

	if (!ptcp_proxy_has_diag_reply_writer(ptcp_proxy)) {
		pr_info("no reply writer in remote");
		return;
	}

	switch (msg->extra_flags) {
	case EXTRA_FLAGS_NORMAL:
		query_reply_on_data(r, ptcp_proxy, msg, extra);
		break;

	case EXTRA_FLAGS_RECORDER_CMD:
		break;

	case EXTRA_FLAGS_RECORDER_DATA:
		break;

	default:
		break;
	}
}

void diag_reply_on_heartbeat(const struct buildin_reader *r,
				struct participant_proxy *ptcp_proxy,
				const struct submessage_heartbeat *msg)
{
	(void)r;
	(void)ptcp_proxy;
	(void)msg;

	return;
}

void diag_reply_reader_on_ptcp_online(const struct buildin_reader *r,
				      struct participant *ptcp,
				      struct participant_proxy *ptcp_proxy)
{
	(void)r;
	(void)ptcp;

	if (!ptcp_proxy_has_diag_reply_writer(ptcp_proxy)) {
		pr_info("Remote has no monitor writer.");
		return;
	}

	pr_info("Remote monitor writer ptcp [%s] online.", ptcp_proxy->ptcp_name);
}

void diag_reply_reader_on_ptcp_offline(const struct buildin_reader *w,
					struct participant *ptcp,
					struct participant_proxy *ptcp_proxy)
{
	(void)w;
	(void)ptcp;

	if (!ptcp_proxy_has_diag_reply_writer(ptcp_proxy)) {
		return;
	}

	return;
}
#endif

#ifdef MVBS_DIAG_REPLY_WRITER_ENABLE
int32_t diag_reply_send_data(struct participant *ptcp,
			     struct participant_proxy *proxy,
			     uint16_t extra_flags,
			     bool (*send_data)(mvbs_cdr_t *cdr, void *arg),
			     void *arg)
{
	struct rtps_time	cur_time;
	locator_t		*meta_uc_loc;
	int32_t ret;

	if (ptcp == NULL) {
		pr_info("Invalid parameters.");
		return -ERR_INVALID;
	}

	if (proxy == NULL) {
		pr_info("Has no recorder_proxy.");
		return -ERR_INVALID;
	}

	mvbs_cdr_t *cdr;

	cdr = ptcp_get_tx_buffer(ptcp);

	mcdr_reset_buffer(cdr);

	(void)rtps_msg_add_header(cdr, &ptcp->guid_prefix);

	/* INFO_TS submessage */
	mvbs_get_time(&cur_time.seconds, &cur_time.nanosec);
	(void)rtps_msg_add_submsg_timestamp(cdr, &cur_time);

	meta_uc_loc = ptcp_proxy_get_meta_uc_loc(proxy);
	ret = ptcp_send_submsg_data_wrap(ptcp, meta_uc_loc, false,
					 cdr, extra_flags,
					 &ptcp->diag_reply_sn,
					 &ENTITYID_DIAG_REPLY_WRITER,
					 &ENTITYID_DIAG_REPLY_READER,
					 send_data, arg);
	if (!ret) {
		pr_err(ERR_INVALID, "Send cmd reply error.");
		return -ERR_MCDR;
	}

        return 0;
}

void diag_reply_on_acknack(const struct buildin_writer *w,
				struct participant_proxy *ptcp_proxy,
				const struct submessage_acknack *msg)
{
	(void)w;
	(void)ptcp_proxy;
	(void)msg;

	return;
}

void diag_reply_writer_on_ptcp_online(const struct buildin_writer *w,
					struct participant *ptcp,
					struct participant_proxy *ptcp_proxy)
{
	(void)w;
	(void)ptcp;

	if (!ptcp_proxy_has_diag_reply_reader(ptcp_proxy)) {
		return;
	}

	pr_info("Remote monitor reader ptcp [%s] online.",
		ptcp_proxy->ptcp_name);

	return;
}

void diag_reply_writer_on_ptcp_offline(const struct buildin_writer *w,
					struct participant *ptcp,
					struct participant_proxy *ptcp_proxy)
{
	(void)w;
	(void)ptcp;

	if (!ptcp_proxy_has_diag_reply_reader(ptcp_proxy)) {
		return;
	}

	if (ptcp->recorder_proxy == ptcp_proxy) {
		ptcp->recorder_proxy = NULL;
	}

	return;
}
#endif

int32_t ptcp_diag_init(struct participant *ptcp)
{
	if (ptcp == NULL) {
		return -ERR_INVALID;
	}

	ptcp->recorder_proxy = NULL;

	rtps_sn_set_zero(&ptcp->diag_request_sn);
	rtps_sn_set_zero(&ptcp->diag_reply_sn);

	return 0;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
