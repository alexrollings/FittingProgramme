#include <fstream>
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooCBShape.h"
#include "RooCategory.h"
#include "RooConstVar.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooDstD0BG.h"
#include "RooExponential.h"
#include "RooGaussian.h"
#include "RooHist.h"
#include "RooPlotable.h"
#include "RooPolyVar.h"
#include "RooProdPdf.h"
#include "RooRandom.h"
#include "RooTreeData.h"
#include "TApplication.h"
#include "TRandom3.h"

#include "CommonFunctions.h" 

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

RooDataSet ExtractDataSet(std::string const &input, RooRealVar &buMass,
                          RooRealVar &deltaMass, RooCategory &fitting,
                          std::string const &box_bu_low,
                          std::string const &box_bu_high,
                          std::string const &box_delta_low,
                          std::string const &box_delta_high, double &nBu,
                          double &nDelta, bool dsCombined) {
  TFile in(input.c_str(), "READ");
  std::unique_ptr<RooDataSet> dataBu;
  std::unique_ptr<RooDataSet> dataDelta;
  if (dsCombined == true) {
    RooDataSet *inputDataSet;
    gDirectory->GetObject("dataset", inputDataSet);
    if (inputDataSet == nullptr) {
      throw std::runtime_error("Data set does not exist.");
    } else {
      std::cout << "inputDataSet extracted... \n";
      inputDataSet->Print();
    }

    auto dataBu_tmp = std::unique_ptr<RooDataSet>(
        dynamic_cast<RooDataSet *>(inputDataSet->reduce(
            ("Delta_M>" + box_delta_low + "&&Delta_M<" + box_delta_high)
                .c_str())));
    if (dataBu_tmp.get() == nullptr) {
      throw std::runtime_error(
          "Could not reduce inputDataSet with delta mass.");
    }
    dataBu = std::unique_ptr<RooDataSet>(
        dynamic_cast<RooDataSet *>(dataBu_tmp->reduce(RooArgSet(buMass))));
    if (dataBu.get() == nullptr) {
      throw std::runtime_error("Could not reduce inputDataSet to Bu mass.");
    }

    auto dataDelta_tmp = std::unique_ptr<RooDataSet>(
        dynamic_cast<RooDataSet *>(inputDataSet->reduce(
            ("Bu_Delta_M>" + box_bu_low + "&&Bu_Delta_M<" + box_bu_high)
                .c_str())));
    if (dataDelta_tmp.get() == nullptr) {
      throw std::runtime_error("Could not reduce inputDataSet with bu mass.");
    }
    dataDelta = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
        dataDelta_tmp->reduce(RooArgSet(deltaMass))));
    if (dataDelta.get() == nullptr) {
      throw std::runtime_error("Could not reduce inputDataSet to Delta mass.");
    }
  } else {
    RooDataSet *dataBu_tmp;
    gDirectory->GetObject("buDataSet", dataBu_tmp);
    if (dataBu_tmp == nullptr) {
      throw std::runtime_error("buDataSet does not exist.");
    } else {
      std::cout << "dataBu extracted... \n";
      dataBu_tmp->Print();
    }
    dataBu = std::unique_ptr<RooDataSet>(
        dynamic_cast<RooDataSet *>(dataBu_tmp->reduce(RooArgSet(buMass), 
            ("Delta_M>" + box_delta_low + "&&Delta_M<" + box_delta_high)
                .c_str())));
    if (dataBu.get() == nullptr) {
      throw std::runtime_error("Could not reduce buDataSet with delta mass.");
    }
    RooDataSet *dataDelta_tmp;
    gDirectory->GetObject("deltaDataSet", dataDelta_tmp);
    if (dataDelta_tmp == nullptr) {
      throw std::runtime_error("deltaDataSet does not exist.");
    } else {
      std::cout << "dataDelta extracted... \n";
      dataDelta_tmp->Print();
    }
    dataDelta = std::unique_ptr<RooDataSet>(
        dynamic_cast<RooDataSet *>(dataDelta_tmp->reduce(RooArgSet(deltaMass), 
            ("Bu_Delta_M>" + box_bu_low + "&&Bu_Delta_M<" + box_bu_high)
                .c_str())));
    if (dataDelta.get() == nullptr) {
      throw std::runtime_error(
          "Could not reduce deltaDataSet with delta mass.");
    }
  }
  nBu = dataBu->numEntries();
  nDelta = dataDelta->numEntries();

  RooDataSet combData("combData", "", RooArgSet(buMass, deltaMass),
                      RooFit::Index(fitting),
                      RooFit::Import("bu", *dataBu.get()),
                      RooFit::Import("delta", *dataDelta.get()));
  return combData;
}

