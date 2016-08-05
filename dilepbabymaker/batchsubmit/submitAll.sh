#!/bin/bash
voms-proxy-init -voms cms -valid 240:00
condor_submit configs_V08-11-04/condor_V08-11-04_ttgamma_incl_amcnlo.cmd
condor_submit configs_V08-11-04/condor_V08-11-04_wjets_ht100_amcnlo.cmd
condor_submit configs_V08-11-04/condor_V08-11-04_wjets_ht1200_amcnlo.cmd
condor_submit configs_V08-11-04/condor_V08-11-04_wjets_ht200_amcnlo.cmd
condor_submit configs_V08-11-04/condor_V08-11-04_wjets_ht2500_amcnlo.cmd
condor_submit configs_V08-11-04/condor_V08-11-04_wjets_ht400_amcnlo.cmd
condor_submit configs_V08-11-04/condor_V08-11-04_wjets_ht600_amcnlo.cmd
condor_submit configs_V08-11-04/condor_V08-11-04_wjets_ht800_amcnlo.cmd
condor_submit configs_V08-11-04/condor_V08-11-04_wjets_incl_amcnlo.cmd
