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

def calculate_string_crc16(data: str, poly=0x1021, init_crc=0xFFFF) -> int:
    crc = init_crc
    for byte in data.encode('utf-8'):
        crc ^= byte << 8
        for _ in range(8):
            if (crc & 0x8000) != 0:
                crc = (crc << 1) ^ poly
            else:
                crc <<= 1
            crc &= 0xFFFF  # Ensure that the CRC value is always 16 bits

    # Use the format string to convert to a four-digit hexadecimal string
    return f"{crc:04X}"

def get_enum_member_string(string_topic, enum_list):
    string_topic += enum_list['typeCodeFQName']
    string_topic += " "
    for enum_member in enum_list['memberFieldMapList']:
        if enum_member['ordinal'] == "NULL":
            string_topic += enum_member['name'] + " " + str(enum_member['value']) + " "
        else:
            if "0x" in enum_member['ordinal']:
                string_topic += enum_member['name'] + " " + str(int(enum_member['ordinal'], 16)) + " "
            else:
                string_topic += enum_member['name'] + " " + enum_member['ordinal'] + " "

    # Use rstrip() method to remove trailing spaces.
    trimmed_string = string_topic.rstrip()
    return trimmed_string

def get_sequence_mebmer_string(string_topic, sequence_member, crc_value):
    if crc_value:     #user
        string_topic += "sequence<" + crc_value
    else:        #buildin
        string_topic += "sequence<" + sequence_member['realTypeName']

    if sequence_member['isdefault'] == 'false':
        if "0x" in str(sequence_member['seqSizeRealValue']):
            string_topic += "," + " " + str(int(sequence_member['seqSizeRealValue'], 16))
        else:
            string_topic += "," + " " + str(sequence_member['seqSizeRealValue'])
    string_topic += ">" + " " + sequence_member['name'] + " "

    return string_topic


def get_array_mebmer_string(string_topic, struct_list):
    new_string_topic = struct_list['realTypeName'] + struct_list['dimensionList']
    string_topic += new_string_topic + " " + struct_list['name'] + " "

    return string_topic

def get_struct_member_string(string_topic, mem_type, struct_list):
    string_topic += mem_type

    if mem_type == 'string' and struct_list['isdefault'] == 'false':
        if 'SizeValue' in struct_list:
            string_topic += '<' + str(struct_list['SizeValue']) + '>'
        else:
            string_topic += '<' + str(struct_list['strSize']) + '>'

    if 'dimensionList' in struct_list:
        if "SizeValue" in struct_list:
            string_topic += "[" + str(struct_list['SizeValue']) + "]"
        else:
            string_topic += struct_list['dimensionList']

    string_topic += " " + struct_list['name'] + " "

    return string_topic

def calculate_enum_topic_crc(string_topic, topic_list):
    string_topic = get_enum_member_string(string_topic, topic_list)
    topic_crc = calculate_string_crc16(string_topic)

    return topic_crc

def get_topic_crc_from_list(topic_name, topic_crc_list):
    if topic_crc_list == []:
        return None

    for d in topic_crc_list:
        # Print and check the type of each element
        if isinstance(d, dict) and 'topic_name' in d:
            if d['topic_name'] == topic_name:
                return d['crc_value']

    return None

def add_topic_crc_to_list(topic_name, struct_topic_crc, topic_crc_list):
    topic_crc_dict = {}

    topic_crc_dict['topic_name'] = topic_name
    topic_crc_dict['crc_value'] = struct_topic_crc

    ret = get_topic_crc_from_list(topic_name, topic_crc_list)

    if not ret:
        topic_crc_list.append(topic_crc_dict)

def get_user_type_member_string(string_topic, topic_member, topic_crc_list, constructMapList):
    for new_topic_list in constructMapList:
        if new_topic_list['nativeFQNameInModule'] == topic_member['nativeTypeFQName']:
            # new_topic_crc_dict = {}
            if new_topic_list['constructKind'] == "struct":
                new_string_topic = get_struct_topic_string(new_topic_list['nativeFQNameInModule'], "", new_topic_list,
                                                           constructMapList)
                topic_crc = calculate_string_crc16(new_string_topic)

                string_topic = get_struct_member_string(string_topic, topic_crc, topic_member)

            elif new_topic_list['constructKind'] == "union":

                pass
            elif new_topic_list['constructKind'] == "enum":
                topic_crc = calculate_enum_topic_crc("", new_topic_list)
                string_topic = get_struct_member_string(string_topic, topic_crc, topic_member)

                pass
            elif new_topic_list['constructKind'] == "alias":
                if 'isAliasOfArray' in new_topic_list and "isBaseArray" in new_topic_list:
                    #typedef array
                    if new_topic_list['isAliasOfArray'] == 'true' and new_topic_list['isBaseArray'] == 'true':
                        # typedef basic array
                        string_topic += topic_member['Original_type'] + '[' + topic_member['Original_count'] + ']' + " " +  topic_member['name'] + " "

                    elif new_topic_list['isAliasOfArray'] == 'true' and new_topic_list['isBaseArray'] == 'false':
                        # typedef complex array
                        topic_name = new_topic_list['memberFieldMapList'][0]['nativeTypeFQName']
                        topic_crc =  get_topic_crc_from_list(topic_name, topic_crc_list)
                        if not topic_crc:
                            print("the topic {} not find crc".format(topic_name))
                        else:
                            string_topic += topic_crc + new_topic_list['memberFieldMapList'][0]['dimensionList']+ " " + topic_member['name'] + " "
                if 'isAliseofSequence' in new_topic_list and 'isBaseSequence' in new_topic_list:
                    #typedef sequence
                    if new_topic_list['isAliseofSequence'] == 'true' and new_topic_list['isBaseSequence'] == 'true':
                        # typedef basic sequence
                        print("crc: not suppport typedef basic sequence")
                        pass
                    elif new_topic_list['isAliseofSequence'] == 'true' and new_topic_list['isBaseSequence'] == 'true':
                        # typedef complex sequence
                        print("crc: not suppport typedef complex sequence")
                        pass

    return string_topic

