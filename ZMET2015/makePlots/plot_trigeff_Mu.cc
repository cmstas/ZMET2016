#include "TFile.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TLegend.h"
#include "TString.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TEfficiency.h"
//#include "tdrstyle_SUSY.C"


void plot_trigeff_Mu (const TString& indir = "/nfs-7/userdata/leptonTree/v2.11Muon20GeV/") {

//  gROOT->ProcessLine(".L ./tdrstyle_SUSY.C");
  
//  setTDRStyle();
  
  TH1::SetDefaultSumw2();
  
  TChain* t_ele = new TChain("t");

  double xbins[47] = {10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,75,100,150,200,300,510};  
  //double xbins[28] = {25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,75,100};  
  // t_ele->Add(Form("%s/2016*SingleMu_R.root", indir.Data()));
  t_ele->Add(Form("%s/2016*SingleMu_R.root", indir.Data()));
  // t_ele->Add(Form("%s/2016GSingleMu_R.root", indir.Data()));
  t_ele->Add(Form("%s/2016H1SingleMu_P.root", indir.Data()));
  t_ele->Add(Form("%s/2016H1SingleMu_P_1.root", indir.Data()));
  t_ele->Add(Form("%s/2016H2SingleMu_P.root", indir.Data()));

  string filename = "trigeff_Muon_pt_2016_withH";
  

  TFile* f_out = new TFile("trigeff_Mu.root","RECREATE");
  
  TH1D* h_pt_denom_ele27WPLoose = new TH1D("h_pt_denom_ele27WPLoose",";muon p_{T} [GeV]", 46, xbins);
  TH1D* h_pt_denom_eb_ele27WPLoose = (TH1D*) h_pt_denom_ele27WPLoose->Clone("h_pt_denom_eb_ele27WPLoose");
  TH1D* h_pt_denom_eb_ptvar_ele27WPLoose = (TH1D*) h_pt_denom_ele27WPLoose->Clone("h_pt_denom_eb_ptvar_ele27WPLoose");
  TH1D* h_pt_denom_eb_massvar_ele27WPLoose = (TH1D*) h_pt_denom_ele27WPLoose->Clone("h_pt_denom_eb_massvar_ele27WPLoose");
  TH1D* h_pt_denom_eb_njetvar_ele27WPLoose = (TH1D*) h_pt_denom_ele27WPLoose->Clone("h_pt_denom_eb_njetvar_ele27WPLoose");
  TH1D* h_pt_denom_ee_ele27WPLoose = (TH1D*) h_pt_denom_ele27WPLoose->Clone("h_pt_denom_ee_ele27WPLoose");
  TH1D* h_pt_denom_ee_ptvar_ele27WPLoose = (TH1D*) h_pt_denom_ele27WPLoose->Clone("h_pt_denom_ee_ptvar_ele27WPLoose");
  TH1D* h_pt_denom_ee_njetvar_ele27WPLoose = (TH1D*) h_pt_denom_ele27WPLoose->Clone("h_pt_denom_ee_njetvar_ele27WPLoose");

  TH1D* h_pt_num_ele27WPLoose = (TH1D*) h_pt_denom_ele27WPLoose->Clone("h_pt_num_ele27WPLoose");
  TH1D* h_pt_num_eb_ele27WPLoose = (TH1D*) h_pt_denom_ele27WPLoose->Clone("h_pt_num_eb_ele27WPLoose");
  TH1D* h_pt_num_eb_ptvar_ele27WPLoose = (TH1D*) h_pt_num_ele27WPLoose->Clone("h_pt_num_eb_ptvar_ele27WPLoose");
  TH1D* h_pt_num_eb_njetvar_ele27WPLoose = (TH1D*) h_pt_num_ele27WPLoose->Clone("h_pt_num_eb_njetvar_ele27WPLoose");
  TH1D* h_pt_num_eb_massvar_ele27WPLoose = (TH1D*) h_pt_num_ele27WPLoose->Clone("h_pt_num_eb_massvar_ele27WPLoose");
  TH1D* h_pt_denom_ee_massvar_ele27WPLoose = (TH1D*) h_pt_denom_ele27WPLoose->Clone("h_pt_denom_ee_massvar_ele27WPLoose");
  TH1D* h_pt_num_ee_massvar_ele27WPLoose = (TH1D*) h_pt_num_ele27WPLoose->Clone("h_pt_num_ee_massvar_ele27WPLoose");

  TH1D* h_pt_num_ee_ele27WPLoose = (TH1D*) h_pt_denom_ele27WPLoose->Clone("h_pt_num_ee_ele27WPLoose");
  TH1D* h_pt_num_ee_ptvar_ele27WPLoose = (TH1D*) h_pt_num_ele27WPLoose->Clone("h_pt_num_ee_ptvar_ele27WPLoose");
  TH1D* h_pt_num_ee_njetvar_ele27WPLoose = (TH1D*) h_pt_num_ele27WPLoose->Clone("h_pt_num_ee_njetvar_ele27WPLoose");

  TCanvas* c = new TCanvas("c","c");
  c->SetGrid(1,1);
  c->cd();

  TCut ID = "passes_POG_mediumID && miniiso<0.2 && abs(ip3d)/ip3derr < 8 && dxyPV<0.05 && dZ<0.1";
  //TCut tag = "abs(p4.eta())<2.5 && tag_p4.pt()>30 && (tag_HLT_IsoTkMu22>0||tag_HLT_IsoMu22>0||tag_HLT_Mu45_eta2p1>0||tag_HLT_Mu50>0)"+ID;
  //TCut tag = "abs(p4.eta())<2.5 && tag_p4.pt()>30 && (tag_HLT_IsoTkMu22>0||tag_HLT_IsoMu22>0)"+ID;
  // TCut tag = "abs(tag_p4.eta())<1.4 && tag_p4.pt()>30 && (tag_HLT_IsoMu24 || tag_HLT_IsoTkMu24)&& evt_run > 277428"+ID;
  TCut tag = "abs(tag_p4.eta())<1.4 && tag_p4.pt()>30 && (tag_HLT_IsoMu24 || tag_HLT_IsoTkMu24)"+ID;
  // && acos(cos(tag_p4.phi()-p4.phi()))>1.05
  TCut base = "dilep_mass>70 && dilep_mass<110"+tag;
  TCut eb = base+"abs(p4.eta()) < 1.4";
  TCut ee = base+"abs(p4.eta()) > 1.6 && abs(p4.eta()) < 2.4";
//  TCut trig="(HLT_IsoTkMu22>0||HLT_IsoMu22>0)";
  TCut trig="(HLT_IsoTkMu24>0||HLT_IsoMu24>0)";
  t_ele->Draw("p4.pt()>>h_pt_denom_ele27WPLoose",base);
  t_ele->Draw("p4.pt()>>h_pt_num_ele27WPLoose",base+trig);

  t_ele->Draw("p4.pt()>>h_pt_denom_eb_ele27WPLoose",base+eb);
  t_ele->Draw("p4.pt()>>h_pt_num_eb_ele27WPLoose",base+eb+trig);
  // t_ele->Draw("p4.pt()>>h_pt_denom_eb_njetvar_ele27WPLoose",base+eb+"njets==2");
  // t_ele->Draw("p4.pt()>>h_pt_num_eb_njetvar_ele27WPLoose",base+eb+trig+"njets==2");
  // t_ele->Draw("p4.pt()>>h_pt_denom_eb_ptvar_ele27WPLoose",base+eb+"tag_p4.pt()>40");
  // t_ele->Draw("p4.pt()>>h_pt_num_eb_ptvar_ele27WPLoose",base+eb+trig+"tag_p4.pt()>40");
  // t_ele->Draw("p4.pt()>>h_pt_denom_eb_massvar_ele27WPLoose",base+eb+"dilep_mass>76 && dilep_mass<106");
  // t_ele->Draw("p4.pt()>>h_pt_num_eb_massvar_ele27WPLoose",base+eb+"dilep_mass>76 && dilep_mass<106"+trig);

  // t_ele->Draw("p4.pt()>>h_pt_denom_ee_massvar_ele27WPLoose",base+ee+"dilep_mass>76 && dilep_mass<106");
  // t_ele->Draw("p4.pt()>>h_pt_num_ee_massvar_ele27WPLoose",base+ee+"dilep_mass>76 && dilep_mass<106"+trig);

  t_ele->Draw("p4.pt()>>h_pt_denom_ee_ele27WPLoose",base+ee);
  t_ele->Draw("p4.pt()>>h_pt_num_ee_ele27WPLoose",base+ee+trig);
  // t_ele->Draw("p4.pt()>>h_pt_denom_ee_njetvar_ele27WPLoose",base+ee+"njets==2");
  // t_ele->Draw("p4.pt()>>h_pt_num_ee_njetvar_ele27WPLoose",base+ee+trig+"njets==2");
  // t_ele->Draw("p4.pt()>>h_pt_denom_ee_ptvar_ele27WPLoose",base+ee+"tag_p4.pt()>40");
  // t_ele->Draw("p4.pt()>>h_pt_num_ee_ptvar_ele27WPLoose",base+ee+trig+"tag_p4.pt()>40");


  TH2F* h_axis = new TH2F("h_axis",";muon p_{T} [GeV];Efficiency",20,10,510,20,0.,1);
  h_axis->GetXaxis()->SetMoreLogLabels();
  h_axis->Draw();
  
  // TH1D* h_pt_effi_ele27WPLoose = (TH1D*) h_pt_num_ele27WPLoose->Clone("h_pt_effi_ele27WPLoose");
  // TH1D* h_pt_effi_eb_ele27WPLoose = (TH1D*) h_pt_num_eb_ele27WPLoose->Clone("h_pt_effi_eb_ele27WPLoose");
  // TH1D* h_pt_effi_ee_ele27WPLoose = (TH1D*) h_pt_num_ee_ele27WPLoose->Clone("h_pt_effi_ee_ele27WPLoose");
  // h_pt_effi_ele27WPLoose->Divide(h_pt_denom_ele27WPLoose);
  // h_pt_effi_eb_ele27WPLoose->Divide(h_pt_denom_eb_ele27WPLoose);
  // h_pt_effi_ee_ele27WPLoose->Divide(h_pt_denom_ee_ele27WPLoose);
  TEfficiency* h_pt_eff_ele27WPLoose = new TEfficiency(*h_pt_num_ele27WPLoose, *h_pt_denom_ele27WPLoose);
  h_pt_eff_ele27WPLoose->  SetLineColor(kBlack);
  h_pt_eff_ele27WPLoose->SetMarkerColor(kBlack);

  h_pt_eff_ele27WPLoose->Draw("pe same");

  TEfficiency* h_pt_eff_ee_ele27WPLoose = new TEfficiency(*h_pt_num_ee_ele27WPLoose, *h_pt_denom_ee_ele27WPLoose);
  h_pt_eff_ee_ele27WPLoose->  SetLineColor(kBlue);
  h_pt_eff_ee_ele27WPLoose->SetMarkerColor(kBlue);

  h_pt_eff_ee_ele27WPLoose->Draw("pe same");

  TEfficiency* h_pt_eff_eb_ele27WPLoose = new TEfficiency(*h_pt_num_eb_ele27WPLoose, *h_pt_denom_eb_ele27WPLoose);
  h_pt_eff_eb_ele27WPLoose->  SetLineColor(kRed);
  h_pt_eff_eb_ele27WPLoose->SetMarkerColor(kRed);

  h_pt_eff_eb_ele27WPLoose->Draw("pe same");
  
  TLegend* leg = new TLegend(0.6,0.2,0.9,0.5);
  leg->AddEntry(h_pt_eff_ele27WPLoose,"muons, all #eta","pe");
  leg->AddEntry(h_pt_eff_ee_ele27WPLoose,"muons, endcap","pe");
  leg->AddEntry(h_pt_eff_eb_ele27WPLoose,"muons, barrel","pe");
  //leg->AddEntry(h_pt_eff_ele27WPLoose,"IsoMu24_eta2p1||IsoTkMu24_eta2p1||IsoMu24||IsoTkMu24","pe");
  leg->Draw("same");

  c->SaveAs(Form("../output/ZMET2015/V08-22-05/plots/Closure/%s.pdf", filename.c_str() ));
  c->SaveAs(Form("../output/ZMET2015/V08-22-05/plots/Closure/%s.png", filename.c_str() ));

  TFile * outfile = TFile::Open(Form("%s.root", filename.c_str()),"RECREATE");
  outfile->cd();
  h_pt_eff_eb_ele27WPLoose->  Write();
  h_pt_eff_eb_ele27WPLoose->  Write();
  h_pt_eff_eb_ele27WPLoose->  Write();
  h_pt_eff_ee_ele27WPLoose->  Write();
  h_pt_eff_ee_ele27WPLoose->  Write();
  h_pt_eff_ee_ele27WPLoose->  Write();
  h_pt_eff_ele27WPLoose->  Write();
  h_pt_eff_ele27WPLoose->  Write();
  h_pt_eff_ele27WPLoose->  Write();
  outfile->Write();
  
  // split into EB and EE
  
  // TCanvas* c_eb = new TCanvas("c_eb","c_eb");
  // c_eb->SetGrid(1,1);
  // c_eb->cd();

  // h_axis->Draw();


  // TEfficiency* h_pt_eff_eb_ele27WPLoose = new TEfficiency(*h_pt_num_eb_ele27WPLoose, *h_pt_denom_eb_ele27WPLoose);
  // TEfficiency* h_pt_eff_eb_ptvar_ele27WPLoose = new TEfficiency(*h_pt_num_eb_ptvar_ele27WPLoose, *h_pt_denom_eb_ptvar_ele27WPLoose);
  // TEfficiency* h_pt_eff_eb_njetvar_ele27WPLoose = new TEfficiency(*h_pt_num_eb_njetvar_ele27WPLoose, *h_pt_denom_eb_njetvar_ele27WPLoose);
  // TEfficiency* h_pt_eff_eb_massvar_ele27WPLoose = new TEfficiency(*h_pt_num_eb_massvar_ele27WPLoose, *h_pt_denom_eb_massvar_ele27WPLoose);

  // h_pt_eff_eb_ele27WPLoose->SetLineColor(kGreen+2);
  // h_pt_eff_eb_ele27WPLoose->SetMarkerColor(kGreen+2);
  // h_pt_eff_eb_ptvar_ele27WPLoose->SetLineColor(kMagenta);
  // h_pt_eff_eb_ptvar_ele27WPLoose->SetMarkerColor(kMagenta);
  // h_pt_eff_eb_njetvar_ele27WPLoose->SetLineColor(kBlue);
  // h_pt_eff_eb_njetvar_ele27WPLoose->SetMarkerColor(kBlue);
  // h_pt_eff_eb_massvar_ele27WPLoose->SetLineColor(kRed);
  // h_pt_eff_eb_massvar_ele27WPLoose->SetMarkerColor(kRed);
  // h_pt_eff_eb_ptvar_ele27WPLoose->Draw("pe same");
  // h_pt_eff_eb_massvar_ele27WPLoose->Draw("pe same");
  // h_pt_eff_eb_njetvar_ele27WPLoose->Draw("pe same");
  // h_pt_eff_eb_ele27WPLoose->Draw("pe same");
  // TLegend* leg_eb = new TLegend(0.6,0.2,0.9,0.5);
  // leg_eb->AddEntry(h_pt_eff_eb_ele27WPLoose,"Muons, |#eta| < 1.2","pe");
  // leg_eb->AddEntry(h_pt_eff_eb_ptvar_ele27WPLoose,"Muons, vary tag pt","pe");
  // leg_eb->AddEntry(h_pt_eff_eb_njetvar_ele27WPLoose,"Muons, njets==2","pe");
  // leg_eb->AddEntry(h_pt_eff_eb_massvar_ele27WPLoose,"Muons,vary mass window","pe");
  // leg_eb->Draw("same");
  // c_eb->SetLogx();
  // c_eb->SaveAs("trigeff_Mu_EB_var_unzoom.pdf");

  // c_eb->SetLogx(0);
  // h_axis->GetXaxis()->SetRangeUser(10,70);
  // h_axis->GetYaxis()->SetRangeUser(0.75,1.0);
  // gPad->Modified();
  // c_eb->SaveAs("trigeff_Mu_EB_var_zoom.pdf");

  
  // TCanvas* c_ee = new TCanvas("c_ee","c_ee");
  // c_ee->SetGrid(1,1);
  // c_ee->cd();

  // h_axis->GetXaxis()->SetRangeUser(0,1000);
  // h_axis->GetYaxis()->SetRangeUser(0.,1.0);
  // h_axis->Draw();

  // TEfficiency* h_pt_eff_ee_ele27WPLoose = new TEfficiency(*h_pt_num_ee_ele27WPLoose, *h_pt_denom_ee_ele27WPLoose);
  // TEfficiency* h_pt_eff_ee_massvar_ele27WPLoose = new TEfficiency(*h_pt_num_ee_massvar_ele27WPLoose, *h_pt_denom_ee_massvar_ele27WPLoose);
  // TEfficiency* h_pt_eff_ee_ptvar_ele27WPLoose = new TEfficiency(*h_pt_num_ee_ptvar_ele27WPLoose, *h_pt_denom_ee_ptvar_ele27WPLoose);
  // TEfficiency* h_pt_eff_ee_njetvar_ele27WPLoose = new TEfficiency(*h_pt_num_ee_njetvar_ele27WPLoose, *h_pt_denom_ee_njetvar_ele27WPLoose);

  // h_pt_eff_ee_ele27WPLoose->SetLineColor(kGreen+2);
  // h_pt_eff_ee_ele27WPLoose->SetMarkerColor(kGreen+2);
  // h_pt_eff_ee_ptvar_ele27WPLoose->SetLineColor(kMagenta);
  // h_pt_eff_ee_ptvar_ele27WPLoose->SetMarkerColor(kMagenta);
  // h_pt_eff_ee_njetvar_ele27WPLoose->SetLineColor(kBlue);
  // h_pt_eff_ee_njetvar_ele27WPLoose->SetMarkerColor(kBlue);
  // h_pt_eff_ee_massvar_ele27WPLoose->SetLineColor(kRed);
  // h_pt_eff_ee_massvar_ele27WPLoose->SetMarkerColor(kRed);
  // h_axis->Draw();
  // h_pt_eff_ee_massvar_ele27WPLoose->Draw("pe same");
  // h_pt_eff_ee_ptvar_ele27WPLoose->Draw("pe same");
  // h_pt_eff_ee_njetvar_ele27WPLoose->Draw("pe same");
  // h_pt_eff_ee_ele27WPLoose->Draw("pe same");
  // TLegend* leg_ee = new TLegend(0.6,0.2,0.9,0.5);
  // leg_ee->AddEntry(h_pt_eff_ee_ele27WPLoose,"Muons, 1.2 < |#eta| < 2.1","pe");
  // leg_ee->AddEntry(h_pt_eff_ee_ptvar_ele27WPLoose,"Muons, vary tag pt","pe");
  // leg_ee->AddEntry(h_pt_eff_ee_massvar_ele27WPLoose,"Muons,vary mass","pe");
  // leg_ee->AddEntry(h_pt_eff_ee_njetvar_ele27WPLoose,"Muons, njets==2","pe");
  // leg_ee->Draw("same");
  // c_ee->SetLogx();
  // c_ee->SaveAs("../output/ZMET2015/V08-22-05/plots/Closure/trigeff_Mu_EE_var_unzoom.pdf");
  // //c_ee->SaveAs("trigeff_Mu_EE_var_unzoom.pdf");
  
  // c_ee->SetLogx(0);
  // h_axis->GetXaxis()->SetRangeUser(10,70);
  // h_axis->GetYaxis()->SetRangeUser(0.75,1.0);
  // gPad->Modified();
  // c_ee->SaveAs("trigeff_Mu_EE_var_zoom.pdf");
  
  // f_out->Write();
  // f_out->Close();
  
  return;
  
}
