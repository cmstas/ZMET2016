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

void DrawPlots(vector<TString> plot_names, TString filename, TString save_dir){
  
  TFile* f = new TFile(filename);

  while(!plot_names.empty()){
    TString plot_name = plot_names.back();
    plot_names.pop_back();

    TH1F* data = (TH1F*) ((TH1F*) f->Get("data_"+plot_name))->Clone("datahist_"+plot_name);
    TH1F* zjets = (TH1F*) ((TH1F*) f->Get("zjets_"+plot_name))->Clone("zjetshist_"+plot_name);
    TH1F* fsbkg= (TH1F*) ((TH1F*) f->Get("fsbkg_"+plot_name))->Clone("fsbkghist_"+plot_name);

    TH1F* mc_sum = (TH1F*) zjets->Clone("mc_sum");
    mc_sum->Add(fsbkg);

    //============================================
    // Draw Data-MC Plots
    //============================================

    TCanvas * c = new TCanvas("c","",1600,1200);
    c->cd();
    gPad->SetRightMargin(0.05);
    gPad->Modified();
    gStyle->SetOptStat(kFALSE);
    TPad *fullpad = new TPad("fullpad", "fullpad", 0,0,1,1);

    fullpad->Draw();
    fullpad->cd();

    TPad *plotpad = new TPad("plotpad", "plotpad",0,0.2,1.0,0.99);
    plotpad->SetRightMargin(0.05);
    plotpad->SetBottomMargin(0.12);
    plotpad->Draw();
    plotpad->cd();
    if (! plot_name.Contains("_phi"))
    {
        plotpad->SetLogy();
    }
    zjets->SetFillColor(kRed);
    zjets->SetFillStyle(1001);

    fsbkg->SetFillColor(kYellow);
    fsbkg->SetFillStyle(1001);

    data->SetMarkerStyle(20);
    
    THStack * stack = new THStack("stack_"+plot_name, data->GetTitle());
    stack->Add(fsbkg);
    stack->Add(zjets);

    double ymax = 0;
    if (mc_sum->GetMaximum() < data->GetMaximum()){
        ymax = 1.2*data->GetMaximum();
    }
    else {
        ymax = 1.2*mc_sum->GetMaximum();   
    }

    TH2F* h_axes = new TH2F(Form("%s_axes",plot_name.Data()),data->GetTitle(),data->GetNbinsX(),data->GetXaxis()->GetXmin(),data->GetXaxis()->GetXmax(),1000,0.001,ymax);

    cout<<data->GetTitle()<<endl;
    cout<<zjets->GetTitle()<<endl;

    TLatex label;
    label.SetNDC();
    label.SetTextSize(0.032);
    label.DrawLatex(0.5,0.73,data->GetTitle());

    //-----------------------
    // AXES FIX
    //-----------------------
    if (plot_name.Contains("_phi")){
        h_axes->GetXaxis()->SetTitle(data->GetXaxis()->GetTitle());
        h_axes->GetYaxis()->SetTitle(data->GetYaxis()->GetTitle());
    }

    else
    {
        h_axes->GetXaxis()->SetTitle("E^{miss}_{T}");
        h_axes->GetYaxis()->SetTitle("Count / [5 GeV]");
    }

    //----------------------
    // ADD OVERFLOW BIN
    //----------------------
    if (plot_name.Contains("_pt")){
        int n_bins = data->GetNbinsX();
        int overflow_data = data->GetBinContent(n_bins + 1);
        int overflow_zjets = zjets->GetBinContent(n_bins + 1);
        int overflow_fsbkg = fsbkg->GetBinContent(n_bins + 1);
        int overflow_mcsum = fsbkg->GetBinContent(n_bins + 1);

        int max_data = data->GetBinContent(n_bins);
        int max_zjets = zjets->GetBinContent(n_bins);
        int max_fsbkg = fsbkg->GetBinContent(n_bins);
        int max_mcsum = mc_sum->GetBinContent(n_bins);

        data->SetBinContent(n_bins, max_data+overflow_data);
        zjets->SetBinContent(n_bins, max_zjets+overflow_zjets);
        fsbkg->SetBinContent(n_bins, max_fsbkg+overflow_fsbkg);
        mc_sum->SetBinContent(n_bins, max_mcsum+overflow_mcsum);
    }

    h_axes->GetXaxis()->SetLabelSize(0.04);
    h_axes->GetXaxis()->SetTitleSize(0.05);
    h_axes->GetYaxis()->SetLabelSize(0.04);
    h_axes->GetYaxis()->SetTitleOffset(0.95);
    h_axes->GetYaxis()->SetTitleSize(0.05);

    h_axes->Draw();
    stack->Draw("HIST SAME");
    data->Draw("E1 SAME");

    plotpad->RedrawAxis();
    //c->RedrawAxis();

    TLegend *l1 = new TLegend(0.73, 0.73, 0.88, 0.88);
    l1->SetLineColor(kWhite);  
    l1->SetShadowColor(kWhite);
    l1->SetFillColor(kWhite);
    l1->AddEntry(data, "data", "p");
    l1->AddEntry(zjets, "Z+jets", "f");
    l1->AddEntry(fsbkg, "t#bar{t}", "f");

    l1->Draw("same");

    //--------------------------
    // Fill in Residual Plot
    //--------------------------

    fullpad->cd();
    TPad *ratiopad = new TPad("ratiopad", "ratiopad" ,0.,0.,1,0.21);
    ratiopad->SetTopMargin(0.05);
    ratiopad->SetBottomMargin(0.1);
    ratiopad->SetRightMargin(0.05);
    ratiopad->SetGridy();  // doesn't actually appear for some reason..
    ratiopad->Draw();
    ratiopad->cd();
    
    TH1F* residual = (TH1F*) data->Clone("residual");
    residual->Divide(mc_sum);

    for (int count=1; count<=mc_sum->GetNbinsX(); count++){ 
      double relative_error = (mc_sum->GetBinError(count))/ (mc_sum->GetBinContent(count));
      residual->SetBinError(count, residual->GetBinContent(count)*relative_error);
    }

    TH1F* h_axis_ratio = new TH1F(Form("%s_residual_axes",plot_name.Data()),"",residual->GetNbinsX(),residual->GetXaxis()->GetXmin(),residual->GetXaxis()->GetXmax());

    h_axis_ratio->GetYaxis()->SetTitleOffset(0.25);
    h_axis_ratio->GetYaxis()->SetTitleSize(0.18);
    h_axis_ratio->GetYaxis()->SetNdivisions(5);
    h_axis_ratio->GetYaxis()->SetLabelSize(0.15);
    //h_axis_ratio->GetYaxis()->SetRangeUser(0.5,1.5);
    h_axis_ratio->GetYaxis()->SetRangeUser(0.001,2.0);
    h_axis_ratio->GetYaxis()->SetTitle("Data/MC");
    h_axis_ratio->GetXaxis()->SetTickLength(0.07);
    h_axis_ratio->GetXaxis()->SetTitleSize(0.);
    h_axis_ratio->GetXaxis()->SetLabelSize(0.);
    
    TLine* line1 = new TLine(data->GetXaxis()->GetXmin(),1,data->GetXaxis()->GetXmax(),1);
    line1->SetLineStyle(2);
    
//    h_axis_ratio->GetXaxis()->SetTitle(data->GetXaxis()->GetTitle());
    h_axis_ratio->Draw("axis");
    line1->Draw("same");
    residual->Draw("same");
    
    c->Update();
    c->cd();
    c->SaveAs(save_dir+plot_name+TString(".pdf"));
    c->SaveAs(save_dir+plot_name+TString(".png"));


    delete l1;
    delete mc_sum;
    delete stack;
    delete zjets;
    delete fsbkg;
    delete data;
    delete residual;
    delete ratiopad;
    delete plotpad;
    delete fullpad;
    delete c;
  }
  f->Close();
  delete f;
}

void METStudy_draw(bool pt=true, bool phi=true, TString save_dir = "~/public_html/ZMET2016/plots/MET_study/V07-06-08    /")
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
    DrawPlots(plot_names, save_dir+"METStudy_all.root", save_dir);
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
    DrawPlots(plot_names, save_dir+"METStudy_all.root", save_dir);
    plot_names.clear();
  }

  return;
}


