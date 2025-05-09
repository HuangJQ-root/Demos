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


#ifndef __MVBS_VBSLITE_PERF_H
#define __MVBS_VBSLITE_PERF_H


#include <stdint.h>
#include <stdbool.h>
#include <string.h>

struct mvbs_cdr;
/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld1
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD1_SIZE		12


typedef struct HelloWorld1 {
	uint32_t index;
	int32_t message;
} HelloWorld1;


void HelloWorld1_init(HelloWorld1 *sample);


bool HelloWorld1_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld1 *topic);

bool HelloWorld1_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld1 *topic);

uint32_t HelloWorld1_topic_max_size(uint32_t size);
HelloWorld1 *HelloWorld1_create(void);

void HelloWorld1_delete(HelloWorld1 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld2
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD2_SIZE		12


typedef struct HelloWorld2 {
	uint32_t index;
	int32_t message;
} HelloWorld2;


void HelloWorld2_init(HelloWorld2 *sample);


bool HelloWorld2_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld2 *topic);

bool HelloWorld2_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld2 *topic);

uint32_t HelloWorld2_topic_max_size(uint32_t size);
HelloWorld2 *HelloWorld2_create(void);

void HelloWorld2_delete(HelloWorld2 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld3
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD3_SIZE		12


typedef struct HelloWorld3 {
	uint32_t index;
	int32_t message;
} HelloWorld3;


void HelloWorld3_init(HelloWorld3 *sample);


bool HelloWorld3_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld3 *topic);

bool HelloWorld3_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld3 *topic);

uint32_t HelloWorld3_topic_max_size(uint32_t size);
HelloWorld3 *HelloWorld3_create(void);

void HelloWorld3_delete(HelloWorld3 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld4
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD4_SIZE		12


typedef struct HelloWorld4 {
	uint32_t index;
	int32_t message;
} HelloWorld4;


void HelloWorld4_init(HelloWorld4 *sample);


bool HelloWorld4_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld4 *topic);

bool HelloWorld4_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld4 *topic);

uint32_t HelloWorld4_topic_max_size(uint32_t size);
HelloWorld4 *HelloWorld4_create(void);

void HelloWorld4_delete(HelloWorld4 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld5
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD5_SIZE		12


typedef struct HelloWorld5 {
	uint32_t index;
	int32_t message;
} HelloWorld5;


void HelloWorld5_init(HelloWorld5 *sample);


bool HelloWorld5_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld5 *topic);

bool HelloWorld5_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld5 *topic);

uint32_t HelloWorld5_topic_max_size(uint32_t size);
HelloWorld5 *HelloWorld5_create(void);

void HelloWorld5_delete(HelloWorld5 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld6
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD6_SIZE		12


typedef struct HelloWorld6 {
	uint32_t index;
	int32_t message;
} HelloWorld6;


void HelloWorld6_init(HelloWorld6 *sample);


bool HelloWorld6_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld6 *topic);

bool HelloWorld6_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld6 *topic);

uint32_t HelloWorld6_topic_max_size(uint32_t size);
HelloWorld6 *HelloWorld6_create(void);

void HelloWorld6_delete(HelloWorld6 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld7
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD7_SIZE		12


typedef struct HelloWorld7 {
	uint32_t index;
	int32_t message;
} HelloWorld7;


void HelloWorld7_init(HelloWorld7 *sample);


bool HelloWorld7_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld7 *topic);

bool HelloWorld7_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld7 *topic);

uint32_t HelloWorld7_topic_max_size(uint32_t size);
HelloWorld7 *HelloWorld7_create(void);

void HelloWorld7_delete(HelloWorld7 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld8
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD8_SIZE		12


typedef struct HelloWorld8 {
	uint32_t index;
	int32_t message;
} HelloWorld8;


void HelloWorld8_init(HelloWorld8 *sample);


bool HelloWorld8_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld8 *topic);

bool HelloWorld8_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld8 *topic);

uint32_t HelloWorld8_topic_max_size(uint32_t size);
HelloWorld8 *HelloWorld8_create(void);

void HelloWorld8_delete(HelloWorld8 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld9
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD9_SIZE		12


typedef struct HelloWorld9 {
	uint32_t index;
	int32_t message;
} HelloWorld9;


void HelloWorld9_init(HelloWorld9 *sample);


bool HelloWorld9_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld9 *topic);

bool HelloWorld9_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld9 *topic);

uint32_t HelloWorld9_topic_max_size(uint32_t size);
HelloWorld9 *HelloWorld9_create(void);

void HelloWorld9_delete(HelloWorld9 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld10
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD10_SIZE		12


typedef struct HelloWorld10 {
	uint32_t index;
	int32_t message;
} HelloWorld10;


void HelloWorld10_init(HelloWorld10 *sample);


bool HelloWorld10_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld10 *topic);

bool HelloWorld10_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld10 *topic);

uint32_t HelloWorld10_topic_max_size(uint32_t size);
HelloWorld10 *HelloWorld10_create(void);

void HelloWorld10_delete(HelloWorld10 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld11
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD11_SIZE		12


typedef struct HelloWorld11 {
	uint32_t index;
	int32_t message;
} HelloWorld11;


void HelloWorld11_init(HelloWorld11 *sample);


bool HelloWorld11_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld11 *topic);

bool HelloWorld11_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld11 *topic);

uint32_t HelloWorld11_topic_max_size(uint32_t size);
HelloWorld11 *HelloWorld11_create(void);

void HelloWorld11_delete(HelloWorld11 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld12
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD12_SIZE		12


typedef struct HelloWorld12 {
	uint32_t index;
	int32_t message;
} HelloWorld12;


void HelloWorld12_init(HelloWorld12 *sample);


bool HelloWorld12_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld12 *topic);

bool HelloWorld12_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld12 *topic);

uint32_t HelloWorld12_topic_max_size(uint32_t size);
HelloWorld12 *HelloWorld12_create(void);

void HelloWorld12_delete(HelloWorld12 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld13
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD13_SIZE		12


typedef struct HelloWorld13 {
	uint32_t index;
	int32_t message;
} HelloWorld13;


void HelloWorld13_init(HelloWorld13 *sample);


bool HelloWorld13_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld13 *topic);

bool HelloWorld13_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld13 *topic);

uint32_t HelloWorld13_topic_max_size(uint32_t size);
HelloWorld13 *HelloWorld13_create(void);

void HelloWorld13_delete(HelloWorld13 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld14
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD14_SIZE		12


typedef struct HelloWorld14 {
	uint32_t index;
	int32_t message;
} HelloWorld14;


void HelloWorld14_init(HelloWorld14 *sample);


bool HelloWorld14_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld14 *topic);

bool HelloWorld14_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld14 *topic);

uint32_t HelloWorld14_topic_max_size(uint32_t size);
HelloWorld14 *HelloWorld14_create(void);

void HelloWorld14_delete(HelloWorld14 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld15
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD15_SIZE		12


typedef struct HelloWorld15 {
	uint32_t index;
	int32_t message;
} HelloWorld15;


void HelloWorld15_init(HelloWorld15 *sample);


bool HelloWorld15_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld15 *topic);

bool HelloWorld15_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld15 *topic);

uint32_t HelloWorld15_topic_max_size(uint32_t size);
HelloWorld15 *HelloWorld15_create(void);

void HelloWorld15_delete(HelloWorld15 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld16
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD16_SIZE		12


typedef struct HelloWorld16 {
	uint32_t index;
	int32_t message;
} HelloWorld16;


void HelloWorld16_init(HelloWorld16 *sample);


bool HelloWorld16_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld16 *topic);

bool HelloWorld16_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld16 *topic);

uint32_t HelloWorld16_topic_max_size(uint32_t size);
HelloWorld16 *HelloWorld16_create(void);

void HelloWorld16_delete(HelloWorld16 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld17
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD17_SIZE		12


typedef struct HelloWorld17 {
	uint32_t index;
	int32_t message;
} HelloWorld17;


void HelloWorld17_init(HelloWorld17 *sample);


bool HelloWorld17_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld17 *topic);

bool HelloWorld17_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld17 *topic);

uint32_t HelloWorld17_topic_max_size(uint32_t size);
HelloWorld17 *HelloWorld17_create(void);

void HelloWorld17_delete(HelloWorld17 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld18
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD18_SIZE		12


typedef struct HelloWorld18 {
	uint32_t index;
	int32_t message;
} HelloWorld18;


void HelloWorld18_init(HelloWorld18 *sample);


bool HelloWorld18_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld18 *topic);

bool HelloWorld18_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld18 *topic);

uint32_t HelloWorld18_topic_max_size(uint32_t size);
HelloWorld18 *HelloWorld18_create(void);

void HelloWorld18_delete(HelloWorld18 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld19
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD19_SIZE		12


typedef struct HelloWorld19 {
	uint32_t index;
	int32_t message;
} HelloWorld19;


void HelloWorld19_init(HelloWorld19 *sample);


bool HelloWorld19_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld19 *topic);

bool HelloWorld19_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld19 *topic);

uint32_t HelloWorld19_topic_max_size(uint32_t size);
HelloWorld19 *HelloWorld19_create(void);

void HelloWorld19_delete(HelloWorld19 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld20
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD20_SIZE		12


typedef struct HelloWorld20 {
	uint32_t index;
	int32_t message;
} HelloWorld20;


void HelloWorld20_init(HelloWorld20 *sample);


bool HelloWorld20_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld20 *topic);

bool HelloWorld20_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld20 *topic);

uint32_t HelloWorld20_topic_max_size(uint32_t size);
HelloWorld20 *HelloWorld20_create(void);

void HelloWorld20_delete(HelloWorld20 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld21
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD21_SIZE		12


typedef struct HelloWorld21 {
	uint32_t index;
	int32_t message;
} HelloWorld21;


void HelloWorld21_init(HelloWorld21 *sample);


bool HelloWorld21_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld21 *topic);

bool HelloWorld21_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld21 *topic);

uint32_t HelloWorld21_topic_max_size(uint32_t size);
HelloWorld21 *HelloWorld21_create(void);

void HelloWorld21_delete(HelloWorld21 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld22
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD22_SIZE		12


typedef struct HelloWorld22 {
	uint32_t index;
	int32_t message;
} HelloWorld22;


void HelloWorld22_init(HelloWorld22 *sample);


bool HelloWorld22_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld22 *topic);

bool HelloWorld22_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld22 *topic);

uint32_t HelloWorld22_topic_max_size(uint32_t size);
HelloWorld22 *HelloWorld22_create(void);

void HelloWorld22_delete(HelloWorld22 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld23
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD23_SIZE		12


typedef struct HelloWorld23 {
	uint32_t index;
	int32_t message;
} HelloWorld23;


void HelloWorld23_init(HelloWorld23 *sample);


bool HelloWorld23_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld23 *topic);

bool HelloWorld23_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld23 *topic);

uint32_t HelloWorld23_topic_max_size(uint32_t size);
HelloWorld23 *HelloWorld23_create(void);

void HelloWorld23_delete(HelloWorld23 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld24
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD24_SIZE		12


typedef struct HelloWorld24 {
	uint32_t index;
	int32_t message;
} HelloWorld24;


void HelloWorld24_init(HelloWorld24 *sample);


bool HelloWorld24_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld24 *topic);

bool HelloWorld24_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld24 *topic);

uint32_t HelloWorld24_topic_max_size(uint32_t size);
HelloWorld24 *HelloWorld24_create(void);

void HelloWorld24_delete(HelloWorld24 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld25
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD25_SIZE		12


typedef struct HelloWorld25 {
	uint32_t index;
	int32_t message;
} HelloWorld25;


void HelloWorld25_init(HelloWorld25 *sample);


bool HelloWorld25_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld25 *topic);

bool HelloWorld25_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld25 *topic);

uint32_t HelloWorld25_topic_max_size(uint32_t size);
HelloWorld25 *HelloWorld25_create(void);

void HelloWorld25_delete(HelloWorld25 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld26
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD26_SIZE		12


typedef struct HelloWorld26 {
	uint32_t index;
	int32_t message;
} HelloWorld26;


void HelloWorld26_init(HelloWorld26 *sample);


bool HelloWorld26_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld26 *topic);

bool HelloWorld26_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld26 *topic);

uint32_t HelloWorld26_topic_max_size(uint32_t size);
HelloWorld26 *HelloWorld26_create(void);

void HelloWorld26_delete(HelloWorld26 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld27
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD27_SIZE		12


typedef struct HelloWorld27 {
	uint32_t index;
	int32_t message;
} HelloWorld27;


void HelloWorld27_init(HelloWorld27 *sample);


bool HelloWorld27_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld27 *topic);

bool HelloWorld27_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld27 *topic);

uint32_t HelloWorld27_topic_max_size(uint32_t size);
HelloWorld27 *HelloWorld27_create(void);

void HelloWorld27_delete(HelloWorld27 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld28
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD28_SIZE		12


typedef struct HelloWorld28 {
	uint32_t index;
	int32_t message;
} HelloWorld28;


void HelloWorld28_init(HelloWorld28 *sample);


bool HelloWorld28_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld28 *topic);

bool HelloWorld28_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld28 *topic);

uint32_t HelloWorld28_topic_max_size(uint32_t size);
HelloWorld28 *HelloWorld28_create(void);

void HelloWorld28_delete(HelloWorld28 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld29
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD29_SIZE		12


typedef struct HelloWorld29 {
	uint32_t index;
	int32_t message;
} HelloWorld29;


void HelloWorld29_init(HelloWorld29 *sample);


bool HelloWorld29_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld29 *topic);

bool HelloWorld29_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld29 *topic);

uint32_t HelloWorld29_topic_max_size(uint32_t size);
HelloWorld29 *HelloWorld29_create(void);

void HelloWorld29_delete(HelloWorld29 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld30
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD30_SIZE		12


typedef struct HelloWorld30 {
	uint32_t index;
	int32_t message;
} HelloWorld30;


void HelloWorld30_init(HelloWorld30 *sample);


bool HelloWorld30_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld30 *topic);

bool HelloWorld30_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld30 *topic);

uint32_t HelloWorld30_topic_max_size(uint32_t size);
HelloWorld30 *HelloWorld30_create(void);

void HelloWorld30_delete(HelloWorld30 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld31
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD31_SIZE		12


typedef struct HelloWorld31 {
	uint32_t index;
	int32_t message;
} HelloWorld31;


void HelloWorld31_init(HelloWorld31 *sample);


bool HelloWorld31_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld31 *topic);

bool HelloWorld31_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld31 *topic);

uint32_t HelloWorld31_topic_max_size(uint32_t size);
HelloWorld31 *HelloWorld31_create(void);

void HelloWorld31_delete(HelloWorld31 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld32
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD32_SIZE		12


typedef struct HelloWorld32 {
	uint32_t index;
	int32_t message;
} HelloWorld32;


void HelloWorld32_init(HelloWorld32 *sample);


bool HelloWorld32_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld32 *topic);

bool HelloWorld32_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld32 *topic);

uint32_t HelloWorld32_topic_max_size(uint32_t size);
HelloWorld32 *HelloWorld32_create(void);

void HelloWorld32_delete(HelloWorld32 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld33
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD33_SIZE		12


typedef struct HelloWorld33 {
	uint32_t index;
	int32_t message;
} HelloWorld33;


void HelloWorld33_init(HelloWorld33 *sample);


bool HelloWorld33_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld33 *topic);

bool HelloWorld33_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld33 *topic);

uint32_t HelloWorld33_topic_max_size(uint32_t size);
HelloWorld33 *HelloWorld33_create(void);

void HelloWorld33_delete(HelloWorld33 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld34
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD34_SIZE		12


typedef struct HelloWorld34 {
	uint32_t index;
	int32_t message;
} HelloWorld34;


void HelloWorld34_init(HelloWorld34 *sample);


bool HelloWorld34_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld34 *topic);

bool HelloWorld34_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld34 *topic);

uint32_t HelloWorld34_topic_max_size(uint32_t size);
HelloWorld34 *HelloWorld34_create(void);

void HelloWorld34_delete(HelloWorld34 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld35
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD35_SIZE		12


typedef struct HelloWorld35 {
	uint32_t index;
	int32_t message;
} HelloWorld35;


void HelloWorld35_init(HelloWorld35 *sample);


bool HelloWorld35_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld35 *topic);

bool HelloWorld35_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld35 *topic);

uint32_t HelloWorld35_topic_max_size(uint32_t size);
HelloWorld35 *HelloWorld35_create(void);

void HelloWorld35_delete(HelloWorld35 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld36
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD36_SIZE		12


typedef struct HelloWorld36 {
	uint32_t index;
	int32_t message;
} HelloWorld36;


void HelloWorld36_init(HelloWorld36 *sample);


bool HelloWorld36_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld36 *topic);

bool HelloWorld36_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld36 *topic);

uint32_t HelloWorld36_topic_max_size(uint32_t size);
HelloWorld36 *HelloWorld36_create(void);

void HelloWorld36_delete(HelloWorld36 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld37
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD37_SIZE		12


typedef struct HelloWorld37 {
	uint32_t index;
	int32_t message;
} HelloWorld37;


void HelloWorld37_init(HelloWorld37 *sample);


bool HelloWorld37_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld37 *topic);

bool HelloWorld37_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld37 *topic);

uint32_t HelloWorld37_topic_max_size(uint32_t size);
HelloWorld37 *HelloWorld37_create(void);

