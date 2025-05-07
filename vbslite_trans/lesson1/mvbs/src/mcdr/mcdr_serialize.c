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

/* Part1: Basic Interfaces */
 bool mcdr_serialize_byte_1(mvbs_cdr_t *buffer, const uint8_t *byte)
 {
	 if (buffer == NULL) {
		 return false;
	 }

	 if (mcdr_check_buffer(buffer, sizeof(*byte))) {
		 if (byte != NULL) {
			 *buffer->cur_pos = *byte;
		 }

		 /* mcdr_check_buffer() guarantees that it will
			 * not exceed buffer->final
			 */
		 buffer->cur_pos += sizeof(*byte);
		 buffer->last_data_size = sizeof(*byte);
	 }

	 return !buffer->error;
 }

 bool mcdr_serialize_byte_2(mvbs_cdr_t *buffer, bool is_little_endian,
			    const uint16_t *bytes)
 {
	 if (buffer == NULL) {
		 return false;
	 }

	 uint32_t alignment = mcdr_buffer_alignment(buffer, sizeof(*bytes));

	 if (mcdr_check_buffer(buffer, alignment + sizeof(*bytes))) {
		 buffer->cur_pos += alignment;

		 if (bytes != NULL) {
			 uint16_t reverse_value = *bytes;
			 if (is_little_endian != LOCAL_IS_LITTLE_ENDIAN) {
				 reverse_value = mcdr_reverse_2bytes(reverse_value);
			 }

			 (void)memcpy(buffer->cur_pos, &reverse_value, sizeof(reverse_value));
		 }

		 buffer->cur_pos	+= sizeof(*bytes);
		 buffer->last_data_size  = sizeof(*bytes);
	 }

	 return !buffer->error;
 }

 bool mcdr_serialize_byte_4(mvbs_cdr_t *buffer, bool is_little_endian,
			    const uint32_t *bytes)
 {
	 if (buffer == NULL) {
		 return false;
	 }

	 uint32_t alignment = mcdr_buffer_alignment(buffer, sizeof(*bytes));

	 if (mcdr_check_buffer(buffer, alignment + sizeof(*bytes))) {
		 buffer->cur_pos += alignment;

		 if (bytes != NULL) {
			 uint32_t reverse_value = *bytes;
			 if (is_little_endian != LOCAL_IS_LITTLE_ENDIAN) {
				 reverse_value = mcdr_reverse_4bytes(reverse_value);
			 }

			 (void)memcpy(buffer->cur_pos, &reverse_value, sizeof(reverse_value));
		 }

		 buffer->cur_pos	+= sizeof(*bytes);
		 buffer->last_data_size  = sizeof(*bytes);
	 }

	 return !buffer->error;

 }

 bool mcdr_serialize_byte_8(mvbs_cdr_t *buffer, bool is_little_endian,
			    const uint64_t *bytes)
 {
	 if (buffer == NULL) {
		 return false;
	 }

	 uint32_t alignment = mcdr_buffer_alignment(buffer, sizeof(*bytes));

	 if (mcdr_check_buffer(buffer, alignment + sizeof(*bytes))) {
		 buffer->cur_pos += alignment;

		 if (bytes != NULL) {
			 uint64_t reverse_value = *bytes;
			 if (is_little_endian != LOCAL_IS_LITTLE_ENDIAN) {
				 reverse_value = mcdr_reverse_8bytes(reverse_value);
			 }

			 (void)memcpy(buffer->cur_pos, &reverse_value, sizeof(reverse_value));
		 }

		 buffer->cur_pos	+= sizeof(*bytes);
		 buffer->last_data_size  = sizeof(*bytes);
	 }

	 return !buffer->error;
 }

/* Part2: Basic Type */
bool mcdr_serialize_bool(mvbs_cdr_t *cdr, bool value)
{
	return mcdr_serialize_byte_1(cdr, (const uint8_t *)&value);
}

bool mcdr_serialize_char(mvbs_cdr_t *cdr, char value)
{
	return mcdr_serialize_byte_1(cdr, (const uint8_t *)&value);
}

bool mcdr_serialize_unsigned_char(mvbs_cdr_t *cdr, unsigned char value)
{
	return mcdr_serialize_byte_1(cdr, (const uint8_t *)&value);
}

bool mcdr_serialize_int8_t(mvbs_cdr_t *cdr, int8_t value)
{
	return mcdr_serialize_byte_1(cdr, (const uint8_t *)&value);
}

bool mcdr_serialize_uint8_t(mvbs_cdr_t *cdr, const uint8_t value)
{
	return mcdr_serialize_byte_1(cdr, &value);
}

