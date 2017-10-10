#include "PDAnalysis/Ntu/interface/PDEnumString.h"

#include <iostream>

//using namespace std;

std::string PDEnumString::defaultString;
std::map<int,std::string> PDEnumString::trigPathMapIS;
std::map<std::string,int> PDEnumString::trigPathMapSI;
std::map<int,std::string> PDEnumString::trigObjectMapIS;
std::map<std::string,int> PDEnumString::trigObjectMapSI;
std::map<int,std::string> PDEnumString::recoObjectMapIS;
std::map<std::string,int> PDEnumString::recoObjectMapSI;
std::map<int,std::string> PDEnumString::recoUITypeMapIS;
std::map<std::string,int> PDEnumString::recoUITypeMapSI;
std::map<int,std::string> PDEnumString::vertexTypeMapIS;
std::map<std::string,int> PDEnumString::vertexTypeMapSI;
std::map<int,std::string> PDEnumString:: trackTypeMapIS;
std::map<std::string,int> PDEnumString:: trackTypeMapSI;
std::map<int,std::string> PDEnumString::  muonTypeMapIS;
std::map<std::string,int> PDEnumString::  muonTypeMapSI;

static PDEnumString pdEnumString;

#define mP( NAME ) std::make_pair( #NAME, NAME )

PDEnumString::PDEnumString() {

  defaultString = "";

  trigPathMapSI.clear();
//  trigPathMapSI.insert(
//      mP( dummy ) );
  trigPathMapSI.insert(
      mP( HLT_Mu10_CentralPFJet30_BTagCSV_p13_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu17_Mu8_DZ_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu17_Mu8_SameSign_DZ_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu17_Mu8_SameSign_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu17_Mu8_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu17_TkMu8_DZ_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu17_TrkIsoVVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu17_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu20_Mu10_DZ_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu20_Mu10_SameSign_DZ_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu20_Mu10_SameSign_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu20_Mu10_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu27_TkMu8_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu30_TkMu11_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu3_PFJet40_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu40_TkMu11_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu8_TrkIsoVVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu8_v ) );
  trigPathMapSI.insert(
      mP( HLT_TripleMu_12_10_5_v ) );
  trigPathMapSI.insert(
      mP( HLT_TripleMu_5_3_3_v ) );
  trigPathMapSI.insert(
      mP( HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v ) );
  trigPathMapSI.insert(
      mP( HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleMu18NoFiltersNoVtx_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleMu23NoFiltersNoVtxDisplaced_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleMu28NoFiltersNoVtxDisplaced_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleMu33NoFiltersNoVtx_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleMu38NoFiltersNoVtx_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleMu8_Mass8_PFHT250_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleMu8_Mass8_PFHT300_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleMu4_JpsiTrkTrk_Displaced_v ) );
  trigPathMapSI.insert(
      mP( HLT_L2DoubleMu23_NoVertex_v ) );
  trigPathMapSI.insert(
      mP( HLT_L2DoubleMu28_NoVertex_2Cha_Angle2p5_Mass10_v ) );
  trigPathMapSI.insert(
      mP( HLT_L2DoubleMu38_NoVertex_2Cha_Angle2p5_Mass10_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleMu4_LowMassNonResonantTrk_Displaced_v ) );
  trigPathMapSI.insert(
      mP( HLT_Dimuon0_Phi_Barrel_v ) );
  trigPathMapSI.insert(
      mP( HLT_Dimuon0_Jpsi3p5_Muon2_v ) );
  trigPathMapSI.insert(
      mP( HLT_Dimuon0_Upsilon_Muon_v ) );
  trigPathMapSI.insert(
      mP( HLT_Dimuon13_Upsilon_v ) );
  trigPathMapSI.insert(
      mP( HLT_Dimuon8_Upsilon_Barrel_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu16_TkMu0_dEta18_Onia_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu16_TkMu0_dEta18_Phi_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu25_TkMu0_dEta18_Onia_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu7p5_L2Mu2_Upsilon_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu7p5_Track2_Upsilon_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu7p5_Track3p5_Upsilon_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu7p5_Track7_Upsilon_v ) );
  trigPathMapSI.insert(
      mP( HLT_QuadMuon0_Dimuon0_Upsilon_v ) );
  trigPathMapSI.insert(
      mP( HLT_Dimuon0_Jpsi_Muon_v ) );
  trigPathMapSI.insert(
      mP( HLT_Dimuon0er16_Jpsi_NoOS_NoVertexing_v ) );
  trigPathMapSI.insert(
      mP( HLT_Dimuon0er16_Jpsi_NoVertexing_v ) );
  trigPathMapSI.insert(
      mP( HLT_Dimuon10_Jpsi_Barrel_v ) );
  trigPathMapSI.insert(
      mP( HLT_Dimuon13_PsiPrime_v ) );
  trigPathMapSI.insert(
      mP( HLT_Dimuon16_Jpsi_v ) );
  trigPathMapSI.insert(
      mP( HLT_Dimuon20_Jpsi_v ) );
  trigPathMapSI.insert(
      mP( HLT_Dimuon6_Jpsi_NoVertexing_v ) );
  trigPathMapSI.insert(
      mP( HLT_Dimuon8_PsiPrime_Barrel_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleMu4_3_Bs_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleMu4_3_Jpsi_Displaced_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleMu4_JpsiTrk_Displaced_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleMu4_PsiPrimeTrk_Displaced_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu7p5_L2Mu2_Jpsi_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu7p5_Track2_Jpsi_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu7p5_Track3p5_Jpsi_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu7p5_Track7_Jpsi_v ) );
  trigPathMapSI.insert(
      mP( HLT_QuadMuon0_Dimuon0_Jpsi_v ) );
  trigPathMapSI.insert(
      mP( HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT250_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleEle33_CaloIdL_MW_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleEle33_CaloIdL_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT250_v ) );
  trigPathMapSI.insert(
      mP( HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v ) );
  trigPathMapSI.insert(
      mP( HLT_ECALHT800_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV_p13_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele12_CaloIdM_TrackIdM_PFJet30_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele17_CaloIdL_GsfTrkIdVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele17_CaloIdL_TrackIdL_IsoVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele17_CaloIdM_TrackIdM_PFJet30_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele23_CaloIdM_TrackIdM_PFJet30_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele27_HighEta_Ele20_Mass55_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele30WP60_Ele8_Mass55_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele30WP60_SC4_Mass55_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v ) );
  trigPathMapSI.insert(
      mP( HLT_Ele8_CaloIdM_TrackIdM_PFJet30_v ) );
  revertMap( trigPathMapSI,
             trigPathMapIS );

  trigObjectMapSI.clear();
  trigObjectMapSI.insert( mP( hltJet      ) );
  trigObjectMapSI.insert( mP( hltMuon     ) );
  trigObjectMapSI.insert( mP( hltElectron ) );
  trigObjectMapSI.insert( mP( hltTau      ) );
  revertMap( trigObjectMapSI,
             trigObjectMapIS );

  recoObjectMapSI.clear();
  recoObjectMapSI.insert( mP( recJet      ) );
  recoObjectMapSI.insert( mP( recMuon     ) );
  recoObjectMapSI.insert( mP( recElectron ) );
  recoObjectMapSI.insert( mP( recTau      ) );
  revertMap( recoObjectMapSI,
             recoObjectMapIS );

  recoUITypeMapSI.clear();
  recoUITypeMapSI.insert( mP( puBeta      ) );
  recoUITypeMapSI.insert( mP( puBetaStar  ) );
  revertMap( recoUITypeMapSI,
             recoUITypeMapIS );

  vertexTypeMapSI.clear();
  vertexTypeMapSI.insert( mP( svtTagInfo   ) );
  vertexTypeMapSI.insert( mP( svtFitPair   ) );
  vertexTypeMapSI.insert( mP( svtJPsi      ) );
  vertexTypeMapSI.insert( mP( svtKx0       ) );
  vertexTypeMapSI.insert( mP( svtPhi       ) );
  vertexTypeMapSI.insert( mP( svtBuJPsiK   ) );
  vertexTypeMapSI.insert( mP( svtBdJPsiKx  ) );
  vertexTypeMapSI.insert( mP( svtBsJPsiPhi ) );
  revertMap( vertexTypeMapSI,
             vertexTypeMapIS );

  trackTypeMapSI.clear();
  trackTypeMapSI.insert( mP( general      ) );
  trackTypeMapSI.insert( mP( packed       ) );
  trackTypeMapSI.insert( mP( pflink       ) );
  trackTypeMapSI.insert( mP( rclink       ) );
  trackTypeMapSI.insert( mP( gplink       ) );
  trackTypeMapSI.insert( mP( muInner      ) );
  trackTypeMapSI.insert( mP( muStandalone ) );
  trackTypeMapSI.insert( mP( muGlobal     ) );
  trackTypeMapSI.insert( mP( muBest       ) );
  trackTypeMapSI.insert( mP( muPF         ) );
  trackTypeMapSI.insert( mP( muReco       ) );
  revertMap( trackTypeMapSI,
             trackTypeMapIS );

  muonTypeMapSI.clear();
  muonTypeMapSI.insert( mP( tmOneStation ) );
  muonTypeMapSI.insert( mP( gmPrompt     ) );
  muonTypeMapSI.insert( mP( pf           ) );
  muonTypeMapSI.insert( mP( loose        ) );
  muonTypeMapSI.insert( mP( medium       ) );
  muonTypeMapSI.insert( mP( tight        ) );
  muonTypeMapSI.insert( mP( soft         ) );
  muonTypeMapSI.insert( mP( highPt       ) );
  muonTypeMapSI.insert( mP( inner        ) );
  muonTypeMapSI.insert( mP( standalone   ) );
  muonTypeMapSI.insert( mP( global       ) );
  revertMap( muonTypeMapSI,
             muonTypeMapIS );

}


