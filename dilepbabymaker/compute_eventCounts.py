from __future__ import print_function
import ROOT as r
import numpy as np
import os,sys
import glob
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

        "tchiwz-fullsim":{2016:["SMS-TChiWZ_ZToLL_mZMin-0p1_mC1-325to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_GridpackScan_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_CMS4_V10-02-10","SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv3-PUMoriond17_GridpackScan_94X_mcRun2_asymptotic_v3-v1_MINIAODSIM_CMS4_V10-02-10"],2017:["SMS-TChiWZ_ZToLL_mZMin-0p1_mC1-325to1000_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_GridpackScan_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V10-02-10","SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_GridpackScan_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V10-02-10"],2018:["SMS-TChiWZ_ZToLL_mZMin-0p1_mC1-325to1000_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIAutumn18MiniAOD-GridpackScan_102X_upgrade2018_realistic_v15-v1_MINIAODSIM_CMS4_V10-02-10","SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8_RunIIAutumn18MiniAOD-GridpackScan_102X_upgrade2018_realistic_v15-v1_MINIAODSIM_CMS4_V10-02-10"]},

    }


years =[2016,2017,2018]
gluinoMassBins = np.array([800.000000,900.000000,1000.000000,1050.000000,1100.000000,1150.000000,1200.000000,1250.000000,1300.000000,1350.000000,1400.000000,1450.000000,1500.000000,1550.000000,1600.000000,1650.000000,1700.000000,1750.000000,1800.000000,1850.000000,1900.000000,1950.000000,2000.000000,2050.000000,2100.000000,2150.000000,2200.000000,2250.000000,2300.000000,2350.000000,2400.000000], dtype = np.float64)

lspMassBins = np.array([25.000000,50.000000,100.000000,150.000000,200.000000,250.000000,300.000000,350.000000,400.000000,450.000000,500.000000,550.000000,600.000000,650.000000,700.000000,750.000000,790.000000,800.000000,850.000000,890.000000,900.000000,950.000000,990.000000,1000.000000,1040.000000,1050.000000,1090.000000,1100.000000,1140.000000,1150.000000,1190.000000,1200.000000,1240.000000,1250.000000,1290.000000,1300.000000,1340.000000,1350.000000,1390.000000,1400.000000,1440.000000,1450.000000,1490.000000,1500.000000,1540.000000,1550.000000,1590.000000,1600.000000,1640.000000,1650.000000,1690.000000,1700.000000,1740.000000,1750.000000,1790.000000,1800.000000,1840.000000,1850.000000,1890.000000,1900.000000,1940.000000,1950.000000,1990.000000,2000.000000,2040.000000,2050.000000,2090.000000,2100.000000,2140.000000,2150.000000,2190.000000,2200.000000,2240.000000,2250.000000,2290.000000,2300.000000,2340.000000,2350.000000,2390.000000,2400.000000], dtype = np.float64)


#Add all files except those in the dirty list
corruptList = []
try:
    corruptListFile = open("corrupt_fastsim_files.txt","r")
    for line in corruptListFile:
    	corruptList.append(line.rstrip("\n"))
except:
      pass

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
                print("Skipping {} because it is corrupt".format(filename))

    if fastsim_sample == "tchiwz" or fastsim_sample == "tchiwz-fullsim":
        n_events_per_year[year] = r.TH2D("h_nevents_"+str(year),"mass1[GeV]:mass2[GeV]",60,0,3000,60,0,3000)
    elif fastsim_sample == "t5zz":
        n_events_per_year[year] = r.TH2D("h_nevents_"+str(year),"mass1[GeV]:mass2[GeV]",len(gluinoMassBins)-1,gluinoMassBins,len(lspMassBins)-1,lspMassBins)
    elif fastsim_sample == "tchizz":
        n_events_per_year[year] = r.TH1D("h_nevents_"+str(year),"mass1[GeV]",60,0,3000)
    elif fastsim_sample == "tchihz":
        n_events_per_year[year] = r.TH1D("h_nevents_"+str(year),"mass1[GeV]",60,0,3000)
    print("Chain has ",ch.GetEntries()," events")
    if fastsim_sample == "tchiwz" or fastsim_sample == "t5zz" or fastsim_sample == "tchiwz-fullsim":
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
