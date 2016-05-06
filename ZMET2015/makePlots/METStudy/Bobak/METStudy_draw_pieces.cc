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

void DrawPlots(vector<TString> plot_names, TString filename, TString save_dir, double plot_height = .8){
  
  TFile* f = new TFile(filename);

  while(!plot_names.empty()){
    TString plot_name = plot_names.back();
    plot_names.pop_back();

    TH1F* data = (TH1F*) f->Get("data_"+plot_name);
    TH1F* zjets = (TH1F*) f->Get("zjets_"+plot_name);
    TH1F* fsbkg= (TH1F*) f->Get("fsbkg_"+plot_name);
    TH1F* residual = (TH1F*) data->Clone("residual");
    TH1F* mc_sum = (TH1F*) zjets->Clone("mc_sum");
    mc_sum->Add(fsbkg);
    residual->Divide(mc_sum);

    //============================================
    // Draw Data-MC Plots
    //============================================

    TCanvas *c_plot = new TCanvas("plot_canvas", "plot_canvas" ,1920, 1080*plot_height);

    gPad->SetRightMargin(0.05);
    gPad->Modified();
    gStyle->SetOptStat(kFALSE);

    c_plot->SetLogy();
    
    zjets->SetFillColor(kRed);
    zjets->SetFillStyle(1001);

    fsbkg->SetFillColor(kYellow);
    fsbkg->SetFillStyle(1001);

    data->SetMarkerStyle(20);
    
    THStack * stack = new THStack("stack", data->GetTitle());
    stack->Add(fsbkg);
    stack->Add(zjets);

    if (stack->GetMaximum() < data->GetMaximum()){
      stack->SetMaximum(1.2*data->GetMaximum());
    }

    stack->Draw("HIST");
    stack->Draw("HIST SAME");
    data->Draw("E1 SAME");
    c_plot->RedrawAxis();

    TLegend *l1 = new TLegend(0.73, 0.73, 0.88, 0.88);
    l1->SetLineColor(kWhite);  
    l1->SetShadowColor(kWhite);
    l1->SetFillColor(kWhite);
    l1->AddEntry(data, "data", "p");
    l1->AddEntry(zjets, "Z+jets", "f");
    l1->AddEntry(fsbkg, "t#bar{t}", "f");

    l1->Draw("same");

    stack->GetXaxis()->SetTitle(data->GetXaxis()->GetTitle());
    stack->GetYaxis()->SetTitle(data->GetYaxis()->GetTitle());

    c_plot->Update();
    c_plot->SaveAs(save_dir+plot_name+TString("_plot.png"));
    delete c_plot;

    //============================================
    // Draw Ratio Plot
    //============================================
    
    TCanvas *c_ratio = new TCanvas("ratio_canvas", "ratio_canvas" ,1920, 1080*(1-plot_height));
    c_ratio->cd();

    residual->GetYaxis()->SetTitle("Data/MC");
    
    /*for (int count=1; count<=mc_sum->GetNbinsX(); count++){ 
      double relative_error = (mc_sum->GetBinError(count))/ (mc_sum->GetBinContent(count));
      residual->SetBinError(count, residual->GetBinContent(count)*relative_error);
    }*/
    
    residual->Draw();
    
    c_ratio->Update();
    c_ratio->SaveAs(save_dir+plot_name+TString("_ratio.png"));
    
    delete c_ratio;
    delete stack;
    delete l1;
    delete zjets;
    delete fsbkg;
    delete data;
    delete residual;
    delete mc_sum;
  }
  delete f;
}

void METStudy_draw_pieces(bool pt=true, bool phi=true, TString save_dir = "~/public_html/ZMET2016/plots/MET_study/")
{
  

  vector<TString> plot_names;
  

  if (phi) {
  //============================================
  // Phi plots
  //============================================
  //-----------------define---------------------
    plot_names.push_back("ph_0013_phi");
    plot_names.push_back("ch_0013_phi");
    plot_names.push_back("nu_0013_phi");
    plot_names.push_back("ph_1624_phi");
    plot_names.push_back("ch_1624_phi");
    plot_names.push_back("nu_1624_phi");
    plot_names.push_back("ph_2430_phi");
    plot_names.push_back("ch_2430_phi");
    plot_names.push_back("nu_2430_phi");
    
    // Run over Phi plots
    DrawPlots(plot_names, save_dir+"METStudy_phi.root", save_dir);
    plot_names.clear();
  }

  if (pt) {
    //============================================
    // PT plots
    //============================================

    //-----------------define---------------------
    plot_names.push_back("MET");
    plot_names.push_back("MET_2Jets");
    plot_names.push_back("ph_0013_pt");
    plot_names.push_back("ch_0013_pt");
    plot_names.push_back("nu_0013_pt");
    plot_names.push_back("ph_1624_pt");
    plot_names.push_back("ch_1624_pt");
    plot_names.push_back("nu_1624_pt");
    plot_names.push_back("ph_2430_pt");
    plot_names.push_back("ch_2430_pt");
    plot_names.push_back("nu_2430_pt");
    plot_names.push_back("nu_30in_pt");
    
    // Run over PT plots
    DrawPlots(plot_names, save_dir+"METStudy_pt.root", save_dir);
    plot_names.clear();
  }

  return;
}


