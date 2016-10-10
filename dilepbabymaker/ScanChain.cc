// C++
#include <iostream>
#include <vector>
#include <set>

// ROOT
#include "TChain.h"
#include "TDirectory.h"
#include "TTreeCache.h"
#include "Math/VectorUtil.h"
#include "TVector2.h"
#include "TBenchmark.h"
#include "TLorentzVector.h"
#include "TH2.h"

// CORE
#include "../CORE/CMS3.h"
#include "../CORE/Base.h"
#include "../CORE/OSSelections.h"
#include "../CORE/ElectronSelections.h"
#include "../CORE/IsolationTools.h"
#include "../CORE/JetSelections.h"
#include "../CORE/MuonSelections.h"
#include "../CORE/IsoTrackVeto.h"
#include "../CORE/PhotonSelections.h"
#include "../CORE/TriggerSelections.h"
#include "../CORE/VertexSelections.h"
#include "../CORE/MCSelections.h"
#include "../CORE/MetSelections.h"
#include "../CORE/SimPa.h"
#include "../CORE/Tools/jetcorr/FactorizedJetCorrector.h"
#include "../CORE/Tools/JetCorrector.h"
#include "../CORE/Tools/jetcorr/JetCorrectionUncertainty.h"
#include "../CORE/Tools/MT2/MT2.h"
#include "../CORE/Tools/hemJet.h"
#include "../CORE/Tools/utils.h"
#include "../CORE/Tools/goodrun.h"
#include "../CORE/Tools/btagsf/BTagCalibrationStandalone.h"

// header
#include "ScanChain.h"

using namespace std;
using namespace tas;

// turn on to add debugging statements
const bool verbose = false;
// turn on to apply JEC from text files
const bool applyJECfromFile = true;
//turn on to veto transition region for leps and photons
const bool vetoXitionRegion = false;
//turn on to veto eta > 2.4 for leps and photons
const bool maxEta24 = true;
// is set during runtime
bool isSMSScan = false;
// always on
bool applyBtagSFs = true;

//--------------------------------------------------------------------

// This is meant to be passed as the third argument, the predicate, of the standard library sort algorithm
inline bool sortByPt(const LorentzVector &vec1, const LorentzVector &vec2 ) {
  return vec1.pt() > vec2.pt();
}

// This is meant to be passed as the third argument, the predicate, of the standard library sort algorithm
inline bool sortByValue(const std::pair<int,float>& pair1, const std::pair<int,float>& pair2 ) {
  return pair1.second > pair2.second;
}

int returnBrokenTrigger( string trigname )
{
  if( passHLTTriggerPattern(   trigname.c_str() ) ){
	return
	  passHLTTriggerPattern(   trigname.c_str() ) >
	  HLT_prescale(triggerName(trigname.c_str() )) ?
	  passHLTTriggerPattern(   trigname.c_str() ) :
	  HLT_prescale(triggerName(trigname.c_str() ));
  }
  return false;
}

 //--------------------------------------------------------------------

