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
#include "tdrstyle_SUSY.C"

using namespace std;

int GetNumBins(const vector<double> &pts, double width){
  double pmin = *min_element(pts.cbegin(), pts.cend());
  double pmax = *max_element(pts.cbegin(), pts.cend());
  return max(1, min(500, static_cast<int>(ceil((pmax-pmin)/width))));
}

// code from Manuel Franco Sevilla to extract graphs from TH2 histograms
// https://github.com/CMS-SUS-XPAG/PlotsSMS/blob/0314f060280997093d827841b787c396dd64e27c/src/utilities.cpp#L24-L59
TGraph* getGraph(TH2* hobs, bool useLongest) {
  //hobs->Smooth();
  TGraph* graph = NULL;
  vector<double> vx, vy, vz;
  for(int binx=1; binx<=hobs->GetNbinsX(); ++binx){
    double x = hobs->GetXaxis()->GetBinCenter(binx);
    for(int biny=1; biny<=hobs->GetNbinsY(); ++biny){
      double y = hobs->GetYaxis()->GetBinCenter(biny);
      double z = hobs->GetBinContent(hobs->GetBin(binx,biny));
      vx.push_back(x);
      vy.push_back(y);
      vz.push_back(z);
    }
  }
    
  TGraph2D gsmooth("gsmooth", "", vx.size(), &vx.at(0), &vy.at(0), &vz.at(0));
  gsmooth.SetNpx(GetNumBins(vx, 1));
  gsmooth.SetNpy(GetNumBins(vy, 1));
  gsmooth.GetHistogram();
  TList *list = gsmooth.GetContourList(1.);
  TIter liter(list);
  // want longest contour in some cases and shortest in others.. have to set manually for each case when calling this function
  int max_points = 0;
  if (!useLongest) max_points = 991;
  for(int i = 0; i < list->GetSize(); ++i){
    TGraph *g = static_cast<TGraph*>(list->At(i));
    if(g == nullptr) continue;
    int n_points = g->GetN();
    //    cout<<"Contour with "<<n_points<<" points "<<endl;
    if((useLongest && n_points > max_points) || (!useLongest && n_points < max_points)){
      graph = g;
      max_points = n_points;
    }
  }

  // remove points from graph with y > x to clean above diagonal..
  for (int i = graph->GetN(); i > 0; --i) {
    double x,y;
    graph->GetPoint(i,x,y);
    if (y > x) graph->RemovePoint(i);
  }

  return static_cast<TGraph*>(graph);
}

