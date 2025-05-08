#!/usr/bin/env python
# -*- coding: utf-8 -*-

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

from xml.etree import ElementTree as ET
from argparse import ArgumentParser
from xml.dom import minidom
from pathlib import Path

import itertools
import os.path


def prettify_xml(element):
    rough_string = ET.tostring(element, 'utf-8')
    re_parsed = minidom.parseString(rough_string)
    return re_parsed.toprettyxml(indent='\t')


def locate_resource(res_key, lst):
    for element in lst:
        if res_key in prettify_xml(element):
            return element


def add_sub_elements(sub_root, element, dictionary):
    for name, new_name in dictionary.items():
        sub_element = element.find(name)
        if sub_element is not None and sub_element.text:
            new_element = ET.SubElement(sub_root, new_name)
            new_element.text = sub_element.text.strip()


def rewrite_idl(idl_lst, new_root):
    if idl_lst is None:
        return

    for idl in idl_lst:
        element = ET.SubElement(new_root, 'idl')
        element.text = idl.text.strip()


def rewriter_network(root, new_root):
    if root is None:
        return

    mappings = {
        'master': [
            ('host', 'address'),
            ('netmask', 'netmask')
        ],
        'backup': [
            ('address', 'address'),
            ('netmask', 'netmask')
        ],
    }

    for key, maps in mappings.items():
        for element in root.findall(key):
            sub_root = ET.Element(key)
            add_sub_elements(sub_root, element, dict(maps))

            if list(sub_root):
                new_root.append(sub_root)


def rewriter_discovery(root, new_root):
    if root is None:
        return

    mappings = {
        'initial_announcements': [
            ('announce_times', 'times'),
            ('period', 'period')
        ],
        'heartbeat': [
            ('per_max_samples', 'per_samples'),
            ('period', 'period')
        ],
        'liveliness': [
            ('lease_duration', 'lease_duration'),
            ('assert_period', 'period')
        ],
    }

    for key, maps in mappings.items():
        sub_root = ET.Element('announce' if key == 'initial_announcements' else key)
        element = root.find(key)

        if element is not None:
            add_sub_elements(sub_root, element, dict(maps))
        
            if list(sub_root):
                new_root.append(sub_root)


def rewriter_qos(root, new_root, res_info):
    if root is None:
        return

    mappings = {
        'durability': [
            ('kind', 'kind'),
        ],
        'reliability': [
            ('kind', 'kind'),
        ],
        'ownership': [
            ('kind', 'kind'),
        ],
        'ownership_strength': [
            ('value', 'value'),
        ],
        'deadline': [
            ('period', 'period'),
        ],
        'liveliness': [
            ('kind', 'kind'),
            ('lease_duration', 'lease_duration'),
        ],
        'lifespan': [
            ('period', 'period'),
        ],
        'history': [
            ('kind', 'kind'),
            ('depth', 'depth'),
        ],
        'e2e_policy': [
            ('enable', 'enable'),
            ('e2e_p04_min_data_length', 'e2e_p04_min_data_length'),
            ('e2e_p04_max_data_length', 'e2e_p04_max_data_length'),
            ('e2e_p04_max_delta_counter', 'e2e_p04_max_delta_counter'),
        ]
    }

    for peer in itertools.chain(root.findall('reader'), root.findall('writer')):
        new_peer = ET.SubElement(new_root, f'{peer.tag}s')

        add_sub_elements(new_peer, peer, {'key': 'key'})

        qos_name = new_peer.find('key').text.strip() if new_peer.find('key') is not None else 'default'

        for key, maps in mappings.items():
            sub_root = ET.Element(key)
            element = peer.find(key)
            
            if element is not None:
                add_sub_elements(sub_root, element, dict(maps))
            
                if list(sub_root):
                    new_peer.append(sub_root)
        
        history = new_peer.find('history')

        if res_info is None or history is None:
            continue

        if list(history):
            resource = None
            key = peer.find('resource')

            if key is not None and key.text:
                resource = locate_resource(key.text, res_info.findall(f'{peer.tag}s'))
            
            if not resource:
                continue

            for attr in ['max_samples', 'max_instances', 'max_samples_per_instance']:
                value = resource.find(attr)
                if value is not None and value.text:
                    element = ET.SubElement(history, attr)
                    element.text = value.text.strip()

            if resource.find('max_remote_readers') is not None:
                max_remote_peers = resource.find('max_remote_readers')
            elif resource.find('max_remote_writers') is not None:
                max_remote_peers = resource.find('max_remote_writers')
            else:
                continue

            peer_resource[f'{peer.tag}s_{qos_name}'] = max_remote_peers


