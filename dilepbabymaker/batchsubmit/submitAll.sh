#!/bin/bash
voms-proxy-init -voms cms -valid 240:00
condor_submit configs_V07-06-02/condor_V07-06-02_data_2015C25ns16Dec2015_em.cmd
