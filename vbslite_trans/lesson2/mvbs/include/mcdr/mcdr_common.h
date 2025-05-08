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

#ifndef MVBS_MCDR_COMMON_H
#define MVBS_MCDR_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct mvbs_cdr {
	const uint8_t	*start;
	const uint8_t	*end;
	uint8_t		*cur_pos;

	uint8_t		last_data_size;

	bool		is_le;
	bool		error;
} mvbs_cdr_t;

struct mcdr_sequence {
	void		*buffer; /* Only support one mem block */
	uint32_t	max_cnt;
	uint32_t	cur_cnt;
	uint32_t	elem_size;

	uint8_t		flags;
};

extern const bool LOCAL_IS_LITTLE_ENDIAN;

void mcdr_init_buffer(mvbs_cdr_t *cdr, const uint8_t *pdata, uint32_t size);

void mcdr_init_buffer_offset(mvbs_cdr_t *cdr, const uint8_t *pdata,
			     uint32_t size, uint32_t offset);

/* FIXME: make sure that offset is necessary. */
void mcdr_init_buffer_offset_endian(mvbs_cdr_t *cdr, const uint8_t *pdata,
				    uint32_t size, uint32_t offset,
				    bool is_little_endian);

void mcdr_copy_buffer(mvbs_cdr_t *mb_dest, const mvbs_cdr_t *mb_source);

void mcdr_reset_buffer(mvbs_cdr_t *cdr);

/* FIXME: Only for RPC */
void mcdr_reset_buffer_offset(mvbs_cdr_t *cdr, uint32_t offset);

void mcdr_buffer_append_data(mvbs_cdr_t *cdr, const void *data, uint32_t size);

void mcdr_fill_buffer_with_offset(mvbs_cdr_t *cdr, uint32_t offset,
				  const void *data, uint32_t size);

void mcdr_align_to(mvbs_cdr_t *cdr, uint32_t alignment);

uint32_t mcdr_get_alignment(uint32_t buffer_position, uint32_t data_size);

/* Get the total size of cdr buffer. */
size_t mcdr_buffer_size(const mvbs_cdr_t *cdr);

/* Get current valid data size in cdr buffer. */
size_t mcdr_buffer_length(const mvbs_cdr_t *cdr);

/* Get current remain data size in cdr buffer. */
size_t mcdr_buffer_remaining(const mvbs_cdr_t *cdr);

bool mcdr_sequence_init(struct mcdr_sequence *self, uint32_t element_size,
			      uint32_t maximum);

uint32_t mcdr_sequence_get_max_length(const struct mcdr_sequence *self);

uint32_t mcdr_sequence_get_length(const struct mcdr_sequence *self);

bool mcdr_sequence_set_length(struct mcdr_sequence *self, uint32_t new_length);

void *mcdr_sequence_get_reference(const struct mcdr_sequence *self, uint32_t i);

bool mcdr_sequence_set_buffer(struct mcdr_sequence *self, void *buffer,
			      uint32_t buffer_size);

static inline void mcdr_align_to_uint32(mvbs_cdr_t *cdr)
{
	mcdr_align_to(cdr, 4U);
}

/* Get the cdr is_le. */
static inline bool mcdr_buffer_is_little_endian(const mvbs_cdr_t *cdr)
{
	if (cdr == NULL) {
		return false;	/* FIXME: default is big endian */
	}

	return cdr->is_le;
}

/* Set the cdr is_le. */
static inline bool mcdr_buffer_set_little_endian(mvbs_cdr_t *cdr,
						 bool is_little_endian)
{
	if (cdr == NULL) {
		return false;
	}

	cdr->is_le = is_little_endian;

	return true;
}

/* Get the cdr error. */
static inline bool mcdr_buffer_has_error(const mvbs_cdr_t *cdr)
{
	if (cdr == NULL) {
		return false;
	}

	return cdr->error;
}

static inline const uint8_t *mcdr_get_buffer(const mvbs_cdr_t *cdr)
{
	if (cdr == NULL) {
		return NULL;
	}

	return cdr->start;
}

/*
 * High frequency function.
 * PLEASE NOTE:
 * 1. pow_two must be a power of 2
 * 2. When pow_two is a power of 2, offset % pow_two can be equivalently
 *    replaced with offset & (data_size - 1U), which can avoid the time-consuming
 *    modulo operation.
 *    Since bit operations are generally more efficient than modulo operations,
 *    this can increase the execution speed of the function.
 */
static inline uint32_t mcdr_buffer_alignment(const mvbs_cdr_t *cdr,
					     uint32_t pow_two)
{
	/*
	 * cdr->cur_pos >= cdr->start is naturally established.
	 */
	if (pow_two > cdr->last_data_size) {
		uintptr_t offset = (uintptr_t)(cdr->cur_pos - cdr->start);
		return (uint32_t)(0U - offset) & (pow_two - 1U);
	}

	return 0;
}

/*
 * High frequency function
 * the user must ensure that cdr is not empty
 */
static inline uint32_t mcdr_buffer_alignment_common(const mvbs_cdr_t *cdr,
						    uint32_t any_size)
{
	if (any_size > cdr->last_data_size) {
		ptrdiff_t diff = cdr->cur_pos - cdr->start;
		return (any_size - ((uint32_t)diff % any_size)) & (any_size - 1U);
	}

	return 0;
}

/*
 * High frequency function
 * the user must ensure that cdr is not empty
 */
static inline bool mcdr_check_buffer(mvbs_cdr_t *cdr, uint32_t bytes)
{
	if (!cdr->error && ((cdr->cur_pos + bytes) > cdr->end)) {
		cdr->error = true;
	}

	return !cdr->error;
}

static inline uint16_t mcdr_reverse_2bytes(uint16_t x)
{
	return (x >> 8) | (x << 8);
}

static inline uint32_t mcdr_reverse_4bytes(uint32_t x)
{
	x = (x >> 16) | (x << 16);

	x = ((x & 0xFF00FF00U) >> 8) |
	    ((x & 0x00FF00FFU) << 8);

	return x;
}

static inline uint64_t mcdr_reverse_8bytes(uint64_t x)
{
	x = (x >> 32) | (x << 32);

	x = ((x & 0xFFFF0000FFFF0000ULL) >> 16) |
	    ((x & 0x0000FFFF0000FFFFULL) << 16);

	x = ((x & 0xFF00FF00FF00FF00ULL) >> 8) |
	    ((x & 0x00FF00FF00FF00FFULL) << 8);

	return x;
}

#endif
