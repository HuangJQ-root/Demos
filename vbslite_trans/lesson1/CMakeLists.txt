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
project(LocalTest)

#配置开启 GDB 调试
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

# 设置 local_test 头文件目录
set(LOCAL_TEST_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/local_test"
)

# 设置 IDL 工具路径和输入输出路径
set(IDL_TOOL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/mvbs-idl/mvbs-idl.py")
# 修改为实际的 IDL 输入文件路径
set(IDL_INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/idl/HelloWorld.idl") 
set(IDL_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

# 添加自定义命令来运行 IDL 工具，同时指定生成 HelloWorldPlugin.c
add_custom_command(
    OUTPUT ${IDL_OUTPUT_DIR}/HelloWorldPlugin.h ${IDL_OUTPUT_DIR}/HelloWorldPlugin.c
    COMMAND ${CMAKE_COMMAND} -E make_directory ${IDL_OUTPUT_DIR}
    COMMAND python3 ${IDL_TOOL_PATH} -i ${IDL_INPUT_FILE} -d ${IDL_OUTPUT_DIR} -t TEST
    DEPENDS ${IDL_INPUT_FILE} ${IDL_TOOL_PATH}
    COMMENT "Generating IDL code"
)

# 添加自定义目标来触发代码生成，依赖于头文件和源文件的生成
add_custom_target(
    generate_idl_code
    DEPENDS ${IDL_OUTPUT_DIR}/HelloWorldPlugin.h ${IDL_OUTPUT_DIR}/HelloWorldPlugin.c
)

# 设置 XML 工具路径和相关模板路径
set(XML_TOOL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/mvbs-cfg/mvbs-config.py")
# 修改为实际的 XML输入文件路径
set(XML_INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/local_test/app_config.xml")
set(XML_OUTPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/generated/app_config.c")


# 添加自定义命令来运行 XML 工具，模仿 IDL 部分的格式
add_custom_command(
    OUTPUT ${XML_OUTPUT_FILE}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${IDL_OUTPUT_DIR}
    # 添加 -B 选项并确保路径一致
    COMMAND python3 -B ${XML_TOOL_PATH} -s ${XML_INPUT_FILE} -t ${XML_OUTPUT_FILE}
    DEPENDS ${XML_TOOL_PATH} ${XML_INPUT_FILE} 
    COMMENT "Generating app_config.c from app_config.xml"
)

# 添加自定义目标来触发 XML 代码生成
add_custom_target(
    generate_xml_code
    DEPENDS ${XML_OUTPUT_FILE}
)

# 添加可执行文件 local_test_app，依赖于 generate_idl_code 和 generate_xml_code 目标
add_executable(local_test_app 
    ${CMAKE_CURRENT_SOURCE_DIR}/local_test/app_test.c
)

# 添加生成的源文件到 local_test_app 的源文件列表
target_sources(local_test_app PRIVATE 
    ${IDL_OUTPUT_DIR}/HelloWorldPlugin.c
    ${XML_OUTPUT_FILE}
)

# 将头文件搜索路径添加到 local_test_app 目标
target_include_directories(local_test_app PRIVATE 
    ${IDL_OUTPUT_DIR}
    ${LOCAL_TEST_HEADERS}
)

# 在构建 local_test_app 之前生成 IDL 代码和 XML 代码
add_dependencies(local_test_app generate_idl_code generate_xml_code)

# 链接库到可执行文件
if(CONFIG_MVBS)
    target_link_libraries(local_test_app mvbs mvbs_aux)
endif()