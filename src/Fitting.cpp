#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooHist.h"
#include "RooMCStudy.h"
#include "RooPlot.h"
#include "RooRandom.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TLine.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TTree.h"
#include "TTreeReader.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorDaughtersVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralVars.h"
#include "ParseArguments.h"
#include "Pdf.h"

enum class SplitByCharge { ktrue, kfalse };
enum class Toys { single, many, none };
enum class Variable { bu, delta };

std::string EnumToString(Variable variable) {
  switch (variable) {
    case Variable::bu:
      return "bu";
    case Variable::delta:
      return "delta";
  }
}

void SetStyle() {
  gStyle->SetTitleFont(132, "XYZ");
  gStyle->SetLabelFont(132, "XYZ");
  gStyle->SetStatFont(132);
  gStyle->SetStatFontSize(0.04);
  gStyle->SetTitleSize(0.06, "Z");
  gStyle->SetTitleSize(0.03, "XY");
  gStyle->SetLabelSize(0.024, "XY");
  gStyle->SetLegendFont(132);
  gStyle->SetTitleOffset(0.9, "X");
  gStyle->SetTitleOffset(1.1, "Y");
  gStyle->SetTitleOffset(0.9, "Z");
  gStyle->SetLegendTextSize(0.03);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.09);
  gStyle->SetPadLeftMargin(0.1);
}

TLegend MakeLegend(int const id, TCanvas &canvas, TPad &pad1, TPad &pad2,
                   PdfBase &pdf) {
  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();

  canvas.cd();
  pad1.cd();

  TLegend legend(0.7, 0.7, 0.97, 0.90);
  // ------------- Draw Legends -------------- //
  auto pdfSignalHist = std::make_unique<TH1D>(
      ("pdfSignalHist" + ComposeName(id, neutral, bachelor, daughters)).c_str(),
      "pdfSignalHist", 1, 0, 1);
  pdfSignalHist->SetLineColor(kBlue);
  pdfSignalHist->SetLineStyle(kDashed);
  pdfSignalHist->SetLineWidth(2);

  auto pdf_CombHist = std::make_unique<TH1D>(
      ("pdf_CombHist" + ComposeName(id, neutral, bachelor, daughters)).c_str(),
      "pdf_CombHist", 1, 0, 1);
  pdf_CombHist->SetLineColor(kRed);
  pdf_CombHist->SetLineStyle(kDashed);
  pdf_CombHist->SetLineWidth(2);

  // legend.SetHeader("Physics Backgrounds");
  legend.AddEntry(
      pdfSignalHist.get(),
      ("B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}#font[132]{[}" +
       EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}" +
       EnumToLabel(neutral) + "#font[132]{]}_{D^{0}*}" + EnumToLabel(bachelor) +
       "^{" + EnumToLabel(charge) + "}")
          .c_str(),
      "l");
  legend.AddEntry(pdf_CombHist.get(), "Combinatorial", "l");

  return legend;
}

void PlotComponent(Variable variable, RooRealVar &var, PdfBase &pdf,
                   RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                   Configuration::Categories &categories, TLegend &legend,
                   TLegend &yieldLegend, std::string const &outputDir) {
  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();
  int id = 0;

  // Stops ROOT print INFO messages
  gErrorIgnoreLevel = kWarning;

  std::unique_ptr<RooPlot> frame(var.frame(RooFit::Title(
      ("B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}#font[132]{[}" +
       EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}" +
       EnumToLabel(neutral) + "#font[132]{]}_{D^{*0}}" + EnumToLabel(bachelor) +
       "^{" + EnumToLabel(charge) + "}")
          .c_str())));

  fullDataSet.plotOn(
      frame.get(),
      RooFit::Cut(("fitting==fitting::" +
                   ComposeFittingName(neutral, bachelor, daughters, charge))
                      .c_str()));

  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(
          categories.fitting,
          ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::LineColor(kBlue));

  // auto pullHist = std::unique_ptr<RooHist>(
  //     dynamic_cast<RooHist *>(frame->RooPlot::pullHist()));
  // if (pullHist == nullptr) {
  //   throw std::runtime_error("\npullHist empty.\n");
  // }
  RooHist *pullHist = frame->RooPlot::pullHist();

  if (variable == Variable::bu) {
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdfBu_Bu2Dst0h_Dst02D0pi0()),
        RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));
    if (neutral == Neutral::gamma) {
      simPdf.plotOn(
          frame.get(),
          RooFit::Slice(
              categories.fitting,
              ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
          RooFit::ProjWData(categories.fitting, fullDataSet),
          RooFit::Components(pdf.pdfBu_Bu2Dst0h_Dst02D0gamma()),
          RooFit::LineStyle(kDashed), RooFit::LineColor(kOrange));
    }
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdfBu_Bu2D0h()),
        RooFit::LineStyle(kDashed), RooFit::LineColor(kGreen));
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdfBu_partialRec()),
        RooFit::LineStyle(kDashed), RooFit::LineColor(kMagenta));
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdfBu_Comb()), RooFit::LineStyle(kDashed),
        RooFit::LineColor(kRed));
    frame->SetXTitle(
        ("m[D*^{0}" + EnumToLabel(bachelor) + "] (MeV/c^{2})").c_str());
  } else {
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdfDelta_Bu2Dst0h_Dst02D0pi0()),
        RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));
    if (neutral == Neutral::gamma) {
      simPdf.plotOn(
          frame.get(),
          RooFit::Slice(
              categories.fitting,
              ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
          RooFit::ProjWData(categories.fitting, fullDataSet),
          RooFit::Components(pdf.pdfDelta_Bu2Dst0h_Dst02D0gamma()),
          RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));
    }
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdfDelta_Bu2D0h()),
        RooFit::LineStyle(kDashed), RooFit::LineColor(kGreen));
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdfDelta_partialRec()),
        RooFit::LineStyle(kDashed), RooFit::LineColor(kMagenta));
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdfDelta_Comb()), RooFit::LineStyle(kDashed),
        RooFit::LineColor(kRed));
    frame->SetXTitle("m[D*^{0}] - m[D^{0}] (MeV/c^{2})");
  }

  std::unique_ptr<RooPlot> pullFrame(var.frame(RooFit::Title(" ")));

  pullFrame->addPlotable(pullHist /* .get() */, "P");
  pullFrame->SetName(("pullFrame_" + EnumToString(variable) + "_" +
                      ComposeName(id, neutral, bachelor, daughters, charge))
                         .c_str());
  pullFrame->SetTitle("");

  // --------------- plot onto canvas ---------------------
  TCanvas canvas(("canvas_" + EnumToString(variable) + "_" +
                  ComposeName(id, neutral, bachelor, daughters, charge))
                     .c_str(),
                 "canvas", 1200, 1000);

  TPad pad1(("pad1_" + EnumToString(variable) + "_" +
             ComposeName(id, neutral, bachelor, daughters, charge))
                .c_str(),
            "pad1", 0.0, 0.14, 1.0, 1.0, kWhite);
  pad1.Draw();

  TPad pad2(("pad2_" + EnumToString(variable) + "_" +
             ComposeName(id, neutral, bachelor, daughters, charge))
                .c_str(),
            "pad2", 0.0, 0.05, 1.0, 0.15, kWhite);
  pad2.Draw();

  // .get() gets the raw pointer from underneath the smart pointer
  // FIX THIS
  // TLegend legend = MakeLegend(id, canvas, pad1, pad2, pdf);

  // Zero line on error plot.
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
  // yieldLegend.Draw("same");
  // dataHist->Draw("same");

  canvas.Update();
  canvas.SaveAs((outputDir + "/" +
                 ComposeName(id, neutral, bachelor, daughters, charge) + "_" +
                 EnumToString(variable) + "Mass.pdf")
                    .c_str());
}

