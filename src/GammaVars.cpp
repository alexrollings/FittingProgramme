#include "GlobalVars.h"
#include "NeutralVars.h"
#include "Params.h"

// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::gamma>::NeutralVars(int uniqueId)
    : uniqueId_(uniqueId),
      A_Kpi_(Params::Get().CreateFixed("A_Kpi", uniqueId_, Neutral::gamma,
                                       -1.15e-02, 1.6e-03, Systematic::A_Kpi,
                                       Sign::none)),
      a_Kpi_(MakeLittleAsym(
          ("a_Kpi_" + ComposeName(uniqueId_, Neutral::gamma)).c_str(),
          *A_Kpi_)),
      // -------------------- PDF SHAPES -------------------- //
      // -------------------- Bu2Dst0h_D0gamma -------------------- //
      Bu2Dst0h_D0gamma_meanDelta_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0gamma_meanDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, 135, 150)),
      Bu2Dst0h_D0gamma_KpiSigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_KpiSigmaDelta", uniqueId_, Neutral::gamma,
          1.0402e+00, 2.46e-02,
          Systematic::Bu2Dst0h_D0gamma_PdfDelta_SigmaRatioKpi, Sign::same)),
      // Bu2Dst0h_D0gamma_KpiSigmaDelta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0gamma_KpiSigmaDelta", uniqueId_, Neutral::gamma,
      //     0.99278, 0.9, 1.1)),
      Bu2Dst0h_D0gamma_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::Bu2Dst0h_D0gamma_PdfDelta_Tails,
          Sign::same)),
      Bu2Dst0h_D0gamma_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::Bu2Dst0h_D0gamma_PdfDelta_Tails,
          Sign::same)),
      Bu2Dst0h_D0gamma_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a2Delta", uniqueId_, Neutral::gamma, -6.0668e-01,
          8.97e-03, Systematic::Bu2Dst0h_D0gamma_PdfDelta_Tails, Sign::same)),
      // Bu2Dst0h_D0gamma_a2Delta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0gamma_a2Delta", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0gamma, -5, -0.000001)),
      Bu2Dst0h_D0gamma_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n2Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::Bu2Dst0h_D0gamma_PdfDelta_Tails,
          Sign::same)),
      Bu2Dst0h_D0gamma_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_fracPdf1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::Bu2Dst0h_D0gamma_PdfDelta_Frac,
          Sign::same)),
      Bu2Dst0h_D0gamma_meanBu_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0gamma_meanBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, 5275, 5285)),
      Bu2Dst0h_D0gamma_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_KpiSigmaBu", uniqueId_, Neutral::gamma, 9.8368e-01,
          2.06e-02,
          // Neutral::gamma, 1.0061e+00, 2.14e-02,
          Systematic::Bu2Dst0h_D0gamma_PdfBu_SigmaRatioKpi, Sign::same)),
      // Bu2Dst0h_D0gamma_KpiSigmaBu_(
      //     Params::Get().CreateFloating("Bu2Dst0h_D0gamma_KpiSigmaBu",
      //     uniqueId_,
      //                                  Neutral::gamma, 0.957103, 0.9, 1.1)),
      Bu2Dst0h_D0gamma_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::Bu2Dst0h_D0gamma_PdfBu_Tails,
          Sign::same)),
      Bu2Dst0h_D0gamma_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::Bu2Dst0h_D0gamma_PdfBu_Tails,
          Sign::same)),
      Bu2Dst0h_D0gamma_a2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a2Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::Bu2Dst0h_D0gamma_PdfBu_Tails,
          Sign::same)),
      Bu2Dst0h_D0gamma_n2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n2Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::Bu2Dst0h_D0gamma_PdfBu_Tails,
          Sign::same)),
      Bu2Dst0h_D0gamma_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_fracPdf1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::Bu2Dst0h_D0gamma_PdfBu_Frac,
          Sign::same)),
      Bu2Dst0h_D0gamma_meanBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_meanBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::Bu2Dst0h_D0gamma_PdfBuPartial,
          Sign::same)),
      Bu2Dst0h_D0gamma_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::Bu2Dst0h_D0gamma_PdfBuPartial,
          Sign::same)),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      BR_pi02gamma_eff_(Params::Get().CreateFloating(
          "BR_pi02gamma_eff", uniqueId_, Neutral::gamma,
          GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma().getVal(),
          0, 5)),
      Bu2Dst0h_D0pi0_meanDelta_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_meanDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, 75, 95)),
      Bu2Dst0h_D0pi0_KpiSigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_KpiSigmaDelta", uniqueId_, Neutral::gamma, 1.0341e+00,
          3.92e-02, Systematic::Bu2Dst0h_D0pi0_PdfDelta_SigmaRatioKpi,
          Sign::same)),
      // Bu2Dst0h_D0pi0_KpiSigmaDelta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_KpiSigmaDelta", uniqueId_, Neutral::gamma,
      //     0.979346, 0.9, 1.1)),
      Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::gamma, 3.2160e-01,
          3.47e-02, Systematic::Bu2Dst0h_D0pi0_PdfDelta_Tails, Sign::same)),
      // Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0pi0, 0, 5)),
      Bu2Dst0h_D0pi0_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfDelta_Tails,
          Sign::same)),
      Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfDelta_Tails,
          Sign::same)),
      Bu2Dst0h_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfDelta_Tails,
          Sign::same)),
      Bu2Dst0h_D0pi0_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfDelta_Frac,
          Sign::same)),
      Bu2Dst0h_D0pi0_mean1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_mean1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfBu, Sign::same)),
      Bu2Dst0h_D0pi0_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_meanOffset21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfBu, Sign::none)),
      Bu2Dst0h_D0pi0_mean2Bu_(
          ("Bu2Dst0h_D0pi0_mean2Bu" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0+@1",
          RooArgList(*Bu2Dst0h_D0pi0_mean1Bu_,
                     *Bu2Dst0h_D0pi0_meanOffset21Bu_)),
      Bu2Dst0h_D0pi0_sigmaRatio21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_sigmaRatio21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfBu, Sign::same)),
      Bu2Dst0h_D0pi0_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_KpiSigmaBu", uniqueId_, Neutral::gamma, 1.0, 0.0,
          Systematic::Bu2Dst0h_D0pi0_PdfBu, Sign::same)),
      Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfBu, Sign::same)),
      Bu2Dst0h_D0pi0_a2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfBu, Sign::same)),
      Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfBu, Sign::same)),
      Bu2Dst0h_D0pi0_n2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfBu, Sign::same)),
      Bu2Dst0h_D0pi0_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfBu, Sign::same)),
      Bu2Dst0h_D0pi0_mean1BuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_mean1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, 5280, 5310)),
      // Bu2Dst0h_D0pi0_mean1BuPartial_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_mean1BuPartial", uniqueId_, Neutral::gamma,
      //     5.2983e+03, 2.18e-01, Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_Mean,
      //     Sign::same)),
      Bu2Dst0h_D0pi0_meanOffset31BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_meanOffset31BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0,
          Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_MeanOffset, Sign::none)),
      Bu2Dst0h_D0pi0_mean3BuPartial_(
          ("Bu2Dst0h_D0pi0_mean3BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0+@1",
          RooArgSet(*Bu2Dst0h_D0pi0_mean1BuPartial_,
                    *Bu2Dst0h_D0pi0_meanOffset31BuPartial_)),
      Bu2Dst0h_D0pi0_KpiSigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_KpiSigmaBuPartial", uniqueId_, Neutral::gamma,
          9.4705e-01, 2.53e-02,
          Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatioKpi, Sign::same)),
      // Bu2Dst0h_D0pi0_KpiSigmaBuPartial_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_KpiSigmaBuPartial", uniqueId_, Neutral::gamma,
      //     0.959297, 0.9, 1.1)),
      Bu2Dst0h_D0pi0_sigmaRatio21BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_sigmaRatio21BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0,
          Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatio, Sign::same)),
      Bu2Dst0h_D0pi0_sigmaRatio31BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_sigmaRatio31BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0,
          Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatio, Sign::same)),
      Bu2Dst0h_D0pi0_a1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1BuPartial", uniqueId_, Neutral::gamma, 2.5872e+00,
          1.15e-01, Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_Tails, Sign::same)),
      // Bu2Dst0h_D0pi0_a1BuPartial_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_a1BuPartial", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0pi0, 0, 5)),
      Bu2Dst0h_D0pi0_n1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_Tails,
          Sign::same)),
      Bu2Dst0h_D0pi0_a2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2BuPartial", uniqueId_, Neutral::gamma, -3.0105e+00,
          5.45e-01, Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_Tails, Sign::same)),
      // Bu2Dst0h_D0pi0_a2BuPartial_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_a2BuPartial", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0pi0, -5, -0.00001)),
      Bu2Dst0h_D0pi0_n2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_Tails,
          Sign::same)),
      Bu2Dst0h_D0pi0_fracPdf1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_Frac,
          Sign::same)),
      Bu2Dst0h_D0pi0_fracPdf2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf2BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_Frac,
          Sign::same)),
      // -------------------- Bu2Dst0h_D0gamma_WN -------------------- //
      Bu2Dst0h_D0gamma_WN_thresholdDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_thresholdDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfDelta,
          Sign::same)),
      Bu2Dst0h_D0gamma_WN_aDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_aDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfDelta,
          Sign::none)),
      // Bu2Dst0h_D0gamma_WN_aDelta_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0gamma_WN_aDelta", uniqueId_, Neutral::gamma,
      //     5.4321e-01, 7.48e-03, Systematic::Bu2Dst0h_D0gamma_WN_PdfDelta,
      //     Sign::none)),
      // Bu2Dst0h_D0gamma_WN_aDelta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0gamma_WN_aDelta", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0gamma_WN, 0, 1)),
      Bu2Dst0h_D0gamma_WN_bDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_bDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfDelta,
          Sign::none)),
      Bu2Dst0h_D0gamma_WN_cDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_cDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfDelta,
          Sign::same)),
      pdfDelta_Bu2Dst0h_D0gamma_WN_(new RooDstD0BG(
          ("pdfDelta_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0gamma_WN_thresholdDelta_, *Bu2Dst0h_D0gamma_WN_cDelta_,
          *Bu2Dst0h_D0gamma_WN_aDelta_, *Bu2Dst0h_D0gamma_WN_bDelta_)),
      Bu2Dst0h_D0gamma_WN_mean1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_mean1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfBu,
          Sign::same)),
      Bu2Dst0h_D0gamma_WN_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_meanOffset21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfBu,
          Sign::none)),
      Bu2Dst0h_D0gamma_WN_mean2Bu_(
          ("Bu2Dst0h_D0gamma_WN_mean2Bu_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0+@1",
          RooArgSet(*Bu2Dst0h_D0gamma_WN_mean1Bu_,
                    *Bu2Dst0h_D0gamma_WN_meanOffset21Bu_)),
      Bu2Dst0h_D0gamma_WN_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_KpiSigmaBu", uniqueId_, Neutral::gamma, 1.0,
          0.05, Systematic::Bu2Dst0h_D0gamma_WN_PdfBu, Sign::same)),
      Bu2Dst0h_D0gamma_WN_sigmaRatio21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_sigmaRatio21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfBu,
          Sign::same)),
      Bu2Dst0h_D0gamma_WN_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_a1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfBu,
          Sign::none)),
      Bu2Dst0h_D0gamma_WN_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_n1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfBu,
          Sign::same)),
      Bu2Dst0h_D0gamma_WN_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_fracPdf1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfBu,
          Sign::same)),
      Bu2Dst0h_D0gamma_WN_mean1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_mean1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::Bu2Dst0h_D0gamma_WN_PdfBuPartial, Sign::same)),
      Bu2Dst0h_D0gamma_WN_meanOffset21BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_meanOffset21BuPartial", uniqueId_,
          Neutral::gamma, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::Bu2Dst0h_D0gamma_WN_PdfBuPartial, Sign::none)),
      Bu2Dst0h_D0gamma_WN_mean2BuPartial_(
          ("Bu2Dst0h_D0gamma_WN_mean2BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0+@1",
          RooArgSet(*Bu2Dst0h_D0gamma_WN_mean1BuPartial_,
                    *Bu2Dst0h_D0gamma_WN_meanOffset21BuPartial_)),
      Bu2Dst0h_D0gamma_WN_KpiSigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_KpiSigmaBuPartial", uniqueId_, Neutral::gamma,
          1.0, 0.05, Systematic::Bu2Dst0h_D0gamma_WN_PdfBuPartial, Sign::same)),
      Bu2Dst0h_D0gamma_WN_sigmaRatio21BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_sigmaRatio21BuPartial", uniqueId_,
          Neutral::gamma, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::Bu2Dst0h_D0gamma_WN_PdfBuPartial, Sign::same)),
      Bu2Dst0h_D0gamma_WN_a1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_a1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::Bu2Dst0h_D0gamma_WN_PdfBuPartial, Sign::none)),
      Bu2Dst0h_D0gamma_WN_n1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_n1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::Bu2Dst0h_D0gamma_WN_PdfBuPartial, Sign::same)),
      Bu2Dst0h_D0gamma_WN_fracPdf1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_fracPdf1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::Bu2Dst0h_D0gamma_WN_PdfBuPartial, Sign::same)),
      // -------------------- Bu2Dst0h_D0pi0_WN -------------------- //
      Bu2Dst0h_D0pi0_WN_thresholdDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_thresholdDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfDelta,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_cDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_cDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfDelta,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_mean1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_mean1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBu,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_meanOffset21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBu,
          Sign::none)),
      Bu2Dst0h_D0pi0_WN_mean2Bu_(("Bu2Dst0h_D0pi0_WN_mean2Bu_" +
                                  ComposeName(uniqueId_, Neutral::gamma))
                                     .c_str(),
                                 "@0+@1",
                                 RooArgSet(*Bu2Dst0h_D0pi0_WN_mean1Bu_,
                                           *Bu2Dst0h_D0pi0_WN_meanOffset21Bu_)),
      Bu2Dst0h_D0pi0_WN_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_KpiSigmaBu", uniqueId_, Neutral::gamma, 1.0, 0.05,
          Systematic::Bu2Dst0h_D0pi0_WN_PdfBu, Sign::same)),
      Bu2Dst0h_D0pi0_WN_sigmaRatio21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_sigmaRatio21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBu,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_a1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBu,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_n1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBu,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_a2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_a2Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBu,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_n2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_n2Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBu,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_fracPdf1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBu,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_mean1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_mean1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_meanOffset31BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_meanOffset31BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial,
          Sign::none)),
      Bu2Dst0h_D0pi0_WN_mean3BuPartial_(
          ("Bu2Dst0h_D0pi0_WN_mean3BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0+@1",
          RooArgSet(*Bu2Dst0h_D0pi0_WN_mean1BuPartial_,
                    *Bu2Dst0h_D0pi0_WN_meanOffset31BuPartial_)),
      Bu2Dst0h_D0pi0_WN_KpiSigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_KpiSigmaBuPartial", uniqueId_, Neutral::gamma, 1.0,
          0.05, Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial, Sign::same)),
      Bu2Dst0h_D0pi0_WN_sigmaRatio21BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_sigmaRatio21BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_sigmaRatio31BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_sigmaRatio31BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_a1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_a1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_n1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_n1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_a2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_a2BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial,
          Sign::same)),
      // Bu2Dst0h_D0pi0_WN_a2BuPartial_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_WN_a2BuPartial", uniqueId_, Neutral::gamma,
      //     -3.8030e+00, 8.04e-01, Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial,
      //     Sign::same)),
      // Bu2Dst0h_D0pi0_WN_a2BuPartial_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_a2BuPartial", uniqueId_, Neutral::gamma,
      //     Mode::Bu2Dst0pi_D0pi0_WN, -5, -0.000001)),
      Bu2Dst0h_D0pi0_WN_n2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_n2BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_fracPdf1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_fracPdf1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_fracPdf2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_fracPdf2BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial,
          Sign::same)),
      // -------------------- Bu2Dst0h_WN -------------------- //
      Bu2Dst0h_WN_floatingFracD0pi0_(nullptr),
      // -------------------- Bd2Dsth -------------------- //
      Bd2Dsth_thresholdDelta_(Params::Get().CreateFixed(
          "Bd2Dsth_thresholdDelta", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfDelta, Sign::same)),
      Bd2Dsth_aDelta_(Params::Get().CreateFixed(
          "Bd2Dsth_aDelta", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfDelta, Sign::none)),
      Bd2Dsth_bDelta_(Params::Get().CreateFixed(
          "Bd2Dsth_bDelta", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfDelta, Sign::none)),
      Bd2Dsth_cDelta_(Params::Get().CreateFixed(
          "Bd2Dsth_cDelta", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfDelta, Sign::same)),
      pdfDelta_Bd2Dsth_(
          ("pdfDelta_Bd2Dsth_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bd2Dsth_thresholdDelta_,
          *Bd2Dsth_cDelta_, *Bd2Dsth_aDelta_, *Bd2Dsth_bDelta_),
      Bd2Dsth_mean1Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_mean1Bu", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfBu, Sign::same)),
      Bd2Dsth_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_meanOffset21Bu", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfBu, Sign::none)),
      Bd2Dsth_mean2Bu_(
          ("Bd2Dsth_mean2Bu_" + ComposeName(uniqueId_, Neutral::gamma)).c_str(),
          "", "@0+@1", RooArgSet(*Bd2Dsth_mean1Bu_, *Bd2Dsth_meanOffset21Bu_)),
      Bd2Dsth_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bd2Dsth_KpiSigmaBu", uniqueId_, Neutral::gamma, 1.0, 0.05,
          Systematic::Bd2Dsth_PdfBu, Sign::same)),
      Bd2Dsth_sigmaRatio21Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_sigmaRatio21Bu", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfBu, Sign::same)),
      Bd2Dsth_a1Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_a1Bu", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfBu, Sign::same)),
      Bd2Dsth_n1Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_n1Bu", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfBu, Sign::same)),
      Bd2Dsth_a2Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_a2Bu", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfBu, Sign::same)),
      Bd2Dsth_n2Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_n2Bu", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfBu, Sign::same)),
      Bd2Dsth_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_fracPdf1Bu", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfBu, Sign::same)),
      Bd2Dsth_mean1BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_mean1BuPartial", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfBuPartial, Sign::same)),
      // Bd2Dsth_mean1BuPartial_(Params::Get().CreateFloating(
      //     "Bd2Dsth_mean1BuPartial", uniqueId_, Neutral::gamma,
      //     Mode::Bd2Dstpi, 5340, 5360)),
      Bd2Dsth_meanOffset21BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_meanOffset21BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bd2Dstpi, Systematic::Bd2Dsth_PdfBuPartial, Sign::none)),
      Bd2Dsth_mean2BuPartial_(
          ("Bd2Dsth_mean2BuPartial_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", "@0+@1",
          RooArgSet(*Bd2Dsth_mean1BuPartial_, *Bd2Dsth_meanOffset21BuPartial_)),
      Bd2Dsth_KpiSigmaBuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_KpiSigmaBuPartial", uniqueId_, Neutral::gamma, 1.0, 0.05,
          Systematic::Bd2Dsth_PdfBuPartial, Sign::same)),
      Bd2Dsth_sigmaRatio21BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_sigmaRatio21BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bd2Dstpi, Systematic::Bd2Dsth_PdfBuPartial, Sign::same)),
      Bd2Dsth_a1BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_a1BuPartial", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfBuPartial, Sign::same)),
      Bd2Dsth_n1BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_n1BuPartial", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfBuPartial, Sign::same)),
      Bd2Dsth_a2BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_a2BuPartial", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfBuPartial, Sign::same)),
      Bd2Dsth_n2BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_n2BuPartial", uniqueId_, Neutral::gamma, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfBuPartial, Sign::same)),
      Bd2Dsth_fracPdf1BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_fracPdf1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bd2Dstpi, Systematic::Bd2Dsth_PdfBuPartial, Sign::same)),
      // -------------------- Bu2D0hst -------------------- //
      Bu2D0hst_thresholdDelta_(Params::Get().CreateFixed(
          "Bu2D0hst_thresholdDelta", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfDelta, Sign::same)),
      Bu2D0hst_aDelta_(Params::Get().CreateFixed(
          "Bu2D0hst_aDelta", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfDelta, Sign::none)),
      Bu2D0hst_bDelta_(Params::Get().CreateFixed(
          "Bu2D0hst_bDelta", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfDelta, Sign::none)),
      Bu2D0hst_cDelta_(Params::Get().CreateFixed(
          "Bu2D0hst_cDelta", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfDelta, Sign::same)),
      pdfDelta_Bu2D0hst_(new RooDstD0BG(
          ("pdfDelta_Bu2D0hst_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2D0hst_thresholdDelta_,
          *Bu2D0hst_cDelta_, *Bu2D0hst_aDelta_, *Bu2D0hst_bDelta_)),
      Bu2D0hst_mean1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_mean1Bu", uniqueId, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfBu, Sign::same)),
      Bu2D0hst_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_meanOffset21Bu", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfBu, Sign::none)),
      Bu2D0hst_mean2Bu_(
          ("Bu2D0hst_mean2Bu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "@0+@1", RooArgSet(*Bu2D0hst_mean1Bu_, *Bu2D0hst_meanOffset21Bu_)),
      Bu2D0hst_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2D0hst_KpiSigmaBu", uniqueId_, Neutral::gamma, 1.0, 0.05,
          Systematic::Bu2D0hst_PdfBu, Sign::same)),
      Bu2D0hst_sigmaRatio21Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_sigmaRatio21Bu", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfBu, Sign::same)),
      Bu2D0hst_a1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_a1Bu", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfBu, Sign::none)),
      // Bu2D0hst_a1Bu_(Params::Get().CreateFloating(
      //     "Bu2D0hst_a1Bu", uniqueId_, Neutral::gamma, Mode::Bu2D0rho, 0, 5)),
      Bu2D0hst_n1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_n1Bu", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfBu, Sign::same)),
      Bu2D0hst_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_fracPdf1Bu", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfBu, Sign::same)),
      Bu2D0hst_meanBuPartial_(Params::Get().CreateFixed(
          "Bu2D0hst_meanBuPartial", uniqueId_, Neutral::gamma, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfBuPartial, Sign::same)),
      // Bu2D0hst_meanBuPartial_(Params::Get().CreateFloating(
      //     "Bu2D0hst_meanBuPartial", uniqueId_, Neutral::gamma,
      //     Mode::Bu2D0rho, 5250, 5270)),
      Bu2D0hst_KpiSigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2D0hst_KpiSigmaBuPartial", uniqueId_, Neutral::gamma, 1.0, 0.05,
          Systematic::Bu2D0hst_PdfBuPartial, Sign::same)),
      // -------------------- Bu2Dst0hst_D0gamma -------------------- //
      Bu2Dst0hst_D0gamma_meanDelta_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_meanDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gamma_PdfDelta,
          Sign::same)),
      Bu2Dst0hst_D0gamma_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_sigmaDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gamma_PdfDelta,
          Sign::same)),
      pdfDelta_Bu2Dst0hst_D0gamma_(("pdfDelta_Bu2Dst0hst_D0gamma_" +
                                    ComposeName(uniqueId_, Neutral::gamma))
                                       .c_str(),
                                   "", Configuration::Get().deltaMass(),
                                   *Bu2Dst0hst_D0gamma_meanDelta_,
                                   *Bu2Dst0hst_D0gamma_sigmaDelta_),
      Bu2Dst0hst_D0gamma_mean1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_mean1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gamma_PdfBu,
          Sign::same)),
      Bu2Dst0hst_D0gamma_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_meanOffset21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gamma_PdfBu,
          Sign::none)),
      Bu2Dst0hst_D0gamma_mean2Bu_(
          ("Bu2Dst0hst_D0gamma_mean2Bu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", "@0+@1",
          RooArgSet(*Bu2Dst0hst_D0gamma_mean1Bu_,
                    *Bu2Dst0hst_D0gamma_meanOffset21Bu_)),
      Bu2Dst0hst_D0gamma_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_KpiSigmaBu", uniqueId_, Neutral::gamma, 1.0, 0.05,
          Systematic::Bu2Dst0hst_D0gamma_PdfBu, Sign::same)),
      Bu2Dst0hst_D0gamma_sigmaRatio21Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_sigmaRatio21Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gamma_PdfBu,
          Sign::same)),
      Bu2Dst0hst_D0gamma_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_a1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gamma_PdfBu,
          Sign::same)),
      Bu2Dst0hst_D0gamma_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_n1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gamma_PdfBu,
          Sign::same)),
      Bu2Dst0hst_D0gamma_a2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_a2Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gamma_PdfBu,
          Sign::same)),
      Bu2Dst0hst_D0gamma_n2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_n2Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gamma_PdfBu,
          Sign::same)),
      Bu2Dst0hst_D0gamma_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_fracPdf1Bu", uniqueId, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gamma_PdfBu,
          Sign::same)),
      Bu2Dst0hst_D0gamma_meanBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_meanBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gamma_PdfBuPartial,
          Sign::same)),
      Bu2Dst0hst_D0gamma_KpiSigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_KpiSigmaBuPartial", uniqueId_, Neutral::gamma,
          1.0, 0.05, Systematic::Bu2Dst0hst_D0gamma_PdfBuPartial, Sign::same)),
      // -------------------- Bu2Dst0hst_D0pi0 -------------------- //
      Bu2Dst0hst_D0pi0_meanDelta_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_meanDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0pi0, Systematic::Bu2Dst0hst_D0pi0_PdfDelta,
          Sign::same)),
      Bu2Dst0hst_D0pi0_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_sigmaDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0pi0, Systematic::Bu2Dst0hst_D0pi0_PdfDelta,
          Sign::same)),
      pdfDelta_Bu2Dst0hst_D0pi0_(("pdfDelta_Bu2Dst0hst_D0pi0_" +
                                  ComposeName(uniqueId_, Neutral::gamma))
                                     .c_str(),
                                 "", Configuration::Get().deltaMass(),
                                 *Bu2Dst0hst_D0pi0_meanDelta_,
                                 *Bu2Dst0hst_D0pi0_sigmaDelta_),
      Bu2Dst0hst_D0pi0_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_meanBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0pi0, Systematic::Bu2Dst0hst_D0pi0_PdfBu,
          Sign::same)),
      Bu2Dst0hst_D0pi0_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_KpiSigmaBu", uniqueId_, Neutral::gamma, 1.0, 0.0,
          Systematic::Bu2Dst0hst_D0pi0_PdfBu, Sign::same)),
      Bu2Dst0hst_D0pi0_meanBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_meanBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0rho_D0pi0, Systematic::Bu2Dst0hst_D0pi0_PdfBuPartial,
          Sign::same)),
      Bu2Dst0hst_D0pi0_KpiSigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_KpiSigmaBuPartial", uniqueId_, Neutral::gamma, 1.0,
          0.05, Systematic::Bu2Dst0hst_D0pi0_PdfBuPartial, Sign::same)),
      // -------------------- Bu2Dst0hst -------------------- //
      // Bu2Dst0hst_floatingFracD0pi0_(Params::Get().CreateFloating(
      //     "Bu2Dst0hst_floatingFracD0pi0", uniqueId_, Neutral::gamma, 1, 0,
      //     5)),
      // Bu2Dst0hst_floatingFracD0pi0_(Params::Get().CreateFixed(
      //     "Bu2Dst0hst_floatingFracD0pi0", uniqueId_, Neutral::gamma, 1., 0.3,
      //     Systematic::Bu2Dst0hst_Frac, Sign::same)),
      // -------------------- Lb2Omegach_Lcpi0 -------------------- //
      Lb2Omegach_Lcpi0_thresholdDelta_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_thresholdDelta", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfDelta,
          Sign::same)),
      Lb2Omegach_Lcpi0_aDelta_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_aDelta", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfDelta,
          Sign::none)),
      Lb2Omegach_Lcpi0_bDelta_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_bDelta", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfDelta,
          Sign::none)),
      Lb2Omegach_Lcpi0_cDelta_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_cDelta", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfDelta,
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
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfBu,
          Sign::same)),
      Lb2Omegach_Lcpi0_sigmaBu_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_sigmaBu", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfBu,
          Sign::same)),
      Lb2Omegach_Lcpi0_a1Bu_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_a1Bu", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfBu,
          Sign::none)),
      Lb2Omegach_Lcpi0_n1Bu_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_n1Bu", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfBu,
          Sign::same)),
      pdfBu_Lb2Omegach_Lcpi0_(
          ("pdfBu_Lb2Omegach_Lcpi0_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *Lb2Omegach_Lcpi0_meanBu_,
          *Lb2Omegach_Lcpi0_sigmaBu_, *Lb2Omegach_Lcpi0_a1Bu_,
          *Lb2Omegach_Lcpi0_n1Bu_),
      Lb2Omegach_Lcpi0_meanBuPartial_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_meanBuPartial", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfBuPartial,
          Sign::same)),
      Lb2Omegach_Lcpi0_sigmaBuPartial_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfBuPartial,
          Sign::same)),
      Lb2Omegach_Lcpi0_a1BuPartial_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_a1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfBuPartial,
          Sign::none)),
      Lb2Omegach_Lcpi0_n1BuPartial_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_n1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfBuPartial,
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
          Systematic::boxEffs_Bkg, Sign::same)),
      deltaEffLb2Omegach_Lcpi0_(Params::Get().CreateFixed(
          "deltaEffLb2Omegach_Lcpi0_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      buEffLb2Omegach_Lcpi0_(Params::Get().CreateFixed(
          "buEffLb2Omegach_Lcpi0_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      buPartialEffLb2Omegach_Lcpi0_(Params::Get().CreateFixed(
          "buPartialEffLb2Omegach_Lcpi0_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      // -------------------- Bs2D0Kst0 -------------------- //
      Bs2D0Kst0_thresholdDelta_(Params::Get().CreateFixed(
          "Bs2D0Kst0_thresholdDelta", uniqueId_, Neutral::gamma,
          Mode::Bs2D0Kst0, Systematic::Bs2D0Kst0_PdfDelta, Sign::same)),
      Bs2D0Kst0_aDelta_(Params::Get().CreateFixed(
          "Bs2D0Kst0_aDelta", uniqueId_, Neutral::gamma, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfDelta, Sign::none)),
      Bs2D0Kst0_bDelta_(Params::Get().CreateFixed(
          "Bs2D0Kst0_bDelta", uniqueId_, Neutral::gamma, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfDelta, Sign::none)),
      Bs2D0Kst0_cDelta_(Params::Get().CreateFixed(
          "Bs2D0Kst0_cDelta", uniqueId_, Neutral::gamma, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfDelta, Sign::same)),
      pdfDelta_Bs2D0Kst0_(
          ("pdfDelta_Bs2D0Kst0_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2D0Kst0_thresholdDelta_,
          *Bs2D0Kst0_cDelta_, *Bs2D0Kst0_aDelta_, *Bs2D0Kst0_bDelta_),
      Bs2D0Kst0_meanBu_(Params::Get().CreateFixed(
          "Bs2D0Kst0_meanBu", uniqueId_, Neutral::gamma, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfBu, Sign::same)),
      Bs2D0Kst0_sigmaBu_(Params::Get().CreateFixed(
          "Bs2D0Kst0_sigmaBu", uniqueId_, Neutral::gamma, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfBu, Sign::same)),
      Bs2D0Kst0_a1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kst0_a1Bu", uniqueId_, Neutral::gamma, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfBu, Sign::none)),
      Bs2D0Kst0_n1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kst0_n1Bu", uniqueId_, Neutral::gamma, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfBu, Sign::same)),
      pdfBu_Bs2D0Kst0_(
          ("pdfBu_Bs2D0Kst0_" + ComposeName(uniqueId_, Neutral::gamma)).c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2D0Kst0_meanBu_,
          *Bs2D0Kst0_sigmaBu_, *Bs2D0Kst0_a1Bu_, *Bs2D0Kst0_n1Bu_),
      Bs2D0Kst0_mean1BuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kst0_mean1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bs2D0Kst0, Systematic::Bs2D0Kst0_PdfBuPartial, Sign::same)),
      Bs2D0Kst0_meanOffset21BuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kst0_meanOffset21BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bs2D0Kst0, Systematic::Bs2D0Kst0_PdfBuPartial, Sign::same)),
      Bs2D0Kst0_mean2BuPartial_(
          ("Bs2D0Kst0_mean2BuPartial" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0+@1",
          RooArgList(*Bs2D0Kst0_mean1BuPartial_,
                     *Bs2D0Kst0_meanOffset21BuPartial_)),
      Bs2D0Kst0_sigma1BuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kst0_sigma1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bs2D0Kst0, Systematic::Bs2D0Kst0_PdfBuPartial, Sign::same)),
      Bs2D0Kst0_sigmaRatio21BuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kst0_sigmaRatio21BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bs2D0Kst0, Systematic::Bs2D0Kst0_PdfBuPartial, Sign::same)),
      Bs2D0Kst0_sigma2BuPartial_(
          ("Bs2D0Kst0_sigma2BuPartial" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0*@1",
          RooArgList(*Bs2D0Kst0_sigma1BuPartial_,
                     *Bs2D0Kst0_sigmaRatio21BuPartial_)),
      Bs2D0Kst0_a1BuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kst0_a1BuPartial", uniqueId_, Neutral::gamma, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfBuPartial, Sign::none)),
      Bs2D0Kst0_n1BuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kst0_n1BuPartial", uniqueId_, Neutral::gamma, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfBuPartial, Sign::same)),
      Bs2D0Kst0_fracPdf1BuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kst0_fracPdf1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bs2D0Kst0, Systematic::Bs2D0Kst0_PdfBuPartial, Sign::same)),
      pdf1BuPartial_Bs2D0Kst0_(
          ("pdf1BuPartial_Bs2D0Kst0_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2D0Kst0_mean1BuPartial_,
          *Bs2D0Kst0_sigma1BuPartial_, *Bs2D0Kst0_a1BuPartial_,
          *Bs2D0Kst0_n1BuPartial_),
      pdf2BuPartial_Bs2D0Kst0_(
          ("pdf2BuPartial_Bs2D0Kst0_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), Bs2D0Kst0_mean2BuPartial_,
          Bs2D0Kst0_sigma2BuPartial_),
      pdfBuPartial_Bs2D0Kst0_(
          ("pdfBuPartial_Bs2D0Kst0_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", RooArgList(pdf1BuPartial_Bs2D0Kst0_, pdf2BuPartial_Bs2D0Kst0_),
          *Bs2D0Kst0_fracPdf1BuPartial_),
      mcEff_Bs2D0Kst0_(Params::Get().CreateFixed(
          "mcEff_Bs2D0Kst0", uniqueId_, Neutral::gamma,
          ReturnMCEffs(Mode::Bs2D0Kst0, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bs2D0Kst0, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg, Sign::same)),
      orEffBs2D0Kst0_(Params::Get().CreateFixed(
          "orEffBs2D0Kst0_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2D0Kst0, Bachelor::k, Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bs2D0Kst0, Bachelor::k, Efficiency::orEffErr,
                        false),
          Systematic::boxEffs_Bkg, Sign::same)),
      deltaEffBs2D0Kst0_(Params::Get().CreateFixed(
          "deltaEffBs2D0Kst0_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2D0Kst0, Bachelor::k, Efficiency::deltaEff,
                        false),
          ReturnBoxEffs(Mode::Bs2D0Kst0, Bachelor::k, Efficiency::deltaEffErr,
                        false),
          Systematic::boxEffs_Bkg, Sign::same)),
      buEffBs2D0Kst0_(Params::Get().CreateFixed(
          "buEffBs2D0Kst0_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2D0Kst0, Bachelor::k, Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bs2D0Kst0, Bachelor::k, Efficiency::buEffErr,
                        false),
          Systematic::boxEffs_Bkg, Sign::same)),
      buPartialEffBs2D0Kst0_(Params::Get().CreateFixed(
          "buPartialEffBs2D0Kst0_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2D0Kst0, Bachelor::k, Efficiency::buPartialEff,
                        false),
          ReturnBoxEffs(Mode::Bs2D0Kst0, Bachelor::k,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      // -------------------- Bs2Dst0Kst0_D0pi0 -------------------- //
      Bs2Dst0Kst0_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_a1Delta", uniqueId_, Neutral::gamma, 3.4363e-01,
          3.87e-02, Systematic::Bs2Dst0Kst0_PdfDelta, Sign::same)),
      Bs2Dst0Kst0_D0pi0_n1Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_n1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bs2Dst0Kst0_PdfDelta, Sign::same)),
      Bs2Dst0Kst0_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_a2Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bs2Dst0Kst0_PdfDelta, Sign::same)),
      Bs2Dst0Kst0_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_n2Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bs2Dst0Kst0_PdfDelta, Sign::same)),
      Bs2Dst0Kst0_D0pi0_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_fracPdf1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bs2Dst0Kst0_PdfDelta, Sign::same)),
      Bs2Dst0Kst0_D0pi0_mean1Bu_(nullptr),
      Bs2Dst0Kst0_D0pi0_meanOffset21Bu_(nullptr),
      Bs2Dst0Kst0_D0pi0_mean2Bu_(),
      Bs2Dst0Kst0_D0pi0_sigma1Bu_(nullptr),
      Bs2Dst0Kst0_D0pi0_sigmaRatio21Bu_(nullptr),
      Bs2Dst0Kst0_D0pi0_sigma2Bu_(),
      Bs2Dst0Kst0_D0pi0_a1Bu_(nullptr),
      Bs2Dst0Kst0_D0pi0_n1Bu_(nullptr),
      pdf1Bu_Bs2Dst0Kst0_D0pi0_(),
      pdf2Bu_Bs2Dst0Kst0_D0pi0_(),
      Bs2Dst0Kst0_D0pi0_fracPdf1Bu_(nullptr),
      pdfBu_Bs2Dst0Kst0_D0pi0_(),
      Bs2Dst0Kst0_D0pi0_meanBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_meanBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kst0_D0pi0, Systematic::Bs2Dst0Kst0_PdfBuPartial,
          Sign::same)),
      Bs2Dst0Kst0_D0pi0_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kst0_D0pi0, Systematic::Bs2Dst0Kst0_PdfBuPartial,
          Sign::same)),
      Bs2Dst0Kst0_D0pi0_a1BuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_a1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kst0_D0pi0, Systematic::Bs2Dst0Kst0_PdfBuPartial,
          Sign::none)),
      Bs2Dst0Kst0_D0pi0_n1BuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_n1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kst0_D0pi0, Systematic::Bs2Dst0Kst0_PdfBuPartial,
          Sign::none)),
      pdfBuPartial_Bs2Dst0Kst0_D0pi0_(
          ("pdfBuPartial_Bs2Dst0Kst0_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *Bs2Dst0Kst0_D0pi0_meanBuPartial_, *Bs2Dst0Kst0_D0pi0_sigmaBuPartial_,
          *Bs2Dst0Kst0_D0pi0_a1BuPartial_, *Bs2Dst0Kst0_D0pi0_n1BuPartial_),
      mcEff_Bs2Dst0Kst0_D0pi0_(Params::Get().CreateFixed(
          "mcEff_Bs2Dst0Kst0_D0pi0", uniqueId_, Neutral::gamma,
          ReturnMCEffs(Mode::Bs2Dst0Kst0_D0pi0, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bs2Dst0Kst0_D0pi0, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg, Sign::same)),
      orEffBs2Dst0Kst0_D0pi0_(Params::Get().CreateFixed(
          "orEffBs2Dst0Kst0_D0pi0_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0, Bachelor::k, Efficiency::orEff,
                        false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0, Bachelor::k,
                        Efficiency::orEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      deltaEffBs2Dst0Kst0_D0pi0_(Params::Get().CreateFixed(
          "deltaEffBs2Dst0Kst0_D0pi0_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0, Bachelor::k,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0, Bachelor::k,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      buEffBs2Dst0Kst0_D0pi0_(Params::Get().CreateFixed(
          "buEffBs2Dst0Kst0_D0pi0_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0, Bachelor::k, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0, Bachelor::k,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      buPartialEffBs2Dst0Kst0_D0pi0_(Params::Get().CreateFixed(
          "buPartialEffBs2Dst0Kst0_D0pi0_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0, Bachelor::k,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0, Bachelor::k,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      // -------------------- Bs2Dst0Kst0_D0gamma -------------------- //
      Bs2Dst0Kst0_D0gamma_a1Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_a1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::Bs2Dst0Kst0_PdfDelta,
          Sign::same)),
      Bs2Dst0Kst0_D0gamma_n1Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_n1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::Bs2Dst0Kst0_PdfDelta,
          Sign::same)),
      Bs2Dst0Kst0_D0gamma_a2Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_a2Delta", uniqueId_, Neutral::gamma, -6.7782e-01,
          1.28e-02, Systematic::Bs2Dst0Kst0_PdfDelta, Sign::same)),
      Bs2Dst0Kst0_D0gamma_n2Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_n2Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::Bs2Dst0Kst0_PdfDelta,
          Sign::same)),
      Bs2Dst0Kst0_D0gamma_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_fracPdf1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::Bs2Dst0Kst0_PdfDelta,
          Sign::same)),
      Bs2Dst0Kst0_D0gamma_meanBu_(
          Params::Get().CreateFixed("Bs2Dst0Kst0_D0gamma_meanBu", uniqueId_,
                                    Neutral::gamma, Mode::Bs2Dst0Kst0_D0gamma,
                                    Systematic::Bs2Dst0Kst0_PdfBu, Sign::same)),
      Bs2Dst0Kst0_D0gamma_sigmaBu_(
          Params::Get().CreateFixed("Bs2Dst0Kst0_D0gamma_sigmaBu", uniqueId_,
                                    Neutral::gamma, Mode::Bs2Dst0Kst0_D0gamma,
                                    Systematic::Bs2Dst0Kst0_PdfBu, Sign::same)),
      Bs2Dst0Kst0_D0gamma_a1Bu_(
          Params::Get().CreateFixed("Bs2Dst0Kst0_D0gamma_a1Bu", uniqueId_,
                                    Neutral::gamma, Mode::Bs2Dst0Kst0_D0gamma,
                                    Systematic::Bs2Dst0Kst0_PdfBu, Sign::none)),
      Bs2Dst0Kst0_D0gamma_n1Bu_(
          Params::Get().CreateFixed("Bs2Dst0Kst0_D0gamma_n1Bu", uniqueId_,
                                    Neutral::gamma, Mode::Bs2Dst0Kst0_D0gamma,
                                    Systematic::Bs2Dst0Kst0_PdfBu, Sign::none)),
      Bs2Dst0Kst0_D0gamma_a2Bu_(
          Params::Get().CreateFixed("Bs2Dst0Kst0_D0gamma_a2Bu", uniqueId_,
                                    Neutral::gamma, Mode::Bs2Dst0Kst0_D0gamma,
                                    Systematic::Bs2Dst0Kst0_PdfBu, Sign::none)),
      Bs2Dst0Kst0_D0gamma_n2Bu_(
          Params::Get().CreateFixed("Bs2Dst0Kst0_D0gamma_n2Bu", uniqueId_,
                                    Neutral::gamma, Mode::Bs2Dst0Kst0_D0gamma,
                                    Systematic::Bs2Dst0Kst0_PdfBu, Sign::none)),
      Bs2Dst0Kst0_D0gamma_fracPdf1Bu_(
          Params::Get().CreateFixed("Bs2Dst0Kst0_D0gamma_fracPdf1Bu", uniqueId_,
                                    Neutral::gamma, Mode::Bs2Dst0Kst0_D0gamma,
                                    Systematic::Bs2Dst0Kst0_PdfBu, Sign::none)),
      pdf1Bu_Bs2Dst0Kst0_D0gamma_(
          ("pdf1Bu_Bs2Dst0Kst0_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2Dst0Kst0_D0gamma_meanBu_,
          *Bs2Dst0Kst0_D0gamma_sigmaBu_, *Bs2Dst0Kst0_D0gamma_a1Bu_,
          *Bs2Dst0Kst0_D0gamma_n1Bu_),
      pdf2Bu_Bs2Dst0Kst0_D0gamma_(
          ("pdf2Bu_Bs2Dst0Kst0_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2Dst0Kst0_D0gamma_meanBu_,
          *Bs2Dst0Kst0_D0gamma_sigmaBu_, *Bs2Dst0Kst0_D0gamma_a2Bu_,
          *Bs2Dst0Kst0_D0gamma_n2Bu_),
      pdfBu_Bs2Dst0Kst0_D0gamma_(
          ("pdfBu_Bs2Dst0Kst0_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdf1Bu_Bs2Dst0Kst0_D0gamma_, pdf2Bu_Bs2Dst0Kst0_D0gamma_),
          *Bs2Dst0Kst0_D0gamma_fracPdf1Bu_),
      mcEff_Bs2Dst0Kst0_D0gamma_(Params::Get().CreateFixed(
          "mcEff_Bs2Dst0Kst0_D0gamma", uniqueId_, Neutral::gamma,
          ReturnMCEffs(Mode::Bs2Dst0Kst0_D0gamma, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bs2Dst0Kst0_D0gamma, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg, Sign::same)),
      orEffBs2Dst0Kst0_D0gamma_(Params::Get().CreateFixed(
          "orEffBs2Dst0Kst0_D0gamma_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma, Bachelor::k,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma, Bachelor::k,
                        Efficiency::orEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      deltaEffBs2Dst0Kst0_D0gamma_(Params::Get().CreateFixed(
          "deltaEffBs2Dst0Kst0_D0gamma_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma, Bachelor::k,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma, Bachelor::k,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      buEffBs2Dst0Kst0_D0gamma_(Params::Get().CreateFixed(
          "buEffBs2Dst0Kst0_D0gamma_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma, Bachelor::k,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma, Bachelor::k,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      buPartialEffBs2Dst0Kst0_D0gamma_(Params::Get().CreateFixed(
          "buPartialEffBs2Dst0Kst0_D0gamma_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma, Bachelor::k,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma, Bachelor::k,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      // -------------------- Bs2Dst0Kst0_comb -------------------- //
      // Bu peak PDF only made of true gamma: BuPartial peak PDF only made of
      // true π0
      // eff π0 BF = eff BR x gamma BF
      Bs2Dst0Kst0_fracD0pi0_(
          ("Bs2Dst0Kst0_fracD0pi0_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "(@0*@1*@2*@3)/(@0*@1*@2*@3+@1*@4*@5)",
          RooArgList(*BR_pi02gamma_eff_,
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma(),
                     *mcEff_Bs2Dst0Kst0_D0pi0_, *orEffBs2Dst0Kst0_D0pi0_,
                     *mcEff_Bs2Dst0Kst0_D0gamma_, *orEffBs2Dst0Kst0_D0gamma_)),
      Bs2Dst0Kst0_fracD0pi0_Delta_(
          ("Bs2Dst0Kst0_fracD0pi0_Delta_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "(@0*@1*@2*@3*@4)/(@0*@1*@2*@3*@4+@1*@5*@6*@7)",
          RooArgList(
              *BR_pi02gamma_eff_, GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma(),
              *mcEff_Bs2Dst0Kst0_D0pi0_, *orEffBs2Dst0Kst0_D0pi0_,
              *deltaEffBs2Dst0Kst0_D0pi0_, *mcEff_Bs2Dst0Kst0_D0gamma_,
              *orEffBs2Dst0Kst0_D0gamma_, *deltaEffBs2Dst0Kst0_D0gamma_)),
      // Bs2Dst0Kst0_fracD0pi0_(Params::Get().CreateFixed(
      //     "Bs2Dst0Kst0_fracD0pi0", uniqueId_, Neutral::gamma,
      //     ReadPdfFracs<Neutral::gamma, Bachelor::k>("Bs2Dst0Kst0_fracD0pi0",
      //                                               ReturnType::val),
      //     // 0.3,
      //     ReadPdfFracs<Neutral::gamma, Bachelor::k>("Bs2Dst0Kst0_fracD0pi0",
      //                                               ReturnType::std),
      //     Systematic::Bs2Dst0Kst0_Frac, Sign::same)),
      // Bs2Dst0Kst0_fracD0pi0_Delta_(Params::Get().CreateFixed(
      //     "Bs2Dst0Kst0_fracD0pi0_Delta", uniqueId_, Neutral::gamma,
      //     ReadPdfFracs<Neutral::gamma, Bachelor::k>(
      //         "Bs2Dst0Kst0_fracD0pi0_Delta", ReturnType::val),
      //     // 0.3,
      //     ReadPdfFracs<Neutral::gamma, Bachelor::k>(
      //         "Bs2Dst0Kst0_fracD0pi0_Delta", ReturnType::std),
      //     Systematic::Bs2Dst0Kst0_Frac, Sign::same)),
      mcEff_Bs2Dst0Kst0_comb_(
          ("mcEff_Bs2Dst0Kst0_comb_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bs2Dst0Kst0_fracD0pi0_, *mcEff_Bs2Dst0Kst0_D0pi0_,
                     *mcEff_Bs2Dst0Kst0_D0gamma_)),
      orEffBs2Dst0Kst0_comb_(
          ("orEffBs2Dst0Kst0_comb_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bs2Dst0Kst0_fracD0pi0_, *orEffBs2Dst0Kst0_D0pi0_,
                     *orEffBs2Dst0Kst0_D0gamma_)),
      deltaEffBs2Dst0Kst0_comb_(
          ("deltaEffBs2Dst0Kst0_comb_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bs2Dst0Kst0_fracD0pi0_, *deltaEffBs2Dst0Kst0_D0pi0_,
                     *deltaEffBs2Dst0Kst0_D0gamma_)),
      // -------------------- Bs2Dst0Kst0_D0pi0_WN -------------------- //
      Bs2Dst0Kst0_D0pi0_WN_thresholdDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_WN_thresholdDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bs2Dst0Kst0_PdfDelta,
          Sign::same)),
      Bs2Dst0Kst0_D0pi0_WN_cDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_WN_cDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bs2Dst0Kst0_PdfDelta,
          Sign::same)),
      Bs2Dst0Kst0_D0pi0_WN_meanBu_(
          Params::Get().CreateFixed("Bs2Dst0Kst0_D0pi0_WN_meanBu", uniqueId_,
                                    Neutral::gamma, Mode::Bs2Dst0Kst0_D0pi0_WN,
                                    Systematic::Bs2Dst0Kst0_PdfBu, Sign::same)),
      Bs2Dst0Kst0_D0pi0_WN_sigmaBu_(
          Params::Get().CreateFixed("Bs2Dst0Kst0_D0pi0_WN_sigmaBu", uniqueId_,
                                    Neutral::gamma, Mode::Bs2Dst0Kst0_D0pi0_WN,
                                    Systematic::Bs2Dst0Kst0_PdfBu, Sign::same)),
      pdfBu_Bs2Dst0Kst0_D0pi0_WN_(("pdfBu_Bs2Dst0Kst0_D0pi0_WN_" +
                                   ComposeName(uniqueId_, Neutral::gamma))
                                      .c_str(),
                                  "", Configuration::Get().buDeltaMass(),
                                  *Bs2Dst0Kst0_D0pi0_WN_meanBu_,
                                  *Bs2Dst0Kst0_D0pi0_WN_sigmaBu_),
      Bs2Dst0Kst0_D0pi0_WN_meanBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_WN_meanBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kst0_D0pi0_WN, Systematic::Bs2Dst0Kst0_PdfBuPartial,
          Sign::same)),
      Bs2Dst0Kst0_D0pi0_WN_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_WN_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kst0_D0pi0_WN, Systematic::Bs2Dst0Kst0_PdfBuPartial,
          Sign::same)),
      pdfBuPartial_Bs2Dst0Kst0_D0pi0_WN_(
          ("pdfBuPartial_Bs2Dst0Kst0_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *Bs2Dst0Kst0_D0pi0_WN_meanBuPartial_,
          *Bs2Dst0Kst0_D0pi0_WN_sigmaBuPartial_),
      mcEff_Bs2Dst0Kst0_D0pi0_WN_(Params::Get().CreateFixed(
          "mcEff_Bs2Dst0Kst0_D0pi0_WN", uniqueId_, Neutral::gamma,
          ReturnMCEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg, Sign::same)),
      orEffBs2Dst0Kst0_D0pi0_WN_(Params::Get().CreateFixed(
          "orEffBs2Dst0Kst0_D0pi0_WN_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Bachelor::k,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Bachelor::k,
                        Efficiency::orEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      deltaEffBs2Dst0Kst0_D0pi0_WN_(Params::Get().CreateFixed(
          "deltaEffBs2Dst0Kst0_D0pi0_WN_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Bachelor::k,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Bachelor::k,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      buEffBs2Dst0Kst0_D0pi0_WN_(Params::Get().CreateFixed(
          "buEffBs2Dst0Kst0_D0pi0_WN_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Bachelor::k,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Bachelor::k,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      buPartialEffBs2Dst0Kst0_D0pi0_WN_(Params::Get().CreateFixed(
          "buPartialEffBs2Dst0Kst0_D0pi0_WN_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Bachelor::k,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Bachelor::k,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      // -------------------- Bs2Dst0Kst0_D0gamma_WN -------------------- //
      Bs2Dst0Kst0_D0gamma_WN_thresholdDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_WN_thresholdDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bs2Dst0Kst0_PdfDelta,
          Sign::same)),
      Bs2Dst0Kst0_D0gamma_WN_aDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_WN_aDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bs2Dst0Kst0_PdfDelta,
          Sign::none)),
      Bs2Dst0Kst0_D0gamma_WN_bDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_WN_bDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bs2Dst0Kst0_PdfDelta,
          Sign::none)),
      Bs2Dst0Kst0_D0gamma_WN_cDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_WN_cDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bs2Dst0Kst0_PdfDelta,
          Sign::same)),
      pdfDelta_Bs2Dst0Kst0_D0gamma_WN_(("pdfDelta_Bs2Dst0Kst0_D0gamma_WN_" +
                                        ComposeName(uniqueId_, Neutral::gamma))
                                           .c_str(),
                                       "", Configuration::Get().deltaMass(),
                                       *Bs2Dst0Kst0_D0gamma_WN_thresholdDelta_,
                                       *Bs2Dst0Kst0_D0gamma_WN_cDelta_,
                                       *Bs2Dst0Kst0_D0gamma_WN_aDelta_,
                                       *Bs2Dst0Kst0_D0gamma_WN_bDelta_),
      Bs2Dst0Kst0_D0gamma_WN_meanBu_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_WN_meanBu", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kst0_D0gamma_WN, Systematic::Bs2Dst0Kst0_PdfBu,
          Sign::same)),
      Bs2Dst0Kst0_D0gamma_WN_sigmaBu_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_WN_sigmaBu", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kst0_D0gamma_WN, Systematic::Bs2Dst0Kst0_PdfBu,
          Sign::same)),
      pdfBu_Bs2Dst0Kst0_D0gamma_WN_(("pdfBu_Bs2Dst0Kst0_D0gamma_WN_" +
                                     ComposeName(uniqueId_, Neutral::gamma))
                                        .c_str(),
                                    "", Configuration::Get().buDeltaMass(),
                                    *Bs2Dst0Kst0_D0gamma_WN_meanBu_,
                                    *Bs2Dst0Kst0_D0gamma_WN_sigmaBu_),
      Bs2Dst0Kst0_D0gamma_WN_meanBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_WN_meanBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kst0_D0gamma_WN, Systematic::Bs2Dst0Kst0_PdfBuPartial,
          Sign::same)),
      Bs2Dst0Kst0_D0gamma_WN_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_WN_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Mode::Bs2Dst0Kst0_D0gamma_WN, Systematic::Bs2Dst0Kst0_PdfBuPartial,
          Sign::same)),
      pdfBuPartial_Bs2Dst0Kst0_D0gamma_WN_(
          ("pdfBuPartial_Bs2Dst0Kst0_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *Bs2Dst0Kst0_D0gamma_WN_meanBuPartial_,
          *Bs2Dst0Kst0_D0gamma_WN_sigmaBuPartial_),
      mcEff_Bs2Dst0Kst0_D0gamma_WN_(Params::Get().CreateFixed(
          "mcEff_Bs2Dst0Kst0_D0gamma_WN", uniqueId_, Neutral::gamma,
          ReturnMCEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Neutral::gamma,
                       Bachelor::k, Efficiency::mcEff),
          ReturnMCEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Neutral::gamma,
                       Bachelor::k, Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg, Sign::same)),
      orEffBs2Dst0Kst0_D0gamma_WN_(Params::Get().CreateFixed(
          "orEffBs2Dst0Kst0_D0gamma_WN_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Bachelor::k,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Bachelor::k,
                        Efficiency::orEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      deltaEffBs2Dst0Kst0_D0gamma_WN_(Params::Get().CreateFixed(
          "deltaEffBs2Dst0Kst0_D0gamma_WN_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Bachelor::k,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Bachelor::k,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      buEffBs2Dst0Kst0_D0gamma_WN_(Params::Get().CreateFixed(
          "buEffBs2Dst0Kst0_D0gamma_WN_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Bachelor::k,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Bachelor::k,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      buPartialEffBs2Dst0Kst0_D0gamma_WN_(Params::Get().CreateFixed(
          "buPartialEffBs2Dst0Kst0_D0gamma_WN_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Bachelor::k,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Bachelor::k,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      // -------------------- Bs2Dst0Kst0_WN -------------------- //
      Bs2Dst0Kst0_fracD0pi0_WN_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_fracD0pi0_WN", uniqueId_, Neutral::gamma,
          ReadPdfFracs<Neutral::gamma, Bachelor::k>("Bs2Dst0Kst0_fracD0pi0_WN",
                                                    ReturnType::val),
          ReadPdfFracs<Neutral::gamma, Bachelor::k>("Bs2Dst0Kst0_fracD0pi0_WN",
                                                    ReturnType::std),
          Systematic::Bs2Dst0Kst0_Frac, Sign::same)),
      Bs2Dst0Kst0_fracD0pi0_WN_Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_fracD0pi0_WN_Bu", uniqueId_, Neutral::gamma,
          ReadPdfFracs<Neutral::gamma, Bachelor::k>(
              "Bs2Dst0Kst0_fracD0pi0_WN_Bu", ReturnType::val),
          ReadPdfFracs<Neutral::gamma, Bachelor::k>(
              "Bs2Dst0Kst0_fracD0pi0_WN_Bu", ReturnType::std),
          Systematic::Bs2Dst0Kst0_Frac, Sign::same)),
      Bs2Dst0Kst0_fracD0pi0_WN_Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_fracD0pi0_WN_Delta", uniqueId_, Neutral::gamma,
          ReadPdfFracs<Neutral::gamma, Bachelor::k>(
              "Bs2Dst0Kst0_fracD0pi0_WN_Delta", ReturnType::val),
          ReadPdfFracs<Neutral::gamma, Bachelor::k>(
              "Bs2Dst0Kst0_fracD0pi0_WN_Delta", ReturnType::std),
          Systematic::Bs2Dst0Kst0_Frac, Sign::same)),
      Bs2Dst0Kst0_fracD0pi0_WN_BuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_fracD0pi0_WN_BuPartial", uniqueId_, Neutral::gamma,
          ReadPdfFracs<Neutral::gamma, Bachelor::k>(
              "Bs2Dst0Kst0_fracD0pi0_WN_BuPartial", ReturnType::val),
          ReadPdfFracs<Neutral::gamma, Bachelor::k>(
              "Bs2Dst0Kst0_fracD0pi0_WN_BuPartial", ReturnType::std),
          Systematic::Bs2Dst0Kst0_Frac, Sign::same)),
      pdfBu_Bs2Dst0Kst0_WN_(
          ("pdfBu_Bs2Dst0Kst0_WN_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdfBu_Bs2Dst0Kst0_D0pi0_WN_,
                     pdfBu_Bs2Dst0Kst0_D0gamma_WN_),
          *Bs2Dst0Kst0_fracD0pi0_WN_Bu_),
      pdfBuPartial_Bs2Dst0Kst0_WN_(
          ("pdfBuPartial_Bs2Dst0Kst0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdfBuPartial_Bs2Dst0Kst0_D0pi0_WN_,
                     pdfBuPartial_Bs2Dst0Kst0_D0gamma_WN_),
          *Bs2Dst0Kst0_fracD0pi0_WN_BuPartial_),
      mcEff_Bs2Dst0Kst0_WN_(
          ("mcEff_Bs2Dst0Kst0_WN_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bs2Dst0Kst0_fracD0pi0_WN_, *mcEff_Bs2Dst0Kst0_D0pi0_WN_,
                     *mcEff_Bs2Dst0Kst0_D0gamma_WN_)),
      orEffBs2Dst0Kst0_WN_(
          ("orEffBs2Dst0Kst0_WN_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bs2Dst0Kst0_fracD0pi0_WN_, *orEffBs2Dst0Kst0_D0pi0_WN_,
                     *orEffBs2Dst0Kst0_D0gamma_WN_)),
      buEffBs2Dst0Kst0_WN_(
          ("buEffBs2Dst0Kst0_WN_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bs2Dst0Kst0_fracD0pi0_WN_, *buEffBs2Dst0Kst0_D0pi0_WN_,
                     *buEffBs2Dst0Kst0_D0gamma_WN_)),
      deltaEffBs2Dst0Kst0_WN_(
          ("deltaEffBs2Dst0Kst0_WN_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bs2Dst0Kst0_fracD0pi0_WN_, *deltaEffBs2Dst0Kst0_D0pi0_WN_,
                     *deltaEffBs2Dst0Kst0_D0gamma_WN_)),
      buPartialEffBs2Dst0Kst0_WN_(
          ("buPartialEffBs2Dst0Kst0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bs2Dst0Kst0_fracD0pi0_WN_,
                     *buPartialEffBs2Dst0Kst0_D0pi0_WN_,
                     *buPartialEffBs2Dst0Kst0_D0gamma_WN_)),
      // -------------------- Bu2Dst0h_D0gamma_D02pik -------------------- //
      Bu2Dst0h_D0gamma_D02pik_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_D02pik_sigmaDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_D02pik, Systematic::D02pik_Pdfs, Sign::same)),
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
          Mode::Bu2Dst0pi_D0gamma_D02pik, Systematic::D02pik_Pdfs, Sign::same)),
      Bu2Dst0h_D0gamma_D02pik_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_D02pik_sigmaBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_D02pik, Systematic::D02pik_Pdfs, Sign::same)),
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
          Systematic::boxEffs_D02pik, Sign::same)),
      deltaEffBu2Dst0h_D0gamma_D02pik_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0gamma_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_D02pik, Sign::same)),
      buEffBu2Dst0h_D0gamma_D02pik_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0gamma_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_D02pik, Sign::same)),
      buPartialEffBu2Dst0h_D0gamma_D02pik_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0gamma_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_D02pik, Sign::same)),
      // -------------------- Bu2Dst0h_D0pi0_D02pik -------------------- //
      Bu2Dst0h_D0pi0_D02pik_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_sigmaDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::D02pik_Pdfs, Sign::same)),
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
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::D02pik_Pdfs, Sign::same)),
      Bu2Dst0h_D0pi0_D02pik_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_sigmaBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::D02pik_Pdfs, Sign::same)),
      pdfBu_Bu2Dst0h_D0pi0_D02pik_(("pdfBu_Bu2Dst0h_D0pi0_D02pik_" +
                                    ComposeName(uniqueId_, Neutral::gamma))
                                       .c_str(),
                                   "", Configuration::Get().buDeltaMass(),
                                   *Bu2Dst0h_D0pi0_D02pik_meanBu_,
                                   *Bu2Dst0h_D0pi0_D02pik_sigmaBu_),
      Bu2Dst0h_D0pi0_D02pik_meanBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_meanBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::D02pik_Pdfs, Sign::same)),
      Bu2Dst0h_D0pi0_D02pik_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_sigmaBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::D02pik_Pdfs, Sign::same)),
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
          Systematic::boxEffs_D02pik, Sign::same)),
      deltaEffBu2Dst0h_D0pi0_D02pik_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_D02pik, Sign::same)),
      buEffBu2Dst0h_D0pi0_D02pik_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_D02pik, Sign::same)),
      buPartialEffBu2Dst0h_D0pi0_D02pik_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0pi0_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_D02pik, Sign::same)),
      // -------------------- Bu2Dst0h_D0gamma_WN_D02pik -------------------- //
      Bu2Dst0h_D0gamma_WN_D02pik_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_D02pik_sigmaDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Systematic::D02pik_Pdfs,
          Sign::same)),
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
          Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Systematic::D02pik_Pdfs,
          Sign::same)),
      Bu2Dst0h_D0gamma_WN_D02pik_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_D02pik_sigmaBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Systematic::D02pik_Pdfs,
          Sign::same)),
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
          Systematic::boxEffs_D02pik, Sign::same)),
      deltaEffBu2Dst0h_D0gamma_WN_D02pik_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0gamma_WN_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_D02pik, Sign::same)),
      buEffBu2Dst0h_D0gamma_WN_D02pik_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0gamma_WN_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_D02pik, Sign::same)),
      buPartialEffBu2Dst0h_D0gamma_WN_D02pik_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0gamma_WN_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN_D02pik, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_D02pik, Sign::same)),
      // -------------------- Bu2Dst0h_D0pi0_WN_D02pik -------------------- //
      Bu2Dst0h_D0pi0_WN_D02pik_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_sigmaDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::D02pik_Pdfs,
          Sign::same)),
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
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::D02pik_Pdfs,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_D02pik_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_sigmaBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::D02pik_Pdfs,
          Sign::same)),
      pdfBu_Bu2Dst0h_D0pi0_WN_D02pik_(("pdfBu_Bu2Dst0h_D0pi0_WN_D02pik_" +
                                       ComposeName(uniqueId_, Neutral::gamma))
                                          .c_str(),
                                      "", Configuration::Get().buDeltaMass(),
                                      *Bu2Dst0h_D0pi0_WN_D02pik_meanBu_,
                                      *Bu2Dst0h_D0pi0_WN_D02pik_sigmaBu_),
      Bu2Dst0h_D0pi0_WN_D02pik_meanBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_meanBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::D02pik_Pdfs,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_D02pik_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_sigmaBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::D02pik_Pdfs,
          Sign::same)),
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
          Systematic::boxEffs_D02pik, Sign::same)),
      deltaEffBu2Dst0h_D0pi0_WN_D02pik_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_WN_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_D02pik, Sign::same)),
      buEffBu2Dst0h_D0pi0_WN_D02pik_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_WN_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_D02pik, Sign::same)),
      buPartialEffBu2Dst0h_D0pi0_WN_D02pik_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0pi0_WN_D02pik_", uniqueId_, Neutral::gamma,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_D02pik, Sign::same)),
      // -------------------- Bkg Fractions -------------------- //
      bkgFracGlobal_WN_(Params::Get().CreateFloating(
          "bkgFracGlobal_WN", uniqueId_, Neutral::gamma, 1, 0, 5)),
      bkgFloatingFrac_Bu2Dst0h_D0gamma_WN_(nullptr),
      bkgFracFAV_Bd2Dsth_(Params::Get().CreateFloating(
          "bkgFracFAV_Bd2Dsth", uniqueId_, Neutral::gamma,
          ReadBkgFracs<Neutral::gamma>(Mode::Bd2Dstpi, ReturnType::val), 0, 5)),
      // Constrained relative to Bd2Dsth
      // bkgFracFAV_Bu2D0hst_(Params::Get().CreateFloating(
      //     "bkgFracFAV_Bu2D0hst", uniqueId_, Neutral::gamma,
      // ReadBkgFracs<Neutral::gamma>(Mode::Bu2D0rho, ReturnType::val),
      //     0, 5)),
      bkgFracFAV_Bu2D0hst_(Params::Get().CreateFixed(
          "bkgFracFAV_Bu2D0hst", uniqueId_, Neutral::gamma,
          ReadBkgFracs<Neutral::gamma>(Mode::Bu2D0rho, ReturnType::val),
          ReadBkgFracs<Neutral::gamma>(Mode::Bu2D0rho, ReturnType::std),
          Systematic::Bu2D0hst_BkgFrac, Sign::same)),
      cpFrac_Bu2D0hst_(Params::Get().CreateFloating(
          "cpFrac_Bu2D0hst", uniqueId_, Neutral::gamma, 2, 0, 5)),
      bkgFracFAV_Bu2Dst0hst_(Params::Get().CreateFixed(
          "bkgFracFAV_Bu2Dst0hst", uniqueId_, Neutral::gamma,
          ReadBkgFracs<Neutral::gamma>(Mode::Bu2Dst0rho, ReturnType::val),
          ReadBkgFracs<Neutral::gamma>(Mode::Bu2Dst0rho, ReturnType::std),
          Systematic::Bu2Dst0hst_BkgFrac, Sign::same)),
      // bkgFracFAV_Bu2Dst0hst_(Params::Get().CreateFloating(
      //     "bkgFracFAV_Bu2Dst0hst", uniqueId_, Neutral::gamma,
      //     ReadBkgFracs<Neutral::gamma>(Mode::Bu2Dst0rho, ReturnType::val),
      //     0, 5)),
      bkgFracKK_Lb2Omegach_Lcpi0_(Params::Get().CreateFloating(
          "bkgFracKK_Lb2Omegach_Lcpi0", uniqueId_, Neutral::gamma, 0.1, 0, 5)),
      bkgFracADS_Bs2D0Kst0_(Params::Get().CreateFloating(
          "bkgFracADS_Bs2D0Kst0", uniqueId_, Neutral::gamma,
          ReadBkgFracs<Neutral::gamma>(Mode::Bs2D0Kst0, ReturnType::val), -2,
          10)),
      // bkgFracADS_Bs2D0Kst0_(Params::Get().CreateFixed(
      //     "bkgFracADS_Bs2D0Kst0", uniqueId_, Neutral::gamma,
      //     ReadBkgFracs<Neutral::gamma>(Mode::Bs2D0Kst0, ReturnType::val),
      //     ReadBkgFracs<Neutral::gamma>(Mode::Bs2D0Kst0, ReturnType::std),
      //     Systematic::Bs2D0Kst0_BkgFrac, Sign::same)) {}
      bkgFracADS_Bs2Dst0Kst0_(Params::Get().CreateFloating(
          "bkgFracADS_Bs2Dst0Kst0", uniqueId_, Neutral::gamma,
          ReadBkgFracs<Neutral::gamma>(Mode::Bs2Dst0Kst0, ReturnType::val), 0,
          5)),
      // -------------------- Bs2Dst0Kst0 -------------------- //
      Bs2Dst0Kst0_fracWN_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_fracWN", uniqueId_, Neutral::gamma,
          ReadPdfFracs<Neutral::gamma, Bachelor::k>("Bs2Dst0Kst0_fracWN",
                                                    ReturnType::val),
          ReadPdfFracs<Neutral::gamma, Bachelor::k>("Bs2Dst0Kst0_fracWN",
                                                    ReturnType::std),
          Systematic::Bs2Dst0Kst0_Frac, Sign::same)),
      Bs2Dst0Kst0_fracWN_Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_fracWN_Bu", uniqueId_, Neutral::gamma,
          ReadPdfFracs<Neutral::gamma, Bachelor::k>("Bs2Dst0Kst0_fracWN_Bu",
                                                    ReturnType::val),
          // 1.0,
          ReadPdfFracs<Neutral::gamma, Bachelor::k>("Bs2Dst0Kst0_fracWN_Bu",
                                                    ReturnType::std),
          Systematic::Bs2Dst0Kst0_Frac, Sign::same)),
      Bs2Dst0Kst0_fracWN_Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_fracWN_Delta", uniqueId_, Neutral::gamma,
          ReadPdfFracs<Neutral::gamma, Bachelor::k>("Bs2Dst0Kst0_fracWN_Delta",
                                                    ReturnType::val),
          ReadPdfFracs<Neutral::gamma, Bachelor::k>("Bs2Dst0Kst0_fracWN_Delta",
                                                    ReturnType::std),
          Systematic::Bs2Dst0Kst0_Frac, Sign::same)),
      Bs2Dst0Kst0_fracWN_BuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_fracWN_BuPartial", uniqueId_, Neutral::gamma,
          ReadPdfFracs<Neutral::gamma, Bachelor::k>(
              "Bs2Dst0Kst0_fracWN_BuPartial", ReturnType::val),
          // 1.0,
          ReadPdfFracs<Neutral::gamma, Bachelor::k>(
              "Bs2Dst0Kst0_fracWN_BuPartial", ReturnType::std),
          Systematic::Bs2Dst0Kst0_Frac, Sign::same)),
      Bs2Dst0Kst0_floatingFracWN_Bu_(
          ("Bs2Dst0Kst0_floatingFracWN_Bu_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0*@1", RooArgList(*Bs2Dst0Kst0_fracWN_Bu_, *bkgFracGlobal_WN_)),
      // "@0", RooArgList(*Bs2Dst0Kst0_fracWN_Bu_)),
      Bs2Dst0Kst0_floatingFracWN_Delta_(
          ("Bs2Dst0Kst0_floatingFracWN_Delta_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0*@1", RooArgList(*Bs2Dst0Kst0_fracWN_Delta_, *bkgFracGlobal_WN_)),
      Bs2Dst0Kst0_floatingFracWN_BuPartial_(
          ("Bs2Dst0Kst0_floatingFracWN_BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0*@1",
          // "@0",
          RooArgList(*Bs2Dst0Kst0_fracWN_BuPartial_, *bkgFracGlobal_WN_)),
      pdfBu_Bs2Dst0Kst0_(
          ("pdfBu_Bs2Dst0Kst0_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", RooArgList(pdfBu_Bs2Dst0Kst0_WN_, pdfBu_Bs2Dst0Kst0_D0gamma_),
          Bs2Dst0Kst0_floatingFracWN_Bu_),
      pdfBuPartial_Bs2Dst0Kst0_(
          ("pdfBuPartial_Bs2Dst0Kst0_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdfBuPartial_Bs2Dst0Kst0_WN_,
                     pdfBuPartial_Bs2Dst0Kst0_D0pi0_),
          Bs2Dst0Kst0_floatingFracWN_BuPartial_),
      mcEff_Bs2Dst0Kst0_(
          ("mcEff_Bs2Dst0Kst0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@2*(1-@0*@1)+@3*@0*@1",
          RooArgList(*Bs2Dst0Kst0_fracWN_, *bkgFracGlobal_WN_,
                     mcEff_Bs2Dst0Kst0_comb_, mcEff_Bs2Dst0Kst0_WN_)),
      orEffBs2Dst0Kst0_(
          ("orEffBs2Dst0Kst0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@2*(1-@0*@1)+@3*@0*@1",
          RooArgList(*Bs2Dst0Kst0_fracWN_, *bkgFracGlobal_WN_,
                     orEffBs2Dst0Kst0_comb_, orEffBs2Dst0Kst0_WN_)),
      buEffBs2Dst0Kst0_(
          ("buEffBs2Dst0Kst0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@2*(1-@0*@1)+@3*@0*@1",
          // "@0",
          RooArgList(*Bs2Dst0Kst0_fracWN_, *bkgFracGlobal_WN_,
                     *buEffBs2Dst0Kst0_D0gamma_, buEffBs2Dst0Kst0_WN_)),
      // RooArgList(*buEffBs2Dst0Kst0_D0gamma_)),
      deltaEffBs2Dst0Kst0_(
          ("deltaEffBs2Dst0Kst0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@2*(1-@0*@1)+@3*@0*@1",
          RooArgList(*Bs2Dst0Kst0_fracWN_, *bkgFracGlobal_WN_,
                     deltaEffBs2Dst0Kst0_comb_, deltaEffBs2Dst0Kst0_WN_)),
      buPartialEffBs2Dst0Kst0_(
          ("buPartialEffBs2Dst0Kst0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@2*(1-@0*@1)+@3*@0*@1",
          // "@0",
          RooArgList(*Bs2Dst0Kst0_fracWN_, *bkgFracGlobal_WN_,
                     *buPartialEffBs2Dst0Kst0_D0pi0_,
                     buPartialEffBs2Dst0Kst0_WN_)) {}
// RooArgList(*buPartialEffBs2Dst0Kst0_D0pi0_)) {}
