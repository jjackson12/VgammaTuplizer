from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'Wgamma94XTuples_Jun18_2017B'
config.General.workArea = 'crab_jobs_2017B_Jun18'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'VgammaTuplizer/Ntuplizer/config_generic.py'
config.JobType.inputFiles=[
        './VgammaTuplizer/Ntuplizer/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'
]
config.JobType.sendExternalFolder = True
config.Data.inputDataset = '/SinglePhoton/Run2017B-17Nov2017-v1/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 30
config.Data.lumiMask='VgammaTuplizer/Ntuplizer/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'Wgamma94XTuples_Jun18_2017B'
config.Site.storageSite = 'T3_US_FNALLPC'
