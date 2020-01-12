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
// #include "TMathText.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TLine.h"
#include "TPaveLabel.h"
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
  gStyle->SetTitleSize(0.04, "XY");
  gStyle->SetLabelSize(0.035, "XY");
  gStyle->SetLegendFont(132);
  gStyle->SetLegendTextSize(0.05);
  gStyle->SetTitleOffset(1.0, "X");
  gStyle->SetTitleOffset(1.3, "Y");
  gStyle->SetPadTopMargin(0.03);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.1);
  gStyle->SetPadLeftMargin(0.11);
}

// Function to plot 1D projections - written so that it can be used for both bu
// and delta mass
void PlotComponent(Mass mass, RooRealVar &var, PdfBase &pdf,
                   RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                   TLegend &legend, std::string const &outputDir,
                   Configuration &config,
                   std::map<std::string, Color_t> colorMap) {
  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();
  int id = 0;

  // Stops ROOT print INFO messages
  gErrorIgnoreLevel = kWarning;

  std::unique_ptr<RooPlot> frame(var.frame(RooFit::Title(" ")));

  fullDataSet.plotOn(frame.get(),
                     RooFit::Cut(("fitting==fitting::" +
                                  ComposeFittingName(mass, neutral, bachelor,
                                                     daughters, charge))
                                     .c_str()));

  if (config.noFit() == false) {
    simPdf.plotOn(frame.get(),
                  RooFit::Slice(config.fitting,
                                ComposeFittingName(mass, neutral, bachelor,
                                                   daughters, charge)
                                    .c_str()),
                  RooFit::ProjWData(config.fitting, fullDataSet),
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
          std::stringstream compStream;
          compStream << pdf.pdfBu_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfBu_MisRec().GetName() << ","
                     << pdf.pdfBu_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0pi_D0gamma"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_MisRec().GetName() << ","
                     << pdf.pdfBu_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["MisRecPi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["Bu2D0pi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0pi_D0pi0"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["PartRecRho"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0K_D0gamma"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0K_D0pi0"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        } else {
          std::stringstream compStream;
          compStream << pdf.pdfBu_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_MisRec().GetName() << ","
                     << pdf.pdfBu_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0pi_D0pi0"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_MisRec().GetName() << ","
                     << pdf.pdfBu_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["MisRecPi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["Bu2D0pi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["PartRecRho"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0K_D0pi0"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        }
      } else {
        if (neutral == Neutral::gamma) {
          std::stringstream compStream;
          compStream << pdf.pdfBu_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfBu_MisRec().GetName() << ","
                     << pdf.pdfBu_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_misId_MisRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0K_D0gamma"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_MisRec().GetName() << ","
                     << pdf.pdfBu_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_misId_MisRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["MisRecK"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_misId_MisRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["Bu2D0K"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_misId_MisRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0K_D0pi0"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_misId_MisRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["PartRecKst"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_misId_MisRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0pi_D0gamma"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_misId_MisRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0pi_D0pi0"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_misId_MisRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["MisRecPi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["Bu2D0pi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["PartRecPi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        } else {
          std::stringstream compStream;
          compStream << pdf.pdfBu_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_MisRec().GetName() << ","
                     << pdf.pdfBu_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_misId_MisRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0K_D0pi0"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_MisRec().GetName() << ","
                     << pdf.pdfBu_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_misId_MisRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["MisRecK"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_misId_MisRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["Bu2D0K"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_PartRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_misId_MisRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["PartRecKst"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfBu_misId_MisRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0pi_D0pi0"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_misId_MisRec().GetName() << ","
                     << pdf.pdfBu_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["MisRecPi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["Bu2D0pi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfBu_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["PartRecPi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        }
      }
    } else if (mass == Mass::buDeltaPartial) {
      std::cout << "Plotting " << pdf.addPdfBuPartial().GetName() << "\n";
      if (bachelor == Bachelor::pi) {
        std::stringstream compStream;
        compStream << pdf.pdfBuPartial_Bu2Dst0h_D0pi0().GetName() << ","
                   << pdf.pdfBuPartial_MisRec().GetName() << ","
                   << pdf.pdfBuPartial_Bu2D0h().GetName() << ","
                   << pdf.pdfBuPartial_Bu2Dst0h_D0gamma().GetName() << ","
                   << pdf.pdfBuPartial_PartRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0().GetName();
        simPdf.plotOn(frame.get(),
                      RooFit::Slice(config.fitting,
                                    ComposeFittingName(mass, neutral, bachelor,
                                                       daughters, charge)
                                        .c_str()),
                      RooFit::ProjWData(config.fitting, fullDataSet),
                      RooFit::Components(compStream.str().c_str()),
                      RooFit::DrawOption("F"),
                      RooFit::FillColor(colorMap["Bu2Dst0pi_D0pi0"]),
                      RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        compStream.str(std::string());
        compStream << pdf.pdfBuPartial_MisRec().GetName() << ","
                   << pdf.pdfBuPartial_Bu2D0h().GetName() << ","
                   << pdf.pdfBuPartial_Bu2Dst0h_D0gamma().GetName() << ","
                   << pdf.pdfBuPartial_PartRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0().GetName();
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                config.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(config.fitting, fullDataSet),
            RooFit::Components(compStream.str().c_str()),
            RooFit::DrawOption("F"), RooFit::FillColor(colorMap["MisRecPi"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        compStream.str(std::string());
        compStream << pdf.pdfBuPartial_Bu2D0h().GetName() << ","
                   << pdf.pdfBuPartial_Bu2Dst0h_D0gamma().GetName() << ","
                   << pdf.pdfBuPartial_PartRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0().GetName();
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                config.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(config.fitting, fullDataSet),
            RooFit::Components(compStream.str().c_str()),
            RooFit::DrawOption("F"), RooFit::FillColor(colorMap["Bu2D0pi"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        compStream.str(std::string());
        compStream << pdf.pdfBuPartial_Bu2Dst0h_D0gamma().GetName() << ","
                   << pdf.pdfBuPartial_PartRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0().GetName();
        simPdf.plotOn(frame.get(),
                      RooFit::Slice(config.fitting,
                                    ComposeFittingName(mass, neutral, bachelor,
                                                       daughters, charge)
                                        .c_str()),
                      RooFit::ProjWData(config.fitting, fullDataSet),
                      RooFit::Components(compStream.str().c_str()),
                      RooFit::DrawOption("F"),
                      RooFit::FillColor(colorMap["Bu2Dst0pi_D0gamma"]),
                      RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        compStream.str(std::string());
        compStream << pdf.pdfBuPartial_PartRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0().GetName();
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                config.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(config.fitting, fullDataSet),
            RooFit::Components(compStream.str().c_str()),
            RooFit::DrawOption("F"), RooFit::FillColor(colorMap["PartRecRho"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        compStream.str(std::string());
        compStream << pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0().GetName();
        simPdf.plotOn(frame.get(),
                      RooFit::Slice(config.fitting,
                                    ComposeFittingName(mass, neutral, bachelor,
                                                       daughters, charge)
                                        .c_str()),
                      RooFit::ProjWData(config.fitting, fullDataSet),
                      RooFit::Components(compStream.str().c_str()),
                      RooFit::DrawOption("F"),
                      RooFit::FillColor(colorMap["Bu2Dst0K_D0pi0"]),
                      RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
      } else {
        std::stringstream compStream;
        compStream << pdf.pdfBuPartial_Bu2Dst0h_D0pi0().GetName() << ","
                   << pdf.pdfBuPartial_MisRec().GetName() << ","
                   << pdf.pdfBuPartial_Bu2D0h().GetName() << ","
                   << pdf.pdfBuPartial_Bu2Dst0h_D0gamma().GetName() << ","
                   << pdf.pdfBuPartial_PartRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0().GetName() << ","
                   << pdf.pdfBuPartial_misId_MisRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2D0h().GetName() << ","
                   << pdf.pdfBuPartial_misId_PartRec().GetName();
        simPdf.plotOn(frame.get(),
                      RooFit::Slice(config.fitting,
                                    ComposeFittingName(mass, neutral, bachelor,
                                                       daughters, charge)
                                        .c_str()),
                      RooFit::ProjWData(config.fitting, fullDataSet),
                      RooFit::Components(compStream.str().c_str()),
                      RooFit::DrawOption("F"),
                      RooFit::FillColor(colorMap["Bu2Dst0K_D0pi0"]),
                      RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        compStream.str(std::string());
        compStream << pdf.pdfBuPartial_MisRec().GetName() << ","
                   << pdf.pdfBuPartial_Bu2D0h().GetName() << ","
                   << pdf.pdfBuPartial_Bu2Dst0h_D0gamma().GetName() << ","
                   << pdf.pdfBuPartial_PartRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0().GetName() << ","
                   << pdf.pdfBuPartial_misId_MisRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2D0h().GetName() << ","
                   << pdf.pdfBuPartial_misId_PartRec().GetName();
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                config.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(config.fitting, fullDataSet),
            RooFit::Components(compStream.str().c_str()),
            RooFit::DrawOption("F"), RooFit::FillColor(colorMap["MisRecK"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        compStream.str(std::string());
        compStream << pdf.pdfBuPartial_Bu2D0h().GetName() << ","
                   << pdf.pdfBuPartial_Bu2Dst0h_D0gamma().GetName() << ","
                   << pdf.pdfBuPartial_PartRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0().GetName() << ","
                   << pdf.pdfBuPartial_misId_MisRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2D0h().GetName() << ","
                   << pdf.pdfBuPartial_misId_PartRec().GetName();
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                config.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(config.fitting, fullDataSet),
            RooFit::Components(compStream.str().c_str()),
            RooFit::DrawOption("F"), RooFit::FillColor(colorMap["Bu2D0K"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        compStream.str(std::string());
        compStream << pdf.pdfBuPartial_Bu2Dst0h_D0gamma().GetName() << ","
                   << pdf.pdfBuPartial_PartRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0().GetName() << ","
                   << pdf.pdfBuPartial_misId_MisRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2D0h().GetName() << ","
                   << pdf.pdfBuPartial_misId_PartRec().GetName();
        simPdf.plotOn(frame.get(),
                      RooFit::Slice(config.fitting,
                                    ComposeFittingName(mass, neutral, bachelor,
                                                       daughters, charge)
                                        .c_str()),
                      RooFit::ProjWData(config.fitting, fullDataSet),
                      RooFit::Components(compStream.str().c_str()),
                      RooFit::DrawOption("F"),
                      RooFit::FillColor(colorMap["Bu2Dst0K_D0gamma"]),
                      RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        compStream.str(std::string());
        compStream << pdf.pdfBuPartial_PartRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0().GetName() << ","
                   << pdf.pdfBuPartial_misId_MisRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2D0h().GetName() << ","
                   << pdf.pdfBuPartial_misId_PartRec().GetName();
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                config.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(config.fitting, fullDataSet),
            RooFit::Components(compStream.str().c_str()),
            RooFit::DrawOption("F"), RooFit::FillColor(colorMap["PartRecKst"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        compStream.str(std::string());
        compStream << pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0().GetName() << ","
                   << pdf.pdfBuPartial_misId_MisRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2D0h().GetName() << ","
                   << pdf.pdfBuPartial_misId_PartRec().GetName();
        simPdf.plotOn(frame.get(),
                      RooFit::Slice(config.fitting,
                                    ComposeFittingName(mass, neutral, bachelor,
                                                       daughters, charge)
                                        .c_str()),
                      RooFit::ProjWData(config.fitting, fullDataSet),
                      RooFit::Components(compStream.str().c_str()),
                      RooFit::DrawOption("F"),
                      RooFit::FillColor(colorMap["Bu2Dst0pi_D0pi0"]),
                      RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        compStream.str(std::string());
        compStream << pdf.pdfBuPartial_misId_MisRec().GetName() << ","
                   << pdf.pdfBuPartial_misId_Bu2D0h().GetName() << ","
                   << pdf.pdfBuPartial_misId_PartRec().GetName();
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                config.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(config.fitting, fullDataSet),
            RooFit::Components(compStream.str().c_str()),
            RooFit::DrawOption("F"), RooFit::FillColor(colorMap["MisRecPi"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        compStream.str(std::string());
        compStream << pdf.pdfBuPartial_misId_Bu2D0h().GetName() << ","
                   << pdf.pdfBuPartial_misId_PartRec().GetName();
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                config.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(config.fitting, fullDataSet),
            RooFit::Components(compStream.str().c_str()),
            RooFit::DrawOption("F"), RooFit::FillColor(colorMap["Bu2D0pi"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        compStream.str(std::string());
        compStream << pdf.pdfBuPartial_misId_PartRec().GetName();
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                config.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(config.fitting, fullDataSet),
            RooFit::Components(compStream.str().c_str()),
            RooFit::DrawOption("F"), RooFit::FillColor(colorMap["PartRecPi"]),
            RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
      }
    } else {
      std::cout << "Plotting " << pdf.addPdfDelta().GetName() << "\n";
      if (bachelor == Bachelor::pi) {
        if (neutral == Neutral::gamma) {
          std::stringstream compStream;
          compStream << pdf.pdfDelta_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfDelta_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_MisRec().GetName() << ","
                     << pdf.pdfDelta_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0pi_D0gamma"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_MisRec().GetName() << ","
                     << pdf.pdfDelta_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0pi_D0pi0"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_MisRec().GetName() << ","
                     << pdf.pdfDelta_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["MisRecPi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["Bu2D0pi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["PartRecRho"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0K_D0gamma"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0K_D0pi0"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        } else {
          std::stringstream compStream;
          compStream << pdf.pdfDelta_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_MisRec().GetName() << ","
                     << pdf.pdfDelta_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0pi_D0pi0"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_MisRec().GetName() << ","
                     << pdf.pdfDelta_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["MisRecPi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["Bu2D0pi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["PartRecRho"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0K_D0pi0"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        }
      } else {
        if (neutral == Neutral::gamma) {
          std::stringstream compStream;
          compStream << pdf.pdfDelta_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfDelta_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_MisRec().GetName() << ","
                     << pdf.pdfDelta_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_misId_MisRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0K_D0gamma"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_MisRec().GetName() << ","
                     << pdf.pdfDelta_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_misId_MisRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0K_D0pi0"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_MisRec().GetName() << ","
                     << pdf.pdfDelta_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_misId_MisRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["MisRecK"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_misId_MisRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["Bu2D0K"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_misId_MisRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["PartRecKst"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_misId_MisRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0pi_D0gamma"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_misId_MisRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0pi_D0pi0"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_misId_MisRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["MisRecPi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["Bu2D0pi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["PartRecPi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        } else {
          std::stringstream compStream;
          compStream << pdf.pdfDelta_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_MisRec().GetName() << ","
                     << pdf.pdfDelta_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_misId_MisRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0K_D0pi0"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_MisRec().GetName() << ","
                     << pdf.pdfDelta_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_misId_MisRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["MisRecK"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_misId_MisRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["Bu2D0K"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_PartRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_misId_MisRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["PartRecKst"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName() << ","
                     << pdf.pdfDelta_misId_MisRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"),
              RooFit::FillColor(colorMap["Bu2Dst0pi_D0pi0"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_misId_MisRec().GetName() << ","
                     << pdf.pdfDelta_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["MisRecPi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_misId_Bu2D0h().GetName() << ","
                     << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["Bu2D0pi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
          compStream.str(std::string());
          compStream << pdf.pdfDelta_misId_PartRec().GetName();
          simPdf.plotOn(
              frame.get(),
              RooFit::Slice(
                  config.fitting,
                  ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                      .c_str()),
              RooFit::ProjWData(config.fitting, fullDataSet),
              RooFit::Components(compStream.str().c_str()),
              RooFit::DrawOption("F"), RooFit::FillColor(colorMap["PartRecPi"]),
              RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
        }
      }
    }
    simPdf.plotOn(frame.get(),
                  RooFit::Slice(config.fitting,
                                ComposeFittingName(mass, neutral, bachelor,
                                                   daughters, charge)
                                    .c_str()),
                  RooFit::ProjWData(config.fitting, fullDataSet),
                  RooFit::LineColor(kBlue));
  }

  fullDataSet.plotOn(frame.get(),
                     RooFit::Cut(("fitting==fitting::" +
                                  ComposeFittingName(mass, neutral, bachelor,
                                                     daughters, charge))
                                     .c_str()));

  if (mass == Mass::delta) {
    if (neutral == Neutral::gamma) {
      frame->SetXTitle("m[D^{*0}] - m[D^{0}] (MeV/c^{2})");
    } else {
      frame->SetXTitle(
          "m[D^{*0}] - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
    }
  } else {
    frame->SetXTitle(("m[D^{*0}" + EnumToLabel(bachelor) + "^{" +
                      EnumToLabel(charge) + "}" +
                      "] - m[D^{*0}] + m[D^{*0}]_{PDG} (MeV/c^{2})")
                         .c_str());
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
      "pad2", 0.0, 0.02, 1.0, 0.14, kWhite);
  pad2.Draw();

  TLine zeroLine(var.getMin(), 0, var.getMax(), 0);
  zeroLine.SetLineColor(kRed);
  zeroLine.SetLineStyle(kDashed);

  if (config.noFit() == false) {
    canvas.cd();
    pad2.cd();
    pullFrame->addPlotable(pullHist /* .get() */, "P");
    pullFrame->SetName(("pullFrame_" + ComposeName(id, mass, neutral, bachelor,
                                                   daughters, charge))
                           .c_str());
    pullFrame->SetTitle("");
    pullFrame->SetXTitle(" ");
    pullFrame->GetYaxis()->SetTitle(" ");
    // pullFrame->GetYaxis()->SetTitle("Residuals (#sigma)");
    // pullFrame->SetTitleSize(0.2, "Y");
    // pullFrame->SetTitleOffset(0.1, "Y");
    pullFrame->SetLabelSize(0.15, "Y");
    pullFrame->SetLabelOffset(0.02, "Y");
    pullFrame->SetLabelFont(132, "Y");
    pullFrame->Draw();
    zeroLine.Draw("same");
  }

  canvas.cd();
  pad1.cd();
  if ((bachelor == Bachelor::k && daughters != Daughters::kpi) ||
      daughters == Daughters::pik) {
    frame->SetLabelOffset(50, "Y");
  }
  frame->Draw();

  double blindMin, blindMax;
  if (mass == Mass::delta) {
    blindMin = var.getMin() + 0.1;
    if (neutral == Neutral::gamma) {
      blindMax = 160;
    } else {
      blindMax = 155;
    }
  } else if (mass == Mass::buDelta) {
    blindMin = 5200;
    blindMax = 5350;
  } else {
    blindMin = 5150;
    blindMax = 5400;
  }

  TPaveLabel blindBox(blindMin, -0.11, blindMax, frame->GetMaximum() - 0.1,
                      "#font[12]{Blind}", "");
  blindBox.SetBorderSize(0);
  blindBox.SetTextSize(0.07);
  // blindBox.SetTextAngle(30);
  blindBox.SetTextColor(kRed + 1);
  blindBox.SetFillColor(10);
  if (daughters == Daughters::pik) {
    blindBox.Draw("same");
  }
  legend.Draw("same");

  canvas.Update();
  canvas.SaveAs((outputDir + "/plots/" +
                 ComposeName(id, mass, neutral, bachelor, daughters, charge) +
                 "_" + config.ReturnBoxString() + ".pdf")
                    .c_str());
}

// Plot projections
void Plotting1D(int const id, PdfBase &pdf, Configuration &config,
                RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                std::string const &outputDir, RooFitResult *result) {
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

  TLegend legend(0.72, 0.75, 0.9, 0.85);

  std::string legendString_1 = "#font[22]{LHCb}";
  std::string legendString_2 = "#font[12]{preliminary}";
  if (config.runToy() == true) {
    legend.SetY2(0.83);
    gStyle->SetLegendTextSize(0.06);
    legendString_1 = "#font[132]{TOY}";
    legendString_2 = " ";
  }
  legend.SetBorderSize(0);
  legend.SetMargin(0);
  legend.SetFillStyle(0);
  legend.AddEntry(blankHist.get(), legendString_1.c_str(), "l");
  legend.AddEntry(blankHist.get(), " ", "l");
  legend.AddEntry(blankHist.get(), " ", "l");
  legend.AddEntry(blankHist.get(), legendString_2.c_str(), "l");
  legend.AddEntry(blankHist.get(), " ", "l");
  legend.AddEntry(blankHist.get(), " ", "l");
  legend.AddEntry(blankHist.get(), " ", "l");
  legend.AddEntry(blankHist.get(), " ", "l");
  legend.AddEntry(blankHist.get(), " ", "l");

  std::string decayString = "#font[12]{B^{" + EnumToLabel(charge) +
                            "}#rightarrow#font[132]{[}#font[132]{[}" +
                            EnumToLabel(daughters, charge) +
                            "#font[132]{]}_{D}" + EnumToLabel(neutral) +
                            "#font[132]{]}_{D*}" + EnumToLabel(bachelor) +
                            "^{" + EnumToLabel(charge) + "}}";
  legend.AddEntry(blankHist.get(), decayString.c_str(), "l");

  TList *list = legend.GetListOfPrimitives();
  if (list != nullptr) {
    TObject *entryObj1 = list->At(3);
    if (entryObj1 != nullptr) {
      auto entry1 = dynamic_cast<TLegendEntry *>(entryObj1);
      if (entry1 != nullptr) {
        entry1->SetTextSize(0.035);
      } else {
        throw std::runtime_error(
            "Could not cast entry1 from TObject to TLegendEntry.");
      }
    } else {
      throw std::runtime_error(
          "Could not extract entryObj1 from list in TLegend.");
    }
    TObject *entryObj2 = list->At(9);
    if (entryObj2 != nullptr) {
      auto entry2 = dynamic_cast<TLegendEntry *>(entryObj2);
      if (entry2 != nullptr) {
        entry2->SetTextSize(0.045);
      } else {
        throw std::runtime_error(
            "Could not cast entry2 from TObject to TLegendEntry.");
      }
    } else {
      throw std::runtime_error(
          "Could not extract entryObj2 from list in TLegend.");
    }
  }

  // ------------- Draw Legends -------------- //
  std::map<std::string, Color_t> colorMap;

  colorMap["Bu2Dst0pi_D0gamma"] = kAzure - 4;
  colorMap["Bu2Dst0K_D0gamma"] = kRed + 1;
  colorMap["Bu2Dst0pi_D0pi0"] = kAzure + 3;
  colorMap["Bu2Dst0K_D0pi0"] = kMagenta - 1;
  colorMap["MisRecPi"] = kBlue - 6;
  colorMap["MisRecK"] = kMagenta - 10;
  colorMap["Bu2D0pi"] = kBlue + 4;
  colorMap["Bu2D0K"] = kMagenta - 7;
  colorMap["PartRecRho"] = kGreen + 3;
  colorMap["PartRecKst"] = kRed + 4;

  PlotComponent(Mass::buDelta, config.buDeltaMass(), pdf, fullDataSet, simPdf,
                legend, outputDir, config, colorMap);
  if (config.fitBuPartial() == true) {
    PlotComponent(Mass::buDeltaPartial, config.buDeltaMass(), pdf, fullDataSet,
                  simPdf, legend, outputDir, config, colorMap);
  }
  if (config.fit1D() == false) {
    PlotComponent(Mass::delta, config.deltaMass(), pdf, fullDataSet, simPdf,
                  legend, outputDir, config, colorMap);
  }
}

void PlotCorrelations(RooFitResult *result, std::string const &outputDir,
                      Configuration &config) {
  TCanvas corrCanvas("corrCanvas", "corrCanvas", 1700, 900);
  TH2 *corrHist = result->correlationHist();
  corrHist->SetStats(0);
  corrHist->SetTitle(" ");
  corrCanvas.cd();
  gStyle->SetLabelSize(0.002, "XY");
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
    int const id, Configuration &config,
    std::vector<Daughters> const &daughtersVec,
    std::vector<Charge> const &chargeVec) {
  RooSimultaneous *simPdf = new RooSimultaneous(
      ("simPdf_" + std::to_string(id)).c_str(),
      ("simPdf_" + std::to_string(id)).c_str(), config.fitting);

  std::vector<PdfBase *> pdfs;
  // d is a reference to an element od the vector
  // Downside: don't have direct access to the index
  for (auto &c : chargeVec) {
    switch (config.neutral()) {
      case Neutral::gamma:
        switch (c) {
          case Charge::total:
            for (auto &d : daughtersVec) {
              switch (d) {
                case Daughters::kpi:
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                           Charge::total>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
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
                  if (config.fitBuPartial() == true) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                        Charge::total>::Get(id)
                        .CreateBuPartialAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                        Charge::total>::Get(id)
                        .CreateBuPartialAddPdf();
                  }
                  if (config.fit1D() == false) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                        Charge::total>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                        Charge::total>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::kk:
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                           Charge::total>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                           Charge::total>::Get(id));
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                      Charge::total>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                      Charge::total>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                      Charge::total>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                      Charge::total>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fitBuPartial() == true) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                        Charge::total>::Get(id)
                        .CreateBuPartialAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                        Charge::total>::Get(id)
                        .CreateBuPartialAddPdf();
                  }
                  if (config.fit1D() == false) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                        Charge::total>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                        Charge::total>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::pipi:
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                           Charge::total>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                           Charge::total>::Get(id));
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                      Charge::total>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                      Charge::total>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                      Charge::total>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                      Charge::total>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fitBuPartial() == true) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                        Charge::total>::Get(id)
                        .CreateBuPartialAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                        Charge::total>::Get(id)
                        .CreateBuPartialAddPdf();
                  }
                  if (config.fit1D() == false) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                        Charge::total>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                        Charge::total>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::pik:
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                           Charge::total>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                           Charge::total>::Get(id));
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                      Charge::total>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                      Charge::total>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                      Charge::total>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                      Charge::total>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fitBuPartial() == true) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                        Charge::total>::Get(id)
                        .CreateBuPartialAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                        Charge::total>::Get(id)
                        .CreateBuPartialAddPdf();
                  }
                  if (config.fit1D() == false) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                        Charge::total>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                        Charge::total>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
              }
            }
            break;
          case Charge::plus:
            for (auto &d : daughtersVec) {
              switch (d) {
                case Daughters::kpi:
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                           Charge::plus>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                           Charge::plus>::Get(id));
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                      Charge::plus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                      Charge::plus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                      Charge::plus>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                      Charge::plus>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fitBuPartial() == true) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                        Charge::plus>::Get(id)
                        .CreateBuPartialAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                        Charge::plus>::Get(id)
                        .CreateBuPartialAddPdf();
                  }
                  if (config.fit1D() == false) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                        Charge::plus>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                        Charge::plus>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::kk:
                  pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                         Daughters::kk, Charge::plus>::Get(id));
                  pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k,
                                         Daughters::kk, Charge::plus>::Get(id));
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                      Charge::plus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                      Charge::plus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                      Charge::plus>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                      Charge::plus>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fitBuPartial() == true) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                        Charge::plus>::Get(id)
                        .CreateBuPartialAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                        Charge::plus>::Get(id)
                        .CreateBuPartialAddPdf();
                  }
                  if (config.fit1D() == false) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                        Charge::plus>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                        Charge::plus>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::pipi:
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                           Charge::plus>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                           Charge::plus>::Get(id));
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                      Charge::plus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                      Charge::plus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                      Charge::plus>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                      Charge::plus>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fitBuPartial() == true) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                        Charge::plus>::Get(id)
                        .CreateBuPartialAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                        Charge::plus>::Get(id)
                        .CreateBuPartialAddPdf();
                  }
                  if (config.fit1D() == false) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                        Charge::plus>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                        Charge::plus>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::pik:
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                           Charge::plus>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                           Charge::plus>::Get(id));
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                      Charge::plus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                      Charge::plus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                      Charge::plus>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                      Charge::plus>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fitBuPartial() == true) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                        Charge::plus>::Get(id)
                        .CreateBuPartialAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                        Charge::plus>::Get(id)
                        .CreateBuPartialAddPdf();
                  }
                  if (config.fit1D() == false) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                        Charge::plus>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                        Charge::plus>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
              }
            }
            break;
          case Charge::minus:
            for (auto &d : daughtersVec) {
              switch (d) {
                case Daughters::kpi:
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                           Charge::minus>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
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
                  if (config.fitBuPartial() == true) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                        Charge::minus>::Get(id)
                        .CreateBuPartialAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                        Charge::minus>::Get(id)
                        .CreateBuPartialAddPdf();
                  }
                  if (config.fit1D() == false) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                        Charge::minus>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                        Charge::minus>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::kk:
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                           Charge::minus>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                           Charge::minus>::Get(id));
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                      Charge::minus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                      Charge::minus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                      Charge::minus>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                      Charge::minus>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fitBuPartial() == true) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                        Charge::minus>::Get(id)
                        .CreateBuPartialAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                        Charge::minus>::Get(id)
                        .CreateBuPartialAddPdf();
                  }
                  if (config.fit1D() == false) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                        Charge::minus>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                        Charge::minus>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::pipi:
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                           Charge::minus>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                           Charge::minus>::Get(id));
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                      Charge::minus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                      Charge::minus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                      Charge::minus>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                      Charge::minus>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fitBuPartial() == true) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                        Charge::minus>::Get(id)
                        .CreateBuPartialAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                        Charge::minus>::Get(id)
                        .CreateBuPartialAddPdf();
                  }
                  if (config.fit1D() == false) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                        Charge::minus>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                        Charge::minus>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::pik:
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                           Charge::minus>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                           Charge::minus>::Get(id));
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                      Charge::minus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                      Charge::minus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                      Charge::minus>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                      Charge::minus>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fitBuPartial() == true) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                        Charge::minus>::Get(id)
                        .CreateBuPartialAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                        Charge::minus>::Get(id)
                        .CreateBuPartialAddPdf();
                  }
                  if (config.fit1D() == false) {
                    Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                        Charge::minus>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                        Charge::minus>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
              }
            }
            break;
        }
        break;
      case Neutral::pi0:
        switch (c) {
          case Charge::total:
            for (auto &d : daughtersVec) {
              switch (d) {
                case Daughters::kpi:
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                           Charge::total>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                           Charge::total>::Get(id));
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                      Charge::total>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                      Charge::total>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                      Charge::total>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                      Charge::total>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fit1D() == false) {
                    Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                        Charge::total>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                        Charge::total>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::kk:
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                           Charge::total>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                           Charge::total>::Get(id));
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                      Charge::total>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                      Charge::total>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                      Charge::total>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                      Charge::total>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fit1D() == false) {
                    Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                        Charge::total>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                        Charge::total>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::pipi:
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                           Charge::total>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                           Charge::total>::Get(id));
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                      Charge::total>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                      Charge::total>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                      Charge::total>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                      Charge::total>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fit1D() == false) {
                    Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                        Charge::total>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                        Charge::total>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::pik:
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                           Charge::total>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                           Charge::total>::Get(id));
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                      Charge::total>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                      Charge::total>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                      Charge::total>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                      Charge::total>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fit1D() == false) {
                    Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                        Charge::total>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                        Charge::total>::Get(id)
                        .CreateDeltaAddPdf();
                  }
              }
            }
            break;
          case Charge::plus:
            for (auto &d : daughtersVec) {
              switch (d) {
                case Daughters::kpi:
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                           Charge::plus>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                           Charge::plus>::Get(id));
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                      Charge::plus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                      Charge::plus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                      Charge::plus>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                      Charge::plus>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fit1D() == false) {
                    Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                        Charge::plus>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                        Charge::plus>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::kk:
                  pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi,
                                         Daughters::kk, Charge::plus>::Get(id));
                  pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k,
                                         Daughters::kk, Charge::plus>::Get(id));
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                      Charge::plus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                      Charge::plus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                      Charge::plus>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                      Charge::plus>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fit1D() == false) {
                    Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                        Charge::plus>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                        Charge::plus>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::pipi:
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                           Charge::plus>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                           Charge::plus>::Get(id));
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                      Charge::plus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                      Charge::plus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                      Charge::plus>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                      Charge::plus>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fit1D() == false) {
                    Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                        Charge::plus>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                        Charge::plus>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::pik:
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                           Charge::plus>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                           Charge::plus>::Get(id));
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                      Charge::plus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                      Charge::plus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                      Charge::plus>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                      Charge::plus>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fit1D() == false) {
                    Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                        Charge::plus>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                        Charge::plus>::Get(id)
                        .CreateDeltaAddPdf();
                  }
              }
            }
            break;
          case Charge::minus:
            for (auto &d : daughtersVec) {
              switch (d) {
                case Daughters::kpi:
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                           Charge::minus>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                           Charge::minus>::Get(id));
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                      Charge::minus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                      Charge::minus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                      Charge::minus>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                      Charge::minus>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fit1D() == false) {
                    Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                        Charge::minus>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                        Charge::minus>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::kk:
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                           Charge::minus>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                           Charge::minus>::Get(id));
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                      Charge::minus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                      Charge::minus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                      Charge::minus>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                      Charge::minus>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fit1D() == false) {
                    Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                        Charge::minus>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                        Charge::minus>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::pipi:
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                           Charge::minus>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                           Charge::minus>::Get(id));
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                      Charge::minus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                      Charge::minus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                      Charge::minus>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                      Charge::minus>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fit1D() == false) {
                    Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                        Charge::minus>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                        Charge::minus>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
                case Daughters::pik:
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                           Charge::minus>::Get(id));
                  pdfs.emplace_back(
                      &Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                           Charge::minus>::Get(id));
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                      Charge::minus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                      Charge::minus>::Get(id)
                      .AssignMisIdYields();
                  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                      Charge::minus>::Get(id)
                      .CreateBuAddPdf();
                  Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                      Charge::minus>::Get(id)
                      .CreateBuAddPdf();
                  if (config.fit1D() == false) {
                    Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                        Charge::minus>::Get(id)
                        .CreateDeltaAddPdf();
                    Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                        Charge::minus>::Get(id)
                        .CreateDeltaAddPdf();
                  }
                  break;
              }
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

  if (config.fitBuPartial() == true) {
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
        "m[D^{*0}] - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
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
  if (config.fitBuPartial() == true) {
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
               Configuration &config,
               std::vector<Daughters> const &daughtersVec,
               std::vector<Charge> const &chargeVec,
               std::string const &outputDir, int id) {
  std::cout << "\n\n -------------------------- Running toy #" << id
            << " -------------------------- \n\n";
  auto p = MakeSimultaneousPdf(id, config, daughtersVec, chargeVec);
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
                        RooFit::Index(config.fitting),
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
                     RooFit::Index(config.fitting),
                     RooFit::Import(mapFittingDataSet));

  std::cout << "\n\n\n";
  toyDataSet.Print();
  dataSet.Print();
  std::cout << "\n\n\n";

  // if (id == 1) {
  //   for (auto &p : pdfs) {
  //     std::string toyLabel = "toy";
  //     std::string dataLabel = "data";
  //     Plotting2D(dataSet, id, *p, config, outputDir, dataLabel);
  //     Plotting2D(toyDataSet, id, *p, config, outputDir, toyLabel);
  //   }
  //   for (auto &p : pdfs) {
  //     Plotting1D(id, *p, config, *toyAbsData, *simPdf, outputDir,
  //                toyFitResult.get());
  //   }
  //   if (config.noFit() == false) {
  //     PlotCorrelations(toyFitResult.get(), outputDir, config);
  //   }
  // }
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
                Configuration &config,
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
      auto p = MakeSimultaneousPdf(tmpId, config, daughtersVec, chargeVec);
      simPdf = std::unique_ptr<RooSimultaneous>(p.first);
    }

    RooRandom::randomGenerator()->SetSeed(0);
    TRandom3 random(0);
    double randomTag = random.Rndm();

    double nEvtsPerToy = simPdf->expectedEvents(config.fitting);
    std::unique_ptr<RooDataSet> toyDataSet;
    if (config.fit1D() == false) {
      toyDataSet = std::unique_ptr<RooDataSet>(simPdf->generate(
          RooArgSet(config.buDeltaMass(), config.deltaMass(), config.fitting),
          nEvtsPerToy));
    } else {
      toyDataSet = std::unique_ptr<RooDataSet>(simPdf->generate(
          RooArgSet(config.buDeltaMass(), config.fitting), nEvtsPerToy));
    }
    toyDataSet->SetName(("toyDataSet_" + std::to_string(id)).c_str());
    auto toyDataHist = std::unique_ptr<RooDataHist>(
        toyDataSet->binnedClone(("toyDataHist_" + std::to_string(id)).c_str(),
                                ("toyDataHist" + std::to_string(id)).c_str()));
    auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

    auto simPdfToFit = std::unique_ptr<RooSimultaneous>(new RooSimultaneous(
        ("simPdfFit_" + std::to_string(id)).c_str(),
        ("simPdfFit_" + std::to_string(id)).c_str(), config.fitting));

    auto p = MakeSimultaneousPdf(id, config, daughtersVec, chargeVec);
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
      auto pdfs = p.second;
      for (auto &p : pdfs) {
        Plotting1D(id, *p, config, *toyAbsData, *simPdfToFit, outputDir,
                   toyFitResult.get());
      }
      if (config.noFit() == false) {
        PlotCorrelations(toyFitResult.get(), outputDir, config);
      }
      NeutralBachelorVars<Neutral::gamma, Bachelor::pi> npVars(id);
      std::cout << "Gamma, pi:\n"
                << "\tBu2Dst0h_D0gamma:\n";
      std::cout << "\torEff = " << npVars.orEffMisId_Bu2Dst0h_D0gamma().getVal()
                << "\n"
                << "\tbuDeltaCutEff = "
                << npVars.buDeltaCutEffMisId_Bu2Dst0h_D0gamma().getVal() << "\n"
                << "\tdeltaCutEff = "
                << npVars.deltaCutEffMisId_Bu2Dst0h_D0gamma().getVal() << "\n";
      std::cout << "\n\tBu2Dst0h_D0pi0:\n";
      std::cout << "\torEff = " << npVars.orEffMisId_Bu2Dst0h_D0pi0().getVal()
                << "\n"
                << "\tbuDeltaCutEff = "
                << npVars.buDeltaCutEffMisId_Bu2Dst0h_D0pi0().getVal() << "\n"
                << "\tdeltaCutEff = "
                << npVars.deltaCutEffMisId_Bu2Dst0h_D0pi0().getVal() << "\n"
                << "\tdeltaPartialCutEff = "
                << npVars.deltaPartialCutEffMisId_Bu2Dst0h_D0pi0().getVal()
                << "\n";

      NeutralBachelorVars<Neutral::gamma, Bachelor::k> nkVars(id);
      std::cout << "\nGamma, K:\n"
                << "\tBu2Dst0h_D0gamma:\n";
      std::cout << "\torEff = " << nkVars.orEffMisId_Bu2Dst0h_D0gamma().getVal()
                << "\n"
                << "\tbuDeltaCutEff = "
                << nkVars.buDeltaCutEffMisId_Bu2Dst0h_D0gamma().getVal() << "\n"
                << "\tdeltaCutEff = "
                << nkVars.deltaCutEffMisId_Bu2Dst0h_D0gamma().getVal() << "\n";
      std::cout << "\n\tBu2Dst0h_D0pi0:\n";
      std::cout << "\torEff = " << nkVars.orEffMisId_Bu2Dst0h_D0pi0().getVal()
                << "\n"
                << "\tbuDeltaCutEff = "
                << nkVars.buDeltaCutEffMisId_Bu2Dst0h_D0pi0().getVal() << "\n"
                << "\tdeltaCutEff = "
                << nkVars.deltaCutEffMisId_Bu2Dst0h_D0pi0().getVal() << "\n"
                << "\tdeltaPartialCutEff = "
                << nkVars.deltaPartialCutEffMisId_Bu2Dst0h_D0pi0().getVal()
                << "\n";

      for (auto &p : pdfs) {
        std::cout << "\nBachelor = " << EnumToString(p->bachelor()) << "\n";
        if (config.neutral() == Neutral::gamma) {
          std::cout << "\nBu2Dst0h_D0gamma"
                    << ":\n";
          // std::cout << "\tN: " << p->N_Bu2Dst0h_D0gamma().getVal() << "\n";
          std::cout << "\tN_misId: " << p->N_misId_Bu2Dst0h_D0gamma().getVal()
                    << "\n";
          std::cout << "\tN_Bu: " << p->N_Bu_Bu2Dst0h_D0gamma().getVal()
                    << "\n";
          std::cout << "\tN_misId_Bu: "
                    << p->N_Bu_misId_Bu2Dst0h_D0gamma().getVal() << "\n";
          // if (config.fitBuPartial() == true) {
          //   std::cout << "\tN_BuPartial: "
          //             << p->N_BuPartial_Bu2Dst0h_D0gamma().getVal() << "\n";
          // }
          if (config.fit1D() == false) {
            std::cout << "\tN_Delta: " << p->N_Delta_Bu2Dst0h_D0gamma().getVal()
                      << "\n";
            std::cout << "\tN_misId_Delta: "
                      << p->N_Delta_misId_Bu2Dst0h_D0gamma().getVal() << "\n";
          }
        }
        std::cout << "\nBu2Dst0h_D0pi0"
                  << ":\n";
        // std::cout << "\tN: " << p->N_Bu2Dst0h_D0pi0().getVal() << "\n";
        std::cout << "\tN_misId: " << p->N_misId_Bu2Dst0h_D0pi0().getVal()
                  << "\n";
        std::cout << "\tN_Bu: " << p->N_Bu_Bu2Dst0h_D0pi0().getVal() << "\n";
        std::cout << "\tN_misId_Bu: " << p->N_Bu_misId_Bu2Dst0h_D0pi0().getVal()
                  << "\n";
        if (config.fitBuPartial() == true) {
          std::cout << "\tN_BuPartial: "
                    << p->N_BuPartial_Bu2Dst0h_D0pi0().getVal() << "\n";
          std::cout << "\tN_misId_BuPartial: "
                    << p->N_BuPartial_misId_Bu2Dst0h_D0pi0().getVal() << "\n";
        }
        if (config.fit1D() == false) {
          std::cout << "\tN_Delta: " << p->N_Delta_Bu2Dst0h_D0pi0().getVal()
                    << "\n";
          std::cout << "\tN_misId_Delta: "
                    << p->N_Delta_misId_Bu2Dst0h_D0pi0().getVal() << "\n";
        }
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

void SaveEffToTree(Configuration &config, TFile &outputFile, TTree &tree,
                   Mode mode) {
  double boxEff, orEff, buDeltaCutEff, deltaCutEff;
  {
    RooRealVar orEffRRV("orEffRRV", "", 1);
    RooRealVar boxEffRRV("boxEffRRV", "", 1);
    RooRealVar buDeltaCutEffRRV("buDeltaCutEffRRV", "", 1);
    RooRealVar deltaCutEffRRV("deltaCutEffRRV", "", 1);

    if (config.fitBuPartial() == true) {
      RooRealVar boxPartialEffRRV("boxPartialEffRRV", "", 1);
      RooRealVar deltaPartialCutEffRRV("deltaPartialCutEffRRV", "", 1);
      config.SetEfficiencies(mode, Bachelor::pi, orEffRRV, boxEffRRV,
                             boxPartialEffRRV, buDeltaCutEffRRV, deltaCutEffRRV,
                             deltaPartialCutEffRRV, false);
      double boxPartialEff = boxPartialEffRRV.getVal();
      double deltaPartialCutEff = deltaPartialCutEffRRV.getVal();
      tree.Branch(("boxPartialEff_" + EnumToString(mode)).c_str(),
                  &boxPartialEff,
                  ("boxPartialEff_" + EnumToString(mode) + "/D").c_str());
      tree.Branch(("deltaPartialCutEff_" + EnumToString(mode)).c_str(),
                  &deltaPartialCutEff,
                  ("deltaPartialCutEff_" + EnumToString(mode) + "/D").c_str());
      tree.Fill();
    } else {
      config.SetEfficiencies(mode, Bachelor::pi, orEffRRV, boxEffRRV,
                             buDeltaCutEffRRV, deltaCutEffRRV, false);
    }

    orEff = orEffRRV.getVal();
    boxEff = boxEffRRV.getVal();
    buDeltaCutEff = buDeltaCutEffRRV.getVal();
    deltaCutEff = deltaCutEffRRV.getVal();
  }

  outputFile.cd();
  tree.Branch(("orEff_" + EnumToString(mode)).c_str(), &orEff,
              ("orEff_" + EnumToString(mode) + "/D").c_str());
  tree.Branch(("boxEff_" + EnumToString(mode)).c_str(), &boxEff,
              ("boxEff_" + EnumToString(mode) + "/D").c_str());
  tree.Branch(("buDeltaCutEff_" + EnumToString(mode)).c_str(), &buDeltaCutEff,
              ("buDeltaCutEff_" + EnumToString(mode) + "/D").c_str());
  tree.Branch(("deltaCutEff_" + EnumToString(mode)).c_str(), &deltaCutEff,
              ("deltaCutEff_" + EnumToString(mode) + "/D").c_str());
  tree.Fill();
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
    float deltaPartialLowArg = 0.0;
    float deltaPartialHighArg = 0.0;
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
      std::cout
          << "Give box dimensions:\n"
          << "    -dl=#, -dh=#, -bl=#, -bh=# (-dpl=#, -dph=# for gamma mode)\n";
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
      if (!args("toys", toysArg)) {
        std::cout << "Running data fit.\n";
      } else {
        nToys = toysArg;
        config.runToy() = true;
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
      if (chargeVec.size() > 1) {
        config.splitByCharge() = true;
      }

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
      if (config.neutral() == Neutral::gamma) {
        if (!args("dpl", deltaPartialLowArg)) {
          std::cout << "Only fitting Bu mass for gamma delta mass window.\n";
        } else {
          config.SetDeltaPartialLow(deltaPartialLowArg);
          config.fitBuPartial() = true;
          std::cout << "Set value for lower deltaPartial mass box threshold: " +
                           std::to_string(config.deltaPartialLow()) + "\n";
          if (!args("dph", deltaPartialHighArg)) {
            std::cout << "Only fitting Bu mass for gamma delta mass window.\n";
          } else {
            config.SetDeltaPartialHigh(deltaPartialHighArg);
            config.fitBuPartial() = true;
            std::cout
                << "Set value for upper deltaPartial mass box threshold: " +
                       std::to_string(config.deltaPartialHigh()) + "\n";
          }
        }
      }
    }
  }

  if (daughtersVec.size() > 1 && config.blindFit() == false &&
      config.noFit() == false) {
    std::cerr
        << "\n\n !!!!!! Cannot run unblinded fit for signal modes !!!!!! \n\n";
    return 1;
  }

  // Raise lower mass boundary in delta mass for pi0 plots
  if (config.neutral() == Neutral::pi0) {
    config.deltaMass().setMin(136);
    config.deltaMass().setBins(54);
    config.initYieldFAVSignal() = 1.3346e+04;
  }

  // Define categories AFTER neutral and SplitByCharge have been set in
  // Configuration
  config.DefineCategories();

  // Declare simPDF and result before any if statements so that it can be passed
  // to RunD1DToys no matter what
  std::unique_ptr<RooSimultaneous> simPdf;
  std::unique_ptr<RooFitResult> dataFitResult;

  if (inputDir != "") {
    std::map<std::string, RooDataSet *> mapDataLabelDataSet;

    // Add up lumi in order to convert into string to go on plots
    // double lumi = 0;
    // double lumiErr = 0;

    // Loop over all options in
    // order to extract correct roodataSets.
    for (auto &y : yearVec) {
      // if (y == Year::y2011) {
      //   lumi += 0.98;
      //   lumiErr += 0.02;
      // } else if (y == Year::y2012) {
      //   lumi += 1.99;
      //   lumiErr += 0.02;
      // } else if (y == Year::y2015) {
      //   lumi += 0.28;
      //   lumiErr += 0.01;
      // } else if (y == Year::y2016) {
      //   lumi += 1.65;
      // } else if (y == Year::y2017) {
      //   lumi += 1.7;
      // } else if (y == Year::y2018) {
      //   lumi += 2.19;
      // }
      for (auto &p : polarityVec) {
        for (auto &b : bachelorVec) {
          for (auto &d : daughtersVec) {
            for (auto &c : chargeVec) {
              std::string dsFile =
                  inputDir + "/" +
                  ComposeFilename(y, p, b, config.neutral(), d, c) + ".root";
              std::cout << "Extracting RooDataSet from file: \n";

              if (!fexists(dsFile)) {
                std::cerr << dsFile << " does not exist.\n";
                return 1;
              } else {
                std::cout << dsFile << " exists.\n";
                TFile in(dsFile.c_str(), "READ");
                RooDataSet *inputDataSet;
                gDirectory->GetObject("inputDataSet", inputDataSet);
                if (inputDataSet == nullptr) {
                  throw std::runtime_error("Data set does not exist.\n");
                } else {
                  std::cout << "inputDataSet extracted: \n";
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
                        "Could not reduce input w/ neutral cuts dataSet.\n");
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
                        "Could not reduce input dataSet w/ bachelor cuts.\n");
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
                        "Could not reduce input dataSet w/ daughter cuts.\n");
                  }
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
    if (config.runToy() == true) {
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
        Run2DToys(toyResultFile, mapDataLabelDataSet, config, daughtersVec,
                  chargeVec, outputDir, id);
        toyFileNames[id - 1] = toyResultFile.GetName();
        toyResultFile.Close();
      }
    }
    // id = 0 for data fit
    int id = 0;
    auto p = MakeSimultaneousPdf(id, config, daughtersVec, chargeVec);
    simPdf = std::unique_ptr<RooSimultaneous>(p.first);
    auto pdfs = p.second;
    // Apply box cuts and split PDF into mass categories too
    std::map<std::string, RooDataSet *> mapFittingDataSet;
    for (auto &p : pdfs) {
      MakeMapFittingDataSet(*p, mapDataLabelDataSet, mapFittingDataSet, config);
    }

    RooDataSet fullDataSet("fullDataSet", "fullDataSet", config.fittingArgSet(),
                           RooFit::Index(config.fitting),
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

    if (config.runToy() == false) {
      // Loop over daughters again to plot correct PDFs
      for (auto &p : pdfs) {
        Plotting1D(id, *p, config, fullDataSet, *simPdf, outputDir,
                   dataFitResult.get());
      }

      if (config.noFit() == false) {
        dataFitResult->Print("v");
        // double pi_pi0, k_pi0, pi_gamma, k_gamma;
        // for (auto &p : pdfs) {
        //   if (p->bachelor() == Bachelor::pi) {
        //     if (config.neutral() == Neutral::gamma) {
        //       pi_gamma = p->N_tot_Bu2Dst0h_D0gamma().getVal();
        //     }
        //     pi_pi0 = p->N_tot_Bu2Dst0h_D0pi0().getVal();
        //   } else {
        //     if (config.neutral() == N_toteutral::gamma) {
        //       k_gamma = p->N_tot_Bu2Dst0h_D0gamma().getVal();
        //     }
        //     k_pi0 = p->N_tot_Bu2Dst0h_D0pi0().getVal();
        //   }
        // }
        // if (config.neutral() == Neutral::gamma) {
        //   std::cout << "R gamma = " << k_gamma / pi_gamma << "\n";
        // }
        // std::cout << "R pi0 = " << k_pi0 / pi_pi0 << "\n";
        // config.deltaMass().setRange("total", 136, 190);
        // RooAbsReal *sigDeltaInt =
        // p->pdfDelta_Bu2Dst0h_D0pi0().createIntegral(
        //     config.deltaMass(), RooFit::NormSet(config.deltaMass()),
        //     RooFit::Range("total"));
        // if (sigDeltaInt == nullptr) {
        //   throw std::runtime_error("Signal could not be integrated.");
        // } else {
        //   double sigYieldVal =
        //       sigDeltaInt->getVal() * p->N_Delta_Bu2Dst0h_D0pi0().getVal();
        //   double sigYieldErr =
        //       sigDeltaInt->getVal() *
        //       p->N_Delta_Bu2Dst0h_D0pi0().getPropagatedError(*dataFitResult);
        //   std::cout << "For deltaMass, pi0 signal yield = " << sigYieldVal
        //             << " ± " << sigYieldErr << "\n";
        // }
        //
        // config.buDeltaMass().setRange("total", 5050, 5500);
        // RooAbsReal *sigBuDeltaInt = p->pdfBu_Bu2Dst0h_D0pi0().createIntegral(
        //     config.buDeltaMass(), RooFit::NormSet(config.buDeltaMass()),
        //     RooFit::Range("total"));
        // if (sigBuDeltaInt == nullptr) {
        //   throw std::runtime_error("Signal could not be integrated.");
        // } else {
        //   double sigYieldVal =
        //       sigBuDeltaInt->getVal() * p->N_Bu_Bu2Dst0h_D0pi0().getVal();
        //   double sigYieldErr =
        //       sigBuDeltaInt->getVal() *
        //       p->N_Bu_Bu2Dst0h_D0pi0().getPropagatedError(*dataFitResult);
        //   std::cout << "For buDeltaMass, pi0 signal yield = " << sigYieldVal
        //             << " ± " << sigYieldErr << "\n";
        // }
        // }
        PlotCorrelations(dataFitResult.get(), outputDir, config);
        // Save RFR of data and efficiencies to calculate observables with
        // corrected errors
        TFile outputFile((outputDir + "/results/DataResult_" +
                          config.ReturnBoxString() + ".root")
                             .c_str(),
                         "recreate");
        dataFitResult->Write();
        TTree tree("tree", "");
        if (config.neutral() == Neutral::pi0 || config.fitBuPartial() == true) {
          SaveEffToTree(config, outputFile, tree, Mode::Bu2Dst0pi_D0pi0);
        }
        if (config.neutral() == Neutral::gamma) {
          SaveEffToTree(config, outputFile, tree, Mode::Bu2Dst0pi_D0gamma);
        }
        outputFile.cd();
        tree.Write();
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
    if (config.runToy() == false) {
      throw std::runtime_error("Must specify input directory to run data fit.");
      return 1;
    }
    std::cout << "Fitting using D1D method\n";
    RunD1DToys(simPdf, dataFitResult, config, daughtersVec, chargeVec,
               outputDir, nToys);
  }
  return 0;
}
