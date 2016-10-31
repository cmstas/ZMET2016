#include <stdexcept>
#include <iostream>
#include <map>

#include "TH1.h"
#include "TMath.h"
#include "TH1F.h"
#include "TFile.h"
#include "TCollection.h"
#include "TDirectory.h"
#include "TKey.h"

#include "AnalysisSelections.h"
#include "histTools.h"
#include "ZMET.h"

#include "../../CORE/SimPa.h"
#include "../../CORE/Tools/MT2/MT2.h"
#include "../../CORE/Tools/MT2/MT2Utility.h"

using namespace std;

bool passBaselineSelections()
{
  if( zmet.njets()                       < 2         ) return false; // >=2 jets  
  return true;
}

bool passMETFilters()
{

  if( zmet.isData() ){
	if( zmet.mass_gluino() < 0 ){
	  if (!zmet.Flag_EcalDeadCellTriggerPrimitiveFilter()      ) return false; // MC
	  if (!zmet.Flag_badChargedCandidateFilter         ()      ) return false; // MC
	  if (!zmet.Flag_HBHENoiseFilter                   ()      ) return false;
	  if (!zmet.Flag_HBHEIsoNoiseFilter                ()      ) return false;
	  if (!zmet.Flag_goodVertices                      ()      ) return false;
	  if (!zmet.Flag_eeBadScFilter                     ()      ) return false;
	  if (!zmet.Flag_globalTightHalo2016               ()      ) return false;
	  if( zmet.isData() ){
		if (zmet.nVert                                 () == 0 ) return false;
		if (!zmet.Flag_badMuonFilter                   ()      ) return false;
	  }
	}
	else{
	  if( zmet.met_T1CHS_miniAOD_CORE_pt() > 100 && (zmet.met_pt() / zmet.met_calo_pt()) > 5 ) return false;
	}
  }
  
  return true;
}

