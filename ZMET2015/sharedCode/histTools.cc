#include <iostream>

#include "TH1.h"
#include "TFile.h"
#include "TList.h"
#include "TIterator.h"
#include "TRegexp.h"
#include "TObject.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TMath.h"

using namespace std;


float err_mult(float A, float B, float errA, float errB, float C) {
  return sqrt(C*C*(pow(errA/A,2) + pow(errB/B,2)));
}

double getBinomialError( const double num, const double deno ){
  double   p       =   num / deno;
  double   error   =   sqrt(p*(1-p)/deno);
  return error;  
}

 //____________________________________________________________________________
// returns the error on C = A/(A+B) 
//  note that if A and B are integers, simplifies to sqrt((C * (1-C)) / (A+B))
//  or thinking of an efficiency, sqrt((eff * (1-eff)) / N)
float err_binomial(float A, float B, float errA, float errB) {
 return (1/pow(A+B,2)) * sqrt(pow(B*errA,2) + pow(A*errB,2));
}

void fillUnderOverFlow(TH1F * &h1, float value, float weight){
  float min = h1->GetXaxis()->GetXmin();
  float max = h1->GetXaxis()->GetXmax();
  if (value > max) value = h1->GetBinCenter(h1->GetNbinsX());
  if (value < min) value = h1->GetBinCenter(1);
  h1->Fill(value, weight);
}

void fillUnderOverFlow(TH1D * &h1, double value, float weight){
  double min = h1->GetXaxis()->GetXmin();
  double max = h1->GetXaxis()->GetXmax();
  if (value > max) value = h1->GetBinCenter(h1->GetNbinsX());
  if (value < min) value = h1->GetBinCenter(1);
  h1->Fill(value, weight);
}

void saveHist(const string filename, const string pat)
{
  TList* list = gDirectory->GetList() ;
  TIterator* iter = list->MakeIterator();
  TRegexp re(pat.c_str(),kTRUE) ;
  TObject *obj;
  TFile outf(filename.c_str(),"RECREATE") ;
  while((obj=iter->Next())) {
	if (TString(obj->GetName()).Index(re)>=0) {
	  obj->Write() ;
	  cout << "." ;
	  cout.flush() ;
	}
  }
  cout << endl ;
  outf.Close() ;
  delete iter ;
}

void drawCMSLatex( TCanvas * &canvas, float luminosity )
{

  canvas->cd();
  TLatex *lumitex = NULL;
  // lumitex = new TLatex(0.66,0.955, Form("%.1f fb^{-1} (13 TeV)", luminosity) );    
  lumitex = new TLatex(0.66,0.955, Form("%.1f pb^{-1} (13 TeV)", luminosity*1000) );    
  // lumitex = new TLatex(0.66,0.955, Form("few pb^{-1} (13 TeV)") );    
  lumitex->SetNDC();    
  lumitex->SetTextSize(0.04);    
  lumitex->SetLineWidth(2);
  lumitex->SetTextFont(42);    
  lumitex->Draw();

  TLatex *cmstex = NULL;
  cmstex = new TLatex(0.21,0.90, "CMS" );    
  cmstex->SetNDC();    
  cmstex->SetTextSize(0.04);    
  cmstex->SetLineWidth(2);
  cmstex->SetTextFont(62);    
  cmstex->Draw();

  cmstex = new TLatex(0.30,0.90, "Preliminary" );    
  cmstex->SetNDC();    
  cmstex->SetTextSize(0.03);    
  cmstex->SetLineWidth(2);
  cmstex->SetTextFont(12);    
  cmstex->Draw();

  return;
}

void drawCMSLatex( TCanvas * &canvas, float luminosity, float cmsleftmargin, float lumileftmargin )
{

  canvas->cd();
  TLatex *lumitex = NULL;
  // lumitex = new TLatex(lumileftmargin, 0.955, Form("%.1f fb^{-1} (13 TeV)", luminosity) );    
  lumitex = new TLatex(lumileftmargin, 0.955, Form("%.1f fb^{-1} (13 TeV)", luminosity) );    
  lumitex->SetNDC();    
  lumitex->SetTextSize(0.04);    
  lumitex->SetLineWidth(2);
  lumitex->SetTextFont(42);    
  lumitex->Draw();

  TLatex *cmstex = NULL;
  cmstex = new TLatex(cmsleftmargin, 0.95, "CMS Simulation" );    
  cmstex->SetNDC();    
  cmstex->SetTextSize(0.04);    
  cmstex->SetLineWidth(2);
  cmstex->SetTextFont(62);    
  cmstex->Draw();

  return;
}