void HelloWorld37_delete(HelloWorld37 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld38
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD38_SIZE		12


typedef struct HelloWorld38 {
	uint32_t index;
	int32_t message;
} HelloWorld38;


void HelloWorld38_init(HelloWorld38 *sample);


bool HelloWorld38_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld38 *topic);

bool HelloWorld38_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld38 *topic);

uint32_t HelloWorld38_topic_max_size(uint32_t size);
HelloWorld38 *HelloWorld38_create(void);

void HelloWorld38_delete(HelloWorld38 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld39
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD39_SIZE		12


typedef struct HelloWorld39 {
	uint32_t index;
	int32_t message;
} HelloWorld39;


void HelloWorld39_init(HelloWorld39 *sample);


bool HelloWorld39_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld39 *topic);

bool HelloWorld39_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld39 *topic);

uint32_t HelloWorld39_topic_max_size(uint32_t size);
HelloWorld39 *HelloWorld39_create(void);

void HelloWorld39_delete(HelloWorld39 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld40
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD40_SIZE		12


typedef struct HelloWorld40 {
	uint32_t index;
	int32_t message;
} HelloWorld40;


void HelloWorld40_init(HelloWorld40 *sample);


bool HelloWorld40_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld40 *topic);

bool HelloWorld40_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld40 *topic);

uint32_t HelloWorld40_topic_max_size(uint32_t size);
HelloWorld40 *HelloWorld40_create(void);

void HelloWorld40_delete(HelloWorld40 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld41
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD41_SIZE		12


typedef struct HelloWorld41 {
	uint32_t index;
	int32_t message;
} HelloWorld41;


void HelloWorld41_init(HelloWorld41 *sample);


bool HelloWorld41_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld41 *topic);

bool HelloWorld41_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld41 *topic);

uint32_t HelloWorld41_topic_max_size(uint32_t size);
HelloWorld41 *HelloWorld41_create(void);

void HelloWorld41_delete(HelloWorld41 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld42
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD42_SIZE		12


typedef struct HelloWorld42 {
	uint32_t index;
	int32_t message;
} HelloWorld42;


void HelloWorld42_init(HelloWorld42 *sample);


bool HelloWorld42_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld42 *topic);

bool HelloWorld42_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld42 *topic);

uint32_t HelloWorld42_topic_max_size(uint32_t size);
HelloWorld42 *HelloWorld42_create(void);

void HelloWorld42_delete(HelloWorld42 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld43
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD43_SIZE		12


typedef struct HelloWorld43 {
	uint32_t index;
	int32_t message;
} HelloWorld43;


void HelloWorld43_init(HelloWorld43 *sample);


bool HelloWorld43_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld43 *topic);

bool HelloWorld43_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld43 *topic);

uint32_t HelloWorld43_topic_max_size(uint32_t size);
HelloWorld43 *HelloWorld43_create(void);

void HelloWorld43_delete(HelloWorld43 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld44
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD44_SIZE		12


typedef struct HelloWorld44 {
	uint32_t index;
	int32_t message;
} HelloWorld44;


void HelloWorld44_init(HelloWorld44 *sample);


bool HelloWorld44_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld44 *topic);

bool HelloWorld44_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld44 *topic);

uint32_t HelloWorld44_topic_max_size(uint32_t size);
HelloWorld44 *HelloWorld44_create(void);

void HelloWorld44_delete(HelloWorld44 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld45
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD45_SIZE		12


typedef struct HelloWorld45 {
	uint32_t index;
	int32_t message;
} HelloWorld45;


void HelloWorld45_init(HelloWorld45 *sample);


bool HelloWorld45_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld45 *topic);

bool HelloWorld45_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld45 *topic);

uint32_t HelloWorld45_topic_max_size(uint32_t size);
HelloWorld45 *HelloWorld45_create(void);

void HelloWorld45_delete(HelloWorld45 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld46
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD46_SIZE		12


typedef struct HelloWorld46 {
	uint32_t index;
	int32_t message;
} HelloWorld46;


void HelloWorld46_init(HelloWorld46 *sample);


bool HelloWorld46_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld46 *topic);

bool HelloWorld46_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld46 *topic);

uint32_t HelloWorld46_topic_max_size(uint32_t size);
HelloWorld46 *HelloWorld46_create(void);

void HelloWorld46_delete(HelloWorld46 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld47
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD47_SIZE		12


typedef struct HelloWorld47 {
	uint32_t index;
	int32_t message;
} HelloWorld47;


void HelloWorld47_init(HelloWorld47 *sample);


bool HelloWorld47_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld47 *topic);

bool HelloWorld47_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld47 *topic);

uint32_t HelloWorld47_topic_max_size(uint32_t size);
HelloWorld47 *HelloWorld47_create(void);

void HelloWorld47_delete(HelloWorld47 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld48
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD48_SIZE		12


typedef struct HelloWorld48 {
	uint32_t index;
	int32_t message;
} HelloWorld48;


void HelloWorld48_init(HelloWorld48 *sample);


bool HelloWorld48_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld48 *topic);

bool HelloWorld48_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld48 *topic);

uint32_t HelloWorld48_topic_max_size(uint32_t size);
HelloWorld48 *HelloWorld48_create(void);

void HelloWorld48_delete(HelloWorld48 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld49
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD49_SIZE		12


typedef struct HelloWorld49 {
	uint32_t index;
	int32_t message;
} HelloWorld49;


void HelloWorld49_init(HelloWorld49 *sample);


bool HelloWorld49_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld49 *topic);

bool HelloWorld49_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld49 *topic);

uint32_t HelloWorld49_topic_max_size(uint32_t size);
HelloWorld49 *HelloWorld49_create(void);

void HelloWorld49_delete(HelloWorld49 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld50
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD50_SIZE		12


typedef struct HelloWorld50 {
	uint32_t index;
	int32_t message;
} HelloWorld50;


void HelloWorld50_init(HelloWorld50 *sample);


bool HelloWorld50_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld50 *topic);

bool HelloWorld50_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld50 *topic);

uint32_t HelloWorld50_topic_max_size(uint32_t size);
HelloWorld50 *HelloWorld50_create(void);

void HelloWorld50_delete(HelloWorld50 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld51
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD51_SIZE		12


typedef struct HelloWorld51 {
	uint32_t index;
	int32_t message;
} HelloWorld51;


void HelloWorld51_init(HelloWorld51 *sample);


bool HelloWorld51_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld51 *topic);

bool HelloWorld51_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld51 *topic);

uint32_t HelloWorld51_topic_max_size(uint32_t size);
HelloWorld51 *HelloWorld51_create(void);

void HelloWorld51_delete(HelloWorld51 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld52
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD52_SIZE		12


typedef struct HelloWorld52 {
	uint32_t index;
	int32_t message;
} HelloWorld52;


void HelloWorld52_init(HelloWorld52 *sample);


bool HelloWorld52_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld52 *topic);

bool HelloWorld52_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld52 *topic);

uint32_t HelloWorld52_topic_max_size(uint32_t size);
HelloWorld52 *HelloWorld52_create(void);

void HelloWorld52_delete(HelloWorld52 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld53
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD53_SIZE		12


typedef struct HelloWorld53 {
	uint32_t index;
	int32_t message;
} HelloWorld53;


void HelloWorld53_init(HelloWorld53 *sample);


bool HelloWorld53_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld53 *topic);

bool HelloWorld53_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld53 *topic);

uint32_t HelloWorld53_topic_max_size(uint32_t size);
HelloWorld53 *HelloWorld53_create(void);

void HelloWorld53_delete(HelloWorld53 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld54
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD54_SIZE		12


typedef struct HelloWorld54 {
	uint32_t index;
	int32_t message;
} HelloWorld54;


void HelloWorld54_init(HelloWorld54 *sample);


bool HelloWorld54_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld54 *topic);

bool HelloWorld54_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld54 *topic);

uint32_t HelloWorld54_topic_max_size(uint32_t size);
HelloWorld54 *HelloWorld54_create(void);

void HelloWorld54_delete(HelloWorld54 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld55
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD55_SIZE		12


typedef struct HelloWorld55 {
	uint32_t index;
	int32_t message;
} HelloWorld55;


void HelloWorld55_init(HelloWorld55 *sample);


bool HelloWorld55_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld55 *topic);

bool HelloWorld55_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld55 *topic);

uint32_t HelloWorld55_topic_max_size(uint32_t size);
HelloWorld55 *HelloWorld55_create(void);

void HelloWorld55_delete(HelloWorld55 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld56
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD56_SIZE		12


typedef struct HelloWorld56 {
	uint32_t index;
	int32_t message;
} HelloWorld56;


void HelloWorld56_init(HelloWorld56 *sample);


bool HelloWorld56_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld56 *topic);

bool HelloWorld56_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld56 *topic);

uint32_t HelloWorld56_topic_max_size(uint32_t size);
HelloWorld56 *HelloWorld56_create(void);

void HelloWorld56_delete(HelloWorld56 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld57
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD57_SIZE		12


typedef struct HelloWorld57 {
	uint32_t index;
	int32_t message;
} HelloWorld57;


void HelloWorld57_init(HelloWorld57 *sample);


bool HelloWorld57_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld57 *topic);

bool HelloWorld57_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld57 *topic);

uint32_t HelloWorld57_topic_max_size(uint32_t size);
HelloWorld57 *HelloWorld57_create(void);

void HelloWorld57_delete(HelloWorld57 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld58
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD58_SIZE		12


typedef struct HelloWorld58 {
	uint32_t index;
	int32_t message;
} HelloWorld58;


void HelloWorld58_init(HelloWorld58 *sample);


bool HelloWorld58_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld58 *topic);

bool HelloWorld58_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld58 *topic);

uint32_t HelloWorld58_topic_max_size(uint32_t size);
HelloWorld58 *HelloWorld58_create(void);

void HelloWorld58_delete(HelloWorld58 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld59
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD59_SIZE		12


typedef struct HelloWorld59 {
	uint32_t index;
	int32_t message;
} HelloWorld59;


void HelloWorld59_init(HelloWorld59 *sample);


bool HelloWorld59_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld59 *topic);

bool HelloWorld59_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld59 *topic);

uint32_t HelloWorld59_topic_max_size(uint32_t size);
HelloWorld59 *HelloWorld59_create(void);

void HelloWorld59_delete(HelloWorld59 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld60
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD60_SIZE		12


typedef struct HelloWorld60 {
	uint32_t index;
	int32_t message;
} HelloWorld60;


void HelloWorld60_init(HelloWorld60 *sample);


bool HelloWorld60_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld60 *topic);

bool HelloWorld60_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld60 *topic);

uint32_t HelloWorld60_topic_max_size(uint32_t size);
HelloWorld60 *HelloWorld60_create(void);

void HelloWorld60_delete(HelloWorld60 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld61
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD61_SIZE		12


typedef struct HelloWorld61 {
	uint32_t index;
	int32_t message;
} HelloWorld61;


void HelloWorld61_init(HelloWorld61 *sample);


bool HelloWorld61_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld61 *topic);

bool HelloWorld61_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld61 *topic);

uint32_t HelloWorld61_topic_max_size(uint32_t size);
HelloWorld61 *HelloWorld61_create(void);

void HelloWorld61_delete(HelloWorld61 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld62
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD62_SIZE		12


typedef struct HelloWorld62 {
	uint32_t index;
	int32_t message;
} HelloWorld62;


void HelloWorld62_init(HelloWorld62 *sample);


bool HelloWorld62_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld62 *topic);

bool HelloWorld62_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld62 *topic);

uint32_t HelloWorld62_topic_max_size(uint32_t size);
HelloWorld62 *HelloWorld62_create(void);

void HelloWorld62_delete(HelloWorld62 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld63
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD63_SIZE		12


typedef struct HelloWorld63 {
	uint32_t index;
	int32_t message;
} HelloWorld63;


void HelloWorld63_init(HelloWorld63 *sample);


bool HelloWorld63_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld63 *topic);

bool HelloWorld63_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld63 *topic);

uint32_t HelloWorld63_topic_max_size(uint32_t size);
HelloWorld63 *HelloWorld63_create(void);

void HelloWorld63_delete(HelloWorld63 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld64
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD64_SIZE		12


typedef struct HelloWorld64 {
	uint32_t index;
	int32_t message;
} HelloWorld64;


void HelloWorld64_init(HelloWorld64 *sample);


bool HelloWorld64_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld64 *topic);

bool HelloWorld64_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld64 *topic);

uint32_t HelloWorld64_topic_max_size(uint32_t size);
HelloWorld64 *HelloWorld64_create(void);

void HelloWorld64_delete(HelloWorld64 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld65
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD65_SIZE		12


typedef struct HelloWorld65 {
	uint32_t index;
	int32_t message;
} HelloWorld65;


void HelloWorld65_init(HelloWorld65 *sample);


bool HelloWorld65_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld65 *topic);

bool HelloWorld65_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld65 *topic);

uint32_t HelloWorld65_topic_max_size(uint32_t size);
HelloWorld65 *HelloWorld65_create(void);

void HelloWorld65_delete(HelloWorld65 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld66
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD66_SIZE		12


typedef struct HelloWorld66 {
	uint32_t index;
	int32_t message;
} HelloWorld66;


void HelloWorld66_init(HelloWorld66 *sample);


bool HelloWorld66_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld66 *topic);

bool HelloWorld66_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld66 *topic);

uint32_t HelloWorld66_topic_max_size(uint32_t size);
HelloWorld66 *HelloWorld66_create(void);

void HelloWorld66_delete(HelloWorld66 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld67
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD67_SIZE		12


typedef struct HelloWorld67 {
	uint32_t index;
	int32_t message;
} HelloWorld67;


void HelloWorld67_init(HelloWorld67 *sample);


bool HelloWorld67_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld67 *topic);

bool HelloWorld67_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld67 *topic);

uint32_t HelloWorld67_topic_max_size(uint32_t size);
HelloWorld67 *HelloWorld67_create(void);

void HelloWorld67_delete(HelloWorld67 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld68
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD68_SIZE		12


typedef struct HelloWorld68 {
	uint32_t index;
	int32_t message;
} HelloWorld68;


void HelloWorld68_init(HelloWorld68 *sample);


bool HelloWorld68_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld68 *topic);

bool HelloWorld68_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld68 *topic);

uint32_t HelloWorld68_topic_max_size(uint32_t size);
HelloWorld68 *HelloWorld68_create(void);

void HelloWorld68_delete(HelloWorld68 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld69
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD69_SIZE		12


typedef struct HelloWorld69 {
	uint32_t index;
	int32_t message;
} HelloWorld69;


void HelloWorld69_init(HelloWorld69 *sample);


bool HelloWorld69_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld69 *topic);

bool HelloWorld69_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld69 *topic);

uint32_t HelloWorld69_topic_max_size(uint32_t size);
HelloWorld69 *HelloWorld69_create(void);

void HelloWorld69_delete(HelloWorld69 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld70
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD70_SIZE		12


typedef struct HelloWorld70 {
	uint32_t index;
	int32_t message;
} HelloWorld70;


void HelloWorld70_init(HelloWorld70 *sample);


bool HelloWorld70_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld70 *topic);

bool HelloWorld70_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld70 *topic);

uint32_t HelloWorld70_topic_max_size(uint32_t size);
HelloWorld70 *HelloWorld70_create(void);

void HelloWorld70_delete(HelloWorld70 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld71
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD71_SIZE		12


typedef struct HelloWorld71 {
	uint32_t index;
	int32_t message;
} HelloWorld71;


void HelloWorld71_init(HelloWorld71 *sample);


bool HelloWorld71_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld71 *topic);

bool HelloWorld71_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld71 *topic);

uint32_t HelloWorld71_topic_max_size(uint32_t size);
HelloWorld71 *HelloWorld71_create(void);

void HelloWorld71_delete(HelloWorld71 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld72
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD72_SIZE		12


typedef struct HelloWorld72 {
	uint32_t index;
	int32_t message;
} HelloWorld72;


void HelloWorld72_init(HelloWorld72 *sample);


bool HelloWorld72_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld72 *topic);

bool HelloWorld72_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld72 *topic);

uint32_t HelloWorld72_topic_max_size(uint32_t size);
HelloWorld72 *HelloWorld72_create(void);

void HelloWorld72_delete(HelloWorld72 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld73
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD73_SIZE		12


typedef struct HelloWorld73 {
	uint32_t index;
	int32_t message;
} HelloWorld73;


void HelloWorld73_init(HelloWorld73 *sample);


bool HelloWorld73_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld73 *topic);

bool HelloWorld73_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld73 *topic);

uint32_t HelloWorld73_topic_max_size(uint32_t size);
HelloWorld73 *HelloWorld73_create(void);

void HelloWorld73_delete(HelloWorld73 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld74
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD74_SIZE		12


typedef struct HelloWorld74 {
	uint32_t index;
	int32_t message;
} HelloWorld74;


void HelloWorld74_init(HelloWorld74 *sample);


bool HelloWorld74_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld74 *topic);

bool HelloWorld74_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld74 *topic);

uint32_t HelloWorld74_topic_max_size(uint32_t size);
HelloWorld74 *HelloWorld74_create(void);

void HelloWorld74_delete(HelloWorld74 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld75
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD75_SIZE		12


typedef struct HelloWorld75 {
	uint32_t index;
	int32_t message;
} HelloWorld75;


void HelloWorld75_init(HelloWorld75 *sample);


bool HelloWorld75_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld75 *topic);

bool HelloWorld75_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld75 *topic);

