#/bin/bash

condor_dir=$1

for condorfile in $condor_dir/*; do
    echo "RUNNING " $condorfile
    ./resubmitConfig.sh $condorfile
done