PDEnumString::~PDEnumString() {
}


void
PDEnumString::resetTrigMap() {
  trigPathMapIS.clear();
  trigPathMapSI.clear();
  return;
}


void
PDEnumString::revertTrigMap() {
  revertMap( trigPathMapSI,
             trigPathMapIS );
  return;
}


const std::map<int,std::string>&
PDEnumString::trigMap() {
  return trigPathMapIS;
}


std::string PDEnumString::trigBase( const std::string& trigPath ) {
  int pathLength = trigPath.length();
  const char* str = trigPath.c_str() + pathLength - 1;
  while ( ( *str >= '0' ) && ( *str <= '9' ) ) {
    --str;
    --pathLength;
  }
  return trigPath.substr( 0, pathLength );
}


int
PDEnumString::findTrigPath( const std::string& trigPath,
                            bool fixedList, int code ) {
//  std::string trigName = trigBase( trigPath );
//  std::map<std::string,int>::const_iterator
//    iter = trigPathMapSI.find( trigName );
  std::map<std::string,int>::const_iterator
    iter = trigPathMapSI.find( trigPath );
  std::map<std::string,int>::const_iterator
    iend = trigPathMapSI.end();
  if ( iter != iend ) return iter->second;
  if ( fixedList ) return -1;
  int nextSlot = ( code < 0 ? trigPathMapIS.rbegin()->first + 1 : code );
//  std::cout << "add " << nextSlot << " " << trigPath << std::endl;
//  trigPathMapSI.insert( std::make_pair( trigName, nextSlot ) );
//  trigPathMapIS.insert( std::make_pair( nextSlot, trigName ) );
  trigPathMapSI.insert( std::make_pair( trigPath, nextSlot ) );
  trigPathMapIS.insert( std::make_pair( nextSlot, trigPath ) );
  return nextSlot;
}


