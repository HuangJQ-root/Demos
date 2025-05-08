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
#include <calculatorRpcClient.h>
#include <calculatorRpcParams.h>

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
static int test_status			= MVBS_TEST_CONTINUE;
static struct rpc_client *cli	= NULL;


static int check_a = 0;
static int check_b = 0;
static MVBS_calculator_add_in req_type = {0, 0};

#define BUF_SIZE			256

static int add_cb(MVBS_calculator_add_out *res_type, int32_t rpc_errno)
{
	if (rpc_errno == RPC_ERRNO_TIMEOUT) {
		pr_info("Add Operation Timeout");
		test_status = MVBS_TEST_FAIL;
		return 0;
	}

	if (res_type->ret == check_a + check_b) {
		pr_info("add(%d, %d) = %d, success", check_a, check_b, res_type->ret);
		rpc_ok_cnt++;
		check_a++;
		check_b++;
	} else {
		pr_info("add(%d, %d) = %d, fail",  check_a, check_b, res_type->ret);
		test_status = MVBS_TEST_FAIL;
	}

	return 0;
}

static int app_loop(unsigned long timercnt_ms)
{
	static int wait;
	static int connect_cnt;
	static char buf[BUF_SIZE];

	if (connect_cnt >= 0) {
		if (rpc_client_connect(cli) < 0) {
			if (connect_cnt++ > 20)
				return MVBS_TEST_FAIL;
			else
				return MVBS_TEST_CONTINUE;
		}
		connect_cnt = -1;
	}

	if (wait-- > 0) {
		rpc_client_recv_loop(cli, timercnt_ms, buf, BUF_SIZE);
		return MVBS_TEST_CONTINUE;
	}

	MVBS_calculator_add(cli, &req_type, add_cb, -1);

	req_type.a++;
	req_type.b++;

	rpc_client_recv_loop(cli, timercnt_ms, buf, BUF_SIZE);

	wait = 20;

	if (rpc_ok_cnt > TEST_CNT) {
		rpc_client_destroy(cli);
		pr_info("client exit");
		test_status = MVBS_TEST_PASS;
	}

	return test_status;
}

static int app_init(int argc, char *argv[])
{
	(void)(argc);
	(void)(argv);
	extern int32_t mvbs_netio_init();
	extern void mvbs_mm_init();

	mvbs_netio_init();
	mvbs_mm_init();

	cli = rpc_client_new(RPC_SRV_ADDR, RPC_SRV_PORT);
	if (cli == NULL)
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
