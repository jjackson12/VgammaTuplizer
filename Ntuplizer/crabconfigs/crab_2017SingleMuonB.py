from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'Wgamma94XSingleMuonTuples_%s_2017B'%"Jul13"
config.General.workArea = 'crab_jobs_2017B_%s'%"Jul13"
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'VgammaTuplizer/Ntuplizer/config_generic.py'
config.JobType.inputFiles=[
        './VgammaTuplizer/Ntuplizer/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSONv1.txt'
]
config.JobType.sendExternalFolder = True
config.Data.inputDataset = '/SingleMuon/Run2017B-31Mar2018-v1/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 30
config.Data.lumiMask='VgammaTuplizer/Ntuplizer/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSONv1.txt'
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'Wgamma94XSingleMuonTuples_%s_2017B'%"Jul13"
config.Site.storageSite = 'T3_US_FNALLPC'
