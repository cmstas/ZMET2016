#include "TROOT.h"
#include "Riostream.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TString.h"

//int skimBaby(TString inFileName="output.root", TString outFileName="skim.root"){
// int skimBaby(TString inFileName="/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016D_23sep2016rereco_ph_v1_1.root", TString outFileName="skim.root"){
int skimBaby(TString inFileName="/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/ttbar_dilep_powheg_alphas01273_14.root", TString outFileName="skim.root"){  

  //
  // Input File i/o
  //

  // Open input file
  TFile *inFile = new TFile(inFileName.Data(), "read");

  if(!inFile){
    cout << "result=" << 1 << endl;
    return 1;
  }

  bool isZombie = (bool)inFile->IsZombie();
  
  // Return 0 if good, 1 if bad
  cout << "result=" << isZombie << endl;
  //return (int)isZombie;

  bool isSignalScan=false;
  if(inFileName.Contains("SMS") || 
     inFileName.Contains("Signal") ) isSignalScan=true;

  // Grab ttree
  TTree *t = (TTree*)inFile->Get("t");


  //
  // Set variables that need to be accessed in skim
  //

  int nEvents_pass_total=0;

  // njets
  float cut_njets = 2;
  int nEvents_pass_njets=0;
  
  int njets=-1;

  t->SetBranchAddress("njets", &njets);

  // muon gamma region
  int nEvents_pass_lepgamma=0;
  
  int evt_type=-1;
  t->SetBranchAddress("evt_type", &evt_type);
  int nlep=-1;
  t->SetBranchAddress("nlep", &nlep);

  //
  // Output File i/o
  //
  
  // Open ouput file
  TFile *outFile = new TFile(outFileName.Data(), "recreate");

  // Clone Tree
  TTree *t_out = (TTree*)t->CloneTree(0);

  //
  // Loop over events and check if they pass selection
  //

  int nEvents = t->GetEntries();
  for(int iEvt=0; iEvt<nEvents; iEvt++){

    // Grab entry
    t->GetEntry(iEvt);


    // Progress
    if(iEvt!=0){
      int period = 1000;
      if(iEvt%1000 == 0) {
	// xterm magic from L. Vacavant and A. Cerri
	if (isatty(1)) {
	  if( ( nEvents - iEvt ) > period ){
	    float frac = (float)iEvt/(nEvents*0.01);
	    printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
		   "\033[0m\033[32m <---\033[0m\015", frac);
	    fflush(stdout);
	  }
	  else {
	    printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
		   "\033[0m\033[32m <---\033[0m\015", 100.);
	    cout << endl;
	  }
	}
      }
    }


    // Selection
    
    if( njets>=cut_njets  ){
	  nEvents_pass_njets++;
	}
	
	if( evt_type == 2 && nlep > 0 ){	
	  nEvents_pass_lepgamma++;
	}

    // MET
    if( njets<cut_njets && !( evt_type == 2 && nlep > 0 ) ) continue;

	nEvents_pass_total++;
	
    // Fill new tree
    t_out->Fill();

  } // end loop over events



  //
  // Print Results
  //
  cout << "=====================================================" << endl;
  cout << "    NEvents scanned = " << nEvents << endl;
  cout << "    NEvents pass njets > " << cut_njets   << ": " << nEvents_pass_njets   << " (" << 100.0*(double)nEvents_pass_njets  /(double)nEvents << "%)" << endl;
  cout << "    NEvents pass lepgamma: " << nEvents_pass_lepgamma << " (" << 100.0*(double)nEvents_pass_lepgamma/(double)nEvents << "%)" << endl;
  cout << "    NEvents pass skim: " << nEvents_pass_total << " (" << 100.0*(double)nEvents_pass_total/(double)nEvents << "%)" << endl;
  cout << "=====================================================" << endl;
  cout << endl;


  //
  // Write output
  //
  t_out->AutoSave();
  outFile->Write();
  outFile->Close();
  inFile->Close();


  return 0;
}
