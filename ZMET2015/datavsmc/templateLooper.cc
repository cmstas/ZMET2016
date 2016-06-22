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

const bool usejson              = true;
const bool dovtxreweighting     = false;
const bool dotemplateprediction = false;
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
  if( dotemplateprediction ){
	// mettemplates.loadTemplatesFromFile( Form("../output/%s/data%s_novtxweight_ptweight_templates.root", iter.c_str(), selection.c_str()), mettemplate_hists );
	mettemplates.loadTemplatesFromFile( Form("../output/%s/data%s_novtxweight_templates.root", iter.c_str(), selection.c_str()), mettemplate_hists );
	mettemplates.setBins( selection );
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
  const char* json_file = "../../json/DCSONLY_json_160516_snt.txt"; // 2016 data
  
  set_goodrun_file(json_file);

  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");

  TH1F * h_vtxweight = NULL;
  TFile * f_vtx = NULL;
  if( dovtxreweighting ){
	f_vtx = TFile::Open("nvtx_ratio.root","READ");
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
		  if( zmet.genPart_motherId().at(genind) == 23 &&
			  zmet.genPart_status().at(genind) == 23 &&
			  (abs(zmet.genPart_pdgId().at(genind))==11 ||
			   abs(zmet.genPart_pdgId().at(genind))==13) ){
		  }
		  realzpair = true;
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
		  weight *= h_vtxweight->GetBinContent(h_vtxweight->FindBin(zmet.nVert()));		
		  // weight *= h_vtxweight->GetBinContent(h_vtxweight->FindBin(zmet.nTrueInt()));		
		// }
	  }

	  if( sample == "zjets" ){
		if( TString(currentFile->GetTitle()).Contains("m50") ) weight *= 14987122./2550912.;
	  }
	  
	  float event_met_pt = zmet.met_pt();
	  float event_met_ph = zmet.met_phi();

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
	  
	  //~-~-~-~-~-~-~-~-//
      // event selection// 
	  //~-~-~-~-~-~-~-~-//
	  if( zmet.nlep()                        < 2         ) continue; // require at least 2 good leptons
	  if( zmet.lep_pt().at(0)                < 20        ) continue; // leading lep pT > 25 GeV
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

	  // cout<<"weight before: "<<weightbefore<<endl;
	  // cout<<"btag sf      : "<<zmet.weight_btagsf()<<endl;
	  // cout<<"lepton SF    : "<<lepton_SF<<endl;
	  // cout<<"weight after:  "<<weightafter<<endl;
	  
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
				(( zmet.HLT_MuEG()           || zmet.HLT_MuEG_noiso()                                     ) && zmet.hyp_type() == 2 )
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
	  fillHist( "event", "nVert"  , "passtrig", zmet.nVert()        , weight );	  
	  fillHist( "event", "ptdil"  , "passtrig", zmet.dilpt()        , weight );	  
	  fillHist( "event", "metphi" , "passtrig", event_met_ph        , weight );	  
	  fillHist( "event", "metphir", "passtrig", zmet.met_rawPhi()   , weight );	  

	  if( zmet.njets() > 0 ) fillHist( "event", "ptj1"   , "passtrig", zmet.jets_p4().at(0).pt() , weight );	  
	  if( zmet.njets() > 1 ) fillHist( "event", "ptj2"   , "passtrig", zmet.jets_p4().at(1).pt() , weight );	  
	  if( zmet.njets() > 2 ) fillHist( "event", "ptj3"   , "passtrig", zmet.jets_p4().at(2).pt() , weight );	  
	  if( zmet.njets() > 3 ) fillHist( "event", "ptj4"   , "passtrig", zmet.jets_p4().at(3).pt() , weight );	  

	  if( zmet.njets() > 0 ) fillHist( "event", "csv1"   , "passtrig", zmet.jets_csv().at(0) , weight );	  
	  if( zmet.njets() > 1 ) fillHist( "event", "csv2"   , "passtrig", zmet.jets_csv().at(1) , weight );	  
	  if( zmet.njets() > 2 ) fillHist( "event", "csv3"   , "passtrig", zmet.jets_csv().at(2) , weight );	  
	  if( zmet.njets() > 3 ) fillHist( "event", "csv4"   , "passtrig", zmet.jets_csv().at(3) , weight );	  

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


	  fillHist( "event", "chpfcands_0013_pt" , "passtrig", zmet.chpfcands_0013_pt()  , weight );	  
	  fillHist( "event", "chpfcands_1316_pt" , "passtrig", zmet.chpfcands_1316_pt()  , weight );	  
	  fillHist( "event", "chpfcands_1624_pt" , "passtrig", zmet.chpfcands_1624_pt()  , weight );	  
	  fillHist( "event", "chpfcands_2430_pt" , "passtrig", zmet.chpfcands_2430_pt()  , weight );	  
	  fillHist( "event", "chpfcands_30in_pt" , "passtrig", zmet.chpfcands_30in_pt()  , weight );	  
	  fillHist( "event", "phpfcands_0013_pt" , "passtrig", zmet.phpfcands_0013_pt()  , weight );	  
	  fillHist( "event", "phpfcands_1316_pt" , "passtrig", zmet.phpfcands_1316_pt()  , weight );	  
	  fillHist( "event", "phpfcands_1624_pt" , "passtrig", zmet.phpfcands_1624_pt()  , weight );	  
	  fillHist( "event", "phpfcands_2430_pt" , "passtrig", zmet.phpfcands_2430_pt()  , weight );	  
	  fillHist( "event", "phpfcands_30in_pt" , "passtrig", zmet.phpfcands_30in_pt()  , weight );	  
	  fillHist( "event", "nupfcands_0013_pt" , "passtrig", zmet.nupfcands_0013_pt()  , weight );	  
	  fillHist( "event", "nupfcands_1316_pt" , "passtrig", zmet.nupfcands_1316_pt()  , weight );	  
	  fillHist( "event", "nupfcands_1624_pt" , "passtrig", zmet.nupfcands_1624_pt()  , weight );	  
	  fillHist( "event", "nupfcands_2430_pt" , "passtrig", zmet.nupfcands_2430_pt()  , weight );	  
	  fillHist( "event", "nupfcands_30in_pt" , "passtrig", zmet.nupfcands_30in_pt()  , weight );	  
	  fillHist( "event", "chpfcands_0013_sumet" , "passtrig", zmet.chpfcands_0013_sumet()  , weight );	  
	  fillHist( "event", "chpfcands_1316_sumet" , "passtrig", zmet.chpfcands_1316_sumet()  , weight );	  
	  fillHist( "event", "chpfcands_1624_sumet" , "passtrig", zmet.chpfcands_1624_sumet()  , weight );	  
	  fillHist( "event", "chpfcands_2430_sumet" , "passtrig", zmet.chpfcands_2430_sumet()  , weight );	  
	  fillHist( "event", "chpfcands_30in_sumet" , "passtrig", zmet.chpfcands_30in_sumet()  , weight );	  
	  fillHist( "event", "phpfcands_0013_sumet" , "passtrig", zmet.phpfcands_0013_sumet()  , weight );	  
	  fillHist( "event", "phpfcands_1316_sumet" , "passtrig", zmet.phpfcands_1316_sumet()  , weight );	  
	  fillHist( "event", "phpfcands_1624_sumet" , "passtrig", zmet.phpfcands_1624_sumet()  , weight );	  
	  fillHist( "event", "phpfcands_2430_sumet" , "passtrig", zmet.phpfcands_2430_sumet()  , weight );	  
	  fillHist( "event", "phpfcands_30in_sumet" , "passtrig", zmet.phpfcands_30in_sumet()  , weight );	  
	  fillHist( "event", "nupfcands_0013_sumet" , "passtrig", zmet.nupfcands_0013_sumet()  , weight );	  
	  fillHist( "event", "nupfcands_1316_sumet" , "passtrig", zmet.nupfcands_1316_sumet()  , weight );	  
	  fillHist( "event", "nupfcands_1624_sumet" , "passtrig", zmet.nupfcands_1624_sumet()  , weight );	  
	  fillHist( "event", "nupfcands_2430_sumet" , "passtrig", zmet.nupfcands_2430_sumet()  , weight );	  
	  fillHist( "event", "nupfcands_30in_sumet" , "passtrig", zmet.nupfcands_30in_sumet()  , weight );	  

	  
	  int bjetind = 0;
	  int genbjetind = 0;
	  for( int jetind = 0; jetind < zmet.njets(); jetind++ ){
		if( zmet.jets_csv().at(jetind) > 0.89 ){
		  if( bjetind+1 > 4 ) continue;
		  fillHist( "event", Form("ptb%i", bjetind+1)   , "passtrig", zmet.jets_p4().at(jetind).pt() , weight );
		  bjetind++;
		}
		if( zmet.jets_csv().at(jetind) > 0.89 && !zmet.isData() && abs(zmet.jets_mcFlavour().at(jetind)) == 5 ){
		  fillHist( "event", Form("pt_matchedbjet%i", genbjetind+1) , "passtrig", zmet.jets_p4().at(jetind).pt() , weight );
		  genbjetind++;
		}
	  }
	  
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
  mettemplates.correctBinUncertainty( mettemplate_hists, event_hists.at("h_templ_met") );

  
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

