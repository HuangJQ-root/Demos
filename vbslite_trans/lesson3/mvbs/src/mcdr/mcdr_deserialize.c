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

#include <mvbs/sections/start_sec_code.h>
#include <mvbs/sections/start_sec_bss.h>
#include <mvbs/sections/start_sec_const.h>
#include <mvbs/sections/start_sec_data.h>

#include <string.h>
#include <mcdr/mcdr.h>
#include <mvbs/utils/cdefs.h>

#include <mcdr/mcdr.h>


/* Part1: Basic Interfaces */
static bool mcdr_deserialize_byte_1(mvbs_cdr_t *buffer, uint8_t *byte)
{
	if (buffer == NULL) {
		return false;
	}

	if (mcdr_check_buffer(buffer, sizeof(*byte))) {
		if (byte != NULL) {
			*byte = *buffer->cur_pos;
		}

		buffer->cur_pos += sizeof(*byte);
		buffer->last_data_size = sizeof(*byte);
	}

	return !buffer->error;
}

static bool mcdr_deserialize_byte_2(mvbs_cdr_t *buffer, bool is_little_endian,
				    uint16_t *bytes)
{
	if (buffer == NULL) {
		return false;
	}

	uint32_t alignment = mcdr_buffer_alignment(buffer, sizeof(*bytes));

	if (mcdr_check_buffer(buffer, alignment + sizeof(*bytes))) {
		buffer->cur_pos += alignment;

		if(bytes != NULL) {
			(void)memcpy(bytes, static_cast_ptr(uint16_t, buffer->cur_pos), sizeof(*bytes));

			if (is_little_endian != LOCAL_IS_LITTLE_ENDIAN) {
				*bytes = mcdr_reverse_2bytes(*bytes);
			}
		}

		buffer->cur_pos += sizeof(*bytes);
		buffer->last_data_size = sizeof(*bytes);
	}

	return !buffer->error;
}

static bool mcdr_deserialize_byte_4(mvbs_cdr_t *buffer, bool is_little_endian,
				    uint32_t *bytes)
{
	if (buffer == NULL) {
		return false;
	}

	uint32_t alignment = mcdr_buffer_alignment(buffer, sizeof(*bytes));

	if (mcdr_check_buffer(buffer, alignment + sizeof(*bytes))) {
		buffer->cur_pos += alignment;

		if (bytes != NULL) {
			(void)memcpy(bytes, static_cast_ptr(uint32_t, buffer->cur_pos), sizeof(*bytes));

			if (is_little_endian != LOCAL_IS_LITTLE_ENDIAN) {
				*bytes = mcdr_reverse_4bytes(*bytes);
			}
		}

		buffer->cur_pos += sizeof(*bytes);
		buffer->last_data_size = sizeof(*bytes);
	}

	return !buffer->error;
}

static bool mcdr_deserialize_byte_8(mvbs_cdr_t *buffer, bool is_little_endian,
				    uint64_t *bytes)
{
	if (buffer == NULL) {
		return false;
	}

	uint32_t alignment = mcdr_buffer_alignment(buffer, sizeof(*bytes));

	if (mcdr_check_buffer(buffer, alignment + sizeof(*bytes))) {
		buffer->cur_pos += alignment;

		if (bytes != NULL) {
			(void)memcpy(bytes, static_cast_ptr(uint64_t, buffer->cur_pos), sizeof(*bytes));

			if (is_little_endian != LOCAL_IS_LITTLE_ENDIAN) {
				*bytes = mcdr_reverse_8bytes(*bytes);
			}
		}

		buffer->cur_pos += sizeof(*bytes);
		buffer->last_data_size = sizeof(*bytes);
	}

	return !buffer->error;
}

/* Part2: Basic Type */
bool mcdr_deserialize_bool(mvbs_cdr_t *cdr, bool *value)
{
	return mcdr_deserialize_byte_1(cdr, (uint8_t *)value);
}

