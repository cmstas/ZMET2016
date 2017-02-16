#!/bin/bash

#
# args
#

FILEID=${OUTPUT_NAMES}
FILE=${FILENAME}
COPYDIR=${OUTPUT_NAMES}

echo "[wrapper] FILEID    = " ${FILEID}
echo "[wrapper] FILE      = " ${FILE}
echo "[wrapper] COPYDIR   = " ${COPYDIR}

#
# set up environment
#
CMSSW_VERSION=CMSSW_8_0_5

###version using cvmfs install of CMSSW
echo "[wrapper] setting env"
export SCRAM_ARCH=slc6_amd64_gcc530
source /cvmfs/cms.cern.ch/cmsset_default.sh
OLDDIR=`pwd`
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/cmssw/$CMSSW_VERSION/src
#cmsenv
eval `scramv1 runtime -sh`
cd $OLDDIR

# ### version using nfs install of CMSSW
# echo "[wrapper] setting env"
# export SCRAM_ARCH=slc6_amd64_gcc493
# source /nfs-7/cmssoft/cms.cern.ch/cmssw/cmsset_default.sh
# OLDDIR=`pwd`
# cd /nfs-7/cmssoft/cms.cern.ch/cmssw/slc6_amd64_gcc493/cms/cmssw-patch/$CMSSW_VERSION/src
# #cmsenv
# eval `scramv1 runtime -sh`
# cd $OLDDIR

echo

echo "[wrapper] printing env"
printenv
echo 

echo "[wrapper] hostname  = " `hostname`
echo "[wrapper] date      = " `date`
echo "[wrapper] linux timestamp = " `date +%s`
echo "[wrapper] checking input file with ls"
ls -alrth ${FILE}

# catch exit code
if [ $? -ne 0 ]; then
    echo "[wrapper] could not find input file, trying xrootd instead"
    FILESHORT=${FILE#/hadoop/cms}
    xrdfs xrootd.t2.ucsd.edu ls ${FILESHORT}
    if [ $? -ne 0 ]; then
	echo "[wrapper] could not find input file with xrootd either, exiting"
	exit 1
    else
	echo "[wrapper] found file with xrootd, will proceed"
	FILE="root://xrootd.t2.ucsd.edu/"${FILESHORT}
    fi
fi

#
# untar input sandbox
#

echo "[wrapper] extracting input sandbox"
tar -zxf package.tar.gz

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
echo "[wrapper] running: ./processBaby ${FILEID} ${FILE}"

./processBaby ${FILEID} ${FILE}

#
# do something with output
#

echo "[wrapper] output is"
ls


OUTPUT=`ls | grep ${FILEID}`
echo "[wrapper] OUTPUT = " ${OUTPUT}
mv ${OUTPUT} output.root

# Rigorous sweeproot which checks ALL branches for ALL events.
# If GetEntry() returns -1, then there was an I/O problem, so we will delete it
cat > rigorousSweepRoot.py << EOL
import ROOT as r
import os, sys

f1 = r.TFile("output.root")
if not f1 or not f1.IsOpen() or f1.IsZombie():
    print "[RSR] removing zombie output.root because it does not deserve to live"
    os.system("rm output.root")
    sys.exit()

t = f1.Get("t")
if not t:
    print "[RSR] removing output.root due to missing tree"
    os.system("rm output.root")
    sys.exit()

print "[RSR] ntuple has %i events" % t.GetEntries()

foundBad = False
for i in range(0,t.GetEntries(),1):
    if t.GetEntry(i) < 0:
        foundBad = True
        print "[RSR] found bad event %i" % i
        break

if foundBad:
    print "[RSR] removing output.root because it does not deserve to live"
    os.system("rm output.root")
else:
    print "[RSR] passed the rigorous sweeproot"
EOL

date +%s
echo "[wrapper] running rigorousSweepRoot.py"
python rigorousSweepRoot.py
date +%s


#
# do skim
#

echo "[wrapper] doing skim"
root -b -q skim_macro.C

#
# clean up
#

echo "[wrapper] copying file"

# if [ ! -d "${COPYDIR}" ]; then
#     echo "creating output directory " ${COPYDIR}
#     mkdir ${COPYDIR}
# fi

# gfal-copy -p -f -t 4200 --verbose file:`pwd`/${OUTPUT} srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=${COPYDIR}/${OUTPUT}

# echo "[wrapper] cleaning up"
# for FILE in `find . -not -name "*stderr" -not -name "*stdout"`; do rm -rf $FILE; done
# echo "[wrapper] cleaned up"
# ls
