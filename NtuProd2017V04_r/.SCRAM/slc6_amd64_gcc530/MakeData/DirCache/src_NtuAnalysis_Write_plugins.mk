ifeq ($(strip $(NtuAnalysisWritePlugins)),)
NtuAnalysisWritePlugins := self/src/NtuAnalysis/Write/plugins
PLUGINS:=yes
NtuAnalysisWritePlugins_files := $(patsubst src/NtuAnalysis/Write/plugins/%,%,$(foreach file,*.cc,$(eval xfile:=$(wildcard src/NtuAnalysis/Write/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/NtuAnalysis/Write/plugins/$(file). Please fix src/NtuAnalysis/Write/plugins/BuildFile.))))
NtuAnalysisWritePlugins_BuildFile    := $(WORKINGDIR)/cache/bf/src/NtuAnalysis/Write/plugins/BuildFile
NtuAnalysisWritePlugins_LOC_FLAGS_CXXFLAGS   := -Wno-delete-non-virtual-dtor
NtuAnalysisWritePlugins_LOC_USE := self  FWCore/ParameterSet FWCore/Framework FWCore/PluginManager NtuAnalysis/Common
NtuAnalysisWritePlugins_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,NtuAnalysisWritePlugins,NtuAnalysisWritePlugins,$(SCRAMSTORENAME_LIB),src/NtuAnalysis/Write/plugins))
NtuAnalysisWritePlugins_PACKAGE := self/src/NtuAnalysis/Write/plugins
ALL_PRODS += NtuAnalysisWritePlugins
NtuAnalysis/Write_forbigobj+=NtuAnalysisWritePlugins
NtuAnalysisWritePlugins_INIT_FUNC        += $$(eval $$(call Library,NtuAnalysisWritePlugins,src/NtuAnalysis/Write/plugins,src_NtuAnalysis_Write_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
NtuAnalysisWritePlugins_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,NtuAnalysisWritePlugins,src/NtuAnalysis/Write/plugins))
endif
ALL_COMMONRULES += src_NtuAnalysis_Write_plugins
src_NtuAnalysis_Write_plugins_parent := NtuAnalysis/Write
src_NtuAnalysis_Write_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_NtuAnalysis_Write_plugins,src/NtuAnalysis/Write/plugins,PLUGINS))
