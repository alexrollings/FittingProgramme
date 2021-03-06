#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooCBShape.h"
#include "RooCategory.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooDstD0BG.h"
#include "RooExponential.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooHist.h"
#include "RooPlot.h"
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
#include "TLine.h"
#include "TPad.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TTreeReader.h"

enum class Mode { Bu2Dst0pi_D0gamma, Bu2Dst0pi_D0pi0 };
enum class Variable { buGamma, buPartial, delta };

std::string EnumToString(Mode mode) {
  switch (mode) {
    case Mode::Bu2Dst0pi_D0gamma:
      return "Bu2Dst0pi_D0gamma";
      break;
    case Mode::Bu2Dst0pi_D0pi0:
      return "Bu2Dst0pi_D0pi0";
      break;
    default:
      return " ";
      break;
  }
}

std::string EnumToString(Variable variable) {
  switch (variable) {
    case Variable::buGamma:
      return "buGamma";
      break;
    case Variable::buPartial:
      return "buPartial";
      break;
    case Variable::delta:
      return "delta";
      break;
    default:
      return " ";
  }
}

void GetDataMapAndBoxEff(
    Mode mode, RooRealVar &buMass, RooRealVar &deltaMass,
    std::map<std::string, RooDataSet *> &mapCategoryDataSet,
    RooRealVar &deltaBoxEff, RooRealVar &buBoxEff_asGamma,
    RooRealVar &buBoxEff_asPartial, RooRealVar &orEff) {
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

  chain.GetEntry(0);
  TTreeReader reader(&chain);

  TTreeReaderValue<int> Bu_BKGCAT(reader, "Bu_BKGCAT");
  TTreeReaderValue<double> Delta_M(reader, "Delta_M");
  TTreeReaderValue<double> Bu_Delta_M(reader, "Bu_Delta_M");
  TTreeReaderValue<double> D0_M(reader, "D0_M");
  TTreeReaderValue<double> D0h_M(reader, "D0h_M");
  TTreeReaderValue<double> D0_M_DOUBLESW_KP(reader, "D0_M_DOUBLESW_KP");
  TTreeReaderValue<float> BDT1(reader, "BDT1");
  TTreeReaderValue<float> BDT2(reader, "BDT2");
  TTreeReaderValue<double> bach_PIDK_corr(reader, "bach_PIDK_corr");
  TTreeReaderValue<double> D0_FD_ZSIG(reader, "D0_FD_ZSIG");

  TFile file("tree_file.root", "RECREATE");

  TTree *newTree = dynamic_cast<TTree *>(chain.GetTree()->CloneTree(0));
  if (newTree == nullptr) {
    throw std::runtime_error("File did not contain ttree.");
  }

  int i = 0;

  while (reader.Next()) {
    chain.GetEntry(i);
    i++;
    if (*BDT2 > 0.05 && *BDT1 > 0.05 && abs(*D0_M - 1864) < 25 &&
        *Delta_M > 50 && *Delta_M < 190 && *Bu_Delta_M > 4900 &&
        *Bu_Delta_M < 5800 && *bach_PIDK_corr < 12 &&
        abs(*D0_M_DOUBLESW_KP - 1864) > 15 && *D0_FD_ZSIG > 2 &&
        *D0h_M > 4900) {
      newTree->Fill();
    }
  }

  RooDataSet dataset("dataset", "dataset", newTree,
                     RooArgSet(buMass, deltaMass));

  std::string buBoxLow = "5240";
  std::string buBoxHigh = "5320";
  std::string deltaBoxLow_asGamma = "125";
  std::string deltaBoxHigh_asGamma = "170";
  std::string deltaBoxLow_asPartial = "60";
  std::string deltaBoxHigh_asPartial = "105";

  RooDataSet *buGammaDataSet = nullptr;
  buGammaDataSet = dynamic_cast<RooDataSet *>(dataset.reduce(
      ("Delta_M>" + deltaBoxLow_asGamma + "&&Delta_M<" + deltaBoxHigh_asGamma)
          .c_str()));
  if (buGammaDataSet == nullptr) {
    throw std::runtime_error("Could not reduce bu data with box cuts.");
  }

  if (mapCategoryDataSet.find(EnumToString(Variable::buGamma)) ==
      mapCategoryDataSet.end()) {
    mapCategoryDataSet.insert(
        std::make_pair(EnumToString(Variable::buGamma), buGammaDataSet));
    std::cout << "Created key-value pair for category " +
                     EnumToString(Variable::buGamma) +
                     " and corresponding dataset for MC of " +
                     EnumToString(mode) + "\n";
  } else {
    mapCategoryDataSet[EnumToString(Variable::buGamma)]->append(
        *buGammaDataSet);
    std::cout << "Appended dataset for MC of " + EnumToString(mode) +
                     " to category " + EnumToString(Variable::buGamma) + "\n";
  }

  RooDataSet *buPartialDataSet = nullptr;
  buPartialDataSet = dynamic_cast<RooDataSet *>(
      dataset.reduce(("Delta_M>" + deltaBoxLow_asPartial + "&&Delta_M<" +
                      deltaBoxHigh_asPartial)
                         .c_str()));
  if (buPartialDataSet == nullptr) {
    throw std::runtime_error("Could not reduce bu data with box cuts.");
  }

  if (mapCategoryDataSet.find(EnumToString(Variable::buPartial)) ==
      mapCategoryDataSet.end()) {
    mapCategoryDataSet.insert(
        std::make_pair(EnumToString(Variable::buPartial), buPartialDataSet));
    std::cout << "Created key-value pair for category " +
                     EnumToString(Variable::buPartial) +
                     " and corresponding dataset for MC of " +
                     EnumToString(mode) + "\n";
  } else {
    mapCategoryDataSet[EnumToString(Variable::buPartial)]->append(
        *buPartialDataSet);
    std::cout << "Appended dataset for MC of " + EnumToString(mode) +
                     " to category " + EnumToString(Variable::buPartial) + "\n";
  }

  RooDataSet *deltaDataSet = nullptr;
  deltaDataSet = dynamic_cast<RooDataSet *>(dataset.reduce(
      ("Bu_Delta_M>" + buBoxLow + "&&Bu_Delta_M<" + buBoxHigh).c_str()));
  if (deltaDataSet == nullptr) {
    throw std::runtime_error("Could not reduce delta data with box cuts.");
  }

  if (mapCategoryDataSet.find(EnumToString(Variable::delta)) ==
      mapCategoryDataSet.end()) {
    mapCategoryDataSet.insert(
        std::make_pair(EnumToString(Variable::delta), deltaDataSet));
    std::cout << "Created key-value pair for category " +
                     EnumToString(Variable::delta) +
                     " and corresponding dataset for MC of " +
                     EnumToString(mode) + "\n";
    ;

  } else {
    mapCategoryDataSet[EnumToString(Variable::delta)]->append(*deltaDataSet);
    std::cout << "Appended dataset for MC of " + EnumToString(mode) +
                     " to category " + EnumToString(Variable::delta) + "\n";
  }

  double nInitial = newTree->GetEntries();
  double nBuWindow = newTree->GetEntries(
      ("Bu_Delta_M>" + buBoxLow + "&&Bu_Delta_M<" + buBoxHigh).c_str());
  double nDeltaWindow_asGamma = newTree->GetEntries(
      ("Delta_M>" + deltaBoxLow_asGamma + "&&Delta_M<" + deltaBoxHigh_asGamma)
          .c_str());
  double nDeltaWindow_asPartial =
      newTree->GetEntries(("Delta_M>" + deltaBoxLow_asPartial + "&&Delta_M<" +
                           deltaBoxHigh_asPartial)
                              .c_str());
  double nOr = newTree->GetEntries(
      ("(Delta_M>" + deltaBoxLow_asGamma + "&&Delta_M<" + deltaBoxHigh_asGamma +
       ")||(Bu_Delta_M>" + buBoxLow + "&&Bu_Delta_M<" + buBoxHigh +
       ")||(Delta_M>" + deltaBoxLow_asPartial + "&&Delta_M<" +
       deltaBoxHigh_asPartial + ")")
          .c_str());

  deltaBoxEff.setVal(nBuWindow / nInitial);
  buBoxEff_asGamma.setVal(nDeltaWindow_asGamma / nInitial);
  buBoxEff_asPartial.setVal(nDeltaWindow_asPartial / nInitial);
  orEff.setVal(nOr / nInitial);

  std::cout << "# events initially =\t" << nInitial << "\n"
            << "Set efficiencies for " << EnumToString(mode) << " :\n"
            << "\tBu Window =\t" << nBuWindow / nInitial << "\n"
            << "\tDelta Window as gamma =\t" << nDeltaWindow_asGamma / nInitial
            << "\tDelta Window as partial =\t"
            << nDeltaWindow_asPartial / nInitial
            << "\tDelta OR BuGamma OR BuPartial =\t" << nOr / nInitial << "\n";
}

