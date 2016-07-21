#include <stdexcept>
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>

#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"

#include "Math/VectorUtil.h"

#include "../sharedCode/histTools.h"
#include "../sharedCode/ZMET.h"
#include "../sharedCode/METTemplateSelections.h"
#include "../sharedCode/AnalysisSelections.h"


void makeDataCard(  int mglu = 1100, int mlsp = 750 )
{


  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");

  TFile * f_eventcounts_bveto_SRA = TFile::Open("../output/V08-11-00/fullscan_SRA_bveto_hists.root","READ");
  TFile * f_eventcounts_withb_SRA = TFile::Open("../output/V08-11-00/fullscan_SRA_withb_hists.root","READ");
  TFile * f_eventcounts_bveto_SRB = TFile::Open("../output/V08-11-00/fullscan_SRB_bveto_hists.root","READ");
  TFile * f_eventcounts_withb_SRB = TFile::Open("../output/V08-11-00/fullscan_SRB_withb_hists.root","READ");
  
  TH2F * h_eventcounts_bveto_SRA_met100to150 = NULL; TH2F * h_eventcounts_bveto_SRB_met100to150 = NULL;
  TH2F * h_eventcounts_bveto_SRA_met150to225 = NULL; TH2F * h_eventcounts_bveto_SRB_met150to225 = NULL;
  TH2F * h_eventcounts_bveto_SRA_met225to300 = NULL; TH2F * h_eventcounts_bveto_SRB_met225to300 = NULL;
  TH2F * h_eventcounts_bveto_SRA_met300toinf = NULL; TH2F * h_eventcounts_bveto_SRB_met300toinf = NULL;
  TH2F * h_eventcounts_withb_SRA_met100to150 = NULL; TH2F * h_eventcounts_withb_SRB_met100to150 = NULL;
  TH2F * h_eventcounts_withb_SRA_met150to225 = NULL; TH2F * h_eventcounts_withb_SRB_met150to225 = NULL;
  TH2F * h_eventcounts_withb_SRA_met225to300 = NULL; TH2F * h_eventcounts_withb_SRB_met225to300 = NULL;
  TH2F * h_eventcounts_withb_SRA_met300toinf = NULL; TH2F * h_eventcounts_withb_SRB_met300toinf = NULL;

  h_eventcounts_bveto_SRA_met100to150 = (TH2F*)f_eventcounts_bveto_SRA->Get("h_signalyields_met100to150_ll")->Clone("h_eventcounts_bveto_SRA_met100to150");
  h_eventcounts_bveto_SRA_met150to225 = (TH2F*)f_eventcounts_bveto_SRA->Get("h_signalyields_met150to225_ll")->Clone("h_eventcounts_bveto_SRA_met150to225");
  h_eventcounts_bveto_SRA_met225to300 = (TH2F*)f_eventcounts_bveto_SRA->Get("h_signalyields_met225to300_ll")->Clone("h_eventcounts_bveto_SRA_met225to300");
  h_eventcounts_bveto_SRA_met300toinf = (TH2F*)f_eventcounts_bveto_SRA->Get("h_signalyields_met300toinf_ll")->Clone("h_eventcounts_bveto_SRA_met300toinf");
  h_eventcounts_withb_SRA_met100to150 = (TH2F*)f_eventcounts_withb_SRA->Get("h_signalyields_met100to150_ll")->Clone("h_eventcounts_withb_SRA_met100to150");
  h_eventcounts_withb_SRA_met150to225 = (TH2F*)f_eventcounts_withb_SRA->Get("h_signalyields_met150to225_ll")->Clone("h_eventcounts_withb_SRA_met150to225");
  h_eventcounts_withb_SRA_met225to300 = (TH2F*)f_eventcounts_withb_SRA->Get("h_signalyields_met225to300_ll")->Clone("h_eventcounts_withb_SRA_met225to300");
  h_eventcounts_withb_SRA_met300toinf = (TH2F*)f_eventcounts_withb_SRA->Get("h_signalyields_met300toinf_ll")->Clone("h_eventcounts_withb_SRA_met300toinf");
  h_eventcounts_bveto_SRB_met100to150 = (TH2F*)f_eventcounts_bveto_SRB->Get("h_signalyields_met100to150_ll")->Clone("h_eventcounts_bveto_SRB_met100to150");
  h_eventcounts_bveto_SRB_met150to225 = (TH2F*)f_eventcounts_bveto_SRB->Get("h_signalyields_met150to225_ll")->Clone("h_eventcounts_bveto_SRB_met150to225");
  h_eventcounts_bveto_SRB_met225to300 = (TH2F*)f_eventcounts_bveto_SRB->Get("h_signalyields_met225to300_ll")->Clone("h_eventcounts_bveto_SRB_met225to300");
  h_eventcounts_bveto_SRB_met300toinf = (TH2F*)f_eventcounts_bveto_SRB->Get("h_signalyields_met300toinf_ll")->Clone("h_eventcounts_bveto_SRB_met300toinf");
  h_eventcounts_withb_SRB_met100to150 = (TH2F*)f_eventcounts_withb_SRB->Get("h_signalyields_met100to150_ll")->Clone("h_eventcounts_withb_SRB_met100to150");
  h_eventcounts_withb_SRB_met150to225 = (TH2F*)f_eventcounts_withb_SRB->Get("h_signalyields_met150to225_ll")->Clone("h_eventcounts_withb_SRB_met150to225");
  h_eventcounts_withb_SRB_met225to300 = (TH2F*)f_eventcounts_withb_SRB->Get("h_signalyields_met225to300_ll")->Clone("h_eventcounts_withb_SRB_met225to300");
  h_eventcounts_withb_SRB_met300toinf = (TH2F*)f_eventcounts_withb_SRB->Get("h_signalyields_met300toinf_ll")->Clone("h_eventcounts_withb_SRB_met300toinf");

  h_eventcounts_bveto_SRA_met100to150->SetDirectory(rootdir);
  h_eventcounts_bveto_SRA_met150to225->SetDirectory(rootdir);
  h_eventcounts_bveto_SRA_met225to300->SetDirectory(rootdir);
  h_eventcounts_bveto_SRA_met300toinf->SetDirectory(rootdir);
  h_eventcounts_withb_SRA_met100to150->SetDirectory(rootdir);
  h_eventcounts_withb_SRA_met150to225->SetDirectory(rootdir);
  h_eventcounts_withb_SRA_met225to300->SetDirectory(rootdir);
  h_eventcounts_withb_SRA_met300toinf->SetDirectory(rootdir);
  h_eventcounts_bveto_SRB_met100to150->SetDirectory(rootdir);
  h_eventcounts_bveto_SRB_met150to225->SetDirectory(rootdir);
  h_eventcounts_bveto_SRB_met225to300->SetDirectory(rootdir);
  h_eventcounts_bveto_SRB_met300toinf->SetDirectory(rootdir);
  h_eventcounts_withb_SRB_met100to150->SetDirectory(rootdir);
  h_eventcounts_withb_SRB_met150to225->SetDirectory(rootdir);
  h_eventcounts_withb_SRB_met225to300->SetDirectory(rootdir);
  h_eventcounts_withb_SRB_met300toinf->SetDirectory(rootdir);

  f_eventcounts_bveto_SRA ->Close();
  f_eventcounts_withb_SRA ->Close();
  f_eventcounts_bveto_SRB ->Close();
  f_eventcounts_withb_SRB ->Close();

  string cardname = Form("datacards/datacard_mGluino_%d_mLSP_%d_.txt",mglu,mlsp);

  cout<<"Writing card for: "<<cardname<<endl;
  
  ofstream fout;
  fout.open(cardname);

  // int n_syst = 9;

  vector <string> channel;  
  channel.push_back("bveto_SRB_met100to150");  
  channel.push_back("bveto_SRB_met150to225");  
  channel.push_back("bveto_SRB_met225to300");  
  channel.push_back("bveto_SRB_met300toinf");  
  channel.push_back("withb_SRB_met100to150");
  channel.push_back("withb_SRB_met150to225");
  channel.push_back("withb_SRB_met225to300");
  channel.push_back("withb_SRB_met300toinf");

  // channel.push_back("bveto_SRA_met100to150");     
  // channel.push_back("bveto_SRA_met150to225");  
  // channel.push_back("bveto_SRA_met225to300");  
  // channel.push_back("bveto_SRA_met300toinf");  
  // channel.push_back("withb_SRA_met100to150");
  // channel.push_back("withb_SRA_met150to225");
  // channel.push_back("withb_SRA_met225to300");
  // channel.push_back("withb_SRA_met300toinf");
  
  vector <double> val_data;  
  val_data.push_back( 85);  
  val_data.push_back( 26);  
  val_data.push_back(  9);  
  val_data.push_back(  2);  
  val_data.push_back(138);//43
  val_data.push_back( 64);//22
  val_data.push_back( 15);//3
  val_data.push_back(  2);
  val_data.push_back( 28);  
  val_data.push_back(  6);  
  val_data.push_back(  5);  
  val_data.push_back(  6);  
  val_data.push_back( 21);
  val_data.push_back(  6);
  val_data.push_back(  1);
  val_data.push_back(  3);
  
  int signalbin = h_eventcounts_bveto_SRA_met100to150->FindBin(mglu,mlsp);
  
  vector <double> val_signal;  
  vector <double> err_signal;  
  val_signal.push_back(h_eventcounts_bveto_SRB_met100to150->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_bveto_SRB_met100to150->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_bveto_SRB_met150to225->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_bveto_SRB_met150to225->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_bveto_SRB_met225to300->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_bveto_SRB_met225to300->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_bveto_SRB_met300toinf->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_bveto_SRB_met300toinf->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_withb_SRB_met100to150->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_withb_SRB_met100to150->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_withb_SRB_met150to225->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_withb_SRB_met150to225->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_withb_SRB_met225to300->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_withb_SRB_met225to300->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_withb_SRB_met300toinf->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_withb_SRB_met300toinf->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_bveto_SRA_met100to150->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_bveto_SRA_met100to150->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_bveto_SRA_met150to225->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_bveto_SRA_met150to225->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_bveto_SRA_met225to300->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_bveto_SRA_met225to300->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_bveto_SRA_met300toinf->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_bveto_SRA_met300toinf->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_withb_SRA_met100to150->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_withb_SRA_met100to150->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_withb_SRA_met150to225->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_withb_SRA_met150to225->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_withb_SRA_met225to300->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_withb_SRA_met225to300->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_withb_SRA_met300toinf->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_withb_SRA_met300toinf->GetBinError(signalbin)); 
  
  vector <double> val_zjets;  
  vector <double> err_zjets;  
  vector <double> err_zjets_closure;  
  val_zjets.push_back(33.22); err_zjets.push_back( 3.59); err_zjets_closure.push_back(1.15); // bveto
  val_zjets.push_back( 7.56); err_zjets.push_back( 2.19); err_zjets_closure.push_back(1.20);
  val_zjets.push_back( 1.06); err_zjets.push_back( 0.63); err_zjets_closure.push_back(1.30);
  val_zjets.push_back( 0.86); err_zjets.push_back( 0.86); err_zjets_closure.push_back(1.30);
  val_zjets.push_back(11.26); err_zjets.push_back( 6.87); err_zjets_closure.push_back(1.15); // withb
  val_zjets.push_back( 0.28); err_zjets.push_back( 3.31); err_zjets_closure.push_back(1.15);
  val_zjets.push_back( 0.30); err_zjets.push_back( 0.30); err_zjets_closure.push_back(1.25);
  val_zjets.push_back( 0.00); err_zjets.push_back( 0.50); err_zjets_closure.push_back(1.35);
  // val_zjets.push_back( 9.62); err_zjets.push_back( 0.72); err_zjets_closure.push_back(1.04); // bveto
  // val_zjets.push_back( 3.21); err_zjets.push_back( 0.52); err_zjets_closure.push_back(1.10);
  // val_zjets.push_back( 0.32); err_zjets.push_back( 0.12); err_zjets_closure.push_back(1.20);
  // val_zjets.push_back( 0.14); err_zjets.push_back( 0.08); err_zjets_closure.push_back(1.25);
  // val_zjets.push_back( 4.90); err_zjets.push_back( 0.66); err_zjets_closure.push_back(1.04); // withb
  // val_zjets.push_back( 1.51); err_zjets.push_back( 0.29); err_zjets_closure.push_back(1.10);
  // val_zjets.push_back( 0.43); err_zjets.push_back( 0.15); err_zjets_closure.push_back(1.20);
  // val_zjets.push_back( 0.29); err_zjets.push_back( 0.12); err_zjets_closure.push_back(1.25);
  val_zjets.push_back(23.46); err_zjets.push_back( 4.21); err_zjets_closure.push_back(1.04); // bveto
  val_zjets.push_back( 4.25); err_zjets.push_back( 0.56); err_zjets_closure.push_back(1.05);
  val_zjets.push_back( 1.38); err_zjets.push_back( 0.28); err_zjets_closure.push_back(1.15);
  val_zjets.push_back( 0.99); err_zjets.push_back( 0.37); err_zjets_closure.push_back(1.35);
  val_zjets.push_back( 4.54); err_zjets.push_back( 0.77); err_zjets_closure.push_back(1.05); // withb
  val_zjets.push_back( 1.35); err_zjets.push_back( 0.32); err_zjets_closure.push_back(1.10);
  val_zjets.push_back( 0.74); err_zjets.push_back( 0.27); err_zjets_closure.push_back(1.30);
  val_zjets.push_back( 0.26); err_zjets.push_back( 0.14); err_zjets_closure.push_back(1.40);
  
  vector <double> val_fsbkg;  
  vector <double> err_fsbkg;  
  val_fsbkg.push_back( 22.3); err_fsbkg.push_back( 6.1); 
  val_fsbkg.push_back( 14.8); err_fsbkg.push_back( 5.2); 
  val_fsbkg.push_back(  4.2); err_fsbkg.push_back( 3.4); 
  val_fsbkg.push_back(  2.1); err_fsbkg.push_back( 2.8); 
  val_fsbkg.push_back(123.0); err_fsbkg.push_back(15.0);
  val_fsbkg.push_back( 48.8); err_fsbkg.push_back( 8.8);
  val_fsbkg.push_back( 18.0); err_fsbkg.push_back( 5.6);
  val_fsbkg.push_back(  5.3); err_fsbkg.push_back( 3.6);

  val_fsbkg.push_back(  3.2); err_fsbkg.push_back( 3.1); 
  val_fsbkg.push_back(  3.2); err_fsbkg.push_back( 3.1); 
  val_fsbkg.push_back(  1.1); err_fsbkg.push_back( 2.4); 
  val_fsbkg.push_back(  0.0); err_fsbkg.push_back( 1.2); 
  val_fsbkg.push_back(  9.5); err_fsbkg.push_back( 4.3);
  val_fsbkg.push_back(  4.2); err_fsbkg.push_back( 3.3);
  val_fsbkg.push_back(  4.2); err_fsbkg.push_back( 3.3);
  val_fsbkg.push_back(  1.1); err_fsbkg.push_back( 2.4);

  double Rsfof = 1.06;
  
  vector <double> val_mcbkg;  
  vector <double> err_mcbkg;  
  val_mcbkg.push_back( 3.1); err_mcbkg.push_back( 1.55); 
  val_mcbkg.push_back( 2.3); err_mcbkg.push_back( 1.15); 
  val_mcbkg.push_back( 0.8); err_mcbkg.push_back( 0.40); 
  val_mcbkg.push_back( 1.1); err_mcbkg.push_back( 0.55); 
  val_mcbkg.push_back( 3.3); err_mcbkg.push_back( 1.65); 
  val_mcbkg.push_back( 2.0); err_mcbkg.push_back( 1.0); 
  val_mcbkg.push_back( 0.7); err_mcbkg.push_back( 0.35); 
  val_mcbkg.push_back( 0.4); err_mcbkg.push_back( 0.2); 

  val_mcbkg.push_back( 1.5); err_mcbkg.push_back( 0.75); 
  val_mcbkg.push_back( 1.2); err_mcbkg.push_back( 0.60); 
  val_mcbkg.push_back( 0.8); err_mcbkg.push_back( 0.40); 
  val_mcbkg.push_back( 0.9); err_mcbkg.push_back( 0.45); 
  val_mcbkg.push_back( 0.9); err_mcbkg.push_back( 0.45); 
  val_mcbkg.push_back( 0.8); err_mcbkg.push_back( 0.40); 
  val_mcbkg.push_back( 0.4); err_mcbkg.push_back( 0.20); 
  val_mcbkg.push_back( 0.2); err_mcbkg.push_back( 0.10); 
  
  // for( size_t binind = 0; binind < channel.size(); binind++ ){	
  
  fout <<  Form("imax %d  number of channels", (int)channel.size())    << endl;
  fout <<  "jmax 3  number of backgrounds"                        << endl;
  // fout <<  Form("kmax %d  number of nuisance parameters",n_syst)  << endl;
  fout <<  "kmax *  number of nuisance parameters" << endl;
  fout << setw(50) << left << "---------------"                           << endl;

  fout << setw(50) << left << "bin";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	fout  << setw(100) << right <<  Form(" %s ", channel.at(binind).c_str() );
  }
  fout << endl;

  fout << setw(50) << left << "observation";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	fout << setw(100) << right << Form(" %.0f", val_data.at(binind)      );
  }
  fout << setw(50) << endl << left << "---------------" << endl;

  fout << setw(50) << endl << left <<  "bin";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	fout << setw(25) << right << Form("%s",channel.at(binind).c_str());
	fout << setw(25) << right << Form("%s",channel.at(binind).c_str());
	fout << setw(25) << right << Form("%s",channel.at(binind).c_str());
	fout << setw(25) << right << Form("%s",channel.at(binind).c_str());
  }

  fout << endl << setw(50) << left << "process";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	fout << setw(25) << right << "sig";
	fout << setw(25) << right << "zjets";
	fout << setw(25) << right << "fsbkg";
	fout << setw(25) << right << "mcbkg";
  }
  fout << endl; 

  fout << setw(50) << left << "process";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	fout << setw(25) << right << "0";
	fout << setw(25) << right << "1";
	fout << setw(25) << right << "2";
	fout << setw(25) << right << "3";
  }

  fout << endl << setw(50) << left << "rate";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	fout << setw(25) << right << Form("%2.5f",val_signal.at(binind));
	fout << setw(25) << right << Form("%2.1f",val_zjets.at(binind));
	fout << setw(25) << right << Form("%2.6f",Rsfof*(float)((int)(val_fsbkg.at(binind)/(Rsfof-0.01))));
	fout << setw(25) << right << Form("%2.1f",val_mcbkg.at(binind));
  }
  fout << endl;
  fout << setw(50) << left <<  "---------------" << endl;
 
  // ---- sig systs
  fout << setw(40) << left << "sig_trig_syst";
  fout << setw(10) << left << "lnN";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
  	fout << setw(25) << right <<  "1.05";   
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  }
  fout << endl;

  //lepton scale + fastsim
  fout << setw(40) << left << "sig_leptonFS_syst";
  fout << setw(10) << left << "lnN";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
  	fout << setw(25) << right <<  "1.067";   
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  }
  fout << endl;

  //b-tag heavy systematic
  fout << setw(40) << left << "sig_btagheavy_syst";
  fout << setw(10) << left << "lnN";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	if( TString(channel.at(binind)).Contains("bveto") ){
	  fout << setw(25) << right <<  "0.95";   
	}else{
	  fout << setw(25) << right <<  "1.05";   
	}		
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  }
  fout << endl;

  //b-tag light systematic
  fout << setw(40) << left << "sig_btaglight_syst";
  fout << setw(10) << left << "lnN";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	if( TString(channel.at(binind)).Contains("bveto") ){
	  fout << setw(25) << right <<  "0.98";   
	}else{
	  fout << setw(25) << right <<  "1.02";   
	}		
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  }
  fout << endl;

  // JES systematic
  fout << setw(40) << left << "sig_lumi_syst";
  fout << setw(10) << left << "lnN";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	fout << setw(25) << right <<  "1.046";   
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  }
  fout << endl;

  // JES systematic
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
  	fout << setw(40) << left << "sig_JES_syst_"+channel.at(binind);
  	fout << setw(10) << left << "lnN";
  	for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	
  	  if( binindemb == binind ){
  		if( TString(channel.at(binind)).Contains("300toinf") ){
  		  fout << setw(25) << right <<  "1.02";   
  		}else{
  		  fout << setw(25) << right <<  "1.05";   
  		}		
  		fout << setw(25) << right <<  "-";
  		fout << setw(25) << right <<  "-";
  		fout << setw(25) << right <<  "-";
  	  }else{
  		fout << setw(25) << right << "-";
  		fout << setw(25) << right << "-";
  		fout << setw(25) << right << "-";
  		fout << setw(25) << right << "-";   
  	  }
  	}
  	fout << endl;
  }

  // // PDF systematic
  // for( size_t binind = 0; binind < channel.size(); binind++ ){	
  // 	fout << setw(40) << left << "sig_PDF_syst_"+channel.at(binind);
  // 	fout << setw(10) << left << "lnN";
  // 	for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	
  // 	  if( binindemb == binind ){
  // 		// if( TString(channel.at(binind)).Contains("100to150") ) fout << setw(25) << right <<  "1.20";   
  // 		// if( TString(channel.at(binind)).Contains("150to225") ) fout << setw(25) << right <<  "1.15";   
  // 		// if( TString(channel.at(binind)).Contains("225to300") ) fout << setw(25) << right <<  "1.10";   
  // 		// if( TString(channel.at(binind)).Contains("300toinf") ) fout << setw(25) << right <<  "1.05";   
  // 	    fout << setw(25) << right <<  "1.10";   
  // 		fout << setw(25) << right <<  "-";
  // 		fout << setw(25) << right <<  "-";
  // 		fout << setw(25) << right <<  "-";
  // 	  }else{
  // 		fout << setw(25) << right << "-";
  // 		fout << setw(25) << right << "-";
  // 		fout << setw(25) << right << "-";
  // 		fout << setw(25) << right << "-";   
  // 	  }
  // 	}
  // 	fout << endl;
  // }

  // uncorrelated statistical uncertainty on signal yield
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	fout << setw(40) << left << "sig_stat_syst_"+channel.at(binind);
	fout << setw(10) << left << "lnN";
	for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	
	  if( binindemb == binind ){
		if( err_signal.at(binind) > 0 ){
		  fout << setw(25) << right <<  Form("%.3f",1 + (err_signal.at(binind))/val_signal.at(binind));   
		}else{
		  fout << setw(25) << right <<  "2.0";   
		}
		fout << setw(25) << right <<  "-";
		fout << setw(25) << right <<  "-";
		fout << setw(25) << right <<  "-";
	  }else{
		fout << setw(25) << right << "-";
		fout << setw(25) << right << "-";
		fout << setw(25) << right << "-";
		fout << setw(25) << right << "-";   
	  }
	}
	fout << endl;
  }

  // correlated systematic uncertainty on Rsfof
  fout << setw(40) << left << "fsbkg_rsfof_syst";
  fout << setw(10) << left << "lnN";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	fout << setw(25) << right << "-";
	fout << setw(25) << right << "-";
	fout << setw(25) << right <<  Form("%.3f", 1.06);   
	fout << setw(25) << right << "-";
  }
  fout << endl;

  
  // // correlated systematic uncertainty on MC backgrounds
  // fout << setw(40) << left << "mcbkg_syst";
  // fout << setw(10) << left << "lnN";
  // for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	
  // 	fout << setw(25) << right << "-";
  // 	fout << setw(25) << right << "-";
  // 	fout << setw(25) << right << "-";
  // 	fout << setw(25) << right <<  Form("%.3f",1.50);
  // }
  // fout << endl;

  // partially correlated systematic uncertainty on template normalization
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	string zjets_norm_syst = "";
	if( TString(channel.at(binind)).Contains("bveto_SRA") )zjets_norm_syst  = "zjets_norm_syst_bveto_SRA";
	if( TString(channel.at(binind)).Contains("withb_SRA") )zjets_norm_syst  = "zjets_norm_syst_withb_SRA";
	if( TString(channel.at(binind)).Contains("bveto_SRB") )zjets_norm_syst  = "zjets_norm_syst_bveto_SRB";
	if( TString(channel.at(binind)).Contains("withb_SRB") )zjets_norm_syst  = "zjets_norm_syst_withb_SRB";
	fout << setw(40) << left << zjets_norm_syst;
	fout << setw(10) << left << "lnN";
	for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	
	  if( binindemb == binind ){
		fout << setw(25) << right <<  "-";
		if( TString(channel.at(binindemb)).Contains("bveto_SRA") )fout << setw(25) << right << "1.04";
		if( TString(channel.at(binindemb)).Contains("withb_SRA") )fout << setw(25) << right << "1.10";
		if( TString(channel.at(binindemb)).Contains("bveto_SRB") )fout << setw(25) << right << "1.03";
		if( TString(channel.at(binindemb)).Contains("withb_SRB") )fout << setw(25) << right << "1.06";
		fout << setw(25) << right <<  "-";
		fout << setw(25) << right <<  "-";
	  }else{
		fout << setw(25) << right << "-";
		fout << setw(25) << right << "-";
		fout << setw(25) << right << "-";
		fout << setw(25) << right << "-";   
	  }
	}
	fout << endl;
  }

  // uncorrelated systematic uncertainty on templates from closure test
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	fout << setw(40) << left << "zjets_clos_syst_"+channel.at(binind);
	fout << setw(10) << left << "lnN";
	for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	
	  if( binindemb == binind ){
		fout << setw(25) << right <<  "-";
		fout << setw(25) << right << Form("%.2f", err_zjets_closure.at(binindemb));
		fout << setw(25) << right <<  "-";
		fout << setw(25) << right <<  "-";
	  }else{
		fout << setw(25) << right << "-";
		fout << setw(25) << right << "-";
		fout << setw(25) << right << "-";
		fout << setw(25) << right << "-";   
	  }
	}
	fout << endl;
  }

  // uncorrelated systematic uncertainty on templates from statistics
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	fout << setw(40) << left << "zjets_stat_syst_"+channel.at(binind);
	fout << setw(10) << left << "lnN";
	for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	
	  if( binindemb == binind ){
		fout << setw(25) << right <<  "-";
		fout << setw(25) << right << Form("%.2f", 1 + err_zjets.at(binindemb)/val_zjets.at(binindemb));
		fout << setw(25) << right <<  "-";
		fout << setw(25) << right <<  "-";
	  }else{
		fout << setw(25) << right << "-";
		fout << setw(25) << right << "-";
		fout << setw(25) << right << "-";
		fout << setw(25) << right << "-";   
	  }
	}
	fout << endl;
  }

  // statistical uncertainty on FSbkg
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	fout << setw(40) << left << "fsbkg_stat_syst_"+channel.at(binind);
	fout << setw(10) << left << Form("gmN %d", (int)(val_fsbkg.at(binind)/(Rsfof-0.01)) );
	for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	

	  if( binindemb == binind ){
		fout << setw(25) << right << "-";
		fout << setw(25) << right << "-";
		fout << setw(25) << right <<  Form("%.3f", Rsfof);   
		fout << setw(25) << right << "-";
	  }else{
		fout << setw(25) << right << "-";
		fout << setw(25) << right << "-";
		fout << setw(25) << right << "-";
		fout << setw(25) << right << "-";   
	  }
	}
	fout << endl;
  }

  // uncorrelated systematic uncertainty on MC backgrounds
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
  	fout << setw(40) << left << "mcbkg_syst_"+channel.at(binind);
  	fout << setw(10) << left << "lnN";
  	for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	
  	  if( binindemb == binind ){
  		fout << setw(25) << right << "-";   
  		fout << setw(25) << right << "-";   
  		fout << setw(25) << right << "-";   
  		fout << setw(25) << right <<  Form("%.3f",1 + err_mcbkg.at(binindemb)/val_mcbkg.at(binindemb));   
  	  }else{
  		fout << setw(25) << right << "-";   
  		fout << setw(25) << right << "-";   
  		fout << setw(25) << right << "-";   
  		fout << setw(25) << right << "-";   
  	  }
  	}
  	fout << endl;
  }

  fout.close();
  
  return;
}


void makeDataCards()
{

  // for( int xbinind = 12; xbinind < 13; xbinind++ ){
  // 	for( int ybinind = 2; ybinind < xbinind-1; ybinind++ ){
  // 	  cout<<Form("Making datacard for %i | %i",xbinind*50,ybinind*50)<<endl;
  // 	  makeDataCard(xbinind*50, ybinind*50);
  // 	}
  // }

  for( int xbinind = 12; xbinind < 36; xbinind++ ){
  	for( int ybinind = 2; ybinind < xbinind+1; ybinind++ ){
  	  cout<<Form("Making datacard for %i | %i",xbinind*50,ybinind*50)<<endl;
  	  makeDataCard(xbinind*50, ybinind*50);
  	}
  }
  
  return;
}
