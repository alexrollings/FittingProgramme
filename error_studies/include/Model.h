#pragma once
#include <iostream>
#include <string>
#include <sstream>

#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooCategory.h"
#include "RooRealVar.h"
#include "RooFormulaVar.h"
#include "RooAbsReal.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooExponential.h"
#include "RooGaussian.h"
#include "RooDstD0BG.h"
#include "RooSimultaneous.h"
#include "RooProdPdf.h"

#include <Configuration.h>
#include <CommonFunctions.h>

// Class to hold a bunch of variables that are passed around
class Model {
 public:
  Model(Configuration&, int);

  int uniqueId;

  RooRealVar buMean;
  RooRealVar buSigma;
  RooRealVar buA1;
  RooRealVar buN1;
  RooRealVar buA2;
  RooRealVar buN2;
  RooRealVar buFrac;
  RooCBShape buPdf1;
  RooCBShape buPdf2;
  RooAddPdf buPdf;

  RooRealVar deltaMean;
  RooRealVar deltaSigma;
  RooRealVar deltaA1;
  RooRealVar deltaN1;
  RooRealVar deltaA2;
  RooRealVar deltaN2;
  RooRealVar deltaFrac;
  RooCBShape deltaPdf1;
  RooCBShape deltaPdf2;
  RooAddPdf deltaPdf;

  double N_Sig;
  RooRealVar eff_Bu;
  RooRealVar eff_Delta;
  RooRealVar eff_Or;
  RooRealVar N_tot;
  std::unique_ptr<RooAbsReal> N_Bu;
  RooFormulaVar N_Delta;

  // RooRealVar buLambda;
  // RooExponential buBkgPdf;
  // RooRealVar deltaLambda;
  // RooExponential deltaBkgPdf;

  RooRealVar buBkgMean;
  RooRealVar buBkgSigma;
  RooGaussian buBkgPdf;
  RooRealVar deltaBkgThreshold;
  RooRealVar deltaBkgC;
  RooRealVar deltaBkgA;
  RooRealVar deltaBkgB;
  RooDstD0BG deltaBkgPdf;

  double N_Bkg;
  RooRealVar N_tot_Bkg;
  RooRealVar eff_Bu_Bkg;
  RooRealVar eff_Delta_Bkg;
  std::unique_ptr<RooAbsReal> N_Bu_Bkg;
  RooFormulaVar N_Delta_Bkg;

  RooArgList buFunctions;
  RooArgList buYields;
  RooArgList deltaFunctions;
  RooArgList deltaYields;

  std::unique_ptr<RooAddPdf> buAddPdf;
  std::unique_ptr<RooAddPdf> deltaAddPdf;

  std::unique_ptr<RooSimultaneous> simPdf;

  RooProdPdf sigPdf2D;
  RooRealVar N_Sig2D;

  RooProdPdf bkgPdf2D;
  RooRealVar N_Bkg2D;

  RooArgList functions2D;
  RooArgList yields2D;

  std::unique_ptr<RooAddPdf> pdf2D;
};
