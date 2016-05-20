#pragma once

#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooArgList.h"
#include "RooGaussian.h"
#include "RooExponential.h"

#include "Configuration.h"

#include <memory>

class Pdf {
public:
  Pdf(Bachelor bachelor, RooRealVar &fitVariable,
      RooArgList const &commonFunctions);

  // Implementing something in the header file that is not a template needs the
  // inline key word
  inline RooAddPdf &addPdf() { return *addPdf_; }

  inline RooAddPdf const &addPdf() const { return *addPdf_; }

private:
  std::string bachelorString_;
  RooRealVar buMassMean_;
  RooRealVar buMassSigma_;
  RooRealVar lambdaCombinatorial_;
  RooGaussian signalGaussian_;
  RooExponential combinatorialExponential_;
  RooArgList functions_;
  RooRealVar signalYield_;
  RooRealVar combinatorialYield_;
  RooRealVar bu2Dst0HstYield_;
  RooRealVar crossFeedYield_;
  RooRealVar bu2D0HYield_;
  RooRealVar bu2D0HstYield_;
  RooRealVar bd2DstHYield_;
  RooArgList yields_;
  double scaleFactor;
  std::unique_ptr<RooAddPdf> addPdf_;
};

