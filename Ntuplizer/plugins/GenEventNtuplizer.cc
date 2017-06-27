#include "../interface/GenEventNtuplizer.h"

//===================================================================================================================
GenEventNtuplizer::GenEventNtuplizer( std::vector< edm::EDGetTokenT< GenEventInfoProduct > > tokens,
                                     std::vector< edm::EDGetTokenT< LHEEventProduct > > tokens2,
                                     bool doPDF,
                                     NtupleBranches* nBranches, TH1D* _hCounter )
: CandidateNtuplizer( nBranches )
, geneventToken_( tokens[0] )
, lheeventToken_( tokens2[0] )
, doPDF_(doPDF)
, _hCounterLoc(_hCounter)
{
    
}

//===================================================================================================================
GenEventNtuplizer::~GenEventNtuplizer( void )
{
    
}

//===================================================================================================================
void GenEventNtuplizer::fillBranches( edm::Event const & event, const edm::EventSetup& iSetup ){
    
    //event.getByToken(geneventToken_, geneventInfo_);
    edm::Handle<LHEEventProduct> eventHandle;
    edm::InputTag srcModule("source");
    if (event.getByLabel(srcModule, eventHandle)){
      const lhef::HEPEUP& lheEvent = eventHandle->hepeup();
      std::vector<lhef::HEPEUP::FiveVector> lheParticles = lheEvent.PUP;
      size_t nLheParticles = lheParticles.size();
      TLorentzVector* lheParticleVec = new TLorentzVector();
      std::vector<int> mothers;
      for (size_t iLheParticle = 0; iLheParticle < nLheParticles; ++iLheParticle) {
             nBranches_->lheParticle_pdgId     .push_back(lheEvent.IDUP[iLheParticle]);
             nBranches_->lheParticle_status    .push_back(lheEvent.ISTUP[iLheParticle]);
             mothers.clear();
             mothers.push_back(lheEvent.MOTHUP[iLheParticle].first);
             mothers.push_back(lheEvent.MOTHUP[iLheParticle].second);
             nBranches_->lheParticle_mother    .push_back(mothers);
             lheParticleVec->SetPxPyPzE(
                                                         lheParticles[iLheParticle][0],
                                                         lheParticles[iLheParticle][1],
                                                         lheParticles[iLheParticle][2],
                                                         lheParticles[iLheParticle][3]
                                                       ); 
             nBranches_->lheParticle_pt     .push_back(lheParticleVec->Pt());
             if (lheParticleVec->Pt() > 0.00001) {
               nBranches_->lheParticle_eta    .push_back(lheParticleVec->Eta());
               nBranches_->lheParticle_phi    .push_back(lheParticleVec->Phi());
             }
             else {
               nBranches_->lheParticle_eta    .push_back(-9999.);
               nBranches_->lheParticle_phi    .push_back(-9999.);
             }
             nBranches_->lheParticle_mass   .push_back(lheParticleVec->M());
      }
    }
    //TODO why is all this broken?
    //if (doPDF_) {
    //    event.getByToken(lheeventToken_, lheeventInfo_);
    //    nBranches_->originalXWGTUP=lheeventInfo_->originalXWGTUP();
    //    for(unsigned int k=0; k<lheeventInfo_->weights().size(); k++){
    //        nBranches_->sys_weights.push_back(lheeventInfo_->weights().at(k).wgt);
    //    }
    //}
    
    //double wght = 1;
    //if (geneventInfo_->weight() < 0)
    //    wght = -1;
    //
    //_hCounterLoc->Fill(1.,wght);
    //
    //nBranches_->genWeight=wght;
    //nBranches_->qScale=geneventInfo_->qScale();
    //nBranches_->pdf_scalePDF=geneventInfo_->pdf()->scalePDF;
    //nBranches_->PDF_x.push_back((geneventInfo_->pdf()->x).first);
    //nBranches_->PDF_x.push_back((geneventInfo_->pdf()->x).second);
    //nBranches_->PDF_xPDF.push_back((geneventInfo_->pdf()->xPDF).first);
    //nBranches_->PDF_xPDF.push_back((geneventInfo_->pdf()->xPDF).second);
    //nBranches_->PDF_id.push_back((geneventInfo_->pdf()->id).first);
    //nBranches_->PDF_id.push_back((geneventInfo_->pdf()->id).second);
    
}
