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
  RooRandom::randomGenerator()->SetSeed(0);

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
  
  // DEFINE INDEX CATEGORIES
  RooCategory variable("variable", "variable");
  variable.defineType("bu");
  variable.defineType("delta");

  // DEFINE PDFs
  // Signal
  RooRealVar meanDeltaSig("meanDeltaSig", "Mean of Sig m[Delta]", 145,
			     140, 150);
  RooRealVar sigmaDeltaSig("sigmaDeltaSig", "Sigma of pi Delta Gaussian",
			      8, 0, 15);
  RooGaussian pdfDeltaSig("pdfDeltaSig", "Sig pi Delta PDF", deltaMass,
			     meanDeltaSig, sigmaDeltaSig);

  RooRealVar meanBuSig("meanBuSig", "Mean of Sig m[Bu]", 5280,
			     5275, 5285);
  RooRealVar sigmaBuSig("sigmaBuSig", "Sigma of pi Bu Gaussian",
			      30, 0, 50);
  RooGaussian pdfBuSig("pdfBuSig", "Sig pi Bu PDF", buMass,
			     meanBuSig, sigmaBuSig);

  // ROOADDPDF
  RooRealVar yieldSig("yieldSig", "", 1000, 0, 5000);

  RooArgSet yields;
  yields.add(yieldSig);

  RooArgSet functionsBu;
  functionsBu.add(pdfBuSig);
  RooAddPdf pdfBu("pdfBu", "", functionsBu, yields);

  RooArgSet functionsDelta;
  functionsDelta.add(pdfDeltaSig);
  RooAddPdf pdfDelta("pdfDelta", "", functionsDelta, yields);

  // CONSTRUCT SIMULTANEOUS PDF
  RooSimultaneous simPdf("simPdf", "", variable);
  simPdf.addPdf(pdfBu, "bu");
  simPdf.addPdf(pdfDelta, "delta");
  
  // Generate datasets
  auto dataBu = std::unique_ptr<RooDataSet>(
      pdfBu.generate(RooArgSet(buMass), simPdf.expectedEvents(variable)));
  if (dataBu.get() == nullptr) {
    throw std::runtime_error("Could not reduce pi0 input dataset.");
  }
  dataBu->Print();

  auto dataDelta = std::unique_ptr<RooDataSet>(
      pdfDelta.generate(RooArgSet(deltaMass), simPdf.expectedEvents(variable)));
  if (dataDelta.get() == nullptr) {
    throw std::runtime_error("Could not reduce pi0 input dataset.");
  }
  dataDelta->Print();

  RooDataSet combData("combData", "", RooArgSet(buMass, deltaMass),
		      RooFit::Index(variable),
		      RooFit::Import("bu", *dataBu.get()),
		      RooFit::Import("delta", *dataDelta.get()));

  std::unique_ptr<RooFitResult> result = std::unique_ptr<RooFitResult>(
      simPdf.fitTo(combData, RooFit::Extended(true),
                   RooFit::SplitRange(true),
                   RooFit::Save(),
                   RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                   RooFit::Offset(true), 
                   RooFit::NumCPU(8, 2)));

  // Plot
  std::unique_ptr<RooPlot> frameBu(buMass.frame(RooFit::Title("m[D^{*0}#pi]")));

  combData.plotOn(frameBu.get(), RooFit::Cut("variable==variable::bu"));

  simPdf.plotOn(frameBu.get(), RooFit::Slice(variable, "bu"),
		RooFit::ProjWData(variable, combData));
  // simPdf.plotOn(frameBu.get(), RooFit::Slice(variable, "bu"),
	// 	RooFit::Components(pdfBuSig.GetName()),
	// 	RooFit::ProjWData(variable, combData),
	// 	RooFit::LineStyle(kDashed), RooFit::LineColor(kMagenta),
	// 	RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));

  std::unique_ptr<RooPlot> frameDelta(deltaMass.frame(RooFit::Title("m[D^{*0}] - m[D^{0}]")));

  combData.plotOn(frameDelta.get(), RooFit::Cut("variable==variable::delta"));

  simPdf.plotOn(frameDelta.get(), RooFit::Slice(variable, "delta"),
		RooFit::ProjWData(variable, combData));
  // simPdf.plotOn(frameDelta.get(), RooFit::Slice(variable, "delta"),
	// 	RooFit::Components(pdfDeltaSig.GetName()),
	// 	RooFit::ProjWData(variable, combData),
	// 	RooFit::LineStyle(kDashed), RooFit::LineColor(kMagenta),
	// 	RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));

  TCanvas canvas("canvas", "canvas", 1000, 400);
  canvas.SetTitle(" ");
  canvas.Divide(2);
  canvas.cd(1);
  canvas.SetLogy();
  gPad->SetLeftMargin(0.15);
  frameBu->GetYaxis()->SetTitleOffset(1.4);
  frameBu->Draw();
  canvas.cd(2);
  gPad->SetLeftMargin(0.15);
  frameDelta->GetYaxis()->SetTitleOffset(1.4);
  frameDelta->Draw();

  canvas.SaveAs("SimpleToy.pdf");

  result->Print("v");
  app.Run(true);
}

int main() {
  SimToy();
  return 0;
}