void PlotComponent(Variable variable, RooRealVar &var, RooDataHist dataHist,
                   RooSimultaneous &simPdf, RooCategory &fitting,
                   RooAbsPdf &pdfGamma, RooAbsPdf &pdfPi0) {
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
    case Variable::buGamma:
      title = "m[D^{*0}#pi] - m[D^{*0}] + m[D^{*0}]_{PDG}";
      break;
    case Variable::buPartial:
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

  dataHist.plotOn(
      frame.get(),
      RooFit::Cut(("fitting==fitting::" + EnumToString(variable)).c_str()));
  simPdf.plotOn(frame.get(),
                RooFit::Slice(fitting, EnumToString(variable).c_str()),
                RooFit::ProjWData(fitting, dataHist),
                RooFit::Components(pdfGamma.GetName()),
                RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed));
  simPdf.plotOn(frame.get(),
                RooFit::Slice(fitting, EnumToString(variable).c_str()),
                RooFit::ProjWData(fitting, dataHist),
                RooFit::Components(pdfPi0.GetName()),
                RooFit::LineColor(kOrange), RooFit::LineStyle(kDashed));
  simPdf.plotOn(frame.get(),
                RooFit::Slice(fitting, EnumToString(variable).c_str()),
                RooFit::ProjWData(fitting, dataHist), RooFit::LineColor(kBlue));
  pullHist = frame->RooPlot::pullHist();

  dataHist.plotOn(
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
  canvas.SaveAs(("TripleToy_" + EnumToString(variable) + "Mass.pdf").c_str());
}

