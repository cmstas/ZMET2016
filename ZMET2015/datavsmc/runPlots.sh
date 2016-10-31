#! /bin/bash

source ../settings.sh

# analysis_version=V07-04-03_goodtrigs

if [ ! -d "../output/ZMET2015/$analysis_version/plots/Closure/" ]; then
	mkdir -p ../output/ZMET2015/$analysis_version/plots/Closure/
	cp ../index.php ../output/ZMET2015/$analysis_version/plots/Closure/
fi

# root -b -q "compareMET.cc+( \"$analysis_version\", \"_2jets_inclusive\" , 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_SR_EWK\" , 1.0 )"

# root -b -q "compareMET.cc+( \"$analysis_version\", \"_central_twojets_novtxweight\"              , 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_central_withb_twojets_novtxweight\"        , 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_central_with2_twojets_novtxweight\"        , 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_central_3jets_inclusive_novtxweight\"      , 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_central_withb_3jets_inclusive_novtxweight\", 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_central_with2_3jets_inclusive_novtxweight\", 1.0 )"

# root -b -q "compareMET.cc+( \"$analysis_version\", \"_forward_twojets_novtxweight\"              , 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_forward_withb_twojets_novtxweight\"        , 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_forward_with2_twojets_novtxweight\"        , 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_forward_3jets_inclusive_novtxweight\"      , 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_forward_withb_3jets_inclusive_novtxweight\", 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_forward_with2_3jets_inclusive_novtxweight\", 1.0 )"

# root -b -q "compareMET.cc+( \"$analysis_version\", \"_2jets_inclusive\", 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_SRB_bveto\", 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_SRB_withb\", 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_SRA_bveto\", 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_SRA_withb\", 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_SR_ATLAS\" , 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_SR_EWK\" , 1.0 )"

lumi=26.4
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_central\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_3jets_inclusive_central\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"         , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_EWK\"                  , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SRA_bveto\"               , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SRA_withb\"               , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SRB_bveto\"               , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SRB_withb\"               , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_ATLAS\"                , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_ZH\"                 , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  

# lumi=10.5083658
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_ATLAS\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_ATLAS\"             , \"ee\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_ATLAS\"             , \"mm\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_ATLAS\"             , \"em\", \"mll_fkw\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"ee\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"mm\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"em\", \"mll\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"ee\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"mm\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"em\", \"mll\",       \"passtrig\" )"  

lumi=40.0
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_A_bveto_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_A_withb_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_B_bveto_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_B_withb_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_C_bveto_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_C_withb_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"mll\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_A_bveto_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"mt2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_A_withb_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"mt2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_B_bveto_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"mt2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_B_withb_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"mt2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_C_bveto_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"mt2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_C_withb_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"mt2\",       \"passtrig\" )"  

root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_A_bveto_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"met\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_A_withb_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"met\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_B_bveto_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"met\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_B_withb_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"met\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_C_bveto_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"met\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"newSR_C_withb_dphicut0p4_dphi2cut0p4_3lvetotight_mdzwindow_mt2cut\"             , \"ll\", \"met\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"ll\", \"met_T1CHS_miniAOD_CORE_pt\", \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"ll\", \"ptdil\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"ll\", \"nVert\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"ll\", \"mll\",       \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"ll\", \"njets\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"ll\", \"nbjets\",    \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"ll\", \"met_raw\",   \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"ll\", \"ht\",        \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"ll\", \"mt2\",       \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"ll\", \"ptj1\",      \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"ll\", \"ptj2\",      \"passtrig\" )"  &

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"ll\", \"met_T1CHS_miniAOD_CORE_pt\", \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"ll\", \"ptdil\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"ll\", \"nVert\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"ll\", \"mll\",       \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"ll\", \"njets\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"ll\", \"nbjets\",    \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"ll\", \"met_raw\",   \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"ll\", \"ht\",        \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"ll\", \"mt2\",       \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"ll\", \"ptj1\",      \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"ll\", \"ptj2\",      \"passtrig\" )"  &

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"em\", \"met_T1CHS_miniAOD_CORE_pt\", \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"em\", \"ptdil\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"em\", \"nVert\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"em\", \"mll\",       \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"em\", \"njets\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"em\", \"nbjets\",    \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"em\", \"met_raw\",   \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"em\", \"ht\",        \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"em\", \"mt2\",       \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"em\", \"ptj1\",      \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive_novtxweight\"             , \"em\", \"ptj2\",      \"passtrig\" )"  &

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"em\", \"met_T1CHS_miniAOD_CORE_pt\", \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"em\", \"ptdil\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"em\", \"nVert\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"em\", \"mll\",       \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"em\", \"njets\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"em\", \"nbjets\",    \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"em\", \"met_raw\",   \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"em\", \"ht\",        \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"em\", \"mt2\",       \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"em\", \"ptj1\",      \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_2jets_inclusive\"             , \"em\", \"ptj2\",      \"passtrig\" )"  &

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"met_T1CHS_miniAOD_CORE_pt\", \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ptdil\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"nVert\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"mll\",       \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"njets\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"nbjets\",    \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"met_raw\",   \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ht\",        \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"mt2\",       \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ptj1\",      \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ptj2\",      \"passtrig\" )"  &

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"met_T1CHS_miniAOD_CORE_pt\", \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ptdil\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"nVert\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"mll\",       \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"njets\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"nbjets\",    \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"met_raw\",   \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ht\",        \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"mt2\",       \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ptj1\",      \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ptj2\",      \"passtrig\" )"  &

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"met_T1CHS_miniAOD_CORE_pt\", \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"ptdil\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"nVert\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"mll\",       \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"njets\",     \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"nbjets\",    \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"met_raw\",   \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"ht\",        \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"mt2\",       \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"ptj1\",      \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"ptj2\",      \"passtrig\" )"  &

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_EWK\"             , \"em\", \"met_T1CHS_miniAOD_CORE_pt\", \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_EWK\"             , \"em\", \"ptdil\",     \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_EWK\"             , \"em\", \"nVert\",     \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_EWK\"             , \"em\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_EWK\"             , \"em\", \"njets\",     \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_EWK\"             , \"em\", \"nbjets\",    \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_EWK\"             , \"em\", \"met_raw\",   \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_EWK\"             , \"em\", \"ht\",        \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_EWK\"             , \"em\", \"mt2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_EWK\"             , \"em\", \"ptj1\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_SR_EWK\"             , \"em\", \"ptj2\",      \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\" , \"ll\", \"nVert\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"met\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"ptdil\",     \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"nVert\",     \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"njets\",     \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"nbjets\",    \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"met_raw\",   \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"ht\",        \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"ptj1\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"ptj2\",      \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"met_T1CHS_miniAOD_CORE_pt\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"met\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nVert\",     \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"met_T1CHS_miniAOD_CORE_pt\",       \"passtrig\" )"  

