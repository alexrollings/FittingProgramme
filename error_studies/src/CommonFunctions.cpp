#include "CommonFunctions.h"

#include <algorithm>
#include <regex>

bool fexists(std::string const &filename) {
  std::ifstream infile(filename.c_str());
  return infile.is_open();
}

std::string to_string_with_precision(double value, int nDP) {
  std::ostringstream out;
  // fixed option sets number of DPs rather than SFs
  out << std::setprecision(nDP) << std::fixed << value;
  return out.str();
}

void AppendFiles(Mode mode, Configuration &config, 
                 std::vector<std::string> &input) {
  namespace fs = std::experimental::filesystem;
  std::regex re("\\/data\\/lhcb\\/users\\/rollings\\/Bu2Dst0h_mc_new_3\\/" +
                EnumToString(mode) + "((_201[0-9]|_ReDecay).*)");
  std::string treeDir("/data/lhcb/users/rollings/Bu2Dst0h_mc_new_3/");
  for (auto &p : fs::directory_iterator(treeDir)) {
    std::smatch sm;
    std::stringstream pathStream;
    pathStream << p;
    std::string pathStr(pathStream.str());
    pathStr.erase(std::remove(pathStr.begin(), pathStr.end(), '"'),
                  pathStr.end());
    if (std::regex_match(pathStr, sm, re)) {
      input.emplace_back(treeDir + EnumToString(mode) + sm[1].str() +
                         "/pi0/bach_pi" +
                         "/tmva_stage1/tmva_stage2_loose/to_fit/" +
                         EnumToString(mode) + sm[1].str() +
                         "_TM_Triggers_BDT1_BDT2_MERemoved_Fit.root");
    }
  }
}

void SetupTChain(Configuration &config, TChain &chain,
                 std::vector<std::string> const &input) {
  std::string tree = "BtoDstar0h3_h1h2pi0RTuple";
  try {
    chain.SetName(tree.c_str());
    std::cout << "Initialised TChain\n";
  } catch (std::exception &ex) {
    std::cout << "Could not set chain name : " << ex.what() << "!\n";
  }
  for (auto &f : input) {
    if (!fexists(f)) {
      throw std::logic_error(f + " does not exist\n");
    }
    try {
      chain.Add(f.c_str());
      std::cout << "Extracted TTree from " << f << "\n";
    } catch (std::exception &ex) {
      std::cout << "Failed to pass " << f << " to chain: " << ex.what()
                << "!\n";
    }
  }
}

void MakeMapFittingDataSet(
    Configuration &config, RooDataSet &dataset,
    std::map<std::string, RooDataSet *> &mapFittingDataSet) {
  RooDataSet *buDataSet = nullptr;
  buDataSet = dynamic_cast<RooDataSet *>(
      dataset.reduce(("Delta_M>" + std::to_string(config.deltaBoxLow) +
                      "&&Delta_M<" + std::to_string(config.deltaBoxHigh))
                         .c_str()));
  if (buDataSet == nullptr) {
    throw std::runtime_error("Could not reduce bu data with box cuts.");
  }
  buDataSet->SetName((EnumToString(Mass::bu) + "_DS").c_str());
  buDataSet->Print();
  mapFittingDataSet.insert(std::make_pair(EnumToString(Mass::bu), buDataSet));
  std::cout << "Appended dataSet to category " + EnumToString(Mass::bu) + "\n";
  RooDataSet *deltaDataSet = nullptr;
  deltaDataSet = dynamic_cast<RooDataSet *>(
      dataset.reduce(("Bu_Delta_M>" + std::to_string(config.buBoxLow) +
                      "&&Bu_Delta_M<" + std::to_string(config.buBoxHigh))
                         .c_str()));
  if (deltaDataSet == nullptr) {
    throw std::runtime_error("Could not reduce delta data with box cuts.");
  }
  deltaDataSet->SetName((EnumToString(Mass::delta) + "_DS").c_str());
  deltaDataSet->Print();
  mapFittingDataSet.insert(
      std::make_pair(EnumToString(Mass::delta), deltaDataSet));
  std::cout << "Appended dataSet to category " + EnumToString(Mass::delta) +
                   "\n";

}

