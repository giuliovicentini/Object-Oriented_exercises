#include<iostream>

#include "Event.h"

using namespace std;

void dump (const Event& ev1) {

  cout << ev1.id << endl;
  cout << ev1.x <<  ' ' << ev1.y << ' ' << ev1.z << endl;
  cout << ev1.n << endl;
  

  for (int i=0; i<ev1.n; i++) 
	cout << ev1.pp[i]-> c << ' ' << ev1.pp[i]-> px << ' ' << ev1.pp[i]-> py << ' ' << ev1.pp[i]-> pz << endl;

  cout << endl;
  }
