#! /bin/bash

function runskim
{
	infile=$1
	outfile=$2
	echo "Skimming with following command: root -b -q \"skimBaby.C+(\"$infile\", \"$outfile\")\""
	root -b -q "skimBaby.C+(\"$infile\", \"$outfile\")"

}

function skim
{   
	sample=$1
	echo "" > skim_log_$sample.txt
	indir="/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/" 
	for file in `ls $indir/$sample*`;do 
		filename=`basename $file`
	    nohup nice -n 19 `runskim $file "/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_$filename" >> skim_log_$sample.txt 2>&1`
	done
}

function skimbg
{   
	skim $1 &
}

# skimbg data_2016B_23sep2016rereco_ee
# skimbg data_2016B_23sep2016rereco_mm
# skimbg data_2016B_23sep2016rereco_em
# skimbg data_2016B_23sep2016rereco_ph
# skimbg data_2016B_23sep2016rereco_sm

# skimbg data_2016C_23sep2016rereco_ee
# skimbg data_2016C_23sep2016rereco_mm
# skimbg data_2016C_23sep2016rereco_em
# skimbg data_2016C_23sep2016rereco_ph
# skimbg data_2016C_23sep2016rereco_sm

# skimbg data_2016D_23sep2016rereco_ee
# skimbg data_2016D_23sep2016rereco_mm
# skimbg data_2016D_23sep2016rereco_em
# skimbg data_2016D_23sep2016rereco_ph
# skimbg data_2016D_23sep2016rereco_sm

# skimbg data_2016E_23sep2016rereco_ee
# skimbg data_2016E_23sep2016rereco_mm
# skimbg data_2016E_23sep2016rereco_em
# skimbg data_2016E_23sep2016rereco_ph
# skimbg data_2016E_23sep2016rereco_sm

# skimbg data_2016F_23sep2016rereco_ee
# skimbg data_2016F_23sep2016rereco_mm
# skimbg data_2016F_23sep2016rereco_em
# skimbg data_2016F_23sep2016rereco_ph
# skimbg data_2016F_23sep2016rereco_sm

# skimbg data_2016G_23sep2016rereco_ee
# skimbg data_2016G_23sep2016rereco_mm
# skimbg data_2016G_23sep2016rereco_em
# skimbg data_2016G_23sep2016rereco_ph
# skimbg data_2016G_23sep2016rereco_sm

# skimbg data_2016H_Prompt_ee
# skimbg data_2016H_Prompt_mm
# skimbg data_2016H_Prompt_em
# skimbg data_2016H_Prompt_ph
# skimbg data_2016H_Prompt_sm


# # 2016 MC

# # # DY
# skim dy_m1050_amcnlo
# skim dy_m50_amcnlo

# # # ttbar
# skim ttbar_dilep_mgmlm
# skim ttbar_dilep_powheg
# skim ttbar_1ltop_mgmlm
# skim ttbar_1ltbr_mgmlm
# skim ttbar_dilep_mgmlm_ext
# skim ttbar_dilep_powheg_alphas01273

# # # single top
# skim stt_top_lepdec_powheg
# skim stt_antitop_lepdec_powheg
# skim sttw_antitop_nofullhaddecay_powheg
# skim sttw_top_nofullhaddecay_powheg	  

# # # VV
# skim ww_2l2nu_powheg
# skim ww_lnuqq_powheg
# skim wz_lnqq_amcnlo
# skim wz_1l3n_amcnlo
# skim wz_2l2q_amcnlo
# skim wz_3lnu_powheg
# skim zz_2l2n_powheg
# skim zz_2l2q_amcnlo
# skim zz_2q2n_amcnlo
# skim zz_4l_powheg

# # # ttV
# skim ttw_incl_mgmlm
# skim ttz_incl_mgmlm
# skim ttbb_incl_amcnlo
# skim ttz_2l2n_amcnlo
# skim ttz_qq_amcnlo
# skim ttg_incl_amcnlo
# skim ttw_ln_amcnlo
# skim ttw_qq_amcnlo
# skim ttz_2l2n_amcnlo_ext

# # # VVV
# skim www_incl_amcnlo
# skim wwz_incl_amcnlo
# skim wzz_incl_amcnlo
# skim zzz_incl_amcnlo

# # # # WJets
# skim wjets_incl_amcnlo
# skim wgjets_incl_mgmlm
# skim wgjets_incl_amcnlo
# skim wjets_ht1200_mgmlm
# skim wjets_ht2500_mgmlm
# skim wjets_ht800_mgmlm
# skim wjets_ht600_mgmlm
# skim wjets_ht400_mgmlm
# skim wjets_ht200_mgmlm
# skim wjets_ht100_mgmlm
# skim wjets_incl_mgmlm

# # # other ewk contamination
# skim znunugamma_ptg130_mgmlm
# skim znunugamma_ptg40_mgmlm
# skim ttgamma_incl_amcnlo

# # # signal
# # ./writeConfig_80X.sh /${hadoopdirv2}_fastsim/SMS-T5ZZ_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-09/ ${TAG}_t5zz_80x_v2
# # ./writeConfig_80X.sh /${hadoopdirv2}_fastsim/SMS-TChiWZ_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/V08-00-09/ ${TAG}_tchiwz_80x_v2
# # ./writeConfig_80X.sh /${hadoopdirv2}_fastsim/SMS-TChiHZ_HToBB_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-09/ ${TAG}_tchihz_80x_v2

# # # samples for closure
skimbg dy_m1050_mgmlm
skimbg dy_m50_mgmlm_ext1
# skim dy_m50_mgmlm_ht100_ext1
# skim dy_m50_mgmlm_ht200_ext1
# skim dy_m50_mgmlm_ht400_ext1
# skim dy_m50_mgmlm_ht600_ext1

# skim gjetsht40_dr0p05_mgmlm 
# skim gjetsht100_dr0p05_mgmlm
# skim gjetsht200_dr0p05_mgmlm
# skim gjetsht400_dr0p05_mgmlm
# skim gjetsht600_dr0p05_mgmlm
