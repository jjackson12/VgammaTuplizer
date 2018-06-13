from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'Wgamma94XTuples_Jun18_2017B'
config.General.workArea = 'crab_jobs_2017B_Jun18'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'config_generic_cfi.py'
config.JobType.inputFiles=[
        './JEC/Summer16_23Sep2016BCDV3_DATA_L1FastJet_AK4Calo.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L1FastJet_AK4JPT.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L1FastJet_AK4PF.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L1FastJet_AK4PFPuppi.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L1FastJet_AK4PFchs.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L1FastJet_AK8PF.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L1FastJet_AK8PFPuppi.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L1FastJet_AK8PFchs.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L1JPTOffset_AK4JPT.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L1RC_AK4PF.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L1RC_AK4PFchs.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L1RC_AK8PF.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L1RC_AK8PFchs.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2L3Residual_AK4Calo.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2L3Residual_AK4JPT.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2L3Residual_AK4PF.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2L3Residual_AK4PFPuppi.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2L3Residual_AK4PFchs.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2L3Residual_AK8PF.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2L3Residual_AK8PFPuppi.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2L3Residual_AK8PFchs.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2Relative_AK4Calo.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2Relative_AK4JPT.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2Relative_AK4PF.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2Relative_AK4PFPuppi.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2Relative_AK4PFchs.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2Relative_AK8PF.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2Relative_AK8PFPuppi.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2Relative_AK8PFchs.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2Residual_AK4Calo.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2Residual_AK4JPT.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2Residual_AK4PF.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2Residual_AK4PFPuppi.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2Residual_AK4PFchs.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2Residual_AK8PF.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2Residual_AK8PFPuppi.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L2Residual_AK8PFchs.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L3Absolute_AK4Calo.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L3Absolute_AK4JPT.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L3Absolute_AK4PF.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L3Absolute_AK4PFPuppi.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L3Absolute_AK4PFchs.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L3Absolute_AK8PF.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L3Absolute_AK8PFPuppi.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_L3Absolute_AK8PFchs.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_Uncertainty_AK4PF.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_Uncertainty_AK4PFPuppi.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_Uncertainty_AK4PFchs.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_Uncertainty_AK8PF.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_Uncertainty_AK8PFPuppi.txt',
        './JEC/Summer16_23Sep2016BCDV3_DATA_Uncertainty_AK8PFchs.txt',
        './JER/Spring16_25nsV6_MC_PtResolution_AK8PFchs.txt',
        './JER/Spring16_25nsV6_MC_PtResolution_AK4PFchs.txt',
        './JER/Spring16_25nsV6_MC_PtResolution_AK8PFPuppi.txt',
        './JER/Spring16_25nsV6_MC_PtResolution_AK4PFPuppi.txt',
        './JER/Spring16_25nsV6_MC_SF_AK8PFchs.txt',
        './JER/Spring16_25nsV6_MC_SF_AK4PFchs.txt',
        './JER/Spring16_25nsV6_MC_SF_AK8PFPuppi.txt',
        './JER/Spring16_25nsV6_MC_SF_AK4PFPuppi.txt'
]
config.JobType.sendExternalFolder = True

config.Data.inputDataset = '/SinglePhoton/Run2017B-17Nov2017-v1/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 30
config.Data.lumiMask='Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'Wgamma94XTuples_Jun18_2017B'
#TODO:
config.Site.storageSite = 'T3_US_FNALLPC'
