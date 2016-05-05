#include <iostream>
#include <stdexcept>
#include <vector>

#include "TChain.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TColor.h"
#include "THStack.h"
#include "TCut.h"
#include "TH1F.h"

using namespace std;

void METStudy(TString save_dir = "~/public_html/ZMET2016/plots/MET_study/")
{

  vector<TCut> cuts;
  vector<TString> plot_names;
  vector<TString> plot_vars;

  //============================================
  // Define plots
  //============================================

  // Raw Met
  plot_names.push_back("MET");
  plot_vars.push_back("met_rawPt");
  cuts.push_back("nlep > 2 && lep_pt[0] > 20 && lep_pt[1] > 20 && abs(lep_p4[0].eta()) < 1.3 && abs(lep_p4[1].eta()) < 1.3 && dRll < 0.1 && evt_type == 0 && (( HLT_DoubleMu || HLT_DoubleMu_tk || HLT_DoubleMu_noiso ) && hyp_type == 1 ) || (( HLT_DoubleEl_DZ || HLT_DoubleEl_noiso ) && hyp_type == 0) && evt_passgoodrunlist > 0");

  // Raw Met With at least 2 jets
  plot_names.push_back("MET_2Jets");
  plot_vars.push_back("met_rawPt");
  cuts.push_back("njets >= 2 && nlep > 2 && lep_pt[0] > 20 && lep_pt[1] > 20 && abs(lep_p4[0].eta()) < 1.3 && abs(lep_p4[1].eta()) < 1.3 && dRll < 0.1 && evt_type == 0 && (( HLT_DoubleMu || HLT_DoubleMu_tk || HLT_DoubleMu_noiso ) && hyp_type == 1 ) || (( HLT_DoubleEl_DZ || HLT_DoubleEl_noiso ) && hyp_type == 0) && evt_passgoodrunlist > 0");

  //============================================
  // Load in Data
  //============================================

  TChain * ch_zjets = new TChain("t");
  ch_zjets->Add("/nfs-7/userdata/ZMEToutput2016/output/ZMETbabies/V07-06-06/DY*");
 
  TChain * ch_fsbkg = new TChain("t");
  ch_fsbkg->Add("/nfs-7/userdata/ZMEToutput2016/output/ZMETbabies/V07-06-06/ttjets*");

  TChain * ch_data =  new TChain("t");
  ch_data->Add("/nfs-7/userdata/ZMEToutput2016/output/ZMETbabies/V07-06-06/data*");
  
  TCut weight = "evt_scale1fb*2.3"; //Good for 2015 run2

  //============================================
  // Define Cuts
  //============================================

  while(!cuts.empty()){
    TCut selection = cuts.back();
    TString plot_variable = plot_vars.back();
    TString plot_name = plot_names.back();

    cuts.pop_back();
    plot_vars.pop_back();
    plot_names.pop_back();

    TH1F * zjets = new TH1F("zjets_"+plot_name, "", 500, 0 ,500);
    TH1F * fsbkg = new TH1F("fsbkg_"+plot_name, "", 500, 0 ,500);
    TH1F * data = new TH1F("data_"+plot_name, "", 500, 0 ,500);
 
    zjets->Sumw2();
    fsbkg->Sumw2();

    ch_zjets->Draw(plot_variable+">>zjets_"+plot_name    ,  selection          *weight);
    ch_fsbkg->Draw(plot_variable+">>fsbkg_"+plot_name    ,  selection          *weight);
    ch_data->Draw(plot_variable+">>data_"+plot_name    ,  selection);

    THStack * stack = new THStack("stack","");

    zjets->Rebin(5);
    fsbkg->Rebin(5);
    data->Rebin(5);

    stack->Add(fsbkg);
    stack->Add(zjets);


    //============================================
    // Draw Plots
    //============================================

    TCanvas * c = new TCanvas("c","",1920,1080);
    gStyle->SetOptStat(kFALSE);
    c->cd();
    c->SetLogy();
    
    zjets->SetFillColor(kRed);
    zjets->SetFillStyle(1001);

    fsbkg->SetFillColor(kYellow);
    fsbkg->SetFillStyle(1001);

    data->SetMarkerStyle(20);
    
    zjets->GetXaxis()->SetTitle("E^{miss}_{T}");
    zjets->GetYaxis()->SetTitle("Count / [5 GeV]");  

    stack->Draw("HIST");
    stack->Draw("HIST SAME");
    data->Draw("E1 SAME");
    c->RedrawAxis();

    TLegend *l1 = new TLegend(0.73, 0.73, 0.88, 0.88);    
    l1->SetLineColor(kWhite);    
    l1->SetShadowColor(kWhite);    
    l1->SetFillColor(kWhite);    
    l1->AddEntry(data, "data", "p");
    l1->AddEntry(zjets, "Z+jets", "f");
    l1->AddEntry(fsbkg, "t#bar{t}", "f");

    l1->Draw("same");

    c->SaveAs(save_dir+plot_name+TString(".pdf"));
    c->SaveAs(save_dir+plot_name+TString(".png"));

    c->~TCanvas();
    selection->~TCut();
    plot_name->~TString();
    plot_variable->~TString();
    zjets->~TH1F();
    fsbkg->~TH1F();
    data->~TH1F();
  }

  return;
}
