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

def merge_participant(master, slave):
    mismatch_filed = ["key", "discovery"]
    if any(master[key] != slave[key] for key in mismatch_filed):
        raise Exception("Unmatched node filed: {}".format(mismatch_filed))

    configs = {
        "domain_id": ("Unmatched node domain_id", 0),
        "resource.remote_node": ("Unmatched resource remote_node", 8),
        "resource.remote_writer": ("Unmatched resource remote_writer", 8),
        "resource.remote_reader": ("Unmatched resource remote_reader", 8),
    }
    override_default(master, slave, configs)

    preferred_list_1 = master.get('preferred_remote_participant', [])
    preferred_list_2 = slave.get('preferred_remote_participant', [])

    preferred_list = list(set(preferred_list_1 + preferred_list_2))

    master.setdefault("preferred_remote_participant", preferred_list)

    merge_node_members(master.setdefault("writers", []), slave.get("writers", []), master["discovery"], "W")
    merge_node_members(master.setdefault("readers", []), slave.get("readers", []), master["discovery"], "R")


def merge_node_members(master, slave, discovery_type, member_type):
    if len(slave) == 0:
        return
    if len(master) == 0:
        master.extend(slave)
    configs = {
        "qos": ("Unmatched node member qos", "default"),
        "backup_enabled": ("Unmatched node member backup_enabled", "false"),
    }

    for peer_member in slave:
        try:
            member = next(item for item in master if item["key"] == peer_member["key"])
        except StopIteration:
            master.append(peer_member)
            continue
        mismatch_filed = ["topic", "type", "rtps_object_id"]
        if any(member[key] != peer_member[key] for key in mismatch_filed):
            raise Exception("Unmatched node member {} in field {}".format(member, mismatch_filed))
        override_default(member, peer_member, configs)
        if discovery_type == "DPSE":
            working_key = "dpse_peer_reader" if member_type == "W" else "dpse_peer_writer"
            merge_dpse_member(member[working_key], peer_member[working_key], working_key)


def merge_dpse_member(master, slave, sub_key):
    working_key = "sub_object_id" if sub_key == "dpse_peer_reader" else "pub_object_id"

    for peer_member in slave:
        try:
            member = next(item for item in master if item[working_key] == peer_member[working_key])
        except StopIteration:
            master.append(peer_member)
            continue
        if member["qos"] != peer_member["qos"]:
            raise Exception("Unmatched peer member {} in field {}".format(member, "qos"))


def merge_idl(master, slave):
    master_set = set(master)
    master.extend(item for item in slave if item not in master_set)


def merge_network(master, slave):
    master_net = master["masters"][0]
    slave_net = slave["masters"][0]

    configs = {
        "local_ip": ("Unmatched network interfaces local_ip", "127.0.0.1"),
        "local_netmask": ("Unmatched network interfaces local_netmask", "255.255.255.0"),
    }
    override_default(master_net, slave_net, configs)


def merge_discovery(master, slave):
    configs = {
        "initial_announcements.announce_times": ("Unmatched network interfaces local_ip", 5),
        "initial_announcements.period": ("Unmatched network interfaces local_netmask", [0, 20000000]),

        "heartbeat.period": ("Unmatched network interfaces local_ip", 3000),
        "heartbeat.per_max_samples": ("Unmatched network interfaces local_netmask", 5),

        "liveliness.assert_period": ("Unmatched network interfaces local_ip", interval_limit),
        "liveliness.lease_duration": ("Unmatched network interfaces local_netmask", interval_limit),

    }
    override_default(master, slave, configs)


def merge_qos(master, slave, sub_key):
    for key, peer_qos in slave.items():
        if key not in master:
            master[key] = peer_qos
            continue

        qos = master[key]
        configs = {
            "resource.max_samples": ("Unmatched resource max_samples", 5),
            "resource.max_instances": ("Unmatched resource max_instances", 1),
            "resource.max_samples_per_instance": ("Unmatched resource max_samples_per_instance", 5),
            "resource.{}".format(sub_key): ("Unmatched resource {}".format(sub_key), 1),

            "durability.kind": ("Unmatched durability kind", "TRANSIENT_LOCAL"),
            "reliability.kind": ("Unmatched reliability kind", "BEST_EFFORT"),
            "ownership.kind": ("Unmatched ownership kind", "SHARED"),
            "ownership_strength.value": ("Unmatched ownership_strength value", 0),

            "deadline.period": ("Unmatched deadline period", interval_limit),

            "liveliness.kind": ("Unmatched liveliness kind", "AUTOMATIC"),
            "liveliness.lease_duration": ("Unmatched liveliness lease_duration", interval_limit),
            "lifespan.period": ("Unmatched lifespan period", interval_limit),

            "history.kind": ("Unmatched history kind", "KEEP_LAST"),
            "history.depth": ("Unmatched history depth", 5),

            "e2e_policy.enable": ("Unmatched e2e_policy enable", "false"),
            "e2e_policy.e2e_p04_data_id": ("Unmatched e2e_policy e2e_p04_data_id", 0),
            "e2e_policy.e2e_p04_min_data_length": ("Unmatched e2e_policy e2e_p04_min_data_length", 1),
            "e2e_policy.e2e_p04_max_data_length": ("Unmatched e2e_policy e2e_p04_max_data_length", 2),
            "e2e_policy.e2e_p04_max_delta_counter": ("Unmatched e2e_policy e2e_p04_max_delta_counter", 3),
        }

        override_default(qos, peer_qos, configs)


def override_default(master, slave, configs):
    for key, (exception_msg, default_value) in configs.items():
        keys = key.split(".")
        working_key = keys.pop()
        master_clone = master
        slave_clone = slave
        for sub_key in keys:
            master_clone = master_clone.get(sub_key)
            slave_clone = slave_clone.get(sub_key)

        if master_clone[working_key] == default_value:
            master_clone[working_key] = slave_clone[working_key]
        elif slave_clone[working_key] != default_value and master_clone[working_key] != slave_clone[working_key]:
            raise Exception(exception_msg)


def merge_render_data(master, slave):
    merge_idl(master["idls"], slave["idls"])
    merge_network(master["network"], slave["network"])
    merge_discovery(master["discovery"], slave["discovery"])
    merge_participant(master["node"], slave["node"])
    merge_qos(master["writer_qos_group"], slave["writer_qos_group"], "max_remote_readers")
    merge_qos(master["reader_qos_group"], slave["reader_qos_group"], "max_remote_writers")
