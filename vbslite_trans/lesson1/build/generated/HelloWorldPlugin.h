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


#ifndef __MVBS_HELLOWORLD_H
#define __MVBS_HELLOWORLD_H


#include <stdint.h>
#include <stdbool.h>
#include <string.h>

struct mvbs_cdr;
/* --------------------------------------------------------------------------
 *  All of New Function declarations: MVBS_HelloWorld
 * --------------------------------------------------------------------------
 */
#define	MVBS_HELLOWORLD_SIZE		80


typedef struct MVBS_HelloWorld {
	int32_t id;
	char msg[64 + 1];
} MVBS_HelloWorld;


void MVBS_HelloWorld_init(MVBS_HelloWorld *sample);


bool MVBS_HelloWorld_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld *topic);

bool MVBS_HelloWorld_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld *topic);

uint32_t MVBS_HelloWorld_topic_max_size(uint32_t size);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: MVBS_HelloWorld1
 * --------------------------------------------------------------------------
 */
#define	MVBS_HELLOWORLD1_SIZE		8


typedef struct MVBS_HelloWorld1 {
	int16_t short_data;
	uint16_t ushort_data;
} MVBS_HelloWorld1;


void MVBS_HelloWorld1_init(MVBS_HelloWorld1 *sample);


bool MVBS_HelloWorld1_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld1 *topic);

bool MVBS_HelloWorld1_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld1 *topic);

uint32_t MVBS_HelloWorld1_topic_max_size(uint32_t size);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: MVBS_HelloWorld2
 * --------------------------------------------------------------------------
 */
#define	MVBS_HELLOWORLD2_SIZE		20


typedef struct MVBS_HelloWorld2 {
	float float_data;
	double double_data;
} MVBS_HelloWorld2;


void MVBS_HelloWorld2_init(MVBS_HelloWorld2 *sample);


bool MVBS_HelloWorld2_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld2 *topic);

bool MVBS_HelloWorld2_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld2 *topic);

uint32_t MVBS_HelloWorld2_topic_max_size(uint32_t size);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: MVBS_HelloWorld3
 * --------------------------------------------------------------------------
 */
#define	MVBS_HELLOWORLD3_SIZE		92


typedef struct MVBS_HelloWorld3 {
	MVBS_HelloWorld struct_data;
	double double_data;
} MVBS_HelloWorld3;


void MVBS_HelloWorld3_init(MVBS_HelloWorld3 *sample);


bool MVBS_HelloWorld3_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld3 *topic);

bool MVBS_HelloWorld3_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld3 *topic);

uint32_t MVBS_HelloWorld3_topic_max_size(uint32_t size);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: MVBS_HelloWorld4
 * --------------------------------------------------------------------------
 */
#define	MVBS_HELLOWORLD4_SIZE		100


typedef struct MVBS_HelloWorld4 {
	MVBS_HelloWorld struct_data;
	double double1_data;
	double double2_data;
} MVBS_HelloWorld4;


void MVBS_HelloWorld4_init(MVBS_HelloWorld4 *sample);


bool MVBS_HelloWorld4_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld4 *topic);

bool MVBS_HelloWorld4_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld4 *topic);

uint32_t MVBS_HelloWorld4_topic_max_size(uint32_t size);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: MVBS_HelloWorld5
 * --------------------------------------------------------------------------
 */
#define	MVBS_HELLOWORLD5_SIZE		164


typedef struct MVBS_HelloWorld5 {
	MVBS_HelloWorld struct1_data;
	MVBS_HelloWorld struct2_data;
	double double_data;
} MVBS_HelloWorld5;


void MVBS_HelloWorld5_init(MVBS_HelloWorld5 *sample);


bool MVBS_HelloWorld5_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld5 *topic);

bool MVBS_HelloWorld5_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_HelloWorld5 *topic);

uint32_t MVBS_HelloWorld5_topic_max_size(uint32_t size);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: MVBS_BasicTypeStruct
 * --------------------------------------------------------------------------
 */
#define	MVBS_BASICTYPESTRUCT_SIZE		128