def rewriter_participant(root, new_root, res_info):
    if root is None:
        return

    participant_mappings = {
        'key': 'name',
        'domain_id': 'domain_id',
        'discovery': 'discovery',
        'check_crc': 'check_crc',
    }

    peer_mappings = {
        'key': 'key',
        'topic': 'topic',
        'type': 'type',
        'qos': 'qos',
        'backup_enabled': 'net_redundancy',
        'rtps_object_id': 'object_id',
    }

    sub_peer_mappings = {
        'sub_object_id': 'object_id',
        'pub_object_id': 'object_id',
        'qos': 'qos',
    }

    add_sub_elements(new_root, root, participant_mappings)

    writer_participant_res(root, new_root, res_info)

    for peer in itertools.chain(root.findall('reader'), root.findall('writer')):
        new_peer = ET.SubElement(new_root, peer.tag)

        add_sub_elements(new_peer, peer, peer_mappings)

        qos_name = new_peer.find('qos').text.strip() if new_peer.find('qos') is not None else 'default'
        element = ET.SubElement(new_peer, 'max_remote_peers')

        if f'{peer.tag}_{qos_name}' in peer_resource:
            element.text = peer_resource[f'{peer.tag}_{qos_name}'].text.strip()
        else:
            new_peer.remove(element)

        for sub_peer in itertools.chain(peer.findall('dpse_peer_reader'), peer.findall('dpse_peer_writer')):
            new_sub_peer = ET.SubElement(new_peer, 'static_peers')

            add_sub_elements(new_sub_peer, sub_peer, sub_peer_mappings)


def writer_participant_res(root, new_root, res_info):
    mappings = {
        'remote_node': 'max_remote_participants',
        'local_rx_buffer': 'local_rx_buffer',
        'udp_rx_buffer': 'udp_rx_buffer',
    }

    if res_info is None:
        return

    resource = None
    key = root.find('resource')
    if key is not None and key.text:
        resource = locate_resource(key.text, res_info.findall('nodes'))

    if resource is None:
        return

    add_sub_elements(new_root, resource, mappings)


def writer_new_xml(tag_dict):
    # root
    new_root = ET.Element('dds')

    # idl
    rewrite_idl(tag_dict['idl'], new_root)

    # network
    network = ET.Element('network')
    rewriter_network(tag_dict['network'], network)
    if list(network):
        new_root.append(network)

    # discovery
    discovery = ET.Element('discovery')
    rewriter_discovery(tag_dict['discovery'], discovery)
    if list(discovery):
        new_root.append(discovery)

    # resource
    resource = tag_dict['resource_allocation']

    # qos
    qos = ET.Element('qos')
    rewriter_qos(tag_dict['qos'], qos, resource)
    if list(qos):
        new_root.append(qos)

    # participant
    participant = ET.Element('participant')
    rewriter_participant(tag_dict['nodes'], participant, resource)
    if list(participant):
        new_root.append(participant)

    return new_root


def rewriter_xml(file_path):
    try:
        tree = ET.parse(file_path)
    except Exception as e:
        print(str(e))
        return

    root = tree.getroot()
    root_dict = {
        tag: root.find(tag)
        for tag in itertools.chain([
            'network',
            'discovery',
            'resource_allocation',
            'qos',
            'nodes',
        ])
    }
    root_dict['idl'] = root.findall('idl')

    root = writer_new_xml(root_dict)
    xml_str = prettify_xml(root)

    with open(file_path, 'w', encoding='utf-8') as f:
        f.write(xml_str)


def parse_args():
    parser = ArgumentParser()
    group = parser.add_mutually_exclusive_group()

    group.add_argument('-f', '--file', dest='cache', help='XML File Path')
    group.add_argument('-d', '--directory', dest='cache', help='XML Directory Path')

    return parser.parse_known_args()


def main():
    args, _ = parse_args()
    cache = args.cache

    if os.path.isfile(cache):
        print(cache)
        rewriter_xml(cache)
    elif os.path.isdir(cache):
        dir_path = Path(cache)
        for file in dir_path.rglob('*.xml'):
            print(file)
            rewriter_xml(file)
    else:
        print('Check your input and make sure file exists')


if __name__ == '__main__':
    peer_resource = {}

    main()
