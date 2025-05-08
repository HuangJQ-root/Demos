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

#ifndef MVBS_ADAPTER_POSIX_SOCKET
#define MVBS_ADAPTER_POSIX_SOCKET

#include <mvbs/base_type.h>
#include <mvbs/errno.h>

#ifdef TARGET_PRODUCT_MINGW
#include <event2/event.h>

typedef evutil_socket_t		sock_fd_t;

/* FIXME: To Be Removed */
static inline int sock_fd_is_invalid(sock_fd_t fd)
{
	return fd == (sock_fd_t)EVUTIL_INVALID_SOCKET;
}

#define ADAPTER_SOCK_INVALID		EVUTIL_INVALID_SOCKET

#define ADAPTER_SOCK_READ		EV_READ
#define ADAPTER_SOCK_WRITE		EV_WRITE
#define ADAPTER_SOCK_ET			EV_ET	/* edge triger */

#else
#include <sys/epoll.h>
#include <netinet/in.h>

typedef int			sock_fd_t;

#define ADAPTER_SOCK_INVALID	-1


/* FIXME: To Be Removed */
static inline int sock_fd_is_invalid(sock_fd_t fd)
{
	return fd <= 0;
}

#define ADAPTER_SOCK_READ		EPOLLIN
#define ADAPTER_SOCK_WRITE		EPOLLOUT
#define ADAPTER_SOCK_ET			EPOLLET	/* edge triger */

#endif

struct adapter_socket;

typedef void (*adapter_socket_handle_t)(sock_fd_t fd, short events,
					struct adapter_socket *ms);

/* part1: UDP */
struct adapter_socket *adapter_socket_alloc_udp(adapter_socket_handle_t fn);

/* part2: TCP */
struct adapter_socket *adapter_socket_alloc_tcp(void);

int32_t adapter_socket_listen(struct adapter_socket *ms, uint16_t max_channels,
						   adapter_socket_handle_t fn);
int32_t adapter_socket_connect(struct adapter_socket *ms, struct sockaddr_in *srv,
						   adapter_socket_handle_t fn);

int32_t adapter_socket_connected(struct adapter_socket *ms);
int32_t adapter_socket_disconnected(struct adapter_socket *ms);

struct adapter_socket *adapter_socket_accept(struct adapter_socket *tcp_ms,
					   struct sockaddr *addr,
					   adapter_socket_handle_t fn);

void adapter_socket_free(struct adapter_socket *socket);

/* part3: helpers */
bool adapter_socket_is_invalid(struct adapter_socket *ms);
uint8_t adapter_socket_get_index(struct adapter_socket *ms);
sock_fd_t adapter_socket_get_fd(struct adapter_socket *ms);

void adapter_socket_set_port(struct adapter_socket *ms, uint16_t port);

struct adapter_socket *adapter_socket_get(uint8_t index);
static inline sock_fd_t adapter_socket_fd(uint8_t index)
{
	return adapter_socket_get_fd(adapter_socket_get(index));
}

/* part4: Init and loop */
int adapter_socket_monitor_init(void);
void adapter_socket_monitor_loop(void);

#endif
