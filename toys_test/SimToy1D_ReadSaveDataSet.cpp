#include <fstream>
#include <iostream>
#include <map>
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
#include "RooCruijff.h"
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
#include "TLegend.h"
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
  Bu2Dst0pi_D0gamma_WN,
  Bu2Dst0pi_D0pi0,
  Bu2Dst0pi_D0pi0_WN,
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
    case Mode::Bu2Dst0pi_D0gamma_WN:
      return "Bu2Dst0pi_D0gamma_WN";
      break;
    case Mode::Bu2Dst0pi_D0pi0:
      return "Bu2Dst0pi_D0pi0";
      break;
    case Mode::Bu2Dst0pi_D0pi0_WN:
      return "Bu2Dst0pi_D0pi0_WN";
      break;
    case Mode::Bu2Dst0rho_D0gamma:
      return "Bu2Dst0rho_D0gamma";
      break;
    case Mode::Bu2Dst0rho_D0pi0:
      return "Bu2Dst0rho_D0pi0";
  }
}

std::string EnumToDirString(Mode mode) {
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
    case Mode::Bu2Dst0pi_D0gamma_WN:
      return "Bu2Dst0pi_D0gamma";
      break;
    case Mode::Bu2Dst0pi_D0pi0:
      return "Bu2Dst0pi_D0pi0";
      break;
    case Mode::Bu2Dst0pi_D0pi0_WN:
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
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToDirString(mode) +
      "_2011_MagUp/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2011_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_2(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToDirString(mode) +
      "_2011_MagDown/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2011_MagDown_BDT1_BDT2_PID_TM.root");
  std::string inputfile_3(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToDirString(mode) +
      "_2012_MagUp/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2012_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_4(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToDirString(mode) +
      "_2012_MagDown/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2012_MagDown_BDT1_BDT2_PID_TM.root");
  std::string inputfile_5(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToDirString(mode) +
      "_2015_MagUp/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2015_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_6(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToDirString(mode) +
      "_2015_MagDown/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2015_MagDown_BDT1_BDT2_PID_TM.root");
  std::string inputfile_7(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToDirString(mode) +
      "_2016_MagUp/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2016_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_8(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToDirString(mode) +
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

  if (mode != Mode::Bu2Dst0pi_D0pi0 && mode != Mode::Bu2Dst0pi_D0gamma &&
      mode != Mode::Bu2Dst0pi_D0pi0_WN && mode != Mode::Bu2Dst0pi_D0gamma_WN) {
    std::string inputfile_9(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToDirString(mode) +
        "_2015_MagUp/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
        "cross_feed_removed/" +
        EnumToString(mode) + "_2015_MagUp_BDT1_BDT2_PID_TM.root");
    std::string inputfile_10(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToDirString(mode) +
        "_ReDecay_2015_MagDown/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
        "cross_feed_removed/" +
        EnumToString(mode) + "_ReDecay_2015_MagDown_BDT1_BDT2_PID_TM.root");
    std::string inputfile_11(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToDirString(mode) +
        "_ReDecay_2016_MagUp/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
        "cross_feed_removed/" +
        EnumToString(mode) + "_ReDecay_2016_MagUp_BDT1_BDT2_PID_TM.root");
    std::string inputfile_12(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToDirString(mode) +
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
      "BDT1>0.05&&BDT2>0.05&&Delta_M>50&&Delta_M<190&&Bu_M_DTF_D0>5050&&Bu_M_"
      "DTF_D0<5800");
  double nDeltaWindow =
      chain.GetEntries(("BDT1>0.05&&BDT2>0.05&&Delta_M>50&&Delta_M<190&&Bu_M_"
                        "DTF_D0>5050&&Bu_M_DTF_D0<5800&&Delta_M>" +
                        box_delta_low + "&&Delta_M<" + box_delta_high)
                           .c_str());
  double nBuWindow =
      chain.GetEntries(("BDT1>0.05&&BDT2>0.05&&Delta_M>50&&Delta_M<190&&Bu_M_"
                        "DTF_D0>5050&&Bu_M_DTF_D0<5800&&Bu_Delta_M>" +
                        box_bu_low + "&&Bu_Delta_M<" + box_bu_high)
                           .c_str());
  double nBox = chain.GetEntries(
      ("BDT1>0.05&&BDT2>0.05&&Delta_M>50&&Delta_M<190&&Bu_M_DTF_D0>5050&&Bu_M_"
       "DTF_D0<5800&&Delta_M>" +
       box_delta_low + "&&Delta_M<" + box_delta_high + "&&Bu_Delta_M>" +
       box_bu_low + "&&Bu_Delta_M<" + box_bu_high)
          .c_str());
  double nOr = chain.GetEntries(
      ("BDT1>0.05&&BDT2>0.05&&Delta_M>50&&Delta_M<190&&Bu_M_DTF_D0>5050&&Bu_M_"
       "DTF_D0<5800&&((Delta_M>" +
       box_delta_low + "&&Delta_M<" + box_delta_high + ")||(Bu_Delta_M>" +
       box_bu_low + "&&Bu_Delta_M<" + box_bu_high + "))")
          .c_str());

  deltaCutEff.setVal(nDeltaWindow / nInitial);
  buCutEff.setVal(nBuWindow / nInitial);
  boxEff.setVal(nBox / nInitial);
  orEff.setVal(nOr / nInitial);

  std::cout << "Set efficiencies for " << EnumToString(mode) << " :\n"
            << "\tDelta Window =\t" << nDeltaWindow / nInitial
            << "\tBu Window =\t" << nBuWindow / nInitial << "\tBox =\t"
            << nBox / nInitial << "\n"
            << "\tDelta OR Bu =\t" << nOr / nInitial << "\n"
            << "\t# events initially =\t" << nInitial << "\n";
}

void PlotComponent(Variable variable, RooRealVar &var, RooDataHist *dataHist,
                   RooSimultaneous &simPdf, RooCategory &dimension,
                   RooAddPdf &sigPdf, RooAbsPdf &bkg1Pdf, RooAbsPdf &bkg2Pdf,
                   RooAbsPdf &bkg3Pdf, std::string const &outputDir,
                   std::string const &box_bu_low,
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
      title = "m[D^{*0}#pi] - m[D^{*0}] + m[D^{*0}]_{PDG}";
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
      RooFit::Cut(("dimension==dimension::" + EnumToString(variable)).c_str()));
  simPdf.plotOn(
      frame.get(), RooFit::Slice(dimension, EnumToString(variable).c_str()),
      RooFit::ProjWData(dimension, *dataHist), RooFit::LineColor(kBlue));
  pullHist = frame->RooPlot::pullHist();
  simPdf.plotOn(frame.get(),
                RooFit::Slice(dimension, EnumToString(variable).c_str()),
                RooFit::ProjWData(dimension, *dataHist),
                RooFit::Components(sigPdf.GetName()), RooFit::LineColor(kBlue),
                RooFit::LineStyle(kDashed));
  simPdf.plotOn(frame.get(),
                RooFit::Slice(dimension, EnumToString(variable).c_str()),
                RooFit::ProjWData(dimension, *dataHist),
                RooFit::Components(bkg1Pdf.GetName()),
                RooFit::LineColor(kOrange), RooFit::LineStyle(kDashed));
  simPdf.plotOn(frame.get(),
                RooFit::Slice(dimension, EnumToString(variable).c_str()),
                RooFit::ProjWData(dimension, *dataHist),
                RooFit::Components(bkg2Pdf.GetName()), RooFit::LineColor(kRed),
                RooFit::LineStyle(kDashed));
  simPdf.plotOn(frame.get(),
                RooFit::Slice(dimension, EnumToString(variable).c_str()),
                RooFit::ProjWData(dimension, *dataHist),
                RooFit::Components(bkg3Pdf.GetName()),
                RooFit::LineColor(kGreen), RooFit::LineStyle(kDashed));
  // simPdf.plotOn(
  //     frame.get(), RooFit::Slice(dimension, EnumToString(variable).c_str()),
  //     RooFit::ProjWData(dimension, *dataHist),
  //     RooFit::Components(bkg4Pdf.GetName()),
  //     RooFit::LineColor(kMagenta), RooFit::LineStyle(kDashed));

  dataHist->plotOn(
      frame.get(),
      RooFit::Cut(("dimension==dimension::" + EnumToString(variable)).c_str()));

  if (pullHist != 0) {
    pullFrame->addPlotable(pullHist /* .get() */, "P");
    pullFrame->SetName(("pullFrame_" + EnumToString(variable)).c_str());
    pullFrame->SetTitle("");
  }

  TLegend legend(0.71, 0.65, 0.95, 0.88);
  // ------------- Draw Legends -------------- //
  auto sigHist = std::make_unique<TH1D>(
      ("sigHist_" + EnumToString(variable)).c_str(), "sigHist", 1, 0, 1);
  sigHist->SetLineColor(kBlue);
  sigHist->SetLineStyle(kDashed);
  sigHist->SetLineWidth(2);
  auto bkg1Hist = std::make_unique<TH1D>(
      ("bkg1Hist_" + EnumToString(variable)).c_str(), "bkg1Hist", 1, 0, 1);
  bkg1Hist->SetLineColor(kOrange);
  bkg1Hist->SetLineStyle(kDashed);
  bkg1Hist->SetLineWidth(2);
  auto bkg2Hist = std::make_unique<TH1D>(
      ("bkg2Hist_" + EnumToString(variable)).c_str(), "bkg2Hist", 1, 0, 1);
  bkg2Hist->SetLineColor(kRed);
  bkg2Hist->SetLineStyle(kDashed);
  bkg2Hist->SetLineWidth(2);
  auto bkg3Hist = std::make_unique<TH1D>(
      ("bkg3Hist_" + EnumToString(variable)).c_str(), "bkg3Hist", 1, 0, 1);
  bkg3Hist->SetLineColor(kGreen);
  bkg3Hist->SetLineStyle(kDashed);
  bkg3Hist->SetLineWidth(2);
  // auto bkg4Hist = std::make_unique<TH1D>(
  //     ("bkg4Hist_" + EnumToString(variable)).c_str(), "bkg4Hist", 1, 0, 1);
  // bkg4Hist->SetLineColor(kMagenta);
  // bkg4Hist->SetLineStyle(kDashed);
  // bkg4Hist->SetLineWidth(2);

  legend.SetLineColor(kWhite);
  legend.AddEntry(sigHist.get(), sigPdf.GetName(), "l");
  legend.AddEntry(bkg1Hist.get(), bkg1Pdf.GetName(), "l");
  legend.AddEntry(bkg2Hist.get(), bkg2Pdf.GetName(), "l");
  legend.AddEntry(bkg3Hist.get(), bkg3Pdf.GetName(), "l");
  // legend.AddEntry(bkg4Hist.get(), bkg4Pdf.GetName(), "l");

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
  legend.Draw("same");
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
  corrCanvas.SaveAs((outputDir + "/1d_plots/CorrelationMatrix" + "_" +
                     box_delta_low + "_" + box_delta_high + "_" + box_bu_low +
                     "_" + box_bu_high + ".pdf")
                        .c_str());
}

