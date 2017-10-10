ifeq ($(strip $(NtuToolEDMTest)),)
NtuToolEDMTest := self/src/NtuTool/EDM/test
NtuToolEDMTest_files := $(patsubst src/NtuTool/EDM/test/%,%,$(foreach file,stubs/*.cc,$(eval xfile:=$(wildcard src/NtuTool/EDM/test/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/NtuTool/EDM/test/$(file). Please fix src/NtuTool/EDM/test/BuildFile.))))
NtuToolEDMTest_BuildFile    := $(WORKINGDIR)/cache/bf/src/NtuTool/EDM/test/BuildFile
NtuToolEDMTest_LOC_FLAGS_CXXFLAGS   := -Wno-delete-non-virtual-dtor
NtuToolEDMTest_LOC_USE := self  FWCore/Framework FWCore/ParameterSet NtuTool/Common NtuTool/EDM root
NtuToolEDMTest_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,NtuToolEDMTest,NtuToolEDMTest,$(SCRAMSTORENAME_LIB),src/NtuTool/EDM/test))
NtuToolEDMTest_PACKAGE := self/src/NtuTool/EDM/test
ALL_PRODS += NtuToolEDMTest
NtuToolEDMTest_INIT_FUNC        += $$(eval $$(call Library,NtuToolEDMTest,src/NtuTool/EDM/test,src_NtuTool_EDM_test,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
NtuToolEDMTest_CLASS := TEST_LIBRARY
else
$(eval $(call MultipleWarningMsg,NtuToolEDMTest,src/NtuTool/EDM/test))
endif
ALL_COMMONRULES += src_NtuTool_EDM_test
src_NtuTool_EDM_test_parent := NtuTool/EDM
src_NtuTool_EDM_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_NtuTool_EDM_test,src/NtuTool/EDM/test,TEST))