bool passSignalRegionSelection( string selection )
{

  bool jes_up = false;
  bool jes_dn = false;
  
  if( TString(selection).Contains("jes_up")      ) jes_up      = true;
  if( TString(selection).Contains("jes_dn")      ) jes_dn      = true;

  float event_met_pt = zmet.met_pt();
  float event_met_ph = zmet.met_phi();

  event_met_pt = zmet.met_T1CHS_miniAOD_CORE_pt();
  event_met_ph = zmet.met_T1CHS_miniAOD_CORE_phi();

  float event_ht    = zmet.ht();
  float event_njets = zmet.njets();

  if( jes_up ){
	event_ht     = zmet.ht_up();
	event_njets  = zmet.njets_up();
	event_met_pt = zmet.met_T1CHS_miniAOD_CORE_up_pt();
	event_met_ph = zmet.met_T1CHS_miniAOD_CORE_up_phi();

  }else if( jes_dn ){
	event_ht     = zmet.ht_dn();
	event_njets  = zmet.njets_dn();
	event_met_pt = zmet.met_T1CHS_miniAOD_CORE_dn_pt();
	event_met_ph = zmet.met_T1CHS_miniAOD_CORE_dn_phi();

  }

  if( TString(selection).Contains("fastsimMET") ){
	event_met_pt = (zmet.met_T1CHS_miniAOD_CORE_pt()  + zmet.met_genPt() )/2.0;
	event_met_ph = (zmet.met_T1CHS_miniAOD_CORE_phi() + zmet.met_genPhi())/2.0;
  }
  
  //splitting the photon for MT2
  // Particle(Float_t pt, Float_t eta, Float_t phi, Float_t mass, Float_t width_);
  //   //A test Z boson with pt = 100 GeV, eta = 0, phi = 0, mass 91.2GeV, and width 2 GeV
  Particle lepton1(0, 0, 0, 0, 0);
  Particle lepton2(0, 0, 0, 0, 0);

  LorentzVector lep1_p4(0,0,0,0);
  LorentzVector lep2_p4(0,0,0,0);

  if( zmet.evt_type() == 2 && zmet.ngamma() > 0 ){

  	Particle iphoton(0, 0, 0, 0, 0);  
  	iphoton = Particle(zmet.gamma_p4().at(0).pt(), zmet.gamma_p4().at(0).eta(), zmet.gamma_p4().at(0).phi(), 91, 2);

  	TRandom3 ran(0);   
  	ProduceDecay(ran, &iphoton, &lepton1, &lepton2, 0.001, 0.001); 

  	lep1_p4.SetPx( lepton1.p.X()); lep1_p4.SetPy( lepton1.p.Y()); lep1_p4.SetPz( lepton1.p.Z()); lep1_p4.SetE ( lepton1.p.E());
  	lep2_p4.SetPx( lepton2.p.X()); lep2_p4.SetPy( lepton2.p.Y()); lep2_p4.SetPz( lepton2.p.Z()); lep2_p4.SetE ( lepton2.p.E());

  	// cout<<MT2( event_met_pt, event_met_ph, lep1_p4, lep2_p4, 0.0, false )<<endl;
  }

  try
	{

	  if( TString(selection).Contains("newSR_A"        ) ){
		if( !( event_njets == 2 || event_njets == 3 )                                                        )return false; // 2 or 3 jets
		if( TString(selection).Contains("bveto" ) && event_ht < 500                                          )return false; // HT 500
		if( TString(selection).Contains("withb" ) && event_ht < 200                                          )return false; // HT 500
	  }
	  if( TString(selection).Contains("newSR_B"        ) ){
		if( !( event_njets == 4 || event_njets == 5 )                                                        )return false; // 4 or 5 jets
		if( TString(selection).Contains("bveto" ) && event_ht < 500                                          )return false; // HT 500
		if( TString(selection).Contains("withb" ) && event_ht < 200                                          )return false; // HT 500
	  }
	  if( TString(selection).Contains("newSR_C"        ) && !((event_njets >= 6 ))                           ) return false; // >= 6 jets

	  if( TString(selection).Contains("dphicut1p0"     ) && !(event_njets > 1 && zmet.dphi_metj1() > 1.0)    ) return false; // phi MET jet1 > 1.0
	  if( TString(selection).Contains("dphicut0p4"     ) && !(event_njets > 1 && zmet.dphi_metj1() > 0.4)    ) return false; // phi MET jet1 > 0.4
	  if( TString(selection).Contains("dphi2cut0p4"    ) && !(event_njets > 1 && zmet.dphi_metj2() > 0.4)    ) return false; // phi MET jet2 > 0.4

	  if( TString(selection).Contains("3lepveto"       ) && !(zmet.nveto_leptons() < 1 && zmet.nlep() == 2 ) ) return false; // 3rd lep veto
	  if( TString(selection).Contains("3lvetotight"    ) && !(zmet.nisoTrack_mt2() < 1 )                     ) return false;

	  if( TString(selection).Contains("mdzwindow" ) ){
		if( zmet.evt_type() == 0 && !( zmet.dilmass() > 86   && zmet.dilmass() < 96   ) ) return false; // mZ +- 5 GeV
	  }
	  
	  if( TString(selection).Contains("baseline2016"   ) ){
		if( !(event_njets > 1 && zmet.dphi_metj1() > 0.4)    ) return false; // phi MET jet1 > 0.4
		if( !(event_njets > 1 && zmet.dphi_metj2() > 0.4)    ) return false; // phi MET jet2 > 0.4
		if( !(zmet.nveto_leptons() < 1 && zmet.nlep() == 2 ) ) return false; // 3rd lep veto
		if( zmet.evt_type() == 0 ){
		  if( TString(selection).Contains("bveto") && MT2( event_met_pt, event_met_ph, zmet.lep_p4().at(0), zmet.lep_p4().at(1), 0.0, false ) <=  80 ) return false; // mt2 cut on dilep evts
		  if( TString(selection).Contains("withb") && MT2( event_met_pt, event_met_ph, zmet.lep_p4().at(0), zmet.lep_p4().at(1), 0.0, false ) <= 100 ) return false; // mt2 cut on dilep evts
		}
		if( zmet.evt_type() == 2 ){
		  if( !( abs(lep1_p4.eta()) < 2.4 && abs(lep2_p4.eta()) < 2.4 )             ) return false; // decayed leps eta < 2.4
		  if( !( ( abs(lep1_p4.eta()) < 1.4 || abs(lep1_p4.eta()) > 1.6 ) &&
				 ( abs(lep2_p4.eta()) < 1.4 || abs(lep2_p4.eta()) > 1.6 ) )         ) return false; // decayed leps veto xition
		  if( TString(selection).Contains("bveto") && MT2( event_met_pt, event_met_ph, zmet.lep_p4().at(0), zmet.lep_p4().at(1), 0.0, false ) <=  80 ) return false; // mt2 cut on dilep evts
		  if( TString(selection).Contains("withb") && MT2( event_met_pt, event_met_ph, zmet.lep_p4().at(0), zmet.lep_p4().at(1), 0.0, false ) <= 100 ) return false; // mt2 cut on dilep evts
		}
	  }
	  
	  if( TString(selection).Contains("metcut"         ) && !(event_met_pt > 100)                            ) return false; // MET > 100

	  if( TString(selection).Contains("mt2cut"         ) ){
		if( zmet.evt_type() == 0 ){
		  if( TString(selection).Contains("bveto") && MT2( event_met_pt, event_met_ph, zmet.lep_p4().at(0), zmet.lep_p4().at(1), 0.0, false ) <=  80 ) return false; // mt2 cut on dilep evts
		  if( TString(selection).Contains("withb") && MT2( event_met_pt, event_met_ph, zmet.lep_p4().at(0), zmet.lep_p4().at(1), 0.0, false ) <= 100 ) return false; // mt2 cut on dilep evts
		}
		if( zmet.evt_type() == 2 ){
		  if( !( abs(lep1_p4.eta()) < 2.4 && abs(lep2_p4.eta()) < 2.4 )             ) return false; // decayed leps eta < 2.4
		  if( !( ( abs(lep1_p4.eta()) < 1.4 || abs(lep1_p4.eta()) > 1.6 ) &&
				 ( abs(lep2_p4.eta()) < 1.4 || abs(lep2_p4.eta()) > 1.6 ) )         ) return false; // decayed leps veto xition
		  if( TString(selection).Contains("bveto") && MT2( event_met_pt, event_met_ph, lep1_p4, lep2_p4, 0.0, false ) <=  80 ) return false; // mt2 cut on dilep evts
		  if( TString(selection).Contains("withb") && MT2( event_met_pt, event_met_ph, lep1_p4, lep2_p4, 0.0, false ) <= 100 ) return false; // mt2 cut on dilep evts
		}
	  }
	  
	  if( TString(selection).Contains("loosephoton"    ) && !((zmet.evt_type() == 2 && isLoosePhoton(0))  || zmet.evt_type() != 2) ) return false; //tight photon selection for systematics study
	  if( TString(selection).Contains("mediumphoton"   ) && !((zmet.evt_type() == 2 && isMediumPhoton(0)) || zmet.evt_type() != 2) ) return false; //tight photon selection for systematics study
	  if( TString(selection).Contains("tightphoton"    ) && !((zmet.evt_type() == 2 && isTightPhoton(0))  || zmet.evt_type() != 2) ) return false; //tight photon selection for systematics study

	  if( TString(selection).Contains("withtightb"     ) && zmet.nBJetTight()  < 1 ) return false; // require tight b-tag
	  if( TString(selection).Contains("bveto"          ) && zmet.nBJetMedium() > 0 ) return false; // bveto
	  if( TString(selection).Contains("withb"          ) && zmet.nBJetMedium() < 1 ) return false; // at least 1 b-tag
	  if( TString(selection).Contains("with2"          ) && zmet.nBJetMedium() < 2 ) return false; // at least 2 b-tags

	  if( TString(selection).Contains("SRA"            ) && !((event_njets == 2 ||
															   event_njets == 3  ) &&
															  (event_ht    > 400 )) ) return false; // high HT region
	  if( TString(selection).Contains("SRB"            ) && event_njets < 4         ) return false; // large njets

	  if( TString(selection).Contains("twojets"        ) && event_njets != 2 ) return false; // exactly 2 jets
	  if( TString(selection).Contains("2jets_inclusive") && event_njets <  2 ) return false; // at least 2 jets
	  if( TString(selection).Contains("3jets_inclusive") && event_njets <  3 ) return false; // at least 3 jets

	  if( TString(selection).Contains( "SR_ATLAS" ) ){
		if( zmet.njets() < 2                                               ) return false; // >= 2 jets
		if( acos( cos( event_met_ph - zmet.jets_p4().at(0).phi() ) ) < 0.4 ) return false; // dphi(MET,jet1) > 0.4
		if( acos( cos( event_met_ph - zmet.jets_p4().at(1).phi() ) ) < 0.4 ) return false; // dphi(MET,jet2) > 0.4
		if( zmet.evt_type() == 2 ){
		  if( event_ht +
			  zmet.gamma_pt().at(0) < 600 ) return false; // photon + HT > 600
		}		  
		if( zmet.evt_type() == 0 ){
		  if( zmet.lep_pt().at(0) < 50    ) return false; // lep1 > 50 GeV
		  if( zmet.lep_pt().at(1) < 25    ) return false; // lep1 > 25 GeV
		  if( event_ht +
			  zmet.lep_pt().at(0) +
			  zmet.lep_pt().at(1) < 600   ) return false; // lep1 + lep2 + HT > 600
		}
	  }
		  


		  std::pair<LorentzVector, LorentzVector> lepsFromDecayedZ;
	  if( zmet.evt_type() == 0 && ( zmet.nlep() == 2) ){
		LorentzVector z_p4(zmet.lep_p4().at(0).X()+zmet.lep_p4().at(1).X(),
						   zmet.lep_p4().at(0).Y()+zmet.lep_p4().at(1).Y(),
						   zmet.lep_p4().at(0).Z()+zmet.lep_p4().at(1).Z(),
						   zmet.lep_p4().at(0).E()+zmet.lep_p4().at(1).E());
		lepsFromDecayedZ = returnDecayProducts( z_p4 );
	  }
	  
	  if( TString(selection).Contains("SR_EWK" ) && 
		  !( (
			  ( zmet.evt_type() == 0 && ( (zmet.nveto_leptons() < 1 && zmet.nlep() == 2 ) && MT2( event_met_pt, event_met_ph, zmet.lep_p4().at(0), zmet.lep_p4().at(1), 0.0, false ) > 80         ) ) || // dilep cuts
			  // ( zmet.evt_type() == 0 && ( zmet.nlep() == 2 && MT2( event_met_pt, event_met_ph, lepsFromDecayedZ.first, lepsFromDecayedZ.second, 0.0, false ) > 80         ) ) || // dilep cuts
			  ( zmet.evt_type() == 2 &&
				( (   abs(zmet.decayedphoton_lep1_p4().eta()) < 2.4 && abs(zmet.decayedphoton_lep2_p4().eta()) < 2.4 ) &&
				  ( ( abs(zmet.decayedphoton_lep1_p4().eta()) < 1.4 || abs(zmet.decayedphoton_lep1_p4().eta()) > 1.6 ) &&
					( abs(zmet.decayedphoton_lep2_p4().eta()) < 1.4 || abs(zmet.decayedphoton_lep2_p4().eta()) > 1.6 ) ) &&
				  // MT2( event_met_pt, event_met_ph, zmet.decayedphoton_lep1_p4(), zmet.decayedphoton_lep2_p4(), 0.0, false ) > 80 ) ) ) && // photon+jets cuts
				  MT2( event_met_pt, event_met_ph, lep1_p4, lep2_p4, 0.0, false ) > 80 ) ) ) && // photon+jets cuts
			 // ( ( abs(lep1_p4.eta()) < 2.4 && abs(lep2_p4.eta()) < 2.4 ) &&
			 //   ( ( abs(lep1_p4.eta()) < 1.4 || abs(lep1_p4.eta()) > 1.6 ) &&
			 // 	( abs(lep2_p4.eta()) < 1.4 || abs(lep2_p4.eta()) > 1.6 ) ) &&
			 //   MT2( event_met_pt, event_met_ph, lep1_p4, lep2_p4, 0.0, false ) > 80 ) ) ) && // photon+jets cuts
			 ( event_njets > 1 && zmet.nBJetMedium() == 0 && zmet.dphi_metj1() > 1.0 ) ) // common cuts
		  )return false; 

	  if( TString(selection).Contains("SR_ZH" ) && 
		  !( (( zmet.evt_type() == 0 && ( zmet.nlep() == 2 && zmet.mt2b() > 200                          ) ) || // dilep cuts
			  ( zmet.evt_type() == 2                                                                     ) ) && // photon+jets cuts
			 ( zmet.njets() > 1 && zmet.nBJetMedium() > 1 && zmet.mbb_csv() > 90 && zmet.mbb_csv() < 150 ) )  // common cuts
		  )return false; 
	  if( TString(selection).Contains("forward"        ) && !((zmet.evt_type() == 0 &&
															   ((abs(zmet.lep_eta().at(0)) < 1.4 && abs(zmet.lep_eta().at(1)) > 1.6) ||
																(abs(zmet.lep_eta().at(1)) < 1.4 && abs(zmet.lep_eta().at(0)) > 1.6) ||
																(abs(zmet.lep_eta().at(0)) > 1.6 && abs(zmet.lep_eta().at(1)) > 1.6) ) ) ||
															  (zmet.evt_type() == 2 ) ) ) return false; //edge forward
	  if( TString(selection).Contains("central"        ) && !((zmet.evt_type() == 0 &&
															   (abs(zmet.lep_eta().at(0)) < 1.4 && abs(zmet.lep_eta().at(1)) < 1.4  ) ) ||
															  (zmet.evt_type() == 2 ) ) ) return false; //edge central  														 

	  if( TString(selection).Contains("CR3lep"       ) && !(zmet.evt_type() != 2 &&
															( zmet.nlep() == 3 &&
															  zmet.lep_pt().at(0) > 20 &&
															  zmet.lep_pt().at(1) > 20 &&
															  zmet.lep_pt().at(2) > 20 &&
															  zmet.nBJetMedium() == 0 &&
															  // zmet.met_pt() > 50 &&
															  (((zmet.lep_pdgId().at(0)*zmet.lep_pdgId().at(1) == -121 ||
																 zmet.lep_pdgId().at(0)*zmet.lep_pdgId().at(1) == -169) &&
																(zmet.lep_p4().at(0)+zmet.lep_p4().at(1)).mass() > 81 &&
																(zmet.lep_p4().at(0)+zmet.lep_p4().at(1)).mass() < 101 ) ||

														   ((zmet.lep_pdgId().at(0)*zmet.lep_pdgId().at(2) == -121 ||
															 zmet.lep_pdgId().at(0)*zmet.lep_pdgId().at(2) == -169) &&
															(zmet.lep_p4().at(0)+zmet.lep_p4().at(2)).mass() > 81 &&
															(zmet.lep_p4().at(0)+zmet.lep_p4().at(2)).mass() < 101 ) ||

														   ((zmet.lep_pdgId().at(1)*zmet.lep_pdgId().at(2) == -121 ||
															 zmet.lep_pdgId().at(1)*zmet.lep_pdgId().at(2) == -169) &&
															(zmet.lep_p4().at(1)+zmet.lep_p4().at(2)).mass() > 81 &&
															(zmet.lep_p4().at(1)+zmet.lep_p4().at(2)).mass() < 101 ) 
														   ))))return false;

  if( TString(selection).Contains("CR4lep"       ) && !(zmet.evt_type() != 2 &&
														( zmet.nlep() == 4 &&
														  zmet.lep_pt().at(0) > 20 &&
														  zmet.lep_pt().at(1) > 20 &&
														  zmet.lep_pt().at(2) > 20 &&
														  zmet.lep_pt().at(3) > 20 &&
														  // zmet.met_pt() > 50 &&
														  (((zmet.lep_pdgId().at(0)*zmet.lep_pdgId().at(1) == -121 ||
															 zmet.lep_pdgId().at(0)*zmet.lep_pdgId().at(1) == -169) &&
															(zmet.lep_p4().at(0)+zmet.lep_p4().at(1)).mass() > 81 &&
															(zmet.lep_p4().at(0)+zmet.lep_p4().at(1)).mass() < 101 ) ||

														   ((zmet.lep_pdgId().at(0)*zmet.lep_pdgId().at(2) == -121 ||
															 zmet.lep_pdgId().at(0)*zmet.lep_pdgId().at(2) == -169) &&
															(zmet.lep_p4().at(0)+zmet.lep_p4().at(2)).mass() > 81 &&
															(zmet.lep_p4().at(0)+zmet.lep_p4().at(2)).mass() < 101 ) ||

														   ((zmet.lep_pdgId().at(0)*zmet.lep_pdgId().at(3) == -121 ||
															 zmet.lep_pdgId().at(0)*zmet.lep_pdgId().at(3) == -169) &&
															(zmet.lep_p4().at(0)+zmet.lep_p4().at(3)).mass() > 81 &&
															(zmet.lep_p4().at(0)+zmet.lep_p4().at(3)).mass() < 101 ) ||

														   ((zmet.lep_pdgId().at(1)*zmet.lep_pdgId().at(2) == -121 ||
															 zmet.lep_pdgId().at(1)*zmet.lep_pdgId().at(2) == -169) &&
															(zmet.lep_p4().at(1)+zmet.lep_p4().at(2)).mass() > 81 &&
															(zmet.lep_p4().at(1)+zmet.lep_p4().at(2)).mass() < 101 ) ||

														   ((zmet.lep_pdgId().at(1)*zmet.lep_pdgId().at(3) == -121 ||
															 zmet.lep_pdgId().at(1)*zmet.lep_pdgId().at(3) == -169) &&
															(zmet.lep_p4().at(1)+zmet.lep_p4().at(3)).mass() > 81 &&
															(zmet.lep_p4().at(1)+zmet.lep_p4().at(3)).mass() < 101 ) ||

														   ((zmet.lep_pdgId().at(2)*zmet.lep_pdgId().at(3) == -121 ||
															 zmet.lep_pdgId().at(2)*zmet.lep_pdgId().at(3) == -169) &&
															(zmet.lep_p4().at(2)+zmet.lep_p4().at(3)).mass() > 81 &&
															(zmet.lep_p4().at(2)+zmet.lep_p4().at(3)).mass() < 101 )
														   ))))return false;

	}
  catch (exception &e)
	{
	  cout<<"failed due to exception: "<<e.what()<<endl;
	}
  
  return true;
}

