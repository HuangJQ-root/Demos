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

#include <mvbs/errno.h>
#include <mcdr/mcdr.h>

#include <mvbs/utils/log.h>
#include <mvbs/utils/string.h>
#include <mvbs/utils/mm.h>

#include <rpc/rpc.h>
#include "calculatorRpcClient.h"


static int32_t MVBS_calculator_add_cb(struct mvbs_cdr *stream, void *arg, int32_t error_flag)
{
	/* Interface name and operation name */
	char	interface[sizeof("MVBS_calculator")];
	char	operation[sizeof("add")];
	
	/* Param[OUT] */
	MVBS_calculator_add_out res_type;

	int32_t (*add_cb)(MVBS_calculator_add_out *res_type,  int32_t rpc_errno);

	add_cb = arg;

	/* Case 1: error_flag Handling */
	if (error_flag) {
		int32_t rpc_errno = 0;

		if (mcdr_deserialize_int32_t(stream, &rpc_errno) == false)
			return -ERR_MCDR;

		/* maybe there is a error message in the future */
		return add_cb(&res_type, rpc_errno);
	}

	/* Case 2: Non-error_flag Handling */

	/* step1: deserialize interface name and operation name */
	if (mcdr_deserialize_string(stream, interface, sizeof("MVBS_calculator")) == false)
		return -ERR_MCDR;

	if (mcdr_deserialize_string(stream, operation, sizeof("add")) == false)
		return -ERR_MCDR;
	
	/*  step3: deserialize param[out] */
	if (MVBS_calculator_add_deserialize_output_params(stream, &res_type) == false)
		return -ERR_MCDR;

	/* step3: Call the real callback defined by user. */

	return add_cb(&res_type, 0);

}


int32_t MVBS_calculator_add(struct rpc_client *cli, MVBS_calculator_add_in *req_type, 
			int32_t (*add_cb)(MVBS_calculator_add_out *res_type,  int32_t rpc_errno),
			uint32_t timeout)
{
	char *req_buf		= NULL;
	int32_t ret		= 0;
	uint32_t req_size	= RPC_HEADER_SIZE;
	uint32_t default_sn	= RPC_INVALID_SN;
	struct mvbs_cdr stream;

	if (rpc_client_is_valid(cli) == false || add_cb == NULL)
		return -ERR_INVALID;

	req_size = get_size_of_MVBS_calculator_add(req_type, req_size);

	/* step1: Initialize mcdr */
	req_buf = mvbs_malloc(req_size, MVBS_MM_ALIGN_DEFAULT);
	if (req_buf == NULL)
		return -ERR_NOMEM;

	mcdr_init_buffer(&stream, (uint8_t *)req_buf, req_size);

	/* step2: Install Callback Routine, and get a SN back */
	default_sn = rpc_client_alloc_sn(cli, timeout, MVBS_calculator_add_cb, add_cb, 0, default_sn);
	if (default_sn == RPC_INVALID_SN) {
		mvbs_free(req_buf);
		return -ERR_SNFAIL;
	}

	/* step3: serialize the rpc_header */
	ret = rpc_header_serialize(&stream, RPC_TYPE_NORM_REQ, default_sn, req_size - RPC_HEADER_SIZE);
	if (ret < 0) {
		rpc_client_free_sn(cli, default_sn);
		mvbs_free(req_buf);
		return ret;
	}

	/*  step4: serialize the interface name */
	if (mcdr_serialize_string(&stream, "MVBS_calculator") == false)
		goto MCDR_FAIL;

	/*  step5: serialize the operation name */
	if (mcdr_serialize_string(&stream, "add") == false)
		goto MCDR_FAIL;

	/* step6: serialize the interface/operation name and Param[in] */
	if (MVBS_calculator_add_serialize_input_params(&stream, req_type) == false)
		goto MCDR_FAIL;

	/* step7: Send the request to server */
	ret = rpc_client_send(cli, req_buf, req_size);
	if (ret < 0) {
		rpc_client_free_sn(cli, default_sn);
		mvbs_free(req_buf);
		return ret;
	}

	mvbs_free(req_buf);

	return 0;

MCDR_FAIL:
	rpc_client_free_sn(cli, default_sn);

	mvbs_free(req_buf);

	return -ERR_MCDR;
}


