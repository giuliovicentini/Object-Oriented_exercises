#ifndef LifetimeFit_h
#define LifetimeFit_h

class Event;

class LifetimeFit {

 public:

  LifetimeFit( float min1, float max1, double minTime1, double maxTime1, double minScan1, double maxScan1, double scanStep1 ); // mass range
  ~LifetimeFit();

  bool add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms
  
  double lifeTime();		// return particle mean lifetime
  double lifeTimeError();	// return particle mean lifetime error

  unsigned int nEvents() const;                        // return number of accepted events
                                

 private:

  float min; // min mass
  float max; // max mass
  
 // min and max lifetime range
  double minTime;
  double maxTime;
  // min and max scan range
  double minScanRange;
  double maxScanRange;
  // scan step
  double scanStep;
  // container for all the dacy times
  std::vector<double> DecayTimes;				// perchè non si lamenta che non ho incluso il vector?
  // Particle mean lifetime and error
  double particleMeanLifetime;
  double PMLifetimeError;
};

#endif

