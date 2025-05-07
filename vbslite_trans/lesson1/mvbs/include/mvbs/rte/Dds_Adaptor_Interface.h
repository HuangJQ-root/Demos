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

#ifndef MVBS_RTE_DDS_ADAPTOR_INTERFACE_H
#define MVBS_RTE_DDS_ADAPTOR_INTERFACE_H

typedef signed int		sint32;
typedef unsigned char		dds_socket_id;
typedef unsigned char		uint8;
typedef unsigned short int	uint16;
typedef unsigned long int	uint64;

typedef struct participant *	Rte_Dds_Participant;

typedef struct {
	uint16			domain;
} dds_socket_addr;

#ifndef TRUE
#define TRUE			1u
#endif

#ifndef FALSE
#define FALSE			0u
#endif

/* Definition for Error Code */
#define	DDS_ERRNO_BASE		(sint32)(-9000)
#define	DDS_ERR_INVALID		(sint32)(-9001)		/* Invalid paramters */
#define	DDS_ERR_NOMEM		(sint32)(-9002)		/* Fail to alloc memory */
#define	DDS_ERR_NOENTITY	(sint32)(-9003)		/* Fail to find entity */
#define	DDS_ERR_SEND_ERR	(sint32)(-9004)		/* Fail to send cachechange */

/* Definition for Event operation */
typedef uint64					EventMaskType;

#define DDS_SetEvent(TaskID, Mask)		SetEvent(TaskID, Mask)
#define DDS_GetEvent(TaskID, Mask)		GetEvent(TaskID, Mask)
#define DDS_WaitEvent(Mask)			WaitEvent(Mask)
#define DDS_ClearEvent(Mask)			ClearEvent(Mask)


sint32 DDS_Init_Adaptor(void);

sint32 DDS_Pub_Adaptor(const char* topic_name, void* sample, uint64 sn,
							     uint64 timestamp);

void DDS_Recv_Adaptor(const char* topic_name, const void* payload, uint16 size);


void DDS_TCPIP_RxIndication_Adaptor(dds_socket_id socket,
				    dds_socket_addr *remote_addr_ptr,
				    const uint8* buf_ptr, uint16 length);
void DDS_Mainloop_Adaptor(void);

#endif /* !MVBS_RTE_DDS_ADAPTOR_INTERFACE_H */
