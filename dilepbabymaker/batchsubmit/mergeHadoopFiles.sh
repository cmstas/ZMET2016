#!/bin/bash

function run () {
    echo root -b -q mergeHadoopFiles.C\(\"${HADOOPDIR}/${TAG}_$1/\",\"${OUTPUTDIR}/$1.root\"\)
    nohup nice -n 19 root -b -q mergeHadoopFiles.C\(\"${HADOOPDIR}/${TAG}_$1/\",\"${OUTPUTDIR}/$1.root\"\) >& merge_logs_${TAG}/log_merge_$1.txt &
}

source ../../ZMET2015/settings.sh 

TAG=${analysis_version}

HADOOPDIR=/hadoop/cms/store/user/${USER}/uaf8/dilepbabies/
OUTPUTDIR=/nfs-7/userdata/ZMEToutput/output/bobakBabies/$TAG/

if [ ! -d "$OUTPUTDIR" ]; then
	mkdir -p $OUTPUTDIR
	chmod -R a+wrx $OUTPUTDIR
fi

if [ ! -d "merge_logs_${TAG}" ]; then
	mkdir merge_logs_${TAG}
fi


# 2016 data
run data_2016B_Prompt_ee_v1
run data_2016B_Prompt_mm_v1
run data_2016B_Prompt_ee_v2
#run data_2016B_Prompt_mm_v2
#run data_2016B_Prompt_em_v1
#run data_2016B_Prompt_em_v2
run data_2016B_Prompt_ph_v1
#run data_2016B_Prompt_ph_v2

# # 2016 MC

# # DY
# run dy_m1050_amcnlo
# run dy_m50_amcnlo

# # ttbar
# run ttbar_dilep_mgmlm

# # single top
# run sttw_antitop_powheg
# run sttw_top_powheg

# # VV
# run ww_2l2nu_powheg
# run wz_2l2q_amcnlo
# run wz_3lnu_powheg
# run zz_2l2nu_powheg
# run zz_2l2q_amcnlo

# # ttV
# run ttw_incl_mgmlm
# run ttz_incl_mgmlm

# # VVV
# run www_incl_amcnlo
# run wwz_incl_amcnlo
# run wzz_incl_amcnlo
# run zzz_incl_mgmlm

# # samples for closure

# # 2016 GJets
#run Gjets_mgmlm_HT40100
#run Gjets_mgmlm_HT100200
#run Gjets_mgmlm_HT200400
#run Gjets_mgmlm_HT400600
#run Gjets_mgmlm_HT600Inf

# # 2016 ZJets
# miniAODv1
#run zjets_m50_mgmlm
#run zjets_m50_mgmlm_HT100200
#run zjets_m50_mgmlm_HT200400
#run zjets_m50_mgmlm_HT400600
# miniAOD v2
#run zjets_miniAODv2_m50_mgmlm_HT600Inf
#run zjets_miniAODv2_m50_mgmlm_HT600Inf_ext1

# # will use this for first closure studies
# run dy_m1050_mgmlm_ext1

# will do these later. Focus on the main samples for now
# /DYJetsToLL_M-5to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3-v1
# /DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext1-v1

# # gjets
# run gjetsht100_dr0p4_mgmlm
# run gjetsht400_dr0p4_mgmlm
# run gjetsht40_dr0p4_mgmlm
# run gjetsht600_dr0p4_mgmlm
# run gjetsht100_mgmlm



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

# #####==============================
# # TTV
# #####==============================
# run TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8
# run TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8
# run TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8
# run TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8
# run TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8
# run ttHJetToNonbb_M125_13TeV

# #####==============================
# # VVV
# #####==============================
# run WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8
# run WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8
# run WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8
