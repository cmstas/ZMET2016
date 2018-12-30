#! /bin/bash

function skim
{   
    echo root -b -q skim_2j_gammalep_3lep.C\(\"${INDIR}/\",\"${OUTPUTDIR}\",\"$1\"\)
    nohup nice -n 19 root -b -q skim_2j_gammalep_3lep.C\(\"${INDIR}/\",\"${OUTPUTDIR}\",\"$1\"\) >& ${LOGDIR}/log_skim_${TAG}_$1.txt &
}

TAG=V08-22-08

INDIR=/hadoop/cms/store/user/${USER}/AutoTwopler_babies/merged/ZMET/${TAG}/output/
OUTPUTDIR=/nfs-7/userdata/ZMEToutput/output/ZMETbabies/${TAG}/skims
LOGDIR=skimLogs

mkdir -p $OUTPUTDIR
mkdir -p $LOGDIR
chmod -R a+wrx $OUTPUTDIR

# skim data_Run2016B_23sep2016rereco_ee
# skim data_Run2016B_23sep2016rereco_mm
# skim data_Run2016B_23sep2016rereco_em
# skim data_Run2016B_23sep2016rereco_ph
# skim data_Run2016B_23sep2016rereco_sm

# skim data_Run2016C_23sep2016rereco_ee
# skim data_Run2016C_23sep2016rereco_mm
# skim data_Run2016C_23sep2016rereco_em
# skim data_Run2016C_23sep2016rereco_ph
# skim data_Run2016C_23sep2016rereco_sm

# skim data_Run2016D_23sep2016rereco_ee
# skim data_Run2016D_23sep2016rereco_mm
# skim data_Run2016D_23sep2016rereco_em
# skim data_Run2016D_23sep2016rereco_ph
# skim data_Run2016D_23sep2016rereco_sm

# skim data_Run2016E_23sep2016rereco_ee
# skim data_Run2016E_23sep2016rereco_mm
# skim data_Run2016E_23sep2016rereco_em
# skim data_Run2016E_23sep2016rereco_ph
# skim data_Run2016E_23sep2016rereco_sm

# skim data_Run2016F_23sep2016rereco_ee
# skim data_Run2016F_23sep2016rereco_mm
# skim data_Run2016F_23sep2016rereco_em
# skim data_Run2016F_23sep2016rereco_ph
# skim data_Run2016F_23sep2016rereco_sm

# skim data_Run2016G_23sep2016rereco_ee
# skim data_Run2016G_23sep2016rereco_mm
# skim data_Run2016G_23sep2016rereco_em
# skim data_Run2016G_23sep2016rereco_ph
# skim data_Run2016G_23sep2016rereco_sm

# skim data_Run2016H_Prompt_ee
# skim data_Run2016H_Prompt_mm
# skim data_Run2016H_Prompt_em
# skim data_Run2016H_Prompt_ph
# skim data_Run2016H_Prompt_sm


# # 2016 MC

# # # DY
# skim dy_m1050_amcnlo
# skim dy_m50_amcnlo
# skim dy_m1050_mgmlm
# skim dy_m50_mgmlm_ext1

# # # ttbar
# #skim ttbar_dilep_powheg
# skim ttbar_1ltop_mgmlm_nonext
# skim ttbar_1ltop_mgmlm_ext1
# skim ttbar_1ltbr_mgmlm_nonext
# skim ttbar_1ltbr_mgmlm_ext1
# skim ttbar_dilep_mgmlm_nonext
# skim ttbar_dilep_mgmlm_ext1

# # # single top
# #skim stt_top_incdec_powheg
# skim stt_antitop_incdec_powheg
# skim sttw_antitop_nofullhaddecay_powheg
# skim sttw_top_nofullhaddecay_powheg	  
# skim tzq_ll_amcnlo
# skim sttwll_madgraph

# # # VV
# skim ww_2l2nu_powheg
# skim ww_lnuqq_powheg
# skim wz_lnqq_amcnlo
# skim wz_1l3n_amcnlo
# #skim wz_2l2q_amcnlo
# skim wz_3lnu_powheg
# skim zz_2l2n_powheg
# skim zz_2l2q_powheg
# skim zz_2q2n_amcnlo
# skim zz_4l_powheg

# # # ttV
# skim ttw_incl_mgmlm
# skim ttz_incl_mgmlm
# # #skim ttbb_incl_amcnlo
# skim ttz_2l2n_amcnlo
# # #skim ttz_qq_amcnlo
#skim ttg_incl_amcnlo
# skim ttw_ln_amcnlo_ext2
# skim ttw_qq_amcnlo
# # #skim ttz_2l2n_amcnlo_ext
# skim tth_bb_powheg
# skim tth_nonbb_powheg

# # # VVV
# skim www_incl_amcnlo
# skim wwz_incl_amcnlo
# skim wzz_incl_amcnlo
# skim zzz_incl_amcnlo

# # # # WJets
# skim wjets_incl_mgmlm
# skim wjets_ht1200_mgmlm_nonext
# skim wjets_ht2500_mgmlm_ext1
# skim wjets_ht800_mgmlm_ext1
# skim wjets_ht600_mgmlm_ext1
# skim wjets_ht400_mgmlm_ext1
# skim wjets_ht200_mgmlm_ext1
# skim wjets_ht100_mgmlm_ext1

# # # other ewk contamination
# skim wgjets_incl_mgmlm
# skim wgjets_incl_amcnlo
# skim wgjets_ptg40_mgmlm
# skim wgjets_ptg130_mgmlm
# skim znunugamma_ptg130_mgmlm
# skim znunugamma_ptg40_mgmlm

# # # signal
# # ./writeConfig_80X.sh /${hadoopdirv2}_fastsim/SMS-T5ZZ_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-09/ ${TAG}_t5zz_80x_v2
# # ./writeConfig_80X.sh /${hadoopdirv2}_fastsim/SMS-TChiWZ_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/V08-00-09/ ${TAG}_tchiwz_80x_v2
# # ./writeConfig_80X.sh /${hadoopdirv2}_fastsim/SMS-TChiHZ_HToBB_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-09/ ${TAG}_tchihz_80x_v2

# # # samples for closure
# skim dy_m50_mgmlm_ht100_nonext
# skim dy_m50_mgmlm_ht200_ext1
# skim dy_m50_mgmlm_ht400_ext1
# skim dy_m50_mgmlm_ht600_nonext
# skim dy_m50_mgmlm_ht800_nonext
# skim dy_m50_mgmlm_ht1200_nonext
# skim dy_m50_mgmlm_ht2500_nonext

# skim gjetsht40_dr0p4_mgmlm 
# skim gjetsht100_dr0p4_mgmlm
# skim gjetsht200_dr0p4_mgmlm
# #skim gjetsht400_dr0p4_mgmlm
# skim gjetsht600_dr0p4_mgmlm

# skim gjetsht40_dr0p05_mgmlm_ext1
# skim gjetsht100_dr0p05_mgmlm_nonext
# skim gjetsht200_dr0p05_mgmlm_ext1
# skim gjetsht400_dr0p05_mgmlm_nonext
# skim gjetsht600_dr0p05_mgmlm_ext1

# skim qcdpt20_emenriched_nonext
# skim qcdpt30_emenriched_nonext
# skim qcdpt30_emenriched_ext1 
# skim qcdpt50_emenriched_ext1 
# skim qcdpt80_emenriched_ext1
# skim qcdpt170_emenriched_nonext
# skim qcdpt300_emenriched_nonext

# skim qcdht100_nonext
# skim qcdht200_nonext
# skim qcdht200_ext1 
# skim qcdht300_nonext
# skim qcdht300_ext1 
# skim qcdht500_nonext
# skim qcdht500_ext1 
# skim qcdht700_nonext
# skim qcdht700_ext1 
# skim qcdht1000_nonext
# skim qcdht1000_ext1
# skim qcdht1500_nonext
# skim qcdht1500_ext1
# skim qcdht2000_nonext
# skim qcdht2000_ext1
