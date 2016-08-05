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
#include "TH3.h"
#include "TMath.h"
#include "TGraph.h"
// #include "TGraphAsymmErrors.h"

#include "Math/VectorUtil.h"

#include "templateLooper.h"

#include "../sharedCode/histTools.h"
#include "../sharedCode/ZMET.h"
#include "../sharedCode/METTemplateSelections.h"
#include "../sharedCode/AnalysisSelections.h"

#include "../../CORE/Tools/dorky/dorky.h"
#include "../../CORE/Tools/goodrun.h"
#include "../../CORE/Tools/badEventFilter.h"
#include "../../CORE/Tools/MT2/MT2.h"
#include "../../CORE/Tools/MT2/MT2Utility.h"

using namespace std;
using namespace duplicate_removal;

const bool debug = false;

const bool usejson                 = true;
const bool dovtxreweighting        = true;
const bool dotemplateprediction    = true;
const bool correctewkcontamination = true;
const bool dotemplatepredictionmc = false;

// Used for MC, to calculate nominal values
const bool doscalefactors       = true;
const bool do_btagscalefactors  = true;
const bool do2016METforFS       = true;

// print cutflow values
bool docutflow = true;

// these are for deriving signal systematics
bool doisrboost   = true;
bool heavy_up     = false;
bool light_up     = false;
bool jes_up       = false;
bool jes_dn       = false;
bool dofastsim    = true;
bool doleptonid   = true;
bool doleptoniso  = true;
bool doleptonreco = true;

float nlosplit = 0.0;
float nhisplit = 0.0;

templateLooper::templateLooper()
{
};

templateLooper::~templateLooper()
{
};

