#ifndef ParticleLifetime_h
#define ParticleLifetime_h

#include <vector>
#include <string>

#include "AnalysisFramework/AnalysisSteering.h"
#include "AnalysisObjects/LifetimeFit.h"

#include "util/include/ActiveObserver.h"

using namespace std;

class Event;
class MassMean;
class TH1F;

class ParticleLifetime: public AnalysisSteering,
		    public ActiveObserver<Event> {
 public:

  ParticleLifetime( const AnalysisInfo* info );
  virtual ~ParticleLifetime();

  // function to be called at execution start
  virtual void beginJob();
  // function to be called at execution end
  virtual void   endJob();
  // function to be called for each event
  virtual void update( const Event& ev );

 private:

  // dummy copy constructor and assignment to prevent unadvertent copy
  ParticleLifetime           ( const ParticleLifetime& x );
  ParticleLifetime& operator=( const ParticleLifetime& x );

  // particle struct
  struct Particle {
	string name;
	LifetimeFit* LFit;
	TH1F* hMean;
  };

  // set of Bragg curves for different total energies
  vector<Particle*> pList;

  // function to crate a decay mode
  void pCreate( const string& name, float min, float max, float timeMin, float timeMax, double minScan, double maxScan, double scanStep);

};

#endif
