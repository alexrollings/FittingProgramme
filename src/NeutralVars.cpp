#include "NeutralVars.h"
#include "Configuration.h"

// Neutral specializations

template <>
NeutralVars<Neutral::gamma>::NeutralVars()
    : meanBu2Dst0H_D0pi0_("meanBu2Dst0H_D0pi0_Gamma",
                          "Gamma Bu2Dst0H_D0pi0 mean", 5266.5),
      aBu2Dst0H_D0pi0_("aBu2Dst0H_D0pi0_Gamma", "Gamma Bu2Dst0H_D0pi0 a", 3.17),
      nBu2Dst0H_D0pi0_("nBu2Dst0H_D0pi0_Gamma", "Gamma Bu2Dst0H_D0pi0 n", 0.5),
      meanBu2Dst0H_D0gamma_("meanBu2Dst0H_D0gamma_Gamma",
                            "Gamma Bu2Dst0H_D0gamma mean", 5281, 5277, 5285),
      aBu2Dst0H_D0gamma_(), // Construct empty unused variables??
      nBu2Dst0H_D0gamma_(),
      meanNonTmSignal_("meanNonTmSignal_Gamma", "Gamma NonTmSignal mean",
                       5284.8),
      aNonTmSignal_1_("aNonTmSignal_1_Gamma", "Gamma NonTmSignal_1 a", -1.27),
      nNonTmSignal_1_("nNonTmSignal_1_Gamma", "Gamma NonTmSignal_1 n", 10.0),
      fracNonTmSignal_1_("fracNonTmSignal_1_Gamma",
                         "Gamma NonTmSignal fraction of first CBShape", 0.81),
      aNonTmSignal_2_("aNonTmSignal_2_Gamma", "Gamma NonTmSignal_2 a", 1.92),
      nNonTmSignal_2_("nNonTmSignal_2_Gamma", "Gamma NonTmSignal_2 n", 0),
      meanBu2D0H_("meanBu2D0H_Gamma", "Gamma Bu20H mean", 5430),
      meanBu2D0Hst_("meanBu2D0Hst_Gamma", "Gamma Bu2D0Hst mean", 5221.7),
      aBu2D0Hst_("aBu2D0Hst_Gamma", "Gamma Bu2D0Hst a", 1.58),
      nBu2D0Hst_("nBu2D0Hst_Gamma", "Gamma Bu2D0Hst n", 2.8),
      meanBd2DstH_("meanBd2DstH_Gamma", "Gamma Bd2DstH mean", 5257.0),
      aBd2DstH_("aBd2DstH_Gamma", "Gamma Bd2DstH a", 3.9),
      nBd2DstH_("nBd2DstH_Gamma", "Gamma Bd2DstH n", 2.7),
      nonTmRatio_("nonTmRatio_Gamma", "Ratio of non TM .w.r.t TM signal, Gamma", 1, 0, 5) {}

template <>
NeutralVars<Neutral::pi0>::NeutralVars()
    : meanBu2Dst0H_D0pi0_("meanBu2Dst0H_D0pi0_Pi0", "Pi0 Bu2Dst0H_D0pi0 mean",
                          5279, 5275, 5385),
      aBu2Dst0H_D0pi0_("aBu2Dst0H_D0pi0_Pi0", "Pi0 Bu2Dst0H_D0pi0 a", 2.13),
      nBu2Dst0H_D0pi0_("nBu2Dst0H_D0pi0_Pi0", "Pi0 Bu2Dst0H_D0pi0 n", 2.37),
      meanBu2Dst0H_D0gamma_("meanBu2Dst0H_D0gamma_Pi0",
                            "Pi0 Bu2Dst0H_D0gamma mean", 5283),
      aBu2Dst0H_D0gamma_("aBu2Dst0H_D0gamma_Pi0", "Pi0 Bu2Dst0H_D0gamma a",
                         3.5),
      nBu2Dst0H_D0gamma_("nBu2Dst0H_D0gamma_Pi0", "Pi0 Bu2Dst0H_D0gamma n",
                         2.8),
      meanNonTmSignal_("meanNonTmSignal_Pi0", "Pi0 NonTmSignal mean", 5284.8),
      aNonTmSignal_1_(), nNonTmSignal_1_(),
      fracNonTmSignal_1_(), aNonTmSignal_2_(),
      nNonTmSignal_2_(),
      meanBu2D0H_("meanBu2D0H_Pi0", "Pi0 Bu20H mean", 5492),
      meanBu2D0Hst_("meanBu2D0Hst_Pi0", "Pi0 Bu2D0Hst mean", 5304),
      aBu2D0Hst_("aBu2D0Hst_Pi0", "Pi0 Bu2D0Hst a", 0.33),
      nBu2D0Hst_("nBu2D0Hst_Pi0", "Pi0 Bu2D0Hst n", 5.0),
      meanBd2DstH_("meanBd2DstH_Pi0", "Pi0 Bd2DstH mean", 5277.6),
      aBd2DstH_("aBd2DstH_Pi0", "Pi0 Bd2DstH a", 4.0),
      nBd2DstH_("nBd2DstH_Pi0", "Pi0 Bd2DstH n", 6.1),
      nonTmRatio_("nonTmRatio_Pi0", "Ratio of non TM .w.r.t TM signal, Pi0", 1, 0, 5) {}



