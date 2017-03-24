#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TGraph2D.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TStyle.h"

#include <iostream>
#include <vector>

bool  pairCompare(const std::pair<int, TGraph>& no1, const std::pair<int, TGraph>& no2){
  return no1.first < no2.first;
}

TGraph MergeGraphs(vector<TGraph> vecGraph){
  TMultiGraph mg;
  mg.Add(&vecGraph[0]);
  mg.Add(&vecGraph[1]);
  TGraph g;
  g.Merge(mg.GetListOfGraphs());
  g.SetName(vecGraph[0].GetName());
  return g;
}

vector<TGraph> DrawContours(TH2* hist, int color, int style){

  TGraph2D *h_graph   = new TGraph2D(hist);
  
  TCanvas* c1 = new TCanvas();
  
  h_graph->Draw("CONT0 LIST");
  c1->Update();

  // TObjArray* obj = (TObjArray*) gROOT->GetListOfSpecials()->FindObject("contours");
  // TList* l2 = (TList*) obj->At(1);
  
  vector<TGraph> vecGraph;
  vector<pair<int,TGraph>> vecGraphPairs;
  TGraph out1 = 0;
  TGraph out2 = 0;
  TList *l = h_graph->GetContourList(1.0);
  if(!l){
    std::cout << "no contour" << std::endl;
    vecGraph.push_back(out1);
    vecGraph.push_back(out2);
    return vecGraph;
  }
  
  //bool added = false;
  int max_points = -1;
  for(int i = 0; i < l->GetSize(); ++i){
    TGraph *g = static_cast<TGraph*>(l->At(i));
    if(!g){
      std::cout << "no graph" << std::endl;
      continue;
    }
    int n_points = g->GetN();
    std::cout << "n_points = " << n_points << std::endl;
    vecGraphPairs.push_back(std::make_pair(n_points,*g));
    if(n_points > max_points){
      // out2 = out1;
      // out1 = *g;
      max_points = n_points;
    }
    g->SetLineColor(color);
    g->SetLineStyle(style);
    g->SetLineWidth(4);
    g->Draw("L same");
  }

  std::sort(vecGraphPairs.rbegin(),vecGraphPairs.rend(),pairCompare);
  
  if (vecGraphPairs.size() == 1) vecGraphPairs.push_back(vecGraphPairs[0]);
  
  // if (l->GetSize() < 2) out2 = out1;
  
  vecGraph.push_back(vecGraphPairs[0].second);
  vecGraph.push_back(vecGraphPairs[1].second);

  //DELETE STUFF
  
  return vecGraph;
}

TGraph ExtractContour(TH2* hist, int color, int style, bool splitRL=false){

  vector<TGraph> v_contour;

  hist->SetMinimum(0);
  hist->SetMaximum(2);
  hist->SetContour(4);
  
  if(splitRL) {
    TH2* hL = (TH2*) hist->Clone();
    TH2* hR = (TH2*) hist->Clone();

    for (int ix = 1; ix < hist->GetNbinsX()+1; ix++) {
      for (int iy = 1; iy < hist->GetNbinsY()+1; iy++) {
	float m1 = hist->GetXaxis()->GetBinLowEdge(ix);
	float m2 = hist->GetYaxis()->GetBinLowEdge(iy);
	if (m1-m2 >= 150) hL->SetBinContent(ix,iy, 0);
	if (m1-m2 <= 200) hR->SetBinContent(ix,iy, 0);
      }
    }

    vector<TGraph> v_L = DrawContours(hL, color, style);
    vector<TGraph> v_R = DrawContours(hR, color, style);

    v_contour.push_back(v_L[0]);
    v_contour.push_back(v_R[0]);
  }
  else{
    v_contour = DrawContours(hist, color, style);  
  }
  
  TGraph g = MergeGraphs(v_contour);

  //DELETE STUFF

  //FIXME:for now just return the first graph
  return v_contour[0];
}

void make_contour(std::string model){

  TFile *f = new TFile(Form("r-values_%s.root", model.c_str()), "UPDATE");
  f->cd();

  TH2 *hExp_smooth   = (TH2*)f->Get("hExp_smooth");
  TH2 *hObs_smooth   = (TH2*)f->Get("hObs_smooth");
  TH2 *hObs1m_smooth   = (TH2*)f->Get("hObs1m_smooth");
  TH2 *hObs1p_smooth   = (TH2*)f->Get("hObs1p_smooth");
  TH2 *hExp1m_smooth = (TH2*)f->Get("hExp1m_smooth");
  TH2 *hExp2m_smooth = (TH2*)f->Get("hExp2m_smooth");
  TH2 *hExp1p_smooth = (TH2*)f->Get("hExp1p_smooth");
  TH2 *hExp2p_smooth = (TH2*)f->Get("hExp2p_smooth");

  if(!hExp_smooth) std::cout << "hist not found" << std::endl;

  gStyle->SetNumberContours(100);
  
  bool splitRL = false;
  TGraph cup = ExtractContour(hExp1p_smooth,2,2,splitRL);
  TGraph cdown = ExtractContour(hExp1m_smooth,2,2,splitRL);
  TGraph cexp = ExtractContour(hExp_smooth,2,1,splitRL);
  TGraph cobs = ExtractContour(hObs_smooth,1,1,splitRL);
  TGraph cobsm = ExtractContour(hObs1m_smooth,1,1,splitRL);
  TGraph cobsp = ExtractContour(hObs1p_smooth,1,1,splitRL);

  cup.Write("gr_ep1s_smoothed",TObject::kOverwrite);
  cdown.Write("gr_em1s_smoothed",TObject::kOverwrite);
  cexp.Write("gr_exp_smoothed",TObject::kOverwrite);
  cobs.Write("gr_obs_smoothed",TObject::kOverwrite);
  cobsm.Write("gr_om1s_smoothed",TObject::kOverwrite);
  cobsp.Write("gr_op1s_smoothed",TObject::kOverwrite);

  f->Close();
  delete f;

}
