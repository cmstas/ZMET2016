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
#include "TMath.h"

#include "Math/VectorUtil.h"

#include "makePhotonTemplates.h"

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
const bool usejson = false;
bool dovtxreweighting = false;
bool dovtxreweightingformc = false;

makePhotonTemplates::makePhotonTemplates()
{
  dohtreweighting = false;
  doptreweighting = false;
};

makePhotonTemplates::makePhotonTemplates( bool htreweighting, bool ptreweighting )
{
  dohtreweighting = htreweighting;
  doptreweighting = ptreweighting;
};

makePhotonTemplates::~makePhotonTemplates()
{
};

void makePhotonTemplates::ScanChain ( TChain * chain , const string iter , const string sample, const string selection ){

  // if( zmet.isData() )        cout << "Running on Data."        << endl;
  // else                       cout << "Running on MC.  "        << endl;

  float n_numelecs   = 0;
  float n_numall     = 0;

  float n_allphotons   = 0;
  float n_loosephotons = 0;
  float n_tightphotons = 0;
  
  float e_allphotons   = 0;
  float e_loosephotons = 0;
  float e_tightphotons = 0;
  
  float allmet_nobreq   = 0;
  float allmet_hasrealb = 0;
  float endmet_nobreq   = 0;
  float endmet_hasrealb = 0;

  float allmet_btag_nobreq   = 0;
  float allmet_btag_hasrealb = 0;
  float endmet_btag_nobreq   = 0;
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
  
  double npass = 0;
  METTemplates mettemplates( selection );
  mettemplates.setBins( selection );
  mettemplates.bookMETHists(mettemplate_hists);  
  bookHistos();

  eventFilter metFilterTxt;
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

  // do this once per job
  // const char* json_file = "../../json/json_golden_168pb_290915_sntformat.txt"; // 116 pb
  // const char* json_file = "../../json/json_225pb_091015_sntformat.txt"; // 225 pb with bad data

  // const char* json_file = "/home/users/cwelke/analysis2015/CMSSW_7_4_7_patch2_dilepbabymaker/V07-04-10_datadriven/CORE/Tools/json_600pb_131015_sntformat.txt"; // updated, need more cms3

  // const char* json_file = "/home/users/cwelke/analysis2015/CMSSW_7_4_7_patch2_dilepbabymaker/V07-04-10/json/json_150pb_141015_sntformat.txt";

  // const char* json_file = "/home/users/olivito/mt2_74x_dev/MT2Analysis/babymaker/jsons/Cert_246908-258750_13TeV_PromptReco_Collisions15_25ns_JSON_snt.txt"; // 1.3 fb
  // const char* json_file = "../../json/Cert_271036-274240_13TeV_PromptReco_Collisions16_JSON_snt.txt"; // 0.8 fb-1 for FSR
  // const char* json_file = "../../json/golden_json_080716_snt.txt"; // 6.26 fb, for preapproval
  // const char* json_file = "../../json/golden_json_080716_7p65fb_snt.txt"; // 7.65 fb, for preapproval
  const char* json_file = "../../json/golden_json_200716_12p9fb_snt.txt"; // 12.9 fb

  set_goodrun_file(json_file);

  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");

  TH1F * h_vtxweight_22  = NULL;
  TH1F * h_vtxweight_30  = NULL;
  TH1F * h_vtxweight_36  = NULL;
  TH1F * h_vtxweight_50  = NULL;
  TH1F * h_vtxweight_75  = NULL;
  TH1F * h_vtxweight_90  = NULL;
  TH1F * h_vtxweight_120 = NULL;
  TH1F * h_vtxweight_165 = NULL;
  TFile * f_vtx = NULL;
  if( dovtxreweighting ){
	f_vtx = TFile::Open("../vtxreweighting/nvtx_ratio_data.root","READ");
	h_vtxweight_22  = (TH1F*)f_vtx->Get("h_vtx_ratio_22") ->Clone( "h_vtxweight_22" );
	h_vtxweight_30  = (TH1F*)f_vtx->Get("h_vtx_ratio_30") ->Clone( "h_vtxweight_30" );
	h_vtxweight_36  = (TH1F*)f_vtx->Get("h_vtx_ratio_36") ->Clone( "h_vtxweight_36" );
	h_vtxweight_50  = (TH1F*)f_vtx->Get("h_vtx_ratio_50") ->Clone( "h_vtxweight_50" );
	h_vtxweight_75  = (TH1F*)f_vtx->Get("h_vtx_ratio_75") ->Clone( "h_vtxweight_75" );
	h_vtxweight_90  = (TH1F*)f_vtx->Get("h_vtx_ratio_90") ->Clone( "h_vtxweight_90" );
	h_vtxweight_120 = (TH1F*)f_vtx->Get("h_vtx_ratio_120")->Clone( "h_vtxweight_120");
	h_vtxweight_165 = (TH1F*)f_vtx->Get("h_vtx_ratio_165")->Clone( "h_vtxweight_165");
	h_vtxweight_22 ->SetDirectory(rootdir);
	h_vtxweight_30 ->SetDirectory(rootdir);
	h_vtxweight_36 ->SetDirectory(rootdir);
	h_vtxweight_50 ->SetDirectory(rootdir);
	h_vtxweight_75 ->SetDirectory(rootdir);
	h_vtxweight_90 ->SetDirectory(rootdir);
	h_vtxweight_120->SetDirectory(rootdir);
	h_vtxweight_165->SetDirectory(rootdir);
	f_vtx->Close();
  }

	TH1F * h_vtxweight = NULL;
  if( dovtxreweightingformc ){
	f_vtx = TFile::Open("nvtx_ratio.root","READ");
	h_vtxweight = (TH1F*)f_vtx->Get("h_vtx_ratio")->Clone("h_vtxweight");
	h_vtxweight->SetDirectory(rootdir);
	f_vtx->Close();
  }

  // TH1F * h_htweight_22  = NULL;
  // TH1F * h_htweight_30  = NULL;
  // TH1F * h_htweight_36  = NULL;
  // TH1F * h_htweight_50  = NULL;
  // TH1F * h_htweight_75  = NULL;
  // TH1F * h_htweight_90  = NULL;
  // TH1F * h_htweight_120 = NULL;
  // TH1F * h_htweight_165 = NULL;
  // TFile * f_ht = NULL;
  // if( dohtreweighting ){
  // 	f_ht = TFile::Open(Form("../vtxreweighting/ht_ratio_data_novtx_nohtweight%s.root", selection.c_str()),"READ");
  // 	h_htweight_22  = (TH1F*)f_ht->Get("h_ht_ratio_22") ->Clone( "h_htweight_22" );
  // 	h_htweight_30  = (TH1F*)f_ht->Get("h_ht_ratio_30") ->Clone( "h_htweight_30" );
  // 	h_htweight_36  = (TH1F*)f_ht->Get("h_ht_ratio_36") ->Clone( "h_htweight_36" );
  // 	h_htweight_50  = (TH1F*)f_ht->Get("h_ht_ratio_50") ->Clone( "h_htweight_50" );
  // 	h_htweight_75  = (TH1F*)f_ht->Get("h_ht_ratio_75") ->Clone( "h_htweight_75" );
  // 	h_htweight_90  = (TH1F*)f_ht->Get("h_ht_ratio_90") ->Clone( "h_htweight_90" );
  // 	h_htweight_120 = (TH1F*)f_ht->Get("h_ht_ratio_120")->Clone( "h_htweight_120");
  // 	h_htweight_165 = (TH1F*)f_ht->Get("h_ht_ratio_165")->Clone( "h_htweight_165");
  // 	h_htweight_22 ->SetDirectory(rootdir);
  // 	h_htweight_30 ->SetDirectory(rootdir);
  // 	h_htweight_36 ->SetDirectory(rootdir);
  // 	h_htweight_50 ->SetDirectory(rootdir);
  // 	h_htweight_75 ->SetDirectory(rootdir);
  // 	h_htweight_90 ->SetDirectory(rootdir);
  // 	h_htweight_120->SetDirectory(rootdir);
  // 	h_htweight_165->SetDirectory(rootdir);
  // 	f_ht->Close();
  // }

  TH1F * h_htweight = NULL;
  TFile * f_ht = NULL;
  if( dohtreweighting ){
	if ( TString(sample).Contains("withMC") ) {
	  f_ht = TFile::Open(Form("../vtxreweighting/ht_ratio_data_novtx_nohtweight_ewkcontam%s.root", selection.c_str()),"READ");
	}else{
	  f_ht = TFile::Open(Form("../vtxreweighting/ht_ratio_data_novtx_nohtweight%s.root", selection.c_str()),"READ");
	}
  
  	h_htweight = (TH1F*)f_ht->Get("h_ht_ratio")->Clone("h_htweight");
  	h_htweight->SetDirectory(rootdir);
  	f_ht->Close();
  }

  TH1F * h_ptweight = NULL;
  TFile * f_pt = NULL;
  if( doptreweighting ){
  	f_pt = TFile::Open(Form("../vtxreweighting/pt_ratio_data_novtx_nohtweight%s.root", selection.c_str()),"READ");
  	h_ptweight = (TH1F*)f_pt->Get("h_pt_ratio")->Clone("h_ptweight");
  	h_ptweight->SetDirectory(rootdir);
  	f_pt->Close();
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
	  
	  if (nEventsTotal % 100000 == 0){ // progress feedback to user
	  	if (isatty(1)){ // xterm magic from L. Vacavant and A. Cerri               
          printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
                 "\033[0m\033[32m <---\033[0m\015", (float)nEventsTotal/(nEventsChain*0.01));
          fflush(stdout);
        }
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
	  
	  //-~-~-~-~-~-~-~-~-~-~-~-//
	  //Deal with event weights//
	  //-~-~-~-~-~-~-~-~-~-~-~-//
	  float weight = 1.0;
	  if( zmet.isData() ){
		weight = 1.0;
	  }else if( !zmet.isData() ){
		weight *= zmet.evt_scale1fb();
		if ( TString(sample).Contains("withMC") ) {
		  weight *= -12.9;
		}
	  	if( TString(currentFile->GetTitle()).Contains("wjets_incl_amcnlo") && zmet.gen_ht() > 100 ) continue;
	  }

	  // define "global" event variables
	  float event_met_pt = zmet.met_T1CHS_miniAOD_CORE_pt();
	  float event_met_ph = zmet.met_T1CHS_miniAOD_CORE_phi();

	  if( zmet.isData() ){
		event_met_pt = zmet.met_T1CHS_miniAOD_CORE_pt();
		event_met_ph = zmet.met_T1CHS_miniAOD_CORE_phi();
	  }
	  
	  float evt_ht    = zmet.ht();

	  float evt_njets = zmet.njets();
	  
	  // if (zmet.isData() && metFilterTxt.eventFails(zmet.run(), zmet.lumi(), zmet.evt())) {
	  // 	//cout<<"Found bad event in data: "<<t.run<<", "<<t.lumi<<", "<<t.evt<<endl;
	  // 	continue;
      // }	  

	  if( evt_njets < 2 ) continue;	  

	  //~-~-~-~-~-~-~-~-//
      // event selection// 
	  //~-~-~-~-~-~-~-~-//
	  if( !eventHasGoodPhoton()                                    ) continue; // event selection
      if( !usejson && zmet.isData() && !zmet.evt_passgoodrunlist() ) continue; // use json applied at babymaking
      if( zmet.isData() && zmet.nVert() == 0                       ) continue; // special selection for now
	  if( zmet.isData() && getPrescaleNoBins_nol1ps() <= 0         ) continue; // pass trigger for data
	  if( zmet.nlep()>0                                            ) continue; // lepton veto
	  if( !passSignalRegionSelection(selection)                    ) continue;
	  if( !passMETFilters()                                        ) continue;
	  
	  // better lep veto
	  if( zmet.nisoTrack_5gev()           > 0    ) continue;
	  
	  // //trig emulator cuts
	  // if( !zmet.isData() ){
	  if( zmet.gamma_r9()            .at(0) < 0.92 ) continue;
	  if( zmet.gamma_hOverE()        .at(0) > 0.2  ) continue;
	  if( zmet.gamma_hollowtkiso03() .at(0) > 5    ) continue;
	  if( abs(zmet.gamma_eta().at(0)) < 1.4 && zmet.gamma_ecpfclusiso()   .at(0) > 4 + zmet.gamma_pt().at(0) * 0.0053  ) continue;
	  if( abs(zmet.gamma_eta().at(0)) < 1.4 && zmet.gamma_hcpfclusiso()   .at(0) > 8 + zmet.gamma_pt().at(0) * 0.014   ) continue;
	  if( abs(zmet.gamma_eta().at(0)) > 1.6 && zmet.gamma_ecpfclusiso()   .at(0) > 4 + zmet.gamma_pt().at(0) * 0.0034  ) continue;
	  if( abs(zmet.gamma_eta().at(0)) > 1.6 && zmet.gamma_hcpfclusiso()   .at(0) > 8 + zmet.gamma_pt().at(0) * 0.0139  ) continue;
	  // }

	  // if( zmet.HLT_CaloJet500_NoJetID() > 0 && zmet.gamma_pt().at(0) > 180 &&
	  // 	(zmet.HLT_Photon165_R9Id90_HE10_IsoM() < 1 || zmet.HLT_Photon165_HE10() < 1 )
	  // 	){
	  //   cout<<zmet.HLT_CaloJet500_NoJetID()<<" | ";
	  //   cout<<zmet.HLT_Photon165_R9Id90_HE10_IsoM()<<" | ";
	  //   cout<<zmet.HLT_Photon165_HE10()<<" | ";
	  //   cout<<zmet.gamma_pt().at(0)<<" | ";
	  //   cout<<endl;
	  // }


	  
	  if( zmet.isData() ){  
		// weight *= (float) getPrescale();
		// weight *= (float) getPrescaleNoBins();
		weight *= (float) getPrescaleNoBins_nol1ps();
	  }
	  
	  n_allphotons += weight;
	  e_allphotons += weight*weight;
	  if( isLoosePhoton(0) ){ n_loosephotons += weight; e_loosephotons += weight*weight;}
	  if( isTightPhoton(0) ){ n_tightphotons += weight;	e_tightphotons += weight*weight;}

	  if( dovtxreweighting ){
	    if(      zmet.gamma_pt().at(0) > 165 ) weight *= h_vtxweight_165 ->GetBinContent(h_vtxweight_165 ->FindBin(zmet.nVert()));
	  	else if( zmet.gamma_pt().at(0) > 120 ) weight *= h_vtxweight_120 ->GetBinContent(h_vtxweight_120 ->FindBin(zmet.nVert()));
	  	else if( zmet.gamma_pt().at(0) > 90  ) weight *= h_vtxweight_90  ->GetBinContent(h_vtxweight_90  ->FindBin(zmet.nVert()));
	  	else if( zmet.gamma_pt().at(0) > 75  ) weight *= h_vtxweight_75  ->GetBinContent(h_vtxweight_75  ->FindBin(zmet.nVert()));
	  	else if( zmet.gamma_pt().at(0) > 50  ) weight *= h_vtxweight_50  ->GetBinContent(h_vtxweight_50  ->FindBin(zmet.nVert()));
	  	else if( zmet.gamma_pt().at(0) > 36  ) weight *= h_vtxweight_36  ->GetBinContent(h_vtxweight_36  ->FindBin(zmet.nVert()));
	  	else if( zmet.gamma_pt().at(0) > 33  ) weight *= h_vtxweight_30  ->GetBinContent(h_vtxweight_30  ->FindBin(zmet.nVert()));
	  	else if( zmet.gamma_pt().at(0) > 22  ) weight *= h_vtxweight_22  ->GetBinContent(h_vtxweight_22  ->FindBin(zmet.nVert()));
	  }

	  // if( TString(currentFile->GetTitle()).Contains("gjetsht40_") ){weight *= 2.6  ;}
	  // if( TString(currentFile->GetTitle()).Contains("gjetsht100") ){weight *= 4.21 ;}
	  // if( TString(currentFile->GetTitle()).Contains("gjetsht200") ){weight *= 16.55;}
	  // if( TString(currentFile->GetTitle()).Contains("gjetsht400") ){weight *= 5.61 ;}
	  // if( TString(currentFile->GetTitle()).Contains("gjetsht600") ){weight *= 6.9  ;}

	  // if( TString(currentFile->GetTitle()).Contains("gjetsht40_") ){weight *= 0.296;}
	  // if( TString(currentFile->GetTitle()).Contains("gjetsht100") ){weight *= 0.476;}
	  // if( TString(currentFile->GetTitle()).Contains("gjetsht200") ){weight *= 2.14 ;}
	  // if( TString(currentFile->GetTitle()).Contains("gjetsht400") ){weight *= 0.836;}
	  // if( TString(currentFile->GetTitle()).Contains("gjetsht600") ){weight *= 1.0  ;}

	  // if( TString(currentFile->GetTitle()).Contains("gjetsht40_") ){weight *= 0.280;}
	  // if( TString(currentFile->GetTitle()).Contains("gjetsht100") ){weight *= 0.476;}
	  // if( TString(currentFile->GetTitle()).Contains("gjetsht200") ){weight *= 2.022;}
	  // if( TString(currentFile->GetTitle()).Contains("gjetsht400") ){weight *= 0.834;}
	  // if( TString(currentFile->GetTitle()).Contains("gjetsht600") ){weight *= 1.0  ;}
		
	  // if( TString(selection).Contains("SR_ATLAS") ){
	  // 	fillHist( "event", "htgt1jets", "passtrig", zmet.gamma_pt().at(0) + zmet.ht() , weight ); // this is for HT reweighting
	  // }else{
	  // 	fillHist( "event", "htgt1jets", "passtrig", zmet.gamma_pt().at(0)             , weight ); // this is for HT reweighting
	  // }

	  fillHist( "event", "htgt1jets", "passtrig", zmet.gamma_pt().at(0)             , weight ); // this is for HT reweighting

	  
	  if( dohtreweighting ){
		float minpt = min(2999.0,(double)zmet.gamma_pt().at(0));
	  	weight *= h_htweight->GetBinContent(h_htweight->FindBin(minpt));		
	  }
	  fillHist( "event", "ht_highbin", "passtrig", zmet.ht()            , weight );

	  if( doptreweighting ){
		float minht = min(2999.0,(double)evt_ht);
	  	weight *= h_ptweight->GetBinContent(h_ptweight->FindBin( minht ));		
	  }

	  if( !zmet.isData() && dovtxreweightingformc ){
		weight *= h_vtxweight->GetBinContent(h_vtxweight->FindBin(zmet.nVert()));		
	  }

	  
	  // if( TString(selection).Contains("tail") ){
	  if( true ){

		float btagcount = zmet.nBJetMedium();
		if( TString(selection).Contains("withtightb") ) btagcount = zmet.nBJetTight();

		if( !zmet.isData() && btagcount > 0 ) {
		  bool hasrealb = false;
		  for( int jetind = 0; jetind < zmet.njets(); jetind++ ){
			if( abs(zmet.jets_mcFlavour().at(jetind)) == 5 ) hasrealb = true;
			if( hasrealb ) break;
		  }		

			allmet_nobreq += weight;
			unc_allmet_nobreq += weight*weight;
		
		  if( hasrealb ){
			allmet_hasrealb += weight;
			unc_allmet_hasrealb += weight*weight;
		  }

		  if( event_met_pt > 100 ){
			  endmet_nobreq     += weight;
			  unc_endmet_nobreq += weight*weight;		
		
			if( hasrealb ) endmet_hasrealb     += weight;		
			if( hasrealb ) unc_endmet_hasrealb += weight*weight;		
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
		  if( btagcount == 0 ) endmet_btag_nobreq       += weight;
		  if( btagcount == 0 ) unc_endmet_btag_nobreq   += weight*weight;		
		  if( btagcount > 0  ) endmet_btag_hasrealb     += weight;		
		  if( btagcount > 0  ) unc_endmet_btag_hasrealb += weight*weight;		
		}		

	  }	 
	  
	  //-~-~-~-~-~-~-~-~-//
	  //Fill event  hists//
	  //-~-~-~-~-~-~-~-~-//	  
	  fillHist( "event", "njets"  , "passtrig", evt_njets            , weight );
	  fillHist( "event", "met"    , "passtrig", event_met_pt         , weight );
	  fillHist( "event", "met_raw", "passtrig", zmet.met_rawPt()     , weight );
	  fillHist( "event", "ht"     , "passtrig", evt_ht               , weight );
	  if( !zmet.isData() ) fillHist( "event", "gen_ht" , "passtrig", zmet.gen_ht()               , weight );
	  fillHist( "event", "ptg"    , "passtrig", zmet.gamma_pt().at(0), weight );	  
	  fillHist( "event", "nVert"  , "passtrig", zmet.nVert()         , weight );	  
	  fillHist( "event", "metphi" , "passtrig", event_met_ph         , weight );	  
	  fillHist( "event", "metphir", "passtrig", zmet.met_rawPhi()    , weight );	  
	  if( evt_njets > 0 ) 	   fillHist( "event", "htgt0jets" , "passtrig", evt_ht               , weight );
	  if( event_met_pt > 200 ) fillHist( "event", "ptg_met200", "passtrig", zmet.gamma_pt().at(0), weight );	  
	  if( evt_njets == 0 )     fillHist( "event", "met0jet"   , "passtrig", event_met_pt         , weight );
	  if( evt_njets == 1 )     fillHist( "event", "met1jet"   , "passtrig", event_met_pt         , weight );
	  if( evt_njets >= 2 )     fillHist( "event", "metgt1jet" , "passtrig", event_met_pt         , weight );

	  if( event_met_pt > 100 ){
		n_numall   += weight;

		bool haselec = false;
		for( size_t genind = 0; genind < zmet.genPart_motherId().size(); genind++ ){
		  if(  (abs(zmet.genPart_pdgId().at(genind))==11 && abs(zmet.genPart_motherId().at(genind))==24 ) ){
			// cout<<"mom "<<zmet.genPart_motherId().at(genind) << " | stat "<< zmet.genPart_status().at(genind) <<  " | id "<< zmet.genPart_pdgId().at(genind) << endl;
			haselec = true;
		  }
		}
		if( haselec ) n_numelecs += weight;
	  }
		
	  // if( dohtreweighting ){
	  // 	float evt_pt = zmet.gamma_pt().at(0);
	  //   if(      ( zmet.gamma_pt().at(0) > 165 ) weight *= h_htweight_165 ->GetBinContent(h_htweight_165 ->FindBin(evt_pt));
	  // 	else if( ( zmet.gamma_pt().at(0) > 120 ) weight *= h_htweight_120 ->GetBinContent(h_htweight_120 ->FindBin(evt_pt));
	  // 	else if( ( zmet.gamma_pt().at(0) > 90  ) weight *= h_htweight_90  ->GetBinContent(h_htweight_90  ->FindBin(evt_pt));
	  // 	else if( ( zmet.gamma_pt().at(0) > 75  ) weight *= h_htweight_75  ->GetBinContent(h_htweight_75  ->FindBin(evt_pt));
	  // 	else if( ( zmet.gamma_pt().at(0) > 50  ) weight *= h_htweight_50  ->GetBinContent(h_htweight_50  ->FindBin(evt_pt));
	  // 	else if( ( zmet.gamma_pt().at(0) > 36  ) weight *= h_htweight_36  ->GetBinContent(h_htweight_36  ->FindBin(evt_pt));
	  // 	else if( ( zmet.gamma_pt().at(0) > 33  ) weight *= h_htweight_30  ->GetBinContent(h_htweight_30  ->FindBin(evt_pt));
	  // 	else if( ( zmet.gamma_pt().at(0) > 22  ) weight *= h_htweight_22  ->GetBinContent(h_htweight_22  ->FindBin(evt_pt));
	  // if(      ( !zmet.isData() && zmet.gamma_pt().at(0) > 170 ) || passPhotonTrigger165() ) weight *= h_htweight_165 ->GetBinContent(h_htweight_165 ->FindBin(evt_ht));
	  // else if( ( !zmet.isData() && zmet.gamma_pt().at(0) > 125 ) || passPhotonTrigger120() ) weight *= h_htweight_120 ->GetBinContent(h_htweight_120 ->FindBin(evt_ht));
	  // else if( ( !zmet.isData() && zmet.gamma_pt().at(0) > 100 ) || passPhotonTrigger90()  ) weight *= h_htweight_90  ->GetBinContent(h_htweight_90  ->FindBin(evt_ht));
	  // else if( ( !zmet.isData() && zmet.gamma_pt().at(0) > 80  ) || passPhotonTrigger75()  ) weight *= h_htweight_75  ->GetBinContent(h_htweight_75  ->FindBin(evt_ht));
	  // else if( ( !zmet.isData() && zmet.gamma_pt().at(0) > 60  ) || passPhotonTrigger50()  ) weight *= h_htweight_50  ->GetBinContent(h_htweight_50  ->FindBin(evt_ht));
	  // else if( ( !zmet.isData() && zmet.gamma_pt().at(0) > 40  ) || passPhotonTrigger36()  ) weight *= h_htweight_36  ->GetBinContent(h_htweight_36  ->FindBin(evt_ht));
	  // else if( ( !zmet.isData() && zmet.gamma_pt().at(0) > 35  ) || passPhotonTrigger30()  ) weight *= h_htweight_30  ->GetBinContent(h_htweight_30  ->FindBin(evt_ht));
	  // else if( ( !zmet.isData() && zmet.gamma_pt().at(0) > 25  ) || passPhotonTrigger22()  ) weight *= h_htweight_22  ->GetBinContent(h_htweight_22  ->FindBin(evt_ht));
	  // }

	  // // synch for Bobak
	  // if( event_met_pt > 150 ){
	  // 	cout << setw(10)<<zmet.run()<<" | ";
	  // 	cout << setw(10)<<zmet.lumi()<<" | ";
	  // 	cout << setw(10)<<zmet.evt()<<" | ";
	  // 	cout << setw(5)<<zmet.njets()<<" | ";
	  // 	cout << setw(5)<<zmet.ngamma()<<" | ";
	  // 	cout << setw(5)<<zmet.evt_type()<<" | ";
	  // 	cout << setw(10)<<zmet.gamma_pt().at(0)<<" | ";
	  // 	cout << setw(10)<<zmet.gamma_eta().at(0)<<" | ";
	  // 	cout << setw(10)<<zmet.jets_p4().at(0).pt()<<" | ";
	  // 	cout << setw(10)<<zmet.jets_p4().at(1).pt()<<" | ";
	  // 	cout << setw(10)<<zmet.jets_p4().at(0).eta()<<" | ";
	  // 	cout << setw(10)<<zmet.jets_p4().at(1).eta()<<" | ";
	  // 	cout << setw(10)<<zmet.ht()<<" | ";
	  // 	cout << setw(10)<<zmet.met_T1CHS_miniAOD_CORE_pt()<<" | ";
	  // 	cout << setw(10)<<passMETFilters()<<" | ";
	  // 	cout<<endl;
	  // }

	  
	  //-~-~-~-~-~-~-~-~-~-//
	  //Fill Template hists//
	  //-~-~-~-~-~-~-~-~-~-//	  
      npass += weight;
	  mettemplates.FillTemplate(mettemplate_hists, evt_njets, evt_ht, zmet.gamma_pt().at(0), event_met_pt, weight );

    } // end loop over events
  } // end loop over files



  cout << npass       << " events passing selection" << endl;
  cout << nDuplicates << " duplicate events in data" << endl;
  // cout << "em events at low MET : "     << nem_2jets*10 << endl;

  float unc_endmet_nobreq_binomial   = err_binomial( endmet_nobreq  , allmet_nobreq  , sqrt(unc_endmet_nobreq  ), sqrt(unc_allmet_nobreq  ));
  float unc_endmet_hasrealb_binomial = err_binomial( endmet_hasrealb, allmet_hasrealb, sqrt(unc_endmet_hasrealb), sqrt(unc_allmet_hasrealb));

  cout<<"fraction in tail with no b-req: "<< 100*endmet_nobreq  /allmet_nobreq   << " | " << 100*unc_endmet_nobreq_binomial   <<endl;	
  cout<<"fraction in tail with 1 real b: "<< 100*endmet_hasrealb/allmet_hasrealb << " | " << 100*unc_endmet_hasrealb_binomial <<endl;

  float unc_endmet_btag_nobreq_binomial   = err_binomial( endmet_btag_nobreq  , allmet_btag_nobreq  , sqrt(unc_endmet_btag_nobreq  ), sqrt(unc_allmet_btag_nobreq  ));
  float unc_endmet_btag_hasrealb_binomial = err_binomial( endmet_btag_hasrealb, allmet_btag_hasrealb, sqrt(unc_endmet_btag_hasrealb), sqrt(unc_allmet_btag_hasrealb));

  cout<<endl<<"fraction in tail with no b-tags: "<< 100*endmet_btag_nobreq  /allmet_btag_nobreq    << " | " << 100*unc_endmet_btag_nobreq_binomial   <<endl;	
  cout<<      "fraction in tail with b-tags   : "<< 100*endmet_btag_hasrealb/allmet_btag_hasrealb  << " | " << 100*unc_endmet_btag_hasrealb_binomial <<endl;

  cout<<endl<<"all MET b-veto : "<< allmet_btag_nobreq    << " | " << sqrt(unc_allmet_btag_nobreq  )   <<endl;	
  cout<<endl<<"MET>100 b-veto : "<< endmet_btag_nobreq    << " | " << sqrt(unc_endmet_btag_nobreq  )   <<endl;	

  cout<<endl<<"all MET w b-tag: "<< allmet_btag_hasrealb    << " | " << sqrt(unc_allmet_btag_hasrealb  )   <<endl;	
  cout<<endl<<"MET>100 w b-tag: "<< endmet_btag_hasrealb    << " | " << sqrt(unc_endmet_btag_hasrealb  )   <<endl;	

  float unc_loose_all = err_binomial( n_loosephotons, n_allphotons, sqrt(e_loosephotons), sqrt(e_allphotons));
  float unc_tight_loose = err_binomial( n_tightphotons, n_loosephotons, sqrt(e_tightphotons), sqrt(e_loosephotons));

  cout<<"nall  : "<<n_allphotons<<endl;
  cout<<"nloose: "<<n_loosephotons<<endl;
  cout<<"ntight: "<<n_tightphotons<<endl;
  cout<<"loose/all  : "<<(float)n_loosephotons/(float)n_allphotons<<" +\- "<<unc_loose_all<<endl;
  cout<<"tight/loose: "<<(float)n_tightphotons/(float)n_loosephotons<<" +\- "<<unc_tight_loose<<endl;

  cout<<"Numevts that pass        : "<<n_numall<<endl;
  cout<<"Numevts with gen electron: "<<n_numelecs<<endl;
  
  mettemplates.NormalizeTemplates(mettemplate_hists);

  
  if (nEventsChain != nEventsTotal)
    std::cout << "ERROR: number of events from files is not equal to total number of events" << std::endl;

  string str_vtxweight = "";
  
  if( !dovtxreweighting ) str_vtxweight+= "_novtxweight";
  if( !dohtreweighting ) str_vtxweight+= "_nohtweight";
  if( doptreweighting ) str_vtxweight+= "_ptweight";

  // make histos rootfile
  string outputfilename = 	Form("../output/%s/%s%s%s_templates.root",
								 iter.c_str(),
								 sample.c_str(),
								 selection.c_str(),
								 str_vtxweight.c_str()
								 );

  cout << "Writing output to " << outputfilename << endl;
  saveHist(outputfilename.c_str(),"*");
  
  // deleteHistos();
  
} // end ScanChain


