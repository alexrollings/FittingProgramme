#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooDataSet.h"
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

std::string path;

void Plotting(PdfBase &pdf, std::vector<Charge> const &chargeVec,
              Configuration &config, Configuration::Categories &categories,
              RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
              RooFitResult *result) {

  SetStyle();
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
       daughtersLabel + "#font[132]{]}_{D^{0}}" + neutralLabel +
       "#font[132]{]}_{D^{*0}}" + bachelorLabel + "^{" + chargeLabel + "}")
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

  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.pdfSignal()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kBlue));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.pdfComb()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kRed));
  frame->SetXTitle(("m[D*^{0}" + bachelorLabel + "] (MeV/c^{2})").c_str());

  // ------------- Draw Legend --------------

  auto pdfSignalHist = std::make_unique<TH1D>(
      ("pdfSignalHist" + ComposeName(neutral, bachelor, daughters)).c_str(),
      "pdfSignalHist", 0, 0, 0);
  pdfSignalHist->SetLineColor(kBlue);
  pdfSignalHist->SetLineStyle(kDashed);
  pdfSignalHist->SetLineWidth(2);

  auto pdfCombHist = std::make_unique<TH1D>(
      ("pdfCombHist" + ComposeName(neutral, bachelor, daughters)).c_str(),
      "pdfCombHist", 0, 0, 0);
  pdfCombHist->SetLineColor(kRed);
  pdfCombHist->SetLineStyle(kDashed);
  pdfCombHist->SetLineWidth(2);

  auto legend = std::make_unique<TLegend>(0.7, 0.7, 0.97, 0.90);
  // legend->SetHeader("Physics Backgrounds");
  legend->AddEntry(
      pdfSignalHist.get(),
      ("B^{" + chargeLabel + "}#rightarrow#font[132]{[}#font[132]{[}" +
       daughtersLabel + "#font[132]{]}_{D^{0}}" + neutralLabel +
       "#font[132]{]}_{D^{0}*}" + bachelorLabel + "^{" + chargeLabel + "}")
          .c_str(),
      "l");
  legend->AddEntry(pdfCombHist.get(), "Combinatorial", "l");

  // --------------- plot onto canvas ---------------------

  std::unique_ptr<RooPlot> pullFrame(config.buMass().frame(RooFit::Title(" ")));

  pullFrame->addPlotable(hpull /* .get() */, "P");
  pullFrame->SetName(
      ("pullFrame_" + ComposeName(neutral, bachelor, daughters)).c_str());
  pullFrame->SetTitle("");

  TCanvas canvas(
      ("simPdf_" + ComposeName(neutral, bachelor, daughters)).c_str(), "simPdf",
      1200, 1000);

  TPad pad2(("pad2_" + ComposeName(neutral, bachelor, daughters)).c_str(),
            "pad2", 0.0, 0.05, 1.0, 0.15, kWhite);
  pad2.Draw();

  TPad pad1(("pad1_" + ComposeName(neutral, bachelor, daughters)).c_str(),
            "pad1", 0.0, 0.14, 1.0, 1.0, kWhite);
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

  auto blankHist = std::make_unique<TH1D>(
      ("blankHist" + ComposeName(neutral, bachelor, daughters)).c_str(),
      "blankHist", 0, 0, 0);
  blankHist->SetLineColor(kWhite);
  blankHist->SetLineWidth(2);

  auto yieldLegend = std::make_unique<TLegend>(0.12, 0.6, 0.3, 0.8);

  std::stringstream sigLegend;
  sigLegend << "Signal: " << pdf.yieldSignal().getVal()
            // << " #pm " << pdf.yieldSignal().getPropagatedError(*result)
            << " events";

  std::stringstream bkgLegend;
  bkgLegend << "Background: "
            << fullDataSet.numEntries() - pdf.yieldSignal().getVal()
            // << " #pm ";
            // << backgroundYield.getError()
            << " events";

  yieldLegend->SetLineColor(kWhite);
  // yieldLegend->AddEntry(blankHist.get(), "#int L dt = 4.8 #pm 0.13 fb^{-1}",
  //                       "l");
  yieldLegend->AddEntry(blankHist.get(), sigLegend.str().c_str(), "l");
  yieldLegend->AddEntry(blankHist.get(), bkgLegend.str().c_str(), "l");

  pad1.cd();
  pullFrame->SetXTitle(("m[D^{*0}" + bachelorLabel + "] (MeV/c^{2})").c_str());
  frame->Draw();
  legend->Draw("same");
  // yieldLegend->Draw("same");
  // dataHist->Draw("same");

  canvas.Update();
  canvas.SaveAs(
      (path + ComposeName(neutral, bachelor, daughters) + ".pdf").c_str());
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
void FitSimPdfToData(RooAbsData &fittingDataSet, RooSimultaneous &simPdf,
                     Configuration &config,
                     Configuration::Categories &categories,
                     std::vector<Charge> const &chargeVec,
                     std::vector<PdfBase *> &pdfs) {
  RooFitResult *result =
      simPdf.fitTo(fittingDataSet, RooFit::Extended(kTRUE), RooFit::Save());

  // Loop over daughters again to plot correct PDFs
  for (auto &p : pdfs) {
    Plotting(*p, chargeVec, config, categories, fittingDataSet, simPdf, result);
  }

  result->Print("v");
  std::cout << "Printed result." << std::endl;

  TCanvas correlationCanvas("correlationCanvas", "correlationCanvas", 1000,
                            1000);
  std::cout << "Created canvas." << std::endl;
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
             std::vector<Charge> const &chargeVec) {
  RooSimultaneous simPdf("simPdf", "simPdf", categories.fitting);

  std::vector<PdfBase *> pdfs;

  // d is a reference to an element od the vector
  // Downside: don't have direct access to the index
  for (auto &d : daughtersVec) {
    if (d == Daughters::kpi) {
      // emplace_back creates
      // the
      // object then moves it into the vector      // You only have to pass the
      // arguments as if you were constructing the
      // vector type
      // The operators required to do this are not supported by RooFit so we
      // have to use a vector of pointers

      // switch (neutral) {
      // case Neutral::pi0:      for (auto &n : neutralVec) {

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
            //     .AssignMissIdYields();          // Pdf<Neutral::pi0,
            //     Bachelor::k, Daughters::kpi>::Get()
            //     .CreateRooAddPdf();
            break;

          case Neutral::gamma:

            pdfs.emplace_back(
                &Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Get());
            pdfs.emplace_back(
                &Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi>::Get());

            // Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Get()
            // .AssignMissIdYields();
            // Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Get()
            //     .CreateRooAddPdf();
            // Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi>::Get()
            //     .AssignMissIdYields();
            // Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi>::Get()
            // //     .CreateRooAddPdf();

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
            // .AssignMissIdYields();
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
            // .AssignMissIdYields();
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
            // .AssignMissIdYields();
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
            // .AssignMissIdYields();
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
            // .AssignMissIdYields();
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

            // Pdf<Neutral::gamma, Bachelor::pi, Daughters::pi>::Get()
            // .AssignMissIdYields();
            // Pdf<Neutral::gamma, Bachelor::pi, Daughters::pi>::Get()
            //     .CreateRooAddPdf();
            // Pdf<Neutral::gamma, Bachelor::k, Daughters::pi>::Get()
            //     .AssignMissIdYields();
            // Pdf<Neutral::gamma, Bachelor::k, Daughters::pi>::Get()
            //     .CreateRooAddPdf();

            break;
        }
      }
    }
  }

  for (auto &p : pdfs) {
    p->AddToSimultaneousPdf(simPdf);
  }

  FitSimPdfToData(fullDataSet, simPdf, config, categories, chargeVec, pdfs);
}

