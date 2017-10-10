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