std::vector<std::string> SplitLine(std::string const &str) {
  std::stringstream ss;
  ss.str(str);
  std::string tempString;
  std::vector<std::string> stringVector;
  // '' = char
  while (std::getline(ss, tempString, ' ')) {
    stringVector.emplace_back(tempString);
  }
  return stringVector;
}

void CalcBinomialErr(double eff, double nInit, double &err) {
  if (eff > 1) {
    throw std::logic_error("Cannot have efficiency > 1");
  }
  // std::cout << eff << "\t" << nInit << "\n";
  err = std::sqrt((eff * (1 - eff)) / nInit);
  // std::cout << err << "\n";
};

double ReturnBoxEff(Mode mode, Configuration &config, Efficiency eff) {
  std::string txtFileName =
      "/data/lhcb/users/rollings/txt_efficiencies_mc/pi0_" +
      EnumToString(mode) + "_" + config.ReturnBoxStr() + ".txt";

  std::string effStr;
  if (eff == Efficiency::deltaEff) {
    // Box eff for delta dimn is eff of buDelta window, and vice versa
    effStr = "buDeltaCutEff";
  } else if (eff == Efficiency::buEff) {
    effStr = "deltaCutEff";
  } else {
    effStr = "orEff";
  }

  if (!fexists(txtFileName)) {
    std::vector<std::string> input;
    AppendFiles(mode, config, input);
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
    std::string dlString = std::to_string(config.deltaBoxLow);
    std::string dhString = std::to_string(config.deltaBoxHigh);
    std::string blString = std::to_string(config.buBoxLow);
    std::string bhString = std::to_string(config.buBoxHigh);

    std::string orString;
    orString = "((Delta_M>" + dlString + "&&Delta_M<" + dhString +
               ")||(Bu_Delta_M>" + blString + "&&Bu_Delta_M<" + bhString + "))";
    std::string cutStr = config.cutString;
    cutStr += "&&Bu_Delta_M>" + std::to_string(config.buRangeLow) +
              "&&Bu_Delta_M<" + std::to_string(config.buRangeHigh) +
              "&&Delta_M>" + std::to_string(config.deltaRangeLow) +
              "&&Delta_M<" + std::to_string(config.deltaRangeHigh);

    double nInitial = chain.GetEntries(cutStr.c_str());
    std::cout << "nInitial = " << nInitial << "\n";
    double nOr = chain.GetEntries((cutStr + "&&" + orString).c_str());
    std::cout << "nOr = " << nOr << "\n";
    double nBuCut =
        chain.GetEntries((cutStr + "&&" + orString + "&&Bu_Delta_M>" +
                          blString + "&&Bu_Delta_M<" + bhString)
                             .c_str());
    std::cout << "nBuCut = " << nBuCut << "\n";
    double nDeltaCut =
        chain.GetEntries((cutStr + "&&" + orString + "&&Delta_M>" + dlString +
                          "&&Delta_M<" + dhString)
                             .c_str());
    std::cout << "nDeltaCut = " << nDeltaCut << "\n";

    double orEff = nOr / nInitial;
    double buDeltaCutEff = nBuCut / nOr;
    double deltaCutEff = nDeltaCut / nOr;

    double orEffErr;
    double buDeltaCutEffErr;
    double deltaCutEffErr;

    CalcBinomialErr(orEff, nInitial, orEffErr);
    CalcBinomialErr(buDeltaCutEff, nOr, buDeltaCutEffErr);
    CalcBinomialErr(deltaCutEff, nOr, deltaCutEffErr);

    std::ofstream outFile;
    outFile.open(txtFileName);
    outFile << "orEff " + std::to_string(orEff) + "\n";
    outFile << "orEffErr " + std::to_string(orEffErr) + "\n";
    outFile << "buDeltaCutEff " + std::to_string(buDeltaCutEff) + "\n";
    outFile << "buDeltaCutEffErr " + std::to_string(buDeltaCutEffErr) + "\n";
    outFile << "deltaCutEff " + std::to_string(deltaCutEff) + "\n";
    outFile << "deltaCutEffErr " + std::to_string(deltaCutEffErr) + "\n";

    if (eff == Efficiency::deltaEff) {
      return buDeltaCutEff;
    } else if (eff == Efficiency::buEff) {
      return deltaCutEff;
    } else {
      return orEff;
    }

  } else {
    //   // If exists, read in from txt file
    std::cout << txtFileName << " exists.\n";
    std::ifstream inFile(txtFileName);
    std::string line;
    // Loop over lines in txt file
    while (std::getline(inFile, line)) {
      // Separate label and value (white space)
      std::vector<std::string> lineVec = SplitLine(line);
      if (lineVec[0] == effStr) {
        std::cout << std::stod(lineVec[1]) << "\n";
        return std::stod(lineVec[1]);
      }
    }
    throw std::runtime_error("Efficiency not found.\n");
  }
}

