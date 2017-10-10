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
ifeq ($(strip $(PDAnalysis/EDM)),)
ALL_COMMONRULES += src_PDAnalysis_EDM_src
src_PDAnalysis_EDM_src_parent := PDAnalysis/EDM
src_PDAnalysis_EDM_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_PDAnalysis_EDM_src,src/PDAnalysis/EDM/src,LIBRARY))
PDAnalysisEDM := self/PDAnalysis/EDM
PDAnalysis/EDM := PDAnalysisEDM
PDAnalysisEDM_files := $(patsubst src/PDAnalysis/EDM/src/%,%,$(wildcard $(foreach dir,src/PDAnalysis/EDM/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PDAnalysisEDM_BuildFile    := $(WORKINGDIR)/cache/bf/src/PDAnalysis/EDM/BuildFile
PDAnalysisEDM_LOC_FLAGS_CXXFLAGS   := -Wno-delete-non-virtual-dtor
PDAnalysisEDM_LOC_USE := self  root CommonTools/Utils DataFormats/FWLite DataFormats/MuonReco DataFormats/ParticleFlowCandidate FWCore/ParameterSet FWCore/Framework FWCore/PluginManager HLTrigger/HLTcore DataFormats/PatCandidates PhysicsTools/CandUtils PhysicsTools/Utilities PhysicsTools/FWLite CommonTools/CandUtils PhysicsTools/UtilAlgos PhysicsTools/PatUtils RecoVertex/KalmanVertexFit NtuTool/Common NtuTool/Read NtuTool/EDM NtuAnalysis/Common NtuAnalysis/Write PDAnalysis/Ntu BPHAnalysis/RecoDecay BPHAnalysis/SpecificDecay
PDAnalysisEDM_EX_LIB   := PDAnalysisEDM
PDAnalysisEDM_EX_USE   := $(foreach d,$(PDAnalysisEDM_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
PDAnalysisEDM_PACKAGE := self/src/PDAnalysis/EDM/src
ALL_PRODS += PDAnalysisEDM
PDAnalysisEDM_CLASS := LIBRARY
PDAnalysis/EDM_forbigobj+=PDAnalysisEDM
PDAnalysisEDM_INIT_FUNC        += $$(eval $$(call Library,PDAnalysisEDM,src/PDAnalysis/EDM/src,src_PDAnalysis_EDM_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
ifeq ($(strip $(PDAnalysis/Ntu)),)
ALL_COMMONRULES += src_PDAnalysis_Ntu_src
src_PDAnalysis_Ntu_src_parent := PDAnalysis/Ntu
src_PDAnalysis_Ntu_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_PDAnalysis_Ntu_src,src/PDAnalysis/Ntu/src,LIBRARY))
PDAnalysisNtu := self/PDAnalysis/Ntu
PDAnalysis/Ntu := PDAnalysisNtu
PDAnalysisNtu_files := $(patsubst src/PDAnalysis/Ntu/src/%,%,$(wildcard $(foreach dir,src/PDAnalysis/Ntu/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PDAnalysisNtu_BuildFile    := $(WORKINGDIR)/cache/bf/src/PDAnalysis/Ntu/BuildFile
PDAnalysisNtu_LOC_USE := self  NtuAnalysis/Common
PDAnalysisNtu_EX_LIB   := PDAnalysisNtu
PDAnalysisNtu_EX_USE   := $(foreach d,$(PDAnalysisNtu_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
PDAnalysisNtu_PACKAGE := self/src/PDAnalysis/Ntu/src
ALL_PRODS += PDAnalysisNtu
PDAnalysisNtu_CLASS := LIBRARY
PDAnalysis/Ntu_forbigobj+=PDAnalysisNtu
PDAnalysisNtu_INIT_FUNC        += $$(eval $$(call Library,PDAnalysisNtu,src/PDAnalysis/Ntu/src,src_PDAnalysis_Ntu_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
ifeq ($(strip $(NtuTool/EDM)),)
ALL_COMMONRULES += src_NtuTool_EDM_src
src_NtuTool_EDM_src_parent := NtuTool/EDM
src_NtuTool_EDM_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_NtuTool_EDM_src,src/NtuTool/EDM/src,LIBRARY))
NtuToolEDM := self/NtuTool/EDM
NtuTool/EDM := NtuToolEDM
NtuToolEDM_files := $(patsubst src/NtuTool/EDM/src/%,%,$(wildcard $(foreach dir,src/NtuTool/EDM/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
NtuToolEDM_BuildFile    := $(WORKINGDIR)/cache/bf/src/NtuTool/EDM/BuildFile
NtuToolEDM_LOC_FLAGS_CXXFLAGS   := -Wno-delete-non-virtual-dtor
NtuToolEDM_LOC_USE := self  FWCore/Framework NtuTool/Common
NtuToolEDM_EX_LIB   := NtuToolEDM
NtuToolEDM_EX_USE   := $(foreach d,$(NtuToolEDM_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
NtuToolEDM_PACKAGE := self/src/NtuTool/EDM/src
ALL_PRODS += NtuToolEDM
NtuToolEDM_CLASS := LIBRARY
NtuTool/EDM_forbigobj+=NtuToolEDM
NtuToolEDM_INIT_FUNC        += $$(eval $$(call Library,NtuToolEDM,src/NtuTool/EDM/src,src_NtuTool_EDM_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
ifeq ($(strip $(NtuAnalysis/Write)),)
ALL_COMMONRULES += src_NtuAnalysis_Write_src
src_NtuAnalysis_Write_src_parent := NtuAnalysis/Write
src_NtuAnalysis_Write_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_NtuAnalysis_Write_src,src/NtuAnalysis/Write/src,LIBRARY))
NtuAnalysisWrite := self/NtuAnalysis/Write
NtuAnalysis/Write := NtuAnalysisWrite
NtuAnalysisWrite_files := $(patsubst src/NtuAnalysis/Write/src/%,%,$(wildcard $(foreach dir,src/NtuAnalysis/Write/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
NtuAnalysisWrite_BuildFile    := $(WORKINGDIR)/cache/bf/src/NtuAnalysis/Write/BuildFile
NtuAnalysisWrite_LOC_FLAGS_CXXFLAGS   := -Wno-delete-non-virtual-dtor
NtuAnalysisWrite_LOC_USE := self  root FWCore/Framework FWCore/ParameterSet NtuAnalysis/Common NtuTool/Common NtuTool/EDM
NtuAnalysisWrite_EX_LIB   := NtuAnalysisWrite
NtuAnalysisWrite_EX_USE   := $(foreach d,$(NtuAnalysisWrite_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
NtuAnalysisWrite_PACKAGE := self/src/NtuAnalysis/Write/src
ALL_PRODS += NtuAnalysisWrite
NtuAnalysisWrite_CLASS := LIBRARY
NtuAnalysis/Write_forbigobj+=NtuAnalysisWrite
NtuAnalysisWrite_INIT_FUNC        += $$(eval $$(call Library,NtuAnalysisWrite,src/NtuAnalysis/Write/src,src_NtuAnalysis_Write_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
ifeq ($(strip $(NtuTool/Common)),)
ALL_COMMONRULES += src_NtuTool_Common_src
src_NtuTool_Common_src_parent := NtuTool/Common
src_NtuTool_Common_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_NtuTool_Common_src,src/NtuTool/Common/src,LIBRARY))
NtuToolCommon := self/NtuTool/Common
NtuTool/Common := NtuToolCommon
NtuToolCommon_files := $(patsubst src/NtuTool/Common/src/%,%,$(wildcard $(foreach dir,src/NtuTool/Common/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
NtuToolCommon_BuildFile    := $(WORKINGDIR)/cache/bf/src/NtuTool/Common/BuildFile
NtuToolCommon_LOC_LIB   := Rint
NtuToolCommon_LOC_USE := self  root
NtuToolCommon_EX_LIB   := NtuToolCommon
NtuToolCommon_EX_USE   := $(foreach d,$(NtuToolCommon_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
NtuToolCommon_PACKAGE := self/src/NtuTool/Common/src
ALL_PRODS += NtuToolCommon
NtuToolCommon_CLASS := LIBRARY
NtuTool/Common_forbigobj+=NtuToolCommon
NtuToolCommon_INIT_FUNC        += $$(eval $$(call Library,NtuToolCommon,src/NtuTool/Common/src,src_NtuTool_Common_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
ifeq ($(strip $(PDAnalysisEDMPlugins)),)
PDAnalysisEDMPlugins := self/src/PDAnalysis/EDM/plugins
PLUGINS:=yes
PDAnalysisEDMPlugins_files := $(patsubst src/PDAnalysis/EDM/plugins/%,%,$(foreach file,*.cc,$(eval xfile:=$(wildcard src/PDAnalysis/EDM/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PDAnalysis/EDM/plugins/$(file). Please fix src/PDAnalysis/EDM/plugins/BuildFile.))))
PDAnalysisEDMPlugins_BuildFile    := $(WORKINGDIR)/cache/bf/src/PDAnalysis/EDM/plugins/BuildFile
PDAnalysisEDMPlugins_LOC_FLAGS_CXXFLAGS   := -Wno-delete-non-virtual-dtor
PDAnalysisEDMPlugins_LOC_USE := self  FWCore/Framework NtuAnalysis/Write PDAnalysis/EDM DataFormats/Candidate DataFormats/HepMCCandidate DataFormats/Math CommonTools/UtilAlgos CommonTools/CandUtils TrackingTools/IPTools TrackingTools/TransientTrack
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
ifeq ($(strip $(NtuAnalysis/Common)),)
ALL_COMMONRULES += src_NtuAnalysis_Common_src
src_NtuAnalysis_Common_src_parent := NtuAnalysis/Common
src_NtuAnalysis_Common_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_NtuAnalysis_Common_src,src/NtuAnalysis/Common/src,LIBRARY))
NtuAnalysisCommon := self/NtuAnalysis/Common
NtuAnalysis/Common := NtuAnalysisCommon
NtuAnalysisCommon_files := $(patsubst src/NtuAnalysis/Common/src/%,%,$(wildcard $(foreach dir,src/NtuAnalysis/Common/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
NtuAnalysisCommon_BuildFile    := $(WORKINGDIR)/cache/bf/src/NtuAnalysis/Common/BuildFile
NtuAnalysisCommon_LOC_FLAGS_CXXFLAGS   := -Wno-delete-non-virtual-dtor
NtuAnalysisCommon_LOC_USE := self  root NtuTool/Common
NtuAnalysisCommon_EX_LIB   := NtuAnalysisCommon
NtuAnalysisCommon_EX_USE   := $(foreach d,$(NtuAnalysisCommon_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
NtuAnalysisCommon_PACKAGE := self/src/NtuAnalysis/Common/src
ALL_PRODS += NtuAnalysisCommon
NtuAnalysisCommon_CLASS := LIBRARY
NtuAnalysis/Common_forbigobj+=NtuAnalysisCommon
NtuAnalysisCommon_INIT_FUNC        += $$(eval $$(call Library,NtuAnalysisCommon,src/NtuAnalysis/Common/src,src_NtuAnalysis_Common_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
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
ifeq ($(strip $(NtuTool/Read)),)
ALL_COMMONRULES += src_NtuTool_Read_src
src_NtuTool_Read_src_parent := NtuTool/Read
src_NtuTool_Read_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_NtuTool_Read_src,src/NtuTool/Read/src,LIBRARY))
NtuToolRead := self/NtuTool/Read
NtuTool/Read := NtuToolRead
NtuToolRead_files := $(patsubst src/NtuTool/Read/src/%,%,$(wildcard $(foreach dir,src/NtuTool/Read/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
NtuToolRead_BuildFile    := $(WORKINGDIR)/cache/bf/src/NtuTool/Read/BuildFile
NtuToolRead_LOC_USE := self  NtuTool/Common root
NtuToolRead_EX_LIB   := NtuToolRead
NtuToolRead_EX_USE   := $(foreach d,$(NtuToolRead_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
NtuToolRead_PACKAGE := self/src/NtuTool/Read/src
ALL_PRODS += NtuToolRead
NtuToolRead_CLASS := LIBRARY
NtuTool/Read_forbigobj+=NtuToolRead
NtuToolRead_INIT_FUNC        += $$(eval $$(call Library,NtuToolRead,src/NtuTool/Read/src,src_NtuTool_Read_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
endif
