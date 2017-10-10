ifeq ($(strip $(HeavyFlavorSpecificDecaysPlugins)),)
HeavyFlavorSpecificDecaysPlugins := self/src/BPHAnalysis/SpecificDecay/plugins
PLUGINS:=yes
HeavyFlavorSpecificDecaysPlugins_files := $(patsubst src/BPHAnalysis/SpecificDecay/plugins/%,%,$(foreach file,*.cc,$(eval xfile:=$(wildcard src/BPHAnalysis/SpecificDecay/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/BPHAnalysis/SpecificDecay/plugins/$(file). Please fix src/BPHAnalysis/SpecificDecay/plugins/BuildFile.))))
HeavyFlavorSpecificDecaysPlugins_BuildFile    := $(WORKINGDIR)/cache/bf/src/BPHAnalysis/SpecificDecay/plugins/BuildFile
HeavyFlavorSpecificDecaysPlugins_LOC_USE := self  root BPHAnalysis/RecoDecay BPHAnalysis/SpecificDecay DataFormats/ParticleFlowCandidate DataFormats/PatCandidates DataFormats/TrackReco FWCore/Framework FWCore/ParameterSet FWCore/MessageLogger FWCore/ServiceRegistry PhysicsTools/UtilAlgos
HeavyFlavorSpecificDecaysPlugins_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,HeavyFlavorSpecificDecaysPlugins,HeavyFlavorSpecificDecaysPlugins,$(SCRAMSTORENAME_LIB),src/BPHAnalysis/SpecificDecay/plugins))
HeavyFlavorSpecificDecaysPlugins_PACKAGE := self/src/BPHAnalysis/SpecificDecay/plugins
ALL_PRODS += HeavyFlavorSpecificDecaysPlugins
BPHAnalysis/SpecificDecay_forbigobj+=HeavyFlavorSpecificDecaysPlugins
HeavyFlavorSpecificDecaysPlugins_INIT_FUNC        += $$(eval $$(call Library,HeavyFlavorSpecificDecaysPlugins,src/BPHAnalysis/SpecificDecay/plugins,src_BPHAnalysis_SpecificDecay_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
HeavyFlavorSpecificDecaysPlugins_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,HeavyFlavorSpecificDecaysPlugins,src/BPHAnalysis/SpecificDecay/plugins))
endif
ALL_COMMONRULES += src_BPHAnalysis_SpecificDecay_plugins
src_BPHAnalysis_SpecificDecay_plugins_parent := BPHAnalysis/SpecificDecay
src_BPHAnalysis_SpecificDecay_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_BPHAnalysis_SpecificDecay_plugins,src/BPHAnalysis/SpecificDecay/plugins,PLUGINS))
