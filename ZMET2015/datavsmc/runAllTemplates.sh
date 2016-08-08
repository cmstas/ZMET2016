#! /bin/bash


source ../settings.sh

compile_looper
# create_analysis_output

if [ ! -d "../output/$analysis_version/" ]; then
	mkdir -p ../output/$analysis_version/
fi

# selection="_2jets_inclusive"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_SRA_bveto"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_SRA_withb"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_SRB_bveto"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_SRB_withb"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_SR_ATLAS"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_SR_EWK"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &


# 2016
selection="_inclusive"
# ./runTemplateLooper $selection $analysis_version data &
./runTemplateLooper $selection $analysis_version zjets &
./runTemplateLooper $selection $analysis_version ttbar &
./runTemplateLooper $selection $analysis_version st &
./runTemplateLooper $selection $analysis_version ww &
./runTemplateLooper $selection $analysis_version wz &
./runTemplateLooper $selection $analysis_version zz &
./runTemplateLooper $selection $analysis_version ttv &
./runTemplateLooper $selection $analysis_version vvv &
./runTemplateLooper $selection $analysis_version zjetsmlm &
./runTemplateLooper $selection $analysis_version wz_inc &
./runTemplateLooper $selection $analysis_version zz_inc &

# selection="_2jets_inclusive"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_2jets_inclusive_central"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_3jets_inclusive_central"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_SRA_bveto"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &
# # # # ./runTemplateLooper $selection $analysis_version fullscan &

# selection="_SRA_withb"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &
# # # # ./runTemplateLooper $selection $analysis_version fullscan &

# selection="_SRB_bveto"
# # ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &
# # ./runTemplateLooper $selection $analysis_version wz_inc &
# # ./runTemplateLooper $selection $analysis_version zz_inc &
# ./runTemplateLooper $selection $analysis_version fullscan 

# selection="_SRB_withb"
# # ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &
# # ./runTemplateLooper $selection $analysis_version wz_inc &
# # ./runTemplateLooper $selection $analysis_version zz_inc &
# ./runTemplateLooper $selection $analysis_version fullscan 

# selection="_SR_ATLAS"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version zjetsmlm &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz_inc &
# # ./runTemplateLooper $selection $analysis_version zz_inc &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &
# # ./runTemplateLooper $selection $analysis_version fullscan 

# selection="_SR_EWK"
# # ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &
# # ./runTemplateLooper $selection $analysis_version wz_inc &
# # ./runTemplateLooper $selection $analysis_version zz_inc &
# ./runTemplateLooper $selection $analysis_version fullscan_tchiwz

# selection="_SR_ZH"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_SR_EWK"
# # ./runTemplateLooper $selection $analysis_version data &
# ./runTemplateLooper $selection $analysis_version zjetsmlm

#################
## for studies ##
#################

# selection="_rawMET_SRA_tailstudy"
# # ./runTemplateLooper $selection $analysis_version zjets
# ./runTemplateLooper $selection $analysis_version zjetsmlm
# # ./runTemplateLooper $selection $analysis_version data

# selection="_rawMET_SRB_tailstudy"
# # ./runTemplateLooper $selection $analysis_version zjets
# ./runTemplateLooper $selection $analysis_version zjetsmlm
# # ./runTemplateLooper $selection $analysis_version data

# selection="_rawMET_2jets_inclusive_tailstudy"
# # ./runTemplateLooper $selection $analysis_version zjetsmlm
# ./runTemplateLooper $selection $analysis_version data

# selection="_rawMET_withb_SRA_tailstudy"
# ./runTemplateLooper $selection $analysis_version data
# selection="_rawMET_bveto_SRA_tailstudy"
# ./runTemplateLooper $selection $analysis_version data
# selection="_rawMET_bveto_SRB_tailstudy"
# ./runTemplateLooper $selection $analysis_version data
# selection="_rawMET_withb_SRB_tailstudy"
# ./runTemplateLooper $selection $analysis_version data

# # selection="_rawMET_SRA_withb_tailstudy"
# # ./runTemplateLooper $selection $analysis_version data &

# # selection="_rawMET_SRA_withtightb_tailstudy"
# # ./runTemplateLooper $selection $analysis_version data &

# selection="_rawMET_SRB_tailstudy"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &

# selection="_CR3lep"
# ./runTemplateLooper $selection $analysis_version data  &
# ./runTemplateLooper $selection $analysis_version zjets &
# ./runTemplateLooper $selection $analysis_version ttbar &
# ./runTemplateLooper $selection $analysis_version st &
# ./runTemplateLooper $selection $analysis_version ww &
# ./runTemplateLooper $selection $analysis_version wz &
# ./runTemplateLooper $selection $analysis_version zz &
# ./runTemplateLooper $selection $analysis_version ttv &
# ./runTemplateLooper $selection $analysis_version vvv &

# selection="_CR4lep"
# ./runTemplateLooper $selection $analysis_version data  &
# ./runTemplateLooper $selection $analysis_version zjets &
# ./runTemplateLooper $selection $analysis_version ttbar &
# ./runTemplateLooper $selection $analysis_version st &
# ./runTemplateLooper $selection $analysis_version ww &
# ./runTemplateLooper $selection $analysis_version wz &
# ./runTemplateLooper $selection $analysis_version zz &
# ./runTemplateLooper $selection $analysis_version ttv &
# ./runTemplateLooper $selection $analysis_version vvv &

# selection="_inclusive_withb"
# ./runTemplateLooper $selection $analysis_version data  &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &
# # ./runTemplateLooper $selection $analysis_version wz_inc &
# # ./runTemplateLooper $selection $analysis_version zz_inc &
# # ./runTemplateLooper $selection $analysis_version zjetsmlm &

