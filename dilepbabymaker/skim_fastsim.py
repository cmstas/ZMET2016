from __future__ import print_function
import ROOT as r
import numpy as np
import sys,os

#skim baseline selection

baseline_sel = "(njets >=2 && nlep >= 2)"

#fastsim mass points selection
gluino_mass = sys.argv[2]
lsp_mass = sys.argv[3]

mass_sel = "(mass_gluino == {} && mass_LSP == {})".format(gluino_mass,lsp_mass)

inDirName = sys.argv[1]
outfileName = "skim_mG_{}_mLSP_{}.root".format(gluino_mass,lsp_mass)

ch = r.TChain("t")
ch.Add(os.path.join(inDirName,"*.root"))

print("Chain has {} entries".format(ch.GetEntries()))

outFile = r.TFile(outfileName,"RECREATE")
outTree = ch.CopyTree(mass_sel + "&&" + mass_sel)
print("Output tree has {} entries".format(outTree.GetEntries()))
outTree.Write()
outFile.Close()
