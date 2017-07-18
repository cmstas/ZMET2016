import sys
#sys.path.insert(0,"/home/users/olivito/zmet_dev/ZMET2016/NtupleTools/AutoTwopler")
sys.path.insert(0,"/home/users/bhashemi/Projects/GIT/ZMET2016/NtupleTools/AutoTwopler")
import run
import params as p
import zmet as zmet

# set tag
zmet.tag = "V08-22-18"

# make instructions
instructions = []

##
## make instructions by class of sample
##
#samples_types = ["backgrounds", "data", "scans"]
#samples_types = ["backgrounds", "data"]
samples_types = ["data"]
for stype in samples_types:
    for ds in zmet.d_ds2name[stype].keys():
        instructions.append({"executable": zmet.executable, "package": zmet.package, "analysis": "ZMET", "dataset": ds, "baby_tag": zmet.tag, "type": "BABY", "extra": [-1, "output.root,skim.root"]})

##
## make instructions by sample shortname
##
#todo = "wjets_ht1200_mgmlm_nonext ".strip().split()
#instructions = [inst for inst in instructions if zmet.dataset_to_shortname(inst["dataset"]) in todo]

#print instructions
#sys.exit()

p.dataset_to_shortname = zmet.dataset_to_shortname
p.dashboard_name = zmet.dashboard_name
p.sweepRoot_scripts = zmet.sweepRoot_scripts
p.merging_scripts = zmet.merging_scripts
p.baby_merged_dir = zmet.baby_merged_dir
p.merge_babies_on_condor = zmet.merge_babies_on_condor
p.exit_when_done = True

run.main(instructions=instructions, params=p)

# instructions = [ 
#         {
#             "dataset": "/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
#             "type": "BABY",
#             "extra": "",
#             "baby_tag": "v0.01",
#             "analysis": "ZMET",
#             "package": ss.package,
#             "executable": ss.executable,
#             }
#         ]

# p.merging_scripts = ["frank/merge.sh", "frank/merge.C"]
# p.dashboard_name = "AutoTwopler_test"
# p.merge_babies_on_condor = True
# run.main(instructions=instructions, params=p, do_one_iteration=True)
