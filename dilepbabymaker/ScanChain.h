#ifndef ScanChain_h
#define ScanChain_h

// C++ includes
#include <string>
#include <vector>

// ROOT includes
#include "TROOT.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TH2.h"

#include "Math/LorentzVector.h"
#include "Math/GenVector/LorentzVector.h"

#include "../CORE/Tools/btagsf/BTagCalibrationStandalone.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

class BTagCalibration;
class BTagCalibrationReader;

class babyMaker {

 public:

  babyMaker() {};
  ~babyMaker() {
    if (BabyFile_) delete BabyFile_;
    if (BabyTree_) delete BabyTree_;
  };

  void ScanChain(TChain*, std::string = "testSample");

  void MakeBabyNtuple(const char *);
  void InitBabyNtuple();
  void FillBabyNtuple();
  void CloseBabyNtuple();

 private:

  TFile *BabyFile_;
  TTree *BabyTree_;

  float getBtagEffFromFile(float pt, float eta, int mcFlavour, bool isFastsim);
  
  // for btag SFs
  BTagCalibration* calib;
  BTagCalibrationReader* reader_heavy;
  BTagCalibrationReader* reader_heavy_UP;
  BTagCalibrationReader* reader_heavy_DN;
  BTagCalibrationReader* reader_light;
  BTagCalibrationReader* reader_light_UP;
  BTagCalibrationReader* reader_light_DN;

  TH2D* h_btag_eff_b;
  TH2D* h_btag_eff_c;
  TH2D* h_btag_eff_udsg;
  
  BTagCalibration* calib_fastsim;
  BTagCalibrationReader* reader_fastsim;
  BTagCalibrationReader* reader_fastsim_UP;
  BTagCalibrationReader* reader_fastsim_DN;

  TH2D* h_btag_eff_b_fastsim;
  TH2D* h_btag_eff_c_fastsim;
  TH2D* h_btag_eff_udsg_fastsim;
  
  //baby ntuple variables

  Int_t           run;
  Int_t           lumi;
  ULong64_t       evt;
  Int_t           isData;

  Bool_t          evt_passgoodrunlist;
  Float_t         evt_scale1fb;
  Float_t         evt_xsec;
  Float_t         evt_kfactor;
  Float_t         evt_filter;
  Int_t           evt_nEvts;
  Int_t           evt_id;
  Float_t         puWeight;
  Int_t           nVert;
  Int_t           nTrueInt;
  Float_t         rho;
  Float_t         rho25;

  Int_t           nBJetTight;
  Int_t           nBJetMedium;
  Int_t           nBJetLoose;

  Int_t           nBJetTight_up;
  Int_t           nBJetMedium_up;
  Int_t           nBJetLoose_up;

  Int_t           nBJetTight_dn;
  Int_t           nBJetMedium_dn;
  Int_t           nBJetLoose_dn;

  Int_t           nMuons10;
  Int_t           nElectrons10;
  Int_t           nGammas20;

  Float_t         gen_ht;

  Int_t           hyp_type; // 0 = ee; 1 = mm; 2 = em; 2 = me
  Int_t           evt_type; // 0 = OS; 1 = SS; 2 = photon+jets
  Float_t         dilmass;
  Float_t         dilpt;
  Float_t         dRll;

  Float_t         matched_neutralemf; // neutral em fraction for jet closest to photon within dR = .1
  Float_t         matched_emf;        // neutral + charged em fraction for jet closest to photon within dR = .1

  Bool_t          elveto; // Reject photons which have electron of pT > 10 GeV within dR < 0.2


  Float_t         met_pt;
  Float_t         met_phi;
  Float_t         met_rawPt;
  Float_t         met_rawPhi;
  Float_t         met_caloPt;
  Float_t         met_caloPhi;
  Float_t         met_genPt;
  Float_t         met_genPhi;

  Float_t         sumet_raw;
  
//----- MET FILTERS
  Int_t Flag_ecalLaserCorrFilter;
  Int_t Flag_hcalLaserEventFilter;
  Int_t Flag_trackingFailureFilter;
  Int_t Flag_CSCTightHaloFilter;