bool eventHas2GoodLeps()
{
  if( zmet.nlep()                        < 2         ) return false; // require at least 2 good leptons
  if( zmet.lep_pt().at(0)                < 20        ) return false; // leading lep pT > 25 GeV
  if( zmet.lep_pt().at(1)                < 20        ) return false; // tailing lep pT > 20 GeV
  if( abs(zmet.lep_p4().at(0).eta())     > 2.4       ) return false; // eta < 2.4
  if( abs(zmet.lep_p4().at(1).eta())     > 2.4       ) return false; // eta < 2.4
  if( abs(zmet.lep_p4().at(0).eta())     > 1.4 &&
	  abs(zmet.lep_p4().at(0).eta())     < 1.6       ) return false;
  if( abs(zmet.lep_p4().at(1).eta())     > 1.4 &&
	  abs(zmet.lep_p4().at(1).eta())     < 1.6       ) return false; // veto xition region
  if( zmet.dRll()                        < 0.1       ) return false;
  if( !(zmet.hyp_type() == 0 ||					     
		zmet.hyp_type() == 1 ||					     
		zmet.hyp_type() == 2 )                       ) return false; // require explicit dilepton event
  if( !(zmet.evt_type() == 0 )                       ) return false; // require opposite sign
  if( !(zmet.dilmass() > 81 && zmet.dilmass() < 101) ) return false; // on-Z
  if( !(zmet.dilpt() > 50)                           ) return false; // Z pT > 50 GeV
  return true;
}

