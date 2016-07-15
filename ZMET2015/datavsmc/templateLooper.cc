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

#include "Math/VectorUtil.h"

#include "templateLooper.h"

#include "../sharedCode/histTools.h"
#include "../sharedCode/ZMET.h"
#include "../sharedCode/METTemplateSelections.h"
#include "../sharedCode/AnalysisSelections.h"

#include "../../CORE/Tools/dorky/dorky.h"
#include "../../CORE/Tools/goodrun.h"
#include "../../CORE/Tools/badEventFilter.h"

using namespace std;
using namespace duplicate_removal;

const bool debug = false;

const bool usejson                 = true;
const bool dovtxreweighting        = true;
const bool dotemplateprediction    = true;
const bool correctewkcontamination = true;
const bool dotemplatepredictionmc = false;

// Used for MC, to calculate nominal values
const bool doscalefactors       = false;

// these are for deriving signal systematics
bool doisrboost  = true;
bool heavy_up    = false;
bool light_up    = false;
bool jes_up      = false;
bool jes_dn      = false;
bool dofastsim   = true;
bool doleptonid  = true;
bool doleptoniso = true;

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
  
  bookHistos();

  // eventFilter metFilterTxt;
  // if ( TString(sample).Contains("data") ) {
  //   cout<<"Loading bad event files ..."<<endl;
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/DoubleEG_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/DoubleEG_ecalscn1043093.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/DoubleMuon_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/DoubleMuon_ecalscn1043093.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/HTMHT_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/HTMHT_ecalscn1043093.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/JetHT_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/JetHT_ecalscn1043093.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/MET_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/MET_ecalscn1043093.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/MuonEG_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/MuonEG_ecalscn1043093.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/SingleElectron_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/SingleElectron_ecalscn1043093.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/SingleMuon_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/SingleMuon_ecalscn1043093.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/SinglePhoton_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/SinglePhoton_ecalscn1043093.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_DoubleEG_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_DoubleMuon_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_HTMHT_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_JetHT_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_MET_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_MuonEG_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_SingleElectron_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_SingleMuon_csc2015.txt");
  //   metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_SinglePhoton_csc2015.txt");
  //   cout<<" ... finished!"<<endl;
  // }

  double npass = 0;

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
  const char* json_file = "../../json/golden_json_080716_snt.txt"; // 4.0 fb, for preapproval
  
  set_goodrun_file(json_file);

  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");

  TH1F * h_vtxweight = NULL;
  TFile * f_vtx = NULL;
  if( dovtxreweighting ){
	f_vtx = TFile::Open("nvtx_ratio_6p26fb.root","READ");
	h_vtxweight = (TH1F*)f_vtx->Get("h_vtx_ratio")->Clone("h_vtxweight");
	// f_vtx = TFile::Open("puWeights_nTrueInt.root","READ");
	// h_vtxweight = (TH1F*)f_vtx->Get("weights")->Clone("h_vtxweight");
	h_vtxweight->SetDirectory(rootdir);
	f_vtx->Close();
  }

  TFile * f_sfweights = NULL;
  TH2D * h_isrweights = NULL;
  TH2D * h_bsfweights = NULL;
  TH2D * h_bsfweights_heavy_UP = NULL;
  TH2D * h_bsfweights_light_UP = NULL;
  TH2D * h_eleweights = NULL;
  TH2D * h_muoweights = NULL;

  TH2D * h_eleweights_id = NULL;
  TH2D * h_muoweights_id = NULL;
  TH2D * h_eleweightsiso = NULL;
  TH2D * h_muoweightsiso = NULL;

  if( doscalefactors ){
	f_sfweights  = TFile::Open("nsig_weights_T5ZZ.root","READ");

	h_isrweights = (TH2D*)f_sfweights->Get("h_avg_weight_isr")   ->Clone("h_isrweights");
	h_bsfweights = (TH2D*)f_sfweights->Get("h_avg_weight_btagsf")->Clone("h_bsfweights");
	h_bsfweights_heavy_UP = (TH2D*)f_sfweights->Get("h_avg_weight_btagsf_heavy_UP")->Clone("h_bsfweights_heavy_UP");
	h_bsfweights_light_UP = (TH2D*)f_sfweights->Get("h_avg_weight_btagsf_light_UP")->Clone("h_bsfweights_light_UP");

	h_isrweights->SetDirectory(rootdir);
	h_bsfweights->SetDirectory(rootdir);
	h_bsfweights_heavy_UP->SetDirectory(rootdir);
	h_bsfweights_light_UP->SetDirectory(rootdir);

	f_sfweights->Close();

	// for FS to Fullsim
	f_sfweights  = TFile::Open("sf_el_tight_mini01.root","READ");
	h_eleweights = (TH2D*)f_sfweights->Get("histo2D")   ->Clone("h_eleweights");
	h_eleweights->SetDirectory(rootdir);
	f_sfweights->Close();
	f_sfweights  = TFile::Open("sf_mu_mediumID_mini02.root","READ");
	h_muoweights = (TH2D*)f_sfweights->Get("histo2D")   ->Clone("h_muoweights");
	h_muoweights->SetDirectory(rootdir);
	f_sfweights->Close();

	// for Fullsim to Data
	f_sfweights  = TFile::Open("kinematicBinSFele.root","READ");
	h_eleweights_id = (TH2D*)f_sfweights->Get("MVATight_and_TightIP2D_and_TightIP3D") -> Clone("h_eleweights_id");
	h_eleweightsiso = (TH2D*)f_sfweights->Get("MiniIso0p1_vs_AbsEta")                 -> Clone("h_eleweightsiso");
	h_eleweights_id->SetDirectory(rootdir);
	h_eleweightsiso->SetDirectory(rootdir);
	f_sfweights->Close();
	f_sfweights  = TFile::Open("TnP_MuonID_NUM_MediumID_DENOM_generalTracks_VAR_map_pt_eta.root","READ");
	h_muoweights_id = (TH2D*)f_sfweights->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_tag_IsoMu20_pass")   ->Clone("h_muoweights_id");
	h_muoweights_id->SetDirectory(rootdir);
	f_sfweights->Close();
	f_sfweights  = TFile::Open("TnP_MuonID_NUM_MiniIsoTight_DENOM_LooseID_VAR_map_pt_eta.root","READ");
	h_muoweightsiso = (TH2D*)f_sfweights->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_PF_pass_&_tag_IsoMu20_pass")   ->Clone("h_muoweightsiso");
	h_muoweightsiso->SetDirectory(rootdir);
	f_sfweights->Close();
	
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

	  if (nEventsTotal % 1000 == 0){ // progress feedback to user
	  	if (isatty(1)){ // xterm magic from L. Vacavant and A. Cerri               
          printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
                 "\033[0m\033[32m <---\033[0m\015", (float)nEventsTotal/(nEventsChain*0.01));
          fflush(stdout);
        }
      }

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
	  	  
	  if ( zmet.isData() && usejson && !goodrun(zmet.run(), zmet.lumi()) ) continue;

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
	  
	  //~-~-~-~-~-~-~-~~-//
	  //trigger variables//
	  //~-~-~-~-~-~-~-~-~//

	  
	  //-~-~-~-~-~-~-~-~-~-~-~-//
	  //Deal with event weights//
	  //-~-~-~-~-~-~-~-~-~-~-~-//
	  float weight = 1.0;
	  if( zmet.isData() ){
		weight = 1.0;
	  }else if( !zmet.isData() ){
		weight *= zmet.evt_scale1fb();
	  	if( TString(currentFile->GetTitle()).Contains("t5zz") ){
		  weight *= 2.11;
		}
	  	if( TString(currentFile->GetTitle()).Contains("dy_m50_mgmlm_ext1") ){
		  weight *= 3.545;
		}
	  }
	  
	  if( !zmet.isData() && dovtxreweighting ){
	  	// if( !TString(currentFile->GetTitle()).Contains("t5zz") ){
		  // weight *= h_vtxweight->GetBinContent(h_vtxweight->FindBin(zmet.nVert()));		
		  weight *= h_vtxweight->GetBinContent(h_vtxweight->FindBin(zmet.nTrueInt()));		
		// }
	  }

	  // if( sample == "zjets" ){
	  // 	if( TString(currentFile->GetTitle()).Contains("m50") ) weight *= 14987122./2550912.;
	  // }
	  

	  float event_met_pt = zmet.met_T1CHS_miniAOD_CORE_pt();
	  float event_met_ph = zmet.met_T1CHS_miniAOD_CORE_phi();

	  
	  // float event_ht    = zmet.ht();
	  // float event_njets = zmet.njets();

	  // if( jes_up ){
	  // 	event_ht    = zmet.ht_up();
	  // 	event_njets = zmet.njets_up();

	  // }else if( jes_dn ){
	  // 	event_ht    = zmet.ht_dn();
	  // 	event_njets = zmet.njets_dn();

	  // }

	  if( TString(currentFile->GetTitle()).Contains("t5zz") ){
		// if( zmet.met_T1CHS_miniAOD_CORE_pt() > 6500 ) continue;

		// if( !(zmet.mass_gluino() == 1050 && zmet.mass_LSP() == 800) ) continue;
	  	// if( (zmet.mass_gluino() == 1050 && zmet.mass_LSP() == 850) ){
	  	// // if( zmet.met_T1CHS_miniAOD_CORE_pt() > 6500 && zmet.met_pt() < 6500 ){
	  	//   cout<<"miniAOD met: "<<zmet.met_pt()<<" | rawMET: "<<zmet.met_rawPt()<<" | COREMET: "<<zmet.met_T1CHS_miniAOD_CORE_pt()<<endl;
	  	// }
	  	if( zmet.met_T1CHS_miniAOD_CORE_pt() < 6500 ){
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
	  	}else if( zmet.met_pt() > 6500 ){
	  	  // cout<<"miniAOD met: "<<zmet.met_pt()<<" | rawMET: "<<zmet.met_rawPt()<<endl;
	  	  // cout<<zmet.evt_xsec()<<endl;
	  	  // cout<<zmet.evt_nEvts()<<endl;
	  	  // cout<<zmet.evt_scale1fb()<<endl;
	  	  // cout<<zmet.nTrueInt()<<endl;
	  	  continue;
	  	}

	  }else{
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
		
	  }
	  
	  if( TString(currentFile->GetTitle()).Contains("t5zz") ){
		if( TString(sample).Contains("signal1100200") && !(zmet.mass_gluino() == 1000 && zmet.mass_LSP() == 800) ) continue;
		if( TString(selection).Contains("losplit") && !(zmet.mass_gluino() == 1000 && zmet.mass_LSP() == 800) ) continue;
		if( event_met_pt > 225 ) nlosplit += weight;
		if( TString(selection).Contains("hisplit") && !(zmet.mass_gluino() == 1050 && zmet.mass_LSP() == 400) ) continue;
		if( event_met_pt > 225 ) nhisplit += weight;
	  }

