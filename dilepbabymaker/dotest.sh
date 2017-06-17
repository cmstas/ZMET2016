#!/bin/bash

make -j5
didcompile=$?

if [ ! $didcompile == "0" ]; then
	echo "did not compile. exiting."
	exit $didcompile
fi

cp ../json/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON_snt.txt .


#======================================
# Process Baby Commands, tests looper
#======================================
dotest_nEvts=1000

#dotest_babyID=test_80_data 
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_data/Run2016B_DoubleEG_MINIAOD_PromptReco-v2/merged/V08-00-06/merged_ntuple_32.root

#dotest_babyID=test_80_data_photon 
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_data/Run2016B_SinglePhoton_MINIAOD_PromptReco-v2/merged/V08-00-04/merged_ntuple_200.root

# dotest_babyID=test_80_data_mumu 
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_data/Run2016B_DoubleMuon_MINIAOD_PromptReco-v2/merged/V08-00-06/merged_ntuple_1.root 

# dotest_babyID=test_80_t5zz_fastsim 
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2_fastsim/SMS-T5ZZ_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-05/merged_ntuple_1.root

# dotest_babyID=edgeexcess_Run2016 
#dotest_babyPath=/home/users/cwelke/CMSSW/MCNtupling/CMSSW_8_0_11_V08-00-06/src/all_ntuple_merged.root

# dotest_babyID=test_80_data_mumu 
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_data/Run2016C_DoubleMuon_MINIAOD_PromptReco-v2/merged/V08-00-07/merged_ntuple_16.root 

# dotest_babyID=test_80_MC_ttbar 
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext4-v1/V08-00-05/merged_ntuple_1.root

# dotest_babyID=test_80_tchiwz 
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2_fastsim/SMS-TChiWZ_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/V08-00-09/merged_ntuple_1.root 

# dotest_babyID=test_80_data_ph 
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_data/Run2016C_SinglePhoton_MINIAOD_PromptReco-v2/merged/V08-00-07/merged_ntuple_1.root 

# dotest_babyID=test_80_data_relval 
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_25ns/RelValTTbar_13_CMSSW_8_1_0_pre9-PU25ns_81X_mcRun2_asymptotic_v2-v1/V08-01-00/merged_ntuple_1.root 

# dotest_babyID=test_80_data 
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_data/Run2016G_MuonEG_MINIAOD_PromptReco-v1/merged/V08-00-12/merged_ntuple_1.root 

# dotest_babyID=test_80_data_ph 
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_data/Run2016G_SinglePhoton_MINIAOD_PromptReco-v1/merged/V08-00-12/merged_ntuple_41.root 

# dotest_babyID=test_80_data_ee 
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_data/Run2016G_DoubleEG_MINIAOD_PromptReco-v1/merged/V08-00-12/merged_ntuple_126.root

# dotest_babyID=test_80_datarereco_ee 
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_data/Run2016G_DoubleEG_MINIAOD_23Sep2016-v1/merged/V08-00-14/merged_ntuple_1.root 

#dotest_babyID=test_80_Wgamma_withW_P  
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-05/merged_ntuple_1.root 

# dotest_babyID=test_80_WJets_withW_P   
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-05/merged_ntuple_1.root

# dotest_babyID=test_80_signal_t5zz 
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2_fastsim/SMS-T5ZZ_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-09/merged_ntuple_1.root 

#dotest_babyID=test_80_sync_ttbar_mc 
#dotest_babyPath=/nfs-6/userdata/cwelke/CMSSW/MCNtupling/CMSSW_8_0_21_CMS3_V08-00-16/src/sync_ttbar_80MiniAODv2.root

#dotest_babyID=test_moriondmc_ttbar_1k 
#dotest_babyPath=/hadoop/cms/store/group/snt/run2_moriond17/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/merged_ntuple_2.root

dotest_babyID=test_mia_WWW
dotest_babyPath=/hadoop/cms/store/group/snt/run2_moriond17/TEST-www_www-Private80X-v1/V08-00-16/merged_ntuple_1.root

#dotest_babyID=test_moriondmc_sync_ttbar_dilep_nopostproc
#dotest_babyPath=/nfs-7/userdata/ZMEToutput/output/sync_Jan2017/sync_ttbar_dilep_Summer16_1file_nopostproc.root 

./processBaby $dotest_babyID $dotest_babyPath $dotest_nEvts

dotest_babyID=test_data
dotest_babyPath=/hadoop/cms/store/group/snt/run2_data/Run2016D_SingleMuon_MINIAOD_03Feb2017-v1/merged/V08-00-18/merged_ntuple_331.root

./processBaby $dotest_babyID $dotest_babyPath $dotest_nEvts

#======================================
# Tests Skimmer
#======================================

dotest_outfile=`ls | grep ${dotest_babyID}`
cp ${dotest_outfile} output.root
root -b -q skim_macro.C