bool eventHas3Jets()
{
  if( zmet.njets()                       < 3         ) return false; // require at least 3 jets
  return true;
}

bool eventHasGoodPhoton()
{
  if( zmet.ngamma()                      <  1    ) return false; // require at least 1 good photon
  if( zmet.evt_type()                    != 2    ) return false; // photon + jets events
  if( zmet.gamma_pt().at(0)              < 22    ) return false; // photon pt > 22 GeV
  if( abs(zmet.gamma_p4().at(0).eta())   > 1.4 &&
  	  abs(zmet.gamma_p4().at(0).eta())   < 1.6   ) return false; // veto xition region
  if( abs(zmet.gamma_p4().at(0).eta())   > 2.4   ) return false; // photon in EC or EB
  if( zmet.gamma_hOverE().at(0)          > 0.1   ) return false; // H/E < 0.1	  
  // if( zmet.matched_neutralemf()          < 0.7   ) return false; // jet neutral EM fraction cut
  if( zmet.matched_emf()                 < 0.7   ) return false; // jet neutral EM fraction cut
  if( acos( cos( zmet.gamma_phi().at(0)			 
				 - zmet.met_phi() ) )    < 0.14  ) return false; // kill photons aligned with MET
  if( zmet.elveto()                              ) return false; // veto pixel match
  return true;  
}

