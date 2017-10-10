ifeq ($(strip $(BPHAnalysis/SpecificDecay)),)
ALL_COMMONRULES += src_BPHAnalysis_SpecificDecay_src
src_BPHAnalysis_SpecificDecay_src_parent := BPHAnalysis/SpecificDecay
src_BPHAnalysis_SpecificDecay_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_BPHAnalysis_SpecificDecay_src,src/BPHAnalysis/SpecificDecay/src,LIBRARY))
BPHAnalysisSpecificDecay := self/BPHAnalysis/SpecificDecay
BPHAnalysis/SpecificDecay := BPHAnalysisSpecificDecay
BPHAnalysisSpecificDecay_files := $(patsubst src/BPHAnalysis/SpecificDecay/src/%,%,$(wildcard $(foreach dir,src/BPHAnalysis/SpecificDecay/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
BPHAnalysisSpecificDecay_BuildFile    := $(WORKINGDIR)/cache/bf/src/BPHAnalysis/SpecificDecay/BuildFile
BPHAnalysisSpecificDecay_LOC_USE := self  BPHAnalysis/RecoDecay DataFormats/ParticleFlowCandidate DataFormats/PatCandidates DataFormats/RecoCandidate DataFormats/TrackReco DataFormats/VertexReco FWCore/Framework PhysicsTools/CandUtils RecoVertex/KalmanVertexFit RecoVertex/KinematicFit RecoVertex/KinematicFitPrimitives RecoVertex/VertexPrimitives TrackingTools/PatternTools TrackingTools/Records TrackingTools/TransientTrack
BPHAnalysisSpecificDecay_LCGDICTS  := x 
BPHAnalysisSpecificDecay_PRE_INIT_FUNC += $$(eval $$(call LCGDict,BPHAnalysisSpecificDecay,src/BPHAnalysis/SpecificDecay/src/classes.h,src/BPHAnalysis/SpecificDecay/src/classes_def.xml,$(SCRAMSTORENAME_LIB),$(GENREFLEX_ARGS) --fail_on_warnings,))
BPHAnalysisSpecificDecay_EX_LIB   := BPHAnalysisSpecificDecay
BPHAnalysisSpecificDecay_EX_USE   := $(foreach d,$(BPHAnalysisSpecificDecay_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
BPHAnalysisSpecificDecay_PACKAGE := self/src/BPHAnalysis/SpecificDecay/src
ALL_PRODS += BPHAnalysisSpecificDecay
BPHAnalysisSpecificDecay_CLASS := LIBRARY
BPHAnalysis/SpecificDecay_forbigobj+=BPHAnalysisSpecificDecay
BPHAnalysisSpecificDecay_INIT_FUNC        += $$(eval $$(call Library,BPHAnalysisSpecificDecay,src/BPHAnalysis/SpecificDecay/src,src_BPHAnalysis_SpecificDecay_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
