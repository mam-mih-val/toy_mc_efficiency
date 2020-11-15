//
// Created by mikhail on 11/14/20.
//

#ifndef TOYMC_SRC_EFFICIENCY_H_
#define TOYMC_SRC_EFFICIENCY_H_

#include "phi_generator.h"

class Efficiency : public PhiGenerator {
public:
  Efficiency() : PhiGenerator(){};
  ~Efficiency() override = default;
  bool IsMissed( double phi ){
    auto prob = GetProbability( phi );
    auto p = rnd_engine_(gen_);
    return p > prob;
  }
  void SetEfficiencyAmplitude(double efficiency_amplitude) {
    efficiency_amplitude_ = efficiency_amplitude;
  }

protected:
  double efficiency_amplitude_{0.7};
  double GetProbability(double num) override { return 0.7*( 1.0 + 2*v1*cos(num) + 2*v2*cos(num) ); }
};

#endif // TOYMC_SRC_EFFICIENCY_H_
