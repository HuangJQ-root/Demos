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
#include <mvbs/utils/tracepoint.h>
#include <mvbs/utils/rx_buffer.h>
#include <mvbs/utils/log.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/mm.h>
#include <mvbs/core/netio/socket.h>

static inline struct udp_rx_buffer *ptcp_get_local_ringbuf(struct participant *ptcp)
{
	struct udp_transport	*trans = NULL;

	trans = (struct udp_transport *)ptcp->ptransport;

	return &trans->ringbuf_local;
}

int32_t local_trans_send(struct udp_transport *trans, const void *buf,
							size_t length)
{
	int32_t ret;

	if (trans->cfg_local == NULL) {
		pr_verb("Local communication hasn't enabled.");

		return -ERR_NOMEM;
	}

	if ((buf == NULL) || (length <= 0u)) {
		return -ERR_INVALID;
	}

	ret = udp_rx_buffer_put_pkg(&trans->ringbuf_local, 1, buf, length);
	if (ret != 0) {
		pr_err(ret, "Local: udp_rx_buffer_put_pkg returns: %d", ret);
	}

	return ret;
}

static int32_t local_trans_recv(struct udp_transport *trans, uint8_t *buf, size_t buf_size,
								locator_t *dst)
{
	int32_t ret	= 0;

	ret = udp_rx_buffer_get_pkg(&trans->ringbuf_local, NULL, buf, buf_size);
	if (ret <= 0) {
		return ret;
	}

	if (dst != NULL) {
		dst->kind = (uint16_t)LOCATOR_KIND_LOCAL;
	}

	return ret;
}

void local_trans_recv_handle(struct transport *this, uint32_t recv_max_pkg)
{
	struct udp_transport *trans;
	locator_t loc;

	int32_t ret = 0;
	uint32_t i = 0;

	if (this == NULL) {
		pr_err(ERR_INVALID, "The param transport is null!\n");

		return;
	}

	trans = container_of(this, struct udp_transport, ops);

	if (mvbs_local_rx_buffer_get_size(trans->ptcp) <= 0U) {
		return;
	}

	if (recv_max_pkg == 0) {
		while (mvbs_true) {
			ret = local_trans_recv(trans, trans->recv_buff,
					       trans->recv_size, &loc);
			if (ret < 0) {
				break;
			}

			trans->recv_callback(trans->ptcp, trans->recv_buff,
					     ret, &loc);
		}
	} else {
		for (i = 0; i < recv_max_pkg; i++) {
			ret = local_trans_recv(trans, trans->recv_buff,
					       trans->recv_size, &loc);
			if (ret < 0) {
				break;
			}

			trans->recv_callback(trans->ptcp, trans->recv_buff,
					     ret, &loc);
		}
	}
}

void transport_local_create(struct udp_transport *trans,
			    struct participant *ptcp,
			    const struct transport_info *trans_info,
			    transport_rx_cb fn)
{
	const struct transport_info_local *local_comm_info;
	int32_t ret;

	(void)ptcp;
	(void)fn;

	if (trans == NULL) {
		return;
	}

	trans->cfg_local = NULL;

	if (trans_info->local_comm == NULL) {
		return;
	}

	local_comm_info = trans_info->local_comm;

	if (local_comm_info != NULL) {
		ret = udp_rx_buffer_init(&trans->ringbuf_local,
					 local_comm_info->buf_info.buffer,
					 local_comm_info->buf_info.buffer_size);

		if (ret != 0) {
			pr_err(ret, "Failed to init Local ring buffer.");
			return;
		}
	}

	trans->cfg_local = trans_info->local_comm;

	return;
}

bool mvbs_local_rx_buffer_is_empty(struct participant *ptcp)
{
	if (ptcp == NULL) {
		return true;
	}

	if (udp_rx_buffer_len(ptcp_get_local_ringbuf(ptcp)) == 0) {
		return true;
	}

	return false;
}

uint32_t mvbs_local_rx_buffer_total_size(struct participant *ptcp)
{
	if (ptcp == NULL) {
		return 0;
	}

	return udp_rx_buffer_size(ptcp_get_local_ringbuf(ptcp));
}

uint32_t mvbs_local_rx_buffer_get_size(struct participant *ptcp)
{
	if (ptcp == NULL) {
		return 0;
	}

	return udp_rx_buffer_len(ptcp_get_local_ringbuf(ptcp));
}

uint32_t mvbs_local_rx_buffer_unuse_size(struct participant *ptcp)
{
	if (ptcp == NULL) {
		return 0;
	}

	return udp_rx_buffer_unused(ptcp_get_local_ringbuf(ptcp));
}

uint32_t mvbs_local_rx_buffer_pkg_count(struct participant *ptcp)
{
	return udp_rx_buffer_get_pkg_count(ptcp_get_local_ringbuf(ptcp));
}

uint32_t mvbs_local_rx_buffer_cur_usage_rate(struct participant *ptcp)
{
	return udp_rx_buffer_usage_rate(ptcp_get_local_ringbuf(ptcp));
}

uint32_t mvbs_local_rx_buffer_max_usage_rate(struct participant *ptcp)
{
	struct udp_transport	*trans = NULL;

	if (ptcp == NULL)
		return 0;

	trans = (struct udp_transport *)ptcp->ptransport;

	return trans->max_rate_local_buf;
}

void mvbs_local_rx_buffer_max_usage_rate_update(struct participant *ptcp)
{
	struct udp_transport	*trans = NULL;

	if (ptcp == NULL)
		return ;

	trans = (struct udp_transport *)ptcp->ptransport;

	int32_t rate = mvbs_local_rx_buffer_cur_usage_rate(ptcp);

	if (trans->max_rate_local_buf < rate) {
		trans->max_rate_local_buf = rate;
	}
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
