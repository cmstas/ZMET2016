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

  TFile * f_eventcounts_SR_EWK              = TFile::Open("../output/V08-11-00/fullscan_tchiwz_SR_EWK_fastsimMET_hists.root","READ");
  TFile * f_eventcounts_SR_EWK_nofastsimmet = TFile::Open("../output/V08-11-00/fullscan_tchiwz_SR_EWK_hists.root","READ");

  TH2F * h_eventcounts_SR_EWK_met150to225 = NULL; 
  TH2F * h_eventcounts_SR_EWK_met225to300 = NULL; 
  TH2F * h_eventcounts_SR_EWK_met300toinf = NULL; 

  TH2F * h_eventcounts_SR_EWK_met150to225_nofastsimmet = NULL; 
  TH2F * h_eventcounts_SR_EWK_met225to300_nofastsimmet = NULL; 
  TH2F * h_eventcounts_SR_EWK_met300toinf_nofastsimmet = NULL; 

  h_eventcounts_SR_EWK_met150to225 = (TH2F*)f_eventcounts_SR_EWK->Get("h_signalyields_met150to225_ll")->Clone("h_eventcounts_SR_EWK_met150to225");
  h_eventcounts_SR_EWK_met225to300 = (TH2F*)f_eventcounts_SR_EWK->Get("h_signalyields_met225to300_ll")->Clone("h_eventcounts_SR_EWK_met225to300");
  h_eventcounts_SR_EWK_met300toinf = (TH2F*)f_eventcounts_SR_EWK->Get("h_signalyields_met300toinf_ll")->Clone("h_eventcounts_SR_EWK_met300toinf");

  h_eventcounts_SR_EWK_met150to225_nofastsimmet = (TH2F*)f_eventcounts_SR_EWK_nofastsimmet->Get("h_signalyields_met150to225_ll")->Clone("h_eventcounts_SR_EWK_met150to225_nofastsimmet");
  h_eventcounts_SR_EWK_met225to300_nofastsimmet = (TH2F*)f_eventcounts_SR_EWK_nofastsimmet->Get("h_signalyields_met225to300_ll")->Clone("h_eventcounts_SR_EWK_met225to300_nofastsimmet");
  h_eventcounts_SR_EWK_met300toinf_nofastsimmet = (TH2F*)f_eventcounts_SR_EWK_nofastsimmet->Get("h_signalyields_met300toinf_ll")->Clone("h_eventcounts_SR_EWK_met300toinf_nofastsimmet");

  h_eventcounts_SR_EWK_met150to225->SetDirectory(rootdir);
  h_eventcounts_SR_EWK_met225to300->SetDirectory(rootdir);
  h_eventcounts_SR_EWK_met300toinf->SetDirectory(rootdir);

  h_eventcounts_SR_EWK_met150to225_nofastsimmet->SetDirectory(rootdir);
  h_eventcounts_SR_EWK_met225to300_nofastsimmet->SetDirectory(rootdir);
  h_eventcounts_SR_EWK_met300toinf_nofastsimmet->SetDirectory(rootdir);

  f_eventcounts_SR_EWK ->Close();
  f_eventcounts_SR_EWK_nofastsimmet ->Close();

  string cardname = Form("datacards/datacard_mGluino_%d_mLSP_%d_.txt",mglu,mlsp);

  cout<<"Writing card for: "<<cardname<<endl;
  
  ofstream fout;
  fout.open(cardname);

  // int n_syst = 9;

  vector <string> channel;  
  channel.push_back("SR_EWK_met150to225");  
  channel.push_back("SR_EWK_met225to300");  
  channel.push_back("SR_EWK_met300toinf");  
  
  vector <double> val_data;  
  val_data.push_back( 45);  
  val_data.push_back( 15);  
  val_data.push_back(  7);  
  
  int signalbin = h_eventcounts_SR_EWK_met150to225->FindBin(mglu,mlsp);
  
  vector <double> val_signal;  
  vector <double> val_signal_nofastsimmet;  
  vector <double> err_signal;  
  val_signal.push_back(h_eventcounts_SR_EWK_met150to225->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_SR_EWK_met150to225->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_SR_EWK_met225to300->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_SR_EWK_met225to300->GetBinError(signalbin)); 
  val_signal.push_back(h_eventcounts_SR_EWK_met300toinf->GetBinContent(signalbin)); err_signal.push_back(h_eventcounts_SR_EWK_met300toinf->GetBinError(signalbin)); 

  val_signal_nofastsimmet.push_back(h_eventcounts_SR_EWK_met150to225_nofastsimmet->GetBinContent(signalbin)); 
  val_signal_nofastsimmet.push_back(h_eventcounts_SR_EWK_met225to300_nofastsimmet->GetBinContent(signalbin)); 
  val_signal_nofastsimmet.push_back(h_eventcounts_SR_EWK_met300toinf_nofastsimmet->GetBinContent(signalbin)); 

  // cout<<"nofastsim: "<<h_eventcounts_SR_EWK_met150to225_nofastsimmet->GetBinContent(signalbin)<<endl;
  // cout<<"w/fastsim: "<<h_eventcounts_SR_EWK_met150to225->GetBinContent(signalbin)<<endl;
  
  vector <double> val_zjets;  
  vector <double> err_zjets;  
  vector <double> err_zjets_closure;  
  val_zjets.push_back( 18.3); err_zjets.push_back( 2.06); err_zjets_closure.push_back(1.10);
  val_zjets.push_back( 4.69); err_zjets.push_back( 1.29); err_zjets_closure.push_back(1.15);
  val_zjets.push_back( 2.73); err_zjets.push_back( 0.79); err_zjets_closure.push_back(1.15);
  
  vector <double> val_fsbkg;  
  vector <double> err_fsbkg;  
  val_fsbkg.push_back( 3.91); err_fsbkg.push_back( 1.36); 
  val_fsbkg.push_back( 0.50); err_fsbkg.push_back( 0.27); 
  val_fsbkg.push_back( 0.10); err_fsbkg.push_back( 0.11); 

  // double Rsfof = 1.083;
  
  vector <double> val_mcbkg;  
  vector <double> err_mcbkg;  
  val_mcbkg.push_back(12.74); err_mcbkg.push_back( 3.03); 
  val_mcbkg.push_back( 6.07); err_mcbkg.push_back( 1.67); 
  val_mcbkg.push_back( 5.04); err_mcbkg.push_back( 1.39); 
  
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
	fout << setw(25) << right << Form("%2.6f",val_fsbkg.at(binind));
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
	fout << setw(25) << right <<  "1.01";   
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  }
  fout << endl;

  //b-tag light systematic
  fout << setw(40) << left << "sig_btaglight_syst";
  fout << setw(10) << left << "lnN";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
  	fout << setw(25) << right <<  "1.00";   
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  	fout << setw(25) << right <<  "-";
  }
  fout << endl;

  // lumi systematic
  fout << setw(40) << left << "sig_lumi_syst";
  fout << setw(10) << left << "lnN";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	fout << setw(25) << right <<  "1.062";   
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
		fout << setw(25) << right <<  "1.05";   
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

  // // correlated systematic uncertainty on Rsfof
  // fout << setw(40) << left << "fsbkg_rsfof_syst";
  // fout << setw(10) << left << "lnN";
  // for( size_t binind = 0; binind < channel.size(); binind++ ){	
  // 	fout << setw(25) << right << "-";
  // 	fout << setw(25) << right << "-";
  // 	fout << setw(25) << right <<  Form("%.3f", 1.06);   
  // 	fout << setw(25) << right << "-";
  // }
  // fout << endl;

  
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
	zjets_norm_syst  = "zjets_norm_syst_SR_EWK";
	fout << setw(40) << left << zjets_norm_syst;
	fout << setw(10) << left << "lnN";
	for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	
	  if( binindemb == binind ){
		fout << setw(25) << right <<  "-";
		fout << setw(25) << right << "1.05";
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

  // // statistical uncertainty on FSbkg
  // for( size_t binind = 0; binind < channel.size(); binind++ ){	
  // 	fout << setw(40) << left << "fsbkg_stat_syst_"+channel.at(binind);
  // 	fout << setw(10) << left << Form("gmN %d", (int)(val_fsbkg.at(binind)/(Rsfof-0.01)) );
  // 	for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	

  // 	  if( binindemb == binind ){
  // 		fout << setw(25) << right << "-";
  // 		fout << setw(25) << right << "-";
  // 		fout << setw(25) << right <<  Form("%.3f", Rsfof);   
  // 		fout << setw(25) << right << "-";
  // 	  }else{
  // 		fout << setw(25) << right << "-";
  // 		fout << setw(25) << right << "-";
  // 		fout << setw(25) << right << "-";
  // 		fout << setw(25) << right << "-";   
  // 	  }
  // 	}
  // 	fout << endl;
  // }

  // // uncorrelated systematic uncertainty on MC backgrounds
  // for( size_t binind = 0; binind < channel.size(); binind++ ){	
  // 	fout << setw(40) << left << "mcbkg_syst_"+channel.at(binind);
  // 	fout << setw(10) << left << "lnN";
  // 	for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	
  // 	  if( binindemb == binind ){
  // 		fout << setw(25) << right << "-";   
  // 		fout << setw(25) << right << "-";   
  // 		fout << setw(25) << right << "-";   
  // 		fout << setw(25) << right <<  Form("%.3f",1 + err_mcbkg.at(binindemb)/val_mcbkg.at(binindemb));   
  // 	  }else{
  // 		fout << setw(25) << right << "-";   
  // 		fout << setw(25) << right << "-";   
  // 		fout << setw(25) << right << "-";   
  // 		fout << setw(25) << right << "-";   
  // 	  }
  // 	}
  // 	fout << endl;
  // }

  // uncorrelated statistical uncertainty on FS backgrounds
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
  	fout << setw(40) << left << "fsbkg_syst_"+channel.at(binind);
  	fout << setw(10) << left << "lnN";
  	for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	
  	  if( binindemb == binind ){
  		fout << setw(25) << right << "-";   
  		fout << setw(25) << right << "-";   
  		fout << setw(25) << right <<  Form("%.3f",1 + err_fsbkg.at(binindemb)/val_fsbkg.at(binindemb));   
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

  fout.close();
  
  return;
}


void makeDataCards()
{

  for( int xbinind = 4; xbinind < 31; xbinind++ ){
  	for( int ybinind = 0; ybinind < 32; ybinind++ ){
  	  // int binind = h_entries->FindBin(xbinind*25,ybinind*10);
  	  cout<<Form("Making datacard for %i | %i",xbinind*25,ybinind*10)<<endl;
  	  makeDataCard(xbinind*25, ybinind*10);
  	}
  }

  // makeDataCard(200, 0);

  return;
}
