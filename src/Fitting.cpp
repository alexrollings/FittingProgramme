#include "RooAbsBinning.h"
#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooFitResult.h"
#include "RooHist.h"
#include "RooMCStudy.h"
#include "RooPlot.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TLine.h"
#include "TStyle.h"

#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Configuration.h"
#include "DaughtersVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralVars.h"
#include "ParseArguments.h"
#include "Pdf.h"

void Plotting(PdfBase &pdf, std::vector<Charge> const &chargeVec,
              Configuration &config, Configuration::Categories &categories,
              RooAbsData const &fullDataSet, RooSimultaneous const &simPdf) {

  // -------------- Set Style Attributes ------------------

  gStyle->SetTitleFont(132, "XYZ");
  gStyle->SetLabelFont(132, "XYZ");
  gStyle->SetStatFont(132);
  gStyle->SetStatFontSize(0.04);
  gStyle->SetTitleSize(0.08, "Z");
  gStyle->SetTitleSize(0.045, "XY");
  gStyle->SetLabelSize(0.04, "XY");
  gStyle->SetLegendFont(132);
  gStyle->SetTitleOffset(0.85, "X");
  gStyle->SetTitleOffset(0.95, "Y");
  gStyle->SetTitleOffset(0.9, "Z");
  // gStyle->SetLegendTextSize(0.08);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.09);
  gStyle->SetPadLeftMargin(0.1);

  // --------------- create frame ---------------------

  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();

  std::string chargeLabel = EnumToLabel(chargeVec);
  std::string daughtersLabel = EnumToLabel(daughters, chargeVec);
  std::string bachelorLabel = EnumToLabel(bachelor);
  std::string neutralLabel = EnumToLabel(neutral);
  std::string crossFeedLabel = CrossFeedLabel(neutral);
  std::string hstLabel = HstLabel(bachelor);
  std::string missIdLabel = MissIdLabel(bachelor);

  std::unique_ptr<RooPlot> frame(config.buMass().frame(RooFit::Title(
      ("B^{" + chargeLabel + "}#rightarrow#font[132]{[}#font[132]{[}" +
       daughtersLabel + "#font[132]{]}_{D}" + neutralLabel +
       "#font[132]{]}_{D^{*}}" + bachelorLabel + "^{" + chargeLabel + "}")
          .c_str())));

  // --------- Create histogram of data to plot on top of fit ----------
  // Need to plot a reduced data set

  // TH1F *dataHist = (TH1F *)fullDataSet.createHistogram(
  //     "dataHist", config.buMass(), RooFit::Binning(152));
  // dataHist->SetMarkerColor(1);
  // dataHist->SetMarkerStyle(20);
  // dataHist->SetMarkerSize(1);

  // --------------- plot data and pdfs onto frame ---------------------

  fullDataSet.plotOn(frame.get(),
                     RooFit::Cut(("fitting==fitting::" +
                                  ComposeName(neutral, bachelor, daughters))
                                     .c_str()));

  // .get() gets the raw pointer from underneath the smart pointer

  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::LineColor(kBlue));

  // auto hpull = std::unique_ptr<RooHist>(
  //     dynamic_cast<RooHist *>(frame->RooPlot::pullHist()));
  RooHist *hpull = frame->RooPlot::pullHist();

  if (neutral == Neutral::pi0) {
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(categories.fitting,
                      ComposeName(neutral, bachelor, daughters).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.signal()), RooFit::LineStyle(kDashed),
        RooFit::LineColor(kBlue));
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(categories.fitting,
                      ComposeName(neutral, bachelor, daughters).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.crossFeed()), RooFit::LineStyle(kDashed),
        RooFit::LineColor(kRed));
  } else {
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(categories.fitting,
                      ComposeName(neutral, bachelor, daughters).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.signal()), RooFit::LineStyle(kDashed),
        RooFit::LineColor(kRed));
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(categories.fitting,
                      ComposeName(neutral, bachelor, daughters).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.crossFeed()), RooFit::LineStyle(kDashed),
        RooFit::LineColor(kBlue));
  }
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.nonTmSignal()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kBlack));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bu2Dst0Hst_D0pi0()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kGreen));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bu2Dst0Hst_D0gamma()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kMagenta + 3));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bu2D0H()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kOrange));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bu2D0Hst()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kTeal));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bd2DstH()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kMagenta));
  // simPdf.plotOn(
  //     frame.get(),
  //     RooFit::Slice(
  //         categories.fitting,
  //         ComposeName(neutral, bachelor, daughters).c_str()),
  //     RooFit::ProjWData(categories.fitting, fullDataSet),
  //     RooFit::Components(pdf.bu2D0Hst0()), RooFit::LineStyle(kDashed),
  //     RooFit::LineColor(kYellow));
  // simPdf.plotOn(
  //     frame.get(),
  //     RooFit::Slice(categories.fitting,
  //                   ComposeName(neutral, bachelor, daughters).c_str()),
  //     RooFit::ProjWData(categories.fitting, fullDataSet),
  //     RooFit::Components(pdf.missId()), RooFit::LineStyle(kDashed),
  //     RooFit::LineColor(9));
  // simPdf.plotOn(
  //     frame.get(),
  //     RooFit::Slice(categories.fitting,
  //                   ComposeName(neutral, bachelor, daughters).c_str()),
  //     RooFit::ProjWData(categories.fitting, fullDataSet),
  //     RooFit::Components(pdf.bu2D0HMissId()), RooFit::LineStyle(kDashed),
  //     RooFit::LineColor(kOrange));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.combinatorial()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kRed + 2));

  // ------------- Draw Legend --------------

  auto bu2Dst0H_D0pi0Hist = std::make_unique<TH1D>(
      ("bu2Dst0H_D0pi0Hist" + ComposeName(neutral, bachelor, daughters))
          .c_str(),
      "bu2Dst0H_D0pi0Hist", 0, 0, 0);
  bu2Dst0H_D0pi0Hist->SetLineColor(kBlue);
  bu2Dst0H_D0pi0Hist->SetLineStyle(kDashed);
  bu2Dst0H_D0pi0Hist->SetLineWidth(2);

  auto nonTMSignalHist = std::make_unique<TH1D>(
      ("nonTMSignalHist" + ComposeName(neutral, bachelor, daughters))
          .c_str(),
      "nonTMSignalHist", 0, 0, 0);
  nonTMSignalHist->SetLineColor(kBlack);
  nonTMSignalHist->SetLineStyle(kDashed);
  nonTMSignalHist->SetLineWidth(2);

  auto bu2Dst0H_D0gammaHist = std::make_unique<TH1D>(
      ("bu2Dst0H_D0gammaHist" + ComposeName(neutral, bachelor, daughters))
          .c_str(),
      "bu2Dst0H_D0gammaHist", 0, 0, 0);
  bu2Dst0H_D0gammaHist->SetLineColor(kRed);
  bu2Dst0H_D0gammaHist->SetLineStyle(kDashed);
  bu2Dst0H_D0gammaHist->SetLineWidth(2);

  auto bu2Dst0Hst_D0pi0Hist = std::make_unique<TH1D>(
      ("bu2Dst0Hst_D0pi0Hist" + ComposeName(neutral, bachelor, daughters))
          .c_str(),
      "bu2Dst0Hst_D0pi0Hist", 0, 0, 0);
  bu2Dst0Hst_D0pi0Hist->SetLineColor(kGreen);
  bu2Dst0Hst_D0pi0Hist->SetLineStyle(kDashed);
  bu2Dst0Hst_D0pi0Hist->SetLineWidth(2);

  auto bu2Dst0Hst_D0gammaHist = std::make_unique<TH1D>(
      ("bu2Dst0Hst_D0gammaHist" + ComposeName(neutral, bachelor, daughters))
          .c_str(),
      "bu2Dst0Hst_D0gammaHist", 0, 0, 0);
  bu2Dst0Hst_D0gammaHist->SetLineColor(kMagenta + 3);
  bu2Dst0Hst_D0gammaHist->SetLineStyle(kDashed);
  bu2Dst0Hst_D0gammaHist->SetLineWidth(2);

  auto bu2D0HHist = std::make_unique<TH1D>(
      ("bu2D0HHist" + ComposeName(neutral, bachelor, daughters))
          .c_str(),
      "bu2D0HHist", 0, 0, 0);
  bu2D0HHist->SetLineColor(kOrange);
  bu2D0HHist->SetLineStyle(kDashed);
  bu2D0HHist->SetLineWidth(2);

  auto bu2D0HstHist = std::make_unique<TH1D>(
      ("bu2D0HstHist" + ComposeName(neutral, bachelor, daughters))
          .c_str(),
      "bu2D0HstHist", 0, 0, 0);
  bu2D0HstHist->SetLineColor(kTeal);
  bu2D0HstHist->SetLineStyle(kDashed);
  bu2D0HstHist->SetLineWidth(2);

  auto bd2DstHHist = std::make_unique<TH1D>(
      ("bd2DstHHist" + ComposeName(neutral, bachelor, daughters))
          .c_str(),
      "bd2DstHHist", 0, 0, 0);
  bd2DstHHist->SetLineColor(kMagenta);
  bd2DstHHist->SetLineStyle(kDashed);
  bd2DstHHist->SetLineWidth(2);

  auto combinatorialHist = std::make_unique<TH1D>(
      ("combinatorialHist" + ComposeName(neutral, bachelor, daughters))
          .c_str(),
      "combinatorialHist", 0, 0, 0);
  combinatorialHist->SetLineColor(kRed + 2);
  combinatorialHist->SetLineStyle(kDashed);
  combinatorialHist->SetLineWidth(2);

  auto missIdHist = std::make_unique<TH1D>(
      ("missIdHist" + ComposeName(neutral, bachelor, daughters))
          .c_str(),
      "missIdHist", 0, 0, 0);
  missIdHist->SetLineColor(9);
  missIdHist->SetLineStyle(kDashed);
  missIdHist->SetLineWidth(2);

  auto bu2D0HMissIdHist = std::make_unique<TH1D>(
      ("bu2D0HMissIdHist" + ComposeName(neutral, bachelor, daughters))
          .c_str(),
      "bu2D0HMissIdHist", 0, 0, 0);
  bu2D0HMissIdHist->SetLineColor(kYellow);
  bu2D0HMissIdHist->SetLineStyle(kDashed);
  bu2D0HMissIdHist->SetLineWidth(2);

  auto legend = std::make_unique<TLegend>(0.6, 0.35, 0.97, 0.90);
  // legend->SetHeader("Physics Bachgrounds");
  legend->AddEntry(bu2Dst0H_D0pi0Hist.get(),
                   ("B^{" + chargeLabel +
                    "}#rightarrow#font[132]{[}#font[132]{[}" + daughtersLabel +
                    "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{0}*}" +
                    bachelorLabel + "^{" + chargeLabel + "}")
                       .c_str(),
                   "l");
  legend->AddEntry(nonTMSignalHist.get(), ("Miss-Reconstructed B^{" + chargeLabel +
                                     "}#rightarrow#font[132]{[}#font[132]{[}" +
                                     daughtersLabel + "#font[132]{]}_{D^{0}}" +
                                     neutralLabel + "#font[132]{]}_{D^{0}*}" +
                                     bachelorLabel + "^{" + chargeLabel + "}")
                                        .c_str(),
                   "l");
  legend->AddEntry(bu2Dst0H_D0gammaHist.get(),
                   ("B^{" + chargeLabel +
                    "}#rightarrow#font[132]{[}#font[132]{[}" + daughtersLabel +
                    "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{0}*}" +
                    bachelorLabel + "^{" + chargeLabel + "}")
                       .c_str(),
                   "l");
  legend->AddEntry(bu2Dst0Hst_D0pi0Hist.get(),
                   ("B^{" + chargeLabel +
                    "}#rightarrow#font[132]{[}#font[132]{[}" + daughtersLabel +
                    "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{0}*}" +
                    hstLabel + "^{" + chargeLabel + "}")
                       .c_str(),
                   "l");
  legend->AddEntry(bu2Dst0Hst_D0gammaHist.get(),
                   ("B^{" + chargeLabel +
                    "}#rightarrow#font[132]{[}#font[132]{[}" + daughtersLabel +
                    "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{0}*}" +
                    hstLabel + "^{" + chargeLabel + "}")
                       .c_str(),
                   "l");
  legend->AddEntry(bu2D0HHist.get(),
                   ("B^{" + chargeLabel + "}#rightarrow#font[132]{[}" +
                    daughtersLabel + "#font[132]{]}_{D^{0}}" + bachelorLabel +
                    "^{" + chargeLabel + "}")
                       .c_str(),
                   "l");
  legend->AddEntry(bu2D0HstHist.get(),
                   ("B^{" + chargeLabel + "}#rightarrow#font[132]{[}" +
                    daughtersLabel + "#font[132]{]}_{D^{0}}" + hstLabel + "^{" +
                    chargeLabel + "}")
                       .c_str(),
                   "l");
  legend->AddEntry(bd2DstHHist.get(),
                   ("B^{0}#rightarrow#font[132]{[}#font[132]{[}" +
                    daughtersLabel + "#font[132]{]}_{D^{0}}#pi^{-}#font["
                                     "132]{]}_{D^{-}*}" +
                    bachelorLabel + "^{+}")
                       .c_str(),
                   "l");
  legend->AddEntry(
      missIdHist.get(),
      ("Miss-ID B^{" + chargeLabel + "}#rightarrow#font[132]{[}#font[132]{[}" +
       daughtersLabel + "#font[132]{]}_{D^{0}}" + neutralLabel +
       "#font[132]{]}_{D^{0}*}" + missIdLabel + "^{" + chargeLabel + "}")
          .c_str(),
      "l");
  legend->AddEntry(bu2D0HMissIdHist.get(),
                   ("Miss-ID B^{" + chargeLabel + "}#rightarrow#font[132]{[}" +
                    daughtersLabel + "#font[132]{]}_{D^{0}}" + missIdLabel +
                    "^{" + chargeLabel + "}")
                       .c_str(),
                   "l");
  legend->AddEntry(combinatorialHist.get(), "Combinatorial", "l");

  // --------------- plot onto canvas ---------------------

  std::unique_ptr<RooPlot> pullFrame(config.buMass().frame(RooFit::Title(" ")));

  pullFrame->addPlotable(hpull /* .get() */, "P");
  pullFrame->SetName(
      ("pullFrame_" + ComposeName(neutral, bachelor, daughters)).c_str());
  pullFrame->SetTitle("");

  TCanvas canvas(
      ("simPdf_" + ComposeName(neutral, bachelor, daughters)).c_str(), "simPdf",
      1500, 900);

  TPad pad2(("pad2_" + ComposeName(neutral, bachelor, daughters)).c_str(),
            "pad2", 0.0, 0.1, 1.0, 0.20, kWhite);
  pad2.Draw();

  TPad pad1(("pad1_" + ComposeName(neutral, bachelor, daughters)).c_str(),
            "pad1", 0.0, 0.19, 1.0, 1.0, kWhite);
  pad1.Draw();

  // Zero line on error plot.
  TLine zeroLine(5045, 0, 5805, 0);
  zeroLine.SetLineColor(kRed);
  zeroLine.SetLineStyle(kDashed);

  pad2.cd();
  pullFrame->SetYTitle(" ");
  pullFrame->SetXTitle(" ");
  pullFrame->SetLabelSize(0.2, "Y");
  pullFrame->SetLabelFont(132, "XY");
  pullFrame->SetLabelOffset(100, "X");
  // pullFrame->SetLabelOffset(0.1, "Y");
  pullFrame->SetTitleOffset(100, "X");
  pullFrame->Draw();
  zeroLine.Draw("same");

  pad1.cd();
  pullFrame->SetXTitle("m[Bu] (MeV/c^{2})");
  frame->Draw();
  legend->Draw("same");
  // dataHist->Draw("same");

  canvas.Update();
  canvas.SaveAs(
      ("Result_" + ComposeName(neutral, bachelor, daughters) + ".pdf").c_str());
}

