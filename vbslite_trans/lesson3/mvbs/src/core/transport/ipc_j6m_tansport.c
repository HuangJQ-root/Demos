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
#include <mvbs/utils/mm.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/log.h>
#include <mvbs/adapter/adapter.h>

#ifndef MVBS_IPC_TXBUFSIZE
#define MVBS_IPC_TXBUFSIZE 4090
#endif

#ifndef MVBS_IPC_RXBUFSIZE
#define MVBS_IPC_RXBUFSIZE 4090
#endif

#ifndef MVBS_IPC_J6M_ENABLED
int32_t mvbs_ipc_j6m_send(void *buff, uint16_t size)
{
	(void)buff;
	(void)size;
	return 0;
}
#endif

static struct ipc_j6m_transport *ipc_j6m_trans = NULL;

static void ipc_j6m_trans_setup(struct ipc_j6m_transport *trans)
{
	ipc_j6m_trans = trans;
}

static void ipc_j6m_trans_free(struct ipc_j6m_transport *trans)
{
	mvbs_free(trans);
}

static uint32_t ipc_j6m_trans_get_rx_buffer_size(void)
{
	struct ipc_j6m_transport *trans = NULL;

	trans = ipc_j6m_trans;

	if (trans == NULL) {
		return 0;
	}

	return trans->cfg->buf_info.buffer_size;
}

static int32_t ipc_j6m_trans_recvfrom(struct ipc_j6m_transport *trans, uint8_t *buf,
					size_t buf_size, locator_t *dst)
{
	int32_t ret = 0;

	if ((trans == NULL) || (buf == NULL) || (buf_size == 0)) {
		return -ERR_INVALID;
	}

	ret = udp_rx_buffer_get_pkg(&trans->rx_ringbuffer, NULL, buf, buf_size);
	if (ret <= 0) {
		return ret;
	}

	if (dst != NULL) {
		dst->kind = (uint16_t)LOCATOR_KIND_IPC;
	}

	return ret;
}

static struct mvbs_cdr *ipc_j6m_trans_get_tx_buffer(struct transport *this)
{
	struct ipc_j6m_transport *trans;

	if (this == NULL) {
		return NULL;
	}

	trans = container_of(this, struct ipc_j6m_transport, ops);

	return &trans->cdr;
}

static int32_t ipc_j6m_trans_sendto(struct transport *this, locator_t *dst,
						const void *buf, size_t size)
{
	(void) this;
	(void) dst;

	void *data = (void *)buf;

	int32_t ret	= 0;

	ret = mvbs_ipc_j6m_send(data, size);

	return ret;
}

static void ipc_j6m_trans_recv_handle(struct transport *this, uint32_t recv_max_pkg)
{
	locator_t	loc;
	int32_t		ret;
	(void) recv_max_pkg;

	struct ipc_j6m_transport	*trans;

	if (this == NULL) {
		pr_err(ERR_INVALID, "The param transport is null!\n");

		return;
	}

	trans = container_of(this, struct ipc_j6m_transport, ops);

	if (ipc_j6m_trans_get_rx_buffer_size() <= 0U) {
		return ;
	}

	while (mvbs_true) {
		ret = ipc_j6m_trans_recvfrom(trans, trans->recv_buff,
					      trans->recv_size, &loc);
		if (ret < 0) {
			break;
		}

		trans->recv_callback(trans->recv_args, trans->recv_buff, ret, &loc);
	}
}

static int32_t ipc_j6m_trans_serialized_locator(struct transport *this,
						struct mvbs_cdr *cdr,
						const endpoint_attr_t *attr,
						uint16_t pid)
{
	struct ipc_j6m_transport *trans;

	(void)attr;

	if (this == NULL) {
		return -ERR_INVALID;
	}

	trans = container_of(this, struct ipc_j6m_transport, ops);

	(void)cdr_serialize_locator(cdr, &trans->locator, pid);
	if (mcdr_buffer_has_error(cdr)) {
		return -ERR_NOMEM;
	}

	return 0;
}

static bool ipc_j6m_trans_detect_master_link(struct transport *this,
					     locator_t *loc)
{
	struct ipc_j6m_transport *trans;

	if (this == NULL) {
		return false;
	}

	if (loc == NULL) {
		return false;
	}

	trans = container_of(this, struct ipc_j6m_transport, ops);

	(void)trans;

	if (loc->kind != (uint16_t)LOCATOR_KIND_IPC) {
		return false;
	}

	return true;
}

