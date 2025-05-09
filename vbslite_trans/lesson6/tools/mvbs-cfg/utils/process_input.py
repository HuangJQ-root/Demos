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

import itertools

from utils.read_xml import read_from_xml
from utils.calculate_timer import count_timer
from utils.merge_xml import merge_render_data
from utils.check_input import gen_render_data

import os


data_lst = []


def divide_time_by_two(time_list):
    seconds, nanoseconds = time_list
    total_nanoseconds = seconds * 1000000000 + nanoseconds

    half_nanoseconds = total_nanoseconds // 2
    new_seconds = half_nanoseconds // 1000000000
    new_nanoseconds = half_nanoseconds % 1000000000

    return [new_seconds, new_nanoseconds]

def pre_init(cfg_file, transport, host):
    if not os.path.exists(cfg_file):
        raise Exception('Input config file not exist')

    if cfg_file.split('.')[-1] != 'xml':
        raise Exception('Only [.xml] file suffixes are supported')

    data = read_from_xml(cfg_file)
    data_lst.append(gen_render_data(data, transport, host))

    if len(data_lst) == 2:
        try:
            merge_render_data(data_lst[0], data_lst.pop())
        except Exception as e:
            raise Exception(f'Merge Conflicts: {str(e)}')

    return data_lst[0]


def post_init(master_data, init_intf_name):
    writers = master_data['participant'].get('writers', [])
    readers = master_data['participant'].get('readers', [])

    # set agent_flag
    for writer in writers:
        if 'agent_flag' not in writer:
            writer['agent_flag'] = 0
        else:
            if writer['agent_flag'] == 'true':
                writer['agent_flag'] = 1
            elif writer['agent_flag'] == 'false':
                writer['agent_flag'] = 0

    for reader in readers:
        if 'agent_flag' not in reader:
            reader['agent_flag'] = 0
        else:
            if reader['agent_flag'] == 'true':
                reader['agent_flag'] = 1
            elif reader['agent_flag'] == 'false':
                reader['agent_flag'] = 0

    # static peers
    master_data['remote_reader'] = sum([len(writer.get('static_peers', [])) for writer in writers])
    master_data['remote_writer'] = sum([len(reader.get('static_peers', [])) for reader in readers])

    # enable local
    topic_lst = [peer['topic'] for peer in itertools.chain(writers, readers)]
    master_data['enable_local'] = len(topic_lst) != len(set(topic_lst))

    # build plugin_array
    type_lst = [peer['type'].replace('::', '_') for peer in itertools.chain(writers, readers)]
    master_data['type_lst'] = sorted(set(type_lst), key=type_lst.index)

    # build e2e timeout qos
    for writer in writers:
        qos = master_data['qos_lst'][writer['qos']]
        if qos['e2e_policy']['enable'] == 'true' and writer['sendtype'] == 'OnChange':
                qos['liveliness']['kind'] = qos['e2e_policy']['e2e_liveliness_kind']
                qos['liveliness']['lease_duration'] = qos['e2e_policy']['e2e_liveliness_lease_duration']
                qos['liveliness']['period'] = divide_time_by_two(qos['e2e_policy']['e2e_liveliness_lease_duration'])
        elif qos['e2e_policy']['enable'] == 'true' and writer['sendtype'] == 'Periodic':
                duration = writer['period'] * qos['e2e_policy']['e2e_deadline_counter']
                seconds = duration // 1000
                nanoseconds = (duration % 1000) * 1000000
                qos['deadline']['period'] = [seconds, nanoseconds]

    for reader in readers:
        qos = master_data['qos_lst'][reader['qos']]
        if qos['e2e_policy']['enable'] == 'true' and reader['sendtype'] == 'OnChange':
                qos['liveliness']['kind'] = qos['e2e_policy']['e2e_liveliness_kind']
                qos['liveliness']['lease_duration'] = qos['e2e_policy']['e2e_liveliness_lease_duration']
                qos['liveliness']['period'] = divide_time_by_two(qos['e2e_policy']['e2e_liveliness_lease_duration'])
        elif qos['e2e_policy']['enable'] == 'true' and reader['sendtype'] == 'Periodic':
                duration = reader['period'] * qos['e2e_policy']['e2e_deadline_counter']
                seconds = duration // 1000
                nanoseconds = (duration % 1000) * 1000000
                qos['deadline']['period'] = [seconds, nanoseconds]

    # timer number
    master_data['timer_num'] = count_timer(master_data['participant']['max_remote_participants'])

    # network setting
    transport_udpv4 = master_data.get('transport_udpv4', [])

    if transport_udpv4 and len(transport_udpv4) > 5:
        raise Exception('The maximum of network member is 5.')

    # for test init
    if init_intf_name is None:
        master_data["__intf_name__"] = "Rte_Dds_GetParticipant"
    else:
        master_data["__intf_name__"] = init_intf_name
