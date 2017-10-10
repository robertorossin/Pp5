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
