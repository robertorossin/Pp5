#ifndef PDEDMToNtuple_h
#define PDEDMToNtuple_h

#include "NtuAnalysis/Write/interface/NtuEDMAnalyzer.h"
#include "NtuAnalysis/Write/interface/NtuEDConsumer.h"
#include "PDAnalysis/Ntu/bin/PDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <string>
#include <vector>
class TFile;

namespace pat {
  class Muon;
  class Jet;
}

class PDEDMToNtuple: public PDAnalyzer,
                      public NtuEDMAnalyzer {

 public:

  template<class T>
  PDEDMToNtuple( const edm::ParameterSet& ps, NtuEDConsumer<T>* c  ):
   NtuEDMAnalyzer( ps ) {
    // interface to allow uniform access to data in different CMSSW versions
    ObjectConsumer<T>& oc = getConsumer( c );
    oc.consume< std::vector<pat::Muon> >( gt_muons,
                                        labelMuons );
    oc.consume< std::vector<pat::Jet > >( gt_jets ,
                                        labelJets  );
  }
  virtual ~PDEDMToNtuple();

  virtual void beginJob();
  virtual void beginRun();
  virtual void read( const edm::EventBase& ev );
  virtual void endRun();
  virtual void endJob();

 private:

  template<class PATObject> class CompareByPt {
   public:
    bool operator()( const PATObject* l, const PATObject* r ) {
      return l->pt() > r->pt();
    }
  };

  std::string labelMuons;
  std::string labelJets;

  edm::Handle< std::vector<pat::Muon> >    muons;
  edm::Handle< std::vector<pat::Jet > >    jets;

  // interfaces to allow uniform access to data in different CMSSW versions
  NtuEDToken < std::vector<pat::Muon> > gt_muons;
  NtuEDToken < std::vector<pat::Jet > > gt_jets;

  void build( const edm::ParameterSet& ps );

  void fillMuons();
  void fillJets();

};

#endif
