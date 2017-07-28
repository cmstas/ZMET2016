import os
import sys

os.system("source make_job_inputs.sh") #Should remake the tarball and ensure running ducks always takes the newest code.

d_ds2name = {
    "backgrounds": {
### Wjets
        "/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                        : "wjets_incl_mgmlm",
        "/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"       : "wjets_ht100_mgmlm_ext1",
        "/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"       : "wjets_ht200_mgmlm_ext1",
        "/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"       : "wjets_ht400_mgmlm_ext1",
        "/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"       : "wjets_ht600_mgmlm_ext1",
        "/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"      : "wjets_ht800_mgmlm_ext1",
        "/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"          : "wjets_ht1200_mgmlm_nonext",
        "/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"      : "wjets_ht2500_mgmlm_ext1",
### DYToLL
        "/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"         : "dy_m1050_amcnlo",
        "/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_HCALDebug_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"        : "dy_m50_amcnlo",
        "/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"               : "dy_m1050_mgmlm",
        "/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM"              : "dy_m50_mgmlm_ext1",
        "/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"  : "dy_m50_mgmlm_ht100_ext1",
        "/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"  : "dy_m50_mgmlm_ht200_ext1",
        "/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"  : "dy_m50_mgmlm_ht400_ext1",
        "/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"       : "dy_m50_mgmlm_ht600_nonext",
        "/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"      : "dy_m50_mgmlm_ht800_nonext",
        "/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"     : "dy_m50_mgmlm_ht1200_nonext",
        "/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"      : "dy_m50_mgmlm_ht2500_nonext",
### GJets dr0p4
#        "/GJets_DR-0p4_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_qcut19_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"    : "gjetsht40_dr0p4_mgmlm",
#        "/GJets_DR-0p4_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_qcut19_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"   : "gjetsht100_dr0p4_mgmlm",
#        "/GJets_DR-0p4_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_qcut19_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"   : "gjetsht200_dr0p4_mgmlm",
#         "/GJets_DR-0p4_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_qcut19_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"   : "gjetsht400_dr0p4_mgmlm",
#        "/GJets_DR-0p4_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_qcut19_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"   : "gjetsht600_dr0p4_mgmlm",
### GJets dr0p05
        "/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"             : "gjetsht40_dr0p05_mgmlm_ext1",
        "/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                 : "gjetsht100_dr0p05_mgmlm_nonext",
        "/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"            : "gjetsht200_dr0p05_mgmlm_ext1",
        "/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                 : "gjetsht400_dr0p05_mgmlm_nonext",
        "/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                 : "gjetsht600_dr0p05_mgmlm_nonext",
        "/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"            : "gjetsht600_dr0p05_mgmlm_ext1",
### ttbar
        "/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"            : "ttbar_dilep_powheg",
        "/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"            : "ttbar_1ltop_mgmlm_nonext",
        "/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"       : "ttbar_1ltop_mgmlm_ext1",
        "/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"         : "ttbar_1ltbr_mgmlm_nonext", 
        "/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"    : "ttbar_1ltbr_mgmlm_ext1", 
        "/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                     : "ttbar_dilep_mgmlm_nonext",
        "/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                : "ttbar_dilep_mgmlm_ext1",
### single top
        "/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "stt_antitop_incdec_powheg",
        "/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"     : "stt_top_incdec_powheg",
        "/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                    : "sts_4f_leptonic_amcnlo",
        "/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                        : "sttw_top_nofullhaddecay_powheg",
        "/ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                    : "sttw_antitop_nofullhaddecay_powheg",
        "/tZq_ll_4f_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                                               : "tzq_ll_amcnlo",
        "/ST_tWll_5f_LO_13TeV-MadGraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                : "sttwll_madgraph",
### diboson
        "/WWTo2L2Nu_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                : "ww_2l2nu_powheg",
        "/WWToLNuQQ_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                : "ww_lnuqq_powheg",
        "/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3/MINIAODSIM"        : "wz_lnqq_amcnlo",
        "/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"          : "wz_1l3n_amcnlo",
        "/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"    : "wpwpjj_ewk-qcd_madgraph",
        "/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"              : "ww_2l2nu_dbl_scat",
        "/WmWmJJ_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                           : "wmwm_powheg",
        "/EWKWPlus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"      : "Wpjj_lnu_madgraph",
        "/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"           : "Zjj_m50)madgraph",
        "/EWKWMinus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"     : "Wmjj_lnu_madgraph",
# missing        ""                                                : "wz_2l2q_amcnlo",
        "/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"            : "wz_3lnu_powheg",
        "/ZZTo2L2Nu_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                        : "zz_2l2n_powheg",
        "/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"           : "zz_2l2q_powheg",
        "/ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"          : "zz_2q2n_amcnlo",
        "/ZZTo4L_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                           : "zz_4l_powheg",
### ttV
        "/ttZJets_13TeV_madgraphMLM/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                       : "ttz_incl_mgmlm",
        "/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"           : "ttz_2l2n_amcnlo",
# missing        "/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                : "ttz_qq_amcnlo",
        "/ttWJets_13TeV_madgraphMLM/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                       : "ttw_incl_mgmlm",
        "/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"   : "ttw_ln_amcnlo_ext2",
        "/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"         : "ttw_qq_amcnlo",
        "/ttHTobb_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                   : "tth_bb_powheg",
        "/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"       : "tth_nonbb_powheg",
#        "/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                            : "tttt_amcnlo",
### ewk gamma contamination
        "/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"           : "wgjets_incl_amcnlo",
        "/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                 : "wgjets_incl_mgmlm",
        "/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"       : "wgjets_ptg40_mgmlm",
        "/WGJets_MonoPhoton_PtG-130_TuneCUETP8M1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"           : "wgjets_ptg130_mgmlm",
        "/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"            : "zgamma_2lG_amc",
        "/ZNuNuGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"   : "znunugamma_ptg40_mgmlm",
        "/ZNuNuGJets_MonoPhoton_PtG-130_TuneCUETP8M1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"       : "znunugamma_ptg130_mgmlm",
        "/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"         : "ttg_incl_amcnlo",
        "/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"               : "vh_nonbb_amcnlo",
# buggy        "/TTGamma_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"   : "ttg_1ltop_mgmlm",
# buggy        "/TTGamma_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM": "ttg_1ltbr_mgmlm",
# buggy        "/TTGamma_Dilept_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"            : "ttg_dilep_mgmlm",
### triboson
        "/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"   : "www_incl_amcnlo",
        "/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"      : "wwz_incl_amcnlo",
        "/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"      : "wzz_incl_amcnlo",
        "/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"      : "zzz_incl_amcnlo",
        "/WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"      : "wzg_incl_amcnlo",
        "/WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" : "wwg_incl_amcnlo",
###Private from Mia        
        "/TEST-www/www-Private80X-v1/USER"                                                                                                       : "www_2l_mia",
        "/TEST-www/wwwext-Private80X-v1/USER"                                                                                                    : "www_2l_ext1_mia",
        "/TEST-tth/tth-Private80X-v1/USER"                                                                                                       : "tth_mia"
### QCD pt-binned EM-enriched (to be added)
#        "/QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"       : "qcdpt20_emenriched_nonext",
#        "/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"       : "qcdpt30_emenriched_nonext",
#        "/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"  : "qcdpt30_emenriched_ext1",
#        "/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"  : "qcdpt50_emenriched_ext1",
#        "/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" : "qcdpt80_emenriched_ext1",
# missing 120
#        "/QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"     : "qcdpt170_emenriched_nonext",
#        "/QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"     : "qcdpt300_emenriched_nonext",
### QCD HT-binned
#        "/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"        : "qcdht100_nonext", 
#        "/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"        : "qcdht200_nonext", 
#        "/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"   : "qcdht200_ext1", 
#        "/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"        : "qcdht300_nonext", 
#        "/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"   : "qcdht300_ext1", 
#        "/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"        : "qcdht500_nonext", 
#        "/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM"   : "qcdht500_ext1", 
#        "/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"       : "qcdht700_nonext", 
#        "/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"  : "qcdht700_ext1", 
#        "/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"      : "qcdht1000_nonext", 
#        "/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" : "qcdht1000_ext1", 
#        "/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"      : "qcdht1500_nonext", 
#        "/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" : "qcdht1500_ext1", 
#        "/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"       : "qcdht2000_nonext", 
#        "/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"  : "qcdht2000_ext1",
 },
    "data": {
        "/SingleMuon/Run2016B-03Feb2017_ver2-v2/MINIAOD"      : "data_Run2016B_03feb2017rereco_sm_v2",
        "/SinglePhoton/Run2016B-03Feb2017_ver2-v2/MINIAOD"    : "data_Run2016B_03feb2017rereco_ph_v2",
        "/DoubleEG/Run2016B-03Feb2017_ver2-v2/MINIAOD"        : "data_Run2016B_03feb2017rereco_ee_v2",
        "/DoubleMuon/Run2016B-03Feb2017_ver2-v2/MINIAOD"      : "data_Run2016B_03feb2017rereco_mm_v2",
        "/MuonEG/Run2016B-03Feb2017_ver2-v2/MINIAOD"          : "data_Run2016B_03feb2017rereco_em_v2",

        "/SingleMuon/Run2016C-03Feb2017-v1/MINIAOD"      : "data_Run2016C_03feb2017rereco_sm_v1",
        "/SinglePhoton/Run2016C-03Feb2017-v1/MINIAOD"    : "data_Run2016C_03feb2017rereco_ph_v1",
        "/DoubleEG/Run2016C-03Feb2017-v1/MINIAOD"        : "data_Run2016C_03feb2017rereco_ee_v1",
        "/DoubleMuon/Run2016C-03Feb2017-v1/MINIAOD"      : "data_Run2016C_03feb2017rereco_mm_v1",
        "/MuonEG/Run2016C-03Feb2017-v1/MINIAOD"          : "data_Run2016C_03feb2017rereco_em_v1",

        "/SingleMuon/Run2016D-03Feb2017-v1/MINIAOD"      : "data_Run2016D_03feb2017rereco_sm_v1",
        "/SinglePhoton/Run2016D-03Feb2017-v1/MINIAOD"    : "data_Run2016D_03feb2017rereco_ph_v1",
        "/DoubleEG/Run2016D-03Feb2017-v1/MINIAOD"        : "data_Run2016D_03feb2017rereco_ee_v1",
        "/DoubleMuon/Run2016D-03Feb2017-v1/MINIAOD"      : "data_Run2016D_03feb2017rereco_mm_v1",
        "/MuonEG/Run2016D-03Feb2017-v1/MINIAOD"          : "data_Run2016D_03feb2017rereco_em_v1",

        "/SingleMuon/Run2016E-03Feb2017-v1/MINIAOD"      : "data_Run2016E_03feb2017rereco_sm_v1",
        "/SinglePhoton/Run2016E-03Feb2017-v1/MINIAOD"    : "data_Run2016E_03feb2017rereco_ph_v1",
        "/DoubleEG/Run2016E-03Feb2017-v1/MINIAOD"        : "data_Run2016E_03feb2017rereco_ee_v1",
        "/DoubleMuon/Run2016E-03Feb2017-v1/MINIAOD"      : "data_Run2016E_03feb2017rereco_mm_v1",
        "/MuonEG/Run2016E-03Feb2017-v1/MINIAOD"          : "data_Run2016E_03feb2017rereco_em_v1",

        "/SingleMuon/Run2016F-03Feb2017-v1/MINIAOD"      : "data_Run2016F_03feb2017rereco_sm_v1",
        "/SinglePhoton/Run2016F-03Feb2017-v1/MINIAOD"    : "data_Run2016F_03feb2017rereco_ph_v1",
        "/DoubleEG/Run2016F-03Feb2017-v1/MINIAOD"        : "data_Run2016F_03feb2017rereco_ee_v1",
        "/DoubleMuon/Run2016F-03Feb2017-v1/MINIAOD"      : "data_Run2016F_03feb2017rereco_mm_v1",
        "/MuonEG/Run2016F-03Feb2017-v1/MINIAOD"          : "data_Run2016F_03feb2017rereco_em_v1",

        "/SingleMuon/Run2016G-03Feb2017-v1/MINIAOD"      : "data_Run2016G_03feb2017rereco_sm_v1",
        "/SinglePhoton/Run2016G-03Feb2017-v1/MINIAOD"    : "data_Run2016G_03feb2017rereco_ph_v1",
        "/DoubleEG/Run2016G-03Feb2017-v1/MINIAOD"        : "data_Run2016G_03feb2017rereco_ee_v1",
        "/DoubleMuon/Run2016G-03Feb2017-v1/MINIAOD"      : "data_Run2016G_03feb2017rereco_mm_v1",
        "/MuonEG/Run2016G-03Feb2017-v1/MINIAOD"          : "data_Run2016G_03feb2017rereco_em_v1",

        "/SingleMuon/Run2016H-03Feb2017_ver2-v1/MINIAOD"     : "data_Run2016H_03feb2017rereco_sm_v2",
        "/SingleMuon/Run2016H-03Feb2017_ver3-v1/MINIAOD"     : "data_Run2016H_03feb2017rereco_sm_v3",
        "/SinglePhoton/Run2016H-03Feb2017_ver2-v1/MINIAOD"   : "data_Run2016H_03feb2017rereco_ph_v2",
        "/SinglePhoton/Run2016H-03Feb2017_ver3-v1/MINIAOD"   : "data_Run2016H_03feb2017rereco_ph_v3",
        "/DoubleEG/Run2016H-03Feb2017_ver2-v1/MINIAOD"       : "data_Run2016H_03feb2017rereco_ee_v2",
        "/DoubleEG/Run2016H-03Feb2017_ver3-v1/MINIAOD"       : "data_Run2016H_03feb2017rereco_ee_v3",
        "/DoubleMuon/Run2016H-03Feb2017_ver2-v1/MINIAOD"     : "data_Run2016H_03feb2017rereco_mm_v2",
        "/DoubleMuon/Run2016H-03Feb2017_ver3-v1/MINIAOD"     : "data_Run2016H_03feb2017rereco_mm_v3",
        "/MuonEG/Run2016H-03Feb2017_ver2-v1/MINIAOD"         : "data_Run2016H_03feb2017rereco_em_v2",
        "/MuonEG/Run2016H-03Feb2017_ver3-v1/MINIAOD"         : "data_Run2016H_03feb2017rereco_em_v3"

        #=============
        # 2017
        #=============
        #------
        # 2017A
        #"/DoubleEG/Run2017A-PromptReco-v3/MINIAOD"           : "data_run2017A_PromptReco_ee_v3",
        #"/DoubleEG/Run2017A-PromptReco-v2/MINIAOD"           : "data_run2017A_PromptReco_ee_v2",
        #"/DoubleEG/Run2017A-PromptReco-v3/MINIAOD"           : "data_run2017A_PromptReco_ee_v3",
        #"/DoubleMuon/Run2017A-PromptReco-v1/MINIAOD"         : "data_run2017A_PromptReco_mm_v1",
        #"/DoubleMuon/Run2017A-PromptReco-v2/MINIAOD"         : "data_run2017A_PromptReco_mm_v2",
        #"/DoubleMuon/Run2017A-PromptReco-v3/MINIAOD"         : "data_run2017A_PromptReco_mm_v3",
        #"/MuonEG/Run2017A-PromptReco-v1/MINIAOD"             : "data_run2017A_PromptReco_em_v1",
        #"/MuonEG/Run2017A-PromptReco-v2/MINIAOD"             : "data_run2017A_PromptReco_em_v2",
        #"/MuonEG/Run2017A-PromptReco-v3/MINIAOD"             : "data_run2017A_PromptReco_em_v3",
        #"/SingleElectron/Run2017A-PromptReco-v2/MINIAOD"     : "data_run2017A_PromptReco_ee_v2",
        #"/SingleElectron/Run2017A-PromptReco-v3/MINIAOD"     : "data_run2017A_PromptReco_se_v3",
        #"/SingleMuon/Run2017A-PromptReco-v2/MINIAOD"         : "data_run2017A_PromptReco_sm_v2",
        #"/SingleMuon/Run2017A-PromptReco-v3/MINIAOD"         : "data_run2017A_PromptReco_sm_v3",
        #"/SinglePhoton/Run2017A-PromptReco-v1/MINIAOD"       : "data_run2017A_PromptReco_ph_v1",
        #"/SinglePhoton/Run2017A-PromptReco-v2/MINIAOD"       : "data_run2017A_PromptReco_ph_v2",
        #"/SinglePhoton/Run2017A-PromptReco-v3/MINIAOD"       : "data_run2017A_PromptReco_ph_v3",

    }
#    "scans": {
#        "/SMS-T5ZZ_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"                    : "t5zz_orig_80x_v2",
#        "/SMS-T5ZZ_mGluino-1850to2100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM" : "t5zz_mg1850_80x_v2",
#        "/SMS-TChiWZ_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM"            : "tchiwz_80x_v2",
#        "/SMS-TChiZZ_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"            : "tchizz_80x_v2",
#        "/SMS-TChiHZ_HToBB_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"      : "tchihz_80x_v2",
#    }
}

