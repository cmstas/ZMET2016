#!/bin/bash
voms-proxy-init -voms cms -valid 240:00
condor_submit configs_V7680-hybrid-00_photonstudies/condor_V7680-hybrid-00_photonstudies_data_2016B_Prompt_ph_v1.cmd
condor_submit configs_V7680-hybrid-00_photonstudies/condor_V7680-hybrid-00_photonstudies_data_2016B_Prompt_ph_v2.cmd