// 	  if(
// 		 // 1460034810 ||
// 		 //  240607834 ||
// 		 //  838557150 ){

// // zmet.evt() == 934930608 ||
// // zmet.evt() == 272622131 ||
// // zmet.evt() == 2097023176

// 		 // christian events
// zmet.evt() ==      91733880 ||
// zmet.evt() ==     995726603 ||
// zmet.evt() ==     384783207 ||
// zmet.evt() ==     581236778 ||
// zmet.evt() ==    1128357558 ||
// zmet.evt() ==     403253061 ||
// zmet.evt() ==     898021054 ||
// zmet.evt() ==     532257885 ||
// zmet.evt() ==     828778701 ||
// zmet.evt() ==    1341174591 ||
// zmet.evt() ==     272708087 ||
// zmet.evt() ==    1321540936 ||
// zmet.evt() ==     189657985 ||
// zmet.evt() ==    1523328940 ||
// zmet.evt() ==    1523877064 ||
// zmet.evt() ==     498745462 ||
// zmet.evt() ==    1458781899 ||
// zmet.evt() ==     534484562 ||
// zmet.evt() ==    1395571756 ||
// zmet.evt() ==    1640674051 ||
// zmet.evt() ==     428341485 ||
// zmet.evt() ==     518382269 ||
// zmet.evt() ==     408995381 ||
// zmet.evt() ==     662566378 ||
// zmet.evt() ==     663855252 ||
// zmet.evt() ==     856330582 ||
// zmet.evt() ==      94079532 ||
// zmet.evt() ==     269336427 ||
// zmet.evt() ==     275389649 ||
// zmet.evt() ==     583823335 ||
// zmet.evt() ==     955296115 ||
// zmet.evt() ==     105865683 ||
// zmet.evt() ==     170110611 ||
// zmet.evt() ==     115572426 ||
// zmet.evt() ==     375620266 ||
// zmet.evt() ==     433563640 ||
// zmet.evt() ==     514067061 ||
// zmet.evt() ==     658381701 ||
// zmet.evt() ==    2887934467 ||
// zmet.evt() ==    3119457226 ||
// zmet.evt() ==     305938885 ||
// zmet.evt() ==    1433198965 ||
// zmet.evt() ==    1180144798 ||
// zmet.evt() ==    1955523829 ||
// zmet.evt() ==    1240111493 ||
// zmet.evt() ==    2690660742 ||
// zmet.evt() ==     311377665 ||
// zmet.evt() ==    1062159148 ||
// zmet.evt() ==     466300021 ||
// zmet.evt() ==     552331404 ||
// zmet.evt() ==    1017097676 ||
// zmet.evt() ==    1148935813 ||
// zmet.evt() ==    2166823585 ||
// zmet.evt() ==    2963378283 ||
// zmet.evt() ==    3010206426 ||
// zmet.evt() ==     275682628 ||
// zmet.evt() ==     328622283 ||
// zmet.evt() ==     365129122 ||
// zmet.evt() ==     212481745 ||
// zmet.evt() ==     425075862 ||
// zmet.evt() ==     397385233 ||
// zmet.evt() ==      36914698 ||
// zmet.evt() ==      84067364 ||
// zmet.evt() ==     692149758 ||
// zmet.evt() ==     674743624 ||
// zmet.evt() ==      39751186 ||
// zmet.evt() ==     281655459 ||
// zmet.evt() ==     164344750 ||
// zmet.evt() ==    1834915362 ||
// zmet.evt() ==    1734542357 ||
// zmet.evt() ==    1750311294 ||
// zmet.evt() ==     387754935 ||
// zmet.evt() ==    1629797629 ||
// zmet.evt() ==     798835684 ||
// zmet.evt() ==    1114679529 ||
// zmet.evt() ==    2188652359 ||
// zmet.evt() ==    2231938513 ||
// zmet.evt() ==    3269629166 ||
// zmet.evt() ==    3296086248 ||
// zmet.evt() ==    3442144600 ||
// zmet.evt() ==    3558707175 ||
// zmet.evt() ==     556529889 ||
// zmet.evt() ==     287630862 ||
// zmet.evt() ==     336250172 ||
// zmet.evt() ==     507830966 ||
// zmet.evt() ==     705392050 ||
// zmet.evt() ==     170022302 ||
// zmet.evt() ==     493041919 ||
// zmet.evt() ==     674186184 ||
// zmet.evt() ==      96555225 ||
// zmet.evt() ==     176770264 ||
// zmet.evt() ==     440274765 ||
// zmet.evt() ==     658814007 ||
// zmet.evt() ==    1202555176 ||
// zmet.evt() ==    1222405135 ||
// zmet.evt() ==    1257377315 ||
// zmet.evt() ==     105811178 ||
// zmet.evt() ==    1638368691 ||
// zmet.evt() ==    1716250145 ||
// zmet.evt() ==    1642957017 ||
// zmet.evt() ==    1696298344 ||
// zmet.evt() ==     319646535 ||
// zmet.evt() ==     663402455 ||
// zmet.evt() ==    1286269698 ||
// zmet.evt() ==    1625300720 ||
// zmet.evt() ==     223264003 ||
// zmet.evt() ==     961253777 ||
// zmet.evt() ==     586706890 ||
// zmet.evt() ==    1266094471 ||
// zmet.evt() ==      90768710 ||
// zmet.evt() ==    1147003038 ||
// zmet.evt() ==    1177797272 ||
// zmet.evt() ==     760744135 ||
// zmet.evt() ==     763385219 ||
// zmet.evt() ==    1251599978 ||
// zmet.evt() ==    1462634786 ||
// zmet.evt() ==     833004454 ||
// zmet.evt() ==    1660391926 ||
// zmet.evt() ==      33055224 ||
// zmet.evt() ==     157025333 ||
// zmet.evt() ==     708450771 ||
// zmet.evt() ==    1168308546 ||
// zmet.evt() ==    1297161823 ||
// zmet.evt() ==    1419703703 ||
// zmet.evt() ==     740368788 ||
// zmet.evt() ==    1198414201 ||
// zmet.evt() ==    1032548693 ||
// zmet.evt() ==    1329726811 ||
// zmet.evt() ==    1595737936 ||
// zmet.evt() ==      21182302 ||
// zmet.evt() ==     263057789 ||
// zmet.evt() ==    1082328063 ||
// zmet.evt() ==    1308660423 ||
// zmet.evt() ==     103484639 ||
// zmet.evt() ==    1745972648 ||
// zmet.evt() ==     776844947 ||
// zmet.evt() ==    1505184501 ||
// zmet.evt() ==    1985282889 ||
// zmet.evt() ==    2065291556 ||
// zmet.evt() ==      20322433 ||
// zmet.evt() ==      41245134 ||
// zmet.evt() ==      73041017 ||
// zmet.evt() ==     107295541 ||
// zmet.evt() ==     128078212 ||
// zmet.evt() ==     225502854 ||
// zmet.evt() ==     300627332 ||
// zmet.evt() ==     516873912 ||
// zmet.evt() ==     539562778 ||
// zmet.evt() ==     696450320 ||
// zmet.evt() ==     892661884 ||
// zmet.evt() ==    1069734519 ||
// zmet.evt() ==    1108172148 ||
// zmet.evt() ==    1267399188 ||
// zmet.evt() ==    1443741303 ||
// zmet.evt() ==    1537520654 ||
// zmet.evt() ==    1919340805 ||
// zmet.evt() ==    2430209084 ||
// zmet.evt() ==      26822349 ||
// zmet.evt() ==      41490551 ||
// zmet.evt() ==     234081679 ||
// zmet.evt() ==     341764569 ||
// zmet.evt() ==     692823763 ||
// zmet.evt() ==    1048404243 ||
// zmet.evt() ==     925671441 ||
// zmet.evt() ==      89897426 ||
// zmet.evt() ==    1309811653 ||
// zmet.evt() ==     274514821 ||
// zmet.evt() ==     722710893 ||
// zmet.evt() ==     796106322 ||
// zmet.evt() ==     827180522 ||
// zmet.evt() ==     986784684 ||
// zmet.evt() ==     103482138 ||
// zmet.evt() ==     392864049 ||
// zmet.evt() ==      20367250 ||
// zmet.evt() ==     177284394 ||
// zmet.evt() ==     324611814 ||
// zmet.evt() ==     380434487 ||
// zmet.evt() ==     482357173 ||
// zmet.evt() ==     505634325 ||
// zmet.evt() ==     612827466 ||
// zmet.evt() ==     621448549 ||
// zmet.evt() ==     677296557 ||
// zmet.evt() ==     805055209 ||
// zmet.evt() ==     881389384 ||
// zmet.evt() ==     584707881 ||
// zmet.evt() ==     568343962 ||
// zmet.evt() ==     670205982 ||
// zmet.evt() ==     650224687 ||
// zmet.evt() ==      67471649 ||
// zmet.evt() ==     210897611 ||
// zmet.evt() ==     814487875 ||
// zmet.evt() ==     323009928 ||
// zmet.evt() ==     349280206 ||
// zmet.evt() ==    1054668903 ||
// zmet.evt() ==    1497212768 ||
// zmet.evt() ==    1215849521 ||
// zmet.evt() ==    1430059679 ||
// zmet.evt() ==    1436702562 ||
// zmet.evt() ==     316334358 ||
// zmet.evt() ==    1010594407 ||
// zmet.evt() ==    1251770301 ||
// zmet.evt() ==    1359038487 ||
// zmet.evt() ==    1650117307 ||
// zmet.evt() ==     226812915 ||
// zmet.evt() ==     275115746 ||
// zmet.evt() ==       6795480 ||
// zmet.evt() ==     233729788 ||
// zmet.evt() ==      93371983 ||
// zmet.evt() ==     258991225 ||
// zmet.evt() ==     178977223 ||
// zmet.evt() ==     602592167 ||
// zmet.evt() ==     795095755 ||
// zmet.evt() ==      20822516 ||
// zmet.evt() ==      41466128 ||
// zmet.evt() ==     249587960 ||
// zmet.evt() ==      31796123 ||
// zmet.evt() ==     116612272 ||
// zmet.evt() ==     454339165 ||
// zmet.evt() ==      42618760 ||
// zmet.evt() ==      12889205 ||
// zmet.evt() ==     426849303 ||
// zmet.evt() ==     482528238 ||
// zmet.evt() ==     550346018 ||
// zmet.evt() ==     233577435 ||
// zmet.evt() ==     189902157 ||
// zmet.evt() ==     269698707 ||
// zmet.evt() ==     361634321 ||
// zmet.evt() ==     523496749 ||
// zmet.evt() ==    1052179793 ||
// zmet.evt() ==     239191202 ||
// zmet.evt() ==     240387660 ||
// zmet.evt() ==     256370278 ||
// zmet.evt() ==      21882343 ||
// zmet.evt() ==     140053977 ||
// zmet.evt() ==     193470262 ||
// zmet.evt() ==     902808627 ||
// zmet.evt() ==    1790571179 ||
// zmet.evt() ==    2317515384 ||
// zmet.evt() ==     231914682 ||
// zmet.evt() ==     252429405 ||
// zmet.evt() ==    1337085261 ||
// zmet.evt() ==    1350737159 ||
// zmet.evt() ==    1403642411 ||
// zmet.evt() ==    1688970085 ||
// zmet.evt() ==    1969166416 ||
// zmet.evt() ==    2005492283 ||
// zmet.evt() ==    2341583076 ||
// zmet.evt() ==    2858185346 ||
// zmet.evt() ==    3138551976 ||
// zmet.evt() ==    3231057927 ||
// zmet.evt() ==    3441044752 ||
// zmet.evt() ==    3514810443 ||
// zmet.evt() ==      69572768 ||
// zmet.evt() ==     589934139 ||
// zmet.evt() ==    1301796409 ||
// zmet.evt() ==    1481747361 ||
// zmet.evt() ==      11489442 ||
// zmet.evt() ==     173491301 ||
// zmet.evt() ==      55486631 ||
// zmet.evt() ==      96523447 ||
// zmet.evt() ==     108218573 ||
// zmet.evt() ==     409198651 ||
// zmet.evt() ==     423438580 ||
// zmet.evt() ==     185546020 ||
// zmet.evt() ==     184681443 ||
// zmet.evt() ==     457764099 ||
// zmet.evt() ==     171857983 ||
// zmet.evt() ==     255631616 ||
// zmet.evt() ==     446828372 ||
// zmet.evt() ==     920947145 ||
// zmet.evt() ==     204405015 ||
// zmet.evt() ==     388862460 ||
// zmet.evt() ==     447150883 ||
// zmet.evt() ==     746925313 ||
// zmet.evt() ==     874046137 ||
// zmet.evt() ==     590055906 ||
// zmet.evt() ==     705577258 ||
// zmet.evt() ==    1539053393 ||
// zmet.evt() ==     256288625 ||
// zmet.evt() ==    1154074355 ||
// zmet.evt() ==    1657475558 ||
// zmet.evt() ==     863560427 ||
// zmet.evt() ==     995958611 ||
// zmet.evt() ==     823781616 ||
// zmet.evt() ==    1813666219 ||
// zmet.evt() ==      27576865 ||
// zmet.evt() ==      99784606 ||
// zmet.evt() ==     230060291 ||
// zmet.evt() ==     614060858 ||
// zmet.evt() ==     723737061 ||
// zmet.evt() ==     768202876 ||
// zmet.evt() ==     339134901 ||
// zmet.evt() ==     441670092 ||
// zmet.evt() ==     774419736 ||
// zmet.evt() ==    1277085482 ||
// zmet.evt() ==     931984973 ||
// zmet.evt() ==       9762539 ||
// zmet.evt() ==      44746550 ||
// zmet.evt() ==     280874354 ||
// zmet.evt() ==     308720504 ||
// zmet.evt() ==      52223949 ||
// zmet.evt() ==     797710850 ||
// zmet.evt() ==      85386071 ||
// zmet.evt() ==     259332110 ||
// zmet.evt() ==      86218312 ||
// zmet.evt() ==     202232107 ||
// zmet.evt() ==     215641741 ||
// zmet.evt() ==     130255936 ||
// zmet.evt() ==     218517351 ||
// zmet.evt() ==     382711079 ||
// zmet.evt() ==     302925101 ||
// zmet.evt() ==     611814869 ||
// zmet.evt() ==     618004443 ||
// zmet.evt() ==    1367091805 ||
// zmet.evt() ==    1655930974 ||
// zmet.evt() ==     521489326 ||
// zmet.evt() ==    1045382283 ||
// zmet.evt() ==     481180724 ||
// zmet.evt() ==     491326881 ||
// zmet.evt() ==     478861948 ||
// zmet.evt() ==     388546353 ||
// zmet.evt() ==       6777225 ||
// zmet.evt() ==     267790777 ||
// zmet.evt() ==     510340245 ||
// zmet.evt() ==     544361601 ||
// zmet.evt() ==     688272335 ||
// zmet.evt() ==     261570755 ||
// zmet.evt() ==     205417500 ||
// zmet.evt() ==      48441630 ||
// zmet.evt() ==     421581016 ||
// zmet.evt() ==    1056833375 ||
// zmet.evt() ==     600933415 ||
// zmet.evt() ==      72219652 ||
// zmet.evt() ==      96856536 ||
// zmet.evt() ==     448114023 ||
// zmet.evt() ==    2315755316 ||
// zmet.evt() ==    2690608828 ||
// zmet.evt() ==     931364577 ||
// zmet.evt() ==     669038277 ||
// zmet.evt() ==    2128382035 ||
// zmet.evt() ==    2587403505 ||
// zmet.evt() ==    3310676988 ||
// zmet.evt() ==    2303569008 ||
// zmet.evt() ==      30892588 ||
// zmet.evt() ==     115352716 ||
// zmet.evt() ==     583216391 ||
// zmet.evt() ==     652937977 ||
// zmet.evt() ==     139295063 ||
// zmet.evt() ==     247646752 ||
// zmet.evt() ==     372121983 ||
// zmet.evt() ==      50972622 ||
// zmet.evt() ==      40549049 ||
// zmet.evt() ==     189966915 ||
// zmet.evt() ==    1281136923 ||
// zmet.evt() ==    1265551771 ||
// zmet.evt() ==     388943916 ||
// zmet.evt() ==     417395249 ||
// zmet.evt() ==    1799203724 ||
// zmet.evt() ==     648698515 ||
// zmet.evt() ==    1334283906 ||
// zmet.evt() ==     290817740 ||
// zmet.evt() ==     467127513 ||
// zmet.evt() ==       3926234 ||
// zmet.evt() ==     742485378 ||
// zmet.evt() ==     704674488 ||
// zmet.evt() ==     455878919 ||
// zmet.evt() ==     244164241 ||
// zmet.evt() ==     314328975 ||
// zmet.evt() ==      55334056 ||
// zmet.evt() ==     776799990 ||
// zmet.evt() ==     487741834 ||
// zmet.evt() ==     207851666 ||
// zmet.evt() ==      13699553 ||
// zmet.evt() ==     102443765 ||
// zmet.evt() ==     260382774 ||
// zmet.evt() ==     761008490 ||
// zmet.evt() ==    1502453305 ||
// zmet.evt() ==     375567487 ||
// zmet.evt() ==     345411333 ||
// zmet.evt() ==    1497446944 ||
// zmet.evt() ==     949766574 ||
// zmet.evt() ==     999398727 ||
// zmet.evt() ==    1218844064 ||
// zmet.evt() ==     273328343 ||
// zmet.evt() ==     188898327 ||
// zmet.evt() ==      80298093 ||
// zmet.evt() ==     153686592 ||
// zmet.evt() ==     792067175 ||
// zmet.evt() ==    1207963905 ||
// zmet.evt() ==    1545750828 ||
// zmet.evt() ==    1095160227 ||
// zmet.evt() ==       7021394 ||
// zmet.evt() ==      64918964 ||
// zmet.evt() ==      66079462 ||
// zmet.evt() ==     204066420 ||
// zmet.evt() ==     533454589 ||
// zmet.evt() ==     158833244 ||
// zmet.evt() ==     485961381 ||
// zmet.evt() ==    1065715946 ||
// zmet.evt() ==    1071386649 ||
// zmet.evt() ==    1184355622 ||
// zmet.evt() ==     712063922 ||
// zmet.evt() ==     548587800 ||
// zmet.evt() ==     135484035 ||
// zmet.evt() ==    3103235364 ||
// zmet.evt() ==      55729742 ||
// zmet.evt() ==     914932148 ||
// zmet.evt() ==    1892183801 ||
// zmet.evt() ==    2993442939 ||
// zmet.evt() ==    2061973406 ||
// zmet.evt() ==     253016921 ||
// zmet.evt() ==    2668631268 ||
// zmet.evt() ==     516214375 ||
// zmet.evt() ==    3087525423 ||
// zmet.evt() ==    2745610726 ||
// zmet.evt() ==     248089675 ||
// zmet.evt() ==     211352775 ||
// zmet.evt() ==     309534705 ||
// zmet.evt() ==     342814344 ||
// zmet.evt() ==     373152966 ||
// zmet.evt() ==     589226659 ||
// zmet.evt() ==    1103925997 ||
// zmet.evt() ==     149907153 ||
// zmet.evt() ==     435906043 ||
// zmet.evt() ==    2715088145 ||
// zmet.evt() ==    2176509129 ||
// zmet.evt() ==     760109811 ||
// zmet.evt() ==    3417736598 ||
// zmet.evt() ==    2358114572 ||
// zmet.evt() ==    2564333855 ||
// zmet.evt() ==     212214576 ||
// zmet.evt() ==     203727723 ||
// zmet.evt() ==      71175647 ||
// zmet.evt() ==     402742312 ||
// zmet.evt() ==     284169581 ||
// zmet.evt() ==     482756421 ||
// zmet.evt() ==     399252691 ||
// zmet.evt() ==     305116194 ||
// zmet.evt() ==     713161305 ||
// zmet.evt() ==     245278791 ||
// zmet.evt() ==     549092878 ||
// zmet.evt() ==    1069218258 ||
// zmet.evt() ==     151001659 ||
// zmet.evt() ==     162308383 ||
// zmet.evt() ==    2187998222 ||
// zmet.evt() ==     965812963 ||
// zmet.evt() ==     789229786 ||
// zmet.evt() ==    1227277425 ||
// zmet.evt() ==    1386963055 ||
// zmet.evt() ==    1023856829 ||
// zmet.evt() ==     171372591 ||
// zmet.evt() ==      56042653 ||
// zmet.evt() ==     499309199 ||
// zmet.evt() ==     293953355 ||
// zmet.evt() ==    1225902613 ||
// zmet.evt() ==     581337343 ||
// zmet.evt() ==     302555094 ||
// zmet.evt() ==     482931214 ||
// zmet.evt() ==    1441663995 ||
// zmet.evt() ==    1647550356 ||
// zmet.evt() ==     114775916 ||
// zmet.evt() ==     635225700 ||
// zmet.evt() ==     824897420 ||
// zmet.evt() ==     336862499 ||
// zmet.evt() ==    1050955298 ||
// zmet.evt() ==    1045691850 ||
// zmet.evt() ==     418321233 ||
// zmet.evt() ==     889776468 ||
// zmet.evt() ==    1350291194 ||
// zmet.evt() ==     868701812 ||
// zmet.evt() ==     889831759 ||
// zmet.evt() ==     567897420 ||
// zmet.evt() ==    1205896224 ||
// zmet.evt() ==    1251222929 ||
// zmet.evt() ==     621648474 ||
// zmet.evt() ==    1408354490 ||
// zmet.evt() ==     154768076 ||
// zmet.evt() ==     403556326 ||
// zmet.evt() ==    1015112549 ||
// zmet.evt() ==     718406407 ||
// zmet.evt() ==    1545104200 ||
// zmet.evt() ==     552872609 ||
// zmet.evt() ==    2075765256 ||
// zmet.evt() ==     691628918 ||
// zmet.evt() ==    2103245964 ||
// zmet.evt() ==    2621636555 ||
// zmet.evt() ==     698145799 ||
// zmet.evt() ==     675906514 ||
// zmet.evt() ==     818669081 ||
// zmet.evt() ==    1259942938 ||
// zmet.evt() ==      96262357 ||
// zmet.evt() ==    1399666684 ||
// zmet.evt() ==    1012558153 ||
// zmet.evt() ==     337771862 ||
// zmet.evt() ==      78609791 ||
// zmet.evt() ==     317584316 ||
// zmet.evt() ==     987863912 ||
// zmet.evt() ==     217828533 ||
// zmet.evt() ==     801598703 ||
// zmet.evt() ==     347886779 ||
// zmet.evt() ==     316828761 ||
// zmet.evt() ==     280834948 ||
// zmet.evt() ==     626617344 ||
// zmet.evt() ==     639630718 ||
// zmet.evt() ==     323939122 ||
// zmet.evt() ==     607604321 ||
// zmet.evt() ==     517145322 ||
// zmet.evt() ==     283152961 ||
// zmet.evt() ==     355470728 ||
// zmet.evt() ==     208092780 ||
// zmet.evt() ==     260777411 ||
// zmet.evt() ==      32681474 ||
// zmet.evt() ==     712905114 ||
// zmet.evt() ==      99456957 ||
// zmet.evt() ==     143234971 ||
// zmet.evt() ==      11771600 ||
// zmet.evt() ==     571880296 ||
// zmet.evt() ==     587721399 ||
// zmet.evt() ==     142895111 ||
// zmet.evt() ==     299598103 ||
// zmet.evt() ==     152292614 ||
// zmet.evt() ==     226768511 ||
// zmet.evt() ==     467416442 ||
// zmet.evt() ==     473850942 ||
// zmet.evt() ==     509546090 ||
// zmet.evt() ==      76515231 ||
// zmet.evt() ==      93057487 ||
// zmet.evt() ==     750950700 ||
// zmet.evt() ==     521792516 ||
// zmet.evt() ==     273418079 ||
// zmet.evt() ==     285432473 ||
// zmet.evt() ==     127346500 ||
// zmet.evt() ==     243699833 ||
// zmet.evt() ==     201916331 ||
// zmet.evt() ==     743124668 ||
// zmet.evt() ==     855783995 ||
// zmet.evt() ==    1190849019 ||
// zmet.evt() ==     244418368 ||
// zmet.evt() ==     477494557 ||
// zmet.evt() ==     293458372 ||
// zmet.evt() ==     797345754 ||
// zmet.evt() ==     898880648 ||
// zmet.evt() ==     548388181 ||
// zmet.evt() ==     251428268 ||
// zmet.evt() ==     276683519 ||
// zmet.evt() ==     420148880 ||
// zmet.evt() ==     480307076 ||
// zmet.evt() ==      26420076 ||
// zmet.evt() ==      48199504 ||
// zmet.evt() ==     598019576 ||
// zmet.evt() ==     178043401 ||
// zmet.evt() ==    1280019522 ||
// zmet.evt() ==    2559753570 ||
// zmet.evt() ==     285272317 ||
// zmet.evt() ==    1717661178 ||
// zmet.evt() ==    1360605293 ||
// zmet.evt() ==    1756650511 ||
// zmet.evt() ==    1995754313 ||
// zmet.evt() ==    3203785513 ||
// zmet.evt() ==    2629478864 ||
// zmet.evt() ==    2193922587 ||
// zmet.evt() ==    2499148870 ||
// zmet.evt() ==    2587525031 ||
// zmet.evt() ==    2950925878 ||
// zmet.evt() ==    3003459558 ||
// zmet.evt() ==    3402590460 ||
// zmet.evt() ==     658222948 ||
// zmet.evt() ==    1407348043 ||
// zmet.evt() ==    1695455893 ||
// zmet.evt() ==     168251361 ||
// zmet.evt() ==     907136773 ||
// zmet.evt() ==     603582911 ||
// zmet.evt() ==     856114721 ||
// zmet.evt() ==    1664531313 ||
// zmet.evt() ==    2313855924 ||
// zmet.evt() ==     272557052 ||
// zmet.evt() ==      14931594 ||
// zmet.evt() ==      54193754 ||
// zmet.evt() ==      34949358 ||
// zmet.evt() ==     113999620 ||
// zmet.evt() ==     165179967 ||
// zmet.evt() ==     105579285 ||
// zmet.evt() ==     189538761 ||
// zmet.evt() ==     721678167 ||
// zmet.evt() ==     203471341 ||
// zmet.evt() ==     282901028 ||
// zmet.evt() ==     633616507 ||
// zmet.evt() ==     663003077 ||
// zmet.evt() ==     967457859 ||
// zmet.evt() ==      63099359 ||
// zmet.evt() ==     565319735 ||
// zmet.evt() ==     571126039 ||
// zmet.evt() ==     879605239 ||
// zmet.evt() ==     402962104 ||
// zmet.evt() ==    1041351720 ||
// zmet.evt() ==    1090574508 ||
// zmet.evt() ==     380709044 ||
// zmet.evt() ==     781872540 ||
// zmet.evt() ==     451128819 ||
// zmet.evt() ==     479676628 ||
// zmet.evt() ==     612218467 ||
// zmet.evt() ==     917986500 ||
// zmet.evt() ==     810680183 ||
// zmet.evt() ==     900433382 ||
// zmet.evt() ==     912927068 ||
// zmet.evt() ==     162707819 ||
// zmet.evt() ==     580457656 ||
// zmet.evt() ==     879809183 ||
// zmet.evt() ==    1042537633 ||
// zmet.evt() ==    1058516872 ||
// zmet.evt() ==      21099196 ||
// zmet.evt() ==     578469048 ||
// zmet.evt() ==     603939460 ||
// zmet.evt() ==     971745638 ||
// zmet.evt() ==    1443630988 ||
// zmet.evt() ==    1569220948 ||
// zmet.evt() ==      89918855 ||
// zmet.evt() ==     644493112 ||
// zmet.evt() ==     647152059 ||
// zmet.evt() ==     653241393 ||
// zmet.evt() ==    1264343098 ||
// zmet.evt() ==     821461335 ||
// zmet.evt() ==     189987738 ||
// zmet.evt() ==     394528714 ||
// zmet.evt() ==       6843671 ||
// zmet.evt() ==     368579656 ||
// zmet.evt() ==     643476202 ||
// zmet.evt() ==     326140164 ||
// zmet.evt() ==     382433705 ||
// zmet.evt() ==     507819696 ||
// zmet.evt() ==     697700244 ||
// zmet.evt() ==    1179116495 ||
// zmet.evt() ==    1278270700 ||
// zmet.evt() ==    1126520272 ||
// zmet.evt() ==     423652875 ||
// zmet.evt() ==    1029550055 ||
// zmet.evt() ==    1296297613 ||
// zmet.evt() ==      41382691 ||
// zmet.evt() ==     232243102 ||
// zmet.evt() ==    1000807674 ||
// zmet.evt() ==     558654296 ||
// zmet.evt() ==     892773393 ||
// zmet.evt() ==    1020505524 ||
// zmet.evt() ==    1104037552 ||
// zmet.evt() ==     928630480 ||
// zmet.evt() ==     824577530 ||
// zmet.evt() ==      17698835 ||
// zmet.evt() ==      46161172 ||
// zmet.evt() ==     242909619 ||
// zmet.evt() ==     821491164 ||
// zmet.evt() ==     461377290 ||
// zmet.evt() ==     222606973 ||
// zmet.evt() ==     413396338 ||
// zmet.evt() ==     347720004 ||
// zmet.evt() ==       2414337 ||
// zmet.evt() ==      36803384 ||
// zmet.evt() ==      82598744 ||
// zmet.evt() ==      84159245 ||
// zmet.evt() ==     475487001 ||
// zmet.evt() ==     121307571 ||
// zmet.evt() ==     286742443 ||
// zmet.evt() ==     874992762 ||
// zmet.evt() ==     292565379 ||
// zmet.evt() ==     865216936 ||
// zmet.evt() ==    1320451288 ||
// zmet.evt() ==     175974976 ||
// zmet.evt() ==     818050186 ||
// zmet.evt() ==     120770119 ||
// zmet.evt() ==    1516864277 ||
// zmet.evt() ==     285293893 ||
// zmet.evt() ==     484449780 ||
// zmet.evt() ==    1327264605 ||
// zmet.evt() ==     449644895 ||
// zmet.evt() ==     497259629 ||
// zmet.evt() ==    1053655257 ||
// zmet.evt() ==     514371613 ||
// zmet.evt() ==    1234599047 ||
// zmet.evt() ==    1304650600 ||
// zmet.evt() ==     112561198 ||
// zmet.evt() ==     298455048 ||
// zmet.evt() ==      40042896 ||
// zmet.evt() ==     573585241 ||
// zmet.evt() ==    1432601602 ||
// zmet.evt() ==    1790011864 ||
// zmet.evt() ==    1795220892 ||
// zmet.evt() ==     208963482 ||
// zmet.evt() ==     647041243 ||
// zmet.evt() ==      92155055 ||
// zmet.evt() ==     953914919 ||
// zmet.evt() ==     515657902 ||
// zmet.evt() ==    1555764824 ||
// zmet.evt() ==     759747604 ||
// zmet.evt() ==     392938409 ||
// zmet.evt() ==       5577712 ||
// zmet.evt() ==     996424895 ||
// zmet.evt() ==      49226259 ||
// zmet.evt() ==     906496573 ||
// zmet.evt() ==     906665245 ||
// zmet.evt() ==     938643414 ||
// zmet.evt() ==    1086506314 ||
// zmet.evt() ==    1091603529 ||
// zmet.evt() ==     872174795 ||
// zmet.evt() ==    1162004400 ||
// zmet.evt() ==     717151654 ||
// zmet.evt() ==     947600111 ||
// zmet.evt() ==      63137127 ||
// zmet.evt() ==     393866247 ||
// zmet.evt() ==     490698250 ||
// zmet.evt() ==     317298556 ||
// zmet.evt() ==     781166252 ||
// zmet.evt() ==     102058575 ||
// zmet.evt() ==     169394828 ||
// zmet.evt() ==     287960682 ||
// zmet.evt() ==     698981990 ||
// zmet.evt() ==     300541745 ||
// zmet.evt() ==     477221680 ||
// zmet.evt() ==    2576560117 ||
// zmet.evt() ==      12809651 ||
// zmet.evt() ==    2971690922 ||
// zmet.evt() ==     499734398 ||
// zmet.evt() ==     504185758 ||
// zmet.evt() ==    1372964106 ||
// zmet.evt() ==     587445581 ||
// zmet.evt() ==      67712713 ||
// zmet.evt() ==     525704830 ||
// zmet.evt() ==    1462413113 ||
// zmet.evt() ==     607390354 ||
// zmet.evt() ==    2633165621 ||
// zmet.evt() ==    2660710351 ||
// zmet.evt() ==     338699690 ||
// zmet.evt() ==    1748911874 ||
// zmet.evt() ==    1722962454 ||
// zmet.evt() ==      68872184 ||
// zmet.evt() ==      99835614 ||
// zmet.evt() ==     351313184 ||
// zmet.evt() ==     178726031 ||
// zmet.evt() ==       6564414 ||
// zmet.evt() ==      71461634 ||
// zmet.evt() ==     129373690 ||
// zmet.evt() ==     228148027 ||
// zmet.evt() ==      58259852 ||
// zmet.evt() ==     420025874 ||
// zmet.evt() ==     371374014 ||
// zmet.evt() ==     562356759 ||
// zmet.evt() ==    3220424640 ||
// zmet.evt() ==    1654129838 ||
// zmet.evt() ==    2476194683 ||
// zmet.evt() ==    2479888404 ||
// zmet.evt() ==    2847497629 ||
// zmet.evt() ==    2313534920 ||
// zmet.evt() ==     377618640 ||
// zmet.evt() ==     930088491 ||
// zmet.evt() ==     103864737 ||
// zmet.evt() ==     270345207 ||
// zmet.evt() ==    1846065625 ||
// zmet.evt() ==    3248204216 ||
// zmet.evt() ==    1322389181 ||
// zmet.evt() ==    2601385138 ||
// zmet.evt() ==    1230634172 ||
// zmet.evt() ==    2195167695 ||
// zmet.evt() ==    2956846478 ||
// zmet.evt() ==    3366718235 ||
// zmet.evt() ==    3303027576 ||
// zmet.evt() ==    2134599355 ||
// zmet.evt() ==    2808790844 ||
// zmet.evt() ==    1207320050 ||
// zmet.evt() ==     189328669 ||
// zmet.evt() ==     486254325 ||
// zmet.evt() ==     490451499 ||
// zmet.evt() ==     493274190 ||
// zmet.evt() ==     759479556 ||
// zmet.evt() ==     140722489 ||
// zmet.evt() ==     146951700 ||
// zmet.evt() ==     683315588 ||
// zmet.evt() ==     480808344 ||
// zmet.evt() ==     176618831 ||
// zmet.evt() ==     370465266 ||
// zmet.evt() ==     198093774 ||
// zmet.evt() ==     321327578 ||
// zmet.evt() ==     409166100 ||
// zmet.evt() ==     474452644 ||
// zmet.evt() ==     791478802 ||
// zmet.evt() ==     416177193 ||
// zmet.evt() ==     477692584 ||
// zmet.evt() ==     483316187 ||
// zmet.evt() ==     620961824 ||
// zmet.evt() ==    1268489075 ||
// zmet.evt() ==    1174620486 ||
// zmet.evt() ==     670671202 ||
// zmet.evt() ==    1234332020 ||
// zmet.evt() ==     268711048 ||
// zmet.evt() ==      47477174 ||
// zmet.evt() ==      49293139 ||
// zmet.evt() ==    1660713001 ||
// zmet.evt() ==     685923062 ||
// zmet.evt() ==    1380330960 ||
// zmet.evt() ==      29612091 ||
// zmet.evt() ==     989908318 ||
// zmet.evt() ==     195655000 ||
// zmet.evt() ==    1367664618 ||
// zmet.evt() ==     236873254 ||
// zmet.evt() ==    1326718395 ||
// zmet.evt() ==    1404277461 ||
// zmet.evt() ==    1133737313 ||
// zmet.evt() ==    2125545626 ||
// zmet.evt() ==    1869742529 ||
// zmet.evt() ==    2004270410 ||
// zmet.evt() ==    1560790397 ||
// zmet.evt() ==     776530443 ||
// zmet.evt() ==       2702864 ||
// zmet.evt() ==    1102067159 ||
// zmet.evt() ==    1229506865 ||
// zmet.evt() ==    1627897684 ||
// zmet.evt() ==    1689668021 ||
// zmet.evt() ==    1374265051 ||
// zmet.evt() ==     297581223 ||
// zmet.evt() ==    1304388933 ||
// zmet.evt() ==     891995917 ||
// zmet.evt() ==    1645504623 ||
// zmet.evt() ==      75934337 ||
// zmet.evt() ==    1264647118 ||
// zmet.evt() ==     396186535 ||
// zmet.evt() ==     850011120 ||
// zmet.evt() ==      62587581 ||
// zmet.evt() ==      68538554 ||
// zmet.evt() ==     305562220 ||
// zmet.evt() ==     687086175 ||
// zmet.evt() ==      84349285 ||
// zmet.evt() ==     881071504 ||
// zmet.evt() ==     331066524 ||
// zmet.evt() ==     744899907 ||
// zmet.evt() ==     166763948 ||
// zmet.evt() ==    1393905269 ||
// zmet.evt() ==     434906553 ||
// zmet.evt() ==     256173551 ||
// zmet.evt() ==    1069533136 ||
// zmet.evt() ==    1187446387 ||
// zmet.evt() ==     687026901 ||
// zmet.evt() ==      94901432 ||
// zmet.evt() ==    1317553291 ||
// zmet.evt() ==    1366706099 ||
// zmet.evt() ==    1900053665 ||
// zmet.evt() ==    1013469472 ||
// zmet.evt() ==     917339476 ||
// zmet.evt() ==     446542668 ||
// zmet.evt() ==     626717973 ||
// zmet.evt() ==    1631012758 ||
// zmet.evt() ==     378238847 ||
// zmet.evt() ==    1612071785 ||
// zmet.evt() ==     201218597 ||
// zmet.evt() ==     368290534 ||
// zmet.evt() ==    1071566426 ||
// zmet.evt() ==    1914313487 ||
// zmet.evt() ==     513489867 ||
// zmet.evt() ==    2028601688 ||
// zmet.evt() ==    2115563426 ||
// zmet.evt() ==    2415975642 ||
// zmet.evt() ==     159610020 ||
// zmet.evt() ==     301121450 ||
// zmet.evt() ==     589600919 ||
// zmet.evt() ==    1266947113 ||
// zmet.evt() ==     189726737 ||
// zmet.evt() ==     830633171 ||
// zmet.evt() ==     836245354 ||
// zmet.evt() ==     942213070 ||
// zmet.evt() ==     967421935 ||
// zmet.evt() ==     994642770 ||
// zmet.evt() ==     914150792 ||
// zmet.evt() ==    1417411358 ||
// zmet.evt() ==    2118930519 ||
// zmet.evt() ==    1754407940 ||
// zmet.evt() ==    1766097937 ||
// zmet.evt() ==    1205899387 ||
// zmet.evt() ==    2313284112 ||
// zmet.evt() ==    1342618685 ||
// zmet.evt() ==    1985748206 ||
// zmet.evt() ==    2218529337 ||
// zmet.evt() ==      27280019 ||
// zmet.evt() ==      28371886 ||
// zmet.evt() ==     182518464 ||
// zmet.evt() ==      65661747 ||
// zmet.evt() ==     155669188 ||
// zmet.evt() ==     724428975 ||
// zmet.evt() ==     208639446 ||
// zmet.evt() ==     280314724 ||
// zmet.evt() ==     384337236 ||
// zmet.evt() ==     645341182 ||
// zmet.evt() ==     985488725 ||
// zmet.evt() ==     281180983 ||
// zmet.evt() ==     858977169 ||
// zmet.evt() ==     127011299 ||
// zmet.evt() ==     911326541 ||
// zmet.evt() ==    1249631602 ||
// zmet.evt() ==     261153617 ||
// zmet.evt() ==     598093576 ||
// zmet.evt() ==     600123618 ||
// zmet.evt() ==     604164884 ||
// zmet.evt() ==    1167654814 ||
// zmet.evt() ==       9981193 ||
// zmet.evt() ==     114820969 ||
// zmet.evt() ==     358096488 ||
// zmet.evt() ==     583524488 ||
// zmet.evt() ==     853536937 ||
// zmet.evt() ==     312859729 ||
// zmet.evt() ==     751643916 ||
// zmet.evt() ==     315731957 ||
// zmet.evt() ==     513910881 ||
// zmet.evt() ==     356618947 ||
// zmet.evt() ==     468603738 ||
// zmet.evt() ==     538092181 ||
// zmet.evt() ==     669151891 ||
// zmet.evt() ==     674185343 ||
// zmet.evt() ==     800787062 ||
// zmet.evt() ==     876242903 ||
// zmet.evt() ==     255298419 ||
// zmet.evt() ==     388089847 ||
// zmet.evt() ==     734404359 ||
// zmet.evt() ==     849936472 ||
// zmet.evt() ==     951978139 ||
// zmet.evt() ==     984338476 ||
// zmet.evt() ==     126212970 ||
// zmet.evt() ==     674037960 ||
// zmet.evt() ==     645127812 ||
// zmet.evt() ==     214100002 ||
// zmet.evt() ==     233083508 ||
// zmet.evt() ==     601723661 ||
// zmet.evt() ==     447300195 ||
// zmet.evt() ==     650959562 ||
// zmet.evt() ==     292850898 ||
// zmet.evt() ==     889794871 ||
// zmet.evt() ==     964275402 ||
// zmet.evt() ==     901466952 ||
// zmet.evt() ==     760577538 ||
// zmet.evt() ==     652232550 ||
// zmet.evt() ==    1301979178 ||
// zmet.evt() ==    1590112800 ||
// zmet.evt() ==     283397410 ||
// zmet.evt() ==     821467814 ||
// zmet.evt() ==     530684314 ||
// zmet.evt() ==    1120098112 ||
// zmet.evt() ==    1123589011 

