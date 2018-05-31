#include "NeutralVars.h"
#include "GlobalVars.h"

// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::gamma>::NeutralVars(int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : meanDelta_Bu2Dst0h_Dst02D0gamma_(
          ("meanDelta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Mean of Bu2Dst0h_Dst02D0gamma m[Delta]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          141, 136, 146),
      a0MeanBu_Bu2Dst0h_Dst02D0gamma_(
          ("a0MeanBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5105, 5055, 5165),
      a1MeanBu_Bu2Dst0h_Dst02D0gamma_(
          ("a1MeanBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3, 0, 10),
      a2MeanBu_Bu2Dst0h_Dst02D0gamma_(
          ("a2MeanBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -0.012, -0.1, 0.1),
      meanBu_Bu2Dst0h_Dst02D0gamma_(
          ("meanBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Mean of Bu2Dst0h_Dst02D0gamma m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0MeanBu_Bu2Dst0h_Dst02D0gamma_,
                     a1MeanBu_Bu2Dst0h_Dst02D0gamma_,
                     a2MeanBu_Bu2Dst0h_Dst02D0gamma_)),
      // -------------------- PARTIAL PI0 -------------------- //
      meanDelta_Bu2Dst0h_Dst02D0pi0_(("meanDelta_Bu2Dst0h_Dst02D0pi0_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("Mean of Bu2Dst0h_Dst02D0pi0 m[Delta]" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     80, 70, 90),
      a0MeanBu_Bu2Dst0h_Dst02D0pi0_(("a0MeanBu_Bu2Dst0h_Dst02D0pi0_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a0 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    5057, 5027, 5087),
      a1MeanBu_Bu2Dst0h_Dst02D0pi0_(("a1MeanBu_Bu2Dst0h_Dst02D0pi0_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a1 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    3, 0, 10),
      a2MeanBu_Bu2Dst0h_Dst02D0pi0_(("a2MeanBu_Bu2Dst0h_Dst02D0pi0_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a2 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    -0.012, -0.1, 0.1),
      meanBu_Bu2Dst0h_Dst02D0pi0_(
          ("meanBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Mean of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              a0MeanBu_Bu2Dst0h_Dst02D0pi0_, a1MeanBu_Bu2Dst0h_Dst02D0pi0_, a2MeanBu_Bu2Dst0h_Dst02D0pi0_)),
      // -------------------- DST0D0 BACKGROUND -------------------- //
      thresholdDeltaComb_(("thresholdDeltaComb_" +
                           ComposeName(uniqueId, Neutral::gamma))
                              .c_str(),
                          ("Delta Combinatorial thershold " +
                           ComposeName(uniqueId, Neutral::gamma))
                              .c_str(),
                          0.1),
      cDeltaComb_(
          ("cDeltaComb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Delta Combinatorial c parameter " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          10, 0.001, 20),
      aDeltaComb_(
          ("aDeltaComb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Delta Combinatorial a parameter " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -0.5, -1, 1),
      bDeltaComb_(
          ("bDeltaComb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Delta Combinatorial b parameter " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.000001),  // -0.5, 0.5),
      pdfDeltaComb_(
          ("pdfDeltaComb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("DeltaCombinatorial PDF " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), thresholdDeltaComb_, cDeltaComb_,
          aDeltaComb_, bDeltaComb_),
      // -------------------- EXPONENTIAL BACKGROUND -------------------- //
      a0LambdaBuComb_(
          ("a0LambdaBuComb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 component for Bu Combinatorial constant " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -0.001, -1, -0.00001),
      lambdaBuComb_(
          ("lambdaBuComb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Bu Combinatorial constant " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), RooArgSet(a0LambdaBuComb_)),
      pdfBuComb_(("pdfBuComb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
                 ("BuCombinatorial PDF " +
                  ComposeName(uniqueId, Neutral::gamma))
                     .c_str(),
                 Configuration::Get().buMass(), lambdaBuComb_),
      pdfComb_(("pdfComb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
               ("Combinatorial PDF " + ComposeName(uniqueId, Neutral::gamma))
                   .c_str(),
               pdfDeltaComb_,
               RooFit::Conditional(pdfBuComb_, Configuration::Get().buMass())),
      neutralCrossFeedRate_Bu2Dst0h_() {}

template <>
NeutralVars<Neutral::pi0>::NeutralVars(int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : meanDelta_Bu2Dst0h_Dst02D0pi0_(("meanDelta_Bu2Dst0h_Dst02D0pi0_" +
                                      ComposeName(uniqueId, Neutral::pi0))
                                         .c_str(),
                                     ("Mean of Bu2Dst0h_Dst02D0pi0 m[Delta]" +
                                      ComposeName(uniqueId, Neutral::pi0))
                                         .c_str(),
                                     144, 139, 149),
      a0MeanBu_Bu2Dst0h_Dst02D0pi0_(
          ("a0MeanBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          5105, 5055, 5155),
      a1MeanBu_Bu2Dst0h_Dst02D0pi0_(
          ("a1MeanBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          3, 0, 10),
      a2MeanBu_Bu2Dst0h_Dst02D0pi0_(
          ("a2MeanBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a2 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -0.012, -0.1, 0.1),
      meanBu_Bu2Dst0h_Dst02D0pi0_(
          ("meanBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Mean of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0MeanBu_Bu2Dst0h_Dst02D0pi0_,
                     a1MeanBu_Bu2Dst0h_Dst02D0pi0_,
                     a2MeanBu_Bu2Dst0h_Dst02D0pi0_)),
      // -------------------- NO CROSS FEED BECAUSE OF VETO -------------------- //
      meanDelta_Bu2Dst0h_Dst02D0gamma_(),
      a0MeanBu_Bu2Dst0h_Dst02D0gamma_(),
      a1MeanBu_Bu2Dst0h_Dst02D0gamma_(),
      a2MeanBu_Bu2Dst0h_Dst02D0gamma_(),
      meanBu_Bu2Dst0h_Dst02D0gamma_(),
      // -------------------- DST0D0 BACKGROUND -------------------- //
      thresholdDeltaComb_(
          ("thresholdDeltaComb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Delta Combinatorial thershold " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          135),
      cDeltaComb_(("cDeltaComb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
                  ("Delta Combinatorial c parameter " +
                   ComposeName(uniqueId, Neutral::pi0))
                      .c_str(),
                  10, 0.001, 20),
      aDeltaComb_(("aDeltaComb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
                  ("Delta Combinatorial a parameter " +
                   ComposeName(uniqueId, Neutral::pi0))
                      .c_str(),
                  -0.5, -1, 1),
      bDeltaComb_(("bDeltaComb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
                  ("Delta Combinatorial b parameter " +
                   ComposeName(uniqueId, Neutral::pi0))
                      .c_str(),
                  0.01),  // -0.5, 0.5),
      pdfDeltaComb_(
          ("pdfDeltaComb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("DeltaCombinatorial PDF " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), thresholdDeltaComb_, cDeltaComb_,
          aDeltaComb_, bDeltaComb_),
      // -------------------- EXPONENTIAL BACKGROUND -------------------- //
      a0LambdaBuComb_(
          ("a0LambdaBuComb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 component for Bu Combinatorial constant " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -0.001, -1, -0.00001),
      lambdaBuComb_(
          ("lambdaBuComb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Bu Combinatorial constant " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), RooArgSet(a0LambdaBuComb_)),
      pdfBuComb_(("pdfBuComb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
                 ("BuCombinatorial PDF " + ComposeName(uniqueId, Neutral::pi0))
                     .c_str(),
                 Configuration::Get().buMass(), lambdaBuComb_),
      pdfComb_(
          ("pdfComb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Combinatorial PDF " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          pdfDeltaComb_,
          RooFit::Conditional(pdfBuComb_, Configuration::Get().buMass())),
      neutralCrossFeedRate_Bu2Dst0h_(("neutralCrossFeedRate_Bu2Dst0h_" +
                               ComposeName(uniqueId, Neutral::pi0))
                                  .c_str(),
                              ("Neutral cross feed rate of Bu2Dst0h " +
                               ComposeName(uniqueId, Neutral::pi0))
                                  .c_str(),
                              0.7, 0, 1) {}
