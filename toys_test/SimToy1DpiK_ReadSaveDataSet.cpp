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
#include "RooHistPdf.h"
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
enum class Option { saveD1DToy, save2DToy, fitD1DToy, fit2DToy, fitData };
enum class Bachelor { pi, K };
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

std::string EnumToCategory(Variable variable, Bachelor bachelor) {
  switch (variable) {
    case Variable::bu:
      switch (bachelor) {
        case Bachelor::pi:
          return "bu_pi";
          break;
        case Bachelor::K:
          return "bu_K";
          break;
        default:
          return " ";
      }
      break;
    case Variable::delta:
      switch (bachelor) {
        case Bachelor::pi:
          return "delta_pi";
          break;
        case Bachelor::K:
          return "delta_K";
          break;
        default:
          return " ";
      }
      break;
    default:
      return " ";
  }
}

std::string EnumToString(Variable variable) {
  switch (variable) {
    case Variable::bu:
      return "bu";
      break;
    case Variable::delta:
      return "delta";
      break;
    default:
      return " ";
  }
}

std::string EnumToString(Bachelor bachelor) {
  switch (bachelor) {
    case Bachelor::pi:
      return "pi";
      break;
    case Bachelor::K:
      return "K";
      break;
    default:
      return " ";
  }
}

std::string EnumToLabel(Bachelor bachelor) {
  switch (bachelor) {
    case Bachelor::pi:
      return "#pi";
      break;
    case Bachelor::K:
      return "K";
      break;
    default:
      return " ";
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
    default:
      return " ";
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
    default:
      return " ";
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

void PlotComponent(Variable variable, Bachelor bachelor, RooRealVar &var,
                   RooDataHist *dataHist, RooSimultaneous &simPdf,
                   RooCategory &category, RooAbsPdf &sigPdf, RooAbsPdf &bkg1Pdf,
                   RooAbsPdf &bkg2Pdf, RooAbsPdf &bkg3Pdf,
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
      switch (bachelor) {
        case Bachelor::pi:
          title = "m[D^{*0}#pi] - m[D^{*0}] + m[D^{*0}]_{PDG}";
          break;
        case Bachelor::K:
          title = "m[D^{*0}K] - m[D^{*0}] + m[D^{*0}]_{PDG}";
          break;
      }
      break;
    case Variable::delta:
      title = "m[D^{*0}] - m[D^{0}]";
      break;
  }

  auto frame =
      std::unique_ptr<RooPlot>(var.frame(RooFit::Title(title.c_str())));

  RooHist *pullHist = nullptr;
  std::unique_ptr<RooPlot> pullFrame(var.frame(RooFit::Title(" ")));

  dataHist->plotOn(frame.get(), RooFit::Cut(("category==category::" +
                                             EnumToCategory(variable, bachelor))
                                                .c_str()));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(category, EnumToCategory(variable, bachelor).c_str()),
      RooFit::ProjWData(category, *dataHist),
      RooFit::Components(sigPdf.GetName()), RooFit::LineColor(kBlue),
      RooFit::LineStyle(kDashed));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(category, EnumToCategory(variable, bachelor).c_str()),
      RooFit::ProjWData(category, *dataHist),
      RooFit::Components(bkg1Pdf.GetName()), RooFit::LineColor(kOrange),
      RooFit::LineStyle(kDashed));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(category, EnumToCategory(variable, bachelor).c_str()),
      RooFit::ProjWData(category, *dataHist),
      RooFit::Components(bkg2Pdf.GetName()), RooFit::LineColor(kRed),
      RooFit::LineStyle(kDashed));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(category, EnumToCategory(variable, bachelor).c_str()),
      RooFit::ProjWData(category, *dataHist),
      RooFit::Components(bkg3Pdf.GetName()), RooFit::LineColor(kGreen),
      RooFit::LineStyle(kDashed));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(category, EnumToCategory(variable, bachelor).c_str()),
      RooFit::ProjWData(category, *dataHist), RooFit::LineColor(kBlue));
  pullHist = frame->RooPlot::pullHist();

  dataHist->plotOn(frame.get(), RooFit::Cut(("category==category::" +
                                             EnumToCategory(variable, bachelor))
                                                .c_str()));

  if (pullHist != 0) {
    pullFrame->addPlotable(pullHist /* .get() */, "P");
    pullFrame->SetName(
        ("pullFrame_" + EnumToCategory(variable, bachelor)).c_str());
    pullFrame->SetTitle("");
  }

  TLegend legend(0.71, 0.65, 0.95, 0.88);
  // ------------- Draw Legends -------------- //
  auto sigHist = std::make_unique<TH1D>(
      ("sigHist_" + EnumToCategory(variable, bachelor)).c_str(), "sigHist", 1,
      0, 1);
  sigHist->SetLineColor(kBlue);
  sigHist->SetLineStyle(kDashed);
  sigHist->SetLineWidth(2);
  auto bkg1Hist = std::make_unique<TH1D>(
      ("bkg1Hist_" + EnumToCategory(variable, bachelor)).c_str(), "bkg1Hist", 1,
      0, 1);
  bkg1Hist->SetLineColor(kOrange);
  bkg1Hist->SetLineStyle(kDashed);
  bkg1Hist->SetLineWidth(2);
  auto bkg2Hist = std::make_unique<TH1D>(
      ("bkg2Hist_" + EnumToCategory(variable, bachelor)).c_str(), "bkg2Hist", 1,
      0, 1);
  bkg2Hist->SetLineColor(kRed);
  bkg2Hist->SetLineStyle(kDashed);
  bkg2Hist->SetLineWidth(2);
  auto bkg3Hist = std::make_unique<TH1D>(
      ("bkg3Hist_" + EnumToCategory(variable, bachelor)).c_str(), "bkg3Hist", 1,
      0, 1);
  bkg3Hist->SetLineColor(kGreen);
  bkg3Hist->SetLineStyle(kDashed);
  bkg3Hist->SetLineWidth(2);

  legend.SetLineColor(kWhite);
  legend.AddEntry(sigHist.get(), sigPdf.GetName(), "l");
  legend.AddEntry(bkg1Hist.get(), bkg1Pdf.GetName(), "l");
  legend.AddEntry(bkg2Hist.get(), bkg2Pdf.GetName(), "l");
  legend.AddEntry(bkg3Hist.get(), bkg3Pdf.GetName(), "l");

  TCanvas canvas(("canvas_" + EnumToCategory(variable, bachelor)).c_str(), "",
                 1200, 1000);

  TPad pad1(("pad1_" + EnumToCategory(variable, bachelor)).c_str(), "", 0.0,
            0.14, 1.0, 1.0, kWhite);
  pad1.Draw();

  TPad pad2(("pad2_" + EnumToCategory(variable, bachelor)).c_str(), "", 0.0,
            0.05, 1.0, 0.15, kWhite);
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
  canvas.SaveAs((outputDir + "/1d_plots/" + EnumToCategory(variable, bachelor) +
                 "_" + box_delta_low + "_" + box_delta_high + "_" + box_bu_low +
                 "_" + box_bu_high + ".pdf")
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

RooDataSet ExtractDataSet(Option option, Bachelor bachelor,
                          std::string const &input, RooRealVar &buMass,
                          RooRealVar &deltaMass, RooCategory &category,
                          std::string const &box_bu_low,
                          std::string const &box_bu_high,
                          std::string const &box_delta_low,
                          std::string const &box_delta_high, int it) {
  TFile in(input.c_str(), "READ");
  if (option == Option::fitD1DToy) {
    std::cout << "Extracting 1D toy dataset.\n";
    RooDataSet *dataDelta;
    std::string rdsName;
    if (bachelor == Bachelor::pi) {
      rdsName = "PiDataSet";
    } else {
      rdsName = "KDataSet";
    }
    gDirectory->GetObject(("delta" + rdsName).c_str(), dataDelta);
    if (dataDelta == nullptr) {
      throw std::runtime_error("Delta dataset does not exist.");
    } else {
      std::cout << "dataDelta extracted... \n";
      dataDelta->Print();
    }
    RooDataSet *dataBu;
    gDirectory->GetObject(("bu" + rdsName).c_str(), dataBu);
    if (dataBu == nullptr) {
      throw std::runtime_error("Bu dataset does not exist.");
    } else {
      std::cout << "dataBu extracted... \n";
      dataBu->Print();
    }
    RooDataSet combData(
        ("combData_" + EnumToString(bachelor) + "_" + std::to_string(it))
            .c_str(),
        "", RooArgSet(buMass, deltaMass), RooFit::Index(category),
        RooFit::Import(EnumToCategory(Variable::delta, bachelor).c_str(),
                       *dataDelta),
        RooFit::Import(EnumToCategory(Variable::bu, bachelor).c_str(),
                       *dataBu));
    return combData;
    std::cout << "1D: returning combDataSet\n";
  } else { 
    RooDataSet *inputDataSet;
    std::string cutString = "";
    if (option == Option::fit2DToy) {
      std::cout << "Extracting 2D toy dataset.\n";
      gDirectory->GetObject("inputDataSet", inputDataSet);
    } else {
      std::cout << "Extracting 2D dataset with cuts applied.\n";
      if (bachelor == Bachelor::pi) {
        cutString =
            "BDT1>0.05&&BDT2>0.05&&bach_PIDK<12&&((abs(h1_D_ID)==211&&h1_D_"
            "PIDK<-2)||(abs(h1_D_ID)==321&&h1_D_PIDK>2))&&((abs(h2_D_ID)==211&&"
            "h2_D_PIDK<-2)||(abs(h2_D_ID)==321&&h2_D_PIDK>2))";
      } else {
        cutString =
            "BDT1>0.05&&BDT2>0.05&&bach_PIDK>12&&((abs(h1_D_ID)==211&&h1_D_"
            "PIDK<-2)||(abs(h1_D_ID)==321&&h1_D_PIDK>2))&&((abs(h2_D_ID)==211&&"
            "h2_D_PIDK<-2)||(abs(h2_D_ID)==321&&h2_D_PIDK>2))";
      }
      RooDataSet *inputDataSet_tmp;
      gDirectory->GetObject("inputDataSet", inputDataSet_tmp);
      // Reduce # RRVs as binnedClone() only works with < 4
      inputDataSet = dynamic_cast<RooDataSet *>(
          inputDataSet_tmp->reduce(RooArgSet(buMass, deltaMass), cutString.c_str()));
    }
    if (inputDataSet == nullptr) {
      throw std::runtime_error("Data set does not exist.");
    } else {
      std::cout << "inputDataSet extracted... \n";
      inputDataSet->Print();
    }
    if (option == Option::save2DToy) {
      inputDataSet->SetName(
          ("inputDataSet_" + EnumToString(bachelor) + "_" + std::to_string(it))
              .c_str());
      return *inputDataSet;
      std::cout << "Returning 2D dataset for " << EnumToString(bachelor)
                << " bachelor.\n";
    } else {
      auto dataBu_tmp = std::unique_ptr<RooDataSet>(
          dynamic_cast<RooDataSet *>(inputDataSet->reduce(
              ("Delta_M>" + box_delta_low + "&&Delta_M<" + box_delta_high)
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
        throw std::runtime_error(
            "Could not reduce inputDataSet to Delta mass.");
      }
      dataDelta->Print();

      RooDataSet combData(
          ("combData_" + EnumToString(bachelor) + "_" + std::to_string(it))
              .c_str(),
          "", RooArgSet(buMass, deltaMass), RooFit::Index(category),
          RooFit::Import(EnumToCategory(Variable::delta, bachelor).c_str(),
                         *dataDelta.get()),
          RooFit::Import(EnumToCategory(Variable::bu, bachelor).c_str(),
                         *dataBu.get()));
      combData.Print();
      return combData;
      std::cout << "2D: returning combDataSet\n";
    }
  }
}

void PlotGeneratedData(Bachelor bachelor, RooRealVar &buMass,
                       RooRealVar &deltaMass, RooDataHist *dataHist,
                       RooDataSet *toyData, RooHistPdf &histPdf,
                       std::string const &outputDir) {
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

  RooPlot *frame1 = buMass.frame(RooFit::Title(
      ("m[D^{*0}" + EnumToLabel(bachelor) + "] - m[D^{*0}] + m[D^{*0}]_{PDG}")
          .c_str()));
  dataHist->plotOn(frame1);
  toyData->plotOn(frame1, RooFit::LineColor(kBlue));

  RooPlot *frame2 = deltaMass.frame(RooFit::Title("m[D^{*0}] - m[D^{0}]"));
  dataHist->plotOn(frame2);
  toyData->plotOn(frame2, RooFit::LineColor(kBlue));

  TCanvas canvas_1d("canvas_1d", "canvas", 1800, 900);
  canvas_1d.Divide(2, 1);

  canvas_1d.cd(1);
  frame1->Draw();

  canvas_1d.cd(2);
  frame2->Draw();

  canvas_1d.Update();
  canvas_1d.SaveAs(
      (outputDir + "/plots/1DProjections_" + EnumToString(bachelor) + ".pdf")
          .c_str());

  int nContours = 255;

  gStyle->SetNumberContours(nContours);
  gStyle->SetTitleSize(0.03, "XYZ");
  gStyle->SetLabelSize(0.025, "XYZ");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetTitleOffset(1.2, "Z");
  gStyle->SetPadRightMargin(0.15);

  // Make two-dimensional plot of sampled PDF in x vs y
  TH2F *histModel = (TH2F *)histPdf.createHistogram(
      ("histModel_" + EnumToString(bachelor)).c_str(), buMass,
      RooFit::Binning(buMass.getBins()),
      RooFit::YVar(deltaMass, RooFit::Binning(deltaMass.getBins())));
  histModel->SetTitle("");

  // Make 2D plot of data
  TH2F *histData = (TH2F *)dataHist->createHistogram(
      "Bu_Delta_M,Delta_M", buMass.getBins(), deltaMass.getBins());
  histData->SetName(("histData_" + EnumToString(bachelor)).c_str());
  histData->SetTitle("");

  TH2F *histToy = (TH2F *)toyData->createHistogram(
      "Bu_Delta_M,Delta_M", buMass.getBins(), deltaMass.getBins());
  histToy->SetName(("histToy_" + EnumToString(bachelor)).c_str());
  histToy->SetTitle("");

  // Scale model plot to total number of data events
  histModel->Scale(histData->Integral());

  // Make a histogram with the Poisson stats in each data bin
  TH2F histDataErr(("histDataErr_" + EnumToString(bachelor)).c_str(), "",
                   buMass.getBins(), buMass.getMin(), buMass.getMax(),
                   deltaMass.getBins(), deltaMass.getMin(), deltaMass.getMax());
  for (int i = 0; i < buMass.getBins() * deltaMass.getBins(); i++) {
    float n_bin = histData->GetBinContent(i);
    float err = sqrt(n_bin);
    histDataErr.SetBinContent(i, err);
  }

  // 2D PDF plot
  TCanvas canvas2DPdf("canvas2DPdf", "", 1000, 800);
  histModel->SetStats(0);
  histModel->Draw("colz");
  histModel->SetTitle(
      "B^{#pm}#rightarrow#font[132]{[}#font[132]{[}K^{#pm}#pi^{#"
      "mp}#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{0}*}#pi^{#"
      "pm}");
  histModel->Draw("colz");
  canvas2DPdf.Update();
  canvas2DPdf.SaveAs(
      (outputDir + "/plots/2DHistPdf_" + EnumToString(bachelor) + ".pdf")
          .c_str());

  // 2D data plot
  TCanvas canvas2DData("canvas2DData", "", 1000, 800);
  histData->SetStats(0);
  histData->Draw("colz");
  histData->SetTitle(
      "B^{#pm}#rightarrow#font[132]{[}#font[132]{[}K^{#pm}#pi^{#"
      "mp}#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{0}*}#pi^{#"
      "pm}");
  histData->Draw("colz");
  canvas2DData.Update();
  canvas2DData.SaveAs(
      (outputDir + "/plots/2DData_" + EnumToString(bachelor) + ".pdf").c_str());

  // 2D toy data plot
  TCanvas canvas2DToy("canvas2DToy", "", 1000, 800);
  histToy->SetStats(0);
  histToy->Draw("colz");
  histToy->SetTitle(
      "B^{#pm}#rightarrow#font[132]{[}#font[132]{[}K^{#pm}#pi^{#"
      "mp}#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{0}*}#pi^{#"
      "pm}");
  histToy->Draw("colz");
  canvas2DToy.Update();
  canvas2DToy.SaveAs(
      (outputDir + "/plots/2DToyData_" + EnumToString(bachelor) + ".pdf")
          .c_str());

  // const int n = 7;
  // double red[n] = {0.000, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000};
  // double green[n] = {0.800, 0.800, 0.000, 0.000, 0.000, 0.000, 0.600};
  // double blue[n] = {0.000, 0.800, 1.000, 0.200, 1.000, 0.000, 0.000};
  // double length[n] = {0.000, 0.167, 0.333, 0.5, 0.667, 0.833, 1.000};
  //
  // TColor::CreateGradientColorTable(n, length, red, green, blue, nContours);

  // 2D residuals plot (data - PDF)/err
  TCanvas canvas2DRes("canvas2DRes", "", 1000, 800);
  canvas2DRes.cd();
  TH2F *histDataNew = (TH2F *)histData->Clone();
  histDataNew->SetName(("histDataNew_" + EnumToString(bachelor)).c_str());
  histDataNew->Add(histToy, -1);
  histDataNew->Divide(&histDataErr);
  canvas2DRes.cd();
  histDataNew->GetZaxis()->SetTitle("Residual");
  histDataNew->GetZaxis()->SetRangeUser(-6.0, 6.0);
  histDataNew->SetStats(0);
  histDataNew->Draw("colz");
  canvas2DRes.Update();
  canvas2DRes.SaveAs(
      (outputDir + "/plots/2DResiduals_" + EnumToString(bachelor) + ".pdf")
          .c_str());
}

void FitToys(Option option, int &nIter,
             std::vector<std::string> const &filenamesPi,
             std::vector<std::string> const &filenamesK,
             std::string const &outputDir, std::string const &box_delta_low,
             std::string const &box_delta_high, std::string const &box_bu_low,
             std::string const &box_bu_high) {
  int bu_low = 5050;
  int bu_high = 5800;
  int delta_low = 70;  // 134;
  int delta_high = 190;

  int bu_nbins = (bu_high - bu_low) / 10;
  int delta_nbins = (delta_high - delta_low) / 2;

  // ---------------------------- Fitting Vars ----------------------------
  RooRealVar buMass("Bu_Delta_M",
                    "m[D^{*0}h^{#pm}] - m[D^{*0}] + m[D^{*0}]_{PDG}", bu_low,
                    bu_high, "MeV/c^{2}");
  RooRealVar deltaMass("Delta_M", "m[D^{*0}] - m[D^{0}]", delta_low, delta_high,
                       "MeV/c^{2}");

  buMass.setBins(bu_nbins);
  deltaMass.setBins(delta_nbins);

  // ---------------------------- Categories ----------------------------
  RooCategory category("category", "category");
  category.defineType(EnumToCategory(Variable::bu, Bachelor::pi).c_str());
  category.defineType(EnumToCategory(Variable::bu, Bachelor::K).c_str());
  category.defineType(EnumToCategory(Variable::delta, Bachelor::pi).c_str());
  category.defineType(EnumToCategory(Variable::delta, Bachelor::K).c_str());

  // ---------------------------- Yield Starting points
  // ----------------------------
  double initYieldBu2Dst0pi_D0gamma = 5.1958e+04;
  double initYieldBu2Dst0pi_D0pi0 = initYieldBu2Dst0pi_D0gamma * 0.916;
  double fracMisRecPi_Bu2Dst0pi_D0gamma_WN = 0.473;
  double fracMisRecPi_Bu2Dst0pi_D0pi0_WN = 0.809;
  double fracMisRecPi_Bd2Dstpi = 0.643;
  double fracMisRecPi_Bu2D0rho = 0.973;
  double fracMisRecPi = fracMisRecPi_Bu2Dst0pi_D0gamma_WN +
                        fracMisRecPi_Bu2Dst0pi_D0pi0_WN +
                        fracMisRecPi_Bd2Dstpi + fracMisRecPi_Bu2D0rho;
  double initYieldMisRecPi = initYieldBu2Dst0pi_D0gamma * (fracMisRecPi);
  double initYieldBu2D0pi = initYieldBu2Dst0pi_D0gamma * (1.54);
  // double initYieldBu2Dst0pi_D0pi0_WN = initYieldBu2Dst0pi_D0gamma * 0.809;
  // double initYieldBd2Dstpi = initYieldBu2Dst0pi_D0gamma * 0.643;
  // double initYieldBu2D0rho = initYieldBu2Dst0pi_D0gamma * 0.973;

  // ---------------------------- Efficiencies ----------------------------
  // Outside of loop as all datasets have same box dimensions
  RooRealVar orEffBu2Dst0pi_D0gamma("orEffBu2Dst0pi_D0gamma", "", 1);
  RooRealVar boxEffBu2Dst0pi_D0gamma("boxEffBu2Dst0pi_D0gamma", "", 1);
  RooRealVar deltaCutEffBu2Dst0pi_D0gamma("deltaCutEffBu2Dst0pi_D0gamma", "",
                                          1);
  RooRealVar buCutEffBu2Dst0pi_D0gamma("buCutEffBu2Dst0pi_D0gamma", "", 1);
  RooRealVar orEffBu2Dst0pi_D0pi0("orEffBu2Dst0pi_D0pi0", "", 1);
  RooRealVar boxEffBu2Dst0pi_D0pi0("boxEffBu2Dst0pi_D0pi0", "", 1);
  RooRealVar deltaCutEffBu2Dst0pi_D0pi0("deltaCutEffBu2Dst0pi_D0pi0", "", 1);
  RooRealVar buCutEffBu2Dst0pi_D0pi0("buCutEffBu2Dst0pi_D0pi0", "", 1);
  RooRealVar orEffBu2D0pi("orEffBu2D0pi", "", 1);
  RooRealVar boxEffBu2D0pi("boxEffBu2D0pi", "", 1);
  RooRealVar deltaCutEffBu2D0pi("deltaCutEffBu2D0pi", "", 1);
  RooRealVar buCutEffBu2D0pi("buCutEffBu2D0pi", "", 1);

  double orEffMisRecPiVal = 0.0;
  double boxEffMisRecPiVal = 0.0;
  double deltaCutEffMisRecPiVal = 0.0;
  double buCutEffMisRecPiVal = 0.0;

  std::map<Mode, double> misRecModesMap = {
      {Mode::Bu2Dst0pi_D0pi0_WN,
       fracMisRecPi_Bu2Dst0pi_D0pi0_WN / fracMisRecPi},
      {Mode::Bu2Dst0pi_D0gamma_WN,
       fracMisRecPi_Bu2Dst0pi_D0gamma_WN / fracMisRecPi},
      {Mode::Bu2D0rho, fracMisRecPi_Bu2D0rho / fracMisRecPi},
      {Mode::Bd2Dstpi, fracMisRecPi_Bd2Dstpi / fracMisRecPi}};

  if (option != Option::save2DToy) {
    ExtractBoxEfficiencies(
        Mode::Bu2Dst0pi_D0gamma, box_delta_low, box_delta_high, box_bu_low,
        box_bu_high, boxEffBu2Dst0pi_D0gamma, deltaCutEffBu2Dst0pi_D0gamma,
        buCutEffBu2Dst0pi_D0gamma, orEffBu2Dst0pi_D0gamma);
    ExtractBoxEfficiencies(Mode::Bu2Dst0pi_D0pi0, box_delta_low, box_delta_high,
                           box_bu_low, box_bu_high, boxEffBu2Dst0pi_D0pi0,
                           deltaCutEffBu2Dst0pi_D0pi0, buCutEffBu2Dst0pi_D0pi0,
                           orEffBu2Dst0pi_D0pi0);
    ExtractBoxEfficiencies(Mode::Bu2D0pi, box_delta_low, box_delta_high,
                           box_bu_low, box_bu_high, boxEffBu2D0pi,
                           deltaCutEffBu2D0pi, buCutEffBu2D0pi, orEffBu2D0pi);

    for (auto &m : misRecModesMap) {
      RooRealVar orEffTemp("orEffTemp", "", 1);
      RooRealVar boxEffTemp("boxEffTemp", "", 1);
      RooRealVar deltaCutEffTemp("deltaCutEffTemp", "", 1);
      RooRealVar buCutEffTemp("buCutEffTemp", "", 1);

      ExtractBoxEfficiencies(m.first, box_delta_low, box_delta_high, box_bu_low,
                             box_bu_high, boxEffTemp, deltaCutEffTemp,
                             buCutEffTemp, orEffTemp);

      orEffMisRecPiVal += orEffTemp.getVal() * m.second;
      boxEffMisRecPiVal += boxEffTemp.getVal() * m.second;
      deltaCutEffMisRecPiVal += deltaCutEffTemp.getVal() * m.second;
      buCutEffMisRecPiVal += buCutEffTemp.getVal() * m.second;
    }
  }

  RooRealVar orEffMisRecPi("orEffMisRecPi", "", orEffMisRecPiVal);
  RooRealVar boxEffMisRecPi("boxEffMisRecPi", "", boxEffMisRecPiVal);
  RooRealVar deltaCutEffMisRecPi("deltaCutEffMisRecPi", "",
                                 deltaCutEffMisRecPiVal);
  RooRealVar buCutEffMisRecPi("buCutEffMisRecPi", "", buCutEffMisRecPiVal);

  if (option != Option::save2DToy) {
    std::cout << "Set MisRecPi efficiencies :\n"
              << "\tDelta Window =\t" << deltaCutEffMisRecPi.getVal()
              << "\tBu Window =\t" << buCutEffMisRecPi.getVal() << "\tBox =\t"
              << boxEffMisRecPi.getVal() << "\n"
              << "\tDelta OR Bu =\t" << orEffMisRecPi.getVal() << "\n";
  }

  RooConstVar pidEff("pidEff", "", 0.64);

  // Loop over data files and perform 1D fit to each dataset
  for (int i = 0; i < nIter; ++i) {
    // ---------------------------- Pi Yields ----------------------------
    RooRealVar yieldTotBu2Dst0pi_D0gamma(
        ("yieldTotBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        initYieldBu2Dst0pi_D0gamma * orEffBu2Dst0pi_D0gamma.getVal(), -1000000,
        1000000);
    RooFormulaVar yieldBuBu2Dst0pi_D0gamma(
        ("yieldBuBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        "(@0/@1)*@2",
        RooArgList(deltaCutEffBu2Dst0pi_D0gamma, orEffBu2Dst0pi_D0gamma,
                   yieldTotBu2Dst0pi_D0gamma));
    RooFormulaVar yieldDeltaBu2Dst0pi_D0gamma(
        ("yieldDeltaBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        "(@0/@1)*@2",
        RooArgList(buCutEffBu2Dst0pi_D0gamma, orEffBu2Dst0pi_D0gamma,
                   yieldTotBu2Dst0pi_D0gamma));
    RooFormulaVar yieldSharedBu2Dst0pi_D0gamma(
        ("yieldSharedBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        "(@0/@1)*@2",
        RooArgList(boxEffBu2Dst0pi_D0gamma, orEffBu2Dst0pi_D0gamma,
                   yieldTotBu2Dst0pi_D0gamma));

    RooRealVar yieldTotBu2Dst0pi_D0pi0(
        ("yieldTotBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        initYieldBu2Dst0pi_D0pi0 * orEffBu2Dst0pi_D0pi0.getVal(), -1000000,
        1000000);
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

    RooRealVar yieldTotMisRecPi(
        ("yieldTotMisRecPi_" + std::to_string(i)).c_str(), "",
        initYieldMisRecPi * orEffMisRecPi.getVal(), -1000000, 1000000);
    RooFormulaVar yieldBuMisRecPi(
        ("yieldBuMisRecPi_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(deltaCutEffMisRecPi, orEffMisRecPi, yieldTotMisRecPi));
    RooFormulaVar yieldDeltaMisRecPi(
        ("yieldDeltaMisRecPi_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(buCutEffMisRecPi, orEffMisRecPi, yieldTotMisRecPi));
    RooFormulaVar yieldSharedMisRecPi(
        ("yieldSharedMisRecPi_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(boxEffMisRecPi, orEffMisRecPi, yieldTotMisRecPi));

    RooRealVar yieldTotBu2D0pi(("yieldTotBu2D0pi_" + std::to_string(i)).c_str(),
                               "", initYieldBu2D0pi * orEffBu2D0pi.getVal(),
                               -1000000, 1000000);
    RooFormulaVar yieldBuBu2D0pi(
        ("yieldBuBu2D0pi_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(deltaCutEffBu2D0pi, orEffBu2D0pi, yieldTotBu2D0pi));
    RooFormulaVar yieldDeltaBu2D0pi(
        ("yieldDeltaBu2D0pi_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(buCutEffBu2D0pi, orEffBu2D0pi, yieldTotBu2D0pi));
    RooFormulaVar yieldSharedBu2D0pi(
        ("yieldSharedBu2D0pi_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(boxEffBu2D0pi, orEffBu2D0pi, yieldTotBu2D0pi));

    // ---------------------------- K Yields ----------------------------
    RooRealVar ratioTotBu2Dst0K_D0gamma(
        ("ratioTotBu2Dst0K_D0gamma_" + std::to_string(i)).c_str(), "", 0.07930,
        -1, 1);
    RooFormulaVar yieldTotBu2Dst0K_D0gamma(
        ("yieldTotBu2Dst0K_D0gamma_" + std::to_string(i)).c_str(), "",
        "@0*@1*@2", RooArgList(yieldTotBu2Dst0pi_D0gamma,
                               ratioTotBu2Dst0K_D0gamma, pidEff));
    RooFormulaVar yieldBuBu2Dst0K_D0gamma(
        ("yieldBuBu2Dst0K_D0gamma_" + std::to_string(i)).c_str(), "",
        "(@0/@1)*@2",
        RooArgList(deltaCutEffBu2Dst0pi_D0gamma, orEffBu2Dst0pi_D0gamma,
                   yieldTotBu2Dst0K_D0gamma));
    RooFormulaVar yieldDeltaBu2Dst0K_D0gamma(
        ("yieldDeltaBu2Dst0K_D0gamma_" + std::to_string(i)).c_str(), "",
        "(@0/@1)*@2",
        RooArgList(buCutEffBu2Dst0pi_D0gamma, orEffBu2Dst0pi_D0gamma,
                   yieldTotBu2Dst0K_D0gamma));
    RooFormulaVar yieldSharedBu2Dst0K_D0gamma(
        ("yieldSharedBu2Dst0K_D0gamma_" + std::to_string(i)).c_str(), "",
        "(@0/@1)*@2",
        RooArgList(boxEffBu2Dst0pi_D0gamma, orEffBu2Dst0pi_D0gamma,
                   yieldTotBu2Dst0K_D0gamma));

    RooRealVar ratioTotBu2Dst0K_D0pi0(
        ("ratioTotBu2Dst0K_D0pi0_" + std::to_string(i)).c_str(), "", 0.07930,
        -1, 1);
    RooFormulaVar yieldTotBu2Dst0K_D0pi0(
        ("yieldTotBu2Dst0K_D0pi0_" + std::to_string(i)).c_str(), "", "@0*@1*@2",
        RooArgList(yieldTotBu2Dst0pi_D0pi0, ratioTotBu2Dst0K_D0pi0, pidEff));
    RooFormulaVar yieldBuBu2Dst0K_D0pi0(
        ("yieldBuBu2Dst0K_D0pi0_" + std::to_string(i)).c_str(), "",
        "(@0/@1)*@2", RooArgList(deltaCutEffBu2Dst0pi_D0pi0,
                                 orEffBu2Dst0pi_D0pi0, yieldTotBu2Dst0K_D0pi0));
    RooFormulaVar yieldDeltaBu2Dst0K_D0pi0(
        ("yieldDeltaBu2Dst0K_D0pi0_" + std::to_string(i)).c_str(), "",
        "(@0/@1)*@2", RooArgList(buCutEffBu2Dst0pi_D0pi0, orEffBu2Dst0pi_D0pi0,
                                 yieldTotBu2Dst0K_D0pi0));
    RooFormulaVar yieldSharedBu2Dst0K_D0pi0(
        ("yieldSharedBu2Dst0K_D0pi0_" + std::to_string(i)).c_str(), "",
        "(@0/@1)*@2", RooArgList(boxEffBu2Dst0pi_D0pi0, orEffBu2Dst0pi_D0pi0,
                                 yieldTotBu2Dst0K_D0pi0));

    RooRealVar ratioTotMisRecK(("ratioTotMisRecK_" + std::to_string(i)).c_str(),
                               "", 0.06, -1, 1);
    RooFormulaVar yieldTotMisRecK(
        ("yieldTotMisRecK_" + std::to_string(i)).c_str(), "", "@0*@1*@2",
        RooArgList(yieldTotBu2Dst0pi_D0pi0, ratioTotMisRecK, pidEff));
    RooFormulaVar yieldBuMisRecK(
        ("yieldBuMisRecK_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(deltaCutEffMisRecPi, orEffMisRecPi, yieldTotMisRecK));
    RooFormulaVar yieldDeltaMisRecK(
        ("yieldDeltaMisRecK_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(buCutEffMisRecPi, orEffMisRecPi, yieldTotMisRecK));
    RooFormulaVar yieldSharedMisRecK(
        ("yieldSharedMisRecK_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(boxEffMisRecPi, orEffMisRecPi, yieldTotMisRecK));

    RooRealVar ratioTotBu2D0K(("ratioTotBu2D0K_" + std::to_string(i)).c_str(),
                              "", 0.07768, -1, 1);
    RooFormulaVar yieldTotBu2D0K(
        ("yieldTotBu2D0K_" + std::to_string(i)).c_str(), "", "@0*@1*@2",
        RooArgList(yieldTotBu2Dst0pi_D0pi0, ratioTotBu2D0K, pidEff));
    RooFormulaVar yieldBuBu2D0K(
        ("yieldBuBu2D0K_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(deltaCutEffBu2D0pi, orEffBu2D0pi, yieldTotBu2D0K));
    RooFormulaVar yieldDeltaBu2D0K(
        ("yieldDeltaBu2D0K_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(buCutEffBu2D0pi, orEffBu2D0pi, yieldTotBu2D0K));
    RooFormulaVar yieldSharedBu2D0K(
        ("yieldSharedBu2D0K_" + std::to_string(i)).c_str(), "", "(@0/@1)*@2",
        RooArgList(boxEffBu2D0pi, orEffBu2D0pi, yieldTotBu2D0K));

    // ---------------------------- PDFs ----------------------------
    // ---------------------------- Bu2Dst0pi_D0gamma
    // ----------------------------
    // ---------------------------- Delta: π/K shared
    // ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanDeltaBu2Dst0pi_D0gamma(
        ("meanDeltaBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        1.4233e+02);  //, 135, 150);
    // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaDeltaBu2Dst0pi_D0gamma(
        ("sigmaDeltaBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        8.1675e+00);  //, 2, 15);
    // ---------------------------- Tails ----------------------------
    RooRealVar a1DeltaBu2Dst0pi_D0gamma(
        ("a1DeltaBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        1.5109e+00);  //, 0, 5);
    RooRealVar a2DeltaBu2Dst0pi_D0gamma(
        ("a2DeltaBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        -5.7023e-01);  //, -5, -0.001);
    RooRealVar n1DeltaBu2Dst0pi_D0gamma(
        ("n1DeltaBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        6.0060e+00);  //, 0, 10);
    RooRealVar n2DeltaBu2Dst0pi_D0gamma(
        ("n2DeltaBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        7.8408e+00);  //, 0, 10);
    // ---------------------------- PDFs ----------------------------
    RooCBShape pdfDeltaBu2Dst0pi_D0gamma1(
        ("pdfDeltaBu2Dst0pi_D0gamma1_" + std::to_string(i)).c_str(), "",
        deltaMass, meanDeltaBu2Dst0pi_D0gamma, sigmaDeltaBu2Dst0pi_D0gamma,
        a1DeltaBu2Dst0pi_D0gamma, n1DeltaBu2Dst0pi_D0gamma);
    RooCBShape pdfDeltaBu2Dst0pi_D0gamma2(
        ("pdfDeltaBu2Dst0pi_D0gamma2_" + std::to_string(i)).c_str(), "",
        deltaMass, meanDeltaBu2Dst0pi_D0gamma, sigmaDeltaBu2Dst0pi_D0gamma,
        a2DeltaBu2Dst0pi_D0gamma, n2DeltaBu2Dst0pi_D0gamma);
    RooRealVar fracPdf1DeltaBu2Dst0pi_D0gamma(
        ("fracPdf1DeltaBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        2.6638e-01);
    RooAddPdf pdfDeltaBu2Dst0pi_D0gamma(
        ("pdfDeltaBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        RooArgSet(pdfDeltaBu2Dst0pi_D0gamma1, pdfDeltaBu2Dst0pi_D0gamma2),
        fracPdf1DeltaBu2Dst0pi_D0gamma);

    // // ---------------------------- Mean ----------------------------
    // RooRealVar meanDeltaBu2Dst0pi_D0gamma(
    //     ("meanDeltaBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
    //     1.4141e+02, 135, 145);
    // // // ---------------------------- Sigmas π ----------------------------
    // RooRealVar sigmaLDeltaBu2Dst0pi_D0gamma(
    //     ("sigmaLDeltaBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
    //     7.0374e+00, 2, 10);
    // RooRealVar sigmaRDeltaBu2Dst0pi_D0gamma(
    //     ("sigmaRDeltaBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
    //     9.8254e+00, 2, 15);
    // // ---------------------------- Tails ----------------------------
    // RooRealVar aLDeltaBu2Dst0pi_D0gamma(
    //     ("aLDeltaBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
    //     9.7299e-02);
    // RooRealVar aRDeltaBu2Dst0pi_D0gamma(
    //     ("aRDeltaBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
    //     2.6434e-01);
    // // ---------------------------- PDF ----------------------------
    // RooCruijff pdfDeltaBu2Dst0pi_D0gamma(
    //     ("pdfDeltaBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
    //     deltaMass,
    //     meanDeltaBu2Dst0pi_D0gamma, sigmaLDeltaBu2Dst0pi_D0gamma,
    //     sigmaRDeltaBu2Dst0pi_D0gamma, aLDeltaBu2Dst0pi_D0gamma,
    //     aRDeltaBu2Dst0pi_D0gamma);

    // ---------------------------- PDFs: Bu: π/K separate
    // ----------------------------
    // ---------------------------- Bu2Dst0pi_D0gamma
    // ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanBuBu2Dst0pi_D0gamma(
        ("meanBuBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        5.2819e+03);  //, 5275, 5290);
    // ---------------------------- Sigmas π ----------------------------
    RooRealVar sigmaBuBu2Dst0pi_D0gamma(
        ("sigmaBuBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        2.0051e+01);  //, 15, 30);
    // ---------------------------- Sigmas K ----------------------------
    RooRealVar relativeSigmaBuBu2Dst0pi_D0gamma(
        ("relativeSigmaBuBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        0.95);  //, 0.7, 1.1);
    RooFormulaVar sigmaBuBu2Dst0K_D0gamma(
        ("sigmaBuBu2Dst0K_D0gamma_" + std::to_string(i)).c_str(), "", "@0*@1",
        RooArgList(sigmaBuBu2Dst0pi_D0gamma, relativeSigmaBuBu2Dst0pi_D0gamma));
    // ---------------------------- Tails ----------------------------
    RooRealVar a1BuBu2Dst0pi_D0gamma(
        ("a1BuBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        1.6184e+00);  // 0, 5);
    RooRealVar a2BuBu2Dst0pi_D0gamma(
        ("a2BuBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        -1.6623e+00);  // -5, -0.0001);
    RooRealVar n1BuBu2Dst0pi_D0gamma(
        ("n1BuBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        8.6469e+00);  // 0, 10);
    RooRealVar n2BuBu2Dst0pi_D0gamma(
        ("n2BuBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        5.2563e+00);  // 0, 10);
    // ---------------------------- PDFs π ----------------------------
    RooRealVar fracPdf1BuBu2Dst0pi_D0gamma(
        ("fracPdf1BuBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        6.8457e-01);
    RooCBShape pdfBuBu2Dst0pi_D0gamma1(
        ("pdfBuBu2Dst0pi_D0gamma1_" + std::to_string(i)).c_str(), "", buMass,
        meanBuBu2Dst0pi_D0gamma, sigmaBuBu2Dst0pi_D0gamma,
        a1BuBu2Dst0pi_D0gamma, n1BuBu2Dst0pi_D0gamma);
    RooCBShape pdfBuBu2Dst0pi_D0gamma2(
        ("pdfBuBu2Dst0pi_D0gamma2_" + std::to_string(i)).c_str(), "", buMass,
        meanBuBu2Dst0pi_D0gamma, sigmaBuBu2Dst0pi_D0gamma,
        a2BuBu2Dst0pi_D0gamma, n2BuBu2Dst0pi_D0gamma);
    RooAddPdf pdfBuBu2Dst0pi_D0gamma(
        ("pdfBuBu2Dst0pi_D0gamma_" + std::to_string(i)).c_str(), "",
        RooArgSet(pdfBuBu2Dst0pi_D0gamma1, pdfBuBu2Dst0pi_D0gamma2),
        fracPdf1BuBu2Dst0pi_D0gamma);

    // ---------------------------- PDFs K ----------------------------
    RooCBShape pdfBuBu2Dst0K_D0gamma1(
        ("pdfBuBu2Dst0K_D0gamma1_" + std::to_string(i)).c_str(), "", buMass,
        meanBuBu2Dst0pi_D0gamma, sigmaBuBu2Dst0K_D0gamma, a1BuBu2Dst0pi_D0gamma,
        n1BuBu2Dst0pi_D0gamma);
    RooCBShape pdfBuBu2Dst0K_D0gamma2(
        ("pdfBuBu2Dst0K_D0gamma2_" + std::to_string(i)).c_str(), "", buMass,
        meanBuBu2Dst0pi_D0gamma, sigmaBuBu2Dst0K_D0gamma, a2BuBu2Dst0pi_D0gamma,
        n2BuBu2Dst0pi_D0gamma);
    RooAddPdf pdfBuBu2Dst0K_D0gamma(
        ("pdfBuBu2Dst0K_D0gamma_" + std::to_string(i)).c_str(), "",
        RooArgSet(pdfBuBu2Dst0K_D0gamma1, pdfBuBu2Dst0K_D0gamma2),
        fracPdf1BuBu2Dst0pi_D0gamma);

    // ---------------------------- Bu2Dst0pi_D0pi0 ----------------------------
    // ---------------------------- Delta: π/K shared
    // ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanDeltaBu2Dst0pi_D0pi0(
        ("meanDeltaBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        8.6075e+01);  //, 80, 90);
    // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaDeltaBu2Dst0pi_D0pi0(
        ("sigmaDeltaBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        9.2845e+00);  //, 2, 15);
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

    // ---------------------------- PDFs: Bu: π/K separate
    // ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanBuBu2Dst0pi_D0pi0(
        ("meanBuBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        5.3431e+03);  //, 5300, 5400);
    // ---------------------------- Sigmas π ----------------------------
    RooRealVar sigmaBuBu2Dst0pi_D0pi0(
        ("sigmaBuBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        4.6911e+01);  //, 15, 70);
    // ---------------------------- Sigmas K ----------------------------
    RooRealVar relativeSigmaBuBu2Dst0pi_D0pi0(
        ("relativeSigmaBuBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        0.95);  //, 0.7, 1.1);
    RooFormulaVar sigmaBuBu2Dst0K_D0pi0(
        ("sigmaBuBu2Dst0K_D0pi0_" + std::to_string(i)).c_str(), "", "@0*@1",
        RooArgList(sigmaBuBu2Dst0pi_D0pi0, relativeSigmaBuBu2Dst0pi_D0pi0));
    // ---------------------------- Tails ----------------------------
    RooRealVar aBuBu2Dst0pi_D0pi0(
        ("aBuBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        9.8213e-01);  // 0, 5);
    RooRealVar nBuBu2Dst0pi_D0pi0(
        ("nBuBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "",
        10);  // 0, 100);
    // ---------------------------- PDFs π ----------------------------
    RooCBShape pdfBuBu2Dst0pi_D0pi0(
        ("pdfBuBu2Dst0pi_D0pi0_" + std::to_string(i)).c_str(), "", buMass,
        meanBuBu2Dst0pi_D0pi0, sigmaBuBu2Dst0pi_D0pi0, aBuBu2Dst0pi_D0pi0,
        nBuBu2Dst0pi_D0pi0);
    // ---------------------------- PDFs K ----------------------------
    RooCBShape pdfBuBu2Dst0K_D0pi0(
        ("pdfBuBu2Dst0K_D0pi0_" + std::to_string(i)).c_str(), "", buMass,
        meanBuBu2Dst0pi_D0pi0, sigmaBuBu2Dst0K_D0pi0, aBuBu2Dst0pi_D0pi0,
        nBuBu2Dst0pi_D0pi0);

    // ---------------------------- Mis-Reconstructed Background
    // ----------------------------
    // // ---------------------------- Delta: π/K shared
    // ----------------------------
    RooRealVar thresholdDeltaMisRecPi(
        ("thresholdDeltaMisRecPi_" + std::to_string(i)).c_str(), "",
        5.7223e+01);  //, 40, 70);
    RooRealVar cDeltaMisRecPi(("cDeltaMisRecPi_" + std::to_string(i)).c_str(),
                              "",
                              3.1867e+01);  //, 0, 100);
    RooRealVar aDeltaMisRecPi(("aDeltaMisRecPi_" + std::to_string(i)).c_str(),
                              "",
                              1.2396e+00);  //, -2, 2);
    RooRealVar bDeltaMisRecPi(("bDeltaMisRecPi_" + std::to_string(i)).c_str(),
                              "", -1.7973e+00);  //, -2, 2);
    RooDstD0BG pdfDeltaMisRecPi(
        ("pdfDeltaMisRecPi_" + std::to_string(i)).c_str(), "", deltaMass,
        thresholdDeltaMisRecPi, cDeltaMisRecPi, aDeltaMisRecPi, bDeltaMisRecPi);
    // ---------------------------- Bu: π/K separate
    // ----------------------------
    // // ---------------------------- Mean π ----------------------------
    RooRealVar meanBuMisRecPi(("meanBuMisRecPi_" + std::to_string(i)).c_str(),
                              "", 5.2991e+03);  //, 5280, 5310);
    // // ---------------------------- Mean K ----------------------------
    // RooRealVar meanBuMisRecK(("meanBuMisRecK_" + std::to_string(i)).c_str(),
    // "",
    //                          5.2991e+03, 5280, 5310);
    // // ---------------------------- Sigmas π ----------------------------
    RooRealVar sigmaBuMisRecPi(("sigmaBuMisRecPi_" + std::to_string(i)).c_str(),
                               "", 9.4812e+01);  //, 80, 110);
    // // ---------------------------- Sigmas K ----------------------------
    // RooRealVar sigmaBuMisRecK(("sigmaBuMisRecK_" +
    // std::to_string(i)).c_str(),
    //                           "", 9.4812e+01, 80, 110);
    // ---------------------------- Tails ----------------------------
    RooRealVar aBuMisRecPi(("aBuMisRecPi_" + std::to_string(i)).c_str(), "",
                           2.6265e+00);  // 0, 5);
    RooRealVar nBuMisRecPi(("nBuMisRecPi_" + std::to_string(i)).c_str(), "",
                           9.9921e-01);  // 0, 100);
    // ---------------------------- PDFs π ----------------------------
    RooCBShape pdfBuMisRecPi(("pdfBuMisRecPi_" + std::to_string(i)).c_str(), "",
                             buMass, meanBuMisRecPi, sigmaBuMisRecPi,
                             aBuMisRecPi, nBuMisRecPi);
    // ---------------------------- PDFs K ----------------------------
    RooCBShape pdfBuMisRecK(("pdfBuMisRecK_" + std::to_string(i)).c_str(), "",
                            buMass, meanBuMisRecPi, sigmaBuMisRecPi,
                            aBuMisRecPi, nBuMisRecPi);

    // // ---------------------------- Mean ----------------------------
    // RooRealVar meanBuMisRecPi(("meanBuMisRecPi_" +
    // std::to_string(i)).c_str(),
    // "",
    //                     5.3164e+03);  //, 5280, 5310);
    // // // ---------------------------- Sigmas ----------------------------
    // RooRealVar sigmaLBuMisRecPiPi(("sigmaLBuMisRecPiPi_" +
    // std::to_string(i)).c_str(), "",
    //                      1.1455e+02);  //, 50, 100);
    // RooRealVar sigmaRBuMisRecPiPi(("sigmaRBuMisRecPiPi_" +
    // std::to_string(i)).c_str(), "",
    //                      8.5687e+01);  //, 50, 100);
    // // ---------------------------- Tails ----------------------------
    // RooRealVar aLBuMisRecPi(("aLBuMisRecPi_" + std::to_string(i)).c_str(),
    // "",
    //                  2.4412e-05);  // 0, 5);
    // RooRealVar aRBuMisRecPi(("aRBuMisRecPi_" + std::to_string(i)).c_str(),
    // "",
    //                  1.8396e-07);  // 0, 100);
    // // ---------------------------- PDFs ----------------------------
    // RooCruijff pdfBuMisRecPiPi(("pdfBuMisRecPiPi_" +
    // std::to_string(i)).c_str(),
    // "",
    // buMass,
    //                    meanBuMisRecPi, sigmaLBuMisRecPiPi, aLBuMisRecPi,
    //                    aRBuMisRecPi);

    // ---------------------------- Bu2D0pi Background
    // ----------------------------
    // ---------------------------- Delta: π/K shared
    // ----------------------------
    // ---------------------------- Mean ----------------------------
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
    // ---------------------------- Bu: π/K separate
    // ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanBuBu2D0pi(("meanBuBu2D0pi_" + std::to_string(i)).c_str(), "",
                             5.5263e+03);  //, 5500, 5550);
    // // ---------------------------- Sigmas π ----------------------------
    RooRealVar sigmaLBuBu2D0pi(("sigmaLBuBu2D0pi_" + std::to_string(i)).c_str(),
                               "",
                               8.8227e+01);  //, 70, 100);
    RooRealVar sigmaRBuBu2D0pi(("sigmaRBuBu2D0pi_" + std::to_string(i)).c_str(),
                               "", 7.6224e+01);  //, 70, 100);
    // // ---------------------------- Sigmas K ----------------------------
    RooRealVar relativeSigmaBuBu2D0pi(
        ("relativeSigmaBuBu2D0pi_" + std::to_string(i)).c_str(), "",
        0.95);  //, 0.7, 1.1);
    RooFormulaVar sigmaLBuBu2D0K(
        ("sigmaLBuBu2D0K_" + std::to_string(i)).c_str(), "", "@0*@1",
        RooArgList(sigmaLBuBu2D0pi, relativeSigmaBuBu2D0pi));
    RooFormulaVar sigmaRBuBu2D0K(
        ("sigmaRBuBu2D0K_" + std::to_string(i)).c_str(), "", "@0*@1",
        RooArgList(sigmaRBuBu2D0pi, relativeSigmaBuBu2D0pi));
    // ---------------------------- Tails ----------------------------
    RooRealVar aLBuBu2D0pi(("aLBuBu2D0pi_" + std::to_string(i)).c_str(), "",
                           6.7243e-09);  // 0, 5);
    RooRealVar aRBuBu2D0pi(("aRBuBu2D0pi_" + std::to_string(i)).c_str(), "",
                           2.1226e-11);  //, 0, 1);
    // ---------------------------- PDFs π ----------------------------
    RooCruijff pdfBuBu2D0pi(("pdfBuBu2D0pi_" + std::to_string(i)).c_str(), "",
                            buMass, meanBuBu2D0pi, sigmaLBuBu2D0pi,
                            sigmaRBuBu2D0pi, aLBuBu2D0pi, aRBuBu2D0pi);
    // ---------------------------- PDFs K ----------------------------
    RooCruijff pdfBuBu2D0K(("pdfBuBu2D0K_" + std::to_string(i)).c_str(), "",
                           buMass, meanBuBu2D0pi, sigmaLBuBu2D0K,
                           sigmaRBuBu2D0K, aLBuBu2D0pi, aRBuBu2D0pi);

    // ---------------------------- Add PDFs and yields
    // ----------------------------

    RooArgSet yieldsDeltaPi;
    yieldsDeltaPi.add(yieldDeltaBu2Dst0pi_D0gamma);
    yieldsDeltaPi.add(yieldDeltaBu2Dst0pi_D0pi0);
    yieldsDeltaPi.add(yieldDeltaMisRecPi);
    yieldsDeltaPi.add(yieldDeltaBu2D0pi);

    RooArgSet functionsDeltaPi;
    functionsDeltaPi.add(pdfDeltaBu2Dst0pi_D0gamma);
    functionsDeltaPi.add(pdfDeltaBu2Dst0pi_D0pi0);
    functionsDeltaPi.add(pdfDeltaMisRecPi);
    functionsDeltaPi.add(pdfDeltaBu2D0pi);
    RooAddPdf pdfDeltaPi(("pdfDeltaPi_" + std::to_string(i)).c_str(), "",
                         functionsDeltaPi, yieldsDeltaPi);

    RooArgSet yieldsBuPi;
    yieldsBuPi.add(yieldBuBu2Dst0pi_D0gamma);
    yieldsBuPi.add(yieldBuBu2Dst0pi_D0pi0);
    yieldsBuPi.add(yieldBuMisRecPi);
    yieldsBuPi.add(yieldBuBu2D0pi);

    RooArgSet functionsBuPi;
    functionsBuPi.add(pdfBuBu2Dst0pi_D0gamma);
    functionsBuPi.add(pdfBuBu2Dst0pi_D0pi0);
    functionsBuPi.add(pdfBuMisRecPi);
    functionsBuPi.add(pdfBuBu2D0pi);
    RooAddPdf pdfBuPi(("pdfBuPi_" + std::to_string(i)).c_str(), "",
                      functionsBuPi, yieldsBuPi);

    RooArgSet yieldsDeltaK;
    yieldsDeltaK.add(yieldDeltaBu2Dst0K_D0gamma);
    yieldsDeltaK.add(yieldDeltaBu2Dst0K_D0pi0);
    yieldsDeltaK.add(yieldDeltaMisRecK);
    yieldsDeltaK.add(yieldDeltaBu2D0K);

    RooArgSet functionsDeltaK;
    functionsDeltaK.add(pdfDeltaBu2Dst0pi_D0gamma);
    functionsDeltaK.add(pdfDeltaBu2Dst0pi_D0pi0);
    functionsDeltaK.add(pdfDeltaMisRecPi);
    functionsDeltaK.add(pdfDeltaBu2D0pi);
    RooAddPdf pdfDeltaK(("pdfDeltaK_" + std::to_string(i)).c_str(), "",
                        functionsDeltaK, yieldsDeltaK);

    RooArgSet yieldsBuK;
    yieldsBuK.add(yieldBuBu2Dst0K_D0gamma);
    yieldsBuK.add(yieldBuBu2Dst0K_D0pi0);
    yieldsBuK.add(yieldBuMisRecK);
    yieldsBuK.add(yieldBuBu2D0K);

    RooArgSet functionsBuK;
    functionsBuK.add(pdfBuBu2Dst0K_D0gamma);
    functionsBuK.add(pdfBuBu2Dst0K_D0pi0);
    functionsBuK.add(pdfBuMisRecK);
    functionsBuK.add(pdfBuBu2D0K);
    RooAddPdf pdfBuK(("pdfBuK_" + std::to_string(i)).c_str(), "", functionsBuK,
                     yieldsBuK);

    // ---------------------------- Construct Sim PDF
    // ----------------------------
    RooSimultaneous simPdf(("simPdf_" + std::to_string(i)).c_str(), "",
                           category);
    simPdf.addPdf(pdfDeltaPi,
                  EnumToCategory(Variable::delta, Bachelor::pi).c_str());
    simPdf.addPdf(pdfBuPi, EnumToCategory(Variable::bu, Bachelor::pi).c_str());
    simPdf.addPdf(pdfDeltaK,
                  EnumToCategory(Variable::delta, Bachelor::K).c_str());
    simPdf.addPdf(pdfBuK, EnumToCategory(Variable::bu, Bachelor::K).c_str());

    std::cout << "Created simPdf for iteration " << i << "\n";

    if (option == Option::fitData) {
      std::vector<RooDataSet> dsVec;
      std::cout << "Number of datasets = "
                << filenamesPi.size() + filenamesK.size() << "\n";
      for (unsigned int f = 0; f < filenamesPi.size(); ++f) {
        if (!file_exists(filenamesPi[f])) {
          std::cerr << filenamesPi[f] << " does not exist.\n";
        } else if (!file_exists(filenamesK[f])) {
          std::cerr << filenamesK[f] << " does not exist.\n";
        } else {
          dsVec.emplace_back(ExtractDataSet(
              option, Bachelor::pi, filenamesPi[f], buMass, deltaMass, category,
              box_bu_low, box_bu_high, box_delta_low, box_delta_high, f));
          dsVec.emplace_back(ExtractDataSet(
              option, Bachelor::K, filenamesK[f], buMass, deltaMass, category,
              box_bu_low, box_bu_high, box_delta_low, box_delta_high, f));
        }
      }
      std::cout << "Entries in dsVec = " << dsVec.size() << "\n";
      RooDataSet combData = dsVec[0];
      for (unsigned int d = 0; d < dsVec.size() - 1; ++d) {
        combData.append(dsVec[d + 1]);
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
              RooFit::Save(), RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
              RooFit::Offset(true), RooFit::NumCPU(8, 2)));

      std::cout << "Plotting projections of m[Bu] for π bachelor.\n";
      PlotComponent(Variable::bu, Bachelor::pi, buMass, dataHist.get(), simPdf,
                    category, pdfBuBu2Dst0pi_D0gamma, pdfBuBu2Dst0pi_D0pi0,
                    pdfBuMisRecPi, pdfBuBu2D0pi, outputDir, box_delta_low,
                    box_delta_high, box_bu_low, box_bu_high);
      std::cout << "Plotting projections of m[Delta] for π bachelor.\n";
      PlotComponent(Variable::delta, Bachelor::pi, deltaMass, dataHist.get(),
                    simPdf, category, pdfDeltaBu2Dst0pi_D0gamma,
                    pdfDeltaBu2Dst0pi_D0pi0, pdfDeltaMisRecPi, pdfDeltaBu2D0pi,
                    outputDir, box_delta_low, box_delta_high, box_bu_low,
                    box_bu_high);
      std::cout << "Plotting projections of m[Bu] for K bachelor.\n";
      PlotComponent(Variable::bu, Bachelor::K, buMass, dataHist.get(), simPdf,
                    category, pdfBuBu2Dst0K_D0gamma, pdfBuBu2Dst0K_D0pi0,
                    pdfBuMisRecK, pdfBuBu2D0K, outputDir, box_delta_low,
                    box_delta_high, box_bu_low, box_bu_high);
      std::cout << "Plotting projections of m[Delta] for K bachelor.\n";
      PlotComponent(Variable::delta, Bachelor::K, deltaMass, dataHist.get(),
                    simPdf, category, pdfDeltaBu2Dst0pi_D0gamma,
                    pdfDeltaBu2Dst0pi_D0pi0, pdfDeltaMisRecPi, pdfDeltaBu2D0pi,
                    outputDir, box_delta_low, box_delta_high, box_bu_low,
                    box_bu_high);
      std::cout << "Plotting correlation matrix\n";
      PlotCorrMatrix(result.get(), outputDir, box_delta_low, box_delta_high,
                     box_bu_low, box_bu_high);

      result->Print("v");

      double errYieldTotBu2Dst0pi_D0gamma =
          yieldTotBu2Dst0pi_D0gamma.getPropagatedError(*result) *
          ((yieldSharedBu2Dst0pi_D0gamma.getVal() /
            yieldTotBu2Dst0pi_D0gamma.getVal()) *
               std::sqrt(2) +
           1 -
           yieldSharedBu2Dst0pi_D0gamma.getVal() /
               yieldTotBu2Dst0pi_D0gamma.getVal());
      std::cout << "yieldSharedBu2Dst0pi_D0gamma = "
                << yieldSharedBu2Dst0pi_D0gamma.getVal() << " ± "
                << yieldSharedBu2Dst0pi_D0gamma.getPropagatedError(*result)
                << "\n";
      std::cout << "yieldTotBu2Dst0pi_D0gamma = "
                << yieldTotBu2Dst0pi_D0gamma.getVal() << " ± "
                << errYieldTotBu2Dst0pi_D0gamma << "\n";
      std::cout << "Corrected error / fit Error = "
                << errYieldTotBu2Dst0pi_D0gamma /
                       yieldTotBu2Dst0pi_D0gamma.getPropagatedError(*result)
                << "\n";
    } else if (option == Option::save2DToy) {
      std::cout << "Option: saving 2D toy\n";
      std::vector<RooDataSet> dsVecPi;
      std::vector<RooDataSet> dsVecK;
      std::cout << "Number of datasets = "
                << filenamesPi.size() + filenamesK.size() << "\n";
      for (unsigned int f = 0; f < filenamesPi.size(); ++f) {
        if (!file_exists(filenamesPi[f])) {
          std::cerr << filenamesPi[f] << " does not exist.\n";
        } else if (!file_exists(filenamesK[f])) {
          std::cerr << filenamesK[f] << " does not exist.\n";
        } else {
          std::cout << "Extracting dataset for " << filenamesPi[f] << " and "
                    << filenamesK[f] << "\n";
          dsVecPi.emplace_back(ExtractDataSet(
              option, Bachelor::pi, filenamesPi[f], buMass, deltaMass, category,
              box_bu_low, box_bu_high, box_delta_low, box_delta_high, f));
          dsVecK.emplace_back(ExtractDataSet(
              option, Bachelor::K, filenamesK[f], buMass, deltaMass, category,
              box_bu_low, box_bu_high, box_delta_low, box_delta_high, f));
        }
      }
      std::cout << "Entries in dsVec = " << dsVecPi.size() << "\n";
      std::cout << "Entries in dsVec = " << dsVecK.size() << "\n";

      RooDataSet combDataPi = dsVecPi[0];
      RooDataSet combDataK = dsVecK[0];
      for (unsigned int d = 0; d < dsVecPi.size() - 1; ++d) {
        combDataPi.append(dsVecPi[d + 1]);
        combDataK.append(dsVecK[d + 1]);
      }
      std::cout << "Appended roodatasets" << std::endl;
      combDataPi.Print();
      combDataK.Print();

      auto dataHistPi = std::unique_ptr<RooDataHist>(combDataPi.binnedClone(
          ("dataHistPi_" + std::to_string(i)).c_str(), "dataHistPi"));
      auto dataHistK = std::unique_ptr<RooDataHist>(combDataK.binnedClone(
          ("dataHistK_" + std::to_string(i)).c_str(), "dataHistK"));

      RooHistPdf histPdfPi(("histPdfPi_" + std::to_string(i)).c_str(), "",
                           RooArgSet(buMass, deltaMass), *dataHistPi.get(), 2);
      RooHistPdf histPdfK(("histPdfK_" + std::to_string(i)).c_str(), "",
                          RooArgSet(buMass, deltaMass), *dataHistK.get(), 2);

      RooRandom::randomGenerator()->SetSeed(0);
      TRandom3 random(0);

      RooDataSet *toyDataPi = histPdfPi.generate(RooArgSet(buMass, deltaMass),
                                                 combDataPi.numEntries());
      std::cout << "Generated π dataset!" << std::endl;
      toyDataPi->Print();
      RooDataSet *toyDataK = histPdfK.generate(RooArgSet(buMass, deltaMass),
                                               combDataK.numEntries());
      std::cout << "Generated K dataset!" << std::endl;
      toyDataK->Print();

      // PlotGeneratedData(Bachelor::pi, buMass, deltaMass, dataHistPi.get(), toyDataPi,
      //                   histPdfPi, outputDir);
      // PlotGeneratedData(Bachelor::K, buMass, deltaMass, dataHistK.get(), toyDataK,
      //                   histPdfK, outputDir);

      double randomTag = random.Rndm();
      TFile dsFilePi(
          (outputDir + "/DataFilePi2D_" + std::to_string(randomTag) + ".root")
              .c_str(),
          "RECREATE");
      toyDataPi->Write("inputDataSet");
      dsFilePi.Close();
      TFile dsFileK(
          (outputDir + "/DataFileK2D_" + std::to_string(randomTag) + ".root")
              .c_str(),
          "RECREATE");
      toyDataK->Write("inputDataSet");
      dsFileK.Close();
      std::cout << "Saved " << randomTag << " datasets for π and K\n";
    } else if (option == Option::saveD1DToy) {
      RooRandom::randomGenerator()->SetSeed(0);
      TRandom3 random(0);
      double randomTag = random.Rndm();

      double nEvtsPerToyBuPi =
          yieldBuBu2Dst0pi_D0gamma.getVal() + yieldBuBu2Dst0pi_D0pi0.getVal() +
          yieldBuMisRecPi.getVal() + yieldBuBu2D0pi.getVal();
      double nEvtsPerToyDeltaPi = yieldDeltaBu2Dst0pi_D0gamma.getVal() +
                                  yieldDeltaBu2Dst0pi_D0pi0.getVal() +
                                  yieldDeltaMisRecPi.getVal() +
                                  yieldDeltaBu2D0pi.getVal();

      // Generate bu and delta mass datasets separately from individual PDFs
      // Saving simPdf as one PDF reduces number of events by 1/2 in each
      // dimension
      // Saving each variable from simPdf doesn't work (not sure what it
      // does!)
      // - completely flat in delta mass dimension (data has no structure)
      RooDataSet *buPiDataSet =
          pdfBuPi.generate(RooArgSet(buMass), nEvtsPerToyBuPi);
      std::cout << "Generated!\n";
      buPiDataSet->SetName("buPiDataSet");
      buPiDataSet->Print();

      RooDataSet *deltaPiDataSet =
          pdfDeltaPi.generate(RooArgSet(deltaMass), nEvtsPerToyDeltaPi);
      std::cout << "Generated!\n";
      deltaPiDataSet->SetName("deltaPiDataSet");
      deltaPiDataSet->Print();

      TFile dsPiFile((outputDir + "/DataFilePi1D_" + box_delta_low + "_" +
                      box_delta_high + "_" + box_bu_low + "_" + box_bu_high +
                      "_" + std::to_string(randomTag) + ".root")
                         .c_str(),
                     "RECREATE");
      buPiDataSet->Write("buPiDataSet");
      deltaPiDataSet->Write("deltaPiDataSet");
      dsPiFile.Close();

      double nEvtsPerToyBuK = yieldBuBu2Dst0K_D0gamma.getVal() +
                              yieldBuBu2Dst0K_D0pi0.getVal() +
                              yieldBuMisRecK.getVal() + yieldBuBu2D0K.getVal();
      double nEvtsPerToyDeltaK = yieldDeltaBu2Dst0K_D0gamma.getVal() +
                                 yieldDeltaBu2Dst0K_D0pi0.getVal() +
                                 yieldDeltaMisRecK.getVal() +
                                 yieldDeltaBu2D0K.getVal();

      RooDataSet *buKDataSet =
          pdfBuK.generate(RooArgSet(buMass), nEvtsPerToyBuK);
      std::cout << "Generated!\n";
      buKDataSet->SetName("buKDataSet");
      buKDataSet->Print();

      RooDataSet *deltaKDataSet =
          pdfDeltaK.generate(RooArgSet(deltaMass), nEvtsPerToyDeltaK);
      std::cout << "Generated!\n";
      deltaKDataSet->SetName("deltaKDataSet");
      deltaKDataSet->Print();

      TFile dsKFile((outputDir + "/DataFileK1D_" + box_delta_low + "_" +
                     box_delta_high + "_" + box_bu_low + "_" + box_bu_high +
                     "_" + std::to_string(randomTag) + ".root")
                        .c_str(),
                    "RECREATE");
      buKDataSet->Write("buKDataSet");
      deltaKDataSet->Write("deltaKDataSet");
      dsKFile.Close();

      std::cout << "Saved " << randomTag << " datasets\n";
    } else {
      if (!file_exists(filenamesPi[i])) {
        std::cerr << filenamesPi[i] << " does not exist.\n";
      } else if (!file_exists(filenamesK[i])) {
        std::cerr << filenamesK[i] << " does not exist.\n";
      } else {
        std::regex rexp("[A-Za-z0-9_]+_([0-9].[0-9]+).root");
        std::smatch match;
        std::regex_search(filenamesPi[i], match, rexp);
        std::string rndm = match[1];

        // ---------------------------- Read in toy dataset
        // ----------------------------
        int it = 0;
        RooDataSet combData = ExtractDataSet(
            option, Bachelor::pi, filenamesPi[i], buMass, deltaMass, category,
            box_bu_low, box_bu_high, box_delta_low, box_delta_high, it);
        RooDataSet combDataK = ExtractDataSet(
            option, Bachelor::K, filenamesK[i], buMass, deltaMass, category,
            box_bu_low, box_bu_high, box_delta_low, box_delta_high, it);
        combData.append(combDataK);
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

        // if (i == 0) {
        //   std::cout << "Plotting projections of m[Bu] for π bachelor.\n";
        //   PlotComponent(Variable::bu, Bachelor::pi, buMass, toyDataHist.get(),
        //                 simPdf, category, pdfBuBu2Dst0pi_D0gamma,
        //                 pdfBuBu2Dst0pi_D0pi0, pdfBuMisRecPi, pdfBuBu2D0pi,
        //                 outputDir, box_delta_low, box_delta_high, box_bu_low,
        //                 box_bu_high);
        //   std::cout << "Plotting projections of m[Delta] for π bachelor.\n";
        //   PlotComponent(Variable::delta, Bachelor::pi, deltaMass,
        //                 toyDataHist.get(), simPdf, category,
        //                 pdfDeltaBu2Dst0pi_D0gamma, pdfDeltaBu2Dst0pi_D0pi0,
        //                 pdfDeltaMisRecPi, pdfDeltaBu2D0pi, outputDir,
        //                 box_delta_low, box_delta_high, box_bu_low, box_bu_high);
        //   std::cout << "Plotting projections of m[Bu] for K bachelor.\n";
        //   PlotComponent(Variable::bu, Bachelor::K, buMass, toyDataHist.get(),
        //                 simPdf, category, pdfBuBu2Dst0K_D0gamma,
        //                 pdfBuBu2Dst0K_D0pi0, pdfBuMisRecK, pdfBuBu2D0K,
        //                 outputDir, box_delta_low, box_delta_high, box_bu_low,
        //                 box_bu_high);
        //   std::cout << "Plotting projections of m[Delta] for K bachelor.\n";
        //   PlotComponent(Variable::delta, Bachelor::K, deltaMass,
        //                 toyDataHist.get(), simPdf, category,
        //                 pdfDeltaBu2Dst0pi_D0gamma, pdfDeltaBu2Dst0pi_D0pi0,
        //                 pdfDeltaMisRecPi, pdfDeltaBu2D0pi, outputDir,
        //                 box_delta_low, box_delta_high, box_bu_low, box_bu_high);
        //   std::cout << "Plotting correlation matrix\n";
        //   PlotCorrMatrix(result.get(), outputDir, box_delta_low, box_delta_high,
        //                  box_bu_low, box_bu_high);
        // }
        result->Print("v");
        // if (meanDeltaBu2Dst0pi_D0gamma.getError() > 0.069) {
        //   std::cout << "GAMMA DELTA MEAN IN SECOND MIN\n";
        //   std::cout << "EDM = " << result->edm() << "\n";
        // } else {
        //   std::cout << "GAMMA DELTA MEAN IN FIRST MIN\n";
        //   std::cout << "EDM = " << result->edm() << "\n";
        // }
        // if (sigmaDeltaBu2Dst0pi_D0gamma.getError() > 0.0665) {
        //   std::cout << "GAMMA DELTA SIGMA IN SECOND MIN\n";
        //   std::cout << "EDM = " << result->edm() << "\n";
        // } else {
        //   std::cout << "GAMMA DELTA SIGMA IN FIRST MIN\n";
        //   std::cout << "EDM = " << result->edm() << "\n";
        // }
        // if (meanDeltaBu2Dst0pi_D0pi0.getError() > 0.097) {
        //   std::cout << "PI0 DELTA MEAN IN SECOND MIN\n";
        //   std::cout << "EDM = " << result->edm() << "\n";
        // } else {
        //   std::cout << "PI0 DELTA MEAN IN FIRST MIN\n";
        //   std::cout << "EDM = " << result->edm() << "\n";
        // }

        // Essentially just fitErr * sqrt((boxEff * sqrt(2))^2 + (1-boxEff)^2)
        // double errYieldTotBu2Dst0pi_D0gamma =
        //     yieldTotBu2Dst0pi_D0gamma.getPropagatedError(*result) *
        //     ((yieldSharedBu2Dst0pi_D0gamma.getVal() /
        //     yieldTotBu2Dst0pi_D0gamma.getVal()) *
        //              std::sqrt(2)+
        //         1 - yieldSharedBu2Dst0pi_D0gamma.getVal() /
        //         yieldTotBu2Dst0pi_D0gamma.getVal());
        // std::cout << "Box = " << box_delta_low << "-" << box_delta_high <<
        // "
        // "
        //           << box_bu_low << "-" << box_bu_high << "\n";
        // std::cout << "yieldSharedBu2Dst0pi_D0gamma = " <<
        // yieldSharedBu2Dst0pi_D0gamma.getVal()
        // <<
        // " ± "
        //           <<
        //           yieldSharedBu2Dst0pi_D0gamma.getPropagatedError(*result)
        //           << "\n";
        // std::cout << "yieldTotBu2Dst0pi_D0gamma = " <<
        // yieldTotBu2Dst0pi_D0gamma.getVal() << " ±
        // "
        //           << errYieldTotBu2Dst0pi_D0gamma << "\n";
        // std::cout << "Corrected error / fit Error = "
        //           << errYieldTotBu2Dst0pi_D0gamma /
        //                  yieldTotBu2Dst0pi_D0gamma.getPropagatedError(*result)
        //           << "\n";
        // std::cout << "Corrected error / fit Error = "
        //           << errYieldTotBu2Dst0pi_D0gamma /
        //           yieldTotBu2Dst0pi_D0gamma.getError() << "\n";
        std::string dim;
        if (option == Option::fit2DToy) {
          dim = "2";
        } else {
          dim = "1";
        }
        TFile outputFile((outputDir + "/Result" + dim + "D_" + rndm + "_" +
                          box_delta_low + "_" + box_delta_high + "_" +
                          box_bu_low + "_" + box_bu_high + ".root")
                             .c_str(),
                         "recreate");
        outputFile.cd();
        result->SetName(("Result_" + rndm).c_str());
        result->Write();
        // Don't save corrected error for now - see if we can get error from
        // pulls
        // TTree tree("tree", "");
        // tree.Branch("errYieldTotBu2Dst0pi_D0gamma",
        // &errYieldTotBu2Dst0pi_D0gamma,
        // "errYieldTotBu2Dst0pi_D0gamma/D");
        // double orEffBu2Dst0pi_D0gammaD = orEffBu2Dst0pi_D0gamma.getVal();
        // tree.Branch("orEffBu2Dst0pi_D0gamma", &orEffBu2Dst0pi_D0gammaD,
        // "orEffBu2Dst0pi_D0gamma/D");
        // double boxEffBu2Dst0pi_D0gammaD = boxEffBu2Dst0pi_D0gamma.getVal();
        // tree.Branch("boxEffBu2Dst0pi_D0gamma", &boxEffBu2Dst0pi_D0gammaD,
        // "boxEffBu2Dst0pi_D0gamma/D");
        // tree.Fill();
        // tree.Write();
        outputFile.Write();
        outputFile.Close();
        std::cout << "Written result to file " << outputFile.GetName() << "\n";
      }
    }
  }
}

int main(int argc, char *argv[]) {
  std::string instructions1 =
      "\t1) Saving D1D toy datasets generated from the D1D model:\n\t\t Enter: "
      "'1', output directory, low delta "
      "box dimn, high delta box dimn, low bu box dimn, high bu box dimn, # of "
      "datasets to save\n";
  std::string instructions2 =
      "\t2) Saving a 2D toy dataset generated from 2D data:\n\t\t Enter: '2', "
      "output directory,# of "
      "datasets to save, π input "
      "datasets, K input datasets\n";
  std::string instructions3 =
      "\t3) Fitting the D1D model to D1D toy datasets:\n\t\t Enter: '3', "
      "output directory, low delta box dimn, high delta "
      "box dimn, low bu box dimn, high bu box dimn, π input datasets, K input "
      "datasets\n";
  std::string instructions4 =
      "\t4) Fitting the D1D model to 2D toy datasets:\n\t\t Enter: '4', "
      "output directory, low delta box dimn, high delta box dimn, "
      "low bu box dimn, high bu box dimn, pi input datasets, K input "
      "datasets\n";
  std::string instructions5 =
      "\t5) Fitting the D1D model to data:\n\t\t Enter: '5', "
      "output directory, low delta box dimn, high delta box dimn, low bu box "
      "dimn, high bu box dimn, π input datasets, K input datasets\n";
  std::string instructions = "There are 5 options for running this macro:\n" +
                             instructions1 + instructions2 + instructions3 +
                             instructions4 + instructions5;
  if (argc < 2) {
    std::cerr << instructions;
    return 1;
  }

  Option option;
  {
    int nOption = std::atoi(argv[1]);
    if (nOption == 1) {
      option = Option::saveD1DToy;
      if (argc != 8) {
        std::cerr << instructions1;
        return 1;
      }
    } else if (nOption == 2) {
      option = Option::save2DToy;
      if (argc != 6) {
        std::cerr << instructions2;
        return 1;
      }
    } else if (nOption == 3) {
      option = Option::fitD1DToy;
      if (argc != 9) {
        std::cerr << instructions3;
        return 1;
      }
    } else if (nOption == 4) {
      option = Option::fit2DToy;
      if (argc != 9) {
        std::cerr << instructions4;
        return 1;
      }
    } else if (nOption == 5) {
      option = Option::fitData;
      if (argc != 9) {
        std::cerr << instructions5;
        return 1;
      }
    } else {
      std::cerr << instructions;
      return 1;
    }
  }

  std::string outputDir = argv[2];
  std::string box_delta_low = "";
  std::string box_delta_high = "";
  std::string box_bu_low = "";
  std::string box_bu_high = "";
  int nIter;
  std::vector<std::string> filenames;
  std::vector<std::string> filenamesK;

  if (option == Option::saveD1DToy) {
    box_delta_low = argv[3];
    box_delta_high = argv[4];
    box_bu_low = argv[5];
    box_bu_high = argv[6];
    nIter = std::atoi(argv[7]);
  } else if (option == Option::save2DToy) {
    nIter = std::atoi(argv[3]);
    std::string inputPi = argv[4];
    filenames = SplitByComma(inputPi);
    std::string inputK = argv[5];
    filenamesK = SplitByComma(inputK);
    if (filenames.size() != filenamesK.size()) {
      std::cerr
          << "Must provide same number of π and K datasets. Currently, π = "
          << filenames.size() << " and K = " << filenamesK.size() << "\n";
    }
  } else {
    box_delta_low = argv[3];
    box_delta_high = argv[4];
    box_bu_low = argv[5];
    box_bu_high = argv[6];
    std::string inputPi = argv[7];
    filenames = SplitByComma(inputPi);
    std::string inputK = argv[8];
    filenamesK = SplitByComma(inputK);
    if (filenames.size() != filenamesK.size()) {
      std::cerr
          << "Must provide same number of π and K datasets. Currently, π = "
          << filenames.size() << " and K = " << filenamesK.size() << "\n";
    }
    if (option == Option::fitData) {
      box_delta_low = argv[3];
      box_delta_high = argv[4];
      box_bu_low = argv[5];
      box_bu_high = argv[6];
      nIter = 1;
    } else {
      nIter = filenames.size();
    }
  }

  FitToys(option, nIter, filenames, filenamesK, outputDir, box_delta_low,
          box_delta_high, box_bu_low, box_bu_high);

  return 0;
}
