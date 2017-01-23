#include "NeutralVars.h"
#include "Configuration.h"

// Neutral specializations

template <>
NeutralVars<Neutral::gamma>::NeutralVars()
    : meanCrossFeed_("meanBu2Dst0H_D0pi0_Gamma", "Gamma Bu2Dst0H_D0pi0 mean",
                     5257),
      aCrossFeed_1_("aBu2Dst0H_D0pi0_1_Gamma", "Gamma Bu2Dst0H_D0pi0 a 1",
                    -0.079),
      aCrossFeed_2_("aBu2Dst0H_D0pi0_2_Gamma", "Gamma Bu2Dst0H_D0pi0 a 2",
                    0.045),
      meanSignal_("meanBu2Dst0H_D0gamma_Gamma", "Gamma Bu2Dst0H_D0gamma mean",
                  5281, 5277, 5285),
      aSignal_1_("aBu2Dst0H_D0gamma_1_Gamma", "Gamma Bu2Dst0H_D0gamma a 1",
                 0.064),
      aSignal_2_("aBu2Dst0H_D0gamma_2_Gamma", "Gamma Bu2Dst0H_D0gamma a 2",
                 0.066),
      meanNonTmSignal_("meanNonTmSignal_Gamma", "Gamma NonTmSignal mean", 5275),
      aNonTmSignal_1_("aNonTmSignal_1_Gamma", "Gamma NonTmSignal a 1", 0.207),
      aNonTmSignal_2_("aNonTmSignal_2_Gamma", "Gamma NonTmSignal a 2", 0.093),
      meanBu2D0H_1_(
          new RooConstVar("meanBu2D0H_1_Gamma", "Gamma Bu20H mean 1", 5435.9)),
      meanBu2D0H_2_(), aBu2D0H_1_(), aBu2D0H_2_(), nBu2D0H_1_(), nBu2D0H_2_(),
      fracBu2D0H_1_(),
      meanBu2D0Hst_("meanBu2D0Hst_Gamma", "Gamma Bu2D0Hst mean", 5242),
      aBu2D0Hst_("aBu2D0Hst_Gamma", "Gamma Bu2D0Hst a", 0.355),
      nBu2D0Hst_("nBu2D0Hst_Gamma", "Gamma Bu2D0Hst n", 10),
      meanBd2DstH_("meanBd2DstH_Gamma", "Gamma Bd2DstH mean", 5253.7),
      aBd2DstH_1_("aBd2DstH_1_Gamma", "Gamma Bd2DstH a 1", -0.052),
      aBd2DstH_2_("aBd2DstH_2_Gamma", "Gamma Bd2DstH a 2", 0.033),
      maxYield_(29000), bu2D0HExpected_(6080), bd2DstHExpected_(2570),
      bu2Dst0Hst_D0pi0Expected_(2650), bu2Dst0Hst_D0gammaExpected_(3530),
      bu2D0HstExpected_(1840), nonTmSignalExpected_(7000),
      crossFeedExpected_(6230), signalExpected_(9830),
      combinatorialExpected_(100),
      relativeBu2D0HYield_(
          "relativeBu2D0HYield_Gamma",
          "Relative yield of Bu2D0H w.r.t. N_Dh, Gamma mode", 0.57784),
      relativeBu2D0HstYield_(
          "relativeBu2D0HstYield_Gamma",
          "Relative yield of Bu2D0Hst w.r.t. N_Dh, Gamma mode", 0.16205),
      relativeBd2DstHYield_("relativeBd2DstHYield_Gamma",
                            "Relative yield of Bd2DstH w.r.t. N_Dh, Gamma mode",
                            0.23142),
      relativeBu2Dst0Hst_D0pi0Yield_(
          "relativeBu2Dst0Hst_D0pi0Yield_Gamma",
          "Relative yield of Bu2Dst0Hst_D0pi0 w.r.t. N_Dh, Gamma mode", 0.21538),
      relativeBu2Dst0Hst_D0gammaYield_(
          "relativeBu2Dst0Hst_D0gammaYield_Gamma",
          "Relative yield of Bu2Dst0Hst_D0gamma w.r.t. N_Dh, Gamma mode", 0.27199),
      selfCrossFeedRate_(new RooRealVar("selfCrossFeedRate_gamma",
                                        "Proportion of SCF in N_Dpi, gamma, kk",
                                        0.26424)),
      crossFeedRate_(new RooRealVar("crossFeedRate_gamma",
                                    "Proportion of CF in N_Dpi, gamma",
                                    0.10187)) {}

