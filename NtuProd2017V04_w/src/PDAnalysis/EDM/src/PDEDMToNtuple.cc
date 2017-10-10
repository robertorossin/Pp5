#include "PDAnalysis/EDM/interface/PDEDMToNtuple.h"
#include "PDAnalysis/Ntu/interface/PDEnumString.h"
#include "PDAnalysis/EDM/interface/PDMuonWrapper.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHOniaToMuMuBuilder.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHKx0ToKPiBuilder.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHPhiToKKBuilder.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHBuToJPsiKBuilder.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHBdToJPsiKxBuilder.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHBsToJPsiPhiBuilder.h"
//#include "PDAnalysis/EDM/interface/PDJPsiBuilder.h"
//#include "PDAnalysis/EDM/interface/PDKx0Builder.h"
//#include "PDAnalysis/EDM/interface/PDPhiBuilder.h"
//#include "PDAnalysis/EDM/interface/PDBuToJPsiKBuilder.h"
//#include "PDAnalysis/EDM/interface/PDBdToJPsiKxBuilder.h"
//#include "PDAnalysis/EDM/interface/PDBsToJPsiPhiBuilder.h"
//#include "PDAnalysis/EDM/interface/PDDumpRecoCand.h"
#include "BPHAnalysis/RecoDecay/interface/BPHPlusMinusCandidate.h"
#include "BPHAnalysis/RecoDecay/interface/BPHTrackReference.h"
#include "TFile.h"
#include "TROOT.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"

#include "DataFormats/PatCandidates/interface/MET.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "DataFormats/PatCandidates/interface/Tau.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"

#include "DataFormats/BTauReco/interface/SecondaryVertexTagInfo.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/Measurement1D.h"

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
//#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "RecoVertex/VertexTools/interface/VertexDistanceXY.h"
#include "RecoVertex/VertexTools/interface/VertexDistance3D.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/Common/interface/RefToBase.h"
#include "DataFormats/Common/interface/Ref.h"

#include <iostream>
#include <sstream>
#include <map>
#include <math.h>

using edm::TriggerResults;
using pat::MET;
using pat::Muon;
using pat::Electron;
using pat::Tau;
using pat::Jet;
using reco::Candidate;
using reco::PFCandidate;
using reco::PFCandidatePtr;
using reco::PFCandidateRef;
using reco::MuonPFIsolation;
using reco::Track;
using reco::TrackRef;
using reco::TrackBaseRef;
using reco::TransientTrack;
using reco::HitPattern;
using reco::Vertex;
using reco::SecondaryVertexTagInfo;
using reco::GenParticle;
using reco::GenJet;

using namespace std;

template <class T>
void shiftVector( T* v, int i, int j ) { v->at( i ) = v->at( j ); }

void relink( map<int,int>& m, int& i ) { i = m[i]; }

