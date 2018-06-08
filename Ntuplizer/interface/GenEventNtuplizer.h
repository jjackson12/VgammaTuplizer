#ifndef GenEventNtuplizer_H
#define GenEventNtuplizer_H

#include <algorithm>
#include <numeric>
#include <functional>
#include <iostream>

#include "../interface/CandidateNtuplizer.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "GeneratorInterface/LHEInterface/interface/LHEEvent.h"


class GenEventNtuplizer : public CandidateNtuplizer {

public:
  GenEventNtuplizer( std::vector< edm::EDGetTokenT< GenEventInfoProduct > > tokens, NtupleBranches* nBranches ,std::vector< edm::EDGetTokenT< LHEEventProduct > > tokens_lhe);
  ~GenEventNtuplizer( void );
  
  void fillBranches( edm::Event const & event, const edm::EventSetup& iSetup );
  
private:
   edm::EDGetTokenT< GenEventInfoProduct > geneventToken_; 
     
   edm::Handle< GenEventInfoProduct >  geneventInfo_;
  
   edm::EDGetTokenT<LHEEventProduct > lheEventProductToken_; 
   edm::Handle<LHEEventProduct> lheEventProduct_;
};

#endif // GenEventNtuplizer_H#ifndef GenEventNtuplizer_H

