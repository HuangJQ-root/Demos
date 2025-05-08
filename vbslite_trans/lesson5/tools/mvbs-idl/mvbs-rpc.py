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
import crcmod
import logging
import argparse
from resources import context
from typeprocess.GenContainer_rpc import *
from jinja2 import Environment, FileSystemLoader
from antlr4.error.ErrorListener import ErrorListener


envMap = {"genWriter": "true", "genReader": "true", "language": "C"}
logging.basicConfig(level=logging.DEBUG, format="[%(levelname)s]-[%(asctime)s]-[Msg:%(message)s]")


class MySyntaxErrorListener(ErrorListener):
    def syntaxError(self, recognizer, offendingSymbol, line, column, msg, e):
        raise Exception(f"Parser error at line {line}:{column} - {msg}")


def calculate_crc16(file_path):
    crc16_func = crcmod.mkCrcFun(0x11021, rev=False, initCrc=0xFFFF, xorOut=0x0000)
    with open(file_path, "rb") as file:
        crc16_value = crc16_func(file.read())

    return hex(crc16_value)[2:]


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--input_file", required=True, help="Input IDL File Path")
    parser.add_argument("-d", "--dir_path", default=".", help="Storage Path of Generated Files")
    return parser.parse_args()


def rpc_gen_file(content_idl, content_rpc, suffix_list, template_list, output_path, idl_basename, env):
    if not content_rpc:
        for suffix in suffix_list:
            file_path = os.path.join(output_path, idl_basename + suffix)
            with open(file_path, "w", encoding="utf-8") as f:
                pass
    else:
        for template_file, suffix in zip(template_list, suffix_list):
            template = env.get_template(template_file)
            if template is not None:
                file_path = os.path.join(output_path, idl_basename + suffix)
                with open(file_path, "w", encoding="utf-8") as out_stream:
                    out_stream.write(
                        template.render(constructMapList_idl = content_idl, constructMapList =content_rpc, Idlfilename=idl_basename, envMap=envMap))
            else:
                logging.error("{} is not exist".format(template_file))


def main():
    args = parse_args()
    idl_path = args.input_file
    output_path = args.dir_path

    if not os.path.exists(idl_path):
        logging.error("Input idl file not exist")
        sys.exit(1)

    if not os.path.exists(output_path):
        os.makedirs(output_path)

    now = int(time.time())
    envMap["executionID"] = str(now)
    envMap["crc16"] = calculate_crc16(idl_path)
    idl_basename_with_extension = os.path.basename(idl_path)
    idl_basename, extension = os.path.splitext(idl_basename_with_extension)
    # load template
    template_path = os.path.dirname(os.path.realpath(__file__))
    template_path = os.path.join(template_path, "resources","template")
    env = Environment(loader=FileSystemLoader(template_path), extensions=['jinja2.ext.do'])
    env.globals.update(context.get_functions())

    # use Antlr4 parser idl file
    input_stream = FileStream(idl_path, encoding='utf-8')
    lexer = IDL_GrammarLexer(input_stream)
    stream = CommonTokenStream(lexer)
    parser = IDL_GrammarParser(stream)

    parser.removeErrorListeners()
    error_listener = MySyntaxErrorListener()
    parser.addErrorListener(error_listener)

    try:
        tree = parser.specification()
    except Exception as e:
        print(e)
        exit(-1)

    walker = ParseTreeWalker()
    walker.walk(MemberListener(), tree)

    # print(constructMapList)
    if not constructMapList:
        logging.error("Check if Input File Complies with IDL Specification")
        try:
            os.rmdir(output_path)
        except OSError as e:
            pass
        sys.exit(1)

    # gen rpc file
    idl_list = [item for item in constructMapList if isinstance(item, dict)]
    rpc_map_list = constructMapList[-1] if isinstance(constructMapList[-1], list) else []
    suffix_list = ["RpcClient.h", "RpcClient.c", "RpcServer.h", "RpcServer.c", "RpcParams.c","RpcParams.h"]
    template_list = ["typeRpcClientHeader.jinja2", "typeRpcClientBody.jinja2",
                     "typeRpcServerHeader.jinja2", "typeRpcServerBody.jinja2", "paramsMesgBody.jinja2","paramsMesgHeader.jinja2"]
    rpc_gen_file(idl_list, rpc_map_list, suffix_list, template_list, output_path, idl_basename, env)


if __name__ == '__main__':
    main()
