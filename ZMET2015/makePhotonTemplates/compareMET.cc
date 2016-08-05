#include "TH1F.h"
#include "TFile.h"
#include "TLine.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPad.h"
#include "TLatex.h"
#include "TStyle.h"

#include <iostream>

#include "../sharedCode/histTools.cc"

using namespace std;

void printYieldTable( vector <float> metcut, TH1F* h_zll, TH1F* h_pho );
  
void compareMET( std::string region = "", float luminosity = 1.0, string variabletodraw = "ht" )
{

  bool doreweighted = true;

  TFile *infile_al = NULL;
  TFile *infile_wg = NULL;
  TFile *infile_wj = NULL;
  TFile *infile_tg = NULL;
  TFile *infile_tj = NULL;

  if( doreweighted ){
	infile_al = new TFile(Form("../output/V08-11-00/allewk%s_novtxweight_templates.root"  , region.c_str()));
	infile_wg = new TFile(Form("../output/V08-11-00/wgjets%s_novtxweight_templates.root"  , region.c_str()));
	infile_wj = new TFile(Form("../output/V08-11-00/wjets%s_novtxweight_templates.root"   , region.c_str()));
	infile_tg = new TFile(Form("../output/V08-11-00/ttgamma%s_novtxweight_templates.root" , region.c_str()));
	infile_tj = new TFile(Form("../output/V08-11-00/ttbar%s_novtxweight_templates.root"   , region.c_str()));
  }else{

	infile_al = new TFile(Form("../output/V08-11-00/allewk%s_novtxweight_nohtweight_templates.root"  , region.c_str()));
	infile_wg = new TFile(Form("../output/V08-11-00/wgjets%s_novtxweight_nohtweight_templates.root"  , region.c_str()));
	infile_wj = new TFile(Form("../output/V08-11-00/wjets%s_novtxweight_nohtweight_templates.root"   , region.c_str()));
	infile_tg = new TFile(Form("../output/V08-11-00/ttgamma%s_novtxweight_nohtweight_templates.root" , region.c_str()));
	infile_tj = new TFile(Form("../output/V08-11-00/ttbar%s_novtxweight_nohtweight_templates.root"   , region.c_str()));
  }
  
  TH1F * h_alewk = (TH1F*)infile_al->Get(Form("h_ph_event_%s_passtrig", variabletodraw.c_str() ))->Clone("h_alewk");
  TH1F * h_wgama = (TH1F*)infile_wg->Get(Form("h_ph_event_%s_passtrig", variabletodraw.c_str() ))->Clone("h_wgama");
  TH1F * h_wjets = (TH1F*)infile_wj->Get(Form("h_ph_event_%s_passtrig", variabletodraw.c_str() ))->Clone("h_wjets");
  TH1F * h_ttgma = (TH1F*)infile_tg->Get(Form("h_ph_event_%s_passtrig", variabletodraw.c_str() ))->Clone("h_ttgma");
  TH1F * h_ttjts = (TH1F*)infile_tj->Get(Form("h_ph_event_%s_passtrig", variabletodraw.c_str() ))->Clone("h_ttjts");

  h_alewk->SetTitle("Current EWK prediction"             );
  h_wgama->SetTitle("W$\\gamma$+jets"                    );
  h_wjets->SetTitle("W+jets"                             );
  h_ttgma->SetTitle("t$\\mathrm{\\bar{t}}$$\\gamma$+jets");
  h_ttjts->SetTitle("t$\\mathrm{\\bar{t}}$+jets"         );
  
  h_alewk -> Scale(luminosity);
  h_wgama -> Scale(luminosity);
  h_wjets -> Scale(luminosity);
  h_ttgma -> Scale(luminosity);
  h_ttjts -> Scale(luminosity);

  if( region == "_SRA_bveto" ){
	h_alewk -> Scale(0.979244*1.02);
	h_wgama -> Scale(0.979244*1.02);
	h_wjets -> Scale(0.979244*1.02);
	h_ttgma -> Scale(0.979244*1.02);
	h_ttjts -> Scale(0.979244*1.02);
  }
  
  if( region == "_SRA_withb" ){
	h_alewk -> Scale(0.849002*1.14);
	h_wgama -> Scale(0.849002*1.14);
	h_wjets -> Scale(0.849002*1.14);
	h_ttgma -> Scale(0.849002*1.14);
	h_ttjts -> Scale(0.849002*1.14);
  }
  
  if( region == "_SRB_bveto" ){
	h_alewk -> Scale(0.973755*0.187);
	h_wgama -> Scale(0.973755*0.187);
	h_wjets -> Scale(0.973755*0.187);
	h_ttgma -> Scale(0.973755*0.187);
	h_ttjts -> Scale(0.973755*0.187);
  }

  if( region == "_SRB_withb" ){
	h_alewk -> Scale(0.731901*0.62*0.398);
	h_wgama -> Scale(0.731901*0.62*0.398);
	h_wjets -> Scale(0.731901*0.62*0.398);
	h_ttgma -> Scale(0.731901*0.62*0.398);
	h_ttjts -> Scale(0.731901*0.62*0.398);
  }

  if( region == "_SR_ATLAS" ){
	h_alewk -> Scale(0.958875*0.566666);
	h_wgama -> Scale(0.958875*0.566666);
	h_wjets -> Scale(0.958875*0.566666);
	h_ttgma -> Scale(0.958875*0.566666);
	h_ttjts -> Scale(0.958875*0.566666);
  }
  
  float xmax = 350;
  if( variabletodraw == "ht"        ) xmax = 1000;
  if( variabletodraw == "ht_highbin") xmax = 1500;
  if( variabletodraw == "gen_ht"    ) xmax = 1500;
  if( variabletodraw == "njets"     ) xmax = 20;
  if( variabletodraw == "met"       ) xmax = 350;
  if( variabletodraw == "ptg"       ) xmax = 500;

  updateoverflow( h_alewk , xmax-1 );
  updateoverflow( h_wgama , xmax-1 );
  updateoverflow( h_wjets , xmax-1 );
  updateoverflow( h_ttgma , xmax-1 );
  updateoverflow( h_ttjts , xmax-1 );
  
  // //MAKE TABLES
  if( variabletodraw == "met"       ) {
	vector <float> metcut_row1;
	metcut_row1.clear();
	// metcut_row1.push_back(0.0);
	// metcut_row1.push_back(50);
	// metcut_row1.push_back(100);
	if( region != "_SR_ATLAS" ) metcut_row1.push_back(100);
	if( region == "_SR_ATLAS" ) metcut_row1.push_back(225);
	metcut_row1.push_back(-1);
	printYieldTable( metcut_row1, h_alewk, h_wjets );
	printYieldTable( metcut_row1, h_alewk, h_ttgma );
	printYieldTable( metcut_row1, h_wgama, h_wjets );
	printYieldTable( metcut_row1, h_ttgma, h_ttjts );
  }

  // if( region != "_2jets_inclusive" ){
  // 	vector <float> metcut_row2;
  // 	metcut_row2.clear();
  // 	metcut_row2.push_back(150);
  // 	metcut_row2.push_back(225);
  // 	if( region != "_SR_ATLAS" ) metcut_row2.push_back(300);
  // 	metcut_row2.push_back(-1);
  // 	printYieldTable( metcut_row2, h_zll, h_pho );
  // }
  
  //MAKE BINNING FOR PLOTS
  vector <float> metcut;
  metcut.clear();
  if( variabletodraw == "met"       ) {
	metcut.push_back(0.0);
	metcut.push_back(50);
	metcut.push_back(100);
	metcut.push_back(150);
	metcut.push_back(225);
	if( region != "_SR_ATLAS" ) metcut.push_back(300);
	metcut.push_back(-1);
  }
  
  //MAKE PLOTS
  int nbinsx = metcut.size();
  int rebin = 50;

  if( nbinsx > 0 ){
	double xbins[(int)(nbinsx)];

	for( size_t binind = 0; binind < metcut.size()-1; binind++ ){
	  xbins[binind] = metcut.at(binind);
	}
  
	xbins[nbinsx-1] = xmax;  
	h_alewk = (TH1F*)h_alewk->Rebin(nbinsx-1, "h_alewk_rebinned", xbins);
	h_wgama = (TH1F*)h_wgama->Rebin(nbinsx-1, "h_wgama_rebinned", xbins);
	h_wjets = (TH1F*)h_wjets->Rebin(nbinsx-1, "h_wjets_rebinned", xbins);
	h_ttjts = (TH1F*)h_ttjts->Rebin(nbinsx-1, "h_ttjts_rebinned", xbins);
	h_ttgma = (TH1F*)h_ttgma->Rebin(nbinsx-1, "h_ttgma_rebinned", xbins);

	renormalizebins( h_alewk );
	renormalizebins( h_wgama );
	renormalizebins( h_wjets );
	renormalizebins( h_ttgma );
	renormalizebins( h_ttjts );
	  	  
  }else{
	if( variabletodraw == "njets"     ) rebin = 1;
	if( variabletodraw == "met"       ) rebin = 10;
	if( variabletodraw == "ptg"       ) rebin = 25;
	if( variabletodraw == "ht"        ) rebin = 50;
	if( variabletodraw == "ht_highbin") rebin = 50;
	if( variabletodraw == "gen_ht"    ) rebin = 20;
	h_alewk->Rebin(rebin);
	h_wgama->Rebin(rebin);
	h_wjets->Rebin(rebin);
	h_ttgma->Rebin(rebin);
	h_ttjts->Rebin(rebin);

  }

  
  TCanvas * c1 = new TCanvas("c1","");
  c1->cd();
  // c1->SetLogy();

  TPad *pad = new TPad( "p_main", "p_main", 0.0, 0.3, 1.0, 1.0);
  pad->SetBottomMargin(0.05);
  pad->SetRightMargin(0.07);
  pad->SetTopMargin(0.08);
  pad->SetLeftMargin(0.18);
  pad->Draw();
  pad->cd();
  pad->SetLogy();

  h_alewk->SetLineColor(kBlack);
  h_wgama->SetLineColor(kCyan+2);
  h_wjets->SetLineColor(kAzure-1);
  h_ttgma->SetLineColor(kOrange-3);
  h_ttjts->SetLineColor(kPink-6);

  h_alewk->SetLineWidth(2);
  h_wgama->SetLineWidth(2);
  h_wjets->SetLineWidth(2);
  h_ttgma->SetLineWidth(2);
  h_ttjts->SetLineWidth(2);

  if( variabletodraw == "njets"     ) h_wgama->GetXaxis()->SetTitle("N_{jets}");
  if( variabletodraw == "met"       ) h_wgama->GetXaxis()->SetTitle("E_{T}^{miss} [GeV]");
  if( variabletodraw == "ptg"       ) h_wgama->GetXaxis()->SetTitle("#gamma p_{T} [GeV]");
  if( variabletodraw == "ht"        ) h_wgama->GetXaxis()->SetTitle("H_{T} [GeV]");
  if( variabletodraw == "ht_highbin") h_wgama->GetXaxis()->SetTitle("H_{T} [GeV]");
  if( variabletodraw == "gen_ht"    ) h_wgama->GetXaxis()->SetTitle("gen H_{T} [GeV]");

  // h_wgama->GetXaxis()->SetLabelSize(0);
  // h_wgama->GetYaxis()->SetLabelSize(0.05);
  h_wgama->GetYaxis()->SetTitleOffset(1.5);
  h_wgama->GetYaxis()->SetTitleSize(0.05);
  if( variabletodraw != "njets" ) h_wgama->GetYaxis()->SetTitle(Form("Events/%.0f GeV", (float)rebin));
  if( variabletodraw == "njets" ) h_wgama->GetYaxis()->SetTitle("Events");
  if( region == "_SR_EWK" ) h_wgama->GetXaxis()->SetRangeUser(50,xmax);
  if( region != "_SR_EWK" ) h_wgama->GetXaxis()->SetRangeUser(0,xmax);
  h_wgama->GetYaxis()->SetRangeUser(2e-2,h_wgama->GetMaximum()*1e2);
  if( variabletodraw == "met"       ) h_wgama->GetYaxis()->SetRangeUser(2e-2,4e2);
  if( variabletodraw == "ptg"       ) h_wgama->GetYaxis()->SetRangeUser(2e-2,6e2);
  // h_wgama->SetMarkerStyle(8);
  // h_wgama->SetMarkerSize(0.75);

  h_wgama->Draw("e1hist");
  h_wjets->Draw("samehiste1");
  h_ttgma->Draw("samehiste1");
  h_ttjts->Draw("samehiste1");
  h_alewk->Draw("samehiste1");
  
  pad->RedrawAxis();

  TLegend *l1 = new TLegend(0.6, 0.6, 0.9, 0.85);    
  l1->SetLineColor(kWhite);    
  l1->SetShadowColor(kWhite);    
  l1->SetFillColor(kWhite);    
  l1->SetTextFont(42);    
  l1->AddEntry( h_alewk , "Current EWK Prediction" , "le");
  l1->AddEntry( h_ttjts , "t#bar{t}+jets MC"       , "le");
  l1->AddEntry( h_ttgma , "t#bar{t}#gamma+jets MC" , "le");
  l1->AddEntry( h_wjets , "W+jets MC"              , "le");
  l1->AddEntry( h_wgama , "W#gamma+jets MC"        , "le");
  l1->Draw("same");
  
  c1->cd();
	
  // TPad *rat_pad = new TPad( "p_main", "p_main", 0.0, 0.0, 1.0, 0.3);
  // rat_pad->SetBottomMargin(0.36);
  // rat_pad->SetRightMargin(0.07);
  // rat_pad->SetTopMargin(0.07);
  // rat_pad->SetLeftMargin(0.18);
  // rat_pad->Draw();
  // rat_pad->cd();
  // rat_pad->SetGridy();

  // TH1F* h_rat = (TH1F*)h_zll->Clone("h_rat");

  // h_rat->Divide(h_pho);

  // h_rat->GetYaxis()->SetRangeUser(0.0,2.0);
  // h_rat->GetYaxis()->SetLabelSize(0.12);
  // h_rat->GetXaxis()->SetLabelSize(0.12);
  // h_rat->GetYaxis()->SetNdivisions(5);

  // h_rat->GetYaxis()->SetTitle("#frac{Z+jets}{#gamma+jets}");
  // h_rat->GetYaxis()->SetTitleSize(0.12);
  // h_rat->GetYaxis()->SetTitleOffset(0.5);
  // h_rat->GetYaxis()->CenterTitle();
  // // cout<<h_rat->GetYaxis()->GetTitleSize()<<endl;

  // h_rat->GetXaxis()->SetTitle("E_{T}^{miss} GeV");
  // h_rat->GetXaxis()->SetTitleOffset(0.9);
  // h_rat->GetXaxis()->SetTitleSize(0.15);

  // h_rat->SetMarkerStyle(8);
  // h_rat->SetMarkerSize(0.75);

  // TH1F* h_uncband = (TH1F*)h_zll->Clone("h_uncband");  
  // h_uncband->SetFillColor(kBlue+3);
  // h_uncband->SetFillStyle(3004);
  // h_uncband->SetMarkerSize(0);  

  // for( int binind = 1; binind < h_uncband->GetNbinsX()+1; binind++ ){

  // 	float binlowedge = h_uncband->GetBinLowEdge(binind);
  // 	float uncertainty = 0.0;

  // 	if( region == "_SR_ATLAS" ){
  // 	  if(      binlowedge <  50 ) uncertainty = 0.02;
  // 	  else if( binlowedge < 100 ) uncertainty = 0.10;
  // 	  else if( binlowedge < 150 ) uncertainty = 0.25;
  // 	  else if( binlowedge < 225 ) uncertainty = 0.35;
  // 	  else if( binlowedge < 350 ) uncertainty = 0.40;
  // 	}

  // 	if( region == "_SRA_bveto" ){
  // 	  if(      binlowedge <   50 ) uncertainty = 0.02;
  // 	  else if( binlowedge <  100 ) uncertainty = 0.10;
  // 	  else if( binlowedge <  300 ) uncertainty = 0.20;
  // 	  else if( binlowedge <  350 ) uncertainty = 0.25;
  // 	}
  
  // 	if( region == "_SRA_withb" ){
  // 	  if(      binlowedge <   50 ) uncertainty = 0.02;
  // 	  else if( binlowedge <  100 ) uncertainty = 0.07;
  // 	  else if( binlowedge <  225 ) uncertainty = 0.20;
  // 	  else if( binlowedge <  300 ) uncertainty = 0.40;
  // 	  else if( binlowedge <  350 ) uncertainty = 0.40;
  // 	}
  
  // 	if( region == "_SRB_bveto" ){
  // 	  if(      binlowedge <   50 ) uncertainty = 0.01;
  // 	  else if( binlowedge <  100 ) uncertainty = 0.06;
  // 	  else if( binlowedge <  150 ) uncertainty = 0.10;
  // 	  else if( binlowedge <  225 ) uncertainty = 0.10;
  // 	  else if( binlowedge <  350 ) uncertainty = 0.35;
  // 	}
  
  // 	if( region == "_SRB_withb" ){
  // 	  if(      binlowedge <   50 ) uncertainty = 0.01;
  // 	  else if( binlowedge <  100 ) uncertainty = 0.10;
  // 	  else if( binlowedge <  150 ) uncertainty = 0.20;
  // 	  else if( binlowedge <  225 ) uncertainty = 0.25;
  // 	  else if( binlowedge <  300 ) uncertainty = 0.30;
  // 	  else if( binlowedge <  350 ) uncertainty = 0.30;
  // 	}
  
  // 	if( region == "_SR_EWK" ){
  // 	  if(      binlowedge <  100 ) uncertainty = 0.02;
  // 	  else if( binlowedge <  300 ) uncertainty = 0.10;
  // 	  else if( binlowedge <  350 ) uncertainty = 0.15;
  // 	}
  
  // 	if( region == "_2jets_inclusive" ){
  // 	  if(      binlowedge <   50 ) uncertainty = 0.01;
  // 	  else if( binlowedge <  150 ) uncertainty = 0.02;
  // 	  else if( binlowedge <  350 ) uncertainty = 0.05;
  // 	}
  
  // 	h_uncband -> SetBinError  ( binind, uncertainty );
  // 	h_uncband -> SetBinContent( binind, 1.0 );

  // 	// cout<<uncertainty<<endl;
	
  // }
  
  // h_rat    ->Draw("e1x0");
  // gStyle->SetErrorX(0.5);
  // h_uncband->Draw("samee2");
  
  // TLine * xaxis = new TLine(0,1,xmax,1);
  // if( region == "_SR_EWK" ){
  // 	xaxis = new TLine(50,1,xmax,1);
  // }
  // xaxis->SetLineWidth(2);
  // xaxis->Draw("same");  
 
  drawCMSLatex( c1, 12.9 );

  if( doreweighted ){
	c1->SaveAs(Form("../output/ZMET2015/V08-11-00/plots/Closure/h_%s_comparison_reweighted%s.png", variabletodraw.c_str(), region.c_str() ));
	c1->SaveAs(Form("../output/ZMET2015/V08-11-00/plots/Closure/h_%s_comparison_reweighted%s.pdf", variabletodraw.c_str(), region.c_str() ));  
  }else{
	c1->SaveAs(Form("../output/ZMET2015/V08-11-00/plots/Closure/h_%s_comparison%s.png", variabletodraw.c_str(), region.c_str() ));
	c1->SaveAs(Form("../output/ZMET2015/V08-11-00/plots/Closure/h_%s_comparison%s.pdf", variabletodraw.c_str(), region.c_str() ));  
  }
  
  return;
}


