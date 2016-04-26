#!/bin/bash
voms-proxy-init -voms cms -valid 240:00
condor_submit configs_V07-06-06/condor_V07-06-06_data_2015C25ns16Dec2015_ee.cmd
condor_submit configs_V07-06-06/condor_V07-06-06_data_2015C25ns16Dec2015_me.cmd
condor_submit configs_V07-06-06/condor_V07-06-06_data_2015C25ns16Dec2015_mm.cmd
condor_submit configs_V07-06-06/condor_V07-06-06_data_2015D25ns16Dec2015_ee.cmd
condor_submit configs_V07-06-06/condor_V07-06-06_data_2015D25ns16Dec2015_me.cmd
condor_submit configs_V07-06-06/condor_V07-06-06_data_2015D25ns16Dec2015_mm.cmd
