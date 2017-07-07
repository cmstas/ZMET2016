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
#include "../CORE/SSSelections.h"
#include "../CORE/VVVSelections.h"
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
// for testing purposes, running on unmerged files (default false)
const bool removePostProcVars = false;

const double JET_PT_MIN = 20;
const double JET_ETA_MAX = 5;

const double BJET_PT_MIN = 20;
const double BJET_ETA_MAX = 2.4;

const double BJET_CSV_TIGHT = 0.9535;
const double BJET_CSV_MED = 0.8484;
const double BJET_CSV_LOOSE = 0.5426;



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

void babyMaker::ScanChain(TChain* chain, std::string baby_name, int max_events){

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  cout<<"Creating MVA input for electrons."<<endl;
  // createAndInitMVA("MVAinput", true); // for electrons
  createAndInitMVA("MVAinput", true, false, 80); // for electrons

  // SimPa class for simulating photon decay
  SimPa simpa;

  MakeBabyNtuple( Form("%s.root", baby_name.c_str()) );

  load_leptonSF_files();
	
  // do this once per job
  const char* json_file = "Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON_snt.txt"; // 26p4 fb
  cout<<"Setting grl: "<<json_file<<endl;
  set_goodrun_file(json_file);

  if( TString(baby_name).Contains("t5zz") || TString(baby_name).Contains("tchiwz") || TString(baby_name).Contains("tchihz") || TString(baby_name).Contains("tchizz") || TString(baby_name).Contains("signal") ) isSMSScan = true;
  
  if (applyBtagSFs) {
	// setup btag calibration readers
	calib           = new BTagCalibration("csvv2", "btagsf/CSVv2_Moriond17_B_H.csv"); // Moriond17 version of SFs
	reader_heavy    = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "central"); // central
	reader_heavy_UP = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "up"     ); // sys up
	reader_heavy_DN = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "down"   ); // sys down
	reader_light    = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "incl", "central"); // central
	reader_light_UP = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "incl", "up"     ); // sys up
	reader_light_DN = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "incl", "down"   ); // sys down

	// get btag efficiencies
	TFile * f_btag_eff           = new TFile("btagsf/btageff__ttbar_powheg_pythia8_25ns_Moriond17.root");
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
	  calib_fastsim     = new BTagCalibration("CSV", "btagsf/fastsim_csvv2_ttbar_26_1_2017.csv"); // Moriond 17 25ns fastsim version of SFs
	  reader_fastsim    = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "central"); // central
	  reader_fastsim_UP = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "up"     ); // sys up
	  reader_fastsim_DN = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "down"   ); // sys down

	  // get btag efficiencies
	  TFile * f_btag_eff_fastsim           = new TFile("btagsf/btageff__SMS-T1bbbb-T1qqqq_25ns_Moriond17.root");
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

  h_neventsinfile = new TH1I( "h_neventsinfile", "", 1, 0, 1 );
  
  //add 2016 data vtx weights for PU, Moriond 2017 version
  TH1F * h_vtxweight = NULL;
  TFile * f_vtx = NULL;
  f_vtx = TFile::Open("puWeight2016.root","READ");
  h_vtxweight = (TH1F*)f_vtx->Get("pileupWeight")->Clone("h_vtxweight");
  h_vtxweight->SetDirectory(rootdir);
  f_vtx->Close();
  
  //cout<<__LINE__<<endl;

  TH1F * h_susyxsecs  = NULL;
  TFile * f_susyxsecs = NULL;

  TH2F * h_eventcounts  = NULL;
  TH1D * h_eventcounts_1d  = NULL;
  TFile * f_eventcounts = NULL;

  if (isSMSScan) {

	cout<<"issmsscan"<<endl;
	
	f_susyxsecs = TFile::Open("xsec_susy_13tev.root","READ");
	if( TString(baby_name).Contains("t5zz")   ) h_susyxsecs = (TH1F*)f_susyxsecs->Get("h_xsec_gluino")->Clone("h_susyxsecs");
	else if( TString(baby_name).Contains("tchiwz") ) h_susyxsecs = (TH1F*)f_susyxsecs->Get("h_xsec_c1n2"  )->Clone("h_susyxsecs");
	else if( TString(baby_name).Contains("tchihz") || TString(baby_name).Contains("tchizz") ) h_susyxsecs = (TH1F*)f_susyxsecs->Get("h_xsec_higgsino"  )->Clone("h_susyxsecs");

	h_susyxsecs->SetDirectory(rootdir);
	f_susyxsecs->Close();

	if( TString(baby_name).Contains("tchiwz") ) f_eventcounts = TFile::Open("TChiWZ_ZToLL_entries.root","READ");
	else if( TString(baby_name).Contains("t5zz"  ) ) f_eventcounts = TFile::Open("T5ZZ_entries.root"               ,"READ");
	else if( TString(baby_name).Contains("tchihz") ) f_eventcounts = TFile::Open("TChiHZ_HToBB_ZToLL_entries.root" ,"READ");
	else if( TString(baby_name).Contains("tchizz") ) f_eventcounts = TFile::Open("TChiZZ_ZToLL_entries.root","READ");

	if(TString(baby_name).Contains("tchihz") || TString(baby_name).Contains("tchizz")) {
		h_eventcounts_1d = (TH1D*)f_eventcounts->Get("h_entries")->Clone("h_eventcounts");
		h_eventcounts_1d->SetDirectory(rootdir);
	}
	else{
		h_eventcounts = (TH2F*)f_eventcounts->Get("h_entries")->Clone("h_eventcounts");	
		h_eventcounts->SetDirectory(rootdir);
	}

	h_eventcounts = (TH2F*)f_eventcounts->Get("h_entries")->Clone("h_eventcounts");

	h_eventcounts->SetDirectory(rootdir);
	f_eventcounts->Close();
  }
  //cout<<__LINE__<<endl;
  
  // File Loop
  int nDuplicates = 0;
  int nEvents = chain->GetEntries();
  unsigned int nEventsChain = nEvents;
  cout << "Running on " << nEventsChain << " events" << endl;
  unsigned int nEventsTotal = 0;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  h_neventsinfile->SetBinContent(0, nEvents);
	
  while ( (currentFile = (TFile*)fileIter.Next()) ) {
    cout << "running on file: " << currentFile->GetTitle() << endl;

    // evt_id = sampleID(currentFile->GetTitle());
    TString currentFileName(currentFile->GetTitle());

    // Get File Content
    TFile f( currentFile->GetTitle() );
    TTree *tree = (TTree*)f.Get("Events");
    TTreeCache::SetLearnEntries(10);
    tree->SetCacheSize(128*1024*1024);
    cms3.Init(tree);

    // ----------------------------------
    // retrieve JEC from files, if using
    // ----------------------------------

    // stores current corrections for a given event
    FactorizedJetCorrector   * jet_corrector_pfL1FastJetL2L3_current = NULL;
    JetCorrectionUncertainty * jecUnc_current                        = NULL;

    // default corrections     
    std::vector<std::string> jetcorr_filenames_pfL1FastJetL2L3;
    FactorizedJetCorrector   * jet_corrector_pfL1FastJetL2L3 = NULL;
    JetCorrectionUncertainty * jecUnc                        = NULL;

    // corrections for later runs in 2016F
    std::vector<std::string> jetcorr_filenames_pfL1FastJetL2L3_postrun278802;
    FactorizedJetCorrector   * jet_corrector_pfL1FastJetL2L3_postrun278802 = NULL;
    JetCorrectionUncertainty * jecUnc_postrun278802                        = NULL;
	
    if (applyJECfromFile) {
      jetcorr_filenames_pfL1FastJetL2L3.clear();

  	  //JECs for 76X
  	  if( currentFileName.Contains("16Dec2015") || currentFileName.Contains("76X_mcRun2") ){
    		if( currentFileName.Contains("Run2015C") || currentFileName.Contains("Run2015D") ){
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
  	  else if( currentFileName.Contains("80MiniAODv") || currentFileName.Contains("RelVal") ){
  		  // files for 80X MC, ICHEP production
    		jetcorr_filenames_pfL1FastJetL2L3.clear();
    		jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/MC/Spring16_25nsV1_MC_L1FastJet_AK4PFchs.txt"   );
    		jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/MC/Spring16_25nsV1_MC_L2Relative_AK4PFchs.txt"  );
    		jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/MC/Spring16_25nsV1_MC_L3Absolute_AK4PFchs.txt"  );
    		jecUnc = new JetCorrectionUncertainty        ("jetCorrections/source_80X/MC/Spring16_25nsV1_MC_Uncertainty_AK4PFchs.txt" );
  	  } 		
  	  else if( currentFileName.Contains("Summer16") || currentFileName.Contains("TEST") ){
    		// files for 80X MC, Summer16 (Moriond17) production
    		jetcorr_filenames_pfL1FastJetL2L3.clear();
    		jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/MC/Summer16_23Sep2016V3_MC_L1FastJet_AK4PFchs.txt"   );
    		jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/MC/Summer16_23Sep2016V3_MC_L2Relative_AK4PFchs.txt"  );
    		jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/MC/Summer16_23Sep2016V3_MC_L3Absolute_AK4PFchs.txt"  );
    		jecUnc = new JetCorrectionUncertainty        ("jetCorrections/source_80X/MC/Summer16_23Sep2016V3_MC_Uncertainty_AK4PFchs.txt" );
  	  }
  	  else if( currentFileName.Contains("Run2016") || currentFileName.Contains("CMSSW_8_0_11_V08-00-06") ){
    		// 	jetcorr_filenames_pfL1FastJetL2L3.clear();
    		// 	jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Spring16_25nsV6_DATA_L1FastJet_AK4PFchs.txt"   );
    		// 	jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Spring16_25nsV6_DATA_L2Relative_AK4PFchs.txt"  );
    		// 	jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Spring16_25nsV6_DATA_L3Absolute_AK4PFchs.txt"  );
    		// 	jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Spring16_25nsV6_DATA_L2L3Residual_AK4PFchs.txt");
    		// 	jecUnc = new JetCorrectionUncertainty        ("jetCorrections/source_80X/DATA/Spring16_25nsV6_DATA_Uncertainty_AK4PFchs.txt" );

    		// 	jetcorr_filenames_pfL1FastJetL2L3_postrun278802.clear();
    		// 	jetcorr_filenames_pfL1FastJetL2L3_postrun278802.push_back  ("jetCorrections/source_80X/DATA/Spring16_25nsV6_DATA_L1FastJet_AK4PFchs.txt"   );
    		// 	jetcorr_filenames_pfL1FastJetL2L3_postrun278802.push_back  ("jetCorrections/source_80X/DATA/Spring16_25nsV6_DATA_L2Relative_AK4PFchs.txt"  );
    		// 	jetcorr_filenames_pfL1FastJetL2L3_postrun278802.push_back  ("jetCorrections/source_80X/DATA/Spring16_25nsV6_DATA_L3Absolute_AK4PFchs.txt"  );
    		// 	jetcorr_filenames_pfL1FastJetL2L3_postrun278802.push_back  ("jetCorrections/source_80X/DATA/Spring16_25nsV6_DATA_L2L3Residual_AK4PFchs.txt");
    		// 	jecUnc_postrun278802 = new JetCorrectionUncertainty        ("jetCorrections/source_80X/DATA/Spring16_25nsV6_DATA_Uncertainty_AK4PFchs.txt" );
    		// 	jet_corrector_pfL1FastJetL2L3_postrun278802  = makeJetCorrector(jetcorr_filenames_pfL1FastJetL2L3_postrun278802);

    		// // This scheme will eventually be used for Moriond. For now just use JECs from ICHEP
    		if( currentFileName.Contains("Run2016B") ||
    			currentFileName.Contains("Run2016C") ||
    			currentFileName.Contains("Run2016D") ){
    		  // files for 80X Data
    		  jetcorr_filenames_pfL1FastJetL2L3.clear();
    		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016BCDV3_DATA_L1FastJet_AK4PFchs.txt"   );
    		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016BCDV3_DATA_L2Relative_AK4PFchs.txt"  );
    		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016BCDV3_DATA_L3Absolute_AK4PFchs.txt"  );
    		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016BCDV3_DATA_L2L3Residual_AK4PFchs.txt");
    		  jecUnc = new JetCorrectionUncertainty        ("jetCorrections/source_80X/DATA/Summer16_23Sep2016BCDV3_DATA_Uncertainty_AK4PFchs.txt" );
    		}

    		if( currentFileName.Contains("Run2016E") ||
    			currentFileName.Contains("Run2016F") ){
    		  // files for 80X Data
    		  jetcorr_filenames_pfL1FastJetL2L3.clear();
    		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016EFV3_DATA_L1FastJet_AK4PFchs.txt"   );
    		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016EFV3_DATA_L2Relative_AK4PFchs.txt"  );
    		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016EFV3_DATA_L3Absolute_AK4PFchs.txt"  );
    		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016EFV3_DATA_L2L3Residual_AK4PFchs.txt");
    		  jecUnc = new JetCorrectionUncertainty        ("jetCorrections/source_80X/DATA/Summer16_23Sep2016EFV3_DATA_Uncertainty_AK4PFchs.txt" );

    		  jetcorr_filenames_pfL1FastJetL2L3_postrun278802.clear();
    		  jetcorr_filenames_pfL1FastJetL2L3_postrun278802.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016GV3_DATA_L1FastJet_AK4PFchs.txt"   );
    		  jetcorr_filenames_pfL1FastJetL2L3_postrun278802.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016GV3_DATA_L2Relative_AK4PFchs.txt"  );
    		  jetcorr_filenames_pfL1FastJetL2L3_postrun278802.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016GV3_DATA_L3Absolute_AK4PFchs.txt"  );
    		  jetcorr_filenames_pfL1FastJetL2L3_postrun278802.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016GV3_DATA_L2L3Residual_AK4PFchs.txt");
    		  jecUnc_postrun278802 = new JetCorrectionUncertainty        ("jetCorrections/source_80X/DATA/Summer16_23Sep2016GV3_DATA_Uncertainty_AK4PFchs.txt" );
    		  jet_corrector_pfL1FastJetL2L3_postrun278802  = makeJetCorrector(jetcorr_filenames_pfL1FastJetL2L3_postrun278802);
    		}

    		if( currentFileName.Contains("Run2016G") ){
    		  // files for 80X Data
    		  jetcorr_filenames_pfL1FastJetL2L3.clear();
    		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016GV3_DATA_L1FastJet_AK4PFchs.txt"   );
    		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016GV3_DATA_L2Relative_AK4PFchs.txt"  );
    		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016GV3_DATA_L3Absolute_AK4PFchs.txt"  );
    		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016GV3_DATA_L2L3Residual_AK4PFchs.txt");
    		  jecUnc = new JetCorrectionUncertainty        ("jetCorrections/source_80X/DATA/Summer16_23Sep2016GV3_DATA_Uncertainty_AK4PFchs.txt" );

    		  jetcorr_filenames_pfL1FastJetL2L3_postrun278802.clear();
    		  jetcorr_filenames_pfL1FastJetL2L3_postrun278802.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016GV3_DATA_L1FastJet_AK4PFchs.txt"   );
    		  jetcorr_filenames_pfL1FastJetL2L3_postrun278802.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016GV3_DATA_L2Relative_AK4PFchs.txt"  );
    		  jetcorr_filenames_pfL1FastJetL2L3_postrun278802.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016GV3_DATA_L3Absolute_AK4PFchs.txt"  );
    		  jetcorr_filenames_pfL1FastJetL2L3_postrun278802.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016GV3_DATA_L2L3Residual_AK4PFchs.txt");
    		  jecUnc_postrun278802 = new JetCorrectionUncertainty        ("jetCorrections/source_80X/DATA/Summer16_23Sep2016GV3_DATA_Uncertainty_AK4PFchs.txt" );
    		  jet_corrector_pfL1FastJetL2L3_postrun278802  = makeJetCorrector(jetcorr_filenames_pfL1FastJetL2L3_postrun278802);
    		}

    		if( currentFileName.Contains("Run2016H") ){
    		  jetcorr_filenames_pfL1FastJetL2L3.clear();
    		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016HV3_DATA_L1FastJet_AK4PFchs.txt"   );
    		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016HV3_DATA_L2Relative_AK4PFchs.txt"  );
    		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016HV3_DATA_L3Absolute_AK4PFchs.txt"  );
    		  jetcorr_filenames_pfL1FastJetL2L3.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016HV3_DATA_L2L3Residual_AK4PFchs.txt");
    		  jecUnc = new JetCorrectionUncertainty        ("jetCorrections/source_80X/DATA/Summer16_23Sep2016HV3_DATA_Uncertainty_AK4PFchs.txt" );

    		  jetcorr_filenames_pfL1FastJetL2L3_postrun278802.clear();
    		  jetcorr_filenames_pfL1FastJetL2L3_postrun278802.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016HV3_DATA_L1FastJet_AK4PFchs.txt"   );
    		  jetcorr_filenames_pfL1FastJetL2L3_postrun278802.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016HV3_DATA_L2Relative_AK4PFchs.txt"  );
    		  jetcorr_filenames_pfL1FastJetL2L3_postrun278802.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016HV3_DATA_L3Absolute_AK4PFchs.txt"  );
    		  jetcorr_filenames_pfL1FastJetL2L3_postrun278802.push_back  ("jetCorrections/source_80X/DATA/Summer16_23Sep2016HV3_DATA_L2L3Residual_AK4PFchs.txt");
    		  jecUnc_postrun278802 = new JetCorrectionUncertainty        ("jetCorrections/source_80X/DATA/Summer16_23Sep2016HV3_DATA_Uncertainty_AK4PFchs.txt" );
    		  jet_corrector_pfL1FastJetL2L3_postrun278802  = makeJetCorrector(jetcorr_filenames_pfL1FastJetL2L3_postrun278802);
    		}
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

  	  cout<<"JECs used:"<<endl;
  	  for( size_t jecind = 0; jecind < jetcorr_filenames_pfL1FastJetL2L3.size(); jecind++ ){
  		  cout<<jetcorr_filenames_pfL1FastJetL2L3.at(jecind)<<endl;
  	  }
  	  
  	  jet_corrector_pfL1FastJetL2L3  = makeJetCorrector(jetcorr_filenames_pfL1FastJetL2L3);
    }

    //cout<<__LINE__<<endl;

    // Event Loop
    unsigned int nEventsToLoop = tree->GetEntriesFast();
    if (max_events > 0) nEventsToLoop = (unsigned int) max_events;
    
    //===============================
    // LOOP OVER EVENTS IN FILE
    //===============================
    for( unsigned int event = 0; event < nEventsToLoop; ++event) {
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
      if (cms3.evt_dataset().size() > 0) evt_dataset.push_back(cms3.evt_dataset().at(0));

      //cout<<__LINE__<<endl;

      //if ( (!(run==1 && evt==4924476 && lumi==35685)) /*&& (!(run==1 && evt==1535469 && lumi==7737)) && (!(run==1 && evt==1990371 && lumi==10030))*/ ) continue;

      // set random seed on first event of each input file for SimPa
      if (event == 0) simpa.SetSeed(evt);

      // set jet corrector based on run number for data
      if (isData && run >= 278802 && run <= 278808) {
        jet_corrector_pfL1FastJetL2L3_current = jet_corrector_pfL1FastJetL2L3_postrun278802;
        jecUnc_current = jecUnc_postrun278802;
      } 
      else {
        jet_corrector_pfL1FastJetL2L3_current = jet_corrector_pfL1FastJetL2L3;
        jecUnc_current = jecUnc;
      }

      //cout<<__LINE__<<endl;
      if (!removePostProcVars) {
        evt_kfactor  = cms3.evt_kfactor();
        evt_filter   = cms3.evt_filt_eff();
      }

      // get CMS3 version number to use later
      TString cms3_version = cms3.evt_CMS3tag().at(0);
      // convert last two digits of version number to int
      int small_cms3_version = TString(cms3_version(cms3_version.Length()-2,cms3_version.Length())).Atoi();
      bool recent_cms3_version = true;
      if (cms3_version.Contains("V08-00") && small_cms3_version <= 12) recent_cms3_version = false;
      
      //cout<<__LINE__<<endl;

  	  if( isSMSScan ){
  		if (currentFileName.Contains("SMS-TChiHZ") || currentFileName.Contains("SMS-TChiZZ")){
  		  mass_chi = cms3.sparm_values().at(0);
  		  evt_nEvts    = h_eventcounts_1d->GetBinContent(h_eventcounts_1d->FindBin(mass_chi));
  		}
  		else{
  		  mass_gluino = cms3.sparm_values().at(0);
  		  mass_LSP    = cms3.sparm_values().at(1);
  		  evt_nEvts    = h_eventcounts->GetBinContent(h_eventcounts->FindBin(mass_gluino,mass_LSP));
  		}

  		std::vector<int> produced_particles;

  		if( currentFileName.Contains("SMS-T5ZZ"  ) ) {
  		  evt_xsec = h_susyxsecs->GetBinContent(h_susyxsecs->FindBin(mass_gluino))*(0.19175);// BF for at least 1 Z to two leps
  		  produced_particles.push_back(1000021); // gluino
  		}
  		else if( currentFileName.Contains("SMS-TChiWZ") ) {
  		  evt_xsec = h_susyxsecs->GetBinContent(h_susyxsecs->FindBin(mass_gluino))*(0.100974);// BF for Z to two leps
  		  produced_particles.push_back(1000024); // chargino1
  		  produced_particles.push_back(1000023); // neutralino2
  		}
  		else if( currentFileName.Contains("SMS-TChiHZ") ) {
  		  evt_xsec = h_susyxsecs->GetBinContent(h_susyxsecs->FindBin(mass_chi))*(0.100974*0.5824);// BF for Z to two leps * BF for Higgs to bb.
  		  produced_particles.push_back(1000023); // neutralino2
  		  produced_particles.push_back(1000025); // neutralino3
  		}		  
  		else if( currentFileName.Contains("SMS-TChiZZ") ) {
  		  evt_xsec = h_susyxsecs->GetBinContent(h_susyxsecs->FindBin(mass_chi))*(0.19175);// BF for at least 1 Z to two leps
  		  produced_particles.push_back(1000023); // neutralino2
  		  produced_particles.push_back(1000025); // neutralino3
  		}

  		evt_scale1fb = evt_xsec*1000/evt_nEvts;

  		LorentzVector isrSystem_p4;
  		for( size_t genind = 0; genind < cms3.genps_p4().size(); genind++ ){
  		  if( cms3.genps_isLastCopy().at(genind) != 1) continue;
  		  for (unsigned int ipart = 0; ipart < produced_particles.size(); ++ipart) {
  		    if (abs(cms3.genps_id().at(genind)) == produced_particles.at(ipart)) {
  		      isrSystem_p4 += cms3.genps_p4().at(genind);
  		      break;
  		    }
  		  } // loop over produced susy particles 
  		} // loop over cms3 genps

  		isrboost = (isrSystem_p4).pt();
  		
  	  }
  	  else if (!removePostProcVars) {
    		evt_nEvts    = cms3.evt_nEvts();
    		evt_scale1fb = cms3.evt_scale1fb();
    		evt_xsec     = cms3.evt_xsec_incl();
  	  }
  	  
  	  puWeight     = 1.0;
  	  if( !isData ){
  	  	nTrueInt = cms3.puInfo_trueNumInteractions().at(0);
  		  puWeight = h_vtxweight->GetBinContent(h_vtxweight->FindBin(nTrueInt));
  	  }
      rho = cms3.evt_fixgridfastjet_all_rho(); //this one is used in JECs

      if (verbose) cout << "before vertices" << endl;

      //cout<<__LINE__<<endl;

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
      met_miniaod_pt  = cms3.evt_pfmet();
      met_miniaod_phi = cms3.evt_pfmetPhi();
      if (isData && small_cms3_version >= 18) {
      	met_muegclean_pt  = cms3.evt_muegclean_pfmet();
      	met_muegclean_phi = cms3.evt_muegclean_pfmetPhi();
      }
      met_genPt    = cms3.gen_met();
      met_genPhi   = cms3.gen_metPhi();
      met_rawPt    = cms3.evt_pfmet_raw();
      met_rawPhi   = cms3.evt_pfmetPhi_raw();
      sumet_raw    = cms3.evt_pfsumet_raw();

      // //recalculate rawMET
      pair<float,float> newMET = getT1CHSMET_fromMINIAOD(jet_corrector_pfL1FastJetL2L3_current, NULL, 0, true);
      met_T1CHS_fromCORE_pt  = newMET.first;
      met_T1CHS_fromCORE_phi = newMET.second;
    
      // met with no unc
      pair <float, float> met_T1CHS_miniAOD_CORE_p2 = getT1CHSMET_fromMINIAOD(jet_corrector_pfL1FastJetL2L3_current);
      met_T1CHS_miniAOD_CORE_pt  = met_T1CHS_miniAOD_CORE_p2.first;
      met_T1CHS_miniAOD_CORE_phi = met_T1CHS_miniAOD_CORE_p2.second;

      // choose default value of MET to use for analysis, set as met_pt, met_phi
      if (isData && small_cms3_version >= 18) 
      { // for re-MINIAOD data
      	met_pt = met_muegclean_pt;
      	met_phi = met_muegclean_phi;
      } 
      else {
      	met_pt = met_T1CHS_miniAOD_CORE_pt;
      	met_phi = met_T1CHS_miniAOD_CORE_phi;
      }
    
      // met with up unc
      pair <float, float> met_T1CHS_miniAOD_CORE_up_p2 = getT1CHSMET_fromMINIAOD(jet_corrector_pfL1FastJetL2L3_current, jecUnc_current, 1);
      met_T1CHS_miniAOD_CORE_up_pt  = met_T1CHS_miniAOD_CORE_up_p2.first;
      met_T1CHS_miniAOD_CORE_up_phi = met_T1CHS_miniAOD_CORE_up_p2.second;

      // met with dn unc
      pair <float, float> met_T1CHS_miniAOD_CORE_dn_p2 = getT1CHSMET_fromMINIAOD(jet_corrector_pfL1FastJetL2L3_current, jecUnc_current, 0);
      met_T1CHS_miniAOD_CORE_dn_pt  = met_T1CHS_miniAOD_CORE_dn_p2.first;
      met_T1CHS_miniAOD_CORE_dn_phi = met_T1CHS_miniAOD_CORE_dn_p2.second;

      metsig_unofficial = met_pt / sqrt(ht); // == met_T1CHS_miniAOD_CORE_pt in MC, where we do variations
      metsig_unofficial_up = met_T1CHS_miniAOD_CORE_up_pt / sqrt(ht_up);
      metsig_unofficial_dn = met_T1CHS_miniAOD_CORE_dn_pt / sqrt(ht_dn);
       	  
      //cout<<__LINE__<<endl;

      // MET FILTERS
  	  if( isData ){
  		Flag_ecalLaserCorrFilter                = cms3.filt_ecalLaser();
  		Flag_hcalLaserEventFilter               = cms3.filt_hcalLaser();
  		Flag_trackingFailureFilter              = cms3.filt_trackingFailure();
  		Flag_CSCTightHaloFilter                 = cms3.filt_cscBeamHalo();
  	  }

      //cout<<__LINE__<<endl;

  	  // in data and MC
  	  if( !isSMSScan ){
    		Flag_HBHENoiseFilter                    = cms3.filt_hbheNoise();
    		Flag_HBHEIsoNoiseFilter                 = cms3.filt_hbheNoiseIso();
    		Flag_CSCTightHalo2015Filter             = cms3.filt_cscBeamHalo2015();
    		Flag_EcalDeadCellTriggerPrimitiveFilter = cms3.filt_ecalTP();
    		Flag_goodVertices                       = cms3.filt_goodVertices();
    		Flag_eeBadScFilter                      = cms3.filt_eeBadSc();
    		Flag_badChargedCandidateFilter          = badChargedCandidateFilter();
    		// inputs for badMuonFilters in latest cms3 tags
    		if (recent_cms3_version) {
    		  Flag_globalTightHalo2016                      = cms3.filt_globalTightHalo2016();
    		  Flag_badMuonFilter                            = badMuonFilter();
    		  Flag_badMuonFilterv2                          = badMuonFilterV2();
    		  Flag_badChargedCandidateFilterv2              = badChargedCandidateFilterV2();          
    		  if (small_cms3_version >= 18) {
    		    Flag_badMuons                               = cms3.filt_badMuons();
    		    Flag_duplicateMuons                         = cms3.filt_duplicateMuons();
    		    Flag_noBadMuons                             = cms3.filt_noBadMuons();
    		  }
    		}
  	  }
  	  
  	  //TRIGGER
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
  	  HLT_DoubleEl_noiso = ( passHLTTriggerPattern( "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v"    ) ||
  	                         passHLTTriggerPattern( "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_v" ) );
  	  HLT_DoubleEl       = ( passHLTTriggerPattern( "HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_v"   ) ||
				 passHLTTriggerPattern( "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v")); // prescaled - turned off
  	  HLT_DoubleEl_DZ    = passHLTTriggerPattern( "HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"); // prescaled
  	  HLT_DoubleEl_DZ_2  = passHLTTriggerPattern( "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"); // new
     
  	  // electron-muon
  	  HLT_MuEG           = (passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v" )    ||
  				passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v"  )    ||
  				passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v"  )    ||
  				passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v_DZ_v"  ) ||
                                passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v" )    ||
                                passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v"  )  ||
                                passHLTTriggerPattern("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v" )||
                                passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v"  )||
                                 passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v" ));


  	  HLT_MuEG_noiso     = (passHLTTriggerPattern("HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v"                 ) ||
                                passHLTTriggerPattern("HLT_Mu33_Ele33_CaloIdL_GsfTrkIdVL_v"                 ));

  	  HLT_MuEG_2         = (passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v" ) ||
  				passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v"  ) ||
  				passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v"  ) );

  	  HLT_MuEG_noiso_2   =  passHLTTriggerPattern("HLT_Mu33_Ele33_CaloIdL_GsfTrkIdVL_v"                 );
  		
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
  		
  	  // Double muon
  	  HLT_DoubleMu_noiso    = (passHLTTriggerPattern( "HLT_Mu27_TkMu8_v"                          ) ||
  				   passHLTTriggerPattern( "HLT_Mu30_TkMu11_v"                         ) ||
  				   passHLTTriggerPattern( "HLT_Mu40_TkMu11_v"                         ) );

  	  HLT_DoubleMu          =  (passHLTTriggerPattern( "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v"     )||
                                        passHLTTriggerPattern( "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"   )||
                                        passHLTTriggerPattern( "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v" )||
  					passHLTTriggerPattern( "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v"        )||
              				passHLTTriggerPattern( "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v"      ) );

  	  HLT_DoubleMu_noiso_27_8  = passHLTTriggerPattern( "HLT_Mu27_TkMu8_v"                         );
  	  HLT_DoubleMu_noiso_30_11 = passHLTTriggerPattern( "HLT_Mu30_TkMu11_v"                        );
  	  HLT_DoubleMu_noiso_40_11 = passHLTTriggerPattern( "HLT_Mu40_TkMu11_v"                        );
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


  	  
      if (verbose) cout << "before gen particles" << endl;
      
      //cout<<__LINE__<<endl;
      
      //GEN PARTICLES
      ngenPart       = 0;
  	  ngen_p6s3Part  = 0;
      ngenLep        = 0;
  	  ngen_p6s3Lep   = 0;
  	  ngenTau        = 0;
      ngenLepFromTau = 0;
      gen_ht         = 0;

      //cout<<__LINE__<<endl;

  	  if ( cms3.evt_isRealData() && !goodrun(cms3.evt_run(), cms3.evt_lumiBlock()) ) evt_passgoodrunlist = false;
  	  
      //cout<<__LINE__<<endl;

  	  if( !isData ){
        //cout<<__LINE__<<endl;
    		
        for(unsigned int iGen = 0; iGen < cms3.genps_p4().size(); iGen++){
    		  //cout<<__LINE__<<endl;
          genPart_p4            .push_back( cms3.genps_p4()                           .at(iGen));
    		  //cout<<__LINE__<<endl;
          genPart_pt            .push_back( cms3.genps_p4()                           .at(iGen).pt());
    		  //cout<<__LINE__<<endl;
          genPart_eta           .push_back( cms3.genps_p4()                           .at(iGen).eta());
    		  //cout<<__LINE__<<endl;
          genPart_phi           .push_back( cms3.genps_p4()                           .at(iGen).phi());
    		  //cout<<__LINE__<<endl;
          genPart_mass          .push_back( cms3.genps_mass()                         .at(iGen));
    		  //cout<<__LINE__<<endl;
          genPart_pdgId         .push_back( cms3.genps_id()                           .at(iGen));
    		  //cout<<__LINE__<<endl;
          genPart_status        .push_back( cms3.genps_status()                       .at(iGen));
    		  //cout<<__LINE__<<endl;
          genPart_isp6status3   .push_back( cms3.genps_isMostlyLikePythia6Status3()   .at(iGen));
    		  //cout<<__LINE__<<endl;
          genPart_charge        .push_back( cms3.genps_charge()                       .at(iGen));
    		  //cout<<__LINE__<<endl;
          genPart_motherId      .push_back( cms3.genps_id_simplemother()              .at(iGen));
    		  //cout<<__LINE__<<endl;
          genPart_grandmaId     .push_back( cms3.genps_id_simplegrandma()             .at(iGen));
    		  //cout<<__LINE__<<endl;
          ngenPart++;
          
          //cout<<__LINE__<<endl;
    		  
          if( cms3.genps_isMostlyLikePythia6Status3().at(iGen) ) ngen_p6s3Part++;
    		  //calculate gen_ht for stitching purposes
    		  if((abs(cms3.genps_id().at(iGen)) <  6 || // quarks
            abs(cms3.genps_id().at(iGen)) == 21)  // gluons
    			  && (cms3.genps_status().at(iGen) == 22 || // something to do with "status 3"
    				cms3.genps_status().at(iGen) == 23)){
    			  gen_ht += cms3.genps_p4()              .at(iGen).pt();
    		  }
          
          //cout<<__LINE__<<endl;
    		  
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
          
          //cout<<__LINE__<<endl;
    		  
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
          
          //cout<<__LINE__<<endl;
    		  
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
          
          //cout<<__LINE__<<endl;
    		  
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
          
          //cout<<__LINE__<<endl;

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
  		  //cout<<__LINE__<<endl;
  	  }
      //cout<<__LINE__<<endl;
      //LEPTONS
  	  std::vector<std::pair<int, float> > lep_pt_ordering;
  	  vector<float>vec_lep_pt;
      vector<float>vec_lep_eta;
      vector<float>vec_lep_phi;
      vector<float>vec_lep_mass;
      vector<float>vec_lep_charge;
      
      //for WWW
      vector< bool >   vec_lep_3ch_agree;
      vector< bool >    vec_lep_isFromW;
      vector< bool >    vec_lep_isFromZ;
      vector< bool >    vec_lep_isFromB;
      vector< bool >    vec_lep_isFromC;
      vector< bool >    vec_lep_isFromL;
      vector< bool >    vec_lep_isFromLF;
      vector< LorentzVector > vec_lep_closest_jet_p4;
      vector< double > vec_lep_ptRatio;
      vector< double > vec_lep_coneCorrPt;
      vector< double > vec_lep_ptRel;
      vector< int    > vec_lep_motherIdSS;
      vector< int    > vec_lep_genPart_index;
      vector< double > vec_lep_relIso03;
      vector< double > vec_lep_relIso03DB;
      vector< double > vec_lep_relIso03EA;
      vector< double > vec_lep_relIso03EAv2;
      vector< double > vec_lep_relIso04DB;
      vector< double > vec_lep_relIso04EA;
      vector< double > vec_lep_relIso04EAv2;
      vector< double > vec_lep_miniRelIsoCMS3_EA;
      vector< double > vec_lep_miniRelIsoCMS3_EAv2;
      vector< double > vec_lep_miniRelIsoCMS3_DB;


      vector<int>  vec_lep_pdgId;
      vector<int>  vec_lep_mc_Id;
      vector<float>vec_lep_dxy;
      vector<float>vec_lep_ip3d;
      vector<float>vec_lep_ip3derr;
      vector<float>vec_lep_dz;
      vector<int>  vec_lep_tightId;

      vector< bool >   vec_lep_pass_VVV_cutbased_veto;
      vector< bool >   vec_lep_pass_VVV_cutbased_veto_noiso;
      vector< bool >   vec_lep_pass_VVV_cutbased_veto_noiso_noip;
      vector< bool >   vec_lep_pass_VVV_cutbased_fo;
      vector< bool >   vec_lep_pass_VVV_cutbased_fo_noiso;
      vector< bool >   vec_lep_pass_VVV_cutbased_tight_noiso;
      vector< bool >   vec_lep_pass_VVV_cutbased_tight;
      vector< bool >   vec_lep_pass_VVV_MVAbased_tight_noiso;
      vector< bool >   vec_lep_pass_VVV_MVAbased_tight;
      vector< bool >   vec_lep_pass_VVV_baseline;

      vector<int>  vec_lep_mcMatchId;
      vector<int>  vec_lep_lostHits;
      vector<int>  vec_lep_convVeto;
      vector<int>  vec_lep_tightCharge;
      vector<float>vec_lep_MVA;
      vector<float>vec_lep_etaSC;
      vector<float>vec_lep_validfraction;
      vector<float>vec_lep_ptErr;

      //cout<<__LINE__<<endl;

  	  vector<float>vec_lep_sta_pterrOpt ;
  	  vector<float>vec_lep_glb_pterrOpt ;
  	  // vector<float>vec_lep_bft_pterrOpt ;
  	  vector<float>vec_lep_x2ondof      ;
  	  vector<float>vec_lep_sta_x2ondof  ;
  	  vector<float>vec_lep_glb_x2ondof  ;
  	  // vector<float>vec_lep_bft_x2ondof  ;

      //cout<<__LINE__<<endl;

  	  vector<LorentzVector> vec_lep_p4s;

  	  vector<LorentzVector> p4sLeptonsForJetCleaning;

  	  nveto_leptons = 0;
  	  //cout<<__LINE__<<endl;
      if (verbose) cout << "before electrons" << endl;

      //ELECTRONS
      nlep = 0;

      nlep_VVV_cutbased_veto            = 0;
      nlep_VVV_cutbased_veto_noiso      = 0;
      nlep_VVV_cutbased_veto_noiso_noip = 0;
      nlep_VVV_cutbased_fo              = 0;
      nlep_VVV_cutbased_fo_noiso        = 0;
      nlep_VVV_cutbased_tight_noiso     = 0;
      nlep_VVV_cutbased_tight           = 0;
      nlep_VVV_MVAbased_tight_noiso     = 0;
      nlep_VVV_MVAbased_tight           = 0;
      nlep_VVV_baseline                 = 0;
      
      nElectrons10 = 0;
      nVetoEl_relIso03EAless01 = 0;
      nVetoEl_relIso03EAless02 = 0;
      nVetoEl_relIso03EAless03 = 0;
      nVetoEl_relIso03EAless04 = 0;

  	  for(unsigned int iEl = 0; iEl < cms3.els_p4().size(); iEl++){
   	  	//cout<<"checking electrons"<<endl;
        if( !(passElectronSelection_VVV( iEl, VVV_cutbased_veto_noiso_noip ) || passElectronSelection_VVV( iEl, VVV_MVAbased_tight_noiso )) ) {
          /*cout<<"Electron did not pass analysis selection, checking veto selection"<<endl;
          cout<<"etaSC: "<<fabs(els_etaSC().at(iEl))<<" ";
          cout<<"conv_vtx: "<<els_conv_vtx_flag().at(iEl)<<" ";
          cout<<"exp_inlayers: "<<els_exp_innerlayers().at(iEl)<<" ";
          cout<<"dxy: "<<fabs(els_dxyPV().at(iEl))<<" ";
          cout<<"TSnoIso: "<<isTriggerSafenoIso_v1(iEl)<<" ";
          cout<<"dz: "<<fabs(els_dzPV().at(iEl))<<" ";
          cout<<"sip: "<<fabs(els_ip3d().at(iEl))/els_ip3derr().at(iEl)<<" ";
          cout<<"MVA: "<<getMVAoutput(iEl)<<endl;*/
          if( passElectronSelection_VVV( iEl, VVV_cutbased_veto_noiso ) ){ 
            //cout<<"Electron passed veto selection, eta is "<< cms3.els_p4().at(iEl).eta() <<endl;
            if( abs(cms3.els_p4().at(iEl).eta()) <= 2.4 ){
              //cout<<"Electron eta <= 2.4, adding to veto leptons selection, relIsoValue is "<<eleRelIso03EA(iEl, /*eaversion=*/1)<<endl;
              nveto_leptons++;
              if (eleRelIso03EA(iEl, /*eaversion=*/1) > 0.40) nVetoEl_relIso03EAless04++;
              else if (eleRelIso03EA(iEl, /*eaversion=*/1) > 0.30) nVetoEl_relIso03EAless03++;
              else if (eleRelIso03EA(iEl, /*eaversion=*/1) > 0.20) nVetoEl_relIso03EAless02++;
              else if (eleRelIso03EA(iEl, /*eaversion=*/1) > 0.10) nVetoEl_relIso03EAless01++;
              nVetoEl_relIso03EAless03 += nVetoEl_relIso03EAless04;
              nVetoEl_relIso03EAless02 += nVetoEl_relIso03EAless03;
              nVetoEl_relIso03EAless01 += nVetoEl_relIso03EAless02;
            }
            //cout<<"num veto els: 01=="<<nVetoEl_relIso03EAless01<<" 02=="<< nVetoEl_relIso03EAless02<<" 03=="<< nVetoEl_relIso03EAless03<<" 04=="<< nVetoEl_relIso03EAless04<<endl;
          }
          continue;
        }
  		
          nElectrons10++;

    		if( cms3.els_p4().at(iEl).pt() > 10.0 ){
    		  lep_pt_ordering	   .push_back( std::pair<int, float>(nlep, cms3.els_p4().at(iEl).pt()));
    		  vec_lep_p4s          .push_back( cms3.els_p4().at(iEl)           );
    		  vec_lep_pt           .push_back( cms3.els_p4().at(iEl).pt()      );
    		  vec_lep_eta          .push_back( cms3.els_p4().at(iEl).eta()     ); //save eta, even though we use SCeta for ID
    		  vec_lep_phi          .push_back( cms3.els_p4().at(iEl).phi()     );
    		  vec_lep_mass         .push_back( cms3.els_mass().at(iEl)         );
    		  vec_lep_charge       .push_back( cms3.els_charge().at(iEl)       );
          
          //WWW Selection Vars
          vec_lep_3ch_agree            .push_back( threeChargeAgree(iEl) );
          const LorentzVector& temp_jet_p4 = closestJet(cms3.els_p4().at(iEl), 0.4, 3.0, /*whichCorr = */2);
          float closeJetPt            = temp_jet_p4.pt();
          vec_lep_closest_jet_p4       .push_back(temp_jet_p4);
          vec_lep_ptRatio              .push_back((closeJetPt>0. ? cms3.els_p4().at(iEl).pt()/closeJetPt : 1.));
          vec_lep_coneCorrPt           .push_back(coneCorrPt(/* pdgid= */ 11, iEl));
          vec_lep_ptRel                .push_back(ptRel(cms3.els_p4().at(iEl), temp_jet_p4, true));
          vec_lep_relIso03             .push_back(eleRelIso03_noCorr(iEl));
          vec_lep_relIso03DB           .push_back(eleRelIso03DB(iEl));
          vec_lep_relIso03EA           .push_back(eleRelIso03EA(iEl, /*eaversion=*/1));
          vec_lep_relIso03EAv2         .push_back(eleRelIso03EA(iEl, /*eaversion=*/2));
          vec_lep_relIso04DB           .push_back(elRelIsoCustomCone(iEl, 0.4, false, 0.0, /*useDBCorr=*/true));
          vec_lep_relIso04EA           .push_back(elRelIsoCustomCone(iEl, 0.4, false, 0.0, /*useDBCorr=*/false, /*useEACorr=*/true, /*mindr=*/-1, /*eaversion=*/1));
          vec_lep_relIso04EAv2         .push_back(elRelIsoCustomCone(iEl, 0.4, false, 0.0, /*useDBCorr=*/false, /*useEACorr=*/true, /*mindr=*/-1, /*eaversion=*/2));
          vec_lep_miniRelIsoCMS3_EA    .push_back(elMiniRelIsoCMS3_EA(iEl, /*eaversion=*/1));
          vec_lep_miniRelIsoCMS3_EAv2  .push_back(elMiniRelIsoCMS3_EA(iEl, /*eaversion=*/2));
          vec_lep_miniRelIsoCMS3_DB    .push_back(elMiniRelIsoCMS3_DB(iEl));

          vec_lep_pass_VVV_cutbased_veto            .push_back( passElectronSelection_VVV( iEl, VVV_cutbased_veto             ) );
          vec_lep_pass_VVV_cutbased_veto_noiso      .push_back( passElectronSelection_VVV( iEl, VVV_cutbased_veto_noiso       ) );
          vec_lep_pass_VVV_cutbased_veto_noiso_noip .push_back( passElectronSelection_VVV( iEl, VVV_cutbased_veto_noiso_noip  ) );
          vec_lep_pass_VVV_cutbased_fo              .push_back( passElectronSelection_VVV( iEl, VVV_cutbased_fo               ) );
          vec_lep_pass_VVV_cutbased_fo_noiso        .push_back( passElectronSelection_VVV( iEl, VVV_cutbased_fo_noiso         ) );
          vec_lep_pass_VVV_cutbased_tight_noiso     .push_back( passElectronSelection_VVV( iEl, VVV_cutbased_tight_noiso      ) );
          vec_lep_pass_VVV_cutbased_tight           .push_back( passElectronSelection_VVV( iEl, VVV_cutbased_tight            ) );
          vec_lep_pass_VVV_MVAbased_tight_noiso     .push_back( passElectronSelection_VVV( iEl, VVV_MVAbased_tight_noiso      ) );
          vec_lep_pass_VVV_MVAbased_tight           .push_back( passElectronSelection_VVV( iEl, VVV_MVAbased_tight            ) );
          vec_lep_pass_VVV_baseline                 .push_back( passElectronSelection_VVV( iEl, VVV_baseline                  ) );

          if ( vec_lep_pass_VVV_cutbased_veto.back()            ) nlep_VVV_cutbased_veto++;
          if ( vec_lep_pass_VVV_cutbased_veto_noiso.back()      ) nlep_VVV_cutbased_veto_noiso++;
          if ( vec_lep_pass_VVV_cutbased_veto_noiso_noip.back() ) nlep_VVV_cutbased_veto_noiso_noip++;
          if ( vec_lep_pass_VVV_cutbased_fo.back()              ) nlep_VVV_cutbased_fo++;
          if ( vec_lep_pass_VVV_cutbased_fo_noiso.back()        ) nlep_VVV_cutbased_fo_noiso++;
          if ( vec_lep_pass_VVV_cutbased_tight_noiso.back()     ) nlep_VVV_cutbased_tight_noiso++;
          if ( vec_lep_pass_VVV_cutbased_tight.back()           ) nlep_VVV_cutbased_tight++;
          if ( vec_lep_pass_VVV_MVAbased_tight_noiso.back()     ) nlep_VVV_MVAbased_tight_noiso++;
          if ( vec_lep_pass_VVV_MVAbased_tight.back()           ) nlep_VVV_MVAbased_tight++;
          if ( vec_lep_pass_VVV_baseline.back()                 ) nlep_VVV_baseline++;

          if (!isData){
            vec_lep_isFromW              .push_back( isFromW(/* pdgid= */11, iEl)  );
            vec_lep_isFromZ              .push_back( isFromZ(/* pdgid= */11, iEl)  );
            vec_lep_isFromB              .push_back( isFromB(/* pdgid= */11, iEl)  );
            vec_lep_isFromC              .push_back( isFromC(/* pdgid= */11, iEl)  );
            vec_lep_isFromL              .push_back( isFromLight(/* pdgid= */11, iEl)  );
            vec_lep_isFromLF             .push_back( isFromLightFake(/* pdgid= */11, iEl) );
            pair<int, int> motherId_genIdx = lepMotherID_v2(Lep(cms3.els_charge().at(iEl)*(-11), iEl));//don't forget the sign
            vec_lep_motherIdSS           .push_back(motherId_genIdx.first);
            vec_lep_genPart_index        .push_back(motherId_genIdx.second);
            vec_lep_mc_Id                .push_back( cms3.els_mc_id().at(iEl)        );
          }
          else{
            vec_lep_isFromW              .push_back( -1 );
            vec_lep_isFromZ              .push_back( -1 );
            vec_lep_isFromB              .push_back( -1 );
            vec_lep_isFromC              .push_back( -1 );
            vec_lep_isFromL              .push_back( -1 );
            vec_lep_isFromLF             .push_back( -1 );
            vec_lep_motherIdSS           .push_back( -1 );
            vec_lep_genPart_index        .push_back( -1 );
            vec_lep_mc_Id                .push_back( -1 );
          }

    		  vec_lep_pdgId        .push_back( cms3.els_charge().at(iEl)*(-11) );
    		  vec_lep_dxy          .push_back( cms3.els_dxyPV().at(iEl)        );
          vec_lep_ip3d         .push_back( cms3.els_ip3d().at(iEl)         );
          vec_lep_ip3derr      .push_back( cms3.els_ip3derr().at(iEl)      );
    		  vec_lep_dz           .push_back( cms3.els_dzPV().at(iEl)         );
    		  vec_lep_tightId      .push_back( eleTightID(iEl, ZMET)           );
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

  	  //cout<<__LINE__<<endl;

      //MUONS
      nMuons10 = 0;
      nBadMuons20 = 0;
      nVetoMu_relIso03EAless01 = 0;
      nVetoMu_relIso03EAless02 = 0;
      nVetoMu_relIso03EAless03 = 0;
      nVetoMu_relIso03EAless04 = 0;
  	  // RCLSA: this is a TEMPORARY protections for a problem with CMS3 samples
  	  if (cms3.mus_p4().size() != cms3.mus_dzPV().size()) continue;
      
      //cout<<__LINE__<<endl;  
  	  
      for(unsigned int iMu = 0; iMu < cms3.mus_p4().size(); iMu++){
        if (recent_cms3_version) {
          if (cms3.mus_p4().at(iMu).pt() > 20.0 && isBadGlobalMuon(iMu)) ++nBadMuons20;
        }
   	  	if( !passMuonSelection_VVV( iMu, VVV_cutbased_veto_noiso_noip ) ){
          /*cout<<"Muon did not pass analysis selection, checking veto selection"<<endl;
          cout<<"dxy: "<<fabs(mus_dxyPV().at(iMu))<<" ";
          cout<<"dz: "<<fabs(mus_dzPV().at(iMu))<<" ";
          cout<<"sip: "<<fabs(mus_ip3d().at(iMu))/mus_ip3derr().at(iMu)<<" ";
          cout<<"ptSig: "<<(mus_ptErr().at(iMu)/mus_trk_p4().at(iMu).pt())<<" ";
          cout<<"Med ID: "<<isMediumMuonPOG(iMu)<<" ";
          cout<<"Eta: "<<abs(cms3.mus_p4().at(iMu).eta())<<" ";
          cout<<"Loose ID: "<<isLooseMuonPOG(iMu)<<endl;*/

          if( passMuonSelection_VVV( iMu, VVV_cutbased_veto_noiso ) ){ //from SSSelections.h (strictly looser than our analysis selection)
            //cout<<"Muon passed veto selection, eta is "<< cms3.mus_p4().at(iMu).eta() <<endl;
            if( abs(cms3.mus_p4().at(iMu).eta()) <= 2.4 ){
              //cout<<"Muon eta <= 2.4, adding to veto leptons selection, relIsoValue is "<<muRelIso03EA(iMu, /*eaversion=*/1)<<endl;
              nveto_leptons++;
              if (muRelIso03EA(iMu, /*eaversion=*/1) > 0.40) nVetoMu_relIso03EAless04++;
              else if (muRelIso03EA(iMu, /*eaversion=*/1) > 0.30) nVetoMu_relIso03EAless03++;
              else if (muRelIso03EA(iMu, /*eaversion=*/1) > 0.20) nVetoMu_relIso03EAless02++;
              else if (muRelIso03EA(iMu, /*eaversion=*/1) > 0.10) nVetoMu_relIso03EAless01++;
              nVetoMu_relIso03EAless03 += nVetoMu_relIso03EAless04;
              nVetoMu_relIso03EAless02 += nVetoMu_relIso03EAless03;
              nVetoMu_relIso03EAless01 += nVetoMu_relIso03EAless02;
              //cout<<"num veto muons: 01=="<<nVetoMu_relIso03EAless01<<" 02=="<< nVetoMu_relIso03EAless02<<" 03=="<< nVetoMu_relIso03EAless03<<" 04=="<< nVetoMu_relIso03EAless04<<endl;
              }
            }
            continue;
        } 
  		  
        //cout<<__LINE__<<endl;
        
        nMuons10++;

  		  double validFraction = mus_validHits().at(iMu)/(double)(mus_validHits().at(iMu)+mus_lostHits().at(iMu)+mus_exp_innerlayers().at(iMu)+mus_exp_outerlayers().at(iMu));
  		  
        //cout<<__LINE__<<endl;  
        
    		if( cms3.mus_p4().at(iMu).pt() > 10.0 ){
     		  lep_pt_ordering	   .push_back ( std::pair<int, float>(nlep, cms3.mus_p4().at(iMu).pt()));
    		  vec_lep_p4s          .push_back ( cms3.mus_p4()     .at(iMu)       );
    		  vec_lep_pt           .push_back ( cms3.mus_p4()     .at(iMu).pt()  );
    		  vec_lep_eta          .push_back ( cms3.mus_p4()     .at(iMu).eta() );
    		  vec_lep_phi          .push_back ( cms3.mus_p4()     .at(iMu).phi() );
    		  vec_lep_mass         .push_back ( cms3.mus_mass()   .at(iMu)       );
    		  vec_lep_charge       .push_back ( cms3.mus_charge() .at(iMu)       );
          
          //WWW Selection Vars
          vec_lep_3ch_agree            .push_back( true );
          const LorentzVector& temp_jet_p4 = closestJet(cms3.mus_p4().at(iMu), 0.4, 3.0, /*whichCorr = */2);
          float closeJetPt            = temp_jet_p4.pt();
          vec_lep_closest_jet_p4       .push_back(temp_jet_p4);
          vec_lep_ptRatio              .push_back((closeJetPt>0. ? cms3.mus_p4().at(iMu).pt()/closeJetPt : 1.));
          vec_lep_coneCorrPt           .push_back(coneCorrPt(/* pdgid= */ 13, iMu));
          vec_lep_ptRel                .push_back(ptRel(cms3.mus_p4().at(iMu), temp_jet_p4, true));
          vec_lep_relIso03             .push_back(muRelIso03_noCorr(iMu));
          vec_lep_relIso03DB           .push_back(muRelIso03DB(iMu));
          vec_lep_relIso03EA           .push_back(muRelIso03EA(iMu,/*eaversion=*/1));
          vec_lep_relIso03EAv2         .push_back(muRelIso03EA(iMu,/*eaversion=*/2));
          vec_lep_relIso04DB           .push_back(muRelIso04DB(iMu));
          vec_lep_relIso04EA           .push_back(muRelIsoCustomCone(iMu, 0.4, /*useVetoCones=*/false, 0.5, false, true, -1, 1));
          vec_lep_relIso04EAv2         .push_back(muRelIsoCustomCone(iMu, 0.4, /*useVetoCones=*/false, 0.5, false, true, -1, 2));
          vec_lep_miniRelIsoCMS3_EA    .push_back(muMiniRelIsoCMS3_EA(iMu, /*eaversion=*/1));
          vec_lep_miniRelIsoCMS3_EAv2  .push_back(muMiniRelIsoCMS3_EA(iMu, /*eaversion=*/2));
          vec_lep_miniRelIsoCMS3_DB    .push_back(muMiniRelIsoCMS3_DB(iMu));

          vec_lep_pass_VVV_cutbased_veto            .push_back( passMuonSelection_VVV( iMu, VVV_cutbased_veto              ) );
          vec_lep_pass_VVV_cutbased_veto_noiso      .push_back( passMuonSelection_VVV( iMu, VVV_cutbased_veto_noiso        ) );
          vec_lep_pass_VVV_cutbased_veto_noiso_noip .push_back( passMuonSelection_VVV( iMu, VVV_cutbased_veto_noiso_noip   ) );
          vec_lep_pass_VVV_cutbased_fo              .push_back( passMuonSelection_VVV( iMu, VVV_cutbased_fo                ) );
          vec_lep_pass_VVV_cutbased_fo_noiso        .push_back( passMuonSelection_VVV( iMu, VVV_cutbased_fo_noiso          ) );
          vec_lep_pass_VVV_cutbased_tight_noiso     .push_back( passMuonSelection_VVV( iMu, VVV_cutbased_tight_noiso       ) );
          vec_lep_pass_VVV_cutbased_tight           .push_back( passMuonSelection_VVV( iMu, VVV_cutbased_tight             ) );
          vec_lep_pass_VVV_MVAbased_tight_noiso     .push_back( passMuonSelection_VVV( iMu, VVV_cutbased_tight_noiso       ) ); //MVA for Muons doesn't exist, so use cutbased tight
          vec_lep_pass_VVV_MVAbased_tight           .push_back( passMuonSelection_VVV( iMu, VVV_cutbased_tight             ) ); //MVA for Muons doesn't exist, so use cutbased tight
          vec_lep_pass_VVV_baseline                 .push_back( passMuonSelection_VVV( iMu, VVV_baseline                   ) );
          
          if (vec_lep_pass_VVV_cutbased_veto.back()            ) nlep_VVV_cutbased_veto++;
          if (vec_lep_pass_VVV_cutbased_veto_noiso.back()      ) nlep_VVV_cutbased_veto_noiso++;
          if (vec_lep_pass_VVV_cutbased_veto_noiso_noip.back() ) nlep_VVV_cutbased_veto_noiso_noip++;
          if (vec_lep_pass_VVV_cutbased_fo.back()              ) nlep_VVV_cutbased_fo++;
          if (vec_lep_pass_VVV_cutbased_fo_noiso.back()        ) nlep_VVV_cutbased_fo_noiso++;
          if (vec_lep_pass_VVV_cutbased_tight_noiso.back()     ) nlep_VVV_cutbased_tight_noiso++;
          if (vec_lep_pass_VVV_cutbased_tight.back()           ) nlep_VVV_cutbased_tight++;
          if (vec_lep_pass_VVV_MVAbased_tight_noiso.back()     ) nlep_VVV_MVAbased_tight_noiso++;
          if (vec_lep_pass_VVV_MVAbased_tight.back()           ) nlep_VVV_MVAbased_tight++;
          if (vec_lep_pass_VVV_baseline.back()                 ) nlep_VVV_baseline++;

          if (!isData){
            vec_lep_isFromW              .push_back( isFromW(/* pdgid= */13, iMu)  );
            vec_lep_isFromZ              .push_back( isFromZ(/* pdgid= */13, iMu)  );
            vec_lep_isFromB              .push_back( isFromB(/* pdgid= */13, iMu)  );
            vec_lep_isFromC              .push_back( isFromC(/* pdgid= */13, iMu)  );
            vec_lep_isFromL              .push_back( isFromLight(/* pdgid= */13, iMu)  );
            vec_lep_isFromLF             .push_back( isFromLightFake(/* pdgid= */13, iMu) );

            pair<int, int> motherId_genIdx = lepMotherID_v2(Lep(cms3.mus_charge().at(iMu)*(-13), iMu));//don't forget the sign
            vec_lep_motherIdSS           .push_back(motherId_genIdx.first);
            vec_lep_genPart_index        .push_back(motherId_genIdx.second);
            vec_lep_mc_Id                .push_back ( cms3.mus_mc_id() .at(iMu)          );

          }
          else{
            vec_lep_isFromW              .push_back( -1 );
            vec_lep_isFromZ              .push_back( -1 );
            vec_lep_isFromB              .push_back( -1 );
            vec_lep_isFromC              .push_back( -1 );
            vec_lep_isFromL              .push_back( -1 );
            vec_lep_isFromLF             .push_back( -1 );
            vec_lep_motherIdSS           .push_back( -1 );
            vec_lep_genPart_index        .push_back( -1 );
            vec_lep_mc_Id                .push_back( -1 );  
          }

          vec_lep_pdgId        .push_back ( cms3.mus_charge() .at(iMu)*(-13) );
    		  vec_lep_dxy          .push_back ( cms3.mus_dxyPV()  .at(iMu)       );
          vec_lep_ip3d         .push_back ( cms3.mus_ip3d()   .at(iMu)       );
          vec_lep_ip3derr      .push_back ( cms3.mus_ip3derr().at(iMu)       );
    		  vec_lep_dz           .push_back ( cms3.mus_dzPV()   .at(iMu)       );
    		  vec_lep_tightId      .push_back ( isTightMuonPOG(iMu)              );
    		  vec_lep_etaSC        .push_back ( cms3.mus_p4().at(iMu).eta()      );
    		  vec_lep_MVA          .push_back ( -99                              );
    		  vec_lep_validfraction.push_back ( validFraction                    );
    		  vec_lep_ptErr        .push_back ( cms3.mus_ptErr() .at(iMu)        );

          //cout<<__LINE__<<endl;  
          
    		  vec_lep_sta_pterrOpt .push_back ( cms3.mus_sta_qoverpError() .at(iMu) / cms3.mus_sta_qoverp()  .at(iMu) );
    		  vec_lep_glb_pterrOpt .push_back ( cms3.mus_gfit_qoverpError().at(iMu) / cms3.mus_gfit_qoverp() .at(iMu) );
    		  // vec_lep_bft_pterrOpt .push_back ( cms3.mus_bfit_qoverpError().at(iMu) / cms3.mus_bfit_qoverp() .at(iMu) );
    		  vec_lep_x2ondof      .push_back ( cms3.mus_chi2()            .at(iMu) / cms3.mus_ndof()        .at(iMu) );
    		  vec_lep_sta_x2ondof  .push_back ( cms3.mus_sta_chi2()        .at(iMu) / cms3.mus_sta_ndof()    .at(iMu) );
    		  if( currentFileName.Contains("V08-00-1") ){ 
            vec_lep_glb_x2ondof  .push_back ( cms3.mus_gfit_chi2()       .at(iMu) / cms3.mus_gfit_ndof()   .at(iMu) );
    		  }
          else{                                                       vec_lep_glb_x2ondof  .push_back ( -1.0                                                                  );}
    		  // vec_lep_bft_x2ondof  .push_back ( cms3.mus_bfit_chi2()       .at(iMu) / cms3.mus_bfit_ndof()   .at(iMu) );
    		  
    		  if (!isData && (cms3.mus_mc3dr().at(iMu) < 0.2 && cms3.mus_mc3idx().at(iMu) != -9999 && abs(cms3.mus_mc3_id().at(iMu)) == 13 )) { // matched to a prunedGenParticle electron?
            int momid =  abs(genPart_motherId[cms3.mus_mc3idx().at(iMu)]);
            vec_lep_mcMatchId.push_back ( momid != 13 ? momid : genPart_grandmaId[cms3.mus_mc3idx().at(iMu)]); // if mother is different store mother, otherwise store grandmother
    		  }
    		  else {
            vec_lep_mcMatchId.push_back (0);
          }

    		  vec_lep_lostHits   .push_back ( cms3.mus_exp_innerlayers().at(iMu)); // use defaults as if "good electron"
    		  vec_lep_convVeto   .push_back ( 1                                 );// use defaults as if "good electron"
    		  vec_lep_tightCharge.push_back ( tightChargeMuon(iMu)              );

    		  nlep++;

  		  }

    		if( cms3.mus_p4().at(iMu).pt() > 20.0 ){
    		  p4sLeptonsForJetCleaning.push_back(cms3.mus_p4().at(iMu));
    		}
      }
  	  
      //cout<<__LINE__<<endl;  
      
  	  if (verbose) cout<<" before ordering"<<endl;
  	  
      // Implement pT ordering for leptons (it's irrelevant but easier for us to add than for ETH to remove)
      //now fill arrays from vectors, isotracks with largest pt first
      int i = 0;
      std::sort(lep_pt_ordering.begin(), lep_pt_ordering.end(), sortByValue);
      for(std::vector<std::pair<int, float> >::iterator it = lep_pt_ordering.begin(); it!= lep_pt_ordering.end(); ++it){
    		lep_p4                  .push_back( vec_lep_p4s                 .at(it->first));
    		lep_pt                  .push_back( vec_lep_pt                  .at(it->first));
    		lep_eta                 .push_back( vec_lep_eta                 .at(it->first));
    		lep_phi                 .push_back( vec_lep_phi                 .at(it->first));
    		lep_mass                .push_back( vec_lep_mass                .at(it->first));
    		lep_charge              .push_back( vec_lep_charge              .at(it->first));
    		lep_pdgId               .push_back( vec_lep_pdgId               .at(it->first));
        lep_mc_Id               .push_back( vec_lep_mc_Id               .at(it->first));
    		lep_dz                  .push_back( vec_lep_dz                  .at(it->first));
    		lep_dxy                 .push_back( vec_lep_dxy                 .at(it->first));
        lep_ip3d                .push_back( vec_lep_ip3d                .at(it->first));
        lep_ip3derr             .push_back( vec_lep_ip3derr             .at(it->first));
    		lep_etaSC               .push_back( vec_lep_etaSC               .at(it->first));
    		lep_tightId             .push_back( vec_lep_tightId             .at(it->first));
        lep_closest_jet_p4      .push_back( vec_lep_closest_jet_p4      .at(it->first));
    		
        // WWW Selection Vars
        lep_3ch_agree           .push_back( vec_lep_3ch_agree           .at(it->first));
        lep_isFromW             .push_back( vec_lep_isFromW         .at(it->first));
        lep_isFromZ             .push_back( vec_lep_isFromZ         .at(it->first));
        lep_isFromB             .push_back( vec_lep_isFromB         .at(it->first));
        lep_isFromC             .push_back( vec_lep_isFromC         .at(it->first));
        lep_isFromL             .push_back( vec_lep_isFromL         .at(it->first));
        lep_isFromLF            .push_back( vec_lep_isFromLF        .at(it->first));
        lep_ptRatio             .push_back( vec_lep_ptRatio             .at(it->first));
        lep_motherIdSS          .push_back( vec_lep_motherIdSS          .at(it->first));
        lep_genPart_index       .push_back( vec_lep_genPart_index       .at(it->first));
        lep_coneCorrPt          .push_back( vec_lep_coneCorrPt          .at(it->first));
        lep_ptRel               .push_back( vec_lep_ptRel               .at(it->first));
        lep_relIso03            .push_back( vec_lep_relIso03            .at(it->first));
        lep_relIso03DB          .push_back( vec_lep_relIso03DB          .at(it->first));
        lep_relIso03EA          .push_back( vec_lep_relIso03EA          .at(it->first));
        lep_relIso03EAv2        .push_back( vec_lep_relIso03EAv2        .at(it->first));
        lep_relIso04DB          .push_back( vec_lep_relIso04DB          .at(it->first));
        lep_relIso04EA          .push_back( vec_lep_relIso04EA          .at(it->first));
        lep_relIso04EAv2        .push_back( vec_lep_relIso04EAv2        .at(it->first));
        lep_miniRelIsoCMS3_EA   .push_back( vec_lep_miniRelIsoCMS3_EA   .at(it->first));
        lep_miniRelIsoCMS3_EAv2 .push_back( vec_lep_miniRelIsoCMS3_EAv2 .at(it->first));
        lep_miniRelIsoCMS3_DB   .push_back( vec_lep_miniRelIsoCMS3_DB   .at(it->first));

        lep_pass_VVV_cutbased_veto             .push_back( vec_lep_pass_VVV_cutbased_veto              .at(it->first));
        lep_pass_VVV_cutbased_veto_noiso       .push_back( vec_lep_pass_VVV_cutbased_veto_noiso        .at(it->first));
        lep_pass_VVV_cutbased_veto_noiso_noip  .push_back( vec_lep_pass_VVV_cutbased_veto_noiso_noip   .at(it->first));
        lep_pass_VVV_cutbased_fo               .push_back( vec_lep_pass_VVV_cutbased_fo                .at(it->first));
        lep_pass_VVV_cutbased_fo_noiso         .push_back( vec_lep_pass_VVV_cutbased_fo_noiso          .at(it->first));
        lep_pass_VVV_cutbased_tight_noiso      .push_back( vec_lep_pass_VVV_cutbased_tight_noiso       .at(it->first));
        lep_pass_VVV_cutbased_tight            .push_back( vec_lep_pass_VVV_cutbased_tight             .at(it->first));
        lep_pass_VVV_MVAbased_tight_noiso      .push_back( vec_lep_pass_VVV_MVAbased_tight_noiso       .at(it->first));
        lep_pass_VVV_MVAbased_tight            .push_back( vec_lep_pass_VVV_MVAbased_tight             .at(it->first));
        lep_pass_VVV_baseline                  .push_back( vec_lep_pass_VVV_baseline                   .at(it->first));

    		lep_mcMatchId           .push_back( vec_lep_mcMatchId           .at(it->first));
    		lep_lostHits            .push_back( vec_lep_lostHits            .at(it->first));
    		lep_convVeto            .push_back( vec_lep_convVeto            .at(it->first));
    		lep_tightCharge         .push_back( vec_lep_tightCharge         .at(it->first));
    		lep_MVA                 .push_back( vec_lep_MVA                 .at(it->first));
    		lep_validfraction       .push_back( vec_lep_validfraction       .at(it->first));
    		lep_pterr               .push_back( vec_lep_ptErr               .at(it->first));
    		lep_sta_pterrOpt        .push_back( vec_lep_sta_pterrOpt        .at(it->first));
    		lep_glb_pterrOpt        .push_back( vec_lep_glb_pterrOpt        .at(it->first));
    		// lep_bft_pterrOpt     .push_back( vec_lep_bft_pterrOpt        .at(it->first));
    		lep_x2ondof             .push_back( vec_lep_x2ondof             .at(it->first));
    		lep_sta_x2ondof         .push_back( vec_lep_sta_x2ondof         .at(it->first));
    		lep_glb_x2ondof         .push_back( vec_lep_glb_x2ondof         .at(it->first));
    		// lep_bft_x2ondof      .push_back( vec_lep_bft_x2ondof         .at(it->first));

    		i++;
      }

         
      //cout<<__LINE__<<endl;  
       
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
    		gamma_hOverE_online.push_back( cms3.photons_full5x5_hOverE().at(iGamma)        );
    		gamma_idCutBased   .push_back( isTightPhoton(iGamma,HAD) ? 1 : 0               ); 		
    		gamma_hollowtkiso03.push_back( cms3.photons_tkIsoHollow03()   .at(iGamma)      );
    		gamma_ecpfclusiso  .push_back( photonEcalpfClusterIso03EA(iGamma)              );
    		gamma_hcpfclusiso  .push_back( photonHcalpfClusterIso03EA(iGamma)              );

    		if(gamma_pt[ngamma] > 20) nGammas20++;
    	
        //cout<<__LINE__<<endl;  
      
    		// Some work for truth-matching (should be integrated in CMS3 as for the leptons)
    		int bestMatch = -1;
    		float bestDr = 0.1;
    		float bestMatchEta = -999;
    		float bestMatchPhi = -999;

    		if( !isData ){		  
    		  for(unsigned int iGen = 0; iGen < cms3.genps_p4().size(); iGen++){
    		    if ( (cms3.genps_id().at(iGen) != 22) && (abs(cms3.genps_id().at(iGen)) != 11) ) continue; // accept gen photons and electrons
      			if ( cms3.genps_status()               .at(iGen)        != 1  ) continue; 
      			if ( (fabs(cms3.genps_id_simplemother() .at(iGen))       > 24) && (fabs (cms3.genps_id_simplemother() .at(iGen)) != 2212) ) continue; // pions etc 
      			if ( fabs(eta - cms3.genps_p4()        .at(iGen).eta()) > 0.1 ) continue;
      			if ( 2*cms3.genps_p4()                 .at(iGen).pt()   < pt  ) continue;
      			if ( 0.5*cms3.genps_p4()               .at(iGen).pt()   > pt  ) continue;
      			float thisDR = DeltaR( cms3.genps_p4() .at(iGen).eta(), eta, cms3.genps_p4().at(iGen).phi(), phi);
            if (thisDR < bestDr) {
      			  bestDr = thisDR;
      			  bestMatch = iGen;
      			  bestMatchEta = cms3.genps_p4().at(iGen).eta();
      			  bestMatchPhi = cms3.genps_p4().at(iGen).phi();
      			}
    		  }

          //cout<<__LINE__<<endl;  
      
    		  if (bestMatch != -1) {
      			// 7 is a special code for photons without a mother. this seems to be due to a miniAOD bug where links are broken.
      		  gamma_mcMatchId.push_back(cms3.genps_id_simplemother().at(bestMatch) == 0 ? 7 : cms3.genps_id().at(bestMatch));
            gamma_genPt.push_back(cms3.genps_id().at(bestMatch) == 22 ? cms3.genps_p4().at(bestMatch).pt() : -1);
      			gamma_genIso.push_back(-1); //cms2.genps_iso().at(bestMatch);
            gamma_genIsPromptFinalState.push_back(cms3.genps_isPromptFinalState().at(bestMatch));
            // Now want to look at DR between photon and parton
      			float minDR = 999.; 
      			for(unsigned int iGen = 0; iGen < cms3.genps_p4().size(); iGen++){
      			  if( cms3.genps_status().at(iGen)   != 22 && cms3.genps_status().at(iGen)   != 23) continue;
      			  if( fabs(cms3.genps_id().at(iGen)) != 21 || fabs(cms3.genps_id().at(iGen)) <= 4 ) continue;
      			  float dr = DeltaR( cms3.genps_p4().at(iGen).eta(), bestMatchEta, cms3.genps_p4().at(iGen).phi(), bestMatchPhi);
      			  if (dr < minDR) minDR = dr;
      			}
      			
            gamma_drMinParton.push_back ( minDR );
    		  }
    		  else {
      			gamma_mcMatchId.push_back(0);
      			gamma_genPt.push_back(-1);
      			gamma_genIso.push_back(-1);
      			gamma_genIsPromptFinalState.push_back(-1);
      			gamma_drMinParton.push_back ( -1 );
    		  }
    		}   
    		ngamma++;
      }
  	
      //cout<<__LINE__<<endl;  
      
  	  if( isData && ngamma > 0 ){
  	    float minDr = 0.2;		

  	    // old way: loop through all trigger objects
        if (small_cms3_version < 18) {
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
        	} // loop over trig objs
        } // if old CMS3 version

  	    // new way: pre-computed matching in CMS3
  	    else if (small_cms3_version >= 18) {
  	      if( HLT_Photon165_HE10             > 0 && cms3.photons_HLT_Photon165_HE10().at(0) )             HLT_Photon165_HE10_matchedtophoton             = true;
  	      if( HLT_Photon165_R9Id90_HE10_IsoM > 0 && cms3.photons_HLT_Photon165_R9Id90_HE10_IsoM().at(0) ) HLT_Photon165_R9Id90_HE10_IsoM_matchedtophoton = true;
  	      if( HLT_Photon120_R9Id90_HE10_IsoM > 0 && cms3.photons_HLT_Photon120_R9Id90_HE10_IsoM().at(0) ) HLT_Photon120_R9Id90_HE10_IsoM_matchedtophoton = true;
  	      if( HLT_Photon90_R9Id90_HE10_IsoM  > 0 && cms3.photons_HLT_Photon90_R9Id90_HE10_IsoM().at(0) )  HLT_Photon90_R9Id90_HE10_IsoM_matchedtophoton  = true;
  	      if( HLT_Photon75_R9Id90_HE10_IsoM  > 0 && cms3.photons_HLT_Photon75_R9Id90_HE10_IsoM().at(0) )  HLT_Photon75_R9Id90_HE10_IsoM_matchedtophoton  = true;
  	      if( HLT_Photon50_R9Id90_HE10_IsoM  > 0 && cms3.photons_HLT_Photon50_R9Id90_HE10_IsoM().at(0) )  HLT_Photon50_R9Id90_HE10_IsoM_matchedtophoton  = true;
  	      if( HLT_Photon36_R9Id90_HE10_IsoM  > 0 && cms3.photons_HLT_Photon36_R9Id90_HE10_IsoM().at(0) )  HLT_Photon36_R9Id90_HE10_IsoM_matchedtophoton  = true;
  	      if( HLT_Photon30_R9Id90_HE10_IsoM  > 0 && cms3.photons_HLT_Photon30_R9Id90_HE10_IsoM().at(0) )  HLT_Photon30_R9Id90_HE10_IsoM_matchedtophoton  = true;
  	      if( HLT_Photon22_R9Id90_HE10_IsoM  > 0 && cms3.photons_HLT_Photon22_R9Id90_HE10_IsoM().at(0) )  HLT_Photon22_R9Id90_HE10_IsoM_matchedtophoton  = true;
  	    } // if new CMS3 version
  	  }
  	  
      //cout<<__LINE__<<endl;  
      
  	  // add selections to keep only events with photons and dilepton events
  	  if( !(ngamma > 0 || nlep > 0) ) {
  	    simpa.GenerateRandoms(); // supposed to make sure we generate the same amount of random numbers whether we pass or fail each event..
        //cout<<"DEBUGEVENT: run "<<run<<" lumi "<<lumi<<" evt "<<evt<<" Failed < 0 leptons or less than 0 photons"<<endl;
  	    continue;// fix for not iso study
  	  }
  		// std::pair <int, int> hyp_indices =  getHypLepIndices( lep_p4, lep_pdgId );
  	  std::pair <int, int> hyp_indices = std::make_pair(0, 1);
  		
  	  if (nlep > 1 ) {//require min 2 leps
    		if (lep_charge.at(hyp_indices.first)*lep_charge.at(hyp_indices.second) > 0){
    		  evt_type = 1; // same sign event
    		}
        else{
    		  evt_type = 0; // oppo sign event 
    		}

    		if ( abs(lep_pdgId.at(hyp_indices.first)) == 11 && abs(lep_pdgId.at(hyp_indices.second)) == 11 ){ 
          hyp_type = 0;// ee event												   			   
    		}
        else if (  abs(lep_pdgId.at(hyp_indices.first)) == 13 && abs(lep_pdgId.at(hyp_indices.second)) == 13 ){ 
          hyp_type = 1;// mm event												   			   
    		}
        else if ( (abs(lep_pdgId.at(hyp_indices.first)) == 11 && abs(lep_pdgId.at(hyp_indices.second)) == 13) || (abs(lep_pdgId.at(hyp_indices.first)) == 13 && abs(lep_pdgId.at(hyp_indices.second)) == 11) ){ 
          hyp_type = 2;// em event
    		}
        else {
    		  //cout<<"Leptype not ee, mm, or em! Exiting."<<endl;
    		  simpa.GenerateRandoms(); // supposed to make sure we generate the same amount of random numbers whether we pass or fail each event..
          //cout<<"DEBUGEVENT: run "<<run<<" lumi "<<lumi<<" evt "<<evt<<" Failed More than 1 lepton, but can't be matched to ee, mumu, or emu"<<endl;
    		  continue;
    		}

    		dilmass = (lep_p4.at(hyp_indices.first)+lep_p4.at(hyp_indices.second)).mass();
    		dilpt   = (lep_p4.at(hyp_indices.first)+lep_p4.at(hyp_indices.second)).pt();       

    		//Add dRll
    		float dEtall =            lep_p4.at(hyp_indices.first).eta() - lep_p4.at(hyp_indices.second).eta();
    		float dPhill = acos( cos( lep_p4.at(hyp_indices.first).phi() - lep_p4.at(hyp_indices.second).phi() ) );
    		dRll = sqrt(pow( dEtall, 2) + pow( dPhill, 2));
  	  }
      else if( ngamma > 0 ) {// here are the photon only variables
        evt_type = 2; // photon + jets event
  	  }
      else{
        simpa.GenerateRandoms(); // supposed to make sure we generate the same amount of random numbers whether we pass or fail each event..
        //cout<<"DEBUGEVENT: run "<<run<<" lumi "<<lumi<<" evt "<<evt<<" Failed More than 1 lepton, but can't be matched to ee, mumu, or emu"<<endl;
        continue; // leftovers
  	  }

      //cout<<__LINE__<<endl;  
      
  	  if(nlep>1){
  		  LorentzVector z_pt(lep_p4.at(hyp_indices.first).X()+lep_p4.at(hyp_indices.second).X(),
  						   lep_p4.at(hyp_indices.first).Y()+lep_p4.at(hyp_indices.second).Y(),
  						   lep_p4.at(hyp_indices.first).Z()+lep_p4.at(hyp_indices.second).Z(),
  						   lep_p4.at(hyp_indices.first).E()+lep_p4.at(hyp_indices.second).E());

    		//start from here
    		std::pair<LorentzVector, LorentzVector> lepsFromDecayedGamma = simpa.returnDecayProducts( z_pt );
    		decayedphoton_lep1_p4 = lepsFromDecayedGamma.first;
    		decayedphoton_lep2_p4 = lepsFromDecayedGamma.second;
    		decayedphoton_bosn_p4 =
    		  LorentzVector(decayedphoton_lep1_p4.X()+decayedphoton_lep2_p4.X(),
    						decayedphoton_lep1_p4.Y()+decayedphoton_lep2_p4.Y(),
    						decayedphoton_lep1_p4.Z()+decayedphoton_lep2_p4.Z(),
    						decayedphoton_lep1_p4.E()+decayedphoton_lep2_p4.E());
  	  }	  
  	  else if(ngamma>0){
    		//start from here
    		std::pair<LorentzVector, LorentzVector> lepsFromDecayedGamma = simpa.returnDecayProducts( gamma_p4.at(0) );
    		decayedphoton_lep1_p4 = lepsFromDecayedGamma.first;
    		decayedphoton_lep2_p4 = lepsFromDecayedGamma.second;
    		decayedphoton_bosn_p4 =
    		  LorentzVector(decayedphoton_lep1_p4.X()+decayedphoton_lep2_p4.X(),
    						decayedphoton_lep1_p4.Y()+decayedphoton_lep2_p4.Y(),
    						decayedphoton_lep1_p4.Z()+decayedphoton_lep2_p4.Z(),
    						decayedphoton_lep1_p4.E()+decayedphoton_lep2_p4.E());
  	  }
  	  
      //cout<<__LINE__<<endl;  
      
  	  if (verbose) cout << "before jets" << endl;
  	  
      //JETS
      //correct jets and check baseline selections
      vector < LorentzVector> p4sCorrJets; // store corrected p4 for ALL jets, so indices match CMS3 ntuple
      vector < LorentzVector> p4sCorrJets_up; // store corrected p4 for ALL jets, so indices match CMS3 ntuple
      vector < LorentzVector> p4sCorrJets_dn; // store corrected p4 for ALL jets, so indices match CMS3 ntuple
      vector < double       > jet_corrfactor; // store correction for ALL jets, and indices match CMS3 ntuple
      vector < std::pair<int,float> > passJets; //index of jets that pass baseline selections with their corrected pt
      vector < double       > jet_corrfactor_up; // store correction for ALL jets, and vary by uncertainties
      vector < double       > jet_corrfactor_dn; // store correction for ALL jets, and vary by uncertainties

      for(unsigned int iJet = 0; iJet < cms3.pfjets_p4().size(); iJet++){

    		LorentzVector pfjet_p4_cor = cms3.pfjets_p4().at(iJet);

    		double corr = 1.0;
    		double shift = 0.0;
    		if (applyJECfromFile) {

    		  // get uncorrected jet p4 to use as input for corrections
    		  LorentzVector pfjet_p4_uncor = cms3.pfjets_p4().at(iJet) * cms3.pfjets_undoJEC().at(iJet);

    		  vector<float> corr_vals;
    		  
    		  // get L1FastL2L3Residual total correction
    		  jet_corrector_pfL1FastJetL2L3_current->setRho   ( cms3.evt_fixgridfastjet_all_rho() );
    		  jet_corrector_pfL1FastJetL2L3_current->setJetA  ( cms3.pfjets_area().at(iJet)       );
    		  jet_corrector_pfL1FastJetL2L3_current->setJetPt ( pfjet_p4_uncor.pt()               );
    		  jet_corrector_pfL1FastJetL2L3_current->setJetEta( pfjet_p4_uncor.eta()              );
    		  //get actual corrections
    		  corr_vals = jet_corrector_pfL1FastJetL2L3_current->getSubCorrections();
    		  corr      = corr_vals.at(corr_vals.size()-1); // All corrections		  
    		  shift = 0.0;
    		  if (jecUnc_current != 0) {
    		    jecUnc_current->setJetEta(pfjet_p4_uncor.eta()); 
    		    jecUnc_current->setJetPt(pfjet_p4_uncor.pt()*corr); 
    		    double unc = jecUnc_current->getUncertainty(true);
    		    // note that this always checks the "default" filename vector size, not the run-dependent for late 2016F
    		    if( cms3.evt_isRealData() && jetcorr_filenames_pfL1FastJetL2L3.size() == 4 ){
    		      shift = sqrt(unc*unc + pow((corr_vals.at(corr_vals.size()-1)/corr_vals.at(corr_vals.size()-2)-1.),2));	  
    		    }else{
    		      shift = unc;
    		    }
    		  }

    		  // apply new JEC to p4
    		  pfjet_p4_cor = pfjet_p4_uncor * corr;
    		}
    		
    		p4sCorrJets.push_back(pfjet_p4_cor);
    		p4sCorrJets_up.push_back(pfjet_p4_cor*(1.0 + shift));
    		p4sCorrJets_dn.push_back(pfjet_p4_cor*(1.0 - shift));
    		jet_corrfactor.push_back(corr);
    		jet_corrfactor_up.push_back(1.0 + shift);
    		jet_corrfactor_dn.push_back(1.0 - shift);
    
  		  //if((p4sCorrJets.at(iJet).pt() < JET_PT_MIN) && (p4sCorrJets.at(iJet).pt() < BJET_PT_MIN)) continue; 
        //if( (fabs(p4sCorrJets.at(iJet).eta()) > JET_ETA_MAX) && ((fabs(p4sCorrJets.at(iJet).eta()) > BJET_ETA_MAX)) )continue;
        if(p4sCorrJets.at(iJet).pt() < 15 ) continue; 
        if(fabs(p4sCorrJets.at(iJet).eta()) > 5.2) continue;
  		  // note this uses the eta of the jet as stored in CMS3
  		  //  chance for small discrepancies if JEC changes direction slightly..
        if(!isLoosePFJet_Summer16_v1(iJet) && !isSMSScan) continue;
  		  if( isSMSScan && isBadFastsimJet(iJet) ) continue;
  		  passJets.push_back(std::pair<int,float>(iJet, pfjet_p4_cor.pt()));
      }

      // sort passing jets by corrected pt
      std::sort(passJets.begin(), passJets.end(), sortByValue);

  	  if (verbose) cout << "before jet/photon requirements" << endl;
   	  //matched to pfJet with pT > 10 GeV, within cone of dR < 0.3. neutral EM energy fraction > 0.7
   	  for(int iGamma = 0; iGamma < ngamma; iGamma++){
     		if (iGamma>0) continue; // Only care about leading photon.
     
     		float minDR = 0.4;
     		int minIndex = -1;
     		for(unsigned int passIdx = 0; passIdx < passJets.size(); passIdx++){ //loop through jets that passed baseline selections
     	
     		  // int iJet = passJets.at(passIdx);
     		  int iJet = passJets.at(passIdx).first;
     
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
     		}
        else{

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
      //remove ALL jets within dR < 0.4 of an analysis lepton with pt > 20
      vector<int> removedJets; //index of jets to be removed because they overlap with a lepton
      for(unsigned int iLep = 0; iLep < p4sLeptonsForJetCleaning.size(); iLep++){

        const float maxDR = 0.4;
        for(unsigned int passIdx = 0; passIdx < passJets.size(); passIdx++){ //loop through jets that passed baseline selections

          int iJet = passJets.at(passIdx).first;

          if( !(p4sCorrJets.at(iJet).pt()    > JET_PT_MIN || 
            (p4sCorrJets.at(iJet).pt()    > BJET_PT_MIN && getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", iJet) >= BJET_CSV_MED))) continue;
          if( fabs(p4sCorrJets.at(iJet).eta() ) > JET_ETA_MAX  ) continue;
          if( !(isLoosePFJet_Summer16_v1(iJet) || isSMSScan) ) continue;
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
          if(thisDR < maxDR){
            removedJets.push_back(iJet);
          }
        }
      }

  	  if (verbose) cout << "before isr weight loop over jets" << endl;

  	  if( !isData ){

    		bool failbadfastsimjet = false;	  
    		vector <LorentzVector> jets_for_pileup;
    		for(unsigned int iJet = 0; iJet < cms3.pfjets_p4().size(); iJet++){

    		  LorentzVector pfjet_p4_cor = cms3.pfjets_p4().at(iJet);
    		  vector<float> corr_vals;
    		  double corr = 1.0;

    		  if (applyJECfromFile) {

    		    // get uncorrected jet p4 to use as input for corrections
    		    LorentzVector pfjet_p4_uncor = cms3.pfjets_p4().at(iJet) * cms3.pfjets_undoJEC().at(iJet);

    		    // get L1FastL2L3Residual total correction
    		    jet_corrector_pfL1FastJetL2L3_current->setRho   ( cms3.evt_fixgridfastjet_all_rho() );
    		    jet_corrector_pfL1FastJetL2L3_current->setJetA  ( cms3.pfjets_area().at(iJet)       );
    		    jet_corrector_pfL1FastJetL2L3_current->setJetPt ( pfjet_p4_uncor.pt()               );
    		    jet_corrector_pfL1FastJetL2L3_current->setJetEta( pfjet_p4_uncor.eta()              );
    		    //get actual corrections
    		    corr_vals = jet_corrector_pfL1FastJetL2L3_current->getSubCorrections();
    		    corr      = corr_vals.at(corr_vals.size()-1); // All corrections		  

    		    // apply new JEC to p4
    		    pfjet_p4_cor = pfjet_p4_uncor * corr;
    		  }
    		
    		  if(       pfjet_p4_cor.pt()    < JET_PT_MIN       ) continue; 
    		  if( fabs( pfjet_p4_cor.eta() ) > JET_ETA_MAX              ) continue;
    		  if(!isLoosePFJet_Summer16_v1(iJet) && !isSMSScan  ) continue;
    		  if( isSMSScan && isBadFastsimJet(iJet)      ) failbadfastsimjet = true;

    		  bool jetoverlapswithlepton = false;
    		  for(unsigned int iLep = 0; iLep < p4sLeptonsForJetCleaning.size(); iLep++){

    		    float minDR = 0.4;
    		    float thisDR = DeltaR(pfjet_p4_cor.eta(), p4sLeptonsForJetCleaning.at(iLep).eta(), pfjet_p4_cor.phi(), p4sLeptonsForJetCleaning.at(iLep).phi());
    		    if(thisDR < minDR){
    		      minDR = thisDR; 
    		      jetoverlapswithlepton = true;
    		    }
    		  }
    		  
    		  if( jetoverlapswithlepton ) continue;

    		  jets_for_pileup.push_back(pfjet_p4_cor);
        }

    		if( failbadfastsimjet ) continue; // throw away event if fails bad fastsim jet

    		isr_njets  = get_nisrMatch( jets_for_pileup );
    		isr_weight = get_isrWeight( isr_njets       );
    		isr_unc    = get_isrUnc(    isr_njets       );
    		if( currentFileName.Contains("SMS-TChi"  ) ) {
    		  isr_weight = get_isrWeight_ewk(isrboost);
    		  isr_unc = -999.;
    		}
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

          int iJet = passJets.at(passIdx).first;

          if(      !(p4sCorrJets.at(iJet).pt()    > JET_PT_MIN ||
  				 (p4sCorrJets.at(iJet).pt()    > BJET_PT_MIN && getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", iJet) >= BJET_CSV_MED))) continue;
          if( fabs(p4sCorrJets.at(iJet).eta() ) > JET_ETA_MAX  ) continue;
          if( !(isLoosePFJet_Summer16_v1(iJet) || isSMSScan) ) continue;
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
      nJet200MuFrac50DphiMet  = 0;

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

        int iJet = passJets.at(passIdx).first;

        float current_csv_val = getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", iJet);
        float current_muf_val = cms3.pfjets_muonE()[iJet] / (cms3.pfjets_undoJEC().at(iJet)*cms3.pfjets_p4()[iJet].energy());

        //check against list of jets that overlap with a lepton
        bool isOverlapJet = false;
        for(unsigned int j=0; j<removedJets.size(); j++){
          if(iJet == removedJets.at(j)){
            isOverlapJet = true;
            break;
          }
        }
        if(isOverlapJet){ 
          removed_jets_p4.push_back(p4sCorrJets.at(iJet));
          removed_jets_csv.push_back(current_csv_val);
          continue;
        }

        //check against list of jets that overlap with a photon for photon+jets events
        bool isOverlapJetGamma = false;
        for(unsigned int j=0; j<removedJetsGamma.size(); j++){
          if(iJet == removedJetsGamma.at(j)){
            isOverlapJetGamma = true;
            break;
          }
        }
        if(evt_type == 2 && isOverlapJetGamma) {
          removed_jets_p4.push_back(p4sCorrJets.at(iJet)) ;
          removed_jets_csv.push_back(current_csv_val);
          continue;
        }

    		if( verbose ) cout<<"Before filling jet branches"<<endl;

        //Btag Pt always lower than regular jet Pt, but we want to fill the jet collection with all jets and btagged jets. 
        //So first fill jets with anything that is within jet and bjet pt acceptence, eta acceptance always larger for jets than bjets
    		if( p4sCorrJets.at(iJet).pt() > BJET_PT_MIN && abs(p4sCorrJets.at(iJet).eta()) < JET_ETA_MAX ){
     		  if( p4sCorrJets.at(iJet).pt() > JET_PT_MIN ) {
      			jets_p4                                       .push_back(p4sCorrJets.at(iJet));
      			jets_csv                                      .push_back(current_csv_val);
      			jets_muf                                      .push_back(current_muf_val);
    		  }
          //Then we check whether the jet is within the bjet eta acceptence and has 
    		  if( current_csv_val >= BJET_CSV_MED && abs(p4sCorrJets.at(iJet).eta()) < BJET_ETA_MAX ){
      			if( p4sCorrJets.at(iJet).pt() <= JET_PT_MIN ) {
      			  jets_p4                                       .push_back(p4sCorrJets.at(iJet));
      			  jets_csv                                      .push_back(current_csv_val);
      			  jets_muf                                      .push_back(current_muf_val);
      			}
      			jets_medb_p4  .push_back(p4sCorrJets.at(iJet));
    		  }	   

    		  if( !isData ){
            jets_mcFlavour   .push_back(cms3.pfjets_partonFlavour().at(iJet));
    		  	jets_mcHadronFlav.push_back(cms3.pfjets_hadronFlavour().at(iJet));
    		  }

    		  // ad-hoc filter:
    		  //  check for jets with pt > 200, mufrac > 0.5, dphi(jet,MET) > pi - 0.4
    		  if ( (p4sCorrJets.at(iJet).pt() > 200.0) && (current_muf_val > 0.5) && (DeltaPhi(p4sCorrJets.at(iJet).phi(),met_phi) > TMath::Pi() - 0.4) ) {
    		    ++nJet200MuFrac50DphiMet;
    		  }

    		  // require pT > JET_PT_MIN for HT
    		  if( p4sCorrJets.at(iJet).pt() > JET_PT_MIN ){ ht+=p4sCorrJets.at(iJet).pt(); }
    		
    		  if( (current_csv_val >= BJET_CSV_TIGHT) && (fabs(p4sCorrJets.at(iJet).eta()) < BJET_ETA_MAX) && (p4sCorrJets.at(iJet).pt() > BJET_PT_MIN) ){ nBJetTight++; }

    		  if(current_csv_val >= BJET_CSV_MED && (fabs(p4sCorrJets.at(iJet).eta()) < BJET_ETA_MAX) && (p4sCorrJets.at(iJet).pt() > BJET_PT_MIN)) {
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
    		  }
          else{ // fail btag
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
      			  } 
              else {
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
              } 
              else {
        				btagprob_light_UP *= (1. - weight_cent * eff);
        				btagprob_light_DN *= (1. - weight_cent * eff);
        				btagprob_heavy_UP *= (1. - weight_UP * eff);
        				btagprob_heavy_DN *= (1. - weight_DN * eff);
              }
      			}
    		  }
    		
    		  if(current_csv_val >= BJET_CSV_LOOSE && (fabs(p4sCorrJets.at(iJet).eta()) < BJET_ETA_MAX) && (p4sCorrJets.at(iJet).pt() > BJET_PT_MIN)) { nBJetLoose++; }

    		  //require pT > JET_PT_MIN for jet counting
    		  if( p4sCorrJets.at(iJet).pt() > JET_PT_MIN ){ njets++; }
    		}

    		if( verbose ) cout<<"Before filling jet up branches"<<endl;
    		
    		if( (p4sCorrJets_up.at(iJet).pt() > BJET_PT_MIN ) && abs(p4sCorrJets_up.at(iJet).eta()) < JET_ETA_MAX ){
          if( p4sCorrJets_up.at(iJet).pt() > JET_PT_MIN ){ 
            njets_up++;
            jets_up_p4    .push_back(p4sCorrJets_up.at(iJet));
    		    jets_up_csv   .push_back(current_csv_val);
          }
          if( p4sCorrJets_up.at(iJet).pt() > BJET_PT_MIN && fabs(p4sCorrJets_up.at(iJet).eta()) < BJET_ETA_MAX ) { ht_up+=p4sCorrJets_up.at(iJet).pt(); }
    		  if(current_csv_val >= BJET_CSV_TIGHT && fabs(p4sCorrJets_up.at(iJet).eta()) < BJET_ETA_MAX) { nBJetTight_up++; }
    		  if(current_csv_val >= BJET_CSV_MED && fabs(p4sCorrJets_up.at(iJet).eta()) < BJET_ETA_MAX) {
      			nBJetMedium_up++;
      			jets_medb_up_p4.push_back(p4sCorrJets_up.at(iJet));
    		  }
    		  if(current_csv_val >= BJET_CSV_LOOSE && fabs(p4sCorrJets_up.at(iJet).eta()) < BJET_ETA_MAX) { nBJetLoose_up++; }
    		}

    		if( verbose ) cout<<"Before filling jet dn branches"<<endl;
        if( (p4sCorrJets_dn.at(iJet).pt() > BJET_PT_MIN ) && fabs(p4sCorrJets_dn.at(iJet).eta()) < JET_ETA_MAX ){
          if( p4sCorrJets_dn.at(iJet).pt() > JET_PT_MIN ){ 
            njets_dn++;
            jets_dn_p4    .push_back(p4sCorrJets_dn.at(iJet));
            jets_dn_csv   .push_back(current_csv_val);
          }
          if( p4sCorrJets_dn.at(iJet).pt() > BJET_PT_MIN && fabs(p4sCorrJets_dn.at(iJet).eta()) < BJET_ETA_MAX ) { ht_dn+=p4sCorrJets_dn.at(iJet).pt(); }
          if(current_csv_val >= BJET_CSV_TIGHT && fabs(p4sCorrJets_dn.at(iJet).eta()) < BJET_ETA_MAX) { nBJetTight_dn++; }
          if(current_csv_val >= BJET_CSV_MED && fabs(p4sCorrJets_dn.at(iJet).eta()) < BJET_ETA_MAX) {
            nBJetMedium_dn++;
            jets_medb_dn_p4.push_back(p4sCorrJets_dn.at(iJet));
          }
          if(current_csv_val >= BJET_CSV_LOOSE && fabs(p4sCorrJets_dn.at(iJet).eta()) < BJET_ETA_MAX) { nBJetLoose_dn++; }
        }
      }
  	  
  	  if (!isData) {
        weight_btagsf          = btagprob_data     / btagprob_mc;
    		weight_btagsf_heavy_UP = btagprob_heavy_UP / btagprob_mc;
    		weight_btagsf_heavy_DN = btagprob_heavy_DN / btagprob_mc;
    		weight_btagsf_light_UP = btagprob_light_UP / btagprob_mc;
    		weight_btagsf_light_DN = btagprob_light_DN / btagprob_mc;
  	  }
  	  
  	  if( nlep > 0 ) mt_lep1 = MT(lep_pt.at(0), lep_phi.at(0), met_pt, met_phi);
  		
  	  decayedphoton_mt2 = 0;
  	  if( abs(decayedphoton_lep1_p4.eta()) < 2.4 && abs(decayedphoton_lep2_p4.eta()) < 2.4  ){
    		if( (abs(decayedphoton_lep1_p4.eta()) < 1.4 || abs(decayedphoton_lep1_p4.eta()) > 1.6) &&
    			(abs(decayedphoton_lep2_p4.eta()) < 1.4 || abs(decayedphoton_lep2_p4.eta()) > 1.6) ){
    		    decayedphoton_mt2 = MT2( met_pt, met_phi, decayedphoton_lep1_p4, decayedphoton_lep2_p4, 0.0 );
    		}
  	  }

  	  
  	  // add kinematic variables to do with jets leps and photons here
  	  if( lep_p4.size() > 1 && evt_type != 2 ){
    		// MT2J( MET_MAGNITUDE, MET_PHI, P4_LEPTON_1, P4_LEPTON_2, VECT_P4_Jets, MASS_INVISIBLE_PARTICLE, MT2_CALCULATION_METHOD )
    		mt2     = -1.0;
    		mt2_up  = -1.0;
    		mt2_dn  = -1.0;
    		mt2j    = -1.0;
    		mt2b    = -1.0;
    		mt2b_up = -1.0;
    		mt2b_dn = -1.0;

    		mt2    = MT2( met_pt   , met_phi   , lep_p4.at(0), lep_p4.at(1), 0.0 );
    		mt2_up = MT2( met_T1CHS_miniAOD_CORE_up_pt, met_T1CHS_miniAOD_CORE_up_phi, lep_p4.at(0), lep_p4.at(1), 0.0 );
    		mt2_dn = MT2( met_T1CHS_miniAOD_CORE_dn_pt, met_T1CHS_miniAOD_CORE_dn_phi, lep_p4.at(0), lep_p4.at(1), 0.0 );
    		mt2_genmet = MT2( met_genPt   , met_genPhi   , lep_p4.at(0), lep_p4.at(1), 0.0 );
     	
     		if( jets_p4.size() > 1 ){
     		  mt2j = MT2J( met_pt, met_phi, lep_p4.at(0), lep_p4.at(1), jets_p4, 0.0 );
    		}

    		if( jets_medb_p4.size() > 1 ){
     		  mt2b = MT2J( met_pt, met_phi, lep_p4.at(0), lep_p4.at(1), jets_medb_p4, 0.0 );
     		  mt2b_genmet = MT2J( met_genPt, met_genPhi, lep_p4.at(0), lep_p4.at(1), jets_medb_p4, 0.0 );
    		}		
    		if( jets_medb_up_p4.size() > 1 ){
     		  mt2b_up = MT2J( met_T1CHS_miniAOD_CORE_up_pt, met_T1CHS_miniAOD_CORE_up_phi, lep_p4.at(0), lep_p4.at(1), jets_medb_up_p4, 0.0 );
    		}		
    		if( jets_medb_dn_p4.size() > 1 ){
     		  mt2b_dn = MT2J( met_T1CHS_miniAOD_CORE_dn_pt, met_T1CHS_miniAOD_CORE_dn_phi, lep_p4.at(0), lep_p4.at(1), jets_medb_dn_p4, 0.0 );
    		}		

    		sum_mlb = get_sum_mlb();
    		dphi_ll = acos(cos(lep_p4 .at(0).phi() - lep_p4 .at(1).phi()));
  	  }

      //=================================
      // LEPTON SCALE FACTORS
      //=================================
  	  if( !isData ){
    		for( size_t lepind = 0; lepind < lep_p4.size(); lepind++ ){
    		  float min_leppt  = min( 110.0, (double)lep_pt.at(lepind));
    		  float abs_lepeta = abs(lep_eta.at(lepind));

    		  if( abs(lep_pdgId.at(lepind)) == 11 ){			
      			weightsf_lepreco .push_back( h_eleweights_reco->GetBinContent( h_eleweights_reco->FindBin( lep_eta.at(lepind), 100        )) ); // this is a 1d hist in 2 dimensions for some reason
      			weightsf_lepid   .push_back( h_eleweights_id  ->GetBinContent( h_eleweights_id  ->FindBin( min_leppt         , abs_lepeta )) );
      			weightsf_lepiso  .push_back( h_eleweightsiso  ->GetBinContent( h_eleweightsiso  ->FindBin( min_leppt         , abs_lepeta )) );
      			weightsf_lepip   .push_back( 1.0 );// ip weight already accounted for in id weight for electrons
      			weightsf_lepconv .push_back( h_eleweights_conv  ->GetBinContent( h_eleweights_conv  ->FindBin( min_leppt         , abs_lepeta )) );

      			if( isSMSScan ){
      			  weightsf_lepid_FS . push_back( h_eleweights->GetBinContent(h_eleweights->FindBin( min_leppt, abs_lepeta )) );
      			}
            else{
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
      			weightsf_lepconv .push_back( 1.0 );// not used for muons

      			if( isSMSScan ){
      			  weightsf_lepid_FS . push_back( h_muoweights       ->GetBinContent( h_muoweights       ->FindBin( min_leppt, abs_lepeta )) );
      			  weightsf_lepiso_FS. push_back( h_muoweights_FS_iso->GetBinContent( h_muoweights_FS_iso->FindBin( min_leppt, abs_lepeta )) );
      			  weightsf_lepip_FS . push_back( h_muoweights_FS_ip ->GetBinContent( h_muoweights_FS_ip ->FindBin( min_leppt, abs_lepeta )) );

      			}
            else{
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

    		if( njets > 1 ){
    		  mjj_mindphi = 0.0;
    		  float dphi_jetjet = 4.0;
    		  for( int jet1ind = 0; jet1ind < njets-1; jet1ind++ ){
      			for( int jet2ind = jet1ind+1; jet2ind < njets; jet2ind++ ){
      			  if( jets_p4.at(jet1ind).pt() < JET_PT_MIN || jets_p4.at(jet2ind).pt() < JET_PT_MIN ) continue;
      			  float dphi_jet1_jet2 = acos(cos(jets_p4.at(jet1ind).phi() - jets_p4.at(jet2ind).phi()));
      			  if( dphi_jet1_jet2 < dphi_jetjet ){
        				dphi_jetjet = dphi_jet1_jet2;
        				mjj_mindphi = (jets_p4.at(jet1ind) + jets_p4.at(jet2ind)).mass();
      			  }
      			}
    		  }
    		}
    	  
    		mjj = (jets_p4.at(0) + jets_p4.at(1)).mass();
    		dphi_jj = acos(cos(jets_p4.at(0).phi() - jets_p4.at(1).phi()));
    		deta_jj = abs(jets_p4.at(0).eta() - jets_p4.at(1).eta());
    		dR_jj   = sqrt(pow(deta_jj,2) + pow(dphi_jj,2));

    		dphi_metj1 = acos(cos(jets_p4.at(0).phi() - met_phi));
    		dphi_metj2 = acos(cos(jets_p4.at(1).phi() - met_phi));
    		dphi_genmetj1 = acos(cos(jets_p4.at(0).phi() - met_genPhi));
    		dphi_genmetj2 = acos(cos(jets_p4.at(1).phi() - met_genPhi));

    		if( jets_medb_p4.size() > 1 ){
    		  mbb_bpt = (jets_medb_p4.at(0) + jets_medb_p4.at(1)).mass();
    		  mbb_csv = mbb_highest_csv( jets_p4, jets_csv );
    		}	  
  	  }
  	  
  	  if( jets_up_p4.size() > 1 ){
    		if( njets_up > 1 ){
    		  mjj_mindphi_up = 0.0;
    		  float dphi_jetjet = 4.0;
    		  for( int jet1ind = 0; jet1ind < njets_up-1; jet1ind++ ){
      			for( int jet2ind = jet1ind+1; jet2ind < njets_up; jet2ind++ ){
      			  if( jets_up_p4.at(jet1ind).pt() < JET_PT_MIN || jets_up_p4.at(jet2ind).pt() < JET_PT_MIN ) continue;
      			  float dphi_jet1_jet2 = acos(cos(jets_up_p4.at(jet1ind).phi() - jets_up_p4.at(jet2ind).phi()));
      			  if( dphi_jet1_jet2 < dphi_jetjet ){
        				dphi_jetjet = dphi_jet1_jet2;
        				mjj_mindphi_up = (jets_up_p4.at(jet1ind) + jets_up_p4.at(jet2ind)).mass();
      			  }
      			}
    		  }
    		}
    	  
    		mjj_up = (jets_up_p4.at(0) + jets_up_p4.at(1)).mass();
    		dphi_jj_up = acos(cos(jets_up_p4.at(0).phi() - jets_up_p4.at(1).phi()));
    		deta_jj_up = abs(jets_up_p4.at(0).eta() - jets_up_p4.at(1).eta());
    		dR_jj_up   = sqrt(pow(deta_jj_up,2) + pow(dphi_jj_up,2));

    		dphi_metj1_up = acos(cos(jets_up_p4.at(0).phi() - met_T1CHS_miniAOD_CORE_up_phi));
    		dphi_metj2_up = acos(cos(jets_up_p4.at(1).phi() - met_T1CHS_miniAOD_CORE_up_phi));

    		if( jets_medb_up_p4.size() > 1 ){
    		  mbb_bpt_up = (jets_medb_up_p4.at(0) + jets_medb_up_p4.at(1)).mass();	
    		  mbb_csv_up = mbb_highest_csv( jets_up_p4, jets_up_csv );	
    		}	  
  	  }

  	  if( jets_dn_p4.size() > 1 ){

    		if( njets_dn > 1 ){
    		  mjj_mindphi_dn = 0.0;
    		  float dphi_jetjet = 4.0;
    		  for( int jet1ind = 0; jet1ind < njets_dn-1; jet1ind++ ){
      			for( int jet2ind = jet1ind+1; jet2ind < njets_dn; jet2ind++ ){
      			  if( jets_dn_p4.at(jet1ind).pt() < JET_PT_MIN || jets_dn_p4.at(jet2ind).pt() < JET_PT_MIN ) continue;
      			  float dphi_jet1_jet2 = acos(cos(jets_dn_p4.at(jet1ind).phi() - jets_dn_p4.at(jet2ind).phi()));
      			  if( dphi_jet1_jet2 < dphi_jetjet ){
        				dphi_jetjet = dphi_jet1_jet2;
        				mjj_mindphi_dn = (jets_dn_p4.at(jet1ind) + jets_dn_p4.at(jet2ind)).mass();
      			  }
      			}
    		  }
    		}
    	  
    		mjj_dn = (jets_dn_p4.at(0) + jets_dn_p4.at(1)).mass();
    		dphi_jj_dn = acos(cos(jets_dn_p4.at(0).phi() - jets_dn_p4.at(1).phi()));
    		deta_jj_dn = abs(jets_dn_p4.at(0).eta() - jets_dn_p4.at(1).eta());
    		dR_jj_dn   = sqrt(pow(deta_jj_dn,2) + pow(dphi_jj_dn,2));

    		dphi_metj1_dn = acos(cos(jets_dn_p4.at(0).phi() - met_T1CHS_miniAOD_CORE_dn_phi));
    		dphi_metj2_dn = acos(cos(jets_dn_p4.at(1).phi() - met_T1CHS_miniAOD_CORE_dn_phi));

    		if( jets_medb_dn_p4.size() > 1 ){
    		  mbb_bpt_dn = (jets_medb_dn_p4.at(0) + jets_medb_dn_p4.at(1)).mass();
    		  mbb_csv_dn = mbb_highest_csv( jets_dn_p4, jets_dn_csv );
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
      nisoTrack_stop = 0;
  	  nisoTrack_PFLep5_woverlaps  = 0;
  	  nisoTrack_PFHad10_woverlaps = 0;
  	  nhighPtPFcands = 0;

      nisoTrack_mt2_cleaned_VVV_cutbased_veto              = 0;
      nisoTrack_mt2_cleaned_VVV_cutbased_veto_noiso        = 0;
      nisoTrack_mt2_cleaned_VVV_cutbased_veto_noiso_noip   = 0;
      nisoTrack_mt2_cleaned_VVV_cutbased_fo                = 0;
      nisoTrack_mt2_cleaned_VVV_cutbased_fo_noiso          = 0;
      nisoTrack_mt2_cleaned_VVV_cutbased_tight_noiso       = 0;
      nisoTrack_mt2_cleaned_VVV_cutbased_tight             = 0;
      nisoTrack_mt2_cleaned_VVV_MVAbased_tight_noiso       = 0;
      nisoTrack_mt2_cleaned_VVV_MVAbased_tight             = 0;
      nisoTrack_mt2_cleaned_VVV_baseline                   = 0;

      //------------------------------------
      // Compute Kinematic Vars For PFCands
      //------------------------------------
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

    		// save high pt pf cands: all with pt > 300, pf muons with pt > 50
    		if ( (pfcand_p4.pt() > 300.) || (pfcand_p4.pt() > 50. && abs(cms3.pfcands_particleId().at(pfind)) == 13) ) {
    		  ++nhighPtPFcands;
    		  highPtPFcands_p4.push_back(pfcand_p4);
    		  highPtPFcands_dz.push_back(cms3.pfcands_dz().at(pfind));
    		  highPtPFcands_pdgId.push_back(cms3.pfcands_particleId().at(pfind));
    		}
    		
        if(      cms3.pfcands_charge().at(pfind)  == 0  ) continue;
        if( fabs(cms3.pfcands_dz()    .at(pfind)) >  0.1) continue;
        if(      cms3.pfcands_fromPV().at(pfind)  <= 1  ) continue;

        float cand_pt = cms3.pfcands_p4().at(pfind).pt();
        if(cand_pt < 5) continue;

        // isotrack a la MT2
        int  pdgId = abs( cms3.pfcands_particleId().at( pfind ) );

        bool leptonoverlaps = false;

        bool leptonoverlaps_VVV_cutbased_veto = false;
        bool leptonoverlaps_VVV_cutbased_veto_noiso = false;
        bool leptonoverlaps_VVV_cutbased_veto_noiso_noip = false;
        bool leptonoverlaps_VVV_cutbased_fo = false;
        bool leptonoverlaps_VVV_cutbased_fo_noiso = false;
        bool leptonoverlaps_VVV_cutbased_tight_noiso = false;
        bool leptonoverlaps_VVV_cutbased_tight = false;
        bool leptonoverlaps_VVV_MVAbased_tight_noiso = false;
        bool leptonoverlaps_VVV_MVAbased_tight = false;
        bool leptonoverlaps_VVV_baseline = false;


        if( evt_type != 2 ){
          for( size_t lepind = 0; lepind < lep_p4.size(); lepind++ ){
            //if( lepind >= 2 ) break; // consider all analysis leptons
            if( sqrt( pow(cms3.pfcands_p4().at(pfind).eta() - lep_p4.at(lepind).eta(), 2) +
                  pow(acos(cos(cms3.pfcands_p4().at(pfind).phi() - lep_p4.at(lepind).phi())), 2) ) < 0.01 ){
              leptonoverlaps = true;
              if (lep_pass_VVV_cutbased_veto.at(lepind))            leptonoverlaps_VVV_cutbased_veto = true;
              if (lep_pass_VVV_cutbased_veto_noiso.at(lepind))      leptonoverlaps_VVV_cutbased_veto_noiso = true;
              if (lep_pass_VVV_cutbased_veto_noiso_noip.at(lepind)) leptonoverlaps_VVV_cutbased_veto_noiso_noip = true;
              if (lep_pass_VVV_cutbased_fo.at(lepind))              leptonoverlaps_VVV_cutbased_fo = true;
              if (lep_pass_VVV_cutbased_fo_noiso.at(lepind))        leptonoverlaps_VVV_cutbased_fo_noiso = true;
              if (lep_pass_VVV_cutbased_tight_noiso.at(lepind))     leptonoverlaps_VVV_cutbased_tight_noiso = true;
              if (lep_pass_VVV_cutbased_tight.at(lepind))           leptonoverlaps_VVV_cutbased_tight = true;
              if (lep_pass_VVV_MVAbased_tight_noiso.at(lepind))     leptonoverlaps_VVV_MVAbased_tight_noiso = true;
              if (lep_pass_VVV_MVAbased_tight.at(lepind))           leptonoverlaps_VVV_MVAbased_tight = true;
              if (lep_pass_VVV_baseline.at(lepind))                 leptonoverlaps_VVV_baseline = true;

              //cout<<"Found match for track, lepton passed -- lep_pass_VVV_cutbased_veto: "<<lep_pass_VVV_cutbased_veto.at(lepind)<<" lep_pass_VVV_cutbased_fo: "<<lep_pass_VVV_cutbased_fo.at(lepind)<<" lep_pass_VVV_MVAbased_tight_noiso: "<<lep_pass_VVV_MVAbased_tight_noiso.at(lepind)<<endl;
            }
          }
        }

        //cout<<"PROIR: nisoTrack_mt2_cleaned_VVV_cutbased_veto: "<<nisoTrack_mt2_cleaned_VVV_cutbased_veto<<" nisoTrack_mt2_cleaned_VVV_cutbased_fo: "<< nisoTrack_mt2_cleaned_VVV_cutbased_fo<<" nisoTrack_mt2_cleaned_VVV_MVAbased_tight_noiso: "<<nisoTrack_mt2_cleaned_VVV_MVAbased_tight_noiso<<endl;
        
        float absiso03 = TrackIso( pfind, 0.3, 0.0, true, false );
        if(  absiso03 < min( 0.2 * cand_pt, 8.0 ) ){

          //cout<<"Iso is good"<<endl;
          // nuclear options for photon sample
          nisoTrack_5gev++;

      		
      		if( (cand_pt > 5.) && (pdgId == 11 || pdgId == 13) ){
            if (absiso03/cand_pt < 0.2) {
      		    nisoTrack_PFLep5_woverlaps++;
      		    if( !leptonoverlaps ) nisoTrack_mt2++;

              if( !leptonoverlaps_VVV_cutbased_veto )               nisoTrack_mt2_cleaned_VVV_cutbased_veto++;
              if( !leptonoverlaps_VVV_cutbased_veto_noiso )         nisoTrack_mt2_cleaned_VVV_cutbased_veto_noiso++;
              if( !leptonoverlaps_VVV_cutbased_veto_noiso_noip )    nisoTrack_mt2_cleaned_VVV_cutbased_veto_noiso_noip++;
              if( !leptonoverlaps_VVV_cutbased_fo )                 nisoTrack_mt2_cleaned_VVV_cutbased_fo++;
              if( !leptonoverlaps_VVV_cutbased_fo_noiso )           nisoTrack_mt2_cleaned_VVV_cutbased_fo_noiso++;
              if( !leptonoverlaps_VVV_cutbased_tight_noiso )        nisoTrack_mt2_cleaned_VVV_cutbased_tight_noiso++;
              if( !leptonoverlaps_VVV_cutbased_tight )              nisoTrack_mt2_cleaned_VVV_cutbased_tight++;
              if( !leptonoverlaps_VVV_MVAbased_tight_noiso )        nisoTrack_mt2_cleaned_VVV_MVAbased_tight_noiso++;
              if( !leptonoverlaps_VVV_MVAbased_tight )              nisoTrack_mt2_cleaned_VVV_MVAbased_tight++;
              if( !leptonoverlaps_VVV_baseline )                    nisoTrack_mt2_cleaned_VVV_baseline++;
            }
      		}
      		
      		if( cand_pt > 10. && pdgId == 211 ){ 
      		  if (absiso03/cand_pt < 0.1 ){
              nisoTrack_PFHad10_woverlaps++;
      		    if( !leptonoverlaps ) nisoTrack_mt2++;

              if( !leptonoverlaps_VVV_cutbased_veto )               nisoTrack_mt2_cleaned_VVV_cutbased_veto++;
              if( !leptonoverlaps_VVV_cutbased_veto_noiso )         nisoTrack_mt2_cleaned_VVV_cutbased_veto_noiso++;
              if( !leptonoverlaps_VVV_cutbased_veto_noiso_noip )    nisoTrack_mt2_cleaned_VVV_cutbased_veto_noiso_noip++;
              if( !leptonoverlaps_VVV_cutbased_fo )                 nisoTrack_mt2_cleaned_VVV_cutbased_fo++;
              if( !leptonoverlaps_VVV_cutbased_fo_noiso )           nisoTrack_mt2_cleaned_VVV_cutbased_fo_noiso++;
              if( !leptonoverlaps_VVV_cutbased_tight_noiso )        nisoTrack_mt2_cleaned_VVV_cutbased_tight_noiso++;
              if( !leptonoverlaps_VVV_cutbased_tight )              nisoTrack_mt2_cleaned_VVV_cutbased_tight++;
              if( !leptonoverlaps_VVV_MVAbased_tight_noiso )        nisoTrack_mt2_cleaned_VVV_MVAbased_tight_noiso++;
              if( !leptonoverlaps_VVV_MVAbased_tight )              nisoTrack_mt2_cleaned_VVV_MVAbased_tight++;
              if( !leptonoverlaps_VVV_baseline )                    nisoTrack_mt2_cleaned_VVV_baseline++;
            }
      		}
        }

        //cout<<"AFTER: nisoTrack_mt2_cleaned_VVV_cutbased_veto: "<<nisoTrack_mt2_cleaned_VVV_cutbased_veto<<" nisoTrack_mt2_cleaned_VVV_cutbased_fo: "<< nisoTrack_mt2_cleaned_VVV_cutbased_fo<<" nisoTrack_mt2_cleaned_VVV_MVAbased_tight_noiso: "<<nisoTrack_mt2_cleaned_VVV_MVAbased_tight_noiso<<endl;


        //IsoTrack Stop
        float absisoDZ = TrackIso( pfind, 0.3, 0.1);
        if( (pdgId == 11 || pdgId == 13) ){
          if (cand_pt < 5.) continue;
          else{
            if (absisoDZ/cand_pt < 0.2){
              if( !leptonoverlaps ) nisoTrack_stop++;
            }
          }
        }
        else if ( pdgId == 211 ) {
          if (cand_pt < 10.) continue;
          else if (cand_pt <= 60.){
            if (absisoDZ/cand_pt < 0.1){
              if( !leptonoverlaps ) nisoTrack_stop++;
            }
          }
          else{ //pt > 60
            if (absisoDZ < 6.0){
              if( !leptonoverlaps ) nisoTrack_stop++;
            }
          }
        }


  	  } // loop over pfcands
  	  
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

      //TAUS
      // selection here is the multilepton Tight selection, to preserve orthogonality with them
      // we don't apply their dxy, dz cuts since we don't have the vars.  That makes us looser than them anyway
      nTaus20 = 0;
      for(unsigned int iTau = 0; iTau < cms3.taus_pf_p4().size(); iTau++){
        if(cms3.taus_pf_p4().at(iTau).pt() < 20.0) continue; 
        if(fabs(cms3.taus_pf_p4().at(iTau).eta()) > 2.3) continue; 
        if (!cms3.passTauID("byTightIsolationMVArun2v1DBoldDMwLT", iTau)) continue; // HPS, Tight MVA iso
        if (!cms3.passTauID("againstElectronLooseMVA6", iTau)) continue; // electron removal

        // check for overlap with analysis leptons
        bool leptonoverlaps = false;
        for( size_t lepind = 0; lepind < lep_p4.size(); lepind++ ){
          if( sqrt( pow(cms3.taus_pf_p4().at(iTau).eta() - lep_p4.at(lepind).eta(), 2) +
        	  pow(acos(cos(cms3.taus_pf_p4().at(iTau).phi() - lep_p4.at(lepind).phi())), 2) ) < 0.4 ){
            leptonoverlaps = true;
            break;
          }
        }
        if (leptonoverlaps) continue;

        nTaus20++;
      }
  	  
      FillBabyNtuple();
	  }//end loop on events in a file
  
    delete tree;
    f.Close();

    if (applyJECfromFile) {
      delete jet_corrector_pfL1FastJetL2L3;
      delete jecUnc;
      if (jet_corrector_pfL1FastJetL2L3_postrun278802) delete jet_corrector_pfL1FastJetL2L3_postrun278802;
      if (jecUnc_postrun278802) delete jecUnc_postrun278802;
    }  
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
  BabyTree_->Branch("evt_dataset", "std::vector <TString>", &evt_dataset);
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

  BabyTree_->Branch("nJet200MuFrac50DphiMet", &nJet200MuFrac50DphiMet );
  
  BabyTree_->Branch("nMuons10", &nMuons10 );
  BabyTree_->Branch("nBadMuons20", &nBadMuons20 );
  BabyTree_->Branch("nElectrons10", &nElectrons10 );
  BabyTree_->Branch("nGammas20", &nGammas20 );
  BabyTree_->Branch("nTaus20", &nTaus20 );

  BabyTree_->Branch("met_pt"      , &met_pt       );
  BabyTree_->Branch("met_phi"     , &met_phi      );
  BabyTree_->Branch("met_calo_pt" , &met_calo_pt  );
  BabyTree_->Branch("met_calo_phi", &met_calo_phi );
  BabyTree_->Branch("met_miniaod_pt" , &met_miniaod_pt  );
  BabyTree_->Branch("met_miniaod_phi", &met_miniaod_phi );
  BabyTree_->Branch("met_muegclean_pt" , &met_muegclean_pt  );
  BabyTree_->Branch("met_muegclean_phi", &met_muegclean_phi );
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

  BabyTree_->Branch("Flag_badMuonFilter"                , &Flag_badMuonFilter               );
  BabyTree_->Branch("Flag_badChargedCandidateFilter"    , &Flag_badChargedCandidateFilter   );
  BabyTree_->Branch("Flag_badMuonFilterv2"              , &Flag_badMuonFilterv2             );
  BabyTree_->Branch("Flag_badChargedCandidateFilterv2"  , &Flag_badChargedCandidateFilterv2 );
  BabyTree_->Branch("Flag_badMuons"                     , &Flag_badMuons                    ); 
  BabyTree_->Branch("Flag_duplicateMuons"               , &Flag_duplicateMuons              );   
  BabyTree_->Branch("Flag_noBadMuons"                   , &Flag_noBadMuons                  );  
		
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
  BabyTree_->Branch("HLT_MuEG_noiso_2" , &HLT_MuEG_noiso_2 );

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
  BabyTree_->Branch("HLT_DoubleMu_noiso_27_8"     , &HLT_DoubleMu_noiso_27_8     );
  BabyTree_->Branch("HLT_DoubleMu_noiso_30_11"    , &HLT_DoubleMu_noiso_30_11    );
  BabyTree_->Branch("HLT_DoubleMu_noiso_40_11"    , &HLT_DoubleMu_noiso_40_11    );
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

  BabyTree_->Branch("nVetoEl_relIso03EAless01" , &nVetoEl_relIso03EAless01 );
  BabyTree_->Branch("nVetoEl_relIso03EAless02" , &nVetoEl_relIso03EAless02 );
  BabyTree_->Branch("nVetoEl_relIso03EAless03" , &nVetoEl_relIso03EAless03 );
  BabyTree_->Branch("nVetoEl_relIso03EAless04" , &nVetoEl_relIso03EAless04 );
  BabyTree_->Branch("nVetoMu_relIso03EAless01" , &nVetoMu_relIso03EAless01 );
  BabyTree_->Branch("nVetoMu_relIso03EAless02" , &nVetoMu_relIso03EAless02 );
  BabyTree_->Branch("nVetoMu_relIso03EAless03" , &nVetoMu_relIso03EAless03 );
  BabyTree_->Branch("nVetoMu_relIso03EAless04" , &nVetoMu_relIso03EAless04 );

  
  BabyTree_->Branch("lep_p4"           , &lep_p4         );
  BabyTree_->Branch("lep_pt"           , "std::vector< Float_t >"       , &lep_pt         );
  BabyTree_->Branch("lep_eta"          , "std::vector< Float_t >"       , &lep_eta        );
  BabyTree_->Branch("lep_phi"          , "std::vector< Float_t >"       , &lep_phi        );
  BabyTree_->Branch("lep_mass"         , "std::vector< Float_t >"       , &lep_mass       );
  BabyTree_->Branch("lep_charge"       , "std::vector< Int_t >"         , &lep_charge     );
  
  //New vars for testing WWW
  BabyTree_->Branch("lep_3ch_agree"            , "std::vector< Bool_t  > " , &lep_3ch_agree             );
  BabyTree_->Branch("lep_isFromW"              , "std::vector< Bool_t   > " , &lep_isFromW               );
  BabyTree_->Branch("lep_isFromZ"              , "std::vector< Bool_t   > " , &lep_isFromZ               );
  BabyTree_->Branch("lep_isFromB"              , "std::vector< Bool_t   > " , &lep_isFromB               );
  BabyTree_->Branch("lep_isFromC"              , "std::vector< Bool_t   > " , &lep_isFromC               );
  BabyTree_->Branch("lep_isFromL"              , "std::vector< Bool_t   > " , &lep_isFromL               );
  BabyTree_->Branch("lep_isFromLF"             , "std::vector< Bool_t   > " , &lep_isFromLF              );
  BabyTree_->Branch("lep_closest_jet_p4"       , &lep_closest_jet_p4 );
  BabyTree_->Branch("lep_ptRatio"              , "std::vector< Double_t >" , &lep_ptRatio               );
  BabyTree_->Branch("lep_motherIdSS"           , "std::vector< Int_t    >" , &lep_motherIdSS            );
  BabyTree_->Branch("lep_genPart_index"        , "std::vector< Int_t    >" , &lep_genPart_index         );
  BabyTree_->Branch("lep_coneCorrPt"           , "std::vector< Double_t >" , &lep_coneCorrPt            );
  BabyTree_->Branch("lep_ptRel"                , "std::vector< Double_t >" , &lep_ptRel                 );
  BabyTree_->Branch("lep_relIso03"             , "std::vector< Double_t >" , &lep_relIso03              );
  BabyTree_->Branch("lep_relIso03DB"           , "std::vector< Double_t >" , &lep_relIso03DB            );
  BabyTree_->Branch("lep_relIso03EA"           , "std::vector< Double_t >" , &lep_relIso03EA            );
  BabyTree_->Branch("lep_relIso03EAv2"         , "std::vector< Double_t >" , &lep_relIso03EAv2          );
  BabyTree_->Branch("lep_relIso04DB"           , "std::vector< Double_t >" , &lep_relIso04DB            );
  BabyTree_->Branch("lep_relIso04EA"           , "std::vector< Double_t >" , &lep_relIso04EA            );
  BabyTree_->Branch("lep_relIso04EAv2"         , "std::vector< Double_t >" , &lep_relIso04EAv2          );
  BabyTree_->Branch("lep_miniRelIsoCMS3_EA"    , "std::vector< Double_t >" , &lep_miniRelIsoCMS3_EA     );
  BabyTree_->Branch("lep_miniRelIsoCMS3_EAv2"  , "std::vector< Double_t >" , &lep_miniRelIsoCMS3_EAv2   );
  BabyTree_->Branch("lep_miniRelIsoCMS3_DB"    , "std::vector< Double_t >" , &lep_miniRelIsoCMS3_DB     );

  BabyTree_->Branch("lep_pass_VVV_cutbased_veto"              , "std::vector< Bool_t  > " , &lep_pass_VVV_cutbased_veto             );
  BabyTree_->Branch("lep_pass_VVV_cutbased_veto_noiso"        , "std::vector< Bool_t  > " , &lep_pass_VVV_cutbased_veto_noiso       );
  BabyTree_->Branch("lep_pass_VVV_cutbased_veto_noiso_noip"   , "std::vector< Bool_t  > " , &lep_pass_VVV_cutbased_veto_noiso_noip  );
  BabyTree_->Branch("lep_pass_VVV_cutbased_fo"                , "std::vector< Bool_t  > " , &lep_pass_VVV_cutbased_fo               );
  BabyTree_->Branch("lep_pass_VVV_cutbased_fo_noiso"          , "std::vector< Bool_t  > " , &lep_pass_VVV_cutbased_fo_noiso         );
  BabyTree_->Branch("lep_pass_VVV_cutbased_tight_noiso"       , "std::vector< Bool_t  > " , &lep_pass_VVV_cutbased_tight_noiso      );
  BabyTree_->Branch("lep_pass_VVV_cutbased_tight"             , "std::vector< Bool_t  > " , &lep_pass_VVV_cutbased_tight            );
  BabyTree_->Branch("lep_pass_VVV_MVAbased_tight_noiso"       , "std::vector< Bool_t  > " , &lep_pass_VVV_MVAbased_tight_noiso      );
  BabyTree_->Branch("lep_pass_VVV_MVAbased_tight"             , "std::vector< Bool_t  > " , &lep_pass_VVV_MVAbased_tight            );
  BabyTree_->Branch("lep_pass_VVV_baseline"                   , "std::vector< Bool_t  > " , &lep_pass_VVV_baseline                  );

  BabyTree_->Branch("nlep_VVV_cutbased_veto"             , &nlep_VVV_cutbased_veto             , "nlep_VVV_cutbased_veto/I" );
  BabyTree_->Branch("nlep_VVV_cutbased_veto_noiso"       , &nlep_VVV_cutbased_veto_noiso       , "nlep_VVV_cutbased_veto_noiso/I" );
  BabyTree_->Branch("nlep_VVV_cutbased_veto_noiso_noip"  , &nlep_VVV_cutbased_veto_noiso_noip  , "nlep_VVV_cutbased_veto_noiso_noip/I" );
  BabyTree_->Branch("nlep_VVV_cutbased_fo"               , &nlep_VVV_cutbased_fo               , "nlep_VVV_cutbased_fo/I" );
  BabyTree_->Branch("nlep_VVV_cutbased_fo_noiso"         , &nlep_VVV_cutbased_fo_noiso         , "nlep_VVV_cutbased_fo_noiso/I" );
  BabyTree_->Branch("nlep_VVV_cutbased_tight_noiso"      , &nlep_VVV_cutbased_tight_noiso      , "nlep_VVV_cutbased_tight_noiso/I" );
  BabyTree_->Branch("nlep_VVV_cutbased_tight"            , &nlep_VVV_cutbased_tight            , "nlep_VVV_cutbased_tight/I" );
  BabyTree_->Branch("nlep_VVV_MVAbased_tight_noiso"      , &nlep_VVV_MVAbased_tight_noiso      , "nlep_VVV_MVAbased_tight_noiso/I" );
  BabyTree_->Branch("nlep_VVV_MVAbased_tight"            , &nlep_VVV_MVAbased_tight            , "nlep_VVV_MVAbased_tight/I" );
  BabyTree_->Branch("nlep_VVV_baseline"                  , &nlep_VVV_baseline                  , "nlep_VVV_baseline/I" );

  BabyTree_->Branch("lep_pdgId"        , "std::vector< Int_t >"         , &lep_pdgId      );
  BabyTree_->Branch("lep_mc_Id"        , "std::vector< Int_t >"         , &lep_mc_Id      );
  BabyTree_->Branch("lep_dxy"          , "std::vector< Float_t >"       , &lep_dxy        );
  BabyTree_->Branch("lep_ip3d"         , "std::vector< Float_t >"       , &lep_ip3d       );
  BabyTree_->Branch("lep_ip3derr"      , "std::vector< Float_t >"       , &lep_ip3derr    );
  BabyTree_->Branch("lep_etaSC"        , "std::vector< Float_t >"       , &lep_etaSC      );
  BabyTree_->Branch("lep_dz"           , "std::vector< Float_t >"       , &lep_dz         );
  BabyTree_->Branch("lep_tightId"      , "std::vector< Int_t >"         , &lep_tightId    );
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

  BabyTree_->Branch("nisoTrack_mt2_cleaned_VVV_cutbased_veto"  ,             &nisoTrack_mt2_cleaned_VVV_cutbased_veto             );
  BabyTree_->Branch("nisoTrack_mt2_cleaned_VVV_cutbased_veto_noiso"  ,       &nisoTrack_mt2_cleaned_VVV_cutbased_veto_noiso       );
  BabyTree_->Branch("nisoTrack_mt2_cleaned_VVV_cutbased_veto_noiso_noip"  ,  &nisoTrack_mt2_cleaned_VVV_cutbased_veto_noiso_noip  );
  BabyTree_->Branch("nisoTrack_mt2_cleaned_VVV_cutbased_fo"  ,               &nisoTrack_mt2_cleaned_VVV_cutbased_fo               );
  BabyTree_->Branch("nisoTrack_mt2_cleaned_VVV_cutbased_fo_noiso"  ,         &nisoTrack_mt2_cleaned_VVV_cutbased_fo_noiso         );
  BabyTree_->Branch("nisoTrack_mt2_cleaned_VVV_cutbased_tight_noiso"  ,      &nisoTrack_mt2_cleaned_VVV_cutbased_tight_noiso      );
  BabyTree_->Branch("nisoTrack_mt2_cleaned_VVV_cutbased_tight"  ,            &nisoTrack_mt2_cleaned_VVV_cutbased_tight            );
  BabyTree_->Branch("nisoTrack_mt2_cleaned_VVV_MVAbased_tight_noiso"  ,      &nisoTrack_mt2_cleaned_VVV_MVAbased_tight_noiso      );
  BabyTree_->Branch("nisoTrack_mt2_cleaned_VVV_MVAbased_tight"  ,            &nisoTrack_mt2_cleaned_VVV_MVAbased_tight            );
  BabyTree_->Branch("nisoTrack_mt2_cleaned_VVV_baseline"  ,                  &nisoTrack_mt2_cleaned_VVV_baseline                  );

  BabyTree_->Branch("nisoTrack_stop"  , &nisoTrack_stop  );
  BabyTree_->Branch("nisoTrack_PFLep5_woverlaps"  , &nisoTrack_PFLep5_woverlaps  );
  BabyTree_->Branch("nisoTrack_PFHad10_woverlaps" , &nisoTrack_PFHad10_woverlaps );

  BabyTree_->Branch("ngamma"             , &ngamma        , "ngamma/I" );
  BabyTree_->Branch("gamma_p4"           , &gamma_p4    );
  BabyTree_->Branch("gamma_pt"           , "std::vector <Float_t>" , &gamma_pt           );
  BabyTree_->Branch("gamma_eta"          , "std::vector <Float_t>" , &gamma_eta          );
  BabyTree_->Branch("gamma_phi"          , "std::vector <Float_t>" , &gamma_phi          );
  BabyTree_->Branch("gamma_mass"         , "std::vector <Float_t>" , &gamma_mass         );
  BabyTree_->Branch("gamma_mcMatchId"    , "std::vector <Int_t  >" , &gamma_mcMatchId    );
  BabyTree_->Branch("gamma_genPt"        , "std::vector <Float_t>" , &gamma_genPt        );
  BabyTree_->Branch("gamma_genIso"       , "std::vector <Float_t>" , &gamma_genIso       );
  BabyTree_->Branch("gamma_chHadIso"     , "std::vector <Float_t>" , &gamma_chHadIso     );
  BabyTree_->Branch("gamma_neuHadIso"    , "std::vector <Float_t>" , &gamma_neuHadIso    );
  BabyTree_->Branch("gamma_phIso"        , "std::vector <Float_t>" , &gamma_phIso        );
  BabyTree_->Branch("gamma_sigmaIetaIeta", "std::vector <Float_t>" , &gamma_sigmaIetaIeta);
  BabyTree_->Branch("gamma_r9"           , "std::vector <Float_t>" , &gamma_r9           );
  BabyTree_->Branch("gamma_hOverE"       , "std::vector <Float_t>" , &gamma_hOverE       );
  BabyTree_->Branch("gamma_hOverE_online", "std::vector <Float_t>" , &gamma_hOverE_online);
  BabyTree_->Branch("gamma_idCutBased"   , "std::vector <Int_t  >" , &gamma_idCutBased   );
  BabyTree_->Branch("gamma_ecpfclusiso"                            , &gamma_ecpfclusiso  );
  BabyTree_->Branch("gamma_hcpfclusiso"                            , &gamma_hcpfclusiso  );
  BabyTree_->Branch("gamma_hollowtkiso03"                          , &gamma_hollowtkiso03);
  BabyTree_->Branch("gamma_genIsPromptFinalState"                  , &gamma_genIsPromptFinalState);
  BabyTree_->Branch("gamma_drMinParton"                            , &gamma_drMinParton);

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

//----- JETS - pt > JET_PT_MIN, eta < 2.4
  BabyTree_->Branch("njets"           , &njets             );
  BabyTree_->Branch("jets_p4"         , &jets_p4           );
  BabyTree_->Branch("removed_jets_p4" , &removed_jets_p4   );
  BabyTree_->Branch("removed_jets_csv", &removed_jets_csv  );
  BabyTree_->Branch("jets_medb_p4"    , &jets_medb_p4      );

  BabyTree_->Branch("njets_up"        , &njets_up        );
  BabyTree_->Branch("jets_up_p4"      , &jets_up_p4      );
  BabyTree_->Branch("jets_medb_up_p4" , &jets_medb_up_p4 );
  BabyTree_->Branch("jets_csv"        , &jets_csv        );
  BabyTree_->Branch("jets_up_csv"     , &jets_up_csv     );

  BabyTree_->Branch("njets_dn"        , &njets_dn        );
  BabyTree_->Branch("jets_dn_p4"      , &jets_dn_p4      );
  BabyTree_->Branch("jets_medb_dn_p4" , &jets_medb_dn_p4 );
  BabyTree_->Branch("jets_dn_csv"     , &jets_dn_csv     );

  BabyTree_->Branch("jets_muf"          , &jets_muf          );
  BabyTree_->Branch("jets_mcFlavour"    , &jets_mcFlavour    );
  BabyTree_->Branch("jets_mcHadronFlav" , &jets_mcHadronFlav );

//----- HIGH PT PF CANDS
  BabyTree_->Branch("nhighPtPFcands"           , &nhighPtPFcands        );
  BabyTree_->Branch("highPtPFcands_p4"         , &highPtPFcands_p4      );
  BabyTree_->Branch("highPtPFcands_dz"         , &highPtPFcands_dz      );
  BabyTree_->Branch("highPtPFcands_pdgId"      , &highPtPFcands_pdgId   );

  BabyTree_->Branch("ht"    , &ht    );
  BabyTree_->Branch("ht_up" , &ht_up );
  BabyTree_->Branch("ht_dn" , &ht_dn );

  BabyTree_->Branch("metsig_unofficial"    , &metsig_unofficial    );
  BabyTree_->Branch("metsig_unofficial_up" , &metsig_unofficial_up );
  BabyTree_->Branch("metsig_unofficial_dn" , &metsig_unofficial_dn );

  BabyTree_->Branch("mt_lep1" , &mt_lep1 );
  BabyTree_->Branch("mt2"     , &mt2     );
  BabyTree_->Branch("mt2_up"  , &mt2_up  );
  BabyTree_->Branch("mt2_dn"  , &mt2_dn  );
  BabyTree_->Branch("mt2j"    , &mt2j    );
  BabyTree_->Branch("mt2b"    , &mt2b    );
  BabyTree_->Branch("mt2b_up" , &mt2b_up );
  BabyTree_->Branch("mt2b_dn" , &mt2b_dn );
  BabyTree_->Branch("mt2_genmet"     , &mt2_genmet     );
  BabyTree_->Branch("mt2b_genmet"    , &mt2b_genmet    );

  BabyTree_->Branch("mjj_mindphi"   , &mjj_mindphi   );
  BabyTree_->Branch("mjj"           , &mjj           );
  BabyTree_->Branch("mbb_csv"       , &mbb_csv       );
  BabyTree_->Branch("mbb_bpt"       , &mbb_bpt       );
  BabyTree_->Branch("dphi_jj"       , &dphi_jj       );
  BabyTree_->Branch("dphi_ll"       , &dphi_ll       );
  BabyTree_->Branch("sum_mlb"       , &sum_mlb       );
  BabyTree_->Branch("deta_jj"       , &deta_jj       );
  BabyTree_->Branch("dR_jj"         , &dR_jj         );
  BabyTree_->Branch("dphi_metj1"    , &dphi_metj1    );
  BabyTree_->Branch("dphi_metj2"    , &dphi_metj2    );
  BabyTree_->Branch("dphi_genmetj1" , &dphi_genmetj1 );
  BabyTree_->Branch("dphi_genmetj2" , &dphi_genmetj2 );

  BabyTree_->Branch("mjj_mindphi_up" , &mjj_mindphi_up );
  BabyTree_->Branch("mjj_up"         , &mjj_up         );
  BabyTree_->Branch("mbb_csv_up"     , &mbb_csv_up     );
  BabyTree_->Branch("mbb_bpt_up"     , &mbb_bpt_up     );
  BabyTree_->Branch("dphi_jj_up"     , &dphi_jj_up     );
  BabyTree_->Branch("dphi_ll_up"     , &dphi_ll_up     );
  BabyTree_->Branch("sum_mlb_up"     , &sum_mlb_up     );
  BabyTree_->Branch("deta_jj_up"     , &deta_jj_up     );
  BabyTree_->Branch("dR_jj_up"       , &dR_jj_up       );
  BabyTree_->Branch("dphi_metj1_up"  , &dphi_metj1_up  );
  BabyTree_->Branch("dphi_metj2_up"  , &dphi_metj2_up  );

  BabyTree_->Branch("mjj_mindphi_dn" , &mjj_mindphi_dn );
  BabyTree_->Branch("mjj_dn"         , &mjj_dn         );
  BabyTree_->Branch("mbb_csv_dn"     , &mbb_csv_dn     );
  BabyTree_->Branch("mbb_bpt_dn"     , &mbb_bpt_dn     );
  BabyTree_->Branch("dphi_jj_dn"     , &dphi_jj_dn     );
  BabyTree_->Branch("dphi_ll_dn"     , &dphi_ll_dn     );
  BabyTree_->Branch("sum_mlb_dn"     , &sum_mlb_dn     );
  BabyTree_->Branch("deta_jj_dn"     , &deta_jj_dn     );
  BabyTree_->Branch("dR_jj_dn"       , &dR_jj_dn       );
  BabyTree_->Branch("dphi_metj1_dn"  , &dphi_metj1_dn  );
  BabyTree_->Branch("dphi_metj2_dn"  , &dphi_metj2_dn  );
  
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
  BabyTree_->Branch("mass_chi"   , &mass_chi   );

  BabyTree_->Branch("isrboost"   , &isrboost   );
  BabyTree_->Branch("isr_njets"  , &isr_njets  );
  BabyTree_->Branch("isr_weight" , &isr_weight );
  BabyTree_->Branch("isr_unc"    , &isr_unc    );

  BabyTree_->Branch("weightsf_lepid"    , &weightsf_lepid     );
  BabyTree_->Branch("weightsf_lepiso"   , &weightsf_lepiso    );
  BabyTree_->Branch("weightsf_lepip"    , &weightsf_lepip     );
  BabyTree_->Branch("weightsf_lepreco"  , &weightsf_lepreco   );
  BabyTree_->Branch("weightsf_lepconv"  , &weightsf_lepconv   );
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
  evt_dataset.clear();
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

  nJet200MuFrac50DphiMet = -999;

  nMuons10 = -999;
  nBadMuons20 = -999;
  nElectrons10 = -999;
  nGammas20 = -999;
  nTaus20 = -999;

  gen_ht = -999.0;

  met_pt       = -999.0;
  met_phi      = -999.0;
  met_calo_pt  = -999.0;
  met_calo_phi = -999.0;
  met_miniaod_pt  = -999.0;
  met_miniaod_phi = -999.0;
  met_muegclean_pt  = -999.0;
  met_muegclean_phi = -999.0;
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
  Flag_badMuonFilterv2              = -999;
  Flag_badChargedCandidateFilterv2  = -999;
  Flag_globalTightHalo2016        = -999;
  Flag_badMuons              = -999;
  Flag_duplicateMuons        = -999;
  Flag_noBadMuons            = -999;

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
  HLT_MuEG_noiso_2 = -999;

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
  HLT_DoubleMu_noiso_27_8     = -999;
  HLT_DoubleMu_noiso_30_11    = -999;
  HLT_DoubleMu_noiso_40_11    = -999;
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

  nVetoEl_relIso03EAless01 = -999;
  nVetoEl_relIso03EAless02 = -999;
  nVetoEl_relIso03EAless03 = -999;
  nVetoEl_relIso03EAless04 = -999;
  nVetoMu_relIso03EAless01 = -999;
  nVetoMu_relIso03EAless02 = -999;
  nVetoMu_relIso03EAless03 = -999;
  nVetoMu_relIso03EAless04 = -999;

  lep_p4            .clear();
  lep_pt            .clear();
  lep_eta           .clear();
  lep_phi           .clear();
  lep_mass          .clear();
  lep_charge        .clear();

  lep_3ch_agree           .clear();
  lep_isFromW             .clear();
  lep_isFromZ             .clear();
  lep_isFromB             .clear();
  lep_isFromC             .clear();
  lep_isFromL             .clear();
  lep_isFromLF            .clear();
  lep_ptRatio             .clear();
  lep_motherIdSS          .clear();
  lep_genPart_index       .clear();
  lep_closest_jet_p4      .clear();
  lep_coneCorrPt          .clear();
  lep_ptRel               .clear();
  lep_relIso03            .clear();
  lep_relIso03DB          .clear();
  lep_relIso03EA          .clear();
  lep_relIso03EAv2        .clear();
  lep_relIso04DB          .clear();
  lep_relIso04EA          .clear();
  lep_relIso04EAv2        .clear();
  lep_miniRelIsoCMS3_EA   .clear();
  lep_miniRelIsoCMS3_EAv2 .clear();
  lep_miniRelIsoCMS3_DB   .clear();

  lep_pass_VVV_cutbased_veto             .clear();
  lep_pass_VVV_cutbased_veto_noiso       .clear();
  lep_pass_VVV_cutbased_veto_noiso_noip  .clear();
  lep_pass_VVV_cutbased_fo               .clear();
  lep_pass_VVV_cutbased_fo_noiso         .clear();
  lep_pass_VVV_cutbased_tight_noiso      .clear();
  lep_pass_VVV_cutbased_tight            .clear();
  lep_pass_VVV_MVAbased_tight_noiso      .clear();
  lep_pass_VVV_MVAbased_tight            .clear();
  lep_pass_VVV_baseline                  .clear();

  nlep_VVV_cutbased_veto             = -999;
  nlep_VVV_cutbased_veto_noiso       = -999;
  nlep_VVV_cutbased_veto_noiso_noip  = -999;
  nlep_VVV_cutbased_fo               = -999;
  nlep_VVV_cutbased_fo_noiso         = -999;
  nlep_VVV_cutbased_tight_noiso      = -999;
  nlep_VVV_cutbased_tight            = -999;
  nlep_VVV_MVAbased_tight_noiso      = -999;
  nlep_VVV_MVAbased_tight            = -999;
  nlep_VVV_baseline                  = -999;


  lep_pdgId         .clear();
  lep_mc_Id         .clear();
  lep_dxy           .clear();
  lep_ip3d          .clear();
  lep_ip3derr       .clear();
  lep_etaSC         .clear();
  lep_dz            .clear();
  lep_tightId       .clear();
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

  nisoTrack_mt2_cleaned_VVV_cutbased_veto            = -1;      
  nisoTrack_mt2_cleaned_VVV_cutbased_veto_noiso      = -1;            
  nisoTrack_mt2_cleaned_VVV_cutbased_veto_noiso_noip = -1;                 
  nisoTrack_mt2_cleaned_VVV_cutbased_fo              = -1;    
  nisoTrack_mt2_cleaned_VVV_cutbased_fo_noiso        = -1;          
  nisoTrack_mt2_cleaned_VVV_cutbased_tight_noiso     = -1;             
  nisoTrack_mt2_cleaned_VVV_cutbased_tight           = -1;       
  nisoTrack_mt2_cleaned_VVV_MVAbased_tight_noiso     = -1;             
  nisoTrack_mt2_cleaned_VVV_MVAbased_tight           = -1;       
  nisoTrack_mt2_cleaned_VVV_baseline                 = -1; 

  nisoTrack_stop = -1;
  nisoTrack_PFLep5_woverlaps  = -1;
  nisoTrack_PFHad10_woverlaps = -1;

  ngamma = -999;
  gamma_p4           .clear();   //[ngamma]
  gamma_pt           .clear();   //[ngamma]
  gamma_eta          .clear();   //[ngamma]
  gamma_phi          .clear();   //[ngamma]
  gamma_mass         .clear();   //[ngamma]
  gamma_mcMatchId    .clear();   //[ngamma]
  gamma_genPt        .clear();   //[ngamma]
  gamma_genIso       .clear();   //[ngamma]
  gamma_chHadIso     .clear();   //[ngamma]
  gamma_neuHadIso    .clear();   //[ngamma]
  gamma_phIso        .clear();   //[ngamma]
  gamma_sigmaIetaIeta.clear();   //[ngamma]
  gamma_r9           .clear();   //[ngamma]
  gamma_hOverE       .clear();   //[ngamma]
  gamma_hOverE_online.clear();   //[ngamma]
  gamma_idCutBased   .clear();   //[ngamma]
  gamma_ecpfclusiso  .clear();
  gamma_hcpfclusiso  .clear();
  gamma_hollowtkiso03.clear();
  gamma_genIsPromptFinalState.clear();
  gamma_drMinParton  .clear();

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
  
//----- JETS - pt > JET_PT_MIN, eta < 2.4
  njets    = -999.0;
  njets_up = -999.0;
  njets_dn = -999.0;

  jets_p4            .clear();
  jets_medb_p4       .clear();
  jets_medb_up_p4    .clear();
  jets_medb_dn_p4    .clear();
  jets_dn_p4         .clear();
  jets_up_p4         .clear();
  jets_csv           .clear();
  jets_up_csv        .clear();
  jets_dn_csv        .clear();
  jets_muf           .clear();
  jets_mcFlavour     .clear();
  jets_mcHadronFlav  .clear();

  removed_jets_p4    .clear();
  removed_jets_csv   .clear();

//----- HIGH PT PF CANDS
  nhighPtPFcands = -999.0;
  highPtPFcands_p4   .clear();
  highPtPFcands_dz   .clear();
  highPtPFcands_pdgId.clear();
  
  ht       = -999.0;
  ht_up    = -999.0;
  ht_dn    = -999.0;

  metsig_unofficial       = -999.0;
  metsig_unofficial_up    = -999.0;
  metsig_unofficial_dn    = -999.0;

  mt_lep1  = -999.0;
  mt2      = -999.0;
  mt2_up   = -999.0;
  mt2_dn   = -999.0;
  mt2j     = -999.0;
  mt2b     = -999.0;
  mt2b_up  = -999.0;
  mt2b_dn  = -999.0;
  mt2_genmet      = -999.0;
  mt2b_genmet     = -999.0;

  mjj_mindphi = -999.0;
  mjj         = -999.0;
  mbb_csv     = -999.0;
  mbb_bpt     = -999.0;
  dphi_jj     = -999.0;
  sum_mlb     = -999.0;
  dphi_ll     = -999.0;
  deta_jj     = -999.0;
  dR_jj       = -999.0;  
  dphi_metj1  = -999.0;
  dphi_metj2  = -999.0;
  dphi_genmetj1  = -999.0;
  dphi_genmetj2  = -999.0;

  mjj_mindphi_up = -999.0;
  mjj_up         = -999.0;
  mbb_csv_up     = -999.0;
  mbb_bpt_up     = -999.0;
  dphi_jj_up     = -999.0;
  sum_mlb_up     = -999.0;
  dphi_ll_up     = -999.0;
  deta_jj_up     = -999.0;
  dR_jj_up       = -999.0;  
  dphi_metj1_up  = -999.0;
  dphi_metj2_up  = -999.0;

  mjj_mindphi_dn = -999.0;
  mjj_dn         = -999.0;
  mbb_csv_dn     = -999.0;
  mbb_bpt_dn     = -999.0;
  dphi_jj_dn     = -999.0;
  sum_mlb_dn     = -999.0;
  dphi_ll_dn     = -999.0;
  deta_jj_dn     = -999.0;
  dR_jj_dn       = -999.0;  
  dphi_metj1_dn  = -999.0;
  dphi_metj2_dn  = -999.0;

  
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
  mass_chi    = -999;
  
  isrboost    = -999;
  isr_njets   = -999;
  isr_weight  = -999.9;
  isr_unc     = -999.9;

  weightsf_lepid     . clear();
  weightsf_lepiso    . clear();
  weightsf_lepip     . clear();
  weightsf_lepreco   . clear();
  weightsf_lepconv   . clear();
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
  h_neventsinfile->Write();
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
		if( jets_csv.at(jetind) > BJET_CSV_MED ) continue; // don't double count b-jets
		mlb_temp_2 = (lep_p4.at(1) + jets_p4.at(jetind)).M();
		if(mlb_temp_2 < min_mlb_2){
		  min_mlb_2 = mlb_temp_2;
		}
	  }
	}else{

	  // Find lowest Mlb for lep 1
	  for( size_t jetind = 0; jetind < jets_p4.size(); jetind++ ){
		if( jets_csv.at(jetind) > BJET_CSV_MED ) continue; // don't double count b-jets
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
  f_sfweights  = TFile::Open("leptonSFs/electrons/moriond17/egammaEffi.txt_EGM2D.root","READ");
  h_eleweights_reco = (TH2D*) f_sfweights->Get("EGamma_SF2D") -> Clone("h_eleweights_reco");
  h_eleweights_reco->SetDirectory(rootdir);
  f_sfweights->Close();

  // electron ID/Iso SFs for Fullsim to Data
  f_sfweights  = TFile::Open("leptonSFs/electrons/moriond17/scaleFactors_el_moriond_2017.root","READ");
  h_eleweights_id = (TH2D*) f_sfweights->Get("GsfElectronToMVATightTightIP2DSIP3D4") -> Clone("h_eleweights_id");
  h_eleweightsiso = (TH2D*) f_sfweights->Get("MVAVLooseElectronToMini")  -> Clone("h_eleweightsiso");
  h_eleweights_conv = (TH2D*) f_sfweights->Get("MVATightElectronToConvVetoIHit0") -> Clone("h_eleweights_conv");
  h_eleweights_id->SetDirectory(rootdir);
  h_eleweightsiso->SetDirectory(rootdir);
  h_eleweights_conv->SetDirectory(rootdir);
  f_sfweights->Close();

  // muon id SF for Fullsim to Data
  f_sfweights  = TFile::Open("leptonSFs/muons/moriond17/TnP_NUM_MediumID_DENOM_generalTracks_VAR_map_pt_eta.root","READ");
  h_muoweights_id = (TH2D*) f_sfweights->Get("SF") -> Clone("h_muoweights_id");
  h_muoweights_id	->SetDirectory(rootdir);
  f_sfweights->Close();
	
  // muon iso SF for Fullsim to Data
  f_sfweights  = TFile::Open("leptonSFs/muons/moriond17/TnP_NUM_MiniIsoTight_DENOM_MediumID_VAR_map_pt_eta.root","READ");
  h_muoweightsiso = (TH2D*) f_sfweights->Get("SF") -> Clone("h_muoweightsiso");
  h_muoweightsiso	->SetDirectory(rootdir);
  f_sfweights->Close();

  // muon tracking SF due to HIPs for Fullsim to Data
  f_sfweights  = TFile::Open("leptonSFs/muons/moriond17/Tracking_EfficienciesAndSF_BCDEFGH_hists.root","READ");
  h_muoweights_HIP_hist = (TH1F*) f_sfweights->Get("ratio_eff_eta3_dr030e030_corr") -> Clone("h_muoweights_HIP_hist");
  h_muoweights_HIP_hist -> SetDirectory(rootdir);
  f_sfweights->Close();
	
  // f_sfweights  = TFile::Open("leptonSFs/muons/TnP_MuonID_NUM_TightIP2D_DENOM_MediumID_VAR_map_pt_eta.root","READ");
  // h_muoweights_HIP = (TGraphAsymmErrors*) f_sfweights->Get("ratio_eta") -> Clone("h_muoweights_HIP");
  // // h_muoweights_HIP -> SetDirectory(rootdir);
  // f_sfweights->Close();
	
  // muon ip SF for Fullsim to Data
  f_sfweights  = TFile::Open("leptonSFs/muons/moriond17/TnP_NUM_TightIP2D_DENOM_MediumID_VAR_map_pt_eta.root","READ");
  h_muoweights_ip = (TH2D*) f_sfweights->Get("SF") -> Clone("h_muoweights_ip");
  h_muoweights_ip	->SetDirectory(rootdir);
  f_sfweights->Close();
	
  // SFs electrons for FS to Fullsim
  f_sfweights  = TFile::Open("leptonSFs/FS/moriond17/sf_el_tightMVA_tight2DIP_vtxC_hitseq0.root","READ");
  h_eleweights = (TH2D*)f_sfweights->Get("histo2D") -> Clone("h_eleweights");
  h_eleweights->SetDirectory(rootdir);
  f_sfweights->Close();

  // SFs muons for FS to Fullsim, medium ID
  f_sfweights  = TFile::Open("leptonSFs/FS/moriond17/sf_mu_mediumID.root","READ");
  h_muoweights = (TH2D*)f_sfweights->Get("histo2D") -> Clone("h_muoweights");
  h_muoweights->SetDirectory(rootdir);
  f_sfweights->Close();

  // SFs muons for FS to Fullsim, iso
  f_sfweights  = TFile::Open("leptonSFs/FS/moriond17/sf_mu_mediumID_mini02.root","READ");
  h_muoweights_FS_iso = (TH2D*)f_sfweights->Get("histo2D") -> Clone("h_muoweights_FS_iso");
  h_muoweights_FS_iso->SetDirectory(rootdir);
  f_sfweights->Close();

  // SFs muons for FS to Fullsim, ip
  f_sfweights  = TFile::Open("leptonSFs/FS/moriond17/sf_mu_mediumID_tightIP2D.root","READ");
  h_muoweights_FS_ip = (TH2D*)f_sfweights->Get("histo2D") -> Clone("h_muoweights_FS_ip");
  h_muoweights_FS_ip->SetDirectory(rootdir);
  f_sfweights->Close();
  
  return;
}
