#ifndef ParticleMass_h
#define ParticleMass_h

#include "AnalysisSteering.h"
#include <vector>
#include <string>

using namespace std;

class Event;
class MassMean;
class TH1F;

class ParticleMass: public AnalysisSteering {

 public:

  ParticleMass();
  virtual ~ParticleMass();

  // function to be called at execution start
  virtual void beginJob();
  // function to be called at execution end
  virtual void   endJob();
  // function to be called for each event
  virtual void process( const Event& ev );

 private:

  // dummy copy constructor and assignment to prevent unadvertent copy
  ParticleMass           ( const ParticleMass& x );
  ParticleMass& operator=( const ParticleMass& x );

  // particle struct
  struct Particle {
	string name;
	MassMean* MMean;
	TH1F* hMean;
  };

  // set of Bragg curves for different total energies
  vector<Particle*> pList;

  // function to crate a decay mode
  void pCreate( const string& name, float min, float max);

};

#endif