void PlotComponent(RooAbsPdf *totPdf, Configuration &config,
                   std::unique_ptr<RooDataSet> &fullDataSet, Mass mass,
                   std::unique_ptr<RooPlot> &frame,
                   std::unique_ptr<RooPlot> &pullFrame, bool fitBool,
                   bool plotAll) {
  if (frame == nullptr) {
    throw std::runtime_error(EnumToString(mass) + " frame not initialised\n");
  }
  if (pullFrame == nullptr) {
    throw std::runtime_error(EnumToString(mass) +
                             " pull frame not initialised\n");
  }

  frame->SetTitleSize(0.065, "X");
  frame->SetTitleSize(0.058, "Y");
  frame->SetLabelSize(0.055, "XY");
  frame->SetTitleOffset(1.0, "X");
  frame->SetTitleOffset(0.9, "Y");
  frame->SetLabelFont(132, "XY");
  frame->SetTitleFont(132, "XY");

  pullFrame->SetTitle("");
  pullFrame->SetXTitle(" ");
  pullFrame->GetYaxis()->SetTitle("Residual (#sigma)");
  pullFrame->GetYaxis()->CenterTitle();
  pullFrame->SetLabelFont(132, "XY");
  pullFrame->SetTitleFont(132, "XY");
  pullFrame->SetTitleSize(0.13, "Y");
  pullFrame->SetTitleOffset(0.35, "Y");
  pullFrame->SetLabelSize(0.12, "XY");
  pullFrame->SetLabelOffset(0.01, "Y");
  pullFrame->GetYaxis()->SetRangeUser(-5, 5);
  pullFrame->GetYaxis()->SetNdivisions(6);

  if (config.fit1D == false) {
    fullDataSet->plotOn(
        frame.get(),
        RooFit::Cut(("fitting==fitting::" + EnumToString(mass)).c_str()));
  } else {
    fullDataSet->plotOn(frame.get());
  }
  if (fitBool == true) {
    if (config.fit1D == false) {
      totPdf->plotOn(frame.get(),
                     RooFit::Slice(config.fitting, EnumToString(mass).c_str()),
                     RooFit::ProjWData(config.fitting, *fullDataSet.get()),
                     RooFit::LineColor(kAzure - 3), RooFit::LineWidth(1));
    } else {
      totPdf->plotOn(frame.get(), RooFit::LineColor(kAzure - 3),
                     RooFit::LineWidth(1));
    }

    RooHist *pullHist = nullptr;
    pullHist = frame->RooPlot::pullHist();

    if (config.fit1D == false) {
      fullDataSet->plotOn(
          frame.get(),
          RooFit::Cut(("fitting==fitting::" + EnumToString(mass)).c_str()));
    } else {
      fullDataSet->plotOn(frame.get());
    }

    // Pull distribution is normalised
    pullFrame->addPlotable(pullHist, "P");
  }
  pullFrame->GetYaxis()->SetRangeUser(-5, 5);
}