RooDataSet ExtractDataSet(std::string const &input, std::string &dim,
                          RooRealVar &buMass, RooRealVar &deltaMass,
                          RooCategory &dimension, std::string const &box_bu_low,
                          std::string const &box_bu_high,
                          std::string const &box_delta_low,
                          std::string const &box_delta_high, bool toy, int it) {
  TFile in(input.c_str(), "READ");
  if (toy == true && dim == "1") {
    std::cout << "Extracting 1D toy dataset.\n";
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
    RooDataSet combData(("combData_" + std::to_string(it)).c_str(), "",
                        RooArgSet(buMass, deltaMass), RooFit::Index(dimension),
                        RooFit::Import("delta", *dataDelta),
                        RooFit::Import("bu", *dataBu));
    return combData;
    std::cout << "1D: returning combDataSet\n";
  } else {
    RooDataSet *inputDataSet;
    std::string rdsName;
    std::string cutString = "";
    if (toy == true) {
      std::cout << "Extracting 2D toy dataset.\n";
      rdsName = "toyDataSet";
    } else {
      std::cout << "Extracting 2D dataset with cuts applied.\n";
      rdsName = "inputDataSet";
      cutString =
          "&&BDT1>0.05&&BDT2>0.05&&bach_PIDK<12&&((abs(h1_D_ID)==211&&h1_D_"
          "PIDK<"
          "-2)||(abs(h1_D_ID)==321&&h1_D_PIDK>2))&&((abs(h2_D_ID)==211&&h2_D_"
          "PIDK<-2)||(abs(h2_D_ID)==321&&h2_D_PIDK>2))";
    }
    gDirectory->GetObject(rdsName.c_str(), inputDataSet);
    if (inputDataSet == nullptr) {
      throw std::runtime_error("Data set does not exist.");
    } else {
      std::cout << "inputDataSet extracted... \n";
      inputDataSet->Print();
    }
    auto dataBu_tmp = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
        inputDataSet->reduce(("Delta_M>" + box_delta_low + "&&Delta_M<" +
                              box_delta_high + cutString)
                                 .c_str())));
    std::cout << "Formula compiled\n";
    if (dataBu_tmp.get() == nullptr) {
      throw std::runtime_error(
          "Could not reduce inputDataSet with delta mass.");
    }
    auto dataBu = std::unique_ptr<RooDataSet>(
        dynamic_cast<RooDataSet *>(dataBu_tmp->reduce(RooArgSet(buMass))));
    if (dataBu.get() == nullptr) {
      throw std::runtime_error("Could not reduce inputDataSet to Bu mass.");
    }
    dataBu->Print();

    auto dataDelta_tmp = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
        inputDataSet->reduce(("Bu_Delta_M>" + box_bu_low + "&&Bu_Delta_M<" +
                              box_bu_high + cutString)
                                 .c_str())));
    if (dataDelta_tmp.get() == nullptr) {
      throw std::runtime_error("Could not reduce inputDataSet with bu mass.");
    }
    auto dataDelta = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
        dataDelta_tmp->reduce(RooArgSet(deltaMass))));
    if (dataDelta.get() == nullptr) {
      throw std::runtime_error("Could not reduce inputDataSet to Delta mass.");
    }
    dataDelta->Print();

    RooDataSet combData(("combData_" + std::to_string(it)).c_str(), "",
                        RooArgSet(buMass, deltaMass), RooFit::Index(dimension),
                        RooFit::Import("bu", *dataBu.get()),
                        RooFit::Import("delta", *dataDelta.get()));
    combData.Print();
    return combData;
    std::cout << "2D: returning combDataSet\n";
  }
}