void printYieldTable( vector <float> metcut, TH1F* h_zll, TH1F* h_pho )
{

  vector <double> val_zjets;
  vector <double> err_zjets;
  vector <double> val_gjets;
  vector <double> err_gjets;
  vector <double> val_ratio;
  vector <double> err_ratio;
  
  for( size_t i = 0; i < metcut.size(); i++ ){
	val_zjets.push_back(0);
	err_zjets.push_back(0);
	val_gjets.push_back(0);
	err_gjets.push_back(0);
	val_ratio.push_back(0);
	err_ratio.push_back(0);
  }

  for( size_t bini = 0; bini < metcut.size()-1; bini++ ){
	if( bini < metcut.size()-1 ){
	  val_zjets.at(bini) = h_zll->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_zjets.at(bini));
	  val_gjets.at(bini) = h_pho->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_gjets.at(bini));
	}
	if( bini == metcut.size()-1 ){
	  if( metcut.at(bini+1) == -1 ){
		val_zjets.at(bini) = h_zll->IntegralAndError( metcut.at(bini)+1, -1, err_zjets.at(bini));
		val_gjets.at(bini) = h_pho->IntegralAndError( metcut.at(bini)+1, -1, err_gjets.at(bini));
	  }
	  else{
		val_zjets.at(bini) = h_zll->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_zjets.at(bini));
		val_gjets.at(bini) = h_pho->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_gjets.at(bini));
	  }
	}  
  }
  
  cout<<"$\\mathrm{E_{T}^{miss} [GeV]}$ &";
  for( size_t bini = 0; bini < metcut.size()-2; bini++ ){
	cout<<Form("%.0f - %.0f & ", metcut.at(bini), metcut.at(bini+1) );
  }
  if( metcut.at(metcut.size()-1) == -1 ){ cout<<Form("$\\geq$ %.0f \\\\", metcut.at(metcut.size()-2) );}
  else{ 	cout<<Form("%.0f - %.0f \\\\", metcut.at(metcut.size()-2), metcut.at(metcut.size()-1) );}

  cout<<endl;

  cout<<"\\hline "<<endl;

  string histtitle1 = h_zll->GetTitle();
  histtitle1 += "&";
  // cout<<Form("%s& ", histtitle1.c_str());
  cout<<histtitle1;
  for( size_t bini = 0; bini < val_zjets.size()-1; bini++ ){
	if( bini < val_zjets.size()-2 ){
	  if( val_zjets.at(bini) < 0.05 || err_zjets.at(bini) < 0.05 ){ cout<<Form(" %.2f $\\pm$ %.2f & ", val_zjets.at(bini), err_zjets.at(bini));}
	  else{                                                         cout<<Form(" %.1f $\\pm$ %.1f & ", val_zjets.at(bini), err_zjets.at(bini));}
	}
	if( bini == val_zjets.size()-2 ){
	  if( val_zjets.at(bini) < 0.05 || err_zjets.at(bini) < 0.05 ){ cout<<Form(" %.2f $\\pm$ %.2f \\\\ ", val_zjets.at(bini), err_zjets.at(bini));}
	  else{                                                         cout<<Form(" %.1f $\\pm$ %.1f \\\\ ", val_zjets.at(bini), err_zjets.at(bini));}
	}
  }
  cout<<endl;

  string histtitle2 = h_pho->GetTitle();  
  histtitle2 += "&";
  // cout<<Form("%s& ", histtitle2.c_str());
  cout<<histtitle2;
  for( size_t bini = 0; bini < val_gjets.size()-1; bini++ ){
	if( bini < val_gjets.size()-2 ){
	  if( val_gjets.at(bini) < 0.05 || err_gjets.at(bini) < 0.05 ){ cout<<Form(" %.2f $\\pm$ %.2f & ", val_gjets.at(bini), err_gjets.at(bini));}
	  else{                                                         cout<<Form(" %.1f $\\pm$ %.1f & ", val_gjets.at(bini), err_gjets.at(bini));}
	}
	if( bini == val_gjets.size()-2 ){
	  if( val_gjets.at(bini) < 0.05 || err_zjets.at(bini) < 0.05 ){ cout<<Form(" %.2f $\\pm$ %.2f \\\\ ", val_gjets.at(bini), err_gjets.at(bini));}
	  else{                                                         cout<<Form(" %.1f $\\pm$ %.1f \\\\ ", val_gjets.at(bini), err_gjets.at(bini));}
	}
  }
  cout<<endl<<"\\hline"<<endl;

  for( size_t bini = 0; bini < val_ratio.size()-1; bini++ ){
	val_ratio.at(bini) = val_zjets.at(bini)/val_gjets.at(bini);
	err_ratio.at(bini) = err_mult( val_zjets.at(bini), val_gjets.at(bini), err_zjets.at(bini), err_gjets.at(bini), val_ratio.at(bini));
  }
  
  cout<<"ratio& ";
  for( size_t bini = 0; bini < val_zjets.size()-1; bini++ ){
	if( bini < val_zjets.size()-2 )
	  cout<<Form(" %.2f $\\pm$ %.2f & ", val_ratio.at(bini), err_ratio.at(bini));
	if( bini == val_zjets.size()-2 )
	  cout<<Form(" %.2f $\\pm$ %.2f \\\\ ", val_ratio.at(bini), err_ratio.at(bini));
  }
  cout<<endl<<"\\hline"<<endl;

  return;

}
