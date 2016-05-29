#!/bin/bash

#
# args
#

FILEID=$1
FILE=$2
COPYDIR=$3

echo "[wrapper] FILEID    = " ${FILEID}
echo "[wrapper] FILE      = " ${FILE}
echo "[wrapper] COPYDIR   = " ${COPYDIR}

#
# set up environment
#
CMSSW_VERSION=CMSSW_8_0_7

echo "[wrapper] setting env"
export SCRAM_ARCH=slc6_amd64_gcc530
source /cvmfs/cms.cern.ch/cmsset_default.sh
OLDDIR=`pwd`
cd /cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw/$CMSSW_VERSION/src
#cmsenv
eval `scramv1 runtime -sh`
cd $OLDDIR

# ### version using nfs install of CMSSW
# echo "[wrapper] setting env"
# export SCRAM_ARCH=slc6_amd64_gcc491
# source /nfs-7/cmssoft/cms.cern.ch/cmssw/cmsset_default.sh
# OLDDIR=`pwd`
# cd /nfs-7/cmssoft/cms.cern.ch/cmssw/slc6_amd64_gcc491/cms/cmssw-patch/$CMSSW_VERSION/src
# #cmsenv
# eval `scramv1 runtime -sh`
# cd $OLDDIR

echo

echo "[wrapper] printing env"
printenv

#
# untar input sandbox
#

echo "[wrapper] extracting input sandbox"
tar -zxf input.tar.gz

#source job_input/setupenv.sh
#printenv

cd job_input
echo "[wrapper] input contents are"
ls -a

echo "[wrapper] directory contents are"
ls

#
# run it
#
./processBaby ${FILEID} ${FILE}

#
# do something with output
#

echo "[wrapper] output is"
ls

#
# clean up
#

echo "[wrapper] copying file"
OUTPUT=`ls | grep ${FILEID}`
echo "[wrapper] OUTPUT = " ${OUTPUT}

if [ ! -d "${COPYDIR}" ]; then
    echo "creating output directory " ${COPYDIR}
    mkdir ${COPYDIR}
fi

lcg-cp -b -D srmv2 --vo cms --connect-timeout 60 --sendreceive-timeout 4200  --verbose file:`pwd`/${OUTPUT} srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=${COPYDIR}/${OUTPUT}

echo "[wrapper] cleaning up"
for FILE in `find . -not -name "*stderr" -not -name "*stdout"`; do rm -rf $FILE; done
echo "[wrapper] cleaned up"
ls


