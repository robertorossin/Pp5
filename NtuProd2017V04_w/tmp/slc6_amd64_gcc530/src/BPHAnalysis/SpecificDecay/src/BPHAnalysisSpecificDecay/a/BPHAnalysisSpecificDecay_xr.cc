// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME tmpdIslc6_amd64_gcc530dIsrcdIBPHAnalysisdISpecificDecaydIsrcdIBPHAnalysisSpecificDecaydIadIBPHAnalysisSpecificDecay_xr

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "src/BPHAnalysis/SpecificDecay/src/classes.h"

// Header files passed via #pragma extra_include

namespace {
  void TriggerDictionaryInitialization_BPHAnalysisSpecificDecay_xr_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/lustre/cmswork/rrossin/Pp5/NtuProd2017V04_w/src",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw/CMSSW_9_2_6/src",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/lcg/root/6.08.07/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/boost/1.63.0-mlhled2/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/pcre/8.37-oenich/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/bz2lib/1.0.6/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/clhep/2.3.4.2-mlhled2/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/gsl/2.2.1/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/hepmc/2.06.07-oenich/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/libuuid/2.22.2/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/python/2.7.11-mlhled2/include/python2.7",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/tbb/2017_20161004oss/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/vdt/v0.3.2-oenich2/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/xerces-c/3.1.3/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/xz/5.2.1-oenich/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/zlib-x86_64/1.2.11/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/md5/1.0.0/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/tinyxml/2.5.3-mlhled2/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/lcg/root/6.08.07/include",
"/lustre/cmswork/rrossin/Pp5/NtuProd2017V04_w/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "BPHAnalysisSpecificDecay_xr dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "BPHAnalysisSpecificDecay_xr dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif
#ifndef CMS_DICT_IMPL
  #define CMS_DICT_IMPL 1
#endif
#ifndef _REENTRANT
  #define _REENTRANT 1
#endif
#ifndef GNUSOURCE
  #define GNUSOURCE 1
#endif
#ifndef __STRICT_ANSI__
  #define __STRICT_ANSI__ 1
#endif
#ifndef GNU_GCC
  #define GNU_GCC 1
#endif
#ifndef _GNU_SOURCE
  #define _GNU_SOURCE 1
#endif
#ifndef CMSSW_GIT_HASH
  #define CMSSW_GIT_HASH "CMSSW_9_2_6"
#endif
#ifndef PROJECT_NAME
  #define PROJECT_NAME "CMSSW"
#endif
#ifndef PROJECT_VERSION
  #define PROJECT_VERSION "CMSSW_9_2_6"
#endif
#ifndef TBB_USE_GLIBCXX_VERSION
  #define TBB_USE_GLIBCXX_VERSION 50300
#endif
#ifndef BOOST_SPIRIT_THREADSAFE
  #define BOOST_SPIRIT_THREADSAFE 1
#endif
#ifndef PHOENIX_THREADSAFE
  #define PHOENIX_THREADSAFE 1
#endif
#ifndef CMSSW_REFLEX_DICT
  #define CMSSW_REFLEX_DICT 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H

// dummy file


#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("BPHAnalysisSpecificDecay_xr",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_BPHAnalysisSpecificDecay_xr_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_BPHAnalysisSpecificDecay_xr_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_BPHAnalysisSpecificDecay_xr() {
  TriggerDictionaryInitialization_BPHAnalysisSpecificDecay_xr_Impl();
}