uint32_t HelloWorld75_topic_max_size(uint32_t size);
HelloWorld75 *HelloWorld75_create(void);

void HelloWorld75_delete(HelloWorld75 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld76
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD76_SIZE		12


typedef struct HelloWorld76 {
	uint32_t index;
	int32_t message;
} HelloWorld76;


void HelloWorld76_init(HelloWorld76 *sample);


bool HelloWorld76_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld76 *topic);

bool HelloWorld76_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld76 *topic);

uint32_t HelloWorld76_topic_max_size(uint32_t size);
HelloWorld76 *HelloWorld76_create(void);

void HelloWorld76_delete(HelloWorld76 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld77
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD77_SIZE		12


typedef struct HelloWorld77 {
	uint32_t index;
	int32_t message;
} HelloWorld77;


void HelloWorld77_init(HelloWorld77 *sample);


bool HelloWorld77_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld77 *topic);

bool HelloWorld77_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld77 *topic);

uint32_t HelloWorld77_topic_max_size(uint32_t size);
HelloWorld77 *HelloWorld77_create(void);

void HelloWorld77_delete(HelloWorld77 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld78
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD78_SIZE		12


typedef struct HelloWorld78 {
	uint32_t index;
	int32_t message;
} HelloWorld78;


void HelloWorld78_init(HelloWorld78 *sample);


bool HelloWorld78_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld78 *topic);

bool HelloWorld78_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld78 *topic);

uint32_t HelloWorld78_topic_max_size(uint32_t size);
HelloWorld78 *HelloWorld78_create(void);

void HelloWorld78_delete(HelloWorld78 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld79
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD79_SIZE		12


typedef struct HelloWorld79 {
	uint32_t index;
	int32_t message;
} HelloWorld79;


void HelloWorld79_init(HelloWorld79 *sample);


bool HelloWorld79_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld79 *topic);

bool HelloWorld79_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld79 *topic);

uint32_t HelloWorld79_topic_max_size(uint32_t size);
HelloWorld79 *HelloWorld79_create(void);

void HelloWorld79_delete(HelloWorld79 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld80
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD80_SIZE		12


typedef struct HelloWorld80 {
	uint32_t index;
	int32_t message;
} HelloWorld80;


void HelloWorld80_init(HelloWorld80 *sample);


bool HelloWorld80_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld80 *topic);

bool HelloWorld80_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld80 *topic);

uint32_t HelloWorld80_topic_max_size(uint32_t size);
HelloWorld80 *HelloWorld80_create(void);

void HelloWorld80_delete(HelloWorld80 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld81
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD81_SIZE		12


typedef struct HelloWorld81 {
	uint32_t index;
	int32_t message;
} HelloWorld81;


void HelloWorld81_init(HelloWorld81 *sample);


bool HelloWorld81_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld81 *topic);

bool HelloWorld81_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld81 *topic);

uint32_t HelloWorld81_topic_max_size(uint32_t size);
HelloWorld81 *HelloWorld81_create(void);

void HelloWorld81_delete(HelloWorld81 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld82
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD82_SIZE		12


typedef struct HelloWorld82 {
	uint32_t index;
	int32_t message;
} HelloWorld82;


void HelloWorld82_init(HelloWorld82 *sample);


bool HelloWorld82_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld82 *topic);

bool HelloWorld82_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld82 *topic);

uint32_t HelloWorld82_topic_max_size(uint32_t size);
HelloWorld82 *HelloWorld82_create(void);

void HelloWorld82_delete(HelloWorld82 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld83
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD83_SIZE		12


typedef struct HelloWorld83 {
	uint32_t index;
	int32_t message;
} HelloWorld83;


void HelloWorld83_init(HelloWorld83 *sample);


bool HelloWorld83_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld83 *topic);

bool HelloWorld83_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld83 *topic);

uint32_t HelloWorld83_topic_max_size(uint32_t size);
HelloWorld83 *HelloWorld83_create(void);

void HelloWorld83_delete(HelloWorld83 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld84
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD84_SIZE		12


typedef struct HelloWorld84 {
	uint32_t index;
	int32_t message;
} HelloWorld84;


void HelloWorld84_init(HelloWorld84 *sample);


bool HelloWorld84_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld84 *topic);

bool HelloWorld84_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld84 *topic);

uint32_t HelloWorld84_topic_max_size(uint32_t size);
HelloWorld84 *HelloWorld84_create(void);

void HelloWorld84_delete(HelloWorld84 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld85
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD85_SIZE		12


typedef struct HelloWorld85 {
	uint32_t index;
	int32_t message;
} HelloWorld85;


void HelloWorld85_init(HelloWorld85 *sample);


bool HelloWorld85_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld85 *topic);

bool HelloWorld85_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld85 *topic);

uint32_t HelloWorld85_topic_max_size(uint32_t size);
HelloWorld85 *HelloWorld85_create(void);

void HelloWorld85_delete(HelloWorld85 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld86
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD86_SIZE		12


typedef struct HelloWorld86 {
	uint32_t index;
	int32_t message;
} HelloWorld86;


void HelloWorld86_init(HelloWorld86 *sample);


bool HelloWorld86_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld86 *topic);

bool HelloWorld86_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld86 *topic);

uint32_t HelloWorld86_topic_max_size(uint32_t size);
HelloWorld86 *HelloWorld86_create(void);

void HelloWorld86_delete(HelloWorld86 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld87
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD87_SIZE		12


typedef struct HelloWorld87 {
	uint32_t index;
	int32_t message;
} HelloWorld87;


void HelloWorld87_init(HelloWorld87 *sample);


bool HelloWorld87_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld87 *topic);

bool HelloWorld87_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld87 *topic);

uint32_t HelloWorld87_topic_max_size(uint32_t size);
HelloWorld87 *HelloWorld87_create(void);

void HelloWorld87_delete(HelloWorld87 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld88
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD88_SIZE		12


typedef struct HelloWorld88 {
	uint32_t index;
	int32_t message;
} HelloWorld88;


void HelloWorld88_init(HelloWorld88 *sample);


bool HelloWorld88_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld88 *topic);

bool HelloWorld88_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld88 *topic);

uint32_t HelloWorld88_topic_max_size(uint32_t size);
HelloWorld88 *HelloWorld88_create(void);

void HelloWorld88_delete(HelloWorld88 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld89
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD89_SIZE		12


typedef struct HelloWorld89 {
	uint32_t index;
	int32_t message;
} HelloWorld89;


void HelloWorld89_init(HelloWorld89 *sample);


bool HelloWorld89_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld89 *topic);

bool HelloWorld89_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld89 *topic);

uint32_t HelloWorld89_topic_max_size(uint32_t size);
HelloWorld89 *HelloWorld89_create(void);

void HelloWorld89_delete(HelloWorld89 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld90
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD90_SIZE		12


typedef struct HelloWorld90 {
	uint32_t index;
	int32_t message;
} HelloWorld90;


void HelloWorld90_init(HelloWorld90 *sample);


bool HelloWorld90_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld90 *topic);

bool HelloWorld90_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld90 *topic);

uint32_t HelloWorld90_topic_max_size(uint32_t size);
HelloWorld90 *HelloWorld90_create(void);

void HelloWorld90_delete(HelloWorld90 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld91
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD91_SIZE		12


typedef struct HelloWorld91 {
	uint32_t index;
	int32_t message;
} HelloWorld91;


void HelloWorld91_init(HelloWorld91 *sample);


bool HelloWorld91_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld91 *topic);

bool HelloWorld91_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld91 *topic);

uint32_t HelloWorld91_topic_max_size(uint32_t size);
HelloWorld91 *HelloWorld91_create(void);

void HelloWorld91_delete(HelloWorld91 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld92
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD92_SIZE		12


typedef struct HelloWorld92 {
	uint32_t index;
	int32_t message;
} HelloWorld92;


void HelloWorld92_init(HelloWorld92 *sample);


bool HelloWorld92_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld92 *topic);

bool HelloWorld92_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld92 *topic);

uint32_t HelloWorld92_topic_max_size(uint32_t size);
HelloWorld92 *HelloWorld92_create(void);

void HelloWorld92_delete(HelloWorld92 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld93
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD93_SIZE		12


typedef struct HelloWorld93 {
	uint32_t index;
	int32_t message;
} HelloWorld93;


void HelloWorld93_init(HelloWorld93 *sample);


bool HelloWorld93_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld93 *topic);

bool HelloWorld93_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld93 *topic);

uint32_t HelloWorld93_topic_max_size(uint32_t size);
HelloWorld93 *HelloWorld93_create(void);

void HelloWorld93_delete(HelloWorld93 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld94
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD94_SIZE		12


typedef struct HelloWorld94 {
	uint32_t index;
	int32_t message;
} HelloWorld94;


void HelloWorld94_init(HelloWorld94 *sample);


bool HelloWorld94_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld94 *topic);

bool HelloWorld94_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld94 *topic);

uint32_t HelloWorld94_topic_max_size(uint32_t size);
HelloWorld94 *HelloWorld94_create(void);

void HelloWorld94_delete(HelloWorld94 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld95
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD95_SIZE		12


typedef struct HelloWorld95 {
	uint32_t index;
	int32_t message;
} HelloWorld95;


void HelloWorld95_init(HelloWorld95 *sample);


bool HelloWorld95_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld95 *topic);

bool HelloWorld95_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld95 *topic);

uint32_t HelloWorld95_topic_max_size(uint32_t size);
HelloWorld95 *HelloWorld95_create(void);

void HelloWorld95_delete(HelloWorld95 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld96
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD96_SIZE		12


typedef struct HelloWorld96 {
	uint32_t index;
	int32_t message;
} HelloWorld96;


void HelloWorld96_init(HelloWorld96 *sample);


bool HelloWorld96_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld96 *topic);

bool HelloWorld96_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld96 *topic);

uint32_t HelloWorld96_topic_max_size(uint32_t size);
HelloWorld96 *HelloWorld96_create(void);

void HelloWorld96_delete(HelloWorld96 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld97
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD97_SIZE		12


typedef struct HelloWorld97 {
	uint32_t index;
	int32_t message;
} HelloWorld97;


void HelloWorld97_init(HelloWorld97 *sample);


bool HelloWorld97_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld97 *topic);

bool HelloWorld97_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld97 *topic);

uint32_t HelloWorld97_topic_max_size(uint32_t size);
HelloWorld97 *HelloWorld97_create(void);

void HelloWorld97_delete(HelloWorld97 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld98
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD98_SIZE		12


typedef struct HelloWorld98 {
	uint32_t index;
	int32_t message;
} HelloWorld98;


void HelloWorld98_init(HelloWorld98 *sample);


bool HelloWorld98_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld98 *topic);

bool HelloWorld98_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld98 *topic);

uint32_t HelloWorld98_topic_max_size(uint32_t size);
HelloWorld98 *HelloWorld98_create(void);

void HelloWorld98_delete(HelloWorld98 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld99
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD99_SIZE		12


typedef struct HelloWorld99 {
	uint32_t index;
	int32_t message;
} HelloWorld99;


void HelloWorld99_init(HelloWorld99 *sample);


bool HelloWorld99_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld99 *topic);

bool HelloWorld99_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld99 *topic);

uint32_t HelloWorld99_topic_max_size(uint32_t size);
HelloWorld99 *HelloWorld99_create(void);

void HelloWorld99_delete(HelloWorld99 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld100
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD100_SIZE		12


typedef struct HelloWorld100 {
	uint32_t index;
	int32_t message;
} HelloWorld100;


void HelloWorld100_init(HelloWorld100 *sample);


bool HelloWorld100_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld100 *topic);

bool HelloWorld100_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld100 *topic);

uint32_t HelloWorld100_topic_max_size(uint32_t size);
HelloWorld100 *HelloWorld100_create(void);

void HelloWorld100_delete(HelloWorld100 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld101
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD101_SIZE		12


typedef struct HelloWorld101 {
	uint32_t index;
	int32_t message;
} HelloWorld101;


void HelloWorld101_init(HelloWorld101 *sample);


bool HelloWorld101_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld101 *topic);

bool HelloWorld101_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld101 *topic);

uint32_t HelloWorld101_topic_max_size(uint32_t size);
HelloWorld101 *HelloWorld101_create(void);

void HelloWorld101_delete(HelloWorld101 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld102
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD102_SIZE		12


typedef struct HelloWorld102 {
	uint32_t index;
	int32_t message;
} HelloWorld102;


void HelloWorld102_init(HelloWorld102 *sample);


bool HelloWorld102_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld102 *topic);

bool HelloWorld102_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld102 *topic);

uint32_t HelloWorld102_topic_max_size(uint32_t size);
HelloWorld102 *HelloWorld102_create(void);

void HelloWorld102_delete(HelloWorld102 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld103
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD103_SIZE		12


typedef struct HelloWorld103 {
	uint32_t index;
	int32_t message;
} HelloWorld103;


void HelloWorld103_init(HelloWorld103 *sample);


bool HelloWorld103_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld103 *topic);

bool HelloWorld103_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld103 *topic);

uint32_t HelloWorld103_topic_max_size(uint32_t size);
HelloWorld103 *HelloWorld103_create(void);

void HelloWorld103_delete(HelloWorld103 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld104
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD104_SIZE		12


typedef struct HelloWorld104 {
	uint32_t index;
	int32_t message;
} HelloWorld104;


void HelloWorld104_init(HelloWorld104 *sample);


bool HelloWorld104_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld104 *topic);

bool HelloWorld104_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld104 *topic);

uint32_t HelloWorld104_topic_max_size(uint32_t size);
HelloWorld104 *HelloWorld104_create(void);

void HelloWorld104_delete(HelloWorld104 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld105
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD105_SIZE		12


typedef struct HelloWorld105 {
	uint32_t index;
	int32_t message;
} HelloWorld105;


void HelloWorld105_init(HelloWorld105 *sample);


bool HelloWorld105_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld105 *topic);

bool HelloWorld105_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld105 *topic);

uint32_t HelloWorld105_topic_max_size(uint32_t size);
HelloWorld105 *HelloWorld105_create(void);

void HelloWorld105_delete(HelloWorld105 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld106
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD106_SIZE		12


typedef struct HelloWorld106 {
	uint32_t index;
	int32_t message;
} HelloWorld106;


void HelloWorld106_init(HelloWorld106 *sample);


bool HelloWorld106_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld106 *topic);

bool HelloWorld106_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld106 *topic);

uint32_t HelloWorld106_topic_max_size(uint32_t size);
HelloWorld106 *HelloWorld106_create(void);

void HelloWorld106_delete(HelloWorld106 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld107
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD107_SIZE		12


typedef struct HelloWorld107 {
	uint32_t index;
	int32_t message;
} HelloWorld107;


void HelloWorld107_init(HelloWorld107 *sample);


bool HelloWorld107_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld107 *topic);

bool HelloWorld107_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld107 *topic);

uint32_t HelloWorld107_topic_max_size(uint32_t size);
HelloWorld107 *HelloWorld107_create(void);

void HelloWorld107_delete(HelloWorld107 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld108
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD108_SIZE		12


typedef struct HelloWorld108 {
	uint32_t index;
	int32_t message;
} HelloWorld108;


void HelloWorld108_init(HelloWorld108 *sample);


bool HelloWorld108_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld108 *topic);

bool HelloWorld108_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld108 *topic);

uint32_t HelloWorld108_topic_max_size(uint32_t size);
HelloWorld108 *HelloWorld108_create(void);

void HelloWorld108_delete(HelloWorld108 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld109
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD109_SIZE		12


typedef struct HelloWorld109 {
	uint32_t index;
	int32_t message;
} HelloWorld109;


void HelloWorld109_init(HelloWorld109 *sample);


bool HelloWorld109_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld109 *topic);

bool HelloWorld109_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld109 *topic);

uint32_t HelloWorld109_topic_max_size(uint32_t size);
HelloWorld109 *HelloWorld109_create(void);

void HelloWorld109_delete(HelloWorld109 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld110
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD110_SIZE		12


typedef struct HelloWorld110 {
	uint32_t index;
	int32_t message;
} HelloWorld110;


void HelloWorld110_init(HelloWorld110 *sample);


bool HelloWorld110_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld110 *topic);

bool HelloWorld110_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld110 *topic);

uint32_t HelloWorld110_topic_max_size(uint32_t size);
HelloWorld110 *HelloWorld110_create(void);

void HelloWorld110_delete(HelloWorld110 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld111
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD111_SIZE		12


typedef struct HelloWorld111 {
	uint32_t index;
	int32_t message;
} HelloWorld111;


void HelloWorld111_init(HelloWorld111 *sample);


bool HelloWorld111_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld111 *topic);

bool HelloWorld111_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld111 *topic);

uint32_t HelloWorld111_topic_max_size(uint32_t size);
HelloWorld111 *HelloWorld111_create(void);

void HelloWorld111_delete(HelloWorld111 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld112
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD112_SIZE		12


typedef struct HelloWorld112 {
	uint32_t index;
	int32_t message;
} HelloWorld112;


void HelloWorld112_init(HelloWorld112 *sample);


bool HelloWorld112_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld112 *topic);

bool HelloWorld112_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld112 *topic);

uint32_t HelloWorld112_topic_max_size(uint32_t size);
HelloWorld112 *HelloWorld112_create(void);

void HelloWorld112_delete(HelloWorld112 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld113
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD113_SIZE		12


typedef struct HelloWorld113 {
	uint32_t index;
	int32_t message;
} HelloWorld113;


void HelloWorld113_init(HelloWorld113 *sample);


bool HelloWorld113_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld113 *topic);

