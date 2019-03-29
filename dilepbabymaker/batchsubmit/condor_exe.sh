PACKAGE=package.tar.gz
OUTPUTDIR=$1
OUTPUTFILENAME=$2
INPUTFILENAME=$3
INDEX=$4
CMSSWVER=$5
SCRAMARCH=$6


echo "[wrapper] OUTPUTDIR       = " ${OUTPUTDIR}
echo "[wrapper] OUTPUTFILENAME  = " ${OUTPUTFILENAME}
echo "[wrapper] INPUTFILENAME  = " ${INPUTFILENAME}
echo "[wrapper] INDEX           = " ${INDEX}
echo "[wrapper] CMSSWVER        = " ${CMSSWVER}
echo "[wrapper] SCRAMARCH       = " ${SCRAMARCH}

echo "[wrapper] printing env"
printenv
echo

echo "[wrapper] hostname  = " `hostname`
echo "[wrapper] date      = " `date`
echo "[wrapper] linux timestamp = " `date +%s`

######################
# Set up environment #
######################
export SCRAM_ARCH=slc6_amd64_gcc630   # or whatever scram_arch you need for your desired CMSSW release
source /cvmfs/cms.cern.ch/cmsset_default.sh
pushd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/cmssw/CMSSW_9_4_9/src
eval `scramv1 runtime -sh`
popd

# Untar
tar -xzvf package.tar.gz
OUTPUTTAG=$(echo ${INPUTFILENAME##*/} | sed 's/\.root//')
MAXEVENTS=-1
echo "[wrapper] running babymaker"
echo "[wrapper] ./processBaby [$OUTPUTTAG] [$INPUTFILENAME] -1"
./processBaby "${OUTPUTTAG}" "${INPUTFILENAME}" "${MAXEVENTS}"

NAMEINCONDOR=$(cat outputName.txt)
echo "[wrapper] output file name = ${NAMEINCONDOR}.root"
ls -ltrh
echo "[wrapper] gfal-copy output file"
gfal-copy -p -f -t 4200 --verbose file://`pwd`/${NAMEINCONDOR}.root gsiftp://gftp.t2.ucsd.edu/${OUTPUTDIR}/${OUTPUTFILENAME}_${INDEX}.root --checksum ADLER32
if ["$?"!= "0" ]; then
    echo "Removing output file because gfal-copy crashed!"
    gfal-rm --verbose gsiftp://gftp.t2.ucsd.edu${OUTPUTDIR}/${OUTPUT}
fi