# selection="_inclusive"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjetsmlm &
# ./runTemplateLooper $selection $analysis_version zjets &
# ./runTemplateLooper $selection $analysis_version ttbar &
# ./runTemplateLooper $selection $analysis_version st &
# ./runTemplateLooper $selection $analysis_version ww &
# ./runTemplateLooper $selection $analysis_version ttv &
# ./runTemplateLooper $selection $analysis_version vvv &
# ./runTemplateLooper $selection $analysis_version wz_inc &
# ./runTemplateLooper $selection $analysis_version zz_inc &

#################
## for closure ##
#################


# For Systematics
# selection="_rawMET_loosephoton_withb_SRB"
# ./runTemplateLooper $selection $analysis_version fullscan &
# selection="_rawMET_loosephoton_bveto_SRB"
# ./runTemplateLooper $selection $analysis_version fullscan &

# selection="_rawMET_loosephoton_withb_SRB_noisrboost"
# ./runTemplateLooper $selection $analysis_version fullscan &
# selection="_rawMET_loosephoton_bveto_SRB_noisrboost"
# ./runTemplateLooper $selection $analysis_version fullscan &

# selection="_rawMET_loosephoton_withb_SRB_nofastsim"
# ./runTemplateLooper $selection $analysis_version fullscan &
# selection="_rawMET_loosephoton_bveto_SRB_nofastsim"
# ./runTemplateLooper $selection $analysis_version fullscan &

# selection="_rawMET_loosephoton_withb_SRB_noleptonid_noleptoniso"
# ./runTemplateLooper $selection $analysis_version fullscan &
# selection="_rawMET_loosephoton_bveto_SRB_noleptonid_noleptoniso"
# ./runTemplateLooper $selection $analysis_version fullscan &

# selection="_rawMET_loosephoton_withb_SRB_heavy_UP"
# ./runTemplateLooper $selection $analysis_version fullscan &
# selection="_rawMET_loosephoton_bveto_SRB_heavy_UP"
# ./runTemplateLooper $selection $analysis_version fullscan &

# selection="_rawMET_loosephoton_withb_SRB_light_UP"
# ./runTemplateLooper $selection $analysis_version fullscan &
# selection="_rawMET_loosephoton_bveto_SRB_light_UP"
# ./runTemplateLooper $selection $analysis_version fullscan &

# selection="_rawMET_loosephoton_withb_SRB_jes_up"
# ./runTemplateLooper $selection $analysis_version fullscan &
# selection="_rawMET_loosephoton_bveto_SRB_jes_up"
# ./runTemplateLooper $selection $analysis_version fullscan &

# selection="_rawMET_loosephoton_withb_SRB_jes_dn"
# ./runTemplateLooper $selection $analysis_version fullscan &
# selection="_rawMET_loosephoton_bveto_SRB_jes_dn"
# ./runTemplateLooper $selection $analysis_version fullscan &


# selection="_SR_EWK"
# ./runTemplateLooper $selection $analysis_version fullscan_tchiwz &
# selection="_SR_EWK_fastsimMET"
# ./runTemplateLooper $selection $analysis_version fullscan_tchiwz &
# # selection="_SR_EWK_heavy_UP"
# # ./runTemplateLooper $selection $analysis_version fullscan_tchiwz &
# # selection="_SR_EWK_light_UP"
# # ./runTemplateLooper $selection $analysis_version fullscan_tchiwz &
# # selection="_SR_EWK_jes_up"
# # ./runTemplateLooper $selection $analysis_version fullscan_tchiwz &
# # selection="_SR_EWK_nofastsim"
# # ./runTemplateLooper $selection $analysis_version fullscan_tchiwz &
# # selection="_SR_EWK_noleptonid_noleptoniso"
# # ./runTemplateLooper $selection $analysis_version fullscan_tchiwz &

# selection="_SRB_bveto_fastsimMET"
# ./runTemplateLooper $selection $analysis_version fullscan &
# # selection="_SRB_bveto_heavy_UP"
# # ./runTemplateLooper $selection $analysis_version fullscan &
# # selection="_SRB_bveto_light_UP"
# # ./runTemplateLooper $selection $analysis_version fullscan &
# # selection="_SRB_bveto_jes_up"
# # ./runTemplateLooper $selection $analysis_version fullscan &
# # selection="_SRB_bveto_nofastsim"
# # ./runTemplateLooper $selection $analysis_version fullscan &
# # selection="_SRB_bveto_noleptonid_noleptoniso"
# # ./runTemplateLooper $selection $analysis_version fullscan &
# # selection="_SRB_bveto_noisr"
# # ./runTemplateLooper $selection $analysis_version fullscan &

# selection="_SRB_withb_fastsimMET"
# ./runTemplateLooper $selection $analysis_version fullscan &
# # selection="_SRB_withb_heavy_UP"
# # ./runTemplateLooper $selection $analysis_version fullscan &
# # selection="_SRB_withb_light_UP"
# # ./runTemplateLooper $selection $analysis_version fullscan &
# # selection="_SRB_withb_jes_up"
# # ./runTemplateLooper $selection $analysis_version fullscan &
# # selection="_SRB_withb_nofastsim"
# # ./runTemplateLooper $selection $analysis_version fullscan &
# # selection="_SRB_withb_noleptonid_noleptoniso"
# # ./runTemplateLooper $selection $analysis_version fullscan &
# # selection="_SRB_withb_noisr"
# # ./runTemplateLooper $selection $analysis_version fullscan &
