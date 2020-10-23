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
      // Bu2Dst0h_D0pi0_mean1BuPartial_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_mean1BuPartial", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0pi0, 5280, 5310)),
      Bu2Dst0h_D0pi0_mean1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_mean1BuPartial", uniqueId_, Neutral::gamma,
          5.2983e+03, 2.18e-01, Systematic::NA,
          Sign::same)),
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
      pdfDelta_Bu2D0hst_(new RooDstD0BG(
          ("pdfDelta_Bu2D0hst_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2D0hst_thresholdDelta_,
          *Bu2D0hst_cDelta_, *Bu2D0hst_aDelta_, *Bu2D0hst_bDelta_)),
      Bu2D0hst_mean1Bu_(nullptr),
      Bu2D0hst_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_meanOffset21Bu", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hstBuPdf, Sign::none)),
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
      Bu2Dst0hst_D0gamma_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_meanOffset21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gammaBuPdf,
          Sign::none)),
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
          "Bs2Dst0Kpi_mean1Bu", uniqueId_, Neutral::gamma, 5.1989e+03, 4.93e+00,
          Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      // Bs2Dst0Kpi_mean1Bu_(Params::Get().CreateFloating(
      //     "Bs2Dst0Kpi_mean1Bu", uniqueId_, Neutral::gamma, Mode::Bs2Dst0Kpi,
      //     5180, 5230)),
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
      // -------------------- Bu2Dst0h_D0gamma_D02pik -------------------- //
      Bu2Dst0h_D0gamma_D02pik_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_D02pik_sigmaDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_D02pik, Systematic::NA, Sign::same)),
      pdf1Delta_Bu2Dst0h_D0gamma_D02pik_(
          ("pdf1Delta_Bu2Dst0h_D0gamma_D02pik_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0gamma_meanDelta_,
          *Bu2Dst0h_D0gamma_D02pik_sigmaDelta_, *Bu2Dst0h_D0gamma_a1Delta_,
          *Bu2Dst0h_D0gamma_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0gamma_D02pik_(
          ("pdf2Delta_Bu2Dst0h_D0gamma_D02pik_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0gamma_meanDelta_,
          *Bu2Dst0h_D0gamma_D02pik_sigmaDelta_, *Bu2Dst0h_D0gamma_a2Delta_,
          *Bu2Dst0h_D0gamma_n2Delta_),
      pdfDelta_Bu2Dst0h_D0gamma_D02pik_(
          ("pdfDelta_Bu2Dst0h_D0gamma_D02pik_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0gamma_D02pik_,
                     pdf2Delta_Bu2Dst0h_D0gamma_D02pik_),
          *Bu2Dst0h_D0gamma_fracPdf1Delta_),
      Bu2Dst0h_D0gamma_D02pik_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_D02pik_meanBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_D02pik, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0gamma_D02pik_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_D02pik_sigmaBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_D02pik, Systematic::NA, Sign::same)),
      pdfBu_Bu2Dst0h_D0gamma_D02pik_(("pdfBu_Bu2Dst0h_D0gamma_D02pik_" +
                                      ComposeName(uniqueId_, Neutral::gamma))
                                         .c_str(),
                                     "", Configuration::Get().buDeltaMass(),
                                     *Bu2Dst0h_D0gamma_D02pik_meanBu_,
                                     *Bu2Dst0h_D0gamma_D02pik_sigmaBu_),
      orEffBu2Dst0h_D0gamma_D02pik_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0gamma_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0h_D0gamma_D02pik_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0gamma_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0h_D0gamma_D02pik_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0gamma_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      buPartialEffBu2Dst0h_D0gamma_D02pik_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0gamma_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::same)),
      // -------------------- Bu2Dst0h_D0pi0_D02pik -------------------- //
      Bu2Dst0h_D0pi0_D02pik_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_sigmaDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_D02pik_a2Delta_(nullptr),
      Bu2Dst0h_D0pi0_D02pik_n2Delta_(nullptr),
      Bu2Dst0h_D0pi0_D02pik_fracPdf1Delta_(nullptr),
      pdf1Delta_Bu2Dst0h_D0pi0_D02pik_(
          ("pdf1Delta_Bu2Dst0h_D0pi0_D02pik_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0pi0_meanDelta_,
          *Bu2Dst0h_D0pi0_D02pik_sigmaDelta_, *Bu2Dst0h_D0pi0_a1Delta_,
          *Bu2Dst0h_D0pi0_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0pi0_D02pik_(
          ("pdf2Delta_Bu2Dst0h_D0pi0_D02pik_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0pi0_meanDelta_,
          *Bu2Dst0h_D0pi0_D02pik_sigmaDelta_, *Bu2Dst0h_D0pi0_a2Delta_,
          *Bu2Dst0h_D0pi0_n2Delta_),
      pdfDelta_Bu2Dst0h_D0pi0_D02pik_(
          ("pdfDelta_Bu2Dst0h_D0pi0_D02pik_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_D02pik_,
                     pdf2Delta_Bu2Dst0h_D0pi0_D02pik_),
          *Bu2Dst0h_D0pi0_fracPdf1Delta_),
      Bu2Dst0h_D0pi0_D02pik_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_meanBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_D02pik_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_sigmaBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::NA, Sign::same)),
      pdfBu_Bu2Dst0h_D0pi0_D02pik_(("pdfBu_Bu2Dst0h_D0pi0_D02pik_" +
                                    ComposeName(uniqueId_, Neutral::gamma))
                                       .c_str(),
                                   "", Configuration::Get().buDeltaMass(),
                                   *Bu2Dst0h_D0pi0_D02pik_meanBu_,
                                   *Bu2Dst0h_D0pi0_D02pik_sigmaBu_),
      Bu2Dst0h_D0pi0_D02pik_meanBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_meanBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_D02pik_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_sigmaBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::NA, Sign::same)),
      pdfBuPartial_Bu2Dst0h_D0pi0_D02pik_(
          ("pdfBuPartial_Bu2Dst0h_D0pi0_D02pik_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *Bu2Dst0h_D0pi0_D02pik_meanBuPartial_,
          *Bu2Dst0h_D0pi0_D02pik_sigmaBuPartial_),
      orEffBu2Dst0h_D0pi0_D02pik_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0pi0_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0h_D0pi0_D02pik_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0h_D0pi0_D02pik_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      buPartialEffBu2Dst0h_D0pi0_D02pik_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0pi0_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::same)),
      // -------------------- Bu2Dst0h_D0gamma_WN_D02pik -------------------- //
      Bu2Dst0h_D0gamma_WN_D02pik_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_D02pik_sigmaDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Systematic::NA, Sign::same)),
      pdf1Delta_Bu2Dst0h_D0gamma_WN_D02pik_(
          ("pdf1Delta_Bu2Dst0h_D0gamma_WN_D02pik_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0gamma_meanDelta_,
          *Bu2Dst0h_D0gamma_WN_D02pik_sigmaDelta_, *Bu2Dst0h_D0gamma_a1Delta_,
          *Bu2Dst0h_D0gamma_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0gamma_WN_D02pik_(
          ("pdf2Delta_Bu2Dst0h_D0gamma_WN_D02pik_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0gamma_meanDelta_,
          *Bu2Dst0h_D0gamma_WN_D02pik_sigmaDelta_, *Bu2Dst0h_D0gamma_a2Delta_,
          *Bu2Dst0h_D0gamma_n2Delta_),
      pdfDelta_Bu2Dst0h_D0gamma_WN_D02pik_(
          ("pdfDelta_Bu2Dst0h_D0gamma_WN_D02pik_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0gamma_WN_D02pik_,
                     pdf2Delta_Bu2Dst0h_D0gamma_WN_D02pik_),
          *Bu2Dst0h_D0gamma_fracPdf1Delta_),
      Bu2Dst0h_D0gamma_WN_D02pik_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_D02pik_meanBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0gamma_WN_D02pik_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_D02pik_sigmaBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Systematic::NA, Sign::same)),
      pdfBu_Bu2Dst0h_D0gamma_WN_D02pik_(("pdfBu_Bu2Dst0h_D0gamma_WN_D02pik_" +
                                         ComposeName(uniqueId_, Neutral::gamma))
                                            .c_str(),
                                        "", Configuration::Get().buDeltaMass(),
                                        *Bu2Dst0h_D0gamma_WN_D02pik_meanBu_,
                                        *Bu2Dst0h_D0gamma_WN_D02pik_sigmaBu_),
      orEffBu2Dst0h_D0gamma_WN_D02pik_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0gamma_WN_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0h_D0gamma_WN_D02pik_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0gamma_WN_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0h_D0gamma_WN_D02pik_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0gamma_WN_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      buPartialEffBu2Dst0h_D0gamma_WN_D02pik_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0gamma_WN_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::same)),
      // -------------------- Bu2Dst0h_D0pi0_WN_D02pik -------------------- //
      Bu2Dst0h_D0pi0_WN_D02pik_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_sigmaDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_WN_D02pik_a2Delta_(nullptr),
      Bu2Dst0h_D0pi0_WN_D02pik_n2Delta_(nullptr),
      Bu2Dst0h_D0pi0_WN_D02pik_fracPdf1Delta_(nullptr),
      pdf1Delta_Bu2Dst0h_D0pi0_WN_D02pik_(
          ("pdf1Delta_Bu2Dst0h_D0pi0_WN_D02pik_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0pi0_meanDelta_,
          *Bu2Dst0h_D0pi0_WN_D02pik_sigmaDelta_, *Bu2Dst0h_D0pi0_a1Delta_,
          *Bu2Dst0h_D0pi0_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0pi0_WN_D02pik_(
          ("pdf2Delta_Bu2Dst0h_D0pi0_WN_D02pik_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0pi0_meanDelta_,
          *Bu2Dst0h_D0pi0_WN_D02pik_sigmaDelta_, *Bu2Dst0h_D0pi0_a2Delta_,
          *Bu2Dst0h_D0pi0_n2Delta_),
      pdfDelta_Bu2Dst0h_D0pi0_WN_D02pik_(
          ("pdfDelta_Bu2Dst0h_D0pi0_WN_D02pik_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_WN_D02pik_,
                     pdf2Delta_Bu2Dst0h_D0pi0_WN_D02pik_),
          *Bu2Dst0h_D0pi0_fracPdf1Delta_),
      Bu2Dst0h_D0pi0_WN_D02pik_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_meanBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_WN_D02pik_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_sigmaBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::NA, Sign::same)),
      pdfBu_Bu2Dst0h_D0pi0_WN_D02pik_(("pdfBu_Bu2Dst0h_D0pi0_WN_D02pik_" +
                                       ComposeName(uniqueId_, Neutral::gamma))
                                          .c_str(),
                                      "", Configuration::Get().buDeltaMass(),
                                      *Bu2Dst0h_D0pi0_WN_D02pik_meanBu_,
                                      *Bu2Dst0h_D0pi0_WN_D02pik_sigmaBu_),
      Bu2Dst0h_D0pi0_WN_D02pik_meanBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_meanBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_WN_D02pik_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_sigmaBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::NA, Sign::same)),
      pdfBuPartial_Bu2Dst0h_D0pi0_WN_D02pik_(
          ("pdfBuPartial_Bu2Dst0h_D0pi0_WN_D02pik_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *Bu2Dst0h_D0pi0_WN_D02pik_meanBuPartial_,
          *Bu2Dst0h_D0pi0_WN_D02pik_sigmaBuPartial_),
      orEffBu2Dst0h_D0pi0_WN_D02pik_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0pi0_WN_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0h_D0pi0_WN_D02pik_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_WN_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0h_D0pi0_WN_D02pik_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_WN_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      buPartialEffBu2Dst0h_D0pi0_WN_D02pik_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0pi0_WN_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::same)),
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
      bkgFracADS_Bs2Dst0Kpi_(Params::Get().CreateFloating(
          "bkgFracADS_Bs2Dst0Kpi", uniqueId_, Neutral::gamma, 4, -2, 10)),
      // bkgFracADS_Bs2D0Kpi_(Params::Get().CreateFloating(
      //     "bkgFracADS_Bs2D0Kpi", uniqueId_, Neutral::gamma, 4, -2, 10)),
      bkgFracADS_Bs2D0Kpi_(Params::Get().CreateFixed(
          "bkgFracADS_Bs2D0Kpi", uniqueId_, Neutral::gamma,
          (ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, Efficiency::orEff,
                         false) /
           ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k, Efficiency::orEff,
                         false)) *
              (ReturnMCEffs(Mode::Bs2D0Kpi, Neutral::gamma, Bachelor::k,
                            Efficiency::mcEff) /
               ReturnMCEffs(Mode::Bs2Dst0Kpi, Neutral::gamma, Bachelor::k,
                            Efficiency::mcEff)),
          0., Systematic::NA, Sign::same)),
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
      constraints_argSet_() {}
// constraints_argSet_(constraint_bkgFracGlobal_WN_) {}
// constraint_bkgFracFAV_Bu2D0hst_) {}