bool mcdr_serialize_int16_t(mvbs_cdr_t *cdr, int16_t value)
{
	return mcdr_serialize_byte_2(cdr, mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(const uint16_t, &value));
}

bool mcdr_serialize_uint16_t(mvbs_cdr_t *cdr, uint16_t value)
{
	return mcdr_serialize_byte_2(cdr, mcdr_buffer_is_little_endian(cdr), &value);
}

bool mcdr_serialize_int32_t(mvbs_cdr_t *cdr, int32_t value)
{
	return mcdr_serialize_byte_4(cdr, mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(const uint32_t, &value));
}

bool mcdr_serialize_uint32_t(mvbs_cdr_t *cdr, uint32_t value)
{
	return mcdr_serialize_byte_4(cdr, mcdr_buffer_is_little_endian(cdr), &value);
}

bool mcdr_serialize_int64_t(mvbs_cdr_t *cdr, int64_t value)
{
	return mcdr_serialize_byte_8(cdr, mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(const uint64_t, &value));
}

bool mcdr_serialize_uint64_t(mvbs_cdr_t *cdr, uint64_t value)
{
	return mcdr_serialize_byte_8(cdr, mcdr_buffer_is_little_endian(cdr), &value);
}

bool mcdr_serialize_float(mvbs_cdr_t *cdr, float value)
{
	return mcdr_serialize_byte_4(cdr, mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(const uint32_t, &value));
}

bool mcdr_serialize_double(mvbs_cdr_t *cdr, double value)
{
	return mcdr_serialize_byte_8(cdr, mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(const uint64_t, &value));
}

/* Part3: Array Type */
bool mcdr_serialize_array_byte_1(mvbs_cdr_t *buffer, const uint8_t *array,
				 uint32_t size)
{
	if (buffer == NULL) {
		return false;
	}

	if (mcdr_check_buffer(buffer, size)) {
		if (array != NULL) {
			(void)memcpy(buffer->cur_pos, (const uint8_t *)array,
					size);
		}

		buffer->cur_pos += size;
		buffer->last_data_size = sizeof(uint8_t);
	}

	return !buffer->error;
}

bool mcdr_serialize_array_byte_2(mvbs_cdr_t *buffer, bool is_little_endian,
				 const uint16_t *array, uint32_t size)
{
	if (buffer == NULL) {
		return false;
	}

	uint32_t array_size = size * sizeof(uint16_t);
	uint32_t alignment = mcdr_buffer_alignment(buffer, sizeof(uint16_t));

	if (mcdr_check_buffer(buffer, alignment + array_size)) {
		buffer->cur_pos += alignment;

		if (is_little_endian == LOCAL_IS_LITTLE_ENDIAN) {
			if (array != NULL) {
				(void)memcpy(buffer->cur_pos, (const uint8_t *)array, array_size);
			}

			buffer->cur_pos += array_size;
			buffer->last_data_size = sizeof(uint16_t);
		} else {
			for (uint32_t i = 0; i < size; i++) {
				(void)mcdr_serialize_byte_2(buffer,
						is_little_endian, array + i);
			}
		}
	}

	return !buffer->error;
}

bool mcdr_serialize_array_byte_4(mvbs_cdr_t *buffer, bool is_little_endian,
				 const uint32_t *array, uint32_t size)
{
	if (buffer == NULL) {
		return false;
	}

	uint32_t array_size = size * sizeof(uint32_t);
	uint32_t alignment = mcdr_buffer_alignment(buffer, sizeof(uint32_t));

	if (mcdr_check_buffer(buffer, alignment + array_size)) {
		buffer->cur_pos += alignment;

		if (is_little_endian == LOCAL_IS_LITTLE_ENDIAN) {
			if (array != NULL) {
				(void)memcpy(buffer->cur_pos, (const uint8_t *)array, array_size);
			}

			buffer->cur_pos += array_size;
			buffer->last_data_size = sizeof(uint32_t);
		} else {
			for (uint32_t i = 0; i < size; i++) {
				(void)mcdr_serialize_byte_4(buffer,
						is_little_endian, array + i);
			}
		}
	}

	return !buffer->error;
}

