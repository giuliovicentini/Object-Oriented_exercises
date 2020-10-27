#ifndef Utilities_h
#define Utilities_h

class Utilities {
  public:

	Utilities();
	~Utilities();	
	
	// compute energy from momentum x,y,z components and invariant mass
	static double energy (double PtotX, double PtotY, double PtotZ, double invMass);

  	// compute invariant mass from momentum x,y,z components and energy
	static double invMass (double PtotX, double PtotY, double PtotZ, double energy);

};

#endif 
