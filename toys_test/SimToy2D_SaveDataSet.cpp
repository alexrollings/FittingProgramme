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

enum class Variable { bu, delta };

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

void PlotComponent(Variable variable, RooRealVar &var, RooDataHist *dataHist,
                   RooAddPdf &pdf, RooAbsPdf &sig, RooAbsPdf &bkg1,
                   RooAbsPdf &bkg2, RooAbsPdf &bkg3, RooAbsPdf &bkg4,
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
      title = "m[D^{*0}#pi] - m[D^{*0}]";
      break;
    case Variable::delta:
      title = "m[D^{*0}]-m[D^{0}]";
      break;
  }

  auto frame =
      std::unique_ptr<RooPlot>(var.frame(RooFit::Title(title.c_str())));

  RooHist *pullHist = nullptr;
  std::unique_ptr<RooPlot> pullFrame(var.frame(RooFit::Title(" ")));

  dataHist->plotOn(frame.get());
  pdf.plotOn(frame.get(), RooFit::LineColor(kBlue));
  pullHist = frame->RooPlot::pullHist();
  pdf.plotOn(frame.get(), RooFit::Components(sig.GetName()),
             RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed));
  pdf.plotOn(frame.get(), RooFit::Components(bkg1.GetName()),
             RooFit::LineColor(kRed), RooFit::LineStyle(kDashed));
  pdf.plotOn(frame.get(), RooFit::Components(bkg2.GetName()),
             RooFit::LineColor(kOrange), RooFit::LineStyle(kDashed));
  pdf.plotOn(frame.get(), RooFit::Components(bkg3.GetName()),
             RooFit::LineColor(kGreen), RooFit::LineStyle(kDashed));
  pdf.plotOn(frame.get(), RooFit::Components(bkg4.GetName()),
             RooFit::LineColor(kMagenta), RooFit::LineStyle(kDashed));

  dataHist->plotOn(frame.get());

  if (pullHist != 0) {
    pullFrame->addPlotable(pullHist /* .get() */, "P");
    pullFrame->SetName("pullFrame");
    pullFrame->SetTitle("");
  }

  TCanvas canvas(("canvas_" + EnumToString(variable)).c_str(), "", 1200, 1000);

  TPad pad1(("pad1_" + EnumToString(variable)).c_str(), "", 0.0, 0.14, 1.0, 1.0,
            kWhite);
  pad1.Draw();

  TPad pad2(("pad2_" + EnumToString(variable)).c_str(), "", 0.0, 0.05, 1.0,
            0.15, kWhite);
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
  canvas.SaveAs(
      (outputDir + "/2d_plots/" + EnumToString(variable) + "Projection.pdf")
          .c_str());
}

