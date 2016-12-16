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

	
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016B_23sep2016rereco_ee*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016B_23sep2016rereco_em*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016B_23sep2016rereco_mm*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016C_23sep2016rereco_ee*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016C_23sep2016rereco_em*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016C_23sep2016rereco_mm*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016D_23sep2016rereco_ee*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016D_23sep2016rereco_em*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016D_23sep2016rereco_mm*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016E_23sep2016rereco_ee*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016E_23sep2016rereco_em*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016E_23sep2016rereco_mm*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016F_23sep2016rereco_ee*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016F_23sep2016rereco_em*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016F_23sep2016rereco_mm*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016G_23sep2016rereco_ee*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016G_23sep2016rereco_em*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016G_23sep2016rereco_mm*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016H_Prompt_ee*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016H_Prompt_em*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016H_Prompt_mm*.root" ));

	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016B_23sep2016rereco_ee*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016C_23sep2016rereco_ee*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016D_23sep2016rereco_ee*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016E_23sep2016rereco_ee*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016F_23sep2016rereco_ee*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016G_23sep2016rereco_ee*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016H_Prompt_ee*.root" ));

	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016B_23sep2016rereco_em*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016C_23sep2016rereco_em*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016D_23sep2016rereco_em*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016E_23sep2016rereco_em*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016F_23sep2016rereco_em*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016G_23sep2016rereco_em*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016H_Prompt_em*.root" ));

	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016B_23sep2016rereco_mm*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016C_23sep2016rereco_mm*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016D_23sep2016rereco_mm*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016E_23sep2016rereco_mm*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016F_23sep2016rereco_mm*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016G_23sep2016rereco_mm*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_data_2016H_Prompt_mm*.root" ));
	
	if( TString(selection).Contains("signalcontamination") ){
	  ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/t5zz_mgl*_mlm.root" , iter.c_str() ));
	}	
  }

  if ( sample == "datab" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016B_23sep2016rereco_ee*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016B_23sep2016rereco_em*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016B_23sep2016rereco_mm*.root" ));
  }

  if ( sample == "datac" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016C_23sep2016rereco_ee*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016C_23sep2016rereco_em*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016C_23sep2016rereco_mm*.root" ));
  }

  if ( sample == "datad" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016D_23sep2016rereco_ee*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016D_23sep2016rereco_em*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016D_23sep2016rereco_mm*.root" ));
  }

  if ( sample == "datae" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016E_23sep2016rereco_ee*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016E_23sep2016rereco_em*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016E_23sep2016rereco_mm*.root" ));
  }

  if ( sample == "dataf" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016F_23sep2016rereco_ee*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016F_23sep2016rereco_em*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016F_23sep2016rereco_mm*.root" ));
  }

  if ( sample == "datag" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016G_23sep2016rereco_ee*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016G_23sep2016rereco_em*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016G_23sep2016rereco_mm*.root" ));
  }

  if ( sample == "datah" ){
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016H_Prompt_ee*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016H_Prompt_em*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016H_Prompt_mm*.root" ));
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
  	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-10/dy_m1050_amcnlo*.root" ));
	ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-10/dy_m50_amcnlo*.root"   ));
  }

  else if( sample == "zjetsmlm" ){

	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_dy_m50_mgmlm_ext1*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_dy_m1050_mgmlm*.root"    ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_dy_m50_mgmlm_ht100_ext1*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_dy_m50_mgmlm_ht200_ext1*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_dy_m50_mgmlm_ht400_ext1*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_dy_m50_mgmlm_ht600_ext1*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_wz_2l2q_amcnlo*.root" ));

  }

  else if( sample == "zjinc" ){
	ch->Add(Form("/nfs-6/userdata/cwelke/ZMETbabies/%s/dyjetsll_m50inc*.root"    , iter.c_str() ));
  }

  else if( sample == "ttbar" ){
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/%s/ttbar_dilep_mgmlm*.root" , iter.c_str() ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_ttbar_dilep_mgmlm.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_ttbar_dilep_mgmlm_1.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_ttbar_dilep_mgmlm_2.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_ttbar_dilep_mgmlm_3.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_ttbar_1ltbr_mgmlm*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_ttbar_1ltop_mgmlm*.root" ));

  }

  else if( sample == "st" ){
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-10/sttw_antitop_powheg*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-10/sttw_top_powheg*.root"     ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_stt_antitop_lepdec_powheg.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_stt_top_lepdec_powheg.root"     ));
  }

  else if( sample == "ww" ){
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_ww_2l2nu_powheg*.root" ));
  }

  else if( sample == "wz_inc" ){
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_wz_3lnu_powheg*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-10/wz_1l3n_amcnlo*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-10/wz_lnqq_amcnlo*.root" ));
  }

  else if( sample == "zz_inc" ){
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_zz_2l2n_powheg*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-10/zz_2l2q_amcnlo*.root" ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-10/zz_4l_powheg*.root"   ));
  }

  else if( sample == "wz" ){
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_wz_3lnu_powheg*.root" ));
  }

  else if( sample == "zz" ){
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_zz_2l2n_powheg*.root" ));
  }

  else if( sample == "vvv" ){
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-10/www_incl_amcnlo*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_wwz_incl_amcnlo*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_wzz_incl_amcnlo*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_zzz_incl_amcnlo*.root" ));
  }

  else if( sample == "ttv" ){

	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-10/ttbb_incl_amcnlo*.root" ));

	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-10/ttgamma_incl_amcnlo*.root"   ));

	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-10/ttw_ln_amcnlo*.root"    ));
	// ch->Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-10/ttw_qq_amcnlo*.root"    ));

	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_ttz_2l2n_amcnlo_ext*.root" ));
	ch->Add(Form("/home/users/cwelke/ZMetbabyskims/V08-22-05/skim_ttz_qq_amcnlo*.root"       ));
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