bool passPhotonTrigger()
{
  if(      passPhotonTrigger22()  ) return true;
  else if( passPhotonTrigger30()  ) return true;
  else if( passPhotonTrigger36()  ) return true;
  else if( passPhotonTrigger50()  ) return true;
  else if( passPhotonTrigger75()  ) return true;
  else if( passPhotonTrigger90()  ) return true;
  else if( passPhotonTrigger120() ) return true;
  else if( passPhotonTrigger165() ) return true;
  return false;
}

bool passPhotonTrigger22()
{
  // if( zmet.HLT_Photon22_R9Id90_HE10_IsoM()  > 0 && zmet.gamma_pt().at(0) > 25   && zmet.gamma_pt().at(0) < 35  ) return true;
  if( zmet.HLT_Photon22_R9Id90_HE10_IsoM()  > 0 && zmet.gamma_pt().at(0) < 33  ) return true;
  return false;
}

bool passPhotonTrigger30()
{
  // if( zmet.HLT_Photon30_R9Id90_HE10_IsoM()  > 0 && zmet.gamma_pt().at(0) > 35  && zmet.gamma_pt().at(0) < 40  ) return true;
  if( zmet.HLT_Photon30_R9Id90_HE10_IsoM()  > 0 && zmet.gamma_pt().at(0) > 33 ) return true;
  return false;
}

bool passPhotonTrigger36()
{
  // if( zmet.HLT_Photon36_R9Id90_HE10_IsoM()  > 0 && zmet.gamma_pt().at(0) > 40  && zmet.gamma_pt().at(0) < 60  ) return true;
  if( zmet.HLT_Photon36_R9Id90_HE10_IsoM()  > 0 ) return true;
  return false;
}

bool passPhotonTrigger50()
{
  // if( zmet.HLT_Photon50_R9Id90_HE10_IsoM()  > 0 && zmet.gamma_pt().at(0) > 60  && zmet.gamma_pt().at(0) < 80  ) return true;
  if( zmet.HLT_Photon50_R9Id90_HE10_IsoM()  > 0 ) return true;
  return false;
}