def dataset_to_shortname(ds):
    for typ_values in d_ds2name.values():
        for dname in typ_values:
            if dname == ds:
                return typ_values[dname]
    return "unknown"

inputs_path = os.path.abspath(__file__).rsplit("/",1)[0]+"/job_input/"
sweepRoot_scripts = [inputs_path+"sweeproot.sh", inputs_path+"sweeproot_macro.C"]
merging_scripts = [inputs_path+"merge_script.sh", inputs_path+"merge_macro.C"]

tag = "test"
package = inputs_path+"package.tar.gz"
executable = inputs_path+"wrapper_auto.sh"
dashboard_name = "AutoTwopler_ZMETbabies"
baby_merged_dir = "/hadoop/cms/store/user/%s/AutoTwopler_babies/merged/"%(os.getenv("USER"))
merge_babies_on_condor = True

if not os.path.isfile(package):
    raise Exception("Woah! Did you run make_job_inputs.sh? I don't see the package.tar.gz file in %s" % inputs_path)
elif ((os.path.getmtime(package) < os.path.getmtime("../ScanChain.cc")) or (os.path.getmtime(package) < os.path.getmtime("../skim_macro.C"))):
    raise Exception("Woah! Did you run make_job_inputs.sh? It looks like ScanChain/skim_macro might be newer than the tarball in %s" % inputs_path)

