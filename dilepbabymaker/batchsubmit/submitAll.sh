#!/bin/bash
voms-proxy-init -voms cms -valid 240:00
condor_submit configs_V7680-hybrid-00/condor_V7680-hybrid-00_data_2016B_Prompt_ee.cmd
condor_submit configs_V7680-hybrid-00/condor_V7680-hybrid-00_data_2016B_Prompt_em.cmd
condor_submit configs_V7680-hybrid-00/condor_V7680-hybrid-00_data_2016B_Prompt_mm.cmd
condor_submit configs_V7680-hybrid-00/condor_V7680-hybrid-00_data_2016B_Prompt_ph.cmd
