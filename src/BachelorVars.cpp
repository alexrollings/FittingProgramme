#include "BachelorVars.h"
#include "Configuration.h"
#include "NeutralVars.h"
#include "RooBifurGauss.h"
#include "RooCBShape.h"
#include "RooGaussian.h"
#include "RooPolynomial.h"

// Bachelor specializations

template <>
BachelorVars<Neutral::gamma, Bachelor::pi>::BachelorVars()
    : sigmaBu2Dst0H_D0pi0_("sigmaBu2Dst0H_D0pi0_GammaPi",
                           "Gamma, Pi Bu2Dst0H_D0pi0 sigma", 80.2),
      sigmaBu2Dst0H_D0gamma_1_("sigmaLeftBu2Dst0H_D0gamma_GammaPi",
                               "Gamma, Pi Bu2Dst0H_D0gamma sigma left", 23),
      sigmaBu2Dst0H_D0gamma_2_("sigmaRightBu2Dst0H_D0gamma_GammaPi",
                               "Gamma, Pi Bu2Dst0H_D0gamma sigma right", 25),
      sigmaNonTmSignal_1_("sigmaNonTmSignal_1_GammaPi",
                          "Gamma, Pi NonTmSignal sigma 1", 86.8),
      sigmaNonTmSignal_2_("sigmaNonTmSignal_2_GammaPi",
                          "Gamma, Pi NonTmSignal sigma 2", 29.1),
      sigmaBu2D0H_1_("sigmaLeftBu2D0H_GammaPi", "Gamma, Pi Bu2D0H sigma left",
                     51.0),
      sigmaBu2D0H_2_("sigmaRightBu2D0H_GammaPi", "Gamma, Pi Bu2D0H sigma right",
                     93.6),
      sigmaBu2D0Hst_("sigmaRightBu2D0Hst_GammaPi",
                     "Gamma, Pi Bu2D0Hst sigma right", 87.0),
      sigmaBd2DstH_("sigmaRightBd2DstH_GammaPi",
                    "Gamma, Pi Bd2DstH sigma right", 82.7),
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
      bu2Dst0H_D0pi0_(new RooCBShape(
          "bu2Dst0H_D0pi0_GammaPi", "Gamma, Pi bu2Dst0H_D0pi0 CBShape",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanBu2Dst0H_D0pi0(),
          sigmaBu2Dst0H_D0pi0_,
          NeutralVars<Neutral::gamma>::Get().aBu2Dst0H_D0pi0(),
          NeutralVars<Neutral::gamma>::Get().nBu2Dst0H_D0pi0())),
      bu2Dst0H_D0gamma_(new RooBifurGauss(
          "bu2Dst0H_D0gamma_GammaPi", "Gamma, Pi bu2Dst0H_D0gamma BifurGauss",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanBu2Dst0H_D0gamma(),
          sigmaBu2Dst0H_D0gamma_1_, sigmaBu2Dst0H_D0gamma_2_)),
      nonTmSignal_1_(new RooCBShape(
          "nonTmSignal_1_GammaPi", "Gamma, Pi nonTmSignal_1 CBShape",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanNonTmSignal(),
          sigmaNonTmSignal_1_,
          NeutralVars<Neutral::gamma>::Get().aNonTmSignal_1(),
          NeutralVars<Neutral::gamma>::Get().nNonTmSignal_1())),
      nonTmSignal_2_(new RooCBShape(
          "nonTmSignal_2_GammaPi", "Gamma, Pi nonTmSignal_2 CBShape",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanNonTmSignal(),
          sigmaNonTmSignal_2_,
          NeutralVars<Neutral::gamma>::Get().aNonTmSignal_2(),
          NeutralVars<Neutral::gamma>::Get().nNonTmSignal_2())),
      nonTmSignal_(new RooAddPdf(
          "nonTmSignal_GammaPi", "Gamma, Pi nonTmSignal AddPdf ",
          RooArgList(*nonTmSignal_1_, *nonTmSignal_2_),
          NeutralVars<Neutral::gamma>::Get().fracNonTmSignal_1())),
      bu2Dst0Hst_D0pi0_(new RooCBShape(
          "bu2Dst0Hst_D0pi0_GammaPi", "Gamma, Pi bu2Dst0Hst_D0pi0 CBShape",
          Configuration::Get().buMass(), meanBu2Dst0Hst_D0pi0_,
          sigmaBu2Dst0Hst_D0pi0_, aBu2Dst0Hst_D0pi0_, nBu2Dst0Hst_D0pi0_)),
      bu2Dst0Hst_D0gamma_(new RooCBShape(
          "bu2Dst0Hst_D0gamma_GammaPi", "Gamma, Pi bu2Dst0Hst_D0gamma CBShape",
          Configuration::Get().buMass(), meanBu2Dst0Hst_D0gamma_,
          sigmaBu2Dst0Hst_D0gamma_, aBu2Dst0Hst_D0gamma_,
          nBu2Dst0Hst_D0gamma_)),
      bu2D0H_(new RooBifurGauss("bu2D0H_GammaPi",
                                "Gamma, Pi bu2Dst0H_D0gamma BifurGauss ",
                                Configuration::Get().buMass(),
                                NeutralVars<Neutral::gamma>::Get().meanBu2D0H(),
                                sigmaBu2D0H_1_, sigmaBu2D0H_2_)),
      bu2D0Hst_(new RooCBShape(
          "bu2D0Hst_GammaPi", "Gamma, Pi bu2D0Hst CBShape",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanBu2D0Hst(), sigmaBu2D0Hst_,
          NeutralVars<Neutral::gamma>::Get().aBu2D0Hst(),
          NeutralVars<Neutral::gamma>::Get().nBu2D0Hst())),
      bd2DstH_(new RooCBShape("bd2DstH_GammaPi", "Gamma, Pi bd2DstH_ CBShape",
                              Configuration::Get().buMass(),
                              NeutralVars<Neutral::gamma>::Get().meanBd2DstH(),
                              sigmaBd2DstH_,
                              NeutralVars<Neutral::gamma>::Get().aBd2DstH(),
                              NeutralVars<Neutral::gamma>::Get().nBd2DstH())),
      missId1_(new RooCBShape("missId1_GammaPi", "Gamma, Pi missId1 CBShape",
                              Configuration::Get().buMass(), meanMissId1_,
                              sigmaMissId1_, aMissId1_, nMissId1_)),
      missId2_(new RooCBShape("missId2_GammaPi", "Gamma, Pi missId2 CBShape",
                              Configuration::Get().buMass(), meanMissId1_,
                              sigmaMissId2_, aMissId2_, nMissId2_)),
      missId_(new RooAddPdf("missId_GammaPi", "Gamma, Pi missId AddPdf",
                            RooArgList(*missId1_, *missId2_), fracMissId1_)) {}

