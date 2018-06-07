#include "../interface/TriggersNtuplizer.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"


//===================================================================================================================
TriggersNtuplizer::TriggersNtuplizer( edm::EDGetTokenT<edm::TriggerResults> tokens,
                                      edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> object,
				      edm::EDGetTokenT<pat::PackedTriggerPrescales> prescale,
				      edm::EDGetTokenT<edm::TriggerResults> noiseFilterToken,
				      edm::EDGetTokenT<bool> HBHENoiseFilterLooseResultToken,
				      edm::EDGetTokenT<bool> HBHENoiseFilterTightResultToken,
				      edm::EDGetTokenT<bool> HBHENoiseIsoFilterResultToken,
				      NtupleBranches* nBranches,
				      const edm::ParameterSet& iConfig,
				      std::map< std::string, bool >& runFlags)
   : CandidateNtuplizer	( nBranches )
   , HLTtriggersToken_	( tokens )
   , triggerObjects_	( object )
   , triggerPrescales_	( prescale )
   , noiseFilterToken_	( noiseFilterToken )
   , HBHENoiseFilterLoose_Selector_( HBHENoiseFilterLooseResultToken )
   , HBHENoiseFilterTight_Selector_( HBHENoiseFilterTightResultToken )
   , HBHENoiseIsoFilter_Selector_( HBHENoiseIsoFilterResultToken )
   , doTriggerDecisions_( runFlags["doTriggerDecisions"] )
   , doTriggerObjects_	( runFlags["doTriggerObjects"] )
   , doHltFilters_	( runFlags["doHltFilters"] )
   , runOnMC_           ( runFlags["runOnMC"] )
{

  HBHENoiseFilter_Selector_ =  iConfig.getParameter<std::string> ("noiseFilterSelection_HBHENoiseFilter");
  CSCHaloNoiseFilter_Selector_ =  iConfig.getParameter<std::string> ("noiseFilterSelection_CSCTightHaloFilter");
  CSCTightHalo2015Filter_Selector_ =  iConfig.getParameter<std::string> ("noiseFilterSelection_CSCTightHalo2015Filter");
  HCALlaserNoiseFilter_Selector_ =  iConfig.getParameter<std::string> ("noiseFilterSelection_hcalLaserEventFilter");
  ECALDeadCellNoiseFilter_Selector_ =  iConfig.getParameter<std::string> ("noiseFilterSelection_EcalDeadCellTriggerPrimitiveFilter");
  GoodVtxNoiseFilter_Selector_ =  iConfig.getParameter<std::string> ("noiseFilterSelection_goodVertices");
  TrkFailureNoiseFilter_Selector_ =  iConfig.getParameter<std::string> ("noiseFilterSelection_trackingFailureFilter");
  EEBadScNoiseFilter_Selector_ =  iConfig.getParameter<std::string> ("noiseFilterSelection_eeBadScFilter");
  ECALlaserNoiseFilter_Selector_ =  iConfig.getParameter<std::string> ("noiseFilterSelection_ecalLaserCorrFilter");
  TrkPOGNoiseFilter_Selector_ =  iConfig.getParameter<std::string> ("noiseFilterSelection_trkPOGFilters");
  TrkPOG_manystrip_NoiseFilter_Selector_ =  iConfig.getParameter<std::string> ("noiseFilterSelection_trkPOG_manystripclus53X");
  TrkPOG_toomanystrip_NoiseFilter_Selector_ =  iConfig.getParameter<std::string> ("noiseFilterSelection_trkPOG_toomanystripclus53X");
  TrkPOG_logError_NoiseFilter_Selector_ =  iConfig.getParameter<std::string> ("noiseFilterSelection_trkPOG_logErrorTooManyClusters");
  METFilters_Selector_ =  iConfig.getParameter<std::string> ("noiseFilterSelection_metFilters");

  //NEW FOR ICHEP
  CSCTightHaloTrkMuUnvetoFilter_Selector_       =  iConfig.getParameter<std::string> ("noiseFilterSelection_CSCTightHaloTrkMuUnvetoFilter");
  globalTightHalo2016Filter_Selector_           =  iConfig.getParameter<std::string> ("noiseFilterSelection_globalTightHalo2016Filter");
  HcalStripHaloFilter_Selector_                 =  iConfig.getParameter<std::string> ("noiseFilterSelection_HcalStripHaloFilter");
  chargedHadronTrackResolutionFilter_Selector_  =  iConfig.getParameter<std::string> ("noiseFilterSelection_chargedHadronTrackResolutionFilter");
  muonBadTrackFilter_Selector_                  =  iConfig.getParameter<std::string> ("noiseFilterSelection_muonBadTrackFilter");
  
  //NEW FOR MORIOND

  badMuons_Selector_  =  iConfig.getParameter<std::string> ("noiseFilterSelection_badMuonsFilter");
  duplicateMuons_Selector_  =  iConfig.getParameter<std::string> ("noiseFilterSelection_duplicateMuonsFilter");
  nobadMuons_Selector_  =  iConfig.getParameter<std::string> ("noiseFilterSelection_nobadMuonsFilter");

}

//===================================================================================================================
TriggersNtuplizer::~TriggersNtuplizer( void )
{

}

