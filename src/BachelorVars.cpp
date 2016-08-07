#include "BachelorVars.h"
#include "Configuration.h"
#include "NeutralVars.h"
#include "RooBifurGauss.h"
#include "RooCBShape.h"
#include "RooCruijff.h"
#include "RooGaussian.h"
#include "RooPolynomial.h"

// Bachelor specializations

template <>
BachelorVars<Neutral::gamma, Bachelor::pi>::BachelorVars()
    : bu2Dst0MissIdBR_("bu2Dst0MissIdBR", "Branching Ratio of Bu2Dst0pi",
                       0.000420),
      bu2Dst0HBR_("bu2Dst0HBR", "Branching Ratio of Bu2Dst0K", 0.00518),
      missIdRate_("missIdRate", "Rate of miss-ID with PIDK>12", 0.3266),
      bachEff_("bachEff", "Efficiency of detection of bachelor K with PIDK>12",
               0.9965),
      sigmaCrossFeed_1_(
          new RooRealVar("sigmaLeftBu2Dst0H_D0pi0_GammaPi",
                         "Gamma, Pi Bu2Dst0H_D0pi0 sigma left", 77.6)),
      sigmaCrossFeed_2_(
          new RooRealVar("sigmaRightBu2Dst0H_D0pi0_GammaPi",
                         "Gamma, Pi Bu2Dst0H_D0pi0 sigma right", 81.0)),
      sigmaSignal_1_(new RooRealVar(
          "sigmaLeftBu2Dst0H_D0gamma_GammaPi",
          "Gamma, Pi Bu2Dst0H_D0gamma sigma left", 20.9, 15, 23)), //18
      sigmaSignal_2_(new RooRealVar(
          "sigmaRightBu2Dst0H_D0gamma_GammaPi",
          "Gamma, Pi Bu2Dst0H_D0gamma sigma right", 21.7, 15, 25)), //20
      sigmaNonTmSignal_1_(new RooRealVar(
          "sigmaNonTmSignal_1_GammaPi", "Gamma, Pi NonTmSignal sigma 1", 71.6)),
      sigmaNonTmSignal_2_(new RooRealVar(
          "sigmaNonTmSignal_2_GammaPi", "Gamma, Pi NonTmSignal sigma 2", 75.7)),
      sigmaBu2D0H_1_(new RooRealVar("sigmaLeftBu2D0H_GammaPi",
                                    "Gamma, Pi Bu2D0H sigma left", 54.1)),
      sigmaBu2D0H_2_(new RooRealVar("sigmaRightBu2D0H_GammaPi",
                                    "Gamma, Pi Bu2D0H sigma right", 90.4)),
      sigmaBu2D0Hst_(new RooRealVar("sigmaBu2D0Hst_GammaPi",
                                    "Gamma, Pi Bu2D0Hst sigma", 115.3)),
      sigmaBd2DstH_1_(new RooRealVar("sigmaLeftBd2DstH_GammaPi",
                                     "Gamma, Pi Bd2DstH sigma left", 82)),
      sigmaBd2DstH_2_(new RooRealVar("sigmaRightBd2DstH_GammaPi",
                                     "Gamma, Pi Bd2DstH sigma right", 80.4)),
      meanBu2Dst0Hst_D0pi0_("meanBu2Dst0Hst_D0pi0_GammaPi",
                            "Gamma, Pi Bu2Dst0Hst_D0pi0 mean", 5025),
      sigmaBu2Dst0Hst_D0pi0_("sigmaBu2Dst0Hst_D0pi0_GammaPi",
                             "Gamma, Pi Bu2Dst0Hst_D0pi0 sigma", 96.2),
      aBu2Dst0Hst_D0pi0_("aBu2Dst0Hst_D0pi0_GammaPi",
                         "Gamma, Pi Bu2Dst0Hst_D0pi0 a", 1.36),
      nBu2Dst0Hst_D0pi0_("nBu2Dst0Hst_D0pi0_GammaPi",
                         "Gamma, Pi Bu2Dst0Hst_D0pi0 n", 0.1),
      meanBu2Dst0Hst_D0gamma_("meanBu2Dst0Hst_D0gamma_GammaPi",
                              "Gamma, Pi Bu2Dst0Hst_D0gamma mean", 5089),
      sigmaBu2Dst0Hst_D0gamma_("sigmaBu2Dst0Hst_D0gamma_GammaPi",
                               "Gamma, Pi Bu2Dst0Hst_D0gamma sigma", 49.2),
      aBu2Dst0Hst_D0gamma_("aBu2Dst0Hst_D0gamma_GammaPi",
                           "Gamma, Pi Bu2Dst0Hst_D0gamma a", -1.86),
      nBu2Dst0Hst_D0gamma_("nBu2Dst0Hst_D0gamma_GammaPi",
                           "Gamma, Pi Bu2Dst0Hst_D0gamma n", 2.1),
      meanMissId1_("meanMissId1_GammaPi", "Gamma, Pi Miss ID mean", 5218.6),
      sigmaMissId1_("sigmaMissId1_GammaPi", "Gamma, Pi Miss ID sigma", 92.3),
      aMissId1_("aMissId1_GammaPi", "Gamma, Pi Miss ID a", -1.90),
      nMissId1_("nMissId1_GammaPi", "Gamma, Pi Miss ID n", 2.7),
      fracMissId1_("fracMissId1_GammaPi", "Gamma, Pi Miss ID fraction of PDF 1",
                   0.234),
      meanMissId2_(),
      sigmaMissId2_("sigmaMissId2_GammaPi", "Gamma, Pi Miss ID sigma", 30.4),
      aMissId2_("aMissId2_GammaPi", "Gamma, Pi Miss ID a", 0.77),
      nMissId2_("nMissId2_GammaPi", "Gamma, Pi Miss ID n", 5.3),
      crossFeed_(new RooCruijff(
          "bu2Dst0H_D0pi0_GammaPi", "Gamma, Pi bu2Dst0H_D0pi0 Cruijff",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanCrossFeed(),
          *sigmaCrossFeed_1_, *sigmaCrossFeed_2_,
          NeutralVars<Neutral::gamma>::Get().aCrossFeed_1(),
          NeutralVars<Neutral::gamma>::Get().aCrossFeed_2())),
      signal_(new RooCruijff(
          "bu2Dst0H_D0gamma_GammaPi", "Gamma, Pi bu2Dst0H_D0gamma BifurGauss",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanSignal(),
          *sigmaSignal_1_, *sigmaSignal_2_,
          NeutralVars<Neutral::gamma>::Get().aSignal_1(),
          NeutralVars<Neutral::gamma>::Get().aSignal_2())),
      nonTmSignal_(new RooCruijff(
          "nonTmSignal_GammaPi", "Gamma, Pi nonTmSignal RooCruijff ",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanNonTmSignal(),
          *sigmaNonTmSignal_1_, *sigmaNonTmSignal_2_,
          NeutralVars<Neutral::gamma>::Get().aNonTmSignal_1(),
          NeutralVars<Neutral::gamma>::Get().aNonTmSignal_2())),
      bu2Dst0Hst_D0pi0_(new RooCBShape(
          "bu2Dst0Hst_D0pi0_GammaPi", "Gamma, Pi bu2Dst0Hst_D0pi0 CBShape",
          Configuration::Get().buMass(), meanBu2Dst0Hst_D0pi0_,
          sigmaBu2Dst0Hst_D0pi0_, aBu2Dst0Hst_D0pi0_, nBu2Dst0Hst_D0pi0_)),
      bu2Dst0Hst_D0gamma_(new RooCBShape(
          "bu2Dst0Hst_D0gamma_GammaPi", "Gamma, Pi bu2Dst0Hst_D0gamma CBShape",
          Configuration::Get().buMass(), meanBu2Dst0Hst_D0gamma_,
          sigmaBu2Dst0Hst_D0gamma_, aBu2Dst0Hst_D0gamma_,
          nBu2Dst0Hst_D0gamma_)),
      bu2D0H_1_(nullptr), bu2D0H_2_(nullptr),
      bu2D0H_(new RooBifurGauss(
          "bu2D0H_GammaPi", "Gamma, Pi bu2Dst0H_D0gamma RooBifurGauss",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanBu2D0H_1(), *sigmaBu2D0H_1_,
          *sigmaBu2D0H_2_)),
      bu2D0Hst_(new RooCBShape(
          "bu2D0Hst_GammaPi", "Gamma, Pi bu2D0Hst CBShape",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanBu2D0Hst(), *sigmaBu2D0Hst_,
          NeutralVars<Neutral::gamma>::Get().aBu2D0Hst(),
          NeutralVars<Neutral::gamma>::Get().nBu2D0Hst())),
      bd2DstH_(new RooCruijff(
          "bd2DstH_GammaPi", "Gamma, Pi bd2DstH_ CBShape",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanBd2DstH(), *sigmaBd2DstH_1_,
          *sigmaBd2DstH_2_, NeutralVars<Neutral::gamma>::Get().aBd2DstH_1(),
          NeutralVars<Neutral::gamma>::Get().aBd2DstH_2())),
      missId1_(new RooCBShape("missId1_GammaPi", "Gamma, Pi missId1 CBShape",
                              Configuration::Get().buMass(), meanMissId1_,
                              sigmaMissId1_, aMissId1_, nMissId1_)),
      missId2_(new RooCBShape("missId2_GammaPi", "Gamma, Pi missId2 CBShape",
                              Configuration::Get().buMass(), meanMissId1_,
                              sigmaMissId2_, aMissId2_, nMissId2_)),
      missId_(new RooAddPdf("missId_GammaPi", "Gamma, Pi missId AddPdf",
                            RooArgList(*missId1_, *missId2_), fracMissId1_)),
      bachelorSF_(1.0) {}

