#! /bin/bash

# root -b -q "compareMET.cc+(\"_SRB_withb\", 12.9, \"ht_highbin\" )"
# root -b -q "compareMET.cc+(\"_SRB_withb\", 12.9, \"met\" )"
# root -b -q "compareMET.cc+(\"_SRB_withb\", 12.9, \"ptg\" )"
# root -b -q "compareMET.cc+(\"_SRB_withb\", 12.9, \"njets\" )"
# root -b -q "compareMET.cc+(\"_SRB_withb\", 12.9, \"gen_ht\" )"
# root -b -q "compareMET.cc+(\"_SRB_bveto\", 12.9, \"ht_highbin\" )"
# root -b -q "compareMET.cc+(\"_SRB_bveto\", 12.9, \"met\" )"
# root -b -q "compareMET.cc+(\"_SRB_bveto\", 12.9, \"ptg\" )"
# root -b -q "compareMET.cc+(\"_SRB_bveto\", 12.9, \"njets\" )"
# root -b -q "compareMET.cc+(\"_SRB_bveto\", 12.9, \"gen_ht\" )"
# root -b -q "compareMET.cc+(\"_SRA_withb\", 12.9, \"ht_highbin\" )"
# root -b -q "compareMET.cc+(\"_SRA_withb\", 12.9, \"met\" )"
# root -b -q "compareMET.cc+(\"_SRA_withb\", 12.9, \"ptg\" )"
# root -b -q "compareMET.cc+(\"_SRA_withb\", 12.9, \"njets\" )"
# root -b -q "compareMET.cc+(\"_SRA_withb\", 12.9, \"gen_ht\" )"
# root -b -q "compareMET.cc+(\"_SRA_bveto\", 12.9, \"ht_highbin\" )"
# root -b -q "compareMET.cc+(\"_SRA_bveto\", 12.9, \"met\" )"
# root -b -q "compareMET.cc+(\"_SRA_bveto\", 12.9, \"ptg\" )"
# root -b -q "compareMET.cc+(\"_SRA_bveto\", 12.9, \"njets\" )"
# root -b -q "compareMET.cc+(\"_SRA_bveto\", 12.9, \"gen_ht\" )"

# root -b -q "compareMET.cc+(\"_SR_ATLAS\", 12.9, \"ht_highbin\" )"
# root -b -q "compareMET.cc+(\"_SR_ATLAS\", 12.9, \"met\" )"
# root -b -q "compareMET.cc+(\"_SR_ATLAS\", 12.9, \"ptg\" )"
# root -b -q "compareMET.cc+(\"_SR_ATLAS\", 12.9, \"njets\" )"
# root -b -q "compareMET.cc+(\"_SR_ATLAS\", 12.9, \"gen_ht\" )"

root -b -q "compareMET.cc+(\"_SRA_bveto\", 1.0, \"met\" )"
root -b -q "compareMET.cc+(\"_SRA_withb\", 1.0, \"met\" )"
root -b -q "compareMET.cc+(\"_SRB_bveto\", 1.0, \"met\" )"
root -b -q "compareMET.cc+(\"_SRB_withb\", 1.0, \"met\" )"
root -b -q "compareMET.cc+(\"_SR_ATLAS\",  1.0, \"met\" )"

# root -b -q "compareMET.cc+(\"_SRA_bveto\", 1.0, \"ptg\" )"
# root -b -q "compareMET.cc+(\"_SRA_withb\", 1.0, \"ptg\" )"
# root -b -q "compareMET.cc+(\"_SRB_bveto\", 1.0, \"ptg\" )"
# root -b -q "compareMET.cc+(\"_SRB_withb\", 1.0, \"ptg\" )"
# root -b -q "compareMET.cc+(\"_SR_ATLAS\",  1.0, \"ptg\" )"
