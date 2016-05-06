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

void METStudy_phi(TString save_dir = "~/public_html/ZMET2016/plots/MET_study/")
{

  vector<TCut> cuts;
  vector<TString> plot_names;
  vector<TString> plot_titles;
  vector<TString> plot_vars;

  //============================================
  // Define plots
  //============================================

  // Photon Pt in Barrel
  plot_names.push_back("ph_0013_phi");
  plot_vars.push_back("phpfcands_0013_phi");
  plot_titles.push_back("Photon MET-Phi in Barrel");
  cuts.push_back("phpfcands_0013_pt > 0 && nlep >= 2 && lep_pt[0] > 20 && lep_pt[1] > 20 && abs(lep_p4[0].eta()) < 1.3 && abs(lep_p4[1].eta()) < 1.3 && dRll > 0.1 && evt_type == 0 && (( HLT_DoubleMu || HLT_DoubleMu_tk || HLT_DoubleMu_noiso ) && hyp_type == 1 ) || (( HLT_DoubleEl_DZ || HLT_DoubleEl_noiso ) && hyp_type == 0) && evt_passgoodrunlist > 0");

  // Charged Hadron Pt in Barrel
  plot_names.push_back("ch_0013_phi");
  plot_vars.push_back("chpfcands_0013_phi");
  plot_titles.push_back("Charged Hadron MET-Phi in Barrel");
  cuts.push_back("chpfcands_0013_pt > 0 && nlep >= 2 && lep_pt[0] > 20 && lep_pt[1] > 20 && abs(lep_p4[0].eta()) < 1.3 && abs(lep_p4[1].eta()) < 1.3 && dRll > 0.1 && evt_type == 0 && (( HLT_DoubleMu || HLT_DoubleMu_tk || HLT_DoubleMu_noiso ) && hyp_type == 1 ) || (( HLT_DoubleEl_DZ || HLT_DoubleEl_noiso ) && hyp_type == 0) && evt_passgoodrunlist > 0");

  // Neutral Hadron Pt in Barrel
  plot_names.push_back("nu_0013_phi");
  plot_vars.push_back("nupfcands_0013_phi");
  plot_titles.push_back("Neutral Hadron MET-Phi in Barrel");
  cuts.push_back("nupfcands_0013_pt > 0 && nlep >= 2 && lep_pt[0] > 20 && lep_pt[1] > 20 && abs(lep_p4[0].eta()) < 1.3 && abs(lep_p4[1].eta()) < 1.3 && dRll > 0.1 && evt_type == 0 && (( HLT_DoubleMu || HLT_DoubleMu_tk || HLT_DoubleMu_noiso ) && hyp_type == 1 ) || (( HLT_DoubleEl_DZ || HLT_DoubleEl_noiso ) && hyp_type == 0) && evt_passgoodrunlist > 0");

  // Photon Pt in Endcap
  plot_names.push_back("ph_1624_phi");
  plot_vars.push_back("phpfcands_1624_phi");
  plot_titles.push_back("Photon MET-Phi in Endcap");
  cuts.push_back("phpfcands_1624_pt > 0 && nlep >= 2 && lep_pt[0] > 20 && lep_pt[1] > 20 && abs(lep_p4[0].eta()) < 1.3 && abs(lep_p4[1].eta()) < 1.3 && dRll > 0.1 && evt_type == 0 && (( HLT_DoubleMu || HLT_DoubleMu_tk || HLT_DoubleMu_noiso ) && hyp_type == 1 ) || (( HLT_DoubleEl_DZ || HLT_DoubleEl_noiso ) && hyp_type == 0) && evt_passgoodrunlist > 0");

  // Charged Hadron Pt in Endcap
  plot_names.push_back("ch_1624_phi");
  plot_vars.push_back("chpfcands_1624_phi");
  plot_titles.push_back("Charged Hadron MET-Phi in Endcap");
  cuts.push_back("chpfcands_1624_pt > 0 && nlep >= 2 && lep_pt[0] > 20 && lep_pt[1] > 20 && abs(lep_p4[0].eta()) < 1.3 && abs(lep_p4[1].eta()) < 1.3 && dRll > 0.1 && evt_type == 0 && (( HLT_DoubleMu || HLT_DoubleMu_tk || HLT_DoubleMu_noiso ) && hyp_type == 1 ) || (( HLT_DoubleEl_DZ || HLT_DoubleEl_noiso ) && hyp_type == 0) && evt_passgoodrunlist > 0");

  // Neutral Hadron Pt in Endcap
  plot_names.push_back("nu_1624_phi");
  plot_vars.push_back("nupfcands_1624_phi");
  plot_titles.push_back("Neutral Hadron MET-Phi in Endcap");
  cuts.push_back("nupfcands_1624_pt > 0 && nlep >= 2 && lep_pt[0] > 20 && lep_pt[1] > 20 && abs(lep_p4[0].eta()) < 1.3 && abs(lep_p4[1].eta()) < 1.3 && dRll > 0.1 && evt_type == 0 && (( HLT_DoubleMu || HLT_DoubleMu_tk || HLT_DoubleMu_noiso ) && hyp_type == 1 ) || (( HLT_DoubleEl_DZ || HLT_DoubleEl_noiso ) && hyp_type == 0) && evt_passgoodrunlist > 0");

  // Photon Pt in Forward Endcap (No Tracker)
  plot_names.push_back("ph_2430_phi");
  plot_vars.push_back("phpfcands_2430_phi");
  plot_titles.push_back("Photon MET-Phi in Forward Endcap (No Tracker)");
  cuts.push_back("phpfcands_2430_pt > 0 && nlep >= 2 && lep_pt[0] > 20 && lep_pt[1] > 20 && abs(lep_p4[0].eta()) < 1.3 && abs(lep_p4[1].eta()) < 1.3 && dRll > 0.1 && evt_type == 0 && (( HLT_DoubleMu || HLT_DoubleMu_tk || HLT_DoubleMu_noiso ) && hyp_type == 1 ) || (( HLT_DoubleEl_DZ || HLT_DoubleEl_noiso ) && hyp_type == 0) && evt_passgoodrunlist > 0");

  // Charged Hadron Pt in Forward Endcap (No Tracker)
  plot_names.push_back("ch_2430_phi");
  plot_vars.push_back("chpfcands_2430_phi");
  plot_titles.push_back("Charged Hadron MET-Phi in Forward Endcap (No Tracker)");
  cuts.push_back("chpfcands_2430_pt > 0 && nlep >= 2 && lep_pt[0] > 20 && lep_pt[1] > 20 && abs(lep_p4[0].eta()) < 1.3 && abs(lep_p4[1].eta()) < 1.3 && dRll > 0.1 && evt_type == 0 && (( HLT_DoubleMu || HLT_DoubleMu_tk || HLT_DoubleMu_noiso ) && hyp_type == 1 ) || (( HLT_DoubleEl_DZ || HLT_DoubleEl_noiso ) && hyp_type == 0) && evt_passgoodrunlist > 0");

  // Neutral Hadron Pt in Forward Endcap (No Tracker)
  plot_names.push_back("nu_2430_phi");
  plot_vars.push_back("nupfcands_2430_phi");
  plot_titles.push_back("Neutral Hadron MET-Phi in Forward Endcap (No Tracker)");
  cuts.push_back("nupfcands_2430_pt > 0 && nlep >= 2 && lep_pt[0] > 20 && lep_pt[1] > 20 && abs(lep_p4[0].eta()) < 1.3 && abs(lep_p4[1].eta()) < 1.3 && dRll > 0.1 && evt_type == 0 && (( HLT_DoubleMu || HLT_DoubleMu_tk || HLT_DoubleMu_noiso ) && hyp_type == 1 ) || (( HLT_DoubleEl_DZ || HLT_DoubleEl_noiso ) && hyp_type == 0) && evt_passgoodrunlist > 0");


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
  // Draw Histograms
  //============================================

  TFile * output = new TFile(save_dir+"METStudy_phi.root", "recreate");

  while(!cuts.empty()){
    TCut selection = cuts.back();
    TString plot_variable = plot_vars.back();
    TString plot_name = plot_names.back();
    TString plot_title = plot_titles.back();

    cuts.pop_back();
    plot_vars.pop_back();
    plot_names.pop_back();
    plot_titles.pop_back();

    TH1F * zjets = new TH1F("zjets_"+plot_name, plot_title, 40, -3.14 ,3.14);
    TH1F * fsbkg = new TH1F("fsbkg_"+plot_name, plot_title, 40, -3.14 ,3.14);
    TH1F * data = new TH1F("data_"+plot_name, plot_title, 40, -3.14 ,3.14);
 
    zjets->Sumw2();
    fsbkg->Sumw2();

    ch_zjets->Draw(plot_variable+">>zjets_"+plot_name    ,  selection          *weight);
    ch_fsbkg->Draw(plot_variable+">>fsbkg_"+plot_name    ,  selection          *weight);
    ch_data->Draw(plot_variable+">>data_"+plot_name    ,  selection);
    
    data->GetYaxis()->SetTitle("Count / [2Pi/40]");
    data->GetXaxis()->SetTitle("MET-Phi (Radians)");

    zjets->Write();
    fsbkg->Write();
    data->Write();

    delete zjets;
    delete fsbkg;
    delete data;
}
  output->Close();
  delete output;
  return;
}
