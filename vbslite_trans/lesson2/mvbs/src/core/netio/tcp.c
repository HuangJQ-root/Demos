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

#include <mvbs/utils/mm.h>
#include <mvbs/utils/log.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/rx_buffer.h>
#include <mvbs/core/netio/socket.h>
#include <mvbs/core/netio/tcp.h>
#include <mvbs/core/netio/utils.h>
#include <mvbs/adapter/adapter.h>

/* FIXME: The max number of Tcp socket number supportted is different in
 * S32G_XCU and BZCU, thus the 10 set to TCP_SOCKET_NUM is for testing.
 */
#define TCP_SOCKET_NUM			10	/* TODO, FIXME */

#define TCP_INVALID_INDEX		(-1)
#define TCP_INVALID_SOCKFD		(-1)
#define TCP_PRIVBUFF_SIZE		2048U

/*TCP connect flag*/
#define TCP_NOTCONNECT		0	/* have not call tcp_connect */
#define TCP_CONNECTING		1	/* already call tcp_connect and is still connecting */
#define TCP_CONNECTED		2	/* connected interrupt is called */
#define TCP_CONNCOMFIRMED	3	/* connected is confirmed by tcp_connect */

/*
 * When several clients try to connect the server simultaneously, the interrupt will be called
 * and tcp_accept is not called yet, thus the server will ignore this connect. Using array and
 * two pointer to record all child socket fd allocated by server when tcp_accept haven't been
 * called.
 * for example: accepted_cnt == 2
 * -------------------
 * | fd  | fd  |empty|
 * -------------------
 *   |            |
 *  start        end
 */
typedef struct {
	uint8_t			accepted_cnt;
	mvbs_socket_id_t	accept_array[TCP_SOCKET_NUM-1];
	int32_t			start;
	int32_t			end;
} accept_data_t;

typedef struct {
	mvbs_socket_id_t	socket_id;
	uint8_t			active_socket;
	uint8_t			binded;
	uint8_t			connect_flag;
	uint8_t			close_wait;
	accept_data_t		*accept_data;
	uint8_t			*private_buffer;
	struct tcpip_rx_buffer	tcp_rx;
} mvbs_tcp_socket_t;

void mvbs_tcp_recv_indication(int32_t socket_id, void *buf, size_t buf_len,
			      uint32_t remote_addr, uint16_t remote_port,
			      void *priv);
void mvbs_tcp_event(int32_t socket_id, mvbs_net_event_t event);

static const struct mvbs_socket_ops tcp_socket_ops = {
	.rx_indication	= mvbs_tcp_recv_indication,
	.event		= mvbs_tcp_event
};

/*pointer array for all sock structs*/
static mvbs_tcp_socket_t* tcp_socks[TCP_SOCKET_NUM] = { NULL };

/*num of active socket, which will call connnect or accept soon*/
static int32_t active_socket_num = 0;

static int32_t mvbs_tcp_socket_get(mvbs_socket_id_t socket_id)
{
	int32_t index		= TCP_INVALID_INDEX;
	mvbs_tcp_socket_t *sock	= NULL;

	index = (int32_t)socket_id % TCP_SOCKET_NUM;

	sock = tcp_socks[index];
	if ((sock != NULL) && (sock->socket_id == socket_id)) {
		return index;
	}

	/*hash collision*/
	for (index = 0; index < TCP_SOCKET_NUM; index++) {
		sock = tcp_socks[index];
		if ((sock != NULL) && (sock->socket_id == socket_id)) {
			return index;
		}
	}

	return TCP_INVALID_INDEX;
}

static int32_t mvbs_tcp_socket_init(int32_t index, mvbs_socket_id_t socket_id)
{
	int32_t ret		= 0;
	mvbs_tcp_socket_t *sock	= NULL;

	if (tcp_socks[index] != NULL) {
		pr_warn("sock already exists, fd = %u, socket_id = %u", index, socket_id);
		return -ERR_SOCK;
	}

	tcp_socks[index] = mvbs_malloc(sizeof(mvbs_tcp_socket_t), MVBS_MM_ALIGN_DEFAULT);

	sock = tcp_socks[index];
	if (sock == NULL) {
		pr_warn("sock alloc fail, fd = %u, socket_id = %u", index, socket_id);
		return -ERR_NOMEM;
	}

	sock->socket_id		= socket_id;
	sock->binded		= 0;
	sock->connect_flag	= TCP_NOTCONNECT;
	sock->close_wait	= 0;
	sock->accept_data	= NULL;

	sock->private_buffer = mvbs_malloc(TCP_PRIVBUFF_SIZE, MVBS_MM_ALIGN_DEFAULT);
	if (sock->private_buffer == NULL) {
		pr_warn("malloc private buffer fail, fd = %u, socket_id = %u", index, socket_id);
		return -ERR_NOMEM;
	}

	ret = tcpip_rx_buffer_init(&sock->tcp_rx, sock->private_buffer, TCP_PRIVBUFF_SIZE);
	if (ret < 0) {
		pr_warn("init private buffer fail, fd = %u, socket_id = %u", index, socket_id);
		return ret;
	}

	return 0;
}

