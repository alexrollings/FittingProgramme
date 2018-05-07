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

std::string path;

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

TLegend MakeLegend(TCanvas &canvas, TPad &pad1, TPad &pad2, PdfBase &pdf) {
  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();

  int id = 0;
  canvas.cd();
  pad1.cd();

  TLegend legend(0.7, 0.7, 0.97, 0.90);
  // ------------- Draw Legends -------------- //
  auto pdfSignalHist = std::make_unique<TH1D>(
      ("pdfSignalHist" + ComposeName(id, neutral, bachelor, daughters))
          .c_str(),
      "pdfSignalHist", 0, 0, 0);
  pdfSignalHist->SetLineColor(kBlue);
  pdfSignalHist->SetLineStyle(kDashed);
  pdfSignalHist->SetLineWidth(2);

  auto pdfCombHist = std::make_unique<TH1D>(
      ("pdfCombHist" + ComposeName(id, neutral, bachelor, daughters))
          .c_str(),
      "pdfCombHist", 0, 0, 0);
  pdfCombHist->SetLineColor(kRed);
  pdfCombHist->SetLineStyle(kDashed);
  pdfCombHist->SetLineWidth(2);

  // legend.SetHeader("Physics Backgrounds");
  legend.AddEntry(
      pdfSignalHist.get(),
      ("B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}#font[132]{[}" +
       EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}" +
       EnumToLabel(neutral) + "#font[132]{]}_{D^{0}*}" + EnumToLabel(bachelor) +
       "^{" + EnumToLabel(charge) + "}")
          .c_str(),
      "l");
  legend.AddEntry(pdfCombHist.get(), "Combinatorial", "l");

  return legend;
}

