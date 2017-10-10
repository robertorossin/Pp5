#ifndef PDEnumString_H
#define PDEnumString_H

#include <map>
#include <string>

class PDEnumString {

 public:

  PDEnumString();
  virtual ~PDEnumString();

//  enum trigPath   { dummy = 0 };
  enum trigPath   { HLT_Mu10_CentralPFJet30_BTagCSV_p13_v = 1,
                    HLT_Mu17_Mu8_DZ_v,
                    HLT_Mu17_Mu8_SameSign_DZ_v,
                    HLT_Mu17_Mu8_SameSign_v,
                    HLT_Mu17_Mu8_v,
                    HLT_Mu17_TkMu8_DZ_v,
                    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v,
                    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v,
                    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v,
                    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v,
                    HLT_Mu17_TrkIsoVVL_v,
                    HLT_Mu17_v,
                    HLT_Mu20_Mu10_DZ_v,
                    HLT_Mu20_Mu10_SameSign_DZ_v,
                    HLT_Mu20_Mu10_SameSign_v,
                    HLT_Mu20_Mu10_v,
                    HLT_Mu27_TkMu8_v,
                    HLT_Mu30_TkMu11_v,
                    HLT_Mu3_PFJet40_v,
                    HLT_Mu40_TkMu11_v,
                    HLT_Mu8_TrkIsoVVL_v,
                    HLT_Mu8_v,
                    HLT_TripleMu_12_10_5_v,
                    HLT_TripleMu_5_3_3_v,
                    HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v,
                    HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx_v,
                    HLT_DoubleMu18NoFiltersNoVtx_v,
                    HLT_DoubleMu23NoFiltersNoVtxDisplaced_v,
                    HLT_DoubleMu28NoFiltersNoVtxDisplaced_v,
                    HLT_DoubleMu33NoFiltersNoVtx_v,
                    HLT_DoubleMu38NoFiltersNoVtx_v,
                    HLT_DoubleMu8_Mass8_PFHT250_v,
                    HLT_DoubleMu8_Mass8_PFHT300_v,
                    HLT_DoubleMu4_JpsiTrkTrk_Displaced_v,
                    HLT_L2DoubleMu23_NoVertex_v,
                    HLT_L2DoubleMu28_NoVertex_2Cha_Angle2p5_Mass10_v,
                    HLT_L2DoubleMu38_NoVertex_2Cha_Angle2p5_Mass10_v,
                    HLT_DoubleMu4_LowMassNonResonantTrk_Displaced_v,
                    HLT_Dimuon0_Phi_Barrel_v,
                    HLT_Dimuon0_Jpsi3p5_Muon2_v,
                    HLT_Dimuon0_Upsilon_Muon_v,
                    HLT_Dimuon13_Upsilon_v,
                    HLT_Dimuon8_Upsilon_Barrel_v,
                    HLT_Mu16_TkMu0_dEta18_Onia_v,
                    HLT_Mu16_TkMu0_dEta18_Phi_v,
                    HLT_Mu25_TkMu0_dEta18_Onia_v,
                    HLT_Mu7p5_L2Mu2_Upsilon_v,
                    HLT_Mu7p5_Track2_Upsilon_v,
                    HLT_Mu7p5_Track3p5_Upsilon_v,
                    HLT_Mu7p5_Track7_Upsilon_v,
                    HLT_QuadMuon0_Dimuon0_Upsilon_v,
                    HLT_Dimuon0_Jpsi_Muon_v,
                    HLT_Dimuon0er16_Jpsi_NoOS_NoVertexing_v,
                    HLT_Dimuon0er16_Jpsi_NoVertexing_v,
                    HLT_Dimuon10_Jpsi_Barrel_v,
                    HLT_Dimuon13_PsiPrime_v,
                    HLT_Dimuon16_Jpsi_v,
                    HLT_Dimuon20_Jpsi_v,
                    HLT_Dimuon6_Jpsi_NoVertexing_v,
                    HLT_Dimuon8_PsiPrime_Barrel_v,
                    HLT_DoubleMu4_3_Bs_v,
                    HLT_DoubleMu4_3_Jpsi_Displaced_v,
                    HLT_DoubleMu4_JpsiTrk_Displaced_v,
                    HLT_DoubleMu4_PsiPrimeTrk_Displaced_v,
                    HLT_Mu7p5_L2Mu2_Jpsi_v,
                    HLT_Mu7p5_Track2_Jpsi_v,
                    HLT_Mu7p5_Track3p5_Jpsi_v,
                    HLT_Mu7p5_Track7_Jpsi_v,
                    HLT_QuadMuon0_Dimuon0_Jpsi_v,
                    HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v,
                    HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v,
                    HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v,
                    HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v,
                    HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL_v,
                    HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v,
                    HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL_v,
                    HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v,
                    HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT250_v,
                    HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v,
                    HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v,
                    HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v,
                    HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_v,
                    HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_v,
                    HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v,
                    HLT_DoubleEle33_CaloIdL_MW_v,
                    HLT_DoubleEle33_CaloIdL_v,
                    HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL_v,
                    HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT250_v,
                    HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v,
                    HLT_ECALHT800_v,
                    HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV_p13_v,
                    HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v,
                    HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v,
                    HLT_Ele12_CaloIdM_TrackIdM_PFJet30_v,
                    HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v,
                    HLT_Ele17_CaloIdL_GsfTrkIdVL_v,
                    HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30_v,
                    HLT_Ele17_CaloIdL_TrackIdL_IsoVL_v,
                    HLT_Ele17_CaloIdM_TrackIdM_PFJet30_v,
                    HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v,
                    HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_v,
                    HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v,
                    HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v,
                    HLT_Ele23_CaloIdM_TrackIdM_PFJet30_v,
                    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded_v,
                    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v,
                    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v,
                    HLT_Ele27_HighEta_Ele20_Mass55_v,
                    HLT_Ele30WP60_Ele8_Mass55_v,
                    HLT_Ele30WP60_SC4_Mass55_v,
                    HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v,
                    HLT_Ele8_CaloIdM_TrackIdM_PFJet30_v,
                    DUMMY_LAST_TRIGGER };
  enum trigObject { hltJet = 1,
                    hltMuon,
                    hltElectron,
                    hltTau };
  enum recoObject { recJet = 1,
                    recMuon,
                    recElectron,
                    recTau };
  enum infoType   { puBeta = 1,
                    puBetaStar };
  enum vertexType { svtTagInfo = 1,
                    svtFitPair,
                    svtJPsi,
                    svtKx0,
                    svtPhi,
                    svtBuJPsiK,
                    svtBdJPsiKx,
                    svtBsJPsiPhi,
                    DUMMY_LAST_DECAY };
  enum trackType  { general      =     1,
                    packed       =     2,
                    pflink       =     4,
                    rclink       =     8,
                    gplink       =    16,
                    muInner      =  1024,
                    muStandalone =  2048,
                    muGlobal     =  4096,
                    muBest       =  8192,
                    muPF         = 16384,
                    muReco       = 32768 };
  enum muonType   { tmOneStation =    1,
                    gmPrompt     =    2,
                    pf           = pflink,
                    loose        =    8,
                    medium       =   16,
                    tight        =   32,
                    soft         =   64,
                    highPt       =  128,
                    inner        = muInner,
                    standalone   = muStandalone,
                    global       = muGlobal };

