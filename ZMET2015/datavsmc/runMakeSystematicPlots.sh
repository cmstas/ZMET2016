#! /bin/bash

root -b -q "makeSystematicPlots.cc+( \"bveto_SRB\", \"_noleptonid_noleptoniso\", \"225toinf\" )"
root -b -q "makeSystematicPlots.cc+( \"withb_SRB\", \"_noleptonid_noleptoniso\", \"225toinf\" )"

root -b -q "makeSystematicPlots.cc+( \"bveto_SRB\", \"_nofastsim\", \"225toinf\" )"
root -b -q "makeSystematicPlots.cc+( \"withb_SRB\", \"_nofastsim\", \"225toinf\" )"

root -b -q "makeSystematicPlots.cc+( \"bveto_SRB\", \"_noisrboost\", \"225toinf\" )"
root -b -q "makeSystematicPlots.cc+( \"withb_SRB\", \"_noisrboost\", \"225toinf\" )"

root -b -q "makeSystematicPlots.cc+( \"bveto_SRB\", \"_heavy_UP\", \"225toinf\" )"
root -b -q "makeSystematicPlots.cc+( \"withb_SRB\", \"_heavy_UP\", \"225toinf\" )"

root -b -q "makeSystematicPlots.cc+( \"bveto_SRB\", \"_light_UP\", \"225toinf\" )"
root -b -q "makeSystematicPlots.cc+( \"withb_SRB\", \"_light_UP\", \"225toinf\" )"

root -b -q "makeSystematicPlots.cc+( \"bveto_SRB\", \"_jes_up\", \"100to150\" )"
root -b -q "makeSystematicPlots.cc+( \"withb_SRB\", \"_jes_up\", \"100to150\" )"
root -b -q "makeSystematicPlots.cc+( \"bveto_SRB\", \"_jes_dn\", \"100to150\" )"
root -b -q "makeSystematicPlots.cc+( \"withb_SRB\", \"_jes_dn\", \"100to150\" )"

root -b -q "makeSystematicPlots.cc+( \"bveto_SRB\", \"_jes_up\", \"150to225\" )"
root -b -q "makeSystematicPlots.cc+( \"withb_SRB\", \"_jes_up\", \"150to225\" )"
root -b -q "makeSystematicPlots.cc+( \"bveto_SRB\", \"_jes_dn\", \"150to225\" )"
root -b -q "makeSystematicPlots.cc+( \"withb_SRB\", \"_jes_dn\", \"150to225\" )"

root -b -q "makeSystematicPlots.cc+( \"bveto_SRB\", \"_jes_up\", \"225to300\" )"
root -b -q "makeSystematicPlots.cc+( \"withb_SRB\", \"_jes_up\", \"225to300\" )"
root -b -q "makeSystematicPlots.cc+( \"bveto_SRB\", \"_jes_dn\", \"225to300\" )"
root -b -q "makeSystematicPlots.cc+( \"withb_SRB\", \"_jes_dn\", \"225to300\" )"

root -b -q "makeSystematicPlots.cc+( \"bveto_SRB\", \"_jes_up\", \"225toinf\" )"
root -b -q "makeSystematicPlots.cc+( \"withb_SRB\", \"_jes_up\", \"225toinf\" )"
root -b -q "makeSystematicPlots.cc+( \"bveto_SRB\", \"_jes_dn\", \"225toinf\" )"
root -b -q "makeSystematicPlots.cc+( \"withb_SRB\", \"_jes_dn\", \"225toinf\" )"

root -b -q "makeSystematicPlots.cc+( \"bveto_SRB\", \"_jes_up\", \"300toinf\" )"
root -b -q "makeSystematicPlots.cc+( \"withb_SRB\", \"_jes_up\", \"300toinf\" )"
root -b -q "makeSystematicPlots.cc+( \"bveto_SRB\", \"_jes_dn\", \"300toinf\" )"
root -b -q "makeSystematicPlots.cc+( \"withb_SRB\", \"_jes_dn\", \"300toinf\" )"
