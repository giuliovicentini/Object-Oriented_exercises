#include "AnalysisPlugins/ParticleMass.h"

#include "AnalysisFramework/Event.h"
#include "AnalysisFramework/AnalysisInfo.h"
#include "AnalysisFramework/AnalysisFactory.h"
#include "AnalysisObjects/MassMean.h"
#include "AnalysisObjects/ParticleReco.h"

#include "TH1F.h"
#include "TFile.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "util/include/ActiveObserver.h"

using namespace std;


// concrete factory to create an ElementReco analyzer
class ParticleMassFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "plot" as name for this analyzer and factory
  ParticleMassFactory(): AnalysisFactory::AbsFactory( "massplot" ) {}
  // create an ElementReco when builder is run
  virtual AnalysisSteering* create( const AnalysisInfo* info ) {
    return new ParticleMass( info );
  }
};
// create a global ElementRecoFactory, so that it is created and registered 
// before main execution start:
// when the AnalysisFactory::create function is run,
// an ElementRecoFactory will be available with name "plot".
static ParticleMassFactory er;

ParticleMass::ParticleMass( const AnalysisInfo* info ):
 AnalysisSteering( info ) {
}


ParticleMass::~ParticleMass() {
}


// function to be called at execution start
void ParticleMass::beginJob() {
  
  ifstream file( aInfo->value( "ranges" ).c_str() );		
  string name;
  float eMin;
  float eMax;
  while ( file >> name >> eMin >> eMax ) pCreate( name, eMin, eMax );
  
  return;
}


// function to be called at execution end
void ParticleMass::endJob() {

  // save current working area
  TDirectory* currentDir = gDirectory;
  // open histogram file
  TFile* file = new TFile( aInfo->value( "massplot" ).c_str(), "RECREATE" );

  // loop over elements
  int n = pList.size();
  int i;
  for ( i = 0; i < n; ++i ) {
    MassMean* MM = pList[i]->MMean;
    TH1F*     hMean = pList[i]->hMean;
    // compute results
    MM->compute();
    
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
void ParticleMass::update( const Event& ev ) {  
  // loop over energy distributions and pass event to each of them
  unsigned int n = pList.size();
  unsigned int i;
  double M = ParticleReco::instance()->invariantMass();
  for ( i = 0; i < n; ++i ) {
    if( pList[i]->MMean->add( ev ) ) pList[i]->hMean->Fill( M ); 
  }
  
  return;
}

void ParticleMass::pCreate( const string& name, float min, float max ) {
  // create energy distribution for events with total energy in given range

  // create name for TH1F object
  const string& name1 = "mass" + name;
  const char* hName = name1.c_str();

  // create TH1F and statistic objects and store their pointers
  Particle* p = new Particle;
  p-> name = name;
  p->MMean = new MassMean( min, max );
  p->hMean = new TH1F( hName, hName, 100, min, max ); 
  pList.push_back( p );

  return;
}

