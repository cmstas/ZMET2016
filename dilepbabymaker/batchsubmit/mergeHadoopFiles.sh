#!/bin/bash

function run () {
    echo root -b -q mergeHadoopFiles.C\(\"${HADOOPDIR}/${TAG}_$1/\",\"${OUTPUTDIR}/$1.root\"\)
    nohup nice -n 19 root -b -q mergeHadoopFiles.C\(\"${HADOOPDIR}/${TAG}_$1/\",\"${OUTPUTDIR}/$1.root\"\) >& merge_logs_${TAG}/log_merge_$1.txt &
}

source ../../ZMET2015/settings.sh 

TAG=${analysis_version}

HADOOPDIR=/hadoop/cms/store/user/${USER}/uaf8/dilepbabies/
OUTPUTDIR=/nfs-7/userdata/ZMEToutput/output/ZMETbabies/$TAG/

if [ ! -d "$OUTPUTDIR" ]; then
	mkdir -p $OUTPUTDIR
	chmod -R a+wrx $OUTPUTDIR
fi

if [ ! -d "merge_logs_${TAG}" ]; then
	mkdir merge_logs_${TAG}
fi

# # 2016 data
# run data_2016B_Prompt_ee_v2
# run data_2016B_Prompt_mm_v2
# run data_2016B_Prompt_em_v2
# run data_2016B_Prompt_ph_v2

# run data_2016C_Prompt_ee_v2
# run data_2016C_Prompt_mm_v2
# run data_2016C_Prompt_em_v2
# run data_2016C_Prompt_ph_v2

# run data_2016D_Prompt_ee_v2
# run data_2016D_Prompt_mm_v2
# run data_2016D_Prompt_em_v2
# run data_2016D_Prompt_ph_v2

# run data_2016E_Prompt_ee_v2
# run data_2016E_Prompt_mm_v2
# run data_2016E_Prompt_em_v2
# run data_2016E_Prompt_ph_v2

# run data_2016F_Prompt_ee_v1
# run data_2016F_Prompt_mm_v1
# run data_2016F_Prompt_em_v1
# run data_2016F_Prompt_ph_v1

# # 2016 MC

# # DY
# run dy_m1050_amcnlo
# run dy_m50_amcnlo

# # ttbar
# run ttbar_dilep_mgmlm
# run ttbar_dilep_powheg
# run ttbar_1ltop_mgmlm
# run ttbar_1ltbr_mgmlm

# # single top
# run sttw_antitop_powheg
# run sttw_top_powheg

# # VV
# run ww_2l2nu_powheg
# run ww_lnuqq_powheg
# run wz_lnqq_amcnlo
# run wz_1l3n_amcnlo
# run wz_2l2q_amcnlo
# run wz_3lnu_powheg
# run zz_2l2n_powheg
# run zz_2l2q_amcnlo
# run zz_2q2n_amcnlo
# run zz_4l_powheg

# # ttV
# run ttw_incl_mgmlm
# run ttz_incl_mgmlm
# run ttbb_incl_amcnlo
# run ttz_2l2n_amcnlo
# run ttz_qq_amcnlo
# run ttg_incl_mgmlm
# run ttw_ln_amcnlo
# run ttw_qq_amcnlo

# # VVV
# run www_incl_amcnlo
# run wwz_incl_amcnlo
# run wzz_incl_amcnlo
# run zzz_incl_amcnlo

# # WJets
# run wjets_incl_amcnlo
# run wgjets_incl_mgmlm
# run wgjets_incl_amcnlo
# run wjets_ht1200_mgmlm
# run wjets_ht2500_mgmlm
# run wjets_ht800_mgmlm
# run wjets_ht600_mgmlm
# run wjets_ht400_mgmlm
# run wjets_ht200_mgmlm
# run wjets_ht100_mgmlm

# run ttgamma_incl_amcnlo
# run znunugamma_ptg130_mgmlm
# run znunugamma_ptg40_mgmlm

# # samples for closure
# run dy_m1050_mgmlm
# run dy_m50_mgmlm_ext1
# run dy_m50_mgmlm_ht100_ext1
# run dy_m50_mgmlm_ht200_ext1
# run dy_m50_mgmlm_ht400_ext1
# run dy_m50_mgmlm_ht600_ext1

# # gjets
# run gjetsht100_dr0p4_mgmlm
# run gjetsht200_dr0p4_mgmlm
# run gjetsht400_dr0p4_mgmlm
# run gjetsht40_dr0p4_mgmlm
# run gjetsht600_dr0p4_mgmlm
# run gjetsht100_mgmlm

# # signal
# run t5zz_80x_v2
# run tchiwz_80x_v2

# above this is done