  // recommended from twiki
  Int_t Flag_HBHENoiseFilter                   ;
  Int_t Flag_HBHEIsoNoiseFilter                ;
  Int_t Flag_CSCTightHalo2015Filter            ; // check: filt_cscBeamHalo2015
  Int_t Flag_EcalDeadCellTriggerPrimitiveFilter;
  Int_t Flag_goodVertices                      ;
  Int_t Flag_eeBadScFilter                     ;
  
  //TRIGGER
  // for ATLAS cross checks
  Int_t HLT_singleEl;
  Int_t HLT_singleMu;
					  
  // Double electron
  Int_t HLT_DoubleEl_noiso;
  Int_t HLT_DoubleEl      ; // prescaled - turned off
  Int_t HLT_DoubleEl_DZ   ; // prescaled
  Int_t HLT_DoubleEl_DZ_2 ; // new
	  
  // electron-muon
  Int_t HLT_MuEG      ;
  Int_t HLT_MuEG_2    ;
  Int_t HLT_MuEG_noiso;

  // Double electron
  Int_t HLT_DoubleMu_noiso   ;
  Int_t HLT_DoubleMu         ;
  Int_t HLT_DoubleMu_tk      ;
  Int_t HLT_DoubleMu_nonDZ   ;
  Int_t HLT_DoubleMu_tk_nonDZ; // new unprescaled : use these

