#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include "RooRealVar.h"
#include "RooArgList.h"
#include "RooArgSet.h"
#include "RooDataHist.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooGaussian.h"
#include "TAxis.h"
#include "TLegend.h"
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

std::string to_string_with_precision(double value) {
  std::ostringstream out;
  out << std::setprecision(3) << value;
  return out.str();
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
    std::regex fileRexp(".+_([0-9].[0-9]+)_[0-9]+_[0-9]+_[0-9]+_[0-9]+.root");
    std::smatch fileMatch;
    std::regex_search(filename, fileMatch, fileRexp);
    std::string rndm = fileMatch[1];
    auto result = std::unique_ptr<RooFitResult>(dynamic_cast<RooFitResult *>(
        file->FindObjectAny(("Result_" + rndm).c_str())));
    if (result == nullptr) {
      throw std::runtime_error("Could not extract Result from " + filename);
    } else {
      resultVec.emplace_back(*result.get());
      std::cout << "Extracted Result from " << filename << "\n";
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
  // Save initial values for starting point of mean
  std::vector<double> initialVec(nParams);
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

  std::cout << "Number of results saved = " << resultVec.size() << "\n";

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
        // Fill histograms
        initialVec[i] = initialVal;
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
    // Extract parameter names using regular expression in order to remove _#
    std::string fullName = initialPars0.at(i)->GetName();
    // std::cout << "Full parameter name = " << fullName << "\n";
    std::regex rexp("([A-Za-z0-9]+)_[0-9]+");
    std::smatch match;
    std::regex_search(fullName, match, rexp);
    std::string paramName = match[1];
    // std::cout << "After regex, parameter name = " << paramName << "\n";


    double valRange = valMax[i] - valMin[i];
    // TH1D valHist(("valHist_" + paramName).c_str(), "", round(resultVec.size()/20),
    TH1D valHist(("valHist_" + paramName).c_str(), "", 50,
                 valMin[i] - valRange/5, valMax[i] + valRange/5);
    double errRange = errMax[i] - errMin[i];
    // TH1D errHist(("errHist_" + paramName).c_str(), "", round(resultVec.size()/20),
    TH1D errHist(("errHist_" + paramName).c_str(), "", 50,
                 errMin[i] - errRange/5, errMax[i] + errRange/5);
    // double pullRange = pullMax[i] - pullMin[i];
    // TH1D pullHist(("pullHist_" + paramName).c_str(), "", round(resultVec.size()/10),
    //              pullMin[i] - pullRange/5, pullMax[i] + pullRange/5);
    TH1D pullHist(("pullHist_" + paramName).c_str(), "", 50, -5, 5);
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
    RooRealVar valMean(("valMean_" + paramName).c_str(), "", initialVec[i],
                       val.getMin(), val.getMax());
    RooRealVar valSigma(("valSigma_" + paramName).c_str(), "",
                        (val.getMax() - val.getMin()) / 5, 0,
                        val.getMax() - val.getMin());
    RooGaussian valGaus(("valGauss_" + paramName).c_str(), "", val, valMean,
                        valSigma);
    auto valResult =
        std::unique_ptr<RooFitResult>(valGaus.fitTo(valDH, RooFit::Save()));
    valResult->Print("v");
    std::unique_ptr<RooPlot> valFrame(val.frame(RooFit::Title(" ")));
    valFrame->GetXaxis()->SetTitle(paramName.c_str());
    valDH.plotOn(valFrame.get());
    valGaus.plotOn(valFrame.get(), RooFit::LineColor(kRed), RooFit::LineWidth(2));
    valDH.plotOn(valFrame.get());
    varCanvas.cd(1);
    valFrame->Draw();
    
    auto blankHist = std::make_unique<TH1D>("blankHist", "", 1, 0, 1);
    blankHist->SetLineColor(kWhite);
    TLegend valLegend(0.5, 0.78, 0.85, 0.88);
    valLegend.SetTextSize(0.03);
    valLegend.SetLineColor(kWhite);
    std::stringstream valMeanString, valSigmaString;
    valMeanString << "#mu = " << to_string_with_precision(valMean.getVal());
    valMeanString << " #pm " << to_string_with_precision(valMean.getPropagatedError(*valResult.get()));
    valSigmaString << "#sigma = " << to_string_with_precision(valSigma.getVal());
    valSigmaString << " #pm " << to_string_with_precision(valSigma.getPropagatedError(*valResult.get()));
    valLegend.AddEntry(blankHist.get(), valMeanString.str().c_str(), "l");
    valLegend.AddEntry(blankHist.get(), valSigmaString.str().c_str(), "l");
    valLegend.Draw("same");

    RooRealVar err(("err_" + paramName).c_str(), "",
                   errHist.GetXaxis()->GetXmin(),
                   errHist.GetXaxis()->GetXmax());
    RooDataHist errDH(("errDH_" + paramName).c_str(), "", RooArgSet(err),
                      RooFit::Import(errHist));
    RooRealVar errMean(("errMean_" + paramName).c_str(), "",
                       err.getMin() + (err.getMax() - err.getMin()) / 2,
                       err.getMin(), err.getMax());
    RooRealVar errSigma(("errSigma_" + paramName).c_str(), "",
                        (err.getMax() - err.getMin()) / 5, 0,
                        err.getMax() - err.getMin());
    RooGaussian errGaus(("errGauss_" + paramName).c_str(), "", err, errMean,
                        errSigma);
    auto errResult =
        std::unique_ptr<RooFitResult>(errGaus.fitTo(errDH, RooFit::Save()));
    errResult->Print("v");
    std::unique_ptr<RooPlot> errFrame(err.frame(RooFit::Title(" ")));
    errFrame->GetXaxis()->SetTitle((paramName + " Error").c_str());
    errDH.plotOn(errFrame.get());
    errGaus.plotOn(errFrame.get(), RooFit::LineColor(kRed), RooFit::LineWidth(2));
    errDH.plotOn(errFrame.get());
    varCanvas.cd(2);
    errFrame->Draw();

    TLegend errLegend(0.5, 0.78, 0.85, 0.88);
    errLegend.SetTextSize(0.03);
    errLegend.SetLineColor(kWhite);
    std::stringstream errMeanString, errSigmaString;
    errMeanString << "#mu = " << to_string_with_precision(errMean.getVal());
    errMeanString << " #pm " << to_string_with_precision(errMean.getPropagatedError(*errResult.get()));
    errSigmaString << "#sigma = " << to_string_with_precision(errSigma.getVal());
    errSigmaString << " #pm " << to_string_with_precision(errSigma.getPropagatedError(*errResult.get()));
    errLegend.AddEntry(blankHist.get(), errMeanString.str().c_str(), "l");
    errLegend.AddEntry(blankHist.get(), errSigmaString.str().c_str(), "l");
    errLegend.Draw("same");

    RooRealVar pull(("pull_" + paramName).c_str(), "",
                   pullHist.GetXaxis()->GetXmin(),
                   pullHist.GetXaxis()->GetXmax());
    RooDataHist pullDH(("pullDH_" + paramName).c_str(), "", RooArgSet(pull),
                       RooFit::Import(pullHist));
    RooRealVar pullMean(("pullMean_" + paramName).c_str(), "", 0, pull.getMin(),
                        pull.getMax());
    RooRealVar pullSigma(("pullSigma_" + paramName).c_str(), "", 1, 0,
                         pull.getMax() - pull.getMin());
    RooGaussian pullGaus(("pullGauss_" + paramName).c_str(), "", pull, pullMean,
                        pullSigma);
    auto pullResult =
        std::unique_ptr<RooFitResult>(pullGaus.fitTo(pullDH, RooFit::Save()));
    pullResult->Print("v");
    std::unique_ptr<RooPlot> pullFrame(pull.frame(RooFit::Title(" ")));
    pullFrame->GetXaxis()->SetTitle((paramName + " Pull").c_str());
    pullDH.plotOn(pullFrame.get());
    pullGaus.plotOn(pullFrame.get(), RooFit::LineColor(kRed), RooFit::LineWidth(2));
    pullDH.plotOn(pullFrame.get());
    varCanvas.cd(3);
    pullFrame->Draw();

    TLegend pullLegend(0.55, 0.78, 0.85, 0.88);
    pullLegend.SetTextSize(0.03);
    pullLegend.SetLineColor(kWhite);
    std::stringstream pullMeanString, pullSigmaString;
    pullMeanString << "#mu = " << to_string_with_precision(pullMean.getVal());
    pullMeanString << " #pm " << to_string_with_precision(pullMean.getPropagatedError(*pullResult.get()));
    pullSigmaString << "#sigma = " << to_string_with_precision(pullSigma.getVal());
    pullSigmaString << " #pm " << to_string_with_precision(pullSigma.getPropagatedError(*pullResult.get()));
    pullLegend.AddEntry(blankHist.get(), pullMeanString.str().c_str(), "l");
    pullLegend.AddEntry(blankHist.get(), pullSigmaString.str().c_str(), "l");
    pullLegend.Draw("same");

    varCanvas.SaveAs((outputDir + "/ValErrPull_" + paramName + ".pdf").c_str());
  }

  std::cout << "\nQuality of fits:\n"
            << "Unconverged: " << nUnConv / resultVec.size() * 100 << " %\n"
            << "Forced positive definite: " << nFPD / resultVec.size() * 100
            << " %\n"
            << "MINOS problems: " << nMINOS / resultVec.size() * 100 << " %\n";

  return 1;
}