void Plotting2D(RooRealVar &buMass, RooRealVar &deltaMass,
                RooDataHist *dataHist, RooAddPdf &pdf,
                std::string const &outputDir) {
  gStyle->SetTitleSize(0.03, "XYZ");
  gStyle->SetLabelSize(0.025, "XYZ");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetTitleOffset(1.5, "Z");
  gStyle->SetPadRightMargin(0.15);

  auto dataHist1d = dataHist->createHistogram(
      "dataHist2d", buMass, RooFit::Binning(buMass.getBins()),
      RooFit::YVar(deltaMass, RooFit::Binning(deltaMass.getBins())));
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
  TCanvas canvasData("canvasData", "", 1000, 800);
  dataHist2d->SetStats(0);
  dataHist2d->SetTitle(
      "B^{#pm}#rightarrow#font[132]{[}#font[132]{[}K^{#pm}#"
      "pi^{#mp}#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{*0}}#pi^{#pm}");
  dataHist2d->Draw("colz");
  canvasData.Update();
  canvasData.SaveAs((outputDir + "/2d_plots/2dData.pdf").c_str());

  auto modelHist1d = pdf.createHistogram(
      "modelHist2d", buMass, RooFit::Binning(buMass.getBins()),
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

  TCanvas canvasModel("canvasModel", "", 1000, 800);
  modelHist2d->SetStats(0);
  modelHist2d->SetTitle(
      "B^{#pm}#rightarrow#font[132]{[}#font[132]{[}K^{#pm}#"
      "pi^{#mp}#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{*0}}#pi^{#pm}");
  modelHist2d->Draw("colz");
  modelHist2d->GetZaxis()->SetRangeUser(-0.00001, modelHist2d->GetMaximum());
  canvasModel.Update();
  canvasModel.SaveAs((outputDir + "/2d_plots/2dPDF.pdf").c_str());

  gStyle->SetTitleOffset(1.2, "Z");
  // Make a histogram with the Poisson stats in each data bin
  auto errHist2d = std::unique_ptr<TH2F>(new TH2F(
      "errHist2d", "", buMass.getBins(), buMass.getMin(), buMass.getMax(),
      deltaMass.getBins(), deltaMass.getMin(), deltaMass.getMax()));
  for (int i = 0; i < buMass.getBins() * deltaMass.getBins(); i++) {
    float n_bin = dataHist2d->GetBinContent(i);
    float err = sqrt(n_bin);
    errHist2d->SetBinContent(i, err);
  }

  // 2D residuals plot (data - PDF)/err
  TCanvas canvasRes("canvasRes", "", 1000, 800);
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
  canvasRes.SaveAs((outputDir + "/2d_plots/2dResiduals.pdf").c_str());

  // 1D residuals plot (sum over all 2D bins)
  TCanvas canvasRes1d("canvasRes1d", "", 1000, 800);
  canvasRes1d.cd();
  TH1F resHist1d("resHist1d", "", 130, -6, 6);
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
  canvasRes1d.SaveAs((outputDir + "/2d_plots/1dResiduals.pdf").c_str());
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
  corrHist->SetLabelSize(0.04, "XY");
  corrHist->SetLabelSize(0.02, "Z");
  corrHist->Draw("colz");
  corrCanvas.Update();
  corrCanvas.SaveAs((outputDir + "/2d_plots/CorrelationMatrix.pdf").c_str());
}

void GenerateToys(std::string const &outputDir, int nToys) {
  int bu_low = 5050;
  int bu_high = 5800;
  int delta_low = 60;  // 134;
  int delta_high = 210;

  int bu_nbins = (bu_high - bu_low) / 10;
  int delta_nbins = (delta_high - delta_low) / 2;

  // ---------------------------- Fitting Vars ----------------------------
  RooRealVar buMass("Bu_Delta_M", "m[D^{*0}#pi^{#pm}] - m[D^{*0}]", bu_low,
                    bu_high, "MeV/c^{2}");
  RooRealVar deltaMass("Delta_M", "m[D^{*0}] - m[D^{0}]", delta_low, delta_high,
                       "MeV/c^{2}");

  buMass.setBins(bu_nbins);
  deltaMass.setBins(delta_nbins);

  for (int i = 0; i < nToys; i++) {
    RooRandom::randomGenerator()->SetSeed(0);
    TRandom3 random(0);

    // ---------------------------- PDFs ----------------------------
    //
    // ---------------------------- Signal ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanDeltaSignal("meanDeltaSignal", "",
                               1.4256e+02);  //, 135, 150);
    // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaDeltaSignal("sigmaDeltaSignal", "",
                                8.4647e+00);  //, 5, 15);
    // ---------------------------- Tails ----------------------------
    RooRealVar a1DeltaSignal("a1DeltaSignal", "", 1.6783e+00);
    RooRealVar a2DeltaSignal("a2DeltaSignal", "", -5.6685e-01);
    RooRealVar n1DeltaSignal("n1DeltaSignal", "", 4.1125e+00);
    RooRealVar n2DeltaSignal("n2DeltaSignal", "", 4.4286e+00);
    // ---------------------------- PDFs ----------------------------
    RooCBShape pdfDeltaSignal1("pdfDeltaSignal1", "", deltaMass,
                               meanDeltaSignal, sigmaDeltaSignal, a1DeltaSignal,
                               n1DeltaSignal);
    RooCBShape pdfDeltaSignal2("pdfDeltaSignal2", "", deltaMass,
                               meanDeltaSignal, sigmaDeltaSignal, a2DeltaSignal,
                               n2DeltaSignal);
    RooRealVar fracPdf1DeltaSignal("fracPdf1DeltaSignal", "", 2.8510e-01);
    RooAddPdf pdfDeltaSignal("pdfDeltaSignal", "",
                             RooArgSet(pdfDeltaSignal1, pdfDeltaSignal2),
                             fracPdf1DeltaSignal);

    // ---------------------------- π PDFs: Bu ----------------------------
    // ---------------------------- Signal ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar a0MeanBuSignal("a0MeanBuSignal", "",
                              5.1774e+03);  //, 4500, 5500);
    RooRealVar a1MeanBuSignal("a1MeanBuSignal", "", 8.9919e-01);  //, -10, 10);
    RooRealVar a2MeanBuSignal("a2MeanBuSignal", "",
                              -1.2149e-03);  //, -0.1, 0.1);
    RooPolyVar meanBuSignal(
        "meanBuSignal", "", deltaMass,
        RooArgList(a0MeanBuSignal, a1MeanBuSignal, a2MeanBuSignal));
    // ---------------------------- Sigmas ----------------------------
    RooRealVar a0SigmaBuSignal("a0SigmaBuSignal", "",
                               2.8951e+02);  //, 300, 400);
    RooRealVar a1SigmaBuSignal("a1SigmaBuSignal", "",
                               -3.4700e+00);  //, -10, 10);
    RooRealVar a2SigmaBuSignal("a2SigmaBuSignal", "", 1.2303e-02);

    RooPolyVar sigma1BuSignal(
        "sigma1BuSignal", "", deltaMass,
        RooArgList(a0SigmaBuSignal, a1SigmaBuSignal, a2SigmaBuSignal));

    RooRealVar sigma21FracBuSignal("sigma21FracBuSignal", "",
                                   4.1625e-01);  //, -1, 1);

    RooFormulaVar sigma2BuSignal(
        "sigma2BuSignal", "", "@0*@1",
        RooArgSet(sigma1BuSignal, sigma21FracBuSignal));

    // ---------------------------- PDFs ----------------------------
    RooRealVar fracPdf1BuSignal("fracPdf1BuSignal", "", 6.3427e-02);
    RooGaussian pdfBuSignal1("pdfBuSignal1", "", buMass, meanBuSignal,
                             sigma1BuSignal);
    RooGaussian pdfBuSignal2("pdfBuSignal2", "", buMass, meanBuSignal,
                             sigma2BuSignal);
    RooAddPdf pdfBuSignal("pdfBuSignal", "",
                          RooArgSet(pdfBuSignal1, pdfBuSignal2),
                          fracPdf1BuSignal);
    // ---------------------------- π Total PDF ----------------------------
    RooProdPdf pdfSignal("pdfSignal", "", pdfDeltaSignal,
                         RooFit::Conditional(pdfBuSignal, buMass));

    // ---------------------------- Bu2Dst0pi_D0pi0 Background
    // ----------------------------
    // ---------------------------- Peaking Background
    // ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanDeltaBu2Dst0pi_D0pi0("meanDeltaBu2Dst0pi_D0pi0", "",
                                        8.6146e+01);  //, 135, 150);
    // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaDeltaBu2Dst0pi_D0pi0("sigmaDeltaBu2Dst0pi_D0pi0", "",
                                         9.5986e+00);  //, 5, 15);
    // ---------------------------- Tails ----------------------------
    RooRealVar a1DeltaBu2Dst0pi_D0pi0("a1DeltaBu2Dst0pi_D0pi0", "", 2.4446e-01);
    RooRealVar a2DeltaBu2Dst0pi_D0pi0("a2DeltaBu2Dst0pi_D0pi0", "",
                                      -5.3368e-01);
    RooRealVar n1DeltaBu2Dst0pi_D0pi0("n1DeltaBu2Dst0pi_D0pi0", "", 3.6208e+01);
    RooRealVar n2DeltaBu2Dst0pi_D0pi0("n2DeltaBu2Dst0pi_D0pi0", "", 6.7095e+00);
    // ---------------------------- PDFs ----------------------------
    RooCBShape pdfDeltaBu2Dst0pi_D0pi01(
        "pdfDeltaBu2Dst0pi_D0pi01", "", deltaMass, meanDeltaBu2Dst0pi_D0pi0,
        sigmaDeltaBu2Dst0pi_D0pi0, a1DeltaBu2Dst0pi_D0pi0,
        n1DeltaBu2Dst0pi_D0pi0);
    RooCBShape pdfDeltaBu2Dst0pi_D0pi02(
        "pdfDeltaBu2Dst0pi_D0pi02", "", deltaMass, meanDeltaBu2Dst0pi_D0pi0,
        sigmaDeltaBu2Dst0pi_D0pi0, a2DeltaBu2Dst0pi_D0pi0,
        n2DeltaBu2Dst0pi_D0pi0);
    RooRealVar fracPdf1DeltaBu2Dst0pi_D0pi0("fracPdf1DeltaBu2Dst0pi_D0pi0", "",
                                            3.0425e-01);
    RooAddPdf pdfDeltaBu2Dst0pi_D0pi0(
        "pdfDeltaBu2Dst0pi_D0pi0", "",
        RooArgSet(pdfDeltaBu2Dst0pi_D0pi01, pdfDeltaBu2Dst0pi_D0pi02),
        fracPdf1DeltaBu2Dst0pi_D0pi0);
    // ---------------------------- π/K shared PDFs: Bu
    // ----------------------------
    RooRealVar a0Mean1BuBu2Dst0pi_D0pi0("a0Mean1BuBu2Dst0pi_D0pi0", "",
                                         5.1622e+03);  //, 4500, 5500);
    RooRealVar a1Mean1BuBu2Dst0pi_D0pi0("a1Mean1BuBu2Dst0pi_D0pi0", "",
                                         1.7761e+00);  //, -10, 10);
    RooRealVar a2Mean1BuBu2Dst0pi_D0pi0("a2Mean1BuBu2Dst0pi_D0pi0", "",
                                         -2.9948e-03);  //, -0.1, 0.1);
    RooPolyVar mean1BuBu2Dst0pi_D0pi0(
        "mean1BuBu2Dst0pi_D0pi0", "", deltaMass,
        RooArgList(a0Mean1BuBu2Dst0pi_D0pi0, a1Mean1BuBu2Dst0pi_D0pi0,
                   a2Mean1BuBu2Dst0pi_D0pi0));
    RooRealVar a0Mean2BuBu2Dst0pi_D0pi0("a0Mean2BuBu2Dst0pi_D0pi0", "",
                                         5.2687e+03);  //, -4500, 5500);
    RooRealVar a1Mean2BuBu2Dst0pi_D0pi0("a1Mean2BuBu2Dst0pi_D0pi0", "",
                                         -7.4864e-02);  //, -10, 10);
    RooRealVar a2Mean2BuBu2Dst0pi_D0pi0("a2Mean2BuBu2Dst0pi_D0pi0", "",
                                         3.3846e-03);  //, -0.1, 0.1);
    RooPolyVar mean2BuBu2Dst0pi_D0pi0(
        "mean2BuBu2Dst0pi_D0pi0", "", deltaMass,
        RooArgList(a0Mean2BuBu2Dst0pi_D0pi0, a1Mean2BuBu2Dst0pi_D0pi0,
                   a2Mean2BuBu2Dst0pi_D0pi0));
    // // ---------------------------- Sigmas ----------------------------
    RooRealVar a0Sigma1BuBu2Dst0pi_D0pi0("a0Sigma1BuBu2Dst0pi_D0pi0", "",
                                          1.0035e+02);  //, -300, 300);
    RooRealVar a1Sigma1BuBu2Dst0pi_D0pi0("a1Sigma1BuBu2Dst0pi_D0pi0", "",
                                          -1.6530e+00);  //, -10, 10);
    RooRealVar a2Sigma1BuBu2Dst0pi_D0pi0("a2Sigma1BuBu2Dst0pi_D0pi0", "",
                                          8.7887e-03);  //, -0.1, 0.1);
    RooPolyVar sigma1BuBu2Dst0pi_D0pi0(
        "sigma1BuBu2Dst0pi_D0pi0", "", deltaMass,
        RooArgList(a0Sigma1BuBu2Dst0pi_D0pi0, a1Sigma1BuBu2Dst0pi_D0pi0,
                   a2Sigma1BuBu2Dst0pi_D0pi0));
    RooRealVar sigmaFracBuBu2Dst0pi_D0pi0("sigmaFracBuBu2Dst0pi_D0pi0", "",
                                           1.7152e+00);  //, -0.1, 0.1);
    RooFormulaVar sigma2BuBu2Dst0pi_D0pi0(
        "sigma2BuBu2Dst0pi_D0pi0", "", "@0*@1",
        RooArgSet(sigma1BuBu2Dst0pi_D0pi0, sigmaFracBuBu2Dst0pi_D0pi0));

    RooRealVar fracPdf1BuBu2Dst0pi_D0pi0("fracPdf1BuBu2Dst0pi_D0pi0", "",
                                          3.3530e-01);
    RooGaussian pdfBuBu2Dst0pi_D0pi01("pdfBuBu2Dst0pi_D0pi01", "", buMass,
                                       mean1BuBu2Dst0pi_D0pi0,
                                       sigma1BuBu2Dst0pi_D0pi0);
    RooGaussian pdfBuBu2Dst0pi_D0pi02("pdfBuBu2Dst0pi_D0pi02", "", buMass,
                                       mean2BuBu2Dst0pi_D0pi0,
                                       sigma2BuBu2Dst0pi_D0pi0);
    RooAddPdf pdfBuBu2Dst0pi_D0pi0(
        "pdfBuBu2Dst0pi_D0pi0", "",
        RooArgSet(pdfBuBu2Dst0pi_D0pi01, pdfBuBu2Dst0pi_D0pi02),
        fracPdf1BuBu2Dst0pi_D0pi0);
    // // ---------------------------- π Total Peaking PDF
    // ----------------------------
    RooProdPdf pdfBu2Dst0pi_D0pi0(
        "pdfBu2Dst0pi_D0pi0", "", pdfDeltaBu2Dst0pi_D0pi0,
        RooFit::Conditional(pdfBuBu2Dst0pi_D0pi0, buMass));

    // ---------------------------- Non TM Background
    // ----------------------------
    RooRealVar thresholdDeltaNonTM("thresholdDeltaNonTM", "", 5.1365e+01);
    RooRealVar cDeltaNonTM("cDeltaNonTM", "", 6.0571e+01);
    RooRealVar aDeltaNonTM("aDeltaNonTM", "", 8.2633e-01);
    RooRealVar bDeltaNonTM("bDeltaNonTM", "", -8.4849e-01);
    RooDstD0BG pdfDeltaNonTM("pdfDeltaNonTM", "", deltaMass,
                             thresholdDeltaNonTM, cDeltaNonTM, aDeltaNonTM,
                             bDeltaNonTM);
    // ---------------------------- π/K shared PDFs: Bu Bu2Dst0pi_Dst02D0pi0
    // ----------------------------
    RooRealVar a0MeanBuNonTM_Bu2Dst0pi_D0pi0("a0MeanBuNonTM_Bu2Dst0pi_D0pi0",
                                             "",
                                             5.2995e+03);  //, 4500, 5500);
    RooRealVar a1MeanBuNonTM_Bu2Dst0pi_D0pi0("a1MeanBuNonTM_Bu2Dst0pi_D0pi0",
                                             "",
                                             3.8979e-01);  //, -10, 10);
    RooRealVar a2MeanBuNonTM_Bu2Dst0pi_D0pi0("a2MeanBuNonTM_Bu2Dst0pi_D0pi0",
                                             "",
                                             -2.3520e-03);  //, -0.1, 0.1);
    RooPolyVar meanBuNonTM_Bu2Dst0pi_D0pi0(
        "meanBuNonTM_Bu2Dst0pi_D0pi0", "", deltaMass,
        RooArgList(a0MeanBuNonTM_Bu2Dst0pi_D0pi0, a1MeanBuNonTM_Bu2Dst0pi_D0pi0,
                   a2MeanBuNonTM_Bu2Dst0pi_D0pi0));
    // // ---------------------------- Sigmas ----------------------------
    RooRealVar a0SigmaBuNonTM_Bu2Dst0pi_D0pi0("a0SigmaBuNonTM_Bu2Dst0pi_D0pi0",
                                              "",
                                              5.3181e+01);  //, -300, 300);
    RooRealVar a1SigmaBuNonTM_Bu2Dst0pi_D0pi0("a1SigmaBuNonTM_Bu2Dst0pi_D0pi0",
                                              "",
                                              -1.0070e-01);  //, -10, 10);
    RooRealVar a2SigmaBuNonTM_Bu2Dst0pi_D0pi0("a2SigmaBuNonTM_Bu2Dst0pi_D0pi0",
                                              "",
                                              2.1628e-03);  //, -0.1, 0.1);
    RooPolyVar sigmaBuNonTM_Bu2Dst0pi_D0pi0(
        "sigmaBuNonTM_Bu2Dst0pi_D0pi0", "", deltaMass,
        RooArgList(a0SigmaBuNonTM_Bu2Dst0pi_D0pi0,
                   a1SigmaBuNonTM_Bu2Dst0pi_D0pi0,
                   a2SigmaBuNonTM_Bu2Dst0pi_D0pi0));
    RooGaussian pdfBuNonTM_Bu2Dst0pi_D0pi0("pdfBuNonTM_Bu2Dst0pi_D0pi0", "",
                                           buMass, meanBuNonTM_Bu2Dst0pi_D0pi0,
                                           sigmaBuNonTM_Bu2Dst0pi_D0pi0);
    // ---------------------------- π/K shared PDFs: Bu Bu2Dst0pi_Dst02D0gamma
    // ----------------------------
    RooRealVar a0MeanBuNonTM_Bu2Dst0pi_D0gamma(
        "a0MeanBuNonTM_Bu2Dst0pi_D0gamma", "",
        5.2770e+03);  //, 4500, 5500);
    RooRealVar a1MeanBuNonTM_Bu2Dst0pi_D0gamma(
        "a1MeanBuNonTM_Bu2Dst0pi_D0gamma", "",
        7.1443e-01);  //, -10, 10);
    RooRealVar a2MeanBuNonTM_Bu2Dst0pi_D0gamma(
        "a2MeanBuNonTM_Bu2Dst0pi_D0gamma", "",
        -3.2166e-03);  //, -0.1, 0.1);
    RooPolyVar meanBuNonTM_Bu2Dst0pi_D0gamma(
        "meanBuNonTM_Bu2Dst0pi_D0gamma", "", deltaMass,
        RooArgList(a0MeanBuNonTM_Bu2Dst0pi_D0gamma,
                   a1MeanBuNonTM_Bu2Dst0pi_D0gamma,
                   a2MeanBuNonTM_Bu2Dst0pi_D0gamma));
    // // ---------------------------- Sigmas ----------------------------
    RooRealVar a0SigmaBuNonTM_Bu2Dst0pi_D0gamma(
        "a0SigmaBuNonTM_Bu2Dst0pi_D0gamma", "",
        4.8916e+01);  //, -300, 300);
    RooRealVar a1SigmaBuNonTM_Bu2Dst0pi_D0gamma(
        "a1SigmaBuNonTM_Bu2Dst0pi_D0gamma", "",
        3.4428e-01);  //, -10, 10);
    RooRealVar a2SigmaBuNonTM_Bu2Dst0pi_D0gamma(
        "a2SigmaBuNonTM_Bu2Dst0pi_D0gamma", "",
        1.8772e-04);  //, -0.1, 0.1);
    RooPolyVar sigmaBuNonTM_Bu2Dst0pi_D0gamma(
        "sigmaBuNonTM_Bu2Dst0pi_D0gamma", "", deltaMass,
        RooArgList(a0SigmaBuNonTM_Bu2Dst0pi_D0gamma,
                   a1SigmaBuNonTM_Bu2Dst0pi_D0gamma,
                   a2SigmaBuNonTM_Bu2Dst0pi_D0gamma));
    RooGaussian pdfBuNonTM_Bu2Dst0pi_D0gamma(
        "pdfBuNonTM_Bu2Dst0pi_D0gamma", "", buMass,
        meanBuNonTM_Bu2Dst0pi_D0gamma, sigmaBuNonTM_Bu2Dst0pi_D0gamma);
    // // ---------------------------- Bu NonTM PDF ----------------------------
    RooRealVar fracBuPdfNonTM_Bu2Dst0pi_D0pi0("fracBuPdfNonTM_Bu2Dst0pi_D0pi0",
                                              "", 6.3103e-01);
    RooAddPdf pdfBuNonTM(
        "pdfNonTM", "",
        RooArgSet(pdfBuNonTM_Bu2Dst0pi_D0pi0, pdfBuNonTM_Bu2Dst0pi_D0gamma),
        fracBuPdfNonTM_Bu2Dst0pi_D0pi0);
    // // ---------------------------- π Total NonTM PDF
    // ----------------------------
    RooProdPdf pdfNonTM("pdfNonTM_Bu2Dst0pi_D0pi0", "", pdfDeltaNonTM,
                        RooFit::Conditional(pdfBuNonTM, buMass));

    // ---------------------------- B02Dstpi Background
    // ----------------------------

    // RooRealVar lambdaDeltaBkg("lambdaDeltaBkg", "", 0.01);//, -0.1, 0.1);
    // RooExponential pdfDeltaBkg("pdfDeltaBkg", "", deltaMass, lambdaDeltaBkg);

    RooRealVar thresholdDeltaB02Dstpi("thresholdDeltaB02Dstpi", "", 5.2666e+01);
    RooRealVar cDeltaB02Dstpi("cDeltaB02Dstpi", "", 5.0814e+01);
    RooRealVar aDeltaB02Dstpi("aDeltaB02Dstpi", "", 9.2597e-01);
    RooRealVar bDeltaB02Dstpi("bDeltaB02Dstpi", "", -1.0400e+00);
    RooDstD0BG pdfDeltaB02Dstpi("pdfDeltaB02Dstpi", "", deltaMass,
                                thresholdDeltaB02Dstpi, cDeltaB02Dstpi,
                                aDeltaB02Dstpi, bDeltaB02Dstpi);
    // ---------------------------- π/K shared PDFs: Bu
    // ----------------------------
    // RooRealVar lambdaBuBkg("lambdaBuBkg", "", -0.005);//, -0.1, 0.1);
    // RooExponential pdfBuBkg("pdfBuBkg", "", buMass, lambdaBuBkg);

    RooRealVar a0Mean1BuB02Dstpi("a0Mean1BuB02Dstpi", "",
                                 5.2068e+03);  //, 4500, 5500);
    RooRealVar a1Mean1BuB02Dstpi("a1Mean1BuB02Dstpi", "",
                                 1.6004e+00);  //, -10, 10);
    RooRealVar a2Mean1BuB02Dstpi("a2Mean1BuB02Dstpi", "",
                                 -6.2917e-03);  //, -0.1, 0.1);
    RooPolyVar mean1BuB02Dstpi(
        "mean1BuB02Dstpi", "", deltaMass,
        RooArgList(a0Mean1BuB02Dstpi, a1Mean1BuB02Dstpi, a2Mean1BuB02Dstpi));
    // // ---------------------------- Sigmas ----------------------------
    RooRealVar a0Sigma1BuB02Dstpi("a0Sigma1BuB02Dstpi", "",
                                  1.9083e+01);  //, -300, 300);
    RooRealVar a1Sigma1BuB02Dstpi("a1Sigma1BuB02Dstpi", "",
                                  3.8123e-01);  //, -10, 10);
    RooRealVar a2Sigma1BuB02Dstpi("a2Sigma1BuB02Dstpi", "",
                                  5.5464e-04);  //, -0.1, 0.1);
    RooPolyVar sigma1BuB02Dstpi(
        "sigma1BuB02Dstpi", "", deltaMass,
        RooArgList(a0Sigma1BuB02Dstpi, a1Sigma1BuB02Dstpi, a2Sigma1BuB02Dstpi));
    RooGaussian pdfBuB02Dstpi("pdfBuB02Dstpi", "", buMass, mean1BuB02Dstpi,
                              sigma1BuB02Dstpi);
    // // ---------------------------- π Total PDF ----------------------------
    // RooProdPdf pdfB02Dstpi("pdfB02Dstpi", "", RooArgSet(pdfDeltaB02Dstpi,
    // pdfBuB02Dstpi));
    RooProdPdf pdfB02Dstpi("pdfB02Dstpi", "", pdfDeltaB02Dstpi,
                           RooFit::Conditional(pdfBuB02Dstpi, buMass));

    // ---------------------------- Bu2D0rho Background
    // ----------------------------
    RooRealVar thresholdDeltaBu2D0rho("thresholdDeltaBu2D0rho", "", 5.1070e+01);
    RooRealVar cDeltaBu2D0rho("cDeltaBu2D0rho", "", 5.8825e+01);
    RooRealVar aDeltaBu2D0rho("aDeltaBu2D0rho", "", 8.5307e-01);
    RooRealVar bDeltaBu2D0rho("bDeltaBu2D0rho", "", -8.6985e-01);
    RooDstD0BG pdfDeltaBu2D0rho("pdfDeltaBu2D0rho", "", deltaMass,
                                thresholdDeltaBu2D0rho, cDeltaBu2D0rho,
                                aDeltaBu2D0rho, bDeltaBu2D0rho);
    // ---------------------------- π/K shared PDFs: Bu
    // ----------------------------
    RooRealVar a0Mean1BuBu2D0rho("a0Mean1BuBu2D0rho", "",
                                 5.2340e+03);  //, 4500, 5500);
    RooRealVar a1Mean1BuBu2D0rho("a1Mean1BuBu2D0rho", "",
                                 1.5946e+00);  //, -10, 10);
    RooRealVar a2Mean1BuBu2D0rho("a2Mean1BuBu2D0rho", "",
                                 -6.9947e-03);  //, -0.1, 0.1);
    RooPolyVar mean1BuBu2D0rho(
        "mean1BuBu2D0rho", "", deltaMass,
        RooArgList(a0Mean1BuBu2D0rho, a1Mean1BuBu2D0rho, a2Mean1BuBu2D0rho));
    RooRealVar a0Mean2BuBu2D0rho("a0Mean2BuBu2D0rho", "",
                                 5.1485e+03);  //, -4500, 5500);
    RooRealVar a1Mean2BuBu2D0rho("a1Mean2BuBu2D0rho", "",
                                 1.3977e+00);  //, -10, 10);
    RooRealVar a2Mean2BuBu2D0rho("a2Mean2BuBu2D0rho", "",
                                 -7.4131e-03);  //, -0.1, 0.1);
    RooPolyVar mean2BuBu2D0rho(
        "mean2BuBu2D0rho", "", deltaMass,
        RooArgList(a0Mean2BuBu2D0rho, a1Mean2BuBu2D0rho, a2Mean2BuBu2D0rho));
    // // ---------------------------- Sigmas ----------------------------
    RooRealVar a0Sigma1BuBu2D0rho("a0Sigma1BuBu2D0rho", "",
                                  2.8808e+01);  //, -300, 300);
    RooRealVar a1Sigma1BuBu2D0rho("a1Sigma1BuBu2D0rho", "",
                                  2.1428e-01);  //, -10, 10);
    RooRealVar a2Sigma1BuBu2D0rho("a2Sigma1BuBu2D0rho", "",
                                  1.2546e-03);  //, -0.1, 0.1);
    RooPolyVar sigma1BuBu2D0rho(
        "sigma1BuBu2D0rho", "", deltaMass,
        RooArgList(a0Sigma1BuBu2D0rho, a1Sigma1BuBu2D0rho, a2Sigma1BuBu2D0rho));
    RooRealVar sigmaFracBuBu2D0rho("sigmaFracBuBu2D0rho", "",
                                   7.3477e-01);  //, -0.1, 0.1);
    RooFormulaVar sigma2BuBu2D0rho(
        "sigma2BuBu2D0rho", "", "@0*@1",
        RooArgSet(sigma1BuBu2D0rho, sigmaFracBuBu2D0rho));

    RooRealVar fracPdf1BuBu2D0rho("fracPdf1BuBu2D0rho", "", 6.7034e-01);
    RooGaussian pdfBuBu2D0rho1("pdfBuBu2D0rho1", "", buMass, mean1BuBu2D0rho,
                               sigma1BuBu2D0rho);
    RooGaussian pdfBuBu2D0rho2("pdfBuBu2D0rho2", "", buMass, mean2BuBu2D0rho,
                               sigma2BuBu2D0rho);
    RooAddPdf pdfBuBu2D0rho("pdfBuBu2D0rho", "",
                            RooArgSet(pdfBuBu2D0rho1, pdfBuBu2D0rho2),
                            fracPdf1BuBu2D0rho);
    // // ---------------------------- π Total PDF ----------------------------
    RooProdPdf pdfBu2D0rho("pdfBu2D0rho", "", pdfDeltaBu2D0rho,
                           RooFit::Conditional(pdfBuBu2D0rho, buMass));

    // ---------------------------- Yields ----------------------------
    RooRealVar yieldSignal("yieldSignal", "", 40000, -1000000, 1000000);
    RooRealVar fracB02DstpiYield("fracB02DstpiYield", "", 0.643);
    RooFormulaVar yieldB02Dstpi("yieldB02Dstpi", "", "@0*@1",
                                RooArgSet(yieldSignal, fracB02DstpiYield));
    RooRealVar fracBu2D0rhoYield("fracBu2D0rhoYield", "", 0.973);
    RooFormulaVar yieldBu2D0rho("yieldBu2D0rho", "", "@0*@1",
                                RooArgSet(yieldSignal, fracBu2D0rhoYield));
    RooRealVar fracBu2Dst0pi_D0pi0Yield("fracBu2Dst0pi_D0pi0Yield", "", 0.916);
    RooFormulaVar yieldBu2Dst0pi_D0pi0(
        "yieldBu2Dst0pi_D0pi0", "", "@0*@1",
        RooArgSet(yieldSignal, fracBu2Dst0pi_D0pi0Yield));
    RooRealVar fracNonTMYield("fracNonTMYield", "", 1.28);
    RooFormulaVar yieldNonTM("yieldNonTM", "", "@0*@1",
                             RooArgSet(yieldSignal, fracNonTMYield));

    // ---------------------------- Add PDFs and yields
    // ----------------------------
    RooArgSet yields;
    yields.add(yieldSignal);
    yields.add(yieldB02Dstpi);
    yields.add(yieldBu2D0rho);
    yields.add(yieldBu2Dst0pi_D0pi0);
    yields.add(yieldNonTM);
    RooArgSet functions;
    functions.add(pdfSignal);
    functions.add(pdfB02Dstpi);
    functions.add(pdfBu2D0rho);
    functions.add(pdfBu2Dst0pi_D0pi0);
    functions.add(pdfNonTM);
    RooAddPdf pdf("pdf", "", functions, yields);

    double nEvtsPerToy = yieldSignal.getVal() + yieldB02Dstpi.getVal() +
                         yieldBu2D0rho.getVal() +
                         yieldBu2Dst0pi_D0pi0.getVal() + yieldNonTM.getVal();
    std::cout << "Generating toy dataset..." << std::endl;

    // ---------------------------- Generate toy datasets for bu and delta
    // spearately: save them
    // ----------------------------
    // RooDataSet *buDataSet = pdf.generate(RooArgSet(buMass), nEvtsPerToy);
    // std::cout << "Generated!" << std::endl;
    // buDataSet->SetName("buDataSet");
    // buDataSet->Print();
    //
    // TFile buFile((outputDir + "buDataFile.root").c_str(), "RECREATE");
    // buDataSet->Write("buDataSet");
    // buFile.Close();
    //
    // RooDataSet *deltaDataSet = pdf.generate(RooArgSet(deltaMass),
    // nEvtsPerToy);
    // std::cout << "Generated!" << std::endl;
    // deltaDataSet->SetName("deltaDataSet");
    // deltaDataSet->Print();
    //
    // TFile deltaFile((outputDir + "deltaDataFile.root").c_str(), "RECREATE");
    // deltaDataSet->Write("deltaDataSet");
    // deltaFile.Close();

    // ---------------------------- Generate toy dataset: CAN'T generate bu and
    // delta separately as doesn't generate whole 2D phase space
    // ----------------------------
    RooDataSet *toyDataSet =
        pdf.generate(RooArgSet(buMass, deltaMass), nEvtsPerToy);
    std::cout << "Generated!" << std::endl;
    toyDataSet->Print();

    double randomTag = random.Rndm();
    TFile dsFile(
        (outputDir + "/DataFile2D_" + std::to_string(randomTag) + ".root")
            .c_str(),
        "RECREATE");
    toyDataSet->Write("toyDataSet");
    dsFile.Close();
    std::cout << "Saved " << randomTag << " dataset\n";

    auto toyDataHist = std::unique_ptr<RooDataHist>(
        toyDataSet->binnedClone("toyDataHist", "toyDataHist"));
    auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

    // meanDeltaSignal.setVal(142);

    std::unique_ptr<RooFitResult> result =
        std::unique_ptr<RooFitResult>(pdf.fitTo(
            *toyAbsData, RooFit::Extended(true), RooFit::SplitRange(true),
            RooFit::Save(), RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
            RooFit::Offset(true), RooFit::NumCPU(8, 2)));

    // ---------------------------- Plot if specified
    // ----------------------------
    std::cout << "Plotting projections of m[Bu]\n";
    PlotComponent(Variable::bu, buMass, toyDataHist.get(), pdf, pdfSignal,
                  pdfB02Dstpi, pdfBu2D0rho, pdfBu2Dst0pi_D0pi0, pdfNonTM,
                  outputDir);
    std::cout << "Plotting projections of m[Delta]\n";
    PlotComponent(Variable::delta, deltaMass, toyDataHist.get(), pdf, pdfSignal,
                  pdfB02Dstpi, pdfBu2D0rho, pdfBu2Dst0pi_D0pi0, pdfNonTM,
                  outputDir);
    std::cout << "Plotting in 2D\n";
    Plotting2D(buMass, deltaMass, toyDataHist.get(), pdf, outputDir);
    std::cout << "Plotting correlation matrix\n";
    PlotCorrMatrix(result.get(), outputDir);

    result->Print("v");
  }
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr
        << "Enter output directory and number of toy datasets to generate\n";
    return 1;
  }
  std::string outputDir = argv[1];
  int nToys = std::atoi(argv[2]);
  GenerateToys(outputDir, nToys);
  return 0;
}
