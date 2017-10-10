ALL_COMMONRULES += src_NtuTool_Common_test
src_NtuTool_Common_test_parent := NtuTool/Common
src_NtuTool_Common_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_NtuTool_Common_test,src/NtuTool/Common/test,TEST))
