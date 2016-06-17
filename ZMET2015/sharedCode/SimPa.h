#ifndef SIMPA_H
#define SIMPA_H

#include "TRandom3.h"
#include "TLorentzVector.h"
#include "ZMET.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

////////////Small wrapper for Particle//////////////////
class Particle {

public:

  Particle(Float_t pt, Float_t eta, Float_t phi, Float_t mass, Float_t width_);
  ~Particle();

  TLorentzVector p;
  // LorentzVector p;
  Float_t width;

};
////////////Small wrapper for Particle//////////////////

////////////Functions doing the decay//////////////////
Float_t fix(Float_t a);
Float_t thetaToEta(Float_t);
void ProduceDecay(TRandom , Particle *, Particle *, Particle *, Float_t, Float_t);

#endif