static int32_t mvbs_tcp_socket_alloc(mvbs_socket_id_t socket_id)
{
	int32_t index	= TCP_INVALID_INDEX;
	int32_t ret	= 0;

	index = (int32_t)socket_id % TCP_SOCKET_NUM;
	if (tcp_socks[index] == NULL) {
		goto tcp_index_valid;
	}

	/*hash collision*/
	for (index = 0; index < TCP_SOCKET_NUM; index++) {
		if (tcp_socks[index] == NULL) {
			goto tcp_index_valid;
		}
	}

	return TCP_INVALID_INDEX;

tcp_index_valid:
	ret = mvbs_tcp_socket_init(index, socket_id);
	if (ret < 0) {
		return TCP_INVALID_INDEX;
	}

	return index;
}

static void mvbs_tcp_socket_free(int32_t index)
{
	mvbs_tcp_socket_t *sock = NULL;

	sock = tcp_socks[index];
	if (sock == NULL) {
		pr_warn("sock free fail");
		return;
	}

	if (sock->active_socket == 1U) {
		active_socket_num--;
	}

	if (sock->private_buffer != NULL) {
		mvbs_free(sock->private_buffer);
	}

	mvbs_free(sock);

	tcp_socks[index] = NULL;

	return;
}

/* -------------------------------------------------------------------
 *			PUBLIC INTERFACE (NETIO_TCP)
 * ------------------------------------------------------------------- */

int32_t mvbs_tcp_socket_open(void)
{
	int32_t index			= TCP_INVALID_INDEX;
	int32_t sockfd			= TCP_INVALID_SOCKFD;
	mvbs_socket_id_t socket_id	= 0;
	mvbs_net_err_t ret		= MVBS_NET_E_OK;
	mvbs_socket_t *sock		= NULL;

	ret = mvbs_tcp_socket_create(&socket_id);
	if (ret != MVBS_NET_E_OK) {
		pr_warn("create tcp socket fail, err = %d", (int32_t)ret);
		return -ERR_SOCK;
	}

	sock = mvbs_socket_alloc(socket_id);
	if (sock == NULL) {
		mvbs_socket_close(socket_id);
		return -ERR_NOMEM;
	}

	index = mvbs_tcp_socket_alloc(socket_id);
	if (index == TCP_INVALID_INDEX) {
		mvbs_socket_close(socket_id);
		pr_warn("socket %u create fail", socket_id);
		return -ERR_NOMEM;
	}

	if (mvbs_socket_setup_ops((int32_t)socket_id, &tcp_socket_ops, NULL) < 0) {
		pr_warn("socket_id %u set callback fail", socket_id);
		return -ERR_SOCK;
	}

	/*for active socket(not socket created by accept)*/
	tcp_socks[index]->active_socket = 1U;
	active_socket_num++;

	sockfd = (int32_t)socket_id;

	return sockfd;
}

int32_t mvbs_tcp_socket_close(int32_t sockfd)
{
	int32_t index			= TCP_INVALID_INDEX;
	mvbs_socket_id_t socket_id	= (mvbs_socket_id_t)sockfd;

	index = mvbs_tcp_socket_get(socket_id);
	if (index == TCP_INVALID_INDEX) {
		return -ERR_INVALID;
	}

	mvbs_socket_close(socket_id);

	mvbs_tcp_socket_free(index);

	mvbs_socket_free(socket_id);

	return 0;
}

