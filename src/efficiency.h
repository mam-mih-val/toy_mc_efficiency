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
  bool IsMissed( double phi, double pT ){
    auto prob = GetProbability( phi, pT );
    auto p = rnd_engine_(gen_);
    return p > prob;
  }
  void SetEfficiencyAmplitude(double efficiency_amplitude) {
    efficiency_amplitude_ = efficiency_amplitude;
  }

protected:
  double efficiency_amplitude_{0.7};
  double GetProbability(double phi, double pT) override {
    double v1_pT = v1_slope*pT;
    double v2_pT = v2_slope*pT;
    double prob;
    prob = 0.7*( 1.0 + 2* v1_pT *cos(phi) + 2* v2_pT *cos(phi) );
    return prob;
  }
};

#endif // TOYMC_SRC_EFFICIENCY_H_
