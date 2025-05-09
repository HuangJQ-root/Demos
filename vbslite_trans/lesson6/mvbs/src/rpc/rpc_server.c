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
#include <mvbs/utils/mm.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/log.h>
#include <mvbs/core/netio/tcp.h>
#include <rpc/rpc.h>

struct rpc_connection {
	int32_t			sockfd;
};

struct rpc_server {
	int32_t			sockfd;
	struct rpc_connection	*connection;
	uint16_t		max_connects;
	uint16_t		cur_connects;
	uint16_t		port;
	rpc_server_cb_t		service_entry;
};

int32_t rpc_connection_send(struct rpc_connection *conn, const char *buf, uint32_t len)
{
	int32_t ret	= 0;
	char *send_buf	= NULL;

	if ((conn == NULL) || (conn->sockfd == -1)) {
		return -ERR_INVALID;
	}

	if (buf == NULL) {
		return -ERR_NOBUFS;
	}

	/*change const char* to char* */
	mvbs_memcpy(&send_buf, &buf, (uint32_t)sizeof(char*));

	ret = mvbs_tcp_socket_send(conn->sockfd, send_buf, len);
	if (ret < 0) {
		pr_debug("rpc client send fail, ret = %d", ret);
	}

	return ret;
}

static int32_t rpc_connection_recv(struct rpc_connection *conn, char *buf,
							uint32_t buf_size)
{
	int32_t ret = 0;

	ret = mvbs_tcp_socket_recv(conn->sockfd, buf, buf_size);
	if (ret == 0) {
		pr_info("client closed");
	}
	if (ret < 0) {
		pr_debug("rpc server recv fail, ret = %d", ret);
	}

	return ret;
}

static struct rpc_connection *rpc_server_connection_new(struct rpc_server *srv,
							int32_t sockfd)
{
	uint16_t i = 0U;

	struct rpc_connection *conn = NULL;

	for (i = 0U; i < srv->max_connects; i++) {
		conn = &srv->connection[i];
		if (conn->sockfd > 0) {
			continue;
		}

		conn->sockfd = sockfd;

		srv->cur_connects++;

		return conn;
	}

	return NULL;
}

static void rpc_server_connection_destroy(struct rpc_server *srv,
					  struct rpc_connection *conn)
{
	if (srv->cur_connects == 0U) {
		pr_info("All connections have been destroyed");
		return;
	}

	(void)mvbs_tcp_socket_close(conn->sockfd);

	conn->sockfd = -1;

	srv->cur_connects--;
}

static void rpc_server_accept(struct rpc_server *srv)
{
	int32_t sockfd = 0;

	struct rpc_connection *connect = NULL;

	sockfd = mvbs_tcp_socket_accept(srv->sockfd);
	if (sockfd < 0) {
		return;
	}

	/*
	 * Currently this is no need, since if connection is full,
	 * the accept interrupt will not be triggered.
	 */
	if (srv->cur_connects >= srv->max_connects) {
		pr_err(ERR_NOBUFS, "rpc server connect is full!");
		(void)mvbs_tcp_socket_close(sockfd);
		return;
	}

	connect = rpc_server_connection_new(srv, sockfd);
	if (connect == NULL) {
		pr_err(ERR_NOMEM, "rpc server couldn't alloc connection!");
		(void)mvbs_tcp_socket_close(sockfd);
		return;
	}

	pr_info("server create a connection");
}

static bool rpc_server_check_header(struct rpc_header *header)
{
	if (header->magic_num != RPC_HEAD_MAGIC) {
		return false;
	}

	if ((header->msg_type == (uint32_t)RPC_TYPE_NORM_RES)
		|| (header->msg_type == (uint32_t)RPC_TYPE_STREAM_RES)) {
		return false;
	}

	return true;
}

