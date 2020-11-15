//
// Created by mikhail on 11/14/20.
//

#include "phi_generator.h"

double PhiGenerator::GetProbability(double phi, double pT){
  double v1_pT = v1_slope*pT;
  double v2_pT = v2_slope*pT;
  double prob;
  prob = 1.0/2.0/M_PI * (1+ 2*v1_pT*cos( phi ) + 2*v2_pT*cos(2*phi) );
  return prob;
}
