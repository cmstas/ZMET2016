#! /bin/bash


source ../settings.sh

compile_looper
# create_analysis_output

if [ ! -d "../output/$analysis_version/" ]; then
	mkdir -p ../output/$analysis_version/
fi

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

selection="_inclusive"
./runTemplateLooper $selection $analysis_version data &
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
./runTemplateLooper $selection $analysis_version zjets &
./runTemplateLooper $selection $analysis_version ttbar &
./runTemplateLooper $selection $analysis_version st &
./runTemplateLooper $selection $analysis_version ww &
./runTemplateLooper $selection $analysis_version ttv &
./runTemplateLooper $selection $analysis_version vvv &
./runTemplateLooper $selection $analysis_version wz_inc &
./runTemplateLooper $selection $analysis_version zz_inc &

#################
## for closure ##
#################

# selection="_central_twojets"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_central_withb_twojets"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_central_with2_twojets"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_central_3jets_inclusive"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_central_withb_3jets_inclusive"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_central_with2_3jets_inclusive"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &

# selection="_forward_twojets"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_forward_withb_twojets"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_forward_with2_twojets"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_forward_3jets_inclusive"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_forward_withb_3jets_inclusive"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_forward_with2_3jets_inclusive"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &

# selection="_rawMET_bveto_SRB"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_rawMET_withb_SRB"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_rawMET_bveto_SRA"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_rawMET_withb_SRA"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &
# selection="_rawMET_SR_ATLAS"
# ./runTemplateLooper $selection $analysis_version zjetsmlm &

##################
## for SR preds ##
##################

# selection="_central_loosephoton_twojets"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_central_loosephoton_withb_twojets"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_central_loosephoton_with2_twojets"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_central_loosephoton_3jets_inclusive"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_central_loosephoton_withb_3jets_inclusive"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_central_loosephoton_with2_3jets_inclusive"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &



# selection="_forward_loosephoton_twojets"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_forward_loosephoton_withb_twojets"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_forward_loosephoton_with2_twojets"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_forward_loosephoton_3jets_inclusive"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_forward_loosephoton_withb_3jets_inclusive"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_forward_loosephoton_with2_3jets_inclusive"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &





# # selection="_rawMET_SRB"
# # ./runTemplateLooper $selection $analysis_version data &

# # selection="_rawMET_SRA"
# # ./runTemplateLooper $selection $analysis_version data &

# selection="_rawMET_bveto_SRB"
# ./runTemplateLooper $selection $analysis_version data &
# # # ./runTemplateLooper $selection $analysis_version zjetsmlm &
# # # # ./runTemplateLooper $selection $analysis_version zjets &
# # # # # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &
# # # # # ./runTemplateLooper $selection $analysis_version wz_inc &
# # # # # ./runTemplateLooper $selection $analysis_version zz_inc &

# selection="_rawMET_withb_SRB"
# ./runTemplateLooper $selection $analysis_version data &
# # # # # ./runTemplateLooper $selection $analysis_version zjets &
# # # ./runTemplateLooper $selection $analysis_version zjetsmlm &
# # # # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &
# # # # ./runTemplateLooper $selection $analysis_version wz_inc &
# # # # ./runTemplateLooper $selection $analysis_version zz_inc &

# selection="_rawMET_bveto_SRA"
# ./runTemplateLooper $selection $analysis_version data &
# # # # ./runTemplateLooper $selection $analysis_version zjets &
# # # ./runTemplateLooper $selection $analysis_version zjetsmlm & 
# # # # # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &
# # # # # ./runTemplateLooper $selection $analysis_version wz_inc &
# # # # # ./runTemplateLooper $selection $analysis_version zz_inc &

# selection="_rawMET_withb_SRA"
# ./runTemplateLooper $selection $analysis_version data &
# # # ./runTemplateLooper $selection $analysis_version zjetsmlm &
# # # # # ./runTemplateLooper $selection $analysis_version zjets &
# # # # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &
# # # # ./runTemplateLooper $selection $analysis_version wz_inc &
# # # # ./runTemplateLooper $selection $analysis_version zz_inc &

# selection="_rawMET_SR_ATLAS"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version zjets &
# # ./runTemplateLooper $selection $analysis_version zjetsmlm &
# # # ./runTemplateLooper $selection $analysis_version ttbar &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &
# # # ./runTemplateLooper $selection $analysis_version wz_inc &
# # # ./runTemplateLooper $selection $analysis_version zz_inc &


# selection="_rawMET_2jets_inclusive"
# ./runTemplateLooper $selection $analysis_version data &
# ./runTemplateLooper $selection $analysis_version zjets &
# ./runTemplateLooper $selection $analysis_version ttbar &
# ./runTemplateLooper $selection $analysis_version st &
# ./runTemplateLooper $selection $analysis_version ww &
# ./runTemplateLooper $selection $analysis_version wz &
# ./runTemplateLooper $selection $analysis_version zz &
# ./runTemplateLooper $selection $analysis_version ttv &
# ./runTemplateLooper $selection $analysis_version vvv &


