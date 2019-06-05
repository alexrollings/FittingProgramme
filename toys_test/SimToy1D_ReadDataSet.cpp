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

void PlotComponent(Variable variable,
                   RooRealVar &var, RooDataHist *dataHist,
                   RooSimultaneous &simPdf, RooCategory &fitting,
                   RooAddPdf &sig, RooAbsPdf &bkg,
                   std::string const &path) {
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
      title = "m[D^{*0}] - m[D^{0}]";
      break;
  }

  auto frame =
      std::unique_ptr<RooPlot>(var.frame(RooFit::Title(title.c_str())));

  RooHist *pullHist = nullptr;
  std::unique_ptr<RooPlot> pullFrame(var.frame(RooFit::Title(" ")));

  dataHist->plotOn(frame.get(),
                   RooFit::Cut(("fitting==fitting::" +
                                EnumToString(variable))
                                   .c_str()));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(fitting, EnumToString(variable).c_str()),
      RooFit::ProjWData(fitting, *dataHist), RooFit::LineColor(kBlue));
  pullHist = frame->RooPlot::pullHist();
  simPdf.plotOn(frame.get(),
                RooFit::Slice(fitting, EnumToString(variable).c_str()),
                RooFit::ProjWData(fitting, *dataHist),
                RooFit::Components(sig.GetName()), RooFit::LineColor(kBlue),
                RooFit::LineStyle(kDashed));
  simPdf.plotOn(frame.get(),
                RooFit::Slice(fitting, EnumToString(variable).c_str()),
                RooFit::ProjWData(fitting, *dataHist),
                RooFit::Components(bkg.GetName()), RooFit::LineColor(kRed),
                RooFit::LineStyle(kDashed));

  dataHist->plotOn(frame.get(),
                   RooFit::Cut(("fitting==fitting::" +
                                EnumToString(variable))
                                   .c_str()));

  if (pullHist != 0) {
    pullFrame->addPlotable(pullHist /* .get() */, "P");
    pullFrame->SetName(
        ("pullFrame_" + EnumToString(variable)).c_str());
    pullFrame->SetTitle("");
  }

  TCanvas canvas(("canvas_" + EnumToString(variable)).c_str(),
                 "", 1200, 1000);

  TPad pad1(("pad1_" + EnumToString(variable)).c_str(), "",
            0.0, 0.14, 1.0, 1.0, kWhite);
  pad1.Draw();

  TPad pad2(("pad2_" + EnumToString(variable)).c_str(), "",
            0.0, 0.05, 1.0, 0.15, kWhite);
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
  canvas.SaveAs((path + "/1d_plots/" +
                 EnumToString(variable) + ".pdf")
                    .c_str());
}

void PlotCorrMatrix(RooFitResult *result, std::string const &path) {
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
  corrCanvas.SaveAs((path + "/1d_plots/CorrelationMatrix.pdf").c_str());
}

