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

#include <mvbs/utils/cdefs.h>
#include <mvbs/utils/fifo.h>
#include <mvbs/utils/string.h>
#include <mvbs/adapter/adapter.h>

int32_t mvbs_fifo_init(struct mvbs_fifo *fifo, void *buffer, size_t size)
{
	if (fifo == NULL) {
		return -ERR_INVALID;
	}

	/* check if the size is power of 2 */
	if (!((size != 0U) && ((size & (size - 1U)) == 0U))) {
		return -ERR_INVALID;
	}

	fifo->in	= 0U;
	fifo->out	= 0U;
	fifo->mask	= size - 1U;
	fifo->data	= buffer;

	return 0;
}

static void mvbs_fifo_copy_in(struct mvbs_fifo *fifo, const void *src,
							size_t len, size_t off)
{
	size_t size	= fifo->mask + 1U;
	size_t offset	= off;
	size_t l;

	offset &= fifo->mask;

	l = min_size(len, size - offset);

	(void)mvbs_memcpy((char*)fifo->data + offset, (const char*)src, l);
	(void)mvbs_memcpy((char*)fifo->data, (const char*)src + l, len - l);

	/*
	 * make sure that the data in the fifo is up to date before
	 * incrementing the fifo->in index counter
	 */
	mvbs_smp_mb();
}

static void mvbs_fifo_copy_out(struct mvbs_fifo *fifo, void *dst,
						size_t len, size_t off)
{
	size_t size	= fifo->mask + 1U;
	size_t offset	= off;
	size_t l;

	offset &= fifo->mask;

	l = min_size(len, size - offset);

	(void)mvbs_memcpy((char*)dst, (char*)fifo->data + offset, l);
	(void)mvbs_memcpy((char*)dst + l, (char*)fifo->data, len - l);

	/*
	 * make sure that the data is copied before
	 * incrementing the fifo->out index counter
	 */
	mvbs_smp_mb();
}

size_t mvbs_fifo_in(struct mvbs_fifo *fifo, const void *buf, size_t len)
{
	size_t l	= 0U;
	size_t length	= len;

	l = mvbs_fifo_unused(fifo);
	if (length > l) {
		length = l;
	}

	mvbs_fifo_copy_in(fifo, buf, length, fifo->in);

	fifo->in += length;

	return length;
}

size_t mvbs_fifo_peek(struct mvbs_fifo *fifo, void *buf, size_t len)
{
	size_t length	= len;

	length = min_size(length, (size_t)mvbs_fifo_len(fifo));

	mvbs_fifo_copy_out(fifo, buf, length, fifo->out);

	return length;
}

size_t mvbs_fifo_out(struct mvbs_fifo *fifo, void *buf, size_t len)
{
	size_t length	= len;

	length = mvbs_fifo_peek(fifo, buf, length);

	fifo->out += length;

	return length;
}

size_t mvbs_fifo_skip(struct mvbs_fifo *fifo, size_t len)
{
	size_t skip_length;

	skip_length = min_size(len, (size_t)mvbs_fifo_len(fifo));

	fifo->out += skip_length;

	return skip_length;
}

size_t mvbs_fifo_peek_skip(struct mvbs_fifo *fifo, void *buf,
						size_t len, size_t fifo_skip)
{
	size_t l;

	if (fifo_skip >= (size_t)mvbs_fifo_len(fifo)) {
		return 0U;
	}

	l = min_size(len + fifo_skip, (size_t)mvbs_fifo_len(fifo));

	mvbs_fifo_copy_out(fifo, buf, l - fifo_skip, fifo->out + fifo_skip);

	return l - fifo_skip;
}


size_t mvbs_fifo_out_skip(struct mvbs_fifo *fifo, void *buf,
						size_t len, size_t fifo_skip)
{
	size_t l;

	l = mvbs_fifo_peek_skip(fifo, buf, len, fifo_skip);

	fifo->out += l + fifo_skip;

	return l;
}

#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>
