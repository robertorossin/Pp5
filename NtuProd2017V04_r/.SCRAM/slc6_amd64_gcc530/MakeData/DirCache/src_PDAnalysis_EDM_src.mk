ifeq ($(strip $(PDAnalysis/EDM)),)
ALL_COMMONRULES += src_PDAnalysis_EDM_src
src_PDAnalysis_EDM_src_parent := PDAnalysis/EDM
src_PDAnalysis_EDM_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_PDAnalysis_EDM_src,src/PDAnalysis/EDM/src,LIBRARY))
PDAnalysisEDM := self/PDAnalysis/EDM
PDAnalysis/EDM := PDAnalysisEDM
PDAnalysisEDM_files := $(patsubst src/PDAnalysis/EDM/src/%,%,$(wildcard $(foreach dir,src/PDAnalysis/EDM/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PDAnalysisEDM_BuildFile    := $(WORKINGDIR)/cache/bf/src/PDAnalysis/EDM/BuildFile
PDAnalysisEDM_LOC_FLAGS_CXXFLAGS   := -Wno-delete-non-virtual-dtor
PDAnalysisEDM_LOC_USE := self  root DataFormats/Common DataFormats/PatCandidates NtuAnalysis/Write FWCore/Framework FWCore/ParameterSet PDAnalysis/Ntu
PDAnalysisEDM_EX_LIB   := PDAnalysisEDM
PDAnalysisEDM_EX_USE   := $(foreach d,$(PDAnalysisEDM_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
PDAnalysisEDM_PACKAGE := self/src/PDAnalysis/EDM/src
ALL_PRODS += PDAnalysisEDM
PDAnalysisEDM_CLASS := LIBRARY
PDAnalysis/EDM_forbigobj+=PDAnalysisEDM
PDAnalysisEDM_INIT_FUNC        += $$(eval $$(call Library,PDAnalysisEDM,src/PDAnalysis/EDM/src,src_PDAnalysis_EDM_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
