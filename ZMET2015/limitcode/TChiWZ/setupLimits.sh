#! /bin/bash

export SCRAM_ARCH=slc6_amd64_gcc481
cmsrel CMSSW_7_1_5
if [ ! -e CMSSW_7_1_5 ]; then
	cd CMSSW_7_1_5/src/
	cmsenv
else
	echo "Directory: CMSSW_7_1_5 Does not exist. Exiting."
	exit 1
fi

git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
cd HiggsAnalysis/CombinedLimit
git fetch origin
git checkout v5.0.1
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
	cout "Making directory: log"
	mkdir log
fi

# makeLimitTable.C
# make_rValues.C
# make_sigValues.C
# doLimits.sh
# doSignif.sh
