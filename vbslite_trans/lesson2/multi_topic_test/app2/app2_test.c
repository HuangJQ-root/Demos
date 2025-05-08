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

#include <mvbs/errno.h>
#include <mvbs/utils/cdefs.h>
#include <mvbs/rte/Rte_Dds_Adaptor.h>

#include <mvbs/utils/mm.h>
#include <mvbs/utils/mm_stat.h>
#include <mvbs/utils/log.h>
#include <mvbs/utils/time.h>

#include "HelloWorldPlugin.h"

#if defined(TARGET_PRODUCT_LINUX) || defined(TARGET_PRODUCT_J6M_ACORE) || defined(TARGET_PRODUCT_MINGW)
#include <mvbs_aux/mvbs_aux.h>
#endif
 
#ifdef TARGET_PRODUCT_MINGW
#include <windows.h>
#endif

#ifndef UINT_MAX
#define UINT_MAX			(uint32_t)(-1)
#endif

#define MVBS_LOOP_CYCLE_MS		5

#define TOTAL_TIME_MS			72*60*60*1000		// 72h
#define READER_DUMP_PER_CNT		1000
#define WRITER_DUMP_PER_CNT		1000

#define MVBS_TEST_CONTINUE		1
#define MVBS_TEST_PASS			0
#define MVBS_TEST_AGAIN			1
#define MVBS_TEST_FAIL			-1

#define reader_topic_index(x)		x##_r_idx
#define writer_topic_index(x)		x##_w_idx

typedef void (*sample_init_t)(void *);


/* The following code lines are for reader topic. */

enum {
	reader_topic_index(MVBS_topic1),
	reader_topic_index(MVBS_topic2),
	reader_topic_index(MVBS_topic3),
	reader_topic_index(MVBS_topic4),
	reader_topic_index(MVBS_topic5),
};

struct reader_meta_info {
	Rte_Dds_Reader	r;
	const char	*topic;
	void		*sample;
	uint16_t	period_ms;
	uint16_t	match_count;
	uint32_t	total_count;
	uint32_t	recv_count;
	uint32_t	fail_count;

	sample_init_t	init;

	void (*fn)(void *);

	uint32_t	print_per_cnt;
};


static void MVBS_topic1_cb(void *sample)
{
	MVBS_HelloWorld *data = (MVBS_HelloWorld*)sample;

	(void)data;
}

static void MVBS_topic2_cb(void *sample)
{
	MVBS_BasicTypeStruct *data = (MVBS_BasicTypeStruct*)sample;

	(void)data;
}

static void MVBS_topic3_cb(void *sample)
{
	MVBS_sdatatype *data = (MVBS_sdatatype*)sample;

	(void)data;
}

static void MVBS_topic4_cb(void *sample)
{
	MVBS_ComplexDataType *data = (MVBS_ComplexDataType*)sample;

	(void)data;
}

static void MVBS_topic5_cb(void *sample)
{
	StructSize50 *data = (StructSize50*)sample;

	(void)data;
}

