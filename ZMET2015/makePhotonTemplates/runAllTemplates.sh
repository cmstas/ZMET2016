#! /bin/bash


source ../settings.sh

compile_looper
# create_analysis_output

if [ ! -d "../output/$analysis_version/" ]; then
	mkdir -p ../output/$analysis_version/
fi

# selection="_rawMET_bveto_SRA"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
selection="_rawMET_SRA_tailstudy"
# ./makePhotonTemplates $selection ${analysis_version} data dohtreweighting 
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting 
# ./makePhotonTemplates $selection ${analysis_version} data dontdohtreweighting &

# selection="_rawMET_SRA_tailstudy"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting 
# selection="_rawMET_SRA_tailstudy"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting 
# selection="_rawMET_SRB_tailstudy"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting 
# selection="_rawMET_SRB_tailstudy"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting 

# selection="_rawMET_withb_SRA"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting 
# # ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting 


# selection="_rawMET_SRA"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting 

# selection="_rawMET_withb_SRA_tailstudy"
# # ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting 
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting 

# selection="_rawMET_bveto_SRA_tailstudy"
# # ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting 
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting 

# selection="_rawMET_withb_SRB_tailstudy"
# # ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting 
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting 

# selection="_rawMET_bveto_SRB_tailstudy"
# # ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting 
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting 


# selection="_rawMET_SRA_tailstudy"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting 
# selection="_rawMET_SRB_tailstudy"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting 
# selection="_rawMET_SRB_tailstudy"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting 

# selection="_rawMET_2jets_inclusive_tailstudy"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting 
# selection="_rawMET_2jets_inclusive_tailstudy"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting 

# selection="_rawMET_2jets_inclusive_tailstudy"
# # ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting 
# # selection="_rawMET_2jets_inclusive_tailstudy"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting 



# selection="_2jets_inclusive_tailstudy"
# ./makePhotonTemplates $selection ${analysis_version} data dontdohtreweighting

# selection="_3jets_inclusive_tailstudy"
# ./makePhotonTemplates $selection ${analysis_version} data dontdohtreweighting

# selection="_SRB_tailstudy"
# ./makePhotonTemplates $selection ${analysis_version} data dontdohtreweighting

# selection="_SRB_tailstudy"
# ./makePhotonTemplates $selection ${analysis_version} All_MC dontdohtreweighting


# selection="_2jets_inclusive_formarc"
# ./makePhotonTemplates $selection ${analysis_version} All_MC dontdohtreweighting
# # ./makePhotonTemplates $selection ${analysis_version} data dontdohtreweighting

# selection="_rawMET_SRA_withb_tailstudy"
# ./makePhotonTemplates $selection ${analysis_version} data dontdohtreweighting &
# selection="_rawMET_SRA_withtightb_tailstudy"
# ./makePhotonTemplates $selection ${analysis_version} data dontdohtreweighting &

# selection="_rawMET_SRA_withb_tailstudy"
# ./makePhotonTemplates $selection ${analysis_version} data dohtreweighting 
# selection="_rawMET_SRA_withtightb_tailstudy"
# ./makePhotonTemplates $selection ${analysis_version} data dohtreweighting 

# selection="_central_loosephoton_twojets"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_central_loosephoton_withb_twojets"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_central_loosephoton_with2_twojets"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_central_loosephoton_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_central_loosephoton_withb_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_central_loosephoton_with2_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &

# selection="_forward_loosephoton_twojets"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_forward_loosephoton_withb_twojets"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_forward_loosephoton_with2_twojets"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_forward_loosephoton_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_forward_loosephoton_withb_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_forward_loosephoton_with2_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &

# selection="_rawMET_bveto_SRB"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting 
# selection="_rawMET_withb_SRB"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting 
# selection="_rawMET_bveto_SRA"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting 
# selection="_rawMET_withb_SRA"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting 
# selection="_rawMET_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting 

# # selection="_rawMET_SRB"
# # ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_rawMET_SRA"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &

# selection="_central_loosephoton_twojets"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_central_loosephoton_withb_twojets"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_central_loosephoton_with2_twojets"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_central_loosephoton_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_central_loosephoton_withb_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_central_loosephoton_with2_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &

# selection="_forward_loosephoton_twojets"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_forward_loosephoton_withb_twojets"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_forward_loosephoton_with2_twojets"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_forward_loosephoton_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_forward_loosephoton_withb_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_forward_loosephoton_with2_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &


# selection="_rawMET_bveto_SRB"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_rawMET_withb_SRB"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_rawMET_bveto_SRA"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_rawMET_withb_SRA"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_rawMET_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &

# # selection="_rawMET_bveto_SRB"
# # ./makePhotonTemplates $selection $analysis_version data doptreweighting &
# # selection="_rawMET_withb_SRB"
# # ./makePhotonTemplates $selection $analysis_version data doptreweighting &
# selection="_rawMET_bveto_SRA"
# ./makePhotonTemplates $selection $analysis_version data doptreweighting &
# selection="_rawMET_withb_SRA"
# ./makePhotonTemplates $selection $analysis_version data doptreweighting &
# # selection="_rawMET_SR_ATLAS"
# # ./makePhotonTemplates $selection $analysis_version data doptreweighting &

# selection="_central_twojets"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_central_withb_twojets"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_central_with2_twojets"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_central_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_central_withb_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_central_with2_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &

# selection="_forward_twojets"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_forward_withb_twojets"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_forward_with2_twojets"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_forward_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_forward_withb_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_forward_with2_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &

# selection="_rawMET_bveto_SRB"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_rawMET_withb_SRB"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_rawMET_bveto_SRA"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_rawMET_withb_SRA"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_rawMET_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &

# selection="_central_twojets"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
# selection="_central_withb_twojets"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
# selection="_central_with2_twojets"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
# selection="_central_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
# selection="_central_withb_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
# selection="_central_with2_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &

# selection="_forward_twojets"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
# selection="_forward_withb_twojets"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
# selection="_forward_with2_twojets"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
# selection="_forward_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
# selection="_forward_withb_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
# selection="_forward_with2_3jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &

# selection="_rawMET_bveto_SRB"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting 
# selection="_rawMET_withb_SRB"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting 
# selection="_rawMET_bveto_SRA"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting 
# selection="_rawMET_withb_SRA"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting 
# # selection="_rawMET_SR_ATLAS"
# # ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &



# selection="_rawMET_tightphoton_bveto_SRB"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_rawMET_tightphoton_withb_SRB"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_rawMET_tightphoton_bveto_SRA"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_rawMET_tightphoton_withb_SRA"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_rawMET_tightphoton_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &

# selection="_rawMET_tightphoton_bveto_SRB"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_rawMET_tightphoton_withb_SRB"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_rawMET_tightphoton_bveto_SRA"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_rawMET_tightphoton_withb_SRA"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_rawMET_tightphoton_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &


# selection="_rawMET_loosephoton_bveto_SRB"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_rawMET_loosephoton_withb_SRB"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_rawMET_loosephoton_bveto_SRA"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_rawMET_loosephoton_withb_SRA"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_rawMET_loosephoton_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &

# selection="_rawMET_loosephoton_bveto_SRB"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_rawMET_loosephoton_withb_SRB"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_rawMET_loosephoton_bveto_SRA"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_rawMET_loosephoton_withb_SRA"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_rawMET_loosephoton_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &

# selection="_rawMET_loosephoton_withb_SRB"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_rawMET_loosephoton_withb_SRA"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &

# selection="_rawMET_loosephoton_withb_SRB"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_rawMET_loosephoton_withb_SRA"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &


# selection="_rawMET_loosephoton_SR_ATLAS_signalcontamination_hisplit"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_rawMET_loosephoton_SR_ATLAS_signalcontamination_losplit"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &

# selection="_rawMET_loosephoton_SR_ATLAS_signalcontamination_hisplit"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_rawMET_loosephoton_SR_ATLAS_signalcontamination_losplit"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &

# selection="_rawMET_loosephoton_withb_SRB_signalcontamination_hisplit"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_rawMET_loosephoton_withb_SRB_signalcontamination_losplit"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &

# selection="_rawMET_loosephoton_withb_SRB_signalcontamination_hisplit"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_rawMET_loosephoton_withb_SRB_signalcontamination_losplit"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &

# selection="_2jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_SRA_bveto"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_SRA_withb"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_SRB_bveto"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_SRB_withb"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_SR_EWK"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# # selection="_SR_ZH"
# # ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &

selection="_2jets_inclusive"
./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_SRA_bveto"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_SRA_withb"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_SRB_bveto"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_SRB_withb"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_SR_EWK"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# # selection="_SR_ZH"
# # ./makePhotonTemplates $selection $analysis_version data dohtreweighting &

# selection="_2jets_inclusive_central"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_3jets_inclusive_central"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &

# selection="_2jets_inclusive_central"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_3jets_inclusive_central"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