template <>
NeutralVars<Neutral::pi0>::NeutralVars()
    : meanSignal_("meanBu2Dst0H_D0pi0_Pi0", "Pi0 Bu2Dst0H_D0pi0 mean", 5281,
                  5279, 5283),
      aSignal_1_("aBu2Dst0H_D0pi0_Pi0_1", "Pi0 Bu2Dst0H_D0pi0 a 1", 0.125),
      aSignal_2_("aBu2Dst0H_D0pi0_Pi0_2", "Pi0 Bu2Dst0H_D0pi0 a 2", 0.087),
      meanCrossFeed_("meanBu2Dst0H_D0gamma_Pi0", "Pi0 Bu2Dst0H_D0gamma mean",
                     5283),
      aCrossFeed_1_("aBu2Dst0H_D0gamma_1_Pi0", "Pi0 Bu2Dst0H_D0gamma a 1",
                    2.96),
      aCrossFeed_2_("aBu2Dst0H_D0gamma_2_Pi0", "Pi0 Bu2Dst0H_D0gamma a 2", 2.5),
      meanNonTmSignal_("meanNonTmSignal_Pi0", "Pi0 NonTmSignal mean", 5278),
      aNonTmSignal_1_("aNonTmSignal_1_Pi0", "Pi0 NonTmSignal_1 a", 0.128),
      aNonTmSignal_2_("aNonTmSignal_2_Pi0", "Pi0 NonTmSignal_2 a", 0.021),
      meanBu2D0H_1_(new RooRealVar("meanBu2D0H_1_Pi0", "Pi0 Bu2D0H mean 1",
                                   5470, 5465, 5475)),
      meanBu2D0H_2_("meanBu2D0H_2_Pi0", "Pi0 Bu2D0H mean 2", 5525, 5520, 5540),
      aBu2D0H_1_("aBu2D0H_1_Pi0", "Pi0 Bu2D0H a 1", -0.84), // -5, 5),
      aBu2D0H_2_("aBu2D0H_2_Pi0", "Pi0 Bu2D0H a 2", 1.69),  // -5, 5),
      nBu2D0H_1_("nBu2D0H_1_Pi0", "Pi0 Bu2D0H n 1", 13),    // 0, 20),
      nBu2D0H_2_("nBu2D0H_2_Pi0", "Pi0 Bu2D0H n 2", 2.0),   // 0, 20),
      fracBu2D0H_1_("fracBu2D0H_1_Pi0", "Pi0 Bu2D0H first shape fraction",
                    0.376, 0, 1),
      meanBu2D0Hst_("meanBu2D0Hst_Pi0", "Pi0 Bu2D0Hst mean", 5298),
      aBu2D0Hst_("aBu2D0Hst_Pi0", "Pi0 Bu2D0Hst a", 0.52),
      nBu2D0Hst_("nBu2D0Hst_Pi0", "Pi0 Bu2D0Hst n", 0.25),
      meanBd2DstH_("meanBd2DstH_Pi0", "Pi0 Bd2DstH mean", 5274.5),
      aBd2DstH_1_("aBd2DstH_1_Pi0", "Pi0 Bd2DstH a 1", -0.0498),
      aBd2DstH_2_("aBd2DstH_2_Pi0", "Pi0 Bd2DstH a 2", 0.041), maxYield_(27000),
      bu2D0HExpected_(2830), bd2DstHExpected_(1340),
      bu2Dst0Hst_D0pi0Expected_(5470), bu2Dst0Hst_D0gammaExpected_(540),
      bu2D0HstExpected_(2450), nonTmSignalExpected_(7000),
      signalExpected_(9540), crossFeedExpected_(1860),
      combinatorialExpected_(100),
      relativeBu2D0HYield_("relativeBu2D0HYield_Pi0",
                           "Relative yield of Bu2D0H w.r.t. N_Dh, Pi0 mode",
                           0.10277),
      relativeBu2D0HstYield_("relativeBu2D0HstYield_Pi0",
                             "Relative yield of Bu2D0Hst w.r.t. N_Dh, Pi0 mode",
                             0.08897),
      relativeBd2DstHYield_("relativeBd2DstHYield_Pi0",
                            "Relative yield of Bd2DstH w.r.t. N_Dh, Pi0 mode",
                            0.04860),
      relativeBu2Dst0Hst_D0pi0Yield_(
          "relativeBu2Dst0Hst_D0pi0Yield_Pi0",
          "Relative yield of Bu2Dst0Hst_D0pi0 w.r.t. N_Dh, Pi0 mode", 0.19867),
      relativeBu2Dst0Hst_D0gammaYield_(
          "relativeBu2Dst0Hst_D0gammaYield_Pi0",
          "Relative yield of Bu2Dst0Hst_D0gamma w.r.t. N_Dh, Pi0 mode", 0.019708),
      selfCrossFeedRate_(new RooConstVar("selfCrossFeedRate_pi0",
                                         "Proportion of SCF in N_Dpi, pi0, kpi",
                                         0.31394)),
      crossFeedRate_(new RooConstVar("crossFeedRate_pi0",
                                     "Proportion of CF in N_Dpi, pi0",
                                     0.34005)) {}