int32_t mvbs_tcp_socket_bind(int32_t sockfd, uint16_t port)
{
	int32_t index			= 0;
	mvbs_net_err_t ret		= MVBS_NET_E_OK;
	mvbs_tcp_socket_t *sock		= NULL;
	mvbs_socket_id_t socket_id	= (mvbs_socket_id_t)sockfd;

	if (port == 0U) {
		return -ERR_INVALID;
	}

	index = mvbs_tcp_socket_get(socket_id);
	if (index == TCP_INVALID_INDEX) {
		return -ERR_INVALID;
	}

	sock = tcp_socks[index];
	if (sock->binded == 1U) {
		pr_warn("socket %d is already binded", socket_id);
		return -ERR_BIND;
	}

	ret = mvbs_tcp_bind(socket_id, 0, port);
	if (ret != MVBS_NET_E_OK) {
		pr_warn("tcpip bind fail, fd = %u", socket_id);
		return -ERR_BIND;
	}

	sock->binded = 1;

	return 0;
}

int32_t mvbs_tcp_socket_listen(int32_t sockfd, uint16_t max_channels)
{
	int32_t index			= 0;
	mvbs_net_err_t ret		= MVBS_NET_E_OK;
	mvbs_tcp_socket_t *sock		= NULL;
	mvbs_socket_id_t socket_id	= (mvbs_socket_id_t)sockfd;

	if ((max_channels <= 0U) || (max_channels > (uint16_t)TCP_SOCKET_NUM)) {
		pr_warn("max_channels should be (0,%d)", TCP_SOCKET_NUM);
		return -ERR_INVALID;
	}

	index = mvbs_tcp_socket_get(socket_id);
	if (index == TCP_INVALID_INDEX) {
		return -ERR_INVALID;
	}

	sock = tcp_socks[index];
	if (sock->accept_data != NULL) {
		pr_warn("socket %u is listening", socket_id);
		return -ERR_LISTEN;
	}

	sock->accept_data = mvbs_malloc(sizeof(accept_data_t), MVBS_MM_ALIGN_DEFAULT);
	if (sock->accept_data == NULL) {
		pr_warn("tcpip tcp set accept data fail, fd = %u", socket_id);
		return -ERR_NOMEM;
	}

	mvbs_memzero(sock->accept_data, sizeof(accept_data_t));

	ret = mvbs_tcp_listen(socket_id, max_channels);
	if (ret != MVBS_NET_E_OK) {
		pr_warn("tcpip tcp listen fail, fd = %u", socket_id);
		return -ERR_LISTEN;
	}

	return 0;
}

int32_t mvbs_tcp_socket_connect(int32_t sockfd, const uint32_t* srv_addr, uint16_t port)
{
	int32_t index			= 0;
	mvbs_net_err_t ret		= MVBS_NET_E_OK;
	mvbs_tcp_socket_t *sock		= NULL;
	mvbs_socket_id_t socket_id	= (mvbs_socket_id_t)sockfd;

	if ((srv_addr == NULL) || (port == 0U)) {
		return -ERR_INVALID;
	}

	index = mvbs_tcp_socket_get(socket_id);
	if (index == TCP_INVALID_INDEX) {
		return -ERR_INVALID;
	}

	sock = tcp_socks[index];

	/*check connect flag*/
	if (sock->connect_flag == (uint8_t)TCP_CONNECTING) {
		return -ERR_INPROGRESS;
	}

	if (sock->connect_flag == (uint8_t)TCP_CONNECTED) {
		sock->connect_flag = TCP_CONNCOMFIRMED;
		return 0;
	}

	ret = mvbs_tcp_connect(socket_id, *srv_addr, mvbs_htons(port));
	if (ret != MVBS_NET_E_OK) {
		pr_warn("tcpip connect fail, fd = %u", socket_id);
		return -ERR_CONNECT;
	}

	if (sock->connect_flag == (uint8_t)TCP_NOTCONNECT) {
		sock->connect_flag = TCP_CONNECTING;
		return -ERR_INPROGRESS;
	}

	if (sock->connect_flag == (uint8_t)TCP_CONNECTED) {
		sock->connect_flag = TCP_CONNCOMFIRMED;
	}

	return 0;
}

/* if need, some parameter like ip address can be added to this interface as out
 * parameter. Currently upper layer donot need information of client address
 * int32_t tcp_accept(int32_t sockfd, char* uint32_t* cli_addr, uint16_t* port) */