void Fitting(Configuration &config, Configuration::Categories &categories,
             std::vector<Neutral> const &neutralVec,
             std::vector<Daughters> const &daughtersVec,
             std::vector<Charge> const &chargeVec) {
  RooSimultaneous simPdf("simPdf", "simPdf", categories.fitting);

  std::vector<PdfBase *> pdfs;

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
            // .AssignMissIdYields();
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
            // .AssignMissIdYields();
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
            // .AssignMissIdYields();
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
            // .AssignMissIdYields();
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
            // .AssignMissIdYields();
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
            // .AssignMissIdYields();
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
            // .AssignMissIdYields();
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

  // Toy data sets check for bias in our model. The pull distribution should
  // be
  // around 0, i.e. the generated data matches the defined model.

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
  {  // calls destructor when object goes out of scope: Will tell you if
    // anything
    // was not used that was given as a command line argument before
    // continuing
    ParseArguments args(argc, argv);  // object instantiated

    // std::string yearArg("2011,2012,2015,2016");
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
      std::cout << "    -charge=<choice {plus,minus} default: " << chargeArg
                << ">\n";
      std::cout << "    -toys"
                <<  " (optional)\n";
      std::cout << "\n";
      std::cout << "To specify multiple options, separate them by commas.\n";
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "\n";

      return 1;
    } else {
      // Data folder
      runToys = args("toys");

      if (!args("dataDir", dataDir) && runToys==false) {
        std::cerr << "Data directory must be specified (-dataDir=<path>)\n";
        return 1;
      }

      //
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
      } catch (std::invalid_argument) {
        std::cerr << "charge assignment failed, please specify: "
                     "-charge=[plus,minus].\n";
        return 1;
      }
    }
  }

  Configuration &config = Configuration::Get();
  Configuration::Categories &categories = Configuration::Get().categories();

  if (runToys == false) {
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
                    dataDir + "/" +
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

    // for (unsigned int i = 0; i < 10000; i++) {
    //
    //   RooArgSet const *row = fullDataSet.get(i);
    //
    //   std::cout << "For event " << i << ":";
    //
    //   RooRealVar *buMassPtr =
    //       dynamic_cast<RooRealVar *>(row->find(config.buMass().GetName()));
    //   if (buMassPtr == nullptr) {
    //     std::stringstream output;
    //     output << "No buMass value for event " << i << ".";
    //     throw std::runtime_error(output.str());
    //   } else {
    //     std::cout << "buMass = " << buMassPtr->getVal() << "\n";
    //   }
    // }

    path = "result/";
    Fitting(fullDataSet, config, categories, neutralVec, daughtersVec,
            chargeVec);

  } else {
    path = "toys/";
    Fitting(config, categories, neutralVec, daughtersVec, chargeVec);
  }

  return 0;
}
