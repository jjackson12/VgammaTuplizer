def makeCrabConfig(date, datasetShortName, datasetLongName, jecName, run):
  print "date ", date
  print "datasetShortName ", datasetShortName
  print "datasetLongName ", datasetLongName
  print "jecName ", jecName
  outConfigFile = open("crab_%s.py" % datasetShortName, "w")
  outConfigFile.write("""from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'Hgamma80XTuples_%s_%s'
config.General.workArea = 'crab_jobs_%s_%s'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'config_%s.py'
config.JobType.inputFiles=['%s', 'JER']
config.JobType.sendExternalFolder = True

config.Data.inputDataset = '%s'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 60
config.Data.lumiMask='Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
config.Data.outLFNDirBase = '/store/user/%%s/' %% (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'Hgamma80XTuples_%s_%s'

config.Site.storageSite = 'T3_US_Brown'
""" % (date, datasetShortName, datasetShortName, date, run, jecName, datasetLongName, date, datasetShortName) )
  outConfigFile.close()

from sys import argv
from os import path
if not len(argv) == 2 :
  print "please supply one config file"
  exit(1)
if not path.isfile(argv[1]):
  print "config file not found:", argv[1]
  exit(1)

from ConfigParser import RawConfigParser
config = RawConfigParser()   
config.optionxform = str       # Last two lines are done because ConfigParser will not preserve case
config.read(argv[1])

shortNames = dict([key, shortName] for key, shortName in config.items('ShortNames'))
longNames = dict([shortName, longName] for shortName, longName in config.items('LongNames'))
jecNames = dict([shortName, jecName] for shortName, jecName in config.items('JecNames'))
runNames = dict([shortName, runName] for shortName, runName in config.items('RunNames'))

import datetime
today = datetime.date.today()
for key in shortNames:
  makeCrabConfig(today.strftime("%b%d"), shortNames[key], longNames[key], jecNames[key], runNames[key]) 