void babyMaker::ScanChain(TChain* chain, std::string baby_name){

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  cout<<"Creating MVA input for electrons."<<endl;
  createAndInitMVA("MVAinput", true); // for electrons

  MakeBabyNtuple( Form("%s.root", baby_name.c_str()) );

  load_leptonSF_files();
	
  // do this once per job
  const char* json_file = "golden_json_260916_26p4fb_snt.txt"; // 26p4 fb
  cout<<"Setting grl: "<<json_file<<endl;
  set_goodrun_file(json_file);

  if( TString(baby_name).Contains("t5zz") || TString(baby_name).Contains("tchiwz") || TString(baby_name).Contains("signal") ) isSMSScan = true;
  
  if (applyBtagSFs) {
	// setup btag calibration readers
	calib           = new BTagCalibration("csvv2", "btagsf/CSVv2_ichep.csv"); // 25s version of SFs
	reader_heavy    = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "central"); // central
	reader_heavy_UP = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "up"     ); // sys up
	reader_heavy_DN = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "down"   ); // sys down
	reader_light    = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "incl", "central"); // central
	reader_light_UP = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "incl", "up"     ); // sys up
	reader_light_DN = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "incl", "down"   ); // sys down

	// get btag efficiencies
	TFile * f_btag_eff           = new TFile("btagsf/btageff__ttbar_powheg_pythia8_25ns.root");
	TH2D  * h_btag_eff_b_temp    = (TH2D*) f_btag_eff->Get("h2_BTaggingEff_csv_med_Eff_b");
	TH2D  * h_btag_eff_c_temp    = (TH2D*) f_btag_eff->Get("h2_BTaggingEff_csv_med_Eff_c");
	TH2D  * h_btag_eff_udsg_temp = (TH2D*) f_btag_eff->Get("h2_BTaggingEff_csv_med_Eff_udsg");
	BabyFile_->cd();
	h_btag_eff_b    = (TH2D*) h_btag_eff_b_temp    -> Clone("h_btag_eff_b"   );
	h_btag_eff_c    = (TH2D*) h_btag_eff_c_temp    -> Clone("h_btag_eff_c"   );
	h_btag_eff_udsg = (TH2D*) h_btag_eff_udsg_temp -> Clone("h_btag_eff_udsg");
	// f_btag_eff->Close();

	std::cout << "loaded fullsim btag SFs" << std::endl;
    
	// extra copy for fastsim -> fullsim SFs
	if (isSMSScan) {
	  // setup btag calibration readers
	  calib_fastsim     = new BTagCalibration("CSV", "btagsf/CSV_13TEV_Combined_14_7_2016.csv"); // 25ns fastsim version of SFs
	  reader_fastsim    = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "central"); // central
	  reader_fastsim_UP = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "up"     ); // sys up
	  reader_fastsim_DN = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "down"   ); // sys down

	  // get btag efficiencies
	  TFile * f_btag_eff_fastsim           = new TFile("btagsf/btageff__SMS-T1bbbb-T1qqqq_fastsim.root");
	  TH2D  * h_btag_eff_b_fastsim_temp    = (TH2D*) f_btag_eff_fastsim->Get("h2_BTaggingEff_csv_med_Eff_b"  );
	  TH2D  * h_btag_eff_c_fastsim_temp    = (TH2D*) f_btag_eff_fastsim->Get("h2_BTaggingEff_csv_med_Eff_c"  );
	  TH2D  * h_btag_eff_udsg_fastsim_temp = (TH2D*) f_btag_eff_fastsim->Get("h2_BTaggingEff_csv_med_Eff_udsg");
	  BabyFile_->cd();
	  h_btag_eff_b_fastsim    = (TH2D*) h_btag_eff_b_fastsim_temp    -> Clone("h_btag_eff_b_fastsim"   );
	  h_btag_eff_c_fastsim    = (TH2D*) h_btag_eff_c_fastsim_temp    -> Clone("h_btag_eff_c_fastsim"   );
	  h_btag_eff_udsg_fastsim = (TH2D*) h_btag_eff_udsg_fastsim_temp -> Clone("h_btag_eff_udsg_fastsim");
	  // f_btag_eff_fastsim->Close();
      
	  std::cout << "loaded fastsim btag SFs" << std::endl;
	} // if (isFastsim)
  }
  
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");

  //add 2015 data vtx weights for PU
  TH1F * h_vtxweight = NULL;
  TFile * f_vtx = NULL;
  f_vtx = TFile::Open("pileup_jul21_nominalUpDown.root","READ");
  h_vtxweight = (TH1F*)f_vtx->Get("weightsNominal")->Clone("h_vtxweight");
  h_vtxweight->SetDirectory(rootdir);
  f_vtx->Close();
  
  TH1F * h_susyxsecs  = NULL;
  TFile * f_susyxsecs = NULL;

  TH2F * h_eventcounts  = NULL;
  TFile * f_eventcounts = NULL;

  if (isSMSScan) {

	cout<<"issmsscan"<<endl;
	
	f_susyxsecs = TFile::Open("xsec_susy_13tev.root","READ");
	if( TString(baby_name).Contains("t5zz")   ) h_susyxsecs = (TH1F*)f_susyxsecs->Get("h_xsec_gluino")->Clone("h_susyxsecs");
	if( TString(baby_name).Contains("tchiwz") ) h_susyxsecs = (TH1F*)f_susyxsecs->Get("h_xsec_c1n2"  )->Clone("h_susyxsecs");
	h_susyxsecs->SetDirectory(rootdir);
	f_susyxsecs->Close();

	if( TString(baby_name).Contains("tchiwz") ) f_eventcounts = TFile::Open("TChiWZ_entries_V08-00-05_FS.root","READ");
	if( TString(baby_name).Contains("t5zz"  ) ) f_eventcounts = TFile::Open("T5ZZ_entries.root"               ,"READ");
	h_eventcounts = (TH2F*)f_eventcounts->Get("h_entries")->Clone("h_eventcounts");
	h_eventcounts->SetDirectory(rootdir);
	f_eventcounts->Close();
  }
  
  // File Loop
  int nDuplicates = 0;
  int nEvents = chain->GetEntries();
  unsigned int nEventsChain = nEvents;
  cout << "Running on " << nEventsChain << " events" << endl;
  unsigned int nEventsTotal = 0;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
  while ( (currentFile = (TFile*)fileIter.Next()) ) {
    cout << "running on file: " << currentFile->GetTitle() << endl;

    // evt_id = sampleID(currentFile->GetTitle());

    // Get File Content
    TFile f( currentFile->GetTitle() );
    TTree *tree = (TTree*)f.Get("Events");
    TTreeCache::SetLearnEntries(10);
    tree->SetCacheSize(128*1024*1024);
    cms3.Init(tree);

    // ----------------------------------
    // retrieve JEC from files, if using
    // ----------------------------------

    std::vector<std::string> jetcorr_filenames_pfL1FastJetL2L3;
    FactorizedJetCorrector *jet_corrector_pfL1FastJetL2L3;

	JetCorrectionUncertainty* jecUnc;
	
    if (applyJECfromFile) {
      jetcorr_filenames_pfL1FastJetL2L3.clear();

	  //JECs for 76X
	  if( TString(currentFile->GetTitle()).Contains("16Dec2015") || TString(currentFile->GetTitle()).Contains("76X_mcRun2") ){
		if( TString(currentFile->GetTitle()).Contains("Run2015C") || TString(currentFile->GetTitle()).Contains("Run2015D") ){
		  jetcorr_filenames_pfL1FastJetL2L3.clear();
		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_76X/DATA/Fall15_25nsV2_DATA_L1FastJet_AK4PFchs.txt"   );
		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_76X/DATA/Fall15_25nsV2_DATA_L2Relative_AK4PFchs.txt"  );
		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_76X/DATA/Fall15_25nsV2_DATA_L3Absolute_AK4PFchs.txt"  );
		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_76X/DATA/Fall15_25nsV2_DATA_L2L3Residual_AK4PFchs.txt");
		  jecUnc = new JetCorrectionUncertainty        ("jetCorrections/source_76X/DATA/Fall15_25nsV2_DATA_Uncertainty_AK4PFchs.txt" );
		}

		else{
		  // files for 76X MC
		  jetcorr_filenames_pfL1FastJetL2L3.clear();
		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_76X/MC/Fall15_25nsV2_MC_L1FastJet_AK4PFchs.txt"   );
		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_76X/MC/Fall15_25nsV2_MC_L2Relative_AK4PFchs.txt"  );
		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_76X/MC/Fall15_25nsV2_MC_L3Absolute_AK4PFchs.txt"  );
		  jecUnc = new JetCorrectionUncertainty        ("jetCorrections/source_76X/MC/Fall15_25nsV2_MC_Uncertainty_AK4PFchs.txt" );
		}		
	  }

	  else if( TString(currentFile->GetTitle()).Contains("80MiniAODv") || TString(currentFile->GetTitle()).Contains("RelVal") ){
		// files for 80X MC
		jetcorr_filenames_pfL1FastJetL2L3.clear();
		jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/MC/Spring16_25nsV1_MC_L1FastJet_AK4PFchs.txt"   );
		jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/MC/Spring16_25nsV1_MC_L2Relative_AK4PFchs.txt"  );
		jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/MC/Spring16_25nsV1_MC_L3Absolute_AK4PFchs.txt"  );
		jecUnc = new JetCorrectionUncertainty        ("jetCorrections/source_80X/MC/Spring16_25nsV1_MC_Uncertainty_AK4PFchs.txt" );
	  }
		
	  else if( TString(currentFile->GetTitle()).Contains("Run2016") || TString(currentFile->GetTitle()).Contains("CMSSW_8_0_11_V08-00-06") ){
		// files for 80X Data
		jetcorr_filenames_pfL1FastJetL2L3.clear();
		jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Spring16_25nsV6_DATA_L1FastJet_AK4PFchs.txt"   );
		jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Spring16_25nsV1_DATA_L2Relative_AK4PFchs.txt"  );
		jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Spring16_25nsV1_DATA_L3Absolute_AK4PFchs.txt"  );
		jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Spring16_25nsV6_DATA_L2L3Residual_AK4PFchs.txt");
		jecUnc = new JetCorrectionUncertainty        ("jetCorrections/source_80X/DATA/Spring16_25nsV6_DATA_Uncertainty_AK4PFchs.txt" );
	  }

	  if( isSMSScan ){
		// files for 25ns fastsim samples
		jetcorr_filenames_pfL1FastJetL2L3.clear();
		jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/FASTSIM/Spring16_FastSimV1_L1FastJet_AK4PFchs.txt"   );
		jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/FASTSIM/Spring16_FastSimV1_L2Relative_AK4PFchs.txt"  );
		jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/FASTSIM/Spring16_FastSimV1_L3Absolute_AK4PFchs.txt"  );
		jecUnc = new JetCorrectionUncertainty        ("jetCorrections/source_80X/FASTSIM/Spring16_FastSimV1_Uncertainty_AK4PFchs.txt" );
	  }

	  if( jetcorr_filenames_pfL1FastJetL2L3.size() == 0 ){
		cout<<"Error, sample not found. Check the JECs."<<endl;
		exit(100);
	  }
	  
	  jet_corrector_pfL1FastJetL2L3  = makeJetCorrector(jetcorr_filenames_pfL1FastJetL2L3);
    }

    // Event Loop
    unsigned int nEventsTree = tree->GetEntriesFast();
    for( unsigned int event = 0; event < nEventsTree; ++event) {
	  //for( unsigned int event = 0; event < 100; ++event) {

	  // if( event > 100 ) continue;
	  
      // Get Event Content
      tree->LoadTree(event);
      cms3.GetEntry(event);
      ++nEventsTotal;
    
      // Progress
      CMS3::progress( nEventsTotal, nEventsChain );

      InitBabyNtuple();

      run    = cms3.evt_run();
      lumi   = cms3.evt_lumiBlock();
      evt    = cms3.evt_event();
      isData = cms3.evt_isRealData();

      evt_kfactor  = cms3.evt_kfactor();
      evt_filter   = cms3.evt_filt_eff();

	  if( isSMSScan ){
		mass_gluino = cms3.sparm_values().at(0);
		mass_LSP    = cms3.sparm_values().at(1);

		evt_nEvts    = h_eventcounts->GetBinContent(h_eventcounts->FindBin(mass_gluino,mass_LSP));
		
		if( TString(currentFile->GetTitle()).Contains("SMS-T5ZZ") ) evt_xsec = h_susyxsecs->GetBinContent(h_susyxsecs->FindBin(mass_gluino))*(0.19175);// BF for at least 1 Z to two leps
		if( TString(currentFile->GetTitle()).Contains("SMS-TChi") ) evt_xsec = h_susyxsecs->GetBinContent(h_susyxsecs->FindBin(mass_gluino))*(0.100974);// BF for Z to two leps
		evt_scale1fb = evt_xsec*1000/evt_nEvts;

		LorentzVector isrSystem_p4;
		for( size_t genind = 0; genind < cms3.genps_p4().size(); genind++ ){
		  if( cms3.genps_isLastCopy().at(genind) == 1 && (abs(cms3.genps_id().at(genind)) == 1000024 || abs(cms3.genps_id().at(genind)) == 1000023 || cms3.genps_id().at(genind) == 1000021) ){
			isrSystem_p4 += cms3.genps_p4().at(genind);
		  }
		}

		isrboost = (isrSystem_p4).pt();
		
	  }
	  else{
		evt_nEvts    = cms3.evt_nEvts();
		evt_scale1fb = cms3.evt_scale1fb();
		evt_xsec     = cms3.evt_xsec_incl();
	  }
	  
	  puWeight     = 1.0;
	  if( !isData ){
	  	nTrueInt     = cms3.puInfo_trueNumInteractions().at(0);
		puWeight     = h_vtxweight->GetBinContent(h_vtxweight->FindBin(nTrueInt));
	  }
	  rho            = cms3.evt_fixgridfastjet_all_rho(); //this one is used in JECs

      if (verbose) cout << "before vertices" << endl;

      //VERTICES
      nVert = 0;
      for(unsigned int ivtx=0; ivtx < cms3.evt_nvtxs(); ivtx++){

        if(     cms3.vtxs_isFake()   .at(ivtx)             ) continue;
        if(     cms3.vtxs_ndof()     .at(ivtx)       <= 4  ) continue;
        if(fabs(cms3.vtxs_position() .at(ivtx).z())  >  24 ) continue;
        if(     cms3.vtxs_position() .at(ivtx).Rho() >  2  ) continue;
        nVert++;  
      }
      
      met_pt       = cms3.evt_pfmet();
      met_phi      = cms3.evt_pfmetPhi();
      met_calo_pt  = cms3.evt_calomet();
      met_calo_phi = cms3.evt_calometPhi();	  
	  met_genPt    = cms3.gen_met();
      met_genPhi   = cms3.gen_metPhi();
      met_rawPt    = cms3.evt_pfmet_raw();
      met_rawPhi   = cms3.evt_pfmetPhi_raw();
      sumet_raw    = cms3.evt_pfsumet_raw();

      // MET FILTERS
	  if( isData ){
		Flag_ecalLaserCorrFilter                = cms3.filt_ecalLaser();
		Flag_hcalLaserEventFilter               = cms3.filt_hcalLaser();
		Flag_trackingFailureFilter              = cms3.filt_trackingFailure();
		Flag_CSCTightHaloFilter                 = cms3.filt_cscBeamHalo();
		// recommended from twiki
		Flag_badMuonFilter                      = badMuonFilter();
	  }

	  // in data and MC
	  if( !isSMSScan ){
		Flag_HBHENoiseFilter                    = cms3.filt_hbheNoise();
		Flag_HBHEIsoNoiseFilter                 = cms3.filt_hbheNoiseIso();
		Flag_CSCTightHalo2015Filter             = cms3.filt_cscBeamHalo2015();
		Flag_EcalDeadCellTriggerPrimitiveFilter = cms3.filt_ecalTP();
		Flag_goodVertices                       = cms3.filt_goodVertices();
		Flag_eeBadScFilter                      = cms3.filt_eeBadSc();
		Flag_globalTightHalo2016                = cms3.filt_globalTightHalo2016();
		Flag_badChargedCandidateFilter          = badChargedCandidateFilter();
	  }
	  
      //TRIGGER
	  if( isData ){ // NO TRIGGERS IN MC FOR 80X
		// for ATLAS cross checks
		HLT_singleEl =  (passHLTTriggerPattern("HLT_Ele32_eta2p1_WPTight_Gsf_v" ) ||
						 passHLTTriggerPattern("HLT_Ele27_WPTight_Gsf_v"        ) );

		HLT_singleMu = (passHLTTriggerPattern("HLT_IsoMu22_v"           ) ||
						passHLTTriggerPattern("HLT_IsoTkMu22_v"         ) ||
						passHLTTriggerPattern("HLT_IsoMu24_v"           ) ||
						passHLTTriggerPattern("HLT_IsoTkMu24_v"         ) );
		HLT_singleMu_noiso = (passHLTTriggerPattern("HLT_Mu50_v"        ) ||
							  passHLTTriggerPattern("HLT_TkMu50_v"      ) ||
							  passHLTTriggerPattern("HLT_Mu55_v"        ) );

		// Double electron
		HLT_DoubleEl_noiso = passHLTTriggerPattern( "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_v"    );
		HLT_DoubleEl       = passHLTTriggerPattern( "HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_v"   ); // prescaled - turned off
		HLT_DoubleEl_DZ    = passHLTTriggerPattern( "HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"); // prescaled
		HLT_DoubleEl_DZ_2  = passHLTTriggerPattern( "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"); // new
   
		// electron-muon
		HLT_MuEG           = (passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v" ) ||
							  passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v"  ) );
		HLT_MuEG_2         = (passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v" ) ||
							  passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v"  ) ||
							  passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v"  ) );
		HLT_MuEG_noiso     =  passHLTTriggerPattern("HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v"                 );

		//separate emu trigs
		HLT_Mu8_EG17      = passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v"  );
		HLT_Mu8_EG23      = passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v"  );
		HLT_Mu8_EG23_DZ   = passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v"  );

		HLT_Mu12_EG23_DZ  = passHLTTriggerPattern("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v" );

		HLT_Mu17_EG12     = passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v" );

		HLT_Mu23_EG8      = passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v"  );
		HLT_Mu23_EG8_DZ   = passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v"  );
		HLT_Mu23_EG12     = passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v" );
		HLT_Mu23_EG12_DZ  = passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v" );
		
		// Double electron
		HLT_DoubleMu_noiso    = (passHLTTriggerPattern( "HLT_Mu27_TkMu8_v"                          ) ||
								 passHLTTriggerPattern( "HLT_Mu30_TkMu11_v"                         ) ||
								 passHLTTriggerPattern( "HLT_Mu40_TkMu11_v"                         ) );
		HLT_DoubleMu          =  passHLTTriggerPattern( "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v"     );
		HLT_DoubleMu_tk       =  passHLTTriggerPattern( "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"   );
		HLT_DoubleMu_dbltk    =  passHLTTriggerPattern( "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v" );
		HLT_DoubleMu_nonDZ    =  passHLTTriggerPattern( "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v"        );
		HLT_DoubleMu_tk_nonDZ =  passHLTTriggerPattern( "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v"      ); // new unprescaled : use these

		// Single photon
		HLT_Photon22_R9Id90_HE10_IsoM  = returnBrokenTrigger("HLT_Photon22_R9Id90_HE10_IsoM_v" );
		HLT_Photon30_R9Id90_HE10_IsoM  = returnBrokenTrigger("HLT_Photon30_R9Id90_HE10_IsoM_v" );
		HLT_Photon36_R9Id90_HE10_IsoM  = returnBrokenTrigger("HLT_Photon36_R9Id90_HE10_IsoM_v" );
		HLT_Photon50_R9Id90_HE10_IsoM  = returnBrokenTrigger("HLT_Photon50_R9Id90_HE10_IsoM_v" );
		HLT_Photon75_R9Id90_HE10_IsoM  = returnBrokenTrigger("HLT_Photon75_R9Id90_HE10_IsoM_v" );
		HLT_Photon90_R9Id90_HE10_IsoM  = returnBrokenTrigger("HLT_Photon90_R9Id90_HE10_IsoM_v" );
		HLT_Photon120_R9Id90_HE10_IsoM = returnBrokenTrigger("HLT_Photon120_R9Id90_HE10_IsoM_v");
		HLT_Photon165_R9Id90_HE10_IsoM = returnBrokenTrigger("HLT_Photon165_R9Id90_HE10_IsoM_v");
		HLT_Photon165_HE10             = returnBrokenTrigger("HLT_Photon165_HE10_v"            );

		// for high pT photon efficiency checks
		HLT_CaloJet500_NoJetID = returnBrokenTrigger("HLT_CaloJet500_NoJetID_v" );
		HLT_ECALHT800_NoJetID  = returnBrokenTrigger("HLT_ECALHT800_NoJetID_v"  );

	  }

	  
      if (verbose) cout << "before gen particles" << endl;

      //GEN PARTICLES
      ngenPart       = 0;
	  ngen_p6s3Part  = 0;
      ngenLep        = 0;
	  ngen_p6s3Lep   = 0;
	  ngenTau        = 0;
      ngenLepFromTau = 0;
      gen_ht         = 0;

	  if ( cms3.evt_isRealData() && !goodrun(cms3.evt_run(), cms3.evt_lumiBlock()) ) evt_passgoodrunlist = false;
	  
	  if( !isData ){
	  
		for(unsigned int iGen = 0; iGen < cms3.genps_p4().size(); iGen++){
		  genPart_p4            .push_back( cms3.genps_p4()                           .at(iGen));
		  genPart_pt            .push_back( cms3.genps_p4()                           .at(iGen).pt());
		  genPart_eta           .push_back( cms3.genps_p4()                           .at(iGen).eta());
		  genPart_phi           .push_back( cms3.genps_p4()                           .at(iGen).phi());
		  genPart_mass          .push_back( cms3.genps_mass()                         .at(iGen));
		  genPart_pdgId         .push_back( cms3.genps_id()                           .at(iGen));
		  genPart_status        .push_back( cms3.genps_status()                       .at(iGen));
		  genPart_isp6status3   .push_back( cms3.genps_isMostlyLikePythia6Status3()   .at(iGen));
		  genPart_charge        .push_back( cms3.genps_charge()                       .at(iGen));
		  genPart_motherId      .push_back( cms3.genps_id_simplemother()              .at(iGen));
		  genPart_grandmaId     .push_back( cms3.genps_id_simplegrandma()             .at(iGen));
		  ngenPart++;
		  if( cms3.genps_isMostlyLikePythia6Status3().at(iGen) ) ngen_p6s3Part++;
		  //calculate gen_ht for stitching purposes
		  if((abs(cms3.genps_id().at(iGen)) <  6 || // quarks
			  abs(cms3.genps_id().at(iGen)) == 21)  // gluons
			 && (cms3.genps_status().at(iGen) == 22 || // something to do with "status 3"
				 cms3.genps_status().at(iGen) == 23)){
			gen_ht += cms3.genps_p4()              .at(iGen).pt();
		  }

		  // save lepton info
		  int pdgId = abs(cms3.genps_id().at(iGen));
		  if ((pdgId != 11) && (pdgId != 13) && (pdgId != 15)) continue;

		  int motherId  = abs(cms3.genps_id_simplemother()  .at(iGen));
		  int grandmaId = abs(cms3.genps_id_simplegrandma() .at(iGen));
		  int status    =     cms3.genps_status()           .at(iGen);

		  // reject leptons with direct parents of quarks or hadrons. 
		  //  Allow SUSY parents - not explicitly checking for now though
		  if (motherId <= 5 || (motherId > 100 && motherId < 1000000)) continue;

		  bool goodLep = false;
		  bool goodTau = false;
		  bool goodLepFromTau = false;
		  int sourceId = 0;

		  // electrons, muons: status 1 or 23 and mother W/Z/H or tau from W/Z/H
		  if ( (pdgId == 11 || pdgId == 13) && (status == 1 || status == 23) ) {
			// save leptons pre-FSR: prefer status 23 over status 1
			if (status == 1 && motherId == pdgId && (cms3.genps_status().at(cms3.genps_idx_simplemother().at(iGen)) == 23)) {
			  // don't save
			}
			// leptons from taus
			else if (motherId == 15 && (grandmaId == 25 || grandmaId == 24 || grandmaId == 23 || grandmaId == 15)) {
			  goodLepFromTau = true;
			} 
			// leptons from W/Z/H
			else if (motherId == 25 || motherId == 24 || motherId == 23) {
			  goodLep = true;
			} 
		  } // status 1 e or mu

		  // taus: status 2 or 23, from W/Z/H
		  else if (pdgId == 15 && (status == 2 || status == 23)) {
			// save leptons pre-FSR: prefer status 23 over status 2
			if (status == 2 && motherId == pdgId && (cms3.genps_status().at(cms3.genps_idx_simplemother().at(iGen)) == 23)) {
			  // don't save
			}
			// leptons from W/Z/H
			else if (motherId == 25 || motherId == 24 || motherId == 23) {
			  goodTau = true;
			} 
		  } // status 2 tau

		  //broken for some reason :(
		  // if (goodLep || goodTau || goodLepFromTau) {
		  //   sourceId = getSourceId(iGen);
		  // }

		  // save gen leptons (e/mu) directly from W/Z/H
		  if (goodLep) {
			genLep_pt            .push_back( cms3.genps_p4()     .at(iGen).pt());
			genLep_eta           .push_back( cms3.genps_p4()     .at(iGen).eta());
			genLep_phi           .push_back( cms3.genps_p4()     .at(iGen).phi());
			genLep_mass          .push_back( cms3.genps_mass()   .at(iGen));
			genLep_pdgId         .push_back( cms3.genps_id()     .at(iGen));
			genLep_status        .push_back( cms3.genps_status() .at(iGen));
			genLep_charge        .push_back( cms3.genps_charge() .at(iGen));
			genLep_isp6status3   .push_back( cms3.genps_isMostlyLikePythia6Status3()   .at(iGen));
			genLep_sourceId      .push_back( sourceId );
			++ngenLep;
			if( cms3.genps_isMostlyLikePythia6Status3().at(iGen) ) ++ngen_p6s3Lep;
		  }

		  // save gen taus from W/Z/H
		  if (goodTau) {
			genTau_pt      .push_back(cms3.genps_p4()     .at(iGen).pt());
			genTau_eta     .push_back(cms3.genps_p4()     .at(iGen).eta());
			genTau_phi     .push_back(cms3.genps_p4()     .at(iGen).phi());
			genTau_mass    .push_back(cms3.genps_mass()   .at(iGen));
			genTau_pdgId   .push_back(cms3.genps_id()     .at(iGen));
			genTau_status  .push_back(cms3.genps_status() .at(iGen));
			genTau_charge  .push_back(cms3.genps_charge() .at(iGen));
			genTau_sourceId.push_back(sourceId);
			++ngenTau;
		  }

		  // save gen e/mu from taus (which are from W/Z/H)
		  if (goodLepFromTau) {
			genLepFromTau_pt      .push_back(cms3.genps_p4()     .at(iGen).pt());
			genLepFromTau_eta     .push_back(cms3.genps_p4()     .at(iGen).eta());
			genLepFromTau_phi     .push_back(cms3.genps_p4()     .at(iGen).phi());
			genLepFromTau_mass    .push_back(cms3.genps_mass()   .at(iGen));
			genLepFromTau_pdgId   .push_back(cms3.genps_id()     .at(iGen));
			genLepFromTau_status  .push_back(cms3.genps_status() .at(iGen));
			genLepFromTau_charge  .push_back(cms3.genps_charge() .at(iGen));
			genLepFromTau_sourceId.push_back(sourceId);
			++ngenLepFromTau;
		  }

		} // loop over genPart
		// cout<<__LINE__<<endl;
	  }

      //LEPTONS
	  std::vector<std::pair<int, float> > lep_pt_ordering;
	  vector<float>vec_lep_pt;
      vector<float>vec_lep_eta;
      vector<float>vec_lep_phi;
      vector<float>vec_lep_mass;
      vector<float>vec_lep_charge;
      vector<int>  vec_lep_pdgId;
      vector<float>vec_lep_dxy;
      vector<float>vec_lep_dz;
      vector<int>  vec_lep_tightId;
      vector<float>vec_lep_relIso03;
      vector<float>vec_lep_relIso03MREA;
      vector<float>vec_lep_relIso03MRDB;
      vector<float>vec_lep_relIso03MRNC;
      vector<float>vec_lep_relIso04;
      vector<int>  vec_lep_mcMatchId;
      vector<int>  vec_lep_lostHits;
      vector<int>  vec_lep_convVeto;
      vector<int>  vec_lep_tightCharge;
      vector<float>vec_lep_MVA;
      vector<float>vec_lep_etaSC;
      vector<float>vec_lep_validfraction;
      vector<float>vec_lep_ptErr;

	  vector<float>vec_lep_sta_pterrOpt ;
	  vector<float>vec_lep_glb_pterrOpt ;
	  // vector<float>vec_lep_bft_pterrOpt ;
	  vector<float>vec_lep_x2ondof      ;
	  vector<float>vec_lep_sta_x2ondof  ;
	  vector<float>vec_lep_glb_x2ondof  ;
	  // vector<float>vec_lep_bft_x2ondof  ;

	  vector<LorentzVector> vec_lep_p4s;

	  vector<LorentzVector> p4sLeptonsForJetCleaning;

	  nveto_leptons = 0;
	  
      if (verbose) cout << "before electrons" << endl;

      //ELECTRONS
      nlep = 0;
      nElectrons10 = 0;
	  for(unsigned int iEl = 0; iEl < cms3.els_p4().size(); iEl++){

		if( passElectronSelection_ZMET_thirdlepton_v1( iEl, false, false ) ){
		  if( abs(cms3.els_p4().at(iEl).eta()) < 2.5 ){
			nveto_leptons++;
		  }
		}
 	  	if( !passElectronSelection_ZMET( iEl ) ) continue;
		
        nElectrons10++;

		if( cms3.els_p4().at(iEl).pt() > 10.0 ){
		  lep_pt_ordering	   .push_back( std::pair<int, float>(nlep, cms3.els_p4().at(iEl).pt()));
		  vec_lep_p4s          .push_back( cms3.els_p4().at(iEl)           );
		  vec_lep_pt           .push_back( cms3.els_p4().at(iEl).pt()      );
		  vec_lep_eta          .push_back( cms3.els_p4().at(iEl).eta()     ); //save eta, even though we use SCeta for ID
		  vec_lep_phi          .push_back( cms3.els_p4().at(iEl).phi()     );
		  vec_lep_mass         .push_back( cms3.els_mass().at(iEl)         );
		  vec_lep_charge       .push_back( cms3.els_charge().at(iEl)       );
		  vec_lep_pdgId        .push_back( cms3.els_charge().at(iEl)*(-11) );
		  vec_lep_dxy          .push_back( cms3.els_dxyPV().at(iEl)        );
		  vec_lep_dz           .push_back( cms3.els_dzPV().at(iEl)         );
		  vec_lep_tightId      .push_back( eleTightID(iEl, ZMET)           );
		  vec_lep_relIso03     .push_back( eleRelIso03EA(iEl,1)            );
		  vec_lep_relIso03MREA .push_back( elMiniRelIsoCMS3_EA( iEl, 1 )   );
		  vec_lep_etaSC        .push_back( els_etaSC().at(iEl)             );
		  vec_lep_MVA          .push_back( getMVAoutput(iEl)               );
		  vec_lep_validfraction.push_back( -1                              );
		  vec_lep_ptErr        .push_back( cms3.els_ptErr() .at(iEl)       );
		  vec_lep_sta_pterrOpt .push_back ( -1                             );
		  vec_lep_glb_pterrOpt .push_back ( -1                             );
		  // vec_lep_bft_pterrOpt .push_back ( cms3.els_bfit_qoverpError().at(iEl) / cms3.els_bfit_qoverp() .at(iEl) );
		  vec_lep_x2ondof      .push_back ( cms3.els_chi2()            .at(iEl) / cms3.els_ndof()        .at(iEl) );
		  vec_lep_sta_x2ondof  .push_back ( -1                             );
		  vec_lep_glb_x2ondof  .push_back ( -1                             );
		  // vec_lep_bft_x2ondof  .push_back ( cms3.els_bfit_chi2()       .at(iEl) / cms3.els_bfit_ndof()   .at(iEl) );

		  if (!isData && (cms3.els_mc3dr().at(iEl) < 0.2 && cms3.els_mc3idx().at(iEl) != -9999 && abs(cms3.els_mc3_id().at(iEl)) == 11 )) { // matched to a prunedGenParticle electron?
			int momid =  abs(genPart_motherId[cms3.els_mc3idx().at(iEl)]);
			vec_lep_mcMatchId.push_back ( momid != 11 ? momid : genPart_grandmaId[cms3.els_mc3idx().at(iEl)]); // if mother is different store mother, otherwise store grandmother
		  }
		  else{
			vec_lep_mcMatchId.push_back (0);
		  }
		  
		  vec_lep_lostHits.push_back ( cms3.els_exp_innerlayers().at(iEl)); //cms2.els_lost_pixelhits().at(iEl);
		  vec_lep_convVeto.push_back ( !cms3.els_conv_vtx_flag().at(iEl));
		  vec_lep_tightCharge.push_back ( tightChargeEle(iEl));

		  nlep++;
		}

		if( cms3.els_p4().at(iEl).pt() > 20.0 ){
		  p4sLeptonsForJetCleaning.push_back(cms3.els_p4().at(iEl));
		}		
      }
	  
	  if (verbose) cout << "before muons" << endl;

      //MUONS
      nMuons10 = 0;
	  // RCLSA: this is a TEMPORARY protections for a problem with CMS3 samples
	  if (cms3.mus_p4().size() != cms3.mus_dzPV().size()) continue;
      
	  for(unsigned int iMu = 0; iMu < cms3.mus_p4().size(); iMu++){
		if( passMuonSelection_ZMET_veto_v2( iMu, false, true ) ){
		  nveto_leptons++;
		}
 	  	if( !passMuonSelection_ZMET( iMu ) ) continue;
		nMuons10++;

		double validFraction = mus_validHits().at(iMu)/(double)(mus_validHits().at(iMu)+mus_lostHits().at(iMu)+mus_exp_innerlayers().at(iMu)+mus_exp_outerlayers().at(iMu));
		
		if( cms3.mus_p4().at(iMu).pt() > 10.0 ){
 		  lep_pt_ordering	   .push_back ( std::pair<int, float>(nlep, cms3.mus_p4().at(iMu).pt()));
		  vec_lep_p4s          .push_back ( cms3.mus_p4()    .at(iMu)       );
		  vec_lep_pt           .push_back ( cms3.mus_p4()    .at(iMu).pt()  );
		  vec_lep_eta          .push_back ( cms3.mus_p4()    .at(iMu).eta() );
		  vec_lep_phi          .push_back ( cms3.mus_p4()    .at(iMu).phi() );
		  vec_lep_mass         .push_back ( cms3.mus_mass()  .at(iMu)       );
		  vec_lep_charge       .push_back ( cms3.mus_charge().at(iMu)       );
		  vec_lep_pdgId        .push_back ( cms3.mus_charge().at(iMu)*(-13) );
		  vec_lep_dxy          .push_back ( cms3.mus_dxyPV() .at(iMu)       );
		  vec_lep_dz           .push_back ( cms3.mus_dzPV()  .at(iMu)       );
		  vec_lep_tightId      .push_back ( isTightMuonPOG(iMu)             );
		  vec_lep_relIso03     .push_back ( muRelIso03EA(iMu,1)             );
		  vec_lep_relIso03MREA .push_back ( muMiniRelIsoCMS3_EA( iMu, 1)    );
		  vec_lep_etaSC        .push_back ( cms3.mus_p4().at(iMu).eta()     );
		  vec_lep_MVA          .push_back ( -99                             );
		  vec_lep_validfraction.push_back ( validFraction                   );
		  vec_lep_ptErr        .push_back ( cms3.mus_ptErr() .at(iMu)       );

		  vec_lep_sta_pterrOpt .push_back ( cms3.mus_sta_qoverpError() .at(iMu) / cms3.mus_sta_qoverp()  .at(iMu) );
		  vec_lep_glb_pterrOpt .push_back ( cms3.mus_gfit_qoverpError().at(iMu) / cms3.mus_gfit_qoverp() .at(iMu) );
		  // vec_lep_bft_pterrOpt .push_back ( cms3.mus_bfit_qoverpError().at(iMu) / cms3.mus_bfit_qoverp() .at(iMu) );
		  vec_lep_x2ondof      .push_back ( cms3.mus_chi2()            .at(iMu) / cms3.mus_ndof()        .at(iMu) );
		  vec_lep_sta_x2ondof  .push_back ( cms3.mus_sta_chi2()        .at(iMu) / cms3.mus_sta_ndof()    .at(iMu) );
		  vec_lep_glb_x2ondof  .push_back ( cms3.mus_gfit_chi2()       .at(iMu) / cms3.mus_gfit_ndof()   .at(iMu) );
		  // vec_lep_bft_x2ondof  .push_back ( cms3.mus_bfit_chi2()       .at(iMu) / cms3.mus_bfit_ndof()   .at(iMu) );
		  
		  if (!isData && (cms3.mus_mc3dr().at(iMu) < 0.2 && cms3.mus_mc3idx().at(iMu) != -9999 && abs(cms3.mus_mc3_id().at(iMu)) == 13 )) { // matched to a prunedGenParticle electron?
			int momid =  abs(genPart_motherId[cms3.mus_mc3idx().at(iMu)]);
			vec_lep_mcMatchId.push_back ( momid != 13 ? momid : genPart_grandmaId[cms3.mus_mc3idx().at(iMu)]); // if mother is different store mother, otherwise store grandmother
		  }
		  else vec_lep_mcMatchId.push_back (0);

		  vec_lep_lostHits   .push_back ( cms3.mus_exp_innerlayers().at(iMu)); // use defaults as if "good electron"
		  vec_lep_convVeto   .push_back ( 1                                 );// use defaults as if "good electron"
		  vec_lep_tightCharge.push_back ( tightChargeMuon(iMu)              );

		  nlep++;

		}

		if( cms3.mus_p4().at(iMu).pt() > 20.0 ){
		  p4sLeptonsForJetCleaning.push_back(cms3.mus_p4().at(iMu));
		}

      }

	  // veto leptons are looser than analysis leptons
	  nveto_leptons -= nlep;
	  
	  if (verbose) cout<<" before ordering"<<endl;
	  
      // Implement pT ordering for leptons (it's irrelevant but easier for us to add than for ETH to remove)
      //now fill arrays from vectors, isotracks with largest pt first
      int i = 0;
      std::sort(lep_pt_ordering.begin(), lep_pt_ordering.end(), sortByValue);
      for(std::vector<std::pair<int, float> >::iterator it = lep_pt_ordering.begin(); it!= lep_pt_ordering.end(); ++it){
		lep_p4           .push_back( vec_lep_p4s          .at(it->first));
		lep_pt           .push_back( vec_lep_pt           .at(it->first));
		lep_eta          .push_back( vec_lep_eta          .at(it->first));
		lep_phi          .push_back( vec_lep_phi          .at(it->first));
		lep_mass         .push_back( vec_lep_mass         .at(it->first));
		lep_charge       .push_back( vec_lep_charge       .at(it->first));
		lep_pdgId        .push_back( vec_lep_pdgId        .at(it->first));
		lep_dz           .push_back( vec_lep_dz           .at(it->first));
		lep_dxy          .push_back( vec_lep_dxy          .at(it->first));
		lep_etaSC        .push_back( vec_lep_etaSC        .at(it->first));
		lep_tightId      .push_back( vec_lep_tightId      .at(it->first));
		lep_relIso03MREA .push_back( vec_lep_relIso03MREA .at(it->first));
		lep_mcMatchId    .push_back( vec_lep_mcMatchId    .at(it->first));
		lep_lostHits     .push_back( vec_lep_lostHits     .at(it->first));
		lep_convVeto     .push_back( vec_lep_convVeto     .at(it->first));
		lep_tightCharge  .push_back( vec_lep_tightCharge  .at(it->first));
		lep_MVA          .push_back( vec_lep_MVA          .at(it->first));
		lep_validfraction.push_back( vec_lep_validfraction.at(it->first));
		lep_pterr        .push_back( vec_lep_ptErr        .at(it->first));
		lep_sta_pterrOpt .push_back( vec_lep_sta_pterrOpt .at(it->first));
		lep_glb_pterrOpt .push_back( vec_lep_glb_pterrOpt .at(it->first));
		// lep_bft_pterrOpt .push_back( vec_lep_bft_pterrOpt .at(it->first));
		lep_x2ondof      .push_back( vec_lep_x2ondof      .at(it->first));
		lep_sta_x2ondof  .push_back( vec_lep_sta_x2ondof  .at(it->first));
		lep_glb_x2ondof  .push_back( vec_lep_glb_x2ondof  .at(it->first));
		// lep_bft_x2ondof  .push_back( vec_lep_bft_x2ondof  .at(it->first));

		i++;
      }
        
	  if (verbose) cout << "before photons" << endl;

      //PHOTONS
      ngamma = 0;
      nGammas20 = 0;
	  for(unsigned int iGamma = 0; iGamma < cms3.photons_p4().size(); iGamma++){
 		if( !passPhotonSelection_ZMET( iGamma ) )continue;
	  
		
		float pt  = cms3.photons_p4().at(iGamma).pt();
		float eta = cms3.photons_p4().at(iGamma).eta();
		float phi = cms3.photons_p4().at(iGamma).phi();

		gamma_p4           .push_back( cms3.photons_p4().at(iGamma) );
		gamma_pt           .push_back( pt                           );
		gamma_eta          .push_back( eta                          );
		gamma_phi          .push_back( phi                          );

		gamma_mass         .push_back( cms3.photons_mass().at(iGamma)                  );
		gamma_sigmaIetaIeta.push_back( cms3.photons_full5x5_sigmaIEtaIEta().at(iGamma) );
		gamma_chHadIso     .push_back( cms3.photons_chargedHadronIso().at(iGamma)      );
		gamma_neuHadIso    .push_back( cms3.photons_neutralHadronIso().at(iGamma)      );
		gamma_phIso        .push_back( cms3.photons_photonIso().at(iGamma)             );
		gamma_r9           .push_back( cms3.photons_full5x5_r9().at(iGamma)            );
		gamma_hOverE       .push_back( cms3.photons_full5x5_hOverEtowBC().at(iGamma)   );
		gamma_idCutBased   .push_back( isTightPhoton(iGamma,HAD) ? 1 : 0               ); 		
		gamma_hollowtkiso03.push_back( cms3.photons_tkIsoHollow03()   .at(iGamma)      );
		gamma_ecpfclusiso  .push_back( photonEcalpfClusterIso03EA(iGamma)              );
		gamma_hcpfclusiso  .push_back( photonHcalpfClusterIso03EA(iGamma)              );

		if(gamma_pt[ngamma] > 20) nGammas20++;
	
		// Some work for truth-matching (should be integrated in CMS3 as for the leptons)
		int bestMatch = -1;
		float bestDr = 0.1;

		if( !isData ){		  
		  for(unsigned int iGen = 0; iGen < cms3.genps_p4().size(); iGen++){
			if ( cms3.genps_id()                   .at(iGen)        != 22 ) continue; 
			if ( cms3.genps_status()               .at(iGen)        != 1  ) continue; 
			if ( fabs(cms3.genps_id_simplemother() .at(iGen))       > 22  ) continue; // pions etc 
			if ( fabs(eta - cms3.genps_p4()        .at(iGen).eta()) > 0.1 ) continue;
			if ( 2*cms3.genps_p4()                 .at(iGen).pt()   < pt  ) continue;
			if ( 0.5*cms3.genps_p4()               .at(iGen).pt()   > pt  ) continue;
			float thisDR = DeltaR( cms3.genps_p4() .at(iGen).eta(), eta, cms3.genps_p4().at(iGen).phi(), phi);
			if (thisDR < bestDr) {
			  bestDr = thisDR;
			  bestMatch = iGen;
			}
		  }
		  if (bestMatch != -1) {
			// 7 is a special code for photons without a mother. this seems to be due to a miniAOD bug where links are broken.
			gamma_mcMatchId.push_back(cms3.genps_id_simplemother().at(bestMatch) == 0 ? 7 : 22); 
			gamma_genIso.push_back(-1); //cms2.genps_iso().at(bestMatch);
		  }
		  else {
			gamma_mcMatchId.push_back(0);
			gamma_genIso.push_back(-1);
		  }
		}   


		ngamma++;
      }
	
	  if( isData && ngamma > 0 ){
	    float minDr = 0.2;		

		for( size_t hltind = 0; hltind < cms3.hlt_trigObjs_id().size(); hltind++ ){ // loop over HLTs		  
		  for( size_t trigind = 0; trigind < cms3.hlt_trigObjs_id().at(hltind).size(); trigind++ ){

			if( cms3.hlt_trigObjs_passLast().at(hltind).at(trigind) ){
			  float thisDR = ROOT::Math::VectorUtil::DeltaR(cms3.hlt_trigObjs_p4().at(hltind).at(trigind), gamma_p4.at(0));

			  if( HLT_Photon165_HE10             > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon165_HE10"            ) ) if( thisDR < minDr ) HLT_Photon165_HE10_matchedtophoton             = true;
			  if( HLT_Photon165_R9Id90_HE10_IsoM > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon165_R9Id90_HE10_IsoM") ) if( thisDR < minDr ) HLT_Photon165_R9Id90_HE10_IsoM_matchedtophoton = true;
			  if( HLT_Photon120_R9Id90_HE10_IsoM > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon120_R9Id90_HE10_IsoM") ) if( thisDR < minDr ) HLT_Photon120_R9Id90_HE10_IsoM_matchedtophoton = true;
			  if( HLT_Photon90_R9Id90_HE10_IsoM  > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon90_R9Id90_HE10_IsoM" ) ) if( thisDR < minDr ) HLT_Photon90_R9Id90_HE10_IsoM_matchedtophoton  = true;
			  if( HLT_Photon75_R9Id90_HE10_IsoM  > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon75_R9Id90_HE10_IsoM" ) ) if( thisDR < minDr ) HLT_Photon75_R9Id90_HE10_IsoM_matchedtophoton  = true;
			  if( HLT_Photon50_R9Id90_HE10_IsoM  > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon50_R9Id90_HE10_IsoM" ) ) if( thisDR < minDr ) HLT_Photon50_R9Id90_HE10_IsoM_matchedtophoton  = true;
			  if( HLT_Photon36_R9Id90_HE10_IsoM  > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon36_R9Id90_HE10_IsoM" ) ) if( thisDR < minDr ) HLT_Photon36_R9Id90_HE10_IsoM_matchedtophoton  = true;
			  if( HLT_Photon30_R9Id90_HE10_IsoM  > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon30_R9Id90_HE10_IsoM" ) ) if( thisDR < minDr ) HLT_Photon30_R9Id90_HE10_IsoM_matchedtophoton  = true;
			  if( HLT_Photon22_R9Id90_HE10_IsoM  > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon22_R9Id90_HE10_IsoM" ) ) if( thisDR < minDr ) HLT_Photon22_R9Id90_HE10_IsoM_matchedtophoton  = true;

			  // dump info for events that don't have a matched photon
			  // if( (HLT_Photon165_HE10             > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon165_HE10"            ) ) ||
			  // 	  (HLT_Photon165_R9Id90_HE10_IsoM > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon165_R9Id90_HE10_IsoM") ) ||
			  // 	  (HLT_Photon120_R9Id90_HE10_IsoM > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon120_R9Id90_HE10_IsoM") ) ||
			  // 	  (HLT_Photon90_R9Id90_HE10_IsoM  > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon90_R9Id90_HE10_IsoM" ) ) ||
			  // 	  (HLT_Photon75_R9Id90_HE10_IsoM  > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon75_R9Id90_HE10_IsoM" ) ) ||
			  // 	  (HLT_Photon50_R9Id90_HE10_IsoM  > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon50_R9Id90_HE10_IsoM" ) ) ||
			  // 	  (HLT_Photon36_R9Id90_HE10_IsoM  > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon36_R9Id90_HE10_IsoM" ) ) ||
			  // 	  (HLT_Photon30_R9Id90_HE10_IsoM  > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon30_R9Id90_HE10_IsoM" ) ) ||
			  // 	  (HLT_Photon22_R9Id90_HE10_IsoM  > 0 && TString(cms3.hlt_trigNames().at(hltind)).Contains("HLT_Photon22_R9Id90_HE10_IsoM" ) ) ){
			  // 	if( thisDR > minDr ){
			  // 	  cout<<"trig   : "<<cms3.hlt_trigNames().at(hltind)<<endl;
			  // 	  cout<<"trig pt: "<<cms3.hlt_trigObjs_p4().at(hltind).at(trigind).pt()<<endl;
			  // 	  cout<<"offl pt: "<<gamma_p4.at(0)                               .pt()<<endl;
			  // 	  cout<<"trig et: "<<cms3.hlt_trigObjs_p4().at(hltind).at(trigind).eta()<<endl;
			  // 	  cout<<"offl et: "<<gamma_p4.at(0)                               .eta()<<endl;
			  // 	  cout<<"trig ph: "<<cms3.hlt_trigObjs_p4().at(hltind).at(trigind).phi()<<endl;
			  // 	  cout<<"offl ph: "<<gamma_p4.at(0)                               .phi()<<endl;
			  // 	}
			  // }
			  
			}
		  }
		}
	  }
	  
	  // add selections to keep only events with photons and dilepton events
	  if( !(ngamma > 0 || nlep > 0) ) continue;// fix for not iso study
       
		// std::pair <int, int> hyp_indices =  getHypLepIndices( lep_p4, lep_pdgId );
	  std::pair <int, int> hyp_indices = std::make_pair(0, 1);
		
	  if (nlep > 1 ) {//require min 2 leps
		if (lep_charge.at(hyp_indices.first)*lep_charge.at(hyp_indices.second) > 0){
		  evt_type = 1; // same sign event
		}else{
		  evt_type = 0; // oppo sign event 
		}

		if (        abs(lep_pdgId.at(hyp_indices.first)) == 11 && abs(lep_pdgId.at(hyp_indices.second)) == 11  ){ hyp_type = 0;// ee event												   			   
		}else if (  abs(lep_pdgId.at(hyp_indices.first)) == 13 && abs(lep_pdgId.at(hyp_indices.second)) == 13  ){ hyp_type = 1;// mm event												   			   
		}else if ( (abs(lep_pdgId.at(hyp_indices.first)) == 11 && abs(lep_pdgId.at(hyp_indices.second)) == 13) ||
				   (abs(lep_pdgId.at(hyp_indices.first)) == 13 && abs(lep_pdgId.at(hyp_indices.second)) == 11) ){ hyp_type = 2;// em event
		}else {
		  cout<<"Leptype not ee, mm, or em! Exiting."<<endl;
		  continue;
		}
		
		dilmass = (lep_p4.at(hyp_indices.first)+lep_p4.at(hyp_indices.second)).mass();
		dilpt   = (lep_p4.at(hyp_indices.first)+lep_p4.at(hyp_indices.second)).pt();       

		//Add dRll
		float dEtall =            lep_p4.at(hyp_indices.first).eta() - lep_p4.at(hyp_indices.second).eta();
		float dPhill = acos( cos( lep_p4.at(hyp_indices.first).phi() - lep_p4.at(hyp_indices.second).phi() ) );
		dRll = sqrt(pow( dEtall, 2) + pow( dPhill, 2));

		LorentzVector z_pt(lep_p4.at(hyp_indices.first).X()+lep_p4.at(hyp_indices.second).X(),
						   lep_p4.at(hyp_indices.first).Y()+lep_p4.at(hyp_indices.second).Y(),
						   lep_p4.at(hyp_indices.first).Z()+lep_p4.at(hyp_indices.second).Z(),
						   lep_p4.at(hyp_indices.first).E()+lep_p4.at(hyp_indices.second).E());

		//start from here
		std::pair<LorentzVector, LorentzVector> lepsFromDecayedGamma = returnDecayProducts( z_pt );
		decayedphoton_lep1_p4 = lepsFromDecayedGamma.first;
		decayedphoton_lep2_p4 = lepsFromDecayedGamma.second;
		decayedphoton_bosn_p4 =
		  LorentzVector(decayedphoton_lep1_p4.X()+decayedphoton_lep2_p4.X(),
						decayedphoton_lep1_p4.Y()+decayedphoton_lep2_p4.Y(),
						decayedphoton_lep1_p4.Z()+decayedphoton_lep2_p4.Z(),
						decayedphoton_lep1_p4.E()+decayedphoton_lep2_p4.E());
		
		decayedphoton_mt2 = 0;
		if( abs(decayedphoton_lep1_p4.eta()) < 2.4 && abs(decayedphoton_lep2_p4.eta()) < 2.4  ){
		  if( (abs(decayedphoton_lep1_p4.eta()) < 1.4 || abs(decayedphoton_lep1_p4.eta()) > 1.6) &&
			  (abs(decayedphoton_lep2_p4.eta()) < 1.4 || abs(decayedphoton_lep2_p4.eta()) > 1.6) ){
			decayedphoton_mt2 = MT2( met_T1CHS_miniAOD_CORE_pt, met_T1CHS_miniAOD_CORE_phi, decayedphoton_lep1_p4, decayedphoton_lep2_p4, 0.0 );
		  }
		}
		
	  }else if( ngamma > 0 ) {// here are the photon only variables
		evt_type = 2; // photon + jets event

		//start from here
		std::pair<LorentzVector, LorentzVector> lepsFromDecayedGamma = returnDecayProducts( gamma_p4.at(0) );
		decayedphoton_lep1_p4 = lepsFromDecayedGamma.first;
		decayedphoton_lep2_p4 = lepsFromDecayedGamma.second;
		decayedphoton_bosn_p4 =
		  LorentzVector(decayedphoton_lep1_p4.X()+decayedphoton_lep2_p4.X(),
						decayedphoton_lep1_p4.Y()+decayedphoton_lep2_p4.Y(),
						decayedphoton_lep1_p4.Z()+decayedphoton_lep2_p4.Z(),
						decayedphoton_lep1_p4.E()+decayedphoton_lep2_p4.E());
		
		decayedphoton_mt2 = 0;
		if( abs(decayedphoton_lep1_p4.eta()) < 2.4 && abs(decayedphoton_lep2_p4.eta()) < 2.4  ){
		  if( (abs(decayedphoton_lep1_p4.eta()) < 1.4 || abs(decayedphoton_lep1_p4.eta()) > 1.6) &&
			  (abs(decayedphoton_lep2_p4.eta()) < 1.4 || abs(decayedphoton_lep2_p4.eta()) > 1.6) ){
			decayedphoton_mt2 = MT2( met_T1CHS_miniAOD_CORE_pt, met_T1CHS_miniAOD_CORE_phi, decayedphoton_lep1_p4, decayedphoton_lep2_p4, 0.0 );
		  }
		}
		
	  }else{
		continue; // leftovers
	  }
       	  
	  if (verbose) cout << "before jets" << endl;
	  
      //JETS
      //correct jets and check baseline selections
      vector < LorentzVector> p4sCorrJets; // store corrected p4 for ALL jets, so indices match CMS3 ntuple
      vector < double       > jet_corrfactor; // store correction for ALL jets, and indices match CMS3 ntuple
      vector < int          > passJets; //index of jets that pass baseline selections
      vector < double       > jet_corrfactor_up; // store correction for ALL jets, and vary by uncertainties
      vector < double       > jet_corrfactor_dn; // store correction for ALL jets, and vary by uncertainties

      for(unsigned int iJet = 0; iJet < cms3.pfjets_p4().size(); iJet++){

		LorentzVector pfjet_p4_cor = cms3.pfjets_p4().at(iJet);

		double corr = 1.0;
		double shift = 0.0;
		if (applyJECfromFile) {

		  // get uncorrected jet p4 to use as input for corrections
		  LorentzVector pfjet_p4_uncor = cms3.pfjets_p4().at(iJet) * cms3.pfjets_undoJEC().at(iJet);

		  // get L1FastL2L3Residual total correction
		  jet_corrector_pfL1FastJetL2L3->setRho   ( cms3.evt_fixgridfastjet_all_rho() );
		  jet_corrector_pfL1FastJetL2L3->setJetA  ( cms3.pfjets_area().at(iJet)       );
		  jet_corrector_pfL1FastJetL2L3->setJetPt ( pfjet_p4_uncor.pt()               );
		  jet_corrector_pfL1FastJetL2L3->setJetEta( pfjet_p4_uncor.eta()              );
		  // corr = jet_corrector_pfL1FastJetL2L3->getCorrection();

		  vector<float> corr_vals = jet_corrector_pfL1FastJetL2L3->getSubCorrections();
		  corr        = corr_vals.at(corr_vals.size()-1); // All corrections

		  // apply new JEC to p4
		  pfjet_p4_cor = pfjet_p4_uncor * corr;

		  shift = 0.0;
		  if (jecUnc != 0) {
			jecUnc->setJetEta(pfjet_p4_uncor.eta()); 
			jecUnc->setJetPt(pfjet_p4_uncor.pt()*corr); 
			double unc = jecUnc->getUncertainty(true);
			if( cms3.evt_isRealData() && jetcorr_filenames_pfL1FastJetL2L3.size() == 4 ){
			  shift = sqrt(unc*unc + pow((corr_vals.at(corr_vals.size()-1)/corr_vals.at(corr_vals.size()-2)-1.),2));	  
			}else{
			  shift = unc;
			}
		  }

		}
		
		p4sCorrJets.push_back(pfjet_p4_cor);
		jet_corrfactor.push_back(corr);
		jet_corrfactor_up.push_back(1.0 + shift);
		jet_corrfactor_dn.push_back(1.0 - shift);
  
		if(p4sCorrJets.at(iJet).pt() < 15.0) continue; 
        if(fabs(p4sCorrJets.at(iJet).eta()) > 5.2) continue;
		// note this uses the eta of the jet as stored in CMS3
		//  chance for small discrepancies if JEC changes direction slightly..
        if(!isLoosePFJet_50nsV1(iJet) && !isSMSScan) continue;
		if( isSMSScan && isBadFastsimJet(iJet) ) continue;
		passJets.push_back(iJet);
      }

	  if (verbose) cout << "before jet/photon requirements" << endl;
 	  //matched to pfJet with pT > 10 GeV, within cone of dR < 0.3. neutral EM energy fraction > 0.7
 	  for(int iGamma = 0; iGamma < ngamma; iGamma++){
 		if (iGamma>0) continue; // Only care about leading photon.
 
 		float minDR = 0.4;
 		int minIndex = -1;
 		for(unsigned int passIdx = 0; passIdx < passJets.size(); passIdx++){ //loop through jets that passed baseline selections
 	
 		  // int iJet = passJets.at(passIdx);
 		  int iJet = passJets.at(passIdx);
 
 		  if(p4sCorrJets.at(iJet).pt() < 10.0       ) continue;
 		  if(fabs(p4sCorrJets.at(iJet).eta()) > 5.2 ) continue;
 
 		  // float thisDR = DeltaR(p4sCorrJets.at(iJet).eta(), gamma_eta[iGamma], p4sCorrJets.at(iJet).phi(), gamma_phi[iGamma]);
 		  // float thisDR = DeltaR(pfjets_p4().at(iJet).eta(), gamma_eta[iGamma], pfjets_p4().at(iJet).phi(), gamma_phi[iGamma]);
 		  float thisDR = ROOT::Math::VectorUtil::DeltaR(p4sCorrJets.at(iJet), gamma_p4[iGamma]);
 		  if(thisDR < minDR){
 			minDR = thisDR; 
 			minIndex = iJet;
 		  }
 		} // end jet loop

		// get emf of jet closest to photon
 		if( minIndex > -1 ){
 		  matched_neutralemf = ( cms3.pfjets_neutralEmE().at(minIndex)                                         ) / (p4sCorrJets.at(minIndex).energy()/jet_corrfactor.at(minIndex));
 		  matched_emf        = ( cms3.pfjets_neutralEmE().at(minIndex) + cms3.pfjets_chargedEmE().at(minIndex) ) / (p4sCorrJets.at(minIndex).energy()/jet_corrfactor.at(minIndex));
 		}else{

		  for(unsigned int jetind = 0; jetind < cms3.pfjets_p4().size(); jetind++){ //loop through jets that passed baseline selections

			float thisDR = ROOT::Math::VectorUtil::DeltaR(cms3.pfjets_p4().at(jetind), gamma_p4[iGamma]);
			if(thisDR < minDR){
			  minDR = thisDR; 
			  minIndex = jetind;
			}
		  }

		  if( minIndex > -1 ){
			matched_neutralemf = ( cms3.pfjets_neutralEmE().at(minIndex)                                         ) / (cms3.pfjets_p4().at(minIndex).energy()*cms3.pfjets_undoJEC().at(minIndex));
			matched_emf        = ( cms3.pfjets_neutralEmE().at(minIndex) + cms3.pfjets_chargedEmE().at(minIndex) ) / (cms3.pfjets_p4().at(minIndex).energy()*cms3.pfjets_undoJEC().at(minIndex));
		  }
		}
		 	  
 		if (verbose) cout << "before checking for photon/electron overlap" << endl;

 		//	  elveto
 		for(unsigned int iEl = 0; iEl < cms3.els_p4().size(); iEl++){
 		  if(cms3.els_p4().at(iEl).pt() < 10.0                                              ) continue; // pT > 10 GeV
 		  if( ROOT::Math::VectorUtil::DeltaR(cms3.els_p4().at(iEl), gamma_p4[iGamma]) > 0.2 ) continue; // dr < 0.2
 		  elveto = true;
 		} // end electron loop	  		
 	  }	  
	  
      if (verbose) cout << "before jet/lepton overlap" << endl;

      //check overlapping with leptons
      //only want to remove the closest jet to a lepton, threshold deltaR < 0.4
      vector<int> removedJets; //index of jets to be removed because they overlap with a lepton
      for(unsigned int iLep = 0; iLep < p4sLeptonsForJetCleaning.size(); iLep++){

        float minDR = 0.4;
        int minIndex = -1;
        for(unsigned int passIdx = 0; passIdx < passJets.size(); passIdx++){ //loop through jets that passed baseline selections

          int iJet = passJets.at(passIdx);

          if(      !(p4sCorrJets.at(iJet).pt()    > 35.0 ||
					 (p4sCorrJets.at(iJet).pt()    > 25.0 && getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", iJet) >= 0.800))) continue;
          if( fabs(p4sCorrJets.at(iJet).eta() ) > 2.4  ) continue;
          if( !(isLoosePFJet_50nsV1(iJet) || isSMSScan) ) continue;
		  if( isSMSScan && isBadFastsimJet(iJet) ) continue;

          bool alreadyRemoved = false;
          for(unsigned int j=0; j<removedJets.size(); j++){
            if(iJet == removedJets.at(j)){
              alreadyRemoved = true;
              break;
            }
          }
          if(alreadyRemoved) continue;

          float thisDR = DeltaR(p4sCorrJets.at(iJet).eta(), p4sLeptonsForJetCleaning.at(iLep).eta(), p4sCorrJets.at(iJet).phi(), p4sLeptonsForJetCleaning.at(iLep).phi());
          if(thisDR < minDR){
            minDR = thisDR; 
            minIndex = iJet;
          }
        }
        removedJets.push_back(minIndex);
      }

	  if (verbose) cout << "before isr weight loop over jets" << endl;

	  if( !isData ){

		bool failbadfastsimjet = false;	  
		vector <LorentzVector> jets_for_pileup;
		for(unsigned int iJet = 0; iJet < cms3.pfjets_p4().size(); iJet++){

		  LorentzVector pfjet_p4_cor = cms3.pfjets_p4().at(iJet);

		  double corr = 1.0;
		  if (applyJECfromFile) {

			// get uncorrected jet p4 to use as input for corrections
			LorentzVector pfjet_p4_uncor = cms3.pfjets_p4().at(iJet) * cms3.pfjets_undoJEC().at(iJet);

			// get L1FastL2L3Residual total correction
			jet_corrector_pfL1FastJetL2L3->setRho   ( cms3.evt_fixgridfastjet_all_rho() );
			jet_corrector_pfL1FastJetL2L3->setJetA  ( cms3.pfjets_area().at(iJet)       );
			jet_corrector_pfL1FastJetL2L3->setJetPt ( pfjet_p4_uncor.pt()               );
			jet_corrector_pfL1FastJetL2L3->setJetEta( pfjet_p4_uncor.eta()              );

			vector<float> corr_vals = jet_corrector_pfL1FastJetL2L3->getSubCorrections();
			corr        = corr_vals.at(corr_vals.size()-1); // All corrections

			// apply new JEC to p4
			pfjet_p4_cor = pfjet_p4_uncor * corr;
		  }
		
		  if(       pfjet_p4_cor.pt()    < 30.0       ) continue; 
		  if( fabs( pfjet_p4_cor.eta() ) > 2.4        ) continue;
		  if(!isLoosePFJet_50nsV1(iJet) && !isSMSScan ) continue;
		  if( isSMSScan && isBadFastsimJet(iJet)      ) failbadfastsimjet = true;

		  bool jetoverlapswithlepton = false;
		  for(unsigned int iLep = 0; iLep < p4sLeptonsForJetCleaning.size(); iLep++){

			float minDR = 0.4;
			for(unsigned int passIdx = 0; passIdx < passJets.size(); passIdx++){ //loop through jets that passed baseline selections

			  float thisDR = DeltaR(pfjet_p4_cor.eta(), p4sLeptonsForJetCleaning.at(iLep).eta(), pfjet_p4_cor.phi(), p4sLeptonsForJetCleaning.at(iLep).phi());
			  if(thisDR < minDR){
				minDR = thisDR; 
				jetoverlapswithlepton = true;
			  }
			}
		  }
		  
		  if( jetoverlapswithlepton ) continue;

		  jets_for_pileup.push_back(pfjet_p4_cor);
		}

		if( failbadfastsimjet ) continue; // throw away event if fails bad fastsim jet

		isr_njets  = get_nisrMatch( jets_for_pileup );
		isr_weight = get_isrWeight( isr_njets       );
		isr_unc    = get_isrUnc(    isr_njets       );
	  }

      if (verbose) cout << "before jet/photon overlap" << endl;

      //check overlapping with photons
      //only want to remove the closest jet to a photon, threshold deltaR < 0.4
      vector<int> removedJetsGamma; //index of jets to be removed because they overlap with a photon
      for(int iGamma = 0; iGamma < ngamma; iGamma++){
		if (iGamma>0) continue; // Only check leading photon. Let the others be

        float minDR = 0.4;
        int minIndex = -1;
        for(unsigned int passIdx = 0; passIdx < passJets.size(); passIdx++){ //loop through jets that passed baseline selections

          int iJet = passJets.at(passIdx);

          if(      !(p4sCorrJets.at(iJet).pt()    > 35.0 ||
					 (p4sCorrJets.at(iJet).pt()    > 25.0 && getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", iJet) >= 0.800))) continue;
          if( fabs(p4sCorrJets.at(iJet).eta() ) > 2.4  ) continue;
          if( !(isLoosePFJet_50nsV1(iJet) || isSMSScan) ) continue;
		  if( isSMSScan && isBadFastsimJet(iJet) ) continue;
		
          bool alreadyRemoved = false;
          for(unsigned int j=0; j<removedJetsGamma.size(); j++){
            if(iJet == removedJetsGamma.at(j)){
              alreadyRemoved = true;
              break;
            }
          }
          if(alreadyRemoved) continue;

          float thisDR = DeltaR(p4sCorrJets.at(iJet).eta(), gamma_eta[iGamma], p4sCorrJets.at(iJet).phi(), gamma_phi[iGamma]);
          if(thisDR < minDR){
            minDR = thisDR; 
            minIndex = iJet;
          }
        }
        removedJetsGamma.push_back(minIndex);
      }

      nBJetTight  = 0;
      nBJetMedium = 0;
      nBJetLoose  = 0;
      nBJetTight_up  = 0;
      nBJetMedium_up = 0;
      nBJetLoose_up  = 0;
      nBJetTight_dn  = 0;
      nBJetMedium_dn = 0;
      nBJetLoose_dn  = 0;

	  njets    = 0;
	  njets_up = 0;
	  njets_dn = 0;
	  ht    = 0;
	  ht_up = 0;
	  ht_dn = 0;

      // for applying btagging SFs, using Method 1a from the twiki below:
      //   https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagSFMethods#1a_Event_reweighting_using_scale
      //   https://twiki.cern.ch/twiki/pub/CMS/BTagSFMethods/Method1aExampleCode_CSVM.cc.txt
      float btagprob_data = 1.;
	  float btagprob_heavy_UP = 1.;
	  float btagprob_heavy_DN = 1.;
	  float btagprob_light_UP = 1.;
	  float btagprob_light_DN = 1.;
	  float btagprob_mc = 1.;
	  
      if (verbose) cout << "before main jet loop" << endl;
      //now fill variables for jets that pass baseline selections and don't overlap with a lepton
      for(unsigned int passIdx = 0; passIdx < passJets.size(); passIdx++){

        int iJet = passJets.at(passIdx);

        //check against list of jets that overlap with a lepton
        bool isOverlapJet = false;
        for(unsigned int j=0; j<removedJets.size(); j++){
          if(iJet == removedJets.at(j)){
            isOverlapJet = true;
            break;
          }
        }
        if(isOverlapJet) continue;

        //check against list of jets that overlap with a photon for photon+jets events
        bool isOverlapJetGamma = false;
        for(unsigned int j=0; j<removedJetsGamma.size(); j++){
          if(iJet == removedJetsGamma.at(j)){
            isOverlapJetGamma = true;
            break;
          }
        }
        if(evt_type == 2 && isOverlapJetGamma) continue;

		if( verbose ) cout<<"Before filling jet branches"<<endl;

		float current_csv_val = getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", iJet);

		if( p4sCorrJets.at(iJet).pt() > 25.0 && abs(p4sCorrJets.at(iJet).eta()) < 2.4 ){
 		  if( p4sCorrJets.at(iJet).pt() > 35.0 ) {
			jets_p4                                       .push_back(p4sCorrJets.at(iJet));
			jets_csv                                      .push_back(current_csv_val);
		  }
		  if( current_csv_val >= 0.800 ){
			if( p4sCorrJets.at(iJet).pt() <= 35.0 ) {
			  jets_p4                                       .push_back(p4sCorrJets.at(iJet));
			  jets_csv                                      .push_back(current_csv_val);
			}
			jets_medb_p4  .push_back(p4sCorrJets.at(iJet));
		  }	   

		  if( !isData ){
			jets_mcFlavour   .push_back(cms3.pfjets_partonFlavour().at(iJet));
		  	jets_mcHadronFlav.push_back(cms3.pfjets_hadronFlavour().at(iJet));
		  }

		  // require pT > 35 for HT
		  if( p4sCorrJets.at(iJet).pt() > 35.0 ){ ht+=p4sCorrJets.at(iJet).pt(); }
		
		  if(current_csv_val >= 0.935) { nBJetTight++; }

		  if(current_csv_val >= 0.800) {
			nBJetMedium++;

			// for applying btagging SFs
			if (!isData && applyBtagSFs) {
			  float eff = getBtagEffFromFile(p4sCorrJets.at(iJet).pt(), p4sCorrJets.at(iJet).eta(), cms3.pfjets_hadronFlavour().at(iJet), isSMSScan);
			  BTagEntry::JetFlavor flavor = BTagEntry::FLAV_UDSG;
			  if (abs(cms3.pfjets_hadronFlavour().at(iJet)) == 5) flavor = BTagEntry::FLAV_B;
			  else if (abs(cms3.pfjets_hadronFlavour().at(iJet)) == 4) flavor = BTagEntry::FLAV_C;
			  float pt_cutoff = std::max(30.,std::min(669.,double(p4sCorrJets.at(iJet).pt())));
			  float eta_cutoff = std::min(2.39,fabs(double(p4sCorrJets.at(iJet).eta())));
			  float weight_cent(1.), weight_UP(1.), weight_DN(1.);
			  if (flavor == BTagEntry::FLAV_UDSG) {
				weight_cent = reader_light->eval(flavor, eta_cutoff, pt_cutoff);
				weight_UP = reader_light_UP->eval(flavor, eta_cutoff, pt_cutoff);
				weight_DN = reader_light_DN->eval(flavor, eta_cutoff, pt_cutoff);
			  } else {
				weight_cent = reader_heavy->eval(flavor, eta_cutoff, pt_cutoff);
				weight_UP = reader_heavy_UP->eval(flavor, eta_cutoff, pt_cutoff);
				weight_DN = reader_heavy_DN->eval(flavor, eta_cutoff, pt_cutoff);
			  }
			  // extra SF for fastsim
			  if (isSMSScan) {
				weight_cent *= reader_fastsim->eval(flavor, eta_cutoff, pt_cutoff);
				weight_UP *= reader_fastsim_UP->eval(flavor, eta_cutoff, pt_cutoff);
				weight_DN *= reader_fastsim_DN->eval(flavor, eta_cutoff, pt_cutoff);
			  }
			  btagprob_data *= weight_cent * eff;
			  btagprob_mc *= eff;
			  if (flavor == BTagEntry::FLAV_UDSG) {
				btagprob_light_UP *= weight_UP * eff;
				btagprob_light_DN *= weight_DN * eff;
				btagprob_heavy_UP *= weight_cent * eff;
				btagprob_heavy_DN *= weight_cent * eff;
			  } else {
				btagprob_light_UP *= weight_cent * eff;
				btagprob_light_DN *= weight_cent * eff;
				btagprob_heavy_UP *= weight_UP * eff;
				btagprob_heavy_DN *= weight_DN * eff;
			  }
			}
		  }else{ // fail btag
			
			if (!isData && applyBtagSFs) { // fail med btag -- needed for SF event weights
			  float eff = getBtagEffFromFile(p4sCorrJets.at(iJet).pt(), p4sCorrJets.at(iJet).eta(), cms3.pfjets_hadronFlavour().at(iJet), isSMSScan);
			  BTagEntry::JetFlavor flavor = BTagEntry::FLAV_UDSG;
			  if (abs(cms3.pfjets_hadronFlavour().at(iJet)) == 5) flavor = BTagEntry::FLAV_B;
			  else if (abs(cms3.pfjets_hadronFlavour().at(iJet)) == 4) flavor = BTagEntry::FLAV_C;
			  float pt_cutoff = std::max(30.,std::min(669.,double(p4sCorrJets.at(iJet).pt())));
			  float eta_cutoff = std::min(2.39,fabs(double(p4sCorrJets.at(iJet).eta())));
			  float weight_cent(1.), weight_UP(1.), weight_DN(1.);
			  if (flavor == BTagEntry::FLAV_UDSG) {
				weight_cent = reader_light->eval(flavor, eta_cutoff, pt_cutoff);
				weight_UP = reader_light_UP->eval(flavor, eta_cutoff, pt_cutoff);
				weight_DN = reader_light_DN->eval(flavor, eta_cutoff, pt_cutoff);
			  } else {
				weight_cent = reader_heavy->eval(flavor, eta_cutoff, pt_cutoff);
				weight_UP = reader_heavy_UP->eval(flavor, eta_cutoff, pt_cutoff);
				weight_DN = reader_heavy_DN->eval(flavor, eta_cutoff, pt_cutoff);
			  }
			  // extra SF for fastsim
			  if (isSMSScan) {
				weight_cent *= reader_fastsim->eval(flavor, eta_cutoff, pt_cutoff);
				weight_UP *= reader_fastsim_UP->eval(flavor, eta_cutoff, pt_cutoff);
				weight_DN *= reader_fastsim_DN->eval(flavor, eta_cutoff, pt_cutoff);
			  }
              btagprob_data *= (1. - weight_cent * eff);
              btagprob_mc *= (1. - eff);
			  if (flavor == BTagEntry::FLAV_UDSG) {
				btagprob_light_UP *= (1. - weight_UP * eff);
				btagprob_light_DN *= (1. - weight_DN * eff);
				btagprob_heavy_UP *= (1. - weight_cent * eff);
				btagprob_heavy_DN *= (1. - weight_cent * eff);
              } else {
				btagprob_light_UP *= (1. - weight_cent * eff);
				btagprob_light_DN *= (1. - weight_cent * eff);
				btagprob_heavy_UP *= (1. - weight_UP * eff);
				btagprob_heavy_DN *= (1. - weight_DN * eff);
              }
			}
		  }
		
		  if(current_csv_val >= 0.460) { nBJetLoose++; }

		  //require pT > 35 for jet counting
		  if( p4sCorrJets.at(iJet).pt() > 35.0 ){ njets++; }
		}

		if( verbose ) cout<<"Before filling jet up branches"<<endl;

		if(     (jet_corrfactor_up.at(iJet))*p4sCorrJets.at(iJet).pt()   > 25.0 &&
			abs((jet_corrfactor_up.at(iJet))*p4sCorrJets.at(iJet).eta()) < 2.4 ){
 		  jets_up_p4    .push_back((jet_corrfactor_up.at(iJet))*p4sCorrJets.at(iJet));

		  if( (jet_corrfactor_up.at(iJet))*p4sCorrJets.at(iJet).pt() > 35.0 ){ ht_up+=(jet_corrfactor_up.at(iJet))*p4sCorrJets.at(iJet).pt(); }
		  if(current_csv_val >= 0.935) { nBJetTight_up++; }
		  if(current_csv_val >= 0.800) { nBJetMedium_up++; }
		  if(current_csv_val >= 0.460) { nBJetLoose_up++; }
		  if( (jet_corrfactor_up.at(iJet))*p4sCorrJets.at(iJet).pt() > 35.0 ){ njets_up++; }
		}

		if( verbose ) cout<<"Before filling jet dn branches"<<endl;

		if( (jet_corrfactor_dn.at(iJet))*p4sCorrJets.at(iJet).pt() > 25.0 &&
			abs((jet_corrfactor_dn.at(iJet))*p4sCorrJets.at(iJet).eta()) < 2.4 ){
 		  jets_dn_p4    .push_back(p4sCorrJets.at(iJet)*jet_corrfactor_dn.at(iJet));
		  if( (jet_corrfactor_dn.at(iJet))*p4sCorrJets.at(iJet).pt() > 35.0 ){ ht_dn+=(jet_corrfactor_dn.at(iJet))*p4sCorrJets.at(iJet).pt(); }
		  if(current_csv_val >= 0.935) { nBJetTight_dn++; }
		  if(current_csv_val >= 0.800) { nBJetMedium_dn++; }
		  if(current_csv_val >= 0.460) { nBJetLoose_dn++; }
		  if( (jet_corrfactor_dn.at(iJet))*p4sCorrJets.at(iJet).pt() > 35.0 ){ njets_dn++; }
		}	  
      }

	  if (!isData) {
        weight_btagsf          = btagprob_data     / btagprob_mc;
		weight_btagsf_heavy_UP = btagprob_heavy_UP / btagprob_mc;
		weight_btagsf_heavy_DN = btagprob_heavy_DN / btagprob_mc;
		weight_btagsf_light_UP = btagprob_light_UP / btagprob_mc;
		weight_btagsf_light_DN = btagprob_light_DN / btagprob_mc;
	  }
	  
	  // //recalculate rawMET
	  pair<float,float> newMET = getT1CHSMET_fromMINIAOD(jet_corrector_pfL1FastJetL2L3, NULL, 0, true);
	  met_T1CHS_fromCORE_pt  = newMET.first;
	  met_T1CHS_fromCORE_phi = newMET.second;
	  
	  // met with no unc
	  pair <float, float> met_T1CHS_miniAOD_CORE_p2 = getT1CHSMET_fromMINIAOD(jet_corrector_pfL1FastJetL2L3);
	  met_T1CHS_miniAOD_CORE_pt  = met_T1CHS_miniAOD_CORE_p2.first;
	  met_T1CHS_miniAOD_CORE_phi = met_T1CHS_miniAOD_CORE_p2.second;

	  metsig_unofficial = met_T1CHS_miniAOD_CORE_pt / sqrt(ht);
	  
	  // met with up unc
	  pair <float, float> met_T1CHS_miniAOD_CORE_up_p2 = getT1CHSMET_fromMINIAOD(jet_corrector_pfL1FastJetL2L3, jecUnc, 1);
	  met_T1CHS_miniAOD_CORE_up_pt  = met_T1CHS_miniAOD_CORE_up_p2.first;
	  met_T1CHS_miniAOD_CORE_up_phi = met_T1CHS_miniAOD_CORE_up_p2.second;

	  metsig_unofficial = met_T1CHS_miniAOD_CORE_up_pt / sqrt(ht_up);

	  // met with dn unc
	  pair <float, float> met_T1CHS_miniAOD_CORE_dn_p2 = getT1CHSMET_fromMINIAOD(jet_corrector_pfL1FastJetL2L3, jecUnc, 0);
	  met_T1CHS_miniAOD_CORE_dn_pt  = met_T1CHS_miniAOD_CORE_dn_p2.first;
	  met_T1CHS_miniAOD_CORE_dn_phi = met_T1CHS_miniAOD_CORE_dn_p2.second;

	  metsig_unofficial = met_T1CHS_miniAOD_CORE_dn_pt / sqrt(ht_dn);

	  // add kinematic variables to do with jets leps and photons here
	  if( lep_p4.size() > 1 && evt_type != 2 ){
		// MT2J( MET_MAGNITUDE, MET_PHI, P4_LEPTON_1, P4_LEPTON_2, VECT_P4_Jets, MASS_INVISIBLE_PARTICLE, MT2_CALCULATION_METHOD )
		mt2  = -1.0;
		mt2j = -1.0;
		mt2b = -1.0;

		mt2 = MT2( met_T1CHS_miniAOD_CORE_pt, met_T1CHS_miniAOD_CORE_phi, lep_p4.at(0), lep_p4.at(1), 0.0 );
 	
 		if( jets_p4.size() > 1 ){
 		  mt2j = MT2J( met_T1CHS_miniAOD_CORE_pt, met_T1CHS_miniAOD_CORE_phi, lep_p4.at(0), lep_p4.at(1), jets_p4, 0.0 );
		}

		if( jets_medb_p4.size() > 1 ){
 		  mt2b = MT2J( met_T1CHS_miniAOD_CORE_pt, met_T1CHS_miniAOD_CORE_phi, lep_p4.at(0), lep_p4.at(1), jets_medb_p4, 0.0 );
		}		

		sum_mlb = get_sum_mlb();
		dphi_ll = acos(cos(lep_p4 .at(0).phi() - lep_p4 .at(1).phi()));
		
	  }

	  // lepton scale factors go here
	  if( !isData ){

		for( size_t lepind = 0; lepind < lep_p4.size(); lepind++ ){

		  float min_leppt  = min( 110.0, (double)lep_pt.at(lepind));
		  float abs_lepeta = abs(lep_eta.at(lepind));

		  if( abs(lep_pdgId.at(lepind)) == 11 ){			
			weightsf_lepreco .push_back( h_eleweights_reco->GetBinContent( h_eleweights_reco->FindBin( lep_eta.at(lepind), 100        )) ); // this is a 1d hist in 2 dimensions for some reason
			weightsf_lepid   .push_back( h_eleweights_id  ->GetBinContent( h_eleweights_id  ->FindBin( min_leppt         , abs_lepeta )) );
			weightsf_lepiso  .push_back( h_eleweightsiso  ->GetBinContent( h_eleweightsiso  ->FindBin( min_leppt         , abs_lepeta )) );			
			weightsf_lepip   .push_back( 1.0 );// ip weight already accounted for in id weight for electrons

			if( isSMSScan ){
			  weightsf_lepid_FS . push_back( h_eleweights->GetBinContent(h_eleweights->FindBin( min_leppt, abs_lepeta )) );

			}else{
			  weightsf_lepid_FS . push_back( 1.0 );
			}

			// ip and iso FS weights already accounted for in id weight for electrons
			weightsf_lepiso_FS. push_back( 1.0 );
			weightsf_lepip_FS . push_back( 1.0 );
			
		  }

		  if( abs(lep_pdgId.at(lepind)) == 13 ){			
			weightsf_lepreco .push_back( h_muoweights_HIP_hist->GetBinContent( h_muoweights_HIP_hist->FindBin( lep_eta  . at(lepind) )) );
			weightsf_lepid   .push_back( h_muoweights_id      ->GetBinContent( h_muoweights_id      ->FindBin( min_leppt, abs_lepeta )) );
			weightsf_lepiso  .push_back( h_muoweightsiso      ->GetBinContent( h_muoweightsiso      ->FindBin( min_leppt, abs_lepeta )) );			
			weightsf_lepip   .push_back( h_muoweights_ip      ->GetBinContent( h_muoweights_ip      ->FindBin( min_leppt, abs_lepeta )) );

			if( isSMSScan ){
			  weightsf_lepid_FS . push_back( h_muoweights       ->GetBinContent( h_muoweights       ->FindBin( min_leppt, abs_lepeta )) );
			  weightsf_lepiso_FS. push_back( h_muoweights_FS_iso->GetBinContent( h_muoweights_FS_iso->FindBin( min_leppt, abs_lepeta )) );
			  weightsf_lepip_FS . push_back( h_muoweights_FS_ip ->GetBinContent( h_muoweights_FS_ip ->FindBin( min_leppt, abs_lepeta )) );

			}else{
			  weightsf_lepid_FS . push_back( 1.0 );
			  weightsf_lepiso_FS. push_back( 1.0 );
			  weightsf_lepip_FS . push_back( 1.0 );
			}
		  }		 
		}		
	  }

	  
	  if( evt_type == 2 ){
		mt2 = decayedphoton_mt2;
	  }
	  
	  // add kinematic variables to do with ewk signal regions
	  if( jets_p4.size() > 1 ){
		mjj = (jets_p4.at(0) + jets_p4.at(1)).mass();
		dphi_jj = acos(cos(jets_p4.at(0).phi() - jets_p4.at(1).phi()));
		deta_jj = abs(jets_p4.at(0).eta() - jets_p4.at(1).eta());
		dR_jj   = sqrt(pow(deta_jj,2) + pow(dphi_jj,2));

		dphi_metj1 = acos(cos(jets_p4.at(0).phi() - met_T1CHS_miniAOD_CORE_phi));
		dphi_metj2 = acos(cos(jets_p4.at(1).phi() - met_T1CHS_miniAOD_CORE_phi));

		if( jets_medb_p4.size() > 1 ){
		  mbb_bpt = (jets_medb_p4.at(0) + jets_medb_p4.at(1)).mass();
		  mbb_csv = mbb_highest_csv( jets_p4, jets_csv );
		}	  
	  }

		
	  if( verbose ) cout<<" Before loop over pfcands " <<endl;
	  	  
	  LorentzVector chpfcands_0013_p4(0,0,0,0);
	  LorentzVector chpfcands_1316_p4(0,0,0,0);
	  LorentzVector chpfcands_1624_p4(0,0,0,0);
	  LorentzVector chpfcands_2430_p4(0,0,0,0);
	  LorentzVector chpfcands_30in_p4(0,0,0,0);
	  LorentzVector phpfcands_0013_p4(0,0,0,0);
	  LorentzVector phpfcands_1316_p4(0,0,0,0);
	  LorentzVector phpfcands_1624_p4(0,0,0,0);
	  LorentzVector phpfcands_2430_p4(0,0,0,0);
	  LorentzVector phpfcands_30in_p4(0,0,0,0);
	  LorentzVector nupfcands_0013_p4(0,0,0,0);
	  LorentzVector nupfcands_1316_p4(0,0,0,0);
	  LorentzVector nupfcands_1624_p4(0,0,0,0);
	  LorentzVector nupfcands_2430_p4(0,0,0,0);
	  LorentzVector nupfcands_30in_p4(0,0,0,0);

	  chpfcands_0013_sumet = 0.0;
	  chpfcands_1316_sumet = 0.0;
	  chpfcands_1624_sumet = 0.0;
	  chpfcands_2430_sumet = 0.0;
	  chpfcands_30in_sumet = 0.0;
	  phpfcands_0013_sumet = 0.0;
	  phpfcands_1316_sumet = 0.0;
	  phpfcands_1624_sumet = 0.0;
	  phpfcands_2430_sumet = 0.0;
	  phpfcands_30in_sumet = 0.0;
	  nupfcands_0013_sumet = 0.0;
	  nupfcands_1316_sumet = 0.0;
	  nupfcands_1624_sumet = 0.0;
	  nupfcands_2430_sumet = 0.0;
	  nupfcands_30in_sumet = 0.0;

	  nisoTrack_5gev = 0;
	  nisoTrack_mt2  = 0;

	  for( size_t pfind = 0; pfind < cms3.pfcands_p4().size(); pfind++ ){

		LorentzVector pfcand_p4 = cms3.pfcands_p4().at(pfind);
		
		if( abs(cms3.pfcands_charge().at(pfind)) > 0 ){ // charged cands
		  if(                               abs(pfcand_p4.eta()) < 1.3 ){ chpfcands_0013_p4 -= pfcand_p4; chpfcands_0013_sumet += pfcand_p4.pt(); }
		  if( abs(pfcand_p4.eta()) > 1.3 && abs(pfcand_p4.eta()) < 1.6 ){ chpfcands_1316_p4 -= pfcand_p4; chpfcands_1316_sumet += pfcand_p4.pt(); }
		  if( abs(pfcand_p4.eta()) > 1.6 && abs(pfcand_p4.eta()) < 2.4 ){ chpfcands_1624_p4 -= pfcand_p4; chpfcands_1624_sumet += pfcand_p4.pt(); }
		  if( abs(pfcand_p4.eta()) > 2.4 && abs(pfcand_p4.eta()) < 3.0 ){ chpfcands_2430_p4 -= pfcand_p4; chpfcands_2430_sumet += pfcand_p4.pt(); }
		  if( abs(pfcand_p4.eta()) > 3.0                               ){ chpfcands_30in_p4 -= pfcand_p4; chpfcands_30in_sumet += pfcand_p4.pt(); }
		}

		if( abs(cms3.pfcands_charge().at(pfind)) == 0 && abs(cms3.pfcands_particleId().at(pfind)) == 22 ){ // photon cands
		  if(                               abs(pfcand_p4.eta()) < 1.3 ){ phpfcands_0013_p4 -= pfcand_p4;  phpfcands_0013_sumet += pfcand_p4.pt(); }
		  if( abs(pfcand_p4.eta()) > 1.3 && abs(pfcand_p4.eta()) < 1.6 ){ phpfcands_1316_p4 -= pfcand_p4;  phpfcands_1316_sumet += pfcand_p4.pt(); }
		  if( abs(pfcand_p4.eta()) > 1.6 && abs(pfcand_p4.eta()) < 2.4 ){ phpfcands_1624_p4 -= pfcand_p4;  phpfcands_1624_sumet += pfcand_p4.pt(); }
		  if( abs(pfcand_p4.eta()) > 2.4 && abs(pfcand_p4.eta()) < 3.0 ){ phpfcands_2430_p4 -= pfcand_p4;  phpfcands_2430_sumet += pfcand_p4.pt(); }
		}

		if( abs(cms3.pfcands_charge().at(pfind)) == 0 && abs(cms3.pfcands_particleId().at(pfind)) != 22 ){ // neutral had cands
		  if(                               abs(pfcand_p4.eta()) < 1.3 ){ nupfcands_0013_p4 -= pfcand_p4; nupfcands_0013_sumet += pfcand_p4.pt(); }
		  if( abs(pfcand_p4.eta()) > 1.3 && abs(pfcand_p4.eta()) < 1.6 ){ nupfcands_1316_p4 -= pfcand_p4; nupfcands_1316_sumet += pfcand_p4.pt(); }
		  if( abs(pfcand_p4.eta()) > 1.6 && abs(pfcand_p4.eta()) < 2.4 ){ nupfcands_1624_p4 -= pfcand_p4; nupfcands_1624_sumet += pfcand_p4.pt(); }
		  if( abs(pfcand_p4.eta()) > 2.4 && abs(pfcand_p4.eta()) < 3.0 ){ nupfcands_2430_p4 -= pfcand_p4; nupfcands_2430_sumet += pfcand_p4.pt(); }
		}

		if( abs(pfcand_p4.eta()) > 3.0 && abs(cms3.pfcands_charge().at(pfind)) == 0 ){ // HF cands have different particle ID
		  if( abs(cms3.pfcands_particleId().at(pfind)) == 1 ){ nupfcands_30in_p4 -= pfcand_p4; nupfcands_30in_sumet += pfcand_p4.pt(); }
		  if( abs(cms3.pfcands_particleId().at(pfind)) == 2 ){ phpfcands_30in_p4 -= pfcand_p4; phpfcands_30in_sumet += pfcand_p4.pt(); }
		}


        if(      cms3.pfcands_charge().at(pfind)  == 0  ) continue;
        if( fabs(cms3.pfcands_dz()    .at(pfind)) >  0.1) continue;
        if(      cms3.pfcands_fromPV().at(pfind)  <= 1  ) continue;
 
        float cand_pt = cms3.pfcands_p4().at(pfind).pt();
        if(cand_pt < 5) continue;

        float absiso = TrackIso( pfind, 0.3, 0.0, true, false );
        if(  absiso >= min( 0.2 * cand_pt, 8.0 ) ) continue;

		// nuclear options for photon sample
		nisoTrack_5gev++;

		// isotrack a la MT2
        int  pdgId = abs( cms3.pfcands_particleId().at( pfind ) );

		bool leptonoverlaps = false;
		for( size_t lepind = 0; lepind < lep_p4.size(); lepind++ ){
		  if( sqrt( pow(cms3.pfcands_p4().at(pfind).eta() - lep_p4.at(lepind).eta(), 2) +
					pow(acos(cos(cms3.pfcands_p4().at(pfind).phi() - lep_p4.at(lepind).phi())), 2) ) < 0.01 ){
			leptonoverlaps = true;
		  }
		}

		if( leptonoverlaps ) continue;
		
		if( (cand_pt > 5.) && (pdgId == 11 || pdgId == 13) && (absiso/cand_pt < 0.2) ){
		  nisoTrack_mt2++;
		}
		
		if( cand_pt > 10. && pdgId == 211 && (absiso/cand_pt < 0.1 ) ){ 
		  nisoTrack_mt2++;
		}
		
	  }
	  
	  chpfcands_0013_pt = chpfcands_0013_p4.pt();
	  chpfcands_1316_pt = chpfcands_1316_p4.pt();
	  chpfcands_1624_pt = chpfcands_1624_p4.pt();
	  chpfcands_2430_pt = chpfcands_2430_p4.pt();
	  chpfcands_30in_pt = chpfcands_30in_p4.pt();
	  phpfcands_0013_pt = phpfcands_0013_p4.pt();
	  phpfcands_1316_pt = phpfcands_1316_p4.pt();
	  phpfcands_1624_pt = phpfcands_1624_p4.pt();
	  phpfcands_2430_pt = phpfcands_2430_p4.pt();
	  phpfcands_30in_pt = phpfcands_30in_p4.pt();
	  nupfcands_0013_pt = nupfcands_0013_p4.pt();
	  nupfcands_1316_pt = nupfcands_1316_p4.pt();
	  nupfcands_1624_pt = nupfcands_1624_p4.pt();
	  nupfcands_2430_pt = nupfcands_2430_p4.pt();
	  nupfcands_30in_pt = nupfcands_30in_p4.pt();

	  chpfcands_0013_phi = chpfcands_0013_p4.phi();
	  chpfcands_1316_phi = chpfcands_1316_p4.phi();
	  chpfcands_1624_phi = chpfcands_1624_p4.phi();
	  chpfcands_2430_phi = chpfcands_2430_p4.phi();
	  chpfcands_30in_phi = chpfcands_30in_p4.phi();
	  phpfcands_0013_phi = phpfcands_0013_p4.phi();
	  phpfcands_1316_phi = phpfcands_1316_p4.phi();
	  phpfcands_1624_phi = phpfcands_1624_p4.phi();
	  phpfcands_2430_phi = phpfcands_2430_p4.phi();
	  phpfcands_30in_phi = phpfcands_30in_p4.phi();
	  nupfcands_0013_phi = nupfcands_0013_p4.phi();
	  nupfcands_1316_phi = nupfcands_1316_p4.phi();
	  nupfcands_1624_phi = nupfcands_1624_p4.phi();
	  nupfcands_2430_phi = nupfcands_2430_p4.phi();
	  nupfcands_30in_phi = nupfcands_30in_p4.phi();	  

      FillBabyNtuple();

	}//end loop on events in a file
  
    delete tree;
    f.Close();
  }//end loop on files
  
  cout << "Processed " << nEventsTotal << " events" << endl;
  if ( nEventsChain != nEventsTotal ) {
    std::cout << "ERROR: number of events from files is not equal to total number of events" << std::endl;
  }

  cout << nDuplicates << " duplicate events were skipped." << endl;

  CloseBabyNtuple();

  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << " Events Processed" << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f s", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f s", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  // delete bmark;

  return;
}

void babyMaker::MakeBabyNtuple(const char *BabyFilename){

  //
  BabyFile_ = new TFile(Form("%s", BabyFilename), "RECREATE");
  BabyFile_->cd();
  BabyTree_ = new TTree("t", "A Baby Ntuple");

  BabyTree_->Branch("run"   , &run    );
  BabyTree_->Branch("lumi"  , &lumi   );
  BabyTree_->Branch("evt"   , &evt    );
  BabyTree_->Branch("isData", &isData );
  BabyTree_->Branch("evt_passgoodrunlist", &evt_passgoodrunlist);
  BabyTree_->Branch("evt_scale1fb", &evt_scale1fb);
  BabyTree_->Branch("evt_xsec", &evt_xsec );
  BabyTree_->Branch("evt_kfactor", &evt_kfactor );
  BabyTree_->Branch("evt_filter", &evt_filter );
  BabyTree_->Branch("evt_nEvts", &evt_nEvts );
  BabyTree_->Branch("puWeight", &puWeight );
  BabyTree_->Branch("nVert", &nVert );
  BabyTree_->Branch("nTrueInt", &nTrueInt );
  BabyTree_->Branch("rho", &rho );
  BabyTree_->Branch("rho25", &rho25 );

  BabyTree_->Branch("gen_ht", &gen_ht );

  BabyTree_->Branch("nBJetTight", &nBJetTight );
  BabyTree_->Branch("nBJetMedium", &nBJetMedium );
  BabyTree_->Branch("nBJetLoose", &nBJetLoose );

  BabyTree_->Branch("nBJetTight_up", &nBJetTight_up );
  BabyTree_->Branch("nBJetMedium_up", &nBJetMedium_up );
  BabyTree_->Branch("nBJetLoose_up", &nBJetLoose_up );

  BabyTree_->Branch("nBJetTight_dn", &nBJetTight_dn );
  BabyTree_->Branch("nBJetMedium_dn", &nBJetMedium_dn );
  BabyTree_->Branch("nBJetLoose_dn", &nBJetLoose_dn );

  BabyTree_->Branch("nMuons10", &nMuons10 );
  BabyTree_->Branch("nElectrons10", &nElectrons10 );
  BabyTree_->Branch("nGammas20", &nGammas20 );

  BabyTree_->Branch("met_pt"      , &met_pt       );
  BabyTree_->Branch("met_phi"     , &met_phi      );
  BabyTree_->Branch("met_calo_pt" , &met_calo_pt  );
  BabyTree_->Branch("met_calo_phi", &met_calo_phi );
  BabyTree_->Branch("met_rawPt"   , &met_rawPt    );
  BabyTree_->Branch("met_rawPhi"  , &met_rawPhi   );
  BabyTree_->Branch("met_genPt"   , &met_genPt    );
  BabyTree_->Branch("met_genPhi"  , &met_genPhi   );
  BabyTree_->Branch("sumet_raw"   , &sumet_raw    );
  
  //MET Filters
  BabyTree_->Branch("Flag_ecalLaserCorrFilter"   , &Flag_ecalLaserCorrFilter   );
  BabyTree_->Branch("Flag_hcalLaserEventFilter"  , &Flag_hcalLaserEventFilter  );
  BabyTree_->Branch("Flag_trackingFailureFilter" , &Flag_trackingFailureFilter );
  BabyTree_->Branch("Flag_CSCTightHaloFilter"    , &Flag_CSCTightHaloFilter    );

  // recommended from MET twiki
  BabyTree_->Branch("Flag_HBHENoiseFilter"                    , &Flag_HBHENoiseFilter                    );
  BabyTree_->Branch("Flag_HBHEIsoNoiseFilter"                 , &Flag_HBHEIsoNoiseFilter                 );
  BabyTree_->Branch("Flag_CSCTightHalo2015Filter"             , &Flag_CSCTightHalo2015Filter             );
  BabyTree_->Branch("Flag_EcalDeadCellTriggerPrimitiveFilter" , &Flag_EcalDeadCellTriggerPrimitiveFilter );
  BabyTree_->Branch("Flag_goodVertices"                       , &Flag_goodVertices                       );
  BabyTree_->Branch("Flag_eeBadScFilter"                      , &Flag_eeBadScFilter                      );
  BabyTree_->Branch("Flag_globalTightHalo2016"                , &Flag_globalTightHalo2016                );

  BabyTree_->Branch("Flag_badMuonFilter"                , &Flag_badMuonFilter             );
  BabyTree_->Branch("Flag_badChargedCandidateFilter"    , &Flag_badChargedCandidateFilter );
		
  //TRIGGER
  // for ATLAS cross checks
  BabyTree_->Branch("HLT_singleEl"       , &HLT_singleEl       );
  BabyTree_->Branch("HLT_singleMu"       , &HLT_singleMu       );
  BabyTree_->Branch("HLT_singleMu_noiso" , &HLT_singleMu_noiso );
					  
  // Double electron
  BabyTree_->Branch("HLT_DoubleEl_noiso" , &HLT_DoubleEl_noiso );
  BabyTree_->Branch("HLT_DoubleEl"       , &HLT_DoubleEl       ); // prescaled - turned off
  BabyTree_->Branch("HLT_DoubleEl_DZ"    , &HLT_DoubleEl_DZ    ); // prescaled
  BabyTree_->Branch("HLT_DoubleEl_DZ_2"  , &HLT_DoubleEl_DZ_2  ); // new
	  
  // electron-muon
  BabyTree_->Branch("HLT_MuEG"         , &HLT_MuEG         );
  BabyTree_->Branch("HLT_MuEG_2"       , &HLT_MuEG_2       );
  BabyTree_->Branch("HLT_MuEG_noiso"   , &HLT_MuEG_noiso   );

  BabyTree_->Branch("HLT_Mu8_EG17"     , &HLT_Mu8_EG17     );
  BabyTree_->Branch("HLT_Mu8_EG23"     , &HLT_Mu8_EG23     );
  BabyTree_->Branch("HLT_Mu8_EG23_DZ"  , &HLT_Mu8_EG23_DZ  );

  BabyTree_->Branch("HLT_Mu12_EG23_DZ" , &HLT_Mu12_EG23_DZ );

  BabyTree_->Branch("HLT_Mu17_EG12"    , &HLT_Mu17_EG12    );

  BabyTree_->Branch("HLT_Mu23_EG8"     , &HLT_Mu23_EG8     );
  BabyTree_->Branch("HLT_Mu23_EG8_DZ"  , &HLT_Mu23_EG8_DZ  );
  BabyTree_->Branch("HLT_Mu23_EG12"    , &HLT_Mu23_EG12    );
  BabyTree_->Branch("HLT_Mu23_EG12_DZ" , &HLT_Mu23_EG12_DZ );

  // Double electron
  BabyTree_->Branch("HLT_DoubleMu_noiso"    , &HLT_DoubleMu_noiso    );
  BabyTree_->Branch("HLT_DoubleMu"          , &HLT_DoubleMu          );
  BabyTree_->Branch("HLT_DoubleMu_tk"       , &HLT_DoubleMu_tk       );
  BabyTree_->Branch("HLT_DoubleMu_dbltk"    , &HLT_DoubleMu_dbltk    );
  BabyTree_->Branch("HLT_DoubleMu_nonDZ"    , &HLT_DoubleMu_nonDZ    );
  BabyTree_->Branch("HLT_DoubleMu_tk_nonDZ" , &HLT_DoubleMu_tk_nonDZ ); // new unprescaled : use these

  // Single photon
  BabyTree_->Branch("HLT_Photon22_R9Id90_HE10_IsoM"  , &HLT_Photon22_R9Id90_HE10_IsoM  );
  BabyTree_->Branch("HLT_Photon30_R9Id90_HE10_IsoM"  , &HLT_Photon30_R9Id90_HE10_IsoM  );
  BabyTree_->Branch("HLT_Photon36_R9Id90_HE10_IsoM"  , &HLT_Photon36_R9Id90_HE10_IsoM  );
  BabyTree_->Branch("HLT_Photon50_R9Id90_HE10_IsoM"  , &HLT_Photon50_R9Id90_HE10_IsoM  );
  BabyTree_->Branch("HLT_Photon75_R9Id90_HE10_IsoM"  , &HLT_Photon75_R9Id90_HE10_IsoM  );
  BabyTree_->Branch("HLT_Photon90_R9Id90_HE10_IsoM"  , &HLT_Photon90_R9Id90_HE10_IsoM  );
  BabyTree_->Branch("HLT_Photon120_R9Id90_HE10_IsoM" , &HLT_Photon120_R9Id90_HE10_IsoM );
  BabyTree_->Branch("HLT_Photon165_R9Id90_HE10_IsoM" , &HLT_Photon165_R9Id90_HE10_IsoM );
  BabyTree_->Branch("HLT_Photon165_HE10"             , &HLT_Photon165_HE10             );

  BabyTree_->Branch("HLT_CaloJet500_NoJetID" , &HLT_CaloJet500_NoJetID );
  BabyTree_->Branch("HLT_ECALHT800_NoJetID"  , &HLT_ECALHT800_NoJetID  );

  BabyTree_->Branch("HLT_Photon22_R9Id90_HE10_IsoM_matchedtophoton"  , &HLT_Photon22_R9Id90_HE10_IsoM_matchedtophoton  );
  BabyTree_->Branch("HLT_Photon30_R9Id90_HE10_IsoM_matchedtophoton"  , &HLT_Photon30_R9Id90_HE10_IsoM_matchedtophoton  );
  BabyTree_->Branch("HLT_Photon36_R9Id90_HE10_IsoM_matchedtophoton"  , &HLT_Photon36_R9Id90_HE10_IsoM_matchedtophoton  );
  BabyTree_->Branch("HLT_Photon50_R9Id90_HE10_IsoM_matchedtophoton"  , &HLT_Photon50_R9Id90_HE10_IsoM_matchedtophoton  );
  BabyTree_->Branch("HLT_Photon75_R9Id90_HE10_IsoM_matchedtophoton"  , &HLT_Photon75_R9Id90_HE10_IsoM_matchedtophoton  );
  BabyTree_->Branch("HLT_Photon90_R9Id90_HE10_IsoM_matchedtophoton"  , &HLT_Photon90_R9Id90_HE10_IsoM_matchedtophoton  );
  BabyTree_->Branch("HLT_Photon120_R9Id90_HE10_IsoM_matchedtophoton" , &HLT_Photon120_R9Id90_HE10_IsoM_matchedtophoton );
  BabyTree_->Branch("HLT_Photon165_R9Id90_HE10_IsoM_matchedtophoton" , &HLT_Photon165_R9Id90_HE10_IsoM_matchedtophoton );
  BabyTree_->Branch("HLT_Photon165_HE10_matchedtophoton"             , &HLT_Photon165_HE10_matchedtophoton             );

  BabyTree_->Branch("dilmass", &dilmass );
  BabyTree_->Branch("dilpt"  , &dilpt );
  BabyTree_->Branch("dRll"   , &dRll );

  BabyTree_->Branch("matched_neutralemf", &matched_neutralemf );
  BabyTree_->Branch("matched_emf"       , &matched_emf );
  BabyTree_->Branch("elveto", &elveto );

  BabyTree_->Branch("nlep"             , &nlep, "nlep/I" );
  BabyTree_->Branch("nveto_leptons"    , &nveto_leptons );
  BabyTree_->Branch("lep_p4"           , &lep_p4         );
  BabyTree_->Branch("lep_pt"           , "std::vector< Float_t >"       , &lep_pt         );
  BabyTree_->Branch("lep_eta"          , "std::vector< Float_t >"       , &lep_eta        );
  BabyTree_->Branch("lep_phi"          , "std::vector< Float_t >"       , &lep_phi        );
  BabyTree_->Branch("lep_mass"         , "std::vector< Float_t >"       , &lep_mass       );
  BabyTree_->Branch("lep_charge"       , "std::vector< Int_t >"         , &lep_charge     );
  BabyTree_->Branch("lep_pdgId"        , "std::vector< Int_t >"         , &lep_pdgId      );
  BabyTree_->Branch("lep_dxy"          , "std::vector< Float_t >"       , &lep_dxy        );
  BabyTree_->Branch("lep_etaSC"        , "std::vector< Float_t >"       , &lep_etaSC      );
  BabyTree_->Branch("lep_dz"           , "std::vector< Float_t >"       , &lep_dz         );
  BabyTree_->Branch("lep_tightId"      , "std::vector< Int_t >"         , &lep_tightId    );
  BabyTree_->Branch("lep_relIso03"     , "std::vector< Float_t >"       , &lep_relIso03   );
  BabyTree_->Branch("lep_relIso03MREA" , "std::vector< Float_t >"       , &lep_relIso03MREA   );
  BabyTree_->Branch("lep_relIso03MRDB" , "std::vector< Float_t >"       , &lep_relIso03MRDB   );
  BabyTree_->Branch("lep_relIso03MRNC" , "std::vector< Float_t >"       , &lep_relIso03MRNC   );
  BabyTree_->Branch("lep_relIso04"     , "std::vector< Float_t >"       , &lep_relIso04   );
  BabyTree_->Branch("lep_mcMatchId"    , "std::vector< Int_t >"         , &lep_mcMatchId  );
  BabyTree_->Branch("lep_lostHits"     , "std::vector< Int_t >"         , &lep_lostHits   );
  BabyTree_->Branch("lep_convVeto"     , "std::vector< Int_t >"         , &lep_convVeto   );
  BabyTree_->Branch("lep_tightCharge"  , "std::vector< Int_t >"         , &lep_tightCharge);
  BabyTree_->Branch("lep_MVA"          , "std::vector< Float_t >"       , &lep_MVA        );
  BabyTree_->Branch("lep_validfraction", &lep_validfraction );
  BabyTree_->Branch("lep_pterr"        , &lep_pterr         );
  BabyTree_->Branch("lep_sta_pterrOpt" , &lep_sta_pterrOpt  );
  BabyTree_->Branch("lep_glb_pterrOpt" , &lep_glb_pterrOpt  );
  // BabyTree_->Branch("lep_bft_pterrOpt" , &lep_bft_pterrOpt  );
  BabyTree_->Branch("lep_x2ondof"      , &lep_x2ondof       );
  BabyTree_->Branch("lep_sta_x2ondof"  , &lep_sta_x2ondof   );
  BabyTree_->Branch("lep_glb_x2ondof"  , &lep_glb_x2ondof   );
  // BabyTree_->Branch("lep_bft_x2ondof"  , &lep_bft_x2ondof   );

  BabyTree_->Branch("nisoTrack_5gev" , &nisoTrack_5gev );
  BabyTree_->Branch("nisoTrack_mt2"  , &nisoTrack_mt2  );

  BabyTree_->Branch("ngamma"             , &ngamma        , "ngamma/I" );
  BabyTree_->Branch("gamma_p4"           , &gamma_p4    );
  BabyTree_->Branch("gamma_pt"           , "std::vector <Float_t>" , &gamma_pt           );
  BabyTree_->Branch("gamma_eta"          , "std::vector <Float_t>" , &gamma_eta          );
  BabyTree_->Branch("gamma_phi"          , "std::vector <Float_t>" , &gamma_phi          );
  BabyTree_->Branch("gamma_mass"         , "std::vector <Float_t>" , &gamma_mass         );
  BabyTree_->Branch("gamma_mcMatchId"    , "std::vector <Int_t  >" , &gamma_mcMatchId    );
  BabyTree_->Branch("gamma_genIso"       , "std::vector <Float_t>" , &gamma_genIso       );
  BabyTree_->Branch("gamma_chHadIso"     , "std::vector <Float_t>" , &gamma_chHadIso     );
  BabyTree_->Branch("gamma_neuHadIso"    , "std::vector <Float_t>" , &gamma_neuHadIso    );
  BabyTree_->Branch("gamma_phIso"        , "std::vector <Float_t>" , &gamma_phIso        );
  BabyTree_->Branch("gamma_sigmaIetaIeta", "std::vector <Float_t>" , &gamma_sigmaIetaIeta);
  BabyTree_->Branch("gamma_r9"           , "std::vector <Float_t>" , &gamma_r9           );
  BabyTree_->Branch("gamma_hOverE"       , "std::vector <Float_t>" , &gamma_hOverE       );
  BabyTree_->Branch("gamma_idCutBased"   , "std::vector <Int_t  >" , &gamma_idCutBased   );
  BabyTree_->Branch("gamma_ecpfclusiso"  , &gamma_ecpfclusiso      );
  BabyTree_->Branch("gamma_hcpfclusiso"  , &gamma_hcpfclusiso      );
  BabyTree_->Branch("gamma_hollowtkiso03", &gamma_hollowtkiso03    );

  BabyTree_->Branch("ngenPart"         , &ngenPart        , "ngenPart/I" );
  BabyTree_->Branch("genPart_p4"       , &genPart_p4         );
  BabyTree_->Branch("genPart_pt"       , "std::vector <Float_t>" , &genPart_pt        );
  BabyTree_->Branch("genPart_eta"      , "std::vector <Float_t>" , &genPart_eta       );
  BabyTree_->Branch("genPart_phi"      , "std::vector <Float_t>" , &genPart_phi       );
  BabyTree_->Branch("genPart_mass"     , "std::vector <Float_t>" , &genPart_mass      );
  BabyTree_->Branch("genPart_pdgId"    , "std::vector <Int_t  >" , &genPart_pdgId     );
  BabyTree_->Branch("genPart_status"   , "std::vector <Int_t  >" , &genPart_status    );
  BabyTree_->Branch("genPart_charge"   , "std::vector <Float_t>" , &genPart_charge    );
  BabyTree_->Branch("genPart_motherId" , "std::vector <Int_t  >" , &genPart_motherId  );
  BabyTree_->Branch("genPart_grandmaId", "std::vector <Int_t  >" , &genPart_grandmaId );
  BabyTree_->Branch("genPart_isp6status3"  , "std::vector <Bool_t  >" , &genPart_isp6status3  );

  BabyTree_->Branch("ngenLep", &ngenLep, "ngenLep/I" );
  BabyTree_->Branch("genLep_pt"      , "std::vector <Float_t>" , &genLep_pt      );
  BabyTree_->Branch("genLep_eta"     , "std::vector <Float_t>" , &genLep_eta     );
  BabyTree_->Branch("genLep_phi"     , "std::vector <Float_t>" , &genLep_phi     );
  BabyTree_->Branch("genLep_mass"    , "std::vector <Float_t>" , &genLep_mass    );
  BabyTree_->Branch("genLep_pdgId"   , "std::vector <Int_t  >" , &genLep_pdgId   );
  BabyTree_->Branch("genLep_status"  , "std::vector <Int_t  >" , &genLep_status  );
  BabyTree_->Branch("genLep_charge"  , "std::vector <Float_t>" , &genLep_charge  );
  BabyTree_->Branch("genLep_sourceId", "std::vector <Int_t  >" , &genLep_sourceId);
  BabyTree_->Branch("genLep_isp6status3"  , "std::vector <Bool_t  >" , &genLep_isp6status3  );

  BabyTree_->Branch("ngenTau", &ngenTau, "ngenTau/I" );
  BabyTree_->Branch("genTau_pt"      , "std::vector <Float_t>" , &genTau_pt      );
  BabyTree_->Branch("genTau_eta"     , "std::vector <Float_t>" , &genTau_eta     );
  BabyTree_->Branch("genTau_phi"     , "std::vector <Float_t>" , &genTau_phi     );
  BabyTree_->Branch("genTau_mass"    , "std::vector <Float_t>" , &genTau_mass    );
  BabyTree_->Branch("genTau_pdgId"   , "std::vector <Int_t  >" , &genTau_pdgId   );
  BabyTree_->Branch("genTau_status"  , "std::vector <Int_t  >" , &genTau_status  );
  BabyTree_->Branch("genTau_charge"  , "std::vector <Float_t>" , &genTau_charge  );
  BabyTree_->Branch("genTau_sourceId", "std::vector <Int_t  >" , &genTau_sourceId);

  BabyTree_->Branch("ngenLepFromTau", &ngenLepFromTau, "ngenLepFromTau/I" );
  BabyTree_->Branch("genLepFromTau_pt"      , "std::vector <Float_t>" , &genLepFromTau_pt      );
  BabyTree_->Branch("genLepFromTau_eta"     , "std::vector <Float_t>" , &genLepFromTau_eta     );
  BabyTree_->Branch("genLepFromTau_phi"     , "std::vector <Float_t>" , &genLepFromTau_phi     );
  BabyTree_->Branch("genLepFromTau_mass"    , "std::vector <Float_t>" , &genLepFromTau_mass    );
  BabyTree_->Branch("genLepFromTau_pdgId"   , "std::vector <Int_t  >" , &genLepFromTau_pdgId   );
  BabyTree_->Branch("genLepFromTau_status"  , "std::vector <Int_t  >" , &genLepFromTau_status  );
  BabyTree_->Branch("genLepFromTau_charge"  , "std::vector <Float_t>" , &genLepFromTau_charge  );
  BabyTree_->Branch("genLepFromTau_sourceId", "std::vector <Int_t  >" , &genLepFromTau_sourceId);

//----- JETS - pt > 35, eta < 2.4
  BabyTree_->Branch("njets"           , &njets        );
  BabyTree_->Branch("njets_up"        , &njets_up     );
  BabyTree_->Branch("njets_dn"        , &njets_dn     );
  BabyTree_->Branch("jets_p4"         , &jets_p4      );
  BabyTree_->Branch("jets_medb_p4"    , &jets_medb_p4 );
  BabyTree_->Branch("jets_dn_p4"      , &jets_dn_p4   );
  BabyTree_->Branch("jets_up_p4"      , &jets_up_p4   );

  BabyTree_->Branch("jets_csv"          , &jets_csv          );
  BabyTree_->Branch("jets_mcFlavour"    , &jets_mcFlavour    );
  BabyTree_->Branch("jets_mcHadronFlav" , &jets_mcHadronFlav );

  BabyTree_->Branch("ht"    , &ht    );
  BabyTree_->Branch("ht_up" , &ht_up );
  BabyTree_->Branch("ht_dn" , &ht_dn );

  BabyTree_->Branch("metsig_unofficial"    , &metsig_unofficial    );
  BabyTree_->Branch("metsig_unofficial_up" , &metsig_unofficial_up );
  BabyTree_->Branch("metsig_unofficial_dn" , &metsig_unofficial_dn );

  BabyTree_->Branch("mt2" , &mt2  );
  BabyTree_->Branch("mt2j", &mt2j );
  BabyTree_->Branch("mt2b", &mt2b );

  BabyTree_->Branch("mjj"    , &mjj     );
  BabyTree_->Branch("mbb_csv", &mbb_csv );
  BabyTree_->Branch("mbb_bpt", &mbb_bpt );
  BabyTree_->Branch("dphi_jj", &dphi_jj );
  BabyTree_->Branch("dphi_ll", &dphi_ll );
  BabyTree_->Branch("sum_mlb" , &sum_mlb);
  BabyTree_->Branch("deta_jj", &deta_jj );
  BabyTree_->Branch("dR_jj"  , &dR_jj   );

  BabyTree_->Branch("dphi_metj1", &dphi_metj1 );
  BabyTree_->Branch("dphi_metj2", &dphi_metj2 );
  
  BabyTree_->Branch("weight_btagsf", &weight_btagsf );
  BabyTree_->Branch("weight_btagsf_heavy_UP", &weight_btagsf_heavy_UP );
  BabyTree_->Branch("weight_btagsf_light_UP", &weight_btagsf_light_UP );
  BabyTree_->Branch("weight_btagsf_heavy_DN", &weight_btagsf_heavy_DN );
  BabyTree_->Branch("weight_btagsf_light_DN", &weight_btagsf_light_DN );
   
  BabyTree_->Branch("chpfcands_0013_pt"     , &chpfcands_0013_pt   );
  BabyTree_->Branch("chpfcands_1316_pt"     , &chpfcands_1316_pt   );
  BabyTree_->Branch("chpfcands_1624_pt"     , &chpfcands_1624_pt   );
  BabyTree_->Branch("chpfcands_2430_pt"     , &chpfcands_2430_pt   );
  BabyTree_->Branch("chpfcands_30in_pt"     , &chpfcands_30in_pt   );
  BabyTree_->Branch("phpfcands_0013_pt"     , &phpfcands_0013_pt   );
  BabyTree_->Branch("phpfcands_1316_pt"     , &phpfcands_1316_pt   );
  BabyTree_->Branch("phpfcands_1624_pt"     , &phpfcands_1624_pt   );
  BabyTree_->Branch("phpfcands_2430_pt"     , &phpfcands_2430_pt   );
  BabyTree_->Branch("phpfcands_30in_pt"     , &phpfcands_30in_pt   );
  BabyTree_->Branch("nupfcands_0013_pt"     , &nupfcands_0013_pt   );
  BabyTree_->Branch("nupfcands_1316_pt"     , &nupfcands_1316_pt   );
  BabyTree_->Branch("nupfcands_1624_pt"     , &nupfcands_1624_pt   );
  BabyTree_->Branch("nupfcands_2430_pt"     , &nupfcands_2430_pt   );
  BabyTree_->Branch("nupfcands_30in_pt"     , &nupfcands_30in_pt   );
   
  BabyTree_->Branch("chpfcands_0013_sumet"     , &chpfcands_0013_sumet   );
  BabyTree_->Branch("chpfcands_1316_sumet"     , &chpfcands_1316_sumet   );
  BabyTree_->Branch("chpfcands_1624_sumet"     , &chpfcands_1624_sumet   );
  BabyTree_->Branch("chpfcands_2430_sumet"     , &chpfcands_2430_sumet   );
  BabyTree_->Branch("chpfcands_30in_sumet"     , &chpfcands_30in_sumet   );
  BabyTree_->Branch("phpfcands_0013_sumet"     , &phpfcands_0013_sumet   );
  BabyTree_->Branch("phpfcands_1316_sumet"     , &phpfcands_1316_sumet   );
  BabyTree_->Branch("phpfcands_1624_sumet"     , &phpfcands_1624_sumet   );
  BabyTree_->Branch("phpfcands_2430_sumet"     , &phpfcands_2430_sumet   );
  BabyTree_->Branch("phpfcands_30in_sumet"     , &phpfcands_30in_sumet   );
  BabyTree_->Branch("nupfcands_0013_sumet"     , &nupfcands_0013_sumet   );
  BabyTree_->Branch("nupfcands_1316_sumet"     , &nupfcands_1316_sumet   );
  BabyTree_->Branch("nupfcands_1624_sumet"     , &nupfcands_1624_sumet   );
  BabyTree_->Branch("nupfcands_2430_sumet"     , &nupfcands_2430_sumet   );
  BabyTree_->Branch("nupfcands_30in_sumet"     , &nupfcands_30in_sumet   );

  BabyTree_->Branch("chpfcands_0013_phi"     , &chpfcands_0013_phi   );
  BabyTree_->Branch("chpfcands_1316_phi"     , &chpfcands_1316_phi   );
  BabyTree_->Branch("chpfcands_1624_phi"     , &chpfcands_1624_phi   );
  BabyTree_->Branch("chpfcands_2430_phi"     , &chpfcands_2430_phi   );
  BabyTree_->Branch("chpfcands_30in_phi"     , &chpfcands_30in_phi   );
  BabyTree_->Branch("phpfcands_0013_phi"     , &phpfcands_0013_phi   );
  BabyTree_->Branch("phpfcands_1316_phi"     , &phpfcands_1316_phi   );
  BabyTree_->Branch("phpfcands_1624_phi"     , &phpfcands_1624_phi   );
  BabyTree_->Branch("phpfcands_2430_phi"     , &phpfcands_2430_phi   );
  BabyTree_->Branch("phpfcands_30in_phi"     , &phpfcands_30in_phi   );
  BabyTree_->Branch("nupfcands_0013_phi"     , &nupfcands_0013_phi   );
  BabyTree_->Branch("nupfcands_1316_phi"     , &nupfcands_1316_phi   );
  BabyTree_->Branch("nupfcands_1624_phi"     , &nupfcands_1624_phi   );
  BabyTree_->Branch("nupfcands_2430_phi"     , &nupfcands_2430_phi   );
  BabyTree_->Branch("nupfcands_30in_phi"     , &nupfcands_30in_phi   );

  BabyTree_->Branch("met_T1CHS_pt"               , &met_T1CHS_pt               );
  BabyTree_->Branch("met_T1CHS_phi"              , &met_T1CHS_phi              );
  BabyTree_->Branch("met_T1CHS_fromCORE_pt"      , &met_T1CHS_fromCORE_pt      );
  BabyTree_->Branch("met_T1CHS_fromCORE_phi"     , &met_T1CHS_fromCORE_phi     );

  BabyTree_->Branch("met_T1CHS_miniAOD_CORE_pt"      , &met_T1CHS_miniAOD_CORE_pt      );
  BabyTree_->Branch("met_T1CHS_miniAOD_CORE_phi"     , &met_T1CHS_miniAOD_CORE_phi     );
  BabyTree_->Branch("met_T1CHS_miniAOD_CORE_up_pt"      , &met_T1CHS_miniAOD_CORE_up_pt      );
  BabyTree_->Branch("met_T1CHS_miniAOD_CORE_up_phi"     , &met_T1CHS_miniAOD_CORE_up_phi     );
  BabyTree_->Branch("met_T1CHS_miniAOD_CORE_dn_pt"      , &met_T1CHS_miniAOD_CORE_dn_pt      );
  BabyTree_->Branch("met_T1CHS_miniAOD_CORE_dn_phi"     , &met_T1CHS_miniAOD_CORE_dn_phi     );

  BabyTree_->Branch("decayedphoton_lep1_p4", &decayedphoton_lep1_p4 );
  BabyTree_->Branch("decayedphoton_lep2_p4", &decayedphoton_lep2_p4 );
  BabyTree_->Branch("decayedphoton_bosn_p4", &decayedphoton_bosn_p4 );
  BabyTree_->Branch("decayedphoton_mt2"    , &decayedphoton_mt2     );
  
  BabyTree_->Branch("hyp_type", &hyp_type);
  BabyTree_->Branch("evt_type", &evt_type);

  BabyTree_->Branch("mass_gluino", &mass_gluino);
  BabyTree_->Branch("mass_LSP"   , &mass_LSP   );

  BabyTree_->Branch("isrboost"   , &isrboost   );
  BabyTree_->Branch("isr_njets"  , &isr_njets  );
  BabyTree_->Branch("isr_weight" , &isr_weight );
  BabyTree_->Branch("isr_unc"    , &isr_unc    );

  BabyTree_->Branch("weightsf_lepid"    , &weightsf_lepid     );
  BabyTree_->Branch("weightsf_lepiso"   , &weightsf_lepiso    );
  BabyTree_->Branch("weightsf_lepip"    , &weightsf_lepip     );
  BabyTree_->Branch("weightsf_lepreco"  , &weightsf_lepreco   );
  BabyTree_->Branch("weightsf_lepid_FS" , &weightsf_lepid_FS  );
  BabyTree_->Branch("weightsf_lepiso_FS", &weightsf_lepiso_FS );
  BabyTree_->Branch("weightsf_lepip_FS" , &weightsf_lepip_FS  );

  return;
}

void babyMaker::InitBabyNtuple () {

  run    = -999;
  lumi   = -999;
  evt    = -1;
  isData = -999;
  evt_passgoodrunlist = 1;
  evt_scale1fb = 0;
  evt_xsec = -999.0;
  evt_kfactor = -999.0;
  evt_filter = -999.0;
  evt_nEvts = 0;
  //evt_id = -1; // don't reset every event
  puWeight = -999.0;
  nVert = -999;
  nTrueInt = -999;
  rho = -999.0;
  rho25 = -999.0;
  nBJetTight = -999;
  nBJetMedium = -999;
  nBJetLoose = -999;

  nBJetTight_up = -999;
  nBJetMedium_up = -999;
  nBJetLoose_up = -999;

  nBJetTight_dn = -999;
  nBJetMedium_dn = -999;
  nBJetLoose_dn = -999;

  nMuons10 = -999;
  nElectrons10 = -999;
  nGammas20 = -999;

  gen_ht = -999.0;

  met_pt       = -999.0;
  met_phi      = -999.0;
  met_calo_pt  = -999.0;
  met_calo_phi = -999.0;
  met_rawPt    = -999.0;
  met_rawPhi   = -999.0;
  met_genPt    = -999.0;
  met_genPhi   = -999.0;

  sumet_raw = -999.0;

  //MET Filters
  Flag_ecalLaserCorrFilter   = -999;
  Flag_hcalLaserEventFilter  = -999;
  Flag_trackingFailureFilter = -999;
  Flag_CSCTightHaloFilter    = -999;

  // recommended from MET twiki
  Flag_HBHENoiseFilter                    = -999;
  Flag_HBHEIsoNoiseFilter                 = -999;
  Flag_CSCTightHalo2015Filter             = -999;
  Flag_EcalDeadCellTriggerPrimitiveFilter = -999;
  Flag_goodVertices                       = -999;
  Flag_eeBadScFilter                      = -999;

  Flag_badMuonFilter              = -999;
  Flag_badChargedCandidateFilter  = -999;
  Flag_globalTightHalo2016        = -999;

  //TRIGGER
  // for ATLAS cross checks
  HLT_singleEl       = -999;
  HLT_singleMu       = -999;
  HLT_singleMu_noiso = -999;
					  
  // Double electron
  HLT_DoubleEl_noiso = -999;
  HLT_DoubleEl       = -999; // prescaled - turned off
  HLT_DoubleEl_DZ    = -999; // prescaled
  HLT_DoubleEl_DZ_2  = -999; // new
	  
  // electron-muon
  HLT_MuEG         = -999;
  HLT_MuEG_2       = -999;
  HLT_MuEG_noiso   = -999;

  HLT_Mu8_EG17     = -999;
  HLT_Mu8_EG23     = -999;
  HLT_Mu8_EG23_DZ  = -999;

  HLT_Mu12_EG23_DZ = -999;

  HLT_Mu17_EG12    = -999;

  HLT_Mu23_EG8     = -999;
  HLT_Mu23_EG8_DZ  = -999;
  HLT_Mu23_EG12    = -999;
  HLT_Mu23_EG12_DZ = -999;

  // Double electron
  HLT_DoubleMu_noiso    = -999;
  HLT_DoubleMu          = -999;
  HLT_DoubleMu_tk       = -999;
  HLT_DoubleMu_dbltk    = -999;
  HLT_DoubleMu_nonDZ    = -999;
  HLT_DoubleMu_tk_nonDZ = -999; // new unprescaled : use these

  // Single photon
  HLT_Photon22_R9Id90_HE10_IsoM  = -999;
  HLT_Photon30_R9Id90_HE10_IsoM  = -999;
  HLT_Photon36_R9Id90_HE10_IsoM  = -999;
  HLT_Photon50_R9Id90_HE10_IsoM  = -999;
  HLT_Photon75_R9Id90_HE10_IsoM  = -999;
  HLT_Photon90_R9Id90_HE10_IsoM  = -999;
  HLT_Photon120_R9Id90_HE10_IsoM = -999;
  HLT_Photon165_R9Id90_HE10_IsoM = -999;
  HLT_Photon165_HE10             = -999;

  HLT_CaloJet500_NoJetID = -999;
  HLT_ECALHT800_NoJetID  = -999;
  
  HLT_Photon22_R9Id90_HE10_IsoM_matchedtophoton  = 0;
  HLT_Photon30_R9Id90_HE10_IsoM_matchedtophoton  = 0;
  HLT_Photon36_R9Id90_HE10_IsoM_matchedtophoton  = 0;
  HLT_Photon50_R9Id90_HE10_IsoM_matchedtophoton  = 0;
  HLT_Photon75_R9Id90_HE10_IsoM_matchedtophoton  = 0;
  HLT_Photon90_R9Id90_HE10_IsoM_matchedtophoton  = 0;
  HLT_Photon120_R9Id90_HE10_IsoM_matchedtophoton = 0;
  HLT_Photon165_R9Id90_HE10_IsoM_matchedtophoton = 0;
  HLT_Photon165_HE10_matchedtophoton             = 0;

  dilmass = -999;
  dilpt   = -999;
  dRll    = -999;
 
  matched_neutralemf = -999.0;
  matched_emf = -999.0;
  elveto = false;  
 
  hyp_type = -999;
  evt_type = -999;
  
  nlep = -999;
  nveto_leptons = -999;
  lep_p4            .clear();
  lep_pt            .clear();
  lep_eta           .clear();
  lep_phi           .clear();
  lep_mass          .clear();
  lep_charge        .clear();
  lep_pdgId         .clear();
  lep_dxy           .clear();
  lep_etaSC         .clear();
  lep_dz            .clear();
  lep_tightId       .clear();
  lep_relIso03      .clear();
  lep_relIso03MREA  .clear();
  lep_relIso03MRDB  .clear();
  lep_relIso03MRNC  .clear();
  lep_relIso04      .clear();
  lep_mcMatchId     .clear();
  lep_lostHits      .clear();
  lep_convVeto      .clear();
  lep_tightCharge   .clear();
  lep_MVA           .clear();
  lep_validfraction .clear();
  lep_pterr         .clear();
  lep_sta_pterrOpt  .clear();
  lep_glb_pterrOpt  .clear();
  // lep_bft_pterrOpt  .clear();
  lep_x2ondof       .clear();
  lep_sta_x2ondof   .clear();
  lep_glb_x2ondof   .clear();
  // lep_bft_x2ondof   .clear();

  
  nisoTrack_5gev = -1;
  nisoTrack_mt2  = -1;

  ngamma = -999;
  gamma_p4           .clear();   //[ngamma]
  gamma_pt           .clear();   //[ngamma]
  gamma_eta          .clear();   //[ngamma]
  gamma_phi          .clear();   //[ngamma]
  gamma_mass         .clear();   //[ngamma]
  gamma_mcMatchId    .clear();   //[ngamma]
  gamma_genIso       .clear();   //[ngamma]
  gamma_chHadIso     .clear();   //[ngamma]
  gamma_neuHadIso    .clear();   //[ngamma]
  gamma_phIso        .clear();   //[ngamma]
  gamma_sigmaIetaIeta.clear();   //[ngamma]
  gamma_r9           .clear();   //[ngamma]
  gamma_hOverE       .clear();   //[ngamma]
  gamma_idCutBased   .clear();   //[ngamma]
  gamma_ecpfclusiso  .clear();
  gamma_hcpfclusiso  .clear();
  gamma_hollowtkiso03.clear();

  ngenPart = -999;
  ngen_p6s3Part = -999;
  genPart_p4         .clear();   //[ngenPart]
  genPart_pt         .clear();   //[ngenPart]
  genPart_eta        .clear();   //[ngenPart]
  genPart_phi        .clear();   //[ngenPart]
  genPart_mass       .clear();   //[ngenPart]
  genPart_pdgId      .clear();   //[ngenPart]
  genPart_isp6status3.clear();   //[ngenPart]
  genPart_status     .clear();   //[ngenPart]
  genPart_charge     .clear();   //[ngenPart]
  genPart_motherId   .clear();   //[ngenPart]
  genPart_grandmaId  .clear();   //[ngenPart]

  ngenLep = -999;
  ngen_p6s3Lep = -999;
  genLep_pt         .clear();   //[ngenLep]
  genLep_eta        .clear();   //[ngenLep]
  genLep_phi        .clear();   //[ngenLep]
  genLep_mass       .clear();   //[ngenLep]
  genLep_pdgId      .clear();   //[ngenLep]
  genLep_status     .clear();   //[ngenLep]
  genLep_isp6status3.clear();   //[ngenLep]
  genLep_charge     .clear();   //[ngenLep]
  genLep_sourceId   .clear();   //[ngenLep]

  ngenTau = -999;
  genTau_pt      .clear();   //[ngenTau]
  genTau_eta     .clear();   //[ngenTau]
  genTau_phi     .clear();   //[ngenTau]
  genTau_mass    .clear();   //[ngenTau]
  genTau_pdgId   .clear();   //[ngenTau]
  genTau_status  .clear();   //[ngenTau]
  genTau_charge  .clear();   //[ngenTau]
  genTau_sourceId.clear();   //[ngenTau]

  ngenLepFromTau = -999;
  genLepFromTau_pt      .clear();   //[ngenLepFromTau]
  genLepFromTau_eta     .clear();   //[ngenLepFromTau]
  genLepFromTau_phi     .clear();   //[ngenLepFromTau]
  genLepFromTau_mass    .clear();   //[ngenLepFromTau]
  genLepFromTau_pdgId   .clear();   //[ngenLepFromTau]
  genLepFromTau_status  .clear();   //[ngenLepFromTau]
  genLepFromTau_charge  .clear();   //[ngenLepFromTau]
  genLepFromTau_sourceId.clear();   //[ngenLepFromTau]
  
//----- JETS - pt > 35, eta < 2.4
  njets    = -999.0;
  njets_up = -999.0;
  njets_dn = -999.0;

  jets_p4            .clear();
  jets_medb_p4       .clear();
  jets_dn_p4         .clear();
  jets_up_p4         .clear();
  jets_csv           .clear();
  jets_mcFlavour     .clear();
  jets_mcHadronFlav  .clear();

  ht       = -999.0;
  ht_up    = -999.0;
  ht_dn    = -999.0;

  metsig_unofficial       = -999.0;
  metsig_unofficial_up    = -999.0;
  metsig_unofficial_dn    = -999.0;

  mt2      = -999.0;
  mt2j     = -999.0;
  mt2b     = -999.0;

  mjj      = -999.0;
  mbb_csv  = -999.0;
  mbb_bpt  = -999.0;
  dphi_jj  = -999.0;
  sum_mlb  = -999.0;
  dphi_ll  = -999.0;
  deta_jj  = -999.0;
  dR_jj    = -999.0;
  
  dphi_metj1  = -999.0;
  dphi_metj2  = -999.0;

  
  //----- pfMETs
  chpfcands_0013_pt = -999;
  chpfcands_1316_pt = -999;
  chpfcands_1624_pt = -999;
  chpfcands_2430_pt = -999;
  chpfcands_30in_pt = -999;
  phpfcands_0013_pt = -999;
  phpfcands_1316_pt = -999;
  phpfcands_1624_pt = -999;
  phpfcands_2430_pt = -999;
  phpfcands_30in_pt = -999;
  nupfcands_0013_pt = -999;
  nupfcands_1316_pt = -999;
  nupfcands_1624_pt = -999;
  nupfcands_2430_pt = -999;
  nupfcands_30in_pt = -999;

  chpfcands_0013_phi = -999;
  chpfcands_1316_phi = -999;
  chpfcands_1624_phi = -999;
  chpfcands_2430_phi = -999;
  chpfcands_30in_phi = -999;
  phpfcands_0013_phi = -999;
  phpfcands_1316_phi = -999;
  phpfcands_1624_phi = -999;
  phpfcands_2430_phi = -999;
  phpfcands_30in_phi = -999;
  nupfcands_0013_phi = -999;
  nupfcands_1316_phi = -999;
  nupfcands_1624_phi = -999;
  nupfcands_2430_phi = -999;
  nupfcands_30in_phi = -999;

  //----- pfsumETs
  chpfcands_0013_sumet = -999;
  chpfcands_1316_sumet = -999;
  chpfcands_1624_sumet = -999;
  chpfcands_2430_sumet = -999;
  chpfcands_30in_sumet = -999;
  phpfcands_0013_sumet = -999;
  phpfcands_1316_sumet = -999;
  phpfcands_1624_sumet = -999;
  phpfcands_2430_sumet = -999;
  phpfcands_30in_sumet = -999;
  nupfcands_0013_sumet = -999;
  nupfcands_1316_sumet = -999;
  nupfcands_1624_sumet = -999;
  nupfcands_2430_sumet = -999;
  nupfcands_30in_sumet = -999;

  weight_btagsf = 1.;
  weight_btagsf_heavy_UP = 1.;
  weight_btagsf_light_UP = 1.;
  weight_btagsf_heavy_DN = 1.;
  weight_btagsf_light_DN = 1.;

  met_T1CHS_pt                  = -999;
  met_T1CHS_phi                 = -999;
  met_T1CHS_fromCORE_pt         = -999;
  met_T1CHS_fromCORE_phi        = -999;
  met_T1CHS_miniAOD_CORE_pt     = -999;
  met_T1CHS_miniAOD_CORE_phi    = -999;
  met_T1CHS_miniAOD_CORE_up_pt  = -999;
  met_T1CHS_miniAOD_CORE_up_phi = -999;
  met_T1CHS_miniAOD_CORE_dn_pt  = -999;
  met_T1CHS_miniAOD_CORE_dn_phi = -999;

  decayedphoton_lep1_p4 = LorentzVector(0,0,0,0);
  decayedphoton_lep2_p4 = LorentzVector(0,0,0,0);
  decayedphoton_bosn_p4 = LorentzVector(0,0,0,0);
  decayedphoton_mt2     = -999.9;

  mass_gluino = -999;
  mass_LSP    = -999;
  
  isrboost    = -999;
  isr_njets   = -999;
  isr_weight  = -999.9;
  isr_unc     = -999.9;

  weightsf_lepid     . clear();
  weightsf_lepiso    . clear();
  weightsf_lepip     . clear();
  weightsf_lepreco   . clear();
  weightsf_lepid_FS  . clear();
  weightsf_lepiso_FS . clear();
  weightsf_lepip_FS  . clear();

  return;
}

void babyMaker::FillBabyNtuple(){
  BabyTree_->Fill();
  return;
}

void babyMaker::CloseBabyNtuple(){
  BabyFile_->cd();
  BabyTree_->Write();
  BabyFile_->Close();
  return;
}

float babyMaker::getBtagEffFromFile(float pt, float eta, int mcFlavour, bool isFastsim){
  if(!h_btag_eff_b || !h_btag_eff_c || !h_btag_eff_udsg) {
	std::cout << "babyMaker::getBtagEffFromFile: ERROR: missing input hists" << std::endl;
	return 1.;
  }

  if(isFastsim && (!h_btag_eff_b_fastsim || !h_btag_eff_c_fastsim || !h_btag_eff_udsg_fastsim)) {
	std::cout << "babyMaker::getBtagEffFromFile: ERROR: missing input hists" << std::endl;
	return 1.;
  }

  // only use pt bins up to 400 GeV for charm and udsg
  float pt_cutoff = std::max(20.,std::min(399.,double(pt)));
  TH2D* h(0);
  if (abs(mcFlavour) == 5) {
	h = isFastsim ? h_btag_eff_b_fastsim : h_btag_eff_b;
	// use pt bins up to 600 GeV for b
	pt_cutoff = std::max(20.,std::min(599.,double(pt)));
  }
  else if (abs(mcFlavour) == 4) {
	h = isFastsim ? h_btag_eff_c_fastsim : h_btag_eff_c;
  }
  else {
	h = isFastsim ? h_btag_eff_udsg_fastsim : h_btag_eff_udsg;
  }
    
  int binx = h->GetXaxis()->FindBin(pt_cutoff);
  int biny = h->GetYaxis()->FindBin(fabs(eta));
  return h->GetBinContent(binx,biny);
}

// get sum Mlb for NLL
float babyMaker::get_sum_mlb()
{
  float min_mlb_1 = 10000.;
  float min_mlb_2 = 10000.;

  float mlb_temp_1 = min_mlb_1;
  float mlb_temp_2 = min_mlb_2;

  int jet_tempind_1 = -1;
  int jet_tempind_2 = -1;

  if (jets_medb_p4.size() > 1) {

	// Find lowest Mlb for lep 1
	for( size_t jetind = 0; jetind < jets_medb_p4.size(); jetind++ ){ // loop over jets
	  mlb_temp_1 = (lep_p4.at(0) + jets_medb_p4.at(jetind)).M();      // store mlb1 temp
	  if(mlb_temp_1 < min_mlb_1){                                     // find min val
		min_mlb_1 = mlb_temp_1;
		jet_tempind_1 = jetind;                                       // find min val index
	  }
	}

    mlb_temp_2 = (lep_p4.at(1) + jets_medb_p4.at(jet_tempind_1)).M();
	if( mlb_temp_2 < mlb_temp_1 ){ // mlb2 is smaller, gotta search again

	  min_mlb_2 = mlb_temp_2;
	  jet_tempind_2 = jet_tempind_1;
	  
	  min_mlb_1 = 10000.;
	  // Find lowest Mlb for lep 1 again
	  for( size_t jetind = 0; jetind < jets_medb_p4.size(); jetind++ ){
		if( jetind == (size_t)jet_tempind_2 ) continue;
		mlb_temp_1 = (lep_p4.at(0) + jets_medb_p4.at(jetind)).M();
		if(mlb_temp_1 < min_mlb_1){
		  min_mlb_1 = mlb_temp_1;
		  jet_tempind_1 = jetind;
		}
	  }

	}

	else{ // mlb1 is smaller, we are fine

	  // Find lowest Mlb for lep 2
	  for( size_t jetind = 0; jetind < jets_medb_p4.size(); jetind++ ){
		if( jetind == (size_t)jet_tempind_1 ) continue;
		mlb_temp_2 = (lep_p4.at(1) + jets_medb_p4.at(jetind)).M();
		if(mlb_temp_2 < min_mlb_2){
		  min_mlb_2 = mlb_temp_2;
		  jet_tempind_2 = jetind;
		}
	  }
	}
	
  }else if(jets_medb_p4.size() == 1 && jets_p4.size() > 1){
	mlb_temp_1 = (lep_p4.at(0) + jets_medb_p4.at(0)).M();      // store mlb1 temp
	mlb_temp_2 = (lep_p4.at(1) + jets_medb_p4.at(0)).M();      // store mlb2 temp

	mlb_temp_1 < mlb_temp_2 ? min_mlb_1 = mlb_temp_1 : min_mlb_2 = mlb_temp_2;

	if( mlb_temp_1 < mlb_temp_2 ){

	  // Find lowest Mlb for lep 2
	  for( size_t jetind = 0; jetind < jets_p4.size(); jetind++ ){
		if( jets_csv.at(jetind) > 0.800 ) continue; // don't double count b-jets
		mlb_temp_2 = (lep_p4.at(1) + jets_p4.at(jetind)).M();
		if(mlb_temp_2 < min_mlb_2){
		  min_mlb_2 = mlb_temp_2;
		}
	  }
	}else{

	  // Find lowest Mlb for lep 1
	  for( size_t jetind = 0; jetind < jets_p4.size(); jetind++ ){
		if( jets_csv.at(jetind) > 0.800 ) continue; // don't double count b-jets
		mlb_temp_1 = (lep_p4.at(0) + jets_p4.at(jetind)).M();
		if(mlb_temp_1 < min_mlb_1){
		  min_mlb_1 = mlb_temp_1;
		}
	  }
	}
	
  }else if(jets_medb_p4.size() < 1 && jets_p4.size() > 1){

	// Find lowest Mlb for lep 1
	for( size_t jetind = 0; jetind < jets_p4.size(); jetind++ ){ // loop over jets
	  mlb_temp_1 = (lep_p4.at(0) + jets_p4.at(jetind)).M();      // store mlb1 temp
	  if(mlb_temp_1 < min_mlb_1){                                     // find min val
		min_mlb_1 = mlb_temp_1;
		jet_tempind_1 = jetind;                                       // find min val index
	  }
	}

	mlb_temp_2 = (lep_p4.at(1) + jets_p4.at(jet_tempind_1)).M();
	if( mlb_temp_2 < mlb_temp_1 ){ // mlb2 is smaller, gotta search again

	  min_mlb_2 = mlb_temp_2;
	  jet_tempind_2 = jet_tempind_1;
	  
	  min_mlb_1 = 10000.;
	  // Find lowest Mlb for lep 1 again
	  for( size_t jetind = 0; jetind < jets_p4.size(); jetind++ ){
		if( jetind == (size_t)jet_tempind_2 ) continue;
		mlb_temp_1 = (lep_p4.at(0) + jets_p4.at(jetind)).M();
		if(mlb_temp_1 < min_mlb_1){
		  min_mlb_1 = mlb_temp_1;
		  jet_tempind_1 = jetind;
		}
	  }

	}else{ // mlb1 is smaller, we are fine

	  // Find lowest Mlb for lep 2
	  for( size_t jetind = 0; jetind < jets_p4.size(); jetind++ ){
		if( jetind == (size_t)jet_tempind_1 ) continue;
		mlb_temp_2 = (lep_p4.at(1) + jets_p4.at(jetind)).M();
		if(mlb_temp_2 < min_mlb_2){
		  min_mlb_2 = mlb_temp_2;
		  jet_tempind_2 = jetind;
		}
	  }
	}	
	
	// cout<<"mlb1: "<<min_mlb_1<<endl;
	// cout<<"mlb2: "<<min_mlb_2<<endl;		
	
  }else if( jets_p4.size() < 2 ){

	min_mlb_1 = 0.0;
	min_mlb_2 = 0.0;

  }

  return min_mlb_1 + min_mlb_2; 
}

void babyMaker::load_leptonSF_files()
{

  cout<<"Loading Lepton Scale Factors..."<<endl;
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
  TFile * f_sfweights = NULL;
  
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

  // SFs muons for FS to Fullsim, ip
  f_sfweights  = TFile::Open("leptonSFs/FS/sf_mu_tightIP2D.root","READ");
  h_muoweights_FS_ip = (TH2D*)f_sfweights->Get("histo2D") -> Clone("h_muoweights_FS_ip");
  h_muoweights_FS_ip->SetDirectory(rootdir);
  f_sfweights->Close();
  
  return;
}
