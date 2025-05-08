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

#ifndef __CALCULATORRPCCLIENT_H
#define __CALCULATORRPCCLIENT_H
#include <rpc/rpc.h>
#include "calculatorRpcParams.h"


int32_t MVBS_calculator_add(struct rpc_client *cli, MVBS_calculator_add_in *req_type, 
							int32_t (*add_cb)(MVBS_calculator_add_out *res_type, int32_t rpc_errno),
							uint32_t timeout);


#endif /* !__CALCULATORRPCCLIENT_H__ */