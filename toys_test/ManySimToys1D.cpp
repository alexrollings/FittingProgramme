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

std::string FittingName(Variable variable, Neutral neutral, Bachelor bachelor) {
  switch (variable) {
    case Variable::bu:
      switch (neutral) {
        case Neutral::pi0:
          switch (bachelor) {
            case Bachelor::pi:
              return "bu_pi0_pi";
              break;
            case Bachelor::k:
              return "bu_pi0_K";
              break;
          }
          break;
        case Neutral::gamma:
          switch (bachelor) {
            case Bachelor::pi:
              return "bu_gamma_pi";
              break;
            case Bachelor::k:
              return "bu_gamma_K";
              break;
          }
          break;
      }
      break;
    case Variable::delta:
      switch (neutral) {
        case Neutral::pi0:
          switch (bachelor) {
            case Bachelor::pi:
              return "bu_pi0_pi";
              break;
            case Bachelor::k:
              return "bu_pi0_K";
              break;
          }
          break;
        case Neutral::gamma:
          switch (bachelor) {
            case Bachelor::pi:
              return "bu_gamma_pi";
              break;
            case Bachelor::k:
              return "bu_gamma_K";
              break;
          }
          break;
      }
      break;
  }
}

void PlotComponent(Neutral neutral, Bachelor bachelor, Variable variable,
                   RooRealVar &var, RooDataHist *dataHist,
                   RooSimultaneous &simPdf, RooCategory &fitting,
                   // RooAddPdf &sig, RooAddPdf &bkg,
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
          title = "m[D^{*0}]-m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG}";
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
          ("fitting==fitting::" + FittingName(variable, neutral, bachelor)).c_str()));
  simPdf.plotOn(frame.get(),
                RooFit::Slice(fitting, FittingName(variable, neutral, bachelor).c_str()),
                RooFit::ProjWData(fitting, *dataHist),
                RooFit::LineColor(kBlue));
  pullHist = frame->RooPlot::pullHist();
  // simPdf.plotOn(frame.get(),
  //               RooFit::Slice(fitting, FittingName(variable, neutral, bachelor).c_str()),
  //               RooFit::ProjWData(fitting, *dataHist),
  //               RooFit::Components(sig.GetName()), RooFit::LineColor(kBlue),
  //               RooFit::LineStyle(kDashed));
  // simPdf.plotOn(frame.get(),
  //               RooFit::Slice(fitting, FittingName(variable neutral, bachelor).c_str()),
  //               RooFit::ProjWData(fitting, *dataHist),
  //               RooFit::Components(bkg.GetName()), RooFit::LineColor(kRed),
  //               RooFit::LineStyle(kDashed));

  dataHist->plotOn(
      frame.get(),
      RooFit::Cut(
          ("fitting==fitting::" + FittingName(variable, neutral, bachelor)).c_str()));

  if (pullHist != 0) {
    pullFrame->addPlotable(pullHist /* .get() */, "P");
    pullFrame->SetName(("pullFrame_" + FittingName(variable, neutral, bachelor)).c_str());
    pullFrame->SetTitle("");
  }

  TCanvas canvas(("canvas_" + EnumToString(variable) + "_" +
                  FittingName(variable, neutral, bachelor))
                     .c_str(),
                 "", 1200, 1000);

  TPad pad1(
      ("pad1_" + EnumToString(variable) + "_" + FittingName(variable, neutral, bachelor))
          .c_str(),
      "", 0.0, 0.14, 1.0, 1.0, kWhite);
  pad1.Draw();

  TPad pad2(
      ("pad2_" + EnumToString(variable) + "_" + FittingName(variable, neutral, bachelor))
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
  canvas.SaveAs((outputDir + "/plots/" + FittingName(variable, neutral, bachelor) + ".pdf")
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
  corrHist->SetLabelSize(0.04, "XY");
  corrHist->SetLabelSize(0.02, "Z");
  corrHist->Draw("colz");
  corrCanvas.Update();
  corrCanvas.SaveAs((outputDir + "/plots/CorrelationMatrix.pdf").c_str());
}

void GenerateToys(std::string const &outputDir, int nToys, bool toPlot) {
  int bu_low = 5050;
  int bu_high = 5800;
  int delta_low = 70;  // 134;
  int delta_high = 210;

  int bu_nbins = (bu_high - bu_low) / 10;
  int delta_nbins = (delta_high - delta_low) / 2.8;

  // ---------------------------- Fitting Vars ----------------------------
  RooRealVar buMass("Bu_M_DTF_D0", "m[D^{*0}#pi^{#pm}]", bu_low, bu_high,
                    "MeV/c^{2}");
  RooRealVar deltaMass("Delta_M", "m[D^{*0}] - m[D^{0}]", delta_low, delta_high,
                       "MeV/c^{2}");

  buMass.setBins(bu_nbins);
  deltaMass.setBins(delta_nbins);

  // ---------------------------- Categories ----------------------------
  RooCategory fitting("fitting", "fitting");
  fitting.defineType("bu_gamma_pi");
  fitting.defineType("delta_gamma_pi");
  fitting.defineType("bu_gamma_K");
  fitting.defineType("delta_gamma_K");

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

    // ---------------------------- Shared yields ----------------------------

    // ---------------------------- PDFs ----------------------------
    //
    // ---------------------------- Signal ----------------------------
    //
    // ---------------------------- π/K shared PDFs: Delta
    // ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanDeltaSignal(("meanDeltaSignal_" + std::to_string(i)).c_str(),
                               "", 1.4257e+02);//, 135, 150);
    // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaDeltaSignal(
        ("sigmaDeltaSignal_" + std::to_string(i)).c_str(), "", 8.4700e+00);//, 5, 15);
    // ---------------------------- Tails ----------------------------
    RooRealVar a1DeltaSignal(("a1DeltaSignal_" + std::to_string(i)).c_str(), "",
                             1.6863e+00);
    RooRealVar a2DeltaSignal(("a2DeltaSignal_" + std::to_string(i)).c_str(), "",
                             -5.6811e-01);
    RooRealVar n1DeltaSignal(("n1DeltaSignal_" + std::to_string(i)).c_str(), "",
                             4.0630e+00);
    RooRealVar n2DeltaSignal(("n2DeltaSignal_" + std::to_string(i)).c_str(), "",
                             4.4013e+00);
    // ---------------------------- PDFs ----------------------------
    // RooGaussian pdfDeltaSignal1(
    //     ("pdfDeltaSignal1_" + std::to_string(i)).c_str(), "", deltaMass,
    //     meanDeltaSignal, sigma1DeltaSignal);
    RooCBShape pdfDeltaSignal1(("pdfDeltaSignal1_" + std::to_string(i)).c_str(),
                               "", deltaMass, meanDeltaSignal,
                               sigmaDeltaSignal, a1DeltaSignal, n1DeltaSignal);
    RooCBShape pdfDeltaSignal2(("pdfDeltaSignal2_" + std::to_string(i)).c_str(),
                               "", deltaMass, meanDeltaSignal,
                               sigmaDeltaSignal, a2DeltaSignal, n2DeltaSignal);
    RooRealVar fracPdf1DeltaSignal(
        ("fracPdf1DeltaSignal_" + std::to_string(i)).c_str(), "", 2.8498e-01);
    RooAddPdf pdfDeltaSignal(("pdfDeltaSignal_" + std::to_string(i)).c_str(),
                             "", RooArgSet(pdfDeltaSignal1, pdfDeltaSignal2),
                             fracPdf1DeltaSignal);

    // ---------------------------- π PDFs: Bu ----------------------------
    // ---------------------------- Signal ----------------------------
    // ---------------------------- Mean ----------------------------
    RooRealVar meanBuSignal(("meanBuSignal_" + std::to_string(i)).c_str(),
                              "", 5.0271e+03);//, 4500, 5500);
    // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaBuSignalPi(
        ("sigmaBuSignalPi_" + std::to_string(i)).c_str(), "", 2.3604e+01);//, 300, 400);

    // ---------------------------- Tails ----------------------------
    RooRealVar a1BuSignal(("a1BuSignal_" + std::to_string(i)).c_str(), "",
                          9.9494e-01);
    RooRealVar a2BuSignal(("a2BuSignal_" + std::to_string(i)).c_str(), "",
                          -9.9380e-01);
    RooRealVar n1BuSignal(("n1BuSignal_" + std::to_string(i)).c_str(), "",
                          10);
    RooRealVar n2BuSignal(("n2BuSignal_" + std::to_string(i)).c_str(), "",
                          10);
    // ---------------------------- PDFs ----------------------------
    RooRealVar fracPdf1BuSignal(
        ("fracPdf1BuSignal_" + std::to_string(i)).c_str(), "", 9.1502e-02);
    // RooGaussian pdfBuSignalPi1(("pdfBuSignalPi1_" + std::to_string(i)).c_str(),
    //                            "", buMass, meanBuSignal, sigma1BuSignalPi);
    RooCBShape pdfBuSignalPi1(("pdfBuSignalPi1_" + std::to_string(i)).c_str(),
                              "", buMass, meanBuSignal, sigmaBuSignalPi,
                              a1BuSignal, n1BuSignal);
    // RooGaussian pdfBuSignalPi2(("pdfBuSignalPi2_" + std::to_string(i)).c_str(),
    //                            "", buMass, meanBuSignal, sigma2BuSignalPi);
    RooCBShape pdfBuSignalPi2(("pdfBuSignalPi2_" + std::to_string(i)).c_str(),
                              "", buMass, meanBuSignal, sigmaBuSignalPi,
                              a2BuSignal, n2BuSignal);
    RooAddPdf pdfBuSignalPi(("pdfBuSignalPi_" + std::to_string(i)).c_str(), "",
                            RooArgSet(pdfBuSignalPi1, pdfBuSignalPi2),
                            fracPdf1BuSignal);

    // ---------------------------- K PDFs: Bu ----------------------------
    // ---------------------------- Signal ----------------------------
    // ---------------------------- Sigmas ----------------------------
    RooRealVar sigmaRelativeWidthSignal(
        ("sigmaRelativeWidthSignal_" + std::to_string(i)).c_str(), "", 1);
    RooFormulaVar sigmaBuSignalK(
        ("sigmaBuSignalK_" + std::to_string(i)).c_str(), "", "@0*@1",
        RooArgList(sigmaBuSignalPi, sigmaRelativeWidthSignal));
    // ---------------------------- PDFs ----------------------------
    // RooGaussian pdfBuSignalK1(("pdfBuSignalK1_" + std::to_string(i)).c_str(),
    //                           "", buMass, meanBuSignal, sigma1BuSignalK);
    RooCBShape pdfBuSignalK1(("pdfBuSignalK1_" + std::to_string(i)).c_str(), "",
                             buMass, meanBuSignal, sigmaBuSignalK, a1BuSignal,
                             n1BuSignal);
    // RooGaussian pdfBuSignalK2(("pdfBuSignalK2_" + std::to_string(i)).c_str(),
    //                           "", buMass, meanBuSignal, sigma2BuSignalK);
    RooCBShape pdfBuSignalK2(("pdfBuSignalK2_" + std::to_string(i)).c_str(), "",
                             buMass, meanBuSignal, sigmaBuSignalK, a2BuSignal,
                             n2BuSignal);
    RooAddPdf pdfBuSignalK(("pdfBuSignalK_" + std::to_string(i)).c_str(), "",
                           RooArgSet(pdfBuSignalK1, pdfBuSignalK2),
                           fracPdf1BuSignal);

    // ---------------------------- Background ----------------------------
    //
    // ---------------------------- π/K shared PDFs: Delta
    // ----------------------------
    // RooRealVar threshold1DeltaBkg(
    //     ("threshold1DeltaBkg_" + std::to_string(i)).c_str(), "", 5.2160e+01);
    // RooRealVar c1DeltaBkg(("c1DeltaBkg_" + std::to_string(i)).c_str(), "",
    //                       4.2450e+01);
    // RooRealVar a1DeltaBkg(("a1DeltaBkg_" + std::to_string(i)).c_str(), "",
    //                       1.0341e+00);
    // RooRealVar b1DeltaBkg(("b1DeltaBkg_" + std::to_string(i)).c_str(), "",
    //                       -1.2284e+00);
    RooRealVar threshold2DeltaBkg(
        ("threshold2DeltaBkg_" + std::to_string(i)).c_str(), "", 6.7237e+01);
    RooRealVar c2DeltaBkg(("c2DeltaBkg_" + std::to_string(i)).c_str(), "",
                          4.7874e+01);
    RooRealVar a2DeltaBkg(("a2DeltaBkg_" + std::to_string(i)).c_str(), "",
                          8.8301e-01);
    RooRealVar b2DeltaBkg(("b2DeltaBkg_" + std::to_string(i)).c_str(), "",
                          -9.9972e-01);
    RooDstD0BG pdf1DeltaBkg(("pdf1DeltaBkg_" + std::to_string(i)).c_str(), "",
                            deltaMass, threshold2DeltaBkg, c2DeltaBkg,
                            a2DeltaBkg, b2DeltaBkg);
    RooDstD0BG pdf2DeltaBkg(("pdf2DeltaBkg_" + std::to_string(i)).c_str(), "",
                            deltaMass, threshold2DeltaBkg, c2DeltaBkg,
                            a2DeltaBkg, b2DeltaBkg);

    // RooRealVar lambda1DeltaBkg(("lambda1DeltaBkg_" + std::to_string(i)).c_str(),
    //                           "", 0.01);
    // RooExponential pdf1DeltaBkg(("pdf1DeltaBkg_" + std::to_string(i)).c_str(), "",
    //                            deltaMass, lambda1DeltaBkg);
    // RooRealVar lambda2DeltaBkg(("lambda2DeltaBkg_" + std::to_string(i)).c_str(),
    //                           "", 0.00001);
    // RooExponential pdf2DeltaBkg(("pdf2DeltaBkg_" + std::to_string(i)).c_str(), "",
    //                            deltaMass, lambda2DeltaBkg);
    // ---------------------------- π PDFs: Bu ----------------------------
    RooRealVar a0Mean1BuBkg(("a0Mean1BuBkg_" + std::to_string(i)).c_str(), "",
                            5.0884e+03, 4500, 5500);
    RooRealVar a1Mean1BuBkg(("a1Mean1BuBkg_" + std::to_string(i)).c_str(), "",
                            2.1973e+00, -10, 10);
    RooRealVar a2Mean1BuBkg(("a2Mean1BuBkg_" + std::to_string(i)).c_str(), "",
                            -4.7604e-03);//, -0.1, 0.1);
    RooPolyVar mean1BuBkg(("mean1BuBkg_" + std::to_string(i)).c_str(), "",
                          deltaMass,
                          RooArgList(a0Mean1BuBkg, a1Mean1BuBkg, a2Mean1BuBkg));
    RooRealVar a0Mean2BuBkg(("a0Mean2BuBkg_" + std::to_string(i)).c_str(), "",
                            5.0900e+03, -4500, 5500);
    RooRealVar a1Mean2BuBkg(("a1Mean2BuBkg_" + std::to_string(i)).c_str(), "",
                            1.5989e+00, -10, 10);
    RooRealVar a2Mean2BuBkg(("a2Mean2BuBkg_" + std::to_string(i)).c_str(), "",
                            -4.4125e-03);//, -0.1, 0.1);
    RooPolyVar mean2BuBkg(("mean2BuBkg_" + std::to_string(i)).c_str(), "",
                          deltaMass,
                          RooArgList(a0Mean2BuBkg, a1Mean2BuBkg, a2Mean2BuBkg));
    // ---------------------------- Sigmas ----------------------------
    RooRealVar a0Sigma1BuBkgPi(("a0Sigma1BuBkgPi_" + std::to_string(i)).c_str(),
                               "", 1.1688e+01, -300, 300);
    RooRealVar a1Sigma1BuBkgPi(("a1Sigma1BuBkgPi_" + std::to_string(i)).c_str(),
                               "", 5.2448e-01, -10, 10);
    RooRealVar a2Sigma1BuBkgPi(("a2Sigma1BuBkgPi_" + std::to_string(i)).c_str(),
                               "", -1.5881e-05);//, -0.1, 0.1);
    RooPolyVar sigma1BuBkgPi(
        ("sigma1BuBkgPi_" + std::to_string(i)).c_str(), "", deltaMass,
        RooArgList(a0Sigma1BuBkgPi, a1Sigma1BuBkgPi, a2Sigma1BuBkgPi));
    RooRealVar a0Sigma2BuBkgPi(("a0Sigma2BuBkgPi_" + std::to_string(i)).c_str(),
                               "", 5.6539e+01, -300, 300);
    RooRealVar a1Sigma2BuBkgPi(("a1Sigma2BuBkgPi_" + std::to_string(i)).c_str(),
                               "", 4.4641e-01, -10, 10);
    RooRealVar a2Sigma2BuBkgPi(("a2Sigma2BuBkgPi_" + std::to_string(i)).c_str(),
                               "", 2.2171e-04);//, -0.1, 0.1);
    RooPolyVar sigma2BuBkgPi(
        ("sigma2BuBkgPi_" + std::to_string(i)).c_str(), "", deltaMass,
        RooArgList(a0Sigma2BuBkgPi, a1Sigma2BuBkgPi, a2Sigma2BuBkgPi));
    // ---------------------------- Tails ----------------------------
    // RooRealVar a1BuBkg(("a1BuBkg_" + std::to_string(i)).c_str(), "",
    //                    2.5926e+00);
    // RooRealVar n1BuBkg(("n1BuBkg_" + std::to_string(i)).c_str(), "",
    //                    2.4846e-01);
    // RooRealVar a2BuBkg(("a2BuBkg_" + std::to_string(i)).c_str(), "",
    //                    1.2916e+00);
    // RooRealVar n2BuBkg(("n2BuBkg_" + std::to_string(i)).c_str(), "",
    //                    3.4602e+00);
    // ---------------------------- PDFs ----------------------------
    RooGaussian pdf1BuBkgPi(("pdf1BuBkgPi_" + std::to_string(i)).c_str(), "",
                           buMass, mean1BuBkg, sigma1BuBkgPi);
    // RooCBShape pdf1BuBkgPi(("pdf1BuBkgPi_" + std::to_string(i)).c_str(), "",
    //                        buMass, mean1BuBkg, sigma1BuBkgPi, a1BuBkg, n1BuBkg);
    RooGaussian pdf2BuBkgPi(("pdf2BuBkgPi_" + std::to_string(i)).c_str(), "",
                           buMass, mean2BuBkg, sigma2BuBkgPi);
    // RooCBShape pdf2BuBkgPi(("pdf2BuBkgPi_" + std::to_string(i)).c_str(), "",
    //                        buMass, mean2BuBkg, sigma2BuBkgPi, a2BuBkg, n2BuBkg);
    // ---------------------------- π Total PDF ----------------------------
    RooProdPdf pdf1BkgPi(("pdf1BkgPi_" + std::to_string(i)).c_str(), "",
                         pdf1DeltaBkg,
                         RooFit::Conditional(pdf1BuBkgPi, buMass));
    RooProdPdf pdf2BkgPi(("pdf2BkgPi_" + std::to_string(i)).c_str(), "",
                         pdf2DeltaBkg,
                         RooFit::Conditional(pdf2BuBkgPi, buMass));
    RooRealVar fracPdf1Bkg(("fracPdf1Bkg_" + std::to_string(i)).c_str(), "",
                           0.714);//, 0, 1);
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
    RooGaussian pdf1BuBkgK(("pdf1BuBkgK_" + std::to_string(i)).c_str(), "",
                          buMass, mean1BuBkg, sigma1BuBkgK);
    // RooCBShape pdf1BuBkgK(("pdf1BuBkgK_" + std::to_string(i)).c_str(), "",
    //                       buMass, mean1BuBkg, sigma1BuBkgK, a1BuBkg, n1BuBkg);
    RooGaussian pdf2BuBkgK(("pdf2BuBkgK_" + std::to_string(i)).c_str(), "",
                          buMass, mean2BuBkg, sigma2BuBkgK);
    // RooCBShape pdf2BuBkgK(("pdf2BuBkgK_" + std::to_string(i)).c_str(), "",
    //                       buMass, mean2BuBkg, sigma2BuBkgK, a2BuBkg, n2BuBkg);
    // ---------------------------- K Total PDF ----------------------------
    RooProdPdf pdf1BkgK(("pdf1BkgK_" + std::to_string(i)).c_str(), "",
                        pdf1DeltaBkg, RooFit::Conditional(pdf1BuBkgK, buMass));
    RooProdPdf pdf2BkgK(("pdf2BkgK_" + std::to_string(i)).c_str(), "",
                        pdf2DeltaBkg, RooFit::Conditional(pdf2BuBkgK, buMass));
    RooAddPdf pdfBkgK(("pdfBkgK_" + std::to_string(i)).c_str(), "",
                      RooArgSet(pdf1BkgK, pdf2BkgK), fracPdf1Bkg);

    // ---------------------------- Yields ----------------------------
    RooRealVar yieldSignalPi(("yieldSignalPi_" + std::to_string(i)).c_str(), "",
                             40000, -1000000, 1000000);
    RooRealVar yieldBkgPi(("yieldBkgPi_" + std::to_string(i)).c_str(), "",
                          100000, -1000000, 1000000);
    RooRealVar yieldRatioSignal(
        ("yieldRatioSignal_" + std::to_string(i)).c_str(), "", 0.07930, -1, 1);
    RooFormulaVar yieldSignalK(("yieldSignalK_" + std::to_string(i)).c_str(),
                               "", "@0*@1",
                               RooArgList(yieldSignalPi, yieldRatioSignal));
    RooRealVar yieldRatioBkg(("yieldRatioBkg_" + std::to_string(i)).c_str(), "",
                             0.05, -1, 1);
    RooFormulaVar yieldBkgK(("yieldBkgK_" + std::to_string(i)).c_str(), "",
                            "@0*@1", RooArgList(yieldBkgPi, yieldRatioBkg));

    // ---------------------------- Add PDFs and yields
    // ----------------------------
    RooArgSet yieldsPi;
    yieldsPi.add(yieldSignalPi);
    // yieldsPi.add(yieldBkgPi);

    RooArgSet functionsBuPi;
    functionsBuPi.add(pdfBuSignalPi);
    // functionsPi.add(pdfBuBkgPi);
    RooAddPdf pdfBuPi(("pdfBuPi_" + std::to_string(i)).c_str(), "",
                      functionsBuPi, yieldsPi);

    RooArgSet functionsDeltaPi;
    functionsDeltaPi.add(pdfDeltaSignal);
    // functionsPi.add(pdfDeltaBkgPi);
    RooAddPdf pdfDeltaPi(("pdfDeltaPi_" + std::to_string(i)).c_str(), "",
                         functionsDeltaPi, yieldsPi);

    RooArgSet yieldsK;
    yieldsK.add(yieldSignalK);
    // yieldsK.add(yieldBkgK);

    RooArgSet functionsBuK;
    functionsBuK.add(pdfBuSignalK);
    // functionsK.add(pdfBuBkgK);
    RooAddPdf pdfBuK(("pdfBuK_" + std::to_string(i)).c_str(), "",
                      functionsBuK, yieldsK);

    RooArgSet functionsDeltaK;
    functionsDeltaK.add(pdfDeltaSignal);
    // functionsK.add(pdfDeltaBkgK);
    RooAddPdf pdfDeltaK(("pdfDeltaK_" + std::to_string(i)).c_str(), "",
                         functionsDeltaK, yieldsK);


    // ---------------------------- Construct Sim PDF
    // ----------------------------
    RooSimultaneous simPdf(("simPdf_" + std::to_string(i)).c_str(), "",
                           fitting);
    simPdf.addPdf(pdfBuPi, "bu_gamma_pi");
    simPdf.addPdf(pdfDeltaPi, "delta_gamma_pi");
    simPdf.addPdf(pdfBuK, "bu_gamma_K");
    simPdf.addPdf(pdfDeltaK, "delta_gamma_K");

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

    // ---------------------------- Fit Sim PDF to toy
    // ----------------------------
    std::unique_ptr<RooFitResult> result = std::unique_ptr<RooFitResult>(
        simPdf.fitTo(*toyAbsData, RooFit::Extended(true),
                     RooFit::SplitRange(true),
                     RooFit::Save(),
                     RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                     RooFit::Offset(true), 
                     RooFit::NumCPU(8, 2)));

    // ---------------------------- Save result to file
    // ----------------------------
    outputFile.cd();
    result->SetName(("Result" + std::to_string(randomTag)).c_str());
    result->Write();
    outputFile.Close();

    std::cout << "Result saved in file " << outputDir << "/ResultFile"
              << std::to_string(randomTag) << ".root\n";

    // ---------------------------- Plot if specified
    // ----------------------------
    if (toPlot == true && i == 0) {
      std::cout << "Plotting projections of m[Bu]\n";
      PlotComponent(Neutral::gamma, Bachelor::pi, Variable::bu, buMass,
                    toyDataHist.get(), simPdf, fitting, //pdfSignalBuPi, pdfBkgBuPi,
                    outputDir);
      PlotComponent(Neutral::gamma, Bachelor::k, Variable::bu, buMass,
                    toyDataHist.get(), simPdf, fitting, //pdfSignalBuK, pdfBkgBuK,
                    outputDir);
      std::cout << "Plotting projections of m[Delta]\n";
      PlotComponent(Neutral::gamma, Bachelor::pi, Variable::delta, deltaMass,
                    toyDataHist.get(), simPdf, fitting, //pdfSignalDeltaPi, pdfBkgDeltaPi,
                    outputDir);
      PlotComponent(Neutral::gamma, Bachelor::k, Variable::delta, deltaMass,
                    toyDataHist.get(), simPdf, fitting, //pdfSignalDeltaK, pdfBkgDeltaK,
                    outputDir);
      std::cout << "Plotting correlation matrix\n";
      PlotCorrMatrix(result.get(), outputDir);
    }
    result->Print("v");
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
