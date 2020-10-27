#include <fstream>
#include <iostream>

//... include header files ...
#include "Event.h"
#include "MassMean.h" 

using namespace std;

//... declare functions to read and dump events ...
const Event* read (ifstream& file1);
void dump (const Event& ev1);

int main( int argc, char* argv[] ) {

  // open input file
  const char* file = argv[1];
  ifstream inputfile (file);

  // create MassMean objects
  MassMean K0(0.490, 0.505);
  MassMean Lambda0(1.114, 1.118);

  // loop over events
  const Event* ev;
  while ( (ev = read (inputfile)) ) {		// doppia () perchè ritorna un bool
    dump(*ev);
    K0.add(*ev);
    Lambda0.add(*ev);
    delete ev;
  }

  // compute results
  K0.compute();
  Lambda0.compute();

  // print number of selected events and results for both particles
  cout << K0.nEvents() << " " << K0.mMean() << " " << K0.mRMS() << endl;
  cout << Lambda0.nEvents() << " " << Lambda0.mMean() << " " << Lambda0.mRMS() << endl;

  return 0;

}

