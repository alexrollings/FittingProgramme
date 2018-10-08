#include "GlobalVars.h"
#include "NeutralVars.h"

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
          1.4208e+02),
      sigmaLDelta_Bu2Dst0h_Dst02D0gamma_(
          ("sigmaLDelta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Sigma left of Bu2Dst0h_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.5462e+00),
      sigmaRDelta_Bu2Dst0h_Dst02D0gamma_(
          ("sigmaRDelta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Sigma right of Bu2Dst0h_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          9.8299e+00),
      aLDelta_Bu2Dst0h_Dst02D0gamma_(("aLDelta_Bu2Dst0h_Dst02D0gamma_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("aL of Bu2Dst0h_Dst02D0gamma " +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     -8.4131e-02),
      aRDelta_Bu2Dst0h_Dst02D0gamma_(("aRDelta_Bu2Dst0h_Dst02D0gamma_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("aR of Bu2Dst0h_Dst02D0gamma " +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     2.4612e+00),
      nLDelta_Bu2Dst0h_Dst02D0gamma_(("nLDelta_Bu2Dst0h_Dst02D0gamma_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("nL of Bu2Dst0h_Dst02D0gamma " +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     8.7673e-01),
      nRDelta_Bu2Dst0h_Dst02D0gamma_(("nRDelta_Bu2Dst0h_Dst02D0gamma_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("nR of Bu2Dst0h_Dst02D0gamma " +
                                      ComposeName(uniqueId, Neutral::gamma))
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
      pdfDelta_Bu2Dst0h_Dst02D0gamma_(
          ("pdfDelta_Bu2Dst0h_Dst02D0gamma_" +
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
          ("mean1Bu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
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
      aLBu_Bu2Dst0h_Dst02D0gamma_(("aLBu_Bu2Dst0h_Dst02D0gamma_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("aL of Bu2Dst0h_Dst02D0gamma " +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  5.9484e+00),  // 2.3, 0, 5),
      aRBu_Bu2Dst0h_Dst02D0gamma_(("aRBu_Bu2Dst0h_Dst02D0gamma_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("aR of Bu2Dst0h_Dst02D0gamma " +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  2.2011e+00),  // 4.6, 0, 5),
      nLBu_Bu2Dst0h_Dst02D0gamma_(("nLBu_Bu2Dst0h_Dst02D0gamma_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("nL of Bu2Dst0h_Dst02D0gamma " +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  100),  // 3.4, 0, 5),
      nRBu_Bu2Dst0h_Dst02D0gamma_(("nRBu_Bu2Dst0h_Dst02D0gamma_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("nR of Bu2Dst0h_Dst02D0gamma " +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  1.4977e+00),  // 3.5, 0, 5),
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
          0.07930, -1, 1),  //, 0.0, 0.1),
      // -------------------- PARTIAL PI0 -------------------- //
      Bu2Dst0h_Dst02D0pi0_meanDelta_(("Bu2Dst0h_Dst02D0pi0_meanDelta_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("Mean of Bu2Dst0h_Dst02D0pi0 m[Delta]" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     8.5057e+01),
      // 82, 77, 87),
      Bu2Dst0h_Dst02D0pi0_sigmaLDelta_(("Bu2Dst0h_Dst02D0pi0_sigmaLDelta_" +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       ("Sigma left of Bu2Dst0h_Dst02D0pi0 " +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       1.9656e+01),
      Bu2Dst0h_Dst02D0pi0_sigmaRDelta_(("Bu2Dst0h_Dst02D0pi0_sigmaRDelta_" +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       ("Sigma right of Bu2Dst0h_Dst02D0pi0 " +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       7.2062e+00),
      Bu2Dst0h_Dst02D0pi0_aLDelta_(
          ("Bu2Dst0h_Dst02D0pi0_aLDelta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("aL of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -3.1226e+00),
      Bu2Dst0h_Dst02D0pi0_aRDelta_(
          ("Bu2Dst0h_Dst02D0pi0_aRDelta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("aR of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.6928e+00),
      nLDelta_Bu2Dst0h_Dst02D0pi0_(
          ("nLDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("nL of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.3440e+00),
      Bu2Dst0h_Dst02D0pi0_nRDelta_(
          ("Bu2Dst0h_Dst02D0pi0_nRDelta_" +
           ComposeName(uniqueId, Neutral::gamma))
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
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0pi0_meanDelta_,
          Bu2Dst0h_Dst02D0pi0_sigmaLDelta_, Bu2Dst0h_Dst02D0pi0_aLDelta_,
          nLDelta_Bu2Dst0h_Dst02D0pi0_),
      pdfRDelta_Bu2Dst0h_Dst02D0pi0_(
          ("pdfRDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Delta right PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0pi0_meanDelta_,
          Bu2Dst0h_Dst02D0pi0_sigmaRDelta_, Bu2Dst0h_Dst02D0pi0_aRDelta_,
          Bu2Dst0h_Dst02D0pi0_nRDelta_),
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
      a0Mean1Bu_Bu2Dst0h_Dst02D0pi0_(
          ("a0Mean1Bu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean1 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 5030, 4950, 5550),
          5.2861e+03),
      a1Mean1Bu_Bu2Dst0h_Dst02D0pi0_(
          ("a1Mean1Bu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean1 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 3, 0, 10),
          1.0338e+00),
      a2Mean1Bu_Bu2Dst0h_Dst02D0pi0_(
          ("a2Mean1Bu_Bu2Dst0h_Dst02D0pi0_" +
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
      a0Mean2Bu_Bu2Dst0h_Dst02D0pi0_(
          ("a0Mean2Bu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean2 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 5030, 4950, 5550),
          5.3129e+03),
      a1Mean2Bu_Bu2Dst0h_Dst02D0pi0_(
          ("a1Mean2Bu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean2 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 3, 0, 10),
          -3.8732e+00),
      a2Mean2Bu_Bu2Dst0h_Dst02D0pi0_(
          ("a2Mean2Bu_Bu2Dst0h_Dst02D0pi0_" +
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
          -9.7902e+00),  // 2.3, 0, 5),
      aRBu_Bu2Dst0h_Dst02D0pi0_(
          ("aRBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("aR of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.0165e+00),  // 4.6, 0, 5),
      nLBu_Bu2Dst0h_Dst02D0pi0_(
          ("nLBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("nL of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          9.1883e+01),  // 3.4, 0, 5),
      nRBu_Bu2Dst0h_Dst02D0pi0_(
          ("nRBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("nR of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.5663e+00),  // 3.5, 0, 5),
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
          0.07930, -1, 1),  //, 0.0, 0.1),
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
      // a0MeanBu_overRec_(
      //     ("a0MeanBu_overRec_" + ComposeName(uniqueId,
      //     Neutral::gamma)).c_str(),
      //     ("a0 of mean of overRec m[Bu] PDF " +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     // 5400, 5350, 5450),
      //     5400, 5350, 5450),
      // meanBu_overRec_(
      //     ("meanBu_overRec_" + ComposeName(uniqueId,
      //     Neutral::gamma)).c_str(), Configuration::Get().deltaMass(),
      //     RooArgList(a0MeanBu_overRec_)),
      a0Mean1Bu_overRec_(
          ("a0Mean1Bu_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean1 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 5030, 4950, 5550),
          5.2641e+03),
      a1Mean1Bu_overRec_(
          ("a1Mean1Bu_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean1 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 3, 0, 10),
          3.2770e+00),
      a2Mean1Bu_overRec_(
          ("a2Mean1Bu_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean1 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // -0.007, -0.1, 0.1),
          -8.1688e-03),
      mean1Bu_overRec_(
          ("mean1Bu_overRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean1 of overRec m[Bu]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0Mean1Bu_overRec_, a1Mean1Bu_overRec_,
                     a2Mean1Bu_overRec_)),
      a0Mean2Bu_overRec_(
          ("a0Mean2Bu_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean2 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 5030, 4950, 5550),
          5.4396e+03),
      a1Mean2Bu_overRec_(
          ("a1Mean2Bu_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean2 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 3, 0, 10),
          -1.4957e-02),
      a2Mean2Bu_overRec_(
          ("a2Mean2Bu_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean2 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // -0.007, -0.1, 0.1),
          5.8425e-04),
      mean2Bu_overRec_(
          ("mean2Bu_overRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean2 of overRec m[Bu]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0Mean2Bu_overRec_, a1Mean2Bu_overRec_,
                     a2Mean2Bu_overRec_)),
      a0SigmaLBu_overRec_(
          ("a0SigmaLBu_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigmaL of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 32, -100, 100),
          4.5119e+00),
      a1SigmaLBu_overRec_(
          ("a1SigmaLBu_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigmaL of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 0.09, -10, 10),
          1.2461e-01),
      a2SigmaLBu_overRec_(
          ("a2SigmaLBu_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigmaL of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 0.0036, -0.01, 0.01),
          1.8108e-03),
      a0SigmaRBu_overRec_(
          ("a0SigmaRBu_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigmaR of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.0667e+01),
      a1SigmaRBu_overRec_(
          ("a1SigmaRBu_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigmaR of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          7.5421e-01),
      a2SigmaRBu_overRec_(
          ("a2SigmaRBu_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigmaR of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -2.2312e-03),
      aLBu_overRec_(
          ("aLBu_overRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("aL of overRec " + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          3.7878e+00),  // 2.3, 0, 5),
      aRBu_overRec_(
          ("aRBu_overRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("aR of overRec " + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          -3.1173e+00),  // 4.6, 0, 5),
      nLBu_overRec_(
          ("nLBu_overRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("nL of overRec " + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          2.7083e+00),  // 3.4, 0, 5),
      nRBu_overRec_(
          ("nRBu_overRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("nR of overRec " + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          3.7229e+01),  // 3.5, 0, 5),
      fracLRPdfBu_overRec_(
          ("fracLRPdfBu_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of left w.r.t. right Bu PDF in overRec " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.9029e-01),
      relativeBuWidth_overRec_(
          ("relativeBuWidth_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in overRec "
           "mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1),
      ratioDst0KDst0pi_overRec_(
          ("ratioDst0KDst0pi_overRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n overRec mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.07768),  //, 0.0, 0.1),
      // -------------------- Pi0 PART RECONSTRUCTED BKG --------------------
      meanDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("meanDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Mean of Bu2Dst0hst_Dst02D0pi0 m[Delta]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          8.9570e+01),
      sigmaLDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("sigmaLDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Sigma left of Bu2Dst0hst_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.0927e+01),
      sigmaRDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("sigmaRDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Sigma right of Bu2Dst0hst_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.2894e+01),
      aLDelta_Bu2Dst0hst_Dst02D0pi0_(("aLDelta_Bu2Dst0hst_Dst02D0pi0_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("aL of Bu2Dst0hst_Dst02D0pi0 " +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     -4.2871e+00),
      aRDelta_Bu2Dst0hst_Dst02D0pi0_(("aRDelta_Bu2Dst0hst_Dst02D0pi0_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("aR of Bu2Dst0hst_Dst02D0pi0 " +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     6.0492e+00),
      nLDelta_Bu2Dst0hst_Dst02D0pi0_(("nLDelta_Bu2Dst0hst_Dst02D0pi0_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("nL of Bu2Dst0hst_Dst02D0pi0 " +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     7.4985e-01),
      nRDelta_Bu2Dst0hst_Dst02D0pi0_(("nRDelta_Bu2Dst0hst_Dst02D0pi0_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("nR of Bu2Dst0hst_Dst02D0pi0 " +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     5.4406e+01),
      pdfLDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfLDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Delta left PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), meanDelta_Bu2Dst0hst_Dst02D0pi0_,
          sigmaLDelta_Bu2Dst0hst_Dst02D0pi0_, aLDelta_Bu2Dst0hst_Dst02D0pi0_,
          nLDelta_Bu2Dst0hst_Dst02D0pi0_),
      pdfRDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfRDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Delta right PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), meanDelta_Bu2Dst0hst_Dst02D0pi0_,
          sigmaRDelta_Bu2Dst0hst_Dst02D0pi0_, aRDelta_Bu2Dst0hst_Dst02D0pi0_,
          nRDelta_Bu2Dst0hst_Dst02D0pi0_),
      fracLRDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("fracLRDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of left w.r.t. right PDF in Bu2Dst0hst_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          8.9266e-01),
      pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 peaking Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          RooArgList(pdfLDelta_Bu2Dst0hst_Dst02D0pi0_,
                     pdfRDelta_Bu2Dst0hst_Dst02D0pi0_),
          fracLRDelta_Bu2Dst0hst_Dst02D0pi0_),
      pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Delta_Bu2Dst0hst_Dst02D0pi0 flat Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), thresholdDelta_bkg_, cDelta_bkg_,
          aDelta_bkg_, bDelta_bkg_),
      fracPdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("fracPdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of flat pdf w.r.t. peaking pdf for partially "
           "reconstructed bkg " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          6.0674e-01),
      pdfDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          RooArgSet(pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_,
                    pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0_),
          fracPdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_),
      a0MeanBu_Bu2Dst0hst_Dst02D0pi0_(
          ("a0MeanBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.7586e+03),
      a1MeanBu_Bu2Dst0hst_Dst02D0pi0_(
          ("a1MeanBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3.5646e+00),
      a2MeanBu_Bu2Dst0hst_Dst02D0pi0_(
          ("a2MeanBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.4359e-02),
      meanBu_Bu2Dst0hst_Dst02D0pi0_(
          ("meanBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Mean of Bu2Dst0hst_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0MeanBu_Bu2Dst0hst_Dst02D0pi0_,
                     a1MeanBu_Bu2Dst0hst_Dst02D0pi0_,
                     a2MeanBu_Bu2Dst0hst_Dst02D0pi0_)),
      a0SigmaLBu_Bu2Dst0hst_Dst02D0pi0_(
          ("a0SigmaLBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigmaL of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.4387e+01),
      a1SigmaLBu_Bu2Dst0hst_Dst02D0pi0_(
          ("a1SigmaLBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigmaL of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          7.8205e-02),
      a2SigmaLBu_Bu2Dst0hst_Dst02D0pi0_(
          ("a2SigmaLBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigmaL of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3.1524e-03),
      a0SigmaRBu_Bu2Dst0hst_Dst02D0pi0_(
          ("a0SigmaRBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigmaR of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          9.8039e+01),
      a1SigmaRBu_Bu2Dst0hst_Dst02D0pi0_(
          ("a1SigmaRBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigmaR of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -7.1628e-01),
      a2SigmaRBu_Bu2Dst0hst_Dst02D0pi0_(
          ("a2SigmaRBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigmaR of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.3805e-03),
      aLBu_Bu2Dst0hst_Dst02D0pi0_(
          ("aLBu_Bu2Dst0hst_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("aL of Bu2Dst0hst_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -3.8309e+00),
      aRBu_Bu2Dst0hst_Dst02D0pi0_(
          ("aRBu_Bu2Dst0hst_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("aR of Bu2Dst0hst_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.2150e+00),
      nLBu_Bu2Dst0hst_Dst02D0pi0_(
          ("nLBu_Bu2Dst0hst_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("nL of Bu2Dst0hst_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3.5387e+00),
      nRBu_Bu2Dst0hst_Dst02D0pi0_(
          ("nRBu_Bu2Dst0hst_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("nR of Bu2Dst0hst_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.3416e+01),
      fracLRPdfBu_Bu2Dst0hst_Dst02D0pi0_(
          ("fracLRPdfBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of left w.r.t. right Bu PDF in Bu2Dst0hst_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.0890e-07),
      relativeBuWidth_Bu2Dst0hst_Dst02D0pi0_(
          ("relativeBuWidth_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in Bu2Dst0hst_Dst02D0pi0 "
           "mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_(
          ("ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n Bu2Dst0hst_Dst02D0pi0 mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.02, -1, 1),
      // ------------------ Gamma PART RECONSTRUCTED BACKGROUND
      // ------------------ //
      Bu2Dst0hst_Dst02D0gamma_meanDelta_(
          ("Bu2Dst0hst_Dst02D0gamma_meanDelta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Mean of Bu2Dst0hst_Dst02D0gamma m[Delta]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.3807e+02),
      Bu2Dst0hst_Dst02D0gamma_sigmaLDelta_(
          ("Bu2Dst0hst_Dst02D0gamma_sigmaLDelta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Sigma left of Bu2Dst0hst_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.4124e+00),
      Bu2Dst0hst_Dst02D0gamma_sigmaRDelta_(
          ("Bu2Dst0hst_Dst02D0gamma_sigmaRDelta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Sigma right of Bu2Dst0hst_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.3384e+01),
      Bu2Dst0hst_Dst02D0gamma_aLDelta_(("Bu2Dst0hst_Dst02D0gamma_aLDelta_" +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       ("aL of Bu2Dst0hst_Dst02D0gamma " +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       -1.3836e-01),
      Bu2Dst0hst_Dst02D0gamma_aRDelta_(("Bu2Dst0hst_Dst02D0gamma_aRDelta_" +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       ("aR of Bu2Dst0hst_Dst02D0gamma " +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       1.5977e+00),
      Bu2Dst0hst_Dst02D0gamma_nLDelta_(("Bu2Dst0hst_Dst02D0gamma_nLDelta_" +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       ("nL of Bu2Dst0hst_Dst02D0gamma " +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       1.0469e+02),
      Bu2Dst0hst_Dst02D0gamma_nRDelta_(("Bu2Dst0hst_Dst02D0gamma_nRDelta_" +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       ("nR of Bu2Dst0hst_Dst02D0gamma " +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       1.3000e+01),
      pdfLDelta_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfLDelta_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Delta left PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0hst_Dst02D0gamma_meanDelta_,
          Bu2Dst0hst_Dst02D0gamma_sigmaLDelta_,
          Bu2Dst0hst_Dst02D0gamma_aLDelta_, Bu2Dst0hst_Dst02D0gamma_nLDelta_),
      pdfRDelta_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfRDelta_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Delta right PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0hst_Dst02D0gamma_meanDelta_,
          Bu2Dst0hst_Dst02D0gamma_sigmaRDelta_,
          Bu2Dst0hst_Dst02D0gamma_aRDelta_, Bu2Dst0hst_Dst02D0gamma_nRDelta_),
      fracLRDelta_Bu2Dst0hst_Dst02D0gamma_(
          ("fracLRDelta_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of left w.r.t. right PDF in Bu2Dst0hst_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.5168e-01),
      pdfDelta_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfDelta_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          RooArgList(pdfLDelta_Bu2Dst0hst_Dst02D0gamma_,
                     pdfRDelta_Bu2Dst0hst_Dst02D0gamma_),
          fracLRDelta_Bu2Dst0hst_Dst02D0gamma_),
      a0MeanBu_Bu2Dst0hst_Dst02D0gamma_(
          ("a0MeanBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.9823e+03),
      a1MeanBu_Bu2Dst0hst_Dst02D0gamma_(
          ("a1MeanBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          7.2035e-01),
      a2MeanBu_Bu2Dst0hst_Dst02D0gamma_(
          ("a2MeanBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -5.2626e-04),
      meanBu_Bu2Dst0hst_Dst02D0gamma_(
          ("meanBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Mean of Bu2Dst0hst_Dst02D0gamma m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0MeanBu_Bu2Dst0hst_Dst02D0gamma_,
                     a1MeanBu_Bu2Dst0hst_Dst02D0gamma_,
                     a2MeanBu_Bu2Dst0hst_Dst02D0gamma_)),
      a0SigmaLBu_Bu2Dst0hst_Dst02D0gamma_(
          ("a0SigmaLBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigmaL of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.1748e+02),
      a1SigmaLBu_Bu2Dst0hst_Dst02D0gamma_(
          ("a1SigmaLBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigmaL of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.0968e+00),
      a2SigmaLBu_Bu2Dst0hst_Dst02D0gamma_(
          ("a2SigmaLBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigmaL of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.5671e-03),
      a0SigmaRBu_Bu2Dst0hst_Dst02D0gamma_(
          ("a0SigmaRBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigmaR of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.8658e+01),
      a1SigmaRBu_Bu2Dst0hst_Dst02D0gamma_(
          ("a1SigmaRBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigmaR of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -2.1932e-01),
      a2SigmaRBu_Bu2Dst0hst_Dst02D0gamma_(
          ("a2SigmaRBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigmaR of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.4876e-03),
      aLBu_Bu2Dst0hst_Dst02D0gamma_(("aLBu_Bu2Dst0hst_Dst02D0gamma_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("aL of Bu2Dst0hst_Dst02D0gamma " +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    -3.1581e+00),  // 2.3, 0, 5),
      aRBu_Bu2Dst0hst_Dst02D0gamma_(("aRBu_Bu2Dst0hst_Dst02D0gamma_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("aR of Bu2Dst0hst_Dst02D0gamma " +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    -3.0000e+00),  // 4.6, 0, 5),
      nLBu_Bu2Dst0hst_Dst02D0gamma_(("nLBu_Bu2Dst0hst_Dst02D0gamma_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("nL of Bu2Dst0hst_Dst02D0gamma " +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    3.6653e-01),  // 3.4, 0, 5),
      nRBu_Bu2Dst0hst_Dst02D0gamma_(("nRBu_Bu2Dst0hst_Dst02D0gamma_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("nR of Bu2Dst0hst_Dst02D0gamma " +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    5.1129e-01),  // 3.5, 0, 5),
      fracLRPdfBu_Bu2Dst0hst_Dst02D0gamma_(
          ("fracLRPdfBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of left w.r.t. right Bu PDF in Bu2Dst0hst_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.6816e-01),
      relativeBuWidth_Bu2Dst0hst_Dst02D0gamma_(
          ("relativeBuWidth_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in Bu2Dst0hst_Dst02D0gamma "
           "mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_(
          ("ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n Bu2Dst0hst_Dst02D0gamma "
           "mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.02, 0, 1),  //, 0.0, 0.1),
      // ------------------ MIS-RECONSTRUCTED BACKGROUND ------------------ //
      pdfDelta_misRec_(
          ("pdfDelta_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Delta_misRec PDF " + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          Configuration::Get().deltaMass(), thresholdDelta_bkg_, cDelta_bkg_,
          aDelta_bkg_, bDelta_bkg_),
      a0Mean1Bu_misRec_(
          ("a0Mean1Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 of mean1 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.2058e+03),
      a1Mean1Bu_misRec_(
          ("a1Mean1Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a1 of mean1 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -4.3289e-02),
      a2Mean1Bu_misRec_(
          ("a2Mean1Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a2 of mean1 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          8.2392e-03),
      mean1Bu_misRec_(
          ("mean1Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean1 of misRec m[Bu]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0Mean1Bu_misRec_, a1Mean1Bu_misRec_, a2Mean1Bu_misRec_)),
      a0Mean2Bu_misRec_(
          ("a0Mean2Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 of mean2 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.3652e+03),
      a1Mean2Bu_misRec_(
          ("a1Mean2Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a1 of mean2 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.4674e-01),
      a2Mean2Bu_misRec_(
          ("a2Mean2Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a2 of mean2 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          8.3082e-03),
      mean2Bu_misRec_(
          ("mean2Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean2 of misRec m[Bu]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0Mean2Bu_misRec_, a1Mean2Bu_misRec_, a2Mean2Bu_misRec_)),
      a0Mean3Bu_misRec_(
          ("a0Mean3Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 of mean2 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.0854e+03),
      a1Mean3Bu_misRec_(
          ("a1Mean3Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a1 of mean2 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.9793e+00),
      a2Mean3Bu_misRec_(
          ("a2Mean3Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a2 of mean2 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -5.5658e-03),
      mean3Bu_misRec_(
          ("mean3Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean2 of misRec m[Bu]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0Mean3Bu_misRec_, a1Mean3Bu_misRec_, a2Mean3Bu_misRec_)),
      a0Sigma1Bu_misRec_(
          ("a0Sigma1Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma1 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -3.3548e+01),
      a1Sigma1Bu_misRec_(
          ("a1Sigma1Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma1 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          7.0068e-01),
      a2Sigma1Bu_misRec_(
          ("a2Sigma1Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma1 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -8.3490e-04),
      a0Sigma2Bu_misRec_(
          ("a0Sigma2Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma2 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.3523e+01),
      a1Sigma2Bu_misRec_(
          ("a1Sigma2Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma2 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -2.6007e-01),
      a2Sigma2Bu_misRec_(
          ("a2Sigma2Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma2 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -2.3067e-02),
      a0Sigma3Bu_misRec_(
          ("a0Sigma3Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma3 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.1908e+01),
      a1Sigma3Bu_misRec_(
          ("a1Sigma3Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma3 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.8331e-01),
      a2Sigma3Bu_misRec_(
          ("a2Sigma3Bu_misRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma3 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.0471e-03),
      frac1PdfBu_misRec_(
          ("frac1PdfBu_misRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of 1st CB Bu PDF in misRec " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          9.2004e-02),
      frac2PdfBu_misRec_(
          ("frac2PdfBu_misRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of 2nd CB Bu PDF in misRec " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3.4431e-04),
      frac3PdfBu_misRec_(
          ("frac3PdfBu_misRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of 3rd CB Bu PDF in misRec " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "1-(@0+@1)", RooArgList(frac1PdfBu_misRec_, frac2PdfBu_misRec_)),
      relativeBuWidth_misRec_(
          ("relativeBuWidth_misRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in misRec "
           "mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1),
      ratioDst0KDst0pi_misRec_(
          ("ratioDst0KDst0pi_misRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n misRec mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.05, 0, 0.1),
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
