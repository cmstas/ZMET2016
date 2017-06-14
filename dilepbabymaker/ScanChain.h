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
#include "TString.h"

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

  void ScanChain(TChain*, std::string = "testSample", int max_events = -1);

  void MakeBabyNtuple(const char *);
  void InitBabyNtuple();
  void FillBabyNtuple();
  void CloseBabyNtuple();

private:

  TFile *BabyFile_;
  TTree *BabyTree_;

  TH2D * h_eleweights     ; // FS to Fullsim
  TH2D * h_eleweights_id  ;
  TH2D * h_eleweightsiso  ;
  TH2D * h_eleweights_reco;
  TH2D * h_eleweights_conv;

  TH2D * h_muoweights       ; // FS to Fullsim; ID
  TH2D * h_muoweights_FS_iso; // FS to Fullsim; ISO
  TH2D * h_muoweights_FS_ip ; // FS to Fullsim; IP

  TH2D * h_muoweights_id;
  TH2D * h_muoweights_ip;
  TH2D * h_muoweightsiso;
  TH1F * h_muoweights_HIP_hist;

  TH1I * h_neventsinfile;

  float getBtagEffFromFile(float pt, float eta, int mcFlavour, bool isFastsim);
  float get_sum_mlb();
  void load_leptonSF_files();

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
  std::vector<TString>   evt_dataset; // needs to be vector<TString> due to root technicality
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

  Int_t           nJet200MuFrac50DphiMet;
  
  Int_t           nMuons10;
  Int_t           nBadMuons20;
  Int_t           nElectrons10;
  Int_t           nGammas20;
  Int_t           nTaus20;

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
  Float_t         met_calo_pt;
  Float_t         met_calo_phi;
  Float_t         met_miniaod_pt;
  Float_t         met_miniaod_phi;
  Float_t         met_muegclean_pt;
  Float_t         met_muegclean_phi;
  Float_t         met_rawPt;
  Float_t         met_rawPhi;
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
  Int_t Flag_badChargedCandidateFilter         ;
  Int_t Flag_badMuonFilter                     ;
  Int_t Flag_badChargedCandidateFilterv2       ;
  Int_t Flag_badMuonFilterv2                   ;
  Int_t Flag_globalTightHalo2016               ;
  Int_t Flag_badMuons                          ;
  Int_t Flag_duplicateMuons                    ;
  Int_t Flag_noBadMuons                        ;

  //TRIGGER
  // for ATLAS cross checks
  Int_t HLT_singleEl;
  Int_t HLT_singleMu;
  Int_t HLT_singleMu_noiso;
  
  // Double electron
  Int_t HLT_DoubleEl_noiso;
  Int_t HLT_DoubleEl      ; // prescaled - turned off
  Int_t HLT_DoubleEl_DZ   ; // prescaled
  Int_t HLT_DoubleEl_DZ_2 ; // new
	  
  // electron-muon
  Int_t HLT_MuEG        ;
  Int_t HLT_MuEG_2      ;
  Int_t HLT_MuEG_noiso  ;
  Int_t HLT_MuEG_noiso_2;

  Int_t HLT_Mu8_EG17      ;
  Int_t HLT_Mu8_EG23      ;
  Int_t HLT_Mu8_EG23_DZ   ;

  Int_t HLT_Mu12_EG23_DZ  ;

  Int_t HLT_Mu17_EG12     ;

  Int_t HLT_Mu23_EG8      ;
  Int_t HLT_Mu23_EG8_DZ   ;
  Int_t HLT_Mu23_EG12     ;
  Int_t HLT_Mu23_EG12_DZ  ;

  // Double electron
  Int_t HLT_DoubleMu_noiso   ;
  Int_t HLT_DoubleMu_noiso_27_8    ;
  Int_t HLT_DoubleMu_noiso_30_11   ;
  Int_t HLT_DoubleMu_noiso_40_11   ;
  Int_t HLT_DoubleMu         ;
  Int_t HLT_DoubleMu_tk      ;
  Int_t HLT_DoubleMu_dbltk   ;
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

  Int_t HLT_CaloJet500_NoJetID;
  Int_t HLT_ECALHT800_NoJetID ;

  Bool_t HLT_Photon22_R9Id90_HE10_IsoM_matchedtophoton;
  Bool_t HLT_Photon30_R9Id90_HE10_IsoM_matchedtophoton;
  Bool_t HLT_Photon36_R9Id90_HE10_IsoM_matchedtophoton;
  Bool_t HLT_Photon50_R9Id90_HE10_IsoM_matchedtophoton;
  Bool_t HLT_Photon75_R9Id90_HE10_IsoM_matchedtophoton;
  Bool_t HLT_Photon90_R9Id90_HE10_IsoM_matchedtophoton;
  Bool_t HLT_Photon120_R9Id90_HE10_IsoM_matchedtophoton;
  Bool_t HLT_Photon165_R9Id90_HE10_IsoM_matchedtophoton;
  Bool_t HLT_Photon165_HE10_matchedtophoton;
  
  //----- LEPTONS
  Int_t           nlep;
  Int_t           nveto_leptons;
  Int_t           nVetoEl_relIso03EAless01;
  Int_t           nVetoEl_relIso03EAless02;
  Int_t           nVetoEl_relIso03EAless03;
  Int_t           nVetoEl_relIso03EAless04;
  Int_t           nVetoMu_relIso03EAless01;
  Int_t           nVetoMu_relIso03EAless02;
  Int_t           nVetoMu_relIso03EAless03;
  Int_t           nVetoMu_relIso03EAless04;
  
  std::vector <LorentzVector> lep_p4;
  std::vector <Float_t> lep_pt           ;   //[nlep]
  std::vector <Float_t> lep_eta          ;   //[nlep]
  std::vector <Float_t> lep_phi          ;   //[nlep]
  std::vector <Float_t> lep_mass         ;   //[nlep]
  std::vector <Int_t  > lep_charge       ;   //[nlep]
  
  std::vector <Bool_t >  lep_3ch_agree             ;
  std::vector <Bool_t  > lep_isFromW               ;
  std::vector <Bool_t  > lep_isFromZ               ;
  std::vector <Bool_t  > lep_isFromB               ;
  std::vector <Bool_t  > lep_isFromC               ;
  std::vector <Bool_t  > lep_isFromL               ;
  std::vector <Bool_t  > lep_isFromLF              ;
  std::vector <Double_t> lep_coneCorrPt            ;
  std::vector <Double_t> lep_ptRatio               ;
  std::vector <Double_t> lep_ptRel                 ;
  std::vector <Double_t> lep_relIso03              ;
  std::vector <Double_t> lep_relIso03DB            ;
  std::vector <Double_t> lep_relIso03EA            ;
  std::vector <Double_t> lep_relIso03EAv2          ;
  std::vector <Double_t> lep_relIso04DB            ;
  std::vector <Double_t> lep_relIso04EA            ;
  std::vector <Double_t> lep_relIso04EAv2          ; 
  std::vector <Double_t> lep_miniRelIsoCMS3_EA     ;
  std::vector <Double_t> lep_miniRelIsoCMS3_EAv2   ;
  std::vector <Double_t> lep_miniRelIsoCMS3_DB     ;
  std::vector <LorentzVector> lep_closest_jet_p4   ;
  std::vector <Int_t>    lep_motherIdSS            ;
  std::vector <Int_t>    lep_genPart_index         ;


  //Lepton IDs:
  std::vector <Bool_t >  lep_pass_VVV_cutbased_veto             ;
  std::vector <Bool_t >  lep_pass_VVV_cutbased_veto_noiso       ;
  std::vector <Bool_t >  lep_pass_VVV_cutbased_veto_noiso_noip  ;
  std::vector <Bool_t >  lep_pass_VVV_cutbased_fo               ;
  std::vector <Bool_t >  lep_pass_VVV_cutbased_fo_noiso         ;
  std::vector <Bool_t >  lep_pass_VVV_cutbased_tight_noiso      ;
  std::vector <Bool_t >  lep_pass_VVV_cutbased_tight            ;
  std::vector <Bool_t >  lep_pass_VVV_MVAbased_tight_noiso      ;
  std::vector <Bool_t >  lep_pass_VVV_MVAbased_tight            ;
  std::vector <Bool_t >  lep_pass_VVV_baseline                  ;

  //Lepton ID Counters:
  Int_t  nlep_VVV_cutbased_veto                  ;
  Int_t  nlep_VVV_cutbased_veto_noiso            ;
  Int_t  nlep_VVV_cutbased_veto_noiso_noip       ;
  Int_t  nlep_VVV_cutbased_fo                    ;
  Int_t  nlep_VVV_cutbased_fo_noiso              ;
  Int_t  nlep_VVV_cutbased_tight_noiso           ;
  Int_t  nlep_VVV_cutbased_tight                 ;
  Int_t  nlep_VVV_MVAbased_tight_noiso           ;
  Int_t  nlep_VVV_MVAbased_tight                 ;
  Int_t  nlep_VVV_baseline                       ;

  std::vector <Int_t  > lep_pdgId        ;   //[nlep]
  std::vector <Int_t  > lep_mc_Id        ;
  std::vector <Float_t> lep_dxy          ;   //[nlep]
  std::vector <Float_t> lep_ip3d         ;   //[nlep]
  std::vector <Float_t> lep_ip3derr      ;   //[nlep]
  std::vector <Float_t> lep_etaSC        ;   //[nlep]
  std::vector <Float_t> lep_dz           ;   //[nlep]
  std::vector <Int_t  > lep_tightId      ;   //[nlep]
  std::vector <Int_t  > lep_mcMatchId    ;   //[nlep]
  std::vector <Int_t  > lep_lostHits     ;   //[nlep]
  std::vector <Int_t  > lep_convVeto     ;   //[nlep]
  std::vector <Int_t  > lep_tightCharge  ;   //[nlep]
  std::vector <Float_t> lep_MVA          ;   //[nlep]
  std::vector <Float_t> lep_validfraction;   //[nlep]
  std::vector <Float_t> lep_pterr        ;   //[nlep]
  std::vector <Float_t> lep_sta_pterrOpt ;   //[nlep]
  std::vector <Float_t> lep_glb_pterrOpt ;   //[nlep]
  // std::vector <Float_t> lep_bft_pterrOpt ;   //[nlep]
  std::vector <Float_t> lep_x2ondof      ;   //[nlep]
  std::vector <Float_t> lep_sta_x2ondof  ;   //[nlep]
  std::vector <Float_t> lep_glb_x2ondof  ;   //[nlep]
  // std::vector <Float_t> lep_bft_x2ondof  ;   //[nlep]
  
  Int_t nisoTrack_5gev;
  Int_t nisoTrack_stop;
  Int_t nisoTrack_mt2 ;
  
  Int_t nisoTrack_mt2_cleaned_VVV_cutbased_veto            ;     
  Int_t nisoTrack_mt2_cleaned_VVV_cutbased_veto_noiso      ;           
  Int_t nisoTrack_mt2_cleaned_VVV_cutbased_veto_noiso_noip ;                
  Int_t nisoTrack_mt2_cleaned_VVV_cutbased_fo              ;   
  Int_t nisoTrack_mt2_cleaned_VVV_cutbased_fo_noiso        ;         
  Int_t nisoTrack_mt2_cleaned_VVV_cutbased_tight_noiso     ;            
  Int_t nisoTrack_mt2_cleaned_VVV_cutbased_tight           ;      
  Int_t nisoTrack_mt2_cleaned_VVV_MVAbased_tight_noiso     ;            
  Int_t nisoTrack_mt2_cleaned_VVV_MVAbased_tight           ;      
  Int_t nisoTrack_mt2_cleaned_VVV_baseline                 ;

  Int_t nisoTrack_PFLep5_woverlaps ;
  Int_t nisoTrack_PFHad10_woverlaps ;

  //----- PHOTONS
  Int_t           ngamma;
  std::vector <LorentzVector>   gamma_p4;
  std::vector <Float_t>         gamma_pt           ;           //[ngamma]
  std::vector <Float_t>         gamma_eta          ;           //[ngamma]
  std::vector <Float_t>         gamma_phi          ;           //[ngamma]
  std::vector <Float_t>         gamma_mass         ;           //[ngamma]
  std::vector <Float_t>         gamma_sigmaIetaIeta;           //[ngamma]
  std::vector <Float_t>         gamma_chHadIso     ;           //[ngamma]
  std::vector <Float_t>         gamma_neuHadIso    ;           //[ngamma]
  std::vector <Float_t>         gamma_phIso        ;           //[ngamma]
  std::vector <Float_t>         gamma_r9           ;           //[ngamma]
  std::vector <Float_t>         gamma_hOverE       ;           //[ngamma]
  std::vector <Float_t>         gamma_hOverE_online;           //[ngamma]
  std::vector <Int_t  >         gamma_idCutBased   ;           //[ngamma]
  std::vector <Int_t  >         gamma_mcMatchId    ;           //[ngamma]
  std::vector <Float_t>         gamma_genPt        ;           //[ngamma]
  std::vector <Float_t>         gamma_genIso       ;           //[ngamma]
  std::vector <Float_t>         gamma_ecpfclusiso  ;           //[ngamma]
  std::vector <Float_t>         gamma_hcpfclusiso  ;           //[ngamma]
  std::vector <Float_t>         gamma_hollowtkiso03;           //[ngamma]
  std::vector <Int_t>           gamma_genIsPromptFinalState;   //[ngamma]
  std::vector <Float_t>         gamma_drMinParton  ;

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
  std::vector <LorentzVector>   jets_p4;
  std::vector <LorentzVector>   removed_jets_p4;
  std::vector <LorentzVector>   jets_medb_p4;
  std::vector <Float_t>         jets_csv;
  std::vector <Float_t>         removed_jets_csv;
  std::vector <Float_t>         jets_muf;

  Int_t           njets_up;
  std::vector <LorentzVector>   jets_up_p4;
  std::vector <LorentzVector>   jets_medb_up_p4;
  std::vector <Float_t>         jets_up_csv;

  Int_t           njets_dn;
  std::vector <LorentzVector>   jets_dn_p4;
  std::vector <LorentzVector>   jets_medb_dn_p4;
  std::vector <Float_t>         jets_dn_csv;

  // MC only
  std::vector <Int_t  >         jets_mcFlavour   ;
  std::vector <Int_t  >         jets_mcHadronFlav;

  //----- HIGH PT PF CANDS (pt > 300, or pt > 50 for muons)
  Int_t           nhighPtPFcands;
  std::vector <LorentzVector>   highPtPFcands_p4;
  std::vector <Float_t>         highPtPFcands_dz;
  std::vector <Int_t>           highPtPFcands_pdgId;

  Float_t         ht;
  Float_t         ht_up;
  Float_t         ht_dn;

  Float_t         metsig_unofficial;
  Float_t         metsig_unofficial_dn;
  Float_t         metsig_unofficial_up;

  Float_t         mt_lep1;  // leading lepton only
  Float_t         mt2;  // only leptons
  Float_t         mt2_up;  // only leptons
  Float_t         mt2_dn;  // only leptons
  Float_t         mt2j; // all jets
  Float_t         mt2b; // b-jets only
  Float_t         mt2b_up; // b-jets only
  Float_t         mt2b_dn; // b-jets only
  Float_t         mt2_genmet; // only leptons
  Float_t         mt2b_genmet; // b-jets only

  Float_t         mjj_mindphi;
  Float_t         mjj;
  Float_t         mbb_csv;
  Float_t         mbb_bpt;
  Float_t         dphi_jj;
  Float_t         sum_mlb;
  Float_t         dphi_ll;
  Float_t         deta_jj;
  Float_t         dR_jj;
  Float_t         dphi_metj1;
  Float_t         dphi_metj2;
  Float_t         dphi_genmetj1;
  Float_t         dphi_genmetj2;

  Float_t         mjj_mindphi_up;
  Float_t         mjj_up;
  Float_t         mbb_csv_up;
  Float_t         mbb_bpt_up;
  Float_t         dphi_jj_up;
  Float_t         sum_mlb_up;
  Float_t         dphi_ll_up;
  Float_t         deta_jj_up;
  Float_t         dR_jj_up;
  Float_t         dphi_metj1_up;
  Float_t         dphi_metj2_up;

  Float_t         mjj_mindphi_dn;
  Float_t         mjj_dn;
  Float_t         mbb_csv_dn;
  Float_t         mbb_bpt_dn;
  Float_t         dphi_jj_dn;
  Float_t         sum_mlb_dn;
  Float_t         dphi_ll_dn;
  Float_t         deta_jj_dn;
  Float_t         dR_jj_dn;
  Float_t         dphi_metj1_dn;
  Float_t         dphi_metj2_dn;

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

  //----- decayed photon variables
  LorentzVector decayedphoton_lep1_p4;
  LorentzVector decayedphoton_lep2_p4;
  LorentzVector decayedphoton_bosn_p4;
  Float_t       decayedphoton_mt2;
  
  // SUSY variables
  Int_t mass_gluino;
  Int_t mass_LSP;
  Int_t mass_chi;

  Float_t isrboost  ;
  Int_t   isr_njets ;
  Float_t isr_weight;
  Float_t isr_unc   ;

  // all electron weights in lepid; muon weights split in three weights
  std::vector <Float_t> weightsf_lepid;
  std::vector <Float_t> weightsf_lepiso;
  std::vector <Float_t> weightsf_lepip;

  // electron reco efficiency; muon loss due to HIP
  std::vector <Float_t> weightsf_lepreco;

  // electron conv veto efficiency; not used for muons
  std::vector <Float_t> weightsf_lepconv;

  // all electron weights in lepid; muon weights split in three weights  
  std::vector <Float_t> weightsf_lepid_FS;
  std::vector <Float_t> weightsf_lepiso_FS;
  std::vector <Float_t> weightsf_lepip_FS;
  
};

#endif

