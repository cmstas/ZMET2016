#include "Riostream.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TH3D.h"
#include "TH2F.h"
#include "TString.h"
#include "TKey.h"

#include <vector>
#include <string>
#include <cstring>

void merge_macro(std::string indir, std::string input_files, std::string outfile) {

  //split input list of files input into a vector of files names
  std::vector<std::string> vfiles;
  char *saveptr;
  char *tok = std::strtok((char*)input_files.c_str(), ",");
  while (tok != NULL) {
    vfiles.push_back(std::string(tok));
    tok = std::strtok(NULL,",");
  }  
  
  // Print user commands
  cout << "Merging files from dir: " << indir << endl;
  cout << "Outputting to: " << outfile << endl;

  // Declare new TChain
  TChain *chain = new TChain("t");
  // chain->SetMaxTreeSize(5000000000LL); //default is 100000000000LL = 100Gb

  // Get number of files from input directory
  int nFiles_in = 0;
  for (std::vector<std::string>::iterator it = vfiles.begin(); it != vfiles.end(); it++, nFiles_in++) {
    chain->Add(Form("%s/%s", indir.c_str(), it->c_str()));
  }

  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  //Next corrupt files
  currentFile = 0;
  fileIter.Reset(); 
  while ( (currentFile = (TFile*)fileIter.Next()) ){
      std::cout << " currentFile->GetTitle(): " << currentFile->GetTitle() << std::endl;
    TFile *file = TFile::Open(currentFile->GetTitle());
    if (file->IsZombie()){
      cout << "Error! " << currentFile->GetTitle() << " is corrupt" << endl;
      return;  
    }
  }
  cout << "No corrupt files, all good."  << endl;

  //Then merge trees
  chain->Merge(outfile.c_str(), "fast");
  std::cout << "Total events merged: " << chain->GetEntries() << std::endl;
  
  //Then merge 1D hists
  std::vector <TH1F*> ourHists; 
  currentFile = 0;
  fileIter.Reset(); 
  //file loop
  while ( (currentFile = (TFile*)fileIter.Next()) ){
    TFile *file = TFile::Open(currentFile->GetTitle());
    //Hist loop
    for (auto&& keyAsObj : *file->GetListOfKeys()){
      auto key = (TKey*)keyAsObj;
      if (strncmp(key->GetClassName(), "TH1D", 1000) != 0) continue; 
      TH1F *hist = (TH1F*)key->ReadObj(); 
      //OurHist loop
      bool foundIt = false;
      for (unsigned int i = 0; i < ourHists.size(); i++){
        if (strncmp(ourHists[i]->GetTitle(), hist->GetTitle(), 1000) == 0){ ourHists[i]->Add(hist); foundIt = true; }
      }
      if (!foundIt) ourHists.push_back(hist); 
    }
  }
  cout << ourHists.size() << endl;
  cout << ourHists[0]->GetBinContent(0) << endl; 
  
  TFile *file = new TFile(outfile.c_str(), "UPDATE"); 
  for (unsigned int i = 0; i < ourHists.size(); i++) ourHists[i]->Write();  
  delete file; 

  cout << "done!" << endl;
}
