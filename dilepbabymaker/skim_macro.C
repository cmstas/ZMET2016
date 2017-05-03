#include <fstream>
#include <sstream>
#include <iostream>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>

using namespace std;

void skim_macro(string inpath = "./", string outpath = "./", string intag = "output", string outtag = "skim") {
  
  //--------------------------------------------------
  // cut for output files
  //--------------------------------------------------

  // NOTE: string below doesn't work correctly, implicitly requires all events to have 2 leptons
  //  const char* sel = "((njets >= 2 || njets_up >= 2 || njets_dn >= 2) || (evt_type == 2 && nlep > 0 && abs(lep_pdgId[0]) == 13) || (nlep > 2 && lep_pt[0] > 25 && lep_pt[1] > 20)) ";
  
  //const char* sel = "((njets >= 2 || njets_up >= 2 || njets_dn >= 2) || (evt_type == 2 && nlep > 0) || (nlep > 2)) ";
  const char* sel = "((evt_type == 1 && nlep == 2) || (nlep > 2)) ";

  //cout << "Skimming with selection : "<<sel<<endl;

  //--------------------------------------------------
  // input and output file
  //--------------------------------------------------
  
  const char* infilename = Form("%s/%s*.root",inpath.c_str(),intag.c_str());
  const char* outfilename = Form("%s/%s.root",outpath.c_str(),outtag.c_str());
  
  //--------------------------------------------------
  // cout stuff
  //--------------------------------------------------
  
  cout << "Reading in : " << infilename << endl;
  cout << "Writing to : " << outfilename << endl;
  cout << "Selection : " << sel << endl;
  
  //--------------------------------------------------
  // read input file, write to output files
  //--------------------------------------------------
  
  //long long max_tree_size = 5000000000LL; // 5GB
  //long long max_tree_size = 2500000000LL; // 2.5GB
  //TTree::SetMaxTreeSize(max_tree_size);
  
  TChain *chain = new TChain("t");
  chain->Add(infilename);

  unsigned int input_entries = chain->GetEntries();
  cout << "Input tree has entries: " << input_entries << endl;
  if (input_entries == 0) {
    cout << "ERROR: no entries in input tree, exiting.." << endl;
    return;
  }
  
  //-------------------
  // skim
  //-------------------
  
  TFile *outfile = TFile::Open(outfilename, "RECREATE");
  assert( outfile != 0 );
  TTree* outtree = chain->CopyTree( sel );
  unsigned int output_entries = outtree->GetEntries();
  cout << "Output tree has entries: " << output_entries << endl
       << "Reduction factor of: " << double(input_entries)/double(output_entries) << endl;
  outtree->Write();
  outfile->Close();

}
