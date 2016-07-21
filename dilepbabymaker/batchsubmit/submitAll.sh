#!/bin/bash
voms-proxy-init -voms cms -valid 240:00
condor_submit configs_V08-11-00/condor_V08-11-00_data_2016D_Prompt_ee_v2.cmd
condor_submit configs_V08-11-00/condor_V08-11-00_data_2016D_Prompt_em_v2.cmd
condor_submit configs_V08-11-00/condor_V08-11-00_data_2016D_Prompt_mm_v2.cmd
condor_submit configs_V08-11-00/condor_V08-11-00_data_2016D_Prompt_ph_v2.cmd
