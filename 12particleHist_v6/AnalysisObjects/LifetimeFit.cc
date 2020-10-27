#include<iostream>
#include<math.h>
#include<vector>

#include "AnalysisObjects/LifetimeFit.h"
#include "AnalysisFramework/Event.h"
#include "AnalysisObjects/ParticleReco.h"
#include "AnalysisObjects/ProperTime.h"
#include "AnalysisUtilities/QuadraticFitter.h"

using namespace std;


LifetimeFit::LifetimeFit( float min1, float max1, 
			  double minTime1, double maxTime1,
			  double minScan1, double maxScan1, double scanStep1):
 min(min1),
 max(max1),
 minTime(minTime1),
 maxTime(maxTime1),
 minScanRange(minScan1),
 maxScanRange(maxScan1),
 scanStep(scanStep1) { // initializations
}


LifetimeFit::~LifetimeFit() {
}


// add data from a new event
bool LifetimeFit::add( const Event& ev ) {
  double M;
  M = ParticleReco::instance()->invariantMass(); 
  // check for mass being in range
  if( M > min && M < max ) {
    DecayTimes.push_back( ProperTime::instance()->decayTime() );
    //accepted++;
    return true;
  }

  else return false;
}


unsigned int LifetimeFit::nEvents() const {
  return DecayTimes.size();
}

double LifetimeFit::lifeTime() {
  return particleMeanLifetime;
}

double LifetimeFit::lifeTimeError() {
  return PMLifetimeError;
}

void LifetimeFit::compute() {
  QuadraticFitter qf;
  
  for ( double t = minScanRange; t < maxScanRange; t+=scanStep ) {
    double L=0;
    for ( unsigned int i = 0; i < DecayTimes.size(); i++ ) {	
      L = L + ( DecayTimes[i] / t ) + log( t ) + log( exp( - minTime / t ) - exp( - maxTime / t ) );
    }
    qf.add( t, L );
  }
  particleMeanLifetime = - qf.b() / ( 2 * qf.c() );
  PMLifetimeError = 1 / sqrt( 2 * qf.c() );
  
}