void GenerateToys(std::string const &path) {
  int bu_low = 5050;
  int bu_high = 5800;
  int delta_low = 60;  // 134;
  int delta_high = 210;

  int bu_nbins = (bu_high - bu_low) / 10;
  int delta_nbins = (delta_high - delta_low) / 2;

  // ---------------------------- Fitting Vars ----------------------------
  RooRealVar buMass("Bu_Delta_M", "m[D^{*0}#pi^{#pm}] - m[D^{*0}]", bu_low, bu_high,
                    "MeV/c^{2}");
  RooRealVar deltaMass("Delta_M", "m[D^{*0}] - m[D^{0}]", delta_low, delta_high,
                       "MeV/c^{2}");

  buMass.setBins(bu_nbins);
  deltaMass.setBins(delta_nbins);

  // ---------------------------- Categories ----------------------------
  RooCategory fitting("fitting", "fitting");
  fitting.defineType("bu");
  fitting.defineType("delta");

  // ---------------------------- PDFs ----------------------------
  //
  // ---------------------------- Signal ----------------------------
  // ---------------------------- Mean ----------------------------
  RooRealVar meanDeltaSignal("meanDeltaSignal", "", 1.4276e+02, 135, 150);
  // ---------------------------- Sigmas ----------------------------
  RooRealVar sigmaDeltaSignal("sigmaDeltaSignal", "", 8.6601e+00, 5, 15);
  // ---------------------------- Tails ----------------------------
  RooRealVar a1DeltaSignal("a1DeltaSignal", "", 1.9251e+00);
  RooRealVar a2DeltaSignal("a2DeltaSignal", "", -7.4405e-01);
  RooRealVar n1DeltaSignal("n1DeltaSignal", "", 1.0441e+00);
  RooRealVar n2DeltaSignal("n2DeltaSignal", "", 4.2875e+00);
  // ---------------------------- PDFs ----------------------------
  RooCBShape pdfDeltaSignal1("pdfDeltaSignal1", "", deltaMass, meanDeltaSignal,
                             sigmaDeltaSignal, a1DeltaSignal, n1DeltaSignal);
  RooCBShape pdfDeltaSignal2("pdfDeltaSignal2", "", deltaMass, meanDeltaSignal,
                             sigmaDeltaSignal, a2DeltaSignal, n2DeltaSignal);
  RooRealVar fracPdf1DeltaSignal("fracPdf1DeltaSignal", "", 1.7974e-01);
  RooAddPdf pdfDeltaSignal("pdfDeltaSignal", "",
                           RooArgSet(pdfDeltaSignal1, pdfDeltaSignal2),
                           fracPdf1DeltaSignal);

  // ---------------------------- PDFs: Bu ----------------------------
  // ---------------------------- Signal ----------------------------
  // ---------------------------- Mean ----------------------------
  RooRealVar meanBuSignal("meanBuSignal", "", 5.2819e+03, 5280, 5290);
  // ---------------------------- Sigmas ----------------------------
  RooRealVar sigmaBuSignal("sigmaBuSignal", "", 2.0182e+01, 15, 30);  //, 300, 400);

  // ---------------------------- Tails ----------------------------
  RooRealVar a1BuSignal("a1BuSignal", "", 1.6160e+00);
  RooRealVar a2BuSignal("a2BuSignal", "", -1.5208e+00);
  RooRealVar n1BuSignal("n1BuSignal", "", 9.9933e+00);
  RooRealVar n2BuSignal("n2BuSignal", "", 6.4413e+00);
  // ---------------------------- PDFs ----------------------------
  RooRealVar fracPdf1BuSignal("fracPdf1BuSignal", "", 7.4517e-01);
  RooCBShape pdfBuSignal1("pdfBuSignal1", "", buMass, meanBuSignal,
                            sigmaBuSignal, a1BuSignal, n1BuSignal);
  RooCBShape pdfBuSignal2("pdfBuSignal2", "", buMass, meanBuSignal,
                            sigmaBuSignal, a2BuSignal, n2BuSignal);
  RooAddPdf pdfBuSignal("pdfBuSignal", "",
                          RooArgSet(pdfBuSignal1, pdfBuSignal2),
                          fracPdf1BuSignal);
  
  // ---------------------------- Background ----------------------------
  //
  RooRealVar lambdaDeltaBkg("lambdaDeltaBkg", "", 0.01, -0.1, 0.1);
  RooExponential pdfDeltaBkg("pdfDeltaBkg", "", deltaMass, lambdaDeltaBkg);

  // RooRealVar thresholdDeltaBkg("thresholdDeltaBkg", "", 4.7048e+01);
  // RooRealVar cDeltaBkg("cDeltaBkg", "", 6.2583e+01);
  // RooRealVar aDeltaBkg("aDeltaBkg", "", 8.1939e-01);
  // RooRealVar bDeltaBkg("bDeltaBkg", "", -7.9655e-01);
  // RooDstD0BG pdfDeltaBkg("pdfDeltaBkg", "", deltaMass, thresholdDeltaBkg,
  //                        cDeltaBkg, aDeltaBkg, bDeltaBkg);

  // ---------------------------- π/K shared PDFs: Bu
  // ----------------------------
  RooRealVar lambdaBuBkg("lambdaBuBkg", "", -0.005, -0.1, 0.1);
  RooExponential pdfBuBkg("pdfBuBkg", "", buMass, lambdaBuBkg);
  // // ---------------------------- Mean ----------------------------
  // RooRealVar mean1BuBkg("mean1BuBkg", "", 5.3544e+03, 5300, 5400);
  // RooRealVar mean2BuBkg("mean2BuBkg", "", 5.2230e+03, 5200, 5250);
  // // ---------------------------- Sigmas ----------------------------
  // RooRealVar sigma1BuBkg("sigma1BuBkg", "", 8.6260e+01, 50, 100);        //, 5, 15);
  // RooRealVar sigmaFracBuBkg("sigmaFracBuBkg", "", 8.2710e-01, 0, 1);  //, -0.1, 0.1);
  // RooFormulaVar sigma2BuBkg("sigma2BuBkg", "", "@0*@1",
  //                           RooArgSet(sigma1BuBkg, sigmaFracBuBkg));
  // // ---------------------------- Tails ----------------------------
  // RooRealVar a1BuBkg("a1BuBkg", "", 4.3289e+00);
  // RooRealVar a2BuBkg("a2BuBkg", "",  -1.0599e+00);
  // RooRealVar n1BuBkg("n1BuBkg", "",  2.0140e+00);
  // RooRealVar n2BuBkg("n2BuBkg", "", 2.1358e+01);
  // // ---------------------------- PDFs ----------------------------
  // RooCBShape pdfBuBkg1("pdfBuBkg1", "", buMass, mean1BuBkg, sigma1BuBkg,
  //                      a1BuBkg, n1BuBkg);
  // RooCBShape pdfBuBkg2("pdfBuBkg2", "", buMass, mean2BuBkg, sigma2BuBkg,
  //                      a2BuBkg, n2BuBkg);
  // RooRealVar fracPdf1BuBkg("fracPdf1BuBkg", "",  5.2225e-01);
  // RooAddPdf pdfBuBkg("pdfBuBkg", "", RooArgSet(pdfBuBkg1, pdfBuBkg2),
  //                    fracPdf1BuBkg);

  // ---------------------------- Yields ----------------------------
  // MC efficiency * 2D signal yield
  // Delta cut efficiency = 0.91467
  RooRealVar yieldBuSignal("yieldBuSignal", "", 36587, 0, 1000000);
  RooRealVar fracBuBkgYield("fracBuBkgYield", "", 0.33613, 0, 1);
  RooFormulaVar yieldBuBkg("yielBuBkg", "", "@0*@1",
                         RooArgSet(yieldBuSignal, fracBuBkgYield));

  // Bu cut efficiency = 0.95157
  RooRealVar yieldDeltaSignal("yieldDeltaSignal", "", 38062, 0, 1000000);
  RooRealVar fracDeltaBkgYield("fracDeltaBkgYield", "", 0.16613, 0, 1);
  RooFormulaVar yieldDeltaBkg("yielDeltaBkg", "", "@0*@1",
                         RooArgSet(yieldDeltaSignal, fracDeltaBkgYield));

  // ---------------------------- Add PDFs and yields
  // ----------------------------
  RooArgSet yieldsBu;
  yieldsBu.add(yieldBuSignal);
  yieldsBu.add(yieldBuBkg);

  RooArgSet functionsBu;
  functionsBu.add(pdfBuSignal);
  functionsBu.add(pdfBuBkg);
  RooAddPdf pdfBu("pdfBu", "", functionsBu, yieldsBu);

  RooArgSet yieldsDelta;
  yieldsDelta.add(yieldDeltaSignal);
  yieldsDelta.add(yieldDeltaBkg);

  RooArgSet functionsDelta;
  functionsDelta.add(pdfDeltaSignal);
  functionsDelta.add(pdfDeltaBkg);
  RooAddPdf pdfDelta("pdfDelta", "", functionsDelta, yieldsDelta);

  // ---------------------------- Construct Sim PDF
  // ----------------------------
  RooSimultaneous simPdf("simPdf", "", fitting);
  simPdf.addPdf(pdfBu, "bu");
  simPdf.addPdf(pdfDelta, "delta");

  // ---------------------------- Read in toy dataset
  // ----------------------------
  TFile in((path + "/DataFile.root").c_str(), "READ");
  RooDataSet *inputDataSet;
  gDirectory->GetObject("toyDataSet", inputDataSet);
  if (inputDataSet == nullptr) {
    throw std::runtime_error("Data set does not exist.");
  } else {
    std::cout << "inputDataSet extracted... \n";
    inputDataSet->Print();
  }

  auto dataBu_tmp = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
      inputDataSet->reduce("Delta_M>125&&Delta_M<175")));
  if (dataBu_tmp.get() == nullptr) {
    throw std::runtime_error("Could not reduce inputDataSet with delta mass.");
  }
  dataBu_tmp->Print();
  auto dataBu = std::unique_ptr<RooDataSet>(
      dynamic_cast<RooDataSet *>(dataBu_tmp->reduce(RooArgSet(buMass))));
  if (dataBu.get() == nullptr) {
    throw std::runtime_error("Could not reduce inputDataSet to Bu mass.");
  }
  dataBu->Print();

  auto dataDelta_tmp = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
      inputDataSet->reduce("Bu_Delta_M>5230&&Bu_Delta_M<5330")));
  if (dataDelta_tmp.get() == nullptr) {
    throw std::runtime_error("Could not reduce inputDataSet with bu mass.");
  }
  dataDelta_tmp->Print();
  auto dataDelta = std::unique_ptr<RooDataSet>(
      dynamic_cast<RooDataSet *>(dataDelta_tmp->reduce(RooArgSet(deltaMass))));
  if (dataDelta.get() == nullptr) {
    throw std::runtime_error("Could not reduce inputDataSet to Delta mass.");
  }
  dataDelta->Print();

  RooDataSet combData("combData", "", RooArgSet(buMass, deltaMass),
		      RooFit::Index(fitting),
		      RooFit::Import("bu", *dataBu.get()),
		      RooFit::Import("delta", *dataDelta.get()));
  combData.Print();

  auto toyDataHist = std::unique_ptr<RooDataHist>(
      combData.binnedClone("toyDataHist", "toyDataHist"));
  auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

  // meanDeltaSignal.setVal(142);

  // ---------------------------- Fit Sim PDF to toy
  // ----------------------------
  std::unique_ptr<RooFitResult> result =
      std::unique_ptr<RooFitResult>(simPdf.fitTo(
          *toyAbsData, RooFit::Extended(true), RooFit::SplitRange(true),
          RooFit::Save(), RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
          RooFit::Offset(true), RooFit::NumCPU(8, 2)));

  std::cout << "Plotting projections of m[Bu]\n";
  PlotComponent(Variable::bu, buMass, toyDataHist.get(), simPdf, fitting,
                pdfBuSignal, pdfBuBkg, path);
  std::cout << "Plotting projections of m[Delta]\n";
  PlotComponent(Variable::delta, deltaMass, toyDataHist.get(), simPdf, fitting,
                pdfDeltaSignal, pdfDeltaBkg, path);
  std::cout << "Plotting correlation matrix\n";
  PlotCorrMatrix(result.get(), path);
  result->Print("v");
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Enter directory\n";
    return 1;
  }
  std::string path = argv[1];
  GenerateToys(path);
  return 0;
}