const std::string&
PDEnumString::findTrigPath( int trigPath ) {
  std::map<int,std::string>::const_iterator
    iter = trigPathMapIS.find( trigPath );
  std::map<int,std::string>::const_iterator
    iend = trigPathMapIS.end();
  if ( iter != iend ) return iter->second;
  return defaultString;
}


int
PDEnumString::findTrigObject( const std::string& trigObject ) {
  std::map<std::string,int>::const_iterator
    iter = trigObjectMapSI.find( trigObject );
  std::map<std::string,int>::const_iterator
    iend = trigObjectMapSI.end();
  if ( iter != iend ) return iter->second;
  return -1;
}


const std::string&
PDEnumString::findTrigObject( int trigObject ) {
  std::map<int,std::string>::const_iterator
    iter = trigObjectMapIS.find( trigObject );
  std::map<int,std::string>::const_iterator
    iend = trigObjectMapIS.end();
  if ( iter != iend ) return iter->second;
  return defaultString;
}


int
PDEnumString::findRecoUIType( const std::string& recoUIType ) {
  std::map<std::string,int>::const_iterator
    iter = recoUITypeMapSI.find( recoUIType );
  std::map<std::string,int>::const_iterator
    iend = recoUITypeMapSI.end();
  if ( iter != iend ) return iter->second;
  return -1;
}


const std::string&
PDEnumString::findRecoUIType( int recoUIType ) {
  std::map<int,std::string>::const_iterator
    iter = recoUITypeMapIS.find( recoUIType );
  std::map<int,std::string>::const_iterator
    iend = recoUITypeMapIS.end();
  if ( iter != iend ) return iter->second;
  return defaultString;
}


int
PDEnumString::findRecoObject( const std::string& recoObject ) {
  std::map<std::string,int>::const_iterator
    iter = recoObjectMapSI.find( recoObject );
  std::map<std::string,int>::const_iterator
    iend = recoObjectMapSI.end();
  if ( iter != iend ) return iter->second;
  return -1;
}


const std::string&
PDEnumString::findRecoObject( int recoObject ) {
  std::map<int,std::string>::const_iterator
    iter = recoObjectMapIS.find( recoObject );
  std::map<int,std::string>::const_iterator
    iend = recoObjectMapIS.end();
  if ( iter != iend ) return iter->second;
  return defaultString;
}


int
PDEnumString::findVertexType( const std::string& vtxType ) {
  std::map<std::string,int>::const_iterator
    iter = vertexTypeMapSI.find( vtxType );
  std::map<std::string,int>::const_iterator
    iend = vertexTypeMapSI.end();
  if ( iter != iend ) return iter->second;
  return -1;
}


const std::string&
PDEnumString::findVertexType( int vtxType ) {
  std::map<int,std::string>::const_iterator
    iter = vertexTypeMapIS.find( vtxType );
  std::map<int,std::string>::const_iterator
    iend = vertexTypeMapIS.end();
  if ( iter != iend ) return iter->second;
  return defaultString;
}


void PDEnumString::revertMap( const std::map<std::string,int>& mapSI,
                                    std::map<int,std::string>& mapIS ) {
  mapIS.clear();
  std::map<std::string,int>::const_iterator iter = mapSI.begin();
  std::map<std::string,int>::const_iterator iend = mapSI.end();
  while ( iter != iend ) {
    const std::pair<std::string,int>& entry = *iter++;
    mapIS.insert( std::make_pair( entry.second, entry.first ) );
  }
  return;
}

