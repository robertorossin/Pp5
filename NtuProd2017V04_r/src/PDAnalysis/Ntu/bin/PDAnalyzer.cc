#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

#include "PDAnalyzer.h"

#include "TDirectory.h"
#include "TBranch.h"
#include "TTree.h"
#include "TCanvas.h"
#include "Math/LorentzVector.h"
#include "TFile.h"

// additional features
//#include "PDSecondNtupleWriter.h"                // second ntuple
//#include "DataSetFilter.cc"                      // dataset filter

using namespace std;

PDAnalyzer::PDAnalyzer() {

  std::cout << "new PDAnalyzer" << std::endl;

  // user parameters are set as names associated to a string, 
  // default values can be set in the analyzer class contructor

  setUserParameter( "verbose", "f" );
  setUserParameter( "ptCut", "40.0" );
  setUserParameter( "dmMax", "0.25" );

}


PDAnalyzer::~PDAnalyzer() {
}



void PDAnalyzer::beginJob() {

  PDAnalyzerUtil::beginJob();

  // user parameters are retrieved as strings by using their names;
  // numeric parameters ( int, float or whatever ) can be directly set
  // by passing the corresponding variable,
  // e.g. getUserParameter( "name", x )

  getUserParameter( "verbose", verbose );
  getUserParameter( "ptCut", ptCut );
  getUserParameter( "dmMax", dmMax );

// to skim the N-tuple "uncomment" the following lines
//  // dropBranch( "*tau*" ); // drop some branch if required
//  initWSkim( new TFile( "skim.root", "RECREATE" ) );

// additional features
//  DataSetFilter::beginJob();                     // dataset filter
//  tWriter = new PDSecondNtupleWriter;            // second ntuple
//  tWriter->open( "secondNtu.root", "RECREATE" ); // second ntuple

  return;

}


void PDAnalyzer::book() {

  // putting "autoSavedObject" in front of the histo creation 
  // it's automatically marked for saving on file; the option 
  // is uneffective when not using the full utility

  autoSavedObject =
  hptmumax        = new TH1D( "hptmumax"    , "ptmumax"    ,  50, 0.0, 100.0 );
  autoSavedObject =
  hptmu2nd        = new TH1D( "hptmu2nd"    , "ptmu 2nd"   ,  50, 0.0, 100.0 );
  autoSavedObject =
  hptmu           = new TH1D( "hptmu"       , "ptmu"       ,  50, 0.0, 100.0 );
  autoSavedObject =
  hMass1          = new TH1F( "hMass1"      , "mass"       , 120, 0.0,   6.0 );
  autoSavedObject =
  hMass2          = new TH1F( "hMass2"      , "mass"       , 600, 0.0,   6.0 );
  autoSavedObject =
  hMass3          = new TH1F( "hMass3"      , "mass"       , 600, 0.0,   6.0 );

  return;

}


void PDAnalyzer::reset() {
// automatic reset
  autoReset();
  return;
}