//===================================================================================================================
bool TriggersNtuplizer::findTrigger( std::string trigName ){

   if(  
       trigName.find( "PFHT800"                                        ) != std::string::npos ||
       trigName.find( "PFHT900"                                        ) != std::string::npos ||
       trigName.find( "HLT_AK8PFJet360_TrimMass30_v"                   ) != std::string::npos ||
       trigName.find( "HLT_CaloJet500_NoJetID_v"                        ) != std::string::npos ||
       trigName.find( "HLT_ECALHT800_v"                                 ) != std::string::npos ||
       trigName.find( "HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_PFMET40"  ) != std::string::npos ||
       trigName.find( "HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_VBF"      ) != std::string::npos ||
       trigName.find( "HLT_Photon22_R9Id90_HE10_IsoM"                  ) != std::string::npos ||
       trigName.find( "HLT_Photon22_v"                                 ) != std::string::npos ||
       trigName.find( "HLT_Photon30_R9Id90_HE10_IsoM"                  ) != std::string::npos ||
       trigName.find( "HLT_Photon30_v"                                 ) != std::string::npos ||
       trigName.find( "HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_PFMET40"  ) != std::string::npos ||
       trigName.find( "HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_VBF"      ) != std::string::npos ||
       trigName.find( "HLT_Photon36_R9Id90_HE10_IsoM"                  ) != std::string::npos ||
       trigName.find( "HLT_Photon36_v"                                 ) != std::string::npos ||
       trigName.find( "HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_PFMET40"  ) != std::string::npos ||
       trigName.find( "HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_VBF"      ) != std::string::npos ||
       trigName.find( "HLT_Photon50_R9Id90_HE10_IsoM"                  ) != std::string::npos ||
       trigName.find( "HLT_Photon50_v"                                 ) != std::string::npos ||
       trigName.find( "HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_PFMET40"  ) != std::string::npos ||
       trigName.find( "HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_VBF"      ) != std::string::npos ||
       trigName.find( "HLT_Photon75_R9Id90_HE10_IsoM"                  ) != std::string::npos ||
       trigName.find( "HLT_Photon75_v"                                 ) != std::string::npos ||
       trigName.find( "HLT_Photon90_CaloIdL_PFHT500"                   ) != std::string::npos || 
       trigName.find( "HLT_Photon90_CaloIdL_PFHT600"                   ) != std::string::npos || 
       trigName.find( "HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_PFMET40"  ) != std::string::npos || 
       trigName.find( "HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_VBF"      ) != std::string::npos || 
       trigName.find( "HLT_Photon90_R9Id90_HE10_IsoM"                  ) != std::string::npos ||
       trigName.find( "HLT_Photon90_v"                                 ) != std::string::npos ||
       trigName.find( "HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40" ) != std::string::npos ||
       trigName.find( "HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_VBF"     ) != std::string::npos ||
       trigName.find( "HLT_Photon120_R9Id90_HE10_IsoM"                 ) != std::string::npos ||
       trigName.find( "HLT_Photon120_v"                                ) != std::string::npos ||
       trigName.find( "HLT_Photon135_PFMET100"                         ) != std::string::npos ||
       trigName.find( "HLT_Photon165_HE10_v"                             ) != std::string::npos ||
       trigName.find( "HLT_Photon165_R9Id90_HE10_IsoM"                 ) != std::string::npos ||
       trigName.find( "HLT_Photon175_v"                                ) != std::string::npos ||
       trigName.find( "HLT_Photon250_NoHE"                             ) != std::string::npos ||
       trigName.find( "HLT_Photon300_NoHE"                             ) != std::string::npos ||
       trigName.find( "HLT_Photon500_v"                                ) != std::string::npos ||
       trigName.find( "HLT_Photon600_v"                                ) != std::string::npos 
   ) return true;
   else
     return false;
}


