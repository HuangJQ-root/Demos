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
 
#ifndef calculatorRpcParam_H
#define calculatorRpcParam_H

#include <string.h>

#include <mcdr/mcdr.h>

#include <mvbs/utils/string.h>
#include <mvbs/utils/mm.h>

/************************  MVBS_calculator_add  *************************/

typedef struct MVBS_calculator_add_in {
	int32_t a;
	int32_t b;
} MVBS_calculator_add_in;

uint32_t get_size_of_MVBS_calculator_add(MVBS_calculator_add_in *req_type, uint32_t size);

bool MVBS_calculator_add_serialize_input_params(struct mvbs_cdr *cdr,
						MVBS_calculator_add_in *topic);

bool MVBS_calculator_add_deserialize_input_params(struct mvbs_cdr *cdr,
						MVBS_calculator_add_in *topic);

typedef struct MVBS_calculator_add_out {
	int32_t ret;
} MVBS_calculator_add_out;

bool MVBS_calculator_add_serialize_output_params(struct mvbs_cdr *cdr,
						MVBS_calculator_add_out *topic);

bool MVBS_calculator_add_deserialize_output_params(struct mvbs_cdr *cdr,
						MVBS_calculator_add_out *topic);

#endif /* calculatorRpcParam_H */