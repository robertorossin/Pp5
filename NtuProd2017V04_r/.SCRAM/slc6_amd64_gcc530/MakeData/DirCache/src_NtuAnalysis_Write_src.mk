ifeq ($(strip $(NtuAnalysis/Write)),)
ALL_COMMONRULES += src_NtuAnalysis_Write_src
src_NtuAnalysis_Write_src_parent := NtuAnalysis/Write
src_NtuAnalysis_Write_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_NtuAnalysis_Write_src,src/NtuAnalysis/Write/src,LIBRARY))
NtuAnalysisWrite := self/NtuAnalysis/Write
NtuAnalysis/Write := NtuAnalysisWrite
NtuAnalysisWrite_files := $(patsubst src/NtuAnalysis/Write/src/%,%,$(wildcard $(foreach dir,src/NtuAnalysis/Write/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
NtuAnalysisWrite_BuildFile    := $(WORKINGDIR)/cache/bf/src/NtuAnalysis/Write/BuildFile
NtuAnalysisWrite_LOC_FLAGS_CXXFLAGS   := -Wno-delete-non-virtual-dtor
NtuAnalysisWrite_LOC_USE := self  root FWCore/Framework FWCore/ParameterSet NtuAnalysis/Common NtuTool/Common NtuTool/EDM
NtuAnalysisWrite_EX_LIB   := NtuAnalysisWrite
NtuAnalysisWrite_EX_USE   := $(foreach d,$(NtuAnalysisWrite_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
NtuAnalysisWrite_PACKAGE := self/src/NtuAnalysis/Write/src
ALL_PRODS += NtuAnalysisWrite
NtuAnalysisWrite_CLASS := LIBRARY
NtuAnalysis/Write_forbigobj+=NtuAnalysisWrite
NtuAnalysisWrite_INIT_FUNC        += $$(eval $$(call Library,NtuAnalysisWrite,src/NtuAnalysis/Write/src,src_NtuAnalysis_Write_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
