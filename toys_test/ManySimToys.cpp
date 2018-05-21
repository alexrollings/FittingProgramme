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
#include "TFile.h"
#include "TH2.h"
#include "TPad.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TChain.h"
#include "TTreeReader.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

void GenerateToys(std::string const &outputDir) {
  RooRandom::randomGenerator()->SetSeed(0);
  TRandom3 random(0);
  double randomTag = random.Rndm();

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

  RooRealVar buMass("Bu_M_DTF_D0", "m[D^{*0}#pi^{#pm}]", bu_low, bu_high,
                    "MeV/c^{2}");
  RooRealVar deltaMass("Delta_M", "m[D^{*0}] - m[D^{0}]", delta_low, delta_high,
                       "MeV/c^{2}");

  buMass.setBins(bu_nbins);
  deltaMass.setBins(delta_nbins);

  // DEFINE INDEX CATEGORIES
  RooCategory bachelor("bachelor", "bachelor");
  bachelor.defineType("pi");
  bachelor.defineType("k");

  double a0MeanBuSignal_init = 5101.86875;
  double a1MeanBuSignal_init = 2.1375;
  double a2MeanBuSignal_init = -0.0062;

  TFile treeFile(
      (outputDir + "/TreeFile_" + std::to_string(randomTag) + ".root").c_str(),
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
    // DEFINE pi PDFs
    // SIGNAL
    RooRealVar meanDeltaSignal("meanDeltaSignal", "Mean of Signal m[Delta]",
                               145, 140, 150);
    RooRealVar a0MeanBuSignal("a0MeanBuSignal",
                              "a0 of mean of Signal m[Bu] PDF",
                              a0MeanBuSignal_init, 4879, 5579);
    RooRealVar a1MeanBuSignal("a1MeanBuSignal",
                              "a1 of mean of Signal m[Bu] PDF",
                              a1MeanBuSignal_init, 0, 10);
    RooRealVar a2MeanBuSignal("a2MeanBuSignal",
                              "a2 of mean of Signal m[Bu] PDF",
                              a2MeanBuSignal_init, -0.01, -0.00001);
    RooPolyVar meanBuSignal(
        "meanBuSignal", "Mean of Signal m[Bu]", deltaMass,
        RooArgList(a0MeanBuSignal, a1MeanBuSignal, a2MeanBuSignal));
    RooRealVar sigmaDeltaSignalPi("sigmaDeltaSignalPi",
                                  "Sigma of pi delta Gaussian", 20, 0, 40);
    RooGaussian pdfDeltaSignalPi("pdfDeltaSignalPi", "Signal pi Delta PDF",
                                 deltaMass, meanDeltaSignal,
                                 sigmaDeltaSignalPi);
    RooRealVar sigmaBuSignalPi("sigmaBuSignalPi", "Sigma of pi Bu Gaussian",
                               100, 0, 150);
    RooGaussian pdfBuSignalPi("pdfBuSignalPi", "Signal pi Bu PDF", buMass,
                              meanBuSignal, sigmaBuSignalPi);
    RooProdPdf pdfSignalPi("pdfSignalPi", "Signal pi 2D PDF", pdfDeltaSignalPi,
                           RooFit::Conditional(pdfBuSignalPi, buMass));
    // BACKGROUND
    RooRealVar lambdaDeltaCombPi("lambdaDeltaCombPi", "lambda of delta comb pi",
                                 -0.001, -1, 1);
    RooRealVar a0LambdaBuCombPi("a0LambdaBuCombPi",
                                "a0 of lambda of bu comb pi", -0.001, -1, 1);
    RooPolyVar lambdaBuCombPi("lambdaBuCombPi", "lambda of bu comb pi",
                              deltaMass, RooArgList(a0LambdaBuCombPi));
    RooExponential pdfDeltaCombPi("pdfDeltaCombPi", "pdf of delta pi comb",
                                  deltaMass, lambdaDeltaCombPi);
    RooExponential pdfBuCombPi("pdfBuCombPi", "pdf of bu pi comb", buMass,
                               lambdaBuCombPi);
    RooProdPdf pdfCombPi("pdfCombPi", "pdf of pi comb", pdfDeltaCombPi,
                         RooFit::Conditional(pdfBuSignalPi, buMass));
    // ROOADDPDF
    RooRealVar yieldSignalPi("yieldSignalPi", "yield of pi signal", 100000, 0,
                             500000);
    RooRealVar yieldBackgroundPi("yieldBackgroundPi", "yield of pi background",
                                 10000, 0, 50000);

    RooArgSet yieldsPi;
    yieldsPi.add(yieldSignalPi);
    yieldsPi.add(yieldBackgroundPi);
    RooArgSet functionsPi;
    functionsPi.add(pdfSignalPi);
    functionsPi.add(pdfCombPi);

    RooAddPdf pdfPi("pdfPi", "pdf pi", functionsPi, yieldsPi);

    // DEFINE K SIGNAL PDFs
    // SIGNAL
    RooRealVar sigmaRatio("sigmaRatio", "sigmaRatio", 0.95, 0, 1);
    RooFormulaVar sigmaDeltaSignalK("sigmaDeltaSignalK",
                                    "Sigma of k delta Gaussian", "@0*@1",
                                    RooArgList(sigmaDeltaSignalPi, sigmaRatio));
    RooGaussian pdfDeltaSignalK("pdfDeltaSignalK", "Signal k Delta PDF",
                                deltaMass, meanDeltaSignal, sigmaDeltaSignalK);
    RooFormulaVar sigmaBuSignalK("sigmaBuSignalK", "Sigma of k Bu Gaussian",
                                 "@0*@1",
                                 RooArgList(sigmaBuSignalPi, sigmaRatio));
    RooGaussian pdfBuSignalK("pdfBuSignalK", "Signal k Bu PDF", buMass,
                             meanBuSignal, sigmaBuSignalK);
    RooProdPdf pdfSignalK("pdfSignalK", "Signal k 2D PDF", pdfDeltaSignalK,
                          RooFit::Conditional(pdfBuSignalK, buMass));
    // BACKGROUND
    RooRealVar lambdaDeltaCombK("lambdaDeltaCombK", "lambda of delta comb k",
                                -0.001, -1, 1);
    RooRealVar a0LambdaBuCombK("a0LambdaBuCombK", "a0 of lambda of bu comb k",
                               -0.001, -1, 1);
    RooPolyVar lambdaBuCombK("lambdaBuCombK", "lambda of bu comb k", deltaMass,
                             RooArgList(a0LambdaBuCombK));
    RooExponential pdfDeltaCombK("pdfDeltaCombK", "pdf of delta k comb",
                                 deltaMass, lambdaDeltaCombK);
    RooExponential pdfBuCombK("pdfBuCombK", "pdf of bu k comb", buMass,
                              lambdaBuCombK);
    RooProdPdf pdfCombK("pdfCombK", "pdf of k comb", pdfDeltaCombK,
                        RooFit::Conditional(pdfBuSignalK, buMass));
    // ROOADDPDF
    RooRealVar yieldRatio("yieldRatio", "yieldRatio", 0.1, 0, 1);
    RooFormulaVar yieldSignalK("yieldSignalK", "yield of k signal", "@0*@1",
                               RooArgList(yieldSignalPi, yieldRatio));
    RooRealVar yieldBackgroundK("yieldBackgroundK", "yield of k background",
                                100, 0, 500);

    RooArgSet yieldsK;
    yieldsK.add(yieldSignalK);
    yieldsK.add(yieldBackgroundK);
    RooArgSet functionsK;
    functionsK.add(pdfSignalK);
    functionsK.add(pdfCombK);

    RooAddPdf pdfK("pdfK", "pdf k", functionsK, yieldsK);

    // CONSTRUCT SIMULTANEOUS PDF
    RooSimultaneous simPdf(("simPdf_" + std::to_string(i)).c_str(),
                           ("simPdf_" + std::to_string(i)).c_str(), bachelor);
    simPdf.addPdf(pdfPi, "pi");
    simPdf.addPdf(pdfK, "k");

    RooDataSet *toyDataSet =
        simPdf.generate(RooArgSet(buMass, deltaMass, bachelor), n_events);
    toyDataSet->SetName(("toyDataSet_" + std::to_string(i)).c_str());
    auto toyDataHist = std::unique_ptr<RooDataHist>(
        toyDataSet->binnedClone(("toyDataHist_" + std::to_string(i)).c_str(),
                                ("toyDataHist" + std::to_string(i)).c_str()));
    auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

    meanDeltaSignal.setVal(142);

    RooFitResult *result = 0;
    result = simPdf.fitTo(*toyAbsData, RooFit::Save(true));

    RooAbsArg *a0MeanAbsArg = const_cast<RooAbsArg *>(
        result->floatParsFinal().find("a0MeanBuSignal"));

    RooRealVar *a0MeanVar = dynamic_cast<RooRealVar *>(a0MeanAbsArg);
    if (a0MeanVar == nullptr) {
      std::stringstream output;
      output << "No value found in variable a0MeanBuSignal";
      throw std::runtime_error(output.str());
    }

    RooAbsArg *a1MeanAbsArg = const_cast<RooAbsArg *>(
        result->floatParsFinal().find("a1MeanBuSignal"));

    RooRealVar *a1MeanVar = dynamic_cast<RooRealVar *>(a1MeanAbsArg);
    if (a1MeanVar == nullptr) {
      std::stringstream output;
      output << "No value found in variable a1MeanBuSignal";
      throw std::runtime_error(output.str());
    }

    RooAbsArg *a2MeanAbsArg = const_cast<RooAbsArg *>(
        result->floatParsFinal().find("a2MeanBuSignal"));

    RooRealVar *a2MeanVar = dynamic_cast<RooRealVar *>(a2MeanAbsArg);
    if (a2MeanVar == nullptr) {
      std::stringstream output;
      output << "No value found in variable a2MeanBuSignal";
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
  treeFile.cd();
  tree.Write("", TObject::kOverwrite);
  treeFile.Write();
  treeFile.Close();

  std::cout << "Result saved in file " << outputDir << "/Tree_"
            << std::to_string(randomTag) << ".root\n";
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
