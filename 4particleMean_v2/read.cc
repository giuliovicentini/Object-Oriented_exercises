#include<fstream>

#include "Event.h"

using namespace std;

const Event* read (ifstream& file1) {

  Event* ev1;
  int id1, n1;
  float x1, y1, z1;
  if (file1 >> id1 >> x1 >> y1 >> z1 >> n1)
	ev1 = new Event(id1, x1, y1, z1);
	
  else return 0;
  
  int charge[n1];
  float px[n1], py[n1], pz[n1];
  for (int i=0; i<n1; i++) {
	file1 >> charge[i] >> px[i] >> py[i] >> pz[i];
	ev1->add(px[i], py[i], pz[i], charge[i]);	
	}
  
  return ev1; 
}
