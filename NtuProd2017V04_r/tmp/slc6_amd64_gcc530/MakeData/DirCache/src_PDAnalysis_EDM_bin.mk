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
