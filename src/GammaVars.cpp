#include "GlobalVars.h"
#include "NeutralVars.h"
#include "Params.h"

// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::gamma>::NeutralVars(int uniqueId)
    // -------------------- PDF SHAPES -------------------- //
    // -------------------- Bu2Dst0h_D0gamma -------------------- //
    : uniqueId_(uniqueId),
      Bu2Dst0h_D0gamma_meanDelta_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0gamma_meanDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, 135, 150)),
      Bu2Dst0h_D0gamma_KpiSigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_KpiSigmaDelta", uniqueId_, Neutral::gamma,
          1.0402e+00, 2.46e-02, Systematic::gammaDeltaWidthRatio, Sign::same)),
      // Bu2Dst0h_D0gamma_KpiSigmaDelta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0gamma_KpiSigmaDelta", uniqueId_, Neutral::gamma,
      //     0.99278, 0.9, 1.1)),
      Bu2Dst0h_D0gamma_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::gammaDeltaTails, Sign::same)),
      Bu2Dst0h_D0gamma_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::gammaDeltaTails, Sign::same)),
      // Bu2Dst0h_D0gamma_a2Delta_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0gamma_a2Delta", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0gamma, Systematic::gammaDeltaTails, Sign::same)),
      Bu2Dst0h_D0gamma_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a2Delta", uniqueId_, Neutral::gamma, -6.7782e-01,
          1.28e-02, Systematic::gammaDeltaTails, Sign::same)),
      // Bu2Dst0h_D0gamma_a2Delta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0gamma_a2Delta", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0gamma, -5, -0.00001)),
      Bu2Dst0h_D0gamma_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n2Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::gammaDeltaTails, Sign::same)),
      Bu2Dst0h_D0gamma_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_fracPdf1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::gammaDeltaFrac, Sign::same)),
      Bu2Dst0h_D0gamma_meanBu_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0gamma_meanBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, 5275, 5285)),
      Bu2Dst0h_D0gamma_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_KpiSigmaBu", uniqueId_, Neutral::gamma, 9.8368e-01,
          2.06e-02, Systematic::gammaBuWidthRatio, Sign::same)),
      // Bu2Dst0h_D0gamma_KpiSigmaBu_(
      //     Params::Get().CreateFloating("Bu2Dst0h_D0gamma_KpiSigmaBu",
      //     uniqueId_,
      //                                  Neutral::gamma, 0.957103, 0.9, 1.1)),
      Bu2Dst0h_D0gamma_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::gammaBuTails, Sign::same)),
      Bu2Dst0h_D0gamma_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::gammaBuTails, Sign::same)),
      Bu2Dst0h_D0gamma_a2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a2Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::gammaBuTails, Sign::same)),
      Bu2Dst0h_D0gamma_n2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n2Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::gammaBuTails, Sign::same)),
      Bu2Dst0h_D0gamma_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_fracPdf1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::gammaBuFrac, Sign::same)),
      Bu2Dst0h_D0gamma_meanBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_meanBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::crossFeedBuPartialPdf,
          Sign::same)),
      Bu2Dst0h_D0gamma_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::crossFeedBuPartialPdf,
          Sign::same)),
      // -------------------- Bu2Dst0h_D0gamma_FAVasSUP -------------------- //
      Bu2Dst0h_D0gamma_FAVasSUP_meanDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_meanDelta", uniqueId_, Neutral::gamma,
          1.4448e+02, 8.73e-01, Systematic::gammaFAVasSUPDeltaPdf, Sign::same)),
      Bu2Dst0h_D0gamma_FAVasSUP_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_sigmaDelta", uniqueId_, Neutral::gamma,
          9.9175e+00, 9.85e-01, Systematic::gammaFAVasSUPDeltaPdf, Sign::same)),
      Bu2Dst0h_D0gamma_FAVasSUP_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_a1Delta", uniqueId_, Neutral::gamma,
          1.0314e+00, 2.90e-01, Systematic::gammaFAVasSUPDeltaPdf, Sign::same)),
      Bu2Dst0h_D0gamma_FAVasSUP_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_a2Delta", uniqueId_, Neutral::gamma,
          -4.9581e-01, 2.78e-01, Systematic::gammaFAVasSUPDeltaPdf,
          Sign::same)),
      Bu2Dst0h_D0gamma_FAVasSUP_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_n1Delta", uniqueId_, Neutral::gamma,
          1.0000e+01, 1.00, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0gamma_FAVasSUP_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_n2Delta", uniqueId_, Neutral::gamma,
          2.9165e+00, 1.00, Systematic::NA, Sign::same)),
      pdf1Delta_Bu2Dst0h_D0gamma_FAVasSUP_(
          ("pdf1Delta_Bu2Dst0h_D0gamma_FAVasSUP_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0gamma_FAVasSUP_meanDelta_,
          *Bu2Dst0h_D0gamma_FAVasSUP_sigmaDelta_,
          *Bu2Dst0h_D0gamma_FAVasSUP_a1Delta_,
          *Bu2Dst0h_D0gamma_FAVasSUP_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0gamma_FAVasSUP_(
          ("pdf2Delta_Bu2Dst0h_D0gamma_FAVasSUP_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0gamma_FAVasSUP_meanDelta_,
          *Bu2Dst0h_D0gamma_FAVasSUP_sigmaDelta_,
          *Bu2Dst0h_D0gamma_FAVasSUP_a2Delta_,
          *Bu2Dst0h_D0gamma_FAVasSUP_n2Delta_),
      Bu2Dst0h_D0gamma_FAVasSUP_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_fracPdf1Delta", uniqueId_, Neutral::gamma,
          3.9419e-01, 2.37e-01, Systematic::gammaFAVasSUPDeltaPdf, Sign::same)),
      pdfDelta_Bu2Dst0h_D0gamma_FAVasSUP_(
          ("pdfDelta_Bu2Dst0h_D0gamma_FAVasSUP_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0gamma_FAVasSUP_,
                     pdf2Delta_Bu2Dst0h_D0gamma_FAVasSUP_),
          *Bu2Dst0h_D0gamma_FAVasSUP_fracPdf1Delta_),
      Bu2Dst0h_D0gamma_FAVasSUP_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_meanBu", uniqueId_, Neutral::gamma,
          5.2790e+03, 2.62e+00, Systematic::gammaFAVasSUPBuPdf, Sign::same)),
      Bu2Dst0h_D0gamma_FAVasSUP_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_sigmaBu", uniqueId_, Neutral::gamma,
          9.2045e+01, 1.95e+00, Systematic::gammaFAVasSUPBuPdf, Sign::same)),
      Bu2Dst0h_D0gamma_FAVasSUP_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_a1Bu", uniqueId_, Neutral::gamma,
          2.6730e+00, 1.23e-01, Systematic::gammaFAVasSUPBuPdf, Sign::none)),
      Bu2Dst0h_D0gamma_FAVasSUP_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_n1Bu", uniqueId_, Neutral::gamma,
          7.5377e-07, 1.60e-01, Systematic::gammaFAVasSUPBuPdf, Sign::same)),
      pdfBu_Bu2Dst0h_D0gamma_FAVasSUP_(("pdfBu_Bu2Dst0h_D0gamma_FAVasSUP_" +
                                        ComposeName(uniqueId_, Neutral::gamma))
                                           .c_str(),
                                       "", Configuration::Get().deltaMass(),
                                       *Bu2Dst0h_D0gamma_FAVasSUP_meanBu_,
                                       *Bu2Dst0h_D0gamma_FAVasSUP_sigmaBu_,
                                       *Bu2Dst0h_D0gamma_FAVasSUP_a1Bu_,
                                       *Bu2Dst0h_D0gamma_FAVasSUP_n1Bu_),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      Bu2Dst0h_D0pi0_meanDelta_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_meanDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, 75, 95)),
      Bu2Dst0h_D0pi0_KpiSigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_KpiSigmaDelta", uniqueId_, Neutral::gamma, 1.0341e+00,
          3.92e-02, Systematic::pi0DeltaWidthRatio, Sign::same)),
      // Bu2Dst0h_D0pi0_KpiSigmaDelta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_KpiSigmaDelta", uniqueId_, Neutral::gamma,
      //     0.979346, 0.9, 1.1)),
      // Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::same)),
      Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::gamma, 3.4363e-01,
          3.87e-02, Systematic::pi0DeltaTails, Sign::same)),
      // Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0pi0, 0, 5)),
      Bu2Dst0h_D0pi0_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::same)),
      Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::same)),
      Bu2Dst0h_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::same)),
      Bu2Dst0h_D0pi0_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaFrac, Sign::same)),
      Bu2Dst0h_D0pi0_mean1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_mean1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::crossFeedBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_meanOffset21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::crossFeedBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_mean2Bu_(
          ("Bu2Dst0h_D0pi0_mean2Bu" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0+@1",
          RooArgList(*Bu2Dst0h_D0pi0_mean1Bu_,
                     *Bu2Dst0h_D0pi0_meanOffset21Bu_)),
      Bu2Dst0h_D0pi0_sigmaRatio21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_sigmaRatio21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::crossFeedBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_KpiSigmaBu", uniqueId_, Neutral::gamma, 1.0, 0.0,
          Systematic::crossFeedBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::crossFeedBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_a2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::crossFeedBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::crossFeedBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_n2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::crossFeedBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::crossFeedBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_mean1BuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_mean1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, 5280, 5310)),
      Bu2Dst0h_D0pi0_meanOffset31BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_meanOffset31BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::crossFeedBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_mean3BuPartial_(
          ("Bu2Dst0h_D0pi0_mean3BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0+@1",
          RooArgSet(*Bu2Dst0h_D0pi0_mean1BuPartial_,
                    *Bu2Dst0h_D0pi0_meanOffset31BuPartial_)),
      Bu2Dst0h_D0pi0_KpiSigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_KpiSigmaBuPartial", uniqueId_, Neutral::gamma,
          9.4705e-01, 2.53e-02, Systematic::pi0BuPartialWidthRatio,
          Sign::same)),
      // Bu2Dst0h_D0pi0_KpiSigmaBuPartial_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_KpiSigmaBuPartial", uniqueId_, Neutral::gamma,
      //     0.959297, 0.9, 1.1)),
      Bu2Dst0h_D0pi0_sigmaRatio21BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_sigmaRatio21BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::crossFeedBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_sigmaRatio31BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_sigmaRatio31BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::crossFeedBuPdf, Sign::same)),
      // Bu2Dst0h_D0pi0_a1BuPartial_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_a1BuPartial", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0pi0, Systematic::pi0BuPartialTails, Sign::same)),
      Bu2Dst0h_D0pi0_a1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1BuPartial", uniqueId_, Neutral::gamma, 1.8866e+00,
          4.94e-02, Systematic::pi0BuPartialTails, Sign::same)),
      // Bu2Dst0h_D0pi0_a1BuPartial_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_a1BuPartial", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0pi0, 0, 5)),
      Bu2Dst0h_D0pi0_n1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0BuPartialTails, Sign::same)),
      // Bu2Dst0h_D0pi0_a2BuPartial_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_a2BuPartial", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0pi0, Systematic::pi0BuPartialTails, Sign::same)),
      Bu2Dst0h_D0pi0_a2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2BuPartial", uniqueId_, Neutral::gamma, -1.4538e+00,
          6.43e-02, Systematic::pi0BuPartialTails, Sign::same)),
      // Bu2Dst0h_D0pi0_a2BuPartial_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_a2BuPartial", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0pi0, -5, -0.000001)),
      Bu2Dst0h_D0pi0_n2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0BuPartialTails, Sign::same)),
      Bu2Dst0h_D0pi0_fracPdf1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0BuPartialFrac, Sign::same)),
      Bu2Dst0h_D0pi0_fracPdf2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf2BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0BuPartialFrac, Sign::same)),
      // -------------------- Bu2Dst0h_D0gamma_WN -------------------- //
      Bu2Dst0h_D0gamma_WN_thresholdDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_thresholdDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNDeltaPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_aDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_aDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNDeltaPdf, Sign::none)),
      Bu2Dst0h_D0gamma_WN_bDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_bDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNDeltaPdf, Sign::none)),
      Bu2Dst0h_D0gamma_WN_cDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_cDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNDeltaPdf, Sign::same)),
      pdfDelta_Bu2Dst0h_D0gamma_WN_(new RooDstD0BG(
          ("pdfDelta_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0gamma_WN_thresholdDelta_, *Bu2Dst0h_D0gamma_WN_cDelta_,
          *Bu2Dst0h_D0gamma_WN_aDelta_, *Bu2Dst0h_D0gamma_WN_bDelta_)),
      Bu2Dst0h_D0gamma_WN_mean1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_mean1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNBuPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_meanOffset21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNBuPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_mean2Bu_(
          ("Bu2Dst0h_D0gamma_WN_mean2Bu_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0+@1",
          RooArgSet(*Bu2Dst0h_D0gamma_WN_mean1Bu_,
                    *Bu2Dst0h_D0gamma_WN_meanOffset21Bu_)),
      // Bu2Dst0h_D0gamma_WN_KpiSigmaBu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0gamma_WN_KpiSigmaBu", uniqueId_, Neutral::gamma, 0.95,
      //     0.5, 1.5)),
      Bu2Dst0h_D0gamma_WN_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_KpiSigmaBu", uniqueId_, Neutral::gamma, 1.0,
          0.05, Systematic::gammaWNBuPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_sigmaRatio21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_sigmaRatio21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNBuPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_a1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNBuPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_n1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNBuPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_fracPdf1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNBuPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_meanBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_meanBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNBuPartialPdf,
          Sign::same)),
      Bu2Dst0h_D0gamma_WN_KpiSigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_KpiSigmaBuPartial", uniqueId_, Neutral::gamma,
          1.0, 0.0, Systematic::gammaWNBuPartialPdf, Sign::same)),
      // -------------------- Bu2Dst0h_D0pi0_WN -------------------- //
      Bu2Dst0h_D0pi0_WN_thresholdDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_thresholdDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNDeltaPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_cDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_cDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNDeltaPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_mean1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_mean1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_meanOffset21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::none)),
      Bu2Dst0h_D0pi0_WN_mean2Bu_(("Bu2Dst0h_D0pi0_WN_mean2Bu_" +
                                  ComposeName(uniqueId_, Neutral::gamma))
                                     .c_str(),
                                 "@0+@1",
                                 RooArgSet(*Bu2Dst0h_D0pi0_WN_mean1Bu_,
                                           *Bu2Dst0h_D0pi0_WN_meanOffset21Bu_)),
      // Bu2Dst0h_D0pi0_WN_KpiSigmaBu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_KpiSigmaBu", uniqueId_, Neutral::gamma,
      //     0.95, 0.5, 1.5)),
      Bu2Dst0h_D0pi0_WN_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_KpiSigmaBu", uniqueId_, Neutral::gamma, 0.975858,
          0.021574, Systematic::pi0WNBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_sigmaRatio21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_sigmaRatio21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_a1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::same)),
      // Bu2Dst0h_D0pi0_WN_a1Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_a1Bu", uniqueId_, Neutral::gamma,
      //     1, 0, 5)),
      Bu2Dst0h_D0pi0_WN_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_n1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_a2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_a2Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::same)),
      // Bu2Dst0h_D0pi0_WN_a2Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_a2Bu", uniqueId_, Neutral::gamma,
      //     -1, -5, -0.00001)),
      Bu2Dst0h_D0pi0_WN_n2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_n2Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_fracPdf1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_mean1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_mean1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
      // Bu2Dst0h_D0pi0_WN_mean1BuPartial_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_mean1BuPartial", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0pi0_WN, 5270, 5290)),
      Bu2Dst0h_D0pi0_WN_meanOffset31BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_meanOffset31BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::none)),
      Bu2Dst0h_D0pi0_WN_mean3BuPartial_(
          ("Bu2Dst0h_D0pi0_WN_mean3BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0+@1",
          RooArgSet(*Bu2Dst0h_D0pi0_WN_mean1BuPartial_,
                    *Bu2Dst0h_D0pi0_WN_meanOffset31BuPartial_)),
      // Bu2Dst0h_D0pi0_WN_KpiSigmaBuPartial_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_KpiSigmaBuPartial", uniqueId_, Neutral::gamma,
      //     0.95, 0.5, 1.5)),
      Bu2Dst0h_D0pi0_WN_KpiSigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_KpiSigmaBuPartial", uniqueId_, Neutral::gamma,
          0.937220, 0.059189, Systematic::pi0WNBuPartialPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_sigmaRatio21BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_sigmaRatio21BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_sigmaRatio31BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_sigmaRatio31BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_a1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_a1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
      // Bu2Dst0h_D0pi0_WN_a1BuPartial_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_WN_a1BuPartial", uniqueId_, Neutral::gamma,
      //     8.2891e-01, 1.60e-01, Systematic::pi0WNBuPartialPdf, Sign::same)),
      // Bu2Dst0h_D0pi0_WN_a1BuPartial_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_a1BuPartial", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0pi0_WN, 0, 5)),
      Bu2Dst0h_D0pi0_WN_n1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_n1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_a2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_a2BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
      // Bu2Dst0h_D0pi0_WN_a2BuPartial_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_WN_a2BuPartial", uniqueId_, Neutral::gamma,
      //     -3.8030e+00, 8.04e-01, Systematic::pi0WNBuPartialPdf, Sign::same)),
      // Bu2Dst0h_D0pi0_WN_a2BuPartial_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_a2BuPartial", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0pi0_WN, -5, -0.000001)),
      Bu2Dst0h_D0pi0_WN_n2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_n2BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_fracPdf1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_fracPdf1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_fracPdf2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_fracPdf2BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
      // -------------------- Bu2Dst0h_WN -------------------- //
      Bu2Dst0h_WN_floatingFracD0pi0_(nullptr),
      // -------------------- Bu2Dst0h_D0pi0_FAVasSUP -------------------- //
      Bu2Dst0h_D0pi0_FAVasSUP_meanDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_meanDelta", uniqueId_, Neutral::gamma,
          8.0373e+01, 2.94e-01, Systematic::pi0FAVasSUPDeltaPdf, Sign::same)),
      Bu2Dst0h_D0pi0_FAVasSUP_sigma1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_sigma1Delta", uniqueId_, Neutral::gamma,
          2.7182e+01, 1.27e+00, Systematic::pi0FAVasSUPDeltaPdf, Sign::same)),
      Bu2Dst0h_D0pi0_FAVasSUP_sigma2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_sigma2Delta", uniqueId_, Neutral::gamma,
          1.5428e+01, 4.44e-01, Systematic::pi0FAVasSUPDeltaPdf, Sign::same)),
      Bu2Dst0h_D0pi0_FAVasSUP_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_a1Delta", uniqueId_, Neutral::gamma,
          2.2712e+00, 1.00, Systematic::NA, Sign::none)),
      Bu2Dst0h_D0pi0_FAVasSUP_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_a2Delta", uniqueId_, Neutral::gamma,
          -1.1218e+00, 1.00, Systematic::NA, Sign::none)),
      Bu2Dst0h_D0pi0_FAVasSUP_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_n1Delta", uniqueId_, Neutral::gamma,
          2.0098e+00, 1.00, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_FAVasSUP_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_n2Delta", uniqueId_, Neutral::gamma,
          2.0519e+00, 1.00, Systematic::NA, Sign::same)),
      pdf1Delta_Bu2Dst0h_D0pi0_FAVasSUP_(
          ("pdf1Delta_Bu2Dst0h_D0pi0_FAVasSUP_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0pi0_FAVasSUP_meanDelta_,
          *Bu2Dst0h_D0pi0_FAVasSUP_sigma1Delta_,
          *Bu2Dst0h_D0pi0_FAVasSUP_a1Delta_, *Bu2Dst0h_D0pi0_FAVasSUP_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0pi0_FAVasSUP_(
          ("pdf2Delta_Bu2Dst0h_D0pi0_FAVasSUP_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0pi0_FAVasSUP_meanDelta_,
          *Bu2Dst0h_D0pi0_FAVasSUP_sigma2Delta_,
          *Bu2Dst0h_D0pi0_FAVasSUP_a2Delta_, *Bu2Dst0h_D0pi0_FAVasSUP_n2Delta_),
      Bu2Dst0h_D0pi0_FAVasSUP_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_fracPdf1Delta", uniqueId_, Neutral::gamma,
          3.1093e-01, 3.19e-02, Systematic::pi0FAVasSUPDeltaPdf, Sign::same)),
      pdfDelta_Bu2Dst0h_D0pi0_FAVasSUP_(
          new RooAddPdf(("pdfDelta_Bu2Dst0h_D0pi0_FAVasSUP_" +
                         ComposeName(uniqueId_, Neutral::gamma))
                            .c_str(),
                        "",
                        RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_FAVasSUP_,
                                   pdf2Delta_Bu2Dst0h_D0pi0_FAVasSUP_),
                        *Bu2Dst0h_D0pi0_FAVasSUP_fracPdf1Delta_)),
      Bu2Dst0h_D0pi0_FAVasSUP_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_meanBu", uniqueId_, Neutral::gamma,
          5.2946e+03, 2.83e+00, Systematic::pi0FAVasSUPBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_FAVasSUP_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_sigmaBu", uniqueId_, Neutral::gamma,
          1.0716e+02, 2.38e+00, Systematic::pi0FAVasSUPBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_FAVasSUP_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_a1Bu", uniqueId_, Neutral::gamma, 1.3827e+00,
          1.13e-01, Systematic::pi0FAVasSUPBuPdf, Sign::none)),
      Bu2Dst0h_D0pi0_FAVasSUP_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_n1Bu", uniqueId_, Neutral::gamma, 1.0000e+01,
          1.00, Systematic::NA, Sign::same)),
      pdfBu_Bu2Dst0h_D0pi0_FAVasSUP_(
          ("pdfBu_Bu2Dst0h_D0pi0_FAVasSUP_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0pi0_FAVasSUP_meanBu_, *Bu2Dst0h_D0pi0_FAVasSUP_sigmaBu_,
          *Bu2Dst0h_D0pi0_FAVasSUP_a1Bu_, *Bu2Dst0h_D0pi0_FAVasSUP_n1Bu_),
      Bu2Dst0h_D0pi0_FAVasSUP_meanBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_meanBuPartial", uniqueId_, Neutral::gamma,
          5.2716e+03, 7.49e-01, Systematic::pi0FAVasSUPBuPartialPdf,
          Sign::same)),
      Bu2Dst0h_D0pi0_FAVasSUP_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_sigmaBuPartial", uniqueId_, Neutral::gamma,
          9.7158e+01, 5.59e-01, Systematic::pi0FAVasSUPBuPartialPdf,
          Sign::same)),
      Bu2Dst0h_D0pi0_FAVasSUP_a1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_a1BuPartial", uniqueId_, Neutral::gamma,
          2.7829e+00, 3.02e-01, Systematic::pi0FAVasSUPBuPartialPdf,
          Sign::none)),
      Bu2Dst0h_D0pi0_FAVasSUP_n1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_n1BuPartial", uniqueId_, Neutral::gamma,
          1.3591e+00, 1.00, Systematic::NA, Sign::same)),
      pdfBuPartial_Bu2Dst0h_D0pi0_FAVasSUP_(
          ("pdfBuPartial_Bu2Dst0h_D0pi0_FAVasSUP_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0pi0_FAVasSUP_meanBuPartial_,
          *Bu2Dst0h_D0pi0_FAVasSUP_sigmaBuPartial_,
          *Bu2Dst0h_D0pi0_FAVasSUP_a1BuPartial_,
          *Bu2Dst0h_D0pi0_FAVasSUP_n1BuPartial_),
      // -------------------- Bd2Dsth -------------------- //
      Bd2Dsth_thresholdDelta_(Params::Get().CreateFixed(
          "Bd2Dsth_thresholdDelta", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthDeltaPdf, Sign::same)),
      Bd2Dsth_aDelta_(Params::Get().CreateFixed(
          "Bd2Dsth_aDelta", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthDeltaPdf, Sign::none)),
      Bd2Dsth_bDelta_(Params::Get().CreateFixed(
          "Bd2Dsth_bDelta", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthDeltaPdf, Sign::none)),
      Bd2Dsth_cDelta_(Params::Get().CreateFixed(
          "Bd2Dsth_cDelta", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthDeltaPdf, Sign::same)),
      pdfDelta_Bd2Dsth_(
          ("pdfDelta_Bd2Dsth_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bd2Dsth_thresholdDelta_,
          *Bd2Dsth_cDelta_, *Bd2Dsth_aDelta_, *Bd2Dsth_bDelta_),
      Bd2Dsth_mean1Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_mean1Bu", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthBuPdf, Sign::same)),
      Bd2Dsth_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_meanOffset21Bu", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthBuPdf, Sign::none)),
      Bd2Dsth_mean2Bu_(
          ("Bd2Dsth_mean2Bu_" + ComposeName(uniqueId_, Neutral::gamma)).c_str(),
          "", "@0+@1", RooArgSet(*Bd2Dsth_mean1Bu_, *Bd2Dsth_meanOffset21Bu_)),
      Bd2Dsth_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bd2Dsth_KpiSigmaBu", uniqueId_, Neutral::gamma, 1.0, 0.05,
          Systematic::Bd2DsthBuPdf, Sign::same)),
      Bd2Dsth_sigmaRatio21Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_sigmaRatio21Bu", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthBuPdf, Sign::same)),
      Bd2Dsth_a1Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_a1Bu", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthBuPdf, Sign::same)),
      Bd2Dsth_n1Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_n1Bu", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthBuPdf, Sign::same)),
      Bd2Dsth_a2Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_a2Bu", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthBuPdf, Sign::same)),
      Bd2Dsth_n2Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_n2Bu", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthBuPdf, Sign::same)),
      Bd2Dsth_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_fracPdf1Bu", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthBuPdf, Sign::same)),
      Bd2Dsth_mean1BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_mean1BuPartial", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthBuPartialPdf, Sign::same)),
      // Bd2Dsth_mean1BuPartial_(Params::Get().CreateFloating(
      //     "Bd2Dsth_mean1BuPartial", uniqueId_, Neutral::gamma,
      //     Mode::Bd2Dstpi, 5340, 5360)),
      Bd2Dsth_meanOffset21BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_meanOffset21BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bd2Dstpi, Systematic::Bd2DsthBuPartialPdf, Sign::none)),
      Bd2Dsth_mean2BuPartial_(
          ("Bd2Dsth_mean2BuPartial_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", "@0+@1",
          RooArgSet(*Bd2Dsth_mean1BuPartial_, *Bd2Dsth_meanOffset21BuPartial_)),
      Bd2Dsth_KpiSigmaBuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_KpiSigmaBuPartial", uniqueId_, Neutral::gamma, 1.0, 0.05,
          Systematic::Bd2DsthBuPartialPdf, Sign::same)),
      Bd2Dsth_sigmaRatio21BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_sigmaRatio21BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bd2Dstpi, Systematic::Bd2DsthBuPartialPdf, Sign::same)),
      Bd2Dsth_a1BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_a1BuPartial", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthBuPartialPdf, Sign::same)),
      Bd2Dsth_n1BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_n1BuPartial", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthBuPartialPdf, Sign::same)),
      Bd2Dsth_a2BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_a2BuPartial", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthBuPartialPdf, Sign::same)),
      Bd2Dsth_n2BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_n2BuPartial", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2DsthBuPartialPdf, Sign::same)),
      Bd2Dsth_fracPdf1BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_fracPdf1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bd2Dstpi, Systematic::Bd2DsthBuPartialPdf, Sign::same)),
      // -------------------- Bu2D0hst -------------------- //
      Bu2D0hst_thresholdDelta_(Params::Get().CreateFixed(
          "Bu2D0hst_thresholdDelta", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hstDeltaPdf, Sign::same)),
      Bu2D0hst_aDelta_(Params::Get().CreateFixed(
          "Bu2D0hst_aDelta", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hstDeltaPdf, Sign::none)),
      Bu2D0hst_bDelta_(Params::Get().CreateFixed(
          "Bu2D0hst_bDelta", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hstDeltaPdf, Sign::none)),
      Bu2D0hst_cDelta_(Params::Get().CreateFixed(
          "Bu2D0hst_cDelta", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hstDeltaPdf, Sign::same)),
      pdfDelta_Bu2D0hst_(
          ("pdfDelta_Bu2D0hst_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2D0hst_thresholdDelta_,
          *Bu2D0hst_cDelta_, *Bu2D0hst_aDelta_, *Bu2D0hst_bDelta_),
      Bu2D0hst_mean1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_mean1Bu", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hstBuPdf, Sign::same)),
      // Bu2D0hst_mean1Bu_(Params::Get().CreateFloating(
      //     "Bu2D0hst_mean1Bu", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
      //     5150, 5250)),
      Bu2D0hst_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_meanOffset21Bu", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hstBuPdf, Sign::none)),
      Bu2D0hst_mean2Bu_(
          ("Bu2D0hst_mean2Bu_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", "@0+@1",
          RooArgSet(*Bu2D0hst_mean1Bu_, *Bu2D0hst_meanOffset21Bu_)),
      Bu2D0hst_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2D0hst_KpiSigmaBu", uniqueId_, Neutral::gamma, 1.0, 0.05,
          Systematic::Bu2D0hstBuPdf, Sign::same)),
      Bu2D0hst_sigmaRatio21Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_sigmaRatio21Bu", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hstBuPdf, Sign::same)),
      Bu2D0hst_a1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_a1Bu", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hstBuPdf, Sign::same)),
      // Bu2D0hst_a1Bu_(Params::Get().CreateFloating(
      //     "Bu2D0hst_a1Bu", uniqueId_, Neutral::gamma, Mode::Bu2D0rho, 0, 5)),
      Bu2D0hst_n1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_n1Bu", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hstBuPdf, Sign::same)),
      Bu2D0hst_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_fracPdf1Bu", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hstBuPdf, Sign::same)),
      Bu2D0hst_meanBuPartial_(Params::Get().CreateFixed(
          "Bu2D0hst_meanBuPartial", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hstBuPartialPdf, Sign::same)),
      // Bu2D0hst_meanBuPartial_(Params::Get().CreateFloating(
      //     "Bu2D0hst_meanBuPartial", uniqueId_, Neutral::gamma,
      //     Mode::Bu2D0rho, 5250, 5270)),
      Bu2D0hst_KpiSigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2D0hst_KpiSigmaBuPartial", uniqueId_, Neutral::gamma, 1.0, 0.05,
          Systematic::Bu2D0hstBuPartialPdf, Sign::same)),
      // -------------------- Bu2Dst0hst_D0gamma -------------------- //
      Bu2Dst0hst_D0gamma_meanDelta_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_meanDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gammaDeltaPdf,
          Sign::same)),
      Bu2Dst0hst_D0gamma_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_sigmaDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gammaDeltaPdf,
          Sign::same)),
      pdfDelta_Bu2Dst0hst_D0gamma_(("pdfDelta_Bu2Dst0hst_D0gamma_" +
                                    ComposeName(uniqueId_, Neutral::gamma))
                                       .c_str(),
                                   "", Configuration::Get().deltaMass(),
                                   *Bu2Dst0hst_D0gamma_meanDelta_,
                                   *Bu2Dst0hst_D0gamma_sigmaDelta_),
      Bu2Dst0hst_D0gamma_mean1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_mean1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gammaBuPdf,
          Sign::same)),
      // Bu2Dst0hst_D0gamma_mean1Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0hst_D0gamma_mean1Bu", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0rho_D0gamma, 5070, 5170)),
      Bu2Dst0hst_D0gamma_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_meanOffset21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gammaBuPdf,
          Sign::none)),
      Bu2Dst0hst_D0gamma_mean2Bu_(
          ("Bu2Dst0hst_D0gamma_mean2Bu_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", "@0+@1",
          RooArgSet(*Bu2Dst0hst_D0gamma_mean1Bu_,
                    *Bu2Dst0hst_D0gamma_meanOffset21Bu_)),
      Bu2Dst0hst_D0gamma_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_KpiSigmaBu", uniqueId_, Neutral::gamma, 1.0, 0.05,
          Systematic::Bu2Dst0hst_D0gammaBuPdf, Sign::same)),
      Bu2Dst0hst_D0gamma_sigmaRatio21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_sigmaRatio21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gammaBuPdf,
          Sign::same)),
      Bu2Dst0hst_D0gamma_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_a1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gammaBuPdf,
          Sign::same)),
      Bu2Dst0hst_D0gamma_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_n1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gammaBuPdf,
          Sign::same)),
      Bu2Dst0hst_D0gamma_a2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_a2Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gammaBuPdf,
          Sign::same)),
      Bu2Dst0hst_D0gamma_n2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_n2Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gammaBuPdf,
          Sign::same)),
      Bu2Dst0hst_D0gamma_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_fracPdf1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gammaBuPdf,
          Sign::same)),
      Bu2Dst0hst_D0gamma_meanBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_meanBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gammaBuPartialPdf,
          Sign::same)),
      Bu2Dst0hst_D0gamma_KpiSigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_KpiSigmaBuPartial", uniqueId_, Neutral::gamma,
          1.0, 0.05, Systematic::Bu2Dst0hst_D0gammaBuPartialPdf, Sign::same)),
      // -------------------- Bu2Dst0hst_D0pi0 -------------------- //
      Bu2Dst0hst_D0pi0_meanDelta_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_meanDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0pi0, Systematic::Bu2Dst0hst_D0pi0DeltaPdf,
          Sign::same)),
      Bu2Dst0hst_D0pi0_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_sigmaDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0pi0, Systematic::Bu2Dst0hst_D0pi0DeltaPdf,
          Sign::same)),
      pdfDelta_Bu2Dst0hst_D0pi0_(("pdfDelta_Bu2Dst0hst_D0pi0_" +
                                  ComposeName(uniqueId_, Neutral::gamma))
                                     .c_str(),
                                 "", Configuration::Get().deltaMass(),
                                 *Bu2Dst0hst_D0pi0_meanDelta_,
                                 *Bu2Dst0hst_D0pi0_sigmaDelta_),
      Bu2Dst0hst_D0pi0_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_meanBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0pi0, Systematic::Bu2Dst0hst_D0pi0BuPdf,
          Sign::same)),
      // Bu2Dst0hst_D0pi0_meanBu_(Params::Get().CreateFloating(
      //     "Bu2Dst0hst_D0pi0_meanBu", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0rho_D0pi0, 5135, 5175)),
      Bu2Dst0hst_D0pi0_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_KpiSigmaBu", uniqueId_, Neutral::gamma, 1.0, 0.0,
          Systematic::Bu2Dst0hst_D0pi0BuPdf, Sign::same)),
      Bu2Dst0hst_D0pi0_meanBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_meanBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0pi0, Systematic::Bu2Dst0hst_D0pi0BuPartialPdf,
          Sign::same)),
      Bu2Dst0hst_D0pi0_KpiSigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_KpiSigmaBuPartial", uniqueId_, Neutral::gamma, 1.0,
          0.05, Systematic::Bu2Dst0hst_D0pi0BuPartialPdf, Sign::same)),
      // -------------------- Bu2Dst0hst -------------------- //
      // Bu2Dst0hst_floatingFracD0pi0_(Params::Get().CreateFloating(
      //     "Bu2Dst0hst_floatingFracD0pi0", uniqueId_, Neutral::gamma, 1, 0,
      //     5)),
      Bu2Dst0hst_floatingFracD0pi0_(Params::Get().CreateFixed(
          "Bu2Dst0hst_floatingFracD0pi0", uniqueId_, Neutral::gamma, 1., 0.,
          Systematic::NA, Sign::none)),
      // -------------------- Lb2Omegach_Lcpi0 -------------------- //
      Lb2Omegach_Lcpi0_thresholdDelta_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_thresholdDelta", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0DeltaPdf,
          Sign::same)),
      Lb2Omegach_Lcpi0_aDelta_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_aDelta", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0DeltaPdf,
          Sign::same)),
      Lb2Omegach_Lcpi0_bDelta_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_bDelta", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0DeltaPdf,
          Sign::same)),
      Lb2Omegach_Lcpi0_cDelta_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_cDelta", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0DeltaPdf,
          Sign::same)),
      pdfDelta_Lb2Omegach_Lcpi0_(
          ("pdfDelta_Lb2Omegach_Lcpi0_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Lb2Omegach_Lcpi0_thresholdDelta_, *Lb2Omegach_Lcpi0_cDelta_,
          *Lb2Omegach_Lcpi0_aDelta_, *Lb2Omegach_Lcpi0_bDelta_),
      Lb2Omegach_Lcpi0_meanBu_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_meanBu", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0BuPdf,
          Sign::same)),
      Lb2Omegach_Lcpi0_sigmaBu_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_sigmaBu", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0BuPdf,
          Sign::same)),
      Lb2Omegach_Lcpi0_a1Bu_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_a1Bu", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0BuPdf,
          Sign::same)),
      Lb2Omegach_Lcpi0_n1Bu_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_n1Bu", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0BuPdf,
          Sign::same)),
      pdfBu_Lb2Omegach_Lcpi0_(
          ("pdfBu_Lb2Omegach_Lcpi0_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *Lb2Omegach_Lcpi0_meanBu_,
          *Lb2Omegach_Lcpi0_sigmaBu_, *Lb2Omegach_Lcpi0_a1Bu_,
          *Lb2Omegach_Lcpi0_n1Bu_),
      Lb2Omegach_Lcpi0_meanBuPartial_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_meanBuPartial", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0BuPartialPdf,
          Sign::same)),
      Lb2Omegach_Lcpi0_sigmaBuPartial_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0BuPartialPdf,
          Sign::same)),
      Lb2Omegach_Lcpi0_a1BuPartial_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_a1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0BuPartialPdf,
          Sign::same)),
      Lb2Omegach_Lcpi0_n1BuPartial_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_n1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0BuPartialPdf,
          Sign::same)),
      pdfBuPartial_Lb2Omegach_Lcpi0_(
          ("pdfBuPartial_Lb2Omegach_Lcpi0_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *Lb2Omegach_Lcpi0_meanBuPartial_, *Lb2Omegach_Lcpi0_sigmaBuPartial_,
          *Lb2Omegach_Lcpi0_a1BuPartial_, *Lb2Omegach_Lcpi0_n1BuPartial_),
      orEffLb2Omegach_Lcpi0_(Params::Get().CreateFixed(
          "orEffLb2Omegach_Lcpi0_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffLb2Omegach_Lcpi0_(Params::Get().CreateFixed(
          "deltaEffLb2Omegach_Lcpi0_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      buEffLb2Omegach_Lcpi0_(Params::Get().CreateFixed(
          "buEffLb2Omegach_Lcpi0_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      buPartialEffLb2Omegach_Lcpi0_(Params::Get().CreateFixed(
          "buPartialEffLb2Omegach_Lcpi0_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::same)),
      // -------------------- Bs2D0Kpi -------------------- //
      Bs2D0Kpi_thresholdDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_thresholdDelta", uniqueId_, Neutral::gamma, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiDeltaPdf, Sign::same)),
      Bs2D0Kpi_aDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_aDelta", uniqueId_, Neutral::gamma, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiDeltaPdf, Sign::same)),
      Bs2D0Kpi_bDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_bDelta", uniqueId_, Neutral::gamma, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiDeltaPdf, Sign::same)),
      Bs2D0Kpi_cDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_cDelta", uniqueId_, Neutral::gamma, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiDeltaPdf, Sign::same)),
      pdfDelta_Bs2D0Kpi_(
          ("pdfDelta_Bs2D0Kpi_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2D0Kpi_thresholdDelta_,
          *Bs2D0Kpi_cDelta_, *Bs2D0Kpi_aDelta_, *Bs2D0Kpi_bDelta_),
      Bs2D0Kpi_meanBu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_meanBu", uniqueId_, Neutral::gamma, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiBuPdf, Sign::same)),
      Bs2D0Kpi_sigmaBu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_sigmaBu", uniqueId_, Neutral::gamma, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiBuPdf, Sign::same)),
      Bs2D0Kpi_a1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_a1Bu", uniqueId_, Neutral::gamma, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiBuPdf, Sign::same)),
      Bs2D0Kpi_n1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_n1Bu", uniqueId_, Neutral::gamma, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiBuPdf, Sign::same)),
      pdfBu_Bs2D0Kpi_(
          ("pdfBu_Bs2D0Kpi_" + ComposeName(uniqueId_, Neutral::gamma)).c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2D0Kpi_meanBu_,
          *Bs2D0Kpi_sigmaBu_, *Bs2D0Kpi_a1Bu_, *Bs2D0Kpi_n1Bu_),
      Bs2D0Kpi_meanBuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kpi_meanBuPartial", uniqueId_, Neutral::gamma, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiBuPartialPdf, Sign::same)),
      Bs2D0Kpi_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kpi_sigmaBuPartial", uniqueId_, Neutral::gamma, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiBuPartialPdf, Sign::same)),
      Bs2D0Kpi_a1BuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kpi_a1BuPartial", uniqueId_, Neutral::gamma, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiBuPartialPdf, Sign::same)),
      Bs2D0Kpi_n1BuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kpi_n1BuPartial", uniqueId_, Neutral::gamma, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiBuPartialPdf, Sign::same)),
      pdfBuPartial_Bs2D0Kpi_(
          ("pdfBuPartial_Bs2D0Kpi_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2D0Kpi_meanBuPartial_,
          *Bs2D0Kpi_sigmaBuPartial_, *Bs2D0Kpi_a1BuPartial_,
          *Bs2D0Kpi_n1BuPartial_),
      orEffBs2D0Kpi_(Params::Get().CreateFixed(
          "orEffBs2D0Kpi_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, Efficiency::orEffErr,
                        false),
          Systematic::NA, Sign::same)),
      deltaEffBs2D0Kpi_(Params::Get().CreateFixed(
          "deltaEffBs2D0Kpi_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, Efficiency::deltaEff,
                        false),
          ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, Efficiency::deltaEffErr,
                        false),
          Systematic::NA, Sign::same)),
      buEffBs2D0Kpi_(Params::Get().CreateFixed(
          "buEffBs2D0Kpi_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, Efficiency::buEffErr,
                        false),
          Systematic::NA, Sign::same)),
      buPartialEffBs2D0Kpi_(Params::Get().CreateFixed(
          "buPartialEffBs2D0Kpi_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, Efficiency::buPartialEff,
                        false),
          ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::same)),
      // -------------------- Bs2Dst0Kpi -------------------- //
      Bs2Dst0Kpi_thresholdDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_thresholdDelta", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kpi, Systematic::Bs2Dst0KpiDeltaPdf, Sign::same)),
      Bs2Dst0Kpi_aDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_aDelta", uniqueId_, Neutral::gamma, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiDeltaPdf, Sign::same)),
      Bs2Dst0Kpi_bDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_bDelta", uniqueId_, Neutral::gamma, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiDeltaPdf, Sign::same)),
      Bs2Dst0Kpi_cDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_cDelta", uniqueId_, Neutral::gamma, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiDeltaPdf, Sign::same)),
      pdfFlatDelta_Bs2Dst0Kpi_(
          ("pdfFlatDelta_Bs2Dst0Kpi_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2Dst0Kpi_thresholdDelta_,
          *Bs2Dst0Kpi_cDelta_, *Bs2Dst0Kpi_aDelta_, *Bs2Dst0Kpi_bDelta_),
      Bs2Dst0Kpi_fracPdfGammaPeakDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_fracPdfGammaPeakDelta", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kpi, Systematic::Bs2Dst0KpiDeltaPdf, Sign::same)),
      Bs2Dst0Kpi_fracPdfPi0PeakDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_fracPdfPi0PeakDelta", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kpi, Systematic::Bs2Dst0KpiDeltaPdf, Sign::same)),
      Bs2Dst0Kpi_mean1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_mean1Bu", uniqueId_, Neutral::gamma, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_meanOffset21Bu", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kpi, Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_mean2Bu_(
          ("Bs2Dst0Kpi_mean2Bu_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0+@1",
          RooArgList(*Bs2Dst0Kpi_mean1Bu_, *Bs2Dst0Kpi_meanOffset21Bu_)),
      Bs2Dst0Kpi_sigma1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigma1Bu", uniqueId_, Neutral::gamma, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_sigmaRatio21Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigmaRatio21Bu", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kpi, Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_sigma2Bu_(
          ("Bs2Dst0Kpi_sigma2Bu_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0*@1",
          RooArgList(*Bs2Dst0Kpi_sigma1Bu_, *Bs2Dst0Kpi_sigmaRatio21Bu_)),
      Bs2Dst0Kpi_a1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_a1Bu", uniqueId_, Neutral::gamma, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_a2Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_a2Bu", uniqueId_, Neutral::gamma, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_n1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_n1Bu", uniqueId_, Neutral::gamma, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_n2Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_n2Bu", uniqueId_, Neutral::gamma, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_fracPdf1Bu", uniqueId_, Neutral::gamma, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      pdf1Bu_Bs2Dst0Kpi_(
          ("pdf1Bu_Bs2Dst0Kpi_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2Dst0Kpi_mean1Bu_,
          *Bs2Dst0Kpi_sigma1Bu_, *Bs2Dst0Kpi_a1Bu_, *Bs2Dst0Kpi_n1Bu_),
      pdf2Bu_Bs2Dst0Kpi_(
          ("pdf2Bu_Bs2Dst0Kpi_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), Bs2Dst0Kpi_mean2Bu_,
          Bs2Dst0Kpi_sigma2Bu_, *Bs2Dst0Kpi_a2Bu_, *Bs2Dst0Kpi_n2Bu_),
      pdfBu_Bs2Dst0Kpi_(
          ("pdfBu_Bs2Dst0Kpi_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", RooArgList(pdf1Bu_Bs2Dst0Kpi_, pdf2Bu_Bs2Dst0Kpi_),
          *Bs2Dst0Kpi_fracPdf1Bu_),
      Bs2Dst0Kpi_meanBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_meanBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kpi, Systematic::Bs2Dst0KpiBuPartialPdf, Sign::same)),
      Bs2Dst0Kpi_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kpi, Systematic::Bs2Dst0KpiBuPartialPdf, Sign::same)),
      Bs2Dst0Kpi_a1BuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_a1BuPartial", uniqueId_, Neutral::gamma, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiBuPartialPdf, Sign::same)),
      Bs2Dst0Kpi_n1BuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_n1BuPartial", uniqueId_, Neutral::gamma, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiBuPartialPdf, Sign::same)),
      pdfBuPartial_Bs2Dst0Kpi_(
          ("pdfBuPartial_Bs2Dst0Kpi_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2Dst0Kpi_meanBuPartial_,
          *Bs2Dst0Kpi_sigmaBuPartial_, *Bs2Dst0Kpi_a1BuPartial_,
          *Bs2Dst0Kpi_n1BuPartial_),
      orEffBs2Dst0Kpi_(Params::Get().CreateFixed(
          "orEffBs2Dst0Kpi_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k, Efficiency::orEff,
                        false),
          ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k, Efficiency::orEffErr,
                        false),
          Systematic::NA, Sign::same)),
      deltaEffBs2Dst0Kpi_(Params::Get().CreateFixed(
          "deltaEffBs2Dst0Kpi_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k, Efficiency::deltaEff,
                        false),
          ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k, Efficiency::deltaEffErr,
                        false),
          Systematic::NA, Sign::same)),
      buEffBs2Dst0Kpi_(Params::Get().CreateFixed(
          "buEffBs2Dst0Kpi_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k, Efficiency::buEffErr,
                        false),
          Systematic::NA, Sign::same)),
      buPartialEffBs2Dst0Kpi_(Params::Get().CreateFixed(
          "buPartialEffBs2Dst0Kpi_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k, Efficiency::buPartialEff,
                        false),
          ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::same)),
      // -------------------- MIS-REC -------------------- //
      MisRec_thresholdDelta_(Params::Get().CreateFixed(
          "MisRec_thresholdDelta", uniqueId_, Neutral::gamma, 4.9426e+01,
          7.76e-01, Systematic::misRecDeltaPdf, Sign::same)),
      MisRec_aDelta_(Params::Get().CreateFloating(
          "MisRec_aDelta", uniqueId_, Neutral::gamma, 1.1334e+00, 0, 5)),
      MisRec_bDelta_(Params::Get().CreateFixed(
          "MisRec_bDelta", uniqueId_, Neutral::gamma, -1.5029e+00, 2.56e-03,
          Systematic::misRecDeltaPdf, Sign::none)),
      MisRec_cDelta_(Params::Get().CreateFixed(
          "MisRec_cDelta", uniqueId_, Neutral::gamma, 3.4954e+01, 2.08e-01,
          Systematic::misRecDeltaPdf, Sign::same)),
      pdfDelta_MisRec_(
          ("pdfDelta_MisRec_" + ComposeName(uniqueId_, Neutral::gamma)).c_str(),
          "", Configuration::Get().deltaMass(), *MisRec_thresholdDelta_,
          *MisRec_cDelta_, *MisRec_aDelta_, *MisRec_bDelta_),
      pdfDelta_misId_MisRec_(
          ("pdfDelta_misId_MisRec_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *MisRec_thresholdDelta_,
          *MisRec_cDelta_, *MisRec_aDelta_, *MisRec_bDelta_),
      MisRec_meanBu_(Params::Get().CreateFixed(
          "MisRec_meanBu", uniqueId_, Neutral::gamma, 5.3155e+03, 6.48e-01,
          Systematic::misRecBuPdf, Sign::same)),
      MisRec_aLBu_(Params::Get().CreateFixed(
          "MisRec_aLBu", uniqueId_, Neutral::gamma, 1.5419e-02, 1.27e-02,
          Systematic::misRecBuPdf, Sign::same)),
      MisRec_aRBu_(Params::Get().CreateFixed(
          "MisRec_aRBu", uniqueId_, Neutral::gamma, 3.1182e-02, 7.38e-03,
          Systematic::misRecBuPdf, Sign::same)),
      MisRec_meanBuPartial_(Params::Get().CreateFixed(
          "MisRec_meanBuPartial", uniqueId_, Neutral::gamma, 5.3344e+03,
          7.06e-01, Systematic::misRecBuPartialPdf, Sign::same)),
      MisRec_aLBuPartial_(Params::Get().CreateFixed(
          "MisRec_aLBuPartial", uniqueId_, Neutral::gamma, 1.6586e-07, 1.10e-03,
          Systematic::misRecBuPartialPdf, Sign::same)),
      MisRec_aRBuPartial_(Params::Get().CreateFixed(
          "MisRec_aRBuPartial", uniqueId_, Neutral::gamma, 1.1570e-08, 2.81e-03,
          Systematic::misRecBuPartialPdf, Sign::same)),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_thresholdDelta_(
          ("Bu2D0h_thresholdDelta_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", 6.7754e+01),
      Bu2D0h_aDelta_(
          ("Bu2D0h_aDelta_" + ComposeName(uniqueId_, Neutral::gamma)).c_str(),
          "", 5.8996e-01),
      Bu2D0h_bDelta_(
          ("Bu2D0h_bDelta_" + ComposeName(uniqueId_, Neutral::gamma)).c_str(),
          "", -5.6691e-01),
      Bu2D0h_cDelta_(
          ("Bu2D0h_cDelta_" + ComposeName(uniqueId_, Neutral::gamma)).c_str(),
          "", 6.2156e+01),
      pdfDelta_Bu2D0h_(
          ("pdfDelta_Bu2D0h_" + ComposeName(uniqueId_, Neutral::gamma)).c_str(),
          "", Configuration::Get().deltaMass(), Bu2D0h_thresholdDelta_,
          Bu2D0h_cDelta_, Bu2D0h_aDelta_, Bu2D0h_bDelta_),
      pdfDelta_misId_Bu2D0h_(
          ("pdfDelta_misId_Bu2D0h_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), Bu2D0h_thresholdDelta_,
          Bu2D0h_cDelta_, Bu2D0h_aDelta_, Bu2D0h_bDelta_),
      Bu2D0h_meanBu_(
          ("Bu2D0h_meanBu_" + ComposeName(uniqueId_, Neutral::gamma)).c_str(),
          // "", 5.5269e+03, 5450, 5600),
          // Fixed from data
          "", 5.5403e+03),
      Bu2D0h_aLBu_(
          ("Bu2D0h_aLBu_" + ComposeName(uniqueId_, Neutral::gamma)).c_str(), "",
          // 5.4892e-09, 0, 5),
          // Fixed from data
          5.0307e-07),
      Bu2D0h_aRBu_(
          ("Bu2D0h_aRBu_" + ComposeName(uniqueId_, Neutral::gamma)).c_str(), "",
          // 5.3835e-12, 0, 5),
          // Fixed from data
          3.1175e-09),
      Bu2D0h_meanBuPartial_(
          ("Bu2D0h_meanBuPartial_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          // "", 5.5319e+03, 5450, 5580),
          // Fixed from data
          "", 5.5429e+03),
      Bu2D0h_aLBuPartial_(
          ("Bu2D0h_aLBuPartial_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", 1.0264e-01),
      Bu2D0h_aRBuPartial_(
          ("Bu2D0h_aRBuPartial_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", 2.6929e-02),
      // -------------------- PART-REC -------------------- //
      PartRec_thresholdDelta_(Params::Get().CreateFixed(
          "PartRec_thresholdDelta", uniqueId_, Neutral::gamma, 6.5000e+01,
          1.42e+00, Systematic::partRecDeltaPdf, Sign::same)),
      PartRec_aDelta_(Params::Get().CreateFixed(
          "PartRec_aDelta", uniqueId_, Neutral::gamma, 5.7789e-01, 6.95e-03,
          Systematic::partRecDeltaPdf, Sign::none)),
      PartRec_bDelta_(Params::Get().CreateFixed(
          "PartRec_bDelta", uniqueId_, Neutral::gamma, -6.7459e-01, 8.51e-03,
          Systematic::partRecDeltaPdf, Sign::none)),
      PartRec_cDelta_(Params::Get().CreateFixed(
          "PartRec_cDelta", uniqueId_, Neutral::gamma, 9.9939e+01, 5.48e+00,
          Systematic::partRecDeltaPdf, Sign::same)),
      pdfDelta_PartRec_(
          ("pdfDelta_PartRec_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *PartRec_thresholdDelta_,
          *PartRec_cDelta_, *PartRec_aDelta_, *PartRec_bDelta_),
      pdfDelta_misId_PartRec_(
          ("pdfDelta_misId_PartRec_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *PartRec_thresholdDelta_,
          *PartRec_cDelta_, *PartRec_aDelta_, *PartRec_bDelta_),
      PartRec_D0pi0_meanBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_meanBu", uniqueId_, Neutral::gamma, 5.1473e+03,
          3.68e+00, Systematic::partRecBuPdf, Sign::same)),
      PartRec_D0pi0_aLBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_aLBu", uniqueId_, Neutral::gamma, 6.1807e-08, 1.45e-02,
          Systematic::partRecBuPdf, Sign::same)),
      PartRec_D0pi0_aRBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_aRBu", uniqueId_, Neutral::gamma, 4.8226e-07, 8.40e-03,
          Systematic::partRecBuPdf, Sign::same)),
      PartRec_D0gamma_meanBu_(Params::Get().CreateFixed(
          "PartRec_D0gamma_meanBu", uniqueId_, Neutral::gamma, 5.1068e+03,
          4.67e+00, Systematic::partRecBuPdf, Sign::same)),
      PartRec_D0gamma_aLBu_(Params::Get().CreateFixed(
          "PartRec_D0gamma_aLBu", uniqueId_, Neutral::gamma, 8.6670e-02,
          3.96e-02, Systematic::partRecBuPdf, Sign::same)),
      PartRec_D0gamma_aRBu_(Params::Get().CreateFixed(
          "PartRec_D0gamma_aRBu", uniqueId_, Neutral::gamma, 1.9464e-01,
          1.57e-02, Systematic::partRecBuPdf, Sign::same)),
      PartRec_frac_D0pi0_(Params::Get().CreateFixed(
          "PartRec_frac_D0pi0", uniqueId_, Neutral::gamma, 3.8179e-01, 1.34e-02,
          Systematic::partRecBuPdf, Sign::same)),
      PartRec_meanBuPartial_(Params::Get().CreateFixed(
          "PartRec_meanBuPartial", uniqueId_, Neutral::gamma, 5.1640e+03,
          2.20e+00, Systematic::partRecBuPartialPdf, Sign::same)),
      PartRec_aLBuPartial_(Params::Get().CreateFixed(
          "PartRec_aLBuPartial", uniqueId_, Neutral::gamma, 4.6600e-02,
          1.90e-02, Systematic::partRecBuPartialPdf, Sign::same)),
      PartRec_aRBuPartial_(Params::Get().CreateFixed(
          "PartRec_aRBuPartial", uniqueId_, Neutral::gamma, 1.3962e-01,
          6.78e-03, Systematic::partRecBuPartialPdf, Sign::same)),
      // ------------- Expected yields and relative fractions w.r.t. sig
      // -------------//
      fracBu2Dst0h_D0gamma_(),
      initYieldFAVBu2Dst0h_D0gamma_(Configuration::Get().initYieldFAVSignal()),
      fracBu2Dst0h_D0pi0_(0.871),
      initYieldFAVBu2Dst0h_D0pi0_(Configuration::Get().initYieldFAVSignal() *
                                  fracBu2Dst0h_D0pi0_),
      fracMisRec_Bu2Dst0h_D0gamma_(),
      fracMisRec_Bu2Dst0h_D0gamma_WN_(0.628),
      fracMisRec_Bu2Dst0h_D0pi0_WN_(1.137),
      fracMisRec_Bu2D0hst_(1.481),
      fracMisRec_Bd2Dsth_(0.814),
      fracMisRec_(fracMisRec_Bu2Dst0h_D0gamma_WN_ +
                  fracMisRec_Bu2Dst0h_D0pi0_WN_ + fracMisRec_Bu2D0hst_ +
                  fracMisRec_Bd2Dsth_),
      initYieldFAVMisRec_(
          (Configuration::Get().initYieldFAVSignal() * fracMisRec_) / 2),
      fracBu2D0h_(1.936),
      initYieldFAVBu2D0h_(Configuration::Get().initYieldFAVSignal() *
                          fracBu2D0h_),
      fracPartRec_Bu2Dst0hst_D0gamma_(0.141),
      fracPartRec_Bu2Dst0hst_D0pi0_(0.162),
      fracPartRec_(fracPartRec_Bu2Dst0hst_D0gamma_ +
                   fracPartRec_Bu2Dst0hst_D0pi0_),
      initYieldFAVPartRec_(Configuration::Get().initYieldFAVSignal() *
                           fracPartRec_),
      // -------------------- Bkg Fractions -------------------- //
      bkgFracGlobal_WN_(Params::Get().CreateFloating(
          "bkgFracGlobal_WN", uniqueId_, Neutral::gamma, 1, 0, 5)),
      bkgFracFAV_Bd2Dsth_(Params::Get().CreateFloating(
          "bkgFracFAV_Bd2Dsth", uniqueId_, Neutral::gamma,
          (ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff,
                         false) /
           ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                         Efficiency::orEff, false)) *
              (ReturnMCEffs(Mode::Bd2Dstpi, Neutral::gamma, Bachelor::pi,
                            Efficiency::mcEff) /
               ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma, Neutral::gamma,
                            Bachelor::pi, Efficiency::mcEff)) *
              (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
               GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()) /
              (GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal() *
               GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma().getVal()),
          0, 5)),
      // Constrained relative to Bd2Dsth
      // bkgFracFAV_Bu2D0hst_(Params::Get().CreateFloating(
      //     "bkgFracFAV_Bu2D0hst", uniqueId_, Neutral::gamma,
      //     (ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::orEff,
      //                    false) /
      //      ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff,
      //                    false)) *
      //         (ReturnMCEffs(Mode::Bu2D0rho, Neutral::gamma, Bachelor::pi,
      //                       Efficiency::mcEff) /
      //          ReturnMCEffs(Mode::Bd2Dstpi, Neutral::gamma, Bachelor::pi,
      //                       Efficiency::mcEff)) *
      //         GlobalVars::Get(uniqueId_).kBF_Bu2D0rho().getVal() /
      //         (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
      //          GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()),
      //     0, 5)),
      bkgFracFAV_Bu2D0hst_(Params::Get().CreateFixed(
          "bkgFracFAV_Bu2D0hst", uniqueId_, Neutral::gamma,
          (ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::orEff,
                         false) /
           ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff,
                         false)) *
              (ReturnMCEffs(Mode::Bu2D0rho, Neutral::gamma, Bachelor::pi,
                            Efficiency::mcEff) /
               ReturnMCEffs(Mode::Bd2Dstpi, Neutral::gamma, Bachelor::pi,
                            Efficiency::mcEff)) *
              GlobalVars::Get(uniqueId_).kBF_Bu2D0rho().getVal() /
              (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
               GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()),
          0., Systematic::NA, Sign::none)),
      bkgFracFAV_Bu2Dst0hst_D0gamma_(Params::Get().CreateFloating(
          "bkgFracFAV_Bu2Dst0hst_D0gamma", uniqueId_, Neutral::gamma,
          (ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                         Efficiency::orEff, false) /
           ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff,
                         false)) *
              (ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, Neutral::gamma,
                            Bachelor::pi, Efficiency::mcEff) /
               ReturnMCEffs(Mode::Bd2Dstpi, Neutral::gamma, Bachelor::pi,
                            Efficiency::mcEff)) *
              (GlobalVars::Get(uniqueId_).kBF_Bu2Dst0rho().getVal() *
               GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma().getVal()) /
              (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
               GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()),
          0, 5)),
      // Constrained relative to Bu2Dst0hst_D0gamma
      bkgFracFAV_Bu2Dst0hst_D0pi0_(Params::Get().CreateFloating(
          "bkgFracFAV_Bu2Dst0hst_D0pi0", uniqueId_, Neutral::gamma,
          (ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                         Efficiency::orEff, false) /
           ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                         Efficiency::orEff, false)) *
              (ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, Neutral::gamma,
                            Bachelor::pi, Efficiency::mcEff) /
               ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, Neutral::gamma,
                            Bachelor::pi, Efficiency::mcEff)) *
              GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma().getVal(),
          0, 5)),
      // bkgFracFAV_Bu2Dst0hst_(Params::Get().CreateFloating(
      //     "bkgFracFAV_Bu2Dst0hst", uniqueId_, Neutral::gamma,
      //     (ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
      //                    Efficiency::orEff, false) /
      //      ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff,
      //                    false)) *
      //             (ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, Neutral::gamma,
      //                           Bachelor::pi, Efficiency::mcEff) /
      //              ReturnMCEffs(Mode::Bd2Dstpi, Neutral::gamma, Bachelor::pi,
      //                           Efficiency::mcEff)) *
      //             (GlobalVars::Get(uniqueId_).kBF_Bu2Dst0rho().getVal() *
      //              GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0().getVal()) /
      //             (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
      //              GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()) +
      //         (ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
      //                        Efficiency::orEff, false) /
      //          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff,
      //                        false)) *
      //             (ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, Neutral::gamma,
      //                           Bachelor::pi, Efficiency::mcEff) /
      //              ReturnMCEffs(Mode::Bd2Dstpi, Neutral::gamma, Bachelor::pi,
      //                           Efficiency::mcEff)) *
      //             (GlobalVars::Get(uniqueId_).kBF_Bu2Dst0rho().getVal() *
      //              GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma().getVal()) /
      //             (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
      //              GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()),
      //     0, 5)),
      bkgFracFAV_Bu2Dst0hst_(Params::Get().CreateFixed(
          "bkgFracFAV_Bu2Dst0hst", uniqueId_, Neutral::gamma,
          (ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                         Efficiency::orEff, false) /
           ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff,
                         false)) *
                  (ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, Neutral::gamma,
                                Bachelor::pi, Efficiency::mcEff) /
                   ReturnMCEffs(Mode::Bd2Dstpi, Neutral::gamma, Bachelor::pi,
                                Efficiency::mcEff)) *
                  (GlobalVars::Get(uniqueId_).kBF_Bu2Dst0rho().getVal() *
                   GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0().getVal()) /
                  (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
                   GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()) +
              (ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                             Efficiency::orEff, false) /
               ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff,
                             false)) *
                  (ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, Neutral::gamma,
                                Bachelor::pi, Efficiency::mcEff) /
                   ReturnMCEffs(Mode::Bd2Dstpi, Neutral::gamma, Bachelor::pi,
                                Efficiency::mcEff)) *
                  (GlobalVars::Get(uniqueId_).kBF_Bu2Dst0rho().getVal() *
                   GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma().getVal()) /
                  (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
                   GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()),
          0., Systematic::NA, Sign::none)),
      bkgFracKK_Lb2Omegach_Lcpi0_(Params::Get().CreateFloating(
          "bkgFracKK_Lb2Omegach_Lcpi0", uniqueId_, Neutral::gamma, 0.1, 0, 5)),
      bkgFracADS_Bs2D0Kpi_(Params::Get().CreateFloating(
          "bkgFracADS_Bs2D0Kpi", uniqueId_, Neutral::gamma, 4, -2, 10)),
      bkgFracADS_Bs2Dst0Kpi_(Params::Get().CreateFloating(
          "bkgFracADS_Bs2Dst0Kpi", uniqueId_, Neutral::gamma, 4, -2, 10)),
      constraint_bkgFracGlobal_WN_(("constraint_bkgFracGlobal_WN_" +
                                    ComposeName(uniqueId_, Neutral::gamma))
                                       .c_str(),
                                   "", *bkgFracGlobal_WN_, RooFit::RooConst(1),
                                   RooFit::RooConst(0.1)),
      constraint_bkgFracFAV_Bu2D0hst_(
          ("constraint_bkgFracFAV_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", *bkgFracFAV_Bu2D0hst_,
          RooFit::RooConst(ReadBkgFracs<Neutral::gamma>(Mode::Bu2D0rho, "val")),
          RooFit::RooConst(
              ReadBkgFracs<Neutral::gamma>(Mode::Bu2D0rho, "std"))),
      constraint_bkgFracFAV_Bu2Dst0hst_D0gamma_(
          ("constraint_bkgFracFAV_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", *bkgFracFAV_Bu2Dst0hst_D0gamma_,
          RooFit::RooConst(
              ReadBkgFracs<Neutral::gamma>(Mode::Bu2Dst0rho_D0gamma, "val")),
          RooFit::RooConst(
              ReadBkgFracs<Neutral::gamma>(Mode::Bu2Dst0rho_D0gamma, "std"))),
      constraint_bkgFracFAV_Bu2Dst0hst_D0pi0_(
          ("constraint_bkgFracFAV_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", *bkgFracFAV_Bu2Dst0hst_D0pi0_,
          RooFit::RooConst(
              ReadBkgFracs<Neutral::gamma>(Mode::Bu2Dst0rho_D0pi0, "val")),
          RooFit::RooConst(
              ReadBkgFracs<Neutral::gamma>(Mode::Bu2Dst0rho_D0pi0, "std"))),
      constraints_argSet_() {}
      // constraints_argSet_(constraint_bkgFracGlobal_WN_) {}
// constraint_bkgFracFAV_Bu2D0hst_) {}
// constraint_bkgFracFAV_Bu2Dst0hst_D0pi0_,
// constraint_bkgFracFAV_Bu2Dst0hst_D0gamma_) {}
