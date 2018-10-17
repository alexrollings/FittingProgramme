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
          1.4198e+02),
      Bu2Dst0h_Dst02D0gamma_sigma1Delta_(
          ("Bu2Dst0h_Dst02D0gamma_sigma1Delta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Sigma left of Bu2Dst0h_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.2632e+01),
      Bu2Dst0h_Dst02D0gamma_sigma2Delta_(
          ("Bu2Dst0h_Dst02D0gamma_sigma2Delta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Sigma right of Bu2Dst0h_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          8.4637e+00),
      Bu2Dst0h_Dst02D0gamma_a1Delta_(("Bu2Dst0h_Dst02D0gamma_a1Delta_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("a1 of Bu2Dst0h_Dst02D0gamma " +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     1.0007e+00),
      Bu2Dst0h_Dst02D0gamma_a2Delta_(("Bu2Dst0h_Dst02D0gamma_a2Delta_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("a2 of Bu2Dst0h_Dst02D0gamma " +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     -8.3151e-01),
      Bu2Dst0h_Dst02D0gamma_n1Delta_(("Bu2Dst0h_Dst02D0gamma_n1Delta_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("n1 of Bu2Dst0h_Dst02D0gamma " +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     9.2760e+01),
      Bu2Dst0h_Dst02D0gamma_n2Delta_(("Bu2Dst0h_Dst02D0gamma_n2Delta_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("n2 of Bu2Dst0h_Dst02D0gamma " +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     3.7703e+00),
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
          5.6359e-02),
      pdfDelta_Bu2Dst0h_Dst02D0gamma_(
          ("pdfDelta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          RooArgList(pdf1Delta_Bu2Dst0h_Dst02D0gamma_,
                     pdf2Delta_Bu2Dst0h_Dst02D0gamma_),
          Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_),
      Bu2Dst0h_Dst02D0gamma_a0MeanBu_(
          ("Bu2Dst0h_Dst02D0gamma_a0MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.0347e+03),
      Bu2Dst0h_Dst02D0gamma_a1MeanBu_(
          ("Bu2Dst0h_Dst02D0gamma_a1MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.9638e+00),
      Bu2Dst0h_Dst02D0gamma_a2MeanBu_(
          ("Bu2Dst0h_Dst02D0gamma_a2MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.7220e-03),
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
          7.9257e+01),
      Bu2Dst0h_Dst02D0gamma_a1Sigma1Bu_(
          ("Bu2Dst0h_Dst02D0gamma_a1Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma1 of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -7.6265e-01),
      Bu2Dst0h_Dst02D0gamma_a2Sigma1Bu_(
          ("Bu2Dst0h_Dst02D0gamma_a2Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma1 of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.9199e-03),
      Bu2Dst0h_Dst02D0gamma_a0Sigma2Bu_(
          ("Bu2Dst0h_Dst02D0gamma_a0Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma2 of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.2950e+02),
      Bu2Dst0h_Dst02D0gamma_a1Sigma2Bu_(
          ("Bu2Dst0h_Dst02D0gamma_a1Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma2 of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.6410e+00),
      Bu2Dst0h_Dst02D0gamma_a2Sigma2Bu_(
          ("Bu2Dst0h_Dst02D0gamma_a2Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma2 of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.7878e-03),
      Bu2Dst0h_Dst02D0gamma_a1Bu_(("Bu2Dst0h_Dst02D0gamma_a1Bu_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("a1 of Bu2Dst0h_Dst02D0gamma " +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  2.3741e+00),
      Bu2Dst0h_Dst02D0gamma_a2Bu_(("Bu2Dst0h_Dst02D0gamma_a2Bu_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("a2 of Bu2Dst0h_Dst02D0gamma " +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  -1.0153e+00),
      Bu2Dst0h_Dst02D0gamma_n1Bu_(("Bu2Dst0h_Dst02D0gamma_n1Bu_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("n1 of Bu2Dst0h_Dst02D0gamma " +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  2.0028e-07),
      Bu2Dst0h_Dst02D0gamma_n2Bu_(("Bu2Dst0h_Dst02D0gamma_n2Bu_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("n2 of Bu2Dst0h_Dst02D0gamma " +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  1.8493e+01),
      Bu2Dst0h_Dst02D0gamma_frac1PdfBu_(
          ("Bu2Dst0h_Dst02D0gamma_frac1PdfBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of left w.r.t. right Bu PDF in Bu2Dst0h_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.0453e-01),
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
      Bu2Dst0h_Dst02D0pi0_mean1Delta_(("Bu2Dst0h_Dst02D0pi0_mean1Delta_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("Mean1 of Bu2Dst0h_Dst02D0pi0 m[Delta]" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     8.4363e+01),
      Bu2Dst0h_Dst02D0pi0_mean2Delta_(("Bu2Dst0h_Dst02D0pi0_mean2Delta_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("Mean2 of Bu2Dst0h_Dst02D0pi0 m[Delta]" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     8.3496e+01),
      Bu2Dst0h_Dst02D0pi0_sigma1Delta_(("Bu2Dst0h_Dst02D0pi0_sigma1Delta_" +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       ("Sigma left of Bu2Dst0h_Dst02D0pi0 " +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       6.7633e+00),
      Bu2Dst0h_Dst02D0pi0_sigma2Delta_(("Bu2Dst0h_Dst02D0pi0_sigma2Delta_" +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       ("Sigma right of Bu2Dst0h_Dst02D0pi0 " +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       1.6300e+01),
      Bu2Dst0h_Dst02D0pi0_a1Delta_(
          ("Bu2Dst0h_Dst02D0pi0_a1Delta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3.1703e-01),
      Bu2Dst0h_Dst02D0pi0_a2Delta_(
          ("Bu2Dst0h_Dst02D0pi0_a2Delta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.0692e+00),
      Bu2Dst0h_Dst02D0pi0_n1Delta_(
          ("Bu2Dst0h_Dst02D0pi0_n1Delta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("n1 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          9.9976e+00),
      Bu2Dst0h_Dst02D0pi0_n2Delta_(
          ("Bu2Dst0h_Dst02D0pi0_n2Delta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("n2 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          6.7356e+00),
      pdf1Delta_Bu2Dst0h_Dst02D0pi0_(
          ("pdf1Delta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Delta left PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0pi0_mean1Delta_,
          Bu2Dst0h_Dst02D0pi0_sigma1Delta_, Bu2Dst0h_Dst02D0pi0_a1Delta_,
          Bu2Dst0h_Dst02D0pi0_n1Delta_),
      pdf2Delta_Bu2Dst0h_Dst02D0pi0_(
          ("pdf2Delta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Delta right PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0pi0_mean2Delta_,
          Bu2Dst0h_Dst02D0pi0_sigma2Delta_, Bu2Dst0h_Dst02D0pi0_a2Delta_,
          Bu2Dst0h_Dst02D0pi0_n2Delta_),
      Bu2Dst0h_Dst02D0pi0_frac1PdfDelta_(
          ("Bu2Dst0h_Dst02D0pi0_frac1PdfDelta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of left w.r.t. right PDF in Bu2Dst0h_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3.6573e-01),
      pdfDelta_Bu2Dst0h_Dst02D0pi0_(("pdfDelta_Bu2Dst0h_Dst02D0pi0_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("Bu2Dst0h_Dst02D0pi0 Delta PDF " +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    RooArgList(pdf1Delta_Bu2Dst0h_Dst02D0pi0_,
                                               pdf2Delta_Bu2Dst0h_Dst02D0pi0_),
                                    Bu2Dst0h_Dst02D0pi0_frac1PdfDelta_),
      Bu2Dst0h_Dst02D0pi0_a0MeanBu_(
          ("Bu2Dst0h_Dst02D0pi0_a0MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.1955e+03),
      Bu2Dst0h_Dst02D0pi0_a1MeanBu_(
          ("Bu2Dst0h_Dst02D0pi0_a1MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -6.1038e-01),
      Bu2Dst0h_Dst02D0pi0_a2MeanBu_(
          ("Bu2Dst0h_Dst02D0pi0_a2MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.1671e-02),
      Bu2Dst0h_Dst02D0pi0_meanBu_(("Bu2Dst0h_Dst02D0pi0_meanBu_" +
                                    ComposeName(uniqueId, Neutral::gamma))
                                       .c_str(),
                                   ("Mean of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                    ComposeName(uniqueId, Neutral::gamma))
                                       .c_str(),
                                   Configuration::Get().deltaMass(),
                                   RooArgList(Bu2Dst0h_Dst02D0pi0_a0MeanBu_,
                                              Bu2Dst0h_Dst02D0pi0_a1MeanBu_,
                                              Bu2Dst0h_Dst02D0pi0_a2MeanBu_)),
      Bu2Dst0h_Dst02D0pi0_a0Sigma1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a0Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma1 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.6147e+02),
      Bu2Dst0h_Dst02D0pi0_a1Sigma1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a1Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma1 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -2.9402e+00),
      Bu2Dst0h_Dst02D0pi0_a2Sigma1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a2Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma1 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.6005e-02),
      Bu2Dst0h_Dst02D0pi0_a0Sigma2Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a0Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma2 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.5582e+02),
      Bu2Dst0h_Dst02D0pi0_a1Sigma2Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a1Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma2 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -2.7101e+00),
      Bu2Dst0h_Dst02D0pi0_a2Sigma2Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a2Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma2 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.5196e-02),
      Bu2Dst0h_Dst02D0pi0_a1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          8.1271e-01),
      Bu2Dst0h_Dst02D0pi0_a2Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.3363e+00),
      Bu2Dst0h_Dst02D0pi0_n1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_n1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("n1 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          9.9810e+01),
      Bu2Dst0h_Dst02D0pi0_n2Bu_(
          ("Bu2Dst0h_Dst02D0pi0_n2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("n2 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          9.8572e+01),
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
          // 43),
          48),
      bkg_cDelta_(
          ("bkg_cDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          (" Delta_bkg c parameter " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 10, 0.001, 20),
          // 29, 0, 35),
          5.0179e+01),
      bkg_aDelta_(
          ("bkg_aDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          (" Delta_bkg a parameter " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // -0.5, -1, 1),
          // -0.044, -1, 1),
          9.2245e-01),
      bkg_bDelta_(
          ("bkg_bDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
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
          Configuration::Get().deltaMass(), bkg_thresholdDelta_, bkg_cDelta_,
          bkg_aDelta_, bkg_bDelta_),
      // overRec_a0MeanBu_(
      //     ("overRec_a0MeanBu_" + ComposeName(uniqueId,
      //     Neutral::gamma)).c_str(),
      //     ("a0 of mean of overRec m[Bu] PDF " +
      //      ComposeName(uniqueId, Neutral::gamma))
      //         .c_str(),
      //     // 5400, 5350, 5450),
      //     5400, 5350, 5450),
      // overRec_meanBu_(
      //     ("overRec_meanBu_" + ComposeName(uniqueId,
      //     Neutral::gamma)).c_str(), Configuration::Get().deltaMass(),
      //     RooArgList(overRec_a0MeanBu_)),
      overRec_a0Mean1Bu_(
          ("overRec_a0Mean1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean1 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 5030, 4950, 5550),
          5.2641e+03),
      overRec_a1Mean1Bu_(
          ("overRec_a1Mean1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean1 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 3, 0, 10),
          3.2770e+00),
      overRec_a2Mean1Bu_(
          ("overRec_a2Mean1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean1 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // -0.007, -0.1, 0.1),
          -8.1688e-03),
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
          // 5030, 4950, 5550),
          5.4396e+03),
      overRec_a1Mean2Bu_(
          ("overRec_a1Mean2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean2 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 3, 0, 10),
          -1.4957e-02),
      overRec_a2Mean2Bu_(
          ("overRec_a2Mean2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean2 of overRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // -0.007, -0.1, 0.1),
          5.8425e-04),
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
          // 32, -100, 100),
          4.5119e+00),
      overRec_a1Sigma1Bu_(
          ("overRec_a1Sigma1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma1 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 0.09, -10, 10),
          1.2461e-01),
      overRec_a2Sigma1Bu_(
          ("overRec_a2Sigma1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma1 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 0.0036, -0.01, 0.01),
          1.8108e-03),
      overRec_a0Sigma2Bu_(
          ("overRec_a0Sigma2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma2 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.0667e+01),
      overRec_a1Sigma2Bu_(
          ("overRec_a1Sigma2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma2 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          7.5421e-01),
      overRec_a2Sigma2Bu_(
          ("overRec_a2Sigma2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma2 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -2.2312e-03),
      overRec_a1Bu_(
          ("overRec_a1Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a1 of overRec " + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          3.7878e+00),  // 2.3, 0, 5),
      overRec_a2Bu_(
          ("overRec_a2Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a2 of overRec " + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          -3.1173e+00),  // 4.6, 0, 5),
      overRec_n1Bu_(
          ("overRec_n1Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("n1 of overRec " + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          2.7083e+00),  // 3.4, 0, 5),
      overRec_n2Bu_(
          ("overRec_n2Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("n2 of overRec " + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          3.7229e+01),  // 3.5, 0, 5),
      overRec_frac1PdfBu_(
          ("overRec_frac1PdfBu_" + ComposeName(uniqueId, Neutral::gamma))
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
      pdf1Delta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdf1Delta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Delta left PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0pi0_mean1Delta_,
          Bu2Dst0h_Dst02D0pi0_sigma1Delta_, Bu2Dst0h_Dst02D0pi0_a1Delta_,
          Bu2Dst0h_Dst02D0pi0_n1Delta_),
      pdf2Delta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdf2Delta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Delta right PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0pi0_mean1Delta_,
          Bu2Dst0h_Dst02D0pi0_sigma2Delta_, Bu2Dst0h_Dst02D0pi0_a2Delta_,
          Bu2Dst0h_Dst02D0pi0_n2Delta_),
      Bu2Dst0hst_Dst02D0pi0_frac1PdfDelta_(
          ("Bu2Dst0hst_Dst02D0pi0_frac1PdfDelta_" +
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
          RooArgList(pdf1Delta_Bu2Dst0hst_Dst02D0pi0_,
                     pdf2Delta_Bu2Dst0hst_Dst02D0pi0_),
          Bu2Dst0hst_Dst02D0pi0_frac1PdfDelta_),
      pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Delta_Bu2Dst0hst_Dst02D0pi0 flat Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), bkg_thresholdDelta_, bkg_cDelta_,
          bkg_aDelta_, bkg_bDelta_),
      Bu2Dst0hst_Dst02D0pi0_fracPdfFlatDelta_(
          ("Bu2Dst0hst_Dst02D0pi0_fracPdfFlatDelta_" +
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
          Bu2Dst0hst_Dst02D0pi0_fracPdfFlatDelta_),
      Bu2Dst0hst_Dst02D0pi0_a0MeanBu_(
          ("Bu2Dst0hst_Dst02D0pi0_a0MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.7586e+03),
      Bu2Dst0hst_Dst02D0pi0_a1MeanBu_(
          ("Bu2Dst0hst_Dst02D0pi0_a1MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3.5646e+00),
      Bu2Dst0hst_Dst02D0pi0_a2MeanBu_(
          ("Bu2Dst0hst_Dst02D0pi0_a2MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.4359e-02),
      Bu2Dst0hst_Dst02D0pi0_meanBu_(
          ("Bu2Dst0hst_Dst02D0pi0_meanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Mean of Bu2Dst0hst_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(Bu2Dst0hst_Dst02D0pi0_a0MeanBu_,
                     Bu2Dst0hst_Dst02D0pi0_a1MeanBu_,
                     Bu2Dst0hst_Dst02D0pi0_a2MeanBu_)),
      Bu2Dst0hst_Dst02D0pi0_a0Sigma1Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_a0Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma1 of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.4387e+01),
      Bu2Dst0hst_Dst02D0pi0_a1Sigma1Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_a1Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma1 of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          7.8205e-02),
      Bu2Dst0hst_Dst02D0pi0_a2Sigma1Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_a2Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma1 of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3.1524e-03),
      Bu2Dst0hst_Dst02D0pi0_a0Sigma2Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_a0Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma2 of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          9.8039e+01),
      Bu2Dst0hst_Dst02D0pi0_a1Sigma2Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_a1Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma2 of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -7.1628e-01),
      Bu2Dst0hst_Dst02D0pi0_a2Sigma2Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_a2Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma2 of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.3805e-03),
      Bu2Dst0hst_Dst02D0pi0_a1Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_a1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of Bu2Dst0hst_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -3.8309e+00),
      Bu2Dst0hst_Dst02D0pi0_a2Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_a2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of Bu2Dst0hst_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.2150e+00),
      Bu2Dst0hst_Dst02D0pi0_n1Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_n1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("n1 of Bu2Dst0hst_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3.5387e+00),
      Bu2Dst0hst_Dst02D0pi0_n2Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_n2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("n2 of Bu2Dst0hst_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.3416e+01),
      Bu2Dst0hst_Dst02D0pi0_frac1PdfBu_(
          ("Bu2Dst0hst_Dst02D0pi0_frac1PdfBu_" +
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
      pdf1Delta_Bu2Dst0hst_Dst02D0gamma_(
          ("pdf1Delta_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Delta left PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0gamma_meanDelta_,
          Bu2Dst0h_Dst02D0gamma_sigma1Delta_,
          Bu2Dst0h_Dst02D0gamma_a1Delta_, Bu2Dst0h_Dst02D0gamma_n1Delta_),
      pdf2Delta_Bu2Dst0hst_Dst02D0gamma_(
          ("pdf2Delta_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Delta right PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0gamma_meanDelta_,
          Bu2Dst0h_Dst02D0gamma_sigma2Delta_,
          Bu2Dst0h_Dst02D0gamma_a2Delta_, Bu2Dst0h_Dst02D0gamma_n2Delta_),
      Bu2Dst0hst_Dst02D0gamma_frac1PdfDelta_(
          ("Bu2Dst0hst_Dst02D0gamma_frac1PdfDelta_" +
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
          RooArgList(pdf1Delta_Bu2Dst0hst_Dst02D0gamma_,
                     pdf2Delta_Bu2Dst0hst_Dst02D0gamma_),
          Bu2Dst0hst_Dst02D0gamma_frac1PdfDelta_),
      Bu2Dst0hst_Dst02D0gamma_a0MeanBu_(
          ("Bu2Dst0hst_Dst02D0gamma_a0MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of mean of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.9823e+03),
      Bu2Dst0hst_Dst02D0gamma_a1MeanBu_(
          ("Bu2Dst0hst_Dst02D0gamma_a1MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of mean of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          7.2035e-01),
      Bu2Dst0hst_Dst02D0gamma_a2MeanBu_(
          ("Bu2Dst0hst_Dst02D0gamma_a2MeanBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of mean of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -5.2626e-04),
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
          1.1748e+02),
      Bu2Dst0hst_Dst02D0gamma_a1Sigma1Bu_(
          ("Bu2Dst0hst_Dst02D0gamma_a1Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma1 of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.0968e+00),
      Bu2Dst0hst_Dst02D0gamma_a2Sigma1Bu_(
          ("Bu2Dst0hst_Dst02D0gamma_a2Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma1 of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          4.5671e-03),
      Bu2Dst0hst_Dst02D0gamma_a0Sigma2Bu_(
          ("Bu2Dst0hst_Dst02D0gamma_a0Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma2 of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.8658e+01),
      Bu2Dst0hst_Dst02D0gamma_a1Sigma2Bu_(
          ("Bu2Dst0hst_Dst02D0gamma_a1Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma2 of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -2.1932e-01),
      Bu2Dst0hst_Dst02D0gamma_a2Sigma2Bu_(
          ("Bu2Dst0hst_Dst02D0gamma_a2Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma2 of Bu2Dst0hst_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.4876e-03),
      Bu2Dst0hst_Dst02D0gamma_a1Bu_(("Bu2Dst0hst_Dst02D0gamma_a1Bu_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a1 of Bu2Dst0hst_Dst02D0gamma " +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    -3.1581e+00),  // 2.3, 0, 5),
      Bu2Dst0hst_Dst02D0gamma_a2Bu_(("Bu2Dst0hst_Dst02D0gamma_a2Bu_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("a2 of Bu2Dst0hst_Dst02D0gamma " +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    -3.0000e+00),  // 4.6, 0, 5),
      Bu2Dst0hst_Dst02D0gamma_n1Bu_(("Bu2Dst0hst_Dst02D0gamma_n1Bu_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("n1 of Bu2Dst0hst_Dst02D0gamma " +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    3.6653e-01),  // 3.4, 0, 5),
      Bu2Dst0hst_Dst02D0gamma_n2Bu_(("Bu2Dst0hst_Dst02D0gamma_n2Bu_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("n2 of Bu2Dst0hst_Dst02D0gamma " +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    5.1129e-01),  // 3.5, 0, 5),
      Bu2Dst0hst_Dst02D0gamma_frac1PdfBu_(
          ("Bu2Dst0hst_Dst02D0gamma_frac1PdfBu_" +
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
          Configuration::Get().deltaMass(), bkg_thresholdDelta_, bkg_cDelta_,
          bkg_aDelta_, bkg_bDelta_),
      misRec_a0Mean1Bu_(
          ("misRec_a0Mean1Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 of mean1 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.2058e+03),
      misRec_a1Mean1Bu_(
          ("misRec_a1Mean1Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a1 of mean1 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -4.3289e-02),
      misRec_a2Mean1Bu_(
          ("misRec_a2Mean1Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a2 of mean1 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          8.2392e-03),
      misRec_mean1Bu_(
          ("misRec_mean1Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean1 of misRec m[Bu]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(misRec_a0Mean1Bu_, misRec_a1Mean1Bu_, misRec_a2Mean1Bu_)),
      misRec_a0Mean2Bu_(
          ("misRec_a0Mean2Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 of mean2 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.3652e+03),
      misRec_a1Mean2Bu_(
          ("misRec_a1Mean2Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a1 of mean2 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.4674e-01),
      misRec_a2Mean2Bu_(
          ("misRec_a2Mean2Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a2 of mean2 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          8.3082e-03),
      misRec_mean2Bu_(
          ("misRec_mean2Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean2 of misRec m[Bu]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(misRec_a0Mean2Bu_, misRec_a1Mean2Bu_, misRec_a2Mean2Bu_)),
      misRec_a0Mean3Bu_(
          ("misRec_a0Mean3Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 of mean2 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.0854e+03),
      misRec_a1Mean3Bu_(
          ("misRec_a1Mean3Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a1 of mean2 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          1.9793e+00),
      misRec_a2Mean3Bu_(
          ("misRec_a2Mean3Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a2 of mean2 of misRec m[Bu]" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -5.5658e-03),
      misRec_mean3Bu_(
          ("misRec_mean3Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean2 of misRec m[Bu]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(misRec_a0Mean3Bu_, misRec_a1Mean3Bu_, misRec_a2Mean3Bu_)),
      misRec_a0Sigma1Bu_(
          ("misRec_a0Sigma1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma1 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -3.3548e+01),
      misRec_a1Sigma1Bu_(
          ("misRec_a1Sigma1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma1 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          7.0068e-01),
      misRec_a2Sigma1Bu_(
          ("misRec_a2Sigma1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma1 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -8.3490e-04),
      misRec_a0Sigma2Bu_(
          ("misRec_a0Sigma2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma2 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.3523e+01),
      misRec_a1Sigma2Bu_(
          ("misRec_a1Sigma2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma2 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -2.6007e-01),
      misRec_a2Sigma2Bu_(
          ("misRec_a2Sigma2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma2 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -2.3067e-02),
      misRec_a0Sigma3Bu_(
          ("misRec_a0Sigma3Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a0 of sigma3 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.1908e+01),
      misRec_a1Sigma3Bu_(
          ("misRec_a1Sigma3Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a1 of sigma3 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5.8331e-01),
      misRec_a2Sigma3Bu_(
          ("misRec_a2Sigma3Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("a2 of sigma3 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -1.0471e-03),
      misRec_frac1PdfBu_(
          ("misRec_frac1PdfBu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of 1st CB Bu PDF in misRec " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          9.2004e-02),
      misRec_frac2PdfBu_(
          ("misRec_frac2PdfBu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of 2nd CB Bu PDF in misRec " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          3.4431e-04),
      misRec_frac3PdfBu_(
          ("misRec_frac3PdfBu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Fraction of 3rd CB Bu PDF in misRec " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "1-(@0+@1)", RooArgList(misRec_frac1PdfBu_, misRec_frac2PdfBu_)),
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
