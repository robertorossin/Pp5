import FWCore.ParameterSet.Config as cms

process = cms.Process("bphAnalysis")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")

process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.options.allowUnscheduled = cms.untracked.bool(True)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:/lustre/cmswork/cmsdata/ronchese/store/mc/RunIISummer17MiniAOD/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/92X_upgrade2017_realistic_v10-v1/70000/003FD0A7-C490-E711-97BF-001F290860E4.root')
)

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

### vtxTagInfo
process.load('RecoBTag/SoftLepton/softLepton_cff')
#process.load('RecoBTag/SoftLepton/softPFMuonTagInfos_cfi')
#process.load('RecoBTag/SoftLepton/softPFElectronTagInfos_cfi')
process.load('RecoBTag/SecondaryVertex/pfInclusiveSecondaryVertexFinderTagInfos_cfi')
process.load('RecoBTag/ImpactParameter/pfImpactParameterTagInfos_cfi')

#process.load('RecoBTag/SecondaryVertex/secondaryVertexTagInfos_cfi')

process.softPFMuonsTagInfos.primaryVertex = cms.InputTag("offlineSlimmedPrimaryVertices")
process.softPFMuonsTagInfos.jets = cms.InputTag("slimmedJets")
process.softPFMuonsTagInfos.muons = cms.InputTag("slimmedMuons")

process.softPFElectronsTagInfos.primaryVertex = cms.InputTag("offlineSlimmedPrimaryVertices")
process.softPFElectronsTagInfos.jets = cms.InputTag("slimmedJets")
process.softPFElectronsTagInfos.electrons = cms.InputTag("slimmedElectrons")

process.pfImpactParameterTagInfos.primaryVertex = cms.InputTag("offlineSlimmedPrimaryVertices")
process.pfImpactParameterTagInfos.jets = cms.InputTag("slimmedJets")
process.pfImpactParameterTagInfos.candidates = cms.InputTag("packedPFCandidates")

process.tagInfoProd = cms.Sequence(
    process.softPFMuonsTagInfos
    + process.softPFElectronsTagInfos
    + process.pfImpactParameterTagInfos
    * process.pfSecondaryVertexTagInfos
    )

### vtxTagInfo end


process.pdAnalyzer = cms.EDAnalyzer('PDNtuplizer',

    ## optional
    eventList = cms.string('evtlist'),
    verbose = cms.untracked.string('f'),
    evStamp = cms.untracked.string('f'),

    ## mandatory
    ## ntuple file name: empty string to drop ntuple filling
    ntuName = cms.untracked.string('ntu.root'),
    ## histogram file name
    histName = cms.untracked.string('his.root'),

    labelTrigResults  = cms.string('TriggerResults::HLT'), 
    labelTrigEvent    = cms.string(''),
    labelBeamSpot     = cms.string('offlineBeamSpot'),
    labelMets         = cms.string('slimmedMETs'),
    labelMuons        = cms.string('slimmedMuons'),
    labelElectrons    = cms.string('slimmedElectrons'),
    labelTaus         = cms.string('slimmedTaus'),

    labelJets         = cms.string('slimmedJets'),
    labelPCCandidates = cms.string('packedPFCandidates::PAT'),

    labelGeneralTracks = cms.string(''),
    labelPVertices    = cms.string('offlineSlimmedPrimaryVertices'),
    labelSVertices    = cms.string('pfSecondaryVertexTagInfos'),
    labelSVTagInfo    = cms.string(''),
    labelPUInfo       = cms.string(''),
    labelGen          = cms.string('prunedGenParticles'),
    labelGPJ          = cms.string('slimmedGenJets'),

    labelCSV          = cms.string('pfCombinedInclusiveSecondaryVertexV2BJetTags'),
    labelTCHE         = cms.string('trackCountingHighEffBJetTags'),

    vertReco = cms.vstring('svtBuJPsiK','svtBdJPsiKx','svtBsJPsiPhi'),

    acceptNewTrigPaths = cms.string('f'),
    write_hltlist = cms.string('f'),

    selectAssociatedPF = cms.string('f'),
    selectAssociatedTk = cms.string('f'),
    recoverMuonTracks = cms.string('t'),
    writeAllPrimaryVertices = cms.string('t'),

    jetPtMin  = cms.double(  5.0 ),
    jetEtaMax = cms.double(  2.5 ),
    trkDzMax  = cms.double(  0.8 ),
    trkPtMin  = cms.double(  0.5 ),
    trkEtaMax = cms.double(  3.0 ),
    dRmatchHLT = cms.double( 0.5 ),
    dPmatchHLT = cms.double( 0.5 ),


    savedTriggerPaths = cms.vstring(
        '*'
    ),

    ## trigger objects to save on ntuple:
    savedTriggerObjects = cms.vstring(
        'hltJet',
        'hltMuon'
    ),

    ## jet user info to save on ntuple:
    savedJetInfo = cms.vstring(
#        'puBeta*'
    )


)


#############################################################
#### PATH definition
#############################################################
# Let it run
process.p = cms.Path(
    process.tagInfoProd *
    process.pdAnalyzer
    )