// void GenerateToyDataSet(const &simPdf, Configuration &config,
// Configuration::Categories &categories) {
//
//   RooMCStudy mcStudy(simPdf, RooArgList(config.buMass(), categories.fitting),
//   RooFit::FitOptions(RooFit::Save(kTrue)));
//
//   mcStudy.generate(1, 400000, true);
//   RooDataSet *toyDataSet = dynamic_cast<RooDataSet*>(mcStudy.genData(0));

// mcStudy.generateAndFit(10000);
//
// std::unique_ptr<RooPlot> frame(mcStudy.plotPull(config.buMass(),
// RooFit::Bins(20), RooFit::FitGauss(true)));
//
// TCanvas canvas(
//     ("ToysCanvas", "Toys Canvas", 1500, 900);
//
// frame->Draw();
// canvas.Update();
// canvas.SaveAs(("Toys_PullHist.ibution_" + ComposeFittingCategory(neutral,
// bachelor, daughters) + ".pdf").c_str());
// }
void FitSimPdfToData(RooAbsData &fittingDataSet,
                     RooSimultaneous &simPdf, Configuration &config,
                     Configuration::Categories &categories,
                     std::vector<Charge> const &chargeVec,
                     std::vector<PdfBase *> &pdfs) {

  RooFitResult *result =
      simPdf.fitTo(fittingDataSet, RooFit::Extended(kTRUE), RooFit::Save());

  // Loop over daughters again to plot correct PDFs
  for (auto &p : pdfs) {
    Plotting(*p, chargeVec, config, categories, fittingDataSet, simPdf);
  }

  result->Print("v");
  std::cout << "Printed result." << std::endl;

  TCanvas correlationCanvas("correlationCanvas", "correlationCanvas", 2000,
                            1000);
  std::cout << "Created canvas." << std::endl;
  gStyle->SetTitleFont(132, "XYZ");
  gStyle->SetLabelFont(132, "XYZ");
  gStyle->SetStatFont(132);
  gStyle->SetStatFontSize(0.04);
  gStyle->SetTitleSize(0.08, "Z");
  gStyle->SetTitleSize(0.02, "XY");
  gStyle->SetLabelSize(0.02, "XY");
  gStyle->SetTitleOffset(0.85, "X");
  gStyle->SetTitleOffset(0.95, "Y");
  gStyle->SetTitleOffset(0.9, "Z");
  // gStyle->SetLegendTextSize(0.08);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.09);
  gStyle->SetPadLeftMargin(0.1);
  correlationCanvas.cd();
  std::cout << "Extracting correlation histogram from result..." << std::endl;
  result->correlationHist()->Draw("colz");
  std::cout << "Extracted correlation histogram from result." << std::endl;
  correlationCanvas.Update();
  std::cout << "Updated canvas." << std::endl;
  correlationCanvas.SaveAs("CorrelationMatrix.pdf");
  std::cout << "Save to pdf file." << std::endl;
}