void FitToys(std::vector<std::string> const &filenames,
             std::string const &outputDir, std::string const &box_delta_low,
             std::string const &box_delta_high, std::string const &box_bu_low,
             std::string const &box_bu_high, bool dsCombined) {
  int bu_low = 5050;
  int bu_high = 5500;
  int delta_low = 60;  // 134;
  int delta_high = 190;

  int bu_nbins = (bu_high - bu_low) / 10;
  int delta_nbins = (delta_high - delta_low) / 2;

  // ---------------------------- Fitting Vars ----------------------------
  RooRealVar buMass("Bu_Delta_M", "m[D^{*0}#pi^{#pm}] - m[D^{*0}]", bu_low,
                    bu_high, "MeV/c^{2}");
  RooRealVar deltaMass("Delta_M", "m[D^{*0}] - m[D^{0}]", delta_low, delta_high,
                       "MeV/c^{2}");

  buMass.setBins(bu_nbins);
  deltaMass.setBins(delta_nbins);

  // ---------------------------- Categories ----------------------------
  RooCategory fitting("fitting", "fitting");
  fitting.defineType("bu");
  fitting.defineType("delta");

  // ---------------------------- Efficiencies ----------------------------
  // Outside of loop as all datasets have same box dimensions
  RooRealVar orEffSignal("orEffSignal", "",
                         ReturnBoxEff(Efficiency::orEff, box_delta_low,
                                      box_delta_high, box_bu_low, box_bu_high));
  RooRealVar boxEffSignal(
      "boxEffSignal", "",
      ReturnBoxEff(Efficiency::boxEff, box_delta_low, box_delta_high,
                   box_bu_low, box_bu_high));
  RooRealVar deltaCutEffSignal(
      "deltaCutEffSignal", "",
      ReturnBoxEff(Efficiency::deltaCutEff, box_delta_low, box_delta_high,
                   box_bu_low, box_bu_high));
  RooRealVar buCutEffSignal(
      "buCutEffSignal", "",
      ReturnBoxEff(Efficiency::buCutEff, box_delta_low, box_delta_high,
                   box_bu_low, box_bu_high));

  double a2DeltaVal, meanDeltaVal, sigmaDeltaVal;
  if (std::stoi(box_bu_high) >= 5355) {
    a2DeltaVal = -7.2190e-01;
    meanDeltaVal = 1.4277e+02;
    sigmaDeltaVal = 8.7264e+00;
  } else if (std::stoi(box_bu_high) >= 5345 && std::stoi(box_bu_high) < 5355) {
    a2DeltaVal = -7.2698e-01;
    meanDeltaVal = 1.4276e+02;
    sigmaDeltaVal = 8.7195e+00;
  } else if (std::stoi(box_bu_high) >= 5335 && std::stoi(box_bu_high) < 5345) {
    a2DeltaVal = -7.3603e-01;
    meanDeltaVal = 1.4275e+02;
    sigmaDeltaVal = 8.6937e+00;
  } else if (std::stoi(box_bu_high) >= 5325 && std::stoi(box_bu_high) < 5335) {
    a2DeltaVal = -7.5835e-01;
    meanDeltaVal = 1.4275e+02;
    sigmaDeltaVal = 8.6786e+00;
  } else if (std::stoi(box_bu_high) >= 5315 && std::stoi(box_bu_high) < 5325) {
    a2DeltaVal = -7.8634e-01;
    meanDeltaVal = 1.4266e+02;
    sigmaDeltaVal = 8.6644e+00;
  } else if (std::stoi(box_bu_high) >= 5305 && std::stoi(box_bu_high) < 5315) {
    a2DeltaVal = -8.2444e-01;
    meanDeltaVal = 1.4250e+02;
    sigmaDeltaVal = 8.6223e+00;
  } else if (std::stoi(box_bu_high) >= 5295 && std::stoi(box_bu_high) < 5305) {
    a2DeltaVal = -8.5594e-01;
    meanDeltaVal = 1.4215e+02;
    sigmaDeltaVal = 8.5430e+00;
  } else if (std::stoi(box_bu_high) >= 5285 && std::stoi(box_bu_high) < 5295) {
    a2DeltaVal = -8.9696e-01;
    meanDeltaVal = 1.4168e+02;
    sigmaDeltaVal = 8.4596e+00;
  } else if (std::stoi(box_bu_high) >= 5275 && std::stoi(box_bu_high) < 5285) {
    a2DeltaVal = -8.9336e-01;
    meanDeltaVal = 1.4089e+02;
    sigmaDeltaVal = 8.3475e+00;
  } else if (std::stoi(box_bu_high) >= 5265 && std::stoi(box_bu_high) < 5275) {
    a2DeltaVal = -9.0617e-01;
    meanDeltaVal = 1.4007e+02;
    sigmaDeltaVal = 8.4106e+00;
  } else if (std::stoi(box_bu_high) >= 5255 && std::stoi(box_bu_high) < 5265) {
    a2DeltaVal = -9.3522e-01;
    meanDeltaVal = 1.3950e+02;
    sigmaDeltaVal = 8.3672e+00;
  } else if (std::stoi(box_bu_high) >= 5245 && std::stoi(box_bu_high) < 5255) {
    a2DeltaVal = -8.2290e-01;
    meanDeltaVal = 1.3874e+02;
    sigmaDeltaVal = 8.1266e+00;
  } else if (std::stoi(box_bu_high) >= 5235 && std::stoi(box_bu_high) < 5245) {
    a2DeltaVal = -5.0851e-01;
    meanDeltaVal = 1.3771e+02;
    sigmaDeltaVal = 7.8642e+00;
  } else if (std::stoi(box_bu_high) >= 5225 && std::stoi(box_bu_high) < 5235) {
    a2DeltaVal = -1.9972e-01;
    meanDeltaVal = 1.3651e+02;
    sigmaDeltaVal = 6.8620e+00;
  } else if (std::stoi(box_bu_high) >= 5215 && std::stoi(box_bu_high) < 5225) {
    a2DeltaVal = -2.7735e-02;
    meanDeltaVal = 1.3730e+02;
    sigmaDeltaVal = 6.3788e+00;
  } else if (std::stoi(box_bu_high) >= 5205 && std::stoi(box_bu_high) < 5215) {
    a2DeltaVal = -2.6097e-03;
    meanDeltaVal = 1.4209e+02;
    sigmaDeltaVal = 5.5830e+00;
  } else if (std::stoi(box_bu_high) < 5205) {
    a2DeltaVal = -1.0712e-03;
    meanDeltaVal = 1.4308e+02;
    sigmaDeltaVal = 5.1589e+00;
  } else {
    std::cout << "No value set for a2DeltaVal, using default";
    a2DeltaVal = -1;
    meanDeltaVal = 140;
    sigmaDeltaVal = 8;
  }

  // Loop over data files and perform 1D fit to each dataset
  for (unsigned int i = 0; i < filenames.size(); ++i) {
    if (!fexists(filenames[i])) {
      std::cerr << filenames[i] << " does not exist.\n";
    } else {
      double nBu, nDelta;
      // ---------------------------- Read in toy dataset
      // ----------------------------
      RooDataSet combData = ExtractDataSet(
          filenames[i], buMass, deltaMass, fitting, box_bu_low, box_bu_high,
          box_delta_low, box_delta_high, nBu, nDelta, dsCombined);
      combData.Print();

      auto toyDataHist = std::unique_ptr<RooDataHist>(combData.binnedClone(
          ("toyDataHist_" + std::to_string(i)).c_str(), "toyDataHist"));
      auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());
      toyAbsData->SetName(("toyAbsData_" + std::to_string(i)).c_str());

      // ---------------------------- PDFs ----------------------------
      //
      // ---------------------------- Signal ----------------------------
      // ---------------------------- Mean ----------------------------
      RooRealVar meanDeltaSignal(
          ("meanDeltaSignal_" + std::to_string(i)).c_str(), "", 1.4280e+02);//, 135, 150);
      meanDeltaSignal.setVal(meanDeltaVal);
      // ---------------------------- Sigmas ----------------------------
      RooRealVar sigmaDeltaSignal(
          ("sigmaDeltaSignal_" + std::to_string(i)).c_str(), "", 8.7003e+00);//, 5, 15);
      sigmaDeltaSignal.setVal(sigmaDeltaVal);
          // 8.6601e+00, 5, 15);
      // ---------------------------- Tails ----------------------------
      RooRealVar a1DeltaSignal(("a1DeltaSignal_" + std::to_string(i)).c_str(),
                               "", 2.0640e+00);//, 0, 5);//1.9251e+00, 0, 5);
      RooRealVar a2DeltaSignal(("a2DeltaSignal_" + std::to_string(i)).c_str(),
                               "", -7.2834e-01);//, -5, -0.001);//-7.4405e-01, -5, -0.0001);
      a2DeltaSignal.setVal(a2DeltaVal);
      RooRealVar n1DeltaSignal(("n1DeltaSignal_" + std::to_string(i)).c_str(),
                               "", 1.8569e+00);//, 0, 10);//1.0441e+00, 0, 10);
      RooRealVar n2DeltaSignal(("n2DeltaSignal_" + std::to_string(i)).c_str(),
                               "", 3.3122e+00);//, 0, 10);//4.2875e+00, 0, 10);
      // ---------------------------- PDFs ----------------------------
      RooCBShape pdfDeltaSignal1(
          ("pdfDeltaSignal1_" + std::to_string(i)).c_str(), "", deltaMass,
          meanDeltaSignal, sigmaDeltaSignal, a1DeltaSignal, n1DeltaSignal);
      RooCBShape pdfDeltaSignal2(
          ("pdfDeltaSignal2_" + std::to_string(i)).c_str(), "", deltaMass,
          meanDeltaSignal, sigmaDeltaSignal, a2DeltaSignal, n2DeltaSignal);
      RooRealVar fracPdf1DeltaSignal(
          ("fracPdf1DeltaSignal_" + std::to_string(i)).c_str(), "", 1.7974e-01);
      RooAddPdf pdfDeltaSignal(("pdfDeltaSignal_" + std::to_string(i)).c_str(),
                               "", RooArgSet(pdfDeltaSignal1, pdfDeltaSignal2),
                               fracPdf1DeltaSignal);

      // ---------------------------- PDFs: Bu ----------------------------
      // ---------------------------- Signal ----------------------------
      // ---------------------------- Mean ----------------------------
      RooRealVar meanBuSignal(("meanBuSignal_" + std::to_string(i)).c_str(), "",
                              5.2834e+03);//, 5280, 5290);
      // ---------------------------- Sigmas ----------------------------
      RooRealVar sigmaBuSignal(("sigmaBuSignal_" + std::to_string(i)).c_str(),
                               "", 2.1232e+01);//, 18,
                               // 24);  //, 300, 400);

      // ---------------------------- Tails ----------------------------
      RooRealVar a1BuSignal(("a1BuSignal_" + std::to_string(i)).c_str(), "",
                            1.9600e+00);//1.6160e+00, 0, 5);
      RooRealVar a2BuSignal(("a2BuSignal_" + std::to_string(i)).c_str(), "",
                            -1.1104e+00);//-1.5208e+00, -5, -0.0001);
      RooRealVar n1BuSignal(("n1BuSignal_" + std::to_string(i)).c_str(), "",
                            9.9268e+00);//9.9933e+00, 0, 10);
      RooRealVar n2BuSignal(("n2BuSignal_" + std::to_string(i)).c_str(), "",
                            4.2966e+00);//6.4413e+00, 0, 10);
      // ---------------------------- PDFs ----------------------------
      RooRealVar fracPdf1BuSignal(
          ("fracPdf1BuSignal_" + std::to_string(i)).c_str(), "", 7.4517e-01);
      RooCBShape pdfBuSignal1(("pdfBuSignal1_" + std::to_string(i)).c_str(), "",
                              buMass, meanBuSignal, sigmaBuSignal, a1BuSignal,
                              n1BuSignal);
      RooCBShape pdfBuSignal2(("pdfBuSignal2_" + std::to_string(i)).c_str(), "",
                              buMass, meanBuSignal, sigmaBuSignal, a2BuSignal,
                              n2BuSignal);
      RooAddPdf pdfBuSignal(("pdfBuSignal_" + std::to_string(i)).c_str(), "",
                            RooArgSet(pdfBuSignal1, pdfBuSignal2),
                            fracPdf1BuSignal);

      // ---------------------------- Background ----------------------------
      //
      // RooRealVar lambdaDeltaBkg(("lambdaDeltaBkg_" + std::to_string(i)).c_str(),
      //                           "", 0.01);//, -0.1, 0.1);
      // RooExponential pdfDeltaBkg(("pdfDeltaBkg_" + std::to_string(i)).c_str(),
      //                            "", deltaMass, lambdaDeltaBkg);

      RooRealVar thresholdDeltaBkg(
          ("thresholdDeltaBkg_" + std::to_string(i)).c_str(), "", 5.8300e+01);
      RooRealVar cDeltaBkg(("cDeltaBkg_" + std::to_string(i)).c_str(), "",
                           8.3605e+01);
      RooRealVar aDeltaBkg(("aDeltaBkg_" + std::to_string(i)).c_str(), "",
                           2.2537e-01);
      RooRealVar bDeltaBkg(("bDeltaBkg_" + std::to_string(i)).c_str(), "",
                           -3.5935e-01);
      RooDstD0BG pdfDeltaBkg(("pdfDeltaBkg_" + std::to_string(i)).c_str(), "",
                             deltaMass, thresholdDeltaBkg, cDeltaBkg, aDeltaBkg,
                             bDeltaBkg);

      // ---------------------------- π/K shared PDFs: Bu
      // ----------------------------
      // RooRealVar lambdaBuBkg(("lambdaBuBkg_" + std::to_string(i)).c_str(),
      // "",
      //                        -0.005);//, -0.1, 0.1);
      // RooExponential pdfBuBkg(("pdfBuBkg_" + std::to_string(i)).c_str(), "",
      //                         buMass, lambdaBuBkg);
      RooRealVar meanBuBkg(("meanBuBkg_" + std::to_string(i)).c_str(), "",
                           5.2499e+03);
      RooRealVar sigmaBuBkg(("sigmaBuBkg_" + std::to_string(i)).c_str(), "",
                            7.9054e+01);
      RooGaussian pdfBuBkg(("pdfBuBkg_" + std::to_string(i)).c_str(), "",
                           buMass, meanBuBkg, sigmaBuBkg);
      // // ---------------------------- Mean ----------------------------
      // RooRealVar mean1BuBkg(("mean1BuBkg_" + std::to_string(i)).c_str(), "",
      // 5.3544e+03, 5300, 5400);
      // RooRealVar mean2BuBkg(("mean2BuBkg_" + std::to_string(i)).c_str(), "",
      // 5.2230e+03, 5200, 5250);
      // // ---------------------------- Sigmas ----------------------------
      // RooRealVar sigma1BuBkg(("sigma1BuBkg_" + std::to_string(i)).c_str(),
      // "", 8.6260e+01, 50, 100); //,
      // 5, 15);
      // RooRealVar sigmaFracBuBkg(("sigmaFracBuBkg_" +
      // std::to_string(i)).c_str(), "", 8.2710e-01, 0, 1);  //,
      // -0.1, 0.1);
      // RooFormulaVar sigma2BuBkg(("sigma2BuBkg_" + std::to_string(i)).c_str(),
      // "", "@0*@1",
      //                           RooArgSet(sigma1BuBkg, sigmaFracBuBkg));
      // // ---------------------------- Tails ----------------------------
      // RooRealVar a1BuBkg(("a1BuBkg_" + std::to_string(i)).c_str(), "",
      // -1.0599e+00);
      // RooRealVar n1BuBkg(("n1BuBkg_" + std::to_string(i)).c_str(), "",
      // 2.0140e+00);
      // RooRealVar n2BuBkg(("n2BuBkg_" + std::to_string(i)).c_str(), "",
      // 2.1358e+01);
      // // ---------------------------- PDFs ----------------------------
      // RooCBShape pdfBuBkg1(("pdfBuBkg1_" + std::to_string(i)).c_str(), "",
      // buMass, mean1BuBkg, sigma1BuBkg,
      //                      a1BuBkg, n1BuBkg);
      // RooCBShape pdfBuBkg2(("pdfBuBkg2_" + std::to_string(i)).c_str(), "",
      // buMass, mean2BuBkg, sigma2BuBkg,
      //                      a2BuBkg, n2BuBkg);
      // RooRealVar fracPdf1BuBkg(("fracPdf1BuBkg_" +
      // std::to_string(i)).c_str(), "",  5.2225e-01);
      // RooAddPdf pdfBuBkg(("pdfBuBkg_" + std::to_string(i)).c_str(), "",
      // RooArgSet(pdfBuBkg1, pdfBuBkg2),
      //                    fracPdf1BuBkg);

      double nSig = 43374;
      RooRealVar yieldTotSignal(("yieldTotSignal_" + std::to_string(i)).c_str(),
                                "", nSig * orEffSignal.getVal(), 0, 100000);
      // ---------------------------- Yields ----------------------------

      RooFormulaVar yieldBuSignal(
          ("yieldBuSignal_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
          RooArgList(deltaCutEffSignal, orEffSignal, yieldTotSignal));
      RooFormulaVar yieldDeltaSignal(
          ("yieldDeltaSignal_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
          RooArgList(buCutEffSignal, orEffSignal, yieldTotSignal));
      RooFormulaVar yieldSharedSignal(
          ("yieldSharedSignal_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
          RooArgList(boxEffSignal, orEffSignal, yieldTotSignal));

      // Temporary solution to calculate bkg efficiencies
      double nBuBkg = nBu - nSig * deltaCutEffSignal.getVal();
      double nDeltaBkg = nDelta - nSig * buCutEffSignal.getVal();

      RooRealVar yieldBuBkg(("yieldBuBkg_" + std::to_string(i)).c_str(), "",
                            nBuBkg, 0, 100000);
      RooRealVar yieldDeltaBkg(("yieldDeltaBkg_" + std::to_string(i)).c_str(),
                               "", nDeltaBkg, 0, 100000);

      // RooRealVar yieldTotBkg(("yieldTotBkg_" + std::to_string(i)).c_str(),
      // "", (nBuBkg + nDeltaBkg), 0,
      // 100000);
      // RooRealVar fracBkgYield(("fracBkgYield_" + std::to_string(i)).c_str(),
      // "", 0.8, -5, 5);
      // RooFormulaVar yieldTotBkg(("yieldTotBkg_" + std::to_string(i)).c_str(),
      // "", "@0*@1",
      //                        RooArgSet(yieldTotSignal, fracBkgYield));

      // RooFormulaVar yieldBuBkg(("yieldBuBkg_" + std::to_string(i)).c_str(),
      // "", "@0*@1",
      //                          RooArgList(yieldTotBkg, deltaCutEffBkg));
      // RooFormulaVar yieldDeltaBkg(("yieldDeltaBkg_" +
      // std::to_string(i)).c_str(), "", "@0*@1",
      //                             RooArgList(yieldTotBkg, buCutEffBkg));
      // RooFormulaVar yieldSharedBkg(("yieldSharedBkg_" +
      // std::to_string(i)).c_str(), "", "@0*@1",
      //                              RooArgList(yieldTotBkg, boxEffBkg));

      // ---------------------------- Add PDFs and yields
      // ----------------------------
      RooArgSet yieldsBu;
      yieldsBu.add(yieldBuSignal);
      yieldsBu.add(yieldBuBkg);

      RooArgSet functionsBu;
      functionsBu.add(pdfBuSignal);
      functionsBu.add(pdfBuBkg);
      RooAddPdf pdfBu(("pdfBu_" + std::to_string(i)).c_str(), "", functionsBu,
                      yieldsBu);

      RooArgSet yieldsDelta;
      yieldsDelta.add(yieldDeltaSignal);
      yieldsDelta.add(yieldDeltaBkg);

      RooArgSet functionsDelta;
      functionsDelta.add(pdfDeltaSignal);
      functionsDelta.add(pdfDeltaBkg);
      RooAddPdf pdfDelta(("pdfDelta_" + std::to_string(i)).c_str(), "",
                         functionsDelta, yieldsDelta);

      // ---------------------------- Construct Sim PDF
      // ----------------------------
      RooSimultaneous simPdf(("simPdf_" + std::to_string(i)).c_str(), "",
                             fitting);
      simPdf.addPdf(pdfBu, "bu");
      simPdf.addPdf(pdfDelta, "delta");

      // meanDeltaSignal.setVal(142);

      // ---------------------------- Fit Sim PDF to toy
      // ----------------------------
      std::unique_ptr<RooFitResult> result =
          std::unique_ptr<RooFitResult>(simPdf.fitTo(
              *toyAbsData, RooFit::Extended(true), RooFit::SplitRange(true),
              RooFit::Save(), RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
              RooFit::Offset(true), RooFit::NumCPU(8, 2)));

      if (i == 0) {
        std::cout << "Plotting projections of m[Bu]\n";
        PlotComponent(Variable::bu, buMass, toyDataHist.get(), simPdf, fitting,
                      pdfBuSignal, pdfBuBkg, outputDir, box_delta_low,
                      box_delta_high,
                      box_bu_low, box_bu_high);
        std::cout << "Plotting projections of m[Delta]\n";
        PlotComponent(Variable::delta, deltaMass, toyDataHist.get(), simPdf,
        fitting,
                      pdfDeltaSignal, pdfDeltaBkg, outputDir, box_delta_low,
                      box_delta_high, box_bu_low, box_bu_high);
        std::cout << "Plotting correlation matrix\n";
        PlotCorrMatrix(result.get(), outputDir, box_delta_low, box_delta_high,
                       box_bu_low, box_bu_high);
      }
      result->Print("v");

      // Essentially just fitErr * sqrt((boxEff * sqrt(2))^2 + (1-boxEff)^2)
      double errYieldTotSignal =
          yieldTotSignal.getPropagatedError(*result) *
          std::sqrt(
              pow(((yieldSharedSignal.getVal() / yieldTotSignal.getVal()) *
                   std::sqrt(2)),
                  2) +
              pow((1 - yieldSharedSignal.getVal() / yieldTotSignal.getVal()),
                  2));
      std::cout << "Box = " << box_delta_low << "-" << box_delta_high << " "
                << box_bu_low << "-" << box_bu_high << "\n";
      std::cout << "yieldSharedSignal = " << yieldSharedSignal.getVal() << " ± "
                << yieldSharedSignal.getPropagatedError(*result) << "\n";
      std::cout << "yieldTotSignal = " << yieldTotSignal.getVal() << " ± "
                << errYieldTotSignal << "\n";
      std::cout << "Corrected error / fit Error = "
                << errYieldTotSignal /
                       yieldTotSignal.getPropagatedError(*result)
                << "\n";
      std::cout << "Corrected error / fit Error = "
                << errYieldTotSignal / yieldTotSignal.getError() << "\n";
      // double errYieldTotBkg =
      //     yieldTotBkg.getPropagatedError(*result) *
      //     (yieldSharedBkg.getVal() / yieldTotBkg.getVal() * std::sqrt(2) +
      //      (1 - yieldSharedBkg.getVal() / yieldTotBkg.getVal()));
      // std::cout << "yieldTotBkg = " << yieldTotBkg.getVal() << " ± "
      //           << errYieldTotBkg << "\n";
      std::regex rexp("DataFile_([A-Za-z0-9]+).root");
      std::smatch match;
      std::regex_search(filenames[i], match, rexp);
      std::string seed = match[1];
      TFile outputFile(
          (outputDir + "/results/ResultD1D_" + box_delta_low + "_" +
           box_delta_high + "_" + box_bu_low + "_" + box_bu_high + "_" + seed + ".root")
              .c_str(),
          "recreate");
      outputFile.cd();
      // result->SetName(("Result_" + rndm).c_str());
      result->SetName("ToyResult");
      result->Write();
      // Don't save corrected error for now - see if we can get error from pulls
      // TTree tree("tree", "");
      // tree.Branch("errYieldTotSignal", &errYieldTotSignal, "errYieldTotSignal/D");
      // double orEffSignalD = orEffSignal.getVal();
      // tree.Branch("orEffSignal", &orEffSignalD, "orEffSignal/D");
      // double boxEffSignalD = boxEffSignal.getVal();
      // tree.Branch("boxEffSignal", &boxEffSignalD, "boxEffSignal/D");
      // tree.Fill();
      // tree.Write();
      outputFile.Write();
      outputFile.Close();
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 7) {
    std::cerr << "Enter input file vector, output directory and box limits: "
                 "delta_low, "
                 "delta_high, bu_low, bu_high, optional 1D flag to fit "
                 "separate bu and delta mass datasets\n";
    return 1;
  }

  std::vector<std::string> filenames;
  {
    std::string input = argv[1];
    filenames = SplitByComma(input);
  }

  std::string outputDir = argv[2];
  std::string box_delta_low = argv[3];
  std::string box_delta_high = argv[4];
  std::string box_bu_low = argv[5];
  std::string box_bu_high = argv[6];

  bool dsCombined = true;
  if (argc == 8) {
    std::string dsOptStr = argv[7];
    if (dsOptStr == "1D") {
      dsCombined = false;
      std::cout << "Reading in separate datasets\n";
    }
  }

  FitToys(filenames, outputDir, box_delta_low, box_delta_high, box_bu_low,
          box_bu_high, dsCombined);

  return 0;
}
