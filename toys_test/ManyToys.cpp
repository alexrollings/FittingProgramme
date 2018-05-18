#include "RooRandom.h"
#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooPolyVar.h"
#include "RooProdPdf.h"
#include "RooRealVar.h"
#include "RooTreeData.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TH2.h"
#include "TPad.h"
#include "TRandom3.h"
#include "TStyle.h"

void GenerateToys() {
  RooRandom::randomGenerator()->SetSeed(0);
  TRandom3 r3(0);

  // Number of toys to run
  Int_t n_toys = 1000;

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

  TFile treeFile(("/home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/"
                  "results/TreeFile_" +
                  std::to_string(randomTag) + ".root")
                     .c_str(),
                 "recreate");
  TTree tree("tree", "tree");

  // save variable value, error, and fit quality variables
  double a0Mean, a0MeanErr, a1Mean, a1MeanErr, a2Mean, a2MeanErr, EDM;
  int covQual, fitStatus;

  tree.Branch("a0Mean", &a0Mean, "a0Mean/D");
  tree.Branch("a0MeanErr", &a0MeanErr, "a0MeanErr/D");
  tree.Branch("a1Mean", &a1Mean, "a1Mean/D");
  tree.Branch("a1MeanErr", &a1MeanErr, "a1MeanErr/D");
  tree.Branch("a2Mean", &a2Mean, "a2Mean/D");
  tree.Branch("a2MeanErr", &a2MeanErr, "a2MeanErr/D");
  tree.Branch("EDM", &EDM, "EDM/D");
  tree.Branch("covQual", &covQual, "covQual/I");
  tree.Branch("fitStatus", &fitStatus, "fitStatus/I");

  // run n_toys fits and store the values in the histograms
  for (int i = 0; i < n_toys; i++) {
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
        pdf_tot.generate(RooArgSet(buMass, deltaMass, bachelor), n_events);
    toyDataSet->SetName(("toyDataSet_" + std::to_string(i)).c_str());
    auto toyDataHist = std::unique_ptr<RooDataHist>(
        toyDataSet->binnedClone(("toyDataHist_" + std::to_string(i)).c_str(),
                                ("toyDataHist" + std::to_string(i)).c_str()));
    auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

    delta_mean.setVal(142);

    RooFitResult *result = 0;
    result = pdf_tot.fitTo(*toyAbsData, RooFit::Save(true));

    RooAbsArg *a0MeanAbsArg = const_cast<RooAbsArg *>(
        result->floatParsFinal().find("a0_mean"));

    RooRealVar *a0MeanVar = dynamic_cast<RooRealVar *>(a0MeanAbsArg);
    if (a0MeanVar == nullptr) {
      std::stringstream output;
      output << "No value found in variable a0_mean";
      throw std::runtime_error(output.str());
    }

    RooAbsArg *a1MeanAbsArg = const_cast<RooAbsArg *>(
        result->floatParsFinal().find("a1_mean"));

    RooRealVar *a1MeanVar = dynamic_cast<RooRealVar *>(a1MeanAbsArg);
    if (a1MeanVar == nullptr) {
      std::stringstream output;
      output << "No value found in variable a1_mean";
      throw std::runtime_error(output.str());
    }

    RooAbsArg *a2MeanAbsArg = const_cast<RooAbsArg *>(
        result->floatParsFinal().find("a2_mean"));

    RooRealVar *a2MeanVar = dynamic_cast<RooRealVar *>(a2MeanAbsArg);
    if (a2MeanVar == nullptr) {
      std::stringstream output;
      output << "No value found in variable a2_mean";
      throw std::runtime_error(output.str());
    }

    a0Mean = a0MeanVar->getVal();
    a0MeanErr = a0MeanVar->getError();
    a1Mean = a1MeanVar->getVal();
    a1MeanErr = a1MeanVar->getError();
    a2Mean = a2MeanVar->getVal();
    a2MeanErr = a2MeanVar->getError();
    EDM = result->edm();
    fitStatus = result->status();
    covQual = result->covQual();
    result->Print("v");

    tree.Fill();
  }
}

int main() {
  GenerateToys();
  return 0;
}
