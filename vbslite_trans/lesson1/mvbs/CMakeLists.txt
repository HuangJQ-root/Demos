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

if(CONFIG_MVBS)
    set(MVBS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

    # 使用 GLOB_RECURSE 递归查找 MVBS 相关的源文件
    file(GLOB_RECURSE MVBS_SRCS_CURRENT
        "${MVBS_SOURCE_DIR}/core/*.c"
        "${MVBS_SOURCE_DIR}/mcdr/*.c"
        "${MVBS_SOURCE_DIR}/rte/*.c"
        "${MVBS_SOURCE_DIR}/rpc/*.c"
        "${MVBS_SOURCE_DIR}/adapter/posix/*.c"  # 只包含 posix 相关的源文件
    )

    # 从查找到的源文件列表中移除不需要的文件 Dds_Adaptor_Interface.c(弱定义Rte_Dds_GetParticipant)
    list(REMOVE_ITEM MVBS_SRCS_CURRENT
    "${MVBS_SOURCE_DIR}/rte/Dds_Adaptor_Interface.c"
    )

    # 将筛选后的源文件列表存储在 MVBS_SOURCES 变量中
    set(MVBS_SOURCES
        ${MVBS_SRCS_CURRENT}
        CACHE INTERNAL "SRCS for mvbs"
    )

    # 设置 MVBS 库需要包含的头文件目录
    set(MVBS_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${MVBS_SOURCE_DIR}/core/include"
        "${MVBS_SOURCE_DIR}/adapter/posix/include"  # 只包含 posix 相关的头文件目录
        CACHE INTERNAL "INCS for mvbs"
    )

    # 添加构建 mvbs 库的命令
    # 使用 MVBS_SOURCES 变量中的源文件来构建 mvbs 静态库
    add_library(mvbs STATIC ${MVBS_SOURCES})

    # 为 mvbs 库指定需要包含的头文件目录，PUBLIC 表示这些头文件目录对于依赖 mvbs 库的其他目标也是可见的
    target_include_directories(mvbs PUBLIC ${MVBS_HEADERS})

    # 使用 GLOB 查找 mvbs_aux 库的源文件
    file(GLOB MVBS_AUX_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/posix_aux/src/*.c"
    )

    # 设置 mvbs_aux 库需要包含的头文件目录
    set(MVBS_AUX_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/posix_aux/include"
        CACHE INTERNAL "INCS for mvbs_aux"
    )

    # 添加构建 mvbs_aux 库的命令
    # 使用 MVBS_AUX_SOURCES 变量中的源文件来构建 mvbs_aux 静态库
    add_library(mvbs_aux STATIC ${MVBS_AUX_SOURCES})

    # 为 mvbs_aux 库指定需要包含的头文件目录，PUBLIC 表示这些头文件目录对于依赖 mvbs_aux 库的其他目标也是可见的
    target_include_directories(mvbs_aux PUBLIC ${MVBS_AUX_HEADERS})
endif()