  // Single photon
  Int_t HLT_Photon22_R9Id90_HE10_IsoM ;
  Int_t HLT_Photon30_R9Id90_HE10_IsoM ;
  Int_t HLT_Photon36_R9Id90_HE10_IsoM ;
  Int_t HLT_Photon50_R9Id90_HE10_IsoM ;
  Int_t HLT_Photon75_R9Id90_HE10_IsoM ;
  Int_t HLT_Photon90_R9Id90_HE10_IsoM ;
  Int_t HLT_Photon120_R9Id90_HE10_IsoM;
  Int_t HLT_Photon165_R9Id90_HE10_IsoM;
  Int_t HLT_Photon165_HE10            ;

  
  //----- LEPTONS
  Int_t           nlep;
  std::vector <LorentzVector> lep_p4;
  std::vector <Float_t> lep_pt         ;   //[nlep]
  std::vector <Float_t> lep_eta        ;   //[nlep]
  std::vector <Float_t> lep_phi        ;   //[nlep]
  std::vector <Float_t> lep_mass       ;   //[nlep]
  std::vector <Int_t  > lep_charge     ;   //[nlep]
  std::vector <Int_t  > lep_pdgId      ;   //[nlep]
  std::vector <Float_t> lep_dxy        ;   //[nlep]
  std::vector <Float_t> lep_etaSC      ;   //[nlep]
  std::vector <Float_t> lep_dz         ;   //[nlep]
  std::vector <Int_t  > lep_tightId    ;   //[nlep]
  std::vector <Float_t> lep_relIso03   ;   //[nlep]
  std::vector <Float_t> lep_relIso03MREA   ;   //[nlep]
  std::vector <Float_t> lep_relIso03MRDB   ;   //[nlep]
  std::vector <Float_t> lep_relIso03MRNC   ;   //[nlep]
  std::vector <Float_t> lep_relIso04   ;   //[nlep]
  std::vector <Int_t  > lep_mcMatchId  ;   //[nlep]
  std::vector <Int_t  > lep_lostHits   ;   //[nlep]
  std::vector <Int_t  > lep_convVeto   ;   //[nlep]
  std::vector <Int_t  > lep_tightCharge;   //[nlep]
  std::vector <Float_t> lep_MVA        ;   //[nlep]
  

//----- PHOTONS
  Int_t           ngamma;
  std::vector <LorentzVector>   gamma_p4;
  std::vector <Float_t>         gamma_pt           ;   //[ngamma]
  std::vector <Float_t>         gamma_eta          ;   //[ngamma]
  std::vector <Float_t>         gamma_phi          ;   //[ngamma]
  std::vector <Float_t>         gamma_mass         ;   //[ngamma]
  std::vector <Float_t>         gamma_sigmaIetaIeta;   //[ngamma]
  std::vector <Float_t>         gamma_chHadIso     ;   //[ngamma]
  std::vector <Float_t>         gamma_neuHadIso    ;   //[ngamma]
  std::vector <Float_t>         gamma_phIso        ;   //[ngamma]
  std::vector <Float_t>         gamma_r9           ;   //[ngamma]
  std::vector <Float_t>         gamma_hOverE       ;   //[ngamma]
  std::vector <Int_t  >         gamma_idCutBased   ;   //[ngamma]
  std::vector <Int_t  >         gamma_mcMatchId    ;   //[ngamma]
  std::vector <Float_t>         gamma_genIso       ;   //[ngamma]

//----- GEN PARTICLES
  Int_t           ngenPart;
  Int_t           ngen_p6s3Part;
  std::vector <LorentzVector>   genPart_p4         ;
  std::vector <Float_t>         genPart_pt         ;   //[ngenPart]
  std::vector <Float_t>         genPart_eta        ;   //[ngenPart]
  std::vector <Float_t>         genPart_phi        ;   //[ngenPart]
  std::vector <Float_t>         genPart_mass       ;   //[ngenPart]
  std::vector <Int_t  >         genPart_pdgId      ;   //[ngenPart]
  std::vector <Int_t  >         genPart_status     ;   //[ngenPart]
  std::vector <Bool_t >         genPart_isp6status3;   //[ngenPart]
  std::vector <Float_t>         genPart_charge     ;   //[ngenPart]
  std::vector <Int_t  >         genPart_motherId   ;   //[ngenPart]
  std::vector <Int_t  >         genPart_grandmaId  ;   //[ngenPart]

//----- GEN LEPTONS (ELECTRONS/MUONS)
  Int_t           ngenLep;
  Int_t           ngen_p6s3Lep;
  std::vector <Float_t>         genLep_pt         ;   //[ngenLep]
  std::vector <Float_t>         genLep_eta        ;   //[ngenLep]
  std::vector <Float_t>         genLep_phi        ;   //[ngenLep]
  std::vector <Float_t>         genLep_mass       ;   //[ngenLep]
  std::vector <Int_t  >         genLep_pdgId      ;   //[ngenLep]
  std::vector <Int_t  >         genLep_status     ;   //[ngenLep]
  std::vector <Bool_t >         genLep_isp6status3;   //[ngenLep]
  std::vector <Float_t>         genLep_charge     ;   //[ngenLep]
  std::vector <Int_t  >         genLep_sourceId   ;   //[ngenLep]

//----- GEN TAUS
  Int_t           ngenTau;
  std::vector <Float_t>         genTau_pt      ;   //[ngenTau]
  std::vector <Float_t>         genTau_eta     ;   //[ngenTau]
  std::vector <Float_t>         genTau_phi     ;   //[ngenTau]
  std::vector <Float_t>         genTau_mass    ;   //[ngenTau]
  std::vector <Int_t  >         genTau_pdgId   ;   //[ngenTau]
  std::vector <Int_t  >         genTau_status  ;   //[ngenTau]
  std::vector <Float_t>         genTau_charge  ;   //[ngenTau]
  std::vector <Int_t  >         genTau_sourceId;   //[ngenTau]

//----- GEN LEPTONS FROM TAUS
  Int_t           ngenLepFromTau;
  std::vector <Float_t>         genLepFromTau_pt      ;   //[ngenLepFromTau]
  std::vector <Float_t>         genLepFromTau_eta     ;   //[ngenLepFromTau]
  std::vector <Float_t>         genLepFromTau_phi     ;   //[ngenLepFromTau]
  std::vector <Float_t>         genLepFromTau_mass    ;   //[ngenLepFromTau]
  std::vector <Int_t  >         genLepFromTau_pdgId   ;   //[ngenLepFromTau]
  std::vector <Int_t  >         genLepFromTau_status  ;   //[ngenLepFromTau]
  std::vector <Float_t>         genLepFromTau_charge  ;   //[ngenLepFromTau]
  std::vector <Int_t  >         genLepFromTau_sourceId;   //[ngenLepFromTau]

//----- JETS - pt > 35, eta < 2.4
  Int_t           njets;
  Int_t           njets_up;
  Int_t           njets_dn;
  std::vector <LorentzVector>   jets_p4;
  std::vector <LorentzVector>   jets_up_p4;
  std::vector <LorentzVector>   jets_dn_p4;

