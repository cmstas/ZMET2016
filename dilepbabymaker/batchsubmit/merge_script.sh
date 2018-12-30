#!/bin/bash

eval "$1" # Beautiful trick - http://unix.stackexchange.com/a/185467

echo "hostname:" `hostname`
echo "Args:"
echo "UNMERGED_DIR: $UNMERGED_DIR"
echo "INPUT_NAMES: $INPUT_NAMES"
echo "OUTPUT_DIR: $OUTPUT_DIR"
echo "OUTPUT_NAME: $OUTPUT_NAME"
echo "SHORTNAME: $SHORTNAME"
echo "IMERGED: $IMERGED"

###version using cvmfs install of CMSSW
echo "[wrapper] setting env"
export SCRAM_ARCH=slc6_amd64_gcc530
source /cvmfs/cms.cern.ch/cmsset_default.sh
OLDDIR=`pwd`
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/cmssw/CMSSW_8_0_5/src
#cmsenv
eval `scramv1 runtime -sh`
cd $OLDDIR

OUTFILE=${SHORTNAME}_${OUTPUT_NAME}_${IMERGED}.root

if [ ! -d ${OUTPUT_DIR} ]; then
    echo "creating output directory: " ${OUTPUT_DIR}
    mkdir -p ${OUTPUT_DIR}
fi

echo "Merging files ${UNMERGED_DIR}/${INPUT_NAMES} into ${OUTPUT_DIR}"
echo "${INPUT_NAMES}" > list_input.txt
echo "root -l -n -b -q merge_macro.C+(\"${UNMERGED_DIR}\",\"list_input.txt\",\"${OUTFILE}\")"
root -l -n -b -q "merge_macro.C+(\"${UNMERGED_DIR}\",\"list_input.txt\",\"${OUTFILE}\")"

# Rigorous sweeproot which checks ALL branches for ALL events.
# If GetEntry() returns -1, then there was an I/O problem, so we will delete it
cat > rigorousSweepRoot.py << EOL
import ROOT as r
import os, sys

print "[RSR] inside rigorousSweepRoot"

f1 = r.TFile("${OUTFILE}")
if not f1 or not f1.IsOpen() or f1.IsZombie():
    print "[RSR] removing zombie ${OUTFILE} because it does not deserve to live"
    os.system("rm ${OUTFILE}")
    sys.exit()

t = f1.Get("t")
if not t:
    print "[RSR] removing ${OUTFILE} due to missing tree"
    os.system("rm ${OUTFILE}")
    sys.exit()

print "[RSR] ntuple has %i events" % t.GetEntries()

foundBad = False
for i in range(0,t.GetEntries(),1):
    if t.GetEntry(i) < 0:
        foundBad = True
        print "[RSR] found bad event %i" % i
        break

if foundBad:
    print "[RSR] removing ${OUTFILE} because it does not deserve to live"
    os.system("rm ${OUTFILE}")
else:
    print "[RSR] passed the rigorous sweeproot"
EOL

date +%s
echo "[merge_script] running rigorousSweepRoot.py"
python rigorousSweepRoot.py
date +%s

pwd
echo "[merge_script] output is"
ls

##
## copy file to output
##
gfal-copy -p -f -t 4200 --verbose file://`pwd`/${OUTFILE} srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=${OUTPUT_DIR}/${OUTFILE}
#cp `pwd`/${OUTFILE} ${OUTPUT_DIR}/${OUTFILE}

echo "[merge_script] cleaning up"
for FILE in `find . -not -name "*stderr" -not -name "*stdout"`; do rm -rf $FILE; done
echo "[merge_script] cleaned up"
ls -l
