#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooCBShape.h"
#include "RooCategory.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooDstD0BG.h"
#include "RooExponential.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooHist.h"
#include "RooPlot.h"
#include "RooPlotable.h"
#include "RooPolyVar.h"
#include "RooProdPdf.h"
#include "RooRandom.h"
#include "RooRealVar.h"
#include "RooSimultaneous.h"
#include "RooTreeData.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TLine.h"
#include "TPad.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TTreeReader.h"

enum class Neutral { pi0, gamma };
enum class Bachelor { pi, k };
enum class Variable { bu, delta };

std::string EnumToString(Neutral neutral) {
  switch (neutral) {
    case Neutral::pi0:
      return "pi0";
      break;
    case Neutral::gamma:
      return "gamma";
      break;
  }
}

std::string EnumToString(Bachelor bachelor) {
  switch (bachelor) {
    case Bachelor::pi:
      return "pi";
      break;
    case Bachelor::k:
      return "k";
      break;
  }
}

std::string EnumToString(Variable variable) {
  switch (variable) {
    case Variable::bu:
      return "bu";
      break;
    case Variable::delta:
      return "delta";
      break;
  }
}

std::string EnumToLabel(Neutral neutral) {
  switch (neutral) {
    case Neutral::pi0:
      return "#pi^{0}";
      break;
    case Neutral::gamma:
      return "#gamma";
      break;
  }
}

std::string EnumToLabel(Bachelor bachelor) {
  switch (bachelor) {
    case Bachelor::pi:
      return "#pi";
      break;
    case Bachelor::k:
      return "K";
      break;
  }
}

std::string FittingName(Neutral neutral, Bachelor bachelor) {
  switch (neutral) {
    case Neutral::pi0:
      switch (bachelor) {
        case Bachelor::pi:
          return "pi0_pi";
          break;
        case Bachelor::k:
          return "pi0_K";
          break;
      }
      break;
    case Neutral::gamma:
      switch (bachelor) {
        case Bachelor::pi:
          return "gamma_pi";
          break;
        case Bachelor::k:
          return "gamma_K";
          break;
      }
      break;
  }
}

void PlotComponent(Neutral neutral, Bachelor bachelor, Variable variable,
                   RooRealVar &var, RooDataHist *dataHist,
                   RooSimultaneous &simPdf, RooCategory &fitting,
                   RooProdPdf &sig, RooAddPdf &bkg,
                   std::string const &outputDir) {
  gStyle->SetTitleFont(132, "XYZ");
  gStyle->SetLabelFont(132, "XYZ");
  gStyle->SetStatFont(132);
  gStyle->SetStatFontSize(0.02);
  gStyle->SetTitleSize(0.08, "Z");
  gStyle->SetTitleSize(0.035, "XY");
  gStyle->SetLabelSize(0.03, "XY");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.5, "Y");
  gStyle->SetTitleOffset(0.95, "Z");
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.1);
  gStyle->SetPadLeftMargin(0.12);

  std::string title;
  switch (variable) {
    case Variable::bu:
      title = "m[D^{*0}" + EnumToLabel(bachelor) + "]";
      break;
    case Variable::delta:
      switch (neutral) {
        case Neutral::gamma:
          title = "m[D^{*0}]-m[D^{0}]";
          break;
        case Neutral::pi0:
          title = "m[D^{*0}]-m[D^{0}] - m[#pi^{0}]";
          break;
      }
      break;
  }

  auto frame =
      std::unique_ptr<RooPlot>(var.frame(RooFit::Title(title.c_str())));

  RooHist *pullHist = nullptr;
  std::unique_ptr<RooPlot> pullFrame(var.frame(RooFit::Title(" ")));

  dataHist->plotOn(
      frame.get(),
      RooFit::Cut(
          ("fitting==fitting::" + FittingName(neutral, bachelor)).c_str()));
  simPdf.plotOn(frame.get(),
                RooFit::Slice(fitting, FittingName(neutral, bachelor).c_str()),
                RooFit::ProjWData(fitting, *dataHist),
                RooFit::LineColor(kBlue));
  pullHist = frame->RooPlot::pullHist();
  simPdf.plotOn(frame.get(),
                RooFit::Slice(fitting, FittingName(neutral, bachelor).c_str()),
                RooFit::ProjWData(fitting, *dataHist),
                RooFit::Components(sig.GetName()), RooFit::LineColor(kBlue),
                RooFit::LineStyle(kDashed));
  simPdf.plotOn(frame.get(),
                RooFit::Slice(fitting, FittingName(neutral, bachelor).c_str()),
                RooFit::ProjWData(fitting, *dataHist),
                RooFit::Components(bkg.GetName()), RooFit::LineColor(kRed),
                RooFit::LineStyle(kDashed));

  dataHist->plotOn(
      frame.get(),
      RooFit::Cut(
          ("fitting==fitting::" + FittingName(neutral, bachelor)).c_str()));

  if (pullHist != 0) {
    pullFrame->addPlotable(pullHist /* .get() */, "P");
    pullFrame->SetName(("pullFrame_" + FittingName(neutral, bachelor)).c_str());
    pullFrame->SetTitle("");
  }

  TCanvas canvas(("canvas_" + EnumToString(variable) + "_" +
                  FittingName(neutral, bachelor))
                     .c_str(),
                 "", 1200, 1000);

  TPad pad1(
      ("pad1_" + EnumToString(variable) + "_" + FittingName(neutral, bachelor))
          .c_str(),
      "", 0.0, 0.14, 1.0, 1.0, kWhite);
  pad1.Draw();

  TPad pad2(
      ("pad2_" + EnumToString(variable) + "_" + FittingName(neutral, bachelor))
          .c_str(),
      "", 0.0, 0.05, 1.0, 0.15, kWhite);
  pad2.Draw();

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
  canvas.Update();
  canvas.SaveAs((outputDir + "/plots/" + FittingName(neutral, bachelor) + "_" +
                 EnumToString(variable) + "Projection.pdf")
                    .c_str());
}

