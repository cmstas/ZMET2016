#!/bin/bash

#
# All MT2 related datasets available on hadoop
#

# compile files
cd ..
make -j8
cd -

# copy compiled files
cp -r ../*.so ../pileup_jul21_nominalUpDown.root ../btagsf ../TChiWZ_entries_V08-00-05_FS.root ../xsec_susy_13tev.root ../T5ZZ_entries.root ../jetCorrections ../processBaby ../MVAinput ../../json/*.txt job_input/ 

source ../../ZMET2015/settings.sh 

# update tag
TAG=${analysis_version}

# 2016 data
./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016B_DoubleEG_MINIAOD_PromptReco-v2/merged/V08-00-06/     ${TAG}_data_2016B_Prompt_ee_v2
./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016B_DoubleMuon_MINIAOD_PromptReco-v2/merged/V08-00-06/   ${TAG}_data_2016B_Prompt_mm_v2
./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016B_MuonEG_MINIAOD_PromptReco-v2/merged/V08-00-06/       ${TAG}_data_2016B_Prompt_em_v2
./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016B_SinglePhoton_MINIAOD_PromptReco-v2/merged/V08-00-06/ ${TAG}_data_2016B_Prompt_ph_v2

./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016C_DoubleEG_MINIAOD_PromptReco-v2/merged/V08-00-07/     ${TAG}_data_2016C_Prompt_ee_v2
./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016C_DoubleMuon_MINIAOD_PromptReco-v2/merged/V08-00-07/   ${TAG}_data_2016C_Prompt_mm_v2
./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016C_MuonEG_MINIAOD_PromptReco-v2/merged/V08-00-07/       ${TAG}_data_2016C_Prompt_em_v2
./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016C_SinglePhoton_MINIAOD_PromptReco-v2/merged/V08-00-07/ ${TAG}_data_2016C_Prompt_ph_v2

./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016D_DoubleEG_MINIAOD_PromptReco-v2/merged/V08-00-08/     ${TAG}_data_2016D_Prompt_ee_v2
./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016D_DoubleMuon_MINIAOD_PromptReco-v2/merged/V08-00-08/   ${TAG}_data_2016D_Prompt_mm_v2
./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016D_MuonEG_MINIAOD_PromptReco-v2/merged/V08-00-08/       ${TAG}_data_2016D_Prompt_em_v2
./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016D_SinglePhoton_MINIAOD_PromptReco-v2/merged/V08-00-08/ ${TAG}_data_2016D_Prompt_ph_v2

# 2016 MC

hadoopdirv2="hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2"
miniaodv2="RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2"

# DY
./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_${miniaodv2}_v0-v1/V08-00-05/ ${TAG}_dy_m1050_amcnlo
./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_${miniaodv2}_v0-v1/V08-00-05/ ${TAG}_dy_m50_amcnlo

# ttbar
./writeConfig_80X.sh /${hadoopdirv2}/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0-v4/V08-00-05/             ${TAG}_ttbar_dilep_mgmlm
./writeConfig_80X.sh /${hadoopdirv2}/TTTo2L2Nu_13TeV-powheg_${miniaodv2}_v0_ext1-v1/V08-00-05/                                      ${TAG}_ttbar_dilep_powheg
./writeConfig_80X.sh /${hadoopdirv2}/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0-v1/V08-00-05/    ${TAG}_ttbar_1ltop_mgmlm
./writeConfig_80X.sh /${hadoopdirv2}/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0-v1/V08-00-05/ ${TAG}_ttbar_1ltbr_mgmlm

# single top
./writeConfig_80X.sh /${hadoopdirv2}/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_${miniaodv2}_v0-v1/V08-00-05/ ${TAG}_sttw_antitop_powheg
./writeConfig_80X.sh /${hadoopdirv2}/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_${miniaodv2}_v0-v2/V08-00-05/     ${TAG}_sttw_top_powheg

# VV
./writeConfig_80X.sh /${hadoopdirv2}/WWTo2L2Nu_13TeV-powheg_${miniaodv2}_v0-v1/V08-00-05/                         ${TAG}_ww_2l2nu_powheg
./writeConfig_80X.sh /${hadoopdirv2}/WWToLNuQQ_13TeV-powheg_${miniaodv2}_v0-v1/V08-00-05/                         ${TAG}_ww_lnuqq_powheg
./writeConfig_80X.sh /${hadoopdirv2}/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_${miniaodv2}_v0-v1/V08-00-05/ ${TAG}_wz_lnqq_amcnlo
./writeConfig_80X.sh /${hadoopdirv2}/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_${miniaodv2}_v0-v1/V08-00-05/   ${TAG}_wz_1l3n_amcnlo
./writeConfig_80X.sh /${hadoopdirv2}/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_${miniaodv2}_v0-v1/V08-00-05/    ${TAG}_wz_2l2q_amcnlo
./writeConfig_80X.sh /${hadoopdirv2}/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8_${miniaodv2}_v0-v1/V08-00-05/     ${TAG}_wz_3lnu_powheg
./writeConfig_80X.sh /${hadoopdirv2}/ZZTo2L2Nu_13TeV_powheg_pythia8_${miniaodv2}_v0-v1/V08-00-05/                 ${TAG}_zz_2l2n_powheg
./writeConfig_80X.sh /${hadoopdirv2}/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_${miniaodv2}_v0-v1/V08-00-05/    ${TAG}_zz_2l2q_amcnlo
./writeConfig_80X.sh /${hadoopdirv2}/ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8_${miniaodv2}_v0-v1/V08-00-05/   ${TAG}_zz_2q2n_amcnlo
./writeConfig_80X.sh /${hadoopdirv2}/ZZTo4L_13TeV_powheg_pythia8_${miniaodv2}_v0-v1/V08-00-05/                    ${TAG}_zz_4l_powheg

# ttV
./writeConfig_80X.sh /${hadoopdirv2}/ttWJets_13TeV_madgraphMLM_${miniaodv2}_v0-v1/V08-00-05/                                    ${TAG}_ttw_incl_mgmlm
./writeConfig_80X.sh /${hadoopdirv2}/ttZJets_13TeV_madgraphMLM_${miniaodv2}_v0-v1/V08-00-05/                                    ${TAG}_ttz_incl_mgmlm
./writeConfig_80X.sh /${hadoopdirv2}/ttbb_4FS_ckm_amcatnlo_madspin_pythia8_${miniaodv2}_v0_ext1-v1/V08-00-05/                   ${TAG}_ttbb_incl_amcnlo
./writeConfig_80X.sh /${hadoopdirv2}/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_${miniaodv2}_v0-v1/V08-00-05/         ${TAG}_ttz_2l2n_amcnlo
./writeConfig_80X.sh /${hadoopdirv2}/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_${miniaodv2}_v0-v1/V08-00-05/                  ${TAG}_ttz_qq_amcnlo
./writeConfig_80X.sh /${hadoopdirv2}/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_${miniaodv2}_v0-v1/V08-00-05/      ${TAG}_ttg_incl_amcnlo
./writeConfig_80X.sh /${hadoopdirv2}/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_${miniaodv2}_v0-v1/V08-00-05/ ${TAG}_ttw_ln_amcnlo
./writeConfig_80X.sh /${hadoopdirv2}/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_${miniaodv2}_v0-v1/V08-00-05/  ${TAG}_ttw_qq_amcnlo

# VVV
./writeConfig_80X.sh /${hadoopdirv2}/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8_${miniaodv2}_v0-v1/V08-00-05/ ${TAG}_www_incl_amcnlo
./writeConfig_80X.sh /${hadoopdirv2}/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_${miniaodv2}_v0-v1/V08-00-05/    ${TAG}_wwz_incl_amcnlo
./writeConfig_80X.sh /${hadoopdirv2}/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_${miniaodv2}_v0-v1/V08-00-05/    ${TAG}_wzz_incl_amcnlo
./writeConfig_80X.sh /${hadoopdirv2}/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_${miniaodv2}_v0-v1/V08-00-05/    ${TAG}_zzz_incl_amcnlo

# # WJets
./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_${miniaodv2}_v0-v1/V08-00-05/                   ${TAG}_wjets_incl_amcnlo
./writeConfig_80X.sh /${hadoopdirv2}/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0-v1/V08-00-05/                      ${TAG}_wgjets_incl_mgmlm
./writeConfig_80X.sh /${hadoopdirv2}/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_${miniaodv2}_v0_ext1-v1/V08-00-05/                ${TAG}_wgjets_incl_amcnlo
./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0_ext1-v1/V08-00-05/ ${TAG}_wjets_ht1200_mgmlm
./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0_ext1-v1/V08-00-05/	${TAG}_wjets_ht2500_mgmlm
./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0_ext1-v1/V08-00-05/	${TAG}_wjets_ht800_mgmlm
./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0-v1/V08-00-05/		${TAG}_wjets_ht600_mgmlm
./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0_ext1-v1/V08-00-05/	${TAG}_wjets_ht400_mgmlm
./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0_ext1-v1/V08-00-05/	${TAG}_wjets_ht200_mgmlm
./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0_ext1-v1/V08-00-05/   ${TAG}_wjets_ht100_mgmlm

# other ewk contamination
./writeConfig_80X.sh /${hadoopdirv2}/ZNuNuGJets_MonoPhoton_PtG-130_TuneCUETP8M1_13TeV-madgraph_RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-09/ ${TAG}_znunugamma_ptg130_mgmlm
./writeConfig_80X.sh /${hadoopdirv2}/ZNuNuGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-09/      ${TAG}_znunugamma_ptg40_mgmlm
./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-05/ ${TAG}_ttgamma_incl_amcnlo

# signal
./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2_fastsim/SMS-T5ZZ_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-09/ ${TAG}_t5zz_80x_v2
./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2_fastsim/SMS-TChiWZ_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/V08-00-09/ ${TAG}_tchiwz_80x_v2

# samples for closure
./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0-v1/V08-00-05/             ${TAG}_dy_m1050_mgmlm
./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0_ext1-v1/V08-00-05             ${TAG}_dy_m50_mgmlm_ext1
./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0_ext1-v1/V08-00-05 ${TAG}_dy_m50_mgmlm_ht100_ext1
./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0_ext1-v1/V08-00-05 ${TAG}_dy_m50_mgmlm_ht200_ext1
./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0_ext1-v1/V08-00-05 ${TAG}_dy_m50_mgmlm_ht400_ext1
# ./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0-v1/V08-00-05      ${TAG}_dy_m50_mgmlm_ht600
./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0_ext1-v1/V08-00-05 ${TAG}_dy_m50_mgmlm_ht600_ext1

./writeConfig_80X.sh /${hadoopdirv2}/GJets_DR-0p4_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0-v1/V08-00-05  ${TAG}_gjetsht40_dr0p4_mgmlm 
./writeConfig_80X.sh /${hadoopdirv2}/GJets_DR-0p4_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0-v1/V08-00-05 ${TAG}_gjetsht100_dr0p4_mgmlm
./writeConfig_80X.sh /${hadoopdirv2}/GJets_DR-0p4_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0-v1/V08-00-05 ${TAG}_gjetsht200_dr0p4_mgmlm
./writeConfig_80X.sh /${hadoopdirv2}/GJets_DR-0p4_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0-v1/V08-00-05 ${TAG}_gjetsht400_dr0p4_mgmlm
./writeConfig_80X.sh /${hadoopdirv2}/GJets_DR-0p4_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_v0-v1/V08-00-05 ${TAG}_gjetsht600_dr0p4_mgmlm

# ######################################################################################
# # all the MC and DATA for the MET study
# # main samples
# ######################################################################################
# # all the data for the MET study
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/DATA/DoubleEG_Run2015C_25ns-16Dec2015-v1/CMS3_V07-06-03/   ${TAG}_data_2015C25ns16Dec2015_ee
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/DATA/DoubleEG_Run2015D-16Dec2015-v2/CMS3_V07-06-03/        ${TAG}_data_2015D25ns16Dec2015_ee
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/DATA/DoubleMuon_Run2015C_25ns-16Dec2015-v1/CMS3_V07-06-03/ ${TAG}_data_2015C25ns16Dec2015_mm
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/DATA/DoubleMuon_Run2015D-16Dec2015-v1/CMS3_V07-06-03/      ${TAG}_data_2015D25ns16Dec2015_mm
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/DATA/MuonEG_Run2015C_25ns-16Dec2015-v1/CMS3_V07-06-03/     ${TAG}_data_2015C25ns16Dec2015_me
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/DATA/MuonEG_Run2015D-16Dec2015-v1/CMS3_V07-06-03/          ${TAG}_data_2015D25ns16Dec2015_me


# #####==============================
# # DYJetsToLL
# #####==============================
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/V/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/v1/CMS3_V07-06-03/     ${TAG}_DYJetsToLL_M-50_amcNLO_v1
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/V/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/v1/CMS3_V07-06-03/ ${TAG}_DYJetsToLL_M-10to50_amcNLO_v1

# #./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/V07-06-03_MC       ${TAG}_DYJetsToLL_M-50_madgraph
# #./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/V/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ext4-v1/CMS3_V07-06-03/     ${TAG}_DYJetsToLL_M-50_amcNLO_ext4-v1
# #./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/V/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/HCALdebug-v1/CMS3_V07-06-03/     ${TAG}_DYJetsToLL_M-50_amcNLO_HCALdebug-v1
# #./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/V/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ext3-v1/CMS3_V07-06-03/     ${TAG}_DYJetsToLL_M-10to50_amcNLO_ext3-v1
# #./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/V/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ext1-v1/CMS3_V07-06-03/     ${TAG}_DYJetsToLL_M-10to50_amcNLO_ext1-v1

# #####==============================
# # TTbar
# #####==============================
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/TT/TTTo2L2Nu_13TeV-powheg/v1/CMS3_V07-06-03/		${TAG}_ttTo2L2Nu_powheg

# #./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/TT/TTTo2L2Nu_13TeV-powheg/ext-v1/CMS3_V07-06-03/		${TAG}_ttTo2L2Nu_powheg
# #./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/V07-06-03_MC/		${TAG}_ttjets_2L-madgraph
# #./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/V07-06-03_MC/		${TAG}_4T_amcNLO
# #./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/V07-06-03_MC/		${TAG}_ttjets_pythia

# #####==============================
# # ZZ
# #####==============================
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/VV/ZZTo2L2Nu_13TeV_powheg_pythia8/CMS3_V07-06-03/              ${TAG}_ZZTo2L2Nu_13TeV_powheg_pythia8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/VV/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/CMS3_V07-06-03/ ${TAG}_ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/VV/ZZTo4L_13TeV_powheg_pythia8/CMS3_V07-06-03/                 ${TAG}_ZZTo4L_13TeV_powheg_pythia8

# #####==============================
# # WZ
# #####==============================
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/VV/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/CMS3_V07-06-03/	${TAG}_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8

# #####==============================
# # WW
# #####==============================
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/VV/WWTo2L2Nu_13TeV-powheg/CMS3_V07-06-03/	${TAG}_WWTo2L2Nu_13TeV-powheg

# #####==============================
# # Single Top
# #####==============================
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/V07-06-03_MC/	${TAG}_ST_tW_antitop_5f_inclusiveDecays_13TeV
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/V07-06-03_MC/	${TAG}_ST_tW_top_5f_inclusiveDecays_13TeV

# #####==============================
# # TTV
# #####==============================
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/TTV/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/CMS3_V07-06-03/ ${TAG}_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/TTV/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/CMS3_V07-06-03/  ${TAG}_TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/TTV/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/CMS3_V07-06-03/      ${TAG}_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/TTV/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/CMS3_V07-06-03/                  ${TAG}_TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/TTV/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/CMS3_V07-06-03/         ${TAG}_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix_RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/V07-06-03_MC/ ${TAG}_ttHJetToNonbb_M125_13TeV

# #####==============================
# # VVV
# #####==============================
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/VVV/WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8/CMS3_V07-06-03/    ${TAG}_WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/VVV/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/CMS3_V07-06-03/ ${TAG}_WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_76MiniAODv2/VVV/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/CMS3_V07-06-03/    ${TAG}_WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8



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







# rare samples. Will decide on the fly which we need for early data studies
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_sttwatop_25ns_powp8  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2/V07-04-11/     ${TAG}_sttwtop_25ns_powp8   
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WWTo2L2Nu_13TeV-powheg_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/                ${TAG}_ww2l2nu_25ns_powp8   
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/      ${TAG}_vv2l2nu_25ns_nlo 
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/        ${TAG}_wz3lnu_25ns_powp8   
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WWTo2L2Nu_13TeV-powheg_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/                ${TAG}_ww2l2nu_25ns_powp8   
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/           ${TAG}_zzz_25ns_nlo  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/           ${TAG}_wwz_25ns_nlo  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/           ${TAG}_wzz_25ns_nlo  


# all the data for dec
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_25ns_DoubleMuon_MINIAOD_05Oct2015-v1/merged/V07-04-11/   ${TAG}_data_2015C25ns05Oct2015_mm
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_25ns_MuonEG_MINIAOD_05Oct2015-v1/merged/V07-04-11/       ${TAG}_data_2015C25ns05Oct2015_em
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_25ns_SinglePhoton_MINIAOD_05Oct2015-v1/merged/V07-04-11/ ${TAG}_data_2015C25ns05Oct2015_ph
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_25ns_DoubleEG_MINIAOD_05Oct2015-v1/merged/V07-04-11/     ${TAG}_data_2015C25ns05Oct2015_ee
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_DoubleEG_MINIAOD_PromptReco-v3/merged/V07-04-09/         ${TAG}_data_2015D25nsPrompt_ee
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_SinglePhoton_MINIAOD_PromptReco-v3/merged/V07-04-09/     ${TAG}_data_2015D25nsPrompt_ph
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_DoubleMuon_MINIAOD_PromptReco-v3/merged/V07-04-09/       ${TAG}_data_2015D25nsPrompt_mm
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_MuonEG_MINIAOD_PromptReco-v3/merged/V07-04-09/           ${TAG}_data_2015D25nsPrompt_em
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_DoubleEG_MINIAOD_PromptReco-v4/merged/V07-04-11/         ${TAG}_data_2015D25nsPromptv4_ee
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_SinglePhoton_MINIAOD_PromptReco-v4/merged/V07-04-11/     ${TAG}_data_2015D25nsPromptv4_ph
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_DoubleMuon_MINIAOD_PromptReco-v4/merged/V07-04-11/       ${TAG}_data_2015D25nsPromptv4_mm
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_MuonEG_MINIAOD_PromptReco-v4/merged/V07-04-11/           ${TAG}_data_2015D25nsPromptv4_em
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_DoubleEG_MINIAOD_05Oct2015-v1/merged//V07-04-11/         ${TAG}_data_2015D25ns05Oct2015_ee
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_DoubleMuon_MINIAOD_05Oct2015-v1/merged//V07-04-11/       ${TAG}_data_2015D25ns05Oct2015_mm
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_MuonEG_MINIAOD_05Oct2015-v2/merged//V07-04-11/           ${TAG}_data_2015D25ns05Oct2015_em
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_SinglePhoton_MINIAOD_05Oct2015-v1/merged//V07-04-11/     ${TAG}_data_2015D25ns05Oct2015_ph

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/            ${TAG}_dyjetsll_25ns_m50nlo  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/        ${TAG}_dyjetsll_25ns_m1050nlo
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTTo2L2Nu_13TeV-powheg_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/                                             ${TAG}_tt2lnu_25ns_php8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_sttwatop_25ns_powp8  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2/V07-04-11/     ${TAG}_sttwtop_25ns_powp8   
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/            ${TAG}_ttg_25ns_nlo      
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2/V07-04-11/          ${TAG}_ttzllnunu_25ns_nlo 
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/            ${TAG}_ttzqq_25ns_nlo     
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/       ${TAG}_ttwlnu_25ns_nlo
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/        ${TAG}_ttw2q_25ns_nlo 

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/       ${TAG}_wz2l2q_25ns_nlo  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/       ${TAG}_zz2l2q_25ns_nlo  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_vhnonbb_25ns_nlo 
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/      ${TAG}_vv2l2nu_25ns_nlo 
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ZZTo2L2Nu_13TeV_powheg_pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2/V07-04-11/                    ${TAG}_zz2l2nu_25ns_powp8 
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/        ${TAG}_wz3lnu_25ns_powp8   
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ZZTo4L_13TeV_powheg_pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2/V07-04-11/           ${TAG}_zz4l_25ns_php8    
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WWTo2L2Nu_13TeV-powheg_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/                ${TAG}_ww2l2nu_25ns_powp8   
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/           ${TAG}_zzz_25ns_nlo  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/           ${TAG}_wwz_25ns_nlo  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/           ${TAG}_wzz_25ns_nlo  

# # for closure studies
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/             ${TAG}_zjetsll_25ns_m50mlm  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_zjetsllht100_25ns_m50mlm  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_zjetsllht200_25ns_m50mlm  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2/V07-04-11/ ${TAG}_zjetsllht400_25ns_m50mlm  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/ ${TAG}_zjetsllht600_25ns_m50mlm  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/            ${TAG}_gjets_25ns_ht40mlm  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/           ${TAG}_gjets_25ns_ht100mlm  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/           ${TAG}_gjets_25ns_ht200mlm  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/           ${TAG}_gjets_25ns_ht400mlm  
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns_MiniAODv2/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/V07-04-11/           ${TAG}_gjets_25ns_ht600mlm  


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