bool PDAnalyzer::analyze( int entry, int event_file, int event_tot ) {

  if ( verbose ) {
    cout << " +++++++++++++++++++++++++++ " << endl;
    cout << "entry: "
         << entry << " " << event_file << " " << event_tot << endl;
    cout << "run: " <<   runNumber << " , "
         << "evt: " << eventNumber << endl;
  }
  else {
//    if ( !( event_file % 10000 ) || !( event_tot % 10000 ) )
    if ( !( event_tot % 10000 ) && event_tot )
      cout << event_file << " " << event_tot << endl;
  }

// additional features
//  if ( !triggerAccept() ) return false;          // dataset filter
//  tWriter->nSum = nMuons + nElectrons;           // second ntuple
//  tWriter->nPro = nMuons * nElectrons;           // second ntuple
//  tWriter->fill();                               // second ntuple

  // flag to be set "true" or "false" for events accepted or rejected
  bool flag;

  flag = true;

  int iMuon;
  float ptmu;
  float ptmumax = -1.0;
  float ptmu2nd = -1.0;
  for ( iMuon = 0; iMuon < nMuons; ++iMuon ) {
    cout << "muon " << iMuon << endl;
    ptmu = muoPt->at( iMuon );
    hptmu->Fill( ptmu );
    if( ptmu > ptmu2nd ) {
      if( ptmu > ptmumax ) {
        ptmu2nd = ptmumax;
        ptmumax = ptmu;
      }
      else {
        ptmu2nd = ptmu;
      }
    }
  }
  hptmumax->Fill( ptmumax );
  hptmu2nd->Fill( ptmu2nd );	

/*
// associate jets to partons
  class DistByDeltaRSquare: public ObjectDistance {
    virtual number operator()(
                   number lObjPt , number lObjEta, number lObjPhi,
                   number lObjPx , number lObjPy , number lObjPz ,
                   number lObjE  , int    lObjCha,
                   number rObjPt , number rObjEta, number rObjPhi,
                   number rObjPx , number rObjPy , number rObjPz ,
                   number rObjE  , int    rObjCha) {
      if ( lObjCha != rObjCha ) return FLT_MAX;
      return dRSqua( lObjEta, lObjPhi, rObjEta, rObjPhi );
      // dRSqua defined in NtuAnalysis/Common/interface/NtuUtil.h
    }
    virtual number dMax() { return 0.09; }
  } drs;
  class SelectHadron: public ObjectSelection {
   public:
    SelectHadron( const set<int>& hSet ): hs( hSet ) {}
    virtual bool operator()( int obj ) {
      if ( hs.find( obj ) == hs.end() ) return false;
      return true;
    }
    const set<int>& hs;
  };
  const set<int>& fPSet = finalPartSet();
  // finalPartSet defined in PDAnalysis/Ntu/interface/PDGenHandler.h
  SelectHadron hsel( fPSet );
  convSpheCart( jetPt, jetEta, jetPhi,
                jetPx, jetPy , jetPz );
  convSpheCart( genPt, genEta, genPhi,
                genPx, genPy , genPz );
  const vector<ObjectAssociation>& jetAss = genAssociation(
                                            &drs, PDEnumString::recJet,
                                            &hsel );
*/

  int iJet;
  for ( iJet = 0; iJet < nJets; ++iJet ) {
    cout << "jet: " << iJet << " / SV: " << tagSVJet( iJet )
         << " / " << jetCSV->at( iJet ) << endl;
/*
    const vector<int>& tks = tracksFromJet( iJet );
    // tracksFromJet defined in PDAnalyzer/Ntu/bin/PDAnalyzerUtil.h
    int i = 0;
    int n = tks.size();
    if ( n ) {
      cout << "tracks for jet " << iJet << " :";
      while ( i < n ) cout << " " << tks[i++];
      cout << endl;
    }
    int iPart = jetAss[iJet].iObj;
    int iType = ( iPart >= 0 ? genId->at( iPart ) : 0 );
    if ( iType )
    cout << "jet associated to parton " << iPart
         << " (" << iType << ")" << endl;
*/
  }

/*
  cout << "-----" << endl;

  int iPV;
  for ( iPV = 0; iPV < nPVertices; ++iPV ) {
    const vector<int>& tks = tracksFromPV( iPV );
    // tracksFromPV defined in PDAnalyzer/Ntu/bin/PDAnalyzerUtil.h
    int i = 0;
    int n = tks.size();
    if ( n ) {
      cout << "tracks for PV " << iPV << " :";
      while ( i < n ) cout << " " << tks[i++];
      cout << endl;
    }
  }

  cout << "-----" << endl;
*/

  int iSV;
  for ( iSV = 0; iSV < nSVertices; ++iSV ) {
    if ( svtType->at( iSV ) < 3 ) continue;
    hMass1->Fill( svtMass->at( iSV ) );
    hMass2->Fill( svtMass->at( iSV ) );
    if ( svtType->at( iSV ) == PDEnumString::svtPhi ) {
      int iMot = motherVtxSV( iSV );
      if ( iMot == -1 ) continue;
      float mMass = svtMass->at( iMot );
      if ( fabs( mMass - 5.366 ) > dmMax ) continue;
    }
    hMass3->Fill( svtMass->at( iSV ) );
  }

/*
  for ( iSV = 0; iSV < nSVertices; ++iSV ) {
    const vector<int>& tks = tracksFromSV( iSV );
    // tracksFromSV defined in PDAnalyzer/Ntu/bin/PDAnalyzerUtil.h
    int i = 0;
    int n = tks.size();
    if ( n ) {
      cout << "tracks for SV " << iSV << "(" << svtName( iSV ) << ") :";
      while ( i < n ) cout << " " << tks[i++];
      cout << endl;
    }
    const vector<int>& sub = subVtxFromSV( iSV );
    // subVtxFromSV defined in PDAnalyzer/Ntu/bin/PDAnalyzerUtil.h
    int j = 0;
    int m = sub.size();
    if ( m ) {
      cout << "parts for SV " << iSV << "(" << svtName( iSV ) << ") :";
      while ( j < m ) cout << " " << sub[j++];
      cout << endl;
    }
//    int jSV;
//    for ( jSV = 0; jSV < nSVertices; ++jSV ) cout << jSV << ( subVtxSVRel( jSV, iSV ) ? 'y' : 'n' ) << endl;
  }
*/

/*
  int iTk;
  for ( iTk = 0; iTk < nTracks; ++iTk ) {
    const vector<int>& svs = sVtsWithTrack( iTk );
    // sVtsWithTrack defined in PDAnalyzer/Ntu/bin/PDAnalyzerUtil.h
    int i = 0;
    int n = svs.size();
    if ( n ) {
      cout << "SVtx with track " << iTk;
      while ( i < n ) cout << " " << svs[i++];
      cout << endl;
    }
  }
*/
//  cout << nElectrons << endl;

  flag = ptmumax > ptCut;

// to skim the N-tuple "uncomment" the following line
//  if ( flag ) fillSkim();

  return flag;

}


void PDAnalyzer::endJob() {
// to skim the N-tuple "uncomment" the following line
//  closeSkim();

// additional features
//  DataSetFilter::endJob();                       // dataset filter
//  tWriter->close();                              // second ntuple
  return;
}


void PDAnalyzer::save() {
#  if UTIL_USE == FULL
  // explicit saving not necessary for "autoSavedObjects"
  autoSave();
#elif UTIL_USE == BARE
  // explicit save histos when not using the full utility
  hptmumax->Write();
  hptmu2nd->Write();
  hptmu   ->Write();
#endif

  return;
}


// to plot some histogram immediately after the ntuple loop
// "uncomment" the following lines
/*
void PDAnalyzer::plot() {
  TCanvas* can = new TCanvas( "muoPt", "muoPt", 800, 600 );
  can->cd();
  can->Divide( 1, 2 );
  can->cd( 1 );
  hptmumax->Draw();
  hptmu2nd->Draw();
  return;
}
*/

