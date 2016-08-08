#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"

#include <iostream>
#include <vector>



void Fill2d(TH2F *&hist, double w, double x, double y){   
  x = std::min(hist->GetXaxis()->GetBinCenter(hist->GetXaxis()->GetLast()) , x); 
  x = std::max(hist->GetXaxis()->GetBinCenter(hist->GetXaxis()->GetFirst()), x); 
  y = std::min(hist->GetYaxis()->GetBinCenter(hist->GetYaxis()->GetLast()) , y); 
  y = std::max(hist->GetYaxis()->GetBinCenter(hist->GetYaxis()->GetFirst()), y); 
  hist->SetBinContent(hist->FindBin(x, y), w); 
}

void make_sigValue(std::string model, int m1, int m2){

  //setup file to hold r-values if it doesn't already exist
  TFile *f_temp = new TFile(Form("r-values_Significance_%s.root", model.c_str()), "NEW");
  if(f_temp){
    
    // TH2F *hExp   = new TH2F("hExp",   "hExp"  , 25,87.5,712.5,31,-5,305);
    // TH2F *hObs   = new TH2F("hObs",   "hObs"  , 25,87.5,712.5,31,-5,305);
    // TH2F *hExp1m = new TH2F("hExp1m", "hExp1m", 25,87.5,712.5,31,-5,305);
    // TH2F *hExp2m = new TH2F("hExp2m", "hExp2m", 25,87.5,712.5,31,-5,305);
    // TH2F *hExp1p = new TH2F("hExp1p", "hExp1p", 25,87.5,712.5,31,-5,305);
    // TH2F *hExp2p = new TH2F("hExp2p", "hExp2p", 25,87.5,712.5,31,-5,305);
    TH2F *hSig   = new TH2F("hSig",   "hSig"  , 25,87.5,712.5,31,-5,305);

    f_temp->Write();
    f_temp->Close();
  }
  delete f_temp;

  //This file is created earlier by running combine
  // TFile *limit_file = new TFile(Form("significance_%s_%d_%d.root", model.c_str(), m1, m2), "READ");
  // TTree *limit_tree = (TTree*)limit_file->Get("limit");

  //This file is created earlier by running combine
  TFile *significance_file = new TFile(Form("significance_%s_%d_%d.root", model.c_str(), m1, m2), "READ");
  TTree *significance_tree = (TTree*)significance_file->Get("limit");

  if( !significance_tree ) return;
  
  //This file will hold 2d histograms with limit r-values and discovery significance
  TFile *f = new TFile(Form("r-values_Significance_%s.root", model.c_str()), "UPDATE");

  // double value = -1.0;
  // limit_tree->SetBranchAddress("limit", &value);

  // double limit   = -1.0; //observed limit
  // double rm2s    = -1.0; //expected - 2 sigma
  // double rm1s    = -1.0; //expected - 1 sigma
  // double rmedian = -1.0; //expected limit
  // double rp1s    = -1.0; //expected + 1 sigma
  // double rp2s    = -1.0; //expected + 2 sigma

  // for(int i=0; i< 6; i++){
  //   limit_tree->GetEntry(i);
  // 	if( value < 21263 ){
  // 	  if(i==0)      rm2s    = value;
  // 	  else if(i==1) rm1s    = value;
  // 	  else if(i==2) rmedian = value;
  // 	  else if(i==3) rp1s    = value;
  // 	  else if(i==4) rp2s    = value;
  // 	  else if(i==5) limit   = value;
  // 	}
  // }

  double sig = -1.0;
  significance_tree->SetBranchAddress("limit", &sig);
  significance_tree->GetEntry(0);

  // delete limit_tree;
  // limit_file->Close();
  // delete limit_file;

  delete significance_tree;
  significance_file->Close();
  delete significance_file;

  // if( value > 21263 ) exit(0);
  
  f->cd();

  // TH2F *hExp   = (TH2F*)f->Get("hExp");
  // TH2F *hObs   = (TH2F*)f->Get("hObs");
  // TH2F *hExp1m = (TH2F*)f->Get("hExp1m");
  // TH2F *hExp2m = (TH2F*)f->Get("hExp2m");
  // TH2F *hExp1p = (TH2F*)f->Get("hExp1p");
  // TH2F *hExp2p = (TH2F*)f->Get("hExp2p");
  TH2F *hSig   = (TH2F*)f->Get("hSig");

  // Fill2d(hExp  , rmedian, m1, m2);    
  // Fill2d(hObs  , limit  , m1, m2);  
  // Fill2d(hExp1m, rm1s   , m1, m2);  
  // Fill2d(hExp2m, rm2s   , m1, m2);  
  // Fill2d(hExp1p, rp1s   , m1, m2);  
  // Fill2d(hExp2p, rp2s   , m1, m2);  
  Fill2d(hSig  , sig    , m1, m2);  

  // hExp  ->Write("",TObject::kOverwrite);
  // hObs  ->Write("",TObject::kOverwrite);
  // hExp1m->Write("",TObject::kOverwrite);
  // hExp2m->Write("",TObject::kOverwrite);
  // hExp1p->Write("",TObject::kOverwrite);
  // hExp2p->Write("",TObject::kOverwrite);
  hSig  ->Write("",TObject::kOverwrite);
  f->Close();
  delete f;

}


void make_sigValues(){
  for( int xbinind = 4; xbinind < 31; xbinind++ ){
  	for( int ybinind = 0; ybinind < 32; ybinind++ ){
  	  // int binind = h_entries->FindBin(xbinind*25,ybinind*10);
  	  cout<<Form("Making significance for %i | %i",xbinind*25,ybinind*10)<<endl;
	  make_sigValue("TChiWZ", xbinind*25, ybinind*10);
  	}
  }
  return;
}
