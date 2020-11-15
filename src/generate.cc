//
// Created by mikhail on 11/14/20.
//

#include "efficiency.h"
#include "phi_generator.h"
#include "pt_generator.h"
#include <TFile.h>
#include <TH2F.h>
#include <TTree.h>

int main(){
  double v1_slope{0.1};
  double v2_slope{-0.04};
  double e1_slope{-0.02};
  double e2_slope{0.001};
  long int n_iterations{1'000'000};
  double phi = 0.0;
  double pT = 0.0;
  auto file = TFile::Open("toy-mc.root", "recreate");
  auto tree = new TTree("toy-mc", "");
  tree->Branch("phi", &phi );
  tree->Branch("pT", &pT );
  PhiGenerator phi_generator;
  phi_generator.SetV1Slope(v1_slope);
  phi_generator.SetV2Slope(v2_slope);
  Efficiency efficiency;
  efficiency.SetV1Slope(e1_slope);
  efficiency.SetV2Slope(e2_slope);
  PtGenerator pt_generator;

  for( int i=0; i< n_iterations; ++i ){
    pT = pt_generator.GetNumber();
    phi = phi_generator.GetNumber(pT);
    if( efficiency.IsMissed(phi, pT) )
      continue;
    tree->Fill();
  }
  std::cout << "INITIAL SETUP:\tv1_slope=" << v1_slope << "\t\tv2_slope=" << v2_slope << std::endl;
  std::cout << "EFFICIENCY:\t\te1_slope=" << e1_slope << "\t\te2_slope=" << e2_slope
            << std::endl;

  tree->Write();
  file->Close();
  return 0;
}
