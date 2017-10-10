ifeq ($(strip $(NtuTool/EDM)),)
ALL_COMMONRULES += src_NtuTool_EDM_src
src_NtuTool_EDM_src_parent := NtuTool/EDM
src_NtuTool_EDM_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_NtuTool_EDM_src,src/NtuTool/EDM/src,LIBRARY))
NtuToolEDM := self/NtuTool/EDM
NtuTool/EDM := NtuToolEDM
NtuToolEDM_files := $(patsubst src/NtuTool/EDM/src/%,%,$(wildcard $(foreach dir,src/NtuTool/EDM/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
NtuToolEDM_BuildFile    := $(WORKINGDIR)/cache/bf/src/NtuTool/EDM/BuildFile
NtuToolEDM_LOC_FLAGS_CXXFLAGS   := -Wno-delete-non-virtual-dtor
NtuToolEDM_LOC_USE := self  FWCore/Framework NtuTool/Common
NtuToolEDM_EX_LIB   := NtuToolEDM
NtuToolEDM_EX_USE   := $(foreach d,$(NtuToolEDM_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
NtuToolEDM_PACKAGE := self/src/NtuTool/EDM/src
ALL_PRODS += NtuToolEDM
NtuToolEDM_CLASS := LIBRARY
NtuTool/EDM_forbigobj+=NtuToolEDM
NtuToolEDM_INIT_FUNC        += $$(eval $$(call Library,NtuToolEDM,src/NtuTool/EDM/src,src_NtuTool_EDM_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
