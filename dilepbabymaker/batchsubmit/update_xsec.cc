#include "TFile.h"
#include "TH1.h"
#include "TChain.h"

#include <iostream>
#include <stdexcept>

using namespace std;

ULong64_t get_new_nevents( string inputdir = "" )
{

  if(inputdir == ""){
	cout<<"no directory given. Exiting."<<endl;
	return 1;
  }

  ULong64_t nevents_total = 0;
  TH1F * hist = NULL;
  
  // get list of filenames using tchain
  TChain * ch = new TChain("t");
  ch->Add(Form("%s/*.root", inputdir.c_str()));
  TObjArray *listOfFiles = ch->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile* currentFile = 0;
  while ( (currentFile = (TFile*) fileIter.Next()) ){  
  	// cout<<"opening file: "<<currentFile->GetTitle()<<endl;
	TFile f(currentFile->GetTitle());
	try{
	  hist = (TH1F*)f.Get("h_neventsinfile");
	}catch(exception &e)
	  {
		cout<<"hist: h_neventsinfile does not exist. Exiting."<<endl;
		exit(1);
	  }
  	nevents_total += hist->GetBinContent(0);	
  }
  
  // cout<<"Sum of events: "<<nevents_total<<endl;
  return nevents_total;
}

double calculate_new_scale1fb( TChain * &ch, string indir = "", string outpath = "", double xsec_force = -1. ){

  ULong64_t new_nevents = get_new_nevents( indir );

  float xsec_input_max = ch->GetMaximum("evt_xsec");
  float xsec_input_min = ch->GetMinimum("evt_xsec");
  if (xsec_force < 0 && fabs(xsec_input_max - xsec_input_min) > 1e-4 * xsec_input_max) {
	cout << "ERROR: xsec varies across input trees: max value: " << xsec_input_max
		 << ", min value: " << xsec_input_min << ", aborting.." << endl;
	return 2;
  }

  else if (xsec_force > 0) {
	xsec_input_max = xsec_force;
  }

  float kfactor_input = ch->GetMaximum("evt_kfactor");
  float filter_input  = ch->GetMaximum("evt_filter" );

  Float_t scale1fb_input = xsec_input_max * kfactor_input * filter_input * 1000. / double(new_nevents);

  cout << "input events: " << new_nevents << endl
  	   << "xsec*kfactor*filter: " << xsec_input_max * kfactor_input * filter_input << endl
  	   << "new scale1fb: " << scale1fb_input << endl;
  
  return scale1fb_input;
}

void update_xsec()
{

  string outpath = "/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-03/zz_4l_powheg";
  
  TChain * ch = new TChain("t");
  ch->Add(Form("%s*.root", outpath.c_str()));

  calculate_new_scale1fb( ch, "/hadoop/cms/store/user/cwelke/uaf8/dilepbabies//V08-22-03_zz_4l_powheg/", outpath );
  return;
}
