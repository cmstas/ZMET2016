#! /bin/bash

# root -b -q "doAll.C(\"2jets_inclusive\")"
root -b -q "doAll.C(\"2jets_inclusive\", \"ht\")"
# root -b -q "drawReweightingHists.cc+(\"2jets_inclusive\")"

# root -b -q "doAll.C(\"3jets_inclusive\")" &

# root -b -q "doAll.C(\"SRA_withb\")" &
# root -b -q "doAll.C(\"SRA_bveto\")" &
# root -b -q "doAll.C(\"SRB_withb\")" &
# root -b -q "doAll.C(\"SRB_bveto\")" &

# root -b -q "drawReweightingHists.cc+(\"3jets_inclusive\")" &
# root -b -q "drawReweightingHists.cc+(\"SRA_bveto\")" &
# root -b -q "drawReweightingHists.cc+(\"SRA_withb\")" &
# root -b -q "drawReweightingHists.cc+(\"SRB_withb\")" &
# root -b -q "drawReweightingHists.cc+(\"SRB_bveto\")" &
