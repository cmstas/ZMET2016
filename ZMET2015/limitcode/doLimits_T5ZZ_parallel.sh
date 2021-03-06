#!/bin/bash

function process_datacard ()
{

	datacardname=`basename $1`
	MASS1=$(echo "$datacardname" | awk '{split($0,a,"_"); print a[3]}')
	MASS2=$(echo "$datacardname" | awk '{split($0,a,"_"); print a[5]}')

	if [ $MASS1 -ge $MINMASS ]; then

		# if [ $MASS2 -gt $(($MASS1-150)) ]; then
		if [ -e ${INDIR}/datacard_mGluino_${MASS1}_mLSP_${MASS2}_.txt ]; then
			echo "Running command: nice -n 10 combine -M Asymptotic -n mGluino${MASS1}_mLSP${MASS2}_ ${INDIR}/datacard_mGluino_${MASS1}_mLSP_${MASS2}_.txt > log/limit_mGluino${MASS1}_mLSP${MASS2}.txt 2>&1"
			nice -n 10 combine -M Asymptotic -n mGluino${MASS1}_mLSP${MASS2}_ ${INDIR}/datacard_mGluino_${MASS1}_mLSP_${MASS2}_.txt  > log/limit_mGluino${MASS1}_mLSP${MASS2}.txt 2>&1
		fi
		
		if [ -e higgsCombinemGluino${MASS1}_mLSP${MASS2}_.Asymptotic.mH120.root ]; then
			mv higgsCombinemGluino${MASS1}_mLSP${MASS2}_.Asymptotic.mH120.root "limit_${MODEL}_${MASS1}_${MASS2}.root"
			echo "limit_${MODEL}_${MASS1}_${MASS2}.root" >> list_$MODEL.txt
		fi
	fi

}

MODEL=T5ZZ
#INDIR=/home/users/bhashemi/Projects/GIT/ZMETBabyLooper2017/SMSScans/DataCards/
#INDIR=/home/users/bhashemi/Projects/GIT/ZMETBabyLooper2017/SMSScans/DataCards/
INDIR=/home/users/olivito/zmet_dev/ZMET2016/ZMET2015/limitcode/datacards_T5ZZ_070317/
MINMASS=1000

#MODEL=TChiWZ
#INDIR=~/analysis/CMSSW_8_0_11/V08-11-00/ZMET2015/interpretations_ewk/datacards/
#MINMASS=100

OUTDIR=limits_${MODEL}_070317_paralleltest
OWD=`pwd`

declare -a cards=(`ls ${INDIR}/datacard_mG*.txt`)

# #need to combine cards from multiple signal regions if necessary
# for i in "${cards[@]}"
# do
#   if [ ! -e "$INDIR/datacard_all_$i.txt" ]; then
#     python combineCards.py "$INDIR/datacard_"*"_$i.txt" > "$INDIR/datacard_all_$i.txt"  
#   fi
# done

if [ ! -d "$OUTDIR" ]; then
  mkdir -p "$OUTDIR"
fi

if [ ! -d "$OUTDIR/log" ]; then
  mkdir -p "$OUTDIR/log"
fi

cp make_allRValues.C $OUTDIR
pushd $OUTDIR

rm -f list_$MODEL.txt

counter=0
PID_LIST=''
for i in "${cards[@]}"
do
    process_datacard $i & pid=$!
    PID_LIST+=" $pid";
    if [[ "$counter" -ge 10 ]]; then
	trap "kill $PID_LIST" SIGINT
	wait ${PID_LIST}
	counter=0
	PID_LIST=''
    else
	counter=$((counter+1))
    fi
done

root -b -q make_allRValues.C+\(\"$MODEL\",\"list_$MODEL.txt\"\)
cp r-values_$MODEL.root $OWD
popd
