#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "RooRealVar.h"
#include "TAxis.h"
#include "RooFitResult.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TPad.h"
#include "TStyle.h"
#include "TTreeReader.h"

std::vector<std::string> SplitByComma(std::string const &str) {
  std::stringstream ss;
  ss.str(str);
  std::string tempString;
  std::vector<std::string> stringVector;
  // '' = char
  while (std::getline(ss, tempString, ',')) {
    stringVector.emplace_back(tempString);
  }
  return stringVector;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Pass comma separated string of filenames storing RooFitResults and output directory.\n";
    return 1;
  }
  std::vector<std::string> resultFiles = SplitByComma(argv[1]);
  std::string outputDir = argv[2];

  // Loop over filenames, open the files, then extract the RooFitResults and
  // from each and store in vector
  std::vector<RooFitResult> resultVec;

  for (auto &filename : resultFiles) {
    auto file = std::unique_ptr<TFile>(TFile::Open(filename.c_str()));
    auto result = std::unique_ptr<RooFitResult>(dynamic_cast<RooFitResult *>(
        file->FindObjectAny(("Result" + filename.substr(14, 8)).c_str())));
    if (result == nullptr) {
      throw std::runtime_error("Could not extract Result" +
                               filename.substr(14, 8) + " from " + filename);
    } else {
      resultVec.emplace_back(*result.get());
      // std::cout << "Extracted Result" + filename.substr(14, 8) + " from " +
      //                  filename  + "\n";
    }
  }

  // Create vector of histograms: automatically make histograms for the value,
  RooArgList initialPars0 = resultVec[0].floatParsInit();
  double nParams = initialPars0.getSize();
  std::cout << "Number of parameters stored in results = " << nParams << "\n";
  std::vector<TH1D> valHistVec(nParams);
  std::vector<TH1D> errHistVec(nParams);
  std::vector<TH1D> pullHistVec(nParams);
  // std::unique_ptr<RooAbsArg> paramAbsArg;
  // std::unique_ptr<RooRealVar> paramReal;
  RooAbsArg* paramAbsArg = nullptr;
  RooRealVar* paramRealVar = nullptr;

  for (double i = 0; i < nParams; ++i) {
    std::string varName = initialPars0.at(i)->GetName();
    std::cout << "Extracting parameter " << varName << std::endl;
    paramAbsArg = initialPars0.find(varName.c_str());
    // paramAbsArg = std::unique_ptr<RooAbsArg>(initialPars0.find(varName.c_str()));
    // if (paramAbsArg == nullptr) {
    //   throw std::runtime_error(
    //       "Could not extract RooAbsArg from RooArgList for " + varName);
    // }
    paramRealVar = dynamic_cast<RooRealVar *>(paramAbsArg);
    // paramRealVar =
    //     std::unique_ptr<RooRealVar>(dynamic_cast<RooRealVar *>(paramAbsArg.get()));
    // if (paramRealVar == nullptr) {
    //   throw std::runtime_error("Could not cast " + varName + " to RooRealVar.");
    // }
    double varMax = paramRealVar->getMax();
    double varMin = paramRealVar->getMin();
    TH1D valHist(("valHist_" + varName).c_str(), "", 50, varMin, varMax);
    valHist.SetStats(0);
    valHist.SetTitle(" ");
    valHist.GetXaxis()->SetTitle(varName.c_str());
    valHistVec[i] = valHist;
    TH1D errHist(("errHist_" + varName).c_str(), "", 50, -(varMax - varMin) / 10,
                 (varMax - varMin) / 10);
    errHist.SetStats(0);
    errHist.SetTitle(" ");
    errHist.GetXaxis()->SetTitle((varName + " Error").c_str());
    errHistVec[i] = errHist;
    TH1D pullHist(("pullHist_" + varName).c_str(), "", 50, -5, 5);
    pullHist.SetStats(0);
    pullHist.SetTitle(" ");
    pullHist.GetXaxis()->SetTitle((varName + " Pull").c_str());
    pullHistVec[i] = pullHist;
  }

  // Check result quality and print out stats 
  double nUnConv = 0;
  double nFPD = 0;
  double nMINOS = 0;
  // Fill histograms with elements of vectors: change max/min depending on
  // values
  // Loop over each result
  RooAbsArg* initialAbsArg = nullptr;
  RooRealVar* initialRealVar = nullptr;
  RooAbsArg* finalAbsArg = nullptr;
  RooRealVar* finalRealVar = nullptr;

  for (auto &result : resultVec) {
    // Check quality of result 
    // double edm = result.edm();
    double fitStatus = result.status();
    double covQual = result.covQual();
    if (covQual < 2) {
      nUnConv++;
    } else if (covQual < 3) {
      nFPD++;
    } else if (fitStatus != 0) {
      nMINOS++;
    } else {
      RooArgList initialPars = result.floatParsInit();
      RooArgList finalPars = result.floatParsFinal();
      // Loop over each parameter in result
      for (double i = 0; i < nParams; ++i) {
        initialAbsArg = initialPars.find(initialPars.at(i)->GetName());
        initialRealVar = dynamic_cast<RooRealVar *>(initialAbsArg);
        finalAbsArg = finalPars.find(finalPars.at(i)->GetName());
        finalRealVar = dynamic_cast<RooRealVar *>(finalAbsArg);
        // auto initialRealVar =
        //     std::unique_ptr<RooRealVar>(dynamic_cast<RooRealVar *>(
        //         initialPars.find(initialPars.at(i)->GetName())));
        // auto finalRealVar =
        //     std::unique_ptr<RooRealVar>(dynamic_cast<RooRealVar *>(
        //         finalPars.find(finalPars.at(i)->GetName())));
        // Extract initial value, final value and error: calulate pull
        double initialVal = initialRealVar->getVal();
        double finalVal = finalRealVar->getVal();
        double finalErr = finalRealVar->getError();
        double pull = (finalVal - initialVal) / finalErr;
        // Check histogram ranges
        if (abs(pull) > 5) {
          pullHistVec[i].SetBins(50, -(abs(pull)*5/4), abs(pull)*5/4);
        }
        double varMax = initialRealVar->getMax();
        double varMin = initialRealVar->getMin();
        if (abs(finalErr) > (varMax - varMin) / 10) {
          errHistVec[i].SetBins(50, -(abs(finalErr) + (varMax - varMin) / 10),
                                (abs(finalErr) + (varMax - varMin) / 10));
        }
        // Fill histograms 
        valHistVec[i].Fill(finalVal);
        errHistVec[i].Fill(finalErr);
        pullHistVec[i].Fill(pull);
      }
    }
  }

  // Plot histograms onto canvas and save
  for (double i = 0; i < nParams; ++i) {
    std::string varName = initialPars0.at(i)->GetName();
    TCanvas varCanvas((varName + "Canvas").c_str(), " ",
                      1500, 500);
    varCanvas.Divide(3, 1);
    varCanvas.cd(1);
    valHistVec[i].Draw();
    varCanvas.cd(2);
    errHistVec[i].Draw();
    varCanvas.cd(3);
    pullHistVec[i].Draw();
    varCanvas.SaveAs(
        (outputDir + "/ValErrPull_" + varName + ".pdf").c_str());
  }

  std::cout << "\nQuality of fits:\n"
            << "Unconverged: " << nUnConv / resultVec.size() * 100 << " %\n"
            << "Forced positive definite: " << nFPD / resultVec.size() * 100
            << " %\n"
            << "MINOS problems: " << nMINOS / resultVec.size() * 100 << " %\n";

  return 1;
}