bool mcdr_serialize_array_byte_8(mvbs_cdr_t *cdr, bool is_little_endian,
				 const uint64_t *array, uint32_t size)
{
	if (cdr == NULL) {
		return false;
	}

	uint32_t array_size = size * sizeof(uint64_t);
	uint32_t alignment = mcdr_buffer_alignment(cdr, sizeof(uint64_t));

	if (mcdr_check_buffer(cdr, alignment + array_size)) {
		cdr->cur_pos += alignment;

		if (is_little_endian == LOCAL_IS_LITTLE_ENDIAN) {
			if (array != NULL) {
				(void)memcpy(cdr->cur_pos, (const uint8_t *)array, array_size);
			}

			cdr->cur_pos += array_size;
			cdr->last_data_size = sizeof(uint64_t);
		} else {
			for (uint32_t i = 0; i < size; i++) {
				(void)mcdr_serialize_byte_8(cdr,
						is_little_endian, array + i);
			}
		}
	}

	return !cdr->error;
}

bool mcdr_serialize_array_bool(mvbs_cdr_t *cdr, const bool *array,
			       uint32_t size)
{
	return mcdr_serialize_array_byte_1(cdr, (const uint8_t *)array, size);
}


bool mcdr_serialize_array_char(mvbs_cdr_t *cdr, const char *array,
			       uint32_t size)
{
	return mcdr_serialize_array_byte_1(cdr, (const uint8_t *)array, size);
}

bool mcdr_serialize_array_unsigned_char(mvbs_cdr_t *cdr, const unsigned char *array,
			       uint32_t size)
{
	return mcdr_serialize_array_byte_1(cdr, (const uint8_t *)array, size);
}

bool mcdr_serialize_array_int8_t(mvbs_cdr_t *cdr, const int8_t *array,
				 uint32_t size)
{
	return mcdr_serialize_array_byte_1(cdr, (const uint8_t *)array, size);
}

bool mcdr_serialize_array_uint8_t(mvbs_cdr_t *cdr, const uint8_t *array,
				  uint32_t size)
{
	return mcdr_serialize_array_byte_1(cdr, array, size);
}

bool mcdr_serialize_array_int16_t(mvbs_cdr_t *cdr, const int16_t *array,
				  uint32_t size)
{
	return mcdr_serialize_array_byte_2(cdr,
				mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(const uint16_t, array), size);
}

bool mcdr_serialize_array_uint16_t(mvbs_cdr_t *cdr, const uint16_t *array,
				   uint32_t size)
{
	return mcdr_serialize_array_byte_2(cdr,
				mcdr_buffer_is_little_endian(cdr), array, size);
}

bool mcdr_serialize_array_int32_t(mvbs_cdr_t *cdr, const int32_t *array,
				  uint32_t size)
{
	return mcdr_serialize_array_byte_4(cdr,
				mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(const uint32_t, array), size);
}

bool mcdr_serialize_array_uint32_t(mvbs_cdr_t *cdr, const uint32_t *array,
				   uint32_t size)
{
	return mcdr_serialize_array_byte_4(cdr,
				mcdr_buffer_is_little_endian(cdr), array, size);
}

bool mcdr_serialize_array_int64_t(mvbs_cdr_t *cdr, const int64_t *array,
				  uint32_t size)
{
	return mcdr_serialize_array_byte_8(cdr,
				mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(const uint64_t, array), size);
}

bool mcdr_serialize_array_uint64_t(mvbs_cdr_t *cdr, const uint64_t *array,
				   uint32_t size)
{
	return mcdr_serialize_array_byte_8(cdr,
				mcdr_buffer_is_little_endian(cdr), array, size);
}

bool mcdr_serialize_array_float(mvbs_cdr_t *cdr, const float *array,
				uint32_t size)
{
	const void *tmp_array = (const void *)array;

	return mcdr_serialize_array_byte_4(cdr,
				mcdr_buffer_is_little_endian(cdr),
				(const uint32_t *)tmp_array, size);
}

bool mcdr_serialize_array_double(mvbs_cdr_t *cdr, const double *array,
				 uint32_t size)
{
	const void *tmp_array = (const void *)array;

	return mcdr_serialize_array_byte_8(cdr,
				mcdr_buffer_is_little_endian(cdr),
				(const uint64_t *)tmp_array, size);
}

/* Part4: String Type */
bool mcdr_serialize_string(mvbs_cdr_t *cdr, const char *str)
{
	if ((cdr == NULL) || (str == NULL)) {
		return false;
	}

	return mcdr_serialize_sequence_char(cdr, str,
				(uint32_t)strlen(str) + 1U);
}

/* Part5: Sequence Type */
bool mcdr_serialize_sequence_byte_1(mvbs_cdr_t *cdr, bool is_little_endian,
				    const uint8_t *array, uint32_t size)
{
	(void)is_little_endian;

	if ((cdr == NULL) || (array == NULL)) {
		return false;
	}

	(void)mcdr_serialize_uint32_t(cdr, size);

	return mcdr_serialize_array_byte_1(cdr, array, size);
}

