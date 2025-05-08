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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mvbs/rte/Rte_Dds_Adaptor.h>
#include <HelloWorldPlugin.h>

#if defined(TARGET_PRODUCT_LINUX) || defined(TARGET_PRODUCT_J6M_ACORE) || defined(TARGET_PRODUCT_MINGW)
#include <mvbs_aux/mvbs_aux.h>
#endif

#ifdef	TARGET_PRODUCT_MINGW
#include <windows.h>
#endif

#define TEST_CNT 500
#define EVENT_CYCLE_MS 500
#define MVBS_LOOP_CYCLE_MS 5

#define MVBS_TEST_CONTINUE		1
#define MVBS_TEST_PASS			0
#define MVBS_TEST_FAIL			-1

static int gtx_ok_cnt;
static MVBS_HelloWorld sample1;
static Rte_Dds_TopicData data_w;
static Rte_Dds_Writer w;
static Rte_Dds_TopicId topic_w = DEF_RTE_DDS_TOPIC("domain_0_topic_0Topic", 0 );


static int on_event()
{
	Rte_Dds_TopicStats stats;

	memset(&stats, 0, sizeof(Rte_Dds_TopicStats));
	if (Rte_Dds_GetWriterStats(w, &stats) != RTE_DDS_RETCODE_OK) {
		pr_err(ERR_FAULT, "peers match failed!");
	}

	if (stats.remotes_online > 0) {
		sprintf(sample1.msg, "msg (%d) from node1_w1", gtx_ok_cnt);
		Rte_Dds_ReturnType ret = Rte_Dds_TxData(w, &data_w, NULL);
		if (ret == RTE_DDS_RETCODE_OK) {
			gtx_ok_cnt++;
			pr_info("--------tx count:%ld-------, \n", gtx_ok_cnt);
		} else {
			pr_info("Rte_Dds_TxData failed!\n");
		return MVBS_TEST_FAIL;
		}
	}
	if (gtx_ok_cnt > TEST_CNT) {
		return MVBS_TEST_PASS;
	}


    return MVBS_TEST_CONTINUE;
}


static int app_loop(unsigned long timer_ms)
{
    int ret;
    static int loop_cnt;

    (void)timer_ms;

    if (++loop_cnt >= EVENT_CYCLE_MS / MVBS_LOOP_CYCLE_MS) {
        loop_cnt = 0;
        ret = on_event();
    } else {
        ret = MVBS_TEST_CONTINUE;
    }

    return ret;
}


static Rte_Dds_Participant app_init(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	extern Rte_Dds_Participant Rte_Dds_GetParticipant();
	Rte_Dds_Participant ptcp = Rte_Dds_GetParticipant();
	if (Rte_Dds_Init(ptcp) != RTE_DDS_RETCODE_OK) {
		pr_err(ERR_INVALID,"Rte_Dds_Init fail !");
		return NULL;
	}
	pr_info("Rte_Dds_Init OK!.\n");

	MVBS_HelloWorld_init(&sample1);
	Rte_Dds_PackData(&data_w, &sample1);
	w = Rte_Dds_GetWriter(ptcp, topic_w.name);

	return ptcp;
}

#define MVBS_APP_LOOP_PERIOD_MS			5

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	int ret;
	struct mvbs_event_loop		*loop		= NULL;
	Rte_Dds_Participant		ptcp		= NULL;

	unsigned long			mvbs_app_loop_cnt = 0;
	uint32_t			recv_max_pkg	  = 0;
	uint32_t			event		  = 0;

	#ifdef TARGET_PRODUCT_MINGW
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	#endif

	setbuf(stdout, NULL);

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

			ret = app_loop(mvbs_app_loop_cnt * MVBS_APP_LOOP_PERIOD_MS);
			if (ret != MVBS_TEST_CONTINUE) {
				break ;
			}
		}
	}
	if (ret == MVBS_TEST_PASS) {
		pr_info("~~~ Run successfully ~~~");
	} else {
		pr_info("~~~ Run failure ~~~");
	}

#ifdef TARGET_PRODUCT_MINGW
	WSACleanup();
#endif
	return ret;
}