int makeLimitHist_T5ZZ()
{

  setTDRStyle();           
  gROOT->ForceStyle();
  
  TH1F * h_susyxsecs  = NULL;
  TFile * f_susyxsecs = NULL;

  f_susyxsecs = TFile::Open("../../dilepbabymaker/data/xsec_susy_13tev.root","READ");
  h_susyxsecs = (TH1F*)f_susyxsecs->Get("h_xsec_gluino")->Clone("h_susyxsecs");

  
  // More better palette
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  double stops[] = {0.00, 0.34, 0.61, 0.84, 1.00};
  double red[]   = {0.50, 0.50, 1.00, 1.00, 1.00};
  double green[] = {0.50, 1.00, 1.00, 0.60, 0.50};
  double blue[]  = {1.00, 1.00, 0.50, 0.40, 0.50};
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
  
  TString version = "limits_T5ZZ_100317";
  TFile * f_rvalues = TFile::Open(Form("%s/r-values_T5ZZ.root",version.Data()),"READ");  
  
  TH2F * massplane        = (TH2F*) f_rvalues->Get("hExp")   -> Clone("massplane_exp");
  TH2F * massplane_obs    = (TH2F*) f_rvalues->Get("hObs")   -> Clone("massplane_obs");
  TH2F * massplane_obs_up = (TH2F*) f_rvalues->Get("hObs")   -> Clone("massplane_obs_up");
  TH2F * massplane_obs_dn = (TH2F*) f_rvalues->Get("hObs")   -> Clone("massplane_obs_dn");
  TH2F * massplane_exp_up = (TH2F*) f_rvalues->Get("hExp1p") -> Clone("massplane_exp_up");
  TH2F * massplane_exp_dn = (TH2F*) f_rvalues->Get("hExp1m") -> Clone("massplane_exp_dn");
  TH2F * massplane_exp_up2 = (TH2F*) f_rvalues->Get("hExp2p") -> Clone("massplane_exp_up2");
  TH2F * massplane_exp_dn2 = (TH2F*) f_rvalues->Get("hExp2m") -> Clone("massplane_exp_dn2");
  // TH2F * massplane_xsec   = new TH2F("massplane_xsec","", 27,25,1375,25,75.0,1325.0);

  TH2F * massplane_xsec   = (TH2F*) massplane_obs-> Clone("massplane_obs_xsec");
  TH2F * efficiency       = (TH2F*) massplane    -> Clone("efficiency"    );

  TH2F * h_axis = new TH2F("h_axis","",110,1000,2100,220,0,2200);

  double contours[1];
  contours[0] = 1.0;

  TH2F * contourplot = dynamic_cast<TH2F*>(massplane->Clone("contourplot"));

  h_axis->GetXaxis()->SetRangeUser(1100,2000);
  h_axis->GetYaxis()->SetRangeUser(100,2200);

  h_axis->GetXaxis()->SetLabelSize(0.035);
  h_axis->GetXaxis()->SetNdivisions(508);
  h_axis->GetYaxis()->SetLabelSize(0.035);
  h_axis->GetXaxis()->SetTitle("m_{#tilde{g}} [GeV]");
  h_axis->GetYaxis()->SetTitle("m_{#tilde{#chi}_{1}^{0}} [GeV]");
  
  massplane_xsec->GetZaxis()->SetTitle("95% CL upper limit on #sigma [pb]");
  massplane_xsec->GetZaxis()->SetRangeUser(1e-3,1e-1);
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
  h_axis->Draw("axis");
  //  massplane_xsec->Draw("colz same");

  // // scale for lumi
  // const float lumiscaling = 2.;
  // massplane        ->Scale(1./sqrt(lumiscaling));
  // massplane_obs    ->Scale(1./sqrt(lumiscaling));
  // massplane_obs_up ->Scale(1./sqrt(lumiscaling));
  // massplane_obs_dn ->Scale(1./sqrt(lumiscaling));
  // massplane_exp_up ->Scale(1./sqrt(lumiscaling));
  // massplane_exp_dn ->Scale(1./sqrt(lumiscaling));
  // massplane_exp_up2->Scale(1./sqrt(lumiscaling));
  // massplane_exp_dn2->Scale(1./sqrt(lumiscaling));
  // massplane_xsec   ->Scale(1./sqrt(lumiscaling));
  // contourplot       ->Scale(1/sqrt(lumiscaling));  

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

  massplane_exp_up2->SetContour(1, contours);
  massplane_exp_up2->SetLineWidth(2);
  massplane_exp_up2->SetLineStyle(3);
  massplane_exp_up2->SetLineColor(kRed);
  massplane_exp_up2->Smooth();
  massplane_exp_dn2->SetContour(1, contours);
  massplane_exp_dn2->SetLineWidth(2);
  massplane_exp_dn2->SetLineStyle(3);
  massplane_exp_dn2->SetLineColor(kRed);
  massplane_exp_dn2->Smooth();
  
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

  // multiply by susy xsec
  for( int binx = 1; binx <= massplane_xsec->GetNbinsX(); binx++ ){
  	for( int biny = 1; biny <= massplane_xsec->GetNbinsY(); biny++ ){
	  int mgluino = massplane_xsec->GetXaxis()->GetBinCenter(binx);
	  int truebin = massplane_xsec->GetBin(binx,biny);
	  // massplane_xsec->SetBinContent(truebin, massplane_xsec->GetBinContent(truebin)/(0.19175)*h_susyxsecs->GetBinContent(h_susyxsecs->FindBin(mgluino)));
	  double xsec = h_susyxsecs->GetBinContent(h_susyxsecs->FindBin(mgluino));
	  double xsec_relerr = h_susyxsecs->GetBinError(h_susyxsecs->FindBin(mgluino))/xsec;
	  massplane_xsec->SetBinContent(truebin, massplane_xsec->GetBinContent(truebin)*xsec);
	  massplane_obs_up->SetBinContent(truebin, massplane_obs->GetBinContent(truebin)*(1. + xsec_relerr));
	  massplane_obs_dn->SetBinContent(truebin, massplane_obs->GetBinContent(truebin)*(1. - xsec_relerr));
	}
  }
  
  //set diag to 1 for contours
  for( int binx = 0; binx < contourplot->GetNbinsX()+1; binx++ ){
	for( int biny = 0; biny < contourplot->GetNbinsY()+1; biny++ ){
	  int mgluino = massplane_xsec->GetXaxis()->GetBinCenter(binx);
	  int mchi = massplane_xsec->GetYaxis()->GetBinCenter(biny);
	  int truebin = massplane_xsec->GetBin(binx,biny);
	  int truebinminus1 = massplane_xsec->GetBin(binx,biny-1);
	  
	  // hack: this fills a couple bins above the diagonal with large values so limit contours won't run off to high values
	  if ( mchi > mgluino && mchi < mgluino + 100) {
	    float penalty_factor = 2.;
	    massplane_obs    -> SetBinContent(truebin,massplane_obs    -> GetBinContent(truebinminus1)*penalty_factor);
	    massplane_obs_up -> SetBinContent(truebin,massplane_obs_up -> GetBinContent(truebinminus1)*penalty_factor);
	    massplane_obs_dn -> SetBinContent(truebin,massplane_obs_dn -> GetBinContent(truebinminus1)*penalty_factor);
	    massplane_exp_up -> SetBinContent(truebin,massplane_exp_up -> GetBinContent(truebinminus1)*penalty_factor);
	    massplane_exp_dn -> SetBinContent(truebin,massplane_exp_dn -> GetBinContent(truebinminus1)*penalty_factor);
	    massplane_exp_up2 -> SetBinContent(truebin,massplane_exp_up2 -> GetBinContent(truebinminus1)*penalty_factor);
	    massplane_exp_dn2 -> SetBinContent(truebin,massplane_exp_dn2 -> GetBinContent(truebinminus1)*penalty_factor);
	    massplane_xsec   -> SetBinContent(truebin,massplane_xsec   -> GetBinContent(truebinminus1)*penalty_factor);
	    contourplot      -> SetBinContent(truebin,contourplot      -> GetBinContent(truebinminus1)*penalty_factor);
	  }
	} // biny
  } // binx

  massplane_xsec->Draw("samecolz");

  // -----------------------------------------------------------
  // for drawing smoothed "rainbow carpet" observed xsec limits
  
  //binning needs to correspond to actual binning of TH2F with limits
  vector<double> vmx, vmy, vxsec, vobs, vobsup, vobsdown, vexp, vup, vdown;  
  for( int binx = 18; binx < 44; binx++ ){
  	for( int biny = 2; biny < binx+2; biny++ ){
	  int truebin = massplane_xsec->FindBin(binx*50,biny*50);
	  vmx.push_back(binx*50); vmy.push_back(biny*50);
	  vxsec    . push_back(h_susyxsecs      -> GetBinContent(h_susyxsecs->FindBin(binx*50)));
	  vobs     . push_back(massplane_obs    -> GetBinContent(truebin));
	  vobsup   . push_back(massplane_obs_up -> GetBinContent(truebin));
	  vobsdown . push_back(massplane_obs_dn -> GetBinContent(truebin));
	  vexp     . push_back(massplane        -> GetBinContent(truebin));
	  vup      . push_back(massplane_exp_up -> GetBinContent(truebin));
	  vdown    . push_back(massplane_exp_dn -> GetBinContent(truebin));

	}
  }

  vector<double> vlim(vxsec.size());
  for(int i = 0; i < vxsec.size(); ++i){
    vlim.at(i) = vxsec.at(i) * vobs.at(i);
    // vlim.at(i) = vxsec.at(i) * vobs.at(i)*(7.65)*(0.19175);
  }
  
  TGraph2D glim("glim", "Cross-Section Limit"            , vlim    .size(), &vmx.at(0), &vmy.at(0), &vlim    .at(0));
  TGraph dots(vmx.size(), &vmx.at(0), &vmy.at(0));

  double xmin = *min_element(vmx.cbegin(), vmx.cend());
  double xmax = *max_element(vmx.cbegin(), vmx.cend());
  double ymin = *min_element(vmy.cbegin(), vmy.cend());
  double ymax = *max_element(vmy.cbegin(), vmy.cend());
  double bin_size = 12.5;
  int nxbins = max(1, min(500, static_cast<int>(ceil((xmax-xmin)/bin_size))));
  int nybins = max(1, min(500, static_cast<int>(ceil((ymax-ymin)/bin_size))));
  glim.SetNpx(nxbins);
  glim.SetNpy(nybins);
  
  TH2D *hlim = glim.GetHistogram();
  hlim->SetName("hObsXsec");
  hlim->GetXaxis()->SetTitle("m_{#tilde{g}} [GeV]");
  hlim->GetYaxis()->SetTitle("m_{#tilde{#chi}_{1}^{0}} [GeV]");
  hlim->GetZaxis()->SetRangeUser(1e-3,1e-1);
  hlim->GetZaxis()->SetLabelSize(0);
  // manually fix below zero and above diagonal
  for (int binx=1; binx <= hlim->GetNbinsX(); ++binx) {
    for (int biny=1; biny <= hlim->GetNbinsY(); ++biny) {
      int truebin = hlim->GetBin(binx,biny);
      float mgluino = hlim->GetXaxis()->GetBinCenter(binx);
      float mlsp = hlim->GetYaxis()->GetBinCenter(biny);
      if (mlsp < 0. || mgluino < 1100. || mgluino > 2000. || mlsp > mgluino) hlim->SetBinContent(truebin,0.);
    }
  }

  // end rainbow carpet code
  // -----------------------------------------------------------

  // smoothed version of temperature map
  hlim   ->Draw("samecolz");

  // contours: drawing these from histograms
  contourplot->Draw("samecont3");
  massplane_obs->Draw("samecont3");
  massplane_obs_up->Draw("samecont3");
  massplane_obs_dn->Draw("samecont3");
  massplane_exp_up->Draw("samecont3");
  massplane_exp_dn->Draw("samecont3");
  massplane_exp_up2->Draw("samecont3");
  massplane_exp_dn2->Draw("samecont3");

  // extract contours as graphs and save to file for aux material
  TFile* fg = new TFile("limits_T5ZZ.root","RECREATE");
  fg->cd();
  TGraph* g_exp = getGraph(contourplot,1);
  g_exp->SetName("gExp");
  g_exp->Write();
  TGraph* g_obs = getGraph(massplane_obs,1);
  g_obs->SetName("gObs");
  g_obs->Write();
  TGraph* g_obs_up = getGraph(massplane_obs_up,1);
  g_obs_up->SetName("gObsUp");
  g_obs_up->Write();
  TGraph* g_obs_dn = getGraph(massplane_obs_dn,1);
  g_obs_dn->SetName("gObsDn");
  g_obs_dn->Write();
  TGraph* g_exp_up = getGraph(massplane_exp_up,1);
  g_exp_up->SetName("gExpUp");
  g_exp_up->Write();
  TGraph* g_exp_dn = getGraph(massplane_exp_dn,0);
  g_exp_dn->SetName("gExpDn");
  g_exp_dn->Write();
  TGraph* g_exp_up2 = getGraph(massplane_exp_up2,1);
  g_exp_up2->SetName("gExpUp2");
  g_exp_up2->Write();
  TGraph* g_exp_dn2 = getGraph(massplane_exp_dn2,1);
  g_exp_dn2->SetName("gExpDn2");
  g_exp_dn2->Write();
  hlim->Write();
  fg->Close();
  delete fg;
  
  // use white lines to cover up unpleasant artifacts..
  TLine * diag_0 = new TLine(1100,1100,2000,2000);
  diag_0->SetLineWidth(7);
  diag_0->SetLineColor(kWhite);
  diag_0->SetLineStyle(1);
  diag_0->Draw("same");

  for( int i = 1; i < 6; i++ ){
	diag_0 = new TLine(1100,1100+i*20,2000,2000+i*20);
	diag_0->SetLineWidth(7);
	diag_0->SetLineColor(kWhite);
	diag_0->SetLineStyle(1);
	diag_0->Draw("same");
  }
  
  padt->RedrawAxis();

  TBox * box = new TBox(1100,1750,2000,2200);
  box->SetFillColor(kWhite);
  box->Draw("same");

  TLegend *l1 = new TLegend(0.205, 0.77, 0.71, 0.83);    
  l1->SetLineColor(kWhite);    
  l1->SetTextFont(42);    
  l1->SetTextSize(0.038);
  l1->SetShadowColor(kWhite);    
  l1->SetFillColor(kWhite);    
  l1->AddEntry(contourplot , "Expected limit, #pm 1,2 #sigma_{exp.}"            , "l");
  // l1->AddEntry(massplane_obs , "Observed limit"            , "l");
  l1->AddEntry(massplane_obs , "Observed limit, #pm 1 #sigma_{theory}"            , "l");
  l1->Draw("same");

  TLine * top_margin = new TLine(1100,2200,2000,2200);
  top_margin->SetLineWidth(4);
  top_margin->SetLineColor(kBlack);
  top_margin->SetLineStyle(1);
  top_margin->Draw("same");

  TLine * bot_margin = new TLine(1100,1750,2000,1750);
  bot_margin->SetLineWidth(4);
  bot_margin->SetLineColor(kBlack);
  bot_margin->SetLineStyle(1);
  bot_margin->Draw("same");

  TLine * lef_margin = new TLine(1100,1750,1100,2200);
  lef_margin->SetLineWidth(4);
  lef_margin->SetLineColor(kBlack);
  lef_margin->SetLineStyle(1);
  lef_margin->Draw("same");

  TLine * rig_margin = new TLine(2000,1750,2000,2200);
  rig_margin->SetLineWidth(4);
  rig_margin->SetLineColor(kBlack);
  rig_margin->SetLineStyle(1);
  rig_margin->Draw("same");

  TLatex *prctex = NULL;
  prctex = new TLatex(0.215,0.88, "pp #rightarrow #tilde{g} #tilde{g}, #tilde{g}#rightarrow 2j + #tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow Z#tilde{G}; m_{#tilde{G}} = 1 GeV" );    
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
//  cmstex = new TLatex(0.575,0.94, "35.9 fb^{-1} (13 TeV)" );    
  cmstex = new TLatex(0.575,0.94,"137.2 fb^{-1} (13 TeV)");
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

  //c_massplane->SaveAs("T5ZZ_Exclusion_13TeV.pdf");
  c_massplane->SaveAs("/home/users/olivito/public_html/T5ZZ_Exclusion_13TeV.pdf");
  //c_massplane->SaveAs("/home/users/olivito/public_html/T5ZZ_Exclusion_13TeV_x3lumi.pdf");

  return 0;
}