void makePhotonTemplates::bookHistos(){

  // hist naming convention: "h_<leptype>_<object>_<variable>_<selection>"
  vector <string> leptype;
  // leptype.push_back("ee");
  // leptype.push_back("mm");
  // leptype.push_back("em");
  // leptype.push_back("ll");
  leptype.push_back("ph");
  vector <string> object;
  object.push_back("event");
  // object.push_back("templ");
  // object.push_back("lep1");
  // object.push_back("lep2");
  // object.push_back("dilep");
  vector <string> selection;
  selection.push_back("inclusive");
  selection.push_back("passtrig");
  selection.push_back("passtrig165");
  selection.push_back("passtrig120");
  selection.push_back("passtrig90");
  selection.push_back("passtrig75");
  selection.push_back("passtrig50");
  selection.push_back("passtrig36");
  selection.push_back("passtrig30");
  selection.push_back("passtrig22");

  vector <string> variable;      vector <float> variable_bins;

  variable.push_back("ptg");       variable_bins.push_back(1000);  
  variable.push_back("met");       variable_bins.push_back(500 );  
  variable.push_back("metphi");    variable_bins.push_back(500 );  
  variable.push_back("metphir");   variable_bins.push_back(500 );  
  variable.push_back("met_raw");   variable_bins.push_back(500 );  
  variable.push_back("ht");	       variable_bins.push_back(1000);  
  variable.push_back("gen_ht");    variable_bins.push_back(1000);  
  variable.push_back("ht_highbin");variable_bins.push_back(1500);  
  variable.push_back("htgt0jets"); variable_bins.push_back(1000);  
  variable.push_back("htgt1jets"); variable_bins.push_back(3000);  
  variable.push_back("njets");     variable_bins.push_back(20  );  
  variable.push_back("nVert");     variable_bins.push_back(50 );  
  variable.push_back("met0jet");   variable_bins.push_back(500 );  
  variable.push_back("met1jet");   variable_bins.push_back(500 );  
  variable.push_back("metgt1jet"); variable_bins.push_back(500 );  

  variable.push_back("ptg_met200");       variable_bins.push_back(1000);  

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
  // need to add hists for calculating FS BG


}

