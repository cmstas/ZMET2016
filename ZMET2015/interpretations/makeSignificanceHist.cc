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
#include "TGraph.h"
#include "TGraph2D.h"

using namespace std;

int makeSignificanceHist()
{

  float zmin = 0;
  float zmax = 1;

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

  TFile * f_rvalues = TFile::Open("r-values_Significance_T5ZZ.root","READ");  
  
  TH2F * massplane        = (TH2F*) f_rvalues->Get("hSig")   -> Clone("massplane");

  massplane->GetXaxis()->SetRangeUser(1025,1725);
  massplane->GetXaxis()->SetLabelSize(0.035);
  massplane->GetYaxis()->SetLabelSize(0.035);
  massplane->GetXaxis()->SetTitle("gluino mass [GeV]");
  massplane->GetYaxis()->SetTitle("#chi_{1}^{0} mass [GeV]");
  massplane->GetZaxis()->SetTitle("Observed Local Significance (#sigma)");
  massplane->GetZaxis()->SetRangeUser(zmin,zmax);
  massplane->GetZaxis()->SetLabelSize(0.035);
  massplane->GetZaxis()->SetTitleSize(0.045);
  massplane->GetZaxis()->SetTitleOffset(1.25);
  massplane->GetZaxis()->SetLabelSize(0.);
  
  TCanvas *c_massplane = new TCanvas("c_massplane", "", 800, 800);
  c_massplane->cd();
  TPad *padt = new TPad("p_tex", "p_tex", 0.0, 0.0, 1.0, 1.0);
  padt->SetTopMargin(0.08);
  padt->SetBottomMargin(0.16);
  padt->SetRightMargin(0.17);
  padt->SetLeftMargin(0.18);
  padt->Draw();
  padt->cd();
  // padt->SetLogz();

  //edit here
  massplane->GetYaxis()->SetRangeUser(125,1725);
  massplane->GetYaxis()->SetRangeUser(125,1925);
  massplane->Draw("colz");

  TFile * file = new TFile("CLS_Significance.root","RECREATE");
  file->cd();
  massplane->Write();
  file->Write();
  file->Close();
  
  // for( int binx = 0; binx < 31; binx++ ){
  // 	for( int biny = 1; biny < 32; biny++ ){
  // 	  // if( binx*25 < biny*10 && (biny)*10 < 200) continue;
  // 	  int truebin = massplane->FindBin(binx*25,biny*10);
  // 	  if( binx*25 == 250 && biny*10 == 180 ) massplane   -> SetBinContent(truebin,0);
  // 	  int truebinminus1 = massplane->FindBin(binx*25,(biny-1)*10);
  // 	  if( massplane   -> GetBinContent(truebin) <=  0.01 ) massplane   -> SetBinContent(truebin,massplane   -> GetBinContent(truebinminus1));
  // 	  if( massplane   -> GetBinContent(truebin) >= 42    ) massplane   -> SetBinContent(truebin,massplane   -> GetBinContent(truebinminus1));
  // 	  if( binx*25 - biny*10 < 80 ) massplane   -> SetBinContent(truebin,0);
  // 	}
  // }
  
  massplane->Draw("colz");

  //binning needs to correspond to actual binning of TH2F with limits
  vector<double> vmx, vmy, vexp;  
  for( int binx = 18; binx < 44; binx++ ){
  	for( int biny = 2; biny < binx+2; biny++ ){
	  int truebin = massplane->FindBin(binx*50,biny*50);
	  vmx.push_back(binx*50); vmy.push_back(biny*50);
	  vexp     . push_back(massplane        -> GetBinContent(truebin));
	}
  }

  
  TGraph2D gexp("gexp"    , "Expected Limit", vexp.size(), &vmx.at(0), &vmy.at(0), &vexp.at(0));
  TGraph   dots(vmx.size(), &vmx.at(0), &vmy.at(0));

  double xmin = *min_element(vmx.cbegin(), vmx.cend());
  double xmax = *max_element(vmx.cbegin(), vmx.cend());
  double ymin = *min_element(vmy.cbegin(), vmy.cend());
  double ymax = *max_element(vmy.cbegin(), vmy.cend());
  double bin_size = 5;
  int nxbins = max(1, min(500, static_cast<int>(ceil((xmax-xmin)/bin_size))));
  int nybins = max(1, min(500, static_cast<int>(ceil((ymax-ymin)/bin_size))));
  gexp.SetNpx(nxbins);
  gexp.SetNpy(nybins);

  TH2D *hexp = gexp.GetHistogram();  
  hexp->GetZaxis()->SetRangeUser(zmin,zmax);

  hexp   ->Draw("samecolz");

  // gStyle->SetPaintTextFormat("1.1f");
  // massplane->Draw("sametext");

  // TLine * diag_0 = new TLine(110,150,310,350);
  // diag_0->SetLineWidth(7);
  // diag_0->SetLineColor(kWhite);
  // diag_0->SetLineStyle(1);
  // diag_0->Draw("same");

  // for( int i = 1; i < 20; i++ ){
  // 	diag_0 = new TLine(110,150+i*5,310,350+i*5);
  // 	diag_0->SetLineWidth(7);
  // 	diag_0->SetLineColor(kWhite);
  // 	diag_0->SetLineStyle(1);
  // 	diag_0->Draw("same");
  // }
  
  // for( int i = 1; i > -27; i-- ){
  // 	diag_0 = new TLine(110,150+i*5,330,370+i*5);
  // 	diag_0->SetLineWidth(7);
  // 	diag_0->SetLineColor(kWhite);
  // 	diag_0->SetLineStyle(1);
  // 	diag_0->Draw("same");
  // }
  

  TLine * diag_0 = new TLine(1025,1035,1675,1685);
  diag_0->SetLineWidth(7);
  diag_0->SetLineColor(kWhite);
  diag_0->SetLineStyle(1);
  diag_0->Draw("same");

  diag_0 = new TLine(1025,1055,1675,1705);
  diag_0->SetLineWidth(7);
  diag_0->SetLineColor(kWhite);
  diag_0->SetLineStyle(1);
  diag_0->Draw("same");

  diag_0 = new TLine(1025,1075,1675,1725);
  diag_0->SetLineWidth(7);
  diag_0->SetLineColor(kWhite);
  diag_0->SetLineStyle(1);
  diag_0->Draw("same");

  diag_0 = new TLine(1025,1095,1675,1745);
  diag_0->SetLineWidth(7);
  diag_0->SetLineColor(kWhite);
  diag_0->SetLineStyle(1);
  diag_0->Draw("same");

  diag_0 = new TLine(1025,1115,1675,1765);
  diag_0->SetLineWidth(7);
  diag_0->SetLineColor(kWhite);
  diag_0->SetLineStyle(1);
  diag_0->Draw("same");

  padt->RedrawAxis();

  TBox * box = new TBox(1025,1500,1725,1925);
  box->SetFillColor(kWhite);
  box->Draw("same");

  // TLegend *l1 = new TLegend(0.205, 0.77, 0.71, 0.83);    
  // l1->SetLineColor(kWhite);    
  // l1->SetTextFont(42);    
  // l1->SetTextSize(0.038);
  // l1->SetShadowColor(kWhite);    
  // l1->SetFillColor(kWhite);    
  // l1->AddEntry(contourplot , "Expected limit, #pm 1 #sigma_{exp.}"            , "l");
  // // l1->AddEntry(massplane_obs , "Observed limit"            , "l");
  // l1->AddEntry(massplane_obs , "Observed limit, #pm 1 #sigma_{theory}"            , "l");
  // l1->Draw("same");

  TLine * top_margin = new TLine(1025,1925,1725,1925);
  top_margin->SetLineWidth(4);
  top_margin->SetLineColor(kBlack);
  top_margin->SetLineStyle(1);
  top_margin->Draw("same");

  TLine * bot_margin = new TLine(1025,1500,1725,1500);
  bot_margin->SetLineWidth(4);
  bot_margin->SetLineColor(kBlack);
  bot_margin->SetLineStyle(1);
  bot_margin->Draw("same");

  TLine * lef_margin = new TLine(1025,1500,1025,1925);
  lef_margin->SetLineWidth(4);
  lef_margin->SetLineColor(kBlack);
  lef_margin->SetLineStyle(1);
  lef_margin->Draw("same");

  TLine * rig_margin = new TLine(1725,1500,1725,1925);
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
  prctex = new TLatex(0.205,0.83, "pp #rightarrow #tilde{g} #tilde{g}, #tilde{g}#rightarrow 2j + #chi_{1}^{0}, #chi_{1}^{0} #rightarrow Z#tilde{G}; m_{#tilde{G}} = 1 GeV" );    
  prctex->SetNDC();    
  prctex->SetTextSize(0.035);    
  prctex->SetLineWidth(2);
  prctex->SetTextFont(42);    
  prctex->Draw();

  // TLatex *clstex = NULL;
  // clstex = new TLatex(0.215,0.84, "NLO + NLL exclusion" );    
  // clstex->SetNDC();    
  // clstex->SetTextSize(0.032);    
  // clstex->SetLineWidth(2);
  // clstex->SetTextFont(42);    
  // clstex->Draw();


  TLatex *cmstex = NULL;
  cmstex = new TLatex(0.575,0.94, "12.9 fb^{-1} (13 TeV)" );    
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
  cmstexbold->SetTextFont(52);    
  cmstexbold->Draw();

  c_massplane->SaveAs("T5ZZ_Significance_13TeV.pdf");
  // c_massplane->SaveAs("/home/users/cwelke/public_html/T5ZZ_Exclusion_13TeV.pdf");

  return 0;
}
