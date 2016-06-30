Currently the master branch is meant to work with CMSSW 80X. Git branches exist to run over ntuples made with older versions of CMSSW.  

This repository is used to produce babies, and analyze babies for the Z+MET analysis. Follow these steps to check out and compile the baby maker:

source /code/osgcode/cmssoft/cmsset_default.sh  > /dev/null 2>&1  
export SCRAM_ARCH=slc6_amd64_gcc530  
cmsrel CMSSW_8_0_11  
cd CMSSW_8_0_11  
cmsenv  
ANALYSIS_TAG=V08-07-01  
git clone git@github.com:cmstas/ZMET2016.git $ANALYSIS_TAG  
cd $ANALYSIS_TAG  
git checkout $ANALYSIS_TAG  
git clone git@github.com:cmstas/Software.git  
cd Software/  
git checkout root6  
cd ../  
git clone git@github.com:cmstas/CORE.git  
cd dilepbabymaker  
make -j5  

Once this is done, run the test command  
./dotest.sh  

This should make a baby ntuple in your home directory.  


Useful commands:

Tagging your code

git tag -a <version> -m 'add a message'

git push --tags

