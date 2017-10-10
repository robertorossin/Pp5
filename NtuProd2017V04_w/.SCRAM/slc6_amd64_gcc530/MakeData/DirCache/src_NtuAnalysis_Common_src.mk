ifeq ($(strip $(NtuAnalysis/Common)),)
ALL_COMMONRULES += src_NtuAnalysis_Common_src
src_NtuAnalysis_Common_src_parent := NtuAnalysis/Common
src_NtuAnalysis_Common_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_NtuAnalysis_Common_src,src/NtuAnalysis/Common/src,LIBRARY))
NtuAnalysisCommon := self/NtuAnalysis/Common
NtuAnalysis/Common := NtuAnalysisCommon
NtuAnalysisCommon_files := $(patsubst src/NtuAnalysis/Common/src/%,%,$(wildcard $(foreach dir,src/NtuAnalysis/Common/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
NtuAnalysisCommon_BuildFile    := $(WORKINGDIR)/cache/bf/src/NtuAnalysis/Common/BuildFile
NtuAnalysisCommon_LOC_FLAGS_CXXFLAGS   := -Wno-delete-non-virtual-dtor
NtuAnalysisCommon_LOC_USE := self  root NtuTool/Common
NtuAnalysisCommon_EX_LIB   := NtuAnalysisCommon
NtuAnalysisCommon_EX_USE   := $(foreach d,$(NtuAnalysisCommon_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
NtuAnalysisCommon_PACKAGE := self/src/NtuAnalysis/Common/src
ALL_PRODS += NtuAnalysisCommon
NtuAnalysisCommon_CLASS := LIBRARY
NtuAnalysis/Common_forbigobj+=NtuAnalysisCommon
NtuAnalysisCommon_INIT_FUNC        += $$(eval $$(call Library,NtuAnalysisCommon,src/NtuAnalysis/Common/src,src_NtuAnalysis_Common_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
