#include "RooAbsBinning.h"
#include "RooDataHist.h"

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
  bool signalOnlyArg = false;
  int blArg = 5220;
  int bhArg = 5330;
  int dlArg = 138;
  int dhArg = 148;
  int nToys = 0;
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
      signalOnlyArg = true;
    }
    if (args("nToys", nToys)) {
      std::cout << nToys << " toys being run.\n";
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
  config.signalOnly = signalOnlyArg;
  if (config.fit1D == true) {
    nToys = 0;
    std::cout << "Setting nToys to 0: cannot run D1D toys with 1D PDF.\n";
  }

  Mode sigMode = Mode::Bu2Dst0pi_D0pi0;
  RooDataSet *sigDataSet = nullptr;
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
    sigDataSet =
        new RooDataSet("sigDataSet", "sigDataSet", &chain, config.variableArgset);
    TFile dsFile(sigFname.c_str(), "RECREATE");
    sigDataSet->Write("dataset");
    dsFile.Close();
  } else {
    std::cout << sigFname << " exists.\n";
    TFile dsFile(sigFname.c_str(), "READ");
    gDirectory->GetObject("dataset", sigDataSet);
    if (sigDataSet == nullptr) {
      throw std::runtime_error("DataSet does not exist.\n");
    } else {
      std::cout << "dataset extracted: \n";
      sigDataSet->Print();
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

  int id = 0;
  Model model(config, id);

  RooDataSet *genData;
  if (config.fit1D == false) {
    genData =
        model.bkgPdf.generate(RooArgSet(config.buMass, config.deltaMass),
                              model.N_Bkg);
  } else {
    genData = model.buBkgPdf.generate(RooArgSet(config.buMass),
                                      model.N_Bkg);
  }
  genData->Print();

  std::unique_ptr<RooDataSet> fullDataSet = nullptr;
  std::map<std::string, RooDataSet *> mapFittingDataSet;
  std::unique_ptr<RooDataSet> reducedDataSet = nullptr;

  if (config.fit1D == false) {
    if (config.signalOnly == false) {
      sigDataSet->append(*genData);
    }
    if (sigDataSet != nullptr) {
      reducedDataSet = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
          sigDataSet->reduce(config.fittingArgset, config.cutString.c_str())));
    } else {
      throw std::runtime_error("DataSet was not loaded.\n");
    }
    MakeMapFittingDataSet(config, *reducedDataSet, mapFittingDataSet);
    fullDataSet = std::unique_ptr<RooDataSet>(new RooDataSet(
        "fullDataSet", "fullDataSet", config.fittingArgset,
        RooFit::Index(config.fitting), RooFit::Import(mapFittingDataSet)));
  } else {
    if (config.signalOnly == false) {
      sigDataSet->append(*genData);
    }
    std::cout << config.cutString << std::endl;
    fullDataSet = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
        sigDataSet->reduce(config.buMass, config.cutString.c_str())));
  }
  fullDataSet->Print();

  std::unique_ptr<RooFitResult> fitResult = nullptr;

  std::string foutName = EnumToString(sigMode);
  if (config.fit1D == false) {
    if (fitBool == true) {
      fitResult = std::unique_ptr<RooFitResult>(
          model.simPdf->fitTo(*fullDataSet.get(), RooFit::Save(),
                          RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                          RooFit::Offset(true)));

    }
    std::string label = "data";
    PlotOnCanvas(model.simPdf.get(), config, fullDataSet, fitBool, plotAll, foutName, label);
  } else {
    fitResult = std::unique_ptr<RooFitResult>(
        model.buAddPdf->fitTo(*fullDataSet.get(), RooFit::Save(), RooFit::Strategy(2),
                        RooFit::Minimizer("Minuit2"), RooFit::Offset(true)));
    std::string label = "data";
    PlotOnCanvas(model.buAddPdf.get(), config, fullDataSet, fitBool, plotAll, foutName, label);
  }

  for (int id = 1; id < nToys + 1; ++id) {
    std::cout << "\n\n -------------------------- Running toy #" << id
              << " -------------------------- \n\n";

    Model toyModel(config, id);

    std::unique_ptr<RooDataSet> genDataSet;
    GenerateToyFromData(reducedDataSet, genDataSet, id, config);
    if (genDataSet == nullptr) {
      throw std::runtime_error("\ngenDataSet returns nullptr\n");
    }

    Plotting2D(config, *genDataSet, *reducedDataSet);

    std::map<std::string, RooDataSet *> mapFittingToy;
    MakeMapFittingDataSet(config, *genDataSet.get(), mapFittingToy);

    auto toyDataSet = std::unique_ptr<RooDataSet>(new RooDataSet(
        ("toyDataSet_" + std::to_string(id)).c_str(), "toyDataSet",
        config.fittingArgset, RooFit::Index(config.fitting),
        RooFit::Import(mapFittingToy)));
    toyDataSet->Print();

    std::shared_ptr<RooFitResult> toyFitResult;
    toyFitResult = std::shared_ptr<RooFitResult>(toyModel.simPdf->fitTo(
        *toyDataSet.get(), RooFit::Save(), RooFit::Strategy(2),
        RooFit::Minimizer("Minuit2"), RooFit::Offset(true)));
    // RooFit::Extended(kTRUE)
    toyFitResult->SetName("ToyResult");

    fitResult->Print("v");
    toyFitResult->Print("v");
    std::string label = "toy";
    PlotOnCanvas(toyModel.simPdf.get(), config, toyDataSet, fitBool, plotAll,
                 foutName, label);

    // outputFile.cd();
    // toyFitResult->Write();
    // fitResult->Write();
    // outputFile.Close();
    // std::cout << toyFitResult->GetName() << " has been saved to file "
    //           << outputFile.GetName() << "\n";
  }
  // fitResult->Print();
  // SaveResult(fitResult, config, foutName);

  return 0;
}
