#ifndef PDEDMToNtuple_h
#define PDEDMToNtuple_h

#include "NtuAnalysis/Write/interface/NtuEDMAnalyzer.h"
#include "PDAnalysis/Ntu/bin/PDAnalyzer.h"
#include "PDAnalysis/Ntu/interface/PDEnumString.h"
#include "NtuAnalysis/Write/interface/NtuEDConsumer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/Measurement1D.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "DataFormats/BTauReco/interface/SecondaryVertexTagInfo.h"

#include "DataFormats/Common/interface/TriggerResults.h"

#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "BPHAnalysis/RecoDecay/interface/BPHTrackReference.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"

#include "BPHAnalysis/RecoDecay/interface/BPHTrackReference.h"
#include "PDAnalysis/EDM/interface/PDVertexWrapper.h"

#include <string>
#include <vector>
#include <set>
#include <iostream>

class BPHRecoCandidate;
class VertexDistanceXY;

class TFile;

namespace edm {
  class LumiReWeighting;
}

class HLTConfigProvider;
class PileupSummaryInfo;

class PDEDMToNtuple: public PDAnalyzer,
                      public NtuEDMAnalyzer {

 public:

  template<class T>
  PDEDMToNtuple( const edm::ParameterSet& ps, NtuEDConsumer<T>* c ):
   NtuEDMAnalyzer( ps ) {
    build( ps );
    ObjectConsumer<T>& oc = getConsumer( c );
    oc.consume< edm::TriggerResults                  >( gt_trigResults  ,
                                                      labelTrigResults   );
    oc.consume< pat::TriggerEvent                    >( gt_trigEvent    ,
                                                      labelTrigEvent     );
    oc.consume< reco::BeamSpot                       >( gt_beamSpot     ,
                                                      labelBeamSpot      );
    oc.consume< std::vector<pat::MET               > >( gt_mets         ,
                                                      labelMets          );
    oc.consume< std::vector<pat::Muon              > >( gt_muons        ,
                                                      labelMuons         );
    oc.consume< std::vector<pat::Electron          > >( gt_electrons    ,
                                                      labelElectrons     );
    oc.consume< std::vector<pat::Tau               > >( gt_taus         ,
                                                      labelTaus          );
    oc.consume< std::vector<pat::Jet               > >( gt_jets         ,
                                                      labelJets          );
    oc.consume< std::vector<reco::PFCandidate      > >( gt_pfCandidates ,
                                                      labelPFCandidates  );
    oc.consume< std::vector<pCandidate             > >( gt_pcCandidates ,
                                                      labelPCCandidates  );
    oc.consume< std::vector<pat::GenericParticle   > >( gt_gpCandidates ,
                                                      labelGPCandidates  );
    oc.consume< std::vector<pat::CompositeCandidate> >( gt_mmCandidates ,
                                                      labelMMCandidates  );
    oc.consume< std::vector<reco::Track            > >( gt_generalTracks,
                                                      labelGeneralTracks );
    oc.consume< std::vector<reco::Vertex           > >( gt_pVertices    ,
                                                      labelPVertices     );
    oc.consume< std::vector<svtInfo                > >( gt_sVertices    ,
                                                      labelSVertices     );
    oc.consume< std::vector<PileupSummaryInfo      > >( gt_PUInfo       ,
                                                      labelPUInfo        );
    oc.consume< std::vector<reco::GenParticle      > >( gt_genParticles ,
                                                      labelGen           );
    oc.consume< std::vector<reco::GenJet           > >( gt_genJets      ,
                                                      labelGPJ           );

  }

  virtual ~PDEDMToNtuple();

  virtual void beginJob();
  virtual void beginRun();
  virtual void read( const edm::EventBase& ev );
  virtual void endRun();
  virtual void endJob();

 private:

  template<class PATObject> class compareByPt {
   public:
    bool operator()( const PATObject* l, const PATObject* r ) {
      return l->pt() > r->pt();
    }
  };

  bool verbose;
  bool evStamp;

  std::string labelTrigResults;
  std::string labelTrigEvent;
  std::string labelBeamSpot;
  std::string labelMets;
  std::string labelMuons;
  std::string labelElectrons;
  std::string labelTaus;
  std::string labelJets;
  std::string labelPFCandidates;
  std::string labelPCCandidates;
  std::string labelGPCandidates;
  std::string labelMMCandidates;
  std::string labelGeneralTracks;
  std::string labelPVertices;
  std::string labelSVertices;
  std::string labelSVTagInfo;
  std::string labelPUInfo;
  std::string labelGen;
  std::string labelGPJ;

  std::string labelCSV;
  std::string labelTCHE;

  bool selectAssociatedPF;
  bool selectAssociatedTk;
  bool recoverMuonTracks;
  bool recoverCandTracks;
  bool writeAllPrimaryVertices;

  bool read_hlts;
  bool read_hlto;
  bool read_bspot;
  bool read_met;
  bool read_muons;
  bool read_electrons;
  bool read_taus;
  bool read_jets;
  bool read_pflow;
  bool read_mm;
  bool read_gentrk;
  bool read_tracks;
  bool read_pvts;
  bool read_svts;
  bool read_svtj;
  bool reco_svts;
  bool read_puwgt;
  bool read_gen;
  bool read_gpj;

  bool readPF;
  bool readPC;
  bool readGP;

  bool fill_svts;
  bool fill_svtt;

  typedef BPHTrackReference::candidate pCandidate;

  typedef PDVertexWrapBase::svtInfo   svtInfo;
  typedef PDVertexWrapBase::sVtx      sVtx;
  typedef PDVertexWrapBase::svtTkList svtTkList;

  typedef PDVertexWrapBase::VtxComponent VtxComponent;

  struct VtxInfo {
    int jetId;
    PDVertexContainer vtx;
    const GlobalVector* dir;
    Measurement1D  d2d;
    Measurement1D  d3d;
    std::vector<VtxComponent> compList;
  };

  std::map< const pat::Jet*,std::vector<VtxInfo> > svtMap;

  edm::Handle< edm::TriggerResults                  > trigResults;
  NtuEDToken < edm::TriggerResults                  > gt_trigResults;
  edm::Handle< pat::TriggerEvent                    > trigEvent;
  NtuEDToken < pat::TriggerEvent                    > gt_trigEvent;
  edm::Handle< reco::BeamSpot                       > beamSpot;
  NtuEDToken < reco::BeamSpot                       > gt_beamSpot;
  edm::Handle< std::vector<pat::MET               > > mets;
  NtuEDToken < std::vector<pat::MET               > > gt_mets;
  edm::Handle< std::vector<pat::Muon              > > muons;
  NtuEDToken < std::vector<pat::Muon              > > gt_muons;
  edm::Handle< std::vector<pat::Electron          > > electrons;
  NtuEDToken < std::vector<pat::Electron          > > gt_electrons;
  edm::Handle< std::vector<pat::Tau               > > taus;
  NtuEDToken < std::vector<pat::Tau               > > gt_taus;
  edm::Handle< std::vector<pat::Jet               > > jets;
  NtuEDToken < std::vector<pat::Jet               > > gt_jets;
  edm::Handle< std::vector<reco::PFCandidate      > > pfCandidates;
  NtuEDToken < std::vector<reco::PFCandidate      > > gt_pfCandidates;
  edm::Handle< std::vector<pCandidate             > > pcCandidates;
  NtuEDToken < std::vector<pCandidate             > > gt_pcCandidates;
  edm::Handle< std::vector<pat::GenericParticle   > > gpCandidates;
  NtuEDToken < std::vector<pat::GenericParticle   > > gt_gpCandidates;
  edm::Handle< std::vector<pat::CompositeCandidate> > mmCandidates;
  NtuEDToken < std::vector<pat::CompositeCandidate> > gt_mmCandidates;
  edm::Handle< std::vector<reco::Track            > > generalTracks;
  NtuEDToken < std::vector<reco::Track            > > gt_generalTracks;
  edm::Handle< std::vector<reco::Vertex           > > pVertices;
  NtuEDToken < std::vector<reco::Vertex           > > gt_pVertices;
  edm::Handle< std::vector<svtInfo                > > sVertices;
  NtuEDToken < std::vector<svtInfo                > > gt_sVertices;
  edm::Handle< std::vector<PileupSummaryInfo      > > PUInfo;
  NtuEDToken < std::vector<PileupSummaryInfo      > > gt_PUInfo;
  edm::Handle< std::vector<reco::GenParticle      > > genParticles;
  NtuEDToken < std::vector<reco::GenParticle      > > gt_genParticles;
  edm::Handle< std::vector<reco::GenJet           > > genJets;
  NtuEDToken < std::vector<reco::GenJet           > > gt_genJets;

  const edm::TriggerNames* triggerNames;
  std::vector<std::string> savedTriggerPaths;
  std::vector<std::string> savedTriggerObjects;
  std::vector<std::string> savedJetInfo;
  HLTConfigProvider* hltConfigProvider;

  std::vector<double> puWgt_mc;
  std::vector<double> puWgt_data;
  edm::LumiReWeighting* LumiWeights;

  std::vector<bool> vRecoFlag;

  bool fixedTrigPathList;
  int lastTrigMapSize;

  float jetPtMin;
  float jetEtaMax;
  float trkDzMax;
  float trkPtMin;
  float trkEtaMax;

  float dRmatchHLT;
  float dPmatchHLT;

  std::     map<const pat ::Muon       *,int                   > muoMap;
  std::     map<const pat ::Electron   *,int                   > eleMap;
  std::     map<const pat ::Tau        *,int                   > tauMap;
  std::     map<const pat ::Jet        *,int                   > jetMap;
  std::     map<const reco::Candidate  *,int                   > pcjMap;
  std::     map<const reco::Candidate  *,int                   > pfcMap;
//  std::     map<const reco::Track      *,int                   > tkmMap;
//  std::     map<const reco::Track      *,int                   > tkeMap;
//  std::     map<const reco::Track      *,int                   > tkpMap;
  std::     map<const reco::Track      *,int                   > ptjMap;
  std::     map<const reco::Track      *,int                   > tkvMap;
  std::     map<const reco::Track      *,int                   > trkMap;
  std::     map<const reco::Candidate  *,int                   > genMap;
  std::     map<const reco::GenJet     *,int                   > gpjMap;
  std::     set<const reco::Track      *                       > tkrSet;
  std::     set<const reco::Track      *                       > allPTk;
  std::multimap<const pat ::Muon       *,const reco::Track    *> mtkMap;
  std::     map<const pat ::Electron   *,const reco::Track    *> etkMap;
  std::multimap<const reco::Candidate  *,const reco::Track    *> ptkMap;
  std::     map<const reco::Track      *,const pat ::Muon     *> tmuMap;
  std::     map<const reco::Track      *,const pat ::Electron *> telMap;
  std::     map<const reco::Track      *,const reco::Candidate*> tpfMap;
//  std::     map<const reco::Candidate  *,const reco::Vertex   *> mcvMap;
  std::multimap<const reco::Candidate  *,const pat ::Muon     *> cmuMap;
  std::     map<const reco::Candidate  *,const reco::Vertex   *> pcvMap;
  std::     map<const reco::Track      *,const reco::Vertex   *> tvpMap;
  std::multimap<const reco::Vertex     *,const reco::Track    *> vtkMap;
  std::  vector<const pat ::Muon       *                       > muonList;
  std::  vector<const reco::Candidate  *                       > muRCList;
  std::  vector<const reco::Candidate  *                       > candList;
//  std::  vector<PDEnumString::trackType                        > candType;
  std::     map<const BPHRecoCandidate *,int                   > rsvMap;
  std::  vector<const reco::Track      *                       > pTrack;
  std::  vector<const reco::Track      *                       > pTList;
  std::     map<const reco::Track      *,int                   > pTType;
  std::  vector<const reco::Track      *                       > mTrack;
  std::  vector<const reco::Track      *                       > mTList;
  std::     map<const reco::Track      *,int                   > mTType;
  std::  vector<const reco::Track      *                       > pfcTrkP;
  std::  vector<const reco::Vertex     *                       > vtxList;
  std::     map<const reco::Vertex     *,int                   > vtxMap;

  std::set<int> savedTrk;
  std::set<int> savedPFC;
  std::set<int> savedVtx;
  std::set<int> savedJet;

  typedef
  std::multimap<const reco::Candidate  *,const reco::Track    *>
     ::const_iterator ptk_iter;

  void build( const edm::ParameterSet& ps );

  bool dumpNtuple;
  void fillHLTStatus   ();
  void fillHLTObjects  ();
  void fillBeamSpot    ();
  void fillMet         ();
  void fillOniaMuons   ();
  void fillMuons       ();
  void fillElectrons   ();
  void fillTaus        ();
  void fillJets        ();
  void fillVtxTrkMap   ();
  void fillPFCandidates();
  void fillTracks      ();
  void fillPVertices   ();
  void fillSVertices   ();
  void fillSVertReco   ();
  void fillPUWeight    ();
  void fillGenParticles();
  void fillGenJets     ();
  void fillUserInfo( int obj, int index,
                     int info , number value );
  void fillSVTInfoMap();
  void fillSVTIJetMap();

  void fillSaved();
  void cleanTracks();
  void cleanPFCand();

  const reco::Vertex* nearestPV( const reco::Track* );

  static void vertexDir( const reco::Vertex& pvtx,
                         const reco::Vertex& svtx,
                         const pat::CompositeCandidate& cand,
                         GlobalVector & dir,
                         Measurement1D& d2d,
                         Measurement1D& d3d );

  int addSecondaryVertex( const PDVertexWrapBase& vtx,
                          double vMass,
                          const std::map<const reco::         Track*,
                                               reco::TransientTrack*>& ttm,
                          const std::map<const reco::         Track*,
                                               float                >& tmm,
//                          const std::map<const reco::         Track*,
//                                         const reco::Candidate     *>& rcm,
//                          const std::map<const reco::         Track*,
//                                         const reco::Candidate     *>& rom,
                          const  GlobalVector& dir,
                          const Measurement1D& d2d,
                          const Measurement1D& d3d,
                          const std::string& type, int jetId );
  int addTrackIP(   int trkIndex, const reco::Track & trk, float mass,
                    int vtxIndex, const PDVertexWrapBase& vtx );
  int addTrackVtxP( int tipIndex, const reco::TransientTrack* trk,
                                  const PDVertexWrapBase& vtx );

  void linkMTracks();
  void linkETracks();
  void linkPTracks();

  int nearestHLT( PDEnumString::trigObject type,
                  double pt, double eta, double phi );

  bool wildMatch( const std::string& name, std::string model );

  void setTrkType( const reco::Track* trk, int type,
                   std::vector<const reco::Track *   >& cTList,
                   std::map   <const reco::Track*,int>& cTType );
  int lastTrack( int i );


  template<class Container,class Token>
  bool fillPFList( Container& container, const Token& token,
                   PDEnumString::trackType type ) {
    token.get( currentEvBase, container );
    if ( !container.isValid() ) {
      switch ( type ) {
      case PDEnumString::pflink:
        std::cout << "invalid particle flow" << std::endl;
        break;
      case PDEnumString::packed:
        std::cout << "invalid packed candidates" << std::endl;
        break;
      case PDEnumString::gplink:
        std::cout << "invalid generic candidates" << std::endl;
        break;
      default:
        break;
      }
      return false;
    }
    int pos = 0;
    int iPF = candList.size();
    int lPF = iPF + container->size();
    candList.resize( lPF );
    while ( iPF < lPF ) candList[iPF++] = &container->at( pos++ );
/*
    candType.resize( lPF );
    while ( iPF < lPF ) {
      candList[iPF] = &container->at( pos++ );
      candType[iPF] = type;
      ++iPF;
    }
*/
    return true;
  }

};

#endif
