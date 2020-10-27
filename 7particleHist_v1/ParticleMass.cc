#include "ParticleMass.h"

#include "Event.h"
#include "MassMean.h"

#include "TH1F.h"
#include "TFile.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

float mass( const Event& ev );

ParticleMass::ParticleMass() {
}


ParticleMass::~ParticleMass() {
}


// function to be called at execution start
void ParticleMass::beginJob() {
  
  pCreate ( "K0", 0.495, 0.500 );
  pCreate ( "Lambda0", 1.115, 1.116);
  return;

}


// function to be called at execution end
void ParticleMass::endJob() {

  // save current working area
  TDirectory* currentDir = gDirectory;
  // open histogram file
  TFile* file = new TFile( "hist.root", "RECREATE" );

  // loop over elements
  int n = pList.size();
  int i;
  for ( i = 0; i < n; ++i ) {
    
    MassMean* MM = pList[i]->MMean;
    TH1F*     hMean = pList[i]->hMean;
    
    // compute results
    MM->compute();
    // print results
    cout << i << " " << MM->mMean() << " " << MM->mRMS() << endl;
    // print number of events
    cout << MM->nEvents() << endl;
    // save distribution
    hMean->Write();
  }
  
  // close file
  file->Close();
  delete file;
  // restore working area
  currentDir->cd();

  return;

}


// function to be called for each event
void ParticleMass::process( const Event& ev ) {  
  // loop over energy distributions and pass event to each of them
  unsigned int n = pList.size();
  unsigned int i;
  for ( i = 0; i < n; ++i ) {
	
	if( pList[i]->MMean->add( ev ) ) pList[i]->hMean->Fill( mass(ev) );
	
	
  }
  return;
}

void ParticleMass::pCreate( const string& name, float min, float max ) {
// create energy distribution for events with total energy in given range

  // create name for TH1F object
  const char* hName = name.c_str();

  // create TH1F and statistic objects and store their pointers
  Particle* p = new Particle;
  pList.push_back( p );
  p-> name = name;
  p->MMean = new MassMean( min, max );
  p->hMean = new TH1F( hName, hName, 100, min, max ); 
  
  return;

}

