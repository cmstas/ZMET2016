from __future__ import print_function
import ROOT as r
import numpy as np
import os,sys

#One histogram file containing histograms from all three years
fastsim_sample = sys.argv[1].lower()
directory_prefix = "/hadoop/cms/store/group/snt/"
year_directory_mapping = {
        2016:"run2_mc2016_94x",
        2017:"run2_mc2017",
        2018:"run2_mc2018"
        }

dataset_directory_mapping ={

        "t5zz":{2016:["SMS-T5ZZ_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUSummer16v3Fast_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_CMS4_V10-02-09","SMS-T5ZZ_mGluino-1850to2400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUSummer16v3Fast_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_CMS4_V10-02-09"],
            2017:["SMS-T5ZZ_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PUFall17Fast_94X_mc2017_realistic_v15-v1_MINIAODSIM_CMS4_V10-02-09","SMS-T5ZZ_mGluino-1850to2400_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PUFall17Fast_94X_mc2017_realistic_v15-v1_MINIAODSIM_CMS4_V10-02-09"],
            2018:["SMS-T5ZZ_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIAutumn18MiniAOD-PUFall18Fast_102X_upgrade2018_realistic_v15-v1_MINIAODSIM_CMS4_V10-02-09","SMS-T5ZZ_mGluino-1850to2400_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIAutumn18MiniAOD-PUFall18Fast_102X_upgrade2018_realistic_v15-v1_MINIAODSIM_CMS4_V10-02-09"]},

        "tchiwz":{2016:["SMS-TChiWZ_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUSummer16v3Fast_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_CMS4_V10-02-09"],
            2017:["SMS-TChiWZ_ZToLL_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PUFall17Fast_94X_mc2017_realistic_v15-v1_MINIAODSIM_CMS4_V10-02-09"],
            2018:["SMS-TChiWZ_ZToLL_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIAutumn18MiniAOD-PUFall18Fast_102X_upgrade2018_realistic_v15-v1_MINIAODSIM_CMS4_V10-02-09"]},

        "tchihz":{2016:["SMS-TChiHZ_HToBB_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUSummer16v3Fast_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_CMS4_V10-02-09"],
            2017:["SMS-TChiHZ_HToBB_ZToLL_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PUFall17Fast_94X_mc2017_realistic_v15-v1_MINIAODSIM_CMS4_V10-02-09"],
            2018:["SMS-TChiHZ_HToBB_ZToLL_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIAutumn18MiniAOD-PUFall18Fast_102X_upgrade2018_realistic_v15-v1_MINIAODSIM_CMS4_V10-02-09"]},

        "tchizz":{2016:["SMS-TChiZZ_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUSummer16v3Fast_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_CMS4_V10-02-09"],
            2017:["SMS-TChiZZ_ZToLL_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PUFall17Fast_94X_mc2017_realistic_v15-v1_MINIAODSIM_CMS4_V10-02-09"],
            2018:["SMS-TChiZZ_ZToLL_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIAutumn18MiniAOD-PUFall18Fast_102X_upgrade2018_realistic_v15-v1_MINIAODSIM_CMS4_V10-02-09"]},

    }


years =[2016,2017,2018]

#Add all files except those in the dirty list
corruptListFile = open("corrupt_fastsim_files.txt","r")
corruptList = []
for line in corruptListFile:
    corruptLlist.append(line)

n_events_per_year = {}
for year in years:
    print("Processing sample",fastsim_sample,"for year=",year)

    ch = r.TChain("Events")
    ch.Reset() #Additional precaution
    for directory in dataset_directory_mapping[fastsim_sample][year]:
        full_path = os.path.join(directory_prefix,year_directory_mapping[year],directory,"*.root")
        files_list = glob.glob(full_path)
        print("Adding directory ",full_path," to TChain")
        for filename in files_list:
            if filename not in corruptList:
                ch.Add(filename)
            else:
                print("Skipping {} because it is corrupt",filename)

    if fastsim_sample == "tchiwz":
        n_events_per_year[year] = r.TH2D("h_nevents_"+str(year),"mass1[GeV]:mass2[GeV]",60,0,3000,60,0,3000)
    elif fastsim_sample == "t5zz":
        n_events_per_year[year] = r.TH2D("h_nevents_"+str(year),"mass1[GeV]:mass2[GeV]",60,0,3000,60,0,3000)
    elif fastsim_sample == "tchizz":
        n_events_per_year[year] = r.TH1D("h_nevents_"+str(year),"mass1[GeV]",60,0,3000)
    elif fastsim_sample == "tchihz":
        n_events_per_year[year] = r.TH1D("h_nevents_"+str(year),"mass1[GeV]",60,0,3000)
    print("Chain has ",ch.GetEntries()," events")
    if fastsim_sample == "tchiwz" or fastsim_sample == "t5zz":
        ch.Project("h_nevents_"+str(year),"sparm_values[1]:sparm_values[0]")
#        ch.Draw("sparm_values[1]:sparm_values[0] >> h_nevents_"+str(year))
    elif fastsim_sample == "tchihz" or fastsim_sample == "tchizz":
#         ch.Draw("sparm_values >> h_nevents_"+str(year))
        ch.Project("h_nevents_"+str(year),"sparm_values")
    else:
        print("WHAT ON EARTH!")


histogramFile = r.TFile(fastsim_sample+"_entries.root","RECREATE")
histogramFile.cd()
for year,histogram in n_events_per_year.items():
    histogram.SetDirectory(histogramFile)

histogramFile.Write()
