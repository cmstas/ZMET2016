#!/bin/bash

function run () {
    echo root -b -q mergeHadoopFiles.C\(\"${HADOOPDIR}/${TAG}_$1/\",\"${OUTPUTDIR}/$1.root\"\)
    nohup nice -n 19 root -b -q mergeHadoopFiles.C\(\"${HADOOPDIR}/${TAG}_$1/\",\"${OUTPUTDIR}/$1.root\"\) >& merge_logs_${TAG}/log_merge_$1.txt &
}

source ../../ZMET2015/settings.sh 

TAG=${analysis_version}

HADOOPDIR=/hadoop/cms/store/user/${USER}/uaf8/dilepbabies/
OUTPUTDIR=/nfs-7/userdata/ZMEToutput/output/ZMETbabies/$TAG/

if [ ! -d "$OUTPUTDIR" ]; then
	mkdir -p $OUTPUTDIR
	chmod -R a+wrx $OUTPUTDIR
fi

if [ ! -d "merge_logs_${TAG}" ]; then
	mkdir merge_logs_${TAG}
fi
# all the data for the MET study
# run data_2015C25ns16Dec2015_ee
# run data_2015D25ns16Dec2015_ee
# run data_2015C25ns16Dec2015_mm
# run data_2015D25ns16Dec2015_mm
# run data_2015C25ns16Dec2015_me
# run data_2015D25ns16Dec2015_me

# ######################################################################################
# # all the MC for the MET study
# # main samples
# ######################################################################################

# # #####==============================
# # # DYJetsToLL
# # #####==============================
# run DYJetsToLL_M-50_amcNLO_v1
# run DYJetsToLL_M-10to50_amcNLO_v1

# # #####==============================
# # # TTbar
# # #####==============================
# run ttTo2L2Nu_powheg

# #####==============================
# # ZZ
# #####==============================
# run ZZTo2L2Nu_13TeV_powheg_pythia8
# run ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8
# run ZZTo4L_13TeV_powheg_pythia8

# #####==============================
# # WZ
# #####==============================
# run WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8

# #####==============================
# # WW
# #####==============================
# run WWTo2L2Nu_13TeV-powheg

# #####==============================
# # Single Top
# #####==============================
# run ST_tW_antitop_5f_inclusiveDecays_13TeV
# run ST_tW_top_5f_inclusiveDecays_13TeV

#####==============================
# TTV
#####==============================
run TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8
run TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8
run TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8
run TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8
run TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8
run ttHJetToNonbb_M125_13TeV

# #####==============================
# # VVV
# #####==============================
# run WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8
# run WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8
# run WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8
