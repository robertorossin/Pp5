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
