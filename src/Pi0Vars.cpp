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
          "Bu2Dst0h_D0pi0_KpiSigmaDelta", uniqueId_, Neutral::pi0, 1.038649,
          0.031802, Systematic::pi0DeltaWidthRatio, Sign::same)),
      Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::same)),
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
      Bu2Dst0h_D0pi0_meanBu_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_meanBu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, 5270, 5280)),
      Bu2Dst0h_D0pi0_sigmaBu_(nullptr),
      Bu2Dst0h_D0pi0_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_KpiSigmaBu", uniqueId_, Neutral::pi0, 0.944180,
          0.013207, Systematic::pi0BuWidthRatio, Sign::same)),
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
      //     Mode::Bu2Dst0pi_D0pi0_WN, -5, 5)),
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
      // -------------------- Bu2Dst0h_D0pi0_FAVasSUP -------------------- //
      Bu2Dst0h_D0pi0_FAVasSUP_meanDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_meanDelta", uniqueId_, Neutral::pi0,
          1.4274e+02, 2.38e-01, Systematic::pi0FAVasSUPDeltaPdf, Sign::same)),
      Bu2Dst0h_D0pi0_FAVasSUP_sigma1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_sigma1Delta", uniqueId_, Neutral::pi0,
          2.7445e+00, 1.00, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_FAVasSUP_sigma2Delta_(nullptr),
      Bu2Dst0h_D0pi0_FAVasSUP_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_a1Delta", uniqueId_, Neutral::pi0,
          -1.0183e+00, 1.00, Systematic::NA, Sign::none)),
      Bu2Dst0h_D0pi0_FAVasSUP_a2Delta_(nullptr),
      Bu2Dst0h_D0pi0_FAVasSUP_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_n1Delta", uniqueId_, Neutral::pi0,
          1.1431e+00, 1.00, Systematic::NA, Sign::same)),
      Bu2Dst0h_D0pi0_FAVasSUP_n2Delta_(nullptr),
      pdf1Delta_Bu2Dst0h_D0pi0_FAVasSUP_(),
      pdf2Delta_Bu2Dst0h_D0pi0_FAVasSUP_(),
      Bu2Dst0h_D0pi0_FAVasSUP_fracPdf1Delta_(nullptr),
      pdfDelta_Bu2Dst0h_D0pi0_FAVasSUP_(
          new RooCBShape(("pdfDelta_Bu2Dst0h_D0pi0_FAVasSUP_" +
                          ComposeName(uniqueId_, Neutral::pi0))
                             .c_str(),
                         "", Configuration::Get().deltaMass(),
                         *Bu2Dst0h_D0pi0_FAVasSUP_meanDelta_,
                         *Bu2Dst0h_D0pi0_FAVasSUP_sigma1Delta_,
                         *Bu2Dst0h_D0pi0_FAVasSUP_a1Delta_,
                         *Bu2Dst0h_D0pi0_FAVasSUP_n1Delta_)),
      Bu2Dst0h_D0pi0_FAVasSUP_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_meanBu", uniqueId_, Neutral::pi0, 5.2723e+03,
          5.12e+00, Systematic::pi0FAVasSUPBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_FAVasSUP_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_sigmaBu", uniqueId_, Neutral::pi0,
          9.1079e+01, 4.14e+00, Systematic::pi0FAVasSUPBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_FAVasSUP_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_a1Bu", uniqueId_, Neutral::pi0, 1.7278e+00,
          4.38e-01, Systematic::pi0FAVasSUPBuPdf, Sign::none)),
      Bu2Dst0h_D0pi0_FAVasSUP_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_n1Bu", uniqueId_, Neutral::pi0, 1.0000e+01,
          1.00, Systematic::NA, Sign::same)),
      pdfBu_Bu2Dst0h_D0pi0_FAVasSUP_(
          ("pdfBu_Bu2Dst0h_D0pi0_FAVasSUP_" +
           ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0pi0_FAVasSUP_meanBu_, *Bu2Dst0h_D0pi0_FAVasSUP_sigmaBu_,
          *Bu2Dst0h_D0pi0_FAVasSUP_a1Bu_, *Bu2Dst0h_D0pi0_FAVasSUP_n1Bu_),
      Bu2Dst0h_D0pi0_FAVasSUP_meanBuPartial_(nullptr),
      Bu2Dst0h_D0pi0_FAVasSUP_sigmaBuPartial_(nullptr),
      Bu2Dst0h_D0pi0_FAVasSUP_a1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_FAVasSUP_n1BuPartial_(nullptr),
      pdfBuPartial_Bu2Dst0h_D0pi0_FAVasSUP_(),
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
      // -------------------- Bu2Dst0h_D0gamma_FAVasSUP -------------------- //
      Bu2Dst0h_D0gamma_FAVasSUP_meanDelta_(nullptr),
      Bu2Dst0h_D0gamma_FAVasSUP_sigmaDelta_(nullptr),
      Bu2Dst0h_D0gamma_FAVasSUP_a1Delta_(nullptr),
      Bu2Dst0h_D0gamma_FAVasSUP_a2Delta_(nullptr),
      Bu2Dst0h_D0gamma_FAVasSUP_n1Delta_(nullptr),
      Bu2Dst0h_D0gamma_FAVasSUP_n2Delta_(nullptr),
      pdf1Delta_Bu2Dst0h_D0gamma_FAVasSUP_(),
      pdf2Delta_Bu2Dst0h_D0gamma_FAVasSUP_(),
      Bu2Dst0h_D0gamma_FAVasSUP_fracPdf1Delta_(nullptr),
      pdfDelta_Bu2Dst0h_D0gamma_FAVasSUP_(),
      Bu2Dst0h_D0gamma_FAVasSUP_meanBu_(nullptr),
      Bu2Dst0h_D0gamma_FAVasSUP_sigmaBu_(nullptr),
      Bu2Dst0h_D0gamma_FAVasSUP_a1Bu_(nullptr),
      Bu2Dst0h_D0gamma_FAVasSUP_n1Bu_(nullptr),
      pdfBu_Bu2Dst0h_D0gamma_FAVasSUP_(),
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
      //     "Bd2Dsth_aDelta", uniqueId_, Neutral::pi0, Mode::Bd2Dstpi, -5, 5)),
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
      pdfDelta_Bu2D0hst_(
          ("pdfDelta_Bu2D0hst_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", Configuration::Get().deltaMass(), *Bu2D0hst_thresholdDelta_,
          *Bu2D0hst_cDelta_, *Bu2D0hst_aDelta_, *Bu2D0hst_bDelta_),
      Bu2D0hst_mean1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_mean1Bu", uniqueId_, Neutral::pi0, Mode::Bu2D0rho,
          Systematic::Bu2D0hstBuPdf, Sign::same)),
      // Bu2D0hst_mean1Bu_(Params::Get().CreateFloating(
      //     "Bu2D0hst_mean1Bu", uniqueId_, Neutral::pi0, Mode::Bu2D0rho,
      //     5235, 5255)),
      Bu2D0hst_meanOffset21Bu_(nullptr),
      Bu2D0hst_mean2Bu_(),
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
      Bu2Dst0hst_D0gamma_mean1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_mean1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gammaBuPdf,
          Sign::same)),
      Bu2Dst0hst_D0gamma_meanOffset21Bu_(nullptr),
      Bu2Dst0hst_D0gamma_mean2Bu_(),
      Bu2Dst0hst_D0gamma_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_KpiSigmaBu", uniqueId_, Neutral::pi0, 1.0, 0.05,
          Systematic::Bu2Dst0hst_D0gammaBuPdf, Sign::same)),
      Bu2Dst0hst_D0gamma_sigmaRatio21Bu_(nullptr),
      Bu2Dst0hst_D0gamma_a1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_n1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_a2Bu_(nullptr),
      Bu2Dst0hst_D0gamma_n2Bu_(nullptr),
      Bu2Dst0hst_D0gamma_fracPdf1Bu_(nullptr),
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
      // -------------------- MIS-REC -------------------- //
      MisRec_thresholdDelta_(Params::Get().CreateFixed(
          "MisRec_thresholdDelta", uniqueId_, Neutral::pi0, 1.3549e+02, 1e-01,
          Systematic::NA, Sign::same)),
      MisRec_aDelta_(Params::Get().CreateFloating(
          "MisRec_aDelta", uniqueId_, Neutral::pi0, -1.5314e+00, -5, 5)),
      MisRec_bDelta_(Params::Get().CreateFixed(
          "MisRec_bDelta", uniqueId_, Neutral::pi0, -7.4912e-03, 7.87e-02,
          Systematic::misRecDeltaPdf, Sign::none)),
      MisRec_cDelta_(Params::Get().CreateFixed(
          "MisRec_cDelta", uniqueId_, Neutral::pi0, 2.1012e+00, 8.82e-02,
          Systematic::misRecDeltaPdf, Sign::same)),
      pdfDelta_MisRec_(
          ("pdfDelta_MisRec_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", Configuration::Get().deltaMass(), *MisRec_thresholdDelta_,
          *MisRec_cDelta_, *MisRec_aDelta_, *MisRec_bDelta_),
      pdfDelta_misId_MisRec_(
          ("pdfDelta_misId_MisRec_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), *MisRec_thresholdDelta_,
          *MisRec_cDelta_, *MisRec_aDelta_, *MisRec_bDelta_),
      MisRec_meanBu_(Params::Get().CreateFixed(
          "MisRec_meanBu", uniqueId_, Neutral::pi0, 5.2759e+03, 1.04e+00,
          Systematic::misRecBuPdf, Sign::same)),
      // MisRec_meanBu_(Params::Get().CreateFloating(
      //     "MisRec_meanBu", uniqueId_, Neutral::pi0, 5.2759e+03, 5250, 5290)),
      MisRec_aLBu_(Params::Get().CreateFixed(
          "MisRec_aLBu", uniqueId_, Neutral::pi0, 8.7522e-06, 2.86e-02,
          Systematic::misRecBuPdf, Sign::same)),
      // MisRec_aLBu_(Params::Get().CreateFloating(
      //     "MisRec_aLBu", uniqueId_, Neutral::pi0, 8.7522e-06, 0, 5)),
      MisRec_aRBu_(Params::Get().CreateFixed(
          "MisRec_aRBu", uniqueId_, Neutral::pi0, 1.6777e-07, 5.25e-03,
          Systematic::misRecBuPdf, Sign::same)),
      // MisRec_aRBu_(Params::Get().CreateFloating(
      //     "MisRec_aRBu", uniqueId_, Neutral::pi0, 1.6777e-07, 0, 5)),
      MisRec_meanBuPartial_(nullptr),
      MisRec_aLBuPartial_(nullptr),
      MisRec_aRBuPartial_(nullptr),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_thresholdDelta_(
          ("Bu2D0h_thresholdDelta_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", 1.3362e+02),
      Bu2D0h_aDelta_(
          ("Bu2D0h_aDelta_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(), "",
          -6.1787e-01),
      Bu2D0h_bDelta_(
          ("Bu2D0h_bDelta_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(), "",
          9.9982e-01),
      Bu2D0h_cDelta_(
          ("Bu2D0h_cDelta_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(), "",
          3.3662e+00),
      pdfDelta_Bu2D0h_(
          ("pdfDelta_Bu2D0h_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", Configuration::Get().deltaMass(), Bu2D0h_thresholdDelta_,
          Bu2D0h_cDelta_, Bu2D0h_aDelta_, Bu2D0h_bDelta_),
      pdfDelta_misId_Bu2D0h_(
          ("pdfDelta_misId_Bu2D0h_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), Bu2D0h_thresholdDelta_,
          Bu2D0h_cDelta_, Bu2D0h_aDelta_, Bu2D0h_bDelta_),
      Bu2D0h_meanBu_(
          ("Bu2D0h_meanBu_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(), "",
          // 5.4893e+03, 5450, 5500),
          // Fixed from data
          // 5.4875e+03),
          // Fixed from data
          5500),
      Bu2D0h_aLBu_(
          ("Bu2D0h_aLBu_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(), "",
          1.3673e-01),
      Bu2D0h_aRBu_(
          ("Bu2D0h_aRBu_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(), "",
          // 5.0076e-08, 0, 5),
          // Fixed from data
          // 1.3901e-01),
          // Fixed from data
          1.5969e-01),
      Bu2D0h_meanBuPartial_(),
      Bu2D0h_aLBuPartial_(),
      Bu2D0h_aRBuPartial_(),
      // -------------------- PART REC -------------------- //
      PartRec_thresholdDelta_(Params::Get().CreateFixed(
          "PartRec_thresholdDelta", uniqueId_, Neutral::pi0, 1.3596e+02,
          7.15e-01, Systematic::partRecDeltaPdf, Sign::same)),
      PartRec_aDelta_(Params::Get().CreateFixed(
          "PartRec_aDelta", uniqueId_, Neutral::pi0, -4.1649e-01, 2.85e-01,
          Systematic::partRecDeltaPdf, Sign::none)),
      PartRec_bDelta_(Params::Get().CreateFixed(
          "PartRec_bDelta", uniqueId_, Neutral::pi0, -9.9944e-01, 1.22e+00,
          Systematic::partRecDeltaPdf, Sign::none)),
      PartRec_cDelta_(Params::Get().CreateFixed(
          "PartRec_cDelta", uniqueId_, Neutral::pi0, 2.1081e+00, 1.39e+00,
          Systematic::partRecDeltaPdf, Sign::same)),
      pdfDelta_PartRec_(
          ("pdfDelta_PartRec_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", Configuration::Get().deltaMass(), *PartRec_thresholdDelta_,
          *PartRec_cDelta_, *PartRec_aDelta_, *PartRec_bDelta_),
      pdfDelta_misId_PartRec_(
          ("pdfDelta_misId_PartRec_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), *PartRec_thresholdDelta_,
          *PartRec_cDelta_, *PartRec_aDelta_, *PartRec_bDelta_),
      PartRec_D0pi0_meanBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_meanBu", uniqueId_, Neutral::pi0, 5.1332e+03, 1.91e+00,
          Systematic::partRecBuPdf, Sign::same)),
      PartRec_D0pi0_aLBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_aLBu", uniqueId_, Neutral::pi0, 4.7967e-07, 7.49e-02,
          Systematic::partRecBuPdf, Sign::same)),
      PartRec_D0pi0_aRBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_aRBu", uniqueId_, Neutral::pi0, 1.7013e-07, 3.08e+00,
          Systematic::partRecBuPdf, Sign::same)),
      PartRec_D0gamma_meanBu_(nullptr),
      PartRec_D0gamma_aLBu_(nullptr),
      PartRec_D0gamma_aRBu_(nullptr),
      PartRec_meanBuPartial_(nullptr),
      PartRec_aLBuPartial_(nullptr),
      PartRec_aRBuPartial_(nullptr),
      // ------------- Expected yields and relative fractions w.r.t. sig
      // -------------//
      fracBu2Dst0h_D0pi0_(),
      initYieldFAVBu2Dst0h_D0pi0_(
          initYieldFAVBu2Dst0h_D0pi0_ =
              Configuration::Get().initYieldFAVSignal()),
      fracBu2Dst0h_D0gamma_(0.213),
      initYieldFAVBu2Dst0h_D0gamma_(Configuration::Get().initYieldFAVSignal() *
                                    fracBu2Dst0h_D0gamma_),
      fracMisRec_Bu2Dst0h_D0gamma_(0.213),
      fracMisRec_Bu2Dst0h_D0gamma_WN_(0.481),
      fracMisRec_Bu2Dst0h_D0pi0_WN_(2.722),
      fracMisRec_Bu2D0hst_(1.083),
      fracMisRec_Bd2Dsth_(0.491),
      fracMisRec_(fracMisRec_Bu2Dst0h_D0gamma_WN_ +
                  fracMisRec_Bu2Dst0h_D0pi0_WN_ + fracMisRec_Bu2D0hst_ +
                  fracMisRec_Bd2Dsth_ + fracMisRec_Bu2Dst0h_D0gamma_),
      initYieldFAVMisRec_(Configuration::Get().initYieldFAVSignal() *
                          fracMisRec_ / 2),
      fracBu2D0h_(1.363),
      initYieldFAVBu2D0h_(Configuration::Get().initYieldFAVSignal() *
                          fracBu2D0h_),
      fracPartRec_Bu2Dst0hst_D0pi0_(),
      fracPartRec_Bu2Dst0hst_D0gamma_(),
      fracPartRec_(0.290),
      initYieldFAVPartRec_(Configuration::Get().initYieldFAVSignal() *
                           fracPartRec_),
      // -------------------- Bkg Fractions -------------------- //
      bkgFracGlobal_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFloating(
          "bkgFracGlobal_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::pi0,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff) /
              ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::pi0, Bachelor::pi,
                           Efficiency::mcEff),
          -5, 5)),
      // bkgFracGlobal_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
      //     "bkgFracGlobal_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::pi0,
      //     ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, Neutral::pi0, Bachelor::pi,
      //                  Efficiency::mcEff) /
      //         ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::pi0, Bachelor::pi,
      //                      Efficiency::mcEff),
      //     0.0, Systematic::NA, Sign::same)),
      // No global frac for gamma mode in π0: different physics
      bkgFracGlobal_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFloating(
          "bkgFracGlobal_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::pi0,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff) /
              ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::pi0, Bachelor::pi,
                           Efficiency::mcEff) *
              GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0().getVal(),
          -5, 5)),
      bkgFracFAV_Bd2Dsth_(Params::Get().CreateFloating(
          "bkgFracFAV_Bd2Dsth", uniqueId_, Neutral::pi0,
          ReturnMCEffs(Mode::Bd2Dstpi, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff) /
              ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::pi0, Bachelor::pi,
                           Efficiency::mcEff) *
              (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
               GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()) /
              (GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal() *
               GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0().getVal()),
          -5, 5)),
      // bkgFracFAV_Bd2Dsth_(Params::Get().CreateFixed(
      //     "bkgFracFAV_Bd2Dsth", uniqueId_, Neutral::pi0,
      //     ReturnMCEffs(Mode::Bd2Dstpi, Neutral::pi0, Bachelor::pi,
      //                  Efficiency::mcEff) /
      //         ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::pi0, Bachelor::pi,
      //                      Efficiency::mcEff) *
      //         (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
      //          GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()) /
      //         (GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal() *
      //          GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0().getVal()),
      //     0.0, Systematic::NA, Sign::same)),
      // bkgFracFAV_Bu2D0hst_(Params::Get().CreateFloating(
      //     "bkgFracFAV_Bu2D0hst", uniqueId_, Neutral::pi0,
      //     ReturnMCEffs(Mode::Bu2D0rho, Neutral::pi0, Bachelor::pi,
      //                  Efficiency::mcEff) /
      //         ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::pi0, Bachelor::pi,
      //                      Efficiency::mcEff) *
      //         GlobalVars::Get(uniqueId_).kBF_Bu2D0rho().getVal() /
      //         (GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal() *
      //          GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0().getVal()),
      //     -5, 5)),
      bkgFracFAV_Bu2D0hst_(Params::Get().CreateFixed(
          "bkgFracFAV_Bu2D0hst", uniqueId_, Neutral::pi0,
          ReturnMCEffs(Mode::Bu2D0rho, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff) /
              ReturnMCEffs(Mode::Bd2Dstpi, Neutral::pi0, Bachelor::pi,
                           Efficiency::mcEff) *
              GlobalVars::Get(uniqueId_).kBF_Bu2D0rho().getVal() /
              (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
               GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()),
          0.0, Systematic::NA, Sign::same)),
      bkgFracFAV_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "bkgFracFAV_Bu2Dst0hst_D0pi0", uniqueId_, Neutral::pi0,
          ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff) /
              ReturnMCEffs(Mode::Bd2Dstpi, Neutral::pi0, Bachelor::pi,
                           Efficiency::mcEff) *
              (GlobalVars::Get(uniqueId_).kBF_Bu2Dst0rho().getVal() *
               GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0().getVal()) /
              (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
               GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()),
          0.0, Systematic::NA, Sign::same)),
      // Don't use: fix yield w.r.t. π0 mode in NBDVars
      bkgFracFAV_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "bkgFracFAV_Bu2Dst0hst_D0gamma", uniqueId_, Neutral::pi0,
          ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff) /
              ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, Neutral::pi0, Bachelor::pi,
                           Efficiency::mcEff) *
              GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0().getVal(),
          0.0, Systematic::NA, Sign::same)),
      constraint_bkgFracGlobal_Bu2Dst0h_D0pi0_WN_(
          ("constraint_bkgFracGlobal_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", *bkgFracGlobal_Bu2Dst0h_D0pi0_WN_,
          RooFit::RooConst(ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, Neutral::pi0,
                                        Bachelor::pi, Efficiency::mcEff) /
                           ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::pi0,
                                        Bachelor::pi, Efficiency::mcEff)),
          RooFit::RooConst(ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, Neutral::pi0,
                                        Bachelor::pi, Efficiency::mcEffErr))),
      constraint_bkgFracGlobal_Bu2Dst0h_D0gamma_WN_(
          ("constraint_bkgFracGlobal_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", *bkgFracGlobal_Bu2Dst0h_D0gamma_WN_,
          RooFit::RooConst(
              ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN, Neutral::pi0,
                           Bachelor::pi, Efficiency::mcEff) /
              ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::pi0, Bachelor::pi,
                           Efficiency::mcEff) *
              GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0().getVal()),
          RooFit::RooConst(ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN,
                                        Neutral::pi0, Bachelor::pi,
                                        Efficiency::mcEffErr))),
      constraint_bkgFracFAV_Bd2Dsth_(
          ("constraint_bkgFracFAV_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", *bkgFracFAV_Bd2Dsth_,
          RooFit::RooConst(
              ReturnMCEffs(Mode::Bd2Dstpi, Neutral::pi0, Bachelor::pi,
                           Efficiency::mcEff) /
              ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::pi0, Bachelor::pi,
                           Efficiency::mcEff) *
              (GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi().getVal() *
               GlobalVars::Get(uniqueId_).kBF_Dst2D0pi().getVal()) /
              (GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal() *
               GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0().getVal())),
          RooFit::RooConst(ReturnMCEffs(Mode::Bd2Dstpi, Neutral::pi0,
                                        Bachelor::pi, Efficiency::mcEffErr))),
      constraint_bkgFracFAV_Bu2D0hst_(),
      constraints_argSet_(constraint_bkgFracGlobal_Bu2Dst0h_D0pi0_WN_,
                          constraint_bkgFracGlobal_Bu2Dst0h_D0gamma_WN_) {}
// constraints_argSet_(constraint_bkgFracGlobal_Bu2Dst0h_D0pi0_WN_,
//                     constraint_bkgFracFAV_Bd2Dsth_) {}