int32_t mvbs_tcp_socket_accept(int32_t sockfd)
{
	int32_t index				= TCP_INVALID_INDEX;
	int32_t child_sockfd			= TCP_INVALID_SOCKFD;
	mvbs_tcp_socket_t* sock			= NULL;
	accept_data_t *accept_data		= NULL;
	mvbs_socket_id_t socket_id		= (mvbs_socket_id_t)sockfd;
	mvbs_socket_id_t child_socket_id	= (mvbs_socket_id_t)0;

	index = mvbs_tcp_socket_get(socket_id);
	if (index == TCP_INVALID_INDEX) {
		return -ERR_INVALID;
	}

	sock = tcp_socks[index];
	if (sock->accept_data == NULL) {
		return -ERR_INVALID;
	}

	/* connection is not ready*/
	accept_data = sock->accept_data;
	if (accept_data->accepted_cnt == 0U) {
		return -ERR_NODATA;
	}

	/*after the accept interrupt*/

	child_socket_id = accept_data->accept_array[accept_data->start];
	accept_data->start = (accept_data->start + 1) % (TCP_SOCKET_NUM - 1);
	accept_data->accepted_cnt--;

	child_sockfd = (int32_t)child_socket_id;

	return child_sockfd;
}

int32_t mvbs_tcp_socket_send(int32_t sockfd, void *buf, uint32_t len)
{
	int32_t index			= 0;
	mvbs_net_err_t ret		= MVBS_NET_E_OK;
	mvbs_tcp_socket_t *sock		= NULL;
	mvbs_socket_id_t socket_id	= (mvbs_socket_id_t) sockfd;

	if (buf == NULL) {
		return -ERR_INVALID;
	}

	if (len == 0U) {
		return 0;
	}

	index = mvbs_tcp_socket_get(socket_id);
	if (index == TCP_INVALID_INDEX) {
		return -ERR_INVALID;
	}

	sock = tcp_socks[index];
	if ((sock->active_socket == 1U) && (sock->connect_flag != (uint8_t)TCP_CONNCOMFIRMED)) {
		pr_warn("the connection between socket %u and its peer has not been created", socket_id);
		return -ERR_SEND;
	}

	ret = mvbs_tcp_send(socket_id, (uint8_t *)buf, len);
	if (ret != MVBS_NET_E_OK) {
		pr_warn("tcpip tcp transmit fail, fd = %u", socket_id);
		return -ERR_SEND;
	}

	return (int32_t)len;
}

int32_t mvbs_tcp_socket_recv(int32_t sockfd, void *buf, uint32_t len)
{
	int32_t index			= 0;
	int32_t rx_len			= 0;
	mvbs_net_err_t ret		= MVBS_NET_E_OK;
	mvbs_tcp_socket_t *sock		= NULL;
	mvbs_socket_id_t socket_id	= (mvbs_socket_id_t)sockfd;

	if ((buf == NULL) || (len == 0U)) {
		return -ERR_INVALID;
	}

	index = mvbs_tcp_socket_get(socket_id);
	if (index == TCP_INVALID_INDEX) {
		return -ERR_INVALID;
	}

	sock = tcp_socks[index];

	rx_len = tcpip_rx_buffer_out(&sock->tcp_rx, buf, len);
	if ((rx_len == 0) && (sock->close_wait == 1U)) {
		pr_debug("peer of socket %d is closed", socket_id);
		return 0;
	}
	if (rx_len <= 0) {
		return -ERR_NODATA;
	}

	ret = mvbs_tcp_received(socket_id, (uint32_t)rx_len);
	if (ret != MVBS_NET_E_OK) {
		pr_warn("increase tcp recv window fail, fd = %u", socket_id);
		return -ERR_RECV;
	}

	return rx_len;
}

int32_t mvbs_tcp_socket_recv_peek(int32_t sockfd, void *buf, uint32_t len, int32_t *total_recvd_size)
{
	int32_t index			= 0;
	int32_t rx_len			= 0;
	mvbs_tcp_socket_t *sock		= NULL;
	mvbs_socket_id_t socket_id	= (mvbs_socket_id_t)sockfd;

	if ((buf == NULL) || (len == 0U ) || (total_recvd_size == NULL)) {
		return -ERR_INVALID;
	}

	index = mvbs_tcp_socket_get(socket_id);
	if (index == TCP_INVALID_INDEX) {
		return -ERR_INVALID;
	}

	sock = tcp_socks[index];

	rx_len = tcpip_rx_buffer_peek(&sock->tcp_rx, buf, len);
	if ((rx_len == 0) && (sock->close_wait == 1U)) {
		pr_info("peer of socket %d is closed", socket_id);
		return 0;
	}
	if (rx_len <= 0) {
		return -ERR_NODATA;
	}

	*total_recvd_size = tcpip_rx_buffer_len(&sock->tcp_rx);

	return rx_len;
}

