#!/bin/bash

#Needs to be run from CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/scripts/

# cmsenv

INDIR=~/analysis/CMSSW_8_0_11/V08-11-00/ZMET2015/interpretations/datacards/
# OUTDIR=scantest

declare -a samples=(`ls ${INDIR}datacard*.txt`)

# #need to combine cards from multiple signal regions if necessary
# for i in "${samples[@]}"
# do
#   if [ ! -e "$INDIR/datacard_all_$i.txt" ]; then
#     python combineCards.py "$INDIR/datacard_"*"_$i.txt" > "$INDIR/datacard_all_$i.txt"  
#   fi
# done

# if [ ! -d "$OUTDIR" ]; then
#   mkdir -p "$OUTDIR"
#   mkdir -p "$OUTDIR/log"
# fi

# pushd .
# cp make_rValues.C "$OUTDIR"
# cp makeLimitTable.C "$OUTDIR"
# cd "$OUTDIR"

for i in "${samples[@]}"
do

	datacardname=`basename $i`

	# MODEL=$(echo "$datacardname"|awk -F- 'split($1,a,"_")&&$0=a[1]') #because awk
	# echo $MODEL

	MODEL=T5ZZ
	
	MASS1=$(echo "$datacardname"|awk -F- 'split($1,a,"_")&&$0=a[3]')
	MASS2=$(echo "$datacardname"|awk -F- 'split($1,a,"_")&&$0=a[5]')
	# echo $MASS1
	# echo $MASS2

	if [ $MASS1 -gt "950" ]; then
		
		# if [ $MASS2 -gt $(($MASS1-150)) ]; then
		if [ -e ${INDIR}datacard_mGluino_${MASS1}_mLSP_${MASS2}_.txt ]; then
			echo "Running command: combine -M Asymptotic -n mGluino${MASS1}_mLSP${MASS2}_ ${INDIR}datacard_mGluino_${MASS1}_mLSP_${MASS2}_.txt > log/limit_mGluino${MASS1}_mLSP${MASS2}.txt 2>&1"
			combine -M Asymptotic -n mGluino${MASS1}_mLSP${MASS2}_ ${INDIR}datacard_mGluino_${MASS1}_mLSP_${MASS2}_.txt  > log/limit_mGluino${MASS1}_mLSP${MASS2}.txt 2>&1
		fi
		
		if [ -e higgsCombinemGluino${MASS1}_mLSP${MASS2}_.Asymptotic.mH120.root ]; then
			mv higgsCombinemGluino${MASS1}_mLSP${MASS2}_.Asymptotic.mH120.root "limit_${MODEL}_${MASS1}_${MASS2}.root"
		fi

		if [ -e limit_${MODEL}_${MASS1}_${MASS2}.root ]; then
			root -b -q "make_rValues.C(\"$MODEL\",$MASS1,$MASS2)" > /dev/null 2>&1
		fi
		# fi
	fi
done

# root -b -q makeLimitTable.C > table.txt 2>&1

# rm make_rValues.C
# rm makeLimitTable.C
# rm roostats*
# popd



