#!/bin/bash

make -j5
didcompile=$?

if [ ! $didcompile == "0" ]; then
	echo "did not compile. exiting."
	exit $didcompile
fi

cp ../json/Cert_13TeV_16Dec2015ReReco_Collisions15_25ns_JSON_snt.txt .

# ./processBaby test  /hadoop/cms/store/group/snt/run2_50ns/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-03/merged_ntuple_1.root
# ./processBaby test_mc /hadoop/cms/store/group/snt/run2_25ns/TTTo2L2Nu_13TeV-powheg_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08///merged_ntuple_1.root

# ./processBaby test_mc_old /hadoop/cms/store/group/snt/run2_25ns/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-07/merged_ntuple_1.root

# ./processBaby test_data /hadoop/cms/store/group/snt/run2_data/Run2015C_DoubleEG_MINIAOD_PromptReco-v1/merged/V07-04-08/merged_ntuple_1.root

# ./processBaby data_ee_missing /hadoop/cms/store/group/snt/run2_data/Run2015C_DoubleEG_MINIAOD_PromptReco-v1/merged/V07-04-08/merged_ntuple_88.root 

# ./processBaby photon_mc /hadoop/cms/store/group/snt/run2_25ns/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-08/merged_ntuple_1.root
# ./processBaby photon_data /hadoop/cms/store/group/snt/run2_data/Run2015C_SinglePhoton_MINIAOD_PromptReco-v1/merged/V07-04-08/merged_ntuple_1.root

# ./processBaby ee_data_1 /hadoop/cms/store/group/snt/run2_data/Run2015D_DoubleEG_MINIAOD_PromptReco-v3/merged/V07-04-09/merged_ntuple_1.root
# ./processBaby test_mc ~/MCNtupling/CMSSW_7_4_14_CMS3_V07-04-09/src/ntuple_pp.root 

# ./processBaby test_data /hadoop/cms/store/group/snt/run2_data/Run2015D_DoubleEG_MINIAOD_PromptReco-v3/merged/V07-04-09/merged_ntuple_1.root


# ./processBaby edge_sync /home/users/cwelke/MCNtupling/CMSSW_7_4_14_CMS3_V07-04-11/src/ntuple_pp.root

# ./processBaby data_ph /hadoop/cms/store/group/snt/run2_data/Run2015D_SinglePhoton_MINIAOD_05Oct2015-v1/merged//V07-04-11/merged_ntuple_1.root
# ./processBaby mc_ph /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/merged_ntuple_1.root

# ./processBaby maria_sync ~/MCNtupling/CMSSW_7_4_14_CMS3_V07-04-11/src/ntuple_m.root

# ./processBaby merged_ntuple_59 /hadoop/cms/store/group/snt/run2_data/Run2015D_DoubleEG_MINIAOD_05Oct2015-v1/merged//V07-04-11//merged_ntuple_59.root 
# ./processBaby ssevent /nfs-3/userdata/cwelke/analysis/CMSSW_7_4_14/weirdssevent/ntuple_m.root

# ./processBaby test_zjnunu /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ZJetsToNuNu_HT-400To600_13TeV-madgraph_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-10/merged_ntuple_1.root

# ./processBaby test_withnewrho /home/users/cwelke/MCNtupling/CMSSW_7_4_7_patch2_V07-04-08_dev/src/ntuple_postp.root


# ./processBaby test_76 /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/merged_ntuple_1.root 


./processBaby merged_ntuple_161 /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/V/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/v1/CMS3_V07-06-03/merged_ntuple_161.root
