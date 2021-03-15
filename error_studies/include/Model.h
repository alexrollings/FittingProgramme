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
#include "RooSimultaneous.h"

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

  RooRealVar N_tot;
  RooRealVar eff_Bu;
  RooRealVar eff_Delta;
  std::unique_ptr<RooAbsReal> N_Bu;
  RooFormulaVar N_Delta;

  RooArgList buFunctions;
  RooArgList buYields;
  RooArgList deltaFunctions;
  RooArgList deltaYields;

  std::unique_ptr<RooAddPdf> buAddPdf;
  std::unique_ptr<RooAddPdf> deltaAddPdf;
};
