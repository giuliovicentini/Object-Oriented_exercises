#include "EventDump.h"
#include "Event.h"
#include <iostream>
#include <stdio.h>

using namespace std;

EventDump::EventDump() {
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
void EventDump::process( const Event& ev ) {

  cout << ev.eventNumber() << endl;
  cout << ev.x() <<  ' ' << ev.y() << ' ' << ev.z() << endl;
  cout << ev.nParticle() << endl;

  for (int i=0; i<ev.nParticle(); i++) 
	cout << ev.particle(i)-> charge << ' ' << ev.particle(i)-> px << ' ' << ev.particle(i)-> py << ' ' << ev.particle(i)-> pz << endl;

  return;

}

