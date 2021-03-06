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
                   std::string const &outputDir,
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
  canvas.SaveAs(
      (outputDir + "/1d_plots/" + EnumToString(variable) + "_" +
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
                 box_delta_low + "_" + box_delta_high + "_" + box_bu_low + "_" +
                 box_bu_high + ".pdf")
                    .c_str());

}

bool fexists(std::string const &filename) {
  std::ifstream infile(filename.c_str());
  return infile.is_open();
}

RooDataSet ExtractDataSetFromMC(std::string const &input, RooRealVar &buMass,
                                RooRealVar &deltaMass, RooCategory &fitting,
                                std::string const &box_bu_low,
                                std::string const &box_bu_high,
                                std::string const &box_delta_low,
                                std::string const &box_delta_high, double &nBu,
                                double &nDelta) {
  RooDataSet *inputDataSet = nullptr;

  if (!fexists(input)) {
    std::string inputfile_1(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/"
        "Bu2Dst0pi_D0gamma_2011_MagUp/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/"
        "Bu2Dst0pi_D0gamma_2011_MagUp_BDT1_BDT2_PID_buDelta_TM.root");
    std::string inputfile_2(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/"
        "Bu2Dst0pi_D0gamma_2011_MagDown/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/"
        "Bu2Dst0pi_D0gamma_2011_MagDown_BDT1_BDT2_PID_buDelta_TM.root");
    std::string inputfile_3(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/"
        "Bu2Dst0pi_D0gamma_2012_MagUp/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/"
        "Bu2Dst0pi_D0gamma_2012_MagUp_BDT1_BDT2_PID_buDelta_TM.root");
    std::string inputfile_4(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/"
        "Bu2Dst0pi_D0gamma_2012_MagDown/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/"
        "Bu2Dst0pi_D0gamma_2012_MagDown_BDT1_BDT2_PID_buDelta_TM.root");
    std::string inputfile_5(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/"
        "Bu2Dst0pi_D0gamma_2015_MagUp/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/"
        "Bu2Dst0pi_D0gamma_2015_MagUp_BDT1_BDT2_PID_buDelta_TM.root");
    std::string inputfile_6(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/"
        "Bu2Dst0pi_D0gamma_2015_MagDown/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/"
        "Bu2Dst0pi_D0gamma_2015_MagDown_BDT1_BDT2_PID_buDelta_TM.root");
    std::string inputfile_7(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/"
        "Bu2Dst0pi_D0gamma_2016_MagUp/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/"
        "Bu2Dst0pi_D0gamma_2016_MagUp_BDT1_BDT2_PID_buDelta_TM.root");
    std::string inputfile_8(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/"
        "Bu2Dst0pi_D0gamma_2016_MagDown/"
        "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/"
        "Bu2Dst0pi_D0gamma_2016_MagDown_BDT1_BDT2_PID_buDelta_TM.root");
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

    TTreeReaderValue<double> Bu_M_DTF_D0(reader, "Bu_M_DTF_D0");
    TTreeReaderValue<double> Delta_M(reader, "Delta_M");
    TTreeReaderValue<double> Bu_Delta_M(reader, "Bu_Delta_M");
    TTreeReaderValue<double> D0_M(reader, "D0_M");
    TTreeReaderValue<double> D0h_M(reader, "D0h_M");
    TTreeReaderValue<double> D0_M_DOUBLESW_KP(reader, "D0_M_DOUBLESW_KP");
    TTreeReaderValue<float> BDT1(reader, "BDT1");
    TTreeReaderValue<float> BDT2(reader, "BDT2");
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
          *Bu_M_DTF_D0 < 5800 && *Bu_M_DTF_D0 > 5050 && *Bu_M_DTF_D0 < 5800 &&
          *Bu_M_DTF_D0 > 5050 && *Delta_M > 50 && *Delta_M < 210 &&
          abs(*D0_M_DOUBLESW_KP - 1864) > 15 && *D0_FD_ZSIG > 2 &&
          *D0h_M > 4950) {
        newTree->Fill();
      }
    }

    inputDataSet = new RooDataSet("inputDataSet", "inputDataSet", newTree,
                                  RooArgSet(buMass, deltaMass));

    TFile dataFile(input.c_str(), "RECREATE");
    inputDataSet->Write("inputDataSet");
    dataFile.Close();

    std::cout << "MC roodataset saved in " << input << "\n";
  } else {
    std::cout << "Extracting roodataset from " << input << "\n";

    TFile inData(input.c_str(), "READ");
    gDirectory->GetObject("inputDataSet", inputDataSet);
    inData.Close();

    if (inputDataSet == nullptr) {
      throw std::runtime_error("Data set does not exist.");
    } else {
      std::cout << "\n\n\n Dataset extracted. \n\n";
      inputDataSet->Print();
    }
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

void GenerateToys(std::string const &input, std::string const &outputDir,
                  std::string const &box_delta_low,
                  std::string const &box_delta_high,
                  std::string const &box_bu_low,
                  std::string const &box_bu_high) {
  int bu_low = 5150;
  int bu_high = 5400;
  int delta_low = 100;  // 134;
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

  // ---------------------------- Read in toy dataset
  // ----------------------------
  double nBu, nDelta;
  RooDataSet combData = ExtractDataSetFromMC(
      input, buMass, deltaMass, fitting, box_bu_low, box_bu_high, box_delta_low,
      box_delta_high, nBu, nDelta);

  combData.Print();

  auto toyDataHist = std::unique_ptr<RooDataHist>(
      combData.binnedClone("toyDataHist", "toyDataHist"));
  auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

  // ---------------------------- PDFs ----------------------------
  //
  // ---------------------------- Signal ----------------------------
  // ---------------------------- Mean ----------------------------
  RooRealVar meanDeltaSignal("meanDeltaSignal", "", 1.4276e+02, 135, 150);
  // ---------------------------- Sigmas ----------------------------
  RooRealVar sigmaDeltaSignal("sigmaDeltaSignal", "", 8.6601e+00, 5, 15);
  // ---------------------------- Tails ----------------------------
  RooRealVar a1DeltaSignal("a1DeltaSignal", "", 1.9251e+00);
  RooRealVar a2DeltaSignal("a2DeltaSignal", "", -7.4405e-01);
  RooRealVar n1DeltaSignal("n1DeltaSignal", "", 1.0441e+00);
  RooRealVar n2DeltaSignal("n2DeltaSignal", "", 4.2875e+00);
  // ---------------------------- PDFs ----------------------------
  RooCBShape pdfDeltaSignal1("pdfDeltaSignal1", "", deltaMass, meanDeltaSignal,
                             sigmaDeltaSignal, a1DeltaSignal, n1DeltaSignal);
  RooCBShape pdfDeltaSignal2("pdfDeltaSignal2", "", deltaMass, meanDeltaSignal,
                             sigmaDeltaSignal, a2DeltaSignal, n2DeltaSignal);
  RooRealVar fracPdf1DeltaSignal("fracPdf1DeltaSignal", "", 1.7974e-01);
  RooAddPdf pdfDeltaSignal("pdfDeltaSignal", "",
                           RooArgSet(pdfDeltaSignal1, pdfDeltaSignal2),
                           fracPdf1DeltaSignal);

  // ---------------------------- PDFs: Bu ----------------------------
  // ---------------------------- Signal ----------------------------
  // ---------------------------- Mean ----------------------------
  RooRealVar meanBuSignal("meanBuSignal", "", 5.2819e+03, 5280, 5290);
  // ---------------------------- Sigmas ----------------------------
  RooRealVar sigmaBuSignal("sigmaBuSignal", "", 2.0783e+01, 18,
                           24);  //, 300, 400);

  // ---------------------------- Tails ----------------------------
  RooRealVar a1BuSignal("a1BuSignal", "", 1.6160e+00);
  RooRealVar a2BuSignal("a2BuSignal", "", -1.5208e+00);
  RooRealVar n1BuSignal("n1BuSignal", "", 9.9933e+00);
  RooRealVar n2BuSignal("n2BuSignal", "", 6.4413e+00);
  // ---------------------------- PDFs ----------------------------
  RooRealVar fracPdf1BuSignal("fracPdf1BuSignal", "", 7.4517e-01);
  RooCBShape pdfBuSignal1("pdfBuSignal1", "", buMass, meanBuSignal,
                          sigmaBuSignal, a1BuSignal, n1BuSignal);
  RooCBShape pdfBuSignal2("pdfBuSignal2", "", buMass, meanBuSignal,
                          sigmaBuSignal, a2BuSignal, n2BuSignal);

  // ---------------------------- Efficiencies ----------------------------
  RooRealVar orEffSignal("orEffSignal", "", 1);
  RooRealVar boxEffSignal("boxEffSignal", "", 1);
  RooRealVar deltaCutEffSignal("deltaCutEffSignal", "", 1);
  RooRealVar buCutEffSignal("buCutEffSignal", "", 1);

  ExtractBoxEfficiencies(Mode::Bu2Dst0pi_D0gamma, box_delta_low, box_delta_high,
                         box_bu_low, box_bu_high, boxEffSignal,
                         deltaCutEffSignal, buCutEffSignal, orEffSignal);

  RooRealVar yieldTotSignal("yieldTotSignal", "", 14000 * orEffSignal.getVal(),
                            0, 15000);
  // ---------------------------- Yields ----------------------------

  RooFormulaVar yieldBuSignal(
      "yieldBuSignal", "", "(@0/@1)*@2",
      RooArgList(deltaCutEffSignal, orEffSignal, yieldTotSignal));
  RooFormulaVar yieldBuSignal1("yieldBuSignal1", "", "@0*@1",
                               RooArgList(yieldBuSignal, fracPdf1BuSignal));
  RooFormulaVar yieldBuSignal2("yieldBuSignal2", "", "@0*(1-@1)",
                               RooArgList(yieldBuSignal, fracPdf1BuSignal));
  RooFormulaVar yieldDeltaSignal(
      "yieldDeltaSignal", "", "(@0/@1)*@2",
      RooArgList(buCutEffSignal, orEffSignal, yieldTotSignal));
  RooFormulaVar yieldDeltaSignal1(
      "yieldDeltaSignal1", "", "@0*@1",
      RooArgList(yieldDeltaSignal, fracPdf1DeltaSignal));
  RooFormulaVar yieldDeltaSignal2(
      "yieldDeltaSignal2", "", "@0*(1-@1)",
      RooArgList(yieldDeltaSignal, fracPdf1DeltaSignal));
  RooFormulaVar yieldSharedSignal(
      "yieldSharedSignal", "", "(@0/@1)*@2",
      RooArgList(boxEffSignal, orEffSignal, yieldTotSignal));

  // ---------------------------- Add PDFs and yields
  // ----------------------------
  RooArgSet yieldsBu;
  yieldsBu.add(yieldBuSignal1);
  yieldsBu.add(yieldBuSignal2);

  RooArgSet functionsBu;
  functionsBu.add(pdfBuSignal1);
  functionsBu.add(pdfBuSignal2);
  RooAddPdf pdfBu("pdfBu", "", functionsBu, yieldsBu);

  RooArgSet yieldsDelta;
  yieldsDelta.add(yieldDeltaSignal1);
  yieldsDelta.add(yieldDeltaSignal2);

  RooArgSet functionsDelta;
  functionsDelta.add(pdfDeltaSignal1);
  functionsDelta.add(pdfDeltaSignal2);
  RooAddPdf pdfDelta("pdfDelta", "", functionsDelta, yieldsDelta);

  // ---------------------------- Construct Sim PDF
  // ----------------------------
  RooSimultaneous simPdf("simPdf", "", fitting);
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

  std::cout << "Plotting projections of m[Bu]\n";
  PlotComponent(Variable::bu, buMass, toyDataHist.get(), simPdf, fitting,
                outputDir, box_delta_low, box_delta_high,
                box_bu_low, box_bu_high);
  std::cout << "Plotting projections of m[Delta]\n";
  PlotComponent(Variable::delta, deltaMass, toyDataHist.get(), simPdf, fitting,
                outputDir, box_delta_low, box_delta_high,
                box_bu_low, box_bu_high);
  std::cout << "Plotting correlation matrix\n";
  PlotCorrMatrix(result.get(), outputDir, box_delta_low, box_delta_high,
                box_bu_low, box_bu_high);

  result->Print("v");

  // double errYieldTotSignal =
  //     yieldTotSignal.getPropagatedError(*result) *
  //     std::sqrt(
  //         pow((yieldSharedSignal.getVal() / yieldTotSignal.getVal() *
  //              std::sqrt(2)),
  //             2) +
  //         pow((1 - yieldSharedSignal.getVal() / yieldTotSignal.getVal()), 2));
  double errYieldTotSignal =
      yieldTotSignal.getPropagatedError(*result) * (
          (yieldSharedSignal.getVal() / yieldTotSignal.getVal() *
               std::sqrt(2)) +
          (1 - yieldSharedSignal.getVal() / yieldTotSignal.getVal()));
  std::cout << "Box = " << box_delta_low << "-" << box_delta_high
            << " " << box_bu_low << "-" << box_bu_high << "\n";
  std::cout << "yieldSharedSignal = " << yieldSharedSignal.getVal() << " ± "
            << yieldSharedSignal.getPropagatedError(*result) << "\n";
  std::cout << "yieldTotSignal = " << yieldTotSignal.getVal() << " ± "
            << errYieldTotSignal << "\n";
  std::cout << "Corrected error / fit Error = "
            << errYieldTotSignal / yieldTotSignal.getPropagatedError(*result) << "\n";
  std::cout << "Corrected error / fit Error = "
            << errYieldTotSignal / yieldTotSignal.getError() << "\n";
  TFile outputFile(
      (outputDir + "/Result_" + box_delta_low + "_" + box_delta_high + "_" +
       box_bu_low + "_" + box_bu_high + ".root")
          .c_str(),
      "recreate");
  outputFile.cd();
  result->SetName(("Result_" + box_delta_low + "_" + box_delta_high + "_" +
                   box_bu_low + "_" + box_bu_high)
                      .c_str());
  result->Write();
  TTree tree("tree", "");
  tree.Branch("errYieldTotSignal", &errYieldTotSignal, "errYieldTotSignal/D");
  tree.Fill();
  outputFile.Write();
  outputFile.Close();
}

int main(int argc, char *argv[]) {
  if (argc < 7) {
    std::cerr
        << "Enter input file, output directory and box limits: delta_low, "
           "delta_high, bu_low, bu_high\n";
    return 1;
  }
  std::string input = argv[1];
  std::string outputDir = argv[2];
  std::string box_delta_low = argv[3];
  std::string box_delta_high = argv[4];
  std::string box_bu_low = argv[5];
  std::string box_bu_high = argv[6];
  GenerateToys(input, outputDir, box_delta_low, box_delta_high, box_bu_low,
               box_bu_high);
  return 0;
}
