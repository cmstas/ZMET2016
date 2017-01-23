#include "Riostream.h"
#include "TFile.h"
#include "TTree.h"

int sweeproot_macro(const char *rootFileName, const char *treeName = "t", bool check_every_event = false){

  TFile *rootFile = new TFile(rootFileName, "read");

  // Check if file handle is bad, Return 0 if good, 1 if bad
  if(!rootFile){
    cout << "result=" << 1 << endl;
    return 1;
  }

  // Check if file isZombie
  bool isZombie = (bool)rootFile->IsZombie();

  // Check number of entries
  if (check_every_event) {
      TTree *tree = (TTree*)rootFile->Get(treeName);
      unsigned int nEvents = tree->GetEntries();
      for (unsigned int idx = 0; idx < nEvents; idx++) {
          if (tree->GetEntry(idx,1) < 0) {
              cout << "Event " << idx << " in file " << rootFileName << " is bad" << endl;
              return -1*idx;
          }
      }
  }
  rootFile->Close();
  
  // Return 0 if good, 1 if bad
  cout << "result=" << isZombie << endl;
  return (int)isZombie;

}
  