# selection="_rawMET_tightphoton_bveto_SRB"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_rawMET_tightphoton_withb_SRB"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_rawMET_tightphoton_bveto_SRA"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_rawMET_tightphoton_withb_SRA"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_rawMET_tightphoton_SR_ATLAS"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &


# selection="_rawMET_loosephoton_bveto_SRB"
# # ./runTemplateLooper $selection $analysis_version data &
# # # ./runTemplateLooper $selection $analysis_version st &
# # # ./runTemplateLooper $selection $analysis_version ww &
# # # ./runTemplateLooper $selection $analysis_version wz &
# # # ./runTemplateLooper $selection $analysis_version zz &
# # # ./runTemplateLooper $selection $analysis_version ttv &
# # # ./runTemplateLooper $selection $analysis_version vvv &
# # ./runTemplateLooper $selection $analysis_version signal1100200 &
# ./runTemplateLooper $selection $analysis_version fullscan &

# selection="_rawMET_loosephoton_withb_SRB"
# # ./runTemplateLooper $selection $analysis_version data &
# # # ./runTemplateLooper $selection $analysis_version st &
# # # ./runTemplateLooper $selection $analysis_version ww &
# # # ./runTemplateLooper $selection $analysis_version wz &
# # # ./runTemplateLooper $selection $analysis_version zz &
# # # ./runTemplateLooper $selection $analysis_version ttv &
# # # ./runTemplateLooper $selection $analysis_version vvv &
# # ./runTemplateLooper $selection $analysis_version signal1100200 &
# ./runTemplateLooper $selection $analysis_version fullscan &

# selection="_rawMET_loosephoton_bveto_SRA"
# # ./runTemplateLooper $selection $analysis_version data &
# # # ./runTemplateLooper $selection $analysis_version st &
# # # ./runTemplateLooper $selection $analysis_version ww &
# # # ./runTemplateLooper $selection $analysis_version wz &
# # # ./runTemplateLooper $selection $analysis_version zz &
# # # ./runTemplateLooper $selection $analysis_version ttv &
# # # ./runTemplateLooper $selection $analysis_version vvv &
# # ./runTemplateLooper $selection $analysis_version signal1100200 &
# ./runTemplateLooper $selection $analysis_version fullscan &

# selection="_rawMET_loosephoton_withb_SRA"
# # ./runTemplateLooper $selection $analysis_version data &
# # # ./runTemplateLooper $selection $analysis_version st &
# # # ./runTemplateLooper $selection $analysis_version ww &
# # # ./runTemplateLooper $selection $analysis_version wz &
# # # ./runTemplateLooper $selection $analysis_version zz &
# # # ./runTemplateLooper $selection $analysis_version ttv &
# # # ./runTemplateLooper $selection $analysis_version vvv &
# # ./runTemplateLooper $selection $analysis_version signal1100200 &
# ./runTemplateLooper $selection $analysis_version fullscan &

# selection="_rawMET_loosephoton_SR_ATLAS"
# # ./runTemplateLooper $selection $analysis_version data &
# # # ./runTemplateLooper $selection $analysis_version st &
# # # ./runTemplateLooper $selection $analysis_version ww &
# # # ./runTemplateLooper $selection $analysis_version wz &
# # # ./runTemplateLooper $selection $analysis_version zz &
# # # ./runTemplateLooper $selection $analysis_version ttv &
# # # ./runTemplateLooper $selection $analysis_version vvv &
# # ./runTemplateLooper $selection $analysis_version signal1100200 &
# ./runTemplateLooper $selection $analysis_version fullscan &



# selection="_rawMET_loosephoton_SR_ATLAS_signalcontamination_hisplit"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &

# selection="_rawMET_loosephoton_SR_ATLAS_signalcontamination_losplit"
# ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &


# selection="_rawMET_loosephoton_withb_SRB_signalcontamination_losplit"
# # ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &
# # # ./runTemplateLooper $selection $analysis_version signal1100200 &

# selection="_rawMET_loosephoton_withb_SRB_signalcontamination_hisplit"
# # ./runTemplateLooper $selection $analysis_version data &
# # ./runTemplateLooper $selection $analysis_version st &
# # ./runTemplateLooper $selection $analysis_version ww &
# # ./runTemplateLooper $selection $analysis_version wz &
# # ./runTemplateLooper $selection $analysis_version zz &
# # ./runTemplateLooper $selection $analysis_version ttv &
# # ./runTemplateLooper $selection $analysis_version vvv &
# # # ./runTemplateLooper $selection $analysis_version signal1100200 &


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
