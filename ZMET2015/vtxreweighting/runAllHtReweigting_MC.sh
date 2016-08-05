#! /bin/bash

root -b -q "getReweightHTHist_MC.cc+(\"2jets_inclusive\")"
root -b -q "getReweightHTHist_MC.cc+(\"SR_EWK\")"

root -b -q "getReweightHTHist_MC.cc+(\"SRB_bveto\")"
root -b -q "getReweightHTHist_MC.cc+(\"SRB_withb\")"
root -b -q "getReweightHTHist_MC.cc+(\"SRA_bveto\")"
root -b -q "getReweightHTHist_MC.cc+(\"SRA_withb\")"
root -b -q "getReweightHTHist_MC.cc+(\"SR_ATLAS\")"

# root -b -q "getReweightHTHist_MC.cc+(\"central_twojets\")"
# root -b -q "getReweightHTHist_MC.cc+(\"central_withb_twojets\")"
# root -b -q "getReweightHTHist_MC.cc+(\"central_with2_twojets\")"
# root -b -q "getReweightHTHist_MC.cc+(\"central_3jets_inclusive\")"
# root -b -q "getReweightHTHist_MC.cc+(\"central_withb_3jets_inclusive\")"
# root -b -q "getReweightHTHist_MC.cc+(\"central_with2_3jets_inclusive\")"

# root -b -q "getReweightHTHist_MC.cc+(\"forward_twojets\")"
# root -b -q "getReweightHTHist_MC.cc+(\"forward_withb_twojets\")"
# root -b -q "getReweightHTHist_MC.cc+(\"forward_with2_twojets\")"
# root -b -q "getReweightHTHist_MC.cc+(\"forward_3jets_inclusive\")"
# root -b -q "getReweightHTHist_MC.cc+(\"forward_withb_3jets_inclusive\")"
# root -b -q "getReweightHTHist_MC.cc+(\"forward_with2_3jets_inclusive\")"

# root -b -q "getReweightHTHist_MC.cc+(\"rawMET_SRA_tailstudy\")"
# root -b -q "getReweightHTHist_MC.cc+(\"rawMET_SRB_tailstudy\")"
# root -b -q "getReweightHTHist_MC.cc+(\"rawMET_2jets_inclusive_tailstudy\")"
