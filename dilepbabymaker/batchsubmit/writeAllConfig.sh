#!/bin/bash

#
# All MT2 related datasets available on hadoop
#

# compile files
cd ..
make -j25
cd -

# copy compiled files
cp -r ../*.so ../jetCorrections ../processBaby ../MVAinput ../../json/*.txt job_input/ 

source ../../ZMET2015/settings.sh 

# update tag
TAG=${analysis_version}

# will add

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_DoubleEG_MINIAOD_PromptReco-v1/merged/V07-04-08/     ${TAG}_data_25nsPrompt_ee
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_SinglePhoton_MINIAOD_PromptReco-v1/merged/V07-04-08/ ${TAG}_data_25nsPrompt_ph
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_DoubleMuon_MINIAOD_PromptReco-v1/merged/V07-04-08/   ${TAG}_data_25nsPrompt_mm
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_MuonEG_MINIAOD_PromptReco-v1/merged/V07-04-08/       ${TAG}_data_25nsPrompt_em

./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_DoubleEG_MINIAOD_PromptReco-v3/merged/V07-04-09/     ${TAG}_data_2015D25nsPrompt_ee
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_SinglePhoton_MINIAOD_PromptReco-v3/merged/V07-04-09/ ${TAG}_data_2015D25nsPrompt_ph
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_DoubleMuon_MINIAOD_PromptReco-v3/merged/V07-04-09/   ${TAG}_data_2015D25nsPrompt_mm
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_MuonEG_MINIAOD_PromptReco-v3/merged/V07-04-09/       ${TAG}_data_2015D25nsPrompt_em

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-08/ ${TAG}_zjetsllht100_25ns_m50mlm  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-08/ ${TAG}_zjetsllht200_25ns_m50mlm  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-08/ ${TAG}_zjetsllht400_25ns_m50mlm  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-08/ ${TAG}_zjetsllht600_25ns_m50mlm  

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-08/ ${TAG}_wz2l2q_25ns_nlo  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08/ ${TAG}_zz2l2q_25ns_nlo  

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/ZZTo4L_13TeV_powheg_pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08/                 ${TAG}_zz4l_25ns_php8  

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08/ ${TAG}_wwz_25ns_nlo  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-08/ ${TAG}_zzz_25ns_nlo  

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08/ ${TAG}_dyjetsll_25ns_m1050nlo
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/V07-04-08/     ${TAG}_dyjetsll_25ns_m50nlo	 
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/TTTo2L2Nu_13TeV-powheg_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08/                                      ${TAG}_tt2lnu_25ns_php8

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08/                        ${TAG}_wz3lnu_25ns_powp8  	 
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/WWTo2L2Nu_13TeV-powheg_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08/                                            ${TAG}_ww2l2nu_25ns_powp8   
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08	 ${TAG}_sttwtop_25ns_powp8   
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08 ${TAG}_sttwatop_25ns_powp8  

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08       ${TAG}_ttwlnu_25ns_nlo 
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08/       ${TAG}_ttw2q_25ns_nlo 
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08/                           ${TAG}_wzz_25ns_nlo  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08            ${TAG}_ttg_25ns_nlo  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08						 ${TAG}_ttzqq_25ns_nlo  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08               ${TAG}_ttzllnunu_25ns_nlo  


# # for closure studies
# ./writeConfig.sh /hadoop/cms/store/user/cwelke/run2_25ns/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08/    ${TAG}_zjetsll_25ns_m50mlm  

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-08/     ${TAG}_gjets_25ns_ht40mlm  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-08/    ${TAG}_gjets_25ns_ht100mlm  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-08/    ${TAG}_gjets_25ns_ht200mlm  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08/    ${TAG}_gjets_25ns_ht400mlm  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08/    ${TAG}_gjets_25ns_ht600mlm  


# --- write submit script ---
mkdir -p configs_${TAG}

mv condor_${TAG}*.cmd configs_${TAG}
echo "#!/bin/bash" > submitAll.sh
echo "voms-proxy-init -voms cms -valid 240:00" >> submitAll.sh
for file in configs_${TAG}/*.cmd
do 
    echo "condor_submit ${file}" >> submitAll.sh
done
chmod +x submitAll.sh
echo "[writeAllConfig] wrote submit script submitAll.sh"
