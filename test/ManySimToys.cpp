#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooCBShape.h"
#include "RooCategory.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
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
#include "TH2.h"
#include "TPad.h"
#include "TRandom3.h"
#include "TStyle.h"

void GenerateToys() {
  RooRandom::randomGenerator()->SetSeed(0);
  TRandom3 r3(0);

  // Number of toys to run
  Int_t n_toys = 5;

  // Number of events to generate
  Int_t n_events = 100000;

  int bu_low = 5045;
  int bu_high = 5805;
  int delta_low = 80;
  int delta_high = 240;

  int bu_nbins = (bu_high - bu_low) / 5;
  int delta_nbins = (delta_high - delta_low) / 2;

  RooRealVar buMass("Bu_M_DTF_D0", "m[D^{*0}#pi^{#pm}]", bu_low, bu_high,
                    "MeV/c^{2}");
  RooRealVar deltaMass("Delta_M", "m[D^{*0}] - m[D^{0}]", delta_low, delta_high,
                       "MeV/c^{2}");

  buMass.setBins(bu_nbins);
  deltaMass.setBins(delta_nbins);

  // DEFINE INDEX CATEGORIES
  RooCategory bachelor("bachelor", "bachelor");
  bachelor.defineType("pi");
  bachelor.defineType("k");

  // Values and their errors get saved into histograms after each fit
  TH1F *hist_a0MeanBuSignal =
      new TH1F("hist_a0MeanBuSignal", "", 40, 4800, 5600);
  TH1F *hist_a0MeanBuSignal_err =
      new TH1F("hist_a0MeanBuSignal_err", "", 40, 30, 50);
  TH1F *hist_a0MeanBuSignal_pull =
      new TH1F("hist_a0MeanBuSignal_pull", "", 40, -5, 5);

  TH1F *hist_a1MeanBuSignal = new TH1F("hist_a1MeanBuSignal", "", 40, 0, 10);
  TH1F *hist_a1MeanBuSignal_err =
      new TH1F("hist_a1MeanBuSignal_err", "", 40, 0, 2);
  TH1F *hist_a1MeanBuSignal_pull =
      new TH1F("hist_a1MeanBuSignal_pull", "", 40, -5, 5);

  TH1F *hist_a2MeanBuSignal =
      new TH1F("hist_a2MeanBuSignal", "", 40, -0.02, 0.02);
  TH1F *hist_a2MeanBuSignal_err =
      new TH1F("hist_a2MeanBuSignal_err", "", 40, 0, 0.005);
  TH1F *hist_a2MeanBuSignal_pull =
      new TH1F("hist_a2MeanBuSignal_pull", "", 40, -5, 5);

  double a0MeanBuSignal_init = 5101.86875;
  double a1MeanBuSignal_init = 2.1375;
  double a2MeanBuSignal_init = -0.0062;
  // run n_toys fits and store the values in the histograms
  for (int i = 0; i < n_toys; i++) {
    // DEFINE pi PDFs
    // SIGNAL
    RooRealVar meanDeltaSignal("meanDeltaSignal", "Mean of Signal m[Delta]",
                               145, 140, 150);
    RooRealVar a0MeanBuSignal("a0MeanBuSignal",
                              "a0 of mean of Signal m[Bu] PDF", 5101.86875,
                              4879, 5579);
    RooRealVar a1MeanBuSignal("a1MeanBuSignal",
                              "a1 of mean of Signal m[Bu] PDF", 2.1375, 0, 10);
    RooRealVar a2MeanBuSignal("a2MeanBuSignal",
                              "a2 of mean of Signal m[Bu] PDF", -0.0062, -0.01,
                              -0.00001);
    RooPolyVar meanBuSignal(
        "meanBuSignal", "Mean of Signal m[Bu]", deltaMass,
        RooArgList(a0MeanBuSignal, a1MeanBuSignal, a2MeanBuSignal));
    RooRealVar sigmaDeltaSignalPi("sigmaDeltaSignalPi",
                                  "Sigma of pi delta Gaussian", 20, 0, 40);
    RooGaussian pdfDeltaSignalPi("pdfDeltaSignalPi", "Signal pi Delta PDF",
                                 deltaMass, meanDeltaSignal,
                                 sigmaDeltaSignalPi);
    RooRealVar sigmaBuSignalPi("sigmaBuSignalPi", "Sigma of pi Bu Gaussian",
                               100, 0, 150);
    RooGaussian pdfBuSignalPi("pdfBuSignalPi", "Signal pi Bu PDF", buMass,
                              meanBuSignal, sigmaBuSignalPi);
    RooProdPdf pdfSignalPi("pdfSignalPi", "Signal pi 2D PDF", pdfDeltaSignalPi,
                           RooFit::Conditional(pdfBuSignalPi, buMass));
    // BACKGROUND
    RooRealVar lambdaDeltaCombPi("lambdaDeltaCombPi", "lambda of delta comb pi",
                                 -0.001, -1, 1);
    RooRealVar a0LambdaBuCombPi("a0LambdaBuCombPi",
                                "a0 of lambda of bu comb pi", -0.001, -1, 1);
    RooPolyVar lambdaBuCombPi("lambdaBuCombPi", "lambda of bu comb pi",
                              deltaMass, RooArgList(a0LambdaBuCombPi));
    RooExponential pdfDeltaCombPi("pdfDeltaCombPi", "pdf of delta pi comb",
                                  deltaMass, lambdaDeltaCombPi);
    RooExponential pdfBuCombPi("pdfBuCombPi", "pdf of bu pi comb", buMass,
                               lambdaBuCombPi);
    RooProdPdf pdfCombPi("pdfCombPi", "pdf of pi comb", pdfDeltaCombPi,
                         RooFit::Conditional(pdfBuSignalPi, buMass));
    // ROOADDPDF
    RooRealVar yieldSignalPi("yieldSignalPi", "yield of pi signal", 100000, 0,
                             500000);
    RooRealVar yieldBackgroundPi("yieldBackgroundPi", "yield of pi background",
                                 10000, 0, 50000);

    RooArgSet yieldsPi;
    yieldsPi.add(yieldSignalPi);
    yieldsPi.add(yieldBackgroundPi);
    RooArgSet functionsPi;
    functionsPi.add(pdfSignalPi);
    functionsPi.add(pdfCombPi);

    RooAddPdf pdfPi("pdfPi", "pdf pi", functionsPi, yieldsPi);

    // DEFINE K SIGNAL PDFs
    // SIGNAL
    RooRealVar sigmaRatio("sigmaRatio", "sigmaRatio", 0.95, 0, 1);
    RooFormulaVar sigmaDeltaSignalK("sigmaDeltaSignalK",
                                    "Sigma of k delta Gaussian", "@0*@1",
                                    RooArgList(sigmaDeltaSignalPi, sigmaRatio));
    RooGaussian pdfDeltaSignalK("pdfDeltaSignalK", "Signal k Delta PDF",
                                deltaMass, meanDeltaSignal, sigmaDeltaSignalK);
    RooFormulaVar sigmaBuSignalK("sigmaBuSignalK", "Sigma of k Bu Gaussian",
                                 "@0*@1",
                                 RooArgList(sigmaBuSignalPi, sigmaRatio));
    RooGaussian pdfBuSignalK("pdfBuSignalK", "Signal k Bu PDF", buMass,
                             meanBuSignal, sigmaBuSignalK);
    RooProdPdf pdfSignalK("pdfSignalK", "Signal k 2D PDF", pdfDeltaSignalK,
                          RooFit::Conditional(pdfBuSignalK, buMass));
    // BACKGROUND
    RooRealVar lambdaDeltaCombK("lambdaDeltaCombK", "lambda of delta comb k",
                                -0.001, -1, 1);
    RooRealVar a0LambdaBuCombK("a0LambdaBuCombK", "a0 of lambda of bu comb k",
                               -0.001, -1, 1);
    RooPolyVar lambdaBuCombK("lambdaBuCombK", "lambda of bu comb k", deltaMass,
                             RooArgList(a0LambdaBuCombK));
    RooExponential pdfDeltaCombK("pdfDeltaCombK", "pdf of delta k comb",
                                 deltaMass, lambdaDeltaCombK);
    RooExponential pdfBuCombK("pdfBuCombK", "pdf of bu k comb", buMass,
                              lambdaBuCombK);
    RooProdPdf pdfCombK("pdfCombK", "pdf of k comb", pdfDeltaCombK,
                        RooFit::Conditional(pdfBuSignalK, buMass));
    // ROOADDPDF
    RooRealVar yieldRatio("yieldRatio", "yieldRatio", 0.1, 0, 1);
    RooFormulaVar yieldSignalK("yieldSignalK", "yield of k signal", "@0*@1",
                               RooArgList(yieldSignalPi, yieldRatio));
    RooRealVar yieldBackgroundK("yieldBackgroundK", "yield of k background",
                                100, 0, 500);

    RooArgSet yieldsK;
    yieldsK.add(yieldSignalK);
    yieldsK.add(yieldBackgroundK);
    RooArgSet functionsK;
    functionsK.add(pdfSignalK);
    functionsK.add(pdfCombK);

    RooAddPdf pdfK("pdfK", "pdf k", functionsK, yieldsK);

    // CONSTRUCT SIMULTANEOUS PDF
    RooSimultaneous simPdf(("simPdf_" + std::to_string(i)).c_str(),
                           ("simPdf_" + std::to_string(i)).c_str(), bachelor);
    simPdf.addPdf(pdfPi, "pi");
    simPdf.addPdf(pdfK, "k");

    RooDataSet *toyDataSet =
        simPdf.generate(RooArgSet(buMass, deltaMass, bachelor), n_events);
    toyDataSet->SetName(("toyDataSet_" + std::to_string(i)).c_str());
    auto toyDataHist = std::unique_ptr<RooDataHist>(
        toyDataSet->binnedClone(("toyDataHist_" + std::to_string(i)).c_str(),
                                ("toyDataHist" + std::to_string(i)).c_str()));
    auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

    meanDeltaSignal.setVal(142);

    RooFitResult *result = 0;
    result = simPdf.fitTo(*toyAbsData, RooFit::Save(true));

    // Fill histograms
    if (result->covQual() > 2 && result->status() == 0) {
      hist_a0MeanBuSignal->Fill(a0MeanBuSignal.getVal());
      hist_a0MeanBuSignal_err->Fill(a0MeanBuSignal.getError());
      hist_a0MeanBuSignal_pull->Fill(
          (a0MeanBuSignal.getVal() - a0MeanBuSignal_init) /
          a0MeanBuSignal.getError());

      hist_a1MeanBuSignal->Fill(a1MeanBuSignal.getVal());
      hist_a1MeanBuSignal_err->Fill(a1MeanBuSignal.getError());
      hist_a1MeanBuSignal_pull->Fill(
          (a1MeanBuSignal.getVal() - a1MeanBuSignal_init) /
          a1MeanBuSignal.getError());

      hist_a2MeanBuSignal->Fill(a2MeanBuSignal.getVal());
      hist_a2MeanBuSignal_err->Fill(a2MeanBuSignal.getError());
      hist_a2MeanBuSignal_pull->Fill(
          (a2MeanBuSignal.getVal() - a2MeanBuSignal_init) /
          a2MeanBuSignal.getError());
      result->Print("v");
    } else {
      result->Print("v");
    }
    if (result->edm() > 0.2) {
      result->Print("v");
    }
  }

  TCanvas canvas_a0("canvas_a0", "", 1500, 500);
  canvas_a0.Divide(3, 1);
  canvas_a0.cd(1);
  hist_a0MeanBuSignal->GetXaxis()->SetTitle("a0 Mean");
  hist_a0MeanBuSignal->SetTitle(" ");
  hist_a0MeanBuSignal->Draw();
  canvas_a0.cd(2);
  hist_a0MeanBuSignal_err->GetXaxis()->SetTitle("a0 Mean Error");
  hist_a0MeanBuSignal_err->SetTitle(" ");
  hist_a0MeanBuSignal_err->Draw();
  canvas_a0.cd(3);
  hist_a0MeanBuSignal_pull->GetXaxis()->SetTitle("a0 Mean Pull");
  hist_a0MeanBuSignal_pull->SetTitle(" ");
  hist_a0MeanBuSignal_pull->Draw();
  canvas_a0.SaveAs("a0MeanBuSignal.pdf");

  TCanvas canvas_a1("canvas_a1", "", 1500, 500);
  canvas_a1.Divide(3, 1);
  canvas_a1.cd(1);
  hist_a1MeanBuSignal->GetXaxis()->SetTitle("a1 Mean");
  hist_a1MeanBuSignal->SetTitle(" ");
  hist_a1MeanBuSignal->Draw();
  canvas_a1.cd(2);
  hist_a1MeanBuSignal_err->GetXaxis()->SetTitle("a1 Mean Error");
  hist_a1MeanBuSignal_err->SetTitle(" ");
  hist_a1MeanBuSignal_err->Draw();
  canvas_a1.cd(3);
  hist_a1MeanBuSignal_pull->GetXaxis()->SetTitle("a1 Mean Pull");
  hist_a1MeanBuSignal_pull->SetTitle(" ");
  hist_a1MeanBuSignal_pull->Draw();
  canvas_a1.SaveAs("a1MeanBuSignal.pdf");

  TCanvas canvas_a2("canvas_a2", "", 1500, 500);
  canvas_a2.Divide(3, 1);
  canvas_a2.cd(1);
  hist_a2MeanBuSignal->GetXaxis()->SetTitle("a2 Mean");
  hist_a2MeanBuSignal->SetTitle(" ");
  hist_a2MeanBuSignal->Draw();
  canvas_a2.cd(2);
  hist_a2MeanBuSignal_err->GetXaxis()->SetTitle("a2 Mean Error");
  hist_a2MeanBuSignal_err->SetTitle(" ");
  hist_a2MeanBuSignal_err->Draw();
  canvas_a2.cd(3);
  hist_a2MeanBuSignal_pull->GetXaxis()->SetTitle("a2 Mean Pull");
  hist_a2MeanBuSignal_pull->SetTitle(" ");
  hist_a2MeanBuSignal_pull->Draw();
  canvas_a2.SaveAs("a2MeanBuSignal.pdf");
}

int main() {
  GenerateToys();
  return 0;
}