void FitToys(bool fitDontSave, int &nIter,
             std::vector<std::string> const &filenames,
             std::string const &outputDir, std::string const &box_delta_low,
             std::string const &box_delta_high, std::string const &box_bu_low,
             std::string const &box_bu_high, bool toy) {
  int bu_low = 5050;
  int bu_high = 5800;
  int delta_low = 70;  // 134;
  int delta_high = 190;

  int bu_nbins = (bu_high - bu_low) / 10;
  int delta_nbins = (delta_high - delta_low) / 2;

  // ---------------------------- dimension Vars ----------------------------
  RooRealVar buMass("Bu_Delta_M",
                    "m[D^{*0}#pi^{#pm}] - m[D^{*0}] + m[D^{*0}]_{PDG}", bu_low,
                    bu_high, "MeV/c^{2}");
  RooRealVar deltaMass("Delta_M", "m[D^{*0}] - m[D^{0}]", delta_low, delta_high,
                       "MeV/c^{2}");

  buMass.setBins(bu_nbins);
  deltaMass.setBins(delta_nbins);

  // ---------------------------- Categories ----------------------------
  RooCategory dimension("dimension", "dimension");
  dimension.defineType("bu");
  dimension.defineType("delta");

  // ---------------------------- Yield Starting points
  // ----------------------------
  double initYieldSig = 40000;
  double initYieldBu2Dst0pi_D0pi0 = initYieldSig * 0.916;
  double fracMisRec_Bu2Dst0pi_D0gamma_WN = 0.473;
  double fracMisRec_Bu2Dst0pi_D0pi0_WN = 0.809;
  double fracMisRec_Bd2Dstpi = 0.643;
  double fracMisRec_Bu2D0rho = 0.973;
  double fracMisRec = fracMisRec_Bu2Dst0pi_D0gamma_WN +
                      fracMisRec_Bu2Dst0pi_D0pi0_WN + fracMisRec_Bd2Dstpi +
                      fracMisRec_Bu2D0rho;
  double initYieldMisRec = initYieldSig * (fracMisRec);
  double initYieldBu2D0pi = initYieldSig * (1.54);
  // double initYieldBu2Dst0pi_D0pi0_WN = initYieldSig * 0.809;
  // double initYieldBd2Dstpi = initYieldSig * 0.643;
  // double initYieldBu2D0rho = initYieldSig * 0.973;

  // ---------------------------- Efficiencies ----------------------------
  // Outside of loop as all datasets have same box dimensions
  RooRealVar orEffSignal("orEffSignal", "", 1);
  RooRealVar boxEffSignal("boxEffSignal", "", 1);
  RooRealVar deltaCutEffSignal("deltaCutEffSignal", "", 1);
  RooRealVar buCutEffSignal("buCutEffSignal", "", 1);

  ExtractBoxEfficiencies(Mode::Bu2Dst0pi_D0gamma, box_delta_low, box_delta_high,
                         box_bu_low, box_bu_high, boxEffSignal,
                         deltaCutEffSignal, buCutEffSignal, orEffSignal);

  RooRealVar orEffBu2Dst0pi_D0pi0("orEffBu2Dst0pi_D0pi0", "", 1);
  RooRealVar boxEffBu2Dst0pi_D0pi0("boxEffBu2Dst0pi_D0pi0", "", 1);
  RooRealVar deltaCutEffBu2Dst0pi_D0pi0("deltaCutEffBu2Dst0pi_D0pi0", "", 1);
  RooRealVar buCutEffBu2Dst0pi_D0pi0("buCutEffBu2Dst0pi_D0pi0", "", 1);

  ExtractBoxEfficiencies(Mode::Bu2Dst0pi_D0pi0, box_delta_low, box_delta_high,
                         box_bu_low, box_bu_high, boxEffBu2Dst0pi_D0pi0,
                         deltaCutEffBu2Dst0pi_D0pi0, buCutEffBu2Dst0pi_D0pi0,
                         orEffBu2Dst0pi_D0pi0);

  double orEffMisRecVal = 0.0;
  double boxEffMisRecVal = 0.0;
  double deltaCutEffMisRecVal = 0.0;
  double buCutEffMisRecVal = 0.0;

  std::map<Mode, double> misRecModesMap = {
      {Mode::Bu2Dst0pi_D0pi0_WN, fracMisRec_Bu2Dst0pi_D0pi0_WN / fracMisRec},
      {Mode::Bu2Dst0pi_D0gamma_WN,
       fracMisRec_Bu2Dst0pi_D0gamma_WN / fracMisRec},
      {Mode::Bu2D0rho, fracMisRec_Bu2D0rho / fracMisRec},
      {Mode::Bd2Dstpi, fracMisRec_Bd2Dstpi / fracMisRec}};

  for (auto &m : misRecModesMap) {
    RooRealVar orEffTemp("orEffTemp", "", 1);
    RooRealVar boxEffTemp("boxEffTemp", "", 1);
    RooRealVar deltaCutEffTemp("deltaCutEffTemp", "", 1);
    RooRealVar buCutEffTemp("buCutEffTemp", "", 1);

    ExtractBoxEfficiencies(m.first, box_delta_low, box_delta_high, box_bu_low,
                           box_bu_high, boxEffTemp, deltaCutEffTemp,
                           buCutEffTemp, orEffTemp);

    orEffMisRecVal += orEffTemp.getVal() * m.second;
    boxEffMisRecVal += boxEffTemp.getVal() * m.second;
    deltaCutEffMisRecVal += deltaCutEffTemp.getVal() * m.second;
    buCutEffMisRecVal += buCutEffTemp.getVal() * m.second;
  }

  RooRealVar orEffMisRec("orEffMisRec", "", orEffMisRecVal);
  RooRealVar boxEffMisRec("boxEffMisRec", "", boxEffMisRecVal);
  RooRealVar deltaCutEffMisRec("deltaCutEffMisRec", "", deltaCutEffMisRecVal);
  RooRealVar buCutEffMisRec("buCutEffMisRec", "", buCutEffMisRecVal);

  std::cout << "Set MisRec efficiencies :\n"
            << "\tDelta Window =\t" << deltaCutEffMisRec.getVal()
            << "\tBu Window =\t" << buCutEffMisRec.getVal() << "\tBox =\t"
            << boxEffMisRec.getVal() << "\n"
            << "\tDelta OR Bu =\t" << orEffMisRec.getVal() << "\n";

  RooRealVar orEffBu2D0pi("orEffBu2D0pi", "", 1);
  RooRealVar boxEffBu2D0pi("boxEffBu2D0pi", "", 1);
  RooRealVar deltaCutEffBu2D0pi("deltaCutEffBu2D0pi", "", 1);
  RooRealVar buCutEffBu2D0pi("buCutEffBu2D0pi", "", 1);

  ExtractBoxEfficiencies(Mode::Bu2D0pi, box_delta_low, box_delta_high,
                         box_bu_low, box_bu_high, boxEffBu2D0pi,
                         deltaCutEffBu2D0pi, buCutEffBu2D0pi, orEffBu2D0pi);

  // Loop over data files and perform 1D fit to each dataset
  for (int i = 0; i < nIter; ++i) {
    // ---------------------------- Yields ----------------------------
    RooRealVar yieldTotSignal(("yieldTotSignal_" + std::to_string(i)).c_str(),
                              "", initYieldSig * orEffSignal.getVal(), -100000,
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

    RooRealVar yieldTotBu2Dst0pi_D0pi0(
        ("yieldTotBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        initYieldBu2Dst0pi_D0pi0 * orEffBu2Dst0pi_D0pi0.getVal(), -100000,
        100000);
    RooFormulaVar yieldBuBu2Dst0pi_D0pi0(
        ("yieldBuBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        "(@0/@1)*@2",
        RooArgList(deltaCutEffBu2Dst0pi_D0pi0, orEffBu2Dst0pi_D0pi0,
                   yieldTotBu2Dst0pi_D0pi0));
    RooFormulaVar yieldDeltaBu2Dst0pi_D0pi0(
        ("yieldDeltaBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        "(@0/@1)*@2", RooArgList(buCutEffBu2Dst0pi_D0pi0, orEffBu2Dst0pi_D0pi0,
                                 yieldTotBu2Dst0pi_D0pi0));
    RooFormulaVar yieldSharedBu2Dst0pi_D0pi0(
        ("yieldSharedBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        "(@0/@1)*@2", RooArgList(boxEffBu2Dst0pi_D0pi0, orEffBu2Dst0pi_D0pi0,
                                 yieldTotBu2Dst0pi_D0pi0));

    RooRealVar yieldTotMisRec(("yieldTotMisRec_" + std::to_string(i)).c_str(),
                              "", initYieldMisRec * orEffMisRec.getVal(),
                              -100000, 100000);
    RooFormulaVar yieldBuMisRec(
        ("yieldBuMisRec_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(deltaCutEffMisRec, orEffMisRec, yieldTotMisRec));
    RooFormulaVar yieldDeltaMisRec(
        ("yieldDeltaMisRec_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(buCutEffMisRec, orEffMisRec, yieldTotMisRec));
    RooFormulaVar yieldSharedMisRec(
        ("yieldSharedMisRec_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(boxEffMisRec, orEffMisRec, yieldTotMisRec));

    RooRealVar yieldTotBu2D0pi(("yieldTotBu2D0pi_" + std::to_string(i)).c_str(),
                               "", initYieldBu2D0pi * orEffBu2D0pi.getVal(),
                               -100000, 100000);
    RooFormulaVar yieldBuBu2D0pi(
        ("yieldBuBu2D0pi_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(deltaCutEffBu2D0pi, orEffBu2D0pi, yieldTotBu2D0pi));
    RooFormulaVar yieldDeltaBu2D0pi(
        ("yieldDeltaBu2D0pi_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(buCutEffBu2D0pi, orEffBu2D0pi, yieldTotBu2D0pi));
    RooFormulaVar yieldSharedBu2D0pi(
        ("yieldSharedBu2D0pi_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(boxEffBu2D0pi, orEffBu2D0pi, yieldTotBu2D0pi));

    // ---------------------------- PDFs ----------------------------
    // ---------------------------- Signal ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanDeltaSignal(("meanDeltaSignal_" + std::to_string(i)).c_str(),
                               "",
                               1.4233e+02, 135, 150);
    // meanDeltaSignal.setVal(meanDeltaVal);
    // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaDeltaSignal(
        ("sigmaDeltaSignal_" + std::to_string(i)).c_str(), "",
        8.1675e+00, 2, 15);
    // sigmaDeltaSignal.setVal(sigmaDeltaVal);
    // ---------------------------- Tails ----------------------------
    RooRealVar a1DeltaSignal(("a1DeltaSignal_" + std::to_string(i)).c_str(), "",
                             1.5109e+00);  //, 0, 5);
    RooRealVar a2DeltaSignal(("a2DeltaSignal_" + std::to_string(i)).c_str(), "",
                             -5.7023e-01);  //, -5, -0.001);
    RooRealVar n1DeltaSignal(("n1DeltaSignal_" + std::to_string(i)).c_str(), "",
                             6.0060e+00);  //, 0, 10);
    RooRealVar n2DeltaSignal(("n2DeltaSignal_" + std::to_string(i)).c_str(), "",
                             7.8408e+00);  //, 0, 10);
    // ---------------------------- PDFs ----------------------------
    RooCBShape pdfDeltaSignal1(("pdfDeltaSignal1_" + std::to_string(i)).c_str(),
                               "", deltaMass, meanDeltaSignal, sigmaDeltaSignal,
                               a1DeltaSignal, n1DeltaSignal);
    RooCBShape pdfDeltaSignal2(("pdfDeltaSignal2_" + std::to_string(i)).c_str(),
                               "", deltaMass, meanDeltaSignal, sigmaDeltaSignal,
                               a2DeltaSignal, n2DeltaSignal);
    RooRealVar fracPdf1DeltaSignal(
        ("fracPdf1DeltaSignal_" + std::to_string(i)).c_str(), "", 2.6638e-01);
    RooAddPdf pdfDeltaSignal(("pdfDeltaSignal_" + std::to_string(i)).c_str(),
                             "", RooArgSet(pdfDeltaSignal1, pdfDeltaSignal2),
                             fracPdf1DeltaSignal);

    // ---------------------------- PDFs: Bu ----------------------------
    // ---------------------------- Signal ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanBuSignal(("meanBuSignal_" + std::to_string(i)).c_str(), "",
                            5.2819e+03, 5275, 5290);
    // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaBuSignal(("sigmaBuSignal_" + std::to_string(i)).c_str(), "",
                             2.0051e+01, 15, 30);  //, 300, 400);

    // ---------------------------- Tails ----------------------------
    RooRealVar a1BuSignal(("a1BuSignal_" + std::to_string(i)).c_str(), "",
                          1.6184e+00);  // 0, 5);
    RooRealVar a2BuSignal(("a2BuSignal_" + std::to_string(i)).c_str(), "",
                          -1.6623e+00);  // -5, -0.0001);
    RooRealVar n1BuSignal(("n1BuSignal_" + std::to_string(i)).c_str(), "",
                          8.6469e+00);  // 0, 10);
    RooRealVar n2BuSignal(("n2BuSignal_" + std::to_string(i)).c_str(), "",
                          5.2563e+00);  // 0, 10);
    // ---------------------------- PDFs ----------------------------
    RooRealVar fracPdf1BuSignal(
        ("fracPdf1BuSignal_" + std::to_string(i)).c_str(), "", 6.8457e-01);
    RooCBShape pdfBuSignal1(("pdfBuSignal1_" + std::to_string(i)).c_str(), "",
                            buMass, meanBuSignal, sigmaBuSignal, a1BuSignal,
                            n1BuSignal);
    RooCBShape pdfBuSignal2(("pdfBuSignal2_" + std::to_string(i)).c_str(), "",
                            buMass, meanBuSignal, sigmaBuSignal, a2BuSignal,
                            n2BuSignal);
    RooAddPdf pdfBuSignal(("pdfBuSignal_" + std::to_string(i)).c_str(), "",
                          RooArgSet(pdfBuSignal1, pdfBuSignal2),
                          fracPdf1BuSignal);

    // ---------------------------- Bu2Dst0pi_D0pi0 ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanDeltaBu2Dst0pi_D0pi0(
        ("meanDeltaBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        8.6075e+01, 80, 90);
    // meanDeltaBu2Dst0pi_D0pi0.setVal(meanDeltaVal);
    // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaDeltaBu2Dst0pi_D0pi0(
        ("sigmaDeltaBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        9.2845e+00, 2, 15);
    // sigmaDeltaBu2Dst0pi_D0pi0.setVal(sigmaDeltaVal);
    // ---------------------------- Tails ----------------------------
    RooRealVar a1DeltaBu2Dst0pi_D0pi0(
        ("a1DeltaBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        4.2812e-01);  //, 0, 5);
    RooRealVar a2DeltaBu2Dst0pi_D0pi0(
        ("a2DeltaBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        -7.3982e-01);  //, -5, -0.001);
    RooRealVar n1DeltaBu2Dst0pi_D0pi0(
        ("n1DeltaBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        9.9912e+01);  //, 0, 10);
    RooRealVar n2DeltaBu2Dst0pi_D0pi0(
        ("n2DeltaBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        7.0288e+00);  //, 0, 10);
    // ---------------------------- PDFs ----------------------------
    RooCBShape pdfDeltaBu2Dst0pi_D0pi01(
        ("pdfDeltaBu2Dst0pi_D0pi01_" + std::to_string(i)).c_str(), "",
        deltaMass, meanDeltaBu2Dst0pi_D0pi0, sigmaDeltaBu2Dst0pi_D0pi0,
        a1DeltaBu2Dst0pi_D0pi0, n1DeltaBu2Dst0pi_D0pi0);
    RooCBShape pdfDeltaBu2Dst0pi_D0pi02(
        ("pdfDeltaBu2Dst0pi_D0pi02_" + std::to_string(i)).c_str(), "",
        deltaMass, meanDeltaBu2Dst0pi_D0pi0, sigmaDeltaBu2Dst0pi_D0pi0,
        a2DeltaBu2Dst0pi_D0pi0, n2DeltaBu2Dst0pi_D0pi0);
    RooRealVar fracPdf1DeltaBu2Dst0pi_D0pi0(
        ("fracPdf1DeltaBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        2.9911e-01);
    RooAddPdf pdfDeltaBu2Dst0pi_D0pi0(
        ("pdfDeltaBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        RooArgSet(pdfDeltaBu2Dst0pi_D0pi01, pdfDeltaBu2Dst0pi_D0pi02),
        fracPdf1DeltaBu2Dst0pi_D0pi0);

    // ---------------------------- PDFs: Bu ----------------------------
    // ---------------------------- Bu2Dst0pi_D0pi0 ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanBuBu2Dst0pi_D0pi0(
        ("meanBuBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        5.3431e+03);  //, 5300, 5400);
    // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaBuBu2Dst0pi_D0pi0(
        ("sigmaBuBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        4.6911e+01);  //, 15, 50);

    // ---------------------------- Tails ----------------------------
    RooRealVar aBuBu2Dst0pi_D0pi0(
        ("aBuBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        9.8213e-01);  // 0, 5);
    RooRealVar nBuBu2Dst0pi_D0pi0(
        ("nBuBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        10);  // 0, 100);
    // ---------------------------- PDFs ----------------------------
    RooCBShape pdfBuBu2Dst0pi_D0pi0(
        ("pdfBuBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "", buMass,
        meanBuBu2Dst0pi_D0pi0, sigmaBuBu2Dst0pi_D0pi0, aBuBu2Dst0pi_D0pi0,
        nBuBu2Dst0pi_D0pi0);

    // ---------------------------- Mis-Reconstructed Background
    // ----------------------------
    RooRealVar thresholdDeltaMisRec(
        ("thresholdDeltaMisRec_" + std::to_string(i)).c_str(), "",
        5.7223e+01);  //, 40, 70);
    RooRealVar cDeltaMisRec(("cDeltaMisRec_" + std::to_string(i)).c_str(), "",
                            3.1867e+01);  //, 0, 100);
    RooRealVar aDeltaMisRec(("aDeltaMisRec_" + std::to_string(i)).c_str(), "",
                            1.2396e+00);  //, -2, 2);
    RooRealVar bDeltaMisRec(("bDeltaMisRec_" + std::to_string(i)).c_str(), "",
                            -1.7973e+00);  //, -2, 2);
    RooDstD0BG pdfDeltaMisRec(("pdfDeltaMisRec_" + std::to_string(i)).c_str(),
                              "", deltaMass, thresholdDeltaMisRec, cDeltaMisRec,
                              aDeltaMisRec, bDeltaMisRec);
    // ---------------------------- π/K shared PDFs: Bu
    // ----------------------------
    // // ---------------------------- Mean ----------------------------
    RooRealVar meanBuMisRec(("meanBuMisRec_" + std::to_string(i)).c_str(), "",
                            5.2991e+03, 5280, 5310);
    // // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaBuMisRec(("sigmaBuMisRec_" + std::to_string(i)).c_str(), "",
                             9.4812e+01, 80, 110);
    // ---------------------------- Tails ----------------------------
    RooRealVar aBuMisRec(("aBuMisRec_" + std::to_string(i)).c_str(), "",
                         2.6265e+00);  // 0, 5);
    RooRealVar nBuMisRec(("nBuMisRec_" + std::to_string(i)).c_str(), "",
                         9.9921e-01);  // 0, 100);
    // ---------------------------- PDFs ----------------------------
    RooCBShape pdfBuMisRec(("pdfBuMisRec_" + std::to_string(i)).c_str(), "",
                           buMass, meanBuMisRec, sigmaBuMisRec, aBuMisRec,
                           nBuMisRec);

    // // ---------------------------- Mean ----------------------------
    // RooRealVar meanBuMisRec(("meanBuMisRec_" + std::to_string(i)).c_str(),
    // "",
    //                     5.3164e+03);  //, 5280, 5310);
    // // // ---------------------------- Sigmas ----------------------------
    // RooRealVar sigmaLBuMisRec(("sigmaLBuMisRec_" +
    // std::to_string(i)).c_str(), "",
    //                      1.1455e+02);  //, 50, 100);
    // RooRealVar sigmaRBuMisRec(("sigmaRBuMisRec_" +
    // std::to_string(i)).c_str(), "",
    //                      8.5687e+01);  //, 50, 100);
    // // ---------------------------- Tails ----------------------------
    // RooRealVar aLBuMisRec(("aLBuMisRec_" + std::to_string(i)).c_str(), "",
    //                  2.4412e-05);  // 0, 5);
    // RooRealVar aRBuMisRec(("aRBuMisRec_" + std::to_string(i)).c_str(), "",
    //                  1.8396e-07);  // 0, 100);
    // // ---------------------------- PDFs ----------------------------
    // RooCruijff pdfBuMisRec(("pdfBuMisRec_" + std::to_string(i)).c_str(), "",
    // buMass,
    //                    meanBuMisRec, sigmaLBuMisRec, aLBuMisRec, aRBuMisRec);

    // ---------------------------- Bu2D0pi Background
    // ----------------------------
    RooRealVar thresholdDeltaBu2D0pi(
        ("thresholdDeltaBu2D0pi_" + std::to_string(i)).c_str(), "",
        6.7773e+01);  //, 40, 70);
    RooRealVar cDeltaBu2D0pi(("cDeltaBu2D0pi_" + std::to_string(i)).c_str(), "",
                             6.2156e+01);  //, 0, 100);
    RooRealVar aDeltaBu2D0pi(("aDeltaBu2D0pi_" + std::to_string(i)).c_str(), "",
                             5.8996e-01);  //, -2, 2);
    RooRealVar bDeltaBu2D0pi(("bDeltaBu2D0pi_" + std::to_string(i)).c_str(), "",
                             -5.6691e-01);  //, -2, 2);
    RooDstD0BG pdfDeltaBu2D0pi(("pdfDeltaBu2D0pi_" + std::to_string(i)).c_str(),
                               "", deltaMass, thresholdDeltaBu2D0pi,
                               cDeltaBu2D0pi, aDeltaBu2D0pi, bDeltaBu2D0pi);
    // ---------------------------- π/K shared PDFs: Bu
    // ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanBuBu2D0pi(("meanBuBu2D0pi_" + std::to_string(i)).c_str(), "",
                             5.5263e+03);//, 5500, 5550);
    // // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaLBuBu2D0pi(("sigmaLBuBu2D0pi_" + std::to_string(i)).c_str(),
                               "",
                               8.8227e+01);//, 70, 100);
    RooRealVar sigmaRBuBu2D0pi(("sigmaRBuBu2D0pi_" + std::to_string(i)).c_str(),
                               "",
                               7.6224e+01);//, 70, 100);
    // ---------------------------- Tails ----------------------------
    RooRealVar aLBuBu2D0pi(("aLBuBu2D0pi_" + std::to_string(i)).c_str(), "",
                           6.7243e-09);  // 0, 5);
    RooRealVar aRBuBu2D0pi(("aRBuBu2D0pi_" + std::to_string(i)).c_str(), "",
                           2.1226e-11);  // 0, 100);
    // ---------------------------- PDFs ----------------------------
    RooCruijff pdfBuBu2D0pi(("pdfBuBu2D0pi_" + std::to_string(i)).c_str(), "",
                            buMass, meanBuBu2D0pi, sigmaLBuBu2D0pi, aLBuBu2D0pi,
                            aRBuBu2D0pi);

    // ---------------------------- Add PDFs and yields
    // ----------------------------

    RooArgSet yieldsDelta;
    yieldsDelta.add(yieldDeltaSignal);
    yieldsDelta.add(yieldDeltaBu2Dst0pi_D0pi0);
    yieldsDelta.add(yieldDeltaMisRec);
    yieldsDelta.add(yieldDeltaBu2D0pi);

    RooArgSet functionsDelta;
    functionsDelta.add(pdfDeltaSignal);
    functionsDelta.add(pdfDeltaBu2Dst0pi_D0pi0);
    functionsDelta.add(pdfDeltaMisRec);
    functionsDelta.add(pdfDeltaBu2D0pi);
    RooAddPdf pdfDelta(("pdfDelta_" + std::to_string(i)).c_str(), "",
                       functionsDelta, yieldsDelta);

    RooArgSet yieldsBu;
    yieldsBu.add(yieldBuSignal);
    yieldsBu.add(yieldBuBu2Dst0pi_D0pi0);
    yieldsBu.add(yieldBuMisRec);
    yieldsBu.add(yieldBuBu2D0pi);

    RooArgSet functionsBu;
    functionsBu.add(pdfBuSignal);
    functionsBu.add(pdfBuBu2Dst0pi_D0pi0);
    functionsBu.add(pdfBuMisRec);
    functionsBu.add(pdfBuBu2D0pi);
    RooAddPdf pdfBu(("pdfBu_" + std::to_string(i)).c_str(), "", functionsBu,
                    yieldsBu);

    // ---------------------------- Construct Sim PDF
    // ----------------------------
    RooSimultaneous simPdf(("simPdf_" + std::to_string(i)).c_str(), "",
                           dimension);
    simPdf.addPdf(pdfDelta, "delta");
    simPdf.addPdf(pdfBu, "bu");

    if (toy == false) {
      std::string dim = "2";
      std::vector<RooDataSet> dsVec;
      std::cout << "Number of datasets = " << filenames.size() << "\n";
      for (unsigned int f = 0; f < filenames.size(); ++f) {
        dsVec.emplace_back(ExtractDataSet(
            filenames[f], dim, buMass, deltaMass, dimension, box_bu_low,
            box_bu_high, box_delta_low, box_delta_high, toy, f));
      }
      std::cout << "Entries in dsVec = " << dsVec.size() << "\n";
      RooDataSet combData = dsVec[0];
      for (unsigned int d = 0; d < dsVec.size()-1; ++d) {
        combData.append(dsVec[d+1]);
      }
      std::cout << "Appended roodatasets" << std::endl;
      combData.Print();

      auto dataHist = std::unique_ptr<RooDataHist>(combData.binnedClone(
          ("dataHist_" + std::to_string(i)).c_str(), "dataHist"));
      auto absData = dynamic_cast<RooAbsData *>(dataHist.get());
      absData->SetName(("absData_" + std::to_string(i)).c_str());

      std::unique_ptr<RooFitResult> result =
          std::unique_ptr<RooFitResult>(simPdf.fitTo(
              *absData, RooFit::Extended(true), RooFit::SplitRange(true),
              RooFit::Save(), RooFit::Strategy(2),
              RooFit::Minimizer("Minuit2"),
              RooFit::Offset(true), RooFit::NumCPU(8, 2)));

      std::cout << "Plotting projections of m[Bu]\n";
      PlotComponent(Variable::bu, buMass, dataHist.get(), simPdf, dimension,
                    pdfBuSignal, pdfBuBu2Dst0pi_D0pi0, pdfBuMisRec,
                    pdfBuBu2D0pi, outputDir, box_delta_low, box_delta_high,
                    box_bu_low, box_bu_high);
      std::cout << "Plotting projections of m[Delta]\n";
      PlotComponent(Variable::delta, deltaMass, dataHist.get(), simPdf,
                    dimension, pdfDeltaSignal, pdfDeltaBu2Dst0pi_D0pi0,
                    pdfDeltaMisRec, pdfDeltaBu2D0pi, outputDir,
                    box_delta_low,
                    box_delta_high, box_bu_low, box_bu_high);
      std::cout << "Plotting correlation matrix\n";
      PlotCorrMatrix(result.get(), outputDir, box_delta_low, box_delta_high,
                     box_bu_low, box_bu_high);

      result->Print("v");

      double errYieldTotSignal =
          yieldTotSignal.getPropagatedError(*result) *
          ((yieldSharedSignal.getVal() / yieldTotSignal.getVal()) *
               std::sqrt(2) +
           1 - yieldSharedSignal.getVal() / yieldTotSignal.getVal());
      std::cout << "yieldSharedSignal = " << yieldSharedSignal.getVal() << " ± "
                << yieldSharedSignal.getPropagatedError(*result) << "\n";
      std::cout << "yieldTotSignal = " << yieldTotSignal.getVal() << " ± "
                << errYieldTotSignal << "\n";
      std::cout << "Corrected error / fit Error = "
                << errYieldTotSignal /
                       yieldTotSignal.getPropagatedError(*result)
                << "\n";

    } else {
      if (fitDontSave == false) {
        RooRandom::randomGenerator()->SetSeed(0);
        TRandom3 random(0);

        double nEvtsPerToyBu = yieldBuSignal.getVal() +
                               yieldBuBu2Dst0pi_D0pi0.getVal() +
                               yieldBuMisRec.getVal() + yieldBuBu2D0pi.getVal();
        double nEvtsPerToyDelta =
            yieldDeltaSignal.getVal() + yieldDeltaBu2Dst0pi_D0pi0.getVal() +
            yieldDeltaMisRec.getVal() + yieldDeltaBu2D0pi.getVal();
        // std::cout << "Generating toy dataset with " << nEvtsPerToy << "
        // events\n";

        // Generate bu and delta mass datasets separately from individual PDFs
        // Saving simPdf as one PDF reduces number of events by 1/2 in each
        // dimension
        // Saving each variable from simPdf doesn't work (not sure what it
        // does!)
        // - completely flat in delta mass dimension (data has no structure)
        RooDataSet *buDataSet =
            pdfBu.generate(RooArgSet(buMass), nEvtsPerToyBu);
        std::cout << "Generated!\n";
        buDataSet->SetName("buDataSet");
        buDataSet->Print();

        RooDataSet *deltaDataSet =
            pdfDelta.generate(RooArgSet(deltaMass), nEvtsPerToyDelta);
        std::cout << "Generated!\n";
        deltaDataSet->SetName("deltaDataSet");
        deltaDataSet->Print();

        // RooDataSet *toyDataSet =
        //     simPdf.generate(RooArgSet(buMass, deltaMass, dimension),
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
              "DataFile([0-9])D_[0-9]+_[0-9]+_[0-9]+_[0-9]+_([0-9].[0-9]+)."
              "root");
          std::smatch match;
          std::regex_search(filenames[i], match, rexp);
          std::string dim = match[1];
          std::cout << "Dimension = " << dim << "\n";
          std::string rndm = match[2];
          // double nBu, nDelta;
          // ---------------------------- Read in toy dataset
          // ----------------------------
          int it = 0;
          RooDataSet combData = ExtractDataSet(
              filenames[i], dim, buMass, deltaMass, dimension, box_bu_low,
              box_bu_high, box_delta_low, box_delta_high, toy, it);
          combData.Print();

          auto toyDataHist = std::unique_ptr<RooDataHist>(combData.binnedClone(
              ("toyDataHist_" + std::to_string(i)).c_str(), "toyDataHist"));
          auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());
          toyAbsData->SetName(("toyAbsData_" + std::to_string(i)).c_str());

          // ---------------------------- Fit Sim PDF to toy
          // ----------------------------
          std::unique_ptr<RooFitResult> result = std::unique_ptr<RooFitResult>(
              simPdf.fitTo(*toyAbsData, RooFit::Extended(true),
                           RooFit::SplitRange(true), RooFit::Save(),
                           RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                           RooFit::Offset(true), RooFit::NumCPU(8, 2)));

          if (i == 0) {
            std::cout << "Plotting projections of m[Bu]\n";
            PlotComponent(Variable::bu, buMass, toyDataHist.get(), simPdf,
                          dimension, pdfBuSignal, pdfBuBu2Dst0pi_D0pi0,
                          pdfBuMisRec, pdfBuBu2D0pi, outputDir, box_delta_low,
                          box_delta_high, box_bu_low, box_bu_high);
            std::cout << "Plotting projections of m[Delta]\n";
            PlotComponent(Variable::delta, deltaMass, toyDataHist.get(), simPdf,
                          dimension, pdfDeltaSignal, pdfDeltaBu2Dst0pi_D0pi0,
                          pdfDeltaMisRec, pdfDeltaBu2D0pi, outputDir,
                          box_delta_low, box_delta_high, box_bu_low,
                          box_bu_high);
            std::cout << "Plotting correlation matrix\n";
            PlotCorrMatrix(result.get(), outputDir, box_delta_low,
                           box_delta_high, box_bu_low, box_bu_high);
          }
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
}

int main(int argc, char *argv[]) {
  bool fitDontSave = true;
  bool toy = true;

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
    if (argc < 8) {
      std::cerr << "Enter input file vector, "
                   "output directory "
                   "box limits: delta_low, delta_high, bu_low, bu_high, "
                   "roodataset type: toy/data\n";
      return 1;
    }
    filenames = SplitByComma(input);
    std::cout << "RooDataSets will be fit to and results saved.\n";
    std::string dsType = argv[7];
    if (dsType == "toy") {
      std::cout << "Fitting to toy datasets.\n";
      nIter = filenames.size();
    } else if (dsType == "data") {
      std::cout << "Fitting to data.\n";
      toy = false;
      nIter = 1;
    } else {
      std::cerr
          << "8th argument must be toy/data when fitting to RooDataSets.\n";
      return 1;
    }
  }

  std::string outputDir = argv[2];
  std::string box_delta_low = argv[3];
  std::string box_delta_high = argv[4];
  std::string box_bu_low = argv[5];
  std::string box_bu_high = argv[6];

  FitToys(fitDontSave, nIter, filenames, outputDir, box_delta_low,
          box_delta_high, box_bu_low, box_bu_high, toy);

  return 0;
}
