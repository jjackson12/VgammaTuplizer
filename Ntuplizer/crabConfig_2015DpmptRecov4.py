from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'WZgammaNtuples_2015DpmptRecoV4_Dec22'
config.General.workArea = 'crab_jobs_2015DpmptRecoV4_Dec22'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'config_data.py'
config.JobType.inputFiles=['JEC']

config.Data.inputDataset = '/SinglePhoton/Run2015D-PromptReco-v4/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 50
config.Data.lumiMask='/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/13TeV/Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON_v2.txt'
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = True
config.Data.outputDatasetTag = 'WZgammaNtuples_2015DpmptRecoV4_Dec22'

config.Site.storageSite = 'T3_US_Brown'
