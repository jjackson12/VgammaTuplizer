# EXOVVNtuplizerRunII


## Instructions for CMSSW_8_0_20

```
cmsrel CMSSW_8_0_19
cd CMSSW_8_0_19/src
cmsenv
export CMSSW_GIT_REFERENCE=/cvmfs/cms.cern.ch/cmssw.git.daily
git cms-init
git cms-merge-topic -u cms-met:CMSSW_8_0_X-METFilterUpdate
git remote add btv-cmssw https://github.com/cms-btv-pog/cmssw.git
git fetch --tags btv-cmssw
git cms-merge-topic -u cms-btv-pog:BoostedDoubleSVTaggerV3-WithWeightFiles-v1_from-CMSSW_8_0_8_patch1
git clone git@github.com:jhakala/EXOVVNtuplizerRunII.git
cd EXOVVNtuplizerRunII/
git fetch
git checkout 80X_dev
scram b distclean
cd ..
scram b -j12
# select your input file in config_MC.py
# copy the appropriate JECs and JERs into the respective dirs
cmsRun config_MC.py
```

to add the new MVA photon ID, follow the instructions here:
https://twiki.cern.ch/twiki/bin/view/CMS/MultivariatePhotonIdentificationRun2#Recipes_for_regular_users
