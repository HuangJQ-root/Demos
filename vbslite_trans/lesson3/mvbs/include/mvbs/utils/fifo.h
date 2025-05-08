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

#ifndef MVBS_UTILS_FIFO_H
#define MVBS_UTILS_FIFO_H

#include <mvbs/errno.h>
#include <mvbs/utils/cdefs.h>

struct mvbs_fifo {
	uint32_t	in;
	uint32_t	out;
	uint32_t	mask;	/* sizeof(data) -1 */
	void		*data;	/* sizeof(data) should be power of 2 */
};

int32_t mvbs_fifo_init(struct mvbs_fifo *fifo, void *buffer, size_t size);

static inline void mvbs_fifo_reset(struct mvbs_fifo *fifo)
{
	if (fifo != NULL) {
		fifo->in	= 0U;
		fifo->out	= 0U;
		fifo->mask	= 0U;
		fifo->data	= NULL;
	}
}

static inline size_t mvbs_fifo_size(struct mvbs_fifo *fifo)
{
	return (size_t)(fifo->mask + 1U);
}

static inline int32_t mvbs_fifo_len(struct mvbs_fifo *fifo)
{
	uint32_t result = fifo->in - fifo->out;
	return (int32_t)(result);
}

static inline bool mvbs_fifo_is_empty(struct mvbs_fifo *fifo)
{
	return fifo->in == fifo->out;
}

static inline bool mvbs_fifo_is_full(struct mvbs_fifo *fifo)
{
	return mvbs_fifo_len(fifo) > (int32_t)fifo->mask;
}

static inline size_t mvbs_fifo_unused(struct mvbs_fifo *fifo)
{
	return (size_t)((fifo->mask + 1U) - (fifo->in - fifo->out));
}

size_t mvbs_fifo_in(struct mvbs_fifo *fifo, const void *buf, size_t len);

size_t mvbs_fifo_peek(struct mvbs_fifo *fifo, void *buf, size_t len);
size_t mvbs_fifo_out(struct mvbs_fifo *fifo, void *buf, size_t len);

size_t mvbs_fifo_skip(struct mvbs_fifo *fifo, size_t len);

size_t mvbs_fifo_peek_skip(struct mvbs_fifo *fifo, void *buf,
						size_t len, size_t fifo_skip);

size_t mvbs_fifo_out_skip(struct mvbs_fifo *fifo, void *buf,
						size_t len, size_t fifo_skip);

#endif /* !MVBS_FIFO_H */
