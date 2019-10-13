#! /bin/bash

# Instructions to run limit code taken from:
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit#ROOT6_SLC6_release_CMSSW_7_4_X

# to be run from a clean environment

#source /code/osgcode/cmssoft/cmsset_default.sh  > /dev/null 2>&1
#export SCRAM_ARCH=slc6_amd64_gcc481
cmsrel CMSSW_7_4_7
cd CMSSW_7_4_7/src 
cmsenv

#git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
#git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
git clone git@github.com:cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
cd HiggsAnalysis/CombinedLimit
git fetch origin
#git checkout 74x-root6
git checkout v6.3.1
scramv1 b clean; scramv1 b -j8

didcompile=$?
if [ $didcompile -eq 0 ]; then
	echo "Compiled successfully."
else
	echo "Did not compile successfully. Exiting."
	exit 2
fi

cd $CMSSW_BASE/src/

if [ ! -e log ]; then
	echo "Making directory: log"
	mkdir log
fi

# makeLimitTable.C
# make_rValues.C
# make_sigValues.C
# doLimits.sh
# doSignif.sh
