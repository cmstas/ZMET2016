#! /bin/bash

source ../settings.sh

# analysis_version=V07-04-03_goodtrigs

if [ ! -d "../output/ZMET2015/$analysis_version/plots/Closure/" ]; then
	mkdir -p ../output/ZMET2015/$analysis_version/plots/Closure/
	cp ../index.php ../output/ZMET2015/$analysis_version/plots/Closure/
fi

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

# root -b -q "compareMET.cc+( \"$analysis_version\", \"_rawMET_bveto_SRB_novtxweight\", 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_rawMET_withb_SRB_novtxweight\", 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_rawMET_bveto_SRA_novtxweight\", 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_rawMET_withb_SRA_novtxweight\", 1.0 )"
# root -b -q "compareMET.cc+( \"$analysis_version\", \"_rawMET_SR_ATLAS_novtxweight\" , 1.0 )"

lumi=2.26
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"mll\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"mbb_csv\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"mbb_csv\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"mbb_csv\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"mbb_bpt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"mbb_bpt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"mbb_bpt\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"mjj\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"mjj\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"mjj\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"mt2j\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"mt2j\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"mt2j\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"mt2b\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"mt2b\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"mt2b\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"mt2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"mt2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"mt2\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"met_T1CHS_miniAOD_CORE_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"met_T1CHS_miniAOD_CORE_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"met_T1CHS_miniAOD_CORE_pt\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"njets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"njets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"njets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nbjets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"nbjets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"nbjets\",       \"passtrig\" )"  

root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_0013_pt\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_1316_pt\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_1624_pt\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_2430_pt\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_30in_pt\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_0013_pt\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_1316_pt\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_1624_pt\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_2430_pt\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_30in_pt\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_0013_pt\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_1316_pt\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_1624_pt\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_2430_pt\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_30in_pt\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_0013_sumet\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_1316_sumet\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_1624_sumet\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_2430_sumet\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"chpfcands_30in_sumet\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_0013_sumet\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_1316_sumet\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_1624_sumet\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_2430_sumet\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"phpfcands_30in_sumet\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_0013_sumet\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_1316_sumet\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_1624_sumet\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_2430_sumet\",       \"passtrig\" )"  
root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nupfcands_30in_sumet\",       \"passtrig\" )"  

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

lumi=2.11
# lumi=1.28
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\", \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\", \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\", \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\", \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_SR_ATLAS\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\", \"ll\", \"mll_fkw\",       \"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\", \"ll\", \"mll_fkw\",       \"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\", \"ll\", \"mll_fkw\",       \"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\", \"ll\", \"mll_fkw\",       \"passtrig\" )"

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\", \"em\", \"mll_fkw\",       \"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\", \"em\", \"mll_fkw\",       \"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\", \"em\", \"mll_fkw\",       \"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\", \"em\", \"mll_fkw\",       \"passtrig\" )"

# lumi=1.8319653
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\", \"em\", \"mll_fkw\",       \"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\", \"ll\", \"mll_fkw\",       \"passtrig\" )"

# lumi=1.9453203
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\", \"em\", \"mll_fkw\",       \"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\", \"ll\", \"mll_fkw\",       \"passtrig\" )"

# lumi=1.59
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\", \"em\", \"mll_fkw\",       \"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\", \"ll\", \"mll_fkw\",       \"passtrig\" )"


# lumi=1.9827
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\", \"em\", \"mll_fkw\",       \"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\", \"ll\", \"mll_fkw\",       \"passtrig\" )"

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  

lumi=2.11
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_central_loosephoton_twojets\"              , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_central_loosephoton_withb_twojets\"        , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_central_loosephoton_with2_twojets\"        , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_central_loosephoton_3jets_inclusive\"      , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_central_loosephoton_withb_3jets_inclusive\", \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_central_loosephoton_with2_3jets_inclusive\", \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_forward_loosephoton_twojets\"              , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_forward_loosephoton_withb_twojets\"        , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_forward_loosephoton_with2_twojets\"        , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_forward_loosephoton_3jets_inclusive\"      , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_forward_loosephoton_withb_3jets_inclusive\", \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_forward_loosephoton_with2_3jets_inclusive\", \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_withb_SRA\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_bveto_SRA\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_withb_SRB\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_bveto_SRB\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_SR_ATLAS\"              , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"mll\",       \"passtrig\" )"  

# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"njets\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"njets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"nbjets\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"nbjets\",      \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ht_highbin\",  \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ht_highbin\",  \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ptdil\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ptdil\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"met_T1CHS_miniAOD_CORE_pt\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"met_T1CHS_miniAOD_CORE_pt\",       \"passtrig\" )"  



# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_tightphoton_withb_SRA\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_withb_SRA\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_tightphoton_bveto_SRA\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_bveto_SRA\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_tightphoton_withb_SRB\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_withb_SRB\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_tightphoton_bveto_SRB\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_bveto_SRB\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_tightphoton_SR_ATLAS\"  , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_SR_ATLAS\"  , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_withb_SRA\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_bveto_SRA\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_withb_SRB\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_bveto_SRB\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_SR_ATLAS\"  , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  

# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_SR_ATLAS\"  , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_SR_ATLAS_signalcontamination_hisplit\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_SR_ATLAS_signalcontamination_losplit\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_withb_SRB\"  , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_withb_SRB_signalcontamination_hisplit\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_loosephoton_withb_SRB_signalcontamination_losplit\" , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"ht_highbin\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"ptj1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"ptj1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"ptj1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"ptj1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"ptj2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"ptj2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"ptj2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"ptj2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"ptj3\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"ptj3\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"ptj3\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"ptj3\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"ptj4\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"ptj4\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"ptj4\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"ptj4\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"ptb1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ptb1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ptb1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"ptb1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"ptb2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ptb2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ptb2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"ptb2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"ptb3\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ptb3\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ptb3\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"ptb3\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"ptb4\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ptb4\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ptb4\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"ptb4\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"pt_matchedbjet1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"pt_matchedbjet1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"pt_matchedbjet1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"pt_matchedbjet1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"pt_matchedbjet2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"pt_matchedbjet2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"pt_matchedbjet2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"pt_matchedbjet2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"pt_matchedbjet3\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"pt_matchedbjet3\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"pt_matchedbjet3\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"pt_matchedbjet3\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"ht_highbin\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"ptj1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ptj1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ptj1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"ptj1\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"ptj2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ptj2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ptj2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"ptj2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"ptj3\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ptj3\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ptj3\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"ptj3\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"ptj4\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ee\", \"ptj4\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"mm\", \"ptj4\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"em\", \"ptj4\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"ht_highbin\", \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"ht_highbin\", \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"ht_highbin\", \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"ht_highbin\", \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"met\",        \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"met\",        \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"met\",        \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"met\",        \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"mll\",        \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"mll\",        \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"mll\",        \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"mll\",        \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"ptl1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"ptl1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"ptl1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"ptl1\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"ptl2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"ptl2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"ptl2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"ptl2\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"metphi\",     \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"metphi\",     \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"metphi\",     \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"metphi\",     \"passtrig\" )"  

# lumi=2.11
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"met\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"ptdil\",    \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nVert\",    \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"mll\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"njets\",    \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"             , \"ll\", \"nbjets\",   \"passtrig\" )"  


# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met_T1CHS_miniAOD_CORE_pt\",    \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met_T1CHS_miniAOD_CORE_up_pt\", \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met_T1CHS_miniAOD_CORE_dn_pt\", \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"met_T1CHS_miniAOD_CORE_pt\",    \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"met_T1CHS_miniAOD_CORE_up_pt\", \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"met_T1CHS_miniAOD_CORE_dn_pt\", \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"met_T1CHS_miniAOD_CORE_pt\",    \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"met_T1CHS_miniAOD_CORE_up_pt\", \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"met_T1CHS_miniAOD_CORE_dn_pt\", \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"em\", \"met_T1CHS_miniAOD_CORE_pt\",    \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"em\", \"met_T1CHS_miniAOD_CORE_up_pt\", \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"em\", \"met_T1CHS_miniAOD_CORE_dn_pt\", \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"ht\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"met\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"ptdil\",    \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"nVert\",    \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"mll\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"njets\",      \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"nbjets\",      \"passtrig\" )"  


# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_SR_ATLAS\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ll\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ee\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"mm\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"em\", \"ht_highbin\",       \"passtrig\" )"  

