#ifndef PhotonsNtuplizer_H
#define PhotonsNtuplizer_H

#include "../interface/CandidateNtuplizer.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"


class PhotonsNtuplizer : public CandidateNtuplizer {

public:
  PhotonsNtuplizer(   NtupleBranches*                                      nBranches      , 
                      edm::EDGetToken                                      photonToken    , 
                      edm::EDGetTokenT<reco::VertexCollection>             verticeToken   , 
                      edm::EDGetTokenT<double>                             rhoToken       ,
                      std::vector<edm::EDGetTokenT<edm::ValueMap<bool> > > phoIDtokens      );
  ~PhotonsNtuplizer( void );
  
  void fillBranches( edm::Event const & event, const edm::EventSetup& iSetup );
  
  //float dEtaInSeed( const reco::Photon &pho );
  bool  phoIDpassed( std::string id, const reco::Photon &pho );
  
private:
   edm::EDGetToken                           photonToken_;
   edm::EDGetTokenT<reco::VertexCollection>  verticeToken_ ;
   edm::EDGetTokenT<double>                  rhoToken_     ;   
   //edm::EDGetTokenT<edm::ValueMap<bool> >    photonVetoIdMapToken_;  
   edm::EDGetTokenT<edm::ValueMap<bool> >    photonLooseIdMapToken_; 
   edm::EDGetTokenT<edm::ValueMap<bool> >    photonMediumIdMapToken_;
   edm::EDGetTokenT<edm::ValueMap<bool> >    photonTightIdMapToken_;
   //edm::EDGetTokenT<edm::ValueMap<bool> >    photonHEEPIdMapToken_;
   //edm::EDGetTokenT<edm::ValueMap<bool> >    photonHEEPId51MapToken_;
   
   edm::Handle<edm::View<reco::Photon> >     photons    ;
   edm::Handle<reco::VertexCollection> 	     vertices_     ;
   edm::Handle<double>                       rho_	   ;
   //edm::Handle<edm::ValueMap<float> >        mvaValues;
   //edm::Handle<edm::ValueMap<int> >          mvaCategories;
   edm::Handle<edm::ValueMap<bool> >         loose_id_decisions; 
   edm::Handle<edm::ValueMap<bool> >         medium_id_decisions;
   edm::Handle<edm::ValueMap<bool> >         tight_id_decisions;
      
};

#endif // PhotonsNtuplizer_H
