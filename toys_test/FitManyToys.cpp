#include <fstream>
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
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

enum class Mode {
  Bd2Dstpi,
  Bu2D0pi,
  Bu2D0rho,
  Bu2Dst0pi_D0gamma,
  Bu2Dst0pi_D0pi0,
  Bu2Dst0rho_D0gamma,
  Bu2Dst0rho_D0pi0
};

std::string EnumToString(Mode mode) {
  switch (mode) {
    case Mode::Bd2Dstpi:
      return "Bd2Dstpi";
      break;
    case Mode::Bu2D0pi:
      return "Bu2D0pi";
      break;
    case Mode::Bu2D0rho:
      return "Bu2D0rho";
      break;
    case Mode::Bu2Dst0pi_D0gamma:
      return "Bu2Dst0pi_D0gamma";
      break;
    case Mode::Bu2Dst0pi_D0pi0:
      return "Bu2Dst0pi_D0pi0";
      break;
    case Mode::Bu2Dst0rho_D0gamma:
      return "Bu2Dst0rho_D0gamma";
      break;
    case Mode::Bu2Dst0rho_D0pi0:
      return "Bu2Dst0rho_D0pi0";
  }
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

std::string to_string_with_precision(double value) {
  std::ostringstream out;
  out << std::setprecision(3) << value;
  return out.str();
}

void ExtractBoxEfficiencies(Mode mode, std::string const &box_delta_low,
                            std::string const &box_delta_high,
                            std::string const &box_bu_low,
                            std::string const &box_bu_high, double &boxEff,
                            double &orEff) {
  std::string inputfile_1(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2011_MagUp/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2011_MagUp_BDT1_BDT2_PID_buDelta_TM.root");
  std::string inputfile_2(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2011_MagDown/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2011_MagDown_BDT1_BDT2_PID_buDelta_TM.root");
  std::string inputfile_3(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2012_MagUp/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2012_MagUp_BDT1_BDT2_PID_buDelta_TM.root");
  std::string inputfile_4(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2012_MagDown/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2012_MagDown_BDT1_BDT2_PID_buDelta_TM.root");
  std::string inputfile_5(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2015_MagUp/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2015_MagUp_BDT1_BDT2_PID_buDelta_TM.root");
  std::string inputfile_6(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2015_MagDown/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2015_MagDown_BDT1_BDT2_PID_buDelta_TM.root");
  std::string inputfile_7(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2016_MagUp/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2016_MagUp_BDT1_BDT2_PID_buDelta_TM.root");
  std::string inputfile_8(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2016_MagDown/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2016_MagDown_BDT1_BDT2_PID_buDelta_TM.root");
  std::string ttree("BtoDstar0h3_h1h2gammaTuple");

  TChain chain(ttree.c_str());

  chain.Add(inputfile_1.c_str());
  chain.Add(inputfile_2.c_str());
  chain.Add(inputfile_3.c_str());
  chain.Add(inputfile_4.c_str());
  chain.Add(inputfile_5.c_str());
  chain.Add(inputfile_6.c_str());
  chain.Add(inputfile_7.c_str());
  chain.Add(inputfile_8.c_str());

  if (mode != Mode::Bu2Dst0pi_D0pi0 && mode != Mode::Bu2Dst0pi_D0gamma) {
    std::string inputfile_9(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
        "_2015_MagUp/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
        "cross_feed_removed/" +
        EnumToString(mode) + "_2015_MagUp_BDT1_BDT2_PID_buDelta_TM.root");
    std::string inputfile_10(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
        "_ReDecay_2015_MagDown/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
        "cross_feed_removed/" +
        EnumToString(mode) +
        "_ReDecay_2015_MagDown_BDT1_BDT2_PID_buDelta_TM.root");
    std::string inputfile_11(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
        "_ReDecay_2016_MagUp/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
        "cross_feed_removed/" +
        EnumToString(mode) +
        "_ReDecay_2016_MagUp_BDT1_BDT2_PID_buDelta_TM.root");
    std::string inputfile_12(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
        "_ReDecay_2016_MagDown/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
        "cross_feed_removed/" +
        EnumToString(mode) +
        "_ReDecay_2016_MagDown_BDT1_BDT2_PID_buDelta_TM.root");
    chain.Add(inputfile_9.c_str());
    chain.Add(inputfile_10.c_str());
    chain.Add(inputfile_11.c_str());
    chain.Add(inputfile_12.c_str());
  }

  chain.GetEntry(0);

  TTreeReader reader(&chain);

  TTreeReaderValue<double> Bu_Delta_M(reader, "Bu_Delta_M");
  TTreeReaderValue<double> Delta_M(reader, "Delta_M");

  double nInitial = chain.GetEntries(
      "BDT1>0.05&&BDT2>0.05&&Delta_M>50&&Delta_M<210&&Bu_M_DTF_D0>5050&&Bu_M_"
      "DTF_D0<5800");
  double nBox = chain.GetEntries(
      ("BDT1>0.05&&BDT2>0.05&&Delta_M>50&&Delta_M<210&&Bu_M_DTF_D0>5050&&Bu_M_"
       "DTF_D0<5800&&Delta_M>" +
       box_delta_low + "&&Delta_M<" + box_delta_high + "&&Bu_Delta_M>" +
       box_bu_low + "&&Bu_Delta_M<" + box_bu_high)
          .c_str());
  double nOr = chain.GetEntries(
      ("BDT1>0.05&&BDT2>0.05&&Delta_M>50&&Delta_M<210&&Bu_M_DTF_D0>5050&&Bu_M_"
       "DTF_D0<5800&&((Delta_M>" +
       box_delta_low + "&&Delta_M<" + box_delta_high + ")||(Bu_Delta_M>" +
       box_bu_low + "&&Bu_Delta_M<" + box_bu_high + "))")
          .c_str());

  boxEff = nBox / nInitial;
  orEff = nOr / nInitial;

  std::cout << "Set efficiencies :\n"
            << "\tBox =\t" << nBox / nInitial << "\n"
            << "\tDelta OR Bu =\t" << nOr / nInitial << "\n";
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Pass comma separated string of filenames storing "
                 "RooFitResults and output directory.\n";
    return 1;
  }
  std::vector<std::string> resultFiles = SplitByComma(argv[1]);
  std::cout << resultFiles.size();
  std::string outputDir = argv[2];

  // Loop over filenames, open the files, then extract the RooFitResults and
  // from each and store in vector
  std::vector<RooFitResult> resultVec;
  std::string deltaLow, deltaHigh, buLow, buHigh;

  for (auto &filename : resultFiles) {
    auto file = std::unique_ptr<TFile>(TFile::Open(filename.c_str()));
    std::regex fileRexp(
        ".+_([0-9].[0-9]+)_([0-9]+)_([0-9]+)_([0-9]+)_([0-9]+).root");
    std::smatch fileMatch;
    std::regex_search(filename, fileMatch, fileRexp);
    std::string rndm = fileMatch[1];
    deltaLow = fileMatch[2];
    deltaHigh = fileMatch[3];
    buLow = fileMatch[4];
    buHigh = fileMatch[5];
    auto result = std::unique_ptr<RooFitResult>(dynamic_cast<RooFitResult *>(
        file->FindObjectAny(("Result_" + rndm).c_str())));
    if (result == nullptr) {
      throw std::runtime_error("Could not extract Result from " + filename);
    } else {
      resultVec.emplace_back(*result.get());
      // std::cout << "Extracted Result from " << filename << "\n";
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
  std::vector<double> initValMin(nParams, 1000000);
  std::vector<double> initValMax(nParams, -1000000);
  std::vector<double> valMin(nParams, 1000000);
  std::vector<double> valMax(nParams, -1000000);
  std::vector<double> errMin(nParams, 1000000);
  std::vector<double> errMax(nParams, -1000000);
  std::vector<double> pullMin(nParams, 1000000);
  std::vector<double> pullMax(nParams, -1000000);
  // Save initial values for starting point of mean
  std::vector<double> initialVec(nParams);
  std::vector<std::vector<double> > initValVec(resultVec.size(),
                                               std::vector<double>(nParams));
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
        initValVec[j][i] = initialVal;
        valVec[j][i] = finalVal;
        errVec[j][i] = finalErr;
        pullVec[j][i] = pull;
        std::cout << initialPars.at(i)->GetName()
                  << "\tInital Val = " << initialVal
                  << "\tFinal Val = " << finalVal << "\tErr = " << finalErr
                  << "\tPull = " << pull << "\n";

        if (initialVal > initValMax[i]) {
          initValMax[i] = initialVal;
        }
        if (initialVal < initValMin[i]) {
          initValMin[i] = initialVal;
        }
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
  // Extract box efficiencies for calulcations with toys
  double boxEffSignal, orEffSignal;

  ExtractBoxEfficiencies(Mode::Bu2Dst0pi_D0gamma, deltaLow, deltaHigh,
                         buLow, buHigh, boxEffSignal, orEffSignal);

  // File to save results
  TFile outputFile((outputDir + "/results/Result_" + deltaLow + "_" +
                    deltaHigh + "_" + buLow + "_" + buHigh + ".root")
                       .c_str(),
                   "recreate");
  outputFile.cd();
  TTree tree("tree", "");
  tree.Branch("orEffSignal", &orEffSignal, "orEffSignal/D");
  tree.Branch("boxEffSignal", &boxEffSignal, "boxEffSignal/D");
  tree.Fill();
  tree.Write();

  // Loop over params, create histogram for each and fill with values from
  // result
  for (double i = 0; i < nParams; ++i) {
    // Extract parameter names using regular expression in order to remove _#
    std::string fullName = initialPars0.at(i)->GetName();
    // std::cout << "Full parameter name = " << fullName << "\n";
    std::regex rexp("([A-Za-z0-9]+)_[0-9]+");
    std::smatch match;
    std::regex_search(fullName, match, rexp);
    std::string paramName = match[1];
    // std::cout << "After regex, parameter name = " << paramName << "\n";

    double initValRange = initValMax[i] - initValMin[i];
    // TH1D initValHist(("initValHist_" + paramName).c_str(), "",
    // round(resultVec.size()/20),
    TH1D initValHist(("initValHist_" + paramName).c_str(), "", 50,
                     initValMin[i] - initValRange / 5,
                     initValMax[i] + initValRange / 5);
    double valRange = valMax[i] - valMin[i];
    // TH1D valHist(("valHist_" + paramName).c_str(), "",
    // round(resultVec.size()/20),
    TH1D valHist(("valHist_" + paramName).c_str(), "", 50,
                 valMin[i] - valRange / 5, valMax[i] + valRange / 5);
    double errRange = errMax[i] - errMin[i];
    // TH1D errHist(("errHist_" + paramName).c_str(), "",
    // round(resultVec.size()/20),
    TH1D errHist(("errHist_" + paramName).c_str(), "", 50,
                 errMin[i] - errRange / 5, errMax[i] + errRange / 5);
    // double pullRange = pullMax[i] - pullMin[i];
    // TH1D pullHist(("pullHist_" + paramName).c_str(), "",
    // round(resultVec.size()/10),
    //              pullMin[i] - pullRange/5, pullMax[i] + pullRange/5);
    TH1D pullHist(("pullHist_" + paramName).c_str(), "", 50, -5, 5);
    for (double j = 0; j < round(resultVec.size() / 5); ++j) {
      initValHist.Fill(initValVec[j][i]);
      valHist.Fill(valVec[j][i]);
      errHist.Fill(errVec[j][i]);
      pullHist.Fill(pullVec[j][i]);
    }
    TCanvas initValCanvas((paramName + "Canvas").c_str(), " ", 1500, 500);
    initValHist.GetXaxis()->SetTitle(paramName.c_str());
    initValHist.Draw();
    initValCanvas.SaveAs((outputDir + "/plots/" + deltaLow + "_" + deltaHigh +
                          "_" + buLow + "_" + buHigh + "_" + paramName +
                          "_initVal.pdf")
                             .c_str());

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
    valResult->SetName(("Result_Val_" + paramName).c_str());
    valResult->Write();
    std::unique_ptr<RooPlot> valFrame(val.frame(RooFit::Title(" ")));
    valFrame->GetXaxis()->SetTitle(paramName.c_str());
    valDH.plotOn(valFrame.get());
    valGaus.plotOn(valFrame.get(), RooFit::LineColor(kRed),
                   RooFit::LineWidth(2));
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
    valMeanString << " #pm "
                  << to_string_with_precision(
                         valMean.getPropagatedError(*valResult.get()));
    valSigmaString << "#sigma = "
                   << to_string_with_precision(valSigma.getVal());
    valSigmaString << " #pm "
                   << to_string_with_precision(
                          valSigma.getPropagatedError(*valResult.get()));
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
    errResult->SetName(("Result_Err_" + paramName).c_str());
    errResult->Write();
    std::unique_ptr<RooPlot> errFrame(err.frame(RooFit::Title(" ")));
    errFrame->GetXaxis()->SetTitle((paramName + " Error").c_str());
    errDH.plotOn(errFrame.get());
    errGaus.plotOn(errFrame.get(), RooFit::LineColor(kRed),
                   RooFit::LineWidth(2));
    errDH.plotOn(errFrame.get());
    varCanvas.cd(2);
    errFrame->Draw();

    TLegend errLegend(0.5, 0.78, 0.85, 0.88);
    errLegend.SetTextSize(0.03);
    errLegend.SetLineColor(kWhite);
    std::stringstream errMeanString, errSigmaString;
    errMeanString << "#mu = " << to_string_with_precision(errMean.getVal());
    errMeanString << " #pm "
                  << to_string_with_precision(
                         errMean.getPropagatedError(*errResult.get()));
    errSigmaString << "#sigma = "
                   << to_string_with_precision(errSigma.getVal());
    errSigmaString << " #pm "
                   << to_string_with_precision(
                          errSigma.getPropagatedError(*errResult.get()));
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
    pullResult->SetName(("Result_Pull_" + paramName).c_str());
    pullResult->Write();
    std::unique_ptr<RooPlot> pullFrame(pull.frame(RooFit::Title(" ")));
    pullFrame->GetXaxis()->SetTitle((paramName + " Pull").c_str());
    pullDH.plotOn(pullFrame.get());
    pullGaus.plotOn(pullFrame.get(), RooFit::LineColor(kRed),
                    RooFit::LineWidth(2));
    pullDH.plotOn(pullFrame.get());
    varCanvas.cd(3);
    pullFrame->Draw();

    TLegend pullLegend(0.55, 0.78, 0.85, 0.88);
    pullLegend.SetTextSize(0.03);
    pullLegend.SetLineColor(kWhite);
    std::stringstream pullMeanString, pullSigmaString;
    pullMeanString << "#mu = " << to_string_with_precision(pullMean.getVal());
    pullMeanString << " #pm "
                   << to_string_with_precision(
                          pullMean.getPropagatedError(*pullResult.get()));
    pullSigmaString << "#sigma = "
                    << to_string_with_precision(pullSigma.getVal());
    pullSigmaString << " #pm "
                    << to_string_with_precision(
                           pullSigma.getPropagatedError(*pullResult.get()));
    pullLegend.AddEntry(blankHist.get(), pullMeanString.str().c_str(), "l");
    pullLegend.AddEntry(blankHist.get(), pullSigmaString.str().c_str(), "l");
    pullLegend.Draw("same");

    varCanvas.SaveAs((outputDir + "/plots/" + deltaLow + "_" + deltaHigh + "_" +
                      buLow + "_" + buHigh + "_" + paramName +
                      "_ValErrPull.pdf")
                         .c_str());
  }
  // Don't save corrected error for now - see if we can get error from pulls
  // TTree tree("tree", "");
  // tree.Branch("errYieldTotSignal", &errYieldTotSignal,
  // "errYieldTotSignal/D");
  // tree.Fill();
  outputFile.Write();
  outputFile.Close();
  std::cout << resultVec.size() << "\n"
            << initValVec.size() << "\n"
            << valVec.size() << "\n"
            << errVec.size() << "\n"
            << pullVec.size();

  std::cout << "\nQuality of fits:\n"
            << "Unconverged: " << nUnConv / resultVec.size() * 100 << " %\n"
            << "Forced positive definite: " << nFPD / resultVec.size() * 100
            << " %\n"
            << "MINOS problems: " << nMINOS / resultVec.size() * 100 << " %\n";

  return 1;
}