# lumi=1.0496
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"ht_highbin\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_SR_ATLAS\"              , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"em\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"em\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"em\", \"ht_highbin\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"em\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"em\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"em\", \"mll_fkw\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ll\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ll\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"ll\", \"ht_highbin\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ee\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ee\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"ee\", \"ht_highbin\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"mm\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"mm\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"mm\", \"ht_highbin\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"ht_highbin_2jets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ll\", \"ht_highbin_2jets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ll\", \"ht_highbin_2jets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"ll\", \"ht_highbin_2jets\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"ht_highbin_3jets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ll\", \"ht_highbin_3jets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ll\", \"ht_highbin_3jets\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"ll\", \"ht_highbin_3jets\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"mm\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ee\", \"met_rawgt1jet\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"mm\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ee\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"mm\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"ee\", \"met_rawgt1jet\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_SR_ATLAS\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_SR_ATLAS\"             , \"mm\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_SR_ATLAS\"             , \"ee\", \"met_rawgt1jet\",       \"passtrig\" )"  

# # lumi=1.088
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ll\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"mm\", \"ht_highbin\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ee\", \"ht_highbin\",       \"passtrig\" )"  

# lumi=1.0496
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"ptdil\",       \"passtrig\" )"  
# lumi=1.088
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ll\", \"ptdil\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_SR_ATLAS\"              , \"ll\", \"met_rawgt1jet\",       \"passtrig\" )"

# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ee\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"met_rawgt1jet\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"ee\", \"met_rawgt1jet\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ee\", \"met_rawgt1jet\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_SR_ATLAS\"              , \"ee\", \"met_rawgt1jet\",       \"passtrig\" )"

# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"mm\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"met_rawgt1jet\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"mm\", \"met_rawgt1jet\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"mm\", \"met_rawgt1jet\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_SR_ATLAS\"              , \"mm\", \"met_rawgt1jet\",       \"passtrig\" )"

# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"em\", \"met_rawgt1jet\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"met_rawgt1jet\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"em\", \"met_rawgt1jet\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"em\", \"met_rawgt1jet\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_SR_ATLAS\"              , \"em\", \"met_rawgt1jet\",       \"passtrig\" )"

# cr plots
lumi=1.264 # golden json
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_CR4lep\", \"ll\", \"njtall\",\"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_CR4lep\", \"ll\", \"metall\",\"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_CR3lep\", \"ll\", \"njtall\",\"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_CR3lep\", \"ll\", \"njtm50\",\"passtrig\" )"
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_CR3lep\", \"ll\", \"metall\",\"passtrig\" )"


lumi=1.280 # golden json
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met\"        , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"met\"        , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"met\"        , \"passtrig\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"ht_highbin\" , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"ht_highbin\" , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"ht_highbin\" , \"passtrig\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"mll\"        , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"mll\"        , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"mll\"        , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"em\", \"mll\"        , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"njets\"      , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"nbjets\"     , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"ptdil\"      , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"njets\"      , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"nbjets\"     , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"ptdil\"      , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"njets\"      , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"nbjets\"     , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"ptdil\"      , \"passtrig\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_withb\", \"ll\", \"met\"     , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_withb\", \"ll\", \"ht\"      , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_withb\", \"ll\", \"njets\"   , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_withb\", \"ll\", \"nbjets\"  , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_withb\", \"ll\", \"ptdil\"   , \"passtrig\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_withb\", \"ee\", \"met\"     , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_withb\", \"ee\", \"ht\"      , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_withb\", \"ee\", \"njets\"   , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_withb\", \"ee\", \"nbjets\"  , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_withb\", \"ee\", \"ptdil\"   , \"passtrig\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_withb\", \"mm\", \"met\"     , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_withb\", \"mm\", \"ht\"      , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_withb\", \"mm\", \"njets\"   , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_withb\", \"mm\", \"nbjets\"  , \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_withb\", \"mm\", \"ptdil\"   , \"passtrig\" )"     


# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"em\", \"mll_fkw\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  

# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"mll_fkw\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  

# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"mm\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"em\", \"mll_fkw\",       \"passtrig\" )"  
# # root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ee\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"mm\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"em\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ee\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"mm\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"em\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"ee\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_2jets_inclusive\"             , \"mm\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_2jets_inclusive\"             , \"em\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_2jets_inclusive\"             , \"ee\", \"mll_fkw\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_2jets_inclusive\"             , \"ll\", \"mll_fkw\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_2jets_inclusive\"             , \"mm\", \"met\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_2jets_inclusive\"             , \"em\", \"met\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_2jets_inclusive\"             , \"ee\", \"met\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_2jets_inclusive\"             , \"ll\", \"met\",       \"passtrig\" )"  

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"mm\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"mm\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"mm\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"mm\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_SR_ATLAS\"              , \"mm\", \"mll\",       \"passtrig\" )"

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ll\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_SR_ATLAS\"              , \"ll\", \"mll\",       \"passtrig\" )"

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"ee\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"ee\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"ee\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"ee\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_SR_ATLAS\"              , \"ee\", \"mll\",       \"passtrig\" )"

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRA\"             , \"em\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRA\"             , \"em\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_bveto_SRB\"             , \"em\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_withb_SRB\"             , \"em\", \"mll\",       \"passtrig\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_rawMET_SR_ATLAS\"              , \"em\", \"mll\",       \"passtrig\" )"


lumi=1.264 # golden json
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\", \"ll\", \"mll\",    \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\", \"ee\", \"mll\",    \"passtrig\" )" 
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\", \"mm\", \"mll\",    \"passtrig\" )" 
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\", \"em\", \"mll\",    \"passtrig\" )" 

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\", \"ll\", \"nVert\",    \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"nVert\",    \"passtrig\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\", \"ll\", \"met_raw\",    \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\", \"ll\", \"met_CORE\",    \"passtrig\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met_raw\",  \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met_CORE\", \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"mll\",      \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\", \"ll\", \"ht\",       \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"njets\",    \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"nbjets\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"ptdil\",    \"passtrig\" )"     

## PLOTS START HERE
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"ptdil\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"mll\",     \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"njets\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"nbjets\",  \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"ht\",      \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"mt3\",     \"passtrig\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"ptdil\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"mll\",     \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"njets\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"nbjets\",  \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"ht\",      \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"mt3\",     \"passtrig\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"ptdil\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"mll\",     \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"njets\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"nbjets\",  \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"ht\",      \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"mt3\",     \"passtrig\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"met\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\", \"mm\", \"met\",   \"passtrig\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"            , \"mm\", \"met_CORE\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\", \"mm\", \"met_CORE\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\"            , \"mm\", \"met3p0_CORE\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive_novtxweight\", \"mm\", \"met3p0_CORE\",   \"passtrig\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"em\", \"ptl1\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"em\", \"ptl2\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"ptl1\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"ptl2\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"ptl1\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"ptl2\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"ptl1\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"ptl2\",   \"passtrig\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"em\", \"ptdil\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"em\", \"mll\",     \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"em\", \"njets\",   \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"em\", \"nbjets\",  \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"em\", \"ht\",      \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"em\", \"mt3\",     \"passtrig\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"em\", \"met_CORE\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"em\", \"met_raw\", \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met_CORE\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met_raw\", \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"met_CORE\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"met_raw\", \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"met_CORE\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"met_raw\", \"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"em\", \"met\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"met\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"met\",\"passtrig\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"ht\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"ht\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"ht\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"njets\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"njets\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"njets\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"nbjets\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"nbjets\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"nbjets\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"mll\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"mll\",\"passtrig\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"mll\",\"passtrig\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"mll\",     \"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"njets\",   \"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"nbjets\",  \"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"ht\",      \"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met_CORE\",\"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met_raw\", \"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"mt3\",     \"threelep\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"mll\",     \"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"njets\",   \"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"nbjets\",  \"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"ht\",      \"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"met_CORE\",\"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"met_raw\", \"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"mt3\",     \"threelep\" )"     

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"mll\",     \"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"njets\",   \"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"nbjets\",  \"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"ht\",      \"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"met_CORE\",\"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"met_raw\", \"threelep\" )"     
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"mt3\",     \"threelep\" )"     


# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met_raw\",        \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met\",            \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met_mettoolbox\", \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met_raw\",        \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met_CORE\",       \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"nVert\",          \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"ptdil\",          \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"ht\",             \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"njets\",          \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"met_raw\",        \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"metphir\",        \"passtrig\" )"  &
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"mt3\",            \"passtrig\" )"  &

# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ll\", \"mll\",       \"threelep\" )" 
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"ee\", \"mll\",       \"threelep\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"mm\", \"mll\",       \"threelep\" )"  
# root -b -q "drawDatavsMC.cc+( \"$analysis_version\", $lumi, \"_inclusive\", \"em\", \"mll\",       \"threelep\" )" 
