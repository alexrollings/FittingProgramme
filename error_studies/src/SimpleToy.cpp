#include "RooAbsBinning.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooBifurGauss.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooGaussian.h"
#include "RooProdPdf.h"
#include "RooRealVar.h"
#include "RooArgSet.h"
#include "RooFitResult.h"
#include "RooAddPdf.h"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {

  RooRealVar x("x", "", -10, 10);

  RooRealVar mean("mean", "", 0, -1, 1);
  RooRealVar sigma("sigma", "", 1, 0, 5);
  RooGaussian gaus("gaus", "", x, mean, sigma);
  RooRealVar n_gaus("n_gaus", "", 1000, 0, 5000);

  RooAddPdf pdf("pdf", "", RooArgSet(gaus), RooArgSet(n_gaus));

  // RooRealVar lambda("lambda", "", 0.005, -1, 1);
  // RooExponential exp("exp", "", x, lambda);
  // RooRealVar n_exp("n_exp", "", 200, 0, 1000);
  //
  // RooAddPdf pdf("pdf", "", RooArgSet(gaus, exp), RooArgSet(n_gaus, n_exp));
  
  RooDataSet* data = gaus.generate(x, 1000);

  RooFitResult *result =
      pdf.fitTo(*data, RooFit::Save(), RooFit::Strategy(2),
                RooFit::Minimizer("Minuit2"), RooFit::Offset(true));

  result->Print();

  return 0;
}