// 		 ){
// 		cout<<zmet.evt()<<" | "<<event_met_pt<<" | "<<zmet.dphi_metj1()<<" | "<<zmet.mt2()<<" | "<< passMETFilters() <<endl;
// 		// cout<<zmet.hyp_type()<<" | "<<zmet.HLT_MuEG()<<" | "<<zmet.HLT_MuEG_2()<<" | "<<zmet.HLT_MuEG_noiso()<<" | "<< endl<<endl;
// 		if(!( (zmet.HLT_DoubleMu_nonDZ() || zmet.HLT_DoubleMu_tk_nonDZ() || zmet.HLT_DoubleMu_noiso() ) && zmet.hyp_type() == 1 )){
// 		  cout<<zmet.hyp_type()<<" | "<<zmet.HLT_DoubleMu_nonDZ()<<" | "<<zmet.HLT_DoubleMu_tk_nonDZ()<<" | "<<zmet.HLT_DoubleMu_noiso()<<" | "<< endl;
// 		  cout<<zmet.hyp_type()<<" | "<<zmet.HLT_DoubleEl_DZ()<<" | "<<zmet.HLT_DoubleEl_noiso()<<" | "<< endl;
// 		  cout<<zmet.hyp_type()<<" | "<<zmet.HLT_MuEG()<<" | "<<zmet.HLT_MuEG_2()<<" | "<<zmet.HLT_MuEG_noiso()<<" | "<< endl<<endl;
// 		}

