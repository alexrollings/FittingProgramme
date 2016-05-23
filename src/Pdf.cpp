#include "Pdf.h"
#include "Configuration.h"

Pdf::Pdf(Bachelor bachelor, Daughters daughters, RooRealVar &fitVariable)
         // RooArgList const &commonFunctions)
    : bachelor_(bachelor), daughters_(daughters),
      buMassMean_(("m[Bu]_Mean_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                  "m[Bu] signal mean", 5279, 5275, 5285),
      buMassSigma_(("m[Bu]_Sigma_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                   "m[Bu] signal sigma", 18, 15, 23),
      lambdaCombinatorial_(
          ("lambda_Combinatorial_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
          "Combinatorial lambda", 0, -0.1, 0.1),
      meanBu2Dst0Hst_("meanBu2Dst0Hst", "Bu2Dst0Hst mean", 5057),
      sigmaBu2Dst0Hst_("sigmaBu2Dst0Hst", "Bu2Dst0Hst sigma", 65),
      meanBu2D0H_("meanBu2D0H", "Bu2D0H mean", 5508),
      sigmaBu2D0H_("sigmaBu2D0H", "Bu2D0H sigma", 43),
      meanBu2D0Hst_("meanBu2D0Hst", "Bu2D0Hst mean", 5277),
      sigmaBu2D0Hst_("sigmaBu2D0Hst", "Bu2D0Hst sigma", 66),
      meanCrossFeed_("meanCrossFeed", "Neutral cross feed mean", 5294),
      sigmaCrossFeed_("sigmaCrossFeed", "Neutral cross feed sigma", 90),
      meanBd2DstH_("meanBd2DstH", "Bd2DstH mean", 5277),
      sigmaBd2DstH_("sigmaBd2DstH", "Bd2DstH sigma", 66),
      signalGaussian_(("Signal_Gaussian_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                      "Signal gaussian pdf", fitVariable, buMassMean_,
                      buMassSigma_),
      combinatorialExponential_(
          ("Combinatorial_Exponential_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
          "Combinatorial exponential pdf", fitVariable, lambdaCombinatorial_),
      bu2Dst0HstGaussian_("bu2Dst0HstGaussian", "Bu2Dst0Hst gaussian", fitVariable, meanBu2Dst0Hst_, sigmaBu2Dst0Hst_),
      crossFeedGaussian_("crossFeedGaussian", "Neutral cross feed gaussian", fitVariable, meanCrossFeed_, sigmaCrossFeed_),
      bu2D0HGaussian_("bu2D0HGaussian", "Bu2D0H gaussian", fitVariable, meanBu2D0H_, sigmaBu2D0H_),
      bu2D0HstGaussian_("bu2D0HstGaussian", "Bu2D0Hst gaussian", fitVariable, meanBu2D0Hst_, sigmaBu2D0Hst_),
      bd2DstHGaussian_("bd2DstHGaussian", "Bd2DstH gaussian", fitVariable, meanBd2DstH_, sigmaBd2DstH_),
      signalYield_(("signal_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                   "m[Bu] signal yield", 0, 0, 0, ""),
      combinatorialYield_(
          ("combinatorial_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
          "m[Bu] combinatorial yield", 0, 0, 0, ""),
      bu2Dst0HstYield_(("bu2Dst0Hst_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                       "m[Bu] bu2Dst0Hst yield", 0, 0, 0, ""),
      crossFeedYield_(("crossFeed_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                      "m[Bu] crossFeed yield", 0, 0, 0, ""),
      bu2D0HYield_(("bu2D0H_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                   "m[Bu] bu2D0H yield", 0, 0, 0, ""),
      bu2D0HstYield_(("bu2D0Hst_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                     "m[Bu] bu2D0Hst yield", 0, 0, 0, ""),
      bd2DstHYield_(("bd2DstH_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                    "m[Bu] bd2DstH yield", 0, 0, 0, ""),
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
  signalYield_.setVal(10000 * scaleFactor);
  combinatorialYield_.setMax(20000 * scaleFactor);
  combinatorialYield_.setVal(1000 * scaleFactor);
  bu2Dst0HstYield_.setMax(20000 * scaleFactor);
  bu2Dst0HstYield_.setVal(5000 * scaleFactor);
  crossFeedYield_.setMax(20000 * scaleFactor);
  crossFeedYield_.setVal(1000 * scaleFactor);
  bu2D0HYield_.setMax(20000 * scaleFactor);
  bu2D0HYield_.setVal(3000 * scaleFactor);
  bu2D0HstYield_.setMax(20000 * scaleFactor);
  bu2D0HstYield_.setVal(2500 * scaleFactor);
  bd2DstHYield_.setMax(20000 * scaleFactor);
  bd2DstHYield_.setVal(1000 * scaleFactor);

  functions_.add(signalGaussian_);
  functions_.add(combinatorialExponential_);
  functions_.add(bu2Dst0HstGaussian_);
  functions_.add(crossFeedGaussian_);
  functions_.add(bu2D0HGaussian_);
  functions_.add(bu2D0HstGaussian_);
  functions_.add(bd2DstHGaussian_);
  yields_.add(signalYield_);
  yields_.add(combinatorialYield_);
  yields_.add(bu2Dst0HstYield_);
  yields_.add(crossFeedYield_);
  yields_.add(bu2D0HYield_);
  yields_.add(bu2D0HstYield_);
  yields_.add(bd2DstHYield_);
  addPdf_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("pdf_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
      ("pdf_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
      functions_, yields_));
}


void Pdf::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(*addPdf_,
                ComposeFittingCategoryName(bachelor_, daughters_).c_str());
}

