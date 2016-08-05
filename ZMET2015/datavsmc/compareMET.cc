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
  
void compareMET( std::string iter = "", std::string region = "", float luminosity = 1.0 )
{

  string sample = "zjetsmlm";
  bool scaletotemplates = false;

  string dilep = "ll";
  // dilep = "mm";
  // dilep = "ee";

  string variabletodraw = "ht";
  // variabletodraw = "njets";
  variabletodraw = "met";
  
  std::string filename = Form("../output/%s/%s%s_novtxweight_hists.root", iter.c_str(), sample.c_str(), region.c_str() );
  TFile *infile = new TFile(filename.c_str());

  TH1F * h_zll                          = (TH1F*)infile->Get(Form("h_%s_event_met_rawgt1jet_passtrig", dilep.c_str() ))->Clone("h_zll");
  if( variabletodraw == "ht" ) h_zll    = (TH1F*)infile->Get(Form("h_%s_event_ht_highbin_passtrig"   , dilep.c_str() ))->Clone("h_zll");
  if( variabletodraw == "njets" ) h_zll = (TH1F*)infile->Get(Form("h_%s_event_njets_passtrig"        , dilep.c_str() ))->Clone("h_zll");

  TFile *infile_ph = new TFile(Form("../output/V08-11-00/All_MC%s_novtxweight_templates.root", region.c_str()));
  TH1F * h_pho                          = (TH1F*)infile_ph->Get("h_template_njetsind_0_htind_0_ptind_0")->Clone("h_pho");
  if( variabletodraw == "ht" ) h_pho    = (TH1F*)infile_ph->Get("h_ph_event_ht_highbin_passtrig"       )->Clone("h_pho");
  if( variabletodraw == "njets" ) h_pho = (TH1F*)infile_ph->Get("h_ph_event_njets_passtrig"            )->Clone("h_pho");
  
  h_zll->Scale(luminosity);
  h_pho->Scale(luminosity);
  
  float rescaleEWK_zll = h_zll->Integral(h_zll->FindBin(50),h_zll->FindBin(100));
  float rescaleEWK_pho = h_pho->Integral(h_zll->FindBin(50),h_zll->FindBin(100));

  float rescaleEWK = rescaleEWK_zll/rescaleEWK_pho;

  float xmax = 350;
  if( variabletodraw == "ht"    ) xmax = 1500;
  if( variabletodraw == "njets" ) xmax = 20;
  updateoverflow( h_zll , xmax-1 );
  updateoverflow( h_pho , xmax-1 );
  
  h_pho->Scale(1./h_pho->GetSumOfWeights());

  if( region == "_SR_EWK" ){
	h_pho->Scale(rescaleEWK);
  }else{
	h_pho->Scale(h_zll->GetSumOfWeights());
  }
  
  if( variabletodraw == "ht" || variabletodraw == "njets" ) h_pho->Scale(h_zll->GetSumOfWeights()/h_pho->GetSumOfWeights());

  if( scaletotemplates ){

	if( region == "_SRA_bveto" )  h_zll->Scale(6480.15/h_zll->Integral(h_zll->FindBin(0),h_zll->FindBin(50)-1));
	if( region == "_SRA_withb" )  h_zll->Scale(1085.10/h_zll->Integral(h_zll->FindBin(0),h_zll->FindBin(50)-1));
	if( region == "_SRB_bveto" )  h_zll->Scale(8566.25/h_zll->Integral(h_zll->FindBin(0),h_zll->FindBin(50)-1));
	if( region == "_SRB_withb" )  h_zll->Scale(2493.89/h_zll->Integral(h_zll->FindBin(0),h_zll->FindBin(50)-1));
	if( region == "_SR_ATLAS" )   h_zll->Scale(6945.52/h_zll->Integral(h_zll->FindBin(0),h_zll->FindBin(50)-1));
	h_pho->Scale(h_zll->GetSumOfWeights()/h_pho->GetSumOfWeights());
  }

  vector <float> metcut_row1;
  metcut_row1.clear();
  metcut_row1.push_back(0.0);
  metcut_row1.push_back(50);
  metcut_row1.push_back(100);
  metcut_row1.push_back(150);
  if( region == "_2jets_inclusive" ) metcut_row1.push_back(-1);
  printYieldTable( metcut_row1, h_zll, h_pho );

  if( region != "_2jets_inclusive" ){
	vector <float> metcut_row2;
	metcut_row2.clear();
	metcut_row2.push_back(150);
	metcut_row2.push_back(225);
	if( region != "_SR_ATLAS" ) metcut_row2.push_back(300);
	metcut_row2.push_back(-1);
	printYieldTable( metcut_row2, h_zll, h_pho );
  }
  
  //MAKE TABLES
  vector <float> metcut;
  metcut.clear();
  metcut.push_back(0.0);
  metcut.push_back(50);
  metcut.push_back(100);
  metcut.push_back(150);
  if( region != "_2jets_inclusive" ){
  metcut.push_back(225);
  if( region != "_SR_ATLAS" ) metcut.push_back(300);
  }
  metcut.push_back(-1);

  //MAKE PLOTS

  int nbinsx = metcut.size();

  double xbins[(int)(nbinsx)];

  for( size_t binind = 0; binind < metcut.size()-1; binind++ ){
	xbins[binind] = metcut.at(binind);
  }
  
  xbins[nbinsx-1] = xmax;
  
  int rebin = 50;
  if( variabletodraw == "njets" ) {
	rebin = 1;
  }

  if( variabletodraw == "ht" || variabletodraw == "njets"/* || variabletodraw == "met"*/ ) {
	h_zll->Rebin(rebin);
	h_pho->Rebin(rebin);
  }else{
	h_zll = (TH1F*)h_zll->Rebin(nbinsx-1, "h_zll_rebinned", xbins);
	h_pho = (TH1F*)h_pho->Rebin(nbinsx-1, "h_pho_rebinned", xbins);
  }


  // for( int binind = 0; binind < metcut.size()-1; binind++ ){
  // 	cout<<metcut.at(binind)<<" | zll: "<<h_zll->GetBinContent(h_zll->FindBin(metcut.at(binind)))<<endl;
  // 	cout<<metcut.at(binind)<<" | pho: "<<h_pho->GetBinContent(h_zll->FindBin(metcut.at(binind)))<<endl;
  // }

  
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

  h_zll->SetLineWidth(2);
  h_pho->SetFillColor(kAzure+5);
  h_pho->SetFillStyle(1001);
  
  h_zll->GetXaxis()->SetLabelSize(0);
  h_zll->GetYaxis()->SetLabelSize(0.05);
  h_zll->GetYaxis()->SetTitleOffset(1.5);
  h_zll->GetYaxis()->SetTitleSize(0.05);
  h_zll->GetYaxis()->SetTitle(Form("Events/%.0f GeV", (float)rebin));
  if( region == "_SR_EWK" ) h_zll->GetXaxis()->SetRangeUser(50,xmax);
  if( region != "_SR_EWK" ) h_zll->GetXaxis()->SetRangeUser(0,xmax);
  h_zll->GetYaxis()->SetRangeUser(2e-2,h_zll->GetMaximum()*1e2);
  h_zll->SetMarkerStyle(8);
  h_zll->SetMarkerSize(0.75);

  h_zll->Draw("e1x0");
  h_pho->Draw("samehist");
  h_zll->Draw("samex0e1");
  
  pad->RedrawAxis();

  TLegend *l1 = new TLegend(0.6, 0.6, 0.9, 0.85);    
  l1->SetLineColor(kWhite);    
  l1->SetShadowColor(kWhite);    
  l1->SetFillColor(kWhite);    
  l1->AddEntry( h_zll , "Z+jets MC"       , "lpe");
  l1->AddEntry( h_pho , "#gamma+jets MC"       , "f");
  l1->Draw("same");
  
  c1->cd();
	
  TPad *rat_pad = new TPad( "p_main", "p_main", 0.0, 0.0, 1.0, 0.3);
  rat_pad->SetBottomMargin(0.36);
  rat_pad->SetRightMargin(0.07);
  rat_pad->SetTopMargin(0.07);
  rat_pad->SetLeftMargin(0.18);
  rat_pad->Draw();
  rat_pad->cd();
  rat_pad->SetGridy();

  TH1F* h_rat = (TH1F*)h_zll->Clone("h_rat");

  h_rat->Divide(h_pho);

  h_rat->GetYaxis()->SetRangeUser(0.0,2.0);
  h_rat->GetYaxis()->SetLabelSize(0.12);
  h_rat->GetXaxis()->SetLabelSize(0.12);
  h_rat->GetYaxis()->SetNdivisions(5);

  h_rat->GetYaxis()->SetTitle("#frac{Z+jets}{#gamma+jets}");
  h_rat->GetYaxis()->SetTitleSize(0.12);
  h_rat->GetYaxis()->SetTitleOffset(0.5);
  h_rat->GetYaxis()->CenterTitle();
  // cout<<h_rat->GetYaxis()->GetTitleSize()<<endl;

  h_rat->GetXaxis()->SetTitle("E_{T}^{miss} GeV");
  h_rat->GetXaxis()->SetTitleOffset(0.9);
  h_rat->GetXaxis()->SetTitleSize(0.15);

  h_rat->SetMarkerStyle(8);
  h_rat->SetMarkerSize(0.75);

  TH1F* h_uncband = (TH1F*)h_zll->Clone("h_uncband");  
  h_uncband->SetFillColor(kBlue+3);
  h_uncband->SetFillStyle(3004);
  h_uncband->SetMarkerSize(0);  

  for( int binind = 1; binind < h_uncband->GetNbinsX()+1; binind++ ){

	float binlowedge = h_uncband->GetBinLowEdge(binind);
	float uncertainty = 0.0;

	if( region == "_SR_ATLAS" ){
	  if(      binlowedge <  50 ) uncertainty = 0.02;
	  else if( binlowedge < 100 ) uncertainty = 0.10;
	  else if( binlowedge < 150 ) uncertainty = 0.25;
	  else if( binlowedge < 225 ) uncertainty = 0.35;
	  else if( binlowedge < 350 ) uncertainty = 0.40;
	}

	if( region == "_SRA_bveto" ){
	  if(      binlowedge <   50 ) uncertainty = 0.02;
	  else if( binlowedge <  100 ) uncertainty = 0.10;
	  else if( binlowedge <  300 ) uncertainty = 0.20;
	  else if( binlowedge <  350 ) uncertainty = 0.25;
	}
  
	if( region == "_SRA_withb" ){
	  if(      binlowedge <   50 ) uncertainty = 0.02;
	  else if( binlowedge <  100 ) uncertainty = 0.07;
	  else if( binlowedge <  225 ) uncertainty = 0.20;
	  else if( binlowedge <  300 ) uncertainty = 0.40;
	  else if( binlowedge <  350 ) uncertainty = 0.40;
	}
  
	if( region == "_SRB_bveto" ){
	  if(      binlowedge <   50 ) uncertainty = 0.01;
	  else if( binlowedge <  100 ) uncertainty = 0.06;
	  else if( binlowedge <  150 ) uncertainty = 0.10;
	  else if( binlowedge <  225 ) uncertainty = 0.10;
	  else if( binlowedge <  350 ) uncertainty = 0.35;
	}
  
	if( region == "_SRB_withb" ){
	  if(      binlowedge <   50 ) uncertainty = 0.01;
	  else if( binlowedge <  100 ) uncertainty = 0.10;
	  else if( binlowedge <  150 ) uncertainty = 0.20;
	  else if( binlowedge <  225 ) uncertainty = 0.25;
	  else if( binlowedge <  300 ) uncertainty = 0.30;
	  else if( binlowedge <  350 ) uncertainty = 0.30;
	}
  
	if( region == "_SR_EWK" ){
	  if(      binlowedge <  100 ) uncertainty = 0.02;
	  else if( binlowedge <  300 ) uncertainty = 0.10;
	  else if( binlowedge <  350 ) uncertainty = 0.15;
	}
  
	if( region == "_2jets_inclusive" ){
	  if(      binlowedge <   50 ) uncertainty = 0.01;
	  else if( binlowedge <  150 ) uncertainty = 0.02;
	  else if( binlowedge <  350 ) uncertainty = 0.05;
	}
  
	h_uncband -> SetBinError  ( binind, uncertainty );
	h_uncband -> SetBinContent( binind, 1.0 );

	// cout<<uncertainty<<endl;
	
  }
  
  h_rat    ->Draw("e1x0");
  gStyle->SetErrorX(0.5);
  h_uncband->Draw("samee2");
  
  TLine * xaxis = new TLine(0,1,xmax,1);
  if( region == "_SR_EWK" ){
	xaxis = new TLine(50,1,xmax,1);
  }
  xaxis->SetLineWidth(2);
  xaxis->Draw("same");  
 
  drawCMSLatex( c1, luminosity );

  // if( variabletodraw == "njets" ) {
  // 	c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_njets_closure%s.png", iter.c_str(), region.c_str() ));
  // 	c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_njets_closure%s.pdf", iter.c_str(), region.c_str() ));
  // }else if( variabletodraw == "ht" ) {
  // 	c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_ht_closure%s.png", iter.c_str(), region.c_str() ));
  // 	c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_ht_closure%s.pdf", iter.c_str(), region.c_str() ));
  // }else{
  // 	c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_met_ll_closure%s.png", iter.c_str(), region.c_str() ));
  // 	c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_met_ll_closure%s.pdf", iter.c_str(), region.c_str() ));
  // }

  c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_%s_%s_closure%s.png", iter.c_str(), variabletodraw.c_str(), dilep.c_str(), region.c_str() ));
  c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_%s_%s_closure%s.pdf", iter.c_str(), variabletodraw.c_str(), dilep.c_str(), region.c_str() ));
  
  
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
  cout<<"Z+jets& ";
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

  cout<<"$\\mathrm{\\gamma+jets}$& ";
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
