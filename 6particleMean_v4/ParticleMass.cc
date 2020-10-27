#include "ParticleMass.h"

#include "Event.h"
#include "MassMean.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

ParticleMass::ParticleMass() {
}


ParticleMass::~ParticleMass() {
}


// function to be called at execution start
void ParticleMass::beginJob() {

  // create energy distributions for different total energy ranges
  pList.reserve( 10 ); //2?
  pList.push_back( new MassMean( 0.490, 0.505 ) );
  pList.push_back( new MassMean( 1.114, 1.118 ) );
  return;

}


// function to be called at execution end
void ParticleMass::endJob() {

  // loop over elements
  int n = pList.size();
  int i;
  for ( i = 0; i < n; ++i ) {
    MassMean* MM = pList[i];
    // compute results
    MM->compute();
    // print results
    cout << i << " " << MM->mMean() << " " << MM->mRMS() << endl;
    // print number of events
    cout << MM->nEvents() << endl;
  }

  return;
}


// function to be called for each event
void ParticleMass::process( const Event& ev ) {  
  // loop over energy distributions and pass event to each of them
  unsigned int n = pList.size();
  unsigned int i;
  for ( i = 0; i < n; ++i ) pList[i]->add( ev );
  return;
}

