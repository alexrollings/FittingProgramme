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
          5000, 4950, 5550),
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
          -0.007, -0.1, 0.1),
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
                                    5000, 4950, 5550),
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
                                    -0.007, -0.1, 0.1),
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
      // -------------------- BU2D0H BACKGROUND -------------------- //
      thresholdDelta_Bu2D0h_(("thresholdDelta_Bu2D0h_" +
                           ComposeName(uniqueId, Neutral::gamma))
                              .c_str(),
                          (" Delta_Bu2D0hinatorial thershold " +
                           ComposeName(uniqueId, Neutral::gamma))
                              .c_str(),
                          0.1),
      cDelta_Bu2D0h_(
          ("cDelta_Bu2D0h_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          (" Delta_Bu2D0hinatorial c parameter " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          10, 0.001, 20),
      aDelta_Bu2D0h_(
          ("aDelta_Bu2D0h_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          (" Delta_Bu2D0hinatorial a parameter " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -0.5, -1, 1),
      bDelta_Bu2D0h_(
          ("bDelta_Bu2D0h_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          (" Delta_Bu2D0hinatorial b parameter " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.000001),  // -0.5, 0.5),
      pdfDelta_Bu2D0h_(
          ("pdfDelta_Bu2D0h_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Delta_Bu2D0hinatorial PDF " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), thresholdDelta_Bu2D0h_, cDelta_Bu2D0h_,
          aDelta_Bu2D0h_, bDelta_Bu2D0h_),
      a0MeanBu_Bu2D0h_(
          ("a0MeanBu_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean of Bu2D0h m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5400, 5350, 5450),
      meanBu_Bu2D0h_(
          ("meanBu_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Mean of Bu2D0h m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0MeanBu_Bu2D0h_)),
      // -------------------- DST0D0 BACKGROUND -------------------- //
      thresholdDelta_Comb_(("thresholdDelta_Comb_" +
                           ComposeName(uniqueId, Neutral::gamma))
                              .c_str(),
                          ("Delta _Combinatorial thershold " +
                           ComposeName(uniqueId, Neutral::gamma))
                              .c_str(),
                          0.1),
      cDelta_Comb_(
          ("cDelta_Comb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Delta _Combinatorial c parameter " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          10, 0.001, 20),
      aDelta_Comb_(
          ("aDelta_Comb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Delta _Combinatorial a parameter " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -0.5, -1, 1),
      bDelta_Comb_(
          ("bDelta_Comb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Delta _Combinatorial b parameter " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.000001),  // -0.5, 0.5),
      pdfDelta_Comb_(
          ("pdfDelta_Comb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Delta_Combinatorial PDF " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), thresholdDelta_Comb_, cDelta_Comb_,
          aDelta_Comb_, bDelta_Comb_),
      // -------------------- EXPONENTIAL BACKGROUND -------------------- //
      a0LambdaBu_Comb_(
          ("a0LambdaBu_Comb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 component for Bu _Combinatorial constant " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -0.001, -1, -0.00001),
      lambdaBu_Comb_(
          ("lambdaBu_Comb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Bu _Combinatorial constant " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), RooArgSet(a0LambdaBu_Comb_)),
      pdfBu_Comb_(("pdfBu_Comb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
                 ("Bu_Combinatorial PDF " +
                  ComposeName(uniqueId, Neutral::gamma))
                     .c_str(),
                 Configuration::Get().buMass(), lambdaBu_Comb_),
      pdf_Comb_(("pdf_Comb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
               ("_Combinatorial PDF " + ComposeName(uniqueId, Neutral::gamma))
                   .c_str(),
               pdfDelta_Comb_,
               RooFit::Conditional(pdfBu_Comb_, Configuration::Get().buMass())),
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
          5000, 4950, 5050),
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
          -0.007, -0.1, 0.1),
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
      // -------------------- BU2D0H BKG -------------------- //
      thresholdDelta_Bu2D0h_(("thresholdDelta_Bu2D0h_" +
                           ComposeName(uniqueId, Neutral::pi0))
                              .c_str(),
                          (" Delta_Bu2D0hinatorial thershold " +
                           ComposeName(uniqueId, Neutral::pi0))
                              .c_str(),
                          135),
      cDelta_Bu2D0h_(
          ("cDelta_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_Bu2D0hinatorial c parameter " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          10, 0.001, 20),
      aDelta_Bu2D0h_(
          ("aDelta_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_Bu2D0hinatorial a parameter " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -0.5, -1, 1),
      bDelta_Bu2D0h_(
          ("bDelta_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_Bu2D0hinatorial b parameter " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          0.01),  // -0.5, 0.5),
      pdfDelta_Bu2D0h_(
          ("pdfDelta_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Delta_Bu2D0hinatorial PDF " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), thresholdDelta_Bu2D0h_, cDelta_Bu2D0h_,
          aDelta_Bu2D0h_, bDelta_Bu2D0h_),
      a0MeanBu_Bu2D0h_(
          ("a0MeanBu_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of mean of Bu2D0h m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          5400, 5350, 5450),
      meanBu_Bu2D0h_(
          ("meanBu_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Mean of Bu2D0h m[Bu]" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0MeanBu_Bu2D0h_)),
      // -------------------- DST0D0 BACKGROUND -------------------- //
      thresholdDelta_Comb_(
          ("thresholdDelta_Comb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Delta _Combinatorial thershold " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          135),
          // 0.1),
      cDelta_Comb_(("cDelta_Comb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
                  ("Delta _Combinatorial c parameter " +
                   ComposeName(uniqueId, Neutral::pi0))
                      .c_str(),
                  10, 0.001, 20),
      aDelta_Comb_(("aDelta_Comb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
                  ("Delta _Combinatorial a parameter " +
                   ComposeName(uniqueId, Neutral::pi0))
                      .c_str(),
                  -0.5, -1, 1),
      bDelta_Comb_(("bDelta_Comb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
                  ("Delta _Combinatorial b parameter " +
                   ComposeName(uniqueId, Neutral::pi0))
                      .c_str(),
                  0.01),  // -0.5, 0.5),
                  // 0.000001),
      pdfDelta_Comb_(
          ("pdfDelta_Comb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Delta_Combinatorial PDF " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), thresholdDelta_Comb_, cDelta_Comb_,
          aDelta_Comb_, bDelta_Comb_),
      // -------------------- EXPONENTIAL BACKGROUND -------------------- //
      a0LambdaBu_Comb_(
          ("a0LambdaBu_Comb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 component for Bu _Combinatorial constant " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -0.001, -1, -0.00001),
      lambdaBu_Comb_(
          ("lambdaBu_Comb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Bu _Combinatorial constant " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), RooArgSet(a0LambdaBu_Comb_)),
      pdfBu_Comb_(("pdfBu_Comb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
                 ("Bu_Combinatorial PDF " + ComposeName(uniqueId, Neutral::pi0))
                     .c_str(),
                 Configuration::Get().buMass(), lambdaBu_Comb_),
      pdf_Comb_(
          ("pdf_Comb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("_Combinatorial PDF " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          pdfDelta_Comb_,
          RooFit::Conditional(pdfBu_Comb_, Configuration::Get().buMass())),
      neutralCrossFeedRate_Bu2Dst0h_(("neutralCrossFeedRate_Bu2Dst0h_" +
                               ComposeName(uniqueId, Neutral::pi0))
                                  .c_str(),
                              ("Neutral cross feed rate of Bu2Dst0h " +
                               ComposeName(uniqueId, Neutral::pi0))
                                  .c_str(),
                              0.7, 0, 1) {}
