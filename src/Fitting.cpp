#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooHist.h"
#include "RooMCStudy.h"
#include "RooNumIntConfig.h"
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

// #include <chrono>
// #include <thread>
  // std::chrono::seconds dura( 5);
  // std::this_thread::sleep_for( dura );
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

// Function to set the style for all THists
void SetStyle() {
  gStyle->SetTitleFont(132, "XYZ");
  gStyle->SetLabelFont(132, "XYZ");
  gStyle->SetStatFont(132);
  gStyle->SetStatFontSize(0.04);
  gStyle->SetTitleSize(0.06, "Z");
  gStyle->SetTitleSize(0.03, "XY");
  gStyle->SetLabelSize(0.024, "XY");
  gStyle->SetLegendFont(132);
  gStyle->SetLegendTextSize(0.025);
  gStyle->SetTitleOffset(0.9, "X");
  gStyle->SetTitleOffset(1.1, "Y");
  gStyle->SetTitleOffset(0.9, "Z");
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.09);
  gStyle->SetPadLeftMargin(0.1);
}

// Function to plot 1D projections - written so that it can be used for both bu
// and delta mass
void PlotComponent(Variable variable, RooRealVar &var, PdfBase &pdf,
                   RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                   Configuration::Categories &categories, TLegend &legend,
                   TLegend &lumiLegend, std::string const &outputDir,
                   bool fitBool, Configuration &config) {
  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();
  int id = 0;

  // Integration trick to speed up plotting projections. Only works in pi0 mode.
  if (neutral==Neutral::pi0)  {
    int x_int = int(log(2 * var.getBins()) / log(2));
    RooAbsReal::defaultIntegratorConfig()
        ->getConfigSection("RooIntegrator1D")
        .setRealValue("fixSteps", x_int);
        }

  // Stops ROOT print INFO messages
  gErrorIgnoreLevel = kWarning;

  std::unique_ptr<RooPlot> frame(var.frame(RooFit::Title(
      ("B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}#font[132]{[}" +
       EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}" +
       EnumToLabel(neutral) + "#font[132]{]}_{D^{*0}}" + EnumToLabel(bachelor) +
       "^{" + EnumToLabel(charge) + "}")
          .c_str())));
  
  if (neutral == Neutral::pi0) {
    config.deltaMass().setRange("selected", 160, 210);
  } else {
    config.deltaMass().setRange("selected", 180, 210);
  }
  
  fullDataSet.plotOn(
      frame.get(),
      // RooFit::CutRange("selected"),
      RooFit::Cut(("fitting==fitting::" +
                   ComposeFittingName(neutral, bachelor, daughters, charge))
                      .c_str()));

  // Everything to be plotted has to be declared outside of a loop, in the scope
  // of the canvas
  RooHist *pullHist = nullptr;
  std::unique_ptr<RooPlot> pullFrame(var.frame(RooFit::Title(" ")));

  // if (fitBool == true) {
    simPdf.plotOn(
        frame.get(),
        // RooFit::ProjectionRange("selected"),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::LineColor(kBlue));

    pullHist = frame->RooPlot::pullHist();

    // In 2D, we have to plot the 2D PDF on the frame
    simPdf.plotOn(
        frame.get(),
        // RooFit::ProjectionRange("selected"),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdf_Bu2Dst0h_Dst02D0pi0().GetName()),
        RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue),
        RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
    simPdf.plotOn(
        frame.get(),
        // RooFit::ProjectionRange("selected"),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdf_Bu2Dst0h_Dst02D0gamma().GetName()),
        RooFit::LineStyle(kDashed), RooFit::LineColor(kOrange),
        RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
    simPdf.plotOn(
        frame.get(),
        // RooFit::ProjectionRange("selected"),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdf_Bu2Dst0hst_Dst02D0gamma()),
        RooFit::LineStyle(kDashed), RooFit::LineColor(kMagenta),
        RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
    simPdf.plotOn(
        frame.get(),
        // RooFit::ProjectionRange("selected"),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdf_Bu2Dst0hst_Dst02D0pi0()),
        RooFit::LineStyle(kDashed), RooFit::LineColor(kOrange + 3),
        RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
    simPdf.plotOn(
        frame.get(),
        // RooFit::ProjectionRange("selected"),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdf_overRec()), RooFit::LineStyle(kDashed),
        RooFit::LineColor(kGreen), RooFit::Precision(1e-3),
        RooFit::NumCPU(8, 2));
    simPdf.plotOn(
        frame.get(),
        // RooFit::ProjectionRange("selected"),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdf_misRec().GetName()),
        RooFit::LineStyle(kDashed), RooFit::LineColor(kTeal),
        RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
    // }
    // if (neutral == Neutral::pi0) {
    //   simPdf.plotOn(
    //       frame.get(),
    //       RooFit::Slice(
    //           categories.fitting,
    //           ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
    //       RooFit::ProjWData(categories.fitting, fullDataSet),
    //       RooFit::Components(pdf.pdf_Comb()), RooFit::LineStyle(kDashed),
    //       RooFit::LineColor(kRed), RooFit::Precision(1e-3),
    //       RooFit::NumCPU(8, 2));
    // }

    if (variable == Variable::delta) {
      if (neutral == Neutral::gamma) {
        frame->SetXTitle("m[D*^{0}] - m[D^{0}] (MeV/c^{2})");
      } else {
        frame->SetXTitle(
            "m[D^{*0}] - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
      }
    } else {
      frame->SetXTitle(
          ("m[D*^{0}" + EnumToLabel(bachelor) + "] (MeV/c^{2})").c_str());
    }

    if (fitBool == true) {
      pullFrame->addPlotable(pullHist /* .get() */, "P");
      pullFrame->SetName(("pullFrame_" + EnumToString(variable) + "_" +
                          ComposeName(id, neutral, bachelor, daughters, charge))
                             .c_str());
      pullFrame->SetTitle("");
    }

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

  TLine zeroLine(var.getMin(), 0, var.getMax(), 0);
  zeroLine.SetLineColor(kRed);
  zeroLine.SetLineStyle(kDashed);

  if (fitBool == true) {
    // Zero line on error plot.
    // .get() gets the raw pointer from underneath the smart pointer
    // FIX THIS
    // TLegend legend = MakeLegend(id, canvas, pad1, pad2, pdf);

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
  }

  canvas.cd();
  pad1.cd();
  frame->Draw();
  lumiLegend.Draw("same");
  // if (fitBool == true) {
  legend.Draw("same");
  // }
  // dataHist->Draw("same");

  canvas.Update();
  canvas.SaveAs((outputDir + "/" +
                 ComposeName(id, neutral, bachelor, daughters, charge) + "_" +
                 EnumToString(variable) + "Mass.pdf")
                    .c_str());
}

// Plot projections
void Plotting1D(int const id, PdfBase &pdf, Configuration &config,
                Configuration::Categories &categories,
                RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                std::string const &outputDir, bool fitBool,
                std::string &labelString, RooFitResult *result) {
  SetStyle();

  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();

  TLegend legend(0.71, 0.53, 0.85, 0.8);
  // ------------- Draw Legends -------------- //
  auto Bu2Dst0h_Dst02D0pi0Hist = std::make_unique<TH1D>(
      ("Bu2Dst0h_Dst02D0pi0Hist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "Bu2Dst0h_Dst02D0pi0Hist", 1, 0, 1);
  Bu2Dst0h_Dst02D0pi0Hist->SetLineColor(kBlue);
  Bu2Dst0h_Dst02D0pi0Hist->SetLineStyle(kDashed);
  Bu2Dst0h_Dst02D0pi0Hist->SetLineWidth(2);

  auto Bu2Dst0h_Dst02D0gammaHist = std::make_unique<TH1D>(
      ("Bu2Dst0h_Dst02D0gammaHist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "Bu2Dst0h_Dst02D0gammaHist", 1, 0, 1);
  Bu2Dst0h_Dst02D0gammaHist->SetLineColor(kOrange);
  Bu2Dst0h_Dst02D0gammaHist->SetLineStyle(kDashed);
  Bu2Dst0h_Dst02D0gammaHist->SetLineWidth(2);

  auto overRecHist = std::make_unique<TH1D>(
      ("overRecHist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "overRecHist", 1, 0, 1);
  overRecHist->SetLineColor(kGreen);
  overRecHist->SetLineStyle(kDashed);
  overRecHist->SetLineWidth(2);

  auto Bu2Dst0hst_Dst02D0pi0Hist = std::make_unique<TH1D>(
      ("Bu2Dst0hst_Dst02D0pi0Hist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "Bu2Dst0hst_Dst02D0pi0Hist", 1, 0, 1);
  Bu2Dst0hst_Dst02D0pi0Hist->SetLineColor(kOrange + 3);
  Bu2Dst0hst_Dst02D0pi0Hist->SetLineStyle(kDashed);
  Bu2Dst0hst_Dst02D0pi0Hist->SetLineWidth(2);

  auto Bu2Dst0hst_Dst02D0gammaHist = std::make_unique<TH1D>(
      ("Bu2Dst0hst_Dst02D0gammaHist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "Bu2Dst0hst_Dst02D0gammaHist", 1, 0, 1);
  Bu2Dst0hst_Dst02D0gammaHist->SetLineColor(kMagenta);
  Bu2Dst0hst_Dst02D0gammaHist->SetLineStyle(kDashed);
  Bu2Dst0hst_Dst02D0gammaHist->SetLineWidth(2);

  auto misRecHist = std::make_unique<TH1D>(
      ("misRecHist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "misRecHist", 1, 0, 1);
  misRecHist->SetLineColor(kTeal);
  misRecHist->SetLineStyle(kDashed);
  misRecHist->SetLineWidth(2);

  auto combHist = std::make_unique<TH1D>(
      ("combHist" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "combHist", 1, 0, 1);
  combHist->SetLineColor(kRed);
  combHist->SetLineStyle(kDashed);
  combHist->SetLineWidth(2);

  auto blankHist = std::make_unique<TH1D>(
      ("blankHist" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "blankHist", 1, 0, 1);
  blankHist->SetLineColor(kWhite);
  blankHist->SetLineWidth(2);

  std::stringstream Bu2Dst0h_Dst02D0pi0Legend;
  std::stringstream Bu2Dst0h_Dst02D0gammaLegend;
  std::stringstream overRecLegend;
  std::stringstream Bu2Dst0hst_Dst02D0pi0Legend;
  std::stringstream Bu2Dst0hst_Dst02D0gammaLegend;
  std::stringstream misRecLegendBu;
  std::stringstream misRecLegendBd;
  std::stringstream combLegend;
  Bu2Dst0h_Dst02D0pi0Legend
      << "B^{" + EnumToLabel(charge) +
             "}#rightarrow#font[132]{[}#font[132]{[}" +
             EnumToLabel(daughters, charge) +
             "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{0}*}" +
             EnumToLabel(bachelor) + "^{" + EnumToLabel(charge) + "}";
  Bu2Dst0h_Dst02D0gammaLegend
      << "B^{" + EnumToLabel(charge) +
             "}#rightarrow#font[132]{[}#font[132]{[}" +
             EnumToLabel(daughters, charge) +
             "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{0}*}" +
             EnumToLabel(bachelor) + "^{" + EnumToLabel(charge) + "}";
  Bu2Dst0hst_Dst02D0gammaLegend
      << "B^{" + EnumToLabel(charge) +
             "}#rightarrow#font[132]{[}#font[132]{[}" +
             EnumToLabel(daughters, charge) +
             "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{0}*}" +
             HstLabel(bachelor) + "^{" + EnumToLabel(charge) + "}";
  overRecLegend << "B^{" + EnumToLabel(charge) +
                       "}#rightarrow#font[132]{[}#font[132]{[}" +
                       EnumToLabel(daughters, charge) +
                       "#font[132]{]}_{D^{0}}" + EnumToLabel(bachelor) + "^{" +
                       EnumToLabel(charge) + "}";
  misRecLegendBu << "B^{" + EnumToLabel(charge) +
                      "}#rightarrow#font[132]{[}#font[132]{[}" +
                      EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}" +
                      HstLabel(bachelor) + "^{" + EnumToLabel(charge) + "},";
  misRecLegendBd << "B^{0}#rightarrow#font[132]{[}#font[132]{[}" +
                      EnumToLabel(daughters, charge) +
                      "#font[132]{]}_{D^{0}}#pi^{#pm}#font[132]{]}_{D^{+}*}" +
                      EnumToLabel(bachelor) + "^{#mp}";
  Bu2Dst0hst_Dst02D0pi0Legend
      << "B^{" + EnumToLabel(charge) +
             "}#rightarrow#font[132]{[}#font[132]{[}" +
             EnumToLabel(daughters, charge) +
             "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{0}*}" +
             HstLabel(bachelor) + "^{" + EnumToLabel(charge) + "}";
  combLegend << "Combinatorial Bkg";
  // if (fitBool == true && labelString != "TOY") {
  //   Bu2Dst0h_Dst02D0gammaLegend << " ~ "
  //                               << pdf.yield_Bu2Dst0h_Dst02D0gamma().getVal();
  //   // << " pm "
  //   // << pdf.yield_Bu2Dst0h_Dst02D0gamma().getPropagatedError(*result)
  //   // << " events";
  //   Bu2Dst0h_Dst02D0pi0Legend
  //       << " ~ " << pdf.yield_Bu2Dst0h_Dst02D0pi0().getVal();
  //   // << " pm "
  //   // << pdf.yield_Bu2Dst0h_Dst02D0pi0().getPropagatedError(*result)
  //   // << " events";
  //   Bu2Dst0hst_Dst02D0gammaLegend
  //       << " ~ " << pdf.yield_Bu2Dst0hst_Dst02D0gamma().getVal();
  //   // << " pm "
  //   // << pdf.yield_Bu2Dst0hst_Dst02D0gamma().getPropagatedError(*result)
  //   // << " events";
  //   overRecLegend << " ~ " << pdf.yield_overRec().getVal();
  //   // << " pm "
  //   // << pdf.yield_overRec().getPropagatedError(*result)
  //   // << " events";
  //   misRecLegendBd << " ~ " << pdf.yield_misRec().getVal();
  //   // << " pm "
  //   // << pdf.yield_misRec().getPropagatedError(*result) << " events";
  //   Bu2Dst0hst_Dst02D0pi0Legend << " ~ "
  //                               << pdf.yield_Bu2Dst0hst_Dst02D0pi0().getVal();
  //   // << " pm "
  //   // << pdf.yield_Bu2Dst0hst_Dst02D0pi0().getPropagatedError(*result)
  //   // << " events";
  //   // if (neutral == Neutral::pi0) {
  //   //   combLegend << " ~ " << pdf.yield_Comb().getVal();
  //   //   // << " pm "
  //   //   // << pdf.yield_comb().getPropagatedError(*result) << " events";
  //   // }
  // }

  legend.SetLineColor(kWhite);
  legend.AddEntry(Bu2Dst0h_Dst02D0pi0Hist.get(),
                  Bu2Dst0h_Dst02D0pi0Legend.str().c_str(), "l");
  legend.AddEntry(Bu2Dst0h_Dst02D0gammaHist.get(),
                  Bu2Dst0h_Dst02D0gammaLegend.str().c_str(), "l");
  legend.AddEntry(overRecHist.get(), overRecLegend.str().c_str(), "l");
  legend.AddEntry(misRecHist.get(), misRecLegendBu.str().c_str(), "l");
  legend.AddEntry(blankHist.get(), misRecLegendBd.str().c_str(), "l");
  legend.AddEntry(Bu2Dst0hst_Dst02D0gammaHist.get(),
                  Bu2Dst0hst_Dst02D0gammaLegend.str().c_str(), "l");
  legend.AddEntry(Bu2Dst0hst_Dst02D0pi0Hist.get(),
                  Bu2Dst0hst_Dst02D0pi0Legend.str().c_str(), "l");
  // if (neutral == Neutral::pi0) {
  //   legend.AddEntry(combHist.get(), combLegend.str().c_str(), "l");
  // }

  TLegend lumiLegend(0.68, 0.80, 0.85, 0.87);
  lumiLegend.SetTextSize(0.03);
  lumiLegend.SetLineColor(kWhite);
  lumiLegend.AddEntry(blankHist.get(), labelString.c_str(), "l");
  // Blank entry to make space for integration symbol
  lumiLegend.AddEntry(blankHist.get(), " ", "l");

  if (labelString == "TOY") {
    lumiLegend.SetTextSize(0.07);
    legend.SetY1(0.55);
    legend.SetY2(0.7);
    lumiLegend.SetY1(0.7);
    lumiLegend.SetY2(0.8);
    if (neutral == Neutral::gamma) {
      legend.SetY2(0.75);
      lumiLegend.SetY1(0.75);
      // legend.SetY1(0.6);
      // legend.SetY2(0.87);
      // lumiLegend.SetX1(0.15);
      // lumiLegend.SetX2(0.25);
      // lumiLegend.SetY1(0.65);
      // lumiLegend.SetY2(0.8);
    }
  }
  // ---- PLOTTING FOR BU MASS COMPONENT ---- //
  PlotComponent(Variable::bu, config.buMass(), pdf, fullDataSet, simPdf,
                categories, legend, lumiLegend, outputDir, fitBool, config);
  // ---- PLOTTING FOR DELTA MASS COMPONENT ---- //
  PlotComponent(Variable::delta, config.deltaMass(), pdf, fullDataSet, simPdf,
                categories, legend, lumiLegend, outputDir, fitBool, config);
}

// Plot in 2D: data, PDF and residuals
void Plotting2D(int const id, PdfBase &pdf, Configuration &config,
                RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                std::string const &outputDir, bool fitBool) {
  gStyle->SetTitleSize(0.03, "XYZ");
  gStyle->SetLabelSize(0.025, "XYZ");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetTitleOffset(1.5, "Z");
  gStyle->SetPadRightMargin(0.15);

  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();

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

  // 2D data plot
  TCanvas canvasData(
      ("canvasData_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", 1000, 800);
  dataHist2d->SetStats(0);
  if (neutral == Neutral::pi0) {
    dataHist2d->GetYaxis()->SetTitle(
        "m[D^{*0} - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
  }
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
  if (fitBool == true) {
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
    modelHist2d->Scale(dataHist2d->Integral() / modelHist2d->Integral());

    TCanvas canvasModel(
        ("canvasModel_" + ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "", 1000, 800);
    modelHist2d->SetStats(0);
    if (neutral == Neutral::pi0) {
      modelHist2d->GetYaxis()->SetTitle(
          "m[D^{*0} - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
    }
    modelHist2d->SetTitle(("B^{" + EnumToLabel(charge) +
                           "}#rightarrow#font[132]{[}#font[132]{[}" +
                           EnumToLabel(daughters, charge) +
                           "#font[132]{]}_{D^{0}}" + EnumToLabel(neutral) +
                           "#font[132]{]}_{D^{*0}}" + EnumToLabel(bachelor) +
                           "^{" + EnumToLabel(charge) + "}")
                              .c_str());
    modelHist2d->Draw("colz");
    modelHist2d->GetZaxis()->SetRangeUser(-0.00001, modelHist2d->GetMaximum());
    canvasModel.Update();
    canvasModel.SaveAs((outputDir + "/" +
                        ComposeName(id, neutral, bachelor, daughters, charge) +
                        "_2dPDF.pdf")
                           .c_str());

    gStyle->SetTitleOffset(1.2, "Z");
    // Make a histogram with the Poisson stats in each data bin
    auto errHist2d = std::unique_ptr<TH2F>(new TH2F(
        ("errHist2d_" + ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "", config.buMass().getBins(), config.buMass().getMin(),
        config.buMass().getMax(), config.deltaMass().getBins(),
        config.deltaMass().getMin(), config.deltaMass().getMax()));
    for (int i = 0;
         i < config.buMass().getBins() * config.deltaMass().getBins(); i++) {
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
    auto resHist2d = std::unique_ptr<TH2F>(
        dynamic_cast<TH2F *>(resHist2d_temp /* .get() */));
    if (resHist2d == nullptr) {
      throw std::runtime_error("\n2D hist of pdf returns nullptr\n");
    }
    resHist2d->Add(modelHist2d.get(), -1);
    resHist2d->Divide(errHist2d.get());
    canvasRes.cd();
    if (neutral == Neutral::pi0) {
      resHist2d->GetYaxis()->SetTitle(
          "m[D^{*0} - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
    }
    resHist2d->GetZaxis()->SetTitle("Residual");
    resHist2d->GetZaxis()->SetRangeUser(-6.0, 6.0);
    resHist2d->SetStats(0);
    resHist2d->Draw("colz");
    canvasRes.Update();
    canvasRes.SaveAs((outputDir + "/" +
                      ComposeName(id, neutral, bachelor, daughters, charge) +
                      "_2dResiduals.pdf")
                         .c_str());

    // 1D residuals plot (sum over all 2D bins)
    TCanvas canvasRes1d(
        ("canvasRes1d_" + ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "", 1000, 800);
    canvasRes1d.cd();
    TH1F resHist1d(
        ("resHist1d_" + ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "", 130, -6, 6);
    for (int i = 0; i < config.buMass().getBins() * config.deltaMass().getBins(); i++) {
      float n_bin = resHist2d->GetBinContent(i);
      if (n_bin != 0) {
        resHist1d.Fill(n_bin);
      }
    }
    resHist1d.GetXaxis()->SetTitle("Residual");
    resHist1d.GetYaxis()->SetTitle("Entries");
    resHist1d.SetTitle("");
    resHist1d.SetStats(0);
    resHist1d.Draw();
    canvasRes1d.Update();
    canvasRes1d.SaveAs((outputDir + "/" +
                      ComposeName(id, neutral, bachelor, daughters, charge) +
                      "_1dResiduals.pdf")
                         .c_str());
    }
}

// Function that returns the simultaneous PDF, the class which collects all the
// individual components. It is that that we do all our fitting with
std::pair<RooSimultaneous *, std::vector<PdfBase *> > MakeSimultaneousPdf(
    int const id, Configuration &config, Configuration::Categories &categories,
    std::vector<Neutral> const &neutralVec,
    std::vector<Daughters> const &daughtersVec,
    std::vector<Charge> const &chargeVec) {
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

        for (auto &n : neutralVec) {
          switch (n) {
            case Neutral::gamma:
              for (auto &c : chargeVec) {
                switch (c) {
                  case Charge::plus:
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                             Charge::plus>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                             Charge::plus>::Get(id));
                    break;
                  case Charge::minus:
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                             Charge::minus>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                             Charge::minus>::Get(id));
                    break;
                  case Charge::total:
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                             Charge::total>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                             Charge::total>::Get(id));
                    break;
                }
              }
              break;

            case Neutral::pi0:
              for (auto &c : chargeVec) {
                switch (c) {
                  case Charge::plus:
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                             Charge::plus>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                             Charge::plus>::Get(id));
                    break;
                  case Charge::minus:
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                             Charge::minus>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                             Charge::minus>::Get(id));
                    break;
                  case Charge::total:
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                             Charge::total>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                             Charge::total>::Get(id));
                    break;
                }
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
              for (auto &c : chargeVec) {
                switch (c) {
                  case Charge::plus:
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                             Charge::plus>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                             Charge::plus>::Get(id));
                    break;
                  case Charge::minus:
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                             Charge::minus>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                             Charge::minus>::Get(id));
                    break;
                  case Charge::total:
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                             Charge::total>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                             Charge::total>::Get(id));
                    break;
                }
              }
              break;

            case Neutral::pi0:
              for (auto &c : chargeVec) {
                switch (c) {
                  case Charge::plus:
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                             Charge::plus>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                             Charge::plus>::Get(id));
                    break;
                  case Charge::minus:
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                             Charge::minus>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                             Charge::minus>::Get(id));
                    break;
                  case Charge::total:
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                             Charge::total>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                             Charge::total>::Get(id));
                    break;
                }
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
              for (auto &c : chargeVec) {
                switch (c) {
                  case Charge::plus:
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                             Charge::plus>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                             Charge::plus>::Get(id));
                    break;
                  case Charge::minus:
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                             Charge::minus>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                             Charge::minus>::Get(id));
                    break;
                  case Charge::total:
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                             Charge::total>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                             Charge::total>::Get(id));
                    break;
                }
              }
              break;

            case Neutral::pi0:
              for (auto &c : chargeVec) {
                switch (c) {
                  case Charge::plus:
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                             Charge::plus>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                             Charge::plus>::Get(id));
                    break;
                  case Charge::minus:
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                             Charge::minus>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                             Charge::minus>::Get(id));
                    break;
                  case Charge::total:
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                             Charge::total>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                             Charge::total>::Get(id));
                    break;
                }
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
              for (auto &c : chargeVec) {
                switch (c) {
                  case Charge::plus:
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                             Charge::plus>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                             Charge::plus>::Get(id));
                    break;
                  case Charge::minus:
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                             Charge::minus>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                             Charge::minus>::Get(id));
                    break;
                  case Charge::total:
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                             Charge::total>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                             Charge::total>::Get(id));
                    break;
                }
              }
              break;

            case Neutral::pi0:
              for (auto &c : chargeVec) {
                switch (c) {
                  case Charge::plus:
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                             Charge::plus>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                             Charge::plus>::Get(id));
                    break;
                  case Charge::minus:
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                             Charge::minus>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                             Charge::minus>::Get(id));
                    break;
                  case Charge::total:
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                             Charge::total>::Get(id));
                    pdfs.emplace_back(
                        &Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                             Charge::total>::Get(id));
                    break;
                }
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

// Sometimes need to shift the starting point of the yields in order to make the
// toy fit stable (so that the fit actually has to do some work)
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
              auto N_Bu2Dst0h_Dst02D0gamma_RooRealVar =
                  dynamic_cast<RooRealVar *>(
                      &nbdVars_gamma_pi_kpi.N_Bu2Dst0h_Dst02D0gamma());
              N_Bu2Dst0h_Dst02D0gamma_RooRealVar->setVal(
                  N_Bu2Dst0h_Dst02D0gamma_RooRealVar->getVal() * 0.9);
              break;
            }
            case Neutral::pi0: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::kpi> &nbdVars_pi0_pi_kpi =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::kpi>::Get(id);
              auto N_Bu2Dst0h_Dst02D0pi0_RooRealVar =
                  dynamic_cast<RooRealVar *>(
                      &nbdVars_pi0_pi_kpi.N_Bu2Dst0h_Dst02D0pi0());
              N_Bu2Dst0h_Dst02D0pi0_RooRealVar->setVal(
                  N_Bu2Dst0h_Dst02D0pi0_RooRealVar->getVal() * 0.9);
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
              auto N_Bu2Dst0h_Dst02D0gamma_RooRealVar =
                  dynamic_cast<RooRealVar *>(
                      &nbdVars_gamma_pi_kk.N_Bu2Dst0h_Dst02D0gamma());
              N_Bu2Dst0h_Dst02D0gamma_RooRealVar->setVal(
                  N_Bu2Dst0h_Dst02D0gamma_RooRealVar->getVal() * 0.9);
              break;
            }
            case Neutral::pi0: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::kk> &nbdVars_pi0_pi_kk =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::kk>::Get(id);
              auto N_Bu2Dst0h_Dst02D0pi0_RooRealVar =
                  dynamic_cast<RooRealVar *>(
                      &nbdVars_pi0_pi_kk.N_Bu2Dst0h_Dst02D0pi0());
              N_Bu2Dst0h_Dst02D0pi0_RooRealVar->setVal(
                  N_Bu2Dst0h_Dst02D0pi0_RooRealVar->getVal() * 0.9);
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
              auto N_Bu2Dst0h_Dst02D0gamma_RooRealVar =
                  dynamic_cast<RooRealVar *>(
                      &nbdVars_gamma_pi_pipi.N_Bu2Dst0h_Dst02D0gamma());
              N_Bu2Dst0h_Dst02D0gamma_RooRealVar->setVal(
                  N_Bu2Dst0h_Dst02D0gamma_RooRealVar->getVal() * 0.9);
              break;
            }
            case Neutral::pi0: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::pipi>
                  &nbdVars_pi0_pi_pipi =
                      NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                                   Daughters::pipi>::Get(id);
              auto N_Bu2Dst0h_Dst02D0pi0_RooRealVar =
                  dynamic_cast<RooRealVar *>(
                      &nbdVars_pi0_pi_pipi.N_Bu2Dst0h_Dst02D0pi0());
              N_Bu2Dst0h_Dst02D0pi0_RooRealVar->setVal(
                  N_Bu2Dst0h_Dst02D0pi0_RooRealVar->getVal() * 0.9);
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
              auto N_Bu2Dst0h_Dst02D0gamma_RooRealVar =
                  dynamic_cast<RooRealVar *>(
                      &nbdVars_gamma_pi_pik.N_Bu2Dst0h_Dst02D0gamma());
              N_Bu2Dst0h_Dst02D0gamma_RooRealVar->setVal(
                  N_Bu2Dst0h_Dst02D0gamma_RooRealVar->getVal() * 0.9);
              break;
            }
            case Neutral::pi0: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::pik> &nbdVars_pi0_pi_pik =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::pik>::Get(id);
              auto N_Bu2Dst0h_Dst02D0pi0_RooRealVar =
                  dynamic_cast<RooRealVar *>(
                      &nbdVars_pi0_pi_pik.N_Bu2Dst0h_Dst02D0pi0());
              N_Bu2Dst0h_Dst02D0pi0_RooRealVar->setVal(
                  N_Bu2Dst0h_Dst02D0pi0_RooRealVar->getVal() * 0.9);
              break;
            }
          }
        }
        break;
      }
    }
  }
}

