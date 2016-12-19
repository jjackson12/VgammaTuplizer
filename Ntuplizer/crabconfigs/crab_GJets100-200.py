from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'Hgamma80XTuples_Dec18_gjets100-200'
config.General.workArea = 'crab_jobs_gjets100-200_Dec18'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'config_2016mc.py'
config.JobType.inputFiles=['Spring16_23Sep2016V1_MC', 'JER']
config.JobType.sendExternalFolder = True

config.Data.inputDataset = '/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v4/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 30
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'Hgamma80XTuples_Dec18_gjets100-200'

config.Site.storageSite = 'T3_US_Brown'
