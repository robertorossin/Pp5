import FWCore.ParameterSet.Config as cms

process.bphHistoSpecificDecay = cms.EDAnalyzer('BPHHistoSpecificDecay',
  oniaCandsLabel = cms.string(''),
  sdCandsLabel = cms.string(''),
  ssCandsLabel = cms.string(''),
  buCandsLabel = cms.string(''),
  bdCandsLabel = cms.string(''),
  bsCandsLabel = cms.string('')
)
