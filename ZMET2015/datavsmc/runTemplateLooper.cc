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
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/data_2016B_Prompt_ee*.root" , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/data_2016B_Prompt_em*.root" , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/data_2016B_Prompt_mm*.root" , iter.c_str() ));
	// // ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V7680-hybrid-00/data_2016B_Prompt_ph*.root" , iter.c_str() ));	

	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-01/data_2016B_Prompt_ee*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-01/data_2016B_Prompt_em*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-01/data_2016B_Prompt_mm*.root" ));
	
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
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/dy_m1050_amcnlo*.root" , iter.c_str() ));
	// // ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/dy_m50_amcnlo*.root"   , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/dy_m50_amcnlo.root"   , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/dy_m1050_amcnlo*.root"  , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/dy_m50_amcnlo*.root"  , iter.c_str() ));
  }

  else if( sample == "zjetsmlm" ){
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/dy_m50_mgmlm_ext1*.root"  , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/dy_m50_mgmlm_ext1.root"  , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/dy_m50_mgmlm_ext1_1.root"  , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/dy_m50_mgmlm_ext1_2.root"  , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/dy_m50_mgmlm_ht100_ext1*.root"  , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/dy_m50_mgmlm_ht200_ext1*.root"  , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/dy_m50_mgmlm_ht400_ext1*.root"  , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/dy_m50_mgmlm_ht600.root"  , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/dy_m50_mgmlm_ht600_ext1*.root"  , iter.c_str() ));


  }

  else if( sample == "zjinc" ){
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/dyjetsll_m50inc*.root"    , iter.c_str() ));
  }

  else if( sample == "ttbar" ){
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/ttbar_dilep_mgmlm*.root" , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/ttbar_dilep_mgmlm*.root" ));
  }

  else if( sample == "st" ){
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/ST_tW_antitop_5f_inclusiveDecays_13TeV*.root" , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/ST_tW_top_5f_inclusiveDecays_13TeV*.root"     , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/sttw_antitop_powheg*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/sttw_top_powheg*.root"     ));
  }

  else if( sample == "ww" ){
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/WWTo2L2Nu_13TeV-powheg*.root" , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/ww_2l2nu_powheg*.root" ));
  }

  else if( sample == "wz_inc" ){
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8*.root" , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/wz_2l2q_amcnlo*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/wz_3lnu_powheg*.root" ));
  }

  else if( sample == "zz_inc" ){
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/ZZTo2L2Nu_13TeV_powheg_pythia8*.root"              , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8*.root" , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/ZZTo4L_13TeV_powheg_pythia8*.root"                 , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/zz_2l2nu_powheg*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/zz_2l2q_amcnlo*.root"  ));
  }

  else if( sample == "wz" ){
	// ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/wz3lnu_25ns_powp8*.root"     , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/wz_3lnu_powheg*.root" ));
  }

  else if( sample == "zz" ){
	// ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/zz2l2nu_25ns_powp8*.root"        , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/zz_2l2nu_powheg*.root" ));
  }

  else if( sample == "vvv" ){
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8*.root"                 , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8*.root"                 , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8*.root"                 , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/www_incl_amcnlo*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/wwz_incl_amcnlo*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/wzz_incl_amcnlo*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/zzz_incl_mgmlm*.root"  ));
  }

  else if( sample == "ttv" ){
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/ttHJetToNonbb_M125_13TeV*.root"                                     , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8*.root"         , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8*.root"                  , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8*.root" , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8*.root"  , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8*.root"      , iter.c_str() ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-00/*.root"));
	ch->Add(Form("/hadoop/cms/store/user/cwelke/uaf8/dilepbabies/V08-07-00_ttw_ln_amcnlo/wjets*.root"));
	ch->Add(Form("/hadoop/cms/store/user/cwelke/uaf8/dilepbabies/V08-07-00_ttz_llnn_amcnlo/unknown*.root"));
	// ch->Add(Form("/hadoop/cms/store/user/cwelke/uaf8/dilepbabies/V08-07-00_ttg_incl_amcnlo/ttgjets_merged_ntuple*.root"));
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
