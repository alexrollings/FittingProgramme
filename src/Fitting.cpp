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

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorVars.h"
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
void PlotComponent(RooRealVar &var, PdfBase &pdf, RooAbsData const &fullDataSet,
                   RooSimultaneous const &simPdf,
                   Configuration::Categories &categories, TLegend &legend,
                   TLegend &lumiLegend, std::string const &outputDir,
                   bool fitBool, Configuration &config) {
  Bachelor bachelor = pdf.bachelor();
  Mass mass = pdf.mass();
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
  simPdf.plotOn(frame.get(),
                RooFit::Slice(categories.fitting,
                              ComposeFittingName(mass, neutral, bachelor,
                                                 daughters, charge)
                                  .c_str()),
                RooFit::ProjWData(categories.fitting, fullDataSet),
                RooFit::LineColor(kBlue));

  // Everything to be plotted has to be declared outside of a loop, in the scope
  // of the canvas
  RooHist *pullHist = nullptr;
  std::unique_ptr<RooPlot> pullFrame(var.frame(RooFit::Title(" ")));

  pullHist = frame->RooPlot::pullHist();

  if (mass == Mass::buDelta) {
    simPdf.plotOn(frame.get(),
                  RooFit::Slice(categories.fitting,
                                ComposeFittingName(mass, neutral, bachelor,
                                                   daughters, charge)
                                    .c_str()),
                  RooFit::ProjWData(categories.fitting, fullDataSet),
                  RooFit::Components(pdf.pdfBu_Bu2Dst0h_D0gamma().GetName()),
                  RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue),
                  RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                .c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName()),
        RooFit::LineStyle(kDashed), RooFit::LineColor(kMagenta),
        RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
    simPdf.plotOn(frame.get(),
                  RooFit::Slice(categories.fitting,
                                ComposeFittingName(mass, neutral, bachelor,
                                                   daughters, charge)
                                    .c_str()),
                  RooFit::ProjWData(categories.fitting, fullDataSet),
                  RooFit::Components(pdf.pdfBu_Bu2Dst0h_D0pi0().GetName()),
                  RooFit::LineStyle(kDashed), RooFit::LineColor(kOrange),
                  RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
    simPdf.plotOn(frame.get(),
                  RooFit::Slice(categories.fitting,
                                ComposeFittingName(mass, neutral, bachelor,
                                                   daughters, charge)
                                    .c_str()),
                  RooFit::ProjWData(categories.fitting, fullDataSet),
                  RooFit::Components(pdf.pdfBu_MisRec().GetName()),
                  RooFit::LineStyle(kDashed), RooFit::LineColor(kRed),
                  RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
    simPdf.plotOn(frame.get(),
                  RooFit::Slice(categories.fitting,
                                ComposeFittingName(mass, neutral, bachelor,
                                                   daughters, charge)
                                    .c_str()),
                  RooFit::ProjWData(categories.fitting, fullDataSet),
                  RooFit::Components(pdf.pdfBu_Bu2D0h().GetName()),
                  RooFit::LineStyle(kDashed), RooFit::LineColor(kGreen),
                  RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
  } else {
    simPdf.plotOn(frame.get(),
                  RooFit::Slice(categories.fitting,
                                ComposeFittingName(mass, neutral, bachelor,
                                                   daughters, charge)
                                    .c_str()),
                  RooFit::ProjWData(categories.fitting, fullDataSet),
                  RooFit::Components(pdf.pdfDelta_Bu2Dst0h_D0gamma().GetName()),
                  RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue),
                  RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                .c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName()),
        RooFit::LineStyle(kDashed), RooFit::LineColor(kMagenta),
        RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
    simPdf.plotOn(frame.get(),
                  RooFit::Slice(categories.fitting,
                                ComposeFittingName(mass, neutral, bachelor,
                                                   daughters, charge)
                                    .c_str()),
                  RooFit::ProjWData(categories.fitting, fullDataSet),
                  RooFit::Components(pdf.pdfDelta_Bu2Dst0h_D0pi0().GetName()),
                  RooFit::LineStyle(kDashed), RooFit::LineColor(kOrange),
                  RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
    simPdf.plotOn(frame.get(),
                  RooFit::Slice(categories.fitting,
                                ComposeFittingName(mass, neutral, bachelor,
                                                   daughters, charge)
                                    .c_str()),
                  RooFit::ProjWData(categories.fitting, fullDataSet),
                  RooFit::Components(pdf.pdfDelta_MisRec().GetName()),
                  RooFit::LineStyle(kDashed), RooFit::LineColor(kRed),
                  RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
    simPdf.plotOn(frame.get(),
                  RooFit::Slice(categories.fitting,
                                ComposeFittingName(mass, neutral, bachelor,
                                                   daughters, charge)
                                    .c_str()),
                  RooFit::ProjWData(categories.fitting, fullDataSet),
                  RooFit::Components(pdf.pdfDelta_Bu2D0h().GetName()),
                  RooFit::LineStyle(kDashed), RooFit::LineColor(kGreen),
                  RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
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

  if (fitBool == true) {
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

  std::string fileLabel;
  if (config.fit1D() == false) {
    fileLabel = std::to_string(config.deltaLow()) + "_" +
                std::to_string(config.deltaHigh()) + "_" +
                std::to_string(config.buDeltaLow()) + "_" +
                std::to_string(config.buDeltaHigh());
  } else {
    fileLabel = std::to_string(config.deltaLow()) + "_" +
                std::to_string(config.deltaHigh());
  }
  canvas.Update();
  canvas.SaveAs((outputDir + "/plots/" +
                 ComposeName(id, mass, neutral, bachelor, daughters, charge) +
                 "_" + fileLabel + ".pdf")
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
  Mass mass = pdf.mass();

  if (charge == Charge::plus) {
    std::cout << "plus\n";
  } else if (charge == Charge::minus) {
    std::cout << "minus\n";
  } else {
    std::cout << "total\n";
  }

  TLegend legend(0.71, 0.53, 0.85, 0.8);
  // ------------- Draw Legends -------------- //
  auto Bu2Dst0h_D0gammaHist = std::make_unique<TH1D>(
      ("Bu2Dst0h_D0gammaHist" +
       ComposeName(id, mass, neutral, bachelor, daughters, charge))
          .c_str(),
      "Bu2Dst0h_D0gammaHist", 1, 0, 1);
  Bu2Dst0h_D0gammaHist->SetLineColor(kBlue);
  Bu2Dst0h_D0gammaHist->SetLineStyle(kDashed);
  Bu2Dst0h_D0gammaHist->SetLineWidth(2);

  auto misId_Bu2Dst0h_D0gammaHist = std::make_unique<TH1D>(
      ("misId_Bu2Dst0h_D0gammaHist" +
       ComposeName(id, mass, neutral, bachelor, daughters, charge))
          .c_str(),
      "misId_Bu2Dst0h_D0gammaHist", 1, 0, 1);
  misId_Bu2Dst0h_D0gammaHist->SetLineColor(kMagenta);
  misId_Bu2Dst0h_D0gammaHist->SetLineStyle(kDashed);
  misId_Bu2Dst0h_D0gammaHist->SetLineWidth(2);

  auto Bu2Dst0h_D0pi0Hist = std::make_unique<TH1D>(
      ("Bu2Dst0h_D0pi0Hist" +
       ComposeName(id, mass, neutral, bachelor, daughters, charge))
          .c_str(),
      "Bu2Dst0h_D0pi0Hist", 1, 0, 1);
  Bu2Dst0h_D0pi0Hist->SetLineColor(kOrange);
  Bu2Dst0h_D0pi0Hist->SetLineStyle(kDashed);
  Bu2Dst0h_D0pi0Hist->SetLineWidth(2);

  auto MisRecHist = std::make_unique<TH1D>(
      ("MisRecHist" +
       ComposeName(id, mass, neutral, bachelor, daughters, charge))
          .c_str(),
      "MisRecHist", 1, 0, 1);
  MisRecHist->SetLineColor(kRed);
  MisRecHist->SetLineStyle(kDashed);
  MisRecHist->SetLineWidth(2);

  auto Bu2D0hHist = std::make_unique<TH1D>(
      ("Bu2D0hHist" +
       ComposeName(id, mass, neutral, bachelor, daughters, charge))
          .c_str(),
      "Bu2D0hHist", 1, 0, 1);
  Bu2D0hHist->SetLineColor(kGreen);
  Bu2D0hHist->SetLineStyle(kDashed);
  Bu2D0hHist->SetLineWidth(2);

  auto blankHist = std::make_unique<TH1D>(
      ("blankHist" +
       ComposeName(id, mass, neutral, bachelor, daughters, charge))
          .c_str(),
      "blankHist", 1, 0, 1);
  blankHist->SetLineColor(kWhite);
  blankHist->SetLineWidth(2);

  std::stringstream Bu2Dst0h_D0gammaLegend;
  Bu2Dst0h_D0gammaLegend
      << "B^{" + EnumToLabel(charge) +
             "}#rightarrow#font[132]{[}#font[132]{[}" +
             EnumToLabel(daughters, charge) +
             "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{0}*}" +
             EnumToLabel(bachelor) + "^{" + EnumToLabel(charge) + "}";
  std::stringstream misId_Bu2Dst0h_D0gammaLegend;
  // SWAP BACH LABEL
  misId_Bu2Dst0h_D0gammaLegend
      << "B^{" + EnumToLabel(charge) +
             "}#rightarrow#font[132]{[}#font[132]{[}" +
             EnumToLabel(daughters, charge) +
             "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{0}*}" +
             EnumToLabel(bachelor) + "^{" + EnumToLabel(charge) + "}";
  std::stringstream Bu2Dst0h_D0pi0Legend;
  Bu2Dst0h_D0pi0Legend
      << "B^{" + EnumToLabel(charge) +
             "}#rightarrow#font[132]{[}#font[132]{[}" +
             EnumToLabel(daughters, charge) +
             "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{0}*}" +
             EnumToLabel(bachelor) + "^{" + EnumToLabel(charge) + "}";
  std::stringstream MisRecLegend;
  MisRecLegend << "Mis-Reconstructed Bkg";
  std::stringstream Bu2D0hLegend;
  Bu2D0hLegend << "B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}" +
                      EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}" +
                      EnumToLabel(bachelor) + "^{" + EnumToLabel(charge) + "}";

  legend.SetLineColor(kWhite);
  legend.AddEntry(Bu2Dst0h_D0gammaHist.get(),
                  Bu2Dst0h_D0gammaLegend.str().c_str(), "l");
  legend.AddEntry(misId_Bu2Dst0h_D0gammaHist.get(),
                  misId_Bu2Dst0h_D0gammaLegend.str().c_str(), "l");
  legend.AddEntry(Bu2Dst0h_D0pi0Hist.get(), Bu2Dst0h_D0pi0Legend.str().c_str(),
                  "l");
  legend.AddEntry(MisRecHist.get(), MisRecLegend.str().c_str(), "l");
  legend.AddEntry(Bu2D0hHist.get(), Bu2D0hLegend.str().c_str(), "l");

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

  if (mass == Mass::delta) {
    PlotComponent(config.deltaMass(), pdf, fullDataSet, simPdf, categories,
                  legend, lumiLegend, outputDir, fitBool, config);
  } else {
    PlotComponent(config.buDeltaMass(), pdf, fullDataSet, simPdf, categories,
                  legend, lumiLegend, outputDir, fitBool, config);
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
  std::string fileLabel;
  if (config.fit1D() == false) {
    fileLabel = std::to_string(config.deltaLow()) + "_" +
                std::to_string(config.deltaHigh()) + "_" +
                std::to_string(config.buDeltaLow()) + "_" +
                std::to_string(config.buDeltaHigh());
  } else {
    fileLabel = std::to_string(config.deltaLow()) + "_" +
                std::to_string(config.deltaHigh());
  }
  corrCanvas.SaveAs(
      (outputDir + "/plots/CorrelationMatrix_" + fileLabel + ".pdf").c_str());
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
  for (auto &n : neutralVec) {
    for (auto &c : chargeVec) {
      switch (n) {
        case Neutral::gamma:
          switch (c) {
            case Charge::total:
              pdfs.emplace_back(
                  &Pdf<Mass::buDelta, Neutral::gamma, Bachelor::pi,
                       Daughters::kpi, Charge::total>::Get(id));
              pdfs.emplace_back(&Pdf<Mass::buDelta, Neutral::gamma, Bachelor::k,
                                     Daughters::kpi, Charge::total>::Get(id));
              // Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, runType>::Get()
              // .AssignMissIdYields();
              // Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, runType>::Get()
              //     .CreateRooAddPdf();
              // Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, runType>::Get()
              //     .AssignMissIdYields();
              // Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, runType>::Get()
              //     .CreateRooAddPdf();
              if (config.fit1D() == false) {
                pdfs.emplace_back(
                    &Pdf<Mass::delta, Neutral::gamma, Bachelor::pi,
                         Daughters::kpi, Charge::total>::Get(id));
                pdfs.emplace_back(&Pdf<Mass::delta, Neutral::gamma, Bachelor::k,
                                       Daughters::kpi, Charge::total>::Get(id));
              }
              break;
            case Charge::plus:
              pdfs.emplace_back(
                  &Pdf<Mass::buDelta, Neutral::gamma, Bachelor::pi,
                       Daughters::kpi, Charge::plus>::Get(id));
              pdfs.emplace_back(&Pdf<Mass::buDelta, Neutral::gamma, Bachelor::k,
                                     Daughters::kpi, Charge::plus>::Get(id));
              if (config.fit1D() == false) {
                pdfs.emplace_back(
                    &Pdf<Mass::delta, Neutral::gamma, Bachelor::pi,
                         Daughters::kpi, Charge::plus>::Get(id));
                pdfs.emplace_back(&Pdf<Mass::delta, Neutral::gamma, Bachelor::k,
                                       Daughters::kpi, Charge::plus>::Get(id));
              }
              break;
            case Charge::minus:
              pdfs.emplace_back(
                  &Pdf<Mass::buDelta, Neutral::gamma, Bachelor::pi,
                       Daughters::kpi, Charge::minus>::Get(id));
              pdfs.emplace_back(&Pdf<Mass::buDelta, Neutral::gamma, Bachelor::k,
                                     Daughters::kpi, Charge::minus>::Get(id));
              if (config.fit1D() == false) {
                pdfs.emplace_back(
                    &Pdf<Mass::delta, Neutral::gamma, Bachelor::pi,
                         Daughters::kpi, Charge::minus>::Get(id));
                pdfs.emplace_back(&Pdf<Mass::delta, Neutral::gamma, Bachelor::k,
                                       Daughters::kpi, Charge::minus>::Get(id));
              }
              break;
          }
          break;
        case Neutral::pi0:
          switch (c) {
            case Charge::total:
              pdfs.emplace_back(&Pdf<Mass::buDelta, Neutral::pi0, Bachelor::pi,
                                     Daughters::kpi, Charge::total>::Get(id));
              pdfs.emplace_back(&Pdf<Mass::buDelta, Neutral::pi0, Bachelor::k,
                                     Daughters::kpi, Charge::total>::Get(id));
              if (config.fit1D() == false) {
                pdfs.emplace_back(&Pdf<Mass::delta, Neutral::pi0, Bachelor::pi,
                                       Daughters::kpi, Charge::total>::Get(id));
                pdfs.emplace_back(&Pdf<Mass::delta, Neutral::pi0, Bachelor::k,
                                       Daughters::kpi, Charge::total>::Get(id));
              }
              break;
            case Charge::plus:
              pdfs.emplace_back(&Pdf<Mass::buDelta, Neutral::pi0, Bachelor::pi,
                                     Daughters::kpi, Charge::plus>::Get(id));
              pdfs.emplace_back(&Pdf<Mass::buDelta, Neutral::pi0, Bachelor::k,
                                     Daughters::kpi, Charge::plus>::Get(id));
              if (config.fit1D() == false) {
                pdfs.emplace_back(&Pdf<Mass::delta, Neutral::pi0, Bachelor::pi,
                                       Daughters::kpi, Charge::plus>::Get(id));
                pdfs.emplace_back(&Pdf<Mass::delta, Neutral::pi0, Bachelor::k,
                                       Daughters::kpi, Charge::plus>::Get(id));
              }
              break;
            case Charge::minus:
              pdfs.emplace_back(&Pdf<Mass::buDelta, Neutral::pi0, Bachelor::pi,
                                     Daughters::kpi, Charge::minus>::Get(id));
              pdfs.emplace_back(&Pdf<Mass::buDelta, Neutral::pi0, Bachelor::k,
                                     Daughters::kpi, Charge::minus>::Get(id));
              if (config.fit1D() == false) {
                pdfs.emplace_back(&Pdf<Mass::delta, Neutral::pi0, Bachelor::pi,
                                       Daughters::kpi, Charge::minus>::Get(id));
                pdfs.emplace_back(&Pdf<Mass::delta, Neutral::pi0, Bachelor::k,
                                       Daughters::kpi, Charge::minus>::Get(id));
              }
              break;
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

// Function we use to do the toy study - run many toys and extract pulls for
// each mass of interest
void RunToys(std::unique_ptr<RooSimultaneous> &simPdf,
             std::unique_ptr<RooFitResult> &dataFitResult,
             Configuration &config, Configuration::Categories &categories,
             std::vector<Neutral> const &neutralVec,
             std::vector<Daughters> const &daughtersVec,
             std::vector<Charge> const &chargeVec, std::string const &outputDir,
             int nToys, bool fitBool) {
  // Start from 1 as id = 0 is data fit params
  for (int id = 1; id < nToys + 1; ++id) {
    std::cout << "\n\n -------------------------- Running toy #" << id
              << " -------------------------- \n\n";
    // Setting the random seed to 0 is a special case which generates a
    // different seed every time you run. Setting the seed to an integer
    // generates toys in a replicable way, in case you need to debug
    // something.

    auto p = MakeSimultaneousPdf(id, config, categories, neutralVec,
                                 daughtersVec, chargeVec);
    if (simPdf == nullptr) {
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

    simPdfToFit = std::unique_ptr<RooSimultaneous>(p.first);

    std::shared_ptr<RooFitResult> result;
    if (fitBool == true) {
      result = std::shared_ptr<RooFitResult>(simPdfToFit->fitTo(
          *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
          RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
          RooFit::Offset(true), RooFit::NumCPU(8, 2)));
    }
    if (id == 1) {
      std::string lumiString = "TOY";
      auto pdfs = p.second;
      for (auto &p : pdfs) {
        std::cout << "Plotting " << p->addPdf().GetName() << "\n";
        Plotting1D(id, *p, config, categories, *toyAbsData, *simPdfToFit,
                   outputDir, fitBool, lumiString, result.get());
      }
      if (fitBool == true) {
        PlotCorrelations(result.get(), outputDir, config);
      }
    }

    if (fitBool == true) {
      result->Print("v");
      std::string fileLabel;
      if (config.fit1D() == false) {
        fileLabel = std::to_string(config.deltaLow()) + "_" +
                    std::to_string(config.deltaHigh()) + "_" +
                    std::to_string(config.buDeltaLow()) + "_" +
                    std::to_string(config.buDeltaHigh());
      } else {
        fileLabel = std::to_string(config.deltaLow()) + "_" +
                    std::to_string(config.deltaHigh());
      }
      TFile outputFile(
          (outputDir + "/results/DataResult_" + fileLabel + ".root").c_str(),
          "recreate");

      outputFile.cd();
      result->SetName(("Result_" + std::to_string(randomTag)).c_str());
      result->Write();
      if (dataFitResult != nullptr) {
        dataFitResult->SetName("DataFitResult");
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
  std::vector<Neutral> neutralVec;
  std::vector<Daughters> daughtersVec;
  std::vector<Charge> chargeVec;
  // Still want to load both charges:plus and minus, we just fit with
  // them differently

  bool fitBool = true;
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
    std::string neutralArg("gamma,pi0");
    std::string daughtersArg("kpi,kk,pipi,pik");
    std::string chargeArg("total");
    int toysArg = 0;
    int deltaLowArg = 0;
    int deltaHighArg = 0;
    int buDeltaLowArg = 0;
    int buDeltaHighArg = 0;

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

  Configuration::Categories &categories = Configuration::Get().categories();

  // Raise lower mass boundary in delta mass for pi0 plots
  if (neutralVec.size() == 1 && neutralVec[0] == Neutral::pi0) {
    config.deltaMass().setMin(134);
  }

  // Declare simPDF and result before any if statements so that it can be passed
  // to RunToys no matter what
  std::unique_ptr<RooSimultaneous> simPdf;
  std::unique_ptr<RooFitResult> result;

  if (inputDir != "") {
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
      } else if (y == Year::y2018) {
        lumi += 2.19;
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
                    RooDataSet *reducedInputDataSet_n = nullptr;
                    if (n == Neutral::pi0) {
                      reducedInputDataSet_n =
                          dynamic_cast<RooDataSet *>(inputDataSet->reduce(
                              config.gammaCutString().c_str()));
                    } else {
                      reducedInputDataSet_n = dynamic_cast<RooDataSet *>(
                          inputDataSet->reduce(config.pi0CutString().c_str()));
                    }
                    if (reducedInputDataSet_n == nullptr) {
                      throw std::runtime_error(
                          "Could not reduce input w/ neutral cuts dataset.");
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
                          "Could not reduce input dataset w/ bachelor cuts.");
                    }
                    RooDataSet *reducedInputDataSet_d = nullptr;
                    if (d == Daughters::kpi || d == Daughters::pik) {
                      reducedInputDataSet_d = dynamic_cast<RooDataSet *>(
                          reducedInputDataSet_b->reduce(
                              "(abs(h1_D_ID)==211&&h1_D_PIDK<-2)||(abs(h1_D_ID)"
                              "==321&&h1_D_PIDK>2)&&(abs(h2_D_ID)==211&&h2_D_"
                              "PIDK<-2)||(abs(h2_D_ID)==321&&h2_D_PIDK>2)"));
                    } else if (d == Daughters::kk) {
                      reducedInputDataSet_d = dynamic_cast<RooDataSet *>(
                          reducedInputDataSet_b->reduce(
                              "h1_D_PIDK>2&&h2_D_PIDK>2"));
                    } else {
                      reducedInputDataSet_d = dynamic_cast<RooDataSet *>(
                          reducedInputDataSet_b->reduce(
                              "h1_D_PIDK<-2&&h2_D_PIDK<-2"));
                    }
                    if (reducedInputDataSet_d == nullptr) {
                      throw std::runtime_error(
                          "Could not reduce input dataset w/ daughter cuts.");
                    }
                    // ALSO APPLY BOX CUTS HERE
                    RooDataSet *buDeltaInputDataSet = nullptr;
                    buDeltaInputDataSet = dynamic_cast<RooDataSet *>(
                        reducedInputDataSet_d->reduce(
                            config.buDeltaMass(),
                            ("Delta_M>" + std::to_string(config.deltaLow()) +
                             "&&Delta_M<" + std::to_string(config.deltaHigh()))
                                .c_str()));
                    if (buDeltaInputDataSet == nullptr) {
                      throw std::runtime_error(
                          "Could not reduce dataset down to buDeltaMass.");
                    }
                    // Need to append each year, polarity to dataset at each key
                    // in map, as key labelled by n, b, d, c and must be unique.
                    if (mapCategoryDataset.find(
                            ComposeFittingName(Mass::buDelta, n, b, d, c)) ==
                        mapCategoryDataset.end()) {
                      mapCategoryDataset.insert(std::make_pair(
                          ComposeFittingName(Mass::buDelta, n, b, d, c),
                          buDeltaInputDataSet));
                      std::cout
                          << "Created key-value pair for category " +
                                 ComposeFittingName(Mass::buDelta, n, b, d, c) +
                                 " and corresponding dataset\n";
                    } else {
                      mapCategoryDataset[ComposeFittingName(Mass::buDelta, n, b,
                                                            d, c)]
                          ->append(*buDeltaInputDataSet);
                      std::cout
                          << "Appended dataset to category " +
                                 ComposeFittingName(Mass::buDelta, n, b, d, c) +
                                 "\n";
                    }
                    if (config.fit1D() == false) {
                      RooDataSet *deltaInputDataSet = nullptr;
                      deltaInputDataSet = dynamic_cast<RooDataSet *>(
                          reducedInputDataSet_d->reduce(
                              config.deltaMass(),
                              ("Bu_Delta_M>" +
                               std::to_string(config.buDeltaLow()) +
                               "&&Bu_Delta_M<" +
                               std::to_string(config.buDeltaHigh()))
                                  .c_str()));
                      if (deltaInputDataSet == nullptr) {
                        throw std::runtime_error(
                            "Could not reduce dataset down to deltaMass.");
                      }
                      if (mapCategoryDataset.find(
                              ComposeFittingName(Mass::delta, n, b, d, c)) ==
                          mapCategoryDataset.end()) {
                        mapCategoryDataset.insert(std::make_pair(
                            ComposeFittingName(Mass::delta, n, b, d, c),
                            deltaInputDataSet));
                        std::cout
                            << "Created key-value pair for category " +
                                   ComposeFittingName(Mass::delta, n, b, d, c) +
                                   " and corresponding dataset\n";
                      } else {
                        mapCategoryDataset[ComposeFittingName(Mass::delta, n, b,
                                                              d, c)]
                            ->append(*deltaInputDataSet);
                        std::cout
                            << "Appended dataset to category " +
                                   ComposeFittingName(Mass::delta, n, b, d, c) +
                                   "\n";
                      }
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
    simPdf = std::unique_ptr<RooSimultaneous>(p.first);
    auto pdfs = p.second;

    if (fitBool == true) {
      result = std::unique_ptr<RooFitResult>(
          simPdf->fitTo(*fullAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
                        RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                        RooFit::Offset(true), RooFit::NumCPU(8, 2)));
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
                   fitBool, lumiString, result.get());
      }

      if (fitBool == true) {
        result->Print("v");
        PlotCorrelations(result.get(), outputDir, config);
        // Save RFR of data and efficiencies to calculate observables with
        // corrected errors
        std::string fileLabel;
        if (config.fit1D() == false) {
          fileLabel = std::to_string(config.deltaLow()) + "_" +
                      std::to_string(config.deltaHigh()) + "_" +
                      std::to_string(config.buDeltaLow()) + "_" +
                      std::to_string(config.buDeltaHigh());
        } else {
          fileLabel = std::to_string(config.deltaLow()) + "_" +
                      std::to_string(config.deltaHigh());
        }
        TFile outputFile(
            (outputDir + "/results/DataResult_" + fileLabel + ".root").c_str(),
            "recreate");
        result->Write();
        TTree tree("tree", "");
        for (auto &n : neutralVec) {
          double boxEffSignal, orEffSignal, buDeltaCutEffSignal,
              deltaCutEffSignal;
          int id = 0;
          RooRealVar orEffSignalRRV(
              ("orEffSignalRRV_" + EnumToString(n)).c_str(), "", 1);
          RooRealVar boxEffSignalRRV(
              ("boxEffSignalRRV_" + EnumToString(n)).c_str(), "", 1);
          RooRealVar buDeltaCutEffSignalRRV(
              ("buDeltaCutEffSignalRRV_" + EnumToString(n)).c_str(), "", 1);
          RooRealVar deltaCutEffSignalRRV(
              ("deltaCutEffSignalRRV_" + EnumToString(n)).c_str(), "", 1);
          switch (n) {
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
          tree.Branch(("orEffSignal_" + EnumToString(n)).c_str(), &orEffSignal,
                      ("orEffSignal_" + EnumToString(n) + "/D").c_str());
          tree.Branch(("boxEffSignal_" + EnumToString(n)).c_str(),
                      &boxEffSignal,
                      ("boxEffSignal_" + EnumToString(n) + "/D").c_str());
          tree.Branch(
              ("buDeltaCutEffSignal_" + EnumToString(n)).c_str(),
              &buDeltaCutEffSignal,
              ("buDeltaCutEffSignal_" + EnumToString(n) + "/D").c_str());
          tree.Branch(("deltaCutEffSignal_" + EnumToString(n)).c_str(),
                      &deltaCutEffSignal,
                      ("deltaCutEffSignal_" + EnumToString(n) + "/D").c_str());
          tree.Fill();
        }
        tree.Write();
        outputFile.Write();
        outputFile.Close();
      }
    } else {
      if (simPdf == nullptr) {
        std::cerr << "SimPdf not defined: using MC shapes."
                  << "\n";
      } else {
        result->Print("v");
      }
      RunToys(simPdf, result, config, categories, neutralVec, daughtersVec,
              chargeVec, outputDir, nToys, fitBool);
    }
  } else {
    RunToys(simPdf, result, config, categories, neutralVec, daughtersVec,
            chargeVec, outputDir, nToys, fitBool);
  }

  return 0;
}
