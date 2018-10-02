#include "NeutralVars.h"
#include "GlobalVars.h"

// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::gamma>::NeutralVars(int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : meanDelta_Bu2Dst0h_Dst02D0gamma_(("meanDelta_Bu2Dst0h_Dst02D0gamma_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("Mean of Bu2Dst0h_Dst02D0gamma m[Delta]" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     1.4208e+02),
      sigmaLDelta_Bu2Dst0h_Dst02D0gamma_(("sigmaLDelta_Bu2Dst0h_Dst02D0gamma_" +
                                       ComposeName(uniqueId, Neutral::gamma))
                                          .c_str(),
                                      ("Sigma left of Bu2Dst0h_Dst02D0gamma " +
                                       ComposeName(uniqueId, Neutral::gamma))
                                          .c_str(),
                                      4.5462e+00),
      sigmaRDelta_Bu2Dst0h_Dst02D0gamma_(("sigmaRDelta_Bu2Dst0h_Dst02D0gamma_" +
                                       ComposeName(uniqueId, Neutral::gamma))
                                          .c_str(),
                                      ("Sigma right of Bu2Dst0h_Dst02D0gamma " +
                                       ComposeName(uniqueId, Neutral::gamma))
                                          .c_str(),
                                      9.8299e+00),
      aLDelta_Bu2Dst0h_Dst02D0gamma_(
          ("aLDelta_Bu2Dst0h_Dst02D0gamma_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("aL of Bu2Dst0h_Dst02D0gamma " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -8.4131e-02),
      aRDelta_Bu2Dst0h_Dst02D0gamma_(
          ("aRDelta_Bu2Dst0h_Dst02D0gamma_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("aR of Bu2Dst0h_Dst02D0gamma " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.4612e+00),
      nLDelta_Bu2Dst0h_Dst02D0gamma_(
          ("nLDelta_Bu2Dst0h_Dst02D0gamma_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("nL of Bu2Dst0h_Dst02D0gamma " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          8.7673e-01),
      nRDelta_Bu2Dst0h_Dst02D0gamma_(
          ("nRDelta_Bu2Dst0h_Dst02D0gamma_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("nR of Bu2Dst0h_Dst02D0gamma " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.7234e+00),
      pdfLDelta_Bu2Dst0h_Dst02D0gamma_(
          ("pdfLDelta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Delta left PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), meanDelta_Bu2Dst0h_Dst02D0gamma_,
          sigmaLDelta_Bu2Dst0h_Dst02D0gamma_, aLDelta_Bu2Dst0h_Dst02D0gamma_,
          nLDelta_Bu2Dst0h_Dst02D0gamma_),
      pdfRDelta_Bu2Dst0h_Dst02D0gamma_(
          ("pdfRDelta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Delta right PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), meanDelta_Bu2Dst0h_Dst02D0gamma_,
          sigmaRDelta_Bu2Dst0h_Dst02D0gamma_, aRDelta_Bu2Dst0h_Dst02D0gamma_,
          nRDelta_Bu2Dst0h_Dst02D0gamma_),
      fracLRDelta_Bu2Dst0h_Dst02D0gamma_(
          ("fracLRDelta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of left w.r.t. right PDF in Bu2Dst0h_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.5849e-01),
      pdfDelta_Bu2Dst0h_Dst02D0gamma_(("pdfDelta_Bu2Dst0h_Dst02D0gamma_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("Bu2Dst0h_Dst02D0gamma Delta PDF " +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    RooArgList(pdfLDelta_Bu2Dst0h_Dst02D0gamma_,
                                               pdfRDelta_Bu2Dst0h_Dst02D0gamma_),
                                    fracLRDelta_Bu2Dst0h_Dst02D0gamma_),
      a0Mean1Bu_Bu2Dst0h_Dst02D0gamma_(
          ("a0Mean1Bu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 4998, 4950, 5050),
          5.0055e+03),
      a1Mean1Bu_Bu2Dst0h_Dst02D0gamma_(
          ("a1Mean1Bu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 3, 0, 10),
          2.2382e+00),
      a2Mean1Bu_Bu2Dst0h_Dst02D0gamma_(
          ("a2Mean1Bu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // -0.007, -0.1, 0.1),
          -2.0869e-03),
      mean1Bu_Bu2Dst0h_Dst02D0gamma_(
          ("mean1Bu_Bu2Dst0h_Dst02D0gamma_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Mean of Bu2Dst0h_Dst02D0gamma m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0Mean1Bu_Bu2Dst0h_Dst02D0gamma_,
                     a1Mean1Bu_Bu2Dst0h_Dst02D0gamma_,
                     a2Mean1Bu_Bu2Dst0h_Dst02D0gamma_)),
      a0Mean2Bu_Bu2Dst0h_Dst02D0gamma_(),
      a1Mean2Bu_Bu2Dst0h_Dst02D0gamma_(),
      a2Mean2Bu_Bu2Dst0h_Dst02D0gamma_(),
      mean2Bu_Bu2Dst0h_Dst02D0gamma_(),
      a0SigmaLBu_Bu2Dst0h_Dst02D0gamma_(
          ("a0SigmaLBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigmaL of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 15, -100, 100),
          1.8111e+02),
      a1SigmaLBu_Bu2Dst0h_Dst02D0gamma_(
          ("a1SigmaLBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigmaL of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 0.09, -10, 10),
          -2.3305e+00),
      a2SigmaLBu_Bu2Dst0h_Dst02D0gamma_(
          ("a2SigmaLBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigmaL of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 0.0036, -0.01, 0.01),
          8.1783e-03),
      a0SigmaRBu_Bu2Dst0h_Dst02D0gamma_(
          ("a0SigmaRBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigmaR of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          9.1033e+01),
      a1SigmaRBu_Bu2Dst0h_Dst02D0gamma_(
          ("a1SigmaRBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigmaR of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -8.1901e-01),
      a2SigmaRBu_Bu2Dst0h_Dst02D0gamma_(
          ("a2SigmaRBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigmaR of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.9728e-03),
      aLBu_Bu2Dst0h_Dst02D0gamma_(
          ("aLBu_Bu2Dst0h_Dst02D0gamma_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("aL of Bu2Dst0h_Dst02D0gamma " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.9484e+00),  //2.3, 0, 5),
      aRBu_Bu2Dst0h_Dst02D0gamma_(
          ("aRBu_Bu2Dst0h_Dst02D0gamma_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("aR of Bu2Dst0h_Dst02D0gamma " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.2011e+00),  //4.6, 0, 5),
      nLBu_Bu2Dst0h_Dst02D0gamma_(
          ("nLBu_Bu2Dst0h_Dst02D0gamma_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("nL of Bu2Dst0h_Dst02D0gamma " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          100),  //3.4, 0, 5),
      nRBu_Bu2Dst0h_Dst02D0gamma_(
          ("nRBu_Bu2Dst0h_Dst02D0gamma_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("nR of Bu2Dst0h_Dst02D0gamma " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.4977e+00),  //3.5, 0, 5),
      fracLRPdfBu_Bu2Dst0h_Dst02D0gamma_(
          ("fracLRPdfBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of left w.r.t. right Bu PDF in Bu2Dst0h_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          8.3639e-01),
      fracWidePdfBu_Bu2Dst0h_Dst02D0gamma_(
          ("fracWidePdfBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of wide gaussian for Bu PDF in Bu2Dst0h_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3.5033e-03),
      relativeBuWidth_Bu2Dst0h_Dst02D0gamma_(
          ("relativeBuWidth_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in Bu2Dst0h_Dst02D0gamma "
           "mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_(
          ("ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n Bu2Dst0h_Dst02D0gamma mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.07930, -1, 1),//, 0.0, 0.1),
      // -------------------- PARTIAL PI0 -------------------- //
      meanDelta_Bu2Dst0h_Dst02D0pi0_(("meanDelta_Bu2Dst0h_Dst02D0pi0_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("Mean of Bu2Dst0h_Dst02D0pi0 m[Delta]" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     8.5057e+01),
                                     // 82, 77, 87),
      sigmaLDelta_Bu2Dst0h_Dst02D0pi0_(("sigmaLDelta_Bu2Dst0h_Dst02D0pi0_" +
                                       ComposeName(uniqueId, Neutral::gamma))
                                          .c_str(),
                                      ("Sigma left of Bu2Dst0h_Dst02D0pi0 " +
                                       ComposeName(uniqueId, Neutral::gamma))
                                          .c_str(),
                                      1.9656e+01),
      sigmaRDelta_Bu2Dst0h_Dst02D0pi0_(("sigmaRDelta_Bu2Dst0h_Dst02D0pi0_" +
                                       ComposeName(uniqueId, Neutral::gamma))
                                          .c_str(),
                                      ("Sigma right of Bu2Dst0h_Dst02D0pi0 " +
                                       ComposeName(uniqueId, Neutral::gamma))
                                          .c_str(),
                                      7.2062e+00),
      aLDelta_Bu2Dst0h_Dst02D0pi0_(
          ("aLDelta_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("aL of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -3.1226e+00),
      aRDelta_Bu2Dst0h_Dst02D0pi0_(
          ("aRDelta_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("aR of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.6928e+00),
      nLDelta_Bu2Dst0h_Dst02D0pi0_(
          ("nLDelta_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("nL of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.3440e+00),
      nRDelta_Bu2Dst0h_Dst02D0pi0_(
          ("nRDelta_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("nR of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.1259e+01),
      pdfLDelta_Bu2Dst0h_Dst02D0pi0_(
          ("pdfLDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Delta left PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), meanDelta_Bu2Dst0h_Dst02D0pi0_,
          sigmaLDelta_Bu2Dst0h_Dst02D0pi0_, aLDelta_Bu2Dst0h_Dst02D0pi0_,
          nLDelta_Bu2Dst0h_Dst02D0pi0_),
      pdfRDelta_Bu2Dst0h_Dst02D0pi0_(
          ("pdfRDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Delta right PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), meanDelta_Bu2Dst0h_Dst02D0pi0_,
          sigmaRDelta_Bu2Dst0h_Dst02D0pi0_, aRDelta_Bu2Dst0h_Dst02D0pi0_,
          nRDelta_Bu2Dst0h_Dst02D0pi0_),
      fracLRDelta_Bu2Dst0h_Dst02D0pi0_(
          ("fracLRDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of left w.r.t. right PDF in Bu2Dst0h_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          6.9308e-01),
      pdfDelta_Bu2Dst0h_Dst02D0pi0_(("pdfDelta_Bu2Dst0h_Dst02D0pi0_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("Bu2Dst0h_Dst02D0pi0 Delta PDF " +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    RooArgList(pdfLDelta_Bu2Dst0h_Dst02D0pi0_,
                                               pdfRDelta_Bu2Dst0h_Dst02D0pi0_),
                                    fracLRDelta_Bu2Dst0h_Dst02D0pi0_),
      a0Mean1Bu_Bu2Dst0h_Dst02D0pi0_(("a0Mean1Bu_Bu2Dst0h_Dst02D0pi0_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a0 of mean1 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    // 5030, 4950, 5550),
                                    5.2861e+03),
      a1Mean1Bu_Bu2Dst0h_Dst02D0pi0_(("a1Mean1Bu_Bu2Dst0h_Dst02D0pi0_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a1 of mean1 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    // 3, 0, 10),
                                    1.0338e+00),
      a2Mean1Bu_Bu2Dst0h_Dst02D0pi0_(("a2Mean1Bu_Bu2Dst0h_Dst02D0pi0_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a2 of mean1 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    // -0.007, -0.1, 0.1),
                                    1.4709e-02),
      mean1Bu_Bu2Dst0h_Dst02D0pi0_(("mean1Bu_Bu2Dst0h_Dst02D0pi0_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("Mean1 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  Configuration::Get().deltaMass(),
                                  RooArgList(a0Mean1Bu_Bu2Dst0h_Dst02D0pi0_,
                                             a1Mean1Bu_Bu2Dst0h_Dst02D0pi0_,
                                             a2Mean1Bu_Bu2Dst0h_Dst02D0pi0_)),
      a0Mean2Bu_Bu2Dst0h_Dst02D0pi0_(("a0Mean2Bu_Bu2Dst0h_Dst02D0pi0_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a0 of mean2 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    // 5030, 4950, 5550),
                                    5.3129e+03),
      a1Mean2Bu_Bu2Dst0h_Dst02D0pi0_(("a1Mean2Bu_Bu2Dst0h_Dst02D0pi0_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a1 of mean2 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    // 3, 0, 10),
                                    -3.8732e+00),
      a2Mean2Bu_Bu2Dst0h_Dst02D0pi0_(("a2Mean2Bu_Bu2Dst0h_Dst02D0pi0_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a2 of mean2 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    // -0.007, -0.1, 0.1),
                                    3.3767e-02),
      mean2Bu_Bu2Dst0h_Dst02D0pi0_(("mean2Bu_Bu2Dst0h_Dst02D0pi0_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("Mean2 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  Configuration::Get().deltaMass(),
                                  RooArgList(a0Mean2Bu_Bu2Dst0h_Dst02D0pi0_,
                                             a1Mean2Bu_Bu2Dst0h_Dst02D0pi0_,
                                             a2Mean2Bu_Bu2Dst0h_Dst02D0pi0_)),
      a0SigmaLBu_Bu2Dst0h_Dst02D0pi0_(
          ("a0SigmaLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigmaL of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 32, -100, 100),
          1.3351e+01),
      a1SigmaLBu_Bu2Dst0h_Dst02D0pi0_(
          ("a1SigmaLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigmaL of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 0.09, -10, 10),
          3.9526e+00),
      a2SigmaLBu_Bu2Dst0h_Dst02D0pi0_(
          ("a2SigmaLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigmaL of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 0.0036, -0.01, 0.01),
          -3.9637e-02),
      a0SigmaRBu_Bu2Dst0h_Dst02D0pi0_(
          ("a0SigmaRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigmaR of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.5662e+02),
      a1SigmaRBu_Bu2Dst0h_Dst02D0pi0_(
          ("a1SigmaRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigmaR of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -5.2733e+00),
      a2SigmaRBu_Bu2Dst0h_Dst02D0pi0_(
          ("a2SigmaRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigmaR of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3.0374e-02),
      aLBu_Bu2Dst0h_Dst02D0pi0_(
          ("aLBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("aL of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -9.7902e+00),  //2.3, 0, 5),
      aRBu_Bu2Dst0h_Dst02D0pi0_(
          ("aRBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("aR of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.0165e+00),  //4.6, 0, 5),
      nLBu_Bu2Dst0h_Dst02D0pi0_(
          ("nLBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("nL of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          9.1883e+01),  //3.4, 0, 5),
      nRBu_Bu2Dst0h_Dst02D0pi0_(
          ("nRBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("nR of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.5663e+00),  //3.5, 0, 5),
      fracLRPdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("fracLRPdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of left w.r.t. right Bu PDF in Bu2Dst0h_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3.5857e-02),
      relativeBuWidth_Bu2Dst0h_Dst02D0pi0_(
          ("relativeBuWidth_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in Bu2Dst0h_Dst02D0pi0 "
           "mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_(
          ("ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n Bu2Dst0h_Dst02D0pi0 mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.07930, -1, 1),//, 0.0, 0.1),
      // ------------------ DSTD0BKG PARAMETERS (SHARED) ------------------ //
      thresholdDelta_bkg_(
          ("thresholdDelta_bkg_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          (" Delta_bkg thershold " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 43),
          48),
      cDelta_bkg_(
          ("cDelta_bkg_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          (" Delta_bkg c parameter " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 10, 0.001, 20),
          // 29, 0, 35),
          5.0179e+01),
      aDelta_bkg_(
          ("aDelta_bkg_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          (" Delta_bkg a parameter " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // -0.5, -1, 1),
          // -0.044, -1, 1),
          9.2245e-01),
      bDelta_bkg_(
          ("bDelta_bkg_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          (" Delta_bkg b parameter " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 0.000001),  // -0.5, 0.5),
          // 0.00473, -1, 1),
          -1.0816),
      // ------------------ OVER RECONSTRUCTED BACKGROUND ------------------ //
      pdfDelta_overRec_(
          ("pdfDelta_overRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Delta_overRec PDF " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), thresholdDelta_bkg_, cDelta_bkg_,
          aDelta_bkg_, bDelta_bkg_),
      a0MeanBu_overRec_(
          ("a0MeanBu_overRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 of mean of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5400, 5350, 5450),
      meanBu_overRec_(
          ("meanBu_overRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean of overRec m[Bu]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), RooArgList(a0MeanBu_overRec_)),
      relativeBuWidth_overRec_(
          ("relativeBuWidth_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in overRec "
           "mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.95),
      ratioDst0KDst0pi_overRec_(
          ("ratioDst0KDst0pi_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n overRec mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.081, 0.0, 0.1),
      // -------------------- PARTIALLY RECONSTRUCTED BKG --------------------
      sigmaDelta_partialRec_(
          ("sigmaDelta_partialRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Sigma of partialRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5, 0, 10),
      fracPdfDelta_partialRec_(
          ("fracPdfDelta_partialRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of flat pdf w.r.t. peaking pdf for partially "
           "reconstructed bkg " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.2, 0, 1),
      pdfFlatDelta_partialRec_(
          ("pdfFlatDelta_partialRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Delta_partialRec flat bkg " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), thresholdDelta_bkg_, cDelta_bkg_,
          aDelta_bkg_, bDelta_bkg_),
      pdfPeakDelta_partialRec_(
          ("pdfPeakDelta_partialRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("partialRec Delta peaking PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), meanDelta_Bu2Dst0h_Dst02D0gamma_,
          sigmaDelta_partialRec_),
      pdfDelta_partialRec_(
          ("pdfDelta_partialRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("partialRec Delta PDF " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          RooArgSet(pdfPeakDelta_partialRec_, pdfFlatDelta_partialRec_),
          fracPdfDelta_partialRec_),
      a0MeanBu_partialRec_(
          ("a0MeanBu_partialRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean of partialRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5010, 4960, 5060),
      a1MeanBu_partialRec_(
          ("a1MeanBu_partialRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean of partialRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.3, 0, 10),
      a2MeanBu_partialRec_(
          ("a2MeanBu_partialRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean of partialRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -0.004, -0.1, 0.1),
      meanBu_partialRec_(
          ("meanBu_partialRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Mean of partialRec m[Bu]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0MeanBu_partialRec_, a1MeanBu_partialRec_,
                     a2MeanBu_partialRec_)),
      relativeBuWidth_partialRec_(
          ("relativeBuWidth_partialRec_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in partialRec "
           "mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.95),
      ratioDst0KDst0pi_partialRec_(
          ("ratioDst0KDst0pi_partialRec_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n partialRec mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.081, 0.0, 0.1),
      // ------------------ OVER RECONSTRUCTED BACKGROUND ------------------ //
      pdfDelta_misRec_(
          ("pdfDelta_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Delta_misRec PDF " + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          Configuration::Get().deltaMass(), thresholdDelta_bkg_, cDelta_bkg_,
          aDelta_bkg_, bDelta_bkg_),
      a0MeanBu_misRec_(
          ("a0MeanBu_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 of mean of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5250, 5200, 5300),
      meanBu_misRec_(
          ("meanBu_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean of misRec m[Bu]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), RooArgList(a0MeanBu_misRec_)),
      // -------------------- DST0D0 BACKGROUND -------------------- //
      pdfDelta_Comb_(
          ("pdfDelta_Comb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Delta_Combinatorial PDF " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), thresholdDelta_bkg_, cDelta_bkg_,
          aDelta_bkg_, bDelta_bkg_),
      // -------------------- EXPONENTIAL BACKGROUND -------------------- //
      a0LambdaBu_Comb_(
          ("a0LambdaBu_Comb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 component for Bu _Combinatorial constant " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -0.001, -1, -0.00001),
      lambdaBu_Comb_(
          ("lambdaBu_Comb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Bu _Combinatorial constant " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), RooArgSet(a0LambdaBu_Comb_)),
      pdfBu_Comb_(
          ("pdfBu_Comb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Bu_Combinatorial PDF " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().buMass(), lambdaBu_Comb_),
      pdf_Comb_(
          ("pdf_Comb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("_Combinatorial PDF " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          pdfDelta_Comb_,
          RooFit::Conditional(pdfBu_Comb_, Configuration::Get().buMass())) {}

template <>
NeutralVars<Neutral::pi0>::NeutralVars(int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : meanDelta_Bu2Dst0h_Dst02D0pi0_(("meanDelta_Bu2Dst0h_Dst02D0pi0_" +
                                      ComposeName(uniqueId, Neutral::pi0))
                                         .c_str(),
                                     ("Mean of Bu2Dst0h_Dst02D0pi0 m[Delta]" +
                                      ComposeName(uniqueId, Neutral::pi0))
                                         .c_str(),
                                     1.4235e+02),
      // 143, 138, 148),
      sigmaLDelta_Bu2Dst0h_Dst02D0pi0_(("sigmaLDelta_Bu2Dst0h_Dst02D0pi0_" +
                                       ComposeName(uniqueId, Neutral::pi0))
                                          .c_str(),
                                      ("Sigma left of Bu2Dst0h_Dst02D0pi0 " +
                                       ComposeName(uniqueId, Neutral::pi0))
                                          .c_str(),
                                      2.1093e+00),
      // 3, 1, 5),
      sigmaRDelta_Bu2Dst0h_Dst02D0pi0_(("sigmaRDelta_Bu2Dst0h_Dst02D0pi0_" +
                                       ComposeName(uniqueId, Neutral::pi0))
                                          .c_str(),
                                      ("Sigma right of Bu2Dst0h_Dst02D0pi0 " +
                                       ComposeName(uniqueId, Neutral::pi0))
                                          .c_str(),
                                      1.5256e+00),
      aLDelta_Bu2Dst0h_Dst02D0pi0_(
          ("aLDelta_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("aL of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -4.4647e-01),
      aRDelta_Bu2Dst0h_Dst02D0pi0_(
          ("aRDelta_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("aR of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          1.8325e+00),
      nLDelta_Bu2Dst0h_Dst02D0pi0_(
          ("nLDelta_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("nL of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          4.2560e+01),
      nRDelta_Bu2Dst0h_Dst02D0pi0_(
          ("nRDelta_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("nR of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          2.6622e+00),
      pdfLDelta_Bu2Dst0h_Dst02D0pi0_(
          ("pdfLDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Delta left PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), meanDelta_Bu2Dst0h_Dst02D0pi0_,
          sigmaLDelta_Bu2Dst0h_Dst02D0pi0_, aLDelta_Bu2Dst0h_Dst02D0pi0_,
          nLDelta_Bu2Dst0h_Dst02D0pi0_),
      pdfRDelta_Bu2Dst0h_Dst02D0pi0_(
          ("pdfRDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Delta right PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), meanDelta_Bu2Dst0h_Dst02D0pi0_,
          sigmaRDelta_Bu2Dst0h_Dst02D0pi0_, aRDelta_Bu2Dst0h_Dst02D0pi0_,
          nRDelta_Bu2Dst0h_Dst02D0pi0_),
      fracLRDelta_Bu2Dst0h_Dst02D0pi0_(
          ("fracLRDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Fraction of left w.r.t. right PDF in Bu2Dst0h_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          5.0583e-01),
      pdfDelta_Bu2Dst0h_Dst02D0pi0_(("pdfDelta_Bu2Dst0h_Dst02D0pi0_" +
                                     ComposeName(uniqueId, Neutral::pi0))
                                        .c_str(),
                                    ("Bu2Dst0h_Dst02D0pi0 Delta PDF " +
                                     ComposeName(uniqueId, Neutral::pi0))
                                        .c_str(),
                                    RooArgList(pdfLDelta_Bu2Dst0h_Dst02D0pi0_,
                                               pdfRDelta_Bu2Dst0h_Dst02D0pi0_),
                                    fracLRDelta_Bu2Dst0h_Dst02D0pi0_),
      a0Mean1Bu_Bu2Dst0h_Dst02D0pi0_(
          ("a0Mean1Bu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 4998, 4950, 5050),
          5.1129e+03),
      a1Mean1Bu_Bu2Dst0h_Dst02D0pi0_(
          ("a1Mean1Bu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 3, 0, 10),
          -4.0649e-03),
      a2Mean1Bu_Bu2Dst0h_Dst02D0pi0_(
          ("a2Mean1Bu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a2 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // -0.007, -0.1, 0.1),
          8.2868e-03),
      mean1Bu_Bu2Dst0h_Dst02D0pi0_(
          ("mean1Bu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Mean of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0Mean1Bu_Bu2Dst0h_Dst02D0pi0_,
                     a1Mean1Bu_Bu2Dst0h_Dst02D0pi0_,
                     a2Mean1Bu_Bu2Dst0h_Dst02D0pi0_)),
      a0Mean2Bu_Bu2Dst0h_Dst02D0pi0_(),
      a1Mean2Bu_Bu2Dst0h_Dst02D0pi0_(),
      a2Mean2Bu_Bu2Dst0h_Dst02D0pi0_(),
      mean2Bu_Bu2Dst0h_Dst02D0pi0_(),
      a0SigmaLBu_Bu2Dst0h_Dst02D0pi0_(
          ("a0SigmaLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of sigmaL of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 22, -100, 100),
          4.5493e+01),
      a1SigmaLBu_Bu2Dst0h_Dst02D0pi0_(
          ("a1SigmaLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of sigmaL of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 0.07, -10, 10),
          -2.6105e-02),
      a2SigmaLBu_Bu2Dst0h_Dst02D0pi0_(
          ("a2SigmaLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a2 of sigmaL of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 0.0036, -0.01, 0.01),
          -1.2044e-03),
      a0SigmaRBu_Bu2Dst0h_Dst02D0pi0_(
          ("a0SigmaRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of sigmaR of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 22, -100, 100),
          4.5493e+01),
      a1SigmaRBu_Bu2Dst0h_Dst02D0pi0_(
          ("a1SigmaRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of sigmaR of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 0.07, -10, 10),
          -2.6105e-02),
      a2SigmaRBu_Bu2Dst0h_Dst02D0pi0_(
          ("a2SigmaRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a2 of sigmaR of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 0.0036, -0.01, 0.01),
          -1.2044e-03),
      aLBu_Bu2Dst0h_Dst02D0pi0_(
          ("aLBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("aL of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          7.9439e+00),  //2.3, 0, 5),
      aRBu_Bu2Dst0h_Dst02D0pi0_(
          ("aRBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("aR of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -8.6538e+00),  //4.6, 0, 5),
      nLBu_Bu2Dst0h_Dst02D0pi0_(
          ("nLBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("nL of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          9.8579e+00),  //3.4, 0, 5),
      nRBu_Bu2Dst0h_Dst02D0pi0_(
          ("nRBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("nR of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          1.1800e+01),  //3.5, 0, 5),
      fracLRPdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("fracLRPdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Fraction of left w.r.t. right Bu PDF in Bu2Dst0h_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          6.9308e-01),
      relativeBuWidth_Bu2Dst0h_Dst02D0pi0_(
          ("relativeBuWidth_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in Bu2Dst0h_Dst02D0pi0 "
           "mode " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          1),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_(
          ("ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n Bu2Dst0h_Dst02D0pi0 mode " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          0.07930, -1, 1), //, 0.0, 0.1),
      // ------------------ NO CROSS FEED BECAUSE OF VETO ------------------ //
      meanDelta_Bu2Dst0h_Dst02D0gamma_(),
      sigmaLDelta_Bu2Dst0h_Dst02D0gamma_(),
      sigmaRDelta_Bu2Dst0h_Dst02D0gamma_(),
      aRDelta_Bu2Dst0h_Dst02D0gamma_(),
      aLDelta_Bu2Dst0h_Dst02D0gamma_(),
      nRDelta_Bu2Dst0h_Dst02D0gamma_(),
      nLDelta_Bu2Dst0h_Dst02D0gamma_(),
      pdfLDelta_Bu2Dst0h_Dst02D0gamma_(),
      pdfRDelta_Bu2Dst0h_Dst02D0gamma_(),
      fracLRDelta_Bu2Dst0h_Dst02D0gamma_(),
      pdfDelta_Bu2Dst0h_Dst02D0gamma_(),
      a0Mean1Bu_Bu2Dst0h_Dst02D0gamma_(),
      a1Mean1Bu_Bu2Dst0h_Dst02D0gamma_(),
      a2Mean1Bu_Bu2Dst0h_Dst02D0gamma_(),
      mean1Bu_Bu2Dst0h_Dst02D0gamma_(),
      a0Mean2Bu_Bu2Dst0h_Dst02D0gamma_(),
      a1Mean2Bu_Bu2Dst0h_Dst02D0gamma_(),
      a2Mean2Bu_Bu2Dst0h_Dst02D0gamma_(),
      mean2Bu_Bu2Dst0h_Dst02D0gamma_(),
      a0SigmaLBu_Bu2Dst0h_Dst02D0gamma_(),
      a1SigmaLBu_Bu2Dst0h_Dst02D0gamma_(),
      a2SigmaLBu_Bu2Dst0h_Dst02D0gamma_(),
      a0SigmaRBu_Bu2Dst0h_Dst02D0gamma_(),
      a1SigmaRBu_Bu2Dst0h_Dst02D0gamma_(),
      a2SigmaRBu_Bu2Dst0h_Dst02D0gamma_(),
      aLBu_Bu2Dst0h_Dst02D0gamma_(),
      aRBu_Bu2Dst0h_Dst02D0gamma_(),
      nLBu_Bu2Dst0h_Dst02D0gamma_(),
      nRBu_Bu2Dst0h_Dst02D0gamma_(),
      fracLRPdfBu_Bu2Dst0h_Dst02D0gamma_(),
      fracWidePdfBu_Bu2Dst0h_Dst02D0gamma_(),
      relativeBuWidth_Bu2Dst0h_Dst02D0gamma_(),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_(),
      // ------------------ DSTD0BKG PARAMETERS (SHARED) ------------------ //
      thresholdDelta_bkg_(
          ("thresholdDelta_bkg_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg thershold " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 134.5),
          1.3428e+02),
      cDelta_bkg_(
          ("cDelta_bkg_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg c parameter " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 10, 0.001, 20),
          // 3.14),
          6.4715),
      aDelta_bkg_(
          ("aDelta_bkg_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg a parameter " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // -0.5, -1, 1),
          // -0.99),
          -5),
      bDelta_bkg_(
          ("bDelta_bkg_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg b parameter " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 0.01),  // -0.5, 0.5),
          // -0.058),
          -4.0455e-03),
      // -------------------- OVER RECONSTRUCTED BKG -------------------- //
      pdfDelta_overRec_(
          ("pdfDelta_overRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Delta_overRec PDF " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          Configuration::Get().deltaMass(), thresholdDelta_bkg_, cDelta_bkg_,
          aDelta_bkg_, bDelta_bkg_),
      a0MeanBu_overRec_(
          ("a0MeanBu_overRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 of mean of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          5520, 5470, 5570),
      meanBu_overRec_(
          ("meanBu_overRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Mean of overRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), RooArgList(a0MeanBu_overRec_)),
      relativeBuWidth_overRec_(
          ("relativeBuWidth_overRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in overRec "
           "mode " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          0.95),
      ratioDst0KDst0pi_overRec_(
          ("ratioDst0KDst0pi_overRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n overRec mode " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          0.081, 0.0, 0.1),
      // -------------------- PARTIALLY RECONSTRUCTED BKG --------------------
      sigmaDelta_partialRec_(
          ("sigmaDelta_partialRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Sigma of partialRec Gaussian " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          3, 0, 5),
      fracPdfDelta_partialRec_(
          ("fracPdfDelta_partialRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Fraction of flat pdf w.r.t. peaking pdf for partially "
           "reconstructed bkg " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          0.5, 0, 1),
      pdfFlatDelta_partialRec_(
          ("pdfFlatDelta_partialRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Delta_partialRec flat bkg " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), thresholdDelta_bkg_, cDelta_bkg_,
          aDelta_bkg_, bDelta_bkg_),
      pdfPeakDelta_partialRec_(
          ("pdfPeakDelta_partialRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("partialRec Delta peaking PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), meanDelta_Bu2Dst0h_Dst02D0pi0_,
          sigmaDelta_partialRec_),
      pdfDelta_partialRec_(
          ("pdfDelta_partialRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("partialRec Delta PDF " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          RooArgSet(pdfPeakDelta_partialRec_, pdfFlatDelta_partialRec_),
          fracPdfDelta_partialRec_),
      a0MeanBu_partialRec_(
          ("a0MeanBu_partialRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of mean of partialRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 5100, 5050, 5150),
          4950, 4900, 5000),
      a1MeanBu_partialRec_(
          ("a1MeanBu_partialRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of mean of partialRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 3, 0, 10),
          1.3, 0, 10),
      a2MeanBu_partialRec_(
          ("a2MeanBu_partialRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a2 of mean of partialRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -0.004, -0.1, 0.1),
      // -0.007, -0.1, 0.1),
      meanBu_partialRec_(
          ("meanBu_partialRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Mean of partialRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0MeanBu_partialRec_, a1MeanBu_partialRec_,
                     a2MeanBu_partialRec_)),
      relativeBuWidth_partialRec_(
          ("relativeBuWidth_partialRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in partialRec "
           "mode " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          0.95),
      ratioDst0KDst0pi_partialRec_(
          ("ratioDst0KDst0pi_partialRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n partialRec mode " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          0.081, 0.0, 0.1),
      // ------------------ MIS RECONSTRUCTED BACKGROUND ------------------ //
      pdfDelta_misRec_(
          ("pdfDelta_misRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Delta_misRec PDF " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          Configuration::Get().deltaMass(), thresholdDelta_bkg_, cDelta_bkg_,
          aDelta_bkg_, bDelta_bkg_),
      a0MeanBu_misRec_(
          ("a0MeanBu_misRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 of mean of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          5260, 5210, 5310),
      meanBu_misRec_(
          ("meanBu_misRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Mean of misRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), RooArgList(a0MeanBu_misRec_)),
      // -------------------- DST0D0 BACKGROUND -------------------- //
      pdfDelta_Comb_(
          ("pdfDelta_Comb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Delta_Combinatorial PDF " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), thresholdDelta_bkg_, cDelta_bkg_,
          aDelta_bkg_, bDelta_bkg_),
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
      pdfBu_Comb_(
          ("pdfBu_Comb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Bu_Combinatorial PDF " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().buMass(), lambdaBu_Comb_),
      pdf_Comb_(
          ("pdf_Comb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("_Combinatorial PDF " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          pdfDelta_Comb_,
          RooFit::Conditional(pdfBu_Comb_, Configuration::Get().buMass())) {}
