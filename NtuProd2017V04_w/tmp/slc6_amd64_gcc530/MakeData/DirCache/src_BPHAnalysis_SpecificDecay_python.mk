ifeq ($(strip $(PyBPHAnalysisSpecificDecay)),)
PyBPHAnalysisSpecificDecay := self/src/BPHAnalysis/SpecificDecay/python
src_BPHAnalysis_SpecificDecay_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/BPHAnalysis/SpecificDecay/python)
PyBPHAnalysisSpecificDecay_files := $(patsubst src/BPHAnalysis/SpecificDecay/python/%,%,$(wildcard $(foreach dir,src/BPHAnalysis/SpecificDecay/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyBPHAnalysisSpecificDecay_LOC_USE := self  
PyBPHAnalysisSpecificDecay_PACKAGE := self/src/BPHAnalysis/SpecificDecay/python
ALL_PRODS += PyBPHAnalysisSpecificDecay
PyBPHAnalysisSpecificDecay_INIT_FUNC        += $$(eval $$(call PythonProduct,PyBPHAnalysisSpecificDecay,src/BPHAnalysis/SpecificDecay/python,src_BPHAnalysis_SpecificDecay_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyBPHAnalysisSpecificDecay,src/BPHAnalysis/SpecificDecay/python))
endif
ALL_COMMONRULES += src_BPHAnalysis_SpecificDecay_python
src_BPHAnalysis_SpecificDecay_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_BPHAnalysis_SpecificDecay_python,src/BPHAnalysis/SpecificDecay/python,PYTHON))