bool passPhotonTrigger75()
{
  // if( zmet.HLT_Photon75_R9Id90_HE10_IsoM()  > 0 && zmet.gamma_pt().at(0) > 80  && zmet.gamma_pt().at(0) < 100 ) return true;
  if( zmet.HLT_Photon75_R9Id90_HE10_IsoM()  > 0 ) return true;
  return false;
}

bool passPhotonTrigger90()
{
  // if( zmet.HLT_Photon90_R9Id90_HE10_IsoM()  > 0 && zmet.gamma_pt().at(0) > 100 && zmet.gamma_pt().at(0) < 125 ) return true;
  if( zmet.HLT_Photon90_R9Id90_HE10_IsoM()  > 0 ) return true;
  return false;
}

bool passPhotonTrigger120()
{
  // if( zmet.HLT_Photon120_R9Id90_HE10_IsoM() > 0 && zmet.gamma_pt().at(0) > 125 && zmet.gamma_pt().at(0) < 170 ) return true;
  if( zmet.HLT_Photon120_R9Id90_HE10_IsoM() > 0 ) return true;
  return false;
}

bool passPhotonTrigger165()
{
  // if( zmet.HLT_Photon165_R9Id90_HE10_IsoM() > 0 && zmet.gamma_pt().at(0) > 170                                ) return true;
  if( zmet.HLT_Photon165_R9Id90_HE10_IsoM() > 0 ) return true;
  return false;
}

int getPrescale()
{
  if( !( zmet.HLT_Photon22_R9Id90_HE10_IsoM()  > 0 ||
		 zmet.HLT_Photon30_R9Id90_HE10_IsoM()  > 0 ||
		 zmet.HLT_Photon36_R9Id90_HE10_IsoM()  > 0 ||
		 zmet.HLT_Photon50_R9Id90_HE10_IsoM()  > 0 ||
		 zmet.HLT_Photon75_R9Id90_HE10_IsoM()  > 0 || 
		 zmet.HLT_Photon90_R9Id90_HE10_IsoM()  > 0 || 
		 zmet.HLT_Photon120_R9Id90_HE10_IsoM() > 0 ||
		 zmet.HLT_Photon165_R9Id90_HE10_IsoM() > 0 
		 ) ) return 0;
  if(      passPhotonTrigger22()  ) return zmet.HLT_Photon22_R9Id90_HE10_IsoM();
  else if( passPhotonTrigger30()  ) return zmet.HLT_Photon30_R9Id90_HE10_IsoM();
  else if( passPhotonTrigger36()  ) return zmet.HLT_Photon36_R9Id90_HE10_IsoM();
  else if( passPhotonTrigger50()  ) return zmet.HLT_Photon50_R9Id90_HE10_IsoM();
  else if( passPhotonTrigger75()  ) return zmet.HLT_Photon75_R9Id90_HE10_IsoM();
  else if( passPhotonTrigger90()  ) return zmet.HLT_Photon90_R9Id90_HE10_IsoM();
  else if( passPhotonTrigger120() ) return zmet.HLT_Photon120_R9Id90_HE10_IsoM();
  else if( passPhotonTrigger165() ) return zmet.HLT_Photon165_R9Id90_HE10_IsoM();
  return -1; // should not get here
}

int getPrescaleNoBins()
{
  if( !( zmet.HLT_Photon22_R9Id90_HE10_IsoM()  > 0 ||
		 zmet.HLT_Photon30_R9Id90_HE10_IsoM()  > 0 ||
		 zmet.HLT_Photon36_R9Id90_HE10_IsoM()  > 0 ||
		 zmet.HLT_Photon50_R9Id90_HE10_IsoM()  > 0 ||
		 zmet.HLT_Photon75_R9Id90_HE10_IsoM()  > 0 || 
		 zmet.HLT_Photon90_R9Id90_HE10_IsoM()  > 0 || 
		 zmet.HLT_Photon120_R9Id90_HE10_IsoM() > 0 ||
		 zmet.HLT_Photon165_R9Id90_HE10_IsoM() > 0 
		 ) ) return 0;
  if(      zmet.HLT_Photon165_R9Id90_HE10_IsoM() > 0 ) return zmet.HLT_Photon165_R9Id90_HE10_IsoM();
  else if( zmet.HLT_Photon120_R9Id90_HE10_IsoM() > 0 ) return zmet.HLT_Photon120_R9Id90_HE10_IsoM();
  else if( zmet.HLT_Photon90_R9Id90_HE10_IsoM()  > 0 ) return zmet.HLT_Photon90_R9Id90_HE10_IsoM();
  else if( zmet.HLT_Photon75_R9Id90_HE10_IsoM()  > 0 ) return zmet.HLT_Photon75_R9Id90_HE10_IsoM();
  else if( zmet.HLT_Photon50_R9Id90_HE10_IsoM()  > 0 ) return zmet.HLT_Photon50_R9Id90_HE10_IsoM();
  else if( zmet.HLT_Photon36_R9Id90_HE10_IsoM()  > 0 ) return zmet.HLT_Photon36_R9Id90_HE10_IsoM();
  else if( zmet.HLT_Photon30_R9Id90_HE10_IsoM()  > 0 && zmet.gamma_pt().at(0) < 55 ) return zmet.HLT_Photon30_R9Id90_HE10_IsoM()*15;
  else if( zmet.HLT_Photon22_R9Id90_HE10_IsoM()  > 0 && zmet.gamma_pt().at(0) < 33 ) return zmet.HLT_Photon22_R9Id90_HE10_IsoM()*37.5;
  // else if( zmet.HLT_Photon22_R9Id90_HE10_IsoM()  > 0 ) return 0;
  return -1; // should not get here
}

