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

void METStudy_all(TString save_dir = "~/public_html/ZMET2016/plots/MET_study/V07-06-06/")
{

  TCut base_cut = "dilmass < 101 && dilmass > 81 && nlep >= 2 && lep_pt[0] > 20 && lep_pt[1] > 20 && abs(lep_p4[0].eta()) < 2.4 && abs(lep_p4[1].eta()) < 2.4 && dRll > 0.1 && evt_type == 0 && (( HLT_DoubleMu || HLT_DoubleMu_tk || HLT_DoubleMu_noiso ) && hyp_type == 1 ) || (( HLT_DoubleEl_DZ || HLT_DoubleEl_noiso ) && hyp_type == 0) && evt_passgoodrunlist > 0";

  vector<TCut> cuts;
  vector<TString> plot_names;
  vector<TString> plot_titles;
  vector<TString> plot_vars;
  vector<TString> plot_types;

  //============================================
  // Define plots
  //============================================

  // Photon MET-Phi in Barrel
  plot_names.push_back("ph_0013_phi");
  plot_vars.push_back("phpfcands_0013_phi");
  plot_titles.push_back("Photon MET-Phi in Barrel");
  cuts.push_back(base_cut+"phpfcands_0013_pt > 0");
  plot_types.push_back("phi");

  // Charged Hadron MET-Phi in Barrel
  plot_names.push_back("ch_0013_phi");
  plot_vars.push_back("chpfcands_0013_phi");
  plot_titles.push_back("Charged Hadron MET-Phi in Barrel");
  cuts.push_back(base_cut+"chpfcands_0013_pt > 0");
  plot_types.push_back("phi");

  // Neutral Hadron MET-Phi in Barrel
  plot_names.push_back("nu_0013_phi");
  plot_vars.push_back("nupfcands_0013_phi");
  plot_titles.push_back("Neutral Hadron MET-Phi in Barrel");
  cuts.push_back(base_cut+"nupfcands_0013_pt > 0");
  plot_types.push_back("phi");

  // Photon MET-Phi in Endcap
  plot_names.push_back("ph_1624_phi");
  plot_vars.push_back("phpfcands_1624_phi");
  plot_titles.push_back("Photon MET-Phi in Endcap");
  cuts.push_back(base_cut+"phpfcands_1624_pt > 0");
  plot_types.push_back("phi");

  // Charged Hadron MET-Phi in Endcap
  plot_names.push_back("ch_1624_phi");
  plot_vars.push_back("chpfcands_1624_phi");
  plot_titles.push_back("Charged Hadron MET-Phi in Endcap");
  cuts.push_back(base_cut+"chpfcands_1624_pt > 0");
  plot_types.push_back("phi");

  // Neutral Hadron MET-Phi in Endcap
  plot_names.push_back("nu_1624_phi");
  plot_vars.push_back("nupfcands_1624_phi");
  plot_titles.push_back("Neutral Hadron MET-Phi in Endcap");
  cuts.push_back(base_cut+"nupfcands_1624_pt > 0");
  plot_types.push_back("phi");

  // Photon MET-Phi in Forward Endcap (No Tracker)
  plot_names.push_back("ph_2430_phi");
  plot_vars.push_back("phpfcands_2430_phi");
  plot_titles.push_back("Photon MET-Phi in Forward Endcap (No Tracker)");
  cuts.push_back(base_cut+"phpfcands_2430_pt > 0");
  plot_types.push_back("phi");

  // Charged Hadron MET-Phi in Forward Endcap (No Tracker)
  plot_names.push_back("ch_2430_phi");
  plot_vars.push_back("chpfcands_2430_phi");
  plot_titles.push_back("Charged Hadron MET-Phi in Forward Endcap (No Tracker)");
  cuts.push_back(base_cut+"chpfcands_2430_pt > 0");
  plot_types.push_back("phi");

  // Neutral Hadron MET-Phi in Forward Endcap (No Tracker)
  plot_names.push_back("nu_2430_phi");
  plot_vars.push_back("nupfcands_2430_phi");
  plot_titles.push_back("Neutral Hadron MET-Phi in Forward Endcap (No Tracker)");
  cuts.push_back(base_cut+"nupfcands_2430_pt > 0");
  plot_types.push_back("phi");

  // Raw Met
  plot_names.push_back("MET");
  plot_vars.push_back("met_rawPt");
  plot_titles.push_back("Raw MET in barrel for all events in study.");
  cuts.push_back(base_cut+"met_rawPt>0");
  plot_types.push_back("pt");

  // Raw Met With at least 2 jets
  plot_names.push_back("MET_2Jets");
  plot_vars.push_back("met_rawPt");
  plot_titles.push_back("Raw MET in barrel for all events in study with a minimum 2 jet requirement.");
  cuts.push_back(base_cut+"met_rawPt>0");
  plot_types.push_back("pt");

  // Photon Pt in Barrel
  plot_names.push_back("ph_0013_pt");
  plot_vars.push_back("phpfcands_0013_pt");
  plot_titles.push_back("Photon Pt in Barrel");
  cuts.push_back(base_cut+"phpfcands_0013_pt>0");
  plot_types.push_back("pt");

  // Charged Hadron Pt in Barrel
  plot_names.push_back("ch_0013_pt");
  plot_vars.push_back("chpfcands_0013_pt");
  plot_titles.push_back("Charged Hadron Pt in Barrel");
  cuts.push_back(base_cut+"chpfcands_0013_pt>0");
  plot_types.push_back("pt");

  // Neutral Hadron Pt in Barrel
  plot_names.push_back("nu_0013_pt");
  plot_vars.push_back("nupfcands_0013_pt");
  plot_titles.push_back("Neutral Hadron Pt in Barrel");
  cuts.push_back(base_cut+"nupfcands_0013_pt>0");
  plot_types.push_back("pt");

  // Photon Pt in Endcap
  plot_names.push_back("ph_1624_pt");
  plot_vars.push_back("phpfcands_1624_pt");
  plot_titles.push_back("Photon Pt in Endcap");
  cuts.push_back(base_cut+"phpfcands_1624_pt>0");
  plot_types.push_back("pt");

  // Charged Hadron Pt in Endcap
  plot_names.push_back("ch_1624_pt");
  plot_vars.push_back("chpfcands_1624_pt");
  plot_titles.push_back("Charged Hadron Pt in Endcap");
  cuts.push_back(base_cut+"chpfcands_1624_pt>0");
  plot_types.push_back("pt");

  // Neutral Hadron Pt in Endcap
  plot_names.push_back("nu_1624_pt");
  plot_vars.push_back("nupfcands_1624_pt");
  plot_titles.push_back("Neutral Hadron Pt in Endcap");
  cuts.push_back(base_cut+"nupfcands_1624_pt>0");
  plot_types.push_back("pt");

  // Photon Pt in Forward Endcap (No Tracker)
  plot_names.push_back("ph_2430_pt");
  plot_vars.push_back("phpfcands_2430_pt");
  plot_titles.push_back("Photon Pt in Forward Endcap (No Tracker)");
  cuts.push_back(base_cut+"phpfcands_2430_pt>0");
  plot_types.push_back("pt");

  // Charged Hadron Pt in Forward Endcap (No Tracker)
  plot_names.push_back("ch_2430_pt");
  plot_vars.push_back("chpfcands_2430_pt");
  plot_titles.push_back("Charged Hadron Pt in Forward Endcap (No Tracker)");
  cuts.push_back(base_cut+"chpfcands_2430_pt>0");
  plot_types.push_back("pt");

  // Neutral Hadron Pt in Forward Endcap (No Tracker)
  plot_names.push_back("nu_2430_pt");
  plot_vars.push_back("nupfcands_2430_pt");
  plot_titles.push_back("Neutral Hadron Pt in Forward Endcap (No Tracker)");
  cuts.push_back(base_cut+"nupfcands_2430_pt>0");
  plot_types.push_back("pt");

  // Neutral Hadron Pt in Forward Calorimeter (|eta| > 3)
  plot_names.push_back("nu_30in_pt");
  plot_vars.push_back("nupfcands_30in_pt");
  plot_titles.push_back("Neutral Hadron Pt in Forward Endcap (No Tracker)");
  cuts.push_back(base_cut+"nupfcands_30in_pt>0");
  plot_types.push_back("pt");

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

  TFile * output = new TFile(save_dir+"METStudy_all.root", "recreate");

  while(!cuts.empty()){
    TCut selection = cuts.back();
    TString plot_variable = plot_vars.back();
    TString plot_name = plot_names.back();
    TString plot_title = plot_titles.back();
    TString plot_type = plot_types.back();

    cuts.pop_back();
    plot_vars.pop_back();
    plot_names.pop_back();
    plot_titles.pop_back();
    plot_types.pop_back();

    TH1F *zjets;
    TH1F *fsbkg;
    TH1F *data;
    if (plot_type == "phi"){
      zjets = new TH1F("zjets_"+plot_name, plot_title, 40, -3.15 ,3.15);
      fsbkg = new TH1F("fsbkg_"+plot_name, plot_title, 40, -3.15 ,3.15);
      data = new TH1F("data_"+plot_name, plot_title, 40, -3.15 ,3.15);
    }

    else if (plot_type == "pt") {
      zjets = new TH1F("zjets_"+plot_name, plot_title, 500, 0 ,500);
      fsbkg = new TH1F("fsbkg_"+plot_name, plot_title, 500, 0 ,500);
      data = new TH1F("data_"+plot_name, plot_title, 500, 0 ,500);

      zjets->Rebin(5);
      fsbkg->Rebin(5);
      data->Rebin(5);
    }

    zjets->Sumw2();
    fsbkg->Sumw2();

    ch_zjets->Draw(plot_variable+">>zjets_"+plot_name    ,  selection          *weight);
    ch_fsbkg->Draw(plot_variable+">>fsbkg_"+plot_name    ,  selection          *weight);
    ch_data->Draw(plot_variable+">>data_"+plot_name    ,  selection);
    
    if (plot_type == "phi"){
      data->GetYaxis()->SetTitle("Count / [2Pi/40]");
      data->GetXaxis()->SetTitle("MET-Phi (Radians)");
    }
    else if (plot_type == "pt") {
      data->GetYaxis()->SetTitle("Count / [5 GeV]");
      data->GetXaxis()->SetTitle("E^{miss}_{T}");
    }
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
