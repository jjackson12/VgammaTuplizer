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
PhotonsNtuplizer::PhotonsNtuplizer(NtupleBranches*                                        nBranches      ,
                                   edm::EDGetToken                                        photonToken    ,
                                   edm::EDGetTokenT<reco::VertexCollection>               verticeToken   ,
                                   edm::EDGetTokenT<double>                               rhoToken       ,
                                   std::vector< edm::EDGetTokenT<edm::ValueMap<bool> > >  phoIDtokens    ,
                                   std::vector<edm::EDGetTokenT<edm::ValueMap<float> > >  phoIDtokens1   ,
                                   std::vector<edm::EDGetTokenT<edm::ValueMap<int> > >    phoIDtokens2   ,
                                   std::vector<edm::EDGetTokenT<EcalRecHitCollection> >   phoIDtokens3   ,
    )
  /* Stuff for cut based id as in SimplePhotonNtupler example
  // edm::EDGetTokenT<edm::ValueMap<float> >              full5x5SigmaIEtaIEtaMapToken,
  // edm::EDGetTokenT<edm::ValueMap<float> >              phoChargedIsolationToken,
  // edm::EDGetTokenT<edm::ValueMap<float> >              phoNeutralHadronIsolationToken,
  // edm::EDGetTokenT<edm::ValueMap<float> >              phoPhotonIsolationToken,
  */
  : CandidateNtuplizer                ( nBranches       )
  , photonToken_                      ( photonToken     )
  , verticeToken_                     ( verticeToken    )
  , rhoToken_                         ( rhoToken        )
  , photonLooseIdMapToken_            ( phoIDtokens[0]  )
  , photonMediumIdMapToken_           ( phoIDtokens[1]  )
  , photonTightIdMapToken_            ( phoIDtokens[2]  )
  , photonMvaValuesMapToken_          ( phoIDtokens1[0] )
  , photonMvaCategoriesMapToken_      ( phoIDtokens2[0] )
  , ecalHitEBToken_                   ( phoIDtokens3[0] )
  , ecalHitEEToken_                   ( phoIDtokens3[1] )

{

}

//===================================================================================================================
PhotonsNtuplizer::~PhotonsNtuplizer( void )
{

}

