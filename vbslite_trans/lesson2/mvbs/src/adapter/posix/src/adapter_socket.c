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

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#ifdef	TARGET_PRODUCT_MINGW
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#include <mvbs/utils/cdefs.h>
#include <mvbs/utils/log.h>

#include "adapter_socket.h"

struct adapter_socket {
	sock_fd_t		fd;
	int			port;

#define ADAPTER_SOCK_UDP	0
#define ADAPTER_SOCK_TCP_LINK	1
#define ADAPTER_SOCK_TCP_DATA	2
	unsigned int		type;

	unsigned int		is_srv;

	struct sockaddr_in	server;

	adapter_socket_handle_t	handle;

#ifdef	TARGET_PRODUCT_MINGW
	struct event		*ev;
#endif
};

static struct adapter_socket adapter_sockets[256];

#ifdef TARGET_PRODUCT_MINGW
static struct event_base *base;

int adapter_socket_monitor_init(void)
{
	if (base != NULL)
		return 0;

	for (size_t i=0; i<ARRAY_SIZE(adapter_sockets); i++) {
		adapter_sockets[i].fd = ADAPTER_SOCK_INVALID;
		adapter_sockets[i].ev = NULL;
	}

	base = event_base_new();

	return 0;
}

void adapter_socket_monitor_loop(void)
{
	event_base_loop(base, EVLOOP_ONCE);
}

static int adapter_socket_monitor_add(struct adapter_socket *ms, uint32_t event_type)
{
	struct event *ev;

	ev = event_new(base, ms->fd, event_type | EV_PERSIST,
					(event_callback_fn)ms->handle, ms);

	/* Never timeout */
	event_add(ev, NULL);

	ms->ev = ev;

	return 0;
}

static int adapter_socket_monitor_mod(struct adapter_socket *ms, uint32_t event_type)
{
	if ((ms == NULL) || (sock_fd_is_invalid(ms->fd)))
		return -ERR_FAULT;

        event_del(ms->ev);

        event_assign(ms->ev, event_get_base(ms->ev), ms->fd,
					event_type | EV_PERSIST,
					(event_callback_fn)ms->handle, ms);

        event_add(ms->ev, NULL);

	return 0;
}

static int adapter_socket_monitor_del(struct adapter_socket *ms)
{
	if ((ms == NULL) || (sock_fd_is_invalid(ms->fd)))
		return -ERR_FAULT;

	event_free(ms->ev);

	ms->ev = NULL;

	return 0;
}

static int adapter_socket_set_nonblocking(sock_fd_t fd)
{
	return evutil_make_socket_nonblocking(fd);
}

#else
#include <sys/epoll.h>

static int	epoll_fd;

int adapter_socket_monitor_init(void)
{
	int fd;

	for (size_t i=0; i<ARRAY_SIZE(adapter_sockets); i++) {
		adapter_sockets[i].fd = -1;
	}

	fd = epoll_create(1);
	if (fd < 0) {
		perror("Failed to create epoll file descriptor\n");

		return -ERR_FAULT;
	}

	epoll_fd = fd;

	return 0;
}

void adapter_socket_monitor_loop(void)
{
	struct epoll_event events[32];

	int num_events;

	num_events = epoll_wait(epoll_fd, events, ARRAY_SIZE(events), -1);
	if (num_events <= 0) {
		if (errno == EINTR)
			return ;

		perror("Failed to wait file descriptor to epoll\n");
		return ;
	}

	for (int i=0; i<num_events; i++) {
		struct epoll_event *ev=&events[i];
		struct adapter_socket *ms;

		ms = ev->data.ptr;

		ms->handle(ms->fd, ev->events, ms);
	}
}

