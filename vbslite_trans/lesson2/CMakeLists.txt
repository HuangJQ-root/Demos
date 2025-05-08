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
project(multi_topic_test)

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
set(CONFIG_MVBS ON CACHE BOOL "Enable MVBS support")

if(CONFIG_MVBS)
    # 包含 mvbs 子目录的 CMakeLists.txt
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/mvbs)
endif()

# 设置共用 IDL 工具路径和输入输出路径
set(IDL_TOOL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/mvbs-idl/mvbs-idl.py" CACHE PATH "Path to the IDL generation tool")
# 修改为实际的 IDL 输入文件路径
set(IDL_INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/idl/HelloWorld.idl" CACHE FILEPATH "Path to the IDL input file")
set(IDL_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

# 添加自定义命令来运行 IDL 工具，同时指定生成 HelloWorldPlugin.c
add_custom_command(
    OUTPUT ${IDL_OUTPUT_DIR}/HelloWorldPlugin.h ${IDL_OUTPUT_DIR}/HelloWorldPlugin.c
    COMMAND ${CMAKE_COMMAND} -E make_directory ${IDL_OUTPUT_DIR}
    COMMAND python3 ${IDL_TOOL_PATH} -i ${IDL_INPUT_FILE} -d ${IDL_OUTPUT_DIR} -t TEST
    DEPENDS ${IDL_INPUT_FILE} ${IDL_TOOL_PATH}
    COMMENT "Generating IDL code"
    VERBATIM
)

# 添加自定义目标来触发代码生成，依赖于头文件和源文件的生成
add_custom_target(
    generate_idl_code
    DEPENDS ${IDL_OUTPUT_DIR}/HelloWorldPlugin.h ${IDL_OUTPUT_DIR}/HelloWorldPlugin.c
)

# 定义生成 XML 代码的函数
function(generate_xml_code APP_NAME XML_INPUT_FILE XML_OUTPUT_FILE)
    set(XML_TOOL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/mvbs-cfg/mvbs-config.py")
    add_custom_command(
        OUTPUT ${XML_OUTPUT_FILE}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${IDL_OUTPUT_DIR}
        COMMAND python3 -B ${XML_TOOL_PATH} -s ${XML_INPUT_FILE} -t ${XML_OUTPUT_FILE}
        DEPENDS ${XML_TOOL_PATH} ${XML_INPUT_FILE}
        COMMENT "Generating app_config.c from ${APP_NAME}_config.xml"
        VERBATIM
    )
    add_custom_target(
        generate_${APP_NAME}_xml_code
        DEPENDS ${XML_OUTPUT_FILE}
    )
endfunction()

# 设置 app1_test 头文件目录
set(app1_test_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/multi_topic_test/app1"
)

# 设置 app2_test 头文件目录
set(app2_test_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/multi_topic_test/app2"
)

# 生成 app1 的 XML 代码
set(app1_XML_INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/multi_topic_test/app1/app1_config.xml")
set(app1_XML_OUTPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/generated/app1_config.c")
generate_xml_code(app1 ${app1_XML_INPUT_FILE} ${app1_XML_OUTPUT_FILE})

# 生成 app2 的 XML 代码
set(app2_XML_INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/multi_topic_test/app2/app2_config.xml")
set(app2_XML_OUTPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/generated/app2_config.c")
generate_xml_code(app2 ${app2_XML_INPUT_FILE} ${app2_XML_OUTPUT_FILE})

# 添加可执行文件 app1_test，依赖于 generate_idl_code 和 generate_app1_xml_code 目标
add_executable(app1_test 
    ${CMAKE_CURRENT_SOURCE_DIR}/multi_topic_test/app1/app1_test.c
)

# 添加生成的源文件到 app1_test 的源文件列表
target_sources(app1_test PRIVATE 
    ${IDL_OUTPUT_DIR}/HelloWorldPlugin.c
    ${app1_XML_OUTPUT_FILE}
)

# 将头文件搜索路径添加到 app1_test 目标
target_include_directories(app1_test PRIVATE 
    ${IDL_OUTPUT_DIR}
    ${app1_test_HEADERS}
)

# 在构建 app1_test 之前生成 IDL 代码和 XML 代码
add_dependencies(app1_test generate_idl_code generate_app1_xml_code)

# 链接库到可执行文件
if(CONFIG_MVBS)
    target_link_libraries(app1_test mvbs mvbs_aux)
endif()

# 添加可执行文件 app2_test，依赖于 generate_idl_code 和 generate_app2_xml_code 目标
add_executable(app2_test 
    ${CMAKE_CURRENT_SOURCE_DIR}/multi_topic_test/app2/app2_test.c
)

# 添加生成的源文件到 app2_test 的源文件列表
target_sources(app2_test PRIVATE 
    ${IDL_OUTPUT_DIR}/HelloWorldPlugin.c
    ${app2_XML_OUTPUT_FILE}
)

# 将头文件搜索路径添加到 app2_test 目标
target_include_directories(app2_test PRIVATE 
    ${IDL_OUTPUT_DIR}
    ${app2_test_HEADERS}
)

# 在构建 app2_test 之前生成 IDL 代码和 XML 代码
add_dependencies(app2_test generate_idl_code generate_app2_xml_code)

# 链接库到可执行文件
if(CONFIG_MVBS)
    target_link_libraries(app2_test mvbs mvbs_aux)
endif()