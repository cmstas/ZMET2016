#include "TH1F.h"
#include "TH2.h"
#include "TFile.h"
#include "TLine.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPad.h"
#include "TLatex.h"
#include "THStack.h"
#include "TStyle.h"

#include "RooHistError.h"
#include "TGraphAsymmErrors.h"

#include <iostream>

#include "../sharedCode/histTools.cc"


void makeSystematicPlots( string selection  = "bveto_SRB", string systematic = "_noleptonid_noleptoniso", string metcut = "225toinf" )
{

  gStyle->SetPaintTextFormat(".2f");
   
  string iter = "V08-11-00";
  // string selection  = "bveto_SRB";
  // string systematic = "_noleptonid_noleptoniso";
  
  TH2D  * h_nominal = NULL;  
  TFile * f_nominal = NULL;
  TH2D  * h_varied = NULL;  
  TFile * f_varied = NULL;
  cout<<"Nominal: "<<Form("../output/%s/fullscan_%s_hists.root", iter.c_str(), selection.c_str())<<endl;
  cout<<"Varied:  "<<Form("../output/%s/fullscan_%s%s_hists.root", iter.c_str(), selection.c_str(), systematic.c_str())<<endl;
  
  f_nominal = TFile::Open(Form("../output/%s/fullscan_%s_hists.root", iter.c_str(), selection.c_str()), "READ");
  f_varied  = TFile::Open(Form("../output/%s/fullscan_%s%s_hists.root", iter.c_str(), selection.c_str(), systematic.c_str()), "READ");
  h_nominal = (TH2D*)f_nominal->Get(Form("h_signalyields_met%s_ll", metcut.c_str() ))->Clone("h_nominal");
  h_varied  = (TH2D*)f_varied ->Get(Form("h_signalyields_met%s_ll", metcut.c_str() ))->Clone("h_varied");


  TCanvas * c1 = new TCanvas("c1","");
  c1->cd();

  TPad *pad = new TPad( "p_main", "p_main", 0.0, 0.0, 1.0, 1.0);
  pad->SetTopMargin(0.08);
  pad->SetBottomMargin(0.20);
  pad->SetRightMargin(0.05);
  pad->SetLeftMargin(0.15);
  pad->Draw();
  pad->cd();
  // pad->SetLogz();

  TH2D  * h_difference = (TH2D*) h_nominal->Clone("h_difference");  

  h_difference->Add(h_varied, -1);
  h_difference->Divide(h_nominal);

  h_difference->GetXaxis()->SetRangeUser(100,500);
  h_difference->GetZaxis()->SetRangeUser(-0.5,0.5);
  h_difference->GetYaxis()->SetTitle("m(#tilde{#chi}_{0}^{2}) [GeV]");
  h_difference->GetXaxis()->SetTitle("m(#tilde{g}) [GeV]");
  h_difference->GetYaxis()->SetTitleOffset(1.5);
  h_difference->Draw("colztext");
  
  c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_massplane_MET_%s_%s%s.png", iter.c_str(), metcut.c_str(), selection.c_str(), systematic.c_str()));
  c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_massplane_MET_%s_%s%s.pdf", iter.c_str(), metcut.c_str(), selection.c_str(), systematic.c_str()));
  return;
}