bool TriggersNtuplizer::findFilter( std::string filterName ){

   if( filterName.find("hltL3crIsoL1sMu16L1f0L2f10QL3f18QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3crIsoL1sMu18L1f0L2f10QL3f20QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3crIsoL1sMu20L1f0L2f10QL3f22QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3crIsoL1sSingleMu20erL1f0L2f10QL3f22QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3crIsoL1sMu22L1f0L2f10QL3f24QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3fL1sMu16L1f0Tkf18QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3fL1sMu18L1f0Tkf20QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3fL1sMu20erL1f0Tkf22QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3fL1sMu20L1f0Tkf22QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3fL1sMu22L1f0Tkf24QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3fL1sMu22Or25L1f0Tkf27QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3crIsoL1sSingleMu16erL1f0L2f10QL3f17QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltOverlapFilterSingleIsoMu17LooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltL3crIsoL1sMu16erTauJet20erL1f0L2f10QL3f17QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltOverlapFilterIsoMu17LooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltL3crIsoL1sSingleMu18erIorSingleMu20erL1f0L2f10QL3f19QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltOverlapFilterSingleIsoMu19LooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltL3crIsoL1sMu18erTauJet20erL1f0L2f10QL3f19QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltOverlapFilterIsoMu19LooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltL3crIsoL1sSingleMu20erIorSingleMu22erL1f0L2f10QL3f21QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltOverlapFilterSingleIsoMu21LooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltPFTau20TrackLooseIsoAgainstMuon") != std::string::npos ||
       filterName.find("hltEle23WPLooseGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltSingleEle24WPLooseGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle25WPTightGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle25erWPLooseGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle25erWPTightGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle27noerWPLooseGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle27WPTightGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle27erWPLooseGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle27erWPTightGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle32WPTightGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle22WPLooseL1SingleIsoEG20erGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltOverlapFilterSingleIsoEle22WPLooseGsfLooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltEle24WPLooseL1SingleIsoEG22erGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltOverlapFilterSingleIsoEle24WPLooseGsfLooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltEle24WPLooseL1IsoEG22erTau20erGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltOverlapFilterIsoEle24WPLooseGsfLooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltOverlapFilterIsoEle27WPLooseGsfLooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltEle32WPLooseGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltOverlapFilterIsoEle32WPLooseGsfLooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltPFTau20TrackLooseIso") != std::string::npos ||
       filterName.find("hltMu8TrkIsoVVLEle17CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter") != std::string::npos ||
       filterName.find("hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter") != std::string::npos ||
       filterName.find("hltMu17TrkIsoVVLEle12CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter") != std::string::npos ||
       filterName.find("hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter") != std::string::npos ||
       filterName.find("hltMu23TrkIsoVVLEle8CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter") != std::string::npos ||
       filterName.find("hltMu8TrkIsoVVLEle17CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8") != std::string::npos ||
       filterName.find("hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8") != std::string::npos ||
       filterName.find("hltMu17TrkIsoVVLEle12CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered17") != std::string::npos ||
       filterName.find("hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23") != std::string::npos ||
       filterName.find("hltMu23TrkIsoVVLEle8CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23") != std::string::npos ||
       filterName.find("hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLDZFilter") != std::string::npos ||
       filterName.find("hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLDZFilter") != std::string::npos || 
       filterName.find("hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter") != std::string::npos || 
       filterName.find("hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8") != std::string::npos || 
       filterName.find("hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23") != std::string::npos || 
	 //       filterName.find("hltDiMuonGlb17Glb8RelTrkIsoFiltered0p4") != std::string::npos || 
	 //       filterName.find("hltDiMuonGlb17Trk8RelTrkIsoFiltered0p4") != std::string::npos || 
       filterName.find("hltDoublePFTau32TrackPt1MediumIsolationDz02Reg") != std::string::npos || 
       filterName.find("hltDoublePFTau35TrackPt1MediumIsolationDz02Reg") != std::string::npos || 
       filterName.find("hltDoublePFTau40TrackPt1MediumIsolationDz02Reg") != std::string::npos
       ) return true;
   else
     return false;   
}



//===================================================================================================================
void TriggersNtuplizer::fillBranches( edm::Event const & event, const edm::EventSetup& iSetup ){

  event.getByToken(HLTtriggersToken_, HLTtriggers_);
  event.getByToken(triggerObjects_  , triggerObjects);
  event.getByToken(triggerPrescales_, triggerPrescales);

  const edm::TriggerNames& trigNames = event.triggerNames(*HLTtriggers_);


  if (doTriggerDecisions_) {
  	 for (unsigned int i = 0, n = HLTtriggers_->size(); i < n; ++i) {
  	  if( findTrigger(trigNames.triggerName(i)) ){
   	     nBranches_->HLT_isFired[trigNames.triggerName(i)] = HLTtriggers_->accept(i);
	     // std::cout << "Trigger " << trigNames.triggerName(i) << ": " << (HLTtriggers_->accept(i) ? "PASS" : "fail (or not run)") << std::endl;
   	  }
   	}

  } //doTriggerDecisions_
   ) return true;
   else
     return false;
}


bool TriggersNtuplizer::findFilter( std::string filterName ){

   if( filterName.find("hltL3crIsoL1sMu16L1f0L2f10QL3f18QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3crIsoL1sMu18L1f0L2f10QL3f20QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3crIsoL1sMu20L1f0L2f10QL3f22QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3crIsoL1sSingleMu20erL1f0L2f10QL3f22QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3crIsoL1sMu22L1f0L2f10QL3f24QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3fL1sMu16L1f0Tkf18QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3fL1sMu18L1f0Tkf20QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3fL1sMu20erL1f0Tkf22QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3fL1sMu20L1f0Tkf22QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3fL1sMu22L1f0Tkf24QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3fL1sMu22Or25L1f0Tkf27QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltL3crIsoL1sSingleMu16erL1f0L2f10QL3f17QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltOverlapFilterSingleIsoMu17LooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltL3crIsoL1sMu16erTauJet20erL1f0L2f10QL3f17QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltOverlapFilterIsoMu17LooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltL3crIsoL1sSingleMu18erIorSingleMu20erL1f0L2f10QL3f19QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltOverlapFilterSingleIsoMu19LooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltL3crIsoL1sMu18erTauJet20erL1f0L2f10QL3f19QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltOverlapFilterIsoMu19LooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltL3crIsoL1sSingleMu20erIorSingleMu22erL1f0L2f10QL3f21QL3trkIsoFiltered0p09") != std::string::npos ||
       filterName.find("hltOverlapFilterSingleIsoMu21LooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltPFTau20TrackLooseIsoAgainstMuon") != std::string::npos ||
       filterName.find("hltEle23WPLooseGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltSingleEle24WPLooseGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle25WPTightGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle25erWPLooseGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle25erWPTightGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle27noerWPLooseGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle27WPTightGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle27erWPLooseGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle27erWPTightGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle32WPTightGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltEle22WPLooseL1SingleIsoEG20erGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltOverlapFilterSingleIsoEle22WPLooseGsfLooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltEle24WPLooseL1SingleIsoEG22erGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltOverlapFilterSingleIsoEle24WPLooseGsfLooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltEle24WPLooseL1IsoEG22erTau20erGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltOverlapFilterIsoEle24WPLooseGsfLooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltOverlapFilterIsoEle27WPLooseGsfLooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltEle32WPLooseGsfTrackIsoFilter") != std::string::npos ||
       filterName.find("hltOverlapFilterIsoEle32WPLooseGsfLooseIsoPFTau20") != std::string::npos ||
       filterName.find("hltPFTau20TrackLooseIso") != std::string::npos ||
       filterName.find("hltMu8TrkIsoVVLEle17CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter") != std::string::npos ||
       filterName.find("hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter") != std::string::npos ||
       filterName.find("hltMu17TrkIsoVVLEle12CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter") != std::string::npos ||
       filterName.find("hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter") != std::string::npos ||
       filterName.find("hltMu23TrkIsoVVLEle8CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter") != std::string::npos ||
       filterName.find("hltMu8TrkIsoVVLEle17CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8") != std::string::npos ||
       filterName.find("hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8") != std::string::npos ||
       filterName.find("hltMu17TrkIsoVVLEle12CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered17") != std::string::npos ||
       filterName.find("hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23") != std::string::npos ||
       filterName.find("hltMu23TrkIsoVVLEle8CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23") != std::string::npos ||
       filterName.find("hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLDZFilter") != std::string::npos ||
       filterName.find("hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLDZFilter") != std::string::npos || 
       filterName.find("hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter") != std::string::npos || 
       filterName.find("hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8") != std::string::npos || 
       filterName.find("hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23") != std::string::npos || 
	 //       filterName.find("hltDiMuonGlb17Glb8RelTrkIsoFiltered0p4") != std::string::npos || 
	 //       filterName.find("hltDiMuonGlb17Trk8RelTrkIsoFiltered0p4") != std::string::npos || 
       filterName.find("hltDoublePFTau32TrackPt1MediumIsolationDz02Reg") != std::string::npos || 
       filterName.find("hltDoublePFTau35TrackPt1MediumIsolationDz02Reg") != std::string::npos || 
       filterName.find("hltDoublePFTau40TrackPt1MediumIsolationDz02Reg") != std::string::npos
       ) return true;
   else
     return false;   
}