bool mcdr_deserialize_char(mvbs_cdr_t *cdr, char *value)
{
	return mcdr_deserialize_byte_1(cdr, (uint8_t *)value);
}

bool mcdr_deserialize_unsigned_char(mvbs_cdr_t *cdr, unsigned char *value)
{
	return mcdr_deserialize_byte_1(cdr, (uint8_t *)value);
}

bool mcdr_deserialize_uint8_t(mvbs_cdr_t *cdr, uint8_t *value)
{
	return mcdr_deserialize_byte_1(cdr, value);
}

bool mcdr_deserialize_uint16_t(mvbs_cdr_t *cdr, uint16_t *value)
{
	return mcdr_deserialize_byte_2(cdr, mcdr_buffer_is_little_endian(cdr), value);
}

bool mcdr_deserialize_uint32_t(mvbs_cdr_t *cdr, uint32_t *value)
{
	return mcdr_deserialize_byte_4(cdr, mcdr_buffer_is_little_endian(cdr), value);
}

bool mcdr_deserialize_uint64_t(mvbs_cdr_t *cdr, uint64_t *value)
{
	return mcdr_deserialize_byte_8(cdr, mcdr_buffer_is_little_endian(cdr), value);
}

bool mcdr_deserialize_int8_t(mvbs_cdr_t *cdr, int8_t *value)
{
	return mcdr_deserialize_byte_1(cdr, (uint8_t *)value);
}

bool mcdr_deserialize_int16_t(mvbs_cdr_t *cdr, int16_t *value)
{
	return mcdr_deserialize_byte_2(cdr, mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(uint16_t, value));
}

bool mcdr_deserialize_int32_t(mvbs_cdr_t *cdr, int32_t *value)
{
	return mcdr_deserialize_byte_4(cdr, mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(uint32_t, value));
}

bool mcdr_deserialize_int64_t(mvbs_cdr_t *cdr, int64_t *value)
{
	return mcdr_deserialize_byte_8(cdr, mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(uint64_t, value));
}

bool mcdr_deserialize_float(mvbs_cdr_t *cdr, float *value)
{
	return mcdr_deserialize_byte_4(cdr, mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(uint32_t, value));
}

bool mcdr_deserialize_double(mvbs_cdr_t *cdr, double *value)
{
	return mcdr_deserialize_byte_8(cdr, mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(uint64_t, value));
}

/* Part3: Array Type */
bool mcdr_deserialize_array_byte_1(mvbs_cdr_t *buffer, uint8_t *array,
				   uint32_t size)
{
	if (buffer == NULL) {
		return false;
	}

	if (mcdr_check_buffer(buffer, size) && (buffer->cur_pos != NULL)) {
		if (array != NULL) {
			(void)memcpy(array, (uint8_t *)buffer->cur_pos, size);
		}

		buffer->cur_pos += size;
		buffer->last_data_size = sizeof(uint8_t);
	}

	return !buffer->error;
}

bool mcdr_deserialize_array_byte_2(mvbs_cdr_t *buffer, bool is_little_endian,
				   uint16_t *array, uint32_t size)
{
	if (buffer == NULL) {
		return false;
	}

	uint32_t array_size = size * sizeof(uint16_t);
	uint32_t alignment = mcdr_buffer_alignment(buffer, sizeof(uint16_t));

	if (mcdr_check_buffer(buffer, alignment + array_size)) {
		buffer->cur_pos += alignment;

		if (is_little_endian == LOCAL_IS_LITTLE_ENDIAN) {
			if(array != NULL) {
				(void)memcpy(array, static_cast_ptr(uint64_t, buffer->cur_pos), array_size);
			}

			buffer->cur_pos += array_size;
			buffer->last_data_size = sizeof(uint16_t);
		} else {
			for (uint32_t i = 0; i < size; i++) {
				(void)mcdr_deserialize_byte_2(buffer, is_little_endian,
							array + i);
			}
		}
	}

	return !buffer->error;
}