typedef struct MVBS_BasicTypeStruct {
	int32_t id;
	char msg[64 + 1];
	unsigned char tag;
	uint8_t u8_data;
	int16_t short_data;
	uint16_t ushort_data;
	uint32_t ulong_data;
	int64_t llong_data;
	uint64_t ullong_data;
	float float_data;
	double double_data;
	uint8_t bool_data;
} MVBS_BasicTypeStruct;


void MVBS_BasicTypeStruct_init(MVBS_BasicTypeStruct *sample);


bool MVBS_BasicTypeStruct_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_BasicTypeStruct *topic);

bool MVBS_BasicTypeStruct_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_BasicTypeStruct *topic);

uint32_t MVBS_BasicTypeStruct_topic_max_size(uint32_t size);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: MVBS_sdatatype
 * --------------------------------------------------------------------------
 */
#define	MVBS_SDATATYPE_SIZE		16


typedef struct MVBS_sdatatype {
	int32_t data1;
	int32_t data2;
	int32_t data3;
} MVBS_sdatatype;


void MVBS_sdatatype_init(MVBS_sdatatype *sample);


bool MVBS_sdatatype_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_sdatatype *topic);

bool MVBS_sdatatype_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_sdatatype *topic);

uint32_t MVBS_sdatatype_topic_max_size(uint32_t size);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: MVBS_edatatype
 * --------------------------------------------------------------------------
 */



typedef enum MVBS_edatatype {
	ZERO = 0,
	ONE = 1,
	TWO = 2,
	THREE = 3
} MVBS_edatatype;

void MVBS_edatatype_init(MVBS_edatatype *sample);


bool MVBS_edatatype_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_edatatype *topic);

bool MVBS_edatatype_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_edatatype *topic);

uint32_t MVBS_edatatype_topic_max_size(uint32_t size);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: MVBS_arrayType
 * --------------------------------------------------------------------------
 */




typedef int32_t MVBS_arrayType[100];

void MVBS_arrayType_init(MVBS_arrayType *sample);


bool MVBS_arrayType_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_arrayType *topic);

bool MVBS_arrayType_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_arrayType *topic);

uint32_t MVBS_arrayType_topic_max_size(uint32_t size);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: MVBS_arrayType1
 * --------------------------------------------------------------------------
 */




typedef MVBS_sdatatype MVBS_arrayType1[20];

void MVBS_arrayType1_init(MVBS_arrayType1 *sample);


bool MVBS_arrayType1_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_arrayType1 *topic);

bool MVBS_arrayType1_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_arrayType1 *topic);

uint32_t MVBS_arrayType1_topic_max_size(uint32_t size);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: MVBS_ComplexDataType
 * --------------------------------------------------------------------------
 */
#define	MVBS_COMPLEXDATATYPE_SIZE		660


typedef struct MVBS_ComplexDataType {
	MVBS_sdatatype struct_data;
	MVBS_edatatype enum_data;
	MVBS_arrayType array_data;
	MVBS_arrayType1 arrayType1_data;
} MVBS_ComplexDataType;


void MVBS_ComplexDataType_init(MVBS_ComplexDataType *sample);


bool MVBS_ComplexDataType_deserialize_topic(struct mvbs_cdr *cdr,
						MVBS_ComplexDataType *topic);

bool MVBS_ComplexDataType_serialize_topic(struct mvbs_cdr *cdr,
						MVBS_ComplexDataType *topic);

uint32_t MVBS_ComplexDataType_topic_max_size(uint32_t size);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: StructSize50
 * --------------------------------------------------------------------------
 */
#define	STRUCTSIZE50_SIZE		56


typedef struct StructSize50 {
	uint32_t id;
	int32_t data1;
	int32_t data2;
	int32_t data3;
	int32_t data4;
	int32_t data5;
	int32_t data6;
	int32_t data7;
	int32_t data8;
	int32_t data9;
	int32_t data10;
	int16_t data11;
	int16_t data12;
	int16_t data13;
} StructSize50;


void StructSize50_init(StructSize50 *sample);


bool StructSize50_deserialize_topic(struct mvbs_cdr *cdr,
						StructSize50 *topic);

bool StructSize50_serialize_topic(struct mvbs_cdr *cdr,
						StructSize50 *topic);

uint32_t StructSize50_topic_max_size(uint32_t size);


#endif /* __MVBS_HELLOWORLD_H__ */