
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "Configuration.h"
#include "Efficiencies.h"
#include "NeutralVars.h"
#include "ParseArguments.h"
#include "RooArgList.h"
#include "RooArgSet.h"
#include "RooDataHist.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TLegend.h"
#include "TPad.h"
#include "TStyle.h"
#include "TTreeReader.h"

std::string to_string_scientific(double value, int precision) {
  std::ostringstream out;
  out << std::scientific << std::setprecision(precision) << value;
  return out.str();
}

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

RooArgList ReturnInitPars(bool dataToy,
                          std::vector<RooFitResult> &dataResultVec,
                          std::vector<RooFitResult> &resultVec, double it) {
  if (dataToy == true) {
    RooArgList initialPars = dataResultVec[it].floatParsFinal();
    return initialPars;
  } else {
    RooArgList initialPars = resultVec[it].floatParsInit();
    return initialPars;
  }
}

void SetStyle() {
  gStyle->SetTitleFont(132, "XYZ");
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLabelFont(132, "XYZ");
  gStyle->SetStatFont(132);
  gStyle->SetStatFontSize(0.04);
  gStyle->SetTitleSize(0.08, "Y");
  gStyle->SetTitleSize(0.08, "X");
  gStyle->SetLabelSize(0.06, "XY");
  gStyle->SetTitleOffset(0.82, "X");
  gStyle->SetTitleOffset(0.93, "Y");
  gStyle->SetPadTopMargin(0.03);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.15);
}

