#include "TH1F.h"
#include "TFile.h"
#include "TLine.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPad.h"
#include "TLatex.h"

#include <iostream>

#include "../sharedCode/histTools.cc"

using namespace std;

void printYieldTable( vector <float> metcut, TH1F* h_zll, TH1F* h_pho );
  
void compareMET( std::string iter = "", std::string region = "", float luminosity = 1.0 )
{

  string sample = "zjetsmlm";
  
  std::string filename = Form("../output/%s/%s%s_novtxweight_hists.root", iter.c_str(), sample.c_str(), region.c_str() );
  TFile *infile = new TFile(filename.c_str());

  TH1F * h_zll = (TH1F*)infile->Get("h_ll_event_met_rawgt1jet_passtrig")->Clone("h_zll");


  TFile *infile_ph = new TFile(Form("../output/V08-07-00/All_MC%s_novtxweight_templates.root", region.c_str()));
  TH1F * h_pho = (TH1F*)infile_ph->Get("h_template_njetsind_0_htind_0_ptind_0")->Clone("h_pho");

  h_zll->Scale(luminosity);
  h_pho->Scale(luminosity);

  float rescaleEWK_zll = h_zll->Integral(h_zll->FindBin(50),h_zll->FindBin(100));
  float rescaleEWK_pho = h_pho->Integral(h_zll->FindBin(50),h_zll->FindBin(100));

  float rescaleEWK = rescaleEWK_zll/rescaleEWK_pho;

  h_pho->Scale(1./h_pho->GetSumOfWeights());

  if( region == "_SR_EWK" ){
	h_pho->Scale(rescaleEWK);
  }else{
	h_pho->Scale(h_zll->GetSumOfWeights());
  }

  
  //MAKE TABLES
  vector <float> metcut;

  // metcut.push_back(0.0);
  // metcut.push_back(50);
  // metcut.push_back(100);
  // metcut.push_back(-1);
  // printYieldTable( metcut, h_zll, h_pho );

  metcut.clear();
  metcut.push_back(0.0);
  metcut.push_back(50);
  metcut.push_back(100);
  metcut.push_back(150);
  metcut.push_back(150);
  metcut.push_back(225);
  metcut.push_back(-1);
  printYieldTable( metcut, h_zll, h_pho );

  // metcut.clear();
  // metcut.push_back(150);
  // metcut.push_back(225);
  // metcut.push_back(300);
  // metcut.push_back(-1);
  // printYieldTable( metcut, h_zll, h_pho );

  //MAKE PLOTS

  int rebin = 10;
  
  h_zll->Rebin(rebin);
  h_pho->Rebin(rebin);

  float xmax = 350;
  
  updateoverflow( h_zll , xmax );
  updateoverflow( h_pho , xmax );

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
  h_pho->SetFillColor(kBlue);
  h_pho->SetFillStyle(1001);
  
  h_zll->GetXaxis()->SetLabelSize(0);
  h_zll->GetYaxis()->SetLabelSize(0.05);
  h_zll->GetYaxis()->SetTitleOffset(1.5);
  h_zll->GetYaxis()->SetTitleSize(0.05);
  h_zll->GetYaxis()->SetTitle(Form("Events/%.0f GeV", (float)rebin));
  h_zll->GetXaxis()->SetRangeUser(0,xmax);
  h_zll->GetYaxis()->SetRangeUser(2e-3*luminosity,3e4*luminosity);
  h_zll->SetMarkerStyle(8);
  h_zll->SetMarkerSize(0.75);

  h_zll->Draw("e1");
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

  h_rat->GetYaxis()->SetRangeUser(0,2);
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

  h_rat->Draw("e1x0");

  TLine * xaxis = new TLine(0,1,xmax,1);
  xaxis->SetLineWidth(2);
  xaxis->Draw("same");  
 
  drawCMSLatex( c1, luminosity );

  c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_met_closure%s.png", iter.c_str(), region.c_str() ));
  c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_met_closure%s.pdf", iter.c_str(), region.c_str() ));
  
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
	  val_zjets.at(bini) = h_zll->IntegralAndError( metcut.at(bini), metcut.at(bini+1)-1, err_zjets.at(bini));
	  val_gjets.at(bini) = h_pho->IntegralAndError( metcut.at(bini), metcut.at(bini+1)-1, err_gjets.at(bini));
	}
	if( bini == metcut.size()-1 ){
	  if( metcut.at(bini+1) == -1 ){
		val_zjets.at(bini) = h_zll->IntegralAndError( metcut.at(bini), -1, err_zjets.at(bini));
		val_gjets.at(bini) = h_pho->IntegralAndError( metcut.at(bini), -1, err_gjets.at(bini));
	  }
	  else{
		val_zjets.at(bini) = h_zll->IntegralAndError( metcut.at(bini), metcut.at(bini+1)-1, err_zjets.at(bini));
		val_gjets.at(bini) = h_pho->IntegralAndError( metcut.at(bini), metcut.at(bini+1)-1, err_gjets.at(bini));
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
	if( bini == val_zjets.size()-2 )
	  if( val_zjets.at(bini) < 0.05 || err_zjets.at(bini) < 0.05 ){ cout<<Form(" %.2f $\\pm$ %.2f \\\\ ", val_zjets.at(bini), err_zjets.at(bini));}
	  else{                                                         cout<<Form(" %.1f $\\pm$ %.1f \\\\ ", val_zjets.at(bini), err_zjets.at(bini));}
  }
  cout<<endl;

  cout<<"$\\mathrm{\\gamma+jets}$& ";
  for( size_t bini = 0; bini < val_gjets.size()-1; bini++ ){
	if( bini < val_gjets.size()-2 ){
	  if( val_gjets.at(bini) < 0.05 || err_gjets.at(bini) < 0.05 ) cout<<Form(" %.2f $\\pm$ %.2f & ", val_gjets.at(bini), err_gjets.at(bini));
	  else                                                         cout<<Form(" %.1f $\\pm$ %.1f & ", val_gjets.at(bini), err_gjets.at(bini));
	}
	if( bini == val_gjets.size()-2 ){
	  if( val_gjets.at(bini) < 0.05 || err_zjets.at(bini) < 0.05 ) cout<<Form(" %.2f $\\pm$ %.2f \\\\ ", val_gjets.at(bini), err_gjets.at(bini));
	  else                                                         cout<<Form(" %.1f $\\pm$ %.1f \\\\ ", val_gjets.at(bini), err_gjets.at(bini));
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
