import ROOT as r
import sys,os

infile = sys.argv[1]

f = r.TFile(infile)
f.Map()

