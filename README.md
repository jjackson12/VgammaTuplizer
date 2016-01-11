# EXOVVNtuplizerRunII


## Instructions for CMSSW_7_4_16_patch1

```
cmsrel CMSSW_7_4_16_patch1
cd CMSSW_7_4_16_patch1/src
cmsenv
git cms-init
```

To get the 7_4_X (X>=16) photon ID:
```
git cms-merge-topic ikrav:egm_id_7.4.12_v1
```

For the boosted Hbb tagger (will add a lot of packages that will take a long time to compile):
```
git remote add btv-cmssw https://github.com/cms-btv-pog/cmssw.git
git fetch btv-cmssw
git cms-merge-topic -u cms-btv-pog:BoostedDoubleSVTagger-WithWeightFiles-v2_from-CMSSW_7_4_1
```

getting the code:
```
git cms-addpkg RecoJets/Configuration
git clone https://github.com/jhakala/EXOVVNtuplizerRunII.git
scram b distclean
scram b -j8
cd EXOVVNtuplizerRunII/Ntuplizer
```
Tested on lxplus.
