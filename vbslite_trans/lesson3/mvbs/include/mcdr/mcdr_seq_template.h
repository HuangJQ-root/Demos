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

#ifndef	MVBS_MCDR_SEQ_TEMPLATE_H
#define	MVBS_MCDR_SEQ_TEMPLATE_H

#include <mvbs/base_type.h>
#include <mvbs/utils/cdefs.h>

#endif

/*
 * Template Parameter List:
 * 1. MSEQ_ELEM: the type of element in this sequence.
 * 2. MSEQ_NAME: the type name of this mvbs sequence type.
 *
 */

#ifndef MSEQ_ELEM
#error "A sequence type should has a valid element type MSEQ_ELEM".
#endif

#ifndef MSEQ_NAME
#error "A sequence type name should be indicated by MSEQ_NAME".
#endif


struct MSEQ_NAME {
	MSEQ_ELEM 	*buffer;
	uint32_t 	max_cnt;
	uint32_t 	cur_cnt;
	uint32_t 	elem_size;

	uint8_t 	flags;
};

static inline bool CONCAT(MSEQ_NAME,_init)(struct MSEQ_NAME *self, uint32_t max_size)
{
	return mcdr_sequence_init((struct mcdr_sequence *)self,
						sizeof(MSEQ_ELEM), max_size);
}

static inline uint32_t CONCAT(MSEQ_NAME,_get_max_length)(const struct MSEQ_NAME *self)
{
	return mcdr_sequence_get_max_length((const struct mcdr_sequence *)self);
}

static inline uint32_t CONCAT(MSEQ_NAME,_get_length)(const struct MSEQ_NAME *self)
{
	return mcdr_sequence_get_length((const struct mcdr_sequence *)self);
}

static inline bool CONCAT(MSEQ_NAME,_set_length)(struct MSEQ_NAME *self, uint32_t new_length)
{
	return mcdr_sequence_set_length((struct mcdr_sequence *)self, new_length);
}

static inline MSEQ_ELEM *CONCAT(MSEQ_NAME,_get_reference)(const struct MSEQ_NAME *self, uint32_t i)
{
	return (MSEQ_ELEM *)mcdr_sequence_get_reference((const struct mcdr_sequence *)self, i);
}

static inline bool CONCAT(MSEQ_NAME,_set_contiguous_buffer)(struct MSEQ_NAME *self,
					MSEQ_ELEM *buffer, uint32_t buffer_size)
{
	return mcdr_sequence_set_buffer((struct mcdr_sequence *)self,
					(void *)buffer, buffer_size);
}

#undef MSEQ_ELEM
#undef MSEQ_NAME
