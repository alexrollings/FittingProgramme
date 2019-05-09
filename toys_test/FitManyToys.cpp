#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "RooRealVar.h"
#include "RooArgList.h"
#include "RooArgSet.h"
#include "RooDataHist.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "TAxis.h"
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
    std::cerr << "Pass comma separated string of filenames storing "
                 "RooFitResults and output directory.\n";
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

  // Check result quality and print out stats
  double nUnConv = 0;
  double nFPD = 0;
  double nMINOS = 0;
  
  // Save values into vectors and set max/min depending on
  // values: one max/min for each parameter (but all results)
  std::vector<double> valMin(nParams, 1000000);
  std::vector<double> valMax(nParams, -1000000);
  std::vector<double> errMin(nParams, 1000000);
  std::vector<double> errMax(nParams, -1000000);
  std::vector<double> pullMin(nParams, 1000000);
  std::vector<double> pullMax(nParams, -1000000);
  std::vector<std::vector<double> > valVec(resultVec.size(),
                                           std::vector<double>(nParams));
  std::vector<std::vector<double> > errVec(resultVec.size(),
                                           std::vector<double>(nParams));
  std::vector<std::vector<double> > pullVec(resultVec.size(),
                                            std::vector<double>(nParams));

  RooAbsArg *initialAbsArg = nullptr;
  RooRealVar *initialRealVar = nullptr;
  RooAbsArg *finalAbsArg = nullptr;
  RooRealVar *finalRealVar = nullptr;

  for (double j = 0; j < resultVec.size(); ++j) {
    // Check quality of result
    // double edm = resultVec[j].edm();
    double fitStatus = resultVec[j].status();
    double covQual = resultVec[j].covQual();
    if (covQual < 2) {
      nUnConv++;
    } else if (covQual < 3) {
      nFPD++;
    } else if (fitStatus != 0) {
      nMINOS++;
    } else {
      RooArgList initialPars = resultVec[j].floatParsInit();
      RooArgList finalPars = resultVec[j].floatParsFinal();
      // Loop over each parameter in result
      for (double i = 0; i < nParams; ++i) {
        initialAbsArg = initialPars.find(initialPars.at(i)->GetName());
        initialRealVar = dynamic_cast<RooRealVar *>(initialAbsArg);
        finalAbsArg = finalPars.find(finalPars.at(i)->GetName());
        finalRealVar = dynamic_cast<RooRealVar *>(finalAbsArg);
        finalRealVar->Print();
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
        std::cout << finalPars.at(i)->GetName() << " = " << finalVal << " ± "
                  << finalErr << " with pull " << pull << " and initial val "
                  << initialVal << "\n";
        // Fill histograms
        valVec[j][i] = finalVal;
        errVec[j][i] = finalErr;
        pullVec[j][i] = pull;

        if (finalVal > valMax[i]) {
          valMax[i] = finalVal;
        }
        if (finalVal < valMin[i]) {
          valMin[i] = finalVal;
        }
        if (finalErr > errMax[i]) {
          errMax[i] = finalErr;
        }
        if (finalErr < errMin[i]) {
          errMin[i] = finalErr;
        }
        if (pull > pullMax[i]) {
          pullMax[i] = pull;
        }
        if (pull < pullMin[i]) {
          pullMin[i] = pull;
        }
      }
    }
  }

  // Loop over params, create histogram for each and fill with values from result
  for (double i = 0; i < nParams; ++i) {
    std::string paramName = initialPars0.at(i)->GetName();
    std::cout << "Extracting parameter " << paramName << std::endl;

    double valRange = valMax[i] - valMin[i];
    TH1D valHist(("valHist_" + paramName).c_str(), "", round(resultVec.size()/5),
                 valMin[i] - valRange/5, valMax[i] + valRange/5);
    double errRange = errMax[i] - errMin[i];
    TH1D errHist(("errHist_" + paramName).c_str(), "", round(resultVec.size()/5),
                 errMin[i] - errRange/5, errMax[i] + errRange/5);
    double pullRange = pullMax[i] - pullMin[i];
    TH1D pullHist(("pullHist_" + paramName).c_str(), "", round(resultVec.size()/5),
                 pullMin[i] - pullRange/5, pullMax[i] + pullRange/5);
    for (double j = 0; j < round(resultVec.size() / 5); ++j) {
      valHist.Fill(valVec[j][i]);
      errHist.Fill(errVec[j][i]);
      pullHist.Fill(pullVec[j][i]);
    }
    TCanvas varCanvas((paramName + "Canvas").c_str(), " ", 1500, 500);
    varCanvas.Divide(3, 1);
    // Create RRVs for each parameter's value, error and pull
    // Make into function and pass relevant histogram
    RooRealVar val(("val_" + paramName).c_str(), "",
                   valHist.GetXaxis()->GetXmin(),
                   valHist.GetXaxis()->GetXmax());
    RooDataHist valDH(("valDH_" + paramName).c_str(), "", RooArgSet(val),
                      RooFit::Import(valHist));
    std::unique_ptr<RooPlot> valFrame(val.frame(RooFit::Title(" ")));
    valFrame->GetXaxis()->SetTitle(paramName.c_str());
    valDH.plotOn(valFrame.get());
    varCanvas.cd(1);
    valFrame->Draw();

    RooRealVar err(("err_" + paramName).c_str(), "",
                   errHist.GetXaxis()->GetXmin(),
                   errHist.GetXaxis()->GetXmax());
    RooDataHist errDH(("errDH_" + paramName).c_str(), "", RooArgSet(err),
                      RooFit::Import(errHist));
    std::unique_ptr<RooPlot> errFrame(err.frame(RooFit::Title(" ")));
    errFrame->GetXaxis()->SetTitle((paramName + " Error").c_str());
    errDH.plotOn(errFrame.get());
    varCanvas.cd(2);
    errFrame->Draw();

    RooRealVar pull(("pull_" + paramName).c_str(), "",
                   pullHist.GetXaxis()->GetXmin(),
                   pullHist.GetXaxis()->GetXmax());
    RooDataHist pullDH(("pullDH_" + paramName).c_str(), "", RooArgSet(pull),
                      RooFit::Import(pullHist));
    std::unique_ptr<RooPlot> pullFrame(pull.frame(RooFit::Title(" ")));
    pullFrame->GetXaxis()->SetTitle((paramName + " Pull").c_str());
    pullDH.plotOn(pullFrame.get());
    varCanvas.cd(3);
    pullFrame->Draw();
    varCanvas.SaveAs((outputDir + "/ValErrPull_" + paramName + ".pdf").c_str());
  }

  std::cout << "\nQuality of fits:\n"
            << "Unconverged: " << nUnConv / resultVec.size() * 100 << " %\n"
            << "Forced positive definite: " << nFPD / resultVec.size() * 100
            << " %\n"
            << "MINOS problems: " << nMINOS / resultVec.size() * 100 << " %\n";

  return 1;
}
