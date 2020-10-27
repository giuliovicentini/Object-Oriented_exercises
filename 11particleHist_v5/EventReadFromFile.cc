#include "EventReadFromFile.h"

#include "Event.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// read data from file "name"
EventReadFromFile::EventReadFromFile( const string& name ) {
  file1 = new ifstream( name.c_str() );
}


EventReadFromFile::~EventReadFromFile() {
  delete file1;
}


// get an event
const Event* EventReadFromFile::get() {
  return readFile();
}


// read an event
const Event* EventReadFromFile::readFile() {

  // event pointer and identifier
  Event* ev1;
  int id1, n1;
  float x1, y1, z1;

  // try to read input file
  // on success create new event
  if ((*file1) >> id1 >> x1 >> y1 >> z1 >> n1)
	ev1 = new Event(id1, x1, y1, z1);
  // on failure return null pointer
  else return 0;

  // particle
  int charge[n1];
  float px[n1], py[n1], pz[n1];

  // read and store the particles
  for (int i=0; i<n1; i++) {
	(*file1) >> charge[i] >> px[i] >> py[i] >> pz[i];
	ev1->add(px[i], py[i], pz[i], charge[i]);
  }

  return ev1;

}

