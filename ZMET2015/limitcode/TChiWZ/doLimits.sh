#!/bin/bash

#Needs to be run from CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/scripts/

# cmsenv

INDIR=~/analysis/CMSSW_8_0_11/V08-11-00/ZMET2015/interpretations_ewk/datacards/
# OUTDIR=scantest

declare -a samples=(`ls ${INDIR}datacard*.txt`)

doSignificance=true

for i in "${samples[@]}"
do

	datacardname=`basename $i`

	# MODEL=$(echo "$datacardname"|awk -F- 'split($1,a,"_")&&$0=a[1]') #because awk
	# echo $MODEL

	MODEL=TChiWZ
	
	MASS1=$(echo "$datacardname"|awk -F- 'split($1,a,"_")&&$0=a[3]')
	MASS2=$(echo "$datacardname"|awk -F- 'split($1,a,"_")&&$0=a[5]')
	
	# echo $MASS1
	# echo $MASS2
	
	if [ -z $MASS2 ]; then
		MASS2='0';
	fi

	if [ $MASS1 -gt $MASS2 ]; then
		# if [ $MASS1 -gt 400 ]; then
		# if [ $MASS1 -gt $(($MASS1-150)) ]; then
		if [ -e ${INDIR}datacard_mGluino_${MASS1}_mLSP_${MASS2}_.txt ]; then
			if [ "$doSignificance" = true ]; then
				echo "Running command: combine -M ProfileLikelihood --uncapped 1 --significance -n mGluino${MASS1}_mLSP${MASS2}_ ${INDIR}datacard_mGluino_${MASS1}_mLSP_${MASS2}_.txt > log/significance_mGluino${MASS1}_mLSP${MASS2}.txt 2>&1"
				combine -M ProfileLikelihood --uncapped 1 --significance -n mGluino${MASS1}_mLSP${MASS2}_ ${INDIR}datacard_mGluino_${MASS1}_mLSP_${MASS2}_.txt > log/significance_mGluino${MASS1}_mLSP${MASS2}.txt 2>&1
			else
				echo "Running command: combine -M Asymptotic -n mGluino${MASS1}_mLSP${MASS2}_ ${INDIR}datacard_mGluino_${MASS1}_mLSP_${MASS2}_.txt > log/limit_mGluino${MASS1}_mLSP${MASS2}.txt 2>&1"
				# combine -M Asymptotic -n mGluino${MASS1}_mLSP${MASS2}_ ${INDIR}datacard_mGluino_${MASS1}_mLSP_${MASS2}_.txt  > log/limit_mGluino${MASS1}_mLSP${MASS2}.txt 2>&1
			fi
		fi
		
		if [ -e higgsCombinemGluino${MASS1}_mLSP${MASS2}_.ProfileLikelihood.mH120.root ]; then
			mv higgsCombinemGluino${MASS1}_mLSP${MASS2}_.ProfileLikelihood.mH120.root "significance_${MODEL}_${MASS1}_${MASS2}.root"
		fi

		if [ -e higgsCombinemGluino${MASS1}_mLSP${MASS2}_.Asymptotic.mH120.root ]; then
			mv higgsCombinemGluino${MASS1}_mLSP${MASS2}_.Asymptotic.mH120.root "limit_${MODEL}_${MASS1}_${MASS2}.root"
		fi

		if [ -e limit_${MODEL}_${MASS1}_${MASS2}.root ]; then
			if [ "$doSignificance" = true ]; then
				echo root -b -q "make_rValues.C(\"$MODEL\",$MASS1,$MASS2)" > /dev/null 2>&1
			else
				root -b -q "make_rValues.C(\"$MODEL\",$MASS1,$MASS2)" > /dev/null 2>&1
			fi
		fi
	fi
done

# root -b -q makeLimitTable.C > table.txt 2>&1

# rm make_rValues.C
# rm makeLimitTable.C
# rm roostats*
# popd



