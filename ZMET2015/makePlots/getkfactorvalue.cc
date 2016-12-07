#include <iostream>
#include <stdexcept>

#include "TFile.h"
#include "TCut.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH1.h"
#include "TChain.h"
#include "TColor.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLine.h"
#include "TLegend.h"
#include "TStyle.h"

#include "../sharedCode/histTools.cc"

using namespace std;
pair <double, double>  getonekfactorvalue(string region);
pair <double, double>  getonekfactorvalue_varbin(string region, double lobin, double hibin);

void getkfactorvalue()
{

  vector <string> regionnames;

  regionnames.push_back("baseline: E_{T}^{miss}:100-150 GeV");
  regionnames.push_back("baseline: E_{T}^{miss}:150-250 GeV");
  regionnames.push_back("baseline: E_{T}^{miss}:>250 GeV");
  regionnames.push_back("Strong region, b-veto");
  regionnames.push_back("Strong region, with bs");
  regionnames.push_back("TChiHZ");
  
  vector<pair <double, double> > testvalues;
  // testvalues.push_back(getonekfactorvalue("baseline_MET100"));
  // testvalues.push_back(getonekfactorvalue_varbin("baseline_MET100",0,300));
  testvalues.push_back(getonekfactorvalue_varbin("data/baseline_MET100",100,150));
  testvalues.push_back(getonekfactorvalue_varbin("data/baseline_MET100",150,250));
  testvalues.push_back(getonekfactorvalue_varbin("data/baseline_MET100",250,300));
  testvalues.push_back(getonekfactorvalue_varbin("baseline_MET100",100,150));
  testvalues.push_back(getonekfactorvalue_varbin("baseline_MET100",150,250));
  testvalues.push_back(getonekfactorvalue_varbin("baseline_MET100",250,300));

  vector<string> regions;
  regions.push_back("data/baseline_MET100_0B");
  // regions.push_back("data/baseline_MET100_0B_2j_ht500");
  // regions.push_back("data/baseline_MET100_0B_4j_ht500");
  // regions.push_back("data/baseline_MET100_0B_6j");
  regions.push_back("data/baseline_MET100_MT2100_1B");
  // regions.push_back("data/baseline_MET100_MT2100_1B_2j_ht200");
  // regions.push_back("data/baseline_MET100_MT2100_1B_4j_ht200");
  // regions.push_back("data/baseline_MET100_MT2100_1B_6j");
  // regions.push_back("data/baseline_MET100");
  regions.push_back("data/TChiHZ");
  // regions.push_back("baseline");
  vector<pair <double, double> > values_data;
  for( size_t varind = 0; varind < regions.size(); varind++ ){
  	values_data.push_back(getonekfactorvalue(regions.at(varind)));
  }
  
  regions.clear();
  regions.push_back("baseline_MET100_0B");
  // regions.push_back("baseline_MET100_0B_2j_ht500");
  // regions.push_back("baseline_MET100_0B_4j_ht500");
  // regions.push_back("baseline_MET100_0B_6j");
  regions.push_back("baseline_MET100_MT2100_1B");
  // regions.push_back("baseline_MET100_MT2100_1B_2j_ht200");
  // regions.push_back("baseline_MET100_MT2100_1B_4j_ht200");
  // regions.push_back("baseline_MET100_MT2100_1B_6j");
  // regions.push_back("baseline_MET100");
  regions.push_back("TChiHZ");
  // regions.push_back("baseline");

  vector<pair <double, double> > values;
  for( size_t varind = 0; varind < regions.size(); varind++ ){
  	values.push_back(getonekfactorvalue(regions.at(varind)));
  }

  TCanvas * c1 = new TCanvas("c1","");
  c1->cd();

  TPad *pad = new TPad( "p_main", "p_main", 0.0, 0.0, 1.0, 1.0);
  pad->SetBottomMargin(0.25);
  pad->SetRightMargin(0.15);
  pad->SetTopMargin(0.08);
  pad->SetLeftMargin(0.18);
  pad->Draw();
  pad->cd();

  TH1D * hist   = new TH1D("hist"  ,"", (int)testvalues.size(), 0, (double)testvalues.size());
  TH1D * hist_d = new TH1D("hist_d","", (int)testvalues.size(), 0, (double)testvalues.size());

  for( int binind = 0; binind < testvalues.size(); binind++ ){
	if( binind < 3 ){
	  hist->  SetBinContent(binind+1, testvalues.at(binind+3).first );
	  hist->  SetBinError(  binind+1, testvalues.at(binind+3).second);
	  hist_d->SetBinContent(binind+1, testvalues.at(binind)  .first );
	  hist_d->SetBinError(  binind+1, testvalues.at(binind)  .second);
	}else{
	  hist->  SetBinContent(binind+1, values     .at(binind-3).first );
	  hist->  SetBinError(  binind+1, values     .at(binind-3).second);
	  hist_d->SetBinContent(binind+1, values_data.at(binind-3).first );
	  hist_d->SetBinError(  binind+1, values_data.at(binind-3).second);
	}
	hist  ->GetXaxis()->SetBinLabel(binind+1, regionnames.at(binind).c_str());
	hist_d->GetXaxis()->SetBinLabel(binind+1, regionnames.at(binind).c_str());
  }

  hist->SetLineColor(  kTeal-8);
  hist->SetMarkerColor(kTeal-8);
  hist->SetLineWidth(  2);
  // hist->SetMarkerStyle(27);
  // hist->SetMarkerSize(1.5);

  hist_d->SetLineColor(kBlack);
  hist_d->SetLineWidth(  2);
  hist_d->SetMarkerColor(kBlack);

  hist->GetYaxis()->SetRangeUser(0.0, 0.20);
  hist->GetYaxis()->SetTitle("#kappa factor");
  hist->GetXaxis()->SetTitle("");
  hist->GetXaxis()->SetLabelSize(0.04);
  hist->Draw("e1");
  hist_d->Draw("samee1");

  TLine * central = new TLine(0, 0.065, testvalues.size(), 0.065);
  central->SetLineWidth(2);
  central->Draw("same");

  TLine * central_up = new TLine(0, 0.1, testvalues.size(), 0.1);
  central_up->SetLineStyle(2);
  central_up->Draw("same");

  TLine * central_dn = new TLine(0, 0.03, testvalues.size(), 0.03);
  central_dn->SetLineStyle(2);
  central_dn->Draw("same");

  TLatex *lumitex = NULL;
  float luminosity = 36.5;
  if( luminosity > 0.1 ) lumitex = new TLatex(0.59       , 0.94, Form("%.1f fb^{-1} (13 TeV)", luminosity) );    
  else                   lumitex = new TLatex(0.59 + 0.05, 0.94, "(13 TeV)" );    

  lumitex->SetNDC();    
  lumitex->SetTextSize(0.04);    
  lumitex->SetLineWidth(2);
  lumitex->SetTextFont(42);    
  lumitex->Draw();

  TLatex *cmstex = NULL;
  cmstex = new TLatex(0.21,0.85, "CMS" );    
  cmstex->SetNDC();    
  cmstex->SetTextSize(0.04);    
  cmstex->SetLineWidth(2);
  cmstex->SetTextFont(61);    
  cmstex->Draw();

  cmstex = new TLatex(0.21,0.82, "Preliminary" );    
  cmstex->SetNDC();    
  cmstex->SetTextSize(0.03);    
  cmstex->SetLineWidth(2);
  cmstex->SetTextFont(52);    
  cmstex->Draw();
  
  TLegend *l1 = NULL;
  l1 = new TLegend(0.40, 0.65, 0.55, 0.90);    

  l1->SetLineColor(kWhite);    
  l1->SetShadowColor(kWhite);    
  l1->SetFillColor(kWhite);    
  l1->SetTextFont(42);    
  l1->SetTextSize(0.04);
  l1->AddEntry( hist_d  , "Data" , "pe");
  l1->AddEntry( hist    , "MC"   , "pe");
  l1->Draw("same");

  c1->SaveAs(Form("~/public_html/ZMET2015/PlotsForBobak/data_summary_kfactors.pdf"));
  c1->SaveAs(Form("~/public_html/ZMET2015/PlotsForBobak/data_summary_kfactors.png"));
  
  return;
}

