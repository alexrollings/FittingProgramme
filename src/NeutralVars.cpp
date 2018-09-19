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
      sigmaDelta_Bu2Dst0h_Dst02D0gamma_(
          ("sigmaDelta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Sigma of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5, 0, 10),
      pdfDelta_Bu2Dst0h_Dst02D0gamma_(("pdfDelta_Bu2Dst0h_Dst02D0gamma_" +
                                       ComposeName(uniqueId, Neutral::gamma))
                                          .c_str(),
                                      ("Bu2Dst0h_Dst02D0gamma Delta PDF " +
                                       ComposeName(uniqueId, Neutral::gamma))
                                          .c_str(),
                                      Configuration::Get().deltaMass(),
                                      meanDelta_Bu2Dst0h_Dst02D0gamma(),
                                      sigmaDelta_Bu2Dst0h_Dst02D0gamma()),
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
      relativeBuWidth_Bu2Dst0h_Dst02D0gamma_(
          ("relativeBuWidth_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in Bu2Dst0h_Dst02D0gamma "
           "mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.95),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_(
          ("ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n Bu2Dst0h_Dst02D0gamma mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.081, 0.0, 0.1),
      // -------------------- PARTIAL PI0 -------------------- //
      meanDelta_Bu2Dst0h_Dst02D0pi0_(("meanDelta_Bu2Dst0h_Dst02D0pi0_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     ("Mean of Bu2Dst0h_Dst02D0pi0 m[Delta]" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     80, 70, 90),
      sigmaDelta_Bu2Dst0h_Dst02D0pi0_(
          ("sigmaDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Sigma of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          8, 0, 10),
      pdfDelta_Bu2Dst0h_Dst02D0pi0_(("pdfDelta_Bu2Dst0h_Dst02D0pi0_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    ("Bu2Dst0h_Dst02D0pi0 Delta PDF " +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    Configuration::Get().deltaMass(),
                                    meanDelta_Bu2Dst0h_Dst02D0pi0(),
                                    sigmaDelta_Bu2Dst0h_Dst02D0pi0()),
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
      meanBu_Bu2Dst0h_Dst02D0pi0_(("meanBu_Bu2Dst0h_Dst02D0pi0_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  ("Mean of Bu2Dst0h_Dst02D0pi0 m[Bu]" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  Configuration::Get().deltaMass(),
                                  RooArgList(a0MeanBu_Bu2Dst0h_Dst02D0pi0_,
                                             a1MeanBu_Bu2Dst0h_Dst02D0pi0_,
                                             a2MeanBu_Bu2Dst0h_Dst02D0pi0_)),
      relativeBuWidth_Bu2Dst0h_Dst02D0pi0_(
          ("relativeBuWidth_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in Bu2Dst0h_Dst02D0pi0 "
           "mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.95),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_(
          ("ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n Bu2Dst0h_Dst02D0pi0 mode " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          0.081, 0.0, 0.1),
      // ------------------ DSTD0BKG PARAMETERS (SHARED) ------------------ //
      thresholdDelta_bkg_(
          ("thresholdDelta_bkg_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          (" Delta_bkg thershold " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          43),
      cDelta_bkg_(
          ("cDelta_bkg_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          (" Delta_bkg c parameter " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 10, 0.001, 20),
          29, 0, 35),
      aDelta_bkg_(
          ("aDelta_bkg_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          (" Delta_bkg a parameter " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // -0.5, -1, 1),
          -0.044, -1, 1),
      bDelta_bkg_(
          ("bDelta_bkg_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          (" Delta_bkg b parameter " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 0.000001),  // -0.5, 0.5),
          0.00473, -1, 1),
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
          0.5, 0, 1),
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
                                     144, 139, 149),
      sigmaDelta_Bu2Dst0h_Dst02D0pi0_(
          ("sigmaDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Sigma of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          3, 0, 5),
      pdfDelta_Bu2Dst0h_Dst02D0pi0_(("pdfDelta_Bu2Dst0h_Dst02D0pi0_" +
                                       ComposeName(uniqueId, Neutral::pi0))
                                          .c_str(),
                                      ("Bu2Dst0h_Dst02D0pi0 Delta PDF " +
                                       ComposeName(uniqueId, Neutral::pi0))
                                          .c_str(),
                                      Configuration::Get().deltaMass(),
                                      meanDelta_Bu2Dst0h_Dst02D0pi0(),
                                      sigmaDelta_Bu2Dst0h_Dst02D0pi0()),
      a0MeanBu_Bu2Dst0h_Dst02D0pi0_(
          ("a0MeanBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a0 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          5000, 4950, 5050),
      a1MeanBu_Bu2Dst0h_Dst02D0pi0_(
          ("a1MeanBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("a1 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          3, 0, 10),
      a2MeanBu_Bu2Dst0h_Dst02D0pi0_(
          ("a2MeanBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
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
      relativeBuWidth_Bu2Dst0h_Dst02D0pi0_(
          ("relativeBuWidth_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Relative Width of k w.r.t. pi modes in Bu2Dst0h_Dst02D0pi0 "
           "mode " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          0.95),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_(
          ("ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n Bu2Dst0h_Dst02D0pi0 mode " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          0.081, 0.0, 0.1),
      // ------------------ NO CROSS FEED BECAUSE OF VETO ------------------ //
      meanDelta_Bu2Dst0h_Dst02D0gamma_(),
      sigmaDelta_Bu2Dst0h_Dst02D0gamma_(),
      pdfDelta_Bu2Dst0h_Dst02D0gamma_(),
      a0MeanBu_Bu2Dst0h_Dst02D0gamma_(),
      a1MeanBu_Bu2Dst0h_Dst02D0gamma_(),
      a2MeanBu_Bu2Dst0h_Dst02D0gamma_(),
      meanBu_Bu2Dst0h_Dst02D0gamma_(),
      relativeBuWidth_Bu2Dst0h_Dst02D0gamma_(),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_(),
      // ------------------ DSTD0BKG PARAMETERS (SHARED) ------------------ //
      thresholdDelta_bkg_(
          ("thresholdDelta_bkg_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg thershold " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          134.5),
      cDelta_bkg_(
          ("cDelta_bkg_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg c parameter " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 10, 0.001, 20),
          3.14),
      aDelta_bkg_(
          ("aDelta_bkg_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg a parameter " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // -0.5, -1, 1),
          -0.99),
      bDelta_bkg_(
          ("bDelta_bkg_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          (" Delta_bkg b parameter " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 0.01),  // -0.5, 0.5),
          -0.058),
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
