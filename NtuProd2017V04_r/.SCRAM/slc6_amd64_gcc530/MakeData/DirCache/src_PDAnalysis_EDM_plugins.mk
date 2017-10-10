ifeq ($(strip $(PDAnalysisEDMPlugins)),)
PDAnalysisEDMPlugins := self/src/PDAnalysis/EDM/plugins
PLUGINS:=yes
PDAnalysisEDMPlugins_files := $(patsubst src/PDAnalysis/EDM/plugins/%,%,$(foreach file,*.cc,$(eval xfile:=$(wildcard src/PDAnalysis/EDM/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PDAnalysis/EDM/plugins/$(file). Please fix src/PDAnalysis/EDM/plugins/BuildFile.))))
PDAnalysisEDMPlugins_BuildFile    := $(WORKINGDIR)/cache/bf/src/PDAnalysis/EDM/plugins/BuildFile
PDAnalysisEDMPlugins_LOC_FLAGS_CXXFLAGS   := -Wno-delete-non-virtual-dtor
PDAnalysisEDMPlugins_LOC_USE := self  FWCore/Framework NtuAnalysis/Write PDAnalysis/EDM
PDAnalysisEDMPlugins_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,PDAnalysisEDMPlugins,PDAnalysisEDMPlugins,$(SCRAMSTORENAME_LIB),src/PDAnalysis/EDM/plugins))
PDAnalysisEDMPlugins_PACKAGE := self/src/PDAnalysis/EDM/plugins
ALL_PRODS += PDAnalysisEDMPlugins
PDAnalysis/EDM_forbigobj+=PDAnalysisEDMPlugins
PDAnalysisEDMPlugins_INIT_FUNC        += $$(eval $$(call Library,PDAnalysisEDMPlugins,src/PDAnalysis/EDM/plugins,src_PDAnalysis_EDM_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
PDAnalysisEDMPlugins_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,PDAnalysisEDMPlugins,src/PDAnalysis/EDM/plugins))
endif
ALL_COMMONRULES += src_PDAnalysis_EDM_plugins
src_PDAnalysis_EDM_plugins_parent := PDAnalysis/EDM
src_PDAnalysis_EDM_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PDAnalysis_EDM_plugins,src/PDAnalysis/EDM/plugins,PLUGINS))
