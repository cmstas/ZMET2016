#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TGraph2D.h"
#include "TGraph.h"

#include <iostream>
#include <vector>

const int ybinsfirstxbin=30;

float GetValue(float xvalue, TH1F &hist){
  float xmax = hist.GetXaxis()->GetXmax()-0.01;
  int xbin = hist.GetXaxis()->FindBin(min(xvalue, xmax));
  return hist.GetBinContent(xbin);
}

float GetValuePlus(float xvalue, TH1F &hist){
  float xmax = hist.GetXaxis()->GetXmax()-0.01;
  int xbin = hist.GetXaxis()->FindBin(min(xvalue, xmax));
  return hist.GetBinContent(xbin) + hist.GetBinError(xbin);
}

float GetValueMinus(float xvalue, TH1F &hist){
  float xmax = hist.GetXaxis()->GetXmax()-0.01;
  int xbin = hist.GetXaxis()->FindBin(min(xvalue, xmax));
  return hist.GetBinContent(xbin) - hist.GetBinError(xbin);
}

void FillHorizontalBelowZero(TH2 *hist){
  for (int i = 1; i < hist->GetNbinsX()+1; i++) {
    hist->SetBinContent( i,1,hist->GetBinContent(i,2) );
  }
}

void FillEmptyHorizontal(TH2 *hist){
  for (int i = 1; i < hist->GetNbinsX()+1; i++) {
    for (int j = 2; j < hist->GetNbinsY()+1; j++) {
      if (hist->GetBinContent(i,j) < 0.01) {
	hist->SetBinContent( i,j,hist->GetBinContent(i,j-1) );
      }
    }
  }
}

void SmoothDiagonal(TH2* hist){
  for (int ix = 1; ix < hist->GetNbinsX()+1; ix++) {
    for (int iy = hist->GetNbinsY()-2; iy > 0; iy--) {
      //    if (iy>ix+ybinsfirstxbin) hist->SetBinContent(ix,iy,hist->GetBinContent(ix,iy-1));
      if (hist->GetBinContent(ix,iy)==0) {
	for (int iyy = iy; iyy < hist->GetNbinsY()-2; iyy++) {
	  hist->SetBinContent(ix,iyy,hist->GetBinContent(ix,iy-1));
	}
      }
      else break;
    }
  }
}

void CleanDiagonal(TH2* hist, TH2* histUnsmooth, bool isXsec){
  for (int ix = 1; ix < hist->GetNbinsX()+1; ix++) {
    for (int iy = hist->GetNbinsY()-2; iy > 0; iy--) {
      //if (iy>ix+ybinsfirstxbin) hist->SetBinContent(ix,iy,0);
      if (histUnsmooth->GetBinContent(ix,iy)==0) {
  	if (!isXsec) hist->SetBinContent(ix,iy,1.1);
  	else hist->SetBinContent(ix,iy,0);
      }
      else break;
    }
  }
}

TH2D* InterpolateAndSmooth(TH2* hist, string model){

  // //cosmetic fix to extend temperate past axes -- doesn't work for ZMET scans because of the way we fill them
  // FillHorizontalBelowZero(hist);

  //  FillEmptyHorizontal(hist);

  //interpolate by converting hist->graph->hist
  TGraph2D *hist_graph   = new TGraph2D(hist);
  
  const float widthx = 12.5;
  const float widthy = 5;
  hist_graph->SetNpx((hist_graph->GetXmax()-hist_graph->GetXmin())/widthx);
  hist_graph->SetNpy((hist_graph->GetYmax()-hist_graph->GetYmin())/widthy);
  TH2D *hist_smooth   = hist_graph->GetHistogram();
  TH2D * unsmoothedHist = (TH2D*) hist_smooth->Clone();

  //temporarily fill zeroes above diagonal so smoothing doesn't smooth to zero
  SmoothDiagonal(hist_smooth);

  // fill empty horizontal rows in the bulk of the scan
  FillEmptyHorizontal(hist_smooth);

  //perform smoothing
  int nSmooth = 0;  
  if (model.find("T2tt") !=std::string::npos || model.find("TChiWZ") !=std::string::npos) nSmooth = 1;
  else if (model.find("T2qq") !=std::string::npos) nSmooth = 2;
  else nSmooth = 3;
  
  for (int i = 0; i < nSmooth; i++) {
    hist_smooth->Smooth(1,"k3a");
  }

  const string histname = hist->GetName();
  const bool isXsec = histname.find("Xsec") !=std::string::npos;
  //reset zeroes above diagonal
  CleanDiagonal(hist_smooth,unsmoothedHist,isXsec);

  return hist_smooth;
}

