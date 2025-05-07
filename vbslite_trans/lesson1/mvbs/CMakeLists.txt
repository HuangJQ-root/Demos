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
    file(GLOB_RECURSE MVBS_SRCS_CURRENT
        "${MVBS_SOURCE_DIR}/core/*.c"
        "${MVBS_SOURCE_DIR}/mcdr/*.c"
        "${MVBS_SOURCE_DIR}/rte/*.c"
        "${MVBS_SOURCE_DIR}/rpc/*.c"
        "${MVBS_SOURCE_DIR}/adapter/posix/*.c"  # 只包含 posix 相关的源文件
    )

    list(REMOVE_ITEM MVBS_SRCS_CURRENT
    "${MVBS_SOURCE_DIR}/rte/Dds_Adaptor_Interface.c"
    )

    set(MVBS_SOURCES
        ${MVBS_SRCS_CURRENT}
        CACHE INTERNAL "SRCS for mvbs"
    )

    set(MVBS_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/posix_aux/include"
        "${MVBS_SOURCE_DIR}/core/include"
        "${MVBS_SOURCE_DIR}/adapter/posix/include"  # 只包含 posix 相关的头文件目录
        CACHE INTERNAL "INCS for mvbs"
    )

    # 添加构建 mvbs 库的命令
    add_library(mvbs STATIC ${MVBS_SOURCES})
    target_include_directories(mvbs PUBLIC ${MVBS_HEADERS})

    # 构建 mvbs_aux 库
    file(GLOB MVBS_AUX_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/posix_aux/src/*.c"
    )
    add_library(mvbs_aux STATIC ${MVBS_AUX_SOURCES})
    target_include_directories(mvbs_aux PUBLIC ${MVBS_HEADERS})
endif()