bool mcdr_deserialize_array_byte_4(mvbs_cdr_t *buffer, bool is_little_endian,
				   uint32_t *array, uint32_t size)
{
	if (buffer == NULL) {
		return false;
	}

	uint32_t array_size = size * sizeof(uint32_t);
	uint32_t alignment = mcdr_buffer_alignment(buffer, sizeof(uint32_t));

	if (mcdr_check_buffer(buffer, alignment + array_size)) {
		buffer->cur_pos += alignment;

		if (is_little_endian == LOCAL_IS_LITTLE_ENDIAN) {
			if(array != NULL) {
				(void)memcpy(array, static_cast_ptr(uint32_t, buffer->cur_pos), array_size);
			}

			buffer->cur_pos += array_size;
			buffer->last_data_size = sizeof(uint32_t);
		} else {
			for (uint32_t i = 0; i < size; i++) {
				(void)mcdr_deserialize_byte_4(buffer,
						is_little_endian, array + i);
			}
		}
	}

	return !buffer->error;
}

bool mcdr_deserialize_array_byte_8(mvbs_cdr_t *buffer, bool is_little_endian,
				   uint64_t *array, uint32_t size)
{
	if (buffer == NULL) {
		return false;
	}

	uint32_t array_size = size * sizeof(uint64_t);
	uint32_t alignment = mcdr_buffer_alignment(buffer, sizeof(uint64_t));

	if (mcdr_check_buffer(buffer, alignment + array_size)) {
		buffer->cur_pos += alignment;

		if (is_little_endian == LOCAL_IS_LITTLE_ENDIAN) {
			if(array != NULL) {
				(void)memcpy(array, static_cast_ptr(uint64_t, buffer->cur_pos), array_size);
			}

			buffer->cur_pos += array_size;
			buffer->last_data_size = sizeof(uint64_t);
		} else {
			for (uint32_t i = 0; i < size; i++) {
				(void)mcdr_deserialize_byte_8(buffer,
						is_little_endian, array + i);
			}
		}
	}

	return !buffer->error;
}

bool mcdr_deserialize_array_bool(mvbs_cdr_t *cdr, bool *array,
				 uint32_t size)
{
	return mcdr_deserialize_array_byte_1(cdr, (uint8_t *)array, size);
}

bool mcdr_deserialize_array_char(mvbs_cdr_t *cdr, char *array,
				 uint32_t size)
{
	return mcdr_deserialize_array_byte_1(cdr, (uint8_t *)array, size);
}

bool mcdr_deserialize_array_unsigned_char(mvbs_cdr_t *cdr, unsigned char *array,
				 uint32_t size)
{
	return mcdr_deserialize_array_byte_1(cdr, (uint8_t *)array, size);
}

bool mcdr_deserialize_array_int8_t(mvbs_cdr_t *cdr, int8_t *array,
				   uint32_t size)
{
	return mcdr_deserialize_array_byte_1(cdr, (uint8_t *)array, size);
}

bool mcdr_deserialize_array_uint8_t(mvbs_cdr_t *cdr, uint8_t *array,
				    uint32_t size)
{
	return mcdr_deserialize_array_byte_1(cdr, array, size);
}

bool mcdr_deserialize_array_int16_t(mvbs_cdr_t *cdr, int16_t *array,
				    uint32_t size)
{
	return mcdr_deserialize_array_byte_2(cdr, mcdr_buffer_is_little_endian(cdr),
					    static_cast_ptr(uint16_t, array), size);
}

bool mcdr_deserialize_array_uint16_t(mvbs_cdr_t *cdr, uint16_t *array,
				     uint32_t size)
{
	return mcdr_deserialize_array_byte_2(cdr, mcdr_buffer_is_little_endian(cdr), array, size);
}

