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
#include "GlobalVars.h"
#include "NeutralBachelorDaughtersVars.h"
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
      "pdfSignalHist", 0, 0, 0);
  pdfSignalHist->SetLineColor(kBlue);
  pdfSignalHist->SetLineStyle(kDashed);
  pdfSignalHist->SetLineWidth(2);

  auto pdfCombHist = std::make_unique<TH1D>(
      ("pdfCombHist" + ComposeName(id, neutral, bachelor, daughters)).c_str(),
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
  canvas.SaveAs((path + ComposeName(id, neutral, bachelor, daughters, charge) +
                 "_" + EnumToString(variable) + "Mass.pdf")
                    .c_str());
}

void Plotting1D(int const id, PdfBase &pdf, Configuration &config,
                Configuration::Categories &categories,
                RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                RooFitResult const &result) {
  SetStyle();

  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();

  TLegend legend(0.7, 0.7, 0.97, 0.90);
  // ------------- Draw Legends -------------- //
  auto pdfSignalHist = std::make_unique<TH1D>(
      ("pdfSignalHist" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "pdfSignalHist", 0, 0, 0);
  pdfSignalHist->SetLineColor(kBlue);
  pdfSignalHist->SetLineStyle(kDashed);
  pdfSignalHist->SetLineWidth(2);

  auto pdfCombHist = std::make_unique<TH1D>(
      ("pdfCombHist" + ComposeName(id, neutral, bachelor, daughters, charge))
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
      ("blankHist" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "blankHist", 0, 0, 0);
  blankHist->SetLineColor(kWhite);
  blankHist->SetLineWidth(2);

  TLegend yieldLegend(0.12, 0.6, 0.3, 0.8);

  std::stringstream sigLegend;
  sigLegend << "Signal: "
            << pdf.yieldSignal().getVal()
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

void Plotting2D(int const id, PdfBase &pdf, Configuration &config,
                RooAbsData const &fullDataSet, RooSimultaneous const &simPdf) {
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
  //     ("dataHist2d_" + ComposeName(id, neutral, bachelor, daughters, charge))
  //         .c_str(),
  //     config.buMass(), RooFit::Binning(config.buMass().getBins()),
  //     RooFit::YVar(config.deltaMass(),
  //                  RooFit::Binning(config.deltaMass().getBins())),
  //     RooFit::Cut(("fitting==fitting::" +
  //                  ComposeFittingName(neutral, bachelor, daughters, charge))
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

  // double binWidthXaxis_model = modelHist2d->GetXaxis()->GetBinUpEdge(0) -
  // modelHist2d->GetXaxis()->GetBinLowEdge(0);
  // double binWidthXaxis_data = dataHist2d->GetXaxis()->GetBinUpEdge(0) -
  // dataHist2d->GetXaxis()->GetBinLowEdge(0);
  // std::cout << "\n\n Xaxis Bin width of model hist = " << binWidthXaxis_model
  // << "\n\n";
  // std::cout << "\n\n Xaxis Bin width of data hist = " << binWidthXaxis_data
  // << "\n\n";
  // double binWidthYaxis_model = modelHist2d->GetYaxis()->GetBinUpEdge(0) -
  // modelHist2d->GetYaxis()->GetBinLowEdge(0);
  // double binWidthYaxis_data = dataHist2d->GetYaxis()->GetBinUpEdge(0) -
  // dataHist2d->GetYaxis()->GetBinLowEdge(0);
  // std::cout << "\n\n Yaxis Bin width of model hist = " << binWidthYaxis_model
  // << "\n\n";
  // std::cout << "\n\n Yaxis Bin width of data hist = " << binWidthYaxis_data
  // << "\n\n";

  // Scale model plot to total number of data events
  // PDF not normalized: normalize before scaling to data
  // modelHist2d->Scale(1 / modelHist2d->Integral());
  // std::cout << "\n\n" << modelHist2d->Integral() << "\n\n";
  // modelHist2d->GetZaxis()->SetRangeUser(0.0, 0.005);
  // dataHist2d->Scale(1 / dataHist2d->Integral());
  // std::cout << "\n\n" << dataHist2d->Integral() << "\n\n";
  // dataHist2d->GetZaxis()->SetRangeUser(0.0, 0.005);
  modelHist2d->Scale(dataHist2d->Integral()/modelHist2d->Integral());

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
  canvasModel.Update();
  canvasModel.SaveAs((path +
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
  canvasData.SaveAs((path +
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
  canvasRes.SaveAs((path +
                    ComposeName(id, neutral, bachelor, daughters, charge) +
                    "_2dResiduals.pdf")
                       .c_str());
  std::cout << "end" << std::endl;
}

std::pair<RooSimultaneous *, std::vector<PdfBase *> > MakeSimultaneousPdf(
    int const id, Configuration &config, Configuration::Categories &categories,
    std::vector<Neutral> const &neutralVec,
    std::vector<Daughters> const &daughtersVec) {
  RooSimultaneous *simPdf = new RooSimultaneous(
      ("simPdf_" + std::to_string(id)).c_str(),
      ("simPdf_" + std::to_string(id)).c_str(), categories.fitting);

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
    p->AddToSimultaneousPdf(*simPdf);
  }

  auto p = std::make_pair(simPdf, pdfs);
  return p;
}

void RunSingleToy(Configuration &config, Configuration::Categories &categories,
                  std::vector<Neutral> const &neutralVec,
                  std::vector<Daughters> const &daughtersVec) {
  int id = 0;
  auto p =
      MakeSimultaneousPdf(id, config, categories, neutralVec, daughtersVec);
  auto simPdf = std::unique_ptr<RooSimultaneous>(p.first);
  std::vector<PdfBase *> pdfs = p.second;

  double nEvtsPerToy = simPdf->expectedEvents(categories.fitting);

  auto toyDataSet = std::unique_ptr<RooDataSet>(simPdf->generate(
      RooArgSet(config.buMass(), config.deltaMass(), categories.fitting),
      nEvtsPerToy));

  auto simPdfFit = std::unique_ptr<RooSimultaneous>(
      new RooSimultaneous("simPdfFit", "simPdfFit", categories.fitting));

  simPdfFit = std::unique_ptr<RooSimultaneous>(
      dynamic_cast<RooSimultaneous *>(simPdf->Clone()));

  auto result = std::unique_ptr<RooFitResult>(
      simPdfFit->fitTo(*toyDataSet, RooFit::Extended(kTRUE), RooFit::Save()));

  // Loop over daughters again to plot correct PDFs
  for (auto &p : pdfs) {
    Plotting1D(id, *p, config, categories, *toyDataSet, *simPdf, *result.get());
    Plotting2D(id, *p, config, *toyDataSet, *simPdf);
    std::cout << "damn roofit" << std::endl;
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
  correlationCanvas.SaveAs((path + "CorrelationMatrix.pdf").c_str());
  std::cout << "Save to pdf file.\n";
}

void RunManyToys(Configuration &config, Configuration::Categories &categories,
                 std::vector<Neutral> const &neutralVec,
                 std::vector<Daughters> const &daughtersVec) {
  std::vector<std::unique_ptr<RooFitResult> > resultVec;
  int nToys = 100;

  for (int id = 0; id < nToys; ++id) {
    auto p =
        MakeSimultaneousPdf(id, config, categories, neutralVec, daughtersVec);
    auto simPdf = std::unique_ptr<RooSimultaneous>(p.first);

    double nEvtsPerToy = simPdf->expectedEvents(categories.fitting);
    auto toyDataSet = std::unique_ptr<RooDataSet>(simPdf->generate(
        RooArgSet(config.buMass(), config.deltaMass(), categories.fitting),
        nEvtsPerToy));
    toyDataSet->SetName(("toyDataSet_" + std::to_string(id)).c_str());

    auto simPdfToFit = std::unique_ptr<RooSimultaneous>(new RooSimultaneous(
        ("simPdfFit_" + std::to_string(id)).c_str(),
        ("simPdfFit_" + std::to_string(id)).c_str(), categories.fitting));

    simPdfToFit = std::unique_ptr<RooSimultaneous>(
        dynamic_cast<RooSimultaneous *>(simPdf->Clone()));

    // RooFitResult *result =
    //     simPdfToFit->fitTo(*toyDataSet, RooFit::Extended(kTRUE),
    //     RooFit::Save());
    resultVec.emplace_back(std::unique_ptr<RooFitResult>(simPdfToFit->fitTo(
        *toyDataSet, RooFit::Save(), RooFit::Extended(true))));
    // run 3 toys and look at RooFit result ("v")
  }

  TH1D R_Dst0K_vs_Dst0pi_hist("R_Dst0K_vs_Dst0pi_hist",
                              "R_Dst0K_vs_Dst0pi_hist", 40, 0, 0.15);
  TH1D R_Dst0K_vs_Dst0pi_err_hist("R_Dst0K_vs_Dst0pi_err_hist",
                                  "R_Dst0K_vs_Dst0pi_err_hist", 40, 0, 0.01);
  TH1D R_Dst0K_vs_Dst0pi_pull_hist("R_Dst0K_vs_Dst0pi_pull_hist",
                                   "R_Dst0K_vs_Dst0pi_pull_hist", 40, -10, 10);

  for (int id = 0; id < nToys; ++id) {
    resultVec[id]->Print("v");

    GlobalVars &globalVars = GlobalVars::Get(id);

    RooAbsArg *R_Dst0K_vs_Dst0pi_AbsArg =
        const_cast<RooAbsArg *>(resultVec[id]->floatParsFinal().find(
            globalVars.R_Dst0K_vs_Dst0pi().GetName()));

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
        (R_Dst0K_vs_Dst0pi->getVal() -
         globalVars.R_Dst0K_vs_Dst0pi_predicted()) /
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

    path = "result/";
    int id = 0;
    auto p =
        MakeSimultaneousPdf(id, config, categories, neutralVec, daughtersVec);
    auto simPdf = std::unique_ptr<RooSimultaneous>(p.first);
    auto pdfs = p.second;

    auto result = std::unique_ptr<RooFitResult>(
        simPdf->fitTo(fullDataSet, RooFit::Extended(kTRUE), RooFit::Save()));

    // Loop over daughters again to plot correct PDFs
    for (auto &p : pdfs) {
      Plotting1D(id, *p, config, categories, fullDataSet, *simPdf,
                 *result.get());
      Plotting2D(id, *p, config, fullDataSet, *simPdf);
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
    correlationCanvas.SaveAs((path + "CorrelationMatrix.pdf").c_str());
    std::cout << "Save to pdf file.\n";

  } else {
    path = "toys/";
    RunSingleToy(config, categories, neutralVec, daughtersVec);
    // RunManyToys(config, categories, neutralVec, daughtersVec);
  }

  return 0;
}
