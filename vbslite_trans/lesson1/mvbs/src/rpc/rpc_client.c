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

#include <mvbs/errno.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/log.h>
#include <mvbs/utils/mm.h>
#include <mvbs/core/netio/tcp.h>
#include <rpc/rpc.h>

#define	RPC_CALLBACK_MAX		16
#define	RPC_SN_VALID_BITS		31U
#define	RPC_SN_VALID_MASK		(uint32_t)(~((uint32_t)1<<RPC_SN_VALID_BITS))
#define	RPC_SN_MAX			(uint32_t)((uint32_t)1<<RPC_SN_VALID_BITS)

struct rpc_client_handler {
	uint32_t		sn;
#define	REQ_FLAGS_STREAM	1
	int32_t			req_flags;
	rpc_client_cb_t		cb;
	void			*arg;
	uint32_t		timeout;
};

struct rpc_client {
	int32_t				sockfd;
	uint32_t			srv_addr[4];
	uint16_t			srv_port;
	uint32_t			sn;
	struct rpc_client_handler	handlers[RPC_CALLBACK_MAX];
	int32_t				cur_handler_num;
};

int32_t rpc_client_send(struct rpc_client *cli, const char *buf, uint32_t len)
{
	int32_t ret	= 0;
	char *send_buf	= NULL;

	if (!rpc_client_is_valid(cli)) {
		return -ERR_INVALID;
	}

	if (buf == NULL) {
		return -ERR_NOBUFS;
	}

	/*change const char* to char* */
	mvbs_memcpy(&send_buf, &buf, sizeof(char*));

	ret = mvbs_tcp_socket_send(cli->sockfd, send_buf, len);
	if (ret < 0) {
		pr_debug("rpc client send fail, ret = %d", ret);
	}

	return ret;
}

static int32_t rpc_client_recv(struct rpc_client *cli, char *buf, uint32_t buf_size)
{
	int32_t ret = 0;

	ret = mvbs_tcp_socket_recv(cli->sockfd, buf, buf_size);
	if (ret == 0) {
		pr_info("server closed");
	}
	if (ret < 0) {
		pr_debug("rpc client recv fail, ret = %d", ret);
	}

	return ret;
}

static inline void rpc_client_sn_inc(struct rpc_client *cli)
{
	cli->sn = (cli->sn + 1U) & RPC_SN_VALID_MASK;
}

static inline int32_t rpc_client_sn_is_valid(uint32_t sn)
{
	return (sn >= RPC_SN_MAX) ? 0 : 1;
}

static inline struct rpc_client_handler *rpc_client_get_handler(
					 struct rpc_client *cli, uint32_t sn)
{
	int32_t index = 0;

	if (sn >= RPC_SN_MAX) {
		return NULL;
	}

	index = (int32_t)sn % RPC_CALLBACK_MAX;

	return &cli->handlers[index];
}

uint32_t rpc_client_alloc_sn(struct rpc_client *cli, uint32_t timeout,
			     rpc_client_cb_t cb, void *arg, int32_t is_stream,
			     uint32_t preset_sn)
{
	int32_t i	= 0;
	int32_t index	= 0;
	uint32_t sn	= 0;

	struct rpc_client_handler *handler = NULL;

	if (!rpc_client_is_valid(cli)) {
		return RPC_INVALID_SN;
	}

	if ((cb == NULL) || (arg == NULL)) {
		return RPC_INVALID_SN;
	}

	if (preset_sn != RPC_INVALID_SN) {
		handler = rpc_client_get_handler(cli, preset_sn);
		if (handler == NULL) {
			return RPC_INVALID_SN;
		}

		if (handler->sn != preset_sn) {
			return RPC_INVALID_SN;
		}

		handler->cb		= cb;
		handler->arg		= arg;
		handler->timeout	= timeout;

		return preset_sn;
	}

	if (cli->cur_handler_num >= RPC_CALLBACK_MAX) {
		return RPC_INVALID_SN;
	}

	for (i = 0; i < RPC_CALLBACK_MAX; i++) {
		index = (int32_t)cli->sn % RPC_CALLBACK_MAX;

		if (rpc_client_sn_is_valid(cli->handlers[index].sn) > 0) {
			rpc_client_sn_inc(cli);
			continue;
		}

		cli->handlers[index].sn		= cli->sn;
		cli->handlers[index].cb		= cb;
		cli->handlers[index].arg	= arg;
		cli->handlers[index].timeout	= timeout;

		if (is_stream > 0) {
			cli->handlers[index].req_flags = REQ_FLAGS_STREAM;
		} else {
			cli->handlers[index].req_flags = 0;
		}

		sn = cli->sn;

		rpc_client_sn_inc(cli);

		cli->cur_handler_num++;

		return sn;
	}

	return RPC_INVALID_SN;
}