pair <double, double>  getonekfactorvalue(string region = "baseline_MET100")
{
  
  string variable = "type1MET";

  TFile * f_TT_1lep   = NULL;
  TFile * f_TT_dilep  = NULL;
  TFile * f_VVV       = NULL;
  TFile * f_Z_Base    = NULL;
  TFile * f_singletop = NULL;
  TFile * f_ttv       = NULL;
  TFile * f_ttw       = NULL;
  TFile * f_ww        = NULL;
  TFile * f_wz        = NULL;
  TFile * f_zz        = NULL;

  try{
	if( TString(region).Contains("data") ){
	  f_zz        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/EMuData.root"  , region.c_str() ), "READ" );   
	}else{
	  f_TT_1lep   = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/TT_1lep.root"  , region.c_str() ), "READ" );  
	  f_TT_dilep  = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/TT_dilep.root" , region.c_str() ), "READ" ); 
	  f_VVV       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/VVV.root"      , region.c_str() ), "READ" );   
	  f_Z_Base    = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/Z_Base.root"   , region.c_str() ), "READ" );  
	  f_singletop = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/singletop.root", region.c_str() ), "READ" );
	  f_ttv       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/ttv.root"      , region.c_str() ), "READ" );   
	  f_ttw       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/ttw.root"      , region.c_str() ), "READ" );   
	  f_ww        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/ww.root"       , region.c_str() ), "READ" );   
	  f_wz        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/wz.root"       , region.c_str() ), "READ" );   
	  f_zz        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/zz.root"       , region.c_str() ), "READ" );   
	}
  }
  catch ( exception &e ){
	cout<<"could not open file."<<endl;
  }
  
  TH1D * h_mll_TT_1lep   = NULL;
  TH1D * h_mll_TT_dilep  = NULL;
  TH1D * h_mll_VVV       = NULL;
  TH1D * h_mll_Z_Base    = NULL;
  TH1D * h_mll_singletop = NULL;
  TH1D * h_mll_ttv       = NULL;
  TH1D * h_mll_ttw       = NULL;
  TH1D * h_mll_ww        = NULL;
  TH1D * h_mll_wz        = NULL;
  TH1D * h_mll_zz        = NULL;

  TH1D * h_mll_onz       = NULL;
  h_mll_onz       = dynamic_cast<TH1D*>(f_zz        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_onz"            ));

  TH1D * h_mll_all       = NULL;
  h_mll_all       = dynamic_cast<TH1D*>(f_zz        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_all"            ));

  try{
	if( !TString(region).Contains("data") ){
	  h_mll_TT_1lep   = dynamic_cast<TH1D*>(f_TT_1lep   -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_TT_1lep_met50"  ));
	  h_mll_TT_dilep  = dynamic_cast<TH1D*>(f_TT_dilep  -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_TT_dilep_met50" ));
	  h_mll_VVV       = dynamic_cast<TH1D*>(f_VVV       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_VVV_met50"      ));
	  h_mll_Z_Base    = dynamic_cast<TH1D*>(f_Z_Base    -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_Z_Base_met50"   ));
	  h_mll_singletop = dynamic_cast<TH1D*>(f_singletop -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_singletop_met50"));
	  h_mll_ttv       = dynamic_cast<TH1D*>(f_ttv       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ttv_met50"      ));
	  h_mll_ttw       = dynamic_cast<TH1D*>(f_ttw       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ttw_met50"      ));
	  h_mll_ww        = dynamic_cast<TH1D*>(f_ww        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ww_met50"       ));
	  h_mll_wz        = dynamic_cast<TH1D*>(f_wz        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_wz_met50"       ));
	  h_mll_zz        = dynamic_cast<TH1D*>(f_zz        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_zz_met50"       ));
	}
  }
  catch ( exception &e ){
	cout<<"could not open hist."<<endl;
  }

  if( !TString(region).Contains("data") ){
	h_mll_all -> Add(h_mll_TT_1lep  );
	h_mll_all -> Add(h_mll_TT_dilep );
	h_mll_all -> Add(h_mll_VVV      );
	h_mll_all -> Add(h_mll_Z_Base   );
	h_mll_all -> Add(h_mll_singletop);
	h_mll_all -> Add(h_mll_ttv      );
	h_mll_all -> Add(h_mll_ttw      );
	h_mll_all -> Add(h_mll_ww       );
	h_mll_all -> Add(h_mll_wz       );

	h_mll_onz -> Add(h_mll_TT_1lep  );
	h_mll_onz -> Add(h_mll_TT_dilep );
	h_mll_onz -> Add(h_mll_VVV      );
	h_mll_onz -> Add(h_mll_Z_Base   );
	h_mll_onz -> Add(h_mll_singletop);
	h_mll_onz -> Add(h_mll_ttv      );
	h_mll_onz -> Add(h_mll_ttw      );
	h_mll_onz -> Add(h_mll_ww       );
	h_mll_onz -> Add(h_mll_wz       );
  }

  try{

	if( TString(region).Contains("data") ){
	  f_TT_1lep   = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/EMuData.root"  , region.c_str()), "READ" );  
	  h_mll_TT_1lep   = dynamic_cast<TH1D*>(f_TT_1lep   -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_TT_1lep_met50"  ));
	}else{
	  f_TT_1lep   = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/TT_1lep.root"  , region.c_str()), "READ" );  
	  f_TT_dilep  = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/TT_dilep.root" , region.c_str()), "READ" ); 
	  f_VVV       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/VVV.root"      , region.c_str()), "READ" );   
	  f_Z_Base    = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/Z_Base.root"   , region.c_str()), "READ" );  
	  f_singletop = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/singletop.root", region.c_str()), "READ" );
	  f_ttv       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/ttv.root"      , region.c_str()), "READ" );   
	  f_ttw       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/ttw.root"      , region.c_str()), "READ" );   
	  f_ww        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/ww.root"       , region.c_str()), "READ" );   
	  f_wz        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/wz.root"       , region.c_str()), "READ" );   
	  f_zz        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/zz.root"       , region.c_str()), "READ" );   
	  h_mll_TT_1lep   = dynamic_cast<TH1D*>(f_TT_1lep   -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_TT_1lep_met50"  ));
	  h_mll_TT_dilep  = dynamic_cast<TH1D*>(f_TT_dilep  -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_TT_dilep_met50" ));
	  h_mll_VVV       = dynamic_cast<TH1D*>(f_VVV       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_VVV_met50"      ));
	  h_mll_Z_Base    = dynamic_cast<TH1D*>(f_Z_Base    -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_Z_Base_met50"   ));
	  h_mll_singletop = dynamic_cast<TH1D*>(f_singletop -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_singletop_met50"));
	  h_mll_ttv       = dynamic_cast<TH1D*>(f_ttv       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ttv_met50"      ));
	  h_mll_ttw       = dynamic_cast<TH1D*>(f_ttw       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ttw_met50"      ));
	  h_mll_ww        = dynamic_cast<TH1D*>(f_ww        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ww_met50"       ));
	  h_mll_wz        = dynamic_cast<TH1D*>(f_wz        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_wz_met50"       ));
	  h_mll_zz        = dynamic_cast<TH1D*>(f_zz        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_zz_met50"       ));
	}
  }
  catch ( exception &e ){
  	cout<<"could not open file."<<endl;
  }

  if( TString(region).Contains("data") ){
	h_mll_all -> Add(h_mll_TT_1lep  );
  }else{
	h_mll_all -> Add(h_mll_TT_1lep  );
	h_mll_all -> Add(h_mll_TT_dilep );
	h_mll_all -> Add(h_mll_VVV      );
	h_mll_all -> Add(h_mll_Z_Base   );
	h_mll_all -> Add(h_mll_singletop);
	h_mll_all -> Add(h_mll_ttv      );
	h_mll_all -> Add(h_mll_ttw      );
	h_mll_all -> Add(h_mll_ww       );
	h_mll_all -> Add(h_mll_wz       );
	h_mll_all -> Add(h_mll_zz       );
  }
	
  try{
	if( TString(region).Contains("data") ){
	  f_TT_1lep   = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/EMuData.root"  , region.c_str()), "READ" );  
	  h_mll_TT_1lep   = dynamic_cast<TH1D*>(f_TT_1lep   -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_TT_1lep_met50"  ));
	}else{
	  f_TT_1lep   = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/TT_1lep.root"  , region.c_str()), "READ" );  
	  f_TT_dilep  = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/TT_dilep.root" , region.c_str()), "READ" ); 
	  f_VVV       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/VVV.root"      , region.c_str()), "READ" );   
	  f_Z_Base    = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/Z_Base.root"   , region.c_str()), "READ" );  
	  f_singletop = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/singletop.root", region.c_str()), "READ" );
	  f_ttv       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/ttv.root"      , region.c_str()), "READ" );   
	  f_ttw       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/ttw.root"      , region.c_str()), "READ" );   
	  f_ww        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/ww.root"       , region.c_str()), "READ" );   
	  f_wz        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/wz.root"       , region.c_str()), "READ" );   
	  f_zz        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/zz.root"       , region.c_str()), "READ" );   
	  h_mll_TT_1lep   = dynamic_cast<TH1D*>(f_TT_1lep   -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_TT_1lep_met50"  ));
	  h_mll_TT_dilep  = dynamic_cast<TH1D*>(f_TT_dilep  -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_TT_dilep_met50" ));
	  h_mll_VVV       = dynamic_cast<TH1D*>(f_VVV       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_VVV_met50"      ));
	  h_mll_Z_Base    = dynamic_cast<TH1D*>(f_Z_Base    -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_Z_Base_met50"   ));
	  h_mll_singletop = dynamic_cast<TH1D*>(f_singletop -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_singletop_met50"));
	  h_mll_ttv       = dynamic_cast<TH1D*>(f_ttv       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ttv_met50"      ));
	  h_mll_ttw       = dynamic_cast<TH1D*>(f_ttw       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ttw_met50"      ));
	  h_mll_ww        = dynamic_cast<TH1D*>(f_ww        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ww_met50"       ));
	  h_mll_wz        = dynamic_cast<TH1D*>(f_wz        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_wz_met50"       ));
	  h_mll_zz        = dynamic_cast<TH1D*>(f_zz        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_zz_met50"       ));
	}
  }
  catch ( exception &e ){
  	cout<<"could not open file."<<endl;
  }

  if( TString(region).Contains("data") ){
	h_mll_all -> Add(h_mll_TT_1lep  );
  }else{
	h_mll_all -> Add(h_mll_TT_1lep  );
	h_mll_all -> Add(h_mll_TT_dilep );
	h_mll_all -> Add(h_mll_VVV      );
	h_mll_all -> Add(h_mll_Z_Base   );
	h_mll_all -> Add(h_mll_singletop);
	h_mll_all -> Add(h_mll_ttv      );
	h_mll_all -> Add(h_mll_ttw      );
	h_mll_all -> Add(h_mll_ww       );
	h_mll_all -> Add(h_mll_wz       );
	h_mll_all -> Add(h_mll_zz       );
  }
  
  int rebin = 300;
  float xmax = 300;
  h_mll_all -> GetXaxis() -> SetTitle("E_{T}^{miss} [GeV]");
  h_mll_all -> GetYaxis() -> SetTitle(Form("Events"));
  
  h_mll_onz -> Rebin(rebin);
  h_mll_all -> Rebin(rebin);
  
  h_mll_onz -> GetXaxis() -> SetRangeUser(0,xmax);
  h_mll_all -> GetXaxis() -> SetRangeUser(0,xmax);

  updateoverflow( h_mll_all, xmax );
  updateoverflow( h_mll_onz, xmax );

  TH1D * h_mll_ratio = (TH1D*) h_mll_all->Clone("h_mll_ratio");
  h_mll_ratio->Divide(h_mll_onz, h_mll_all, 1, 1, "B");
  
  // h_mll_ratio->GetYaxis()->SetRangeUser(0.0, 0.15);
  // h_mll_ratio->Draw("histe1");

  cout<<h_mll_ratio->GetBinContent(1)<<" +/- ";
  cout<<h_mll_ratio->GetBinError(1)<<endl;

  return make_pair(h_mll_ratio->GetBinContent(1), h_mll_ratio->GetBinError(1));
}

pair <double, double>  getonekfactorvalue_varbin(string region = "baseline_MET100", double lobin = 0, double hibin = 300)
{
  
  string variable = "type1MET";

  TFile * f_TT_1lep   = NULL;
  TFile * f_TT_dilep  = NULL;
  TFile * f_VVV       = NULL;
  TFile * f_Z_Base    = NULL;
  TFile * f_singletop = NULL;
  TFile * f_ttv       = NULL;
  TFile * f_ttw       = NULL;
  TFile * f_ww        = NULL;
  TFile * f_wz        = NULL;
  TFile * f_zz        = NULL;

  try{
	if( TString(region).Contains("data") ){
	  f_zz        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/EMuData.root"  , region.c_str() ), "READ" );   
	}else{
	  f_TT_1lep   = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/TT_1lep.root"  , region.c_str() ), "READ" );  
	  f_TT_dilep  = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/TT_dilep.root" , region.c_str() ), "READ" ); 
	  f_VVV       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/VVV.root"      , region.c_str() ), "READ" );   
	  f_Z_Base    = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/Z_Base.root"   , region.c_str() ), "READ" );  
	  f_singletop = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/singletop.root", region.c_str() ), "READ" );
	  f_ttv       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/ttv.root"      , region.c_str() ), "READ" );   
	  f_ttw       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/ttw.root"      , region.c_str() ), "READ" );   
	  f_ww        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/ww.root"       , region.c_str() ), "READ" );   
	  f_wz        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/wz.root"       , region.c_str() ), "READ" );   
	  f_zz        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_onZ/zz.root"       , region.c_str() ), "READ" );   
	}
  }
  catch ( exception &e ){
	cout<<"could not open file."<<endl;
  }
  
  TH1D * h_mll_TT_1lep   = NULL;
  TH1D * h_mll_TT_dilep  = NULL;
  TH1D * h_mll_VVV       = NULL;
  TH1D * h_mll_Z_Base    = NULL;
  TH1D * h_mll_singletop = NULL;
  TH1D * h_mll_ttv       = NULL;
  TH1D * h_mll_ttw       = NULL;
  TH1D * h_mll_ww        = NULL;
  TH1D * h_mll_wz        = NULL;
  TH1D * h_mll_zz        = NULL;

  TH1D * h_mll_onz       = NULL;
  h_mll_onz       = dynamic_cast<TH1D*>(f_zz        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_onz"            ));

  TH1D * h_mll_all       = NULL;
  h_mll_all       = dynamic_cast<TH1D*>(f_zz        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_all"            ));

  try{
	if( !TString(region).Contains("data") ){
	  h_mll_TT_1lep   = dynamic_cast<TH1D*>(f_TT_1lep   -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_TT_1lep_met50"  ));
	  h_mll_TT_dilep  = dynamic_cast<TH1D*>(f_TT_dilep  -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_TT_dilep_met50" ));
	  h_mll_VVV       = dynamic_cast<TH1D*>(f_VVV       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_VVV_met50"      ));
	  h_mll_Z_Base    = dynamic_cast<TH1D*>(f_Z_Base    -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_Z_Base_met50"   ));
	  h_mll_singletop = dynamic_cast<TH1D*>(f_singletop -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_singletop_met50"));
	  h_mll_ttv       = dynamic_cast<TH1D*>(f_ttv       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ttv_met50"      ));
	  h_mll_ttw       = dynamic_cast<TH1D*>(f_ttw       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ttw_met50"      ));
	  h_mll_ww        = dynamic_cast<TH1D*>(f_ww        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ww_met50"       ));
	  h_mll_wz        = dynamic_cast<TH1D*>(f_wz        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_wz_met50"       ));
	  h_mll_zz        = dynamic_cast<TH1D*>(f_zz        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_zz_met50"       ));
	}
  }
  catch ( exception &e ){
	cout<<"could not open hist."<<endl;
  }

  if( !TString(region).Contains("data") ){
	h_mll_all -> Add(h_mll_TT_1lep  );
	h_mll_all -> Add(h_mll_TT_dilep );
	h_mll_all -> Add(h_mll_VVV      );
	h_mll_all -> Add(h_mll_Z_Base   );
	h_mll_all -> Add(h_mll_singletop);
	h_mll_all -> Add(h_mll_ttv      );
	h_mll_all -> Add(h_mll_ttw      );
	h_mll_all -> Add(h_mll_ww       );
	h_mll_all -> Add(h_mll_wz       );

	h_mll_onz -> Add(h_mll_TT_1lep  );
	h_mll_onz -> Add(h_mll_TT_dilep );
	h_mll_onz -> Add(h_mll_VVV      );
	h_mll_onz -> Add(h_mll_Z_Base   );
	h_mll_onz -> Add(h_mll_singletop);
	h_mll_onz -> Add(h_mll_ttv      );
	h_mll_onz -> Add(h_mll_ttw      );
	h_mll_onz -> Add(h_mll_ww       );
	h_mll_onz -> Add(h_mll_wz       );
  }

  try{

	if( TString(region).Contains("data") ){
	  f_TT_1lep   = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/EMuData.root"  , region.c_str()), "READ" );  
	  h_mll_TT_1lep   = dynamic_cast<TH1D*>(f_TT_1lep   -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_TT_1lep_met50"  ));
	}else{
	  f_TT_1lep   = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/TT_1lep.root"  , region.c_str()), "READ" );  
	  f_TT_dilep  = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/TT_dilep.root" , region.c_str()), "READ" ); 
	  f_VVV       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/VVV.root"      , region.c_str()), "READ" );   
	  f_Z_Base    = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/Z_Base.root"   , region.c_str()), "READ" );  
	  f_singletop = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/singletop.root", region.c_str()), "READ" );
	  f_ttv       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/ttv.root"      , region.c_str()), "READ" );   
	  f_ttw       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/ttw.root"      , region.c_str()), "READ" );   
	  f_ww        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/ww.root"       , region.c_str()), "READ" );   
	  f_wz        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/wz.root"       , region.c_str()), "READ" );   
	  f_zz        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_aboveZ/zz.root"       , region.c_str()), "READ" );   
	  h_mll_TT_1lep   = dynamic_cast<TH1D*>(f_TT_1lep   -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_TT_1lep_met50"  ));
	  h_mll_TT_dilep  = dynamic_cast<TH1D*>(f_TT_dilep  -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_TT_dilep_met50" ));
	  h_mll_VVV       = dynamic_cast<TH1D*>(f_VVV       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_VVV_met50"      ));
	  h_mll_Z_Base    = dynamic_cast<TH1D*>(f_Z_Base    -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_Z_Base_met50"   ));
	  h_mll_singletop = dynamic_cast<TH1D*>(f_singletop -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_singletop_met50"));
	  h_mll_ttv       = dynamic_cast<TH1D*>(f_ttv       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ttv_met50"      ));
	  h_mll_ttw       = dynamic_cast<TH1D*>(f_ttw       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ttw_met50"      ));
	  h_mll_ww        = dynamic_cast<TH1D*>(f_ww        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ww_met50"       ));
	  h_mll_wz        = dynamic_cast<TH1D*>(f_wz        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_wz_met50"       ));
	  h_mll_zz        = dynamic_cast<TH1D*>(f_zz        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_zz_met50"       ));
	}
  }
  catch ( exception &e ){
  	cout<<"could not open file."<<endl;
  }

  if( TString(region).Contains("data") ){
	h_mll_all -> Add(h_mll_TT_1lep  );
  }else{
	h_mll_all -> Add(h_mll_TT_1lep  );
	h_mll_all -> Add(h_mll_TT_dilep );
	h_mll_all -> Add(h_mll_VVV      );
	h_mll_all -> Add(h_mll_Z_Base   );
	h_mll_all -> Add(h_mll_singletop);
	h_mll_all -> Add(h_mll_ttv      );
	h_mll_all -> Add(h_mll_ttw      );
	h_mll_all -> Add(h_mll_ww       );
	h_mll_all -> Add(h_mll_wz       );
	h_mll_all -> Add(h_mll_zz       );
  }
	
  try{
	if( TString(region).Contains("data") ){
	  f_TT_1lep   = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/EMuData.root"  , region.c_str()), "READ" );  
	  h_mll_TT_1lep   = dynamic_cast<TH1D*>(f_TT_1lep   -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_TT_1lep_met50"  ));
	}else{
	  f_TT_1lep   = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/TT_1lep.root"  , region.c_str()), "READ" );  
	  f_TT_dilep  = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/TT_dilep.root" , region.c_str()), "READ" ); 
	  f_VVV       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/VVV.root"      , region.c_str()), "READ" );   
	  f_Z_Base    = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/Z_Base.root"   , region.c_str()), "READ" );  
	  f_singletop = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/singletop.root", region.c_str()), "READ" );
	  f_ttv       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/ttv.root"      , region.c_str()), "READ" );   
	  f_ttw       = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/ttw.root"      , region.c_str()), "READ" );   
	  f_ww        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/ww.root"       , region.c_str()), "READ" );   
	  f_wz        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/wz.root"       , region.c_str()), "READ" );   
	  f_zz        = TFile::Open(Form("/nfs-7/userdata/bobak/ZMET2016_Hists_NovemberClean/FS_mass_window_studies/%s_belowZ/zz.root"       , region.c_str()), "READ" );   
	  h_mll_TT_1lep   = dynamic_cast<TH1D*>(f_TT_1lep   -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_TT_1lep_met50"  ));
	  h_mll_TT_dilep  = dynamic_cast<TH1D*>(f_TT_dilep  -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_TT_dilep_met50" ));
	  h_mll_VVV       = dynamic_cast<TH1D*>(f_VVV       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_VVV_met50"      ));
	  h_mll_Z_Base    = dynamic_cast<TH1D*>(f_Z_Base    -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_Z_Base_met50"   ));
	  h_mll_singletop = dynamic_cast<TH1D*>(f_singletop -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_singletop_met50"));
	  h_mll_ttv       = dynamic_cast<TH1D*>(f_ttv       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ttv_met50"      ));
	  h_mll_ttw       = dynamic_cast<TH1D*>(f_ttw       -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ttw_met50"      ));
	  h_mll_ww        = dynamic_cast<TH1D*>(f_ww        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_ww_met50"       ));
	  h_mll_wz        = dynamic_cast<TH1D*>(f_wz        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_wz_met50"       ));
	  h_mll_zz        = dynamic_cast<TH1D*>(f_zz        -> Get(Form( "%s", variable.c_str() ))->Clone("h_mll_zz_met50"       ));
	}
  }
  catch ( exception &e ){
  	cout<<"could not open file."<<endl;
  }

  if( TString(region).Contains("data") ){
	h_mll_all -> Add(h_mll_TT_1lep  );
  }else{
	h_mll_all -> Add(h_mll_TT_1lep  );
	h_mll_all -> Add(h_mll_TT_dilep );
	h_mll_all -> Add(h_mll_VVV      );
	h_mll_all -> Add(h_mll_Z_Base   );
	h_mll_all -> Add(h_mll_singletop);
	h_mll_all -> Add(h_mll_ttv      );
	h_mll_all -> Add(h_mll_ttw      );
	h_mll_all -> Add(h_mll_ww       );
	h_mll_all -> Add(h_mll_wz       );
	h_mll_all -> Add(h_mll_zz       );
  }
  
  // int rebin = 300;
  // float xmax = 300;
  // h_mll_all -> GetXaxis() -> SetTitle("E_{T}^{miss} [GeV]");
  // h_mll_all -> GetYaxis() -> SetTitle(Form("Events"));
  
  // h_mll_onz -> Rebin(rebin);
  // h_mll_all -> Rebin(rebin);
  
  // h_mll_onz -> GetXaxis() -> SetRangeUser(0,xmax);
  // h_mll_all -> GetXaxis() -> SetRangeUser(0,xmax);

  updateoverflow( h_mll_all, 300 );
  updateoverflow( h_mll_onz, 300 );

  // TH1D * h_mll_ratio = (TH1D*) h_mll_all->Clone("h_mll_ratio");
  // h_mll_ratio->Divide(h_mll_onz, h_mll_all, 1, 1, "B");
  
  // h_mll_ratio->GetYaxis()->SetRangeUser(0.0, 0.15);
  // h_mll_ratio->Draw("histe1");

  double val_num = 0.0, err_num = 0.0;
  double val_den = 0.0, err_den = 0.0;
  double val_rat = 0.0, err_rat = 0.0;

  val_num = h_mll_onz->IntegralAndError( h_mll_onz->FindBin( lobin ), h_mll_onz->FindBin( hibin ) - 1, err_num );
  val_den = h_mll_all->IntegralAndError( h_mll_all->FindBin( lobin ), h_mll_all->FindBin( hibin ) - 1, err_den );
  val_rat = val_num/val_den;
  err_rat = err_mult(val_num, val_den, err_num, err_den, val_num/val_den);
  
  // cout<<"num: "<<val_num<<" +/- ";
  // cout<<err_num<<endl;
  // cout<<"den: "<<val_den<<" +/- ";
  // cout<<err_den<<endl;
  // cout<<"rat: "<<val_rat<<" +/- ";
  cout<<val_rat<<" +/- ";
  cout<<err_rat<<endl;
  
  // cout<<h_mll_ratio->GetBinContent(1)<<" +/- ";
  // cout<<h_mll_ratio->GetBinError(1)<<endl;

  return make_pair(val_rat, err_rat);
  
  // double val_den_mc_met50 = 0;
  // double err_den_mc_met50 = 0;

  // double val_den_mll_all = 0;
  // double err_den_mll_all = 0;

  // val_den_mc_met50   = h_mc_met50   -> IntegralAndError(0, -1., err_den_mc_met50);

  // val_den_mll_all = h_mll_all -> IntegralAndError(0, -1., err_den_mll_all);

  // double val_num_mc_met50 = 0;
  // double err_num_mc_met50 = 0;

  // double val_num_mll_all = 0;
  // double err_num_mll_all = 0;

  // val_num_mc_met50   = h_mc_met50   -> IntegralAndError(h_mc_met50->FindBin(81)  , h_mc_met50->FindBin(101)-1  , err_num_mc_met50);

  // val_num_mll_all = h_mll_all -> IntegralAndError(h_mll_all->FindBin(81), h_mll_all->FindBin(101)-1, err_num_mll_all);

  // cout<<"total mc:   "<<val_den_mc_met50  << " | "<<err_den_mc_met50  <<endl;
  // cout<<"total data: "<<val_den_mll_all<< " | "<<err_den_mll_all<<endl;
  // cout<<"on-Z  mc:   "<<val_num_mc_met50  << " | "<<err_num_mc_met50  <<endl;
  // cout<<"on-Z  data: "<<val_num_mll_all<< " | "<<err_num_mll_all<<endl;
  // cout<<"eff   mc:   "<<val_num_mc_met50/val_den_mc_met50    << " | "<<err_mult(val_num_mc_met50, val_den_mc_met50, err_num_mc_met50, err_den_mc_met50, val_num_mc_met50/val_den_mc_met50)  <<endl;
  // cout<<"eff   data: "<<val_num_mll_all/val_den_mll_all<< " | "<<err_mult(val_num_mll_all, val_den_mll_all, err_num_mll_all, err_den_mll_all, val_num_mll_all/val_den_mll_all)  <<endl;

  
  // TCanvas * c1 = new TCanvas("c1","");
  // c1->cd();

  // TPad *pad = new TPad( "p_main", "p_main", 0.0, 0.3, 1.0, 1.0);
  // pad->SetBottomMargin(0.05);
  // pad->SetRightMargin(0.07);
  // pad->SetTopMargin(0.08);
  // pad->SetLeftMargin(0.18);
  // pad->Draw();
  // pad->cd();

  // return;
}