void PlotOnCanvas(RooAbsPdf *totPdf, Configuration &config,
                  std::unique_ptr<RooDataSet> &fullDataSet, bool fitBool,
                  bool plotAll, std::string const &foutName, std::string const &label) {
  // Declare in config and initialise AFTER mass ranges have been set in order
  // to plot over correct range
  std::unique_ptr<RooPlot> buFrame =
      std::unique_ptr<RooPlot>(config.buMass.frame(RooFit::Title(" ")));
  std::unique_ptr<RooPlot> buPullFrame =
      std::unique_ptr<RooPlot>(config.buMass.frame(RooFit::Title(" ")));
  TLine buZeroLine(config.buRangeLow, 0, config.buRangeHigh, 0);
  buZeroLine.SetLineColor(kGray + 2);
  buZeroLine.SetLineStyle(kDashed);
  TLine buUpLine(config.buRangeLow, 3, config.buRangeHigh, 3);
  buUpLine.SetLineColor(kRed + 2);
  TLine buDownLine(config.buRangeLow, -3, config.buRangeHigh, -3);
  buDownLine.SetLineColor(kRed + 2);

  std::unique_ptr<RooPlot> deltaFrame =
      std::unique_ptr<RooPlot>(config.deltaMass.frame(RooFit::Title(" ")));
  std::unique_ptr<RooPlot> deltaPullFrame =
      std::unique_ptr<RooPlot>(config.deltaMass.frame(RooFit::Title(" ")));
  TLine deltaZeroLine(config.deltaRangeLow, 0, config.deltaRangeHigh, 0);
  deltaZeroLine.SetLineColor(kGray + 2);
  deltaZeroLine.SetLineStyle(kDashed);
  TLine deltaUpLine(config.deltaRangeLow, 3, config.deltaRangeHigh, 3);
  deltaUpLine.SetLineColor(kRed + 2);
  TLine deltaDownLine(config.deltaRangeLow, -3, config.deltaRangeHigh, -3);
  deltaDownLine.SetLineColor(kRed + 2);

  std::unique_ptr<RooPlot> buPartialFrame =
      std::unique_ptr<RooPlot>(config.buMass.frame(RooFit::Title(" ")));
  std::unique_ptr<RooPlot> buPartialPullFrame =
      std::unique_ptr<RooPlot>(config.buMass.frame(RooFit::Title(" ")));

  PlotComponent(totPdf, config, fullDataSet, Mass::bu, buFrame,
                buPullFrame, fitBool, plotAll);
  if (config.fit1D == false) {
    PlotComponent(totPdf, config, fullDataSet, Mass::delta, deltaFrame,
                  deltaPullFrame, fitBool, plotAll);
  }

  TCanvas canvas("canvas", "canvas", 4200, 2000);
  if (config.fit1D == false) {
    canvas.Divide(2, 1);
  } else {
    canvas.SetCanvasSize(2100, 2000);
  }

  gStyle->SetPadRightMargin(0.035);
  // gStyle->SetPadRightMargin(0);
  gStyle->SetPadLeftMargin(0.12);
  // gStyle->SetPadLeftMargin(0);
  gStyle->SetPadTopMargin(0.015);
  gStyle->SetOptTitle(0);
  gStyle->SetFrameLineWidth(1);
  gStyle->SetLineWidth(1);

  canvas.cd(1);
  gStyle->SetPadBottomMargin(0.15);
  TPad buPad("buPad", "buPad", 0.0, 0.32, 1.0, 1.0, kWhite);
  buPad.Draw();
  gStyle->SetPadBottomMargin(0.12);
  TPad buPadResids("buPadResids", "buPadResids", 0.0, 0.0, 1.0, 0.32, kWhite);
  buPadResids.Draw();
  buPad.cd();
  buFrame->Draw();
  buPadResids.cd();
  buPullFrame->Draw();
  buZeroLine.Draw();
  buUpLine.Draw();
  buDownLine.Draw();

  gStyle->SetPadBottomMargin(0.15);
  TPad deltaPad("deltaPad", "deltaPad", 0.0, 0.32, 1.0, 1.0, kWhite);
  gStyle->SetPadBottomMargin(0.12);
  TPad deltaPadResids("deltaPadResids", "deltaPadResids", 0.0, 0.0, 1.0, 0.32,
                      kWhite);
  if (config.fit1D == false) {
    canvas.cd(2);
    deltaPad.Draw();
    deltaPadResids.Draw();
    deltaPad.cd();
    deltaFrame->Draw();
    deltaPadResids.cd();
    deltaPullFrame->Draw();
    deltaZeroLine.Draw();
    deltaUpLine.Draw();
    deltaDownLine.Draw();
  }

  canvas.SaveAs((config.outputDir + "/plots/1D/" + foutName + "_" +
                 config.ReturnBoxStr() + "_" + label + ".eps")
                    .c_str());
}

void SaveResult(std::unique_ptr<RooFitResult> &fitResult, Configuration &config, std::string const &foutName) {
  fitResult->SetName("FitResult");
  TFile rFile(
      (config.outputDir + "/results/" + foutName + "_" + config.ReturnBoxStr() + ".root").c_str(),
      "recreate");
  fitResult->Write();
  rFile.Close();
}
