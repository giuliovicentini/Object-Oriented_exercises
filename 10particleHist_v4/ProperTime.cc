#include "ProperTime.h"
#include "Event.h"
#include "Utilities.h"
#include "Constants.h"
#include <iostream>
#include <math.h>
#include "ParticleReco.h"

using namespace std;


ProperTime::ProperTime() {
}


ProperTime::~ProperTime() {
}


// recompute tag informations for new event
void ProperTime::update( const Event& ev ) {

  //call object Constants
  Constants C;
  float c = C.lightVelocity;

  //declare invariant mass and energy
  float m = ParticleReco::instance()->invariantMass();
  float e = ParticleReco::instance()->totalEnergy(); 
  
  //compute momentum
  float p = sqrt(e*e-m*m);
  
  //call decay point coordinates
  float x = ev.x();
  float y = ev.y();
  float z = ev.z();  

  //compute distance from the origin
  float d = sqrt(x*x+y*y+z*z);

  //compute decay time
  time = d*m/(p*c);

  return;

}

float ProperTime::decayTime() {
  // check for new event and return result
  check();
  return time; 
}