void Plotting1D(int const id, PdfBase &pdf, Configuration &config,
                Configuration::Categories &categories,
                RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                RooFitResult const &result, std::string const &outputDir) {
  SetStyle();

  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();

  TLegend legend(0.7, 0.7, 0.97, 0.90);
  // ------------- Draw Legends -------------- //
  auto pdf_Bu2Dst0h_Dst02D0pi0_Hist = std::make_unique<TH1D>(
      ("pdf_Bu2Dst0h_Dst02D0pi0_Hist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "pdf_Bu2Dst0h_Dst02D0pi0_Hist", 1, 0, 1);
  pdf_Bu2Dst0h_Dst02D0pi0_Hist->SetLineColor(kBlue);
  pdf_Bu2Dst0h_Dst02D0pi0_Hist->SetLineStyle(kDashed);
  pdf_Bu2Dst0h_Dst02D0pi0_Hist->SetLineWidth(2);

  auto pdf_Bu2Dst0h_Dst02D0gamma_Hist = std::make_unique<TH1D>(
      ("pdf_Bu2Dst0h_Dst02D0gamma_Hist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "pdf_Bu2Dst0h_Dst02D0gamma_Hist", 1, 0, 1);
  pdf_Bu2Dst0h_Dst02D0gamma_Hist->SetLineColor(kOrange);
  pdf_Bu2Dst0h_Dst02D0gamma_Hist->SetLineStyle(kDashed);
  pdf_Bu2Dst0h_Dst02D0gamma_Hist->SetLineWidth(2);

  auto pdf_Bu2D0h_Hist = std::make_unique<TH1D>(
      ("pdf_Bu2D0h_Hist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "pdf_Bu2D0h_Hist", 1, 0, 1);
  pdf_Bu2D0h_Hist->SetLineColor(kGreen);
  pdf_Bu2D0h_Hist->SetLineStyle(kDashed);
  pdf_Bu2D0h_Hist->SetLineWidth(2);

  auto pdf_partialRec_Hist = std::make_unique<TH1D>(
      ("pdf_partialRec_Hist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "pdf_partialRec_Hist", 1, 0, 1);
  pdf_partialRec_Hist->SetLineColor(kMagenta);
  pdf_partialRec_Hist->SetLineStyle(kDashed);
  pdf_partialRec_Hist->SetLineWidth(2);

  auto pdf_CombHist = std::make_unique<TH1D>(
      ("pdf_CombHist" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "pdf_CombHist", 1, 0, 1);
  pdf_CombHist->SetLineColor(kRed);
  pdf_CombHist->SetLineStyle(kDashed);
  pdf_CombHist->SetLineWidth(2);

  // legend.SetHeader("Physics Backgrounds");
  legend.AddEntry(
      pdf_Bu2Dst0h_Dst02D0pi0_Hist.get(),
      ("B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}#font[132]{[}" +
       EnumToLabel(daughters, charge) +
       "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{0}*}" +
       EnumToLabel(bachelor) + "^{" + EnumToLabel(charge) + "}")
          .c_str(),
      "l");
  legend.AddEntry(
      pdf_Bu2Dst0h_Dst02D0gamma_Hist.get(),
      ("B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}#font[132]{[}" +
       EnumToLabel(daughters, charge) +
       "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{0}*}" +
       EnumToLabel(bachelor) + "^{" + EnumToLabel(charge) + "}")
          .c_str(),
      "l");
  legend.AddEntry(
      pdf_Bu2D0h_Hist.get(),
      ("B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}#font[132]{[}" +
       EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}" +
       EnumToLabel(bachelor) + "^{" + EnumToLabel(charge) + "}")
          .c_str(),
      "l");
  // Make only pi0 in pi0 mode (gamma removed by veto)
  switch (neutral) {
    case (Neutral::pi0): {
      legend.AddEntry(pdf_partialRec_Hist.get(),
                      ("B^{" + EnumToLabel(charge) +
                       "}#rightarrow#font[132]{[}#font[132]{[}" +
                       EnumToLabel(daughters, charge) +
                       "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{0}*}" +
                       HstLabel(bachelor) + "^{" + EnumToLabel(charge) + "}")
                          .c_str(),
                      "l");
      break;
    }
      case (Neutral::gamma): {
  legend.AddEntry(
      pdf_partialRec_Hist.get(),
      ("B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}#font[132]{[}" +
       EnumToLabel(daughters, charge) +
       "#font[132]{]}_{D^{0}}#pi^{0}/#gamma#font[132]{]}_{D^{0}*}" +
       HstLabel(bachelor) + "^{" + EnumToLabel(charge) + "}")
          .c_str(),
      "l");
      break;
      }
    }
  legend.AddEntry(pdf_CombHist.get(), "_Combinatorial", "l");

  auto blankHist = std::make_unique<TH1D>(
      ("blankHist" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "blankHist", 1, 0, 1);
  blankHist->SetLineColor(kWhite);
  blankHist->SetLineWidth(2);

  TLegend yieldLegend(0.12, 0.6, 0.3, 0.8);

  std::stringstream Bu2Dst0h_Dst02D0pi0Legend;
  std::stringstream Bu2Dst0h_Dst02D0gammaLegend;
  std::stringstream Bu2D0hLegend;
  std::stringstream partialRecLegend;
  std::stringstream combLegend;
  Bu2Dst0h_Dst02D0pi0Legend
      << "B^{" + EnumToLabel(charge) +
             "}#rightarrow#font[132]{[}#font[132]{[}" +
             EnumToLabel(daughters, charge) +
             "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{0}*}" +
             EnumToLabel(bachelor) + "^{" + EnumToLabel(charge) + "}: "
      << pdf.yield_Bu2Dst0h_Dst02D0pi0().getVal()
      // << " #pm " << pdf.yieldSignal().getPropagatedError(*result)
      << " events";
  if (neutral == Neutral::gamma) {
    Bu2Dst0h_Dst02D0gammaLegend
        << "B^{" + EnumToLabel(charge) +
               "}#rightarrow#font[132]{[}#font[132]{[}" +
               EnumToLabel(daughters, charge) +
               "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{0}*}" +
               EnumToLabel(bachelor) + "^{" + EnumToLabel(charge) + "}: "
        << pdf.yield_Bu2Dst0h_Dst02D0gamma().getVal()
        // << " #pm " << pdf.yieldSignal().getPropagatedError(*result)
        << " events";
  }
  Bu2D0hLegend << "B^{" + EnumToLabel(charge) +
                      "}#rightarrow#font[132]{[}#font[132]{[}" +
                      EnumToLabel(daughters, charge) +
                      "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{0}*}" +
                      EnumToLabel(bachelor) + "^{" + EnumToLabel(charge) + "}: "
               << pdf.yield_Bu2D0h().getVal()
               // << " #pm " << pdf.yieldSignal().getPropagatedError(*result)
               << " events";
  switch (neutral) {
    case (Neutral::pi0): {
        partialRecLegend
            << "B^{" + EnumToLabel(charge) +
                   "}#rightarrow#font[132]{[}#font[132]{[}" +
                   EnumToLabel(daughters, charge) +
                   "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{0}*}" +
                   HstLabel(bachelor) + "^{" + EnumToLabel(charge) + "}: "
            << pdf.yield_partialRec().getVal()
            // << " #pm " << pdf.yieldSignal().getPropagatedError(*result)
            << " events";
        break;
    }
      case (Neutral::gamma): {
        partialRecLegend
            << "B^{" + EnumToLabel(charge) +
                   "}#rightarrow#font[132]{[}#font[132]{[}" +
                   EnumToLabel(daughters, charge) +
                   "#font[132]{]}_{D^{0}}#pi^{0}/#gamma#font[132]{]}_{D^{0}*}" +
                   HstLabel(bachelor) + "^{" + EnumToLabel(charge) + "}: "
            << pdf.yield_partialRec().getVal()
            // << " #pm " << pdf.yieldSignal().getPropagatedError(*result)
            << " events";
      break;
      }
    }
  combLegend << "Background: "
             << pdf.yield_Comb().getVal()
             // << " #pm ";
             // << backgroundYield.getError()
             << " events";

  yieldLegend.SetLineColor(kWhite);
  // yieldLegend.AddEntry(blankHist.get(), "#int L dt = 4.8 #pm 0.13
  // fb^{-1}",
  //                       "l");
  yieldLegend.AddEntry(blankHist.get(), Bu2Dst0h_Dst02D0pi0Legend.str().c_str(),
                       "l");
  yieldLegend.AddEntry(blankHist.get(),
                       Bu2Dst0h_Dst02D0gammaLegend.str().c_str(), "l");
  yieldLegend.AddEntry(blankHist.get(), Bu2D0hLegend.str().c_str(), "l");
  yieldLegend.AddEntry(blankHist.get(), partialRecLegend.str().c_str(), "l");
  yieldLegend.AddEntry(blankHist.get(), combLegend.str().c_str(), "l");

  // ---- PLOTTING FOR BU MASS COMPONENT ---- //
  PlotComponent(Variable::bu, config.buMass(), pdf, fullDataSet, simPdf,
                categories, legend, yieldLegend, outputDir);
  // ---- PLOTTING FOR DELTA MASS COMPONENT ---- //
  PlotComponent(Variable::delta, config.deltaMass(), pdf, fullDataSet, simPdf,
                categories, legend, yieldLegend, outputDir);
}

void Plotting2D(int const id, PdfBase &pdf, Configuration &config,
                RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                std::string const &outputDir) {
  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();

  gStyle->SetTitleSize(0.03, "XYZ");
  gStyle->SetLabelSize(0.025, "XYZ");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetTitleOffset(1.5, "Z");
  gStyle->SetPadRightMargin(0.15);

  // Make two-dimensional plot of sampled PDF in x vs y
  // Plot ONLY the PDF not the SimPDF
  // auto singlePdf =
  //     std::unique_ptr<RooAbsPdf>(simPdf.getPdf(pdf.CategoryName().c_str()));
  auto singlePdf = simPdf.getPdf(pdf.CategoryName().c_str());
  if (singlePdf == nullptr) {
    throw std::runtime_error("\nSingle pdf empty\n");
  }

  // auto modelHist1d = std::unique_ptr<TH1>(singlePdf->createHistogram(
  //     ("modelHist2d_" + ComposeName(id, neutral, bachelor, daughters,
  //     charge))
  //         .c_str(),
  //     config.buMass(), RooFit::Binning(config.buMass().getBins()),
  //     RooFit::YVar(config.deltaMass(),
  //                  RooFit::Binning(config.deltaMass().getBins()))));
  auto modelHist1d = singlePdf->createHistogram(
      ("modelHist2d_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      config.buMass(), RooFit::Binning(config.buMass().getBins()),
      RooFit::YVar(config.deltaMass(),
                   RooFit::Binning(config.deltaMass().getBins())));
  if (modelHist1d == nullptr) {
    throw std::runtime_error("\n1D hist of pdf returns nullptr\n");
  }
  auto modelHist2d =
      std::unique_ptr<TH2>(dynamic_cast<TH2F *>(modelHist1d /* .get() */));
  if (modelHist2d == nullptr) {
    throw std::runtime_error("\n2D hist of pdf returns nullptr\n");
  }
  modelHist2d->SetTitle("");

  // Make 2D plot of data
  // Plot ONLY one component of the data
  // auto dataHist1d = std::unique_ptr<TH1>(fullDataSet.createHistogram(
  //     ("dataHist2d_" + ComposeName(id, neutral, bachelor, daughters,
  //     charge))
  //         .c_str(),
  //     config.buMass(), RooFit::Binning(config.buMass().getBins()),
  //     RooFit::YVar(config.deltaMass(),
  //                  RooFit::Binning(config.deltaMass().getBins())),
  //     RooFit::Cut(("fitting==fitting::" +
  //                  ComposeFittingName(neutral, bachelor, daughters,
  //                  charge))
  //                     .c_str())));
  auto dataHist1d = fullDataSet.createHistogram(
      ("dataHist2d_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      config.buMass(), RooFit::Binning(config.buMass().getBins()),
      RooFit::YVar(config.deltaMass(),
                   RooFit::Binning(config.deltaMass().getBins())),
      RooFit::Cut(("fitting==fitting::" +
                   ComposeFittingName(neutral, bachelor, daughters, charge))
                      .c_str()));
  if (dataHist1d == nullptr) {
    throw std::runtime_error("\n1D hist of data returns nullptr\n");
  }
  auto dataHist2d =
      std::unique_ptr<TH2>(dynamic_cast<TH2F *>(dataHist1d /* .get() */));
  if (dataHist2d == nullptr) {
    throw std::runtime_error("\n2D hist of data returns nullptr\n");
  }
  dataHist2d->SetTitle("");

  modelHist2d->Scale(dataHist2d->Integral() / modelHist2d->Integral());

  TCanvas canvasModel(
      ("canvasModel_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", 1000, 800);
  modelHist2d->SetStats(0);
  modelHist2d->Draw("colz");
  modelHist2d->SetTitle(
      ("B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}#font[132]{[}" +
       EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}" +
       EnumToLabel(neutral) + "#font[132]{]}_{D^{*0}}" + EnumToLabel(bachelor) +
       "^{" + EnumToLabel(charge) + "}")
          .c_str());
  modelHist2d->Draw("colz");
  modelHist2d->GetZaxis()->SetRangeUser(-0.00001, modelHist2d->GetMaximum());
  canvasModel.Update();
  canvasModel.SaveAs((outputDir + "/" +
                      ComposeName(id, neutral, bachelor, daughters, charge) +
                      "_2dPDF.pdf")
                         .c_str());

  // 2D data plot
  TCanvas canvasData(
      ("canvasData_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", 1000, 800);
  dataHist2d->SetStats(0);
  dataHist2d->Draw("colz");
  dataHist2d->SetTitle(
      ("B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}#font[132]{[}" +
       EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}" +
       EnumToLabel(neutral) + "#font[132]{]}_{D^{*0}}" + EnumToLabel(bachelor) +
       "^{" + EnumToLabel(charge) + "}")
          .c_str());
  dataHist2d->Draw("colz");
  canvasData.Update();
  canvasData.SaveAs((outputDir + "/" +
                     ComposeName(id, neutral, bachelor, daughters, charge) +
                     "_2dData.pdf")
                        .c_str());

  gStyle->SetTitleOffset(1.2, "Z");
  // Make a histogram with the Poisson stats in each data bin
  auto errHist2d = std::unique_ptr<TH2F>(new TH2F(
      ("errHist2d_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", config.buMass().getBins(), config.buMass().getMin(),
      config.buMass().getMax(), config.deltaMass().getBins(),
      config.deltaMass().getMin(), config.deltaMass().getMax()));
  for (int i = 0; i < config.buMass().getBins() * config.deltaMass().getBins();
       i++) {
    float n_bin = dataHist2d->GetBinContent(i);
    float err = sqrt(n_bin);
    errHist2d->SetBinContent(i, err);
  }

  // 2D residuals plot (data - PDF)/err
  TCanvas canvasRes(
      ("canvasRes_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", 1000, 800);
  canvasRes.cd();
  // auto resHist2d_temp = std::unique_ptr<TObject>(dataHist2d->Clone());
  auto resHist2d_temp = dataHist2d->Clone();
  if (resHist2d_temp == nullptr) {
    throw std::runtime_error("\nCould not clone dataHist2d.\n");
  }
  auto resHist2d =
      std::unique_ptr<TH2F>(dynamic_cast<TH2F *>(resHist2d_temp /* .get() */));
  if (resHist2d == nullptr) {
    throw std::runtime_error("\n2D hist of pdf returns nullptr\n");
  }
  resHist2d->Add(modelHist2d.get(), -1);
  resHist2d->Divide(errHist2d.get());
  canvasRes.cd();
  resHist2d->GetZaxis()->SetTitle("Residual");
  resHist2d->GetZaxis()->SetRangeUser(-6.0, 6.0);
  resHist2d->SetStats(0);
  resHist2d->Draw("colz");
  canvasRes.Update();
  canvasRes.SaveAs((outputDir + "/" +
                    ComposeName(id, neutral, bachelor, daughters, charge) +
                    "_2dResiduals.pdf")
                       .c_str());
}

std::pair<RooSimultaneous *, std::vector<PdfBase *> > MakeSimultaneousPdf(
    int const id, Configuration &config, Configuration::Categories &categories,
    std::vector<Neutral> const &neutralVec,
    std::vector<Daughters> const &daughtersVec, SplitByCharge splitbycharge) {
  RooSimultaneous *simPdf = new RooSimultaneous(
      ("simPdf_" + std::to_string(id)).c_str(),
      ("simPdf_" + std::to_string(id)).c_str(), categories.fitting);

  std::vector<PdfBase *> pdfs;

  // d is a reference to an element od the vector
  // Downside: don't have direct access to the index
  for (auto &d : daughtersVec) {
    switch (d) {
      case Daughters::kpi: {
        // emplace_back creates
        // the
        // object then moves it into the vector      // You only have to
        // pass
        // the arguments as if you were constructing the vector type The
        // operators required to do this are not supported by RooFit so we
        // have
        // to use a vector of pointers

        // switch (neutral) {
        // case Neutral::pi0:      for (auto &n : neutralVec) {

        for (auto &n : neutralVec) {
          switch (n) {
            case Neutral::gamma:

              if (splitbycharge == SplitByCharge::ktrue) {
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                       Daughters::kpi, Charge::plus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k,
                                       Daughters::kpi, Charge::plus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                       Daughters::kpi, Charge::minus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k,
                                       Daughters::kpi, Charge::minus>::Get(id));
              } else {
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                       Daughters::kpi, Charge::total>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k,
                                       Daughters::kpi, Charge::total>::Get(id));
              }

              break;

            case Neutral::pi0:

              if (splitbycharge == SplitByCharge::ktrue) {
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi,
                                       Daughters::kpi, Charge::plus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k,
                                       Daughters::kpi, Charge::plus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi,
                                       Daughters::kpi, Charge::minus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k,
                                       Daughters::kpi, Charge::minus>::Get(id));
              } else {
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi,
                                       Daughters::kpi, Charge::total>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k,
                                       Daughters::kpi, Charge::total>::Get(id));
              }

              break;
          }
        }
        break;
      }
      case Daughters::kk: {
        for (auto &n : neutralVec) {
          switch (n) {
            case Neutral::gamma:

              if (splitbycharge == SplitByCharge::ktrue) {
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                       Daughters::kk, Charge::plus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k,
                                       Daughters::kk, Charge::plus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                       Daughters::kk, Charge::minus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k,
                                       Daughters::kk, Charge::minus>::Get(id));
              } else {
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                       Daughters::kk, Charge::total>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k,
                                       Daughters::kk, Charge::total>::Get(id));
              }

              break;

            case Neutral::pi0:

              if (splitbycharge == SplitByCharge::ktrue) {
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi,
                                       Daughters::kk, Charge::plus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                                       Charge::plus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi,
                                       Daughters::kk, Charge::minus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                                       Charge::minus>::Get(id));
              } else {
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi,
                                       Daughters::kk, Charge::total>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                                       Charge::total>::Get(id));
              }

              break;
          }
        }
        break;
      }
      case Daughters::pipi: {
        for (auto &n : neutralVec) {
          switch (n) {
            case Neutral::gamma:

              if (splitbycharge == SplitByCharge::ktrue) {
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                       Daughters::pipi, Charge::plus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k,
                                       Daughters::pipi, Charge::plus>::Get(id));
                pdfs.emplace_back(
                    &Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                         Charge::minus>::Get(id));
                pdfs.emplace_back(
                    &Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                         Charge::minus>::Get(id));
              } else {
                pdfs.emplace_back(
                    &Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                         Charge::total>::Get(id));
                pdfs.emplace_back(
                    &Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                         Charge::total>::Get(id));
              }

              break;

            case Neutral::pi0:

              if (splitbycharge == SplitByCharge::ktrue) {
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi,
                                       Daughters::pipi, Charge::plus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k,
                                       Daughters::pipi, Charge::plus>::Get(id));
                pdfs.emplace_back(
                    &Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                         Charge::minus>::Get(id));
                pdfs.emplace_back(
                    &Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                         Charge::minus>::Get(id));
              } else {
                pdfs.emplace_back(
                    &Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                         Charge::total>::Get(id));
                pdfs.emplace_back(
                    &Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                         Charge::total>::Get(id));
              }

              break;
          }
        }
        break;
      }
      case Daughters::pik: {
        for (auto &n : neutralVec) {
          switch (n) {
            case Neutral::gamma:

              if (splitbycharge == SplitByCharge::ktrue) {
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                       Daughters::pik, Charge::plus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k,
                                       Daughters::pik, Charge::plus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                       Daughters::pik, Charge::minus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k,
                                       Daughters::pik, Charge::minus>::Get(id));
              } else {
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                       Daughters::pik, Charge::total>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k,
                                       Daughters::pik, Charge::total>::Get(id));
              }

              break;

            case Neutral::pi0:

              if (splitbycharge == SplitByCharge::ktrue) {
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi,
                                       Daughters::pik, Charge::plus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k,
                                       Daughters::pik, Charge::plus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi,
                                       Daughters::pik, Charge::minus>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k,
                                       Daughters::pik, Charge::minus>::Get(id));
              } else {
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi,
                                       Daughters::pik, Charge::total>::Get(id));
                pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k,
                                       Daughters::pik, Charge::total>::Get(id));
              }

              break;
          }
        }
        break;
      }
    }
  }

  for (auto &p : pdfs) {
    p->AddToSimultaneousPdf(*simPdf);
  }

  auto p = std::make_pair(simPdf, pdfs);
  return p;
}