// Run 1 toy and make 1D and 2D plots
void RunSingleToy(Configuration &config, Configuration::Categories &categories,
                  std::vector<Neutral> const &neutralVec,
                  std::vector<Daughters> const &daughtersVec,
                  std::vector<Charge> const &chargeVec,
                  std::string const &outputDir, bool fitBool) {
  RooRandom::randomGenerator()->SetSeed(30);
  TRandom3 random(0);
  int id = 0;
  auto p = MakeSimultaneousPdf(id, config, categories, neutralVec, daughtersVec,
                               chargeVec);
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

  std::unique_ptr<RooFitResult> result;

  if (fitBool == true) {
    result = std::unique_ptr<RooFitResult>(simPdfToFit->fitTo(
        *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
        RooFit::Strategy(2), RooFit::Minimizer("Minuit2"), RooFit::Offset(true),
        RooFit::NumCPU(8, 2)));
  }
  // Label plots to indicate Toy
  std::string lumiString = "TOY";
  // Loop over daughters again to plot correct PDFs
  for (auto &p : pdfs) {
    Plotting1D(id, *p, config, categories, *toyAbsData, *simPdf,
               outputDir, fitBool, lumiString, result.get());
    Plotting2D(id, *p, config, *toyAbsData, *simPdf, outputDir, fitBool);
  }
  if (fitBool == true) {
    result->Print("v");
    TCanvas corrCanvas("corrCanvas", "corrCanvas", 1200, 900);
    TH2* corrHist = result->correlationHist();
    corrHist->SetStats(0);
    corrHist->SetTitle(" ");
    corrCanvas.cd();
    gPad->SetLeftMargin(0.2);
    gPad->SetRightMargin(0.1);
    gPad->SetBottomMargin(0.15);
    gPad->SetTopMargin(0.05);
    corrHist->SetLabelSize(0.015, "XY");
    corrHist->SetLabelSize(0.02, "Z");
    corrHist->Draw("colz");
    corrCanvas.Update();
    corrCanvas.SaveAs((outputDir + "/CorrelationMatrix.pdf").c_str());
  }
}

