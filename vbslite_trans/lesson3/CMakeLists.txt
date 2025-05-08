# 版权声明和许可证信息
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

# 设置 CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(RpcTest)

# 配置开启 GDB 调试
set(CMAKE_BUILD_TYPE Debug)

# 检测 C 和 C++ 编译器
enable_language(C CXX)

add_definitions(-DTARGET_PRODUCT_LINUX)

# 设置编译选项
# C++ 编译选项
set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")

# C 编译选项
set(CMAKE_C_FLAGS "")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")

# 设置链接选项
set(CMAKE_EXE_LINKER_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "")
set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "")
set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "")

# 设置 CONFIG_MVBS 变量，可根据需要修改
set(CONFIG_MVBS ON)

if(CONFIG_MVBS)
    # 包含 mvbs 子目录的 CMakeLists.txt
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/mvbs)
endif()

# 设置 RpcTest 头文件目录
set(RPC_TEST_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/rpc_test"
)

# 设置 IDL 工具路径和输入输出路径
set(IDL_TOOL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/mvbs-idl/mvbs-rpc.py")
# 修改为实际的 IDL 输入文件路径
set(IDL_INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/idl/calculator.idl") 
set(IDL_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

# 查找 Python 解释器
find_package(Python3 REQUIRED COMPONENTS Interpreter)

# 添加自定义命令来运行 IDL 工具，同时指定生成 calculatorRpcClient.c calculatorRpcParam.c calculatorRpcServer.c
add_custom_command(
    OUTPUT ${IDL_OUTPUT_DIR}/calculatorRpcClient.h ${IDL_OUTPUT_DIR}/calculatorRpcClient.c ${IDL_OUTPUT_DIR}/calculatorRpcParams.h ${IDL_OUTPUT_DIR}/calculatorRpcParams.c ${IDL_OUTPUT_DIR}/calculatorRpcServer.h ${IDL_OUTPUT_DIR}/calculatorRpcServer.c
    COMMAND ${Python3_EXECUTABLE} ${IDL_TOOL_PATH} -i ${IDL_INPUT_FILE} -d ${IDL_OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${IDL_OUTPUT_DIR}
    DEPENDS ${IDL_INPUT_FILE} ${IDL_TOOL_PATH}
    COMMENT "Generating IDL code"
)

# 添加自定义目标来触发代码生成，依赖于头文件和源文件的生成
add_custom_target(
    generate_idl_code
    DEPENDS ${IDL_OUTPUT_DIR}/calculatorRpcClient.h ${IDL_OUTPUT_DIR}/calculatorRpcClient.c ${IDL_OUTPUT_DIR}/calculatorRpcParams.h ${IDL_OUTPUT_DIR}/calculatorRpcParams.c ${IDL_OUTPUT_DIR}/calculatorRpcServer.h ${IDL_OUTPUT_DIR}/calculatorRpcServer.c
)

# 添加可执行文件 server，依赖于 generate_idl_code
add_executable(server
    ${CMAKE_CURRENT_SOURCE_DIR}/rpc_test/server.c
)
# 添加生成的源文件到 server
target_sources(server PRIVATE 
    ${IDL_OUTPUT_DIR}/calculatorRpcServer.c
    ${IDL_OUTPUT_DIR}/calculatorRpcParams.c
)
# 将头文件搜索路径添加到 server
target_include_directories(server PRIVATE 
    ${IDL_OUTPUT_DIR}
    ${RPC_TEST_HEADERS}
)
# 设置 server 的依赖关系
add_dependencies(server generate_idl_code)
# 链接库到 server
if(CONFIG_MVBS)
    target_link_libraries(server mvbs mvbs_aux)
endif()

# 添加可执行文件 client，依赖于 generate_idl_code
add_executable(client
    ${CMAKE_CURRENT_SOURCE_DIR}/rpc_test/client.c
)
# 添加生成的源文件到 client
target_sources(client PRIVATE 
    ${IDL_OUTPUT_DIR}/calculatorRpcClient.c
    ${IDL_OUTPUT_DIR}/calculatorRpcParams.c
)
# 将头文件搜索路径添加到 client
target_include_directories(client PRIVATE 
    ${IDL_OUTPUT_DIR}
    ${RPC_TEST_HEADERS}
)
# 设置 client 的依赖关系
add_dependencies(client generate_idl_code)
# 链接库到 client
if(CONFIG_MVBS)
    target_link_libraries(client mvbs mvbs_aux)
endif()