bool mcdr_deserialize_array_int32_t(mvbs_cdr_t *cdr, int32_t *array,
				    uint32_t size)
{
	return mcdr_deserialize_array_byte_4(cdr, mcdr_buffer_is_little_endian(cdr),
					    static_cast_ptr(uint32_t, array), size);
}

bool mcdr_deserialize_array_uint32_t(mvbs_cdr_t *cdr, uint32_t *array,
				     uint32_t size)
{
	return mcdr_deserialize_array_byte_4(cdr, mcdr_buffer_is_little_endian(cdr), array, size);
}

bool mcdr_deserialize_array_int64_t(mvbs_cdr_t *cdr, int64_t *array,
				    uint32_t size)
{
	return mcdr_deserialize_array_byte_8(cdr, mcdr_buffer_is_little_endian(cdr),
					     static_cast_ptr(uint64_t, array), size);
}

bool mcdr_deserialize_array_uint64_t(mvbs_cdr_t *cdr, uint64_t *array,
				     uint32_t size)
{
	return mcdr_deserialize_array_byte_8(cdr, mcdr_buffer_is_little_endian(cdr), array, size);
}

bool mcdr_deserialize_array_float(mvbs_cdr_t *cdr, float *array,
				  uint32_t size)
{
	return mcdr_deserialize_array_byte_4(cdr, mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(uint32_t, array), size);
}

bool mcdr_deserialize_array_double(mvbs_cdr_t *cdr, double *array,
				   uint32_t size)
{
	void *tmp_array = (void *)array;

	return mcdr_deserialize_array_byte_8(cdr, mcdr_buffer_is_little_endian(cdr),
					     (uint64_t *)tmp_array, size);
}

/* Part4: String Type */
bool mcdr_deserialize_string(mvbs_cdr_t *cdr, char *str,
			     uint32_t capacity)
{
	if ((cdr == NULL) || (str == NULL)) {
		return false;
	}

	uint32_t length = 0;

	return mcdr_deserialize_sequence_char(cdr, str, capacity, &length);
}

/* Part5: Sequence Type */
static inline void mcdr_deserialize_sequence_header(mvbs_cdr_t *cdr,
						    uint32_t capacity,
						    uint32_t *size)
{
	(void)mcdr_deserialize_uint32_t(cdr, size);

	if (*size > capacity) {
		cdr->error = true;
	}
}

bool mcdr_deserialize_sequence_byte_1(mvbs_cdr_t *cdr,
				      uint8_t *array,
				      uint32_t array_buffer,
				      uint32_t *size)
{
	if ((cdr == NULL) || (array == NULL) || (size == NULL)) {
		return false;
	}

	mcdr_deserialize_sequence_header(cdr, array_buffer, size);

	return mcdr_deserialize_array_byte_1(cdr, array, *size);
}

bool mcdr_deserialize_sequence_byte_2(mvbs_cdr_t *cdr, bool is_little_endian,
				      uint16_t *array,
				      uint32_t array_buffer,
				      uint32_t *size)
{
	if ((cdr == NULL) || (array == NULL) || (size == NULL)) {
		return false;
	}

	mcdr_deserialize_sequence_header(cdr, array_buffer, size);

	return mcdr_deserialize_array_byte_2(cdr, is_little_endian, array, *size);
}

bool mcdr_deserialize_sequence_byte_4(mvbs_cdr_t *cdr, bool is_little_endian,
				      uint32_t *array,
				      uint32_t array_buffer,
				      uint32_t *size)
{
	if ((cdr == NULL) || (array == NULL) || (size == NULL)) {
		return false;
	}

	mcdr_deserialize_sequence_header(cdr, array_buffer, size);

	return mcdr_deserialize_array_byte_4(cdr, is_little_endian, array, *size);
}

bool mcdr_deserialize_sequence_byte_8(mvbs_cdr_t *cdr, bool is_little_endian,
				      uint64_t *array,
				      uint32_t array_buffer,
				      uint32_t *size)
{
	if ((cdr == NULL) || (array == NULL) || (size == NULL)) {
		return false;
	}

	mcdr_deserialize_sequence_header(cdr, array_buffer, size);

	return mcdr_deserialize_array_byte_8(cdr, is_little_endian, array, *size);
}


