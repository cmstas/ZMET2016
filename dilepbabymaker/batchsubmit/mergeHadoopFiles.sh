#!/bin/bash

function run () {
    echo root -b -q mergeHadoopFiles.C\(\"${HADOOPDIR}/${TAG}_$1/\",\"${OUTPUTDIR}/$1.root\"\)
    nohup nice -n 19 root -b -q mergeHadoopFiles.C\(\"${HADOOPDIR}/${TAG}_$1/\",\"${OUTPUTDIR}/$1.root\"\) >& merge_logs_${TAG}/log_merge_$1.txt &
}

source ../../ZMET2015/settings.sh 

TAG=${analysis_version}

HADOOPDIR=/hadoop/cms/store/user/${USER}/dilepbabies/
OUTPUTDIR=/nfs-7/userdata/ZMEToutput2016/output/ZMETbabies/$TAG/

mkdir -p $OUTPUTDIR
chmod -R a+wrx $OUTPUTDIR

if [ ! -d "merge_logs_${TAG}" ]; then
  mkdir merge_logs_${TAG}
fi

# Bobak's Names
# Data
run data_2015C25ns16Dec2015_ee
run data_2015D25ns16Dec2015_ee
run data_2015C25ns16Dec2015_mm
run data_2015D25ns16Dec2015_mm
run data_2015C25ns16Dec2015_me
run data_2015D25ns16Dec2015_me
# DYToLL
#run DYJetsToLL_M-50_madgraph
#run DYJetsToLL_M-50_amcNLO_ext4-v1
run DYJetsToLL_M-50_amcNLO_v1
#run DYJetsToLL_M-50_amcNLO_HCALdebug-v1
#run DYJetsToLL_M-10to50_amcNLO_ext3-v1
#run DYJetsToLL_M-10to50_amcNLO_ext1-v1
#run DYJetsToLL_M-10to50_amcNLO_v1
# TTBarS
#run ttTo2L2Nu_powheg
run ttjets_2L-madgraph
#run 4T_amcNLO
#run ttjets_pythia
# ZZ
#run ZZTo2L2Nu_13TeV_powheg_pythia8
#run ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8
#run ZZTo4L_13TeV_powheg_pythia8
# WZ
#run WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8
# WW 
#run WWTo2L2Nu_13TeV-powheg
# Single Top
#run ST_tW_antitop_5f_inclusiveDecays_13TeV
#run ST_tW_top_5f_inclusiveDecays_13TeV
# TTV
#run TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8
#run TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8
#run TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8
#run TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8
#run TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8
#run ttHJetToNonbb_M125_13TeV
# VVV
#run WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8
#run WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8
#run WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8


# all the data for dec
# run data_2015C25ns05Oct2015_mm
# run data_2015C25ns05Oct2015_em
# run data_2015C25ns05Oct2015_ph
# run data_2015C25ns05Oct2015_ee

# run data_2015D25nsPromptv4_ee
# run data_2015D25nsPromptv4_ph
# run data_2015D25nsPromptv4_mm
# run data_2015D25nsPromptv4_em

# run data_2015D25ns05Oct2015_ee
# run data_2015D25ns05Oct2015_mm
# run data_2015D25ns05Oct2015_em
# run data_2015D25ns05Oct2015_ph

# run dyjetsll_25ns_m50nlo  
# run dyjetsll_25ns_m1050nlo
# run tt2lnu_25ns_php8
# run wz3lnu_25ns_powp8  	
# run zz4l_25ns_php8  		
# run ww2l2nu_25ns_powp8   
# run zz2l2nu_25ns_powp8 
# run zzz_25ns_nlo  
# run wwz_25ns_nlo  
# run wzz_25ns_nlo  
# run sttwatop_25ns_powp8  
# run sttwtop_25ns_powp8   

# run ttg_25ns_nlo  	   
# run ttzllnunu_25ns_nlo 
# run ttzqq_25ns_nlo     
# run wz2l2q_25ns_nlo  
# run zz2l2q_25ns_nlo  

# run ttwlnu_25ns_nlo
# run ttw2q_25ns_nlo 
# run vhnonbb_25ns_nlo 
# run vv2l2nu_25ns_nlo 
# run zjetsll_25ns_m50mlm  

# run zjetsllht100_25ns_m50mlm  
# run zjetsllht200_25ns_m50mlm  
# run zjetsllht400_25ns_m50mlm  
# run zjetsllht600_25ns_m50mlm  

# run gjets_25ns_ht40mlm  
# run gjets_25ns_ht100mlm  
# run gjets_25ns_ht200mlm  
# run gjets_25ns_ht400mlm  
# run gjets_25ns_ht600mlm  