template <>
BachelorVars<Neutral::gamma, Bachelor::k>::BachelorVars()
    : bu2Dst0MissIdBR_("bu2Dst0MissIdBR", "Branching Ratio of Bu2Dst0pi",
                       0.00518),
      bu2Dst0HBR_("bu2Dst0HBR", "Branching Ratio of Bu2Dst0K", 0.000420),
      missIdRate_("missIdRate", "Rate of miss-ID with PIDK>12", 0.0035),
      bachEff_("bachEff", "Efficiency of detection of bachelor K with PIDK>12",
               0.6734),
      sigmaCrossFeed_1_(new RooFormulaVar(
          "sigmaLeftBu2Dst0H_D0pi0_GammaK",
          "Gamma, K Bu2Dst0H_D0pi0 sigma left", "@0*@1",
          RooArgList(BachelorVars<Neutral::gamma, Bachelor::pi>::Get()
                         .sigmaCrossFeed_1(),
                     Configuration::Get().relativeWidth()))),
      sigmaCrossFeed_2_(new RooFormulaVar(
          "sigmaRightBu2Dst0H_D0pi0_GammaK",
          "Gamma, K Bu2Dst0H_D0pi0 sigma right", "@0*@1",
          RooArgList(BachelorVars<Neutral::gamma, Bachelor::pi>::Get()
                         .sigmaCrossFeed_2(),
                     Configuration::Get().relativeWidth()))),
      sigmaSignal_1_(new RooFormulaVar(
          "sigmaLeftBu2Dst0H_D0gamma_GammaK",
          "Gamma, K Bu2Dst0H_D0gamma sigma left", "@0*@1",
          RooArgList(BachelorVars<Neutral::gamma, Bachelor::pi>::Get()
                         .sigmaSignal_1(),
                     Configuration::Get().relativeWidth()))),
      sigmaSignal_2_(new RooFormulaVar(
          "sigmaRightBu2Dst0H_D0gamma_GammaK",
          "Gamma, K Bu2Dst0H_D0gamma sigma right", "@0*@1",
          RooArgList(BachelorVars<Neutral::gamma, Bachelor::pi>::Get()
                         .sigmaSignal_2(),
                     Configuration::Get().relativeWidth()))),
      sigmaNonTmSignal_1_(new RooFormulaVar(
          "sigmaNonTmSignal_1_GammaK", "Gamma, K NonTmSignal sigma 1", "@0*@1",
          RooArgList(BachelorVars<Neutral::gamma, Bachelor::pi>::Get()
                         .sigmaNonTmSignal_1(),
                     Configuration::Get().relativeWidth()))),
      sigmaNonTmSignal_2_(new RooFormulaVar(
          "sigmaNonTmSignal_2_GammaK", "Gamma, K NonTmSignal sigma 2", "@0*@1",
          RooArgList(BachelorVars<Neutral::gamma, Bachelor::pi>::Get()
                         .sigmaNonTmSignal_2(),
                     Configuration::Get().relativeWidth()))),
      sigmaBu2D0H_1_(new RooFormulaVar(
          "sigmaLeftBu2D0H_GammaK", "Gamma, K Bu2D0H sigma left", "@0*@1",
          RooArgList(
              BachelorVars<Neutral::gamma, Bachelor::pi>::Get().sigmaBu2D0H_1(),
              Configuration::Get().relativeWidth()))),
      sigmaBu2D0H_2_(new RooFormulaVar(
          "sigmaRightBu2D0H_GammaK", "Gamma, K Bu2D0H sigma right ", "@0*@1",
          RooArgList(
              BachelorVars<Neutral::gamma, Bachelor::pi>::Get().sigmaBu2D0H_2(),
              Configuration::Get().relativeWidth()))),
      sigmaBu2D0Hst_(new RooFormulaVar(
          "sigmaRightBu2D0Hst_GammaK", "Gamma, K Bu2D0Hst sigma right", "@0*@1",
          RooArgList(
              BachelorVars<Neutral::gamma, Bachelor::pi>::Get().sigmaBu2D0Hst(),
              Configuration::Get().relativeWidth()))),
      sigmaBd2DstH_1_(new RooFormulaVar(
          "sigmaLeftBd2DstH_GammaK", "Gamma, K Bd2DstH sigma left", "@0*@1",
          RooArgList(
              BachelorVars<Neutral::gamma, Bachelor::pi>::Get().sigmaBd2DstH_1(),
              Configuration::Get().relativeWidth()))),
      sigmaBd2DstH_2_(new RooFormulaVar(
          "sigmaRightBd2DstH_GammaK", "Gamma, K Bd2DstH sigma right", "@0*@1",
          RooArgList(
              BachelorVars<Neutral::gamma, Bachelor::pi>::Get().sigmaBd2DstH_2(),
              Configuration::Get().relativeWidth()))),
      meanBu2Dst0Hst_D0pi0_("meanBu2Dst0Hst_D0pi0_GammaK",
                            "Gamma, K Bu2Dst0Hst_D0pi0 mean", 5091),
      sigmaBu2Dst0Hst_D0pi0_("sigmaBu2Dst0Hst_D0pi0_GammaK",
                             "Gamma, K Bu2Dst0Hst_D0pi0 sigma", 97.6),
      aBu2Dst0Hst_D0pi0_(), nBu2Dst0Hst_D0pi0_(),
      meanBu2Dst0Hst_D0gamma_("meanBu2Dst0Hst_D0gamma_GammaK",
                              "Gamma, K Bu2Dst0Hst_D0gamma mean", 5100),
      sigmaBu2Dst0Hst_D0gamma_("sigmaBu2Dst0Hst_D0gamma_GammaK",
                               "Gamma, K Bu2Dst0Hst_D0gamma sigma", 61),
      aBu2Dst0Hst_D0gamma_("aBu2Dst0Hst_D0gamma_GammaK",
                           "Gamma, K Bu2Dst0Hst_D0gamma a", -0.98),
      nBu2Dst0Hst_D0gamma_("nBu2Dst0Hst_D0gamma_GammaK",
                           "Gamma, K Bu2Dst0Hst_D0gamma n", 10),
      meanMissId1_("meanMissId1_GammaK", "Gamma, K Miss ID mean", 5344.8),
      sigmaMissId1_("sigmaMissId1_GammaK", "Gamma, K Miss ID sigma", 30.0),
      aMissId1_("aMissId1_GammaK", "Gamma, K Miss ID a", -0.68),
      nMissId1_("nMissId1_GammaK", "Gamma, K Miss ID n", 10.0),
      fracMissId1_("fracMissId1_GammaK", "Gamma, K Miss ID fraction of PDF 1 ",
                   0.747),
      meanMissId2_(),
      sigmaMissId2_("sigmaMissId2_GammaK", "Gamma, K Miss ID sigma", 97.4),
      aMissId2_("aMissId2_GammaK", "Gamma, K Miss ID a", 1.62),
      nMissId2_("nMissId2_GammaK", "Gamma, K Miss ID n", 0.0),
      crossFeed_(new RooCruijff(
          "bu2Dst0H_D0pi0_GammaPi", "Gamma, Pi bu2Dst0H_D0pi0 Cruijff",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanCrossFeed(),
          *sigmaCrossFeed_1_, *sigmaCrossFeed_2_,
          NeutralVars<Neutral::gamma>::Get().aCrossFeed_1(),
          NeutralVars<Neutral::gamma>::Get().aCrossFeed_2())),
      signal_(new RooCruijff(
          "bu2Dst0H_D0gamma_GammaPi", "Gamma, Pi bu2Dst0H_D0gamma Cruijff",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanSignal(),
          *sigmaSignal_1_, *sigmaSignal_2_,
          NeutralVars<Neutral::gamma>::Get().aSignal_1(),
          NeutralVars<Neutral::gamma>::Get().aSignal_2())),
      nonTmSignal_(new RooCruijff(
          "nonTmSignal_GammaK", "Gamma, K nonTmSignal RooCruijff ",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanNonTmSignal(),
          *sigmaNonTmSignal_1_, *sigmaNonTmSignal_2_,
          NeutralVars<Neutral::gamma>::Get().aNonTmSignal_1(),
          NeutralVars<Neutral::gamma>::Get().aNonTmSignal_2())),
      bu2Dst0Hst_D0pi0_(new RooGaussian(
          "bu2Dst0Hst_D0pi0_GammaK", "Gamma, K bu2Dst0Hst_D0pi0 CBShape",
          Configuration::Get().buMass(), meanBu2Dst0Hst_D0pi0_,
          sigmaBu2Dst0Hst_D0pi0_)),
      bu2Dst0Hst_D0gamma_(new RooCBShape(
          "bu2Dst0Hst_D0gamma_GammaK", "Gamma, K bu2Dst0Hst_D0gamma CBShape",
          Configuration::Get().buMass(), meanBu2Dst0Hst_D0gamma_,
          sigmaBu2Dst0Hst_D0gamma_, aBu2Dst0Hst_D0gamma_,
          nBu2Dst0Hst_D0gamma_)),
      bu2D0H_1_(nullptr), bu2D0H_2_(nullptr),
      bu2D0H_(new RooBifurGauss(
          "bu2D0H_GammaK", "Gamma, K bu2Dst0H_D0gamma RooBifurGauss",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanBu2D0H_1(), *sigmaBu2D0H_1_,
          *sigmaBu2D0H_2_)),
      bu2D0Hst_(new RooCBShape(
          "bu2D0Hst_GammaK", "Gamma, K bu2D0Hst CBShape",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanBu2D0Hst(), *sigmaBu2D0Hst_,
          NeutralVars<Neutral::gamma>::Get().aBu2D0Hst(),
          NeutralVars<Neutral::gamma>::Get().nBu2D0Hst())),
      bd2DstH_(new RooCruijff("bd2DstH_GammaK", "Gamma, K bd2DstH_ CBShape",
                              Configuration::Get().buMass(),
                              NeutralVars<Neutral::gamma>::Get().meanBd2DstH(),
                              *sigmaBd2DstH_1_,*sigmaBd2DstH_2_,
                              NeutralVars<Neutral::gamma>::Get().aBd2DstH_1(),
                              NeutralVars<Neutral::gamma>::Get().aBd2DstH_2())),
      missId1_(new RooCBShape("missId1_GammaK", "Gamma, K missId1 CBShape",
                              Configuration::Get().buMass(), meanMissId1_,
                              sigmaMissId1_, aMissId1_, nMissId1_)),
      missId2_(new RooCBShape("missId2_GammaK", "Gamma, K missId2 CBShape",
                              Configuration::Get().buMass(), meanMissId1_,
                              sigmaMissId2_, aMissId2_, nMissId2_)),
      missId_(new RooAddPdf("missId_GammaK", "Gamma, K missId AddPdf",
                            RooArgList(*missId1_, *missId2_), fracMissId1_)),
      bachelorSF_(0.08) {}

