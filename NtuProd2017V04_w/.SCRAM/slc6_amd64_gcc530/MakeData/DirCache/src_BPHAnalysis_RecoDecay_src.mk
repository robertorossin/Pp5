ifeq ($(strip $(BPHAnalysis/RecoDecay)),)
ALL_COMMONRULES += src_BPHAnalysis_RecoDecay_src
src_BPHAnalysis_RecoDecay_src_parent := BPHAnalysis/RecoDecay
src_BPHAnalysis_RecoDecay_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_BPHAnalysis_RecoDecay_src,src/BPHAnalysis/RecoDecay/src,LIBRARY))
BPHAnalysisRecoDecay := self/BPHAnalysis/RecoDecay
BPHAnalysis/RecoDecay := BPHAnalysisRecoDecay
BPHAnalysisRecoDecay_files := $(patsubst src/BPHAnalysis/RecoDecay/src/%,%,$(wildcard $(foreach dir,src/BPHAnalysis/RecoDecay/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
BPHAnalysisRecoDecay_BuildFile    := $(WORKINGDIR)/cache/bf/src/BPHAnalysis/RecoDecay/BuildFile
BPHAnalysisRecoDecay_LOC_USE := self  DataFormats/Math DataFormats/ParticleFlowCandidate DataFormats/PatCandidates DataFormats/RecoCandidate DataFormats/TrackReco DataFormats/VertexReco FWCore/Framework FWCore/MessageLogger PhysicsTools/CandUtils RecoVertex/KalmanVertexFit RecoVertex/KinematicFit RecoVertex/KinematicFitPrimitives RecoVertex/VertexPrimitives TrackingTools/PatternTools TrackingTools/Records TrackingTools/TransientTrack
BPHAnalysisRecoDecay_EX_LIB   := BPHAnalysisRecoDecay
BPHAnalysisRecoDecay_EX_USE   := $(foreach d,$(BPHAnalysisRecoDecay_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
BPHAnalysisRecoDecay_PACKAGE := self/src/BPHAnalysis/RecoDecay/src
ALL_PRODS += BPHAnalysisRecoDecay
BPHAnalysisRecoDecay_CLASS := LIBRARY
BPHAnalysis/RecoDecay_forbigobj+=BPHAnalysisRecoDecay
BPHAnalysisRecoDecay_INIT_FUNC        += $$(eval $$(call Library,BPHAnalysisRecoDecay,src/BPHAnalysis/RecoDecay/src,src_BPHAnalysis_RecoDecay_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