def get_struct_topic_string(topic_name, string_topic, topic_list, topic_crc_list, constructMapList):
    for topic_member in topic_list['memberFieldMapList']:
        if topic_member['typeKind'] == "builtin":
            if 'isSeq' in topic_member and topic_member['isSeq'] == 'true':
                string_topic = get_sequence_mebmer_string(string_topic, topic_member, None)
            elif 'dimensionList' in topic_member:
                string_topic = get_array_mebmer_string(string_topic, topic_member)
            else:
                string_topic = get_struct_member_string(string_topic, topic_member['realTypeName'], topic_member)


        elif topic_member['typeKind'] == "user":
            if 'isSeq' in topic_member and topic_member['isSeq'] == 'true':
                crc_value = get_topic_crc_from_list(topic_member['nativeTypeFQName'], topic_crc_list)
                if crc_value:
                    string_topic = get_sequence_mebmer_string(string_topic, topic_member, crc_value)
                else:
                    pass    #not support
            else:
                crc_value = get_topic_crc_from_list(topic_member['nativeTypeFQName'], topic_crc_list)
                #have been calculate crc for topic
                if crc_value:
                    struct_topic_crc = crc_value
                    string_topic = get_struct_member_string(string_topic, struct_topic_crc, topic_member)

                else:
                    string_topic = get_user_type_member_string(string_topic, topic_member, topic_crc_list, constructMapList)

    # Use rstrip() method to remove trailing spaces.
    trimmed_string = string_topic.rstrip()
    return trimmed_string

def get_union_topic_string(topic_name, string_topic, topic_list, topic_crc_list, constructMapList):
    string_topic += "switch_type" + " "

    if topic_list['switchType'] == "user":
        for switch_type in topic_crc_list:
            if switch_type['topic_name'] == topic_list['nativeTypeFQName']:
                switch_crc_value = switch_type['crc_value']
            else:
                switch_crc_value = " "

        string_topic += switch_crc_value + " "

        for member in topic_list['memberFieldMapList']:
            string_topic += topic_list['typeCodeFQNameInModule'] + "::" + member['label'] + " "
            string_topic += member['realTypeName'] + " "+ member['name'] + " "
    else:
        print("switch topic name:{} not support buildin".format(topic_list['nativeFQNameInModule']))

    # Use rstrip() method to remove trailing spaces.
    trimmed_string = string_topic.rstrip()
    return trimmed_string


def topic_if_contain_sting_and_seq(topic_list, constructMapList):
    #return True:Topic contain string or seq
    #return False:Topic contain not string or seq

    if "is_dynamic" in topic_list:
        return True

    else:
        for topic_member in topic_list['memberFieldMapList']:
            if topic_member['typeKind'] == "builtin":
                if topic_member['typeName'] == 'string' or topic_member['typeName'] == 'wstring' or ('isSeq' in topic_member and topic_member['isSeq'] == 'true'):
                    return True

            elif  topic_member['typeKind'] == "user":
                if 'isSeq' in topic_member and topic_member['isSeq'] == 'true':
                    return True
                else:
                    for sub_topic_node in constructMapList:
                        if topic_member['nativeTypeFQName'] == sub_topic_node['nativeFQNameInModule']:
                            ret = topic_if_contain_sting_and_seq(sub_topic_node, constructMapList)
                            if ret:
                                return ret
        return False

def calculate_topic_crc16(topic_name, topic_list, topic_crc_list, constructMapList):
    string_topic = ""

    if topic_list['constructKind'] == "struct":
        string_topic = get_struct_topic_string(topic_name, string_topic,topic_list, topic_crc_list, constructMapList)
        struct_topic_crc = calculate_string_crc16(string_topic)
        ret = topic_if_contain_sting_and_seq(topic_list, constructMapList)

    elif topic_list['constructKind'] == "union":
        string_topic = get_union_topic_string(topic_name, string_topic,topic_list, topic_crc_list, constructMapList)
        struct_topic_crc = calculate_string_crc16(string_topic)
        ret = False

    elif topic_list['constructKind'] == "enum":
        string_topic = get_enum_member_string(string_topic, topic_list)
        struct_topic_crc = calculate_string_crc16(string_topic)
        ret = False

    add_topic_crc_to_list(topic_name, struct_topic_crc, topic_crc_list)

    # print("topic_name:{}++++++++++++++++++++++{}".format(topic_name, string_topic))
    # print("topic_name:{}~~~~~~~~~~~~~~~~~~~~~~{}".format(topic_name,struct_topic_crc))

    return ret


