#! /bin/bash

source /code/osgcode/cmssoft/cmsset_default.sh  > /dev/null 2>&1
export SCRAM_ARCH=slc6_amd64_gcc481
cmsrel CMSSW_7_1_5
cd CMSSW_7_1_5/src/
cmsenv

git clone git@github.com:your-user-name/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
cd HiggsAnalysis/CombinedLimit
git remote add upstream  https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git
git fetch upstream
git checkout -b slc6-root5.34.17  upstream/slc6-root5.34.17 

cd $CMSSW_BASE/src/

if [ ! -e log ]; then
	mkdir log
fi

# makeLimitTable.C
# make_rValues.C
# make_sigValues.C
# doLimits.sh
# doSignif.sh
