#include <iostream>
#include <math.h>
#include <stdio.h>

#include "AnalysisPlugins/EventDump.h"
#include "AnalysisFramework/Event.h"
#include "AnalysisFramework/AnalysisInfo.h"
#include "AnalysisFramework/AnalysisFactory.h"

#include "util/include/ActiveObserver.h"

using namespace std;

// concrete factory to create an EventDump analyzer
class EventDumpFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "dump" as name for this analyzer and factory
  EventDumpFactory(): AnalysisFactory::AbsFactory( "dump" ) {}
  // create an EventDump when builder is run
  virtual AnalysisSteering* create( const AnalysisInfo* info ) {
    return new EventDump( info );
  }
};
// create a global EventDumpFactory, so that it is created and registered 
// before main execution start:
// when the AnalysisFactory::create function is run,
// an EventDumpFactory will be available with name "dump".
static EventDumpFactory ed;

EventDump::EventDump( const AnalysisInfo* info ):
 AnalysisSteering( info ) {
}


EventDump::~EventDump() {
}


// function to be called at execution start
void EventDump::beginJob() {
  return;
}


// function to be called at execution end
void EventDump::endJob() {
  return;
}


// function to be called for each event
void EventDump::update( const Event& ev ) {
  
  cout << ev.eventNumber() << endl;
  cout << ev.x() <<  ' ' << ev.y() << ' ' << ev.z() << endl;
  cout << ev.nParticle() << endl;

  for ( int i = 0; i < ev.nParticle(); i++ ) 
    cout << ev.particle(i)->charge << ' ' << ev.particle(i)->px << ' ' << ev.particle(i)->py << ' ' << ev.particle(i)->pz << endl;

  return;
}

