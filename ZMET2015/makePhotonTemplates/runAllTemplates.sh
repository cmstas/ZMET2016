#! /bin/bash


source ../settings.sh

compile_looper
# create_analysis_output

if [ ! -d "../output/$analysis_version/" ]; then
	mkdir -p ../output/$analysis_version/
fi

# selection="_inclusive"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &

# # this is for closure
# selection="_2jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_SRA_bveto"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_SRA_withb"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_SRB_bveto"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_SRB_withb"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_SR_EWK"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &
# selection="_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version All_MC dontdohtreweighting &

# selection="_2jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
# selection="_SRA_bveto"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
# selection="_SRA_withb"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
# selection="_SRB_bveto"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
# selection="_SRB_withb"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
# selection="_SR_EWK"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &
# selection="_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version All_MC dohtreweighting &

# this is for data


# selection="_SRA_bveto"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_SRA_withb"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_SRB_bveto"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_SRB_withb"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_SRA_bveto"
# ./makePhotonTemplates $selection $analysis_version data_withMC dontdohtreweighting &
# selection="_SRA_withb"
# ./makePhotonTemplates $selection $analysis_version data_withMC dontdohtreweighting &
# selection="_SRB_bveto"
# ./makePhotonTemplates $selection $analysis_version data_withMC dontdohtreweighting &
# selection="_SRB_withb"
# ./makePhotonTemplates $selection $analysis_version data_withMC dontdohtreweighting &
# selection="_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version data_withMC dontdohtreweighting &

# selection="_SRA_bveto"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_SRA_withb"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_SRB_bveto"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_SRB_withb"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_SRA_bveto"
# ./makePhotonTemplates $selection $analysis_version data_withMC dohtreweighting &
# selection="_SRA_withb"
# ./makePhotonTemplates $selection $analysis_version data_withMC dohtreweighting &
# selection="_SRB_bveto"
# ./makePhotonTemplates $selection $analysis_version data_withMC dohtreweighting &
# selection="_SRB_withb"
# ./makePhotonTemplates $selection $analysis_version data_withMC dohtreweighting &
# selection="_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version data_withMC dohtreweighting &


# # edge and EKW regions
# selection="_2jets_inclusive_central"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_3jets_inclusive_central"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_2jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_SR_EWK"
# ./makePhotonTemplates $selection $analysis_version data dontdohtreweighting &
# selection="_2jets_inclusive_central"
# ./makePhotonTemplates $selection $analysis_version data_withMC dontdohtreweighting &
# selection="_3jets_inclusive_central"
# ./makePhotonTemplates $selection $analysis_version data_withMC dontdohtreweighting &
# selection="_2jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data_withMC dontdohtreweighting &
# selection="_SR_EWK"
# ./makePhotonTemplates $selection $analysis_version data_withMC dontdohtreweighting &

# selection="_2jets_inclusive_central"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_3jets_inclusive_central"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_2jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_SR_EWK"
# ./makePhotonTemplates $selection $analysis_version data dohtreweighting &
# selection="_2jets_inclusive_central"
# ./makePhotonTemplates $selection $analysis_version data_withMC dohtreweighting &
# selection="_3jets_inclusive_central"
# ./makePhotonTemplates $selection $analysis_version data_withMC dohtreweighting &
# selection="_2jets_inclusive"
# ./makePhotonTemplates $selection $analysis_version data_withMC dohtreweighting &
# selection="_SR_EWK"
# ./makePhotonTemplates $selection $analysis_version data_withMC dohtreweighting &