bool mcdr_serialize_sequence_byte_2(mvbs_cdr_t *cdr, bool is_little_endian,
				    const uint16_t *array, uint32_t size)
{
	if ((cdr == NULL) || (array == NULL)) {
		return false;
	}

	(void)mcdr_serialize_uint32_t(cdr, size);

	return mcdr_serialize_array_byte_2(cdr, is_little_endian, array, size);
}

bool mcdr_serialize_sequence_byte_4(mvbs_cdr_t *cdr, bool is_little_endian,
				    const uint32_t *array, uint32_t size)
{
	if ((cdr == NULL) || (array == NULL)) {
		return false;
	}

	(void)mcdr_serialize_uint32_t(cdr, size);

	return mcdr_serialize_array_byte_4(cdr, is_little_endian, array, size);
}

bool mcdr_serialize_sequence_byte_8(mvbs_cdr_t *cdr, bool is_little_endian,
				    const uint64_t *array, uint32_t size)
{
	if ((cdr == NULL) || (array == NULL)) {
		return false;
	}

	(void)mcdr_serialize_uint32_t(cdr, size);

	return mcdr_serialize_array_byte_8(cdr, is_little_endian, array, size);
}


bool mcdr_serialize_sequence_bool(mvbs_cdr_t *cdr, const bool *array,
	uint32_t size)
{
	return mcdr_serialize_sequence_byte_1(cdr,
				mcdr_buffer_is_little_endian(cdr),
				(const uint8_t *)array, size);
}

bool mcdr_serialize_sequence_char(mvbs_cdr_t *cdr, const char *array,
				  uint32_t size)
{
	return mcdr_serialize_sequence_byte_1(cdr,
				mcdr_buffer_is_little_endian(cdr),
				(const uint8_t *)array, size);
}

bool mcdr_serialize_sequence_int8_t(mvbs_cdr_t *cdr, const int8_t *array,
				    uint32_t size)
{
	return mcdr_serialize_sequence_byte_1(cdr,
				mcdr_buffer_is_little_endian(cdr),
				(const uint8_t *)array, size);
}

bool mcdr_serialize_sequence_uint8_t(mvbs_cdr_t *cdr, const uint8_t *array,
				     uint32_t size)
{
	return mcdr_serialize_sequence_byte_1(cdr,
				mcdr_buffer_is_little_endian(cdr),
				(const uint8_t *)array, size);
}

bool mcdr_serialize_sequence_int16_t(mvbs_cdr_t *cdr, const int16_t *array,
				     uint32_t size)
{
	return mcdr_serialize_sequence_byte_2(cdr,
				mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(const uint16_t, array), size);
}

bool mcdr_serialize_sequence_uint16_t(mvbs_cdr_t *cdr, const uint16_t *array,
				      uint32_t size)
{
	return mcdr_serialize_sequence_byte_2(cdr,
				mcdr_buffer_is_little_endian(cdr),
				(const uint16_t *)array, size);
}

bool mcdr_serialize_sequence_int32_t(mvbs_cdr_t *cdr, const int32_t *array,
				     uint32_t size)
{
	return mcdr_serialize_sequence_byte_4(cdr,
				mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(const uint32_t, array), size);
}

bool mcdr_serialize_sequence_uint32_t(mvbs_cdr_t *cdr, const uint32_t *array,
				      uint32_t size)
{
	return mcdr_serialize_sequence_byte_4(cdr,
				mcdr_buffer_is_little_endian(cdr),
				(const uint32_t *)array, size);
}

bool mcdr_serialize_sequence_int64_t(mvbs_cdr_t *cdr, const int64_t *array,
				     uint32_t size)
{
	return mcdr_serialize_sequence_byte_8(cdr,
				mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(const uint64_t, array), size);
}


bool mcdr_serialize_sequence_uint64_t(mvbs_cdr_t *cdr, const uint64_t *array,
				      uint32_t size)
{
	return mcdr_serialize_sequence_byte_8(cdr,
				mcdr_buffer_is_little_endian(cdr),
				(const uint64_t *)array, size);
}

bool mcdr_serialize_sequence_float(mvbs_cdr_t *cdr, const float *array,
				   uint32_t size)
{
	return mcdr_serialize_sequence_byte_4(cdr,
				mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(const uint32_t, array), size);
}

bool mcdr_serialize_sequence_double(mvbs_cdr_t *cdr, const double *array,
				    uint32_t size)
{
	return mcdr_serialize_sequence_byte_8(cdr,
				mcdr_buffer_is_little_endian(cdr),
				static_cast_ptr(const uint64_t, array), size);
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
