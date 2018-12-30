#!/bin/bash

FILENAME=$1
TREENAME=${2:-"t"}

echo "    sweepRooting: \"$FILENAME\", \"$TREENAME\""
RESULT=`root -l -b -q sweeproot_macro.C+'("'$FILENAME'","'$TREENAME'")' | grep "result=" | sed s/result=//g`

#echo "RESULT=$RESULT"
    
if [ "$RESULT" == "0" ]; then 
    exit 0
else
    exit 1
fi