static int32_t ipc_j6m_trans_detect_reachable(struct transport *this,
					      locator_t *loc)
{
	struct ipc_j6m_transport *trans;

	if (this == NULL) {
		return -ERR_INVALID;
	}

	if (loc == NULL) {
		return -ERR_INVALID;
	}

	trans = container_of(this, struct ipc_j6m_transport, ops);

	(void)trans;

	if (loc->kind != (uint16_t)LOCATOR_KIND_IPC) {
		return -ERR_FAULT;
	}

	return 0;
}

static void ipc_j6m_trans_destroy(struct transport *this)
{
	struct ipc_j6m_transport *trans;

	if (this == NULL) {
		pr_err(ERR_INVALID, "The param transport is null!\n");
		return;
	}

	trans = container_of(this, struct ipc_j6m_transport, ops);

	ipc_j6m_trans_free(trans);

	ipc_j6m_trans_setup(NULL);
}

static struct ipc_j6m_transport *ipc_j6m_trans_alloc(transport_rx_cb fn,
								void *args)
{
	ipc_j6m_transport_t *trans	= NULL;

	trans = (struct ipc_j6m_transport *)mvbs_malloc(sizeof(*trans),
						MVBS_MM_ALIGN_DEFAULT);
	if (trans == NULL) {
		pr_err(ERR_NOMEM, "Fail to alloc struct ipc_j6m_transport.");
		return NULL;
	}

	mvbs_memzero(trans, sizeof(*trans));

	trans->ops.get_tx_buffer      = ipc_j6m_trans_get_tx_buffer;
	trans->ops.sendto	      = ipc_j6m_trans_sendto;
	trans->ops.recv		      = ipc_j6m_trans_recv_handle;
	trans->ops.serialize_locator  = ipc_j6m_trans_serialized_locator;
	trans->ops.detect_master_link = ipc_j6m_trans_detect_master_link;
	trans->ops.detect_reachable   = ipc_j6m_trans_detect_reachable;
	trans->ops.destroy	      = ipc_j6m_trans_destroy;

	trans->recv_callback	      = fn;
	trans->recv_args	      = args;

	return trans;
}

bool mvbs_ipc_j6m_rx_indication(const uint8_t *buff, uint16_t len)
{
	struct ipc_j6m_transport *trans = NULL;
	int32_t ret = 0;

	CHECKPOINT_LABEL("RX_INDICATION_START");

	trans = ipc_j6m_trans;

	if (trans == NULL) {
		return -ERR_NOENT;
	}

	/* Copy data from Buf to Ringbuffer */
	ret = udp_rx_buffer_put_pkg(&trans->rx_ringbuffer, 1u,
				buff, (size_t)len);
	if (ret != 0) {
		pr_err(ret, "IPC_J6M: Fail to put pkg into ringbuffer: %d", ret);
	}

	CHECKPOINT_LABEL("RX_INDICATION_END");

	return ret;
}

/* old callback, just for compatible */
int32_t j6_ipc_mvbs_rx_indication(const uint8_t* data, uint16_t len)
{
	mvbs_ipc_j6m_rx_indication(data, len);

	return 0;
}

struct transport *transport_ipc_j6m_create(struct participant *ptcp,
				       const struct transport_info *trans_info,
				       transport_rx_cb fn)
{
	static struct ipc_j6m_transport	*trans = NULL;
	const struct transport_info_ipc_j6m *cfg;
	int32_t ret;

	if ((ptcp == NULL) || (trans_info == NULL) || (fn == NULL)) {
		return NULL;
	}

	cfg = trans_info->ipc_j6m;
	if (cfg == NULL) {
		return NULL;
	}

	/* Only one instance returned. */
	if (trans != NULL) {
		return &trans->ops;
	}

	trans = ipc_j6m_trans_alloc(fn, ptcp);

	ret = udp_rx_buffer_init(&trans->rx_ringbuffer, cfg->buf_info.buffer,
							cfg->buf_info.buffer_size);
	if (ret != 0) {
		pr_err(ret, "Fail to init transport ringbuffer of IPC J6m.");

		goto FAIL_RINGBUFFER;
	}

	mcdr_init_buffer(&trans->cdr, cfg->tx_buf.buffer,
				      cfg->tx_buf.buffer_size);

	trans->recv_buff = cfg->rx_buf.buffer;
	trans->recv_size = cfg->rx_buf.buffer_size;

	trans->locator.kind = (uint16_t)LOCATOR_KIND_IPC;

	trans->cfg = trans_info->ipc_j6m;

	ipc_j6m_trans_setup(trans);

	return &trans->ops;

FAIL_RINGBUFFER:
	ipc_j6m_trans_free(trans);
	trans = NULL;

	return NULL;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