int getPrescaleNoBins_nol1ps()
{
  if( !( zmet.HLT_Photon22_R9Id90_HE10_IsoM()  > 0 ||
		 zmet.HLT_Photon30_R9Id90_HE10_IsoM()  > 0 ||
		 zmet.HLT_Photon36_R9Id90_HE10_IsoM()  > 0 ||
		 zmet.HLT_Photon50_R9Id90_HE10_IsoM()  > 0 ||
		 zmet.HLT_Photon75_R9Id90_HE10_IsoM()  > 0 || 
		 zmet.HLT_Photon90_R9Id90_HE10_IsoM()  > 0 || 
		 zmet.HLT_Photon120_R9Id90_HE10_IsoM() > 0 ||
		 zmet.HLT_Photon165_R9Id90_HE10_IsoM() > 0 ||
		 zmet.HLT_Photon165_HE10() > 0
		 ) ) return 0;
  if(     (zmet.HLT_Photon165_R9Id90_HE10_IsoM() > 0 ||
  		   zmet.HLT_Photon165_HE10() > 0)            &&                               zmet.gamma_pt().at(0) > 180 ) return zmet.HLT_Photon165_R9Id90_HE10_IsoM();
  else if( zmet.HLT_Photon120_R9Id90_HE10_IsoM() > 0 &&                               zmet.gamma_pt().at(0) > 135 ) return zmet.HLT_Photon120_R9Id90_HE10_IsoM();
  else if( zmet.HLT_Photon90_R9Id90_HE10_IsoM()  > 0 &&                               zmet.gamma_pt().at(0) > 105 ) return zmet.HLT_Photon90_R9Id90_HE10_IsoM();
  else if( zmet.HLT_Photon75_R9Id90_HE10_IsoM()  > 0 &&                               zmet.gamma_pt().at(0) > 85  ) return zmet.HLT_Photon75_R9Id90_HE10_IsoM();
  else if( zmet.HLT_Photon50_R9Id90_HE10_IsoM()  > 0 &&                               zmet.gamma_pt().at(0) > 55  ) return zmet.HLT_Photon50_R9Id90_HE10_IsoM();
  // normalized using higher pT trigger
  else if( zmet.HLT_Photon36_R9Id90_HE10_IsoM()  > 0 && zmet.gamma_pt().at(0) < 55 && zmet.gamma_pt().at(0) > 40 ) return 134;
  else if( zmet.HLT_Photon30_R9Id90_HE10_IsoM()  > 0 && zmet.gamma_pt().at(0) < 40 && zmet.gamma_pt().at(0) > 33 ) return 269;
  else if( zmet.HLT_Photon22_R9Id90_HE10_IsoM()  > 0 && zmet.gamma_pt().at(0) < 33                               ) return 1667;

  return -1; // should not get here
}

bool highHT_zjinc( string samplename )
{
  if( TString(samplename).Contains("m50inc") ){
	if( zmet.gen_ht() > 100 ) return true;
  }
  return false;
}



//////////////////////
// Photon Isolation //
//////////////////////

// from https://indico.cern.ch/event/369239/contribution/2/attachments/1134693/1623149/spring15_pcb.pdf
float photon_CHEA03( int photonIdx )
{
  return 0.0;

  // float eta = zmet.gamma_p4().at(photonIdx).eta();
  // float EA = -999;
  
  // if(       abs(eta) < 1.0   ){ EA = 0.0157;
  // }else if( abs(eta) < 1.479 ){ EA = 0.0143;
  // }else if( abs(eta) < 2.0   ){ EA = 0.0115;
  // }else if( abs(eta) < 2.2   ){ EA = 0.0094;
  // }else if( abs(eta) < 2.3   ){ EA = 0.0095;
  // }else if( abs(eta) < 2.4   ){ EA = 0.0068;
  // }else if( abs(eta) > 2.4   ){ EA = 0.0053;
  // }
  
  // return EA;
}

float photon_NHEA03( int photonIdx )
{
  float eta = zmet.gamma_p4().at(photonIdx).eta();
  float EA = -999;
  
  if(       abs(eta) < 1.0   ){ EA = 0.0599;
  }else if( abs(eta) < 1.479 ){ EA = 0.0819;
  }else if( abs(eta) < 2.0   ){ EA = 0.0696;
  }else if( abs(eta) < 2.2   ){ EA = 0.0360;
  }else if( abs(eta) < 2.3   ){ EA = 0.0360;
  }else if( abs(eta) < 2.4   ){ EA = 0.0462;
  }else if( abs(eta) > 2.4   ){ EA = 0.0656;
  }
  
  return EA;
}

float photon_EMEA03( int photonIdx )
{
  float eta = zmet.gamma_p4().at(photonIdx).eta();
  float EA = -999;
  
  if(       abs(eta) < 1.0   ){ EA = 0.1271;
  }else if( abs(eta) < 1.479 ){ EA = 0.1101;
  }else if( abs(eta) < 2.0   ){ EA = 0.0756;
  }else if( abs(eta) < 2.2   ){ EA = 0.1175;
  }else if( abs(eta) < 2.3   ){ EA = 0.1498;
  }else if( abs(eta) < 2.4   ){ EA = 0.1857;
  }else if( abs(eta) > 2.4   ){ EA = 0.2183;
  }
  
  return EA;
}

