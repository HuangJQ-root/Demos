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

#ifndef MVBS_CORE_DIAG_RECORDER_H
#define MVBS_CORE_DIAG_RECORDER_H

#include <mvbs/errno.h>
#include <discovery/sddp.h>

struct writer_cache_change;

void recorder_request_on_data(struct participant *ptcp,
			      uint8_t *data, uint16_t size);

int32_t recorder_reply_data(struct participant *ptcp,
				uint8_t *data, uint16_t size);

int32_t recorder_send_writer_record(struct participant *ptcp,
				struct mvbs_cdr *cdr,
				struct writer_cache_change *wcc,
				locator_t *loc,
				struct writer *w,
				uint32_t submessage_header_offset);

int32_t recorder_send_reader_record(struct participant *ptcp,
				   struct message_processing_info *pmsg_info,
				   uint8_t* data_start_ptr,
				   uint16_t data_size,
				   struct reader *r);
#endif
