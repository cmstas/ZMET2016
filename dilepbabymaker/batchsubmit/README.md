How To:  

modify writeAllConfig.sh to run over the samples you want, then run the script to create the jobs.  
./writeAllConfig.sh  

Once these are made, run the submitAll.sh command.  
./submitAll.sh  

you can monitor the jobs by using condor commands, and the most useful will be  
`condor_q <username> `

`<username>` should be replaced by your username.  

Once all the jobs complete, check the output for any corrupted files  

```bash
git clone git@github.com:cmstas/NtupleTools.git 
cd NtupleTools/condorMergingTools/libC  
make  
./sweepRoot -b -o "t" /hadoop/cms/store/user/${USER}/<BABYDIR>/*.root
```

You should remove any files that have been marked as bad before you continue.

Then check the status and create resubmission configs for the ones that failed with the checkAllConfig.sh script. Each job outputs its condor submission command into the directory specified in writeAllConfig, `configs_<VERSION_TAG>` by default at the time of writing. checkAllConfig reads these commands and checks to see which have their output files returned then prints a list of files which are missing. 

You need to provide the log directory that gets created by the writeAllConfig.sh script.  Using the default directory listed above that mean
`checkAllConfig.sh configs_<VERSION_TAG> `

or in general 

`checkAllConfig.sh <condor_cmd_files_dir> `

This will create resubmit configs in the `<condor_cmd_files_dir>` directory, they will be tagged with a `_resubmit.cmd` and these can be run using the command  
`condor_submit <path_to_resubmit_config>  `


Merging  

When all the jobs have run successfully, you will want to merge the output to make accessing it faster. This can be done with the mergeHadoopFiles.sh script.  

When you run this script, run no more than 4 merge jobs at a time. They will run in parallel, so comment out the samples you don't want to run before executing the command. This is really important, if too many jobs are run, you can bring down the disk you are merging to!

##################################################################################
#                                                                                #
#   Instructions for running ZMET baby making within the AutoTwopler framework   #
#                                                                                #
##################################################################################

1. Need to checkout NtupleTools inside of ZMET2016
``` bash
git clone git@github.com:cmstas/NtupleTools.git
```

2. Run setup script (in NtupleTools/AutoTwopler) - this needs to be done in every session
``` bash
. setup.sh
```

3. Prepare input files for job submission (in ZMET2016/dilepbabymaker/batchsubmit)
``` bash
. make_job_inputs.sh
```

4. Job submission

User interaction primarily happens with zmet.py and ducks.py, both inside of ZMET2016/dilepbabymaker/batchsubmit.
The file zmet.py should only need to be touched rarely.  It contains dataset --> shortname mapping for samples and default zmet configuration parameters.
Most interaction is through ducks.py, which is also where parameters from zmet.py can (and should) be overridden, like the ntuple tag.

5. Launching jobs
``` bash
python ducks.py
```
