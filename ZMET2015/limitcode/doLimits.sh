#!/bin/bash

# MODEL=T5ZZ
# INDIR=~/analysis/CMSSW_8_0_11/V08-11-00/ZMET2015/interpretations/datacards/
# MINMASS=950

MODEL=TChiWZ
INDIR=~/analysis/CMSSW_8_0_11/V08-11-00/ZMET2015/interpretations_ewk/datacards/
MINMASS=100

OUTDIR=limits_$MODEL

declare -a cards=(`ls ${INDIR}/datacard*.txt`)

# #need to combine cards from multiple signal regions if necessary
# for i in "${cards[@]}"
# do
#   if [ ! -e "$INDIR/datacard_all_$i.txt" ]; then
#     python combineCards.py "$INDIR/datacard_"*"_$i.txt" > "$INDIR/datacard_all_$i.txt"  
#   fi
# done

if [ ! -d "$OUTDIR" ]; then
  mkdir -p "$OUTDIR"
  mkdir -p "$OUTDIR/log"
fi

cp make_allRValues.C $OUTDIR
pushd $OUTDIR

rm -f list_$MODEL.txt

for i in "${cards[@]}"
do

	datacardname=`basename $i`
	MASS1=$(echo "$datacardname" | awk '{split($0,a,"_"); print a[3]}')
	MASS2=$(echo "$datacardname" | awk '{split($0,a,"_"); print a[5]}')

	if [ $MASS1 -ge $MINMASS ]; then
		
		# if [ $MASS2 -gt $(($MASS1-150)) ]; then
		if [ -e ${INDIR}datacard_mGluino_${MASS1}_mLSP_${MASS2}_.txt ]; then
			echo "Running command: combine -M Asymptotic -n mGluino${MASS1}_mLSP${MASS2}_ ${INDIR}datacard_mGluino_${MASS1}_mLSP_${MASS2}_.txt > log/limit_mGluino${MASS1}_mLSP${MASS2}.txt 2>&1"
			combine -M Asymptotic -n mGluino${MASS1}_mLSP${MASS2}_ ${INDIR}datacard_mGluino_${MASS1}_mLSP_${MASS2}_.txt  > log/limit_mGluino${MASS1}_mLSP${MASS2}.txt 2>&1
		fi
		
		if [ -e higgsCombinemGluino${MASS1}_mLSP${MASS2}_.Asymptotic.mH120.root ]; then
			mv higgsCombinemGluino${MASS1}_mLSP${MASS2}_.Asymptotic.mH120.root "limit_${MODEL}_${MASS1}_${MASS2}.root"
			echo "limit_${MODEL}_${MASS1}_${MASS2}.root" >> list_$MODEL.txt
		fi
	fi
done

root -b -q make_allRValues.C+\(\"$MODEL\",\"list_$MODEL.txt\"\)
popd