bool mcdr_deserialize_sequence_char(mvbs_cdr_t *cdr, char *array,
				    uint32_t array_buffer,
				    uint32_t *size)
{
	return mcdr_deserialize_sequence_byte_1(cdr, (uint8_t *)array,
					 	array_buffer, size);
}

bool mcdr_deserialize_sequence_bool(mvbs_cdr_t *cdr, bool *array,
				    uint32_t array_buffer,
				    uint32_t *size)
{
	return mcdr_deserialize_sequence_byte_1(cdr, (uint8_t *)array,
						array_buffer, size);
}

bool mcdr_deserialize_sequence_uint8_t(mvbs_cdr_t *cdr, uint8_t *array,
				       uint32_t array_buffer,
				       uint32_t *size)
{
	return mcdr_deserialize_sequence_byte_1(cdr, (uint8_t *)array,
						array_buffer, size);
}

bool mcdr_deserialize_sequence_uint16_t(mvbs_cdr_t *cdr, uint16_t *array,
					uint32_t array_buffer,
					uint32_t *size)
{
	return mcdr_deserialize_sequence_byte_2(cdr, mcdr_buffer_is_little_endian(cdr),
					(uint16_t *)array, array_buffer, size);
}

bool mcdr_deserialize_sequence_uint32_t(mvbs_cdr_t *cdr, uint32_t *array,
					uint32_t array_buffer,
					uint32_t *size)
{
	return mcdr_deserialize_sequence_byte_4(cdr, mcdr_buffer_is_little_endian(cdr),
					(uint32_t *)array, array_buffer, size);
}

bool mcdr_deserialize_sequence_uint64_t(mvbs_cdr_t *cdr, uint64_t *array,
					uint32_t array_buffer,
					uint32_t *size)
{
	return mcdr_deserialize_sequence_byte_8(cdr, mcdr_buffer_is_little_endian(cdr),
					(uint64_t *)array, array_buffer, size);
}

bool mcdr_deserialize_sequence_int8_t(mvbs_cdr_t *cdr, int8_t *array,
				      uint32_t array_buffer,
				      uint32_t *size)
{
	return mcdr_deserialize_sequence_byte_1(cdr, (uint8_t *)array,
						array_buffer, size);
}

bool mcdr_deserialize_sequence_int16_t(mvbs_cdr_t *cdr, int16_t *array,
				       uint32_t array_buffer,
				       uint32_t *size)
{
	return mcdr_deserialize_sequence_byte_2(cdr, mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(uint16_t, array), array_buffer, size);
}

bool mcdr_deserialize_sequence_int32_t(mvbs_cdr_t *cdr, int32_t *array,
				       uint32_t array_buffer,
				       uint32_t *size)
{
	return mcdr_deserialize_sequence_byte_4(cdr, mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(uint32_t, array), array_buffer, size);
}

bool mcdr_deserialize_sequence_int64_t(mvbs_cdr_t *cdr, int64_t *array,
				       uint32_t array_buffer,
				       uint32_t *size)
{
	return mcdr_deserialize_sequence_byte_8(cdr, mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(uint64_t, array), array_buffer, size);
}

bool mcdr_deserialize_sequence_float(mvbs_cdr_t *cdr, float *array,
				     uint32_t array_buffer,
				     uint32_t *size)
{
	return mcdr_deserialize_sequence_byte_4(cdr, mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(uint32_t, array), array_buffer, size);
}

bool mcdr_deserialize_sequence_double(mvbs_cdr_t *cdr, double *array,
				      uint32_t array_buffer,
				      uint32_t *size)
{
	return mcdr_deserialize_sequence_byte_8(cdr, mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(uint64_t, array), array_buffer, size);
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
