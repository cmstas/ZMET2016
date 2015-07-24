#include "ZMET.h"
ZMET zmet;
namespace ZMet {
	const int &run() { return zmet.run(); }
	const int &lumi() { return zmet.lumi(); }
	const unsigned long long &evt() { return zmet.evt(); }
	const int &isData() { return zmet.isData(); }
	const bool &evt_passgoodrunlist() { return zmet.evt_passgoodrunlist(); }
	const float &evt_scale1fb() { return zmet.evt_scale1fb(); }
	const float &evt_xsec() { return zmet.evt_xsec(); }
	const float &evt_kfactor() { return zmet.evt_kfactor(); }
	const float &evt_filter() { return zmet.evt_filter(); }
	const int &evt_nEvts() { return zmet.evt_nEvts(); }
	const float &puWeight() { return zmet.puWeight(); }
	const int &nVert() { return zmet.nVert(); }
	const int &nTrueInt() { return zmet.nTrueInt(); }
	const float &rho() { return zmet.rho(); }
	const float &rho25() { return zmet.rho25(); }
	const int &njets() { return zmet.njets(); }
	const float &ht() { return zmet.ht(); }
	const float &gen_ht() { return zmet.gen_ht(); }
	const int &njets_eta30() { return zmet.njets_eta30(); }
	const float &ht_eta30() { return zmet.ht_eta30(); }
	const float &mt2() { return zmet.mt2(); }
	const float &mt2j() { return zmet.mt2j(); }
	const float &mt2j_eta30() { return zmet.mt2j_eta30(); }
	const int &nJet40() { return zmet.nJet40(); }
	const int &nBJet40() { return zmet.nBJet40(); }
	const int &nBJetTight() { return zmet.nBJetTight(); }
	const int &nBJetMedium() { return zmet.nBJetMedium(); }
	const int &nBJetLoose() { return zmet.nBJetLoose(); }
	const int &nMuons10() { return zmet.nMuons10(); }
	const int &nElectrons10() { return zmet.nElectrons10(); }
	const int &nTaus20() { return zmet.nTaus20(); }
	const int &nGammas20() { return zmet.nGammas20(); }
	const float &met_pt() { return zmet.met_pt(); }
	const float &met_phi() { return zmet.met_phi(); }
	const float &met_rawPt() { return zmet.met_rawPt(); }
	const float &met_rawPhi() { return zmet.met_rawPhi(); }
	const float &met_caloPt() { return zmet.met_caloPt(); }
	const float &met_caloPhi() { return zmet.met_caloPhi(); }
	const float &met_genPt() { return zmet.met_genPt(); }
	const float &met_genPhi() { return zmet.met_genPhi(); }
	const float &sumet_raw() { return zmet.sumet_raw(); }
	const float &jzb_raw() { return zmet.jzb_raw(); }
	const float &jzb_T1() { return zmet.jzb_T1(); }
	const float &jgb_raw() { return zmet.jgb_raw(); }
	const float &jgb_T1() { return zmet.jgb_T1(); }
	const int &Flag_EcalDeadCellTriggerPrimitiveFilter() { return zmet.Flag_EcalDeadCellTriggerPrimitiveFilter(); }
	const int &Flag_trkPOG_manystripclus53X() { return zmet.Flag_trkPOG_manystripclus53X(); }
	const int &Flag_ecalLaserCorrFilter() { return zmet.Flag_ecalLaserCorrFilter(); }
	const int &Flag_trkPOG_toomanystripclus53X() { return zmet.Flag_trkPOG_toomanystripclus53X(); }
	const int &Flag_hcalLaserEventFilter() { return zmet.Flag_hcalLaserEventFilter(); }
	const int &Flag_trkPOG_logErrorTooManyClusters() { return zmet.Flag_trkPOG_logErrorTooManyClusters(); }
	const int &Flag_trkPOGFilters() { return zmet.Flag_trkPOGFilters(); }
	const int &Flag_trackingFailureFilter() { return zmet.Flag_trackingFailureFilter(); }
	const int &Flag_CSCTightHaloFilter() { return zmet.Flag_CSCTightHaloFilter(); }
	const int &Flag_HBHENoiseFilter() { return zmet.Flag_HBHENoiseFilter(); }
	const int &Flag_goodVertices() { return zmet.Flag_goodVertices(); }
	const int &Flag_eeBadScFilter() { return zmet.Flag_eeBadScFilter(); }
	const int &Flag_METFilters() { return zmet.Flag_METFilters(); }
	const int &HLT_HT900() { return zmet.HLT_HT900(); }
	const int &HLT_MET170() { return zmet.HLT_MET170(); }
	const int &HLT_ht350met120() { return zmet.HLT_ht350met120(); }
	const int &HLT_SingleMu() { return zmet.HLT_SingleMu(); }
	const int &HLT_DoubleEl() { return zmet.HLT_DoubleEl(); }
	const int &HLT_DoubleEl_DZ() { return zmet.HLT_DoubleEl_DZ(); }
	const int &HLT_DoubleEl_noiso() { return zmet.HLT_DoubleEl_noiso(); }
	const int &HLT_MuEG() { return zmet.HLT_MuEG(); }
	const int &HLT_MuEG_2() { return zmet.HLT_MuEG_2(); }
	const int &HLT_DoubleMu() { return zmet.HLT_DoubleMu(); }
	const int &HLT_DoubleMu_tk() { return zmet.HLT_DoubleMu_tk(); }
	const int &HLT_l1prescale() { return zmet.HLT_l1prescale(); }
	const int &HLT_Photons() { return zmet.HLT_Photons(); }
	const int &HLT_Photon22() { return zmet.HLT_Photon22(); }
	const int &HLT_Photon30() { return zmet.HLT_Photon30(); }
	const int &HLT_Photon36() { return zmet.HLT_Photon36(); }
	const int &HLT_Photon50() { return zmet.HLT_Photon50(); }
	const int &HLT_Photon75() { return zmet.HLT_Photon75(); }
	const int &HLT_Photon90() { return zmet.HLT_Photon90(); }
	const int &HLT_Photon120() { return zmet.HLT_Photon120(); }
	const int &HLT_Photon175() { return zmet.HLT_Photon175(); }
	const int &HLT_Photon165_HE10() { return zmet.HLT_Photon165_HE10(); }
	const int &HLT_Photon22_R9Id90_HE10_IsoM() { return zmet.HLT_Photon22_R9Id90_HE10_IsoM(); }
	const int &HLT_Photon30_R9Id90_HE10_IsoM() { return zmet.HLT_Photon30_R9Id90_HE10_IsoM(); }
	const int &HLT_Photon36_R9Id90_HE10_IsoM() { return zmet.HLT_Photon36_R9Id90_HE10_IsoM(); }
	const int &HLT_Photon50_R9Id90_HE10_IsoM() { return zmet.HLT_Photon50_R9Id90_HE10_IsoM(); }
	const int &HLT_Photon75_R9Id90_HE10_IsoM() { return zmet.HLT_Photon75_R9Id90_HE10_IsoM(); }
	const int &HLT_Photon90_R9Id90_HE10_IsoM() { return zmet.HLT_Photon90_R9Id90_HE10_IsoM(); }
	const int &HLT_Photon120_R9Id90_HE10_IsoM() { return zmet.HLT_Photon120_R9Id90_HE10_IsoM(); }
	const int &HLT_Photon165_R9Id90_HE10_IsoM() { return zmet.HLT_Photon165_R9Id90_HE10_IsoM(); }
	const float &dilmass() { return zmet.dilmass(); }
	const float &dilpt() { return zmet.dilpt(); }
	const float &dRll() { return zmet.dRll(); }
	const float &matched_neutralemf() { return zmet.matched_neutralemf(); }
	const bool &elveto() { return zmet.elveto(); }
	const int &nlep() { return zmet.nlep(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &lep_p4() { return zmet.lep_p4(); }
	const vector<float> &lep_pt() { return zmet.lep_pt(); }
	const vector<float> &lep_eta() { return zmet.lep_eta(); }
	const vector<float> &lep_phi() { return zmet.lep_phi(); }
	const vector<float> &lep_mass() { return zmet.lep_mass(); }
	const vector<int> &lep_charge() { return zmet.lep_charge(); }
	const vector<int> &lep_pdgId() { return zmet.lep_pdgId(); }
	const vector<float> &lep_dxy() { return zmet.lep_dxy(); }
	const vector<float> &lep_etaSC() { return zmet.lep_etaSC(); }
	const vector<float> &lep_dz() { return zmet.lep_dz(); }
	const vector<int> &lep_tightId() { return zmet.lep_tightId(); }
	const vector<float> &lep_relIso03() { return zmet.lep_relIso03(); }
	const vector<float> &lep_relIso03MREA() { return zmet.lep_relIso03MREA(); }
	const vector<float> &lep_relIso03MRDB() { return zmet.lep_relIso03MRDB(); }
	const vector<float> &lep_relIso03MRNC() { return zmet.lep_relIso03MRNC(); }
	const vector<float> &lep_relIso04() { return zmet.lep_relIso04(); }
	const vector<int> &lep_mcMatchId() { return zmet.lep_mcMatchId(); }
	const vector<int> &lep_lostHits() { return zmet.lep_lostHits(); }
	const vector<int> &lep_convVeto() { return zmet.lep_convVeto(); }
	const vector<int> &lep_tightCharge() { return zmet.lep_tightCharge(); }
	const vector<int> &lep_islead() { return zmet.lep_islead(); }
	const vector<int> &lep_istail() { return zmet.lep_istail(); }
	const int &ntau() { return zmet.ntau(); }
	const vector<float> &tau_pt() { return zmet.tau_pt(); }
	const vector<float> &tau_eta() { return zmet.tau_eta(); }
	const vector<float> &tau_phi() { return zmet.tau_phi(); }
	const vector<float> &tau_mass() { return zmet.tau_mass(); }
	const vector<int> &tau_charge() { return zmet.tau_charge(); }
	const vector<float> &tau_dxy() { return zmet.tau_dxy(); }
	const vector<float> &tau_dz() { return zmet.tau_dz(); }
	const vector<int> &tau_idCI3hit() { return zmet.tau_idCI3hit(); }
	const vector<float> &tau_isoCI3hit() { return zmet.tau_isoCI3hit(); }
	const int &ngamma() { return zmet.ngamma(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gamma_p4() { return zmet.gamma_p4(); }
	const vector<float> &gamma_pt() { return zmet.gamma_pt(); }
	const vector<float> &gamma_eta() { return zmet.gamma_eta(); }
	const vector<float> &gamma_phi() { return zmet.gamma_phi(); }
	const vector<float> &gamma_mass() { return zmet.gamma_mass(); }
	const vector<int> &gamma_mcMatchId() { return zmet.gamma_mcMatchId(); }
	const vector<float> &gamma_genIso() { return zmet.gamma_genIso(); }
	const vector<float> &gamma_chHadIso() { return zmet.gamma_chHadIso(); }
	const vector<float> &gamma_neuHadIso() { return zmet.gamma_neuHadIso(); }
	const vector<float> &gamma_phIso() { return zmet.gamma_phIso(); }
	const vector<float> &gamma_sigmaIetaIeta() { return zmet.gamma_sigmaIetaIeta(); }
	const vector<float> &gamma_r9() { return zmet.gamma_r9(); }
	const vector<float> &gamma_hOverE() { return zmet.gamma_hOverE(); }
	const vector<int> &gamma_idCutBased() { return zmet.gamma_idCutBased(); }
	const int &ngenPart() { return zmet.ngenPart(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genPart_p4() { return zmet.genPart_p4(); }
	const vector<float> &genPart_pt() { return zmet.genPart_pt(); }
	const vector<float> &genPart_eta() { return zmet.genPart_eta(); }
	const vector<float> &genPart_phi() { return zmet.genPart_phi(); }
	const vector<float> &genPart_mass() { return zmet.genPart_mass(); }
	const vector<int> &genPart_pdgId() { return zmet.genPart_pdgId(); }
	const vector<int> &genPart_status() { return zmet.genPart_status(); }
	const vector<float> &genPart_charge() { return zmet.genPart_charge(); }
	const vector<int> &genPart_motherId() { return zmet.genPart_motherId(); }
	const vector<int> &genPart_grandmaId() { return zmet.genPart_grandmaId(); }
	const vector<bool> &genPart_isp6status3() { return zmet.genPart_isp6status3(); }
	const int &gamma_nJet40() { return zmet.gamma_nJet40(); }
	const int &gamma_nBJet40() { return zmet.gamma_nBJet40(); }
	const int &ngenLep() { return zmet.ngenLep(); }
	const vector<float> &genLep_pt() { return zmet.genLep_pt(); }
	const vector<float> &genLep_eta() { return zmet.genLep_eta(); }
	const vector<float> &genLep_phi() { return zmet.genLep_phi(); }
	const vector<float> &genLep_mass() { return zmet.genLep_mass(); }
	const vector<int> &genLep_pdgId() { return zmet.genLep_pdgId(); }
	const vector<int> &genLep_status() { return zmet.genLep_status(); }
	const vector<float> &genLep_charge() { return zmet.genLep_charge(); }
	const vector<int> &genLep_sourceId() { return zmet.genLep_sourceId(); }
	const vector<bool> &genLep_isp6status3() { return zmet.genLep_isp6status3(); }
	const int &ngenTau() { return zmet.ngenTau(); }
	const vector<float> &genTau_pt() { return zmet.genTau_pt(); }
	const vector<float> &genTau_eta() { return zmet.genTau_eta(); }
	const vector<float> &genTau_phi() { return zmet.genTau_phi(); }
	const vector<float> &genTau_mass() { return zmet.genTau_mass(); }
	const vector<int> &genTau_pdgId() { return zmet.genTau_pdgId(); }
	const vector<int> &genTau_status() { return zmet.genTau_status(); }
	const vector<float> &genTau_charge() { return zmet.genTau_charge(); }
	const vector<int> &genTau_sourceId() { return zmet.genTau_sourceId(); }
	const int &ngenLepFromTau() { return zmet.ngenLepFromTau(); }
	const vector<float> &genLepFromTau_pt() { return zmet.genLepFromTau_pt(); }
	const vector<float> &genLepFromTau_eta() { return zmet.genLepFromTau_eta(); }
	const vector<float> &genLepFromTau_phi() { return zmet.genLepFromTau_phi(); }
	const vector<float> &genLepFromTau_mass() { return zmet.genLepFromTau_mass(); }
	const vector<int> &genLepFromTau_pdgId() { return zmet.genLepFromTau_pdgId(); }
	const vector<int> &genLepFromTau_status() { return zmet.genLepFromTau_status(); }
	const vector<float> &genLepFromTau_charge() { return zmet.genLepFromTau_charge(); }
	const vector<int> &genLepFromTau_sourceId() { return zmet.genLepFromTau_sourceId(); }
	const int &njet() { return zmet.njet(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &jet_p4() { return zmet.jet_p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &jets_p4() { return zmet.jets_p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &jets_eta30_p4() { return zmet.jets_eta30_p4(); }
	const vector<float> &jet_pt() { return zmet.jet_pt(); }
	const vector<float> &jet_eta() { return zmet.jet_eta(); }
	const vector<float> &jet_phi() { return zmet.jet_phi(); }
	const vector<float> &jet_mass() { return zmet.jet_mass(); }
	const vector<float> &jet_btagCSV() { return zmet.jet_btagCSV(); }
	const vector<float> &jet_rawPt() { return zmet.jet_rawPt(); }
	const vector<float> &jet_mcPt() { return zmet.jet_mcPt(); }
	const vector<int> &jet_mcFlavour() { return zmet.jet_mcFlavour(); }
	const vector<float> &jet_quarkGluonID() { return zmet.jet_quarkGluonID(); }
	const vector<float> &jet_area() { return zmet.jet_area(); }
	const vector<int> &jet_id() { return zmet.jet_id(); }
	const vector<int> &jet_puId() { return zmet.jet_puId(); }
	const float &chpfmet_trk_pt() { return zmet.chpfmet_trk_pt(); }
	const float &chpfmet_trk_phi() { return zmet.chpfmet_trk_phi(); }
	const float &chphpfmet_trk_pt() { return zmet.chphpfmet_trk_pt(); }
	const float &chphpfmet_trk_phi() { return zmet.chphpfmet_trk_phi(); }
	const float &nunophpfmet_trk_pt() { return zmet.nunophpfmet_trk_pt(); }
	const float &nunophpfmet_trk_phi() { return zmet.nunophpfmet_trk_phi(); }
	const float &nunophpfmet_fwd_pt() { return zmet.nunophpfmet_fwd_pt(); }
	const float &nunophpfmet_fwd_phi() { return zmet.nunophpfmet_fwd_phi(); }
	const float &nunophpfmet_all_pt() { return zmet.nunophpfmet_all_pt(); }
	const float &nunophpfmet_all_phi() { return zmet.nunophpfmet_all_phi(); }
	const float &nupfmet_trk_pt() { return zmet.nupfmet_trk_pt(); }
	const float &nupfmet_trk_phi() { return zmet.nupfmet_trk_phi(); }
	const float &nupfmet_fwd_pt() { return zmet.nupfmet_fwd_pt(); }
	const float &nupfmet_fwd_phi() { return zmet.nupfmet_fwd_phi(); }
	const float &nupfmet_all_pt() { return zmet.nupfmet_all_pt(); }
	const float &nupfmet_all_phi() { return zmet.nupfmet_all_phi(); }
	const int &hyp_type() { return zmet.hyp_type(); }
	const int &evt_type() { return zmet.evt_type(); }
}