//===================================================================================================================
void TriggersNtuplizer::fillBranches( edm::Event const & event, const edm::EventSetup& iSetup ){

  event.getByToken(HLTtriggersToken_, HLTtriggers_);
  event.getByToken(triggerObjects_  , triggerObjects);
  event.getByToken(triggerPrescales_, triggerPrescales);

  const edm::TriggerNames& trigNames = event.triggerNames(*HLTtriggers_);


  if (doTriggerDecisions_) {
  	 for (unsigned int i = 0, n = HLTtriggers_->size(); i < n; ++i) {
  	  if( findTrigger(trigNames.triggerName(i)) ){
   	     nBranches_->HLT_isFired[trigNames.triggerName(i)] = HLTtriggers_->accept(i);
	     // std::cout << "Trigger " << trigNames.triggerName(i) << ": " << (HLTtriggers_->accept(i) ? "PASS" : "fail (or not run)") << std::endl;
   	  }
   	}

  } //doTriggerDecisions_

  ////////////////// Trigger objects ///////////////////////////////////
  if (doTriggerObjects_) {

    for (pat::TriggerObjectStandAlone obj : *triggerObjects) {
      
      obj.unpackPathNames(trigNames);
      obj.unpackFilterLabels(event, *HLTtriggers_);

      std::vector<std::string> pathNamesAll  = obj.pathNames(false);

      for (unsigned h = 0, n = pathNamesAll.size(); h < n; ++h) {

	//		  bool isBoth = obj.hasPathName( pathNamesAll[h], true , true );
	//		  bool isL3   = obj.hasPathName( pathNamesAll[h], false, true );
	//		  bool isBoth = obj.hasPathName( pathNamesLast[h], true , true );
	//		  bool isL3   = obj.hasPathName( pathNamesLast[h], false, true );
	
	
	//			if( isBoth || isL3 ){
	

	
  		obj.unpackPathNames(trigNames);
		
  		std::vector<std::string> pathNamesAll  = obj.pathNames(false);
  		std::vector<std::string> pathNamesLast = obj.pathNames(true);
		
  		for (unsigned h = 0, n = pathNamesLast.size(); h < n; ++h) {
		
  			bool isBoth = obj.hasPathName( pathNamesLast[h], true , true );
                        bool isL3   = obj.hasPathName( pathNamesLast[h], false, true );
			
  			if( isBoth || isL3 ){
		
  			   nBranches_->triggerObject_pt	 .push_back(obj.pt());
  			   nBranches_->triggerObject_eta .push_back(obj.eta());
  			   nBranches_->triggerObject_phi .push_back(obj.phi());
  			   nBranches_->triggerObject_mass.push_back(obj.mass());
				
  			   for (unsigned h = 0; h < obj.filterIds().size(); ++h) vfilterIDs.push_back( obj.filterIds()[h]); // as defined in http://cmslxr.fnal.gov/lxr/source/DataFormats/HLTReco/interface/TriggerTypeDefs.h
				
  			   if( pathNamesLast[h] == "HLT_PFHT800_v1"                                   ) vfiredTrigger.push_back( 0 );
  			   if( pathNamesLast[h] == "HLT_PFHT800_v2"                                   ) vfiredTrigger.push_back( 1 );
  			   if( pathNamesLast[h] == "HLT_PFHT800_v3"                                   ) vfiredTrigger.push_back( 2 );
  			   if( pathNamesLast[h] == "HLT_PFHT900_v1"                                   ) vfiredTrigger.push_back( 3 );
  			   if( pathNamesLast[h] == "HLT_PFHT900_v2"                                   ) vfiredTrigger.push_back( 4 );
  			   if( pathNamesLast[h] == "HLT_PFHT900_v3"                                   ) vfiredTrigger.push_back( 5 );
  			   if( pathNamesLast[h] == "HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_PFMET40_v1" ) vfiredTrigger.push_back( 6 );
  			   if( pathNamesLast[h] == "HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_PFMET40_v2" ) vfiredTrigger.push_back( 7 );
  			   if( pathNamesLast[h] == "HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_PFMET40_v3" ) vfiredTrigger.push_back( 8 );
  			   if( pathNamesLast[h] == "HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_VBF_v1"     ) vfiredTrigger.push_back( 9 );
  			   if( pathNamesLast[h] == "HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_VBF_v2"     ) vfiredTrigger.push_back( 10 );
  			   if( pathNamesLast[h] == "HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_VBF_v3"     ) vfiredTrigger.push_back( 11 );
  			   if( pathNamesLast[h] == "HLT_Photon22_R9Id90_HE10_IsoM_v1"                 ) vfiredTrigger.push_back( 12 );
  			   if( pathNamesLast[h] == "HLT_Photon22_R9Id90_HE10_IsoM_v2"                 ) vfiredTrigger.push_back( 13 );
  			   if( pathNamesLast[h] == "HLT_Photon22_R9Id90_HE10_IsoM_v3"                 ) vfiredTrigger.push_back( 14 );
  			   if( pathNamesLast[h] == "HLT_Photon22_v1"                                  ) vfiredTrigger.push_back( 15 );
  			   if( pathNamesLast[h] == "HLT_Photon22_v2"                                  ) vfiredTrigger.push_back( 16 );
  			   if( pathNamesLast[h] == "HLT_Photon22_v3"                                  ) vfiredTrigger.push_back( 17 );
  			   if( pathNamesLast[h] == "HLT_Photon30_R9Id90_HE10_IsoM_v1"                 ) vfiredTrigger.push_back( 18 );
  			   if( pathNamesLast[h] == "HLT_Photon30_R9Id90_HE10_IsoM_v2"                 ) vfiredTrigger.push_back( 19 );
  			   if( pathNamesLast[h] == "HLT_Photon30_R9Id90_HE10_IsoM_v3"                 ) vfiredTrigger.push_back( 20 );
  			   if( pathNamesLast[h] == "HLT_Photon30_v1"                                  ) vfiredTrigger.push_back( 21 );
  			   if( pathNamesLast[h] == "HLT_Photon30_v2"                                  ) vfiredTrigger.push_back( 22 );
  			   if( pathNamesLast[h] == "HLT_Photon30_v3"                                  ) vfiredTrigger.push_back( 23 );
  			   if( pathNamesLast[h] == "HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_PFMET40_v1" ) vfiredTrigger.push_back( 24 );
  			   if( pathNamesLast[h] == "HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_PFMET40_v2" ) vfiredTrigger.push_back( 25 );
  			   if( pathNamesLast[h] == "HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_PFMET40_v3" ) vfiredTrigger.push_back( 26 );
  			   if( pathNamesLast[h] == "HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_VBF_v1"     ) vfiredTrigger.push_back( 27 );
  			   if( pathNamesLast[h] == "HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_VBF_v2"     ) vfiredTrigger.push_back( 28 );
  			   if( pathNamesLast[h] == "HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_VBF_v3"     ) vfiredTrigger.push_back( 29 );
  			   if( pathNamesLast[h] == "HLT_Photon36_R9Id90_HE10_IsoM_v1"                 ) vfiredTrigger.push_back( 30 );
  			   if( pathNamesLast[h] == "HLT_Photon36_R9Id90_HE10_IsoM_v2"                 ) vfiredTrigger.push_back( 31 );
  			   if( pathNamesLast[h] == "HLT_Photon36_R9Id90_HE10_IsoM_v3"                 ) vfiredTrigger.push_back( 32 );
  			   if( pathNamesLast[h] == "HLT_Photon36_v1"                                  ) vfiredTrigger.push_back( 33 );
  			   if( pathNamesLast[h] == "HLT_Photon36_v2"                                  ) vfiredTrigger.push_back( 34 );
  			   if( pathNamesLast[h] == "HLT_Photon36_v3"                                  ) vfiredTrigger.push_back( 35 );
  			   if( pathNamesLast[h] == "HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_PFMET40_v1" ) vfiredTrigger.push_back( 36 );
  			   if( pathNamesLast[h] == "HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_PFMET40_v2" ) vfiredTrigger.push_back( 37 );
  			   if( pathNamesLast[h] == "HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_PFMET40_v3" ) vfiredTrigger.push_back( 38 );
  			   if( pathNamesLast[h] == "HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_VBF_v1"     ) vfiredTrigger.push_back( 39 );
  			   if( pathNamesLast[h] == "HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_VBF_v2"     ) vfiredTrigger.push_back( 40 );
  			   if( pathNamesLast[h] == "HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_VBF_v3"     ) vfiredTrigger.push_back( 41 );
  			   if( pathNamesLast[h] == "HLT_Photon50_R9Id90_HE10_IsoM_v1"                 ) vfiredTrigger.push_back( 42 );
  			   if( pathNamesLast[h] == "HLT_Photon50_R9Id90_HE10_IsoM_v2"                 ) vfiredTrigger.push_back( 43 );
  			   if( pathNamesLast[h] == "HLT_Photon50_R9Id90_HE10_IsoM_v3"                 ) vfiredTrigger.push_back( 44 );
  			   if( pathNamesLast[h] == "HLT_Photon50_v1"                                  ) vfiredTrigger.push_back( 45 );
  			   if( pathNamesLast[h] == "HLT_Photon50_v2"                                  ) vfiredTrigger.push_back( 46 );
  			   if( pathNamesLast[h] == "HLT_Photon50_v3"                                  ) vfiredTrigger.push_back( 47 );
  			   if( pathNamesLast[h] == "HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_PFMET40_v1" ) vfiredTrigger.push_back( 48 );
  			   if( pathNamesLast[h] == "HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_PFMET40_v2" ) vfiredTrigger.push_back( 49 );
  			   if( pathNamesLast[h] == "HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_PFMET40_v3" ) vfiredTrigger.push_back( 50 );
  			   if( pathNamesLast[h] == "HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_VBF_v1"     ) vfiredTrigger.push_back( 51 );
  			   if( pathNamesLast[h] == "HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_VBF_v2"     ) vfiredTrigger.push_back( 52 );
  			   if( pathNamesLast[h] == "HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_VBF_v3"     ) vfiredTrigger.push_back( 53 );
  			   if( pathNamesLast[h] == "HLT_Photon75_R9Id90_HE10_IsoM_v1"                 ) vfiredTrigger.push_back( 54 );
  			   if( pathNamesLast[h] == "HLT_Photon75_R9Id90_HE10_IsoM_v2"                 ) vfiredTrigger.push_back( 55 );
  			   if( pathNamesLast[h] == "HLT_Photon75_R9Id90_HE10_IsoM_v3"                 ) vfiredTrigger.push_back( 56 );
  			   if( pathNamesLast[h] == "HLT_Photon75_v1"                                  ) vfiredTrigger.push_back( 57 );
  			   if( pathNamesLast[h] == "HLT_Photon75_v2"                                  ) vfiredTrigger.push_back( 58 );
  			   if( pathNamesLast[h] == "HLT_Photon75_v3"                                  ) vfiredTrigger.push_back( 59 );
  			   if( pathNamesLast[h] == "HLT_Photon90_CaloIdL_PFHT500_v1"                  ) vfiredTrigger.push_back( 60 );
  			   if( pathNamesLast[h] == "HLT_Photon90_CaloIdL_PFHT500_v2"                  ) vfiredTrigger.push_back( 61 );
  			   if( pathNamesLast[h] == "HLT_Photon90_CaloIdL_PFHT500_v3"                  ) vfiredTrigger.push_back( 62 );
  			   if( pathNamesLast[h] == "HLT_Photon90_CaloIdL_PFHT600_v1"                  ) vfiredTrigger.push_back( 63 );
  			   if( pathNamesLast[h] == "HLT_Photon90_CaloIdL_PFHT600_v2"                  ) vfiredTrigger.push_back( 64 );
  			   if( pathNamesLast[h] == "HLT_Photon90_CaloIdL_PFHT600_v3"                  ) vfiredTrigger.push_back( 65 );
  			   if( pathNamesLast[h] == "HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_PFMET40_v1" ) vfiredTrigger.push_back( 66 );
  			   if( pathNamesLast[h] == "HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_PFMET40_v2" ) vfiredTrigger.push_back( 67 );
  			   if( pathNamesLast[h] == "HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_PFMET40_v3" ) vfiredTrigger.push_back( 68 );
  			   if( pathNamesLast[h] == "HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_VBF_v1"     ) vfiredTrigger.push_back( 69 );
  			   if( pathNamesLast[h] == "HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_VBF_v2"     ) vfiredTrigger.push_back( 70 );
  			   if( pathNamesLast[h] == "HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_VBF_v3"     ) vfiredTrigger.push_back( 71 );
  			   if( pathNamesLast[h] == "HLT_Photon90_R9Id90_HE10_IsoM_v1"                 ) vfiredTrigger.push_back( 72 );
  			   if( pathNamesLast[h] == "HLT_Photon90_R9Id90_HE10_IsoM_v2"                 ) vfiredTrigger.push_back( 73 );
  			   if( pathNamesLast[h] == "HLT_Photon90_R9Id90_HE10_IsoM_v3"                 ) vfiredTrigger.push_back( 74 );
  			   if( pathNamesLast[h] == "HLT_Photon90_v1"                                  ) vfiredTrigger.push_back( 75 );
  			   if( pathNamesLast[h] == "HLT_Photon90_v2"                                  ) vfiredTrigger.push_back( 76 );
  			   if( pathNamesLast[h] == "HLT_Photon90_v3"                                  ) vfiredTrigger.push_back( 77 );
  			   if( pathNamesLast[h] == "HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40_v1") vfiredTrigger.push_back( 78 );
  			   if( pathNamesLast[h] == "HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40_v2") vfiredTrigger.push_back( 79 );
  			   if( pathNamesLast[h] == "HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40_v3") vfiredTrigger.push_back( 80 );
  			   if( pathNamesLast[h] == "HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_VBF_v1"    ) vfiredTrigger.push_back( 81 );
  			   if( pathNamesLast[h] == "HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_VBF_v2"    ) vfiredTrigger.push_back( 82 );
  			   if( pathNamesLast[h] == "HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_VBF_v3"    ) vfiredTrigger.push_back( 83 );
  			   if( pathNamesLast[h] == "HLT_Photon120_R9Id90_HE10_IsoM_v1"                ) vfiredTrigger.push_back( 84 );
  			   if( pathNamesLast[h] == "HLT_Photon120_R9Id90_HE10_IsoM_v2"                ) vfiredTrigger.push_back( 85 );
  			   if( pathNamesLast[h] == "HLT_Photon120_R9Id90_HE10_IsoM_v3"                ) vfiredTrigger.push_back( 86 );
  			   if( pathNamesLast[h] == "HLT_Photon120_v1"                                 ) vfiredTrigger.push_back( 87 );
  			   if( pathNamesLast[h] == "HLT_Photon120_v2"                                 ) vfiredTrigger.push_back( 88 );
  			   if( pathNamesLast[h] == "HLT_Photon120_v3"                                 ) vfiredTrigger.push_back( 89 );
  			   if( pathNamesLast[h] == "HLT_Photon135_PFMET100_v1"                        ) vfiredTrigger.push_back( 90 );
  			   if( pathNamesLast[h] == "HLT_Photon135_PFMET100_v2"                        ) vfiredTrigger.push_back( 91 );
  			   if( pathNamesLast[h] == "HLT_Photon135_PFMET100_v3"                        ) vfiredTrigger.push_back( 92 );
  			   if( pathNamesLast[h] == "HLT_Photon165_HE10_v1"                            ) vfiredTrigger.push_back( 93 );
  			   if( pathNamesLast[h] == "HLT_Photon165_HE10_v2"                            ) vfiredTrigger.push_back( 94 );
  			   if( pathNamesLast[h] == "HLT_Photon165_HE10_v3"                            ) vfiredTrigger.push_back( 95 );
  			   if( pathNamesLast[h] == "HLT_Photon165_R9Id90_HE10_IsoM_v1"                ) vfiredTrigger.push_back( 96 );
  			   if( pathNamesLast[h] == "HLT_Photon165_R9Id90_HE10_IsoM_v2"                ) vfiredTrigger.push_back( 97 );
  			   if( pathNamesLast[h] == "HLT_Photon165_R9Id90_HE10_IsoM_v3"                ) vfiredTrigger.push_back( 98 );
  			   if( pathNamesLast[h] == "HLT_Photon175_v1"                                 ) vfiredTrigger.push_back( 99 );
  			   if( pathNamesLast[h] == "HLT_Photon175_v2"                                 ) vfiredTrigger.push_back( 100 );
  			   if( pathNamesLast[h] == "HLT_Photon175_v3"                                 ) vfiredTrigger.push_back( 101 );
  			   if( pathNamesLast[h] == "HLT_Photon250_NoHE_v1"                            ) vfiredTrigger.push_back( 102 );
  			   if( pathNamesLast[h] == "HLT_Photon250_NoHE_v2"                            ) vfiredTrigger.push_back( 103 );
  			   if( pathNamesLast[h] == "HLT_Photon250_NoHE_v3"                            ) vfiredTrigger.push_back( 104 );
  			   if( pathNamesLast[h] == "HLT_Photon300_NoHE_v1"                            ) vfiredTrigger.push_back( 105 );
  			   if( pathNamesLast[h] == "HLT_Photon300_NoHE_v2"                            ) vfiredTrigger.push_back( 106 );
  			   if( pathNamesLast[h] == "HLT_Photon300_NoHE_v3"                            ) vfiredTrigger.push_back( 107 );
  			   if( pathNamesLast[h] == "HLT_Photon500_v1"                                 ) vfiredTrigger.push_back( 108 );
  			   if( pathNamesLast[h] == "HLT_Photon500_v2"                                 ) vfiredTrigger.push_back( 109 );
  			   if( pathNamesLast[h] == "HLT_Photon500_v3"                                 ) vfiredTrigger.push_back( 110 );
  			   if( pathNamesLast[h] == "HLT_Photon600_v1"                                 ) vfiredTrigger.push_back( 111 );
  			   if( pathNamesLast[h] == "HLT_Photon600_v2"                                 ) vfiredTrigger.push_back( 112 );
  			   if( pathNamesLast[h] == "HLT_Photon600_v3"                                 ) vfiredTrigger.push_back( 113 );
  			   // else vfiredTrigger.push_back( -99 );
  			}
			
  		}
		
  		nBranches_->triggerObject_filterIDs.push_back(vfilterIDs);
  		nBranches_->triggerObject_firedTrigger.push_back(vfiredTrigger);
		
  	}
  } //doTriggerObjects_


  // HLT Noise Filters
  // for deprecation see https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2
  if (doHltFilters_) {

    event.getByToken(noiseFilterToken_, noiseFilterBits_);
    const edm::TriggerNames &names = event.triggerNames(*noiseFilterBits_);
  
    for (unsigned int i = 0, n = noiseFilterBits_->size(); i < n; ++i) {
      if (names.triggerName(i) == HBHENoiseFilter_Selector_)
        nBranches_->passFilter_HBHE_ = noiseFilterBits_->accept(i);
      if (names.triggerName(i) == CSCHaloNoiseFilter_Selector_)
        nBranches_->passFilter_CSCHalo_ = noiseFilterBits_->accept(i); // DEPRECATED	
      if (names.triggerName(i) == CSCTightHalo2015Filter_Selector_)
        nBranches_->passFilter_CSCTightHalo2015_ = noiseFilterBits_->accept(i); // TO BE USED
      if (names.triggerName(i) == HCALlaserNoiseFilter_Selector_)
        nBranches_->passFilter_HCALlaser_ = noiseFilterBits_->accept(i); // DEPRECATED
      if (names.triggerName(i) == ECALDeadCellNoiseFilter_Selector_)
        nBranches_->passFilter_ECALDeadCell_ = noiseFilterBits_->accept(i); // under scrutiny
      if (names.triggerName(i) == GoodVtxNoiseFilter_Selector_)
        nBranches_->passFilter_GoodVtx_ = noiseFilterBits_->accept(i); // TO BE USED
      if (names.triggerName(i) == TrkFailureNoiseFilter_Selector_)
        nBranches_->passFilter_TrkFailure_ = noiseFilterBits_->accept(i); // DEPRECATED
      if (names.triggerName(i) == EEBadScNoiseFilter_Selector_)
        nBranches_->passFilter_EEBadSc_ = noiseFilterBits_->accept(i); // under scrutiny
      if (names.triggerName(i) == ECALlaserNoiseFilter_Selector_)
        nBranches_->passFilter_ECALlaser_ = noiseFilterBits_->accept(i); // DEPRECATED
      if (names.triggerName(i) == TrkPOGNoiseFilter_Selector_)
        nBranches_->passFilter_TrkPOG_ = noiseFilterBits_->accept(i); // DEPRECATED
      if (names.triggerName(i) == TrkPOG_manystrip_NoiseFilter_Selector_)
        nBranches_->passFilter_TrkPOG_manystrip_ = noiseFilterBits_->accept(i); // DEPRECATED
      if (names.triggerName(i) == TrkPOG_toomanystrip_NoiseFilter_Selector_)
        nBranches_->passFilter_TrkPOG_toomanystrip_ = noiseFilterBits_->accept(i); // DEPRECATED
      if (names.triggerName(i) == TrkPOG_logError_NoiseFilter_Selector_)
        nBranches_->passFilter_TrkPOG_logError_ = noiseFilterBits_->accept(i); // DEPRECATED
      if (names.triggerName(i) == METFilters_Selector_)
        nBranches_->passFilter_METFilters_ = noiseFilterBits_->accept(i); // DEPRECATED
       //NEW FOR ICHEP
      if (names.triggerName(i) == CSCTightHaloTrkMuUnvetoFilter_Selector_)
        nBranches_->passFilter_CSCTightHaloTrkMuUnvetoFilter_ = noiseFilterBits_->accept(i);
      if (names.triggerName(i) == globalTightHalo2016Filter_Selector_           )
        nBranches_->passFilter_globalTightHalo2016_ = noiseFilterBits_->accept(i); // TO BE USED FOR ICHEP 2016
      if (names.triggerName(i) == HcalStripHaloFilter_Selector_                 )
        nBranches_->passFilter_HcalStripHalo_ = noiseFilterBits_->accept(i);
      if (names.triggerName(i) == chargedHadronTrackResolutionFilter_Selector_  )
        nBranches_->passFilter_chargedHadronTrackResolution_ = noiseFilterBits_->accept(i); // TO BE USED FOR ICHEP 2016
      if (names.triggerName(i) == muonBadTrackFilter_Selector_                  )
        nBranches_->passFilter_muonBadTrack_ = noiseFilterBits_->accept(i); // TO BE USED FOR ICHEP 2016
      //NEW FOR MORIOND
      if (names.triggerName(i) == badMuons_Selector_                  )
        nBranches_->flag_badMuons_ = noiseFilterBits_->accept(i); // TO BE USED FOR ICHEP 2016

      if (names.triggerName(i) == duplicateMuons_Selector_                  )
        nBranches_->flag_duplicateMuons_ = noiseFilterBits_->accept(i); // TO BE USED FOR ICHEP 2016

      if (names.triggerName(i) == nobadMuons_Selector_                  )
        nBranches_->flag_nobadMuons_ = noiseFilterBits_->accept(i); // TO BE USED FOR ICHEP 2016

    }

    //if( !runOnMC_ /*&& event.id().run() < 251585*/ ){

       edm::Handle<bool> HBHENoiseFilterLooseResultHandle;
       event.getByToken(HBHENoiseFilterLoose_Selector_, HBHENoiseFilterLooseResultHandle);
       bool HBHENoiseFilterLooseResult = *HBHENoiseFilterLooseResultHandle;
       if (!HBHENoiseFilterLooseResultHandle.isValid()) {
         LogDebug("") << "CaloTowerAnalyzer: Could not find HBHENoiseFilterResult" << std::endl;
       }

       nBranches_->passFilter_HBHELoose_ = HBHENoiseFilterLooseResult;

       edm::Handle<bool> HBHENoiseFilterTightResultHandle;
       event.getByToken(HBHENoiseFilterTight_Selector_, HBHENoiseFilterTightResultHandle);
       bool HBHENoiseFilterTightResult = *HBHENoiseFilterTightResultHandle;
       if (!HBHENoiseFilterTightResultHandle.isValid()) {
         LogDebug("") << "CaloTowerAnalyzer: Could not find HBHENoiseFilterResult" << std::endl;
       }

       nBranches_->passFilter_HBHETight_ = HBHENoiseFilterTightResult;

        edm::Handle<bool> HBHENoiseIsoFilterResultHandle;
       event.getByToken(HBHENoiseIsoFilter_Selector_, HBHENoiseIsoFilterResultHandle);
       bool HBHENoiseIsoFilterResult = *HBHENoiseIsoFilterResultHandle;
       if (!HBHENoiseIsoFilterResultHandle.isValid()) {
         LogDebug("") << "CaloTowerAnalyzer: Could not find HBHENoiseFilterResult" << std::endl;
       }

       nBranches_->passFilter_HBHEIso_ = HBHENoiseIsoFilterResult;

    //}

  } //doHltFilters_
}