void ShiftN_Dst0h(std::vector<Daughters> daughtersVec,
                  std::vector<Neutral> neutralVec, int id) {
  for (auto &d : daughtersVec) {
    switch (d) {
      case Daughters::kpi: {
        for (auto &n : neutralVec) {
          switch (n) {
            case Neutral::gamma: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::kpi>
                  &nbdVars_gamma_pi_kpi =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                   Daughters::kpi>::Get(id);
              auto N_Dst0h_RooRealVar =
                  dynamic_cast<RooRealVar *>(&nbdVars_gamma_pi_kpi.N_Dst0h());
              N_Dst0h_RooRealVar->setVal(N_Dst0h_RooRealVar->getVal() * 0.9);
              break;
            }
            case Neutral::pi0: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::kpi> &nbdVars_pi0_pi_kpi =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::kpi>::Get(id);
              auto N_Dst0h_RooRealVar =
                  dynamic_cast<RooRealVar *>(&nbdVars_pi0_pi_kpi.N_Dst0h());
              N_Dst0h_RooRealVar->setVal(N_Dst0h_RooRealVar->getVal() * 0.9);
              break;
            }
          }
        }
        break;
      }
      case Daughters::kk: {
        for (auto &n : neutralVec) {
          switch (n) {
            case Neutral::gamma: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::kk> &nbdVars_gamma_pi_kk =
                  NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                               Daughters::kk>::Get(id);
              auto N_Dst0h_RooRealVar =
                  dynamic_cast<RooRealVar *>(&nbdVars_gamma_pi_kk.N_Dst0h());
              N_Dst0h_RooRealVar->setVal(N_Dst0h_RooRealVar->getVal() * 0.9);
              break;
            }
            case Neutral::pi0: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::kk> &nbdVars_pi0_pi_kk =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::kk>::Get(id);
              auto N_Dst0h_RooRealVar =
                  dynamic_cast<RooRealVar *>(&nbdVars_pi0_pi_kk.N_Dst0h());
              N_Dst0h_RooRealVar->setVal(N_Dst0h_RooRealVar->getVal() * 0.9);
              break;
            }
          }
        }
        break;
      }
      case Daughters::pipi: {
        for (auto &n : neutralVec) {
          switch (n) {
            case Neutral::gamma: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::pipi>
                  &nbdVars_gamma_pi_pipi =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                   Daughters::pipi>::Get(id);
              auto N_Dst0h_RooRealVar =
                  dynamic_cast<RooRealVar *>(&nbdVars_gamma_pi_pipi.N_Dst0h());
              N_Dst0h_RooRealVar->setVal(N_Dst0h_RooRealVar->getVal() * 0.9);
              break;
            }
            case Neutral::pi0: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::pipi>
                  &nbdVars_pi0_pi_pipi =
                      NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                                   Daughters::pipi>::Get(id);
              auto N_Dst0h_RooRealVar =
                  dynamic_cast<RooRealVar *>(&nbdVars_pi0_pi_pipi.N_Dst0h());
              N_Dst0h_RooRealVar->setVal(N_Dst0h_RooRealVar->getVal() * 0.9);
              break;
            }
          }
        }
        break;
      }
      case Daughters::pik: {
        for (auto &n : neutralVec) {
          switch (n) {
            case Neutral::gamma: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::pik>
                  &nbdVars_gamma_pi_pik =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                   Daughters::pik>::Get(id);
              auto N_Dst0h_RooRealVar =
                  dynamic_cast<RooRealVar *>(&nbdVars_gamma_pi_pik.N_Dst0h());
              N_Dst0h_RooRealVar->setVal(N_Dst0h_RooRealVar->getVal() * 0.9);
              break;
            }
            case Neutral::pi0: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::pik> &nbdVars_pi0_pi_pik =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::pik>::Get(id);
              auto N_Dst0h_RooRealVar =
                  dynamic_cast<RooRealVar *>(&nbdVars_pi0_pi_pik.N_Dst0h());
              N_Dst0h_RooRealVar->setVal(N_Dst0h_RooRealVar->getVal() * 0.9);
              break;
            }
          }
        }
        break;
      }
    }
  }
}