// 		if ( !(( zmet.HLT_DoubleEl_DZ()    || zmet.HLT_DoubleEl_noiso()                                 ) && zmet.hyp_type() == 0 )){
// 		  cout<<zmet.hyp_type()<<" | "<<zmet.HLT_DoubleMu_nonDZ()<<" | "<<zmet.HLT_DoubleMu_tk_nonDZ()<<" | "<<zmet.HLT_DoubleMu_noiso()<<" | "<< endl;
// 		  cout<<zmet.hyp_type()<<" | "<<zmet.HLT_DoubleEl_DZ()<<" | "<<zmet.HLT_DoubleEl_noiso()<<" | "<< endl;
// 		  cout<<zmet.hyp_type()<<" | "<<zmet.HLT_MuEG()<<" | "<<zmet.HLT_MuEG_2()<<" | "<<zmet.HLT_MuEG_noiso()<<" | "<< endl<<endl;
// 		}

// 		if (!( ( zmet.HLT_MuEG()           || zmet.HLT_MuEG_noiso()                                     ) && zmet.hyp_type() == 2 )){
// 		  cout<<zmet.hyp_type()<<" | "<<zmet.HLT_DoubleMu_nonDZ()<<" | "<<zmet.HLT_DoubleMu_tk_nonDZ()<<" | "<<zmet.HLT_DoubleMu_noiso()<<" | "<< endl;
// 		  cout<<zmet.hyp_type()<<" | "<<zmet.HLT_DoubleEl_DZ()<<" | "<<zmet.HLT_DoubleEl_noiso()<<" | "<< endl;
// 		  cout<<zmet.hyp_type()<<" | "<<zmet.HLT_MuEG()<<" | "<<zmet.HLT_MuEG_2()<<" | "<<zmet.HLT_MuEG_noiso()<<" | "<< endl<<endl;
// 		}

