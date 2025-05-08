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

#ifndef MVBS_MCDR_SEQ_TYPE_H
#define MVBS_MCDR_SEQ_TYPE_H


/*
 * mvbs_int8_t_seq: A structure for managing sequences of octet values.
 * Provides the following operations:
 * - mvbs_int8_t_seq_init: Initialize the sequence.
 * - mvbs_int8_t_seq_set_length: Set the length of the sequence.
 * - mvbs_int8_t_seq_get_length: Get the length of the sequence.
 * - mvbs_int8_t_seq_get_max_length: Get the maximum capacity of the sequence.
 * - mvbs_int8_t_seq_get_reference: Get a reference to an element in the sequence.
 * - mvbs_int8_t_seq_set_contiguous_buffer: Set a contiguous buffer as the storage for the sequence.
 */
#define MSEQ_ELEM	int8_t
#define MSEQ_NAME	mvbs_int8_t_seq
#include "mcdr_seq_template.h"

/*
 * mvbs_uint8_t_seq: A structure for managing sequences of octet values.
 * Provides the following operations:
 * - mvbs_uint8_t_seq_init: Initialize the sequence.
 * - mvbs_uint8_t_seq_set_length: Set the length of the sequence.
 * - mvbs_uint8_t_seq_get_length: Get the length of the sequence.
 * - mvbs_uint8_t_seq_get_max_length: Get the maximum capacity of the sequence.
 * - mvbs_uint8_t_seq_get_reference: Get a reference to an element in the sequence.
 * - mvbs_uint8_t_seq_set_contiguous_buffer: Set a contiguous buffer as the storage for the sequence.
 */
#define MSEQ_ELEM	uint8_t
#define MSEQ_NAME	mvbs_uint8_seq
#include "mcdr_seq_template.h"

/*
 * mvbs_boolean_seq: A structure for managing sequences of boolean values.
 * Provides the following operations:
 * - mvbs_boolean_seq_init: Initialize the sequence.
 * - mvbs_boolean_seq_set_length: Set the length of the sequence.
 * - mvbs_boolean_seq_get_length: Get the length of the sequence.
 * - mvbs_boolean_seq_get_max_length: Get the maximum capacity of the sequence.
 * - mvbs_boolean_seq_get_reference: Get a reference to an element in the sequence.
 * - mvbs_boolean_seq_set_contiguous_buffer: Set a contiguous buffer as the storage for the sequence.
 */
 #define MSEQ_ELEM	int8_t
 #define MSEQ_NAME	mvbs_boolean_seq
 #include "mcdr_seq_template.h"


/*
 * mvbs_short_seq: A structure for managing sequences of short integers.
 * Provides the following operations:
 * - mvbs_short_seq_init: Initialize the sequence.
 * - mvbs_short_seq_set_length: Set the length of the sequence.
 * - mvbs_short_seq_get_length: Get the length of the sequence.
 * - mvbs_short_seq_get_max_length: Get the maximum capacity of the sequence.
 * - mvbs_short_seq_get_reference: Get a reference to an element in the sequence.
 * - mvbs_short_seq_set_contiguous_buffer: Set a contiguous buffer as the storage for the sequence.
 */
#define MSEQ_ELEM	int16_t
#define MSEQ_NAME	mvbs_short_seq
#include "mcdr_seq_template.h"


/*
 * mvbs_unsigned_short_seq: A structure for managing sequences of unsigned short integers.
 * Provides the following operations:
 * - mvbs_unsigned_short_seq_init: Initialize the sequence.
 * - mvbs_unsigned_short_seq_set_length: Set the length of the sequence.
 * - mvbs_unsigned_short_seq_get_length: Get the length of the sequence.
 * - mvbs_unsigned_short_seq_get_max_length: Get the maximum capacity of the sequence.
 * - mvbs_unsigned_short_seq_get_reference: Get a reference to an element in the sequence.
 * - mvbs_unsigned_short_seq_set_contiguous_buffer: Set a contiguous buffer as the storage for the sequence.
 */
 #define MSEQ_ELEM	uint16_t
 #define MSEQ_NAME	mvbs_unsigned_short_seq
 #include "mcdr_seq_template.h"


/*
 * mvbs_long_seq: A structure for managing sequences of long integers.
 * Provides the following operations:
 * - mvbs_long_seq_init: Initialize the sequence.
 * - mvbs_long_seq_set_length: Set the length of the sequence.
 * - mvbs_long_seq_get_length: Get the length of the sequence.
 * - mvbs_long_seq_get_max_length: Get the maximum capacity of the sequence.
 * - mvbs_long_seq_get_reference: Get a reference to an element in the sequence.
 * - mvbs_long_seq_set_contiguous_buffer: Set a contiguous buffer as the storage for the sequence.
 */
#define MSEQ_ELEM	int32_t
#define MSEQ_NAME	mvbs_long_seq
#include "mcdr_seq_template.h"


