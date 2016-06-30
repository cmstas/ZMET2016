#include <iostream>

#include "TChain.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStyle.h"

#include "makePhotonTemplates.h"

using namespace std;

void runPhotonTemplates( std::string selection = "", std::string iter = "", std::string sample = "", bool dohtreweighting = false , bool doptreweighting = false ){

  gSystem->Load("libmakePhotonTemplates.so");
  gROOT ->SetStyle("Plain");
  gStyle->SetOptStat(111111);

  TChain* ch = new TChain("t");

  if ( sample == "data" ){
	// ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/data_2015C25ns05Oct2015_ph*.root" , iter.c_str() ));
	// ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/data_2015D25ns05Oct2015_ph*.root" , iter.c_str() ));
	// ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/data_2015D25nsPromptv4_ph*.root"  , iter.c_str() ));

	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/data_2015C25ns05Oct2015_ph*.root" , iter.c_str() ));
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/data_2015D25ns05Oct2015_ph*.root" , iter.c_str() ));
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/data_2015D25nsPromptv4_ph*.root"  , iter.c_str() ));

	}

  else if ( sample == "All_MC" ){

	// ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/gjetsht*.root");
	ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/gjetsht40_dr0p4_mgmlm.root");
	ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/gjetsht100_dr0p4_mgmlm.root");
	ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/gjetsht200_dr0p4_mgmlm.root");
	ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/gjetsht400_dr0p4_mgmlm.root");
	ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/gjetsht600_dr0p4_mgmlm.root");

  }

  makePhotonTemplates* myLooper = new makePhotonTemplates(dohtreweighting, doptreweighting);
  myLooper->ScanChain( ch , iter , sample, selection );

  
  // makePhotonTemplates myLooper(selection);
  // myLooper.ScanChain( ch , iter , sample );

}

int main(int argc, char **argv)
{

  if (argc < 5) {
    std::cout << "USAGE: runTemplateLooper <selection> <iter> <sample> <htreweighting>" << std::endl;
    return 1;
  }
  
  string selection(argv[1]); 
  string iter(argv[2]); 
  string sample(argv[3]); 
  string dohtreweighting(argv[4]); 

  bool doreweighting = false;
  bool doptreweighting = false;
  if( dohtreweighting == "dohtreweighting" )  doreweighting = true;
  if( dohtreweighting == "doptreweighting" ){
	doreweighting = true;
	doptreweighting = true;
  }
  
  runPhotonTemplates( selection, iter, sample, doreweighting, doptreweighting );
  return 0;
}
