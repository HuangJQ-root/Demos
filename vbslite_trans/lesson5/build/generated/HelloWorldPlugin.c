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
 * This file was generated form HelloWorld.idl by the mvbs-idl-gen tool.
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

#include "HelloWorldPlugin.h"



/* --------------------------------------------------------------------------
 *  All of New Function definitions: MVBS_HelloWorld
 * --------------------------------------------------------------------------
 */

uint32_t MVBS_HelloWorld_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u + 64 + 1u;

	return size - previousSize;
}

void MVBS_HelloWorld_init(MVBS_HelloWorld *sample)
{
	if (sample != NULL) {
		sample->id = 0;
		mvbs_memzero(sample->msg, 64 + 1);
	}
}

bool MVBS_HelloWorld_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld *topic)
{
	if (!mcdr_serialize_int32_t(cdr, topic->id)) {
		pr_debug("id serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_string(cdr, topic->msg)) {
		pr_debug("msg serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool MVBS_HelloWorld_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld *topic)
{
	if (!mcdr_deserialize_int32_t(cdr, &topic->id)) {
		pr_debug("id deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_string(cdr, topic->msg, 64 + 1)) {
		pr_debug("msg deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t MVBS_HelloWorld_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(MVBS_HelloWorld_topic_max_size(0) + 4u);

	if (size != MVBS_HELLOWORLD_SIZE)
	{
		pr_warn("size:%d, MVBS_HELLOWORLD_SIZE:%d\n", size, MVBS_HELLOWORLD_SIZE);
		pr_warn("size is not equal to MVBS_HELLOWORLD_SIZE\n");

		return size;
	}

	return MVBS_HELLOWORLD_SIZE;
}

static bool MVBS_HelloWorld_serialize(void *data, struct serialized_payload *payload)
{
	MVBS_HelloWorld  *topic = (MVBS_HelloWorld  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!MVBS_HelloWorld_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool MVBS_HelloWorld_deserialize(void *data, struct serialized_payload *payload)
{
	MVBS_HelloWorld *topic = (MVBS_HelloWorld *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!MVBS_HelloWorld_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}MVBS_HelloWorld *MVBS_HelloWorld_create(void)
{
	MVBS_HelloWorld *sample;
	uint32_t size = sizeof(struct MVBS_HelloWorld);

	sample = (MVBS_HelloWorld *)mvbs_calloc(1, size);
	return sample;
}

void MVBS_HelloWorld_delete(MVBS_HelloWorld *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: MVBS_HelloWorld1
 * --------------------------------------------------------------------------
 */

uint32_t MVBS_HelloWorld1_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 2) + 2u;
	size += mcdr_get_alignment(size, 2) + 2u;

	return size - previousSize;
}

void MVBS_HelloWorld1_init(MVBS_HelloWorld1 *sample)
{
	if (sample != NULL) {
		sample->short_data = 0;
		sample->ushort_data = 0;
	}
}

bool MVBS_HelloWorld1_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld1 *topic)
{
	if (!mcdr_serialize_int16_t(cdr, topic->short_data)) {
		pr_debug("short_data serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_uint16_t(cdr, topic->ushort_data)) {
		pr_debug("ushort_data serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool MVBS_HelloWorld1_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld1 *topic)
{
	if (!mcdr_deserialize_int16_t(cdr, &topic->short_data)) {
		pr_debug("short_data deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_uint16_t(cdr, &topic->ushort_data)) {
		pr_debug("ushort_data deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t MVBS_HelloWorld1_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(MVBS_HelloWorld1_topic_max_size(0) + 4u);

	if (size != MVBS_HELLOWORLD1_SIZE)
	{
		pr_warn("size:%d, MVBS_HELLOWORLD1_SIZE:%d\n", size, MVBS_HELLOWORLD1_SIZE);
		pr_warn("size is not equal to MVBS_HELLOWORLD1_SIZE\n");

		return size;
	}

	return MVBS_HELLOWORLD1_SIZE;
}

static bool MVBS_HelloWorld1_serialize(void *data, struct serialized_payload *payload)
{
	MVBS_HelloWorld1  *topic = (MVBS_HelloWorld1  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!MVBS_HelloWorld1_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool MVBS_HelloWorld1_deserialize(void *data, struct serialized_payload *payload)
{
	MVBS_HelloWorld1 *topic = (MVBS_HelloWorld1 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!MVBS_HelloWorld1_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}MVBS_HelloWorld1 *MVBS_HelloWorld1_create(void)
{
	MVBS_HelloWorld1 *sample;
	uint32_t size = sizeof(struct MVBS_HelloWorld1);

	sample = (MVBS_HelloWorld1 *)mvbs_calloc(1, size);
	return sample;
}

void MVBS_HelloWorld1_delete(MVBS_HelloWorld1 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: MVBS_HelloWorld2
 * --------------------------------------------------------------------------
 */

uint32_t MVBS_HelloWorld2_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 8) + 8u;

	return size - previousSize;
}

void MVBS_HelloWorld2_init(MVBS_HelloWorld2 *sample)
{
	if (sample != NULL) {
		sample->float_data = (float)0.0f;
		sample->double_data = 0.0;
	}
}

bool MVBS_HelloWorld2_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld2 *topic)
{
	if (!mcdr_serialize_float(cdr, topic->float_data)) {
		pr_debug("float_data serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_double(cdr, topic->double_data)) {
		pr_debug("double_data serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool MVBS_HelloWorld2_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld2 *topic)
{
	if (!mcdr_deserialize_float(cdr, &topic->float_data)) {
		pr_debug("float_data deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_double(cdr, &topic->double_data)) {
		pr_debug("double_data deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t MVBS_HelloWorld2_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(MVBS_HelloWorld2_topic_max_size(0) + 4u);

	if (size != MVBS_HELLOWORLD2_SIZE)
	{
		pr_warn("size:%d, MVBS_HELLOWORLD2_SIZE:%d\n", size, MVBS_HELLOWORLD2_SIZE);
		pr_warn("size is not equal to MVBS_HELLOWORLD2_SIZE\n");

		return size;
	}

	return MVBS_HELLOWORLD2_SIZE;
}

static bool MVBS_HelloWorld2_serialize(void *data, struct serialized_payload *payload)
{
	MVBS_HelloWorld2  *topic = (MVBS_HelloWorld2  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!MVBS_HelloWorld2_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool MVBS_HelloWorld2_deserialize(void *data, struct serialized_payload *payload)
{
	MVBS_HelloWorld2 *topic = (MVBS_HelloWorld2 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!MVBS_HelloWorld2_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}MVBS_HelloWorld2 *MVBS_HelloWorld2_create(void)
{
	MVBS_HelloWorld2 *sample;
	uint32_t size = sizeof(struct MVBS_HelloWorld2);

	sample = (MVBS_HelloWorld2 *)mvbs_calloc(1, size);
	return sample;
}

void MVBS_HelloWorld2_delete(MVBS_HelloWorld2 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: MVBS_HelloWorld3
 * --------------------------------------------------------------------------
 */

uint32_t MVBS_HelloWorld3_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += MVBS_HelloWorld_topic_max_size(size);
	size += mcdr_get_alignment(size, 8) + 8u;

	return size - previousSize;
}

void MVBS_HelloWorld3_init(MVBS_HelloWorld3 *sample)
{
	if (sample != NULL) {
		MVBS_HelloWorld_init(&sample->struct_data);
		sample->double_data = 0.0;
	}
}

bool MVBS_HelloWorld3_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld3 *topic)
{
	if (!MVBS_HelloWorld_serialize_topic(cdr, &topic->struct_data)) {
		pr_debug("struct_data serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_double(cdr, topic->double_data)) {
		pr_debug("double_data serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool MVBS_HelloWorld3_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld3 *topic)
{ 
	if (!MVBS_HelloWorld_deserialize_topic(cdr, &topic->struct_data)) {
		pr_debug("struct_data deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_double(cdr, &topic->double_data)) {
		pr_debug("double_data deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t MVBS_HelloWorld3_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(MVBS_HelloWorld3_topic_max_size(0) + 4u);

	if (size != MVBS_HELLOWORLD3_SIZE)
	{
		pr_warn("size:%d, MVBS_HELLOWORLD3_SIZE:%d\n", size, MVBS_HELLOWORLD3_SIZE);
		pr_warn("size is not equal to MVBS_HELLOWORLD3_SIZE\n");

		return size;
	}

	return MVBS_HELLOWORLD3_SIZE;
}

static bool MVBS_HelloWorld3_serialize(void *data, struct serialized_payload *payload)
{
	MVBS_HelloWorld3  *topic = (MVBS_HelloWorld3  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!MVBS_HelloWorld3_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool MVBS_HelloWorld3_deserialize(void *data, struct serialized_payload *payload)
{
	MVBS_HelloWorld3 *topic = (MVBS_HelloWorld3 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!MVBS_HelloWorld3_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}MVBS_HelloWorld3 *MVBS_HelloWorld3_create(void)
{
	MVBS_HelloWorld3 *sample;
	uint32_t size = sizeof(struct MVBS_HelloWorld3);

	sample = (MVBS_HelloWorld3 *)mvbs_calloc(1, size);
	return sample;
}

void MVBS_HelloWorld3_delete(MVBS_HelloWorld3 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: MVBS_HelloWorld4
 * --------------------------------------------------------------------------
 */

uint32_t MVBS_HelloWorld4_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += MVBS_HelloWorld_topic_max_size(size);
	size += mcdr_get_alignment(size, 8) + 8u;
	size += mcdr_get_alignment(size, 8) + 8u;

	return size - previousSize;
}

void MVBS_HelloWorld4_init(MVBS_HelloWorld4 *sample)
{
	if (sample != NULL) {
		MVBS_HelloWorld_init(&sample->struct_data);
		sample->double1_data = 0.0;
		sample->double2_data = 0.0;
	}
}

bool MVBS_HelloWorld4_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld4 *topic)
{
	if (!MVBS_HelloWorld_serialize_topic(cdr, &topic->struct_data)) {
		pr_debug("struct_data serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_double(cdr, topic->double1_data)) {
		pr_debug("double1_data serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_double(cdr, topic->double2_data)) {
		pr_debug("double2_data serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool MVBS_HelloWorld4_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld4 *topic)
{ 
	if (!MVBS_HelloWorld_deserialize_topic(cdr, &topic->struct_data)) {
		pr_debug("struct_data deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_double(cdr, &topic->double1_data)) {
		pr_debug("double1_data deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_double(cdr, &topic->double2_data)) {
		pr_debug("double2_data deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t MVBS_HelloWorld4_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(MVBS_HelloWorld4_topic_max_size(0) + 4u);

	if (size != MVBS_HELLOWORLD4_SIZE)
	{
		pr_warn("size:%d, MVBS_HELLOWORLD4_SIZE:%d\n", size, MVBS_HELLOWORLD4_SIZE);
		pr_warn("size is not equal to MVBS_HELLOWORLD4_SIZE\n");

		return size;
	}

	return MVBS_HELLOWORLD4_SIZE;
}

static bool MVBS_HelloWorld4_serialize(void *data, struct serialized_payload *payload)
{
	MVBS_HelloWorld4  *topic = (MVBS_HelloWorld4  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!MVBS_HelloWorld4_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool MVBS_HelloWorld4_deserialize(void *data, struct serialized_payload *payload)
{
	MVBS_HelloWorld4 *topic = (MVBS_HelloWorld4 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!MVBS_HelloWorld4_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}MVBS_HelloWorld4 *MVBS_HelloWorld4_create(void)
{
	MVBS_HelloWorld4 *sample;
	uint32_t size = sizeof(struct MVBS_HelloWorld4);

	sample = (MVBS_HelloWorld4 *)mvbs_calloc(1, size);
	return sample;
}

void MVBS_HelloWorld4_delete(MVBS_HelloWorld4 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: MVBS_HelloWorld5
 * --------------------------------------------------------------------------
 */

uint32_t MVBS_HelloWorld5_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += MVBS_HelloWorld_topic_max_size(size);
	size += MVBS_HelloWorld_topic_max_size(size);
	size += mcdr_get_alignment(size, 8) + 8u;

	return size - previousSize;
}

void MVBS_HelloWorld5_init(MVBS_HelloWorld5 *sample)
{
	if (sample != NULL) {
		MVBS_HelloWorld_init(&sample->struct1_data);
		MVBS_HelloWorld_init(&sample->struct2_data);
		sample->double_data = 0.0;
	}
}

bool MVBS_HelloWorld5_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld5 *topic)
{
	if (!MVBS_HelloWorld_serialize_topic(cdr, &topic->struct1_data)) {
		pr_debug("struct1_data serialize failed!\n");
		return false;
	}

	if (!MVBS_HelloWorld_serialize_topic(cdr, &topic->struct2_data)) {
		pr_debug("struct2_data serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_double(cdr, topic->double_data)) {
		pr_debug("double_data serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool MVBS_HelloWorld5_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld5 *topic)
{ 
	if (!MVBS_HelloWorld_deserialize_topic(cdr, &topic->struct1_data)) {
		pr_debug("struct1_data deserialize failed!\n");
		return false;
	}
 
	if (!MVBS_HelloWorld_deserialize_topic(cdr, &topic->struct2_data)) {
		pr_debug("struct2_data deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_double(cdr, &topic->double_data)) {
		pr_debug("double_data deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t MVBS_HelloWorld5_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(MVBS_HelloWorld5_topic_max_size(0) + 4u);

	if (size != MVBS_HELLOWORLD5_SIZE)
	{
		pr_warn("size:%d, MVBS_HELLOWORLD5_SIZE:%d\n", size, MVBS_HELLOWORLD5_SIZE);
		pr_warn("size is not equal to MVBS_HELLOWORLD5_SIZE\n");

		return size;
	}

	return MVBS_HELLOWORLD5_SIZE;
}

static bool MVBS_HelloWorld5_serialize(void *data, struct serialized_payload *payload)
{
	MVBS_HelloWorld5  *topic = (MVBS_HelloWorld5  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!MVBS_HelloWorld5_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool MVBS_HelloWorld5_deserialize(void *data, struct serialized_payload *payload)
{
	MVBS_HelloWorld5 *topic = (MVBS_HelloWorld5 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!MVBS_HelloWorld5_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}MVBS_HelloWorld5 *MVBS_HelloWorld5_create(void)
{
	MVBS_HelloWorld5 *sample;
	uint32_t size = sizeof(struct MVBS_HelloWorld5);

	sample = (MVBS_HelloWorld5 *)mvbs_calloc(1, size);
	return sample;
}

void MVBS_HelloWorld5_delete(MVBS_HelloWorld5 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: MVBS_BasicTypeStruct
 * --------------------------------------------------------------------------
 */

uint32_t MVBS_BasicTypeStruct_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u + 64 + 1u;
	size += mcdr_get_alignment(size, 1) + 1u;
	size += mcdr_get_alignment(size, 1) + 1u;
	size += mcdr_get_alignment(size, 2) + 2u;
	size += mcdr_get_alignment(size, 2) + 2u;
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 8) + 8u;
	size += mcdr_get_alignment(size, 8) + 8u;
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 8) + 8u;
	size += mcdr_get_alignment(size, 1) + 1u;

	return size - previousSize;
}

void MVBS_BasicTypeStruct_init(MVBS_BasicTypeStruct *sample)
{
	if (sample != NULL) {
		sample->id = 0;
		mvbs_memzero(sample->msg, 64 + 1);
		sample->tag = 0;
		sample->u8_data = 0;
		sample->short_data = 0;
		sample->ushort_data = 0;
		sample->ulong_data = 0;
		sample->llong_data = 0LL;
		sample->ullong_data = 0ULL;
		sample->float_data = (float)0.0f;
		sample->double_data = 0.0;
		sample->bool_data = 0;
	}
}

bool MVBS_BasicTypeStruct_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_BasicTypeStruct *topic)
{
	if (!mcdr_serialize_int32_t(cdr, topic->id)) {
		pr_debug("id serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_string(cdr, topic->msg)) {
		pr_debug("msg serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_unsigned_char(cdr, topic->tag)) {
		pr_debug("tag serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_uint8_t(cdr, topic->u8_data)) {
		pr_debug("u8_data serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int16_t(cdr, topic->short_data)) {
		pr_debug("short_data serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_uint16_t(cdr, topic->ushort_data)) {
		pr_debug("ushort_data serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_uint32_t(cdr, topic->ulong_data)) {
		pr_debug("ulong_data serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int64_t(cdr, topic->llong_data)) {
		pr_debug("llong_data serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_uint64_t(cdr, topic->ullong_data)) {
		pr_debug("ullong_data serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_float(cdr, topic->float_data)) {
		pr_debug("float_data serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_double(cdr, topic->double_data)) {
		pr_debug("double_data serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_uint8_t(cdr, topic->bool_data)) {
		pr_debug("bool_data serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool MVBS_BasicTypeStruct_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_BasicTypeStruct *topic)
{
	if (!mcdr_deserialize_int32_t(cdr, &topic->id)) {
		pr_debug("id deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_string(cdr, topic->msg, 64 + 1)) {
		pr_debug("msg deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_unsigned_char(cdr, &topic->tag)) {
		pr_debug("tag deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_uint8_t(cdr, &topic->u8_data)) {
		pr_debug("u8_data deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int16_t(cdr, &topic->short_data)) {
		pr_debug("short_data deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_uint16_t(cdr, &topic->ushort_data)) {
		pr_debug("ushort_data deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_uint32_t(cdr, &topic->ulong_data)) {
		pr_debug("ulong_data deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int64_t(cdr, &topic->llong_data)) {
		pr_debug("llong_data deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_uint64_t(cdr, &topic->ullong_data)) {
		pr_debug("ullong_data deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_float(cdr, &topic->float_data)) {
		pr_debug("float_data deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_double(cdr, &topic->double_data)) {
		pr_debug("double_data deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_uint8_t(cdr, &topic->bool_data)) {
		pr_debug("bool_data deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t MVBS_BasicTypeStruct_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(MVBS_BasicTypeStruct_topic_max_size(0) + 4u);

	if (size != MVBS_BASICTYPESTRUCT_SIZE)
	{
		pr_warn("size:%d, MVBS_BASICTYPESTRUCT_SIZE:%d\n", size, MVBS_BASICTYPESTRUCT_SIZE);
		pr_warn("size is not equal to MVBS_BASICTYPESTRUCT_SIZE\n");

		return size;
	}

	return MVBS_BASICTYPESTRUCT_SIZE;
}

static bool MVBS_BasicTypeStruct_serialize(void *data, struct serialized_payload *payload)
{
	MVBS_BasicTypeStruct  *topic = (MVBS_BasicTypeStruct  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!MVBS_BasicTypeStruct_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool MVBS_BasicTypeStruct_deserialize(void *data, struct serialized_payload *payload)
{
	MVBS_BasicTypeStruct *topic = (MVBS_BasicTypeStruct *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!MVBS_BasicTypeStruct_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}MVBS_BasicTypeStruct *MVBS_BasicTypeStruct_create(void)
{
	MVBS_BasicTypeStruct *sample;
	uint32_t size = sizeof(struct MVBS_BasicTypeStruct);

	sample = (MVBS_BasicTypeStruct *)mvbs_calloc(1, size);
	return sample;
}

void MVBS_BasicTypeStruct_delete(MVBS_BasicTypeStruct *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: MVBS_sdatatype
 * --------------------------------------------------------------------------
 */

uint32_t MVBS_sdatatype_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void MVBS_sdatatype_init(MVBS_sdatatype *sample)
{
	if (sample != NULL) {
		sample->data1 = 0;
		sample->data2 = 0;
		sample->data3 = 0;
	}
}

bool MVBS_sdatatype_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_sdatatype *topic)
{
	if (!mcdr_serialize_int32_t(cdr, topic->data1)) {
		pr_debug("data1 serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->data2)) {
		pr_debug("data2 serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->data3)) {
		pr_debug("data3 serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool MVBS_sdatatype_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_sdatatype *topic)
{
	if (!mcdr_deserialize_int32_t(cdr, &topic->data1)) {
		pr_debug("data1 deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->data2)) {
		pr_debug("data2 deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->data3)) {
		pr_debug("data3 deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t MVBS_sdatatype_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(MVBS_sdatatype_topic_max_size(0) + 4u);

	if (size != MVBS_SDATATYPE_SIZE)
	{
		pr_warn("size:%d, MVBS_SDATATYPE_SIZE:%d\n", size, MVBS_SDATATYPE_SIZE);
		pr_warn("size is not equal to MVBS_SDATATYPE_SIZE\n");

		return size;
	}

	return MVBS_SDATATYPE_SIZE;
}

static bool MVBS_sdatatype_serialize(void *data, struct serialized_payload *payload)
{
	MVBS_sdatatype  *topic = (MVBS_sdatatype  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!MVBS_sdatatype_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool MVBS_sdatatype_deserialize(void *data, struct serialized_payload *payload)
{
	MVBS_sdatatype *topic = (MVBS_sdatatype *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!MVBS_sdatatype_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}MVBS_sdatatype *MVBS_sdatatype_create(void)
{
	MVBS_sdatatype *sample;
	uint32_t size = sizeof(struct MVBS_sdatatype);

	sample = (MVBS_sdatatype *)mvbs_calloc(1, size);
	return sample;
}

void MVBS_sdatatype_delete(MVBS_sdatatype *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: MVBS_edatatype
 * --------------------------------------------------------------------------
 */

uint32_t MVBS_edatatype_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	size += mcdr_get_alignment(size, 4) + 4u;

	return size - previousSize;
}

void MVBS_edatatype_init(MVBS_edatatype *sample)
{
	if (sample != NULL) {
		*sample = ZERO;
	}
}

bool MVBS_edatatype_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_edatatype *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, (uint32_t)(*topic))) {
		pr_debug("enum data serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool MVBS_edatatype_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_edatatype *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, (uint32_t *)topic)) {
		pr_debug("enum data deserialize failed!\n");
		return false;
	}
	return !mcdr_buffer_has_error(cdr);
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: MVBS_arrayType
 * --------------------------------------------------------------------------
 */

uint32_t MVBS_arrayType_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, sizeof(int32_t));
	size += 100 * sizeof(int32_t);

	return size - previousSize;
}

void MVBS_arrayType_init(MVBS_arrayType *sample)
{
	if (sample != NULL) {
		mvbs_memzero(sample, sizeof(int32_t) * 100);
	}
}

bool MVBS_arrayType_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_arrayType *topic)
{
	int32_t *data = (int32_t *)topic;

	if (!mcdr_serialize_array_int32_t(cdr, data, 100)) {
		pr_debug("MVBS_arrayType serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool MVBS_arrayType_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_arrayType *topic)
{
	int32_t *data = (int32_t *)topic;

	if (!mcdr_deserialize_array_int32_t(cdr, data, 100)) {
		pr_debug("MVBS_arrayType deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: MVBS_arrayType1
 * --------------------------------------------------------------------------
 */

uint32_t MVBS_arrayType1_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4);
	for (int i = 0; i < (int)(20); i++ ) {
		size += MVBS_sdatatype_topic_max_size(size);
	}

	return size - previousSize;
}

void MVBS_arrayType1_init(MVBS_arrayType1 *sample)
{
	if (sample != NULL) {
		mvbs_memzero(sample, sizeof(MVBS_sdatatype) * 20);
	}
}

bool MVBS_arrayType1_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_arrayType1 *topic)
{
	struct MVBS_sdatatype *data = (struct MVBS_sdatatype *)topic;

 	for (int i = 0; i < (int) (20); ++i)
	{
		if (!MVBS_sdatatype_serialize_topic(cdr, &data[i]))
		{
			pr_debug("MVBS_arrayType1 serialize failed!\n");
			return false;
		}
	}

	return !mcdr_buffer_has_error(cdr);
}

bool MVBS_arrayType1_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_arrayType1 *topic)
{
	uint32_t i;
	struct MVBS_sdatatype *data = (struct MVBS_sdatatype *)topic;

	for (i = 0; i < (int)(20); ++i)
	{
		if (!MVBS_sdatatype_deserialize_topic(cdr, &data[i]))
		{
			pr_debug("MVBS_arrayType1 deserialize failed!\n");
			return false;
		}
	}

	return !mcdr_buffer_has_error(cdr);
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: MVBS_ComplexDataType
 * --------------------------------------------------------------------------
 */

uint32_t MVBS_ComplexDataType_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += MVBS_sdatatype_topic_max_size(size);
	size += MVBS_edatatype_topic_max_size(size);
	size += MVBS_arrayType_topic_max_size(size);
	size += MVBS_arrayType1_topic_max_size(size);

	return size - previousSize;
}

void MVBS_ComplexDataType_init(MVBS_ComplexDataType *sample)
{
	if (sample != NULL) {
		MVBS_sdatatype_init(&sample->struct_data);
		MVBS_edatatype_init(&sample->enum_data);
		MVBS_arrayType_init(&sample->array_data);
		MVBS_arrayType1_init(&sample->arrayType1_data);
	}
}

bool MVBS_ComplexDataType_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_ComplexDataType *topic)
{
	if (!MVBS_sdatatype_serialize_topic(cdr, &topic->struct_data)) {
		pr_debug("struct_data serialize failed!\n");
		return false;
	}

	if (!MVBS_edatatype_serialize_topic(cdr, &topic->enum_data)) {
		pr_debug("enum_data serialize failed!\n");
		return false;
	}

	if (!MVBS_arrayType_serialize_topic(cdr, &topic->array_data)) {
		pr_debug("array_data serialize failed!\n");
		return false;
	}

	if (!MVBS_arrayType1_serialize_topic(cdr, &topic->arrayType1_data)) {
		pr_debug("arrayType1_data serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool MVBS_ComplexDataType_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_ComplexDataType *topic)
{ 
	if (!MVBS_sdatatype_deserialize_topic(cdr, &topic->struct_data)) {
		pr_debug("struct_data deserialize failed!\n");
		return false;
	}
 
	if (!MVBS_edatatype_deserialize_topic(cdr, &topic->enum_data)) {
		pr_debug("enum_data deserialize failed!\n");
		return false;
	}
 
	if (!MVBS_arrayType_deserialize_topic(cdr, &topic->array_data)) {
		pr_debug("array_data deserialize failed!\n");
		return false;
	}
 
	if (!MVBS_arrayType1_deserialize_topic(cdr, &topic->arrayType1_data)) {
		pr_debug("arrayType1_data deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t MVBS_ComplexDataType_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(MVBS_ComplexDataType_topic_max_size(0) + 4u);

	if (size != MVBS_COMPLEXDATATYPE_SIZE)
	{
		pr_warn("size:%d, MVBS_COMPLEXDATATYPE_SIZE:%d\n", size, MVBS_COMPLEXDATATYPE_SIZE);
		pr_warn("size is not equal to MVBS_COMPLEXDATATYPE_SIZE\n");

		return size;
	}

	return MVBS_COMPLEXDATATYPE_SIZE;
}

static bool MVBS_ComplexDataType_serialize(void *data, struct serialized_payload *payload)
{
	MVBS_ComplexDataType  *topic = (MVBS_ComplexDataType  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!MVBS_ComplexDataType_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool MVBS_ComplexDataType_deserialize(void *data, struct serialized_payload *payload)
{
	MVBS_ComplexDataType *topic = (MVBS_ComplexDataType *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!MVBS_ComplexDataType_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}MVBS_ComplexDataType *MVBS_ComplexDataType_create(void)
{
	MVBS_ComplexDataType *sample;
	uint32_t size = sizeof(struct MVBS_ComplexDataType);

	sample = (MVBS_ComplexDataType *)mvbs_calloc(1, size);
	return sample;
}

void MVBS_ComplexDataType_delete(MVBS_ComplexDataType *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

/* --------------------------------------------------------------------------
 *  All of New Function definitions: StructSize50
 * --------------------------------------------------------------------------
 */

uint32_t StructSize50_topic_max_size(uint32_t size)
{
	uint32_t previousSize = size;

	
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 4) + 4u;
	size += mcdr_get_alignment(size, 2) + 2u;
	size += mcdr_get_alignment(size, 2) + 2u;
	size += mcdr_get_alignment(size, 2) + 2u;

	return size - previousSize;
}

void StructSize50_init(StructSize50 *sample)
{
	if (sample != NULL) {
		sample->id = 0;
		sample->data1 = 0;
		sample->data2 = 0;
		sample->data3 = 0;
		sample->data4 = 0;
		sample->data5 = 0;
		sample->data6 = 0;
		sample->data7 = 0;
		sample->data8 = 0;
		sample->data9 = 0;
		sample->data10 = 0;
		sample->data11 = 0;
		sample->data12 = 0;
		sample->data13 = 0;
	}
}

bool StructSize50_serialize_topic(struct mvbs_cdr *cdr,
						StructSize50 *topic)
{
	if (!mcdr_serialize_uint32_t(cdr, topic->id)) {
		pr_debug("id serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->data1)) {
		pr_debug("data1 serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->data2)) {
		pr_debug("data2 serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->data3)) {
		pr_debug("data3 serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->data4)) {
		pr_debug("data4 serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->data5)) {
		pr_debug("data5 serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->data6)) {
		pr_debug("data6 serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->data7)) {
		pr_debug("data7 serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->data8)) {
		pr_debug("data8 serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->data9)) {
		pr_debug("data9 serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int32_t(cdr, topic->data10)) {
		pr_debug("data10 serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int16_t(cdr, topic->data11)) {
		pr_debug("data11 serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int16_t(cdr, topic->data12)) {
		pr_debug("data12 serialize failed!\n");
		return false;
	}

	if (!mcdr_serialize_int16_t(cdr, topic->data13)) {
		pr_debug("data13 serialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}

bool StructSize50_deserialize_topic(struct mvbs_cdr *cdr,
						StructSize50 *topic)
{
	if (!mcdr_deserialize_uint32_t(cdr, &topic->id)) {
		pr_debug("id deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->data1)) {
		pr_debug("data1 deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->data2)) {
		pr_debug("data2 deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->data3)) {
		pr_debug("data3 deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->data4)) {
		pr_debug("data4 deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->data5)) {
		pr_debug("data5 deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->data6)) {
		pr_debug("data6 deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->data7)) {
		pr_debug("data7 deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->data8)) {
		pr_debug("data8 deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->data9)) {
		pr_debug("data9 deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int32_t(cdr, &topic->data10)) {
		pr_debug("data10 deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int16_t(cdr, &topic->data11)) {
		pr_debug("data11 deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int16_t(cdr, &topic->data12)) {
		pr_debug("data12 deserialize failed!\n");
		return false;
	}

	if (!mcdr_deserialize_int16_t(cdr, &topic->data13)) {
		pr_debug("data13 deserialize failed!\n");
		return false;
	}

	return !mcdr_buffer_has_error(cdr);
}
static uint32_t StructSize50_get_type_size(void)
{
	uint32_t size = ALIGN_UP_4(StructSize50_topic_max_size(0) + 4u);

	if (size != STRUCTSIZE50_SIZE)
	{
		pr_warn("size:%d, STRUCTSIZE50_SIZE:%d\n", size, STRUCTSIZE50_SIZE);
		pr_warn("size is not equal to STRUCTSIZE50_SIZE\n");

		return size;
	}

	return STRUCTSIZE50_SIZE;
}

static bool StructSize50_serialize(void *data, struct serialized_payload *payload)
{
	StructSize50  *topic = (StructSize50  *)data;
	struct mvbs_cdr cdr = {0};

	if ((data == NULL) || (payload == NULL)) {
		return false;
	}

	mcdr_init_buffer(&cdr, (const uint8_t *)payload->data + 4, payload->length - 4);

	if (!StructSize50_serialize_topic(&cdr, topic)) {
		return false;
	}

	if (!mcdr_serialized_payload_header(&cdr, payload)) {
		return false;
	}
	return true;
}

static bool StructSize50_deserialize(void *data, struct serialized_payload *payload)
{
	StructSize50 *topic = (StructSize50 *)data;
	struct mvbs_cdr cdr = {0};

	if (data == NULL) {
		return false;
	}

	if (mcdr_init_from_serialized_payload(&cdr, payload) < 0) {
		return false;
	}

	if (!StructSize50_deserialize_topic(&cdr, topic)) {
		return false;
	}

	return true;
}StructSize50 *StructSize50_create(void)
{
	StructSize50 *sample;
	uint32_t size = sizeof(struct StructSize50);

	sample = (StructSize50 *)mvbs_calloc(1, size);
	return sample;
}

void StructSize50_delete(StructSize50 *sample)
{
	if (sample != NULL) {
		mvbs_free(sample);
	}
}

const struct type_plugin  MVBS_HelloWorld_typeplugin = {
	.name		= "MVBS::HelloWorld",

	.deserialize	= MVBS_HelloWorld_deserialize,
	.serialize	= MVBS_HelloWorld_serialize,

	.type_size	= MVBS_HelloWorld_get_type_size,
	.crc16		= "560F"
};


const struct type_plugin  MVBS_HelloWorld1_typeplugin = {
	.name		= "MVBS::HelloWorld1",

	.deserialize	= MVBS_HelloWorld1_deserialize,
	.serialize	= MVBS_HelloWorld1_serialize,

	.type_size	= MVBS_HelloWorld1_get_type_size,
	.crc16		= "F1E7"
};


const struct type_plugin  MVBS_HelloWorld2_typeplugin = {
	.name		= "MVBS::HelloWorld2",

	.deserialize	= MVBS_HelloWorld2_deserialize,
	.serialize	= MVBS_HelloWorld2_serialize,

	.type_size	= MVBS_HelloWorld2_get_type_size,
	.crc16		= "9679"
};


const struct type_plugin  MVBS_HelloWorld3_typeplugin = {
	.name		= "MVBS::HelloWorld3",

	.deserialize	= MVBS_HelloWorld3_deserialize,
	.serialize	= MVBS_HelloWorld3_serialize,

	.type_size	= MVBS_HelloWorld3_get_type_size,
	.crc16		= "6DBA"
};


const struct type_plugin  MVBS_HelloWorld4_typeplugin = {
	.name		= "MVBS::HelloWorld4",

	.deserialize	= MVBS_HelloWorld4_deserialize,
	.serialize	= MVBS_HelloWorld4_serialize,

	.type_size	= MVBS_HelloWorld4_get_type_size,
	.crc16		= "FAF4"
};


const struct type_plugin  MVBS_HelloWorld5_typeplugin = {
	.name		= "MVBS::HelloWorld5",

	.deserialize	= MVBS_HelloWorld5_deserialize,
	.serialize	= MVBS_HelloWorld5_serialize,

	.type_size	= MVBS_HelloWorld5_get_type_size,
	.crc16		= "3B68"
};


const struct type_plugin  MVBS_BasicTypeStruct_typeplugin = {
	.name		= "MVBS::BasicTypeStruct",

	.deserialize	= MVBS_BasicTypeStruct_deserialize,
	.serialize	= MVBS_BasicTypeStruct_serialize,

	.type_size	= MVBS_BasicTypeStruct_get_type_size,
	.crc16		= "5E5E"
};


const struct type_plugin  MVBS_sdatatype_typeplugin = {
	.name		= "MVBS::sdatatype",

	.deserialize	= MVBS_sdatatype_deserialize,
	.serialize	= MVBS_sdatatype_serialize,

	.type_size	= MVBS_sdatatype_get_type_size,
	.crc16		= "A56F"
};


const struct type_plugin  MVBS_ComplexDataType_typeplugin = {
	.name		= "MVBS::ComplexDataType",

	.deserialize	= MVBS_ComplexDataType_deserialize,
	.serialize	= MVBS_ComplexDataType_serialize,

	.type_size	= MVBS_ComplexDataType_get_type_size,
	.crc16		= "7A70"
};


const struct type_plugin  StructSize50_typeplugin = {
	.name		= "StructSize50",

	.deserialize	= StructSize50_deserialize,
	.serialize	= StructSize50_serialize,

	.type_size	= StructSize50_get_type_size,
	.crc16		= "35AE"
};



#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>