/*
 * mvbs_unsigned_long_seq: A structure for managing sequences of unsigned long integers.
 * Provides the following operations:
 * - mvbs_unsigned_long_seq_init: Initialize the sequence.
 * - mvbs_unsigned_long_seq_set_length: Set the length of the sequence.
 * - mvbs_unsigned_long_seq_get_length: Get the length of the sequence.
 * - mvbs_unsigned_long_seq_get_max_length: Get the maximum capacity of the sequence.
 * - mvbs_unsigned_long_seq_get_reference: Get a reference to an element in the sequence.
 * - mvbs_unsigned_long_seq_set_contiguous_buffer: Set a contiguous buffer as the storage for the sequence.
 */
 #define MSEQ_ELEM	uint32_t
 #define MSEQ_NAME	mvbs_unsigned_long_seq
 #include "mcdr_seq_template.h"


/*
 * mvbs_enum_seq: A structure for managing sequences of enum values.
 * Provides the following operations:
 * - mvbs_enum_seq_init: Initialize the sequence.
 * - mvbs_enum_seq_set_length: Set the length of the sequence.
 * - mvbs_enum_seq_get_length: Get the length of the sequence.
 * - mvbs_enum_seq_get_max_length: Get the maximum capacity of the sequence.
 * - mvbs_enum_seq_get_reference: Get a reference to an element in the sequence.
 * - mvbs_enum_seq_set_contiguous_buffer: Set a contiguous buffer as the storage for the sequence.
 */
#define MSEQ_ELEM	int32_t
#define MSEQ_NAME	mvbs_enum_seq
#include "mcdr_seq_template.h"


/*
 * mvbs_long_long_seq: A structure for managing sequences of long long integers.
 * Provides the following operations:
 * - mvbs_long_long_seq_init: Initialize the sequence.
 * - mvbs_long_long_seq_set_length: Set the length of the sequence.
 * - mvbs_long_long_seq_get_length: Get the length of the sequence.
 * - mvbs_long_long_seq_get_max_length: Get the maximum capacity of the sequence.
 * - mvbs_long_long_seq_get_reference: Get a reference to an element in the sequence.
 * - mvbs_long_long_seq_set_contiguous_buffer: Set a contiguous buffer as the storage for the sequence.
 */
#define MSEQ_ELEM	int64_t
#define MSEQ_NAME	mvbs_long_long_seq
#include "mcdr_seq_template.h"

/*
 * mvbs_unsigned_long_long_seq: A structure for managing sequences of unsigned long long integers.
 * Provides the following operations:
 * - mvbs_unsigned_long_long_seq_init: Initialize the sequence.
 * - mvbs_unsigned_long_long_seq_set_length: Set the length of the sequence.
 * - mvbs_unsigned_long_long_seq_get_length: Get the length of the sequence.
 * - mvbs_unsigned_long_long_seq_get_max_length: Get the maximum capacity of the sequence.
 * - mvbs_unsigned_long_long_seq_get_reference: Get a reference to an element in the sequence.
 * - mvbs_unsigned_long_long_seq_set_contiguous_buffer: Set a contiguous buffer as the storage for the sequence.
 */
 #define MSEQ_ELEM	uint64_t
 #define MSEQ_NAME	mvbs_unsigned_long_long_seq
 #include "mcdr_seq_template.h"


/*
 * mvbs_float_seq: A structure for managing sequences of float values.
 * Provides the following operations:
 * - mvbs_float_seq_init: Initialize the sequence.
 * - mvbs_float_seq_set_length: Set the length of the sequence.
 * - mvbs_float_seq_get_length: Get the length of the sequence.
 * - mvbs_float_seq_get_max_length: Get the maximum capacity of the sequence.
 * - mvbs_float_seq_get_reference: Get a reference to an element in the sequence.
 * - mvbs_float_seq_set_contiguous_buffer: Set a contiguous buffer as the storage for the sequence.
 */
 #define MSEQ_ELEM	float
 #define MSEQ_NAME	mvbs_float_seq
 #include "mcdr_seq_template.h"


/*
 * mvbs_double_seq: A structure for managing sequences of double values.
 * Provides the following operations:
 * - mvbs_double_seq_init: Initialize the sequence.
 * - mvbs_double_seq_set_length: Set the length of the sequence.
 * - mvbs_double_seq_get_length: Get the length of the sequence.
 * - mvbs_double_seq_get_max_length: Get the maximum capacity of the sequence.
 * - mvbs_double_seq_get_reference: Get a reference to an element in the sequence.
 * - mvbs_double_seq_set_contiguous_buffer: Set a contiguous buffer as the storage for the sequence.
 */
#define MSEQ_ELEM	double
#define MSEQ_NAME	mvbs_double_seq
#include "mcdr_seq_template.h"

#endif
