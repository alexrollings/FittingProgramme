#include "NeutralVars.h"
#include "GlobalVars.h"
// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::pi0>::NeutralVars(int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : Bu2Dst0h_Dst02D0pi0_meanDelta_(("Bu2Dst0h_Dst02D0pi0_meanDelta_" +
                                       ComposeName(uniqueId, Neutral::pi0))
                                          .c_str(),
                                      ("Mean of Bu2Dst0h_Dst02D0pi0 m[Delta]" +
                                       ComposeName(uniqueId, Neutral::pi0))
                                          .c_str(),
                                      1.4262e+02),
      Bu2Dst0h_Dst02D0pi0_sigma1Delta_(("Bu2Dst0h_Dst02D0pi0_sigma1Delta_" +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       ("Sigma left of Bu2Dst0h_Dst02D0pi0 " +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       3.0664e+00),
      Bu2Dst0h_Dst02D0pi0_sigma2Delta_(("Bu2Dst0h_Dst02D0pi0_sigma2Delta_" +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       ("Sigma right of Bu2Dst0h_Dst02D0pi0 " +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       1.5829e+00),
      Bu2Dst0h_Dst02D0pi0_a1Delta_(
          ("Bu2Dst0h_Dst02D0pi0_a1Delta_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          2.7959e+00),
      Bu2Dst0h_Dst02D0pi0_a2Delta_(
          ("Bu2Dst0h_Dst02D0pi0_a2Delta_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a2 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -6.8349e-01),
      Bu2Dst0h_Dst02D0pi0_n1Delta_(
          ("Bu2Dst0h_Dst02D0pi0_n1Delta_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("n1 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          2.3226e+00),
      Bu2Dst0h_Dst02D0pi0_n2Delta_(
          ("Bu2Dst0h_Dst02D0pi0_n2Delta_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("n2 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          3.9713e+00),
      pdf1Delta_Bu2Dst0h_Dst02D0pi0_(
          ("pdf1Delta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Delta left PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0pi0_meanDelta_,
          Bu2Dst0h_Dst02D0pi0_sigma1Delta_, Bu2Dst0h_Dst02D0pi0_a1Delta_,
          Bu2Dst0h_Dst02D0pi0_n1Delta_),
      pdf2Delta_Bu2Dst0h_Dst02D0pi0_(
          ("pdf2Delta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Delta right PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0pi0_meanDelta_,
          Bu2Dst0h_Dst02D0pi0_sigma2Delta_, Bu2Dst0h_Dst02D0pi0_a2Delta_,
          Bu2Dst0h_Dst02D0pi0_n2Delta_),
      Bu2Dst0h_Dst02D0pi0_frac1PdfDelta_(
          ("Bu2Dst0h_Dst02D0pi0_frac1PdfDelta_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Fraction of left w.r.t. right PDF in Bu2Dst0h_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          2.3450e-01),
      pdfDelta_Bu2Dst0h_Dst02D0pi0_(("pdfDelta_Bu2Dst0h_Dst02D0pi0_" +
                                     ComposeName(uniqueId, Neutral::pi0))
                                        .c_str(),
                                    ("Bu2Dst0h_Dst02D0pi0 Delta PDF " +
                                     ComposeName(uniqueId, Neutral::pi0))
                                        .c_str(),
                                    RooArgList(pdf1Delta_Bu2Dst0h_Dst02D0pi0_,
                                               pdf2Delta_Bu2Dst0h_Dst02D0pi0_),
                                    Bu2Dst0h_Dst02D0pi0_frac1PdfDelta_),
      Bu2Dst0h_Dst02D0pi0_a0Mean1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a0Mean1Bu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of mean1 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          5.0645e+03),
      Bu2Dst0h_Dst02D0pi0_a1Mean1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a1Mean1Bu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of mean1 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          1.5183e+00),
      Bu2Dst0h_Dst02D0pi0_a2Mean1Bu_(),
      Bu2Dst0h_Dst02D0pi0_mean1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_mean1Bu_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Mean1 of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(Bu2Dst0h_Dst02D0pi0_a0Mean1Bu_,
                     Bu2Dst0h_Dst02D0pi0_a1Mean1Bu_)),
      // Bu2Dst0h_Dst02D0pi0_a2Mean1Bu_)),
      Bu2Dst0h_Dst02D0pi0_a0Sigma1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a0Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of sigma1 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -4.3271e+01),
      Bu2Dst0h_Dst02D0pi0_a1Sigma1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a1Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of sigma1 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          4.7437e-01),
      Bu2Dst0h_Dst02D0pi0_a2Sigma1Bu_(),
      Bu2Dst0h_Dst02D0pi0_a0Sigma2Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a0Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of sigma2 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -8.4234e+01),
      Bu2Dst0h_Dst02D0pi0_a1Sigma2Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a1Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of sigma2 of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          6.9129e-01),
      Bu2Dst0h_Dst02D0pi0_a2Sigma2Bu_(),
      Bu2Dst0h_Dst02D0pi0_a1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a1Bu_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          2.4753e+00),
      Bu2Dst0h_Dst02D0pi0_a2Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a2Bu_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a2 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -1.7369e+00),
      Bu2Dst0h_Dst02D0pi0_n1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_n1Bu_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("n1 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          1.3874e+00),
      Bu2Dst0h_Dst02D0pi0_n2Bu_(
          ("Bu2Dst0h_Dst02D0pi0_n2Bu_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("n2 of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          2.9609e+00),
      Bu2Dst0h_Dst02D0pi0_frac1PdfBu_(
          ("Bu2Dst0h_Dst02D0pi0_frac1PdfBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Fraction of left w.r.t. right Bu PDF in Bu2Dst0h_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          2.8927e-01),
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
          0.07930, -1, 1),
      // ------------------ NO CROSS FEED BECAUSE OF VETO ------------------ //
      Bu2Dst0h_Dst02D0gamma_meanDelta_(),
      Bu2Dst0h_Dst02D0gamma_sigma1Delta_(),
      Bu2Dst0h_Dst02D0gamma_sigma2Delta_(),
      Bu2Dst0h_Dst02D0gamma_a2Delta_(),
      Bu2Dst0h_Dst02D0gamma_a1Delta_(),
      Bu2Dst0h_Dst02D0gamma_n2Delta_(),
      Bu2Dst0h_Dst02D0gamma_n1Delta_(),
      pdf1Delta_Bu2Dst0h_Dst02D0gamma_(),
      pdf2Delta_Bu2Dst0h_Dst02D0gamma_(),
      Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_(),
      pdfDelta_Bu2Dst0h_Dst02D0gamma_(),
      Bu2Dst0h_Dst02D0gamma_a0MeanBu_(),
      Bu2Dst0h_Dst02D0gamma_a1MeanBu_(),
      Bu2Dst0h_Dst02D0gamma_a2MeanBu_(),
      Bu2Dst0h_Dst02D0gamma_meanBu_(),
      Bu2Dst0h_Dst02D0gamma_a0Sigma1Bu_(),
      Bu2Dst0h_Dst02D0gamma_a1Sigma1Bu_(),
      Bu2Dst0h_Dst02D0gamma_a2Sigma1Bu_(),
      Bu2Dst0h_Dst02D0gamma_a0Sigma2Bu_(),
      Bu2Dst0h_Dst02D0gamma_a1Sigma2Bu_(),
      Bu2Dst0h_Dst02D0gamma_a2Sigma2Bu_(),
      Bu2Dst0h_Dst02D0gamma_a1Bu_(),
      Bu2Dst0h_Dst02D0gamma_a2Bu_(),
      Bu2Dst0h_Dst02D0gamma_n1Bu_(),
      Bu2Dst0h_Dst02D0gamma_n2Bu_(),
      Bu2Dst0h_Dst02D0gamma_frac1PdfBu_(),
      relativeBuWidth_Bu2Dst0h_Dst02D0gamma_(),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_(),
      // ------------------ DSTD0BKG PARAMETERS (SHARED) ------------------ //
      bkg_thresholdDelta_(
          ("bkg_thresholdDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg thershold " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          1.3437e+02),
      bkg_cDelta_(
          ("bkg_cDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg c parameter " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          4.5080e+00),
      bkg_aDelta_(
          ("bkg_aDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg a parameter " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          5.3530e-01),
      bkg_bDelta_(
          ("bkg_bDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg b parameter " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -2.4844e-01),
      // -------------------- OVER RECONSTRUCTED BKG -------------------- //
      pdfDelta_overRec_(
          ("pdfDelta_overRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Delta_overRec PDF " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          Configuration::Get().deltaMass(), bkg_thresholdDelta_, bkg_cDelta_,
          bkg_aDelta_, bkg_bDelta_),
      overRec_a0Mean1Bu_(
          ("overRec_a0Mean1Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 of mean1 of overRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          5.5651e+03),
      overRec_a1Mean1Bu_(
          ("overRec_a1Mean1Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a1 of mean1 of overRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -1.3327e+00),
      overRec_a2Mean1Bu_(
          ("overRec_a2Mean1Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a2 of mean1 of overRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          4.9439e-03),
      overRec_mean1Bu_(
          ("overRec_mean1Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Mean1 of overRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(overRec_a0Mean1Bu_, overRec_a1Mean1Bu_,
                     overRec_a2Mean1Bu_)),
      overRec_a0Mean2Bu_(
          ("overRec_a0Mean2Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 of mean2 of overRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          4.8357e+03),
      overRec_a1Mean2Bu_(
          ("overRec_a1Mean2Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a1 of mean2 of overRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          7.6626e+00),
      overRec_a2Mean2Bu_(
          ("overRec_a2Mean2Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a2 of mean2 of overRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -1.9999e-02),
      overRec_mean2Bu_(
          ("overRec_mean2Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Mean2 of overRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(overRec_a0Mean2Bu_, overRec_a1Mean2Bu_,
                     overRec_a2Mean2Bu_)),
      overRec_a0Sigma1Bu_(
          ("overRec_a0Sigma1Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 of sigma1 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -1.2592e+02),
      overRec_a1Sigma1Bu_(
          ("overRec_a1Sigma1Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a1 of sigma1 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          1.4318e+00),
      overRec_a2Sigma1Bu_(
          ("overRec_a2Sigma1Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a2 of sigma1 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -2.8420e-03),
      overRec_a0Sigma2Bu_(
          ("overRec_a0Sigma2Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 of sigma2 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -4.2326e+02),
      overRec_a1Sigma2Bu_(
          ("overRec_a1Sigma2Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a1 of sigma2 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          4.7441e+00),
      overRec_a2Sigma2Bu_(
          ("overRec_a2Sigma2Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a2 of sigma2 of overRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -1.1290e-02),
      overRec_a1Bu_(
          ("overRec_a1Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a1 of overRec " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          4.8473e+00),
      overRec_a2Bu_(
          ("overRec_a2Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a2 of overRec " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          2.2651e+00),
      overRec_n1Bu_(
          ("overRec_n1Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("n1 of overRec " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          9.7261e+00),
      overRec_n2Bu_(
          ("overRec_n2Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("n2 of overRec " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          1.0870e+00),
      overRec_frac1PdfBu_(
          ("overRec_frac1PdfBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Fraction of left w.r.t. right Bu PDF in overRec " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          4.2722e-01),
      relativeBuWidth_overRec_(
          ("relativeBuWidth_overRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in overRec "
           "mode " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          1),
      ratioDst0KDst0pi_overRec_(
          ("ratioDst0KDst0pi_overRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n overRec mode " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          0.07768),  // CHECK
      // ------------------ MIS RECONSTRUCTED BACKGROUND ------------------ //
      // misRec_thresholdDelta_(
      //     ("misRec_thresholdDelta_" + ComposeName(uniqueId,
      //     Neutral::pi0)).c_str(),
      //     (" Delta_misRec thershold " + ComposeName(uniqueId, Neutral::pi0))
      //         .c_str(),
      //     1.3437e+02),
      misRec_thresholdDelta_(
          ("misRec_thresholdDelta_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          (" Delta_bkg thershold " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          1.3537e+02),
      misRec_cDelta_(
          ("misRec_cDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg c parameter " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          8.3057e+00),
      misRec_aDelta_(
          ("misRec_aDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg a parameter " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          5.1615e-01),
      misRec_bDelta_(
          ("misRec_bDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg b parameter " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -1.8073e+00),
      pdfDelta_misRec_(
          ("pdfDelta_misRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Delta_misRec PDF " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          Configuration::Get().deltaMass(), misRec_thresholdDelta_,
          misRec_cDelta_, misRec_aDelta_, misRec_bDelta_),
      misRec_a0Mean1Bu_(
          ("misRec_a0Mean1Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 of mean of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          5.2476e+03),
      misRec_a1Mean1Bu_(
          ("misRec_a1Mean1Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a1 of mean of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          2.1392e-01),
      misRec_a2Mean1Bu_(),
      misRec_mean1Bu_(
          ("misRec_mean1Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Mean of misRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(misRec_a0Mean1Bu_, misRec_a1Mean1Bu_)),
      misRec_a0Mean2Bu_(
          ("misRec_a0Mean2Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 of mean of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          5.2954e+03),
      misRec_mean2Bu_(
          ("misRec_mean2Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Mean of misRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(misRec_a0Mean2Bu_, misRec_a1Mean1Bu_)),
      misRec_a0Sigma1Bu_(
          ("misRec_a0Sigma1Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 of sigma1 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          5.7378e+01),
      misRec_a1Sigma1Bu_(),
      misRec_a2Sigma1Bu_(),
      misRec_a0Sigma2Bu_(
          ("misRec_a0Sigma2Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 of sigma1 of misRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          7.8502e+01),
      misRec_a1Bu_(
          ("misRec_a1Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a1 of misRec " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          7.1456e-01),
      misRec_a2Bu_(
          ("misRec_a2Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a2 of misRec " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          -1.8906e+00),
      misRec_n1Bu_(
          ("misRec_n1Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("n1 of misRec " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          6.6513e-01),
      misRec_n2Bu_(
          ("misRec_n2Bu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("n2 of misRec " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          9.9913e+00),
      misRec_frac1PdfBu_(
          ("misRec_frac1PdfBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Fraction of left w.r.t. right Bu PDF in misRec " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          5.6450e-01),
      relativeBuWidth_misRec_(
          ("relativeBuWidth_misRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in misRec "
           "mode " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          1),
      ratioDst0KDst0pi_misRec_(
          ("ratioDst0KDst0pi_misRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n misRec mode " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          0.05, 0, 0.1),
      // -------------------- Pi0 PART RECONSTRUCTED BKG --------------------
      Bu2Dst0hst_Dst02D0pi0_meanDelta_(
          ("Bu2Dst0hst_Dst02D0pi0_meanDelta_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Mean of Bu2Dst0hst_Dst02D0pi0 m[Delta]" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          1.4367e+02),
      pdf1Delta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdf1Delta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Delta left PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0hst_Dst02D0pi0_meanDelta_,
          Bu2Dst0h_Dst02D0pi0_sigma1Delta_, Bu2Dst0h_Dst02D0pi0_a1Delta_,
          Bu2Dst0h_Dst02D0pi0_n1Delta_),
      pdf2Delta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdf2Delta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Delta right PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0hst_Dst02D0pi0_meanDelta_,
          Bu2Dst0h_Dst02D0pi0_sigma2Delta_, Bu2Dst0h_Dst02D0pi0_a2Delta_,
          Bu2Dst0h_Dst02D0pi0_n2Delta_),
      pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Delta Peaking PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          RooArgList(pdf1Delta_Bu2Dst0hst_Dst02D0pi0_,
                     pdf2Delta_Bu2Dst0hst_Dst02D0pi0_),
          Bu2Dst0h_Dst02D0pi0_frac1PdfDelta_),
      pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Delta_Bu2Dst0hst_Dst02D0pi0 PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), misRec_thresholdDelta_,
          misRec_cDelta_, misRec_aDelta_, misRec_bDelta_),
      Bu2Dst0hst_Dst02D0pi0_fracPdfPeakDelta_(
          ("Bu2Dst0hst_Dst02D0pi0_fracPdfPeakDelta_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Fraction of peak pdf w.r.t. peaking pdf for partially "
           "reconstructed bkg " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          6.5423e-01),
      pdfDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Delta PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          RooArgSet(pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0_,
                    pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_),
          Bu2Dst0hst_Dst02D0pi0_fracPdfPeakDelta_),
      Bu2Dst0hst_Dst02D0pi0_a0MeanBu_(
          ("Bu2Dst0hst_Dst02D0pi0_a0MeanBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          4.9506e+03),
      Bu2Dst0hst_Dst02D0pi0_a1MeanBu_(
          ("Bu2Dst0hst_Dst02D0pi0_a1MeanBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          9.5885e-01),
      Bu2Dst0hst_Dst02D0pi0_meanBu_(
          ("Bu2Dst0hst_Dst02D0pi0_meanBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Mean of Bu2Dst0hst_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(Bu2Dst0hst_Dst02D0pi0_a0MeanBu_,
                     Bu2Dst0hst_Dst02D0pi0_a1MeanBu_)),
      Bu2Dst0hst_Dst02D0pi0_a0Sigma1Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_a0Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of sigma1 of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -6.1952e+01),
      Bu2Dst0hst_Dst02D0pi0_a1Sigma1Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_a1Sigma1Bu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of sigma1 of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          7.3381e-01),
      Bu2Dst0hst_Dst02D0pi0_a0Sigma2Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_a0Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of sigma2 of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -9.9049e+01),
      Bu2Dst0hst_Dst02D0pi0_a1Sigma2Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_a1Sigma2Bu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of sigma2 of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          9.5144e-01),
      Bu2Dst0hst_Dst02D0pi0_a1Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_a1Bu_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of Bu2Dst0hst_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          3.8134e+00),
      Bu2Dst0hst_Dst02D0pi0_a2Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_a2Bu_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a2 of Bu2Dst0hst_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -2.8253e+00),
      Bu2Dst0hst_Dst02D0pi0_n1Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_n1Bu_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("n1 of Bu2Dst0hst_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          1.8084e+00),
      Bu2Dst0hst_Dst02D0pi0_n2Bu_(
          ("Bu2Dst0hst_Dst02D0pi0_n2Bu_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("n2 of Bu2Dst0hst_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          3.5744e+00),
      Bu2Dst0hst_Dst02D0pi0_frac1PdfBu_(
          ("Bu2Dst0hst_Dst02D0pi0_frac1PdfBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Fraction of left w.r.t. right Bu PDF in Bu2Dst0hst_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          4.1296e-01),
      relativeBuWidth_Bu2Dst0hst_Dst02D0pi0_(
          ("relativeBuWidth_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in Bu2Dst0hst_Dst02D0pi0 "
           "mode " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          0.95),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_(
          ("ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n Bu2Dst0hst_Dst02D0pi0 mode " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          0.02, -1, 1),
      // ------------------ Gamma PART RECONSTRUCTED BACKGROUND
      // ------------------ //
      Bu2Dst0hst_Dst02D0gamma_meanDelta_(),
      pdf1Delta_Bu2Dst0hst_Dst02D0gamma_(),
      pdf2Delta_Bu2Dst0hst_Dst02D0gamma_(),
      pdfDelta_Bu2Dst0hst_Dst02D0gamma_(),
      Bu2Dst0hst_Dst02D0gamma_a0MeanBu_(),
      Bu2Dst0hst_Dst02D0gamma_a1MeanBu_(),
      Bu2Dst0hst_Dst02D0gamma_a2MeanBu_(),
      Bu2Dst0hst_Dst02D0gamma_meanBu_(),
      Bu2Dst0hst_Dst02D0gamma_a0Sigma1Bu_(),
      Bu2Dst0hst_Dst02D0gamma_a1Sigma1Bu_(),
      Bu2Dst0hst_Dst02D0gamma_a2Sigma1Bu_(),
      // Bu2Dst0hst_Dst02D0gamma_a0Sigma2Bu_(),
      // Bu2Dst0hst_Dst02D0gamma_a1Sigma2Bu_(),
      // Bu2Dst0hst_Dst02D0gamma_a2Sigma2Bu_(),
      Bu2Dst0hst_Dst02D0gamma_a1Bu_(),
      // Bu2Dst0hst_Dst02D0gamma_a2Bu_(),
      Bu2Dst0hst_Dst02D0gamma_n1Bu_(),
      // Bu2Dst0hst_Dst02D0gamma_n2Bu_(),
      // Bu2Dst0hst_Dst02D0gamma_frac1PdfBu_(),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_(),
      relativeBuWidth_Bu2Dst0hst_Dst02D0gamma_(),
      // -------------------- DST0D0 BACKGROUND -------------------- //
      pdfDelta_Comb_(
          ("pdfDelta_Comb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Delta_Combinatorial PDF " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), bkg_thresholdDelta_, bkg_cDelta_,
          bkg_aDelta_, bkg_bDelta_),
      // -------------------- EXPONENTIAL BACKGROUND -------------------- //
      Comb_a0LambdaBu_(
          ("Comb_a0LambdaBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 component for Bu _Combinatorial constant " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -0.001, -1, -0.00001),
      Comb_lambdaBu_(
          ("Comb_lambdaBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Bu _Combinatorial constant " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), RooArgSet(Comb_a0LambdaBu_)),
      pdfBu_Comb_(
          ("pdfBu_Comb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Bu_Combinatorial PDF " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().buMass(), Comb_lambdaBu_),
      pdf_Comb_(
          ("pdf_Comb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("_Combinatorial PDF " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          pdfDelta_Comb_,
          RooFit::Conditional(pdfBu_Comb_, Configuration::Get().buMass())) {
  std::cout << "Neutral vars managed to construct itself\n" << std::flush;
      
      }
