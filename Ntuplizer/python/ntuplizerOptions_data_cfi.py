import FWCore.ParameterSet.Config as cms

config = dict()

#--------- general ----------#
config["RUNONMC"] = False
config["USEJSON"] = True
#config["JSONFILE"] = "/scratch/osg/lesya/CMSSW_7_4_14/src/SUSYAnalyzer/PatAnalyzer/test/JSON/Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON_v2.txt"
#config["JSONFILE"] = "/scratch/osg/lesya/CMSSW_8_0_14/src/EXOVVNtuplizerRunII/Ntuplizer/Cert_271036-274421_13TeV_PromptReco_Collisions16_JSON.txt"
config["JSONFILE"] = "/scratch/osg/lesya/CMSSW_8_0_14/src/EXOVVNtuplizerRunII/Ntuplizer/Cert_271036-276811_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt"
config["BUNCHSPACING"] = 25

#--------- basic sequences ----------#
config["DOPHOTONS"] = True
config["DOGENPARTICLES"] = False
config["DOGENJETS"] = False
config["DOGENEVENT"] = False
config["DOLHEEVENT"] = False
config["DOPILEUP"] = False
config["DOELECTRONS"] = True
config["DOELECTRONIDVARS"] = False
config["DOELECTRONISOVARS"] = False
config["DOMUONS"] = True
config["DOMUONIDVARS"] = False
config["DOMUONISOVARS"] = False
config["DOTAUS"] = False
config["DOAK8JETS"] = True
config["DOAK4JETS"] = True
config["DOJETIDVARS"] = False
config["DOVERTICES"] = True
config["DOTRIGGERDECISIONS"] = True
config["DOTRIGGEROBJECTS"] = False
config["DOHLTFILTERS"] = True
config["DOMISSINGET"] = True
config["DOSEMILEPTONICTAUSBOOSTED"] = False

#--------- AK8 jets reclustering ----------#
config["ADDAK8GENJETS"] = False #! Add AK8 gen jet collection with pruned and softdrop mass
config["DOAK8RECLUSTERING"] = True
config["DOAK8PRUNEDRECLUSTERING"] = True #! To add pruned jet and pruned subjet collection (not in MINIAOD)
config["DOAK8PUPPIRECLUSTERING"] = False #ATLAS sequence
config["DOAK8PUPPI"] = False
config["DOAK10TRIMMEDRECLUSTERING"] = False
config["DOHBBTAG"] = True #Higgs-tagger

#--------- MET reclustering ----------#
config["DOMETRECLUSTERING"] = False

#--------- JEC ----------#
config["CORRJETSONTHEFLY"] = True
config["CORRMETONTHEFLY"] = True
config["GETJECFROMDBFILE"] = False # If not yet in global tag, but db file available
