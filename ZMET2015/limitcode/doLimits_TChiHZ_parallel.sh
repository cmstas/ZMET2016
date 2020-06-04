#!/bin/bash

function process_datacard ()
{

	datacardname=`basename $1`
	MASS1=$(echo "$datacardname" | awk '{split($0,a,"_"); print a[4]}')

	if [ $MASS1 -ge $MINMASS ]; then

		if [ -e ${INDIR}/datacard_all_mChi_${MASS1}_.txt ]; then
			echo "Running command: nice -n 10 combine -M Asymptotic -n mChi${MASS1}_ ${INDIR}/datacard_all_mChi_${MASS1}_.txt > log/limit_mChi${MASS1}.txt 2>&1"
			nice -n 10 combine -M Asymptotic -n mChi${MASS1}_ ${INDIR}/datacard_all_mChi_${MASS1}_.txt  > log/limit_mChi${MASS1}.txt 2>&1
		fi

		if [ -e higgsCombinemChi${MASS1}_.Asymptotic.mH120.root ]; then
			mv higgsCombinemChi${MASS1}_.Asymptotic.mH120.root "limit_${MODEL}_${MASS1}.root"
			echo "limit_${MODEL}_${MASS1}.root" >> list_$MODEL.txt
		fi
	fi

}

MODEL=TChiHZ
INDIR=/home/users/bsathian/ZMet/ZMETBabyLooper2017/SMSScans/DataCards/TChiWZ/
MINMASS=100

OUTDIR=limits_${MODEL}_070317_paralleltest
OWD=`pwd`

declare -a cards=(`ls ${INDIR}/datacard_*mC*.txt`)

# #need to combine cards from multiple signal regions if necessary
 for i in "${cards[@]}"
 do
   mG=$(echo "$i" | awk '{split($0,a,"_"); print a[3]"_"a[4]"_"}')
   if [ ! -e "$INDIR/datacard_all_$mG.txt" ]; then
     python combineCards.py "$INDIR/datacard_"*"_$mG.txt" > "$INDIR/datacard_all_$mG.txt"
   fi
 done

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
    if [[ "$counter" -ge 7 ]]; then
	trap "kill $PID_LIST" SIGINT
	wait ${PID_LIST}
	counter=0
	PID_LIST=''
    else
	counter=$((counter+1))
    fi
done

# root -b -q make_allRValues.C+\(\"$MODEL\",\"list_$MODEL.txt\"\)
# cp r-values_$MODEL.root $OWD
popd
