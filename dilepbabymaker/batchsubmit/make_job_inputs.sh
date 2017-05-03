#!/bin/bash

THISDIR=`pwd`
cd ..
tar -czf batchsubmit/job_input/package.tar.gz *.so puWeight2016.root btagsf leptonSFs xsec_susy_13tev.root T5ZZ_entries.root TChiHZ_HToBB_ZToLL_entries.root TChiZZ_ZToLL_entries.root TChiWZ_ZToLL_entries.root jetCorrections processBaby skim_macro.C MVAinput Cert*.txt ../CORE/Tools/jetcorr/data/run2_25ns/
cd $THISDIR
cp wrapper_auto.sh sweeproot.sh sweeproot_macro.C merge_script.sh merge_macro.C job_input/