float photonCHIso03EA( int photonIdx )
{
  float chiso = zmet.gamma_chHadIso().at(photonIdx);
  float ea    = photon_CHEA03(photonIdx);
  float CHIso = std::max(float(0.0), chiso - zmet.rho() * ea);
  return CHIso;
}

float photonNHIso03EA( int photonIdx )
{
  float nhiso = zmet.gamma_neuHadIso().at(photonIdx);
  float ea    = photon_NHEA03(photonIdx);
  float NHIso = std::max(float(0.0), nhiso - zmet.rho() * ea);
  return NHIso;
}

float photonEMIso03EA( int photonIdx )
{
  float emiso = zmet.gamma_phIso().at(photonIdx);
  float ea    = photon_EMEA03(photonIdx);
  float EMIso = std::max(float(0.0), emiso - zmet.rho() * ea);
  return EMIso;
}

bool isLoosePhoton( int photonIdx )
{
  
  float eta = -999;  
  try{
	eta = zmet.gamma_p4().at(photonIdx).eta();
  }
  catch( exception &e ){
	std::cout<<"Error! no photon with photonIdx: "<<photonIdx<<std::endl;
	return false;
  }

  float chiso = photonCHIso03EA(photonIdx);
  float nhiso = photonNHIso03EA(photonIdx);
  float emiso = photonEMIso03EA(photonIdx);

  float sieie  = zmet.gamma_sigmaIetaIeta().at(photonIdx);
  float hovere = zmet.gamma_hOverE()       .at(photonIdx);
  float pt     = zmet.gamma_p4()           .at(photonIdx).pt();
  
  if(       abs(eta) < 1.479 ){
	if( hovere > 0.05                         ) return false;
	if( sieie  > 0.0102                       ) return false;
	if( chiso  > 3.32                         ) return false;
	if( nhiso  > 1.92 + 0.014  * pt + 0.000019 * pow(pt, 2) ) return false;
	if( emiso  > 0.81 + 0.0053 * pt                         ) return false;
  }else if( abs(eta) > 1.479 ){
	if( hovere > 0.05                         ) return false;
	if( sieie  > 0.0274                       ) return false;
	if( chiso  > 1.97                         ) return false;
	if( nhiso  > 11.86 + 0.0139 * pt + 0.000025 * pow(pt, 2) ) return false;
	if( emiso  >  0.83 + 0.0034 * pt                         ) return false;
  }
  
  return true;
}

bool isMediumPhoton( int photonIdx )
{
  
  float eta = -999;  
  try{
	eta = zmet.gamma_p4().at(photonIdx).eta();
  }
  catch( exception &e ){
	std::cout<<"Error! no photon with photonIdx: "<<photonIdx<<std::endl;
	return false;
  }

  float chiso = photonCHIso03EA(photonIdx);
  float nhiso = photonNHIso03EA(photonIdx);
  float emiso = photonEMIso03EA(photonIdx);

  float sieie  = zmet.gamma_sigmaIetaIeta().at(photonIdx);
  float hovere = zmet.gamma_hOverE()       .at(photonIdx);
  float pt     = zmet.gamma_p4()           .at(photonIdx).pt();
  
  if(       abs(eta) < 1.479 ){
	if( hovere > 0.05                         ) return false;
	if( sieie  > 0.0102                       ) return false;
	if( chiso  > 1.37                         ) return false;
	if( nhiso  > 1.06 + 0.014  * pt + 0.000019 * pow(pt, 2) ) return false;
	if( emiso  > 0.28 + 0.0053 * pt                         ) return false;
  }else if( abs(eta) > 1.479 ){
	if( hovere > 0.05                         ) return false;
	if( sieie  > 0.0268                       ) return false;
	if( chiso  > 1.10                         ) return false;
	if( nhiso  > 2.69 + 0.0139 * pt + 0.000025 * pow(pt, 2) ) return false;
	if( emiso  > 0.39 + 0.0034 * pt                         ) return false;
  }
  
  return true;
}

bool isTightPhoton( int photonIdx )
{
  
  float eta = -999;  
  try{
	eta = zmet.gamma_p4().at(photonIdx).eta();
  }
  catch( exception &e ){
	std::cout<<"Error! no photon with photonIdx: "<<photonIdx<<std::endl;
	return false;
  }

  float chiso = photonCHIso03EA(photonIdx);
  float nhiso = photonNHIso03EA(photonIdx);
  float emiso = photonEMIso03EA(photonIdx);

  float sieie  = zmet.gamma_sigmaIetaIeta().at(photonIdx);
  float hovere = zmet.gamma_hOverE()       .at(photonIdx);
  float pt     = zmet.gamma_p4()           .at(photonIdx).pt();
  
  if(       abs(eta) < 1.479 ){
	if( hovere > 0.05                         ) return false;
	if( sieie  > 0.010                        ) return false;
	if( chiso  > 0.76                         ) return false;
	if( nhiso  > 0.97 + 0.014  * pt + 0.000019 * pow(pt, 2) ) return false;
	if( emiso  > 0.08 + 0.0053 * pt                         ) return false;
  }else if( abs(eta) > 1.479 ){
	if( hovere > 0.05                         ) return false;
	if( sieie  > 0.0268                       ) return false;
	if( chiso  > 0.76                         ) return false;
	if( nhiso  > 2.09 + 0.0139 * pt + 0.000025 * pow(pt, 2) ) return false;
	if( emiso  > 0.08 + 0.0034 * pt                         ) return false;
  }
  
  return true;
}