# selection="_SRB_withb"
# ./makePhotonTemplates $selection $analysis_version wgjets dohtreweighting &
# selection="_SRB_withb"
# ./makePhotonTemplates $selection $analysis_version wjets  dohtreweighting &
# selection="_SRB_withb"
# ./makePhotonTemplates $selection $analysis_version ttbar   dohtreweighting &
# selection="_SRB_withb"
# ./makePhotonTemplates $selection $analysis_version ttgamma dohtreweighting &
# selection="_SRB_bveto"
# ./makePhotonTemplates $selection $analysis_version wgjets dohtreweighting &
# selection="_SRB_bveto"
# ./makePhotonTemplates $selection $analysis_version wjets  dohtreweighting &
# selection="_SRB_bveto"
# ./makePhotonTemplates $selection $analysis_version ttbar   dohtreweighting &
# selection="_SRB_bveto"
# ./makePhotonTemplates $selection $analysis_version ttgamma dohtreweighting &
# selection="_SRA_withb"
# ./makePhotonTemplates $selection $analysis_version wgjets dohtreweighting &
# selection="_SRA_withb"
# ./makePhotonTemplates $selection $analysis_version wjets  dohtreweighting &
# selection="_SRA_withb"
# ./makePhotonTemplates $selection $analysis_version ttbar   dohtreweighting &
# selection="_SRA_withb"
# ./makePhotonTemplates $selection $analysis_version ttgamma dohtreweighting &
# selection="_SRA_bveto"
# ./makePhotonTemplates $selection $analysis_version wgjets dohtreweighting &
# selection="_SRA_bveto"
# ./makePhotonTemplates $selection $analysis_version wjets  dohtreweighting &
# selection="_SRA_bveto"
# ./makePhotonTemplates $selection $analysis_version ttbar   dohtreweighting &
# selection="_SRA_bveto"
# ./makePhotonTemplates $selection $analysis_version ttgamma dohtreweighting &
# selection="_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version wgjets dohtreweighting &
# selection="_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version wjets  dohtreweighting &
# selection="_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version ttbar   dohtreweighting &
# selection="_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version ttgamma dohtreweighting &

# selection="_SRB_withb"
# ./makePhotonTemplates $selection $analysis_version wgjets dontdohtreweighting &
# selection="_SRB_withb"
# ./makePhotonTemplates $selection $analysis_version wjets  dontdohtreweighting &
# selection="_SRB_withb"
# ./makePhotonTemplates $selection $analysis_version ttbar   dontdohtreweighting &
# selection="_SRB_withb"
# ./makePhotonTemplates $selection $analysis_version ttgamma dontdohtreweighting &
# selection="_SRB_bveto"
# ./makePhotonTemplates $selection $analysis_version wgjets dontdohtreweighting &
# selection="_SRB_bveto"
# ./makePhotonTemplates $selection $analysis_version wjets  dontdohtreweighting &
# selection="_SRB_bveto"
# ./makePhotonTemplates $selection $analysis_version ttbar   dontdohtreweighting &
# selection="_SRB_bveto"
# ./makePhotonTemplates $selection $analysis_version ttgamma dontdohtreweighting &
# selection="_SRA_withb"
# ./makePhotonTemplates $selection $analysis_version wgjets dontdohtreweighting &
# selection="_SRA_withb"
# ./makePhotonTemplates $selection $analysis_version wjets  dontdohtreweighting &
# selection="_SRA_withb"
# ./makePhotonTemplates $selection $analysis_version ttbar   dontdohtreweighting &
# selection="_SRA_withb"
# ./makePhotonTemplates $selection $analysis_version ttgamma dontdohtreweighting &
# selection="_SRA_bveto"
# ./makePhotonTemplates $selection $analysis_version wgjets dontdohtreweighting &
# selection="_SRA_bveto"
# ./makePhotonTemplates $selection $analysis_version wjets  dontdohtreweighting &
# selection="_SRA_bveto"
# ./makePhotonTemplates $selection $analysis_version ttbar   dontdohtreweighting &
# selection="_SRA_bveto"
# ./makePhotonTemplates $selection $analysis_version ttgamma dontdohtreweighting &
# selection="_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version wgjets dontdohtreweighting &
# selection="_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version wjets  dontdohtreweighting &
# selection="_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version ttbar   dontdohtreweighting &
# selection="_SR_ATLAS"
# ./makePhotonTemplates $selection $analysis_version ttgamma dontdohtreweighting &

selection="_SR_ATLAS"
./makePhotonTemplates $selection $analysis_version allewk dontdohtreweighting &
selection="_SRA_bveto"
./makePhotonTemplates $selection $analysis_version allewk dontdohtreweighting &
selection="_SRA_withb"
./makePhotonTemplates $selection $analysis_version allewk dontdohtreweighting &
selection="_SRB_bveto"
./makePhotonTemplates $selection $analysis_version allewk dontdohtreweighting &
selection="_SRB_withb"
./makePhotonTemplates $selection $analysis_version allewk dontdohtreweighting &

selection="_SR_ATLAS"
./makePhotonTemplates $selection $analysis_version allewk dohtreweighting &
selection="_SRA_bveto"
./makePhotonTemplates $selection $analysis_version allewk dohtreweighting &
selection="_SRA_withb"
./makePhotonTemplates $selection $analysis_version allewk dohtreweighting &
selection="_SRB_bveto"
./makePhotonTemplates $selection $analysis_version allewk dohtreweighting &
selection="_SRB_withb"
./makePhotonTemplates $selection $analysis_version allewk dohtreweighting &
