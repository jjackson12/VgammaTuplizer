from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'Wgamma94XTuples_Jun18_gjets100-200'
config.General.workArea = 'crab_jobs_gjets100-200_Jun18'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'config_2017mc.py'
#TODO
config.JobType.inputFiles=['Spring16_23Sep2016V1_MC', 'JER']
config.JobType.sendExternalFolder = True

config.Data.inputDataset = '/GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 30
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'Wgamma94XTuples_Jun18_gjets100-200'
#TODO:
config.Site.storageSite = 'T3_US_Brown'