bool HelloWorld113_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld113 *topic);

uint32_t HelloWorld113_topic_max_size(uint32_t size);
HelloWorld113 *HelloWorld113_create(void);

void HelloWorld113_delete(HelloWorld113 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld114
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD114_SIZE		12


typedef struct HelloWorld114 {
	uint32_t index;
	int32_t message;
} HelloWorld114;


void HelloWorld114_init(HelloWorld114 *sample);


bool HelloWorld114_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld114 *topic);

bool HelloWorld114_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld114 *topic);

uint32_t HelloWorld114_topic_max_size(uint32_t size);
HelloWorld114 *HelloWorld114_create(void);

void HelloWorld114_delete(HelloWorld114 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld115
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD115_SIZE		12


typedef struct HelloWorld115 {
	uint32_t index;
	int32_t message;
} HelloWorld115;


void HelloWorld115_init(HelloWorld115 *sample);


bool HelloWorld115_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld115 *topic);

bool HelloWorld115_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld115 *topic);

uint32_t HelloWorld115_topic_max_size(uint32_t size);
HelloWorld115 *HelloWorld115_create(void);

void HelloWorld115_delete(HelloWorld115 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld116
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD116_SIZE		12


typedef struct HelloWorld116 {
	uint32_t index;
	int32_t message;
} HelloWorld116;


void HelloWorld116_init(HelloWorld116 *sample);


bool HelloWorld116_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld116 *topic);

bool HelloWorld116_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld116 *topic);

uint32_t HelloWorld116_topic_max_size(uint32_t size);
HelloWorld116 *HelloWorld116_create(void);

void HelloWorld116_delete(HelloWorld116 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld117
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD117_SIZE		12


typedef struct HelloWorld117 {
	uint32_t index;
	int32_t message;
} HelloWorld117;


void HelloWorld117_init(HelloWorld117 *sample);


bool HelloWorld117_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld117 *topic);

bool HelloWorld117_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld117 *topic);

uint32_t HelloWorld117_topic_max_size(uint32_t size);
HelloWorld117 *HelloWorld117_create(void);

void HelloWorld117_delete(HelloWorld117 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld118
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD118_SIZE		12


typedef struct HelloWorld118 {
	uint32_t index;
	int32_t message;
} HelloWorld118;


void HelloWorld118_init(HelloWorld118 *sample);


bool HelloWorld118_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld118 *topic);

bool HelloWorld118_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld118 *topic);

uint32_t HelloWorld118_topic_max_size(uint32_t size);
HelloWorld118 *HelloWorld118_create(void);

void HelloWorld118_delete(HelloWorld118 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld119
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD119_SIZE		12


typedef struct HelloWorld119 {
	uint32_t index;
	int32_t message;
} HelloWorld119;


void HelloWorld119_init(HelloWorld119 *sample);


bool HelloWorld119_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld119 *topic);

bool HelloWorld119_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld119 *topic);

uint32_t HelloWorld119_topic_max_size(uint32_t size);
HelloWorld119 *HelloWorld119_create(void);

void HelloWorld119_delete(HelloWorld119 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld120
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD120_SIZE		12


typedef struct HelloWorld120 {
	uint32_t index;
	int32_t message;
} HelloWorld120;


void HelloWorld120_init(HelloWorld120 *sample);


bool HelloWorld120_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld120 *topic);

bool HelloWorld120_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld120 *topic);

uint32_t HelloWorld120_topic_max_size(uint32_t size);
HelloWorld120 *HelloWorld120_create(void);

void HelloWorld120_delete(HelloWorld120 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld121
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD121_SIZE		12


typedef struct HelloWorld121 {
	uint32_t index;
	int32_t message;
} HelloWorld121;


void HelloWorld121_init(HelloWorld121 *sample);


bool HelloWorld121_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld121 *topic);

bool HelloWorld121_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld121 *topic);

uint32_t HelloWorld121_topic_max_size(uint32_t size);
HelloWorld121 *HelloWorld121_create(void);

void HelloWorld121_delete(HelloWorld121 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld122
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD122_SIZE		12


typedef struct HelloWorld122 {
	uint32_t index;
	int32_t message;
} HelloWorld122;


void HelloWorld122_init(HelloWorld122 *sample);


bool HelloWorld122_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld122 *topic);

bool HelloWorld122_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld122 *topic);

uint32_t HelloWorld122_topic_max_size(uint32_t size);
HelloWorld122 *HelloWorld122_create(void);

void HelloWorld122_delete(HelloWorld122 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld123
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD123_SIZE		12


typedef struct HelloWorld123 {
	uint32_t index;
	int32_t message;
} HelloWorld123;


void HelloWorld123_init(HelloWorld123 *sample);


bool HelloWorld123_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld123 *topic);

bool HelloWorld123_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld123 *topic);

uint32_t HelloWorld123_topic_max_size(uint32_t size);
HelloWorld123 *HelloWorld123_create(void);

void HelloWorld123_delete(HelloWorld123 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld124
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD124_SIZE		12


typedef struct HelloWorld124 {
	uint32_t index;
	int32_t message;
} HelloWorld124;


void HelloWorld124_init(HelloWorld124 *sample);


bool HelloWorld124_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld124 *topic);

bool HelloWorld124_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld124 *topic);

uint32_t HelloWorld124_topic_max_size(uint32_t size);
HelloWorld124 *HelloWorld124_create(void);

void HelloWorld124_delete(HelloWorld124 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld125
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD125_SIZE		12


typedef struct HelloWorld125 {
	uint32_t index;
	int32_t message;
} HelloWorld125;


void HelloWorld125_init(HelloWorld125 *sample);


bool HelloWorld125_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld125 *topic);

bool HelloWorld125_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld125 *topic);

uint32_t HelloWorld125_topic_max_size(uint32_t size);
HelloWorld125 *HelloWorld125_create(void);

void HelloWorld125_delete(HelloWorld125 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld126
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD126_SIZE		12


typedef struct HelloWorld126 {
	uint32_t index;
	int32_t message;
} HelloWorld126;


void HelloWorld126_init(HelloWorld126 *sample);


bool HelloWorld126_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld126 *topic);

bool HelloWorld126_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld126 *topic);

uint32_t HelloWorld126_topic_max_size(uint32_t size);
HelloWorld126 *HelloWorld126_create(void);

void HelloWorld126_delete(HelloWorld126 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld127
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD127_SIZE		12


typedef struct HelloWorld127 {
	uint32_t index;
	int32_t message;
} HelloWorld127;


void HelloWorld127_init(HelloWorld127 *sample);


bool HelloWorld127_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld127 *topic);

bool HelloWorld127_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld127 *topic);

uint32_t HelloWorld127_topic_max_size(uint32_t size);
HelloWorld127 *HelloWorld127_create(void);

void HelloWorld127_delete(HelloWorld127 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld128
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD128_SIZE		12


typedef struct HelloWorld128 {
	uint32_t index;
	int32_t message;
} HelloWorld128;


void HelloWorld128_init(HelloWorld128 *sample);


bool HelloWorld128_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld128 *topic);

bool HelloWorld128_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld128 *topic);

uint32_t HelloWorld128_topic_max_size(uint32_t size);
HelloWorld128 *HelloWorld128_create(void);

void HelloWorld128_delete(HelloWorld128 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld129
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD129_SIZE		12


typedef struct HelloWorld129 {
	uint32_t index;
	int32_t message;
} HelloWorld129;


void HelloWorld129_init(HelloWorld129 *sample);


bool HelloWorld129_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld129 *topic);

bool HelloWorld129_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld129 *topic);

uint32_t HelloWorld129_topic_max_size(uint32_t size);
HelloWorld129 *HelloWorld129_create(void);

void HelloWorld129_delete(HelloWorld129 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld130
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD130_SIZE		12


typedef struct HelloWorld130 {
	uint32_t index;
	int32_t message;
} HelloWorld130;


void HelloWorld130_init(HelloWorld130 *sample);


bool HelloWorld130_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld130 *topic);

bool HelloWorld130_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld130 *topic);

uint32_t HelloWorld130_topic_max_size(uint32_t size);
HelloWorld130 *HelloWorld130_create(void);

void HelloWorld130_delete(HelloWorld130 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld131
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD131_SIZE		12


typedef struct HelloWorld131 {
	uint32_t index;
	int32_t message;
} HelloWorld131;


void HelloWorld131_init(HelloWorld131 *sample);


bool HelloWorld131_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld131 *topic);

bool HelloWorld131_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld131 *topic);

uint32_t HelloWorld131_topic_max_size(uint32_t size);
HelloWorld131 *HelloWorld131_create(void);

void HelloWorld131_delete(HelloWorld131 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld132
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD132_SIZE		12


typedef struct HelloWorld132 {
	uint32_t index;
	int32_t message;
} HelloWorld132;


void HelloWorld132_init(HelloWorld132 *sample);


bool HelloWorld132_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld132 *topic);

bool HelloWorld132_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld132 *topic);

uint32_t HelloWorld132_topic_max_size(uint32_t size);
HelloWorld132 *HelloWorld132_create(void);

void HelloWorld132_delete(HelloWorld132 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld133
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD133_SIZE		12


typedef struct HelloWorld133 {
	uint32_t index;
	int32_t message;
} HelloWorld133;


void HelloWorld133_init(HelloWorld133 *sample);


bool HelloWorld133_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld133 *topic);

bool HelloWorld133_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld133 *topic);

uint32_t HelloWorld133_topic_max_size(uint32_t size);
HelloWorld133 *HelloWorld133_create(void);

void HelloWorld133_delete(HelloWorld133 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld134
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD134_SIZE		12


typedef struct HelloWorld134 {
	uint32_t index;
	int32_t message;
} HelloWorld134;


void HelloWorld134_init(HelloWorld134 *sample);


bool HelloWorld134_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld134 *topic);

bool HelloWorld134_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld134 *topic);

uint32_t HelloWorld134_topic_max_size(uint32_t size);
HelloWorld134 *HelloWorld134_create(void);

void HelloWorld134_delete(HelloWorld134 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld135
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD135_SIZE		12


typedef struct HelloWorld135 {
	uint32_t index;
	int32_t message;
} HelloWorld135;


void HelloWorld135_init(HelloWorld135 *sample);


bool HelloWorld135_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld135 *topic);

bool HelloWorld135_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld135 *topic);

uint32_t HelloWorld135_topic_max_size(uint32_t size);
HelloWorld135 *HelloWorld135_create(void);

void HelloWorld135_delete(HelloWorld135 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld136
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD136_SIZE		12


typedef struct HelloWorld136 {
	uint32_t index;
	int32_t message;
} HelloWorld136;


void HelloWorld136_init(HelloWorld136 *sample);


bool HelloWorld136_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld136 *topic);

bool HelloWorld136_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld136 *topic);

uint32_t HelloWorld136_topic_max_size(uint32_t size);
HelloWorld136 *HelloWorld136_create(void);

void HelloWorld136_delete(HelloWorld136 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld137
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD137_SIZE		12


typedef struct HelloWorld137 {
	uint32_t index;
	int32_t message;
} HelloWorld137;


void HelloWorld137_init(HelloWorld137 *sample);


bool HelloWorld137_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld137 *topic);

bool HelloWorld137_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld137 *topic);

uint32_t HelloWorld137_topic_max_size(uint32_t size);
HelloWorld137 *HelloWorld137_create(void);

void HelloWorld137_delete(HelloWorld137 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld138
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD138_SIZE		12


typedef struct HelloWorld138 {
	uint32_t index;
	int32_t message;
} HelloWorld138;


void HelloWorld138_init(HelloWorld138 *sample);


bool HelloWorld138_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld138 *topic);

bool HelloWorld138_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld138 *topic);

uint32_t HelloWorld138_topic_max_size(uint32_t size);
HelloWorld138 *HelloWorld138_create(void);

void HelloWorld138_delete(HelloWorld138 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld139
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD139_SIZE		12


typedef struct HelloWorld139 {
	uint32_t index;
	int32_t message;
} HelloWorld139;


void HelloWorld139_init(HelloWorld139 *sample);


bool HelloWorld139_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld139 *topic);

bool HelloWorld139_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld139 *topic);

uint32_t HelloWorld139_topic_max_size(uint32_t size);
HelloWorld139 *HelloWorld139_create(void);

void HelloWorld139_delete(HelloWorld139 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld140
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD140_SIZE		12


typedef struct HelloWorld140 {
	uint32_t index;
	int32_t message;
} HelloWorld140;


void HelloWorld140_init(HelloWorld140 *sample);


bool HelloWorld140_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld140 *topic);

bool HelloWorld140_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld140 *topic);

uint32_t HelloWorld140_topic_max_size(uint32_t size);
HelloWorld140 *HelloWorld140_create(void);

void HelloWorld140_delete(HelloWorld140 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld141
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD141_SIZE		12


typedef struct HelloWorld141 {
	uint32_t index;
	int32_t message;
} HelloWorld141;


void HelloWorld141_init(HelloWorld141 *sample);


bool HelloWorld141_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld141 *topic);

bool HelloWorld141_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld141 *topic);

uint32_t HelloWorld141_topic_max_size(uint32_t size);
HelloWorld141 *HelloWorld141_create(void);

void HelloWorld141_delete(HelloWorld141 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld142
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD142_SIZE		12


typedef struct HelloWorld142 {
	uint32_t index;
	int32_t message;
} HelloWorld142;


void HelloWorld142_init(HelloWorld142 *sample);


bool HelloWorld142_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld142 *topic);

bool HelloWorld142_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld142 *topic);

uint32_t HelloWorld142_topic_max_size(uint32_t size);
HelloWorld142 *HelloWorld142_create(void);

void HelloWorld142_delete(HelloWorld142 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld143
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD143_SIZE		12


typedef struct HelloWorld143 {
	uint32_t index;
	int32_t message;
} HelloWorld143;


void HelloWorld143_init(HelloWorld143 *sample);


bool HelloWorld143_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld143 *topic);

bool HelloWorld143_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld143 *topic);

uint32_t HelloWorld143_topic_max_size(uint32_t size);
HelloWorld143 *HelloWorld143_create(void);

void HelloWorld143_delete(HelloWorld143 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld144
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD144_SIZE		12


typedef struct HelloWorld144 {
	uint32_t index;
	int32_t message;
} HelloWorld144;


void HelloWorld144_init(HelloWorld144 *sample);


bool HelloWorld144_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld144 *topic);

bool HelloWorld144_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld144 *topic);

uint32_t HelloWorld144_topic_max_size(uint32_t size);
HelloWorld144 *HelloWorld144_create(void);

void HelloWorld144_delete(HelloWorld144 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld145
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD145_SIZE		12


typedef struct HelloWorld145 {
	uint32_t index;
	int32_t message;
} HelloWorld145;


void HelloWorld145_init(HelloWorld145 *sample);


bool HelloWorld145_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld145 *topic);

bool HelloWorld145_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld145 *topic);

uint32_t HelloWorld145_topic_max_size(uint32_t size);
HelloWorld145 *HelloWorld145_create(void);

void HelloWorld145_delete(HelloWorld145 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld146
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD146_SIZE		12


typedef struct HelloWorld146 {
	uint32_t index;
	int32_t message;
} HelloWorld146;


void HelloWorld146_init(HelloWorld146 *sample);


bool HelloWorld146_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld146 *topic);

bool HelloWorld146_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld146 *topic);

uint32_t HelloWorld146_topic_max_size(uint32_t size);
HelloWorld146 *HelloWorld146_create(void);

void HelloWorld146_delete(HelloWorld146 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld147
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD147_SIZE		12


typedef struct HelloWorld147 {
	uint32_t index;
	int32_t message;
} HelloWorld147;


void HelloWorld147_init(HelloWorld147 *sample);


bool HelloWorld147_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld147 *topic);

bool HelloWorld147_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld147 *topic);

uint32_t HelloWorld147_topic_max_size(uint32_t size);
HelloWorld147 *HelloWorld147_create(void);

void HelloWorld147_delete(HelloWorld147 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld148
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD148_SIZE		520


typedef struct HelloWorld148 {
	uint32_t index;
	int32_t message;
	char str_msg[500 + 1];
} HelloWorld148;


void HelloWorld148_init(HelloWorld148 *sample);


bool HelloWorld148_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld148 *topic);

bool HelloWorld148_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld148 *topic);

uint32_t HelloWorld148_topic_max_size(uint32_t size);
HelloWorld148 *HelloWorld148_create(void);

void HelloWorld148_delete(HelloWorld148 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld149
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD149_SIZE		1020


typedef struct HelloWorld149 {
	uint32_t index;
	int32_t message;
	char str_msg[1000 + 1];
} HelloWorld149;


void HelloWorld149_init(HelloWorld149 *sample);


bool HelloWorld149_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld149 *topic);

bool HelloWorld149_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld149 *topic);

uint32_t HelloWorld149_topic_max_size(uint32_t size);
HelloWorld149 *HelloWorld149_create(void);

void HelloWorld149_delete(HelloWorld149 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld151
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD151_SIZE		12


typedef struct HelloWorld151 {
	uint32_t index;
	int32_t message;
} HelloWorld151;


void HelloWorld151_init(HelloWorld151 *sample);


bool HelloWorld151_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld151 *topic);

bool HelloWorld151_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld151 *topic);

uint32_t HelloWorld151_topic_max_size(uint32_t size);
HelloWorld151 *HelloWorld151_create(void);

