#include "AnalysisObjects/ParticleReco.h"
#include "AnalysisFramework/Event.h"
#include "AnalysisUtilities/Utilities.h"
#include "AnalysisUtilities/Constants.h"

#include <iostream>
#include <math.h>

using namespace std;


ParticleReco::ParticleReco() {
}


ParticleReco::~ParticleReco() {
}

// access 
ParticleReco* ParticleReco::instance() {
  static ParticleReco pr;
  return &pr;
}

// recompute tag informations for new event
void ParticleReco::update( const Event& ev ) {

  // set default quantities
  type   = unknown;
  energy = -1.0;
  mass   = -1.0;

  // code to compute total energy and invariant mass for the two
  // mass hypotheses for the decay products
  //create Utilities object
  Utilities U;	
  //crate Constants object
  Constants C;
  // positive / negative track counters
  int positive = 0;
  int negative = 0;

  // variables for momentum sums
  float PtotX = 0;
  float PtotY = 0;
  float PtotZ = 0;  

  // variables for energy sums, for K0 and Lambda0
  float Kenergy = 0;
  float Lenergy = 0;

  // loop over particles - momenta
  for (int j = 0; j < ev.nParticle(); j++ ) {
    // update momentum sums
    PtotX += ev.particle(j) -> px;
    PtotY += ev.particle(j) -> py;
    PtotZ += ev.particle(j) -> pz;
    // update energy sums, for K0 and Lambda0 hyptheses:
    Kenergy += U.energy(ev.particle(j)->px, ev.particle(j)->py, ev.particle(j)->pz, C.massPion); 
    if (ev.particle(j)->charge == 1)
	Lenergy += U.energy(ev.particle(j)->px, ev.particle(j)->py, ev.particle(j)->pz, C.massProton);
    else if (ev.particle(j)->charge == -1)
	Lenergy += U.energy(ev.particle(j)->px, ev.particle(j)->py, ev.particle(j)->pz, C.massPion);
    // update positive/negative track counters
    if (ev.particle(j) -> charge == 1)
	positive++;
    else if (ev.particle(j) -> charge == -1)
	negative++;
  }
    // invariant masses for different decay product mass hypotheses
  float Kmass, Lmass;
  Kmass = U.invMass (PtotX, PtotY, PtotZ, Kenergy); 
  Lmass = U.invMass (PtotX, PtotY, PtotZ, Lenergy);
  // compare invariant masses with known values and set final values
  // ( type, energy and mass )
  if (fabs(Kmass-C.massK0) < fabs(Lmass-C.massLambda0)) {
    type = K0;
    mass = Kmass;
    energy = Kenergy;
  }
  else {
    type = Lambda0;
    mass = Lmass;
    energy = Lenergy;
  }
  
  return;  
}

float ParticleReco::totalEnergy() {
  // check for new event and return result
  check();
  return energy;
}


float ParticleReco::invariantMass() {
  // check for new event and return result
  check();
  return mass;
}


ParticleReco::ParticleType ParticleReco::particleType() {
  // check for new event and return result
  check();
  return type;
}

