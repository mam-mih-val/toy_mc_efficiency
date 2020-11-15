//
// Created by mikhail on 11/14/20.
//

#include "efficiency.h"
#include "phi_generator.h"
#include <TFile.h>
#include <TH2F.h>
#include <TTree.h>

int main(){
  double v1{0.4};
  double v2{-0.1};
  double e1{-0.1};
  double e2{0.05};
  long int n_iterations{1'000'000};
  double phi = 0.0;
  auto file = TFile::Open("toy-mc.root", "recreate");
  auto tree = new TTree("toy-mc", "");
  tree->Branch("phi", &phi );
  PhiGenerator phi_generator;
  phi_generator.SetV1(v1);
  phi_generator.SetV2(v2);
  Efficiency efficiency;
  efficiency.SetV1(e1);
  efficiency.SetV2(e2);
  double sum_cos{0.0};
  double sum_cos2{0.0};
  double genned_part=0.0;
  for( int i=0; i< n_iterations; ++i ){
    phi = phi_generator.GetNumber();
    if( efficiency.IsMissed(phi) )
      continue;
    tree->Fill();
    genned_part+=1.0;
    sum_cos += cos(phi);
    sum_cos2+= cos(phi)*cos(phi);
  }
  auto mean = sum_cos / genned_part;
  auto variance = sqrt(sum_cos2/genned_part - mean*mean);
  auto standard_error = variance / sqrt(genned_part);
  auto eff_corr = (mean-e1-2*v2*e1)/(1+2*e2);

  std::cout << "INITIAL SETUP:\tv1=" << v1 << "\t\t\tv2=" << v2 << std::endl;
  std::cout << "EFFICIENCY:\t\te1=" << e1 << "\t\te2=" << e2 << std::endl;
  std::cout << "MEASURED:\t\tv1=" << mean << "\t\terr=" << standard_error << std::endl;
  std::cout << "CORRECTED:\t\tv1=" << eff_corr << std::endl;


  tree->Write();
  file->Close();
  return 0;
}
