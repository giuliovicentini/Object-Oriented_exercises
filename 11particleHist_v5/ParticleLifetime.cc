#include "ParticleLifetime.h"

#include "Event.h"
#include "AnalysisInfo.h"
#include "AnalysisFactory.h"
#include "MassMean.h"
#include "ProperTime.h"

#include "TH1F.h"
#include "TFile.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "util/include/ActiveObserver.h"

using namespace std;



// concrete factory to create an ElementReco analyzer
class ParticleLifetimeFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "plot" as name for this analyzer and factory
  ParticleLifetimeFactory(): AnalysisFactory::AbsFactory( "timeplot" ) {}
  // create an ElementReco when builder is run
  virtual AnalysisSteering* create( const AnalysisInfo* info ) {
    return new ParticleLifetime( info );
  }
};
// create a global ElementRecoFactory, so that it is created and registered 
// before main execution start:
// when the AnalysisFactory::create function is run,
// an ElementRecoFactory will be available with name "plot".
static ParticleLifetimeFactory er;

ParticleLifetime::ParticleLifetime( const AnalysisInfo* info ):
 AnalysisSteering( info ) {
}


ParticleLifetime::~ParticleLifetime() {
}


// function to be called at execution start
void ParticleLifetime::beginJob() {
  
  ifstream file( aInfo->value( "fitters" ).c_str() );		
  string name;
  float mMin;
  float mMax;
  float tMin;
  float tMax;
  float sMin;
  float sMax;
  float sStep;
  while ( file >> name >> mMin >> mMax >> tMin >> tMax >> sMin >> sMax >> sStep ) pCreate( name, mMin, mMax, tMin, tMax, sMin, sMax, sStep );
  
  return;

}


// function to be called at execution end
void ParticleLifetime::endJob() {

  // save current working area
  TDirectory* currentDir = gDirectory;
  // open histogram file
  TFile* file = new TFile( aInfo->value( "timeplot" ).c_str(), "RECREATE" );

  // loop over elements
  int n = pList.size();
  int i;
  for ( i = 0; i < n; ++i ) {
    
    LifetimeFit* LF = pList[i]->LFit;
    TH1F*     hMean = pList[i]->hMean;
    // compute results
    LF->compute();
    // print results
    cout << i << " " << LF->lifeTime() << " " << LF->lifeTimeError() << endl;
    // print number of events
    cout << LF->nEvents() << endl;
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
void ParticleLifetime::update( const Event& ev ) {  
  // loop over energy distributions and pass event to each of them
  unsigned int n = pList.size();
  unsigned int i;
  double DT = ProperTime::instance()->decayTime();
  for ( i = 0; i < n; ++i ) {
	if( pList[i]->LFit->add( ev ) ) pList[i]->hMean->Fill( DT );
  }
  return;
}

void ParticleLifetime::pCreate( const string& name, float min, float max, float timeMin, float timeMax, double minScan, double maxScan, double scanStep ) {
// create energy distribution for events with total energy in given range

  // create name for TH1F object
  const string& name1 = "time" + name;
  const char* hName = name1.c_str();

  // create TH1F and statistic objects and store their pointers
  Particle* p = new Particle;
  p-> name = name;
  p->LFit = new LifetimeFit( min, max, timeMin, timeMax, minScan, maxScan, scanStep );
  p->hMean = new TH1F( hName, hName, 100, timeMin, timeMax ); 
  pList.push_back( p );

  return;

}