  std::vector <LorentzVector>   jets_medb_p4;
  std::vector <Float_t>         jets_csv;

  // MC only
  std::vector <Int_t  >         jets_mcFlavour   ;
  std::vector <Int_t  >         jets_mcHadronFlav;

  Float_t         ht;
  Float_t         ht_up;
  Float_t         ht_dn;

  Float_t         mt2;  // only leptons
  Float_t         mt2j; // all jets
  Float_t         mt2b; // b-jets only

  Float_t         mjj;
  Float_t         mbb_csv;
  Float_t         mbb_bpt;
  Float_t         dphi_jj;
  Float_t         deta_jj;
  Float_t         dR_jj;

  Float_t         dphi_metj1;
  Float_t         dphi_metj2;

  //----- weights for b-tag SF  
  Float_t         weight_btagsf;
  Float_t         weight_btagsf_heavy_UP;
  Float_t         weight_btagsf_light_UP;
  Float_t         weight_btagsf_heavy_DN;
  Float_t         weight_btagsf_light_DN;
  
  //----- pfMETs
  Float_t chpfcands_0013_pt;
  Float_t chpfcands_1316_pt;
  Float_t chpfcands_1624_pt;
  Float_t chpfcands_2430_pt;
  Float_t chpfcands_30in_pt;
  Float_t phpfcands_0013_pt;
  Float_t phpfcands_1316_pt;
  Float_t phpfcands_1624_pt;
  Float_t phpfcands_2430_pt;
  Float_t phpfcands_30in_pt;
  Float_t nupfcands_0013_pt;
  Float_t nupfcands_1316_pt;
  Float_t nupfcands_1624_pt;
  Float_t nupfcands_2430_pt;
  Float_t nupfcands_30in_pt;

  Float_t chpfcands_0013_phi;
  Float_t chpfcands_1316_phi;
  Float_t chpfcands_1624_phi;
  Float_t chpfcands_2430_phi;
  Float_t chpfcands_30in_phi;
  Float_t phpfcands_0013_phi;
  Float_t phpfcands_1316_phi;
  Float_t phpfcands_1624_phi;
  Float_t phpfcands_2430_phi;
  Float_t phpfcands_30in_phi;
  Float_t nupfcands_0013_phi;
  Float_t nupfcands_1316_phi;
  Float_t nupfcands_1624_phi;
  Float_t nupfcands_2430_phi;
  Float_t nupfcands_30in_phi;

  //----- pfsumETs
  Float_t chpfcands_0013_sumet;
  Float_t chpfcands_1316_sumet;
  Float_t chpfcands_1624_sumet;
  Float_t chpfcands_2430_sumet;
  Float_t chpfcands_30in_sumet;
  Float_t phpfcands_0013_sumet;
  Float_t phpfcands_1316_sumet;
  Float_t phpfcands_1624_sumet;
  Float_t phpfcands_2430_sumet;
  Float_t phpfcands_30in_sumet;
  Float_t nupfcands_0013_sumet;
  Float_t nupfcands_1316_sumet;
  Float_t nupfcands_1624_sumet;
  Float_t nupfcands_2430_sumet;
  Float_t nupfcands_30in_sumet;

  Float_t met_T1CHS_pt;
  Float_t met_T1CHS_phi;
  Float_t met_T1CHS_fromCORE_pt;
  Float_t met_T1CHS_fromCORE_phi;
  Float_t met_T1CHS_miniAOD_CORE_pt;
  Float_t met_T1CHS_miniAOD_CORE_phi;
  Float_t met_T1CHS_miniAOD_CORE_up_pt;
  Float_t met_T1CHS_miniAOD_CORE_up_phi;
  Float_t met_T1CHS_miniAOD_CORE_dn_pt;
  Float_t met_T1CHS_miniAOD_CORE_dn_phi;

  // SUSY variables
  Int_t mass_gluino;
  Int_t mass_LSP;

  Float_t isrboost;
  
};

#endif