static int adapter_socket_monitor_add(struct adapter_socket *ms, uint32_t event_type)
{
	struct epoll_event event;

	if ((ms == NULL) || (sock_fd_is_invalid(ms->fd)))
		return -ERR_FAULT;

	memset(&event, 0, sizeof(event));

	event.events	= event_type;
	event.data.ptr	= ms;

	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, ms->fd, &event)) {
		perror("Failed to add file descriptor to epoll\n");

		return -ERR_FAULT;
	}

	return 0;
}

static int adapter_socket_monitor_mod(struct adapter_socket *ms, uint32_t event_type)
{
	struct epoll_event event;

	if ((ms == NULL) || (sock_fd_is_invalid(ms->fd)))
		return -ERR_FAULT;

	memset(&event, 0, sizeof(event));

	event.events	= event_type;
	event.data.ptr	= ms;

	if (epoll_ctl(epoll_fd, EPOLL_CTL_MOD, ms->fd, &event) == -1) {
		perror("Failed to modify file descriptor to epoll\n");

		return -ERR_FAULT;
	}

	return 0;
}

static int adapter_socket_monitor_del(struct adapter_socket *ms)
{
	if ((ms == NULL) || (sock_fd_is_invalid(ms->fd)))
		return -ERR_FAULT;

	if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, ms->fd, NULL)) {
		perror("Failed to delete file descriptor to epoll\n");

		return -ERR_FAULT;
	}

	return 0;
}

#include <fcntl.h>
#include <sys/socket.h>

/* return 0 on success, -1 on failure */
static int adapter_socket_set_nonblocking(sock_fd_t sockfd)
{
	int flags;

	flags = fcntl(sockfd, F_GETFL, 0);
	if (flags == -1) {
		perror("fcntl(F_GETFL)");

		return -1;
	}

	if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
		perror("fcntl(F_SETFL)");

		return -1;
	}

	return 0;
}
#endif

struct adapter_socket *adapter_socket_get(uint8_t index)
{
	return &adapter_sockets[index];
}

uint8_t adapter_socket_get_index(struct adapter_socket *ms)
{
	return ms - adapter_sockets;
}

sock_fd_t adapter_socket_get_fd(struct adapter_socket *ms)
{
	return ms->fd;
}

void adapter_socket_set_port(struct adapter_socket *ms, uint16_t port)
{
	ms->port = port;
}

bool adapter_socket_is_invalid(struct adapter_socket *ms)
{
	if (ms == NULL)
		return false;

	return sock_fd_is_invalid(ms->fd);
}

static struct adapter_socket *adapter_socket_alloc(void)
{
	for (size_t i=0; i<ARRAY_SIZE(adapter_sockets); i++) {
		if (sock_fd_is_invalid(adapter_sockets[i].fd))
			return &adapter_sockets[i];
	}

	return NULL;
}

void adapter_socket_free(struct adapter_socket *ms)
{
	if (sock_fd_is_invalid(ms->fd))
		return;

	adapter_socket_monitor_del(ms);

	close(ms->fd);

	ms->fd = ADAPTER_SOCK_INVALID;
}

struct adapter_socket *adapter_socket_alloc_udp(adapter_socket_handle_t fn)
{
	struct adapter_socket *ms = NULL;

	ms = adapter_socket_alloc();
	if (ms == NULL)
		return NULL;

	sock_fd_t sock = socket(AF_INET, SOCK_DGRAM, 0);
	adapter_socket_set_nonblocking(sock);

	ms->fd		= sock;
	ms->handle	= fn;
	ms->type	= ADAPTER_SOCK_UDP;

	adapter_socket_monitor_add(ms, ADAPTER_SOCK_READ);

	return ms;
}

struct adapter_socket *adapter_socket_alloc_tcp(void)
{
	struct adapter_socket *ms = NULL;

	ms = adapter_socket_alloc();
	if (ms == NULL)
		return NULL;

	sock_fd_t sock = socket(AF_INET, SOCK_STREAM, 0);
	adapter_socket_set_nonblocking(sock);

	ms->fd		= sock;
	ms->handle	= NULL;
	ms->type	= ADAPTER_SOCK_TCP_LINK;

