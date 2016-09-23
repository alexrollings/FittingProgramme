#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooArgSet.h"
#include "RooConstVar.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooGlobalFunc.h"
#include "RooMCStudy.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TH2.h"
#include "TStyle.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"


// using namespace RooFit;

void GenerateToys() {
  RooRealVar x("x", "x", 0, 10);
  x.setBins(40);

  RooRealVar mean("mean", "mean", 5, 0, 10);
  RooRealVar sigma1("sigma1", "sigma1", 0.5);
  RooRealVar sigma2("sigma2", "sigma2", 1);

  RooGaussian sig1("sig1", "Signal component 1", x, mean, sigma1);
  RooGaussian sig2("sig2", "Signal component 2", x, mean, sigma2);

  RooRealVar nsig1("sig1frac", "fraction of component 1 in signal", 800, 0,
                   1000);
  RooRealVar nsig2("sig2frac", "fraction of component 2 in signal", 200, 0,
                   1000);
  RooAddPdf sig("sig", "Signal", RooArgList(sig1, sig2),
                RooArgList(nsig1, nsig2));

  RooDataSet *data = sig.generate(RooArgSet(x),1000);
  
  RooRealVar meanB("meanB", "meanB", 5, 0, 10);
  RooRealVar sigmaB1("sigmaB1", "sigmaB1", 0.5);
  RooRealVar sigmaB2("sigmaB2", "sigmaB2", 1);

  RooGaussian sigB1("sigB1", "signal component 1", x, meanB, sigmaB1);
  RooGaussian sigB2("sigB2", "signal component 2", x, meanB, sigmaB2);

  RooRealVar nsigB1("sigB1frac", "fraction of component 1 in signal", 800, 0,
                   1000);
  RooRealVar nsigB2("sigB2frac", "fraction of component 2 in signal", 200, 0,
                   1000);
  RooAddPdf sigB("sigB", "signal", RooArgList(sigB1, sigB2),
                RooArgList(nsigB1, nsigB2));
  
  RooDataSet *dataB = sigB.generate(RooArgSet(x),1500);
 
  RooCategory Letter("Letter", "Letter");
  Letter.defineType("A");
  Letter.defineType("B");

  RooDataSet combData ("combData", "combData", x, RooFit::Index(Letter), RooFit::Import("A", *data), RooFit::Import("B", *dataB));
 
  RooSimultaneous simPdf("simPdf", "", Letter);
  simPdf.addPdf(sig, "A");
  simPdf.addPdf(sig, "B");
  
  // MUST specify yields in RooAbsPdf object in order to use RooMCStudy

  RooMCStudy *mcstudy = new RooMCStudy(
      simPdf, RooArgList(x, Letter), RooFit::Binned(kTRUE), RooFit::Silence(), RooFit::Extended(),
        RooFit::FitOptions(RooFit::Save(kTRUE), RooFit::PrintEvalErrors(0)));

  mcstudy->generate(1,1000,true);
  mcstudy->generateAndFit(1000);

  RooPlot *frameA1 = mcstudy->plotParam(mean, RooFit::Bins(40));
  RooPlot *frameA2 = mcstudy->plotError(mean, RooFit::Bins(40));
  RooPlot *frameA3 =
      mcstudy->plotPull(mean, RooFit::Bins(40), RooFit::FitGauss(kTRUE));

  // RooPlot* frame4 = mcstudy->plotNLL(Bins(40));
  //
  // TH1* hh_cor_a0_s1f =
  // mcstudy->fitParDataSet().createHistogram("hh",a1,YVar(sig1frac));
  // TH1* hh_cor_a0_a1  =
  // mcstudy->fitParDataSet().createHistogram("hh",a0,YVar(a1));
  //
  // TH2* corrHist000 = mcstudy->fitResult(0)->correlationHist("c000");
  // TH2* corrHist127 = mcstudy->fitResult(127)->correlationHist("c127");
  // TH2* corrHist953 = mcstudy->fitResult(953)->correlationHist("c953");

  // gStyle->SetPalette(1);
  // gStyle->SetOptStat(0);
  TCanvas *c = new TCanvas("rf801_mcstudy", "rf801_mcstudy", 900, 900);
  c->Divide(1, 3);

  c->cd(1);
  gPad->SetLeftMargin(0.15);
  frameA1->GetYaxis()->SetTitleOffset(1.4);
  frameA1->Draw();

  c->cd(2);
  gPad->SetLeftMargin(0.15);
  frameA2->GetYaxis()->SetTitleOffset(1.4);
  frameA2->Draw();

  c->cd(3);
  gPad->SetLeftMargin(0.15);
  frameA3->GetYaxis()->SetTitleOffset(1.4);
  frameA3->Draw();

  // c->cd(4);
  // gPad->SetLeftMargin(0.15);
  // frame4->GetYaxis()->SetTitleOffset(1.4);
  // frame4->Draw();

  // c->cd(5);
  // gPad->SetLeftMargin(0.15);
  // hh_cor_a0_s1f->GetYaxis()->SetTitleOffset(1.4);
  // hh_cor_a0_s1f->Draw("box");
  //
  // c->cd(6);
  // gPad->SetLeftMargin(0.15);
  // hh_cor_a0_a1->GetYaxis()->SetTitleOffset(1.4);
  // hh_cor_a0_a1->Draw("box");
  //
  // c->cd(7);
  // gPad->SetLeftMargin(0.15);
  // corrHist000->GetYaxis()->SetTitleOffset(1.4);
  // corrHist000->Draw("colz");
  //
  // c->cd(8);
  // gPad->SetLeftMargin(0.15);
  // corrHist127->GetYaxis()->SetTitleOffset(1.4);
  // corrHist127->Draw("colz");
  //
  // c->cd(9);
  // gPad->SetLeftMargin(0.15);
  // corrHist953->GetYaxis()->SetTitleOffset(1.4);
  // corrHist953->Draw("colz");

  c->Update();
  c->SaveAs("Toys.pdf");
}

int main(int argc, char **argv) { GenerateToys(); }