template <>
BachelorVars<Neutral::gamma, Bachelor::k>::BachelorVars()
    : sigmaBu2Dst0H_D0pi0_("sigmaBu2Dst0H_D0pi0_GammaK",
                           "Gamma, K Bu2Dst0H_D0pi0 sigma", 80.2 * 0.95),
      sigmaBu2Dst0H_D0gamma_1_("sigmaLeftBu2Dst0H_D0gamma_GammaK",
                               "Gamma, K Bu2Dst0H_D0gamma sigma left",
                               23 * 0.95),
      sigmaBu2Dst0H_D0gamma_2_("sigmaRightBu2Dst0H_D0gamma_GammaK",
                               "Gamma, K Bu2Dst0H_D0gamma sigma right",
                               25 * 0.95),
      sigmaNonTmSignal_1_("sigmaNonTmSignal_1_GammaK",
                          "Gamma, K NonTmSignal sigma 1", 86.8 * 0.95),
      sigmaNonTmSignal_2_("sigmaNonTmSignal_2_GammaK",
                          "Gamma, K NonTmSignal sigma 2", 29.1 * 0.95),
      sigmaBu2D0H_1_("sigmaLeftBu2D0H_GammaK", "Gamma, K Bu2D0H sigma left",
                     51.0 * 0.95),
      sigmaBu2D0H_2_("sigmaRightBu2D0H_GammaK", "Gamma, K Bu2D0H sigma right ",
                     93.6 * 0.95),
      sigmaBu2D0Hst_("sigmaRightBu2D0Hst_GammaK",
                     "Gamma, K Bu2D0Hst sigma right", 87.0 * 0.95),
      sigmaBd2DstH_("sigmaRightBd2DstH_GammaK", "Gamma, K Bd2DstH sigma right",
                    82.7 * 0.95),
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
      bu2Dst0H_D0pi0_(new RooCBShape(
          "bu2Dst0H_D0pi0_GammaK", "Gamma, K bu2Dst0H_D0pi0 CBShape",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanBu2Dst0H_D0pi0(),
          sigmaBu2Dst0H_D0pi0_,
          NeutralVars<Neutral::gamma>::Get().aBu2Dst0H_D0pi0(),
          NeutralVars<Neutral::gamma>::Get().nBu2Dst0H_D0pi0())),
      bu2Dst0H_D0gamma_(new RooBifurGauss(
          "bu2Dst0H_D0gamma_GammaK", "Gamma, K bu2Dst0H_D0gamma BifurGauss ",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanBu2Dst0H_D0gamma(),
          sigmaBu2Dst0H_D0gamma_1_, sigmaBu2Dst0H_D0gamma_2_)),
      nonTmSignal_1_(new RooCBShape(
          "nonTmSignal_1_GammaK", "Gamma, K nonTmSignal_1 CBShape",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanNonTmSignal(),
          sigmaNonTmSignal_1_,
          NeutralVars<Neutral::gamma>::Get().aNonTmSignal_1(),
          NeutralVars<Neutral::gamma>::Get().nNonTmSignal_1())),
      nonTmSignal_2_(new RooCBShape(
          "nonTmSignal_2_GammaK", "Gamma, K nonTmSignal_2 CBShape",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanNonTmSignal(),
          sigmaNonTmSignal_2_,
          NeutralVars<Neutral::gamma>::Get().aNonTmSignal_2(),
          NeutralVars<Neutral::gamma>::Get().nNonTmSignal_2())),
      nonTmSignal_(new RooAddPdf(
          "nonTmSignal_GammaK", "Gamma, K nonTmSignal AddPdf ",
          RooArgList(*nonTmSignal_1_, *nonTmSignal_2_),
          NeutralVars<Neutral::gamma>::Get().fracNonTmSignal_1())),
      bu2Dst0Hst_D0pi0_(new RooGaussian(
          "bu2Dst0Hst_D0pi0_GammaK", "Gamma, K bu2Dst0Hst_D0pi0 CBShape",
          Configuration::Get().buMass(), meanBu2Dst0Hst_D0pi0_,
          sigmaBu2Dst0Hst_D0pi0_)),
      bu2Dst0Hst_D0gamma_(new RooCBShape(
          "bu2Dst0Hst_D0gamma_GammaK", "Gamma, K bu2Dst0Hst_D0gamma CBShape",
          Configuration::Get().buMass(), meanBu2Dst0Hst_D0gamma_,
          sigmaBu2Dst0Hst_D0gamma_, aBu2Dst0Hst_D0gamma_,
          nBu2Dst0Hst_D0gamma_)),
      bu2D0H_(new RooBifurGauss("bu2D0H_GammaK",
                                "Gamma, K bu2Dst0H_D0gamma BifurGauss",
                                Configuration::Get().buMass(),
                                NeutralVars<Neutral::gamma>::Get().meanBu2D0H(),
                                sigmaBu2D0H_1_, sigmaBu2D0H_2_)),
      bu2D0Hst_(new RooCBShape(
          "bu2D0Hst_GammaK", "Gamma, K bu2D0Hst CBShape",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanBu2D0Hst(), sigmaBu2D0Hst_,
          NeutralVars<Neutral::gamma>::Get().aBu2D0Hst(),
          NeutralVars<Neutral::gamma>::Get().nBu2D0Hst())),
      bd2DstH_(new RooCBShape("bd2DstH_GammaK", "Gamma, K bd2DstH_ CBShape",
                              Configuration::Get().buMass(),
                              NeutralVars<Neutral::gamma>::Get().meanBd2DstH(),
                              sigmaBd2DstH_,
                              NeutralVars<Neutral::gamma>::Get().aBd2DstH(),
                              NeutralVars<Neutral::gamma>::Get().nBd2DstH())),
      missId1_(new RooCBShape("missId1_GammaK", "Gamma, K missId1 CBShape",
                              Configuration::Get().buMass(), meanMissId1_,
                              sigmaMissId1_, aMissId1_, nMissId1_)),
      missId2_(new RooCBShape("missId2_GammaK", "Gamma, K missId2 CBShape",
                              Configuration::Get().buMass(), meanMissId1_,
                              sigmaMissId2_, aMissId2_, nMissId2_)),
      missId_(new RooAddPdf("missId_GammaK", "Gamma, K missId AddPdf",
                            RooArgList(*missId1_, *missId2_), fracMissId1_)) {}