int main(int argc, char *argv[]) {
  Configuration &config = Configuration::Get();
  config.plotToys() = true;
  // For efficiencies
  config.inputDir = "/data/lhcb/users/rollings/data_fit/";
  std::string outputDir;
  std::vector<std::string> resultFiles;
  bool dataToy;
  bool toys2D = false;

  {
    ParseArguments args(argc, argv);

    std::string neutralArg;
    if (!args("neutral", neutralArg)) {
      std::cerr << "Using default value -neutral=[" << neutralArg << "]\n";
    }
    try {
      config.SetNeutral(StringToEnum<Neutral>(neutralArg));
    } catch (std::invalid_argument) {
      std::cerr << "neutral assignment failed, please specify: "
                   "-neutral=[pi0/gamma].\n";
      return 1;
    }

    if (config.neutral() == Neutral::gamma) {
      if (!args("buPartial")) {
      } else {
        config.fitBuPartial() = true;
      }
    }

    if (!args("outputDir", outputDir)) {
      std::cerr << "Specify output directory (-outputDir=<path>).\n";
      return 1;
    }

    std::string toyInitArg;
    if (!args("toyInit", toyInitArg)) {
      std::cerr << "Specify toy starting values (-initToy=<model/data>).\n";
      return 1;
    } else {
      if (toyInitArg == "model") {
        dataToy = false;
      } else if (toyInitArg == "data") {
        dataToy = true;
      } else {
        std::cerr << "-initToy=<model/data>\n";
        return 1;
      }
    }

    if (args("1D")) {
      config.fit1D() = true;
    }

    if (args("2D")) {
      toys2D = true;
      std::cout << "2D toys\n";
    }

    std::string inputFile;
    if (!args("inputFile", inputFile)) {
      std::cerr << "Pass name of file containing comma separated list of root "
                   "files.\n";
      return 1;
    }
    std::ifstream inStream(inputFile);
    std::string tmp;
    int i = 0;
    while (std::getline(inStream, tmp)) {
      resultFiles.emplace_back(tmp);
    }
    inStream.close();
    if (resultFiles.size() < 1) {
      throw std::runtime_error("No results files found\n");
    }
  }

  // Loop over filenames, open the files, then extract the RooFitResults and
  // from each and store in vector
  std::vector<RooFitResult> resultVec;
  std::vector<std::string> rndmVec;
  std::vector<RooFitResult> dataResultVec;

  for (auto &filename : resultFiles) {
    std::string rndm;
    auto file = std::unique_ptr<TFile>(TFile::Open(filename.c_str()));
    if (config.fit1D() == false) {
      if (config.fitBuPartial() == false) {
        std::regex fileRexp(
            ".+_([0-9].+)_([0-9].+)_([0-9].+)_([0-9].+)_([a-z0-9]+).root");
        std::smatch fileMatch;
        if (std::regex_search(filename, fileMatch, fileRexp)) {
          config.SetDeltaLow(std::stod(fileMatch[1]));
          config.SetDeltaHigh(std::stod(fileMatch[2]));
          config.SetBuDeltaLow(std::stod(fileMatch[3]));
          config.SetBuDeltaHigh(std::stod(fileMatch[4]));
          rndm = fileMatch[5];
        } else {
          throw std::runtime_error(
              "Could not find filename opt 1 with correct regex pattern");
        }
      } else {
        std::regex fileRexp(
            ".+_([0-9].+)_([0-9].+)_([0-9].+)_([0-9].+)_([0-9].+)_([0-9].+)_("
            "[a-z0-9]+).root");
        std::smatch fileMatch;
        if (std::regex_search(filename, fileMatch, fileRexp)) {
          config.SetDeltaPartialLow(std::stod(fileMatch[1]));
          config.SetDeltaPartialHigh(std::stod(fileMatch[2]));
          config.SetDeltaLow(std::stod(fileMatch[3]));
          config.SetDeltaHigh(std::stod(fileMatch[4]));
          config.SetBuDeltaLow(std::stod(fileMatch[5]));
          config.SetBuDeltaHigh(std::stod(fileMatch[6]));
          rndm = fileMatch[7];
        } else {
          throw std::runtime_error(
              "Could not find filename opt 2 with correct regex pattern");
        }
      }
    } else {
      if (config.fitBuPartial() == false) {
        std::regex fileRexp(".+_([0-9].+)_([0-9].+)_([a-z0-9]+).root");
        std::smatch fileMatch;
        if (std::regex_search(filename, fileMatch, fileRexp)) {
          config.SetDeltaLow(std::stod(fileMatch[1]));
          config.SetDeltaHigh(std::stod(fileMatch[2]));
          rndm = fileMatch[3];
        } else {
          throw std::runtime_error(
              "Could not find filename opt 3 with correct regex pattern");
        }
      } else {
        std::regex fileRexp(
            ".+_([0-9].+)_([0-9].+)_([0-9].+)_([0-9].+)_([a-z0-9]+).root");
        std::smatch fileMatch;
        if (std::regex_search(filename, fileMatch, fileRexp)) {
          config.SetDeltaPartialLow(std::stod(fileMatch[1]));
          config.SetDeltaPartialHigh(std::stod(fileMatch[2]));
          config.SetDeltaLow(std::stod(fileMatch[3]));
          config.SetDeltaHigh(std::stod(fileMatch[4]));
          rndm = fileMatch[5];
        } else {
          throw std::runtime_error(
              "Could not find filename opt 4 with correct regex pattern");
        }
      }
    }
    auto result = std::unique_ptr<RooFitResult>(
        dynamic_cast<RooFitResult *>(file->FindObjectAny("ToyResult")));
    std::unique_ptr<RooFitResult> dataResult;
    if (result == nullptr) {
      // throw std::runtime_error("Could not extract Result from " +
      // filename);
      continue;
    } else {
      if (dataToy == true) {
        dataResult = std::unique_ptr<RooFitResult>(
            dynamic_cast<RooFitResult *>(file->FindObjectAny("DataFitResult")));
        if (dataResult == nullptr) {
          // throw std::runtime_error("Could not extract DataFitResult from "
          // +
          //                          filename);
          continue;
        } else {
          dataResultVec.emplace_back(*dataResult.get());
        }
      }
      resultVec.emplace_back(*result.get());
      rndmVec.emplace_back(rndm);
    }
  }

  if (resultVec.size() < 1) {
    throw std::runtime_error("No results found.");
  }

  // Create vector of histograms: automatically make histograms for the value,
  RooArgList finalPars0 = resultVec[0].floatParsFinal();
  double nParams = finalPars0.getSize();
  // std::cout << "Number of parameters stored in results = " << nParams <<
  // "\n";

  // Check result quality and print out stats
  double nUnConv = 0;
  double nFPD = 0;
  double nMINOS = 0;
  double nUnchanged = 0;

  // Save values into vectors and set max/min depending on
  // values: one max/min for each parameter (but all results)
  std::map<std::string, double> initValMinMap;  //(nParams, 1000000);
  std::map<std::string, double> initValMaxMap;  //(nParams, -1000000);
  std::map<std::string, double> valMinMap;      //(nParams, 1000000);
  std::map<std::string, double> valMaxMap;      //(nParams, -1000000);
  std::map<std::string, double> errMinMap;      //(nParams, 1000000);
  std::map<std::string, double> errMaxMap;      //(nParams, -1000000);
  std::map<std::string, double> pullMinMap;     //(nParams, 1000000);
  std::map<std::string, double> pullMaxMap;     //(nParams, -1000000);
  // Save initial values for starting point of mean
  std::map<std::string, std::vector<double> > initValMap;
  std::map<std::string, std::vector<double> > valMap;
  std::map<std::string, std::vector<double> > errMap;
  std::map<std::string, std::vector<std::pair<std::string, double> > > pullMap;

  RooAbsArg *initialAbsArg = nullptr;
  RooRealVar *initialRealVar = nullptr;
  RooAbsArg *finalAbsArg = nullptr;
  RooRealVar *finalRealVar = nullptr;

  std::cout << "Number of results saved = " << resultVec.size() << "\n";
  std::vector<std::string> rndmStore;

  for (double j = 0; j < resultVec.size(); ++j) {
    // std::cout << "\nResult " << rndmVec[j] << "\n\n\n";
    // Check quality of result
    // double edm = resultVec[j].edm();
    double fitStatus = resultVec[j].status();
    double covQual = resultVec[j].covQual();
    if (covQual < 2) {
      std::cout << "Unconverged: " << rndmVec[j] << std::endl;
      nUnConv++;
      continue;
    }
    if (covQual < 3) {
      std::cout << "FPD: " << rndmVec[j] << std::endl;
      nFPD++;
      continue;
    }
    if (fitStatus != 0) {
      std::cout << "MINOS issues: " << rndmVec[j] << std::endl;
      nMINOS++;
      continue;
    }
    if (covQual >= 3 && fitStatus == 0) {
      RooArgList initialPars =
          ReturnInitPars(dataToy, dataResultVec, resultVec, j);
      RooArgList finalPars = resultVec[j].floatParsFinal();
      // Loop over each parameter in result
      for (double i = 0; i < nParams; ++i) {
        RooAbsArg* initPar = initialPars.at(i);
        if (initPar == nullptr) {
          std::cout << "initPar returns nullptr: skip result " << rndmVec[j] <<  "\n";
          continue;
        }
        std::string fullName = initPar->GetName();
        // std::cout << "Full parameter name = " << fullName << "\n";
        std::regex rexp("([A-Za-z0-9_]+)_[0-9]+");
        std::smatch match;
        std::regex_search(fullName, match, rexp);
        std::string paramName = match[1];

        if (initValMap.find(paramName) == initValMap.end()) {
          initValMap.emplace(std::piecewise_construct,
                             std::make_tuple(paramName), std::make_tuple());
        }
        if (initValMaxMap.find(paramName) == initValMaxMap.end()) {
          initValMaxMap.emplace(std::piecewise_construct,
                                std::make_tuple(paramName),
                                std::make_tuple(-1000000));
        }
        if (initValMinMap.find(paramName) == initValMinMap.end()) {
          initValMinMap.emplace(std::piecewise_construct,
                                std::make_tuple(paramName),
                                std::make_tuple(10000000));
        }
        if (valMap.find(paramName) == valMap.end()) {
          valMap.emplace(std::piecewise_construct, std::make_tuple(paramName),
                         std::make_tuple());
        }
        if (valMaxMap.find(paramName) == valMaxMap.end()) {
          valMaxMap.emplace(std::piecewise_construct,
                            std::make_tuple(paramName),
                            std::make_tuple(-10000000));
        }
        if (valMinMap.find(paramName) == valMinMap.end()) {
          valMinMap.emplace(std::piecewise_construct,
                            std::make_tuple(paramName),
                            std::make_tuple(10000000));
        }
        if (errMap.find(paramName) == errMap.end()) {
          errMap.emplace(std::piecewise_construct, std::make_tuple(paramName),
                         std::make_tuple());
        }
        if (errMaxMap.find(paramName) == errMaxMap.end()) {
          errMaxMap.emplace(std::piecewise_construct,
                            std::make_tuple(paramName),
                            std::make_tuple(-10000000));
        }
        if (errMinMap.find(paramName) == errMinMap.end()) {
          errMinMap.emplace(std::piecewise_construct,
                            std::make_tuple(paramName),
                            std::make_tuple(10000000));
        }
        if (pullMap.find(paramName) == pullMap.end()) {
          pullMap.emplace(std::piecewise_construct, std::make_tuple(paramName), 
                          std::make_tuple());
        }
        if (pullMaxMap.find(paramName) == pullMaxMap.end()) {
          pullMaxMap.emplace(std::piecewise_construct,
                             std::make_tuple(paramName),
                             std::make_tuple(-10000000));
        }
        if (pullMinMap.find(paramName) == pullMinMap.end()) {
          pullMinMap.emplace(std::piecewise_construct,
                             std::make_tuple(paramName),
                             std::make_tuple(10000000));
        }

        initialAbsArg = initialPars.find(initialPars.at(i)->GetName());
        initialRealVar = dynamic_cast<RooRealVar *>(initialAbsArg);
        finalAbsArg = finalPars.find(finalPars.at(i)->GetName());
        finalRealVar = dynamic_cast<RooRealVar *>(finalAbsArg);

        double initialVal = initialRealVar->getVal();
        double finalVal = finalRealVar->getVal();
        double finalErr, pull;
        if (finalRealVar->hasAsymError()) {
          if (finalVal <= initialVal) {
            finalErr = finalRealVar->getErrorHi();
            pull = (finalVal - initialVal) / finalErr;
          } else {
            finalErr = finalRealVar->getErrorLo();
            pull = (initialVal - finalVal) / finalErr;
          }
        } else {
          finalErr = finalRealVar->getError();
          pull = (finalVal - initialVal) / finalErr;
        }
        // if ((config.neutral() == Neutral::pi0 &&
        //      paramName == "R_Dst0KDst0pi_Bu2Dst0h_D0pi0_kpi") &&
        //     pull > 3) {
        //   rndmStore.emplace_back(rndmVec[j]);
        // }
        // if (i == 0) {
        //   if (initialVal == finalVal) {
        //     std::cout << "initVal == finalVal for result " << rndmVec[j]
        //               << "\n";
        //     break;
        //   }
        // } else {
        //   std::cout << "initialVal = " << initialVal
        //             << "\tfinalVal = " << finalVal
        //             << "\tfinalErr = " << finalErr << "\tpull = " << pull
        //             << "\n";
        //   if (pull == 0.) {
        //     std::cout << "Pull == 0 for result " << rndmVec[j] << "\n";
        //   }
        // }
        // Fill histograms
        initValMap[paramName].emplace_back(initialVal);
        // valMap[paramName].emplace_back(finalVal - initialVal);
        valMap[paramName].emplace_back(finalVal);
        errMap[paramName].emplace_back(finalErr);
        pullMap[paramName].emplace_back(std::make_pair(rndmVec[j], pull));
        // std::cout << initilPars.at(i)->GetName()
        //           << "\tInital Val = " << initialVal
        //           << "\tFinal Val = " << finalVal << "\tErr = " << finalErr
        //           << "\tPull = " << pull << "\n";

        if (initialVal > initValMaxMap[paramName]) {
          initValMaxMap[paramName] = initialVal;
        }
        if (initialVal < initValMinMap[paramName]) {
          initValMinMap[paramName] = initialVal;
        }
        if (finalVal > valMaxMap[paramName]) {
          valMaxMap[paramName] = finalVal;
        }
        if (finalVal < valMinMap[paramName]) {
          valMinMap[paramName] = finalVal;
        }
        if (finalErr > errMaxMap[paramName]) {
          errMaxMap[paramName] = finalErr;
        }
        if (finalErr < errMinMap[paramName]) {
          errMinMap[paramName] = finalErr;
        }
        if (pull > pullMaxMap[paramName]) {
          pullMaxMap[paramName] = pull;
        }
        if (pull < pullMinMap[paramName]) {
          pullMinMap[paramName] = pull;
        }
      }
    }
  }

  // File to save results
  TFile outputFile(
      (outputDir + "/results/Result_" + config.ReturnBoxString() + ".root")
          .c_str(),
      "recreate");
  TTree tree("tree", "");
  if (config.neutral() == Neutral::pi0 || config.fitBuPartial() == true) {
    SaveEffToTree(config, outputFile, tree, Mode::Bu2Dst0pi_D0pi0);
  }
  if (config.neutral() == Neutral::gamma) {
    SaveEffToTree(config, outputFile, tree, Mode::Bu2Dst0pi_D0gamma);
  }
  outputFile.cd();
  tree.Write();

  SetStyle();

  // Loop over params, create histogram for each and fill with values from
  // result
  for (double i = 0; i < nParams; ++i) {
    // Extract parameter names using regular expression in order to remove _#
    std::string fullName = finalPars0.at(i)->GetName();
    // std::cout << "Full parameter name = " << fullName << "\n";
    std::regex rexp("([A-Za-z0-9_]+)_[0-9]+");
    std::smatch match;
    std::regex_search(fullName, match, rexp);
    std::string paramName = match[1];
    // std::cout << "After regex, parameter name = " << paramName << "\n";

    double initValRange = initValMaxMap[paramName] - initValMinMap[paramName];
    TH1D initValHist(("initValHist_" + paramName).c_str(), "", 50,
                     initValMinMap[paramName] - initValRange / 5,
                     initValMaxMap[paramName] + initValRange / 5);
    double valRange = valMaxMap[paramName] - valMinMap[paramName];
    // TH1D valHist(("valHist_" + paramName).c_str(), "",
    // round(resultVec.size()/20),
    TH1D valHist(("valHist_" + paramName).c_str(), "", 50,
                 valMinMap[paramName] - valRange / 5,
                 valMaxMap[paramName] + valRange / 5);
    double errRange = errMaxMap[paramName] - errMinMap[paramName];
    // TH1D errHist(("errHist_" + paramName).c_str(), "",
    // round(resultVec.size()/20),
    TH1D errHist(("errHist_" + paramName).c_str(), "", 50,
                 errMinMap[paramName] - errRange / 5,
                 errMaxMap[paramName] + errRange / 5);
    double pullRange = pullMaxMap[paramName] - pullMinMap[paramName];
    // TH1D pullHist(("pullHist_" + paramName).c_str(), "", 50,
    //               // round(resultVec.size()/10),
    //               pullMinMap[paramName] - pullRange / 5, pullMaxMap[paramName] +
    //               pullRange / 5);
    // TH1D pullHist(("pullHist_" + paramName).c_str(), "", 50, -10, 10);
    TH1D pullHist(("pullHist_" + paramName).c_str(), "", 50, -6, 6);
    // if (toys2D == true) {
    // pullHist.GetXaxis()->SetLimits(-10, 10);
    // }
    // for (double j = 0; j < round(resultVec.size() / 5); ++j) {
    std::cout << "pullVec = " << pullMap[paramName].size() << "\n";

    if (paramName == "bkgFracADS_Bs2Dst0Kpi_pi0") {
      std::cout << "HERE WE GO\n";
    }
    for (double j = 0; j < initValMap[paramName].size(); ++j) {
      initValHist.Fill(initValMap[paramName][j]);
      valHist.Fill(valMap[paramName][j]);
      errHist.Fill(errMap[paramName][j]);
      pullHist.Fill(pullMap[paramName][j].second);
      if (paramName == "bkgFracADS_Bs2Dst0Kpi_pi0" &&
          pullMap[paramName][j].second > 1.0) {
        std::cout << pullMap[paramName][j].second << "\t";
        std::cout << pullMap[paramName][j].first << "\n";
      }
    }
    int binMax = pullHist.GetMaximumBin();
    int maxContent = pullHist.GetBinContent(pullHist.GetMaximumBin());
    double maxPull = pullHist.GetXaxis()->GetBinCenter(binMax);
    double minBin = pullHist.GetXaxis()->GetBinLowEdge(binMax);
    double maxBin = pullHist.GetXaxis()->GetBinUpEdge(binMax);
    std::cout << "\n ----- \n";
    std::cout << paramName << "\t";
    std::cout << binMax << "\t" << maxContent << "\t" << maxPull << " ("
              << minBin << ", " << maxBin << ")\t" << pullHist.Integral();
    std::cout << "\n ----- \n";

    // Create RRVs for each parameter's value, error and pull
    // Make into function and pass relevant histogram

    TCanvas pullCanvas((paramName + "Canvas").c_str(), " ", 1200, 1000);

    // if (config.blindFit() == false) {
    //   varCanvas.SetCanvasSize(1500, 500);
    //   varCanvas.Divide(3, 1);
    //   varCanvas.cd(1);
    // }

    RooRealVar pull(("pull_" + paramName).c_str(), "",
                    pullHist.GetXaxis()->GetXmin(),
                    pullHist.GetXaxis()->GetXmax());
    RooDataHist pullDH(("pullDH_" + paramName).c_str(), "", RooArgSet(pull),
                       RooFit::Import(pullHist));
    RooRealVar pullMean(("pullMean_" + paramName).c_str(), "",  // 0,
                        pull.getMin() - (pull.getMax() - pull.getMin()),
                        pull.getMax() + (pull.getMax() - pull.getMin()));
    RooRealVar pullSigma(("pullSigma_" + paramName).c_str(), "", 1, 0,
                         pull.getMax() - pull.getMin());
    RooGaussian pullGaus(("pullGauss_" + paramName).c_str(), "", pull, pullMean,
                         pullSigma);

    std::unique_ptr<RooFitResult> pullResult;
    pull.setRange("full", -6, 6);
    if (toys2D == true && (paramName == "R_piK_Bu2Dst0h_D0pi0_Blind_k_total" ||
                           paramName == "R_piK_Bu2Dst0h_D0pi0_Blind_k_minus")) {
      pull.setRange("fit", -4, 4);
      pullResult = std::unique_ptr<RooFitResult>(
          pullGaus.fitTo(pullDH, RooFit::Range("fit"), RooFit::Save()));
    } else {
      pullResult =
          std::unique_ptr<RooFitResult>(pullGaus.fitTo(pullDH, RooFit::Save()));
    }
    pullResult->Print("v");
    pullResult->SetName(("Result_Pull_" + paramName).c_str());
    pullResult->Write();

    gStyle->SetLabelSize(0.06, "X");
    std::unique_ptr<RooPlot> pullFrame;
    // if (toys2D == true) {
    //   Double_t xMin = pullMean.getVal() - 6.0;
    //   Double_t xMax = pullMean.getVal() + 6.0;
    //   pullFrame = std::unique_ptr<RooPlot>(pull.frame(xMin, xMax, pullHist.GetNbinsX()));
      // pullFrame->SetLabelOffset(50, "X");
      // pullFrame->GetXaxis()->SetTickLength(0.);
      // std::cout << "Attempt: \tSet min: " << xMin << "\t"
      //           << "Set max: " << xMax << "\n";
      // double x_min = pullFrame->GetXaxis()->GetXmin();
      // double x_max = pullFrame->GetXaxis()->GetXmax();
      // std::cout << "Actual: \tSet min: " << x_min << "\t"
      //           << "Set max: " << x_max << "\n";
    // } else {
    pullFrame = std::unique_ptr<RooPlot>(pull.frame(RooFit::Title(" ")));
    pullFrame->SetTitle(" ");
    // }
    pullFrame->GetXaxis()->SetTitle((ReturnLaTeXLabel(paramName) + " pull").c_str());
    std::stringstream yLabel;
    // yLabel << "Number of toys / (" << pullHist.GetXaxis()->GetBinWidth(0) << ")";
    pullFrame->GetYaxis()->SetTitle("Number of toys");
    pullDH.plotOn(pullFrame.get());
    pullGaus.plotOn(pullFrame.get(), RooFit::LineColor(kRed+1),
                    RooFit::LineWidth(3), RooFit::Range("full"));
    pullDH.plotOn(pullFrame.get());
    pullFrame->Draw();

    auto blankHist = std::make_unique<TH1D>("blankHist", "", 1, 0, 1);
    blankHist->SetLineColor(kWhite);
    TLegend pullLegend(0.49, 0.84, 0.95, 0.965);
    // if (config.blindFit() == false) {
    //   pullLegend.SetX1(0.5);
    //   pullLegend.SetX2(0.85);
    // }
    pullLegend.SetFillColor(-1);
    pullLegend.SetFillStyle(4000);
    gStyle->SetStatStyle(0);
    gStyle->SetTitleStyle(0);
    pullLegend.SetTextSize(0.055);
    pullLegend.SetLineColor(-1);
    std::ostringstream pullMeanString, pullSigmaString;
    pullMeanString << "#mu = " << to_string_with_precision(pullMean.getVal(), 3);
    pullMeanString << " #pm "
                   << to_string_with_precision(
                          pullMean.getPropagatedError(*pullResult.get()), 3);
    pullSigmaString << "#sigma = "
                    << to_string_with_precision(pullSigma.getVal(), 3);
    pullSigmaString << " #pm "
                    << to_string_with_precision(
                           pullSigma.getPropagatedError(*pullResult.get()), 3);
    pullLegend.AddEntry(blankHist.get(), pullMeanString.str().c_str(), "l");
    pullLegend.AddEntry(blankHist.get(), pullSigmaString.str().c_str(), "l");
    pullLegend.Draw("same");
    pullCanvas.SaveAs((outputDir + "/plots/" + config.ReturnBoxString() + "_" +
                      paramName + "_Pull.pdf")
                         .c_str());

    TCanvas valCanvas((paramName + "Canvas").c_str(), " ", 1200, 1000);
    // // Initialise frame and legend outside of if satement so that pointer exists
    // // outside scope (or not plotted)
    RooRealVar val(("val_" + paramName).c_str(), "",
                   valHist.GetXaxis()->GetXmin(),
                   valHist.GetXaxis()->GetXmax());
    // std::unique_ptr<RooPlot> valFrame(val.frame(RooFit::Title(" ")));
    // TLegend valLegend(0.5, 0.78, 0.85, 0.88);
    //
    RooRealVar err(("err_" + paramName).c_str(), "",
                   errHist.GetXaxis()->GetXmin(),
                   errHist.GetXaxis()->GetXmax());
    // std::unique_ptr<RooPlot> errFrame(err.frame(RooFit::Title(" ")));
    // TLegend errLegend(0.5, 0.78, 0.85, 0.88);
    //
  //   if (toys2D == true || config.blindFit() == false) {
  //     std::cout << "VAL AND ERR TOO\n";
    RooDataHist valDH(("valDH_" + paramName).c_str(), "", RooArgSet(val),
                      RooFit::Import(valHist));
    RooRealVar valMean(("valMean_" + paramName).c_str(), "",
                       val.getMin() - (val.getMax() - val.getMin()),
                       val.getMax() + (val.getMax() - val.getMin()));
    RooRealVar valSigma(("valSigma_" + paramName).c_str(), "",
                        (val.getMax() - val.getMin()) / 5, 0,
                        val.getMax() - val.getMin());
    RooGaussian valGaus(("valGauss_" + paramName).c_str(), "", val, valMean,
                        valSigma);
    auto valResult =
        std::unique_ptr<RooFitResult>(valGaus.fitTo(valDH, RooFit::Save()));
    valResult->Print("v");
    valResult->SetName(("Result_Val_" + paramName).c_str());
    valResult->Write();

    val.setMax(valMean.getVal() + valSigma.getVal() * 5);
    val.setMin(valMean.getVal() -valSigma.getVal() * 5);
    gStyle->SetLabelSize(0.05, "X");
    auto valFrame = std::unique_ptr<RooPlot>(val.frame(RooFit::Title(" ")));
    valFrame->SetTitle(" ");
    // }
    valFrame->GetXaxis()->SetTitle(ReturnLaTeXLabel(paramName).c_str());
    // valFrame->GetXaxis()->SetMaxDigits(2);
    valFrame->GetXaxis()->SetNdivisions(8);
    // valFrame->SetLabelOffset(50, "X");
    // valFrame->GetXaxis()->SetTickLength(0.);
    std::stringstream yLabel_val;
    valFrame->GetYaxis()->SetTitle("Number of toys");
    valDH.plotOn(valFrame.get());
    valGaus.plotOn(valFrame.get(), RooFit::LineColor(kRed + 1),
                   RooFit::LineWidth(3));
    valDH.plotOn(valFrame.get());
    valFrame->GetXaxis()->SetRangeUser(valMean.getVal() - valSigma.getVal() * 5,
                                       valMean.getVal() + valSigma.getVal() * 5);
    valFrame->Draw();

    // TLegend valLegend(0.49, 0.84, 0.95, 0.965);
    TLegend valLegend(0.46, 0.915, 0.95, 0.975);
    // if (config.blindFit() == false) {
    //   valLegend.SetX1(0.5);
    //   valLegend.SetX2(0.85);
    // }
    valLegend.SetFillColor(-1);
    valLegend.SetFillStyle(4000);
    gStyle->SetStatStyle(0);
    gStyle->SetTitleStyle(0);
    valLegend.SetTextSize(0.055);
    valLegend.SetLineColor(-1);
    std::ostringstream valMeanString, valSigmaString;
    // valMeanString << "#mu = " << to_string_scientific(valMean.getVal(), 2);
    // valMeanString << " #pm "
    //                << to_string_scientific(
    //                       valMean.getPropagatedError(*valResult.get()), 2);
    valSigmaString << "#sigma = "
                    << to_string_with_precision(valSigma.getVal(), 4);
    valSigmaString << " #pm "
                    << to_string_with_precision(
                           valSigma.getPropagatedError(*valResult.get()), 4);
    valLegend.AddEntry(blankHist.get(), valMeanString.str().c_str(), "l");
    valLegend.AddEntry(blankHist.get(), valSigmaString.str().c_str(), "l");
    valLegend.Draw("same");
    valCanvas.SaveAs((outputDir + "/plots/" + config.ReturnBoxString() + "_" +
                      paramName + "_Val.pdf")
                         .c_str());

  //
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
      errResult->SetName(("Result_Err_" + paramName).c_str());
      errResult->Write();
  //     errFrame->GetXaxis()->SetTitle((paramName + " Error").c_str());
  //     errDH.plotOn(errFrame.get());
  //     errGaus.plotOn(errFrame.get(), RooFit::LineColor(kRed),
  //                    RooFit::LineWidth(2));
  //     errDH.plotOn(errFrame.get());
  //     varCanvas.cd(3);
  //     errFrame->Draw();
  //
  //     errLegend.SetTextSize(0.03);
  //     errLegend.SetLineColor(kWhite);
  //     std::stringstream errMeanString, errSigmaString;
  //     errMeanString << "#mu = " << to_string_with_precision(errMean.getVal());
  //     errMeanString << " #pm "
  //                   << to_string_with_precision(
  //                          errMean.getPropagatedError(*errResult.get()));
  //     errSigmaString << "#sigma = "
  //                    << to_string_with_precision(errSigma.getVal());
  //     errSigmaString << " #pm "
  //                    << to_string_with_precision(
  //                           errSigma.getPropagatedError(*errResult.get()));
  //     errLegend.AddEntry(blankHist.get(), errMeanString.str().c_str(), "l");
  //     errLegend.AddEntry(blankHist.get(), errSigmaString.str().c_str(), "l");
  //     errLegend.Draw("same");
  //   }

  }

  outputFile.Write();
  outputFile.Close();
  std::cout << "Number of toys: " << resultVec.size() << "\n";

  std::cout << "\nQuality of fits:\n"
            << "Unconverged: " << nUnConv / resultVec.size() * 100 << " %\n"
            << "# Unconverged: " << nUnConv << "\n"
            << "Forced positive definite: " << nFPD / resultVec.size() * 100
            << " %\n"
            << "# Forced positive definite: " << nFPD << "\n"
            << "MINOS problems: " << nMINOS / resultVec.size() * 100 << " %\n"
            << "# MINOS problems: " << nMINOS << "\n";
  for (auto &seed : rndmStore) {
    std::cout << seed << "\n";
  }

  return 1;
}
