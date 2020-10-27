#include "Event.h"

void clear (const Event* ev) {

  for (int i=0; i<ev->n; i++) 
	delete ev->pp[i];
	
  delete[] ev->pp;
  delete ev;	
}