void drawSRLatex( TCanvas * &canvas, string signalregion, float cmsleftmargin, float lumileftmargin )
{

  float top = 0.85;

  canvas->cd();
  TLatex *srtex = NULL;
  srtex = new TLatex(lumileftmargin+ 0.05, top - 0.2, "\\Sigma p_{T}(\\ell_{1,2})+ H_{T} > 400 GeV" );    
  srtex->SetNDC();    
  srtex->SetTextSize(0.035);    
  srtex->SetLineWidth(2);
  // srtex->SetTextFont(42);    

  if( TString(signalregion).Contains("2jets_inclusive") ){
	srtex = new TLatex(lumileftmargin, top       , "N_{jets} #geq 2" );    
	srtex->SetTextSize(0.035);    
	srtex->SetTextFont(42);    
	srtex->Draw();
  }


  if( TString(signalregion).Contains("SRA_withb") ){
	srtex = new TLatex(lumileftmargin, top       , "H_{T} > 400 GeV" );    
	srtex->SetTextSize(0.035);    
	srtex->SetTextFont(42);    
	srtex->Draw();
	srtex = new TLatex(lumileftmargin, top - 0.05, "N_{jets}: 2-3" );    
	srtex->SetTextSize(0.035);    
	srtex->SetTextFont(42);    
	srtex->Draw();
	srtex = new TLatex(lumileftmargin, top - 0.10, "N_{b-tags} #geq 1" );    
	srtex->SetTextSize(0.035);    
	srtex->SetTextFont(42);    
	srtex->Draw();
  }

  if( TString(signalregion).Contains("SRA_bveto") ){
	srtex = new TLatex(lumileftmargin, top       , "H_{T} > 400 GeV" );    
	srtex->SetTextSize(0.035);    
	srtex->SetTextFont(42);    
	srtex->Draw();
	srtex = new TLatex(lumileftmargin, top - 0.05, "N_{jets}: 2-3" );    
	srtex->SetTextSize(0.035);    
	srtex->SetTextFont(42);    
	srtex->Draw();
	srtex = new TLatex(lumileftmargin, top - 0.10, "N_{b-tags} = 0" );    
	srtex->SetTextSize(0.035);    
	srtex->SetTextFont(42);    
	srtex->Draw();
  }

  if( TString(signalregion).Contains("SRB_withb") ){
	srtex = new TLatex(lumileftmargin, top, "N_{jets} #geq 4" );    
	srtex->SetTextSize(0.035);    
	srtex->SetTextFont(42);    
	srtex->Draw();
	srtex = new TLatex(lumileftmargin, top - 0.05, "N_{b-tags} #geq 1" );    
	srtex->SetTextSize(0.035);    
	srtex->SetTextFont(42);    
	srtex->Draw();
  }

  if( TString(signalregion).Contains("SRB_bveto") ){
	srtex = new TLatex(lumileftmargin, top, "N_{jets} #geq 4" );    
	srtex->SetTextSize(0.035);    
	srtex->SetTextFont(42);    
	srtex->Draw();
	srtex = new TLatex(lumileftmargin, top - 0.05, "N_{b-tags} = 0" );    
	srtex->SetTextSize(0.035);    
	srtex->SetTextFont(42);    
	srtex->Draw();
  }

  if( TString(signalregion).Contains("SR_ATLAS") ){
	// srtex = new TLatex(lumileftmargin-0.15, top + 0.05, "p_{T}(\\ell_{1})+p_{T}(\\ell_{2})" );    
	srtex = new TLatex(lumileftmargin+ 0.15, top - 0.18, "#Sigma p_{T}(lep_{1,2})+ H_{T} > 600 GeV" );    
	srtex->SetTextSize(0.035);    
	srtex->SetTextFont(42);    
	srtex->Draw();
	srtex = new TLatex(lumileftmargin+ 0.20, top - 0.23, "#Delta#phi(E_{T}^{miss}, (jet_{1,2})) > 0.4" );    
	srtex->SetTextSize(0.035);    
	srtex->SetTextFont(42);    
	srtex->Draw();
	srtex = new TLatex(lumileftmargin+ 0.35, top - 0.28, "N_{jets} #geq 2" );    
	srtex->SetTextSize(0.035);    
	srtex->SetLineWidth(2);
	srtex->SetTextFont(42);    
	srtex->Draw();
  }

  return;
}

void getBackground( TH1F* &backgroundhist, std::string iter, std::string bgfileprefix, std::string variable, std::string leptype, std::string selection )
{
  std::string filename = Form("../output/%s/%s_hists.root", iter.c_str(), bgfileprefix.c_str() );
  TFile *infile = NULL;

  try{
	infile = TFile::Open(filename.c_str(),"READ");
  }catch(exception &e ){
	cout<<Form("Cannot find file: %s", filename.c_str() )<<endl;
  }

  try{
	backgroundhist = dynamic_cast<TH1F*>(infile->Get(Form("h_%s_event_%s_%s", leptype.c_str(), variable.c_str(), selection.c_str() ))->Clone("backgroundhist"));
  }catch(exception &e ){
	cout<<"Cannot find hist: "<<Form("h_%s_event_%s_%s", leptype.c_str(), variable.c_str(), selection.c_str() )<<endl;
  }
  return;
}

void getTemplateMET( TH1F* &methist, std::string iter, std::string bgfileprefix )
{
  std::string filename = Form("../output/%s/%s_hists.root", iter.c_str(), bgfileprefix.c_str() );
  cout<<"Getting template MET from "<<filename<<endl;
  TFile *infile = TFile::Open(filename.c_str(),"READ");
  methist = dynamic_cast<TH1F*>(infile->Get("h_templ_met")->Clone(Form("methist_%s", bgfileprefix.c_str())));  
  return;
}

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
	if( hist->GetBinWidth(bini) > hist->GetBinWidth(1) ){
	  hist->SetBinContent( bini, hist->GetBinContent( bini )*(hist->GetBinWidth(1)/hist->GetBinWidth(bini)) );	
	  hist->SetBinError( bini, hist->GetBinError( bini )    *(hist->GetBinWidth(1)/hist->GetBinWidth(bini)) );	
	  // hist->SetBinContent( bini, hist->GetBinContent( bini ) * (10./hist->GetBinWidth(bini)) );	
	  // hist->SetBinError(   bini, hist->GetBinError( bini )   * (10./hist->GetBinWidth(bini)) );	
	}
  }  
  return;
}

// //_______________________________________________________________________________
// int round_double(double d)
// {
//   return floor(d + 0.5);
// }