template <>
BachelorVars<Neutral::pi0, Bachelor::pi>::BachelorVars()
    : sigmaBu2Dst0H_D0pi0_("sigmaBu2Dst0H_D0pi0_Pi0Pi",
                           "Pi0, Pi Bu2Dst0H_D0pi0 sigma", 17),
      sigmaBu2Dst0H_D0gamma_1_("sigmaBu2Dst0H_D0gamma_Pi0Pi",
                               "Pi0, Pi Bu2Dst0H_D0gamma sigma", 80),
      sigmaBu2Dst0H_D0gamma_2_(),
      sigmaNonTmSignal_1_("sigmaLeftNonTmSignal_Pi0Pi",
                          "Pi0, Pi NonTmSignal sigma left", 52.6),
      sigmaNonTmSignal_2_("sigmaRightNonTmSignal_Pi0Pi",
                          "Pi0, Pi NonTmSignal sigma right", 49.4),
      sigmaBu2D0H_1_("sigmaLeftBu2D0H_Pi0Pi", "Pi0, Pi Bu2D0H sigma left",
                     35.7),
      sigmaBu2D0H_2_("sigmaRightBu2D0H_Pi0Pi", "Pi0, Pi Bu2D0H sigma right",
                     46.7),
      sigmaBu2D0Hst_("sigmaRightBu2D0Hst_Pi0Pi", "Pi0, Pi Bu2D0Hst sigma right",
                     51.9),
      sigmaBd2DstH_("sigmaRightBd2DstH_Pi0Pi", "Pi0, Pi Bd2DstH sigma right",
                    54.3),
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
      bu2Dst0H_D0pi0_(new RooCBShape(
          "bu2Dst0H_D0pi0_Pi0Pi", "Pi0, Pi bu2Dst0H_D0pi0 CBShape",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get().meanBu2Dst0H_D0pi0(),
          sigmaBu2Dst0H_D0pi0_,
          NeutralVars<Neutral::pi0>::Get().aBu2Dst0H_D0pi0(),
          NeutralVars<Neutral::pi0>::Get().nBu2Dst0H_D0pi0())),
      bu2Dst0H_D0gamma_(new RooCBShape(
          "bu2Dst0H_D0gamma_Pi0Pi", "Pi0, Pi bu2Dst0H_D0gamma CBShape",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get().meanBu2Dst0H_D0gamma(),
          sigmaBu2Dst0H_D0gamma_1_,
          NeutralVars<Neutral::pi0>::Get().aBu2Dst0H_D0gamma(),
          NeutralVars<Neutral::pi0>::Get().nBu2Dst0H_D0gamma())),
      nonTmSignal_1_(new RooCBShape()), nonTmSignal_2_(new RooCBShape()),
      nonTmSignal_(new RooBifurGauss(
          "nonTmSignal_Pi0Pi", "Pi0, Pi nonTmSignal BifurGauss",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get().meanNonTmSignal(),
          sigmaNonTmSignal_1_, sigmaNonTmSignal_2_)),
      bu2Dst0Hst_D0pi0_(new RooCBShape(
          "bu2Dst0Hst_D0pi0_Pi0Pi", "Pi0, Pi bu2Dst0Hst_D0pi0 CBShape",
          Configuration::Get().buMass(), meanBu2Dst0Hst_D0pi0_,
          sigmaBu2Dst0Hst_D0pi0_, aBu2Dst0Hst_D0pi0_, nBu2Dst0Hst_D0pi0_)),
      bu2Dst0Hst_D0gamma_(new RooCBShape(
          "bu2Dst0Hst_D0gamma_Pi0Pi", "Pi0, Pi bu2Dst0Hst_D0gamma CBShape",
          Configuration::Get().buMass(), meanBu2Dst0Hst_D0gamma_,
          sigmaBu2Dst0Hst_D0gamma_, aBu2Dst0Hst_D0gamma_,
          nBu2Dst0Hst_D0gamma_)),
      bu2D0H_(new RooBifurGauss("bu2D0H_Pi0Pi",
                                "Pi0, Pi bu2Dst0H_D0gamma BifurGauss",
                                Configuration::Get().buMass(),
                                NeutralVars<Neutral::pi0>::Get().meanBu2D0H(),
                                sigmaBu2D0H_1_, sigmaBu2D0H_2_)),
      bu2D0Hst_(new RooCBShape("bu2D0Hst_Pi0Pi", "Pi0, Pi bu2D0Hst CBShape",
                               Configuration::Get().buMass(),
                               NeutralVars<Neutral::pi0>::Get().meanBu2D0Hst(),
                               sigmaBu2D0Hst_,
                               NeutralVars<Neutral::pi0>::Get().aBu2D0Hst(),
                               NeutralVars<Neutral::pi0>::Get().nBu2D0Hst())),
      bd2DstH_(new RooCBShape("bd2DstH_Pi0Pi", "Pi0, Pi bd2DstH_ CBShape",
                              Configuration::Get().buMass(),
                              NeutralVars<Neutral::pi0>::Get().meanBd2DstH(),
                              sigmaBd2DstH_,
                              NeutralVars<Neutral::pi0>::Get().aBd2DstH(),
                              NeutralVars<Neutral::pi0>::Get().nBd2DstH())),
      missId1_(new RooCBShape("missId1_Pi0Pi", "Pi0, Pi missId1 CBShape",
                              Configuration::Get().buMass(), meanMissId1_,
                              sigmaMissId1_, aMissId1_, nMissId1_)),
      missId2_(new RooCBShape("missId2_Pi0Pi", "Pi0, Pi missId2 CBShape",
                              Configuration::Get().buMass(), meanMissId1_,
                              sigmaMissId2_, aMissId2_, nMissId2_)),
      missId_(new RooAddPdf("missId_Pi0Pi", "Pi0, Pi missId AddPdf",
                            RooArgList(*missId1_, *missId2_), fracMissId1_)) {}