void HelloWorld151_delete(HelloWorld151 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld152
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD152_SIZE		12


typedef struct HelloWorld152 {
	uint32_t index;
	int32_t message;
} HelloWorld152;


void HelloWorld152_init(HelloWorld152 *sample);


bool HelloWorld152_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld152 *topic);

bool HelloWorld152_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld152 *topic);

uint32_t HelloWorld152_topic_max_size(uint32_t size);
HelloWorld152 *HelloWorld152_create(void);

void HelloWorld152_delete(HelloWorld152 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld153
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD153_SIZE		12


typedef struct HelloWorld153 {
	uint32_t index;
	int32_t message;
} HelloWorld153;


void HelloWorld153_init(HelloWorld153 *sample);


bool HelloWorld153_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld153 *topic);

bool HelloWorld153_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld153 *topic);

uint32_t HelloWorld153_topic_max_size(uint32_t size);
HelloWorld153 *HelloWorld153_create(void);

void HelloWorld153_delete(HelloWorld153 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld154
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD154_SIZE		12


typedef struct HelloWorld154 {
	uint32_t index;
	int32_t message;
} HelloWorld154;


void HelloWorld154_init(HelloWorld154 *sample);


bool HelloWorld154_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld154 *topic);

bool HelloWorld154_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld154 *topic);

uint32_t HelloWorld154_topic_max_size(uint32_t size);
HelloWorld154 *HelloWorld154_create(void);

void HelloWorld154_delete(HelloWorld154 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld155
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD155_SIZE		12


typedef struct HelloWorld155 {
	uint32_t index;
	int32_t message;
} HelloWorld155;


void HelloWorld155_init(HelloWorld155 *sample);


bool HelloWorld155_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld155 *topic);

bool HelloWorld155_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld155 *topic);

uint32_t HelloWorld155_topic_max_size(uint32_t size);
HelloWorld155 *HelloWorld155_create(void);

void HelloWorld155_delete(HelloWorld155 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld156
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD156_SIZE		12


typedef struct HelloWorld156 {
	uint32_t index;
	int32_t message;
} HelloWorld156;


void HelloWorld156_init(HelloWorld156 *sample);


bool HelloWorld156_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld156 *topic);

bool HelloWorld156_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld156 *topic);

uint32_t HelloWorld156_topic_max_size(uint32_t size);
HelloWorld156 *HelloWorld156_create(void);

void HelloWorld156_delete(HelloWorld156 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld157
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD157_SIZE		12


typedef struct HelloWorld157 {
	uint32_t index;
	int32_t message;
} HelloWorld157;


void HelloWorld157_init(HelloWorld157 *sample);


bool HelloWorld157_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld157 *topic);

bool HelloWorld157_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld157 *topic);

uint32_t HelloWorld157_topic_max_size(uint32_t size);
HelloWorld157 *HelloWorld157_create(void);

void HelloWorld157_delete(HelloWorld157 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld158
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD158_SIZE		12


typedef struct HelloWorld158 {
	uint32_t index;
	int32_t message;
} HelloWorld158;


void HelloWorld158_init(HelloWorld158 *sample);


bool HelloWorld158_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld158 *topic);

bool HelloWorld158_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld158 *topic);

uint32_t HelloWorld158_topic_max_size(uint32_t size);
HelloWorld158 *HelloWorld158_create(void);

void HelloWorld158_delete(HelloWorld158 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld159
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD159_SIZE		12


typedef struct HelloWorld159 {
	uint32_t index;
	int32_t message;
} HelloWorld159;


void HelloWorld159_init(HelloWorld159 *sample);


bool HelloWorld159_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld159 *topic);

bool HelloWorld159_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld159 *topic);

uint32_t HelloWorld159_topic_max_size(uint32_t size);
HelloWorld159 *HelloWorld159_create(void);

void HelloWorld159_delete(HelloWorld159 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld160
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD160_SIZE		12


typedef struct HelloWorld160 {
	uint32_t index;
	int32_t message;
} HelloWorld160;


void HelloWorld160_init(HelloWorld160 *sample);


bool HelloWorld160_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld160 *topic);

bool HelloWorld160_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld160 *topic);

uint32_t HelloWorld160_topic_max_size(uint32_t size);
HelloWorld160 *HelloWorld160_create(void);

void HelloWorld160_delete(HelloWorld160 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld161
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD161_SIZE		12


typedef struct HelloWorld161 {
	uint32_t index;
	int32_t message;
} HelloWorld161;


void HelloWorld161_init(HelloWorld161 *sample);


bool HelloWorld161_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld161 *topic);

bool HelloWorld161_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld161 *topic);

uint32_t HelloWorld161_topic_max_size(uint32_t size);
HelloWorld161 *HelloWorld161_create(void);

void HelloWorld161_delete(HelloWorld161 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld162
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD162_SIZE		12


typedef struct HelloWorld162 {
	uint32_t index;
	int32_t message;
} HelloWorld162;


void HelloWorld162_init(HelloWorld162 *sample);


bool HelloWorld162_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld162 *topic);

bool HelloWorld162_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld162 *topic);

uint32_t HelloWorld162_topic_max_size(uint32_t size);
HelloWorld162 *HelloWorld162_create(void);

void HelloWorld162_delete(HelloWorld162 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld163
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD163_SIZE		12


typedef struct HelloWorld163 {
	uint32_t index;
	int32_t message;
} HelloWorld163;


void HelloWorld163_init(HelloWorld163 *sample);


bool HelloWorld163_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld163 *topic);

bool HelloWorld163_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld163 *topic);

uint32_t HelloWorld163_topic_max_size(uint32_t size);
HelloWorld163 *HelloWorld163_create(void);

void HelloWorld163_delete(HelloWorld163 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld164
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD164_SIZE		12


typedef struct HelloWorld164 {
	uint32_t index;
	int32_t message;
} HelloWorld164;


void HelloWorld164_init(HelloWorld164 *sample);


bool HelloWorld164_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld164 *topic);

bool HelloWorld164_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld164 *topic);

uint32_t HelloWorld164_topic_max_size(uint32_t size);
HelloWorld164 *HelloWorld164_create(void);

void HelloWorld164_delete(HelloWorld164 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld165
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD165_SIZE		12


typedef struct HelloWorld165 {
	uint32_t index;
	int32_t message;
} HelloWorld165;


void HelloWorld165_init(HelloWorld165 *sample);


bool HelloWorld165_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld165 *topic);

bool HelloWorld165_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld165 *topic);

uint32_t HelloWorld165_topic_max_size(uint32_t size);
HelloWorld165 *HelloWorld165_create(void);

void HelloWorld165_delete(HelloWorld165 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld166
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD166_SIZE		12


typedef struct HelloWorld166 {
	uint32_t index;
	int32_t message;
} HelloWorld166;


void HelloWorld166_init(HelloWorld166 *sample);


bool HelloWorld166_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld166 *topic);

bool HelloWorld166_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld166 *topic);

uint32_t HelloWorld166_topic_max_size(uint32_t size);
HelloWorld166 *HelloWorld166_create(void);

void HelloWorld166_delete(HelloWorld166 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld167
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD167_SIZE		12


typedef struct HelloWorld167 {
	uint32_t index;
	int32_t message;
} HelloWorld167;


void HelloWorld167_init(HelloWorld167 *sample);


bool HelloWorld167_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld167 *topic);

bool HelloWorld167_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld167 *topic);

uint32_t HelloWorld167_topic_max_size(uint32_t size);
HelloWorld167 *HelloWorld167_create(void);

void HelloWorld167_delete(HelloWorld167 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld168
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD168_SIZE		12


typedef struct HelloWorld168 {
	uint32_t index;
	int32_t message;
} HelloWorld168;


void HelloWorld168_init(HelloWorld168 *sample);


bool HelloWorld168_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld168 *topic);

bool HelloWorld168_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld168 *topic);

uint32_t HelloWorld168_topic_max_size(uint32_t size);
HelloWorld168 *HelloWorld168_create(void);

void HelloWorld168_delete(HelloWorld168 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld169
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD169_SIZE		12


typedef struct HelloWorld169 {
	uint32_t index;
	int32_t message;
} HelloWorld169;


void HelloWorld169_init(HelloWorld169 *sample);


bool HelloWorld169_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld169 *topic);

bool HelloWorld169_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld169 *topic);

uint32_t HelloWorld169_topic_max_size(uint32_t size);
HelloWorld169 *HelloWorld169_create(void);

void HelloWorld169_delete(HelloWorld169 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld170
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD170_SIZE		12


typedef struct HelloWorld170 {
	uint32_t index;
	int32_t message;
} HelloWorld170;


void HelloWorld170_init(HelloWorld170 *sample);


bool HelloWorld170_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld170 *topic);

bool HelloWorld170_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld170 *topic);

uint32_t HelloWorld170_topic_max_size(uint32_t size);
HelloWorld170 *HelloWorld170_create(void);

void HelloWorld170_delete(HelloWorld170 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld171
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD171_SIZE		12


typedef struct HelloWorld171 {
	uint32_t index;
	int32_t message;
} HelloWorld171;


void HelloWorld171_init(HelloWorld171 *sample);


bool HelloWorld171_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld171 *topic);

bool HelloWorld171_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld171 *topic);

uint32_t HelloWorld171_topic_max_size(uint32_t size);
HelloWorld171 *HelloWorld171_create(void);

void HelloWorld171_delete(HelloWorld171 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld172
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD172_SIZE		12


typedef struct HelloWorld172 {
	uint32_t index;
	int32_t message;
} HelloWorld172;


void HelloWorld172_init(HelloWorld172 *sample);


bool HelloWorld172_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld172 *topic);

bool HelloWorld172_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld172 *topic);

uint32_t HelloWorld172_topic_max_size(uint32_t size);
HelloWorld172 *HelloWorld172_create(void);

void HelloWorld172_delete(HelloWorld172 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld173
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD173_SIZE		12


typedef struct HelloWorld173 {
	uint32_t index;
	int32_t message;
} HelloWorld173;


void HelloWorld173_init(HelloWorld173 *sample);


bool HelloWorld173_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld173 *topic);

bool HelloWorld173_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld173 *topic);

uint32_t HelloWorld173_topic_max_size(uint32_t size);
HelloWorld173 *HelloWorld173_create(void);

void HelloWorld173_delete(HelloWorld173 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld174
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD174_SIZE		12


typedef struct HelloWorld174 {
	uint32_t index;
	int32_t message;
} HelloWorld174;


void HelloWorld174_init(HelloWorld174 *sample);


bool HelloWorld174_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld174 *topic);

bool HelloWorld174_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld174 *topic);

uint32_t HelloWorld174_topic_max_size(uint32_t size);
HelloWorld174 *HelloWorld174_create(void);

void HelloWorld174_delete(HelloWorld174 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld175
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD175_SIZE		12


typedef struct HelloWorld175 {
	uint32_t index;
	int32_t message;
} HelloWorld175;


void HelloWorld175_init(HelloWorld175 *sample);


bool HelloWorld175_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld175 *topic);

bool HelloWorld175_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld175 *topic);

uint32_t HelloWorld175_topic_max_size(uint32_t size);
HelloWorld175 *HelloWorld175_create(void);

void HelloWorld175_delete(HelloWorld175 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld176
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD176_SIZE		12


typedef struct HelloWorld176 {
	uint32_t index;
	int32_t message;
} HelloWorld176;


void HelloWorld176_init(HelloWorld176 *sample);


bool HelloWorld176_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld176 *topic);

bool HelloWorld176_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld176 *topic);

uint32_t HelloWorld176_topic_max_size(uint32_t size);
HelloWorld176 *HelloWorld176_create(void);

void HelloWorld176_delete(HelloWorld176 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld177
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD177_SIZE		12


typedef struct HelloWorld177 {
	uint32_t index;
	int32_t message;
} HelloWorld177;


void HelloWorld177_init(HelloWorld177 *sample);


bool HelloWorld177_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld177 *topic);

bool HelloWorld177_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld177 *topic);

uint32_t HelloWorld177_topic_max_size(uint32_t size);
HelloWorld177 *HelloWorld177_create(void);

void HelloWorld177_delete(HelloWorld177 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld178
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD178_SIZE		12


typedef struct HelloWorld178 {
	uint32_t index;
	int32_t message;
} HelloWorld178;


void HelloWorld178_init(HelloWorld178 *sample);


bool HelloWorld178_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld178 *topic);

bool HelloWorld178_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld178 *topic);

uint32_t HelloWorld178_topic_max_size(uint32_t size);
HelloWorld178 *HelloWorld178_create(void);

void HelloWorld178_delete(HelloWorld178 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld179
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD179_SIZE		12


typedef struct HelloWorld179 {
	uint32_t index;
	int32_t message;
} HelloWorld179;


void HelloWorld179_init(HelloWorld179 *sample);


bool HelloWorld179_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld179 *topic);

bool HelloWorld179_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld179 *topic);

uint32_t HelloWorld179_topic_max_size(uint32_t size);
HelloWorld179 *HelloWorld179_create(void);

void HelloWorld179_delete(HelloWorld179 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld180
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD180_SIZE		12


typedef struct HelloWorld180 {
	uint32_t index;
	int32_t message;
} HelloWorld180;


void HelloWorld180_init(HelloWorld180 *sample);


bool HelloWorld180_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld180 *topic);

bool HelloWorld180_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld180 *topic);

uint32_t HelloWorld180_topic_max_size(uint32_t size);
HelloWorld180 *HelloWorld180_create(void);

void HelloWorld180_delete(HelloWorld180 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld181
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD181_SIZE		12


typedef struct HelloWorld181 {
	uint32_t index;
	int32_t message;
} HelloWorld181;


void HelloWorld181_init(HelloWorld181 *sample);


bool HelloWorld181_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld181 *topic);

bool HelloWorld181_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld181 *topic);

uint32_t HelloWorld181_topic_max_size(uint32_t size);
HelloWorld181 *HelloWorld181_create(void);

void HelloWorld181_delete(HelloWorld181 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld182
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD182_SIZE		12


typedef struct HelloWorld182 {
	uint32_t index;
	int32_t message;
} HelloWorld182;


void HelloWorld182_init(HelloWorld182 *sample);


bool HelloWorld182_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld182 *topic);

bool HelloWorld182_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld182 *topic);

uint32_t HelloWorld182_topic_max_size(uint32_t size);
HelloWorld182 *HelloWorld182_create(void);

void HelloWorld182_delete(HelloWorld182 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld183
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD183_SIZE		12


typedef struct HelloWorld183 {
	uint32_t index;
	int32_t message;
} HelloWorld183;


void HelloWorld183_init(HelloWorld183 *sample);


bool HelloWorld183_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld183 *topic);

bool HelloWorld183_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld183 *topic);

uint32_t HelloWorld183_topic_max_size(uint32_t size);
HelloWorld183 *HelloWorld183_create(void);

void HelloWorld183_delete(HelloWorld183 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld184
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD184_SIZE		12


typedef struct HelloWorld184 {
	uint32_t index;
	int32_t message;
} HelloWorld184;


void HelloWorld184_init(HelloWorld184 *sample);


bool HelloWorld184_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld184 *topic);

bool HelloWorld184_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld184 *topic);

uint32_t HelloWorld184_topic_max_size(uint32_t size);
HelloWorld184 *HelloWorld184_create(void);

void HelloWorld184_delete(HelloWorld184 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld185
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD185_SIZE		12


typedef struct HelloWorld185 {
	uint32_t index;
	int32_t message;
} HelloWorld185;


void HelloWorld185_init(HelloWorld185 *sample);


bool HelloWorld185_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld185 *topic);

bool HelloWorld185_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld185 *topic);

uint32_t HelloWorld185_topic_max_size(uint32_t size);
HelloWorld185 *HelloWorld185_create(void);

void HelloWorld185_delete(HelloWorld185 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld186
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD186_SIZE		12


typedef struct HelloWorld186 {
	uint32_t index;
	int32_t message;
} HelloWorld186;


void HelloWorld186_init(HelloWorld186 *sample);


bool HelloWorld186_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld186 *topic);

bool HelloWorld186_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld186 *topic);

uint32_t HelloWorld186_topic_max_size(uint32_t size);
HelloWorld186 *HelloWorld186_create(void);

void HelloWorld186_delete(HelloWorld186 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld187
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD187_SIZE		12


typedef struct HelloWorld187 {
	uint32_t index;
	int32_t message;
} HelloWorld187;


void HelloWorld187_init(HelloWorld187 *sample);


bool HelloWorld187_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld187 *topic);

bool HelloWorld187_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld187 *topic);

uint32_t HelloWorld187_topic_max_size(uint32_t size);
HelloWorld187 *HelloWorld187_create(void);

void HelloWorld187_delete(HelloWorld187 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld188
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD188_SIZE		12


typedef struct HelloWorld188 {
	uint32_t index;
	int32_t message;
} HelloWorld188;


void HelloWorld188_init(HelloWorld188 *sample);


bool HelloWorld188_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld188 *topic);

bool HelloWorld188_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld188 *topic);

uint32_t HelloWorld188_topic_max_size(uint32_t size);
HelloWorld188 *HelloWorld188_create(void);

void HelloWorld188_delete(HelloWorld188 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld189
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD189_SIZE		12


typedef struct HelloWorld189 {
	uint32_t index;
	int32_t message;
} HelloWorld189;


void HelloWorld189_init(HelloWorld189 *sample);


bool HelloWorld189_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld189 *topic);

