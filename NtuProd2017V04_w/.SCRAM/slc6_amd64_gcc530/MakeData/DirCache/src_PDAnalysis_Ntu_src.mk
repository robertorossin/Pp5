ifeq ($(strip $(PDAnalysis/Ntu)),)
ALL_COMMONRULES += src_PDAnalysis_Ntu_src
src_PDAnalysis_Ntu_src_parent := PDAnalysis/Ntu
src_PDAnalysis_Ntu_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_PDAnalysis_Ntu_src,src/PDAnalysis/Ntu/src,LIBRARY))
PDAnalysisNtu := self/PDAnalysis/Ntu
PDAnalysis/Ntu := PDAnalysisNtu
PDAnalysisNtu_files := $(patsubst src/PDAnalysis/Ntu/src/%,%,$(wildcard $(foreach dir,src/PDAnalysis/Ntu/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PDAnalysisNtu_BuildFile    := $(WORKINGDIR)/cache/bf/src/PDAnalysis/Ntu/BuildFile
PDAnalysisNtu_LOC_USE := self  NtuAnalysis/Common
PDAnalysisNtu_EX_LIB   := PDAnalysisNtu
PDAnalysisNtu_EX_USE   := $(foreach d,$(PDAnalysisNtu_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
PDAnalysisNtu_PACKAGE := self/src/PDAnalysis/Ntu/src
ALL_PRODS += PDAnalysisNtu
PDAnalysisNtu_CLASS := LIBRARY
PDAnalysis/Ntu_forbigobj+=PDAnalysisNtu
PDAnalysisNtu_INIT_FUNC        += $$(eval $$(call Library,PDAnalysisNtu,src/PDAnalysis/Ntu/src,src_PDAnalysis_Ntu_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