void SimToy() {
  // TApplication app("app", 0, 0);
  int buLow = 4900;
  int buHigh = 5800;
  int deltaLow = 60;
  int deltaHigh = 190;

  int bu_nbins = (buHigh - buLow) / 10;
  int delta_nbins = (deltaHigh - deltaLow) / 2;

  // ---------------------------- Fitting Vars ----------------------------
  RooRealVar buMass("Bu_Delta_M",
                    "m[D^{*0}#pi^{#pm}] - m[D^{*0}] + m[D^{*0}]_{PDG}", buLow,
                    buHigh, "MeV/c^{2}");
  RooRealVar deltaMass("Delta_M", "m[D^{*0}] - m[D^{0}]", deltaLow, deltaHigh,
                       "MeV/c^{2}");

  buMass.setBins(bu_nbins);
  deltaMass.setBins(delta_nbins);

  // DEFINE INDEX CATEGORIES
  RooCategory fitting("fitting", "fitting");
  fitting.defineType(EnumToString(Variable::buPartial).c_str());
  fitting.defineType(EnumToString(Variable::buGamma).c_str());
  fitting.defineType(EnumToString(Variable::delta).c_str());

  std::map<std::string, RooDataSet *> mapCategoryDataSet;

  RooRealVar deltaBoxEff_D0gamma("deltaBoxEff_D0gamma", "deltaBoxEff_D0gamma",
                                 1);
  RooRealVar buBoxEff_D0gamma_asGamma("buBoxEff_D0gamma_asGamma",
                                      "buBoxEff_D0gamma_asGamma", 1);
  RooRealVar buBoxEff_D0gamma_asPartial("buBoxEff_D0gamma_asPartial",
                                        "buBoxEff_D0gamma_asPartial", 1);
  RooRealVar orEff_D0gamma("orEff_D0gamma", "orEff_D0gamma", 1);

  GetDataMapAndBoxEff(Mode::Bu2Dst0pi_D0gamma, buMass, deltaMass,
                      mapCategoryDataSet, deltaBoxEff_D0gamma,
                      buBoxEff_D0gamma_asGamma, buBoxEff_D0gamma_asPartial,
                      orEff_D0gamma);

  RooRealVar deltaBoxEff_D0pi0("deltaBoxEff_D0pi0", "deltaBoxEff_D0pi0", 1);
  RooRealVar buBoxEff_D0pi0_asGamma("buBoxEff_D0pi0_asGamma",
                                    "buBoxEff_D0pi0_asGamma", 1);
  RooRealVar buBoxEff_D0pi0_asPartial("buBoxEff_D0pi0_asPartial",
                                      "buBoxEff_D0pi0_asPartial", 1);
  RooRealVar orEff_D0pi0("orEff_D0pi0", "orEff_D0pi0", 1);

  GetDataMapAndBoxEff(Mode::Bu2Dst0pi_D0pi0, buMass, deltaMass,
                      mapCategoryDataSet, deltaBoxEff_D0pi0,
                      buBoxEff_D0pi0_asGamma, buBoxEff_D0pi0_asPartial,
                      orEff_D0pi0);

  RooDataSet combData("combData", "", RooArgSet(buMass, deltaMass),
                      RooFit::Index(fitting),
                      RooFit::Import(mapCategoryDataSet));

  combData.Print();

  auto dataHist = std::unique_ptr<RooDataHist>(
      combData.binnedClone("dataHist", "dataHist"));
  if (dataHist == nullptr) {
    throw std::runtime_error("Could not extact binned dataSet.");
  }
  auto absData = dynamic_cast<RooAbsData *>(dataHist.get());
  if (absData == nullptr) {
    throw std::runtime_error("Could not cast to RooAbsData.");
  }

  RooRealVar meanDelta_D0gamma("meanDelta_D0gamma", "", 1.4278e+02, 130, 150);
  RooRealVar sigmaDelta_D0gamma("sigmaDelta_D0gamma", "", 8.4695e+00, 2, 15);
  RooRealVar a1Delta_D0gamma("a1Delta_D0gamma", "", 1.7506e+00);
  RooRealVar n1Delta_D0gamma("n1Delta_D0gamma", "", 1.1606e+00);
  RooRealVar a2Delta_D0gamma("a2Delta_D0gamma", "", -7.8889e-01);
  RooRealVar n2Delta_D0gamma("n2Delta_D0gamma", "", 4.1928e+00);
  RooCBShape pdf1Delta_D0gamma("pdf1Delta_D0gamma", "", deltaMass,
                               meanDelta_D0gamma, sigmaDelta_D0gamma,
                               a1Delta_D0gamma, n1Delta_D0gamma);
  RooCBShape pdf2Delta_D0gamma("pdf2Delta_D0gamma", "", deltaMass,
                               meanDelta_D0gamma, sigmaDelta_D0gamma,
                               a2Delta_D0gamma, n2Delta_D0gamma);
  RooRealVar fracPdf1Delta_D0gamma("fracPdf1Delta_D0gamma",
                                   "Fraction of component 1 in delta PDF",
                                   1.5408e-01);
  RooAddPdf pdfDelta_D0gamma("pdfDelta_D0gamma", "",
                             RooArgSet(pdf1Delta_D0gamma, pdf2Delta_D0gamma),
                             fracPdf1Delta_D0gamma);

  RooRealVar meanDelta_D0pi0("meanDelta_D0pi0", "", 8.6503e+01, 70, 100);
  RooRealVar sigmaDelta_D0pi0("sigmaDelta_D0pi0", "", 9.3347e+00, 5, 15);
  RooRealVar a1Delta_D0pi0("a1Delta_D0pi0", "", 5.7073e-01);
  RooRealVar n1Delta_D0pi0("n1Delta_D0pi0", "", 9.9988e+01);
  RooRealVar a2Delta_D0pi0("a2Delta_D0pi0", "", -8.3282e-01);
  RooRealVar n2Delta_D0pi0("n2Delta_D0pi0", "", 3.7808e+00);
  RooCBShape pdf1Delta_D0pi0("pdf1Delta_D0pi0", "", deltaMass, meanDelta_D0pi0,
                             sigmaDelta_D0pi0, a1Delta_D0pi0, n1Delta_D0pi0);
  RooCBShape pdf2Delta_D0pi0("pdf2Delta_D0pi0", "", deltaMass, meanDelta_D0pi0,
                             sigmaDelta_D0pi0, a2Delta_D0pi0, n2Delta_D0pi0);
  RooRealVar fracPdf1Delta_D0pi0("fracPdf1Delta_D0pi0",
                                 "Fraction of component 1 in delta PDF",
                                 3.0618e-01);
  RooAddPdf pdfDelta_D0pi0("pdfDelta_D0pi0", "",
                           RooArgSet(pdf1Delta_D0pi0, pdf2Delta_D0pi0),
                           fracPdf1Delta_D0pi0);

  RooRealVar meanBu_D0gamma_asGamma("meanBu_D0gamma_asGamma", "",
                                    5.2814e+03);  //, 5275, 5285);
  RooRealVar sigmaBu_D0gamma_asGamma("sigmaBu_D0gamma_asGamma", "",
                                     2.0271e+01);  //, 15, 30);
  RooRealVar a1Bu_D0gamma_asGamma("a1Bu_D0gamma_asGamma", "", 1.6184e+00);
  RooRealVar n1Bu_D0gamma_asGamma("n1Bu_D0gamma_asGamma", "", 8.6469e+00);
  RooRealVar a2Bu_D0gamma_asGamma("a2Bu_D0gamma_asGamma", "", -1.6623e+00);
  RooRealVar n2Bu_D0gamma_asGamma("n2Bu_D0gamma_asGamma", "", 10);
  RooCBShape pdf1Bu_D0gamma_asGamma(
      "pdf1Bu_D0gamma_asGamma", "", buMass, meanBu_D0gamma_asGamma,
      sigmaBu_D0gamma_asGamma, a1Bu_D0gamma_asGamma, n1Bu_D0gamma_asGamma);
  RooCBShape pdf2Bu_D0gamma_asGamma(
      "pdf2Bu_D0gamma_asGamma", "", buMass, meanBu_D0gamma_asGamma,
      sigmaBu_D0gamma_asGamma, a2Bu_D0gamma_asGamma, n2Bu_D0gamma_asGamma);
  RooRealVar fracPdf1Bu_D0gamma_asGamma("fracPdf1Bu_D0gamma_asGamma",
                                        "Fraction of component 1 in bu PDF",
                                        6.8457e-01);
  RooAddPdf pdfBu_D0gamma_asGamma(
      "pdfBu_D0gamma_asGamma", "",
      RooArgSet(pdf1Bu_D0gamma_asGamma, pdf2Bu_D0gamma_asGamma),
      fracPdf1Bu_D0gamma_asGamma);

  RooRealVar meanBu_D0pi0_asGamma("meanBu_D0pi0_asGamma", "", 5.3454e+03);
  RooRealVar sigmaBu_D0pi0_asGamma("sigmaBu_D0pi0_asGamma", "", 4.3979e+01);
  RooRealVar aBu_D0pi0_asGamma("aBu_D0pi0_asGamma", "", 8.2093e-01);
  RooRealVar nBu_D0pi0_asGamma("nBu_D0pi0_asGamma", "", 10);
  RooCBShape pdfBu_D0pi0_asGamma("pdfBu_D0pi0_asGamma", "", buMass,
                                 meanBu_D0pi0_asGamma, sigmaBu_D0pi0_asGamma,
                                 aBu_D0pi0_asGamma, nBu_D0pi0_asGamma);

  RooRealVar meanBu_D0gamma_asPartial("meanBu_D0gamma_asPartial", "",
                                      5.2600e+03);
  RooRealVar sigmaBu_D0gamma_asPartial("sigmaBu_D0gamma_asPartial", "",
                                       3.0651e+01);
  RooRealVar aBu_D0gamma_asPartial("aBu_D0gamma_asPartial", "", 2.5357e+00);
  RooRealVar nBu_D0gamma_asPartial("nBu_D0gamma_asPartial", "", 6.4103e-08);
  RooCBShape pdfBu_D0gamma_asPartial(
      "pdfBu_D0gamma_asPartial", "", buMass, meanBu_D0gamma_asPartial,
      sigmaBu_D0gamma_asPartial, aBu_D0gamma_asPartial, nBu_D0gamma_asPartial);

  RooRealVar meanBu_D0pi0_asPartial("meanBu_D0pi0_asPartial", "",
                                    5.2910e+03);  //, 5275, 5285);
  RooRealVar sigma1Bu_D0pi0_asPartial("sigma1Bu_D0pi0_asPartial", "",
                                      2.8223e+01);  //, 15, 30);
  RooRealVar sigma2Bu_D0pi0_asPartial("sigma2Bu_D0pi0_asPartial", "",
                                      4.7212e+01);  //, 15, 30);
  RooRealVar a1Bu_D0pi0_asPartial("a1Bu_D0pi0_asPartial", "", 1.2671e+00);
  RooRealVar n1Bu_D0pi0_asPartial("n1Bu_D0pi0_asPartial", "", 10);
  RooRealVar a2Bu_D0pi0_asPartial("a2Bu_D0pi0_asPartial", "", -4.6116e+00);
  RooRealVar n2Bu_D0pi0_asPartial("n2Bu_D0pi0_asPartial", "", 3.1306e+00);
  RooCBShape pdf1Bu_D0pi0_asPartial(
      "pdf1Bu_D0pi0_asPartial", "", buMass, meanBu_D0pi0_asPartial,
      sigma1Bu_D0pi0_asPartial, a1Bu_D0pi0_asPartial, n1Bu_D0pi0_asPartial);
  RooCBShape pdf2Bu_D0pi0_asPartial(
      "pdf2Bu_D0pi0_asPartial", "", buMass, meanBu_D0pi0_asPartial,
      sigma2Bu_D0pi0_asPartial, a2Bu_D0pi0_asPartial, n2Bu_D0pi0_asPartial);
  RooRealVar fracPdf1Bu_D0pi0_asPartial("fracPdf1Bu_D0pi0_asPartial",
                                        "Fraction of component 1 in bu PDF",
                                        6.6392e-01);
  RooAddPdf pdfBu_D0pi0_asPartial(
      "pdfBu_D0pi0_asPartial", "",
      RooArgSet(pdf1Bu_D0pi0_asPartial, pdf2Bu_D0pi0_asPartial),
      fracPdf1Bu_D0pi0_asPartial);

  RooRealVar N_D0gamma("N_D0gamma", "", 1.2279e+04, 0, 20000);
  RooFormulaVar N_Delta_D0gamma(
      "N_Delta_D0gamma", "(@0/@1)*@2",
      RooArgList(deltaBoxEff_D0gamma, orEff_D0gamma, N_D0gamma));
  RooFormulaVar N_BuGamma_D0gamma(
      "N_BuGamma_D0gamma", "(@0/@1)*@2",
      RooArgList(buBoxEff_D0gamma_asGamma, orEff_D0gamma, N_D0gamma));
  RooFormulaVar N_BuPartial_D0gamma(
      "N_BuPartial_D0gamma", "(@0/@1)*@2",
      RooArgList(buBoxEff_D0gamma_asPartial, orEff_D0gamma, N_D0gamma));

  RooRealVar N_D0pi0("N_D0pi0", "", 7000, 0, 15000);
  RooFormulaVar N_Delta_D0pi0(
      "N_Delta_D0pi0", "(@0/@1)*@2",
      RooArgList(deltaBoxEff_D0pi0, orEff_D0pi0, N_D0pi0));
  RooFormulaVar N_BuGamma_D0pi0(
      "N_BuGamma_D0pi0", "(@0/@1)*@2",
      RooArgList(buBoxEff_D0pi0_asGamma, orEff_D0pi0, N_D0pi0));
  RooFormulaVar N_BuPartial_D0pi0(
      "N_BuPartial_D0pi0", "(@0/@1)*@2",
      RooArgList(buBoxEff_D0pi0_asPartial, orEff_D0pi0, N_D0pi0));

  RooArgSet functionsBuGamma;
  functionsBuGamma.add(pdfBu_D0gamma_asGamma);
  functionsBuGamma.add(pdfBu_D0pi0_asGamma);
  RooArgSet yieldsBuGamma;
  yieldsBuGamma.add(N_BuGamma_D0gamma);
  yieldsBuGamma.add(N_BuGamma_D0pi0);
  RooAddPdf pdfBuGamma("pdfBuGamma", "", functionsBuGamma, yieldsBuGamma);

  RooArgSet functionsBuPartial;
  functionsBuPartial.add(pdfBu_D0gamma_asPartial);
  functionsBuPartial.add(pdfBu_D0pi0_asPartial);
  RooArgSet yieldsBuPartial;
  yieldsBuPartial.add(N_BuPartial_D0gamma);
  yieldsBuPartial.add(N_BuPartial_D0pi0);
  RooAddPdf pdfBuPartial("pdfBuPartial", "", functionsBuPartial,
                         yieldsBuPartial);

  RooArgSet functionsDelta;
  functionsDelta.add(pdfDelta_D0gamma);
  functionsDelta.add(pdfDelta_D0pi0);
  RooArgSet yieldsDelta;
  yieldsDelta.add(N_Delta_D0gamma);
  yieldsDelta.add(N_Delta_D0pi0);
  RooAddPdf pdfDelta("pdfDelta", "", functionsDelta, yieldsDelta);

  RooSimultaneous simPdf("simPdf", "", fitting);
  simPdf.addPdf(pdfBuGamma, EnumToString(Variable::buGamma).c_str());
  simPdf.addPdf(pdfBuPartial, EnumToString(Variable::buPartial).c_str());
  simPdf.addPdf(pdfDelta, EnumToString(Variable::delta).c_str());

  std::unique_ptr<RooFitResult> result = std::unique_ptr<RooFitResult>(
      simPdf.fitTo(*absData, RooFit::Extended(kTRUE), RooFit::Save(),
                   RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                   RooFit::Offset(true), RooFit::NumCPU(8, 2)));

  PlotComponent(Variable::buGamma, buMass, *dataHist.get(), simPdf, fitting,
                pdfBu_D0gamma_asGamma, pdfBu_D0pi0_asGamma);
  PlotComponent(Variable::buPartial, buMass, *dataHist.get(), simPdf, fitting,
                pdfBu_D0gamma_asPartial, pdfBu_D0pi0_asPartial);
  PlotComponent(Variable::delta, deltaMass, *dataHist.get(), simPdf, fitting,
                pdfDelta_D0gamma, pdfDelta_D0pi0);

  result->Print("v");
  // app.Run(true);
}

int main() {
  SimToy();
  return 0;
}
