#include "GlobalVars.h"
#include "NeutralVars.h"
#include "Params.h"

// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::pi0>::NeutralVars(int uniqueId)
    // -------------------- PDF SHAPES -------------------- //
    // -------------------- Bu2Dst0h_D0pi0 -------------------- //
    : uniqueId_(uniqueId),
      Bu2Dst0h_D0pi0_meanDelta_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_meanDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, 138, 146)),
      Bu2Dst0h_D0pi0_KpiSigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_KpiSigmaDelta", uniqueId_, Neutral::pi0, 1.0167e+00,
          4.10e-02, Systematic::pi0DeltaWidthRatio, Sign::same)),
      // Bu2Dst0h_D0pi0_KpiSigmaDelta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_KpiSigmaDelta", uniqueId_, Neutral::pi0, 1.038649,
      //     0.9, 1.1)),
      // Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::same)),
      Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::pi0, 7.2821e-01,
          5.31e-02, Systematic::pi0DeltaTails, Sign::same)),
      // Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0, 0, 5)),
      Bu2Dst0h_D0pi0_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::same)),
      // Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_a2Delta", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::same)),
      Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2Delta", uniqueId_, Neutral::pi0, -7.5087e-01,
          1.77e-02, Systematic::pi0DeltaTails, Sign::same)),
      // Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_a2Delta", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0, -5, -0.000001)),
      Bu2Dst0h_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::same)),
      Bu2Dst0h_D0pi0_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf1Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaFrac, Sign::same)),
      Bu2Dst0h_D0pi0_mean1Bu_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_mean1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, 5270, 5280)),
      Bu2Dst0h_D0pi0_meanOffset21Bu_(nullptr),
      Bu2Dst0h_D0pi0_mean2Bu_(),
      Bu2Dst0h_D0pi0_sigmaRatio21Bu_(nullptr),
      Bu2Dst0h_D0pi0_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_KpiSigmaBu", uniqueId_, Neutral::pi0, 9.4326e-01,
          3.16e-02, Systematic::pi0BuWidthRatio, Sign::same)),
      // Bu2Dst0h_D0pi0_KpiSigmaBu_(
      //     Params::Get().CreateFloating("Bu2Dst0h_D0pi0_KpiSigmaBu",
      //     uniqueId_,
      //                                  Neutral::pi0, 0.944180, 0.9, 1.1)),
      // Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_a1Bu", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0, Systematic::pi0BuTails, Sign::same)),
      Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Bu", uniqueId_, Neutral::pi0, 1.4577e+00, 7.65e-02,
          Systematic::pi0BuTails, Sign::same)),
      // Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_a1Bu", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0, 0, 5)),
      Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Bu", uniqueId_, Neutral::pi0, Mode::Bu2Dst0pi_D0pi0,
          Systematic::pi0BuTails, Sign::same)),
      // Bu2Dst0h_D0pi0_a2Bu_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_a2Bu", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0, Systematic::pi0BuTails, Sign::same)),
      Bu2Dst0h_D0pi0_a2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2Bu", uniqueId_, Neutral::pi0, -1.3131e+00, 4.27e-02,
          Systematic::pi0BuTails, Sign::same)),
      // Bu2Dst0h_D0pi0_a2Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_a2Bu", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0, -5, -0.00001)),
      Bu2Dst0h_D0pi0_n2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2Bu", uniqueId_, Neutral::pi0, Mode::Bu2Dst0pi_D0pi0,
          Systematic::pi0BuTails, Sign::same)),
      Bu2Dst0h_D0pi0_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0BuFrac, Sign::same)),
      Bu2Dst0h_D0pi0_mean1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_meanOffset31BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_mean3BuPartial_(),
      Bu2Dst0h_D0pi0_KpiSigmaBuPartial_(nullptr),
      Bu2Dst0h_D0pi0_sigmaRatio21BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_sigmaRatio31BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_a1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_a2BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_n1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_n2BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_fracPdf1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_fracPdf2BuPartial_(nullptr),
      // -------------------- Bu2Dst0h_D0gamma -------------------- //
      // All gamma signal reconstructed in mis-reconstructed PDF
      Bu2Dst0h_D0gamma_meanDelta_(nullptr),
      Bu2Dst0h_D0gamma_KpiSigmaDelta_(nullptr),
      Bu2Dst0h_D0gamma_a1Delta_(nullptr),
      Bu2Dst0h_D0gamma_a2Delta_(nullptr),
      Bu2Dst0h_D0gamma_n1Delta_(nullptr),
      Bu2Dst0h_D0gamma_n2Delta_(nullptr),
      Bu2Dst0h_D0gamma_fracPdf1Delta_(nullptr),
      Bu2Dst0h_D0gamma_meanBu_(nullptr),
      Bu2Dst0h_D0gamma_KpiSigmaBu_(nullptr),
      Bu2Dst0h_D0gamma_a1Bu_(nullptr),
      Bu2Dst0h_D0gamma_a2Bu_(nullptr),
      Bu2Dst0h_D0gamma_n1Bu_(nullptr),
      Bu2Dst0h_D0gamma_n2Bu_(nullptr),
      Bu2Dst0h_D0gamma_fracPdf1Bu_(nullptr),
      Bu2Dst0h_D0gamma_meanBuPartial_(nullptr),
      Bu2Dst0h_D0gamma_sigmaBuPartial_(nullptr),
      // -------------------- Bu2Dst0h_D0pi0_WN -------------------- //
      Bu2Dst0h_D0pi0_WN_thresholdDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_thresholdDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNDeltaPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_cDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_cDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNDeltaPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_mean1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_mean1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::same)),
      // Bu2Dst0h_D0pi0_WN_mean1Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_mean1Bu", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0_WN, 5260, 5280)),
      Bu2Dst0h_D0pi0_WN_meanOffset21Bu_(nullptr),
      Bu2Dst0h_D0pi0_WN_mean2Bu_(),
      Bu2Dst0h_D0pi0_WN_sigmaRatio21Bu_(nullptr),
      Bu2Dst0h_D0pi0_WN_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_KpiSigmaBu", uniqueId_, Neutral::pi0, 0.98451,
          0.01585, Systematic::pi0WNBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_a1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::same)),
      // Bu2Dst0h_D0pi0_WN_a1Bu_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_WN_a1Bu", uniqueId_, Neutral::pi0, 3.3625e+00,
      //     4.40e-01, Systematic::pi0WNBuPdf, Sign::same)),
      // Bu2Dst0h_D0pi0_WN_a1Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_a1Bu", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0_WN, 0, 5)),
      Bu2Dst0h_D0pi0_WN_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_n1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_a2Bu_(nullptr),
      Bu2Dst0h_D0pi0_WN_n2Bu_(nullptr),
      Bu2Dst0h_D0pi0_WN_fracPdf1Bu_(nullptr),
      Bu2Dst0h_D0pi0_WN_mean1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_WN_meanOffset31BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_WN_mean3BuPartial_(),
      Bu2Dst0h_D0pi0_WN_KpiSigmaBuPartial_(nullptr),
      Bu2Dst0h_D0pi0_WN_sigmaRatio21BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_WN_sigmaRatio31BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_WN_a1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_WN_a2BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_WN_n1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_WN_n2BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_WN_fracPdf1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_WN_fracPdf2BuPartial_(nullptr),
      // -------------------- Bu2Dst0h_D0gamma_WN -------------------- //
      Bu2Dst0h_D0gamma_WN_thresholdDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_thresholdDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::pi0WNDeltaPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_aDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_aDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::pi0WNDeltaPdf, Sign::none)),
      Bu2Dst0h_D0gamma_WN_bDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_bDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::pi0WNDeltaPdf, Sign::none)),
      Bu2Dst0h_D0gamma_WN_cDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_cDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::pi0WNDeltaPdf, Sign::same)),
      pdfDelta_Bu2Dst0h_D0gamma_WN_(new RooDstD0BG(
          ("pdfDelta_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0gamma_WN_thresholdDelta_, *Bu2Dst0h_D0gamma_WN_cDelta_,
          *Bu2Dst0h_D0gamma_WN_aDelta_, *Bu2Dst0h_D0gamma_WN_bDelta_)),
      Bu2Dst0h_D0gamma_WN_mean1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_mean1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNBuPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_meanOffset21Bu_(nullptr),
      Bu2Dst0h_D0gamma_WN_mean2Bu_(),
      Bu2Dst0h_D0gamma_WN_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_KpiSigmaBu", uniqueId_, Neutral::pi0, 1.0, 0.05,
          Systematic::gammaWNBuPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_sigmaRatio21Bu_(nullptr),
      Bu2Dst0h_D0gamma_WN_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_a1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNBuPdf, Sign::same)),
      // Bu2Dst0h_D0gamma_WN_a1Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0gamma_WN_a1Bu", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0gamma_WN, -5, -0.000001)),
      Bu2Dst0h_D0gamma_WN_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_n1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNBuPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_fracPdf1Bu_(nullptr),
      Bu2Dst0h_D0gamma_WN_meanBuPartial_(nullptr),
      Bu2Dst0h_D0gamma_WN_KpiSigmaBuPartial_(nullptr),
      // -------------------- Bu2Dst0h_WN -------------------- //
      Bu2Dst0h_WN_floatingFracD0pi0_(Params::Get().CreateFixed(
          "Bu2Dst0h_WN_floatingFracD0pi0", uniqueId_, Neutral::pi0, 1, 0.,
          Systematic::NA, Sign::same)),
      // -------------------- Bd2Dsth -------------------- //
      Bd2Dsth_thresholdDelta_(Params::Get().CreateFixed(
          "Bd2Dsth_thresholdDelta", uniqueId_, Neutral::pi0, Mode::Bd2Dstpi,
          Systematic::Bd2DsthDeltaPdf, Sign::same)),
      Bd2Dsth_aDelta_(Params::Get().CreateFixed(
          "Bd2Dsth_aDelta", uniqueId_, Neutral::pi0, Mode::Bd2Dstpi,
          Systematic::Bd2DsthDeltaPdf, Sign::none)),
      // Bd2Dsth_aDelta_(Params::Get().CreateFixed(
      //     "Bd2Dsth_aDelta", uniqueId_, Neutral::pi0, 3.0827e+00, 1.65e+00,
      //     Systematic::Bd2DsthDeltaPdf, Sign::none)),
      // Bd2Dsth_aDelta_(Params::Get().CreateFloating(
      //     "Bd2Dsth_aDelta", uniqueId_, Neutral::pi0, Mode::Bd2Dstpi, 0, 5)),
      Bd2Dsth_bDelta_(Params::Get().CreateFixed(
          "Bd2Dsth_bDelta", uniqueId_, Neutral::pi0, Mode::Bd2Dstpi,
          Systematic::Bd2DsthDeltaPdf, Sign::none)),
      Bd2Dsth_cDelta_(Params::Get().CreateFixed(
          "Bd2Dsth_cDelta", uniqueId_, Neutral::pi0, Mode::Bd2Dstpi,
          Systematic::Bd2DsthDeltaPdf, Sign::same)),
      pdfDelta_Bd2Dsth_(
          ("pdfDelta_Bd2Dsth_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", Configuration::Get().deltaMass(), *Bd2Dsth_thresholdDelta_,
          *Bd2Dsth_cDelta_, *Bd2Dsth_aDelta_, *Bd2Dsth_bDelta_),
      Bd2Dsth_mean1Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_mean1Bu", uniqueId_, Neutral::pi0, Mode::Bd2Dstpi,
          Systematic::Bd2DsthBuPdf, Sign::same)),
      // Bd2Dsth_mean1Bu_(Params::Get().CreateFloating(
      //     "Bd2Dsth_mean1Bu", uniqueId_, Neutral::pi0, Mode::Bd2Dstpi,
      //     5255, 5275)),
      Bd2Dsth_meanOffset21Bu_(nullptr),
      Bd2Dsth_mean2Bu_(),
      Bd2Dsth_sigmaRatio21Bu_(nullptr),
      Bd2Dsth_a1Bu_(nullptr),
      Bd2Dsth_n1Bu_(nullptr),
      Bd2Dsth_a2Bu_(nullptr),
      Bd2Dsth_n2Bu_(nullptr),
      Bd2Dsth_fracPdf1Bu_(nullptr),
      Bd2Dsth_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bd2Dsth_KpiSigmaBu", uniqueId_, Neutral::pi0, 1.0, 0.05,
          Systematic::Bd2DsthBuPdf, Sign::same)),
      Bd2Dsth_mean1BuPartial_(nullptr),
      Bd2Dsth_meanOffset21BuPartial_(nullptr),
      Bd2Dsth_mean2BuPartial_(),
      Bd2Dsth_KpiSigmaBuPartial_(nullptr),
      Bd2Dsth_sigmaRatio21BuPartial_(nullptr),
      Bd2Dsth_a1BuPartial_(nullptr),
      Bd2Dsth_n1BuPartial_(nullptr),
      Bd2Dsth_a2BuPartial_(nullptr),
      Bd2Dsth_n2BuPartial_(nullptr),
      Bd2Dsth_fracPdf1BuPartial_(nullptr),
      // -------------------- Bu2D0hst -------------------- //
      Bu2D0hst_thresholdDelta_(Params::Get().CreateFixed(
          "Bu2D0hst_thresholdDelta", uniqueId_, Neutral::pi0, Mode::Bu2D0rho,
          Systematic::Bu2D0hstDeltaPdf, Sign::same)),
      Bu2D0hst_aDelta_(Params::Get().CreateFixed(
          "Bu2D0hst_aDelta", uniqueId_, Neutral::pi0, Mode::Bu2D0rho,
          Systematic::Bu2D0hstDeltaPdf, Sign::none)),
      // Bu2D0hst_aDelta_(Params::Get().CreateFixed(
      //     "Bu2D0hst_aDelta", uniqueId_, Neutral::pi0, -3.2402e+00, 2.21e+00,
      //     Systematic::Bu2D0hstDeltaPdf, Sign::none)),
      // Bu2D0hst_aDelta_(Params::Get().CreateFloating(
      //     "Bu2D0hst_aDelta", uniqueId_, Neutral::pi0, Mode::Bu2D0rho, -10,
      //     10)),
      Bu2D0hst_bDelta_(Params::Get().CreateFixed(
          "Bu2D0hst_bDelta", uniqueId_, Neutral::pi0, Mode::Bu2D0rho,
          Systematic::Bu2D0hstDeltaPdf, Sign::none)),
      Bu2D0hst_cDelta_(Params::Get().CreateFixed(
          "Bu2D0hst_cDelta", uniqueId_, Neutral::pi0, Mode::Bu2D0rho,
          Systematic::Bu2D0hstDeltaPdf, Sign::same)),
      pdfDelta_Bu2D0hst_(new RooDstD0BG(
          ("pdfDelta_Bu2D0hst_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", Configuration::Get().deltaMass(), *Bu2D0hst_thresholdDelta_,
          *Bu2D0hst_cDelta_, *Bu2D0hst_aDelta_, *Bu2D0hst_bDelta_)),
      Bu2D0hst_mean1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_mean1Bu", uniqueId_, Neutral::pi0, Mode::Bu2D0rho,
          Systematic::Bu2D0hstBuPdf, Sign::same)),
      // Bu2D0hst_mean1Bu_(Params::Get().CreateFloating(
      //     "Bu2D0hst_mean1Bu", uniqueId_, Neutral::pi0, Mode::Bu2D0rho,
      //     5235, 5255)),
      Bu2D0hst_meanOffset21Bu_(nullptr),
      Bu2D0hst_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2D0hst_KpiSigmaBu", uniqueId_, Neutral::pi0, 1.0, 0.05,
          Systematic::Bu2D0hstBuPdf, Sign::same)),
      Bu2D0hst_sigmaRatio21Bu_(nullptr),
      Bu2D0hst_a1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_a1Bu", uniqueId_, Neutral::pi0, Mode::Bu2D0rho,
          Systematic::Bu2D0hstBuPdf, Sign::same)),
      // Bu2D0hst_a1Bu_(Params::Get().CreateFixed(
      //     "Bu2D0hst_a1Bu", uniqueId_, Neutral::pi0, 1.5254e+00, 2.10e-01,
      //     Systematic::Bu2D0hstBuPdf, Sign::same)),
      // Bu2D0hst_a1Bu_(Params::Get().CreateFloating("Bu2D0hst_a1Bu", uniqueId_,
      //                                             Neutral::pi0,
      //                                             Mode::Bu2D0rho, -5,
      //                                             -0.00001)),
      Bu2D0hst_n1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_n1Bu", uniqueId_, Neutral::pi0, Mode::Bu2D0rho,
          Systematic::Bu2D0hstBuPdf, Sign::same)),
      Bu2D0hst_fracPdf1Bu_(nullptr),
      Bu2D0hst_meanBuPartial_(nullptr),
      Bu2D0hst_KpiSigmaBuPartial_(nullptr),
      // -------------------- Bu2Dst0hst_D0gamma -------------------- //
      Bu2Dst0hst_D0gamma_meanDelta_(nullptr),
      Bu2Dst0hst_D0gamma_sigmaDelta_(nullptr),
      pdfDelta_Bu2Dst0hst_D0gamma_(),
      Bu2Dst0hst_D0gamma_meanOffset21Bu_(nullptr),
      Bu2Dst0hst_D0gamma_KpiSigmaBu_(nullptr),
      Bu2Dst0hst_D0gamma_sigmaRatio21Bu_(nullptr),
      Bu2Dst0hst_D0gamma_a1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_n1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_a2Bu_(nullptr),
      Bu2Dst0hst_D0gamma_n2Bu_(nullptr),
      Bu2Dst0hst_D0gamma_meanBuPartial_(nullptr),
      Bu2Dst0hst_D0gamma_KpiSigmaBuPartial_(nullptr),
      // -------------------- Bu2Dst0hst_D0pi0 -------------------- //
      Bu2Dst0hst_D0pi0_meanDelta_(nullptr),
      Bu2Dst0hst_D0pi0_sigmaDelta_(nullptr),
      pdfDelta_Bu2Dst0hst_D0pi0_(),
      Bu2Dst0hst_D0pi0_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_meanBu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0rho_D0pi0, Systematic::Bu2Dst0hst_D0pi0BuPdf,
          Sign::same)),
      Bu2Dst0hst_D0pi0_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_KpiSigmaBu", uniqueId_, Neutral::pi0, 1.0, 0.05,
          Systematic::Bu2Dst0hst_D0pi0BuPdf, Sign::same)),
      Bu2Dst0hst_D0pi0_meanBuPartial_(nullptr),
      Bu2Dst0hst_D0pi0_KpiSigmaBuPartial_(nullptr),
      // -------------------- Bu2Dst0hst -------------------- //
      Bu2Dst0hst_floatingFracD0pi0_(nullptr),
      // -------------------- Lb2Omegach_Lcpi0 -------------------- //
      Lb2Omegach_Lcpi0_thresholdDelta_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_thresholdDelta", uniqueId_, Neutral::pi0,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0DeltaPdf,
          Sign::same)),
      Lb2Omegach_Lcpi0_aDelta_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_aDelta", uniqueId_, Neutral::pi0,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0DeltaPdf,
          Sign::same)),
      Lb2Omegach_Lcpi0_bDelta_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_bDelta", uniqueId_, Neutral::pi0,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0DeltaPdf,
          Sign::same)),
      Lb2Omegach_Lcpi0_cDelta_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_cDelta", uniqueId_, Neutral::pi0,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0DeltaPdf,
          Sign::same)),
      pdfDelta_Lb2Omegach_Lcpi0_(
          ("pdfDelta_Lb2Omegach_Lcpi0_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Lb2Omegach_Lcpi0_thresholdDelta_, *Lb2Omegach_Lcpi0_cDelta_,
          *Lb2Omegach_Lcpi0_aDelta_, *Lb2Omegach_Lcpi0_bDelta_),
      Lb2Omegach_Lcpi0_meanBu_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_meanBu", uniqueId_, Neutral::pi0,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0BuPdf,
          Sign::same)),
      Lb2Omegach_Lcpi0_sigmaBu_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_sigmaBu", uniqueId_, Neutral::pi0,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0BuPdf,
          Sign::same)),
      Lb2Omegach_Lcpi0_a1Bu_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_a1Bu", uniqueId_, Neutral::pi0,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0BuPdf,
          Sign::same)),
      Lb2Omegach_Lcpi0_n1Bu_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_n1Bu", uniqueId_, Neutral::pi0,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0BuPdf,
          Sign::same)),
      pdfBu_Lb2Omegach_Lcpi0_(
          ("pdfBu_Lb2Omegach_Lcpi0_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *Lb2Omegach_Lcpi0_meanBu_,
          *Lb2Omegach_Lcpi0_sigmaBu_, *Lb2Omegach_Lcpi0_a1Bu_,
          *Lb2Omegach_Lcpi0_n1Bu_),
      Lb2Omegach_Lcpi0_meanBuPartial_(nullptr),
      Lb2Omegach_Lcpi0_sigmaBuPartial_(nullptr),
      Lb2Omegach_Lcpi0_a1BuPartial_(nullptr),
      Lb2Omegach_Lcpi0_n1BuPartial_(nullptr),
      pdfBuPartial_Lb2Omegach_Lcpi0_(),
      orEffLb2Omegach_Lcpi0_(Params::Get().CreateFixed(
          "orEffLb2Omegach_Lcpi0_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffLb2Omegach_Lcpi0_(Params::Get().CreateFixed(
          "deltaEffLb2Omegach_Lcpi0_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      buEffLb2Omegach_Lcpi0_(Params::Get().CreateFixed(
          "buEffLb2Omegach_Lcpi0_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      buPartialEffLb2Omegach_Lcpi0_(nullptr),
      // -------------------- Bs2D0Kpi -------------------- //
      Bs2D0Kpi_thresholdDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_thresholdDelta", uniqueId_, Neutral::pi0, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiDeltaPdf, Sign::same)),
      Bs2D0Kpi_aDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_aDelta", uniqueId_, Neutral::pi0, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiDeltaPdf, Sign::same)),
      Bs2D0Kpi_bDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_bDelta", uniqueId_, Neutral::pi0, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiDeltaPdf, Sign::same)),
      Bs2D0Kpi_cDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_cDelta", uniqueId_, Neutral::pi0, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiDeltaPdf, Sign::same)),
      pdfDelta_Bs2D0Kpi_(
          ("pdfDelta_Bs2D0Kpi_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", Configuration::Get().deltaMass(), *Bs2D0Kpi_thresholdDelta_,
          *Bs2D0Kpi_cDelta_, *Bs2D0Kpi_aDelta_, *Bs2D0Kpi_bDelta_),
      Bs2D0Kpi_meanBu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_meanBu", uniqueId_, Neutral::pi0, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiBuPdf, Sign::same)),
      Bs2D0Kpi_sigmaBu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_sigmaBu", uniqueId_, Neutral::pi0, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiBuPdf, Sign::same)),
      Bs2D0Kpi_a1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_a1Bu", uniqueId_, Neutral::pi0, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiBuPdf, Sign::same)),
      Bs2D0Kpi_n1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_n1Bu", uniqueId_, Neutral::pi0, Mode::Bs2D0Kpi,
          Systematic::Bs2D0KpiBuPdf, Sign::same)),
      pdfBu_Bs2D0Kpi_(
          ("pdfBu_Bs2D0Kpi_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2D0Kpi_meanBu_,
          *Bs2D0Kpi_sigmaBu_, *Bs2D0Kpi_a1Bu_, *Bs2D0Kpi_n1Bu_),
      Bs2D0Kpi_meanBuPartial_(nullptr),
      Bs2D0Kpi_sigmaBuPartial_(nullptr),
      Bs2D0Kpi_a1BuPartial_(nullptr),
      Bs2D0Kpi_n1BuPartial_(nullptr),
      pdfBuPartial_Bs2D0Kpi_(),
      orEffBs2D0Kpi_(Params::Get().CreateFixed(
          "orEffBs2D0Kpi_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, Efficiency::orEffErr,
                        false),
          Systematic::NA, Sign::same)),
      deltaEffBs2D0Kpi_(Params::Get().CreateFixed(
          "deltaEffBs2D0Kpi_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, Efficiency::deltaEff,
                        false),
          ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, Efficiency::deltaEffErr,
                        false),
          Systematic::NA, Sign::same)),
      buEffBs2D0Kpi_(Params::Get().CreateFixed(
          "buEffBs2D0Kpi_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, Efficiency::buEffErr,
                        false),
          Systematic::NA, Sign::same)),
      buPartialEffBs2D0Kpi_(nullptr),
      // -------------------- Bs2Dst0Kpi -------------------- //
      Bs2Dst0Kpi_thresholdDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_thresholdDelta", uniqueId_, Neutral::pi0,
          Mode::Bs2Dst0Kpi, Systematic::Bs2Dst0KpiDeltaPdf, Sign::same)),
      Bs2Dst0Kpi_aDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_aDelta", uniqueId_, Neutral::pi0, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiDeltaPdf, Sign::same)),
      Bs2Dst0Kpi_bDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_bDelta", uniqueId_, Neutral::pi0, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiDeltaPdf, Sign::same)),
      Bs2Dst0Kpi_cDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_cDelta", uniqueId_, Neutral::pi0, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiDeltaPdf, Sign::same)),
      pdfFlatDelta_Bs2Dst0Kpi_(
          ("pdfFlatDelta_Bs2Dst0Kpi_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2Dst0Kpi_thresholdDelta_,
          *Bs2Dst0Kpi_cDelta_, *Bs2Dst0Kpi_aDelta_, *Bs2Dst0Kpi_bDelta_),
      Bs2Dst0Kpi_fracPdfPi0PeakDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_fracPdfPi0PeakDelta", uniqueId_, Neutral::pi0,
          Mode::Bs2Dst0Kpi, Systematic::Bs2Dst0KpiDeltaPdf, Sign::same)),
      Bs2Dst0Kpi_fracPdfGammaPeakDelta_(nullptr),
      Bs2Dst0Kpi_mean1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_mean1Bu", uniqueId_, Neutral::pi0, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_meanOffset21Bu", uniqueId_, Neutral::pi0,
          Mode::Bs2Dst0Kpi, Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_mean2Bu_(
          ("Bs2Dst0Kpi_mean2Bu_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "@0+@1",
          RooArgList(*Bs2Dst0Kpi_mean1Bu_, *Bs2Dst0Kpi_meanOffset21Bu_)),
      Bs2Dst0Kpi_sigma1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigma1Bu", uniqueId_, Neutral::pi0, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_sigmaRatio21Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigmaRatio21Bu", uniqueId_, Neutral::pi0,
          Mode::Bs2Dst0Kpi, Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_sigma2Bu_(
          ("Bs2Dst0Kpi_sigma2Bu_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "@0*@1",
          RooArgList(*Bs2Dst0Kpi_sigma1Bu_, *Bs2Dst0Kpi_sigmaRatio21Bu_)),
      Bs2Dst0Kpi_a1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_a1Bu", uniqueId_, Neutral::pi0, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_a2Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_a2Bu", uniqueId_, Neutral::pi0, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_n1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_n1Bu", uniqueId_, Neutral::pi0, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_n2Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_n2Bu", uniqueId_, Neutral::pi0, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_fracPdf1Bu", uniqueId_, Neutral::pi0, Mode::Bs2Dst0Kpi,
          Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      pdf1Bu_Bs2Dst0Kpi_(
          ("pdf1Bu_Bs2Dst0Kpi_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2Dst0Kpi_mean1Bu_,
          *Bs2Dst0Kpi_sigma1Bu_, *Bs2Dst0Kpi_a1Bu_, *Bs2Dst0Kpi_n1Bu_),
      pdf2Bu_Bs2Dst0Kpi_(
          ("pdf2Bu_Bs2Dst0Kpi_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", Configuration::Get().buDeltaMass(), Bs2Dst0Kpi_mean2Bu_,
          Bs2Dst0Kpi_sigma2Bu_, *Bs2Dst0Kpi_a2Bu_, *Bs2Dst0Kpi_n2Bu_),
      pdfBu_Bs2Dst0Kpi_(
          ("pdfBu_Bs2Dst0Kpi_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", RooArgList(pdf1Bu_Bs2Dst0Kpi_, pdf2Bu_Bs2Dst0Kpi_),
          *Bs2Dst0Kpi_fracPdf1Bu_),
      Bs2Dst0Kpi_meanBuPartial_(nullptr),
      Bs2Dst0Kpi_sigmaBuPartial_(nullptr),
      Bs2Dst0Kpi_a1BuPartial_(nullptr),
      Bs2Dst0Kpi_n1BuPartial_(nullptr),
      pdfBuPartial_Bs2Dst0Kpi_(),
      orEffBs2Dst0Kpi_(
          Params::Get().CreateFixed("orEffBs2Dst0Kpi_", uniqueId_, Neutral::pi0,
                                    ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k,
                                                  Efficiency::orEff, false),
                                    ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k,
                                                  Efficiency::orEffErr, false),
                                    Systematic::NA, Sign::same)),
      deltaEffBs2Dst0Kpi_(Params::Get().CreateFixed(
          "deltaEffBs2Dst0Kpi_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k, Efficiency::deltaEff,
                        false),
          ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k, Efficiency::deltaEffErr,
                        false),
          Systematic::NA, Sign::same)),
      buEffBs2Dst0Kpi_(
          Params::Get().CreateFixed("buEffBs2Dst0Kpi_", uniqueId_, Neutral::pi0,
                                    ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k,
                                                  Efficiency::buEff, false),
                                    ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k,
                                                  Efficiency::buEffErr, false),
                                    Systematic::NA, Sign::same)),
      buPartialEffBs2Dst0Kpi_(nullptr),
      // -------------------- Bu2Dst0h_D0pi0_D02pik -------------------- //
      Bu2Dst0h_D0pi0_D02pik_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_sigmaDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_D02pik_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_a2Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_D02pik_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_n2Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_D02pik_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_fracPdf1Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::NA, Sign::same)),
      pdf1Delta_Bu2Dst0h_D0pi0_D02pik_(
          ("pdf1Delta_Bu2Dst0h_D0pi0_D02pik_" +
           ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0pi0_meanDelta_,
          *Bu2Dst0h_D0pi0_D02pik_sigmaDelta_, *Bu2Dst0h_D0pi0_a1Delta_,
          *Bu2Dst0h_D0pi0_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0pi0_D02pik_(
          ("pdf2Delta_Bu2Dst0h_D0pi0_D02pik_" +
           ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0pi0_meanDelta_,
          *Bu2Dst0h_D0pi0_D02pik_sigmaDelta_, *Bu2Dst0h_D0pi0_D02pik_a2Delta_,
          *Bu2Dst0h_D0pi0_D02pik_n2Delta_),
      pdfDelta_Bu2Dst0h_D0pi0_D02pik_(
          ("pdfDelta_Bu2Dst0h_D0pi0_D02pik_" +
           ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_D02pik_,
                     pdf2Delta_Bu2Dst0h_D0pi0_D02pik_),
          *Bu2Dst0h_D0pi0_D02pik_fracPdf1Delta_),
      Bu2Dst0h_D0pi0_D02pik_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_meanBu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_D02pik_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_sigmaBu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::NA, Sign::same)),
      pdfBu_Bu2Dst0h_D0pi0_D02pik_(("pdfBu_Bu2Dst0h_D0pi0_D02pik_" +
                                    ComposeName(uniqueId_, Neutral::pi0))
                                       .c_str(),
                                   "", Configuration::Get().buDeltaMass(),
                                   *Bu2Dst0h_D0pi0_D02pik_meanBu_,
                                   *Bu2Dst0h_D0pi0_D02pik_sigmaBu_),
      Bu2Dst0h_D0pi0_D02pik_meanBuPartial_(nullptr),
      Bu2Dst0h_D0pi0_D02pik_sigmaBuPartial_(nullptr),
      pdfBuPartial_Bu2Dst0h_D0pi0_D02pik_(),
      orEffBu2Dst0h_D0pi0_D02pik_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0pi0_D02pik_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0h_D0pi0_D02pik_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_D02pik_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0h_D0pi0_D02pik_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_D02pik_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      buPartialEffBu2Dst0h_D0pi0_D02pik_(nullptr),
      // -------------------- Bu2Dst0h_D0gamma_D02pik -------------------- //
      Bu2Dst0h_D0gamma_D02pik_sigmaDelta_(nullptr),
      pdf1Delta_Bu2Dst0h_D0gamma_D02pik_(),
      pdf2Delta_Bu2Dst0h_D0gamma_D02pik_(),
      pdfDelta_Bu2Dst0h_D0gamma_D02pik_(),
      Bu2Dst0h_D0gamma_D02pik_meanBu_(nullptr),
      Bu2Dst0h_D0gamma_D02pik_sigmaBu_(nullptr),
      pdfBu_Bu2Dst0h_D0gamma_D02pik_(),
      orEffBu2Dst0h_D0gamma_D02pik_(nullptr),
      deltaEffBu2Dst0h_D0gamma_D02pik_(nullptr),
      buEffBu2Dst0h_D0gamma_D02pik_(nullptr),
      buPartialEffBu2Dst0h_D0gamma_D02pik_(nullptr),
      // -------------------- Bu2Dst0h_D0pi0_WN_D02pik -------------------- //
      Bu2Dst0h_D0pi0_WN_D02pik_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_sigmaDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_WN_D02pik_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_a2Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_WN_D02pik_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_n2Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_WN_D02pik_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_fracPdf1Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::NA, Sign::same)),
      pdf1Delta_Bu2Dst0h_D0pi0_WN_D02pik_(
          ("pdf1Delta_Bu2Dst0h_D0pi0_WN_D02pik_" +
           ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0pi0_meanDelta_,
          *Bu2Dst0h_D0pi0_WN_D02pik_sigmaDelta_, *Bu2Dst0h_D0pi0_a1Delta_,
          *Bu2Dst0h_D0pi0_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0pi0_WN_D02pik_(
          ("pdf2Delta_Bu2Dst0h_D0pi0_WN_D02pik_" +
           ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0pi0_meanDelta_,
          *Bu2Dst0h_D0pi0_WN_D02pik_sigmaDelta_,
          *Bu2Dst0h_D0pi0_WN_D02pik_a2Delta_,
          *Bu2Dst0h_D0pi0_WN_D02pik_n2Delta_),
      pdfDelta_Bu2Dst0h_D0pi0_WN_D02pik_(
          ("pdfDelta_Bu2Dst0h_D0pi0_WN_D02pik_" +
           ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_WN_D02pik_,
                     pdf2Delta_Bu2Dst0h_D0pi0_WN_D02pik_),
          *Bu2Dst0h_D0pi0_WN_D02pik_fracPdf1Delta_),
      Bu2Dst0h_D0pi0_WN_D02pik_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_meanBu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_WN_D02pik_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_sigmaBu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::NA, Sign::same)),
      pdfBu_Bu2Dst0h_D0pi0_WN_D02pik_(("pdfBu_Bu2Dst0h_D0pi0_WN_D02pik_" +
                                       ComposeName(uniqueId_, Neutral::pi0))
                                          .c_str(),
                                      "", Configuration::Get().buDeltaMass(),
                                      *Bu2Dst0h_D0pi0_WN_D02pik_meanBu_,
                                      *Bu2Dst0h_D0pi0_WN_D02pik_sigmaBu_),
      Bu2Dst0h_D0pi0_WN_D02pik_meanBuPartial_(nullptr),
      Bu2Dst0h_D0pi0_WN_D02pik_sigmaBuPartial_(nullptr),
      pdfBuPartial_Bu2Dst0h_D0pi0_WN_D02pik_(),
      orEffBu2Dst0h_D0pi0_WN_D02pik_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0pi0_WN_D02pik_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0h_D0pi0_WN_D02pik_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_WN_D02pik_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0h_D0pi0_WN_D02pik_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_WN_D02pik_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      buPartialEffBu2Dst0h_D0pi0_WN_D02pik_(nullptr),
      // -------------------- Bu2Dst0h_D0gamma_WN_D02pik -------------------- //
      Bu2Dst0h_D0gamma_WN_D02pik_sigmaDelta_(nullptr),
      pdf1Delta_Bu2Dst0h_D0gamma_WN_D02pik_(),
      pdf2Delta_Bu2Dst0h_D0gamma_WN_D02pik_(),
      pdfDelta_Bu2Dst0h_D0gamma_WN_D02pik_(),
      Bu2Dst0h_D0gamma_WN_D02pik_meanBu_(nullptr),
      Bu2Dst0h_D0gamma_WN_D02pik_sigmaBu_(nullptr),
      pdfBu_Bu2Dst0h_D0gamma_WN_D02pik_(),
      orEffBu2Dst0h_D0gamma_WN_D02pik_(nullptr),
      deltaEffBu2Dst0h_D0gamma_WN_D02pik_(nullptr),
      buEffBu2Dst0h_D0gamma_WN_D02pik_(nullptr),
      buPartialEffBu2Dst0h_D0gamma_WN_D02pik_(nullptr),
      // -------------------- Bkg Fractions -------------------- //
      bkgFracGlobal_WN_(Params::Get().CreateFloating(
          "bkgFracGlobal_WN", uniqueId_, Neutral::pi0, 1, 0, 5)),
      bkgFracFAV_Bd2Dsth_(Params::Get().CreateFloating(
          "bkgFracFAV_Bd2Dsth", uniqueId_, Neutral::pi0,
          (ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff,
                         false) /
           ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi, Efficiency::orEff,
                         false)) *
              (ReturnMCEffs(Mode::Bd2Dstpi, Neutral::pi0, Bachelor::pi,
                            Efficiency::mcEff) /
               ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::pi0, Bachelor::pi,
                            Efficiency::mcEff)) *
              (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
               GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()) /
              (GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal() *
               GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0().getVal()),
          0, 5)),
      // Constrained relative to Bd2Dsth
      // bkgFracFAV_Bu2D0hst_(Params::Get().CreateFloating(
      //     "bkgFracFAV_Bu2D0hst", uniqueId_, Neutral::pi0,
      //     (ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::orEff,
      //                    false) /
      //      ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff,
      //                    false)) *
      //         (ReturnMCEffs(Mode::Bu2D0rho, Neutral::pi0, Bachelor::pi,
      //                       Efficiency::mcEff) /
      //          ReturnMCEffs(Mode::Bd2Dstpi, Neutral::pi0, Bachelor::pi,
      //                       Efficiency::mcEff)) *
      //         GlobalVars::Get(uniqueId_).kBF_Bu2D0rho().getVal() /
      //         (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
      //          GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()),
      //     0, 5)),
      bkgFracFAV_Bu2D0hst_(Params::Get().CreateFixed(
          "bkgFracFAV_Bu2D0hst", uniqueId_, Neutral::pi0,
          (ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::orEff,
                         false) /
           ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff,
                         false)) *
              (ReturnMCEffs(Mode::Bu2D0rho, Neutral::pi0, Bachelor::pi,
                            Efficiency::mcEff) /
               ReturnMCEffs(Mode::Bd2Dstpi, Neutral::pi0, Bachelor::pi,
                            Efficiency::mcEff)) *
              GlobalVars::Get(uniqueId_).kBF_Bu2D0rho().getVal() /
              (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
               GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()),
          0., Systematic::NA, Sign::none)),
      bkgFracFAV_Bu2Dst0hst_(Params::Get().CreateFixed(
          "bkgFracFAV_Bu2Dst0hst", uniqueId_, Neutral::pi0,
          (ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                         Efficiency::orEff, false) /
           ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff,
                         false)) *
                  (ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, Neutral::pi0,
                                Bachelor::pi, Efficiency::mcEff) /
                   ReturnMCEffs(Mode::Bd2Dstpi, Neutral::pi0, Bachelor::pi,
                                Efficiency::mcEff)) *
                  (GlobalVars::Get(uniqueId_).kBF_Bu2Dst0rho().getVal() *
                   GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0().getVal()) /
                  (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
                   GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()) +
              (ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                             Efficiency::orEff, false) /
               ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff,
                             false)) *
                  (ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, Neutral::pi0,
                                Bachelor::pi, Efficiency::mcEff) /
                   ReturnMCEffs(Mode::Bd2Dstpi, Neutral::pi0, Bachelor::pi,
                                Efficiency::mcEff)) *
                  (GlobalVars::Get(uniqueId_).kBF_Bu2Dst0rho().getVal() *
                   GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma().getVal()) /
                  (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
                   GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()),
          0., Systematic::NA, Sign::none)),
      // bkgFracFAV_Bu2Dst0hst_(Params::Get().CreateFloating(
      //     "bkgFracFAV_Bu2Dst0hst", uniqueId_, Neutral::pi0,
      //     (ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
      //                    Efficiency::orEff, false) /
      //      ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff,
      //                    false)) *
      //             (ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, Neutral::pi0,
      //                           Bachelor::pi, Efficiency::mcEff) /
      //              ReturnMCEffs(Mode::Bd2Dstpi, Neutral::pi0, Bachelor::pi,
      //                           Efficiency::mcEff)) *
      //             (GlobalVars::Get(uniqueId_).kBF_Bu2Dst0rho().getVal() *
      //              GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0().getVal()) /
      //             (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
      //              GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()) +
      //         (ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
      //                        Efficiency::orEff, false) /
      //          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff,
      //                        false)) *
      //             (ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, Neutral::pi0,
      //                           Bachelor::pi, Efficiency::mcEff) /
      //              ReturnMCEffs(Mode::Bd2Dstpi, Neutral::pi0, Bachelor::pi,
      //                           Efficiency::mcEff)) *
      //             (GlobalVars::Get(uniqueId_).kBF_Bu2Dst0rho().getVal() *
      //              GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma().getVal()) /
      //             (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
      //              GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()),
      //     0, 5)),
      bkgFracKK_Lb2Omegach_Lcpi0_(Params::Get().CreateFloating(
          "bkgFracKK_Lb2Omegach_Lcpi0", uniqueId_, Neutral::pi0, 0.1, 0, 5)),
      bkgFracADS_Bs2Dst0Kpi_(Params::Get().CreateFloating(
          "bkgFracADS_Bs2Dst0Kpi", uniqueId_, Neutral::pi0, 4, -2, 15)),
      // bkgFracADS_Bs2D0Kpi_(Params::Get().CreateFloating(
      //     "bkgFracADS_Bs2D0Kpi", uniqueId_, Neutral::pi0, 4, -2, 10)),
      bkgFracADS_Bs2D0Kpi_(Params::Get().CreateFixed(
          "bkgFracADS_Bs2D0Kpi", uniqueId_, Neutral::pi0,
          (ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, Efficiency::orEff,
                         false) /
           ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k, Efficiency::orEff,
                         false)) *
              (ReturnMCEffs(Mode::Bs2D0Kpi, Neutral::pi0, Bachelor::k,
                            Efficiency::mcEff) /
               ReturnMCEffs(Mode::Bs2Dst0Kpi, Neutral::pi0, Bachelor::k,
                            Efficiency::mcEff)),
          0., Systematic::NA, Sign::same)),
      constraint_bkgFracGlobal_WN_(("constraint_bkgFracGlobal_WN_" +
                                    ComposeName(uniqueId_, Neutral::pi0))
                                       .c_str(),
                                   "", *bkgFracGlobal_WN_, RooFit::RooConst(1),
                                   RooFit::RooConst(0.1)),
      constraint_bkgFracFAV_Bu2D0hst_(
          ("constraint_bkgFracFAV_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", *bkgFracFAV_Bu2D0hst_,
          RooFit::RooConst(ReadBkgFracs<Neutral::pi0>(Mode::Bu2D0rho, "val")),
          RooFit::RooConst(ReadBkgFracs<Neutral::pi0>(Mode::Bu2D0rho, "std"))),
      constraints_argSet_() {}
// constraints_argSet_(constraint_bkgFracGlobal_WN_) {}
// constraint_bkgFracFAV_Bu2D0hst_) {}