template <>
BachelorVars<Neutral::pi0, Bachelor::k>::BachelorVars()
    : sigmaBu2Dst0H_D0pi0_("sigmaBu2Dst0H_D0pi0_Pi0K",
                           "Pi0, K Bu2Dst0H_D0pi0 sigma", 17 * 0.95),
      sigmaBu2Dst0H_D0gamma_1_("sigmaBu2Dst0H_D0gamma_Pi0K",
                               "Pi0, K Bu2Dst0H_D0gamma sigma", 80 * 0.95),
      sigmaBu2Dst0H_D0gamma_2_(),
      sigmaNonTmSignal_1_("sigmaLeftNonTmSignal_Pi0K",
                          "Pi0, K NonTmSignal sigma left", 52.6 * 0.95),
      sigmaNonTmSignal_2_("sigmaRightNonTmSignal_Pi0K",
                          "Pi0, K NonTmSignal sigma right", 49.4 * 0.95),
      sigmaBu2D0H_1_("sigmaLeftBu2D0H_Pi0K", "Pi0, K Bu2D0H sigma left",
                     35.7 * 0.95),
      sigmaBu2D0H_2_("sigmaRightBu2D0H_Pi0K", "Pi0, K Bu2D0H sigma right",
                     46.7 * 0.95),
      sigmaBu2D0Hst_("sigmaRightBu2D0Hst_Pi0K", "Pi0, K Bu2D0Hst sigma right",
                     51.9 * 0.95),
      sigmaBd2DstH_("sigmaRightBd2DstH_Pi0K", "Pi0, K Bd2DstH sigma right",
                    54.3 * 0.95),
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
      aMissId1_("aMissId1_Pi0K", "Pi0, K Miss ID a", -0.33),
      nMissId1_("nMissId1_Pi0K", "Pi0, K Miss ID n", 25.3),
      fracMissId1_("fracMissId1_Pi0K", "Pi0, K Miss ID fraction of PDF 1",
                   0.712),
      meanMissId2_("meanMissId2_Pi0K", "Pi0, K Miss ID mean 2", 5334.8),
      sigmaMissId2_("sigmaMissId2_Pi0K", "Pi0, K Miss ID sigma", 22.9),
      aMissId2_("aMissId2_Pi0K", "Pi0, K Miss ID a", 3.80),
      nMissId2_("nMissId2_Pi0K", "Pi0, K Miss ID n", 13.7),
      bu2Dst0H_D0pi0_(
          new RooCBShape("bu2Dst0H_D0pi0_Pi0K", "Pi0, K bu2Dst0H_D0pi0 CBShape",
                         Configuration::Get().buMass(),
                         NeutralVars<Neutral::pi0>::Get().meanBu2Dst0H_D0pi0(),
                         sigmaBu2Dst0H_D0pi0_,
                         NeutralVars<Neutral::pi0>::Get().aBu2Dst0H_D0pi0(),
                         NeutralVars<Neutral::pi0>::Get().nBu2Dst0H_D0pi0())),
      bu2Dst0H_D0gamma_(new RooCBShape(
          "bu2Dst0H_D0gamma_Pi0K", "Pi0, K bu2Dst0H_D0gamma CBShape",
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get().meanBu2Dst0H_D0gamma(),
          sigmaBu2Dst0H_D0gamma_1_,
          NeutralVars<Neutral::pi0>::Get().aBu2Dst0H_D0gamma(),
          NeutralVars<Neutral::pi0>::Get().nBu2Dst0H_D0gamma())),
      nonTmSignal_1_(new RooCBShape()), nonTmSignal_2_(new RooCBShape()),
      nonTmSignal_(
          new RooBifurGauss("nonTmSignal_Pi0K", "Pi0, K nonTmSignal BifurGauss",
                            Configuration::Get().buMass(),
                            NeutralVars<Neutral::pi0>::Get().meanNonTmSignal(),
                            sigmaNonTmSignal_1_, sigmaNonTmSignal_2_)),
      bu2Dst0Hst_D0pi0_(new RooCBShape(
          "bu2Dst0Hst_D0pi0_Pi0K", "Pi0, K bu2Dst0Hst_D0pi0 CBShape",
          Configuration::Get().buMass(), meanBu2Dst0Hst_D0pi0_,
          sigmaBu2Dst0Hst_D0pi0_, aBu2Dst0Hst_D0pi0_, nBu2Dst0Hst_D0pi0_)),
      bu2Dst0Hst_D0gamma_(new RooCBShape(
          "bu2Dst0Hst_D0gamma_Pi0K", "Pi0, K bu2Dst0Hst_D0gamma CBShape",
          Configuration::Get().buMass(), meanBu2Dst0Hst_D0gamma_,
          sigmaBu2Dst0Hst_D0gamma_, aBu2Dst0Hst_D0gamma_,
          nBu2Dst0Hst_D0gamma_)),
      bu2D0H_(new RooBifurGauss("bu2D0H_Pi0K",
                                "Pi0, K bu2Dst0H_D0gamma BifurGauss",
                                Configuration::Get().buMass(),
                                NeutralVars<Neutral::pi0>::Get().meanBu2D0H(),
                                sigmaBu2D0H_1_, sigmaBu2D0H_2_)),
      bu2D0Hst_(new RooCBShape("bu2D0Hst_Pi0K", "Pi0, K bu2D0Hst CBShape",
                               Configuration::Get().buMass(),
                               NeutralVars<Neutral::pi0>::Get().meanBu2D0Hst(),
                               sigmaBu2D0Hst_,
                               NeutralVars<Neutral::pi0>::Get().aBu2D0Hst(),
                               NeutralVars<Neutral::pi0>::Get().nBu2D0Hst())),
      bd2DstH_(new RooCBShape("bd2DstH_Pi0K", "Pi0, K bd2DstH_ CBShape",
                              Configuration::Get().buMass(),
                              NeutralVars<Neutral::pi0>::Get().meanBd2DstH(),
                              sigmaBd2DstH_,
                              NeutralVars<Neutral::pi0>::Get().aBd2DstH(),
                              NeutralVars<Neutral::pi0>::Get().nBd2DstH())),
      missId1_(new RooCBShape("missId1_Pi0K", "Pi0, K missId1 CBShape",
                              Configuration::Get().buMass(), meanMissId1_,
                              sigmaMissId1_, aMissId1_, nMissId1_)),
      missId2_(new RooCBShape("missId2_Pi0K", "Pi0, K missId2 CBShape",
                              Configuration::Get().buMass(), meanMissId1_,
                              sigmaMissId2_, aMissId2_, nMissId2_)),
      missId_(new RooAddPdf("missId_Pi0K", "Pi0, K missId AddPdf",
                            RooArgList(*missId1_, *missId2_), fracMissId1_)) {}

