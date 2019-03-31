import json
import sys

jsonName = sys.argv[1]
sntName =jsonName[:-4]+"_snt.txt"
sntFile = open(sntName,"w")
goodRuns = json.load(open(jsonName))
for run,lumis in goodRuns.items():
    for lumiblock in lumis:
        sntFile.write("{} {} {}\n".format(run,lumiblock[0],lumiblock[1]))
