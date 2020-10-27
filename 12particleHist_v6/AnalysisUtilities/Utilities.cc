#include "AnalysisUtilities/Utilities.h"
#include <math.h>

Utilities::Utilities() {
}
Utilities::~Utilities() {
}

// compute energy from momentum x,y,z components and invariant mass
double Utilities::energy ( double PtotX, double PtotY, double PtotZ, double invMass ) {
  
  double energy1 = sqrt( PtotX * PtotX + PtotY * PtotY + PtotZ * PtotZ + invMass * invMass );
  return energy1;
}	 

// compute invariant mass from momentum x,y,z components and energy
double Utilities::invMass ( double PtotX, double PtotY, double PtotZ, double energy ) {
  
  double Ptot;
  Ptot = sqrt( PtotX * PtotX + PtotY * PtotY + PtotZ * PtotZ );  
  double invMass1 = sqrt( energy * energy - Ptot * Ptot );
  return invMass1;
} 
