#!/bin/bash

make -j5
didcompile=$?

if [ ! $didcompile == "0" ]; then
	echo "did not compile. exiting."
	exit $didcompile
fi

cp ../json/golden_json_010716_snt.txt .

# ./processBaby test_80_data /hadoop/cms/store/group/snt/run2_data/Run2016B_DoubleEG_MINIAOD_PromptReco-v2/merged/V08-00-06/merged_ntuple_32.root
# # ./processBaby test_80_data_photon /hadoop/cms/store/group/snt/run2_data/Run2016B_SinglePhoton_MINIAOD_PromptReco-v2/merged/V08-00-04/merged_ntuple_200.root

./processBaby test_80_data_mumu /hadoop/cms/store/group/snt/run2_data/Run2016B_DoubleMuon_MINIAOD_PromptReco-v2/merged/V08-00-06/merged_ntuple_1.root 

# ./processBaby test_80_t5zz_fastsim /hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2_fastsim/SMS-T5ZZ_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-05/merged_ntuple_1.root


# ./processBaby edgeexcess_Run2016 /home/users/cwelke/CMSSW/MCNtupling/CMSSW_8_0_11_V08-00-06/src/all_ntuple_merged.root
