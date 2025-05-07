#!/usr/bin/env python

# Copyright (c) 2025 Li Auto Inc. and its affiliates
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


interval_limit = [2147483647, 4294967295]

timer_num = {
    "lifespan": 0,
    "deadline": 0,
    "reliable": 0,
    # liveliness
    "QOS_LIVE_MANUAL_BY_TOPIC": 0,
    "QOS_LIVE_AUTOMATIC": {"w": 0, "r": 0},
    "QOS_LIVE_MANUAL_BY_PTCP": {"w": 0, "r": 0},
}


def extract_timer_config(kind, qos):
    lifespan = qos["lifespan"]["period"]
    if lifespan != interval_limit:
        timer_num["lifespan"] += 1

    deadline = qos["deadline"]["period"]
    if deadline != interval_limit:
        timer_num["deadline"] += 1

    if kind == "w" and qos["reliability"]["kind"] == "RELIABLE":
        timer_num["reliable"] += 1

    qos_kind = qos["liveliness"]["kind"]
    liveliness = qos["liveliness"]["lease_duration"]
    if liveliness != interval_limit:
        if qos_kind == "QOS_LIVE_MANUAL_BY_TOPIC":
            timer_num[qos_kind] += 1
        else:
            timer_num[qos_kind][kind] += 1


def count_timer(remote_cnt):
    # Discovery count
    #   SPDP                  cnt       1
    #   Discover liveliness   cnt       remote_node
    # EDP_CNT           timer_cnt       2
    # WLP_CNT           timer_cnt       1
    # 4 = 1 + 2 + 1

    if timer_num["QOS_LIVE_AUTOMATIC"]["w"] > 0:
        timer_num["QOS_LIVE_AUTOMATIC"]["w"] = 1
    if timer_num["QOS_LIVE_MANUAL_BY_PTCP"]["w"] > 0:
        timer_num["QOS_LIVE_MANUAL_BY_PTCP"]["w"] += 1

    timer_num["base"] = 4
    timer_num["remote"] = remote_cnt
    timer_num["QOS_LIVE_AUTOMATIC"] = sum(timer_num["QOS_LIVE_AUTOMATIC"].values())
    timer_num["QOS_LIVE_MANUAL_BY_PTCP"] = sum(timer_num["QOS_LIVE_MANUAL_BY_PTCP"].values())

    return sum(timer_num.values())
