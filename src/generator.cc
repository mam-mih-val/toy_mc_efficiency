//
// Created by mikhail on 11/14/20.
//

#include "generator.h"

double Generator::GetNumber(){
  double val;
  try {
    val = ranges_.at(0) + rnd_engine_(gen_) * (ranges_.at(1) - ranges_.at(0));
  } catch (std::exception&) {
    throw std::runtime_error( "Generator::GetNumber: ranges are not specified" );
  }
  auto val_prob = GetProbability(val);
  auto p = rnd_engine_(gen_);
  if( p < val_prob )
    return val;
  else return GetNumber();
}