void rpc_client_free_sn(struct rpc_client *cli, uint32_t sn)
{
	int32_t index = 0;

	if (!rpc_client_is_valid(cli)) {
		return;
	}

	index = (int32_t)sn % RPC_CALLBACK_MAX;

	cli->handlers[index].cb		= NULL;
	cli->handlers[index].arg	= NULL;
	cli->handlers[index].req_flags	= 0;
	cli->handlers[index].timeout	= 0;
	cli->handlers[index].sn		= RPC_INVALID_SN;

	cli->cur_handler_num--;
}

static bool rpc_client_check_header(struct rpc_client *cli, struct rpc_header *header)
{
	struct rpc_client_handler *handler = NULL;

	if (header->magic_num != RPC_HEAD_MAGIC) {
		return false;
	}

	if ((header->msg_type == (uint32_t)RPC_TYPE_NORM_REQ)
		|| (header->msg_type == (uint32_t)RPC_TYPE_STREAM_REQ)) {
		return false;
	}

	handler = rpc_client_get_handler(cli, header->sn);
	if (handler == NULL) {
		return false;
	}

	if ((handler->req_flags == REQ_FLAGS_STREAM)
		&& (header->msg_type == (uint32_t)RPC_TYPE_NORM_RES)) {
		return false;
	}

	if (!(handler->req_flags == REQ_FLAGS_STREAM)
		&& ((header->msg_type == (uint32_t)RPC_TYPE_STREAM_RES)
		|| (header->msg_type == (uint32_t)RPC_TYPE_STREAM_STOP))) {
		return false;
	}

	if (handler->sn != header->sn) {
		return false;
	}

	return true;
}

static int32_t rpc_client_check_packet_ready(struct rpc_client *cli, struct rpc_header *header)
{
	int32_t cache_length	= 0;
	int32_t ret		= 0;

	struct mvbs_cdr mcdr_stream;
	char header_buf[RPC_HEADER_SIZE];

	ret = mvbs_tcp_socket_recv_peek(cli->sockfd, header_buf, RPC_HEADER_SIZE, &cache_length);
	if (ret <= 0) {
		return ret;
	}

	mcdr_init_buffer(&mcdr_stream, (uint8_t *)header_buf, RPC_HEADER_SIZE);

	if (rpc_header_deserialize(&mcdr_stream, header) < 0) {
		return -ERR_MCDR;
	}

	if ((RPC_HEADER_SIZE + header->body_len) > (uint32_t)cache_length) {
		return -ERR_NODATA;
	}

	return ret;
}

static void rpc_client_handle_timeout(struct rpc_client *cli,  struct mvbs_cdr *mcdr_stream, int32_t index)
{
	int32_t rpc_errno = RPC_ERRNO_TIMEOUT;

	if (!mcdr_serialize_int32_t(mcdr_stream, rpc_errno)) {
		return;
	}

	mcdr_reset_buffer(mcdr_stream);

	(void)cli->handlers[index].cb(mcdr_stream, cli->handlers[index].arg, 1);

	rpc_client_free_sn(cli, cli->handlers[index].sn);
}

static void rpc_client_check_timeout(struct rpc_client *cli,  struct mvbs_cdr *mcdr_stream,
					uint32_t timer_cnt)
{
	static uint32_t last_timer_cnt = (uint32_t)-1;

	int32_t i		= 0;
	uint32_t time_interval	= 0;

	if (!rpc_client_is_valid(cli)) {
		return;
	}

	if (last_timer_cnt == (uint32_t)-1) {
		last_timer_cnt = timer_cnt;/* for first enter this function */
	}

	if (timer_cnt  >= last_timer_cnt) {
		time_interval = timer_cnt - last_timer_cnt;
	} else {
		time_interval = 0xFFFFFFFFU - (last_timer_cnt - timer_cnt - 1U);
	}

	last_timer_cnt = timer_cnt;

	/* TIMEOUT Handling */
	for (i = 0; i < RPC_CALLBACK_MAX; i++) {
		if (cli->handlers[i].cb == NULL) {
			continue;
		}

		if (cli->handlers[i].timeout == (uint32_t)-1) {
			continue;
		}

		if (cli->handlers[i].timeout == (uint32_t)0) {
			rpc_client_handle_timeout(cli, mcdr_stream, i);
			continue;
		}

		if ((cli->handlers[i].timeout - time_interval)
						> cli->handlers[i].timeout) {
			rpc_client_handle_timeout(cli, mcdr_stream, i);
			continue;
		}

		cli->handlers[i].timeout -= time_interval;
	}
}

static void rpc_client_handle_disconnect(struct rpc_client *cli, struct mvbs_cdr *mcdr_stream)
{
	int32_t i 		= 0;
	int32_t rpc_errno	= RPC_ERRNO_CONNCLOSE;

	for (i = 0; i < RPC_CALLBACK_MAX; i++) {
		if (cli->handlers[i].cb == NULL) {
			continue;
		}

		if (!mcdr_serialize_int32_t(mcdr_stream, rpc_errno)){
			return;
		}

		mcdr_reset_buffer(mcdr_stream);

		(void)cli->handlers[i].cb(mcdr_stream, cli->handlers[i].arg, 1);

		rpc_client_free_sn(cli, cli->handlers[i].sn);
	}
}

