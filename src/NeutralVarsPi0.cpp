#include "NeutralVars.h"
#include "GlobalVars.h"

// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
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
          7.9439e+00),  // 2.3, 0, 5),
      aRBu_Bu2Dst0h_Dst02D0pi0_(
          ("aRBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("aR of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -8.6538e+00),  // 4.6, 0, 5),
      nLBu_Bu2Dst0h_Dst02D0pi0_(
          ("nLBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("nL of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          9.8579e+00),  // 3.4, 0, 5),
      nRBu_Bu2Dst0h_Dst02D0pi0_(
          ("nRBu_Bu2Dst0h_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("nR of Bu2Dst0h_Dst02D0pi0 " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          1.1800e+01),  // 3.5, 0, 5),
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
          0.07930, -1, 1),  //, 0.0, 0.1),
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
      // a0MeanBu_overRec_(
      //     ("a0MeanBu_overRec_" + ComposeName(uniqueId,
      //     Neutral::pi0)).c_str(),
      //     ("a0 of mean of overRec m[Bu] PDF " +
      //      ComposeName(uniqueId, Neutral::pi0))
      //         .c_str(),
      //     5520, 5470, 5570),
      // meanBu_overRec_(
      //     ("meanBu_overRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
      //     ("Mean of overRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
      //         .c_str(),
      //     Configuration::Get().deltaMass(), RooArgList(a0MeanBu_overRec_)),
      a0Mean1Bu_overRec_(),
      a1Mean1Bu_overRec_(),
      a2Mean1Bu_overRec_(),
      mean1Bu_overRec_(),
      a0Mean2Bu_overRec_(),
      a1Mean2Bu_overRec_(),
      a2Mean2Bu_overRec_(),
      mean2Bu_overRec_(),
      a0SigmaLBu_overRec_(),
      a1SigmaLBu_overRec_(),
      a2SigmaLBu_overRec_(),
      a0SigmaRBu_overRec_(),
      a1SigmaRBu_overRec_(),
      a2SigmaRBu_overRec_(),
      aLBu_overRec_(),
      aRBu_overRec_(),
      nLBu_overRec_(),
      nRBu_overRec_(),
      fracLRPdfBu_overRec_(),
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
      sigmaDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("sigmaDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Sigma of Bu2Dst0hst_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          3, 0, 5),
      fracPdfDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("fracPdfDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Fraction of flat pdf w.r.t. peaking pdf for partially "
           "reconstructed bkg " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          0.5, 0, 1),
      pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Delta_Bu2Dst0hst_Dst02D0pi0 flat bkg " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), thresholdDelta_bkg_, cDelta_bkg_,
          aDelta_bkg_, bDelta_bkg_),
      pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Delta peaking PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), meanDelta_Bu2Dst0h_Dst02D0pi0_,
          sigmaDelta_Bu2Dst0hst_Dst02D0pi0_),
      pdfDelta_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfDelta_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Delta PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          RooArgSet(pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0_,
                    pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_),
          fracPdfDelta_Bu2Dst0hst_Dst02D0pi0_),
      a0MeanBu_Bu2Dst0hst_Dst02D0pi0_(
          ("a0MeanBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 5100, 5050, 5150),
          4950, 4900, 5000),
      a1MeanBu_Bu2Dst0hst_Dst02D0pi0_(
          ("a1MeanBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 3, 0, 10),
          1.3, 0, 10),
      a2MeanBu_Bu2Dst0hst_Dst02D0pi0_(
          ("a2MeanBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a2 of mean of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -0.004, -0.1, 0.1),
      // -0.007, -0.1, 0.1),
      meanBu_Bu2Dst0hst_Dst02D0pi0_(
          ("meanBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Mean of Bu2Dst0hst_Dst02D0pi0 m[Bu]" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0MeanBu_Bu2Dst0hst_Dst02D0pi0_,
                     a1MeanBu_Bu2Dst0hst_Dst02D0pi0_,
                     a2MeanBu_Bu2Dst0hst_Dst02D0pi0_)),
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
      meanDelta_Bu2Dst0hst_Dst02D0gamma_(),
      sigmaLDelta_Bu2Dst0hst_Dst02D0gamma_(),
      sigmaRDelta_Bu2Dst0hst_Dst02D0gamma_(),
      aRDelta_Bu2Dst0hst_Dst02D0gamma_(),
      aLDelta_Bu2Dst0hst_Dst02D0gamma_(),
      nRDelta_Bu2Dst0hst_Dst02D0gamma_(),
      nLDelta_Bu2Dst0hst_Dst02D0gamma_(),
      pdfLDelta_Bu2Dst0hst_Dst02D0gamma_(),
      pdfRDelta_Bu2Dst0hst_Dst02D0gamma_(),
      fracLRDelta_Bu2Dst0hst_Dst02D0gamma_(),
      pdfDelta_Bu2Dst0hst_Dst02D0gamma_(),
      a0MeanBu_Bu2Dst0hst_Dst02D0gamma_(),
      a1MeanBu_Bu2Dst0hst_Dst02D0gamma_(),
      a2MeanBu_Bu2Dst0hst_Dst02D0gamma_(),
      meanBu_Bu2Dst0hst_Dst02D0gamma_(),
      a0SigmaLBu_Bu2Dst0hst_Dst02D0gamma_(),
      a1SigmaLBu_Bu2Dst0hst_Dst02D0gamma_(),
      a2SigmaLBu_Bu2Dst0hst_Dst02D0gamma_(),
      a0SigmaRBu_Bu2Dst0hst_Dst02D0gamma_(),
      a1SigmaRBu_Bu2Dst0hst_Dst02D0gamma_(),
      a2SigmaRBu_Bu2Dst0hst_Dst02D0gamma_(),
      aLBu_Bu2Dst0hst_Dst02D0gamma_(),
      aRBu_Bu2Dst0hst_Dst02D0gamma_(),
      nLBu_Bu2Dst0hst_Dst02D0gamma_(),
      nRBu_Bu2Dst0hst_Dst02D0gamma_(),
      fracLRPdfBu_Bu2Dst0hst_Dst02D0gamma_(),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_(),
      relativeBuWidth_Bu2Dst0hst_Dst02D0gamma_(),
      // ------------------ MIS RECONSTRUCTED BACKGROUND ------------------ //
      pdfDelta_misRec_(
          ("pdfDelta_misRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Delta_misRec PDF " + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          Configuration::Get().deltaMass(), thresholdDelta_bkg_, cDelta_bkg_,
          aDelta_bkg_, bDelta_bkg_),
      // a0MeanBu_misRec_(
      //     ("a0MeanBu_misRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
      //     ("a0 of mean of misRec m[Bu] PDF " +
      //      ComposeName(uniqueId, Neutral::pi0))
      //         .c_str(),
      //     5260, 5210, 5310),
      // meanBu_misRec_(
      //     ("meanBu_misRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
      //     ("Mean of misRec m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
      //         .c_str(),
      //     Configuration::Get().deltaMass(), RooArgList(a0MeanBu_misRec_)),
      a0Mean1Bu_misRec_(),
      a1Mean1Bu_misRec_(),
      a2Mean1Bu_misRec_(),
      mean1Bu_misRec_(),
      a0Mean2Bu_misRec_(),
      a1Mean2Bu_misRec_(),
      a2Mean2Bu_misRec_(),
      mean2Bu_misRec_(),
      a0Mean3Bu_misRec_(),
      a1Mean3Bu_misRec_(),
      a2Mean3Bu_misRec_(),
      mean3Bu_misRec_(),
      a0Sigma1Bu_misRec_(),
      a1Sigma1Bu_misRec_(),
      a2Sigma1Bu_misRec_(),
      a0Sigma2Bu_misRec_(),
      a1Sigma2Bu_misRec_(),
      a2Sigma2Bu_misRec_(),
      a0Sigma3Bu_misRec_(),
      a1Sigma3Bu_misRec_(),
      a2Sigma3Bu_misRec_(),
      frac1PdfBu_misRec_(),
      frac2PdfBu_misRec_(),
      frac3PdfBu_misRec_(),
      ratioDst0KDst0pi_misRec_(),
      relativeBuWidth_misRec_(),
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
