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


from utils.calculate_timer import extract_timer_config
from utils.read_xml import type_to_int
from collections import Counter
import itertools
import re
import os


interval_limit = [2147483647, 4294967295]
obj_id_lst = []
qos_lst = []
qos_alias = {}

valid_qos = {
    'history': {
        'DDS_KEEP_LAST_HISTORY_QOS': 'KEEP_LAST',
        'DDS_KEEP_ALL_HISTORY_QOS': 'KEEP_ALL'
    },
    'ownership': {
        'DDS_SHARED_OWNERSHIP_QOS': 'SHARED',
        'DDS_EXCLUSIVE_OWNERSHIP_QOS': 'EXCLUSIVE'
    },
    'liveliness': {
        'DDS_AUTOMATIC_LIVELINESS_QOS': 'QOS_LIVE_AUTOMATIC',
        'DDS_MANUAL_BY_PARTICIPANT_LIVELINESS_QOS': 'QOS_LIVE_MANUAL_BY_PTCP',
        'DDS_MANUAL_BY_TOPIC_LIVELINESS_QOS': 'QOS_LIVE_MANUAL_BY_TOPIC'
    },
    'durability': {
        'DDS_VOLATILE_DURABILITY_QOS': 'VOLATILE',
        'DDS_TRANSIENT_LOCAL_DURABILITY_QOS': 'TRANSIENT_LOCAL',
    },
    'reliability': {
        'DDS_BEST_EFFORT_RELIABILITY_QOS': 'BEST_EFFORT',
        'DDS_RELIABLE_RELIABILITY_QOS': 'RELIABLE'
    },
    'e2e_policy': {
        'DDS_MANUAL_BY_TOPIC_LIVELINESS_QOS': 'QOS_LIVE_MANUAL_BY_TOPIC',
    },
}

data_ranges = {
    'uint8': (0, 255),
    'uint16': (0, 65535),
    'uint32': (0, 4294967295),
    'int8': (0, 127),
    'int16': (0, 32767),
    'int32': (0, 2147483647)
}


def cidr_to_subnet_mask(cidr_prefix_length):
    cidr_prefix_length = int(cidr_prefix_length)
    if cidr_prefix_length > 32 or cidr_prefix_length < 0:
        raise Exception('Invalid CIDR prefix length')
    binary_string = '1' * cidr_prefix_length + '0' * (32 - cidr_prefix_length)
    subnet_mask = '.'.join([str(int(binary_string[i:i+8], 2)) for i in range(0, 32, 8)])
    return subnet_mask


def check_valid_ip(ip):
    if not re.match(r'^(\d{1,3}\.){3}\d{1,3}$', ip):
        raise Exception('IP Address invalid format!')
    octets = ip.split('.')
    for octet in octets:
        if int(octet) > 255:
            raise Exception('IP Address contains invalid value!')
    return ip


def check_valid_qos(key, qos):
    if qos not in valid_qos[key]:
        raise Exception('Invalid QoS value {}, Support {} QoS are {}'.format(qos, key, valid_qos[key].keys()))


def check_valid_keys(marks, key_list):
    count = Counter(key_list)
    duplicates = [item for item in count if count[item] > 1]

    if duplicates:
        print('Notes: ')
        raise Exception(f"Duplicate '{','.join(duplicates)}' in '{marks}'")


def check_valid_interval(key, interval):
    if interval == [0, 0]:
        raise Exception('Setting attribute {} to [0 0] is meaningless.'.format(key))

    if interval == interval_limit:
        return

    max_seconds = 5000000
    seconds, nanoseconds = interval
    if seconds < 0 or seconds > max_seconds:
        raise Exception(f"{key}'s seconds value({seconds}) exceeds the limit [0, {max_seconds}]")
    check_value_range('uint32', 'period.nanoseconds', nanoseconds)


def check_value_range(data_type, key, value):
    if data_type in data_ranges:
        min_value, max_value = data_ranges[data_type]
        if value < min_value or value > max_value:
            raise Exception(f"{key}'s value({value}) exceeds the range of {data_type}: [{min_value}, {max_value}]")
        elif key in type_to_int[8:] and value == 0:
            raise Exception(f"{key}'s value must be greater than zero")
    else:
        raise Exception('Invalid data type')