bool HelloWorld189_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld189 *topic);

uint32_t HelloWorld189_topic_max_size(uint32_t size);
HelloWorld189 *HelloWorld189_create(void);

void HelloWorld189_delete(HelloWorld189 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld190
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD190_SIZE		12


typedef struct HelloWorld190 {
	uint32_t index;
	int32_t message;
} HelloWorld190;


void HelloWorld190_init(HelloWorld190 *sample);


bool HelloWorld190_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld190 *topic);

bool HelloWorld190_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld190 *topic);

uint32_t HelloWorld190_topic_max_size(uint32_t size);
HelloWorld190 *HelloWorld190_create(void);

void HelloWorld190_delete(HelloWorld190 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld191
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD191_SIZE		12


typedef struct HelloWorld191 {
	uint32_t index;
	int32_t message;
} HelloWorld191;


void HelloWorld191_init(HelloWorld191 *sample);


bool HelloWorld191_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld191 *topic);

bool HelloWorld191_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld191 *topic);

uint32_t HelloWorld191_topic_max_size(uint32_t size);
HelloWorld191 *HelloWorld191_create(void);

void HelloWorld191_delete(HelloWorld191 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld192
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD192_SIZE		12


typedef struct HelloWorld192 {
	uint32_t index;
	int32_t message;
} HelloWorld192;


void HelloWorld192_init(HelloWorld192 *sample);


bool HelloWorld192_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld192 *topic);

bool HelloWorld192_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld192 *topic);

uint32_t HelloWorld192_topic_max_size(uint32_t size);
HelloWorld192 *HelloWorld192_create(void);

void HelloWorld192_delete(HelloWorld192 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld193
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD193_SIZE		12


typedef struct HelloWorld193 {
	uint32_t index;
	int32_t message;
} HelloWorld193;


void HelloWorld193_init(HelloWorld193 *sample);


bool HelloWorld193_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld193 *topic);

bool HelloWorld193_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld193 *topic);

uint32_t HelloWorld193_topic_max_size(uint32_t size);
HelloWorld193 *HelloWorld193_create(void);

void HelloWorld193_delete(HelloWorld193 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld194
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD194_SIZE		12


typedef struct HelloWorld194 {
	uint32_t index;
	int32_t message;
} HelloWorld194;


void HelloWorld194_init(HelloWorld194 *sample);


bool HelloWorld194_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld194 *topic);

bool HelloWorld194_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld194 *topic);

uint32_t HelloWorld194_topic_max_size(uint32_t size);
HelloWorld194 *HelloWorld194_create(void);

void HelloWorld194_delete(HelloWorld194 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld195
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD195_SIZE		12


typedef struct HelloWorld195 {
	uint32_t index;
	int32_t message;
} HelloWorld195;


void HelloWorld195_init(HelloWorld195 *sample);


bool HelloWorld195_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld195 *topic);

bool HelloWorld195_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld195 *topic);

uint32_t HelloWorld195_topic_max_size(uint32_t size);
HelloWorld195 *HelloWorld195_create(void);

void HelloWorld195_delete(HelloWorld195 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld196
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD196_SIZE		12


typedef struct HelloWorld196 {
	uint32_t index;
	int32_t message;
} HelloWorld196;


void HelloWorld196_init(HelloWorld196 *sample);


bool HelloWorld196_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld196 *topic);

bool HelloWorld196_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld196 *topic);

uint32_t HelloWorld196_topic_max_size(uint32_t size);
HelloWorld196 *HelloWorld196_create(void);

void HelloWorld196_delete(HelloWorld196 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld197
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD197_SIZE		12


typedef struct HelloWorld197 {
	uint32_t index;
	int32_t message;
} HelloWorld197;


void HelloWorld197_init(HelloWorld197 *sample);


bool HelloWorld197_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld197 *topic);

bool HelloWorld197_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld197 *topic);

uint32_t HelloWorld197_topic_max_size(uint32_t size);
HelloWorld197 *HelloWorld197_create(void);

void HelloWorld197_delete(HelloWorld197 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld198
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD198_SIZE		12


typedef struct HelloWorld198 {
	uint32_t index;
	int32_t message;
} HelloWorld198;


void HelloWorld198_init(HelloWorld198 *sample);


bool HelloWorld198_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld198 *topic);

bool HelloWorld198_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld198 *topic);

uint32_t HelloWorld198_topic_max_size(uint32_t size);
HelloWorld198 *HelloWorld198_create(void);

void HelloWorld198_delete(HelloWorld198 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld199
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD199_SIZE		12


typedef struct HelloWorld199 {
	uint32_t index;
	int32_t message;
} HelloWorld199;


void HelloWorld199_init(HelloWorld199 *sample);


bool HelloWorld199_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld199 *topic);

bool HelloWorld199_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld199 *topic);

uint32_t HelloWorld199_topic_max_size(uint32_t size);
HelloWorld199 *HelloWorld199_create(void);

void HelloWorld199_delete(HelloWorld199 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld200
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD200_SIZE		12


typedef struct HelloWorld200 {
	uint32_t index;
	int32_t message;
} HelloWorld200;


void HelloWorld200_init(HelloWorld200 *sample);


bool HelloWorld200_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld200 *topic);

bool HelloWorld200_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld200 *topic);

uint32_t HelloWorld200_topic_max_size(uint32_t size);
HelloWorld200 *HelloWorld200_create(void);

void HelloWorld200_delete(HelloWorld200 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld201
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD201_SIZE		12


typedef struct HelloWorld201 {
	uint32_t index;
	int32_t message;
} HelloWorld201;


void HelloWorld201_init(HelloWorld201 *sample);


bool HelloWorld201_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld201 *topic);

bool HelloWorld201_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld201 *topic);

uint32_t HelloWorld201_topic_max_size(uint32_t size);
HelloWorld201 *HelloWorld201_create(void);

void HelloWorld201_delete(HelloWorld201 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld202
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD202_SIZE		12


typedef struct HelloWorld202 {
	uint32_t index;
	int32_t message;
} HelloWorld202;


void HelloWorld202_init(HelloWorld202 *sample);


bool HelloWorld202_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld202 *topic);

bool HelloWorld202_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld202 *topic);

uint32_t HelloWorld202_topic_max_size(uint32_t size);
HelloWorld202 *HelloWorld202_create(void);

void HelloWorld202_delete(HelloWorld202 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld203
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD203_SIZE		12


typedef struct HelloWorld203 {
	uint32_t index;
	int32_t message;
} HelloWorld203;


void HelloWorld203_init(HelloWorld203 *sample);


bool HelloWorld203_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld203 *topic);

bool HelloWorld203_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld203 *topic);

uint32_t HelloWorld203_topic_max_size(uint32_t size);
HelloWorld203 *HelloWorld203_create(void);

void HelloWorld203_delete(HelloWorld203 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld204
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD204_SIZE		12


typedef struct HelloWorld204 {
	uint32_t index;
	int32_t message;
} HelloWorld204;


void HelloWorld204_init(HelloWorld204 *sample);


bool HelloWorld204_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld204 *topic);

bool HelloWorld204_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld204 *topic);

uint32_t HelloWorld204_topic_max_size(uint32_t size);
HelloWorld204 *HelloWorld204_create(void);

void HelloWorld204_delete(HelloWorld204 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld205
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD205_SIZE		12


typedef struct HelloWorld205 {
	uint32_t index;
	int32_t message;
} HelloWorld205;


void HelloWorld205_init(HelloWorld205 *sample);


bool HelloWorld205_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld205 *topic);

bool HelloWorld205_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld205 *topic);

uint32_t HelloWorld205_topic_max_size(uint32_t size);
HelloWorld205 *HelloWorld205_create(void);

void HelloWorld205_delete(HelloWorld205 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld206
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD206_SIZE		12


typedef struct HelloWorld206 {
	uint32_t index;
	int32_t message;
} HelloWorld206;


void HelloWorld206_init(HelloWorld206 *sample);


bool HelloWorld206_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld206 *topic);

bool HelloWorld206_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld206 *topic);

uint32_t HelloWorld206_topic_max_size(uint32_t size);
HelloWorld206 *HelloWorld206_create(void);

void HelloWorld206_delete(HelloWorld206 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld207
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD207_SIZE		12


typedef struct HelloWorld207 {
	uint32_t index;
	int32_t message;
} HelloWorld207;


void HelloWorld207_init(HelloWorld207 *sample);


bool HelloWorld207_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld207 *topic);

bool HelloWorld207_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld207 *topic);

uint32_t HelloWorld207_topic_max_size(uint32_t size);
HelloWorld207 *HelloWorld207_create(void);

void HelloWorld207_delete(HelloWorld207 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld208
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD208_SIZE		12


typedef struct HelloWorld208 {
	uint32_t index;
	int32_t message;
} HelloWorld208;


void HelloWorld208_init(HelloWorld208 *sample);


bool HelloWorld208_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld208 *topic);

bool HelloWorld208_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld208 *topic);

uint32_t HelloWorld208_topic_max_size(uint32_t size);
HelloWorld208 *HelloWorld208_create(void);

void HelloWorld208_delete(HelloWorld208 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld209
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD209_SIZE		12


typedef struct HelloWorld209 {
	uint32_t index;
	int32_t message;
} HelloWorld209;


void HelloWorld209_init(HelloWorld209 *sample);


bool HelloWorld209_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld209 *topic);

bool HelloWorld209_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld209 *topic);

uint32_t HelloWorld209_topic_max_size(uint32_t size);
HelloWorld209 *HelloWorld209_create(void);

void HelloWorld209_delete(HelloWorld209 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld210
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD210_SIZE		12


typedef struct HelloWorld210 {
	uint32_t index;
	int32_t message;
} HelloWorld210;


void HelloWorld210_init(HelloWorld210 *sample);


bool HelloWorld210_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld210 *topic);

bool HelloWorld210_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld210 *topic);

uint32_t HelloWorld210_topic_max_size(uint32_t size);
HelloWorld210 *HelloWorld210_create(void);

void HelloWorld210_delete(HelloWorld210 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld211
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD211_SIZE		12


typedef struct HelloWorld211 {
	uint32_t index;
	int32_t message;
} HelloWorld211;


void HelloWorld211_init(HelloWorld211 *sample);


bool HelloWorld211_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld211 *topic);

bool HelloWorld211_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld211 *topic);

uint32_t HelloWorld211_topic_max_size(uint32_t size);
HelloWorld211 *HelloWorld211_create(void);

void HelloWorld211_delete(HelloWorld211 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld212
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD212_SIZE		12


typedef struct HelloWorld212 {
	uint32_t index;
	int32_t message;
} HelloWorld212;


void HelloWorld212_init(HelloWorld212 *sample);


bool HelloWorld212_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld212 *topic);

bool HelloWorld212_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld212 *topic);

uint32_t HelloWorld212_topic_max_size(uint32_t size);
HelloWorld212 *HelloWorld212_create(void);

void HelloWorld212_delete(HelloWorld212 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld213
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD213_SIZE		12


typedef struct HelloWorld213 {
	uint32_t index;
	int32_t message;
} HelloWorld213;


void HelloWorld213_init(HelloWorld213 *sample);


bool HelloWorld213_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld213 *topic);

bool HelloWorld213_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld213 *topic);

uint32_t HelloWorld213_topic_max_size(uint32_t size);
HelloWorld213 *HelloWorld213_create(void);

void HelloWorld213_delete(HelloWorld213 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld214
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD214_SIZE		12


typedef struct HelloWorld214 {
	uint32_t index;
	int32_t message;
} HelloWorld214;


void HelloWorld214_init(HelloWorld214 *sample);


bool HelloWorld214_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld214 *topic);

bool HelloWorld214_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld214 *topic);

uint32_t HelloWorld214_topic_max_size(uint32_t size);
HelloWorld214 *HelloWorld214_create(void);

void HelloWorld214_delete(HelloWorld214 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld215
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD215_SIZE		12


typedef struct HelloWorld215 {
	uint32_t index;
	int32_t message;
} HelloWorld215;


void HelloWorld215_init(HelloWorld215 *sample);


bool HelloWorld215_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld215 *topic);

bool HelloWorld215_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld215 *topic);

uint32_t HelloWorld215_topic_max_size(uint32_t size);
HelloWorld215 *HelloWorld215_create(void);

void HelloWorld215_delete(HelloWorld215 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld216
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD216_SIZE		12


typedef struct HelloWorld216 {
	uint32_t index;
	int32_t message;
} HelloWorld216;


void HelloWorld216_init(HelloWorld216 *sample);


bool HelloWorld216_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld216 *topic);

bool HelloWorld216_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld216 *topic);

uint32_t HelloWorld216_topic_max_size(uint32_t size);
HelloWorld216 *HelloWorld216_create(void);

void HelloWorld216_delete(HelloWorld216 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld217
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD217_SIZE		12


typedef struct HelloWorld217 {
	uint32_t index;
	int32_t message;
} HelloWorld217;


void HelloWorld217_init(HelloWorld217 *sample);


bool HelloWorld217_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld217 *topic);

bool HelloWorld217_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld217 *topic);

uint32_t HelloWorld217_topic_max_size(uint32_t size);
HelloWorld217 *HelloWorld217_create(void);

void HelloWorld217_delete(HelloWorld217 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld218
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD218_SIZE		12


typedef struct HelloWorld218 {
	uint32_t index;
	int32_t message;
} HelloWorld218;


void HelloWorld218_init(HelloWorld218 *sample);


bool HelloWorld218_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld218 *topic);

bool HelloWorld218_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld218 *topic);

uint32_t HelloWorld218_topic_max_size(uint32_t size);
HelloWorld218 *HelloWorld218_create(void);

void HelloWorld218_delete(HelloWorld218 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld219
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD219_SIZE		12


typedef struct HelloWorld219 {
	uint32_t index;
	int32_t message;
} HelloWorld219;


void HelloWorld219_init(HelloWorld219 *sample);


bool HelloWorld219_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld219 *topic);

bool HelloWorld219_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld219 *topic);

uint32_t HelloWorld219_topic_max_size(uint32_t size);
HelloWorld219 *HelloWorld219_create(void);

void HelloWorld219_delete(HelloWorld219 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld220
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD220_SIZE		12


typedef struct HelloWorld220 {
	uint32_t index;
	int32_t message;
} HelloWorld220;


void HelloWorld220_init(HelloWorld220 *sample);


bool HelloWorld220_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld220 *topic);

bool HelloWorld220_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld220 *topic);

uint32_t HelloWorld220_topic_max_size(uint32_t size);
HelloWorld220 *HelloWorld220_create(void);

void HelloWorld220_delete(HelloWorld220 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld221
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD221_SIZE		12


typedef struct HelloWorld221 {
	uint32_t index;
	int32_t message;
} HelloWorld221;


void HelloWorld221_init(HelloWorld221 *sample);


bool HelloWorld221_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld221 *topic);

bool HelloWorld221_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld221 *topic);

uint32_t HelloWorld221_topic_max_size(uint32_t size);
HelloWorld221 *HelloWorld221_create(void);

void HelloWorld221_delete(HelloWorld221 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld222
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD222_SIZE		12


typedef struct HelloWorld222 {
	uint32_t index;
	int32_t message;
} HelloWorld222;


void HelloWorld222_init(HelloWorld222 *sample);


bool HelloWorld222_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld222 *topic);

bool HelloWorld222_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld222 *topic);

uint32_t HelloWorld222_topic_max_size(uint32_t size);
HelloWorld222 *HelloWorld222_create(void);

void HelloWorld222_delete(HelloWorld222 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld223
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD223_SIZE		12


typedef struct HelloWorld223 {
	uint32_t index;
	int32_t message;
} HelloWorld223;


void HelloWorld223_init(HelloWorld223 *sample);


bool HelloWorld223_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld223 *topic);

bool HelloWorld223_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld223 *topic);

uint32_t HelloWorld223_topic_max_size(uint32_t size);
HelloWorld223 *HelloWorld223_create(void);

void HelloWorld223_delete(HelloWorld223 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld224
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD224_SIZE		12


typedef struct HelloWorld224 {
	uint32_t index;
	int32_t message;
} HelloWorld224;


void HelloWorld224_init(HelloWorld224 *sample);


bool HelloWorld224_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld224 *topic);

bool HelloWorld224_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld224 *topic);

uint32_t HelloWorld224_topic_max_size(uint32_t size);
HelloWorld224 *HelloWorld224_create(void);

void HelloWorld224_delete(HelloWorld224 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld225
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD225_SIZE		12


typedef struct HelloWorld225 {
	uint32_t index;
	int32_t message;
} HelloWorld225;


void HelloWorld225_init(HelloWorld225 *sample);


bool HelloWorld225_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld225 *topic);

bool HelloWorld225_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld225 *topic);

uint32_t HelloWorld225_topic_max_size(uint32_t size);
HelloWorld225 *HelloWorld225_create(void);

void HelloWorld225_delete(HelloWorld225 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld226
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD226_SIZE		12


typedef struct HelloWorld226 {
	uint32_t index;
	int32_t message;
} HelloWorld226;


void HelloWorld226_init(HelloWorld226 *sample);


bool HelloWorld226_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld226 *topic);

bool HelloWorld226_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld226 *topic);

uint32_t HelloWorld226_topic_max_size(uint32_t size);
HelloWorld226 *HelloWorld226_create(void);

