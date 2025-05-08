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

MVBS_CFG_PATH:= $(patsubst %/,%,$(subst \,/,$(dir $(lastword $(MAKEFILE_LIST)))))

#
# $1 ==> The path of configure file [mvbs_config.xml]
# $2 ==> The file path to be generated
# $3 ==> Extra Options
#
# Example:
#
#  $(eval $(call mvbs_cfg_generate_rule, $(MVBS_CFG_PATH)/mvbs_config.xml, out/src/mvbs_config.c))
#
define mvbs_cfg_generate_rule
mvbs_code_gen: $2

$2: $1 ${MVBS_CFG_PATH}/template/macros.jinja2 ${MVBS_CFG_PATH}/template/mvbs_config.c.jinja2
	@mkdir -p $$(dir $$@)
	@echo "GEN	$$@"
	$(hide)python3 -B $$(MVBS_CFG_PATH)/mvbs-config.py $3 -s $$< -t $$@
endef

#
# $1 ==> The path of configure file [mvbs_config.xml]
# $2 ==> The dir path to be output or a file path
# $3 ==> Extra Options List
#
# Example:
#
#  $(eval $(call mvbs_cfg_generate, $(MVBS_CFG_PATH)/mvbs_config.xml, out/src/))
#
# FIXME:
# define join-path
# $(subst /./,/, $(subst //,/,$(1)/$(2)))
# endef
#
# $(eval $(call mvbs_cfg_generate_rule, $1, $(call join-path,$(2),$(basename $(1)).c), $3)) $(call join-path,$(2),$(basename $(1)).c)
#
define mvbs_cfg_generate
$(if $(filter %.c %.h,$(2)),
     $(eval $(call mvbs_cfg_generate_rule, $1, $2, $3)) $2,
     $(eval $(call mvbs_cfg_generate_rule, $1, $(2)/$(basename $(notdir $(1))).c, $3)) $(2)/$(basename $(notdir $(1))).c
)
endef


# $1 ==> The path of configure file [mvbs_config.xml]
# $2 ==> The file path to be generated
# $3 ==> Extra options list
#
# Example:
#
# $(call mvbs_cfg_setup, $(MVBS_CFG_PATH)/mvbs_config.xml, out/src/mvbs_config.c)
#
define mvbs_cfg_setup
$(foreach dest, $2, $(call mvbs_cfg_generate, $1, $(dest), $3))
endef

define mvbs_cfg_test_setup
$(foreach dest, $2, $(call mvbs_cfg_generate, $1, $(dest), --test $3))
endef

# vim:ft=make
#
