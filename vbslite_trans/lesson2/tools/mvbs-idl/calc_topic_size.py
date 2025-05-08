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


import sys
import os

constructMapList_global = []
topic_size_dict_global = {}
topic_align_size_dict_global = {}
topic_align_serialize_size_dict_global = {}
const_value_dict = {}

basic_type_size = {
    'int8_t'  : 1,
    'uint8_t' : 1,
    'int16_t' : 2,
    'uint16_t': 2,
    'int32_t' : 4,
    'uint32_t': 4,
    'int64_t' : 8,
    'uint64_t': 8,
    'float'   : 4,
    'double'  : 8,
    'char *'  : 0,
    'unsigned char': 1,
}

def get_hex_size(size):
    if ('0X' in str(size)) or ('0x' in str(size)):
        hex_size = int(size, 16)
        return hex_size
    if ('0C' in str(size)) or ('0c' in str(size)):
        hex_size = int(size, 8)
        return hex_size

    return size

def get_alise_topic_size(node_size, node):
    previous_size = node_size
    member = node['memberFieldMapList'][0]
    if node.get('isAliasOfArray' ) == 'true':
        if node.get('isBaseArray') == 'true' :
            type_size = basic_type_size[member['mvbsTypeName']]
            member_count = get_hex_size(member['SizeValue'])
            node_size += padding(node_size, type_size) + int(type_size) * int(member_count)
        else:#user array
            type = get_topic_type_name(member['nativeTypeFQName'])
            if type == 'struct':  #struct array
                node_name = get_node_by_name(member['nativeTypeFQName'])
                for i in range(int(member['SizeValue'])):
                    node_size += get_struct_topic_size(node_size, node_name)
            else:
                raise ValueError('not support user alise array'.format(node['nativeTypeFQName']))

    elif node.get('isAliseofSequence') == 'true':
        if node.get('isBaseSequence') == 'true' :
            type_size = basic_type_size[member['mvbsTypeName']]
            member_count = get_hex_size(member['SizeValue'])
            node_size += padding(node_size, type_size) + int(type_size) * int(member_count)
        else:#userSequence
            type = get_topic_type_name(member['nativeTypeFQName'])
            if type == 'struct':  #struct Sequence
                node_name = get_node_by_name(member['nativeTypeFQName'])
                for i in range(int(member['SizeValue'])):
                    node_size += get_struct_topic_size(node_size, node_name)
            else:
                raise ValueError('not support user alise Sequence'.format(node['nativeTypeFQName']))

    return node_size - previous_size

def get_union_topic_size(node_size, node_user):
    previous_size = node_size
    union_max_size_serialized = 0

    if node_user['switchType'] == 'user':
        topic_type = get_topic_type_name(node_user['nativeTypeFQName'])

        if topic_type == 'enum':
            node_size += padding(node_size, 4) + 4

            for label in node_user['memberFieldMapList']:
                reset_alignment = node_size
                type_size = basic_type_size[label['mvbsTypeName']]
                node_size += padding(node_size, type_size) + type_size
                if (union_max_size_serialized < reset_alignment):
                    union_max_size_serialized = reset_alignment

            node_size = union_max_size_serialized

            return node_size - previous_size
        else:
            raise TypeError("switchType not is enum: {}".format(node_user['nativeTypeFQName']))

    else:
        raise TypeError("switchType not is user: {}".format(node_user['name']))


def get_topic_type_name(nativeTypeFQName):
    for node in constructMapList_global:
        if nativeTypeFQName == node['nativeFQNameInModule']:
            return node['constructKind']
    return None

def get_node_by_name(nativeTypeFQName):
    for node in constructMapList_global:
        if nativeTypeFQName == node['nativeFQNameInModule']:
            return node
    return None

def get_topic_real_size(constructMapList):

    global constructMapList_global
    constructMapList_global = constructMapList.copy()

    for node in constructMapList_global:
        name = node['nativeFQNameInModule']
        node_type = node['constructKind']

        if node_type == 'struct':
            topic_size = get_struct_topic_size(0, node)
            topic_size_dict_global[name] = topic_size
        else:
            continue

    return topic_size_dict_global.copy()

def get_struct_topic_size(node_size, node):
    previous_size = node_size

    for member in node.get('memberFieldMapList', []):
        if member['typeKind'] == 'builtin':
            node_size += get_builtin_type_size(member, node_size)

        elif member['typeKind'] == 'user':
            # print("{}:{}".format(member['name'], node_size))
            topic_type = get_topic_type_name(member['nativeTypeFQName'])
            node_user = get_node_by_name(member['nativeTypeFQName'])

            if topic_type == 'struct':
                #struct sequence or array
                if member.get('isSeq') or member.get('dimensionList') :
                    node_size +=  padding(node_size, 4) + 4
                    member_count = get_hex_size(member['SizeValue'])
                    for i in range(int(member_count)):
                        node_size += get_struct_topic_size(node_size, node_user)
                else:
                    node_size += get_struct_topic_size(node_size, node_user)

            elif topic_type == 'enum':
                node_size += padding(node_size, 4) + 4

            elif topic_type == 'alias':
                node_size +=  get_alise_topic_size(node_size,node_user)

            elif topic_type == 'union':
                node_size += get_union_topic_size(node_size, node_user)

            else:
                raise TypeError("Invaild type data: {}".format(member['name']))

        else:
            raise TypeError("Invaild typeKind : ".format(member['name']))

    return node_size - previous_size


def get_builtin_type_size(member, size):
    previous_size = size
    type_size = basic_type_size[member['mvbsTypeName']]

    # string
    if member['realTypeName'] == 'string':
        str_size = get_hex_size(member['SizeValue'])
        size += padding(size, 4) + 4 + int(str_size) + 1
    # basic sequence
    elif member.get('isSeq') == 'true':
        member_count = get_hex_size(member['SizeValue'])
        size += padding(size, type_size) + 4 + int(type_size) * int(member_count)

    # basic array
    elif member.get('dimensionList'):
        member_count = get_hex_size(member['SizeValue'])
        size += padding(size, type_size) + int(type_size) * int(member_count)
    # basic type
    else:
        size += padding(size, type_size) + type_size

    return size - previous_size


def padding(buffer_position, data_size):
    size = (data_size - (buffer_position % data_size)) & (data_size - 1)

    return size

def align_to_4_bytes(value):
    return (value + 3) & ~3

def all_topic_align_to_4_bytes(topic_size_dict_global):
    for topic_name, topic_size in topic_size_dict_global.items():
        topic_size = align_to_4_bytes(topic_size)
        topic_align_size_dict_global[topic_name] = topic_size

        # FIXME: The extra 4 bytes is used to store endianess and some other
        # information. It may could be removed for saving memory in future.
        topic_align_serialize_size_dict_global[topic_name] = topic_size + 4

    return topic_align_serialize_size_dict_global

def get_all_topic_max_size(constructMapList):
    topic_size_dict_global = get_topic_real_size(constructMapList)

    return all_topic_align_to_4_bytes(topic_size_dict_global)
