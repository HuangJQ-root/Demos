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
# mvbs-cfg.mk
#

MVBS_IDL_PATH:= $(patsubst %/,%,$(subst \,/,$(dir $(lastword $(MAKEFILE_LIST)))))

# $1 ==> IDL file path
# $2 ==> output path
define mvbs_idl_srcs
    $(foreach idl,$(strip $(basename $(notdir $1))), $(addprefix $(patsubst %/,%,$(strip $2))/$(idl), Plugin.c))
endef

# $1 ==> IDL file path
# $2 ==> output path
define mvbs_idl_hdrs
    $(foreach idl,$(strip $(basename $(notdir $1))), $(addprefix $(patsubst %/,%,$(strip $2))/$(idl), Plugin.h))
endef

# $1 ==> IDL file path
# $2 ==> output dir path
# $3 ==> Extra Options List
#
# Example:
# $(eval $(call mvbs_idl_generate, $(MVBS_IDL_PATH)/hybrid.idl, out/gen))
#
define mvbs_idl_generate
mvbs_code_gen: $(call mvbs_idl_srcs, $1, $2) $(call mvbs_idl_hdrs, $1, $2)

$(call mvbs_idl_srcs, $1, $2) $(call mvbs_idl_hdrs, $1, $2) &: $1
	@mkdir -p $$(dir $$@)
	@echo "GEN	$$@"
	$(hide)python3 -B $$(MVBS_IDL_PATH)/mvbs-idl.py $3 -i $$< -d $$(dir $$@) -t true
endef

#
# $1 ==> IDL file path
# $2 ==> output dir path
# $3 ==> Extra Options List
#
# Example:
#
# $(call mvbs_idl_setup, $(MVBS_IDL_PATH)/hybrid.idl , out/gen)
#
define mvbs_idl_setup
$(foreach idl, $1, $(eval $(call mvbs_idl_generate, $(idl), $2, $3))
                   $(call mvbs_idl_srcs, $(idl), $2)
                   $(call mvbs_idl_hdrs, $(idl), $2))
endef



# $1 ==> RPC file path
# $2 ==> output path
define mvbs_rpc_srcs
    $(foreach rpc,$(strip $(basename $(notdir $1))), $(addprefix $(patsubst %/,%,$(strip $2))/$(rpc), RpcClient.c RpcServer.c RpcParams.c))
endef

# $1 ==> RPC file path
# $2 ==> output path
define mvbs_rpc_hdrs
    $(foreach rpc,$(strip $(basename $(notdir $1))), $(addprefix $(patsubst %/,%,$(strip $2))/$(rpc), RpcClient.h RpcServer.h RpcParams.h))
endef

# $1 ==> RPC file path
# $2 ==> output path
# $3 ==> Extra Options List
define mvbs_rpc_generate
mvbs_code_gen: $(call mvbs_rpc_srcs, $1, $2) $(call mvbs_rpc_hdrs, $1, $2)

$(call mvbs_rpc_srcs, $1, $2) $(call mvbs_rpc_hdrs, $1, $2) &: $1
	@mkdir -p $$(dir $$@)
	@echo "GEN	$$@"
	$(hide)python3 -B $$(MVBS_IDL_PATH)/mvbs-rpc.py $3 -i $$< -d $$(dir $$@)
endef

define mvbs_rpc_setup
$(foreach rpc, $1, $(eval $(call mvbs_rpc_generate, $(rpc), $2, $3))
                   $(call mvbs_rpc_srcs, $(rpc), $2)
                   $(call mvbs_rpc_hdrs, $(rpc), $2))
endef

# vim:ft=make
#
