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


from utils.process_input import pre_init, post_init
from jinja2 import Environment, FileSystemLoader
from argparse import ArgumentParser
import os


def render_bus_config(conf_data, output_file, test_mode):
    # check output file suffix
    if output_file.split(".")[-1] != "c":
        raise Exception("Only [.c] file suffixes are supported")

    template_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), "template")
    template_name = "mvbs_config.c.jinja2"
    conf_data["test_mode"] = test_mode

    # render
    file_loader = FileSystemLoader(template_path)
    env = Environment(loader=file_loader)
    template = env.get_template(template_name)

    with open(output_file, "w") as fp:
        fp.write(template.render(**conf_data))

def render_testcase(conf_data, output_file, test_mode):
    # check output file suffix
    if output_file.split(".")[-1] != "c":
        raise Exception("Only [.c] file suffixes are supported")

    # topic_period_dic = {}
    # with open('../topic_period.txt', 'r') as topic_period_file:
    #     for line in topic_period_file:
    #         line = line.strip()
    #         key, value = line.split(maxsplit = 1)
    #         topic_period_dic[key] = int(value)
    #         for writer in conf_data['participant']['writers']:
    #             if writer['topic'] in topic_period_dic:
    #                 writer["period"] = topic_period_dic[writer['topic']]
    #         for reader in conf_data['participant']['readers']:
    #             if reader['topic'] in topic_period_dic:
    #                 reader['period'] = topic_period_dic[reader['topic']]

    template_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), "template")
    template_name = "mvbs_xml_test.c.jinja2"
    conf_data["test_mode"] = test_mode
    # print(conf_data)

    # render
    file_loader = FileSystemLoader(template_path)
    env = Environment(loader=file_loader)
    template = env.get_template(template_name)

    with open(output_file, "w") as fp:
        fp.write(template.render(**conf_data))


def parse_args():
    parser = ArgumentParser()
    parser.add_argument("-s", "--source", dest="file_lst", action="append", required=True, help="source path for config file (xml)")
    parser.add_argument("-t", "--target", dest="target", help="Indicate C file to generated")

    parser.add_argument("--host", dest="host", help="Set host information")
    parser.add_argument("--transport", dest="transport", help="Setting transport: Type:param1,param2,param3...")

    parser.add_argument("--test", action="store_true", help="Generate source code with test mode")
    parser.add_argument("--intf", help="Indicate the interface name of getting profile")

    parser.add_argument("-p", "--print", action="store_true", help="Print memory usage")
    parser.add_argument("-i", "--idl-dir", dest="idl_dir", help="Indicate IDL directory path")
    parser.add_argument("--version", dest="ver", default="V1.4.0", help="Indicate version for memory usage")
    parser.add_argument("--platform", dest="plt", default="xcu", help="Indicate platforms for memory usage")
    parser.add_argument("-g", dest="gen_test", help="Indicate platforms for memory usage")

    return parser.parse_known_args()


def main():
    args, _ = parse_args()

    for cfg_file in args.file_lst:
        master = pre_init(cfg_file, args.transport, args.host)

    post_init(master, args.intf)

    if args.print:
        if args.ver == "V1.4.0":
            from utils.calculate_mem_V1_4_0 import get_memory_size
        elif args.ver == "V1.3.0":
            from utils.calculate_mem_V1_3_0 import get_memory_size
        elif args.ver == "V1.2.1":
            from utils.calculate_mem_V1_2_1 import get_memory_size
        else:
            from utils.calculate_mem import get_memory_size

        memory_usage = get_memory_size(master, args.idl_dir, args.sec, args.ver, args.plt)
        print(f"\nTotal Usage: [{memory_usage}] Bytes\n")

    if args.file_lst:
        xml_file = args.file_lst[0]
        if xml_file.endswith('.xml'):
            xml_name = os.path.splitext(os.path.basename(xml_file))[0]
            master['xml'] = xml_name

    if args.target:
        render_bus_config(master, args.target, args.test)

    if args.gen_test:
        render_testcase(master, args.gen_test, args.test)


if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print("XML MISCONFIG:", str(e))
        # For debug
        # import traceback
        # traceback.print_exc()
        exit(1)
