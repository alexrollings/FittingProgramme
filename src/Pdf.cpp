#include "Pdf.h"
#include "Configuration.h"

Pdf::Pdf(Neutral neutral, Bachelor bachelor, Daughters daughters,
         RooRealVar &fitVariable)
    // RooArgList const &commonFunctions)
    : bachelor_(bachelor),
      daughters_(daughters),
      neutral_(neutral),
      relativeWidth_(1.0),
      signalPi0Mean_("signalPi0Mean", "m[Bu] signal mean", 5279, 5275, 5285),
      signalPi0Sigma_("signalPi0Sigma", "m[Bu] signal sigma", 0), //, 15, 23),
      aSignalPi0_("aSignalPi0", "a Signal", 0),
      nSignalPi0_("nSignalPi0", "n Signal", 0),
      signalGammaMean_("signalGammaMean", "m[Bu] signal mean", 5281, 5277,
                       5285),
      signalGammaSigmaLeft_("signalGammaSigmaLeft", "m[Bu] signal sigma", 0),
      signalGammaSigmaRight_("signalGammaSigmaRight", "m[Bu] signal sigma", 0),
      lambdaCombinatorial_(("lambda_Combinatorial_" +
                            ComposeFittingCategoryName(neutral_, bachelor_,
                                                       daughters_))
                               .c_str(),
                           "Combinatorial lambda", 0, -1, 1),
      meanNonTMSignalPi0_("meanNonTMSignalPi0", "Non TM signal mean", 0),
      sigmaLeftNonTMSignalPi0_(
          ("sigmaLeftNonTMSignalPi0_" + EnumToString(bachelor_)).c_str(),
          "Non TM signal sigmaLeft", 0),
      sigmaRightNonTMSignalPi0_(
          ("sigmaRightNonTMSignalPi0_" + EnumToString(bachelor_)).c_str(),
          "Non TM signal sigmaRight", 0),
      meanNonTMSignalGamma_("meanNonTMSignalGamma", "Non TM signal mean", 0),
      sigmaNonTMSignalGamma1_("sigmaNonTMSignalGamma1_", "Non TM signal sigma1",
                              0),
      aNonTMSignalGamma1_("aNonTMSignalGamma1_", "Non TM signal a1", 0),
      nNonTMSignalGamma1_("nNonTMSignalGamma1_", "Non TM signal n1", 0),
      fracNonTMSignalGamma1_("fracNonTMSignalGamma1_", "fracNonTMSignal1_", 0),
      sigmaNonTMSignalGamma2_("sigmaNonTMSignalGamma2_", "Non TM signal sigma2",
                              0),
      aNonTMSignalGamma2_("aNonTMSignalGamma2_", "Non TM signal a2", 0),
      nNonTMSignalGamma2_("nNonTMSignalGamma2_", "Non TM signal n2", 0),
      meanCrossFeed_("meanCrossFeed", "Neutral cross feed mean", 0),
      sigmaCrossFeed_(("sigmaCrossFeed_" + EnumToString(bachelor_)).c_str(),
                      "Neutral cross feed sigma", 0),
      aCrossFeed_("aCrossFeed", "aCrossFeed", 0),
      nCrossFeed_("nCrossFeed", "nCrossFeed", 0),
      meanBu2Dst0Kst_D0pi0_Gamma_("meanBu2Dst0Kst_D0pi0_Gamma_", "", 0),
      sigmaBu2Dst0Kst_D0pi0_Gamma_("sigmaBu2Dst0Kst_D0pi0_Gamma_", "", 0),
      meanBu2Dst0Hst_D0pi0_("meanBu2Dst0Hst_D0pi0", "Bu2Dst0Hst_D0pi0 mean", 0),
      sigmaBu2Dst0Hst_D0pi0_(
          ("sigmaBu2Dst0Hst_D0pi0_" + EnumToString(bachelor_)).c_str(),
          "Bu2Dst0Hst_D0pi0 sigma", 0),
      aBu2Dst0Hst_D0pi0_("aBu2Dst0Hst_D0pi0", "aBu2Dst0Hst_D0pi0", 0),
      nBu2Dst0Hst_D0pi0_("nBu2Dst0Hst_D0pi0", "nBu2Dst0Hst_D0pi0", 0),
      meanBu2Dst0Hst_D0gamma_("meanBu2Dst0Hst_D0gamma",
                              "Bu2Dst0Hst_D0gamma mean", 0),
      sigmaBu2Dst0Hst_D0gamma_(
          ("sigmaBu2Dst0Hst_D0gamma_" + EnumToString(bachelor_)).c_str(),
          "Bu2Dst0Hst_D0gamma sigma", 0),
      aBu2Dst0Hst_D0gamma_("aBu2Dst0Hst_D0gamma", "aBu2Dst0Hst_D0gamma", 0),
      nBu2Dst0Hst_D0gamma_("nBu2Dst0Hst_D0gamma", "nBu2Dst0Hst_D0gamma", 0),
      meanBu2D0H_("meanBu2D0H", "Bu2D0H mean", 0),
      sigmaLeftBu2D0H_(("sigmaLeftBu2D0H_" + EnumToString(bachelor_)).c_str(),
                       "Bu2D0H sigmaLeft", 0),
      sigmaRightBu2D0H_(("sigmaRightBu2D0H_" + EnumToString(bachelor_)).c_str(),
                        "Bu2D0H sigmaRight", 0),
      meanBu2D0Hst_("meanBu2D0Hst", "Bu2D0Hst mean", 0),
      sigmaBu2D0Hst_(("sigmaBu2D0Hst_" + EnumToString(bachelor_)).c_str(),
                     "Bu2D0Hst sigma", 0),
      aBu2D0Hst_("aBu2D0Hst", "aBu2D0Hst", 0),
      nBu2D0Hst_("nBu2D0Hst", "nBu2D0Hst", 0),
      meanBd2DstH_("meanBd2DstH", "Bd2DstH mean", 0),
      sigmaBd2DstH_(("sigmaBd2DstH_" + EnumToString(bachelor_)).c_str(),
                    "Bd2DstH sigma", 0),
      aBd2DstH_("aBd2DstH", "aBd2DstH", 0),
      nBd2DstH_("nBd2DstH", "nBd2DstH", 0),
      meanBd2D0Hst0_("meanBd2D0Hst0", "Bd2D0Hst0 mean", 0),
      sigmaBd2D0Hst0_(("sigmaBd2D0Hst0_" + EnumToString(bachelor_)).c_str(),
                      "Bd2D0Hst0 sigma", 0),
      aBd2D0Hst0_("aBd2D0Hst0", "aBd2D0Hst0", 0),
      nBd2D0Hst0_("nBd2D0Hst0", "nBd2D0Hst0", 0),
      meanMissId1_(("meanMissId1_" + EnumToString(bachelor_)).c_str(),
                   "MissId1 mean", 0),
      sigmaMissId1_(("sigmaMissId1_" + EnumToString(bachelor_)).c_str(),
                    "MissId1 sigma", 0),
      aMissId1_(("aMissId1_" + EnumToString(bachelor_)).c_str(), "aMissId1", 0),
      nMissId1_(("nMissId1_" + EnumToString(bachelor_)).c_str(), "nMissId1", 0),
      meanMissId2_(("meanMissId2_" + EnumToString(bachelor_)).c_str(),
                   "MissId2 mean", 0),
      sigmaMissId2_(("sigmaMissId2_" + EnumToString(bachelor_)).c_str(),
                    "MissId2 sigma", 0),
      aMissId2_(("aMissId2_" + EnumToString(bachelor_)).c_str(), "aMissId2", 0),
      nMissId2_(("nMissId2_" + EnumToString(bachelor_)).c_str(), "nMissId2", 0),
      fracMissId1_(("fracMissId1_" + EnumToString(bachelor_)).c_str(),
                   "fracMissId1", 0),
      // Use RooFormulaVar as input to signal pdf. Set constant relating widths
      // below.
      signalPi0_(("signalPi0_" + EnumToString(bachelor_)).c_str(),
                 "Signal gaussian pdf", fitVariable, signalPi0Mean_,
                 signalPi0Sigma_, aSignalPi0_, nSignalPi0_),
      signalGamma_(("signalGamma_" + EnumToString(bachelor_)).c_str(),
                   "Signal gaussian pdf", fitVariable, signalGammaMean_,
                   signalGammaSigmaLeft_, signalGammaSigmaRight_),
      nonTMSignalPi0_(("nonTMSignalPi0_" + EnumToString(bachelor_)).c_str(),
                      "Non TM signal gaussian", fitVariable,
                      meanNonTMSignalPi0_, sigmaLeftNonTMSignalPi0_,
                      sigmaRightNonTMSignalPi0_),
      nonTMSignalGamma1_(
          ("nonTMSignalGamma1_" + EnumToString(bachelor_)).c_str(),
          "Non TM Signal 1 gaussian", fitVariable, meanNonTMSignalGamma_,
          sigmaNonTMSignalGamma2_, aNonTMSignalGamma1_, nNonTMSignalGamma1_),
      nonTMSignalGamma2_(
          ("nonTMSignalGamma2_" + EnumToString(bachelor_)).c_str(),
          "Non TM Signal 2 gaussian", fitVariable, meanNonTMSignalGamma_,
          sigmaNonTMSignalGamma2_, aNonTMSignalGamma2_, nNonTMSignalGamma2_),
      nonTMSignalGamma_(("nonTMSignalGamma_" + EnumToString(bachelor_)).c_str(),
                        "Non TM Signal PDF",
                        RooArgList(nonTMSignalGamma1_, nonTMSignalGamma2_),
                        fracNonTMSignalGamma1_),
      combinatorialExponential_(("Combinatorial_Exponential_" +
                                 ComposeFittingCategoryName(neutral_, bachelor_,
                                                            daughters_))
                                    .c_str(),
                                "Combinatorial exponential pdf", fitVariable,
                                lambdaCombinatorial_),
      missId1_(("missId1_" + EnumToString(neutral_) + EnumToString(bachelor_))
                   .c_str(),
               "Miss ID 1 gaussian", fitVariable, meanMissId1_, sigmaMissId1_,
               aMissId1_, nMissId1_),
      missId2_(("missId2_" + EnumToString(neutral_) + EnumToString(bachelor_))
                   .c_str(),
               "Miss ID 2 gaussian", fitVariable, meanMissId2_, sigmaMissId2_,
               aMissId2_, nMissId2_),
      // Add miss-ID backgrounds individual PDFs to a RooAddPdf - we can defne
      // the fraction of the first compared to the second. Add the total PDF to
      // the simPdf.
      missId_(("missId_" + EnumToString(neutral_) + EnumToString(bachelor_))
                  .c_str(),
              "Miss ID PDF", RooArgList(missId1_, missId2_), fracMissId1_),
      crossFeed_(("crossFeed_" + EnumToString(neutral_) +
                  EnumToString(bachelor_))
                     .c_str(),
                 "Neutral cross feed gaussian", fitVariable, meanCrossFeed_,
                 sigmaCrossFeed_, aCrossFeed_, nCrossFeed_),
      bu2Dst0Hst_D0pi0_(("bu2Dst0Hst_D0pi0_" + EnumToString(neutral_) +
                         EnumToString(bachelor_))
                            .c_str(),
                        "Bu2Dst0Hst_D0pi0 gaussian", fitVariable,
                        meanBu2Dst0Hst_D0pi0_, sigmaBu2Dst0Hst_D0pi0_,
                        aBu2Dst0Hst_D0pi0_, nBu2Dst0Hst_D0pi0_),
      bu2Dst0Kst_D0pi0_Gamma_("bu2Dst0Kst_D0pi0_Gamma_",
                              "Bu2Dst0Kst_D0pi0 gaussian for gamma neutral",
                              fitVariable, meanBu2Dst0Kst_D0pi0_Gamma_,
                              sigmaBu2Dst0Kst_D0pi0_Gamma_),
      bu2Dst0Hst_D0gamma_(("bu2Dst0Hst_D0gamma_" + EnumToString(neutral_) +
                           EnumToString(bachelor_))
                              .c_str(),
                          "Bu2Dst0Hst_D0gamma gaussian", fitVariable,
                          meanBu2Dst0Hst_D0gamma_, sigmaBu2Dst0Hst_D0gamma_,
                          aBu2Dst0Hst_D0gamma_, nBu2Dst0Hst_D0gamma_),
      bu2D0H_(("bu2D0H_" + EnumToString(neutral_) + EnumToString(bachelor_))
                  .c_str(),
              "Bu2D0H gaussian", fitVariable, meanBu2D0H_, sigmaLeftBu2D0H_,
              sigmaRightBu2D0H_),
      bu2D0Hst_(("bu2D0Hst_" + EnumToString(neutral_) + EnumToString(bachelor_))
                    .c_str(),
                "Bu2D0Hst gaussian", fitVariable, meanBu2D0Hst_, sigmaBu2D0Hst_,
                aBu2D0Hst_, nBu2D0Hst_),
      bd2DstH_(("bd2DstH_" + EnumToString(neutral_) + EnumToString(bachelor_))
                   .c_str(),
               "Bd2DstH gaussian", fitVariable, meanBd2DstH_, sigmaBd2DstH_,
               aBd2DstH_, nBd2DstH_),
      bd2D0Hst0_(("bd2D0Hst0_" + EnumToString(neutral_) +
                  EnumToString(bachelor_))
                     .c_str(),
                 "Bd2DstH gaussian", fitVariable, meanBd2DstH_, sigmaBd2DstH_,
                 aBd2DstH_, nBd2DstH_),
      rateRelativeNeutralAddition_(
          "rateRelativeNeutralAddition_",
          "Relative rate for gamma to be added randomly w.r.t. pi0", 2, 0, 10),
      rateFalseSignalReconstruction_(
          ("rateFalseSignalReconstruction_" + EnumToString(neutral_)).c_str(),
          "Probability for signal to be miss-reconstructed (addition or false "
          "neutral)",
          1, 0, 3),
      rateCrossFeed_(("rateCrossFeed_" + EnumToString(neutral_)).c_str(),
                     "Rate of cross feed w.r.t. signal", 1, 0, 5),
      signalYield_(("signal_yield_" +
                    ComposeFittingCategoryName(neutral_, bachelor_, daughters_))
                       .c_str(),
                   "m[Bu] signal yield", 10000, 0, 30000),
      // Improve this estimate for each decay mode?
      nonTMSignalYield_(
          ("nonTMSignalYield_" +
           ComposeFittingCategoryName(neutral_, bachelor_, daughters_))
              .c_str(),
          "Formula for non TM signal yield", "@0*@1",
          RooArgList(signalYield_, rateFalseSignalReconstruction_)),
      combinatorialYield_(("combinatorialYield_" +
                           ComposeFittingCategoryName(neutral_, bachelor_,
                                                      daughters_))
                              .c_str(),
                          "m[Bu] combinatorial yield", 1000, 0, 30000),
      missIdYield_(("missId_yield_" +
                    ComposeFittingCategoryName(neutral_, bachelor_, daughters_))
                       .c_str(),
                   "m[Bu] missId yield", 1000, 0, 30000),
      crossFeedYield_(("crossFeedYield_" +
                       ComposeFittingCategoryName(neutral_, bachelor_,
                                                  daughters_))
                          .c_str(),
                      "CrossFeed yield", "@0*@1",
                      RooArgList(signalYield_, rateCrossFeed_)),
      bu2Dst0Hst_D0pi0Yield_(("bu2Dst0Hst_D0pi0Yield_" +
                              ComposeFittingCategoryName(neutral_, bachelor_,
                                                         daughters_))
                                 .c_str(),
                             "Bu2Dst0Hst_D0pi0 yield", 5000, 0, 30000),
      bu2Dst0Hst_D0gammaYield_(("bu2Dst0Hst_D0gammaYield_" +
                                ComposeFittingCategoryName(neutral_, bachelor_,
                                                           daughters_))
                                   .c_str(),
                               "Bu2Dst0Hst_D0gamma yield", 5000, 0, 30000),
      bu2D0HYield_(("bu2D0HYield_" +
                    ComposeFittingCategoryName(neutral_, bachelor_, daughters_))
                       .c_str(),
                   "Bu2D0H yield", 3000, 0, 30000),
      bu2D0Hst_Pi0Yield_(("bu2D0Hst_Pi0Yield_" + EnumToString(bachelor_) + "_" +
                          EnumToString(daughters_))
                             .c_str(),
                         "Bu2D0Hst yield", 1000, 0, 30000),
      bd2DstH_Pi0Yield_(("bd2DstH_Pi0Yield_" + EnumToString(bachelor_) + "_" +
                         EnumToString(daughters_))
                            .c_str(),
                        "Bd2DstH yield", 1000, 0, 30000),
      bd2D0Hst0_Pi0Yield_(("bd2D0Hst0_Pi0Yield_" + EnumToString(bachelor_) +
                           "_" + EnumToString(daughters_))
                              .c_str(),
                          "Bd2D0Hst0 yield", 100, 0, 30000),
      // bu2D0H_GammaYield_(("bu2D0H_GammaYield_" + EnumToString(bachelor_) +
      // "_" +
      //                     EnumToString(daughters_))
      //                        .c_str(),
      //                    "Bu2D0H yield", "@0*@1",
      //                    RooArgList(bu2D0H_Pi0Yield_,
      //                               rateRelativeNeutralAddition_)),
      bu2D0Hst_GammaYield_(("bu2D0Hst_GammaYield_" + EnumToString(bachelor_) +
                            "_" + EnumToString(daughters_))
                               .c_str(),
                           "Bu2D0Hst yield", 1000, 0, 30000),
      // "@0*@1",
      // RooArgList(bu2D0Hst_Pi0Yield_,
      //            rateRelativeNeutralAddition_)),
      bd2DstH_GammaYield_(("bd2DstH_GammaYield_" + EnumToString(bachelor_) +
                           "_" + EnumToString(daughters_))
                              .c_str(),
                          "Bd2DstH yield", 2000, 0, 3000),
      // "@0*@1",
      // RooArgList(bd2DstH_Pi0Yield_,
      //            rateRelativeNeutralAddition_)),
      // bd2D0Hst0_GammaYield_(("bd2D0Hst0_GammaYield_" +
      // EnumToString(bachelor_) +
      //                        "_" + EnumToString(daughters_))
      //                           .c_str(),
      //                       "Bd2D0Hst0 yield",
      // "@0*@1",
      // RooArgList(bd2D0Hst0_Pi0Yield_,
      //            rateRelativeNeutralAddition_)),
      yields_(),
      functions_(),
      addPdf_(nullptr) {

  switch (neutral) {
  case Neutral::pi0:

    signalPi0Sigma_.setVal(17 * relativeWidth_);
    aSignalPi0_.setVal(2.13);
    nSignalPi0_.setVal(2.37);
    meanNonTMSignalPi0_.setVal(5284.8);
    sigmaLeftNonTMSignalPi0_.setVal(52.6 * relativeWidth_);
    sigmaRightNonTMSignalPi0_.setVal(49.4 * relativeWidth_);
    meanCrossFeed_.setVal(5283);
    sigmaCrossFeed_.setVal(80 * relativeWidth_);
    aCrossFeed_.setVal(3.5);
    nCrossFeed_.setVal(2.8);
    meanBu2D0H_.setVal(5492);
    sigmaLeftBu2D0H_.setVal(35.7 * relativeWidth_);
    sigmaRightBu2D0H_.setVal(46.7 * relativeWidth_);
    meanBu2D0Hst_.setVal(5304);
    sigmaBu2D0Hst_.setVal(51.9 * relativeWidth_);
    aBu2D0Hst_.setVal(0.33);
    nBu2D0Hst_.setVal(5.0);
    meanBd2DstH_.setVal(5277.6);
    sigmaBd2DstH_.setVal(54.3 * relativeWidth_);
    aBd2DstH_.setVal(4.0);
    nBd2DstH_.setVal(6.1);
    meanBd2D0Hst0_.setVal(5225);
    sigmaBd2D0Hst0_.setVal(107 * relativeWidth_);
    aBd2D0Hst0_.setVal(1.21);
    nBd2D0Hst0_.setVal(2.8);

    switch (bachelor) {
    case Bachelor::pi:
      // Miss-ID backgrounds have different shapes for pi and k modes
      meanBu2Dst0Hst_D0pi0_.setVal(5080);
      sigmaBu2Dst0Hst_D0pi0_.setVal(57.8);
      aBu2Dst0Hst_D0pi0_.setVal(1.23);
      nBu2Dst0Hst_D0pi0_.setVal(0.1);
      meanBu2Dst0Hst_D0gamma_.setVal(5068);
      sigmaBu2Dst0Hst_D0gamma_.setVal(91.5);
      aBu2Dst0Hst_D0gamma_.setVal(1.0);
      nBu2Dst0Hst_D0gamma_.setVal(0.1);
      relativeWidth_ = 1.0;
      meanMissId1_.setVal(5218.6);
      sigmaMissId1_.setVal(57.0);
      aMissId1_.setVal(-3.25);
      nMissId1_.setVal(4.77);
      meanMissId2_.setVal(5218.6);
      sigmaMissId2_.setVal(20.8);
      aMissId2_.setVal(0.50);
      nMissId2_.setVal(1.68);
      fracMissId1_.setVal(0.390);
      break;

    case Bachelor::k:
      // Scale factor given by ratio of BR's
      meanBu2Dst0Hst_D0pi0_.setVal(5102);
      sigmaBu2Dst0Hst_D0pi0_.setVal(49.5);
      aBu2Dst0Hst_D0pi0_.setVal(0.23);
      nBu2Dst0Hst_D0pi0_.setVal(0.3);
      meanBu2Dst0Hst_D0gamma_.setVal(5051);
      sigmaBu2Dst0Hst_D0gamma_.setVal(94.5);
      aBu2Dst0Hst_D0gamma_.setVal(-2.26);
      nBu2Dst0Hst_D0gamma_.setVal(6.8);
      relativeWidth_ = 0.95;
      meanMissId1_.setVal(5348.1);
      sigmaMissId1_.setVal(22.9);
      aMissId1_.setVal(-0.03);
      nMissId1_.setVal(25.3);
      meanMissId2_.setVal(5334.8);
      sigmaMissId2_.setVal(54.8);
      aMissId2_.setVal(3.80);
      nMissId2_.setVal(13.7);
      fracMissId1_.setVal(0.712);
      break;
    }

    functions_.add(signalPi0_);
    functions_.add(nonTMSignalPi0_);
    // functions_.add(combinatorialExponential_);
    functions_.add(bu2Dst0Hst_D0pi0_);
    functions_.add(bu2Dst0Hst_D0gamma_);
    functions_.add(crossFeed_);
    functions_.add(bu2D0H_);
    functions_.add(bu2D0Hst_);
    functions_.add(bd2DstH_);
    // functions_.add(bd2D0Hst0_);
    functions_.add(missId_);
    yields_.add(signalYield_);
    yields_.add(nonTMSignalYield_);
    // yields_.add(combinatorialYield_);
    yields_.add(bu2Dst0Hst_D0pi0Yield_);
    yields_.add(bu2Dst0Hst_D0gammaYield_);
    yields_.add(crossFeedYield_);
    yields_.add(bu2D0HYield_);
    yields_.add(bu2D0Hst_Pi0Yield_);
    yields_.add(bd2DstH_Pi0Yield_);
    // yields_.add(bd2D0Hst0_Pi0Yield_);
    yields_.add(missIdYield_);
    break;

  case Neutral::gamma:

    signalGammaSigmaLeft_.setVal(23 * relativeWidth_);
    signalGammaSigmaRight_.setVal(25 * relativeWidth_);
    meanNonTMSignalGamma_.setVal(5284.8);
    sigmaNonTMSignalGamma1_.setVal(86.8 * relativeWidth_);
    aNonTMSignalGamma1_.setVal(-1.27);
    nNonTMSignalGamma1_.setVal(10.0);
    fracNonTMSignalGamma1_.setVal(0.81);
    sigmaNonTMSignalGamma2_.setVal(29.1 * relativeWidth_);
    aNonTMSignalGamma2_.setVal(1.92);
    nNonTMSignalGamma2_.setVal(1.92);
    meanCrossFeed_.setVal(5266.5);
    sigmaCrossFeed_.setVal(80.2 * relativeWidth_);
    aCrossFeed_.setVal(3.17);
    nCrossFeed_.setVal(0.5);
    meanBu2D0H_.setVal(5430);
    sigmaLeftBu2D0H_.setVal(51.0 * relativeWidth_);
    sigmaRightBu2D0H_.setVal(93.6 * relativeWidth_);
    meanBu2D0Hst_.setVal(5221.7);
    sigmaBu2D0Hst_.setVal(87.0 * relativeWidth_);
    aBu2D0Hst_.setVal(1.58);
    nBu2D0Hst_.setVal(2.8);
    meanBd2DstH_.setVal(5257.0);
    sigmaBd2DstH_.setVal(81.7 * relativeWidth_);
    aBd2DstH_.setVal(3.9);
    nBd2DstH_.setVal(2.7);

    switch (bachelor) {
    case Bachelor::pi:
      // Miss-ID backgrounds have different shapes for pi and k modes
      meanBu2Dst0Hst_D0pi0_.setVal(5025);
      sigmaBu2Dst0Hst_D0pi0_.setVal(96.2);
      aBu2Dst0Hst_D0pi0_.setVal(1.36);
      nBu2Dst0Hst_D0pi0_.setVal(0.1);
      meanBu2Dst0Hst_D0gamma_.setVal(5089);
      sigmaBu2Dst0Hst_D0gamma_.setVal(49.2);
      aBu2Dst0Hst_D0gamma_.setVal(-1.86);
      nBu2Dst0Hst_D0gamma_.setVal(2.1);
      relativeWidth_ = 1.0;
      meanMissId1_.setVal(5218.6);
      sigmaMissId1_.setVal(57.0);
      aMissId1_.setVal(-3.25);
      nMissId1_.setVal(4.77);
      meanMissId2_.setVal(5218.6);
      sigmaMissId2_.setVal(20.8);
      aMissId2_.setVal(0.50);
      nMissId2_.setVal(1.68);
      fracMissId1_.setVal(0.390);

      functions_.add(signalGamma_);
      functions_.add(nonTMSignalGamma_);
      // functions_.add(combinatorialExponential_);
      functions_.add(bu2Dst0Hst_D0pi0_);
      functions_.add(bu2Dst0Hst_D0gamma_);
      functions_.add(crossFeed_);
      functions_.add(bu2D0H_);
      functions_.add(bu2D0Hst_);
      functions_.add(bd2DstH_);
      // functions_.add(bd2D0Hst0_);
      functions_.add(missId_);
      yields_.add(signalYield_);
      yields_.add(nonTMSignalYield_);
      // yields_.add(combinatorialYield_);
      yields_.add(bu2Dst0Hst_D0pi0Yield_);
      yields_.add(bu2Dst0Hst_D0gammaYield_);
      yields_.add(crossFeedYield_);
      yields_.add(bu2D0HYield_);
      yields_.add(bu2D0Hst_GammaYield_);
      yields_.add(bd2DstH_GammaYield_);
      // yields_.add(bd2D0Hst0_GammaYield_);
      yields_.add(missIdYield_);

      break;

    case Bachelor::k:
      
      meanBu2Dst0Kst_D0pi0_Gamma_.setVal(5091);
      sigmaBu2Dst0Kst_D0pi0_Gamma_.setVal(97.6);
      // meanBu2Dst0Hst_D0pi0_.setVal(5104);
      // sigmaBu2Dst0Hst_D0pi0_.setVal(92);
      // aBu2Dst0Hst_D0pi0_.setVal(0);
      // nBu2Dst0Hst_D0pi0_.setVal(0);
      meanBu2Dst0Hst_D0gamma_.setVal(5100);
      sigmaBu2Dst0Hst_D0gamma_.setVal(61);
      aBu2Dst0Hst_D0gamma_.setVal(-0.98);
      nBu2Dst0Hst_D0gamma_.setVal(10);
      relativeWidth_ = 0.95;
      meanMissId1_.setVal(5344.8);
      sigmaMissId1_.setVal(30.0);
      aMissId1_.setVal(-0.68);
      nMissId1_.setVal(10.0);
      meanMissId2_.setVal(5344.8);
      sigmaMissId2_.setVal(97.4);
      aMissId2_.setVal(1.62);
      nMissId2_.setVal(0.0);
      fracMissId1_.setVal(0.747);

      functions_.add(signalGamma_);
      functions_.add(nonTMSignalGamma_);
      // functions_.add(combinatorialExponential_);
      functions_.add(bu2Dst0Kst_D0pi0_Gamma_);
      functions_.add(bu2Dst0Hst_D0gamma_);
      functions_.add(crossFeed_);
      functions_.add(bu2D0H_);
      functions_.add(bu2D0Hst_);
      functions_.add(bd2DstH_);
      // functions_.add(bd2D0Hst0_);
      functions_.add(missId_);
      yields_.add(signalYield_);
      yields_.add(nonTMSignalYield_);
      // yields_.add(combinatorialYield_);
      yields_.add(bu2Dst0Hst_D0pi0Yield_);
      yields_.add(bu2Dst0Hst_D0gammaYield_);
      yields_.add(crossFeedYield_);
      yields_.add(bu2D0HYield_);
      yields_.add(bu2D0Hst_GammaYield_);
      yields_.add(bd2DstH_GammaYield_);
      // yields_.add(bd2D0Hst0_GammaYield_);
      yields_.add(missIdYield_);

      break;
    }

    break;
  }

  addPdf_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("pdf_" + ComposeFittingCategoryName(neutral_, bachelor_, daughters_))
          .c_str(),
      ("pdf_" + ComposeFittingCategoryName(neutral_, bachelor_, daughters_))
          .c_str(),
      functions_, yields_));
}

void Pdf::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(
      *addPdf_,
      ComposeFittingCategoryName(neutral_, bachelor_, daughters_).c_str());
}

