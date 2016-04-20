#!/bin/bash
voms-proxy-init -voms cms -valid 240:00
condor_submit configs_V07-06-03/condor_V07-06-03_data_2015C25ns16Dec2015_ee.cmd
condor_submit configs_V07-06-03/condor_V07-06-03_data_2015C25ns16Dec2015_me.cmd
condor_submit configs_V07-06-03/condor_V07-06-03_data_2015C25ns16Dec2015_mm.cmd
condor_submit configs_V07-06-03/condor_V07-06-03_data_2015D25ns16Dec2015_ee.cmd
condor_submit configs_V07-06-03/condor_V07-06-03_data_2015D25ns16Dec2015_me.cmd
condor_submit configs_V07-06-03/condor_V07-06-03_data_2015D25ns16Dec2015_mm.cmd
