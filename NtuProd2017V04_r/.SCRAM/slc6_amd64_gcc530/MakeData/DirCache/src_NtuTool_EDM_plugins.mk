ifeq ($(strip $(NtuToolEDMPlugins)),)
NtuToolEDMPlugins := self/src/NtuTool/EDM/plugins
PLUGINS:=yes
NtuToolEDMPlugins_files := $(patsubst src/NtuTool/EDM/plugins/%,%,$(foreach file,*.cc,$(eval xfile:=$(wildcard src/NtuTool/EDM/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/NtuTool/EDM/plugins/$(file). Please fix src/NtuTool/EDM/plugins/BuildFile.))))
NtuToolEDMPlugins_BuildFile    := $(WORKINGDIR)/cache/bf/src/NtuTool/EDM/plugins/BuildFile
NtuToolEDMPlugins_LOC_FLAGS_CXXFLAGS   := -Wno-delete-non-virtual-dtor
NtuToolEDMPlugins_LOC_USE := self  FWCore/Framework NtuTool/EDM
NtuToolEDMPlugins_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,NtuToolEDMPlugins,NtuToolEDMPlugins,$(SCRAMSTORENAME_LIB),src/NtuTool/EDM/plugins))
NtuToolEDMPlugins_PACKAGE := self/src/NtuTool/EDM/plugins
ALL_PRODS += NtuToolEDMPlugins
NtuTool/EDM_forbigobj+=NtuToolEDMPlugins
NtuToolEDMPlugins_INIT_FUNC        += $$(eval $$(call Library,NtuToolEDMPlugins,src/NtuTool/EDM/plugins,src_NtuTool_EDM_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
NtuToolEDMPlugins_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,NtuToolEDMPlugins,src/NtuTool/EDM/plugins))
endif
ALL_COMMONRULES += src_NtuTool_EDM_plugins
src_NtuTool_EDM_plugins_parent := NtuTool/EDM
src_NtuTool_EDM_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_NtuTool_EDM_plugins,src/NtuTool/EDM/plugins,PLUGINS))
