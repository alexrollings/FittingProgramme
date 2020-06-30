 #include "GlobalVars.h"

GlobalVars::GlobalVars(int uniqueId)
    : uniqueId_(uniqueId),
      // pidEffPi_(Params::Get().CreateFixed(
      //     "pidEffPi", 0.996, 3e-03, Systematic::pidEffPi, Sign::positive)),
      pidEffPi_(
          Params::Get().CreateFloating("pidEffPi", uniqueId_, 0.996, 0.5, 1.5)),
      // Run 1 = 5.34 +/- 0.27 e-05, Run2 = 10.16 +/- 0.37 e-05
      crossFeedRate_(Params::Get().CreateFixed(
          "crossFeedRate", uniqueId_, 8.53e-05, 0.26e-05,
          Systematic::crossFeedRate, Sign::positive)),
      A_FAV_(Params::Get().CreateFixed("A_FAV", uniqueId_, 0, 0.05,
                                       Systematic::A_FAV, Sign::none)),
      A_Kpi_(Params::Get().CreateFixed("A_Kpi", uniqueId_, -1.13e-02, 1.5e-03,
                                       Systematic::A_Kpi, Sign::none)),
      A_pi_(Params::Get().CreateFixed("A_pi", uniqueId_, -6.45e-04, 1.84e-04,
                                      Systematic::A_pi, Sign::none)),
      Delta_A_CP_(Params::Get().CreateFixed("Delta_A_CP", uniqueId_, -1.54e-03,
                                            2.9e-04, Systematic::Delta_A_CP,
                                            Sign::none)) {}
