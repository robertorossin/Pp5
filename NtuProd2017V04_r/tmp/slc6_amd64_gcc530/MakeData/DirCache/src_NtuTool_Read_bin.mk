ALL_COMMONRULES += src_NtuTool_Read_bin
src_NtuTool_Read_bin_parent := NtuTool/Read
src_NtuTool_Read_bin_INIT_FUNC += $$(eval $$(call CommonProductRules,src_NtuTool_Read_bin,src/NtuTool/Read/bin,BINARY))
