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
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016B_23sep2016rereco_ph_v*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016C_23sep2016rereco_ph_v*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016D_23sep2016rereco_ph_v*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016E_23sep2016rereco_ph_v*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016F_23sep2016rereco_ph_v*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016G_23sep2016rereco_ph_v*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016H_Prompt_ph_v*.root"));

	}

  if ( sample == "data_withMC" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-03/data_2016B_Prompt_ph_v2*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-03/data_2016C_Prompt_ph_v2*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-03/data_2016D_Prompt_ph_v2*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-03/wgjets_incl_amcnlo*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-03/ttbar_1ltbr_mgmlm*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-03/ttbar_1ltop_mgmlm*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-03/znunugamma_ptg130_mgmlm*.root"));

	}


  if ( sample == "allewk" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-03/wgjets_incl_amcnlo*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-03/ttbar_1ltbr_mgmlm*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-03/ttbar_1ltop_mgmlm*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-03/znunugamma_ptg130_mgmlm*.root"));
  }

  if ( sample == "wgjets" ){
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-04/wgjets_incl_amcnlo*.root"));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-03/znunugamma_ptg130_mgmlm*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-03/wgjets_incl_amcnlo*.root"));
  }
  if ( sample == "wjets" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-04/wjets*.root"));
  }
  if ( sample == "ttbar" ){
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-04/ttbar_1ltop_mgmlm*.root"));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-04/ttbar_1ltbr_mgmlm*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-03/ttbar_1ltbr_mgmlm*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-03/ttbar_1ltop_mgmlm*.root"));
  }
  if ( sample == "ttgamma" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-04/ttgamma*.root"));
  }
  if ( sample == "znunugamma" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-04/znunugamma_ptg40_mgmlm*.root"));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-04/znunugamma_ptg130_mgmlm*.root"));
	// ch->Add(Form("/hadoop/cms/store/user/cwelke/uaf8/dilepbabies/V08-11-03_znunugamma_ptg130_mgmlm/unknown_merged_ntuple_*.root"));
  }

  if ( sample == "All_MC" ){

	ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-10/gjetsht*_dr0p05_mgmlm*.root");
	// ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-04/gjetsht40_dr0p4_mgmlm.root");
	// ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-04/gjetsht100_dr0p4_mgmlm.root");
	// ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-04/gjetsht200_dr0p4_mgmlm.root");
	// ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-04/gjetsht400_dr0p4_mgmlm.root");
	// ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-04/gjetsht600_dr0p4_mgmlm.root");

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
