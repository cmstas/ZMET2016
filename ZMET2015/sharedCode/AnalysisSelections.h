#ifndef ANALYSISSELECTIONS_H
#define ANALYSISSELECTIONS_H

#include "AnalysisSelections.h"

bool passBaselineSelections();
bool isLoosePhoton( int photonIdx );
bool isMediumPhoton( int photonIdx );
bool isTightPhoton( int photonIdx );
bool passMETFilters();
bool passSignalRegionSelection( std::string selection );
bool eventHas2GoodLeps();
bool eventHas3Jets();
bool eventHasGoodPhoton();
bool passPhotonTrigger();
bool passPhotonTrigger22();
bool passPhotonTrigger30();
bool passPhotonTrigger36();
bool passPhotonTrigger50();
bool passPhotonTrigger75();
bool passPhotonTrigger90();
bool passPhotonTrigger120();
bool passPhotonTrigger165();
int  getPrescale();
int getPrescaleNoBins();
int getPrescaleNoBins_nol1ps();
bool highHT_zjinc( std::string samplename );


//////////////////////
// Photon Isolation //
//////////////////////

// from https://indico.cern.ch/event/369239/contribution/2/attachments/1134693/1623149/spring15_pcb.pdf
float photon_CHEA03( int photonIdx );
float photon_NHEA03( int photonIdx );
float photon_EMEA03( int photonIdx );
float photonCHIso03EA( int photonIdx );
float photonNHIso03EA( int photonIdx );
float photonEMIso03EA( int photonIdx );
#endif