int32_t mvbs_tcp_inet_aton(const char *src, void *dst)
{
	int32_t ret = 0;

	/*note inet_aton return 1 means success, */
	ret = mvbs_inet_aton(src, dst);
	if (ret <= 0) {
		pr_warn("string of ip address is invalid");
		return -ERR_INVALID;
	}

	return 0;
}


/* -------------------------------------------------------------------
 *			INTERRUPT (NETIO_TCP)
 * ------------------------------------------------------------------- */

/*NOTE: this function is called in interrupt*/
void mvbs_tcp_recv_indication(int32_t socket_id, void *buf, size_t buf_len,
			      uint32_t remote_addr, uint16_t remote_port,
			      void *priv)
{
	(void)remote_addr;
	(void)remote_port;
	(void)priv;

	int32_t index 		= TCP_INVALID_INDEX;
	mvbs_tcp_socket_t *sock	= NULL;

	index = mvbs_tcp_socket_get(socket_id);
	if (index == TCP_INVALID_INDEX) {
		return;
	}

	sock = tcp_socks[index];

	if (sock->private_buffer != NULL) {
		(void)tcpip_rx_buffer_in(&sock->tcp_rx, buf, buf_len);
	} else {
		pr_warn("Socket %u tcp private_buffer isn't set", socket_id);
	}
}

/*NOTE: this function is called in interrupt*/
void mvbs_tcp_event(int32_t socket_id, mvbs_net_event_t event)
{
	int32_t index 		= TCP_INVALID_INDEX;
	mvbs_tcp_socket_t *sock	= NULL;

	index = mvbs_tcp_socket_get(socket_id);
	if (index == TCP_INVALID_INDEX) {
		return;
	}

	sock = tcp_socks[index];

	switch (event) {
	case MVBS_NET_EV_SOCK_CLOSED:
		break;
	case MVBS_NET_EV_TCP_FIN_RECEIVED:
		sock->close_wait = 1;
		break;
	case MVBS_NET_EV_TCP_RESET:
		mvbs_tcp_socket_free(index);
		break;
	default:
		pr_warn("socket %u receive non-TCP event", socket_id);
		break;
	}
}

/*NOTE: this function is called in interrupt*/
void mvbs_tcp_connected(mvbs_socket_id_t socket_id)
{
	int32_t index 		= TCP_INVALID_INDEX;
	mvbs_tcp_socket_t *sock	= NULL;

	index = mvbs_tcp_socket_get(socket_id);
	if (index == TCP_INVALID_INDEX) {
		return;
	}

	sock = tcp_socks[index];

	sock->connect_flag = TCP_CONNECTED;
}

//TODO, FIXME, return value?
uint8_t mvbs_tcp_accepted(mvbs_socket_id_t socket_id,
			   mvbs_socket_id_t socket_id_connected,
			   uint32_t ipv4_addr, uint16_t port)
{
	(void)ipv4_addr;
	(void)port;

	int32_t index 			= TCP_INVALID_INDEX;
	int32_t child_index		= TCP_INVALID_INDEX;
	int32_t child_sockfd		= (int32_t)socket_id_connected;
	int32_t ret			= 0;
	mvbs_tcp_socket_t *sock		= NULL;
	accept_data_t *accept_data	= NULL;

	index = mvbs_tcp_socket_get(socket_id);
	if (index == TCP_INVALID_INDEX) {
		return MVBS_NET_ERR_INVPARAM;
	}

	sock = tcp_socks[index];
	if (sock->accept_data == NULL) {
		return MVBS_NET_ERR_INVPARAM;
	}

	ret = mvbs_socket_setup_ops(child_sockfd, &tcp_socket_ops, NULL);
	if (ret < 0) {
		return MVBS_NET_ERR_INVPARAM;
	}

	child_index = mvbs_tcp_socket_alloc(socket_id_connected);
	if (child_index == TCP_INVALID_INDEX) {
		pr_warn("alloc child socket fail");
		return MVBS_NET_ERR_INVPARAM;
	}

	accept_data = sock->accept_data;

	accept_data->accept_array[accept_data->end] = socket_id_connected;
	accept_data->end = (accept_data->end + 1) % (TCP_SOCKET_NUM - 1);
	accept_data->accepted_cnt++;

	return MVBS_NET_E_OK;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
