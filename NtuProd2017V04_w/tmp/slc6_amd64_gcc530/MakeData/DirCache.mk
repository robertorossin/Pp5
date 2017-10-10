ALL_COMMONRULES += src_NtuTool_Read_test
src_NtuTool_Read_test_parent := NtuTool/Read
src_NtuTool_Read_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_NtuTool_Read_test,src/NtuTool/Read/test,TEST))
ALL_PACKAGES += PDAnalysis/uty
subdirs_src_PDAnalysis_uty := 
ifeq ($(strip $(pdFWLite)),)
pdFWLite := self/src/PDAnalysis/EDM/bin
pdFWLite_files := $(patsubst src/PDAnalysis/EDM/bin/%,%,$(foreach file,pdFWLite.cc,$(eval xfile:=$(wildcard src/PDAnalysis/EDM/bin/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PDAnalysis/EDM/bin/$(file). Please fix src/PDAnalysis/EDM/bin/BuildFile.))))
pdFWLite_BuildFile    := $(WORKINGDIR)/cache/bf/src/PDAnalysis/EDM/bin/BuildFile
pdFWLite_LOC_FLAGS_CXXFLAGS   := -Wno-delete-non-virtual-dtor
pdFWLite_LOC_USE := self  root DataFormats/Common DataFormats/FWLite FWCore/FWLite FWCore/ParameterSet FWCore/PythonParameterSet PhysicsTools/FWLite NtuAnalysis/Write PDAnalysis/EDM
pdFWLite_PACKAGE := self/src/PDAnalysis/EDM/bin
ALL_PRODS += pdFWLite
pdFWLite_INIT_FUNC        += $$(eval $$(call Binary,pdFWLite,src/PDAnalysis/EDM/bin,src_PDAnalysis_EDM_bin,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_BIN),bin,$(SCRAMSTORENAME_LOGS)))
pdFWLite_CLASS := BINARY
else
$(eval $(call MultipleWarningMsg,pdFWLite,src/PDAnalysis/EDM/bin))
endif
ALL_COMMONRULES += src_PDAnalysis_EDM_bin
src_PDAnalysis_EDM_bin_parent := PDAnalysis/EDM
src_PDAnalysis_EDM_bin_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PDAnalysis_EDM_bin,src/PDAnalysis/EDM/bin,BINARY))
ALL_PACKAGES += NtuTool/Common
subdirs_src_NtuTool_Common := src_NtuTool_Common_interface src_NtuTool_Common_src src_NtuTool_Common_test
ifeq ($(strip $(BPHAnalysisRecoDecayTest)),)
BPHAnalysisRecoDecayTest := self/src/BPHAnalysis/RecoDecay/test
BPHAnalysisRecoDecayTest_files := $(patsubst src/BPHAnalysis/RecoDecay/test/%,%,$(foreach file,stubs/*.cc,$(eval xfile:=$(wildcard src/BPHAnalysis/RecoDecay/test/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/BPHAnalysis/RecoDecay/test/$(file). Please fix src/BPHAnalysis/RecoDecay/test/BuildFile.))))
BPHAnalysisRecoDecayTest_BuildFile    := $(WORKINGDIR)/cache/bf/src/BPHAnalysis/RecoDecay/test/BuildFile
BPHAnalysisRecoDecayTest_LOC_USE := self  root BPHAnalysis/RecoDecay DataFormats/ParticleFlowCandidate DataFormats/PatCandidates DataFormats/TrackReco FWCore/Framework FWCore/ParameterSet
BPHAnalysisRecoDecayTest_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,BPHAnalysisRecoDecayTest,BPHAnalysisRecoDecayTest,$(SCRAMSTORENAME_LIB),src/BPHAnalysis/RecoDecay/test))
BPHAnalysisRecoDecayTest_PACKAGE := self/src/BPHAnalysis/RecoDecay/test
ALL_PRODS += BPHAnalysisRecoDecayTest
BPHAnalysisRecoDecayTest_INIT_FUNC        += $$(eval $$(call Library,BPHAnalysisRecoDecayTest,src/BPHAnalysis/RecoDecay/test,src_BPHAnalysis_RecoDecay_test,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
BPHAnalysisRecoDecayTest_CLASS := TEST_LIBRARY
else
$(eval $(call MultipleWarningMsg,BPHAnalysisRecoDecayTest,src/BPHAnalysis/RecoDecay/test))
endif
ALL_COMMONRULES += src_BPHAnalysis_RecoDecay_test
src_BPHAnalysis_RecoDecay_test_parent := BPHAnalysis/RecoDecay
src_BPHAnalysis_RecoDecay_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_BPHAnalysis_RecoDecay_test,src/BPHAnalysis/RecoDecay/test,TEST))
ALL_PACKAGES += NtuAnalysis/Write
subdirs_src_NtuAnalysis_Write := src_NtuAnalysis_Write_src src_NtuAnalysis_Write_plugins
ALL_PACKAGES += NtuAnalysis/Template
subdirs_src_NtuAnalysis_Template := 
ALL_COMMONRULES += src_NtuTool_Read_bin
src_NtuTool_Read_bin_parent := NtuTool/Read
src_NtuTool_Read_bin_INIT_FUNC += $$(eval $$(call CommonProductRules,src_NtuTool_Read_bin,src/NtuTool/Read/bin,BINARY))
ALL_PACKAGES += NtuAnalysis/Common
subdirs_src_NtuAnalysis_Common := src_NtuAnalysis_Common_interface src_NtuAnalysis_Common_src
ALL_PACKAGES += NtuAnalysis/Read
subdirs_src_NtuAnalysis_Read := 
ALL_COMMONRULES += src_NtuTool_Common_test
src_NtuTool_Common_test_parent := NtuTool/Common
src_NtuTool_Common_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_NtuTool_Common_test,src/NtuTool/Common/test,TEST))
ALL_SUBSYSTEMS+=NtuTool
subdirs_src_NtuTool = src_NtuTool_uty src_NtuTool_Read src_NtuTool_EDM src_NtuTool_Common
ALL_PACKAGES += PDAnalysis/EDM
subdirs_src_PDAnalysis_EDM := src_PDAnalysis_EDM_interface src_PDAnalysis_EDM_src src_PDAnalysis_EDM_plugins src_PDAnalysis_EDM_bin
ALL_PACKAGES += BPHAnalysis/uty
subdirs_src_BPHAnalysis_uty := 
ALL_SUBSYSTEMS+=BPHAnalysis
subdirs_src_BPHAnalysis = src_BPHAnalysis_uty src_BPHAnalysis_RecoDecay src_BPHAnalysis_SpecificDecay
ALL_PACKAGES += NtuTool/EDM
subdirs_src_NtuTool_EDM := src_NtuTool_EDM_interface src_NtuTool_EDM_src src_NtuTool_EDM_plugins src_NtuTool_EDM_test
ifeq ($(strip $(pdTreeAnalyze)),)
pdTreeAnalyze := self/src/PDAnalysis/Ntu/bin
pdTreeAnalyze_files := $(patsubst src/PDAnalysis/Ntu/bin/%,%,$(foreach file,treeAnalyze.cc,$(eval xfile:=$(wildcard src/PDAnalysis/Ntu/bin/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PDAnalysis/Ntu/bin/$(file). Please fix src/PDAnalysis/Ntu/bin/BuildFile.))))
pdTreeAnalyze_BuildFile    := $(WORKINGDIR)/cache/bf/src/PDAnalysis/Ntu/bin/BuildFile
pdTreeAnalyze_LOC_USE := self  root NtuAnalysis/Common NtuTool/Common NtuTool/Read PDAnalysis/Ntu
pdTreeAnalyze_PACKAGE := self/src/PDAnalysis/Ntu/bin
ALL_PRODS += pdTreeAnalyze
pdTreeAnalyze_INIT_FUNC        += $$(eval $$(call Binary,pdTreeAnalyze,src/PDAnalysis/Ntu/bin,src_PDAnalysis_Ntu_bin,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_BIN),bin,$(SCRAMSTORENAME_LOGS)))
pdTreeAnalyze_CLASS := BINARY
else
$(eval $(call MultipleWarningMsg,pdTreeAnalyze,src/PDAnalysis/Ntu/bin))
endif
ALL_COMMONRULES += src_PDAnalysis_Ntu_bin
src_PDAnalysis_Ntu_bin_parent := PDAnalysis/Ntu
src_PDAnalysis_Ntu_bin_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PDAnalysis_Ntu_bin,src/PDAnalysis/Ntu/bin,BINARY))
ALL_PACKAGES += NtuTool/Read
subdirs_src_NtuTool_Read := src_NtuTool_Read_interface src_NtuTool_Read_src src_NtuTool_Read_test src_NtuTool_Read_bin
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
ALL_SUBSYSTEMS+=PDAnalysis
subdirs_src_PDAnalysis = src_PDAnalysis_Ntu src_PDAnalysis_uty src_PDAnalysis_EDM
ALL_PACKAGES += BPHAnalysis/RecoDecay
subdirs_src_BPHAnalysis_RecoDecay := src_BPHAnalysis_RecoDecay_src src_BPHAnalysis_RecoDecay_test
ALL_PACKAGES += NtuTool/uty
subdirs_src_NtuTool_uty := 
ALL_PACKAGES += BPHAnalysis/SpecificDecay
subdirs_src_BPHAnalysis_SpecificDecay := src_BPHAnalysis_SpecificDecay_interface src_BPHAnalysis_SpecificDecay_src src_BPHAnalysis_SpecificDecay_plugins src_BPHAnalysis_SpecificDecay_test src_BPHAnalysis_SpecificDecay_python
ALL_SUBSYSTEMS+=NtuAnalysis
subdirs_src_NtuAnalysis = src_NtuAnalysis_uty src_NtuAnalysis_Template src_NtuAnalysis_Write src_NtuAnalysis_Read src_NtuAnalysis_Common
ALL_PACKAGES += PDAnalysis/Ntu
subdirs_src_PDAnalysis_Ntu := src_PDAnalysis_Ntu_interface src_PDAnalysis_Ntu_src src_PDAnalysis_Ntu_bin
ifeq ($(strip $(BPHAnalysisSpecificDecayTest)),)
BPHAnalysisSpecificDecayTest := self/src/BPHAnalysis/SpecificDecay/test
BPHAnalysisSpecificDecayTest_files := $(patsubst src/BPHAnalysis/SpecificDecay/test/%,%,$(foreach file,stubs/*.cc,$(eval xfile:=$(wildcard src/BPHAnalysis/SpecificDecay/test/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/BPHAnalysis/SpecificDecay/test/$(file). Please fix src/BPHAnalysis/SpecificDecay/test/BuildFile.))))
BPHAnalysisSpecificDecayTest_BuildFile    := $(WORKINGDIR)/cache/bf/src/BPHAnalysis/SpecificDecay/test/BuildFile
BPHAnalysisSpecificDecayTest_LOC_USE := self  root BPHAnalysis/RecoDecay BPHAnalysis/SpecificDecay DataFormats/ParticleFlowCandidate DataFormats/PatCandidates DataFormats/TrackReco FWCore/Framework FWCore/ParameterSet
BPHAnalysisSpecificDecayTest_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,BPHAnalysisSpecificDecayTest,BPHAnalysisSpecificDecayTest,$(SCRAMSTORENAME_LIB),src/BPHAnalysis/SpecificDecay/test))
BPHAnalysisSpecificDecayTest_PACKAGE := self/src/BPHAnalysis/SpecificDecay/test
ALL_PRODS += BPHAnalysisSpecificDecayTest
BPHAnalysisSpecificDecayTest_INIT_FUNC        += $$(eval $$(call Library,BPHAnalysisSpecificDecayTest,src/BPHAnalysis/SpecificDecay/test,src_BPHAnalysis_SpecificDecay_test,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
BPHAnalysisSpecificDecayTest_CLASS := TEST_LIBRARY
else
$(eval $(call MultipleWarningMsg,BPHAnalysisSpecificDecayTest,src/BPHAnalysis/SpecificDecay/test))
endif
ALL_COMMONRULES += src_BPHAnalysis_SpecificDecay_test
src_BPHAnalysis_SpecificDecay_test_parent := BPHAnalysis/SpecificDecay
src_BPHAnalysis_SpecificDecay_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_BPHAnalysis_SpecificDecay_test,src/BPHAnalysis/SpecificDecay/test,TEST))
ifeq ($(strip $(PyBPHAnalysisSpecificDecay)),)
PyBPHAnalysisSpecificDecay := self/src/BPHAnalysis/SpecificDecay/python
src_BPHAnalysis_SpecificDecay_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/BPHAnalysis/SpecificDecay/python)
PyBPHAnalysisSpecificDecay_files := $(patsubst src/BPHAnalysis/SpecificDecay/python/%,%,$(wildcard $(foreach dir,src/BPHAnalysis/SpecificDecay/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyBPHAnalysisSpecificDecay_LOC_USE := self  
PyBPHAnalysisSpecificDecay_PACKAGE := self/src/BPHAnalysis/SpecificDecay/python
ALL_PRODS += PyBPHAnalysisSpecificDecay
PyBPHAnalysisSpecificDecay_INIT_FUNC        += $$(eval $$(call PythonProduct,PyBPHAnalysisSpecificDecay,src/BPHAnalysis/SpecificDecay/python,src_BPHAnalysis_SpecificDecay_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyBPHAnalysisSpecificDecay,src/BPHAnalysis/SpecificDecay/python))
endif
ALL_COMMONRULES += src_BPHAnalysis_SpecificDecay_python
src_BPHAnalysis_SpecificDecay_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_BPHAnalysis_SpecificDecay_python,src/BPHAnalysis/SpecificDecay/python,PYTHON))
ALL_PACKAGES += NtuAnalysis/uty
subdirs_src_NtuAnalysis_uty := 