def check_valid_bool(key, value):
    if value not in ['true', 'false']:
        raise Exception('Invalid bool value of {} in C'.format(key))


def check_static_peers(name, kind, peer_lst):
    for peer in peer_lst:
        object_id = peer.get('object_id')
        if object_id is None:
            raise Exception(f'Missing object_id tag in {name} peer')
        else:
            check_value_range('int16', f'static_peers.{object_id}', object_id)

        qos = peer.get('qos', None)
        if qos is None:
            raise Exception(f"Under static discovery {name}'s peer has no qos tag")

        qos = f'{kind}_{qos}'
        if qos not in qos_alias:
            raise Exception(f'Unknown qos: {qos[2:]}')
        else:
            index = qos_alias[qos]
            peer['qos'] = index
            extract_timer_config(kind, qos_lst[index])

def filter_invalid_items(peer_lst):
    for peer in peer_lst.copy():
        enabled = peer.get('enabled', 'True').lower()
        check_valid_bool('enabled', enabled)

        if enabled == 'false':
            peer_lst.remove(peer)

    return peer_lst

def process_sendtype(dic):
    if 'sendtype' in dic:
        value = dic['sendtype']
        if value == 'OnChange':
            dic['sendtype'] = 'OnChange'
            dic['period'] = 0
        elif value.startswith('Periodic(') and value.endswith('ms)'):
            period_str = 'Periodic'
            period_value = value[len(period_str) + 1:-3]

            dic['sendtype'] = period_str
            dic['period'] = int(period_value)
    else:
            dic['sendtype'] = 'OnChange'
            dic['period'] = 0

def check_participant_peers(kind, discovery, peer_lst):
    for peer in peer_lst:
        missing_fields = ['key', 'topic', 'type']
        if any(peer.get(field, None) is None for field in missing_fields):
            raise Exception(f"Missing fields: {','.join(missing_fields)}")

        name = peer['key']

        qos = peer.setdefault('qos', 'default')
        qos = f'{kind}_{qos}'
        if qos not in qos_alias:
            raise Exception(f'Unknown qos: {qos[2:]}')
        else:
            index = qos_alias[qos]
            peer['qos'] = index
            extract_timer_config(kind, qos_lst[index])

        peer.setdefault('max_remote_peers', 1)
        check_value_range('uint16', 'max_remote_peers', peer['max_remote_peers'])

        net_redundancy = peer.get('net_redundancy', 'false').lower()
        check_valid_bool('net_redundancy', net_redundancy)
        peer['net_redundancy'] = net_redundancy

        object_id = peer.setdefault('object_id', -1)

        if discovery == 'DPDE':
            peer.pop('static_peers', None)
        else:
            if object_id == -1:
                raise Exception(f'Under static discovery peer {name} has no object_id tag')

            if f'{kind}_{object_id}' in obj_id_lst:
                raise Exception('Duplicate object_id value')

            if 'static_peers' not in peer:
                raise Exception(f'Under static discovery, peer {name} has no static_peers tag')

            check_value_range('uint16', f'{name}.object_id', object_id)
            obj_id_lst.append(f'{kind}_{object_id}')

            peer_kind = 'r' if kind == 'w' else 'w'
            check_static_peers(name, peer_kind, peer['static_peers'])

        process_sendtype(peer)

    prompt = 'participant.writers.{}' if kind == 'w' else 'participant.readers.{}'
    member_keys = [peer['key'] for peer in peer_lst]
    check_valid_keys(prompt.format('key'), member_keys)
    member_topics = [peer['topic'] for peer in peer_lst]
    check_valid_keys(prompt.format('topic'), member_topics)


