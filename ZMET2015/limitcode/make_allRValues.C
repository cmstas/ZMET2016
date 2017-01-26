#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

std::vector<std::string> split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> tokens;
  while (std::getline(ss, item, delim)) {
    tokens.push_back(item);
  }
  return tokens;
}

void Fill2d(TH2F *&hist, double w, double x, double y){   
  x = std::min(hist->GetXaxis()->GetBinCenter(hist->GetXaxis()->GetLast()) , x); 
  x = std::max(hist->GetXaxis()->GetBinCenter(hist->GetXaxis()->GetFirst()), x); 
  y = std::min(hist->GetYaxis()->GetBinCenter(hist->GetYaxis()->GetLast()) , y); 
  y = std::max(hist->GetYaxis()->GetBinCenter(hist->GetYaxis()->GetFirst()), y); 
  hist->SetBinContent(hist->FindBin(x, y), w); 
}

void make_allRValues(std::string model, std::string list_filename){

  //setup file to hold r-values
  TString outfilename = Form("r-values_%s.root", model.c_str()); 
  TFile *f = new TFile(outfilename, "RECREATE");
  
  // default case: T5ZZ binning
  double m1_max = 1925;
  double m1_min = 575;
  double m2_max = 1925;
  double m2_min = 75;
  int m1_div = 50;
  int m2_div = 50;

  if (model.find("TChiWZ") != std::string::npos) {
    m1_max = 712.5;
    m1_min = 87.5;
    m2_max = 305;
    m2_min = -5;
    m1_div = 25;
    m2_div = 10;
  }

  int nbinsx = (m1_max - m1_min)/m1_div;
  int nbinsy = (m2_max - m2_min)/m2_div;

  std::cout << "nbinsx: " << nbinsx << ", nbinsy: " << nbinsy << std::endl;

  f->cd();
  TH2F *hExp   = new TH2F("hExp",   "hExp"  , nbinsx, m1_min, m1_max, nbinsy, m2_min, m2_max);
  TH2F *hObs   = new TH2F("hObs",   "hObs"  , nbinsx, m1_min, m1_max, nbinsy, m2_min, m2_max);
  TH2F *hExp1m = new TH2F("hExp1m", "hExp1m", nbinsx, m1_min, m1_max, nbinsy, m2_min, m2_max);
  TH2F *hExp2m = new TH2F("hExp2m", "hExp2m", nbinsx, m1_min, m1_max, nbinsy, m2_min, m2_max);
  TH2F *hExp1p = new TH2F("hExp1p", "hExp1p", nbinsx, m1_min, m1_max, nbinsy, m2_min, m2_max);
  TH2F *hExp2p = new TH2F("hExp2p", "hExp2p", nbinsx, m1_min, m1_max, nbinsy, m2_min, m2_max);
  //TH2F *hSig   = new TH2F("hSig",   "hSig"  , nbinsx, m1_min, m1_max, nbinsy, m2_min, m2_max);

  // read file with list of combine output filenames
  std::ifstream listfile(list_filename.c_str());
  std::string filename;
  while (std::getline(listfile, filename)) {
  
    //This file is created earlier by running combine
    //  TFile *limit_file = new TFile(Form("limit_%s_%d_%d.root", model.c_str(), m1, m2), "READ");
    TFile *limit_file = new TFile(filename.c_str(), "READ");
    TTree *limit_tree = (TTree*)limit_file->Get("limit");

    //This file is created earlier by running combine
    //TFile *significance_file = new TFile(Form("significance_%s_%d_%d.root", model.c_str(), m1, m2), "READ");
    //TTree *significance_tree = (TTree*)significance_file->Get("limit");

    double value = -1.0;
    limit_tree->SetBranchAddress("limit", &value);

    double limit   = -1.0; //observed limit
    double rm2s    = -1.0; //expected - 2 sigma
    double rm1s    = -1.0; //expected - 1 sigma
    double rmedian = -1.0; //expected limit
    double rp1s    = -1.0; //expected + 1 sigma
    double rp2s    = -1.0; //expected + 2 sigma

    for(int i=0; i< 6; i++){
      limit_tree->GetEntry(i);
      if(i==0)      rm2s    = value;
      else if(i==1) rm1s    = value;
      else if(i==2) rmedian = value;
      else if(i==3) rp1s    = value;
      else if(i==4) rp2s    = value;
      else if(i==5) limit   = value;
    }

    //double sig = -1.0;
    //significance_tree->SetBranchAddress("limit", &sig);
    //significance_tree->GetEntry(0);

    delete limit_tree;
    limit_file->Close();
    delete limit_file;

    //delete significance_tree;
    //significance_file->Close();
    //delete significance_file;

    // protect against non-existant mass points
    if( value > 21263 ) continue;

    // get mass point
    //  filenames of the form: limit_TChiWZ_750_300.root
    std::vector<std::string> tokens = split(filename,'_');
    double m1 = std::stod(tokens[2]);
    std::vector<std::string> tokens2 = split(tokens[3],'.');
    double m2 = std::stod(tokens2[0]);
  
    f->cd();

    Fill2d(hExp  , rmedian, m1, m2);    
    Fill2d(hObs  , limit  , m1, m2);  
    Fill2d(hExp1m, rm1s   , m1, m2);  
    Fill2d(hExp2m, rm2s   , m1, m2);  
    Fill2d(hExp1p, rp1s   , m1, m2);  
    Fill2d(hExp2p, rp2s   , m1, m2);  
    //Fill2d(hSig  , sig    , m1, m2);  

  } // loop over combine output files
  
  f->cd();
  hExp  ->Write("",TObject::kOverwrite);
  hObs  ->Write("",TObject::kOverwrite);
  hExp1m->Write("",TObject::kOverwrite);
  hExp2m->Write("",TObject::kOverwrite);
  hExp1p->Write("",TObject::kOverwrite);
  hExp2p->Write("",TObject::kOverwrite);
  //hSig  ->Write("",TObject::kOverwrite);

  f->Close();
  delete f;

}
