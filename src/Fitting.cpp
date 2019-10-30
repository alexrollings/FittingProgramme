#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooHist.h"
#include "RooHistPdf.h"
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

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralVars.h"
#include "ParseArguments.h"
#include "Pdf.h"

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
  gStyle->SetLegendTextSize(0.03);
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
void PlotComponent(Mass mass, RooRealVar &var, PdfBase &pdf,
                   RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                   Configuration::Categories &categories, TLegend &legend,
                   TLegend &lumiLegend, std::string const &outputDir,
                   Configuration &config,
                   std::map<std::string, Color_t> colorMap) {
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

  fullDataSet.plotOn(frame.get(),
                     RooFit::Cut(("fitting==fitting::" +
                                  ComposeFittingName(mass, neutral, bachelor,
                                                     daughters, charge))
                                     .c_str()));
  if (config.noFit() == false) {
    simPdf.plotOn(frame.get(),
                  RooFit::Slice(categories.fitting,
                                ComposeFittingName(mass, neutral, bachelor,
                                                   daughters, charge)
                                    .c_str()),
                  RooFit::ProjWData(categories.fitting, fullDataSet),
                  RooFit::LineColor(kBlue));
  }

  // Everything to be plotted has to be declared outside of a loop, in the scope
  // of the canvas
  RooHist *pullHist = nullptr;
  std::unique_ptr<RooPlot> pullFrame(var.frame(RooFit::Title(" ")));

  pullHist = frame->RooPlot::pullHist();

  if (config.noFit() == false) {
    if (mass == Mass::buDelta) {
      std::cout << "Plotting " << pdf.addPdfBu().GetName() << "\n";
      if (bachelor == Bachelor::pi) {
        if (neutral == Neutral::gamma) {
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  categories.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(categories.fitting, fullDataSet),
              RooFit::Components(pdf.pdfBu_Bu2Dst0h_D0gamma().GetName()),
              RooFit::LineStyle(kDashed),
              RooFit::LineColor(colorMap["Bu2Dst0pi_D0gamma"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  categories.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(categories.fitting, fullDataSet),
              RooFit::Components(pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName()),
              RooFit::LineStyle(kDashed),
              RooFit::LineColor(colorMap["Bu2Dst0K_D0gamma"]),
              RooFit::LineStyle(kDashed), RooFit::Precision(1e-3),
              RooFit::NumCPU(8, 2));
        }
        simPdf.plotOn(frame.get(),
                      RooFit::Slice(categories.fitting,
                                    ComposeFittingName(mass, neutral, bachelor,
                                                       daughters, charge)
                                        .c_str()),
                      RooFit::ProjWData(categories.fitting, fullDataSet),
                      RooFit::Components(pdf.pdfBu_Bu2Dst0h_D0pi0().GetName()),
                      RooFit::LineStyle(kDashed),
                      RooFit::LineColor(colorMap["Bu2Dst0pi_D0pi0"]),
                      RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName()),
            RooFit::LineStyle(kDashed),
            RooFit::LineColor(colorMap["Bu2Dst0K_D0pi0"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfBu_MisRec().GetName()),
            RooFit::LineStyle(kDashed), RooFit::LineColor(colorMap["MisRecPi"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfBu_Bu2D0h().GetName()),
            RooFit::LineStyle(kDashed), RooFit::LineColor(colorMap["Bu2D0pi"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(frame.get(),
                      RooFit::Slice(categories.fitting,
                                    ComposeFittingName(mass, neutral, bachelor,
                                                       daughters, charge)
                                        .c_str()),
                      RooFit::ProjWData(categories.fitting, fullDataSet),
                      RooFit::Components(pdf.pdfBu_PartRec().GetName()),
                      RooFit::LineStyle(kDashed),
                      RooFit::LineColor(colorMap["PartRecRho"]),
                      RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
      } else {
        if (neutral == Neutral::gamma) {
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  categories.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(categories.fitting, fullDataSet),
              RooFit::Components(pdf.pdfBu_Bu2Dst0h_D0gamma().GetName()),
              RooFit::LineStyle(kDashed),
              RooFit::LineColor(colorMap["Bu2Dst0K_D0gamma"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  categories.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(categories.fitting, fullDataSet),
              RooFit::Components(pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName()),
              RooFit::LineStyle(kDashed),
              RooFit::LineColor(colorMap["Bu2Dst0pi_D0gamma"]),
              RooFit::LineStyle(kDashed), RooFit::Precision(1e-3),
              RooFit::NumCPU(8, 2));
        }
        simPdf.plotOn(frame.get(),
                      RooFit::Slice(categories.fitting,
                                    ComposeFittingName(mass, neutral, bachelor,
                                                       daughters, charge)
                                        .c_str()),
                      RooFit::ProjWData(categories.fitting, fullDataSet),
                      RooFit::Components(pdf.pdfBu_Bu2Dst0h_D0pi0().GetName()),
                      RooFit::LineStyle(kDashed),
                      RooFit::LineColor(colorMap["Bu2Dst0K_D0pi0"]),
                      RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName()),
            RooFit::LineStyle(kDashed),
            RooFit::LineColor(colorMap["Bu2Dst0pi_D0pi0"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfBu_MisRec().GetName()),
            RooFit::LineStyle(kDashed), RooFit::LineColor(colorMap["MisRecK"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfBu_misId_MisRec().GetName()),
            RooFit::LineStyle(kDashed), RooFit::LineColor(colorMap["MisRecPi"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfBu_Bu2D0h().GetName()),
            RooFit::LineStyle(kDashed), RooFit::LineColor(colorMap["Bu2D0K"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfBu_misId_Bu2D0h().GetName()),
            RooFit::LineStyle(kDashed), RooFit::LineColor(colorMap["Bu2D0pi"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(frame.get(),
                      RooFit::Slice(categories.fitting,
                                    ComposeFittingName(mass, neutral, bachelor,
                                                       daughters, charge)
                                        .c_str()),
                      RooFit::ProjWData(categories.fitting, fullDataSet),
                      RooFit::Components(pdf.pdfBu_PartRec().GetName()),
                      RooFit::LineStyle(kDashed),
                      RooFit::LineColor(colorMap["PartRecKst"]),
                      RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(frame.get(),
                      RooFit::Slice(categories.fitting,
                                    ComposeFittingName(mass, neutral, bachelor,
                                                       daughters, charge)
                                        .c_str()),
                      RooFit::ProjWData(categories.fitting, fullDataSet),
                      RooFit::Components(pdf.pdfBu_misId_PartRec().GetName()),
                      RooFit::LineStyle(kDashed),
                      RooFit::LineColor(colorMap["PartRecRho"]),
                      RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
      }
    } else {
      std::cout << "Plotting " << pdf.addPdfDelta().GetName() << "\n";
      if (bachelor == Bachelor::pi) {
        if (neutral == Neutral::gamma) {
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  categories.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(categories.fitting, fullDataSet),
              RooFit::Components(pdf.pdfDelta_Bu2Dst0h_D0gamma().GetName()),
              RooFit::LineStyle(kDashed),
              RooFit::LineColor(colorMap["Bu2Dst0pi_D0gamma"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  categories.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(categories.fitting, fullDataSet),
              RooFit::Components(
                  pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName()),
              RooFit::LineStyle(kDashed),
              RooFit::LineColor(colorMap["Bu2Dst0K_D0gamma"]),
              RooFit::LineStyle(kDashed), RooFit::Precision(1e-3),
              RooFit::NumCPU(8, 2));
        }
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfDelta_Bu2Dst0h_D0pi0().GetName()),
            RooFit::LineStyle(kDashed),
            RooFit::LineColor(colorMap["Bu2Dst0pi_D0pi0"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName()),
            RooFit::LineStyle(kDashed),
            RooFit::LineColor(colorMap["Bu2Dst0K_D0pi0"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfDelta_MisRec().GetName()),
            RooFit::LineStyle(kDashed), RooFit::LineColor(colorMap["MisRecPi"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfDelta_Bu2D0h().GetName()),
            RooFit::LineStyle(kDashed), RooFit::LineColor(colorMap["Bu2D0pi"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(frame.get(),
                      RooFit::Slice(categories.fitting,
                                    ComposeFittingName(mass, neutral, bachelor,
                                                       daughters, charge)
                                        .c_str()),
                      RooFit::ProjWData(categories.fitting, fullDataSet),
                      RooFit::Components(pdf.pdfDelta_PartRec().GetName()),
                      RooFit::LineStyle(kDashed),
                      RooFit::LineColor(colorMap["PartRecRho"]),
                      RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
      } else {
        if (neutral == Neutral::gamma) {
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  categories.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(categories.fitting, fullDataSet),
              RooFit::Components(pdf.pdfDelta_Bu2Dst0h_D0gamma().GetName()),
              RooFit::LineStyle(kDashed),
              RooFit::LineColor(colorMap["Bu2Dst0K_D0gamma"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  categories.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(categories.fitting, fullDataSet),
              RooFit::Components(
                  pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName()),
              RooFit::LineStyle(kDashed),
              RooFit::LineColor(colorMap["Bu2Dst0pi_D0gamma"]),
              RooFit::LineStyle(kDashed), RooFit::Precision(1e-3),
              RooFit::NumCPU(8, 2));
        }
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfDelta_Bu2Dst0h_D0pi0().GetName()),
            RooFit::LineStyle(kDashed),
            RooFit::LineColor(colorMap["Bu2Dst0K_D0pi0"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName()),
            RooFit::LineStyle(kDashed),
            RooFit::LineColor(colorMap["Bu2Dst0pi_D0pi0"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfDelta_MisRec().GetName()),
            RooFit::LineStyle(kDashed), RooFit::LineColor(colorMap["MisRecK"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfDelta_misId_MisRec().GetName()),
            RooFit::LineStyle(kDashed), RooFit::LineColor(colorMap["MisRecPi"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfDelta_Bu2D0h().GetName()),
            RooFit::LineStyle(kDashed), RooFit::LineColor(colorMap["Bu2D0K"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfDelta_misId_Bu2D0h().GetName()),
            RooFit::LineStyle(kDashed), RooFit::LineColor(colorMap["Bu2D0pi"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(frame.get(),
                      RooFit::Slice(categories.fitting,
                                    ComposeFittingName(mass, neutral, bachelor,
                                                       daughters, charge)
                                        .c_str()),
                      RooFit::ProjWData(categories.fitting, fullDataSet),
                      RooFit::Components(pdf.pdfDelta_PartRec().GetName()),
                      RooFit::LineStyle(kDashed),
                      RooFit::LineColor(colorMap["PartRecKst"]),
                      RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                categories.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(categories.fitting, fullDataSet),
            RooFit::Components(pdf.pdfDelta_misId_PartRec().GetName()),
            RooFit::LineStyle(kDashed),
            RooFit::LineColor(colorMap["PartRecRho"]), RooFit::Precision(1e-3),
            RooFit::NumCPU(8, 2));
      }
    }
  }

  if (mass == Mass::delta) {
    if (neutral == Neutral::gamma) {
      frame->SetXTitle("m[D*^{0}] - m[D^{0}] (MeV/c^{2})");
    } else {
      frame->SetXTitle(
          "m[D^{*0}] - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
    }
  } else {
    frame->SetXTitle(("m[D*^{0}" + EnumToLabel(bachelor) +
                      "] - m[D^{*0}] + m[D^{*0}]_{PDG} (MeV/c^{2})")
                         .c_str());
  }

  if (config.noFit() == false) {
    pullFrame->addPlotable(pullHist /* .get() */, "P");
    pullFrame->SetName(("pullFrame_" + ComposeName(id, mass, neutral, bachelor,
                                                   daughters, charge))
                           .c_str());
    pullFrame->SetTitle("");
  }

  // --------------- plot onto canvas ---------------------

  TCanvas canvas(
      ("canvas_" + ComposeName(id, mass, neutral, bachelor, daughters, charge))
          .c_str(),
      "canvas", 1200, 1000);

  TPad pad1(
      ("pad1_" + ComposeName(id, mass, neutral, bachelor, daughters, charge))
          .c_str(),
      "pad1", 0.0, 0.14, 1.0, 1.0, kWhite);
  pad1.Draw();

  TPad pad2(
      ("pad2_" + ComposeName(id, mass, neutral, bachelor, daughters, charge))
          .c_str(),
      "pad2", 0.0, 0.05, 1.0, 0.15, kWhite);
  pad2.Draw();

  TLine zeroLine(var.getMin(), 0, var.getMax(), 0);
  zeroLine.SetLineColor(kRed);
  zeroLine.SetLineStyle(kDashed);

  if (config.noFit() == false) {
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
  // if (config.noFit() == false) {
  legend.Draw("same");
  // }
  // dataHist->Draw("same");

  canvas.Update();
  canvas.SaveAs((outputDir + "/plots/" +
                 ComposeName(id, mass, neutral, bachelor, daughters, charge) +
                 "_" + config.ReturnBoxString() + ".pdf")
                    .c_str());
}

// Plot projections
void Plotting1D(int const id, PdfBase &pdf, Configuration &config,
                Configuration::Categories &categories,
                RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                std::string const &outputDir, std::string &labelString,
                RooFitResult *result) {
  SetStyle();

  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();

  auto blankHist = std::make_unique<TH1D>(
      ("blankHist" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "blankHist", 1, 0, 1);
  blankHist->SetLineColor(kWhite);
  blankHist->SetLineWidth(2);

  TLegend lumiLegend(0.7, 0.75, 0.9, 0.8);
  lumiLegend.SetTextSize(0.03);
  lumiLegend.SetLineColor(kWhite);
  lumiLegend.AddEntry(blankHist.get(), labelString.c_str(), "l");
  // Blank entry to make space for integration symbol
  lumiLegend.AddEntry(blankHist.get(), " ", "l");
  if (labelString == "TOY") {
    lumiLegend.SetTextSize(0.07);
  }

  TLegend legend(0.7, 0.48, 0.9, 0.75);
  legend.SetLineColor(kWhite);

  if (neutral == Neutral::pi0) {
    if (bachelor == Bachelor::k) {
      legend.SetY1(0.375);
    }
    if (labelString == "TOY") {
      lumiLegend.SetX1(0.66);
    }
  }
  if (neutral == Neutral::gamma) {
    legend.SetX1(0.14);
    legend.SetX2(0.35);
    legend.SetY1(0.59);
    legend.SetY2(0.89);
    if (bachelor == Bachelor::k) {
      legend.SetY1(0.515);
    }
    if (labelString == "TOY") {
      lumiLegend.SetX1(0.83);
      lumiLegend.SetX2(0.9);
    } else {
      lumiLegend.SetX1(0.75);
      lumiLegend.SetX2(0.85);
      lumiLegend.SetY1(0.82);
      lumiLegend.SetY2(0.87);
    }
  }
  // ------------- Draw Legends -------------- //
  std::map<std::string, Color_t> colorMap;

  auto Bu2Dst0pi_D0gammaHist = std::make_unique<TH1D>(
      ("Bu2Dst0pi_D0gammaHist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "Bu2Dst0pi_D0gammaHist", 1, 0, 1);
  Bu2Dst0pi_D0gammaHist->SetLineColor(kGreen + 2);
  Bu2Dst0pi_D0gammaHist->SetLineStyle(kDashed);
  Bu2Dst0pi_D0gammaHist->SetLineWidth(2);
  colorMap["Bu2Dst0pi_D0gamma"] = Bu2Dst0pi_D0gammaHist->GetLineColor();

  auto Bu2Dst0K_D0gammaHist = std::make_unique<TH1D>(
      ("Bu2Dst0K_D0gammaHist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "Bu2Dst0K_D0gammaHist", 1, 0, 1);
  Bu2Dst0K_D0gammaHist->SetLineColor(kRed);
  Bu2Dst0K_D0gammaHist->SetLineStyle(kDashed);
  Bu2Dst0K_D0gammaHist->SetLineWidth(2);
  colorMap["Bu2Dst0K_D0gamma"] = Bu2Dst0K_D0gammaHist->GetLineColor();

  auto Bu2Dst0pi_D0pi0Hist = std::make_unique<TH1D>(
      ("Bu2Dst0pi_D0pi0Hist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "Bu2Dst0pi_D0pi0Hist", 1, 0, 1);
  Bu2Dst0pi_D0pi0Hist->SetLineColor(kBlue - 7);
  Bu2Dst0pi_D0pi0Hist->SetLineStyle(kDashed);
  Bu2Dst0pi_D0pi0Hist->SetLineWidth(2);
  colorMap["Bu2Dst0pi_D0pi0"] = Bu2Dst0pi_D0pi0Hist->GetLineColor();

  auto Bu2Dst0K_D0pi0Hist = std::make_unique<TH1D>(
      ("Bu2Dst0K_D0pi0Hist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "Bu2Dst0K_D0pi0Hist", 1, 0, 1);
  Bu2Dst0K_D0pi0Hist->SetLineColor(kViolet - 6);
  Bu2Dst0K_D0pi0Hist->SetLineStyle(kDashed);
  Bu2Dst0K_D0pi0Hist->SetLineWidth(2);
  colorMap["Bu2Dst0K_D0pi0"] = Bu2Dst0K_D0pi0Hist->GetLineColor();

  auto MisRecPiHist = std::make_unique<TH1D>(
      ("MisRecPiHist" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "MisRecPiHist", 1, 0, 1);
  MisRecPiHist->SetLineColor(kOrange);
  MisRecPiHist->SetLineStyle(kDashed);
  MisRecPiHist->SetLineWidth(2);
  colorMap["MisRecPi"] = MisRecPiHist->GetLineColor();

  auto MisRecKHist = std::make_unique<TH1D>(
      ("MisRecKHist" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "MisRecKHist", 1, 0, 1);
  MisRecKHist->SetLineColor(kAzure - 1);
  MisRecKHist->SetLineStyle(kDashed);
  MisRecKHist->SetLineWidth(2);
  colorMap["MisRecK"] = MisRecKHist->GetLineColor();

  auto Bu2D0piHist = std::make_unique<TH1D>(
      ("Bu2D0piHist" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "Bu2D0piHist", 1, 0, 1);
  Bu2D0piHist->SetLineColor(kMagenta);
  Bu2D0piHist->SetLineStyle(kDashed);
  Bu2D0piHist->SetLineWidth(2);
  colorMap["Bu2D0pi"] = Bu2D0piHist->GetLineColor();

  auto Bu2D0KHist = std::make_unique<TH1D>(
      ("Bu2D0KHist" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "Bu2D0KHist", 1, 0, 1);
  Bu2D0KHist->SetLineColor(kCyan + 1);
  Bu2D0KHist->SetLineStyle(kDashed);
  Bu2D0KHist->SetLineWidth(2);
  colorMap["Bu2D0K"] = Bu2D0KHist->GetLineColor();

  auto PartRecRhoHist = std::make_unique<TH1D>(
      ("PartRecRhoHist" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "PartRecRhoHist", 1, 0, 1);
  PartRecRhoHist->SetLineColor(kBlue + 3);
  PartRecRhoHist->SetLineStyle(kDashed);
  PartRecRhoHist->SetLineWidth(2);
  colorMap["PartRecRho"] = PartRecRhoHist->GetLineColor();

  auto PartRecKstHist = std::make_unique<TH1D>(
      ("PartRecKstHist" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "PartRecKstHist", 1, 0, 1);
  PartRecKstHist->SetLineColor(kSpring - 1);
  PartRecKstHist->SetLineStyle(kDashed);
  PartRecKstHist->SetLineWidth(2);
  colorMap["PartRecKst"] = PartRecKstHist->GetLineColor();

  std::stringstream Bu2Dst0pi_D0gammaLegend;
  Bu2Dst0pi_D0gammaLegend
      << "B^{" + EnumToLabel(charge) +
             "}#rightarrow#font[132]{[}#font[132]{[}" +
             EnumToLabel(daughters, charge) +
             "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{0}*}#pi^{" +
             EnumToLabel(charge) + "}";
  std::stringstream Bu2Dst0K_D0gammaLegend;
  Bu2Dst0K_D0gammaLegend
      << "B^{" + EnumToLabel(charge) +
             "}#rightarrow#font[132]{[}#font[132]{[}" +
             EnumToLabel(daughters, charge) +
             "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{0}*}K^{" +
             EnumToLabel(charge) + "}";
  std::stringstream Bu2Dst0pi_D0pi0Legend;
  Bu2Dst0pi_D0pi0Legend
      << "B^{" + EnumToLabel(charge) +
             "}#rightarrow#font[132]{[}#font[132]{[}" +
             EnumToLabel(daughters, charge) +
             "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{0}*}#pi^{" +
             EnumToLabel(charge) + "}";
  std::stringstream Bu2Dst0K_D0pi0Legend;
  Bu2Dst0K_D0pi0Legend
      << "B^{" + EnumToLabel(charge) +
             "}#rightarrow#font[132]{[}#font[132]{[}" +
             EnumToLabel(daughters, charge) +
             "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{0}*}K^{" +
             EnumToLabel(charge) + "}";
  std::stringstream MisRecPiLegend;
  MisRecPiLegend << "Mis-Rec D^{*}#pi^{" + EnumToLabel(charge) + "}";
  std::stringstream MisRecKLegend;
  MisRecKLegend << "Mis-Rec D^{*}K^{" + EnumToLabel(charge) + "}";
  std::stringstream Bu2D0piLegend;
  Bu2D0piLegend << "B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}" +
                       EnumToLabel(daughters, charge) +
                       "#font[132]{]}_{D^{0}}#pi^{" + EnumToLabel(charge) + "}";
  std::stringstream Bu2D0KLegend;
  Bu2D0KLegend << "B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}" +
                      EnumToLabel(daughters, charge) +
                      "#font[132]{]}_{D^{0}}K^{" + EnumToLabel(charge) + "}";
  std::stringstream PartRecRhoLegend;
  PartRecRhoLegend
      << "B^{" + EnumToLabel(charge) +
             "}#rightarrow#font[132]{[}#font[132]{[}" +
             EnumToLabel(daughters, charge) +
             "#font[132]{]}_{D^{0}}#pi^{0}/#gamma#font[132]{]}_{D^{0}*}#rho^{" +
             EnumToLabel(charge) + "}";
  std::stringstream PartRecKstLegend;
  PartRecKstLegend
      << "B^{" + EnumToLabel(charge) +
             "}#rightarrow#font[132]{[}#font[132]{[}" +
             EnumToLabel(daughters, charge) +
             "#font[132]{]}_{D^{0}}#pi^{0}/#gamma#font[132]{]}_{D^{0}*}^{*" +
             EnumToLabel(charge) + "}";

  if (bachelor == Bachelor::pi) {
    if (neutral == Neutral::gamma) {
      legend.AddEntry(Bu2Dst0pi_D0gammaHist.get(),
                      Bu2Dst0pi_D0gammaLegend.str().c_str(), "l");
      legend.AddEntry(Bu2Dst0K_D0gammaHist.get(),
                      Bu2Dst0K_D0gammaLegend.str().c_str(), "l");
    }
    legend.AddEntry(Bu2Dst0pi_D0pi0Hist.get(),
                    Bu2Dst0pi_D0pi0Legend.str().c_str(), "l");
    legend.AddEntry(Bu2Dst0K_D0pi0Hist.get(),
                    Bu2Dst0K_D0pi0Legend.str().c_str(), "l");
    legend.AddEntry(MisRecPiHist.get(), MisRecPiLegend.str().c_str(), "l");
    legend.AddEntry(Bu2D0piHist.get(), Bu2D0piLegend.str().c_str(), "l");
    legend.AddEntry(PartRecRhoHist.get(), PartRecRhoLegend.str().c_str(), "l");
  } else {
    if (neutral == Neutral::gamma) {
      legend.AddEntry(Bu2Dst0K_D0gammaHist.get(),
                      Bu2Dst0K_D0gammaLegend.str().c_str(), "l");
      legend.AddEntry(Bu2Dst0pi_D0gammaHist.get(),
                      Bu2Dst0pi_D0gammaLegend.str().c_str(), "l");
    }
    legend.AddEntry(Bu2Dst0K_D0pi0Hist.get(),
                    Bu2Dst0K_D0pi0Legend.str().c_str(), "l");
    legend.AddEntry(Bu2Dst0pi_D0pi0Hist.get(),
                    Bu2Dst0pi_D0pi0Legend.str().c_str(), "l");
    legend.AddEntry(MisRecKHist.get(), MisRecKLegend.str().c_str(), "l");
    legend.AddEntry(MisRecPiHist.get(), MisRecPiLegend.str().c_str(), "l");
    legend.AddEntry(Bu2D0KHist.get(), Bu2D0KLegend.str().c_str(), "l");
    legend.AddEntry(Bu2D0piHist.get(), Bu2D0piLegend.str().c_str(), "l");
    legend.AddEntry(PartRecKstHist.get(), PartRecKstLegend.str().c_str(), "l");
    legend.AddEntry(PartRecRhoHist.get(), PartRecRhoLegend.str().c_str(), "l");
  }

  PlotComponent(Mass::buDelta, config.buDeltaMass(), pdf, fullDataSet, simPdf,
                categories, legend, lumiLegend, outputDir, config, colorMap);
  if (config.neutral() == Neutral::gamma) {
    PlotComponent(Mass::buDeltaPartial, config.buDeltaMass(), pdf, fullDataSet, simPdf,
                  categories, legend, lumiLegend, outputDir, config, colorMap);
  }
  if (config.fit1D() == false) {
    PlotComponent(Mass::delta, config.deltaMass(), pdf, fullDataSet, simPdf,
                  categories, legend, lumiLegend, outputDir, config, colorMap);
  }
}

void PlotCorrelations(RooFitResult *result, std::string const &outputDir,
                      Configuration &config) {
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
  corrCanvas.SaveAs((outputDir + "/plots/CorrelationMatrix_" +
                     config.ReturnBoxString() + ".pdf")
                        .c_str());
}

// Function that returns the simultaneous PDF, the class which collects all the
// individual components. It is that that we do all our fitting with
std::pair<RooSimultaneous *, std::vector<PdfBase *> > MakeSimultaneousPdf(
    int const id, Configuration &config, Configuration::Categories &categories,
    std::vector<Daughters> const &daughtersVec,
    std::vector<Charge> const &chargeVec) {
  RooSimultaneous *simPdf = new RooSimultaneous(
      ("simPdf_" + std::to_string(id)).c_str(),
      ("simPdf_" + std::to_string(id)).c_str(), categories.fitting);

  std::vector<PdfBase *> pdfs;
  // d is a reference to an element od the vector
  // Downside: don't have direct access to the index
  for (auto &c : chargeVec) {
    switch (config.neutral()) {
      case Neutral::gamma:
        switch (c) {
          case Charge::total:
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                                   Charge::total>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                                   Charge::total>::Get(id));
            Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                Charge::total>::Get(id)
                .AssignMisIdYields();
            Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                Charge::total>::Get(id)
                .AssignMisIdYields();
            Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                Charge::total>::Get(id)
                .CreateBuAddPdf();
            Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                Charge::total>::Get(id)
                .CreateBuAddPdf();
            if (Configuration::Get().fit1D() == false) {
              Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                  Charge::total>::Get(id)
                  .CreateDeltaAddPdf();
              Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                  Charge::total>::Get(id)
                  .CreateDeltaAddPdf();
            }
            break;
          case Charge::plus:
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                                   Charge::plus>::Get(id));
            Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                Charge::plus>::Get(id)
                .AssignMisIdYields();
            Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi, Charge::plus>::Get(
                id)
                .AssignMisIdYields();
            Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                Charge::plus>::Get(id)
                .CreateBuAddPdf();
            Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi, Charge::plus>::Get(
                id)
                .CreateBuAddPdf();
            if (Configuration::Get().fit1D() == false) {
              Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                  Charge::plus>::Get(id)
                  .CreateDeltaAddPdf();
              Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                  Charge::plus>::Get(id)
                  .CreateDeltaAddPdf();
            }
            break;
          case Charge::minus:
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                                   Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                                   Charge::minus>::Get(id));
            Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                Charge::minus>::Get(id)
                .AssignMisIdYields();
            Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                Charge::minus>::Get(id)
                .AssignMisIdYields();
            Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                Charge::minus>::Get(id)
                .CreateBuAddPdf();
            Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                Charge::minus>::Get(id)
                .CreateBuAddPdf();
            if (Configuration::Get().fit1D() == false) {
              Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                  Charge::minus>::Get(id)
                  .CreateDeltaAddPdf();
              Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                  Charge::minus>::Get(id)
                  .CreateDeltaAddPdf();
            }
            break;
        }
        break;
      case Neutral::pi0:
        switch (c) {
          case Charge::total:
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                                   Charge::total>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                                   Charge::total>::Get(id));
            Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::total>::Get(
                id)
                .AssignMisIdYields();
            Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::total>::Get(
                id)
                .AssignMisIdYields();
            Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::total>::Get(
                id)
                .CreateBuAddPdf();
            Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::total>::Get(
                id)
                .CreateBuAddPdf();
            if (Configuration::Get().fit1D() == false) {
              Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                  Charge::total>::Get(id)
                  .CreateDeltaAddPdf();
              Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                  Charge::total>::Get(id)
                  .CreateDeltaAddPdf();
            }
            break;
          case Charge::plus:
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                                   Charge::plus>::Get(id));
            Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::plus>::Get(
                id)
                .AssignMisIdYields();
            Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::plus>::Get(
                id)
                .AssignMisIdYields();
            Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::plus>::Get(
                id)
                .CreateBuAddPdf();
            Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::plus>::Get(
                id)
                .CreateBuAddPdf();
            if (Configuration::Get().fit1D() == false) {
              Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                  Charge::plus>::Get(id)
                  .CreateDeltaAddPdf();
              Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::plus>::Get(
                  id)
                  .CreateDeltaAddPdf();
            }
            break;
          case Charge::minus:
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                                   Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                                   Charge::minus>::Get(id));
            Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::minus>::Get(
                id)
                .AssignMisIdYields();
            Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::minus>::Get(
                id)
                .AssignMisIdYields();
            Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::minus>::Get(
                id)
                .CreateBuAddPdf();
            Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::minus>::Get(
                id)
                .CreateBuAddPdf();
            if (Configuration::Get().fit1D() == false) {
              Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                  Charge::minus>::Get(id)
                  .CreateDeltaAddPdf();
              Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                  Charge::minus>::Get(id)
                  .CreateDeltaAddPdf();
            }
            break;
        }
        break;
    }
  }

  for (auto &p : pdfs) {
    p->AddToSimultaneousPdf(*simPdf);
  }

  auto p = std::make_pair(simPdf, pdfs);
  return p;
}

void Plotting2D(RooDataSet &dataSet, int const id, PdfBase &pdf,
                Configuration &config, std::string const &outputDir,
                std::string const &label) {
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

  auto deltaAbsData = dataSet.reduce(
      ("fitting==fitting::" +
       ComposeFittingName(Mass::delta, neutral, bachelor, daughters, charge))
          .c_str());
  auto deltaDataSet = dynamic_cast<RooDataSet *>(deltaAbsData);
  if (deltaDataSet == nullptr) {
    throw std::runtime_error("Could not cast deltaAbsData to RooDataSet.");
  }

  auto buDeltaAbsData = dataSet.reduce(
      ("fitting==fitting::" +
       ComposeFittingName(Mass::buDelta, neutral, bachelor, daughters, charge))
          .c_str());
  auto buDeltaDataSet = dynamic_cast<RooDataSet *>(buDeltaAbsData);
  if (buDeltaDataSet == nullptr) {
    throw std::runtime_error("Could not cast buDeltaAbsData to RooDataSet.");
  }
  deltaDataSet->append(*buDeltaDataSet);

  if (config.neutral() == Neutral::gamma) {
    auto buDeltaPartialAbsData =
        dataSet.reduce(("fitting==fitting::" +
                        ComposeFittingName(Mass::buDeltaPartial, neutral,
                                           bachelor, daughters, charge))
                           .c_str());
    auto buDeltaPartialDataSet =
        dynamic_cast<RooDataSet *>(buDeltaPartialAbsData);
    if (buDeltaPartialDataSet == nullptr) {
      throw std::runtime_error(
          "Could not cast buDeltaPartialAbsData to RooDataSet.");
    }
    deltaDataSet->append(*buDeltaPartialDataSet);
  }

  auto dataHist = std::unique_ptr<RooDataHist>(deltaDataSet->binnedClone(
      (label + "Hist2d_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      ""));
  if (dataHist == nullptr) {
    throw std::runtime_error("Could not extact binned dataSet.");
  }

  auto dataHist1d = dataHist->createHistogram(
      (label + "Hist2d_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      config.buDeltaMass(), RooFit::Binning(config.buDeltaMass().getBins()),
      RooFit::YVar(config.deltaMass(),
                   RooFit::Binning(config.deltaMass().getBins())));
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
  TCanvas canvasData((label + "Canvas_" +
                      ComposeName(id, neutral, bachelor, daughters, charge))
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
  canvasData.SaveAs((outputDir + "/2d_plots/" +
                     ComposeName(id, neutral, bachelor, daughters, charge) +
                     "_" + label + "2D.pdf")
                        .c_str());
}

void Generate2D(std::map<std::string, RooDataSet *> &mapDataLabelDataSet,
                std::map<std::string, RooDataSet *> &mapDataLabelToy,
                int const id, PdfBase &pdf, Configuration &config,
                std::string const &outputDir) {
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

  auto dataHist = std::unique_ptr<RooDataHist>(
      mapDataLabelDataSet[ComposeDataLabelName(neutral, bachelor, daughters,
                                               charge)]
          ->binnedClone(("dataHist_" + ComposeDataLabelName(neutral, bachelor,
                                                            daughters, charge))
                            .c_str(),
                        "dataHist"));
  if (dataHist == nullptr) {
    throw std::runtime_error("Could not extact binned dataSet.");
  }

  RooHistPdf histPdf(
      ("histPdf_" + ComposeDataLabelName(neutral, bachelor, daughters, charge))
          .c_str(),
      "", config.fittingArgSet(), *dataHist.get(), 2);

  auto toyData = histPdf.generate(
      config.fittingArgSet(),
      mapDataLabelDataSet[ComposeDataLabelName(neutral, bachelor, daughters,
                                               charge)]
          ->numEntries());

  if (mapDataLabelToy.find(ComposeDataLabelName(
          neutral, bachelor, daughters, charge)) == mapDataLabelToy.end()) {
    mapDataLabelToy.insert(std::make_pair(
        ComposeDataLabelName(neutral, bachelor, daughters, charge), toyData));
    std::cout << "Created key-value pair for category " +
                     ComposeDataLabelName(neutral, bachelor, daughters,
                                          charge) +
                     " and corresponding toy\n";
  } else {
    mapDataLabelToy[ComposeDataLabelName(neutral, bachelor, daughters, charge)]
        ->append(*toyData);
    std::cout << "Appended toy to category " +
                     ComposeDataLabelName(neutral, bachelor, daughters,
                                          charge) +
                     "\n";
  }
}

void MakeMapFittingDataSet(
    PdfBase &pdf, std::map<std::string, RooDataSet *> &mapDataLabelDataSet,
    std::map<std::string, RooDataSet *> &mapFittingDataSet,
    Configuration &config) {
  Bachelor b = pdf.bachelor();
  Daughters d = pdf.daughters();
  Neutral n = pdf.neutral();
  Charge c = pdf.charge();

  RooDataSet *buDeltaDataSet = nullptr;
  buDeltaDataSet = dynamic_cast<RooDataSet *>(
      mapDataLabelDataSet[ComposeDataLabelName(n, b, d, c)]->reduce(
          ("Delta_M>" + std::to_string(config.deltaLow()) + "&&Delta_M<" +
           std::to_string(config.deltaHigh()))
              .c_str()));
  if (buDeltaDataSet == nullptr) {
    throw std::runtime_error("Could not reduce buDelta data with box cuts.");
  }
  if (mapFittingDataSet.find(ComposeFittingName(Mass::buDelta, n, b, d, c)) ==
      mapFittingDataSet.end()) {
    mapFittingDataSet.insert(std::make_pair(
        ComposeFittingName(Mass::buDelta, n, b, d, c), buDeltaDataSet));
    std::cout << "Created key-value pair for category " +
                     ComposeFittingName(Mass::buDelta, n, b, d, c) +
                     " and corresponding dataSet\n";
  } else {
    mapFittingDataSet[ComposeFittingName(Mass::buDelta, n, b, d, c)]->append(
        *buDeltaDataSet);
    std::cout << "Appended dataSet to category " +
                     ComposeFittingName(Mass::buDelta, n, b, d, c) + "\n";
  }
  if (n == Neutral::gamma) {
    RooDataSet *buDeltaPartialDataSet = nullptr;
    buDeltaPartialDataSet = dynamic_cast<RooDataSet *>(
        mapDataLabelDataSet[ComposeDataLabelName(n, b, d, c)]->reduce(
            ("Delta_M>" + std::to_string(config.deltaPartialLow()) +
             "&&Delta_M<" + std::to_string(config.deltaPartialHigh()))
                .c_str()));
    if (buDeltaPartialDataSet == nullptr) {
      throw std::runtime_error(
          "Could not reduce buDeltaPartial data with box cuts.");
    }
    if (mapFittingDataSet.find(ComposeFittingName(
            Mass::buDeltaPartial, n, b, d, c)) == mapFittingDataSet.end()) {
      mapFittingDataSet.insert(
          std::make_pair(ComposeFittingName(Mass::buDeltaPartial, n, b, d, c),
                         buDeltaPartialDataSet));
      std::cout << "Created key-value pair for category " +
                       ComposeFittingName(Mass::buDeltaPartial, n, b, d, c) +
                       " and corresponding dataSet\n";
    } else {
      mapFittingDataSet[ComposeFittingName(Mass::buDeltaPartial, n, b, d, c)]
          ->append(*buDeltaPartialDataSet);
      std::cout << "Appended dataSet to category " +
                       ComposeFittingName(Mass::buDeltaPartial, n, b, d, c) +
                       "\n";
    }
  }
  if (config.fit1D() == false) {
    RooDataSet *deltaDataSet = nullptr;
    deltaDataSet = dynamic_cast<RooDataSet *>(
        mapDataLabelDataSet[ComposeDataLabelName(n, b, d, c)]->reduce(
            ("Bu_Delta_M>" + std::to_string(config.buDeltaLow()) +
             "&&Bu_Delta_M<" + std::to_string(config.buDeltaHigh()))
                .c_str()));
    if (deltaDataSet == nullptr) {
      throw std::runtime_error("Could not reduce delta data with box cuts.");
    }
    if (mapFittingDataSet.find(ComposeFittingName(Mass::delta, n, b, d, c)) ==
        mapFittingDataSet.end()) {
      mapFittingDataSet.insert(std::make_pair(
          ComposeFittingName(Mass::delta, n, b, d, c), deltaDataSet));
      std::cout << "Created key-value pair for category " +
                       ComposeFittingName(Mass::delta, n, b, d, c) +
                       " and corresponding dataSet\n";
    } else {
      mapFittingDataSet[ComposeFittingName(Mass::delta, n, b, d, c)]->append(
          *deltaDataSet);
      std::cout << "Appended dataSet to category " +
                       ComposeFittingName(Mass::delta, n, b, d, c) + "\n";
    }
  }
}

void Run2DToys(TFile &outputFile,
               std::map<std::string, RooDataSet *> &mapDataLabelDataSet,
               Configuration &config, Configuration::Categories &categories,
               std::vector<Daughters> const &daughtersVec,
               std::vector<Charge> const &chargeVec,
               std::string const &outputDir, int id) {
  std::cout << "\n\n -------------------------- Running toy #" << id
            << " -------------------------- \n\n";
  auto p = MakeSimultaneousPdf(id, config, categories, daughtersVec, chargeVec);
  auto pdfs = p.second;

  std::map<std::string, RooDataSet *> mapDataLabelToy;

  for (auto &p : pdfs) {
    Generate2D(mapDataLabelDataSet, mapDataLabelToy, id, *p, config, outputDir);
  }

  auto simPdf = std::unique_ptr<RooSimultaneous>(p.first);

  std::map<std::string, RooDataSet *> mapFittingDataSet;
  std::map<std::string, RooDataSet *> mapFittingToy;
  for (auto &p : pdfs) {
    MakeMapFittingDataSet(*p, mapDataLabelDataSet, mapFittingDataSet, config);
    MakeMapFittingDataSet(*p, mapDataLabelToy, mapFittingToy, config);
  }

  RooDataSet toyDataSet("toyDataSet", "toyDataSet", config.fittingArgSet(),
                        RooFit::Index(categories.fitting),
                        RooFit::Import(mapFittingToy));

  auto toyDataHist = std::unique_ptr<RooDataHist>(
      toyDataSet.binnedClone("toyDataHist", "toyDataHist"));
  if (toyDataHist == nullptr) {
    throw std::runtime_error("Could not extact binned dataSet.");
  }
  auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());
  if (toyAbsData == nullptr) {
    throw std::runtime_error("Could not cast to RooAbsData.");
  }

  std::shared_ptr<RooFitResult> toyFitResult;
  if (config.noFit() == false) {
    toyFitResult = std::shared_ptr<RooFitResult>(
        simPdf->fitTo(*toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
                      RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                      RooFit::Offset(true), RooFit::NumCPU(8, 2)));
    // toyFitResult->SetName(("ToyResult_" + std::to_string(id)).c_str());
    toyFitResult->SetName("ToyResult");
  }

  RooDataSet dataSet("dataSet", "dataSet", config.fittingArgSet(),
                     RooFit::Index(categories.fitting),
                     RooFit::Import(mapFittingDataSet));

  std::cout << "\n\n\n";
  toyDataSet.Print();
  dataSet.Print();
  std::cout << "\n\n\n";

  if (id == 1) {
    for (auto &p : pdfs) {
      std::string toyLabel = "toy";
      std::string dataLabel = "data";
      Plotting2D(dataSet, id, *p, config, outputDir, dataLabel);
      Plotting2D(toyDataSet, id, *p, config, outputDir, toyLabel);
    }
    std::string lumiString = "TOY";
    for (auto &p : pdfs) {
      Plotting1D(id, *p, config, categories, *toyAbsData, *simPdf, outputDir,
                 lumiString, toyFitResult.get());
    }
    if (config.noFit() == false) {
      PlotCorrelations(toyFitResult.get(), outputDir, config);
    }
  }
  if (config.noFit() == false) {
    // to make a unique result each time
    toyFitResult->Print("v");
    outputFile.cd();
    toyFitResult->Write();
    outputFile.Close();
    std::cout << toyFitResult->GetName() << " has been saved to file "
              << outputFile.GetName() << "\n";
  }
}

void RunD1DToys(std::unique_ptr<RooSimultaneous> &simPdf,
                std::unique_ptr<RooFitResult> &dataFitResult,
                Configuration &config, Configuration::Categories &categories,
                std::vector<Daughters> const &daughtersVec,
                std::vector<Charge> const &chargeVec,
                std::string const &outputDir, int nToys) {
  // Start from 1 as id = 0 is data fit params
  for (int id = 1; id < nToys + 1; ++id) {
    std::cout << "\n\n -------------------------- Running toy #" << id
              << " -------------------------- \n\n";
    // Setting the random seed to 0 is a special case which generates a
    // different seed every time you run. Setting the seed to an integer
    // generates toys in a replicable way, in case you need to debug
    // something.

    if (simPdf == nullptr) {
      // id=0, equivalent to what would be the data fit
      int tmpId = 0;
      auto p = MakeSimultaneousPdf(tmpId, config, categories, daughtersVec,
                                   chargeVec);
      simPdf = std::unique_ptr<RooSimultaneous>(p.first);
    }

    RooRandom::randomGenerator()->SetSeed(0);
    TRandom3 random(0);
    double randomTag = random.Rndm();

    double nEvtsPerToy = simPdf->expectedEvents(categories.fitting);
    std::unique_ptr<RooDataSet> toyDataSet;
    if (config.fit1D() == false) {
      toyDataSet = std::unique_ptr<RooDataSet>(
          simPdf->generate(RooArgSet(config.buDeltaMass(), config.deltaMass(),
                                     categories.fitting),
                           nEvtsPerToy));
    } else {
      toyDataSet = std::unique_ptr<RooDataSet>(simPdf->generate(
          RooArgSet(config.buDeltaMass(), categories.fitting), nEvtsPerToy));
    }
    toyDataSet->SetName(("toyDataSet_" + std::to_string(id)).c_str());
    auto toyDataHist = std::unique_ptr<RooDataHist>(
        toyDataSet->binnedClone(("toyDataHist_" + std::to_string(id)).c_str(),
                                ("toyDataHist" + std::to_string(id)).c_str()));
    auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

    auto simPdfToFit = std::unique_ptr<RooSimultaneous>(new RooSimultaneous(
        ("simPdfFit_" + std::to_string(id)).c_str(),
        ("simPdfFit_" + std::to_string(id)).c_str(), categories.fitting));

    auto p =
        MakeSimultaneousPdf(id, config, categories, daughtersVec, chargeVec);
    simPdfToFit = std::unique_ptr<RooSimultaneous>(p.first);

    std::shared_ptr<RooFitResult> toyFitResult;
    if (config.noFit() == false) {
      toyFitResult = std::shared_ptr<RooFitResult>(simPdfToFit->fitTo(
          *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
          RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
          RooFit::Offset(true), RooFit::NumCPU(8, 2)));
      toyFitResult->SetName("ToyResult");
      // toyFitResult->SetName(("ToyResult_" + std::to_string(id)).c_str());
    }
    if (id == 1) {
      std::string lumiString = "TOY";
      auto pdfs = p.second;
      for (auto &p : pdfs) {
        Plotting1D(id, *p, config, categories, *toyAbsData, *simPdfToFit,
                   outputDir, lumiString, toyFitResult.get());
      }
      if (config.noFit() == false) {
        PlotCorrelations(toyFitResult.get(), outputDir, config);
      }
    }

    if (config.noFit() == false) {
      toyFitResult->Print("v");
      std::string dimString = "D1D";
      if (config.fit1D() == true) {
        dimString = "1D";
      }
      TFile outputFile(
          (outputDir + "/results/Result" + dimString + "_" +
           config.ReturnBoxString() + "_" + std::to_string(randomTag) + ".root")
              .c_str(),
          "recreate");

      outputFile.cd();
      toyFitResult->Write();
      if (dataFitResult != nullptr) {
        dataFitResult->Write();
      }
      outputFile.Close();
      std::cout << "Results saved to file " << outputFile.GetName() << "\n";
    }
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
  std::string inputDir = "";
  std::string outputDir;
  std::vector<Year> yearVec;
  std::vector<Polarity> polarityVec;
  std::vector<Bachelor> bachelorVec;
  std::vector<Daughters> daughtersVec;
  std::vector<Charge> chargeVec;
  // Still want to load both charges:plus and minus, we just fit with
  // them differently

  int nToys = 0;
  Configuration &config = Configuration::Get();

  // By letting the ParseArguments object go out of scope it will print a
  // warning if the user specified any unknown options.
  {  // calls destructor when object goes out of scope: Will tell you if
    // anything
    // was not used that was given as a command line argument before
    // continuing
    ParseArguments args(argc, argv);  // object instantiated

    std::string yearArg("2011,2012,2015,2016,2017,2018");
    std::string polarityArg("up,down");
    std::string bachelorArg("pi,k");
    std::string neutralArg("gamma");
    std::string daughtersArg("kpi,kk,pipi,pik");
    std::string chargeArg("total");
    int toysArg = 0;
    float deltaLowArg = 0.0;
    float deltaHighArg = 0.0;
    float buDeltaLowArg = 0.0;
    float buDeltaHighArg = 0.0;

    // We always want to simultaneously fir the pi AND k bachelor modes
    // together
    bachelorVec = ExtractEnumList<Bachelor>(bachelorArg);

    if (args("help")) {
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "Type ./Fitting \n"
                << "-inputDir=<RooDataSets directory name> if fitting to data "
                   "or toy generated from data \n"
                << "-outputDir=<output directory> \n";
      std::cout << "Give box dimensions:\n"
                << "    -dl=#, -dh=#, -bl=#, -bh=#\n";
      std::cout << "Followed by the possible options:\n";
      std::cout << "    -1D, default fit is double 1D\n";
      std::cout << "    -noFit, default is to fit PDF to data\n";
      std::cout << "    -year=<choice {2011,2012,2015,2016} default: "
                << yearArg << ">\n";
      std::cout << "    -polarity=<choice {up,down} default: " << polarityArg
                << ">\n";
      // std::cout << "    -bachelor choice {k,pi} default: " << bachelorArg
      // <<
      // "\n";
      std::cout << "    -neutral=<choice {pi0/gamma} default: " << neutralArg
                << ">\n";
      std::cout << "    -daughters=<choice {kpi,kk,pipi,pik} default: "
                << daughtersArg << ">\n";
      std::cout << "    -charge=<choice {plus/minus/total} default: "
                << chargeArg << ">\n";
      std::cout << "To specify multiple options, separate them by commas.\n";
      std::cout << "    -toys=<# toys>"
                << "\n";
      std::cout << "    Optional: if you want to run toys. If # toys = 1, toys "
                   "will also be plotted.\n";
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "\n";

      return 1;
    } else {
      if (!args("bl", buDeltaLowArg)) {
        std::cout
            << "Using default value for lower buDelta mass box threshold: " +
                   std::to_string(config.buDeltaLow()) + "\n";
      } else {
        config.SetBuDeltaLow(buDeltaLowArg);
        std::cout << "Set value for lower buDelta mass box threshold: " +
                         std::to_string(config.buDeltaLow()) + "\n";
      }
      if (!args("bh", buDeltaHighArg)) {
        std::cout
            << "Using default value for upper buDelta mass box threshold: " +
                   std::to_string(config.buDeltaHigh()) + "\n";
      } else {
        config.SetBuDeltaHigh(buDeltaHighArg);
        std::cout << "Set value for upper buDelta mass box threshold: " +
                         std::to_string(config.buDeltaHigh()) + "\n";
      }
      if (!args("dl", deltaLowArg)) {
        std::cout
            << "Using default value for lower delta mass box threshold: " +
                   std::to_string(config.deltaLow()) + "\n";
      } else {
        config.SetDeltaLow(deltaLowArg);
        std::cout << "Set value for lower delta mass box threshold: " +
                         std::to_string(config.deltaLow()) + "\n";
      }
      if (!args("dh", deltaHighArg)) {
        std::cout
            << "Using default value for upper delta mass box threshold: " +
                   std::to_string(config.deltaHigh()) + "\n";
      } else {
        config.SetDeltaHigh(deltaHighArg);
        std::cout << "Set value for upper delta mass box threshold: " +
                         std::to_string(config.deltaHigh()) + "\n";
      }

      if (!args("toys", toysArg)) {
        std::cout << "Running data fit.\n";
      } else {
        nToys = toysArg;
        std::cout << "Running " << nToys << " toys\n";
      }

      if (!args("inputDir", inputDir) && nToys == 0) {
        std::cerr << "Data directory must be specified (-inputDir=<path>).\n";
        return 1;
      } else {
        std::cout << "Generating toy from PDF MC shapes.\n";
      }

      if (!args("outputDir", outputDir)) {
        std::cerr << "Specify output directory (-outputDir=<path>).\n";
        return 1;
      }
      if (args("1D")) {
        std::cout << "Running 1D fit.\n";
        config.fit1D() = true;
      }
      if (args("noFit")) {
        std::cout << "Will not fit PDF to data, just plot both.\n";
        config.noFit() = true;
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
        config.SetNeutral(StringToEnum<Neutral>(neutralArg));
      } catch (std::invalid_argument) {
        std::cerr << "neutral assignment failed, please specify: "
                     "-neutral=[pi0/gamma].\n";
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

  if (chargeVec.size() > 1) {
    config.splitByCharge() = true;
  }

  Configuration::Categories &categories = Configuration::Get().categories();

  // Raise lower mass boundary in delta mass for pi0 plots
  if (config.neutral() == Neutral::pi0) {
    config.deltaMass().setMin(136);
    config.deltaMass().setBins(54);
    config.initYieldFAVSignal() = 1.3346e+04;
  }

  // Declare simPDF and result before any if statements so that it can be passed
  // to RunD1DToys no matter what
  std::unique_ptr<RooSimultaneous> simPdf;
  std::unique_ptr<RooFitResult> dataFitResult;

  if (inputDir != "") {
    std::map<std::string, RooDataSet *> mapDataLabelDataSet;

    // Add up lumi in order to convert into string to go on plots
    double lumi = 0;
    double lumiErr = 0;

    // Loop over all options in
    // order to extract correct roodataSets.
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
      } else if (y == Year::y2018) {
        lumi += 2.19;
      }
      for (auto &p : polarityVec) {
        for (auto &b : bachelorVec) {
          for (auto &d : daughtersVec) {
            for (auto &c : chargeVec) {
              std::string dsFile =
                  inputDir + "/" +
                  ComposeFilename(y, p, b, config.neutral(), d, c) + ".root";
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
                  RooDataSet *reducedInputDataSet_n = nullptr;
                  if (config.neutral() == Neutral::pi0) {
                    reducedInputDataSet_n = dynamic_cast<RooDataSet *>(
                        inputDataSet->reduce(config.gammaCutString().c_str()));
                  } else {
                    reducedInputDataSet_n = dynamic_cast<RooDataSet *>(
                        inputDataSet->reduce(config.pi0CutString().c_str()));
                  }
                  if (reducedInputDataSet_n == nullptr) {
                    throw std::runtime_error(
                        "Could not reduce input w/ neutral cuts dataSet.");
                  }
                  RooDataSet *reducedInputDataSet_b = nullptr;
                  if (b == Bachelor::pi) {
                    reducedInputDataSet_b = dynamic_cast<RooDataSet *>(
                        reducedInputDataSet_n->reduce("bach_PIDK<12"));
                  } else {
                    reducedInputDataSet_b = dynamic_cast<RooDataSet *>(
                        reducedInputDataSet_n->reduce("bach_PIDK>12"));
                  }
                  if (reducedInputDataSet_b == nullptr) {
                    throw std::runtime_error(
                        "Could not reduce input dataSet w/ bachelor cuts.");
                  }
                  RooDataSet *reducedInputDataSet_d = nullptr;
                  if (d == Daughters::kpi || d == Daughters::pik) {
                    reducedInputDataSet_d = dynamic_cast<
                        RooDataSet *>(reducedInputDataSet_b->reduce(
                        config.fittingArgSet(),
                        "((abs(h1_D_ID)==211&&h1_D_PIDK<-2)&&(abs(h2_D_ID)=="
                        "321&&h2_D_PIDK>2))||((abs(h1_D_ID)"
                        "==321&&h1_D_PIDK>2)&&(abs(h2_D_ID)==211&&h2_D_"
                        "PIDK<-2))"));
                  } else if (d == Daughters::kk) {
                    reducedInputDataSet_d = dynamic_cast<RooDataSet *>(
                        reducedInputDataSet_b->reduce(
                            config.fittingArgSet(),
                            "h1_D_PIDK>2&&h2_D_PIDK>2"));
                  } else {
                    reducedInputDataSet_d = dynamic_cast<RooDataSet *>(
                        reducedInputDataSet_b->reduce(
                            config.fittingArgSet(),
                            "h1_D_PIDK<-2&&h2_D_PIDK<-2"));
                  }
                  if (reducedInputDataSet_d == nullptr) {
                    throw std::runtime_error(
                        "Could not reduce input dataSet w/ daughter cuts.");
                  }
                  std::cout << "\n\n";
                  // Need to append each year, polarity to dataSet at each key
                  // in map, as key labelled by config.neutral(), b, d, c and
                  // must be unique.
                  if (mapDataLabelDataSet.find(
                          ComposeDataLabelName(config.neutral(), b, d, c)) ==
                      mapDataLabelDataSet.end()) {
                    mapDataLabelDataSet.insert(std::make_pair(
                        ComposeDataLabelName(config.neutral(), b, d, c),
                        reducedInputDataSet_d));
                    std::cout
                        << "Created key-value pair for category " +
                               ComposeDataLabelName(config.neutral(), b, d, c) +
                               " and corresponding dataSet\n";
                  } else {
                    mapDataLabelDataSet[ComposeDataLabelName(config.neutral(),
                                                             b, d, c)]
                        ->append(*reducedInputDataSet_d);
                    std::cout
                        << "Appended dataSet to category " +
                               ComposeDataLabelName(config.neutral(), b, d, c) +
                               "\n";
                  }
                }
              }
            }
          }
        }
      }
    }

    std::vector<std::string> toyFileNames(nToys);
    if (nToys != 0) {
      // start at id = 1 to reserve 0 for data fit
      for (int id = 1; id < nToys + 1; ++id) {
        RooRandom::randomGenerator()->SetSeed(0);
        TRandom3 random(0);
        double randomTag = random.Rndm();
        TFile toyResultFile(
            (outputDir + "/results/Result2D_" + config.ReturnBoxString() + "_" +
             std::to_string(randomTag) + ".root")
                .c_str(),
            "recreate");
        // Pass random??
        Run2DToys(toyResultFile, mapDataLabelDataSet, config, categories,
                  daughtersVec, chargeVec, outputDir, id);
        toyFileNames[id - 1] = toyResultFile.GetName();
        toyResultFile.Close();
      }
    }
    // id = 0 for data fit
    int id = 0;
    auto p =
        MakeSimultaneousPdf(id, config, categories, daughtersVec, chargeVec);
    simPdf = std::unique_ptr<RooSimultaneous>(p.first);
    auto pdfs = p.second;
    // Apply box cuts and split PDF into mass categories too
    std::map<std::string, RooDataSet *> mapFittingDataSet;
    for (auto &p : pdfs) {
      MakeMapFittingDataSet(*p, mapDataLabelDataSet, mapFittingDataSet, config);
    }

    RooDataSet fullDataSet("fullDataSet", "fullDataSet", config.fittingArgSet(),
                           RooFit::Index(categories.fitting),
                           RooFit::Import(mapFittingDataSet));

    std::cout << "\n\n\n";
    fullDataSet.Print();
    std::cout << "\n\n\n";

    auto fullDataHist = std::unique_ptr<RooDataHist>(
        fullDataSet.binnedClone("fullDataHist", "fullDataHist"));
    if (fullDataHist == nullptr) {
      throw std::runtime_error("Could not extact binned dataSet.");
    }
    auto fullAbsData = dynamic_cast<RooAbsData *>(fullDataHist.get());
    if (fullAbsData == nullptr) {
      throw std::runtime_error("Could not cast to RooAbsData.");
    }

    if (config.noFit() == false) {
      dataFitResult = std::unique_ptr<RooFitResult>(
          simPdf->fitTo(*fullAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
                        RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                        RooFit::Offset(true), RooFit::NumCPU(8, 2)));
      dataFitResult->SetName("DataFitResult");
    }

    if (nToys == 0) {
      // String for lumi label on 1D projection plots
      std::ostringstream lumiStream, lumiErrStream;
      lumiStream << std::setprecision(2) << lumi;
      lumiErrStream << std::setprecision(2) << lumiErr;
      std::string lumiString = "#int L dt = " + lumiStream.str() + " #pm " +
                               lumiErrStream.str() + " fb^{-1}";
      // Loop over daughters again to plot correct PDFs
      for (auto &p : pdfs) {
        Plotting1D(id, *p, config, categories, fullDataSet, *simPdf, outputDir,
                   lumiString, dataFitResult.get());
      }

      if (config.noFit() == false) {
        dataFitResult->Print("v");
        PlotCorrelations(dataFitResult.get(), outputDir, config);
        // Save RFR of data and efficiencies to calculate observables with
        // corrected errors
        TFile outputFile((outputDir + "/results/DataResult_" +
                          config.ReturnBoxString() + ".root")
                             .c_str(),
                         "recreate");
        dataFitResult->Write();
        TTree tree("tree", "");
        double boxEffSignal, orEffSignal, buDeltaCutEffSignal,
            deltaCutEffSignal;
        int id = 0;
        RooRealVar orEffSignalRRV(
            ("orEffSignalRRV_" + EnumToString(config.neutral())).c_str(), "",
            1);
        RooRealVar boxEffSignalRRV(
            ("boxEffSignalRRV_" + EnumToString(config.neutral())).c_str(), "",
            1);
        RooRealVar buDeltaCutEffSignalRRV(
            ("buDeltaCutEffSignalRRV_" + EnumToString(config.neutral()))
                .c_str(),
            "", 1);
        RooRealVar deltaCutEffSignalRRV(
            ("deltaCutEffSignalRRV_" + EnumToString(config.neutral())).c_str(),
            "", 1);
        switch (config.neutral()) {
          case Neutral::gamma: {
            NeutralVars<Neutral::gamma> gVars(id);
            gVars.SetEfficiencies(Mode::Bu2Dst0pi_D0gamma, orEffSignalRRV,
                                  boxEffSignalRRV, buDeltaCutEffSignalRRV,
                                  deltaCutEffSignalRRV);
          } break;
          case Neutral::pi0: {
            NeutralVars<Neutral::pi0> pVars(id);
            pVars.SetEfficiencies(Mode::Bu2Dst0pi_D0pi0, orEffSignalRRV,
                                  boxEffSignalRRV, buDeltaCutEffSignalRRV,
                                  deltaCutEffSignalRRV);
          } break;
        }
        orEffSignal = orEffSignalRRV.getVal();
        boxEffSignal = boxEffSignalRRV.getVal();
        buDeltaCutEffSignal = buDeltaCutEffSignalRRV.getVal();
        deltaCutEffSignal = deltaCutEffSignalRRV.getVal();
        tree.Branch(
            ("orEffSignal_" + EnumToString(config.neutral())).c_str(),
            &orEffSignal,
            ("orEffSignal_" + EnumToString(config.neutral()) + "/D").c_str());
        tree.Branch(
            ("boxEffSignal_" + EnumToString(config.neutral())).c_str(),
            &boxEffSignal,
            ("boxEffSignal_" + EnumToString(config.neutral()) + "/D").c_str());
        tree.Branch(
            ("buDeltaCutEffSignal_" + EnumToString(config.neutral())).c_str(),
            &buDeltaCutEffSignal,
            ("buDeltaCutEffSignal_" + EnumToString(config.neutral()) + "/D")
                .c_str());
        tree.Branch(
            ("deltaCutEffSignal_" + EnumToString(config.neutral())).c_str(),
            &deltaCutEffSignal,
            ("deltaCutEffSignal_" + EnumToString(config.neutral()) + "/D")
                .c_str());
        tree.Fill();
        tree.Write();
        outputFile.Write();
        outputFile.Close();
      }
    } else {
      if (config.noFit() == false) {
        dataFitResult->Print("v");
        for (int id = 1; id < nToys + 1; ++id) {
          if (dataFitResult != nullptr) {
            TFile toyResultFile(toyFileNames[id - 1].c_str(), "update");
            dataFitResult->Write();
            toyResultFile.Close();
            std::cout << "DataFitResult saved to file " << toyFileNames[id - 1]
                      << "\n";
          } else {
            throw std::runtime_error("DataFitResult empty.");
          }
        }
      }
    }
  } else {
    std::cout << "Fitting using D1D method\n";
    RunD1DToys(simPdf, dataFitResult, config, categories, daughtersVec,
               chargeVec, outputDir, nToys);
  }
  return 0;
}
