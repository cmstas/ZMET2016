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

	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-01/data_2016B_Prompt_em*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-07-01/data_2016C_Prompt_em*.root" ));

	
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/data_2016B_Prompt_ee*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/data_2016B_Prompt_em*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/data_2016B_Prompt_mm*.root" ));

	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/data_2016C_Prompt_ee*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/data_2016C_Prompt_em*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/data_2016C_Prompt_mm*.root" ));

	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/data_2016D_Prompt_ee*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/data_2016D_Prompt_em*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/data_2016D_Prompt_mm*.root" ));

	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/data_2016E_Prompt_ee*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/data_2016E_Prompt_em*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/data_2016E_Prompt_mm*.root" ));

	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/data_2016G_Prompt_ee*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/data_2016G_Prompt_em*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/data_2016G_Prompt_mm*.root" ));
	
	if( TString(selection).Contains("signalcontamination") ){
	  ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/t5zz_mgl*_mlm.root" , iter.c_str() ));
	}	
  }

  if ( sample == "fullscan" || sample == "signal1100200" || sample == "signal900" ){
	// ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/t5zz_mgl*_mlm*.root" , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/t5zz_80x_v2*.root"));
  }
  
  if ( sample == "fullscan_tchiwz" ){
	// ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/t5zz_mgl*_mlm*.root" , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/tchiwz_80x_v2*.root"));
  }

  else if ( sample == "All_MC" ){
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/dyjetsll_50ns_m1050nlo*.root"  , iter.c_str() ));
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/dyjetsll_50ns_m50nlo*.root"    , iter.c_str() ));
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/tt2lnu_50ns_php8*.root"         , iter.c_str() ));	
  }

  else if( sample == "zjets" ){
  	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/dy_m1050_amcnlo*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/dy_m50_amcnlo*.root"   ));
  }

  else if( sample == "zjetsmlm" ){

	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/dy_m50_mgmlm_ext1*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/dy_m1050_mgmlm*.root"    ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/dy_m50_mgmlm_ht100_ext1*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/dy_m50_mgmlm_ht200_ext1*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/dy_m50_mgmlm_ht400_ext1*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/dy_m50_mgmlm_ht600_ext1*.root" ));


  }

  else if( sample == "zjinc" ){
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/dyjetsll_m50inc*.root"    , iter.c_str() ));
  }

  else if( sample == "ttbar" ){
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/ttbar_dilep_mgmlm*.root" , iter.c_str() ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/ttbar_dilep_mgmlm*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/ttbar_1ltbr_mgmlm*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/ttbar_1ltop_mgmlm*.root" ));
  }

  else if( sample == "st" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/sttw_antitop_powheg*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/sttw_top_powheg*.root"     ));
  }

  else if( sample == "ww" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/ww_2l2nu_powheg*.root" ));
  }

  else if( sample == "wz_inc" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/wz_2l2q_amcnlo*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/wz_3lnu_powheg*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/wz_1l3n_amcnlo*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/wz_lnqq_amcnlo*.root" ));
  }

  else if( sample == "zz_inc" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/zz_2l2n_powheg*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/zz_2l2q_amcnlo*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/zz_4l_powheg*.root"   ));
  }

  else if( sample == "wz" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/wz_3lnu_powheg*.root" ));
  }

  else if( sample == "zz" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-01/zz_2l2n_powheg*.root" ));
  }

  else if( sample == "vvv" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/www_incl_amcnlo*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/wwz_incl_amcnlo*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/wzz_incl_amcnlo*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/zzz_incl_amcnlo*.root" ));
  }

  else if( sample == "ttv" ){
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-00/ttbb_incl_amcnlo*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-00/ttg_incl_mgmlm*.root"   ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-00/ttw_incl_mgmlm*.root"   )); // don't double count
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-00/ttz_incl_mgmlm*.root"   )); // don't double count
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-00/ttw_ln_amcnlo*.root"    ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-00/ttw_qq_amcnlo*.root"    ));

	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/ttz_2l2n_amcnlo*.root"  ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-09/ttz_qq_amcnlo*.root"    ));
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
  return 0