//===================================================================================================================
void PhotonsNtuplizer::fillBranches( edm::Event const & event, const edm::EventSetup& iSetup ){

  event.getByToken(photonToken_                     , photons                );
  event.getByToken(verticeToken_                    , vertices_              );
  event.getByToken(rhoToken_                        , rho_                   );
  event.getByToken(photonLooseIdMapToken_           , loose_id_decisions     );
  event.getByToken(photonMediumIdMapToken_          , medium_id_decisions    );
  event.getByToken(photonTightIdMapToken_           , tight_id_decisions     );
  event.getByToken(photonMvaValuesMapToken_         , mvaValues              );
  event.getByToken(photonMvaCategoriesMapToken_     , mvaCategories          );
  event.getByToken(photonLooseIdMapToken_           , loose_id_decisions     );
  event.getByToken(photonMediumIdMapToken_          , medium_id_decisions    );
  event.getByToken(photonTightIdMapToken_           , tight_id_decisions     );
  event.getByToken(photonMvaValuesMapToken_         , mvaValues              );
  event.getByToken(photonMvaCategoriesMapToken_     , mvaCategories          );
  event.getByToken(ecalHitEBToken                   , EcalBarrelRecHits      );
  event.getByToken(ecalHitEEToken                   , EcalEndcapRecHits      );

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
    nBranches_->ph_pdgId              .push_back(pho->pdgId());
    nBranches_->ph_charge             .push_back(pho->charge());
    nBranches_->ph_e                  .push_back(pho->energy());
    nBranches_->ph_eta                .push_back(pho->eta());
    nBranches_->ph_phi                .push_back(pho->phi());
    nBranches_->ph_superCluster_eta   .push_back(pho->superCluster()->eta());
    nBranches_->ph_superCluster_phi   .push_back(pho->superCluster()->phi());
    nBranches_->ph_mass               .push_back(pho->mass());
    nBranches_->ph_px                 .push_back(pho->px());
    nBranches_->ph_py                 .push_back(pho->py());
    nBranches_->ph_pz                 .push_back(pho->pz());
    nBranches_->ph_pt                 .push_back(pho->pt());
    nBranches_->ph_et                 .push_back(pho->et());
 // TODO
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
    nBranches_->ph_mvaValue.push_back( (*mvaValues)[pho]);
    nBranches_->ph_mvaCategory.push_back( (*mvaCategories)[pho]);
    ++npho;



    DetId seedDetId = ( (pho->superCluster())->seed() )->seed();

    if(seedDetId.subdetId()==EcalEndcap) {

      int iNeigh=0; 

      CaloNavigator<DetId> cursorE = CaloNavigator<DetId>(seedDetId, theSubdetTopologyEE_ );

      for(int ix=-2; ix<3; ++ix) {
        for(int iy=-2; iy<3; ++iy) {
          cursorE.home();
          cursorE.offsetBy( ix, iy );
          DetId cryId = cursorE.pos();

          if(cryId.subdetId()!=EcalEndcap) { 
            nBranches_->ph_recHitAmplit.push_back( -5000.);
            nBranches_->ph_recHitIeta.push_back( -5000); 
            nBranches_->ph_recHitIphi.push_back( -5000);
            nBranches_->ph_recHitIx.push_back( -5000); 
            nBranches_->ph_recHitIy.push_back( -5000); 
            nBranches_->ph_recHitIz.push_back( -5000); 
            nBranches_->ph_recHitKsaturated.push_back( -5000);
            nBranches_->ph_recHitKleRecovered.push_back( -5000);
            nBranches_->ph_recHitamplitRecovered.push_back( -5000.);
            iNeigh++;
            continue;  
          }

          EcalRecHitCollection::const_iterator itneigh = EcalEndcapRecHits->find( cryId );

          if( itneigh != EcalEndcapRecHits->end() ) {
            nBranches_->ph_recHitAmplit.push_back( itneigh->energy() );
            nBranches_->ph_recHitIeta.push_back( -999); 
            nBranches_->ph_recHitIphi.push_back( -999); 
            nBranches_->ph_recHitIx.push_back( ((EEDetId)itneigh->detid()).ix() );
            nBranches_->ph_recHitIy.push_back( ((EEDetId)itneigh->detid()).iy() );
            nBranches_->ph_recHitIz.push_back( ((EEDetId)itneigh->detid()).zside() );
            nBranches_->ph_recHitKsaturated.push_back( itneigh->checkFlag(EcalRecHit::kSaturated));      
            nBranches_->ph_recHitKleRecovered.push_back = (itneigh->checkFlag(EcalRecHit::kLeadingEdgeRecovered));      

          } else {
            nBranches_->ph_recHitAmplit[iNeigh] = -2000.;
            nBranches_->ph_recHitIeta[iNeigh] = -2000; 
            nBranches_->ph_recHitIphi[iNeigh] = -2000;
            nBranches_->ph_recHitIx[iNeigh] = -2000; 
            nBranches_->ph_recHitIy[iNeigh] = -2000; 
            nBranches_->ph_recHitIz[iNeigh] = -2000; 
            nBranches_->ph_recHitKsaturated[iNeigh] = -2000;
            nBranches_->ph_recHitKleRecovered[iNeigh] = -2000;
            nBranches_->ph_recHitamplitRecovered[iNeigh] = -2000.;
          }

          iNeigh++;
        }
      }
      if (iNeigh!=25) cout << "problem: not 25 crystals!  ==> " << iNeigh << endl;

    } else if (seedDetId.subdetId()==EcalBarrel) { // TODO

      int iNeigh=0; 

      CaloNavigator<DetId> cursorE = CaloNavigator<DetId>(seedDetId, theSubdetTopologyEB_ );

      for(int ix=-2; ix<3; ++ix) {
        for(int iy=-2; iy<3; ++iy) {
          cursorE.home();
          cursorE.offsetBy( ix, iy );
          DetId cryId = cursorE.pos();

          if(cryId.subdetId()!=EcalBarrel) { 
            tree_.amplit[iNeigh] = -5000.;
            tree_.ieta[iNeigh] = -5000; 
            tree_.iphi[iNeigh] = -5000;
            tree_.ix[iNeigh] = -5000; 
            tree_.iy[iNeigh] = -5000; 
            tree_.iz[iNeigh] = -5000; 
            tree_.kSaturated[iNeigh] = -5000;
            tree_.kLeRecovered[iNeigh] = -5000;
            tree_.amplitRecovered[iNeigh] = -5000.;
            iNeigh++;
            continue;  
          }

          EcalRecHitCollection::const_iterator itneigh = EcalBarrelRecHits->find( cryId );

          if( itneigh != EcalBarrelRecHits->end() ) { 
            tree_.amplit[iNeigh] = itneigh->energy();
            tree_.ieta[iNeigh] = ((EBDetId)itneigh->detid()).ieta();
            tree_.iphi[iNeigh] = ((EBDetId)itneigh->detid()).iphi();
            tree_.ix[iNeigh] = -999;
            tree_.iy[iNeigh] = -999;
            tree_.iz[iNeigh] = -999;
            tree_.kSaturated[iNeigh] = itneigh->checkFlag(EcalRecHit::kSaturated);      
            tree_.kLeRecovered[iNeigh] = itneigh->checkFlag(EcalRecHit::kLeadingEdgeRecovered);      
            // extra saturation studies
            if (tree_.kSaturated[iNeigh] || tree_.kLeRecovered[iNeigh]) {
              ebDeadChannelCorrector.setCaloTopology(theCaloTopology.product());
              bool AcceptRecHit=true;
              EcalRecHit hit = ebDeadChannelCorrector.correct( (EBDetId)itneigh->detid(), *EcalBarrelRecHits, "NeuralNetworks", 8, &AcceptRecHit);
              tree_.amplitRecovered[iNeigh] = hit.energy();
            } else {
              tree_.amplitRecovered[iNeigh] = -999.;
            }

          } else {
            tree_.amplit[iNeigh] = -2000.;
            tree_.ieta[iNeigh] = -2000; 
            tree_.iphi[iNeigh] = -2000;
            tree_.ix[iNeigh] = -2000; 
            tree_.iy[iNeigh] = -2000; 
            tree_.iz[iNeigh] = -2000; 
            tree_.kSaturated[iNeigh] = -2000;
            tree_.kLeRecovered[iNeigh] = -2000;
            tree_.amplitRecovered[iNeigh] = -2000.;
          }

          iNeigh++;
        }
      }
      if (iNeigh!=25) cout << "problem: not 25 crystals!  ==> " << iNeigh << endl;
    }

  }

  nBranches_->ph_N = npho;

}

