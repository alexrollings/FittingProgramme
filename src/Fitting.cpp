#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooHist.h"
#include "RooMCStudy.h"
#include "RooPlot.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2F.h"
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

void Plotting1D(PdfBase &pdf, std::vector<Charge> const &chargeVec,
              Configuration &config, Configuration::Categories &categories,
              RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
              RooFitResult *result) {
  SetStyle();

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

  // .get() gets the raw pointer from underneath the smart pointer

  // ------------- Draw Legends -------------- //
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

  // ---- PLOTTING FOR BU MASS COMPONENT ---- //

  std::unique_ptr<RooPlot> frameBu(config.buMass().frame(RooFit::Title(
      ("B^{" + chargeLabel + "}#rightarrow#font[132]{[}#font[132]{[}" +
       daughtersLabel + "#font[132]{]}_{D^{0}}" + neutralLabel +
       "#font[132]{]}_{D^{*0}}" + bachelorLabel + "^{" + chargeLabel + "}")
          .c_str())));

  fullDataSet.plotOn(frameBu.get(),
                     RooFit::Cut(("fitting==fitting::" +
                                  ComposeName(neutral, bachelor, daughters))
                                     .c_str()));

  simPdf.plotOn(
      frameBu.get(),
      RooFit::Slice(categories.fitting,
                    ComposeName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::LineColor(kBlue));

  // auto hpull = std::unique_ptr<RooHist>(
  //     dynamic_cast<RooHist *>(frameBu->RooPlot::pullHist()));
  RooHist *hPullBu = frameBu->RooPlot::pullHist();

  simPdf.plotOn(
      frameBu.get(),
      RooFit::Slice(categories.fitting,
                    ComposeName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.pdfBuSignal()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kBlue));
  simPdf.plotOn(
      frameBu.get(),
      RooFit::Slice(categories.fitting,
                    ComposeName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.pdfBuComb()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kRed));
  frameBu->SetXTitle(("m[D*^{0}" + bachelorLabel + "] (MeV/c^{2})").c_str());

  std::unique_ptr<RooPlot> pullFrameBu(
      config.buMass().frame(RooFit::Title(" ")));

  pullFrameBu->addPlotable(hPullBu /* .get() */, "P");
  pullFrameBu->SetName(
      ("pullFrameBu_" + ComposeName(neutral, bachelor, daughters)).c_str());
  pullFrameBu->SetTitle("");

  // --------------- plot onto canvas ---------------------

  TCanvas canvasBu(
      ("canvasBu_" + ComposeName(neutral, bachelor, daughters)).c_str(),
      "canvasBu", 1200, 1000);

  TPad padBu2(("padBu2_" + ComposeName(neutral, bachelor, daughters)).c_str(),
              "padBu2", 0.0, 0.05, 1.0, 0.15, kWhite);
  padBu2.Draw();

  TPad padBu1(("padBu1_" + ComposeName(neutral, bachelor, daughters)).c_str(),
              "padBu1", 0.0, 0.14, 1.0, 1.0, kWhite);
  padBu1.Draw();

  // Zero line on error plot.
  TLine zeroLineBu(config.buMass().getMin(), 0, config.buMass().getMax(), 0);
  zeroLineBu.SetLineColor(kRed);
  zeroLineBu.SetLineStyle(kDashed);

  canvasBu.cd();
  padBu2.cd();
  pullFrameBu->SetYTitle(" ");
  pullFrameBu->SetXTitle(" ");
  pullFrameBu->SetLabelSize(0.2, "Y");
  pullFrameBu->SetLabelFont(132, "XY");
  pullFrameBu->SetLabelOffset(100, "X");
  // pullFrameBu->SetLabelOffset(0.1, "Y");
  pullFrameBu->SetTitleOffset(100, "X");
  pullFrameBu->Draw();
  zeroLineBu.Draw("same");

  canvasBu.cd();
  padBu1.cd();
  pullFrameBu->SetXTitle(
      ("m[D^{*0}" + bachelorLabel + "] (MeV/c^{2})").c_str());
  frameBu->Draw();
  legend->Draw("same");
  // yieldLegend->Draw("same");
  // dataHist->Draw("same");

  canvasBu.Update();
  canvasBu.SaveAs(
      (path + ComposeName(neutral, bachelor, daughters) + "_buMass.pdf")
          .c_str());

  // ---- PLOTTING FOR DELTA MASS COMPONENT ---- //

  std::unique_ptr<RooPlot> frameDelta(config.deltaMass().frame(RooFit::Title(
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

  // --------------- plot data and pdfs onto frames ---------------------

  fullDataSet.plotOn(frameDelta.get(),
                     RooFit::Cut(("fitting==fitting::" +
                                  ComposeName(neutral, bachelor, daughters))
                                     .c_str()));

  simPdf.plotOn(
      frameDelta.get(),
      RooFit::Slice(categories.fitting,
                    ComposeName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::LineColor(kBlue));

  // auto hpull = std::unique_ptr<RooHist>(
  //     dynamic_cast<RooHist *>(frameDelta->RooPlot::pullHist()));
  RooHist *hPullDelta = frameDelta->RooPlot::pullHist();
  hPullDelta->SetName("test");

  simPdf.plotOn(
      frameDelta.get(),
      RooFit::Slice(categories.fitting,
                    ComposeName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.pdfDeltaSignal()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kBlue));
  simPdf.plotOn(
      frameDelta.get(),
      RooFit::Slice(categories.fitting,
                    ComposeName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.pdfDeltaComb()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kRed));
  frameDelta->SetXTitle("m[D*^{0}] - m[D^{0}] (MeV/c^{2})");

  std::unique_ptr<RooPlot> pullFrameDelta(
      config.deltaMass().frame(RooFit::Title(" ")));

  pullFrameDelta->addPlotable(hPullDelta /* .get() */, "P");
  pullFrameDelta->SetName(
      ("pullFrameDelta_" + ComposeName(neutral, bachelor, daughters)).c_str());
  pullFrameDelta->SetTitle("");

  // --------------- plot onto canvas ---------------------

  TCanvas canvasDelta(
      ("canvasDelta_" + ComposeName(neutral, bachelor, daughters)).c_str(),
      "canvasDelta", 1200, 1000);

  TPad padDelta2(
      ("padDelta2_" + ComposeName(neutral, bachelor, daughters)).c_str(),
      "padDelta2", 0.0, 0.05, 1.0, 0.15, kWhite);
  padDelta2.Draw();

  TPad padDelta1(
      ("padDelta1_" + ComposeName(neutral, bachelor, daughters)).c_str(),
      "padDelta1", 0.0, 0.14, 1.0, 1.0, kWhite);
  padDelta1.Draw();

  TLine zeroLineDelta(config.deltaMass().getMin(), 0, config.deltaMass().getMax(), 0);
  zeroLineDelta.SetLineColor(kRed);
  zeroLineDelta.SetLineStyle(kDashed);

  canvasDelta.cd();
  padDelta2.cd();
  pullFrameDelta->SetYTitle(" ");
  pullFrameDelta->SetXTitle(" ");
  pullFrameDelta->SetLabelSize(0.2, "Y");
  pullFrameDelta->SetLabelFont(132, "XY");
  pullFrameDelta->SetLabelOffset(100, "X");
  // pullFrameDelta->SetLabelOffset(0.1, "Y");
  pullFrameDelta->SetTitleOffset(100, "X");
  pullFrameDelta->SetXTitle("m[D^{*0}] - m[D^{0}] (MeV/c^{2})");
  pullFrameDelta->Draw();
  zeroLineDelta.Draw("same");

  canvasDelta.cd();
  padDelta1.cd();
  frameDelta->Draw();
  legend->Draw("same");
  // yieldLegend->Draw("same");
  // dataHist->Draw("same");

  canvasDelta.Update();
  canvasDelta.SaveAs(
      (path + ComposeName(neutral, bachelor, daughters) + "_deltaMass.pdf")
          .c_str());
}

void Plotting2D(PdfBase &pdf, std::vector<Charge> const &chargeVec,
                Configuration &config, RooAbsData const &fullDataSet,
                RooSimultaneous const &simPdf) {
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

  gStyle->SetTitleSize(0.03, "XYZ");
  gStyle->SetLabelSize(0.025, "XYZ");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetTitleOffset(1.5, "Z");
  gStyle->SetPadRightMargin(0.15);

  // Make two-dimensional plot of sampled PDF in x vs y
  TH2F *hh_model = (TH2F *)simPdf.createHistogram(
      ("hh_model_" + ComposeName(neutral, bachelor, daughters)).c_str(),
      config.buMass(), RooFit::Binning(config.buMass().getBins()),
      RooFit::YVar(config.deltaMass(),
                   RooFit::Binning(config.deltaMass().getBins())));
  hh_model->SetTitle("");

  // Make 2D plot of data
  TH2F *hh_data = (TH2F *)fullDataSet.createHistogram(
      "Bu_M_DTF_D0Pi0,Delta_M", config.buMass(),
      RooFit::Binning(config.buMass().getBins()),
      RooFit::YVar(config.deltaMass(),
                   RooFit::Binning(config.deltaMass().getBins())));
  hh_data->SetName(
      ("hh_data_" + ComposeName(neutral, bachelor, daughters)).c_str());
  hh_data->SetTitle("");

  // Scale model plot to total number of data events
  // PDF not normalized: normalize before scaling to data
  hh_model->Scale(1 / hh_model->Integral());
  // std::cout << "\n\n" << hh_model->Integral() << "\n\n";
  // hh_model->GetZaxis()->SetRangeUser(0.0, 0.005);
  hh_data->Scale(1 / hh_data->Integral());
  // std::cout << "\n\n" << hh_data->Integral() << "\n\n";
  // hh_data->GetZaxis()->SetRangeUser(0.0, 0.005);

  TCanvas *canvasModel = new TCanvas(
      ("canvasModel_" + ComposeName(neutral, bachelor, daughters)).c_str(), "",
      1000, 800);
  hh_model->SetStats(0);
  hh_model->Draw("colz");
  hh_model->SetTitle(
      ("B^{" + chargeLabel + "}#rightarrow#font[132]{[}#font[132]{[}" +
       daughtersLabel + "#font[132]{]}_{D^{0}}" + neutralLabel +
       "#font[132]{]}_{D^{*0}}" + bachelorLabel + "^{" + chargeLabel + "}")
          .c_str());
  hh_model->Draw("colz");
  canvasModel->Update();
  canvasModel->SaveAs(
      (path + ComposeName(neutral, bachelor, daughters) + "_2dPDF.pdf")
          .c_str());

  // 2D data plot
  TCanvas *canvasData = new TCanvas(
      ("canvasData_" + ComposeName(neutral, bachelor, daughters)).c_str(), "",
      1000, 800);
  hh_data->SetStats(0);
  hh_data->Draw("colz");
  hh_data->SetTitle(
      ("B^{" + chargeLabel + "}#rightarrow#font[132]{[}#font[132]{[}" +
       daughtersLabel + "#font[132]{]}_{D^{0}}" + neutralLabel +
       "#font[132]{]}_{D^{*0}}" + bachelorLabel + "^{" + chargeLabel + "}")
          .c_str());
  hh_data->Draw("colz");
  canvasData->Update();
  canvasData->SaveAs(
      (path + ComposeName(neutral, bachelor, daughters) + "_2dData.pdf")
          .c_str());

  gStyle->SetTitleOffset(1.2, "Z");
  // Make a histogram with the Poisson stats in each data bin
  TH2F *hh_err =
      new TH2F(("hh_err_" + ComposeName(neutral, bachelor, daughters)).c_str(),
               "", config.buMass().getBins(), config.buMass().getMin(),
               config.buMass().getMax(), config.deltaMass().getBins(),
               config.deltaMass().getMin(), config.deltaMass().getMax());
  for (int i = 0; i < config.buMass().getBins() * config.deltaMass().getBins();
       i++) {
    float n_bin = hh_data->GetBinContent(i);
    float err = sqrt(n_bin);
    hh_err->SetBinContent(i, err);
  }

  // 2D residuals plot (data - PDF)/err
  TCanvas *canvasRes = new TCanvas(
      ("canvasRes_" + ComposeName(neutral, bachelor, daughters)).c_str(), "",
      1000, 800);
  canvasRes->cd();
  TH2F *hh_data_new = (TH2F *)hh_data->Clone();
  hh_data_new->Add(hh_model, -1);
  hh_data_new->Divide(hh_err);
  canvasRes->cd();
  hh_data_new->GetZaxis()->SetTitle("Residual");
  hh_data_new->GetZaxis()->SetRangeUser(-6.0, 6.0);
  hh_data_new->SetStats(0);
  hh_data_new->Draw("colz");
  canvasRes->Update();
  canvasRes->SaveAs(
      (path + ComposeName(neutral, bachelor, daughters) + "_2dResiduals.pdf")
          .c_str());
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
    Plotting1D(*p, chargeVec, config, categories, fittingDataSet, simPdf, result);
    Plotting2D(*p, chargeVec, config, fittingDataSet, simPdf);
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
  // RooMCStudy mcStudy(
  //     simPdf,
  //     RooArgList(config.buMass(), config.deltaMass(), categories.fitting),
  //     RooFit::Binned(true), RooFit::Silence(), RooFit::Extended(),
  //     RooFit::FitOptions(RooFit::Save(true), RooFit::PrintEvalErrors(0)));
  //
  // std::cout << "Created MCStudy object." << std::endl;
  //
  // int nSamples = 1;
  // int nEvtsPerSample = 60000;
  //
  // mcStudy.generate(nSamples, nEvtsPerSample, true);
  //
  // std::cout << "Generated toy events." << std::endl;
  //
  // RooAbsData *toyDataSet = const_cast<RooAbsData *>(mcStudy.genData(0));
  //
  // std::cout << "Retrieved RooDataSet from MCStudy object." << std::endl;
  //
  // FitSimPdfToData(*toyDataSet, simPdf, config, categories, chargeVec, pdfs);

  // Need the number of generated events to be the sum of all predicted yields
  double expectedEvents = simPdf.expectedEvents(categories.fitting);

  RooDataSet *toyDataSet = simPdf.generate(
      RooArgSet(config.buMass(), config.deltaMass(), categories.fitting),
      expectedEvents);

  RooSimultaneous *simPdfFit =
      new RooSimultaneous("simPdfFit", "simPdfFit", categories.fitting);

  simPdfFit = dynamic_cast<RooSimultaneous *>(simPdf.Clone());

    // SET VALUE AWAY FROM REAL VALUE
    // delta_mean_1.setVal(130);

  FitSimPdfToData(*toyDataSet, *simPdfFit, config, categories, chargeVec,
  pdfs);
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
                << " (optional)\n";
      std::cout << "\n";
      std::cout << "To specify multiple options, separate them by commas.\n";
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "\n";

      return 1;
    } else {
      // Data folder
      runToys = args("toys");

      if (!args("dataDir", dataDir) && runToys == false) {
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
