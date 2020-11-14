//
// Created by mikhail on 11/14/20.
//

#ifndef TOYMC_SRC_GENERATOR_H_
#define TOYMC_SRC_GENERATOR_H_

#include <array>
#include <iostream>
#include <random>
class Generator {
public:
  Generator() = default;
  explicit Generator(const std::array<double, 2> &ranges) : ranges_(ranges) {}
  virtual ~Generator() = default;
  void SetRanges(const std::array<double, 2> &ranges) {
    Generator::ranges_ = ranges;
  }
  double GetNumber();

protected:

  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen_{rd()}; //Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> rnd_engine_{0.0, 1.0};
  std::array<double, 2> ranges_;

  virtual double GetProbability(double num){ return double(0); }
};

#endif // TOYMC_SRC_GENERATOR_H_