void rpc_client_recv_loop(struct rpc_client *cli, uint32_t timer_cnt,
					     char *buf, uint32_t buf_size)
{
	int32_t ret = 0;
	int32_t len = 0;

	struct mvbs_cdr mcdr_stream;
	struct rpc_header header;
	struct rpc_client_handler *cli_handler = NULL;

	if ((!rpc_client_is_valid(cli)) || (buf == NULL)){
		return;
	}

	if (buf_size <= RPC_HEADER_SIZE) {
		pr_err(ERR_NOBUFS, "buffer size is to small!");
		return;
	}

	mcdr_init_buffer(&mcdr_stream, (uint8_t *)buf, buf_size);

	rpc_client_check_timeout(cli, &mcdr_stream, timer_cnt);

	/* check one packet data is ready or not */
	ret = rpc_client_check_packet_ready (cli, &header);
	if (ret == 0) {
		rpc_client_handle_disconnect(cli, &mcdr_stream);
		rpc_client_destroy(cli);
		return;
	}
	if (ret < 0) {
		return;
	}

	/* check user buf length is enough or not */
	if (buf_size <= (RPC_HEADER_SIZE + header.body_len)) {
		pr_err(ERR_NOBUFS, "buffer size is to small!");
		return;
	}

	/* put data of one packet into buf */
	len = rpc_client_recv(cli, buf, RPC_HEADER_SIZE + header.body_len);
	if (len == 0) {
		rpc_client_handle_disconnect(cli, &mcdr_stream);
		rpc_client_destroy(cli);
		return;
	}
	if (len < 0) {
		return;
	}

	/* check this packet is valid or not */
	if (!rpc_client_check_header(cli, &header)) {
		return;
	}

	mcdr_init_buffer_offset(&mcdr_stream, (uint8_t *)buf, buf_size, RPC_HEADER_SIZE);

	cli_handler = rpc_client_get_handler(cli, header.sn);
	if (cli_handler == NULL) {
		return;
	}

	if (header.msg_type == (uint32_t)RPC_TYPE_FAIL) {
		(void)cli_handler->cb(&mcdr_stream, cli_handler->arg, 1);
		rpc_client_free_sn(cli, cli_handler->sn);
	} else {
		(void)cli_handler->cb(&mcdr_stream, cli_handler->arg, 0);
	}

	if ((header.msg_type == (uint32_t)RPC_TYPE_STREAM_STOP)
		|| (header.msg_type == (uint32_t)RPC_TYPE_NORM_RES)) {
		rpc_client_free_sn(cli, header.sn);
	}
}

struct rpc_client *rpc_client_new(const char *server_addr, const uint16_t port)
{
	int32_t ret		= 0;
	struct rpc_client* cli	= NULL;

	if ((server_addr == NULL) || (port == 0U)) {
		return NULL;
	}

	cli = mvbs_malloc(sizeof(struct rpc_client), MVBS_MM_ALIGN_DEFAULT);
	if (cli == NULL) {
		return NULL;
	}

	mvbs_memzero(cli, sizeof(struct rpc_client));

	cli->sockfd = mvbs_tcp_socket_open();
	if (cli->sockfd < 0) {
		pr_err(cli->sockfd, "failed to create socket");
		mvbs_free(cli);
		return NULL;
	}

	ret = mvbs_tcp_inet_aton(server_addr, cli->srv_addr);
	if (ret < 0) {
		pr_err(ret, "server ip address is invalid");
		mvbs_free(cli);
		return NULL;
	}

	cli->srv_port 		= port;
	cli->cur_handler_num 	= 0;

	return cli;
}

int32_t rpc_client_connect(struct rpc_client *cli)
{
	int32_t i	= 0;
	int32_t ret	= 0;

	if (!rpc_client_is_valid(cli)) {
		return -ERR_INVALID;
	}

	ret = mvbs_tcp_socket_connect(cli->sockfd, cli->srv_addr, cli->srv_port);
	if (ret == -ERR_INPROGRESS) {
		pr_info("client is trying to connect the server");
		return ret;
	}
	if (ret < 0) {
		pr_err(ret, "connect Error");
		return ret;
	}

	for (i = 0; i < RPC_CALLBACK_MAX; i++) {
		cli->handlers[i].sn = RPC_INVALID_SN;
	}

	pr_info("connect success");

	return 0;
}

void rpc_client_destroy(struct rpc_client *cli)
{
	if (cli == NULL) {
		return;
	}

	if (cli->sockfd >= 0) {
		(void)mvbs_tcp_socket_close(cli->sockfd);
		cli->sockfd = -1;
	}

	mvbs_free(cli);
}

bool rpc_client_is_valid(struct rpc_client *cli)
{
	if ((cli == NULL) || (cli->sockfd == -1)) {
		return false;
	}

	return true;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