void Plotting2D(Neutral neutral, Bachelor bachelor, RooRealVar &buMass,
                RooRealVar &deltaMass, RooDataHist *dataHist,
                RooSimultaneous &simPdf, RooCategory &fitting,
                std::string const &outputDir) {
  gStyle->SetTitleSize(0.03, "XYZ");
  gStyle->SetLabelSize(0.025, "XYZ");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetTitleOffset(1.5, "Z");
  gStyle->SetPadRightMargin(0.15);

  auto dataHist1d = dataHist->createHistogram(
      ("dataHist2d_" + FittingName(neutral, bachelor)).c_str(), buMass,
      RooFit::Binning(buMass.getBins()),
      RooFit::YVar(deltaMass, RooFit::Binning(deltaMass.getBins())),
      RooFit::Cut(
          ("fitting==fitting::" + FittingName(neutral, bachelor)).c_str()));
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
  TCanvas canvasData(("canvasData_" + FittingName(neutral, bachelor)).c_str(),
                     "", 1000, 800);
  dataHist2d->SetStats(0);
  if (neutral == Neutral::pi0) {
    dataHist2d->GetYaxis()->SetTitle(
        "m[D^{*0} - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
  }
  dataHist2d->SetTitle(("B^{#pm}#rightarrow#font[132]{[}#font[132]{[}K^{#pm}#"
                        "pi^{#mp}#font[132]{]}_{D^{0}}" +
                        EnumToLabel(neutral) + "#font[132]{]}_{D^{*0}}" +
                        EnumToLabel(bachelor) + "^{#pm}")
                           .c_str());
  dataHist2d->Draw("colz");
  canvasData.Update();
  canvasData.SaveAs(
      (outputDir + "/plots/" + FittingName(neutral, bachelor) + "_2dData.pdf")
          .c_str());
  auto singlePdf = simPdf.getPdf(FittingName(neutral, bachelor).c_str());
  if (singlePdf == nullptr) {
    throw std::runtime_error("\nSingle pdf empty\n");
  }

  auto modelHist1d = singlePdf->createHistogram(
      ("modelHist2d_" + FittingName(neutral, bachelor)).c_str(), buMass,
      RooFit::Binning(buMass.getBins()),
      RooFit::YVar(deltaMass, RooFit::Binning(deltaMass.getBins())));
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
  modelHist2d->Scale(dataHist2d->Integral() / modelHist2d->Integral());

  TCanvas canvasModel(("canvasModel_" + FittingName(neutral, bachelor)).c_str(),
                      "", 1000, 800);
  modelHist2d->SetStats(0);
  if (neutral == Neutral::pi0) {
    modelHist2d->GetYaxis()->SetTitle(
        "m[D^{*0} - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
  }
  modelHist2d->SetTitle(("B^{#pm}#rightarrow#font[132]{[}#font[132]{[}K^{#pm}#"
                         "pi^{#mp}#font[132]{]}_{D^{0}}" +
                         EnumToLabel(neutral) + "#font[132]{]}_{D^{*0}}" +
                         EnumToLabel(bachelor) + "^{#pm}")
                            .c_str());
  modelHist2d->Draw("colz");
  modelHist2d->GetZaxis()->SetRangeUser(-0.00001, modelHist2d->GetMaximum());
  canvasModel.Update();
  canvasModel.SaveAs(
      (outputDir + "/plots/" + FittingName(neutral, bachelor) + "_2dPDF.pdf")
          .c_str());

  gStyle->SetTitleOffset(1.2, "Z");
  // Make a histogram with the Poisson stats in each data bin
  auto errHist2d = std::unique_ptr<TH2F>(
      new TH2F(("errHist2d_" + FittingName(neutral, bachelor)).c_str(), "",
               buMass.getBins(), buMass.getMin(), buMass.getMax(),
               deltaMass.getBins(), deltaMass.getMin(), deltaMass.getMax()));
  for (int i = 0; i < buMass.getBins() * deltaMass.getBins(); i++) {
    float n_bin = dataHist2d->GetBinContent(i);
    float err = sqrt(n_bin);
    errHist2d->SetBinContent(i, err);
  }

  // 2D residuals plot (data - PDF)/err
  TCanvas canvasRes(("canvasRes_" + FittingName(neutral, bachelor)).c_str(), "",
                    1000, 800);
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
  if (neutral == Neutral::pi0) {
    resHist2d->GetYaxis()->SetTitle(
        "m[D^{*0} - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
  }
  resHist2d->GetZaxis()->SetTitle("Residual");
  resHist2d->GetZaxis()->SetRangeUser(-6.0, 6.0);
  resHist2d->SetStats(0);
  resHist2d->Draw("colz");
  canvasRes.Update();
  canvasRes.SaveAs((outputDir + "/plots/" + FittingName(neutral, bachelor) +
                    "_2dResiduals.pdf")
                       .c_str());

  // 1D residuals plot (sum over all 2D bins)
  TCanvas canvasRes1d(("canvasRes1d_" + FittingName(neutral, bachelor)).c_str(),
                      "", 1000, 800);
  canvasRes1d.cd();
  TH1F resHist1d(("resHist1d_" + FittingName(neutral, bachelor)).c_str(), "",
                 130, -6, 6);
  for (int i = 0; i < buMass.getBins() * deltaMass.getBins(); i++) {
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
  canvasRes1d.SaveAs((outputDir + "/plots/" + FittingName(neutral, bachelor) +
                      "_1dResiduals.pdf")
                         .c_str());
}

void PlotCorrMatrix(RooFitResult *result, std::string const &outputDir) {
  TCanvas corrCanvas("corrCanvas", "corrCanvas", 1200, 900);
  TH2 *corrHist = result->correlationHist();
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
  corrCanvas.SaveAs((outputDir + "/plots/CorrelationMatrix.pdf").c_str());
}

void GenerateToys(std::string const &outputDir, int nToys, bool toPlot) {
  int bu_low = 5050;
  int bu_high = 5800;
  int delta_low = 60;  // 134;
  int delta_high = 210;

  int bu_nbins = (bu_high - bu_low) / 10;
  int delta_nbins = (delta_high - delta_low) / 3;

  // ---------------------------- Fitting Vars ----------------------------
  RooRealVar buMass("Bu_M_DTF_D0", "m[D^{*0}#pi^{#pm}]", bu_low, bu_high,
                    "MeV/c^{2}");
  RooRealVar deltaMass("Delta_M", "m[D^{*0}] - m[D^{0}]", delta_low, delta_high,
                       "MeV/c^{2}");

  buMass.setBins(bu_nbins);
  deltaMass.setBins(delta_nbins);

  // ---------------------------- Categories ----------------------------
  RooCategory fitting("fitting", "fitting");
  fitting.defineType("pi0_pi");
  fitting.defineType("pi0_K");

  // ---------------------------- Make simPDF for each toy in loop
  // ----------------------------
  for (int i = 0; i < nToys; i++) {
    RooRandom::randomGenerator()->SetSeed(0);
    TRandom3 random(0);
    double randomTag = random.Rndm();

    TFile outputFile(
        (outputDir + "/ResultFile" + std::to_string(randomTag) + ".root")
            .c_str(),
        "recreate");

    // ---------------------------- PDFs ----------------------------
    //
    // ---------------------------- Signal ----------------------------
    //
    // ---------------------------- π/K shared PDFs: Delta
    // ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanDeltaSignal(("meanDeltaSignal_" + std::to_string(i)).c_str(),
                               "", 1.4219e+02);
    // ---------------------------- Sigmas ----------------------------
    RooRealVar sigma1DeltaSignal(
        ("sigma1DeltaSignal_" + std::to_string(i)).c_str(), "", 9.0429e+00);
    RooRealVar sigmaRatioDeltaSignal(
        ("sigmaRatioDeltaSignal_" + std::to_string(i)).c_str(), "", 0.87952);
    RooFormulaVar sigma2DeltaSignal(
        ("sigma2DeltaSignal_" + std::to_string(i)).c_str(), "@0*@1",
        RooArgSet(sigma1DeltaSignal, sigmaRatioDeltaSignal));
    // ---------------------------- Tails ----------------------------
    RooRealVar a1DeltaSignal(("a1DeltaSignal_" + std::to_string(i)).c_str(), "",
                             2.0251e+00);
    RooRealVar a2DeltaSignal(("a2DeltaSignal_" + std::to_string(i)).c_str(), "",
                             -5.9224e-01);
    RooRealVar n1DeltaSignal(("n1DeltaSignal_" + std::to_string(i)).c_str(), "",
                             3.0344e+00);
    RooRealVar n2DeltaSignal(("n2DeltaSignal_" + std::to_string(i)).c_str(), "",
                             4.8427e+00);
    // ---------------------------- PDFs ----------------------------
    // RooGaussian pdfDeltaSignal1(
    //     ("pdfDeltaSignal1_" + std::to_string(i)).c_str(), "", deltaMass,
    //     meanDeltaSignal, sigma1DeltaSignal);
    RooCBShape pdfDeltaSignal1(("pdfDeltaSignal1_" + std::to_string(i)).c_str(),
                               "", deltaMass, meanDeltaSignal,
                               sigma1DeltaSignal, a1DeltaSignal, n1DeltaSignal);
    RooCBShape pdfDeltaSignal2(("pdfDeltaSignal2_" + std::to_string(i)).c_str(),
                               "", deltaMass, meanDeltaSignal,
                               sigma2DeltaSignal, a2DeltaSignal, n2DeltaSignal);
    RooRealVar fracPdf1DeltaSignal(
        ("fracPdf1DeltaSignal_" + std::to_string(i)).c_str(), "", 2.7402e-01);
    RooAddPdf pdfDeltaSignal(("pdfDeltaSignal_" + std::to_string(i)).c_str(),
                             "", RooArgSet(pdfDeltaSignal1, pdfDeltaSignal2),
                             fracPdf1DeltaSignal);

    // ---------------------------- π PDFs: Bu ----------------------------
    // ---------------------------- Signal ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar a0MeanBuSignal(("a0MeanBuSignal_" + std::to_string(i)).c_str(),
                              "", 4.9983e+03);
    RooRealVar a1MeanBuSignal(("a1MeanBuSignal_" + std::to_string(i)).c_str(),
                              "", 2.3119e+00);
    RooRealVar a2MeanBuSignal(("a2MeanBuSignal_" + std::to_string(i)).c_str(),
                              "", -2.3978e-03);
    RooPolyVar meanBuSignal(
        ("meanBuSignal_" + std::to_string(i)).c_str(), "", deltaMass,
        RooArgList(a0MeanBuSignal, a1MeanBuSignal, a2MeanBuSignal));
    // ---------------------------- Sigmas ----------------------------
    RooRealVar a0Sigma1BuSignalPi(
        ("a0Sigma1BuSignalPi_" + std::to_string(i)).c_str(), "", 4.9764e+00);
    RooRealVar a1Sigma1BuSignalPi(
        ("a1Sigma1BuSignalPi_" + std::to_string(i)).c_str(), "", 2.4775e-01);
    RooRealVar a2Sigma1BuSignalPi(
        ("a2Sigma1BuSignalPi_" + std::to_string(i)).c_str(), "", -5.0502e-04);
    RooPolyVar sigma1BuSignalPi(
        ("sigma1BuSignalPi_" + std::to_string(i)).c_str(), "", deltaMass,
        RooArgList(a0Sigma1BuSignalPi, a1Sigma1BuSignalPi, a2Sigma1BuSignalPi));
    RooRealVar a0Sigma2BuSignalPi(
        ("a0Sigma2BuSignalPi_" + std::to_string(i)).c_str(), "", 1.3464e+02);
    RooRealVar a1Sigma2BuSignalPi(
        ("a1Sigma2BuSignalPi_" + std::to_string(i)).c_str(), "", -1.7163e+00);
    RooRealVar a2Sigma2BuSignalPi(
        ("a2Sigma2BuSignalPi_" + std::to_string(i)).c_str(), "", 6.0422e-03);
    RooPolyVar sigma2BuSignalPi(
        ("sigma2BuSignalPi_" + std::to_string(i)).c_str(), "", deltaMass,
        RooArgList(a0Sigma2BuSignalPi, a1Sigma2BuSignalPi, a2Sigma2BuSignalPi));
    // ---------------------------- Tails ----------------------------
    // RooRealVar a1BuSignal(("a1BuSignal_" + std::to_string(i)).c_str(), "",
    //                       2.2666e+00);
    RooRealVar a2BuSignal(("a2BuSignal_" + std::to_string(i)).c_str(), "",
                          -9.3624e-01);
    // RooRealVar n1BuSignal(("n1BuSignal_" + std::to_string(i)).c_str(), "",
    //                       5.6139e-04);
    RooRealVar n2BuSignal(("n2BuSignal_" + std::to_string(i)).c_str(), "",
                          2.4093e+01);
    // ---------------------------- PDFs ----------------------------
    // RooRealVar fracPdf1BuSignal(
    //     ("fracPdf1BuSignal_" + std::to_string(i)).c_str(), "", 8.0963e-02);
    // RooGaussian pdfBuSignalPi1(("pdfBuSignalPi1_" +
    // std::to_string(i)).c_str(),
    //                            "", buMass, meanBuSignal, sigma1BuSignalPi);
    // RooCBShape pdfBuSignalPi1(("pdfBuSignalPi1_" + std::to_string(i)).c_str(),
    //                           "", buMass, meanBuSignal, sigma1BuSignalPi,
    //                           a1BuSignal, n1BuSignal);
    // RooGaussian pdfBuSignalPi2(("pdfBuSignalPi2_" +
    // std::to_string(i)).c_str(),
    //                            "", buMass, meanBuSignal, sigma1BuSignalPi);
    RooCBShape pdfBuSignalPi2(("pdfBuSignalPi2_" + std::to_string(i)).c_str(),
                              "", buMass, meanBuSignal, sigma2BuSignalPi,
                              a2BuSignal, n2BuSignal);
    // RooAddPdf pdfBuSignalPi(("pdfBuSignalPi_" + std::to_string(i)).c_str(), "",
    //                         RooArgSet(pdfBuSignalPi1, pdfBuSignalPi2),
    //                         fracPdf1BuSignal);
    // ---------------------------- π Total PDF ----------------------------
    RooProdPdf pdfSignalPi(("pdfSignalPi_" + std::to_string(i)).c_str(), "",
                           pdfDeltaSignal,
                           RooFit::Conditional(pdfBuSignalPi2, buMass));

    // ---------------------------- K PDFs: Bu ----------------------------
    // ---------------------------- Signal ----------------------------
    // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaRelativeWidthSignal(
        ("sigmaRelativeWidthSignal_" + std::to_string(i)).c_str(), "", 1);
    RooFormulaVar sigma1BuSignalK(
        ("sigma1BuSignalK_" + std::to_string(i)).c_str(), "", "@0*@1",
        RooArgList(sigma1BuSignalPi, sigmaRelativeWidthSignal));
    RooFormulaVar sigma2BuSignalK(
        ("sigma2BuSignalK_" + std::to_string(i)).c_str(), "", "@0*@1",
        RooArgList(sigma2BuSignalPi, sigmaRelativeWidthSignal));
    // ---------------------------- PDFs ----------------------------
    // RooGaussian pdfBuSignalK1(("pdfBuSignalK1_" + std::to_string(i)).c_str(),
    //                           "", buMass, meanBuSignal, sigma1BuSignalK);
    // RooCBShape pdfBuSignalK1(("pdfBuSignalK1_" + std::to_string(i)).c_str(), "",
    //                          buMass, meanBuSignal, sigma1BuSignalK, a1BuSignal,
    //                          n1BuSignal);
    // RooGaussian pdfBuSignalK2(("pdfBuSignalK2_" + std::to_string(i)).c_str(),
    //                           "", buMass, meanBuSignal, sigma1BuSignalK);
    RooCBShape pdfBuSignalK2(("pdfBuSignalK2_" + std::to_string(i)).c_str(), "",
                             buMass, meanBuSignal, sigma2BuSignalK, a2BuSignal,
                             n2BuSignal);
    // RooAddPdf pdfBuSignalK(("pdfBuSignalK_" + std::to_string(i)).c_str(), "",
    //                        RooArgSet(pdfBuSignalK1, pdfBuSignalK2),
    //                        fracPdf1BuSignal);
    // ---------------------------- K Total PDF ----------------------------
    RooProdPdf pdfSignalK(("pdfSignalK_" + std::to_string(i)).c_str(), "",
                          pdfDeltaSignal,
                          RooFit::Conditional(pdfBuSignalK2, buMass));

    // ---------------------------- Background ----------------------------
    //
    // ---------------------------- π/K shared PDFs: Delta
    // ----------------------------
    RooRealVar threshold1DeltaBkg(
        ("threshold1DeltaBkg_" + std::to_string(i)).c_str(), "", 5.2160e+01);
    RooRealVar c1DeltaBkg(("c1DeltaBkg_" + std::to_string(i)).c_str(), "",
                          4.2450e+01);
    RooRealVar a1DeltaBkg(("a1DeltaBkg_" + std::to_string(i)).c_str(), "",
                          1.0341e+00);
    RooRealVar b1DeltaBkg(("b1DeltaBkg_" + std::to_string(i)).c_str(), "",
                          -1.2284e+00);
    RooDstD0BG pdf1DeltaBkg(("pdf1DeltaBkg_" + std::to_string(i)).c_str(), "",
                            deltaMass, threshold1DeltaBkg, c1DeltaBkg,
                            a1DeltaBkg, b1DeltaBkg);
    RooRealVar threshold2DeltaBkg(
        ("threshold2DeltaBkg_" + std::to_string(i)).c_str(), "", 6.7237e+01);
    RooRealVar c2DeltaBkg(("c2DeltaBkg_" + std::to_string(i)).c_str(), "",
                          4.7874e+01);
    RooRealVar a2DeltaBkg(("a2DeltaBkg_" + std::to_string(i)).c_str(), "",
                          8.8301e-01);
    RooRealVar b2DeltaBkg(("b2DeltaBkg_" + std::to_string(i)).c_str(), "",
                          -9.9972e-01);
    RooDstD0BG pdf2DeltaBkg(("pdf2DeltaBkg_" + std::to_string(i)).c_str(), "",
                            deltaMass, threshold2DeltaBkg, c2DeltaBkg,
                            a2DeltaBkg, b2DeltaBkg);

    // RooRealVar lambdaDeltaBkg(
    //     ("lambdaDeltaBkg_" + std::to_string(i)).c_str(), "", 0.01);
    // RooExponential pdfDeltaBkg(("pdfDeltaBkg_" + std::to_string(i)).c_str(),
    // "",
    //                            deltaMass, lambdaDeltaBkg);
    // ---------------------------- π PDFs: Bu ----------------------------
    RooRealVar a0Mean1BuBkg(("a0Mean1BuBkg_" + std::to_string(i)).c_str(), "",
                            5.0873e+03);
    RooRealVar a1Mean1BuBkg(("a1Mean1BuBkg_" + std::to_string(i)).c_str(), "",
                            2.4822e+00);
    RooRealVar a2Mean1BuBkg(("a2Mean1BuBkg_" + std::to_string(i)).c_str(), "",
                            -6.5217e-03);
    RooPolyVar mean1BuBkg(("mean1BuBkg_" + std::to_string(i)).c_str(), "",
                          deltaMass,
                          RooArgList(a0Mean1BuBkg, a1Mean1BuBkg, a2Mean1BuBkg));
    RooRealVar a0Mean2BuBkg(("a0Mean2BuBkg_" + std::to_string(i)).c_str(), "",
                            5.2623e+03);
    RooRealVar a1Mean2BuBkg(("a1Mean2BuBkg_" + std::to_string(i)).c_str(), "",
                            -1.1142e+00);
    RooRealVar a2Mean2BuBkg(("a2Mean2BuBkg_" + std::to_string(i)).c_str(), "",
                            5.1761e-03);
    RooPolyVar mean2BuBkg(("mean2BuBkg_" + std::to_string(i)).c_str(), "",
                          deltaMass,
                          RooArgList(a0Mean2BuBkg, a1Mean2BuBkg, a2Mean2BuBkg));
    // ---------------------------- Sigmas ----------------------------
    RooRealVar a0Sigma1BuBkgPi(("a0Sigma1BuBkgPi_" + std::to_string(i)).c_str(),
                               "", 1.2821e+01);
    RooRealVar a1Sigma1BuBkgPi(("a1Sigma1BuBkgPi_" + std::to_string(i)).c_str(),
                               "", 5.1122e-01);
    RooRealVar a2Sigma1BuBkgPi(("a2Sigma1BuBkgPi_" + std::to_string(i)).c_str(),
                               "", -2.1553e-04);
    RooPolyVar sigma1BuBkgPi(
        ("sigma1BuBkgPi_" + std::to_string(i)).c_str(), "", deltaMass,
        RooArgList(a0Sigma1BuBkgPi, a1Sigma1BuBkgPi, a2Sigma1BuBkgPi));
    RooRealVar a0Sigma2BuBkgPi(("a0Sigma2BuBkgPi_" + std::to_string(i)).c_str(),
                               "", -8.4602e+01);
    RooRealVar a1Sigma2BuBkgPi(("a1Sigma2BuBkgPi_" + std::to_string(i)).c_str(),
                               "", 2.4802e+00);
    RooRealVar a2Sigma2BuBkgPi(("a2Sigma2BuBkgPi_" + std::to_string(i)).c_str(),
                               "", -6.8355e-03);
    RooPolyVar sigma2BuBkgPi(
        ("sigma2BuBkgPi_" + std::to_string(i)).c_str(), "", deltaMass,
        RooArgList(a0Sigma2BuBkgPi, a1Sigma2BuBkgPi, a2Sigma2BuBkgPi));
    // ---------------------------- Tails ----------------------------
    RooRealVar a1BuBkg(("a1BuBkg_" + std::to_string(i)).c_str(), "",
                       2.5926e+00);
    RooRealVar n1BuBkg(("n1BuBkg_" + std::to_string(i)).c_str(), "",
                       2.4846e-01);
    RooRealVar a2BuBkg(("a2BuBkg_" + std::to_string(i)).c_str(), "",
                       1.2916e+00);
    RooRealVar n2BuBkg(("n2BuBkg_" + std::to_string(i)).c_str(), "",
                       3.4602e+00);
    // ---------------------------- PDFs ----------------------------
    // RooGaussian pdf1BuBkgPi(("pdf1BuBkgPi_" + std::to_string(i)).c_str(), "",
    //                        buMass, mean1BuBkg, sigma1BuBkgPi);
    RooCBShape pdf1BuBkgPi(("pdf1BuBkgPi_" + std::to_string(i)).c_str(), "",
                           buMass, mean1BuBkg, sigma1BuBkgPi, a1BuBkg, n1BuBkg);
    // RooGaussian pdf2BuBkgPi(("pdf2BuBkgPi_" + std::to_string(i)).c_str(), "",
    //                        buMass, mean2BuBkg, sigma2BuBkgPi);
    RooCBShape pdf2BuBkgPi(("pdf2BuBkgPi_" + std::to_string(i)).c_str(), "",
                           buMass, mean2BuBkg, sigma2BuBkgPi, a2BuBkg, n2BuBkg);
    // ---------------------------- π Total PDF ----------------------------
    RooProdPdf pdf1BkgPi(("pdf1BkgPi_" + std::to_string(i)).c_str(), "",
                         pdf1DeltaBkg,
                         RooFit::Conditional(pdf1BuBkgPi, buMass));
    RooProdPdf pdf2BkgPi(("pdf2BkgPi_" + std::to_string(i)).c_str(), "",
                         pdf2DeltaBkg,
                         RooFit::Conditional(pdf2BuBkgPi, buMass));
    RooRealVar fracPdf1Bkg(("fracPdf1Bkg_" + std::to_string(i)).c_str(), "",
                           0.714, 0, 1);
    RooAddPdf pdfBkgPi(("pdfBkgPi_" + std::to_string(i)).c_str(), "",
                       RooArgSet(pdf1BkgPi, pdf2BkgPi), fracPdf1Bkg);

    // ---------------------------- K PDFs: Bu ----------------------------
    // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaRelativeWidthBkg(
        ("sigmaRelativeWidthBkg_" + std::to_string(i)).c_str(), "", 1);
    RooFormulaVar sigma1BuBkgK(
        ("sigma1BuBkgK_" + std::to_string(i)).c_str(), "", "@0*@1",
        RooArgList(sigma1BuBkgPi, sigmaRelativeWidthBkg));
    RooFormulaVar sigma2BuBkgK(
        ("sigma2BuBkgK_" + std::to_string(i)).c_str(), "", "@0*@1",
        RooArgList(sigma2BuBkgPi, sigmaRelativeWidthBkg));
    // ---------------------------- PDFs ----------------------------
    // RooGaussian pdf1BuBkgK(("pdf1BuBkgK_" + std::to_string(i)).c_str(), "",
    //                       buMass, mean1BuBkg, sigma1BuBkgK);
    RooCBShape pdf1BuBkgK(("pdf1BuBkgK_" + std::to_string(i)).c_str(), "",
                          buMass, mean1BuBkg, sigma1BuBkgK, a1BuBkg, n1BuBkg);
    // RooGaussian pdf2BuBkgK(("pdf2BuBkgK_" + std::to_string(i)).c_str(), "",
    //                       buMass, mean2BuBkg, sigma2BuBkgK);
    RooCBShape pdf2BuBkgK(("pdf2BuBkgK_" + std::to_string(i)).c_str(), "",
                          buMass, mean2BuBkg, sigma2BuBkgK, a2BuBkg, n2BuBkg);
    // ---------------------------- K Total PDF ----------------------------
    RooProdPdf pdf1BkgK(("pdf1BkgK_" + std::to_string(i)).c_str(), "",
                        pdf1DeltaBkg, RooFit::Conditional(pdf1BuBkgK, buMass));
    RooProdPdf pdf2BkgK(("pdf2BkgK_" + std::to_string(i)).c_str(), "",
                        pdf2DeltaBkg, RooFit::Conditional(pdf2BuBkgK, buMass));
    RooAddPdf pdfBkgK(("pdfBkgK_" + std::to_string(i)).c_str(), "",
                      RooArgSet(pdf1BkgK, pdf2BkgK), fracPdf1Bkg);

    // ---------------------------- Yields ----------------------------
    RooRealVar yieldSignalPi(("yieldSignalPi_" + std::to_string(i)).c_str(), "",
                             // 3000, 1000, 9000);
                             40000, 20000, 60000);
    RooRealVar yieldBkgPi(("yieldBkgPi_" + std::to_string(i)).c_str(), "",
                          // 7000, 1000, 9000);
                          100000, 70000, 130000);
    RooRealVar yieldRatioSignal(
        ("yieldRatioSignal_" + std::to_string(i)).c_str(), "", 0.07930, 0, 1);
    RooFormulaVar yieldSignalK(("yieldSignalK_" + std::to_string(i)).c_str(),
                               "", "@0*@1",
                               RooArgList(yieldSignalPi, yieldRatioSignal));
    RooRealVar yieldRatioBkg(("yieldRatioBkg_" + std::to_string(i)).c_str(), "",
                             0.05, 0, 1);
    RooFormulaVar yieldBkgK(("yieldBkgK_" + std::to_string(i)).c_str(), "",
                            "@0*@1", RooArgList(yieldBkgPi, yieldRatioBkg));

    // ---------------------------- Add PDFs and yields
    // ----------------------------
    RooArgSet yieldsPi;
    yieldsPi.add(yieldSignalPi);
    yieldsPi.add(yieldBkgPi);
    RooArgSet functionsPi;
    functionsPi.add(pdfSignalPi);
    functionsPi.add(pdfBkgPi);
    RooAddPdf pdfPi(("pdfPi_" + std::to_string(i)).c_str(), "", functionsPi,
                    yieldsPi);

    RooArgSet yieldsK;
    yieldsK.add(yieldSignalK);
    yieldsK.add(yieldBkgK);
    RooArgSet functionsK;
    functionsK.add(pdfSignalK);
    functionsK.add(pdfBkgK);
    RooAddPdf pdfK(("pdfK_" + std::to_string(i)).c_str(), "", functionsK,
                   yieldsK);

    // ---------------------------- Construct Sim PDF
    // ----------------------------
    RooSimultaneous simPdf(("simPdf_" + std::to_string(i)).c_str(), "",
                           fitting);
    simPdf.addPdf(pdfPi, "pi0_pi");
    simPdf.addPdf(pdfK, "pi0_K");

    double nEvtsPerToy = simPdf.expectedEvents(fitting);
    std::cout << "Generating toy dataset..." << std::endl;

    // ---------------------------- Generate toy dataset
    // ----------------------------
    RooDataSet *toyDataSet =
        simPdf.generate(RooArgSet(buMass, deltaMass, fitting), nEvtsPerToy);
    std::cout << "Generated!" << std::endl;
    toyDataSet->SetName(("toyDataSet_" + std::to_string(i)).c_str());
    auto toyDataHist = std::unique_ptr<RooDataHist>(
        toyDataSet->binnedClone(("toyDataHist_" + std::to_string(i)).c_str(),
                                ("toyDataHist" + std::to_string(i)).c_str()));
    auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

    // meanDeltaSignal.setVal(142);

    RooFitResult *result = 0;
    // ---------------------------- Fit Sim PDF to toy
    // ----------------------------
    result = simPdf.fitTo(*toyAbsData, RooFit::Save(true));

    // ---------------------------- Save result to file
    // ----------------------------
    outputFile.cd();
    result->SetName(("Result" + std::to_string(randomTag)).c_str());
    result->Print("v");
    result->Write();
    outputFile.Close();

    std::cout << "Result saved in file " << outputDir << "/ResultFile"
              << std::to_string(randomTag) << ".root\n";

    // ---------------------------- Plot if specified
    // ----------------------------
    if (toPlot == true && i == 0) {
      std::cout << "Plotting projections of m[Bu]\n";
      PlotComponent(Neutral::pi0, Bachelor::pi, Variable::bu, buMass,
                    toyDataHist.get(), simPdf, fitting, pdfSignalPi, pdfBkgPi,
                    outputDir);
      PlotComponent(Neutral::pi0, Bachelor::k, Variable::bu, buMass,
                    toyDataHist.get(), simPdf, fitting, pdfSignalK, pdfBkgK,
                    outputDir);
      std::cout << "Plotting projections of m[Delta]\n";
      PlotComponent(Neutral::pi0, Bachelor::pi, Variable::delta, deltaMass,
                    toyDataHist.get(), simPdf, fitting, pdfSignalPi, pdfBkgPi,
                    outputDir);
      PlotComponent(Neutral::pi0, Bachelor::k, Variable::delta, deltaMass,
                    toyDataHist.get(), simPdf, fitting, pdfSignalK, pdfBkgK,
                    outputDir);
      std::cout << "Plotting in 2D\n";
      Plotting2D(Neutral::pi0, Bachelor::pi, buMass, deltaMass,
                 toyDataHist.get(), simPdf, fitting, outputDir);
      Plotting2D(Neutral::pi0, Bachelor::k, buMass, deltaMass,
                 toyDataHist.get(), simPdf, fitting, outputDir);
      std::cout << "Plotting correlation matrix\n";
      PlotCorrMatrix(result, outputDir);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Enter output directory and number of toys. Optional argument "
                 "to plot toys = plot\n";
    return 1;
  }
  std::string outputDir = argv[1];
  int nToys = std::atoi(argv[2]);
  bool toPlot = false;
  if (argc == 4) {
    std::string plotString = argv[3];
    if (plotString == "plot") {
      toPlot = true;
    } else {
      std::cout << "Not plotting: if desired, specify plot as third argument\n";
    }
  }
  GenerateToys(outputDir, nToys, toPlot);
  return 0;
}
