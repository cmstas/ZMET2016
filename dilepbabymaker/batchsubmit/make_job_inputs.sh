#!/bin/bash

THISDIR=`pwd`
cd ..
tar -czf batchsubmit/job_input/package.tar.gz *.so pileup_jul21_nominalUpDown.root xsec_higgsino.root btagsf leptonSFs TChiWZ_entries_V08-00-05_FS.root xsec_susy_13tev.root T5ZZ_entries.root jetCorrections processBaby MVAinput Cert*.txt TChiHZ_HToBB_ZToLL.root 
cd $THISDIR
cp wrapper_auto.sh sweeproot.sh sweeproot_macro.C merge_script.sh merge_macro.C job_input/
