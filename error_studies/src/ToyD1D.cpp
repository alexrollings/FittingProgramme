#include "RooAbsBinning.h"
#include "RooDataHist.h"
#include "RooProdPdf.h"

#include <iostream>
#include <string>
#include <vector>

#include "CommonFunctions.h"
#include "Configuration.h"
#include "ParseArguments.h"
#include "ToyFunctions.h"
#include "Model.h"


int main(int argc, char **argv) {
  bool remakeDS = false;
  bool fitBool = true;
  bool plotAll = false;
  bool fit1DArg = false;
  bool signalOnly = false;
  int blArg = 5220;
  int bhArg = 5330;
  int dlArg = 138;
  int dhArg = 148;
  {
    ParseArguments args(argc, argv);
    if (args("F")) {
      std::cout << "Force remake of RDS.\n";
      remakeDS = true;
    }
    if (args("noFit")) {
      std::cout << "Don't fit PDF to data: just plot data.\n";
      fitBool = false;
    }
    if (args("plotPdfs")) {
      std::cout << "Plot component PDFs.\n";
      plotAll = true;
    }
    if (args("1D")) {
      std::cout << "Fitting in m(B) only.\n";
      fit1DArg = true;
    }
    if (args("sig")) {
      std::cout << "Fitting signal MC only.\n";
      signalOnly = true;
    }
    if (!args("dl", dlArg)) {
      std::cout << "Using default lower box limit for m(Delta):" + std::to_string(dlArg) + ".\n";
    }
    if (!args("dh", dhArg)) {
      std::cout << "Using default upper box limit for m(Delta):" + std::to_string(dhArg) + ".\n";
    }
    if (!args("bl", blArg)) {
      std::cout << "Using default lower box limit for m(B):" + std::to_string(blArg) + ".\n";
    } 
    if (!args("bh", bhArg)) {
      std::cout << "Using default upper box limit for m(B):" + std::to_string(bhArg) + ".\n";
    }
  }

  Configuration config(dlArg, dhArg, blArg, bhArg);
  config.fit1D = fit1DArg;

  Mode sigMode = Mode::Bu2Dst0pi_D0pi0;
  RooDataSet *sigDataset = nullptr;
  std::string sigFname = "/data/lhcb/users/rollings/mc_roodatasets/pi0_" +
                        EnumToString(sigMode) + "_pi.root";
  if (!fexists(sigFname) || remakeDS == true) {
    std::cerr << "Making dataset: " << sigFname << ".\n";
    std::vector<std::string> input;
    AppendFiles(sigMode, config, input);
    if (input.size() == 0) {
      throw std::runtime_error("No input files found\n");
    }
    TChain chain("");
    SetupTChain(config, chain, input);
    std::cout << "Returned TChain\n";
    try {
      chain.GetEntry(0);
    } catch (std::exception &ex) {
      std::cout << "Could net GetEntry(0) from chain: " << ex.what() << "!\n";
    }
    sigDataset =
        new RooDataSet("sigDataset", "sigDataset", &chain, config.variableArgset);
    TFile dsFile(sigFname.c_str(), "RECREATE");
    sigDataset->Write("dataset");
    dsFile.Close();
  } else {
    std::cout << sigFname << " exists.\n";
    TFile dsFile(sigFname.c_str(), "READ");
    gDirectory->GetObject("dataset", sigDataset);
    if (sigDataset == nullptr) {
      throw std::runtime_error("Dataset does not exist.\n");
    } else {
      std::cout << "dataset extracted: \n";
      sigDataset->Print();
    }
  }

  config.buRangeLow = 5150;
  config.buRangeHigh = 5450;
  config.buBins = (config.buRangeHigh - config.buRangeLow) / 5;
  config.deltaRangeLow = 136;
  config.deltaRangeHigh = 160;
  config.deltaBins = (config.deltaRangeHigh - config.deltaRangeLow);
  config.buMass.setMin(config.buRangeLow);
  config.buMass.setMax(config.buRangeHigh);
  config.deltaMass.setMin(config.deltaRangeLow);
  config.deltaMass.setMax(config.deltaRangeHigh);

  RooRealVar buLambda("buLambda", "", -0.005, -1, 1);
  RooExponential buBkgPdf("buBkgPfg", "", config.buMass, buLambda);

  RooRealVar deltaLambda("deltaLambda", "", 0.05, -1, 1);
  RooExponential deltaBkgPdf("deltaBkgPfg", "", config.deltaMass, deltaLambda);

  double N_Bkg = 5000;
  RooProdPdf bkgPdf("bkgPdf", "", RooArgSet(buBkgPdf, deltaBkgPdf));  
  RooDataSet *gen2DBkgData = bkgPdf.generate(
      RooArgSet(config.buMass, config.deltaMass), N_Bkg);
  gen2DBkgData->Print();

  RooDataSet *gen1DBkgData = bkgPdf.generate(RooArgSet(config.buMass), N_Bkg);
  gen1DBkgData->Print();

  std::unique_ptr<RooDataSet> fullDataSet = nullptr;

  if (config.fit1D == false) {
    if (signalOnly == false) {
      sigDataset->append(*gen2DBkgData);
    }
    RooDataSet *reducedDataset = nullptr;
    if (sigDataset != nullptr) {
      reducedDataset = dynamic_cast<RooDataSet *>(
          sigDataset->reduce(config.fittingArgset, config.cutString.c_str()));
    } else {
      throw std::runtime_error("Dataset was not loaded.\n");
    }
    std::map<std::string, RooDataSet *> mapFittingDataSet;
    MakeMapFittingDataSet(config, *reducedDataset, mapFittingDataSet);
    fullDataSet = std::unique_ptr<RooDataSet>(new RooDataSet(
        "fullDataSet", "fullDataSet", config.fittingArgset,
        RooFit::Index(config.fitting), RooFit::Import(mapFittingDataSet)));
  } else {
    if (signalOnly == false) {
      sigDataset->append(*gen1DBkgData);
    }
    std::cout << config.cutString << std::endl;
    fullDataSet = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
        sigDataset->reduce(config.buMass, config.cutString.c_str())));
  }
  fullDataSet->Print();

  int id = 0;
  Model model(config, id);

  RooArgList functionsBu;
  functionsBu.add(model.buPdf);
  RooArgList functionsDelta;
  functionsDelta.add(model.deltaPdf);
  if (signalOnly == false) {
    functionsBu.add(buBkgPdf);
    functionsDelta.add(deltaBkgPdf);
  }

  RooRealVar N_Bu_Bkg("N_Bu_Bkg", "", N_Bkg, 0, 50000);
  RooRealVar N_Delta_Bkg("N_Delta_Bkg", "", N_Bkg, 0, 50000);

  RooArgList yieldsBu;
  yieldsBu.add(*model.N_Bu);
  RooArgList yieldsDelta;
  yieldsDelta.add(model.N_Delta);
  if (signalOnly == false) {
    yieldsBu.add(N_Bu_Bkg);
    yieldsDelta.add(N_Delta_Bkg);
  }

  RooAddPdf buAddPdf("buAddPdf", "", functionsBu, yieldsBu);
  RooAddPdf deltaAddPdf("deltaAddPdf", "", functionsDelta, yieldsDelta);

  std::unique_ptr<RooFitResult> fitResult = nullptr;
  std::vector<RooAbsPdf *> buPdfs;
  std::vector<RooAbsPdf *> deltaPdfs;

  std::string foutName = EnumToString(sigMode);
  if (config.fit1D == false) {
    auto pdfToFit = std::unique_ptr<RooSimultaneous>(
        new RooSimultaneous("pdfToFit", "pdfToFit", config.fitting));
    pdfToFit->addPdf(buAddPdf, EnumToString(Mass::bu).c_str());
    pdfToFit->addPdf(deltaAddPdf, EnumToString(Mass::delta).c_str());
    if (fitBool == true) {
      fitResult = std::unique_ptr<RooFitResult>(
          pdfToFit->fitTo(*fullDataSet.get(), RooFit::Save(),
                          RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                          RooFit::Offset(true)));

    }
    PlotOnCanvas(pdfToFit.get(), config, fullDataSet, fitBool, plotAll, foutName);
  } else {
    fitResult = std::unique_ptr<RooFitResult>(
        buAddPdf.fitTo(*fullDataSet.get(), RooFit::Save(), RooFit::Strategy(2),
                        RooFit::Minimizer("Minuit2"), RooFit::Offset(true)));
    PlotOnCanvas(&buAddPdf, config, fullDataSet, fitBool, plotAll, foutName);
  }
  fitResult->Print();
  SaveResult(fitResult, config, foutName);

  return 0;
}
