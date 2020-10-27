#include <math.h>

#include "MassMean.h"
#include "Event.h"

using namespace std;

float mass( const Event& ev );


MassMean::MassMean( float min1, float max1):
 min(min1), max(max1) { // initializations
}


MassMean::~MassMean() {
}


// add data from a new event
void MassMean::add( const Event& ev ) {
  double M;
  M = mass(ev); 
  // check for mass being in range
  if( M>min && M<max) {
	double M1 = M - min;	
  // update number of events and sums
  	SumInvMass = SumInvMass + M1;
	SumSquares = SumSquares + M*M;
	accepted++;
	}

  else return;
 
}


// compute mean and rms
void MassMean::compute() {
  MEAN = (SumInvMass / accepted) + min;
  RMS = sqrt(SumSquares/accepted - MEAN*MEAN);
}


// return number of selected events
unsigned int MassMean::nEvents() const {
  return accepted;
}

// return mean and rms
double MassMean::mMean() const {
  return MEAN;
}
 
double MassMean::mRMS() const {
  return RMS;
}