void HelloWorld226_delete(HelloWorld226 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld227
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD227_SIZE		12


typedef struct HelloWorld227 {
	uint32_t index;
	int32_t message;
} HelloWorld227;


void HelloWorld227_init(HelloWorld227 *sample);


bool HelloWorld227_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld227 *topic);

bool HelloWorld227_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld227 *topic);

uint32_t HelloWorld227_topic_max_size(uint32_t size);
HelloWorld227 *HelloWorld227_create(void);

void HelloWorld227_delete(HelloWorld227 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld228
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD228_SIZE		12


typedef struct HelloWorld228 {
	uint32_t index;
	int32_t message;
} HelloWorld228;


void HelloWorld228_init(HelloWorld228 *sample);


bool HelloWorld228_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld228 *topic);

bool HelloWorld228_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld228 *topic);

uint32_t HelloWorld228_topic_max_size(uint32_t size);
HelloWorld228 *HelloWorld228_create(void);

void HelloWorld228_delete(HelloWorld228 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld229
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD229_SIZE		12


typedef struct HelloWorld229 {
	uint32_t index;
	int32_t message;
} HelloWorld229;


void HelloWorld229_init(HelloWorld229 *sample);


bool HelloWorld229_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld229 *topic);

bool HelloWorld229_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld229 *topic);

uint32_t HelloWorld229_topic_max_size(uint32_t size);
HelloWorld229 *HelloWorld229_create(void);

void HelloWorld229_delete(HelloWorld229 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld230
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD230_SIZE		12


typedef struct HelloWorld230 {
	uint32_t index;
	int32_t message;
} HelloWorld230;


void HelloWorld230_init(HelloWorld230 *sample);


bool HelloWorld230_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld230 *topic);

bool HelloWorld230_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld230 *topic);

uint32_t HelloWorld230_topic_max_size(uint32_t size);
HelloWorld230 *HelloWorld230_create(void);

void HelloWorld230_delete(HelloWorld230 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld231
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD231_SIZE		12


typedef struct HelloWorld231 {
	uint32_t index;
	int32_t message;
} HelloWorld231;


void HelloWorld231_init(HelloWorld231 *sample);


bool HelloWorld231_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld231 *topic);

bool HelloWorld231_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld231 *topic);

uint32_t HelloWorld231_topic_max_size(uint32_t size);
HelloWorld231 *HelloWorld231_create(void);

void HelloWorld231_delete(HelloWorld231 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld232
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD232_SIZE		12


typedef struct HelloWorld232 {
	uint32_t index;
	int32_t message;
} HelloWorld232;


void HelloWorld232_init(HelloWorld232 *sample);


bool HelloWorld232_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld232 *topic);

bool HelloWorld232_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld232 *topic);

uint32_t HelloWorld232_topic_max_size(uint32_t size);
HelloWorld232 *HelloWorld232_create(void);

void HelloWorld232_delete(HelloWorld232 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld233
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD233_SIZE		12


typedef struct HelloWorld233 {
	uint32_t index;
	int32_t message;
} HelloWorld233;


void HelloWorld233_init(HelloWorld233 *sample);


bool HelloWorld233_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld233 *topic);

bool HelloWorld233_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld233 *topic);

uint32_t HelloWorld233_topic_max_size(uint32_t size);
HelloWorld233 *HelloWorld233_create(void);

void HelloWorld233_delete(HelloWorld233 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld234
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD234_SIZE		12


typedef struct HelloWorld234 {
	uint32_t index;
	int32_t message;
} HelloWorld234;


void HelloWorld234_init(HelloWorld234 *sample);


bool HelloWorld234_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld234 *topic);

bool HelloWorld234_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld234 *topic);

uint32_t HelloWorld234_topic_max_size(uint32_t size);
HelloWorld234 *HelloWorld234_create(void);

void HelloWorld234_delete(HelloWorld234 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld235
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD235_SIZE		12


typedef struct HelloWorld235 {
	uint32_t index;
	int32_t message;
} HelloWorld235;


void HelloWorld235_init(HelloWorld235 *sample);


bool HelloWorld235_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld235 *topic);

bool HelloWorld235_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld235 *topic);

uint32_t HelloWorld235_topic_max_size(uint32_t size);
HelloWorld235 *HelloWorld235_create(void);

void HelloWorld235_delete(HelloWorld235 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld236
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD236_SIZE		12


typedef struct HelloWorld236 {
	uint32_t index;
	int32_t message;
} HelloWorld236;


void HelloWorld236_init(HelloWorld236 *sample);


bool HelloWorld236_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld236 *topic);

bool HelloWorld236_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld236 *topic);

uint32_t HelloWorld236_topic_max_size(uint32_t size);
HelloWorld236 *HelloWorld236_create(void);

void HelloWorld236_delete(HelloWorld236 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld237
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD237_SIZE		12


typedef struct HelloWorld237 {
	uint32_t index;
	int32_t message;
} HelloWorld237;


void HelloWorld237_init(HelloWorld237 *sample);


bool HelloWorld237_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld237 *topic);

bool HelloWorld237_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld237 *topic);

uint32_t HelloWorld237_topic_max_size(uint32_t size);
HelloWorld237 *HelloWorld237_create(void);

void HelloWorld237_delete(HelloWorld237 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld238
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD238_SIZE		12


typedef struct HelloWorld238 {
	uint32_t index;
	int32_t message;
} HelloWorld238;


void HelloWorld238_init(HelloWorld238 *sample);


bool HelloWorld238_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld238 *topic);

bool HelloWorld238_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld238 *topic);

uint32_t HelloWorld238_topic_max_size(uint32_t size);
HelloWorld238 *HelloWorld238_create(void);

void HelloWorld238_delete(HelloWorld238 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld239
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD239_SIZE		12


typedef struct HelloWorld239 {
	uint32_t index;
	int32_t message;
} HelloWorld239;


void HelloWorld239_init(HelloWorld239 *sample);


bool HelloWorld239_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld239 *topic);

bool HelloWorld239_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld239 *topic);

uint32_t HelloWorld239_topic_max_size(uint32_t size);
HelloWorld239 *HelloWorld239_create(void);

void HelloWorld239_delete(HelloWorld239 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld240
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD240_SIZE		12


typedef struct HelloWorld240 {
	uint32_t index;
	int32_t message;
} HelloWorld240;


void HelloWorld240_init(HelloWorld240 *sample);


bool HelloWorld240_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld240 *topic);

bool HelloWorld240_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld240 *topic);

uint32_t HelloWorld240_topic_max_size(uint32_t size);
HelloWorld240 *HelloWorld240_create(void);

void HelloWorld240_delete(HelloWorld240 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld241
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD241_SIZE		12


typedef struct HelloWorld241 {
	uint32_t index;
	int32_t message;
} HelloWorld241;


void HelloWorld241_init(HelloWorld241 *sample);


bool HelloWorld241_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld241 *topic);

bool HelloWorld241_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld241 *topic);

uint32_t HelloWorld241_topic_max_size(uint32_t size);
HelloWorld241 *HelloWorld241_create(void);

void HelloWorld241_delete(HelloWorld241 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld242
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD242_SIZE		12


typedef struct HelloWorld242 {
	uint32_t index;
	int32_t message;
} HelloWorld242;


void HelloWorld242_init(HelloWorld242 *sample);


bool HelloWorld242_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld242 *topic);

bool HelloWorld242_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld242 *topic);

uint32_t HelloWorld242_topic_max_size(uint32_t size);
HelloWorld242 *HelloWorld242_create(void);

void HelloWorld242_delete(HelloWorld242 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld243
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD243_SIZE		12


typedef struct HelloWorld243 {
	uint32_t index;
	int32_t message;
} HelloWorld243;


void HelloWorld243_init(HelloWorld243 *sample);


bool HelloWorld243_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld243 *topic);

bool HelloWorld243_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld243 *topic);

uint32_t HelloWorld243_topic_max_size(uint32_t size);
HelloWorld243 *HelloWorld243_create(void);

void HelloWorld243_delete(HelloWorld243 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld244
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD244_SIZE		12


typedef struct HelloWorld244 {
	uint32_t index;
	int32_t message;
} HelloWorld244;


void HelloWorld244_init(HelloWorld244 *sample);


bool HelloWorld244_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld244 *topic);

bool HelloWorld244_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld244 *topic);

uint32_t HelloWorld244_topic_max_size(uint32_t size);
HelloWorld244 *HelloWorld244_create(void);

void HelloWorld244_delete(HelloWorld244 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld245
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD245_SIZE		12


typedef struct HelloWorld245 {
	uint32_t index;
	int32_t message;
} HelloWorld245;


void HelloWorld245_init(HelloWorld245 *sample);


bool HelloWorld245_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld245 *topic);

bool HelloWorld245_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld245 *topic);

uint32_t HelloWorld245_topic_max_size(uint32_t size);
HelloWorld245 *HelloWorld245_create(void);

void HelloWorld245_delete(HelloWorld245 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld246
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD246_SIZE		12


typedef struct HelloWorld246 {
	uint32_t index;
	int32_t message;
} HelloWorld246;


void HelloWorld246_init(HelloWorld246 *sample);


bool HelloWorld246_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld246 *topic);

bool HelloWorld246_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld246 *topic);

uint32_t HelloWorld246_topic_max_size(uint32_t size);
HelloWorld246 *HelloWorld246_create(void);

void HelloWorld246_delete(HelloWorld246 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld247
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD247_SIZE		12


typedef struct HelloWorld247 {
	uint32_t index;
	int32_t message;
} HelloWorld247;


void HelloWorld247_init(HelloWorld247 *sample);


bool HelloWorld247_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld247 *topic);

bool HelloWorld247_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld247 *topic);

uint32_t HelloWorld247_topic_max_size(uint32_t size);
HelloWorld247 *HelloWorld247_create(void);

void HelloWorld247_delete(HelloWorld247 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld248
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD248_SIZE		12


typedef struct HelloWorld248 {
	uint32_t index;
	int32_t message;
} HelloWorld248;


void HelloWorld248_init(HelloWorld248 *sample);


bool HelloWorld248_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld248 *topic);

bool HelloWorld248_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld248 *topic);

uint32_t HelloWorld248_topic_max_size(uint32_t size);
HelloWorld248 *HelloWorld248_create(void);

void HelloWorld248_delete(HelloWorld248 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld249
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD249_SIZE		12


typedef struct HelloWorld249 {
	uint32_t index;
	int32_t message;
} HelloWorld249;


void HelloWorld249_init(HelloWorld249 *sample);


bool HelloWorld249_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld249 *topic);

bool HelloWorld249_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld249 *topic);

uint32_t HelloWorld249_topic_max_size(uint32_t size);
HelloWorld249 *HelloWorld249_create(void);

void HelloWorld249_delete(HelloWorld249 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld250
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD250_SIZE		12


typedef struct HelloWorld250 {
	uint32_t index;
	int32_t message;
} HelloWorld250;


void HelloWorld250_init(HelloWorld250 *sample);


bool HelloWorld250_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld250 *topic);

bool HelloWorld250_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld250 *topic);

uint32_t HelloWorld250_topic_max_size(uint32_t size);
HelloWorld250 *HelloWorld250_create(void);

void HelloWorld250_delete(HelloWorld250 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld251
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD251_SIZE		12


typedef struct HelloWorld251 {
	uint32_t index;
	int32_t message;
} HelloWorld251;


void HelloWorld251_init(HelloWorld251 *sample);


bool HelloWorld251_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld251 *topic);

bool HelloWorld251_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld251 *topic);

uint32_t HelloWorld251_topic_max_size(uint32_t size);
HelloWorld251 *HelloWorld251_create(void);

void HelloWorld251_delete(HelloWorld251 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld252
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD252_SIZE		12


typedef struct HelloWorld252 {
	uint32_t index;
	int32_t message;
} HelloWorld252;


void HelloWorld252_init(HelloWorld252 *sample);


bool HelloWorld252_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld252 *topic);

bool HelloWorld252_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld252 *topic);

uint32_t HelloWorld252_topic_max_size(uint32_t size);
HelloWorld252 *HelloWorld252_create(void);

void HelloWorld252_delete(HelloWorld252 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld253
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD253_SIZE		12


typedef struct HelloWorld253 {
	uint32_t index;
	int32_t message;
} HelloWorld253;


void HelloWorld253_init(HelloWorld253 *sample);


bool HelloWorld253_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld253 *topic);

bool HelloWorld253_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld253 *topic);

uint32_t HelloWorld253_topic_max_size(uint32_t size);
HelloWorld253 *HelloWorld253_create(void);

void HelloWorld253_delete(HelloWorld253 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld254
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD254_SIZE		12


typedef struct HelloWorld254 {
	uint32_t index;
	int32_t message;
} HelloWorld254;


void HelloWorld254_init(HelloWorld254 *sample);


bool HelloWorld254_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld254 *topic);

bool HelloWorld254_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld254 *topic);

uint32_t HelloWorld254_topic_max_size(uint32_t size);
HelloWorld254 *HelloWorld254_create(void);

void HelloWorld254_delete(HelloWorld254 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld255
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD255_SIZE		12


typedef struct HelloWorld255 {
	uint32_t index;
	int32_t message;
} HelloWorld255;


void HelloWorld255_init(HelloWorld255 *sample);


bool HelloWorld255_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld255 *topic);

bool HelloWorld255_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld255 *topic);

uint32_t HelloWorld255_topic_max_size(uint32_t size);
HelloWorld255 *HelloWorld255_create(void);

void HelloWorld255_delete(HelloWorld255 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld256
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD256_SIZE		12


typedef struct HelloWorld256 {
	uint32_t index;
	int32_t message;
} HelloWorld256;


void HelloWorld256_init(HelloWorld256 *sample);


bool HelloWorld256_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld256 *topic);

bool HelloWorld256_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld256 *topic);

uint32_t HelloWorld256_topic_max_size(uint32_t size);
HelloWorld256 *HelloWorld256_create(void);

void HelloWorld256_delete(HelloWorld256 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld257
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD257_SIZE		12


typedef struct HelloWorld257 {
	uint32_t index;
	int32_t message;
} HelloWorld257;


void HelloWorld257_init(HelloWorld257 *sample);


bool HelloWorld257_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld257 *topic);

bool HelloWorld257_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld257 *topic);

uint32_t HelloWorld257_topic_max_size(uint32_t size);
HelloWorld257 *HelloWorld257_create(void);

void HelloWorld257_delete(HelloWorld257 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld258
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD258_SIZE		12


typedef struct HelloWorld258 {
	uint32_t index;
	int32_t message;
} HelloWorld258;


void HelloWorld258_init(HelloWorld258 *sample);


bool HelloWorld258_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld258 *topic);

bool HelloWorld258_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld258 *topic);

uint32_t HelloWorld258_topic_max_size(uint32_t size);
HelloWorld258 *HelloWorld258_create(void);

void HelloWorld258_delete(HelloWorld258 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld259
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD259_SIZE		12


typedef struct HelloWorld259 {
	uint32_t index;
	int32_t message;
} HelloWorld259;


void HelloWorld259_init(HelloWorld259 *sample);


bool HelloWorld259_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld259 *topic);

bool HelloWorld259_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld259 *topic);

uint32_t HelloWorld259_topic_max_size(uint32_t size);
HelloWorld259 *HelloWorld259_create(void);

void HelloWorld259_delete(HelloWorld259 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld260
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD260_SIZE		12


typedef struct HelloWorld260 {
	uint32_t index;
	int32_t message;
} HelloWorld260;


void HelloWorld260_init(HelloWorld260 *sample);


bool HelloWorld260_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld260 *topic);

bool HelloWorld260_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld260 *topic);

uint32_t HelloWorld260_topic_max_size(uint32_t size);
HelloWorld260 *HelloWorld260_create(void);

void HelloWorld260_delete(HelloWorld260 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld261
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD261_SIZE		12


typedef struct HelloWorld261 {
	uint32_t index;
	int32_t message;
} HelloWorld261;


void HelloWorld261_init(HelloWorld261 *sample);


bool HelloWorld261_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld261 *topic);

bool HelloWorld261_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld261 *topic);

uint32_t HelloWorld261_topic_max_size(uint32_t size);
HelloWorld261 *HelloWorld261_create(void);

void HelloWorld261_delete(HelloWorld261 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld262
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD262_SIZE		12


typedef struct HelloWorld262 {
	uint32_t index;
	int32_t message;
} HelloWorld262;


void HelloWorld262_init(HelloWorld262 *sample);


bool HelloWorld262_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld262 *topic);

bool HelloWorld262_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld262 *topic);

uint32_t HelloWorld262_topic_max_size(uint32_t size);
HelloWorld262 *HelloWorld262_create(void);

void HelloWorld262_delete(HelloWorld262 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld263
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD263_SIZE		12


typedef struct HelloWorld263 {
	uint32_t index;
	int32_t message;
} HelloWorld263;


void HelloWorld263_init(HelloWorld263 *sample);


bool HelloWorld263_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld263 *topic);

bool HelloWorld263_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld263 *topic);

uint32_t HelloWorld263_topic_max_size(uint32_t size);
HelloWorld263 *HelloWorld263_create(void);

void HelloWorld263_delete(HelloWorld263 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld264
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD264_SIZE		12


typedef struct HelloWorld264 {
	uint32_t index;
	int32_t message;
} HelloWorld264;


void HelloWorld264_init(HelloWorld264 *sample);


bool HelloWorld264_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld264 *topic);

bool HelloWorld264_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld264 *topic);