void RunSingleToy(Configuration &config, Configuration::Categories &categories,
                  std::vector<Neutral> const &neutralVec,
                  std::vector<Daughters> const &daughtersVec,
                  SplitByCharge splitbycharge, std::string const &outputDir) {
  RooRandom::randomGenerator()->SetSeed(15);
  TRandom3 random(0);
  int id = 0;
  auto p = MakeSimultaneousPdf(id, config, categories, neutralVec, daughtersVec,
                               splitbycharge);
  auto simPdf = std::unique_ptr<RooSimultaneous>(p.first);
  std::vector<PdfBase *> pdfs = p.second;

  double nEvtsPerToy = simPdf->expectedEvents(categories.fitting);

  auto toyDataSet = std::unique_ptr<RooDataSet>(simPdf->generate(
      RooArgSet(config.buMass(), config.deltaMass(), categories.fitting),
      nEvtsPerToy));

  auto toyDataHist = std::unique_ptr<RooDataHist>(
      toyDataSet->binnedClone("toyDataHist", "toyDataHist"));

  auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

  // ShiftN_Dst0h(daughtersVec, neutralVec, id);

  auto simPdfToFit = std::unique_ptr<RooSimultaneous>(new RooSimultaneous(
      ("simPdfFit_" + std::to_string(id)).c_str(),
      ("simPdfFit_" + std::to_string(id)).c_str(), categories.fitting));

  simPdfToFit = std::unique_ptr<RooSimultaneous>(
      dynamic_cast<RooSimultaneous *>(simPdf->Clone()));

  auto simPdfToFitFit = std::unique_ptr<RooSimultaneous>(new RooSimultaneous(
      "simPdfToFitFit", "simPdfToFitFit", categories.fitting));

  simPdfToFitFit = std::unique_ptr<RooSimultaneous>(
      dynamic_cast<RooSimultaneous *>(simPdfToFit->Clone()));

  auto result = std::unique_ptr<RooFitResult>(simPdfToFitFit->fitTo(
      *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(), RooFit::Strategy(2),
      RooFit::Minimizer("Minuit2"), RooFit::Offset(true)));

  // Loop over daughters again to plot correct PDFs
  for (auto &p : pdfs) {
    Plotting1D(id, *p, config, categories, *toyAbsData, *simPdf, *result.get(),
               outputDir);
    Plotting2D(id, *p, config, *toyAbsData, *simPdf, outputDir);
  }

  result->Print("v");
  std::cout << "Printed result.\n";

  TCanvas correlationCanvas("correlationCanvas", "correlationCanvas", 1000,
                            1000);
  std::cout << "Created canvas.\n";
  correlationCanvas.cd();
  std::cout << "Extracting correlation histogram from result...\n";
  result->correlationHist()->Draw("colz");
  std::cout << "Extracted correlation histogram from result.\n";
  correlationCanvas.Update();
  std::cout << "Updated canvas.\n";
  correlationCanvas.SaveAs((outputDir + "/CorrelationMatrix.pdf").c_str());
  std::cout << "Save to pdf file.\n";
}

