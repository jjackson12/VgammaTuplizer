#ifndef GenEventNtuplizer_H
#define GenEventNtuplizer_H

#include "../interface/CandidateNtuplizer.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"


class GenEventNtuplizer : public CandidateNtuplizer {

public:
  GenEventNtuplizer( std::vector< edm::EDGetTokenT< GenEventInfoProduct > > tokens,
                    std::vector< edm::EDGetTokenT< LHEEventProduct > > tokens2,
                    bool doPDF,
                    NtupleBranches* nBranches );
  ~GenEventNtuplizer( void );
  
  void fillBranches( edm::Event const & event, const edm::EventSetup& iSetup );
  
private:
    
    edm::EDGetTokenT< GenEventInfoProduct > geneventToken_;
    edm::Handle< GenEventInfoProduct >  geneventInfo_;
    edm::EDGetTokenT< LHEEventProduct > lheeventToken_;
    edm::Handle< LHEEventProduct >  lheeventInfo_;
    bool doPDF_;

    
};

#endif // GenEventNtuplizer_H
