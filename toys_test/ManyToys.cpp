#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooCBShape.h"
#include "RooCategory.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooPolyVar.h"
#include "RooProdPdf.h"
#include "RooRandom.h"
#include "RooRealVar.h"
#include "RooSimultaneous.h"
#include "RooTreeData.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TPad.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TTreeReader.h"

void GenerateToys(std::string const &outputDir) {

  // Number of toys to run
  Int_t n_toys = 10;

  // Number of events to generate
  Int_t n_events = 100000;

  int bu_low = 5045;
  int bu_high = 5805;
  int delta_low = 80;
  int delta_high = 240;

  int bu_nbins = (bu_high - bu_low) / 5;
  int delta_nbins = (delta_high - delta_low) / 2;

  RooRealVar bu_mass("Bu_M_DTF_D0", "m[D^{*0}#pi^{#pm}]", bu_low, bu_high,
                     "MeV/c^{2}");
  RooRealVar delta_mass("Delta_M", "m[D^{*0}] - m[D^{0}]", delta_low,
                        delta_high, "MeV/c^{2}");

  bu_mass.setBins(bu_nbins);
  delta_mass.setBins(delta_nbins);

  double a0_mean_init = 5101.86875;
  double a1_mean_init = 2.1375;
  double a2_mean_init = -0.0062;

  // run n_toys fits and store the values in the histograms
  for (int i = 0; i < n_toys; i++) {
    RooRandom::randomGenerator()->SetSeed(0);
    TRandom3 random(0);
    double randomTag = random.Rndm();

    TFile outputFile(
        (outputDir + "/ResultFile" + std::to_string(randomTag) + ".root")
            .c_str(),
        "recreate");

    // DEFINE PDFs
    RooRealVar delta_mean("delta_mean", "delta_mean", 145, 140, 150);
    RooRealVar delta_sigma("delta_sigma", "delta_sigma", 20, 0, 40);
    RooGaussian delta_gaus("delta_gaus", "", delta_mass, delta_mean,
                           delta_sigma);

    RooRealVar a0_mean("a0_mean", "a0_mean", a0_mean_init, 4879, 5579);
    RooRealVar a1_mean("a1_mean", "a1_mean", a1_mean_init, 0, 10);
    RooRealVar a2_mean("a2_mean", "a2_mean", a2_mean_init, -1, 1);
    RooPolyVar bu_mean("bu_mean", "", delta_mass,
                       RooArgSet(a0_mean, a1_mean, a2_mean));
    RooRealVar bu_sigma("bu_sigma", "", 100, 0, 150);
    RooGaussian bu_gaus("bu_gaus", "", bu_mass, bu_mean, bu_sigma);

    RooProdPdf pdf_tot("pdf_tot", "", delta_gaus,
                       RooFit::Conditional(bu_gaus, bu_mass));

    RooDataSet *toyDataSet =
        pdf_tot.generate(RooArgSet(bu_mass, delta_mass), n_events);
    toyDataSet->SetName(("toyDataSet_" + std::to_string(i)).c_str());
    auto toyDataHist = std::unique_ptr<RooDataHist>(
        toyDataSet->binnedClone(("toyDataHist_" + std::to_string(i)).c_str(),
                                ("toyDataHist" + std::to_string(i)).c_str()));
    auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

    delta_mean.setVal(142);

    RooFitResult *result = 0;
    result = pdf_tot.fitTo(*toyAbsData, RooFit::Save(true));

    outputFile.cd();
    result->SetName(("Result" + std::to_string(randomTag)).c_str());
    result->Print("v");
    result->Write();
    outputFile.Close();
  
    std::cout << "Result saved in file " << outputDir << "/ResultFile"
            << std::to_string(randomTag) << ".root\n";
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Enter output directory.\n";
    return 1;
  }
  std::string outputDir = argv[1];
  GenerateToys(outputDir);
  return 0;
}
