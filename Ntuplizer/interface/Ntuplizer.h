#include <memory>
#include "DataFormats/METReco/interface/METCollection.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "SimDataFormats/JetMatching/interface/JetFlavourMatching.h"
#include "SimDataFormats/JetMatching/interface/JetFlavour.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "../interface/NtupleBranches.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "GeneratorInterface/LHEInterface/interface/LHEEvent.h"
class NtupleBranches;
class CandidateNtuplizer;

class Ntuplizer : public edm::EDAnalyzer {
public:
  explicit Ntuplizer(const edm::ParameterSet&);
  ~Ntuplizer();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob()                                                                   override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&)                           override;
  virtual void endJob()                                                                     override;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&)                            override;
  virtual void endRun(edm::Run const&, edm::EventSetup const&)                              override;
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)    override;
  virtual void endLuminosityBlock(edm::LuminosityBlock const  &, edm::EventSetup const&)    override;
  
  // ----------member data ---------------------------
  
  NtupleBranches* nBranches_;
  std::map<std::string,CandidateNtuplizer*>                 nTuplizers_         ;
  
  edm::EDGetTokenT<reco::VertexCollection>                  vtxToken_           ;
  edm::EDGetTokenT<double>                                  rhoToken_           ;
  edm::EDGetTokenT<pat::PackedCandidateCollection>          packedpfcandidatesToken_;

  edm::EDGetTokenT< std::vector<PileupSummaryInfo> >        puinfoToken_        ;
  edm::EDGetTokenT< GenEventInfoProduct >                   geneventToken_      ;
  edm::EDGetTokenT<LHEEventProduct>	                    lheEventProductToken_;
  
  edm::EDGetTokenT<reco::GenParticleCollection>             genparticleToken_   ;
  edm::EDGetTokenT<bool>                                    tauspinnerWTisValidToken_;
  edm::EDGetTokenT<double>                                  tauspinnerWTToken_;
  edm::EDGetTokenT<double>                                  tauspinnerWThminusToken_;
  edm::EDGetTokenT<double>                                  tauspinnerWThplusToken_;
  edm::EDGetTokenT<double>                                  tauspinnerTauPolFromZToken_;
  edm::EDGetTokenT<double>                                  tauspinnerWRightToken_;
  edm::EDGetTokenT<double>                                  tauspinnerWLeftToken_;
  edm::EDGetTokenT<double>                                  tauspinnerIsRightLeftToken_;

  
  edm::EDGetTokenT<pat::JetCollection>                      jetToken_           ;
  edm::EDGetTokenT<pat::JetCollection>                      fatjetToken_        ;
  edm::EDGetTokenT<pat::JetCollection>                      prunedjetToken_     ;
  edm::EDGetTokenT<pat::JetCollection>                      softdropjetToken_   ;
  edm::EDGetTokenT<pat::JetCollection>                      trimmedjetToken_     ;
  edm::EDGetTokenT<pat::JetCollection>                      puppijetToken_     ;
  edm::EDGetTokenT<pat::JetCollection>                      puppiprunedjetToken_     ;
  edm::EDGetTokenT<pat::JetCollection>                      puppisoftdropjetToken_     ;
  edm::EDGetTokenT<reco::GenJetCollection>                  genJetToken_	;
  edm::EDGetTokenT<pat::JetCollection>                      genJetAK8Token_	;
  

  edm::EDGetTokenT<reco::JetFlavourMatchingCollection> 	    flavourToken_	;
  edm::EDGetToken                                           photonToken_	;
  edm::EDGetTokenT<edm::ValueMap<bool> >                    phoLooseIdMapToken_ ;
  edm::EDGetTokenT<edm::ValueMap<bool> >                    phoMediumIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >                    phoTightIdMapToken_ ;
  edm::EDGetTokenT<edm::ValueMap<float> >                   phoMvaValuesMapToken_;
  edm::EDGetTokenT<edm::ValueMap<int> >                     phoMvaCategoriesMapToken_;
  bool                                                      phoVerboseIdFlag_;

  edm::EDGetTokenT<pat::MuonCollection>     		    muonToken_  	;	
  edm::EDGetTokenT<edm::View<pat::Electron> >		    electronToken_	;
  edm::EDGetTokenT<edm::ValueMap<bool> >                    eleVetoIdMapToken_  ;
  edm::EDGetTokenT<edm::ValueMap<bool> >                    eleLooseIdMapToken_ ;
  edm::EDGetTokenT<edm::ValueMap<bool> >                    eleMediumIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >                    eleTightIdMapToken_ ;
  edm::EDGetTokenT<edm::ValueMap<bool> >                    eleHLTIdMapToken_  ;
  edm::EDGetTokenT<edm::ValueMap<bool> >                    eleHEEPIdMapToken_  ;
  edm::EDGetTokenT<edm::ValueMap<bool> >                    eleMVAMediumIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >                    eleMVATightIdMapToken_ ;
  edm::EDGetTokenT<edm::ValueMap<float> >                   mvaValuesMapToken_;
  edm::EDGetTokenT<edm::ValueMap<int> >                     mvaCategoriesMapToken_;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit>>> ebRecHitsToken_;
  edm::EDGetTokenT<pat::TauCollection> 	    		    tauToken_		;
  edm::EDGetTokenT<pat::TauCollection> 	    		    tauBoostedTauToken_	;


  edm::EDGetTokenT<pat::METCollection> 	    		    metToken_		;
  edm::EDGetTokenT<pat::METCollection> 	    		    metpuppiToken_		;
  edm::EDGetTokenT<pat::METCollection> 	    		    metmvaToken_		;
  edm::EDGetTokenT<double> 	    		            metSigToken_		;
  edm::EDGetTokenT<math::Error<2>::type> 	     	    metCovToken_		;
  edm::EDGetTokenT<pat::JetCollection>                      jetForMetCorrToken_ ;
  
  edm::EDGetTokenT<edm::TriggerResults>                     triggerToken_       ;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection>  triggerObjects_     ;
  edm::EDGetTokenT<pat::PackedTriggerPrescales>             triggerPrescales_   ;
  
  edm::EDGetTokenT<edm::TriggerResults>                     noiseFilterToken_;
  edm::EDGetTokenT<bool>                                    HBHENoiseFilterLooseResultToken_;
  edm::EDGetTokenT<bool>                                    HBHENoiseFilterTightResultToken_;
  edm::EDGetTokenT<bool>                                    HBHENoiseIsoFilterResultToken_;  

};