void templateLooper::ScanChain ( TChain * chain , const string iter , const string sample, const string selection ){

  // if( zmet.isData() )        cout << "Running on Data."        << endl;
  // else                       cout << "Running on MC.  "        << endl;

  double nsf_2jets_met_zveto = 0;
  double nof_2jets_met_zveto = 0;

  double nee = 0;
  double nmm = 0;
  double nll = 0;
  double nem = 0;

  double nem_2jets = 0;
  double nem_2jets_mll = 0;

  float allmet_nobreq = 0;
  float allmet_hasrealb = 0;
  float endmet_nobreq = 0;
  float endmet_hasrealb = 0;

  float allmet_btag_nobreq = 0;
  float allmet_btag_hasrealb = 0;
  float endmet_btag_nobreq = 0;
  float endmet_btag_hasrealb = 0;

  float unc_endmet_nobreq        = 0;
  float unc_endmet_hasrealb      = 0;
  float unc_endmet_btag_nobreq   = 0;
  float unc_endmet_btag_hasrealb = 0;
  
  float unc_allmet_nobreq        = 0;
  float unc_allmet_hasrealb      = 0;
  float unc_allmet_btag_nobreq   = 0;
  float unc_allmet_btag_hasrealb = 0;

  cout<<selection<<endl;
  
  if(      TString(sample).Contains("tchiwz"  ) ) bookHistos("tchiwz");
  else if( TString(sample).Contains("fullscan") ) bookHistos("t5zz");
  else bookHistos("t5zz");

  if(      TString(sample).Contains("tchiwz"  ) ) doisrboost = false;
  
  double npass = 0;

  float cutflow_events[10] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  float cutflow_errors[10] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  
  METTemplates mettemplates( selection );
  TH1F* currentMETTemplate = NULL;

  METTemplates mettemplates_ewk( selection );
  TH1F* currentMETTemplate_ewk = NULL;
  if( dotemplateprediction ){
	// mettemplates.loadTemplatesFromFile( Form("../output/%s/data%s_novtxweight_ptweight_templates.root", iter.c_str(), selection.c_str()), mettemplate_hists );
	mettemplates.loadTemplatesFromFile( Form("../output/%s/data%s_novtxweight_templates.root", iter.c_str(), selection.c_str()), mettemplate_hists );
	mettemplates.setBins( selection );

	if( correctewkcontamination ){
	  mettemplates_ewk.loadTemplatesFromFile( Form("../output/%s/data_withMC%s_novtxweight_templates.root", iter.c_str(), selection.c_str()), mettemplate_hists_ewk );
	  mettemplates_ewk.setBins( selection );
	}
	
  }
  if( dotemplatepredictionmc ){
	// mettemplates.loadTemplatesFromFile( Form("../output/%s/data_inclusive_templates.root", iter.c_str(), selection.c_str()), mettemplate_hists );
	mettemplates.loadTemplatesFromFile( Form("../output/%s/All_MC%s_novtxweight_templates.root", iter.c_str(), selection.c_str()), mettemplate_hists );
	mettemplates.setBins( selection );
  }
  
  // do this once per job
  
  // these are for deriving signal systematics
  if( TString(selection).Contains("noisr")       ) doisrboost  = false;
  if( TString(selection).Contains("heavy_UP")    ) heavy_up    = true;
  if( TString(selection).Contains("light_UP")    ) light_up    = true;
  if( TString(selection).Contains("jes_up")      ) jes_up      = true;
  if( TString(selection).Contains("jes_dn")      ) jes_dn      = true;
  if( TString(selection).Contains("nofastsim")   ) dofastsim   = false;
  if( TString(selection).Contains("noleptonid")  ) doleptonid  = false;
  if( TString(selection).Contains("noleptoniso") ) doleptoniso = false;

  // which json do you use?
  // const char* json_file = "/home/users/olivito/mt2_74x_dev/MT2Analysis/babymaker/jsons/Cert_246908-258750_13TeV_PromptReco_Collisions15_25ns_JSON_snt.txt"; // 1.3 fb
  // const char* json_file = "Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON_snt.txt"; // 2.1 fb
  // const char* json_file = "../../json/DCSONLY_json_160516_snt.txt"; // 2016 data
  // const char* json_file = "../../json/Cert_271036-274240_13TeV_PromptReco_Collisions16_JSON_snt.txt"; // 0.8 fb-1 for FSR
  // const char* json_file = "../../json/golden_json_080716_snt.txt"; // 4.0 fb, for preapproval
  // const char* json_file = "../../json/golden_json_080716_7p65fb_snt.txt"; // 7.65 fb, for preapproval
  const char* json_file = "../../json/golden_json_200716_12p9fb_snt.txt"; // 12.9 fb
  
  set_goodrun_file(json_file);

  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");

  TH1F * h_vtxweight = NULL;
  TFile * f_vtx = NULL;
  if( dovtxreweighting ){
	// f_vtx = TFile::Open("nvtx_ratio_6p26fb.root","READ");
	// h_vtxweight = (TH1F*)f_vtx->Get("h_vtx_ratio")->Clone("h_vtxweight");

	f_vtx = TFile::Open("pileup_jul21_nominalUpDown.root","READ");
	// f_vtx = TFile::Open("puWeights_nTrueInt.root","READ");
	h_vtxweight = (TH1F*)f_vtx->Get("weightsNominal")->Clone("h_vtxweight");
	h_vtxweight->SetDirectory(rootdir);
	f_vtx->Close();
  }

  TFile * f_sfweights = NULL;
  TH2D * h_isrweights = NULL;
  TH2D * h_bsfweights = NULL;
  TH2D * h_bsfweights_heavy_UP = NULL;
  TH2D * h_bsfweights_light_UP = NULL;

  TH2D * h_eleweights = NULL; // FS to Fullsim
  TH2D * h_eleweights_id = NULL;
  TH2D * h_eleweightsiso = NULL;
  TH2D * h_eleweights_reco = NULL;

  TH2D * h_muoweights = NULL; // FS to Fullsim; ID
  TH2D * h_muoweights_FS_iso = NULL; // FS to Fullsim; ISO
  TH2D * h_muoweights_FS_ip = NULL; // FS to Fullsim; IP

  TH2D * h_muoweights_id = NULL;
  TH2D * h_muoweights_ip = NULL;
  TH2D * h_muoweightsiso = NULL;
  // TGraphAsymmErrors * h_muoweights_HIP = NULL;
  TH1F * h_muoweights_HIP_hist = NULL;


  
  if( doscalefactors ){
	// electron reconstruction SFs
	f_sfweights  = TFile::Open("leptonSFs/electrons/egammaEffi.txt_SF2D.root","READ");
	h_eleweights_reco = (TH2D*) f_sfweights->Get("EGamma_SF2D") -> Clone("h_eleweights_reco");
	h_eleweights_reco->SetDirectory(rootdir);
	f_sfweights->Close();

	// electron ID/Iso SFs for Fullsim to Data
	f_sfweights  = TFile::Open("leptonSFs/electrons/scaleFactors.root","READ");
	h_eleweights_id = (TH2D*) f_sfweights->Get("GsfElectronToTightID2D3D") -> Clone("h_eleweights_id");
	h_eleweightsiso = (TH2D*) f_sfweights->Get("MVAVLooseElectronToMini")  -> Clone("h_eleweightsiso");
	h_eleweights_id->SetDirectory(rootdir);
	h_eleweightsiso->SetDirectory(rootdir);
	f_sfweights->Close();

	// muon id SF for Fullsim to Data
	f_sfweights  = TFile::Open("leptonSFs/muons/TnP_MuonID_NUM_MediumID_DENOM_generalTracks_VAR_map_pt_eta.root","READ");
	h_muoweights_id = (TH2D*) f_sfweights->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0") -> Clone("h_muoweights_id");
	h_muoweights_id	->SetDirectory(rootdir);
	f_sfweights->Close();
	
	// muon iso SF for Fullsim to Data
	f_sfweights  = TFile::Open("leptonSFs/muons/TnP_MuonID_NUM_MiniIsoTight_DENOM_MediumID_VAR_map_pt_eta.root","READ");
	h_muoweightsiso = (TH2D*) f_sfweights->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_Medium2016_pass") -> Clone("h_muoweightsiso");
	h_muoweightsiso	->SetDirectory(rootdir);
	f_sfweights->Close();

	// muon tracking SF due to HIPs for Fullsim to Data
	f_sfweights  = TFile::Open("leptonSFs/muons/general_tracks_and_early_general_tracks_corr_ratio.root","READ");
	h_muoweights_HIP_hist = (TH1F*) f_sfweights->Get("mutrksfptg10") -> Clone("h_muoweights_HIP_hist");
	h_muoweights_HIP_hist -> SetDirectory(rootdir);
	f_sfweights->Close();
	
	// f_sfweights  = TFile::Open("leptonSFs/muons/TnP_MuonID_NUM_TightIP2D_DENOM_MediumID_VAR_map_pt_eta.root","READ");
	// h_muoweights_HIP = (TGraphAsymmErrors*) f_sfweights->Get("ratio_eta") -> Clone("h_muoweights_HIP");
	// // h_muoweights_HIP -> SetDirectory(rootdir);
	// f_sfweights->Close();
	
	// muon ip SF for Fullsim to Data
	f_sfweights  = TFile::Open("leptonSFs/muons/TnP_MuonID_NUM_TightIP2D_DENOM_MediumID_VAR_map_pt_eta.root","READ");
	h_muoweights_ip = (TH2D*) f_sfweights->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_Medium2016_pass") -> Clone("h_muoweights_ip");
	h_muoweights_ip	->SetDirectory(rootdir);
	f_sfweights->Close();
	
	// SFs electrons for FS to Fullsim
	f_sfweights  = TFile::Open("leptonSFs/FS/sf_el_tightMVA_tight2DIP_vtxC_hitseq0.root","READ");
	h_eleweights = (TH2D*)f_sfweights->Get("histo2D") -> Clone("h_eleweights");
	h_eleweights->SetDirectory(rootdir);
	f_sfweights->Close();

	// SFs muons for FS to Fullsim, medium ID
	f_sfweights  = TFile::Open("leptonSFs/FS/sf_mu_medium.root","READ");
	h_muoweights = (TH2D*)f_sfweights->Get("histo2D") -> Clone("h_muoweights");
	h_muoweights->SetDirectory(rootdir);
	f_sfweights->Close();

	// SFs muons for FS to Fullsim, iso
	f_sfweights  = TFile::Open("leptonSFs/FS/sf_mu_mediumID_mini02.root","READ");
	h_muoweights_FS_iso = (TH2D*)f_sfweights->Get("histo2D") -> Clone("h_muoweights_FS_iso");
	h_muoweights_FS_iso->SetDirectory(rootdir);
	f_sfweights->Close();

	// SFs muons for FS to Fullsim, iso
	f_sfweights  = TFile::Open("leptonSFs/FS/sf_mu_tightIP2D.root","READ");
	h_muoweights_FS_ip = (TH2D*)f_sfweights->Get("histo2D") -> Clone("h_muoweights_FS_ip");
	h_muoweights_FS_ip->SetDirectory(rootdir);
	f_sfweights->Close();

	// SFs for signal, ISR and btag
	if(      TString(sample).Contains("tchiwz"  ) ) f_sfweights  = TFile::Open("nsig_weights_fullscan_tchiwz.root","READ");
	else if( TString(sample).Contains("fullscan") ) f_sfweights  = TFile::Open("nsig_weights_fullscan.root","READ");
	if( TString(sample).Contains("fullscan") ){
	  h_isrweights = (TH2D*)f_sfweights->Get("h_avg_weight_isr")   ->Clone("h_isrweights");
	  h_bsfweights = (TH2D*)f_sfweights->Get("h_avg_weight_btagsf")->Clone("h_bsfweights");
	  h_bsfweights_heavy_UP = (TH2D*)f_sfweights->Get("h_avg_weight_btagsf_heavy_UP")->Clone("h_bsfweights_heavy_UP");
	  h_bsfweights_light_UP = (TH2D*)f_sfweights->Get("h_avg_weight_btagsf_light_UP")->Clone("h_bsfweights_light_UP");
	  h_isrweights->SetDirectory(rootdir);
	  h_bsfweights->SetDirectory(rootdir);
	  h_bsfweights_heavy_UP->SetDirectory(rootdir);
	  h_bsfweights_light_UP->SetDirectory(rootdir);
	  f_sfweights->Close();
	}	

  }

  
  TObjArray *listOfFiles = chain->GetListOfFiles();
  unsigned int nEventsChain = 0;
  unsigned int nEvents = chain->GetEntries();
  nEventsChain = nEvents;
  unsigned int nEventsTotal = 0;
  unsigned int nDuplicates = 0;

  if(debug) cout << "Begin file loop" << endl;

  int badevents = 0;
  
  // file loop
  TIter fileIter(listOfFiles);
  TFile* currentFile = 0;
  while ( (currentFile = (TFile*) fileIter.Next()) ){

	TFile f(currentFile->GetTitle());
    TTree *tree = dynamic_cast<TTree*>(f.Get("t"));
    zmet.Init(tree);

    // event loop
    //unsigned int nEvents = tree->GetEntries();
    nEvents = tree->GetEntries();	
	cout<<"Processing File: "<<TString(currentFile->GetTitle())<<endl;

	
    for (unsigned int event = 0 ; event < nEvents; ++event){
   
	  zmet.GetEntry(event);
      ++nEventsTotal;

	  if (nEventsTotal % 100000 == 0){ // progress feedback to user
	  	if (isatty(1)){ // xterm magic from L. Vacavant and A. Cerri               
          printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
                 "\033[0m\033[32m <---\033[0m\015", (float)nEventsTotal/(nEventsChain*0.01));
          fflush(stdout);
        }
      }

// 	  if(
// ( zmet.run() == 273502 && zmet.lumi() ==          1034 && zmet.evt() ==    1253949348) ||
// ( zmet.run() == 274241 && zmet.lumi() ==          1061 && zmet.evt() ==    1716571168) ||
// ( zmet.run() == 274250 && zmet.lumi() ==           359 && zmet.evt() ==     714603732) ||
// ( zmet.run() == 274251 && zmet.lumi() ==           208 && zmet.evt() ==     323847967) ||
// ( zmet.run() == 274284 && zmet.lumi() ==            80 && zmet.evt() ==     161552931) ||
// ( zmet.run() == 274388 && zmet.lumi() ==           203 && zmet.evt() ==     395052423) ||
// ( zmet.run() == 274442 && zmet.lumi() ==           464 && zmet.evt() ==     816377062) ||
// ( zmet.run() == 274998 && zmet.lumi() ==           666 && zmet.evt() ==    1220445466) ||
// ( zmet.run() == 275311 && zmet.lumi() ==           836 && zmet.evt() ==    1012082659) ||
// ( zmet.run() == 275847 && zmet.lumi() ==           224 && zmet.evt() ==     301510004) ||
// ( zmet.run() == 275847 && zmet.lumi() ==           911 && zmet.evt() ==    1176469748) ||
// ( zmet.run() == 276543 && zmet.lumi() ==           666 && zmet.evt() ==    1215096543) ||
// ( zmet.run() == 276587 && zmet.lumi() ==           483 && zmet.evt() ==     720558255) ||
// ( zmet.run() == 276775 && zmet.lumi() ==           204 && zmet.evt() ==     241758803) ||
// ( zmet.run() == 276775 && zmet.lumi() ==          1051 && zmet.evt() ==    1829473072) ||
// ( zmet.run() == 276808 && zmet.lumi() ==           516 && zmet.evt() ==     966247493) ||
// ( zmet.run() == 276811 && zmet.lumi() ==           677 && zmet.evt() ==    1234391680) 
// 		 ){

//   		cout << setw(10)<<zmet.run()<<" | ";
//   		cout << setw(10)<<zmet.lumi()<<" | ";
//   		cout << setw(10)<<zmet.evt()<<" | ";
//   		cout << setw(10)<<zmet.njets()<<" | ";
// 		cout << setw(10)<<zmet.nlep()<<" | ";
// 	  	cout << setw(10)<<(zmet.nlep()+zmet.nveto_leptons()-2)<<" | ";
// 		cout << setw(10)<<zmet.hyp_type()<<" | ";
// 		cout << setw(10)<<zmet.evt_type()<<" | ";
// 		cout << setw(10)<<zmet.lep_pt().at(0)<<" | ";
// 		cout << setw(10)<<zmet.lep_pt().at(1)<<" | ";
// 		cout << setw(10)<<zmet.lep_eta().at(0)<<" | ";
// 		cout << setw(10)<<zmet.lep_eta().at(1)<<" | ";
// 		cout << setw(10)<<zmet.dRll()<<" | ";
// 		cout << setw(10)<<zmet.dilmass()<<" | ";
// 	  	cout << setw(10)<<zmet.mt2()<<" | ";
// 	  	cout << setw(10)<<zmet.dphi_metj1()<<" | ";
// 		cout<<zmet.ht()<<" | ";
// 		cout<<zmet.mlbmin()<<" | ";
// 		cout << setw(10)<<zmet.met_T1CHS_miniAOD_CORE_pt()<<" | ";
// 		cout << setw(10)<<passMETFilters()<<" | ";
// 		cout << setw(10)<<(zmet.HLT_DoubleMu_nonDZ() || zmet.HLT_DoubleMu_tk_nonDZ() || zmet.HLT_DoubleMu_noiso() )<<" | ";
// 		cout << setw(10)<<(zmet.HLT_DoubleEl_DZ_2()  || zmet.HLT_DoubleEl_noiso()                                 )<<" | ";
// 		cout << setw(10)<<(zmet.HLT_MuEG()           || zmet.HLT_MuEG_2()            || zmet.HLT_MuEG_noiso()     )<<" | ";
// 		cout<<endl;

// 	  }
	  
	  //~-~-~-~-~-~-~-~~-//
	  //Stitch DY samples//
	  //~-~-~-~-~-~-~-~-~//
	  if( sample == "zjetsmlm" ){
	  	if( TString(currentFile->GetTitle()).Contains("dy_m50_mgmlm_ext1") ){
	  	  if( zmet.gen_ht()    > 100 ) continue;
	  	}
	  }	

	  if( dotemplateprediction && (sample == "vvv" || sample == "ttv") ){
		bool hasrealmet = false;
		bool realzpair  = false;
		for( size_t genind = 0; genind < zmet.genPart_motherId().size(); genind++ ){
		  if( (abs(zmet.genPart_motherId().at(genind)) == 24 || zmet.genPart_motherId().at(genind) == 23) &&
			  zmet.genPart_status().at(genind) == 23 &&
			  (abs(zmet.genPart_pdgId().at(genind))==12 ||
			   abs(zmet.genPart_pdgId().at(genind))==14 ||
			   abs(zmet.genPart_pdgId().at(genind))==16) ){
			// cout<<"mom "<<zmet.genPart_motherId().at(genind) << " | stat "<< zmet.genPart_status().at(genind) <<  " | id "<< zmet.genPart_pdgId().at(genind) << endl;
			hasrealmet = true;
		  }
		  if( ( zmet.genPart_motherId().at(genind) == 23 ||
				zmet.genPart_grandmaId().at(genind) == 23 ) &&   // mother is a Z, or grandmother
			  ( zmet.genPart_status().at(genind) == 1 ||
				zmet.genPart_status().at(genind) == 23 ) &&     // status of lepton is 1 or 23
			  (abs(zmet.genPart_pdgId().at(genind))==11 ||  // is an electron
			   abs(zmet.genPart_pdgId().at(genind))==13) ){ // is a muon
			realzpair = true;
		  }
		}
		if( !hasrealmet || !realzpair ) continue;
	  }
	  	  
	  
	  if( zmet.isData() ){
		if(  usejson && !goodrun(zmet.run(), zmet.lumi()) ) continue;
		if( !usejson && !zmet.evt_passgoodrunlist()       ) continue;
	  }
	  
	  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~//
	  //Deal with duplicates in data//
	  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~//
	  if( zmet.isData() ) {
		DorkyEventIdentifier id(zmet.run(), zmet.evt(), zmet.lumi());
		if (is_duplicate(id) ){
		  ++nDuplicates;
		  continue;
		}
      }	  
	  
	  //-~-~-~-~-~-~-~-~-~-~-~-//
	  //Deal with event weights//
	  //-~-~-~-~-~-~-~-~-~-~-~-//
	  float weight = 1.0;
	  if( zmet.isData() ){
		weight = 1.0;
	  }else if( !zmet.isData() ){
		weight *= zmet.evt_scale1fb();
	  	if( TString(currentFile->GetTitle()).Contains("t5zz") || TString(currentFile->GetTitle()).Contains("tchiwz") ){
		  weight *= 12.9;
		}
	  	// if( TString(currentFile->GetTitle()).Contains("dy_m50_mgmlm_ext1") ){
		//   weight *= 3.72;
		// }
	  }
	  
	  if( !zmet.isData() && dovtxreweighting ){
	  	// if( !TString(currentFile->GetTitle()).Contains("t5zz") ){
		  // weight *= h_vtxweight->GetBinContent(h_vtxweight->FindBin(zmet.nVert()));		
		  weight *= h_vtxweight->GetBinContent(h_vtxweight->FindBin(zmet.nTrueInt()));		
		// }
	  }
	  

	  float event_met_pt = zmet.met_T1CHS_miniAOD_CORE_pt();
	  float event_met_ph = zmet.met_T1CHS_miniAOD_CORE_phi();

	  if( jes_up ){
		event_met_pt = zmet.met_T1CHS_miniAOD_CORE_up_pt();
		event_met_ph = zmet.met_T1CHS_miniAOD_CORE_up_phi();

	  }else if( jes_dn ){
		event_met_pt = zmet.met_T1CHS_miniAOD_CORE_dn_pt();
		event_met_ph = zmet.met_T1CHS_miniAOD_CORE_dn_phi();

	  }else{
		event_met_pt = zmet.met_T1CHS_miniAOD_CORE_pt();
		event_met_ph = zmet.met_T1CHS_miniAOD_CORE_phi();
	  }

	  if( do2016METforFS ){
	  	if( TString(currentFile->GetTitle()).Contains("t5zz") || TString(currentFile->GetTitle()).Contains("tchiwz") ){
		  event_met_pt = (zmet.met_T1CHS_miniAOD_CORE_pt() + zmet.met_genPt())/2.0;
		}
	  }	  

	  if( docutflow ){
		if( TString(currentFile->GetTitle()).Contains("t5zz")   && !(zmet.mass_gluino() == 1450 && zmet.mass_LSP() == 1000) )continue;
		if( TString(currentFile->GetTitle()).Contains("tchiwz") && !(zmet.mass_gluino() == 300 && zmet.mass_LSP() == 75    ) )continue;
		// cout<<zmet.mass_gluino()<<" | "<<zmet.mass_LSP()<<endl;
		cutflow_events[0] = zmet.evt_nEvts()*zmet.evt_scale1fb()*12.9;
		cutflow_errors[0] = sqrt(zmet.evt_nEvts())*zmet.evt_scale1fb()*12.9;
	  }
	  
	  //~-~-~-~-~-~-~-~-//
      // event selection// 
	  //~-~-~-~-~-~-~-~-//
	  if( zmet.nlep()                        < 2         ) continue; // require at least 2 good leptons
	  if( zmet.lep_pt().at(0)                < 25        ) continue; // leading lep pT > 25 GeV
	  if( zmet.lep_pt().at(1)                < 20        ) continue; // tailing lep pT > 20 GeV

	  if( abs(zmet.lep_p4().at(0).eta())     > 2.4       ) continue; // eta < 2.4
	  if( abs(zmet.lep_p4().at(1).eta())     > 2.4       ) continue; // eta < 2.4
	  if( abs(zmet.lep_p4().at(0).eta())     > 1.4 &&
	  	  abs(zmet.lep_p4().at(0).eta())     < 1.6       ) continue; 
	  if( abs(zmet.lep_p4().at(1).eta())     > 1.4 &&
	  	  abs(zmet.lep_p4().at(1).eta())     < 1.6       ) continue; // veto xition region
	  if( zmet.dRll() < 0.1                              ) continue; // dr between leptons > 0.1
	  if( !(zmet.hyp_type() == 0 ||          
	  		zmet.hyp_type() == 1 ||          
	  		zmet.hyp_type() == 2 )                       ) continue; // require explicit dilepton event
	  if( !(zmet.evt_type() == 0 )                       ) continue; // require opposite sig

	  // scale factors
	  float lepton_SF = 1.0;
	  if( !zmet.isData() && do_btagscalefactors && !(TString(currentFile->GetTitle()).Contains("t5zz") || TString(currentFile->GetTitle()).Contains("tchiwz") ) ){
	  	weight *= zmet.weight_btagsf();		
	  }
	  //flat trigger effs
	  if( !zmet.isData() ){
		if( zmet.hyp_type() == 0 ) weight *= 0.963;
		if( zmet.hyp_type() == 1 ) weight *= 0.947;
		if( zmet.hyp_type() == 2 ) weight *= 0.899;
	  }
	  
	  // deal with other event weights
	  if( !zmet.isData() && doscalefactors ){

		// btag sf variation
		if( !zmet.isData() && do_btagscalefactors && (TString(currentFile->GetTitle()).Contains("t5zz") || TString(currentFile->GetTitle()).Contains("tchiwz") ) ){
		  if(heavy_up){
			weight *= zmet.weight_btagsf_heavy_UP();		
			weight *= 1./h_bsfweights_heavy_UP->GetBinContent(h_bsfweights_heavy_UP->FindBin( zmet.mass_gluino(), zmet.mass_LSP() ));

		  }else if(light_up){
			weight *= zmet.weight_btagsf_light_UP();		
			weight *= 1./h_bsfweights_light_UP->GetBinContent(h_bsfweights_light_UP->FindBin( zmet.mass_gluino(), zmet.mass_LSP() ));

		  }else{
			weight *= zmet.weight_btagsf();		
			weight *= 1./h_bsfweights->GetBinContent(h_bsfweights->FindBin( zmet.mass_gluino(), zmet.mass_LSP() ));
		  }
		}
		
		// cout<<"btagsf: "<<zmet.weight_btagsf()<<endl;
		
		if( doisrboost ){
		  weight *= zmet.isr_weight();
		  weight *= 1./h_isrweights->GetBinContent(h_isrweights->FindBin( zmet.mass_gluino(), zmet.mass_LSP() ));
		}

		// cout<<"leptsf: "<<lepton_SF<<endl;

		float min_leppt1  = min( 110.0, (double)zmet.lep_pt().at(0));
		float min_leppt2  = min( 110.0, (double)zmet.lep_pt().at(1));
		float abs_lepeta1 = abs(zmet.lep_eta().at(0));
		float abs_lepeta2 = abs(zmet.lep_eta().at(1));

		// fullsim to data scale factors
		if( doleptonid ){
		  // TH2D * h_eleweights_id = NULL;
		  if( abs(zmet.lep_pdgId().at(0)) == 11 ) lepton_SF *= h_eleweights_id->GetBinContent(h_eleweights_id->FindBin( min_leppt1, abs_lepeta1 ));
		  if( abs(zmet.lep_pdgId().at(1)) == 11 ) lepton_SF *= h_eleweights_id->GetBinContent(h_eleweights_id->FindBin( min_leppt2, abs_lepeta2 ));
		  // TH2D * h_muoweights_id = NULL;
		  if( abs(zmet.lep_pdgId().at(0)) == 13 ) lepton_SF *= h_muoweights_id->GetBinContent(h_muoweights_id->FindBin( min_leppt1, abs_lepeta1 ));
		  if( abs(zmet.lep_pdgId().at(1)) == 13 ) lepton_SF *= h_muoweights_id->GetBinContent(h_muoweights_id->FindBin( min_leppt2, abs_lepeta2 ));
		  // TH2D * h_muoweights_ip = NULL;
		  if( abs(zmet.lep_pdgId().at(0)) == 13 ) lepton_SF *= h_muoweights_ip->GetBinContent(h_muoweights_ip->FindBin( min_leppt1, abs_lepeta1 ));
		  if( abs(zmet.lep_pdgId().at(1)) == 13 ) lepton_SF *= h_muoweights_ip->GetBinContent(h_muoweights_ip->FindBin( min_leppt2, abs_lepeta2 ));
		}

		// cout<<"leptsf_id: "<<lepton_SF<<endl;
		
		if( doleptoniso ){
		  // TH2D * h_eleweightsiso = NULL;
		  if( abs(zmet.lep_pdgId().at(0)) == 11 ) lepton_SF *= h_eleweightsiso->GetBinContent(h_eleweightsiso->FindBin( min_leppt1, abs_lepeta1 ));
		  if( abs(zmet.lep_pdgId().at(1)) == 11 ) lepton_SF *= h_eleweightsiso->GetBinContent(h_eleweightsiso->FindBin( min_leppt2, abs_lepeta2 ));
		  // TH2D * h_muoweightsiso = NULL;
		  if( abs(zmet.lep_pdgId().at(0)) == 13 ) lepton_SF *= h_muoweightsiso->GetBinContent(h_muoweightsiso->FindBin( min_leppt1, abs_lepeta1 ));
		  if( abs(zmet.lep_pdgId().at(1)) == 13 ) lepton_SF *= h_muoweightsiso->GetBinContent(h_muoweightsiso->FindBin( min_leppt2, abs_lepeta2 ));
		}

		// cout<<"leptsf_id: "<<lepton_SF<<endl;

		if( doleptonreco ){
		  // TH2D * h_eleweights_reco = NULL;
		  if( abs(zmet.lep_pdgId().at(0)) == 11 ) lepton_SF *= h_eleweights_reco->GetBinContent(h_eleweights_reco->FindBin( zmet.lep_eta().at(0), min_leppt1 ));
		  if( abs(zmet.lep_pdgId().at(1)) == 11 ) lepton_SF *= h_eleweights_reco->GetBinContent(h_eleweights_reco->FindBin( zmet.lep_eta().at(1), min_leppt2 ));
		  // TH1F* h_muoweights_HIP_hist = NULL;
		  if( abs(zmet.lep_pdgId().at(0)) == 13 ) lepton_SF *= h_muoweights_HIP_hist->GetBinContent(h_muoweights_HIP_hist->FindBin( zmet.lep_eta().at(0) ) );
		  if( abs(zmet.lep_pdgId().at(1)) == 13 ) lepton_SF *= h_muoweights_HIP_hist->GetBinContent(h_muoweights_HIP_hist->FindBin( zmet.lep_eta().at(1) ) );
		}

	    // cout<<"leptsf_rc: "<<lepton_SF<<endl;

		if( dofastsim && (TString(currentFile->GetTitle()).Contains("t5zz") || TString(currentFile->GetTitle()).Contains("tchiwz") ) ){
		  // TH2D * h_eleweights = NULL; // FS to Fullsim
		  if( abs(zmet.lep_pdgId().at(0)) == 11 ) lepton_SF *= h_eleweights->GetBinContent(h_eleweights->FindBin( min_leppt1, abs_lepeta1 ));
		  if( abs(zmet.lep_pdgId().at(1)) == 11 ) lepton_SF *= h_eleweights->GetBinContent(h_eleweights->FindBin( min_leppt2, abs_lepeta2 ));
		  // TH2D * h_muoweights = NULL; // FS to Fullsim; ID
		  if( abs(zmet.lep_pdgId().at(0)) == 13 ) lepton_SF *= h_muoweights->GetBinContent(h_muoweights->FindBin( min_leppt1, abs_lepeta1 ));
		  if( abs(zmet.lep_pdgId().at(1)) == 13 ) lepton_SF *= h_muoweights->GetBinContent(h_muoweights->FindBin( min_leppt2, abs_lepeta2 ));
		  // TH2D * h_muoweights_FS_iso = NULL; // FS to Fullsim; ISO
		  if( abs(zmet.lep_pdgId().at(0)) == 13 ) lepton_SF *= h_muoweights_FS_iso->GetBinContent(h_muoweights_FS_iso->FindBin( min_leppt1, abs_lepeta1 ));
		  if( abs(zmet.lep_pdgId().at(1)) == 13 ) lepton_SF *= h_muoweights_FS_iso->GetBinContent(h_muoweights_FS_iso->FindBin( min_leppt2, abs_lepeta2 ));
		  // TH2D * h_muoweights_FS_ip = NULL; // FS to Fullsim; IP
		  if( abs(zmet.lep_pdgId().at(0)) == 13 ) lepton_SF *= h_muoweights_FS_ip->GetBinContent(h_muoweights_FS_ip->FindBin( min_leppt1, abs_lepeta1 ));
		  if( abs(zmet.lep_pdgId().at(1)) == 13 ) lepton_SF *= h_muoweights_FS_ip->GetBinContent(h_muoweights_FS_ip->FindBin( min_leppt2, abs_lepeta2 ));
		}

	    // cout<<"leptsf_fs: "<<lepton_SF<<endl<<endl;
		
		weight *= lepton_SF;		
		// weightafter = weight; 
	  }	  
	  
	  if( docutflow ){
		if( zmet.hyp_type() != 2 ){
		  if( TString(selection).Contains("SR_ATLAS") && !(zmet.lep_pt().at(0) > 50 && zmet.lep_pt().at(1) > 25) ) continue;
			cutflow_events[1] += weight; cutflow_errors[1] += weight*weight;
		  if( zmet.dilmass() > 81 && zmet.dilmass() < 101 ){
			cutflow_events[2] += weight; cutflow_errors[2] += weight*weight;

			if( TString(selection).Contains("SR_ATLAS") && zmet.njets() > 1 ){
			  cutflow_events[3] += weight; cutflow_errors[3] += weight*weight;
			  if( (zmet.ht() + zmet.lep_pt().at(0) + zmet.lep_pt().at(1)) > 600 ){
				cutflow_events[4] += weight; cutflow_errors[4] += weight*weight;
				if( event_met_pt > 225 ){
				  cutflow_events[5] += weight; cutflow_errors[5] += weight*weight;
				  if( acos(cos(event_met_ph-zmet.jets_p4().at(0).phi())) > 0.4 && acos(cos(event_met_ph-zmet.jets_p4().at(1).phi())) > 0.4 ){
					cutflow_events[6] += weight; cutflow_errors[6] += weight*weight;
				  }
				}
			  }
			}
			
			if( TString(selection).Contains("SRB") && zmet.njets() > 3 ){
			  cutflow_events[3] += weight; cutflow_errors[3] += weight*weight;
			  if( TString(selection).Contains("withb") && zmet.nBJetMedium() >= 1 ){
				cutflow_events[4] += weight; cutflow_errors[4] += weight*weight;
				if( event_met_pt > 100 ){
				  cutflow_events[5] += weight; cutflow_errors[5] += weight*weight;
				  if( event_met_pt > 150 ){
					cutflow_events[6] += weight; cutflow_errors[6] += weight*weight;
					if( event_met_pt > 225 ){
					  cutflow_events[7] += weight; cutflow_errors[7] += weight*weight;
					  if( event_met_pt > 300 ){
						cutflow_events[8] += weight; cutflow_errors[8] += weight*weight;
					  }
					}
				  }
				}
			  }

			  if( TString(selection).Contains("bveto") && zmet.nBJetMedium() == 0 ){
				cutflow_events[4] += weight; cutflow_errors[4] += weight*weight;
				if( event_met_pt > 100 ){
				  cutflow_events[5] += weight; cutflow_errors[5] += weight*weight;
				  if( event_met_pt > 150 ){
					cutflow_events[6] += weight; cutflow_errors[6] += weight*weight;
					if( event_met_pt > 225 ){
					  cutflow_events[7] += weight; cutflow_errors[7] += weight*weight;
					  if( event_met_pt > 300 ){
						cutflow_events[8] += weight; cutflow_errors[8] += weight*weight;
					  }
					}
				  }
				}
			  }
			}			
		  }
		}

		if( zmet.hyp_type() != 2 ){
		  if( TString(selection).Contains("SR_EWK") ){
			if( (zmet.nveto_leptons() < 1 && zmet.nlep() == 2) && !(zmet.lep_pt().at(0) > 25 && zmet.lep_pt().at(1) > 20) ) continue;
			cutflow_events[1] += weight; cutflow_errors[1] += weight*weight;
			if( zmet.dilmass() > 81 && zmet.dilmass() < 101 ){
			  cutflow_events[2] += weight; cutflow_errors[2] += weight*weight;
			  if( zmet.njets() > 1 ){
				cutflow_events[3] += weight; cutflow_errors[3] += weight*weight;
				if( zmet.nBJetMedium() == 0 ){
				  cutflow_events[4] += weight; cutflow_errors[4] += weight*weight;
				  if( zmet.dphi_metj1() > 1.0 ){
					cutflow_events[5] += weight; cutflow_errors[5] += weight*weight;
					// if( zmet.mt2() > 80  ){
					if( MT2( event_met_pt, event_met_ph, zmet.lep_p4().at(0), zmet.lep_p4().at(1), 0.0, false ) > 80 ){
					  cutflow_events[6] += weight; cutflow_errors[6] += weight*weight;
					  if( event_met_pt > 150 ){
						cutflow_events[7] += weight; cutflow_errors[7] += weight*weight;
						if( event_met_pt > 225 ){
						  cutflow_events[8] += weight; cutflow_errors[8] += weight*weight;
						  if( event_met_pt > 300 ){
							cutflow_events[9] += weight; cutflow_errors[9] += weight*weight;
						  }
						}
					  }
					}
				  }
				}			
			  }
			}
		  }	  	  
		}
	  }
	  
	  // after scale factors and cutflows
	  if( !passSignalRegionSelection(selection) ) continue;
	  if( !passMETFilters()                     ) continue;

	  fillHist( "event", "mll"  , "inclusive", zmet.dilmass()  , weight );
	  if( (zmet.dilmass() > 81 && zmet.dilmass() < 101) ) fillHist( "event", "nVert", "inclusive", zmet.nVert()  , weight );

	  if( !(TString(currentFile->GetTitle()).Contains("t5zz") || TString(currentFile->GetTitle()).Contains("tchiwz")) && zmet.isData() ){		  
		if( !((( zmet.HLT_DoubleMu_nonDZ() || zmet.HLT_DoubleMu_tk_nonDZ() || zmet.HLT_DoubleMu_noiso() ) && zmet.hyp_type() == 1 ) ||
			  (( zmet.HLT_DoubleEl_DZ_2()  || zmet.HLT_DoubleEl_noiso()                                 ) && zmet.hyp_type() == 0 ) ||
			  (( zmet.HLT_MuEG()           || zmet.HLT_MuEG_2()            || zmet.HLT_MuEG_noiso()     ) && zmet.hyp_type() == 2 )
			  )           ) continue;
	  }
	  
	  fillHist( "event", "mll"    , "passtrig" , zmet.dilmass()  , weight );
	  if( zmet.njets() > 1 ){
		if( zmet.hyp_type() == 2 ) nem_2jets += weight;	  
		fillHist( "event", "metgt1jet" , "inclusive", event_met_pt        , weight );
	  }

	  if( (event_met_pt > 225) ){
		if( TString(selection).Contains("SR_ATLAS") && event_met_pt > 225 )fillHist( "event", "mll_fkw", "passtrig", zmet.dilmass()   , weight );	  
		// else  fillHist( "event", "mll_fkw", "passtrig", zmet.dilmass()   , weight );	  
	  }

	  // synch with edgers in off Z region
	  if( zmet.njets() > 1 && event_met_pt > 150 && (zmet.dilmass() < 81 || zmet.dilmass() > 101 ) && zmet.dilmass() > 20){
		if( zmet.hyp_type() == 0 || zmet.hyp_type() == 1 ) nsf_2jets_met_zveto ++;
		if( zmet.hyp_type() == 2                         ) nof_2jets_met_zveto ++;
	  }

	  if( !(zmet.dilmass() > 81 && zmet.dilmass() < 101) ) continue; // onZ

	  if( zmet.njets() > 1 && zmet.hyp_type() == 2 ) nem_2jets_mll += weight;	  

	  //-~-~-~-~-~-~-~-~-//
	  //Fill event  hists//
	  //-~-~-~-~-~-~-~-~-//	  
	  fillHist( "event", "njets"  , "passtrig", zmet.njets()        , weight );
	  fillHist( "event", "nbjets" , "passtrig", zmet.nBJetMedium()  , weight );
	  fillHist( "event", "met"    , "passtrig", event_met_pt        , weight );
	  fillHist( "event", "met_raw", "passtrig", zmet.met_rawPt()    , weight );
	  fillHist( "event", "ht"     , "passtrig", zmet.ht()           , weight );
	  fillHist( "event", "ptl1"   , "passtrig", zmet.lep_pt().at(0) , weight );	  
	  fillHist( "event", "ptl2"   , "passtrig", zmet.lep_pt().at(1) , weight );	  

	  fillHist( "event", "l1phi"   , "passtrig", zmet.lep_p4().at(0).phi() , weight );	  
	  fillHist( "event", "l2phi"   , "passtrig", zmet.lep_p4().at(1).phi() , weight );	  
	  fillHist( "event", "l1eta"   , "passtrig", zmet.lep_p4().at(0).eta() , weight );	  
	  fillHist( "event", "l2eta"   , "passtrig", zmet.lep_p4().at(1).eta() , weight );	  
	  fillHist( "event", "nVert"   , "passtrig", zmet.nVert()        , weight );	  
	  fillHist( "event", "ptdil"  , "passtrig", zmet.dilpt()        , weight );	  
	  fillHist( "event", "ptlep1lep2"  , "passtrig", zmet.lep_pt().at(0) + zmet.lep_pt().at(1), weight );	  
	  fillHist( "event", "metphi" , "passtrig", event_met_ph        , weight );	  
	  fillHist( "event", "metphir", "passtrig", zmet.met_rawPhi()   , weight );	  

	  if( !zmet.isData() ) fillHist( "event", "nVert_true"  , "passtrig", zmet.nTrueInt() , weight );	  

	  if( zmet.njets() > 0 ) fillHist( "event", "ptj1"   , "passtrig", zmet.jets_p4().at(0).pt() , weight );	  
	  if( zmet.njets() > 1 ) fillHist( "event", "ptj2"   , "passtrig", zmet.jets_p4().at(1).pt() , weight );	  
	  if( zmet.njets() > 2 ) fillHist( "event", "ptj3"   , "passtrig", zmet.jets_p4().at(2).pt() , weight );	  
	  if( zmet.njets() > 3 ) fillHist( "event", "ptj4"   , "passtrig", zmet.jets_p4().at(3).pt() , weight );	  

	  // if( zmet.njets() > 0 ) fillHist( "event", "csv1"   , "passtrig", zmet.jets_csv().at(0) , weight );	  
	  // if( zmet.njets() > 1 ) fillHist( "event", "csv2"   , "passtrig", zmet.jets_csv().at(1) , weight );	  
	  // if( zmet.njets() > 2 ) fillHist( "event", "csv3"   , "passtrig", zmet.jets_csv().at(2) , weight );	  
	  // if( zmet.njets() > 3 ) fillHist( "event", "csv4"   , "passtrig", zmet.jets_csv().at(3) , weight );	  

	  //start here
	  fillHist( "event", "mbb_bpt", "passtrig", zmet.mbb_bpt()   , weight );	  
	  fillHist( "event", "mbb_csv", "passtrig", zmet.mbb_csv()   , weight );	  
	  fillHist( "event", "mt2j", "passtrig", zmet.mt2j()   , weight );	  
	  fillHist( "event", "mt2b", "passtrig", zmet.mt2b()   , weight );	  
	  fillHist( "event", "mt2" , "passtrig", zmet.mt2()    , weight );	  
	  fillHist( "event", "mjj" , "passtrig", zmet.mjj()    , weight );	  

	  fillHist( "event", "dphijj" , "passtrig", zmet.dphi_jj()  , weight );	  
	  fillHist( "event", "detajj" , "passtrig", zmet.deta_jj()  , weight );	  
	  fillHist( "event", "dRjj"   , "passtrig", zmet.dR_jj()    , weight );	  


	  // fillHist( "event", "chpfcands_0013_pt" , "passtrig", zmet.chpfcands_0013_pt()  , weight );	  
	  // fillHist( "event", "chpfcands_1316_pt" , "passtrig", zmet.chpfcands_1316_pt()  , weight );	  
	  // fillHist( "event", "chpfcands_1624_pt" , "passtrig", zmet.chpfcands_1624_pt()  , weight );	  
	  // fillHist( "event", "chpfcands_2430_pt" , "passtrig", zmet.chpfcands_2430_pt()  , weight );	  
	  // fillHist( "event", "chpfcands_30in_pt" , "passtrig", zmet.chpfcands_30in_pt()  , weight );	  
	  // fillHist( "event", "phpfcands_0013_pt" , "passtrig", zmet.phpfcands_0013_pt()  , weight );	  
	  // fillHist( "event", "phpfcands_1316_pt" , "passtrig", zmet.phpfcands_1316_pt()  , weight );	  
	  // fillHist( "event", "phpfcands_1624_pt" , "passtrig", zmet.phpfcands_1624_pt()  , weight );	  
	  // fillHist( "event", "phpfcands_2430_pt" , "passtrig", zmet.phpfcands_2430_pt()  , weight );	  
	  // fillHist( "event", "phpfcands_30in_pt" , "passtrig", zmet.phpfcands_30in_pt()  , weight );	  
	  // fillHist( "event", "nupfcands_0013_pt" , "passtrig", zmet.nupfcands_0013_pt()  , weight );	  
	  // fillHist( "event", "nupfcands_1316_pt" , "passtrig", zmet.nupfcands_1316_pt()  , weight );	  
	  // fillHist( "event", "nupfcands_1624_pt" , "passtrig", zmet.nupfcands_1624_pt()  , weight );	  
	  // fillHist( "event", "nupfcands_2430_pt" , "passtrig", zmet.nupfcands_2430_pt()  , weight );	  
	  // fillHist( "event", "nupfcands_30in_pt" , "passtrig", zmet.nupfcands_30in_pt()  , weight );	  
	  // fillHist( "event", "chpfcands_0013_sumet" , "passtrig", zmet.chpfcands_0013_sumet()  , weight );	  
	  // fillHist( "event", "chpfcands_1316_sumet" , "passtrig", zmet.chpfcands_1316_sumet()  , weight );	  
	  // fillHist( "event", "chpfcands_1624_sumet" , "passtrig", zmet.chpfcands_1624_sumet()  , weight );	  
	  // fillHist( "event", "chpfcands_2430_sumet" , "passtrig", zmet.chpfcands_2430_sumet()  , weight );	  
	  // fillHist( "event", "chpfcands_30in_sumet" , "passtrig", zmet.chpfcands_30in_sumet()  , weight );	  
	  // fillHist( "event", "phpfcands_0013_sumet" , "passtrig", zmet.phpfcands_0013_sumet()  , weight );	  
	  // fillHist( "event", "phpfcands_1316_sumet" , "passtrig", zmet.phpfcands_1316_sumet()  , weight );	  
	  // fillHist( "event", "phpfcands_1624_sumet" , "passtrig", zmet.phpfcands_1624_sumet()  , weight );	  
	  // fillHist( "event", "phpfcands_2430_sumet" , "passtrig", zmet.phpfcands_2430_sumet()  , weight );	  
	  // fillHist( "event", "phpfcands_30in_sumet" , "passtrig", zmet.phpfcands_30in_sumet()  , weight );	  
	  // fillHist( "event", "nupfcands_0013_sumet" , "passtrig", zmet.nupfcands_0013_sumet()  , weight );	  
	  // fillHist( "event", "nupfcands_1316_sumet" , "passtrig", zmet.nupfcands_1316_sumet()  , weight );	  
	  // fillHist( "event", "nupfcands_1624_sumet" , "passtrig", zmet.nupfcands_1624_sumet()  , weight );	  
	  // fillHist( "event", "nupfcands_2430_sumet" , "passtrig", zmet.nupfcands_2430_sumet()  , weight );	  
	  // fillHist( "event", "nupfcands_30in_sumet" , "passtrig", zmet.nupfcands_30in_sumet()  , weight );	  

	  fillHist( "event", "ht_highbin", "passtrig", zmet.ht()        , weight );
	  if( zmet.njets() == 2 ) fillHist( "event", "ht_highbin_2jets", "passtrig", zmet.ht()        , weight );
	  if( zmet.njets() == 3 ) fillHist( "event", "ht_highbin_3jets", "passtrig", zmet.ht()        , weight );
	  
	  fillHist( "event", "met_T1CHS_miniAOD_CORE_pt"    , "passtrig", zmet.met_T1CHS_miniAOD_CORE_pt()    , weight );	  
	  fillHist( "event", "met_T1CHS_miniAOD_CORE_up_pt" , "passtrig", zmet.met_T1CHS_miniAOD_CORE_up_pt() , weight );	  
	  fillHist( "event", "met_T1CHS_miniAOD_CORE_dn_pt" , "passtrig", zmet.met_T1CHS_miniAOD_CORE_dn_pt() , weight );	  
	  	  
	  if( event_met_pt < 50 && zmet.hyp_type() == 2 ) nem_2jets += weight;
		  
	  if( zmet.hyp_type() == 0 ) nee += weight;
	  if( zmet.hyp_type() == 1 ) nmm += weight;
	  if( zmet.hyp_type() == 2 ) nem += weight;	  
	  if( zmet.hyp_type() == 0 || zmet.hyp_type() == 1 ) nll += weight;
	  
	  
	  //-~-~-~-~-~-~-~-~-~-//
	  //Fill Template hists//
	  //-~-~-~-~-~-~-~-~-~-//	  
	  if( zmet.njets()                        < 2         ) continue; // require at least 2 good jets



	  // if( zmet.met_T1CHS_miniAOD_CORE_pt() > 100 && (zmet.met_pt() / zmet.met_calo_pt()) > 5 ){
	  // 	cout << setw(10)<<"calomet is bad | ";
	  // 	cout << setw(10)<<zmet.run()<<" | ";
	  // 	cout << setw(5)<<zmet.lumi()<<" | ";
	  // 	cout << setw(10)<<zmet.evt()<<" | ";
	  // 	cout << setw(5)<<zmet.hyp_type()<<" | ";
	  // 	cout << setw(5)<<zmet.nlep()<<" | ";
	  // 	cout << setw(5)<<zmet.nveto_leptons()<<" | ";
	  // 	cout<<zmet.met_T1CHS_miniAOD_CORE_pt()<<" | ";
	  // 	cout<<zmet.met_pt()<<" | ";
	  // 	cout<<zmet.met_calo_pt()<<" | ";
	  // 	cout<<endl;
	  // }
	  
	  // if( event_met_pt > 225 ){
	  // 	cout << setw(10)<<"met>225        | ";
	  // 	cout << setw(10)<<zmet.run()<<" | ";
	  // 	cout << setw(5)<<zmet.lumi()<<" | ";
	  // 	cout << setw(10)<<zmet.evt()<<" | ";
	  // 	cout << setw(5)<<zmet.hyp_type()<<" | ";
	  // 	cout << setw(5)<<zmet.nlep()<<" | ";
	  // 	cout << setw(5)<<zmet.nveto_leptons()<<" | ";
	  // 	cout<<zmet.met_T1CHS_miniAOD_CORE_pt()<<" | ";
	  // 	cout<<zmet.met_pt()<<" | ";
	  // 	cout<<zmet.met_calo_pt()<<" | ";
	  // 	cout<<endl;
	  // }
	  
	  // // sync with Bobak	  
	  // if( event_met_pt > 150 ){
	  // 	cout << setw(10)<<zmet.run()<<" | ";
	  // 	cout << setw(5)<<zmet.lumi()<<" | ";
	  // 	cout << setw(10)<<zmet.evt()<<" | ";
	  // 	cout << setw(5)<<zmet.njets()<<" | ";
	  // 	cout << setw(5)<<zmet.nlep()<<" | ";
	  // 	cout<<(zmet.nlep()+zmet.nveto_leptons()-2)<<" | ";
	  // 	cout << setw(5)<<zmet.hyp_type()<<" | ";
	  // 	cout << setw(5)<<zmet.evt_type()<<" | ";
	  // 	cout << setw(10)<<zmet.mt2()<<" | ";
	  // 	cout << setw(10)<<zmet.dphi_metj1()<<" | ";
	  // 	cout << setw(10)<<zmet.lep_pt().at(0)<<" | ";
	  // 	cout << setw(10)<<zmet.lep_pt().at(1)<<" | ";
	  // 	cout << setw(10)<<zmet.lep_eta().at(0)<<" | ";
	  // 	cout << setw(10)<<zmet.lep_eta().at(1)<<" | ";
	  // 	cout << setw(10)<<zmet.jets_p4().at(0).pt()<<" | ";
	  // 	cout << setw(10)<<zmet.jets_p4().at(1).pt()<<" | ";
	  // 	cout << setw(10)<<zmet.jets_p4().at(0).eta()<<" | ";
	  // 	cout << setw(10)<<zmet.jets_p4().at(1).eta()<<" | ";
	  // 	cout << setw(10)<<zmet.dRll()<<" | ";
	  // 	cout << setw(10)<<zmet.ht()<<" | ";
	  // 	cout << setw(10)<<zmet.met_T1CHS_miniAOD_CORE_pt()<<" | ";
	  // 	cout << setw(10)<<passMETFilters()<<" | ";
	  // 	cout<<zmet.mlbmin()<<" | ";
	  // 	// cout<<zmet.nlep()<<" | ";
	  // 	cout<<endl;
	  // }


	  //synch with Marc

	  // if( zmet.evt() == 1460034810 ||
	  // 	  zmet.evt() == 240607834 ||
	  // 	  zmet.evt() == 838557150 ){
	  // 	 cout<<zmet.evt()<<" | "<<event_met_pt<<" | "<<zmet.dphi_metj1()<<" | "<<zmet.mt2()<<endl;
	  // }
	  // if( event_met_pt > 250 && zmet.hyp_type() == 2 && zmet.njets() > 1 ){
	  // 	cout<<zmet.evt()<<" | "<<event_met_pt<<" | "<<zmet.dphi_metj1()<<" | "<<zmet.mt2()<<endl;
	  // } else {
	  // 	continue;
	  // }

	  npass += weight;
	  
	  fillHist( "event", "ht_gt1j"       , "passtrig", zmet.dilpt(), weight );
	  fillHist( "event", "atlas_ht_gt1j" , "passtrig", zmet.dilpt(), weight );
	  fillHist( "event", "met_rawgt1jet" , "passtrig", event_met_pt        , weight );	  
	  if( (TString(currentFile->GetTitle()).Contains("t5zz") || TString(currentFile->GetTitle()).Contains("tchiwz") ) && TString(sample).Contains("fullscan") ){
		// fill full scan hist
		if( event_met_pt > 100 && event_met_pt <= 150 ){
		  if( zmet.hyp_type() == 0 ) h_signalyields_met100to150_ee -> Fill (zmet.mass_gluino(), zmet.mass_LSP(), weight);
		  if( zmet.hyp_type() == 1 ) h_signalyields_met100to150_mm -> Fill (zmet.mass_gluino(), zmet.mass_LSP(), weight);
		  if( zmet.hyp_type() != 2 ) h_signalyields_met100to150_ll -> Fill (zmet.mass_gluino(), zmet.mass_LSP(), weight);
		}

		if( event_met_pt > 150 && event_met_pt <= 225 ){
		  if( zmet.hyp_type() == 0 ) h_signalyields_met150to225_ee -> Fill (zmet.mass_gluino(), zmet.mass_LSP(), weight);
		  if( zmet.hyp_type() == 1 ) h_signalyields_met150to225_mm -> Fill (zmet.mass_gluino(), zmet.mass_LSP(), weight);
		  if( zmet.hyp_type() != 2 ) h_signalyields_met150to225_ll -> Fill (zmet.mass_gluino(), zmet.mass_LSP(), weight);
		}

		if( event_met_pt > 225 && event_met_pt <= 300 ){
		  if( zmet.hyp_type() == 0 ) h_signalyields_met225to300_ee -> Fill (zmet.mass_gluino(), zmet.mass_LSP(), weight);
		  if( zmet.hyp_type() == 1 ) h_signalyields_met225to300_mm -> Fill (zmet.mass_gluino(), zmet.mass_LSP(), weight);
		  if( zmet.hyp_type() != 2 ) h_signalyields_met225to300_ll -> Fill (zmet.mass_gluino(), zmet.mass_LSP(), weight);
		}

		if( event_met_pt > 225 ){
		  if( zmet.hyp_type() == 0 ) h_signalyields_met225toinf_ee -> Fill (zmet.mass_gluino(), zmet.mass_LSP(), weight);
		  if( zmet.hyp_type() == 1 ) h_signalyields_met225toinf_mm -> Fill (zmet.mass_gluino(), zmet.mass_LSP(), weight);
		  if( zmet.hyp_type() != 2 ) h_signalyields_met225toinf_ll -> Fill (zmet.mass_gluino(), zmet.mass_LSP(), weight);
		}

		if( event_met_pt > 300 ){
		  if( zmet.mass_gluino() == 300 && zmet.mass_LSP() == 0 ) cout<<event_met_pt<<endl;
		  if( zmet.hyp_type() == 0 ) h_signalyields_met300toinf_ee -> Fill (zmet.mass_gluino(), zmet.mass_LSP(), weight);
		  if( zmet.hyp_type() == 1 ) h_signalyields_met300toinf_mm -> Fill (zmet.mass_gluino(), zmet.mass_LSP(), weight);
		  if( zmet.hyp_type() != 2 ) h_signalyields_met300toinf_ll -> Fill (zmet.mass_gluino(), zmet.mass_LSP(), weight);
		}

		if( zmet.mass_gluino() == 1000 && zmet.mass_LSP() == 550 )fillHist( "event", "met_SRATLAS_1000_550"       , "passtrig", event_met_pt, weight );
		if( zmet.mass_gluino() == 1000 && zmet.mass_LSP() == 600 )fillHist( "event", "met_SRATLAS_1000_600"       , "passtrig", event_met_pt, weight );
		
	  }

	  if( TString(selection).Contains("tail") ){

		float btagcount = zmet.nBJetMedium();
	    // btagcount = zmet.nBJetTight();
		
		if( !zmet.isData() && btagcount > 0 ) {
		  bool hasrealb = false;
		  for( int jetind = 0; jetind < zmet.njets(); jetind++ ){
			if( abs(zmet.jets_mcFlavour().at(jetind)) == 5 ) hasrealb = true;
			if( hasrealb ) break;
		  }		
		  allmet_nobreq     += weight;
		  unc_allmet_nobreq += weight*weight;

		  if( hasrealb ){
			allmet_hasrealb     += weight;
			unc_allmet_hasrealb += weight*weight;
		  }

		  if( event_met_pt > 100 ){

			endmet_nobreq     += weight;
			unc_endmet_nobreq += weight*weight;		

			if( hasrealb ){
			  endmet_hasrealb     += weight;		
			  unc_endmet_hasrealb += weight*weight;		
			}

		  }
		}
		
		if( btagcount == 0 ){
		  allmet_btag_nobreq     += weight;
		  unc_allmet_btag_nobreq += weight*weight;
		}
		
		if( btagcount > 0 ){
		  allmet_btag_hasrealb     += weight;
		  unc_allmet_btag_hasrealb += weight*weight;
		}
		
		if( event_met_pt > 100 ){
		  if( btagcount == 0 ){
			endmet_btag_nobreq     += weight;
			unc_endmet_btag_nobreq += weight*weight;		
		  }
		
		  if( btagcount > 0 ) endmet_btag_hasrealb     += weight;		
		  if( btagcount > 0 ) unc_endmet_btag_hasrealb += weight*weight;		
		}		

	  }
	  
	  if( zmet.isData() && event_met_pt > 1000 ){
	  	cout<<"MET:     "<<event_met_pt<<endl;
	  	cout<<"hyptype: "<<zmet.hyp_type()<<endl;
	  	cout<<zmet.run()<<":"<<zmet.lumi()<<":"<<zmet.evt()<<endl;
	  }

	  if( dotemplateprediction || dotemplatepredictionmc ){
		if( (zmet.hyp_type() == 0 || zmet.hyp_type() == 1 ) ){
		  currentMETTemplate = mettemplates.pickTemplate( mettemplate_hists, zmet.njets(), zmet.ht(), zmet.dilpt() );
		  mettemplates.countTemplate( zmet.njets(), zmet.ht(), zmet.dilpt(), weight );

		  if( correctewkcontamination ){
			currentMETTemplate_ewk = mettemplates_ewk.pickTemplate( mettemplate_hists_ewk, zmet.njets(), zmet.ht(), zmet.dilpt() );
			mettemplates_ewk.countTemplate( zmet.njets(), zmet.ht(), zmet.dilpt(), weight );
			try
			  {
				event_hists.at( "h_templ_met_ewk" ) -> Add( currentMETTemplate_ewk, weight );		
			  }
			catch(exception &e)
			  {
				cout<<"Hist: h_templ_met_ewk Does not exist!"<<endl;
				exit(1);
			  }
		  }
		  
		  try
		  	{
		  	  event_hists.at( "h_templ_met" ) -> Add( currentMETTemplate, weight );		
		  	}
		  catch(exception &e)
		  	{
		  	  cout<<"Hist: h_templ_met Does not exist!"<<endl;
		  	  exit(1);
		  	}
		}
	  }

    } // end loop over events
  } // end loop over files
  
  cout << npass       << " events passing selection" << endl;
  cout << nDuplicates << " duplicate events in data" << endl;
  cout << nee         << " ee events passing selection" << endl;
  cout << nmm         << " mm events passing selection" << endl;
  cout << nll         << " ll events passing selection" << endl;
  cout << nem         << " em events passing selection" << endl;
  
  cout<<"nemu 2 jets    : "<<nem_2jets<<endl;
  cout<<"nemu 2 jets mll: "<<nem_2jets_mll<<endl;
  cout<<"emu scale factor: "<<nem_2jets_mll/nem_2jets<<endl;

  cout<<"nlosplit: "<<nlosplit<<endl;
  cout<<"nhisplit: "<<nhisplit<<endl;

  cout<<"badevents: "<<badevents<<endl;

  if( docutflow && TString(selection).Contains("SR_ATLAS") ){
	cout<<"Total Events:   "<< cutflow_events[0] << " | " << sqrt(cutflow_errors[0]) << endl;
	cout<<"2 leptons 5025: "<< cutflow_events[1] << " | " << sqrt(cutflow_errors[1]) << endl;
	cout<<"mll onZ:        "<< cutflow_events[2] << " | " << sqrt(cutflow_errors[2]) << endl;
	cout<<"njets:          "<< cutflow_events[3] << " | " << sqrt(cutflow_errors[3]) << endl;
	cout<<"HT>600:         "<< cutflow_events[4] << " | " << sqrt(cutflow_errors[4]) << endl;
	cout<<"MET>225:        "<< cutflow_events[5] << " | " << sqrt(cutflow_errors[5]) << endl;
	cout<<"dphi:           "<< cutflow_events[6] << " | " << sqrt(cutflow_errors[6]) << endl;
  }

  if( docutflow && TString(selection).Contains("SR_EWK") ){
	cout<<"Total Events:   "<< cutflow_events[0] << " | " << sqrt(cutflow_errors[0]) << endl;
	cout<<"exactly 2 leps: "<< cutflow_events[1] << " | " << sqrt(cutflow_errors[1]) << endl;
	cout<<"mll onZ:        "<< cutflow_events[2] << " | " << sqrt(cutflow_errors[2]) << endl;
	cout<<"njets:          "<< cutflow_events[3] << " | " << sqrt(cutflow_errors[3]) << endl;
	cout<<"bveto:          "<< cutflow_events[4] << " | " << sqrt(cutflow_errors[4]) << endl;
	cout<<"dphi:           "<< cutflow_events[5] << " | " << sqrt(cutflow_errors[5]) << endl;
	cout<<"mt2:            "<< cutflow_events[6] << " | " << sqrt(cutflow_errors[6]) << endl;
	cout<<"MET > 150:      "<< cutflow_events[7] << " | " << sqrt(cutflow_errors[7]) << endl;
	cout<<"MET > 225:      "<< cutflow_events[8] << " | " << sqrt(cutflow_errors[8]) << endl;
	cout<<"MET > 300:      "<< cutflow_events[9] << " | " << sqrt(cutflow_errors[9]) << endl;
  }

  if( docutflow && TString(selection).Contains("SRB") ){
	cout<<"Total Events:   "<< cutflow_events[0] << " | " << sqrt(cutflow_errors[0]) << endl;
	cout<<"2 leptons 2520: "<< cutflow_events[1] << " | " << sqrt(cutflow_errors[1]) << endl;
	cout<<"mll onZ:        "<< cutflow_events[2] << " | " << sqrt(cutflow_errors[2]) << endl;
	cout<<"njets:          "<< cutflow_events[3] << " | " << sqrt(cutflow_errors[3]) << endl;
	if( docutflow && TString(selection).Contains("withb") ){
	  cout<<"withb:          "<< cutflow_events[4] << " | " <<  sqrt(cutflow_errors[4]) << endl;
	  cout<<"MET>100:        "<< cutflow_events[5] << " | " <<  sqrt(cutflow_errors[5]) << endl;
	  cout<<"MET>150:        "<< cutflow_events[6] << " | " <<  sqrt(cutflow_errors[6]) << endl;
	  cout<<"MET>225:        "<< cutflow_events[7] << " | " <<  sqrt(cutflow_errors[7]) << endl;
	  cout<<"MET>300:        "<< cutflow_events[8] << " | " <<  sqrt(cutflow_errors[8]) << endl;
	}

	if( docutflow && TString(selection).Contains("bveto") ){
	  cout<<"bveto:          "<< cutflow_events[4] << " | " <<  sqrt(cutflow_errors[4]) << endl;
	  cout<<"MET>100:        "<< cutflow_events[5] << " | " <<  sqrt(cutflow_errors[5]) << endl;
	  cout<<"MET>150:        "<< cutflow_events[6] << " | " <<  sqrt(cutflow_errors[6]) << endl;
	  cout<<"MET>225:        "<< cutflow_events[7] << " | " <<  sqrt(cutflow_errors[7]) << endl;
	  cout<<"MET>300:        "<< cutflow_events[8] << " | " <<  sqrt(cutflow_errors[8]) << endl;
	}
  }
  
  if( TString(selection).Contains("tail") ){

	float unc_endmet_nobreq_binomial   = err_binomial( endmet_nobreq  , allmet_nobreq  , sqrt(unc_endmet_nobreq  ), sqrt(unc_allmet_nobreq  ));
	float unc_endmet_hasrealb_binomial = err_binomial( endmet_hasrealb, allmet_hasrealb, sqrt(unc_endmet_hasrealb), sqrt(unc_allmet_hasrealb));
	cout<<"fraction in tail with no b-req: "<< endmet_nobreq  /allmet_nobreq   << " | " << unc_endmet_nobreq_binomial   <<endl;	
	cout<<"fraction in tail with 1 real b: "<< endmet_hasrealb/allmet_hasrealb << " | " << unc_endmet_hasrealb_binomial <<endl;

	float unc_endmet_btag_nobreq_binomial   = err_binomial( endmet_btag_nobreq  , allmet_btag_nobreq  , sqrt(unc_endmet_btag_nobreq  ), sqrt(unc_allmet_btag_nobreq  ));
	float unc_endmet_btag_hasrealb_binomial = err_binomial( endmet_btag_hasrealb, allmet_btag_hasrealb, sqrt(unc_endmet_btag_hasrealb), sqrt(unc_allmet_btag_hasrealb));
	cout<<endl<<"fraction in tail with no b-tags: "<< endmet_btag_nobreq  /allmet_btag_nobreq    << " | " << unc_endmet_btag_nobreq_binomial   <<endl;	
	cout<<      "fraction in tail with b-tags   : "<< endmet_btag_hasrealb/allmet_btag_hasrealb  << " | " << unc_endmet_btag_hasrealb_binomial <<endl;
  }

  cout<<"N SF events: "<<nsf_2jets_met_zveto<<endl;
  cout<<"N OF events: "<<nof_2jets_met_zveto<<endl;
  
  // mettemplates.NormalizeTemplates(mettemplate_hists);
  mettemplates     . correctBinUncertainty( mettemplate_hists,     event_hists.at("h_templ_met"    ) );
  mettemplates_ewk . correctBinUncertainty( mettemplate_hists_ewk, event_hists.at("h_templ_met_ewk") );

  event_hists.at("h_templ_met_ewk_subtracted") = (TH1F*)event_hists.at("h_templ_met_ewk")->Clone("h_templ_met_ewk_subtracted");
  event_hists.at("h_templ_met_ewk_difference") = (TH1F*)event_hists.at("h_templ_met"    )->Clone("h_templ_met_ewk_difference");
  event_hists.at("h_templ_met_ewk_difference") -> Add(  event_hists.at("h_templ_met_ewk"), -1.0 ); // get nominal with ewk subtracted
  if (nEventsChain != nEventsTotal)
    std::cout << "ERROR: number of events from files is not equal to total number of events" << std::endl;

  string vtxstring = "";
  if( !dovtxreweighting ) vtxstring = "_novtxweight";
  

  // make histos rootfile
  string outputfilename = 	Form("../output/%s/%s%s%s_hists.root",
								 iter.c_str(),
								 sample.c_str(),
								 selection.c_str(),
								 vtxstring.c_str()
								 );

  cout << "Writing output to " << outputfilename << endl;
  saveHist(outputfilename.c_str(),"*");
  
  // deleteHistos();
  
} // end ScanChain


