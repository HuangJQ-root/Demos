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

#ifndef calculatorRpcParam_C
#define calculatorRpcParam_C

#include <string.h>

#include <mvbs/utils/cdefs.h>

#include <mcdr/mcdr.h>

#include <mvbs/utils/string.h>
#include <mvbs/utils/mm.h>

#include "calculatorRpcParams.h"


uint32_t get_size_of_MVBS_calculator_add(MVBS_calculator_add_in *req_type, uint32_t size)
{
	UNUSED_ARG(req_type);

	size += mcdr_get_alignment(size, sizeof(uint32_t)) + sizeof(uint32_t);
	size += sizeof("MVBS_calculator");
	size += mcdr_get_alignment(size, sizeof(uint32_t)) + sizeof(uint32_t);
	size += sizeof("add");

	size += mcdr_get_alignment(size, sizeof(int32_t)) + sizeof(int32_t);
	size += mcdr_get_alignment(size, sizeof(int32_t)) + sizeof(int32_t);

	return size;
}

/************************  MVBS_calculator_add  *************************/

bool MVBS_calculator_add_serialize_input_params(struct mvbs_cdr *cdr,
						MVBS_calculator_add_in *req_type)
{
	/* serialize the input param*/
	if (!mcdr_serialize_int32_t(cdr, req_type->a)) {
		pr_warn("a serialize failed!\n");
		return false;
	}
	if (!mcdr_serialize_int32_t(cdr, req_type->b)) {
		pr_warn("b serialize failed!\n");
		return false;
	}
	return true;
}


bool MVBS_calculator_add_deserialize_input_params(struct mvbs_cdr *cdr,
						MVBS_calculator_add_in *topic)
{
	if (!mcdr_deserialize_int32_t(cdr, &topic->a)) {
		pr_warn("a deserialize failed!\n");
		return false;
	}
	if (!mcdr_deserialize_int32_t(cdr, &topic->b)) {
		pr_warn("b deserialize failed!\n");
		return false;
	}
	return true;
}

bool MVBS_calculator_add_serialize_output_params(struct mvbs_cdr *cdr,
						MVBS_calculator_add_out *topic)
{
	if (!mcdr_serialize_int32_t(cdr, topic->ret)) {
		pr_warn("ret serialize failed!\n");
		return false;
	}
	return true;
}


bool MVBS_calculator_add_deserialize_output_params(struct mvbs_cdr *cdr,
						MVBS_calculator_add_out *topic)
{
	if (!mcdr_deserialize_int32_t(cdr, &topic->ret)) {
		pr_warn("ret deserialize failed!\n");
		return false;
	}
	return true;
}

#endif /* calculatorRpcParam_C */