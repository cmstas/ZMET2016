#!/bin/bash

make -j5
didcompile=$?

if [ ! $didcompile == "0" ]; then
	echo "did not compile. exiting."
	exit $didcompile
fi

cp ../json/golden_json_260916_26p4fb_snt.txt .

# ./processBaby test_80_data /hadoop/cms/store/group/snt/run2_data/Run2016B_DoubleEG_MINIAOD_PromptReco-v2/merged/V08-00-06/merged_ntuple_32.root
# # ./processBaby test_80_data_photon /hadoop/cms/store/group/snt/run2_data/Run2016B_SinglePhoton_MINIAOD_PromptReco-v2/merged/V08-00-04/merged_ntuple_200.root

# ./processBaby test_80_data_mumu /hadoop/cms/store/group/snt/run2_data/Run2016B_DoubleMuon_MINIAOD_PromptReco-v2/merged/V08-00-06/merged_ntuple_1.root 

# ./processBaby test_80_t5zz_fastsim /hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2_fastsim/SMS-T5ZZ_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-05/merged_ntuple_1.root


# ./processBaby edgeexcess_Run2016 /home/users/cwelke/CMSSW/MCNtupling/CMSSW_8_0_11_V08-00-06/src/all_ntuple_merged.root

# ./processBaby test_80_data_mumu /hadoop/cms/store/group/snt/run2_data/Run2016C_DoubleMuon_MINIAOD_PromptReco-v2/merged/V08-00-07/merged_ntuple_16.root 

# ./processBaby test_80_MC_ttbar /hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext4-v1/V08-00-05/merged_ntuple_1.root

# ./processBaby test_80_tchiwz /hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2_fastsim/SMS-TChiWZ_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/V08-00-09/merged_ntuple_1.root 

# ./processBaby test_80_data_ph /hadoop/cms/store/group/snt/run2_data/Run2016C_SinglePhoton_MINIAOD_PromptReco-v2/merged/V08-00-07/merged_ntuple_1.root 

# ./processBaby test_80_data_relval /hadoop/cms/store/group/snt/run2_25ns/RelValTTbar_13_CMSSW_8_1_0_pre9-PU25ns_81X_mcRun2_asymptotic_v2-v1/V08-01-00/merged_ntuple_1.root 

# ./processBaby test_80_data /hadoop/cms/store/group/snt/run2_data/Run2016G_MuonEG_MINIAOD_PromptReco-v1/merged/V08-00-12/merged_ntuple_1.root 

# ./processBaby test_80_data_ph /hadoop/cms/store/group/snt/run2_data/Run2016G_SinglePhoton_MINIAOD_PromptReco-v1/merged/V08-00-12/merged_ntuple_41.root 


# ./processBaby test_80_data_ee /hadoop/cms/store/group/snt/run2_data/Run2016G_DoubleEG_MINIAOD_PromptReco-v1/merged/V08-00-12/merged_ntuple_126.root

./processBaby test_80_datarereco_ee /hadoop/cms/store/group/snt/run2_data/Run2016G_DoubleEG_MINIAOD_23Sep2016-v1/merged/V08-00-14/merged_ntuple_1.root 

# ./processBaby test_80_Wgamma_withW_P  /hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-05/merged_ntuple_1.root

#./processBaby test_80_WJets_withW_P   /hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-05/merged_ntuple_1.root

# ./processBaby test_80_signal_t5zz /hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2_fastsim/SMS-T5ZZ_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-09/merged_ntuple_1.root 
