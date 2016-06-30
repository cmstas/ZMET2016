#!/bin/bash

DATADIR=$1
COPYDIRBASE=$2

while  ! voms-proxy-info -exist
do echo "No Proxy found issuing \"voms-proxy-init -voms cms\""
   voms-proxy-init -hours 168 -voms cms
done

UNIVERSE="grid"
#UNIVERSE="vanilla"
EXE="wrapper_80X.sh"
INPUT="wrapper_80X.sh, job_input/input.tar.gz"
# can add other US sites here if desired
SITE="T2_US_UCSD"
PROXY=$(voms-proxy-info -path)
USERNAME=$(whoami)

othersites="T2_US_UCSD"

LOGDIR="/data/tmp/$USER/$COPYDIRBASE/submit_logs"
OUTDIR="/data/tmp/$USER/$COPYDIRBASE/job_logs"
LOG="${LOGDIR}/condor_`date "+%m_%d_%Y"`.log"
OUT="${OUTDIR}/1e.\$(Cluster).\$(Process).out"
ERR="${OUTDIR}/1e.\$(Cluster).\$(Process).err"

if [ ! -d "${LOGDIR}" ]; then
    echo "[writeConfig] creating log directory " ${LOGDIR}
    mkdir -p ${LOGDIR}
fi

if [ ! -d "${OUTDIR}" ]; then
    echo "[writeConfig] creating job output log directory " ${OUT}
    mkdir -p ${OUT}
fi

#
# prepare input sandbox
#

DIR=$PWD
rm ${DIR}/job_input/input.*
#printenv | grep -v PS1 | grep -v printenv | awk '{print "export "$1}' > ${DIR}/job_input/setupenv.sh
tar -hcf ${DIR}/job_input/input.tar job_input/*
gzip ${DIR}/job_input/input.tar
cd ${DIR}


COPYDIR=/hadoop/cms/store/user/${USERNAME}/uaf8/dilepbabies/${COPYDIRBASE}
echo "[writeConfig] running on dataset ${DATADIR}"
echo "[writeConfig] copying output to ${COPYDIR}"

if [ ! -d "${COPYDIR}" ]; then
    echo "[writeConfig] creating job output directory " ${COPYDIR}
    mkdir -p ${COPYDIR}
fi

#
# write configuration
#
   
#Grid_Resource=gt2 osg-gw-6.t2.ucsd.edu:2119/jobmanager-condor
Grid_Resource="condor cmssubmit-r1.t2.ucsd.edu glidein-collector.t2.ucsd.edu"
echo "
Universe=${UNIVERSE}
Grid_Resource=${Grid_Resource}
when_to_transfer_output = ON_EXIT
#the actual executable to run is not transfered by its name.
#In fact, some sites may do weird things like renaming it and such.
transfer_input_files=${INPUT}
+DESIRED_Sites=\"${SITE}\"
+remote_DESIRED_Sites=\"${othersites}\" 
+Owner = undefined
log=${LOG}
output=${OUT}
error =${ERR}
notification=Never
x509userproxy=${PROXY}
" > condor_${COPYDIRBASE##*/}.cmd

    #
    # now set the rest of the arguments 
    # for each job
    # 

    for FILE in `ls ${DATADIR}/*.root`; do
        echo "
executable=${EXE}
transfer_executable=True
arguments=`echo ${FILE##*/} | sed 's/\.root//g'` ${FILE} ${COPYDIR}
queue
" >> condor_${COPYDIRBASE##*/}.cmd
    done

echo "[writeConfig] wrote condor_${COPYDIRBASE##*/}.cmd" 
