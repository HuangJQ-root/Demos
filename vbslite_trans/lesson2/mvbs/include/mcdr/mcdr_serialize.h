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

#ifndef MVBS_MCDR_SERIALIZE_H
#define MVBS_MCDR_SERIALIZE_H

#include <mcdr/mcdr_common.h>

/* Part1: Basic Type */
bool mcdr_serialize_bool(mvbs_cdr_t *cdr, bool value);

bool mcdr_serialize_char(mvbs_cdr_t *cdr, char value);
bool mcdr_serialize_unsigned_char(mvbs_cdr_t *cdr, unsigned char value);

bool mcdr_serialize_int8_t(mvbs_cdr_t *cdr, int8_t value);
bool mcdr_serialize_uint8_t(mvbs_cdr_t *cdr, uint8_t value);

bool mcdr_serialize_int16_t(mvbs_cdr_t *cdr, int16_t value);
bool mcdr_serialize_uint16_t(mvbs_cdr_t *cdr, uint16_t value);

bool mcdr_serialize_int32_t(mvbs_cdr_t *cdr, int32_t value);
bool mcdr_serialize_uint32_t(mvbs_cdr_t *cdr, uint32_t value);

bool mcdr_serialize_int64_t(mvbs_cdr_t *cdr, int64_t value);
bool mcdr_serialize_uint64_t(mvbs_cdr_t *cdr, uint64_t value);

bool mcdr_serialize_float(mvbs_cdr_t *cdr, float value);
bool mcdr_serialize_double(mvbs_cdr_t *cdr, double value);

/* Part2: Array Type */
bool mcdr_serialize_array_bool(mvbs_cdr_t *cdr, const bool *array, uint32_t size);

bool mcdr_serialize_array_char(mvbs_cdr_t *cdr, const char *array, uint32_t size);
bool mcdr_serialize_array_unsigned_char(mvbs_cdr_t *cdr, const unsigned char *array, uint32_t size);

bool mcdr_serialize_array_int8_t(mvbs_cdr_t *cdr, const int8_t *array, uint32_t size);
bool mcdr_serialize_array_uint8_t(mvbs_cdr_t *cdr, const uint8_t *array, uint32_t size);

bool mcdr_serialize_array_int16_t(mvbs_cdr_t *cdr, const int16_t *array, uint32_t size);
bool mcdr_serialize_array_uint16_t(mvbs_cdr_t *cdr, const uint16_t *array, uint32_t size);

bool mcdr_serialize_array_int32_t(mvbs_cdr_t *cdr, const int32_t *array, uint32_t size);
bool mcdr_serialize_array_uint32_t(mvbs_cdr_t *cdr, const uint32_t *array, uint32_t size);

bool mcdr_serialize_array_int64_t(mvbs_cdr_t *cdr, const int64_t *array, uint32_t size);
bool mcdr_serialize_array_uint64_t(mvbs_cdr_t *cdr, const uint64_t *array, uint32_t size);

bool mcdr_serialize_array_float(mvbs_cdr_t *cdr, const float *array, uint32_t size);
bool mcdr_serialize_array_double(mvbs_cdr_t *cdr, const double *array, uint32_t size);

/* Part3: String Type */
bool mcdr_serialize_string(mvbs_cdr_t *cdr, const char *str);

/* Part4: Sequence Type */
bool mcdr_serialize_sequence_bool(mvbs_cdr_t *cdr, const bool *array, uint32_t size);

bool mcdr_serialize_sequence_char(mvbs_cdr_t *cdr, const char *array, uint32_t size);

bool mcdr_serialize_sequence_int8_t(mvbs_cdr_t *cdr, const int8_t *array, uint32_t size);
bool mcdr_serialize_sequence_uint8_t(mvbs_cdr_t *cdr, const uint8_t *array, uint32_t size);

bool mcdr_serialize_sequence_int16_t(mvbs_cdr_t *cdr, const int16_t *array, uint32_t size);
bool mcdr_serialize_sequence_uint16_t(mvbs_cdr_t *cdr, const uint16_t *array, uint32_t size);

bool mcdr_serialize_sequence_int32_t(mvbs_cdr_t *cdr, const int32_t *array, uint32_t size);
bool mcdr_serialize_sequence_uint32_t(mvbs_cdr_t *cdr, const uint32_t *array, uint32_t size);

bool mcdr_serialize_sequence_int64_t(mvbs_cdr_t *cdr, const int64_t *array, uint32_t size);
bool mcdr_serialize_sequence_uint64_t(mvbs_cdr_t *cdr, const uint64_t *array, uint32_t size);

bool mcdr_serialize_sequence_float(mvbs_cdr_t *cdr, const float *array, uint32_t size);
bool mcdr_serialize_sequence_double(mvbs_cdr_t *cdr, const double *array, uint32_t size);
#endif
