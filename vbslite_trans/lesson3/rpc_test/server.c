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

#include <mvbs/utils/log.h>
#include <rpc/rpc.h>
#include <calculatorRpcParams.h>
#include <calculatorRpcServer.h>

#if defined(TARGET_PRODUCT_LINUX) || defined(TARGET_PRODUCT_J6M_ACORE) || defined(TARGET_PRODUCT_MINGW)
#include <mvbs_aux/mvbs_aux.h>
#endif

#include "config.h"

#ifdef	TARGET_PRODUCT_MINGW
#include <windows.h>
#endif

#define TEST_CNT 1000
#define EVENT_CYCLE_MS 500
#define MVBS_LOOP_CYCLE_MS 5

#define MVBS_TEST_CONTINUE		1
#define MVBS_TEST_PASS			0
#define MVBS_TEST_AGAIN			1
#define MVBS_TEST_FAIL			-1

static int rpc_ok_cnt			= 0;
static struct rpc_server *srv	= NULL;

#define BUF_SIZE		256

int MVBS_calculator_add_svc(MVBS_calculator_add_in *req_type, MVBS_calculator_add_out *res_type)
{
	res_type->ret = req_type->a + req_type->b;

	pr_info("add(%d, %d) = %d", req_type->a, req_type->b, res_type->ret);

	rpc_ok_cnt++;

	return RPC_SVC_STOP;
}

static int app_loop(unsigned long timercnt_ms)
{
	static char buf[BUF_SIZE];

	(void)(timercnt_ms);

	rpc_server_recv_loop(srv, buf, BUF_SIZE);

	if (rpc_ok_cnt > TEST_CNT) {
		rpc_server_destroy(srv);
		pr_info("server exit");
		return MVBS_TEST_PASS;
	}

	return MVBS_TEST_CONTINUE;
}

static int app_init(int argc, char *argv[])
{
	(void)(argc);
	(void)(argv);

	extern int32_t mvbs_netio_init();
	extern void mvbs_mm_init();

	mvbs_netio_init();
	mvbs_mm_init();


	srv = rpc_server_new(RPC_SRV_PORT, RPC_SRV_CNCT, calculator_rpc_server_svc_cb);
	if (srv == NULL)
		return MVBS_TEST_FAIL;

	return MVBS_TEST_PASS;
}

#define MVBS_APP_LOOP_PERIOD_MS			5

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	int ret;
	struct mvbs_event_loop		*loop		= NULL;

	unsigned long			mvbs_app_loop_cnt = 0;
	uint32_t			event		  = 0;

	#ifdef TARGET_PRODUCT_MINGW
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	#endif

	loop = mvbs_event_loop_create(MVBS_APP_LOOP_PERIOD_MS);

	do {
		ret = app_init(0, NULL);
		if (ret != MVBS_TEST_FAIL) {
			break;
		}
	} while (true);

	while (true) {
		event = mvbs_event_loop_wait(loop);

		if (event & MVBS_EV_TIMER) {

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
