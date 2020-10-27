#include "Event.h"

float mass (const Event& ev);

bool add (const Event& ev, float minMass, float maxMass, 
	double& SumInvMass, double& SumSquares) {

  double M;
  M = mass(ev); 
  if( M>minMass && M<maxMass) {
	double M1 = M - minMass;	
	SumInvMass = SumInvMass + M1;
	SumSquares = SumSquares + M*M;
	return true;
	}
  else return false;

}





