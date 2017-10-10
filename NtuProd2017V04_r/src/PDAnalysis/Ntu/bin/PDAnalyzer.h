#ifndef PDAnalyzer_H
#define PDAnalyzer_H

#include "TH1.h"
#include "PDAnalyzerUtil.h"
#include "PDAnalysis/Ntu/interface/PDGenHandler.h"
// to skim the N-tuple "uncomment" the following line
//#include "NtuTool/Common/interface/TreeFilter.h"

// additional features
//#include "DataSetFilter.h"                       // dataset filter
//class PDSecondNtupleWriter;                      // second ntuple

// to skim the N-tuple replace the the following line
// with the "commented" ones
class PDAnalyzer: public virtual PDAnalyzerUtil
,                 public virtual PDGenHandler
// additional features
//,                 public virtual DataSetFilter   // dataset filter
// to skim the N-tuple "uncomment" the following line
//,                 public virtual TreeFilter
 {

 public:

  PDAnalyzer();
  virtual ~PDAnalyzer();

  // function called before starting the analysis
  virtual void beginJob();

  // functions to book the histograms
  void book();

  // functions called for each event
  // function to reset class content before reading from file
  virtual void reset();
  // function to do event-by-event analysis,
  // return value "true" for accepted events
  virtual bool analyze( int entry, int event_file, int event_tot );

  // function called at the end of the analysis
  virtual void endJob();

  // functions called at the end of the event loop
// to plot some histogram immediately after the ntuple loop
// "uncomment" the following line
//  virtual void plot();   // plot the histograms on the screen
  virtual void save();   // save the histograms on a ROOT file

  bool verbose;

 protected:

  double ptCut;

// additional features: second ntuple
//  PDSecondNtupleWriter* tWriter;                 // second ntuple

 private:

  TH1D* hptmumax;
  TH1D* hptmu2nd;
  TH1D* hptmu;

  TH1F* hMass1;
  TH1F* hMass2;
  TH1F* hMass3;

  float dmMax;

  // dummy copy constructor and assignment
  PDAnalyzer           ( const PDAnalyzer& );
  PDAnalyzer& operator=( const PDAnalyzer& );

};


#endif

