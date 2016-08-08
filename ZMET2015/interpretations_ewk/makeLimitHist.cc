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

int makeLimitHist()
{

  
  TH1F * h_susyxsecs  = NULL;
  TFile * f_susyxsecs = NULL;

  f_susyxsecs = TFile::Open("xsec_susy_13tev.root","READ");
  h_susyxsecs = (TH1F*)f_susyxsecs->Get("h_xsec_c1n2")->Clone("h_susyxsecs");

  
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

  TFile * f_rvalues = TFile::Open("r-values_TChiWZ.root","READ");  
  
  TH2F * massplane        = (TH2F*) f_rvalues->Get("hExp")   -> Clone("massplane");
  TH2F * massplane_obs    = (TH2F*) f_rvalues->Get("hObs")   -> Clone("massplane_obs");
  TH2F * massplane_obs_up = (TH2F*) f_rvalues->Get("hObs")   -> Clone("massplane_obs_up");
  TH2F * massplane_obs_dn = (TH2F*) f_rvalues->Get("hObs")   -> Clone("massplane_obs_dn");
  TH2F * massplane_exp_up = (TH2F*) f_rvalues->Get("hExp1p") -> Clone("massplane_exp_up");
  TH2F * massplane_exp_dn = (TH2F*) f_rvalues->Get("hExp1m") -> Clone("massplane_exp_dn");
  // TH2F * massplane_xsec   = new TH2F("massplane_xsec","", 27,25,1375,25,75.0,1325.0);

  TH2F * massplane_xsec   = (TH2F*) massplane_obs-> Clone("massplane_xsec");
  TH2F * efficiency       = (TH2F*) massplane    -> Clone("efficiency"    );

  double contours[1];
  contours[0] = 1.0;

  TH2F * contourplot = dynamic_cast<TH2F*>(massplane->Clone("contourplot"));

  massplane_xsec->GetXaxis()->SetRangeUser(87.5,712.5);

  massplane_xsec->GetXaxis()->SetLabelSize(0.035);
  massplane_xsec->GetYaxis()->SetLabelSize(0.035);
  // massplane_xsec->GetXaxis()->SetTitle("NLSP mass [GeV]");
  massplane_xsec->GetXaxis()->SetTitle("M_{#tilde{#chi}^{#pm}_{1}/#tilde{#chi}^{0}_{2}} [GeV]");
  massplane_xsec->GetYaxis()->SetTitle("M_{#tilde{#chi}^{0}_{1}} [GeV]");
  // massplane_xsec->GetYaxis()->SetTitle("LSP mass [GeV]");
  massplane_xsec->GetZaxis()->SetTitle("95% CL upper limit on #sigma [pb]");
  massplane_xsec->GetZaxis()->SetRangeUser(5e-2,3e3);
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
  massplane_xsec->GetXaxis()->SetRangeUser(112.5,500);
  // massplane_xsec->GetXaxis()->SetRangeUser(87.5,512.5);
  massplane_xsec->GetYaxis()->SetRangeUser(0,300);
  massplane_xsec->GetYaxis()->SetRangeUser(10,300);
  massplane_xsec->Draw("colz");
  
  // multiply by susy xsec
  for( int biny = 1; biny < 32; biny++ ){
	for( int binx = 0; binx < 31; binx++ ){
	  int mgluino = binx*25;
	  int truebin = massplane_xsec->FindBin(binx*25,biny*10);
	  // massplane_xsec->SetBinContent(truebin, massplane_xsec->GetBinContent(truebin)/(0.19175)*h_susyxsecs->GetBinContent(h_susyxsecs->FindBin(mgluino)));
	  massplane_xsec  ->SetBinContent(truebin, massplane_xsec-> GetBinContent(truebin)*h_susyxsecs->GetBinContent(h_susyxsecs->FindBin(mgluino)));
	  massplane_obs_up->SetBinContent(truebin, massplane_obs -> GetBinContent(truebin)*1.15);
	  massplane_obs_dn->SetBinContent(truebin, massplane_obs -> GetBinContent(truebin)*0.85);
	}
  }

  TFile * file = new TFile("CLS_CSUL.root","RECREATE");
  file->cd();
  massplane_xsec->Write();
  file->Write();
  file->Close();
  
  // if( biny*10 > 250) continue;
  for( int binx = 0; binx < 31; binx++ ){
	for( int biny = 1; biny < 32; biny++ ){
	  // if( binx*25 < biny*10 && (biny)*10 < 200) continue;
	  int truebin = massplane_xsec->FindBin(binx*25,biny*10);
	  int truebinminus1 = massplane_xsec->FindBin(binx*25,(biny-1)*10);

	  // if( biny*10 > 130 ){
	  // 	contourplot      -> SetBinContent(truebin,100);
	  // 	massplane_obs    -> SetBinContent(truebin,100);
	  // 	massplane_obs_up -> SetBinContent(truebin,100);
	  // 	massplane_obs_dn -> SetBinContent(truebin,100);
	  // 	massplane_exp_up -> SetBinContent(truebin,100);
	  // 	massplane_exp_dn -> SetBinContent(truebin,100);
	  // }
	  
	  // if( binx*25 < (biny+1)*10 ) continue;
	  // if( biny*10 > 250        ) continue;
	  if( massplane_obs    -> GetBinContent(truebin) <= 0.01 ) massplane_obs    -> SetBinContent(truebin,massplane_obs    -> GetBinContent(truebinminus1));
	  if( massplane_obs_up -> GetBinContent(truebin) <= 0.01 ) massplane_obs_up -> SetBinContent(truebin,massplane_obs_up -> GetBinContent(truebinminus1));
	  if( massplane_obs_dn -> GetBinContent(truebin) <= 0.01 ) massplane_obs_dn -> SetBinContent(truebin,massplane_obs_dn -> GetBinContent(truebinminus1));
	  if( massplane_exp_up -> GetBinContent(truebin) <= 0.01 ) massplane_exp_up -> SetBinContent(truebin,massplane_exp_up -> GetBinContent(truebinminus1));
	  if( massplane_exp_dn -> GetBinContent(truebin) <= 0.01 ) massplane_exp_dn -> SetBinContent(truebin,massplane_exp_dn -> GetBinContent(truebinminus1));
	  if( massplane_xsec   -> GetBinContent(truebin) <= 0.01 ) massplane_xsec   -> SetBinContent(truebin,massplane_xsec   -> GetBinContent(truebinminus1));
	  if( contourplot      -> GetBinContent(truebin) <= 0.01 ) contourplot      -> SetBinContent(truebin,contourplot      -> GetBinContent(truebinminus1));

	  if( massplane_obs    -> GetBinContent(truebin) >=  42 ) massplane_obs    -> SetBinContent(truebin,massplane_obs    -> GetBinContent(truebinminus1));
	  if( massplane_obs_up -> GetBinContent(truebin) >=  42 ) massplane_obs_up -> SetBinContent(truebin,massplane_obs_up -> GetBinContent(truebinminus1));
	  if( massplane_obs_dn -> GetBinContent(truebin) >=  42 ) massplane_obs_dn -> SetBinContent(truebin,massplane_obs_dn -> GetBinContent(truebinminus1));
	  if( massplane_exp_up -> GetBinContent(truebin) >=  42 ) massplane_exp_up -> SetBinContent(truebin,massplane_exp_up -> GetBinContent(truebinminus1));
	  if( massplane_exp_dn -> GetBinContent(truebin) >=  42 ) massplane_exp_dn -> SetBinContent(truebin,massplane_exp_dn -> GetBinContent(truebinminus1));
	  if( massplane_xsec   -> GetBinContent(truebin) >=  42 ) massplane_xsec   -> SetBinContent(truebin,massplane_xsec   -> GetBinContent(truebinminus1));
	  if( contourplot      -> GetBinContent(truebin) >=  42 ) contourplot      -> SetBinContent(truebin,contourplot      -> GetBinContent(truebinminus1));

	  if( binx*25 - biny*10 < 80 ) massplane_obs   -> SetBinContent(truebin,0);
	  if( binx*25 - biny*10 < 80 ) massplane_xsec  -> SetBinContent(truebin,0);

	  // if( binx*25 > 125 ) contourplot      -> SetBinContent(truebin,0);
	  // if( binx*25 > 425 ) contourplot      -> SetBinContent(truebin,0);

	}
  }

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
  
  massplane_xsec->Draw("colz");
  // contourplot->Draw("samecont3");
  // // contourplot->Draw("colz");
  // massplane_obs->Draw("samecont2");
  // massplane_obs_up->Draw("samecont2");
  // massplane_obs_dn->Draw("samecont2");
  // massplane_exp_up->Draw("samecont3");
  // massplane_exp_dn->Draw("samecont3");

//binning needs to correspond to actual binning of TH2F with limits
  vector<double> vmx, vmy, vxsec, vobs, vobsup, vobsdown, vexp, vup, vdown;  
  for( int binx = 3; binx < 29; binx++ ){
  	for( int biny = -1; biny < 31; biny++ ){
	  int truebin = massplane_xsec->FindBin(binx*25,biny*10);
	  vmx.push_back(binx*25); vmy.push_back(biny*10);
	  vxsec    . push_back(h_susyxsecs      -> GetBinContent(h_susyxsecs->FindBin(binx*25)));
	  vobs     . push_back(massplane_obs    -> GetBinContent(truebin));
	  vobsup   . push_back(massplane_obs_up -> GetBinContent(truebin));
	  vobsdown . push_back(massplane_obs_dn -> GetBinContent(truebin));
	  vexp     . push_back(massplane        -> GetBinContent(truebin));
	  vup      . push_back(massplane_exp_up -> GetBinContent(truebin));
	  vdown    . push_back(massplane_exp_dn -> GetBinContent(truebin));

	}
  }

  vector<double> vlim(vxsec.size());
  for(size_t i = 0; i < vxsec.size(); ++i){
    vlim.at(i) = vxsec.at(i) * vobs.at(i);
    // vlim.at(i) = vxsec.at(i) * vobs.at(i)*(7.65)*(0.19175);
  }
  
  TGraph2D glim(    "glim"     , "Cross-Section Limit"     , vlim    .size(), &vmx.at(0), &vmy.at(0), &vlim    .at(0));
  TGraph2D gobs(    "gobs"     , "Observed Limit"          , vobs    .size(), &vmx.at(0), &vmy.at(0), &vobs    .at(0));
  TGraph2D gobsup(  "gobsup"   , "Observed +1#sigma Limit" , vobsup  .size(), &vmx.at(0), &vmy.at(0), &vobsup  .at(0));
  TGraph2D gobsdown("gobsdown" , "Observed -1#sigma Limit" , vobsdown.size(), &vmx.at(0), &vmy.at(0), &vobsdown.at(0));
  TGraph2D gexp(    "gexp"     , "Expected Limit"          , vexp    .size(), &vmx.at(0), &vmy.at(0), &vexp    .at(0));
  TGraph2D gup(     "gup"      , "Expected +1#sigma Limit" , vup     .size(), &vmx.at(0), &vmy.at(0), &vup     .at(0));
  TGraph2D gdown(   "gdown"    , "Expected -1#sigma Limit" , vdown   .size(), &vmx.at(0), &vmy.at(0), &vdown   .at(0));
  TGraph dots(vmx.size(), &vmx.at(0), &vmy.at(0));

  double xmin = *min_element(vmx.cbegin(), vmx.cend());
  double xmax = *max_element(vmx.cbegin(), vmx.cend());
  double ymin = *min_element(vmy.cbegin(), vmy.cend());
  double ymax = *max_element(vmy.cbegin(), vmy.cend());
  double bin_size = 5;
  int nxbins = max(1, min(500, static_cast<int>(ceil((xmax-xmin)/bin_size))));
  int nybins = max(1, min(500, static_cast<int>(ceil((ymax-ymin)/bin_size))));
  glim.SetNpx(nxbins);
  glim.SetNpy(nybins);
  gexp.SetNpx(nxbins);
  gexp.SetNpy(nybins);
  gobs.SetNpx(nxbins);
  gobs.SetNpy(nybins);
  gobsdown.SetNpx(nxbins);
  gobsdown.SetNpy(nybins);
  gobsup.SetNpx(nxbins);
  gobsup.SetNpy(nybins);
  gup.SetNpx(nxbins);
  gup.SetNpy(nybins);
  gdown.SetNpx(nxbins);
  gdown.SetNpy(nybins);
  
  TH2D *hlim = glim.GetHistogram();
  hlim->SetTitle(";m_{gluino} [GeV];m_{LSP} [GeV]");
  // hlim->GetZaxis()->SetRangeUser(1e-3,1);
  hlim->GetZaxis()->SetLabelSize(0);
  hlim->GetZaxis()->SetRangeUser(5e-2,3e3);

  TH2D *hexp = gexp.GetHistogram();
  hexp->SetContour(1, contours);
  hexp->SetLineWidth(4);
  hexp->SetLineStyle(2);
  hexp->SetLineColor(kRed);
  hexp->Smooth();

  TH2D *hobs = gobs.GetHistogram();
  hobs->SetContour(1, contours);
  hobs->SetLineWidth(4);
  hobs->SetLineStyle(1);
  hobs->SetLineColor(kBlack);
  hobs->Smooth();

  TH2D *hobs_up = gobsup.GetHistogram();
  hobs_up->SetContour(1, contours);
  hobs_up->SetLineWidth(2);
  hobs_up->SetLineStyle(1);
  hobs_up->SetLineColor(kBlack);
  hobs_up->Smooth();

  TH2D *hobs_dn = gobsdown.GetHistogram();
  hobs_dn->SetContour(1, contours);
  hobs_dn->SetLineWidth(2);
  hobs_dn->SetLineStyle(1);
  hobs_dn->SetLineColor(kBlack);
  hobs_dn->Smooth();

  TH2D *hexp_up = gup.GetHistogram();
  hexp_up->SetContour(1, contours);
  hexp_up->SetLineWidth(2);
  hexp_up->SetLineStyle(2);
  hexp_up->SetLineColor(kRed);
  hexp_up->Smooth();

  TH2D *hexp_dn = gdown.GetHistogram();
  hexp_dn->SetContour(1, contours);
  hexp_dn->SetLineWidth(2);
  hexp_dn->SetLineStyle(2);
  hexp_dn->SetLineColor(kRed);
  hexp_dn->Smooth();
  
  hlim   ->Draw("samecolz");
  // hobs   ->Draw("samecont3");
  // hobs_dn->Draw("samecont2");
  // hobs_up->Draw("samecont2");
  // hexp   ->Draw("samecont3");
  // hexp_dn->Draw("samecont2");
  // hexp_up->Draw("samecont2");
  contourplot->Draw("samecont3");
  // contourplot->Draw("colz");
  massplane_obs->Draw("samecont2");
  massplane_obs_up->Draw("samecont2");
  massplane_obs_dn->Draw("samecont2");
  massplane_exp_up->Draw("samecont3");
  massplane_exp_dn->Draw("samecont3");

  TLine * diag_0 = new TLine(110,150,310,350);
  diag_0->SetLineWidth(7);
  diag_0->SetLineColor(kWhite);
  diag_0->SetLineStyle(1);
  diag_0->Draw("same");

  for( int i = 1; i < 20; i++ ){
	diag_0 = new TLine(110,150+i*5,310,350+i*5);
	diag_0->SetLineWidth(7);
	diag_0->SetLineColor(kWhite);
	diag_0->SetLineStyle(1);
	diag_0->Draw("same");
  }
  
  // TBox * box_corner = new TBox(112.5,230,512.5,305);
  // box_corner->SetFillColor(kWhite);
  // box_corner->Draw("same");

  padt->RedrawAxis();

  TBox * box = new TBox(112.5,230,512.5,305);
  box->SetFillColor(kWhite);
  box->Draw("same");

  TLegend *l1 = new TLegend(0.205, 0.74, 0.71, 0.82);    
  l1->SetLineColor(kWhite);    
  l1->SetTextFont(42);    
  l1->SetTextSize(0.038);
  l1->SetShadowColor(kWhite);    
  l1->SetFillColor(kWhite);    
  l1->AddEntry(contourplot , "Expected limit, #pm 1 #sigma_{exp.}"            , "l");
  // l1->AddEntry(massplane_obs , "Observed limit"            , "l");
  l1->AddEntry(massplane_obs , "Observed limit, #pm 1 #sigma_{theory}"            , "l");
  l1->Draw("same");

  TLine * top_margin = new TLine(112.5,305,512.5,305);
  top_margin->SetLineWidth(4);
  top_margin->SetLineColor(kBlack);
  top_margin->SetLineStyle(1);
  top_margin->Draw("same");

  TLine * bot_margin = new TLine(112.5,230,512.5,230);
  bot_margin->SetLineWidth(4);
  bot_margin->SetLineColor(kBlack);
  bot_margin->SetLineStyle(1);
  bot_margin->Draw("same");

  TLine * lef_margin = new TLine(112.5,230,112.5,305);
  lef_margin->SetLineWidth(4);
  lef_margin->SetLineColor(kBlack);
  lef_margin->SetLineStyle(1);
  lef_margin->Draw("same");

  TLine * rig_margin = new TLine(512.5,230,512.5,305);
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
  prctex = new TLatex(0.215,0.88, "pp #rightarrow #tilde{#chi}^{#pm}_{1} #tilde{#chi}^{0}_{2}; #tilde{#chi}^{0}_{2}#rightarrow Z + #chi_{1}^{0}, #tilde{#chi}^{#pm}_{1}#rightarrow W^{#pm} + #chi_{1}^{0}" );    
  prctex->SetNDC();    
  prctex->SetTextSize(0.032);    
  prctex->SetLineWidth(2);
  prctex->SetTextFont(42);    
  prctex->Draw();

  TLatex *clstex = NULL;
  clstex = new TLatex(0.215,0.83, "NLO + NLL exclusion" );    
  clstex->SetNDC();    
  clstex->SetTextSize(0.032);    
  clstex->SetLineWidth(2);
  clstex->SetTextFont(42);    
  clstex->Draw();


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
  cmstexbold->SetTextFont(12);    
  cmstexbold->Draw();

  c_massplane->SaveAs("TChiWZ_Exclusion_13TeV.pdf");
  // c_massplane->SaveAs("/home/users/cwelke/public_html/T5ZZ_Exclusion_13TeV.pdf");

  return 0;
}
