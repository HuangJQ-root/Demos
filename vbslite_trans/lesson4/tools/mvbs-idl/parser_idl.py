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

from resources import context
from typeprocess.GenContainer_idl import *
from antlr4.error.ErrorListener import ErrorListener


class MySyntaxErrorListener(ErrorListener):
    def syntaxError(self, recognizer, offendingSymbol, line, column, msg, e):
        raise Exception(f"Parser error at line {line}:{column} - {msg}")


def parser_idl(file_path):
    constructMapList.clear()

    # use Antlr4 parser idl file
    input_stream = FileStream(file_path, encoding='utf-8')
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

    return constructMapList.copy()
