#!/bin/bash

#
# All MT2 related datasets available on hadoop
#

# compile files
cd ..
make -j8
cd -

# copy compiled files
cp -r ../*.so ../pileup_jul21_nominalUpDown.root ../xsec_higgsino.root ../btagsf ../leptonSFs ../TChiWZ_entries_V08-00-05_FS.root ../xsec_susy_13tev.root ../T5ZZ_entries.root ../jetCorrections ../processBaby ../MVAinput ../../json/*.txt ../TChiHZ_HToBB_ZToLL.root job_input/ 

source ../../ZMET2015/settings.sh 

# update tag
TAG=${analysis_version}

# 2016 data

# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016B_DoubleEG_MINIAOD_23Sep2016-v3/merged/V08-00-14/     ${TAG}_data_2016B_23sep2016rereco_ee_v3
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016B_DoubleMuon_MINIAOD_23Sep2016-v3/merged/V08-00-14/   ${TAG}_data_2016B_23sep2016rereco_mm_v3
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016B_MuonEG_MINIAOD_23Sep2016-v3/merged/V08-00-14/       ${TAG}_data_2016B_23sep2016rereco_em_v3
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016B_SinglePhoton_MINIAOD_23Sep2016-v3/merged/V08-00-14/ ${TAG}_data_2016B_23sep2016rereco_ph_v3
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016B_SingleMuon_MINIAOD_23Sep2016-v3/merged/V08-00-14/   ${TAG}_data_2016B_23sep2016rereco_sm_v3

# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016C_DoubleEG_MINIAOD_23Sep2016-v1/merged/V08-00-14/      ${TAG}_data_2016C_23sep2016rereco_ee_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016C_DoubleMuon_MINIAOD_23Sep2016-v1/merged/V08-00-14/    ${TAG}_data_2016C_23sep2016rereco_mm_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016C_MuonEG_MINIAOD_23Sep2016-v1/merged/V08-00-14/        ${TAG}_data_2016C_23sep2016rereco_em_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016C_SinglePhoton_MINIAOD_23Sep2016-v1/merged/V08-00-14/  ${TAG}_data_2016C_23sep2016rereco_ph_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016C_SingleMuon_MINIAOD_23Sep2016-v1/merged/V08-00-14/    ${TAG}_data_2016C_23sep2016rereco_sm_v1

# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016D_DoubleEG_MINIAOD_23Sep2016-v1/merged/V08-00-14/      ${TAG}_data_2016D_23sep2016rereco_ee_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016D_DoubleMuon_MINIAOD_23Sep2016-v1/merged/V08-00-14/    ${TAG}_data_2016D_23sep2016rereco_mm_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016D_MuonEG_MINIAOD_23Sep2016-v1/merged/V08-00-14/        ${TAG}_data_2016D_23sep2016rereco_em_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016D_SinglePhoton_MINIAOD_23Sep2016-v1/merged/V08-00-14/  ${TAG}_data_2016D_23sep2016rereco_ph_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016D_SingleMuon_MINIAOD_23Sep2016-v1/merged/V08-00-14/    ${TAG}_data_2016D_23sep2016rereco_sm_v1

# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016E_DoubleEG_MINIAOD_23Sep2016-v1/merged/V08-00-14/      ${TAG}_data_2016E_23sep2016rereco_ee_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016E_DoubleMuon_MINIAOD_23Sep2016-v1/merged/V08-00-14/    ${TAG}_data_2016E_23sep2016rereco_mm_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016E_MuonEG_MINIAOD_23Sep2016-v1/merged/V08-00-14/        ${TAG}_data_2016E_23sep2016rereco_em_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016E_SinglePhoton_MINIAOD_23Sep2016-v1/merged/V08-00-14/  ${TAG}_data_2016E_23sep2016rereco_ph_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016E_SingleMuon_MINIAOD_23Sep2016-v1/merged/V08-00-14/    ${TAG}_data_2016E_23sep2016rereco_sm_v1

# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016F_DoubleEG_MINIAOD_23Sep2016-v1/merged/V08-00-14/      ${TAG}_data_2016F_23sep2016rereco_ee_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016F_DoubleMuon_MINIAOD_23Sep2016-v1/merged/V08-00-14/    ${TAG}_data_2016F_23sep2016rereco_mm_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016F_MuonEG_MINIAOD_23Sep2016-v1/merged/V08-00-14/        ${TAG}_data_2016F_23sep2016rereco_em_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016F_SinglePhoton_MINIAOD_23Sep2016-v1/merged/V08-00-14/  ${TAG}_data_2016F_23sep2016rereco_ph_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016F_SingleMuon_MINIAOD_23Sep2016-v1/merged/V08-00-14/    ${TAG}_data_2016F_23sep2016rereco_sm_v1

# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016G_DoubleEG_MINIAOD_23Sep2016-v1/merged/V08-00-14/      ${TAG}_data_2016G_23sep2016rereco_ee_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016G_DoubleMuon_MINIAOD_23Sep2016-v1/merged/V08-00-14/    ${TAG}_data_2016G_23sep2016rereco_mm_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016G_MuonEG_MINIAOD_23Sep2016-v1/merged/V08-00-14/        ${TAG}_data_2016G_23sep2016rereco_em_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016G_SinglePhoton_MINIAOD_23Sep2016-v1/merged/V08-00-14/  ${TAG}_data_2016G_23sep2016rereco_ph_v1
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016G_SingleMuon_MINIAOD_23Sep2016-v1/merged/V08-00-14/    ${TAG}_data_2016G_23sep2016rereco_sm_v1

# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016H_DoubleEG_MINIAOD_PromptReco-v2/merged/V08-00-14/     ${TAG}_data_2016H_Prompt_ee_v2
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016H_DoubleMuon_MINIAOD_PromptReco-v2/merged/V08-00-14/   ${TAG}_data_2016H_Prompt_mm_v2
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016H_MuonEG_MINIAOD_PromptReco-v2/merged/V08-00-14/       ${TAG}_data_2016H_Prompt_em_v2
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016H_SinglePhoton_MINIAOD_PromptReco-v2/merged/V08-00-14/ ${TAG}_data_2016H_Prompt_ph_v2
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016H_SingleMuon_MINIAOD_PromptReco-v2/merged/V08-00-14/   ${TAG}_data_2016H_Prompt_sm_v2

# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016H_DoubleEG_MINIAOD_PromptReco-v3/merged/V08-00-15/     ${TAG}_data_2016H_Prompt_ee_v3
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016H_DoubleMuon_MINIAOD_PromptReco-v3/merged/V08-00-15/   ${TAG}_data_2016H_Prompt_mm_v3
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016H_MuonEG_MINIAOD_PromptReco-v3/merged/V08-00-15/       ${TAG}_data_2016H_Prompt_em_v3
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016H_SinglePhoton_MINIAOD_PromptReco-v3/merged/V08-00-15/ ${TAG}_data_2016H_Prompt_ph_v3
# ./writeConfig_80X.sh /hadoop/cms/store/group/snt/run2_data/Run2016H_SingleMuon_MINIAOD_PromptReco-v3/merged/V08-00-15/   ${TAG}_data_2016H_Prompt_sm_v3

# 2016 Moriond MC

hadoopdirv2="hadoop/cms/store/group/snt/run2_moriond17"
miniaodv2="RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6"

# # DY
# ./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_${miniaodv2}-v1/V08-00-16/ ${TAG}_dy_m1050_amcnlo
# #./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_${miniaodv2}-v1/V08-00-16/ ${TAG}_dy_m50_amcnlo # missing in moriond17

# # ttbar
# ./writeConfig_80X.sh /${hadoopdirv2}/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/             ${TAG}_ttbar_dilep_mgmlm
# #./writeConfig_80X.sh /${hadoopdirv2}/TTTo2L2Nu_13TeV-powheg_${miniaodv2}_ext1-v1/V08-00-16/                                      ${TAG}_ttbar_dilep_powheg # missing in moriond17
# ./writeConfig_80X.sh /${hadoopdirv2}/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/    ${TAG}_ttbar_1ltop_mgmlm
# ./writeConfig_80X.sh /${hadoopdirv2}/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1v1/V08-00-16/ ${TAG}_ttbar_1ltbr_mgmlm_ext
# ./writeConfig_80X.sh /${hadoopdirv2}/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16/        ${TAG}_ttbar_dilep_mgmlm_ext
# #./writeConfig_80X.sh /${hadoopdirv2}/TTTo2L2Nu_TuneCUETP8M1_alphaS01273_13TeV-powheg-pythia8_${miniaodv2}-v1/V08-00-16/          ${TAG}_ttbar_dilep_powheg_alphas01273 # missing in moriond17

# # single top
# #./writeConfig_80X.sh /${hadoopdirv2}/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1_${miniaodv2}-v1/V08-00-16/     ${TAG}_stt_top_lepdec_powheg # missing in moriond17
# #./writeConfig_80X.sh /${hadoopdirv2}/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1_${miniaodv2}-v1/V08-00-16/ ${TAG}_stt_antitop_lepdec_powheg # missing in moriond17
# ./writeConfig_80X.sh /${hadoopdirv2}/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1_${miniaodv2}-v1/V08-00-16/           ${TAG}_sttw_antitop_nofullhaddecay_powheg
# ./writeConfig_80X.sh /${hadoopdirv2}/ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1_${miniaodv2}-v1/V08-00-16/	      ${TAG}_sttw_top_nofullhaddecay_powheg	  
# ./writeConfig_80X.sh /${hadoopdirv2}/tZq_ll_4f_13TeV-amcatnlo-pythia8_${miniaodv2}-v1/V08-00-16/	      ${TAG}_tzq_ll_amcnlo
# # tWZ
# ./writeConfig_80X.sh /${hadoopdirv2}/ST_tWll_5f_LO_13TeV-MadGraph-pythia8_${miniaodv2}-v1/V08-00-16/	      ${TAG}_sttwll_madgraph

# # VV
# ./writeConfig_80X.sh /${hadoopdirv2}/WWTo2L2Nu_13TeV-powheg_${miniaodv2}-v1/V08-00-16/                         ${TAG}_ww_2l2nu_powheg
# ./writeConfig_80X.sh /${hadoopdirv2}/WWToLNuQQ_13TeV-powheg_${miniaodv2}-v1/V08-00-16/                         ${TAG}_ww_lnuqq_powheg
# ./writeConfig_80X.sh /${hadoopdirv2}/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_${miniaodv2}-v3/V08-00-16/ ${TAG}_wz_lnqq_amcnlo
# ./writeConfig_80X.sh /${hadoopdirv2}/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_${miniaodv2}-v1/V08-00-16/   ${TAG}_wz_1l3n_amcnlo
# #./writeConfig_80X.sh /${hadoopdirv2}/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_${miniaodv2}-v1/V08-00-16/    ${TAG}_wz_2l2q_amcnlo # missing in moriond17
# ./writeConfig_80X.sh /${hadoopdirv2}/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8_${miniaodv2}-v1/V08-00-16/     ${TAG}_wz_3lnu_powheg
# ./writeConfig_80X.sh /${hadoopdirv2}/ZZTo2L2Nu_13TeV_powheg_pythia8_${miniaodv2}-v1/V08-00-16/                 ${TAG}_zz_2l2n_powheg
# ./writeConfig_80X.sh /${hadoopdirv2}/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_${miniaodv2}-v1/V08-00-16/    ${TAG}_zz_2l2q_amcnlo
# ./writeConfig_80X.sh /${hadoopdirv2}/ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8_${miniaodv2}-v1/V08-00-16/   ${TAG}_zz_2q2n_amcnlo
# ./writeConfig_80X.sh /${hadoopdirv2}/ZZTo4L_13TeV_powheg_pythia8_${miniaodv2}-v1/V08-00-16/                    ${TAG}_zz_4l_powheg

# # ttV
# ./writeConfig_80X.sh /${hadoopdirv2}/ttWJets_13TeV_madgraphMLM_${miniaodv2}-v1/V08-00-16/                                    ${TAG}_ttw_incl_mgmlm
# ./writeConfig_80X.sh /${hadoopdirv2}/ttZJets_13TeV_madgraphMLM_${miniaodv2}-v1/V08-00-16/                                    ${TAG}_ttz_incl_mgmlm
# #./writeConfig_80X.sh /${hadoopdirv2}/ttbb_4FS_ckm_amcatnlo_madspin_pythia8_${miniaodv2}_ext1-v1/V08-00-16/                   ${TAG}_ttbb_incl_amcnlo # missing in moriond17
# ./writeConfig_80X.sh /${hadoopdirv2}/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_${miniaodv2}-v1/V08-00-16/         ${TAG}_ttz_2l2n_amcnlo
# #./writeConfig_80X.sh /${hadoopdirv2}/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_${miniaodv2}-v1/V08-00-16/                  ${TAG}_ttz_qq_amcnlo # missing in moriond17
# ./writeConfig_80X.sh /${hadoopdirv2}/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_${miniaodv2}-v1/V08-00-16/      ${TAG}_ttg_incl_amcnlo
# ./writeConfig_80X.sh /${hadoopdirv2}/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_${miniaodv2}_ext1-v3/V08-00-16/ ${TAG}_ttw_ln_amcnlo_ext1
# ./writeConfig_80X.sh /${hadoopdirv2}/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_${miniaodv2}_ext2-v1/V08-00-16/ ${TAG}_ttw_ln_amcnlo_ext2
# ./writeConfig_80X.sh /${hadoopdirv2}/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_${miniaodv2}-v1/V08-00-16/  ${TAG}_ttw_qq_amcnlo
# #./writeConfig_80X.sh /${hadoopdirv2}/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14_ext1-v1/V08-00-12/ ${TAG}_ttz_2l2n_amcnlo_ext # missing in moriond17
# ./writeConfig_80X.sh /${hadoopdirv2}/ttHTobb_M125_13TeV_powheg_pythia8_${miniaodv2}-v1/V08-00-16/      ${TAG}_tth_bb_powheg
# ./writeConfig_80X.sh /${hadoopdirv2}/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8_${miniaodv2}-v1/V08-00-16/      ${TAG}_tth_nonbb_powheg

# # VVV
# ./writeConfig_80X.sh /${hadoopdirv2}/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8_${miniaodv2}-v1/V08-00-16/ ${TAG}_www_incl_amcnlo
# ./writeConfig_80X.sh /${hadoopdirv2}/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_${miniaodv2}-v1/V08-00-16/    ${TAG}_wwz_incl_amcnlo
# ./writeConfig_80X.sh /${hadoopdirv2}/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_${miniaodv2}-v1/V08-00-16/    ${TAG}_wzz_incl_amcnlo
# ./writeConfig_80X.sh /${hadoopdirv2}/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_${miniaodv2}-v1/V08-00-16/    ${TAG}_zzz_incl_amcnlo

# # # WJets
# ./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_${miniaodv2}-v1/V08-00-16/                   ${TAG}_wjets_incl_amcnlo
# #./writeConfig_80X.sh /${hadoopdirv2}/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/                      ${TAG}_wgjets_incl_mgmlm # missing in moriond17
# ./writeConfig_80X.sh /${hadoopdirv2}/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_${miniaodv2}_ext1-v1/V08-00-16/                ${TAG}_wgjets_incl_amcnlo
# ./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/ ${TAG}_wjets_ht1200_mgmlm
# ./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16/	${TAG}_wjets_ht2500_mgmlm
# ./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16/	${TAG}_wjets_ht800_mgmlm
# ./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16/	${TAG}_wjets_ht600_mgmlm
# ./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16/	${TAG}_wjets_ht400_mgmlm
# ./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16/	${TAG}_wjets_ht200_mgmlm
# ./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16/   ${TAG}_wjets_ht100_mgmlm
# ./writeConfig_80X.sh /${hadoopdirv2}/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/                    ${TAG}_wjets_incl_mgmlm

# # other ewk contamination
# ./writeConfig_80X.sh /${hadoopdirv2}/ZNuNuGJets_MonoPhoton_PtG-130_TuneCUETP8M1_13TeV-madgraph_${miniaodv2}-v1/V08-00-16/ ${TAG}_znunugamma_ptg130_mgmlm
# ./writeConfig_80X.sh /${hadoopdirv2}/ZNuNuGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph_${miniaodv2}-v1/V08-00-16/      ${TAG}_znunugamma_ptg40_mgmlm

# # # signal
# # ./writeConfig_80X.sh /${hadoopdirv2}_fastsim/SMS-T5ZZ_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-09/ ${TAG}_t5zz_80x_v2
# # ./writeConfig_80X.sh /${hadoopdirv2}_fastsim/SMS-TChiWZ_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/V08-00-09/ ${TAG}_tchiwz_80x_v2
# # ./writeConfig_80X.sh /${hadoopdirv2}_fastsim/SMS-TChiHZ_HToBB_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-09/ ${TAG}_tchihz_80x_v2

# # samples for closure
# ./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/             ${TAG}_dy_m1050_mgmlm
# ./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v2/V08-00-16             ${TAG}_dy_m50_mgmlm_ext1
# ./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16 ${TAG}_dy_m50_mgmlm_ht100
# #./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16 ${TAG}_dy_m50_mgmlm_ht100_ext1 # missing in moriond17
# ./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16 ${TAG}_dy_m50_mgmlm_ht200_ext1
# ./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16 ${TAG}_dy_m50_mgmlm_ht400_ext1
# ./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v2/V08-00-16 ${TAG}_dy_m50_mgmlm_ht600
# ./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16 ${TAG}_dy_m50_mgmlm_ht800
# ./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16 ${TAG}_dy_m50_mgmlm_ht1200
# ./writeConfig_80X.sh /${hadoopdirv2}/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16 ${TAG}_dy_m50_mgmlm_ht2500

# #./writeConfig_80X.sh /${hadoopdirv2}/GJets_DR-0p4_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16  ${TAG}_gjetsht40_dr0p4_mgmlm 
# #./writeConfig_80X.sh /${hadoopdirv2}/GJets_DR-0p4_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16 ${TAG}_gjetsht100_dr0p4_mgmlm
# #./writeConfig_80X.sh /${hadoopdirv2}/GJets_DR-0p4_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16 ${TAG}_gjetsht200_dr0p4_mgmlm
# #./writeConfig_80X.sh /${hadoopdirv2}/GJets_DR-0p4_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16 ${TAG}_gjetsht400_dr0p4_mgmlm # missing in moriond17
# #./writeConfig_80X.sh /${hadoopdirv2}/GJets_DR-0p4_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16 ${TAG}_gjetsht600_dr0p4_mgmlm

# ./writeConfig_80X.sh /${hadoopdirv2}/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16/  ${TAG}_gjetsht40_dr0p05_mgmlm_ext1 
# ./writeConfig_80X.sh /${hadoopdirv2}/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/ ${TAG}_gjetsht100_dr0p05_mgmlm_nonext
# ./writeConfig_80X.sh /${hadoopdirv2}/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16/ ${TAG}_gjetsht200_dr0p05_mgmlm_ext1
# ./writeConfig_80X.sh /${hadoopdirv2}/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/ ${TAG}_gjetsht400_dr0p05_mgmlm_nonext
# ./writeConfig_80X.sh /${hadoopdirv2}/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/ ${TAG}_gjetsht600_dr0p05_mgmlm_nonext
# ./writeConfig_80X.sh /${hadoopdirv2}/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16/ ${TAG}_gjetsht600_dr0p05_mgmlm_ext1

# # QCD
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8_${miniaodv2}-v1/V08-00-16/      ${TAG}_qcdpt20_emenriched_nonext
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8_${miniaodv2}-v1/V08-00-16/      ${TAG}_qcdpt30_emenriched_nonext
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8_${miniaodv2}_ext1-v1/V08-00-16/ ${TAG}_qcdpt30_emenriched_ext1
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8_${miniaodv2}-v1/V08-00-16/      ${TAG}_qcdpt50_emenriched_nonext
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8_${miniaodv2}_ext1-v1/V08-00-16/     ${TAG}_qcdpt80_emenriched_ext1
# #./writeConfig_80X.sh /${hadoopdirv2}/QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8_${miniaodv2}-v1/V08-00-16/    ${TAG}_qcdpt120_emenriched_nonext # missing in moriond17
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8_${miniaodv2}-v1/V08-00-16/    ${TAG}_qcdpt170_emenriched_nonext
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8_${miniaodv2}-v1/V08-00-16/    ${TAG}_qcdpt300_emenriched_nonext

# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/        ${TAG}_qcdht100_nonext
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/        ${TAG}_qcdht200_nonext
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16/   ${TAG}_qcdht200_ext1
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/        ${TAG}_qcdht300_nonext
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16/   ${TAG}_qcdht300_ext1
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/        ${TAG}_qcdht500_nonext
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v2/V08-00-16/   ${TAG}_qcdht500_ext1
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/       ${TAG}_qcdht700_nonext
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16/  ${TAG}_qcdht700_ext1
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/      ${TAG}_qcdht1000_nonext
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16/ ${TAG}_qcdht1000_ext1
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/      ${TAG}_qcdht1500_nonext
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16/ ${TAG}_qcdht1500_ext1
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}-v1/V08-00-16/       ${TAG}_qcdht2000_nonext
# ./writeConfig_80X.sh /${hadoopdirv2}/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_${miniaodv2}_ext1-v1/V08-00-16/  ${TAG}_qcdht2000_ext1

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

