#include "../interface/PhotonsNtuplizer.h"
#include <memory>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/View.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TTree.h"
#include "Math/VectorUtil.h"

//===================================================================================================================
PhotonsNtuplizer::PhotonsNtuplizer(NtupleBranches*                                        nBranches    ,
                                   edm::EDGetToken                                        photonToken  ,
                                   edm::EDGetTokenT<reco::VertexCollection>               verticeToken ,
                                   edm::EDGetTokenT<double>                               rhoToken     ,
                                   std::vector< edm::EDGetTokenT<edm::ValueMap<bool> > >  phoIDtokens,
                                   std::vector<edm::EDGetTokenT<edm::ValueMap<float> > > phoIDtokens1,
                                   std::vector<edm::EDGetTokenT<edm::ValueMap<int> > > phoIDtokens2
                                   
                                   )
/* Stuff for cut based id as in SimplePhotonNtupler example
 // edm::EDGetTokenT<edm::ValueMap<float> >              full5x5SigmaIEtaIEtaMapToken,
 // edm::EDGetTokenT<edm::ValueMap<float> >              phoChargedIsolationToken,
 // edm::EDGetTokenT<edm::ValueMap<float> >              phoNeutralHadronIsolationToken,
 // edm::EDGetTokenT<edm::ValueMap<float> >              phoPhotonIsolationToken,
 */
: CandidateNtuplizer                ( nBranches      )
, photonToken_                      ( photonToken    )
, verticeToken_	                    ( verticeToken   )
, rhoToken_	                        ( rhoToken	     )
, photonLooseIdMapToken_            ( phoIDtokens[0] )
, photonMediumIdMapToken_           ( phoIDtokens[1] )
//, photonMediumIdFullInfoMapToken_   ( phoIDtokens[2] )
, photonTightIdMapToken_            ( phoIDtokens[2] )
, photonMvaValuesMapToken_          ( phoIDtokens1[0] )
, photonMvaCategoriesMapToken_       ( phoIDtokens2[0] )

{
    
}

//===================================================================================================================
PhotonsNtuplizer::~PhotonsNtuplizer( void )
{
    
}

//===================================================================================================================
//float PhotonsNtuplizer::dEtaInSeed( const reco::Photon &pho ){
//  // TODO do we need this?
//	return pho.superCluster().isNonnull() && pho.superCluster()->seed().isNonnull() ? pho.deltaEtaSuperClusterTrackAtVtx()
//    - pho.superCluster()->eta() + pho.superCluster()->seed()->eta() : std::numeric_limits<float>::max();
//}


//===================================================================================================================
void PhotonsNtuplizer::fillBranches( edm::Event const & event, const edm::EventSetup& iSetup ){
    
    event.getByToken(photonToken_                     , photons                );
    event.getByToken(verticeToken_                    , vertices_              );
    event.getByToken(rhoToken_	                       , rho_                   );
    
    event.getByToken(photonLooseIdMapToken_           , loose_id_decisions     );
    event.getByToken(photonMediumIdMapToken_          , medium_id_decisions    );
    //event.getByToken(photonMediumIdFullInfoMapToken_  , medium_id_cutflow_data );
    event.getByToken(photonMvaValuesMapToken_         , mvaValues              );
    event.getByToken(photonMvaCategoriesMapToken_     , mvaCategories          );
    event.getByToken(photonTightIdMapToken_           , tight_id_decisions     );
    
    /*   Vertex stuff -- need this?
     // Find the first vertex in the collection that passes good quality criteria
     // reco::VertexCollection::const_iterator firstGoodVertex = vertices_->end();
     //reco::VertexCollection::const_iterator firstGoodVertex = vertices_->begin();
     //int firstGoodVertexIdx = 0;
     //for( reco::VertexCollection::const_iterator vtx = vertices_->begin(); vtx != vertices_->end(); ++vtx, ++firstGoodVertexIdx){
     //  bool isFake = (vtx->chi2()==0 && vtx->ndof()==0);
     //  // Check the goodness
     //  if( !isFake && vtx->ndof()>=4. && vtx->position().Rho()<=2.0 && fabs(vtx->position().Z())<=24.0) {
     //    firstGoodVertex = vtx;
     //    break;
     //  }
     //
     //}
     */
    int npho = 0;
    
    for (size_t i=0; i < photons->size(); ++i) {
        const auto pho=photons->ptrAt(i);
        if (pho->pt() < 15 ) continue;
        nBranches_->ph_pdgId	           .push_back(pho->pdgId());
        nBranches_->ph_charge	           .push_back(pho->charge());
        nBranches_->ph_e	    	         .push_back(pho->energy());
        nBranches_->ph_eta 	             .push_back(pho->eta());
        nBranches_->ph_phi 	             .push_back(pho->phi());
        nBranches_->ph_superCluster_eta  .push_back(pho->superCluster()->eta());
        nBranches_->ph_superCluster_phi  .push_back(pho->superCluster()->phi());
        nBranches_->ph_mass	   	         .push_back(pho->mass());
        nBranches_->ph_px                .push_back(pho->px());
        nBranches_->ph_py                .push_back(pho->py());
        nBranches_->ph_pz                .push_back(pho->pz());
        nBranches_->ph_pt  	   	         .push_back(pho->pt());
        nBranches_->ph_et  	   	         .push_back(pho->et());
        
        /*======= ISO ==========*/
        //double rho = *(rho_.product());
        
        /*======= IDs ==========*/
        //float et = pho.energy()!=0. ? pho.et()/pho.energy()*pho.caloEnergy() : 0.;
        bool isPassLoose = (*loose_id_decisions)[pho];
        bool isPassMedium = (*medium_id_decisions)[pho];
        bool isPassTight = (*tight_id_decisions)[pho];
        nBranches_->ph_passLooseId.push_back ( (int)isPassLoose );
        nBranches_->ph_passMediumId.push_back ( (int)isPassMedium );
        nBranches_->ph_passTightId.push_back ( (int)isPassTight );
        ++npho;
        
    }
    
    nBranches_->ph_N = npho;
    
}