template <>
BachelorVars<Neutral::pi0, Bachelor::pi>::BachelorVars()
    : bu2Dst0MissIdBR_("bu2Dst0MissIdBR", "Branching Ratio of Bu2Dst0pi",
                       0.000420),
      bu2Dst0HBR_("bu2Dst0HBR", "Branching Ratio of Bu2Dst0K", 0.00518),
      missIdRate_("missIdRate", "Rate of miss-ID with PIDK>12", 0.3266),
      bachEff_("bachEff", "Efficiency of detection of bachelor K with PIDK>12",
               0.9965),
      sigmaSignal_1_(new RooRealVar("sigmaLeftBu2Dst0H_D0pi0_Pi0Pi",
                                            "Pi0, Pi Bu2Dst0H_D0pi0 sigma", 14,
                                            9, 15)), //11
      sigmaSignal_2_(new RooRealVar("sigmaRightBu2Dst0H_D0pi0_Pi0Pi",
                                            "Pi0, Pi Bu2Dst0H_D0pi0 sigma", 16,
                                            10, 25)), //15
      sigmaCrossFeed_1_(
          new RooRealVar("sigmaBu2Dst0H_D0gamma_1_Pi0Pi",
                         "Pi0, Pi Bu2Dst0H_D0gamma sigma 1", 80)),
      // sigmaCrossFeed_2_(
      //     new RooRealVar("sigmaBu2Dst0H_D0gamma_2_Pi0Pi",
      //                    "Pi0, Pi Bu2Dst0H_D0gamma sigma 2", 102)),
      sigmaCrossFeed_2_(nullptr),
      sigmaNonTmSignal_1_(new RooRealVar("sigma1NonTmSignal_Pi0Pi",
                                         "Pi0, Pi NonTmSignal sigma 1", 40.1)),
      sigmaNonTmSignal_2_(new RooRealVar("sigma2NonTmSignal_Pi0Pi",
                                         "Pi0, Pi NonTmSignal sigma 2", 50.5)),
      sigmaBu2D0H_1_(new RooRealVar("sigmaLeftBu2D0H_Pi0Pi",
                                    "Pi0, Pi Bu2D0H sigma left", 35.7, 10, 40)),
      sigmaBu2D0H_2_(new RooRealVar("sigmaRightBu2D0H_Pi0Pi",
                                    "Pi0, Pi Bu2D0H sigma right", 46.7, 20,
                                    50)),
      sigmaBu2D0Hst_(new RooRealVar("sigmaRightBu2D0Hst_Pi0Pi",
                                    "Pi0, Pi Bu2D0Hst sigma right", 53.0)),
      sigmaBd2DstH_1_(new RooRealVar("sigmaLeftBd2DstH_Pi0Pi",
                                   "Pi0, Pi Bd2DstH sigma left", 52.1)),
      sigmaBd2DstH_2_(new RooRealVar("sigmaRightBd2DstH_Pi0Pi",
                                   "Pi0, Pi Bd2DstH sigma right", 55.8)),
      meanBu2Dst0Hst_D0pi0_("meanBu2Dst0Hst_D0pi0_Pi0Pi",
                            "Pi0, Pi Bu2Dst0Hst_D0pi0 mean", 5080),
      sigmaBu2Dst0Hst_D0pi0_("sigmaBu2Dst0Hst_D0pi0_Pi0Pi",
                             "Pi0, Pi Bu2Dst0Hst_D0pi0 sigma", 57.8),
      aBu2Dst0Hst_D0pi0_("aBu2Dst0Hst_D0pi0_Pi0Pi",
                         "Pi0, Pi Bu2Dst0Hst_D0pi0 a", 1.23),
      nBu2Dst0Hst_D0pi0_("nBu2Dst0Hst_D0pi0_Pi0Pi",
                         "Pi0, Pi Bu2Dst0Hst_D0pi0 n", 0.1),
      meanBu2Dst0Hst_D0gamma_("meanBu2Dst0Hst_D0gamma_Pi0Pi",
                              "Pi0, Pi Bu2Dst0Hst_D0gamma mean", 5068),
      sigmaBu2Dst0Hst_D0gamma_("sigmaBu2Dst0Hst_D0gamma_Pi0Pi",
                               "Pi0, Pi Bu2Dst0Hst_D0gamma sigma", 91.5),
      aBu2Dst0Hst_D0gamma_("aBu2Dst0Hst_D0gamma_Pi0Pi",
                           "Pi0, Pi Bu2Dst0Hst_D0gamma a", 1.0),
      nBu2Dst0Hst_D0gamma_("nBu2Dst0Hst_D0gamma_Pi0Pi",
                           "Pi0, Pi Bu2Dst0Hst_D0gamma n", 0.1),
      meanMissId1_("meanMissId1_Pi0Pi", "Pi0, Pi Miss ID mean", 5218.6),
      sigmaMissId1_("sigmaMissId1_Pi0Pi", "Pi0, Pi Miss ID sigma", 57.0),
      aMissId1_("aMissId1_Pi0Pi", "Pi0, Pi Miss ID a", -3.25),
      nMissId1_("nMissId1_Pi0Pi", "Pi0, Pi Miss ID n", 4.77),
      fracMissId1_("fracMissId1_Pi0Pi", "Pi0, Pi Miss ID fraction of PDF 1",
                   0.390),
      meanMissId2_(),
      sigmaMissId2_("sigmaMissId2_Pi0Pi", "Pi0, Pi Miss ID sigma", 20.8),
      aMissId2_("aMissId2_Pi0Pi", "Pi0, Pi Miss ID a", 0.50),
      nMissId2_("nMissId2_Pi0Pi", "Pi0, Pi Miss ID n", 1.68),
      signal_(new RooCruijff(
          "bu2Dst0H_D0pi0_Pi0Pi", "Pi0, Pi bu2Dst0H_D0pi0 Cruijff",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get().meanSignal(),
          *sigmaSignal_1_, *sigmaSignal_2_,
          NeutralVars<Neutral::pi0>::Get().aSignal_1(),
          NeutralVars<Neutral::pi0>::Get().aSignal_2())),
      crossFeed_(new RooCBShape(
          "bu2Dst0H_D0gamma_Pi0Pi", "Pi0, Pi bu2Dst0H_D0gamma CBShape",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get().meanCrossFeed(),
          *sigmaCrossFeed_1_,
          NeutralVars<Neutral::pi0>::Get().aCrossFeed_1(),
          NeutralVars<Neutral::pi0>::Get().aCrossFeed_2())),
      nonTmSignal_(
          new RooCruijff("nonTmSignal_pi0Pi", "pi0, Pi nonTmSignal RooCruijff ",
                         Configuration::Get().buMass(),
                         NeutralVars<Neutral::pi0>::Get().meanNonTmSignal(),
                         *sigmaNonTmSignal_1_, *sigmaNonTmSignal_2_,
                         NeutralVars<Neutral::pi0>::Get().aNonTmSignal_1(),
                         NeutralVars<Neutral::pi0>::Get().aNonTmSignal_2())),
      bu2Dst0Hst_D0pi0_(new RooCBShape(
          "bu2Dst0Hst_D0pi0_Pi0Pi", "Pi0, Pi bu2Dst0Hst_D0pi0 CBShape",
          Configuration::Get().buMass(), meanBu2Dst0Hst_D0pi0_,
          sigmaBu2Dst0Hst_D0pi0_, aBu2Dst0Hst_D0pi0_, nBu2Dst0Hst_D0pi0_)),
      bu2Dst0Hst_D0gamma_(new RooCBShape(
          "bu2Dst0Hst_D0gamma_Pi0Pi", "Pi0, Pi bu2Dst0Hst_D0gamma CBShape",
          Configuration::Get().buMass(), meanBu2Dst0Hst_D0gamma_,
          sigmaBu2Dst0Hst_D0gamma_, aBu2Dst0Hst_D0gamma_,
          nBu2Dst0Hst_D0gamma_)),
      bu2D0H_1_(new RooCBShape("bu2D0H_1_PiPi0", "Pi0, Pi bu2D0H CBShape 1",
                               Configuration::Get().buMass(),
                               NeutralVars<Neutral::pi0>::Get().meanBu2D0H_1(),
                               *sigmaBu2D0H_1_,
                               NeutralVars<Neutral::pi0>::Get().aBu2D0H_1(),
                               NeutralVars<Neutral::pi0>::Get().nBu2D0H_1())),
      bu2D0H_2_(new RooCBShape("bu2D0H_2_PiPi0", "Pi0, Pi bu2D0H CBShape2",
                               Configuration::Get().buMass(),
                               NeutralVars<Neutral::pi0>::Get().meanBu2D0H_2(),
                               *sigmaBu2D0H_2_,
                               NeutralVars<Neutral::pi0>::Get().aBu2D0H_2(),
                               NeutralVars<Neutral::pi0>::Get().nBu2D0H_2())),
      bu2D0H_(new RooAddPdf("bu2D0H_Pi0Pi", "Pi0, Pi bu2D0H RooAddPdf",
                            RooArgList(*bu2D0H_1_, *bu2D0H_2_),
                            NeutralVars<Neutral::pi0>::Get().fracBu2D0H_1())),
      bu2D0Hst_(new RooCBShape("bu2D0Hst_Pi0Pi", "Pi0, Pi bu2D0Hst CBShape",
                               Configuration::Get().buMass(),
                               NeutralVars<Neutral::pi0>::Get().meanBu2D0Hst(),
                               *sigmaBu2D0Hst_,
                               NeutralVars<Neutral::pi0>::Get().aBu2D0Hst(),
                               NeutralVars<Neutral::pi0>::Get().nBu2D0Hst())),
      bd2DstH_(new RooCruijff("bd2DstH_Pi0Pi", "Pi0, Pi bd2DstH_ CBShape",
                              Configuration::Get().buMass(),
                              NeutralVars<Neutral::pi0>::Get().meanBd2DstH(),
                              *sigmaBd2DstH_1_,*sigmaBd2DstH_2_,
                              NeutralVars<Neutral::pi0>::Get().aBd2DstH_1(),
                              NeutralVars<Neutral::pi0>::Get().aBd2DstH_2())),
      missId1_(new RooCBShape("missId1_Pi0Pi", "Pi0, Pi missId1 CBShape",
                              Configuration::Get().buMass(), meanMissId1_,
                              sigmaMissId1_, aMissId1_, nMissId1_)),
      missId2_(new RooCBShape("missId2_Pi0Pi", "Pi0, Pi missId2 CBShape",
                              Configuration::Get().buMass(), meanMissId1_,
                              sigmaMissId2_, aMissId2_, nMissId2_)),
      missId_(new RooAddPdf("missId_Pi0Pi", "Pi0, Pi missId AddPdf",
                            RooArgList(*missId1_, *missId2_), fracMissId1_)),
      bachelorSF_(1.0) {}