	return ms;
}

int32_t adapter_socket_listen(struct adapter_socket *ms, uint16_t max_channels,
						   adapter_socket_handle_t fn)
{
	int ret;

	if (ms == NULL)
		return -ERR_INVALID;

	if (sock_fd_is_invalid(ms->fd))
		return -ERR_INVALID;

	if (ms->type != ADAPTER_SOCK_TCP_LINK)
		return -ERR_INVALID;

	ret = listen(ms->fd, max_channels);
	if (ret < 0) {
		pr_err(ERR_LISTEN, "failed!: %s", strerror(ret));

		return -ERR_LISTEN;
	}

	ms->handle = fn;

	adapter_socket_monitor_add(ms, ADAPTER_SOCK_READ);

	return 0;
}

int32_t adapter_socket_connect(struct adapter_socket *ms, struct sockaddr_in *srv,
						   adapter_socket_handle_t fn)
{
	int ret;

	if ((ms == NULL) || (srv == NULL))
		return -ERR_INVALID;

	if (sock_fd_is_invalid(ms->fd))
		return -ERR_INVALID;

	if (ms->type != ADAPTER_SOCK_TCP_LINK)
		return -ERR_INVALID;

	ret = connect(ms->fd, (struct sockaddr *)srv, sizeof(*srv));
	if (ret < 0 && errno != EINPROGRESS) {
		perror("connect");
		return -ERR_CONNECT;
	}

	ms->handle = fn;
	ms->server = *srv;

	adapter_socket_monitor_add(ms,  ADAPTER_SOCK_READ | ADAPTER_SOCK_WRITE | ADAPTER_SOCK_ET);

	return 0;
}

int32_t adapter_socket_connected(struct adapter_socket *ms)
{
	if (ms == NULL)
		return -ERR_INVALID;

	if (sock_fd_is_invalid(ms->fd))
		return -ERR_INVALID;

	if (ms->type != ADAPTER_SOCK_TCP_LINK)
		return -ERR_INVALID;

	adapter_socket_monitor_mod(ms, ADAPTER_SOCK_READ | ADAPTER_SOCK_ET);

	return 0;
}

int32_t adapter_socket_disconnected(struct adapter_socket *ms)
{
	if (ms == NULL)
		return -ERR_INVALID;

	if (sock_fd_is_invalid(ms->fd))
		return -ERR_INVALID;

	if (ms->type != ADAPTER_SOCK_TCP_DATA)
		return -ERR_INVALID;

	adapter_socket_monitor_mod(ms, 0);

	return 0;
}

struct adapter_socket *adapter_socket_accept(struct adapter_socket *tcp_ms,
					   struct sockaddr *addr,
					   adapter_socket_handle_t fn)
{
	struct adapter_socket *ms = NULL;
	struct sockaddr 	in_addr;
	socklen_t		in_addr_len = sizeof(in_addr);

	sock_fd_t		fd;

	if (tcp_ms == NULL)
		return NULL;

	if (tcp_ms->type != ADAPTER_SOCK_TCP_LINK)
		return NULL;

	ms = adapter_socket_alloc();
	if (ms == NULL)
		return NULL;

	fd = accept(tcp_ms->fd , &in_addr, &in_addr_len);
	if (sock_fd_is_invalid(fd)) {
		adapter_socket_free(ms);
		return NULL;
	}

	adapter_socket_set_nonblocking(fd);

	ms->fd		= fd;
	ms->type	= ADAPTER_SOCK_TCP_DATA;
	ms->handle	= fn;

	adapter_socket_monitor_add(ms, ADAPTER_SOCK_READ);

	if (addr != NULL)
		*addr = in_addr;

	return ms;
}

int adapter_socket_init(void)
{
	return adapter_socket_monitor_init();
}

void adapter_socket_loop(void)
{
	adapter_socket_monitor_loop();
}