#define READER_META_INFO(name, type, cb, period)		\
	[reader_topic_index(name)] = {				\
		.topic		= #name,			\
		.sample		= (type [1]) {},		\
		.period_ms	= period,			\
		.match_count	= 0,				\
		.recv_count	= 0,				\
		.fail_count	= 0,				\
		.init		= (sample_init_t)(type##_init),	\
		.fn		= cb,				\
	}

static struct reader_meta_info subscriber_list[] = {
	READER_META_INFO(MVBS_topic1, MVBS_HelloWorld, MVBS_topic1_cb, 100),
	READER_META_INFO(MVBS_topic2, MVBS_BasicTypeStruct, MVBS_topic2_cb, 100),
	READER_META_INFO(MVBS_topic3, MVBS_sdatatype, MVBS_topic3_cb, 100),
	READER_META_INFO(MVBS_topic4, MVBS_ComplexDataType, MVBS_topic4_cb, 100),
	READER_META_INFO(MVBS_topic5, StructSize50, MVBS_topic5_cb, 100),
};

static void subscriber_init(Rte_Dds_Participant ptcp)
{
	struct reader_meta_info *info;

	for (uint8_t i = 0; i < ARRAY_SIZE(subscriber_list); i++) {
		info = &subscriber_list[i];

		info->r = Rte_Dds_GetReader(ptcp, info->topic);
		info->init(info->sample);

		info->recv_count	= 0;
		info->fail_count	= 0;

		if (info->period_ms != 0) {
			info->print_per_cnt = 1000 / info->period_ms;	/* print per 1s */
		} else {
			info->print_per_cnt = 10;
		}

		Rte_Dds_Reader_Set_Private(info->r, info);
	}
}

void Rte_Dds_RxIndication(Rte_Dds_Reader r, Rte_Dds_Instance inst)
{
	(void)inst;

	struct sample_info		sinfo;
	struct reader_meta_info 	*info;
	Rte_Dds_TopicData        	data;

	info = Rte_Dds_Reader_Get_Private(r);

	Rte_Dds_PackData(&data, info->sample);

	if (RTE_DDS_RETCODE_OK == Rte_Dds_RxData(r, true, &data, &sinfo)) {
		info->recv_count++;

		if (info->fn != NULL) {
			info->fn(info->sample);
		}

		if ((info->recv_count % info->print_per_cnt) == 0) {
			pr_info("Get a sample from: [%s], sample count: %ld, "
				"transport_type: %d.",
				info->topic, info->recv_count,
				sinfo.locator_kind);
		}
	} else {
		info->fail_count++;

		pr_info("Failed to read sample from [%s], fail count:%ld",
						info->topic, info->recv_count);
	}
}

void Rte_Dds_Reader_OnMatch(Rte_Dds_Reader r,
			    const Rte_Dds_Reader_MatchStatus *status)
{
	struct reader_meta_info *info;

	info = Rte_Dds_Reader_Get_Private(r);

	info->match_count = status->current_count;

	pr_warn("topic:%s, match_count:%d", info->topic, info->match_count);
}

static bool get_all_reader_match_status(void)
{
	struct reader_meta_info *info;

	for (uint8_t i = 0; i < ARRAY_SIZE(subscriber_list); i++) {
		info = &subscriber_list[i];

		if (info->match_count == 0) {
			return false;
		}
	}

	return true;
}
/* The following code lines are for writer topic. */

enum {
	writer_topic_index(MVBS_topic6),
	writer_topic_index(MVBS_topic7),
	writer_topic_index(MVBS_topic8),
	writer_topic_index(MVBS_topic9),
	writer_topic_index(MVBS_topic10),
};

struct writer_meta_info {
	Rte_Dds_Writer	w;
	const char	*topic;
	uint8_t		match_count;
	void		*sample;

	unsigned long	period_next;	/* FIXME: Init value maybe shouldn't be zero. */
	uint32_t	period_ms;
	uint32_t	phase_ms;

	uint32_t	public_count;	/* Only for test */
	uint32_t	send_count;

	sample_init_t	init;
};

#define WRITER_META_INFO(name, type, period)			\
	[writer_topic_index(name)] = {				\
		.topic		= #name,			\
		.match_count	= 0,				\
		.sample		= (type [1]) {},		\
		.init		= (sample_init_t)(type##_init),	\
		.period_ms	= period,			\
		.period_next	= 0,				\
	}

static struct writer_meta_info publisher_list[] = {
	WRITER_META_INFO(MVBS_topic6, MVBS_HelloWorld1, 100),
	WRITER_META_INFO(MVBS_topic7, MVBS_HelloWorld2, 100),
	WRITER_META_INFO(MVBS_topic8, MVBS_HelloWorld3, 100),
	WRITER_META_INFO(MVBS_topic9, MVBS_HelloWorld4, 100),
	WRITER_META_INFO(MVBS_topic10, MVBS_HelloWorld5, 100),
};

/* Greatest Common Divisor */
static uint32_t gcd(uint32_t a, uint32_t b)
{
	uint32_t temp;

	while (b != 0) {
		temp = b;

		b = a % b;
		a = temp;
	}

	return a;
}

/* Update the phase */
static void writer_meta_info_update_phase(struct writer_meta_info *info_list,
								int info_cnt)
{
	uint32_t min_conflicts;
	uint32_t best_phase;

	for (int i = 0; i < info_cnt; ++i) {
		info_list[i].period_ms = info_list[i].period_ms / MVBS_LOOP_CYCLE_MS;
	}


	for (int i = 0; i < info_cnt; ++i) {
		min_conflicts	= UINT_MAX;
		best_phase	= 0;

		// for each available phase (0 <= d < k)
		for (uint32_t d = 0; d < info_list[i].period_ms; ++d) {
			uint32_t conflicts = 0;

			// check the all available phase
			for (int j = 0; j < i; ++j) {
				uint32_t tmp_gcd;

				tmp_gcd = gcd(info_list[i].period_ms,
					      info_list[j].period_ms);

				if ((d - info_list[j].phase_ms) % tmp_gcd == 0) {
					// increase the count of conflicts.
					conflicts++;
				}
			}

			// select the best phase
			if (conflicts < min_conflicts ||
			   (conflicts == min_conflicts && d < best_phase)) {
				min_conflicts = conflicts;
				best_phase    = d;
			}
		}

		info_list[i].phase_ms = best_phase; // store the result
	}

	for (int i = 0; i < info_cnt; ++i) {
		info_list[i].period_ms = info_list[i].period_ms * 5;
		info_list[i].phase_ms  = info_list[i].phase_ms * 5;

		info_list[i].period_next  = info_list[i].phase_ms;
	}
}

static void publisher_init(Rte_Dds_Participant ptcp, uint32_t ms)
{
	struct writer_meta_info *info;

	for (uint8_t i = 0; i < ARRAY_SIZE(publisher_list); i++) {
		info = &publisher_list[i];

		info->w = Rte_Dds_GetWriter(ptcp, info->topic);
		info->init(info->sample);

		if (info->period_ms != 0) {
			info->public_count = ms / info->period_ms;
		} else {
			info->public_count = 0;
		}

		Rte_Dds_Writer_Set_Private(info->w, info);
	}

	writer_meta_info_update_phase(publisher_list,
					ARRAY_SIZE(publisher_list));
}

void Rte_Dds_Writer_OnMatch(Rte_Dds_Writer w,
			    const Rte_Dds_Writer_MatchStatus *status)
{
	struct writer_meta_info *info;

	info = Rte_Dds_Writer_Get_Private(w);

	info->match_count = status->current_count;

	pr_warn("topic:%s, match_count:%d", info->topic, info->match_count);
}

static bool get_all_writer_match_status(void)
{
	struct writer_meta_info *info;

	for (uint8_t i = 0; i < ARRAY_SIZE(publisher_list); i++) {
		info = &publisher_list[i];

		if (info->match_count == 0) {
			return false;
		}
	}

	return true;
}

static int writer_topic_public(struct writer_meta_info *info)
{
	Rte_Dds_TopicData        data;

	Rte_Dds_PackData(&data, info->sample);

	if (RTE_DDS_RETCODE_OK == Rte_Dds_TxData(info->w, &data, NULL)) {
		info->send_count++;

		if (info->send_count % WRITER_DUMP_PER_CNT == 0) {
			pr_info("Success to send sample of Topic [%s]: [%d].",
						info->topic, info->send_count);
		}
	} else {
		pr_info("Fail to send sample of Topic [%s].", info->topic);
	}

	return MVBS_TEST_CONTINUE;
}

static int writers_topic_loop(void)
{
	static unsigned long timer_ms;
	struct writer_meta_info *info;
	uint16_t topic_done_cnt = 0;

	for(uint8_t i = 0; i < ARRAY_SIZE(publisher_list); i++) {
		info = &publisher_list[i];

		if (info->public_count == 0) {
			topic_done_cnt++;

			continue ;
		}

		if (time_after_eq(timer_ms, info->period_next)) {
			(void)writer_topic_public(info);

			/* FIXME:
			 * Should the period_next be changed only public success?
			 */
			info->period_next = timer_ms + info->period_ms;

			info->public_count--;
		}
	}

	timer_ms += MVBS_LOOP_CYCLE_MS;

	if (topic_done_cnt < ARRAY_SIZE(publisher_list)) {
		return MVBS_TEST_CONTINUE;
	} else {
		pr_info("Writer test finished.");
		return MVBS_TEST_PASS;
	}
}

static int app_loop(unsigned long timer_ms)
{
	static uint16_t	stage = 0;

	int32_t		tmp_sec = 0;
	uint32_t	tmp_nsec = 0;

	bool		reader_all_match;
	bool		writer_all_match;

	int ret = MVBS_TEST_CONTINUE;

	(void)timer_ms;

	switch (stage) {
	case 0:
		reader_all_match = get_all_reader_match_status();
		writer_all_match = get_all_writer_match_status();

		if (reader_all_match && writer_all_match) {
			mvbs_get_time(&tmp_sec, &tmp_nsec);

			pr_info("All topic are match, current tmp_sec:%d.tmp_nsec:%d",
								   tmp_sec, tmp_nsec);
			stage = 1;
		}

		break ;

	case 1:
		ret = writers_topic_loop();
		break ;

	default:
		break;
	}

	return ret;
}

static void *app_init(int argc, char *argv[])
{
	int32_t		tmp_sec  = 0;
	uint32_t	tmp_nsec = 0;

	(void)argc;
	(void)argv;

	extern Rte_Dds_Participant Rte_Dds_GetParticipant(void);
	Rte_Dds_Participant ptcp = Rte_Dds_GetParticipant();

	mvbs_get_time(&tmp_sec, &tmp_nsec);

	pr_info("MVBS init success, current tmp_sec:%d.tmp_nsec:%d",
							tmp_sec, tmp_nsec);

	if (Rte_Dds_Init(ptcp) != RTE_DDS_RETCODE_OK) {
		return NULL;
	}

	subscriber_init(ptcp);
	publisher_init(ptcp, TOTAL_TIME_MS);

	pr_info("Allocated %ld bytes in heap.", dynamic_mem_get_max_used());

	return ptcp;
}

#if defined(TARGET_PRODUCT_LINUX) || defined(TARGET_PRODUCT_J6M_ACORE) || defined(TARGET_PRODUCT_MINGW)
#define MVBS_APP_LOOP_PERIOD_MS			5

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	struct mvbs_event_loop	*loop		= NULL;
	Rte_Dds_Participant	ptcp		= NULL;

	unsigned long		mvbs_app_loop_cnt = 0;
	uint32_t		recv_max_pkg	  = 0;
	uint32_t		event		  = 0;
	int ret;

	#ifdef TARGET_PRODUCT_MINGW
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	#endif

	loop = mvbs_event_loop_create(MVBS_APP_LOOP_PERIOD_MS);

	do {
		ptcp = app_init(0, NULL);
		if (ptcp != NULL) {
			break;
		}
	} while (true);

	while (true) {
		event = mvbs_event_loop_wait(loop);

		if (event & MVBS_EV_RECV) {
			if (ptcp != NULL) {
				Rte_Dds_Ptcp_Recv_Handler(ptcp, recv_max_pkg);
			}
		}

		if (event & MVBS_EV_TIMER) {
			if (ptcp != NULL) {
				Rte_Dds_Ptcp_Timer_Handler(ptcp);
			}

			mvbs_app_loop_cnt++;

			app_loop(mvbs_app_loop_cnt * MVBS_APP_LOOP_PERIOD_MS);
		}
	}

#ifdef TARGET_PRODUCT_MINGW
	WSACleanup();
#endif

	return ret;
}
#else
void dds_5ms()
{
	#define MVBS_STAGE_INIT         0
	#define MVBS_STAGE_LOOP         1

	static unsigned long	timer_ms;
	static int mvbs_status = MVBS_STAGE_INIT;
	static Rte_Dds_Participant ptcp;

	uint32_t recv_max_pkg = 0;

	timer_ms += MVBS_LOOP_CYCLE_MS;

	switch (mvbs_status) {
	case MVBS_STAGE_INIT:
		ptcp = app_init(0, NULL);
		if (ptcp != NULL)
			mvbs_status = MVBS_STAGE_LOOP;

		break;

	case MVBS_STAGE_LOOP:
		Rte_Dds_Ptcp_Timer_Handler(ptcp);
		Rte_Dds_Ptcp_Recv_Handler(ptcp, recv_max_pkg);

		app_loop(timer_ms);
		break;
	}
}
#endif
