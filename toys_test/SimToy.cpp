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
#include "RooPlot.h"
#include "RooPolyVar.h"
#include "RooProdPdf.h"
#include "RooRandom.h"
#include "RooRealVar.h"
#include "RooSimultaneous.h"
#include "RooTreeData.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TPad.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TTreeReader.h"

void SimToy() {
  TApplication app("app", 0, 0);
  RooRandom::randomGenerator()->SetSeed(15);

  int delta_low = 0;
  int delta_high = 210;

  int delta_nbins = (delta_high - delta_low) / 2;

  RooRealVar deltaMass("Delta_M", "m[D^{*0}] - m[D^{0}]", delta_low, delta_high,
		       "MeV/c^{2}");
  
  deltaMass.setRange("range_pi0", 135, 210);
  deltaMass.setRange("range_gamma", 50, 210);

  deltaMass.setBins(delta_nbins);

  // DEFINE INDEX CATEGORIES
  RooCategory neutral("neutral", "neutral");
  neutral.defineType("pi0");
  neutral.defineType("gamma");

  // DEFINE pi0 PDFs
  // Signal
  RooRealVar meanDeltaSigPi0("meanDeltaSigPi0", "Mean of Sig m[Delta]", 145,
			     140, 150);
  RooRealVar sigmaDeltaSigPi0("sigmaDeltaSigPi0", "Sigma of pi Delta Gaussian",
			      3, 0, 5);
  RooGaussian pdfDeltaSigPi0("pdfDeltaSigPi0", "Sig pi Delta PDF", deltaMass,
			     meanDeltaSigPi0, sigmaDeltaSigPi0);

  // Background
  RooRealVar thDeltaBkgPi0("thDeltaBkgPi0", "", 1.3415e+02);  //, 30, 50);

  RooRealVar aDeltaBkgPi0("aDeltaBkgPi0", "", 5.3768e-01);   //, -1, 1);
  RooRealVar bDeltaBkgPi0("bDeltaBkgPi0", "", -4.4782e-01);  //, -1, 1);
  RooRealVar cDeltaBkgPi0("cDeltaBkgPi0", "", 5.8018e+00);   //, 0, 35);

  RooDstD0BG pdfDeltaBkgPi0("pdfDeltaBkgPi0", "", deltaMass, thDeltaBkgPi0,
			    cDeltaBkgPi0, aDeltaBkgPi0, bDeltaBkgPi0);

  // ROOADDPDF
  RooRealVar yieldSigPi0("yieldSigPi0", "", 1000, 0, 5000);
  RooRealVar yieldBkgPi0("yieldBkgPi0", "", 10000, 0, 50000);

  RooArgSet yieldsPi0;
  yieldsPi0.add(yieldSigPi0);
  yieldsPi0.add(yieldBkgPi0);
  RooArgSet functionsPi0;
  functionsPi0.add(pdfDeltaSigPi0);
  functionsPi0.add(pdfDeltaBkgPi0);

  RooAddPdf pdfPi0("pdfPi0", "", functionsPi0, yieldsPi0);

  // DEFINE gamma PDFs
  // Signal Gamma
  RooRealVar meanDeltaSigGamma1("meanDeltaSigGamma1", "Mean of Sig m[Delta]",
				145, 140, 150);
  RooRealVar sigmaDeltaSigGamma1("sigmaDeltaSigGamma1",
				 "Sigma of pi Delta Gaussian", 10, 0, 20);
  RooGaussian pdfDeltaSigGamma1("pdfDeltaSigGamma1", "Sig pi Delta PDF",
				deltaMass, meanDeltaSigGamma1,
				sigmaDeltaSigGamma1);
  // Signal Pi0
  RooRealVar meanDeltaSigGamma2("meanDeltaSigGamma2", "Mean of Sig m[Delta]",
				85, 80, 90);
  RooRealVar sigmaDeltaSigGamma2("sigmaDeltaSigGamma2",
				 "Sigma of pi Delta Gaussian", 10, 0, 20);
  RooGaussian pdfDeltaSigGamma2("pdfDeltaSigGamma2", "Sig pi Delta PDF",
				deltaMass, meanDeltaSigGamma2,
				sigmaDeltaSigGamma2);

  RooRealVar meanDeltaSigGamma3("meanDeltaSigGamma3", "Mean of Sig m[Delta]",
				25, 20, 30);
  RooRealVar sigmaDeltaSigGamma3("sigmaDeltaSigGamma3",
				 "Sigma of pi Delta Gaussian", 10, 0, 20);
  RooGaussian pdfDeltaSigGamma3("pdfDeltaSigGamma3", "Sig pi Delta PDF",
				deltaMass, meanDeltaSigGamma3,
				sigmaDeltaSigGamma3);

  // Background
  RooRealVar thDeltaBkgGamma("thDeltaBkgGamma", "", 5.2160e+01);  //, 30, 50);

  RooRealVar aDeltaBkgGamma("aDeltaBkgGamma", "", 1.0341e+00);   //, -1, 1);
  RooRealVar bDeltaBkgGamma("bDeltaBkgGamma", "", -1.2284e+00);  //, -1, 1);
  RooRealVar cDeltaBkgGamma("cDeltaBkgGamma", "", 4.2450e+01);   //, 0, 35);

  RooDstD0BG pdfDeltaBkgGamma("pdfDeltaBkgGamma", "", deltaMass,
			      thDeltaBkgGamma, cDeltaBkgGamma, aDeltaBkgGamma,
			      bDeltaBkgGamma);

  // ROOADDPDF
  RooRealVar yieldSigGamma1("yieldSigGamma1", "", 2000, 0, 5000);
  RooRealVar crossFeed("crossFeed", "", 1.5, 0, 5);
  RooFormulaVar yieldSigGamma2("yieldSigGamma2", "", "@0*@1",
			       RooArgList(yieldSigPi0, crossFeed));
  RooRealVar yieldSigGamma3("yieldSigGamma3", "", 2000, 0, 5000);
  RooRealVar yieldBkgGamma("yieldBkgGamma", "", 20000, 0, 50000);

  RooArgSet yieldsGamma;
  yieldsGamma.add(yieldSigGamma1);
  yieldsGamma.add(yieldSigGamma2);
  yieldsGamma.add(yieldSigGamma3);
  yieldsGamma.add(yieldBkgGamma);
  RooArgSet functionsGamma;
  functionsGamma.add(pdfDeltaSigGamma1);
  functionsGamma.add(pdfDeltaSigGamma2);
  functionsGamma.add(pdfDeltaSigGamma3);
  functionsGamma.add(pdfDeltaBkgGamma);

  RooAddPdf pdfGamma("pdfGamma", "", functionsGamma, yieldsGamma);

  // Generate datasets

  auto dataPi0_1 =
      std::unique_ptr<RooDataSet>(pdfPi0.generate(RooArgSet(deltaMass), 11000));
  std::unique_ptr<RooDataSet> dataPi0;
  dataPi0 =
      std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(dataPi0_1->reduce(
          RooFit::CutRange("range==range::range_pi0"))));
  if (dataPi0.get() == nullptr) {
    throw std::runtime_error("Could not reduce pi0 input dataset.");
  }
  // dataPi0->Print();
  auto dataGamma_1 =
      std::unique_ptr<RooDataSet>(pdfGamma.generate(RooArgSet(deltaMass), 11000));
  std::unique_ptr<RooDataSet> dataGamma;
  dataGamma =
      std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(dataGamma_1->reduce(
          RooFit::CutRange("range==range::range_gamma"))));
  if (dataGamma.get() == nullptr) {
    throw std::runtime_error("Could not reduce gamma input dataset.");
  }
  // dataGamma->Print();

  RooDataSet combData("combData", "", RooArgSet(deltaMass),
		      RooFit::Index(neutral),
		      RooFit::Import("pi0", *dataPi0.get()),
		      RooFit::Import("gamma", *dataGamma.get()));

  // CONSTRUCT SIMULTANEOUS PDF
  RooSimultaneous simPdf("simPdf", "", neutral);
  simPdf.addPdf(pdfPi0, "pi0");
  simPdf.addPdf(pdfGamma, "gamma");

  std::unique_ptr<RooFitResult> result = std::unique_ptr<RooFitResult>(
      simPdf.fitTo(combData, RooFit::Extended(true),
                   RooFit::Range("range_neutral"),
                   // RooFit::SumCoefRange("range"),
                   RooFit::SplitRange(true),
                   RooFit::Save(),
                   RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                   RooFit::Offset(true))); 
                   // RooFit::NumCPU(8, 2)));

  // Plot
  std::unique_ptr<RooPlot> framePi0(deltaMass.frame(RooFit::Title("#pi^{0}")));

  combData.plotOn(framePi0.get(), RooFit::Cut("neutral==neutral::pi0"));

  simPdf.plotOn(framePi0.get(), RooFit::Slice(neutral, "pi0"),
		RooFit::ProjWData(neutral, combData));
  simPdf.plotOn(framePi0.get(), RooFit::Slice(neutral, "pi0"),
		RooFit::Components(pdfDeltaSigPi0.GetName()),
		RooFit::ProjWData(neutral, combData),
		RooFit::LineStyle(kDashed), RooFit::LineColor(kMagenta),
		RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
  simPdf.plotOn(framePi0.get(), RooFit::Slice(neutral, "pi0"),
		RooFit::Components(pdfDeltaBkgPi0.GetName()),
		RooFit::ProjWData(neutral, combData),
		RooFit::LineStyle(kDashed), RooFit::LineColor(kOrange),
		RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));

  std::unique_ptr<RooPlot> frameGamma(deltaMass.frame(RooFit::Title("#gamma")));

  combData.plotOn(frameGamma.get(), RooFit::Cut("neutral==neutral::gamma"));

  simPdf.plotOn(frameGamma.get(), RooFit::Slice(neutral, "gamma"),
		RooFit::ProjWData(neutral, combData));
  simPdf.plotOn(frameGamma.get(), RooFit::Slice(neutral, "gamma"),
		RooFit::Components(pdfDeltaSigGamma1.GetName()),
		RooFit::ProjWData(neutral, combData),
		RooFit::LineStyle(kDashed), RooFit::Precision(1e-3),
		RooFit::NumCPU(8, 2));
  simPdf.plotOn(frameGamma.get(), RooFit::Slice(neutral, "gamma"),
		RooFit::Components(pdfDeltaSigGamma2.GetName()),
		RooFit::ProjWData(neutral, combData),
		RooFit::LineStyle(kDashed), RooFit::LineColor(kMagenta),
		RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
  simPdf.plotOn(frameGamma.get(), RooFit::Slice(neutral, "gamma"),
		RooFit::Components(pdfDeltaBkgGamma.GetName()),
		RooFit::ProjWData(neutral, combData),
		RooFit::LineStyle(kDashed), RooFit::LineColor(kOrange),
		RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));
  simPdf.plotOn(frameGamma.get(), RooFit::Slice(neutral, "gamma"),
		RooFit::Components(pdfDeltaSigGamma3.GetName()),
		RooFit::ProjWData(neutral, combData),
		RooFit::LineStyle(kDashed), RooFit::Precision(1e-3),
		RooFit::NumCPU(8, 2));

  TCanvas canvas("canvas", "canvas", 1000, 400);
  canvas.SetTitle(" ");
  canvas.Divide(2);
  canvas.cd(1);
  canvas.SetLogy();
  gPad->SetLeftMargin(0.15);
  framePi0->GetYaxis()->SetTitleOffset(1.4);
  framePi0->Draw();
  canvas.cd(2);
  gPad->SetLeftMargin(0.15);
  frameGamma->GetYaxis()->SetTitleOffset(1.4);
  frameGamma->Draw();

  canvas.SaveAs("SimToy.pdf");

  result->Print("v");
  app.Run(true);
}

int main() {
  SimToy();
  return 0;
}
