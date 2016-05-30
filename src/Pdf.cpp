#include "Pdf.h"
#include "Configuration.h"

Pdf::Pdf(Bachelor bachelor, Daughters daughters, RooRealVar &fitVariable)
         // RooArgList const &commonFunctions)
    : bachelor_(bachelor), daughters_(daughters),
      signalMean_(("m[Bu]_Mean_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                  "m[Bu] signal mean", 5279, 5275, 5285),
      signalSigma_(("m[Bu]_Sigma_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                   "m[Bu] signal sigma", 18, 15, 23),
      aSignal_(("aSignal" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                  "a Signal", 1, -2, 5),
      nSignal_(("nSignal" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                   "n Signal", 1, 0, 5),
      lambdaCombinatorial_(
          ("lambda_Combinatorial_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
          "Combinatorial lambda", 0, -0.1, 0.1),
      meanCrossFeed_("meanCrossFeed", "Neutral cross feed mean", 5292),
      sigmaCrossFeed_("sigmaCrossFeed", "Neutral cross feed sigma", 83),
      aCrossFeed_("aCrossFeed", "aCrossFeed", 2.7),
      nCrossFeed_("nCrossFeed", "nCrossFeed", 0.0),
      meanBu2Dst0Hst_D0pi0_("meanBu2Dst0Hst_D0pi0", "Bu2Dst0Hst_D0pi0 mean", 5073),
      sigmaBu2Dst0Hst_D0pi0_("sigmaBu2Dst0Hst_D0pi0", "Bu2Dst0Hst_D0pi0 sigma", 55),
      aBu2Dst0Hst_D0pi0_("aBu2Dst0Hst_D0pi0", "aBu2Dst0Hst_D0pi0", 1.2),
      nBu2Dst0Hst_D0pi0_("nBu2Dst0Hst_D0pi0", "nBu2Dst0Hst_D0pi0", 0.1),
      meanBu2Dst0Hst_D0gamma_("meanBu2Dst0Hst_D0gamma", "Bu2Dst0Hst_D0gamma mean", 5066),
      sigmaBu2Dst0Hst_D0gamma_("sigmaBu2Dst0Hst_D0gamma", "Bu2Dst0Hst_D0gamma sigma", 101),
      aBu2Dst0Hst_D0gamma_("aBu2Dst0Hst_D0gamma", "aBu2Dst0Hst_D0gamma", 0.22),
      nBu2Dst0Hst_D0gamma_("nBu2Dst0Hst_D0gamma", "nBu2Dst0Hst_D0gamma", 1.0),
      meanBu2D0H_("meanBu2D0H", "Bu2D0H mean", 5507),
      sigmaBu2D0H_("sigmaBu2D0H", "Bu2D0H sigma", 39),
      aBu2D0H_("aBu2D0H", "aBu2D0H", 2.6),
      nBu2D0H_("nBu2D0H", "nBu2D0H", 0.65),
      meanBu2D0Hst_("meanBu2D0Hst", "Bu2D0Hst mean", 5298),
      sigmaBu2D0Hst_("sigmaBu2D0Hst", "Bu2D0Hst sigma", 53),
      aBu2D0Hst_("aBu2D0Hst", "aBu2D0Hst", 0.52),
      nBu2D0Hst_("nBu2D0Hst", "nBu2D0Hst", 0.25),
      meanBd2DstH_("meanBd2DstH", "Bd2DstH mean", 5281),
      sigmaBd2DstH_("sigmaBd2DstH", "Bd2DstH sigma", 55),
      aBd2DstH_("aBd2DstH", "aBd2DstH", 4.2),
      nBd2DstH_("nBd2DstH", "nBd2DstH", 8.1),
      meanBd2D0Hst0_("meanBd2D0Hst0", "Bd2D0Hst0 mean", 5345),
      sigmaBd2D0Hst0_("sigmaBd2D0Hst0", "Bd2D0Hst0 sigma", 24),
      aBd2D0Hst0_("aBd2D0Hst0", "aBd2D0Hst0", 0.02),
      nBd2D0Hst0_("nBd2D0Hst0", "nBd2D0Hst0", 9.7),
      signal_(("Signal" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                      "Signal gaussian pdf", fitVariable, signalMean_,
                      signalSigma_, aSignal_, nSignal_),
      combinatorialExponential_(
          ("Combinatorial_Exponential_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
          "Combinatorial exponential pdf", fitVariable, lambdaCombinatorial_),
      bu2Dst0Hst_D0pi0_("bu2Dst0Hst_D0pi0", "Bu2Dst0Hst_D0pi0 gaussian", fitVariable, meanBu2Dst0Hst_D0pi0_, sigmaBu2Dst0Hst_D0pi0_, aBu2Dst0Hst_D0pi0_, nBu2Dst0Hst_D0pi0_),
      bu2Dst0Hst_D0gamma_("bu2Dst0Hst_D0gamma", "Bu2Dst0Hst_D0gamma gaussian", fitVariable, meanBu2Dst0Hst_D0gamma_, sigmaBu2Dst0Hst_D0gamma_, aBu2Dst0Hst_D0gamma_, nBu2Dst0Hst_D0gamma_),
      crossFeed_("crossFeed", "Neutral cross feed gaussian", fitVariable, meanCrossFeed_, sigmaCrossFeed_, aCrossFeed_, nCrossFeed_),
      bu2D0H_("bu2D0H", "Bu2D0H gaussian", fitVariable, meanBu2D0H_, sigmaBu2D0H_, aBu2D0H_, nBu2D0H_),
      bu2D0Hst_("bu2D0Hst", "Bu2D0Hst gaussian", fitVariable, meanBu2D0Hst_, sigmaBu2D0Hst_, aBu2D0Hst_, nBu2D0Hst_),
      bd2DstH_("bd2DstH", "Bd2DstH gaussian", fitVariable, meanBd2DstH_, sigmaBd2DstH_, aBd2DstH_, nBd2DstH_),
      bd2D0Hst0_("bd2D0Hst0", "Bd2DstH gaussian", fitVariable, meanBd2DstH_, sigmaBd2DstH_, aBd2DstH_, nBd2DstH_),
      signalYield_(("signal_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                   "m[Bu] signal yield", 0, 0, 0, ""),
      combinatorialYield_(
          ("combinatorial_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
          "m[Bu] combinatorial yield", 0, 0, 0, ""),
      bu2Dst0Hst_D0pi0Yield_(("bu2Dst0Hst_D0pi0_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                       "m[Bu] bu2Dst0Hst_D0pi0 yield", 0, 0, 0, ""),
      bu2Dst0Hst_D0gammaYield_(("bu2Dst0Hst_D0gamma_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                       "m[Bu] bu2Dst0Hst_D0gamma yield", 0, 0, 0, ""),
      crossFeedYield_(("crossFeed_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                      "m[Bu] crossFeed yield", 0, 0, 0, ""),
      bu2D0HYield_(("bu2D0H_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                   "m[Bu] bu2D0H yield", 0, 0, 0, ""),
      bu2D0HstYield_(("bu2D0Hst_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                     "m[Bu] bu2D0Hst yield", 0, 0, 0, ""),
      bd2DstHYield_(("bd2DstH_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                    "m[Bu] bd2DstH yield", 0, 0, 0, ""),
      bd2D0Hst0Yield_(("bd2D0Hst0_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                    "m[Bu] bd2D0Hst0 yield", 0, 0, 0, ""),
      yields_(), addPdf_(nullptr) {

  if (bachelor == Bachelor::pi) {
    bachelorScaleFactor = 1;
  } else {
    // Scale factor given by ratio of BR's
    bachelorScaleFactor = 0.000420 / 0.00518;
  }

  if (daughters == Daughters::kpi) {
    daughtersScaleFactor = 1;
  } else if (daughters == Daughters::kk) {
    daughtersScaleFactor = 0.00396 / 0.0388;
  } else if(daughters == Daughters::pipi) {
    daughtersScaleFactor = 0.001402 / 0.0388;
    } else {
    daughtersScaleFactor = 0.0001380 / 0.0388;
    }


  scaleFactor = bachelorScaleFactor*daughtersScaleFactor;
  
  signalYield_.setMax(20000 * scaleFactor);
  signalYield_.setVal(8000 * scaleFactor);
  combinatorialYield_.setMax(20000 * scaleFactor);
  combinatorialYield_.setVal(1 * scaleFactor);
  crossFeedYield_.setMax(20000 * scaleFactor);
  crossFeedYield_.setVal(1000 * scaleFactor);
  bu2Dst0Hst_D0pi0Yield_.setMax(20000 * scaleFactor);
  bu2Dst0Hst_D0pi0Yield_.setVal(4000 * scaleFactor);
  bu2Dst0Hst_D0gammaYield_.setMax(20000 * scaleFactor);
  bu2Dst0Hst_D0gammaYield_.setVal(200 * scaleFactor);
  bu2D0HYield_.setMax(20000 * scaleFactor);
  bu2D0HYield_.setVal(1100 * scaleFactor);
  bu2D0HstYield_.setMax(20000 * scaleFactor);
  bu2D0HstYield_.setVal(1300 * scaleFactor);
  bd2DstHYield_.setMax(20000 * scaleFactor);
  bd2DstHYield_.setVal(600 * scaleFactor);
  bd2D0Hst0Yield_.setMax(20000 * scaleFactor);
  bd2D0Hst0Yield_.setVal(100 * scaleFactor);

  functions_.add(signal_);
  functions_.add(combinatorialExponential_);
  functions_.add(bu2Dst0Hst_D0pi0_);
  functions_.add(bu2Dst0Hst_D0gamma_);
  functions_.add(crossFeed_);
  functions_.add(bu2D0H_);
  functions_.add(bu2D0Hst_);
  functions_.add(bd2DstH_);
  functions_.add(bd2D0Hst0_);
  yields_.add(signalYield_);
  yields_.add(combinatorialYield_);
  yields_.add(bu2Dst0Hst_D0pi0Yield_);
  yields_.add(bu2Dst0Hst_D0gammaYield_);
  yields_.add(crossFeedYield_);
  yields_.add(bu2D0HYield_);
  yields_.add(bu2D0HstYield_);
  yields_.add(bd2DstHYield_);
  yields_.add(bd2D0Hst0Yield_);
  addPdf_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("pdf_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
      ("pdf_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
      functions_, yields_));
}


void Pdf::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(*addPdf_,
                ComposeFittingCategoryName(bachelor_, daughters_).c_str());
}

