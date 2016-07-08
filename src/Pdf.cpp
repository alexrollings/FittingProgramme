#include "Pdf.h"
#include "Configuration.h"

Pdf::Pdf(Bachelor bachelor, Daughters daughters, RooRealVar &fitVariable)
         // RooArgList const &commonFunctions)
    : bachelor_(bachelor), daughters_(daughters),
      relativeWidth_("relativeWidth", "Relative width of k w.r.t. pi Pdfs", 0), 
      signalMean_("signalMean", "m[Bu] signal mean", 5279, 5275, 5285),
      signalSigma_("signalSigma", "m[Bu] signal sigma", 18, 15, 23),
      //Use a RooFormulaVar to relate widths of pi and k Pdfs
      signalSigmaFormula_("signalSigmaFormula", "m[Bu} K signal sigma", "(@0*@1)", RooArgList(signalSigma_,relativeWidth_)),
      aSignal_("aSignal", "a Signal", 1, -2, 5),
      nSignal_("nSignal", "n Signal", 1, 0, 5),
      lambdaCombinatorial_(
          ("lambda_Combinatorial_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
          "Combinatorial lambda", 0, -0.1, 0.1),
      meanNonTMSignal_("meanNonTMSignal", "Non TM signal mean", 5284.8),
      sigmaLeftNonTMSignal_(("sigmaLeftNonTMSignal_" + EnumToString(bachelor_)).c_str(), "Non TM signal sigmaLeft", 52.6),
      sigmaRightNonTMSignal_(("sigmaRightNonTMSignal_" + EnumToString(bachelor_)).c_str(), "Non TM signal sigmaRight", 49.4),
      meanCrossFeed_("meanCrossFeed", "Neutral cross feed mean", 5283),
      sigmaCrossFeed_(("sigmaCrossFeed_" + EnumToString(bachelor_)).c_str(), "Neutral cross feed sigma", 80),
      aCrossFeed_("aCrossFeed", "aCrossFeed", 3.5),
      nCrossFeed_("nCrossFeed", "nCrossFeed", 2.8),
      meanBu2Dst0Hst_D0pi0_("meanBu2Dst0Hst_D0pi0", "Bu2Dst0Hst_D0pi0 mean", 5080),
      sigmaBu2Dst0Hst_D0pi0_(("sigmaBu2Dst0Hst_D0pi0_" + EnumToString(bachelor_)).c_str(), "Bu2Dst0Hst_D0pi0 sigma", 57.8),
      aBu2Dst0Hst_D0pi0_("aBu2Dst0Hst_D0pi0", "aBu2Dst0Hst_D0pi0", 1.23),
      nBu2Dst0Hst_D0pi0_("nBu2Dst0Hst_D0pi0", "nBu2Dst0Hst_D0pi0", 0.1),
      meanBu2Dst0Hst_D0gamma_("meanBu2Dst0Hst_D0gamma", "Bu2Dst0Hst_D0gamma mean", 5068),
      sigmaBu2Dst0Hst_D0gamma_(("sigmaBu2Dst0Hst_D0gamma_" + EnumToString(bachelor_)).c_str(), "Bu2Dst0Hst_D0gamma sigma", 91.5),
      aBu2Dst0Hst_D0gamma_("aBu2Dst0Hst_D0gamma", "aBu2Dst0Hst_D0gamma", 1.0),
      nBu2Dst0Hst_D0gamma_("nBu2Dst0Hst_D0gamma", "nBu2Dst0Hst_D0gamma", 0.1),
      meanBu2D0H_("meanBu2D0H", "Bu2D0H mean", 5492),
      sigmaLeftBu2D0H_(("sigmaLeftBu2D0H_" + EnumToString(bachelor_)).c_str(), "Bu2D0H sigmaLeft", 35.7),
      sigmaRightBu2D0H_(("sigmaRightBu2D0H_" + EnumToString(bachelor_)).c_str(), "Bu2D0H sigmaRight", 46.7),
      meanBu2D0Hst_("meanBu2D0Hst", "Bu2D0Hst mean", 5304),
      sigmaBu2D0Hst_(("sigmaBu2D0Hst_" + EnumToString(bachelor_)).c_str(), "Bu2D0Hst sigma", 51.9),
      aBu2D0Hst_("aBu2D0Hst", "aBu2D0Hst", 0.33),
      nBu2D0Hst_("nBu2D0Hst", "nBu2D0Hst", 5.0),
      meanBd2DstH_("meanBd2DstH", "Bd2DstH mean", 5277.6),
      sigmaBd2DstH_(("sigmaBd2DstH_" + EnumToString(bachelor_)).c_str(), "Bd2DstH sigma", 54.3),
      aBd2DstH_("aBd2DstH", "aBd2DstH", 4.0),
      nBd2DstH_("nBd2DstH", "nBd2DstH", 6.1),
      meanBd2D0Hst0_("meanBd2D0Hst0", "Bd2D0Hst0 mean", 5225),
      sigmaBd2D0Hst0_(("sigmaBd2D0Hst0_" + EnumToString(bachelor_)).c_str(), "Bd2D0Hst0 sigma", 107),
      aBd2D0Hst0_("aBd2D0Hst0", "aBd2D0Hst0", 1.21),
      nBd2D0Hst0_("nBd2D0Hst0", "nBd2D0Hst0", 2.8),
      meanMissId1_(("meanMissId1_" + EnumToString(bachelor_)).c_str(), "MissId1 mean", 0),
      sigmaMissId1_(("sigmaMissId1_" + EnumToString(bachelor_)).c_str(), "MissId1 sigma", 0),
      aMissId1_(("aMissId1_" + EnumToString(bachelor_)).c_str(), "aMissId1", 0),
      nMissId1_(("nMissId1_" + EnumToString(bachelor_)).c_str(), "nMissId1", 0),
      meanMissId2_(("meanMissId2_" + EnumToString(bachelor_)).c_str(), "MissId2 mean", 0),
      sigmaMissId2_(("sigmaMissId2_" + EnumToString(bachelor_)).c_str(), "MissId2 sigma", 0),
      aMissId2_(("aMissId2_" + EnumToString(bachelor_)).c_str(), "aMissId2", 0),
      nMissId2_(("nMissId2_" + EnumToString(bachelor_)).c_str(), "nMissId2", 0),
      fracMissId1_(("fracMissId1_" + EnumToString(bachelor_)).c_str(), "fracMissId1", 0),
      // Use RooFormulaVar as input to signal pdf. Set constant relating widths below.
      signal_(("Signal_" + EnumToString(bachelor_)).c_str(), "Signal gaussian pdf", fitVariable, signalMean_, signalSigmaFormula_, aSignal_, nSignal_),
      nonTMSignal_(("nonTMSignal_"+ EnumToString(bachelor_)).c_str(), "Non TM signal gaussian", fitVariable, meanNonTMSignal_, sigmaLeftNonTMSignal_, sigmaRightNonTMSignal_),
      combinatorialExponential_(
          ("Combinatorial_Exponential_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
          "Combinatorial exponential pdf", fitVariable, lambdaCombinatorial_),
      bu2Dst0Hst_D0pi0_(("bu2Dst0Hst_D0pi0_"+ EnumToString(bachelor_)).c_str(), "Bu2Dst0Hst_D0pi0 gaussian", fitVariable, meanBu2Dst0Hst_D0pi0_, sigmaBu2Dst0Hst_D0pi0_, aBu2Dst0Hst_D0pi0_, nBu2Dst0Hst_D0pi0_),
      bu2Dst0Hst_D0gamma_(("bu2Dst0Hst_D0gamma_"+ EnumToString(bachelor_)).c_str(), "Bu2Dst0Hst_D0gamma gaussian", fitVariable, meanBu2Dst0Hst_D0gamma_, sigmaBu2Dst0Hst_D0gamma_, aBu2Dst0Hst_D0gamma_, nBu2Dst0Hst_D0gamma_),
      crossFeed_(("crossFeed_"+ EnumToString(bachelor_)).c_str(), "Neutral cross feed gaussian", fitVariable, meanCrossFeed_, sigmaCrossFeed_, aCrossFeed_, nCrossFeed_),
      bu2D0H_(("bu2D0H_"+ EnumToString(bachelor_)).c_str(), "Bu2D0H gaussian", fitVariable, meanBu2D0H_, sigmaLeftBu2D0H_, sigmaRightBu2D0H_),
      bu2D0Hst_(("bu2D0Hst_"+ EnumToString(bachelor_)).c_str(), "Bu2D0Hst gaussian", fitVariable, meanBu2D0Hst_, sigmaBu2D0Hst_, aBu2D0Hst_, nBu2D0Hst_),
      bd2DstH_(("bd2DstH_"+ EnumToString(bachelor_)).c_str(), "Bd2DstH gaussian", fitVariable, meanBd2DstH_, sigmaBd2DstH_, aBd2DstH_, nBd2DstH_),
      bd2D0Hst0_(("bd2D0Hst0_"+ EnumToString(bachelor_)).c_str(), "Bd2DstH gaussian", fitVariable, meanBd2DstH_, sigmaBd2DstH_, aBd2DstH_, nBd2DstH_),
      missId1_(("missId1_"+ EnumToString(bachelor_)).c_str(), "Miss ID 1 gaussian", fitVariable, meanMissId1_, sigmaMissId1_, aMissId1_, nMissId1_),
      missId2_(("missId2_"+ EnumToString(bachelor_)).c_str(), "Miss ID 2 gaussian", fitVariable, meanMissId2_, sigmaMissId2_, aMissId2_, nMissId2_),
      //Add miss-ID backgrounds individual PDFs to a RooAddPdf - we can defne the fraction of the first compared to the second. Add the total PDF to the simPdf.
      missId_(("missId_"+ EnumToString(bachelor_)).c_str(), "Miss ID PDF", RooArgList(missId1_, missId2_), fracMissId1_),
      signalYield_(("signal_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                   "m[Bu] signal yield", 0, 0, 0, ""),
      nonTMSignalYield_(("nonTMSignal_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                      "m[Bu] nonTMSignal yield", 0, 0, 0, ""),
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
      missIdYield_(("missId_yield_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
                    "m[Bu] missId yield", 100, 0, 20000),
      yields_(), addPdf_(nullptr) {

  kRelativeWidth_ = 0.95;

  if (bachelor == Bachelor::pi) {
    bachelorScaleFactor = 1;
    //Miss-ID backgrounds have different shapes for pi and k modes
    meanMissId1_.setVal(5218.6);
    sigmaMissId1_.setVal(57.0);
    aMissId1_.setVal(-3.25);
    nMissId1_.setVal(4.77);
    meanMissId2_.setVal(5218.6);
    sigmaMissId2_.setVal(20.8);
    aMissId2_.setVal(0.50);
    nMissId2_.setVal(1.68);
    fracMissId1_.setVal(0.390);
    relativeWidth_.setVal(1.0);
  } else {
    // Scale factor given by ratio of BR's
    bachelorScaleFactor = 0.000420 / 0.00518;
    meanMissId1_.setVal(5348.1);
    sigmaMissId1_.setVal(22.9);
    aMissId1_.setVal(-0.03);
    nMissId1_.setVal(25.3);
    meanMissId2_.setVal(5334.8);
    sigmaMissId2_.setVal(54.8);
    aMissId2_.setVal(3.80);
    nMissId2_.setVal(13.7);
    fracMissId1_.setVal(0.712);
    relativeWidth_.setVal(kRelativeWidth_);
    sigmaLeftNonTMSignal_.setVal(kRelativeWidth_*52.6);
    sigmaRightNonTMSignal_.setVal(kRelativeWidth_*49.4);
    sigmaCrossFeed_.setVal(kRelativeWidth_*80);
    sigmaBu2Dst0Hst_D0pi0_.setVal(kRelativeWidth_*57.8);
    sigmaBu2Dst0Hst_D0gamma_.setVal(kRelativeWidth_*91.5);
    sigmaLeftBu2D0H_.setVal(kRelativeWidth_*35.7);
    sigmaRightBu2D0H_.setVal(kRelativeWidth_*46.7);
    sigmaBu2D0Hst_.setVal(kRelativeWidth_*51.9);
    sigmaBd2DstH_.setVal(kRelativeWidth_*54.3);
    sigmaBd2D0Hst0_.setVal(kRelativeWidth_*107);
  }

  if (daughters == Daughters::kpi) {
    daughtersScaleFactor = 1;
  } else if (daughters == Daughters::kk) {
    daughtersScaleFactor = 0.00396 / 0.0388;
  } else if (daughters == Daughters::pipi) {
    daughtersScaleFactor = 0.001402 / 0.0388;
  } else {
    daughtersScaleFactor = 0.0001380 / 0.0388;
  }

  scaleFactor = bachelorScaleFactor * daughtersScaleFactor;

  signalYield_.setMax(20000 * scaleFactor);
  signalYield_.setVal(8000 * scaleFactor);
  nonTMSignalYield_.setMax(20000 * scaleFactor);
  nonTMSignalYield_.setVal(8000 * scaleFactor);
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
  functions_.add(nonTMSignal_);
  functions_.add(combinatorialExponential_);
  functions_.add(bu2Dst0Hst_D0pi0_);
  functions_.add(bu2Dst0Hst_D0gamma_);
  functions_.add(crossFeed_);
  functions_.add(bu2D0H_);
  functions_.add(bu2D0Hst_);
  functions_.add(bd2DstH_);
  functions_.add(bd2D0Hst0_);
  functions_.add(missId_);
  yields_.add(signalYield_);
  yields_.add(nonTMSignalYield_);
  yields_.add(combinatorialYield_);
  yields_.add(bu2Dst0Hst_D0pi0Yield_);
  yields_.add(bu2Dst0Hst_D0gammaYield_);
  yields_.add(crossFeedYield_);
  yields_.add(bu2D0HYield_);
  yields_.add(bu2D0HstYield_);
  yields_.add(bd2DstHYield_);
  yields_.add(bd2D0Hst0Yield_);
  yields_.add(missIdYield_);
  addPdf_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("pdf_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
      ("pdf_" + ComposeFittingCategoryName(bachelor_, daughters_)).c_str(),
      functions_, yields_));
}


void Pdf::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(*addPdf_,
                ComposeFittingCategoryName(bachelor_, daughters_).c_str());
}

