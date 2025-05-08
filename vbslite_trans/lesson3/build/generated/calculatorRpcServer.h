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

/*
 * This file was generated form calculator.idl by the mvbs-idl-gen tool.
 */

#ifndef __CALCULATORRPCSERVER_H
#define __CALCULATORRPCSERVER_H
#include <rpc/rpc.h>
#include "calculatorRpcParams.h"

/* return value for user in server callback function */
#define		RPC_SVC_FAIL	0 // server doesn't reply and cb won't be called next time.
#define		RPC_SVC_STOP	1 // server will reply and cb won't be called next time.
#define		RPC_SVC_CONT	2 // server will reply and cb will be called next time.
#define		RPC_SVC_ABORT	3 // server doesn't reply and cb will be called next time.

int32_t MVBS_calculator_add_svc(MVBS_calculator_add_in *req_type, MVBS_calculator_add_out *res_type);

int32_t calculator_rpc_server_svc_cb(struct rpc_connection *conn,
			struct mvbs_cdr *cdr, struct rpc_header *header);

#endif /* !__CALCULATORRPCSERVER_H__ */