# lumi=.0136
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"nVert\",     \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"ptdil\",     \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"njets\",     \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"met_raw\",   \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"met_T1CHS_miniAOD_CORE_pt\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"metphi\",        \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"metphir\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"ht\",        \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"ptl1\",      \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"ptl2\",      \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"l1eta\",      \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"l2eta\",      \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"l1phi\",      \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"l2phi\",      \"passtrig\" )"  

# lumi=.024
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"nVert\",     \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"mll\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"ptdil\",     \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"njets\",     \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"met_raw\",   \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"met_T1CHS_miniAOD_CORE_pt\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"metphi\",        \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"metphir\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"ht\",        \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"ptl1\",      \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"ptl2\",      \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"l1eta\",      \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"l2eta\",      \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"l1phi\",      \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"l2phi\",      \"passtrig\" )"  

# lumi=.0065
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"nVert\",     \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"mll\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"ptdil\",     \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"njets\",     \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"met_raw\",   \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"met_T1CHS_miniAOD_CORE_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"metphi\",        \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"metphir\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"ht\",        \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"ptl1\",      \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"ptl2\",      \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"l1eta\",      \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"l2eta\",      \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"l1phi\",      \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"l2phi\",      \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"ptl1\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"ptl2\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"l1eta\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"l2eta\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"l1phi\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"l2phi\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ptl1\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ptl2\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"l1eta\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"l2eta\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"l1phi\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"l2phi\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ptl1\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ptl2\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"l1eta\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"l2eta\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"l1phi\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"l2phi\",      \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"mbb_csv\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"mbb_csv\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"mbb_csv\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"mbb_bpt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"mbb_bpt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"mbb_bpt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"mjj\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"mjj\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"mjj\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"mt2j\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"mt2j\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"mt2j\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"mt2b\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"mt2b\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"mt2b\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ll\", \"mt2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"ee\", \"mt2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\"             , \"mm\", \"mt2\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"met_T1CHS_miniAOD_CORE_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"met_T1CHS_miniAOD_CORE_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"met_T1CHS_miniAOD_CORE_pt\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"njets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"njets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"njets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nbjets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"nbjets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"nbjets\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_0013_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_1316_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_1624_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_2430_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_30in_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_0013_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_1316_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_1624_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_2430_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_30in_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_0013_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_1316_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_1624_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_2430_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_30in_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_0013_sumet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_1316_sumet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_1624_sumet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_2430_sumet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_30in_sumet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_0013_sumet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_1316_sumet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_1624_sumet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_2430_sumet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_30in_sumet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_0013_sumet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_1316_sumet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_1624_sumet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_2430_sumet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_30in_sumet\",       \"passtrig\" )"  

# # # SR plots
# lumi=1.280 # golden json
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  

# lumi=1.2544
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"mll_fkw\",       \"passtrig\" )"  

# lumi=1.0496
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"em\", \"mll_fkw\",       \"passtrig\" )"  
