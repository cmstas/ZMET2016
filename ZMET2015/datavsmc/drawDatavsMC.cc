#include "TH1F.h"
#include "TFile.h"
#include "TLine.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPad.h"
#include "TLatex.h"
#include "THStack.h"
#include "TStyle.h"

#include "RooHistError.h"
#include "TGraphAsymmErrors.h"

#include <iostream>

#include "../sharedCode/histTools.cc"

using namespace std;
void drawDatavsMC( std::string iter = "", float luminosity = 1.0, const string selection = "_inclusive", string dilep = "ll", string variable = "mll", string region = "passtrig" )
{

  float RSFOF = 1.06;
  // float RSFOF = 1.026;
  double RSFOFunc = .06;

  bool drawsignal = false;

  bool showmoredigits   = true;

  bool binningfortables = true;
  bool drawassymuncs    = true;
  bool usetemplates     = true;
  bool usefsbkg         = true;
  bool applysysts       = true;
  bool showunc_main     = true;
  bool showunc_rati     = true;
  bool uservariablebins = true;  // use signal region binning for met plots
  bool combineMCbgs     = true; // 

  bool usemgzjets       = false;  // use madgraph zjets sample
  bool renormalizettbar = false;  // ttbar has too many events

  
  bool normalized       = false;  // normalize backgrounds to data

  bool fractionalBG     = false;  // display background numbers as fraction in zjets and fsbkg
  bool useedgepreds   = false; // combine z bgs and fs bgs into 2 categories
  bool isblind        = false;
  bool printyields    = true;

  bool useedgeplots   = false; // combine z bgs and fs bgs into 2 categories

  TH1F * h_data  = NULL;
  TH1F * h_zjets = NULL;
  TH1F * h_ttbar = NULL;
  TH1F * h_wz    = NULL;
  TH1F * h_ww    = NULL;
  TH1F * h_zz    = NULL;
  TH1F * h_st    = NULL;
  TH1F * h_vvv   = NULL;
  TH1F * h_ttv   = NULL;
  TH1F * h_signal1 = NULL;

  TGraphAsymmErrors * gr;
  TGraphAsymmErrors * r_gr;
  TGraphAsymmErrors * r_gr_central;
	  
  // TH1F * h_fsbkg = NULL;
  // TH1F * h_other = NULL;
  // TH1F * h_vvbkg = NULL;

  // string variable = "mll";
  // string dilep = "ll";
  
  getBackground(   h_data, iter, Form("data%s" , selection.c_str() ), variable, dilep, region );
  if( drawsignal ) getBackground( h_signal1  , iter, Form("signal1100200%s"  , selection.c_str() ), variable, dilep, region );


  if( usefsbkg ){
	// getBackground(  h_ttbar, iter, Form("data%s", selection.c_str() ),    "metgt1jet", "em", "inclusive" );
	getBackground(  h_ttbar, iter, Form("data%s", selection.c_str() ),    variable, "em", "passtrig" );
  }
  else	getBackground(  h_ttbar, iter, Form("ttbar%s", selection.c_str() ), variable, dilep, region );

  getBackground(                 h_st   , iter, Form("zjets%s"   , selection.c_str() ), variable, dilep, region );
  getBackground(                 h_ww   , iter, Form("zjets%s"   , selection.c_str() ), variable, dilep, region );
  getBackground(                 h_ttv  , iter, Form("zjets%s"  , selection.c_str() ), variable, dilep, region );
  getBackground(                 h_vvv  , iter, Form("zjets%s"  , selection.c_str() ), variable, dilep, region );

  if( usetemplates ){
	getTemplateMET( h_zjets, iter, Form("data%s", selection.c_str() ) );
	getBackground(  h_wz   , iter, Form("zjets%s"   , selection.c_str() ), variable, dilep, region );
	getBackground(  h_zz   , iter, Form("zjets%s"   , selection.c_str() ), variable, dilep, region );
  }
  else{
	if( usemgzjets ){
	  getBackground(  h_zjets, iter, Form("zjetsmlm%s" , selection.c_str() ), variable, dilep, region );
	}else{
	  getBackground(  h_zjets, iter, Form("zjets%s" , selection.c_str() ), variable, dilep, region );
	}
	getBackground(  h_wz   , iter, Form("zjets%s", selection.c_str() ), variable, dilep, region );
	getBackground(  h_zz   , iter, Form("zjets%s", selection.c_str() ), variable, dilep, region );
  }
  
  if( isblind ){
	if( TString(selection).Contains("SR_ATLAS") ){
	  for( int binind = 0; binind < h_data -> GetNbinsX()+1; binind++ ){
		if( binind >= h_data->FindBin(225) ) h_data -> SetBinContent( binind, 0 );
		if( binind >= h_data->FindBin(225) ) h_data -> SetBinError( binind, 0 );
	  }
	}
	else if( TString(selection).Contains("twojets") && !TString(selection).Contains("3jets") ){
	  for( int binind = 0; binind < h_data -> GetNbinsX()+1; binind++ ){
		if( binind >= h_data->FindBin(150) ) h_data -> SetBinContent( binind, 0 );
		if( binind >= h_data->FindBin(150) ) h_data -> SetBinError( binind, 0 );
	  }
	}
	else{	  
	  for( int binind = 0; binind < h_data -> GetNbinsX()+1; binind++ ){
		if( binind >= h_data->FindBin(100) ) h_data -> SetBinContent( binind, 0 );
		if( binind >= h_data->FindBin(100) ) h_data -> SetBinError( binind, 0 );
	  }
	}
  }
  
  // h_st ->Scale(luminosity);
  // h_ww ->Scale(luminosity);
  // h_wz ->Scale(luminosity);
  // h_zz ->Scale(luminosity);
  // h_ttv->Scale(luminosity);
  // h_vvv->Scale(luminosity);

  if( renormalizettbar ){

	h_ttbar->Scale(71.542);  
	h_st ->Scale(0);
	h_ww ->Scale(0);
	h_wz ->Scale(0);
	h_zz ->Scale(0);
	h_ttv->Scale(0);
	h_vvv->Scale(0);
  }

  double renorm_unc = 0.0;
  
  if( usetemplates ){
  
	if( TString(selection).Contains("central"      ) ){
	  h_ttbar->Scale(1.014);
	}
	if( TString(selection).Contains("forward"      ) ){
	  h_ttbar->Scale(1.049);
	}
	if( TString(selection).Contains("SR"      ) || TString(selection).Contains("2jets_inclusive" ) ){
	  if(      dilep == "ee" ) h_ttbar->Scale(0.44);
	  else if( dilep == "mm" ) h_ttbar->Scale(0.586);
	  else                     h_ttbar->Scale(RSFOF);
	}
	// h_zjets->Scale(1./h_zjets->GetSumOfWeights());

	float normmethigh = 50;
	
	float val_data  = h_data  -> Integral(1,normmethigh);
	float val_ttbar = h_ttbar -> Integral(1,normmethigh);
	float val_zjets = h_zjets -> Integral(1,normmethigh);
	val_ttbar += h_wz  -> Integral(1,normmethigh);
	val_ttbar += h_zz  -> Integral(1,normmethigh);
	val_ttbar += h_ttv -> Integral(1,normmethigh);
	val_ttbar += h_vvv -> Integral(1,normmethigh);

	// cout<<"data:  "<<val_data<<endl;
	// cout<<"zjets: "<<val_zjets<<endl;
	// cout<<"ttbar: "<<val_ttbar<<endl;
  
	float scaleval = ((val_data-val_ttbar)/(val_zjets));
	h_zjets->Scale(scaleval);

	cout<<"Scaling template prediction by: "<<scaleval<<endl;

	double err_data = 0.0;
	double err_zjet = 0.0;
	
	val_data  = h_data  -> IntegralAndError(1,normmethigh, err_data);
	// val_ttbar = h_ttbar -> Integral(1,normmethigh);
	val_zjets = h_zjets -> IntegralAndError(1,normmethigh, err_zjet);

	// cout<<"data:  "<<val_data<<endl;
	// cout<<"zjets: "<<val_zjets<<endl;
	// cout<<"ttbar: "<<val_ttbar<<endl;
	
	renorm_unc = err_mult( val_data, val_zjets, err_data, err_zjet, val_data/val_zjets);
	
	cout<<"renorm_unc: "<<renorm_unc<<endl;
	
  }
  else{
	h_zjets->Scale(luminosity);
	if( !usefsbkg ) h_ttbar->Scale(luminosity);
  }
  
  vector <float> metcut;

  vector <double> val_data;
  vector <double> err_data;

  vector <double> val_zjets;
  vector <double> err_zjets;

  vector <double> val_fsbkg;
  vector <double> err_fsbkg;

  vector <double> val_ttvbg;
  vector <double> err_ttvbg;

  vector <double> val_vvvbg;
  vector <double> err_vvvbg;

  vector <double> val_zzbkg;
  vector <double> err_zzbkg;

  vector <double> val_vvbkg;
  vector <double> err_vvbkg;

  vector <double> val_allbg;
  vector <double> err_allbg;

  vector <double> val_signal;
  vector <double> err_signal;

  vector <double> val_ratio;
  vector <double> err_ratio;

  vector <double> err_fsbkg_up;
  vector <double> err_allbg_up;
  vector <double> err_ratio_up;
  vector <double> err_fsbkg_dn;
  vector <double> err_allbg_dn;
  vector <double> err_ratio_dn;


	
  if( printyields ){
  
	//MAKE TABLES
	if( variable == "mll" ){
	  metcut.clear();
	  // metcut.push_back(20);
	  // metcut.push_back(70);
	  metcut.push_back(81);
	  metcut.push_back(101);
	  // metcut.push_back(120);
	  // metcut.push_back(165);
	  // metcut.push_back(185);
	  metcut.push_back(-1);
	}
	
	else if( variable == "mll_fkw" ){
	  metcut.clear();
	  // metcut.push_back(20);
	  // metcut.push_back(70);
	  metcut.push_back(81);
	  metcut.push_back(101);
	  // metcut.push_back(120);
	  // metcut.push_back(165);
	  // metcut.push_back(185);
	  // metcut.push_back(-1);
	}
	
	else if( variable == "njets" || TString(variable).Contains("njt") ){
	  metcut.clear();
	  metcut.push_back(0);
	  // metcut.push_back(1);
	  // metcut.push_back(2);
	  // metcut.push_back(3);
	  // metcut.push_back(4);
	  metcut.push_back(-1);
	}
	
	else if( TString(selection).Contains("CR") && (variable == "met" || variable == "metall") ){
	  metcut.clear();
	  metcut.push_back(0);
	  metcut.push_back(-1);

	  if( TString(selection).Contains("CR3") && variable == "metall" ){
		metcut.clear();
		metcut.push_back(0);
		metcut.push_back(50);
		metcut.push_back(100);
		metcut.push_back(150);
		metcut.push_back(-1);
	  }

	  if( TString(selection).Contains("CR4") && variable == "metall" ){
		metcut.clear();
		metcut.push_back(0);
		metcut.push_back(10);
		metcut.push_back(20);
		metcut.push_back(30);
		metcut.push_back(40);
		metcut.push_back(-1);
	  }
	  
	}else{

	  if( TString(selection).Contains("twojets"      ) ){
		useedgepreds = true;
		metcut.clear();
		metcut.push_back(0.0);
		if( !binningfortables ) metcut.push_back(25);
		metcut.push_back(50);
		if( !binningfortables ) metcut.push_back(75);
		metcut.push_back(100);
		metcut.push_back(150);
		metcut.push_back(-1);

	  }
	  else if( TString(selection).Contains("inclusive_central"      ) ){
		useedgepreds = true;
		metcut.clear();
		metcut.push_back(0.0);
		if( !binningfortables ) metcut.push_back(25);
		metcut.push_back(50);
		if( !binningfortables ) metcut.push_back(75);
		metcut.push_back(100);
		metcut.push_back(150);
		metcut.push_back(-1);

	  }
	  else if( TString(selection).Contains("SR_ATLAS"      ) ){
		// useedgepreds = false;
		// combineMCbgs = true;
		metcut.clear();
		metcut.push_back(0.0);
		if( !binningfortables ) metcut.push_back(25);
		metcut.push_back(50);
		if( !binningfortables ) metcut.push_back(75);
		metcut.push_back(100);
		metcut.push_back(150);
		metcut.push_back(225);
		metcut.push_back(-1);

	  }
	  else{
		// useedgepreds = false;
		// combineMCbgs = true;
		metcut.clear();
		metcut.push_back(0.0);
		if( !binningfortables ) metcut.push_back(25);
		metcut.push_back(50);
		if( !binningfortables ) metcut.push_back(75);
		metcut.push_back(100);
		metcut.push_back(150);
		metcut.push_back(225);
		metcut.push_back(300);
		metcut.push_back(-1);

	  }

	  if( TString(selection).Contains("2jets_inclusive") ){
	  	useedgepreds = true;
	  	metcut.clear();
	  	metcut.push_back(0.0);
	  	if( !binningfortables ) metcut.push_back(25);
	  	metcut.push_back(50);
	  	if( !binningfortables ) metcut.push_back(75);
	  	metcut.push_back(100);
	  	metcut.push_back(150);
	  	// metcut.push_back(225);
	  	// metcut.push_back(300);
	  	metcut.push_back(-1);
	  }

	}
    
	for( size_t i = 0; i < metcut.size(); i++ ){
	  val_data.push_back(0);
	  err_data.push_back(0);
	  val_signal.push_back(0);
	  err_signal.push_back(0);
	  val_zjets.push_back(0);
	  err_zjets.push_back(0);
	  val_fsbkg.push_back(0);
	  err_fsbkg.push_back(0);
	  val_ttvbg.push_back(0);
	  err_ttvbg.push_back(0);
	  val_vvvbg.push_back(0);
	  err_vvvbg.push_back(0);
	  val_zzbkg.push_back(0);
	  err_zzbkg.push_back(0);
	  val_vvbkg.push_back(0);
	  err_vvbkg.push_back(0);
	  val_allbg.push_back(0);
	  err_allbg.push_back(0);
	  val_ratio.push_back(0);
	  err_ratio.push_back(0);

	  err_fsbkg_up.push_back(0);
	  err_allbg_up.push_back(0);
	  err_ratio_up.push_back(0);
	  err_fsbkg_dn.push_back(0);
	  err_allbg_dn.push_back(0);
	  err_ratio_dn.push_back(0);

	}


	const Int_t n = metcut.size()-1;;
	Double_t x[n], y[n], exl[n], eyl[n], exh[n], eyh[n];
	Double_t r_x[n], r_y[n], r_exl[n], r_eyl[n], r_exh[n], r_eyh[n];
	Double_t rc_x[n], rc_y[n], rc_exl[n], rc_eyl[n], rc_exh[n], rc_eyh[n];

	
	for( size_t bini = 0; bini < metcut.size()-1; bini++ ){

	  float zsyst = 0;
	  if( bini < metcut.size()-1 ){
		// cout<<"getting yields for: "<<metcut.at(bini)<<" | "<< metcut.at(bini+1)-1<<endl;
		// cout<<"getting yields for: "<<h_data ->FindBin(metcut.at(bini))<<" | "<< h_data ->FindBin(metcut.at(bini+1)-1)<<endl;
		val_data .at(bini) = h_data ->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_data .at(bini));
		if( drawsignal ) val_signal.at(bini)= h_signal1->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_signal .at(bini));
		val_zjets.at(bini) = h_zjets->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_zjets.at(bini));
		val_fsbkg.at(bini) = h_ttbar->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_fsbkg.at(bini));
		val_ttvbg.at(bini) = h_ttv  ->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_ttvbg.at(bini));
		val_vvvbg.at(bini) = h_vvv  ->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_vvvbg.at(bini));
		val_vvbkg.at(bini) = h_wz   ->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_vvbkg.at(bini));
		val_zzbkg.at(bini) = h_zz   ->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_zzbkg.at(bini));

		// if( isblind && metcut.at(bini) >= 100 ){
		//   val_data .at(bini) = 0;
		//   err_data .at(bini) = 0;
		// }
		
		if(       metcut.at(bini+1)   < 0   ){  
		  if( TString(selection).Contains("bveto_SRA"            ) )zsyst = 0.20;
		  if( TString(selection).Contains("withb_SRA"            ) )zsyst = 0.35;
		  if( TString(selection).Contains("bveto_SRB"            ) )zsyst = 0.30;
		  if( TString(selection).Contains("withb_SRB"            ) )zsyst = 0.35;
		  if( TString(selection).Contains("SR_ATLAS"             ) )zsyst = 0.20;
		  if( TString(selection).Contains("SR_EWK"               ) )zsyst = 0.15;
		  if( TString(selection).Contains("2jets_inclusive"      ) )zsyst = 0.05;

		}else if( metcut.at(bini+1)-1 < 50  ){  
		  if( TString(selection).Contains("bveto_SRA"            ) )zsyst = 0.01;
		  if( TString(selection).Contains("withb_SRA"            ) )zsyst = 0.01;
		  if( TString(selection).Contains("bveto_SRB"            ) )zsyst = 0.01;
		  if( TString(selection).Contains("withb_SRB"            ) )zsyst = 0.01;
		  if( TString(selection).Contains("SR_ATLAS"             ) )zsyst = 0.01;
		  if( TString(selection).Contains("SR_EWK"               ) )zsyst = 0.20;
		  if( TString(selection).Contains("2jets_inclusive"      ) )zsyst = 0.01;

		}else if( metcut.at(bini+1)-1 < 100 ){
		  if( TString(selection).Contains("bveto_SRA"            ) )zsyst = 0.05;
		  if( TString(selection).Contains("withb_SRA"            ) )zsyst = 0.05;
		  if( TString(selection).Contains("bveto_SRB"            ) )zsyst = 0.05;
		  if( TString(selection).Contains("withb_SRB"            ) )zsyst = 0.03;
		  if( TString(selection).Contains("SR_ATLAS"             ) )zsyst = 0.10;
		  if( TString(selection).Contains("SR_EWK"               ) )zsyst = 0.02;
		  if( TString(selection).Contains("2jets_inclusive"      ) )zsyst = 0.01;

		}else if( metcut.at(bini+1)-1 < 150 ){
		  if( TString(selection).Contains("bveto_SRA"            ) )zsyst = 0.15;
		  if( TString(selection).Contains("withb_SRA"            ) )zsyst = 0.10;
		  if( TString(selection).Contains("bveto_SRB"            ) )zsyst = 0.15;
		  if( TString(selection).Contains("withb_SRB"            ) )zsyst = 0.15;
		  if( TString(selection).Contains("SR_ATLAS"             ) )zsyst = 0.10;
		  if( TString(selection).Contains("SR_EWK"               ) )zsyst = 0.15;
		  if( TString(selection).Contains("2jets_inclusive"      ) )zsyst = 0.02;

		}else if( metcut.at(bini+1)-1 < 225 ){ 
		  if( TString(selection).Contains("bveto_SRA"            ) )zsyst = 0.15;
		  if( TString(selection).Contains("withb_SRA"            ) )zsyst = 0.10;
		  if( TString(selection).Contains("bveto_SRB"            ) )zsyst = 0.20;
		  if( TString(selection).Contains("withb_SRB"            ) )zsyst = 0.15;
		  if( TString(selection).Contains("SR_ATLAS"             ) )zsyst = 0.10;
		  if( TString(selection).Contains("SR_EWK"               ) )zsyst = 0.15;
		  if( TString(selection).Contains("2jets_inclusive"      ) )zsyst = 0.05;

		}else if( metcut.at(bini+1)-1 < 300 ){
		  if( TString(selection).Contains("bveto_SRA"            ) )zsyst = 0.15;
		  if( TString(selection).Contains("withb_SRA"            ) )zsyst = 0.30;
		  if( TString(selection).Contains("bveto_SRB"            ) )zsyst = 0.30;
		  if( TString(selection).Contains("withb_SRB"            ) )zsyst = 0.25;
		  if( TString(selection).Contains("SR_ATLAS"             ) )zsyst = 0.25;
		  if( TString(selection).Contains("SR_EWK"               ) )zsyst = 0.15;
		  if( TString(selection).Contains("2jets_inclusive"      ) )zsyst = 0.05;

		}

		// cout<<"zsyts for: "<<metcut.at(bini+1)<<" | "<< zsyst<<endl;
	  
		
	  }

	  if( bini == metcut.size()-1 ){
		val_data .at(bini) = h_data ->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_data .at(bini));
		if( drawsignal ) val_signal.at(bini)= h_signal1->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_signal .at(bini));
		val_zjets.at(bini) = h_zjets->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_zjets.at(bini));
		val_fsbkg.at(bini) = h_ttbar->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_fsbkg.at(bini));
		val_ttvbg.at(bini) = h_ttv  ->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_ttvbg.at(bini));
		val_vvvbg.at(bini) = h_vvv  ->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_vvvbg.at(bini));
		val_vvbkg.at(bini) = h_wz   ->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_vvbkg.at(bini));
		val_zzbkg.at(bini) = h_zz   ->IntegralAndError( metcut.at(bini)+1, metcut.at(bini+1), err_zzbkg.at(bini));
	  }

	  val_vvbkg.at(bini) += val_zzbkg.at(bini);
	  err_vvbkg.at(bini) = sqrt( pow(err_zzbkg.at(bini),2) + pow(err_vvbkg.at(bini),2));

	  if( drawassymuncs ){
		//recalculate uncs for low stats bins
		double yield_up, yield_dn;

		int eventcount = val_fsbkg.at(bini)/(RSFOF-0.01);

		// cout<<"ctrval: "<<val_fsbkg.at(bini)<<endl;
		// cout<<"count : "<<eventcount<<endl;
		
		RooHistError::instance().getPoissonInterval(eventcount,yield_dn,yield_up,1.);

		// cout<<"yieldup/yielddn: "<<yield_up<<" | "<<yield_dn<<endl;

		yield_up *= RSFOF;
		yield_dn *= RSFOF;
           
		double statUp = yield_up-val_fsbkg.at(bini);
		double statDn = val_fsbkg.at(bini)-yield_dn;

		// cout<<"yieldup/yielddn: "<<yield_up<<" | "<<yield_dn<<endl;
		// cout<<"FS pred        : "<<val_fsbkg.at(bini)<<" | "<<err_fsbkg.at(bini)<<endl;
		// cout<<"errup/errDn    : "<<statUp<<" | "<<statDn<<endl;

		if( drawassymuncs ){

		  if( applysysts ){
			err_fsbkg_up.at(bini) = (sqrt( pow(statUp, 2 ) + pow( val_fsbkg.at(bini)*RSFOFunc, 2 ) ));
			err_fsbkg_dn.at(bini) = (sqrt( pow(statDn, 2 ) + pow( val_fsbkg.at(bini)*RSFOFunc, 2 ) ));

		  }
		  else{
			err_fsbkg_up.at(bini) = statUp;
			err_fsbkg_dn.at(bini) = statDn;

		  }

		}
	  
	  }
	  
	  if( applysysts ){
		err_zjets.at(bini) = sqrt( pow( err_zjets.at(bini), 2 ) + pow( val_zjets.at(bini)*zsyst, 2 ) + pow( val_zjets.at(bini)*renorm_unc, 2 ) );

		if( TString(selection).Contains("SR" ) || TString(selection).Contains("2jets_inclusive" ) ){
		  err_fsbkg.at(bini) = sqrt( pow( err_fsbkg.at(bini), 2 ) + pow( val_fsbkg.at(bini)*.05, 2 ) );
		}
		  
		err_ttvbg.at(bini) = sqrt( pow( err_ttvbg.at(bini), 2 ) + pow( val_ttvbg.at(bini)*.50, 2 ) );
		err_vvvbg.at(bini) = sqrt( pow( err_vvvbg.at(bini), 2 ) + pow( val_vvvbg.at(bini)*.50, 2 ) );
		err_vvbkg.at(bini) = sqrt( pow( err_vvbkg.at(bini), 2 ) + pow( val_vvbkg.at(bini)*.50, 2 ) );
	  }
	  

	}

	
	// float norm_factor = (val_data.at(0) -
	// 					   val_fsbkg.at(0)
	// 					   // - val_vvbkg.at(0)
	// 					   // - val_other.at(0))
	// 					   )/(val_zjets.at(0));
	// for( size_t bini = 0; bini < metcut.size(); bini++ ){
	// 	val_zjets.at(bini) *= norm_factor;
	// 	err_zjets.at(bini) *= norm_factor;
	// }
  
	for( size_t bini = 0; bini < metcut.size(); bini++ ){
	  if( val_zjets.at(bini) < 0 ) val_zjets.at(bini) = 0.0;
	  
	  val_allbg.at(bini) =
		val_zjets.at(bini) +
		val_fsbkg.at(bini) +
		val_ttvbg.at(bini) +
		val_vvvbg.at(bini) +
		val_vvbkg.at(bini)
		;
	
	  if( drawassymuncs ){

		err_allbg_up.at(bini) = sqrt( pow(err_zjets.at(bini), 2) +
									  pow(err_fsbkg_up.at(bini), 2) +
									  pow(err_ttvbg.at(bini), 2) +
									  pow(err_vvvbg.at(bini), 2) +
									  pow(err_vvbkg.at(bini), 2)
									  );
		err_ratio_up.at(bini) = err_mult( val_data .at(bini), val_allbg.at(bini),
										  err_data .at(bini), err_allbg_up.at(bini), val_data .at(bini)/val_allbg.at(bini));
		err_allbg_dn.at(bini) = sqrt( pow(err_zjets.at(bini), 2) +
									  pow(err_fsbkg_dn.at(bini), 2) +
									  pow(err_ttvbg.at(bini), 2) +
									  pow(err_vvvbg.at(bini), 2) +
									  pow(err_vvbkg.at(bini), 2)
									  );
		err_ratio_dn.at(bini) = err_mult( val_data .at(bini), val_allbg.at(bini),
										  err_data .at(bini), err_allbg_dn.at(bini), val_data .at(bini)/val_allbg.at(bini));
	  
		if( bini < metcut.size()-1 ){		
		  // for main plot
		  y[bini]   = val_allbg.at(bini);
		  eyl[bini] = err_allbg_dn.at(bini);
		  eyh[bini] = err_allbg_up.at(bini);
		  if( bini == metcut.size()-2 ){

			if( TString(selection).Contains("SR") || TString(selection).Contains("2jets_inclusive" ) ){
			  x[bini] = metcut.at(bini) + 0.5*(350-metcut.at(bini));
			  y[bini] *= 25/(350-metcut.at(bini));
			  eyl[bini] *= 25/(350-metcut.at(bini));
			  eyh[bini] *= 25/(350-metcut.at(bini));
			}
			exl[bini] = 0.5*(350-metcut.at(bini));
			exh[bini] = 0.5*(350-metcut.at(bini));

		  }else{
			x[bini] = metcut.at(bini) + 0.5*(metcut.at(bini+1)-metcut.at(bini));
			y[bini] *= 25/(metcut.at(bini+1)-metcut.at(bini));
			eyl[bini] *= 25/(metcut.at(bini+1)-metcut.at(bini));
			eyh[bini] *= 25/(metcut.at(bini+1)-metcut.at(bini));
			exl[bini] = 0.5*(metcut.at(bini+1)-metcut.at(bini));
			exh[bini] = 0.5*(metcut.at(bini+1)-metcut.at(bini));
		  }

		  // for ratio plot
		  r_y[bini]   = 1.0;
		  r_eyl[bini] = err_allbg_dn.at(bini)/val_allbg.at(bini);
		  r_eyh[bini] = err_allbg_up.at(bini)/val_allbg.at(bini);
		  if( bini == metcut.size()-2 ){

			if( TString(selection).Contains("SR") || TString(selection).Contains("2jets_inclusive" ) ){
			  r_x[bini] = metcut.at(bini) + 0.5*(350-metcut.at(bini));
			}
			r_exl[bini] = 0.5*(350-metcut.at(bini));
			r_exh[bini] = 0.5*(350-metcut.at(bini));

		  }else{
			r_x[bini] = metcut.at(bini) + 0.5*(metcut.at(bini+1)-metcut.at(bini));
			r_exl[bini] = 0.5*(metcut.at(bini+1)-metcut.at(bini));
			r_exh[bini] = 0.5*(metcut.at(bini+1)-metcut.at(bini));
		  }

		  // for ratio plot of data/MC
		  rc_y[bini]   = val_data.at(bini)/val_allbg.at(bini);
		  rc_eyl[bini] = err_data.at(bini)/val_data.at(bini);
		  rc_eyh[bini] = err_data.at(bini)/val_data.at(bini);
		  // rc_eyl[bini] = err_ratio_dn.at(bini);
		  // rc_eyh[bini] = err_ratio_up.at(bini);
		  if( bini == metcut.size()-2 ){

			if( TString(selection).Contains("SR") || TString(selection).Contains("2jets_inclusive" ) ){
			  rc_x[bini] = metcut.at(bini) + 0.5*(350-metcut.at(bini));
			}
			// rc_exl[bini] = 0.5*(350-metcut.at(bini));
			// rc_exh[bini] = 0.5*(350-metcut.at(bini));
			rc_exl[bini] = 0.0;
			rc_exh[bini] = 0.0;

		  }else{
			rc_x[bini] = metcut.at(bini) + 0.5*(metcut.at(bini+1)-metcut.at(bini));
			// rc_exl[bini] = 0.5*(metcut.at(bini+1)-metcut.at(bini));
			// rc_exh[bini] = 0.5*(metcut.at(bini+1)-metcut.at(bini));
			rc_exl[bini] = 0.0;
			rc_exh[bini] = 0.0;
		  }

		  // cout<<rc_y[bini]<<" | "<<rc_x[bini]<<endl;
		  
		}
		
	  }
	  
	  err_allbg.at(bini) = sqrt( pow(err_zjets.at(bini), 2) +
								 pow(err_fsbkg.at(bini), 2) +
								 pow(err_ttvbg.at(bini), 2) +
								 pow(err_vvvbg.at(bini), 2) +
								 pow(err_vvbkg.at(bini), 2)
								 );
	  val_ratio.at(bini) = val_data .at(bini)/val_allbg.at(bini);
	  err_ratio.at(bini) = err_mult( val_data .at(bini), val_allbg.at(bini),
									 err_data .at(bini), err_allbg.at(bini), val_data .at(bini)/val_allbg.at(bini));
	}


	if( fractionalBG ) {
	  float tot_data = 0.0;
	  float tot_zjets = 0.0;
	  float tot_fsbkg = 0.0;
	  float tot_ttvbg = 0.0;
	  float tot_vvvbg = 0.0;
	  float tot_zzbkg = 0.0;
	  float tot_allbg = 0.0;

	  for( size_t bini = 0; bini < metcut.size(); bini++ ){
		tot_data  += val_data .at(bini);

		tot_zjets += val_zjets.at(bini);
		tot_zjets += val_zzbkg.at(bini);
		tot_zjets += val_vvbkg.at(bini);

		tot_fsbkg += val_fsbkg.at(bini);
		tot_fsbkg += val_ttvbg.at(bini);
		tot_fsbkg += val_vvvbg.at(bini);
		tot_allbg += val_allbg.at(bini);
	  }

	  for( size_t bini = 0; bini < metcut.size(); bini++ ){
		val_data .at(bini)*=(1.0/tot_data );
		err_data .at(bini)*=(1.0/tot_data );

		val_zjets.at(bini)*=(1.0/tot_zjets);
		err_zjets.at(bini)*=(1.0/tot_zjets);
		val_zzbkg.at(bini)*=(1.0/tot_zjets);
		err_zzbkg.at(bini)*=(1.0/tot_zjets);
		val_vvbkg.at(bini)*=(1.0/tot_zjets);
		err_vvbkg.at(bini)*=(1.0/tot_zjets);

		val_fsbkg.at(bini)*=(1.0/tot_fsbkg);
		err_fsbkg.at(bini)*=(1.0/tot_fsbkg);
		val_ttvbg.at(bini)*=(1.0/tot_fsbkg);
		err_ttvbg.at(bini)*=(1.0/tot_fsbkg);
		val_vvvbg.at(bini)*=(1.0/tot_fsbkg);
		err_vvvbg.at(bini)*=(1.0/tot_fsbkg);
		val_allbg.at(bini)*=(1.0/tot_allbg);
		err_allbg.at(bini)*=(1.0/tot_allbg);
	  }

	}
  
	if( drawassymuncs ){
	  gr = new TGraphAsymmErrors(n,x,y,exl,exh,eyl,eyh);
	  r_gr = new TGraphAsymmErrors(n,r_x,r_y,r_exl,r_exh,r_eyl,r_eyh);
	  r_gr_central = new TGraphAsymmErrors(n,rc_x,rc_y,rc_exl,rc_exh,rc_eyl,rc_eyh);
	}
  
	
	cout<<"$\\mathrm{E_{T}^{miss} [GeV]}$ &";
	for( size_t bini = 0; bini < metcut.size()-2; bini++ ){
	  if( metcut.at(bini) == -1 ) continue;
	  cout<<Form("%.0f - %.0f & ", metcut.at(bini), metcut.at(bini+1) );
	}
	cout<<Form("$\\geq$ %.0f \\\\", metcut.at(metcut.size()-2) );
	cout<<endl;

	cout<<"\\hline "<<endl;
	
	if( useedgepreds ){
	  cout<<"Z background& ";
	  for( size_t bini = 0; bini < val_zjets.size()-1; bini++ ){
		if( metcut.at(bini) == -1 ) continue;
		if( bini < val_zjets.size()-2 ){
		  if( fractionalBG ){
			cout<<Form(" %.3f $\\pm$ %.3f & ", val_zjets.at(bini) + val_vvbkg.at(bini) + val_ttvbg.at(bini) + val_vvvbg.at(bini),
					   sqrt( pow(err_zjets.at(bini),2) + pow(err_vvbkg.at(bini),2) + pow(err_ttvbg.at(bini),2) + pow(err_vvvbg.at(bini),2)));
		  }else{
			cout<<Form(" %.1f $\\pm$ %.1f & ", val_zjets.at(bini) + val_vvbkg.at(bini) + val_ttvbg.at(bini) + val_vvvbg.at(bini),
					   sqrt( pow(err_zjets.at(bini),2) + pow(err_vvbkg.at(bini),2) + pow(err_ttvbg.at(bini),2) + pow(err_vvvbg.at(bini),2)));
		  }
		}

		if( bini == val_zjets.size()-2 ){
		  if( fractionalBG ){
			cout<<Form(" %.3f $\\pm$ %.3f \\\\ ", val_zjets.at(bini) + val_vvbkg.at(bini) + val_ttvbg.at(bini) + val_vvvbg.at(bini),
					   sqrt( pow(err_zjets.at(bini),2) + pow(err_vvbkg.at(bini),2) + pow(err_ttvbg.at(bini),2) + pow(err_vvvbg.at(bini),2)));
		  }else{
			cout<<Form(" %.1f $\\pm$ %.1f \\\\ ", val_zjets.at(bini) + val_vvbkg.at(bini) + val_ttvbg.at(bini) + val_vvvbg.at(bini),
					   sqrt( pow(err_zjets.at(bini),2) + pow(err_vvbkg.at(bini),2) + pow(err_ttvbg.at(bini),2) + pow(err_vvvbg.at(bini),2)));
		  }
		}
	  }
	  cout<<endl;

	}
	else{
	  cout<<"Z+jets& ";
	  for( size_t bini = 0; bini < val_zjets.size()-1; bini++ ){
		if( metcut.at(bini) == -1 ) continue;
		if( bini < val_zjets.size()-2 ){
		  if( fractionalBG ){
			cout<<Form(" %.3f $\\pm$ %.4f & ", val_zjets.at(bini), err_zjets.at(bini));
		  }else{
			if( showmoredigits ){ cout<<Form(" %.2f $\\pm$ %.2f & ", val_zjets.at(bini), err_zjets.at(bini));
			}else               { cout<<Form(" %.1f $\\pm$ %.1f & ", val_zjets.at(bini), err_zjets.at(bini));}
		  }
		}
		if( bini == val_zjets.size()-2 ){
		  if( fractionalBG ){
			cout<<Form(" %.3f $\\pm$ %.4f \\\\ ", val_zjets.at(bini), err_zjets.at(bini));
		  }else{
			if( showmoredigits ){ cout<<Form(" %.2f $\\pm$ %.2f \\\\ ", val_zjets.at(bini), err_zjets.at(bini));
			}else               { cout<<Form(" %.1f $\\pm$ %.1f \\\\ ", val_zjets.at(bini), err_zjets.at(bini));}
		  }
		}
	  }
	  cout<<endl;

	}
	
	cout<<"FS bkg& ";
	for( size_t bini = 0; bini < val_fsbkg.size()-1; bini++ ){
	  if( metcut.at(bini) == -1 ) continue;
	  if( bini < val_fsbkg.size()-2 ){
		if( drawassymuncs ){
		  if( fractionalBG ){
			cout<<Form(" %.4f $\\pm$ %.5f & ", val_fsbkg.at(bini), err_fsbkg.at(bini));
		  }else{
			cout<<Form(" %.1f$^{+ %.1f}_{- %.1f}$ & ", val_fsbkg.at(bini), err_fsbkg_up.at(bini), err_fsbkg_dn.at(bini));
		  }

		}else{
		  if( fractionalBG ){
			cout<<Form(" %.4f $\\pm$ %.5f & ", val_fsbkg.at(bini), err_fsbkg.at(bini));
		  }else{
			cout<<Form(" %.1f $\\pm$ %.1f & ", val_fsbkg.at(bini), err_fsbkg.at(bini));
		  }
		}
		
	  }
	  if( bini == val_fsbkg.size()-2 ){
		if( drawassymuncs ){
		  if( fractionalBG ){
			cout<<Form(" %.4f $\\pm$ %.5f \\\\ ", val_fsbkg.at(bini), err_fsbkg.at(bini));
		  }else{
			cout<<Form(" %.1f$^{+ %.1f}_{- %.1f}$ \\\\ ", val_fsbkg.at(bini), err_fsbkg_up.at(bini), err_fsbkg_dn.at(bini));
		  }
		}else{
		  if( fractionalBG ){
			cout<<Form(" %.4f $\\pm$ %.5f \\\\ ", val_fsbkg.at(bini), err_fsbkg.at(bini));
		  }else{
			cout<<Form(" %.1f $\\pm$ %.1f \\\\ ", val_fsbkg.at(bini), err_fsbkg.at(bini));
		  }
		}
	  }
	}
	cout<<endl;

	if( useedgepreds ){
	  cout<<"\\hline "<<endl;

	}else{
	  
	  if( combineMCbgs ){
		cout<<"Other SM& ";
		for( size_t bini = 0; bini < val_zjets.size()-1; bini++ ){
		  if( metcut.at(bini) == -1 ) continue;
		  if( bini < val_zjets.size()-2 ){
			if( fractionalBG ){
			  cout<<Form(" %.4f $\\pm$ %.5f & ", val_ttvbg.at(bini) + val_vvvbg.at(bini),
						 sqrt( pow(err_ttvbg.at(bini),2) + pow(err_vvvbg.at(bini),2)));
			}else{
			  cout<<Form(" %.1f $\\pm$ %.1f & ", val_ttvbg.at(bini) + val_vvvbg.at(bini) + val_vvbkg.at(bini),
						 sqrt( pow(err_ttvbg.at(bini),2) + pow(err_vvvbg.at(bini),2) + pow(err_vvbkg.at(bini),2)));
			}
		  }
		  if( bini == val_zjets.size()-2 ){
			if( fractionalBG ){
			  cout<<Form(" %.4f $\\pm$ %.5f \\\\ ", val_ttvbg.at(bini) + val_vvvbg.at(bini),
						 sqrt( pow(err_ttvbg.at(bini),2) + pow(err_vvvbg.at(bini),2)));
			}else{
			  cout<<Form(" %.1f $\\pm$ %.1f \\\\ ", val_ttvbg.at(bini) + val_vvvbg.at(bini) + val_vvbkg.at(bini),
						 sqrt( pow(err_ttvbg.at(bini),2) + pow(err_vvvbg.at(bini),2) + pow(err_vvbkg.at(bini),2)));
			}
		  }
		}
		cout<<endl;
	  
	  }else{
		cout<<"WZ + ZZ bkg& ";
		for( size_t bini = 0; bini < val_vvbkg.size()-1; bini++ ){
		  if( metcut.at(bini) == -1 ) continue;
		  if( bini < val_vvbkg.size()-2 ){
			if( fractionalBG ){
			  cout<<Form(" %.4f $\\pm$ %.5f & ", val_vvbkg.at(bini), err_vvbkg.at(bini));
			}else{
			  cout<<Form(" %.1f $\\pm$ %.1f & ", val_vvbkg.at(bini), err_vvbkg.at(bini));
			}
		  }
		  if( bini == val_vvbkg.size()-2 ){
			if( fractionalBG ){
			  cout<<Form(" %.4f $\\pm$ %.5f \\\\ ", val_vvbkg.at(bini), err_vvbkg.at(bini));
			}else{
			  cout<<Form(" %.1f $\\pm$ %.1f \\\\ ", val_vvbkg.at(bini), err_vvbkg.at(bini));
			}
		  }
		}
		cout<<endl;

		cout<<"ttv SM BG& ";
		for( size_t bini = 0; bini < val_ttvbg.size()-1; bini++ ){
		  if( metcut.at(bini) == -1 ) continue;
		  if( bini < val_ttvbg.size()-2 ){
			if( fractionalBG ){
			  cout<<Form(" %.4f $\\pm$ %.5f & ", val_ttvbg.at(bini), err_ttvbg.at(bini));
			}else{
			  cout<<Form(" %.1f $\\pm$ %.1f & ", val_ttvbg.at(bini), err_ttvbg.at(bini));
			}
		  }
		  if( bini == val_ttvbg.size()-2 ){
			if( fractionalBG ){
			  cout<<Form(" %.4f $\\pm$ %.5f \\\\ ", val_ttvbg.at(bini), err_ttvbg.at(bini));
			}else{
			  cout<<Form(" %.1f $\\pm$ %.1f \\\\ ", val_ttvbg.at(bini), err_ttvbg.at(bini));
			}
		  }
		}
		cout<<endl;

		cout<<"vvv SM BG& ";
		for( size_t bini = 0; bini < val_vvvbg.size()-1; bini++ ){
		  if( metcut.at(bini) == -1 ) continue;
		  if( bini < val_vvvbg.size()-2 ){
			if( fractionalBG ){
			  cout<<Form(" %.4f $\\pm$ %.5f & ", val_vvvbg.at(bini), err_vvvbg.at(bini));
			}else{
			  cout<<Form(" %.1f $\\pm$ %.1f & ", val_vvvbg.at(bini), err_vvvbg.at(bini));
			}
		  }
		  if( bini == val_vvvbg.size()-2 ){
			if( fractionalBG ){
			  cout<<Form(" %.4f $\\pm$ %.5f \\\\ ", val_vvvbg.at(bini), err_vvvbg.at(bini));
			}else{
			  cout<<Form(" %.1f $\\pm$ %.1f \\\\ ", val_vvvbg.at(bini), err_vvvbg.at(bini));
			}
		  }
		}
		cout<<endl;
	  }
		
	  cout<<"\\hline "<<endl;

	}
  
  	cout<<"total BG& ";
	for( size_t bini = 0; bini < val_allbg.size()-1; bini++ ){
	  if( metcut.at(bini) == -1 ) continue;
	  if( bini < val_allbg.size()-2 ){
		if( drawassymuncs ){
		  if( fractionalBG ){
			cout<<Form(" %.4f $\\pm$ %.5f & ", val_allbg.at(bini), err_allbg.at(bini));
		  }else{
			cout<<Form(" %.1f$^{+ %.1f}_{- %.1f}$ & ", val_allbg.at(bini), err_allbg_up.at(bini), err_allbg_dn.at(bini));
		  }
		}else{
		  if( fractionalBG ){
			cout<<Form(" %.4f $\\pm$ %.5f & ", val_allbg.at(bini), err_allbg.at(bini));
		  }else{
			cout<<Form(" %.1f $\\pm$ %.1f & ", val_allbg.at(bini), err_allbg.at(bini));
		  }
		}
	  }
	  if( bini == val_allbg.size()-2 ){
		if( drawassymuncs ){
		  if( fractionalBG ){
			cout<<Form(" %.4f $\\pm$ %.5f \\\\ ", val_allbg.at(bini), err_allbg.at(bini));
		  }else{
			cout<<Form(" %.1f$^{+ %.1f}_{- %.1f}$ \\\\ ", val_allbg.at(bini), err_allbg_up.at(bini), err_allbg_dn.at(bini));
		  }
		}else{
		  if( fractionalBG ){
			cout<<Form(" %.4f $\\pm$ %.5f \\\\ ", val_allbg.at(bini), err_allbg.at(bini));
		  }else{
			cout<<Form(" %.1f $\\pm$ %.1f \\\\ ", val_allbg.at(bini), err_allbg.at(bini));
		  }
		}
	  }
	}
	cout<<endl;

	cout<<"\\hline "<<endl;
	cout<<"Data& ";
	for( size_t bini = 0; bini < val_data.size()-1; bini++ ){
	  if( metcut.at(bini) == -1 ) continue;
	  if( bini < val_data.size()-2 ){
		if( fractionalBG ){
		  // cout<<Form(" %.1f $\\pm$ %.1f & ", val_data.at(bini), err_data.at(bini)); // with errors
		  cout<<Form(" %.3f & ", val_data.at(bini));
		}else{
		  // cout<<Form(" %.1f $\\pm$ %.1f & ", val_data.at(bini), err_data.at(bini)); // with errors
		  cout<<Form(" %.0f & ", val_data.at(bini));
		}
	  }
	  if( bini == val_data.size()-2 ){
		if( fractionalBG ){
		  // cout<<Form(" %.1f $\\pm$ %.1f \\\\ ", val_data.at(bini), err_data.at(bini));
		  cout<<Form(" %.3f \\\\ ", val_data.at(bini));
		}else{
		  // cout<<Form(" %.1f $\\pm$ %.1f \\\\ ", val_data.at(bini), err_data.at(bini));
		  cout<<Form(" %.0f \\\\ ", val_data.at(bini));
		}
	  }
	}
	cout<<endl;

	if( drawsignal ){
	  cout<<"\\hline "<<endl;
	  cout<<"Signal& ";
	  for( size_t bini = 0; bini < val_signal.size()-1; bini++ ){
		if( metcut.at(bini) == -1 ) continue;
		if( bini < val_signal.size()-2 ){
		  if( fractionalBG ){
			// cout<<Form(" %.1f $\\pm$ %.1f & ", val_signal.at(bini), err_signal.at(bini)); // with errors
			cout<<Form(" %.3f & ", val_signal.at(bini));
		  }else{
			cout<<Form(" %.2f $\\pm$ %.2f & ", val_signal.at(bini), err_signal.at(bini)); // with errors
		  }
		}
		if( bini == val_signal.size()-2 ){
		  if( fractionalBG ){
			// cout<<Form(" %.1f $\\pm$ %.1f \\\\ ", val_signal.at(bini), err_signal.at(bini));
			cout<<Form(" %.3f \\\\ ", val_signal.at(bini));
		  }else{
			cout<<Form(" %.2f $\\pm$ %.2f \\\\ ", val_signal.at(bini), err_signal.at(bini));
		  }
		}
	  }
	  cout<<endl;
	}
	
	cout<<"\\hline "<<endl;
  
	cout<<"Data/BG& ";
	for( size_t bini = 0; bini < val_ratio.size()-1; bini++ ){
	  if( metcut.at(bini) == -1 ) continue;
	  if( bini < val_ratio.size()-2 )
		cout<<Form(" %.2f $\\pm$ %.2f & ", val_ratio.at(bini), err_ratio.at(bini));
	  if( bini == val_ratio.size()-2 )
		cout<<Form(" %.2f $\\pm$ %.2f \\\\ ", val_ratio.at(bini), err_ratio.at(bini));
	}
	cout<<endl;
  }

  //MAKE PLOTS
  float xmin = 0; float xmax = 200;
  float ymin = 1e-1; float ymax = 10;

  int rebin = 10;
  xmax = 250;
  ymax = 25;
  if( dilep == "em" ){
	xmax = 250;
  }
  if( TString(variable).Contains("mll") ){
	xmin = 10;
  }
  
  if( TString(variable).Contains("ptdil") ){
	xmax = 500;
  }
  
  if( TString(variable).Contains("ptj") ){
	// xmin = 0;
	// xmax = 150;
    // ymin = 0;
	if( variable == "ptj1" ){
	  rebin = 10;
	  xmin = 0;
	  xmax = 1000;
	}
	if( variable == "ptj2" ){
	  rebin = 10;
	  xmax = 500;
	}
	if( variable == "ptj3" ){
	  rebin = 10;
	  xmax = 300;
	}
	if( variable == "ptj4" ){
	  rebin = 10;
	  xmax = 200;
	}
  }

  if( TString(variable).Contains("pt_matchedbjet") || TString(variable).Contains("ptb") ){
	// xmin = 0;
	// xmax = 150;
    // ymin = 0;
	if( variable == "ptb1" ){
	  rebin = 20;
	  xmin = 0;
	  xmax = 500;
	}
	if( variable == "ptb2" ){
	  rebin = 20;
	  xmax = 200;
	}
	if( variable == "ptb3" ){
	  rebin = 25;
	  xmax = 200;
	}
	if( variable == "ptb4" ){
	  rebin = 10;
	  xmax = 200;
	}
  }

  if( variable == "mt3" ){
	xmin = 0;
	xmax = 150;
    // ymin = 0;
	rebin = 10;
  }
  if( TString(variable).Contains("MHT") ){
	xmin = 0;
	xmax = 250;
    // ymin = 0;
	rebin = 5;
  }
  if( TString(variable).Contains("mhtphi") ){
	// xmin = 0;
	// xmax = 250;
    // // ymin = 0;
	rebin = 5;
  }

  if( dilep == "em" ){
    rebin = 10;
	ymin = 1e0;
	if( TString(variable).Contains("met") ){
	  rebin = 20;
	}
  }
  if( variable == "nVert" ){
	xmin = 0;
	xmax = 50;
    ymax = 100;
    ymin = 0;
	rebin = 1;
  }

  if( TString(variable).Contains("met") ){

	if( dilep == "em" ){ rebin = 10;}
	else{ rebin = 10;}
	xmin = 00;
	xmax = 200;
	if( usefsbkg ){
	  xmax = 350;
	  rebin = 25;
		
	}
	else{
	  xmax = 350;
	  rebin = 10;

	  if( TString(selection).Contains("SR_ATLAS") ){
		xmax = 300;
		rebin = 25;
	  }
	  
	  if( variable == "metall" ){

		if( TString(selection).Contains("CR3") ){
		  xmax = 150;
		  rebin = 10;
		  ymax = 2e0;
		}

		if( TString(selection).Contains("CR4") ){
		  xmax = 50;
		  rebin = 10;
		  ymax = 2e0;
		}

	  }
	}
  }

  if( variable == "ht_highbin" ||variable == "ht_highbin_3jets" ||variable == "ht_highbin_2jets" ){
	if( TString(selection).Contains("SRA") ){
	  xmin = 400;
	}
	else{
	  xmin = 100;
	}
		
	xmax = 1500;
	rebin = 50;
  }

  if( variable == "ht" || TString(variable).Contains("sumet") ){
	xmin = 40;
	xmax = 800;

	// ymax = 5e1;
	rebin = 25;
  
	if( variable == "nupfcands_30in_sumet" ){
	  xmin = 0;
	  xmax = 1000;
	  // ymax = 5e1;
	  rebin = 10;
	}
  }

  if( TString(variable).Contains("ptl") && !TString(variable).Contains("met") ){
	xmin = 0;
	xmax = 800;
    // ymax = 5e1;
	rebin = 50;
  }

  if( variable == "nbjets" || variable == "njets" || variable == "nFWjets" || TString(variable).Contains("njt") ){
	xmin = 0;
	xmax = 10;
    ymax = 5e1;
	rebin = 1;

	if( TString(selection).Contains("CR3") ){
	  xmin = 0;
	  xmax = 5;
	  ymax = 3e0;
	  rebin = 1;
	}

	if( TString(selection).Contains("CR4") ){
	  xmin = 0;
	  xmax = 5;
	  ymax = 2e0;
	  rebin = 1;
	}

  }
  if( TString(variable).Contains("phi") || variable == "metphi" || variable == "metphi20" || variable == "metphi40" || variable == "metphi60" || variable == "metphir" ){
	xmin = -3.2;
	xmax = 3.2;
	ymax = 1000;
	rebin = 5;
  }

  if( TString(variable).Contains("l2phi") || variable == "l1phi" ){
	xmin = -3.2;
	xmax = 3.2;
	ymax = 1000;
	rebin = 5;
  }

  if( TString(variable).Contains("l2eta") || variable == "l1eta" ){
	xmin = -2.4;
	xmax = 2.4;
	ymax = 1000;
	rebin = 5;
  }

  if( TString(variable).Contains("metx") || TString(variable).Contains("mety") ){
	xmin = -150;
	xmax =  150;
	rebin = 1;
  }
  if( variable == "pfcandmet_0030_pt" ){
	xmin = 0;
	xmax = 200;
    // ymax = 5e1;
	rebin = 5;
  }

  if( TString(selection).Contains("SR") ){
	if( !TString(selection).Contains("withb") ){
 	  ymax = 2e3;
	}
	else{
 	  ymax = 5e2;
	}
  }
  
  updateoverflow( h_data , xmax );
  updateoverflow( h_zjets, xmax );
  updateoverflow( h_ttbar, xmax );
  updateoverflow( h_st   , xmax );
  updateoverflow( h_wz   , xmax );
  updateoverflow( h_zz   , xmax );
  updateoverflow( h_ww   , xmax );
  updateoverflow( h_ttv  , xmax );
  updateoverflow( h_vvv  , xmax );

  if( drawsignal ) updateoverflow( h_signal1  , xmax );

  if( uservariablebins ) {  

	vector <double> v_bin;
	v_bin.push_back(0);
	v_bin.push_back(25);
	v_bin.push_back(50);
	v_bin.push_back(75);
	v_bin.push_back(100);
	v_bin.push_back(150);
	v_bin.push_back(225);
	if( !TString(selection).Contains("SR_ATLAS"             ) )
	  v_bin.push_back(300);
	v_bin.push_back(xmax);

	// if( TString(selection).Contains("2jets_inclusive"      ) ) {
	//   v_bin.clear();
	//   v_bin.push_back(0);
	//   v_bin.push_back(25);
	//   v_bin.push_back(50);
	//   v_bin.push_back(75);
	//   v_bin.push_back(100);
	//   v_bin.push_back(150);
	//   v_bin.push_back(xmax);
	// }

	
	int nbins = v_bin.size()-1;
  
	double bins[nbins+1];

	for( size_t bini = 0; bini < v_bin.size(); bini++ ){
	  bins[bini] = v_bin.at(bini);
	}

	h_data  = (TH1F*) h_data  -> Rebin(nbins, "h_data_rebinned", bins);
	h_zjets = (TH1F*) h_zjets -> Rebin(nbins, "h_zjets_rebinned", bins);
	h_ttbar = (TH1F*) h_ttbar -> Rebin(nbins, "h_ttbar_rebinned", bins);
	h_st    = (TH1F*) h_st    -> Rebin(nbins, "h_st_rebinned", bins);
	h_wz    = (TH1F*) h_wz    -> Rebin(nbins, "h_wz_rebinned", bins);
	h_zz    = (TH1F*) h_zz    -> Rebin(nbins, "h_zz_rebinned", bins);
	h_ww    = (TH1F*) h_ww    -> Rebin(nbins, "h_ww_rebinned", bins);
	h_vvv   = (TH1F*) h_vvv   -> Rebin(nbins, "h_vvv_rebinned", bins);
	h_ttv   = (TH1F*) h_ttv   -> Rebin(nbins, "h_ttv_rebinned", bins);
	if( drawsignal ) h_signal1 = (TH1F*) h_signal1   -> Rebin(nbins, "h_signal1_rebinned", bins);

	renormalizebins( h_data  );
	renormalizebins( h_zjets );
	renormalizebins( h_ttbar );
	renormalizebins( h_st    );
	renormalizebins( h_wz    );
	renormalizebins( h_zz    );
	renormalizebins( h_ww    );
	renormalizebins( h_vvv   );
	renormalizebins( h_ttv   );
	if( drawsignal ) renormalizebins( h_signal1   );

	
  }else{
	h_data->Rebin(rebin);
	h_zjets->Rebin(rebin);
	h_ttbar->Rebin(rebin);
	h_st->Rebin(rebin);
	h_wz->Rebin(rebin);
	h_zz->Rebin(rebin);
	h_ww->Rebin(rebin);
	h_vvv->Rebin(rebin);
	h_ttv->Rebin(rebin);
	if( drawsignal ) h_signal1->Rebin(rebin);
	// h_vvbkg->Rebin(rebin);
	// h_other->Rebin(rebin);
  }
  
  TCanvas * c1 = new TCanvas("c1","");
  c1->cd();
  // c1->SetLogy();

  TPad *pad = new TPad( "p_main", "p_main", 0.0, 0.3, 1.0, 1.0);
  pad->SetBottomMargin(0.05);
  pad->SetRightMargin(0.07);
  pad->SetTopMargin(0.08);
  pad->SetLeftMargin(0.18);
  pad->Draw();
  pad->cd();
  if( !(TString(variable).Contains("phi") || TString(variable).Contains("eta") || variable == "nVert" || variable == "mhtphi" || dilep == "em" || variable == "metphi" || variable == "metphi20" || variable == "metphi40" || variable == "metphi60" || variable == "metphir" || TString(variable).Contains("njt") || variable == "metall" || variable == "mll_fkw") ){
	pad->SetLogy();
  }
  
  h_data->SetLineWidth(2);

  h_zjets->SetFillColor(kAzure+5);
  h_ttbar->SetFillColor(kYellow+1);
  // h_zz->SetFillColor(kOrange-3);
  h_zz->SetFillColor(kRed-3);
  h_wz->SetFillColor(kRed);
  h_st->SetFillColor(kAzure-2);
  h_ww->SetFillColor(kGreen+1);
  h_ttv->SetFillColor(kViolet+2);
  h_vvv->SetFillColor(kMagenta);
  // h_vvbkg->SetFillColor(kRed);
  // h_other->SetFillColor(kMagenta);
  
  h_zjets->SetFillStyle(1001);
  h_ttbar->SetFillStyle(1001);
  h_st->SetFillStyle(1001);
  h_wz->SetFillStyle(1001);
  h_zz->SetFillStyle(1001);
  h_ww->SetFillStyle(1001);
  h_vvv->SetFillStyle(1001);
  h_ttv->SetFillStyle(1001);
  // h_vvbkg->SetFillStyle(1001);
  // h_other->SetFillStyle(1001);

  float lomll = 0;
  float himll = -1;
  
  float norm_factor =   h_data->Integral(h_data->FindBin(lomll),h_data->FindBin(himll)-1)/
	(h_zjets->Integral(h_zjets->FindBin(lomll),h_zjets->FindBin(himll)-1) +
	 h_ttbar->Integral(h_ttbar->FindBin(lomll),h_ttbar->FindBin(himll)-1) +
	 h_st->Integral(h_st->FindBin(lomll),h_st->FindBin(himll)-1) +
	 h_wz->Integral(h_wz->FindBin(lomll),h_wz->FindBin(himll)-1) +
	 h_zz->Integral(h_zz->FindBin(lomll),h_zz->FindBin(himll)-1) +
	 h_ww->Integral(h_ww->FindBin(lomll),h_ww->FindBin(himll)-1) +
	 h_vvv->Integral(h_vvv->FindBin(lomll),h_vvv->FindBin(himll)-1) + 
	 h_ttv->Integral(h_ttv->FindBin(lomll),h_ttv->FindBin(himll)-1) 
	 );

  cout<<"Norm factor for Z+jets: "<<norm_factor<<endl;

  if( !normalized ) norm_factor = 1;
  // norm_factor = 0.8;
  
  h_zjets->Scale(norm_factor);
  h_ttbar->Scale(norm_factor);
  h_st->Scale(norm_factor);
  h_wz->Scale(norm_factor);
  h_zz->Scale(norm_factor);
  h_ww->Scale(norm_factor);
  h_vvv->Scale(norm_factor);
  h_ttv->Scale(norm_factor);
  
  THStack * stack = new THStack("stack","");

  // stack->Add(h_other);
  // stack->Add(h_vvbkg);

  TH1F * h_allZJbg = (TH1F*) h_zjets->Clone("h_allZJbg");
  TH1F * h_allFSbg = (TH1F*) h_ttbar->Clone("h_allFSbg");
  TH1F * h_otherbg = (TH1F*) h_zz->Clone("h_otherbg");

  if( combineMCbgs ){
	h_otherbg->Add(h_vvv);
	h_otherbg->Add(h_ww);
	h_otherbg->Add(h_ttv);
	stack->Add(h_otherbg);
	stack->Add(h_ttbar);
	stack->Add(h_zjets);
	
  }else
	
	if( useedgeplots ){
	  if( usefsbkg ){
		h_allFSbg->Add(h_ttv);
		h_allFSbg->Add(h_vvv);
		stack->Add(h_allFSbg);
	  }
	  else{
		h_allFSbg->Add(h_ww);
		h_allFSbg->Add(h_st);
		h_allFSbg->Add(h_ttv);
		h_allFSbg->Add(h_vvv);
		stack->Add(h_allFSbg);
	  }
	  if( usetemplates ){
		h_allZJbg->Add(h_wz);
		h_allZJbg->Add(h_zz);
		stack->Add(h_allZJbg);
	  }
	  else{
		stack->Add(h_zjets);
	  }
	}

  else{
  
	stack->Add(h_ttv);
	stack->Add(h_vvv);
	stack->Add(h_wz);
	stack->Add(h_zz);
	if( usefsbkg ){
	  stack->Add(h_ttbar);
	}
	else{
	  stack->Add(h_ww);
	  stack->Add(h_st);
	  stack->Add(h_ttbar);
	}
	if( usetemplates ){
	  stack->Add(h_zjets);
	}
	else{
	  stack->Add(h_zjets);
	}
  }
  
  h_data->GetXaxis()->SetLabelSize(0);
  h_data->GetYaxis()->SetLabelSize(0.05);
  h_data->GetYaxis()->SetLabelFont(42);
  h_data->GetYaxis()->SetTitleOffset(1.5);
  h_data->GetYaxis()->SetTitleSize(0.05);
  h_data->GetYaxis()->SetTitleFont(42);
  h_data->GetYaxis()->SetTitle(Form("Events / %.0f GeV", (float)rebin));

  if( variable == "mll_fkw" ){
	h_data->GetYaxis()->SetRangeUser(0, 40 );  
  }else{
	h_data->GetYaxis()->SetRangeUser(0, h_data->GetMaximum()*1.4 );  
  }

  if( TString(variable).Contains("phi") ||  TString(variable).Contains("eta") || variable == "mhtphi" || dilep    == "em" || variable == "nVert" ||variable == "metphi" || variable == "metphi20" || variable == "metphi40" || variable == "metphi60" || variable == "metphir"  ){

	if( variable == "mll_fkw" ){
	  h_data->GetYaxis()->SetRangeUser(0, 40 );  
	}else{
	  h_data->GetYaxis()->SetRangeUser(0, h_data->GetMaximum()*1.4 );  
	}

	if( TString(variable).Contains("phi") )h_data->GetYaxis()->SetTitle(Form("Events/%.2f", (2*3.14159)/200*(float)rebin));
	if( TString(variable).Contains("eta") )h_data->GetYaxis()->SetTitle(Form("Events/%.2f", (2*2.4)/200*(float)rebin));
  }
  else{
	h_data->GetYaxis()->SetRangeUser(ymin*luminosity, h_data->GetMaximum() * ymax );
  }
  if( TString(variable).Contains("phi") ||  TString(variable).Contains("eta") || variable == "metphi" || variable == "metphi20" || variable == "metphi40" || variable == "metphi60" || variable == "metphir" ){
	h_data->GetYaxis()->SetRangeUser(0, h_data->GetMaximum()*1.4 );  
  }

  if( TString(variable).Contains("njets") || TString(variable).Contains("njt") )h_data->GetYaxis()->SetTitle("Events");
  
  h_data->GetXaxis()->SetRangeUser(xmin, xmax);
  h_data->SetMarkerStyle(8);
  h_data->SetMarkerSize(0.75);

  if( variable == "mll_fkw" ){
	h_data->GetYaxis()->SetRangeUser(0, 60 );  
	if( TString(selection).Contains("SRA") ){
	  h_data->GetYaxis()->SetRangeUser(0, 45 );  
	}
  }

  if( TString(variable).Contains("pt_matchedbjet") ){
	if( h_zjets->GetMaximum() > h_ttbar->GetMaximum()){
	  h_data->GetYaxis()->SetRangeUser(1e-1, h_zjets->GetMaximum()*1e1 );  
	}
	else{
	  h_data->GetYaxis()->SetRangeUser(1e-1, h_ttbar->GetMaximum()*1e1 );  
	}
  }


  if( TString(selection).Contains("SR") || TString(selection).Contains("2jets_inclusive") ){

	h_data->GetYaxis()->SetRangeUser(2e-1, 2e3 );  
	// pad->SetLogy(0);
	if( TString(selection).Contains("SRB_bveto") ){
	  h_data->GetYaxis()->SetRangeUser(1.1e-1, 6e3 );  
	}
	if( TString(selection).Contains("SRB_withb") ){
	  h_data->GetYaxis()->SetRangeUser(7e-2, 9e3 );  
	}

	if( TString(selection).Contains("SRA_bveto") ){
	  h_data->GetYaxis()->SetRangeUser(1.1e-1, 8e3 );  
	}
	if( TString(selection).Contains("SRA_withb") ){
	  h_data->GetYaxis()->SetRangeUser(2e-2, 6e3 );  
	  // h_data->GetYaxis()->SetRangeUser(0, 1.4e2 );  
	  // pad->SetLogy(0);
	}
	if( TString(selection).Contains("SR_ATLAS") ){
	  h_data->GetYaxis()->SetRangeUser(1.1e-1, 1e4 );  
	}
  }
  
  TH1F* h_unc    = (TH1F*)h_data  -> Clone("h_unc");
  TH1F* h_unc_bg = (TH1F*)h_data  -> Clone("h_unc_bg");
  
  for( int binind = 1; binind < h_unc->GetNbinsX()+1; binind++ ){
	h_unc->SetBinContent(binind,1.0);
	float binlowedge = h_unc->GetBinLowEdge(binind);
	float uncertainty = 0.0;
	
	for( size_t errind = 0; errind < metcut.size()-1; errind++ ){

	  if( binlowedge < metcut.at(errind+1) ){
		uncertainty = err_allbg.at(errind)/val_allbg.at(errind);
		h_unc_bg->SetBinContent(binind,val_allbg.at(errind));
		// cout<<"binlow: "<<binlowedge<<" | metlow: "<<metcut.at(errind)<<" | uncertainty: "<<uncertainty<<endl;
		break;
	  }  

	}
	if( uncertainty == 0.0 ){
	  uncertainty = err_allbg.at(err_allbg.size()-2)/val_allbg.at(err_allbg.size()-2);
	  h_unc_bg->SetBinContent(binind,val_allbg.at(err_allbg.size()-2));
	}

	h_unc->SetBinError(binind,uncertainty);
	h_unc_bg->SetBinError(binind,uncertainty*h_unc_bg->GetBinContent(binind));

  }


  if( drawassymuncs ){
	gr->SetFillColor(kBlue+3);
	gr->SetFillStyle(3004);
	gr->SetMarkerSize(0);
	r_gr->SetFillColor(kBlue+3);
	r_gr->SetFillStyle(3004);
	r_gr->SetMarkerSize(1);
  }
  else{
  
	h_unc->SetFillColor(kBlue+3);
	h_unc->SetFillStyle(3004);
	h_unc->SetMarkerSize(0);
	// cout<<gStyle->SetHatchesLineWidth(1.2);
  
	h_unc_bg->SetFillColor(kBlue+3);
	h_unc_bg->SetFillStyle(3004);
	h_unc_bg->SetMarkerSize(0);  
	renormalizebins( h_unc_bg );
  }
  
  if( drawsignal ){
	h_signal1->SetLineColor(kGreen+1);
	h_signal1->SetLineWidth(2);
	h_signal1->SetMarkerSize(0);	
  }
  

  h_data->Draw("x0e1");
  stack->Draw("samehist");
  if( drawassymuncs ) gr->Draw("sameE2");
  h_data->Draw("samex0e1");
  gStyle->SetErrorX(0.5);
  if( showunc_main && ! drawassymuncs ) h_unc_bg->Draw("sameE2");
  if( drawsignal ) h_signal1->Draw("histsame");
  
  pad->RedrawAxis();

  TLegend *l1 = NULL;
  if( !TString(selection).Contains("SRA") ){
	l1 = new TLegend(0.5, 0.6, 0.90, 0.90);    
  }else{
	l1 = new TLegend(0.55, 0.6, 0.90, 0.90);    
  }

  l1->SetLineColor(kWhite);    
  l1->SetShadowColor(kWhite);    
  l1->SetFillColor(kWhite);    
  l1->SetTextFont(42);    
  l1->SetTextSize(0.04);

  if( TString(selection).Contains("signalcontamination") ){
	l1->AddEntry( h_data    , "data + Signal" , "lpe");
  }else{
	l1->AddEntry( h_data    , "Data"          , "lpe");
  }
	  
  if( combineMCbgs ){
	l1->AddEntry( h_zjets , "MET Templates"   , "f");
	l1->AddEntry( h_allFSbg , "FS background" , "f");   
	l1->AddEntry( h_otherbg , "Other SM"      , "f");   

  }else
	if( useedgeplots ){
	  l1->AddEntry( h_allZJbg , "Z background"  , "f");   
	  l1->AddEntry( h_allFSbg , "FS background" , "f");   
	}  

	else{
	  if( usetemplates ){
		l1->AddEntry( h_zjets , "MET Templates" , "f");
	  }else{
		l1->AddEntry( h_zjets , "Z+jets MC"     , "f");
	  }
	  if( usefsbkg ){
		l1->AddEntry( h_ttbar , "FS Bkg"        , "f");
	  }else{
		l1->AddEntry( h_ttbar , "t#bar{t} MC"   , "f");
		l1->AddEntry( h_st , "Single-top MC"    , "f");
		l1->AddEntry( h_ww , "WW MC"            , "f");
	  }
	  l1->AddEntry( h_wz    , "WZ MC"           , "f");
	  l1->AddEntry( h_zz    , "ZZ MC"           , "f");
	  l1->AddEntry( h_vvv , "VVV MC"            , "f");
	  l1->AddEntry( h_ttv , "t#bar{t}V MC"      , "f");
	}
  if( drawsignal ) l1->AddEntry( h_signal1 , "m(#tilde{g})=1050; m_{LSP}=200"       , "l");

  l1->Draw("same");
  
  c1->cd();
	
  TPad *rat_pad = new TPad( "p_main", "p_main", 0.0, 0.0, 1.0, 0.3);
  rat_pad->SetBottomMargin(0.36);
  rat_pad->SetRightMargin(0.07);
  rat_pad->SetTopMargin(0.07);
  rat_pad->SetLeftMargin(0.18);
  rat_pad->Draw();
  rat_pad->cd();
  rat_pad->SetGridy();

  TH1F* h_rat = (TH1F*)h_data  -> Clone("h_rat");
  TH1F* h_den = (TH1F*)h_zjets -> Clone("h_den");
  if( usefsbkg ){
	h_den->Add(h_ttbar);
  }else{
	h_den->Add(h_ttbar);
	h_den->Add(h_st);
	h_den->Add(h_ww);
  }
  h_den->Add(h_zz);
  h_den->Add(h_wz);
  h_den->Add(h_vvv);
  h_den->Add(h_ttv);
  // h_den->Add(h_other);
  // h_den->Add(h_vvbkg);

  h_rat->Divide(h_den);

  // h_rat->GetYaxis()->SetRangeUser(0.6,1.4);
  // if( TString(variable).Contains("met") ){
  h_rat->GetYaxis()->SetRangeUser(0.01,2.0);
  // }
  h_rat->GetYaxis()->SetLabelSize(0.12);
  h_rat->GetXaxis()->SetLabelSize(0.12);
  h_rat->GetYaxis()->SetNdivisions(5);

  h_rat->GetYaxis()->SetTitle("#frac{Data}{Prediction}");
  h_rat->GetYaxis()->SetTitleSize(0.12);
  h_rat->GetYaxis()->SetTitleOffset(0.5);
  h_rat->GetYaxis()->SetLabelFont(42);
  h_rat->GetXaxis()->SetLabelFont(42);
  h_rat->GetYaxis()->SetTitleFont(42);
  h_rat->GetYaxis()->CenterTitle();
  h_rat->GetXaxis()->SetTitleFont(42);
  
  if( variable == "nVert"               ) h_rat->GetXaxis()->SetTitle("N_{vtx}");
  if( TString(variable).Contains("met") ) h_rat->GetXaxis()->SetTitle("E_{T}^{miss} [GeV]");
  if( TString(variable).Contains("sumet") ) h_rat->GetXaxis()->SetTitle("sum E_{T} GeV");
  if( TString(variable).Contains("MHT") ) h_rat->GetXaxis()->SetTitle("H_{T}^{miss} GeV");
  if( TString(variable).Contains("mhtphi") ) h_rat->GetXaxis()->SetTitle("H_{T} Phi");
  if( variable == "ht" || variable == "ht_highbin" ) h_rat->GetXaxis()->SetTitle("H_{T} GeV");
  if( TString(variable).Contains("pt")  ) h_rat->GetXaxis()->SetTitle("p_{T} GeV");
  if( variable == "njets"  || TString(variable).Contains("njt") ) h_rat->GetXaxis()->SetTitle("N_{jets}");  
  if( variable == "nbjets"               ) h_rat->GetXaxis()->SetTitle("N_{b-jets}");  
  if( variable == "mll"                 ) h_rat->GetXaxis()->SetTitle("M_{\\ell\\ell} GeV");
  if( TString(variable).Contains("phi") ) h_rat->GetXaxis()->SetTitle("E_{T}^{miss} #phi");
  if( TString(variable).Contains("l1phi") ) h_rat->GetXaxis()->SetTitle("leading lepton #phi");
  if( TString(variable).Contains("l2phi") ) h_rat->GetXaxis()->SetTitle("sub-leading lepton #phi");
  if( TString(variable).Contains("l1eta") ) h_rat->GetXaxis()->SetTitle("leading lepton #eta");
  if( TString(variable).Contains("l2eta") ) h_rat->GetXaxis()->SetTitle("sub-leading lepton #eta");
  if( TString(variable).Contains("_pt") ) h_rat->GetXaxis()->SetTitle("E_{T}^{miss} [GeV]");
  if( TString(variable).Contains("ptj1")) h_rat->GetXaxis()->SetTitle("p_{T} jet 1 [GeV]");
  if( TString(variable).Contains("ptj2")) h_rat->GetXaxis()->SetTitle("p_{T} jet 2 [GeV]");
  if( TString(variable).Contains("ptj3")) h_rat->GetXaxis()->SetTitle("p_{T} jet 3 [GeV]");
  if( TString(variable).Contains("ptj4")) h_rat->GetXaxis()->SetTitle("p_{T} jet 4 [GeV]");

  h_rat->GetXaxis()->SetTitleOffset(0.9);
  h_rat->GetXaxis()->SetTitleSize(0.15);

  h_rat->SetMarkerStyle(8);
  h_rat->SetMarkerSize(0.75);

  if( drawassymuncs ){
	h_rat->SetMarkerSize(0);
	h_rat->SetLineWidth(0);
	r_gr_central->SetLineColor(kBlack);
	r_gr_central->SetLineWidth(2);
	r_gr_central->SetMarkerColor(kBlack);
	r_gr_central->SetMarkerStyle(8);
	r_gr_central->SetMarkerSize(0.75);

	for( int binind = 0; binind <= h_rat->GetNbinsX()+1; binind++ ){
	  h_rat->SetBinContent(binind, 1.0);
	  h_rat->SetBinError(binind, 0.0);	
	}

  }


  h_rat->Draw("e1x0");
  if( drawassymuncs ){
	r_gr_central->Draw("e1Psame");
  }else{  h_rat->Draw("e1x0same");}
  gStyle->SetErrorX(0.5);
  if( drawassymuncs ) r_gr->Draw("sameE2");
  if( showunc_rati && !drawassymuncs) h_unc->Draw("sameE2");

  TLine * xaxis = new TLine(xmin,1,xmax,1);
  xaxis->SetLineWidth(2);
  xaxis->Draw("same");  
 
  // if( luminosity*norm_factor < 0.0161 ) drawCMSLatex( c1, 0.0161 );
  // else                                  drawCMSLatex( c1, luminosity*norm_factor );

  if( !( TString(selection).Contains("SR") || TString(selection).Contains("2jets_inclusive" ) ) && luminosity*norm_factor < 4.0 ) drawCMSLatex( c1, 4.0 );
  else drawCMSLatex( c1, luminosity*norm_factor );

  if( !TString(selection).Contains("signalcontamination") ){
	drawSRLatex(  c1, selection, 0.35, 0.35 );
  }
	
  if( usefsbkg ) {
	c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_%s_%s_signalregion%s_fsbkg_%s.png", iter.c_str(), variable.c_str(), dilep.c_str(), selection.c_str(), region.c_str() ));
	c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_%s_%s_signalregion%s_fsbkg_%s.pdf", iter.c_str(), variable.c_str(), dilep.c_str(), selection.c_str(), region.c_str() ));
  }else{
	if( usemgzjets ){
	  c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_%s_%s_signalregion%s_%smlm.png", iter.c_str(), variable.c_str(), dilep.c_str(), selection.c_str(), region.c_str() ));
	  c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_%s_%s_signalregion%s_%smlm.pdf", iter.c_str(), variable.c_str(), dilep.c_str(), selection.c_str(), region.c_str() ));
	}
	else{
	  c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_%s_%s_signalregion%s_%s.png", iter.c_str(), variable.c_str(), dilep.c_str(), selection.c_str(), region.c_str() ));
	  c1->SaveAs(Form("../output/ZMET2015/%s/plots/Closure/h_%s_%s_signalregion%s_%s.pdf", iter.c_str(), variable.c_str(), dilep.c_str(), selection.c_str(), region.c_str() ));
	}
  }
  
  return;
}