template <>
BachelorVars<Neutral::pi0, Bachelor::k>::BachelorVars()
    : bu2Dst0MissIdBR_("bu2Dst0MissIdBR", "Branching Ratio of Bu2Dst0pi",
                       0.00518),
      bu2Dst0HBR_("bu2Dst0HBR", "Branching Ratio of Bu2Dst0K", 0.000420),
      missIdRate_("missIdRate", "Rate of miss-ID with PIDK>12", 0.0035),
      bachEff_("bachEff", "Efficiency of detection of bachelor K with PIDK>12",
               0.6734),
      sigmaSignal_1_(new RooFormulaVar(
          "sigmaLeftBu2Dst0H_D0pi0_Pi0K", "Pi0, K Bu2Dst0H_D0pi0 sigma left",
          "@0*@1", RooArgList(BachelorVars<Neutral::pi0, Bachelor::pi>::Get()
                                  .sigmaSignal_1(),
                              Configuration::Get().relativeWidth()))),
      sigmaSignal_2_(new RooFormulaVar(
          "sigmaRightBu2Dst0H_D0pi0_Pi0K", "Pi0, K Bu2Dst0H_D0pi0 sigma right",
          "@0*@1", RooArgList(BachelorVars<Neutral::pi0, Bachelor::pi>::Get()
                                  .sigmaSignal_2(),
                              Configuration::Get().relativeWidth()))),
      sigmaCrossFeed_1_(new RooFormulaVar(
          "sigmaLeftBu2Dst0H_D0gamma_Pi0K",
          "Pi0, K Bu2Dst0H_D0gamma sigma left", "@0*@1",
          RooArgList(BachelorVars<Neutral::pi0, Bachelor::pi>::Get()
                         .sigmaCrossFeed_1(),
                     Configuration::Get().relativeWidth()))),
      // sigmaCrossFeed_2_(new RooFormulaVar(
      //     "sigmaRightBu2Dst0H_D0gamma_Pi0K",
      //     "Pi0, K Bu2Dst0H_D0gamma sigma right", "@0*@1",
      //     RooArgList(BachelorVars<Neutral::pi0, Bachelor::pi>::Get()
      //                    .sigmaCrossFeed_2(),
      //                Configuration::Get().relativeWidth()))),
      sigmaCrossFeed_2_(nullptr),
      sigmaNonTmSignal_1_(new RooFormulaVar(
          "sigmaNonTmSignal_1_Pi0K", "Pi0, K NonTmSignal sigma 1", "@0*@1",
          RooArgList(BachelorVars<Neutral::pi0, Bachelor::pi>::Get()
                         .sigmaNonTmSignal_1(),
                     Configuration::Get().relativeWidth()))),
      sigmaNonTmSignal_2_(new RooFormulaVar(
          "sigmaNonTmSignal_2_Pi0K", "Pi0, K NonTmSignal sigma 2", "@0*@1",
          RooArgList(BachelorVars<Neutral::pi0, Bachelor::pi>::Get()
                         .sigmaNonTmSignal_2(),
                     Configuration::Get().relativeWidth()))),
      sigmaBu2D0H_1_(new RooFormulaVar(
          "sigmaLeftBu2D0H_Pi0K", "Pi0, K Bu2D0H sigma left", "@0*@1",
          RooArgList(
              BachelorVars<Neutral::pi0, Bachelor::pi>::Get().sigmaBu2D0H_1(),
              Configuration::Get().relativeWidth()))),
      sigmaBu2D0H_2_(new RooFormulaVar(
          "sigmaRightBu2D0H_Pi0K", "Pi0, K Bu2D0H sigma right ", "@0*@1",
          RooArgList(
              BachelorVars<Neutral::pi0, Bachelor::pi>::Get().sigmaBu2D0H_2(),
              Configuration::Get().relativeWidth()))),
      sigmaBu2D0Hst_(new RooFormulaVar(
          "sigmaRightBu2D0Hst_Pi0K", "Pi0, K Bu2D0Hst sigma right", "@0*@1",
          RooArgList(
              BachelorVars<Neutral::pi0, Bachelor::pi>::Get().sigmaBu2D0Hst(),
              Configuration::Get().relativeWidth()))),
      sigmaBd2DstH_1_(new RooFormulaVar(
          "sigmaLeftBd2DstH_Pi0K", "Pi0, K Bd2DstH sigma left", "@0*@1",
          RooArgList(
              BachelorVars<Neutral::pi0, Bachelor::pi>::Get().sigmaBd2DstH_1(),
              Configuration::Get().relativeWidth()))),
      sigmaBd2DstH_2_(new RooFormulaVar(
          "sigmaRightBd2DstH_Pi0K", "Pi0, K Bd2DstH sigma right", "@0*@1",
          RooArgList(
              BachelorVars<Neutral::pi0, Bachelor::pi>::Get().sigmaBd2DstH_2(),
              Configuration::Get().relativeWidth()))),
      meanBu2Dst0Hst_D0pi0_("meanBu2Dst0Hst_D0pi0_Pi0K",
                            "Pi0, K Bu2Dst0Hst_D0pi0 mean", 5102),
      sigmaBu2Dst0Hst_D0pi0_("sigmaBu2Dst0Hst_D0pi0_Pi0K",
                             "Pi0, K Bu2Dst0Hst_D0pi0 sigma", 49.5),
      aBu2Dst0Hst_D0pi0_("aBu2Dst0Hst_D0pi0_Pi0K", "Pi0, K Bu2Dst0Hst_D0pi0 a",
                         0.23),
      nBu2Dst0Hst_D0pi0_("nBu2Dst0Hst_D0pi0_Pi0K", "Pi0, K Bu2Dst0Hst_D0pi0 n",
                         0.3),
      meanBu2Dst0Hst_D0gamma_("meanBu2Dst0Hst_D0gamma_Pi0K",
                              "Pi0, K Bu2Dst0Hst_D0gamma mean", 5051),
      sigmaBu2Dst0Hst_D0gamma_("sigmaBu2Dst0Hst_D0gamma_Pi0K",
                               "Pi0, K Bu2Dst0Hst_D0gamma sigma", 94.5),
      aBu2Dst0Hst_D0gamma_("aBu2Dst0Hst_D0gamma_Pi0K",
                           "Pi0, K Bu2Dst0Hst_D0gamma a", -2.26),
      nBu2Dst0Hst_D0gamma_("nBu2Dst0Hst_D0gamma_Pi0K",
                           "Pi0, K Bu2Dst0Hst_D0gamma n", 6.8),
      meanMissId1_("meanMissId1_Pi0K", "Pi0, K Miss ID mean 1", 5348.1),
      sigmaMissId1_("sigmaMissId1_Pi0K", "Pi0, K Miss ID sigma", 22.9),
      aMissId1_("aMissId1_Pi0K", "Pi0, K Miss ID a", -0.03),
      nMissId1_("nMissId1_Pi0K", "Pi0, K Miss ID n", 25.3),
      fracMissId1_("fracMissId1_Pi0K", "Pi0, K Miss ID fraction of PDF 1",
                   0.712),
      meanMissId2_("meanMissId2_Pi0K", "Pi0, K Miss ID mean 2", 5334.8),
      sigmaMissId2_("sigmaMissId2_Pi0K", "Pi0, K Miss ID sigma", 54.8),
      aMissId2_("aMissId2_Pi0K", "Pi0, K Miss ID a", 3.80),
      nMissId2_("nMissId2_Pi0K", "Pi0, K Miss ID n", 13.7),
      signal_(new RooCruijff(
          "bu2Dst0H_D0pi0_Pi0Pi", "Pi0, Pi bu2Dst0H_D0pi0 Cruijff",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get().meanSignal(),
          *sigmaSignal_1_, *sigmaSignal_2_,
          NeutralVars<Neutral::pi0>::Get().aSignal_1(),
          NeutralVars<Neutral::pi0>::Get().aSignal_2())),
      crossFeed_(new RooCBShape(
          "bu2Dst0H_D0gamma_Pi0K", "Pi0, K bu2Dst0H_D0gamma CBShape",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get().meanCrossFeed(),
          *sigmaCrossFeed_1_,
          NeutralVars<Neutral::pi0>::Get().aCrossFeed_1(),
          NeutralVars<Neutral::pi0>::Get().aCrossFeed_2())),
      nonTmSignal_(
          new RooCruijff("nonTmSignal_pi0Pi", "pi0, Pi nonTmSignal RooCruijff ",
                         Configuration::Get().buMass(),
                         NeutralVars<Neutral::pi0>::Get().meanNonTmSignal(),
                         *sigmaNonTmSignal_1_, *sigmaNonTmSignal_2_,
                         NeutralVars<Neutral::pi0>::Get().aNonTmSignal_1(),
                         NeutralVars<Neutral::pi0>::Get().aNonTmSignal_2())),
      bu2Dst0Hst_D0pi0_(new RooCBShape(
          "bu2Dst0Hst_D0pi0_Pi0K", "Pi0, K bu2Dst0Hst_D0pi0 CBShape",
          Configuration::Get().buMass(), meanBu2Dst0Hst_D0pi0_,
          sigmaBu2Dst0Hst_D0pi0_, aBu2Dst0Hst_D0pi0_, nBu2Dst0Hst_D0pi0_)),
      bu2Dst0Hst_D0gamma_(new RooCBShape(
          "bu2Dst0Hst_D0gamma_Pi0K", "Pi0, K bu2Dst0Hst_D0gamma CBShape",
          Configuration::Get().buMass(), meanBu2Dst0Hst_D0gamma_,
          sigmaBu2Dst0Hst_D0gamma_, aBu2Dst0Hst_D0gamma_,
          nBu2Dst0Hst_D0gamma_)),
      bu2D0H_1_(new RooCBShape("bu2D0H_1_KPi0", "Pi0, K bu2D0H CBShape 1",
                               Configuration::Get().buMass(),
                               NeutralVars<Neutral::pi0>::Get().meanBu2D0H_1(),
                               *sigmaBu2D0H_1_,
                               NeutralVars<Neutral::pi0>::Get().aBu2D0H_1(),
                               NeutralVars<Neutral::pi0>::Get().nBu2D0H_1())),
      bu2D0H_2_(new RooCBShape("bu2D0H_2_KPi0", "Pi0, K bu2D0H CBShape2",
                               Configuration::Get().buMass(),
                               NeutralVars<Neutral::pi0>::Get().meanBu2D0H_2(),
                               *sigmaBu2D0H_2_,
                               NeutralVars<Neutral::pi0>::Get().aBu2D0H_2(),
                               NeutralVars<Neutral::pi0>::Get().nBu2D0H_2())),
      bu2D0H_(new RooAddPdf("bu2D0H_Pi0K", "Pi0, K bu2D0H RooAddPdf",
                            RooArgList(*bu2D0H_1_, *bu2D0H_2_),
                            NeutralVars<Neutral::pi0>::Get().fracBu2D0H_1())),
      bu2D0Hst_(new RooCBShape("bu2D0Hst_Pi0K", "Pi0, K bu2D0Hst CBShape",
                               Configuration::Get().buMass(),
                               NeutralVars<Neutral::pi0>::Get().meanBu2D0Hst(),
                               *sigmaBu2D0Hst_,
                               NeutralVars<Neutral::pi0>::Get().aBu2D0Hst(),
                               NeutralVars<Neutral::pi0>::Get().nBu2D0Hst())),
      bd2DstH_(new RooCruijff("bd2DstH_Pi0K", "Pi0, K bd2DstH_ CBShape",
                              Configuration::Get().buMass(),
                              NeutralVars<Neutral::pi0>::Get().meanBd2DstH(),
                              *sigmaBd2DstH_1_,*sigmaBd2DstH_2_,
                              NeutralVars<Neutral::pi0>::Get().aBd2DstH_1(),
                              NeutralVars<Neutral::pi0>::Get().aBd2DstH_2())),
      missId1_(new RooCBShape("missId1_Pi0K", "Pi0, K missId1 CBShape",
                              Configuration::Get().buMass(), meanMissId1_,
                              sigmaMissId1_, aMissId1_, nMissId1_)),
      missId2_(new RooCBShape("missId2_Pi0K", "Pi0, K missId2 CBShape",
                              Configuration::Get().buMass(), meanMissId2_,
                              sigmaMissId2_, aMissId2_, nMissId2_)),
      missId_(new RooAddPdf("missId_Pi0K", "Pi0, K missId AddPdf",
                            RooArgList(*missId1_, *missId2_), fracMissId1_)),
      bachelorSF_(0.08) {}