// 		if(!(( (zmet.HLT_DoubleMu_nonDZ() || zmet.HLT_DoubleMu_tk_nonDZ() || zmet.HLT_DoubleMu_noiso() ) && zmet.hyp_type() == 1 ) ||
// 			 ( (zmet.HLT_DoubleEl_DZ()    || zmet.HLT_DoubleEl_noiso()                                 ) && zmet.hyp_type() == 0 ) ||
// 			 ( ( zmet.HLT_MuEG()          || zmet.HLT_MuEG_noiso()                                     ) && zmet.hyp_type() == 2 ) ) ){
// 		  badevents++;
// 		}

// 	  }

	  
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
	  if( zmet.dRll() < 0.1 ) continue;
	  // if( zmet.dilpt() < 22 ) continue;

	  // // for closure only
	  if( !passSignalRegionSelection(selection) ) continue;
	  if( !passMETFilters() ) continue;

	  // if (zmet.isData() && metFilterTxt.eventFails(zmet.run(), zmet.lumi(), zmet.evt())) {
	  // 	//cout<<"Found bad event in data: "<<t.run<<", "<<t.lumi<<", "<<t.evt<<endl;
	  // 	continue;
      // }	  
	  if( TString(selection).Contains("withtightb") && zmet.nBJetTight() < 1 ) continue;
	  
	  //~-~-~-~-~-~-~-~-//
      // event selection// 
	  //~-~-~-~-~-~-~-~-//
	  if( !(zmet.hyp_type() == 0 ||          
	  		zmet.hyp_type() == 1 ||          
	  		zmet.hyp_type() == 2 )                       ) continue; // require explicit dilepton event
	  if( !(zmet.evt_type() == 0 )                       ) continue; // require opposite sig

	  float lepton_SF = 1.0;
	  // float weightbefore = weight;
	  // float weightafter = weight;
	  
	  // deal with other event weights
	  if( !zmet.isData() && doscalefactors ){

		// btag sf variation
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

		if( doisrboost ){
		  if(      zmet.isrboost() > 400. && zmet.isrboost() < 600. ) weight *= 0.85;
		  else if( zmet.isrboost() > 600.                           ) weight *= 0.70;
		  weight *= 1./h_isrweights->GetBinContent(h_isrweights->FindBin( zmet.mass_gluino(), zmet.mass_LSP() ));
		}

		float min_leppt1  = min( 75.0, (double)zmet.lep_pt().at(0));
		float min_leppt2  = min( 75.0, (double)zmet.lep_pt().at(1));
		float abs_lepeta1 = abs(zmet.lep_eta().at(0));
		float abs_lepeta2 = abs(zmet.lep_eta().at(1));

		// trigger scale factors for SF
		if( zmet.hyp_type() == 0 ) weight *= 0.939;
		if( zmet.hyp_type() == 1 ) weight *= 0.929;
		
		// fullsim to data scale factors
		if( doleptonid ){
		  if( abs(zmet.lep_pdgId().at(0)) == 11 ) lepton_SF *= h_eleweights_id->GetBinContent(h_eleweights_id->FindBin( min_leppt1, abs_lepeta1 ));
		  if( abs(zmet.lep_pdgId().at(1)) == 11 ) lepton_SF *= h_eleweights_id->GetBinContent(h_eleweights_id->FindBin( min_leppt2, abs_lepeta2 ));
		  if( abs(zmet.lep_pdgId().at(0)) == 13 ) lepton_SF *= h_muoweights_id->GetBinContent(h_muoweights_id->FindBin( min_leppt1, abs_lepeta1 ));
		  if( abs(zmet.lep_pdgId().at(1)) == 13 ) lepton_SF *= h_muoweights_id->GetBinContent(h_muoweights_id->FindBin( min_leppt2, abs_lepeta2 ));
		}
		
		if( doleptoniso ){
		  if( abs(zmet.lep_pdgId().at(0)) == 11 ) lepton_SF *= h_eleweightsiso->GetBinContent(h_eleweightsiso->FindBin( min_leppt1, abs_lepeta1 ));
		  if( abs(zmet.lep_pdgId().at(1)) == 11 ) lepton_SF *= h_eleweightsiso->GetBinContent(h_eleweightsiso->FindBin( min_leppt2, abs_lepeta2 ));
		  if( abs(zmet.lep_pdgId().at(0)) == 13 ) lepton_SF *= h_muoweightsiso->GetBinContent(h_muoweightsiso->FindBin( min_leppt1, abs_lepeta1 ));
		  if( abs(zmet.lep_pdgId().at(1)) == 13 ) lepton_SF *= h_muoweightsiso->GetBinContent(h_muoweightsiso->FindBin( min_leppt2, abs_lepeta2 ));
		}
  
		if( dofastsim && TString(currentFile->GetTitle()).Contains("t5zz") ){
		  if( abs(zmet.lep_pdgId().at(0)) == 11 ) lepton_SF *= h_eleweights->GetBinContent(h_eleweights->FindBin( min_leppt1, abs_lepeta1 ));
		  if( abs(zmet.lep_pdgId().at(1)) == 11 ) lepton_SF *= h_eleweights->GetBinContent(h_eleweights->FindBin( min_leppt2, abs_lepeta2 ));
		  if( abs(zmet.lep_pdgId().at(0)) == 13 ) lepton_SF *= h_muoweights->GetBinContent(h_muoweights->FindBin( min_leppt1, abs_lepeta1 ));
		  if( abs(zmet.lep_pdgId().at(1)) == 13 ) lepton_SF *= h_muoweights->GetBinContent(h_muoweights->FindBin( min_leppt2, abs_lepeta2 ));
		}
		
		weight *= lepton_SF;
		
		// if( abs(zmet.lep_pdgId().at(0)) == 11 ) weight *= h_eleweights->GetBinContent(h_eleweights->FindBin( zmet.lep_pt().at(0), zmet.lep_eta().at(0), zmet.nVert() ));
		// if( abs(zmet.lep_pdgId().at(1)) == 11 ) weight *= h_eleweights->GetBinContent(h_eleweights->FindBin( zmet.lep_pt().at(1), zmet.lep_eta().at(1), zmet.nVert() ));

		// if( abs(zmet.lep_pdgId().at(0)) == 13 ) weight *= h_muoweights->GetBinContent(h_muoweights->FindBin( zmet.lep_pt().at(0), zmet.lep_eta().at(0), zmet.nVert() ));
		// if( abs(zmet.lep_pdgId().at(1)) == 13 ) weight *= h_muoweights->GetBinContent(h_muoweights->FindBin( zmet.lep_pt().at(1), zmet.lep_eta().at(1), zmet.nVert() ));

		if( zmet.mass_gluino() == 1400 && zmet.mass_LSP() == 400 ) weight*=2;
		
		// weightafter = weight;
 
	  }

	  //flat trigger effs
	  if( !zmet.isData() ){
		if( zmet.hyp_type() == 0 ) weight *= 0.970;
		if( zmet.hyp_type() == 1 ) weight *= 0.920;
		if( zmet.hyp_type() == 2 ) weight *= 0.886;
	  }
	  
      if( !usejson && zmet.isData() && !zmet.evt_passgoodrunlist()   ) continue;
	  fillHist( "event", "mll"  , "inclusive", zmet.dilmass()  , weight );

	  if( (zmet.dilmass() > 81 && zmet.dilmass() < 101) ){ // HT > 100
		fillHist( "event", "nVert", "inclusive", zmet.nVert()  , weight );	  
	  }

	  if( TString(selection).Contains("CR") && zmet.evt_type() != 2 ){
		if( !((( zmet.HLT_DoubleMu()    || zmet.HLT_DoubleMu_tk()   || zmet.HLT_DoubleMu_noiso() )) ||
			  (( zmet.HLT_DoubleEl_DZ() || zmet.HLT_DoubleEl_noiso()                             )) ||
			  (( zmet.HLT_MuEG()        || zmet.HLT_MuEG_noiso()                                 ))
			  )           ) continue;
	  }else{

		if( !TString(currentFile->GetTitle()).Contains("t5zz") && zmet.isData() ){

		  if( !((( zmet.HLT_DoubleMu_nonDZ() || zmet.HLT_DoubleMu_tk_nonDZ() || zmet.HLT_DoubleMu_noiso() ) && zmet.hyp_type() == 1 ) ||
				(( zmet.HLT_DoubleEl_DZ()    || zmet.HLT_DoubleEl_noiso()                                 ) && zmet.hyp_type() == 0 ) ||
				(( zmet.HLT_MuEG()           || zmet.HLT_MuEG_2()            || zmet.HLT_MuEG_noiso()     ) && zmet.hyp_type() == 2 )
				)           ) continue;
		
		}
	  }
	  
	  fillHist( "event", "mll"    , "passtrig" , zmet.dilmass()  , weight );
	  if( zmet.njets() > 1 ){
		if( zmet.hyp_type() == 2 ) nem_2jets += weight;	  
		fillHist( "event", "metgt1jet" , "inclusive", event_met_pt        , weight );
	  }
	 
	  // // for CRs
	  // if( zmet.evt_type() != 2 ){
	  // // if( TString(selection).Contains("CR") && zmet.evt_type() != 2 ){
	  // 	// cout<<zmet.jet_p4().size()<<" | "<<zmet.jets_p4().size()<<endl;
	  // 	int njets_cr = 0;
	  // 	for( int jetind = 0; jetind < zmet.jet_p4().size(); jetind++ ){
	  // 	  bool foundmatch = false;
	  // 	  if( zmet.jet_p4().at(jetind).pt() < 35   ) continue;
	  // 	  if( zmet.jet_p4().at(jetind).eta() > 2.4 ) continue;
	  // 	  for( int lepind = 0; lepind < zmet.lep_p4().size(); lepind++ ){
	  // 		if(  sqrt( pow(zmet.jet_p4().at(jetind).eta() - zmet.lep_p4().at(lepind).eta(), 2) + pow(acos(cos(zmet.jet_p4().at(jetind).phi() - zmet.lep_p4().at(lepind).phi())), 2) ) < 0.4 ){ 
	  // 		  foundmatch = true;
	  // 		}
	  // 	  }
	  // 	  if( !foundmatch ) njets_cr++;
	  // 	}
	  // 	fillUnderOverFlow(event_hists.at( "h_ll_event_njtall_passtrig" ), njets_cr, weight );
	  // 	if( event_met_pt > 50 ) fillUnderOverFlow(event_hists.at( "h_ll_event_njtm50_passtrig" ), njets_cr, weight );
	  // 	fillUnderOverFlow(event_hists.at( "h_ll_event_metall_passtrig" ), event_met_pt, weight );
	  // 	if( njets_cr != zmet.njets() ) continue;
	  // }

	  if( (event_met_pt > 100) ){
		fillHist( "event", "mll_fkw", "passtrig", zmet.dilmass()   , weight );	  
	  }

	  if( (!(TString(selection).Contains("CR") )&& zmet.evt_type() != 2) ){
		if( !(zmet.dilmass() > 81 && zmet.dilmass() < 101) ) continue; // HT > 100
	  }

	  if( zmet.njets() > 1 ){
		if( zmet.hyp_type() == 2 ) nem_2jets_mll += weight;	  
	  }

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

	  
	  // int bjetind = 0;
	  // int genbjetind = 0;
	  // for( int jetind = 0; jetind < zmet.njets(); jetind++ ){
	  // 	if( zmet.jets_csv().at(jetind) > 0.89 ){
	  // 	  if( bjetind+1 > 4 ) continue;
	  // 	  fillHist( "event", Form("ptb%i", bjetind+1)   , "passtrig", zmet.jets_p4().at(jetind).pt() , weight );
	  // 	  bjetind++;
	  // 	}
	  // 	if( zmet.jets_csv().at(jetind) > 0.89 && !zmet.isData() && abs(zmet.jets_mcFlavour().at(jetind)) == 5 ){
	  // 	  fillHist( "event", Form("pt_matchedbjet%i", genbjetind+1) , "passtrig", zmet.jets_p4().at(jetind).pt() , weight );
	  // 	  genbjetind++;
	  // 	}
	  // }
	  
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
	  if( TString(currentFile->GetTitle()).Contains("t5zz") && sample == "fullscan" ){
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


void templateLooper::bookHistos(){

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

  variable.push_back("chpfcands_0013_pt");        variable_bins.push_back(500 );  
  variable.push_back("chpfcands_1316_pt");        variable_bins.push_back(500 );  
  variable.push_back("chpfcands_1624_pt");        variable_bins.push_back(500 );  
  variable.push_back("chpfcands_2430_pt");        variable_bins.push_back(500 );  
  variable.push_back("chpfcands_30in_pt");        variable_bins.push_back(500 );  
  variable.push_back("phpfcands_0013_pt");        variable_bins.push_back(500 );  
  variable.push_back("phpfcands_1316_pt");        variable_bins.push_back(500 );  
  variable.push_back("phpfcands_1624_pt");        variable_bins.push_back(500 );  
  variable.push_back("phpfcands_2430_pt");        variable_bins.push_back(500 );  
  variable.push_back("phpfcands_30in_pt");        variable_bins.push_back(500 );  
  variable.push_back("nupfcands_0013_pt");        variable_bins.push_back(500 );  
  variable.push_back("nupfcands_1316_pt");        variable_bins.push_back(500 );  
  variable.push_back("nupfcands_1624_pt");        variable_bins.push_back(500 );  
  variable.push_back("nupfcands_2430_pt");        variable_bins.push_back(500 );  
  variable.push_back("nupfcands_30in_pt");        variable_bins.push_back(500 );  

  variable.push_back("chpfcands_0013_sumet");        variable_bins.push_back(2000 );  
  variable.push_back("chpfcands_1316_sumet");        variable_bins.push_back(2000 );  
  variable.push_back("chpfcands_1624_sumet");        variable_bins.push_back(2000 );  
  variable.push_back("chpfcands_2430_sumet");        variable_bins.push_back(2000 );  
  variable.push_back("chpfcands_30in_sumet");        variable_bins.push_back(2000 );  
  variable.push_back("phpfcands_0013_sumet");        variable_bins.push_back(2000 );  
  variable.push_back("phpfcands_1316_sumet");        variable_bins.push_back(2000 );  
  variable.push_back("phpfcands_1624_sumet");        variable_bins.push_back(2000 );  
  variable.push_back("phpfcands_2430_sumet");        variable_bins.push_back(2000 );  
  variable.push_back("phpfcands_30in_sumet");        variable_bins.push_back(2000 );  
  variable.push_back("nupfcands_0013_sumet");        variable_bins.push_back(2000 );  
  variable.push_back("nupfcands_1316_sumet");        variable_bins.push_back(2000 );  
  variable.push_back("nupfcands_1624_sumet");        variable_bins.push_back(2000 );  
  variable.push_back("nupfcands_2430_sumet");        variable_bins.push_back(2000 );  
  variable.push_back("nupfcands_30in_sumet");        variable_bins.push_back(2000 );  

  
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

  h_signalyields_met100to150_ee = new TH2F("h_signalyields_met100to150_ee","h_signalyields_met100to150_ee",(1600-550)/50,575,1625,(1500-50)/50,75,1525);	
  h_signalyields_met100to150_mm = new TH2F("h_signalyields_met100to150_mm","h_signalyields_met100to150_mm",(1600-550)/50,575,1625,(1500-50)/50,75,1525);	
  h_signalyields_met100to150_ll = new TH2F("h_signalyields_met100to150_ll","h_signalyields_met100to150_ll",(1600-550)/50,575,1625,(1500-50)/50,75,1525);	
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

