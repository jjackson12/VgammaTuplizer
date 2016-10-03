#ifndef GenEventNtuplizer_H
#define GenEventNtuplizer_H

#include "../interface/CandidateNtuplizer.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


class GenEventNtuplizer : public CandidateNtuplizer {

public:
  GenEventNtuplizer( std::vector< edm::EDGetTokenT< GenEventInfoProduct > > tokens,
                    std::vector< edm::EDGetTokenT< LHEEventProduct > > tokens2,
                    bool doPDF,
                    NtupleBranches* nBranches, TH1D* _hCounter );
  ~GenEventNtuplizer( void );
  
  void fillBranches( edm::Event const & event, const edm::EventSetup& iSetup );
  
private:
    
    edm::EDGetTokenT< GenEventInfoProduct > geneventToken_;
    edm::Handle< GenEventInfoProduct >  geneventInfo_;
    edm::EDGetTokenT< LHEEventProduct > lheeventToken_;
    edm::Handle< LHEEventProduct >  lheeventInfo_;
    bool doPDF_;
    TH1D* _hCounterLoc;

    
};

#endif // GenEventNtuplizer_H
