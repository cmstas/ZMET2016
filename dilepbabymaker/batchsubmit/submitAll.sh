#!/bin/bash
voms-proxy-init -voms cms -valid 240:00
condor_submit configs_V08-07-01/condor_V08-07-01_data_2016B_Prompt_ee_v1.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_data_2016B_Prompt_ee_v2.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_data_2016B_Prompt_em_v1.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_data_2016B_Prompt_em_v2.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_data_2016B_Prompt_mm_v1.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_data_2016B_Prompt_mm_v2.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_data_2016B_Prompt_ph_v1_brokentrigs.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_data_2016B_Prompt_ph_v2_brokentrigs.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_dy_m50_mgmlm_ext1.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_dy_m50_mgmlm_ht100_ext1.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_dy_m50_mgmlm_ht200_ext1.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_dy_m50_mgmlm_ht400_ext1.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_dy_m50_mgmlm_ht600.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_dy_m50_mgmlm_ht600_ext1.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_gjetsht100_dr0p4_mgmlm.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_gjetsht200_dr0p4_mgmlm.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_gjetsht400_dr0p4_mgmlm.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_gjetsht40_dr0p4_mgmlm.cmd
condor_submit configs_V08-07-01/condor_V08-07-01_gjetsht600_dr0p4_mgmlm.cmd
