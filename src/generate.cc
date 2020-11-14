//
// Created by mikhail on 11/14/20.
//

#include "efficiency.h"
#include "phi_generator.h"
#include <TFile.h>
#include <TH2F.h>
#include <TTree.h>

int main(){
  double v1{0.1};
  double e1{-0.05};
  long int n_iterations{1'000'000};
  double phi = 0.0;
  auto file = TFile::Open("toy-mc.root", "recreate");
  auto tree = new TTree("toy-mc", "");
  tree->Branch("phi", &phi );
  PhiGenerator phi_generator;
  phi_generator.SetV1(v1);
  Efficiency efficiency;
  efficiency.SetV1(e1);
  double mean_cos{0.0};
  double genned_part=0.0;
  for( int i=0; i< n_iterations; ++i ){
    phi = phi_generator.GetNumber();
    if( efficiency.IsMissed(phi) )
      continue;
    tree->Fill();
    genned_part+=1;
    mean_cos+=cos(phi);
  }
  mean_cos/= genned_part;
  std::cout << "v1=" << mean_cos << " genned particles: " << genned_part << std::endl;
  tree->Write();
  file->Close();
  return 0;
}
