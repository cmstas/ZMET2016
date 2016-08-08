#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"

#include <iostream>
#include <vector>


float GetValue(float xvalue, float yvalue, TH2F *&hist){
  float xmax = hist->GetXaxis()->GetXmax()-0.01;
  int xbin   = hist->GetXaxis()->FindBin(min(xvalue, xmax));
  int ybin   = hist->GetYaxis()->FindBin(yvalue);
  return hist->GetBinContent(xbin, ybin);
}


void makeLimitTable(){

  TFile *f_T1tttt = new TFile("r-values_T1tttt.root", "READ");
  TFile *f_T1bbbb = new TFile("r-values_T1bbbb.root", "READ");
  TFile *f_T1qqqq = new TFile("r-values_T1qqqq.root", "READ");
  TFile *f_T2tt   = new TFile("r-values_T2tt.root", "READ");
  TFile *f_T2bb   = new TFile("r-values_T2bb.root", "READ");
  TFile *f_T2qq   = new TFile("r-values_T2qq.root", "READ");

/*
  TH2F *hSig_T1tttt = (TH2F*)f_T1tttt->Get("hSig");
  TH2F *hSig_T1bbbb = (TH2F*)f_T1bbbb->Get("hSig");
  TH2F *hSig_T1qqqq = (TH2F*)f_T1qqqq->Get("hSig");
  TH2F *hSig_T2tt = (TH2F*)f_T2tt->Get("hSig");
  TH2F *hSig_T2bb = (TH2F*)f_T2bb->Get("hSig");
  TH2F *hSig_T2qq = (TH2F*)f_T2qq->Get("hSig");
*/

  TH2F *hExp_T1tttt = (TH2F*)f_T1tttt->Get("hExp");
  TH2F *hExp_T1bbbb = (TH2F*)f_T1bbbb->Get("hExp");
  TH2F *hExp_T1qqqq = (TH2F*)f_T1qqqq->Get("hExp");
  TH2F *hExp_T2tt = (TH2F*)f_T2tt->Get("hExp");
  TH2F *hExp_T2bb = (TH2F*)f_T2bb->Get("hExp");
  TH2F *hExp_T2qq = (TH2F*)f_T2qq->Get("hExp");

/*
  std::cout << endl;
  std::cout <<"SIGNIFICANCE" << std::endl;
  std::cout << "T1tttt (1500, 100) " << GetValue(1500, 100, hSig_T1tttt) << std::endl;
  std::cout << "T1tttt (1200, 800) " << GetValue(1200, 800, hSig_T1tttt) << std::endl;
  std::cout << "T1bbbb (1500, 100) " << GetValue(1500, 100, hSig_T1bbbb) << std::endl;
  std::cout << "T1bbbb (1000, 900) " << GetValue(1000, 900, hSig_T1bbbb) << std::endl;
  std::cout << "T1qqqq (1400, 100) " << GetValue(1400, 100, hSig_T1qqqq) << std::endl;
  std::cout << "T1qqqq (1000, 800) " << GetValue(1000, 800, hSig_T1qqqq) << std::endl;
  std::cout << "T2tt (850, 100) "    << GetValue(850, 100, hSig_T2tt)    << std::endl;
  std::cout << "T2tt (650, 325) "    << GetValue(650, 325, hSig_T2tt)    << std::endl;
  std::cout << "T2tt (500, 325) "    << GetValue(500, 325, hSig_T2tt)    << std::endl;
  std::cout << "T2tt (425, 325) "    << GetValue(425, 325, hSig_T2tt)    << std::endl;
  std::cout << "T2bb (900, 100) "    << GetValue(900, 100, hSig_T2bb)    << std::endl;
  std::cout << "T2bb (600, 580) "    << GetValue(600, 580, hSig_T2bb)    << std::endl;
  std::cout << "T2qq (1200, 100) "   << GetValue(1200, 100, hSig_T2qq)   << std::endl;
  std::cout << "T2qq (600, 550) "    << GetValue(600, 550, hSig_T2qq)    << std::endl;
*/
  std::cout << endl;
  std::cout <<"LIMITS" << std::endl;
  std::cout << "T1tttt (1500, 100) " << GetValue(1500, 100, hExp_T1tttt) << std::endl;
  std::cout << "T1tttt (1200, 800) " << GetValue(1200, 800, hExp_T1tttt) << std::endl;
  std::cout << "T1bbbb (1500, 100) " << GetValue(1500, 100, hExp_T1bbbb) << std::endl;
  std::cout << "T1bbbb (1000, 900) " << GetValue(1000, 900, hExp_T1bbbb) << std::endl;
  std::cout << "T1qqqq (1400, 100) " << GetValue(1400, 100, hExp_T1qqqq) << std::endl;
  std::cout << "T1qqqq (1000, 800) " << GetValue(1000, 800, hExp_T1qqqq) << std::endl;
  std::cout << "T2tt (850, 100) "    << GetValue(850, 100, hExp_T2tt)    << std::endl;
  std::cout << "T2tt (650, 325) "    << GetValue(650, 325, hExp_T2tt)    << std::endl;
  std::cout << "T2tt (500, 325) "    << GetValue(500, 325, hExp_T2tt)    << std::endl;
  std::cout << "T2tt (425, 325) "    << GetValue(425, 325, hExp_T2tt)    << std::endl;
  std::cout << "T2bb (900, 100) "    << GetValue(900, 100, hExp_T2bb)    << std::endl;
  std::cout << "T2bb (600, 580) "    << GetValue(600, 580, hExp_T2bb)    << std::endl;
  std::cout << "T2qq (1200, 100) "   << GetValue(1200, 100, hExp_T2qq)   << std::endl;
  std::cout << "T2qq (600, 550) "    << GetValue(600, 550, hExp_T2qq)    << std::endl;
  std::cout << endl;

}
