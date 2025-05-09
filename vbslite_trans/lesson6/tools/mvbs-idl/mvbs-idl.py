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

import os
import sys
import time
import logging
import argparse
import pcpp
import tempfile
import shutil

from jinja2 import Environment, FileSystemLoader
from parser_idl import *
from calc_topic_crc import calculate_topic_crc16
from calc_topic_size import get_all_topic_max_size

includes_list = []
string_topic_list = []
topic_crc_list = []
envMap = {"genWriter": "true", "genReader": "true", "language": "C"}
logging.basicConfig(level=logging.DEBUG, format="[%(levelname)s]-[%(asctime)s]-[Msg:%(message)s]")


class MySyntaxErrorListener(ErrorListener):
    def syntaxError(self, recognizer, offendingSymbol, line, column, msg, e):
        raise Exception(f"Parser error at line {line}:{column} - {msg}")

# Customize the preprocessor, ignore all #include directives
class ignore_all_include:
    def __init__(self):
        pass

    def read(self):
        return ""

    def close(self):
        pass


class CustomPreprocessor1(pcpp.Preprocessor):
    def on_file_open(self, is_system_include, includepath):
        return ignore_all_include()


def preprocess_idl_file(input_file, output_file):
    preprocessor = CustomPreprocessor1()
    preprocessor.line_directive = None

    with open(input_file, 'r', encoding='utf-8') as f:
        preprocessor.parse(f.read())

    with open(output_file, 'w', encoding='utf-8') as f:
        preprocessor.write(f)

    includes_list = get_include_idl_file_name_list(input_file)

    return includes_list


def get_include_idl_file_name_list(input_filename):
    includes_list = []
    # Read the content of the original IDL file
    with open(input_filename, 'r', encoding='utf-8') as file:
        idl_file_datas = file.readlines()

    for line in idl_file_datas:

        if line.strip().startswith('#include'):
            include_file = line.split('#include ')[-1].strip().strip('"').replace('.idl', 'Plugin.h')
            includes_list.append(include_file)

    return includes_list


class CustomPreprocessor(pcpp.Preprocessor):
    def __init__(self, include_dirs):
        super().__init__()
        # Add the directory where your header files are located
        if include_dirs:
            for directory in include_dirs:
                self.add_path(directory)


def get_whole_constructMapList(input_file, output_file):
    include_dirs = [os.path.dirname(input_file)]
    preprocessor = CustomPreprocessor(include_dirs)
    preprocessor.line_directive = None

    with open(input_file, 'r', encoding='utf-8') as f:
        preprocessor.parse(f.read())

    with open(output_file, 'w', encoding='utf-8') as f:
        preprocessor.write(f)

    constructMapList = parser_idl(output_file)

    return constructMapList


def calculate_idl_all_topic_crc16(constructMapList, topic_crc_list):
    for topic_list in constructMapList:
        topic_name = topic_list['nativeFQNameInModule']
        topic_kind = topic_list['constructKind']

        if topic_kind != "const" and topic_kind != "alias":
            ret = calculate_topic_crc16(topic_name, topic_list, topic_crc_list, constructMapList)

            if ret == True:
                string_topic_list.append(topic_name)


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--input_file", required=True, help="Input IDL File Path")
    parser.add_argument("-d", "--dir_path", default=".", help="Storage Path of Generated Files")
    parser.add_argument("-t", "--test", required=False, help="Test Mode")
    return parser.parse_args()


def gen_file(content, predirective_dict, suffix_list, template_list, output_path, idl_basename, env):
    if content:
        for template_file, suffix in zip(template_list, suffix_list):
            template = env.get_template(template_file)
            if template is not None:
                file_path = os.path.join(output_path, idl_basename + suffix)
                with open(file_path, "w", encoding="utf-8") as out_stream:
                    out_stream.write(
                        template.render(constructMapList=content, preproc_directive=predirective_dict,
                                        Idlfilename=idl_basename, envMap=envMap))
            else:
                logging.error("{} is not exist".format(template_file))


def updata_constructMapList_topic_crc16(topic_crc_list,string_topic_list, constructMapList):
    for node in constructMapList:
        for topic in topic_crc_list:
            if topic['topic_name'] == node['nativeFQNameInModule']:
                node['crc16'] = topic['crc_value']

        for topic_name in string_topic_list:
            if "memberHasString" not in node and  topic_name == node['nativeFQNameInModule']:
                node['memberHasString'] = "true"

def updata_constructMapList_topic_size(topic_size_list, constructMapList):
    for node in constructMapList:
        for topic_name, topic_size in topic_size_list.items():
            if topic_name == node['nativeFQNameInModule']:
                node['type_size'] = topic_size

def main():
    args = parse_args()
    idl_path = args.input_file
    output_path = args.dir_path
    test_mode = args.test

    if not os.path.exists(idl_path):
        logging.error("Input idl file not exist")
        sys.exit(1)

    if not os.path.exists(output_path):
        os.makedirs(output_path)

    now = int(time.time())
    envMap["executionID"] = str(now)
    # envMap["crc16"] = calculate_crc16(idl_path)
    if test_mode:
        envMap["test_mode"] = "true"
    else:
        envMap["test_mode"] = "false"
    idl_basename_with_extension = os.path.basename(idl_path)
    idl_basename, extension = os.path.splitext(idl_basename_with_extension)

    # load template
    template_path = os.path.dirname(os.path.realpath(__file__))
    template_path = os.path.join(template_path, "resources", "template")
    env = Environment(loader=FileSystemLoader(template_path), extensions=['jinja2.ext.do'])
    env.globals.update(context.get_functions())

    # IDL file preprocess
    dir = tempfile.mkdtemp()
    output_file = os.path.join(dir, idl_basename)
    output_tmp_file = os.path.join(dir, idl_basename + '_tmp')

    includes_list = preprocess_idl_file(idl_path, output_file)
    constructMapList = parser_idl(output_file)
    if includes_list == []:
        calculate_idl_all_topic_crc16(constructMapList, topic_crc_list)
        topic_size_list = get_all_topic_max_size(constructMapList)
        updata_constructMapList_topic_size(topic_size_list, constructMapList)

    else:
        new_constructMapList = get_whole_constructMapList(idl_path, output_tmp_file)
        calculate_idl_all_topic_crc16(new_constructMapList, topic_crc_list)
        topic_size_list = get_all_topic_max_size(new_constructMapList)

    updata_constructMapList_topic_size(topic_size_list, constructMapList)
    updata_constructMapList_topic_crc16(topic_crc_list, string_topic_list, constructMapList)
    # print(constructMapList)
    if not constructMapList:
        logging.error("Check if Input File Complies with IDL Specification")
        try:
            os.rmdir(output_path)
        except OSError as e:
            pass
        sys.exit(1)

    # gen idl file
    suffix_list = ["Plugin.h", "Plugin.c"]
    template_list = ["typePluginHeader.jinja2", "typePluginBody.jinja2"]
    gen_file(constructMapList, includes_list, suffix_list, template_list, output_path, idl_basename, env)

    if os.path.exists(output_file):
        os.remove(output_file)

    # Get the directory path where the file is located
    dir_path = os.path.dirname(output_file)

    # Use shutil.rmtree() to remove an entire directory and its contents
    if os.path.exists(dir_path):
        shutil.rmtree(dir_path)



if __name__ == '__main__':
    main()