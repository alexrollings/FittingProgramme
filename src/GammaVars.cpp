#include "GlobalVars.h"
#include "NeutralVars.h"

// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::gamma>::NeutralVars(int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : Bu2Dst0h_Dst02D0gamma_meanDelta_(
          ("Bu2Dst0h_Dst02D0gamma_meanDelta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Mean of Bu2Dst0h_Dst02D0gamma m[Delta]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.4219e+02),
      Bu2Dst0h_Dst02D0gamma_sigma1Delta_(
          ("Bu2Dst0h_Dst02D0gamma_sigma1Delta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Sigma left of Bu2Dst0h_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          9.0429e+00),
      Bu2Dst0h_Dst02D0gamma_sigma2Delta_(
          ("Bu2Dst0h_Dst02D0gamma_sigma2Delta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Sigma right of Bu2Dst0h_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          7.9534e+00),
      Bu2Dst0h_Dst02D0gamma_a1Delta_(("Bu2Dst0h_Dst02D0gamma_a1Delta_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("a1 of Bu2Dst0h_Dst02D0gamma " +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     2.0251e+00),
      Bu2Dst0h_Dst02D0gamma_a2Delta_(("Bu2Dst0h_Dst02D0gamma_a2Delta_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("a2 of Bu2Dst0h_Dst02D0gamma " +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     -5.9224e-01),
      Bu2Dst0h_Dst02D0gamma_n1Delta_(("Bu2Dst0h_Dst02D0gamma_n1Delta_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("n1 of Bu2Dst0h_Dst02D0gamma " +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     3.0344e+00),
      Bu2Dst0h_Dst02D0gamma_n2Delta_(("Bu2Dst0h_Dst02D0gamma_n2Delta_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("n2 of Bu2Dst0h_Dst02D0gamma " +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     4.8427e+00),
      pdf1Delta_Bu2Dst0h_Dst02D0gamma_(
          ("pdf1Delta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Delta left PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0gamma_meanDelta_,
          Bu2Dst0h_Dst02D0gamma_sigma1Delta_, Bu2Dst0h_Dst02D0gamma_a1Delta_,
          Bu2Dst0h_Dst02D0gamma_n1Delta_),
      pdf2Delta_Bu2Dst0h_Dst02D0gamma_(
          ("pdf2Delta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Delta right PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0gamma_meanDelta_,
          Bu2Dst0h_Dst02D0gamma_sigma2Delta_, Bu2Dst0h_Dst02D0gamma_a2Delta_,
          Bu2Dst0h_Dst02D0gamma_n2Delta_),
      Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_(
          ("Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of left w.r.t. right PDF in Bu2Dst0h_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.7402e-01),
      Bu2Dst0h_Dst02D0gamma_thresholdDelta_(),
      Bu2Dst0h_Dst02D0gamma_aDelta_(),
      Bu2Dst0h_Dst02D0gamma_bDelta_(),
      Bu2Dst0h_Dst02D0gamma_cDelta_(),
      pdfDelta_Bu2Dst0h_Dst02D0gamma_(new RooAddPdf(
          ("pdfDelta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          RooArgList(pdf1Delta_Bu2Dst0h_Dst02D0gamma_,
                     pdf2Delta_Bu2Dst0h_Dst02D0gamma_),
          Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_)),
      Bu2Dst0h_Dst02D0gamma_a0MeanBu_(
          ("Bu2Dst0h_Dst02D0gamma_a0MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.9983e+03),
      Bu2Dst0h_Dst02D0gamma_a1MeanBu_(
          ("Bu2Dst0h_Dst02D0gamma_a1MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.3119e+00),
      Bu2Dst0h_Dst02D0gamma_a2MeanBu_(
          ("Bu2Dst0h_Dst02D0gamma_a2MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -2.3978e-03),
      Bu2Dst0h_Dst02D0gamma_meanBu_(
          ("Bu2Dst0h_Dst02D0gamma_meanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Mean of Bu2Dst0h_Dst02D0gamma m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(Bu2Dst0h_Dst02D0gamma_a0MeanBu_,
                     Bu2Dst0h_Dst02D0gamma_a1MeanBu_,
                     Bu2Dst0h_Dst02D0gamma_a2MeanBu_)),
      Bu2Dst0h_Dst02D0gamma_a0Sigma1Bu_(
          ("Bu2Dst0h_Dst02D0gamma_a0Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma1 of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.9764e+00),
      Bu2Dst0h_Dst02D0gamma_a1Sigma1Bu_(
          ("Bu2Dst0h_Dst02D0gamma_a1Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma1 of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.4775e-01),
      Bu2Dst0h_Dst02D0gamma_a2Sigma1Bu_(
          ("Bu2Dst0h_Dst02D0gamma_a2Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma1 of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -5.0502e-04),
      Bu2Dst0h_Dst02D0gamma_a0Sigma2Bu_(
          ("Bu2Dst0h_Dst02D0gamma_a0Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma2 of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.3464e+02),
      Bu2Dst0h_Dst02D0gamma_a1Sigma2Bu_(
          ("Bu2Dst0h_Dst02D0gamma_a1Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma2 of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.7163e+00),
      Bu2Dst0h_Dst02D0gamma_a2Sigma2Bu_(
          ("Bu2Dst0h_Dst02D0gamma_a2Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma2 of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          6.0422e-03),
      Bu2Dst0h_Dst02D0gamma_a1Bu_(("Bu2Dst0h_Dst02D0gamma_a1Bu_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("a1 of Bu2Dst0h_Dst02D0gamma " +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  2.2666e+00),
      Bu2Dst0h_Dst02D0gamma_a2Bu_(("Bu2Dst0h_Dst02D0gamma_a2Bu_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("a2 of Bu2Dst0h_Dst02D0gamma " +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  -9.3624e-01),
      Bu2Dst0h_Dst02D0gamma_n1Bu_(("Bu2Dst0h_Dst02D0gamma_n1Bu_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("n1 of Bu2Dst0h_Dst02D0gamma " +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  5.6139e-04),
      Bu2Dst0h_Dst02D0gamma_n2Bu_(("Bu2Dst0h_Dst02D0gamma_n2Bu_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("n2 of Bu2Dst0h_Dst02D0gamma " +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  2.4093e+01),
      Bu2Dst0h_Dst02D0gamma_frac1PdfBu_(
          ("Bu2Dst0h_Dst02D0gamma_frac1PdfBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of left w.r.t. right Bu PDF in Bu2Dst0h_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          8.0963e-02),
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
                                      8.6718e+01),
      Bu2Dst0h_Dst02D0pi0_sigma1Delta_(("Bu2Dst0h_Dst02D0pi0_sigma1Delta_" +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       ("Sigma left of Bu2Dst0h_Dst02D0pi0 " +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       6.2624e+00),
      Bu2Dst0h_Dst02D0pi0_sigma2Delta_(("Bu2Dst0h_Dst02D0pi0_sigma2Delta_" +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       ("Sigma right of Bu2Dst0h_Dst02D0pi0 " +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       1.5908e+01),
      Bu2Dst0h_Dst02D0pi0_a1Delta_(
          ("Bu2Dst0h_Dst02D0pi0_a1Delta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.8776e+00),
      Bu2Dst0h_Dst02D0pi0_a2Delta_(
          ("Bu2Dst0h_Dst02D0pi0_a2Delta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -8.2594e-01),
      Bu2Dst0h_Dst02D0pi0_n1Delta_(
          ("Bu2Dst0h_Dst02D0pi0_n1Delta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("n1 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          7.4043e+00),
      Bu2Dst0h_Dst02D0pi0_n2Delta_(
          ("Bu2Dst0h_Dst02D0pi0_n2Delta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("n2 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          9.9793e+00),
      pdf1Delta_Bu2Dst0h_Dst02D0pi0_(
          ("pdf1Delta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Delta left PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0pi0_meanDelta_,
          Bu2Dst0h_Dst02D0pi0_sigma1Delta_, Bu2Dst0h_Dst02D0pi0_a1Delta_,
          Bu2Dst0h_Dst02D0pi0_n1Delta_),
      pdf2Delta_Bu2Dst0h_Dst02D0pi0_(
          ("pdf2Delta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Delta right PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0pi0_meanDelta_,
          Bu2Dst0h_Dst02D0pi0_sigma2Delta_, Bu2Dst0h_Dst02D0pi0_a2Delta_,
          Bu2Dst0h_Dst02D0pi0_n2Delta_),
      Bu2Dst0h_Dst02D0pi0_frac1PdfDelta_(
          ("Bu2Dst0h_Dst02D0pi0_frac1PdfDelta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of left w.r.t. right PDF in Bu2Dst0h_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.0321e-01),
      pdfDelta_Bu2Dst0h_Dst02D0pi0_(("pdfDelta_Bu2Dst0h_Dst02D0pi0_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("Bu2Dst0h_Dst02D0pi0 Delta PDF " +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    RooArgList(pdf1Delta_Bu2Dst0h_Dst02D0pi0_,
                                               pdf2Delta_Bu2Dst0h_Dst02D0pi0_),
                                    Bu2Dst0h_Dst02D0pi0_frac1PdfDelta_),
      Bu2Dst0h_Dst02D0pi0_a0Mean1Bu_(("Bu2Dst0h_Dst02D0pi0_a0Mean1Bu_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a0 of mean1 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    5.3105e+03),
      Bu2Dst0h_Dst02D0pi0_a1Mean1Bu_(("Bu2Dst0h_Dst02D0pi0_a1Mean1Bu_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a1 of mean1 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    -2.3015e+00),
      Bu2Dst0h_Dst02D0pi0_a2Mean1Bu_(("Bu2Dst0h_Dst02D0pi0_a2Mean1Bu_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a2 of mean1 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    1.6305e-02),
      Bu2Dst0h_Dst02D0pi0_mean1Bu_(("Bu2Dst0h_Dst02D0pi0_mean1Bu_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("Mean1 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  Configuration::Get().deltaMass(),
                                  RooArgList(Bu2Dst0h_Dst02D0pi0_a0Mean1Bu_,
                                             Bu2Dst0h_Dst02D0pi0_a1Mean1Bu_,
                                             Bu2Dst0h_Dst02D0pi0_a2Mean1Bu_)),
      Bu2Dst0h_Dst02D0pi0_a0Mean2Bu_(("Bu2Dst0h_Dst02D0pi0_a0Mean2Bu_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a0 of mean2 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    4.9887e+03),
      Bu2Dst0h_Dst02D0pi0_a1Mean2Bu_(("Bu2Dst0h_Dst02D0pi0_a1Mean2Bu_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a1 of mean2 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    3.3648e+00),
      Bu2Dst0h_Dst02D0pi0_a2Mean2Bu_(("Bu2Dst0h_Dst02D0pi0_a2Mean2Bu_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a2 of mean2 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    -5.8020e-03),
      Bu2Dst0h_Dst02D0pi0_mean2Bu_(("Bu2Dst0h_Dst02D0pi0_mean2Bu_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("Mean2 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  Configuration::Get().deltaMass(),
                                  RooArgList(Bu2Dst0h_Dst02D0pi0_a0Mean2Bu_,
                                             Bu2Dst0h_Dst02D0pi0_a1Mean2Bu_,
                                             Bu2Dst0h_Dst02D0pi0_a2Mean2Bu_)),
      Bu2Dst0h_Dst02D0pi0_a0Sigma1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a0Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma1 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.3498e-02),
      Bu2Dst0h_Dst02D0pi0_a1Sigma1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a1Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma1 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          7.4321e-01),
      Bu2Dst0h_Dst02D0pi0_a2Sigma1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a2Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma1 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -2.3555e-03),
      Bu2Dst0h_Dst02D0pi0_a0Sigma2Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a0Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma2 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.0462e+02),
      Bu2Dst0h_Dst02D0pi0_a1Sigma2Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a1Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma2 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -3.8000e+00),
      Bu2Dst0h_Dst02D0pi0_a2Sigma2Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a2Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma2 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.9690e-02),
      Bu2Dst0h_Dst02D0pi0_a1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.1782e+00),
      Bu2Dst0h_Dst02D0pi0_a2Bu_(),
      Bu2Dst0h_Dst02D0pi0_n1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_n1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("n1 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3.9931e-01),
      Bu2Dst0h_Dst02D0pi0_n2Bu_(),
      Bu2Dst0h_Dst02D0pi0_frac1PdfBu_(
          ("Bu2Dst0h_Dst02D0pi0_frac1PdfBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of left w.r.t. right Bu PDF in Bu2Dst0h_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          6.6231e-01),
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
      bkg_thresholdDelta_(
          ("bkg_thresholdDelta_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          (" Delta_bkg thershold " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.2160e+01),
      bkg_cDelta_(
          ("bkg_cDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          (" Delta_bkg c parameter " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.2450e+01),
      bkg_aDelta_(
          ("bkg_aDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          (" Delta_bkg a parameter " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.0341e+00),
      bkg_bDelta_(
          ("bkg_bDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          (" Delta_bkg b parameter " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.2284e+00),
      // ------------------ OVER RECONSTRUCTED BACKGROUND ------------------ //
      pdfDelta_overRec_(
          ("pdfDelta_overRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Delta_overRec PDF " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), bkg_thresholdDelta_, bkg_cDelta_,
          bkg_aDelta_, bkg_bDelta_),
      overRec_a0Mean1Bu_(
          ("overRec_a0Mean1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean1 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.2022e+03),
      overRec_a1Mean1Bu_(
          ("overRec_a1Mean1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean1 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.4709e+00),
      overRec_a2Mean1Bu_(
          ("overRec_a2Mean1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean1 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.2101e-02),
      overRec_mean1Bu_(
          ("overRec_mean1Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean1 of overRec m[Bu]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(overRec_a0Mean1Bu_, overRec_a1Mean1Bu_,
                     overRec_a2Mean1Bu_)),
      overRec_a0Mean2Bu_(
          ("overRec_a0Mean2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean2 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.3536e+03),
      overRec_a1Mean2Bu_(
          ("overRec_a1Mean2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean2 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.5054e+00),
      overRec_a2Mean2Bu_(
          ("overRec_a2Mean2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean2 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -3.7428e-03),
      overRec_mean2Bu_(
          ("overRec_mean2Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean2 of overRec m[Bu]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(overRec_a0Mean2Bu_, overRec_a1Mean2Bu_,
                     overRec_a2Mean2Bu_)),
      overRec_a0Sigma1Bu_(
          ("overRec_a0Sigma1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma1 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.3696e+01),
      overRec_a1Sigma1Bu_(
          ("overRec_a1Sigma1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma1 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -3.5232e-01),
      overRec_a2Sigma1Bu_(
          ("overRec_a2Sigma1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma1 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3.6077e-03),
      overRec_a0Sigma2Bu_(
          ("overRec_a0Sigma2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma2 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.6106e+01),
      overRec_a1Sigma2Bu_(
          ("overRec_a1Sigma2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma2 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          7.1468e-01),
      overRec_a2Sigma2Bu_(
          ("overRec_a2Sigma2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma2 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.4613e-03),
      overRec_a1Bu_(
          ("overRec_a1Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a1 of overRec " + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          2.7665e+00),
      overRec_a2Bu_(),
      overRec_n1Bu_(
          ("overRec_n1Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("n1 of overRec " + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          1.4306e-06),
      overRec_n2Bu_(),
      overRec_frac1PdfBu_(
          ("overRec_frac1PdfBu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of left w.r.t. right Bu PDF in overRec " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.4483e-01),
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
          0.07768),
      // -------------------- Pi0 PART RECONSTRUCTED BKG --------------------
      Bu2Dst0hst_Dst02D0pi0_meanDelta_(("Bu2Dst0hst_Dst02D0pi0_meanDelta_" +
                                       ComposeName(uniqueId, Neutral::gamma))
                                          .c_str(),
                                      ("Mean of Bu2Dst0hst_Dst02D0pi0 m[Delta]" +
                                       ComposeName(uniqueId, Neutral::gamma))
                                          .c_str(),
                                      9.2966e+01),
      pdf1Delta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdf1Delta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Delta left PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0hst_Dst02D0pi0_meanDelta_,
          Bu2Dst0h_Dst02D0pi0_sigma1Delta_, Bu2Dst0h_Dst02D0pi0_a1Delta_,
          Bu2Dst0h_Dst02D0pi0_n1Delta_),
      pdf2Delta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdf2Delta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Delta right PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0pi0_meanDelta_,
          Bu2Dst0h_Dst02D0pi0_sigma2Delta_, Bu2Dst0h_Dst02D0pi0_a2Delta_,
          Bu2Dst0h_Dst02D0pi0_n2Delta_),
      pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 peaking Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          RooArgList(pdf1Delta_Bu2Dst0hst_Dst02D0pi0_,
                     pdf2Delta_Bu2Dst0hst_Dst02D0pi0_),
          Bu2Dst0h_Dst02D0pi0_frac1PdfDelta_),
      pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Delta_Bu2Dst0hst_Dst02D0pi0 flat Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), bkg_thresholdDelta_, bkg_cDelta_,
          bkg_aDelta_, bkg_bDelta_),
      Bu2Dst0hst_Dst02D0pi0_fracPdfPeakDelta_(
          ("Bu2Dst0hst_Dst02D0pi0_fracPdfPeakDelta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of peak pdf w.r.t. peaking pdf for partially "
           "reconstructed bkg " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          8.5481e-01),
      pdfDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          RooArgSet(pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0_,
                    pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_),
          Bu2Dst0hst_Dst02D0pi0_fracPdfPeakDelta_),
      Bu2Dst0hst_Dst02D0pi0_a0MeanBu_(
          ("Bu2Dst0hst_Dst02D0pi0_a0MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.0126e+03),
      // Bu2Dst0hst_Dst02D0pi0_a1MeanBu_(),
      Bu2Dst0hst_Dst02D0pi0_a1MeanBu_(
          ("Bu2Dst0hst_Dst02D0pi0_a1MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.2402e-02),
      // Bu2Dst0hst_Dst02D0pi0_a2MeanBu_(
      //     ("Bu2Dst0hst_Dst02D0pi0_a2MeanBu_" +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     ("a2 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     -1.4359e-02),
      Bu2Dst0hst_Dst02D0pi0_meanBu_(
          ("Bu2Dst0hst_Dst02D0pi0_meanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Mean of Bu2Dst0hst_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(Bu2Dst0hst_Dst02D0pi0_a0MeanBu_,
                     Bu2Dst0hst_Dst02D0pi0_a1MeanBu_)),
      // Bu2Dst0hst_Dst02D0pi0_a2MeanBu_)),
      Bu2Dst0hst_Dst02D0pi0_a0Sigma1Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_a0Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma1 of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.9718e+01),
      Bu2Dst0hst_Dst02D0pi0_a1Sigma1Bu_(),
      Bu2Dst0hst_Dst02D0pi0_a0Sigma2Bu_(),
      Bu2Dst0hst_Dst02D0pi0_a1Sigma2Bu_(),
      // Bu2Dst0hst_Dst02D0pi0_a1Sigma1Bu_(
      //     ("Bu2Dst0hst_Dst02D0pi0_a1Sigma1Bu_" +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     ("a1 of sigma1 of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     7.8205e-02),
      // Bu2Dst0hst_Dst02D0pi0_a2Sigma1Bu_(
      //     ("Bu2Dst0hst_Dst02D0pi0_a2Sigma1Bu_" +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     ("a2 of sigma1 of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     3.1524e-03),
      // Bu2Dst0hst_Dst02D0pi0_a0Sigma2Bu_(
      //     ("Bu2Dst0hst_Dst02D0pi0_a0Sigma2Bu_" +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     ("a0 of sigma2 of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     9.8039e+01),
      // Bu2Dst0hst_Dst02D0pi0_a1Sigma2Bu_(
      //     ("Bu2Dst0hst_Dst02D0pi0_a1Sigma2Bu_" +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     ("a1 of sigma2 of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     -7.1628e-01),
      // Bu2Dst0hst_Dst02D0pi0_a2Sigma2Bu_(
      //     ("Bu2Dst0hst_Dst02D0pi0_a2Sigma2Bu_" +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     ("a2 of sigma2 of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     4.3805e-03),
      Bu2Dst0hst_Dst02D0pi0_a1Bu_(),
      Bu2Dst0hst_Dst02D0pi0_a2Bu_(),
      // Bu2Dst0hst_Dst02D0pi0_a2Bu_(
      //     ("Bu2Dst0hst_Dst02D0pi0_a2Bu_" + ComposeName(uniqueId,
      //     Neutral::gamma))
      //         .c_str(),
      //     ("a2 of Bu2Dst0hst_Dst02D0pi0 " + ComposeName(uniqueId,
      //     Neutral::gamma))
      //         .c_str(),
      //     4.2150e+00),
      Bu2Dst0hst_Dst02D0pi0_n1Bu_(),
      Bu2Dst0hst_Dst02D0pi0_n2Bu_(),
      // Bu2Dst0hst_Dst02D0pi0_n2Bu_(
      //     ("Bu2Dst0hst_Dst02D0pi0_n2Bu_" + ComposeName(uniqueId,
      //     Neutral::gamma))
      //         .c_str(),
      //     ("n2 of Bu2Dst0hst_Dst02D0pi0 " + ComposeName(uniqueId,
      //     Neutral::gamma))
      //         .c_str(),
      //     4.3416e+01),
      // Bu2Dst0hst_Dst02D0pi0_frac1PdfBu_(
      //     ("Bu2Dst0hst_Dst02D0pi0_frac1PdfBu_" +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     ("Fraction of left w.r.t. right Bu PDF in Bu2Dst0hst_Dst02D0pi0 " +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     1.0890e-07),
      Bu2Dst0hst_Dst02D0pi0_frac1PdfBu_(),
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
          1.4348e+02),
      pdf1Delta_Bu2Dst0hst_Dst02D0gamma_(
          ("pdf1Delta_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Delta left PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0hst_Dst02D0gamma_meanDelta_,
          Bu2Dst0h_Dst02D0gamma_sigma1Delta_, Bu2Dst0h_Dst02D0gamma_a1Delta_,
          Bu2Dst0h_Dst02D0gamma_n1Delta_),
      pdf2Delta_Bu2Dst0hst_Dst02D0gamma_(
          ("pdf2Delta_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Delta right PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0hst_Dst02D0gamma_meanDelta_,
          Bu2Dst0h_Dst02D0gamma_sigma2Delta_, Bu2Dst0h_Dst02D0gamma_a2Delta_,
          Bu2Dst0h_Dst02D0gamma_n2Delta_),
      pdfDelta_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfDelta_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          RooArgList(pdf1Delta_Bu2Dst0hst_Dst02D0gamma_,
                     pdf2Delta_Bu2Dst0hst_Dst02D0gamma_),
          Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_),
      Bu2Dst0hst_Dst02D0gamma_a0MeanBu_(
          ("Bu2Dst0hst_Dst02D0gamma_a0MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.8874e+03),
      Bu2Dst0hst_Dst02D0gamma_a1MeanBu_(
          ("Bu2Dst0hst_Dst02D0gamma_a1MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.1719e+00),
      Bu2Dst0hst_Dst02D0gamma_a2MeanBu_(
          ("Bu2Dst0hst_Dst02D0gamma_a2MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.0825e-03),
      Bu2Dst0hst_Dst02D0gamma_meanBu_(
          ("Bu2Dst0hst_Dst02D0gamma_meanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Mean of Bu2Dst0hst_Dst02D0gamma m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(Bu2Dst0hst_Dst02D0gamma_a0MeanBu_,
                     Bu2Dst0hst_Dst02D0gamma_a1MeanBu_,
                     Bu2Dst0hst_Dst02D0gamma_a2MeanBu_)),
      Bu2Dst0hst_Dst02D0gamma_a0Sigma1Bu_(
          ("Bu2Dst0hst_Dst02D0gamma_a0Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma1 of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.0003e+01),
      Bu2Dst0hst_Dst02D0gamma_a1Sigma1Bu_(
          ("Bu2Dst0hst_Dst02D0gamma_a1Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma1 of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3.1199e-01),
      Bu2Dst0hst_Dst02D0gamma_a2Sigma1Bu_(
          ("Bu2Dst0hst_Dst02D0gamma_a2Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma1 of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -5.5687e-04),
      // Bu2Dst0hst_Dst02D0gamma_a0Sigma2Bu_(
      //     ("Bu2Dst0hst_Dst02D0gamma_a0Sigma2Bu_" +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     ("a0 of sigma2 of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     5.8658e+01),
      // Bu2Dst0hst_Dst02D0gamma_a1Sigma2Bu_(
      //     ("Bu2Dst0hst_Dst02D0gamma_a1Sigma2Bu_" +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     ("a1 of sigma2 of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     -2.1932e-01),
      // Bu2Dst0hst_Dst02D0gamma_a2Sigma2Bu_(
      //     ("Bu2Dst0hst_Dst02D0gamma_a2Sigma2Bu_" +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     ("a2 of sigma2 of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     1.4876e-03),
      Bu2Dst0hst_Dst02D0gamma_a1Bu_(("Bu2Dst0hst_Dst02D0gamma_a1Bu_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a1 of Bu2Dst0hst_Dst02D0gamma " +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    5.2322e-01),
      // Bu2Dst0hst_Dst02D0gamma_a2Bu_(("Bu2Dst0hst_Dst02D0gamma_a2Bu_" +
      //                                ComposeName(uniqueId, Neutral::gamma))
      //                                   .c_str(),
      //                               ("a2 of Bu2Dst0hst_Dst02D0gamma " +
      //                                ComposeName(uniqueId, Neutral::gamma))
      //                                   .c_str(),
      //                               -3.0000e+00),
      Bu2Dst0hst_Dst02D0gamma_n1Bu_(("Bu2Dst0hst_Dst02D0gamma_n1Bu_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("n1 of Bu2Dst0hst_Dst02D0gamma " +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    9.9998e+00),
      // Bu2Dst0hst_Dst02D0gamma_n2Bu_(("Bu2Dst0hst_Dst02D0gamma_n2Bu_" +
      //                                ComposeName(uniqueId, Neutral::gamma))
      //                                   .c_str(),
      //                               ("n2 of Bu2Dst0hst_Dst02D0gamma " +
      //                                ComposeName(uniqueId, Neutral::gamma))
      //                                   .c_str(),
      //                               5.1129e-01),
      // Bu2Dst0hst_Dst02D0gamma_frac1PdfBu_(
      //     ("Bu2Dst0hst_Dst02D0gamma_frac1PdfBu_" +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     ("Fraction of left w.r.t. right Bu PDF in Bu2Dst0hst_Dst02D0gamma "
      //     +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     2.6816e-01),
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
      misRec_thresholdDelta_(),
      misRec_aDelta_(),
      misRec_bDelta_(),
      misRec_cDelta_(),
      pdfDelta_misRec_(
          ("pdfDelta_misRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Delta_misRec PDF " + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          Configuration::Get().deltaMass(), bkg_thresholdDelta_, bkg_cDelta_,
          bkg_aDelta_, bkg_bDelta_),
      misRec_a0Mean1Bu_(
          ("misRec_a0Mean1Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 of mean1 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.1137e+03),
      misRec_a1Mean1Bu_(
          ("misRec_a1Mean1Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a1 of mean1 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.9263e+00),
      misRec_a2Mean1Bu_(
          ("misRec_a2Mean1Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a2 of mean1 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -5.1276e-03),
      misRec_mean1Bu_(
          ("misRec_mean1Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean1 of misRec m[Bu]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(misRec_a0Mean1Bu_, misRec_a1Mean1Bu_, misRec_a2Mean1Bu_)),
      misRec_a0Mean2Bu_(),
      misRec_mean2Bu_(),
      misRec_a0Sigma1Bu_(
          ("misRec_a0Sigma1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma1 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.2908e+01),
      misRec_a1Sigma1Bu_(
          ("misRec_a1Sigma1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma1 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          9.6805e-01),
      misRec_a2Sigma1Bu_(
          ("misRec_a2Sigma1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma1 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.4419e-03),
      misRec_a0Sigma2Bu_(),
      misRec_a1Bu_(
          ("misRec_a1Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a1 of misRec " + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          1.1678e+00),
      misRec_a2Bu_(),
      misRec_n1Bu_(
          ("misRec_n1Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("n1 of misRec " + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          2.8331e+00),
      misRec_n2Bu_(),
      misRec_frac1PdfBu_(),
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
          Configuration::Get().deltaMass(), bkg_thresholdDelta_, bkg_cDelta_,
          bkg_aDelta_, bkg_bDelta_),
      // -------------------- EXPONENTIAL BACKGROUND -------------------- //
      Comb_a0LambdaBu_(
          ("Comb_a0LambdaBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 component for Bu _Combinatorial constant " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -0.001, -1, -0.00001),
      Comb_lambdaBu_(
          ("Comb_lambdaBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Bu _Combinatorial constant " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), RooArgSet(Comb_a0LambdaBu_)),
      pdfBu_Comb_(
          ("pdfBu_Comb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Bu_Combinatorial PDF " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().buMass(), Comb_lambdaBu_),
      pdf_Comb_(
          ("pdf_Comb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("_Combinatorial PDF " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          pdfDelta_Comb_,
          RooFit::Conditional(pdfBu_Comb_, Configuration::Get().buMass())) {}