uint32_t HelloWorld264_topic_max_size(uint32_t size);
HelloWorld264 *HelloWorld264_create(void);

void HelloWorld264_delete(HelloWorld264 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld265
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD265_SIZE		12


typedef struct HelloWorld265 {
	uint32_t index;
	int32_t message;
} HelloWorld265;


void HelloWorld265_init(HelloWorld265 *sample);


bool HelloWorld265_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld265 *topic);

bool HelloWorld265_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld265 *topic);

uint32_t HelloWorld265_topic_max_size(uint32_t size);
HelloWorld265 *HelloWorld265_create(void);

void HelloWorld265_delete(HelloWorld265 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld266
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD266_SIZE		12


typedef struct HelloWorld266 {
	uint32_t index;
	int32_t message;
} HelloWorld266;


void HelloWorld266_init(HelloWorld266 *sample);


bool HelloWorld266_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld266 *topic);

bool HelloWorld266_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld266 *topic);

uint32_t HelloWorld266_topic_max_size(uint32_t size);
HelloWorld266 *HelloWorld266_create(void);

void HelloWorld266_delete(HelloWorld266 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld267
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD267_SIZE		12


typedef struct HelloWorld267 {
	uint32_t index;
	int32_t message;
} HelloWorld267;


void HelloWorld267_init(HelloWorld267 *sample);


bool HelloWorld267_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld267 *topic);

bool HelloWorld267_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld267 *topic);

uint32_t HelloWorld267_topic_max_size(uint32_t size);
HelloWorld267 *HelloWorld267_create(void);

void HelloWorld267_delete(HelloWorld267 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld268
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD268_SIZE		12


typedef struct HelloWorld268 {
	uint32_t index;
	int32_t message;
} HelloWorld268;


void HelloWorld268_init(HelloWorld268 *sample);


bool HelloWorld268_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld268 *topic);

bool HelloWorld268_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld268 *topic);

uint32_t HelloWorld268_topic_max_size(uint32_t size);
HelloWorld268 *HelloWorld268_create(void);

void HelloWorld268_delete(HelloWorld268 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld269
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD269_SIZE		12


typedef struct HelloWorld269 {
	uint32_t index;
	int32_t message;
} HelloWorld269;


void HelloWorld269_init(HelloWorld269 *sample);


bool HelloWorld269_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld269 *topic);

bool HelloWorld269_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld269 *topic);

uint32_t HelloWorld269_topic_max_size(uint32_t size);
HelloWorld269 *HelloWorld269_create(void);

void HelloWorld269_delete(HelloWorld269 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld270
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD270_SIZE		12


typedef struct HelloWorld270 {
	uint32_t index;
	int32_t message;
} HelloWorld270;


void HelloWorld270_init(HelloWorld270 *sample);


bool HelloWorld270_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld270 *topic);

bool HelloWorld270_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld270 *topic);

uint32_t HelloWorld270_topic_max_size(uint32_t size);
HelloWorld270 *HelloWorld270_create(void);

void HelloWorld270_delete(HelloWorld270 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld271
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD271_SIZE		12


typedef struct HelloWorld271 {
	uint32_t index;
	int32_t message;
} HelloWorld271;


void HelloWorld271_init(HelloWorld271 *sample);


bool HelloWorld271_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld271 *topic);

bool HelloWorld271_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld271 *topic);

uint32_t HelloWorld271_topic_max_size(uint32_t size);
HelloWorld271 *HelloWorld271_create(void);

void HelloWorld271_delete(HelloWorld271 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld272
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD272_SIZE		12


typedef struct HelloWorld272 {
	uint32_t index;
	int32_t message;
} HelloWorld272;


void HelloWorld272_init(HelloWorld272 *sample);


bool HelloWorld272_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld272 *topic);

bool HelloWorld272_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld272 *topic);

uint32_t HelloWorld272_topic_max_size(uint32_t size);
HelloWorld272 *HelloWorld272_create(void);

void HelloWorld272_delete(HelloWorld272 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld273
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD273_SIZE		12


typedef struct HelloWorld273 {
	uint32_t index;
	int32_t message;
} HelloWorld273;


void HelloWorld273_init(HelloWorld273 *sample);


bool HelloWorld273_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld273 *topic);

bool HelloWorld273_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld273 *topic);

uint32_t HelloWorld273_topic_max_size(uint32_t size);
HelloWorld273 *HelloWorld273_create(void);

void HelloWorld273_delete(HelloWorld273 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld274
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD274_SIZE		12


typedef struct HelloWorld274 {
	uint32_t index;
	int32_t message;
} HelloWorld274;


void HelloWorld274_init(HelloWorld274 *sample);


bool HelloWorld274_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld274 *topic);

bool HelloWorld274_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld274 *topic);

uint32_t HelloWorld274_topic_max_size(uint32_t size);
HelloWorld274 *HelloWorld274_create(void);

void HelloWorld274_delete(HelloWorld274 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld275
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD275_SIZE		12


typedef struct HelloWorld275 {
	uint32_t index;
	int32_t message;
} HelloWorld275;


void HelloWorld275_init(HelloWorld275 *sample);


bool HelloWorld275_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld275 *topic);

bool HelloWorld275_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld275 *topic);

uint32_t HelloWorld275_topic_max_size(uint32_t size);
HelloWorld275 *HelloWorld275_create(void);

void HelloWorld275_delete(HelloWorld275 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld276
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD276_SIZE		12


typedef struct HelloWorld276 {
	uint32_t index;
	int32_t message;
} HelloWorld276;


void HelloWorld276_init(HelloWorld276 *sample);


bool HelloWorld276_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld276 *topic);

bool HelloWorld276_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld276 *topic);

uint32_t HelloWorld276_topic_max_size(uint32_t size);
HelloWorld276 *HelloWorld276_create(void);

void HelloWorld276_delete(HelloWorld276 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld277
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD277_SIZE		12


typedef struct HelloWorld277 {
	uint32_t index;
	int32_t message;
} HelloWorld277;


void HelloWorld277_init(HelloWorld277 *sample);


bool HelloWorld277_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld277 *topic);

bool HelloWorld277_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld277 *topic);

uint32_t HelloWorld277_topic_max_size(uint32_t size);
HelloWorld277 *HelloWorld277_create(void);

void HelloWorld277_delete(HelloWorld277 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld278
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD278_SIZE		12


typedef struct HelloWorld278 {
	uint32_t index;
	int32_t message;
} HelloWorld278;


void HelloWorld278_init(HelloWorld278 *sample);


bool HelloWorld278_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld278 *topic);

bool HelloWorld278_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld278 *topic);

uint32_t HelloWorld278_topic_max_size(uint32_t size);
HelloWorld278 *HelloWorld278_create(void);

void HelloWorld278_delete(HelloWorld278 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld279
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD279_SIZE		12


typedef struct HelloWorld279 {
	uint32_t index;
	int32_t message;
} HelloWorld279;


void HelloWorld279_init(HelloWorld279 *sample);


bool HelloWorld279_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld279 *topic);

bool HelloWorld279_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld279 *topic);

uint32_t HelloWorld279_topic_max_size(uint32_t size);
HelloWorld279 *HelloWorld279_create(void);

void HelloWorld279_delete(HelloWorld279 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld280
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD280_SIZE		12


typedef struct HelloWorld280 {
	uint32_t index;
	int32_t message;
} HelloWorld280;


void HelloWorld280_init(HelloWorld280 *sample);


bool HelloWorld280_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld280 *topic);

bool HelloWorld280_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld280 *topic);

uint32_t HelloWorld280_topic_max_size(uint32_t size);
HelloWorld280 *HelloWorld280_create(void);

void HelloWorld280_delete(HelloWorld280 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld281
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD281_SIZE		12


typedef struct HelloWorld281 {
	uint32_t index;
	int32_t message;
} HelloWorld281;


void HelloWorld281_init(HelloWorld281 *sample);


bool HelloWorld281_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld281 *topic);

bool HelloWorld281_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld281 *topic);

uint32_t HelloWorld281_topic_max_size(uint32_t size);
HelloWorld281 *HelloWorld281_create(void);

void HelloWorld281_delete(HelloWorld281 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld282
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD282_SIZE		12


typedef struct HelloWorld282 {
	uint32_t index;
	int32_t message;
} HelloWorld282;


void HelloWorld282_init(HelloWorld282 *sample);


bool HelloWorld282_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld282 *topic);

bool HelloWorld282_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld282 *topic);

uint32_t HelloWorld282_topic_max_size(uint32_t size);
HelloWorld282 *HelloWorld282_create(void);

void HelloWorld282_delete(HelloWorld282 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld283
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD283_SIZE		12


typedef struct HelloWorld283 {
	uint32_t index;
	int32_t message;
} HelloWorld283;


void HelloWorld283_init(HelloWorld283 *sample);


bool HelloWorld283_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld283 *topic);

bool HelloWorld283_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld283 *topic);

uint32_t HelloWorld283_topic_max_size(uint32_t size);
HelloWorld283 *HelloWorld283_create(void);

void HelloWorld283_delete(HelloWorld283 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld284
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD284_SIZE		12


typedef struct HelloWorld284 {
	uint32_t index;
	int32_t message;
} HelloWorld284;


void HelloWorld284_init(HelloWorld284 *sample);


bool HelloWorld284_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld284 *topic);

bool HelloWorld284_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld284 *topic);

uint32_t HelloWorld284_topic_max_size(uint32_t size);
HelloWorld284 *HelloWorld284_create(void);

void HelloWorld284_delete(HelloWorld284 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld285
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD285_SIZE		12


typedef struct HelloWorld285 {
	uint32_t index;
	int32_t message;
} HelloWorld285;


void HelloWorld285_init(HelloWorld285 *sample);


bool HelloWorld285_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld285 *topic);

bool HelloWorld285_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld285 *topic);

uint32_t HelloWorld285_topic_max_size(uint32_t size);
HelloWorld285 *HelloWorld285_create(void);

void HelloWorld285_delete(HelloWorld285 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld286
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD286_SIZE		12


typedef struct HelloWorld286 {
	uint32_t index;
	int32_t message;
} HelloWorld286;


void HelloWorld286_init(HelloWorld286 *sample);


bool HelloWorld286_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld286 *topic);

bool HelloWorld286_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld286 *topic);

uint32_t HelloWorld286_topic_max_size(uint32_t size);
HelloWorld286 *HelloWorld286_create(void);

void HelloWorld286_delete(HelloWorld286 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld287
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD287_SIZE		12


typedef struct HelloWorld287 {
	uint32_t index;
	int32_t message;
} HelloWorld287;


void HelloWorld287_init(HelloWorld287 *sample);


bool HelloWorld287_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld287 *topic);

bool HelloWorld287_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld287 *topic);

uint32_t HelloWorld287_topic_max_size(uint32_t size);
HelloWorld287 *HelloWorld287_create(void);

void HelloWorld287_delete(HelloWorld287 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld288
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD288_SIZE		12


typedef struct HelloWorld288 {
	uint32_t index;
	int32_t message;
} HelloWorld288;


void HelloWorld288_init(HelloWorld288 *sample);


bool HelloWorld288_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld288 *topic);

bool HelloWorld288_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld288 *topic);

uint32_t HelloWorld288_topic_max_size(uint32_t size);
HelloWorld288 *HelloWorld288_create(void);

void HelloWorld288_delete(HelloWorld288 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld289
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD289_SIZE		12


typedef struct HelloWorld289 {
	uint32_t index;
	int32_t message;
} HelloWorld289;


void HelloWorld289_init(HelloWorld289 *sample);


bool HelloWorld289_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld289 *topic);

bool HelloWorld289_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld289 *topic);

uint32_t HelloWorld289_topic_max_size(uint32_t size);
HelloWorld289 *HelloWorld289_create(void);

void HelloWorld289_delete(HelloWorld289 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld290
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD290_SIZE		12


typedef struct HelloWorld290 {
	uint32_t index;
	int32_t message;
} HelloWorld290;


void HelloWorld290_init(HelloWorld290 *sample);


bool HelloWorld290_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld290 *topic);

bool HelloWorld290_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld290 *topic);

uint32_t HelloWorld290_topic_max_size(uint32_t size);
HelloWorld290 *HelloWorld290_create(void);

void HelloWorld290_delete(HelloWorld290 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld291
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD291_SIZE		12


typedef struct HelloWorld291 {
	uint32_t index;
	int32_t message;
} HelloWorld291;


void HelloWorld291_init(HelloWorld291 *sample);


bool HelloWorld291_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld291 *topic);

bool HelloWorld291_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld291 *topic);

uint32_t HelloWorld291_topic_max_size(uint32_t size);
HelloWorld291 *HelloWorld291_create(void);

void HelloWorld291_delete(HelloWorld291 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld292
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD292_SIZE		12


typedef struct HelloWorld292 {
	uint32_t index;
	int32_t message;
} HelloWorld292;


void HelloWorld292_init(HelloWorld292 *sample);


bool HelloWorld292_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld292 *topic);

bool HelloWorld292_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld292 *topic);

uint32_t HelloWorld292_topic_max_size(uint32_t size);
HelloWorld292 *HelloWorld292_create(void);

void HelloWorld292_delete(HelloWorld292 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld293
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD293_SIZE		12


typedef struct HelloWorld293 {
	uint32_t index;
	int32_t message;
} HelloWorld293;


void HelloWorld293_init(HelloWorld293 *sample);


bool HelloWorld293_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld293 *topic);

bool HelloWorld293_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld293 *topic);

uint32_t HelloWorld293_topic_max_size(uint32_t size);
HelloWorld293 *HelloWorld293_create(void);

void HelloWorld293_delete(HelloWorld293 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld294
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD294_SIZE		12


typedef struct HelloWorld294 {
	uint32_t index;
	int32_t message;
} HelloWorld294;


void HelloWorld294_init(HelloWorld294 *sample);


bool HelloWorld294_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld294 *topic);

bool HelloWorld294_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld294 *topic);

uint32_t HelloWorld294_topic_max_size(uint32_t size);
HelloWorld294 *HelloWorld294_create(void);

void HelloWorld294_delete(HelloWorld294 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld295
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD295_SIZE		12


typedef struct HelloWorld295 {
	uint32_t index;
	int32_t message;
} HelloWorld295;


void HelloWorld295_init(HelloWorld295 *sample);


bool HelloWorld295_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld295 *topic);

bool HelloWorld295_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld295 *topic);

uint32_t HelloWorld295_topic_max_size(uint32_t size);
HelloWorld295 *HelloWorld295_create(void);

void HelloWorld295_delete(HelloWorld295 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld296
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD296_SIZE		12


typedef struct HelloWorld296 {
	uint32_t index;
	int32_t message;
} HelloWorld296;


void HelloWorld296_init(HelloWorld296 *sample);


bool HelloWorld296_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld296 *topic);

bool HelloWorld296_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld296 *topic);

uint32_t HelloWorld296_topic_max_size(uint32_t size);
HelloWorld296 *HelloWorld296_create(void);

void HelloWorld296_delete(HelloWorld296 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld297
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD297_SIZE		12


typedef struct HelloWorld297 {
	uint32_t index;
	int32_t message;
} HelloWorld297;


void HelloWorld297_init(HelloWorld297 *sample);


bool HelloWorld297_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld297 *topic);

bool HelloWorld297_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld297 *topic);

uint32_t HelloWorld297_topic_max_size(uint32_t size);
HelloWorld297 *HelloWorld297_create(void);

void HelloWorld297_delete(HelloWorld297 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld298
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD298_SIZE		12


typedef struct HelloWorld298 {
	uint32_t index;
	int32_t message;
} HelloWorld298;


void HelloWorld298_init(HelloWorld298 *sample);


bool HelloWorld298_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld298 *topic);

bool HelloWorld298_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld298 *topic);

uint32_t HelloWorld298_topic_max_size(uint32_t size);
HelloWorld298 *HelloWorld298_create(void);

void HelloWorld298_delete(HelloWorld298 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: HelloWorld299
 * --------------------------------------------------------------------------
 */
#define	HELLOWORLD299_SIZE		12


typedef struct HelloWorld299 {
	uint32_t index;
	int32_t message;
} HelloWorld299;


void HelloWorld299_init(HelloWorld299 *sample);


bool HelloWorld299_deserialize_topic(struct mvbs_cdr *cdr,
						HelloWorld299 *topic);

bool HelloWorld299_serialize_topic(struct mvbs_cdr *cdr,
						HelloWorld299 *topic);

uint32_t HelloWorld299_topic_max_size(uint32_t size);
HelloWorld299 *HelloWorld299_create(void);

void HelloWorld299_delete(HelloWorld299 *sample);

/* --------------------------------------------------------------------------
 *  All of New Function declarations: AgentHelloWorld
 * --------------------------------------------------------------------------
 */
#define	AGENTHELLOWORLD_SIZE		20


typedef struct AgentHelloWorld {
	uint64_t index;
	uint64_t sn;
} AgentHelloWorld;


void AgentHelloWorld_init(AgentHelloWorld *sample);


bool AgentHelloWorld_deserialize_topic(struct mvbs_cdr *cdr,
						AgentHelloWorld *topic);

bool AgentHelloWorld_serialize_topic(struct mvbs_cdr *cdr,
						AgentHelloWorld *topic);

uint32_t AgentHelloWorld_topic_max_size(uint32_t size);
AgentHelloWorld *AgentHelloWorld_create(void);

void AgentHelloWorld_delete(AgentHelloWorld *sample);


#endif /* __MVBS_VBSLITE_PERF_H__ */