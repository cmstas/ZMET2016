#!/bin/bash
voms-proxy-init -voms cms -valid 240:00
condor_submit configs_V08-07-02/condor_V08-07-02_data_2016B_Prompt_ee_v2.cmd
condor_submit configs_V08-07-02/condor_V08-07-02_data_2016B_Prompt_ee_v2_resubmit.cmd
condor_submit configs_V08-07-02/condor_V08-07-02_data_2016B_Prompt_ee_v2_resubmit_resubmit.cmd
condor_submit configs_V08-07-02/condor_V08-07-02_data_2016B_Prompt_em_v2.cmd
condor_submit configs_V08-07-02/condor_V08-07-02_data_2016B_Prompt_em_v2_resubmit.cmd
condor_submit configs_V08-07-02/condor_V08-07-02_data_2016B_Prompt_em_v2_resubmit_resubmit.cmd
condor_submit configs_V08-07-02/condor_V08-07-02_data_2016B_Prompt_mm_v2.cmd
condor_submit configs_V08-07-02/condor_V08-07-02_data_2016B_Prompt_mm_v2_resubmit.cmd
condor_submit configs_V08-07-02/condor_V08-07-02_data_2016B_Prompt_mm_v2_resubmit_resubmit.cmd
condor_submit configs_V08-07-02/condor_V08-07-02_data_2016B_Prompt_ph_v2.cmd
condor_submit configs_V08-07-02/condor_V08-07-02_data_2016B_Prompt_ph_v2_resubmit.cmd
condor_submit configs_V08-07-02/condor_V08-07-02_data_2016B_Prompt_ph_v2_resubmit_resubmit.cmd
