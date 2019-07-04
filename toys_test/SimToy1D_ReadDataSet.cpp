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
            << "\tDelta OR Bu =\t" << nOr / nInitial << "\n";
}

void PlotComponent(Variable variable, RooRealVar &var, RooDataHist *dataHist,
                   RooSimultaneous &simPdf, RooCategory &fitting,
                   RooAddPdf &sig, RooAbsPdf &bkg, std::string const &outputDir,
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
      title = "m[D^{*0}#pi] - m[D^{*0}]";
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
      RooFit::ProjWData(fitting, *dataHist), RooFit::Components(bkg.GetName()),
      RooFit::LineColor(kRed), RooFit::LineStyle(kDashed));

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

RooDataSet ExtractDataSetFromToy(std::string const &input, RooRealVar &buMass,
                                 RooRealVar &deltaMass, RooCategory &fitting,
                                 std::string const &box_bu_low,
                                 std::string const &box_bu_high,
                                 std::string const &box_delta_low,
                                 std::string const &box_delta_high, double &nBu,
                                 double &nDelta) {
  RooDataSet *inputDataSet;
  TFile in(input.c_str(), "READ");
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
    throw std::runtime_error("Could not reduce inputDataSet with delta mass.");
  }
  auto dataBu = std::unique_ptr<RooDataSet>(
      dynamic_cast<RooDataSet *>(dataBu_tmp->reduce(RooArgSet(buMass))));
  if (dataBu.get() == nullptr) {
    throw std::runtime_error("Could not reduce inputDataSet to Bu mass.");
  }
  nBu = dataBu->numEntries();

  auto dataDelta_tmp = std::unique_ptr<RooDataSet>(
      dynamic_cast<RooDataSet *>(inputDataSet->reduce(
          ("Bu_Delta_M>" + box_bu_low + "&&Bu_Delta_M<" + box_bu_high)
              .c_str())));
  if (dataDelta_tmp.get() == nullptr) {
    throw std::runtime_error("Could not reduce inputDataSet with bu mass.");
  }
  auto dataDelta = std::unique_ptr<RooDataSet>(
      dynamic_cast<RooDataSet *>(dataDelta_tmp->reduce(RooArgSet(deltaMass))));
  if (dataDelta.get() == nullptr) {
    throw std::runtime_error("Could not reduce inputDataSet to Delta mass.");
  }
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
             std::string const &box_bu_high) {
  int bu_low = 5050;
  int bu_high = 5800;
  int delta_low = 60;  // 134;
  int delta_high = 210;

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
  RooRealVar orEffSignal("orEffSignal", "", 1);
  RooRealVar boxEffSignal("boxEffSignal", "", 1);
  RooRealVar deltaCutEffSignal("deltaCutEffSignal", "", 1);
  RooRealVar buCutEffSignal("buCutEffSignal", "", 1);

  ExtractBoxEfficiencies(Mode::Bu2Dst0pi_D0gamma, box_delta_low, box_delta_high,
                         box_bu_low, box_bu_high, boxEffSignal,
                         deltaCutEffSignal, buCutEffSignal, orEffSignal);

  // Loop over data files and perform 1D fit to each dataset
  for (unsigned int i = 0; i < filenames.size(); ++i) {
    if (!file_exists(filenames[i])) {
      std::cerr << filenames[i] << " does not exist.\n";
    } else {
      double nBu, nDelta;
      // ---------------------------- Read in toy dataset
      // ----------------------------
      RooDataSet combData = ExtractDataSetFromToy(
          filenames[i], buMass, deltaMass, fitting, box_bu_low, box_bu_high,
          box_delta_low, box_delta_high, nBu, nDelta);
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
          ("meanDeltaSignal_" + std::to_string(i)).c_str(), "", 1.4280e+02, 140,
          145);
      // ---------------------------- Sigmas ----------------------------
      RooRealVar sigmaDeltaSignal(
          ("sigmaDeltaSignal_" + std::to_string(i)).c_str(), "", 8.7003e+00, 5, 15);
          // 8.6601e+00, 5, 15);
      // ---------------------------- Tails ----------------------------
      RooRealVar a1DeltaSignal(("a1DeltaSignal_" + std::to_string(i)).c_str(),
                               "", 2.0640e+00);//, 0, 5);//1.9251e+00, 0, 5);
      RooRealVar a2DeltaSignal(("a2DeltaSignal_" + std::to_string(i)).c_str(),
                               "", -7.2834e-01, -5, -0.0001);//-7.4405e-01, -5, -0.0001);
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
      RooRealVar lambdaDeltaBkg(("lambdaDeltaBkg_" + std::to_string(i)).c_str(),
                                "", 0.01);//, -0.1, 0.1);
      RooExponential pdfDeltaBkg(("pdfDeltaBkg_" + std::to_string(i)).c_str(),
                                 "", deltaMass, lambdaDeltaBkg);

      // RooRealVar thresholdDeltaBkg(("thresholdDeltaBkg_" +
      // std::to_string(i)).c_str(), "", 4.7048e+01);
      // RooRealVar cDeltaBkg(("cDeltaBkg_" + std::to_string(i)).c_str(), "",
      // 6.2583e+01);
      // RooRealVar aDeltaBkg(("aDeltaBkg_" + std::to_string(i)).c_str(), "",
      // 8.1939e-01);
      // RooRealVar bDeltaBkg(("bDeltaBkg_" + std::to_string(i)).c_str(), "",
      // -7.9655e-01);
      // RooDstD0BG pdfDeltaBkg(("pdfDeltaBkg_" + std::to_string(i)).c_str(),
      // "", deltaMass, thresholdDeltaBkg,
      //                        cDeltaBkg, aDeltaBkg, bDeltaBkg);

      // ---------------------------- π/K shared PDFs: Bu
      // ----------------------------
      RooRealVar lambdaBuBkg(("lambdaBuBkg_" + std::to_string(i)).c_str(), "",
                             -0.005);//, -0.1, 0.1);
      RooExponential pdfBuBkg(("pdfBuBkg_" + std::to_string(i)).c_str(), "",
                              buMass, lambdaBuBkg);
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

      RooRealVar yieldTotSignal(("yieldTotSignal_" + std::to_string(i)).c_str(),
                                "", 40000 * orEffSignal.getVal(), 0, 100000);
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
      double nBuBkg = nBu - 40000 * deltaCutEffSignal.getVal();
      double nDeltaBkg = nDelta - 40000 * buCutEffSignal.getVal();

      RooRealVar yieldBuBkg(("yieldBuBkg_" + std::to_string(i)).c_str(), "",
                            nBuBkg);//, 0, 100000);
      RooRealVar yieldDeltaBkg(("yieldDeltaBkg_" + std::to_string(i)).c_str(),
                               "", nDeltaBkg);//, 0, 100000);

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
      std::regex rexp(".+_([0-9].[0-9]+).root");
      std::smatch match;
      std::regex_search(filenames[i], match, rexp);
      std::string rndm = match[1];
      TFile outputFile(
          (outputDir + "/Result_" + rndm + "_" + box_delta_low + "_" +
           box_delta_high + "_" + box_bu_low + "_" + box_bu_high + ".root")
              .c_str(),
          "recreate");
      outputFile.cd();
      result->SetName(("Result_" + rndm).c_str());
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
                 "delta_high, bu_low, bu_high\n";
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

  FitToys(filenames, outputDir, box_delta_low, box_delta_high, box_bu_low,
          box_bu_high);

  return 0;
}
