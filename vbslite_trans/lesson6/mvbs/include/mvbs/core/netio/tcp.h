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

#ifndef MVBS_CORE_NETIO_TCP_H
#define MVBS_CORE_NETIO_TCP_H

#include <mvbs/base_type.h>

/* -------------------------------------------------------------------
 *			PUBLIC INTERFACE (NETIO_TCP)
 * ------------------------------------------------------------------- */

/**
 * Allocate a TCP socket for stream communication.
 *
 * @return a file descriptor for the new socket if success, otherwise an errno
 */
int32_t mvbs_tcp_socket_open(void);


/**
 * Close a TCP socket and release all related resources.
 *
 * @param sockfd socket identifier of the related local socket resource
 * @return zero if success, otherwise an errno
 */
int32_t mvbs_tcp_socket_close(int32_t sockfd);


/**
 * Bind a TCP socket to a local resource.
 *
 * @param sockfd socket identifier of the related local socket resource
 * @param port port number
 * @return zero if success, otherwise an errno
 */
int32_t mvbs_tcp_socket_bind(int32_t sockfd, uint16_t port);


/**
 * Listen for connections on a TCP socket.
 *
 * @param sockfd socket identifier of the related local socket resource
 * @param max_channels max number of new parallel connections established on this socket
 * @return zero if success, otherwise an errno
 */
int32_t mvbs_tcp_socket_listen(int32_t sockfd, uint16_t max_channels);


/**
 * Establish a TCP connection to the configured peer.
 *
 * Note: you can use tcp_inet_aton to get uint32_t srv_addr from a string of IP address.
 *
 * @param sockfd socket identifier of the related local socket resource
 * @param srv_addr pointer to server ip address in network byte order
 * @param port port number
 * @return zero if the connection is established, otherwise an errno
 */
int32_t mvbs_tcp_socket_connect(int32_t sockfd, const uint32_t* srv_addr, uint16_t port);


/**
 * Accept a connection on a TCP socket.
 *
 * @param sockfd socket identifier of the related local socket resource
 * @return a file descriptor for the new child socket if success, otherwise an errno
 */
int32_t mvbs_tcp_socket_accept(int32_t sockfd);


/**
 * Send data on a TCP socket.
 *
 * @param sockfd socket identifier of the related local socket resource
 * @param buf of data to be sent
 * @param len length of data to be sent
 * @return number of bytes sent if success，otherwise an errno
 */
int32_t mvbs_tcp_socket_send(int32_t sockfd, void *buf, uint32_t len);


/**
 * Receive data from a TCP socket.
 *
 * @param sockfd socket identifier of the related local socket resource
 * @param buf buffer to receive data
 * @param len size of buffer
 * @return number of bytes received if success，otherwise an errno
 */
int32_t mvbs_tcp_socket_recv(int32_t sockfd, void *buf, uint32_t len);


/**
 * Peek data from a TCP socket.
 * Note: this interface will copy(but not recv) data of a specific length, and assign the
 * length of all data received now to the out parameter total_recvd_size.
 *
 * @param sockfd socket identifier of the related local socket resource
 * @param buf buffer to peek and copy data
 * @param len length of data that will be peeked
 * @param total_recvd_size length of all data received now
 * @return number of bytes peeked if success，otherwise an errno
 */
int32_t mvbs_tcp_socket_recv_peek(int32_t sockfd, void *buf, uint32_t len, int32_t *total_recvd_size);


/**
 * Convert IPv4 and IPv6 addresses from text to binary form
 *
 * @param src string in source buffer
 * @param dst destination memory area
 * @return zero if success, otherwise an errno
 */
int32_t mvbs_tcp_inet_aton(const char *src, void *dst);

#endif
