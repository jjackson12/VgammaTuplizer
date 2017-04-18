from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'Hgamma80XTuples_Mar14_GJets100To200'
config.General.workArea = 'crab_jobs_GJets100To200_Mar14'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'config_2016mc.py'
config.JobType.inputFiles=['Summer16_23Sep2016V4_MC', 'JER']
config.JobType.sendExternalFolder = True

config.Data.inputDataset = '/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 30
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'Hgamma80XTuples_Mar14_GJets100To200'

config.Site.storageSite = 'T3_US_Brown'
