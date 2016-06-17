#include <iostream>

#include "TFile.h"
#include "TChain.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TF1.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TLatex.h"

using namespace std;

void updateoverflow( TH1F * &hist, float xmax )
{
  int overflowbin = hist->FindBin(xmax)-1;
  for( int bini = overflowbin; bini < hist->GetNbinsX(); bini++ ){
	hist->SetBinContent( overflowbin, hist->GetBinContent( overflowbin ) + hist->GetBinContent( bini + 1 ) );	
	hist->SetBinError  ( overflowbin, sqrt( pow(hist->GetBinError  ( overflowbin ), 2 ) + pow( hist->GetBinError( bini + 1 ), 2 ) ) );	
	hist->SetBinContent( bini + 1, 0 );
	hist->SetBinError  ( bini + 1, 0 );
  }  
  return;
}

void renormalizebins( TH1F * &hist )
{
  for( int bini = 0; bini < hist->GetNbinsX()+1; bini++ ){
	// if( hist->GetBinWidth(bini) > hist->GetBinWidth(1) ){
	  hist->SetBinContent( bini, hist->GetBinContent( bini )*(hist->GetBinWidth(1)/hist->GetBinWidth(bini)) );	
	  hist->SetBinError( bini, hist->GetBinError( bini )    *(hist->GetBinWidth(1)/hist->GetBinWidth(bini)) );	
	// }
  }  
  return;
}



void drawmgammagamma( string corrs = "raw")
{

  // emcut = "05";
  // emcut = "01";

  // corrs = "cor";
  // corrs = "T1Only";

  TChain * ch = new TChain("t");

  ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00_photonstudies/data_2016B_Prompt_ph_v1.root");
  ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00_photonstudies/data_2016B_Prompt_ph_v2.root");
  
  // TFile * f_gg = TFile::Open("data_diphotonstudy_novtxweight_nohtweight_templates.root","READ");

  TH1F * h_gg = new TH1F("h_gg", "", 600, 400, 1000);//(TH1F*)f_gg->Get(Form("h_ph_event_mjj_%s_passtrig", corrs.c_str()))->Clone("h_gg");
  h_gg->Sumw2();
  
  ch->Draw(Form("%s>>h_gg", corrs.c_str()), "evt_passgoodrunlist&&HLT_Photon165_HE10>0 && (abs(diphotonjets_p4[0].eta()) < 3.0 && abs(diphotonjets_p4[1].eta()) < 3.0)");
  
  h_gg -> Rebin(20);

  TF1 *fit_gg = new TF1("fit_gg","pow(x, [0] + [1]*log(x))", 500, 1000);

  h_gg->Fit("fit_gg");
  
  h_gg->SetLineColor(kBlack);
  fit_gg->SetLineColor(kRed);

  h_gg->GetXaxis()->SetTitle("M_{jj} [GeV]");

  TCanvas * c1 = new TCanvas("c1","",800,800);
  c1->cd();
  // c1->SetLogy();
  TPad *pad = new TPad( "p_main", "p_main", 0.0, 0.0, 1.0, 1.0);
  pad->SetBottomMargin(0.12);
  pad->SetRightMargin(0.07);
  pad->SetTopMargin(0.065);
  pad->SetLeftMargin(0.18);
  pad->Draw();
  pad->cd();
  // pad->SetLogy();
	
  h_gg->GetYaxis()->SetTitle("Events/20 GeV");
  // h_gg->GetYaxis()->SetRangeUser(0,100);

  h_gg->Draw("histe1");
  fit_gg->Draw("same");

  // TLegend *l1 = new TLegend(0.6, 0.7, 0.9, 0.90);    
  // l1->SetLineColor(kWhite);    
  // l1->SetShadowColor(kWhite);    
  // l1->SetFillColor(kWhite);    
  // l1->SetTextSize(0.05);    
  // l1->AddEntry( h_gg    , "#gamma+jets"          , "le");
  // l1->AddEntry( h_wb    , "Z+jets"          , "le");
  // l1->Draw("same");

  // drawSRLatex( c1, "withb_SRB", 0.35, 0.35 );
  // drawCMSLatex( c1, 2.2 );

  
  // c1->SaveAs(Form("~/Desktop/template_studies/photon_vs_dilep_%s_%s.pdf", variable.c_str(), btag.c_str() ));
  c1->SaveAs(Form("~/diphoton_peak_%s.pdf", corrs.c_str() ));
  
  return;
}

void plotDiphotons( ){

  // drawmgammagamma( "raw_em10" );
  // drawmgammagamma( "raw_em05" );
  // drawmgammagamma( "raw_em01" );
  // drawmgammagamma( "T1Only_em10" );
  // drawmgammagamma( "T1Only_em05" );
  // drawmgammagamma( "T1Only_em01" );

  // drawmgammagamma( "raw_em90_EBEB" );
  // drawmgammagamma( "raw_em95_EBEB" );
  // drawmgammagamma( "raw_em99_EBEB" );
  // drawmgammagamma( "t1c_em90_EBEB" );
  // drawmgammagamma( "t1c_em95_EBEB" );
  // drawmgammagamma( "t1c_em99_EBEB" );
  // drawmgammagamma( "raw_em90_EBEE" );
  // drawmgammagamma( "raw_em95_EBEE" );
  // drawmgammagamma( "raw_em99_EBEE" );
  // drawmgammagamma( "t1c_em90_EBEE" );
  // drawmgammagamma( "t1c_em95_EBEE" );
  // drawmgammagamma( "t1c_em99_EBEE" );

  // drawmgammagamma( "raw_em90_SSeta" );
  // drawmgammagamma( "raw_em95_SSeta" );
  // drawmgammagamma( "raw_em99_SSeta" );
  // drawmgammagamma( "t1c_em90_SSeta" );
  // drawmgammagamma( "t1c_em95_SSeta" );
  // drawmgammagamma( "t1c_em99_SSeta" );
  // drawmgammagamma( "raw_em90_OSeta" );
  // drawmgammagamma( "raw_em95_OSeta" );
  // drawmgammagamma( "raw_em99_OSeta" );
  // drawmgammagamma( "t1c_em90_OSeta" );
  // drawmgammagamma( "t1c_em95_OSeta" );
  // drawmgammagamma( "t1c_em99_OSeta" );

  drawmgammagamma( "mjj_atleastoneEMF97" );
  drawmgammagamma( "mjj_atleasttwoEMF97" );
  drawmgammagamma( "mjj_EMF97"           );

  return;
}
