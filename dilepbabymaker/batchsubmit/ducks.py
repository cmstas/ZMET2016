import sys, os
import time
import itertools
import numpy
import ZMET_datasets as ZMET

from metis.Sample import DirectorySample,SNTSample
from metis.CondorTask import CondorTask
from metis.StatsParser import StatsParser

exec_path = "condor_exe.sh"
tar_path = "package.tar.gz"
hadoop_path = "ZMET_babies"
job_tag = "ZMET_babies_new"

#datasetsToProcess = ZMET.get(data = "SinglePhoton",year = 2017)
#EWKMCStrings = ["WGammaWJets","ttbar","SingleTop"]
MuonDataString = "2017SingleMuon"
#datasetsToProcess = ZMET.get(data = ["DoubleMuon","DoubleEG","MuonEG","ttZ","ttW","WW","WZ","ZZ","TTBarPowheg","DYamcnlo","SingleTop"],year = 2017)

datasetsToProcess = ZMET.get(data = ["GammaJetsHigherStats"], year = 2017)
#datsetsToProcess = ["/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM"]

print("Processing these datasets")
print(datasetsToProcess)

total_summary = {}
while True:
    all_jobs_done = True
    for dsname in datasetsToProcess:
        if dsname[:7] == "/hadoop":
            sample = DirectorySample(dataset = sample,location = sample)
        else:
            sample = SNTSample(dataset = dsname)
            print(sample.get_location())
        task = CondorTask(
              sample = sample,
              open_dataset = False,
              flush = True,
              files_per_output = 1,
              output_name = "baby.root",
              tag = job_tag,
              cmssw_version = "CMSSW_9_4_9", # doesn't do anything
              executable = exec_path,
              tarfile = tar_path,
              condor_submit_params = {"sites" : "T2_US_UCSD"},
              special_dir = hadoop_path
              )
        task.process()
        if not task.complete():
            print("Job %s still running." % job_tag)
            all_jobs_done = False
        total_summary[dsname] = task.get_task_summary()
        if task.complete():
            print ""
            print "Job={} finished".format(job_tag)
            print ""

    StatsParser(data=total_summary, webdir="~/public_html/dump/ZMet_babymaking/").do()
    if all_jobs_done:
        print ""
        print "All jobs are finished."
        print ""
        break
    os.system("chmod -R 755 ~/public_html/dump/ZMet_babymaking/")
    print "Sleeping 300 seconds ..."
    time.sleep(300)
