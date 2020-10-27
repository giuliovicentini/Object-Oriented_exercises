#include<cmath>

#include "Event.h"


// compute energy from momentum x,y,z components and invariant mass
double energy (double PtotX, double PtotY, double PtotZ, double invMass) {

  double energy1 = sqrt(PtotX*PtotX + PtotY*PtotY + PtotZ*PtotZ + invMass*invMass);
  return energy1;
} 

// compute invariant mass from momentum x,y,z components and energy
double invMass (double PtotX, double PtotY, double PtotZ, double energy) {

  double Ptot;
  Ptot = sqrt(PtotX*PtotX + PtotY*PtotY + PtotZ*PtotZ);  
  double invMass1 = sqrt(energy*energy-Ptot*Ptot);
  return invMass1;
} 

const double massPion    = 0.1395706;   // GeV/c^2
const double massProton  = 0.938272;    // GeV/c^2
const double massK0      = 0.497611;    // GeV/c^2
const double massLambda0 = 1.115683;    // GeV/c^2

float mass (const Event& ev) {

  // retrieve particles in the event
  typedef const Particle* part_ptr;
  const part_ptr* particles = ev.pp;

  // variables to loop over particles

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
  for (int j=0; j<ev.n; j++) {
    // get particle pointer
    
    // update momentum sums
    PtotX = PtotX + particles[j] -> px;
    PtotY = PtotY + particles[j] -> py;
    PtotZ = PtotZ + particles[j] -> pz;
    // update energy sums, for K0 and Lambda0 hyptheses:
    Kenergy = Kenergy + energy(particles[j]->px, particles[j]->py, particles[j]->pz, massPion); 
    if (particles[j]->c == 1)
	Lenergy = Lenergy + energy(particles[j]->px, particles[j]->py, particles[j]->pz, massProton);
    else if (particles[j]->c == -1)
	Lenergy = Lenergy + energy(particles[j]->px, particles[j]->py, particles[j]->pz, massPion);
    else return -1;

    // pion mass for K0,
    // proton or pion mass for Lambda0,
    // for positive or negative particles respectively    
    
    // update positive/negative track counters
    if (particles[j] -> c == 1)
	positive++;

    else if (particles[j] -> c == -1)
	negative++;

    else return -1;
  }
  // check for exactly one positive and one negative track
  // otherwise return negative (unphysical) invariant mass
  if (positive != 1 && negative != 1)
	return -1;

  // invariant masses for different decay product mass hypotheses
  float Kmass, Lmass;
  Kmass = invMass (PtotX, PtotY, PtotZ, Kenergy); 
  Lmass = invMass (PtotX, PtotY, PtotZ, Lenergy);
  // compare invariant masses with known values and return the nearest one
  if ( fabs(Kmass-massK0) < fabs(Lmass-massLambda0) ) return Kmass; 
  
  else return Lmass; 

}