void SaveResultInTree(
    int const nToys,
    std::vector<std::shared_ptr<RooFitResult> > const &resultVec,
    std::string const &varNamePlusID, double varPrediction,
    std::string const &outputDir, double randomTag) {
  std::string varName = varNamePlusID.substr(0, varNamePlusID.size() - 2);

  TFile treeFile((outputDir + "/Tree_" + varName + "_" +
                  std::to_string(randomTag) + ".root")
                     .c_str(),
                 "recreate");
  TTree tree((varName + "_tree").c_str(), (varName + "_tree").c_str());

  // save variable value, error, and fit quality variables
  double varVal, varErr, EDM;
  int covQual, fitStatus;

  tree.Branch(varName.c_str(), &varVal, (varName + "/D").c_str());
  tree.Branch((varName + "_Err").c_str(), &varErr,
              (varName + "_Err/D").c_str());
  tree.Branch((varName + "_Prediction").c_str(), &varPrediction,
              (varName + "_Prediction/D").c_str());
  tree.Branch("EDM", &EDM, "EDM/D");
  tree.Branch("covQual", &covQual, "covQual/I");
  tree.Branch("fitStatus", &fitStatus, "fitStatus/I");

  for (int id = 0; id < nToys; ++id) {
    RooAbsArg *varAbsArg =
        const_cast<RooAbsArg *>(resultVec[id]->floatParsFinal().find(
            (varName + "_" + std::to_string(id)).c_str()));

    RooRealVar *var = dynamic_cast<RooRealVar *>(varAbsArg);
    if (var == nullptr) {
      std::stringstream output;
      output << "No value found in variable " << varName;
      throw std::runtime_error(output.str());
    }

    varVal = var->getVal();
    varErr = var->getError();
    EDM = resultVec[id]->edm();
    fitStatus = resultVec[id]->status();
    covQual = resultVec[id]->covQual();

    tree.Fill();
    if (EDM > 0.2) {
      std::cout << "\n\nEDM VALUE > 0.2\n\n";
      resultVec[id]->Print("v");
    }
  }
  treeFile.cd();
  tree.Write("", TObject::kOverwrite);
  treeFile.Write();
  treeFile.Close();

  std::cout << "Result saved in file " << outputDir << "/Tree_" << varName
            << "_" << std::to_string(randomTag) << ".root\n";
}

