import FWCore.ParameterSet.Config as cms

config = dict()

#--------- general ----------#

#--------- Set Just one to true ----------#
config["RUNONMC"] = False
config["RUNONPromptReco"] = False
config["RUNONReReco"] = True
#-----------------------------------------#

config["USEJSON"] = True # not (config["RUNONMC"])
config["JSONFILE"] =  "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt"
config["BUNCHSPACING"] = 25
config["USENOHF"] = False
config["FILTEREVENTS"] = False

#--------- basic sequences ----------#
config["DOPHOTONS"] = True
config["DOGENPARTICLES"] = (True and config["RUNONMC"])
config["DOGENJETS"] = (True and config["RUNONMC"])
config["DOGENEVENT"] = (True and config["RUNONMC"])
config["DOPILEUP"] = (True and config["RUNONMC"])
config["DOJETIDVARS"] = True
config["DOELECTRONS"] = False
config["DOMUONS"] = False
config["DOTAUS"] = False
config["DOAK8JETS"] = True
config["DOAK4JETS"] = True
config["DOVERTICES"] = True
config["DOTRIGGERDECISIONS"] = True
config["DOTRIGGEROBJECTS"] = False
config["DOHLTFILTERS"] = True
config["DOMISSINGET"] = True
config["DOTAUSBOOSTED"] = True
config["DOMETSVFIT"] = True
config["DOMVAMET"] = False

#--------- AK8 jets reclustering ----------#
config["ADDAK8GENJETS"] = (True and config["RUNONMC"]) #! Add AK8 gen jet collection with pruned and softdrop mass
config["DOAK8RECLUSTERING"] = False
config["DOAK8PRUNEDRECLUSTERING"] = False #! To add pruned jet and pruned subjet collection (not in MINIAOD)
config["DOAK8PUPPI"] = False
config["DOAK10TRIMMEDRECLUSTERING"] = False #ATLAS sequence
config["DOHBBTAG"] = False #Higgs-tagger
config["DOAK8PUPPIRECLUSTERING"] = False
config["UpdateJetCollection"] = False #needed for Higgs-tagger in 80X

#--------- MET reclustering ----------#
config["DOMETRECLUSTERING"] = False

#--------- JEC ----------#
config["CORRJETSONTHEFLY"] = True
config["CORRMETONTHEFLY"] = True
config["GETJECFROMDBFILE"] = False # If not yet in global tag, but db file available

#--------- TAU ----------#
config["DOMULTIPLETAUMVAVERSIONS"] = False
