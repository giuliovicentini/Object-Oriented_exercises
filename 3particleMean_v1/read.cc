#include<fstream>

#include "Particle.h"
#include "Event.h"

using namespace std;

const Event* read (ifstream& file1) {

  Event* ev1;
  int id1, n1;
  float x1, y1, z1;
  if (file1 >> id1 >> x1 >> y1 >> z1 >> n1)
	ev1 = new Event;
	
  else return 0;

  ev1 -> id = id1;
  ev1 -> x = x1;
  ev1 -> y = y1;
  ev1 -> z = z1;
  ev1 -> n = n1;

  int c[n1];
  float px[n1], py[n1], pz[n1];
  ev1 -> pp = new Particle*[n1];
  for (int i=0; i<n1; i++) {
	ev1 -> pp[i] = new Particle;
	file1 >> c[i] >> px[i] >> py[i] >> pz[i];	
	ev1 -> pp[i] -> c = c[i];
	ev1 -> pp[i] -> px = px[i];
	ev1 -> pp[i] -> py = py[i];	
	ev1 -> pp[i] -> pz = pz[i];
	}

  return ev1; 
}
