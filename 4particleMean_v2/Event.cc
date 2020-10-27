#include "Event.h"

Event::Event( int id, float x, float y, float z ):
 // initializations
 id1(id), n1(0),
 x1(x), y1(y), z1(z)
  {
  // allocate a buffer for particle pointers
  pp = new Particle*[maxN];
}


Event::~Event() {
  // delete all the particle pointers
  for (int i=0; i<n1; i++) 
	delete pp[i];
  // delete the pointers array
  delete[] pp;
}


void Event::add( float px, float py, float pz, int charge ) {

  // check for the number of particles, if maximum reached do nothing
  // and return
  if (n1>=maxN) return;

  // create the new particle and fill with data 
  pp[n1] = new Particle;
  pp[n1] -> charge = charge;
  pp[n1] -> px = px;
  pp[n1] -> py = py;
  pp[n1] -> pz = pz;
 
  // store the new particle pointer in the array and increase counter
  n1++;

  return;

}

// get event id.
int Event::eventNumber() const {
  return id1;
}

// get decay point coordinates
float Event::x() const{
  return x1;
}

float Event::y() const{
  return y1;
}

float Event::z() const{
  return z1;
}

// get number of particles
int Event::nParticle() const{
  return n1;
}

// get particle
Event::part_ptr Event::particle( unsigned int i ) const {
  return pp[i];
}

