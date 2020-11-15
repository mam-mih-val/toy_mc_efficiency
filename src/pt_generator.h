//
// Created by mikhail on 11/15/20.
//

#ifndef TOYMC_SRC_PT_GENERATOR_H_
#define TOYMC_SRC_PT_GENERATOR_H_

#include "generator.h"
class PtGenerator : public Generator {
public:
  PtGenerator() { ranges_ = {0.0, 5.0}; };
  ~PtGenerator() override = default;
protected:
  double GetProbability(double num) override {
    return exp( -num );
  }
};

#endif // TOYMC_SRC_PT_GENERATOR_H_
