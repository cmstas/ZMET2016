#include <fstream>
#include <iostream>

#include "TH1F.h"
#include "TH2F.h"
#include "TPad.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLine.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TFile.h"
#include "TBox.h"

using namespace std;

int makeLimitHists()
{

  
  TH1F * h_susyxsecs  = NULL;
  TFile * f_susyxsecs = NULL;

  f_susyxsecs = TFile::Open("xsec_susy_13tev.root","READ");
  h_susyxsecs = (TH1F*)f_susyxsecs->Get("h_xsec_gluino")->Clone("h_susyxsecs");

  
  //"Official" SUSY palette
  int mypalette[255];
  int NRGBs = 5;
  int NCont = 255;
  double stops[] = {0.00, 0.34, 0.61, 0.84, 1.00};
  double red[]   = {0.50, 0.50, 1.00, 1.00, 1.00};
  double green[] = {0.50, 1.00, 1.00, 0.60, 0.50};
  double blue[]  = {1.00, 1.00, 0.50, 0.40, 0.50};
  int FI = TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  for (int i=0;i<NCont;i++){ mypalette[i] = FI+i;}
  gStyle->SetPalette(NCont,mypalette);  

  TFile * f_rvalues = TFile::Open("r-values_T5ZZ.root","READ");  
  
  TH2F * massplane        = (TH2F*) f_rvalues->Get("hExp")   -> Clone("massplane");
  TH2F * massplane_obs    = (TH2F*) f_rvalues->Get("hObs")   -> Clone("massplane_obs");
  TH2F * massplane_obs_up = (TH2F*) f_rvalues->Get("hObs")   -> Clone("massplane_obs_up");
  TH2F * massplane_obs_dn = (TH2F*) f_rvalues->Get("hObs")   -> Clone("massplane_obs_dn");
  TH2F * massplane_exp_up = (TH2F*) f_rvalues->Get("hExp1p") -> Clone("massplane_exp_up");
  TH2F * massplane_exp_dn = (TH2F*) f_rvalues->Get("hExp1m") -> Clone("massplane_exp_dn");
  // TH2F * massplane_xsec   = new TH2F("massplane_xsec","", 27,25,1375,25,75.0,1325.0);

  TH2F * massplane_xsec   = (TH2F*) massplane->Clone("massplane_xsec");
  TH2F * efficiency       = (TH2F*) massplane->Clone("efficiency"    );

  double contours[1];
  contours[0] = 1.0;

  TH2F * contourplot = dynamic_cast<TH2F*>(massplane->Clone("contourplot"));

  massplane_xsec->GetXaxis()->SetRangeUser(975,1775);
  // massplane_xsec->GetYaxis()->SetRangeUser(125,1925);

  massplane_xsec->GetXaxis()->SetLabelSize(0.035);
  massplane_xsec->GetYaxis()->SetLabelSize(0.035);
  massplane_xsec->GetXaxis()->SetTitle("gluino mass [GeV]");
  massplane_xsec->GetYaxis()->SetTitle("#chi_{1}^{0} mass [GeV]");
  massplane_xsec->GetZaxis()->SetTitle("95% CL upper limit on #sigma [pb]");
  massplane_xsec->GetZaxis()->SetRangeUser(1e-2,1e0);
  massplane_xsec->GetZaxis()->SetLabelSize(0.035);

  TCanvas *c_massplane = new TCanvas("c_massplane", "", 800, 800);
  c_massplane->cd();
  TPad *padt = new TPad("p_tex", "p_tex", 0.0, 0.0, 1.0, 1.0);
  padt->SetTopMargin(0.08);
  padt->SetBottomMargin(0.16);
  padt->SetRightMargin(0.17);
  padt->SetLeftMargin(0.18);
  padt->Draw();
  padt->cd();
  padt->SetLogz();

  //edit here
  massplane_xsec->GetYaxis()->SetRangeUser(125,1725);
  massplane_xsec->GetYaxis()->SetRangeUser(125,1925);
  massplane_xsec->Draw("colz");

  contourplot->SetContour(1, contours);
  contourplot->SetLineWidth(4);
  contourplot->SetLineStyle(2);
  contourplot->SetLineColor(kRed);
  contourplot->Smooth();
  massplane_exp_up->SetContour(1, contours);
  massplane_exp_up->SetLineWidth(2);
  massplane_exp_up->SetLineStyle(2);
  massplane_exp_up->SetLineColor(kRed);
  massplane_exp_up->Smooth();
  massplane_exp_dn->SetContour(1, contours);
  massplane_exp_dn->SetLineWidth(2);
  massplane_exp_dn->SetLineStyle(2);
  massplane_exp_dn->SetLineColor(kRed);
  massplane_exp_dn->Smooth();

  massplane_obs->SetContour(1, contours);
  massplane_obs->SetLineWidth(4);
  massplane_obs->SetLineColor(kBlack);
  massplane_obs->SetLineStyle(1);
  massplane_obs->Smooth();
  massplane_obs_up->SetContour(1, contours);
  massplane_obs_up->SetLineWidth(2);
  massplane_obs_up->SetLineColor(kBlack);
  massplane_obs_up->Smooth();
  massplane_obs_dn->SetContour(1, contours);
  massplane_obs_dn->SetLineWidth(2);
  massplane_obs_dn->SetLineColor(kBlack);
  massplane_obs_dn->Smooth();

  //set diag to 1 for contours
  for( int binx = 0; binx < contourplot->GetNbinsX()+1; binx++ ){
	for( int biny = 0; biny < contourplot->GetNbinsY()+1; biny++ ){
	  // if( binx*50 > 925 ){
	  // 	int mainbin = contourplot->FindBin(biny*50, binx*50);
	  // 	if( biny*50 > (binx*50 - 100) ) contourplot     ->SetBinContent(mainbin,1.0);
	  // 	if( biny*50 > (binx*50 - 100) ) massplane_obs   ->SetBinContent(mainbin,1.0);
	  // 	if( biny*50 > (binx*50 - 100) ) massplane_obs_up->SetBinContent(mainbin,1.0);
	  // 	if( biny*50 > (binx*50 - 100) ) massplane_obs_dn->SetBinContent(mainbin,1.0);
	  // 	if( biny*50 > (binx*50 - 100) ) massplane_exp_up->SetBinContent(mainbin,1.0);
	  // 	if( biny*50 > (binx*50 - 100) ) massplane_exp_dn->SetBinContent(mainbin,1.0);
	  // 	if( biny*50 > (binx*50 - 100) ) massplane_xsec  ->SetBinContent(mainbin,0.0);
	  // }

  	  // if( (biny*50 - binx*50) > 350 ) contourplot->SetBinContent(binx,biny,1.0);
  	  // if( (biny*50 - binx*50) > 350 ) massplane_obs->SetBinContent(binx,biny,1.0);
  	  // if( (biny*50 - binx*50) > 350 ) massplane_obs_up->SetBinContent(binx,biny,1.0);
  	  // if( (biny*50 - binx*50) > 350 ) massplane_obs_dn->SetBinContent(binx,biny,1.0);
  	  // if( (biny*50 - binx*50) > 350 ) massplane_exp_up->SetBinContent(binx,biny,1.0);
  	  // if( (biny*50 - binx*50) > 350 ) massplane_exp_dn->SetBinContent(binx,biny,1.0);
  	  // if( (biny*50 - binx*50) > 350 ) massplane_xsec->SetBinContent(binx,biny,0.0);

  	  if( (biny*50 - binx*50) > 350 ) contourplot     ->SetBinContent(binx,biny,0.99);
  	  if( (biny*50 - binx*50) > 350 ) massplane_obs   ->SetBinContent(binx,biny,0.99);
  	  if( (biny*50 - binx*50) > 350 ) massplane_obs_up->SetBinContent(binx,biny,0.99);
  	  if( (biny*50 - binx*50) > 350 ) massplane_obs_dn->SetBinContent(binx,biny,0.99);
  	  if( (biny*50 - binx*50) > 350 ) massplane_exp_up->SetBinContent(binx,biny,0.99);
  	  if( (biny*50 - binx*50) > 350 ) massplane_exp_dn->SetBinContent(binx,biny,0.99);
  	  if( (biny*50 - binx*50) > 350 ) massplane_xsec  ->SetBinContent(binx,biny,0.0);

	  if( binx*50 > 1725 ){
		if( (biny*50 - binx*50) > 400 ) contourplot     ->SetBinContent(binx,biny,0.0);
		if( (biny*50 - binx*50) > 400 ) massplane_obs   ->SetBinContent(binx,biny,0.0);
		if( (biny*50 - binx*50) > 400 ) massplane_obs_up->SetBinContent(binx,biny,0.0);
		if( (biny*50 - binx*50) > 400 ) massplane_obs_dn->SetBinContent(binx,biny,0.0);
		if( (biny*50 - binx*50) > 400 ) massplane_exp_up->SetBinContent(binx,biny,0.0);
		if( (biny*50 - binx*50) > 400 ) massplane_exp_dn->SetBinContent(binx,biny,0.0);
		if( (biny*50 - binx*50) > 400 ) massplane_xsec  ->SetBinContent(binx,biny,0.0);
	  }
	}
  }

  // multiply by susy xsec
  for( int binx = 12; binx < 36; binx++ ){
  	for( int biny = 2; biny < binx-1; biny++ ){
	  int mgluino = binx*50;
	  int truebin = massplane_xsec->FindBin(binx*50,biny*50);
	  // massplane_xsec->SetBinContent(truebin, massplane_xsec->GetBinContent(truebin)/(0.19175)*h_susyxsecs->GetBinContent(h_susyxsecs->FindBin(mgluino)));
	  massplane_xsec->SetBinContent(truebin, massplane_xsec->GetBinContent(truebin)*(0.19175)*(7.65)*h_susyxsecs->GetBinContent(h_susyxsecs->FindBin(mgluino)));
	  massplane_obs_up->SetBinContent(truebin, massplane_obs->GetBinContent(truebin)*1.15);
	  massplane_obs_dn->SetBinContent(truebin, massplane_obs->GetBinContent(truebin)*0.85);
	}
  }
  
  massplane_xsec->Draw("colz");
  contourplot->Draw("samecont3");
  // contourplot->Draw("colz");
  massplane_obs->Draw("samecont2");
  massplane_obs_up->Draw("samecont2");
  massplane_obs_dn->Draw("samecont2");
  massplane_exp_up->Draw("samecont3");
  massplane_exp_dn->Draw("samecont3");

  TLine * diag_01 = new TLine(975,835,1675,1535);
  diag_01->SetLineWidth(7);
  diag_01->SetLineColor(kWhite);
  diag_01->SetLineStyle(1);
  diag_01->Draw("same");

  TLine * diag_0 = new TLine(975,855,1675,1555);
  diag_0->SetLineWidth(7);
  diag_0->SetLineColor(kWhite);
  diag_0->SetLineStyle(1);
  diag_0->Draw("same");

  TLine * diag_1 = new TLine(975,875,1675,1575);
  diag_1->SetLineWidth(7);
  diag_1->SetLineColor(kWhite);
  diag_1->SetLineStyle(1);
  diag_1->Draw("same");

  TLine * diag_2 = new TLine(975,895,1675,1595);
  diag_2->SetLineWidth(7);
  diag_2->SetLineColor(kWhite);
  diag_2->SetLineStyle(1);
  diag_2->Draw("same");

  TLine * diag_3 = new TLine(975,915,1675,1615);
  diag_3->SetLineWidth(7);
  diag_3->SetLineColor(kWhite);
  diag_3->SetLineStyle(1);
  diag_3->Draw("same");

  TLine * diag_4 = new TLine(975,935,1675,1635);
  diag_4->SetLineWidth(7);
  diag_4->SetLineColor(kWhite);
  diag_4->SetLineStyle(1);
  diag_4->Draw("same");

  TLine * diag_5 = new TLine(975,955,1675,1655);
  diag_5->SetLineWidth(7);
  diag_5->SetLineColor(kWhite);
  diag_5->SetLineStyle(1);
  diag_5->Draw("same");

  padt->RedrawAxis();

  TBox * box = new TBox(975,1500,1775,1925);
  box->SetFillColor(kWhite);
  box->Draw("same");

  TLegend *l1 = new TLegend(0.205, 0.77, 0.71, 0.83);    
  l1->SetLineColor(kWhite);    
  l1->SetTextFont(42);    
  l1->SetTextSize(0.038);
  l1->SetShadowColor(kWhite);    
  l1->SetFillColor(kWhite);    
  l1->AddEntry(contourplot , "Expected limit, #pm 1 #sigma_{exp.}"            , "l");
  // l1->AddEntry(massplane_obs , "Observed limit"            , "l");
  l1->AddEntry(massplane_obs , "Observed limit, #pm 1 #sigma_{theory}"            , "l");
  l1->Draw("same");

  TLine * top_margin = new TLine(975,1875,1775,1875);
  top_margin->SetLineWidth(4);
  top_margin->SetLineColor(kBlack);
  top_margin->SetLineStyle(1);
  top_margin->Draw("same");

  TLine * bot_margin = new TLine(975,1500,1775,1500);
  bot_margin->SetLineWidth(4);
  bot_margin->SetLineColor(kBlack);
  bot_margin->SetLineStyle(1);
  bot_margin->Draw("same");

  TLine * lef_margin = new TLine(975,1500,975,1875);
  lef_margin->SetLineWidth(4);
  lef_margin->SetLineColor(kBlack);
  lef_margin->SetLineStyle(1);
  lef_margin->Draw("same");

  TLine * rig_margin = new TLine(1775,1500,1775,1875);
  rig_margin->SetLineWidth(4);
  rig_margin->SetLineColor(kBlack);
  rig_margin->SetLineStyle(1);
  rig_margin->Draw("same");

  // massplane_xsec->Draw("samecolz");

  // TLine * diag = new TLine(975,775,1575,1375);
  // diag->SetLineWidth(5);
  // diag->SetLineStyle(9);
  // diag->Draw("same");

  TLatex *prctex = NULL;
  prctex = new TLatex(0.215,0.88, "pp #rightarrow #tilde{g} #tilde{g}, #tilde{g}#rightarrow 2j + #chi_{1}^{0}, #chi_{1}^{0} #rightarrow Z#tilde{G}; m_{#tilde{G}} = 1 GeV" );    
  prctex->SetNDC();    
  prctex->SetTextSize(0.032);    
  prctex->SetLineWidth(2);
  prctex->SetTextFont(42);    
  prctex->Draw();

  TLatex *clstex = NULL;
  clstex = new TLatex(0.215,0.84, "NLO + NLL exclusion" );    
  clstex->SetNDC();    
  clstex->SetTextSize(0.032);    
  clstex->SetLineWidth(2);
  clstex->SetTextFont(42);    
  clstex->Draw();


  TLatex *cmstex = NULL;
  cmstex = new TLatex(0.575,0.94, "7.65 fb^{-1} (13 TeV)" );    
  cmstex->SetNDC();    
  cmstex->SetTextSize(0.04);    
  cmstex->SetLineWidth(2);
  cmstex->SetTextFont(42);    
  cmstex->Draw();

  TLatex *cmstexbold = NULL;
  cmstexbold = new TLatex(0.18,0.94, "CMS" );    
  cmstexbold->SetNDC();    
  cmstexbold->SetTextSize(0.05);    
  cmstexbold->SetLineWidth(2);
  cmstexbold->SetTextFont(62);    
  cmstexbold->Draw();

  cmstexbold = new TLatex(0.29,0.94, "Preliminary" );    
  cmstexbold->SetNDC();    
  cmstexbold->SetTextSize(0.0375);    
  cmstexbold->SetLineWidth(2);
  cmstexbold->SetTextFont(12);    
  cmstexbold->Draw();

  c_massplane->SaveAs("T5ZZ_Exclusion_13TeV.pdf");
  // c_massplane->SaveAs("/home/users/cwelke/public_html/T5ZZ_Exclusion_13TeV.pdf");

  TFile * file = new TFile("CLS_CSUL.root","RECREATE");
  file->cd();
  massplane_xsec->Write();
  file->Write();
  file->Close();

  return 0;
}
