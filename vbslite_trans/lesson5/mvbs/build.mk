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

#
# build.mk
#

LOCAL_PATH:= $(call my-dir)

# MVBS Configuration

# mvbs option for performance benchmark test
MVBS_CHECKPOINT_ENABLE:=true
# mvbs option for enable diag backend
MVBS_DIAG_BE_ENABLE:=true
# mvbs option for enable diag fronend
MVBS_DIAG_FE_ENABLE:=false

include $(CLEAR_VARS)
LOCAL_MODULE:= libmvbs.a

LOCAL_SRCS:=$(call all-named-files-under,*.c, src/core	\
                                              src/mcdr	\
                                              src/rte	\
                                              src/rpc)

LOCAL_CFLAGS += -D__MVBS_CORE_SOURCE__

ifeq ($(MVBS_CHECKPOINT_ENABLE),true)
LOCAL_CFLAGS+= -DCHECKPOINT_ENABLE
LOCAL_EXPORT_CFLAGS+= -DCHECKPOINT_ENABLE
endif

ifeq ($(MVBS_DIAG_BE_ENABLE),true)
LOCAL_CFLAGS+= -DMVBS_DIAG_REQUEST_READER_ENABLE	\
	       -DMVBS_DIAG_REPLY_WRITER_ENABLE
endif

ifeq ($(MVBS_DIAG_FE_ENABLE),true)
LOCAL_CFLAGS+= -DMVBS_DIAG_REQUEST_WRITER_ENABLE	\
	       -DMVBS_DIAG_REPLY_READER_ENABLE
endif

LOCAL_INC_DIR:= include src/core/include

LOCAL_EXPORT_INC_DIR:= include

ifeq ($(filter LINUX MINGW J6M_ACORE, $(TARGET_PRODUCT_UPPER)),)
LOCAL_SRCS+=$(call all-named-files-under,*.c, src/adapter/auto/src)
LOCAL_INC_DIR+= src/adapter/auto/include
LOCAL_EXPORT_INC_DIR+= src/adapter/auto/include
else
LOCAL_SRCS+=$(call all-named-files-under,*.c, src/adapter/posix/src)	\
	    src/adapter/posix/src/ipc_j6m.cpp
LOCAL_INC_DIR+= src/adapter/posix/include
LOCAL_EXPORT_INC_DIR+= src/adapter/posix/include
endif

# FIXME:
# TCP Interface hasn't been enabled on J6M_RCORE
ifeq ($(TARGET_PRODUCT_UPPER),J6M_RCORE)
LOCAL_SRCS := $(filter-out src/rpc/% %/tcp.c %/mvbs_adapter_net_tcp.c, $(LOCAL_SRCS))
endif

ifeq ($(filter MINGW LINUX J6M_ACORE,$(TARGET_PRODUCT_UPPER)),)
LOCAL_STATIC_LIBRARIES:=libbsw.a
endif

include $(BUILD_STATIC_LIBRARY)

################################################################################
# The following for generating dynamic library on linux.
################################################################################
include $(CLEAR_VARS)
LOCAL_MODULE:= libmvbs.so

LOCAL_SRCS+=$(call all-named-files-under,*.c, src/core	\
                                              src/mcdr	\
                                              src/rte	\
                                              src/rpc	\
					      src/adapter/posix)

ifeq ($(MVBS_CHECKPOINT_ENABLE),true)
LOCAL_CFLAGS+= -DCHECKPOINT_ENABLE
LOCAL_EXPORT_CFLAGS+= -DCHECKPOINT_ENABLE
endif

ifeq ($(MVBS_DIAG_BE_ENABLE),true)
LOCAL_CFLAGS+= -DMVBS_DIAG_REQUEST_READER_ENABLE	\
	       -DMVBS_DIAG_REPLY_WRITER_ENABLE
endif

ifeq ($(MVBS_DIAG_FE_ENABLE),true)
LOCAL_CFLAGS+= -DMVBS_DIAG_REQUEST_WRITER_ENABLE	\
	       -DMVBS_DIAG_REPLY_READER_ENABLE
endif

LOCAL_INC_DIR:= include src/core/include src/adapter/posix/include

LOCAL_EXPORT_INC_DIR:=include src/adapter/posix/include

LOCAL_MODULE_TARGETS:=J6M_ACORE LINUX

include $(BUILD_SHARED_LIBRARY)

################################################################################
# Provide some helpers
################################################################################
include $(CLEAR_VARS)

LOCAL_MODULE:= libmvbs_aux.a

LOCAL_SRCS:= $(call all-named-files-under,*.c, posix_aux/src)

LOCAL_INC_DIR:= posix_aux/include

LOCAL_EXPORT_INC_DIR:= posix_aux/include

LOCAL_MODULE_TARGETS:= LINUX MINGW J6M_ACORE

include $(BUILD_STATIC_LIBRARY)

# vim:ft=make
#