void PlotComponent(Variable variable, RooRealVar &var, PdfBase &pdf,
                   RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                   Configuration::Categories &categories, TLegend &legend,
                   TLegend &yieldLegend) {
  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();
  int id = 0;

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

  // auto hpull = std::unique_ptr<RooHist>(
  //     dynamic_cast<RooHist *>(frame->RooPlot::pullHist()));
  RooHist *hPull = frame->RooPlot::pullHist();

  if (variable == Variable::bu) {
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdfBuSignal()), RooFit::LineStyle(kDashed),
        RooFit::LineColor(kBlue));
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdfBuComb()), RooFit::LineStyle(kDashed),
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
        RooFit::Components(pdf.pdfDeltaSignal()), RooFit::LineStyle(kDashed),
        RooFit::LineColor(kBlue));
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdfDeltaComb()), RooFit::LineStyle(kDashed),
        RooFit::LineColor(kRed));
    frame->SetXTitle("m[D*^{0}] - m[D^{0}] (MeV/c^{2})");
  }

  std::unique_ptr<RooPlot> pullFrame(var.frame(RooFit::Title(" ")));

  pullFrame->addPlotable(hPull /* .get() */, "P");
  pullFrame->SetName(
      ("pullFrame_" + EnumToString(variable) + "_" +
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
  // TLegend legend = MakeLegend(canvas, pad1, pad2, pdf);

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
  canvas.SaveAs((path +
                 ComposeName(id, neutral, bachelor, daughters, charge) +
                 "_" + EnumToString(variable) + "Mass.pdf")
                    .c_str());
}

void Plotting1D(PdfBase &pdf, Configuration &config,
                Configuration::Categories &categories,
                RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                RooFitResult *result) {
  SetStyle();

  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();
  int id = 0;

  TLegend legend(0.7, 0.7, 0.97, 0.90);
  // ------------- Draw Legends -------------- //
  auto pdfSignalHist = std::make_unique<TH1D>(
      ("pdfSignalHist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "pdfSignalHist", 0, 0, 0);
  pdfSignalHist->SetLineColor(kBlue);
  pdfSignalHist->SetLineStyle(kDashed);
  pdfSignalHist->SetLineWidth(2);

  auto pdfCombHist = std::make_unique<TH1D>(
      ("pdfCombHist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "pdfCombHist", 0, 0, 0);
  pdfCombHist->SetLineColor(kRed);
  pdfCombHist->SetLineStyle(kDashed);
  pdfCombHist->SetLineWidth(2);

  // legend.SetHeader("Physics Backgrounds");
  legend.AddEntry(
      pdfSignalHist.get(),
      ("B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}#font[132]{[}" +
       EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}" +
       EnumToLabel(neutral) + "#font[132]{]}_{D^{0}*}" + EnumToLabel(bachelor) +
       "^{" + EnumToLabel(charge) + "}")
          .c_str(),
      "l");
  legend.AddEntry(pdfCombHist.get(), "Combinatorial", "l");

  auto blankHist = std::make_unique<TH1D>(
      ("blankHist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "blankHist", 0, 0, 0);
  blankHist->SetLineColor(kWhite);
  blankHist->SetLineWidth(2);

  TLegend yieldLegend(0.12, 0.6, 0.3, 0.8);

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

  yieldLegend.SetLineColor(kWhite);
  // yieldLegend.AddEntry(blankHist.get(), "#int L dt = 4.8 #pm 0.13 fb^{-1}",
  //                       "l");
  yieldLegend.AddEntry(blankHist.get(), sigLegend.str().c_str(), "l");
  yieldLegend.AddEntry(blankHist.get(), bkgLegend.str().c_str(), "l");

  // ---- PLOTTING FOR BU MASS COMPONENT ---- //
  PlotComponent(Variable::bu, config.buMass(), pdf, fullDataSet, simPdf,
                categories, legend, yieldLegend);
  // ---- PLOTTING FOR DELTA MASS COMPONENT ---- //
  PlotComponent(Variable::delta, config.deltaMass(), pdf, fullDataSet, simPdf,
                categories, legend, yieldLegend);
}

void Plotting2D(PdfBase &pdf, Configuration &config,
                RooAbsData const &fullDataSet, RooSimultaneous const &simPdf) {
  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();
  int id = 0;

  gStyle->SetTitleSize(0.03, "XYZ");
  gStyle->SetLabelSize(0.025, "XYZ");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetTitleOffset(1.5, "Z");
  gStyle->SetPadRightMargin(0.15);

  // Make two-dimensional plot of sampled PDF in x vs y
  // Plot ONLY the PDF not the SimPDF
  RooAbsPdf *singlePdf = simPdf.getPdf(pdf.CategoryName().c_str());
  if (singlePdf == nullptr) {
    throw std::runtime_error("\nSingle pdf empty\n");
  }

  TH1 *hh_model_1D = singlePdf->createHistogram(
      ("hh_model_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      config.buMass(), RooFit::Binning(config.buMass().getBins()),
      RooFit::YVar(config.deltaMass(),
                   RooFit::Binning(config.deltaMass().getBins())));
  if (hh_model_1D == nullptr) {
    throw std::runtime_error("\n1D hist of pdf returns nullptr\n");
  }
  TH2F *hh_model = dynamic_cast<TH2F *>(hh_model_1D);
  if (hh_model == nullptr) {
    throw std::runtime_error("\n2D hist of pdf returns nullptr\n");
  }
  hh_model->SetTitle("");

  // Make 2D plot of data
  // Plot ONLY one component of the data
  TH1 *hh_data_1D = fullDataSet.createHistogram(
      ("hh_data_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      config.buMass(), RooFit::Binning(config.buMass().getBins()),
      RooFit::YVar(config.deltaMass(),
                   RooFit::Binning(config.deltaMass().getBins())),
      RooFit::Cut(("fitting==fitting::" +
                   ComposeFittingName(neutral, bachelor, daughters, charge))
                      .c_str()));
  if (hh_data_1D == nullptr) {
    throw std::runtime_error("\n1D hist of data returns nullptr\n");
  }
  TH2F *hh_data = dynamic_cast<TH2F *>(hh_data_1D);
  if (hh_data == nullptr) {
    throw std::runtime_error("\n2D hist of data returns nullptr\n");
  }
  hh_data->SetTitle("");

  // double binWidthXaxis_model = hh_model->GetXaxis()->GetBinUpEdge(0) -
  // hh_model->GetXaxis()->GetBinLowEdge(0);
  // double binWidthXaxis_data = hh_data->GetXaxis()->GetBinUpEdge(0) -
  // hh_data->GetXaxis()->GetBinLowEdge(0);
  // std::cout << "\n\n Xaxis Bin width of model hist = " << binWidthXaxis_model
  // << "\n\n";
  // std::cout << "\n\n Xaxis Bin width of data hist = " << binWidthXaxis_data
  // << "\n\n";
  // double binWidthYaxis_model = hh_model->GetYaxis()->GetBinUpEdge(0) -
  // hh_model->GetYaxis()->GetBinLowEdge(0);
  // double binWidthYaxis_data = hh_data->GetYaxis()->GetBinUpEdge(0) -
  // hh_data->GetYaxis()->GetBinLowEdge(0);
  // std::cout << "\n\n Yaxis Bin width of model hist = " << binWidthYaxis_model
  // << "\n\n";
  // std::cout << "\n\n Yaxis Bin width of data hist = " << binWidthYaxis_data
  // << "\n\n";

  // Scale model plot to total number of data events
  // PDF not normalized: normalize before scaling to data
  // hh_model->Scale(1 / hh_model->Integral());
  // std::cout << "\n\n" << hh_model->Integral() << "\n\n";
  // hh_model->GetZaxis()->SetRangeUser(0.0, 0.005);
  // hh_data->Scale(1 / hh_data->Integral());
  // std::cout << "\n\n" << hh_data->Integral() << "\n\n";
  // hh_data->GetZaxis()->SetRangeUser(0.0, 0.005);
  hh_model->Scale(hh_data->Integral());

  TCanvas *canvasModel =
      new TCanvas(("canvasModel_" +
                   ComposeName(id, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "", 1000, 800);
  hh_model->SetStats(0);
  hh_model->Draw("colz");
  hh_model->SetTitle(("B^{" + EnumToLabel(charge) +
                      "}#rightarrow#font[132]{[}#font[132]{[}" +
                      EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}" +
                      EnumToLabel(neutral) + "#font[132]{]}_{D^{*0}}" +
                      EnumToLabel(bachelor) + "^{" + EnumToLabel(charge) + "}")
                         .c_str());
  hh_model->Draw("colz");
  canvasModel->Update();
  canvasModel->SaveAs(
      (path + ComposeName(id, neutral, bachelor, daughters, charge) +
       "_2dPDF.pdf")
          .c_str());

  // 2D data plot
  TCanvas *canvasData =
      new TCanvas(("canvasData_" +
                   ComposeName(id, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "", 1000, 800);
  hh_data->SetStats(0);
  hh_data->Draw("colz");
  hh_data->SetTitle(("B^{" + EnumToLabel(charge) +
                     "}#rightarrow#font[132]{[}#font[132]{[}" +
                     EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}" +
                     EnumToLabel(neutral) + "#font[132]{]}_{D^{*0}}" +
                     EnumToLabel(bachelor) + "^{" + EnumToLabel(charge) + "}")
                        .c_str());
  hh_data->Draw("colz");
  canvasData->Update();
  canvasData->SaveAs(
      (path + ComposeName(id, neutral, bachelor, daughters, charge) +
       "_2dData.pdf")
          .c_str());

  gStyle->SetTitleOffset(1.2, "Z");
  // Make a histogram with the Poisson stats in each data bin
  TH2F *hh_err = new TH2F(
      ("hh_err_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
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
  TCanvas *canvasRes =
      new TCanvas(("canvasRes_" +
                   ComposeName(id, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "", 1000, 800);
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
      (path + ComposeName(id, neutral, bachelor, daughters, charge) +
       "_2dResiduals.pdf")
          .c_str());
}

void FitSimPdfToData(RooAbsData &fittingDataSet, RooSimultaneous &simPdf,
                     Configuration &config,
                     Configuration::Categories &categories,
                     std::vector<PdfBase *> &pdfs) {
  RooFitResult *result =
      simPdf.fitTo(fittingDataSet, RooFit::Extended(kTRUE), RooFit::Save());

  // Loop over daughters again to plot correct PDFs
  for (auto &p : pdfs) {
    Plotting1D(*p, config, categories, fittingDataSet, simPdf, result);
    Plotting2D(*p, config, fittingDataSet, simPdf);
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
void MakeSimultaneousPdf(RooAbsData &fullDataSet, Configuration &config,
                         Configuration::Categories &categories,
                         std::vector<Neutral> const &neutralVec,
                         std::vector<Daughters> const &daughtersVec) {
  RooSimultaneous simPdf("simPdf", "simPdf", categories.fitting);

  std::vector<PdfBase *> pdfs;
  int id = 0;

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

            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                                   Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                                   Charge::minus>::Get(id));

            break;

          case Neutral::gamma:

            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                                   Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                                   Charge::minus>::Get(id));

            break;
        }
      }
    } else if (d == Daughters::kk) {
      for (auto &n : neutralVec) {
        switch (n) {
          case Neutral::pi0:

            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                                   Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                                   Charge::minus>::Get(id));

            break;

          case Neutral::gamma:

            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                                   Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                                   Charge::minus>::Get(id));

            break;
        }
      }
    } else if (d == Daughters::pipi) {
      for (auto &n : neutralVec) {
        switch (n) {
          case Neutral::pi0:

            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                                   Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                                   Charge::minus>::Get(id));

            break;

          case Neutral::gamma:

            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                   Daughters::pipi, Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                   Daughters::pipi, Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                                   Charge::minus>::Get(id));

            break;
        }
      }
    } else {
      for (auto &n : neutralVec) {
        switch (n) {
          case Neutral::pi0:

            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                                   Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                                   Charge::minus>::Get(id));

            break;

          case Neutral::gamma:

            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                                   Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                                   Charge::minus>::Get(id));

            break;
        }
      }
    }
  }

  for (auto &p : pdfs) {
    p->AddToSimultaneousPdf(simPdf);
  }

  FitSimPdfToData(fullDataSet, simPdf, config, categories, pdfs);
}

void RunSingleToy(RooSimultaneous &simPdf, Configuration &config,
                  Configuration::Categories &categories,
                  std::vector<PdfBase *> &pdfs) {
  double nEvtsPerToy = simPdf.expectedEvents(categories.fitting);

  RooDataSet *toyDataSet = simPdf.generate(
      RooArgSet(config.buMass(), config.deltaMass(), categories.fitting),
      nEvtsPerToy);

  RooSimultaneous *simPdfFit =
      new RooSimultaneous("simPdfFit", "simPdfFit", categories.fitting);

  simPdfFit = dynamic_cast<RooSimultaneous *>(simPdf.Clone());
  FitSimPdfToData(*toyDataSet, *simPdfFit, config, categories, pdfs);
}

void RunManyToys(RooSimultaneous &simPdf, Configuration &config,
                 Configuration::Categories &categories) {
  RooSimultaneous *simPdfClone =
      new RooSimultaneous("simPdfClone", "simPdfClone", categories.fitting);

  simPdfClone = dynamic_cast<RooSimultaneous *>(simPdf.Clone());

  RooSimultaneous *simPdfToFit =
      new RooSimultaneous("simPdfToFit", "simPdfToFit", categories.fitting);

  // Binned(false) causes seg fault: dataset not datahist?
  RooMCStudy mcStudy(
      simPdf,
      RooArgList(config.buMass(), config.deltaMass(), categories.fitting),
      RooFit::Binned(true), RooFit::Silence(false), RooFit::Extended(true),
      RooFit::FitOptions(RooFit::NumCPU(8, 2), RooFit::Extended(true),
                         RooFit::Optimize(false), RooFit::Offset(true),
                         RooFit::Minimizer("Minuit2", "migrad"),
                         RooFit::Strategy(2)));

  std::cout << "Created MCStudy object." << std::endl;

  int nToys = 3;
  double nEvtsPerToy = simPdf.expectedEvents(categories.fitting);

  mcStudy.generate(nToys, nEvtsPerToy, true);

  // RooDataSet* toyDataSet = nullptr;
  RooAbsData *toyAbsData = nullptr;
  std::vector<RooFitResult *> resultVec;

  for (unsigned int i = 0; i < nToys; ++i) {
    toyAbsData = const_cast<RooAbsData *>(mcStudy.genData(i));
    if (toyAbsData == nullptr) {
      std::stringstream output;
      output << "AbsData number " << i << " in McStudy object empty.\n";
      throw std::runtime_error(output.str());
    }
    // toyDataSet = dynamic_cast<RooDataSet *>(toyAbsData);
    // if (toyDataSet == nullptr) {
    //   std::stringstream output;
    //   output << "Dataset number " << i << " in McStudy object empty.\n";
    //   throw std::runtime_error(output.str());
    // }

    simPdfToFit = dynamic_cast<RooSimultaneous *>(simPdfClone->Clone());

    // RooMsgService::instance().setSilentMode(true);
    // check RooFit result
    resultVec.emplace_back(simPdfToFit->fitTo(
        *toyAbsData, RooFit::Save(), RooFit::NumCPU(8, 2),
        RooFit::Extended(true), RooFit::Optimize(false), RooFit::Offset(true),
        RooFit::Minimizer("Minuit2", "migrad"), RooFit::Strategy(2)));
    // run 3 toys and look at RooFit result ("v")
  }

  TH1D R_Dst0K_vs_Dst0pi_hist("R_Dst0K_vs_Dst0pi_hist",
                              "R_Dst0K_vs_Dst0pi_hist", 40, 0, 0.15);
  TH1D R_Dst0K_vs_Dst0pi_err_hist("R_Dst0K_vs_Dst0pi_err_hist",
                                  "R_Dst0K_vs_Dst0pi_err_hist", 40, 0, 0.01);
  TH1D R_Dst0K_vs_Dst0pi_pull_hist("R_Dst0K_vs_Dst0pi_pull_hist",
                                   "R_Dst0K_vs_Dst0pi_pull_hist", 40, -10, 10);

  for (auto &r : resultVec) {
    r->Print("v");

    RooAbsArg *R_Dst0K_vs_Dst0pi_AbsArg = const_cast<RooAbsArg *>(
        r->floatParsFinal().find(config.R_Dst0K_vs_Dst0pi().GetName()));

    RooRealVar *R_Dst0K_vs_Dst0pi =
        dynamic_cast<RooRealVar *>(R_Dst0K_vs_Dst0pi_AbsArg);
    if (R_Dst0K_vs_Dst0pi == nullptr) {
      std::stringstream output;
      output << "No value found in result.";
      throw std::runtime_error(output.str());
    }

    R_Dst0K_vs_Dst0pi_hist.Fill(R_Dst0K_vs_Dst0pi->getVal());
    R_Dst0K_vs_Dst0pi_err_hist.Fill(R_Dst0K_vs_Dst0pi->getError());
    R_Dst0K_vs_Dst0pi_pull_hist.Fill(
        (R_Dst0K_vs_Dst0pi->getVal() - config.R_Dst0K_vs_Dst0pi_predicted()) /
        R_Dst0K_vs_Dst0pi->getError());
  }

  TCanvas R_Dst0K_vs_Dst0pi_canvas("R_Dst0K_vs_Dst0pi_canvas",
                                   "R_Dst0K_vs_Dst0pi_canvas", 1500, 500);
  R_Dst0K_vs_Dst0pi_canvas.Divide(3, 1);

  R_Dst0K_vs_Dst0pi_canvas.cd(1);
  R_Dst0K_vs_Dst0pi_hist.GetXaxis()->SetTitle("R_Dst0K_vs_Dst0pi");
  R_Dst0K_vs_Dst0pi_hist.SetTitle("");
  R_Dst0K_vs_Dst0pi_hist.Draw();
  R_Dst0K_vs_Dst0pi_canvas.cd(2);
  R_Dst0K_vs_Dst0pi_err_hist.GetXaxis()->SetTitle("R_Dst0K_vs_Dst0pi Error");
  R_Dst0K_vs_Dst0pi_err_hist.SetTitle("");
  R_Dst0K_vs_Dst0pi_err_hist.Draw();
  R_Dst0K_vs_Dst0pi_canvas.cd(3);
  R_Dst0K_vs_Dst0pi_pull_hist.GetXaxis()->SetTitle("R_Dst0K_vs_Dst0pi Pull");
  R_Dst0K_vs_Dst0pi_pull_hist.SetTitle("");
  R_Dst0K_vs_Dst0pi_pull_hist.Draw();

  R_Dst0K_vs_Dst0pi_canvas.SaveAs(
      (path + "hists_R_Dst0K_vs_Dst0pi.pdf").c_str());
}

void MakeSimultaneousPdf(Configuration &config,
                         Configuration::Categories &categories,
                         std::vector<Neutral> const &neutralVec,
                         std::vector<Daughters> const &daughtersVec) {
  RooSimultaneous simPdf("simPdf", "simPdf", categories.fitting);

  std::vector<PdfBase *> pdfs;
  int id = 0;

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

            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                                   Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                                   Charge::minus>::Get(id));

            break;

          case Neutral::gamma:

            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                                   Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                                   Charge::minus>::Get(id));

            break;
        }
      }
    } else if (d == Daughters::kk) {
      for (auto &n : neutralVec) {
        switch (n) {
          case Neutral::pi0:

            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk,
                                   Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kk,
                                   Charge::minus>::Get(id));

            break;

          case Neutral::gamma:

            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                                   Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                                   Charge::minus>::Get(id));

            break;
        }
      }
    } else if (d == Daughters::pipi) {
      for (auto &n : neutralVec) {
        switch (n) {
          case Neutral::pi0:

            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                                   Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                                   Charge::minus>::Get(id));

            break;

          case Neutral::gamma:

            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                   Daughters::pipi, Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                   Daughters::pipi, Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                                   Charge::minus>::Get(id));

            break;
        }
      }
    } else {
      for (auto &n : neutralVec) {
        switch (n) {
          case Neutral::pi0:

            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                                   Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::pik,
                                   Charge::minus>::Get(id));

            break;

          case Neutral::gamma:

            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                                   Charge::plus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                                   Charge::minus>::Get(id));
            pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                                   Charge::minus>::Get(id));

            break;
        }
      }
    }
  }

  // std::string name;
  // RooAbsPdf *singlePdf = nullptr;
  for (auto &p : pdfs) {
    p->AddToSimultaneousPdf(simPdf);
    // singlePdf = simPdf.getPdf(p->CategoryName().c_str());
    // if (singlePdf == nullptr) {
    //   throw std::runtime_error("\nSingle pdf empty\n");
    // }
  }

  // ------------ generate toys ---------------

  // Toy data sets check for bias in our model. The pull distribution should
  // be
  // around 0, i.e. the generated data matches the defined model.

  // Need the number of generated events to be the sum of all predicted yields

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
  // double nEvtsPerToy = simPdf.expectedEvents(categories.fitting);
  //
  // mcStudy.generate(nSamples, nEvtsPerToy, true);
  //
  // std::cout << "Generated toy events." << std::endl;
  //
  // RooAbsData *toyDataSet = const_cast<RooAbsData *>(mcStudy.genData(0));
  //
  // std::cout << "Retrieved RooDataSet from MCStudy object." << std::endl;
  //
  // FitSimPdfToData(*toyDataSet, simPdf, config, categories, pdfs);
  //

  // SET VALUE AWAY FROM REAL VALUE
  // delta_mean_1.setVal(130);
  //
  // Generate toys: remember to set random seed
  // Initialise histograms for pull distributions
  // Loop over nToys
  // Define PDF inside loop, then generate toy dataset from this
  // Save RooFitResults to vector
  // Loop over vector after and fill histograms with values and errors of
  // parameters

  RunSingleToy(simPdf, config, categories, pdfs);
  // RunManyToys(simPdf, config, categories);
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
  std::string dataDir;
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
    std::string chargeArg("true");

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
      std::cout << "    -split=<choice {true/false} default: " << chargeArg
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

      if (!args("split", chargeArg)) {
        std::cout << "Using default value -split=[" << chargeArg << "].\n";
      }
      if (chargeArg == "true") {
        splitbycharge = SplitByCharge::ktrue;
      } else if (chargeArg == "false") {
        splitbycharge = SplitByCharge::kfalse;
      } else {
        std::cerr << "charge assignment failed, please specify split by "
                     "charge: =split=[true/false]";
        return 1;
      }
    }
  }

  int id = 0;
  Configuration &config = Configuration::Get(id);
  Configuration::Categories &categories = Configuration::Get(id).categories();

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

    path = "result/";
    MakeSimultaneousPdf(fullDataSet, config, categories, neutralVec,
                        daughtersVec);

  } else {
    path = "toys/";
    MakeSimultaneousPdf(config, categories, neutralVec, daughtersVec);
  }

  return 0;
}