void PDEDMToNtuple::build( const edm::ParameterSet& ps ) {

  cout << "new PDEDMToNtuple" << endl;

  setUserParameter( "use_hltlist",
       ps.exists( "write_hltlist" ) ? ps.getParameter<string>(
                  "write_hltlist" ) : "false" );

  setUserParameter( "labelTrigResults"   ,
                     labelTrigResults    = ps.getParameter<string>(
                    "labelTrigResults"   ) );
  setUserParameter( "use_hlts"      ,
                  ( read_hlts       = (
  getUserParameter( "labelTrigResults"   ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_hlts"      ) &&
                    read_hlts         )
  setUserParameter( "use_hlts"           , ps.getParameter<string>(
                  "write_hlts"      ) );

  setUserParameter( "labelTrigEvent"     ,
                     labelTrigEvent      = ps.getParameter<string>(
                    "labelTrigEvent"     ) );
  setUserParameter( "use_hlto"      ,
		  ( read_hlto       = (
  getUserParameter( "labelTrigEvent"     ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_hlto"      ) &&
                    read_hlto         )
  setUserParameter( "use_hlto"           , ps.getParameter<string>(
                  "write_hlto"      ) );

  setUserParameter( "labelBeamSpot"      ,
                     labelBeamSpot       = ps.getParameter<string>(
                    "labelBeamSpot"      ) );
  setUserParameter( "use_bspot"     ,
                  ( read_bspot      = (
  getUserParameter( "labelBeamSpot"      ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_bspot"     ) &&
                    read_bspot        )
  setUserParameter( "use_bspot"          , ps.getParameter<string>(
                  "write_bspot"     ) );

  setUserParameter( "labelMets"          ,
                     labelMets           = ps.getParameter<string>(
                    "labelMets"          ) );
  setUserParameter( "use_met"       ,
                  ( read_met        = (
  getUserParameter( "labelMets"          ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_met"       ) &&
                    read_met          )
  setUserParameter( "use_met"            , ps.getParameter<string>(
                  "write_met"       ) );

  setUserParameter( "labelMuons"         ,
                     labelMuons          = ps.getParameter<string>(
                    "labelMuons"         ) );
  setUserParameter( "use_muons"     ,
                  ( read_muons      = (
  getUserParameter( "labelMuons"         ) != "" ) ) ? "t" : "f" );

  setUserParameter( "labelElectrons"     ,
                     labelElectrons      = ps.getParameter<string>(
                    "labelElectrons"     ) );
  setUserParameter( "use_electrons" ,
                  ( read_electrons  = (
  getUserParameter( "labelElectrons"     ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_electrons" ) &&
                    read_electrons    )
  setUserParameter( "use_electrons"      , ps.getParameter<string>(
                  "write_electrons" ) );

  setUserParameter( "labelTaus"          ,
                     labelTaus           = ps.getParameter<string>(
                    "labelTaus"           ) );
  setUserParameter( "use_taus"      ,
                  ( read_taus       = (
  getUserParameter( "labelTaus"          ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_taus"      ) &&
                    read_taus         )
  setUserParameter( "use_taus"           , ps.getParameter<string>(
                  "write_taus"      ) );

  setUserParameter( "labelJets"          ,
                     labelJets           = ps.getParameter<string>(
                    "labelJets"          ) );
  setUserParameter( "use_jets"      ,
                  ( read_jets       = (
  getUserParameter( "labelJets"          ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_jets"      ) &&
                    read_jets         )
  setUserParameter( "use_jets"           , ps.getParameter<string>(
                  "write_jets"      ) );

  setUserParameter( "labelPFCandidates"  ,
                     labelPFCandidates   = (
         ps.exists( "labelPFCandidates" ) ?
                                           ps.getParameter<string>(
                    "labelPFCandidates"  ) : "" ) );
  setUserParameter( "readPF"     ,
                  (  readPF      = (
  getUserParameter( "labelPFCandidates"  ) != "" ) ) ? "t" : "f" );

  setUserParameter( "labelPCCandidates"  ,
                     labelPCCandidates   = (
         ps.exists( "labelPCCandidates" ) ?
                                           ps.getParameter<string>(
                    "labelPCCandidates"  ) : "" ) );
  setUserParameter( "readPC"     ,
                  (  readPC      = (
  getUserParameter( "labelPCCandidates"  ) != "" ) ) ? "t" : "f" );
  if ( readPC ) recoverCandTracks = true;

  setUserParameter( "labelGPCandidates"  ,
                     labelGPCandidates   = (
         ps.exists( "labelGPCandidates" ) ?
                                           ps.getParameter<string>(
                    "labelGPCandidates"  ) : "" ) );
  setUserParameter( "readGP"     ,
                  (  readGP      = (
  getUserParameter( "labelGPCandidates"  ) != "" ) ) ? "t" : "f" );
  if ( readGP ) recoverCandTracks = true;

  setUserParameter( "use_pflow" ,
                  ( read_pflow = readPF || readPC || readGP ) ? "t" : "f" );
  if ( ps.exists( "write_pflow"     ) &&
                    read_pflow        )
  setUserParameter( "use_pflow"          , ps.getParameter<string>(
                  "write_pflow"     ) );

  setUserParameter( "labelMMCandidates"  ,
                     labelMMCandidates   = (
         ps.exists( "labelMMCandidates" ) ?
                                           ps.getParameter<string>(
                    "labelMMCandidates"  ) : "" ) );
  read_mm        = ( labelMMCandidates != "" );
  if ( read_mm ) setUserParameter( "use_muons", "t" );
  if ( ps.exists( "write_muons"     ) &&
       ( read_muons || read_mm ) )
  setUserParameter( "use_muons"          , ps.getParameter<string>(
                  "write_muons"     ) );

  setUserParameter( "labelGeneralTracks" ,
                     labelGeneralTracks  = ps.getParameter<string>(
                    "labelGeneralTracks" ) );
  read_gentrk    =
  read_tracks    = ( labelGeneralTracks != "" );

  setUserParameter( "labelPVertices"     ,
                     labelPVertices      = ps.getParameter<string>(
                    "labelPVertices"     ) );
  setUserParameter( "use_pvts"      ,
                  ( read_pvts       = (
  getUserParameter( "labelPVertices"     ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_pvts"      ) &&
                    read_pvts         )
  setUserParameter( "use_pvts"           , ps.getParameter<string>(
                  "write_pvts"      ) );

  setUserParameter( "labelSVertices"     ,
                     labelSVertices      = ps.getParameter<string>(
                    "labelSVertices"     ) );
                    read_svts       = (
  getUserParameter( "labelSVertices"     ) != "" );
  if ( !read_jets ) read_svts = false;

  setUserParameter( "labelSVTagInfo"     ,
                     labelSVTagInfo      = ps.getParameter<string>(
                    "labelSVTagInfo"     ) );
                    read_svtj       = (
  getUserParameter( "labelSVTagInfo"     ) != "" );
  if ( !read_jets ) read_svtj = false;

  vRecoFlag.resize( PDEnumString::DUMMY_LAST_DECAY + 1, false );
  reco_svts = false;
  if ( ps.exists( "vertReco" ) ) {
    vector<string> vertReco = ps.getParameter< vector<string> >( "vertReco" );
    int nVert = vertReco.size();
    int vType;
    while ( nVert-- ) {
      vType = PDEnumString::findVertexType( vertReco[nVert] );
      if ( vType <= 0 ) continue;
      reco_svts = vRecoFlag.at( vType ) = true;
    }
  }

  fill_svtt =
  fill_svts = read_svts || read_svtj || reco_svts;
  if ( ps.exists(   "fill_svtt" ) ) {
  setUserParameter( "fill_svtt", ps.getParameter<string>(
                    "fill_svtt" ) );
  getUserParameter( "fill_svtt", fill_svtt );
  }


  setUserParameter( "use_svts"      ,
                    fill_svts );
  if ( ps.exists( "write_svts"      ) &&
                  ( fill_svts )       )
  setUserParameter( "use_svts"           , ps.getParameter<string>(
                  "write_svts"      ) );

  setUserParameter( "labelPUInfo"        ,
                     labelPUInfo         = ps.getParameter<string>(
                    "labelPUInfo"        ) );
  setUserParameter( "use_puwgt"     ,
                  ( read_puwgt      = (
  getUserParameter( "labelPUInfo"        ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_puwgt"     ) &&
                    read_puwgt        )
  setUserParameter( "use_puwgt"          , ps.getParameter<string>(
                  "write_puwgt"     ) );

  setUserParameter( "labelGen"           ,
                     labelGen            = ps.getParameter<string>(
                    "labelGen"           ) );
  setUserParameter( "use_gen"       ,
                  ( read_gen        = (
  getUserParameter( "labelGen"           ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_gen"       ) &&
                    read_gen          )
  setUserParameter( "use_gen"            , ps.getParameter<string>(
                  "write_gen"       ) );

  setUserParameter( "labelGPJ"           ,
                     labelGPJ            = ps.getParameter<string>(
                    "labelGPJ"           ) );
  setUserParameter( "use_gpj"       ,
                  ( read_gpj        = (
  getUserParameter( "labelGPJ"           ) != "" ) ) ? "t" : "f" );
  if ( ps.exists( "write_gpj"       ) &&
                    read_gpj          )
  setUserParameter( "use_gpj"            , ps.getParameter<string>(
                  "write_gpj"       ) );

  setUserParameter( "use_vsub", getUserParameter( "use_svts" ) );
  if ( ps.exists( "write_vsub"   ) &&
                    fill_svts      )
  setUserParameter( "use_vsub", ps.getParameter<string>(
                  "write_vsub" ) );
  getUserParameter( "use_vsub"     ,
                     use_vsub      );

  if ( fill_svtt ) {

  setUserParameter( "use_tkips", getUserParameter( "use_svts" ) );
  if ( ps.exists( "write_tkips"   ) &&
                    read_svts       )
  setUserParameter( "use_tkips", ps.getParameter<string>(
                  "write_tkips" ) );

  setUserParameter( "use_vtxps", getUserParameter( "use_svts" ) );
  if ( ps.exists( "write_vtxps" ) &&
                     use_tkips    )
  setUserParameter( "use_vtxps", ps.getParameter<string>(
                  "write_vtxps" ) );

  }
  else {

  setUserParameter( "use_tkips", false );
  setUserParameter( "use_vtxps", false );

  }

  labelCSV  = ps.getParameter<string>( "labelCSV"  );
  labelTCHE = ps.getParameter<string>( "labelTCHE" );

  char apv = 'f';
  if ( ps.exists( "writeAllPrimaryVertices" ) )
                  apv = *ps.getParameter<string>(
                  "writeAllPrimaryVertices" ).c_str();
  writeAllPrimaryVertices = ( apv != 'f' ) && ( apv != 'F' );

  char rmt = 'f';
  if ( ps.exists( "recoverMuonTracks" ) )
                  rmt = *ps.getParameter<string>(
                  "recoverMuonTracks" ).c_str();
  recoverMuonTracks = ( rmt != 'f' ) && ( rmt != 'F' );
  if ( recoverMuonTracks ) read_tracks = true;
  char rct = 'f';
  if ( ps.exists( "recoverCandTracks" ) )
                  rct = *ps.getParameter<string>(
                  "recoverCandTracks" ).c_str();
  recoverCandTracks = ( rct != 'f' ) && ( rct != 'F' );
  if ( recoverCandTracks ) read_tracks = true;
  setUserParameter( "use_tracks"         ,
                    read_tracks ? "t" : "f" );
  if ( ps.exists( "write_tracks"    ) &&
                    read_tracks       )
  setUserParameter( "use_tracks"        , ps.getParameter<string>(
                  "write_tracks"         ) );

  if ( read_puwgt ) {
    puWgt_mc   = ps.getParameter< vector<double> >( "puWgt_mc"   );
    puWgt_data = ps.getParameter< vector<double> >( "puWgt_data" );
  }

  if ( ps.exists( "savedTriggerPaths"   ) )
                   savedTriggerPaths    = ps.getParameter< vector<string> >(
                  "savedTriggerPaths"   );
  if ( ps.exists( "savedTriggerObjects" ) )
                   savedTriggerObjects  = ps.getParameter< vector<string> >(
                  "savedTriggerObjects" );
  if ( ps.exists( "savedJetInfo"        ) )
                   savedJetInfo         = ps.getParameter< vector<string> >(
                  "savedJetInfo"        );
  bool              read_info = savedJetInfo.size();
  setUserParameter( "use_info",
                    read_info ? "t" : "f" );
  if ( ps.exists( "write_info" ) &&
                    read_info )
  setUserParameter( "use_info",
       ps.exists( "write_info" ) ? ps.getParameter<string>(
                  "write_info" ) : "false" );

  char sPF = *ps.getParameter<string>( "selectAssociatedPF" ).c_str();
  char sTk = *ps.getParameter<string>( "selectAssociatedTk" ).c_str();
  selectAssociatedPF = ( sPF != 'f' ) && ( sPF != 'F' );
  selectAssociatedTk = ( sTk != 'f' ) && ( sTk != 'F' );

  char aNP = ( ps.exists( "acceptNewTrigPaths" ) ?
               *ps.getParameter<string>( "acceptNewTrigPaths" ).c_str() :
               'f' );
  fixedTrigPathList = ( aNP == 'f' ) || ( aNP == 'F' );
  lastTrigMapSize = 0;

  jetPtMin  = ps.getParameter<double>( "jetPtMin"  );
  jetEtaMax = ps.getParameter<double>( "jetEtaMax" );
  trkDzMax  = ps.getParameter<double>( "trkDzMax"  );
  trkPtMin  = ps.getParameter<double>( "trkPtMin"  );
  trkEtaMax = ps.getParameter<double>( "trkEtaMax" );
  dRmatchHLT = ps.getParameter<double>( "dRmatchHLT" );
  dPmatchHLT = ps.getParameter<double>( "dPmatchHLT" );

  if ( ps.exists( "eventList" ) )
  setUserParameter( "eventList", ps.getParameter<string>( "eventList" ) );

  if ( ps.exists( "verbose" ) )
  setUserParameter( "verbose",
                    ps.getUntrackedParameter<string>( "verbose" ) );
  if ( ps.exists( "evStamp" ) )
  setUserParameter( "evStamp",
                    ps.getUntrackedParameter<string>( "evStamp" ) );
  getUserParameter( "verbose", verbose );
  getUserParameter( "evStamp", evStamp );
  evStamp = evStamp || verbose;

  setupNtuple();

}


PDEDMToNtuple::~PDEDMToNtuple() {
}


void PDEDMToNtuple::beginJob() {

//  cout << "PDEDMToNtuple::beginJob()" << endl;

  PDAnalyzer::beginJob();
  NtuEDMAnalyzer::beginJob();
  hltConfigProvider = 0;

  if ( read_puwgt ) {
    int iWgt;
    int nWgt;
    vector<float> pw_mc  ( nWgt = puWgt_mc  .size() );
    for ( iWgt = 0; iWgt < nWgt; ++iWgt ) pw_mc  [iWgt] = puWgt_mc  [iWgt];
    vector<float> pw_data( nWgt = puWgt_data.size() );
    for ( iWgt = 0; iWgt < nWgt; ++iWgt ) pw_data[iWgt] = puWgt_data[iWgt];
    LumiWeights = new edm::LumiReWeighting( pw_mc, pw_data );
  }
  else {
    LumiWeights = 0;
  }

  return;

}


void PDEDMToNtuple::beginRun() {
  if ( currentEvSetup != 0 ) {
    try {
      bool changed;
      hltConfigProvider = new HLTConfigProvider;
      hltConfigProvider->init( *currentRun, *currentEvSetup, "HLT", changed );
      const std::string tableName = hltConfigProvider->tableName();
      std::vector<std::string> triggerNames =
            hltConfigProvider->triggerNames();
    }
    catch ( cms::Exception e ) {
      hltConfigProvider = 0;
    }
  }
  return;
}


void PDEDMToNtuple::read( const edm::EventBase& ev ) {

  if ( evStamp ) {
    cout << " +++++++++++++++++++++++++++ " << endl
         << " read ";
    dumpEvent( cout );
  }

  nHLTStatus  = 0;
  nHLTObjects = 0;
  nUserInfo   = 0;
  nMuons      = 0;
  nElectrons  = 0;
  nTaus       = 0;
  nJets       = 0;
  nPF         = 0;
  nTracks     = 0;
  nPVTotal    = 0;
  nPVertices  = 0;
  nSVertices  = 0;
  nTkIPs      = 0;
  nVtxPs      = 0;
  nGenP       = 0;
  nGenJets    = 0;

  useObjType  ->clear();
  useObjIndex ->clear();
  useInfoType ->clear();
  useInfoValue->clear();
  pcvMap.clear();
  vtkMap.clear();
  muonList.clear();
  if ( read_hlts      ) fillHLTStatus   ();
  if ( read_hlto      ) fillHLTObjects  ();
  if ( read_bspot     ) fillBeamSpot    ();
  if ( read_met       ) fillMet         ();
  if ( read_mm        ) fillOniaMuons   ();
  if ( read_muons     ||
       read_mm        ) fillMuons       ();
  if ( read_electrons ) fillElectrons   ();
  if ( read_taus      ) fillTaus        ();
  if ( read_jets      ) fillJets        ();
  if ( read_pvts      &&
       read_tracks    ) fillVtxTrkMap   ();
  if ( read_pflow     ) fillPFCandidates();
  if ( read_tracks    ) fillTracks      ();
  if ( read_pvts      ) fillPVertices   ();
  if ( fill_svts      ) fillSVertices   ();
  if ( reco_svts      ) fillSVertReco   ();
  if ( fill_svts ||
       reco_svts      ) convCartSphe( tvpPx, tvpPy , tvpPz,
                                      tvpPt, tvpEta, tvpPhi );
  if ( read_puwgt     ) fillPUWeight    ();
  if ( read_gen       ) fillGenParticles();
  if ( read_gpj       ) fillGenJets     ();

  if ( read_muons     && read_tracks ) linkMTracks();
  if ( read_electrons && read_tracks ) linkETracks();
  if ( read_pflow     && read_tracks ) linkPTracks();

//  fillSaved();
//  cleanTracks();

  return;

}


void PDEDMToNtuple::endRun() {
  return;
}


void PDEDMToNtuple::endJob() {
  PDAnalyzer::endJob();
  NtuEDMAnalyzer::endJob();
  return;
}


void PDEDMToNtuple::fillHLTStatus() {

  nHLTStatus = 0;
  hltPath   ->clear();
  hltVersion->clear();
  hltScale  ->clear();
  hltRun    ->clear();
  hltAccept ->clear();

  gt_trigResults.get( currentEvBase, trigResults );
  if ( !trigResults.isValid() ) {
    cout << "invalid trigResults" << endl;
    triggerNames = 0;
    return;
  }
  else {
    triggerNames = &( currentEvBase->triggerNames( *trigResults ) );
  }


  int iObj;
  int nObj = triggerNames->size();
  int iTrg;
  int nTrg = savedTriggerPaths.size();
  int iPath;
  int iVers;
  int lVers;
  int lSave;
  int iPres;
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    const string& hltPathName = triggerNames->triggerName( iObj );
    int index = triggerNames->triggerIndex( hltPathName );
    string base = PDEnumString::trigBase( hltPathName );
    iPath = -1;
    iVers = -1;
    iPres = -1;
    stringstream sstr;
    for ( iTrg = 0; iTrg < nTrg; ++iTrg ) {
      const string& name = savedTriggerPaths[iTrg];
      if ( !wildMatch( base, name ) ) continue;
      if ( ( iPath = PDEnumString::findTrigPath( base,
                                                 fixedTrigPathList ) ) < 0 )
          continue;
      lSave = base.length();
      lVers = hltPathName.length() - lSave;
      sstr.clear();
      sstr.str(  hltPathName.substr( lSave, lVers ) );
      sstr >> iVers;
/*
      if ( hltConfigProvider != 0 ) {
//        cout << "look prescale for " << hltPathName << endl;
        try {
          pair<int,int> pathPS = hltConfigProvider->prescaleValues(
                                 *currentEvent, *currentEvSetup, hltPathName );
          iPres = pathPS.first * pathPS.second;
//          cout << "factors: " << pathPS.first << " " << pathPS.second << endl;
        }
        catch ( cms::Exception e ) {
          cout << "prescale not found" << endl;
          iPres = -1;
        }
      }
*/
      ++nHLTStatus;
      hltPath   ->push_back( iPath );
      hltVersion->push_back( iVers );
      hltScale  ->push_back( iPres );
      hltRun    ->push_back( trigResults->wasrun( index ) );
      hltAccept ->push_back( trigResults->accept( index ) );
    }
  }

  nHLTPaths = 0;
  hltCode->clear();
  hltName->clear();
  const std::map<int,std::string>& tMap = PDEnumString::trigMap();
  int newSize = tMap.size();
  if ( newSize > lastTrigMapSize ) {
    nHLTPaths = lastTrigMapSize = newSize;
    hltCode->reserve( newSize );
    hltName->reserve( newSize );
    std::map<int,std::string>::const_iterator iter = tMap.begin();
    std::map<int,std::string>::const_iterator iend = tMap.end();
    while ( iter != iend ) {
      const std::map<int,std::string>::value_type& entry = *iter++;
      hltCode->push_back( entry.first  );
      hltName->push_back( entry.second );
    }
  }

  return;

}


void PDEDMToNtuple::fillHLTObjects() {

  gt_trigEvent.get( currentEvBase, trigEvent );
  bool vHLTo = trigEvent.isValid();

  hltObjType->clear();
  hltPt     ->clear();
  hltEta    ->clear();
  hltPhi    ->clear();
  hltPx     ->clear();
  hltPy     ->clear();
  hltPz     ->clear();
  hltE      ->clear();

  if ( !vHLTo ) {
    cout << "invalid trigEvent" << endl;
    return;
  }

  int iTrg;
  int nTrg = savedTriggerObjects.size();
  int triggerObjectType;
  nHLTObjects = 0;
  for ( iTrg = 0; iTrg < nTrg; ++iTrg ) {
    const string& name = savedTriggerObjects[iTrg];
    if      ( name == "hltMuon" ) triggerObjectType = trigger::TriggerMuon;
    else if ( name == "hltJet"  ) triggerObjectType = trigger::TriggerJet;
    else continue;
    const pat::TriggerObjectRefVector
          trigRefs( trigEvent->objects( triggerObjectType ) );
    pat::TriggerObjectRefVector::const_iterator iter = trigRefs.begin();
    pat::TriggerObjectRefVector::const_iterator iend = trigRefs.end();
    while ( iter != iend ) {
      const pat::TriggerObject& obj = **iter++;
      hltObjType->push_back( PDEnumString::findTrigObject( name ) );
      const Candidate::LorentzVector p4 = obj.p4();
      hltPt          ->push_back( p4.pt    () );
      hltEta         ->push_back( p4.eta   () );
      hltPhi         ->push_back( p4.phi   () );
      hltPx          ->push_back( p4.px    () );
      hltPy          ->push_back( p4.py    () );
      hltPz          ->push_back( p4.pz    () );
      hltE           ->push_back( p4.energy() );
      ++nHLTObjects;
    }
  }

  return;

}


void PDEDMToNtuple::fillBeamSpot() {

  bwX         = -999.999;
  bwY         = -999.999;
  bwXError    = -999.999;
  bwYError    = -999.999;
  bsX         = -999.999;
  bsY         = -999.999;
  bsZ         = -999.999;
  bsXError    = -999.999;
  bsYError    = -999.999;
  bsZError    = -999.999;
  bsdXdZ      = -999.999;
  bsdYdZ      = -999.999;
  bsdXdZError = -999.999;
  bsdYdZError = -999.999;
  gt_beamSpot.get( currentEvBase, beamSpot );
  if ( !beamSpot.isValid() ) {
    cout << "invalid beam spot" << endl;
    return;
  }

  bwX         = beamSpot->BeamWidthX();
  bwY         = beamSpot->BeamWidthY();
  bwXError    = beamSpot->BeamWidthXError();
  bwYError    = beamSpot->BeamWidthYError();
  bsX         = beamSpot->x0();
  bsY         = beamSpot->y0();
  bsZ         = beamSpot->z0();
  bsXError    = beamSpot->x0Error();
  bsYError    = beamSpot->y0Error();
  bsZError    = beamSpot->z0Error();
  bsdXdZ      = beamSpot->dxdz();
  bsdYdZ      = beamSpot->dydz();
  bsdXdZError = beamSpot->dxdzError();
  bsdYdZError = beamSpot->dydzError();

  return;

}


void PDEDMToNtuple::fillMet() {

  mEt = -999.999;
  mEx = -999.999;
  mEy = -999.999;
  gt_mets.get( currentEvBase, mets );
  if ( !mets.isValid() ) {
    cout << "invalid mets" << endl;
    return;
  }

  // store mEt info

  mEt    = mets->at( 0 ).pt();
  mEx    = mets->at( 0 ).px();
  mEy    = mets->at( 0 ).py();
  mEsign = mets->at( 0 ).mEtSig();

  return;

}


void PDEDMToNtuple::fillOniaMuons() {
  gt_mmCandidates.get( currentEvBase, mmCandidates );
  bool vMM = mmCandidates.isValid();
  if ( !vMM ) {
    cout << "invalid mmCandidates" << endl;
    return;
  }
  int n = mmCandidates->size();
  muonList.reserve( n * 2 );
  int i;
  for ( i = 0; i < n; ++i ) {
    const pat::CompositeCandidate& cc = mmCandidates->at( i );
    int j;
    int m = cc.numberOfDaughters();
    for ( j = 0; j < m; ++j ) {
      const reco::Candidate* dp = cc.daughter( j );
      const pat::Muon* mp = dynamic_cast<const pat::Muon*>( dp );
      if ( mp != 0 ) muonList.push_back( mp );
    }
  }
  return;
}


void PDEDMToNtuple::fillMuons() {

  bool vMuons = false;
  if ( read_muons ) {
    gt_muons.get( currentEvBase, muons );
    vMuons = muons.isValid();
  }

  int iMu = 0;
  int lMu = muonList.size();
  nMuons = lMu + ( vMuons ? muons->size() : 0 );
  muonList.resize( nMuons );
  muRCList.resize( nMuons );
  while ( lMu < nMuons ) muonList[lMu++] = &muons->at( iMu++ );

  // store muons info

  int iObj;
  int nObj = nMuons;
//  int nObj = nMuons = ( vMuons ? muons->size() : 0 );
  muoPt          ->resize( nObj );
  muoEta         ->resize( nObj );
  muoPhi         ->resize( nObj );
  muoPx          ->resize( nObj );
  muoPy          ->resize( nObj );
  muoPz          ->resize( nObj );
  muoE           ->resize( nObj );
  muoCharge      ->resize( nObj );
  muoTrk         ->resize( nObj );
  muoTrg         ->resize( nObj );
  muoChaIso      ->resize( nObj );
  muoNeuIso      ->resize( nObj );
  muoPhoIso      ->resize( nObj );
  muoSumCHpt     ->resize( nObj );
  muoSumCPpt     ->resize( nObj );
  muoSumNHet     ->resize( nObj );
  muoSumPHet     ->resize( nObj );
  muoSumPUpt     ->resize( nObj );
  muoNumMatches  ->resize( nObj );
  muoType        ->resize( nObj );
  muoDb          ->resize( nObj );
  muoChi2LP      ->resize( nObj );
  muoTrkKink     ->resize( nObj );
  muoSegmComp    ->resize( nObj );
  muoChi2LM          ->resize( nObj );
  muoTrkRelChi2      ->resize( nObj );
  muoGlbTrackTailProb->resize( nObj );
  muoGlbKinkFinderLOG->resize( nObj );
  muoGlbDeltaEtaPhi  ->resize( nObj );
  muoStaRelChi2      ->resize( nObj );
  muoTimeAtIpInOut   ->resize( nObj );
  muoTimeAtIpInOutErr->resize( nObj );

//  muoInnerChi2   ->clear();
  muoIValFrac    ->clear();
//  muoValPixHits  ->clear();
//  muoNTrkVHits   ->clear();
//  muoOuterChi2   ->clear();
//  muoGNchi2      ->clear();
//  muoVMuHits     ->clear();
//  muoQprod       ->clear();
//  muoLWH         ->clear();
  muoVMuonHitComb->clear();

//  muo_innerChi2   ->resize( nObj, -1 );
  muoIValFrac    ->resize( nObj, -1 );
//  muo_valPixHits  ->resize( nObj, -1 );
//  muo_NTrkVHits   ->resize( nObj, -1 );
//  muo_outerChi2   ->resize( nObj, -1 );
//  muo_gNchi2      ->resize( nObj, -1 );
//  muo_vMuHits     ->resize( nObj, -1 );
//  muo_Qprod       ->resize( nObj, -1 );
//  muo_LWH         ->resize( nObj, -1 );
  muoVMuonHitComb->resize( nObj, -1 );

  muoMap.clear();
  mtkMap.clear();
  tmuMap.clear();
//  mcvMap.clear();
  cmuMap.clear();
//  tkmMap.clear();
  mTType.clear();
  mTrack.clear();
  mTrack.reserve( 4 * nObj );
  if ( !vMuons ) {
    if ( !read_mm )
    cout << "invalid muons" << endl;
    if ( !nMuons ) return;
  }

  vector<const Muon*> muonPtr;
  muonPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    muonPtr[iObj] = muonList[iObj];
//    muonPtr[iObj] = &( muons->at( iObj ) );
  }

  compareByPt<Muon> muoComp;
  sort( muonPtr.begin(), muonPtr.end(), muoComp );

  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Muon* mptr = muonPtr[iObj];
    muRCList[iObj] = mptr;
    if ( muoMap.find( mptr ) != muoMap.end() ) continue;
    const Muon& muon = *mptr;

    int nms = muon.numberOfSourceCandidatePtrs();
//    vector<const Candidate*> cpv( nms );
//    cout << "Muon source: " << mptr << ' ' << nms;
    int ims;
//    for ( ims = 0; ims < nms; ++ims ) cpv[nms] = muon.sourceCandidatePtr( ims ).get();
    const Vertex* vptr = 0;
    for ( ims = 0; ims < nms; ++ims ) {
      const Candidate* rc = mptr->sourceCandidatePtr( ims ).get();
      if ( rc == 0 ) continue;
      cmuMap.insert( make_pair( rc, mptr ) );
      const Vertex* vtx = PDVertexWrapBase::vertexRef( rc );
      if ( vtx != 0 ) pcvMap[mptr] = vptr = vtx;
//      if ( vtx != 0 ) mcvMap[mptr] = vptr = vtx;
//      vrcMap.insert( make_pair( vtx, mptr ) );
    }
//    for ( ims = 0; ims < nms; ++ims ) cout << ' ' << muon.sourceCandidatePtr( ims ).get();
//    cout << endl;

    int type = 0;
    if ( muon.isPFMuon        () ) type |= PDEnumString::pf;
    if ( muon.isTrackerMuon   () ) type |= PDEnumString::inner;
    if ( muon.isGlobalMuon    () ) type |= PDEnumString::global;
    if ( muon.isStandAloneMuon() ) type |= PDEnumString::standalone;
    if ( PDMuonWrapper::  isGoodMuon( muon, muon::TMOneStationTight     ) )
                                   type |= PDEnumString::tmOneStation;
    if ( PDMuonWrapper::  isGoodMuon( muon, muon::GlobalMuonPromptTight ) )
                                   type |= PDEnumString::gmPrompt;
    if ( PDMuonWrapper:: isLooseMuon( muon ) ) type |= PDEnumString::loose;
    if ( PDMuonWrapper::isMediumMuon( muon ) ) type |= PDEnumString::medium;

    mTList.clear();
    mTList.reserve( 6 );
    const Track* gTrack = 0;//muon.globalTrack();
    const Track* iTrack = 0;//muon.innerTrack();
    const Track* oTrack = 0;//muon.outerTrack();
    const Track* tkp;
    if ( ( oTrack =
           tkp = BPHTrackReference::getMuonSA( muon ) ) != 0 )
         setTrkType( tkp, PDEnumString::muStandalone, mTList, mTType );
    if ( ( gTrack =
           tkp = BPHTrackReference::getMuonGT( muon ) ) != 0 )
         setTrkType( tkp, PDEnumString::muGlobal    , mTList, mTType );
    if ( ( iTrack =
           tkp = BPHTrackReference::getMuonIT( muon ) ) != 0 )
         setTrkType( tkp, PDEnumString::muInner     , mTList, mTType );
    if ( ( tkp = BPHTrackReference::getMuonPF( muon ) ) != 0 )
         setTrkType( tkp, PDEnumString::muPF        , mTList, mTType );
    if ( ( tkp = BPHTrackReference::getFromRC( muon ) ) != 0 )
         setTrkType( tkp, PDEnumString::rclink      , mTList, mTType );
    if ( ( tkp = BPHTrackReference::getFromPF( muon ) ) != 0 )
         setTrkType( tkp, PDEnumString::pflink      , mTList, mTType );
    if ( ( tkp = PDMuonWrapper::bestMuonTrack( muon ) ) != 0 )
         setTrkType( tkp, PDEnumString::muBest      , mTList, mTType );
    int iTrk;
    int nTrk = mTList.size();
    for ( iTrk = 0; iTrk < nTrk; ++iTrk ) {
      tkp = mTList[iTrk];
      if ( tmuMap.find( tkp ) != tmuMap.end() ) continue;
//      if ( tkmMap.find( tkp ) != tkmMap.end() ) continue;
      mTrack.push_back( tkp );
//      cout << "muon " << mptr << " track added: " << tkp << ' ' << mTType[tkp] << endl;
      tmuMap[tkp] = mptr;
//      tkmMap[tkp] = iObj;
      mtkMap.insert( make_pair( mptr, tkp ) );
      if ( vptr != 0 )
      vtkMap.insert( make_pair( vptr, tkp ) );
    }

    muoMap[mptr] = iObj;
    const Candidate::LorentzVector p4 = muon.p4();

    muoPt          ->at( iObj ) = p4.pt    ();
    muoEta         ->at( iObj ) = p4.eta   ();
    muoPhi         ->at( iObj ) = p4.phi   ();
    muoPx          ->at( iObj ) = p4.px    ();
    muoPy          ->at( iObj ) = p4.py    ();
    muoPz          ->at( iObj ) = p4.pz    ();
    muoE           ->at( iObj ) = p4.energy();
    muoCharge      ->at( iObj ) = muon.charge();
    muoTrk         ->at( iObj ) = -1;
    muoTrg         ->at( iObj ) = nearestHLT( PDEnumString::hltMuon,
                                              p4.pt(), p4.eta(), p4.phi() );

    muoChaIso      ->at( iObj ) = muon.chargedHadronIso();
    muoNeuIso      ->at( iObj ) = muon.neutralHadronIso();
    muoPhoIso      ->at( iObj ) = muon.photonIso();
    const MuonPFIsolation& pfIsolationR04 = muon.pfIsolationR04();
    muoSumCHpt     ->at( iObj ) = pfIsolationR04.sumChargedHadronPt;
    muoSumCPpt     ->at( iObj ) = pfIsolationR04.sumChargedParticlePt;
    muoSumNHet     ->at( iObj ) = pfIsolationR04.sumNeutralHadronEt;
    muoSumPHet     ->at( iObj ) = pfIsolationR04.sumPhotonEt;
    muoSumPUpt     ->at( iObj ) = pfIsolationR04.sumPUPt;

    muoNumMatches  ->at( iObj ) = muon.numberOfMatchedStations();
    muoType        ->at( iObj ) = type;
    muoDb          ->at( iObj ) = muon.dB();
    const reco::MuonQuality& muQuality = muon.combinedQuality();
    muoChi2LP      ->at( iObj ) = muQuality.chi2LocalPosition;
    muoTrkKink     ->at( iObj ) = muQuality.trkKink;
    muoSegmComp    ->at( iObj ) = muon::segmentCompatibility( muon );

    muoChi2LM          ->at( iObj ) = muQuality.chi2LocalMomentum;
    muoTrkRelChi2      ->at( iObj ) = muQuality.trkRelChi2;
    muoGlbTrackTailProb->at( iObj ) = muQuality.glbTrackProbability;
    muoGlbKinkFinderLOG->at( iObj ) = log( 2 + muQuality.glbKink );
//    muoGlbKinkFinderLOG->at( iObj ) = TMath::Log( 2 + muQuality.glbKink );
    muoGlbDeltaEtaPhi  ->at( iObj ) = muQuality.globalDeltaEtaPhi;
    muoStaRelChi2      ->at( iObj ) = muQuality.staRelChi2;
    muoTimeAtIpInOut   ->at( iObj ) = muon.time().timeAtIpInOut;
    muoTimeAtIpInOutErr->at( iObj ) = muon.time().timeAtIpInOutErr;

//    reco::TrackRef gTrack = muon.globalTrack();
//    reco::TrackRef iTrack = muon.innerTrack();
//    reco::TrackRef oTrack = muon.outerTrack();

    if ( iTrack != 0 ) {
//    if ( muon.innerTrack().isNonnull() ) {
//      muoInnerChi2 ->at( iObj ) = iTrack->normalizedChi2();
      muoIValFrac  ->at( iObj ) = iTrack->validFraction();      
//      muoValPixHits->at( iObj ) = static_cast<number>( iTrack->hitPattern()
//                                 .numberOfValidPixelHits() );
//      muoNTrkVHits ->at( iObj ) = static_cast<number>( iTrack->hitPattern()
//                                 .numberOfValidTrackerHits() );
//      muoLWH       ->at( iObj ) = static_cast<number>( iTrack->hitPattern()
//                                 .trackerLayersWithMeasurement() );
    }

//    if ( oTrack != 0 ) {
////    if ( muon.outerTrack().isNonnull() ) {
//      muoOuterChi2->at( iObj ) = oTrack->normalizedChi2();
//    }

    if ( gTrack != 0 ) {
//    if ( gTrack().isNonnull() ) {
//      muoGNchi2      ->at( iObj ) = gTrack->normalizedChi2();
//      muoVMuHits     ->at( iObj ) = static_cast<float>( gTrack->hitPattern().numberOfValidMuonHits() );

      int vDT;
      int vCSCmax;
      int vRPC;

      vDT     = gTrack->hitPattern().numberOfValidMuonDTHits();
      vCSCmax = gTrack->hitPattern().numberOfValidMuonCSCHits();
      if ( vCSCmax > 6 ) vCSCmax = 6;
      vRPC    = gTrack->hitPattern().numberOfValidMuonRPCHits();

      muoVMuonHitComb->at( iObj ) = (vDT/2 + vCSCmax + vRPC);

    }

//    if ( ( iTrack != 0 ) && ( oTrack != 0 ) ) {
////    if ( ( muon.innerTrack().isNonnull() ) && (
////           muon.outerTrack().isNonnull() ) ) {
//      muoQprod->at( iObj ) = static_cast<float>( iTrack->charge() ) *
//                             static_cast<float>( oTrack->charge() );
//    }

  }

  return;

}


void PDEDMToNtuple::fillElectrons() {

  gt_electrons.get( currentEvBase, electrons );
  bool vElectrons = electrons.isValid();

  // store electrons info

  int iObj;
  int nObj = nElectrons = ( vElectrons ? electrons->size() : 0 );
  elePt     ->resize( nObj );
  eleEta    ->resize( nObj );
  elePhi    ->resize( nObj );
  elePx     ->resize( nObj );
  elePy     ->resize( nObj );
  elePz     ->resize( nObj );
  eleE      ->resize( nObj );
  eleCharge ->resize( nObj );
  eleTrk    ->resize( nObj );
  eleTrg    ->resize( nObj );
  eleChaIso ->resize( nObj );
  eleNeuIso ->resize( nObj );
  elePhoIso ->resize( nObj );
  elePCHIso ->resize( nObj );
  eleAbsEta ->resize( nObj );
  eleAEff   ->resize( nObj );
  eleID     ->resize( nObj );
  eleConsCha->resize( nObj );
  eleEBEEGap->resize( nObj );
  eleDb     ->resize( nObj );
  eleMap.clear();
  etkMap.clear();
  telMap.clear();
//  tkeMap.clear();
  if ( !vElectrons ) {
    cout << "invalid electrons" << endl;
    return;
  }

  vector<const Electron*> electronPtr;
  electronPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    electronPtr[iObj] = &( electrons->at( iObj ) );
  }

  compareByPt<Electron> eleComp;
  sort( electronPtr.begin(), electronPtr.end(), eleComp );

  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Electron* electptr = electronPtr[iObj];
    const Electron& electron = *electptr;
    eleMap[electptr] = iObj;
//    eleMap.insert( make_pair( &electron, iObj ) );
    const Track* tkp = BPHTrackReference::getTrack( electron, "cbe" );
    if ( tkp != 0 ) {
      telMap[tkp     ] = electptr;
//      tkeMap[tkp     ] = iObj;
      etkMap[electptr] = tkp;
    }
    const Candidate::LorentzVector p4 = electron.p4();
    elePt     ->at( iObj ) = p4.pt    ();
    eleEta    ->at( iObj ) = p4.eta   ();
    elePhi    ->at( iObj ) = p4.phi   ();
    elePx     ->at( iObj ) = p4.px    ();
    elePy     ->at( iObj ) = p4.py    ();
    elePz     ->at( iObj ) = p4.pz    ();
    eleE      ->at( iObj ) = p4.energy();
    eleCharge ->at( iObj ) = electron.charge();
    eleTrk    ->at( iObj ) = -1;
    eleTrg    ->at( iObj ) = nearestHLT( PDEnumString::hltElectron,
                                         p4.pt(), p4.eta(), p4.phi() );

    eleChaIso ->at( iObj ) = electron.chargedHadronIso();
    eleNeuIso ->at( iObj ) = electron.neutralHadronIso();
    elePhoIso ->at( iObj ) = electron.photonIso();
    elePCHIso ->at( iObj ) = electron.puChargedHadronIso();
//    double absEta =
    eleAbsEta ->at( iObj ) = fabs( electron.superCluster()->eta() );
    eleAEff   ->at( iObj ) = -999.999;
//    eleAEff   ->at( iObj ) =
//      ElectronEffectiveArea::GetElectronEffectiveArea(
//      ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, absEta,
//      ElectronEffectiveArea::kEleEAData2011 );

    eleID     ->at( iObj ) = 0;//electron.electronID( "eidMediumMC" );
    eleConsCha->at( iObj ) = electron.isGsfCtfScPixChargeConsistent();
    eleEBEEGap->at( iObj ) = electron.isEBEEGap();
    eleDb     ->at( iObj ) = electron.dB();

  }

  return;

}


void PDEDMToNtuple::fillTaus() {

  gt_taus.get( currentEvBase, taus );
  bool vTaus = taus.isValid();

  // store taus info

  int iObj;
  int nObj = nTaus = ( vTaus ? taus->size() : 0 );
  tauPt    ->resize( nObj );
  tauEta   ->resize( nObj );
  tauPhi   ->resize( nObj );
  tauPx    ->resize( nObj );
  tauPy    ->resize( nObj );
  tauPz    ->resize( nObj );
  tauE     ->resize( nObj );
  tauCharge->resize( nObj );
  tauTrg   ->resize( nObj );
  if ( !vTaus ) {
    cout << "invalid taus" << endl;
    return;
  }

  vector<const Tau*> tauPtr;
  tauPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    tauPtr[iObj] = &( taus->at( iObj ) );
  }

  compareByPt<Tau> tauComp;
  sort( tauPtr.begin(), tauPtr.end(), tauComp );

  tauMap.clear();
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Tau& tau = *tauPtr[iObj];
    tauMap[&tau] = iObj;
//    tauMap.insert( make_pair( &tau, iObj ) );

    const Candidate::LorentzVector p4 = tau.p4();
    tauPt    ->at( iObj ) = p4.pt    ();
    tauEta   ->at( iObj ) = p4.eta   ();
    tauPhi   ->at( iObj ) = p4.phi   ();
    tauPx    ->at( iObj ) = p4.px    ();
    tauPy    ->at( iObj ) = p4.py    ();
    tauPz    ->at( iObj ) = p4.pz    ();
    tauE     ->at( iObj ) = p4.energy();
    tauCharge->at( iObj ) = tau.charge();
    tauTrg   ->at( iObj ) = nearestHLT( PDEnumString::hltTau,
                                        p4.pt(), p4.eta(), p4.phi() );

  }

  return;

}


void PDEDMToNtuple::fillJets() {

  gt_jets.get( currentEvBase, jets );
  bool vJets = jets.isValid();

  // store jets info

  int iObj;
  int nObj = 0;
  jetPt  ->clear();
  jetEta ->clear();
  jetPhi ->clear();
  jetPx  ->clear();
  jetPy  ->clear();
  jetPz  ->clear();
  jetE   ->clear();
  jetCSV ->clear();
  jetTCHE->clear();
  jetPF  ->clear();
  jetTrg ->clear();
  jetNDau->clear();
  jetNHF ->clear();
  jetNEF ->clear();
  jetCHF ->clear();
  jetCEF ->clear();
  jetNCH ->clear();
  if ( !vJets ) {
    cout << "invalid jets" << endl;
    return;
  }
  else {
    nObj = jets->size();
  }

  map<const Jet*,int> jhiMap;
  vector<const Jet*> jetPtr;
  jetPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) 
    jhiMap[jetPtr[iObj] = &( jets->at( iObj ) )] = iObj;
//    jhiMap.insert( make_pair( jetPtr[iObj] = &( jets->at( iObj ) ), iObj ) );

  compareByPt<Jet> jetComp;
  sort( jetPtr.begin(), jetPtr.end(), jetComp );

  jetMap.clear();
  pcjMap.clear();
  ptjMap.clear();
  gpjMap.clear();
  nJets = 0;
  bool select;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    select = false;

    const Jet* jPtr = jetPtr[iObj];
    const Jet& jet = *jPtr;

    if ( fabs( jet.eta() ) < jetEtaMax ) select = true;
    if (       jet.pt ()   > jetPtMin  ) select = true;
    if ( !select ) continue;

    gpjMap[jet.genJet()] = iObj;

    std::vector<std::string> userFloatLabels = jPtr->userFloatNames();
    int ijUI;
    int isUI;
    int njUI = userFloatLabels.size();
    int nsUI = savedJetInfo.size();
    for ( ijUI = 0; ijUI < njUI; ++ijUI ) {
      const string& name = userFloatLabels[ijUI];
      for ( isUI = 0; isUI < nsUI; ++isUI ) {
        if ( wildMatch( name, savedJetInfo[isUI] ) )
             fillUserInfo( PDEnumString::recJet, iObj,
                           PDEnumString::findRecoUIType( name ),
                           jPtr->userFloat( name ) );
      }
    }

    jetMap[&jet] = nJets;
//    jetMap.insert( make_pair( &jet, nJets ) );
//    const vector<PFCandidatePtr>& jPFC = jet.getPFConstituents();
    int iPFC;
    int nPFC = jet.numberOfDaughters();
//    int nPFC = jPFC.size();
    for ( iPFC = 0; iPFC < nPFC; ++iPFC ) {
      const Candidate* pfp = jet.daughter( iPFC );
      const Track    * tkp = BPHTrackReference::getTrack( *pfp, "cfbp" );
      ptjMap[tkp] = nJets;
      try {
        pcjMap[&(*pfp)] = nJets;
      }
      catch ( edm::Exception e ) {
      }
    }

    jetPt  ->push_back( jet.pt    () );
    jetEta ->push_back( jet.eta   () );
    jetPhi ->push_back( jet.phi   () );
    jetPx  ->push_back( jet.px    () );
    jetPy  ->push_back( jet.py    () );
    jetPz  ->push_back( jet.pz    () );
    jetE   ->push_back( jet.energy() );
    jetCSV ->push_back( jet.bDiscriminator( labelCSV  )   );
    jetTCHE->push_back( jet.bDiscriminator( labelTCHE )   );
    jetTrg ->push_back( nearestHLT( PDEnumString::hltJet,
                                    jet.pt(), jet.eta(), jet.phi() ) );
    jetPF  ->push_back( jet.isPFJet()                     );
    jetNDau->push_back( jet.numberOfDaughters()           );
    jetNHF ->push_back( jet.neutralHadronEnergyFraction() );
    jetNEF ->push_back( jet.neutralEmEnergyFraction()     );
    jetCHF ->push_back( jet.chargedHadronEnergyFraction() );
    jetCEF ->push_back( jet.chargedEmEnergyFraction()     );
    jetNCH ->push_back( jet.chargedMultiplicity()         );

    ++nJets;

  }

  return;

}


void PDEDMToNtuple::fillVtxTrkMap() {

  if ( verbose ) cout << "fillVtxTrkMap" << endl;
  if ( read_gentrk )
  gt_generalTracks.get( currentEvBase, generalTracks );
  gt_pVertices.get( currentEvBase, pVertices     );
  int iTrk;
  int nTrk = ( generalTracks.isValid() ? generalTracks->size() : 0 );
  int iPVt;
  int nPVt = ( pVertices    .isValid() ? pVertices    ->size() : 0 );
//  int iSVt;
//  int nSVt = ( sVertices    .isValid() ? sVertices    ->size() : 0 );

  map<const Track*,const Muon    *>::const_iterator m_iter;
  map<const Track*,const Muon    *>::const_iterator m_iend = tmuMap.end();
  map<const Track*,const Electron*>::const_iterator e_iend = telMap.end();
  map<const Track*,int            >::const_iterator j_iend = ptjMap.end();
//  map<const Track*,int>::const_iterator it_m;
//  map<const Track*,int>::const_iterator it_e;
//  map<const Track*,int>::const_iterator it_p;
//  map<const Track*,int>::const_iterator ie_m = tkmMap.end();
//  map<const Track*,int>::const_iterator ie_e = tkeMap.end();
//  map<const Track*,int>::const_iterator ie_p = ptjMap.end();

  // look for vertices with tracks linked to a muon, electron or jet
  vtxList.clear();
  allPTk.clear();
  vtxMap.clear();
  tvpMap.clear();
  map< const Vertex*,vector<const Track*> > vvtMap;
  for ( iPVt = 0; iPVt < nPVt; ++iPVt ) {
    const Vertex& vtx = pVertices->at( iPVt );
    const Vertex* vtp = &vtx;
    bool found = writeAllPrimaryVertices;
//    if ( recoverMuonTracks && !iPVt ) found = true;
    vector<const Track*>& tks = vvtMap[vtp];
//    cout << "vertex " << iPVt << ' '
//         << vtx.tracksSize() << ' '
//         << vtkMap.size() << endl;
    tks.reserve( vtx.tracksSize() + vtkMap.size() );
    Vertex::trackRef_iterator it_v = vtx.tracks_begin();
    Vertex::trackRef_iterator ie_v = vtx.tracks_end();
    while ( it_v != ie_v ) {
      try {
        const TrackBaseRef& tkr = *it_v++;
        const Track* tkp = tkr.get();
        tks.push_back( tkp );
      }
      catch ( edm::Exception e ) {
//        cout << "missing track from vertex " << iPVt << endl;
      }
    }
    typedef multimap<const Vertex*,const Track*>::const_iterator vt_iter;
    pair<vt_iter,vt_iter> vtr = vtkMap.equal_range( vtp );
    vt_iter it_c = vtr.first;
    vt_iter ie_c = vtr.second;
//    multimap<const Vertex*,const Track*>::const_iterator it_c = vtkMap.begin();
//    multimap<const Vertex*,const Track*>::const_iterator ie_c = vtkMap.end();
    while ( it_c != ie_c ) tks.push_back( it_c++->second );
    int itk;
    int ntk = tks.size();
    for ( itk = 0; itk < ntk; ++itk ) {
      const Track* tkp = tks[itk];
//      cout << "...track " << tkp << endl;
      tvpMap[tkp] = vtp;
      if ( allPTk.find( tkp ) == allPTk.end() ) allPTk.insert( tkp );
      m_iter = tmuMap.find( tkp );
      if ( m_iter             != m_iend ) {
//           cout << "link muon " << m_iter->second << " to vertex " << endl;
           pcvMap[m_iter->second] = vtp;  found = true; }
      if ( telMap.find( tkp ) != e_iend ) found = true;
      if ( ptjMap.find( tkp ) != j_iend ) found = true;
    }
/*
    while ( it_v != ie_v ) {
      try {
        const TrackBaseRef& tkr = *it_v++;
        const Track* tkp = &(*tkr);
//        tvpMap[tkp] = &vtx;
        if ( allPTk.find( tkp ) == allPTk.end() ) allPTk.insert( tkp );
        if ( tmuMap.find( tkp ) != m_iend ) found = true;
        if ( telMap.find( tkp ) != e_iend ) found = true;
        if ( ptjMap.find( tkp ) != j_iend ) found = true;
//        it_m = tkmMap.find( tkp );
//        it_e = tkeMap.find( tkp );
//        it_p = ptjMap.find( tkp );
//        if ( it_m != ie_m ) found = true;
//        if ( it_e != ie_e ) found = true;
//        if ( it_p != ie_p ) found = true;
      }
      catch ( edm::Exception e ) {
      }
    }
*/
    const reco::Vertex* pvt = &vtx;
    vtxMap[pvt] = -1;
    if ( found ) vtxList.push_back( pvt );
//    if ( found ) vtxList.push_back( &vtx );
  }
  nPVTotal = nPVt;
  nPVt = vtxList.size();

  // save tracks linked to a primary vertex
  tkvMap.clear();
  for ( iPVt = 0; iPVt < nPVt; ++iPVt ) {
    const Vertex* vtp = vtxList[iPVt];
    vtxMap[vtp] = iPVt;
    const vector<const Track*>& tks = vvtMap[vtp];
    int itk;
    int ntk = tks.size();
    for ( itk = 0; itk < ntk; ++itk ) tkvMap[tks[itk]] = iPVt;
/*
    for ( itk = 0; itk < ntk; ++itk ) {
      const Track* tkp = tks[itk];
      if ( fabs( tkp->eta() ) > trkEtaMax ) continue;
      if (       tkp->pt ()   < trkPtMin  ) continue;
      tkvMap[tkp] = iPVt;
    }
*/
/*
    const Vertex& vtx = *vtxList[iPVt];
    vtxMap[&vtx] = iPVt;
    Vertex::trackRef_iterator it_v = vtx.tracks_begin();
    Vertex::trackRef_iterator ie_v = vtx.tracks_end();
    while ( it_v != ie_v ) {
      try {
        const TrackBaseRef& tkr = *it_v++;
        if ( fabs( tkr->eta() ) > trkEtaMax ) continue;
        if (       tkr->pt ()   < trkPtMin  ) continue;
        tkvMap[&(*tkr)] = iPVt;
      }
      catch ( edm::Exception e ) {
      }
    }
*/
  }

  // recover tracks not linked to any primary vertex but near to one of them
  tkrSet.clear();
  set<const Track*>::const_iterator a_iend = allPTk.end();
  for ( iTrk = 0; iTrk < nTrk; ++iTrk ) {
    const Track& trk = generalTracks->at( iTrk );
    const Track* tkp = &trk;
    // skip tracks linked to a primary vertex
    if ( allPTk.find( tkp ) != a_iend ) continue;
    if ( fabs( tkp->eta() ) > trkEtaMax ) continue;
    if (       tkp->pt ()   < trkPtMin  ) continue;
    for ( iPVt = 0; iPVt < nPVt; ++iPVt ) {
      const Vertex& vtx = *vtxList[iPVt];
      const Vertex::Point& pos = vtx.position();
      if ( fabs( tkp->dz( pos ) ) < trkDzMax ) tkrSet.insert( tkp );
    }
  }

/*
  // recover tracks linked to a secondary vertex
  for ( iSVt = 0; iSVt < nSVt; ++iSVt ) {
    const SecondaryVertexTagInfo& secVtxTagInfo = sVertices->at( iSVt );
    int iVtx;
    int nVtx = secVtxTagInfo.nVertices();
    for ( iVtx = 0; iVtx < nVtx; ++iVtx ) {
      const        Vertex& vtx = secVtxTagInfo.secondaryVertex( iVtx );
      Vertex::trackRef_iterator v_iter = vtx.tracks_begin();
      Vertex::trackRef_iterator v_iend = vtx.tracks_end();
      while ( v_iter != v_iend ) {
        const TrackBaseRef& tkr = *v_iter++;
        const Track* tkp = &(*tkr);
        if ( tkrSet.find( tkp ) == tkrSet.end() ) tkrSet.insert( tkp );
      }
    }
  }
*/

  return;

}


void PDEDMToNtuple::fillPFCandidates() {

  candList.clear();
//  candType.clear();
  if ( readPF ) fillPFList( pfCandidates, gt_pfCandidates,
                            PDEnumString::pflink );
  if ( readPC ) fillPFList( pcCandidates, gt_pcCandidates,
                            PDEnumString::packed );
  if ( readGP ) fillPFList( gpCandidates, gt_gpCandidates,
                            PDEnumString::gplink );

  // store particle flow info

  pfcPt      ->clear();
  pfcEta     ->clear();
  pfcPhi     ->clear();
  pfcPx      ->clear();
  pfcPy      ->clear();
  pfcPz      ->clear();
  pfcE       ->clear();
  pfcCharge  ->clear();
  pfcJet     ->clear();
  pfcTrk     ->clear();

  int iObj;
  int nObj = candList.size();
  pfcMap.clear();
  ptkMap.clear();
  tpfMap.clear();
//  pcvMap.clear();
//  tkpMap.clear();
  pTType.clear();
  pTrack.clear();
  pTrack.reserve( 2 * nObj );
  nPF = 0;
  set<const Track*                >::const_iterator r_iend = tkrSet.end();
  map<const Track*,const Muon    *>::const_iterator m_iend = tmuMap.end();
  map<const Track*,const Electron*>::const_iterator e_iend = telMap.end();
  map<const Track*,int            >::const_iterator v_iend = tkvMap.end();
  map<const Candidate*,int        >::const_iterator j_iter;
  map<const Candidate*,int        >::const_iterator j_iend = pcjMap.end();
//  map<const Track      *,int>::const_iterator m_iter;
//  map<const Track      *,int>::const_iterator e_iter;
//  map<const Track      *,int>::const_iterator v_iter;
//  map<const Candidate  *,int>::const_iterator j_iter;
//  map<const Track      *,int>::const_iterator m_iend = tkmMap.end();
//  map<const Track      *,int>::const_iterator e_iend = tkeMap.end();
//  map<const Track      *,int>::const_iterator v_iend = tkvMap.end();
//  map<const Candidate  *,int>::const_iterator j_iend = pcjMap.end();
  map<const Vertex*,int>::const_iterator t_iter;
  map<const Vertex*,int>::const_iterator t_iend = vtxMap.end();
  map<const Track*,const Vertex*>::const_iterator w_iter;
  map<const Track*,const Vertex*>::const_iterator w_iend = tvpMap.end();
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Candidate* pfp = candList[iObj];
//    cout << "PFCandidate: " << pfp << endl;
    const Candidate& pfc = *pfp;

    pTList.clear();
    pTList.reserve( 6 );
    const Track* tkp;
    if ( ( tkp = BPHTrackReference::getFromPC( pfc ) ) != 0 )
      {  setTrkType( tkp, PDEnumString::packed, pTList, pTType );
//         cout << "pt: "    << tkp->pt () << " , "
//              << "trkIP: " << tkp->dxy() << " "
//                           << tkp-> dz() << " "
//                           << tkp->dxyError() << " "
//                           << tkp-> dzError() << endl;
         const Vertex* pvtx = tvpMap[tkp] = pcvMap[pfp] =
                              PDVertexWrapBase::vertexRef( pfp );
         t_iter = vtxMap.find( pvtx );
         int ivtx = ( t_iter != t_iend ? t_iter->second : -1 );
//         cout << "pcvMap[" << pfp << "] = " << pcvMap[pfp] << ' ' << ivtx << ' ' << pfp->charge() << endl;
         if ( ivtx >= 0 ) tkvMap[tkp] = ivtx;
         v_iend = tkvMap.end(); }
    if ( ( tkp = BPHTrackReference::getFromPF( pfc ) ) != 0 )
         setTrkType( tkp, PDEnumString::pflink, pTList, pTType );
    if ( ( tkp = BPHTrackReference::getFromRC( pfc ) ) != 0 )
         setTrkType( tkp, PDEnumString::rclink, pTList, pTType );
    if ( ( tkp = BPHTrackReference::getFromGP( pfc ) ) != 0 )
         setTrkType( tkp, PDEnumString::gplink, pTList, pTType );
    int iTrk; 
    int nTrk = pTList.size();
//    int muoIndex;
//    int eleIndex;
//    int vtxIndex;
    int jetIndex = ( ( j_iter = pcjMap.find( pfp ) ) != j_iend ?
                       j_iter->second : -1 );
    bool found = !selectAssociatedPF;
    for ( iTrk = 0; iTrk < nTrk; ++iTrk ) {
      tkp = pTList[iTrk];
      if ( tpfMap.find( tkp ) != tpfMap.end() ) continue;
//      muoIndex = ( ( m_iter = tkmMap.find( tkp ) ) != m_iend ?
//                     m_iter->second : -1 );
//      eleIndex = ( ( e_iter = tkeMap.find( tkp ) ) != e_iend ?
//                     e_iter->second : -1 );
//      vtxIndex = ( ( v_iter = tkvMap.find( tkp ) ) != v_iend ?
//                     v_iter->second : -1 );
      if ( selectAssociatedPF &&
           ( tkrSet.find( tkp ) == r_iend ) &&
           ( tmuMap.find( tkp ) == m_iend ) &&
           ( telMap.find( tkp ) == e_iend ) &&
           ( tkvMap.find( tkp ) == v_iend ) &&
           ( jetIndex < 0 ) ) continue;
//      if ( selectAssociatedPF &&
//           ( muoIndex < 0 ) &&
//           ( eleIndex < 0 ) &&
//           ( vtxIndex < 0 ) &&
//           ( jetIndex < 0 ) &&
//           ( tkrSet.find( tkp ) == r_iend ) ) continue;
      found = true;
      pTrack.push_back( tkp );
      tpfMap[tkp] = pfp;
//      tkpMap[tkp] = nPF;
      ptkMap.insert( make_pair( pfp, tkp ) );
      vector<const Candidate*> pfl;
      pfl.reserve( cmuMap.size() + 1 );
      pfl.push_back( pfp );
      typedef multimap<const Candidate*,const Muon*>::const_iterator cmu_iter;
      pair<cmu_iter,cmu_iter> cmr = cmuMap.equal_range( pfp );
      cmu_iter cm_iter = cmr.first;
      cmu_iter cm_iend = cmr.second;
      while ( cm_iter != cm_iend ) pfl.push_back( cm_iter++->second );
      int ipl;
      int npl = pfl.size();
      for ( ipl = 0; ipl < npl; ++ipl ) {
        const Candidate* ppl = pfl[ipl];
        if ( pcvMap.find( ppl ) == pcvMap.end() ) {
//          cout << "fill pcvMap... " << ppl << ' ' << tkp << endl;
          w_iter = tvpMap.find( tkp );
          const Vertex* pvtx = ( w_iter != w_iend ? w_iter->second : 0 );
          if ( pvtx != 0 ) pcvMap[ppl] = pvtx;
//          cout << "vertex linked " << pvtx << endl;
//          t_iter = ( pvtx != 0 ? vtxMap.find( tvpMap[tkp] = pcvMap[ppl]
//                                                          = pvtx ) : t_iend );
//          int ivtx = ( t_iter != t_iend ? t_iter->second : -1 );
//          if ( ivtx >= 0 ) 
        }
      }
    }
    if ( !found ) continue;

//    cout << "stored at" << nPF << endl;
    pfcMap[pfp] =  nPF;
    const Candidate::LorentzVector p4 = pfc.p4();

    pfcPt      ->push_back( p4.pt    () );
    pfcEta     ->push_back( p4.eta   () );
    pfcPhi     ->push_back( p4.phi   () );
    pfcPx      ->push_back( p4.px    () );
    pfcPy      ->push_back( p4.py    () );
    pfcPz      ->push_back( p4.pz    () );
    pfcE       ->push_back( p4.energy() );
    pfcCharge  ->push_back( pfc.charge() );
    pfcJet     ->push_back( jetIndex );
    pfcTrk     ->push_back( -1 );

    ++nPF;

  }

  return;

}


void PDEDMToNtuple::fillTracks() {

  bool vTracks = ( read_gentrk && generalTracks.isValid() );

  // store tracks info

  int iObj;
  int nObj = 0;
  trkPt        ->clear();
  trkEta       ->clear();
  trkPhi       ->clear();
  trkPx        ->clear();
  trkPy        ->clear();
  trkPz        ->clear();
  trkCharge    ->clear();
  trkType      ->clear();
  trkPFC       ->clear();
  trkJet       ->clear();
  trkPVtx      ->clear();
  trkQuality   ->clear();
  trkHitPattern->clear();
  trkLayPattern->clear();
  trkNormChi2  ->clear();
  trkDxy       ->clear();
  trkDz        ->clear();
  trkExy       ->clear();
  trkEz        ->clear();
  int ngt = 0;
  int npt = pTrack.size();
  if ( vTracks ) {
    nObj = ( ngt = generalTracks->size() ) + npt + mTrack.size();
  }
  else {
    if ( !recoverMuonTracks && !recoverCandTracks )
    cout << "invalid tracks" << endl;
    if ( !( nObj = npt + mTrack.size() ) ) return;
  }
  int ngp = ngt + npt;

  trkMap.clear();
  nTracks = 0;
  map<const Track*,int             >::const_iterator v_iter;
  set<const Track*                 >::const_iterator r_iend = tkrSet.end();
  map<const Track*,const Muon     *>::const_iterator m_iend = tmuMap.end();
  map<const Track*,const Electron *>::const_iterator e_iend = telMap.end();
  map<const Track*,const Candidate*>::const_iterator p_iend = tpfMap.end();
  map<const Track*,int             >::const_iterator v_iend = tkvMap.end();
//  map<const Track      *,int>::const_iterator m_iter;
//  map<const Track      *,int>::const_iterator e_iter;
//  map<const Track      *,int>::const_iterator p_iter;
//  map<const Track      *,int>::const_iterator v_iter;
//  map<const Track      *,int>::const_iterator m_iend = tkmMap.end();
//  map<const Track      *,int>::const_iterator e_iend = tkeMap.end();
//  map<const Track      *,int>::const_iterator p_iend = tkpMap.end();
//  map<const Track      *,int>::const_iterator v_iend = tkvMap.end();
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    int type = 0;

//    int iPF = -1;
    const Track* tkp;
    if ( iObj < ngt ) {
      const Track& gtk = generalTracks->at( iObj );
      tkp = &gtk;
      type |= PDEnumString::general;
    }
    else
    if ( iObj < ngp ) {
      tkp = pTrack.at( iObj - ngt );
//      tkp = pTrack.at( iPF = ( iObj - ngt ) );
      if ( tkp == 0 ) continue;
      type |= pTType[tkp];
//      type |= candType[iPF];
    }
    else {
      tkp = mTrack.at( iObj - ngp );
      if ( tkp == 0 ) continue;
      type |= mTType[tkp];
    }
    map<const Track*,int>::const_iterator it_p = trkMap.find( tkp );
    map<const Track*,int>::const_iterator ie_p = trkMap.end();
    if ( it_p != ie_p ) {
      trkType->at( it_p->second ) |= type;
      continue;
    }
    const Track& trk = *tkp;

//    int muoIndex = ( ( m_iter = tkmMap.find( tkp ) ) != m_iend ?
//                       m_iter->second : -1 );
//    int eleIndex = ( ( e_iter = tkeMap.find( tkp ) ) != e_iend ?
//                       e_iter->second : -1 );
//    int pfcIndex = ( ( p_iter = tkpMap.find( tkp ) ) != p_iend ?
//                       p_iter->second : -1 );
//    int vtxIndex = ( ( v_iter = tkvMap.find( tkp ) ) != v_iend ?
//                       v_iter->second : -1 );
    v_iter = tkvMap.find( tkp );
    if ( selectAssociatedTk &&
         ( tkrSet.find( tkp ) == r_iend ) &&
         ( tmuMap.find( tkp ) == m_iend ) &&
         ( telMap.find( tkp ) == e_iend ) &&
         ( tpfMap.find( tkp ) == p_iend ) &&
         ( v_iter             == v_iend ) ) continue;
//    if ( selectAssociatedTk &&
//         ( muoIndex < 0 ) &&
//         ( eleIndex < 0 ) &&
//         ( pfcIndex < 0 ) &&
//         ( vtxIndex < 0 ) &&
//         ( tkrSet.find( tkp ) == r_iend ) ) continue;

    trkMap[tkp] = nTracks;
//    trkMap.insert( make_pair( tkp, nTracks ) );
    const HitPattern& hitPattern = tkp->hitPattern();
    int hp = ( hitPattern.numberOfValidMuonHits   () * 1000000 ) +
             ( hitPattern.numberOfValidPixelHits  () *   10000 ) +
             ( hitPattern.numberOfValidTrackerHits() *     100 ) +
               tkp->      numberOfValidHits();
    int lp = ( hitPattern.  pixelLayersWithMeasurement() * 10000 ) +
             ( hitPattern.  stripLayersWithMeasurement() *   100 ) +
               hitPattern.trackerLayersWithMeasurement();

//    int ipv = tkvMap[tkp];
    int npv = vtxList.size();
    int ipv = ( v_iter != v_iend ? v_iter->second : -1 );
//    cout << "tkvMap[" << tkp << "] = " << ipv << endl;
    if ( ipv < 0 ) {
      const Vertex* vtp = nearestPV( tkp );
//      cout << "nearest found: " << vtp << endl;
      if ( vtp != 0 ) ipv = vtxMap[vtp] + npv;
//      cout << "... " << ipv << endl;
    }

    trkPt        ->push_back( trk.pt    () );
    trkEta       ->push_back( trk.eta   () );
    trkPhi       ->push_back( trk.phi   () );
    trkPx        ->push_back( trk.px    () );
    trkPy        ->push_back( trk.py    () );
    trkPz        ->push_back( trk.pz    () );
    trkCharge    ->push_back( trk.charge() );
    trkType      ->push_back( type );
    trkNext      ->push_back( -1 );
    trkPFC       ->push_back( -1 );
    trkJet       ->push_back( -1 );
    trkPVtx      ->push_back( ipv );
    trkQuality   ->push_back( trk.qualityMask() );
    trkHitPattern->push_back( hp );
    trkLayPattern->push_back( lp );
    trkNormChi2  ->push_back( trk.normalizedChi2() );

    math::XYZPoint bsPos(bsX, bsY, bsZ);
    trkDxy       ->push_back( trk.dxy( bsPos ) );
    trkDz        ->push_back( trk.dz ( bsPos ) );
    trkExy       ->push_back( trk.dxyError() );
    trkEz        ->push_back( trk.dzError () );//    if ( ipv < 0 ) {
//    if ( ipv < 0 ) {
//      trkDxy       ->push_back( trk.dxy() );
//      trkDz        ->push_back( trk.dz () );
//      trkExy       ->push_back( trk.dxyError() );
//      trkEz        ->push_back( trk.dzError () );
//    }
//    else {
//      if ( ipv >= npv ) ipv -= npv;
//      const Vertex* vtp = vtxList[ipv];
//      const Vertex::Point& pos = vtp->position();
//      trkDxy       ->push_back( trk.dxy( pos ) );
//      trkDz        ->push_back( trk.dz ( pos ) );
//      trkExy       ->push_back( trk.dxyError() );
//      trkEz        ->push_back( trk.dzError () );
//    }

    ++nTracks;

  }

  return;

}


void PDEDMToNtuple::fillPVertices() {

  if ( verbose ) cout << "fillPVertices" << endl;
  // store primary vertices info

  int iObj;
  int nObj = nPVertices = vtxList.size();
  pvtX         ->resize( nObj );
  pvtY         ->resize( nObj );
  pvtZ         ->resize( nObj );
  pvtSxx       ->resize( nObj );
  pvtSyy       ->resize( nObj );
  pvtSzz       ->resize( nObj );
  pvtSxy       ->resize( nObj );
  pvtSxz       ->resize( nObj );
  pvtSyz       ->resize( nObj );
  pvtNTracks   ->resize( nObj );
  pvtNormChi2  ->resize( nObj );
  pvtBadQuality->resize( nObj );

  map<const Track*,int>::const_iterator it_p;
  map<const Track*,int>::const_iterator ie_p = trkMap.end();
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const Vertex& vtx = *vtxList[iObj];
    const Vertex::Point& pos = vtx.position();

/*
    bool found = writeAllPrimaryVertices;
    Vertex::trackRef_iterator iter = vtx.tracks_begin();
    Vertex::trackRef_iterator iend = vtx.tracks_end();
    while ( iter != iend ) {
      try {
        const TrackBaseRef& tkr = *iter++;
        if ( ( it_p = trkMap.find( &(*tkr ) ) ) == ie_p ) continue;
        found = true;
        int trkIndex = it_p->second;
        int& trkLink = trkPVtx->at( trkIndex );
        if ( trkLink < 0 ) {
          trkLink = nPVertices;
          trkDxy->at( trkIndex ) = tkr->dxy( pos );
          trkDz ->at( trkIndex ) = tkr->dz ( pos );
          trkExy->at( trkIndex ) = tkr->dxyError();
          trkEz ->at( trkIndex ) = tkr->dzError();
        }
      }
      catch ( edm::Exception e ) {
      }
    }
    if ( !found ) continue;
*/

    pvtX         ->at( iObj ) = pos.X();
    pvtY         ->at( iObj ) = pos.Y();
    pvtZ         ->at( iObj ) = pos.Z();
    pvtSxx       ->at( iObj ) = vtx.covariance( 0, 0 );
    pvtSyy       ->at( iObj ) = vtx.covariance( 1, 1 );
    pvtSzz       ->at( iObj ) = vtx.covariance( 2, 2 );
    pvtSxy       ->at( iObj ) = vtx.covariance( 0, 1 );
    pvtSxz       ->at( iObj ) = vtx.covariance( 0, 2 );
    pvtSyz       ->at( iObj ) = vtx.covariance( 1, 2 );
    pvtNTracks   ->at( iObj ) = vtx.nTracks( -1.0 );
    pvtNormChi2  ->at( iObj ) = vtx.normalizedChi2();
    pvtBadQuality->at( iObj ) = vtx.isValid() ? 0 : ( vtx.isFake() ? 1 : 2 );

  }

  return;

}


void PDEDMToNtuple::fillSVertices() {

  if ( verbose ) cout << "fillSVertices" << endl;
  // store secondary vertices info

  svtX         ->clear();
  svtY         ->clear();
  svtZ         ->clear();
  svtSxx       ->clear();
  svtSyy       ->clear();
  svtSzz       ->clear();
  svtSxy       ->clear();
  svtSxz       ->clear();
  svtSyz       ->clear();
  svtDirX      ->clear();
  svtDirY      ->clear();
  svtDirZ      ->clear();
  svtChi2      ->clear();
  svtNDOF      ->clear();
//  svtNormChi2  ->clear();
  svtMass      ->clear();
  svtDist2D    ->clear();
  svtSigma2D   ->clear();
  svtDist3D    ->clear();
  svtSigma3D   ->clear();
  svtJet       ->clear();
  svtNTracks   ->clear();
  svtBadQuality->clear();

  tipTrk       ->clear();
  tipSVtx      ->clear();
  tipDxy       ->clear();
  tipDz        ->clear();

  tvpTip       ->clear();
  tvpPx        ->clear();
  tvpPy        ->clear();
  tvpPz        ->clear();

  svtMap.clear();
  if ( !read_svts && !read_svtj ) return;

  nSVertices = 0;
  nTkIPs     = 0;
  nVtxPs     = 0;
  nCompVts   = 0;

  if ( read_svts ) fillSVTInfoMap();
  if ( read_svtj ) fillSVTIJetMap();

  map< const Jet*,vector<VtxInfo> >::const_iterator svt_iter = svtMap.begin();
  map< const Jet*,vector<VtxInfo> >::const_iterator svt_iend = svtMap.end();
  while ( svt_iter != svt_iend ) {
    const map< const Jet*,vector<VtxInfo> >::value_type& entry = *svt_iter++;
    const Jet* jet = entry.first;
    const vector<VtxInfo>& vtxList = entry.second;
    int iVtx;
    int nVtx = vtxList.size();
    for ( iVtx = 0; iVtx < nVtx; ++iVtx ) {

      const VtxInfo& info = vtxList[iVtx];
      int jetId = info.jetId;
      const PDVertexContainer& vtx = info.vtx;
      const vector<VtxComponent>& compList = info.compList;
      int itk = 0;
      int ntk = compList.size();

      const  GlobalVector& dir = *info.dir;
      const Measurement1D  d2d =  info.d2d;
      const Measurement1D  d3d =  info.d3d;

      vector<const Track*> tti( ntk );
      BPHRecoCandidate tmpc( currentEvSetup );
      map<const Track*,TransientTrack*> ttm;
      map<const Track*,float          > tmm;
//      map<const Track*,const Candidate*> rcm;
//      map<const Track*,const Candidate*> rom;
      for ( itk = 0; itk < ntk; ++itk ) {
        const VtxComponent& vc = compList[itk];
        const Candidate* pcp = vc.cand;
        const Track* tkp = tti[itk] = vc.track;
        ttm[tkp] = 0;
        tmm[tkp] = pcp->mass();
//        tmm[tkp] = -1.0;
//        rcm[tkp] = pcp;
        if ( pcp == 0 ) continue;
        stringstream sstr;
        sstr << "pf" << itk;
        tmpc.add( sstr.str(), pcp );
      }
      for ( itk = 0; itk < ntk; ++itk ) {
        const Track* tkp = tti[itk];
        if ( ttm[tkp] != 0 ) continue;
        stringstream sstr;
        sstr << "pf" << itk;
        const Candidate* td = tmpc.getDaug( sstr.str() );
        if ( td == 0 ) continue;
        ttm[tkp] = tmpc.getTransientTrack( td );
//        rom[tkp] = tmpc.originalReco( td );
      }
      int iPFC;
      int nPFC = jet->numberOfDaughters();
      for ( iPFC = 0; iPFC < nPFC; ++iPFC ) {
        const Candidate* pfp = jet->daughter( iPFC );
        const Track    * tkp = BPHTrackReference::getTrack( *pfp, "cfbp" );
        if ( tkp == 0 ) continue;
//        if ( ttm.find( tkp ) == ttm.end() ) ttm[tkp] = 0;
        if ( ttm.find( tkp ) == ttm.end() ) {
          ttm[tkp] = 0;
//          rcm[tkp] = pfp;
        }
      }

      addSecondaryVertex( *vtx.get(), -1.0, ttm, tmm,//rcm, rom,
                          dir, d2d, d3d, "svtTagInfo", jetId );

      int jtk;
      int ktk;
      for ( jtk = 0; jtk < ntk; ++jtk ) {
        const Candidate* rcp = compList[jtk].cand;
        if ( rcp == 0 ) continue;
        if ( rcp->charge() != +1 ) continue;
        const Track* tkp = compList[jtk].track;
        for ( ktk = 0; ktk < ntk; ++ktk ) {
          const Candidate* rcn = compList[ktk].cand;
          if ( rcn == 0 ) continue;
          if ( rcn->charge() != -1 ) continue;
          const Track* tkn = compList[ktk].track;
          BPHRecoCandidate tmpp( currentEvSetup );
          ttm.clear();
//          rcm.clear();
//          rom.clear();
          tmpp.add( "pPos", rcp, rcp->p4().M(), 1.e-05 );
          tmpp.add( "pNeg", rcn, rcn->p4().M(), 1.e-05 );
          if ( !tmpp.validVertex() ) continue;
          const Candidate* pPos = tmpp.getDaug( "pPos" );
          const Candidate* pNeg = tmpp.getDaug( "pNeg" );
          ttm[tkp] = tmpp.getTransientTrack( pPos );
          ttm[tkn] = tmpp.getTransientTrack( pNeg );
          tmm[tkp] = pPos->mass();
          tmm[tkn] = pNeg->mass();
//          rcm[tkp] = rcp;
//          rcm[tkn] = rcn;
//          rom[tkp] = tmpp.originalReco( rcp );
//          rom[tkn] = tmpp.originalReco( rcn );
          const  GlobalVector dir;
          const Measurement1D d2d;
          const Measurement1D d3d;
          addSecondaryVertex( PDVertexWrapper<Vertex>( tmpp.vertex() ),
                              -1.0, ttm, tmm,//rcm, rom,
                              dir, d2d, d3d, "svtFitPair", jetId );
        }
      }

    }
  }

  return;

}


void PDEDMToNtuple::fillSVertReco() {

  if ( verbose ) cout << "fillSVertReco" << endl;
  if ( currentEvSetup == 0 ) return;
  rsvMap.clear();

  map<const Candidate*,const Vertex*>::const_iterator p_iter;
  map<const Candidate*,const Vertex*>::const_iterator p_iend = pcvMap.end();

  if ( verbose ) cout << "fit jpsi" << endl;
  vector<BPHPlusMinusConstCandPtr> lJPsi;
  map<const BPHRecoCandidate*,BPHPlusMinusConstCandPtr> oMap;
  if ( vRecoFlag[PDEnumString::svtJPsi     ] ||
       vRecoFlag[PDEnumString::svtBuJPsiK  ] ||
       vRecoFlag[PDEnumString::svtBdJPsiKx ] ||
       vRecoFlag[PDEnumString::svtBsJPsiPhi] ) {
    BPHOniaToMuMuBuilder onia( *currentEvSetup,
                         BPHRecoBuilder::createCollection( muons, "cfpmig" ),
                         BPHRecoBuilder::createCollection( muons, "cfpmig" ) );
//    onia.setPtMin( BPHOniaToMuMuBuilder::Psi1, 4.0 );
    lJPsi = onia.getList( BPHOniaToMuMuBuilder::Psi1 );
    int iJPsi;
    int nJPsi = lJPsi.size();
    for ( iJPsi = 0; iJPsi < nJPsi; ++iJPsi ) {
      const BPHPlusMinusCandidate* jpsi = lJPsi[iJPsi].get();
      oMap[jpsi] = onia.getOriginalCandidate( *jpsi );
    }
  }
  int iJPsi;
  int nJPsi = lJPsi.size();
  const string ccName = "svtJPsi";
  for ( iJPsi = 0; iJPsi < nJPsi; ++iJPsi ) {
    const BPHPlusMinusCandidate* jpsi = lJPsi[iJPsi].get();
    if ( !jpsi->validVertex() ) continue;
//    jpsi->kinematicTree();
    const vector<const Candidate*>& jpd = jpsi->daughters();
    int id;
    int nd = jpd.size();
    map<const Track*,TransientTrack*> ttm;
    map<const Track*,float          > tmm;
//    map<const Track*,const Candidate*> rcm;
//    map<const Track*,const Candidate*> rom;
    const Vertex* vtp = 0;
    const Vertex* vtn = 0;
    for ( id = 0; id < nd; ++id ) {
      const Candidate* rc = jpd[id];
//      const Candidate* rc = jpsi->originalReco( jpd[id] );
      const Track* tkp = jpsi->getTrack( rc );
      ttm[tkp] = jpsi->getTransientTrack( rc );
      tmm[tkp] = jpd[id]->mass();
//      rcm[tkp] = rc;
//      rom[tkp] = jpsi->originalReco( rc );
      if ( vtp == 0 ) {
        p_iter = pcvMap.find( jpsi->originalReco( rc ) );
        if ( p_iter != p_iend ) vtp = p_iter->second;
      }
//      if ( vtp == 0 )
//           vtp = mcvMap[jpsi->originalReco( rc )];
      if ( vtn == 0 ) vtn = nearestPV( tkp );
//      cout << jpsi->originalReco( rc ) << "-->" << vtp << endl;
    }
    if ( vtp == 0 ) vtp = vtn;
//    cout << "vertex: " << vtp << endl;
    const Vertex& vtr = jpsi->vertex();
    GlobalVector  dir;
    Measurement1D d2d;
    Measurement1D d3d;
    if ( vtp != 0 ) vertexDir( *vtp, vtr, jpsi->composite(), dir, d2d, d3d );
//    cout << "JPsi mass: " << jpsi->composite().p4().mass() << ' '
//                          << jpsi->p4().mass() << ' '
//                          << jpsi->mass() << " / "
//                          << oMap[jpsi]->composite().p4().mass() << ' '
//                          << oMap[jpsi]->p4().mass() << ' '
//                          << oMap[jpsi]->mass() << endl;
    int svtIndex = addSecondaryVertex( PDVertexWrapper<Vertex>( vtr ),
                                       oMap[jpsi]->mass(), ttm, tmm,// rcm, rom,
//                                       jpsi->composite().mass(), ttm, tmm,// rcm, rom,
                                       dir, d2d, d3d, ccName, -1 );
    rsvMap[jpsi] = svtIndex;
  }

  if ( verbose ) cout << "fit kx0" << endl;
  vector<BPHPlusMinusConstCandPtr> lKx0;
  if ( vRecoFlag[PDEnumString::svtKx0     ] ||
       vRecoFlag[PDEnumString::svtBdJPsiKx] ) {
    BPHKx0ToKPiBuilder kx0( *currentEvSetup,
                       BPHRecoBuilder::createCollection( candList, "cfp" ),
                       BPHRecoBuilder::createCollection( candList, "cfp" ) );
    lKx0 = kx0.build();
//       lKx0 = BPHKx0ToKPiBuilder::build( *currentEvSetup,
//              BPHRecoBuilder::createCollection( candList ),
//              BPHRecoBuilder::createCollection( candList ) );
  }
  const string sdName = "svtKx0";

  if ( verbose ) cout << "fit phi" << endl;
  vector<BPHPlusMinusConstCandPtr> lPhi;
  if ( vRecoFlag[PDEnumString::svtPhi      ] ||
       vRecoFlag[PDEnumString::svtBsJPsiPhi] ) {
    BPHPhiToKKBuilder phi( *currentEvSetup,
                      BPHRecoBuilder::createCollection( candList, "cfp" ),
                      BPHRecoBuilder::createCollection( candList, "cfp" ) );
//    phi.setPtMin( 2.0 );
    lPhi = phi.build();
//       lPhi = BPHPhiToKKBuilder::build( *currentEvSetup,
//              BPHRecoBuilder::createCollection( candList ),
//              BPHRecoBuilder::createCollection( candList ) );
  }
  const string ssName = "svtPhi";

  if ( verbose ) cout << "fit bu" << endl;
  vector<BPHRecoConstCandPtr> lBu;
  if ( vRecoFlag[PDEnumString::svtBuJPsiK] ) {
    BPHBuToJPsiKBuilder bu( *currentEvSetup, lJPsi,
                        BPHRecoBuilder::createCollection( candList, "cfp" ) );
    lBu = bu.build();
//       lBu = BPHBuToJPsiKBuilder::build( *currentEvSetup, lJPsi,
//             BPHRecoBuilder::createCollection( candList ) );
  }
  int iBu;
  int nBu = lBu.size();
  const string buName = "svtBuJPsiK";
  for ( iBu = 0; iBu < nBu; ++iBu ) {
    const BPHRecoCandidate* bu = lBu[iBu].get();
    if ( !bu->validVertex() ) continue;
    const vector<const Candidate*>& bud = bu->daughFull();
    int id;
    int nd = bud.size();
    map<const Track*,TransientTrack*> ttm;
    map<const Track*,float          > tmm;
//    map<const Track*,const Candidate*> rcm;
//    map<const Track*,const Candidate*> rom;
    const Vertex* vtp = 0;
    const Vertex* vtn = 0;
    for ( id = 0; id < nd; ++id ) {
      const Candidate* rc = bud[id];
//      const Candidate* rc = bu->originalReco( bud[id] );
      const Track* tkp = bu->getTrack( rc );
      ttm[tkp] = bu->getTransientTrack( rc );
      tmm[tkp] = bud[id]->mass();
//      rcm[tkp] = rc;
//      rom[tkp] = bu->originalReco( rc );
      if ( vtp == 0 ) {
        p_iter = pcvMap.find( bu->originalReco( rc ) );
        if ( p_iter != p_iend ) vtp = p_iter->second;
      }
      if ( vtn == 0 ) vtn = nearestPV( tkp );
    }
    if ( vtp == 0 ) vtp = vtn;
    const Vertex& vtr = bu->vertex();
    GlobalVector  dir;
    Measurement1D d2d;
    Measurement1D d3d;
    if ( vtp != 0 ) vertexDir( *vtp, vtr, bu->composite(), dir, d2d, d3d );
    int svtIndex = addSecondaryVertex( PDVertexWrapper<Vertex>( vtr ),
                                       bu->mass(), ttm, tmm,// rcm, rom,
//                                       bu->p4().mass(), ttm, tmm,// rcm, rom,
                                       dir, d2d, d3d, buName, -1 );
    const BPHRecoCandidate* jpsi = bu->getComp( "JPsi" ).get();
    subPart->push_back( rsvMap[jpsi] );
    subSVtx->push_back( svtIndex );
    subMass->push_back( jpsi->p4().M() );
//    subMass->push_back( jpsi->vertex().p4().M() );
    ++nCompVts;
  }

  if ( verbose ) cout << "fit bd" << endl;
  vector<BPHRecoConstCandPtr> lBd;
  if ( vRecoFlag[PDEnumString::svtBdJPsiKx] ) {
    BPHBdToJPsiKxBuilder bd( *currentEvSetup, lJPsi, lKx0 );
    lBd = bd.build();
//       lBd = PDBdToJPsiKxBuilder::build( *currentEvSetup, lJPsi, lKx0 );
  }
  int iBd;
  int nBd = lBd.size();
  const string bdName = "svtBdJPsiKx";
  for ( iBd = 0; iBd < nBd; ++iBd ) {
    const BPHRecoCandidate* bd = lBd[iBd].get();
    if ( !bd->validVertex() ) continue;
    const vector<const Candidate*>& bdd = bd->daughFull();
    int id;
    int nd = bdd.size();
    map<const Track*,TransientTrack*> ttm;
    map<const Track*,float          > tmm;
//    map<const Track*,const Candidate*> rom;
//    map<const Track*,const Candidate*> rcm;
    const Vertex* vtp = 0;
    const Vertex* vtn = 0;
    for ( id = 0; id < nd; ++id ) {
      const Candidate* rc = bdd[id];
//      const Candidate* rc = bd->originalReco( bdd[id] );
      const Track* tkp = bd->getTrack( rc );
      ttm[tkp] = bd->getTransientTrack( rc );
      tmm[tkp] = bdd[id]->mass();
//      rcm[tkp] = rc;
//      rom[tkp] = bd->originalReco( rc );
      if ( vtp == 0 ) {
        p_iter = pcvMap.find( bd->originalReco( rc ) );
        if ( p_iter != p_iend ) vtp = p_iter->second;
      }
      if ( vtn == 0 ) vtn = nearestPV( tkp );
    }
    if ( vtp == 0 ) vtp = vtn;
    const Vertex& vtr = bd->vertex();
    GlobalVector  dir;
    Measurement1D d2d;
    Measurement1D d3d;
    if ( vtp != 0 ) vertexDir( *vtp, vtr, bd->composite(), dir, d2d, d3d );
    int svtIndex = addSecondaryVertex( PDVertexWrapper<Vertex>( vtr ),
                                       bd->mass(), ttm, tmm,//rcm, rom,
//                                       bd->p4().mass(), ttm, tmm,//rcm, rom,
                                       dir, d2d, d3d, bdName, -1 );
    const BPHRecoCandidate* jpsi = bd->getComp( "JPsi" ).get();
    subPart->push_back( rsvMap[jpsi] );
    subSVtx->push_back( svtIndex );
    subMass->push_back( jpsi->vertex().p4().M() );
    ++nCompVts;
    const BPHRecoCandidate* kx0 = bd->getComp( "Kx0" ).get();
    if ( rsvMap.find( kx0 ) == rsvMap.end() ) {
      const vector<const Candidate*>& pkd = kx0->daughters();
      int id;
      int nd = pkd.size();
      map<const Track*,TransientTrack*> ttm;
      map<const Track*,float          > tmm;
//      map<const Track*,const Candidate*> rcm;
//      map<const Track*,const Candidate*> rom;
      const Vertex* vtp = 0;
      const Vertex* vtn = 0;
      for ( id = 0; id < nd; ++id ) {
        const Candidate* rc = pkd[id];
//        const Candidate* rc = kx0->originalReco( pkd[id] );
        const Track* tkp = kx0->getTrack( rc );
        ttm[tkp] = kx0->getTransientTrack( rc );
        tmm[tkp] = pkd[id]->mass();
//        rcm[tkp] = rc;
//        rom[tkp] = kx0->originalReco( rc );
        if ( vtp == 0 ) {
          p_iter = pcvMap.find( kx0->originalReco( rc ) );
          if ( p_iter != p_iend ) vtp = p_iter->second;
        }
        if ( vtn == 0 ) vtn = nearestPV( tkp );
      }
      if ( vtp == 0 ) vtp = vtn;
      const Vertex& vtr = kx0->vertex();
      GlobalVector  dir;
      Measurement1D d2d;
      Measurement1D d3d;
      if ( vtp != 0 ) vertexDir( *vtp, vtr, kx0->composite(), dir, d2d, d3d );
      int svtIndex = addSecondaryVertex( PDVertexWrapper<Vertex>( vtr ),
                                         kx0->mass(), ttm, tmm,// rcm, rom,
//                                         kx0->composite().mass(), ttm, tmm,// rcm, rom,
                                         dir, d2d, d3d, sdName, -1 );
      rsvMap[kx0] = svtIndex;
    }
    subPart->push_back( rsvMap[kx0] );
    subSVtx->push_back( svtIndex );
    subMass->push_back( kx0->vertex().p4().M() );
    ++nCompVts;
  }

  if ( verbose ) cout << "fit bs" << endl;
  vector<BPHRecoConstCandPtr> lBs;
  if ( vRecoFlag[PDEnumString::svtBsJPsiPhi] ) {
    BPHBsToJPsiPhiBuilder bs( *currentEvSetup, lJPsi, lPhi );
    lBs = bs.build();
//       lBs = BPHBsToJPsiPhiBuilder::build( *currentEvSetup, lJPsi, lPhi );
  }
  int iBs;
  int nBs = lBs.size();
  const string bsName = "svtBsJPsiPhi";
  for ( iBs = 0; iBs < nBs; ++iBs ) {
    const BPHRecoCandidate* bs = lBs[iBs].get();
    if ( !bs->validVertex() ) continue;
    const vector<const Candidate*>& bsd = bs->daughFull();
    int id;
    int nd = bsd.size();
    map<const Track*,TransientTrack*> ttm;
    map<const Track*,float          > tmm;
//    map<const Track*,const Candidate*> rcm;
//    map<const Track*,const Candidate*> rom;
    const Vertex* vtp = 0;
    const Vertex* vtn = 0;
    for ( id = 0; id < nd; ++id ) {
      const Candidate* rc = bsd[id];
//      const Candidate* rc = bs->originalReco( bsd[id] );
      const Track* tkp = bs->getTrack( rc );
      ttm[tkp] = bs->getTransientTrack( rc );
      tmm[tkp] = bsd[id]->mass();
//      rcm[tkp] = rc;
//      rom[tkp] = bs->originalReco( rc );
      if ( vtp == 0 ) {
        p_iter = pcvMap.find( bs->originalReco( rc ) );
        if ( p_iter != p_iend ) vtp = p_iter->second;
      }
      if ( vtn == 0 ) vtn = nearestPV( tkp );
    }
    if ( vtp == 0 ) vtp = vtn;
    const Vertex& vtr = bs->vertex();
    GlobalVector  dir;
    Measurement1D d2d;
    Measurement1D d3d;
//    cout << "Bs mass: " << bs->composite().p4().mass() << ' '
//                        << bs->p4().mass() << ' '
//                        << bs->mass() << endl;
    if ( vtp != 0 ) vertexDir( *vtp, vtr, bs->composite(), dir, d2d, d3d );
    int svtIndex = addSecondaryVertex( PDVertexWrapper<Vertex>( vtr ),
                                       bs->mass(), ttm, tmm,//rcm, rom,
//                                       bs->p4().mass(), ttm, tmm,//rcm, rom,
                                       dir, d2d, d3d, bsName, -1 );
    const BPHRecoCandidate* jpsi = bs->getComp( "JPsi" ).get();
    subPart->push_back( rsvMap[jpsi] );
    subSVtx->push_back( svtIndex );
    subMass->push_back( jpsi->vertex().p4().M() );
    ++nCompVts;
    const BPHRecoCandidate* phi = bs->getComp( "Phi" ).get();
    if ( rsvMap.find( phi ) == rsvMap.end() ) {
      const vector<const Candidate*>& pkd = phi->daughters();
      int id;
      int nd = pkd.size();
      map<const Track*,TransientTrack*> ttm;
      map<const Track*,float          > tmm;
//      map<const Track*,const Candidate*> rcm;
//      map<const Track*,const Candidate*> rom;
      const Vertex* vtp = 0;
      const Vertex* vtn = 0;
      for ( id = 0; id < nd; ++id ) {
        const Candidate* rc = pkd[id];
//        const Candidate* rc = phi->originalReco( pkd[id] );
        const Track* tkp = phi->getTrack( rc );
//        cout << "Phi daughter " << id << '/' << nd << ' ' << rc << ' ' << tkp << endl; 
        ttm[tkp] = phi->getTransientTrack( rc );
        tmm[tkp] = pkd[id]->mass();
//        rcm[tkp] = rc;
//        rom[tkp] = phi->originalReco( rc );
        if ( vtp == 0 ) {
          p_iter = pcvMap.find( phi->originalReco( rc ) );
          if ( p_iter != p_iend ) vtp = p_iter->second;
        }
        if ( vtn == 0 ) vtn = nearestPV( tkp );
      }
      if ( vtp == 0 ) vtp = vtn;
      const Vertex& vtr = phi->vertex();
      GlobalVector  dir;
      Measurement1D d2d;
      Measurement1D d3d;
      if ( vtp != 0 ) vertexDir( *vtp, vtr, phi->composite(), dir, d2d, d3d );
      int svtIndex = addSecondaryVertex( PDVertexWrapper<Vertex>( vtr ),
                                         phi->mass(), ttm, tmm,//rcm, rom,
//                                         phi->composite().mass(), ttm, tmm,//rcm, rom,
                                         dir, d2d, d3d, ssName, -1 );
      rsvMap[phi] = svtIndex;
    }
    subPart->push_back( rsvMap[phi] );
    subSVtx->push_back( svtIndex );
    subMass->push_back( phi->vertex().p4().M() );
    ++nCompVts;
  }

  return;

}


void PDEDMToNtuple::fillPUWeight() {

  gt_PUInfo.get( currentEvBase, PUInfo );

  int nPT = 0;
  std::vector<PileupSummaryInfo>::const_iterator pu_iter = PUInfo->begin();
  std::vector<PileupSummaryInfo>::const_iterator pu_iend = PUInfo->end();
  while ( pu_iter != pu_iend ) {
    const PileupSummaryInfo& info = *pu_iter++;
    if ( info.getBunchCrossing() == 0 )
      nPT = info.getTrueNumInteractions(); // getPU_NumInteractions();
  }
  puWeight = LumiWeights->weight( nPT );

  return;

}


void PDEDMToNtuple::fillGenParticles() {

  gt_genParticles.get( currentEvBase, genParticles );
  bool vGen = genParticles.isValid();

  // store gen particles info

  int iObj;
  int nObj = ( vGen ? genParticles->size() : 0 );
  genId     ->resize( nObj );
  genStatus ->resize( nObj );
  genMother ->resize( nObj );
  genPartner->resize( nObj );
  genPt     ->resize( nObj );
  genEta    ->resize( nObj );
  genPhi    ->resize( nObj );
  genPx     ->resize( nObj );
  genPy     ->resize( nObj );
  genPz     ->resize( nObj );
  genE      ->resize( nObj );
  genCharge ->resize( nObj );
  genMass   ->resize( nObj );
  genVx     ->resize( nObj );
  genVy     ->resize( nObj );
  genVz     ->resize( nObj );
  if ( !vGen ) {
    cout << "invalid gen particles" << endl;
    return;
  }

  genMap.clear();
  nGenP = nObj;
//  cout << "********** " << nGenP << " gen part **********" << endl;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const GenParticle& gen = genParticles->at( iObj );
    genMap[&gen] = iObj;
//    genMap.insert( make_pair( &gen, iObj ) );

    genId     ->at( iObj ) = gen.pdgId();
    genStatus ->at( iObj ) = gen.status();
    genMother ->at( iObj ) = -1;
    genPartner->at( iObj ) = -1;
    genPt     ->at( iObj ) = gen.pt    ();
    genEta    ->at( iObj ) = gen.eta   ();
    genPhi    ->at( iObj ) = gen.phi   ();
    genPx     ->at( iObj ) = gen.px    ();
    genPy     ->at( iObj ) = gen.py    ();
    genPz     ->at( iObj ) = gen.pz    ();
    genE      ->at( iObj ) = gen.energy();
    genCharge ->at( iObj ) = gen.charge();
    genMass   ->at( iObj ) = gen.mass  ();
    genVx     ->at( iObj ) = gen.vx    ();
    genVy     ->at( iObj ) = gen.vy    ();
    genVz     ->at( iObj ) = gen.vz    ();

  }

  vector< vector<int> > motherTable;
  motherTable.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    const GenParticle& gen = genParticles->at( iObj );
    int iM;
    int nM = gen.numberOfMothers();
    vector<int>& mList = motherTable[iObj];
    mList.resize( nM, -1 );
    map<const Candidate*,int>::const_iterator iter;
    map<const Candidate*,int>::const_iterator iend = genMap.end();
    for ( iM = 0; iM < nM; ++iM ) {
      if ( ( iter = genMap.find( gen.mother( iM ) ) ) != iend )
           mList[iM] = iter->second;
    }
    sort( mList.begin(), mList.end() );
    if ( mList.size() ) genMother->at( iObj ) = mList[0];
  }

  map<int,int> motherMap;
  map< int, vector<int> > motherListMap;
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    vector<int>& mList = motherTable[iObj];
    if ( !mList.size() ) continue;
    int fm = mList[0];
    motherMap[fm] = iObj;
    motherListMap[fm].push_back( iObj );
  }

  map<int,int>::const_iterator m_iter = motherMap.begin();
  map<int,int>::const_iterator m_iend = motherMap.end();
  int iMot;
  while ( m_iter != m_iend ) {
    const pair<int,int>& entry = *m_iter++;
    iMot = entry.first;
    iObj = entry.second;
    const vector<int>& mList = motherTable[iObj];
    int next;
    int iM;
    int nM = mList.size();
    for ( iM = 1; iM < nM; ++iM ) {
      genPartner->at( iMot ) = next = mList[iM];
      iMot = next;
    }
  }

  return;

}


void PDEDMToNtuple::fillGenJets() {

  gt_genJets.get( currentEvBase, genJets );
  bool vGPJ = genJets.isValid();

  // store gen jets info

  int iObj;
  int nObj = ( vGPJ ? genJets->size() : 0 );
  gpjPt  ->resize( nObj );
  gpjEta ->resize( nObj );
  gpjPhi ->resize( nObj );
  gpjPx  ->resize( nObj );
  gpjPy  ->resize( nObj );
  gpjPz  ->resize( nObj );
  gpjE   ->resize( nObj );
  gpjNDau->resize( nObj );
  gpjReco->resize( nObj );
  if ( !vGPJ ) {
    cout << "invalid gen jets" << endl;
    return;
  }

  nGenJets = nObj;
  for ( iObj = 0; iObj < nObj; ++iObj ) {

    const GenJet& gpj = genJets->at( iObj );

    gpjPt  ->at( iObj ) = gpj.pt    ();
    gpjEta ->at( iObj ) = gpj.eta   ();
    gpjPhi ->at( iObj ) = gpj.phi   ();
    gpjPx  ->at( iObj ) = gpj.px    ();
    gpjPy  ->at( iObj ) = gpj.py    ();
    gpjPz  ->at( iObj ) = gpj.pz    ();
    gpjE   ->at( iObj ) = gpj.energy();
    gpjNDau->at( iObj ) = gpj.numberOfDaughters();

    map<const GenJet*,int>::const_iterator j_iter;
    gpjReco->at( iObj ) = ( ( j_iter = gpjMap.find( &gpj ) ) != gpjMap.end() ?
			      j_iter->second : -1 );

/*
    const vector<const GenParticle*>& jGC = gpj.getGenConstituents();
    map<const Candidate*,int>::const_iterator g_iter;
    map<const Candidate*,int>::const_iterator g_iend = genMap.end();
    int iGC;
    int nGC = jGC.size();
    for ( iGC = 0; iGC < nGC; ++iGC ) {
      if ( ( g_iter = genMap.find( jGC.at( iGC ) ) ) != g_iend )
           genJet->at( g_iter->second ) = iObj;
    }
*/
  }

  return;

}


void PDEDMToNtuple::fillUserInfo( int obj, int index,
                                  int info, number value ) {
  ++nUserInfo;
  useObjType  ->push_back( obj );
  useObjIndex ->push_back( index );
  useInfoType ->push_back( info );
  useInfoValue->push_back( value );
  return;
}


void PDEDMToNtuple::fillSVTInfoMap() {

  // "new" secondary vertex tag

  if ( verbose ) cout << "fillSVTInfoMap" << endl;
  gt_sVertices.get( currentEvBase, sVertices );
  bool vSvts = sVertices.isValid();

  if ( !vSvts ) {
    cout << "invalid sVertices" << endl;
    return;
  }
  int iObj;
  int nObj = sVertices->size();

  map<const Jet  *,int>::const_iterator j_iter;
  map<const Jet  *,int>::const_iterator j_iend = jetMap.end();

  for ( iObj = 0; iObj < nObj; ++iObj ) {
    const svtInfo& secVtxTagInfo = sVertices->at( iObj );
    const Jet* jet = dynamic_cast<const Jet*>( secVtxTagInfo.jet().get() );
    if ( ( j_iter = jetMap.find( jet ) ) == j_iend ) continue;
    vector<VtxInfo>& vtxList = svtMap[jet];
    int nOld = vtxList.size();
    int iVtx;
    int nVtx = secVtxTagInfo.nVertices();
    vtxList.resize( nOld + nVtx );
    for ( iVtx = 0; iVtx < nVtx; ++iVtx ) {
      VtxInfo& info = vtxList[nOld + iVtx];
      const sVtx& vtx = secVtxTagInfo.secondaryVertex( iVtx );
      info.jetId = j_iter->second;
      info.vtx.set( vtx );
      info.dir = &secVtxTagInfo.flightDirection( iVtx );
      info.d2d =  secVtxTagInfo.flightDistance(  iVtx, true  );
      info.d3d =  secVtxTagInfo.flightDistance(  iVtx, false );
      if ( fill_svtt )
           PDVertexWrapBase::fillComponent( secVtxTagInfo, iVtx,
                                            info.compList );
    }
  }

  return;

}


void PDEDMToNtuple::fillSVTIJetMap() {

  // "old" secondary vertex tag

  if ( verbose ) cout << "fillSVTIJetMap" << endl;
  int iObj;
  int nObj = ( jets.isValid() ? jets->size() : 0 );

  map<const Jet  *,int>::const_iterator j_iter;
  map<const Jet  *,int>::const_iterator j_iend = jetMap.end();

  for ( iObj = 0; iObj < nObj; ++iObj ) {
    const Jet* jet = &( jets->at( iObj ) );
    if ( ( j_iter = jetMap.find( jet ) ) == j_iend ) continue;
    const reco::SecondaryVertexTagInfo& secVtxTagInfo =
      *( jet->tagInfoSecondaryVertex( getUserParameter( "labelSVTagInfo" ) ) );
    vector<VtxInfo>& vtxList = svtMap[jet];
    int nOld = vtxList.size();
    int iVtx;
    int nVtx = secVtxTagInfo.nVertices();
    vtxList.resize( nOld + nVtx );
    for ( iVtx = 0; iVtx < nVtx; ++iVtx ) {
      VtxInfo& info = vtxList[nOld + iVtx];
      const reco::Vertex& vtx = secVtxTagInfo.secondaryVertex( iVtx );
      info.jetId = j_iter->second;
      info.vtx.set( vtx );
      info.dir = &secVtxTagInfo.flightDirection( iVtx );
      info.d2d =  secVtxTagInfo.flightDistance(  iVtx, true  );
      info.d3d =  secVtxTagInfo.flightDistance(  iVtx, false );
      if ( fill_svtt ) {
        map<const Track*,
            const Candidate*>::const_iterator p_iter;
        map<const Track*,
            const Candidate*>::const_iterator p_iend = tpfMap.end();
        map<const Track*,
            const Muon     *>::const_iterator m_iter;
        map<const Track*,
            const Muon     *>::const_iterator m_iend = tmuMap.end();
        Vertex::trackRef_iterator t_iter = vtx.tracks_begin();
        Vertex::trackRef_iterator t_iend = vtx.tracks_end();
        vector<VtxComponent>& compList = info.compList;
        int itk = 0;
        int ntk = distance( t_iter, t_iend );
        compList.resize( ntk );
        for ( itk = 0; itk < ntk; ++itk ) {
          VtxComponent& vc = compList[itk];
          const Track* tkp = &(**t_iter++);
          p_iter = tpfMap.find( tkp );
          m_iter = tmuMap.find( tkp );
          const Candidate* pcp = ( p_iter == p_iend ? 0 : p_iter->second );
          if ( pcp == 0 )  pcp = ( m_iter == m_iend ? 0 : m_iter->second );
          vc.cand = pcp;
          vc.track = tkp;
        }
      }
    }
  }

  return;

}


void PDEDMToNtuple::fillSaved() {

  savedTrk.clear();
  savedPFC.clear();
  savedVtx.clear();
  savedJet.clear();

  int iMu;
  for ( iMu = 0; iMu < nMuons    ; ++iMu ) {
    int j = muoTrk ->at( iMu );
    while ( j >= 0 ) {
      savedTrk.insert( j );
      savedPFC.insert( trkPFC->at( j ) );
      j = trkNext->at( j );
    }
  }

  int iEl;
  for ( iEl = 0; iEl < nElectrons; ++iEl ) {
    int j = eleTrk ->at( iEl );
    while ( j >= 0 ) {
      savedTrk.insert( j );
      savedPFC.insert( trkPFC->at( j ) );
      j = trkNext->at( j );
    }
  }

  int iSV;
  for ( iSV = 0; iSV < nSVertices; ++iSV ) {
    const std::vector<int>& tks = tracksFromSV( iSV );
    int iTk;
    int nTk = tks.size();
    for ( iTk = 0; iTk < nTk; ++iTk ) {
      int j = tks[iTk];
      while ( j >= 0 ) {
        savedTrk.insert( j );
        savedPFC.insert( trkPFC->at( j ) );
	j = trkNext->at( j );
      }
    }
  }

  set<int>::const_iterator t_iter = savedTrk.begin();
  set<int>::const_iterator t_iend = savedTrk.end();
  while ( t_iter != t_iend ) {
    int iTk = *t_iter++;
    savedVtx.insert( trkPVtx->at( iTk ) );
    savedJet.insert( trkJet ->at( iTk ) );
  }

  set<int>::const_iterator v_iter = savedVtx.begin();
  set<int>::const_iterator v_iend = savedVtx.end();
  while ( v_iter != v_iend ) {
    int iPV = *v_iter++;
    const std::vector<int>& tks = tracksFromPV( iPV );
    int iTk;
    int nTk = tks.size();
    for ( iTk = 0; iTk < nTk; ++iTk ) {
      int j = tks[iTk];
      while ( j >= 0 ) {
        savedTrk.insert( j );
        savedPFC.insert( trkPFC->at( j ) );
	j = trkNext->at( j );
      }
    }
  }

  set<int>::const_iterator j_iter = savedJet.begin();
  set<int>::const_iterator j_iend = savedJet.end();
  while ( j_iter != j_iend ) {
    int iJet = *j_iter++;
    const std::vector<int>& tks = tracksFromJet( iJet );
    int iTk;
    int nTk = tks.size();
    for ( iTk = 0; iTk < nTk; ++iTk ) {
      int j = tks[iTk];
      while ( j >= 0 ) {
        savedTrk.insert( j );
        savedPFC.insert( trkPFC->at( j ) );
	j = trkNext->at( j );
      }
    }
    const std::vector<int>& pfs = pfCandFromJet( iJet );
    int iPF;
    int nPF = pfs.size();
    for ( iPF = 0; iPF < nPF; ++iPF ) {
      int j = pfs[iPF];
      savedTrk.insert( pfcTrk->at( j ) );
      savedPFC.insert( j );
    }
  }

  return;

}


void PDEDMToNtuple::cleanTracks() {

  int i;
/*
  set<int> selTrack;
  for ( i = 0; i < nMuons    ; ++i ) selTrack.insert( muoTrk ->at( i ) );
  for ( i = 0; i < nElectrons; ++i ) selTrack.insert( eleTrk ->at( i ) );
//  for ( i = 0; i < nPF       ; ++i ) selTrack.insert( pfcTrk ->at( i ) );
  for ( i = 0; i < nTracks   ; ++i ) selTrack.insert( trkNext->at( i ) );
  for ( i = 0; i < nTkIPs    ; ++i ) selTrack.insert( tipTrk ->at( i ) );
  set<int>::const_iterator t_iter = selTrack.begin();
  set<int>::const_iterator t_iend = selTrack.end();
*/
  map<int,int> mapTrack;
  for ( i = -1; i < nTracks   ; ++i ) mapTrack[i] = -1;
  set<int>::const_iterator t_iter = savedTrk.begin();
  set<int>::const_iterator t_iend = savedTrk.end();
  int n = 0;
  while ( t_iter != t_iend ) {
    int i = *t_iter++;
    if ( i < 0 ) continue;
    mapTrack[i] = n;
    if ( use_tracks_sphe ) {
    shiftVector( trkPt          , n, i );
    shiftVector( trkEta         , n, i );
    shiftVector( trkPhi         , n, i );
    }
    if ( use_tracks_cart ) {
    shiftVector( trkPx          , n, i );
    shiftVector( trkPy          , n, i );
    shiftVector( trkPz          , n, i );
    }
    shiftVector( trkCharge      , n, i );
    shiftVector( trkType        , n, i );
    shiftVector( trkNext        , n, i );
    shiftVector( trkPFC         , n, i );
    shiftVector( trkJet         , n, i );
    shiftVector( trkPVtx        , n, i );
    shiftVector( trkQuality     , n, i );
    shiftVector( trkHitPattern  , n, i );
    shiftVector( trkLayPattern  , n, i );
    shiftVector( trkNormChi2    , n, i );
    shiftVector( trkDxy         , n, i );
    shiftVector( trkDz          , n, i );
    shiftVector( trkExy         , n, i );
    shiftVector( trkEz          , n, i );
    ++n;
  }
  for ( i = 0; i < nMuons    ; ++i ) relink( mapTrack, muoTrk ->at( i ) );
  for ( i = 0; i < nElectrons; ++i ) relink( mapTrack, eleTrk ->at( i ) );
  for ( i = 0; i < nPF       ; ++i ) relink( mapTrack, pfcTrk ->at( i ) );
  for ( i = 0; i < nTracks   ; ++i ) relink( mapTrack, trkNext->at( i ) );
  for ( i = 0; i < nTkIPs    ; ++i ) relink( mapTrack, tipTrk ->at( i ) );
  if ( use_tracks_sphe ) {
  nTracks = n + 1;
  trkPt          ->resize( nTracks );
  trkEta         ->resize( nTracks );
  trkPhi         ->resize( nTracks );
  }
  if ( use_tracks_cart ) {
  trkPx          ->resize( nTracks );
  trkPy          ->resize( nTracks );
  trkPz          ->resize( nTracks );
  }
  trkCharge      ->resize( nTracks );
  trkType        ->resize( nTracks );
  trkNext        ->resize( nTracks );
  trkPFC         ->resize( nTracks );
  trkJet         ->resize( nTracks );
  trkPVtx        ->resize( nTracks );
  trkQuality     ->resize( nTracks );
  trkHitPattern  ->resize( nTracks );
  trkLayPattern  ->resize( nTracks );
  trkNormChi2    ->resize( nTracks );
  trkDxy         ->resize( nTracks );
  trkDz          ->resize( nTracks );
  trkExy         ->resize( nTracks );
  trkEz          ->resize( nTracks );

  return;

}


const Vertex* PDEDMToNtuple::nearestPV( const Track* tkp ) {
  const Vertex* pvt = 0;
  float dmax = 999999.0;
  int iPVt;
  int nPVt = vtxList.size();
  for ( iPVt = 0; iPVt < nPVt; ++iPVt ) {
    const Vertex* vtp = vtxList[iPVt];
    const Vertex::Point& pos = vtp->position();
    float dist = fabs( tkp->dz( pos ) );
    if ( dist < dmax ) {
      dmax = dist;
      pvt = vtp;
    }
  }
  return pvt;
}


void PDEDMToNtuple::vertexDir( const Vertex& pvtx,
                               const Vertex& svtx,
                               const pat::CompositeCandidate& cand,
                               GlobalVector & dir,
                               Measurement1D& d2d,
                               Measurement1D& d3d ) {
  TVector3 disp2( svtx.x() - pvtx.x(),
                  svtx.y() - pvtx.y(),
                  0 );
  TVector3 disp3( svtx.x() - pvtx.x(),
                  svtx.y() - pvtx.y(),
                  svtx.z() - pvtx.z() );
  dir = GlobalVector( disp3.x(), disp3.y(), disp3.z() );
  TVector3 cmom2( cand.px(), cand.py(), 0 );
  TVector3 cmom3( cand.px(), cand.py(), cand.pz() );
  float cosAlpha2 = disp2.Dot( cmom2 ) / ( disp2.Perp() * cmom2.Perp() );
  float cosAlpha3 = disp3.Dot( cmom3 ) / ( disp3.Perp() * cmom3.Perp() );
  AlgebraicVector3 vmom2( cand.px(), cand.py(), 0 );
  AlgebraicVector3 vmom3( cand.px(), cand.py(), cand.pz() );

  VertexDistanceXY vdistXY;
  VertexDistance3D vdist3D;
  Measurement1D distXY = vdistXY.distance( svtx, pvtx );
  Measurement1D dist3D = vdist3D.distance( svtx, pvtx );
  float mass = cand.mass();
  double ctauPV2 = distXY.value() * cosAlpha2 * mass / cmom2.Perp();
  double ctauPV3 = dist3D.value() * cosAlpha3 * mass / cmom3.Perp();
  GlobalError sve = svtx.error();
  GlobalError pve = pvtx.error();
  AlgebraicSymMatrix33 dve = sve.matrix() + pve.matrix();
  double ctauErrPV2 = sqrt( ROOT::Math::Similarity( vmom2, dve ) ) * mass /
                            cmom2.Perp2();
  double ctauErrPV3 = sqrt( ROOT::Math::Similarity( vmom3, dve ) ) * mass /
                            cmom3.Perp2();
  d2d = Measurement1D( ctauPV2, ctauErrPV2 );
//  d2d = Measurement1D( ctauPV2, ctauPV2 / ctauErrPV2 );
  d3d = Measurement1D( ctauPV3, ctauErrPV3 );
//  d3d = Measurement1D( ctauPV3, ctauPV3 / ctauErrPV3 );

/*
  VertexDistanceXY vdistXY;
  Measurement1D distXY = vdistXY.distance( svtx, pvtx );
  float mass = cand.mass();
  double ctauPV2 = distXY.value() * cosAlpha2 * mass / cmom2.Perp();
  GlobalError sve2 = svtx.error();
  GlobalError pve2 = pvtx.error();
  AlgebraicSymMatrix33 vXYe2 = sve2.matrix() + pve2.matrix();
  double ctauErrPV2 = sqrt( ROOT::Math::Similarity( vmom2, vXYe2 ) ) * mass /
                            cmom2.Perp2();
  d2d = Measurement1D( ctauPV2, ctauPV2 / ctauErrPV2 );

  VertexDistance3D vdist3D;
  Measurement1D dist3D = vdist3D.distance( svtx, pvtx );
  double ctauPV3 = dist3D.value() * cosAlpha3 * mass / cmom3.Perp();
  GlobalError sve3 = svtx.error();
  GlobalError pve3 = pvtx.error();
  AlgebraicSymMatrix33 vXYe3 = sve3.matrix() + pve3.matrix();
  double ctauErrPV3 = sqrt( ROOT::Math::Similarity( vmom3, vXYe3 ) ) * mass /
                            cmom3.Perp2();
  d3d = Measurement1D( ctauPV3, ctauPV3 / ctauErrPV3 );
*/
  return;
}


int PDEDMToNtuple::addSecondaryVertex( const PDVertexWrapBase& vtx,
                                       double vMass,
                                       const map<const    Track*,
                                                 TransientTrack*>& ttm,
                                       const map<const    Track*,
                                                 float          >& tmm,
//                                       const map<const    Track *,
//                                                 TransientTrack *>& ttm,
//                                       const map<const    Track *,
//                                                 const Candidate*>& rcm,
//                                       const map<const    Track *,
//                                                 const Candidate*>& rom,
                                       const  GlobalVector& dir,
                                       const Measurement1D& d2d,
                                       const Measurement1D& d3d,
                                       const string& type, int jetId ) {
  svtX         ->push_back( vtx.position().x() );
  svtY         ->push_back( vtx.position().y() );
  svtZ         ->push_back( vtx.position().z() );
  svtSxx       ->push_back( vtx.covariance( 0, 0 ) );
  svtSyy       ->push_back( vtx.covariance( 1, 1 ) );
  svtSzz       ->push_back( vtx.covariance( 2, 2 ) );
  svtSxy       ->push_back( vtx.covariance( 0, 1 ) );
  svtSxz       ->push_back( vtx.covariance( 0, 2 ) );
  svtSyz       ->push_back( vtx.covariance( 1, 2 ) );
  svtDirX      ->push_back( dir.x() );
  svtDirY      ->push_back( dir.y() );
  svtDirZ      ->push_back( dir.z() );
  svtType      ->push_back( PDEnumString::findVertexType( type ) );
  svtNTracks   ->push_back( vtx.nTracks() );
  svtChi2      ->push_back( vtx.chi2() );
  svtNDOF      ->push_back( lround( vtx.ndof() ) );
//  svtNormChi2  ->push_back( vtx.normalizedChi2() );
  if ( vMass < 0.0 ) {
    try                        { vMass = vtx.p4().M(); }
    catch ( edm::Exception e ) { vMass = -1.0; }
  }
  svtMass      ->push_back( vMass );
  svtDist2D    ->push_back( d2d.value() );
  svtSigma2D   ->push_back( d2d.error() );
//  svtSign2D    ->push_back( d2d.significance() );
  svtDist3D    ->push_back( d3d.value() );
  svtSigma3D   ->push_back( d3d.error() );
//  svtSign3D    ->push_back( d3d.significance() );
  svtJet       ->push_back( jetId );
  svtBadQuality->push_back( vtx.isValid() ? 0 : ( vtx.isFake() ? 1 : 2 ) );

  map<const Track*,int>::const_iterator t_iter;// = trkMap.begin();
  map<const Track*,int>::const_iterator t_iend = trkMap.end();
//  ptk_iter p_iter;// = tpfMap.begin();
//  ptk_iter p_iend = ptkMap.end();
  try {
    map<const Track*,TransientTrack*>::const_iterator m_iter = ttm.begin();
    map<const Track*,TransientTrack*>::const_iterator m_iend = ttm.end();
    map<const Track*,float          >::const_iterator h_iter;
    map<const Track*,float          >::const_iterator h_iend = tmm.end();
//    map<const Track*,const Candidate*>::const_iterator h_iter;
//    map<const Track*,const Candidate*>::const_iterator h_iend = rcm.end();
//    map<const Track*,const Candidate*>::const_iterator o_iter;
//    map<const Track*,const Candidate*>::const_iterator o_iend = rom.end();
    while ( m_iter != m_iend ) {
      const pair<const Track*,TransientTrack*>& entry = *m_iter++;
      const          Track* tkp = entry.first;
      const TransientTrack* ttp = entry.second;
      int trkIndex = ( ( t_iter = trkMap.find( tkp ) ) != t_iend ?
                         t_iter->second : -1 );
//      if ( trkIndex < 0 ) {
//        const Candidate* ocp = ( ( o_iter = rom.find( tkp ) ) != o_iend ?
//                                   o_iter->second : 0 );
//        cout << "original cand: " << ocp << endl;
////        pair<ptk_iter,ptk_iter> pp = ptkMap.equal_range( ocp );
//        const Track* tks = ( ( p_iter = ptkMap.equal_range( ocp ).first )
//                            != p_iend ?
//                               p_iter->second : 0 );
//        trkIndex = ( ( t_iter = trkMap.find( tks ) ) != t_iend ?
//                       t_iter->second : -1 );
////        int pfcIndex = ( ( p_iter = pfcMap.find( ocp ) ) != p_iend ?
////                           p_iter->second : -1 );
////        cout << ocp << ' ' << pfcIndex << endl;
////        trkIndex = ( pfcIndex >= 0 ? pfcTrk->at( pfcIndex ) : -2 );
//      }
//      cout << "trkIndex: " << tkp << ' ' << trkIndex << endl;
      float   mass = ( ( h_iter =    tmm.find( tkp ) ) != h_iend ?
                         h_iter->second : -1 );
//      float   mass = ( ( h_iter =    rcm.find( tkp ) ) != h_iend ?
//                         h_iter->second->mass() : -1 );
      int tipIndex = addTrackIP( trkIndex, *tkp, mass, nSVertices, vtx );
      if ( ttp != 0 ) addTrackVtxP( tipIndex, ttp, vtx );
    }
  }
  catch ( edm::Exception e ) {
  }

  return nSVertices++;
}


int PDEDMToNtuple::addTrackIP( int trkIndex, const Track & trk, float mass,
                               int vtxIndex, const PDVertexWrapBase& vtx ) {
  tipTrk ->push_back( trkIndex );
  tipSVtx->push_back( vtxIndex );
  tipMass->push_back( mass );
  const Vertex::Point& pos = vtx.position();
  tipDxy ->push_back( trk.dxy( pos ) );
  tipDz  ->push_back( trk.dz ( pos ) );
  tipExy ->push_back( trk.dxyError() );
  tipEz  ->push_back( trk.dzError()  );
  return nTkIPs++;
}


int PDEDMToNtuple::addTrackVtxP( int tipIndex, const TransientTrack* trk,
                                               const PDVertexWrapBase& vtx ) {
  tvpTip->push_back( tipIndex );
  const Vertex::Point& vp = vtx.position();
  GlobalPoint gp( vp.X(), vp.Y(), vp.Z() );
  TrajectoryStateClosestToPoint tscp = trk->trajectoryStateClosestToPoint( gp );
  GlobalVector gv = tscp.momentum();
  tvpPx ->push_back( gv.x() );
  tvpPy ->push_back( gv.y() );
  tvpPz ->push_back( gv.z() );
  return nVtxPs++;
}


void PDEDMToNtuple::linkMTracks() {
  map<const Muon     *,int>::const_iterator m_iter;
  map<const Muon     *,int>::const_iterator m_iend = muoMap.end();
  map<const Candidate*,int>::const_iterator p_iter;
  map<const Candidate*,int>::const_iterator p_iend = pfcMap.end();
  map<const Track    *,int>::const_iterator t_iter;
  map<const Track    *,int>::const_iterator t_iend = trkMap.end();
  multimap<const Muon*,const Track*>::const_iterator l_iter = mtkMap.begin();
  multimap<const Muon*,const Track*>::const_iterator l_iend = mtkMap.end();
  int iMuon;
  int iTrk;
  int iSav = -1;
  const Muon* msav = 0;
  while ( l_iter != l_iend ) {
    const multimap<const Muon*,const Track*>::value_type& l_entry = *l_iter++;
    const Muon * muon = l_entry.first;
    const Track* trk  = l_entry.second;
    if ( ( m_iter = muoMap.find( muon ) ) == m_iend ) continue;
    iMuon = m_iter->second;
    if ( ( t_iter = trkMap.find( trk  ) ) == t_iend ) continue;
    iTrk  = t_iter->second;
    if ( muon != msav ) iSav = -1;
    if ( iSav < 0 ) muoTrk->at( iMuon ) = iTrk;
    else            trkNext->at( iSav ) = iTrk;
    int iPFC = -1;
    int nms = muon->numberOfSourceCandidatePtrs();
    int ims = 0;
    while ( ( iPFC < 0 ) && ( ims < nms ) ) {
      const Candidate* rcp = muon->sourceCandidatePtr( ims++ ).get();
      if ( ( p_iter = pfcMap.find( rcp ) ) == p_iend ) continue;
      iPFC = p_iter->second;
    }
    if ( iPFC >= 0 ) trkPFC->at( iTrk ) = iPFC;
    iSav = iTrk;
    msav = muon;
  }
  if ( !read_pvts || !pVertices.isValid() ) return;
  map<const Track*,int>::const_iterator v_iter = tkvMap.begin();
  map<const Track*,int>::const_iterator v_iend = tkvMap.end();
  map<const Track*,const Muon*>::const_iterator n_iter;
  map<const Track*,const Muon*>::const_iterator n_iend = tmuMap.end();
  map<const Muon*,int> mvtMap;
  while ( v_iter != v_iend ) {
    const map<const Track*,int>::value_type& entry = *v_iter++;
    const Track* trk = entry.first;
    int iPVT         = entry.second;
    if ( ( n_iter = tmuMap.find( trk  ) ) == n_iend ) continue;
    const Muon* muon = n_iter->second;
    mvtMap[muon] = iPVT;
  }
  m_iter = muoMap.begin();
  map<const Muon*,int>::const_iterator w_iter;
  map<const Muon*,int>::const_iterator w_iend = mvtMap.end();
  while ( m_iter != m_iend ) {
    const pair<const Muon*,int>& entry = *m_iter++;
    const Muon* muon = entry.first;
    int iMuon        = entry.second;
    int iPVT         = 0;
    if ( ( w_iter = mvtMap.find( muon ) ) != w_iend ) iPVT = w_iter->second;
    const Vertex& vtx = pVertices->at( iPVT );
    if ( PDMuonWrapper:: isTightMuon( *muon, vtx ) )
         muoType->at( iMuon ) |= PDEnumString::tight;
    if ( PDMuonWrapper::  isSoftMuon( *muon, vtx ) )
         muoType->at( iMuon ) |= PDEnumString::soft;
    if ( PDMuonWrapper::isHighPtMuon( *muon, vtx ) )
         muoType->at( iMuon ) |= PDEnumString::highPt;
  }
  return;

}


void PDEDMToNtuple::linkETracks() {

  map<const Track*,int>::const_iterator t_iter;
  map<const Track*,int>::const_iterator t_iend = trkMap.end();
  map<const Electron*,int>::const_iterator m_iter = eleMap.begin();
  map<const Electron*,int>::const_iterator m_iend = eleMap.end();
  map<const Electron*,const Track*>::const_iterator l_iter;
  map<const Electron*,const Track*>::const_iterator l_iend = etkMap.end();
  while ( m_iter != m_iend ) {
    const pair<const Electron*,int>& entry = *m_iter++;
    const Electron* electron = entry.first;
    int iElectron            = entry.second;
    if ( ( l_iter = etkMap.find( electron ) ) != l_iend ) {
      const Track* trk = l_iter->second;
      if ( ( t_iter = trkMap.find( trk ) ) != t_iend )
           eleTrk->at( iElectron ) = t_iter->second;
    }
  }

  return;

}


void PDEDMToNtuple::linkPTracks() {
  map<const Candidate*,int>::const_iterator p_iter;
  map<const Candidate*,int>::const_iterator p_iend = pfcMap.end();
  map<const Track    *,int>::const_iterator t_iter;
  map<const Track    *,int>::const_iterator t_iend = trkMap.end();
  multimap<const Candidate*,
           const Track*>::const_iterator l_iter = ptkMap.begin();
  multimap<const Candidate*,
           const Track*>::const_iterator l_iend = ptkMap.end();
  int iPFC;
  int iTrk;
  int iSav = -1;
  const Candidate* pfs = 0;
  while ( l_iter != l_iend ) {
    const multimap<const Candidate*,
                   const Track*>::value_type& l_entry = *l_iter++;
    const Candidate* pfc = l_entry.first;
    const Track    * trk = l_entry.second;
    if ( ( p_iter = pfcMap.find( pfc ) ) == p_iend ) continue;
    iPFC = p_iter->second;
    if ( ( t_iter = trkMap.find( trk ) ) == t_iend ) continue;
    iTrk = t_iter->second;
    if ( pfc != pfs ) iSav = -1;
    if ( iSav < 0 ) pfcTrk->at( iPFC ) = iTrk;
    else            trkNext->at( lastTrack( iSav ) ) = iTrk;
    trkPFC->at( iTrk ) = iPFC;
    trkJet->at( iTrk ) = pfcJet->at( iPFC );
    iSav = iTrk;
    pfs = pfc;
  }
  return;
}


int PDEDMToNtuple::nearestHLT( PDEnumString::trigObject type,
                               double pt, double eta, double phi ) {
  int iHLT;
  int jHLT = -1;
  float dRmin = 1.0e+37;
  float dRcur;
  for ( iHLT = 0; iHLT < nHLTObjects; ++iHLT ) {
    if ( hltObjType->at( iHLT ) != type )
         continue;
    double diffEta =       eta - hltEta->at( iHLT );
    double diffPhi = fabs( phi - hltPhi->at( iHLT ) );
    while ( diffPhi > M_PI ) diffPhi -= ( 2.0 * M_PI );
    dRcur = sqrt( ( diffEta * diffEta ) + ( diffPhi * diffPhi ) );
    if ( dRcur < dRmin ) {
      jHLT = iHLT;
      dRmin = dRcur;
    }
  }
  if ( dRmin < dRmatchHLT ) {
    if ( type == PDEnumString::hltJet ) return jHLT;
    double diffPt  = ( pt - hltPt->at( jHLT ) ) /
                     ( pt + hltPt->at( jHLT ) );
    if ( fabs( diffPt ) < dPmatchHLT ) return jHLT;
  }
  return -1;
}


bool PDEDMToNtuple::wildMatch( const string& name, string model ) {
  if ( ( model == "*" ) || ( model == "*" ) ) return true;
  int mLength = model.length();
  int nLength =  name.length();
  const char* mtemp = model.c_str();
  bool wildHead = ( mtemp[0]           == '*' );
  bool wildTail = ( mtemp[mLength - 1] == '*' );
  if ( wildHead ) model = model.substr( 1, --mLength );
  if ( wildTail ) model = model.substr( 0, --mLength );
  string::size_type mpos = name.find( model, 0 );
  if ( mpos == string::npos ) return false;
  if ( wildHead ) {
    mLength += mpos;
    mpos = 0;
  }
  else {
    if ( mpos ) return false;
  }
  if ( wildTail ) return true;
  return ( nLength == mLength );
}


void PDEDMToNtuple::setTrkType( const Track* trk, int type,
                                vector<const reco::Track *   >& tList,
                                map   <const reco::Track*,int>& tType ){
  tList.push_back( trk );
  if ( tType.find( trk ) == tType.end() ) tType[trk]  = type;
  else                                    tType[trk] |= type;
  return;
}


int PDEDMToNtuple::lastTrack( int i ) {
  int n;
  while ( ( n = trkNext->at( i ) ) >= 0 ) i = n;
  return i;
}