// Save all info on variables: value, error; EDM, covariance matrix quality and
// status of fit for each result stored. One tree and one file created for each
// variable - should have entries equal to number of toys.
void SaveResultInTree(
    int const nToys,
    std::vector<std::shared_ptr<RooFitResult> > const &resultVec,
    std::string const &varNamePlusID, double varPrediction,
    std::string const &outputDir, double randomTag) {
  std::string varName = varNamePlusID.substr(0, varNamePlusID.size() - 2);

  // Add random tag to file name so that when we submit to the batch and run
  // toys in parallel, files are not overwritten
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

// Function we use to do the toy study - run many toys and extract pulls for
// each variable of interest
void RunManyToys(Configuration &config, Configuration::Categories &categories,
                 std::vector<Neutral> const &neutralVec,
                 std::vector<Daughters> const &daughtersVec,
                 std::vector<Charge> const &chargeVec,
                 std::string const &outputDir /* , int nToys */) {
  // Extract names and predictions of all the variables we want to obtain
  // pulls for
  int id = 0;
  GlobalVars &globalVars = GlobalVars::Get(id);
  std::vector<std::string> varNames;
  std::vector<double> varPredictions;

  // Extract the names of the variables and their starting values
  for (auto &n : neutralVec) {
    for (auto &d : daughtersVec) {
      switch (n) {
        case Neutral::pi0: {
          switch (d) {
            case Daughters::kpi: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::kpi> &nbdVars_pi0_pi_kpi =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::kpi>::Get(id);
              varNames.emplace_back(
                  nbdVars_pi0_pi_kpi.N_Bu2Dst0h_Dst02D0pi0().GetName());
              varPredictions.emplace_back(
                  nbdVars_pi0_pi_kpi.N_Bu2Dst0h_Dst02D0pi0().getVal());
              break;
            }
            case Daughters::kk: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::kk> &nbdVars_pi0_pi_kk =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::kk>::Get(id);
              varNames.emplace_back(
                  nbdVars_pi0_pi_kk.N_Bu2Dst0h_Dst02D0pi0().GetName());
              varPredictions.emplace_back(
                  nbdVars_pi0_pi_kk.N_Bu2Dst0h_Dst02D0pi0().getVal());
              break;
            }
            case Daughters::pipi: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::pipi>
                  &nbdVars_pi0_pi_pipi =
                      NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                                   Daughters::pipi>::Get(id);
              varNames.emplace_back(
                  nbdVars_pi0_pi_pipi.N_Bu2Dst0h_Dst02D0pi0().GetName());
              varPredictions.emplace_back(
                  nbdVars_pi0_pi_pipi.N_Bu2Dst0h_Dst02D0pi0().getVal());
              break;
            }
            case Daughters::pik: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::pik> &nbdVars_pi0_pi_pik =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::pik>::Get(id);
              varNames.emplace_back(
                  nbdVars_pi0_pi_pik.N_Bu2Dst0h_Dst02D0pi0().GetName());
              varPredictions.emplace_back(
                  nbdVars_pi0_pi_pik.N_Bu2Dst0h_Dst02D0pi0().getVal());
              break;
            }
          }
          break;
        }
        case Neutral::gamma: {
          switch (d) {
            case Daughters::kpi: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::kpi>
                  &nbdVars_gamma_pi_kpi =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                   Daughters::kpi>::Get(id);
              varNames.emplace_back(
                  nbdVars_gamma_pi_kpi.N_Bu2Dst0h_Dst02D0gamma().GetName());
              varPredictions.emplace_back(
                  nbdVars_gamma_pi_kpi.N_Bu2Dst0h_Dst02D0gamma().getVal());
              break;
            }
            case Daughters::kk: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::kk> &nbdVars_gamma_pi_kk =
                  NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                               Daughters::kk>::Get(id);
              varNames.emplace_back(
                  nbdVars_gamma_pi_kk.N_Bu2Dst0h_Dst02D0gamma().GetName());
              varPredictions.emplace_back(
                  nbdVars_gamma_pi_kk.N_Bu2Dst0h_Dst02D0gamma().getVal());
              break;
            }
            case Daughters::pipi: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::pipi>
                  &nbdVars_gamma_pi_pipi =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                   Daughters::pipi>::Get(id);
              varNames.emplace_back(
                  nbdVars_gamma_pi_pipi.N_Bu2Dst0h_Dst02D0gamma().GetName());
              varPredictions.emplace_back(
                  nbdVars_gamma_pi_pipi.N_Bu2Dst0h_Dst02D0gamma().getVal());
              break;
            }
            case Daughters::pik: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::pik>
                  &nbdVars_gamma_pi_pik =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                   Daughters::pik>::Get(id);
              varNames.emplace_back(
                  nbdVars_gamma_pi_pik.N_Bu2Dst0h_Dst02D0gamma().GetName());
              varPredictions.emplace_back(
                  nbdVars_gamma_pi_pik.N_Bu2Dst0h_Dst02D0gamma().getVal());
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

  // loop over number of toys we want to run. Make simPDF, generate dataset, fit
  // back and save the result in order to extract the variable info
  for (int id = 0; id < nToys; ++id) {
    std::cout << "\n\n -------------------------- Running toy #" << id+1
              << " -------------------------- \n\n";
    auto p = MakeSimultaneousPdf(id, config, categories, neutralVec,
                                 daughtersVec, chargeVec);
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
                           RooFit::Offset(true), RooFit::NumCPU(8, 2)));
    // auto result = std::unique_ptr<RooFitResult>(simPdfToFit->fitTo(
    //     *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save()));
    resultVec.emplace_back(result);
    // save names and predictions of all variables we want to calculate
    // pulls for
    result->Print("v");
  }

  // loop over all the variables we are interested in
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

  Toys toys;
  bool fitBool = true;

  // By letting the ParseArguments object go out of scope it will print a
  // warning if the user specified any unknown options.
  {  // calls destructor when object goes out of scope: Will tell you if
    // anything
    // was not used that was given as a command line argument before
    // continuing
    ParseArguments args(argc, argv);  // object instantiated

    std::string yearArg("2011,2012,2015,2016,2017");
    std::string polarityArg("up,down");
    std::string bachelorArg("pi,k");
    std::string neutralArg("gamma,pi0");
    std::string daughtersArg("kpi,kk,pipi,pik");
    std::string chargeArg("total");
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
      std::cout << "    -charge=<choice {plus/minus/total} default: " << chargeArg
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
        std::cout << "Using default value -toys=[" << toysArg << "].\n";
        toys = Toys::none;
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

      if (!args("charge", chargeArg)) {
        std::cout << "Using default value -charge=[" << chargeArg << "].\n";
      }
      try {
        chargeVec = ExtractEnumList<Charge>(chargeArg);
        std::cout << "Using value -charge=[" << chargeArg << "].\n";
      } catch (std::invalid_argument) {
        std::cerr << "charge assignment failed, please specify: "
                     "-charge=[plus,minus] or -charge=[total].\n";
        return 1;
      }
    }
  }

  Configuration &config = Configuration::Get();
  Configuration::Categories &categories = Configuration::Get().categories();

  // Raise lower mass boundary in delta mass for pi0 plots 
  if (neutralVec.size() == 1 && neutralVec[0] == Neutral::pi0) {
    config.deltaMass().setMin(134);
  }

  if (toys == Toys::none) {
    std::map<std::string, RooDataSet *> mapCategoryDataset;

    // Add up lumi in order to convert into string to go on plots
    double lumi = 0;
    double lumiErr = 0;

    // Loop over all options in
    // order to extract correct roodatasets.
    for (auto &y : yearVec) {
      if (y == Year::y2011) {
        lumi += 0.98;
        lumiErr += 0.02;
      } else if (y == Year::y2012) {
        lumi += 1.99;
        lumiErr += 0.02;
      } else if (y == Year::y2015) {
        lumi += 0.28;
        lumiErr += 0.01;
      } else if (y == Year::y2016) {
        lumi += 1.65;
      } else if (y == Year::y2017) {
        lumi += 1.7;
      }
      for (auto &p : polarityVec) {
        for (auto &b : bachelorVec) {
          for (auto &n : neutralVec) {
            for (auto &d : daughtersVec) {
              for (auto &c : chargeVec) {
                std::string dsFile = inputDir + "/" +
                                     ComposeFilename(y, p, b, n, d, c) +
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
                    inputDataSet->Print();
                    RooDataSet *reducedInputDataSet_1 = nullptr;
                    if (n == Neutral::pi0) {
                      reducedInputDataSet_1 =
                          dynamic_cast<RooDataSet *>(inputDataSet->reduce(
                              "BDT2>0.05&&Pi0_M<185&&Pi0_M>110"));
                    } else {
                      reducedInputDataSet_1 =
                          dynamic_cast<RooDataSet *>(inputDataSet->reduce(
                              "BDT2>0.05"));
                    }
                    RooDataSet *reducedInputDataSet = nullptr;
                    if (b == Bachelor::pi) {
                      reducedInputDataSet =
                          dynamic_cast<RooDataSet *>(reducedInputDataSet_1->reduce(
                              "bach_PIDK<12&&Bu_M_DTF>5050&&Bu_M_DTF<5800&&"
                              "Delta_M>50&&Delta_M<210&&BDT1>0.05&&pi_"
                              "D_PIDK<-2&&K_D_PIDK>2"));
                    } else {
                      reducedInputDataSet =
                          dynamic_cast<RooDataSet *>(reducedInputDataSet_1->reduce(
                              "bach_PIDK>12&&Bu_M_DTF>5050&&Bu_M_DTF<5800&&"
                              "Delta_M>50&&Delta_M<210&&BDT1>0.05&&pi_"
                              "D_PIDK<-2&&K_D_PIDK>2"));
                    }
                    if (reducedInputDataSet == nullptr) {
                      throw std::runtime_error(
                          "Could not reduce input dataset.");
                    }
                    reducedInputDataSet->Print();
                    // Need to append each year, polarity to dataset at each key
                    // in map, as key labelled by n, b, d, c and must be unique.
                    if (mapCategoryDataset.find(ComposeFittingName(
                            n, b, d, c)) == mapCategoryDataset.end()) {
                      mapCategoryDataset.insert(std::make_pair(
                          ComposeFittingName(n, b, d, c), reducedInputDataSet));
                      std::cout << "Created key-value pair for category " +
                                       ComposeFittingName(n, b, d, c) +
                                       " and "
                                       "dataset " +
                                       EnumToString(y) + "_" + EnumToString(p) +
                                       ".\n";
                    } else {
                      mapCategoryDataset[ComposeFittingName(n, b, d, c)]
                          ->append(*reducedInputDataSet);
                      std::cout << "Appended dataset " + EnumToString(y) +
                                       "_" + EnumToString(p) +
                                       "to category " +
                                       ComposeFittingName(n, b, d, c) + ".\n";
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    int id = 0;

    RooDataSet fullDataSet("fullDataSet", "fullDataSet", config.fittingArgSet(),
                           RooFit::Index(categories.fitting),
                           RooFit::Import(mapCategoryDataset));

    std::cout << "\n\n\n";
    fullDataSet.Print();
    std::cout << "\n\n\n";
    auto fullDataHist = std::unique_ptr<RooDataHist>(
        fullDataSet.binnedClone("fullDataHist", "fullDataHist"));
    if (fullDataHist == nullptr) {
      throw std::runtime_error("Could not extact binned dataset.");
    }
    auto fullAbsData = dynamic_cast<RooAbsData *>(fullDataHist.get());
    if (fullAbsData == nullptr) {
      throw std::runtime_error("Could not cast to RooAbsData.");
    }

    auto p = MakeSimultaneousPdf(id, config, categories, neutralVec,
                                 daughtersVec, chargeVec);
    auto simPdf = std::unique_ptr<RooSimultaneous>(p.first);
    auto pdfs = p.second;

    std::unique_ptr<RooFitResult> result;

    if (fitBool == true) {
      result = std::unique_ptr<RooFitResult>(
          simPdf->fitTo(*fullAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
                        RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                        RooFit::Offset(true), RooFit::NumCPU(8, 2)));
    }

    // String for lumi label on 1D projection plots
    std::ostringstream lumiStream, lumiErrStream;
    lumiStream << std::setprecision(2) << lumi;
    lumiErrStream << std::setprecision(2) << lumiErr;
    std::string lumiString = "#int L dt = " + lumiStream.str() + " #pm " +
                             lumiErrStream.str() + " fb^{-1}";
    // Loop over daughters again to plot correct PDFs
    for (auto &p : pdfs) {
      Plotting1D(id, *p, config, categories, fullDataSet, *simPdf,
                 outputDir, fitBool, lumiString, result.get());
      Plotting2D(id, *p, config, fullDataSet, *simPdf, outputDir, fitBool);
    }

    if (fitBool == true) {
      result->Print("v");
      TCanvas corrCanvas("corrCanvas", "corrCanvas", 1700, 900);
      TH2 *corrHist = result->correlationHist();
      corrHist->SetStats(0);
      corrHist->SetTitle(" ");
      corrCanvas.cd();
      gStyle->SetLabelSize(0.001, "XY");
      gStyle->SetLabelSize(0.015, "Z");
      gPad->SetLeftMargin(0.3);
      gPad->SetRightMargin(0.2);
      gPad->SetBottomMargin(0.21);
      gPad->SetTopMargin(0.05);
      corrHist->Draw("colz");
      corrCanvas.Update();
      corrCanvas.SaveAs((outputDir + "/CorrelationMatrix.pdf").c_str());
    }

  } else {
    if (toys == Toys::single) {
      RunSingleToy(config, categories, neutralVec, daughtersVec, chargeVec,
                   outputDir, fitBool);
    } else if (toys == Toys::many) {
      RunManyToys(config, categories, neutralVec, daughtersVec, chargeVec,
                  outputDir /* , nToys */);
    }
  }

  return 0;
}
