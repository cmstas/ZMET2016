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
#include "TMath.h"

#include "Math/VectorUtil.h"

#include "../sharedCode/histTools.h"
#include "../sharedCode/ZMET.h"
#include "../sharedCode/METTemplateSelections.h"
#include "../sharedCode/AnalysisSelections.h"


void makeDataCards()
{

  int mglu = 600;
  int mlsp = 100;

  string cardname = "datacard_mGluino%d_mLSP%d.txt";
  
  ofstream fout;
  fout.open(cardname);

  double val_sig = 10.3;
  double err_sig = 0.10;

  int n_syst = 9;

  vector <string> channel;  
  channel.push_back("bveto_SRA_met100to150");  channel.push_back("withb_SRA_met100to150");
  // channel.push_back("bveto_SRA_met150to225");  channel.push_back("withb_SRA_met150to225");
  // channel.push_back("bveto_SRA_met225to300");  channel.push_back("withb_SRA_met225to300");
  // channel.push_back("bveto_SRA_met300toinf");  channel.push_back("withb_SRA_met300toinf");
  // channel.push_back("bveto_SRB_met100to150");  channel.push_back("withb_SRB_met100to150");
  // channel.push_back("bveto_SRB_met150to225");  channel.push_back("withb_SRB_met150to225");
  // channel.push_back("bveto_SRB_met225to300");  channel.push_back("withb_SRB_met225to300");
  // channel.push_back("bveto_SRB_met300toinf");  channel.push_back("withb_SRB_met300toinf");

  vector <double> val_data;  
  val_data.push_back(28);  val_data.push_back(21);
  val_data.push_back( 6);  val_data.push_back( 6);
  val_data.push_back( 5);  val_data.push_back( 1);
  val_data.push_back( 6);  val_data.push_back( 3);
  val_data.push_back(20);  val_data.push_back(43);
  val_data.push_back(10);  val_data.push_back(22);
  val_data.push_back( 2);  val_data.push_back( 3);
  val_data.push_back( 0);  val_data.push_back( 3);

  vector <double> val_zjets;  
  vector <double> err_zjets;  
  vector <double> err_zjets_closure;  
  val_zjets.push_back(23.5); err_zjets.push_back( 4.4); err_zjets_closure.push_back(1.04); // bveto
  val_zjets.push_back( 4.3); err_zjets.push_back( 0.6); err_zjets_closure.push_back(1.05);
  val_zjets.push_back( 1.4); err_zjets.push_back( 0.4); err_zjets_closure.push_back(1.15);
  val_zjets.push_back( 1.0); err_zjets.push_back( 0.5); err_zjets_closure.push_back(1.35);
  val_zjets.push_back( 9.6); err_zjets.push_back( 0.9); err_zjets_closure.push_back(1.04);
  val_zjets.push_back( 3.2); err_zjets.push_back( 0.6); err_zjets_closure.push_back(1.10);
  val_zjets.push_back( 0.3); err_zjets.push_back( 0.1); err_zjets_closure.push_back(1.20);
  val_zjets.push_back( 0.1); err_zjets.push_back( 0.1); err_zjets_closure.push_back(1.25);
  val_zjets.push_back( 4.5); err_zjets.push_back( 0.9); err_zjets_closure.push_back(1.05); // withb
  val_zjets.push_back( 1.3); err_zjets.push_back( 0.4);	err_zjets_closure.push_back(1.10);
  val_zjets.push_back( 0.7); err_zjets.push_back( 0.4);	err_zjets_closure.push_back(1.30);
  val_zjets.push_back( 0.3); err_zjets.push_back( 0.2);	err_zjets_closure.push_back(1.40);
  val_zjets.push_back( 4.9); err_zjets.push_back( 0.9);	err_zjets_closure.push_back(1.04);
  val_zjets.push_back( 1.5); err_zjets.push_back( 0.3);	err_zjets_closure.push_back(1.10);
  val_zjets.push_back( 0.4); err_zjets.push_back( 0.3);	err_zjets_closure.push_back(1.20);
  val_zjets.push_back( 0.3); err_zjets.push_back( 0.2);	err_zjets_closure.push_back(1.25);






  
  vector <double> val_fsbkg;  
  vector <double> err_fsbkg;  
  val_fsbkg.push_back( 3.2); err_fsbkg.push_back( 3.1); val_fsbkg.push_back( 9.5); err_fsbkg.push_back( 4.3);
  val_fsbkg.push_back( 3.2); err_fsbkg.push_back( 3.1); val_fsbkg.push_back( 4.2); err_fsbkg.push_back( 3.3);
  val_fsbkg.push_back( 1.1); err_fsbkg.push_back( 2.4); val_fsbkg.push_back( 4.2); err_fsbkg.push_back( 3.3);
  val_fsbkg.push_back( 0.0); err_fsbkg.push_back( 1.2); val_fsbkg.push_back( 1.1); err_fsbkg.push_back( 2.4);
  val_fsbkg.push_back(12.6); err_fsbkg.push_back( 4.8); val_fsbkg.push_back(38.9); err_fsbkg.push_back( 7.6);
  val_fsbkg.push_back( 4.2); err_fsbkg.push_back( 3.3); val_fsbkg.push_back(14.7); err_fsbkg.push_back( 5.1);
  val_fsbkg.push_back( 0.0); err_fsbkg.push_back( 1.2); val_fsbkg.push_back( 0.0); err_fsbkg.push_back( 1.2);
  val_fsbkg.push_back( 1.1); err_fsbkg.push_back( 2.4); val_fsbkg.push_back( 1.1); err_fsbkg.push_back( 2.4);
  double Rsfof = 1.051;

  
  vector <double> val_mcbkg;  
  vector <double> err_mcbkg;  
  val_mcbkg.push_back( 1.5); err_mcbkg.push_back( 0.75); val_mcbkg.push_back( 0.9); err_mcbkg.push_back( 0.45); 
  val_mcbkg.push_back( 1.2); err_mcbkg.push_back( 0.60); val_mcbkg.push_back( 0.8); err_mcbkg.push_back( 0.40); 
  val_mcbkg.push_back( 0.8); err_mcbkg.push_back( 0.40); val_mcbkg.push_back( 0.4); err_mcbkg.push_back( 0.20); 
  val_mcbkg.push_back( 0.9); err_mcbkg.push_back( 0.45); val_mcbkg.push_back( 0.2); err_mcbkg.push_back( 0.10); 
  val_mcbkg.push_back( 0.3); err_mcbkg.push_back( 0.15); val_mcbkg.push_back( 0.8); err_mcbkg.push_back( 0.40); 
  val_mcbkg.push_back( 0.2); err_mcbkg.push_back( 0.10); val_mcbkg.push_back( 0.5); err_mcbkg.push_back( 0.25); 
  val_mcbkg.push_back( 0.1); err_mcbkg.push_back( 0.05); val_mcbkg.push_back( 0.2); err_mcbkg.push_back( 0.10); 
  val_mcbkg.push_back( 0.2); err_mcbkg.push_back( 0.10); val_mcbkg.push_back( 0.1); err_mcbkg.push_back( 0.05); 

  // for( size_t binind = 0; binind < channel.size(); binind++ ){	
  
  cout <<  Form("imax %d  number of channels", (int)channel.size())    << endl;
  cout <<  "jmax 3  number of backgrounds"                        << endl;
  // cout <<  Form("kmax %d  number of nuisance parameters",n_syst)  << endl;
  cout <<  "kmax *  number of nuisance parameters" << endl;
  cout << setw(50) << left << "---------------"                           << endl;

  cout << setw(50) << left << "bin";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	cout  << setw(100) << right <<  Form(" %s ", channel.at(binind).c_str() );
  }
  cout << endl;

  cout << setw(50) << left << "observation";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	cout << setw(100) << right << Form(" %.0f", val_data.at(binind)      );
  }
  cout << setw(50) << endl << left << "---------------" << endl;

  cout << setw(50) << endl << left <<  "bin";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	cout << setw(25) << right << Form("%s",channel.at(binind).c_str());
	cout << setw(25) << right << Form("%s",channel.at(binind).c_str());
	cout << setw(25) << right << Form("%s",channel.at(binind).c_str());
	cout << setw(25) << right << Form("%s",channel.at(binind).c_str());
  }

  cout << endl << setw(50) << left << "process";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	cout << setw(25) << right << "sig";
	cout << setw(25) << right << "zjets";
	cout << setw(25) << right << "fsbkg";
	cout << setw(25) << right << "mcbkg";
  }
  cout << endl; 

  cout << setw(50) << left << "process";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	cout << setw(25) << right << "0";
	cout << setw(25) << right << "1";
	cout << setw(25) << right << "2";
	cout << setw(25) << right << "3";
  }

  cout << endl << setw(50) << left << "rate";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	cout << setw(25) << right << Form("%2.1f",val_sig);
	cout << setw(25) << right << Form("%2.1f",val_zjets.at(binind));
	cout << setw(25) << right << Form("%2.6f",Rsfof*(float)((int)(val_fsbkg.at(binind)/(Rsfof-0.01))));
	cout << setw(25) << right << Form("%2.1f",val_mcbkg.at(binind));
  }
  cout << endl;
  cout << setw(50) << left <<  "---------------" << endl;
 
  // ---- sig systs
  cout << setw(40) << left << "sig_syst";
  cout << setw(10) << left << "lnN";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	cout << setw(25) << right <<  Form("%.3f",1 + (err_sig*val_sig)/val_sig);   
	cout << setw(25) << right <<  "-";
	cout << setw(25) << right <<  "-";
	cout << setw(25) << right <<  "-";
  }
  cout << endl;

  // correlated systematic uncertainty on Rsfof
  cout << setw(40) << left << "fsbkg_rsfof_syst";
  cout << setw(10) << left << "lnN";
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	cout << setw(25) << right << "-";
	cout << setw(25) << right << "-";
	cout << setw(25) << right <<  Form("%.3f", 1.038);   
	cout << setw(25) << right << "-";
  }
  cout << endl;

  
  // // correlated systematic uncertainty on MC backgrounds
  // cout << setw(40) << left << "mcbkg_syst";
  // cout << setw(10) << left << "lnN";
  // for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	
  // 	cout << setw(25) << right << "-";
  // 	cout << setw(25) << right << "-";
  // 	cout << setw(25) << right << "-";
  // 	cout << setw(25) << right <<  Form("%.3f",1.50);
  // }
  // cout << endl;

  // partially correlated systematic uncertainty on template normalization
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	string zjets_norm_syst = "";
	if( TString(channel.at(binind)).Contains("bveto_SRA") )zjets_norm_syst  = "zjets_norm_syst_bveto_SRA";
	if( TString(channel.at(binind)).Contains("withb_SRA") )zjets_norm_syst  = "zjets_norm_syst_withb_SRA";
	if( TString(channel.at(binind)).Contains("bveto_SRB") )zjets_norm_syst  = "zjets_norm_syst_bveto_SRB";
	if( TString(channel.at(binind)).Contains("withb_SRB") )zjets_norm_syst  = "zjets_norm_syst_withb_SRB";
	cout << setw(40) << left << zjets_norm_syst;
	cout << setw(10) << left << "lnN";
	for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	
	  if( binindemb == binind ){
		cout << setw(25) << right <<  "-";
		if( TString(channel.at(binindemb)).Contains("bveto_SRA") )cout << setw(25) << right << "1.04";
		if( TString(channel.at(binindemb)).Contains("withb_SRA") )cout << setw(25) << right << "1.10";
		if( TString(channel.at(binindemb)).Contains("bveto_SRB") )cout << setw(25) << right << "1.03";
		if( TString(channel.at(binindemb)).Contains("withb_SRB") )cout << setw(25) << right << "1.06";
		cout << setw(25) << right <<  "-";
		cout << setw(25) << right <<  "-";
	  }else{
		cout << setw(25) << right << "-";
		cout << setw(25) << right << "-";
		cout << setw(25) << right << "-";
		cout << setw(25) << right << "-";   
	  }
	}
	cout << endl;
  }

  // uncorrelated systematic uncertainty on templates from closure test
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	cout << setw(40) << left << "zjets_clos_syst_"+channel.at(binind);
	cout << setw(10) << left << "lnN";
	for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	
	  if( binindemb == binind ){
		cout << setw(25) << right <<  "-";
		cout << setw(25) << right << Form("%.2f", err_zjets_closure.at(binindemb));
		cout << setw(25) << right <<  "-";
		cout << setw(25) << right <<  "-";
	  }else{
		cout << setw(25) << right << "-";
		cout << setw(25) << right << "-";
		cout << setw(25) << right << "-";
		cout << setw(25) << right << "-";   
	  }
	}
	cout << endl;
  }

  // statistical uncertainty on FSbkg
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
	cout << setw(40) << left << "fsbkg_stat_syst_"+channel.at(binind);
	cout << setw(10) << left << Form("gmN %d", (int)(val_fsbkg.at(binind)/(Rsfof-0.01)) );
	for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	

	  if( binindemb == binind ){
		cout << setw(25) << right << "-";
		cout << setw(25) << right << "-";
		cout << setw(25) << right <<  Form("%.3f", Rsfof);   
		cout << setw(25) << right << "-";
	  }else{
		cout << setw(25) << right << "-";
		cout << setw(25) << right << "-";
		cout << setw(25) << right << "-";
		cout << setw(25) << right << "-";   
	  }
	}
	cout << endl;
  }

  // uncorrelated systematic uncertainty on MC backgrounds
  for( size_t binind = 0; binind < channel.size(); binind++ ){	
  	cout << setw(40) << left << "mcbkg_syst_"+channel.at(binind);
  	cout << setw(10) << left << "lnN";
  	for( size_t binindemb = 0; binindemb < channel.size(); binindemb++ ){	
  	  if( binindemb == binind ){
  		cout << setw(25) << right << "-";   
  		cout << setw(25) << right << "-";   
  		cout << setw(25) << right << "-";   
  		cout << setw(25) << right <<  Form("%.3f",1 + err_mcbkg.at(binindemb)/val_mcbkg.at(binindemb));   
  	  }else{
  		cout << setw(25) << right << "-";   
  		cout << setw(25) << right << "-";   
  		cout << setw(25) << right << "-";   
  		cout << setw(25) << right << "-";   
  	  }
  	}
  	cout << endl;
  }

  // fout.close();
  
  return;
}
