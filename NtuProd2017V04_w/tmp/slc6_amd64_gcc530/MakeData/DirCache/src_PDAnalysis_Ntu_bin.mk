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
