#include<iostream>

#include "Event.h"

using namespace std;

void dump (const Event& ev1) {

  cout << ev1.eventNumber() << endl;
  cout << ev1.x() <<  ' ' << ev1.y() << ' ' << ev1.z() << endl;
  cout << ev1.nParticle() << endl;

  for (int i=0; i<ev1.nParticle(); i++) 
	cout << ev1.particle(i)->charge << ' ' << ev1.particle(i)-> px << ' ' << ev1.particle(i)-> py << ' ' << ev1.particle(i)-> pz << endl;
  
  }