def check_qos_config(cfg):
    durability = cfg.setdefault('durability', {})
    kind = durability.setdefault('kind', 'DDS_TRANSIENT_LOCAL_DURABILITY_QOS')
    check_valid_qos('durability', kind)
    durability['kind'] = valid_qos['durability'][kind]

    reliability = cfg.setdefault('reliability', {})
    kind = reliability.setdefault('kind', 'DDS_BEST_EFFORT_RELIABILITY_QOS')
    check_valid_qos('reliability', kind)
    reliability['kind'] = valid_qos['reliability'][kind]

    ownership = cfg.setdefault('ownership', {})
    kind = ownership.setdefault('kind', 'DDS_SHARED_OWNERSHIP_QOS')
    check_valid_qos('ownership', kind)
    ownership['kind'] = valid_qos['ownership'][kind]

    ownership_strength = cfg.setdefault('ownership_strength', {})
    value = ownership_strength.setdefault('value', 0)
    check_value_range('uint16', 'qos.ownership_strength.value', value)

    deadline = cfg.setdefault('deadline', {})
    period = deadline.setdefault('period', interval_limit)
    check_valid_interval('qos.deadline.period', period)

    liveliness = cfg.setdefault('liveliness', {})
    kind = liveliness.setdefault('kind', 'DDS_AUTOMATIC_LIVELINESS_QOS')
    check_valid_qos('liveliness', kind)
    liveliness['kind'] = valid_qos['liveliness'][kind]
    lease_duration = liveliness.setdefault('lease_duration', interval_limit)
    check_valid_interval('qos.liveliness.lease_duration', lease_duration)

    seconds, nanoseconds = map(int, lease_duration)
    total_nanoseconds = seconds * 1000 + nanoseconds // 100000
    anno_seconds = total_nanoseconds // 1000 // 2
    anno_nanoseconds = (total_nanoseconds * 1000000 // 2) - (anno_seconds * 1000000000)
    liveliness['period'] = [anno_seconds, anno_nanoseconds]

    lifespan = cfg.setdefault('lifespan', {})
    period = lifespan.setdefault('period', interval_limit)
    check_valid_interval('qos.lifespan.period', period)

    history = cfg.setdefault('history', {})
    kind = history.setdefault('kind', 'DDS_KEEP_LAST_HISTORY_QOS')
    check_valid_qos('history', kind)
    history['kind'] = valid_qos['history'][kind]
    depth = history.setdefault('depth', 5)
    check_value_range('uint16', 'depth', depth)
    max_samples = history.setdefault('max_samples', 5)
    check_value_range('uint16', 'max_samples', max_samples)
    max_instances = history.setdefault('max_instances', 1)
    check_value_range('uint8', 'max_instances', max_instances)
    max_samples_per_instance = history.setdefault('max_samples_per_instance', 5)
    check_value_range('uint8', 'max_samples_per_instance', max_samples_per_instance)

    e2e_policy = cfg.setdefault('e2e_policy', {})
    e2e_enable = e2e_policy.get('enable', 'false').lower()
    check_valid_bool('e2e_policy.enable', e2e_enable)
    e2e_policy['enable'] = e2e_enable
    min_data_length = e2e_policy.setdefault('e2e_p04_min_data_length', 0)
    check_value_range('uint16', 'qos.e2e_policy.e2e_p04_min_data_length', min_data_length)
    max_data_length = e2e_policy.setdefault('e2e_p04_max_data_length', 4090)
    check_value_range('uint16', 'qos.e2e_policy.e2e_p04_max_data_length', max_data_length)
    max_delta_counter = e2e_policy.setdefault('e2e_p04_max_delta_counter', 10)
    check_value_range('uint16', 'qos.e2e_policy.e2e_p04_max_delta_counter', max_delta_counter)
    deadline_counter = e2e_policy.setdefault('e2e_deadline_counter', 2)
    check_value_range('uint16', 'qos.e2e_policy.e2e_deadline_counter', deadline_counter)
    liveliness_lease_duration = e2e_policy.setdefault('e2e_liveliness_lease_duration', [0, 500000000])
    check_valid_interval('qos.e2e_policy.e2e_liveliness_lease_duration', liveliness_lease_duration)
    kind = e2e_policy.setdefault('e2e_liveliness_kind', 'DDS_MANUAL_BY_TOPIC_LIVELINESS_QOS')
    check_valid_qos('e2e_policy', kind)
    e2e_policy['e2e_liveliness_kind'] = valid_qos['e2e_policy'][kind]

    return cfg


def record_qos_alias(kind, lst):
    for qos in lst:
        name = f"{kind}_{qos.pop('key', 'default')}"
        cfg = check_qos_config(qos)

        length = len(qos_lst)
        index = length
        if name in qos_alias:
            raise Exception(f'Duplicate qos key {name[2:]}')
        else:
            if index == length:
                qos_lst.append(cfg)

            qos_alias[name] = index

    default_name = f'{kind}_default'
    if default_name not in qos_alias:
        index = len(qos_lst)
        qos_lst.append(check_qos_config({}))
        qos_alias[default_name] = index


###############################################################################
def building_idl(config_data):
    file_list = config_data.pop('idl')

    if file_list is None:
        raise Exception('Please specify idl tag in XML file.')

    idl_lst = [os.path.splitext(os.path.basename(file))[0] for file in file_list]

    config_data['idl_lst'] = sorted(set(idl_lst), key=idl_lst.index)

###############################################################################
def ip4_to_uint32_le(ip_string):
    bytes  = [int(x) for x in ip_string.split(".")]
    return (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0]

# def building_network(config_data, host):
#     user_config = config_data.pop('network', {})
# 
#     if host == None:
#         masters = user_config.setdefault('master', [{
#             'address': '127.0.0.1',
#             'netmask': '255.255.255.0',
#             }]
#         )
#     else:
#         ip_address, _, cidr = host.partition('/')
# 
#         masters = [{
#             'address': check_valid_ip(ip_address),
#             'netmask': cidr_to_subnet_mask(cidr) if cidr else net['netmask'],
#             }]
# 
#     network_config = [
#         {
#             'address': check_valid_ip(locator.get('address', '127.0.0.1')),
#             'netmask': check_valid_ip(locator.get('netmask', '255.255.255.0')),
#             "addr_uint32_le": "0x{:08X}".format(ip4_to_uint32_le(locator.get("address", "127.0.0.1"))),
#             "mask_uint32_le": "0x{:08X}".format(ip4_to_uint32_le(locator.get("netmask", "255.255.255.0"))),
#         }
#         for locator in itertools.chain(masters, user_config.setdefault('backup', []))
#     ]
# 
#     config_data['network_lst'] = network_config

#
#  cmdline_udp_info = [
#      {
#           "address":"172.31.10.111",
#           "netmask": "255.255.255.0"
#      },
#      {
#           "host":"172.31.30.111",
#           "netmask": "255.255.255.0"
#      }
#  ]
#
def get_udp_network(config_data):
    udp_network = config_data.pop('network', {})

    udp_network.setdefault('master', [{
        'address': '127.0.0.1',
        'netmask': '255.255.255.0',
        }]
    )

    udp_network.setdefault('backup', [])

    return udp_network["master"] + udp_network["backup"]

def get_transport(config_data):
    transports = config_data.pop('transports', {})
    transport_list = transports.get('transport', [])

    trans_ipc_j6m = []
    trans_udp = []

    for trans in transport_list:
        if trans["type"] == "UDPv4":
            for udp in trans["udp"]:
                if udp["enable"] == "false":
                    continue

                trans_udp.append({
                            "address":udp.setdefault("address", "127.0.0.1"),
                            "netmask": udp.setdefault("netmask", "255.255.255.0"),
                            })

        if trans["type"] == "IPC_J6M":
            for ipc in trans["ipc"]:
                if ipc["enable"] == "false":
                    continue

                sizebit  = ipc.setdefault("buffer_sizebit", "14")
                buf_size = 1<<int(sizebit)

                trans_ipc_j6m.append({
                            "buffer_sizebit":ipc.setdefault("buffer_sizebit", "14"),
                            "buffer_size":buf_size,
                            "tx_pkg_size":ipc.setdefault("mvbs_rx_pkg_size", "4090"),
                            "rx_pkg_size":ipc.setdefault("mvbs_tx_pkg_size", "4090"),
                            })

    return trans_udp, trans_ipc_j6m

def building_transports(config_data, cmdline_transport, cmdline_host):
    if cmdline_transport != None:
        trans_udpv4, trans_ipc_j6m = cmdline_transport
    else:
        trans_udpv4, trans_ipc_j6m = get_transport(config_data)

        if len(trans_udpv4) == 0:
            trans_udpv4 = get_udp_network(config_data)

        if cmdline_host != None:
            trans_udpv4 = cmdline_host

    transport_udpv4 = [
        {
            'address': check_valid_ip(locator.get('address', '127.0.0.1')),
            'netmask': check_valid_ip(locator.get('netmask', '255.255.255.0')),
            "addr_uint32_le": "0x{:08X}".format(ip4_to_uint32_le(locator.get("address", "127.0.0.1"))),
            "mask_uint32_le": "0x{:08X}".format(ip4_to_uint32_le(locator.get("netmask", "255.255.255.0"))),
        }
        for locator in itertools.chain(trans_udpv4)
    ]

    config_data['transport_udpv4'] = transport_udpv4
    config_data['transport_ipc_j6m'] = trans_ipc_j6m

def building_discovery(config_data):
    user_config = config_data.pop('discovery', {})

    # check announce
    announce = user_config.setdefault('announce', {})
    times = announce.setdefault('times', 5)
    check_value_range('uint16', 'discovery.announce.times', times)
    period = announce.setdefault('period', [0, 20000000])
    check_valid_interval('discovery.announce.period', period)

    # check heartbeat
    heartbeat = user_config.setdefault('heartbeat', {})
    period = heartbeat.setdefault('period', [3, 0])
    seconds, nanoseconds = period

    if period == [0, 0]:
        raise Exception("Setting attribute discovery.heartbeat.period to [0 0] is meaningless.")
    if period != [255, 65535]:
        max_seconds = 60
        if seconds < 0 or seconds > max_seconds:
            raise Exception(f"discovery.heartbeat.period.seconds {seconds} exceeds the limit [0, {max_seconds}]")
        check_value_range("uint16", "period.nanoseconds", nanoseconds)

    milliseconds = nanoseconds / 1e6
    extra_seconds, milliseconds = divmod(milliseconds, 1000)
    seconds += int(extra_seconds)
    milliseconds = int(milliseconds)

    heartbeat["period"] = [seconds, milliseconds]

    per_max_samples = heartbeat.setdefault('per_samples', 5)
    check_value_range('uint8', 'per_samples', per_max_samples)

    # check liveliness
    liveliness = user_config.setdefault('liveliness', {})
    period = liveliness.setdefault('period', [30, 0])
    check_valid_interval('discovery.liveliness.period', period)
    lease_duration = liveliness.setdefault('lease_duration', [100, 0])
    check_valid_interval('discovery.liveliness.lease_duration', lease_duration)

    config_data['discovery'] = user_config


def building_qos(config_data):
    user_config = config_data.pop('qos', {})

    record_qos_alias('w', user_config.get('writer', []))
    record_qos_alias('r', user_config.get('reader', []))

    config_data['qos_lst'] = qos_lst


def building_participant(config_data):
    user_config = config_data.pop('participant', None)
    if user_config is None:
        raise Exception('Please specify participant tag in XML file.')

    if len(user_config) > 1:
        raise Exception('Only 1 Node supported in current mvbs version')

    user_config = user_config[0]
    if user_config.get('name') is None:
        raise Exception('Participant name is necessary')

    domain_id = user_config.setdefault('domain_id', 0)
    check_value_range('int8', 'participant.domain_id', domain_id)

    discovery = user_config.get('discovery', 'DPDE').upper()
    if discovery not in ['DPSE', 'DPDE']:
        raise Exception('Only support [DPSE, DPDE] for participant discovery.')
    user_config['discovery'] = discovery

    if discovery == 'DPSE':
        user_config['check_crc'] = 'false'
    else:
        check_crc = user_config.get('check_crc', 'false').lower()
        check_valid_bool('user_config.check_crc', check_crc)
        user_config['check_crc'] = check_crc

    remote_participants = user_config.setdefault('max_remote_participants', 8)
    check_value_range('uint8', 'max_remote_participants', remote_participants)

    local_rx_buffer = user_config.get('local_rx_buffer', 12)
    user_config['local_rx_buffer'] = pow(2, local_rx_buffer)
    check_value_range('uint32', 'local_rx_buffer', user_config['local_rx_buffer'])

    udp_rx_buffer = user_config.get('udp_rx_buffer', 15)
    user_config['udp_rx_buffer'] = pow(2, udp_rx_buffer)
    check_value_range('uint32', 'udp_rx_buffer', user_config['udp_rx_buffer'])

    preferred_ptcp_list = user_config.get('preferred_remote_participant',[])

    user_config['preferred_remote_participant'] = list()
    if isinstance(preferred_ptcp_list, list):
        user_config['preferred_remote_participant'] += preferred_ptcp_list
    else:
        user_config['preferred_remote_participant'].append(preferred_ptcp_list)

    writers = user_config.get('writer', [])
    readers = user_config.get('reader', [])

    if not (writers or readers):
        print('Warning: There are no readers and writers in participant.')

    writers = filter_invalid_items(writers)
    readers = filter_invalid_items(readers)

    check_participant_peers('w', discovery, writers)
    check_participant_peers('r', discovery, readers)

    if "writer" in user_config:
        del(user_config["writer"])

    if "reader" in user_config:
        del(user_config["reader"])

    user_config["writers"] = writers;
    user_config["readers"] = readers;

    config_data['participant'] = user_config


def preprocess_param_host(host):
    if host == None:
        return None

    items = host.split(":")

    trans_udpv4 = []

    for item in items:
        ip_address, _, cidr = item.partition('/')

        trans_udpv4.append({
            'address': check_valid_ip(ip_address),
            'netmask': cidr_to_subnet_mask(cidr) if cidr else "255.255.255.0",
            })

    return trans_udpv4

def preprocess_param_transport(transport):
    if transport == None:
        return None

    if transport.startswith("UDPv4:"):
        params = transport[6:]

        param_list = params.split(",")

        trans_udpv4 = []

        for param in param_list:
            ip_address, _, cidr = param.partition('/')

            trans_udpv4.append({
                'address': check_valid_ip(ip_address),
                'netmask': cidr_to_subnet_mask(cidr) if cidr else "255.255.255.0",
                })

        return (trans_udpv4, [])

    if transport.startswith("IPC_J6M"):
        params = transport[7:].strip()

        sizebit = 14
        buf_size = 1 << sizebit

        if params == "" or params == ":":
            return ([], [{"buffer_sizebit":sizebit,
                          "buffer_size":buf_size,
                          "tx_pkg_size":"4090",
                          "rx_pkg_size":"4090",
                          }])

        if not params.startswith(":"):
            raise Exception('transport option has invalid parameters')

        param_list = params.split(",")

        trans_ipc_j6m = []

        for param in param_list:
            param = param.strip()

            ret = re.match(r"buffer_sizebit\s*=\s*(\d+)", param)

            if ret == None:
                continue

            sizebit = int(ret.group(1))
            buf_size = 1 << sizebit

            return ([], [{"buffer_sizebit":sizebit,
                          "buffer_size":buf_size,
                          "tx_pkg_size":"4090",
                          "rx_pkg_size":"4090",
                          }])

        return ([], [{"buffer_sizebit":sizebit,
                      "buffer_size":buf_size,
                      "tx_pkg_size":"4090",
                      "rx_pkg_size":"4090",
                      }])

    raise Exception('transport option has invalid type.')


def gen_render_data(config_data, transport=None, host=None):
    obj_id_lst.clear()
    qos_lst.clear()
    qos_alias.clear()

    building_idl(config_data)
    building_transports(config_data,
                        preprocess_param_transport(transport),
                        preprocess_param_host(host))
    building_discovery(config_data)
    building_qos(config_data)
    building_participant(config_data)

    return config_data
