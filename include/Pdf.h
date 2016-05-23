#pragma once

#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooGaussian.h"
#include "RooRealVar.h"
#include "RooSimultaneous.h"

#include "Configuration.h"

#include <memory>

class Pdf {
public:
  Pdf(Bachelor bachelor, Daughters daughters, RooRealVar &fitVariable,
      RooArgList const &commonFunctions);

  Pdf(Pdf const &) = delete;
  Pdf(Pdf &&) = delete;
  Pdf &operator=(Pdf const &) = delete;
  Pdf &operator=(Pdf &&) = delete;

  // Implementing something in the header file that is not a template needs the
  // inline key word
  // inline RooAddPdf &addPdf() { return *addPdf_; }
  //
  // inline RooAddPdf const &addPdf() const { return *addPdf_; }

  // By declaring the function const you say you are not going to change
  // anything in the class by calling the function
  inline Bachelor bachelor() const { return bachelor_; }

  inline Daughters daughters() const { return daughters_; }

  void AddToSimultaneousPdf(RooSimultaneous &simPdf) const;

private:
  Daughters daughters_;
  Bachelor bachelor_;
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
  double bachelorScaleFactor;
  double daughtersScaleFactor;
  std::unique_ptr<RooAddPdf> addPdf_;
};

