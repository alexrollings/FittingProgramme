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

  // RooRealVar buMean("Bu2Dst0h_D0pi0_mean1Bu", "", 5.2819e+03, 5250, 5290);
  // RooRealVar buSigma("Bu2Dst0h_D0pi0_sigma1Bu", "", 20, 10, 50);
  // RooRealVar buA1("Bu2Dst0h_D0pi0_a1Bu", "", 1, 0, 5);
  // RooRealVar buN1("Bu2Dst0h_D0pi0_n1Bu", "", 10);
  // RooRealVar buA2("Bu2Dst0h_D0pi0_a2Bu", "", -1, -5, -0.0001);
  // RooRealVar buN2("Bu2Dst0h_D0pi0_n2Bu", "", 10);
  // RooRealVar buFrac("Bu2Dst0h_D0pi0_fracPdf1Bu", "buFraction of component 1 in bu PDF", 2.0967e-01,
  //                   0, 1);
  // 136 160 
  // RooRealVar buMean("Bu2Dst0h_D0pi0_mean1Bu", "", 5.2730e+03);
  // RooRealVar buSigma("Bu2Dst0h_D0pi0_sigma1Bu", "", 2.2931e+01);
  // RooRealVar buA1("Bu2Dst0h_D0pi0_a1Bu", "", 9.1003e-01);
  // RooRealVar buN1("Bu2Dst0h_D0pi0_n1Bu", "", 10);
  // RooRealVar buA2("Bu2Dst0h_D0pi0_a2Bu", "", -2.2424e+00);
  // RooRealVar buN2("Bu2Dst0h_D0pi0_n2Bu", "", 10);
  // RooRealVar buFrac("Bu2Dst0h_D0pi0_fracPdf1Bu", "buFraction of component 1 in bu PDF", 9.5717e-02);

  // RooCBShape buPdf1("buPdf1", "", config.buMass, buMean, buSigma, buA1, buN1);
  // RooCBShape buPdf2("buPdf2", "", config.buMass, buMean, buSigma, buA2, buN2);
  // RooAddPdf buPdf("buPdf", "", RooArgSet(buPdf1, buPdf2), buFrac);

  // RooRealVar deltaMean("Bu2Dst0h_D0pi0_meanDelta", "", 143, 136, 160);
  // RooRealVar deltaSigma("Bu2Dst0h_D0pi0_sigmaDelta", "", 2, 0, 10);
  // RooRealVar deltaA1("Bu2Dst0h_D0pi0_a1Delta", "", 1, 0, 5);
  // RooRealVar deltaN1("Bu2Dst0h_D0pi0_n1Delta", "", 10);
  // RooRealVar deltaA2("Bu2Dst0h_D0pi0_a2Delta", "", -1, -5, -0.0001);
  // RooRealVar deltaN2("Bu2Dst0h_D0pi0_n2Delta", "", 10);
  // RooRealVar deltaFrac("Bu2Dst0h_D0pi0_fracPdf1Delta", "deltaFraction of component 1 in delta PDF",
  //                      0.5, 0, 1);

  // 5170 5370
  // RooRealVar deltaMean("Bu2Dst0h_D0pi0_meanDelta", "", 1.4241e+02);
  // RooRealVar deltaSigma("Bu2Dst0h_D0pi0_sigmaDelta", "", 1.6230e+00);
  // RooRealVar deltaA1("Bu2Dst0h_D0pi0_a1Delta", "", 7.5392e-01);
  // RooRealVar deltaN1("Bu2Dst0h_D0pi0_n1Delta", "", 10);
  // RooRealVar deltaA2("Bu2Dst0h_D0pi0_a2Delta", "", -6.1887e-01);
  // RooRealVar deltaN2("Bu2Dst0h_D0pi0_n2Delta", "", 10);
  // RooRealVar deltaFrac("Bu2Dst0h_D0pi0_fracPdf1Delta", "deltaFraction of component 1 in delta PDF", 2.1771e-01);

  // 5170 5220
  // RooRealVar deltaMean("Bu2Dst0h_D0pi0_meanDelta", "", 1.4287e+02);
  // RooRealVar deltaSigma("Bu2Dst0h_D0pi0_sigmaDelta", "", 2.1217e+00);
  // RooRealVar deltaA1("Bu2Dst0h_D0pi0_a1Delta", "", 4.1785e+00);
  // RooRealVar deltaN1("Bu2Dst0h_D0pi0_n1Delta", "", 10);
  // RooRealVar deltaA2("Bu2Dst0h_D0pi0_a2Delta", "", -3.8947e+00);
  // RooRealVar deltaN2("Bu2Dst0h_D0pi0_n2Delta", "", 10);
  // RooRealVar deltaFrac("Bu2Dst0h_D0pi0_fracPdf1Delta", "deltaFraction of component 1 in delta PDF", 4.6238e-01);

  // RooCBShape deltaPdf1("deltaPdf1", "", config.deltaMass, deltaMean, deltaSigma,
  //                      deltaA1, deltaN1);
  // RooCBShape deltaPdf2("deltaPdf2", "", config.deltaMass, deltaMean, deltaSigma,
  //                      deltaA2, deltaN2);
  // RooAddPdf deltaPdf("deltaPdf", "", RooArgSet(deltaPdf1, deltaPdf2),
  //                    deltaFrac);

  RooArgList functionsBu;
  functionsBu.add(model.buPdf);
  RooArgList functionsDelta;
  functionsDelta.add(model.deltaPdf);
  if (signalOnly == false) {
    functionsBu.add(buBkgPdf);
    functionsDelta.add(deltaBkgPdf);
  }

  RooRealVar N_tot("N_tot", "", 10000, 0, 50000);
  RooRealVar eff_Bu("eff_Bu", "", ReturnBoxEff(sigMode, config, Efficiency::buEff));
  RooRealVar eff_Delta("eff_Delta", "",
                       ReturnBoxEff(sigMode, config, Efficiency::deltaEff));
  RooFormulaVar N_Bu("N_Bu", "@0*@1", RooArgList(N_tot, eff_Bu));
  RooFormulaVar N_Delta("N_Delta", "@0*@1",
                        RooArgList(N_tot, eff_Delta));

  RooRealVar N_Bu_1D("N_Bu_1D", "", 10000, 0, 50000);
  RooRealVar N_Bu_Bkg("N_Bu_Bkg", "", N_Bkg, 0, 50000);
  RooRealVar N_Delta_Bkg("N_Delta_Bkg", "", N_Bkg, 0, 50000);

  RooArgList yieldsBu;
  if (config.fit1D == false) {
    yieldsBu.add(N_Bu);
  } else {
    yieldsBu.add(N_Bu_1D);
  }
  RooArgList yieldsDelta;
  yieldsDelta.add(N_Delta);
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