static int32_t rpc_server_check_packet_ready(struct rpc_connection *conn, struct rpc_header *header)
{
	int32_t cache_length	= 0;
	int32_t ret		= 0;

	char header_buf[RPC_HEADER_SIZE];
	struct mvbs_cdr mcdr_stream;

	ret = mvbs_tcp_socket_recv_peek(conn->sockfd, header_buf, RPC_HEADER_SIZE, &cache_length);
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

void rpc_server_recv_loop(struct rpc_server *srv, char *buf, uint32_t buf_size)
{
	int32_t i	= 0;
	int32_t conns	= 0;
	int32_t ret	= 0;
	int32_t len	= 0;

	struct mvbs_cdr	mcdr_stream;
	struct rpc_header	header;
	struct rpc_connection  *conn = NULL;

	if ((srv == NULL) || (srv->sockfd == -1) || (buf == NULL)) {
		return;
	}

	if (buf_size <= RPC_HEADER_SIZE) {
		pr_err(ERR_NOBUFS, "buffer size is to small!");
		return;
	}

	rpc_server_accept(srv);

	conns = (int32_t)srv->cur_connects;

	for (i = 0; i < (int32_t)srv->max_connects; i++) {
		if (conns <= 0) {
			break;
		}

		conn = &srv->connection[i];
		if (conn->sockfd < 0) {
			continue;
		}

		conns--;

		while (mvbs_true) {
			ret = rpc_server_check_packet_ready(conn, &header);
			if (ret == 0) {
				rpc_server_connection_destroy(srv, conn);
				break;
			}
			if (ret < 0) {
				break;
			}

			if (buf_size <= (RPC_HEADER_SIZE + header.body_len)) {
				pr_err(ERR_NOBUFS, "buffer size is to small!");
				break;
			}

			len = rpc_connection_recv(conn, buf, RPC_HEADER_SIZE + header.body_len);
			if (len == 0) {
				rpc_server_connection_destroy(srv, conn);
				break;
			}
			if (len < 0) {
				break;
			}

			if (!rpc_server_check_header(&header)) {
				break;
			}

			mcdr_init_buffer_offset(&mcdr_stream, (uint8_t *)buf, buf_size, RPC_HEADER_SIZE);

			(void)srv->service_entry(conn, &mcdr_stream, &header);
		}
	}
}

static int32_t rpc_server_initialize(struct rpc_server *srv, uint16_t port,
			   uint16_t max_connects, rpc_server_cb_t cb)
{
	int32_t err	= 0;
	uint32_t size	= 0;

	/*init server socket*/
	srv->sockfd = mvbs_tcp_socket_open();
	if (srv->sockfd < 0) {
		pr_err(srv->sockfd, "server socket fail! socket=%d", srv->sockfd);
		err = srv->sockfd;
		return err;
	}

	err = mvbs_tcp_socket_bind(srv->sockfd, port);
	if (err < 0) {
		pr_err(err, "server bind fail!");
		(void)mvbs_tcp_socket_close(srv->sockfd);
		return err;
	}

	err = mvbs_tcp_socket_listen(srv->sockfd, max_connects);
	if (err < 0) {
		pr_err(err, "server listen fail!");
		(void)mvbs_tcp_socket_close(srv->sockfd);
		return err;
	}

	/*init server connections*/
	size = (uint32_t)max_connects * (uint32_t)sizeof(struct rpc_connection);

	srv->connection = mvbs_malloc(size, MVBS_MM_ALIGN_DEFAULT);
	if (srv->connection == NULL) {
		(void)mvbs_tcp_socket_close(srv->sockfd);
		return -ERR_NOMEM;
	}

	mvbs_memzero(srv->connection, (size_t)size);

	/*init other parameters*/
	srv->max_connects	= max_connects;
	srv->cur_connects	= 0U;
	srv->port		= port;
	srv->service_entry	= cb;

	return 0;
}

struct rpc_server *rpc_server_new(const uint16_t port, uint16_t max_connects,
						 rpc_server_cb_t cb)
{
	int32_t ret		= 0;
	struct rpc_server* srv	= NULL;

	if ((port == 0U) || (max_connects == 0U)) {
		return NULL;
	}

	srv = mvbs_malloc(sizeof(struct rpc_server), MVBS_MM_ALIGN_DEFAULT);
	if (srv == NULL) {
		return NULL;
	}

	mvbs_memzero(srv, sizeof(struct rpc_server));

	ret = rpc_server_initialize(srv, port, max_connects, cb);
	if (ret < 0) {
		mvbs_free(srv);
		return NULL;
	}

	pr_info("server successfully initialized");

	return srv;
}

static void rpc_server_deinit(struct rpc_server *srv)
{
	(void)mvbs_tcp_socket_close(srv->sockfd);

	mvbs_free(srv->connection);

	srv->sockfd		= -1;
	srv->connection		= NULL;
	srv->port		= 0U;
	srv->max_connects	= 0U;
	srv->cur_connects	= 0U;
	srv->service_entry	= NULL;
}

void rpc_server_destroy(struct rpc_server *srv)
{
	uint16_t i = 0U;

	if (srv == NULL) {
		return;
	}

	for (i = 0U; i < srv->max_connects; i++) {
		/* sockfd available scope: [0, ....] */
		if (srv->connection[i].sockfd >= 0) {
			(void)mvbs_tcp_socket_close(srv->connection[i].sockfd);
		}
	}

	rpc_server_deinit(srv);

	mvbs_free(srv);
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
