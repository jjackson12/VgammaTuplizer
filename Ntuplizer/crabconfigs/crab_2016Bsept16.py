from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'Hgamma80XTuples_Mar11_2016B'
config.General.workArea = 'crab_jobs_2016B_Mar11'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'config_2016BCD.py'
config.JobType.inputFiles=['Summer16_23Sep2016BCDV4_DATA', 'JER']
config.JobType.sendExternalFolder = True

config.Data.inputDataset = '/SinglePhoton/Run2016B-23Sep2016-v3/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 30
config.Data.lumiMask='Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'Hgamma80XTuples_Mar11_2016B'

config.Site.storageSite = 'T3_US_Brown'