void makePhotonTemplates::bookHist( string name, string title, int nbins, float xmin, float xmax ){
  // cout<<"Booking hist: "<<name<<endl;
  TH1F * hist = new TH1F( name.c_str(), title.c_str(), nbins, xmin, xmax );
  hist->Sumw2();
  event_hists.insert ( pair<std::string,TH1F*>( name, hist ) );		
  return;
}  


void makePhotonTemplates::fillHist( string obj, string var, string sel, float value, float weight ){
  // cout<<"Booking hist: "<<name<<endl;
  // TH1F * hist = new TH1F( name, title, nbins, xmin, xmax );
  string hist = "h_";
  try
	{
	  if( zmet.evt_type() == 2 ){
		hist = Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), sel.c_str());
		fillUnderOverFlow(event_hists.at( hist ), value, weight);		
		// if( passPhotonTrigger165() ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig165") ), value, weight);
		// if( passPhotonTrigger120() ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig120") ), value, weight);
		// if( passPhotonTrigger90()  ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig90" ) ), value, weight);
		// if( passPhotonTrigger75()  ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig75" ) ), value, weight);
		// if( passPhotonTrigger50()  ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig50" ) ), value, weight);
		// if( passPhotonTrigger36()  ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig36" ) ), value, weight);
		// if( passPhotonTrigger30()  ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig30" ) ), value, weight);
		// if( passPhotonTrigger22()  ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig22" ) ), value, weight);

		// if(      zmet.gamma_pt().at(0) > 165 ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig165") ), value, weight);
		// else if( zmet.gamma_pt().at(0) > 120 ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig120") ), value, weight);
		// else if( zmet.gamma_pt().at(0) > 90  ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig90" ) ), value, weight);
		// else if( zmet.gamma_pt().at(0) > 75  ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig75" ) ), value, weight);
		// else if( zmet.gamma_pt().at(0) > 50  ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig50" ) ), value, weight);
		// else if( zmet.gamma_pt().at(0) > 36  ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig36" ) ), value, weight);
		// else if( zmet.gamma_pt().at(0) > 33  ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig30" ) ), value, weight);
		// else if( zmet.gamma_pt().at(0) > 22  ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig22" ) ), value, weight);

		if( zmet.HLT_Photon165_R9Id90_HE10_IsoM() > 0 ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig165") ), value, weight);
		if( zmet.HLT_Photon120_R9Id90_HE10_IsoM() > 0 ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig120") ), value, weight);
		if( zmet.HLT_Photon90_R9Id90_HE10_IsoM()  > 0 ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig90" ) ), value, weight);
		if( zmet.HLT_Photon75_R9Id90_HE10_IsoM()  > 0 ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig75" ) ), value, weight);
		if( zmet.HLT_Photon50_R9Id90_HE10_IsoM()  > 0 ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig50" ) ), value, weight);
		if( zmet.HLT_Photon36_R9Id90_HE10_IsoM()  > 0 ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig36" ) ), value, weight);
		if( zmet.HLT_Photon30_R9Id90_HE10_IsoM()  > 0 && zmet.gamma_pt().at(0) > 33 ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig30" ) ), value, weight);
		else if( zmet.HLT_Photon22_R9Id90_HE10_IsoM()  > 0 && zmet.gamma_pt().at(0) < 33 ) fillUnderOverFlow(event_hists.at( Form("h_ph_%s_%s_%s", obj.c_str(), var.c_str(), "passtrig22" ) ), value, weight);

	  }else if( zmet.evt_type() == 0 ){		  
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
	}
  catch(exception &e)
	{
	  cout<<"Hist: "<<hist<<" Does not exist!"<<endl;
	  exit(1);
	}
 
  return;
}  

