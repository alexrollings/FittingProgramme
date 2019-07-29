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
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooHist.h"
#include "RooPlot.h"
#include "RooPlotable.h"
#include "RooPolyVar.h"
#include "RooProdPdf.h"
#include "RooRandom.h"
#include "RooRealVar.h"
#include "RooSimultaneous.h"
#include "RooTreeData.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TLine.h"
#include "TPad.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TTreeReader.h"

enum class Variable { bu, delta };
enum class Mode {
  Bd2Dstpi,
  Bu2D0pi,
  Bu2D0rho,
  Bu2Dst0pi_D0gamma,
  Bu2Dst0pi_D0pi0,
  Bu2Dst0rho_D0gamma,
  Bu2Dst0rho_D0pi0
};

std::string EnumToString(Variable variable) {
  switch (variable) {
    case Variable::bu:
      return "bu";
      break;
    case Variable::delta:
      return "delta";
      break;
  }
}

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

bool file_exists(const std::string &name) {
  std::ifstream infile(name);
  return infile.good();
}

void ExtractBoxEfficiencies(Mode mode, std::string const &box_delta_low,
                            std::string const &box_delta_high,
                            std::string const &box_bu_low,
                            std::string const &box_bu_high, RooRealVar &boxEff,
                            RooRealVar &deltaCutEff, RooRealVar &buCutEff,
                            RooRealVar &orEff) {
  std::string inputfile_1(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2011_MagUp/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2011_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_2(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2011_MagDown/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2011_MagDown_BDT1_BDT2_PID_TM.root");
  std::string inputfile_3(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2012_MagUp/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2012_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_4(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2012_MagDown/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2012_MagDown_BDT1_BDT2_PID_TM.root");
  std::string inputfile_5(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2015_MagUp/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2015_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_6(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2015_MagDown/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2015_MagDown_BDT1_BDT2_PID_TM.root");
  std::string inputfile_7(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2016_MagUp/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2016_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_8(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2016_MagDown/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2016_MagDown_BDT1_BDT2_PID_TM.root");
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
        EnumToString(mode) + "_2015_MagUp_BDT1_BDT2_PID_TM.root");
    std::string inputfile_10(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
        "_ReDecay_2015_MagDown/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
        "cross_feed_removed/" +
        EnumToString(mode) + "_ReDecay_2015_MagDown_BDT1_BDT2_PID_TM.root");
    std::string inputfile_11(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
        "_ReDecay_2016_MagUp/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
        "cross_feed_removed/" +
        EnumToString(mode) + "_ReDecay_2016_MagUp_BDT1_BDT2_PID_TM.root");
    std::string inputfile_12(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
        "_ReDecay_2016_MagDown/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
        "cross_feed_removed/" +
        EnumToString(mode) + "_ReDecay_2016_MagDown_BDT1_BDT2_PID_TM.root");
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
  double nDeltaWindow =
      chain.GetEntries(("BDT1>0.05&&BDT2>0.05&&Delta_M>50&&Delta_M<210&&Bu_M_"
                        "DTF_D0>5050&&Bu_M_DTF_D0<5800&&Delta_M>" +
                        box_delta_low + "&&Delta_M<" + box_delta_high)
                           .c_str());
  double nBuWindow =
      chain.GetEntries(("BDT1>0.05&&BDT2>0.05&&Delta_M>50&&Delta_M<210&&Bu_M_"
                        "DTF_D0>5050&&Bu_M_DTF_D0<5800&&Bu_Delta_M>" +
                        box_bu_low + "&&Bu_Delta_M<" + box_bu_high)
                           .c_str());
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

  deltaCutEff.setVal(nDeltaWindow / nInitial);
  buCutEff.setVal(nBuWindow / nInitial);
  boxEff.setVal(nBox / nInitial);
  orEff.setVal(nOr / nInitial);

  std::cout << "Set efficiencies :\n"
            << "\tDelta Window =\t" << nDeltaWindow / nInitial
            << "\tBu Window =\t" << nBuWindow / nInitial << "\tBox =\t"
            << nBox / nInitial << "\n"
            << "\tDelta OR Bu =\t" << nOr / nInitial << "\n"
            << "\t# events initially =\t" << nInitial << "\n";
}

void PlotComponent(Variable variable, RooRealVar &var, RooDataHist *dataHist,
                   RooSimultaneous &simPdf, RooCategory &fitting,
                   RooAddPdf &sig, RooAbsPdf &bkg1, RooAbsPdf &bkg2,
                   std::string const &outputDir, std::string const &box_bu_low,
                   std::string const &box_bu_high,
                   std::string const &box_delta_low,
                   std::string const &box_delta_high) {
  gStyle->SetTitleFont(132, "XYZ");
  gStyle->SetLabelFont(132, "XYZ");
  gStyle->SetStatFont(132);
  gStyle->SetStatFontSize(0.02);
  gStyle->SetTitleSize(0.08, "Z");
  gStyle->SetTitleSize(0.035, "XY");
  gStyle->SetLabelSize(0.03, "XY");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.5, "Y");
  gStyle->SetTitleOffset(0.95, "Z");
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.1);
  gStyle->SetPadLeftMargin(0.12);

  std::string title;
  switch (variable) {
    case Variable::bu:
      title = "m[D^{*0}#pi] - m[D^{*0}] + m[D^{*0}]_{{PDG}";
      break;
    case Variable::delta:
      title = "m[D^{*0}] - m[D^{0}]";
      break;
  }

  auto frame =
      std::unique_ptr<RooPlot>(var.frame(RooFit::Title(title.c_str())));

  RooHist *pullHist = nullptr;
  std::unique_ptr<RooPlot> pullFrame(var.frame(RooFit::Title(" ")));

  dataHist->plotOn(
      frame.get(),
      RooFit::Cut(("fitting==fitting::" + EnumToString(variable)).c_str()));
  simPdf.plotOn(
      frame.get(), RooFit::Slice(fitting, EnumToString(variable).c_str()),
      RooFit::ProjWData(fitting, *dataHist), RooFit::LineColor(kBlue));
  pullHist = frame->RooPlot::pullHist();
  simPdf.plotOn(
      frame.get(), RooFit::Slice(fitting, EnumToString(variable).c_str()),
      RooFit::ProjWData(fitting, *dataHist), RooFit::Components(sig.GetName()),
      RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed));
  simPdf.plotOn(
      frame.get(), RooFit::Slice(fitting, EnumToString(variable).c_str()),
      RooFit::ProjWData(fitting, *dataHist), RooFit::Components(bkg1.GetName()),
      RooFit::LineColor(kRed), RooFit::LineStyle(kDashed));
  simPdf.plotOn(
      frame.get(), RooFit::Slice(fitting, EnumToString(variable).c_str()),
      RooFit::ProjWData(fitting, *dataHist), RooFit::Components(bkg2.GetName()),
      RooFit::LineColor(kOrange), RooFit::LineStyle(kDashed));

  dataHist->plotOn(
      frame.get(),
      RooFit::Cut(("fitting==fitting::" + EnumToString(variable)).c_str()));

  if (pullHist != 0) {
    pullFrame->addPlotable(pullHist /* .get() */, "P");
    pullFrame->SetName(("pullFrame_" + EnumToString(variable)).c_str());
    pullFrame->SetTitle("");
  }

  TCanvas canvas(("canvas_" + EnumToString(variable)).c_str(), "", 1200, 1000);

  TPad pad1(("pad1_" + EnumToString(variable)).c_str(), "", 0.0, 0.14, 1.0, 1.0,
            kWhite);
  pad1.Draw();

  TPad pad2(("pad2_" + EnumToString(variable)).c_str(), "", 0.0, 0.05, 1.0,
            0.15, kWhite);
  pad2.Draw();

  TLine zeroLine(var.getMin(), 0, var.getMax(), 0);
  zeroLine.SetLineColor(kRed);
  zeroLine.SetLineStyle(kDashed);

  canvas.cd();
  pad2.cd();
  pullFrame->SetYTitle(" ");
  pullFrame->SetXTitle(" ");
  pullFrame->SetLabelSize(0.2, "Y");
  pullFrame->SetLabelFont(132, "XY");
  pullFrame->SetLabelOffset(100, "X");
  pullFrame->SetTitleOffset(100, "X");
  pullFrame->Draw();
  zeroLine.Draw("same");

  canvas.cd();
  pad1.cd();
  frame->Draw();
  canvas.Update();
  canvas.SaveAs((outputDir + "/1d_plots/" + EnumToString(variable) + "_" +
                 box_delta_low + "_" + box_delta_high + "_" + box_bu_low + "_" +
                 box_bu_high + ".pdf")
                    .c_str());
}

void PlotCorrMatrix(RooFitResult *result, std::string const &outputDir,
                    std::string const &box_bu_low,
                    std::string const &box_bu_high,
                    std::string const &box_delta_low,
                    std::string const &box_delta_high) {
  TCanvas corrCanvas("corrCanvas", "corrCanvas", 1200, 900);
  TH2 *corrHist = result->correlationHist();
  corrHist->SetStats(0);
  corrHist->SetTitle(" ");
  corrCanvas.cd();
  gPad->SetLeftMargin(0.2);
  gPad->SetRightMargin(0.1);
  gPad->SetBottomMargin(0.15);
  gPad->SetTopMargin(0.05);
  corrHist->SetLabelSize(0.04, "XY");
  corrHist->SetLabelSize(0.02, "Z");
  corrHist->Draw("colz");
  corrCanvas.Update();
  corrCanvas.SaveAs((outputDir + "/1d_plots/CorrelationMatrix.pdf" + "_" +
                     box_delta_low + "_" + box_delta_high + "_" + box_bu_low +
                     "_" + box_bu_high + ".pdf")
                        .c_str());
}

RooDataSet ExtractDataSetFromToy(std::string const &input, std::string &dim,
                                 RooRealVar &buMass, RooRealVar &deltaMass,
                                 RooCategory &fitting,
                                 std::string const &box_bu_low,
                                 std::string const &box_bu_high,
                                 std::string const &box_delta_low,
                                 std::string const &box_delta_high) {
  TFile in(input.c_str(), "READ");
  if (dim == "1") {
    RooDataSet *dataDelta;
    gDirectory->GetObject("deltaDataSet", dataDelta);
    if (dataDelta == nullptr) {
      throw std::runtime_error("Delta dataset does not exist.");
    } else {
      std::cout << "dataDelta extracted... \n";
      dataDelta->Print();
    }
    RooDataSet *dataBu;
    gDirectory->GetObject("buDataSet", dataBu);
    if (dataBu == nullptr) {
      throw std::runtime_error("Bu dataset does not exist.");
    } else {
      std::cout << "dataBu extracted... \n";
      dataBu->Print();
    }
    RooDataSet combData(
        "combData", "", RooArgSet(buMass, deltaMass), RooFit::Index(fitting),
        RooFit::Import("delta", *dataDelta), RooFit::Import("bu", *dataBu));
    return combData;
    std::cout << "1D: returning combDataSet\n";
  } else {
    RooDataSet *inputDataSet;
    gDirectory->GetObject("toyDataSet", inputDataSet);
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
    auto dataBu = std::unique_ptr<RooDataSet>(
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
    auto dataDelta = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
        dataDelta_tmp->reduce(RooArgSet(deltaMass))));
    if (dataDelta.get() == nullptr) {
      throw std::runtime_error("Could not reduce inputDataSet to Delta mass.");
    }

    RooDataSet combData("combData", "", RooArgSet(buMass, deltaMass),
                        RooFit::Index(fitting),
                        RooFit::Import("bu", *dataBu.get()),
                        RooFit::Import("delta", *dataDelta.get()));
    return combData;
    std::cout << "2D: returning combDataSet\n";
  }
}

void FitToys(bool fitDontSave, int &nIter,
             std::vector<std::string> const &filenames,
             std::string const &outputDir, std::string const &box_delta_low,
             std::string const &box_delta_high, std::string const &box_bu_low,
             std::string const &box_bu_high) {
  int bu_low = 5050;
  int bu_high = 5800;
  int delta_low = 70;  // 134;
  int delta_high = 210;

  int bu_nbins = (bu_high - bu_low) / 10;
  int delta_nbins = (delta_high - delta_low) / 2;

  // ---------------------------- Fitting Vars ----------------------------
  RooRealVar buMass("Bu_Delta_M",
                    "m[D^{*0}#pi^{#pm}] - m[D^{*0}] + m[D^{*0}]_{PDG}", bu_low,
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
  RooRealVar orEffSignal("orEffSignal", "", 1);
  RooRealVar boxEffSignal("boxEffSignal", "", 1);
  RooRealVar deltaCutEffSignal("deltaCutEffSignal", "", 1);
  RooRealVar buCutEffSignal("buCutEffSignal", "", 1);

  ExtractBoxEfficiencies(Mode::Bu2Dst0pi_D0gamma, box_delta_low, box_delta_high,
                         box_bu_low, box_bu_high, boxEffSignal,
                         deltaCutEffSignal, buCutEffSignal, orEffSignal);

  RooRealVar orEffB02Dstpi("orEffB02Dstpi", "", 1);
  RooRealVar boxEffB02Dstpi("boxEffB02Dstpi", "", 1);
  RooRealVar deltaCutEffB02Dstpi("deltaCutEffB02Dstpi", "", 1);
  RooRealVar buCutEffB02Dstpi("buCutEffB02Dstpi", "", 1);

  ExtractBoxEfficiencies(Mode::Bd2Dstpi, box_delta_low, box_delta_high,
                         box_bu_low, box_bu_high, boxEffB02Dstpi,
                         deltaCutEffB02Dstpi, buCutEffB02Dstpi, orEffB02Dstpi);

  RooRealVar orEffBu2D0rho("orEffBu2D0rho", "", 1);
  RooRealVar boxEffBu2D0rho("boxEffBu2D0rho", "", 1);
  RooRealVar deltaCutEffBu2D0rho("deltaCutEffBu2D0rho", "", 1);
  RooRealVar buCutEffBu2D0rho("buCutEffBu2D0rho", "", 1);

  ExtractBoxEfficiencies(Mode::Bu2D0rho, box_delta_low, box_delta_high,
                         box_bu_low, box_bu_high, boxEffBu2D0rho,
                         deltaCutEffBu2D0rho, buCutEffBu2D0rho, orEffBu2D0rho);

  double a2DeltaVal = -7.2924e-01;
  double meanDeltaVal = 1.4256e+02;
  double sigmaDeltaVal = 8.4936e+00;
  if (std::stoi(box_bu_high) == 5360) {
    a2DeltaVal = -7.2924e-01;
    meanDeltaVal = 1.4256e+02;
    sigmaDeltaVal = 8.4936e+00;
  } else if (std::stoi(box_bu_high) == 5350) {
    a2DeltaVal = -7.2698e-01;
    meanDeltaVal = 1.4276e+02;
    sigmaDeltaVal = 8.7195e+00;
  } else if (std::stoi(box_bu_high) == 5340) {
    a2DeltaVal = -7.3603e-01;
    meanDeltaVal = 1.4275e+02;
    sigmaDeltaVal = 8.6937e+00;
  } else if (std::stoi(box_bu_high) == 5330) {
    a2DeltaVal = -7.5835e-01;
    meanDeltaVal = 1.4275e+02;
    sigmaDeltaVal = 8.6786e+00;
  } else if (std::stoi(box_bu_high) == 5320) {
    a2DeltaVal = -7.8634e-01;
    meanDeltaVal = 1.4266e+02;
    sigmaDeltaVal = 8.6644e+00;
  } else if (std::stoi(box_bu_high) == 5310) {
    a2DeltaVal = -8.2444e-01;
    meanDeltaVal = 1.4250e+02;
    sigmaDeltaVal = 8.6223e+00;
  } else if (std::stoi(box_bu_high) == 5300) {
    a2DeltaVal = -8.5594e-01;
    meanDeltaVal = 1.4215e+02;
    sigmaDeltaVal = 8.5430e+00;
  } else if (std::stoi(box_bu_high) == 5290) {
    a2DeltaVal = -8.9696e-01;
    meanDeltaVal = 1.4168e+02;
    sigmaDeltaVal = 8.4596e+00;
  } else if (std::stoi(box_bu_high) == 5280) {
    a2DeltaVal = -8.9336e-01;
    meanDeltaVal = 1.4089e+02;
    sigmaDeltaVal = 8.3475e+00;
  } else if (std::stoi(box_bu_high) == 5270) {
    a2DeltaVal = -9.0617e-01;
    meanDeltaVal = 1.4007e+02;
    sigmaDeltaVal = 8.4106e+00;
  } else if (std::stoi(box_bu_high) == 5260) {
    a2DeltaVal = -9.3522e-01;
    meanDeltaVal = 1.3950e+02;
    sigmaDeltaVal = 8.3672e+00;
  } else if (std::stoi(box_bu_high) == 5250) {
    a2DeltaVal = -8.2290e-01;
    meanDeltaVal = 1.3874e+02;
    sigmaDeltaVal = 8.1266e+00;
  } else if (std::stoi(box_bu_high) == 5240) {
    a2DeltaVal = -5.0851e-01;
    meanDeltaVal = 1.3771e+02;
    sigmaDeltaVal = 7.8642e+00;
  } else if (std::stoi(box_bu_high) == 5230) {
    a2DeltaVal = -1.9972e-01;
    meanDeltaVal = 1.3651e+02;
    sigmaDeltaVal = 6.8620e+00;
  } else if (std::stoi(box_bu_high) == 5220) {
    a2DeltaVal = -2.7735e-02;
    meanDeltaVal = 1.3730e+02;
    sigmaDeltaVal = 6.3788e+00;
  } else if (std::stoi(box_bu_high) == 5210) {
    a2DeltaVal = -2.6097e-03;
    meanDeltaVal = 1.4209e+02;
    sigmaDeltaVal = 5.5830e+00;
  } else if (std::stoi(box_bu_high) == 5200) {
    a2DeltaVal = -1.0712e-03;
    meanDeltaVal = 1.4308e+02;
    sigmaDeltaVal = 5.1589e+00;
  } else {
    std::cout << "No value set for a2DeltaVal, using default";
  }

  // Loop over data files and perform 1D fit to each dataset
  for (int i = 0; i < nIter; ++i) {
    // ---------------------------- PDFs ----------------------------
    // ---------------------------- Signal ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanDeltaSignal(("meanDeltaSignal_" + std::to_string(i)).c_str(),
                               "",
                               meanDeltaVal);  //, 135, 150);
    // meanDeltaSignal.setVal(meanDeltaVal);
    // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaDeltaSignal(
        ("sigmaDeltaSignal_" + std::to_string(i)).c_str(), "",
        sigmaDeltaVal);  //, 2, 15);
    // sigmaDeltaSignal.setVal(sigmaDeltaVal);
    // ---------------------------- Tails ----------------------------
    RooRealVar a1DeltaSignal(("a1DeltaSignal_" + std::to_string(i)).c_str(), "",
                             1.9114e+00);  //, 0, 5);
    RooRealVar a2DeltaSignal(("a2DeltaSignal_" + std::to_string(i)).c_str(), "",
                             a2DeltaVal);  //, -5, -0.001);
    a2DeltaSignal.setVal(a2DeltaVal);
    RooRealVar n1DeltaSignal(("n1DeltaSignal_" + std::to_string(i)).c_str(), "",
                             1.3484e+00);  //, 0, 10);
    RooRealVar n2DeltaSignal(("n2DeltaSignal_" + std::to_string(i)).c_str(), "",
                             2.9966e+00);  //, 0, 10);
    // ---------------------------- PDFs ----------------------------
    RooCBShape pdfDeltaSignal1(("pdfDeltaSignal1_" + std::to_string(i)).c_str(),
                               "", deltaMass, meanDeltaSignal, sigmaDeltaSignal,
                               a1DeltaSignal, n1DeltaSignal);
    RooCBShape pdfDeltaSignal2(("pdfDeltaSignal2_" + std::to_string(i)).c_str(),
                               "", deltaMass, meanDeltaSignal, sigmaDeltaSignal,
                               a2DeltaSignal, n2DeltaSignal);
    RooRealVar fracPdf1DeltaSignal(
        ("fracPdf1DeltaSignal_" + std::to_string(i)).c_str(), "", 1.7974e-01);
    RooAddPdf pdfDeltaSignal(("pdfDeltaSignal_" + std::to_string(i)).c_str(),
                             "", RooArgSet(pdfDeltaSignal1, pdfDeltaSignal2),
                             fracPdf1DeltaSignal);

    // ---------------------------- PDFs: Bu ----------------------------
    // ---------------------------- Signal ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanBuSignal(("meanBuSignal_" + std::to_string(i)).c_str(), "",
                            5.2819e+03);  //, 5275, 5290);
    // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaBuSignal(("sigmaBuSignal_" + std::to_string(i)).c_str(), "",
                             2.0436e+01);  //, 15, 30);  //, 300, 400);

    // ---------------------------- Tails ----------------------------
    RooRealVar a1BuSignal(("a1BuSignal_" + std::to_string(i)).c_str(), "",
                          1.9632e+00);  // 0, 5);
    RooRealVar a2BuSignal(("a2BuSignal_" + std::to_string(i)).c_str(), "",
                          -1.0726e+00);  // -5, -0.0001);
    RooRealVar n1BuSignal(("n1BuSignal_" + std::to_string(i)).c_str(), "",
                          6.5030e+00);  // 0, 10);
    RooRealVar n2BuSignal(("n2BuSignal_" + std::to_string(i)).c_str(), "",
                          1.0561e+01);  // 0, 10);
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

    // ---------------------------- B02Dstpi Background
    // ----------------------------
    //
    // RooRealVar lambdaDeltaBkg(("lambdaDeltaBkg_" +
    // std::to_string(i)).c_str(),
    //                           "", 0.01);//, -0.1, 0.1);
    // RooExponential pdfDeltaBkg(("pdfDeltaBkg_" +
    // std::to_string(i)).c_str(),
    //                            "", deltaMass, lambdaDeltaBkg);

    RooRealVar thresholdDeltaB02Dstpi(
        ("thresholdDeltaB02Dstpi_" + std::to_string(i)).c_str(), "",
        5.2128e+01);  //, 35, 60);
    RooRealVar cDeltaB02Dstpi(("cDeltaB02Dstpi_" + std::to_string(i)).c_str(),
                              "",
                              3.6381e+01);  //, 0, 100);
    RooRealVar aDeltaB02Dstpi(("aDeltaB02Dstpi_" + std::to_string(i)).c_str(),
                              "",
                              1.1156e+00);  //, -2, 2);
    RooRealVar bDeltaB02Dstpi(("bDeltaB02Dstpi_" + std::to_string(i)).c_str(),
                              "",
                              -1.4343e+00);  //, -2, 2);
    RooDstD0BG pdfDeltaB02Dstpi(
        ("pdfDeltaB02Dstpi_" + std::to_string(i)).c_str(), "", deltaMass,
        thresholdDeltaB02Dstpi, cDeltaB02Dstpi, aDeltaB02Dstpi, bDeltaB02Dstpi);

    // ---------------------------- π/K shared PDFs: Bu
    // ----------------------------
    // RooRealVar lambdaBuBkg(("lambdaBuBkg_" + std::to_string(i)).c_str(),
    // "",
    //                        -0.005);//, -0.1, 0.1);
    // RooExponential pdfBuBkg(("pdfBuBkg_" + std::to_string(i)).c_str(), "",
    //                         buMass, lambdaBuBkg);
    // // ---------------------------- Mean ----------------------------
    RooRealVar meanBuB02Dstpi(("meanBuB02Dstpi_" + std::to_string(i)).c_str(),
                              "",
                              5.2970e+03);  //, 5280, 5310);
    // // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaBuB02Dstpi(("sigmaBuB02Dstpi_" + std::to_string(i)).c_str(),
                               "", 9.6292e+01);  //, 50, 100);
    // // ---------------------------- PDFs ----------------------------
    RooGaussian pdfBuB02Dstpi(("pdfBuB02Dstpi_" + std::to_string(i)).c_str(),
                              "", buMass, meanBuB02Dstpi, sigmaBuB02Dstpi);

    // ---------------------------- Bu2D0rho Background
    // ----------------------------
    RooRealVar thresholdDeltaBu2D0rho(
        ("thresholdDeltaBu2D0rho_" + std::to_string(i)).c_str(), "",
        5.1070e+01);  //, 35, 60);
    RooRealVar cDeltaBu2D0rho(("cDeltaBu2D0rho_" + std::to_string(i)).c_str(),
                              "",
                              5.2740e+01);  //, 0, 100);
    RooRealVar aDeltaBu2D0rho(("aDeltaBu2D0rho_" + std::to_string(i)).c_str(),
                              "",
                              8.5307e-01);  //, -2, 2);
    RooRealVar bDeltaBu2D0rho(("bDeltaBu2D0rho_" + std::to_string(i)).c_str(),
                              "",
                              -8.6988e-01);  //, -2, 2);
    RooDstD0BG pdfDeltaBu2D0rho(
        ("pdfDeltaBu2D0rho_" + std::to_string(i)).c_str(), "", deltaMass,
        thresholdDeltaBu2D0rho, cDeltaBu2D0rho, aDeltaBu2D0rho, bDeltaBu2D0rho);

    // // ---------------------------- Mean ----------------------------
    RooRealVar mean1BuBu2D0rho(("mean1BuBu2D0rho_" + std::to_string(i)).c_str(),
                               "",
                               5.3403e+03);  //, 5280, 5310);
    RooRealVar mean2BuBu2D0rho(("mean2BuBu2D0rho_" + std::to_string(i)).c_str(),
                               "",
                               5.1917e+03);  //, 5200, 5250);
    // // ---------------------------- Sigmas ----------------------------
    RooRealVar sigma1BuBu2D0rho(
        ("sigma1BuBu2D0rho_" + std::to_string(i)).c_str(), "",
        8.2450e+01);  //, 50, 150);  //,
    // 5, 15);
    RooRealVar sigma1FracBuBu2D0rho(
        ("sigma1FracBuBu2D0rho_" + std::to_string(i)).c_str(), "",
        9.0480e-01);  //, 0, 1);
    RooFormulaVar sigma2BuBu2D0rho(
        ("sigma2BuBu2D0rho_" + std::to_string(i)).c_str(), "", "@0*@1",
        RooArgSet(sigma1BuBu2D0rho, sigma1FracBuBu2D0rho));
    // // ---------------------------- Tails ----------------------------
    RooRealVar a1BuBu2D0rho(("a1BuBu2D0rho_" + std::to_string(i)).c_str(), "",
                            1.3201e+00);
    RooRealVar a2BuBu2D0rho(("a2BuBu2D0rho_" + std::to_string(i)).c_str(), "",
                            -4.2096e+00);
    RooRealVar n1BuBu2D0rho(("n1BuBu2D0rho_" + std::to_string(i)).c_str(), "",
                            5.0195e+01);
    RooRealVar n2BuBu2D0rho(("n2BuBu2D0rho_" + std::to_string(i)).c_str(), "",
                            3.8065e+00);
    // // ---------------------------- PDFs ----------------------------
    RooCBShape pdfBuBu2D0rho1(("pdfBuBu2D0rho1_" + std::to_string(i)).c_str(),
                              "", buMass, mean1BuBu2D0rho, sigma1BuBu2D0rho,
                              a1BuBu2D0rho, n1BuBu2D0rho);
    RooCBShape pdfBuBu2D0rho2(("pdfBuBu2D0rho2_" + std::to_string(i)).c_str(),
                              "", buMass, mean2BuBu2D0rho, sigma2BuBu2D0rho,
                              a2BuBu2D0rho, n2BuBu2D0rho);
    RooRealVar fracPdf1BuBu2D0rho(
        ("fracPdf1BuBu2D0rho_" + std::to_string(i)).c_str(), "", 4.9050e-01);
    RooAddPdf pdfBuBu2D0rho(("pdfBuBu2D0rho_" + std::to_string(i)).c_str(), "",
                            RooArgSet(pdfBuBu2D0rho1, pdfBuBu2D0rho2),
                            fracPdf1BuBu2D0rho);

    // ---------------------------- Yields ----------------------------
    RooRealVar yieldTotSignal(("yieldTotSignal_" + std::to_string(i)).c_str(),
                              "", 40000 * orEffSignal.getVal(), -100000,
                              100000);
    RooFormulaVar yieldBuSignal(
        ("yieldBuSignal_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(deltaCutEffSignal, orEffSignal, yieldTotSignal));
    RooFormulaVar yieldDeltaSignal(
        ("yieldDeltaSignal_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(buCutEffSignal, orEffSignal, yieldTotSignal));
    RooFormulaVar yieldSharedSignal(
        ("yieldSharedSignal_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(boxEffSignal, orEffSignal, yieldTotSignal));

    // // Bkg yields when using exponential
    // double nBuBkg = nBu - 40000 * deltaCutEffSignal.getVal();
    // double nDeltaBkg = nDelta - 40000 * buCutEffSignal.getVal();
    //
    // RooRealVar yieldBuBkg(("yieldBuBkg_" + std::to_string(i)).c_str(), "",
    //                       nBuBkg, 0, 100000);
    // RooRealVar yieldDeltaBkg(("yieldDeltaBkg_" +
    // std::to_string(i)).c_str(),
    //                          "", nDeltaBkg, 0, 100000);

    RooRealVar yieldFracB02Dstpi(("B02Dstpi_" + std::to_string(i)).c_str(), "",
                                 0.643);
    RooFormulaVar yieldTotB02Dstpi(
        ("yieldTotB02Dstpi_" + std::to_string(i)).c_str(), "", "@0*@1",
        RooArgList(yieldTotSignal, yieldFracB02Dstpi));
    RooFormulaVar yieldBuB02Dstpi(
        ("yieldBuB02Dstpi_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(deltaCutEffB02Dstpi, orEffB02Dstpi, yieldTotB02Dstpi));
    RooFormulaVar yieldDeltaB02Dstpi(
        ("yieldDeltaB02Dstpi_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(buCutEffB02Dstpi, orEffB02Dstpi, yieldTotB02Dstpi));
    RooFormulaVar yieldSharedB02Dstpi(
        ("yieldSharedB02Dstpi_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(boxEffB02Dstpi, orEffB02Dstpi, yieldTotB02Dstpi));

    RooRealVar yieldFracBu2D0rho(("Bu2D0rho_" + std::to_string(i)).c_str(), "",
                                 0.973);
    RooFormulaVar yieldTotBu2D0rho(
        ("yieldTotBu2D0rho_" + std::to_string(i)).c_str(), "", "@0*@1",
        RooArgList(yieldTotSignal, yieldFracBu2D0rho));
    RooFormulaVar yieldBuBu2D0rho(
        ("yieldBuBu2D0rho_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(deltaCutEffBu2D0rho, orEffBu2D0rho, yieldTotBu2D0rho));
    RooFormulaVar yieldDeltaBu2D0rho(
        ("yieldDeltaBu2D0rho_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(buCutEffBu2D0rho, orEffBu2D0rho, yieldTotBu2D0rho));
    RooFormulaVar yieldSharedBu2D0rho(
        ("yieldSharedBu2D0rho_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(boxEffBu2D0rho, orEffBu2D0rho, yieldTotBu2D0rho));

    // ---------------------------- Add PDFs and yields
    // ----------------------------

    RooArgSet yieldsDelta;
    yieldsDelta.add(yieldDeltaSignal);
    yieldsDelta.add(yieldDeltaB02Dstpi);
    yieldsDelta.add(yieldDeltaBu2D0rho);

    RooArgSet functionsDelta;
    functionsDelta.add(pdfDeltaSignal);
    functionsDelta.add(pdfDeltaB02Dstpi);
    functionsDelta.add(pdfDeltaBu2D0rho);
    RooAddPdf pdfDelta(("pdfDelta_" + std::to_string(i)).c_str(), "",
                       functionsDelta, yieldsDelta);

    RooArgSet yieldsBu;
    yieldsBu.add(yieldBuSignal);
    yieldsBu.add(yieldBuB02Dstpi);
    yieldsBu.add(yieldBuBu2D0rho);

    RooArgSet functionsBu;
    functionsBu.add(pdfBuSignal);
    functionsBu.add(pdfBuB02Dstpi);
    functionsBu.add(pdfBuBu2D0rho);
    RooAddPdf pdfBu(("pdfBu_" + std::to_string(i)).c_str(), "", functionsBu,
                    yieldsBu);

    if (fitDontSave == false) {
      RooRandom::randomGenerator()->SetSeed(0);
      TRandom3 random(0);

      double nEvtsPerToyBu = yieldBuSignal.getVal() + yieldBuB02Dstpi.getVal() +
                             yieldBuBu2D0rho.getVal();
      double nEvtsPerToyDelta = yieldDeltaSignal.getVal() +
                                yieldDeltaB02Dstpi.getVal() +
                                yieldDeltaBu2D0rho.getVal();
      // std::cout << "Generating toy dataset with " << nEvtsPerToy << "
      // events\n";

      // Generate bu and delta mass datasets separately from individual PDFs
      // Saving simPdf as one PDF reduces number of events by 1/2 in each
      // dimension
      // Saving each variable from simPdf doesn't work (not sure what it does!)
      // - completely flat in delta mass dimension (data has no structure)
      RooDataSet *buDataSet = pdfBu.generate(RooArgSet(buMass), nEvtsPerToyBu);
      std::cout << "Generated!\n";
      buDataSet->SetName("buDataSet");
      buDataSet->Print();

      RooDataSet *deltaDataSet =
          pdfDelta.generate(RooArgSet(deltaMass), nEvtsPerToyDelta);
      std::cout << "Generated!\n";
      deltaDataSet->SetName("deltaDataSet");
      deltaDataSet->Print();

      // RooDataSet *toyDataSet =
      //     simPdf.generate(RooArgSet(buMass, deltaMass, fitting),
      //     nEvtsPerToy);
      // toyDataSet->Print();

      double randomTag = random.Rndm();
      TFile dsFile((outputDir + "/DataFile1D_" + box_delta_low + "_" +
                    box_delta_high + "_" + box_bu_low + "_" + box_bu_high +
                    "_" + std::to_string(randomTag) + ".root")
                       .c_str(),
                   "RECREATE");
      buDataSet->Write("buDataSet");
      deltaDataSet->Write("deltaDataSet");
      dsFile.Close();
      std::cout << "Saved " << randomTag << " dataset\n";
    } else {
      if (!file_exists(filenames[i])) {
        std::cerr << filenames[i] << " does not exist.\n";
      } else {
        std::regex rexp(
            "DataFile([0-9])D_[0-9]+_[0-9]+_[0-9]+_[0-9]+_([0-9].[0-9]+).root");
        std::smatch match;
        std::regex_search(filenames[i], match, rexp);
        std::string dim = match[1];
        std::cout << "Dimension = " << dim << "\n";
        std::string rndm = match[2];
        // double nBu, nDelta;
        // ---------------------------- Read in toy dataset
        // ----------------------------
        RooDataSet combData = ExtractDataSetFromToy(
            filenames[i], dim, buMass, deltaMass, fitting, box_bu_low,
            box_bu_high, box_delta_low, box_delta_high);
        combData.Print();

        auto toyDataHist = std::unique_ptr<RooDataHist>(combData.binnedClone(
            ("toyDataHist_" + std::to_string(i)).c_str(), "toyDataHist"));
        auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());
        toyAbsData->SetName(("toyAbsData_" + std::to_string(i)).c_str());

        // ---------------------------- Construct Sim PDF
        // ----------------------------
        RooSimultaneous simPdf(("simPdf_" + std::to_string(i)).c_str(), "",
                               fitting);
        simPdf.addPdf(pdfDelta, "delta");
        simPdf.addPdf(pdfBu, "bu");

        // ---------------------------- Fit Sim PDF to toy
        // ----------------------------
        std::unique_ptr<RooFitResult> result = std::unique_ptr<RooFitResult>(
            simPdf.fitTo(*toyAbsData, RooFit::Extended(true),
                         RooFit::SplitRange(true), RooFit::Save(),
                         RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                         RooFit::Offset(true), RooFit::NumCPU(8, 2)));

        // if (i == 0) {
        //   std::cout << "Plotting projections of m[Bu]\n";
        //   PlotComponent(Variable::bu, buMass, toyDataHist.get(), simPdf,
        //                 fitting, pdfBuSignal, pdfBuB02Dstpi, pdfBuBu2D0rho,
        //                 outputDir, box_delta_low, box_delta_high, box_bu_low,
        //                 box_bu_high);
        //   std::cout << "Plotting projections of m[Delta]\n";
        //   PlotComponent(Variable::delta, deltaMass, toyDataHist.get(), simPdf,
        //                 fitting, pdfDeltaSignal, pdfDeltaB02Dstpi,
        //                 pdfDeltaBu2D0rho, outputDir, box_delta_low,
        //                 box_delta_high, box_bu_low, box_bu_high);
        //   std::cout << "Plotting correlation matrix\n";
        //   PlotCorrMatrix(result.get(), outputDir, box_delta_low, box_delta_high,
        //                  box_bu_low, box_bu_high);
        // }
        result->Print("v");

        // Essentially just fitErr * sqrt((boxEff * sqrt(2))^2 + (1-boxEff)^2)
        // double errYieldTotSignal =
        //     yieldTotSignal.getPropagatedError(*result) *
        //     ((yieldSharedSignal.getVal() / yieldTotSignal.getVal()) *
        //              std::sqrt(2)+
        //         1 - yieldSharedSignal.getVal() / yieldTotSignal.getVal());
        // std::cout << "Box = " << box_delta_low << "-" << box_delta_high <<
        // "
        // "
        //           << box_bu_low << "-" << box_bu_high << "\n";
        // std::cout << "yieldSharedSignal = " << yieldSharedSignal.getVal()
        // <<
        // " ± "
        //           << yieldSharedSignal.getPropagatedError(*result) << "\n";
        // std::cout << "yieldTotSignal = " << yieldTotSignal.getVal() << " ±
        // "
        //           << errYieldTotSignal << "\n";
        // std::cout << "Corrected error / fit Error = "
        //           << errYieldTotSignal /
        //                  yieldTotSignal.getPropagatedError(*result)
        //           << "\n";
        // std::cout << "Corrected error / fit Error = "
        //           << errYieldTotSignal / yieldTotSignal.getError() << "\n";
        TFile outputFile(
            (outputDir + "/Result_" + rndm + "_" + box_delta_low + "_" +
             box_delta_high + "_" + box_bu_low + "_" + box_bu_high + ".root")
                .c_str(),
            "recreate");
        outputFile.cd();
        result->SetName(("Result_" + rndm).c_str());
        result->Write();
        // Don't save corrected error for now - see if we can get error from
        // pulls
        // TTree tree("tree", "");
        // tree.Branch("errYieldTotSignal", &errYieldTotSignal,
        // "errYieldTotSignal/D");
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
}

int main(int argc, char *argv[]) {
  bool fitDontSave = true;

  if (argc < 7) {
    std::cerr << "Enter input file vector OR option: save, output directory "
                 "box limits: delta_low, delta_high, bu_low, bu_high, and if "
                 "saving nToys\n";
    return 1;
  }

  int nIter;
  std::vector<std::string> filenames;
  std::string input = argv[1];
  if (input == "save") {
    fitDontSave = false;
    if (argc < 8) {
      std::cerr
          << "Enter option: save, output directory "
             "box limits: delta_low, delta_high, bu_low, bu_high, and nToys\n";
      return 1;
    }
    nIter = std::atoi(argv[7]);
    std::cout << "RooDataSet will be created and saved to file.\n";
  } else {
    filenames = SplitByComma(input);
    nIter = filenames.size();
    std::cout << "RooDataSets will be fit to and results saved.\n";
  }

  std::string outputDir = argv[2];
  std::string box_delta_low = argv[3];
  std::string box_delta_high = argv[4];
  std::string box_bu_low = argv[5];
  std::string box_bu_high = argv[6];

  FitToys(fitDontSave, nIter, filenames, outputDir, box_delta_low,
          box_delta_high, box_bu_low, box_bu_high);

  return 0;
}
