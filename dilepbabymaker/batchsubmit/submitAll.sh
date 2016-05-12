#!/bin/bash
voms-proxy-init -voms cms -valid 240:00
condor_submit configs_V07-06-09/condor_V07-06-09_DYJetsToLL_M-10to50_amcNLO_v1.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_DYJetsToLL_M-50_amcNLO_v1.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_ST_tW_antitop_5f_inclusiveDecays_13TeV.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_ST_tW_top_5f_inclusiveDecays_13TeV.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_WWTo2L2Nu_13TeV-powheg.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_ZZTo2L2Nu_13TeV_powheg_pythia8.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_ZZTo4L_13TeV_powheg_pythia8.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_data_2015C25ns16Dec2015_ee.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_data_2015C25ns16Dec2015_me.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_data_2015C25ns16Dec2015_mm.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_data_2015D25ns16Dec2015_ee.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_data_2015D25ns16Dec2015_me.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_data_2015D25ns16Dec2015_mm.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_ttHJetToNonbb_M125_13TeV.cmd
condor_submit configs_V07-06-09/condor_V07-06-09_ttTo2L2Nu_powheg.cmd
