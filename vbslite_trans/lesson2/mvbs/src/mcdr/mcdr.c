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
#include <mvbs/utils/log.h>
#include <mcdr/mcdr.h>

#ifdef	MVBS_BIG_ENDIAN
const bool LOCAL_IS_LITTLE_ENDIAN = false;
#else
const bool LOCAL_IS_LITTLE_ENDIAN = true;
#endif

static inline void mcdr_set_buffer(mvbs_cdr_t *cdr, const uint8_t *buffer)
{
	cdr->start = buffer;
}

static inline void mcdr_set_buffer_final(mvbs_cdr_t *cdr, const uint8_t *ptr)
{
	cdr->end = ptr;
}

static inline void mcdr_set_buffer_iter(mvbs_cdr_t *cdr, uint8_t *ptr)
{
	cdr->cur_pos = ptr;
}

static inline const uint8_t* mcdr_get_buffer_final(const mvbs_cdr_t *cdr)
{
	return cdr->end;
}

void mcdr_copy_buffer(mvbs_cdr_t *cdr_dest, const mvbs_cdr_t *cdr_source)
{
	if ((cdr_dest == NULL) || (cdr_source == NULL)) {
		return;
	}

	(void)memcpy(cdr_dest, cdr_source, sizeof(mvbs_cdr_t));
}

void mcdr_init_buffer_offset_endian(mvbs_cdr_t *cdr, const uint8_t *pdata,
				    uint32_t size, uint32_t offset,
				    bool is_little_endian)
{
	if ((cdr == NULL) || (pdata == NULL)) {
		return;
	}

	mcdr_set_buffer(cdr, pdata);
	mcdr_set_buffer_final(cdr, mcdr_get_buffer(cdr) + size);
	mcdr_set_buffer_iter(cdr,  (uint8_t *)mcdr_get_buffer(cdr) + offset);

	cdr->error = false;

	(void)mcdr_buffer_set_little_endian(cdr, is_little_endian);

	cdr->last_data_size = 0U;
}

void mcdr_init_buffer_offset(mvbs_cdr_t *cdr, const uint8_t *pdata,
			     uint32_t size, uint32_t offset)
{
	mcdr_init_buffer_offset_endian(cdr, pdata, size, offset,
				       LOCAL_IS_LITTLE_ENDIAN);
}

void mcdr_init_buffer(mvbs_cdr_t *cdr, const uint8_t *pdata, uint32_t size)
{
	mcdr_init_buffer_offset(cdr, pdata, size, 0U);
}

void mcdr_reset_buffer_offset(mvbs_cdr_t *cdr, uint32_t offset)
{
	if (cdr == NULL) {
		return;
	}

	if (offset >= mcdr_buffer_size(cdr)) {
		return ;
	}

	cdr->cur_pos		= (uint8_t *)cdr->start + offset;
	cdr->last_data_size	= 0U;
	cdr->error		= false;
}

void mcdr_reset_buffer(mvbs_cdr_t *cdr)
{
	if (cdr == NULL) {
		return;
	}

	cdr->cur_pos		= (uint8_t *)cdr->start;
	cdr->last_data_size	= 0U;
	cdr->error		= false;
}

void mcdr_fill_buffer_with_offset(mvbs_cdr_t *cdr, uint32_t offset,
				  const void *data, uint32_t size)
{
	if (cdr == NULL || data == NULL || size == 0) {
		return;
	}

	if (offset + size > mcdr_buffer_size(cdr)) {
		return;
	}

	memcpy((void*)(cdr->start + offset), data, size);
}

void mcdr_buffer_append_data(mvbs_cdr_t *cdr, const void *data, uint32_t size)
{
	if (cdr == NULL || data == NULL || size == 0) {
		return;
	}

	/* ensure cdr->cur_pos can't over cdr->end */
	if (mcdr_buffer_remaining(cdr) < size) {
		return;
	}

	memcpy(cdr->cur_pos, data, size);

	cdr->cur_pos += size;
}

void mcdr_align_to(mvbs_cdr_t *cdr, uint32_t alignment)
{
	uint32_t offset = 0U;

	if (cdr == NULL) {
		return;
	}

	offset = mcdr_buffer_alignment_common(cdr, alignment);

	cdr->cur_pos += offset;

	if (cdr->cur_pos > mcdr_get_buffer_final(cdr)) {
		mcdr_set_buffer_iter(cdr, (uint8_t *)mcdr_get_buffer_final(cdr));
	}

	cdr->last_data_size = alignment;
}

uint32_t mcdr_get_alignment(uint32_t buffer_position, uint32_t size)
{
	if ((size & (size - 1U)) != 0) {
	    return 0;
	}

	return (size - (buffer_position & (size - 1U))) & (size - 1U);
}

size_t mcdr_buffer_remaining(const mvbs_cdr_t *cdr)
{
	if (cdr == NULL) {
		return 0;
	}

	if (mcdr_get_buffer_final(cdr) < cdr->cur_pos) {
		return 0;
	}

	ptrdiff_t diff = mcdr_get_buffer_final(cdr) - cdr->cur_pos;

	return (size_t)diff;
}

size_t mcdr_buffer_size(const mvbs_cdr_t *cdr)
{
	if (cdr == NULL) {
		return 0;
	}

	if (mcdr_get_buffer_final(cdr) < mcdr_get_buffer(cdr)) {
		return 0;
	}

        ptrdiff_t diff = mcdr_get_buffer_final(cdr) - mcdr_get_buffer(cdr);

        return (size_t)diff;
}

size_t mcdr_buffer_length(const mvbs_cdr_t *cdr)
{
	if (cdr == NULL) {
		return 0;
	}

	if (cdr->cur_pos < mcdr_get_buffer(cdr)) {
		return 0;
	}

        ptrdiff_t diff = cdr->cur_pos - mcdr_get_buffer(cdr);

        return (size_t)diff;
}


bool mcdr_sequence_init(struct mcdr_sequence *self, uint32_t element_size, uint32_t maximum)
{
	if (self == NULL) {
		return false;
	}

	self->buffer = NULL;
	self->max_cnt = maximum;
	self->cur_cnt = 0;
	self->elem_size = element_size;
	self->flags = 0;

	return true;
}

uint32_t mcdr_sequence_get_max_length(const struct mcdr_sequence * self)
{

	if(self == NULL) {
		return 0;
	}

	return self->max_cnt;
}

uint32_t mcdr_sequence_get_length(const struct mcdr_sequence * self)
{
	if (self == NULL) {
		return false;
	}

	return self->cur_cnt;
}

bool mcdr_sequence_set_length(struct mcdr_sequence * self, uint32_t new_length)
{
	if ((self == NULL) || (new_length > self->max_cnt)) {
		return false;
	}

	self->cur_cnt = new_length;

	return true;
}

void* mcdr_sequence_get_reference(const struct mcdr_sequence *self, uint32_t i)
{
	if (self == NULL) {
		return NULL;
	}

	return (void *)((char*)self->buffer + (i * self->elem_size));
}

bool mcdr_sequence_set_buffer(struct mcdr_sequence *self, void *buffer,
							  uint32_t buffer_size)
{
	if ((self == NULL) || (buffer == NULL)) {
		return false;
	}

	if (buffer_size < self->cur_cnt) {
		pr_warn("buffer_size:%d < self->_length, maximun set failed:%d\n",
						buffer_size,self->cur_cnt);
		return false;
	}

	self->buffer = buffer;
	return true;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