void templateLooper::bookHistos( string signal_sample = "" ){

  // hist naming convention: "h_<leptype>_<object>_<variable>_<selection>"
  vector <string> leptype;
  leptype.push_back("ee");
  leptype.push_back("mm");
  leptype.push_back("em");
  leptype.push_back("ll");
  vector <string> object;
  object.push_back("event");
  vector <string> selection;
  selection.push_back("inclusive");
  selection.push_back("passtrig");

  vector <string> variable;      vector <float> variable_bins;

  variable.push_back("pt_matchedbjet1");          variable_bins.push_back(1000);  
  variable.push_back("pt_matchedbjet2");          variable_bins.push_back(1000);  
  variable.push_back("pt_matchedbjet3");          variable_bins.push_back(1000);  
  variable.push_back("pt_matchedbjet4");          variable_bins.push_back(1000);  
  
  variable.push_back("ptb1");          variable_bins.push_back(1000);  
  variable.push_back("ptb2");          variable_bins.push_back(1000);  
  variable.push_back("ptb3");          variable_bins.push_back(1000);  
  variable.push_back("ptb4");          variable_bins.push_back(1000);  

  variable.push_back("ptl1");          variable_bins.push_back(1000);  
  variable.push_back("ptl2");          variable_bins.push_back(1000);  
  variable.push_back("ptj1");          variable_bins.push_back(1000);  
  variable.push_back("ptj2");          variable_bins.push_back(1000);  
  variable.push_back("ptj3");          variable_bins.push_back(1000);  
  variable.push_back("ptj4");          variable_bins.push_back(1000);  
  variable.push_back("ptdil");         variable_bins.push_back(1000);  
  variable.push_back("met");           variable_bins.push_back(500 );  
  variable.push_back("met_raw");       variable_bins.push_back(500 );  
  variable.push_back("met_rawgt1jet"); variable_bins.push_back(500 );  
  variable.push_back("ht");	           variable_bins.push_back(1000);  
  variable.push_back("ht_highbin");    variable_bins.push_back(1500);  
  variable.push_back("ht_highbin_2jets");    variable_bins.push_back(1500);  
  variable.push_back("ht_highbin_3jets");    variable_bins.push_back(1500);  
  variable.push_back("ht_gt1j");	   variable_bins.push_back(3000);  
  variable.push_back("atlas_ht_gt1j"); variable_bins.push_back(3000);  
  variable.push_back("njets");         variable_bins.push_back(20  );  
  variable.push_back("nbjets");        variable_bins.push_back(20  );  
  variable.push_back("mll");           variable_bins.push_back(300 );  
  variable.push_back("nVert");         variable_bins.push_back(50 );  
  variable.push_back("mll_fkw");       variable_bins.push_back(400 );  
  
  variable.push_back("nVert_true");    variable_bins.push_back(50 );  

  variable.push_back("met_CORE");       variable_bins.push_back(500 );  
  variable.push_back("met_COREgt1jet"); variable_bins.push_back(500 );  

  variable.push_back("met_T1CHS_miniAOD_CORE_pt");       variable_bins.push_back(500 );  
  variable.push_back("met_T1CHS_miniAOD_CORE_up_pt");    variable_bins.push_back(500 );  
  variable.push_back("met_T1CHS_miniAOD_CORE_dn_pt");    variable_bins.push_back(500 );  

  variable.push_back("metgt1jet");                   variable_bins.push_back(500 );  

  variable.push_back("met_SRATLAS_1000_550");    variable_bins.push_back(500 );  
  variable.push_back("met_SRATLAS_1000_600");    variable_bins.push_back(500 );  

  variable.push_back("mbb_bpt");    variable_bins.push_back(400 );  
  variable.push_back("mbb_csv");    variable_bins.push_back(400 );  
  variable.push_back("mt2j");       variable_bins.push_back(500 );  
  variable.push_back("mt2b");       variable_bins.push_back(500 );  
  variable.push_back("mt2");        variable_bins.push_back(500 );  
  variable.push_back("mjj");        variable_bins.push_back(400 );  
  variable.push_back("ptlep1lep2"); variable_bins.push_back(1000);  

  // variable.push_back("chpfcands_0013_pt");        variable_bins.push_back(500 );  
  // variable.push_back("chpfcands_1316_pt");        variable_bins.push_back(500 );  
  // variable.push_back("chpfcands_1624_pt");        variable_bins.push_back(500 );  
  // variable.push_back("chpfcands_2430_pt");        variable_bins.push_back(500 );  
  // variable.push_back("chpfcands_30in_pt");        variable_bins.push_back(500 );  
  // variable.push_back("phpfcands_0013_pt");        variable_bins.push_back(500 );  
  // variable.push_back("phpfcands_1316_pt");        variable_bins.push_back(500 );  
  // variable.push_back("phpfcands_1624_pt");        variable_bins.push_back(500 );  
  // variable.push_back("phpfcands_2430_pt");        variable_bins.push_back(500 );  
  // variable.push_back("phpfcands_30in_pt");        variable_bins.push_back(500 );  
  // variable.push_back("nupfcands_0013_pt");        variable_bins.push_back(500 );  
  // variable.push_back("nupfcands_1316_pt");        variable_bins.push_back(500 );  
  // variable.push_back("nupfcands_1624_pt");        variable_bins.push_back(500 );  
  // variable.push_back("nupfcands_2430_pt");        variable_bins.push_back(500 );  
  // variable.push_back("nupfcands_30in_pt");        variable_bins.push_back(500 );  

  // variable.push_back("chpfcands_0013_sumet");        variable_bins.push_back(2000 );  
  // variable.push_back("chpfcands_1316_sumet");        variable_bins.push_back(2000 );  
  // variable.push_back("chpfcands_1624_sumet");        variable_bins.push_back(2000 );  
  // variable.push_back("chpfcands_2430_sumet");        variable_bins.push_back(2000 );  
  // variable.push_back("chpfcands_30in_sumet");        variable_bins.push_back(2000 );  
  // variable.push_back("phpfcands_0013_sumet");        variable_bins.push_back(2000 );  
  // variable.push_back("phpfcands_1316_sumet");        variable_bins.push_back(2000 );  
  // variable.push_back("phpfcands_1624_sumet");        variable_bins.push_back(2000 );  
  // variable.push_back("phpfcands_2430_sumet");        variable_bins.push_back(2000 );  
  // variable.push_back("phpfcands_30in_sumet");        variable_bins.push_back(2000 );  
  // variable.push_back("nupfcands_0013_sumet");        variable_bins.push_back(2000 );  
  // variable.push_back("nupfcands_1316_sumet");        variable_bins.push_back(2000 );  
  // variable.push_back("nupfcands_1624_sumet");        variable_bins.push_back(2000 );  
  // variable.push_back("nupfcands_2430_sumet");        variable_bins.push_back(2000 );  
  // variable.push_back("nupfcands_30in_sumet");        variable_bins.push_back(2000 );  

  
  for( unsigned int lepind = 0; lepind < leptype.size(); lepind++ ){
	for( unsigned int objind = 0; objind < object.size(); objind++ ){
	  for( unsigned int varind = 0; varind < variable.size(); varind++ ){
		for( unsigned int selind = 0; selind < selection.size(); selind++ ){
		  bookHist(Form("h_%s_%s_%s_%s",
						leptype  .at(lepind).c_str(),
						object   .at(objind).c_str(),
					    variable .at(varind).c_str(),
					    selection.at(selind).c_str()
						),
				   Form("h_%s_%s_%s_%s",
						leptype  .at(lepind).c_str(),
						object   .at(objind).c_str(),
					    variable .at(varind).c_str(),
					    selection.at(selind).c_str()
						),
				   static_cast<int>(variable_bins.at(varind)),
				   0.0,
				   variable_bins.at(varind));
		}
	  }
	}
  }

  // random extra hists here
  bookHist("h_templ_met", "h_templ_met", 500,0,500);
  bookHist("h_templ_met_ewk", "h_templ_met_ewk", 500,0,500);
  bookHist("h_templ_met_ewk_subtracted", "h_templ_met_ewk_subtracted", 500,0,500);
  bookHist("h_templ_met_ewk_difference", "h_templ_met_ewk_difference", 500,0,500);

  vector <string> phivars;
  vector <float> axislimits;

  phivars.push_back("metphi");               axislimits.push_back(3.2);
  phivars.push_back("metphir");				 axislimits.push_back(3.2);
  phivars.push_back("l1phi");                axislimits.push_back(3.2);
  phivars.push_back("l2phi");                axislimits.push_back(3.2);
  phivars.push_back("l1eta");                axislimits.push_back(2.5);
  phivars.push_back("l2eta");                axislimits.push_back(2.5);


  for( unsigned int lepind = 0; lepind < leptype.size(); lepind++ ){
	for( unsigned int objind = 0; objind < object.size(); objind++ ){
	  for( unsigned int varind = 0; varind < phivars.size(); varind++ ){
		for( unsigned int selind = 0; selind < selection.size(); selind++ ){
		  bookHist(Form("h_%s_%s_%s_%s",
						leptype  .at(lepind).c_str(),
						object   .at(objind).c_str(),
					    phivars  .at(varind).c_str(),
					    selection.at(selind).c_str()
						),
				   Form("h_%s_%s_%s_%s",
						leptype  .at(lepind).c_str(),
						object   .at(objind).c_str(),
					    phivars  .at(varind).c_str(),
					    selection.at(selind).c_str()
						),
				   200   ,
				   -axislimits.at(varind) ,
				    axislimits.at(varind)  );
		}
	  }
	}
  }
  
  bookHist("h_ll_event_dphijj_passtrig", "h_ll_event_dphijj_passtrig", 500,0,5);
  bookHist("h_ee_event_dphijj_passtrig", "h_ee_event_dphijj_passtrig", 500,0,5);
  bookHist("h_mm_event_dphijj_passtrig", "h_mm_event_dphijj_passtrig", 500,0,5);
  bookHist("h_em_event_dphijj_passtrig", "h_em_event_dphijj_passtrig", 500,0,5);  
  bookHist("h_ll_event_detajj_passtrig", "h_ll_event_detajj_passtrig", 500,0,5);
  bookHist("h_ee_event_detajj_passtrig", "h_ee_event_detajj_passtrig", 500,0,5);
  bookHist("h_mm_event_detajj_passtrig", "h_mm_event_detajj_passtrig", 500,0,5);
  bookHist("h_em_event_detajj_passtrig", "h_em_event_detajj_passtrig", 500,0,5);  
  bookHist("h_ll_event_dRjj_passtrig", "h_ll_event_dRjj_passtrig", 500,0,10);
  bookHist("h_ee_event_dRjj_passtrig", "h_ee_event_dRjj_passtrig", 500,0,10);
  bookHist("h_mm_event_dRjj_passtrig", "h_mm_event_dRjj_passtrig", 500,0,10);
  bookHist("h_em_event_dRjj_passtrig", "h_em_event_dRjj_passtrig", 500,0,10);
  
  bookHist("h_ll_event_drll_2jets", "h_ll_event_drll_2jets", 500,0,5);
  bookHist("h_ee_event_drll_2jets", "h_ee_event_drll_2jets", 500,0,5);
  bookHist("h_mm_event_drll_2jets", "h_mm_event_drll_2jets", 500,0,5);
  bookHist("h_em_event_drll_2jets", "h_em_event_drll_2jets", 500,0,5);

  bookHist("h_ll_event_csv1_passtrig", "h_ll_event_csv1_passtrig", 500,-1,1.5);
  bookHist("h_ee_event_csv1_passtrig", "h_ee_event_csv1_passtrig", 500,-1,1.5);
  bookHist("h_mm_event_csv1_passtrig", "h_mm_event_csv1_passtrig", 500,-1,1.5);
  bookHist("h_em_event_csv1_passtrig", "h_em_event_csv1_passtrig", 500,-1,1.5);

  bookHist("h_ll_event_csv2_passtrig", "h_ll_event_csv2_passtrig", 500,-1,1.5);
  bookHist("h_ee_event_csv2_passtrig", "h_ee_event_csv2_passtrig", 500,-1,1.5);
  bookHist("h_mm_event_csv2_passtrig", "h_mm_event_csv2_passtrig", 500,-1,1.5);
  bookHist("h_em_event_csv2_passtrig", "h_em_event_csv2_passtrig", 500,-1,1.5);

  bookHist("h_ll_event_csv3_passtrig", "h_ll_event_csv3_passtrig", 500,-1,1.5);
  bookHist("h_ee_event_csv3_passtrig", "h_ee_event_csv3_passtrig", 500,-1,1.5);
  bookHist("h_mm_event_csv3_passtrig", "h_mm_event_csv3_passtrig", 500,-1,1.5);
  bookHist("h_em_event_csv3_passtrig", "h_em_event_csv3_passtrig", 500,-1,1.5);

  bookHist("h_ll_event_csv4_passtrig", "h_ll_event_csv4_passtrig", 500,-1,1.5);
  bookHist("h_ee_event_csv4_passtrig", "h_ee_event_csv4_passtrig", 500,-1,1.5);
  bookHist("h_mm_event_csv4_passtrig", "h_mm_event_csv4_passtrig", 500,-1,1.5);
  bookHist("h_em_event_csv4_passtrig", "h_em_event_csv4_passtrig", 500,-1,1.5);


  bookHist("h_ll_event_njtall_passtrig", "h_ll_event_njtall_passtrig", 10,0,10);
  bookHist("h_ll_event_njtm50_passtrig", "h_ll_event_njtm50_passtrig", 10,0,10);
  bookHist("h_ll_event_metall_passtrig", "h_ll_event_metall_passtrig", 200,0,200);

  if( signal_sample == "t5zz" ){  
	h_signalyields_met100to150_ee = new TH2F("h_signalyields_met100to150_ee","h_signalyields_met100to150_ee",(1900-550)/50,575,1925,(1800-50)/50,75,1825);	
	h_signalyields_met100to150_mm = new TH2F("h_signalyields_met100to150_mm","h_signalyields_met100to150_mm",(1900-550)/50,575,1925,(1800-50)/50,75,1825);	
	h_signalyields_met100to150_ll = new TH2F("h_signalyields_met100to150_ll","h_signalyields_met100to150_ll",(1900-550)/50,575,1925,(1800-50)/50,75,1825);	
  }

  if( signal_sample == "tchiwz" ){  
	h_signalyields_met100to150_ee = new TH2F("h_signalyields_met100to150_ee","h_signalyields_met100to150_ee",25,87.5,712.5,31,-5,305);	
	h_signalyields_met100to150_mm = new TH2F("h_signalyields_met100to150_mm","h_signalyields_met100to150_mm",25,87.5,712.5,31,-5,305);	
	h_signalyields_met100to150_ll = new TH2F("h_signalyields_met100to150_ll","h_signalyields_met100to150_ll",25,87.5,712.5,31,-5,305);	
  }

  h_signalyields_met100to150_ee->Sumw2();
  h_signalyields_met100to150_mm->Sumw2();
  h_signalyields_met100to150_ll->Sumw2();

  h_signalyields_met150to225_ee = (TH2F*) h_signalyields_met100to150_ee->Clone("h_signalyields_met150to225_ee");
  h_signalyields_met150to225_mm = (TH2F*) h_signalyields_met100to150_ee->Clone("h_signalyields_met150to225_mm");
  h_signalyields_met150to225_ll = (TH2F*) h_signalyields_met100to150_ee->Clone("h_signalyields_met150to225_ll");

  h_signalyields_met225to300_ee = (TH2F*) h_signalyields_met100to150_ee->Clone("h_signalyields_met225to300_ee");
  h_signalyields_met225to300_mm = (TH2F*) h_signalyields_met100to150_ee->Clone("h_signalyields_met225to300_mm");
  h_signalyields_met225to300_ll = (TH2F*) h_signalyields_met100to150_ee->Clone("h_signalyields_met225to300_ll");

  h_signalyields_met225toinf_ee = (TH2F*) h_signalyields_met100to150_ee->Clone("h_signalyields_met225toinf_ee");
  h_signalyields_met225toinf_mm = (TH2F*) h_signalyields_met100to150_ee->Clone("h_signalyields_met225toinf_mm");
  h_signalyields_met225toinf_ll = (TH2F*) h_signalyields_met100to150_ee->Clone("h_signalyields_met225toinf_ll");

  h_signalyields_met300toinf_ee = (TH2F*) h_signalyields_met100to150_ee->Clone("h_signalyields_met300toinf_ee");
  h_signalyields_met300toinf_mm = (TH2F*) h_signalyields_met100to150_ee->Clone("h_signalyields_met300toinf_mm");
  h_signalyields_met300toinf_ll = (TH2F*) h_signalyields_met100to150_ee->Clone("h_signalyields_met300toinf_ll");

  
}

