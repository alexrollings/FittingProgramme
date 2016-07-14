#pragma once

#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooCBShape.h"
#include "RooBifurGauss.h"
#include "RooRealVar.h"
#include "RooFormulaVar.h"
#include "RooSimultaneous.h"

#include "Configuration.h"

#include <memory>

class Pdf {
public:
  Pdf(Neutral neutral, Bachelor bachelor, Daughters daughters, RooRealVar &fitVariable);
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
  inline Neutral neutral() const { return neutral_; }
 
  // So that we can access the pdf components in order to plot them separately
  inline RooCBShape const &signalPi0() const { return signalPi0_; }
  inline RooBifurGauss const &nonTMSignalPi0() const { return nonTMSignalPi0_; }
  inline RooBifurGauss const &signalGamma() const { return signalGamma_; }
  inline RooAddPdf const &nonTMSignalGamma() const { return nonTMSignalGamma_; }
  inline RooExponential const &combinatorialExponential() const { return combinatorialExponential_; }
  inline RooCBShape const &bu2Dst0Hst_D0pi0() const { return bu2Dst0Hst_D0pi0_; }
  inline RooCBShape const &bu2Dst0Hst_D0gamma() const { return bu2Dst0Hst_D0gamma_; }
  inline RooCBShape const &crossFeed() const { return crossFeed_; }
  inline RooBifurGauss const &bu2D0H() const { return bu2D0H_; }
  inline RooCBShape const &bu2D0Hst() const { return bu2D0Hst_; }
  inline RooCBShape const &bd2DstH() const { return bd2DstH_; }
  inline RooCBShape const &bd2D0Hst0() const { return bd2D0Hst0_; }
  inline RooAddPdf const &missId() const { return missId_; }

  void AddToSimultaneousPdf(RooSimultaneous &simPdf) const;

private:
  Daughters daughters_;
  Bachelor bachelor_;
  Neutral neutral_;
  double relativeWidth_;
  RooRealVar signalPi0Mean_;
  RooRealVar signalPi0Sigma_;
  RooRealVar aSignalPi0_;
  RooRealVar nSignalPi0_;
  RooRealVar signalGammaMean_;  
  RooRealVar signalGammaSigmaLeft_;
  RooRealVar signalGammaSigmaRight_;
  RooRealVar relativeWidthVar_;
  RooFormulaVar signalGammaSigmaLeftFormula_;
  RooFormulaVar signalGammaSigmaRightFormula_;
  RooRealVar meanNonTMSignalGamma_;
  RooRealVar sigmaNonTMSignalGamma1_;
  RooRealVar aNonTMSignalGamma1_;
  RooRealVar nNonTMSignalGamma1_;
  RooRealVar fracNonTMSignalGamma1_;
  RooRealVar sigmaNonTMSignalGamma2_;
  RooRealVar aNonTMSignalGamma2_;
  RooRealVar nNonTMSignalGamma2_;
  RooRealVar meanNonTMSignalPi0_;
  RooRealVar sigmaLeftNonTMSignalPi0_;
  RooRealVar sigmaRightNonTMSignalPi0_;
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
  RooRealVar sigmaLeftBu2D0H_;
  RooRealVar sigmaRightBu2D0H_;
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
  RooRealVar meanMissId1_;
  RooRealVar sigmaMissId1_;
  RooRealVar aMissId1_;
  RooRealVar nMissId1_;
  RooRealVar meanMissId2_;
  RooRealVar sigmaMissId2_;
  RooRealVar aMissId2_;
  RooRealVar nMissId2_;
  // Miss-ID background is made up of 2 components: define fraction of first component w.r.t. entire PDF to enter into a RooAddPdf
  RooRealVar fracMissId1_;
  RooFormulaVar signalSigmaFormula_;
  RooCBShape signalPi0_;
  RooBifurGauss nonTMSignalPi0_;
  RooBifurGauss signalGamma_;
  RooCBShape nonTMSignalGamma1_;
  RooCBShape nonTMSignalGamma2_;
  RooAddPdf nonTMSignalGamma_;
  RooExponential combinatorialExponential_;
  RooCBShape crossFeed_;
  RooCBShape bu2Dst0Hst_D0pi0_;
  RooCBShape bu2Dst0Hst_D0gamma_;
  RooBifurGauss bu2D0H_;
  RooCBShape bu2D0Hst_;
  RooCBShape bd2DstH_;
  RooCBShape bd2D0Hst0_;
  RooCBShape missId1_;
  RooCBShape missId2_;
  RooAddPdf missId_;
  RooArgList functions_;
  double kSignalPi0BR_;
  double kSignalGammaBR_;
  double kCrossFeedBR_;
  double kBu2Dst0Hst_D0pi0BR_;
  double kBu2Dst0Hst_D0gammaBR_;
  double kBu2D0HBR_;
  double kBu2D0HstBR_;
  double kBd2DstHBR_;
  double kBd2D0Hst0BR_;
  RooRealVar signalBR_;
  RooRealVar crossFeedBR_;
  RooRealVar bu2Dst0Hst_D0pi0BR_;
  RooRealVar bu2Dst0Hst_D0gammaBR_;
  RooRealVar bu2D0HBR_;
  RooRealVar bu2D0HstBR_;
  RooRealVar bd2DstHBR_;
  RooRealVar bd2D0Hst0BR_;
  RooRealVar probLoosePi0_;
  RooRealVar probLooseGamma_;
  RooRealVar probLoosePi_;
  RooRealVar probAddPi0_;
  RooRealVar signalYield_;
  RooFormulaVar nonTMSignalYield_;
  RooRealVar combinatorialYield_;
  RooFormulaVar bu2Dst0Hst_D0pi0Yield_;
  RooFormulaVar bu2Dst0Hst_D0gammaYield_;
  RooFormulaVar crossFeedYield_;
  RooFormulaVar bu2D0HYield_;
  RooFormulaVar bu2D0HstYield_;
  RooFormulaVar bd2D0Hst0Yield_;
  RooFormulaVar bd2DstHYield_;
  RooRealVar missIdYield_;
  RooArgList yields_;
  std::unique_ptr<RooAddPdf> addPdf_;
};

