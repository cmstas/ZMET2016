#!/bin/bash

function run () {
    echo root -b -q mergeHadoopFiles.C\(\"${HADOOPDIR}/${TAG}_$1/\",\"${OUTPUTDIR}/$1.root\"\)
    nohup nice -n 19 root -b -q mergeHadoopFiles.C\(\"${HADOOPDIR}/${TAG}_$1/\",\"${OUTPUTDIR}/$1.root\"\) >& merge_logs_${TAG}/log_merge_$1.txt &
}

source ../../ZMET2015/settings.sh 

TAG=${analysis_version}

HADOOPDIR=/hadoop/cms/store/user/${USER}/dilepbabies/
OUTPUTDIR=/nfs-7/userdata/ZMEToutput/output/ZMETbabies/$TAG/

mkdir -p $OUTPUTDIR
chmod -R a+wrx $OUTPUTDIR

if [ ! -d "merge_logs_${TAG}" ]; then
  mkdir merge_logs_${TAG}
fi

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
run zz2l2nu_25ns_powp8 
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