  static void  resetTrigMap();
  static void revertTrigMap();
  static const std::map<int,std::string>& trigMap();
  static std::string trigBase( const std::string& trigPath );

  static int                findTrigPath  ( const std::string& trigPath,
                                            bool fixedList = true,
                                            int code = -1 );
  static const std::string& findTrigPath  ( int                trigPath   );
  static int                findTrigObject( const std::string& trigObject );
  static const std::string& findTrigObject( int                trigObject );
  static int                findRecoObject( const std::string& recoObject );
  static const std::string& findRecoObject( int                recoObject );
  static int                findRecoUIType( const std::string& recoUIType );
  static const std::string& findRecoUIType( int                recoUIType );
  static int                findVertexType( const std::string& vtxType    );
  static const std::string& findVertexType( int                vtxType    );
  static int                findTrackType ( const std::string& trkType    );
  static const std::string& findTrackType ( int                trkType    );

 private:

  static std::string defaultString;
  static std::map<int,std::string>   trigPathMapIS;
  static std::map<std::string,int>   trigPathMapSI;
  static std::map<int,std::string> trigObjectMapIS;
  static std::map<std::string,int> trigObjectMapSI;
  static std::map<int,std::string> recoObjectMapIS;
  static std::map<std::string,int> recoObjectMapSI;
  static std::map<int,std::string> recoUITypeMapIS;
  static std::map<std::string,int> recoUITypeMapSI;
  static std::map<int,std::string> vertexTypeMapIS;
  static std::map<std::string,int> vertexTypeMapSI;
  static std::map<int,std::string>  trackTypeMapIS;
  static std::map<std::string,int>  trackTypeMapSI;
  static std::map<int,std::string>   muonTypeMapIS;
  static std::map<std::string,int>   muonTypeMapSI;

  static void revertMap( const std::map<std::string,int>& mapSI,
                               std::map<int,std::string>& mapIS );

};


#endif

