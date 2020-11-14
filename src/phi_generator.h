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
  void SetV1(double v_1) { v1 = v_1; }

protected:
  double v1{0.5};
  double GetProbability(double num) override;
};

#endif // TOYMC_SRC_PHI_GENERATOR_H_