void templateLooper::bookHist( string name, string title, int nbins, float xmin, float xmax ){
  // cout<<"Booking hist: "<<name<<endl;
  TH1F * hist = new TH1F( name.c_str(), title.c_str(), nbins, xmin, xmax );
  hist->Sumw2();
  event_hists.insert ( pair<std::string,TH1F*>( name, hist ) );		
  return;
}  


void templateLooper::fillHist( string obj, string var, string sel, float value, float weight ){
  // cout<<"Booking hist: "<<name<<endl;
  // TH1F * hist = new TH1F( name, title, nbins, xmin, xmax );
  string hist = "h_";
  try
	{
	  if( zmet.hyp_type() == 0 ){
		hist = Form("h_ee_%s_%s_%s", obj.c_str(), var.c_str(), sel.c_str());
		fillUnderOverFlow(event_hists.at( hist ), value, weight);
	  }
	  if( zmet.hyp_type() == 1 ){
		hist = Form("h_mm_%s_%s_%s", obj.c_str(), var.c_str(), sel.c_str());
		fillUnderOverFlow(event_hists.at( hist ), value, weight);
	  }
	  if( zmet.hyp_type() == 2 ){
		hist = Form("h_em_%s_%s_%s", obj.c_str(), var.c_str(), sel.c_str());
		fillUnderOverFlow(event_hists.at( hist ), value, weight);
	  }
	  if( zmet.hyp_type() == 0 || zmet.hyp_type() == 1 ){
		hist = Form("h_ll_%s_%s_%s", obj.c_str(), var.c_str(), sel.c_str());
		fillUnderOverFlow(event_hists.at( hist ), value, weight);
	  }
	}
  catch(exception &e)
	{
	  cout<<"Hist: "<<hist<<" Does not exist!"<<endl;
	  exit(1);
	}
 
	return;
}  