void smooth(std::string model){

  //f_susyxsecs = TFile::Open("../../dilepbabymaker/xsec_susy_13tev.root","READ");
  TFile *f_xsec = new TFile("../../dilepbabymaker/xsec_susy_13tev.root", "READ");
  TH1F *h_xsec = (TH1F*)f_xsec->Get("h_xsec_gluino");//FIXME for Gluino models
  if ( model.find("T2-4bd") != string::npos || model.find("T2tt") != string::npos)
    h_xsec = (TH1F*)f_xsec->Get("h_xsec_stop");// for stop/sbottom models
  else if ( model.find("TChiWZ") != string::npos)
    h_xsec = (TH1F*)f_xsec->Get("h_xsec_c1n2");// for stop/sbottom models

  TFile *f = new TFile(Form("r-values_%s.root", model.c_str()), "UPDATE");
  f->cd();

  TH2 *hExp   = (TH2*)f->Get("hExp");
  TH2 *hObs   = (TH2*)f->Get("hObs");
  TH2 *hExp1m = (TH2*)f->Get("hExp1m");
  TH2 *hExp2m = (TH2*)f->Get("hExp2m");
  TH2 *hExp1p = (TH2*)f->Get("hExp1p");
  TH2 *hExp2p = (TH2*)f->Get("hExp2p");

  if(!hExp) std::cout << "hist not found" << std::endl;

  TH2* hXsec_obs = (TH2*)hObs->Clone("hXsec_obs"); 
  TH1D* proj_x = hXsec_obs->ProjectionX();

  for(int i=1; i<=hXsec_obs->GetNbinsX(); i++){
    for(int j=1; j<=hXsec_obs->GetNbinsY(); j++){
      float xsec_limit = hXsec_obs->GetBinContent(i,j);
      if(xsec_limit == 0){
        continue;
      }
      xsec_limit *= GetValue(proj_x->GetBinCenter(i), *h_xsec);
      hXsec_obs->SetBinContent(i,j,xsec_limit);
    }
  } 


  TH2* hObs1m = (TH2*)hObs->Clone("hObs1m"); 
  TH1D* proj_x_1m = hObs1m->ProjectionX();

  for(int i=1; i<=hObs1m->GetNbinsX(); i++){
    for(int j=1; j<=hObs1m->GetNbinsY(); j++){
      float xsec_limit = hObs1m->GetBinContent(i,j);
      if(xsec_limit == 0){
        continue;
      }
      xsec_limit *= (GetValue(proj_x_1m->GetBinCenter(i), *h_xsec)/GetValueMinus(proj_x_1m->GetBinCenter(i), *h_xsec));
      hObs1m->SetBinContent(i,j,xsec_limit);
    }
  } 

  TH2* hObs1p = (TH2*)hObs->Clone("hObs1p"); 
  TH1D* proj_x_1p = hObs1p->ProjectionX();

  for(int i=1; i<=hObs1p->GetNbinsX(); i++){
    for(int j=1; j<=hObs1p->GetNbinsY(); j++){
      float xsec_limit = hObs1p->GetBinContent(i,j);
      if(xsec_limit == 0){
        continue;
      }
      xsec_limit *= (GetValue(proj_x_1p->GetBinCenter(i), *h_xsec)/GetValuePlus(proj_x_1p->GetBinCenter(i), *h_xsec));
      hObs1p->SetBinContent(i,j,xsec_limit);
    }
  } 

  TH2D *hExp_smooth       = InterpolateAndSmooth(hExp,model);
  TH2D *hObs_smooth       = InterpolateAndSmooth(hObs,model);
  TH2D *hObs1m_smooth     = InterpolateAndSmooth(hObs1m,model);
  TH2D *hObs1p_smooth     = InterpolateAndSmooth(hObs1p,model);
  TH2D *hExp1m_smooth     = InterpolateAndSmooth(hExp1m,model);
  TH2D *hExp2m_smooth     = InterpolateAndSmooth(hExp2m,model);
  TH2D *hExp1p_smooth     = InterpolateAndSmooth(hExp1p,model);
  TH2D *hExp2p_smooth     = InterpolateAndSmooth(hExp2p,model);
  TH2D *hXsec_obs_smooth  = InterpolateAndSmooth(hXsec_obs,model);
 
  hExp_smooth             ->Write("hExp_smooth",TObject::kOverwrite);
  hObs_smooth             ->Write("hObs_smooth",TObject::kOverwrite);
  hObs1m_smooth           ->Write("hObs1m_smooth",TObject::kOverwrite);
  hObs1p_smooth           ->Write("hObs1p_smooth",TObject::kOverwrite);
  hExp1m_smooth           ->Write("hExp1m_smooth",TObject::kOverwrite);
  hExp2m_smooth           ->Write("hExp2m_smooth",TObject::kOverwrite);
  hExp1p_smooth           ->Write("hExp1p_smooth",TObject::kOverwrite);
  hExp2p_smooth           ->Write("hExp2p_smooth",TObject::kOverwrite);
  hXsec_obs_smooth        ->Write("obs_xs",TObject::kOverwrite);

  f->Close();
  delete f;

  f_xsec->Close();
  delete f_xsec;

}
