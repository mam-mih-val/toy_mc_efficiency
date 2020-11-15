//
// Created by mikhail on 11/14/20.
//

#include "phi_generator.h"

double PhiGenerator::GetProbability(double num) {
  double prob;
  prob = 1.0/2.0/M_PI * (1+ 2*v1*cos( num ) + 2*v2*cos(2*num) );
  return prob;
}
