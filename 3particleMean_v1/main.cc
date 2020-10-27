#include<iostream>
#include<fstream>
#include<cmath>

#include "Event.h"


using namespace std;

//dichiaro funzioni
const Event* read (ifstream& file1);
void dump (const Event& ev);
void clear (const Event* ev);
bool add (const Event& ev, float minMass, float maxMass, 
	double& SumInvMass, double& SumSquares);

//main
int main ( int argc, char* argv[] ) {
  
  int accepted;
  double SumInvMass, SumSquares;
  double MEAN, RMS;

  const Event* ev;
  const char* file = argv[1];
  ifstream inputfile (file);
  while ( (ev = read (inputfile)) ) {
	if (!ev) return 0;	
	
	if(add(*ev, 0.490, 0.505, SumInvMass, SumSquares)) accepted++;
	MEAN = SumInvMass / accepted + 0.490;
	RMS = sqrt(SumSquares/accepted - MEAN*MEAN);
	cout << MEAN << " " << RMS << endl << endl;
	//dump (*ev);
	clear(ev);
	}

  return 0;
}











