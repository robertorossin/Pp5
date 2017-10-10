ALL_COMMONRULES += src_NtuTool_Read_test
src_NtuTool_Read_test_parent := NtuTool/Read
src_NtuTool_Read_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_NtuTool_Read_test,src/NtuTool/Read/test,TEST))