void Fitting(RooAbsData &fullDataSet, Configuration &config,
             Configuration::Categories &categories,
             std::vector<Neutral> const &neutralVec,
             std::vector<Daughters> const &daughtersVec,
             std::vector<Charge> const &chargeVec, bool runToys) {

  RooSimultaneous simPdf("simPdf", "simPdf", categories.fitting);

  std::vector<PdfBase *> pdfs;

  // d is a reference to an element od the vector
  // Downside: don't have direct access to the index
  for (auto &d : daughtersVec) {

    if (d == Daughters::kpi) {

      // emplace_back creates
      // the
      // object then moves it into the vector
      // You only have to pass the arguments as if you were constructing the
      // vector type
      // The operators required to do this are not supported by RooFit so we
      // have to use a vector of pointers

      // switch (neutral) {
      // case Neutral::pi0:
      for (auto &n : neutralVec) {

        switch (n) {

        case Neutral::pi0:

          pdfs.emplace_back(
              &Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Get());
          pdfs.emplace_back(
              &Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi>::Get());
          // Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Get()
              // .AssignMissIdYields();
          // Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Get()
          //     .CreateRooAddPdf();
          // Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi>::Get()
          //     .AssignMissIdYields();
          // Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi>::Get()
          //     .CreateRooAddPdf();
          break;

        case Neutral::gamma:

          pdfs.emplace_back(
              &Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Get());
          pdfs.emplace_back(
              &Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi>::Get());
          // Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Get()
          //     .AssignMissIdYields();
          // Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Get()
          //     .CreateRooAddPdf();
          // Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi>::Get()
          //     .AssignMissIdYields();
          // Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi>::Get()
          //     .CreateRooAddPdf();
          break;
        }
      }
    } else if (d == Daughters::kk) {

      for (auto &n : neutralVec) {

        switch (n) {

        case Neutral::pi0:

          pdfs.emplace_back(
              &Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk>::Get());
          pdfs.emplace_back(
              &Pdf<Neutral::pi0, Bachelor::k, Daughters::kk>::Get());
          // Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk>::Get()
          //     .AssignMissIdYields();
          // Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk>::Get()
          //     .CreateRooAddPdf();
          // Pdf<Neutral::pi0, Bachelor::k, Daughters::kk>::Get()
          //     .AssignMissIdYields();
          // Pdf<Neutral::pi0, Bachelor::k, Daughters::kk>::Get()
          //     .CreateRooAddPdf();
          break;

        case Neutral::gamma:

          pdfs.emplace_back(
              &Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk>::Get());
          pdfs.emplace_back(
              &Pdf<Neutral::gamma, Bachelor::k, Daughters::kk>::Get());
          // Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk>::Get()
          //     .AssignMissIdYields();
          // Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk>::Get()
          //     .CreateRooAddPdf();
          // Pdf<Neutral::gamma, Bachelor::k, Daughters::kk>::Get()
          //     .AssignMissIdYields();
          // Pdf<Neutral::gamma, Bachelor::k, Daughters::kk>::Get()
          //     .CreateRooAddPdf();
          break;
        }
      }
    } else if (d == Daughters::pipi) {

      for (auto &n : neutralVec) {

        switch (n) {

        case Neutral::pi0:

          pdfs.emplace_back(
              &Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Get());
          pdfs.emplace_back(
              &Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi>::Get());
          // Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Get()
          //     .AssignMissIdYields();
          // Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Get()
          //     .CreateRooAddPdf();
          // Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi>::Get()
          //     .AssignMissIdYields();
          // Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi>::Get()
          //     .CreateRooAddPdf();
          break;

        case Neutral::gamma:

          pdfs.emplace_back(
              &Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Get());
          pdfs.emplace_back(
              &Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi>::Get());
          // Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Get()
          //     .AssignMissIdYields();
          // Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Get()
          //     .CreateRooAddPdf();
          // Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi>::Get()
          //     .AssignMissIdYields();
          // Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi>::Get()
          //     .CreateRooAddPdf();
          break;
        }
      }
    } else {

      for (auto &n : neutralVec) {

        switch (n) {

        case Neutral::pi0:

          pdfs.emplace_back(
              &Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik>::Get());
          pdfs.emplace_back(
              &Pdf<Neutral::pi0, Bachelor::k, Daughters::pik>::Get());
          // Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik>::Get()
          //     .AssignMissIdYields();
          // Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik>::Get()
          //     .CreateRooAddPdf();
          // Pdf<Neutral::pi0, Bachelor::k, Daughters::pik>::Get()
          //     .AssignMissIdYields();
          // Pdf<Neutral::pi0, Bachelor::k, Daughters::pik>::Get()
          //     .CreateRooAddPdf();

          break;

        case Neutral::gamma:

          pdfs.emplace_back(
              &Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik>::Get());
          pdfs.emplace_back(
              &Pdf<Neutral::gamma, Bachelor::k, Daughters::pik>::Get());
          // Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik>::Get()
          //     .AssignMissIdYields();
          // Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik>::Get()
          //     .CreateRooAddPdf();
          // Pdf<Neutral::gamma, Bachelor::k, Daughters::pik>::Get()
          //     .AssignMissIdYields();
          // Pdf<Neutral::gamma, Bachelor::k, Daughters::pik>::Get()
          //     .CreateRooAddPdf();

          break;
        }
      }
    }
  }

  for (auto &p : pdfs) {
    p->AddToSimultaneousPdf(simPdf);
  }


  // ------------ generate toys ---------------

  // Toy data sets check for bias in our model. The pull distribution should be
  // around 0, i.e. the generated data matches the defined model.

  if (runToys == true) {

    // categories.fitting
    RooMCStudy mcStudy(
        simPdf, RooArgList(config.buMass(), categories.fitting),
        RooFit::Binned(true), RooFit::Silence(), RooFit::Extended(),
        RooFit::FitOptions(RooFit::Save(true), RooFit::PrintEvalErrors(0)));

    std::cout << "Created MCStudy object." << std::endl;

    int nSamples = 1;
    int nEvtsPerSample = 60000;

    mcStudy.generate(nSamples, nEvtsPerSample, true);

    std::cout << "Generated toy events." << std::endl;

    RooAbsData *toyDataSet = const_cast<RooAbsData *>(mcStudy.genData(0));

    std::cout << "Retrieved RooDataSet from MCStudy object." << std::endl;
    
    FitSimPdfToData(*toyDataSet, simPdf, config, categories, chargeVec, pdfs);
  
  } else {
    
    FitSimPdfToData(fullDataSet, simPdf, config, categories, chargeVec, pdfs);
  
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

// Path to roodatasets
// std::string dataDir =
// "/Users/alexandrarollings/Desktop/FittingProgramme/roodatasets/";
// std::string dataDir = "/home/rollings/ButoDst0X_FIT/roodatasets/";

int main(int argc, char **argv) {

  std::string dataDir;
  std::vector<Year> yearVec;
  std::vector<Polarity> polarityVec;
  std::vector<Bachelor> bachelorVec;
  std::vector<Neutral> neutralVec;
  std::vector<Daughters> daughtersVec;
  std::vector<Charge> chargeVec;
  bool runToys = false;

  // By letting the ParseArguments object go out of scope it will print a
  // warning if the user specified any unknown options.
  { // calls destructor when object goes out of scope: Will tell you if
    // anything
    // was not used that was given as a command line argument before
    // continuing
    ParseArguments args(argc, argv); // object instantiated

    std::string yearArg("2011,2012,2015");
    std::string polarityArg("up,down");
    std::string bachelorArg("pi,k");
    std::string neutralArg("pi0,gamma");
    std::string daughtersArg("kpi,kk,pipi,pik");
    std::string chargeArg("plus,minus");

    // We always want to simultaneously fir the pi AND k bachelor modes
    // together
    bachelorVec = ExtractEnumList<Bachelor>(bachelorArg);

    if (args("help")) {

      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "Type ./Fitting -dataDir=<RooDataSets directory name> \n"
                << "\n";
      std::cout << "Followed by the possible options:\n";
      std::cout << "\n";
      std::cout << "    -year=<choice {2011,2012,2015} default: " << yearArg
                << ">\n";
      std::cout << "    -polarity=<choice {up,down} default: " << polarityArg
                << ">\n";
      // std::cout << "    -bachelor choice {k,pi} default: " << bachelorArg
      // <<
      // "\n";
      std::cout << "    -neutral=<choice {pi0,gamma} default: " << neutralArg
                << ">\n";
      std::cout << "    -daughters=<choice {kpi,kk,pipi,pik} default: "
                << daughtersArg << ">\n";
      std::cout << "    -charge=<choice {plus,minus} default: " << chargeArg
                << ">\n";
      std::cout << "    -toys"
                << ">\n";
      std::cout << "\n";
      std::cout << "To specify multiple options, separate them by commas.\n";
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "\n";
    } else {

      // Data folder
      if (!args("dataDir", dataDir)) {
        std::cerr << "Data directory must be specified (-dataDir=<path>)\n";
        return 1;
      }

      runToys = args("toys");

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
                     "-year=[2011,2012,2015].\n";
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
      } catch (std::invalid_argument) {
        std::cerr << "charge assignment failed, please specify: "
                     "-charge=[plus,minus].\n";
        return 1;
      }
    }
  }

  Configuration &config = Configuration::Get();
  Configuration::Categories &categories = Configuration::Get().categories();

  RooDataSet fullDataSet("dataset", "dataset", config.fullArgSet());

  // Loop over all options in order to extract correct roodatasets
  for (unsigned int yCounter = 0; yCounter < yearVec.size(); yCounter++) {
    for (unsigned int pCounter = 0; pCounter < polarityVec.size(); pCounter++) {
      for (unsigned int bCounter = 0; bCounter < bachelorVec.size();
           bCounter++) {
        for (unsigned int dCounter = 0; dCounter < daughtersVec.size();
             dCounter++) {
          for (unsigned int cCounter = 0; cCounter < chargeVec.size();
               cCounter++) {
            for (unsigned int nCounter = 0; nCounter < neutralVec.size();
                 nCounter++) {
              std::string dsFile =
                  dataDir + "/" +
                  ComposeFilename(yearVec[yCounter], polarityVec[pCounter],
                                  bachelorVec[bCounter], neutralVec[nCounter],
                                  daughtersVec[dCounter], chargeVec[cCounter]) +
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

  Fitting(fullDataSet, config, categories, neutralVec, daughtersVec, chargeVec,
          runToys);

  //   for (unsigned int i = 0; i < fullDataSet.numEntries(); i++) {
  //
  //     RooArgSet const *row = fullDataSet.get(i);
  //
  //     std::cout << "For event " << i << ":";
  //
  //     RooCategory *neutralPtr =
  //         dynamic_cast<RooCategory
  //         *>(row->find(categories.neutral.GetName()));
  //     if (neutralPtr == nullptr) {
  //       std::stringstream output;
  //       output << "No category assigned to neutral for event " << i << ".";
  //       throw std::runtime_error(output.str());
  //     } else {
  //       std::cout << "    neutral = " << neutralPtr->getLabel() << "\n";
  //       if (neutralPtr->getLabel() == "gamma") {
  //
  //         std::cerr << "Wrong neutral assigned (gamma)\n";
  //         return 1;
  //       }
  //     }
  //   }
  //
  return 0;
}
