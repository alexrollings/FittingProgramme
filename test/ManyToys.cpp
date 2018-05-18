#include "RooRandom.h"
#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooPolyVar.h"
#include "RooProdPdf.h"
#include "RooRealVar.h"
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
  Int_t n_toys = 1000;

  // Number of events to generate
  Int_t n_events = 100000;

  int bu_low = 5045;
  int bu_high = 5805;
  int delta_low = 80;
  int delta_high = 240;

  int bu_nbins = (bu_high - bu_low) / 5;
  int delta_nbins = (delta_high - delta_low) / 2;

  RooRealVar bu_mass("Bu_M_DTF_D0", "m[D^{*0}#pi^{#pm}]", bu_low, bu_high,
                     "MeV/c^{2}");
  RooRealVar delta_mass("Delta_M", "m[D^{*0}] - m[D^{0}]", delta_low,
                        delta_high, "MeV/c^{2}");

  bu_mass.setBins(bu_nbins);
  delta_mass.setBins(delta_nbins);

  // Values and their errors get saved into histograms after each fit
  TH1F *hist_a0_mean = new TH1F("hist_a0_mean", "", 40, 4800, 5600);
  TH1F *hist_a0_mean_err = new TH1F("hist_a0_mean_err", "", 40, 30, 50);
  TH1F *hist_a0_mean_pull = new TH1F("hist_a0_mean_pull", "", 40, -5, 5);

  TH1F *hist_a1_mean = new TH1F("hist_a1_mean", "", 40, 0, 10);
  TH1F *hist_a1_mean_err = new TH1F("hist_a1_mean_err", "", 40, 0, 2);
  TH1F *hist_a1_mean_pull = new TH1F("hist_a1_mean_pull", "", 40, -5, 5);

  TH1F *hist_a2_mean = new TH1F("hist_a2_mean", "", 40, -0.02, 0.02);
  TH1F *hist_a2_mean_err = new TH1F("hist_a2_mean_err", "", 40, 0, 0.005);
  TH1F *hist_a2_mean_pull = new TH1F("hist_a2_mean_pull", "", 40, -5, 5);

  double a0_mean_init = 5101.86875;
  double a1_mean_init = 2.1375;
  double a2_mean_init = -0.0062;
  // run n_toys fits and store the values in the histograms
  for (int i = 0; i < n_toys; i++) {
    // DEFINE PDFs
    RooRealVar delta_mean("delta_mean", "delta_mean", 145, 140, 150);
    RooRealVar delta_sigma("delta_sigma", "delta_sigma", 20, 0, 40);
    RooGaussian delta_gaus("delta_gaus", "", delta_mass, delta_mean,
                           delta_sigma);

    RooRealVar a0_mean("a0_mean", "a0_mean", a0_mean_init, 4879, 5579);
    RooRealVar a1_mean("a1_mean", "a1_mean", a1_mean_init, 0, 10);
    RooRealVar a2_mean("a2_mean", "a2_mean", a2_mean_init, -1, 1);
    RooPolyVar bu_mean("bu_mean", "", delta_mass,
                       RooArgSet(a0_mean, a1_mean, a2_mean));
    RooRealVar bu_sigma("bu_sigma", "", 100, 0, 150);
    RooGaussian bu_gaus("bu_gaus", "", bu_mass, bu_mean, bu_sigma);

    RooProdPdf pdf_tot("pdf_tot", "", delta_gaus,
                       RooFit::Conditional(bu_gaus, bu_mass));

    RooDataSet *toyData =
        pdf_tot.generate(RooArgSet(bu_mass, delta_mass), n_events);

    RooProdPdf *pdf_tot_fit = new RooProdPdf("pdf_tot_fit", "pdf_tot_fit");

    pdf_tot_fit = dynamic_cast<RooProdPdf *>(pdf_tot.Clone());

    delta_mean.setVal(142);

    RooFitResult *result = 0;
    result = pdf_tot_fit->fitTo(*toyData, RooFit::Save(true));

    // Fill histograms
    if (result->covQual() > 2 && result->status() == 0) {
      hist_a0_mean->Fill(a0_mean.getVal());
      hist_a0_mean_err->Fill(a0_mean.getError());
      hist_a0_mean_pull->Fill((a0_mean.getVal() - a0_mean_init) /
                              a0_mean.getError());

      hist_a1_mean->Fill(a1_mean.getVal());
      hist_a1_mean_err->Fill(a1_mean.getError());
      hist_a1_mean_pull->Fill((a1_mean.getVal() - a1_mean_init) /
                              a1_mean.getError());

      hist_a2_mean->Fill(a2_mean.getVal());
      hist_a2_mean_err->Fill(a2_mean.getError());
      hist_a2_mean_pull->Fill((a2_mean.getVal() - a2_mean_init) /
                              a2_mean.getError());
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
  hist_a0_mean->GetXaxis()->SetTitle("a0 Mean");
  hist_a0_mean->SetTitle(" ");
  hist_a0_mean->Draw();
  canvas_a0.cd(2);
  hist_a0_mean_err->GetXaxis()->SetTitle("a0 Mean Error");
  hist_a0_mean_err->SetTitle(" ");
  hist_a0_mean_err->Draw();
  canvas_a0.cd(3);
  hist_a0_mean_pull->GetXaxis()->SetTitle("a0 Mean Pull");
  hist_a0_mean_pull->SetTitle(" ");
  hist_a0_mean_pull->Draw();
  canvas_a0.SaveAs("a0_mean.pdf");

  TCanvas canvas_a1("canvas_a1", "", 1500, 500);
  canvas_a1.Divide(3, 1);
  canvas_a1.cd(1);
  hist_a1_mean->GetXaxis()->SetTitle("a1 Mean");
  hist_a1_mean->SetTitle(" ");
  hist_a1_mean->Draw();
  canvas_a1.cd(2);
  hist_a1_mean_err->GetXaxis()->SetTitle("a1 Mean Error");
  hist_a1_mean_err->SetTitle(" ");
  hist_a1_mean_err->Draw();
  canvas_a1.cd(3);
  hist_a1_mean_pull->GetXaxis()->SetTitle("a1 Mean Pull");
  hist_a1_mean_pull->SetTitle(" ");
  hist_a1_mean_pull->Draw();
  canvas_a1.SaveAs("a1_mean.pdf");

  TCanvas canvas_a2("canvas_a2", "", 1500, 500);
  canvas_a2.Divide(3, 1);
  canvas_a2.cd(1);
  hist_a2_mean->GetXaxis()->SetTitle("a2 Mean");
  hist_a2_mean->SetTitle(" ");
  hist_a2_mean->Draw();
  canvas_a2.cd(2);
  hist_a2_mean_err->GetXaxis()->SetTitle("a2 Mean Error");
  hist_a2_mean_err->SetTitle(" ");
  hist_a2_mean_err->Draw();
  canvas_a2.cd(3);
  hist_a2_mean_pull->GetXaxis()->SetTitle("a2 Mean Pull");
  hist_a2_mean_pull->SetTitle(" ");
  hist_a2_mean_pull->Draw();
  canvas_a2.SaveAs("a2_mean.pdf");
}

int main() {
  GenerateToys();
  return 0;
}
