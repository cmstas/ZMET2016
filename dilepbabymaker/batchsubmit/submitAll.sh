#!/bin/bash
voms-proxy-init -voms cms -valid 240:00
condor_submit configs_V07-06-01/condor_V07-06-01_data_2015C25ns16Dec2015_em.cmd
