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
                   RooAddPdf &sig, RooExponential &bkg,
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
      title = "m[D^{*0}]";
      break;
    case Variable::delta:
      title = "m[D^{*0}]-m[D^{0}]";
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
  int delta_low = 70;  // 134;
  int delta_high = 210;

  int bu_nbins = (bu_high - bu_low) / 10;
  int delta_nbins = (delta_high - delta_low) / 2;

  // ---------------------------- Fitting Vars ----------------------------
  RooRealVar buMass("Bu_M_DTF_D0", "m[D^{*0}#pi^{#pm}]", bu_low, bu_high,
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
  RooRealVar meanDeltaSignal("meanDeltaSignal", "", 1.4257e+02);  //, 135, 150);
  // ---------------------------- Sigmas ----------------------------
  RooRealVar sigmaDeltaSignal("sigmaDeltaSignal", "", 8.4700e+00);  //, 5, 15);
  // ---------------------------- Tails ----------------------------
  RooRealVar a1DeltaSignal("a1DeltaSignal", "", 1.6863e+00);
  RooRealVar a2DeltaSignal("a2DeltaSignal", "", -5.6811e-01);
  RooRealVar n1DeltaSignal("n1DeltaSignal", "", 4.0630e+00);
  RooRealVar n2DeltaSignal("n2DeltaSignal", "", 4.4013e+00);
  // ---------------------------- PDFs ----------------------------
  RooCBShape pdfDeltaSignal1("pdfDeltaSignal1", "", deltaMass, meanDeltaSignal,
                             sigmaDeltaSignal, a1DeltaSignal, n1DeltaSignal);
  RooCBShape pdfDeltaSignal2("pdfDeltaSignal2", "", deltaMass, meanDeltaSignal,
                             sigmaDeltaSignal, a2DeltaSignal, n2DeltaSignal);
  RooRealVar fracPdf1DeltaSignal("fracPdf1DeltaSignal", "", 2.8498e-01);
  RooAddPdf pdfDeltaSignal("pdfDeltaSignal", "",
                           RooArgSet(pdfDeltaSignal1, pdfDeltaSignal2),
                           fracPdf1DeltaSignal);

  // ---------------------------- PDFs: Bu ----------------------------
  // ---------------------------- Signal ----------------------------
  // ---------------------------- Mean ----------------------------
  RooRealVar meanBuSignal("meanBuSignal", "", 5.2854e+03);  //, 4500, 5500);
  // ---------------------------- Sigmas ----------------------------
  RooRealVar sigmaBuSignal("sigmaBuSignal", "", 2.3604e+01);  //, 300, 400);

  // ---------------------------- Tails ----------------------------
  RooRealVar a1BuSignal("a1BuSignal", "", 9.9494e-01);
  RooRealVar a2BuSignal("a2BuSignal", "", -9.9380e-01);
  RooRealVar n1BuSignal("n1BuSignal", "", 10);
  RooRealVar n2BuSignal("n2BuSignal", "", 10);
  // ---------------------------- PDFs ----------------------------
  RooRealVar fracPdf1BuSignal("fracPdf1BuSignal", "", 9.1502e-02);
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
 
  // ---------------------------- π/K shared PDFs: Bu
  // ----------------------------
  RooRealVar lambdaBuBkg("lambdaBuBkg", "", 0.01, -0.1, 0.1);
  RooExponential pdfBuBkg("pdfBuBkg", "", deltaMass, lambdaBuBkg);

  // ---------------------------- Yields ----------------------------
  RooRealVar yieldSignal("yieldSignal", "", 40000, 0, 1000000);
  RooRealVar fracBkgYield("fracBkgYield", "", 0.2, 0, 1);
  RooFormulaVar yieldBkg("yieldBkg", "", "@0*@1",
                         RooArgSet(yieldSignal, fracBkgYield));

  // ---------------------------- Add PDFs and yields
  // ----------------------------
  RooArgSet yields;
  yields.add(yieldSignal);
  yields.add(yieldBkg);

  RooArgSet functionsBu;
  functionsBu.add(pdfBuSignal);
  functionsBu.add(pdfBuBkg);
  RooAddPdf pdfBu("pdfBu", "", functionsBu, yields);

  RooArgSet functionsDelta;
  functionsDelta.add(pdfDeltaSignal);
  functionsDelta.add(pdfDeltaBkg);
  RooAddPdf pdfDelta("pdfDelta", "", functionsDelta, yields);

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

  auto dataBu =
      std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
          inputDataSet->reduce(RooArgSet(buMass))));
  if (dataBu.get() == nullptr) {
    throw std::runtime_error("Could not reduce pi0 input dataset.");
  }
  dataBu->Print();

  auto dataDelta =
      std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
          inputDataSet->reduce(RooArgSet(deltaMass))));
  if (dataDelta.get() == nullptr) {
    throw std::runtime_error("Could not reduce pi0 input dataset.");
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
