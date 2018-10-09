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
                                     1.4235e+02),
      // 143, 138, 148),
      Bu2Dst0h_Dst02D0pi0_sigmaLDelta_(("Bu2Dst0h_Dst02D0pi0_sigmaLDelta_" +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       ("Sigma left of Bu2Dst0h_Dst02D0pi0 " +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       2.1093e+00),
      // 3, 1, 5),
      Bu2Dst0h_Dst02D0pi0_sigmaRDelta_(("Bu2Dst0h_Dst02D0pi0_sigmaRDelta_" +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       ("Sigma right of Bu2Dst0h_Dst02D0pi0 " +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       1.5256e+00),
      Bu2Dst0h_Dst02D0pi0_aLDelta_(
          ("Bu2Dst0h_Dst02D0pi0_aLDelta_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("aL of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -4.4647e-01),
      Bu2Dst0h_Dst02D0pi0_aRDelta_(
          ("Bu2Dst0h_Dst02D0pi0_aRDelta_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("aR of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          1.8325e+00),
      Bu2Dst0h_Dst02D0pi0_nLDelta_(
          ("Bu2Dst0h_Dst02D0pi0_nLDelta_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("nL of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          4.2560e+01),
      Bu2Dst0h_Dst02D0pi0_nRDelta_(
          ("Bu2Dst0h_Dst02D0pi0_nRDelta_" + ComposeName(uniqueId, Neutral::pi0))
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
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0pi0_meanDelta_,
          Bu2Dst0h_Dst02D0pi0_sigmaLDelta_, Bu2Dst0h_Dst02D0pi0_aLDelta_,
          Bu2Dst0h_Dst02D0pi0_nLDelta_),
      pdfRDelta_Bu2Dst0h_Dst02D0pi0_(
          ("pdfRDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Delta right PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), Bu2Dst0h_Dst02D0pi0_meanDelta_,
          Bu2Dst0h_Dst02D0pi0_sigmaRDelta_, Bu2Dst0h_Dst02D0pi0_aRDelta_,
          Bu2Dst0h_Dst02D0pi0_nRDelta_),
      Bu2Dst0h_Dst02D0pi0_fracLRDelta_(
          ("Bu2Dst0h_Dst02D0pi0_fracLRDelta_" +
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
                                    Bu2Dst0h_Dst02D0pi0_fracLRDelta_),
      Bu2Dst0h_Dst02D0pi0_a0Mean1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a0Mean1Bu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 4998, 4950, 5050),
          5.1129e+03),
      Bu2Dst0h_Dst02D0pi0_a1Mean1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a1Mean1Bu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 3, 0, 10),
          -4.0649e-03),
      Bu2Dst0h_Dst02D0pi0_a2Mean1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_a2Mean1Bu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a2 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // -0.007, -0.1, 0.1),
          8.2868e-03),
      Bu2Dst0h_Dst02D0pi0_mean1Bu_(
          ("Bu2Dst0h_Dst02D0pi0_mean1Bu_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Mean of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(Bu2Dst0h_Dst02D0pi0_a0Mean1Bu_,
                     Bu2Dst0h_Dst02D0pi0_a1Mean1Bu_,
                     Bu2Dst0h_Dst02D0pi0_a2Mean1Bu_)),
      Bu2Dst0h_Dst02D0pi0_a0Mean2Bu_(),
      Bu2Dst0h_Dst02D0pi0_a1Mean2Bu_(),
      Bu2Dst0h_Dst02D0pi0_a2Mean2Bu_(),
      Bu2Dst0h_Dst02D0pi0_mean2Bu_(),
      Bu2Dst0h_Dst02D0pi0_a0SigmaLBu_(
          ("Bu2Dst0h_Dst02D0pi0_a0SigmaLBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of sigmaL of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 22, -100, 100),
          4.5493e+01),
      Bu2Dst0h_Dst02D0pi0_a1SigmaLBu_(
          ("Bu2Dst0h_Dst02D0pi0_a1SigmaLBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of sigmaL of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 0.07, -10, 10),
          -2.6105e-02),
      Bu2Dst0h_Dst02D0pi0_a2SigmaLBu_(
          ("Bu2Dst0h_Dst02D0pi0_a2SigmaLBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a2 of sigmaL of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 0.0036, -0.01, 0.01),
          -1.2044e-03),
      Bu2Dst0h_Dst02D0pi0_a0SigmaRBu_(
          ("Bu2Dst0h_Dst02D0pi0_a0SigmaRBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of sigmaR of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 22, -100, 100),
          4.5493e+01),
      Bu2Dst0h_Dst02D0pi0_a1SigmaRBu_(
          ("Bu2Dst0h_Dst02D0pi0_a1SigmaRBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of sigmaR of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 0.07, -10, 10),
          -2.6105e-02),
      Bu2Dst0h_Dst02D0pi0_a2SigmaRBu_(
          ("Bu2Dst0h_Dst02D0pi0_a2SigmaRBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a2 of sigmaR of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 0.0036, -0.01, 0.01),
          -1.2044e-03),
      Bu2Dst0h_Dst02D0pi0_aLBu_(
          ("Bu2Dst0h_Dst02D0pi0_aLBu_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("aL of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          7.9439e+00),  // 2.3, 0, 5),
      Bu2Dst0h_Dst02D0pi0_aRBu_(
          ("Bu2Dst0h_Dst02D0pi0_aRBu_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("aR of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -8.6538e+00),  // 4.6, 0, 5),
      Bu2Dst0h_Dst02D0pi0_nLBu_(
          ("Bu2Dst0h_Dst02D0pi0_nLBu_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("nL of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          9.8579e+00),  // 3.4, 0, 5),
      Bu2Dst0h_Dst02D0pi0_nRBu_(
          ("Bu2Dst0h_Dst02D0pi0_nRBu_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("nR of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          1.1800e+01),  // 3.5, 0, 5),
      Bu2Dst0h_Dst02D0pi0_fracLRPdfBu_(
          ("Bu2Dst0h_Dst02D0pi0_fracLRPdfBu_" +
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
          0.07930, -1, 1),  //, 0.0, 0.1),
      // ------------------ NO CROSS FEED BECAUSE OF VETO ------------------ //
      Bu2Dst0h_Dst02D0gamma_meanDelta_(),
      Bu2Dst0h_Dst02D0gamma_sigmaLDelta_(),
      Bu2Dst0h_Dst02D0gamma_sigmaRDelta_(),
      Bu2Dst0h_Dst02D0gamma_aRDelta_(),
      Bu2Dst0h_Dst02D0gamma_aLDelta_(),
      Bu2Dst0h_Dst02D0gamma_nRDelta_(),
      Bu2Dst0h_Dst02D0gamma_nLDelta_(),
      pdfLDelta_Bu2Dst0h_Dst02D0gamma_(),
      pdfRDelta_Bu2Dst0h_Dst02D0gamma_(),
      Bu2Dst0h_Dst02D0gamma_fracLRDelta_(),
      pdfDelta_Bu2Dst0h_Dst02D0gamma_(),
      Bu2Dst0h_Dst02D0gamma_a0Mean1Bu_(),
      Bu2Dst0h_Dst02D0gamma_a1Mean1Bu_(),
      Bu2Dst0h_Dst02D0gamma_a2Mean1Bu_(),
      Bu2Dst0h_Dst02D0gamma_mean1Bu_(),
      Bu2Dst0h_Dst02D0gamma_a0Mean2Bu_(),
      Bu2Dst0h_Dst02D0gamma_a1Mean2Bu_(),
      Bu2Dst0h_Dst02D0gamma_a2Mean2Bu_(),
      Bu2Dst0h_Dst02D0gamma_mean2Bu_(),
      Bu2Dst0h_Dst02D0gamma_a0SigmaLBu_(),
      Bu2Dst0h_Dst02D0gamma_a1SigmaLBu_(),
      Bu2Dst0h_Dst02D0gamma_a2SigmaLBu_(),
      Bu2Dst0h_Dst02D0gamma_a0SigmaRBu_(),
      Bu2Dst0h_Dst02D0gamma_a1SigmaRBu_(),
      Bu2Dst0h_Dst02D0gamma_a2SigmaRBu_(),
      Bu2Dst0h_Dst02D0gamma_aLBu_(),
      Bu2Dst0h_Dst02D0gamma_aRBu_(),
      Bu2Dst0h_Dst02D0gamma_nLBu_(),
      Bu2Dst0h_Dst02D0gamma_nRBu_(),
      Bu2Dst0h_Dst02D0gamma_fracLRPdfBu_(),
      Bu2Dst0h_Dst02D0gamma_fracWidePdfBu_(),
      relativeBuWidth_Bu2Dst0h_Dst02D0gamma_(),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_(),
      // ------------------ DSTD0BKG PARAMETERS (SHARED) ------------------ //
      bkg_thresholdDelta_(
          ("bkg_thresholdDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg thershold " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 134.5),
          1.3428e+02),
      bkg_cDelta_(
          ("bkg_cDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg c parameter " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 10, 0.001, 20),
          // 3.14),
          6.4715),
      bkg_aDelta_(
          ("bkg_aDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg a parameter " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // -0.5, -1, 1),
          // -0.99),
          -5),
      bkg_bDelta_(
          ("bkg_bDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg b parameter " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 0.01),  // -0.5, 0.5),
          // -0.058),
          -4.0455e-03),
      // -------------------- OVER RECONSTRUCTED BKG -------------------- //
      pdfDelta_overRec_(
          ("pdfDelta_overRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Delta_overRec PDF " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          Configuration::Get().deltaMass(), bkg_thresholdDelta_, bkg_cDelta_,
          bkg_aDelta_, bkg_bDelta_),
      // overRec_a0MeanBu_(
      //     ("overRec_a0MeanBu_" + ComposeName(uniqueId,
      //     Neutral::pi0)).c_str(),
      //     ("a0 of mean of overRec m[Bu] PDF " +
      //      ComposeName(uniqueId, Neutral::pi0))
      //         .c_str(),
      //     5520, 5470, 5570),
      // overRec_meanBu_(
      //     ("overRec_meanBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
      //     ("Mean of overRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
      //         .c_str(),
      //     Configuration::Get().deltaMass(), RooArgList(overRec_a0MeanBu_)),
      overRec_a0Mean1Bu_(),
      overRec_a1Mean1Bu_(),
      overRec_a2Mean1Bu_(),
      overRec_mean1Bu_(),
      overRec_a0Mean2Bu_(),
      overRec_a1Mean2Bu_(),
      overRec_a2Mean2Bu_(),
      overRec_mean2Bu_(),
      overRec_a0SigmaLBu_(),
      overRec_a1SigmaLBu_(),
      overRec_a2SigmaLBu_(),
      overRec_a0SigmaRBu_(),
      overRec_a1SigmaRBu_(),
      overRec_a2SigmaRBu_(),
      overRec_aLBu_(),
      overRec_aRBu_(),
      overRec_nLBu_(),
      overRec_nRBu_(),
      overRec_fracLRPdfBu_(),
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
      // -------------------- Pi0 PART RECONSTRUCTED BKG --------------------
      Bu2Dst0hst_Dst02D0pi0_meanDelta_(),
      Bu2Dst0hst_Dst02D0pi0_sigmaLDelta_(),
      Bu2Dst0hst_Dst02D0pi0_sigmaRDelta_(),
      Bu2Dst0hst_Dst02D0pi0_aRDelta_(),
      Bu2Dst0hst_Dst02D0pi0_aLDelta_(),
      Bu2Dst0hst_Dst02D0pi0_nRDelta_(),
      Bu2Dst0hst_Dst02D0pi0_nLDelta_(),
      pdfLDelta_Bu2Dst0hst_Dst02D0pi0_(),
      pdfRDelta_Bu2Dst0hst_Dst02D0pi0_(),
      Bu2Dst0hst_Dst02D0pi0_fracLRDelta_(),
      pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0_(),
      pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_(),
      Bu2Dst0hst_Dst02D0pi0_fracPdfFlatDelta_(),
      pdfDelta_Bu2Dst0hst_Dst02D0pi0_(),
      Bu2Dst0hst_Dst02D0pi0_a0MeanBu_(
          ("Bu2Dst0hst_Dst02D0pi0_a0MeanBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 5100, 5050, 5150),
          4950, 4900, 5000),
      Bu2Dst0hst_Dst02D0pi0_a1MeanBu_(
          ("Bu2Dst0hst_Dst02D0pi0_a1MeanBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 3, 0, 10),
          1.3, 0, 10),
      Bu2Dst0hst_Dst02D0pi0_a2MeanBu_(
          ("Bu2Dst0hst_Dst02D0pi0_a2MeanBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a2 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -0.004, -0.1, 0.1),
      // -0.007, -0.1, 0.1),
      Bu2Dst0hst_Dst02D0pi0_meanBu_(
          ("Bu2Dst0hst_Dst02D0pi0_meanBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Mean of Bu2Dst0hst_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(Bu2Dst0hst_Dst02D0pi0_a0MeanBu_,
                     Bu2Dst0hst_Dst02D0pi0_a1MeanBu_,
                     Bu2Dst0hst_Dst02D0pi0_a2MeanBu_)),
      Bu2Dst0hst_Dst02D0pi0_a0SigmaLBu_(),
      Bu2Dst0hst_Dst02D0pi0_a1SigmaLBu_(),
      Bu2Dst0hst_Dst02D0pi0_a2SigmaLBu_(),
      Bu2Dst0hst_Dst02D0pi0_a0SigmaRBu_(),
      Bu2Dst0hst_Dst02D0pi0_a1SigmaRBu_(),
      Bu2Dst0hst_Dst02D0pi0_a2SigmaRBu_(),
      Bu2Dst0hst_Dst02D0pi0_aLBu_(),
      Bu2Dst0hst_Dst02D0pi0_aRBu_(),
      Bu2Dst0hst_Dst02D0pi0_nLBu_(),
      Bu2Dst0hst_Dst02D0pi0_nRBu_(),
      Bu2Dst0hst_Dst02D0pi0_fracLRPdfBu_(),
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
          0.081, 0.0, 0.1),
      // ------------------ Gamma PART RECONSTRUCTED BACKGROUND
      // ------------------ //
      Bu2Dst0hst_Dst02D0gamma_meanDelta_(),
      Bu2Dst0hst_Dst02D0gamma_sigmaLDelta_(),
      Bu2Dst0hst_Dst02D0gamma_sigmaRDelta_(),
      Bu2Dst0hst_Dst02D0gamma_aRDelta_(),
      Bu2Dst0hst_Dst02D0gamma_aLDelta_(),
      Bu2Dst0hst_Dst02D0gamma_nRDelta_(),
      Bu2Dst0hst_Dst02D0gamma_nLDelta_(),
      pdfLDelta_Bu2Dst0hst_Dst02D0gamma_(),
      pdfRDelta_Bu2Dst0hst_Dst02D0gamma_(),
      Bu2Dst0hst_Dst02D0gamma_fracLRDelta_(),
      pdfDelta_Bu2Dst0hst_Dst02D0gamma_(),
      Bu2Dst0hst_Dst02D0gamma_a0MeanBu_(),
      Bu2Dst0hst_Dst02D0gamma_a1MeanBu_(),
      Bu2Dst0hst_Dst02D0gamma_a2MeanBu_(),
      Bu2Dst0hst_Dst02D0gamma_meanBu_(),
      Bu2Dst0hst_Dst02D0gamma_a0SigmaLBu_(),
      Bu2Dst0hst_Dst02D0gamma_a1SigmaLBu_(),
      Bu2Dst0hst_Dst02D0gamma_a2SigmaLBu_(),
      Bu2Dst0hst_Dst02D0gamma_a0SigmaRBu_(),
      Bu2Dst0hst_Dst02D0gamma_a1SigmaRBu_(),
      Bu2Dst0hst_Dst02D0gamma_a2SigmaRBu_(),
      Bu2Dst0hst_Dst02D0gamma_aLBu_(),
      Bu2Dst0hst_Dst02D0gamma_aRBu_(),
      Bu2Dst0hst_Dst02D0gamma_nLBu_(),
      Bu2Dst0hst_Dst02D0gamma_nRBu_(),
      Bu2Dst0hst_Dst02D0gamma_fracLRPdfBu_(),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_(),
      relativeBuWidth_Bu2Dst0hst_Dst02D0gamma_(),
      // ------------------ MIS RECONSTRUCTED BACKGROUND ------------------ //
      pdfDelta_misRec_(
          ("pdfDelta_misRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Delta_misRec PDF " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          Configuration::Get().deltaMass(), bkg_thresholdDelta_, bkg_cDelta_,
          bkg_aDelta_, bkg_bDelta_),
      // misRec_a0MeanBu_(
      //     ("misRec_a0MeanBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
      //     ("a0 of mean of misRec m[Bu] PDF " +
      //      ComposeName(uniqueId, Neutral::pi0))
      //         .c_str(),
      //     5260, 5210, 5310),
      // misRec_meanBu_(
      //     ("misRec_meanBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
      //     ("Mean of misRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
      //         .c_str(),
      //     Configuration::Get().deltaMass(), RooArgList(misRec_a0MeanBu_)),
      misRec_a0Mean1Bu_(),
      misRec_a1Mean1Bu_(),
      misRec_a2Mean1Bu_(),
      misRec_mean1Bu_(),
      misRec_a0Mean2Bu_(),
      misRec_a1Mean2Bu_(),
      misRec_a2Mean2Bu_(),
      misRec_mean2Bu_(),
      misRec_a0Mean3Bu_(),
      misRec_a1Mean3Bu_(),
      misRec_a2Mean3Bu_(),
      misRec_mean3Bu_(),
      misRec_a0Sigma1Bu_(),
      misRec_a1Sigma1Bu_(),
      misRec_a2Sigma1Bu_(),
      misRec_a0Sigma2Bu_(),
      misRec_a1Sigma2Bu_(),
      misRec_a2Sigma2Bu_(),
      misRec_a0Sigma3Bu_(),
      misRec_a1Sigma3Bu_(),
      misRec_a2Sigma3Bu_(),
      misRec_frac1PdfBu_(),
      misRec_frac2PdfBu_(),
      misRec_frac3PdfBu_(),
      ratioDst0KDst0pi_misRec_(),
      relativeBuWidth_misRec_(),
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
          RooFit::Conditional(pdfBu_Comb_, Configuration::Get().buMass())) {}
