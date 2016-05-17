 #include <iostream>

#include "TChain.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStyle.h"

#include "templateLooper.h"

using namespace std;

void runTemplateLooper( std::string selection = "", std::string iter = "", std::string sample = "All_MC" ){

  gSystem->Load("libTemplateLooper.so");
  gROOT ->SetStyle("Plain");
  gStyle->SetOptStat(111111);

  TChain* ch = new TChain("t");
  if ( sample == "data" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/data_2016B_Prompt_ee*.root" , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/data_2016B_Prompt_em*.root" , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/data_2016B_Prompt_mm*.root" , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/data_2016B_Prompt_ph*.root" , iter.c_str() ));	
	
	if( TString(selection).Contains("signalcontamination") ){
	  ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/t5zz_mgl*_mlm.root" , iter.c_str() ));
	}	
  }

  if ( sample == "fullscan" || sample == "signal1100200" || sample == "signal900" ){
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/t5zz_mgl*_mlm*.root" , iter.c_str() ));
  }

  else if ( sample == "All_MC" ){
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/dyjetsll_50ns_m1050nlo*.root"  , iter.c_str() ));
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/dyjetsll_50ns_m50nlo*.root"    , iter.c_str() ));
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/tt2lnu_50ns_php8*.root"         , iter.c_str() ));	
  }

  else if( sample == "zjets" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/dy_m1050_amcnlo*.root" , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/dy_m50_amcnlo*.root"   , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/dy_m50_amcnlo.root"   , iter.c_str() ));
  }

  else if( sample == "zjetsmlm" ){
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/zjetsll_25ns_m50mlm*.root"  , iter.c_str() ));
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/zjetsllht100_25ns_m50mlm*.root"  , iter.c_str() ));
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/zjetsllht200_25ns_m50mlm*.root"  , iter.c_str() ));
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/zjetsllht400_25ns_m50mlm*.root"  , iter.c_str() ));
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/zjetsllht600_25ns_m50mlm*.root"  , iter.c_str() ));
  }

  else if( sample == "zjinc" ){
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/dyjetsll_m50inc*.root"    , iter.c_str() ));
  }

  else if( sample == "ttbar" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/ttbar_dilep_mgmlm*.root" , iter.c_str() ));
  }

  else if( sample == "st" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/ST_tW_antitop_5f_inclusiveDecays_13TeV*.root" , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/ST_tW_top_5f_inclusiveDecays_13TeV*.root"     , iter.c_str() ));
  }

  else if( sample == "ww" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/WWTo2L2Nu_13TeV-powheg*.root" , iter.c_str() ));
  }

  else if( sample == "wz_inc" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8*.root" , iter.c_str() ));
  }

  else if( sample == "zz_inc" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/ZZTo2L2Nu_13TeV_powheg_pythia8*.root"              , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8*.root" , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/ZZTo4L_13TeV_powheg_pythia8*.root"                 , iter.c_str() ));
  }

  else if( sample == "wz" ){
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/wz3lnu_25ns_powp8*.root"     , iter.c_str() ));
  }

  else if( sample == "zz" ){
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/zz2l2nu_25ns_powp8*.root"        , iter.c_str() ));
  }

  else if( sample == "vvv" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8*.root"                 , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8*.root"                 , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8*.root"                 , iter.c_str() ));
  }

  else if( sample == "ttv" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/ttHJetToNonbb_M125_13TeV*.root"                                     , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8*.root"         , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8*.root"                  , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8*.root" , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8*.root"  , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8*.root"      , iter.c_str() ));
	// // ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/ttw2q_25ns_nlo*.root"       , iter.c_str() ));
	// // ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/ttwlnu_25ns_nlo*.root"      , iter.c_str() ));
	// ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/ttzllnunu_25ns_nlo*.root"   , iter.c_str() ));
	// // ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/ttzqq_25ns_nlo*.root"       , iter.c_str() ));
	// // ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/ttg_25ns_nlo*.root"         , iter.c_str() ));
  }
  
  templateLooper* myLooper = new templateLooper();
  myLooper->ScanChain( ch , iter , sample, selection );

}

int main(int argc, char **argv)
{

  if (argc < 4) {
    std::cout << "USAGE: runTemplateLooper <selection> <iter> <sample>" << std::endl;
    return 1;
  }
  
  string selection(argv[1]); 
  string iter(argv[2]); 
  string sample(argv[3]); 
  
  runTemplateLooper( selection, iter, sample );
  return 0;
}
