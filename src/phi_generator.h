//
// Created by mikhail on 11/14/20.
//

#ifndef TOYMC_SRC_PHI_GENERATOR_H_
#define TOYMC_SRC_PHI_GENERATOR_H_

#include "generator.h"
class PhiGenerator : public Generator {
public:
  PhiGenerator() { ranges_= {-M_PI, M_PI}; };
  ~PhiGenerator() override = default;
  void SetV1Slope(double v_1) { v1_slope = v_1; }
  void SetV2Slope(double v_2) { v2_slope = v_2; }
  double GetNumber(double pT){
    double val;
    try {
      val = ranges_.at(0) + rnd_engine_(gen_) * (ranges_.at(1) - ranges_.at(0));
    } catch (std::exception&) {
      throw std::runtime_error( "Generator::GetNumber: ranges are not specified" );
    }
    auto val_prob = GetProbability(val, pT);
    auto p = rnd_engine_(gen_);
    if( p < val_prob )
      return val;
    else return GetNumber(pT);
  }

protected:
  double v1_slope{0.1};
  double v2_slope{-0.04};
  double GetProbability(double num) override { return Generator::GetProbability(num); };
  virtual double GetProbability(double phi, double pT);
};

#endif // TOYMC_SRC_PHI_GENERATOR_H_
