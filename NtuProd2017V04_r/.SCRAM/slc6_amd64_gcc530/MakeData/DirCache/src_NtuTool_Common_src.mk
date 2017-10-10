ifeq ($(strip $(NtuTool/Common)),)
ALL_COMMONRULES += src_NtuTool_Common_src
src_NtuTool_Common_src_parent := NtuTool/Common
src_NtuTool_Common_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_NtuTool_Common_src,src/NtuTool/Common/src,LIBRARY))
NtuToolCommon := self/NtuTool/Common
NtuTool/Common := NtuToolCommon
NtuToolCommon_files := $(patsubst src/NtuTool/Common/src/%,%,$(wildcard $(foreach dir,src/NtuTool/Common/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
NtuToolCommon_BuildFile    := $(WORKINGDIR)/cache/bf/src/NtuTool/Common/BuildFile
NtuToolCommon_LOC_LIB   := Rint
NtuToolCommon_LOC_USE := self  root
NtuToolCommon_EX_LIB   := NtuToolCommon
NtuToolCommon_EX_USE   := $(foreach d,$(NtuToolCommon_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
NtuToolCommon_PACKAGE := self/src/NtuTool/Common/src
ALL_PRODS += NtuToolCommon
NtuToolCommon_CLASS := LIBRARY
NtuTool/Common_forbigobj+=NtuToolCommon
NtuToolCommon_INIT_FUNC        += $$(eval $$(call Library,NtuToolCommon,src/NtuTool/Common/src,src_NtuTool_Common_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
