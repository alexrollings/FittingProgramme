#include "Pdf.h"
#include "Configuration.h"

Pdf::Pdf(Bachelor bachelor, Daughters daughters, RooRealVar &fitVariable,
         RooArgList const &commonFunctions)
    : bachelor_(bachelor), daughters_(daughters),
      buMassMean_(("m[Bu]_Mean_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                  "m[Bu] signal mean", 5279, 5275, 5285),
      buMassSigma_(("m[Bu]_Sigma_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                   "m[Bu] signal sigma", 18, 15, 23),
      lambdaCombinatorial_(
          ("lambda_Combinatorial_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
          "Combinatorial lambda", 0, -0.1, 0.1),
      signalGaussian_(("Signal_Gaussian_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                      "Signal gaussian pdf", fitVariable, buMassMean_,
                      buMassSigma_),
      combinatorialExponential_(
          ("Combinatorial_Exponential_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
          "Combinatorial exponential pdf", fitVariable, lambdaCombinatorial_),
      functions_(commonFunctions),
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

