#pragma once

#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooCBShape.h"
#include "RooRealVar.h"
#include "RooSimultaneous.h"

#include "Configuration.h"

#include <memory>

class Pdf {
public:
  Pdf(Bachelor bachelor, Daughters daughters, RooRealVar &fitVariable);
      // RooArgList const &commonFunctions);

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
 
  // So that we can access the pdf components in order to plot them separately
  inline RooCBShape const &signal() const { return signal_; }
  inline RooExponential const &combinatorialExponential() const { return combinatorialExponential_; }
  inline RooCBShape const &bu2Dst0Hst_D0pi0() const { return bu2Dst0Hst_D0pi0_; }
  inline RooCBShape const &bu2Dst0Hst_D0gamma() const { return bu2Dst0Hst_D0gamma_; }
  inline RooCBShape const &crossFeed() const { return crossFeed_; }
  inline RooCBShape const &bu2D0H() const { return bu2D0H_; }
  inline RooCBShape const &bu2D0Hst() const { return bu2D0Hst_; }
  inline RooCBShape const &bd2DstH() const { return bd2DstH_; }
  inline RooCBShape const &bd2D0Hst0() const { return bd2D0Hst0_; }

  void AddToSimultaneousPdf(RooSimultaneous &simPdf) const;

private:
  Daughters daughters_;
  Bachelor bachelor_;
  RooRealVar signalMean_;
  RooRealVar signalSigma_;
  RooRealVar aSignal_;
  RooRealVar nSignal_;
  RooRealVar lambdaCombinatorial_;
  RooRealVar meanCrossFeed_;
  RooRealVar sigmaCrossFeed_;
  RooRealVar aCrossFeed_;
  RooRealVar nCrossFeed_;
  RooRealVar meanBu2Dst0Hst_D0pi0_;
  RooRealVar sigmaBu2Dst0Hst_D0pi0_;
  RooRealVar aBu2Dst0Hst_D0pi0_;
  RooRealVar nBu2Dst0Hst_D0pi0_;
  RooRealVar meanBu2Dst0Hst_D0gamma_;
  RooRealVar sigmaBu2Dst0Hst_D0gamma_;
  RooRealVar aBu2Dst0Hst_D0gamma_;
  RooRealVar nBu2Dst0Hst_D0gamma_;
  RooRealVar meanBu2D0H_;
  RooRealVar sigmaBu2D0H_;
  RooRealVar aBu2D0H_;
  RooRealVar nBu2D0H_;
  RooRealVar meanBu2D0Hst_;
  RooRealVar sigmaBu2D0Hst_;
  RooRealVar aBu2D0Hst_;
  RooRealVar nBu2D0Hst_;
  RooRealVar meanBd2DstH_;
  RooRealVar sigmaBd2DstH_;
  RooRealVar aBd2DstH_;
  RooRealVar nBd2DstH_;
  RooRealVar meanBd2D0Hst0_;
  RooRealVar sigmaBd2D0Hst0_;
  RooRealVar aBd2D0Hst0_;
  RooRealVar nBd2D0Hst0_;
  RooCBShape signal_;
  RooExponential combinatorialExponential_;
  RooCBShape crossFeed_;
  RooCBShape bu2Dst0Hst_D0pi0_;
  RooCBShape bu2Dst0Hst_D0gamma_;
  RooCBShape bu2D0H_;
  RooCBShape bu2D0Hst_;
  RooCBShape bd2DstH_;
  RooCBShape bd2D0Hst0_;
  RooArgList functions_;
  RooRealVar signalYield_;
  RooRealVar combinatorialYield_;
  RooRealVar bu2Dst0Hst_D0pi0Yield_;
  RooRealVar bu2Dst0Hst_D0gammaYield_;
  RooRealVar crossFeedYield_;
  RooRealVar bu2D0HYield_;
  RooRealVar bu2D0HstYield_;
  RooRealVar bd2D0Hst0Yield_;
  RooRealVar bd2DstHYield_;
  RooArgList yields_;
  double scaleFactor;
  double bachelorScaleFactor;
  double daughtersScaleFactor;
  std::unique_ptr<RooAddPdf> addPdf_;
};

