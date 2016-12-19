#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
if [ $# -ne 1 ]
then
  echo "no filenumber supplied!"
  return 1
fi
fileNumber=$(($1+1))
cd /home/hakala/cmssw/CMSSW_8_0_20/src/EXOVVNtuplizerRunII/Ntuplizer
eval `scramv1 runtime -sh`
echo cmsRun config_MC_condor.py fileNumber=${fileNumber}
/cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw/CMSSW_8_0_20/bin/slc6_amd64_gcc530/cmsRun config_MC_condor.py fileNumber=${fileNumber} sigMass=1000
