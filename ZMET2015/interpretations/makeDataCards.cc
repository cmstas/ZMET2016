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

  TFile * f_eventcounts_bveto_SRB              = TFile::Open("../output/V08-11-00/fullscan_SRB_bveto_fastsimMET_hists.root","READ");
  TFile * f_eventcounts_withb_SRB              = TFile::Open("../output/V08-11-00/fullscan_SRB_withb_fastsimMET_hists.root","READ");
  TFile * f_eventcounts_bveto_SRB_nofastsimmet = TFile::Open("../output/V08-11-00/fullscan_SRB_bveto_hists.root","READ");
  TFile * f_eventcounts_withb_SRB_nofastsimmet = TFile::Open("../output/V08-11-00/fullscan_SRB_withb_hists.root","READ");
  
  TH2F * h_eventcounts_bveto_SRB_met100to150 = NULL; TH2F * h_eventcounts_bveto_SRB_met100to150_nofastsimmet = NULL;
  TH2F * h_eventcounts_bveto_SRB_met150to225 = NULL; TH2F * h_eventcounts_bveto_SRB_met150to225_nofastsimmet = NULL;
  TH2F * h_eventcounts_bveto_SRB_met225to300 = NULL; TH2F * h_eventcounts_bveto_SRB_met225to300_nofastsimmet = NULL;
  TH2F * h_eventcounts_bveto_SRB_met300toinf = NULL; TH2F * h_eventcounts_bveto_SRB_met300toinf_nofastsimmet = NULL;
  TH2F * h_eventcounts_withb_SRB_met100to150 = NULL; TH2F * h_eventcounts_withb_SRB_met100to150_nofastsimmet = NULL;
  TH2F * h_eventcounts_withb_SRB_met150to225 = NULL; TH2F * h_eventcounts_withb_SRB_met150to225_nofastsimmet = NULL;
  TH2F * h_eventcounts_withb_SRB_met225to300 = NULL; TH2F * h_eventcounts_withb_SRB_met225to300_nofastsimmet = NULL;
  TH2F * h_eventcounts_withb_SRB_met300toinf = NULL; TH2F * h_eventcounts_withb_SRB_met300toinf_nofastsimmet = NULL;

  h_eventcounts_bveto_SRB_met100to150 = (TH2F*)f_eventcounts_bveto_SRB->Get("h_signalyields_met100to150_ll")->Clone("h_eventcounts_bveto_SRB_met100to150");
  h_eventcounts_bveto_SRB_met150to225 = (TH2F*)f_eventcounts_bveto_SRB->Get("h_signalyields_met150to225_ll")->Clone("h_eventcounts_bveto_SRB_met150to225");
  h_eventcounts_bveto_SRB_met225to300 = (TH2F*)f_eventcounts_bveto_SRB->Get("h_signalyields_met225to300_ll")->Clone("h_eventcounts_bveto_SRB_met225to300");
  h_eventcounts_bveto_SRB_met300toinf = (TH2F*)f_eventcounts_bveto_SRB->Get("h_signalyields_met300toinf_ll")->Clone("h_eventcounts_bveto_SRB_met300toinf");
  h_eventcounts_withb_SRB_met100to150 = (TH2F*)f_eventcounts_withb_SRB->Get("h_signalyields_met100to150_ll")->Clone("h_eventcounts_withb_SRB_met100to150");
  h_eventcounts_withb_SRB_met150to225 = (TH2F*)f_eventcounts_withb_SRB->Get("h_signalyields_met150to225_ll")->Clone("h_eventcounts_withb_SRB_met150to225");
  h_eventcounts_withb_SRB_met225to300 = (TH2F*)f_eventcounts_withb_SRB->Get("h_signalyields_met225to300_ll")->Clone("h_eventcounts_withb_SRB_met225to300");
  h_eventcounts_withb_SRB_met300toinf = (TH2F*)f_eventcounts_withb_SRB->Get("h_signalyields_met300toinf_ll")->Clone("h_eventcounts_withb_SRB_met300toinf");

  h_eventcounts_bveto_SRB_met100to150_nofastsimmet = (TH2F*)f_eventcounts_bveto_SRB_nofastsimmet->Get("h_signalyields_met100to150_ll")->Clone("h_eventcounts_bveto_SRB_met100to150_nofastsimmet");
  h_eventcounts_bveto_SRB_met150to225_nofastsimmet = (TH2F*)f_eventcounts_bveto_SRB_nofastsimmet->Get("h_signalyields_met150to225_ll")->Clone("h_eventcounts_bveto_SRB_met150to225_nofastsimmet");
  h_eventcounts_bveto_SRB_met225to300_nofastsimmet = (TH2F*)f_eventcounts_bveto_SRB_nofastsimmet->Get("h_signalyields_met225to300_ll")->Clone("h_eventcounts_bveto_SRB_met225to300_nofastsimmet");
  h_eventcounts_bveto_SRB_met300toinf_nofastsimmet = (TH2F*)f_eventcounts_bveto_SRB_nofastsimmet->Get("h_signalyields_met300toinf_ll")->Clone("h_eventcounts_bveto_SRB_met300toinf_nofastsimmet");
  h_eventcounts_withb_SRB_met100to150_nofastsimmet = (TH2F*)f_eventcounts_withb_SRB_nofastsimmet->Get("h_signalyields_met100to150_ll")->Clone("h_eventcounts_withb_SRB_met100to150_nofastsimmet");
  h_eventcounts_withb_SRB_met150to225_nofastsimmet = (TH2F*)f_eventcounts_withb_SRB_nofastsimmet->Get("h_signalyields_met150to225_ll")->Clone("h_eventcounts_withb_SRB_met150to225_nofastsimmet");
  h_eventcounts_withb_SRB_met225to300_nofastsimmet = (TH2F*)f_eventcounts_withb_SRB_nofastsimmet->Get("h_signalyields_met225to300_ll")->Clone("h_eventcounts_withb_SRB_met225to300_nofastsimmet");
  h_eventcounts_withb_SRB_met300toinf_nofastsimmet = (TH2F*)f_eventcounts_withb_SRB_nofastsimmet->Get("h_signalyields_met300toinf_ll")->Clone("h_eventcounts_withb_SRB_met300toinf_nofastsimmet");

  h_eventcounts_bveto_SRB_met100to150->SetDirectory(rootdir);
  h_eventcounts_bveto_SRB_met150to225->SetDirectory(rootdir);
  h_eventcounts_bveto_SRB_met225to300->SetDirectory(rootdir);
  h_eventcounts_bveto_SRB_met300toinf->SetDirectory(rootdir);
  h_eventcounts_withb_SRB_met100to150->SetDirectory(rootdir);
  h_eventcounts_withb_SRB_met150to225->SetDirectory(rootdir);
  h_eventcounts_withb_SRB_met225to300->SetDirectory(rootdir);
  h_eventcounts_withb_SRB_met300toinf->SetDirectory(rootdir);

  h_eventcounts_bveto_SRB_met100to150_nofastsimmet->SetDirectory(rootdir);
  h_eventcounts_bveto_SRB_met150to225_nofastsimmet->SetDirectory(rootdir);
  h_eventcounts_bveto_SRB_met225to300_nofastsimmet->SetDirectory(rootdir);
  h_eventcounts_bveto_SRB_met300toinf_nofastsimmet->SetDirectory(rootdir);
  h_eventcounts_withb_SRB_met100to150_nofastsimmet->SetDirectory(rootdir);
  h_eventcounts_withb_SRB_met150to225_nofastsimmet->SetDirectory(rootdir);
  h_eventcounts_withb_SRB_met225to300_nofastsimmet->SetDirectory(rootdir);
  h_eventcounts_withb_SRB_met300toinf_nofastsimmet->SetDirectory(rootdir);

  f_eventcounts_bveto_SRB ->Close();
  f_eventcounts_withb_SRB ->Close();
  f_eventcounts_bveto_SRB_nofastsimmet ->Close();
  f_eventcounts_withb_SRB_nofastsimmet ->Close();

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
  
  vector <double> val_data;  
  val_data.push_back(122);  
  val_data.push_back( 45);  
  val_data.push_back( 11);  
  val_data.push_back(  7);  
  val_data.push_back(238);//43
  val_data.push_back( 99);//22
  val_data.push_back( 24);//3
  val_data.push_back(  7);
  
  int signalbin = h_eventcounts_bveto_SRB_met100to150->FindBin(mglu,mlsp);
  
  vector <double> val_signal;  
  vector <double> val_signal_nofastsimmet;  
  vector <double> err_signal;  
  val_signal.push_back(h_eventcounts_bveto_SRB_met100to150->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_bveto_SRB_met100to150->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_bveto_SRB_met150to225->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_bveto_SRB_met150to225->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_bveto_SRB_met225to300->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_bveto_SRB_met225to300->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_bveto_SRB_met300toinf->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_bveto_SRB_met300toinf->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_withb_SRB_met100to150->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_withb_SRB_met100to150->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_withb_SRB_met150to225->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_withb_SRB_met150to225->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_withb_SRB_met225to300->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_withb_SRB_met225to300->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_withb_SRB_met300toinf->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_withb_SRB_met300toinf->GetBinError(signalbin)); 

  val_signal_nofastsimmet.push_back(h_eventcounts_bveto_SRB_met100to150_nofastsimmet->GetBinContent(signalbin)); 
  val_signal_nofastsimmet.push_back(h_eventcounts_bveto_SRB_met150to225_nofastsimmet->GetBinContent(signalbin)); 
  val_signal_nofastsimmet.push_back(h_eventcounts_bveto_SRB_met225to300_nofastsimmet->GetBinContent(signalbin)); 
  val_signal_nofastsimmet.push_back(h_eventcounts_bveto_SRB_met300toinf_nofastsimmet->GetBinContent(signalbin)); 
  val_signal_nofastsimmet.push_back(h_eventcounts_withb_SRB_met100to150_nofastsimmet->GetBinContent(signalbin)); 
  val_signal_nofastsimmet.push_back(h_eventcounts_withb_SRB_met150to225_nofastsimmet->GetBinContent(signalbin)); 
  val_signal_nofastsimmet.push_back(h_eventcounts_withb_SRB_met225to300_nofastsimmet->GetBinContent(signalbin)); 
  val_signal_nofastsimmet.push_back(h_eventcounts_withb_SRB_met300toinf_nofastsimmet->GetBinContent(signalbin)); 

  vector <double> val_zjets;  
  vector <double> err_zjets;  
  vector <double> err_zjets_closure;  
  val_zjets.push_back( 75.1); err_zjets.push_back( 8.84); err_zjets_closure.push_back(1.20); // bveto
  val_zjets.push_back( 11.3); err_zjets.push_back( 2.20); err_zjets_closure.push_back(1.20);
  val_zjets.push_back( 1.57); err_zjets.push_back( 0.52); err_zjets_closure.push_back(1.20);
  val_zjets.push_back( 1.61); err_zjets.push_back( 1.24); err_zjets_closure.push_back(1.25);
  val_zjets.push_back(27.00); err_zjets.push_back( 3.94); err_zjets_closure.push_back(1.20); // withb
  val_zjets.push_back( 4.01); err_zjets.push_back( 1.08); err_zjets_closure.push_back(1.20);
  val_zjets.push_back( 1.18); err_zjets.push_back( 0.62); err_zjets_closure.push_back(1.20);
  val_zjets.push_back( 0.01); err_zjets.push_back( 0.18); err_zjets_closure.push_back(1.40);
  
  vector <double> val_fsbkg;  
  vector <double> err_fsbkg;  
  val_fsbkg.push_back( 44.4); err_fsbkg.push_back( 8.1); 
  val_fsbkg.push_back( 23.8); err_fsbkg.push_back( 6.2); 
  val_fsbkg.push_back(  8.7); err_fsbkg.push_back( 4.3); 
  val_fsbkg.push_back(  2.2); err_fsbkg.push_back( 2.9); 
  val_fsbkg.push_back(207.9); err_fsbkg.push_back(16.7);
  val_fsbkg.push_back( 73.6); err_fsbkg.push_back(10.1);
  val_fsbkg.push_back( 21.7); err_fsbkg.push_back( 6.0);
  val_fsbkg.push_back(  6.5); err_fsbkg.push_back( 3.9);

  double Rsfof = 1.083;
  
  vector <double> val_mcbkg;  
  vector <double> err_mcbkg;  
  val_mcbkg.push_back( 5.7); err_mcbkg.push_back( 2.45); 
  val_mcbkg.push_back( 4.4); err_mcbkg.push_back( 1.7 ); 
  val_mcbkg.push_back( 1.4); err_mcbkg.push_back( 0.65); 
  val_mcbkg.push_back( 1.9); err_mcbkg.push_back( 0.35); 
  val_mcbkg.push_back( 4.9); err_mcbkg.push_back( 0.50); 
  val_mcbkg.push_back( 3.0); err_mcbkg.push_back( 0.30); 
  val_mcbkg.push_back( 1.1); err_mcbkg.push_back( 0.20); 
  val_mcbkg.push_back( 0.6); err_mcbkg.push_back( 0.10); 
  
  fout <<  Form("imax %d  number of channels", (int)channel.size()) << endl;
  fout <<  "jmax 3  number of backgrounds"                          << endl;
  // fout <<  Form("kmax %d  number of nuisance parameters",n_syst)  << endl;
  fout <<  "kmax *  number of nuisance parameters" << endl;
  fout << setw(50) << left << "---------------"                     << endl;

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
 
  // ---- sig systs for MET from FS
  fout << setw(40) << left << "sig_metfromFS_syst";
  fout << setw(10) << left << "lnN";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
  	fout << setw(25) << right <<  Form("%1.3f", 1 + 0.5 * abs(val_signal.at(binind)-val_signal_nofastsimmet.at(binind))/(val_signal.at(binind)));
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  }
  fout << endl;

  //lepton scale + fastsim
  fout << setw(40) << left << "sig_leptonFS_syst";
  fout << setw(10) << left << "lnN";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
  	fout << setw(25) << right <<  "1.086";   
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
	  fout << setw(25) << right <<  "0.96";   
	}else{
	  fout << setw(25) << right <<  "1.04";   
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
	fout << setw(25) << right <<  "1.062";   
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  }
  fout << endl;


  // ISR systematic
  fout << setw(40) << left << "sig_lumi_syst";
  fout << setw(10) << left << "lnN";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
  if( mglu - mlsp < 150 ) fout << setw(25) << right <<  "1.05";   
  else                    fout << setw(25) << right <<  "1.01";   
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
  		  fout << setw(25) << right <<  "1.01";   
  		}else{
  		  fout << setw(25) << right <<  "1.01";   
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
	fout << setw(25) << right <<  Form("%.3f", 1.026);   
	fout << setw(25) << right << "-";
  }
  fout << endl;

  
  // correlated systematic uncertainty on MC backgrounds
  fout << setw(40) << left << "mcbkg_syst";
  fout << setw(10) << left << "lnN";
  for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	
  	fout << setw(25) << right << "-";
  	fout << setw(25) << right << "-";
  	fout << setw(25) << right << "-";
  	fout << setw(25) << right <<  Form("%.3f",1.50);
  }
  fout << endl;

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
		if( TString(channel.at(binindemb)).Contains("bveto_SRA") )fout << setw(25) << right << "1.02";
		if( TString(channel.at(binindemb)).Contains("withb_SRA") )fout << setw(25) << right << "1.05";
		if( TString(channel.at(binindemb)).Contains("bveto_SRB") )fout << setw(25) << right << "1.02";
		if( TString(channel.at(binindemb)).Contains("withb_SRB") )fout << setw(25) << right << "1.04";
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
