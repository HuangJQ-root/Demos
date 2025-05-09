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

/*
 * This file was generated form vbslite_perf.idl by the mvbs-idl-gen tool.
 */


#include <mvbs/sections/start_sec_code.h>
#include <mvbs/sections/start_sec_bss.h>
#include <mvbs/sections/start_sec_const.h>
#include <mvbs/sections/start_sec_data.h>

#include <string.h>

#include <mvbs/errno.h>
#include <mvbs/core.h>
#include <mvbs/utils/cdefs.h>
#include <mvbs/rtps/message.h>

#include <mcdr/mcdr.h>

#include <mvbs/utils/string.h>
#include <mvbs/utils/mm.h>

#include "vbslite_perfPlugin.h"



/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld1
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld1_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld1_init(HelloWorld1 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld1_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld1 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld1_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld1 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld1_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld1_topic_max_size(0) + 4u);

	if (size != HELLOWORLD1_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD1_SIZE:%d\n", size, HELLOWORLD1_SIZE);
		pr_warn("size is not equal to HELLOWORLD1_SIZE\n");

		return size;
	}

	return HELLOWORLD1_SIZE;
}

static bool HelloWorld1_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld1  *topic = (HelloWorld1  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld1_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld1_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld1 *topic = (HelloWorld1 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld1_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld1 *HelloWorld1_create(void)
{
	HelloWorld1 *sample;
	uint32_t size = sizeof(struct HelloWorld1);

	sample = (HelloWorld1 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld1_delete(HelloWorld1 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld2
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld2_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld2_init(HelloWorld2 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld2_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld2 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld2_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld2 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld2_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld2_topic_max_size(0) + 4u);

	if (size != HELLOWORLD2_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD2_SIZE:%d\n", size, HELLOWORLD2_SIZE);
		pr_warn("size is not equal to HELLOWORLD2_SIZE\n");

		return size;
	}

	return HELLOWORLD2_SIZE;
}

static bool HelloWorld2_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld2  *topic = (HelloWorld2  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld2_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld2_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld2 *topic = (HelloWorld2 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld2_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld2 *HelloWorld2_create(void)
{
	HelloWorld2 *sample;
	uint32_t size = sizeof(struct HelloWorld2);

	sample = (HelloWorld2 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld2_delete(HelloWorld2 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld3
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld3_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld3_init(HelloWorld3 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld3_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld3 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld3_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld3 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld3_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld3_topic_max_size(0) + 4u);

	if (size != HELLOWORLD3_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD3_SIZE:%d\n", size, HELLOWORLD3_SIZE);
		pr_warn("size is not equal to HELLOWORLD3_SIZE\n");

		return size;
	}

	return HELLOWORLD3_SIZE;
}

static bool HelloWorld3_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld3  *topic = (HelloWorld3  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld3_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld3_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld3 *topic = (HelloWorld3 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld3_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld3 *HelloWorld3_create(void)
{
	HelloWorld3 *sample;
	uint32_t size = sizeof(struct HelloWorld3);

	sample = (HelloWorld3 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld3_delete(HelloWorld3 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld4
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld4_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld4_init(HelloWorld4 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld4_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld4 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld4_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld4 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld4_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld4_topic_max_size(0) + 4u);

	if (size != HELLOWORLD4_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD4_SIZE:%d\n", size, HELLOWORLD4_SIZE);
		pr_warn("size is not equal to HELLOWORLD4_SIZE\n");

		return size;
	}

	return HELLOWORLD4_SIZE;
}

static bool HelloWorld4_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld4  *topic = (HelloWorld4  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld4_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld4_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld4 *topic = (HelloWorld4 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld4_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld4 *HelloWorld4_create(void)
{
	HelloWorld4 *sample;
	uint32_t size = sizeof(struct HelloWorld4);

	sample = (HelloWorld4 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld4_delete(HelloWorld4 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld5
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld5_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld5_init(HelloWorld5 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld5_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld5 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld5_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld5 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld5_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld5_topic_max_size(0) + 4u);

	if (size != HELLOWORLD5_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD5_SIZE:%d\n", size, HELLOWORLD5_SIZE);
		pr_warn("size is not equal to HELLOWORLD5_SIZE\n");

		return size;
	}

	return HELLOWORLD5_SIZE;
}

static bool HelloWorld5_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld5  *topic = (HelloWorld5  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld5_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld5_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld5 *topic = (HelloWorld5 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld5_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld5 *HelloWorld5_create(void)
{
	HelloWorld5 *sample;
	uint32_t size = sizeof(struct HelloWorld5);

	sample = (HelloWorld5 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld5_delete(HelloWorld5 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld6
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld6_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld6_init(HelloWorld6 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld6_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld6 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld6_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld6 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld6_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld6_topic_max_size(0) + 4u);

	if (size != HELLOWORLD6_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD6_SIZE:%d\n", size, HELLOWORLD6_SIZE);
		pr_warn("size is not equal to HELLOWORLD6_SIZE\n");

		return size;
	}

	return HELLOWORLD6_SIZE;
}

static bool HelloWorld6_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld6  *topic = (HelloWorld6  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld6_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld6_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld6 *topic = (HelloWorld6 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld6_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld6 *HelloWorld6_create(void)
{
	HelloWorld6 *sample;
	uint32_t size = sizeof(struct HelloWorld6);

	sample = (HelloWorld6 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld6_delete(HelloWorld6 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld7
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld7_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld7_init(HelloWorld7 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld7_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld7 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld7_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld7 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld7_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld7_topic_max_size(0) + 4u);

	if (size != HELLOWORLD7_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD7_SIZE:%d\n", size, HELLOWORLD7_SIZE);
		pr_warn("size is not equal to HELLOWORLD7_SIZE\n");

		return size;
	}

	return HELLOWORLD7_SIZE;
}

static bool HelloWorld7_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld7  *topic = (HelloWorld7  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld7_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld7_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld7 *topic = (HelloWorld7 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld7_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld7 *HelloWorld7_create(void)
{
	HelloWorld7 *sample;
	uint32_t size = sizeof(struct HelloWorld7);

	sample = (HelloWorld7 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld7_delete(HelloWorld7 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld8
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld8_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld8_init(HelloWorld8 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld8_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld8 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld8_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld8 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld8_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld8_topic_max_size(0) + 4u);

	if (size != HELLOWORLD8_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD8_SIZE:%d\n", size, HELLOWORLD8_SIZE);
		pr_warn("size is not equal to HELLOWORLD8_SIZE\n");

		return size;
	}

	return HELLOWORLD8_SIZE;
}

static bool HelloWorld8_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld8  *topic = (HelloWorld8  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld8_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld8_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld8 *topic = (HelloWorld8 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld8_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld8 *HelloWorld8_create(void)
{
	HelloWorld8 *sample;
	uint32_t size = sizeof(struct HelloWorld8);

	sample = (HelloWorld8 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld8_delete(HelloWorld8 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld9
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld9_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld9_init(HelloWorld9 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld9_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld9 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld9_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld9 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld9_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld9_topic_max_size(0) + 4u);

	if (size != HELLOWORLD9_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD9_SIZE:%d\n", size, HELLOWORLD9_SIZE);
		pr_warn("size is not equal to HELLOWORLD9_SIZE\n");

		return size;
	}

	return HELLOWORLD9_SIZE;
}

static bool HelloWorld9_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld9  *topic = (HelloWorld9  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld9_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld9_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld9 *topic = (HelloWorld9 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld9_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld9 *HelloWorld9_create(void)
{
	HelloWorld9 *sample;
	uint32_t size = sizeof(struct HelloWorld9);

	sample = (HelloWorld9 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld9_delete(HelloWorld9 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld10
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld10_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld10_init(HelloWorld10 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld10_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld10 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld10_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld10 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld10_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld10_topic_max_size(0) + 4u);

	if (size != HELLOWORLD10_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD10_SIZE:%d\n", size, HELLOWORLD10_SIZE);
		pr_warn("size is not equal to HELLOWORLD10_SIZE\n");

		return size;
	}

	return HELLOWORLD10_SIZE;
}

static bool HelloWorld10_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld10  *topic = (HelloWorld10  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld10_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld10_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld10 *topic = (HelloWorld10 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld10_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld10 *HelloWorld10_create(void)
{
	HelloWorld10 *sample;
	uint32_t size = sizeof(struct HelloWorld10);

	sample = (HelloWorld10 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld10_delete(HelloWorld10 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld11
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld11_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld11_init(HelloWorld11 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld11_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld11 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld11_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld11 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld11_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld11_topic_max_size(0) + 4u);

	if (size != HELLOWORLD11_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD11_SIZE:%d\n", size, HELLOWORLD11_SIZE);
		pr_warn("size is not equal to HELLOWORLD11_SIZE\n");

		return size;
	}

	return HELLOWORLD11_SIZE;
}

static bool HelloWorld11_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld11  *topic = (HelloWorld11  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld11_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld11_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld11 *topic = (HelloWorld11 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld11_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld11 *HelloWorld11_create(void)
{
	HelloWorld11 *sample;
	uint32_t size = sizeof(struct HelloWorld11);

	sample = (HelloWorld11 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld11_delete(HelloWorld11 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld12
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld12_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld12_init(HelloWorld12 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld12_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld12 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld12_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld12 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld12_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld12_topic_max_size(0) + 4u);

	if (size != HELLOWORLD12_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD12_SIZE:%d\n", size, HELLOWORLD12_SIZE);
		pr_warn("size is not equal to HELLOWORLD12_SIZE\n");

		return size;
	}

	return HELLOWORLD12_SIZE;
}

static bool HelloWorld12_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld12  *topic = (HelloWorld12  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld12_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld12_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld12 *topic = (HelloWorld12 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld12_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld12 *HelloWorld12_create(void)
{
	HelloWorld12 *sample;
	uint32_t size = sizeof(struct HelloWorld12);

	sample = (HelloWorld12 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld12_delete(HelloWorld12 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld13
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld13_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld13_init(HelloWorld13 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld13_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld13 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld13_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld13 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld13_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld13_topic_max_size(0) + 4u);

	if (size != HELLOWORLD13_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD13_SIZE:%d\n", size, HELLOWORLD13_SIZE);
		pr_warn("size is not equal to HELLOWORLD13_SIZE\n");

		return size;
	}

	return HELLOWORLD13_SIZE;
}

static bool HelloWorld13_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld13  *topic = (HelloWorld13  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld13_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld13_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld13 *topic = (HelloWorld13 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld13_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld13 *HelloWorld13_create(void)
{
	HelloWorld13 *sample;
	uint32_t size = sizeof(struct HelloWorld13);

	sample = (HelloWorld13 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld13_delete(HelloWorld13 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld14
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld14_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld14_init(HelloWorld14 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld14_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld14 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld14_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld14 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld14_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld14_topic_max_size(0) + 4u);

	if (size != HELLOWORLD14_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD14_SIZE:%d\n", size, HELLOWORLD14_SIZE);
		pr_warn("size is not equal to HELLOWORLD14_SIZE\n");

		return size;
	}

	return HELLOWORLD14_SIZE;
}

static bool HelloWorld14_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld14  *topic = (HelloWorld14  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld14_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld14_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld14 *topic = (HelloWorld14 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld14_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld14 *HelloWorld14_create(void)
{
	HelloWorld14 *sample;
	uint32_t size = sizeof(struct HelloWorld14);

	sample = (HelloWorld14 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld14_delete(HelloWorld14 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld15
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld15_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld15_init(HelloWorld15 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld15_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld15 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld15_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld15 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld15_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld15_topic_max_size(0) + 4u);

	if (size != HELLOWORLD15_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD15_SIZE:%d\n", size, HELLOWORLD15_SIZE);
		pr_warn("size is not equal to HELLOWORLD15_SIZE\n");

		return size;
	}

	return HELLOWORLD15_SIZE;
}

static bool HelloWorld15_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld15  *topic = (HelloWorld15  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld15_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld15_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld15 *topic = (HelloWorld15 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld15_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld15 *HelloWorld15_create(void)
{
	HelloWorld15 *sample;
	uint32_t size = sizeof(struct HelloWorld15);

	sample = (HelloWorld15 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld15_delete(HelloWorld15 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld16
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld16_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld16_init(HelloWorld16 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld16_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld16 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld16_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld16 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld16_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld16_topic_max_size(0) + 4u);

	if (size != HELLOWORLD16_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD16_SIZE:%d\n", size, HELLOWORLD16_SIZE);
		pr_warn("size is not equal to HELLOWORLD16_SIZE\n");

		return size;
	}

	return HELLOWORLD16_SIZE;
}

static bool HelloWorld16_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld16  *topic = (HelloWorld16  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld16_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld16_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld16 *topic = (HelloWorld16 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld16_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld16 *HelloWorld16_create(void)
{
	HelloWorld16 *sample;
	uint32_t size = sizeof(struct HelloWorld16);

	sample = (HelloWorld16 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld16_delete(HelloWorld16 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld17
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld17_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld17_init(HelloWorld17 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld17_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld17 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld17_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld17 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld17_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld17_topic_max_size(0) + 4u);

	if (size != HELLOWORLD17_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD17_SIZE:%d\n", size, HELLOWORLD17_SIZE);
		pr_warn("size is not equal to HELLOWORLD17_SIZE\n");

		return size;
	}

	return HELLOWORLD17_SIZE;
}

static bool HelloWorld17_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld17  *topic = (HelloWorld17  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld17_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld17_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld17 *topic = (HelloWorld17 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld17_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld17 *HelloWorld17_create(void)
{
	HelloWorld17 *sample;
	uint32_t size = sizeof(struct HelloWorld17);

	sample = (HelloWorld17 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld17_delete(HelloWorld17 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld18
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld18_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld18_init(HelloWorld18 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld18_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld18 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld18_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld18 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld18_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld18_topic_max_size(0) + 4u);

	if (size != HELLOWORLD18_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD18_SIZE:%d\n", size, HELLOWORLD18_SIZE);
		pr_warn("size is not equal to HELLOWORLD18_SIZE\n");

		return size;
	}

	return HELLOWORLD18_SIZE;
}

static bool HelloWorld18_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld18  *topic = (HelloWorld18  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld18_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld18_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld18 *topic = (HelloWorld18 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld18_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld18 *HelloWorld18_create(void)
{
	HelloWorld18 *sample;
	uint32_t size = sizeof(struct HelloWorld18);

	sample = (HelloWorld18 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld18_delete(HelloWorld18 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld19
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld19_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld19_init(HelloWorld19 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld19_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld19 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld19_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld19 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld19_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld19_topic_max_size(0) + 4u);

	if (size != HELLOWORLD19_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD19_SIZE:%d\n", size, HELLOWORLD19_SIZE);
		pr_warn("size is not equal to HELLOWORLD19_SIZE\n");

		return size;
	}

	return HELLOWORLD19_SIZE;
}

static bool HelloWorld19_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld19  *topic = (HelloWorld19  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld19_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld19_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld19 *topic = (HelloWorld19 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld19_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld19 *HelloWorld19_create(void)
{
	HelloWorld19 *sample;
	uint32_t size = sizeof(struct HelloWorld19);

	sample = (HelloWorld19 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld19_delete(HelloWorld19 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld20
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld20_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld20_init(HelloWorld20 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld20_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld20 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld20_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld20 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld20_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld20_topic_max_size(0) + 4u);

	if (size != HELLOWORLD20_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD20_SIZE:%d\n", size, HELLOWORLD20_SIZE);
		pr_warn("size is not equal to HELLOWORLD20_SIZE\n");

		return size;
	}

	return HELLOWORLD20_SIZE;
}

static bool HelloWorld20_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld20  *topic = (HelloWorld20  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld20_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld20_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld20 *topic = (HelloWorld20 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld20_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld20 *HelloWorld20_create(void)
{
	HelloWorld20 *sample;
	uint32_t size = sizeof(struct HelloWorld20);

	sample = (HelloWorld20 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld20_delete(HelloWorld20 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld21
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld21_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld21_init(HelloWorld21 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld21_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld21 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld21_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld21 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld21_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld21_topic_max_size(0) + 4u);

	if (size != HELLOWORLD21_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD21_SIZE:%d\n", size, HELLOWORLD21_SIZE);
		pr_warn("size is not equal to HELLOWORLD21_SIZE\n");

		return size;
	}

	return HELLOWORLD21_SIZE;
}

static bool HelloWorld21_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld21  *topic = (HelloWorld21  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld21_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld21_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld21 *topic = (HelloWorld21 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld21_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld21 *HelloWorld21_create(void)
{
	HelloWorld21 *sample;
	uint32_t size = sizeof(struct HelloWorld21);

	sample = (HelloWorld21 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld21_delete(HelloWorld21 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld22
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld22_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld22_init(HelloWorld22 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld22_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld22 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld22_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld22 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld22_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld22_topic_max_size(0) + 4u);

	if (size != HELLOWORLD22_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD22_SIZE:%d\n", size, HELLOWORLD22_SIZE);
		pr_warn("size is not equal to HELLOWORLD22_SIZE\n");

		return size;
	}

	return HELLOWORLD22_SIZE;
}

static bool HelloWorld22_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld22  *topic = (HelloWorld22  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld22_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld22_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld22 *topic = (HelloWorld22 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld22_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld22 *HelloWorld22_create(void)
{
	HelloWorld22 *sample;
	uint32_t size = sizeof(struct HelloWorld22);

	sample = (HelloWorld22 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld22_delete(HelloWorld22 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld23
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld23_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld23_init(HelloWorld23 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld23_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld23 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld23_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld23 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld23_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld23_topic_max_size(0) + 4u);

	if (size != HELLOWORLD23_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD23_SIZE:%d\n", size, HELLOWORLD23_SIZE);
		pr_warn("size is not equal to HELLOWORLD23_SIZE\n");

		return size;
	}

	return HELLOWORLD23_SIZE;
}

static bool HelloWorld23_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld23  *topic = (HelloWorld23  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld23_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld23_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld23 *topic = (HelloWorld23 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld23_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld23 *HelloWorld23_create(void)
{
	HelloWorld23 *sample;
	uint32_t size = sizeof(struct HelloWorld23);

	sample = (HelloWorld23 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld23_delete(HelloWorld23 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld24
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld24_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld24_init(HelloWorld24 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld24_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld24 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld24_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld24 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld24_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld24_topic_max_size(0) + 4u);

	if (size != HELLOWORLD24_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD24_SIZE:%d\n", size, HELLOWORLD24_SIZE);
		pr_warn("size is not equal to HELLOWORLD24_SIZE\n");

		return size;
	}

	return HELLOWORLD24_SIZE;
}

static bool HelloWorld24_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld24  *topic = (HelloWorld24  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld24_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld24_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld24 *topic = (HelloWorld24 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld24_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld24 *HelloWorld24_create(void)
{
	HelloWorld24 *sample;
	uint32_t size = sizeof(struct HelloWorld24);

	sample = (HelloWorld24 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld24_delete(HelloWorld24 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld25
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld25_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld25_init(HelloWorld25 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld25_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld25 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld25_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld25 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld25_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld25_topic_max_size(0) + 4u);

	if (size != HELLOWORLD25_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD25_SIZE:%d\n", size, HELLOWORLD25_SIZE);
		pr_warn("size is not equal to HELLOWORLD25_SIZE\n");

		return size;
	}

	return HELLOWORLD25_SIZE;
}

static bool HelloWorld25_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld25  *topic = (HelloWorld25  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld25_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld25_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld25 *topic = (HelloWorld25 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld25_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld25 *HelloWorld25_create(void)
{
	HelloWorld25 *sample;
	uint32_t size = sizeof(struct HelloWorld25);

	sample = (HelloWorld25 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld25_delete(HelloWorld25 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld26
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld26_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld26_init(HelloWorld26 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld26_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld26 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld26_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld26 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld26_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld26_topic_max_size(0) + 4u);

	if (size != HELLOWORLD26_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD26_SIZE:%d\n", size, HELLOWORLD26_SIZE);
		pr_warn("size is not equal to HELLOWORLD26_SIZE\n");

		return size;
	}

	return HELLOWORLD26_SIZE;
}

static bool HelloWorld26_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld26  *topic = (HelloWorld26  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld26_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld26_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld26 *topic = (HelloWorld26 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld26_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld26 *HelloWorld26_create(void)
{
	HelloWorld26 *sample;
	uint32_t size = sizeof(struct HelloWorld26);

	sample = (HelloWorld26 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld26_delete(HelloWorld26 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld27
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld27_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld27_init(HelloWorld27 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld27_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld27 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld27_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld27 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld27_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld27_topic_max_size(0) + 4u);

	if (size != HELLOWORLD27_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD27_SIZE:%d\n", size, HELLOWORLD27_SIZE);
		pr_warn("size is not equal to HELLOWORLD27_SIZE\n");

		return size;
	}

	return HELLOWORLD27_SIZE;
}

static bool HelloWorld27_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld27  *topic = (HelloWorld27  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld27_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld27_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld27 *topic = (HelloWorld27 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld27_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld27 *HelloWorld27_create(void)
{
	HelloWorld27 *sample;
	uint32_t size = sizeof(struct HelloWorld27);

	sample = (HelloWorld27 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld27_delete(HelloWorld27 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld28
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld28_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld28_init(HelloWorld28 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld28_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld28 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld28_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld28 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld28_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld28_topic_max_size(0) + 4u);

	if (size != HELLOWORLD28_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD28_SIZE:%d\n", size, HELLOWORLD28_SIZE);
		pr_warn("size is not equal to HELLOWORLD28_SIZE\n");

		return size;
	}

	return HELLOWORLD28_SIZE;
}

static bool HelloWorld28_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld28  *topic = (HelloWorld28  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld28_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld28_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld28 *topic = (HelloWorld28 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld28_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld28 *HelloWorld28_create(void)
{
	HelloWorld28 *sample;
	uint32_t size = sizeof(struct HelloWorld28);

	sample = (HelloWorld28 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld28_delete(HelloWorld28 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld29
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld29_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld29_init(HelloWorld29 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld29_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld29 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld29_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld29 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld29_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld29_topic_max_size(0) + 4u);

	if (size != HELLOWORLD29_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD29_SIZE:%d\n", size, HELLOWORLD29_SIZE);
		pr_warn("size is not equal to HELLOWORLD29_SIZE\n");

		return size;
	}

	return HELLOWORLD29_SIZE;
}

static bool HelloWorld29_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld29  *topic = (HelloWorld29  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld29_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld29_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld29 *topic = (HelloWorld29 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld29_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld29 *HelloWorld29_create(void)
{
	HelloWorld29 *sample;
	uint32_t size = sizeof(struct HelloWorld29);

	sample = (HelloWorld29 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld29_delete(HelloWorld29 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld30
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld30_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld30_init(HelloWorld30 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld30_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld30 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld30_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld30 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld30_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld30_topic_max_size(0) + 4u);

	if (size != HELLOWORLD30_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD30_SIZE:%d\n", size, HELLOWORLD30_SIZE);
		pr_warn("size is not equal to HELLOWORLD30_SIZE\n");

		return size;
	}

	return HELLOWORLD30_SIZE;
}

static bool HelloWorld30_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld30  *topic = (HelloWorld30  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld30_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld30_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld30 *topic = (HelloWorld30 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld30_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld30 *HelloWorld30_create(void)
{
	HelloWorld30 *sample;
	uint32_t size = sizeof(struct HelloWorld30);

	sample = (HelloWorld30 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld30_delete(HelloWorld30 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld31
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld31_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld31_init(HelloWorld31 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld31_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld31 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld31_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld31 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld31_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld31_topic_max_size(0) + 4u);

	if (size != HELLOWORLD31_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD31_SIZE:%d\n", size, HELLOWORLD31_SIZE);
		pr_warn("size is not equal to HELLOWORLD31_SIZE\n");

		return size;
	}

	return HELLOWORLD31_SIZE;
}

static bool HelloWorld31_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld31  *topic = (HelloWorld31  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld31_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld31_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld31 *topic = (HelloWorld31 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld31_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld31 *HelloWorld31_create(void)
{
	HelloWorld31 *sample;
	uint32_t size = sizeof(struct HelloWorld31);

	sample = (HelloWorld31 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld31_delete(HelloWorld31 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld32
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld32_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld32_init(HelloWorld32 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld32_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld32 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld32_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld32 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld32_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld32_topic_max_size(0) + 4u);

	if (size != HELLOWORLD32_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD32_SIZE:%d\n", size, HELLOWORLD32_SIZE);
		pr_warn("size is not equal to HELLOWORLD32_SIZE\n");

		return size;
	}

	return HELLOWORLD32_SIZE;
}

static bool HelloWorld32_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld32  *topic = (HelloWorld32  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld32_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld32_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld32 *topic = (HelloWorld32 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld32_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld32 *HelloWorld32_create(void)
{
	HelloWorld32 *sample;
	uint32_t size = sizeof(struct HelloWorld32);

	sample = (HelloWorld32 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld32_delete(HelloWorld32 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld33
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld33_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld33_init(HelloWorld33 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld33_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld33 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld33_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld33 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld33_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld33_topic_max_size(0) + 4u);

	if (size != HELLOWORLD33_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD33_SIZE:%d\n", size, HELLOWORLD33_SIZE);
		pr_warn("size is not equal to HELLOWORLD33_SIZE\n");

		return size;
	}

	return HELLOWORLD33_SIZE;
}

static bool HelloWorld33_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld33  *topic = (HelloWorld33  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld33_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld33_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld33 *topic = (HelloWorld33 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld33_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld33 *HelloWorld33_create(void)
{
	HelloWorld33 *sample;
	uint32_t size = sizeof(struct HelloWorld33);

	sample = (HelloWorld33 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld33_delete(HelloWorld33 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld34
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld34_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld34_init(HelloWorld34 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld34_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld34 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld34_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld34 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld34_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld34_topic_max_size(0) + 4u);

	if (size != HELLOWORLD34_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD34_SIZE:%d\n", size, HELLOWORLD34_SIZE);
		pr_warn("size is not equal to HELLOWORLD34_SIZE\n");

		return size;
	}

	return HELLOWORLD34_SIZE;
}

static bool HelloWorld34_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld34  *topic = (HelloWorld34  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld34_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld34_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld34 *topic = (HelloWorld34 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld34_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld34 *HelloWorld34_create(void)
{
	HelloWorld34 *sample;
	uint32_t size = sizeof(struct HelloWorld34);

	sample = (HelloWorld34 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld34_delete(HelloWorld34 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld35
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld35_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld35_init(HelloWorld35 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld35_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld35 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld35_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld35 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld35_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld35_topic_max_size(0) + 4u);

	if (size != HELLOWORLD35_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD35_SIZE:%d\n", size, HELLOWORLD35_SIZE);
		pr_warn("size is not equal to HELLOWORLD35_SIZE\n");

		return size;
	}

	return HELLOWORLD35_SIZE;
}

static bool HelloWorld35_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld35  *topic = (HelloWorld35  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld35_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld35_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld35 *topic = (HelloWorld35 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld35_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld35 *HelloWorld35_create(void)
{
	HelloWorld35 *sample;
	uint32_t size = sizeof(struct HelloWorld35);

	sample = (HelloWorld35 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld35_delete(HelloWorld35 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld36
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld36_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld36_init(HelloWorld36 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld36_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld36 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld36_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld36 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld36_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld36_topic_max_size(0) + 4u);

	if (size != HELLOWORLD36_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD36_SIZE:%d\n", size, HELLOWORLD36_SIZE);
		pr_warn("size is not equal to HELLOWORLD36_SIZE\n");

		return size;
	}

	return HELLOWORLD36_SIZE;
}

static bool HelloWorld36_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld36  *topic = (HelloWorld36  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld36_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld36_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld36 *topic = (HelloWorld36 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld36_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld36 *HelloWorld36_create(void)
{
	HelloWorld36 *sample;
	uint32_t size = sizeof(struct HelloWorld36);

	sample = (HelloWorld36 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld36_delete(HelloWorld36 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld37
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld37_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld37_init(HelloWorld37 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld37_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld37 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld37_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld37 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld37_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld37_topic_max_size(0) + 4u);

	if (size != HELLOWORLD37_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD37_SIZE:%d\n", size, HELLOWORLD37_SIZE);
		pr_warn("size is not equal to HELLOWORLD37_SIZE\n");

		return size;
	}

	return HELLOWORLD37_SIZE;
}

static bool HelloWorld37_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld37  *topic = (HelloWorld37  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld37_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld37_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld37 *topic = (HelloWorld37 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld37_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld37 *HelloWorld37_create(void)
{
	HelloWorld37 *sample;
	uint32_t size = sizeof(struct HelloWorld37);

	sample = (HelloWorld37 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld37_delete(HelloWorld37 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld38
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld38_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld38_init(HelloWorld38 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld38_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld38 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld38_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld38 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld38_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld38_topic_max_size(0) + 4u);

	if (size != HELLOWORLD38_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD38_SIZE:%d\n", size, HELLOWORLD38_SIZE);
		pr_warn("size is not equal to HELLOWORLD38_SIZE\n");

		return size;
	}

	return HELLOWORLD38_SIZE;
}

static bool HelloWorld38_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld38  *topic = (HelloWorld38  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld38_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld38_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld38 *topic = (HelloWorld38 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld38_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld38 *HelloWorld38_create(void)
{
	HelloWorld38 *sample;
	uint32_t size = sizeof(struct HelloWorld38);

	sample = (HelloWorld38 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld38_delete(HelloWorld38 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld39
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld39_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld39_init(HelloWorld39 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld39_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld39 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld39_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld39 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld39_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld39_topic_max_size(0) + 4u);

	if (size != HELLOWORLD39_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD39_SIZE:%d\n", size, HELLOWORLD39_SIZE);
		pr_warn("size is not equal to HELLOWORLD39_SIZE\n");

		return size;
	}

	return HELLOWORLD39_SIZE;
}

static bool HelloWorld39_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld39  *topic = (HelloWorld39  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld39_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld39_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld39 *topic = (HelloWorld39 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld39_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld39 *HelloWorld39_create(void)
{
	HelloWorld39 *sample;
	uint32_t size = sizeof(struct HelloWorld39);

	sample = (HelloWorld39 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld39_delete(HelloWorld39 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld40
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld40_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld40_init(HelloWorld40 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld40_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld40 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld40_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld40 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld40_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld40_topic_max_size(0) + 4u);

	if (size != HELLOWORLD40_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD40_SIZE:%d\n", size, HELLOWORLD40_SIZE);
		pr_warn("size is not equal to HELLOWORLD40_SIZE\n");

		return size;
	}

	return HELLOWORLD40_SIZE;
}

static bool HelloWorld40_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld40  *topic = (HelloWorld40  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld40_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld40_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld40 *topic = (HelloWorld40 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld40_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld40 *HelloWorld40_create(void)
{
	HelloWorld40 *sample;
	uint32_t size = sizeof(struct HelloWorld40);

	sample = (HelloWorld40 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld40_delete(HelloWorld40 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld41
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld41_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld41_init(HelloWorld41 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld41_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld41 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld41_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld41 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld41_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld41_topic_max_size(0) + 4u);

	if (size != HELLOWORLD41_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD41_SIZE:%d\n", size, HELLOWORLD41_SIZE);
		pr_warn("size is not equal to HELLOWORLD41_SIZE\n");

		return size;
	}

	return HELLOWORLD41_SIZE;
}

static bool HelloWorld41_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld41  *topic = (HelloWorld41  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld41_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld41_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld41 *topic = (HelloWorld41 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld41_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld41 *HelloWorld41_create(void)
{
	HelloWorld41 *sample;
	uint32_t size = sizeof(struct HelloWorld41);

	sample = (HelloWorld41 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld41_delete(HelloWorld41 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld42
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld42_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld42_init(HelloWorld42 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld42_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld42 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld42_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld42 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld42_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld42_topic_max_size(0) + 4u);

	if (size != HELLOWORLD42_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD42_SIZE:%d\n", size, HELLOWORLD42_SIZE);
		pr_warn("size is not equal to HELLOWORLD42_SIZE\n");

		return size;
	}

	return HELLOWORLD42_SIZE;
}

static bool HelloWorld42_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld42  *topic = (HelloWorld42  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld42_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld42_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld42 *topic = (HelloWorld42 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld42_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld42 *HelloWorld42_create(void)
{
	HelloWorld42 *sample;
	uint32_t size = sizeof(struct HelloWorld42);

	sample = (HelloWorld42 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld42_delete(HelloWorld42 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld43
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld43_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld43_init(HelloWorld43 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld43_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld43 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld43_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld43 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld43_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld43_topic_max_size(0) + 4u);

	if (size != HELLOWORLD43_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD43_SIZE:%d\n", size, HELLOWORLD43_SIZE);
		pr_warn("size is not equal to HELLOWORLD43_SIZE\n");

		return size;
	}

	return HELLOWORLD43_SIZE;
}

static bool HelloWorld43_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld43  *topic = (HelloWorld43  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld43_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld43_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld43 *topic = (HelloWorld43 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld43_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld43 *HelloWorld43_create(void)
{
	HelloWorld43 *sample;
	uint32_t size = sizeof(struct HelloWorld43);

	sample = (HelloWorld43 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld43_delete(HelloWorld43 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld44
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld44_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld44_init(HelloWorld44 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld44_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld44 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld44_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld44 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld44_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld44_topic_max_size(0) + 4u);

	if (size != HELLOWORLD44_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD44_SIZE:%d\n", size, HELLOWORLD44_SIZE);
		pr_warn("size is not equal to HELLOWORLD44_SIZE\n");

		return size;
	}

	return HELLOWORLD44_SIZE;
}

static bool HelloWorld44_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld44  *topic = (HelloWorld44  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld44_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld44_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld44 *topic = (HelloWorld44 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld44_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld44 *HelloWorld44_create(void)
{
	HelloWorld44 *sample;
	uint32_t size = sizeof(struct HelloWorld44);

	sample = (HelloWorld44 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld44_delete(HelloWorld44 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld45
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld45_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld45_init(HelloWorld45 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld45_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld45 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld45_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld45 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld45_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld45_topic_max_size(0) + 4u);

	if (size != HELLOWORLD45_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD45_SIZE:%d\n", size, HELLOWORLD45_SIZE);
		pr_warn("size is not equal to HELLOWORLD45_SIZE\n");

		return size;
	}

	return HELLOWORLD45_SIZE;
}

static bool HelloWorld45_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld45  *topic = (HelloWorld45  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld45_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld45_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld45 *topic = (HelloWorld45 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld45_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld45 *HelloWorld45_create(void)
{
	HelloWorld45 *sample;
	uint32_t size = sizeof(struct HelloWorld45);

	sample = (HelloWorld45 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld45_delete(HelloWorld45 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld46
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld46_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld46_init(HelloWorld46 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld46_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld46 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld46_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld46 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld46_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld46_topic_max_size(0) + 4u);

	if (size != HELLOWORLD46_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD46_SIZE:%d\n", size, HELLOWORLD46_SIZE);
		pr_warn("size is not equal to HELLOWORLD46_SIZE\n");

		return size;
	}

	return HELLOWORLD46_SIZE;
}

static bool HelloWorld46_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld46  *topic = (HelloWorld46  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld46_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld46_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld46 *topic = (HelloWorld46 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld46_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld46 *HelloWorld46_create(void)
{
	HelloWorld46 *sample;
	uint32_t size = sizeof(struct HelloWorld46);

	sample = (HelloWorld46 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld46_delete(HelloWorld46 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld47
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld47_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld47_init(HelloWorld47 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld47_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld47 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld47_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld47 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld47_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld47_topic_max_size(0) + 4u);

	if (size != HELLOWORLD47_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD47_SIZE:%d\n", size, HELLOWORLD47_SIZE);
		pr_warn("size is not equal to HELLOWORLD47_SIZE\n");

		return size;
	}

	return HELLOWORLD47_SIZE;
}

static bool HelloWorld47_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld47  *topic = (HelloWorld47  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld47_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld47_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld47 *topic = (HelloWorld47 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld47_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld47 *HelloWorld47_create(void)
{
	HelloWorld47 *sample;
	uint32_t size = sizeof(struct HelloWorld47);

	sample = (HelloWorld47 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld47_delete(HelloWorld47 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld48
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld48_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld48_init(HelloWorld48 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld48_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld48 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld48_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld48 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld48_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld48_topic_max_size(0) + 4u);

	if (size != HELLOWORLD48_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD48_SIZE:%d\n", size, HELLOWORLD48_SIZE);
		pr_warn("size is not equal to HELLOWORLD48_SIZE\n");

		return size;
	}

	return HELLOWORLD48_SIZE;
}

static bool HelloWorld48_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld48  *topic = (HelloWorld48  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld48_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld48_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld48 *topic = (HelloWorld48 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld48_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld48 *HelloWorld48_create(void)
{
	HelloWorld48 *sample;
	uint32_t size = sizeof(struct HelloWorld48);

	sample = (HelloWorld48 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld48_delete(HelloWorld48 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld49
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld49_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld49_init(HelloWorld49 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld49_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld49 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld49_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld49 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld49_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld49_topic_max_size(0) + 4u);

	if (size != HELLOWORLD49_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD49_SIZE:%d\n", size, HELLOWORLD49_SIZE);
		pr_warn("size is not equal to HELLOWORLD49_SIZE\n");

		return size;
	}

	return HELLOWORLD49_SIZE;
}

static bool HelloWorld49_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld49  *topic = (HelloWorld49  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld49_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld49_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld49 *topic = (HelloWorld49 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld49_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld49 *HelloWorld49_create(void)
{
	HelloWorld49 *sample;
	uint32_t size = sizeof(struct HelloWorld49);

	sample = (HelloWorld49 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld49_delete(HelloWorld49 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld50
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld50_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld50_init(HelloWorld50 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld50_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld50 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld50_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld50 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld50_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld50_topic_max_size(0) + 4u);

	if (size != HELLOWORLD50_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD50_SIZE:%d\n", size, HELLOWORLD50_SIZE);
		pr_warn("size is not equal to HELLOWORLD50_SIZE\n");

		return size;
	}

	return HELLOWORLD50_SIZE;
}

static bool HelloWorld50_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld50  *topic = (HelloWorld50  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld50_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld50_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld50 *topic = (HelloWorld50 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld50_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld50 *HelloWorld50_create(void)
{
	HelloWorld50 *sample;
	uint32_t size = sizeof(struct HelloWorld50);

	sample = (HelloWorld50 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld50_delete(HelloWorld50 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld51
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld51_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld51_init(HelloWorld51 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld51_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld51 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld51_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld51 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld51_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld51_topic_max_size(0) + 4u);

	if (size != HELLOWORLD51_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD51_SIZE:%d\n", size, HELLOWORLD51_SIZE);
		pr_warn("size is not equal to HELLOWORLD51_SIZE\n");

		return size;
	}

	return HELLOWORLD51_SIZE;
}

static bool HelloWorld51_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld51  *topic = (HelloWorld51  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld51_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld51_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld51 *topic = (HelloWorld51 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld51_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld51 *HelloWorld51_create(void)
{
	HelloWorld51 *sample;
	uint32_t size = sizeof(struct HelloWorld51);

	sample = (HelloWorld51 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld51_delete(HelloWorld51 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld52
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld52_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld52_init(HelloWorld52 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld52_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld52 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld52_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld52 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld52_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld52_topic_max_size(0) + 4u);

	if (size != HELLOWORLD52_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD52_SIZE:%d\n", size, HELLOWORLD52_SIZE);
		pr_warn("size is not equal to HELLOWORLD52_SIZE\n");

		return size;
	}

	return HELLOWORLD52_SIZE;
}

static bool HelloWorld52_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld52  *topic = (HelloWorld52  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld52_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld52_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld52 *topic = (HelloWorld52 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld52_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld52 *HelloWorld52_create(void)
{
	HelloWorld52 *sample;
	uint32_t size = sizeof(struct HelloWorld52);

	sample = (HelloWorld52 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld52_delete(HelloWorld52 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld53
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld53_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld53_init(HelloWorld53 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld53_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld53 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld53_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld53 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld53_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld53_topic_max_size(0) + 4u);

	if (size != HELLOWORLD53_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD53_SIZE:%d\n", size, HELLOWORLD53_SIZE);
		pr_warn("size is not equal to HELLOWORLD53_SIZE\n");

		return size;
	}

	return HELLOWORLD53_SIZE;
}

static bool HelloWorld53_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld53  *topic = (HelloWorld53  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld53_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld53_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld53 *topic = (HelloWorld53 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld53_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld53 *HelloWorld53_create(void)
{
	HelloWorld53 *sample;
	uint32_t size = sizeof(struct HelloWorld53);

	sample = (HelloWorld53 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld53_delete(HelloWorld53 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld54
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld54_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld54_init(HelloWorld54 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld54_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld54 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld54_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld54 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld54_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld54_topic_max_size(0) + 4u);

	if (size != HELLOWORLD54_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD54_SIZE:%d\n", size, HELLOWORLD54_SIZE);
		pr_warn("size is not equal to HELLOWORLD54_SIZE\n");

		return size;
	}

	return HELLOWORLD54_SIZE;
}

static bool HelloWorld54_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld54  *topic = (HelloWorld54  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld54_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld54_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld54 *topic = (HelloWorld54 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld54_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld54 *HelloWorld54_create(void)
{
	HelloWorld54 *sample;
	uint32_t size = sizeof(struct HelloWorld54);

	sample = (HelloWorld54 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld54_delete(HelloWorld54 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld55
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld55_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld55_init(HelloWorld55 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld55_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld55 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld55_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld55 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld55_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld55_topic_max_size(0) + 4u);

	if (size != HELLOWORLD55_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD55_SIZE:%d\n", size, HELLOWORLD55_SIZE);
		pr_warn("size is not equal to HELLOWORLD55_SIZE\n");

		return size;
	}

	return HELLOWORLD55_SIZE;
}

static bool HelloWorld55_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld55  *topic = (HelloWorld55  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld55_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld55_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld55 *topic = (HelloWorld55 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld55_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld55 *HelloWorld55_create(void)
{
	HelloWorld55 *sample;
	uint32_t size = sizeof(struct HelloWorld55);

	sample = (HelloWorld55 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld55_delete(HelloWorld55 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld56
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld56_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld56_init(HelloWorld56 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld56_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld56 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld56_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld56 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld56_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld56_topic_max_size(0) + 4u);

	if (size != HELLOWORLD56_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD56_SIZE:%d\n", size, HELLOWORLD56_SIZE);
		pr_warn("size is not equal to HELLOWORLD56_SIZE\n");

		return size;
	}

	return HELLOWORLD56_SIZE;
}

static bool HelloWorld56_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld56  *topic = (HelloWorld56  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld56_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld56_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld56 *topic = (HelloWorld56 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld56_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld56 *HelloWorld56_create(void)
{
	HelloWorld56 *sample;
	uint32_t size = sizeof(struct HelloWorld56);

	sample = (HelloWorld56 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld56_delete(HelloWorld56 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld57
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld57_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld57_init(HelloWorld57 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld57_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld57 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld57_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld57 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld57_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld57_topic_max_size(0) + 4u);

	if (size != HELLOWORLD57_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD57_SIZE:%d\n", size, HELLOWORLD57_SIZE);
		pr_warn("size is not equal to HELLOWORLD57_SIZE\n");

		return size;
	}

	return HELLOWORLD57_SIZE;
}

static bool HelloWorld57_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld57  *topic = (HelloWorld57  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld57_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld57_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld57 *topic = (HelloWorld57 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld57_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld57 *HelloWorld57_create(void)
{
	HelloWorld57 *sample;
	uint32_t size = sizeof(struct HelloWorld57);

	sample = (HelloWorld57 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld57_delete(HelloWorld57 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld58
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld58_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld58_init(HelloWorld58 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld58_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld58 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld58_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld58 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld58_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld58_topic_max_size(0) + 4u);

	if (size != HELLOWORLD58_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD58_SIZE:%d\n", size, HELLOWORLD58_SIZE);
		pr_warn("size is not equal to HELLOWORLD58_SIZE\n");

		return size;
	}

	return HELLOWORLD58_SIZE;
}

static bool HelloWorld58_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld58  *topic = (HelloWorld58  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld58_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld58_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld58 *topic = (HelloWorld58 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld58_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld58 *HelloWorld58_create(void)
{
	HelloWorld58 *sample;
	uint32_t size = sizeof(struct HelloWorld58);

	sample = (HelloWorld58 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld58_delete(HelloWorld58 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld59
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld59_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld59_init(HelloWorld59 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld59_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld59 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld59_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld59 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld59_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld59_topic_max_size(0) + 4u);

	if (size != HELLOWORLD59_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD59_SIZE:%d\n", size, HELLOWORLD59_SIZE);
		pr_warn("size is not equal to HELLOWORLD59_SIZE\n");

		return size;
	}

	return HELLOWORLD59_SIZE;
}

static bool HelloWorld59_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld59  *topic = (HelloWorld59  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld59_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld59_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld59 *topic = (HelloWorld59 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld59_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld59 *HelloWorld59_create(void)
{
	HelloWorld59 *sample;
	uint32_t size = sizeof(struct HelloWorld59);

	sample = (HelloWorld59 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld59_delete(HelloWorld59 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld60
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld60_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld60_init(HelloWorld60 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld60_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld60 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld60_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld60 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld60_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld60_topic_max_size(0) + 4u);

	if (size != HELLOWORLD60_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD60_SIZE:%d\n", size, HELLOWORLD60_SIZE);
		pr_warn("size is not equal to HELLOWORLD60_SIZE\n");

		return size;
	}

	return HELLOWORLD60_SIZE;
}

static bool HelloWorld60_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld60  *topic = (HelloWorld60  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld60_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld60_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld60 *topic = (HelloWorld60 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld60_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld60 *HelloWorld60_create(void)
{
	HelloWorld60 *sample;
	uint32_t size = sizeof(struct HelloWorld60);

	sample = (HelloWorld60 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld60_delete(HelloWorld60 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld61
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld61_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld61_init(HelloWorld61 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld61_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld61 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld61_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld61 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld61_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld61_topic_max_size(0) + 4u);

	if (size != HELLOWORLD61_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD61_SIZE:%d\n", size, HELLOWORLD61_SIZE);
		pr_warn("size is not equal to HELLOWORLD61_SIZE\n");

		return size;
	}

	return HELLOWORLD61_SIZE;
}

static bool HelloWorld61_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld61  *topic = (HelloWorld61  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld61_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld61_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld61 *topic = (HelloWorld61 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld61_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld61 *HelloWorld61_create(void)
{
	HelloWorld61 *sample;
	uint32_t size = sizeof(struct HelloWorld61);

	sample = (HelloWorld61 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld61_delete(HelloWorld61 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld62
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld62_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld62_init(HelloWorld62 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld62_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld62 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld62_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld62 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld62_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld62_topic_max_size(0) + 4u);

	if (size != HELLOWORLD62_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD62_SIZE:%d\n", size, HELLOWORLD62_SIZE);
		pr_warn("size is not equal to HELLOWORLD62_SIZE\n");

		return size;
	}

	return HELLOWORLD62_SIZE;
}

static bool HelloWorld62_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld62  *topic = (HelloWorld62  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld62_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld62_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld62 *topic = (HelloWorld62 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld62_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld62 *HelloWorld62_create(void)
{
	HelloWorld62 *sample;
	uint32_t size = sizeof(struct HelloWorld62);

	sample = (HelloWorld62 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld62_delete(HelloWorld62 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld63
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld63_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld63_init(HelloWorld63 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld63_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld63 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld63_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld63 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld63_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld63_topic_max_size(0) + 4u);

	if (size != HELLOWORLD63_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD63_SIZE:%d\n", size, HELLOWORLD63_SIZE);
		pr_warn("size is not equal to HELLOWORLD63_SIZE\n");

		return size;
	}

	return HELLOWORLD63_SIZE;
}

static bool HelloWorld63_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld63  *topic = (HelloWorld63  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld63_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld63_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld63 *topic = (HelloWorld63 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld63_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld63 *HelloWorld63_create(void)
{
	HelloWorld63 *sample;
	uint32_t size = sizeof(struct HelloWorld63);

	sample = (HelloWorld63 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld63_delete(HelloWorld63 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld64
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld64_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld64_init(HelloWorld64 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld64_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld64 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld64_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld64 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld64_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld64_topic_max_size(0) + 4u);

	if (size != HELLOWORLD64_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD64_SIZE:%d\n", size, HELLOWORLD64_SIZE);
		pr_warn("size is not equal to HELLOWORLD64_SIZE\n");

		return size;
	}

	return HELLOWORLD64_SIZE;
}

static bool HelloWorld64_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld64  *topic = (HelloWorld64  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld64_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld64_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld64 *topic = (HelloWorld64 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld64_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld64 *HelloWorld64_create(void)
{
	HelloWorld64 *sample;
	uint32_t size = sizeof(struct HelloWorld64);

	sample = (HelloWorld64 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld64_delete(HelloWorld64 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld65
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld65_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld65_init(HelloWorld65 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld65_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld65 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld65_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld65 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld65_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld65_topic_max_size(0) + 4u);

	if (size != HELLOWORLD65_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD65_SIZE:%d\n", size, HELLOWORLD65_SIZE);
		pr_warn("size is not equal to HELLOWORLD65_SIZE\n");

		return size;
	}

	return HELLOWORLD65_SIZE;
}

static bool HelloWorld65_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld65  *topic = (HelloWorld65  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld65_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld65_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld65 *topic = (HelloWorld65 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld65_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld65 *HelloWorld65_create(void)
{
	HelloWorld65 *sample;
	uint32_t size = sizeof(struct HelloWorld65);

	sample = (HelloWorld65 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld65_delete(HelloWorld65 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld66
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld66_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld66_init(HelloWorld66 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld66_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld66 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld66_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld66 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld66_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld66_topic_max_size(0) + 4u);

	if (size != HELLOWORLD66_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD66_SIZE:%d\n", size, HELLOWORLD66_SIZE);
		pr_warn("size is not equal to HELLOWORLD66_SIZE\n");

		return size;
	}

	return HELLOWORLD66_SIZE;
}

static bool HelloWorld66_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld66  *topic = (HelloWorld66  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld66_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld66_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld66 *topic = (HelloWorld66 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld66_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld66 *HelloWorld66_create(void)
{
	HelloWorld66 *sample;
	uint32_t size = sizeof(struct HelloWorld66);

	sample = (HelloWorld66 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld66_delete(HelloWorld66 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld67
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld67_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld67_init(HelloWorld67 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld67_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld67 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld67_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld67 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld67_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld67_topic_max_size(0) + 4u);

	if (size != HELLOWORLD67_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD67_SIZE:%d\n", size, HELLOWORLD67_SIZE);
		pr_warn("size is not equal to HELLOWORLD67_SIZE\n");

		return size;
	}

	return HELLOWORLD67_SIZE;
}

static bool HelloWorld67_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld67  *topic = (HelloWorld67  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld67_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld67_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld67 *topic = (HelloWorld67 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld67_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld67 *HelloWorld67_create(void)
{
	HelloWorld67 *sample;
	uint32_t size = sizeof(struct HelloWorld67);

	sample = (HelloWorld67 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld67_delete(HelloWorld67 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld68
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld68_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld68_init(HelloWorld68 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld68_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld68 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld68_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld68 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld68_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld68_topic_max_size(0) + 4u);

	if (size != HELLOWORLD68_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD68_SIZE:%d\n", size, HELLOWORLD68_SIZE);
		pr_warn("size is not equal to HELLOWORLD68_SIZE\n");

		return size;
	}

	return HELLOWORLD68_SIZE;
}

static bool HelloWorld68_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld68  *topic = (HelloWorld68  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld68_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld68_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld68 *topic = (HelloWorld68 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld68_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld68 *HelloWorld68_create(void)
{
	HelloWorld68 *sample;
	uint32_t size = sizeof(struct HelloWorld68);

	sample = (HelloWorld68 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld68_delete(HelloWorld68 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld69
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld69_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld69_init(HelloWorld69 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld69_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld69 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld69_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld69 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld69_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld69_topic_max_size(0) + 4u);

	if (size != HELLOWORLD69_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD69_SIZE:%d\n", size, HELLOWORLD69_SIZE);
		pr_warn("size is not equal to HELLOWORLD69_SIZE\n");

		return size;
	}

	return HELLOWORLD69_SIZE;
}

static bool HelloWorld69_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld69  *topic = (HelloWorld69  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld69_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld69_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld69 *topic = (HelloWorld69 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld69_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld69 *HelloWorld69_create(void)
{
	HelloWorld69 *sample;
	uint32_t size = sizeof(struct HelloWorld69);

	sample = (HelloWorld69 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld69_delete(HelloWorld69 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld70
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld70_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld70_init(HelloWorld70 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld70_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld70 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld70_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld70 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld70_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld70_topic_max_size(0) + 4u);

	if (size != HELLOWORLD70_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD70_SIZE:%d\n", size, HELLOWORLD70_SIZE);
		pr_warn("size is not equal to HELLOWORLD70_SIZE\n");

		return size;
	}

	return HELLOWORLD70_SIZE;
}

static bool HelloWorld70_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld70  *topic = (HelloWorld70  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld70_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld70_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld70 *topic = (HelloWorld70 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld70_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld70 *HelloWorld70_create(void)
{
	HelloWorld70 *sample;
	uint32_t size = sizeof(struct HelloWorld70);

	sample = (HelloWorld70 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld70_delete(HelloWorld70 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld71
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld71_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld71_init(HelloWorld71 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld71_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld71 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld71_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld71 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld71_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld71_topic_max_size(0) + 4u);

	if (size != HELLOWORLD71_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD71_SIZE:%d\n", size, HELLOWORLD71_SIZE);
		pr_warn("size is not equal to HELLOWORLD71_SIZE\n");

		return size;
	}

	return HELLOWORLD71_SIZE;
}

static bool HelloWorld71_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld71  *topic = (HelloWorld71  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld71_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld71_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld71 *topic = (HelloWorld71 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld71_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld71 *HelloWorld71_create(void)
{
	HelloWorld71 *sample;
	uint32_t size = sizeof(struct HelloWorld71);

	sample = (HelloWorld71 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld71_delete(HelloWorld71 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld72
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld72_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld72_init(HelloWorld72 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld72_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld72 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld72_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld72 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld72_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld72_topic_max_size(0) + 4u);

	if (size != HELLOWORLD72_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD72_SIZE:%d\n", size, HELLOWORLD72_SIZE);
		pr_warn("size is not equal to HELLOWORLD72_SIZE\n");

		return size;
	}

	return HELLOWORLD72_SIZE;
}

static bool HelloWorld72_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld72  *topic = (HelloWorld72  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld72_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld72_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld72 *topic = (HelloWorld72 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld72_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld72 *HelloWorld72_create(void)
{
	HelloWorld72 *sample;
	uint32_t size = sizeof(struct HelloWorld72);

	sample = (HelloWorld72 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld72_delete(HelloWorld72 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld73
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld73_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld73_init(HelloWorld73 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld73_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld73 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld73_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld73 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld73_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld73_topic_max_size(0) + 4u);

	if (size != HELLOWORLD73_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD73_SIZE:%d\n", size, HELLOWORLD73_SIZE);
		pr_warn("size is not equal to HELLOWORLD73_SIZE\n");

		return size;
	}

	return HELLOWORLD73_SIZE;
}

static bool HelloWorld73_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld73  *topic = (HelloWorld73  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld73_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld73_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld73 *topic = (HelloWorld73 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld73_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld73 *HelloWorld73_create(void)
{
	HelloWorld73 *sample;
	uint32_t size = sizeof(struct HelloWorld73);

	sample = (HelloWorld73 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld73_delete(HelloWorld73 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld74
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld74_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld74_init(HelloWorld74 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld74_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld74 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld74_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld74 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld74_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld74_topic_max_size(0) + 4u);

	if (size != HELLOWORLD74_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD74_SIZE:%d\n", size, HELLOWORLD74_SIZE);
		pr_warn("size is not equal to HELLOWORLD74_SIZE\n");

		return size;
	}

	return HELLOWORLD74_SIZE;
}

static bool HelloWorld74_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld74  *topic = (HelloWorld74  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld74_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld74_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld74 *topic = (HelloWorld74 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld74_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld74 *HelloWorld74_create(void)
{
	HelloWorld74 *sample;
	uint32_t size = sizeof(struct HelloWorld74);

	sample = (HelloWorld74 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld74_delete(HelloWorld74 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld75
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld75_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld75_init(HelloWorld75 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld75_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld75 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld75_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld75 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld75_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld75_topic_max_size(0) + 4u);

	if (size != HELLOWORLD75_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD75_SIZE:%d\n", size, HELLOWORLD75_SIZE);
		pr_warn("size is not equal to HELLOWORLD75_SIZE\n");

		return size;
	}

	return HELLOWORLD75_SIZE;
}

static bool HelloWorld75_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld75  *topic = (HelloWorld75  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld75_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld75_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld75 *topic = (HelloWorld75 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld75_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld75 *HelloWorld75_create(void)
{
	HelloWorld75 *sample;
	uint32_t size = sizeof(struct HelloWorld75);

	sample = (HelloWorld75 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld75_delete(HelloWorld75 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld76
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld76_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld76_init(HelloWorld76 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld76_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld76 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld76_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld76 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld76_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld76_topic_max_size(0) + 4u);

	if (size != HELLOWORLD76_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD76_SIZE:%d\n", size, HELLOWORLD76_SIZE);
		pr_warn("size is not equal to HELLOWORLD76_SIZE\n");

		return size;
	}

	return HELLOWORLD76_SIZE;
}

static bool HelloWorld76_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld76  *topic = (HelloWorld76  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld76_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld76_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld76 *topic = (HelloWorld76 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld76_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld76 *HelloWorld76_create(void)
{
	HelloWorld76 *sample;
	uint32_t size = sizeof(struct HelloWorld76);

	sample = (HelloWorld76 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld76_delete(HelloWorld76 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld77
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld77_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld77_init(HelloWorld77 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld77_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld77 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld77_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld77 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld77_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld77_topic_max_size(0) + 4u);

	if (size != HELLOWORLD77_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD77_SIZE:%d\n", size, HELLOWORLD77_SIZE);
		pr_warn("size is not equal to HELLOWORLD77_SIZE\n");

		return size;
	}

	return HELLOWORLD77_SIZE;
}

static bool HelloWorld77_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld77  *topic = (HelloWorld77  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld77_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld77_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld77 *topic = (HelloWorld77 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld77_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld77 *HelloWorld77_create(void)
{
	HelloWorld77 *sample;
	uint32_t size = sizeof(struct HelloWorld77);

	sample = (HelloWorld77 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld77_delete(HelloWorld77 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld78
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld78_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld78_init(HelloWorld78 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld78_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld78 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld78_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld78 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld78_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld78_topic_max_size(0) + 4u);

	if (size != HELLOWORLD78_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD78_SIZE:%d\n", size, HELLOWORLD78_SIZE);
		pr_warn("size is not equal to HELLOWORLD78_SIZE\n");

		return size;
	}

	return HELLOWORLD78_SIZE;
}

static bool HelloWorld78_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld78  *topic = (HelloWorld78  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld78_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld78_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld78 *topic = (HelloWorld78 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld78_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld78 *HelloWorld78_create(void)
{
	HelloWorld78 *sample;
	uint32_t size = sizeof(struct HelloWorld78);

	sample = (HelloWorld78 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld78_delete(HelloWorld78 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld79
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld79_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld79_init(HelloWorld79 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld79_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld79 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld79_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld79 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld79_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld79_topic_max_size(0) + 4u);

	if (size != HELLOWORLD79_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD79_SIZE:%d\n", size, HELLOWORLD79_SIZE);
		pr_warn("size is not equal to HELLOWORLD79_SIZE\n");

		return size;
	}

	return HELLOWORLD79_SIZE;
}

static bool HelloWorld79_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld79  *topic = (HelloWorld79  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld79_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld79_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld79 *topic = (HelloWorld79 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld79_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld79 *HelloWorld79_create(void)
{
	HelloWorld79 *sample;
	uint32_t size = sizeof(struct HelloWorld79);

	sample = (HelloWorld79 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld79_delete(HelloWorld79 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld80
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld80_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld80_init(HelloWorld80 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld80_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld80 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld80_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld80 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld80_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld80_topic_max_size(0) + 4u);

	if (size != HELLOWORLD80_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD80_SIZE:%d\n", size, HELLOWORLD80_SIZE);
		pr_warn("size is not equal to HELLOWORLD80_SIZE\n");

		return size;
	}

	return HELLOWORLD80_SIZE;
}

static bool HelloWorld80_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld80  *topic = (HelloWorld80  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld80_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld80_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld80 *topic = (HelloWorld80 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld80_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld80 *HelloWorld80_create(void)
{
	HelloWorld80 *sample;
	uint32_t size = sizeof(struct HelloWorld80);

	sample = (HelloWorld80 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld80_delete(HelloWorld80 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld81
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld81_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld81_init(HelloWorld81 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld81_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld81 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld81_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld81 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld81_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld81_topic_max_size(0) + 4u);

	if (size != HELLOWORLD81_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD81_SIZE:%d\n", size, HELLOWORLD81_SIZE);
		pr_warn("size is not equal to HELLOWORLD81_SIZE\n");

		return size;
	}

	return HELLOWORLD81_SIZE;
}

static bool HelloWorld81_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld81  *topic = (HelloWorld81  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld81_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld81_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld81 *topic = (HelloWorld81 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld81_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld81 *HelloWorld81_create(void)
{
	HelloWorld81 *sample;
	uint32_t size = sizeof(struct HelloWorld81);

	sample = (HelloWorld81 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld81_delete(HelloWorld81 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld82
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld82_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld82_init(HelloWorld82 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld82_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld82 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld82_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld82 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld82_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld82_topic_max_size(0) + 4u);

	if (size != HELLOWORLD82_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD82_SIZE:%d\n", size, HELLOWORLD82_SIZE);
		pr_warn("size is not equal to HELLOWORLD82_SIZE\n");

		return size;
	}

	return HELLOWORLD82_SIZE;
}

static bool HelloWorld82_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld82  *topic = (HelloWorld82  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld82_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld82_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld82 *topic = (HelloWorld82 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld82_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld82 *HelloWorld82_create(void)
{
	HelloWorld82 *sample;
	uint32_t size = sizeof(struct HelloWorld82);

	sample = (HelloWorld82 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld82_delete(HelloWorld82 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld83
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld83_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld83_init(HelloWorld83 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld83_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld83 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld83_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld83 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld83_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld83_topic_max_size(0) + 4u);

	if (size != HELLOWORLD83_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD83_SIZE:%d\n", size, HELLOWORLD83_SIZE);
		pr_warn("size is not equal to HELLOWORLD83_SIZE\n");

		return size;
	}

	return HELLOWORLD83_SIZE;
}

static bool HelloWorld83_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld83  *topic = (HelloWorld83  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld83_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld83_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld83 *topic = (HelloWorld83 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld83_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld83 *HelloWorld83_create(void)
{
	HelloWorld83 *sample;
	uint32_t size = sizeof(struct HelloWorld83);

	sample = (HelloWorld83 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld83_delete(HelloWorld83 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld84
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld84_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld84_init(HelloWorld84 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld84_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld84 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld84_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld84 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld84_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld84_topic_max_size(0) + 4u);

	if (size != HELLOWORLD84_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD84_SIZE:%d\n", size, HELLOWORLD84_SIZE);
		pr_warn("size is not equal to HELLOWORLD84_SIZE\n");

		return size;
	}

	return HELLOWORLD84_SIZE;
}

static bool HelloWorld84_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld84  *topic = (HelloWorld84  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld84_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld84_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld84 *topic = (HelloWorld84 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld84_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld84 *HelloWorld84_create(void)
{
	HelloWorld84 *sample;
	uint32_t size = sizeof(struct HelloWorld84);

	sample = (HelloWorld84 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld84_delete(HelloWorld84 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld85
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld85_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld85_init(HelloWorld85 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld85_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld85 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld85_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld85 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld85_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld85_topic_max_size(0) + 4u);

	if (size != HELLOWORLD85_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD85_SIZE:%d\n", size, HELLOWORLD85_SIZE);
		pr_warn("size is not equal to HELLOWORLD85_SIZE\n");

		return size;
	}

	return HELLOWORLD85_SIZE;
}

static bool HelloWorld85_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld85  *topic = (HelloWorld85  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld85_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld85_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld85 *topic = (HelloWorld85 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld85_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld85 *HelloWorld85_create(void)
{
	HelloWorld85 *sample;
	uint32_t size = sizeof(struct HelloWorld85);

	sample = (HelloWorld85 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld85_delete(HelloWorld85 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld86
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld86_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld86_init(HelloWorld86 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld86_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld86 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld86_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld86 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld86_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld86_topic_max_size(0) + 4u);

	if (size != HELLOWORLD86_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD86_SIZE:%d\n", size, HELLOWORLD86_SIZE);
		pr_warn("size is not equal to HELLOWORLD86_SIZE\n");

		return size;
	}

	return HELLOWORLD86_SIZE;
}

static bool HelloWorld86_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld86  *topic = (HelloWorld86  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld86_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld86_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld86 *topic = (HelloWorld86 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld86_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld86 *HelloWorld86_create(void)
{
	HelloWorld86 *sample;
	uint32_t size = sizeof(struct HelloWorld86);

	sample = (HelloWorld86 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld86_delete(HelloWorld86 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld87
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld87_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld87_init(HelloWorld87 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld87_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld87 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld87_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld87 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld87_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld87_topic_max_size(0) + 4u);

	if (size != HELLOWORLD87_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD87_SIZE:%d\n", size, HELLOWORLD87_SIZE);
		pr_warn("size is not equal to HELLOWORLD87_SIZE\n");

		return size;
	}

	return HELLOWORLD87_SIZE;
}

static bool HelloWorld87_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld87  *topic = (HelloWorld87  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld87_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld87_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld87 *topic = (HelloWorld87 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld87_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld87 *HelloWorld87_create(void)
{
	HelloWorld87 *sample;
	uint32_t size = sizeof(struct HelloWorld87);

	sample = (HelloWorld87 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld87_delete(HelloWorld87 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld88
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld88_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld88_init(HelloWorld88 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld88_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld88 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld88_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld88 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld88_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld88_topic_max_size(0) + 4u);

	if (size != HELLOWORLD88_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD88_SIZE:%d\n", size, HELLOWORLD88_SIZE);
		pr_warn("size is not equal to HELLOWORLD88_SIZE\n");

		return size;
	}

	return HELLOWORLD88_SIZE;
}

static bool HelloWorld88_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld88  *topic = (HelloWorld88  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld88_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld88_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld88 *topic = (HelloWorld88 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld88_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld88 *HelloWorld88_create(void)
{
	HelloWorld88 *sample;
	uint32_t size = sizeof(struct HelloWorld88);

	sample = (HelloWorld88 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld88_delete(HelloWorld88 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld89
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld89_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld89_init(HelloWorld89 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld89_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld89 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld89_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld89 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld89_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld89_topic_max_size(0) + 4u);

	if (size != HELLOWORLD89_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD89_SIZE:%d\n", size, HELLOWORLD89_SIZE);
		pr_warn("size is not equal to HELLOWORLD89_SIZE\n");

		return size;
	}

	return HELLOWORLD89_SIZE;
}

static bool HelloWorld89_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld89  *topic = (HelloWorld89  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld89_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld89_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld89 *topic = (HelloWorld89 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld89_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld89 *HelloWorld89_create(void)
{
	HelloWorld89 *sample;
	uint32_t size = sizeof(struct HelloWorld89);

	sample = (HelloWorld89 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld89_delete(HelloWorld89 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld90
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld90_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld90_init(HelloWorld90 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld90_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld90 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld90_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld90 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld90_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld90_topic_max_size(0) + 4u);

	if (size != HELLOWORLD90_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD90_SIZE:%d\n", size, HELLOWORLD90_SIZE);
		pr_warn("size is not equal to HELLOWORLD90_SIZE\n");

		return size;
	}

	return HELLOWORLD90_SIZE;
}

static bool HelloWorld90_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld90  *topic = (HelloWorld90  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld90_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld90_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld90 *topic = (HelloWorld90 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld90_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld90 *HelloWorld90_create(void)
{
	HelloWorld90 *sample;
	uint32_t size = sizeof(struct HelloWorld90);

	sample = (HelloWorld90 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld90_delete(HelloWorld90 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld91
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld91_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld91_init(HelloWorld91 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld91_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld91 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld91_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld91 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld91_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld91_topic_max_size(0) + 4u);

	if (size != HELLOWORLD91_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD91_SIZE:%d\n", size, HELLOWORLD91_SIZE);
		pr_warn("size is not equal to HELLOWORLD91_SIZE\n");

		return size;
	}

	return HELLOWORLD91_SIZE;
}

static bool HelloWorld91_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld91  *topic = (HelloWorld91  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld91_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld91_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld91 *topic = (HelloWorld91 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld91_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld91 *HelloWorld91_create(void)
{
	HelloWorld91 *sample;
	uint32_t size = sizeof(struct HelloWorld91);

	sample = (HelloWorld91 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld91_delete(HelloWorld91 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld92
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld92_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld92_init(HelloWorld92 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld92_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld92 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld92_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld92 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld92_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld92_topic_max_size(0) + 4u);

	if (size != HELLOWORLD92_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD92_SIZE:%d\n", size, HELLOWORLD92_SIZE);
		pr_warn("size is not equal to HELLOWORLD92_SIZE\n");

		return size;
	}

	return HELLOWORLD92_SIZE;
}

static bool HelloWorld92_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld92  *topic = (HelloWorld92  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld92_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld92_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld92 *topic = (HelloWorld92 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld92_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld92 *HelloWorld92_create(void)
{
	HelloWorld92 *sample;
	uint32_t size = sizeof(struct HelloWorld92);

	sample = (HelloWorld92 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld92_delete(HelloWorld92 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld93
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld93_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld93_init(HelloWorld93 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld93_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld93 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld93_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld93 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld93_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld93_topic_max_size(0) + 4u);

	if (size != HELLOWORLD93_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD93_SIZE:%d\n", size, HELLOWORLD93_SIZE);
		pr_warn("size is not equal to HELLOWORLD93_SIZE\n");

		return size;
	}

	return HELLOWORLD93_SIZE;
}

static bool HelloWorld93_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld93  *topic = (HelloWorld93  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld93_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld93_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld93 *topic = (HelloWorld93 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld93_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld93 *HelloWorld93_create(void)
{
	HelloWorld93 *sample;
	uint32_t size = sizeof(struct HelloWorld93);

	sample = (HelloWorld93 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld93_delete(HelloWorld93 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld94
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld94_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld94_init(HelloWorld94 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld94_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld94 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld94_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld94 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld94_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld94_topic_max_size(0) + 4u);

	if (size != HELLOWORLD94_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD94_SIZE:%d\n", size, HELLOWORLD94_SIZE);
		pr_warn("size is not equal to HELLOWORLD94_SIZE\n");

		return size;
	}

	return HELLOWORLD94_SIZE;
}

static bool HelloWorld94_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld94  *topic = (HelloWorld94  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld94_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld94_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld94 *topic = (HelloWorld94 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld94_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld94 *HelloWorld94_create(void)
{
	HelloWorld94 *sample;
	uint32_t size = sizeof(struct HelloWorld94);

	sample = (HelloWorld94 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld94_delete(HelloWorld94 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld95
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld95_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld95_init(HelloWorld95 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld95_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld95 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld95_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld95 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld95_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld95_topic_max_size(0) + 4u);

	if (size != HELLOWORLD95_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD95_SIZE:%d\n", size, HELLOWORLD95_SIZE);
		pr_warn("size is not equal to HELLOWORLD95_SIZE\n");

		return size;
	}

	return HELLOWORLD95_SIZE;
}

static bool HelloWorld95_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld95  *topic = (HelloWorld95  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld95_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld95_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld95 *topic = (HelloWorld95 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld95_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld95 *HelloWorld95_create(void)
{
	HelloWorld95 *sample;
	uint32_t size = sizeof(struct HelloWorld95);

	sample = (HelloWorld95 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld95_delete(HelloWorld95 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld96
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld96_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld96_init(HelloWorld96 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld96_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld96 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld96_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld96 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld96_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld96_topic_max_size(0) + 4u);

	if (size != HELLOWORLD96_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD96_SIZE:%d\n", size, HELLOWORLD96_SIZE);
		pr_warn("size is not equal to HELLOWORLD96_SIZE\n");

		return size;
	}

	return HELLOWORLD96_SIZE;
}

static bool HelloWorld96_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld96  *topic = (HelloWorld96  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld96_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld96_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld96 *topic = (HelloWorld96 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld96_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld96 *HelloWorld96_create(void)
{
	HelloWorld96 *sample;
	uint32_t size = sizeof(struct HelloWorld96);

	sample = (HelloWorld96 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld96_delete(HelloWorld96 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld97
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld97_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld97_init(HelloWorld97 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld97_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld97 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld97_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld97 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld97_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld97_topic_max_size(0) + 4u);

	if (size != HELLOWORLD97_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD97_SIZE:%d\n", size, HELLOWORLD97_SIZE);
		pr_warn("size is not equal to HELLOWORLD97_SIZE\n");

		return size;
	}

	return HELLOWORLD97_SIZE;
}

static bool HelloWorld97_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld97  *topic = (HelloWorld97  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld97_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld97_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld97 *topic = (HelloWorld97 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld97_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld97 *HelloWorld97_create(void)
{
	HelloWorld97 *sample;
	uint32_t size = sizeof(struct HelloWorld97);

	sample = (HelloWorld97 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld97_delete(HelloWorld97 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld98
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld98_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld98_init(HelloWorld98 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld98_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld98 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld98_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld98 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld98_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld98_topic_max_size(0) + 4u);

	if (size != HELLOWORLD98_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD98_SIZE:%d\n", size, HELLOWORLD98_SIZE);
		pr_warn("size is not equal to HELLOWORLD98_SIZE\n");

		return size;
	}

	return HELLOWORLD98_SIZE;
}

static bool HelloWorld98_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld98  *topic = (HelloWorld98  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld98_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld98_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld98 *topic = (HelloWorld98 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld98_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld98 *HelloWorld98_create(void)
{
	HelloWorld98 *sample;
	uint32_t size = sizeof(struct HelloWorld98);

	sample = (HelloWorld98 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld98_delete(HelloWorld98 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld99
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld99_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld99_init(HelloWorld99 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld99_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld99 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld99_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld99 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld99_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld99_topic_max_size(0) + 4u);

	if (size != HELLOWORLD99_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD99_SIZE:%d\n", size, HELLOWORLD99_SIZE);
		pr_warn("size is not equal to HELLOWORLD99_SIZE\n");

		return size;
	}

	return HELLOWORLD99_SIZE;
}

static bool HelloWorld99_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld99  *topic = (HelloWorld99  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld99_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld99_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld99 *topic = (HelloWorld99 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld99_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld99 *HelloWorld99_create(void)
{
	HelloWorld99 *sample;
	uint32_t size = sizeof(struct HelloWorld99);

	sample = (HelloWorld99 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld99_delete(HelloWorld99 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld100
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld100_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld100_init(HelloWorld100 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld100_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld100 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld100_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld100 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld100_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld100_topic_max_size(0) + 4u);

	if (size != HELLOWORLD100_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD100_SIZE:%d\n", size, HELLOWORLD100_SIZE);
		pr_warn("size is not equal to HELLOWORLD100_SIZE\n");

		return size;
	}

	return HELLOWORLD100_SIZE;
}

static bool HelloWorld100_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld100  *topic = (HelloWorld100  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld100_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld100_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld100 *topic = (HelloWorld100 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld100_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld100 *HelloWorld100_create(void)
{
	HelloWorld100 *sample;
	uint32_t size = sizeof(struct HelloWorld100);

	sample = (HelloWorld100 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld100_delete(HelloWorld100 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld101
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld101_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld101_init(HelloWorld101 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld101_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld101 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld101_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld101 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld101_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld101_topic_max_size(0) + 4u);

	if (size != HELLOWORLD101_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD101_SIZE:%d\n", size, HELLOWORLD101_SIZE);
		pr_warn("size is not equal to HELLOWORLD101_SIZE\n");

		return size;
	}

	return HELLOWORLD101_SIZE;
}

static bool HelloWorld101_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld101  *topic = (HelloWorld101  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld101_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld101_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld101 *topic = (HelloWorld101 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld101_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld101 *HelloWorld101_create(void)
{
	HelloWorld101 *sample;
	uint32_t size = sizeof(struct HelloWorld101);

	sample = (HelloWorld101 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld101_delete(HelloWorld101 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld102
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld102_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld102_init(HelloWorld102 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld102_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld102 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld102_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld102 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld102_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld102_topic_max_size(0) + 4u);

	if (size != HELLOWORLD102_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD102_SIZE:%d\n", size, HELLOWORLD102_SIZE);
		pr_warn("size is not equal to HELLOWORLD102_SIZE\n");

		return size;
	}

	return HELLOWORLD102_SIZE;
}

static bool HelloWorld102_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld102  *topic = (HelloWorld102  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld102_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld102_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld102 *topic = (HelloWorld102 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld102_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld102 *HelloWorld102_create(void)
{
	HelloWorld102 *sample;
	uint32_t size = sizeof(struct HelloWorld102);

	sample = (HelloWorld102 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld102_delete(HelloWorld102 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld103
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld103_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld103_init(HelloWorld103 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld103_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld103 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld103_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld103 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld103_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld103_topic_max_size(0) + 4u);

	if (size != HELLOWORLD103_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD103_SIZE:%d\n", size, HELLOWORLD103_SIZE);
		pr_warn("size is not equal to HELLOWORLD103_SIZE\n");

		return size;
	}

	return HELLOWORLD103_SIZE;
}

static bool HelloWorld103_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld103  *topic = (HelloWorld103  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld103_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld103_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld103 *topic = (HelloWorld103 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld103_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld103 *HelloWorld103_create(void)
{
	HelloWorld103 *sample;
	uint32_t size = sizeof(struct HelloWorld103);

	sample = (HelloWorld103 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld103_delete(HelloWorld103 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld104
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld104_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld104_init(HelloWorld104 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld104_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld104 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld104_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld104 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld104_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld104_topic_max_size(0) + 4u);

	if (size != HELLOWORLD104_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD104_SIZE:%d\n", size, HELLOWORLD104_SIZE);
		pr_warn("size is not equal to HELLOWORLD104_SIZE\n");

		return size;
	}

	return HELLOWORLD104_SIZE;
}

static bool HelloWorld104_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld104  *topic = (HelloWorld104  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld104_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld104_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld104 *topic = (HelloWorld104 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld104_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld104 *HelloWorld104_create(void)
{
	HelloWorld104 *sample;
	uint32_t size = sizeof(struct HelloWorld104);

	sample = (HelloWorld104 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld104_delete(HelloWorld104 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld105
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld105_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld105_init(HelloWorld105 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld105_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld105 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld105_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld105 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld105_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld105_topic_max_size(0) + 4u);

	if (size != HELLOWORLD105_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD105_SIZE:%d\n", size, HELLOWORLD105_SIZE);
		pr_warn("size is not equal to HELLOWORLD105_SIZE\n");

		return size;
	}

	return HELLOWORLD105_SIZE;
}

static bool HelloWorld105_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld105  *topic = (HelloWorld105  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld105_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld105_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld105 *topic = (HelloWorld105 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld105_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld105 *HelloWorld105_create(void)
{
	HelloWorld105 *sample;
	uint32_t size = sizeof(struct HelloWorld105);

	sample = (HelloWorld105 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld105_delete(HelloWorld105 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld106
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld106_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld106_init(HelloWorld106 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld106_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld106 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld106_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld106 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld106_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld106_topic_max_size(0) + 4u);

	if (size != HELLOWORLD106_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD106_SIZE:%d\n", size, HELLOWORLD106_SIZE);
		pr_warn("size is not equal to HELLOWORLD106_SIZE\n");

		return size;
	}

	return HELLOWORLD106_SIZE;
}

static bool HelloWorld106_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld106  *topic = (HelloWorld106  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld106_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld106_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld106 *topic = (HelloWorld106 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld106_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld106 *HelloWorld106_create(void)
{
	HelloWorld106 *sample;
	uint32_t size = sizeof(struct HelloWorld106);

	sample = (HelloWorld106 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld106_delete(HelloWorld106 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld107
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld107_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld107_init(HelloWorld107 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld107_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld107 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld107_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld107 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld107_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld107_topic_max_size(0) + 4u);

	if (size != HELLOWORLD107_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD107_SIZE:%d\n", size, HELLOWORLD107_SIZE);
		pr_warn("size is not equal to HELLOWORLD107_SIZE\n");

		return size;
	}

	return HELLOWORLD107_SIZE;
}

static bool HelloWorld107_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld107  *topic = (HelloWorld107  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld107_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld107_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld107 *topic = (HelloWorld107 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld107_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld107 *HelloWorld107_create(void)
{
	HelloWorld107 *sample;
	uint32_t size = sizeof(struct HelloWorld107);

	sample = (HelloWorld107 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld107_delete(HelloWorld107 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld108
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld108_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld108_init(HelloWorld108 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld108_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld108 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld108_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld108 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld108_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld108_topic_max_size(0) + 4u);

	if (size != HELLOWORLD108_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD108_SIZE:%d\n", size, HELLOWORLD108_SIZE);
		pr_warn("size is not equal to HELLOWORLD108_SIZE\n");

		return size;
	}

	return HELLOWORLD108_SIZE;
}

static bool HelloWorld108_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld108  *topic = (HelloWorld108  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld108_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld108_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld108 *topic = (HelloWorld108 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld108_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld108 *HelloWorld108_create(void)
{
	HelloWorld108 *sample;
	uint32_t size = sizeof(struct HelloWorld108);

	sample = (HelloWorld108 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld108_delete(HelloWorld108 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld109
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld109_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld109_init(HelloWorld109 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld109_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld109 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld109_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld109 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld109_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld109_topic_max_size(0) + 4u);

	if (size != HELLOWORLD109_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD109_SIZE:%d\n", size, HELLOWORLD109_SIZE);
		pr_warn("size is not equal to HELLOWORLD109_SIZE\n");

		return size;
	}

	return HELLOWORLD109_SIZE;
}

static bool HelloWorld109_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld109  *topic = (HelloWorld109  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld109_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld109_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld109 *topic = (HelloWorld109 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld109_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld109 *HelloWorld109_create(void)
{
	HelloWorld109 *sample;
	uint32_t size = sizeof(struct HelloWorld109);

	sample = (HelloWorld109 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld109_delete(HelloWorld109 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld110
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld110_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld110_init(HelloWorld110 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld110_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld110 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld110_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld110 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld110_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld110_topic_max_size(0) + 4u);

	if (size != HELLOWORLD110_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD110_SIZE:%d\n", size, HELLOWORLD110_SIZE);
		pr_warn("size is not equal to HELLOWORLD110_SIZE\n");

		return size;
	}

	return HELLOWORLD110_SIZE;
}

static bool HelloWorld110_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld110  *topic = (HelloWorld110  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld110_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld110_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld110 *topic = (HelloWorld110 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld110_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld110 *HelloWorld110_create(void)
{
	HelloWorld110 *sample;
	uint32_t size = sizeof(struct HelloWorld110);

	sample = (HelloWorld110 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld110_delete(HelloWorld110 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld111
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld111_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld111_init(HelloWorld111 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld111_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld111 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld111_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld111 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld111_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld111_topic_max_size(0) + 4u);

	if (size != HELLOWORLD111_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD111_SIZE:%d\n", size, HELLOWORLD111_SIZE);
		pr_warn("size is not equal to HELLOWORLD111_SIZE\n");

		return size;
	}

	return HELLOWORLD111_SIZE;
}

static bool HelloWorld111_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld111  *topic = (HelloWorld111  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld111_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld111_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld111 *topic = (HelloWorld111 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld111_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld111 *HelloWorld111_create(void)
{
	HelloWorld111 *sample;
	uint32_t size = sizeof(struct HelloWorld111);

	sample = (HelloWorld111 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld111_delete(HelloWorld111 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld112
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld112_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld112_init(HelloWorld112 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld112_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld112 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld112_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld112 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld112_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld112_topic_max_size(0) + 4u);

	if (size != HELLOWORLD112_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD112_SIZE:%d\n", size, HELLOWORLD112_SIZE);
		pr_warn("size is not equal to HELLOWORLD112_SIZE\n");

		return size;
	}

	return HELLOWORLD112_SIZE;
}

static bool HelloWorld112_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld112  *topic = (HelloWorld112  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld112_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld112_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld112 *topic = (HelloWorld112 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld112_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld112 *HelloWorld112_create(void)
{
	HelloWorld112 *sample;
	uint32_t size = sizeof(struct HelloWorld112);

	sample = (HelloWorld112 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld112_delete(HelloWorld112 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld113
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld113_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld113_init(HelloWorld113 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld113_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld113 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld113_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld113 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld113_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld113_topic_max_size(0) + 4u);

	if (size != HELLOWORLD113_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD113_SIZE:%d\n", size, HELLOWORLD113_SIZE);
		pr_warn("size is not equal to HELLOWORLD113_SIZE\n");

		return size;
	}

	return HELLOWORLD113_SIZE;
}

static bool HelloWorld113_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld113  *topic = (HelloWorld113  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld113_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld113_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld113 *topic = (HelloWorld113 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld113_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld113 *HelloWorld113_create(void)
{
	HelloWorld113 *sample;
	uint32_t size = sizeof(struct HelloWorld113);

	sample = (HelloWorld113 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld113_delete(HelloWorld113 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld114
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld114_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld114_init(HelloWorld114 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld114_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld114 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld114_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld114 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld114_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld114_topic_max_size(0) + 4u);

	if (size != HELLOWORLD114_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD114_SIZE:%d\n", size, HELLOWORLD114_SIZE);
		pr_warn("size is not equal to HELLOWORLD114_SIZE\n");

		return size;
	}

	return HELLOWORLD114_SIZE;
}

static bool HelloWorld114_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld114  *topic = (HelloWorld114  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld114_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld114_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld114 *topic = (HelloWorld114 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld114_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld114 *HelloWorld114_create(void)
{
	HelloWorld114 *sample;
	uint32_t size = sizeof(struct HelloWorld114);

	sample = (HelloWorld114 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld114_delete(HelloWorld114 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld115
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld115_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld115_init(HelloWorld115 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld115_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld115 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld115_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld115 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld115_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld115_topic_max_size(0) + 4u);

	if (size != HELLOWORLD115_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD115_SIZE:%d\n", size, HELLOWORLD115_SIZE);
		pr_warn("size is not equal to HELLOWORLD115_SIZE\n");

		return size;
	}

	return HELLOWORLD115_SIZE;
}

static bool HelloWorld115_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld115  *topic = (HelloWorld115  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld115_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld115_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld115 *topic = (HelloWorld115 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld115_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld115 *HelloWorld115_create(void)
{
	HelloWorld115 *sample;
	uint32_t size = sizeof(struct HelloWorld115);

	sample = (HelloWorld115 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld115_delete(HelloWorld115 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld116
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld116_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld116_init(HelloWorld116 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld116_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld116 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld116_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld116 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld116_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld116_topic_max_size(0) + 4u);

	if (size != HELLOWORLD116_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD116_SIZE:%d\n", size, HELLOWORLD116_SIZE);
		pr_warn("size is not equal to HELLOWORLD116_SIZE\n");

		return size;
	}

	return HELLOWORLD116_SIZE;
}

static bool HelloWorld116_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld116  *topic = (HelloWorld116  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld116_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld116_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld116 *topic = (HelloWorld116 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld116_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld116 *HelloWorld116_create(void)
{
	HelloWorld116 *sample;
	uint32_t size = sizeof(struct HelloWorld116);

	sample = (HelloWorld116 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld116_delete(HelloWorld116 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld117
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld117_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld117_init(HelloWorld117 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld117_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld117 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld117_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld117 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld117_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld117_topic_max_size(0) + 4u);

	if (size != HELLOWORLD117_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD117_SIZE:%d\n", size, HELLOWORLD117_SIZE);
		pr_warn("size is not equal to HELLOWORLD117_SIZE\n");

		return size;
	}

	return HELLOWORLD117_SIZE;
}

static bool HelloWorld117_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld117  *topic = (HelloWorld117  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld117_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld117_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld117 *topic = (HelloWorld117 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld117_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld117 *HelloWorld117_create(void)
{
	HelloWorld117 *sample;
	uint32_t size = sizeof(struct HelloWorld117);

	sample = (HelloWorld117 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld117_delete(HelloWorld117 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld118
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld118_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld118_init(HelloWorld118 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld118_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld118 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld118_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld118 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld118_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld118_topic_max_size(0) + 4u);

	if (size != HELLOWORLD118_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD118_SIZE:%d\n", size, HELLOWORLD118_SIZE);
		pr_warn("size is not equal to HELLOWORLD118_SIZE\n");

		return size;
	}

	return HELLOWORLD118_SIZE;
}

static bool HelloWorld118_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld118  *topic = (HelloWorld118  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld118_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld118_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld118 *topic = (HelloWorld118 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld118_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld118 *HelloWorld118_create(void)
{
	HelloWorld118 *sample;
	uint32_t size = sizeof(struct HelloWorld118);

	sample = (HelloWorld118 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld118_delete(HelloWorld118 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld119
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld119_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld119_init(HelloWorld119 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld119_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld119 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld119_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld119 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld119_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld119_topic_max_size(0) + 4u);

	if (size != HELLOWORLD119_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD119_SIZE:%d\n", size, HELLOWORLD119_SIZE);
		pr_warn("size is not equal to HELLOWORLD119_SIZE\n");

		return size;
	}

	return HELLOWORLD119_SIZE;
}

static bool HelloWorld119_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld119  *topic = (HelloWorld119  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld119_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld119_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld119 *topic = (HelloWorld119 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld119_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld119 *HelloWorld119_create(void)
{
	HelloWorld119 *sample;
	uint32_t size = sizeof(struct HelloWorld119);

	sample = (HelloWorld119 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld119_delete(HelloWorld119 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld120
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld120_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld120_init(HelloWorld120 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld120_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld120 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld120_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld120 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld120_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld120_topic_max_size(0) + 4u);

	if (size != HELLOWORLD120_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD120_SIZE:%d\n", size, HELLOWORLD120_SIZE);
		pr_warn("size is not equal to HELLOWORLD120_SIZE\n");

		return size;
	}

	return HELLOWORLD120_SIZE;
}

static bool HelloWorld120_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld120  *topic = (HelloWorld120  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld120_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld120_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld120 *topic = (HelloWorld120 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld120_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld120 *HelloWorld120_create(void)
{
	HelloWorld120 *sample;
	uint32_t size = sizeof(struct HelloWorld120);

	sample = (HelloWorld120 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld120_delete(HelloWorld120 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld121
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld121_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld121_init(HelloWorld121 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld121_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld121 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld121_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld121 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld121_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld121_topic_max_size(0) + 4u);

	if (size != HELLOWORLD121_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD121_SIZE:%d\n", size, HELLOWORLD121_SIZE);
		pr_warn("size is not equal to HELLOWORLD121_SIZE\n");

		return size;
	}

	return HELLOWORLD121_SIZE;
}

static bool HelloWorld121_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld121  *topic = (HelloWorld121  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld121_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld121_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld121 *topic = (HelloWorld121 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld121_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld121 *HelloWorld121_create(void)
{
	HelloWorld121 *sample;
	uint32_t size = sizeof(struct HelloWorld121);

	sample = (HelloWorld121 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld121_delete(HelloWorld121 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld122
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld122_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld122_init(HelloWorld122 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld122_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld122 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld122_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld122 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld122_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld122_topic_max_size(0) + 4u);

	if (size != HELLOWORLD122_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD122_SIZE:%d\n", size, HELLOWORLD122_SIZE);
		pr_warn("size is not equal to HELLOWORLD122_SIZE\n");

		return size;
	}

	return HELLOWORLD122_SIZE;
}

static bool HelloWorld122_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld122  *topic = (HelloWorld122  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld122_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld122_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld122 *topic = (HelloWorld122 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld122_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld122 *HelloWorld122_create(void)
{
	HelloWorld122 *sample;
	uint32_t size = sizeof(struct HelloWorld122);

	sample = (HelloWorld122 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld122_delete(HelloWorld122 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld123
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld123_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld123_init(HelloWorld123 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld123_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld123 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld123_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld123 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld123_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld123_topic_max_size(0) + 4u);

	if (size != HELLOWORLD123_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD123_SIZE:%d\n", size, HELLOWORLD123_SIZE);
		pr_warn("size is not equal to HELLOWORLD123_SIZE\n");

		return size;
	}

	return HELLOWORLD123_SIZE;
}

static bool HelloWorld123_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld123  *topic = (HelloWorld123  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld123_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld123_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld123 *topic = (HelloWorld123 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld123_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld123 *HelloWorld123_create(void)
{
	HelloWorld123 *sample;
	uint32_t size = sizeof(struct HelloWorld123);

	sample = (HelloWorld123 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld123_delete(HelloWorld123 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld124
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld124_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld124_init(HelloWorld124 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld124_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld124 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld124_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld124 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld124_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld124_topic_max_size(0) + 4u);

	if (size != HELLOWORLD124_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD124_SIZE:%d\n", size, HELLOWORLD124_SIZE);
		pr_warn("size is not equal to HELLOWORLD124_SIZE\n");

		return size;
	}

	return HELLOWORLD124_SIZE;
}

static bool HelloWorld124_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld124  *topic = (HelloWorld124  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld124_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld124_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld124 *topic = (HelloWorld124 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld124_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld124 *HelloWorld124_create(void)
{
	HelloWorld124 *sample;
	uint32_t size = sizeof(struct HelloWorld124);

	sample = (HelloWorld124 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld124_delete(HelloWorld124 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld125
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld125_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld125_init(HelloWorld125 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld125_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld125 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld125_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld125 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld125_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld125_topic_max_size(0) + 4u);

	if (size != HELLOWORLD125_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD125_SIZE:%d\n", size, HELLOWORLD125_SIZE);
		pr_warn("size is not equal to HELLOWORLD125_SIZE\n");

		return size;
	}

	return HELLOWORLD125_SIZE;
}

static bool HelloWorld125_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld125  *topic = (HelloWorld125  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld125_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld125_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld125 *topic = (HelloWorld125 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld125_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld125 *HelloWorld125_create(void)
{
	HelloWorld125 *sample;
	uint32_t size = sizeof(struct HelloWorld125);

	sample = (HelloWorld125 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld125_delete(HelloWorld125 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld126
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld126_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld126_init(HelloWorld126 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld126_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld126 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld126_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld126 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld126_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld126_topic_max_size(0) + 4u);

	if (size != HELLOWORLD126_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD126_SIZE:%d\n", size, HELLOWORLD126_SIZE);
		pr_warn("size is not equal to HELLOWORLD126_SIZE\n");

		return size;
	}

	return HELLOWORLD126_SIZE;
}

static bool HelloWorld126_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld126  *topic = (HelloWorld126  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld126_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld126_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld126 *topic = (HelloWorld126 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld126_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld126 *HelloWorld126_create(void)
{
	HelloWorld126 *sample;
	uint32_t size = sizeof(struct HelloWorld126);

	sample = (HelloWorld126 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld126_delete(HelloWorld126 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld127
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld127_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld127_init(HelloWorld127 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld127_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld127 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld127_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld127 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld127_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld127_topic_max_size(0) + 4u);

	if (size != HELLOWORLD127_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD127_SIZE:%d\n", size, HELLOWORLD127_SIZE);
		pr_warn("size is not equal to HELLOWORLD127_SIZE\n");

		return size;
	}

	return HELLOWORLD127_SIZE;
}

static bool HelloWorld127_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld127  *topic = (HelloWorld127  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld127_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld127_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld127 *topic = (HelloWorld127 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld127_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld127 *HelloWorld127_create(void)
{
	HelloWorld127 *sample;
	uint32_t size = sizeof(struct HelloWorld127);

	sample = (HelloWorld127 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld127_delete(HelloWorld127 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld128
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld128_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld128_init(HelloWorld128 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld128_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld128 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld128_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld128 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld128_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld128_topic_max_size(0) + 4u);

	if (size != HELLOWORLD128_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD128_SIZE:%d\n", size, HELLOWORLD128_SIZE);
		pr_warn("size is not equal to HELLOWORLD128_SIZE\n");

		return size;
	}

	return HELLOWORLD128_SIZE;
}

static bool HelloWorld128_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld128  *topic = (HelloWorld128  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld128_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld128_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld128 *topic = (HelloWorld128 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld128_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld128 *HelloWorld128_create(void)
{
	HelloWorld128 *sample;
	uint32_t size = sizeof(struct HelloWorld128);

	sample = (HelloWorld128 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld128_delete(HelloWorld128 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld129
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld129_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld129_init(HelloWorld129 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld129_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld129 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld129_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld129 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld129_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld129_topic_max_size(0) + 4u);

	if (size != HELLOWORLD129_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD129_SIZE:%d\n", size, HELLOWORLD129_SIZE);
		pr_warn("size is not equal to HELLOWORLD129_SIZE\n");

		return size;
	}

	return HELLOWORLD129_SIZE;
}

static bool HelloWorld129_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld129  *topic = (HelloWorld129  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld129_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld129_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld129 *topic = (HelloWorld129 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld129_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld129 *HelloWorld129_create(void)
{
	HelloWorld129 *sample;
	uint32_t size = sizeof(struct HelloWorld129);

	sample = (HelloWorld129 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld129_delete(HelloWorld129 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld130
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld130_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld130_init(HelloWorld130 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld130_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld130 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld130_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld130 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld130_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld130_topic_max_size(0) + 4u);

	if (size != HELLOWORLD130_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD130_SIZE:%d\n", size, HELLOWORLD130_SIZE);
		pr_warn("size is not equal to HELLOWORLD130_SIZE\n");

		return size;
	}

	return HELLOWORLD130_SIZE;
}

static bool HelloWorld130_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld130  *topic = (HelloWorld130  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld130_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld130_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld130 *topic = (HelloWorld130 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld130_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld130 *HelloWorld130_create(void)
{
	HelloWorld130 *sample;
	uint32_t size = sizeof(struct HelloWorld130);

	sample = (HelloWorld130 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld130_delete(HelloWorld130 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld131
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld131_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld131_init(HelloWorld131 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld131_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld131 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld131_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld131 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld131_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld131_topic_max_size(0) + 4u);

	if (size != HELLOWORLD131_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD131_SIZE:%d\n", size, HELLOWORLD131_SIZE);
		pr_warn("size is not equal to HELLOWORLD131_SIZE\n");

		return size;
	}

	return HELLOWORLD131_SIZE;
}

static bool HelloWorld131_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld131  *topic = (HelloWorld131  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld131_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld131_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld131 *topic = (HelloWorld131 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld131_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld131 *HelloWorld131_create(void)
{
	HelloWorld131 *sample;
	uint32_t size = sizeof(struct HelloWorld131);

	sample = (HelloWorld131 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld131_delete(HelloWorld131 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld132
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld132_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld132_init(HelloWorld132 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld132_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld132 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld132_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld132 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld132_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld132_topic_max_size(0) + 4u);

	if (size != HELLOWORLD132_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD132_SIZE:%d\n", size, HELLOWORLD132_SIZE);
		pr_warn("size is not equal to HELLOWORLD132_SIZE\n");

		return size;
	}

	return HELLOWORLD132_SIZE;
}

static bool HelloWorld132_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld132  *topic = (HelloWorld132  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld132_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld132_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld132 *topic = (HelloWorld132 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld132_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld132 *HelloWorld132_create(void)
{
	HelloWorld132 *sample;
	uint32_t size = sizeof(struct HelloWorld132);

	sample = (HelloWorld132 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld132_delete(HelloWorld132 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld133
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld133_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld133_init(HelloWorld133 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld133_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld133 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld133_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld133 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld133_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld133_topic_max_size(0) + 4u);

	if (size != HELLOWORLD133_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD133_SIZE:%d\n", size, HELLOWORLD133_SIZE);
		pr_warn("size is not equal to HELLOWORLD133_SIZE\n");

		return size;
	}

	return HELLOWORLD133_SIZE;
}

static bool HelloWorld133_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld133  *topic = (HelloWorld133  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld133_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld133_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld133 *topic = (HelloWorld133 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld133_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld133 *HelloWorld133_create(void)
{
	HelloWorld133 *sample;
	uint32_t size = sizeof(struct HelloWorld133);

	sample = (HelloWorld133 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld133_delete(HelloWorld133 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld134
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld134_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld134_init(HelloWorld134 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld134_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld134 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld134_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld134 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld134_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld134_topic_max_size(0) + 4u);

	if (size != HELLOWORLD134_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD134_SIZE:%d\n", size, HELLOWORLD134_SIZE);
		pr_warn("size is not equal to HELLOWORLD134_SIZE\n");

		return size;
	}

	return HELLOWORLD134_SIZE;
}

static bool HelloWorld134_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld134  *topic = (HelloWorld134  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld134_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld134_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld134 *topic = (HelloWorld134 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld134_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld134 *HelloWorld134_create(void)
{
	HelloWorld134 *sample;
	uint32_t size = sizeof(struct HelloWorld134);

	sample = (HelloWorld134 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld134_delete(HelloWorld134 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld135
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld135_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld135_init(HelloWorld135 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld135_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld135 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld135_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld135 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld135_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld135_topic_max_size(0) + 4u);

	if (size != HELLOWORLD135_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD135_SIZE:%d\n", size, HELLOWORLD135_SIZE);
		pr_warn("size is not equal to HELLOWORLD135_SIZE\n");

		return size;
	}

	return HELLOWORLD135_SIZE;
}

static bool HelloWorld135_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld135  *topic = (HelloWorld135  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld135_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld135_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld135 *topic = (HelloWorld135 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld135_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld135 *HelloWorld135_create(void)
{
	HelloWorld135 *sample;
	uint32_t size = sizeof(struct HelloWorld135);

	sample = (HelloWorld135 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld135_delete(HelloWorld135 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld136
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld136_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld136_init(HelloWorld136 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld136_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld136 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld136_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld136 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld136_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld136_topic_max_size(0) + 4u);

	if (size != HELLOWORLD136_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD136_SIZE:%d\n", size, HELLOWORLD136_SIZE);
		pr_warn("size is not equal to HELLOWORLD136_SIZE\n");

		return size;
	}

	return HELLOWORLD136_SIZE;
}

static bool HelloWorld136_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld136  *topic = (HelloWorld136  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld136_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld136_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld136 *topic = (HelloWorld136 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld136_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld136 *HelloWorld136_create(void)
{
	HelloWorld136 *sample;
	uint32_t size = sizeof(struct HelloWorld136);

	sample = (HelloWorld136 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld136_delete(HelloWorld136 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld137
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld137_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld137_init(HelloWorld137 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld137_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld137 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld137_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld137 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld137_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld137_topic_max_size(0) + 4u);

	if (size != HELLOWORLD137_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD137_SIZE:%d\n", size, HELLOWORLD137_SIZE);
		pr_warn("size is not equal to HELLOWORLD137_SIZE\n");

		return size;
	}

	return HELLOWORLD137_SIZE;
}

static bool HelloWorld137_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld137  *topic = (HelloWorld137  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld137_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld137_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld137 *topic = (HelloWorld137 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld137_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld137 *HelloWorld137_create(void)
{
	HelloWorld137 *sample;
	uint32_t size = sizeof(struct HelloWorld137);

	sample = (HelloWorld137 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld137_delete(HelloWorld137 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld138
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld138_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld138_init(HelloWorld138 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld138_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld138 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld138_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld138 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld138_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld138_topic_max_size(0) + 4u);

	if (size != HELLOWORLD138_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD138_SIZE:%d\n", size, HELLOWORLD138_SIZE);
		pr_warn("size is not equal to HELLOWORLD138_SIZE\n");

		return size;
	}

	return HELLOWORLD138_SIZE;
}

static bool HelloWorld138_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld138  *topic = (HelloWorld138  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld138_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld138_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld138 *topic = (HelloWorld138 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld138_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld138 *HelloWorld138_create(void)
{
	HelloWorld138 *sample;
	uint32_t size = sizeof(struct HelloWorld138);

	sample = (HelloWorld138 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld138_delete(HelloWorld138 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld139
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld139_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld139_init(HelloWorld139 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld139_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld139 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld139_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld139 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld139_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld139_topic_max_size(0) + 4u);

	if (size != HELLOWORLD139_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD139_SIZE:%d\n", size, HELLOWORLD139_SIZE);
		pr_warn("size is not equal to HELLOWORLD139_SIZE\n");

		return size;
	}

	return HELLOWORLD139_SIZE;
}

static bool HelloWorld139_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld139  *topic = (HelloWorld139  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld139_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld139_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld139 *topic = (HelloWorld139 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld139_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld139 *HelloWorld139_create(void)
{
	HelloWorld139 *sample;
	uint32_t size = sizeof(struct HelloWorld139);

	sample = (HelloWorld139 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld139_delete(HelloWorld139 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld140
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld140_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld140_init(HelloWorld140 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld140_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld140 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld140_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld140 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld140_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld140_topic_max_size(0) + 4u);

	if (size != HELLOWORLD140_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD140_SIZE:%d\n", size, HELLOWORLD140_SIZE);
		pr_warn("size is not equal to HELLOWORLD140_SIZE\n");

		return size;
	}

	return HELLOWORLD140_SIZE;
}

static bool HelloWorld140_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld140  *topic = (HelloWorld140  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld140_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld140_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld140 *topic = (HelloWorld140 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld140_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld140 *HelloWorld140_create(void)
{
	HelloWorld140 *sample;
	uint32_t size = sizeof(struct HelloWorld140);

	sample = (HelloWorld140 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld140_delete(HelloWorld140 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld141
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld141_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld141_init(HelloWorld141 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld141_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld141 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld141_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld141 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld141_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld141_topic_max_size(0) + 4u);

	if (size != HELLOWORLD141_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD141_SIZE:%d\n", size, HELLOWORLD141_SIZE);
		pr_warn("size is not equal to HELLOWORLD141_SIZE\n");

		return size;
	}

	return HELLOWORLD141_SIZE;
}

static bool HelloWorld141_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld141  *topic = (HelloWorld141  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld141_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld141_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld141 *topic = (HelloWorld141 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld141_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld141 *HelloWorld141_create(void)
{
	HelloWorld141 *sample;
	uint32_t size = sizeof(struct HelloWorld141);

	sample = (HelloWorld141 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld141_delete(HelloWorld141 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld142
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld142_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld142_init(HelloWorld142 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld142_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld142 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld142_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld142 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld142_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld142_topic_max_size(0) + 4u);

	if (size != HELLOWORLD142_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD142_SIZE:%d\n", size, HELLOWORLD142_SIZE);
		pr_warn("size is not equal to HELLOWORLD142_SIZE\n");

		return size;
	}

	return HELLOWORLD142_SIZE;
}

static bool HelloWorld142_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld142  *topic = (HelloWorld142  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld142_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld142_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld142 *topic = (HelloWorld142 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld142_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld142 *HelloWorld142_create(void)
{
	HelloWorld142 *sample;
	uint32_t size = sizeof(struct HelloWorld142);

	sample = (HelloWorld142 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld142_delete(HelloWorld142 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld143
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld143_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld143_init(HelloWorld143 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld143_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld143 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld143_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld143 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld143_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld143_topic_max_size(0) + 4u);

	if (size != HELLOWORLD143_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD143_SIZE:%d\n", size, HELLOWORLD143_SIZE);
		pr_warn("size is not equal to HELLOWORLD143_SIZE\n");

		return size;
	}

	return HELLOWORLD143_SIZE;
}

static bool HelloWorld143_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld143  *topic = (HelloWorld143  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld143_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld143_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld143 *topic = (HelloWorld143 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld143_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld143 *HelloWorld143_create(void)
{
	HelloWorld143 *sample;
	uint32_t size = sizeof(struct HelloWorld143);

	sample = (HelloWorld143 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld143_delete(HelloWorld143 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld144
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld144_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld144_init(HelloWorld144 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld144_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld144 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld144_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld144 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld144_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld144_topic_max_size(0) + 4u);

	if (size != HELLOWORLD144_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD144_SIZE:%d\n", size, HELLOWORLD144_SIZE);
		pr_warn("size is not equal to HELLOWORLD144_SIZE\n");

		return size;
	}

	return HELLOWORLD144_SIZE;
}

static bool HelloWorld144_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld144  *topic = (HelloWorld144  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld144_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld144_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld144 *topic = (HelloWorld144 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld144_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld144 *HelloWorld144_create(void)
{
	HelloWorld144 *sample;
	uint32_t size = sizeof(struct HelloWorld144);

	sample = (HelloWorld144 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld144_delete(HelloWorld144 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld145
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld145_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld145_init(HelloWorld145 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld145_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld145 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld145_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld145 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld145_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld145_topic_max_size(0) + 4u);

	if (size != HELLOWORLD145_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD145_SIZE:%d\n", size, HELLOWORLD145_SIZE);
		pr_warn("size is not equal to HELLOWORLD145_SIZE\n");

		return size;
	}

	return HELLOWORLD145_SIZE;
}

static bool HelloWorld145_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld145  *topic = (HelloWorld145  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld145_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld145_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld145 *topic = (HelloWorld145 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld145_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld145 *HelloWorld145_create(void)
{
	HelloWorld145 *sample;
	uint32_t size = sizeof(struct HelloWorld145);

	sample = (HelloWorld145 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld145_delete(HelloWorld145 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld146
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld146_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld146_init(HelloWorld146 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld146_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld146 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld146_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld146 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld146_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld146_topic_max_size(0) + 4u);

	if (size != HELLOWORLD146_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD146_SIZE:%d\n", size, HELLOWORLD146_SIZE);
		pr_warn("size is not equal to HELLOWORLD146_SIZE\n");

		return size;
	}

	return HELLOWORLD146_SIZE;
}

static bool HelloWorld146_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld146  *topic = (HelloWorld146  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld146_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld146_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld146 *topic = (HelloWorld146 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld146_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld146 *HelloWorld146_create(void)
{
	HelloWorld146 *sample;
	uint32_t size = sizeof(struct HelloWorld146);

	sample = (HelloWorld146 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld146_delete(HelloWorld146 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld147
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld147_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld147_init(HelloWorld147 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld147_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld147 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld147_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld147 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld147_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld147_topic_max_size(0) + 4u);

	if (size != HELLOWORLD147_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD147_SIZE:%d\n", size, HELLOWORLD147_SIZE);
		pr_warn("size is not equal to HELLOWORLD147_SIZE\n");

		return size;
	}

	return HELLOWORLD147_SIZE;
}

static bool HelloWorld147_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld147  *topic = (HelloWorld147  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld147_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld147_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld147 *topic = (HelloWorld147 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld147_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld147 *HelloWorld147_create(void)
{
	HelloWorld147 *sample;
	uint32_t size = sizeof(struct HelloWorld147);

	sample = (HelloWorld147 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld147_delete(HelloWorld147 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld148
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld148_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u + 500 + 1u;

	return size - previousSize;
}

void HelloWorld148_init(HelloWorld148 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
		mvbs_memzero(sample->str_msg, 500 + 1);
	}
}

bool HelloWorld148_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld148 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_string(cdr, topic->str_msg)) {
		pr_debug("str_msg serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld148_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld148 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_string(cdr, topic->str_msg, 500 + 1)) {
		pr_debug("str_msg deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld148_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld148_topic_max_size(0) + 4u);

	if (size != HELLOWORLD148_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD148_SIZE:%d\n", size, HELLOWORLD148_SIZE);
		pr_warn("size is not equal to HELLOWORLD148_SIZE\n");

		return size;
	}

	return HELLOWORLD148_SIZE;
}

static bool HelloWorld148_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld148  *topic = (HelloWorld148  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld148_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld148_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld148 *topic = (HelloWorld148 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld148_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld148 *HelloWorld148_create(void)
{
	HelloWorld148 *sample;
	uint32_t size = sizeof(struct HelloWorld148);

	sample = (HelloWorld148 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld148_delete(HelloWorld148 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld149
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld149_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u + 1000 + 1u;

	return size - previousSize;
}

void HelloWorld149_init(HelloWorld149 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
		mvbs_memzero(sample->str_msg, 1000 + 1);
	}
}

bool HelloWorld149_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld149 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_string(cdr, topic->str_msg)) {
		pr_debug("str_msg serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld149_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld149 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_string(cdr, topic->str_msg, 1000 + 1)) {
		pr_debug("str_msg deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld149_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld149_topic_max_size(0) + 4u);

	if (size != HELLOWORLD149_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD149_SIZE:%d\n", size, HELLOWORLD149_SIZE);
		pr_warn("size is not equal to HELLOWORLD149_SIZE\n");

		return size;
	}

	return HELLOWORLD149_SIZE;
}

static bool HelloWorld149_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld149  *topic = (HelloWorld149  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld149_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld149_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld149 *topic = (HelloWorld149 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld149_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld149 *HelloWorld149_create(void)
{
	HelloWorld149 *sample;
	uint32_t size = sizeof(struct HelloWorld149);

	sample = (HelloWorld149 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld149_delete(HelloWorld149 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld151
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld151_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld151_init(HelloWorld151 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld151_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld151 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld151_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld151 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld151_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld151_topic_max_size(0) + 4u);

	if (size != HELLOWORLD151_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD151_SIZE:%d\n", size, HELLOWORLD151_SIZE);
		pr_warn("size is not equal to HELLOWORLD151_SIZE\n");

		return size;
	}

	return HELLOWORLD151_SIZE;
}

static bool HelloWorld151_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld151  *topic = (HelloWorld151  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld151_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld151_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld151 *topic = (HelloWorld151 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld151_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld151 *HelloWorld151_create(void)
{
	HelloWorld151 *sample;
	uint32_t size = sizeof(struct HelloWorld151);

	sample = (HelloWorld151 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld151_delete(HelloWorld151 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld152
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld152_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld152_init(HelloWorld152 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld152_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld152 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld152_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld152 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld152_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld152_topic_max_size(0) + 4u);

	if (size != HELLOWORLD152_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD152_SIZE:%d\n", size, HELLOWORLD152_SIZE);
		pr_warn("size is not equal to HELLOWORLD152_SIZE\n");

		return size;
	}

	return HELLOWORLD152_SIZE;
}

static bool HelloWorld152_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld152  *topic = (HelloWorld152  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld152_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld152_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld152 *topic = (HelloWorld152 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld152_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld152 *HelloWorld152_create(void)
{
	HelloWorld152 *sample;
	uint32_t size = sizeof(struct HelloWorld152);

	sample = (HelloWorld152 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld152_delete(HelloWorld152 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld153
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld153_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld153_init(HelloWorld153 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld153_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld153 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld153_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld153 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld153_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld153_topic_max_size(0) + 4u);

	if (size != HELLOWORLD153_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD153_SIZE:%d\n", size, HELLOWORLD153_SIZE);
		pr_warn("size is not equal to HELLOWORLD153_SIZE\n");

		return size;
	}

	return HELLOWORLD153_SIZE;
}

static bool HelloWorld153_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld153  *topic = (HelloWorld153  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld153_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld153_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld153 *topic = (HelloWorld153 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld153_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld153 *HelloWorld153_create(void)
{
	HelloWorld153 *sample;
	uint32_t size = sizeof(struct HelloWorld153);

	sample = (HelloWorld153 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld153_delete(HelloWorld153 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld154
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld154_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld154_init(HelloWorld154 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld154_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld154 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld154_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld154 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld154_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld154_topic_max_size(0) + 4u);

	if (size != HELLOWORLD154_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD154_SIZE:%d\n", size, HELLOWORLD154_SIZE);
		pr_warn("size is not equal to HELLOWORLD154_SIZE\n");

		return size;
	}

	return HELLOWORLD154_SIZE;
}

static bool HelloWorld154_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld154  *topic = (HelloWorld154  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld154_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld154_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld154 *topic = (HelloWorld154 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld154_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld154 *HelloWorld154_create(void)
{
	HelloWorld154 *sample;
	uint32_t size = sizeof(struct HelloWorld154);

	sample = (HelloWorld154 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld154_delete(HelloWorld154 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld155
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld155_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld155_init(HelloWorld155 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld155_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld155 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld155_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld155 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld155_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld155_topic_max_size(0) + 4u);

	if (size != HELLOWORLD155_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD155_SIZE:%d\n", size, HELLOWORLD155_SIZE);
		pr_warn("size is not equal to HELLOWORLD155_SIZE\n");

		return size;
	}

	return HELLOWORLD155_SIZE;
}

static bool HelloWorld155_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld155  *topic = (HelloWorld155  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld155_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld155_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld155 *topic = (HelloWorld155 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld155_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld155 *HelloWorld155_create(void)
{
	HelloWorld155 *sample;
	uint32_t size = sizeof(struct HelloWorld155);

	sample = (HelloWorld155 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld155_delete(HelloWorld155 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld156
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld156_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld156_init(HelloWorld156 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld156_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld156 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld156_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld156 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld156_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld156_topic_max_size(0) + 4u);

	if (size != HELLOWORLD156_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD156_SIZE:%d\n", size, HELLOWORLD156_SIZE);
		pr_warn("size is not equal to HELLOWORLD156_SIZE\n");

		return size;
	}

	return HELLOWORLD156_SIZE;
}

static bool HelloWorld156_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld156  *topic = (HelloWorld156  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld156_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld156_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld156 *topic = (HelloWorld156 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld156_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld156 *HelloWorld156_create(void)
{
	HelloWorld156 *sample;
	uint32_t size = sizeof(struct HelloWorld156);

	sample = (HelloWorld156 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld156_delete(HelloWorld156 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld157
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld157_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld157_init(HelloWorld157 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld157_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld157 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld157_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld157 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld157_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld157_topic_max_size(0) + 4u);

	if (size != HELLOWORLD157_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD157_SIZE:%d\n", size, HELLOWORLD157_SIZE);
		pr_warn("size is not equal to HELLOWORLD157_SIZE\n");

		return size;
	}

	return HELLOWORLD157_SIZE;
}

static bool HelloWorld157_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld157  *topic = (HelloWorld157  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld157_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld157_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld157 *topic = (HelloWorld157 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld157_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld157 *HelloWorld157_create(void)
{
	HelloWorld157 *sample;
	uint32_t size = sizeof(struct HelloWorld157);

	sample = (HelloWorld157 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld157_delete(HelloWorld157 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld158
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld158_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld158_init(HelloWorld158 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld158_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld158 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld158_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld158 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld158_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld158_topic_max_size(0) + 4u);

	if (size != HELLOWORLD158_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD158_SIZE:%d\n", size, HELLOWORLD158_SIZE);
		pr_warn("size is not equal to HELLOWORLD158_SIZE\n");

		return size;
	}

	return HELLOWORLD158_SIZE;
}

static bool HelloWorld158_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld158  *topic = (HelloWorld158  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld158_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld158_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld158 *topic = (HelloWorld158 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld158_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld158 *HelloWorld158_create(void)
{
	HelloWorld158 *sample;
	uint32_t size = sizeof(struct HelloWorld158);

	sample = (HelloWorld158 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld158_delete(HelloWorld158 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld159
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld159_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld159_init(HelloWorld159 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld159_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld159 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld159_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld159 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld159_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld159_topic_max_size(0) + 4u);

	if (size != HELLOWORLD159_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD159_SIZE:%d\n", size, HELLOWORLD159_SIZE);
		pr_warn("size is not equal to HELLOWORLD159_SIZE\n");

		return size;
	}

	return HELLOWORLD159_SIZE;
}

static bool HelloWorld159_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld159  *topic = (HelloWorld159  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld159_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld159_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld159 *topic = (HelloWorld159 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld159_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld159 *HelloWorld159_create(void)
{
	HelloWorld159 *sample;
	uint32_t size = sizeof(struct HelloWorld159);

	sample = (HelloWorld159 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld159_delete(HelloWorld159 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld160
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld160_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld160_init(HelloWorld160 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld160_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld160 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld160_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld160 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld160_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld160_topic_max_size(0) + 4u);

	if (size != HELLOWORLD160_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD160_SIZE:%d\n", size, HELLOWORLD160_SIZE);
		pr_warn("size is not equal to HELLOWORLD160_SIZE\n");

		return size;
	}

	return HELLOWORLD160_SIZE;
}

static bool HelloWorld160_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld160  *topic = (HelloWorld160  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld160_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld160_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld160 *topic = (HelloWorld160 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld160_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld160 *HelloWorld160_create(void)
{
	HelloWorld160 *sample;
	uint32_t size = sizeof(struct HelloWorld160);

	sample = (HelloWorld160 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld160_delete(HelloWorld160 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld161
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld161_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld161_init(HelloWorld161 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld161_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld161 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld161_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld161 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld161_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld161_topic_max_size(0) + 4u);

	if (size != HELLOWORLD161_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD161_SIZE:%d\n", size, HELLOWORLD161_SIZE);
		pr_warn("size is not equal to HELLOWORLD161_SIZE\n");

		return size;
	}

	return HELLOWORLD161_SIZE;
}

static bool HelloWorld161_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld161  *topic = (HelloWorld161  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld161_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld161_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld161 *topic = (HelloWorld161 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld161_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld161 *HelloWorld161_create(void)
{
	HelloWorld161 *sample;
	uint32_t size = sizeof(struct HelloWorld161);

	sample = (HelloWorld161 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld161_delete(HelloWorld161 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld162
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld162_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld162_init(HelloWorld162 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld162_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld162 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld162_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld162 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld162_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld162_topic_max_size(0) + 4u);

	if (size != HELLOWORLD162_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD162_SIZE:%d\n", size, HELLOWORLD162_SIZE);
		pr_warn("size is not equal to HELLOWORLD162_SIZE\n");

		return size;
	}

	return HELLOWORLD162_SIZE;
}

static bool HelloWorld162_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld162  *topic = (HelloWorld162  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld162_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld162_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld162 *topic = (HelloWorld162 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld162_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld162 *HelloWorld162_create(void)
{
	HelloWorld162 *sample;
	uint32_t size = sizeof(struct HelloWorld162);

	sample = (HelloWorld162 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld162_delete(HelloWorld162 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld163
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld163_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld163_init(HelloWorld163 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld163_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld163 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld163_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld163 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld163_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld163_topic_max_size(0) + 4u);

	if (size != HELLOWORLD163_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD163_SIZE:%d\n", size, HELLOWORLD163_SIZE);
		pr_warn("size is not equal to HELLOWORLD163_SIZE\n");

		return size;
	}

	return HELLOWORLD163_SIZE;
}

static bool HelloWorld163_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld163  *topic = (HelloWorld163  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld163_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld163_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld163 *topic = (HelloWorld163 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld163_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld163 *HelloWorld163_create(void)
{
	HelloWorld163 *sample;
	uint32_t size = sizeof(struct HelloWorld163);

	sample = (HelloWorld163 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld163_delete(HelloWorld163 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld164
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld164_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld164_init(HelloWorld164 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld164_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld164 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld164_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld164 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld164_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld164_topic_max_size(0) + 4u);

	if (size != HELLOWORLD164_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD164_SIZE:%d\n", size, HELLOWORLD164_SIZE);
		pr_warn("size is not equal to HELLOWORLD164_SIZE\n");

		return size;
	}

	return HELLOWORLD164_SIZE;
}

static bool HelloWorld164_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld164  *topic = (HelloWorld164  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld164_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld164_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld164 *topic = (HelloWorld164 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld164_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld164 *HelloWorld164_create(void)
{
	HelloWorld164 *sample;
	uint32_t size = sizeof(struct HelloWorld164);

	sample = (HelloWorld164 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld164_delete(HelloWorld164 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld165
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld165_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld165_init(HelloWorld165 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld165_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld165 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld165_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld165 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld165_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld165_topic_max_size(0) + 4u);

	if (size != HELLOWORLD165_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD165_SIZE:%d\n", size, HELLOWORLD165_SIZE);
		pr_warn("size is not equal to HELLOWORLD165_SIZE\n");

		return size;
	}

	return HELLOWORLD165_SIZE;
}

static bool HelloWorld165_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld165  *topic = (HelloWorld165  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld165_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld165_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld165 *topic = (HelloWorld165 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld165_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld165 *HelloWorld165_create(void)
{
	HelloWorld165 *sample;
	uint32_t size = sizeof(struct HelloWorld165);

	sample = (HelloWorld165 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld165_delete(HelloWorld165 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld166
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld166_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld166_init(HelloWorld166 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld166_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld166 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld166_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld166 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld166_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld166_topic_max_size(0) + 4u);

	if (size != HELLOWORLD166_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD166_SIZE:%d\n", size, HELLOWORLD166_SIZE);
		pr_warn("size is not equal to HELLOWORLD166_SIZE\n");

		return size;
	}

	return HELLOWORLD166_SIZE;
}

static bool HelloWorld166_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld166  *topic = (HelloWorld166  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld166_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld166_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld166 *topic = (HelloWorld166 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld166_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld166 *HelloWorld166_create(void)
{
	HelloWorld166 *sample;
	uint32_t size = sizeof(struct HelloWorld166);

	sample = (HelloWorld166 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld166_delete(HelloWorld166 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld167
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld167_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld167_init(HelloWorld167 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld167_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld167 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld167_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld167 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld167_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld167_topic_max_size(0) + 4u);

	if (size != HELLOWORLD167_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD167_SIZE:%d\n", size, HELLOWORLD167_SIZE);
		pr_warn("size is not equal to HELLOWORLD167_SIZE\n");

		return size;
	}

	return HELLOWORLD167_SIZE;
}

static bool HelloWorld167_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld167  *topic = (HelloWorld167  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld167_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld167_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld167 *topic = (HelloWorld167 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld167_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld167 *HelloWorld167_create(void)
{
	HelloWorld167 *sample;
	uint32_t size = sizeof(struct HelloWorld167);

	sample = (HelloWorld167 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld167_delete(HelloWorld167 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld168
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld168_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld168_init(HelloWorld168 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld168_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld168 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld168_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld168 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld168_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld168_topic_max_size(0) + 4u);

	if (size != HELLOWORLD168_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD168_SIZE:%d\n", size, HELLOWORLD168_SIZE);
		pr_warn("size is not equal to HELLOWORLD168_SIZE\n");

		return size;
	}

	return HELLOWORLD168_SIZE;
}

static bool HelloWorld168_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld168  *topic = (HelloWorld168  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld168_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld168_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld168 *topic = (HelloWorld168 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld168_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld168 *HelloWorld168_create(void)
{
	HelloWorld168 *sample;
	uint32_t size = sizeof(struct HelloWorld168);

	sample = (HelloWorld168 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld168_delete(HelloWorld168 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld169
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld169_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld169_init(HelloWorld169 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld169_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld169 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld169_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld169 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld169_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld169_topic_max_size(0) + 4u);

	if (size != HELLOWORLD169_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD169_SIZE:%d\n", size, HELLOWORLD169_SIZE);
		pr_warn("size is not equal to HELLOWORLD169_SIZE\n");

		return size;
	}

	return HELLOWORLD169_SIZE;
}

static bool HelloWorld169_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld169  *topic = (HelloWorld169  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld169_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld169_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld169 *topic = (HelloWorld169 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld169_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld169 *HelloWorld169_create(void)
{
	HelloWorld169 *sample;
	uint32_t size = sizeof(struct HelloWorld169);

	sample = (HelloWorld169 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld169_delete(HelloWorld169 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld170
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld170_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld170_init(HelloWorld170 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld170_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld170 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld170_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld170 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld170_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld170_topic_max_size(0) + 4u);

	if (size != HELLOWORLD170_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD170_SIZE:%d\n", size, HELLOWORLD170_SIZE);
		pr_warn("size is not equal to HELLOWORLD170_SIZE\n");

		return size;
	}

	return HELLOWORLD170_SIZE;
}

static bool HelloWorld170_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld170  *topic = (HelloWorld170  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld170_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld170_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld170 *topic = (HelloWorld170 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld170_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld170 *HelloWorld170_create(void)
{
	HelloWorld170 *sample;
	uint32_t size = sizeof(struct HelloWorld170);

	sample = (HelloWorld170 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld170_delete(HelloWorld170 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld171
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld171_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld171_init(HelloWorld171 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld171_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld171 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld171_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld171 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld171_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld171_topic_max_size(0) + 4u);

	if (size != HELLOWORLD171_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD171_SIZE:%d\n", size, HELLOWORLD171_SIZE);
		pr_warn("size is not equal to HELLOWORLD171_SIZE\n");

		return size;
	}

	return HELLOWORLD171_SIZE;
}

static bool HelloWorld171_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld171  *topic = (HelloWorld171  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld171_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld171_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld171 *topic = (HelloWorld171 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld171_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld171 *HelloWorld171_create(void)
{
	HelloWorld171 *sample;
	uint32_t size = sizeof(struct HelloWorld171);

	sample = (HelloWorld171 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld171_delete(HelloWorld171 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld172
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld172_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld172_init(HelloWorld172 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld172_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld172 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld172_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld172 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld172_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld172_topic_max_size(0) + 4u);

	if (size != HELLOWORLD172_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD172_SIZE:%d\n", size, HELLOWORLD172_SIZE);
		pr_warn("size is not equal to HELLOWORLD172_SIZE\n");

		return size;
	}

	return HELLOWORLD172_SIZE;
}

static bool HelloWorld172_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld172  *topic = (HelloWorld172  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld172_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld172_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld172 *topic = (HelloWorld172 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld172_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld172 *HelloWorld172_create(void)
{
	HelloWorld172 *sample;
	uint32_t size = sizeof(struct HelloWorld172);

	sample = (HelloWorld172 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld172_delete(HelloWorld172 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld173
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld173_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld173_init(HelloWorld173 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld173_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld173 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld173_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld173 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld173_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld173_topic_max_size(0) + 4u);

	if (size != HELLOWORLD173_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD173_SIZE:%d\n", size, HELLOWORLD173_SIZE);
		pr_warn("size is not equal to HELLOWORLD173_SIZE\n");

		return size;
	}

	return HELLOWORLD173_SIZE;
}

static bool HelloWorld173_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld173  *topic = (HelloWorld173  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld173_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld173_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld173 *topic = (HelloWorld173 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld173_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld173 *HelloWorld173_create(void)
{
	HelloWorld173 *sample;
	uint32_t size = sizeof(struct HelloWorld173);

	sample = (HelloWorld173 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld173_delete(HelloWorld173 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld174
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld174_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld174_init(HelloWorld174 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld174_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld174 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld174_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld174 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld174_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld174_topic_max_size(0) + 4u);

	if (size != HELLOWORLD174_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD174_SIZE:%d\n", size, HELLOWORLD174_SIZE);
		pr_warn("size is not equal to HELLOWORLD174_SIZE\n");

		return size;
	}

	return HELLOWORLD174_SIZE;
}

static bool HelloWorld174_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld174  *topic = (HelloWorld174  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld174_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld174_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld174 *topic = (HelloWorld174 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld174_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld174 *HelloWorld174_create(void)
{
	HelloWorld174 *sample;
	uint32_t size = sizeof(struct HelloWorld174);

	sample = (HelloWorld174 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld174_delete(HelloWorld174 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld175
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld175_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld175_init(HelloWorld175 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld175_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld175 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld175_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld175 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld175_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld175_topic_max_size(0) + 4u);

	if (size != HELLOWORLD175_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD175_SIZE:%d\n", size, HELLOWORLD175_SIZE);
		pr_warn("size is not equal to HELLOWORLD175_SIZE\n");

		return size;
	}

	return HELLOWORLD175_SIZE;
}

static bool HelloWorld175_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld175  *topic = (HelloWorld175  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld175_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld175_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld175 *topic = (HelloWorld175 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld175_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld175 *HelloWorld175_create(void)
{
	HelloWorld175 *sample;
	uint32_t size = sizeof(struct HelloWorld175);

	sample = (HelloWorld175 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld175_delete(HelloWorld175 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld176
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld176_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld176_init(HelloWorld176 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld176_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld176 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld176_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld176 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld176_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld176_topic_max_size(0) + 4u);

	if (size != HELLOWORLD176_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD176_SIZE:%d\n", size, HELLOWORLD176_SIZE);
		pr_warn("size is not equal to HELLOWORLD176_SIZE\n");

		return size;
	}

	return HELLOWORLD176_SIZE;
}

static bool HelloWorld176_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld176  *topic = (HelloWorld176  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld176_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld176_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld176 *topic = (HelloWorld176 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld176_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld176 *HelloWorld176_create(void)
{
	HelloWorld176 *sample;
	uint32_t size = sizeof(struct HelloWorld176);

	sample = (HelloWorld176 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld176_delete(HelloWorld176 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld177
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld177_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld177_init(HelloWorld177 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld177_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld177 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld177_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld177 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld177_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld177_topic_max_size(0) + 4u);

	if (size != HELLOWORLD177_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD177_SIZE:%d\n", size, HELLOWORLD177_SIZE);
		pr_warn("size is not equal to HELLOWORLD177_SIZE\n");

		return size;
	}

	return HELLOWORLD177_SIZE;
}

static bool HelloWorld177_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld177  *topic = (HelloWorld177  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld177_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld177_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld177 *topic = (HelloWorld177 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld177_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld177 *HelloWorld177_create(void)
{
	HelloWorld177 *sample;
	uint32_t size = sizeof(struct HelloWorld177);

	sample = (HelloWorld177 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld177_delete(HelloWorld177 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld178
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld178_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld178_init(HelloWorld178 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld178_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld178 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld178_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld178 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld178_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld178_topic_max_size(0) + 4u);

	if (size != HELLOWORLD178_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD178_SIZE:%d\n", size, HELLOWORLD178_SIZE);
		pr_warn("size is not equal to HELLOWORLD178_SIZE\n");

		return size;
	}

	return HELLOWORLD178_SIZE;
}

static bool HelloWorld178_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld178  *topic = (HelloWorld178  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld178_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld178_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld178 *topic = (HelloWorld178 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld178_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld178 *HelloWorld178_create(void)
{
	HelloWorld178 *sample;
	uint32_t size = sizeof(struct HelloWorld178);

	sample = (HelloWorld178 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld178_delete(HelloWorld178 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld179
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld179_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld179_init(HelloWorld179 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld179_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld179 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld179_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld179 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld179_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld179_topic_max_size(0) + 4u);

	if (size != HELLOWORLD179_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD179_SIZE:%d\n", size, HELLOWORLD179_SIZE);
		pr_warn("size is not equal to HELLOWORLD179_SIZE\n");

		return size;
	}

	return HELLOWORLD179_SIZE;
}

static bool HelloWorld179_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld179  *topic = (HelloWorld179  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld179_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld179_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld179 *topic = (HelloWorld179 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld179_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld179 *HelloWorld179_create(void)
{
	HelloWorld179 *sample;
	uint32_t size = sizeof(struct HelloWorld179);

	sample = (HelloWorld179 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld179_delete(HelloWorld179 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld180
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld180_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld180_init(HelloWorld180 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld180_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld180 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld180_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld180 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld180_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld180_topic_max_size(0) + 4u);

	if (size != HELLOWORLD180_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD180_SIZE:%d\n", size, HELLOWORLD180_SIZE);
		pr_warn("size is not equal to HELLOWORLD180_SIZE\n");

		return size;
	}

	return HELLOWORLD180_SIZE;
}

static bool HelloWorld180_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld180  *topic = (HelloWorld180  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld180_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld180_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld180 *topic = (HelloWorld180 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld180_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld180 *HelloWorld180_create(void)
{
	HelloWorld180 *sample;
	uint32_t size = sizeof(struct HelloWorld180);

	sample = (HelloWorld180 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld180_delete(HelloWorld180 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld181
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld181_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld181_init(HelloWorld181 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld181_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld181 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld181_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld181 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld181_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld181_topic_max_size(0) + 4u);

	if (size != HELLOWORLD181_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD181_SIZE:%d\n", size, HELLOWORLD181_SIZE);
		pr_warn("size is not equal to HELLOWORLD181_SIZE\n");

		return size;
	}

	return HELLOWORLD181_SIZE;
}

static bool HelloWorld181_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld181  *topic = (HelloWorld181  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld181_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld181_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld181 *topic = (HelloWorld181 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld181_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld181 *HelloWorld181_create(void)
{
	HelloWorld181 *sample;
	uint32_t size = sizeof(struct HelloWorld181);

	sample = (HelloWorld181 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld181_delete(HelloWorld181 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld182
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld182_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld182_init(HelloWorld182 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld182_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld182 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld182_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld182 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld182_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld182_topic_max_size(0) + 4u);

	if (size != HELLOWORLD182_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD182_SIZE:%d\n", size, HELLOWORLD182_SIZE);
		pr_warn("size is not equal to HELLOWORLD182_SIZE\n");

		return size;
	}

	return HELLOWORLD182_SIZE;
}

static bool HelloWorld182_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld182  *topic = (HelloWorld182  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld182_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld182_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld182 *topic = (HelloWorld182 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld182_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld182 *HelloWorld182_create(void)
{
	HelloWorld182 *sample;
	uint32_t size = sizeof(struct HelloWorld182);

	sample = (HelloWorld182 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld182_delete(HelloWorld182 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld183
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld183_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld183_init(HelloWorld183 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld183_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld183 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld183_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld183 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld183_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld183_topic_max_size(0) + 4u);

	if (size != HELLOWORLD183_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD183_SIZE:%d\n", size, HELLOWORLD183_SIZE);
		pr_warn("size is not equal to HELLOWORLD183_SIZE\n");

		return size;
	}

	return HELLOWORLD183_SIZE;
}

static bool HelloWorld183_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld183  *topic = (HelloWorld183  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld183_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld183_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld183 *topic = (HelloWorld183 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld183_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld183 *HelloWorld183_create(void)
{
	HelloWorld183 *sample;
	uint32_t size = sizeof(struct HelloWorld183);

	sample = (HelloWorld183 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld183_delete(HelloWorld183 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld184
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld184_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld184_init(HelloWorld184 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld184_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld184 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld184_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld184 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld184_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld184_topic_max_size(0) + 4u);

	if (size != HELLOWORLD184_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD184_SIZE:%d\n", size, HELLOWORLD184_SIZE);
		pr_warn("size is not equal to HELLOWORLD184_SIZE\n");

		return size;
	}

	return HELLOWORLD184_SIZE;
}

static bool HelloWorld184_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld184  *topic = (HelloWorld184  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld184_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld184_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld184 *topic = (HelloWorld184 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld184_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld184 *HelloWorld184_create(void)
{
	HelloWorld184 *sample;
	uint32_t size = sizeof(struct HelloWorld184);

	sample = (HelloWorld184 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld184_delete(HelloWorld184 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld185
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld185_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld185_init(HelloWorld185 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld185_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld185 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld185_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld185 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld185_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld185_topic_max_size(0) + 4u);

	if (size != HELLOWORLD185_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD185_SIZE:%d\n", size, HELLOWORLD185_SIZE);
		pr_warn("size is not equal to HELLOWORLD185_SIZE\n");

		return size;
	}

	return HELLOWORLD185_SIZE;
}

static bool HelloWorld185_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld185  *topic = (HelloWorld185  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld185_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld185_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld185 *topic = (HelloWorld185 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld185_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld185 *HelloWorld185_create(void)
{
	HelloWorld185 *sample;
	uint32_t size = sizeof(struct HelloWorld185);

	sample = (HelloWorld185 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld185_delete(HelloWorld185 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld186
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld186_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld186_init(HelloWorld186 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld186_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld186 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld186_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld186 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld186_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld186_topic_max_size(0) + 4u);

	if (size != HELLOWORLD186_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD186_SIZE:%d\n", size, HELLOWORLD186_SIZE);
		pr_warn("size is not equal to HELLOWORLD186_SIZE\n");

		return size;
	}

	return HELLOWORLD186_SIZE;
}

static bool HelloWorld186_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld186  *topic = (HelloWorld186  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld186_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld186_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld186 *topic = (HelloWorld186 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld186_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld186 *HelloWorld186_create(void)
{
	HelloWorld186 *sample;
	uint32_t size = sizeof(struct HelloWorld186);

	sample = (HelloWorld186 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld186_delete(HelloWorld186 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld187
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld187_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld187_init(HelloWorld187 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld187_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld187 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld187_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld187 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld187_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld187_topic_max_size(0) + 4u);

	if (size != HELLOWORLD187_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD187_SIZE:%d\n", size, HELLOWORLD187_SIZE);
		pr_warn("size is not equal to HELLOWORLD187_SIZE\n");

		return size;
	}

	return HELLOWORLD187_SIZE;
}

static bool HelloWorld187_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld187  *topic = (HelloWorld187  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld187_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld187_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld187 *topic = (HelloWorld187 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld187_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld187 *HelloWorld187_create(void)
{
	HelloWorld187 *sample;
	uint32_t size = sizeof(struct HelloWorld187);

	sample = (HelloWorld187 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld187_delete(HelloWorld187 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld188
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld188_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld188_init(HelloWorld188 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld188_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld188 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld188_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld188 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld188_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld188_topic_max_size(0) + 4u);

	if (size != HELLOWORLD188_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD188_SIZE:%d\n", size, HELLOWORLD188_SIZE);
		pr_warn("size is not equal to HELLOWORLD188_SIZE\n");

		return size;
	}

	return HELLOWORLD188_SIZE;
}

static bool HelloWorld188_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld188  *topic = (HelloWorld188  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld188_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld188_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld188 *topic = (HelloWorld188 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld188_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld188 *HelloWorld188_create(void)
{
	HelloWorld188 *sample;
	uint32_t size = sizeof(struct HelloWorld188);

	sample = (HelloWorld188 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld188_delete(HelloWorld188 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld189
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld189_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld189_init(HelloWorld189 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld189_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld189 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld189_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld189 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld189_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld189_topic_max_size(0) + 4u);

	if (size != HELLOWORLD189_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD189_SIZE:%d\n", size, HELLOWORLD189_SIZE);
		pr_warn("size is not equal to HELLOWORLD189_SIZE\n");

		return size;
	}

	return HELLOWORLD189_SIZE;
}

static bool HelloWorld189_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld189  *topic = (HelloWorld189  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld189_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld189_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld189 *topic = (HelloWorld189 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld189_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld189 *HelloWorld189_create(void)
{
	HelloWorld189 *sample;
	uint32_t size = sizeof(struct HelloWorld189);

	sample = (HelloWorld189 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld189_delete(HelloWorld189 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld190
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld190_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld190_init(HelloWorld190 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld190_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld190 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld190_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld190 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld190_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld190_topic_max_size(0) + 4u);

	if (size != HELLOWORLD190_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD190_SIZE:%d\n", size, HELLOWORLD190_SIZE);
		pr_warn("size is not equal to HELLOWORLD190_SIZE\n");

		return size;
	}

	return HELLOWORLD190_SIZE;
}

static bool HelloWorld190_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld190  *topic = (HelloWorld190  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld190_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld190_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld190 *topic = (HelloWorld190 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld190_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld190 *HelloWorld190_create(void)
{
	HelloWorld190 *sample;
	uint32_t size = sizeof(struct HelloWorld190);

	sample = (HelloWorld190 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld190_delete(HelloWorld190 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld191
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld191_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld191_init(HelloWorld191 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld191_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld191 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld191_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld191 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld191_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld191_topic_max_size(0) + 4u);

	if (size != HELLOWORLD191_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD191_SIZE:%d\n", size, HELLOWORLD191_SIZE);
		pr_warn("size is not equal to HELLOWORLD191_SIZE\n");

		return size;
	}

	return HELLOWORLD191_SIZE;
}

static bool HelloWorld191_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld191  *topic = (HelloWorld191  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld191_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld191_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld191 *topic = (HelloWorld191 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld191_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld191 *HelloWorld191_create(void)
{
	HelloWorld191 *sample;
	uint32_t size = sizeof(struct HelloWorld191);

	sample = (HelloWorld191 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld191_delete(HelloWorld191 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld192
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld192_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld192_init(HelloWorld192 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld192_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld192 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld192_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld192 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld192_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld192_topic_max_size(0) + 4u);

	if (size != HELLOWORLD192_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD192_SIZE:%d\n", size, HELLOWORLD192_SIZE);
		pr_warn("size is not equal to HELLOWORLD192_SIZE\n");

		return size;
	}

	return HELLOWORLD192_SIZE;
}

static bool HelloWorld192_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld192  *topic = (HelloWorld192  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld192_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld192_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld192 *topic = (HelloWorld192 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld192_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld192 *HelloWorld192_create(void)
{
	HelloWorld192 *sample;
	uint32_t size = sizeof(struct HelloWorld192);

	sample = (HelloWorld192 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld192_delete(HelloWorld192 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld193
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld193_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld193_init(HelloWorld193 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld193_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld193 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld193_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld193 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld193_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld193_topic_max_size(0) + 4u);

	if (size != HELLOWORLD193_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD193_SIZE:%d\n", size, HELLOWORLD193_SIZE);
		pr_warn("size is not equal to HELLOWORLD193_SIZE\n");

		return size;
	}

	return HELLOWORLD193_SIZE;
}

static bool HelloWorld193_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld193  *topic = (HelloWorld193  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld193_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld193_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld193 *topic = (HelloWorld193 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld193_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld193 *HelloWorld193_create(void)
{
	HelloWorld193 *sample;
	uint32_t size = sizeof(struct HelloWorld193);

	sample = (HelloWorld193 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld193_delete(HelloWorld193 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld194
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld194_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld194_init(HelloWorld194 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld194_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld194 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld194_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld194 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld194_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld194_topic_max_size(0) + 4u);

	if (size != HELLOWORLD194_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD194_SIZE:%d\n", size, HELLOWORLD194_SIZE);
		pr_warn("size is not equal to HELLOWORLD194_SIZE\n");

		return size;
	}

	return HELLOWORLD194_SIZE;
}

static bool HelloWorld194_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld194  *topic = (HelloWorld194  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld194_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld194_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld194 *topic = (HelloWorld194 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld194_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld194 *HelloWorld194_create(void)
{
	HelloWorld194 *sample;
	uint32_t size = sizeof(struct HelloWorld194);

	sample = (HelloWorld194 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld194_delete(HelloWorld194 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld195
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld195_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld195_init(HelloWorld195 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld195_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld195 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld195_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld195 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld195_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld195_topic_max_size(0) + 4u);

	if (size != HELLOWORLD195_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD195_SIZE:%d\n", size, HELLOWORLD195_SIZE);
		pr_warn("size is not equal to HELLOWORLD195_SIZE\n");

		return size;
	}

	return HELLOWORLD195_SIZE;
}

static bool HelloWorld195_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld195  *topic = (HelloWorld195  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld195_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld195_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld195 *topic = (HelloWorld195 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld195_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld195 *HelloWorld195_create(void)
{
	HelloWorld195 *sample;
	uint32_t size = sizeof(struct HelloWorld195);

	sample = (HelloWorld195 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld195_delete(HelloWorld195 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld196
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld196_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld196_init(HelloWorld196 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld196_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld196 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld196_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld196 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld196_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld196_topic_max_size(0) + 4u);

	if (size != HELLOWORLD196_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD196_SIZE:%d\n", size, HELLOWORLD196_SIZE);
		pr_warn("size is not equal to HELLOWORLD196_SIZE\n");

		return size;
	}

	return HELLOWORLD196_SIZE;
}

static bool HelloWorld196_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld196  *topic = (HelloWorld196  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld196_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld196_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld196 *topic = (HelloWorld196 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld196_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld196 *HelloWorld196_create(void)
{
	HelloWorld196 *sample;
	uint32_t size = sizeof(struct HelloWorld196);

	sample = (HelloWorld196 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld196_delete(HelloWorld196 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld197
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld197_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld197_init(HelloWorld197 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld197_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld197 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld197_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld197 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld197_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld197_topic_max_size(0) + 4u);

	if (size != HELLOWORLD197_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD197_SIZE:%d\n", size, HELLOWORLD197_SIZE);
		pr_warn("size is not equal to HELLOWORLD197_SIZE\n");

		return size;
	}

	return HELLOWORLD197_SIZE;
}

static bool HelloWorld197_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld197  *topic = (HelloWorld197  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld197_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld197_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld197 *topic = (HelloWorld197 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld197_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld197 *HelloWorld197_create(void)
{
	HelloWorld197 *sample;
	uint32_t size = sizeof(struct HelloWorld197);

	sample = (HelloWorld197 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld197_delete(HelloWorld197 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld198
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld198_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld198_init(HelloWorld198 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld198_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld198 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld198_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld198 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld198_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld198_topic_max_size(0) + 4u);

	if (size != HELLOWORLD198_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD198_SIZE:%d\n", size, HELLOWORLD198_SIZE);
		pr_warn("size is not equal to HELLOWORLD198_SIZE\n");

		return size;
	}

	return HELLOWORLD198_SIZE;
}

static bool HelloWorld198_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld198  *topic = (HelloWorld198  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld198_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld198_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld198 *topic = (HelloWorld198 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld198_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld198 *HelloWorld198_create(void)
{
	HelloWorld198 *sample;
	uint32_t size = sizeof(struct HelloWorld198);

	sample = (HelloWorld198 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld198_delete(HelloWorld198 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld199
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld199_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld199_init(HelloWorld199 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld199_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld199 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld199_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld199 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld199_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld199_topic_max_size(0) + 4u);

	if (size != HELLOWORLD199_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD199_SIZE:%d\n", size, HELLOWORLD199_SIZE);
		pr_warn("size is not equal to HELLOWORLD199_SIZE\n");

		return size;
	}

	return HELLOWORLD199_SIZE;
}

static bool HelloWorld199_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld199  *topic = (HelloWorld199  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld199_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld199_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld199 *topic = (HelloWorld199 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld199_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld199 *HelloWorld199_create(void)
{
	HelloWorld199 *sample;
	uint32_t size = sizeof(struct HelloWorld199);

	sample = (HelloWorld199 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld199_delete(HelloWorld199 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld200
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld200_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld200_init(HelloWorld200 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld200_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld200 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld200_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld200 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld200_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld200_topic_max_size(0) + 4u);

	if (size != HELLOWORLD200_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD200_SIZE:%d\n", size, HELLOWORLD200_SIZE);
		pr_warn("size is not equal to HELLOWORLD200_SIZE\n");

		return size;
	}

	return HELLOWORLD200_SIZE;
}

static bool HelloWorld200_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld200  *topic = (HelloWorld200  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld200_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld200_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld200 *topic = (HelloWorld200 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld200_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld200 *HelloWorld200_create(void)
{
	HelloWorld200 *sample;
	uint32_t size = sizeof(struct HelloWorld200);

	sample = (HelloWorld200 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld200_delete(HelloWorld200 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld201
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld201_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld201_init(HelloWorld201 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld201_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld201 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld201_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld201 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld201_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld201_topic_max_size(0) + 4u);

	if (size != HELLOWORLD201_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD201_SIZE:%d\n", size, HELLOWORLD201_SIZE);
		pr_warn("size is not equal to HELLOWORLD201_SIZE\n");

		return size;
	}

	return HELLOWORLD201_SIZE;
}

static bool HelloWorld201_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld201  *topic = (HelloWorld201  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld201_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld201_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld201 *topic = (HelloWorld201 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld201_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld201 *HelloWorld201_create(void)
{
	HelloWorld201 *sample;
	uint32_t size = sizeof(struct HelloWorld201);

	sample = (HelloWorld201 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld201_delete(HelloWorld201 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld202
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld202_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld202_init(HelloWorld202 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld202_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld202 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld202_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld202 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld202_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld202_topic_max_size(0) + 4u);

	if (size != HELLOWORLD202_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD202_SIZE:%d\n", size, HELLOWORLD202_SIZE);
		pr_warn("size is not equal to HELLOWORLD202_SIZE\n");

		return size;
	}

	return HELLOWORLD202_SIZE;
}

static bool HelloWorld202_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld202  *topic = (HelloWorld202  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld202_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld202_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld202 *topic = (HelloWorld202 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld202_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld202 *HelloWorld202_create(void)
{
	HelloWorld202 *sample;
	uint32_t size = sizeof(struct HelloWorld202);

	sample = (HelloWorld202 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld202_delete(HelloWorld202 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld203
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld203_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld203_init(HelloWorld203 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld203_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld203 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld203_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld203 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld203_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld203_topic_max_size(0) + 4u);

	if (size != HELLOWORLD203_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD203_SIZE:%d\n", size, HELLOWORLD203_SIZE);
		pr_warn("size is not equal to HELLOWORLD203_SIZE\n");

		return size;
	}

	return HELLOWORLD203_SIZE;
}

static bool HelloWorld203_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld203  *topic = (HelloWorld203  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld203_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld203_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld203 *topic = (HelloWorld203 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld203_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld203 *HelloWorld203_create(void)
{
	HelloWorld203 *sample;
	uint32_t size = sizeof(struct HelloWorld203);

	sample = (HelloWorld203 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld203_delete(HelloWorld203 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld204
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld204_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld204_init(HelloWorld204 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld204_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld204 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld204_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld204 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld204_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld204_topic_max_size(0) + 4u);

	if (size != HELLOWORLD204_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD204_SIZE:%d\n", size, HELLOWORLD204_SIZE);
		pr_warn("size is not equal to HELLOWORLD204_SIZE\n");

		return size;
	}

	return HELLOWORLD204_SIZE;
}

static bool HelloWorld204_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld204  *topic = (HelloWorld204  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld204_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld204_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld204 *topic = (HelloWorld204 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld204_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld204 *HelloWorld204_create(void)
{
	HelloWorld204 *sample;
	uint32_t size = sizeof(struct HelloWorld204);

	sample = (HelloWorld204 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld204_delete(HelloWorld204 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld205
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld205_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld205_init(HelloWorld205 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld205_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld205 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld205_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld205 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld205_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld205_topic_max_size(0) + 4u);

	if (size != HELLOWORLD205_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD205_SIZE:%d\n", size, HELLOWORLD205_SIZE);
		pr_warn("size is not equal to HELLOWORLD205_SIZE\n");

		return size;
	}

	return HELLOWORLD205_SIZE;
}

static bool HelloWorld205_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld205  *topic = (HelloWorld205  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld205_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld205_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld205 *topic = (HelloWorld205 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld205_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld205 *HelloWorld205_create(void)
{
	HelloWorld205 *sample;
	uint32_t size = sizeof(struct HelloWorld205);

	sample = (HelloWorld205 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld205_delete(HelloWorld205 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld206
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld206_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld206_init(HelloWorld206 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld206_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld206 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld206_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld206 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld206_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld206_topic_max_size(0) + 4u);

	if (size != HELLOWORLD206_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD206_SIZE:%d\n", size, HELLOWORLD206_SIZE);
		pr_warn("size is not equal to HELLOWORLD206_SIZE\n");

		return size;
	}

	return HELLOWORLD206_SIZE;
}

static bool HelloWorld206_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld206  *topic = (HelloWorld206  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld206_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld206_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld206 *topic = (HelloWorld206 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld206_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld206 *HelloWorld206_create(void)
{
	HelloWorld206 *sample;
	uint32_t size = sizeof(struct HelloWorld206);

	sample = (HelloWorld206 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld206_delete(HelloWorld206 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld207
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld207_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld207_init(HelloWorld207 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld207_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld207 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld207_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld207 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld207_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld207_topic_max_size(0) + 4u);

	if (size != HELLOWORLD207_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD207_SIZE:%d\n", size, HELLOWORLD207_SIZE);
		pr_warn("size is not equal to HELLOWORLD207_SIZE\n");

		return size;
	}

	return HELLOWORLD207_SIZE;
}

static bool HelloWorld207_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld207  *topic = (HelloWorld207  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld207_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld207_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld207 *topic = (HelloWorld207 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld207_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld207 *HelloWorld207_create(void)
{
	HelloWorld207 *sample;
	uint32_t size = sizeof(struct HelloWorld207);

	sample = (HelloWorld207 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld207_delete(HelloWorld207 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld208
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld208_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld208_init(HelloWorld208 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld208_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld208 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld208_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld208 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld208_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld208_topic_max_size(0) + 4u);

	if (size != HELLOWORLD208_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD208_SIZE:%d\n", size, HELLOWORLD208_SIZE);
		pr_warn("size is not equal to HELLOWORLD208_SIZE\n");

		return size;
	}

	return HELLOWORLD208_SIZE;
}

static bool HelloWorld208_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld208  *topic = (HelloWorld208  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld208_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld208_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld208 *topic = (HelloWorld208 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld208_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld208 *HelloWorld208_create(void)
{
	HelloWorld208 *sample;
	uint32_t size = sizeof(struct HelloWorld208);

	sample = (HelloWorld208 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld208_delete(HelloWorld208 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld209
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld209_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld209_init(HelloWorld209 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld209_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld209 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld209_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld209 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld209_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld209_topic_max_size(0) + 4u);

	if (size != HELLOWORLD209_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD209_SIZE:%d\n", size, HELLOWORLD209_SIZE);
		pr_warn("size is not equal to HELLOWORLD209_SIZE\n");

		return size;
	}

	return HELLOWORLD209_SIZE;
}

static bool HelloWorld209_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld209  *topic = (HelloWorld209  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld209_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld209_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld209 *topic = (HelloWorld209 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld209_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld209 *HelloWorld209_create(void)
{
	HelloWorld209 *sample;
	uint32_t size = sizeof(struct HelloWorld209);

	sample = (HelloWorld209 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld209_delete(HelloWorld209 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld210
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld210_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld210_init(HelloWorld210 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld210_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld210 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld210_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld210 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld210_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld210_topic_max_size(0) + 4u);

	if (size != HELLOWORLD210_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD210_SIZE:%d\n", size, HELLOWORLD210_SIZE);
		pr_warn("size is not equal to HELLOWORLD210_SIZE\n");

		return size;
	}

	return HELLOWORLD210_SIZE;
}

static bool HelloWorld210_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld210  *topic = (HelloWorld210  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld210_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld210_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld210 *topic = (HelloWorld210 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld210_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld210 *HelloWorld210_create(void)
{
	HelloWorld210 *sample;
	uint32_t size = sizeof(struct HelloWorld210);

	sample = (HelloWorld210 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld210_delete(HelloWorld210 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld211
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld211_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld211_init(HelloWorld211 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld211_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld211 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld211_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld211 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld211_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld211_topic_max_size(0) + 4u);

	if (size != HELLOWORLD211_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD211_SIZE:%d\n", size, HELLOWORLD211_SIZE);
		pr_warn("size is not equal to HELLOWORLD211_SIZE\n");

		return size;
	}

	return HELLOWORLD211_SIZE;
}

static bool HelloWorld211_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld211  *topic = (HelloWorld211  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld211_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld211_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld211 *topic = (HelloWorld211 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld211_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld211 *HelloWorld211_create(void)
{
	HelloWorld211 *sample;
	uint32_t size = sizeof(struct HelloWorld211);

	sample = (HelloWorld211 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld211_delete(HelloWorld211 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld212
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld212_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld212_init(HelloWorld212 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld212_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld212 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld212_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld212 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld212_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld212_topic_max_size(0) + 4u);

	if (size != HELLOWORLD212_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD212_SIZE:%d\n", size, HELLOWORLD212_SIZE);
		pr_warn("size is not equal to HELLOWORLD212_SIZE\n");

		return size;
	}

	return HELLOWORLD212_SIZE;
}

static bool HelloWorld212_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld212  *topic = (HelloWorld212  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld212_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld212_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld212 *topic = (HelloWorld212 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld212_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld212 *HelloWorld212_create(void)
{
	HelloWorld212 *sample;
	uint32_t size = sizeof(struct HelloWorld212);

	sample = (HelloWorld212 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld212_delete(HelloWorld212 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld213
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld213_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld213_init(HelloWorld213 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld213_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld213 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld213_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld213 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld213_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld213_topic_max_size(0) + 4u);

	if (size != HELLOWORLD213_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD213_SIZE:%d\n", size, HELLOWORLD213_SIZE);
		pr_warn("size is not equal to HELLOWORLD213_SIZE\n");

		return size;
	}

	return HELLOWORLD213_SIZE;
}

static bool HelloWorld213_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld213  *topic = (HelloWorld213  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld213_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld213_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld213 *topic = (HelloWorld213 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld213_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld213 *HelloWorld213_create(void)
{
	HelloWorld213 *sample;
	uint32_t size = sizeof(struct HelloWorld213);

	sample = (HelloWorld213 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld213_delete(HelloWorld213 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld214
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld214_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld214_init(HelloWorld214 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld214_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld214 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld214_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld214 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld214_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld214_topic_max_size(0) + 4u);

	if (size != HELLOWORLD214_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD214_SIZE:%d\n", size, HELLOWORLD214_SIZE);
		pr_warn("size is not equal to HELLOWORLD214_SIZE\n");

		return size;
	}

	return HELLOWORLD214_SIZE;
}

static bool HelloWorld214_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld214  *topic = (HelloWorld214  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld214_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld214_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld214 *topic = (HelloWorld214 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld214_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld214 *HelloWorld214_create(void)
{
	HelloWorld214 *sample;
	uint32_t size = sizeof(struct HelloWorld214);

	sample = (HelloWorld214 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld214_delete(HelloWorld214 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld215
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld215_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld215_init(HelloWorld215 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld215_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld215 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld215_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld215 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld215_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld215_topic_max_size(0) + 4u);

	if (size != HELLOWORLD215_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD215_SIZE:%d\n", size, HELLOWORLD215_SIZE);
		pr_warn("size is not equal to HELLOWORLD215_SIZE\n");

		return size;
	}

	return HELLOWORLD215_SIZE;
}

static bool HelloWorld215_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld215  *topic = (HelloWorld215  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld215_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld215_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld215 *topic = (HelloWorld215 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld215_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld215 *HelloWorld215_create(void)
{
	HelloWorld215 *sample;
	uint32_t size = sizeof(struct HelloWorld215);

	sample = (HelloWorld215 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld215_delete(HelloWorld215 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld216
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld216_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld216_init(HelloWorld216 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld216_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld216 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld216_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld216 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld216_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld216_topic_max_size(0) + 4u);

	if (size != HELLOWORLD216_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD216_SIZE:%d\n", size, HELLOWORLD216_SIZE);
		pr_warn("size is not equal to HELLOWORLD216_SIZE\n");

		return size;
	}

	return HELLOWORLD216_SIZE;
}

static bool HelloWorld216_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld216  *topic = (HelloWorld216  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld216_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld216_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld216 *topic = (HelloWorld216 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld216_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld216 *HelloWorld216_create(void)
{
	HelloWorld216 *sample;
	uint32_t size = sizeof(struct HelloWorld216);

	sample = (HelloWorld216 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld216_delete(HelloWorld216 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld217
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld217_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld217_init(HelloWorld217 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld217_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld217 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld217_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld217 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld217_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld217_topic_max_size(0) + 4u);

	if (size != HELLOWORLD217_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD217_SIZE:%d\n", size, HELLOWORLD217_SIZE);
		pr_warn("size is not equal to HELLOWORLD217_SIZE\n");

		return size;
	}

	return HELLOWORLD217_SIZE;
}

static bool HelloWorld217_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld217  *topic = (HelloWorld217  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld217_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld217_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld217 *topic = (HelloWorld217 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld217_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld217 *HelloWorld217_create(void)
{
	HelloWorld217 *sample;
	uint32_t size = sizeof(struct HelloWorld217);

	sample = (HelloWorld217 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld217_delete(HelloWorld217 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld218
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld218_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld218_init(HelloWorld218 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld218_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld218 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld218_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld218 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld218_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld218_topic_max_size(0) + 4u);

	if (size != HELLOWORLD218_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD218_SIZE:%d\n", size, HELLOWORLD218_SIZE);
		pr_warn("size is not equal to HELLOWORLD218_SIZE\n");

		return size;
	}

	return HELLOWORLD218_SIZE;
}

static bool HelloWorld218_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld218  *topic = (HelloWorld218  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld218_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld218_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld218 *topic = (HelloWorld218 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld218_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld218 *HelloWorld218_create(void)
{
	HelloWorld218 *sample;
	uint32_t size = sizeof(struct HelloWorld218);

	sample = (HelloWorld218 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld218_delete(HelloWorld218 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld219
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld219_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld219_init(HelloWorld219 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld219_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld219 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld219_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld219 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld219_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld219_topic_max_size(0) + 4u);

	if (size != HELLOWORLD219_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD219_SIZE:%d\n", size, HELLOWORLD219_SIZE);
		pr_warn("size is not equal to HELLOWORLD219_SIZE\n");

		return size;
	}

	return HELLOWORLD219_SIZE;
}

static bool HelloWorld219_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld219  *topic = (HelloWorld219  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld219_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld219_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld219 *topic = (HelloWorld219 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld219_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld219 *HelloWorld219_create(void)
{
	HelloWorld219 *sample;
	uint32_t size = sizeof(struct HelloWorld219);

	sample = (HelloWorld219 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld219_delete(HelloWorld219 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld220
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld220_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld220_init(HelloWorld220 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld220_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld220 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld220_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld220 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld220_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld220_topic_max_size(0) + 4u);

	if (size != HELLOWORLD220_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD220_SIZE:%d\n", size, HELLOWORLD220_SIZE);
		pr_warn("size is not equal to HELLOWORLD220_SIZE\n");

		return size;
	}

	return HELLOWORLD220_SIZE;
}

static bool HelloWorld220_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld220  *topic = (HelloWorld220  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld220_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld220_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld220 *topic = (HelloWorld220 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld220_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld220 *HelloWorld220_create(void)
{
	HelloWorld220 *sample;
	uint32_t size = sizeof(struct HelloWorld220);

	sample = (HelloWorld220 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld220_delete(HelloWorld220 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld221
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld221_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld221_init(HelloWorld221 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld221_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld221 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld221_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld221 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld221_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld221_topic_max_size(0) + 4u);

	if (size != HELLOWORLD221_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD221_SIZE:%d\n", size, HELLOWORLD221_SIZE);
		pr_warn("size is not equal to HELLOWORLD221_SIZE\n");

		return size;
	}

	return HELLOWORLD221_SIZE;
}

static bool HelloWorld221_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld221  *topic = (HelloWorld221  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld221_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld221_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld221 *topic = (HelloWorld221 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld221_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld221 *HelloWorld221_create(void)
{
	HelloWorld221 *sample;
	uint32_t size = sizeof(struct HelloWorld221);

	sample = (HelloWorld221 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld221_delete(HelloWorld221 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld222
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld222_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld222_init(HelloWorld222 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld222_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld222 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld222_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld222 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld222_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld222_topic_max_size(0) + 4u);

	if (size != HELLOWORLD222_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD222_SIZE:%d\n", size, HELLOWORLD222_SIZE);
		pr_warn("size is not equal to HELLOWORLD222_SIZE\n");

		return size;
	}

	return HELLOWORLD222_SIZE;
}

static bool HelloWorld222_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld222  *topic = (HelloWorld222  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld222_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld222_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld222 *topic = (HelloWorld222 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld222_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld222 *HelloWorld222_create(void)
{
	HelloWorld222 *sample;
	uint32_t size = sizeof(struct HelloWorld222);

	sample = (HelloWorld222 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld222_delete(HelloWorld222 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld223
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld223_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld223_init(HelloWorld223 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld223_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld223 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld223_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld223 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld223_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld223_topic_max_size(0) + 4u);

	if (size != HELLOWORLD223_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD223_SIZE:%d\n", size, HELLOWORLD223_SIZE);
		pr_warn("size is not equal to HELLOWORLD223_SIZE\n");

		return size;
	}

	return HELLOWORLD223_SIZE;
}

static bool HelloWorld223_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld223  *topic = (HelloWorld223  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld223_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld223_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld223 *topic = (HelloWorld223 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld223_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld223 *HelloWorld223_create(void)
{
	HelloWorld223 *sample;
	uint32_t size = sizeof(struct HelloWorld223);

	sample = (HelloWorld223 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld223_delete(HelloWorld223 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld224
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld224_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld224_init(HelloWorld224 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld224_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld224 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld224_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld224 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld224_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld224_topic_max_size(0) + 4u);

	if (size != HELLOWORLD224_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD224_SIZE:%d\n", size, HELLOWORLD224_SIZE);
		pr_warn("size is not equal to HELLOWORLD224_SIZE\n");

		return size;
	}

	return HELLOWORLD224_SIZE;
}

static bool HelloWorld224_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld224  *topic = (HelloWorld224  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld224_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld224_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld224 *topic = (HelloWorld224 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld224_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld224 *HelloWorld224_create(void)
{
	HelloWorld224 *sample;
	uint32_t size = sizeof(struct HelloWorld224);

	sample = (HelloWorld224 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld224_delete(HelloWorld224 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld225
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld225_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld225_init(HelloWorld225 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld225_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld225 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld225_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld225 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld225_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld225_topic_max_size(0) + 4u);

	if (size != HELLOWORLD225_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD225_SIZE:%d\n", size, HELLOWORLD225_SIZE);
		pr_warn("size is not equal to HELLOWORLD225_SIZE\n");

		return size;
	}

	return HELLOWORLD225_SIZE;
}

static bool HelloWorld225_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld225  *topic = (HelloWorld225  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld225_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld225_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld225 *topic = (HelloWorld225 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld225_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld225 *HelloWorld225_create(void)
{
	HelloWorld225 *sample;
	uint32_t size = sizeof(struct HelloWorld225);

	sample = (HelloWorld225 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld225_delete(HelloWorld225 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld226
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld226_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld226_init(HelloWorld226 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld226_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld226 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld226_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld226 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld226_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld226_topic_max_size(0) + 4u);

	if (size != HELLOWORLD226_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD226_SIZE:%d\n", size, HELLOWORLD226_SIZE);
		pr_warn("size is not equal to HELLOWORLD226_SIZE\n");

		return size;
	}

	return HELLOWORLD226_SIZE;
}

static bool HelloWorld226_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld226  *topic = (HelloWorld226  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld226_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld226_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld226 *topic = (HelloWorld226 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld226_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld226 *HelloWorld226_create(void)
{
	HelloWorld226 *sample;
	uint32_t size = sizeof(struct HelloWorld226);

	sample = (HelloWorld226 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld226_delete(HelloWorld226 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld227
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld227_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld227_init(HelloWorld227 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld227_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld227 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld227_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld227 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld227_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld227_topic_max_size(0) + 4u);

	if (size != HELLOWORLD227_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD227_SIZE:%d\n", size, HELLOWORLD227_SIZE);
		pr_warn("size is not equal to HELLOWORLD227_SIZE\n");

		return size;
	}

	return HELLOWORLD227_SIZE;
}

static bool HelloWorld227_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld227  *topic = (HelloWorld227  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld227_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld227_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld227 *topic = (HelloWorld227 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld227_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld227 *HelloWorld227_create(void)
{
	HelloWorld227 *sample;
	uint32_t size = sizeof(struct HelloWorld227);

	sample = (HelloWorld227 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld227_delete(HelloWorld227 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld228
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld228_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld228_init(HelloWorld228 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld228_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld228 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld228_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld228 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld228_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld228_topic_max_size(0) + 4u);

	if (size != HELLOWORLD228_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD228_SIZE:%d\n", size, HELLOWORLD228_SIZE);
		pr_warn("size is not equal to HELLOWORLD228_SIZE\n");

		return size;
	}

	return HELLOWORLD228_SIZE;
}

static bool HelloWorld228_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld228  *topic = (HelloWorld228  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld228_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld228_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld228 *topic = (HelloWorld228 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld228_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld228 *HelloWorld228_create(void)
{
	HelloWorld228 *sample;
	uint32_t size = sizeof(struct HelloWorld228);

	sample = (HelloWorld228 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld228_delete(HelloWorld228 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld229
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld229_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld229_init(HelloWorld229 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld229_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld229 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld229_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld229 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld229_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld229_topic_max_size(0) + 4u);

	if (size != HELLOWORLD229_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD229_SIZE:%d\n", size, HELLOWORLD229_SIZE);
		pr_warn("size is not equal to HELLOWORLD229_SIZE\n");

		return size;
	}

	return HELLOWORLD229_SIZE;
}

static bool HelloWorld229_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld229  *topic = (HelloWorld229  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld229_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld229_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld229 *topic = (HelloWorld229 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld229_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld229 *HelloWorld229_create(void)
{
	HelloWorld229 *sample;
	uint32_t size = sizeof(struct HelloWorld229);

	sample = (HelloWorld229 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld229_delete(HelloWorld229 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld230
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld230_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld230_init(HelloWorld230 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld230_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld230 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld230_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld230 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld230_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld230_topic_max_size(0) + 4u);

	if (size != HELLOWORLD230_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD230_SIZE:%d\n", size, HELLOWORLD230_SIZE);
		pr_warn("size is not equal to HELLOWORLD230_SIZE\n");

		return size;
	}

	return HELLOWORLD230_SIZE;
}

static bool HelloWorld230_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld230  *topic = (HelloWorld230  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld230_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld230_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld230 *topic = (HelloWorld230 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld230_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld230 *HelloWorld230_create(void)
{
	HelloWorld230 *sample;
	uint32_t size = sizeof(struct HelloWorld230);

	sample = (HelloWorld230 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld230_delete(HelloWorld230 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld231
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld231_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld231_init(HelloWorld231 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld231_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld231 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld231_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld231 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld231_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld231_topic_max_size(0) + 4u);

	if (size != HELLOWORLD231_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD231_SIZE:%d\n", size, HELLOWORLD231_SIZE);
		pr_warn("size is not equal to HELLOWORLD231_SIZE\n");

		return size;
	}

	return HELLOWORLD231_SIZE;
}

static bool HelloWorld231_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld231  *topic = (HelloWorld231  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld231_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld231_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld231 *topic = (HelloWorld231 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld231_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld231 *HelloWorld231_create(void)
{
	HelloWorld231 *sample;
	uint32_t size = sizeof(struct HelloWorld231);

	sample = (HelloWorld231 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld231_delete(HelloWorld231 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld232
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld232_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld232_init(HelloWorld232 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld232_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld232 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld232_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld232 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld232_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld232_topic_max_size(0) + 4u);

	if (size != HELLOWORLD232_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD232_SIZE:%d\n", size, HELLOWORLD232_SIZE);
		pr_warn("size is not equal to HELLOWORLD232_SIZE\n");

		return size;
	}

	return HELLOWORLD232_SIZE;
}

static bool HelloWorld232_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld232  *topic = (HelloWorld232  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld232_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld232_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld232 *topic = (HelloWorld232 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld232_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld232 *HelloWorld232_create(void)
{
	HelloWorld232 *sample;
	uint32_t size = sizeof(struct HelloWorld232);

	sample = (HelloWorld232 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld232_delete(HelloWorld232 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld233
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld233_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld233_init(HelloWorld233 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld233_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld233 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld233_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld233 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld233_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld233_topic_max_size(0) + 4u);

	if (size != HELLOWORLD233_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD233_SIZE:%d\n", size, HELLOWORLD233_SIZE);
		pr_warn("size is not equal to HELLOWORLD233_SIZE\n");

		return size;
	}

	return HELLOWORLD233_SIZE;
}

static bool HelloWorld233_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld233  *topic = (HelloWorld233  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld233_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld233_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld233 *topic = (HelloWorld233 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld233_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld233 *HelloWorld233_create(void)
{
	HelloWorld233 *sample;
	uint32_t size = sizeof(struct HelloWorld233);

	sample = (HelloWorld233 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld233_delete(HelloWorld233 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld234
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld234_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld234_init(HelloWorld234 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld234_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld234 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld234_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld234 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld234_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld234_topic_max_size(0) + 4u);

	if (size != HELLOWORLD234_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD234_SIZE:%d\n", size, HELLOWORLD234_SIZE);
		pr_warn("size is not equal to HELLOWORLD234_SIZE\n");

		return size;
	}

	return HELLOWORLD234_SIZE;
}

static bool HelloWorld234_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld234  *topic = (HelloWorld234  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld234_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld234_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld234 *topic = (HelloWorld234 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld234_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld234 *HelloWorld234_create(void)
{
	HelloWorld234 *sample;
	uint32_t size = sizeof(struct HelloWorld234);

	sample = (HelloWorld234 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld234_delete(HelloWorld234 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld235
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld235_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld235_init(HelloWorld235 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld235_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld235 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld235_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld235 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld235_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld235_topic_max_size(0) + 4u);

	if (size != HELLOWORLD235_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD235_SIZE:%d\n", size, HELLOWORLD235_SIZE);
		pr_warn("size is not equal to HELLOWORLD235_SIZE\n");

		return size;
	}

	return HELLOWORLD235_SIZE;
}

static bool HelloWorld235_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld235  *topic = (HelloWorld235  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld235_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld235_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld235 *topic = (HelloWorld235 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld235_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld235 *HelloWorld235_create(void)
{
	HelloWorld235 *sample;
	uint32_t size = sizeof(struct HelloWorld235);

	sample = (HelloWorld235 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld235_delete(HelloWorld235 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld236
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld236_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld236_init(HelloWorld236 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld236_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld236 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld236_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld236 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld236_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld236_topic_max_size(0) + 4u);

	if (size != HELLOWORLD236_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD236_SIZE:%d\n", size, HELLOWORLD236_SIZE);
		pr_warn("size is not equal to HELLOWORLD236_SIZE\n");

		return size;
	}

	return HELLOWORLD236_SIZE;
}

static bool HelloWorld236_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld236  *topic = (HelloWorld236  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld236_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld236_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld236 *topic = (HelloWorld236 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld236_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld236 *HelloWorld236_create(void)
{
	HelloWorld236 *sample;
	uint32_t size = sizeof(struct HelloWorld236);

	sample = (HelloWorld236 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld236_delete(HelloWorld236 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld237
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld237_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld237_init(HelloWorld237 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld237_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld237 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld237_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld237 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld237_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld237_topic_max_size(0) + 4u);

	if (size != HELLOWORLD237_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD237_SIZE:%d\n", size, HELLOWORLD237_SIZE);
		pr_warn("size is not equal to HELLOWORLD237_SIZE\n");

		return size;
	}

	return HELLOWORLD237_SIZE;
}

static bool HelloWorld237_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld237  *topic = (HelloWorld237  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld237_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld237_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld237 *topic = (HelloWorld237 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld237_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld237 *HelloWorld237_create(void)
{
	HelloWorld237 *sample;
	uint32_t size = sizeof(struct HelloWorld237);

	sample = (HelloWorld237 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld237_delete(HelloWorld237 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld238
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld238_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld238_init(HelloWorld238 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld238_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld238 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld238_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld238 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld238_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld238_topic_max_size(0) + 4u);

	if (size != HELLOWORLD238_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD238_SIZE:%d\n", size, HELLOWORLD238_SIZE);
		pr_warn("size is not equal to HELLOWORLD238_SIZE\n");

		return size;
	}

	return HELLOWORLD238_SIZE;
}

static bool HelloWorld238_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld238  *topic = (HelloWorld238  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld238_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld238_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld238 *topic = (HelloWorld238 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld238_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld238 *HelloWorld238_create(void)
{
	HelloWorld238 *sample;
	uint32_t size = sizeof(struct HelloWorld238);

	sample = (HelloWorld238 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld238_delete(HelloWorld238 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld239
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld239_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld239_init(HelloWorld239 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld239_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld239 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld239_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld239 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld239_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld239_topic_max_size(0) + 4u);

	if (size != HELLOWORLD239_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD239_SIZE:%d\n", size, HELLOWORLD239_SIZE);
		pr_warn("size is not equal to HELLOWORLD239_SIZE\n");

		return size;
	}

	return HELLOWORLD239_SIZE;
}

static bool HelloWorld239_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld239  *topic = (HelloWorld239  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld239_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld239_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld239 *topic = (HelloWorld239 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld239_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld239 *HelloWorld239_create(void)
{
	HelloWorld239 *sample;
	uint32_t size = sizeof(struct HelloWorld239);

	sample = (HelloWorld239 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld239_delete(HelloWorld239 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld240
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld240_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld240_init(HelloWorld240 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld240_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld240 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld240_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld240 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld240_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld240_topic_max_size(0) + 4u);

	if (size != HELLOWORLD240_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD240_SIZE:%d\n", size, HELLOWORLD240_SIZE);
		pr_warn("size is not equal to HELLOWORLD240_SIZE\n");

		return size;
	}

	return HELLOWORLD240_SIZE;
}

static bool HelloWorld240_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld240  *topic = (HelloWorld240  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld240_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld240_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld240 *topic = (HelloWorld240 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld240_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld240 *HelloWorld240_create(void)
{
	HelloWorld240 *sample;
	uint32_t size = sizeof(struct HelloWorld240);

	sample = (HelloWorld240 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld240_delete(HelloWorld240 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld241
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld241_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld241_init(HelloWorld241 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld241_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld241 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld241_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld241 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld241_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld241_topic_max_size(0) + 4u);

	if (size != HELLOWORLD241_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD241_SIZE:%d\n", size, HELLOWORLD241_SIZE);
		pr_warn("size is not equal to HELLOWORLD241_SIZE\n");

		return size;
	}

	return HELLOWORLD241_SIZE;
}

static bool HelloWorld241_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld241  *topic = (HelloWorld241  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld241_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld241_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld241 *topic = (HelloWorld241 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld241_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld241 *HelloWorld241_create(void)
{
	HelloWorld241 *sample;
	uint32_t size = sizeof(struct HelloWorld241);

	sample = (HelloWorld241 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld241_delete(HelloWorld241 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld242
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld242_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld242_init(HelloWorld242 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld242_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld242 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld242_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld242 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld242_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld242_topic_max_size(0) + 4u);

	if (size != HELLOWORLD242_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD242_SIZE:%d\n", size, HELLOWORLD242_SIZE);
		pr_warn("size is not equal to HELLOWORLD242_SIZE\n");

		return size;
	}

	return HELLOWORLD242_SIZE;
}

static bool HelloWorld242_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld242  *topic = (HelloWorld242  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld242_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld242_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld242 *topic = (HelloWorld242 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld242_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld242 *HelloWorld242_create(void)
{
	HelloWorld242 *sample;
	uint32_t size = sizeof(struct HelloWorld242);

	sample = (HelloWorld242 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld242_delete(HelloWorld242 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld243
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld243_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld243_init(HelloWorld243 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld243_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld243 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld243_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld243 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld243_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld243_topic_max_size(0) + 4u);

	if (size != HELLOWORLD243_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD243_SIZE:%d\n", size, HELLOWORLD243_SIZE);
		pr_warn("size is not equal to HELLOWORLD243_SIZE\n");

		return size;
	}

	return HELLOWORLD243_SIZE;
}

static bool HelloWorld243_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld243  *topic = (HelloWorld243  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld243_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld243_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld243 *topic = (HelloWorld243 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld243_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld243 *HelloWorld243_create(void)
{
	HelloWorld243 *sample;
	uint32_t size = sizeof(struct HelloWorld243);

	sample = (HelloWorld243 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld243_delete(HelloWorld243 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld244
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld244_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld244_init(HelloWorld244 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld244_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld244 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld244_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld244 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld244_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld244_topic_max_size(0) + 4u);

	if (size != HELLOWORLD244_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD244_SIZE:%d\n", size, HELLOWORLD244_SIZE);
		pr_warn("size is not equal to HELLOWORLD244_SIZE\n");

		return size;
	}

	return HELLOWORLD244_SIZE;
}

static bool HelloWorld244_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld244  *topic = (HelloWorld244  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld244_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld244_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld244 *topic = (HelloWorld244 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld244_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld244 *HelloWorld244_create(void)
{
	HelloWorld244 *sample;
	uint32_t size = sizeof(struct HelloWorld244);

	sample = (HelloWorld244 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld244_delete(HelloWorld244 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld245
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld245_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld245_init(HelloWorld245 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld245_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld245 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld245_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld245 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld245_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld245_topic_max_size(0) + 4u);

	if (size != HELLOWORLD245_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD245_SIZE:%d\n", size, HELLOWORLD245_SIZE);
		pr_warn("size is not equal to HELLOWORLD245_SIZE\n");

		return size;
	}

	return HELLOWORLD245_SIZE;
}

static bool HelloWorld245_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld245  *topic = (HelloWorld245  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld245_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld245_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld245 *topic = (HelloWorld245 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld245_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld245 *HelloWorld245_create(void)
{
	HelloWorld245 *sample;
	uint32_t size = sizeof(struct HelloWorld245);

	sample = (HelloWorld245 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld245_delete(HelloWorld245 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld246
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld246_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld246_init(HelloWorld246 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld246_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld246 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld246_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld246 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld246_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld246_topic_max_size(0) + 4u);

	if (size != HELLOWORLD246_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD246_SIZE:%d\n", size, HELLOWORLD246_SIZE);
		pr_warn("size is not equal to HELLOWORLD246_SIZE\n");

		return size;
	}

	return HELLOWORLD246_SIZE;
}

static bool HelloWorld246_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld246  *topic = (HelloWorld246  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld246_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld246_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld246 *topic = (HelloWorld246 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld246_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld246 *HelloWorld246_create(void)
{
	HelloWorld246 *sample;
	uint32_t size = sizeof(struct HelloWorld246);

	sample = (HelloWorld246 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld246_delete(HelloWorld246 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld247
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld247_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld247_init(HelloWorld247 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld247_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld247 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld247_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld247 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld247_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld247_topic_max_size(0) + 4u);

	if (size != HELLOWORLD247_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD247_SIZE:%d\n", size, HELLOWORLD247_SIZE);
		pr_warn("size is not equal to HELLOWORLD247_SIZE\n");

		return size;
	}

	return HELLOWORLD247_SIZE;
}

static bool HelloWorld247_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld247  *topic = (HelloWorld247  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld247_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld247_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld247 *topic = (HelloWorld247 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld247_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld247 *HelloWorld247_create(void)
{
	HelloWorld247 *sample;
	uint32_t size = sizeof(struct HelloWorld247);

	sample = (HelloWorld247 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld247_delete(HelloWorld247 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld248
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld248_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld248_init(HelloWorld248 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld248_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld248 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld248_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld248 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld248_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld248_topic_max_size(0) + 4u);

	if (size != HELLOWORLD248_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD248_SIZE:%d\n", size, HELLOWORLD248_SIZE);
		pr_warn("size is not equal to HELLOWORLD248_SIZE\n");

		return size;
	}

	return HELLOWORLD248_SIZE;
}

static bool HelloWorld248_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld248  *topic = (HelloWorld248  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld248_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld248_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld248 *topic = (HelloWorld248 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld248_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld248 *HelloWorld248_create(void)
{
	HelloWorld248 *sample;
	uint32_t size = sizeof(struct HelloWorld248);

	sample = (HelloWorld248 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld248_delete(HelloWorld248 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld249
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld249_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld249_init(HelloWorld249 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld249_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld249 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld249_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld249 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld249_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld249_topic_max_size(0) + 4u);

	if (size != HELLOWORLD249_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD249_SIZE:%d\n", size, HELLOWORLD249_SIZE);
		pr_warn("size is not equal to HELLOWORLD249_SIZE\n");

		return size;
	}

	return HELLOWORLD249_SIZE;
}

static bool HelloWorld249_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld249  *topic = (HelloWorld249  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld249_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld249_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld249 *topic = (HelloWorld249 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld249_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld249 *HelloWorld249_create(void)
{
	HelloWorld249 *sample;
	uint32_t size = sizeof(struct HelloWorld249);

	sample = (HelloWorld249 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld249_delete(HelloWorld249 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld250
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld250_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld250_init(HelloWorld250 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld250_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld250 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld250_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld250 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld250_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld250_topic_max_size(0) + 4u);

	if (size != HELLOWORLD250_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD250_SIZE:%d\n", size, HELLOWORLD250_SIZE);
		pr_warn("size is not equal to HELLOWORLD250_SIZE\n");

		return size;
	}

	return HELLOWORLD250_SIZE;
}

static bool HelloWorld250_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld250  *topic = (HelloWorld250  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld250_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld250_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld250 *topic = (HelloWorld250 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld250_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld250 *HelloWorld250_create(void)
{
	HelloWorld250 *sample;
	uint32_t size = sizeof(struct HelloWorld250);

	sample = (HelloWorld250 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld250_delete(HelloWorld250 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld251
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld251_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld251_init(HelloWorld251 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld251_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld251 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld251_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld251 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld251_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld251_topic_max_size(0) + 4u);

	if (size != HELLOWORLD251_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD251_SIZE:%d\n", size, HELLOWORLD251_SIZE);
		pr_warn("size is not equal to HELLOWORLD251_SIZE\n");

		return size;
	}

	return HELLOWORLD251_SIZE;
}

static bool HelloWorld251_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld251  *topic = (HelloWorld251  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld251_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld251_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld251 *topic = (HelloWorld251 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld251_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld251 *HelloWorld251_create(void)
{
	HelloWorld251 *sample;
	uint32_t size = sizeof(struct HelloWorld251);

	sample = (HelloWorld251 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld251_delete(HelloWorld251 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld252
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld252_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld252_init(HelloWorld252 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld252_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld252 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld252_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld252 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld252_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld252_topic_max_size(0) + 4u);

	if (size != HELLOWORLD252_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD252_SIZE:%d\n", size, HELLOWORLD252_SIZE);
		pr_warn("size is not equal to HELLOWORLD252_SIZE\n");

		return size;
	}

	return HELLOWORLD252_SIZE;
}

static bool HelloWorld252_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld252  *topic = (HelloWorld252  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld252_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld252_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld252 *topic = (HelloWorld252 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld252_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld252 *HelloWorld252_create(void)
{
	HelloWorld252 *sample;
	uint32_t size = sizeof(struct HelloWorld252);

	sample = (HelloWorld252 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld252_delete(HelloWorld252 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld253
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld253_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld253_init(HelloWorld253 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld253_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld253 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld253_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld253 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld253_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld253_topic_max_size(0) + 4u);

	if (size != HELLOWORLD253_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD253_SIZE:%d\n", size, HELLOWORLD253_SIZE);
		pr_warn("size is not equal to HELLOWORLD253_SIZE\n");

		return size;
	}

	return HELLOWORLD253_SIZE;
}

static bool HelloWorld253_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld253  *topic = (HelloWorld253  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld253_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld253_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld253 *topic = (HelloWorld253 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld253_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld253 *HelloWorld253_create(void)
{
	HelloWorld253 *sample;
	uint32_t size = sizeof(struct HelloWorld253);

	sample = (HelloWorld253 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld253_delete(HelloWorld253 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld254
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld254_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld254_init(HelloWorld254 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld254_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld254 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld254_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld254 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld254_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld254_topic_max_size(0) + 4u);

	if (size != HELLOWORLD254_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD254_SIZE:%d\n", size, HELLOWORLD254_SIZE);
		pr_warn("size is not equal to HELLOWORLD254_SIZE\n");

		return size;
	}

	return HELLOWORLD254_SIZE;
}

static bool HelloWorld254_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld254  *topic = (HelloWorld254  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld254_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld254_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld254 *topic = (HelloWorld254 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld254_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld254 *HelloWorld254_create(void)
{
	HelloWorld254 *sample;
	uint32_t size = sizeof(struct HelloWorld254);

	sample = (HelloWorld254 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld254_delete(HelloWorld254 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld255
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld255_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld255_init(HelloWorld255 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld255_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld255 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld255_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld255 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld255_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld255_topic_max_size(0) + 4u);

	if (size != HELLOWORLD255_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD255_SIZE:%d\n", size, HELLOWORLD255_SIZE);
		pr_warn("size is not equal to HELLOWORLD255_SIZE\n");

		return size;
	}

	return HELLOWORLD255_SIZE;
}

static bool HelloWorld255_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld255  *topic = (HelloWorld255  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld255_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld255_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld255 *topic = (HelloWorld255 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld255_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld255 *HelloWorld255_create(void)
{
	HelloWorld255 *sample;
	uint32_t size = sizeof(struct HelloWorld255);

	sample = (HelloWorld255 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld255_delete(HelloWorld255 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld256
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld256_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld256_init(HelloWorld256 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld256_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld256 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld256_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld256 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld256_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld256_topic_max_size(0) + 4u);

	if (size != HELLOWORLD256_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD256_SIZE:%d\n", size, HELLOWORLD256_SIZE);
		pr_warn("size is not equal to HELLOWORLD256_SIZE\n");

		return size;
	}

	return HELLOWORLD256_SIZE;
}

static bool HelloWorld256_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld256  *topic = (HelloWorld256  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld256_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld256_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld256 *topic = (HelloWorld256 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld256_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld256 *HelloWorld256_create(void)
{
	HelloWorld256 *sample;
	uint32_t size = sizeof(struct HelloWorld256);

	sample = (HelloWorld256 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld256_delete(HelloWorld256 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld257
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld257_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld257_init(HelloWorld257 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld257_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld257 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld257_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld257 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld257_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld257_topic_max_size(0) + 4u);

	if (size != HELLOWORLD257_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD257_SIZE:%d\n", size, HELLOWORLD257_SIZE);
		pr_warn("size is not equal to HELLOWORLD257_SIZE\n");

		return size;
	}

	return HELLOWORLD257_SIZE;
}

static bool HelloWorld257_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld257  *topic = (HelloWorld257  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld257_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld257_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld257 *topic = (HelloWorld257 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld257_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld257 *HelloWorld257_create(void)
{
	HelloWorld257 *sample;
	uint32_t size = sizeof(struct HelloWorld257);

	sample = (HelloWorld257 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld257_delete(HelloWorld257 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld258
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld258_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld258_init(HelloWorld258 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld258_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld258 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld258_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld258 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld258_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld258_topic_max_size(0) + 4u);

	if (size != HELLOWORLD258_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD258_SIZE:%d\n", size, HELLOWORLD258_SIZE);
		pr_warn("size is not equal to HELLOWORLD258_SIZE\n");

		return size;
	}

	return HELLOWORLD258_SIZE;
}

static bool HelloWorld258_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld258  *topic = (HelloWorld258  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld258_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld258_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld258 *topic = (HelloWorld258 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld258_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld258 *HelloWorld258_create(void)
{
	HelloWorld258 *sample;
	uint32_t size = sizeof(struct HelloWorld258);

	sample = (HelloWorld258 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld258_delete(HelloWorld258 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld259
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld259_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld259_init(HelloWorld259 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld259_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld259 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld259_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld259 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld259_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld259_topic_max_size(0) + 4u);

	if (size != HELLOWORLD259_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD259_SIZE:%d\n", size, HELLOWORLD259_SIZE);
		pr_warn("size is not equal to HELLOWORLD259_SIZE\n");

		return size;
	}

	return HELLOWORLD259_SIZE;
}

static bool HelloWorld259_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld259  *topic = (HelloWorld259  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld259_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld259_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld259 *topic = (HelloWorld259 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld259_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld259 *HelloWorld259_create(void)
{
	HelloWorld259 *sample;
	uint32_t size = sizeof(struct HelloWorld259);

	sample = (HelloWorld259 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld259_delete(HelloWorld259 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld260
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld260_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld260_init(HelloWorld260 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld260_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld260 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld260_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld260 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld260_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld260_topic_max_size(0) + 4u);

	if (size != HELLOWORLD260_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD260_SIZE:%d\n", size, HELLOWORLD260_SIZE);
		pr_warn("size is not equal to HELLOWORLD260_SIZE\n");

		return size;
	}

	return HELLOWORLD260_SIZE;
}

static bool HelloWorld260_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld260  *topic = (HelloWorld260  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld260_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld260_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld260 *topic = (HelloWorld260 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld260_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld260 *HelloWorld260_create(void)
{
	HelloWorld260 *sample;
	uint32_t size = sizeof(struct HelloWorld260);

	sample = (HelloWorld260 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld260_delete(HelloWorld260 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld261
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld261_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld261_init(HelloWorld261 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld261_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld261 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld261_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld261 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld261_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld261_topic_max_size(0) + 4u);

	if (size != HELLOWORLD261_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD261_SIZE:%d\n", size, HELLOWORLD261_SIZE);
		pr_warn("size is not equal to HELLOWORLD261_SIZE\n");

		return size;
	}

	return HELLOWORLD261_SIZE;
}

static bool HelloWorld261_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld261  *topic = (HelloWorld261  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld261_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld261_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld261 *topic = (HelloWorld261 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld261_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld261 *HelloWorld261_create(void)
{
	HelloWorld261 *sample;
	uint32_t size = sizeof(struct HelloWorld261);

	sample = (HelloWorld261 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld261_delete(HelloWorld261 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld262
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld262_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld262_init(HelloWorld262 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld262_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld262 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld262_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld262 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld262_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld262_topic_max_size(0) + 4u);

	if (size != HELLOWORLD262_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD262_SIZE:%d\n", size, HELLOWORLD262_SIZE);
		pr_warn("size is not equal to HELLOWORLD262_SIZE\n");

		return size;
	}

	return HELLOWORLD262_SIZE;
}

static bool HelloWorld262_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld262  *topic = (HelloWorld262  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld262_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld262_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld262 *topic = (HelloWorld262 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld262_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld262 *HelloWorld262_create(void)
{
	HelloWorld262 *sample;
	uint32_t size = sizeof(struct HelloWorld262);

	sample = (HelloWorld262 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld262_delete(HelloWorld262 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld263
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld263_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld263_init(HelloWorld263 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld263_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld263 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld263_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld263 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld263_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld263_topic_max_size(0) + 4u);

	if (size != HELLOWORLD263_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD263_SIZE:%d\n", size, HELLOWORLD263_SIZE);
		pr_warn("size is not equal to HELLOWORLD263_SIZE\n");

		return size;
	}

	return HELLOWORLD263_SIZE;
}

static bool HelloWorld263_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld263  *topic = (HelloWorld263  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld263_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld263_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld263 *topic = (HelloWorld263 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld263_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld263 *HelloWorld263_create(void)
{
	HelloWorld263 *sample;
	uint32_t size = sizeof(struct HelloWorld263);

	sample = (HelloWorld263 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld263_delete(HelloWorld263 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld264
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld264_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld264_init(HelloWorld264 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld264_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld264 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld264_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld264 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld264_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld264_topic_max_size(0) + 4u);

	if (size != HELLOWORLD264_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD264_SIZE:%d\n", size, HELLOWORLD264_SIZE);
		pr_warn("size is not equal to HELLOWORLD264_SIZE\n");

		return size;
	}

	return HELLOWORLD264_SIZE;
}

static bool HelloWorld264_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld264  *topic = (HelloWorld264  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld264_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld264_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld264 *topic = (HelloWorld264 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld264_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld264 *HelloWorld264_create(void)
{
	HelloWorld264 *sample;
	uint32_t size = sizeof(struct HelloWorld264);

	sample = (HelloWorld264 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld264_delete(HelloWorld264 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld265
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld265_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld265_init(HelloWorld265 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld265_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld265 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld265_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld265 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld265_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld265_topic_max_size(0) + 4u);

	if (size != HELLOWORLD265_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD265_SIZE:%d\n", size, HELLOWORLD265_SIZE);
		pr_warn("size is not equal to HELLOWORLD265_SIZE\n");

		return size;
	}

	return HELLOWORLD265_SIZE;
}

static bool HelloWorld265_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld265  *topic = (HelloWorld265  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld265_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld265_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld265 *topic = (HelloWorld265 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld265_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld265 *HelloWorld265_create(void)
{
	HelloWorld265 *sample;
	uint32_t size = sizeof(struct HelloWorld265);

	sample = (HelloWorld265 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld265_delete(HelloWorld265 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld266
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld266_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld266_init(HelloWorld266 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld266_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld266 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld266_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld266 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld266_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld266_topic_max_size(0) + 4u);

	if (size != HELLOWORLD266_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD266_SIZE:%d\n", size, HELLOWORLD266_SIZE);
		pr_warn("size is not equal to HELLOWORLD266_SIZE\n");

		return size;
	}

	return HELLOWORLD266_SIZE;
}

static bool HelloWorld266_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld266  *topic = (HelloWorld266  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld266_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld266_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld266 *topic = (HelloWorld266 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld266_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld266 *HelloWorld266_create(void)
{
	HelloWorld266 *sample;
	uint32_t size = sizeof(struct HelloWorld266);

	sample = (HelloWorld266 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld266_delete(HelloWorld266 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld267
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld267_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld267_init(HelloWorld267 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld267_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld267 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld267_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld267 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld267_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld267_topic_max_size(0) + 4u);

	if (size != HELLOWORLD267_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD267_SIZE:%d\n", size, HELLOWORLD267_SIZE);
		pr_warn("size is not equal to HELLOWORLD267_SIZE\n");

		return size;
	}

	return HELLOWORLD267_SIZE;
}

static bool HelloWorld267_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld267  *topic = (HelloWorld267  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld267_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld267_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld267 *topic = (HelloWorld267 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld267_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld267 *HelloWorld267_create(void)
{
	HelloWorld267 *sample;
	uint32_t size = sizeof(struct HelloWorld267);

	sample = (HelloWorld267 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld267_delete(HelloWorld267 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld268
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld268_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld268_init(HelloWorld268 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld268_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld268 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld268_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld268 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld268_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld268_topic_max_size(0) + 4u);

	if (size != HELLOWORLD268_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD268_SIZE:%d\n", size, HELLOWORLD268_SIZE);
		pr_warn("size is not equal to HELLOWORLD268_SIZE\n");

		return size;
	}

	return HELLOWORLD268_SIZE;
}

static bool HelloWorld268_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld268  *topic = (HelloWorld268  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld268_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld268_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld268 *topic = (HelloWorld268 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld268_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld268 *HelloWorld268_create(void)
{
	HelloWorld268 *sample;
	uint32_t size = sizeof(struct HelloWorld268);

	sample = (HelloWorld268 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld268_delete(HelloWorld268 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld269
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld269_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld269_init(HelloWorld269 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld269_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld269 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld269_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld269 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld269_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld269_topic_max_size(0) + 4u);

	if (size != HELLOWORLD269_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD269_SIZE:%d\n", size, HELLOWORLD269_SIZE);
		pr_warn("size is not equal to HELLOWORLD269_SIZE\n");

		return size;
	}

	return HELLOWORLD269_SIZE;
}

static bool HelloWorld269_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld269  *topic = (HelloWorld269  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld269_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld269_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld269 *topic = (HelloWorld269 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld269_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld269 *HelloWorld269_create(void)
{
	HelloWorld269 *sample;
	uint32_t size = sizeof(struct HelloWorld269);

	sample = (HelloWorld269 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld269_delete(HelloWorld269 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld270
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld270_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld270_init(HelloWorld270 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld270_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld270 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld270_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld270 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld270_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld270_topic_max_size(0) + 4u);

	if (size != HELLOWORLD270_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD270_SIZE:%d\n", size, HELLOWORLD270_SIZE);
		pr_warn("size is not equal to HELLOWORLD270_SIZE\n");

		return size;
	}

	return HELLOWORLD270_SIZE;
}

static bool HelloWorld270_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld270  *topic = (HelloWorld270  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld270_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld270_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld270 *topic = (HelloWorld270 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld270_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld270 *HelloWorld270_create(void)
{
	HelloWorld270 *sample;
	uint32_t size = sizeof(struct HelloWorld270);

	sample = (HelloWorld270 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld270_delete(HelloWorld270 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld271
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld271_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld271_init(HelloWorld271 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld271_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld271 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld271_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld271 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld271_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld271_topic_max_size(0) + 4u);

	if (size != HELLOWORLD271_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD271_SIZE:%d\n", size, HELLOWORLD271_SIZE);
		pr_warn("size is not equal to HELLOWORLD271_SIZE\n");

		return size;
	}

	return HELLOWORLD271_SIZE;
}

static bool HelloWorld271_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld271  *topic = (HelloWorld271  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld271_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld271_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld271 *topic = (HelloWorld271 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld271_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld271 *HelloWorld271_create(void)
{
	HelloWorld271 *sample;
	uint32_t size = sizeof(struct HelloWorld271);

	sample = (HelloWorld271 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld271_delete(HelloWorld271 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld272
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld272_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld272_init(HelloWorld272 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld272_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld272 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld272_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld272 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld272_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld272_topic_max_size(0) + 4u);

	if (size != HELLOWORLD272_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD272_SIZE:%d\n", size, HELLOWORLD272_SIZE);
		pr_warn("size is not equal to HELLOWORLD272_SIZE\n");

		return size;
	}

	return HELLOWORLD272_SIZE;
}

static bool HelloWorld272_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld272  *topic = (HelloWorld272  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld272_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld272_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld272 *topic = (HelloWorld272 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld272_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld272 *HelloWorld272_create(void)
{
	HelloWorld272 *sample;
	uint32_t size = sizeof(struct HelloWorld272);

	sample = (HelloWorld272 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld272_delete(HelloWorld272 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld273
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld273_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld273_init(HelloWorld273 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld273_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld273 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld273_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld273 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld273_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld273_topic_max_size(0) + 4u);

	if (size != HELLOWORLD273_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD273_SIZE:%d\n", size, HELLOWORLD273_SIZE);
		pr_warn("size is not equal to HELLOWORLD273_SIZE\n");

		return size;
	}

	return HELLOWORLD273_SIZE;
}

static bool HelloWorld273_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld273  *topic = (HelloWorld273  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld273_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld273_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld273 *topic = (HelloWorld273 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld273_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld273 *HelloWorld273_create(void)
{
	HelloWorld273 *sample;
	uint32_t size = sizeof(struct HelloWorld273);

	sample = (HelloWorld273 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld273_delete(HelloWorld273 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld274
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld274_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld274_init(HelloWorld274 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld274_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld274 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld274_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld274 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld274_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld274_topic_max_size(0) + 4u);

	if (size != HELLOWORLD274_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD274_SIZE:%d\n", size, HELLOWORLD274_SIZE);
		pr_warn("size is not equal to HELLOWORLD274_SIZE\n");

		return size;
	}

	return HELLOWORLD274_SIZE;
}

static bool HelloWorld274_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld274  *topic = (HelloWorld274  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld274_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld274_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld274 *topic = (HelloWorld274 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld274_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld274 *HelloWorld274_create(void)
{
	HelloWorld274 *sample;
	uint32_t size = sizeof(struct HelloWorld274);

	sample = (HelloWorld274 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld274_delete(HelloWorld274 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld275
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld275_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld275_init(HelloWorld275 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld275_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld275 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld275_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld275 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld275_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld275_topic_max_size(0) + 4u);

	if (size != HELLOWORLD275_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD275_SIZE:%d\n", size, HELLOWORLD275_SIZE);
		pr_warn("size is not equal to HELLOWORLD275_SIZE\n");

		return size;
	}

	return HELLOWORLD275_SIZE;
}

static bool HelloWorld275_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld275  *topic = (HelloWorld275  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld275_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld275_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld275 *topic = (HelloWorld275 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld275_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld275 *HelloWorld275_create(void)
{
	HelloWorld275 *sample;
	uint32_t size = sizeof(struct HelloWorld275);

	sample = (HelloWorld275 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld275_delete(HelloWorld275 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld276
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld276_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld276_init(HelloWorld276 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld276_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld276 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld276_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld276 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld276_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld276_topic_max_size(0) + 4u);

	if (size != HELLOWORLD276_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD276_SIZE:%d\n", size, HELLOWORLD276_SIZE);
		pr_warn("size is not equal to HELLOWORLD276_SIZE\n");

		return size;
	}

	return HELLOWORLD276_SIZE;
}

static bool HelloWorld276_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld276  *topic = (HelloWorld276  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld276_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld276_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld276 *topic = (HelloWorld276 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld276_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld276 *HelloWorld276_create(void)
{
	HelloWorld276 *sample;
	uint32_t size = sizeof(struct HelloWorld276);

	sample = (HelloWorld276 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld276_delete(HelloWorld276 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld277
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld277_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld277_init(HelloWorld277 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld277_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld277 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld277_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld277 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld277_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld277_topic_max_size(0) + 4u);

	if (size != HELLOWORLD277_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD277_SIZE:%d\n", size, HELLOWORLD277_SIZE);
		pr_warn("size is not equal to HELLOWORLD277_SIZE\n");

		return size;
	}

	return HELLOWORLD277_SIZE;
}

static bool HelloWorld277_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld277  *topic = (HelloWorld277  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld277_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld277_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld277 *topic = (HelloWorld277 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld277_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld277 *HelloWorld277_create(void)
{
	HelloWorld277 *sample;
	uint32_t size = sizeof(struct HelloWorld277);

	sample = (HelloWorld277 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld277_delete(HelloWorld277 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld278
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld278_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld278_init(HelloWorld278 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld278_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld278 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld278_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld278 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld278_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld278_topic_max_size(0) + 4u);

	if (size != HELLOWORLD278_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD278_SIZE:%d\n", size, HELLOWORLD278_SIZE);
		pr_warn("size is not equal to HELLOWORLD278_SIZE\n");

		return size;
	}

	return HELLOWORLD278_SIZE;
}

static bool HelloWorld278_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld278  *topic = (HelloWorld278  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld278_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld278_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld278 *topic = (HelloWorld278 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld278_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld278 *HelloWorld278_create(void)
{
	HelloWorld278 *sample;
	uint32_t size = sizeof(struct HelloWorld278);

	sample = (HelloWorld278 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld278_delete(HelloWorld278 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld279
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld279_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld279_init(HelloWorld279 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld279_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld279 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld279_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld279 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld279_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld279_topic_max_size(0) + 4u);

	if (size != HELLOWORLD279_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD279_SIZE:%d\n", size, HELLOWORLD279_SIZE);
		pr_warn("size is not equal to HELLOWORLD279_SIZE\n");

		return size;
	}

	return HELLOWORLD279_SIZE;
}

static bool HelloWorld279_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld279  *topic = (HelloWorld279  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld279_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld279_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld279 *topic = (HelloWorld279 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld279_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld279 *HelloWorld279_create(void)
{
	HelloWorld279 *sample;
	uint32_t size = sizeof(struct HelloWorld279);

	sample = (HelloWorld279 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld279_delete(HelloWorld279 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld280
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld280_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld280_init(HelloWorld280 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld280_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld280 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld280_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld280 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld280_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld280_topic_max_size(0) + 4u);

	if (size != HELLOWORLD280_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD280_SIZE:%d\n", size, HELLOWORLD280_SIZE);
		pr_warn("size is not equal to HELLOWORLD280_SIZE\n");

		return size;
	}

	return HELLOWORLD280_SIZE;
}

static bool HelloWorld280_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld280  *topic = (HelloWorld280  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld280_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld280_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld280 *topic = (HelloWorld280 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld280_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld280 *HelloWorld280_create(void)
{
	HelloWorld280 *sample;
	uint32_t size = sizeof(struct HelloWorld280);

	sample = (HelloWorld280 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld280_delete(HelloWorld280 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld281
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld281_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld281_init(HelloWorld281 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld281_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld281 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld281_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld281 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld281_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld281_topic_max_size(0) + 4u);

	if (size != HELLOWORLD281_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD281_SIZE:%d\n", size, HELLOWORLD281_SIZE);
		pr_warn("size is not equal to HELLOWORLD281_SIZE\n");

		return size;
	}

	return HELLOWORLD281_SIZE;
}

static bool HelloWorld281_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld281  *topic = (HelloWorld281  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld281_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld281_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld281 *topic = (HelloWorld281 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld281_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld281 *HelloWorld281_create(void)
{
	HelloWorld281 *sample;
	uint32_t size = sizeof(struct HelloWorld281);

	sample = (HelloWorld281 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld281_delete(HelloWorld281 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld282
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld282_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld282_init(HelloWorld282 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld282_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld282 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld282_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld282 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld282_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld282_topic_max_size(0) + 4u);

	if (size != HELLOWORLD282_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD282_SIZE:%d\n", size, HELLOWORLD282_SIZE);
		pr_warn("size is not equal to HELLOWORLD282_SIZE\n");

		return size;
	}

	return HELLOWORLD282_SIZE;
}

static bool HelloWorld282_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld282  *topic = (HelloWorld282  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld282_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld282_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld282 *topic = (HelloWorld282 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld282_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld282 *HelloWorld282_create(void)
{
	HelloWorld282 *sample;
	uint32_t size = sizeof(struct HelloWorld282);

	sample = (HelloWorld282 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld282_delete(HelloWorld282 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld283
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld283_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld283_init(HelloWorld283 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld283_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld283 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld283_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld283 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld283_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld283_topic_max_size(0) + 4u);

	if (size != HELLOWORLD283_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD283_SIZE:%d\n", size, HELLOWORLD283_SIZE);
		pr_warn("size is not equal to HELLOWORLD283_SIZE\n");

		return size;
	}

	return HELLOWORLD283_SIZE;
}

static bool HelloWorld283_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld283  *topic = (HelloWorld283  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld283_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld283_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld283 *topic = (HelloWorld283 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld283_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld283 *HelloWorld283_create(void)
{
	HelloWorld283 *sample;
	uint32_t size = sizeof(struct HelloWorld283);

	sample = (HelloWorld283 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld283_delete(HelloWorld283 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld284
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld284_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld284_init(HelloWorld284 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld284_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld284 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld284_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld284 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld284_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld284_topic_max_size(0) + 4u);

	if (size != HELLOWORLD284_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD284_SIZE:%d\n", size, HELLOWORLD284_SIZE);
		pr_warn("size is not equal to HELLOWORLD284_SIZE\n");

		return size;
	}

	return HELLOWORLD284_SIZE;
}

static bool HelloWorld284_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld284  *topic = (HelloWorld284  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld284_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld284_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld284 *topic = (HelloWorld284 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld284_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld284 *HelloWorld284_create(void)
{
	HelloWorld284 *sample;
	uint32_t size = sizeof(struct HelloWorld284);

	sample = (HelloWorld284 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld284_delete(HelloWorld284 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld285
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld285_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld285_init(HelloWorld285 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld285_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld285 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld285_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld285 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld285_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld285_topic_max_size(0) + 4u);

	if (size != HELLOWORLD285_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD285_SIZE:%d\n", size, HELLOWORLD285_SIZE);
		pr_warn("size is not equal to HELLOWORLD285_SIZE\n");

		return size;
	}

	return HELLOWORLD285_SIZE;
}

static bool HelloWorld285_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld285  *topic = (HelloWorld285  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld285_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld285_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld285 *topic = (HelloWorld285 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld285_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld285 *HelloWorld285_create(void)
{
	HelloWorld285 *sample;
	uint32_t size = sizeof(struct HelloWorld285);

	sample = (HelloWorld285 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld285_delete(HelloWorld285 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld286
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld286_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld286_init(HelloWorld286 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld286_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld286 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld286_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld286 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld286_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld286_topic_max_size(0) + 4u);

	if (size != HELLOWORLD286_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD286_SIZE:%d\n", size, HELLOWORLD286_SIZE);
		pr_warn("size is not equal to HELLOWORLD286_SIZE\n");

		return size;
	}

	return HELLOWORLD286_SIZE;
}

static bool HelloWorld286_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld286  *topic = (HelloWorld286  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld286_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld286_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld286 *topic = (HelloWorld286 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld286_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld286 *HelloWorld286_create(void)
{
	HelloWorld286 *sample;
	uint32_t size = sizeof(struct HelloWorld286);

	sample = (HelloWorld286 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld286_delete(HelloWorld286 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld287
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld287_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld287_init(HelloWorld287 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld287_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld287 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld287_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld287 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld287_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld287_topic_max_size(0) + 4u);

	if (size != HELLOWORLD287_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD287_SIZE:%d\n", size, HELLOWORLD287_SIZE);
		pr_warn("size is not equal to HELLOWORLD287_SIZE\n");

		return size;
	}

	return HELLOWORLD287_SIZE;
}

static bool HelloWorld287_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld287  *topic = (HelloWorld287  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld287_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld287_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld287 *topic = (HelloWorld287 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld287_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld287 *HelloWorld287_create(void)
{
	HelloWorld287 *sample;
	uint32_t size = sizeof(struct HelloWorld287);

	sample = (HelloWorld287 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld287_delete(HelloWorld287 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld288
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld288_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld288_init(HelloWorld288 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld288_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld288 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld288_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld288 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld288_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld288_topic_max_size(0) + 4u);

	if (size != HELLOWORLD288_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD288_SIZE:%d\n", size, HELLOWORLD288_SIZE);
		pr_warn("size is not equal to HELLOWORLD288_SIZE\n");

		return size;
	}

	return HELLOWORLD288_SIZE;
}

static bool HelloWorld288_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld288  *topic = (HelloWorld288  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld288_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld288_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld288 *topic = (HelloWorld288 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld288_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld288 *HelloWorld288_create(void)
{
	HelloWorld288 *sample;
	uint32_t size = sizeof(struct HelloWorld288);

	sample = (HelloWorld288 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld288_delete(HelloWorld288 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld289
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld289_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld289_init(HelloWorld289 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld289_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld289 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld289_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld289 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld289_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld289_topic_max_size(0) + 4u);

	if (size != HELLOWORLD289_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD289_SIZE:%d\n", size, HELLOWORLD289_SIZE);
		pr_warn("size is not equal to HELLOWORLD289_SIZE\n");

		return size;
	}

	return HELLOWORLD289_SIZE;
}

static bool HelloWorld289_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld289  *topic = (HelloWorld289  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld289_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld289_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld289 *topic = (HelloWorld289 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld289_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld289 *HelloWorld289_create(void)
{
	HelloWorld289 *sample;
	uint32_t size = sizeof(struct HelloWorld289);

	sample = (HelloWorld289 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld289_delete(HelloWorld289 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld290
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld290_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld290_init(HelloWorld290 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld290_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld290 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld290_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld290 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld290_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld290_topic_max_size(0) + 4u);

	if (size != HELLOWORLD290_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD290_SIZE:%d\n", size, HELLOWORLD290_SIZE);
		pr_warn("size is not equal to HELLOWORLD290_SIZE\n");

		return size;
	}

	return HELLOWORLD290_SIZE;
}

static bool HelloWorld290_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld290  *topic = (HelloWorld290  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld290_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld290_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld290 *topic = (HelloWorld290 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld290_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld290 *HelloWorld290_create(void)
{
	HelloWorld290 *sample;
	uint32_t size = sizeof(struct HelloWorld290);

	sample = (HelloWorld290 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld290_delete(HelloWorld290 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld291
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld291_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld291_init(HelloWorld291 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld291_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld291 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld291_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld291 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld291_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld291_topic_max_size(0) + 4u);

	if (size != HELLOWORLD291_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD291_SIZE:%d\n", size, HELLOWORLD291_SIZE);
		pr_warn("size is not equal to HELLOWORLD291_SIZE\n");

		return size;
	}

	return HELLOWORLD291_SIZE;
}

static bool HelloWorld291_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld291  *topic = (HelloWorld291  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld291_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld291_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld291 *topic = (HelloWorld291 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld291_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld291 *HelloWorld291_create(void)
{
	HelloWorld291 *sample;
	uint32_t size = sizeof(struct HelloWorld291);

	sample = (HelloWorld291 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld291_delete(HelloWorld291 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld292
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld292_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld292_init(HelloWorld292 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld292_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld292 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld292_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld292 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld292_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld292_topic_max_size(0) + 4u);

	if (size != HELLOWORLD292_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD292_SIZE:%d\n", size, HELLOWORLD292_SIZE);
		pr_warn("size is not equal to HELLOWORLD292_SIZE\n");

		return size;
	}

	return HELLOWORLD292_SIZE;
}

static bool HelloWorld292_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld292  *topic = (HelloWorld292  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld292_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld292_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld292 *topic = (HelloWorld292 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld292_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld292 *HelloWorld292_create(void)
{
	HelloWorld292 *sample;
	uint32_t size = sizeof(struct HelloWorld292);

	sample = (HelloWorld292 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld292_delete(HelloWorld292 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld293
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld293_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld293_init(HelloWorld293 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld293_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld293 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld293_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld293 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld293_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld293_topic_max_size(0) + 4u);

	if (size != HELLOWORLD293_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD293_SIZE:%d\n", size, HELLOWORLD293_SIZE);
		pr_warn("size is not equal to HELLOWORLD293_SIZE\n");

		return size;
	}

	return HELLOWORLD293_SIZE;
}

static bool HelloWorld293_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld293  *topic = (HelloWorld293  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld293_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld293_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld293 *topic = (HelloWorld293 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld293_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld293 *HelloWorld293_create(void)
{
	HelloWorld293 *sample;
	uint32_t size = sizeof(struct HelloWorld293);

	sample = (HelloWorld293 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld293_delete(HelloWorld293 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld294
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld294_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld294_init(HelloWorld294 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld294_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld294 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld294_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld294 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld294_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld294_topic_max_size(0) + 4u);

	if (size != HELLOWORLD294_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD294_SIZE:%d\n", size, HELLOWORLD294_SIZE);
		pr_warn("size is not equal to HELLOWORLD294_SIZE\n");

		return size;
	}

	return HELLOWORLD294_SIZE;
}

static bool HelloWorld294_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld294  *topic = (HelloWorld294  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld294_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld294_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld294 *topic = (HelloWorld294 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld294_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld294 *HelloWorld294_create(void)
{
	HelloWorld294 *sample;
	uint32_t size = sizeof(struct HelloWorld294);

	sample = (HelloWorld294 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld294_delete(HelloWorld294 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld295
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld295_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld295_init(HelloWorld295 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld295_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld295 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld295_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld295 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld295_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld295_topic_max_size(0) + 4u);

	if (size != HELLOWORLD295_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD295_SIZE:%d\n", size, HELLOWORLD295_SIZE);
		pr_warn("size is not equal to HELLOWORLD295_SIZE\n");

		return size;
	}

	return HELLOWORLD295_SIZE;
}

static bool HelloWorld295_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld295  *topic = (HelloWorld295  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld295_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld295_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld295 *topic = (HelloWorld295 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld295_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld295 *HelloWorld295_create(void)
{
	HelloWorld295 *sample;
	uint32_t size = sizeof(struct HelloWorld295);

	sample = (HelloWorld295 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld295_delete(HelloWorld295 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld296
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld296_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld296_init(HelloWorld296 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld296_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld296 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld296_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld296 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld296_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld296_topic_max_size(0) + 4u);

	if (size != HELLOWORLD296_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD296_SIZE:%d\n", size, HELLOWORLD296_SIZE);
		pr_warn("size is not equal to HELLOWORLD296_SIZE\n");

		return size;
	}

	return HELLOWORLD296_SIZE;
}

static bool HelloWorld296_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld296  *topic = (HelloWorld296  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld296_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld296_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld296 *topic = (HelloWorld296 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld296_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld296 *HelloWorld296_create(void)
{
	HelloWorld296 *sample;
	uint32_t size = sizeof(struct HelloWorld296);

	sample = (HelloWorld296 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld296_delete(HelloWorld296 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld297
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld297_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld297_init(HelloWorld297 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld297_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld297 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld297_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld297 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld297_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld297_topic_max_size(0) + 4u);

	if (size != HELLOWORLD297_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD297_SIZE:%d\n", size, HELLOWORLD297_SIZE);
		pr_warn("size is not equal to HELLOWORLD297_SIZE\n");

		return size;
	}

	return HELLOWORLD297_SIZE;
}

static bool HelloWorld297_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld297  *topic = (HelloWorld297  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld297_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld297_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld297 *topic = (HelloWorld297 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld297_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld297 *HelloWorld297_create(void)
{
	HelloWorld297 *sample;
	uint32_t size = sizeof(struct HelloWorld297);

	sample = (HelloWorld297 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld297_delete(HelloWorld297 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld298
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld298_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld298_init(HelloWorld298 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld298_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld298 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld298_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld298 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld298_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld298_topic_max_size(0) + 4u);

	if (size != HELLOWORLD298_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD298_SIZE:%d\n", size, HELLOWORLD298_SIZE);
		pr_warn("size is not equal to HELLOWORLD298_SIZE\n");

		return size;
	}

	return HELLOWORLD298_SIZE;
}

static bool HelloWorld298_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld298  *topic = (HelloWorld298  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld298_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld298_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld298 *topic = (HelloWorld298 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld298_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld298 *HelloWorld298_create(void)
{
	HelloWorld298 *sample;
	uint32_t size = sizeof(struct HelloWorld298);

	sample = (HelloWorld298 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld298_delete(HelloWorld298 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: HelloWorld299
 * --------------------------------------------------------------------------
 */

uint32_t HelloWorld299_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void HelloWorld299_init(HelloWorld299 *sample)
{
	if (sample != NULL) {
		sample->index = 0;
		sample->message = 0;
	}
}

bool HelloWorld299_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld299 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->message)) {
		pr_debug("message serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool HelloWorld299_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld299 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->message)) {
		pr_debug("message deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t HelloWorld299_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(HelloWorld299_topic_max_size(0) + 4u);

	if (size != HELLOWORLD299_SIZE)
	{
		pr_warn("size:%d, HELLOWORLD299_SIZE:%d\n", size, HELLOWORLD299_SIZE);
		pr_warn("size is not equal to HELLOWORLD299_SIZE\n");

		return size;
	}

	return HELLOWORLD299_SIZE;
}

static bool HelloWorld299_serialize(void *data, struct serialized_payload *payload)
{
	HelloWorld299  *topic = (HelloWorld299  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!HelloWorld299_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool HelloWorld299_deserialize(void *data, struct serialized_payload *payload)
{
	HelloWorld299 *topic = (HelloWorld299 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!HelloWorld299_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}HelloWorld299 *HelloWorld299_create(void)
{
	HelloWorld299 *sample;
	uint32_t size = sizeof(struct HelloWorld299);

	sample = (HelloWorld299 *)mvbs_calloc(1, size);
	return sample;
}

void HelloWorld299_delete(HelloWorld299 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: AgentHelloWorld
 * --------------------------------------------------------------------------
 */

uint32_t AgentHelloWorld_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 8) + 8u;
	size += mcdr_get_alignment(size, 8) + 8u;

	return size - previousSize;
}

void AgentHelloWorld_init(AgentHelloWorld *sample)
{
	if (sample != NULL) {
		sample->index = 0ULL;
		sample->sn = 0ULL;
	}
}

bool AgentHelloWorld_serialize_topic(struct mvbs_cdr *cdr,
						AgentHelloWorld *topic)
{
	if (!mcdr_serialize_uint64_t(cdr, topic->index)) {
		pr_debug("index serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_uint64_t(cdr, topic->sn)) {
		pr_debug("sn serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool AgentHelloWorld_deserialize_topic(struct mvbs_cdr *cdr,
						AgentHelloWorld *topic)
{
	if (!mcdr_deserialize_uint64_t(cdr, &topic->index)) {
		pr_debug("index deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_uint64_t(cdr, &topic->sn)) {
		pr_debug("sn deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t AgentHelloWorld_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(AgentHelloWorld_topic_max_size(0) + 4u);

	if (size != AGENTHELLOWORLD_SIZE)
	{
		pr_warn("size:%d, AGENTHELLOWORLD_SIZE:%d\n", size, AGENTHELLOWORLD_SIZE);
		pr_warn("size is not equal to AGENTHELLOWORLD_SIZE\n");

		return size;
	}

	return AGENTHELLOWORLD_SIZE;
}

static bool AgentHelloWorld_serialize(void *data, struct serialized_payload *payload)
{
	AgentHelloWorld  *topic = (AgentHelloWorld  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!AgentHelloWorld_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool AgentHelloWorld_deserialize(void *data, struct serialized_payload *payload)
{
	AgentHelloWorld *topic = (AgentHelloWorld *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!AgentHelloWorld_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}AgentHelloWorld *AgentHelloWorld_create(void)
{
	AgentHelloWorld *sample;
	uint32_t size = sizeof(struct AgentHelloWorld);

	sample = (AgentHelloWorld *)mvbs_calloc(1, size);
	return sample;
}

void AgentHelloWorld_delete(AgentHelloWorld *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

const struct type_plugin  HelloWorld1_typeplugin = {
	.name		= "HelloWorld1",

	.deserialize	= HelloWorld1_deserialize,
	.serialize	= HelloWorld1_serialize,

	.type_size	= HelloWorld1_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld2_typeplugin = {
	.name		= "HelloWorld2",

	.deserialize	= HelloWorld2_deserialize,
	.serialize	= HelloWorld2_serialize,

	.type_size	= HelloWorld2_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld3_typeplugin = {
	.name		= "HelloWorld3",

	.deserialize	= HelloWorld3_deserialize,
	.serialize	= HelloWorld3_serialize,

	.type_size	= HelloWorld3_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld4_typeplugin = {
	.name		= "HelloWorld4",

	.deserialize	= HelloWorld4_deserialize,
	.serialize	= HelloWorld4_serialize,

	.type_size	= HelloWorld4_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld5_typeplugin = {
	.name		= "HelloWorld5",

	.deserialize	= HelloWorld5_deserialize,
	.serialize	= HelloWorld5_serialize,

	.type_size	= HelloWorld5_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld6_typeplugin = {
	.name		= "HelloWorld6",

	.deserialize	= HelloWorld6_deserialize,
	.serialize	= HelloWorld6_serialize,

	.type_size	= HelloWorld6_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld7_typeplugin = {
	.name		= "HelloWorld7",

	.deserialize	= HelloWorld7_deserialize,
	.serialize	= HelloWorld7_serialize,

	.type_size	= HelloWorld7_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld8_typeplugin = {
	.name		= "HelloWorld8",

	.deserialize	= HelloWorld8_deserialize,
	.serialize	= HelloWorld8_serialize,

	.type_size	= HelloWorld8_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld9_typeplugin = {
	.name		= "HelloWorld9",

	.deserialize	= HelloWorld9_deserialize,
	.serialize	= HelloWorld9_serialize,

	.type_size	= HelloWorld9_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld10_typeplugin = {
	.name		= "HelloWorld10",

	.deserialize	= HelloWorld10_deserialize,
	.serialize	= HelloWorld10_serialize,

	.type_size	= HelloWorld10_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld11_typeplugin = {
	.name		= "HelloWorld11",

	.deserialize	= HelloWorld11_deserialize,
	.serialize	= HelloWorld11_serialize,

	.type_size	= HelloWorld11_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld12_typeplugin = {
	.name		= "HelloWorld12",

	.deserialize	= HelloWorld12_deserialize,
	.serialize	= HelloWorld12_serialize,

	.type_size	= HelloWorld12_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld13_typeplugin = {
	.name		= "HelloWorld13",

	.deserialize	= HelloWorld13_deserialize,
	.serialize	= HelloWorld13_serialize,

	.type_size	= HelloWorld13_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld14_typeplugin = {
	.name		= "HelloWorld14",

	.deserialize	= HelloWorld14_deserialize,
	.serialize	= HelloWorld14_serialize,

	.type_size	= HelloWorld14_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld15_typeplugin = {
	.name		= "HelloWorld15",

	.deserialize	= HelloWorld15_deserialize,
	.serialize	= HelloWorld15_serialize,

	.type_size	= HelloWorld15_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld16_typeplugin = {
	.name		= "HelloWorld16",

	.deserialize	= HelloWorld16_deserialize,
	.serialize	= HelloWorld16_serialize,

	.type_size	= HelloWorld16_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld17_typeplugin = {
	.name		= "HelloWorld17",

	.deserialize	= HelloWorld17_deserialize,
	.serialize	= HelloWorld17_serialize,

	.type_size	= HelloWorld17_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld18_typeplugin = {
	.name		= "HelloWorld18",

	.deserialize	= HelloWorld18_deserialize,
	.serialize	= HelloWorld18_serialize,

	.type_size	= HelloWorld18_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld19_typeplugin = {
	.name		= "HelloWorld19",

	.deserialize	= HelloWorld19_deserialize,
	.serialize	= HelloWorld19_serialize,

	.type_size	= HelloWorld19_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld20_typeplugin = {
	.name		= "HelloWorld20",

	.deserialize	= HelloWorld20_deserialize,
	.serialize	= HelloWorld20_serialize,

	.type_size	= HelloWorld20_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld21_typeplugin = {
	.name		= "HelloWorld21",

	.deserialize	= HelloWorld21_deserialize,
	.serialize	= HelloWorld21_serialize,

	.type_size	= HelloWorld21_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld22_typeplugin = {
	.name		= "HelloWorld22",

	.deserialize	= HelloWorld22_deserialize,
	.serialize	= HelloWorld22_serialize,

	.type_size	= HelloWorld22_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld23_typeplugin = {
	.name		= "HelloWorld23",

	.deserialize	= HelloWorld23_deserialize,
	.serialize	= HelloWorld23_serialize,

	.type_size	= HelloWorld23_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld24_typeplugin = {
	.name		= "HelloWorld24",

	.deserialize	= HelloWorld24_deserialize,
	.serialize	= HelloWorld24_serialize,

	.type_size	= HelloWorld24_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld25_typeplugin = {
	.name		= "HelloWorld25",

	.deserialize	= HelloWorld25_deserialize,
	.serialize	= HelloWorld25_serialize,

	.type_size	= HelloWorld25_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld26_typeplugin = {
	.name		= "HelloWorld26",

	.deserialize	= HelloWorld26_deserialize,
	.serialize	= HelloWorld26_serialize,

	.type_size	= HelloWorld26_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld27_typeplugin = {
	.name		= "HelloWorld27",

	.deserialize	= HelloWorld27_deserialize,
	.serialize	= HelloWorld27_serialize,

	.type_size	= HelloWorld27_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld28_typeplugin = {
	.name		= "HelloWorld28",

	.deserialize	= HelloWorld28_deserialize,
	.serialize	= HelloWorld28_serialize,

	.type_size	= HelloWorld28_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld29_typeplugin = {
	.name		= "HelloWorld29",

	.deserialize	= HelloWorld29_deserialize,
	.serialize	= HelloWorld29_serialize,

	.type_size	= HelloWorld29_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld30_typeplugin = {
	.name		= "HelloWorld30",

	.deserialize	= HelloWorld30_deserialize,
	.serialize	= HelloWorld30_serialize,

	.type_size	= HelloWorld30_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld31_typeplugin = {
	.name		= "HelloWorld31",

	.deserialize	= HelloWorld31_deserialize,
	.serialize	= HelloWorld31_serialize,

	.type_size	= HelloWorld31_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld32_typeplugin = {
	.name		= "HelloWorld32",

	.deserialize	= HelloWorld32_deserialize,
	.serialize	= HelloWorld32_serialize,

	.type_size	= HelloWorld32_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld33_typeplugin = {
	.name		= "HelloWorld33",

	.deserialize	= HelloWorld33_deserialize,
	.serialize	= HelloWorld33_serialize,

	.type_size	= HelloWorld33_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld34_typeplugin = {
	.name		= "HelloWorld34",

	.deserialize	= HelloWorld34_deserialize,
	.serialize	= HelloWorld34_serialize,

	.type_size	= HelloWorld34_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld35_typeplugin = {
	.name		= "HelloWorld35",

	.deserialize	= HelloWorld35_deserialize,
	.serialize	= HelloWorld35_serialize,

	.type_size	= HelloWorld35_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld36_typeplugin = {
	.name		= "HelloWorld36",

	.deserialize	= HelloWorld36_deserialize,
	.serialize	= HelloWorld36_serialize,

	.type_size	= HelloWorld36_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld37_typeplugin = {
	.name		= "HelloWorld37",

	.deserialize	= HelloWorld37_deserialize,
	.serialize	= HelloWorld37_serialize,

	.type_size	= HelloWorld37_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld38_typeplugin = {
	.name		= "HelloWorld38",

	.deserialize	= HelloWorld38_deserialize,
	.serialize	= HelloWorld38_serialize,

	.type_size	= HelloWorld38_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld39_typeplugin = {
	.name		= "HelloWorld39",

	.deserialize	= HelloWorld39_deserialize,
	.serialize	= HelloWorld39_serialize,

	.type_size	= HelloWorld39_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld40_typeplugin = {
	.name		= "HelloWorld40",

	.deserialize	= HelloWorld40_deserialize,
	.serialize	= HelloWorld40_serialize,

	.type_size	= HelloWorld40_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld41_typeplugin = {
	.name		= "HelloWorld41",

	.deserialize	= HelloWorld41_deserialize,
	.serialize	= HelloWorld41_serialize,

	.type_size	= HelloWorld41_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld42_typeplugin = {
	.name		= "HelloWorld42",

	.deserialize	= HelloWorld42_deserialize,
	.serialize	= HelloWorld42_serialize,

	.type_size	= HelloWorld42_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld43_typeplugin = {
	.name		= "HelloWorld43",

	.deserialize	= HelloWorld43_deserialize,
	.serialize	= HelloWorld43_serialize,

	.type_size	= HelloWorld43_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld44_typeplugin = {
	.name		= "HelloWorld44",

	.deserialize	= HelloWorld44_deserialize,
	.serialize	= HelloWorld44_serialize,

	.type_size	= HelloWorld44_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld45_typeplugin = {
	.name		= "HelloWorld45",

	.deserialize	= HelloWorld45_deserialize,
	.serialize	= HelloWorld45_serialize,

	.type_size	= HelloWorld45_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld46_typeplugin = {
	.name		= "HelloWorld46",

	.deserialize	= HelloWorld46_deserialize,
	.serialize	= HelloWorld46_serialize,

	.type_size	= HelloWorld46_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld47_typeplugin = {
	.name		= "HelloWorld47",

	.deserialize	= HelloWorld47_deserialize,
	.serialize	= HelloWorld47_serialize,

	.type_size	= HelloWorld47_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld48_typeplugin = {
	.name		= "HelloWorld48",

	.deserialize	= HelloWorld48_deserialize,
	.serialize	= HelloWorld48_serialize,

	.type_size	= HelloWorld48_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld49_typeplugin = {
	.name		= "HelloWorld49",

	.deserialize	= HelloWorld49_deserialize,
	.serialize	= HelloWorld49_serialize,

	.type_size	= HelloWorld49_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld50_typeplugin = {
	.name		= "HelloWorld50",

	.deserialize	= HelloWorld50_deserialize,
	.serialize	= HelloWorld50_serialize,

	.type_size	= HelloWorld50_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld51_typeplugin = {
	.name		= "HelloWorld51",

	.deserialize	= HelloWorld51_deserialize,
	.serialize	= HelloWorld51_serialize,

	.type_size	= HelloWorld51_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld52_typeplugin = {
	.name		= "HelloWorld52",

	.deserialize	= HelloWorld52_deserialize,
	.serialize	= HelloWorld52_serialize,

	.type_size	= HelloWorld52_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld53_typeplugin = {
	.name		= "HelloWorld53",

	.deserialize	= HelloWorld53_deserialize,
	.serialize	= HelloWorld53_serialize,

	.type_size	= HelloWorld53_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld54_typeplugin = {
	.name		= "HelloWorld54",

	.deserialize	= HelloWorld54_deserialize,
	.serialize	= HelloWorld54_serialize,

	.type_size	= HelloWorld54_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld55_typeplugin = {
	.name		= "HelloWorld55",

	.deserialize	= HelloWorld55_deserialize,
	.serialize	= HelloWorld55_serialize,

	.type_size	= HelloWorld55_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld56_typeplugin = {
	.name		= "HelloWorld56",

	.deserialize	= HelloWorld56_deserialize,
	.serialize	= HelloWorld56_serialize,

	.type_size	= HelloWorld56_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld57_typeplugin = {
	.name		= "HelloWorld57",

	.deserialize	= HelloWorld57_deserialize,
	.serialize	= HelloWorld57_serialize,

	.type_size	= HelloWorld57_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld58_typeplugin = {
	.name		= "HelloWorld58",

	.deserialize	= HelloWorld58_deserialize,
	.serialize	= HelloWorld58_serialize,

	.type_size	= HelloWorld58_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld59_typeplugin = {
	.name		= "HelloWorld59",

	.deserialize	= HelloWorld59_deserialize,
	.serialize	= HelloWorld59_serialize,

	.type_size	= HelloWorld59_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld60_typeplugin = {
	.name		= "HelloWorld60",

	.deserialize	= HelloWorld60_deserialize,
	.serialize	= HelloWorld60_serialize,

	.type_size	= HelloWorld60_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld61_typeplugin = {
	.name		= "HelloWorld61",

	.deserialize	= HelloWorld61_deserialize,
	.serialize	= HelloWorld61_serialize,

	.type_size	= HelloWorld61_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld62_typeplugin = {
	.name		= "HelloWorld62",

	.deserialize	= HelloWorld62_deserialize,
	.serialize	= HelloWorld62_serialize,

	.type_size	= HelloWorld62_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld63_typeplugin = {
	.name		= "HelloWorld63",

	.deserialize	= HelloWorld63_deserialize,
	.serialize	= HelloWorld63_serialize,

	.type_size	= HelloWorld63_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld64_typeplugin = {
	.name		= "HelloWorld64",

	.deserialize	= HelloWorld64_deserialize,
	.serialize	= HelloWorld64_serialize,

	.type_size	= HelloWorld64_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld65_typeplugin = {
	.name		= "HelloWorld65",

	.deserialize	= HelloWorld65_deserialize,
	.serialize	= HelloWorld65_serialize,

	.type_size	= HelloWorld65_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld66_typeplugin = {
	.name		= "HelloWorld66",

	.deserialize	= HelloWorld66_deserialize,
	.serialize	= HelloWorld66_serialize,

	.type_size	= HelloWorld66_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld67_typeplugin = {
	.name		= "HelloWorld67",

	.deserialize	= HelloWorld67_deserialize,
	.serialize	= HelloWorld67_serialize,

	.type_size	= HelloWorld67_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld68_typeplugin = {
	.name		= "HelloWorld68",

	.deserialize	= HelloWorld68_deserialize,
	.serialize	= HelloWorld68_serialize,

	.type_size	= HelloWorld68_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld69_typeplugin = {
	.name		= "HelloWorld69",

	.deserialize	= HelloWorld69_deserialize,
	.serialize	= HelloWorld69_serialize,

	.type_size	= HelloWorld69_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld70_typeplugin = {
	.name		= "HelloWorld70",

	.deserialize	= HelloWorld70_deserialize,
	.serialize	= HelloWorld70_serialize,

	.type_size	= HelloWorld70_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld71_typeplugin = {
	.name		= "HelloWorld71",

	.deserialize	= HelloWorld71_deserialize,
	.serialize	= HelloWorld71_serialize,

	.type_size	= HelloWorld71_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld72_typeplugin = {
	.name		= "HelloWorld72",

	.deserialize	= HelloWorld72_deserialize,
	.serialize	= HelloWorld72_serialize,

	.type_size	= HelloWorld72_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld73_typeplugin = {
	.name		= "HelloWorld73",

	.deserialize	= HelloWorld73_deserialize,
	.serialize	= HelloWorld73_serialize,

	.type_size	= HelloWorld73_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld74_typeplugin = {
	.name		= "HelloWorld74",

	.deserialize	= HelloWorld74_deserialize,
	.serialize	= HelloWorld74_serialize,

	.type_size	= HelloWorld74_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld75_typeplugin = {
	.name		= "HelloWorld75",

	.deserialize	= HelloWorld75_deserialize,
	.serialize	= HelloWorld75_serialize,

	.type_size	= HelloWorld75_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld76_typeplugin = {
	.name		= "HelloWorld76",

	.deserialize	= HelloWorld76_deserialize,
	.serialize	= HelloWorld76_serialize,

	.type_size	= HelloWorld76_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld77_typeplugin = {
	.name		= "HelloWorld77",

	.deserialize	= HelloWorld77_deserialize,
	.serialize	= HelloWorld77_serialize,

	.type_size	= HelloWorld77_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld78_typeplugin = {
	.name		= "HelloWorld78",

	.deserialize	= HelloWorld78_deserialize,
	.serialize	= HelloWorld78_serialize,

	.type_size	= HelloWorld78_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld79_typeplugin = {
	.name		= "HelloWorld79",

	.deserialize	= HelloWorld79_deserialize,
	.serialize	= HelloWorld79_serialize,

	.type_size	= HelloWorld79_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld80_typeplugin = {
	.name		= "HelloWorld80",

	.deserialize	= HelloWorld80_deserialize,
	.serialize	= HelloWorld80_serialize,

	.type_size	= HelloWorld80_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld81_typeplugin = {
	.name		= "HelloWorld81",

	.deserialize	= HelloWorld81_deserialize,
	.serialize	= HelloWorld81_serialize,

	.type_size	= HelloWorld81_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld82_typeplugin = {
	.name		= "HelloWorld82",

	.deserialize	= HelloWorld82_deserialize,
	.serialize	= HelloWorld82_serialize,

	.type_size	= HelloWorld82_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld83_typeplugin = {
	.name		= "HelloWorld83",

	.deserialize	= HelloWorld83_deserialize,
	.serialize	= HelloWorld83_serialize,

	.type_size	= HelloWorld83_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld84_typeplugin = {
	.name		= "HelloWorld84",

	.deserialize	= HelloWorld84_deserialize,
	.serialize	= HelloWorld84_serialize,

	.type_size	= HelloWorld84_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld85_typeplugin = {
	.name		= "HelloWorld85",

	.deserialize	= HelloWorld85_deserialize,
	.serialize	= HelloWorld85_serialize,

	.type_size	= HelloWorld85_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld86_typeplugin = {
	.name		= "HelloWorld86",

	.deserialize	= HelloWorld86_deserialize,
	.serialize	= HelloWorld86_serialize,

	.type_size	= HelloWorld86_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld87_typeplugin = {
	.name		= "HelloWorld87",

	.deserialize	= HelloWorld87_deserialize,
	.serialize	= HelloWorld87_serialize,

	.type_size	= HelloWorld87_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld88_typeplugin = {
	.name		= "HelloWorld88",

	.deserialize	= HelloWorld88_deserialize,
	.serialize	= HelloWorld88_serialize,

	.type_size	= HelloWorld88_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld89_typeplugin = {
	.name		= "HelloWorld89",

	.deserialize	= HelloWorld89_deserialize,
	.serialize	= HelloWorld89_serialize,

	.type_size	= HelloWorld89_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld90_typeplugin = {
	.name		= "HelloWorld90",

	.deserialize	= HelloWorld90_deserialize,
	.serialize	= HelloWorld90_serialize,

	.type_size	= HelloWorld90_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld91_typeplugin = {
	.name		= "HelloWorld91",

	.deserialize	= HelloWorld91_deserialize,
	.serialize	= HelloWorld91_serialize,

	.type_size	= HelloWorld91_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld92_typeplugin = {
	.name		= "HelloWorld92",

	.deserialize	= HelloWorld92_deserialize,
	.serialize	= HelloWorld92_serialize,

	.type_size	= HelloWorld92_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld93_typeplugin = {
	.name		= "HelloWorld93",

	.deserialize	= HelloWorld93_deserialize,
	.serialize	= HelloWorld93_serialize,

	.type_size	= HelloWorld93_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld94_typeplugin = {
	.name		= "HelloWorld94",

	.deserialize	= HelloWorld94_deserialize,
	.serialize	= HelloWorld94_serialize,

	.type_size	= HelloWorld94_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld95_typeplugin = {
	.name		= "HelloWorld95",

	.deserialize	= HelloWorld95_deserialize,
	.serialize	= HelloWorld95_serialize,

	.type_size	= HelloWorld95_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld96_typeplugin = {
	.name		= "HelloWorld96",

	.deserialize	= HelloWorld96_deserialize,
	.serialize	= HelloWorld96_serialize,

	.type_size	= HelloWorld96_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld97_typeplugin = {
	.name		= "HelloWorld97",

	.deserialize	= HelloWorld97_deserialize,
	.serialize	= HelloWorld97_serialize,

	.type_size	= HelloWorld97_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld98_typeplugin = {
	.name		= "HelloWorld98",

	.deserialize	= HelloWorld98_deserialize,
	.serialize	= HelloWorld98_serialize,

	.type_size	= HelloWorld98_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld99_typeplugin = {
	.name		= "HelloWorld99",

	.deserialize	= HelloWorld99_deserialize,
	.serialize	= HelloWorld99_serialize,

	.type_size	= HelloWorld99_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld100_typeplugin = {
	.name		= "HelloWorld100",

	.deserialize	= HelloWorld100_deserialize,
	.serialize	= HelloWorld100_serialize,

	.type_size	= HelloWorld100_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld101_typeplugin = {
	.name		= "HelloWorld101",

	.deserialize	= HelloWorld101_deserialize,
	.serialize	= HelloWorld101_serialize,

	.type_size	= HelloWorld101_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld102_typeplugin = {
	.name		= "HelloWorld102",

	.deserialize	= HelloWorld102_deserialize,
	.serialize	= HelloWorld102_serialize,

	.type_size	= HelloWorld102_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld103_typeplugin = {
	.name		= "HelloWorld103",

	.deserialize	= HelloWorld103_deserialize,
	.serialize	= HelloWorld103_serialize,

	.type_size	= HelloWorld103_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld104_typeplugin = {
	.name		= "HelloWorld104",

	.deserialize	= HelloWorld104_deserialize,
	.serialize	= HelloWorld104_serialize,

	.type_size	= HelloWorld104_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld105_typeplugin = {
	.name		= "HelloWorld105",

	.deserialize	= HelloWorld105_deserialize,
	.serialize	= HelloWorld105_serialize,

	.type_size	= HelloWorld105_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld106_typeplugin = {
	.name		= "HelloWorld106",

	.deserialize	= HelloWorld106_deserialize,
	.serialize	= HelloWorld106_serialize,

	.type_size	= HelloWorld106_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld107_typeplugin = {
	.name		= "HelloWorld107",

	.deserialize	= HelloWorld107_deserialize,
	.serialize	= HelloWorld107_serialize,

	.type_size	= HelloWorld107_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld108_typeplugin = {
	.name		= "HelloWorld108",

	.deserialize	= HelloWorld108_deserialize,
	.serialize	= HelloWorld108_serialize,

	.type_size	= HelloWorld108_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld109_typeplugin = {
	.name		= "HelloWorld109",

	.deserialize	= HelloWorld109_deserialize,
	.serialize	= HelloWorld109_serialize,

	.type_size	= HelloWorld109_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld110_typeplugin = {
	.name		= "HelloWorld110",

	.deserialize	= HelloWorld110_deserialize,
	.serialize	= HelloWorld110_serialize,

	.type_size	= HelloWorld110_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld111_typeplugin = {
	.name		= "HelloWorld111",

	.deserialize	= HelloWorld111_deserialize,
	.serialize	= HelloWorld111_serialize,

	.type_size	= HelloWorld111_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld112_typeplugin = {
	.name		= "HelloWorld112",

	.deserialize	= HelloWorld112_deserialize,
	.serialize	= HelloWorld112_serialize,

	.type_size	= HelloWorld112_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld113_typeplugin = {
	.name		= "HelloWorld113",

	.deserialize	= HelloWorld113_deserialize,
	.serialize	= HelloWorld113_serialize,

	.type_size	= HelloWorld113_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld114_typeplugin = {
	.name		= "HelloWorld114",

	.deserialize	= HelloWorld114_deserialize,
	.serialize	= HelloWorld114_serialize,

	.type_size	= HelloWorld114_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld115_typeplugin = {
	.name		= "HelloWorld115",

	.deserialize	= HelloWorld115_deserialize,
	.serialize	= HelloWorld115_serialize,

	.type_size	= HelloWorld115_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld116_typeplugin = {
	.name		= "HelloWorld116",

	.deserialize	= HelloWorld116_deserialize,
	.serialize	= HelloWorld116_serialize,

	.type_size	= HelloWorld116_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld117_typeplugin = {
	.name		= "HelloWorld117",

	.deserialize	= HelloWorld117_deserialize,
	.serialize	= HelloWorld117_serialize,

	.type_size	= HelloWorld117_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld118_typeplugin = {
	.name		= "HelloWorld118",

	.deserialize	= HelloWorld118_deserialize,
	.serialize	= HelloWorld118_serialize,

	.type_size	= HelloWorld118_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld119_typeplugin = {
	.name		= "HelloWorld119",

	.deserialize	= HelloWorld119_deserialize,
	.serialize	= HelloWorld119_serialize,

	.type_size	= HelloWorld119_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld120_typeplugin = {
	.name		= "HelloWorld120",

	.deserialize	= HelloWorld120_deserialize,
	.serialize	= HelloWorld120_serialize,

	.type_size	= HelloWorld120_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld121_typeplugin = {
	.name		= "HelloWorld121",

	.deserialize	= HelloWorld121_deserialize,
	.serialize	= HelloWorld121_serialize,

	.type_size	= HelloWorld121_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld122_typeplugin = {
	.name		= "HelloWorld122",

	.deserialize	= HelloWorld122_deserialize,
	.serialize	= HelloWorld122_serialize,

	.type_size	= HelloWorld122_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld123_typeplugin = {
	.name		= "HelloWorld123",

	.deserialize	= HelloWorld123_deserialize,
	.serialize	= HelloWorld123_serialize,

	.type_size	= HelloWorld123_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld124_typeplugin = {
	.name		= "HelloWorld124",

	.deserialize	= HelloWorld124_deserialize,
	.serialize	= HelloWorld124_serialize,

	.type_size	= HelloWorld124_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld125_typeplugin = {
	.name		= "HelloWorld125",

	.deserialize	= HelloWorld125_deserialize,
	.serialize	= HelloWorld125_serialize,

	.type_size	= HelloWorld125_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld126_typeplugin = {
	.name		= "HelloWorld126",

	.deserialize	= HelloWorld126_deserialize,
	.serialize	= HelloWorld126_serialize,

	.type_size	= HelloWorld126_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld127_typeplugin = {
	.name		= "HelloWorld127",

	.deserialize	= HelloWorld127_deserialize,
	.serialize	= HelloWorld127_serialize,

	.type_size	= HelloWorld127_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld128_typeplugin = {
	.name		= "HelloWorld128",

	.deserialize	= HelloWorld128_deserialize,
	.serialize	= HelloWorld128_serialize,

	.type_size	= HelloWorld128_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld129_typeplugin = {
	.name		= "HelloWorld129",

	.deserialize	= HelloWorld129_deserialize,
	.serialize	= HelloWorld129_serialize,

	.type_size	= HelloWorld129_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld130_typeplugin = {
	.name		= "HelloWorld130",

	.deserialize	= HelloWorld130_deserialize,
	.serialize	= HelloWorld130_serialize,

	.type_size	= HelloWorld130_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld131_typeplugin = {
	.name		= "HelloWorld131",

	.deserialize	= HelloWorld131_deserialize,
	.serialize	= HelloWorld131_serialize,

	.type_size	= HelloWorld131_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld132_typeplugin = {
	.name		= "HelloWorld132",

	.deserialize	= HelloWorld132_deserialize,
	.serialize	= HelloWorld132_serialize,

	.type_size	= HelloWorld132_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld133_typeplugin = {
	.name		= "HelloWorld133",

	.deserialize	= HelloWorld133_deserialize,
	.serialize	= HelloWorld133_serialize,

	.type_size	= HelloWorld133_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld134_typeplugin = {
	.name		= "HelloWorld134",

	.deserialize	= HelloWorld134_deserialize,
	.serialize	= HelloWorld134_serialize,

	.type_size	= HelloWorld134_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld135_typeplugin = {
	.name		= "HelloWorld135",

	.deserialize	= HelloWorld135_deserialize,
	.serialize	= HelloWorld135_serialize,

	.type_size	= HelloWorld135_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld136_typeplugin = {
	.name		= "HelloWorld136",

	.deserialize	= HelloWorld136_deserialize,
	.serialize	= HelloWorld136_serialize,

	.type_size	= HelloWorld136_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld137_typeplugin = {
	.name		= "HelloWorld137",

	.deserialize	= HelloWorld137_deserialize,
	.serialize	= HelloWorld137_serialize,

	.type_size	= HelloWorld137_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld138_typeplugin = {
	.name		= "HelloWorld138",

	.deserialize	= HelloWorld138_deserialize,
	.serialize	= HelloWorld138_serialize,

	.type_size	= HelloWorld138_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld139_typeplugin = {
	.name		= "HelloWorld139",

	.deserialize	= HelloWorld139_deserialize,
	.serialize	= HelloWorld139_serialize,

	.type_size	= HelloWorld139_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld140_typeplugin = {
	.name		= "HelloWorld140",

	.deserialize	= HelloWorld140_deserialize,
	.serialize	= HelloWorld140_serialize,

	.type_size	= HelloWorld140_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld141_typeplugin = {
	.name		= "HelloWorld141",

	.deserialize	= HelloWorld141_deserialize,
	.serialize	= HelloWorld141_serialize,

	.type_size	= HelloWorld141_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld142_typeplugin = {
	.name		= "HelloWorld142",

	.deserialize	= HelloWorld142_deserialize,
	.serialize	= HelloWorld142_serialize,

	.type_size	= HelloWorld142_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld143_typeplugin = {
	.name		= "HelloWorld143",

	.deserialize	= HelloWorld143_deserialize,
	.serialize	= HelloWorld143_serialize,

	.type_size	= HelloWorld143_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld144_typeplugin = {
	.name		= "HelloWorld144",

	.deserialize	= HelloWorld144_deserialize,
	.serialize	= HelloWorld144_serialize,

	.type_size	= HelloWorld144_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld145_typeplugin = {
	.name		= "HelloWorld145",

	.deserialize	= HelloWorld145_deserialize,
	.serialize	= HelloWorld145_serialize,

	.type_size	= HelloWorld145_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld146_typeplugin = {
	.name		= "HelloWorld146",

	.deserialize	= HelloWorld146_deserialize,
	.serialize	= HelloWorld146_serialize,

	.type_size	= HelloWorld146_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld147_typeplugin = {
	.name		= "HelloWorld147",

	.deserialize	= HelloWorld147_deserialize,
	.serialize	= HelloWorld147_serialize,

	.type_size	= HelloWorld147_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld148_typeplugin = {
	.name		= "HelloWorld148",

	.deserialize	= HelloWorld148_deserialize,
	.serialize	= HelloWorld148_serialize,

	.type_size	= HelloWorld148_get_type_size,
	.crc16		= "920A"
};


const struct type_plugin  HelloWorld149_typeplugin = {
	.name		= "HelloWorld149",

	.deserialize	= HelloWorld149_deserialize,
	.serialize	= HelloWorld149_serialize,

	.type_size	= HelloWorld149_get_type_size,
	.crc16		= "4144"
};


const struct type_plugin  HelloWorld151_typeplugin = {
	.name		= "HelloWorld151",

	.deserialize	= HelloWorld151_deserialize,
	.serialize	= HelloWorld151_serialize,

	.type_size	= HelloWorld151_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld152_typeplugin = {
	.name		= "HelloWorld152",

	.deserialize	= HelloWorld152_deserialize,
	.serialize	= HelloWorld152_serialize,

	.type_size	= HelloWorld152_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld153_typeplugin = {
	.name		= "HelloWorld153",

	.deserialize	= HelloWorld153_deserialize,
	.serialize	= HelloWorld153_serialize,

	.type_size	= HelloWorld153_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld154_typeplugin = {
	.name		= "HelloWorld154",

	.deserialize	= HelloWorld154_deserialize,
	.serialize	= HelloWorld154_serialize,

	.type_size	= HelloWorld154_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld155_typeplugin = {
	.name		= "HelloWorld155",

	.deserialize	= HelloWorld155_deserialize,
	.serialize	= HelloWorld155_serialize,

	.type_size	= HelloWorld155_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld156_typeplugin = {
	.name		= "HelloWorld156",

	.deserialize	= HelloWorld156_deserialize,
	.serialize	= HelloWorld156_serialize,

	.type_size	= HelloWorld156_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld157_typeplugin = {
	.name		= "HelloWorld157",

	.deserialize	= HelloWorld157_deserialize,
	.serialize	= HelloWorld157_serialize,

	.type_size	= HelloWorld157_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld158_typeplugin = {
	.name		= "HelloWorld158",

	.deserialize	= HelloWorld158_deserialize,
	.serialize	= HelloWorld158_serialize,

	.type_size	= HelloWorld158_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld159_typeplugin = {
	.name		= "HelloWorld159",

	.deserialize	= HelloWorld159_deserialize,
	.serialize	= HelloWorld159_serialize,

	.type_size	= HelloWorld159_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld160_typeplugin = {
	.name		= "HelloWorld160",

	.deserialize	= HelloWorld160_deserialize,
	.serialize	= HelloWorld160_serialize,

	.type_size	= HelloWorld160_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld161_typeplugin = {
	.name		= "HelloWorld161",

	.deserialize	= HelloWorld161_deserialize,
	.serialize	= HelloWorld161_serialize,

	.type_size	= HelloWorld161_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld162_typeplugin = {
	.name		= "HelloWorld162",

	.deserialize	= HelloWorld162_deserialize,
	.serialize	= HelloWorld162_serialize,

	.type_size	= HelloWorld162_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld163_typeplugin = {
	.name		= "HelloWorld163",

	.deserialize	= HelloWorld163_deserialize,
	.serialize	= HelloWorld163_serialize,

	.type_size	= HelloWorld163_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld164_typeplugin = {
	.name		= "HelloWorld164",

	.deserialize	= HelloWorld164_deserialize,
	.serialize	= HelloWorld164_serialize,

	.type_size	= HelloWorld164_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld165_typeplugin = {
	.name		= "HelloWorld165",

	.deserialize	= HelloWorld165_deserialize,
	.serialize	= HelloWorld165_serialize,

	.type_size	= HelloWorld165_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld166_typeplugin = {
	.name		= "HelloWorld166",

	.deserialize	= HelloWorld166_deserialize,
	.serialize	= HelloWorld166_serialize,

	.type_size	= HelloWorld166_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld167_typeplugin = {
	.name		= "HelloWorld167",

	.deserialize	= HelloWorld167_deserialize,
	.serialize	= HelloWorld167_serialize,

	.type_size	= HelloWorld167_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld168_typeplugin = {
	.name		= "HelloWorld168",

	.deserialize	= HelloWorld168_deserialize,
	.serialize	= HelloWorld168_serialize,

	.type_size	= HelloWorld168_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld169_typeplugin = {
	.name		= "HelloWorld169",

	.deserialize	= HelloWorld169_deserialize,
	.serialize	= HelloWorld169_serialize,

	.type_size	= HelloWorld169_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld170_typeplugin = {
	.name		= "HelloWorld170",

	.deserialize	= HelloWorld170_deserialize,
	.serialize	= HelloWorld170_serialize,

	.type_size	= HelloWorld170_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld171_typeplugin = {
	.name		= "HelloWorld171",

	.deserialize	= HelloWorld171_deserialize,
	.serialize	= HelloWorld171_serialize,

	.type_size	= HelloWorld171_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld172_typeplugin = {
	.name		= "HelloWorld172",

	.deserialize	= HelloWorld172_deserialize,
	.serialize	= HelloWorld172_serialize,

	.type_size	= HelloWorld172_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld173_typeplugin = {
	.name		= "HelloWorld173",

	.deserialize	= HelloWorld173_deserialize,
	.serialize	= HelloWorld173_serialize,

	.type_size	= HelloWorld173_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld174_typeplugin = {
	.name		= "HelloWorld174",

	.deserialize	= HelloWorld174_deserialize,
	.serialize	= HelloWorld174_serialize,

	.type_size	= HelloWorld174_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld175_typeplugin = {
	.name		= "HelloWorld175",

	.deserialize	= HelloWorld175_deserialize,
	.serialize	= HelloWorld175_serialize,

	.type_size	= HelloWorld175_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld176_typeplugin = {
	.name		= "HelloWorld176",

	.deserialize	= HelloWorld176_deserialize,
	.serialize	= HelloWorld176_serialize,

	.type_size	= HelloWorld176_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld177_typeplugin = {
	.name		= "HelloWorld177",

	.deserialize	= HelloWorld177_deserialize,
	.serialize	= HelloWorld177_serialize,

	.type_size	= HelloWorld177_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld178_typeplugin = {
	.name		= "HelloWorld178",

	.deserialize	= HelloWorld178_deserialize,
	.serialize	= HelloWorld178_serialize,

	.type_size	= HelloWorld178_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld179_typeplugin = {
	.name		= "HelloWorld179",

	.deserialize	= HelloWorld179_deserialize,
	.serialize	= HelloWorld179_serialize,

	.type_size	= HelloWorld179_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld180_typeplugin = {
	.name		= "HelloWorld180",

	.deserialize	= HelloWorld180_deserialize,
	.serialize	= HelloWorld180_serialize,

	.type_size	= HelloWorld180_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld181_typeplugin = {
	.name		= "HelloWorld181",

	.deserialize	= HelloWorld181_deserialize,
	.serialize	= HelloWorld181_serialize,

	.type_size	= HelloWorld181_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld182_typeplugin = {
	.name		= "HelloWorld182",

	.deserialize	= HelloWorld182_deserialize,
	.serialize	= HelloWorld182_serialize,

	.type_size	= HelloWorld182_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld183_typeplugin = {
	.name		= "HelloWorld183",

	.deserialize	= HelloWorld183_deserialize,
	.serialize	= HelloWorld183_serialize,

	.type_size	= HelloWorld183_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld184_typeplugin = {
	.name		= "HelloWorld184",

	.deserialize	= HelloWorld184_deserialize,
	.serialize	= HelloWorld184_serialize,

	.type_size	= HelloWorld184_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld185_typeplugin = {
	.name		= "HelloWorld185",

	.deserialize	= HelloWorld185_deserialize,
	.serialize	= HelloWorld185_serialize,

	.type_size	= HelloWorld185_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld186_typeplugin = {
	.name		= "HelloWorld186",

	.deserialize	= HelloWorld186_deserialize,
	.serialize	= HelloWorld186_serialize,

	.type_size	= HelloWorld186_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld187_typeplugin = {
	.name		= "HelloWorld187",

	.deserialize	= HelloWorld187_deserialize,
	.serialize	= HelloWorld187_serialize,

	.type_size	= HelloWorld187_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld188_typeplugin = {
	.name		= "HelloWorld188",

	.deserialize	= HelloWorld188_deserialize,
	.serialize	= HelloWorld188_serialize,

	.type_size	= HelloWorld188_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld189_typeplugin = {
	.name		= "HelloWorld189",

	.deserialize	= HelloWorld189_deserialize,
	.serialize	= HelloWorld189_serialize,

	.type_size	= HelloWorld189_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld190_typeplugin = {
	.name		= "HelloWorld190",

	.deserialize	= HelloWorld190_deserialize,
	.serialize	= HelloWorld190_serialize,

	.type_size	= HelloWorld190_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld191_typeplugin = {
	.name		= "HelloWorld191",

	.deserialize	= HelloWorld191_deserialize,
	.serialize	= HelloWorld191_serialize,

	.type_size	= HelloWorld191_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld192_typeplugin = {
	.name		= "HelloWorld192",

	.deserialize	= HelloWorld192_deserialize,
	.serialize	= HelloWorld192_serialize,

	.type_size	= HelloWorld192_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld193_typeplugin = {
	.name		= "HelloWorld193",

	.deserialize	= HelloWorld193_deserialize,
	.serialize	= HelloWorld193_serialize,

	.type_size	= HelloWorld193_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld194_typeplugin = {
	.name		= "HelloWorld194",

	.deserialize	= HelloWorld194_deserialize,
	.serialize	= HelloWorld194_serialize,

	.type_size	= HelloWorld194_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld195_typeplugin = {
	.name		= "HelloWorld195",

	.deserialize	= HelloWorld195_deserialize,
	.serialize	= HelloWorld195_serialize,

	.type_size	= HelloWorld195_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld196_typeplugin = {
	.name		= "HelloWorld196",

	.deserialize	= HelloWorld196_deserialize,
	.serialize	= HelloWorld196_serialize,

	.type_size	= HelloWorld196_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld197_typeplugin = {
	.name		= "HelloWorld197",

	.deserialize	= HelloWorld197_deserialize,
	.serialize	= HelloWorld197_serialize,

	.type_size	= HelloWorld197_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld198_typeplugin = {
	.name		= "HelloWorld198",

	.deserialize	= HelloWorld198_deserialize,
	.serialize	= HelloWorld198_serialize,

	.type_size	= HelloWorld198_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld199_typeplugin = {
	.name		= "HelloWorld199",

	.deserialize	= HelloWorld199_deserialize,
	.serialize	= HelloWorld199_serialize,

	.type_size	= HelloWorld199_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld200_typeplugin = {
	.name		= "HelloWorld200",

	.deserialize	= HelloWorld200_deserialize,
	.serialize	= HelloWorld200_serialize,

	.type_size	= HelloWorld200_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld201_typeplugin = {
	.name		= "HelloWorld201",

	.deserialize	= HelloWorld201_deserialize,
	.serialize	= HelloWorld201_serialize,

	.type_size	= HelloWorld201_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld202_typeplugin = {
	.name		= "HelloWorld202",

	.deserialize	= HelloWorld202_deserialize,
	.serialize	= HelloWorld202_serialize,

	.type_size	= HelloWorld202_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld203_typeplugin = {
	.name		= "HelloWorld203",

	.deserialize	= HelloWorld203_deserialize,
	.serialize	= HelloWorld203_serialize,

	.type_size	= HelloWorld203_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld204_typeplugin = {
	.name		= "HelloWorld204",

	.deserialize	= HelloWorld204_deserialize,
	.serialize	= HelloWorld204_serialize,

	.type_size	= HelloWorld204_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld205_typeplugin = {
	.name		= "HelloWorld205",

	.deserialize	= HelloWorld205_deserialize,
	.serialize	= HelloWorld205_serialize,

	.type_size	= HelloWorld205_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld206_typeplugin = {
	.name		= "HelloWorld206",

	.deserialize	= HelloWorld206_deserialize,
	.serialize	= HelloWorld206_serialize,

	.type_size	= HelloWorld206_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld207_typeplugin = {
	.name		= "HelloWorld207",

	.deserialize	= HelloWorld207_deserialize,
	.serialize	= HelloWorld207_serialize,

	.type_size	= HelloWorld207_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld208_typeplugin = {
	.name		= "HelloWorld208",

	.deserialize	= HelloWorld208_deserialize,
	.serialize	= HelloWorld208_serialize,

	.type_size	= HelloWorld208_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld209_typeplugin = {
	.name		= "HelloWorld209",

	.deserialize	= HelloWorld209_deserialize,
	.serialize	= HelloWorld209_serialize,

	.type_size	= HelloWorld209_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld210_typeplugin = {
	.name		= "HelloWorld210",

	.deserialize	= HelloWorld210_deserialize,
	.serialize	= HelloWorld210_serialize,

	.type_size	= HelloWorld210_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld211_typeplugin = {
	.name		= "HelloWorld211",

	.deserialize	= HelloWorld211_deserialize,
	.serialize	= HelloWorld211_serialize,

	.type_size	= HelloWorld211_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld212_typeplugin = {
	.name		= "HelloWorld212",

	.deserialize	= HelloWorld212_deserialize,
	.serialize	= HelloWorld212_serialize,

	.type_size	= HelloWorld212_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld213_typeplugin = {
	.name		= "HelloWorld213",

	.deserialize	= HelloWorld213_deserialize,
	.serialize	= HelloWorld213_serialize,

	.type_size	= HelloWorld213_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld214_typeplugin = {
	.name		= "HelloWorld214",

	.deserialize	= HelloWorld214_deserialize,
	.serialize	= HelloWorld214_serialize,

	.type_size	= HelloWorld214_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld215_typeplugin = {
	.name		= "HelloWorld215",

	.deserialize	= HelloWorld215_deserialize,
	.serialize	= HelloWorld215_serialize,

	.type_size	= HelloWorld215_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld216_typeplugin = {
	.name		= "HelloWorld216",

	.deserialize	= HelloWorld216_deserialize,
	.serialize	= HelloWorld216_serialize,

	.type_size	= HelloWorld216_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld217_typeplugin = {
	.name		= "HelloWorld217",

	.deserialize	= HelloWorld217_deserialize,
	.serialize	= HelloWorld217_serialize,

	.type_size	= HelloWorld217_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld218_typeplugin = {
	.name		= "HelloWorld218",

	.deserialize	= HelloWorld218_deserialize,
	.serialize	= HelloWorld218_serialize,

	.type_size	= HelloWorld218_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld219_typeplugin = {
	.name		= "HelloWorld219",

	.deserialize	= HelloWorld219_deserialize,
	.serialize	= HelloWorld219_serialize,

	.type_size	= HelloWorld219_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld220_typeplugin = {
	.name		= "HelloWorld220",

	.deserialize	= HelloWorld220_deserialize,
	.serialize	= HelloWorld220_serialize,

	.type_size	= HelloWorld220_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld221_typeplugin = {
	.name		= "HelloWorld221",

	.deserialize	= HelloWorld221_deserialize,
	.serialize	= HelloWorld221_serialize,

	.type_size	= HelloWorld221_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld222_typeplugin = {
	.name		= "HelloWorld222",

	.deserialize	= HelloWorld222_deserialize,
	.serialize	= HelloWorld222_serialize,

	.type_size	= HelloWorld222_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld223_typeplugin = {
	.name		= "HelloWorld223",

	.deserialize	= HelloWorld223_deserialize,
	.serialize	= HelloWorld223_serialize,

	.type_size	= HelloWorld223_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld224_typeplugin = {
	.name		= "HelloWorld224",

	.deserialize	= HelloWorld224_deserialize,
	.serialize	= HelloWorld224_serialize,

	.type_size	= HelloWorld224_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld225_typeplugin = {
	.name		= "HelloWorld225",

	.deserialize	= HelloWorld225_deserialize,
	.serialize	= HelloWorld225_serialize,

	.type_size	= HelloWorld225_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld226_typeplugin = {
	.name		= "HelloWorld226",

	.deserialize	= HelloWorld226_deserialize,
	.serialize	= HelloWorld226_serialize,

	.type_size	= HelloWorld226_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld227_typeplugin = {
	.name		= "HelloWorld227",

	.deserialize	= HelloWorld227_deserialize,
	.serialize	= HelloWorld227_serialize,

	.type_size	= HelloWorld227_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld228_typeplugin = {
	.name		= "HelloWorld228",

	.deserialize	= HelloWorld228_deserialize,
	.serialize	= HelloWorld228_serialize,

	.type_size	= HelloWorld228_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld229_typeplugin = {
	.name		= "HelloWorld229",

	.deserialize	= HelloWorld229_deserialize,
	.serialize	= HelloWorld229_serialize,

	.type_size	= HelloWorld229_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld230_typeplugin = {
	.name		= "HelloWorld230",

	.deserialize	= HelloWorld230_deserialize,
	.serialize	= HelloWorld230_serialize,

	.type_size	= HelloWorld230_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld231_typeplugin = {
	.name		= "HelloWorld231",

	.deserialize	= HelloWorld231_deserialize,
	.serialize	= HelloWorld231_serialize,

	.type_size	= HelloWorld231_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld232_typeplugin = {
	.name		= "HelloWorld232",

	.deserialize	= HelloWorld232_deserialize,
	.serialize	= HelloWorld232_serialize,

	.type_size	= HelloWorld232_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld233_typeplugin = {
	.name		= "HelloWorld233",

	.deserialize	= HelloWorld233_deserialize,
	.serialize	= HelloWorld233_serialize,

	.type_size	= HelloWorld233_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld234_typeplugin = {
	.name		= "HelloWorld234",

	.deserialize	= HelloWorld234_deserialize,
	.serialize	= HelloWorld234_serialize,

	.type_size	= HelloWorld234_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld235_typeplugin = {
	.name		= "HelloWorld235",

	.deserialize	= HelloWorld235_deserialize,
	.serialize	= HelloWorld235_serialize,

	.type_size	= HelloWorld235_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld236_typeplugin = {
	.name		= "HelloWorld236",

	.deserialize	= HelloWorld236_deserialize,
	.serialize	= HelloWorld236_serialize,

	.type_size	= HelloWorld236_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld237_typeplugin = {
	.name		= "HelloWorld237",

	.deserialize	= HelloWorld237_deserialize,
	.serialize	= HelloWorld237_serialize,

	.type_size	= HelloWorld237_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld238_typeplugin = {
	.name		= "HelloWorld238",

	.deserialize	= HelloWorld238_deserialize,
	.serialize	= HelloWorld238_serialize,

	.type_size	= HelloWorld238_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld239_typeplugin = {
	.name		= "HelloWorld239",

	.deserialize	= HelloWorld239_deserialize,
	.serialize	= HelloWorld239_serialize,

	.type_size	= HelloWorld239_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld240_typeplugin = {
	.name		= "HelloWorld240",

	.deserialize	= HelloWorld240_deserialize,
	.serialize	= HelloWorld240_serialize,

	.type_size	= HelloWorld240_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld241_typeplugin = {
	.name		= "HelloWorld241",

	.deserialize	= HelloWorld241_deserialize,
	.serialize	= HelloWorld241_serialize,

	.type_size	= HelloWorld241_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld242_typeplugin = {
	.name		= "HelloWorld242",

	.deserialize	= HelloWorld242_deserialize,
	.serialize	= HelloWorld242_serialize,

	.type_size	= HelloWorld242_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld243_typeplugin = {
	.name		= "HelloWorld243",

	.deserialize	= HelloWorld243_deserialize,
	.serialize	= HelloWorld243_serialize,

	.type_size	= HelloWorld243_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld244_typeplugin = {
	.name		= "HelloWorld244",

	.deserialize	= HelloWorld244_deserialize,
	.serialize	= HelloWorld244_serialize,

	.type_size	= HelloWorld244_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld245_typeplugin = {
	.name		= "HelloWorld245",

	.deserialize	= HelloWorld245_deserialize,
	.serialize	= HelloWorld245_serialize,

	.type_size	= HelloWorld245_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld246_typeplugin = {
	.name		= "HelloWorld246",

	.deserialize	= HelloWorld246_deserialize,
	.serialize	= HelloWorld246_serialize,

	.type_size	= HelloWorld246_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld247_typeplugin = {
	.name		= "HelloWorld247",

	.deserialize	= HelloWorld247_deserialize,
	.serialize	= HelloWorld247_serialize,

	.type_size	= HelloWorld247_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld248_typeplugin = {
	.name		= "HelloWorld248",

	.deserialize	= HelloWorld248_deserialize,
	.serialize	= HelloWorld248_serialize,

	.type_size	= HelloWorld248_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld249_typeplugin = {
	.name		= "HelloWorld249",

	.deserialize	= HelloWorld249_deserialize,
	.serialize	= HelloWorld249_serialize,

	.type_size	= HelloWorld249_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld250_typeplugin = {
	.name		= "HelloWorld250",

	.deserialize	= HelloWorld250_deserialize,
	.serialize	= HelloWorld250_serialize,

	.type_size	= HelloWorld250_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld251_typeplugin = {
	.name		= "HelloWorld251",

	.deserialize	= HelloWorld251_deserialize,
	.serialize	= HelloWorld251_serialize,

	.type_size	= HelloWorld251_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld252_typeplugin = {
	.name		= "HelloWorld252",

	.deserialize	= HelloWorld252_deserialize,
	.serialize	= HelloWorld252_serialize,

	.type_size	= HelloWorld252_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld253_typeplugin = {
	.name		= "HelloWorld253",

	.deserialize	= HelloWorld253_deserialize,
	.serialize	= HelloWorld253_serialize,

	.type_size	= HelloWorld253_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld254_typeplugin = {
	.name		= "HelloWorld254",

	.deserialize	= HelloWorld254_deserialize,
	.serialize	= HelloWorld254_serialize,

	.type_size	= HelloWorld254_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld255_typeplugin = {
	.name		= "HelloWorld255",

	.deserialize	= HelloWorld255_deserialize,
	.serialize	= HelloWorld255_serialize,

	.type_size	= HelloWorld255_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld256_typeplugin = {
	.name		= "HelloWorld256",

	.deserialize	= HelloWorld256_deserialize,
	.serialize	= HelloWorld256_serialize,

	.type_size	= HelloWorld256_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld257_typeplugin = {
	.name		= "HelloWorld257",

	.deserialize	= HelloWorld257_deserialize,
	.serialize	= HelloWorld257_serialize,

	.type_size	= HelloWorld257_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld258_typeplugin = {
	.name		= "HelloWorld258",

	.deserialize	= HelloWorld258_deserialize,
	.serialize	= HelloWorld258_serialize,

	.type_size	= HelloWorld258_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld259_typeplugin = {
	.name		= "HelloWorld259",

	.deserialize	= HelloWorld259_deserialize,
	.serialize	= HelloWorld259_serialize,

	.type_size	= HelloWorld259_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld260_typeplugin = {
	.name		= "HelloWorld260",

	.deserialize	= HelloWorld260_deserialize,
	.serialize	= HelloWorld260_serialize,

	.type_size	= HelloWorld260_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld261_typeplugin = {
	.name		= "HelloWorld261",

	.deserialize	= HelloWorld261_deserialize,
	.serialize	= HelloWorld261_serialize,

	.type_size	= HelloWorld261_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld262_typeplugin = {
	.name		= "HelloWorld262",

	.deserialize	= HelloWorld262_deserialize,
	.serialize	= HelloWorld262_serialize,

	.type_size	= HelloWorld262_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld263_typeplugin = {
	.name		= "HelloWorld263",

	.deserialize	= HelloWorld263_deserialize,
	.serialize	= HelloWorld263_serialize,

	.type_size	= HelloWorld263_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld264_typeplugin = {
	.name		= "HelloWorld264",

	.deserialize	= HelloWorld264_deserialize,
	.serialize	= HelloWorld264_serialize,

	.type_size	= HelloWorld264_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld265_typeplugin = {
	.name		= "HelloWorld265",

	.deserialize	= HelloWorld265_deserialize,
	.serialize	= HelloWorld265_serialize,

	.type_size	= HelloWorld265_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld266_typeplugin = {
	.name		= "HelloWorld266",

	.deserialize	= HelloWorld266_deserialize,
	.serialize	= HelloWorld266_serialize,

	.type_size	= HelloWorld266_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld267_typeplugin = {
	.name		= "HelloWorld267",

	.deserialize	= HelloWorld267_deserialize,
	.serialize	= HelloWorld267_serialize,

	.type_size	= HelloWorld267_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld268_typeplugin = {
	.name		= "HelloWorld268",

	.deserialize	= HelloWorld268_deserialize,
	.serialize	= HelloWorld268_serialize,

	.type_size	= HelloWorld268_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld269_typeplugin = {
	.name		= "HelloWorld269",

	.deserialize	= HelloWorld269_deserialize,
	.serialize	= HelloWorld269_serialize,

	.type_size	= HelloWorld269_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld270_typeplugin = {
	.name		= "HelloWorld270",

	.deserialize	= HelloWorld270_deserialize,
	.serialize	= HelloWorld270_serialize,

	.type_size	= HelloWorld270_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld271_typeplugin = {
	.name		= "HelloWorld271",

	.deserialize	= HelloWorld271_deserialize,
	.serialize	= HelloWorld271_serialize,

	.type_size	= HelloWorld271_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld272_typeplugin = {
	.name		= "HelloWorld272",

	.deserialize	= HelloWorld272_deserialize,
	.serialize	= HelloWorld272_serialize,

	.type_size	= HelloWorld272_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld273_typeplugin = {
	.name		= "HelloWorld273",

	.deserialize	= HelloWorld273_deserialize,
	.serialize	= HelloWorld273_serialize,

	.type_size	= HelloWorld273_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld274_typeplugin = {
	.name		= "HelloWorld274",

	.deserialize	= HelloWorld274_deserialize,
	.serialize	= HelloWorld274_serialize,

	.type_size	= HelloWorld274_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld275_typeplugin = {
	.name		= "HelloWorld275",

	.deserialize	= HelloWorld275_deserialize,
	.serialize	= HelloWorld275_serialize,

	.type_size	= HelloWorld275_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld276_typeplugin = {
	.name		= "HelloWorld276",

	.deserialize	= HelloWorld276_deserialize,
	.serialize	= HelloWorld276_serialize,

	.type_size	= HelloWorld276_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld277_typeplugin = {
	.name		= "HelloWorld277",

	.deserialize	= HelloWorld277_deserialize,
	.serialize	= HelloWorld277_serialize,

	.type_size	= HelloWorld277_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld278_typeplugin = {
	.name		= "HelloWorld278",

	.deserialize	= HelloWorld278_deserialize,
	.serialize	= HelloWorld278_serialize,

	.type_size	= HelloWorld278_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld279_typeplugin = {
	.name		= "HelloWorld279",

	.deserialize	= HelloWorld279_deserialize,
	.serialize	= HelloWorld279_serialize,

	.type_size	= HelloWorld279_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld280_typeplugin = {
	.name		= "HelloWorld280",

	.deserialize	= HelloWorld280_deserialize,
	.serialize	= HelloWorld280_serialize,

	.type_size	= HelloWorld280_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld281_typeplugin = {
	.name		= "HelloWorld281",

	.deserialize	= HelloWorld281_deserialize,
	.serialize	= HelloWorld281_serialize,

	.type_size	= HelloWorld281_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld282_typeplugin = {
	.name		= "HelloWorld282",

	.deserialize	= HelloWorld282_deserialize,
	.serialize	= HelloWorld282_serialize,

	.type_size	= HelloWorld282_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld283_typeplugin = {
	.name		= "HelloWorld283",

	.deserialize	= HelloWorld283_deserialize,
	.serialize	= HelloWorld283_serialize,

	.type_size	= HelloWorld283_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld284_typeplugin = {
	.name		= "HelloWorld284",

	.deserialize	= HelloWorld284_deserialize,
	.serialize	= HelloWorld284_serialize,

	.type_size	= HelloWorld284_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld285_typeplugin = {
	.name		= "HelloWorld285",

	.deserialize	= HelloWorld285_deserialize,
	.serialize	= HelloWorld285_serialize,

	.type_size	= HelloWorld285_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld286_typeplugin = {
	.name		= "HelloWorld286",

	.deserialize	= HelloWorld286_deserialize,
	.serialize	= HelloWorld286_serialize,

	.type_size	= HelloWorld286_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld287_typeplugin = {
	.name		= "HelloWorld287",

	.deserialize	= HelloWorld287_deserialize,
	.serialize	= HelloWorld287_serialize,

	.type_size	= HelloWorld287_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld288_typeplugin = {
	.name		= "HelloWorld288",

	.deserialize	= HelloWorld288_deserialize,
	.serialize	= HelloWorld288_serialize,

	.type_size	= HelloWorld288_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld289_typeplugin = {
	.name		= "HelloWorld289",

	.deserialize	= HelloWorld289_deserialize,
	.serialize	= HelloWorld289_serialize,

	.type_size	= HelloWorld289_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld290_typeplugin = {
	.name		= "HelloWorld290",

	.deserialize	= HelloWorld290_deserialize,
	.serialize	= HelloWorld290_serialize,

	.type_size	= HelloWorld290_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld291_typeplugin = {
	.name		= "HelloWorld291",

	.deserialize	= HelloWorld291_deserialize,
	.serialize	= HelloWorld291_serialize,

	.type_size	= HelloWorld291_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld292_typeplugin = {
	.name		= "HelloWorld292",

	.deserialize	= HelloWorld292_deserialize,
	.serialize	= HelloWorld292_serialize,

	.type_size	= HelloWorld292_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld293_typeplugin = {
	.name		= "HelloWorld293",

	.deserialize	= HelloWorld293_deserialize,
	.serialize	= HelloWorld293_serialize,

	.type_size	= HelloWorld293_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld294_typeplugin = {
	.name		= "HelloWorld294",

	.deserialize	= HelloWorld294_deserialize,
	.serialize	= HelloWorld294_serialize,

	.type_size	= HelloWorld294_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld295_typeplugin = {
	.name		= "HelloWorld295",

	.deserialize	= HelloWorld295_deserialize,
	.serialize	= HelloWorld295_serialize,

	.type_size	= HelloWorld295_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld296_typeplugin = {
	.name		= "HelloWorld296",

	.deserialize	= HelloWorld296_deserialize,
	.serialize	= HelloWorld296_serialize,

	.type_size	= HelloWorld296_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld297_typeplugin = {
	.name		= "HelloWorld297",

	.deserialize	= HelloWorld297_deserialize,
	.serialize	= HelloWorld297_serialize,

	.type_size	= HelloWorld297_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld298_typeplugin = {
	.name		= "HelloWorld298",

	.deserialize	= HelloWorld298_deserialize,
	.serialize	= HelloWorld298_serialize,

	.type_size	= HelloWorld298_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  HelloWorld299_typeplugin = {
	.name		= "HelloWorld299",

	.deserialize	= HelloWorld299_deserialize,
	.serialize	= HelloWorld299_serialize,

	.type_size	= HelloWorld299_get_type_size,
	.crc16		= "39E5"
};


const struct type_plugin  AgentHelloWorld_typeplugin = {
	.name		= "AgentHelloWorld",

	.deserialize	= AgentHelloWorld_deserialize,
	.serialize	= AgentHelloWorld_serialize,

	.type_size	= AgentHelloWorld_get_type_size,
	.crc16		= "F8E8"
};



#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>