void RunManyToys(Configuration &config, Configuration::Categories &categories,
                 std::vector<Neutral> const &neutralVec,
                 std::vector<Daughters> const &daughtersVec,
                 SplitByCharge splitbycharge,
                 std::string const &outputDir /* , int nToys */) {
  // Extract names and predictions of all the variables we want to obtain
  // pulls for
  int id = 0;
  GlobalVars &globalVars = GlobalVars::Get(id);
  std::vector<std::string> varNames;
  std::vector<double> varPredictions;
  varNames.emplace_back(globalVars.ratioDst0KDst0pi().GetName());
  varPredictions.emplace_back(globalVars.ratioDst0KDst0pi().getVal());

  for (auto &n : neutralVec) {
    for (auto &d : daughtersVec) {
      switch (n) {
        case Neutral::pi0: {
          NeutralVars<Neutral::pi0> &nVars_pi0 =
              NeutralVars<Neutral::pi0>::Get(id);
          varNames.emplace_back(
              nVars_pi0.a0MeanBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varPredictions.emplace_back(
              nVars_pi0.a0MeanBu_Bu2Dst0h_Dst02D0pi0().getVal());
          varNames.emplace_back(
              nVars_pi0.a1MeanBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varPredictions.emplace_back(
              nVars_pi0.a1MeanBu_Bu2Dst0h_Dst02D0pi0().getVal());
          varNames.emplace_back(
              nVars_pi0.a2MeanBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varPredictions.emplace_back(
              nVars_pi0.a2MeanBu_Bu2Dst0h_Dst02D0pi0().getVal());
          // varNames.emplace_back(nVars_pi0.thresholdDelta_Comb().GetName());
          // varPredictions.emplace_back(nVars_pi0.thresholdDelta_Comb().getVal());
          varNames.emplace_back(nVars_pi0.cDelta_Comb().GetName());
          varPredictions.emplace_back(nVars_pi0.cDelta_Comb().getVal());
          varNames.emplace_back(nVars_pi0.aDelta_Comb().GetName());
          varPredictions.emplace_back(nVars_pi0.aDelta_Comb().getVal());
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi> &nbVars_pi_pi0 =
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(id);
          varNames.emplace_back(
              nbVars_pi_pi0.a0SigmaBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varPredictions.emplace_back(
              nbVars_pi_pi0.a0SigmaBu_Bu2Dst0h_Dst02D0pi0().getVal());
          varNames.emplace_back(
              nbVars_pi_pi0.a1SigmaBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varPredictions.emplace_back(
              nbVars_pi_pi0.a1SigmaBu_Bu2Dst0h_Dst02D0pi0().getVal());
          varNames.emplace_back(
              nbVars_pi_pi0.a2SigmaBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varPredictions.emplace_back(
              nbVars_pi_pi0.a2SigmaBu_Bu2Dst0h_Dst02D0pi0().getVal());
          switch (d) {
            case Daughters::kpi: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::kpi> &nbdVars_pi0_pi_kpi =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::kpi>::Get(id);
              varNames.emplace_back(nbdVars_pi0_pi_kpi.asym().GetName());
              varPredictions.emplace_back(nbdVars_pi0_pi_kpi.asym().getVal());
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                           Daughters::kpi> &nbdVars_pi0_k_kpi =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                               Daughters::kpi>::Get(id);
              varNames.emplace_back(nbdVars_pi0_k_kpi.asym().GetName());
              varPredictions.emplace_back(nbdVars_pi0_k_kpi.asym().getVal());
              break;
            }
            case Daughters::kk: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::kk> &nbdVars_pi0_pi_kk =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::kk>::Get(id);
              varNames.emplace_back(nbdVars_pi0_pi_kk.asym().GetName());
              varPredictions.emplace_back(nbdVars_pi0_pi_kk.asym().getVal());
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                           Daughters::kk> &nbdVars_pi0_k_kk =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                               Daughters::kk>::Get(id);
              varNames.emplace_back(nbdVars_pi0_k_kk.asym().GetName());
              varPredictions.emplace_back(nbdVars_pi0_k_kk.asym().getVal());
              break;
            }
            case Daughters::pipi: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::pipi>
                  &nbdVars_pi0_pi_pipi =
                      NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                                   Daughters::pipi>::Get(id);
              varNames.emplace_back(nbdVars_pi0_pi_pipi.asym().GetName());
              varPredictions.emplace_back(nbdVars_pi0_pi_pipi.asym().getVal());
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                           Daughters::pipi>
                  &nbdVars_pi0_k_pipi =
                      NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                                   Daughters::pipi>::Get(id);
              varNames.emplace_back(nbdVars_pi0_k_pipi.asym().GetName());
              varPredictions.emplace_back(nbdVars_pi0_k_pipi.asym().getVal());
              break;
            }
            case Daughters::pik: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::pik> &nbdVars_pi0_pi_pik =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::pik>::Get(id);
              varNames.emplace_back(nbdVars_pi0_pi_pik.asym().GetName());
              varPredictions.emplace_back(nbdVars_pi0_pi_pik.asym().getVal());
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                           Daughters::pik> &nbdVars_pi0_k_pik =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                               Daughters::pik>::Get(id);
              varNames.emplace_back(nbdVars_pi0_k_pik.asym().GetName());
              varPredictions.emplace_back(nbdVars_pi0_k_pik.asym().getVal());
              break;
            }
          }
          break;
        }
        case Neutral::gamma: {
          NeutralVars<Neutral::gamma> &nVars_gamma =
              NeutralVars<Neutral::gamma>::Get(id);
          varNames.emplace_back(
              nVars_gamma.a0MeanBu_Bu2Dst0h_Dst02D0gamma().GetName());
          varPredictions.emplace_back(
              nVars_gamma.a0MeanBu_Bu2Dst0h_Dst02D0gamma().getVal());
          varNames.emplace_back(
              nVars_gamma.a1MeanBu_Bu2Dst0h_Dst02D0gamma().GetName());
          varPredictions.emplace_back(
              nVars_gamma.a1MeanBu_Bu2Dst0h_Dst02D0gamma().getVal());
          varNames.emplace_back(
              nVars_gamma.a2MeanBu_Bu2Dst0h_Dst02D0gamma().GetName());
          varPredictions.emplace_back(
              nVars_gamma.a2MeanBu_Bu2Dst0h_Dst02D0gamma().getVal());
          varNames.emplace_back(
              nVars_gamma.a0MeanBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varPredictions.emplace_back(
              nVars_gamma.a0MeanBu_Bu2Dst0h_Dst02D0pi0().getVal());
          varNames.emplace_back(
              nVars_gamma.a1MeanBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varPredictions.emplace_back(
              nVars_gamma.a1MeanBu_Bu2Dst0h_Dst02D0pi0().getVal());
          varNames.emplace_back(
              nVars_gamma.a2MeanBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varPredictions.emplace_back(
              nVars_gamma.a2MeanBu_Bu2Dst0h_Dst02D0pi0().getVal());
          // varNames.emplace_back(nVars_gamma.thresholdDelta_Comb().GetName());
          // varPredictions.emplace_back(nVars_gamma.thresholdDelta_Comb().getVal());
          varNames.emplace_back(nVars_gamma.cDelta_Comb().GetName());
          varPredictions.emplace_back(nVars_gamma.cDelta_Comb().getVal());
          varNames.emplace_back(nVars_gamma.aDelta_Comb().GetName());
          varPredictions.emplace_back(nVars_gamma.aDelta_Comb().getVal());
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi> &nbVars_pi_gamma =
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(id);
          varNames.emplace_back(
              nbVars_pi_gamma.a0SigmaBu_Bu2Dst0h_Dst02D0gamma().GetName());
          varPredictions.emplace_back(
              nbVars_pi_gamma.a0SigmaBu_Bu2Dst0h_Dst02D0gamma().getVal());
          varNames.emplace_back(
              nbVars_pi_gamma.a1SigmaBu_Bu2Dst0h_Dst02D0gamma().GetName());
          varPredictions.emplace_back(
              nbVars_pi_gamma.a1SigmaBu_Bu2Dst0h_Dst02D0gamma().getVal());
          varNames.emplace_back(
              nbVars_pi_gamma.a2SigmaBu_Bu2Dst0h_Dst02D0gamma().GetName());
          varPredictions.emplace_back(
              nbVars_pi_gamma.a2SigmaBu_Bu2Dst0h_Dst02D0gamma().getVal());
          varNames.emplace_back(
              nbVars_pi_gamma.a0SigmaBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varPredictions.emplace_back(
              nbVars_pi_gamma.a0SigmaBu_Bu2Dst0h_Dst02D0pi0().getVal());
          varNames.emplace_back(
              nbVars_pi_gamma.a1SigmaBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varPredictions.emplace_back(
              nbVars_pi_gamma.a1SigmaBu_Bu2Dst0h_Dst02D0pi0().getVal());
          varNames.emplace_back(
              nbVars_pi_gamma.a2SigmaBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varPredictions.emplace_back(
              nbVars_pi_gamma.a2SigmaBu_Bu2Dst0h_Dst02D0pi0().getVal());
          switch (d) {
            case Daughters::kpi: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::kpi>
                  &nbdVars_gamma_pi_kpi =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                   Daughters::kpi>::Get(id);
              varNames.emplace_back(nbdVars_gamma_pi_kpi.asym().GetName());
              varPredictions.emplace_back(nbdVars_gamma_pi_kpi.asym().getVal());
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                           Daughters::kpi>
                  &nbdVars_gamma_k_kpi =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                                   Daughters::kpi>::Get(id);
              varNames.emplace_back(nbdVars_gamma_k_kpi.asym().GetName());
              varPredictions.emplace_back(nbdVars_gamma_k_kpi.asym().getVal());
              break;
            }
            case Daughters::kk: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::kk> &nbdVars_gamma_pi_kk =
                  NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                               Daughters::kk>::Get(id);
              varNames.emplace_back(nbdVars_gamma_pi_kk.asym().GetName());
              varPredictions.emplace_back(nbdVars_gamma_pi_kk.asym().getVal());
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                           Daughters::kk> &nbdVars_gamma_k_kk =
                  NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                               Daughters::kk>::Get(id);
              varNames.emplace_back(nbdVars_gamma_k_kk.asym().GetName());
              varPredictions.emplace_back(nbdVars_gamma_k_kk.asym().getVal());
              break;
            }
            case Daughters::pipi: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::pipi>
                  &nbdVars_gamma_pi_pipi =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                   Daughters::pipi>::Get(id);
              varNames.emplace_back(nbdVars_gamma_pi_pipi.asym().GetName());
              varPredictions.emplace_back(
                  nbdVars_gamma_pi_pipi.asym().getVal());
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                           Daughters::pipi>
                  &nbdVars_gamma_k_pipi =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                                   Daughters::pipi>::Get(id);
              varNames.emplace_back(nbdVars_gamma_k_pipi.asym().GetName());
              varPredictions.emplace_back(nbdVars_gamma_k_pipi.asym().getVal());
              break;
            }
            case Daughters::pik: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::pik>
                  &nbdVars_gamma_pi_pik =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                   Daughters::pik>::Get(id);
              varNames.emplace_back(nbdVars_gamma_pi_pik.asym().GetName());
              varPredictions.emplace_back(nbdVars_gamma_pi_pik.asym().getVal());
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                           Daughters::pik>
                  &nbdVars_gamma_k_pik =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                                   Daughters::pik>::Get(id);
              varNames.emplace_back(nbdVars_gamma_k_pik.asym().GetName());
              varPredictions.emplace_back(nbdVars_gamma_k_pik.asym().getVal());
              break;
            }
          }
          break;
        }
      }
    }
  }
  // Setting the random seed to 0 is a special case which generates a
  // different seed every time you run. Setting the seed to an integer
  // generates toys in a replicable way, in case you need to debug
  // something.
  RooRandom::randomGenerator()->SetSeed(0);
  TRandom3 random(0);
  double randomTag = random.Rndm();
  std::vector<std::shared_ptr<RooFitResult> > resultVec;
  int nToys = 5;

  for (int id = 0; id < nToys; ++id) {
    std::cout << "\n\n -------------------------- Running toy #" << id
              << " -------------------------- \n\n";
    auto p = MakeSimultaneousPdf(id, config, categories, neutralVec,
                                 daughtersVec, splitbycharge);
    auto simPdf = std::unique_ptr<RooSimultaneous>(p.first);

    double nEvtsPerToy = simPdf->expectedEvents(categories.fitting);
    auto toyDataSet = std::unique_ptr<RooDataSet>(simPdf->generate(
        RooArgSet(config.buMass(), config.deltaMass(), categories.fitting),
        nEvtsPerToy));
    toyDataSet->SetName(("toyDataSet_" + std::to_string(id)).c_str());
    auto toyDataHist = std::unique_ptr<RooDataHist>(
        toyDataSet->binnedClone(("toyDataHist_" + std::to_string(id)).c_str(),
                                ("toyDataHist" + std::to_string(id)).c_str()));
    auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

    // ShiftN_Dst0h(daughtersVec, neutralVec, id);

    auto simPdfToFit = std::unique_ptr<RooSimultaneous>(new RooSimultaneous(
        ("simPdfFit_" + std::to_string(id)).c_str(),
        ("simPdfFit_" + std::to_string(id)).c_str(), categories.fitting));

    simPdfToFit = std::unique_ptr<RooSimultaneous>(
        dynamic_cast<RooSimultaneous *>(simPdf->Clone()));

    auto result = std::shared_ptr<RooFitResult>(
        simPdfToFit->fitTo(*toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
                           RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                           RooFit::Offset(true)));
    // auto result = std::unique_ptr<RooFitResult>(simPdfToFit->fitTo(
    //     *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save()));
    resultVec.emplace_back(result);
    // save names and predictions of all variables we want to calculate
    // pulls for
    result->Print("v");
  }

  for (int n = 0; n < varNames.size(); ++n) {
    SaveResultInTree(nToys, resultVec, varNames[n], varPredictions[n],
                     outputDir, randomTag);
  }
}

// ExtractEnumList() allows user to parse multiple options separated by
// commas.
// Takes full options string as input and outputs a vector containing each
// specified option as an element

template <typename Enum>
std::vector<Enum> ExtractEnumList(std::string const &s, char delim = ',') {
  std::stringstream ss(s);
  std::vector<Enum> values;
  std::string substring;

  while (std::getline(ss, substring, delim)) {
    values.emplace_back(StringToEnum<Enum>(substring));
  }

  return values;
}

// Check file exists
bool fexists(std::string const &filename) {
  std::ifstream infile(filename.c_str());
  return infile.is_open();
}

int main(int argc, char **argv) {
  std::string inputDir, outputDir;
  std::vector<Year> yearVec;
  std::vector<Polarity> polarityVec;
  std::vector<Bachelor> bachelorVec;
  std::vector<Neutral> neutralVec;
  std::vector<Daughters> daughtersVec;
  std::vector<Charge> chargeVec;
  // Still want to load both charges:plus and minus, we just fit with
  // them differently
  chargeVec.emplace_back(Charge::plus);
  chargeVec.emplace_back(Charge::minus);

  SplitByCharge splitbycharge;
  Toys toys;

  // By letting the ParseArguments object go out of scope it will print a
  // warning if the user specified any unknown options.
  {  // calls destructor when object goes out of scope: Will tell you if
    // anything
    // was not used that was given as a command line argument before
    // continuing
    ParseArguments args(argc, argv);  // object instantiated

    // std::string yearArg("2011,2012,2015,2016");
    std::string yearArg("2011,2012,2015");
    std::string polarityArg("up,down");
    std::string bachelorArg("pi,k");
    std::string neutralArg("gamma,pi0");
    std::string daughtersArg("kpi,kk,pipi,pik");
    std::string chargeArg("true");
    std::string toysArg("none");

    // We always want to simultaneously fir the pi AND k bachelor modes
    // together
    bachelorVec = ExtractEnumList<Bachelor>(bachelorArg);

    if (args("help")) {
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "Type ./Fitting -inputDir=<RooDataSets directory name> \n"
                << "\n";
      std::cout << "-outputDir=<output directory> \n"
                << "\n";
      std::cout << "Followed by the possible options:\n";
      std::cout << "\n";
      std::cout << "    -year=<choice {2011,2012,2015,2016} default: "
                << yearArg << ">\n";
      std::cout << "    -polarity=<choice {up,down} default: " << polarityArg
                << ">\n";
      // std::cout << "    -bachelor choice {k,pi} default: " << bachelorArg
      // <<
      // "\n";
      std::cout << "    -neutral=<choice {pi0,gamma} default: " << neutralArg
                << ">\n";
      std::cout << "    -daughters=<choice {kpi,kk,pipi,pik} default: "
                << daughtersArg << ">\n";
      std::cout << "    -split=<choice {kTrue/kFalse} default: " << chargeArg
                << ">\n";
      std::cout << "    -toys=<choice {single, many, none} default: none>"
                << "\n";
      std::cout << "To specify multiple options, separate them by commas.\n";
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "\n";

      return 1;
    } else {
      if (!args("toys", toysArg)) {
        std::cout << "Using default value -polarity=[" << toysArg << "].\n";
      } else if (toysArg == "single") {
        toys = Toys::single;
      } else if (toysArg == "many") {
        toys = Toys::many;
      } else if (toysArg == "none") {
        toys = Toys::none;
      } else {
        std::cerr << "Please specify correct toy option: "
                     "-toys=[single,many,none] (optional)\n";
        return 1;
      }

      if (!args("inputDir", inputDir) && toys == Toys::none) {
        std::cerr << "Data directory must be specified (-inputDir=<path>).\n";
        return 1;
      }
      if (!args("outputDir", outputDir)) {
        std::cout << "Specify output directory (-outputDir=<path>).\n";
        return 1;
      }
      // Year
      // args matches "year" to string given in command line and assigns
      // option
      // parsed to year
      if (!args("year", yearArg)) {
        std::cout << "Using default value -year=[" << yearArg << "].\n";
      }
      try {
        yearVec = ExtractEnumList<Year>(yearArg);
      } catch (std::invalid_argument) {
        std::cerr << "year assignment failed, please specify: "
                     "-year=[2011,2012,2015,2016].\n";
        return 1;
      }

      // Polarity
      if (!args("polarity", polarityArg)) {
        std::cout << "Using default value -polarity=[" << polarityArg << "].\n";
      }
      try {
        polarityVec = ExtractEnumList<Polarity>(polarityArg);
      } catch (std::invalid_argument) {
        std::cerr << "Polarity assignment failed, please specify: "
                     "-polarity=[up,down].\n";
        return 1;
      }

      // Neutral
      if (!args("neutral", neutralArg)) {
        std::cerr << "Using default value -neutral=[" << neutralArg << "]\n";
      }
      try {
        neutralVec = ExtractEnumList<Neutral>(neutralArg);
      } catch (std::invalid_argument) {
        std::cerr << "neutral assignment failed, please specify: "
                     "-neutral=[pi0,gamma].\n";
        return 1;
      }

      if (!args("daughters", daughtersArg)) {
        std::cout << "Using default value -daughters=[" << daughtersArg
                  << "].\n";
      }
      try {
        daughtersVec = ExtractEnumList<Daughters>(daughtersArg);
      } catch (std::invalid_argument) {
        std::cerr << "daughters assignment failed, please specify: "
                     "-daughters=[kpi,kk,pipi,pik].\n";
        return 1;
      }

      if (!args("split", chargeArg)) {
        std::cout << "Using default value -split=[" << chargeArg << "].\n";
        splitbycharge = SplitByCharge::ktrue;
      }
      if (chargeArg == "kTrue") {
        splitbycharge = SplitByCharge::ktrue;
      } else if (chargeArg == "kFalse") {
        splitbycharge = SplitByCharge::kfalse;
      } else {
        std::cerr << "charge assignment failed, please specify split by "
                     "charge: -split=[kTrue/kFalse]";
        return 1;
      }
    }
  }

  Configuration &config = Configuration::Get();
  Configuration::Categories &categories = Configuration::Get().categories();

  if (toys == Toys::none) {
    RooDataSet fullDataSet("dataset", "dataset", config.fullArgSet());

    // Loop over all options in order to extract correct roodatasets
    for (unsigned int yCounter = 0; yCounter < yearVec.size(); yCounter++) {
      for (unsigned int pCounter = 0; pCounter < polarityVec.size();
           pCounter++) {
        for (unsigned int bCounter = 0; bCounter < bachelorVec.size();
             bCounter++) {
          for (unsigned int dCounter = 0; dCounter < daughtersVec.size();
               dCounter++) {
            for (unsigned int cCounter = 0; cCounter < chargeVec.size();
                 cCounter++) {
              for (unsigned int nCounter = 0; nCounter < neutralVec.size();
                   nCounter++) {
                std::string dsFile =
                    inputDir + "/" +
                    ComposeFilename(yearVec[yCounter], polarityVec[pCounter],
                                    bachelorVec[bCounter], neutralVec[nCounter],
                                    daughtersVec[dCounter],
                                    chargeVec[cCounter]) +
                    ".root";
                std::cout << "Extracting RooDataSet from file ... " << dsFile
                          << "\n";

                if (!fexists(dsFile)) {
                  std::cerr << dsFile << " does not exist.\n";
                  return 1;
                } else {
                  std::cout << dsFile << " exists.\n";
                  TFile in(dsFile.c_str(), "READ");
                  RooDataSet *inputDataSet;
                  gDirectory->GetObject("inputDataSet", inputDataSet);
                  if (inputDataSet == nullptr) {
                    throw std::runtime_error("Data set does not exist.");
                  } else {
                    std::cout << "inputDataSet extracted... \n";
                    fullDataSet.append(*inputDataSet);
                    std::cout << "Appended to full data set...\n";
                  }
                }
              }
            }
          }
        }
      }
    }

    int id = 0;

    auto fullDataHist = std::unique_ptr<RooDataHist>(
        fullDataSet.binnedClone("fullDataHist", "fullDataHist"));
    auto fullAbsData = dynamic_cast<RooAbsData *>(fullDataHist.get());

    auto p = MakeSimultaneousPdf(id, config, categories, neutralVec,
                                 daughtersVec, splitbycharge);
    auto simPdf = std::unique_ptr<RooSimultaneous>(p.first);
    auto pdfs = p.second;

    auto result = std::unique_ptr<RooFitResult>(
        simPdf->fitTo(*fullAbsData, RooFit::Extended(kTRUE), RooFit::Save()));

    // Loop over daughters again to plot correct PDFs
    for (auto &p : pdfs) {
      Plotting1D(id, *p, config, categories, fullDataSet, *simPdf,
                 *result.get(), outputDir);
      Plotting2D(id, *p, config, fullDataSet, *simPdf, outputDir);
    }

    result->Print("v");
    std::cout << "Printed result.\n";
    TCanvas correlationCanvas("correlationCanvas", "correlationCanvas", 1000,
                              1000);
    std::cout << "Created canvas.\n";
    correlationCanvas.cd();
    std::cout << "Extracting correlation histogram from result...\n";
    result->correlationHist()->Draw("colz");
    std::cout << "Extracted correlation histogram from result.\n";
    correlationCanvas.Update();
    std::cout << "Updated canvas.\n";
    correlationCanvas.SaveAs((outputDir + "/CorrelationMatrix.pdf").c_str());
    std::cout << "Save to pdf file.\n";

  } else {
    if (toys == Toys::single) {
      RunSingleToy(config, categories, neutralVec, daughtersVec, splitbycharge,
                   outputDir);
    } else if (toys == Toys::many) {
      RunManyToys(config, categories, neutralVec, daughtersVec, splitbycharge,
                  outputDir /* , nToys */);
    }
  }

  return 0;
}
