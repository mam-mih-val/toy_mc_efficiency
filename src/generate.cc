//
// Created by mikhail on 11/14/20.
//

#include "efficiency.h"
#include "phi_generator.h"
#include "pt_generator.h"
#include <TFile.h>
#include <TProfile.h>
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

  auto v1_true = new TProfile( "v1_true", ";pT;v_{1}", 10, 0.0, 5.0 );
  auto v1_measured = new TProfile( "v1_measured", ";pT;v_{1}", 10, 0.0, 5.0 );

  for( int i=0; i< n_iterations; ++i ){
    pT = pt_generator.GetNumber();
    phi = phi_generator.GetNumber(pT);
    v1_true->Fill(pT, cos(phi));
    if( efficiency.IsMissed(phi, pT) )
      continue;
    v1_measured->Fill(pT, cos(phi));
    tree->Fill();
  }

  auto n_bins = v1_measured->GetXaxis()->GetNbins();
  auto v1_corrected = new TH1F( "v1_corrected", ";pT;v_{1}", 10, 0.0, 5.0 );
  for( int i=1; i<=n_bins; ++i ){
    auto mean = v1_measured->GetBinContent(i);
    auto rel_err = v1_measured->GetBinError(i) / mean;
    auto pt = v1_measured->GetXaxis()->GetBinCenter(i);
    auto e1_pt = e1_slope*pt;
    auto e2_pt = e2_slope*pt;
    auto v2_pt = v2_slope*pt;
    auto corrected_value = (mean - e1_pt - 2*e1_pt*v2_pt)/(1 + 2*e2_pt);
    auto new_err = corrected_value*rel_err;
    v1_corrected->SetBinContent(i, corrected_value);
    v1_corrected->SetBinError(i, new_err);
  }

  std::cout << "INITIAL SETUP:\tv1_slope=" << v1_slope << "\t\tv2_slope=" << v2_slope << std::endl;
  std::cout << "EFFICIENCY:\t\te1_slope=" << e1_slope << "\t\te2_slope=" << e2_slope
            << std::endl;

  tree->Write();
  v1_true->Write();
  v1_measured->Write();
  v1_corrected->Write();
  file->Close();
  return 0;
}
