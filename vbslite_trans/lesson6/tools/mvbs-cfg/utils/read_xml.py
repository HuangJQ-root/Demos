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


import xmltodict
import os
import re


type_to_lst = [
    'period',
    'lease_duration',
    'e2e_liveliness_lease_duration'
]

type_to_int = [
    'times',
    'value',
    'e2e_p04_min_data_length',
    'e2e_p04_max_data_length',
    'e2e_p04_max_delta_counter',
    'domain_id',
    'local_rx_buffer',
    'udp_rx_buffer',
    'object_id',
    'e2e_deadline_counter',

    'per_samples',
    'depth',
    'max_samples',
    'max_instances',
    'max_samples_per_instance',
    'max_remote_participants',
    'max_remote_peers',
    ]

force_lst_tag = [
    'idl',
    'master',
    'backup',
    'reader',
    'writer',
    'participant',
    'static_peers',
    'udp',
    'ipc',
    'transport',
]


def find_key_in_dict(dic):
    for key, value in dic.items():
        if key in type_to_int:
            dic[key] = int(value)
        if key in type_to_lst:
            dic[key] = [int(x) for x in value.split(' ')]
        if isinstance(value, dict):
            find_key_in_dict(value)
        if isinstance(value, list):
            find_key_in_list(value)


def find_key_in_list(lst):
    for item in lst:
        if isinstance(item, dict):
            find_key_in_dict(item)
        if isinstance(item, list):
            find_key_in_list(item)


def replacer(match, base_dir):
    path = re.findall(r'<include>(.*?)</include>', match.group())[0]
    file_path = os.path.abspath(os.path.join(base_dir, path))
    with open(file_path, 'r', encoding='utf-8') as f:
        return f.read()


def read_from_xml(file):
    with open(file, 'r', encoding='utf-8') as f:
        content = f.read()

    path = os.path.abspath(os.path.join(file, '../'))
    xml_text = re.sub('<include>.*?</include>', lambda match: replacer(match, path), content)

    xml_dict = xmltodict.parse(xml_text, force_list=force_lst_tag)
    xml_dict = xml_dict['dds']
    find_key_in_dict(xml_dict)

    return xml_dict
