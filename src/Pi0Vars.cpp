#include "GlobalVars.h"
#include "NeutralVars.h"
#include "Params.h"

// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::pi0>::NeutralVars(int uniqueId)
    : uniqueId_(uniqueId),
      A_Kpi_(Params::Get().CreateFixed("A_Kpi", uniqueId_, Neutral::pi0,
                                       -1.16e-02, 1.6e-03, Systematic::A_Kpi,
                                       Sign::none)),
      a_Kpi_(MakeLittleAsym(
          ("a_Kpi_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(), *A_Kpi_)),
      // -------------------- PDF SHAPES -------------------- //
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      Bu2Dst0h_D0pi0_meanDelta_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_meanDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, 138, 146)),
      Bu2Dst0h_D0pi0_KpiSigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_KpiSigmaDelta", uniqueId_, Neutral::pi0, 1.0167e+00,
          4.10e-02, Systematic::Bu2Dst0h_D0pi0_PdfDelta_SigmaRatioKpi,
          Sign::same)),
      // Bu2Dst0h_D0pi0_KpiSigmaDelta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_KpiSigmaDelta", uniqueId_, Neutral::pi0, 1.038649,
      //     0.9, 1.1)),
      // Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfDelta_Tails,
      //     Sign::same)),
      Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::pi0, 7.2821e-01,
          5.31e-02, Systematic::Bu2Dst0h_D0pi0_PdfDelta_Tails, Sign::same)),
      // Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0, 0, 5)),
      Bu2Dst0h_D0pi0_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfDelta_Tails,
          Sign::same)),
      // Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_a2Delta", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfDelta_Tails,
      //     Sign::same)),
      Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2Delta", uniqueId_, Neutral::pi0, -7.5087e-01,
          1.77e-02, Systematic::Bu2Dst0h_D0pi0_PdfDelta_Tails, Sign::same)),
      // Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_a2Delta", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0, -5, -0.000001)),
      Bu2Dst0h_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfDelta_Tails,
          Sign::same)),
      Bu2Dst0h_D0pi0_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf1Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfDelta_Frac,
          Sign::same)),
      Bu2Dst0h_D0pi0_mean1Bu_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_mean1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, 5270, 5280)),
      Bu2Dst0h_D0pi0_meanOffset21Bu_(nullptr),
      Bu2Dst0h_D0pi0_mean2Bu_(),
      Bu2Dst0h_D0pi0_sigmaRatio21Bu_(nullptr),
      Bu2Dst0h_D0pi0_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_KpiSigmaBu", uniqueId_, Neutral::pi0, 9.4326e-01,
          3.16e-02, Systematic::Bu2Dst0h_D0pi0_PdfBu_SigmaRatioKpi,
          Sign::same)),
      // Bu2Dst0h_D0pi0_KpiSigmaBu_(
      //     Params::Get().CreateFloating("Bu2Dst0h_D0pi0_KpiSigmaBu",
      //     uniqueId_,
      //                                  Neutral::pi0, 0.944180, 0.9, 1.1)),
      // Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_a1Bu", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfBu_Tails,
      //     Sign::same)),
      Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Bu", uniqueId_, Neutral::pi0, 1.4577e+00, 7.65e-02,
          Systematic::Bu2Dst0h_D0pi0_PdfBu_Tails, Sign::same)),
      // Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_a1Bu", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0, 0, 5)),
      Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Bu", uniqueId_, Neutral::pi0, Mode::Bu2Dst0pi_D0pi0,
          Systematic::Bu2Dst0h_D0pi0_PdfBu_Tails, Sign::same)),
      // Bu2Dst0h_D0pi0_a2Bu_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_a2Bu", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfBu_Tails,
      //     Sign::same)),
      Bu2Dst0h_D0pi0_a2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2Bu", uniqueId_, Neutral::pi0, -1.3131e+00, 4.27e-02,
          Systematic::Bu2Dst0h_D0pi0_PdfBu_Tails, Sign::same)),
      // Bu2Dst0h_D0pi0_a2Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_a2Bu", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0, -5, -0.00001)),
      Bu2Dst0h_D0pi0_n2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2Bu", uniqueId_, Neutral::pi0, Mode::Bu2Dst0pi_D0pi0,
          Systematic::Bu2Dst0h_D0pi0_PdfBu_Tails, Sign::same)),
      Bu2Dst0h_D0pi0_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfBu_Frac,
          Sign::same)),
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
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfDelta,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_cDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_cDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfDelta,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_mean1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_mean1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBu,
          Sign::same)),
      // Bu2Dst0h_D0pi0_WN_mean1Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_mean1Bu", uniqueId_, Neutral::pi0,
      //     Mode::Bu2Dst0pi_D0pi0_WN, 5260, 5280)),
      Bu2Dst0h_D0pi0_WN_meanOffset21Bu_(nullptr),
      Bu2Dst0h_D0pi0_WN_mean2Bu_(),
      Bu2Dst0h_D0pi0_WN_sigmaRatio21Bu_(nullptr),
      Bu2Dst0h_D0pi0_WN_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_KpiSigmaBu", uniqueId_, Neutral::pi0, 1.0, 0.05,
          Systematic::Bu2Dst0h_D0pi0_WN_PdfBu, Sign::same)),
      Bu2Dst0h_D0pi0_WN_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_a1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBu,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_n1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBu,
          Sign::same)),
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
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfDelta,
          Sign::same)),
      Bu2Dst0h_D0gamma_WN_aDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_aDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfDelta,
          Sign::none)),
      Bu2Dst0h_D0gamma_WN_bDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_bDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfDelta,
          Sign::none)),
      Bu2Dst0h_D0gamma_WN_cDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_cDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfDelta,
          Sign::same)),
      pdfDelta_Bu2Dst0h_D0gamma_WN_(new RooDstD0BG(
          ("pdfDelta_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0gamma_WN_thresholdDelta_, *Bu2Dst0h_D0gamma_WN_cDelta_,
          *Bu2Dst0h_D0gamma_WN_aDelta_, *Bu2Dst0h_D0gamma_WN_bDelta_)),
      Bu2Dst0h_D0gamma_WN_mean1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_mean1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfBu,
          Sign::same)),
      Bu2Dst0h_D0gamma_WN_meanOffset21Bu_(nullptr),
      Bu2Dst0h_D0gamma_WN_mean2Bu_(),
      Bu2Dst0h_D0gamma_WN_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_KpiSigmaBu", uniqueId_, Neutral::pi0, 1.0, 0.05,
          Systematic::Bu2Dst0h_D0gamma_WN_PdfBu, Sign::same)),
      Bu2Dst0h_D0gamma_WN_sigmaRatio21Bu_(nullptr),
      Bu2Dst0h_D0gamma_WN_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_a1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfBu,
          Sign::same)),
      Bu2Dst0h_D0gamma_WN_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_n1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bu2Dst0h_D0gamma_WN_PdfBu,
          Sign::same)),
      Bu2Dst0h_D0gamma_WN_fracPdf1Bu_(nullptr),
      Bu2Dst0h_D0gamma_WN_meanBuPartial_(nullptr),
      Bu2Dst0h_D0gamma_WN_KpiSigmaBuPartial_(nullptr),
      // -------------------- Bu2Dst0h_WN -------------------- //
      Bu2Dst0h_WN_floatingFracD0pi0_(Params::Get().CreateFloating(
          "Bu2Dst0h_WN_floatingFracD0pi0", uniqueId_, Neutral::pi0, 1, -1, 2)),
      // -------------------- Bd2Dsth -------------------- //
      Bd2Dsth_thresholdDelta_(Params::Get().CreateFixed(
          "Bd2Dsth_thresholdDelta", uniqueId_, Neutral::pi0, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfDelta, Sign::same)),
      Bd2Dsth_aDelta_(Params::Get().CreateFixed(
          "Bd2Dsth_aDelta", uniqueId_, Neutral::pi0, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfDelta, Sign::none)),
      Bd2Dsth_bDelta_(Params::Get().CreateFixed(
          "Bd2Dsth_bDelta", uniqueId_, Neutral::pi0, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfDelta, Sign::none)),
      Bd2Dsth_cDelta_(Params::Get().CreateFixed(
          "Bd2Dsth_cDelta", uniqueId_, Neutral::pi0, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfDelta, Sign::same)),
      pdfDelta_Bd2Dsth_(
          ("pdfDelta_Bd2Dsth_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", Configuration::Get().deltaMass(), *Bd2Dsth_thresholdDelta_,
          *Bd2Dsth_cDelta_, *Bd2Dsth_aDelta_, *Bd2Dsth_bDelta_),
      Bd2Dsth_mean1Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_mean1Bu", uniqueId_, Neutral::pi0, Mode::Bd2Dstpi,
          Systematic::Bd2Dsth_PdfBu, Sign::same)),
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
          Systematic::Bd2Dsth_PdfBu, Sign::same)),
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
          Systematic::Bu2D0hst_PdfDelta, Sign::same)),
      Bu2D0hst_aDelta_(Params::Get().CreateFixed(
          "Bu2D0hst_aDelta", uniqueId_, Neutral::pi0, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfDelta, Sign::none)),
      Bu2D0hst_bDelta_(Params::Get().CreateFixed(
          "Bu2D0hst_bDelta", uniqueId_, Neutral::pi0, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfDelta, Sign::none)),
      Bu2D0hst_cDelta_(Params::Get().CreateFixed(
          "Bu2D0hst_cDelta", uniqueId_, Neutral::pi0, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfDelta, Sign::same)),
      pdfDelta_Bu2D0hst_(new RooDstD0BG(
          ("pdfDelta_Bu2D0hst_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", Configuration::Get().deltaMass(), *Bu2D0hst_thresholdDelta_,
          *Bu2D0hst_cDelta_, *Bu2D0hst_aDelta_, *Bu2D0hst_bDelta_)),
      Bu2D0hst_mean1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_mean1Bu", uniqueId_, Neutral::pi0, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfBu, Sign::same)),
      Bu2D0hst_meanOffset21Bu_(nullptr),
      Bu2D0hst_mean2Bu_(),
      Bu2D0hst_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2D0hst_KpiSigmaBu", uniqueId_, Neutral::pi0, 1.0, 0.05,
          Systematic::Bu2D0hst_PdfBu, Sign::same)),
      Bu2D0hst_sigmaRatio21Bu_(nullptr),
      Bu2D0hst_a1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_a1Bu", uniqueId_, Neutral::pi0, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfBu, Sign::none)),
      Bu2D0hst_n1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_n1Bu", uniqueId_, Neutral::pi0, Mode::Bu2D0rho,
          Systematic::Bu2D0hst_PdfBu, Sign::same)),
      Bu2D0hst_fracPdf1Bu_(nullptr),
      Bu2D0hst_meanBuPartial_(nullptr),
      Bu2D0hst_KpiSigmaBuPartial_(nullptr),
      // -------------------- Bu2Dst0hst_D0gamma -------------------- //
      Bu2Dst0hst_D0gamma_meanDelta_(nullptr),
      Bu2Dst0hst_D0gamma_sigmaDelta_(nullptr),
      pdfDelta_Bu2Dst0hst_D0gamma_(),
      Bu2Dst0hst_D0gamma_mean1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_meanOffset21Bu_(nullptr),
      Bu2Dst0hst_D0gamma_mean2Bu_(),
      Bu2Dst0hst_D0gamma_KpiSigmaBu_(nullptr),
      Bu2Dst0hst_D0gamma_sigmaRatio21Bu_(nullptr),
      Bu2Dst0hst_D0gamma_a1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_n1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_a2Bu_(nullptr),
      Bu2Dst0hst_D0gamma_n2Bu_(nullptr),
      Bu2Dst0hst_D0gamma_fracPdf1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_meanBuPartial_(nullptr),
      Bu2Dst0hst_D0gamma_KpiSigmaBuPartial_(nullptr),
      // -------------------- Bu2Dst0hst_D0pi0 -------------------- //
      Bu2Dst0hst_D0pi0_meanDelta_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_meanDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0rho_D0pi0, Systematic::Bu2Dst0hst_D0pi0_PdfDelta,
          Sign::same)),
      Bu2Dst0hst_D0pi0_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_sigmaDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0rho_D0pi0, Systematic::Bu2Dst0hst_D0pi0_PdfDelta,
          Sign::same)),
      pdfDelta_Bu2Dst0hst_D0pi0_(),
      Bu2Dst0hst_D0pi0_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_meanBu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0rho_D0pi0, Systematic::Bu2Dst0hst_D0pi0_PdfBu,
          Sign::same)),
      Bu2Dst0hst_D0pi0_KpiSigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_KpiSigmaBu", uniqueId_, Neutral::pi0, 1.0, 0.05,
          Systematic::Bu2Dst0hst_D0pi0_PdfBu, Sign::same)),
      Bu2Dst0hst_D0pi0_meanBuPartial_(nullptr),
      Bu2Dst0hst_D0pi0_KpiSigmaBuPartial_(nullptr),
      // -------------------- Bu2Dst0hst -------------------- //
      // Bu2Dst0hst_floatingFracD0pi0_(nullptr),
      // -------------------- Lb2Omegach_Lcpi0 -------------------- //
      Lb2Omegach_Lcpi0_thresholdDelta_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_thresholdDelta", uniqueId_, Neutral::pi0,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfDelta,
          Sign::same)),
      Lb2Omegach_Lcpi0_aDelta_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_aDelta", uniqueId_, Neutral::pi0,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfDelta,
          Sign::none)),
      Lb2Omegach_Lcpi0_bDelta_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_bDelta", uniqueId_, Neutral::pi0,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfDelta,
          Sign::none)),
      Lb2Omegach_Lcpi0_cDelta_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_cDelta", uniqueId_, Neutral::pi0,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfDelta,
          Sign::same)),
      pdfDelta_Lb2Omegach_Lcpi0_(
          ("pdfDelta_Lb2Omegach_Lcpi0_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Lb2Omegach_Lcpi0_thresholdDelta_, *Lb2Omegach_Lcpi0_cDelta_,
          *Lb2Omegach_Lcpi0_aDelta_, *Lb2Omegach_Lcpi0_bDelta_),
      Lb2Omegach_Lcpi0_meanBu_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_meanBu", uniqueId_, Neutral::pi0,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfBu,
          Sign::same)),
      Lb2Omegach_Lcpi0_sigmaBu_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_sigmaBu", uniqueId_, Neutral::pi0,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfBu,
          Sign::same)),
      Lb2Omegach_Lcpi0_a1Bu_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_a1Bu", uniqueId_, Neutral::pi0,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfBu,
          Sign::none)),
      Lb2Omegach_Lcpi0_n1Bu_(Params::Get().CreateFixed(
          "Lb2Omegach_Lcpi0_n1Bu", uniqueId_, Neutral::pi0,
          Mode::Lb2Omegacpi_Lcpi0, Systematic::Lb2Omegach_Lcpi0_PdfBu,
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
          Systematic::boxEffs_Bkg, Sign::same)),
      deltaEffLb2Omegach_Lcpi0_(Params::Get().CreateFixed(
          "deltaEffLb2Omegach_Lcpi0_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      buEffLb2Omegach_Lcpi0_(Params::Get().CreateFixed(
          "buEffLb2Omegach_Lcpi0_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Lb2Omegacpi_Lcpi0, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_Bkg, Sign::same)),
      buPartialEffLb2Omegach_Lcpi0_(nullptr),
      // -------------------- Bs2D0Kst0 -------------------- //
      Bs2D0Kst0_thresholdDelta_(Params::Get().CreateFixed(
          "Bs2D0Kst0_thresholdDelta", uniqueId_, Neutral::pi0, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfDelta, Sign::same)),
      Bs2D0Kst0_aDelta_(Params::Get().CreateFixed(
          "Bs2D0Kst0_aDelta", uniqueId_, Neutral::pi0, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfDelta, Sign::none)),
      Bs2D0Kst0_bDelta_(Params::Get().CreateFixed(
          "Bs2D0Kst0_bDelta", uniqueId_, Neutral::pi0, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfDelta, Sign::none)),
      Bs2D0Kst0_cDelta_(Params::Get().CreateFixed(
          "Bs2D0Kst0_cDelta", uniqueId_, Neutral::pi0, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfDelta, Sign::same)),
      pdfDelta_Bs2D0Kst0_(
          ("pdfDelta_Bs2D0Kst0_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2D0Kst0_thresholdDelta_,
          *Bs2D0Kst0_cDelta_, *Bs2D0Kst0_aDelta_, *Bs2D0Kst0_bDelta_),
      Bs2D0Kst0_meanBu_(Params::Get().CreateFixed(
          "Bs2D0Kst0_meanBu", uniqueId_, Neutral::pi0, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfBu, Sign::same)),
      Bs2D0Kst0_sigmaBu_(Params::Get().CreateFixed(
          "Bs2D0Kst0_sigmaBu", uniqueId_, Neutral::pi0, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfBu, Sign::same)),
      Bs2D0Kst0_a1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kst0_a1Bu", uniqueId_, Neutral::pi0, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfBu, Sign::none)),
      Bs2D0Kst0_n1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kst0_n1Bu", uniqueId_, Neutral::pi0, Mode::Bs2D0Kst0,
          Systematic::Bs2D0Kst0_PdfBu, Sign::same)),
      pdfBu_Bs2D0Kst0_(
          ("pdfBu_Bs2D0Kst0_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2D0Kst0_meanBu_,
          *Bs2D0Kst0_sigmaBu_, *Bs2D0Kst0_a1Bu_, *Bs2D0Kst0_n1Bu_),
      Bs2D0Kst0_meanBuPartial_(nullptr),
      Bs2D0Kst0_sigmaBuPartial_(nullptr),
      Bs2D0Kst0_a1BuPartial_(nullptr),
      Bs2D0Kst0_n1BuPartial_(nullptr),
      pdfBuPartial_Bs2D0Kst0_(),
      mcEff_Bs2D0Kst0_(Params::Get().CreateFixed(
          "mcEff_Bs2D0Kst0", uniqueId_, Neutral::pi0,
          ReturnMCEffs(Mode::Bs2D0Kst0, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bs2D0Kst0, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg, Sign::same)),
      orEffBs2D0Kst0_(Params::Get().CreateFixed(
          "orEffBs2D0Kst0_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2D0Kst0, Bachelor::k, Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bs2D0Kst0, Bachelor::k, Efficiency::orEffErr,
                        false),
          Systematic::boxEffs_Bs2D0Kst0, Sign::same)),
      deltaEffBs2D0Kst0_(Params::Get().CreateFixed(
          "deltaEffBs2D0Kst0_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2D0Kst0, Bachelor::k, Efficiency::deltaEff,
                        false),
          ReturnBoxEffs(Mode::Bs2D0Kst0, Bachelor::k, Efficiency::deltaEffErr,
                        false),
          Systematic::boxEffs_Bs2D0Kst0, Sign::same)),
      buEffBs2D0Kst0_(Params::Get().CreateFixed(
          "buEffBs2D0Kst0_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2D0Kst0, Bachelor::k, Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bs2D0Kst0, Bachelor::k, Efficiency::buEffErr,
                        false),
          Systematic::boxEffs_Bs2D0Kst0, Sign::same)),
      buPartialEffBs2D0Kst0_(nullptr),
      // -------------------- Bs2Dst0Kst0_D0pi0 -------------------- //
      Bs2Dst0Kst0_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_a1Delta", uniqueId_, Neutral::pi0, 7.2821e-01,
          5.31e-02, Systematic::Bs2Dst0Kst0_PdfDelta, Sign::same)),
      Bs2Dst0Kst0_D0pi0_n1Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_n1Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bs2Dst0Kst0_PdfDelta, Sign::same)),
      Bs2Dst0Kst0_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_a2Delta", uniqueId_, Neutral::pi0, -7.5087e-01,
          1.77e-02, Systematic::Bs2Dst0Kst0_PdfDelta, Sign::same)),
      Bs2Dst0Kst0_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_n2Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bs2Dst0Kst0_PdfDelta, Sign::same)),
      Bs2Dst0Kst0_D0pi0_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_fracPdf1Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bs2Dst0Kst0_PdfDelta, Sign::same)),
      Bs2Dst0Kst0_D0pi0_mean1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_mean1Bu", uniqueId_, Neutral::pi0,
          Mode::Bs2Dst0Kst0_D0pi0, Systematic::Bs2Dst0Kst0_PdfBu, Sign::same)),
      Bs2Dst0Kst0_D0pi0_meanOffset21Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_meanOffset21Bu", uniqueId_, Neutral::pi0,
          Mode::Bs2Dst0Kst0_D0pi0, Systematic::Bs2Dst0Kst0_PdfBu, Sign::none)),
      Bs2Dst0Kst0_D0pi0_mean2Bu_(
          ("Bs2Dst0Kst0_D0pi0_mean2Bu" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "@0+@1",
          RooArgList(*Bs2Dst0Kst0_D0pi0_mean1Bu_,
                     *Bs2Dst0Kst0_D0pi0_meanOffset21Bu_)),
      Bs2Dst0Kst0_D0pi0_sigma1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_sigma1Bu", uniqueId_, Neutral::pi0,
          Mode::Bs2Dst0Kst0_D0pi0, Systematic::Bs2Dst0Kst0_PdfBu, Sign::same)),
      Bs2Dst0Kst0_D0pi0_sigmaRatio21Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_sigmaRatio21Bu", uniqueId_, Neutral::pi0,
          Mode::Bs2Dst0Kst0_D0pi0, Systematic::Bs2Dst0Kst0_PdfBu, Sign::same)),
      Bs2Dst0Kst0_D0pi0_sigma2Bu_(
          ("Bs2Dst0Kst0_D0pi0_sigma2Bu" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "@0*@1",
          RooArgList(*Bs2Dst0Kst0_D0pi0_sigma1Bu_,
                     *Bs2Dst0Kst0_D0pi0_sigmaRatio21Bu_)),
      Bs2Dst0Kst0_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_a1Bu", uniqueId_, Neutral::pi0,
          Mode::Bs2Dst0Kst0_D0pi0, Systematic::Bs2Dst0Kst0_PdfBu, Sign::same)),
      Bs2Dst0Kst0_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_n1Bu", uniqueId_, Neutral::pi0,
          Mode::Bs2Dst0Kst0_D0pi0, Systematic::Bs2Dst0Kst0_PdfBu, Sign::same)),
      pdf1Bu_Bs2Dst0Kst0_D0pi0_(
          ("pdf1Bu_Bs2Dst0Kst0_D0pi0_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2Dst0Kst0_D0pi0_mean1Bu_,
          *Bs2Dst0Kst0_D0pi0_sigma1Bu_, *Bs2Dst0Kst0_D0pi0_a1Bu_,
          *Bs2Dst0Kst0_D0pi0_n1Bu_),
      pdf2Bu_Bs2Dst0Kst0_D0pi0_(
          ("pdf2Bu_Bs2Dst0Kst0_D0pi0_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), Bs2Dst0Kst0_D0pi0_mean2Bu_,
          Bs2Dst0Kst0_D0pi0_sigma2Bu_),
      Bs2Dst0Kst0_D0pi0_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_fracPdf1Bu", uniqueId_, Neutral::pi0,
          Mode::Bs2Dst0Kst0_D0pi0, Systematic::Bs2Dst0Kst0_PdfBu, Sign::same)),
      pdfBu_Bs2Dst0Kst0_D0pi0_(
          ("pdfBu_Bs2Dst0Kst0_D0pi0_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bs2Dst0Kst0_D0pi0_, pdf2Bu_Bs2Dst0Kst0_D0pi0_),
          *Bs2Dst0Kst0_D0pi0_fracPdf1Bu_),
      Bs2Dst0Kst0_D0pi0_meanBuPartial_(nullptr),
      Bs2Dst0Kst0_D0pi0_sigmaBuPartial_(nullptr),
      Bs2Dst0Kst0_D0pi0_a1BuPartial_(nullptr),
      Bs2Dst0Kst0_D0pi0_n1BuPartial_(nullptr),
      pdfBuPartial_Bs2Dst0Kst0_D0pi0_(),
      mcEff_Bs2Dst0Kst0_D0pi0_(Params::Get().CreateFixed(
          "mcEff_Bs2Dst0Kst0_D0pi0", uniqueId_, Neutral::pi0,
          ReturnMCEffs(Mode::Bs2Dst0Kst0_D0pi0, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bs2Dst0Kst0_D0pi0, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg, Sign::same)),
      orEffBs2Dst0Kst0_D0pi0_(Params::Get().CreateFixed(
          "orEffBs2Dst0Kst0_D0pi0_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0, Bachelor::k, Efficiency::orEff,
                        false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0, Bachelor::k,
                        Efficiency::orEffErr, false),
          Systematic::boxEffs_Bs2Dst0Kst0, Sign::same)),
      deltaEffBs2Dst0Kst0_D0pi0_(Params::Get().CreateFixed(
          "deltaEffBs2Dst0Kst0_D0pi0_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0, Bachelor::k,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0, Bachelor::k,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_Bs2Dst0Kst0, Sign::same)),
      buEffBs2Dst0Kst0_D0pi0_(Params::Get().CreateFixed(
          "buEffBs2Dst0Kst0_D0pi0_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0, Bachelor::k, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0, Bachelor::k,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_Bs2Dst0Kst0, Sign::same)),
      buPartialEffBs2Dst0Kst0_D0pi0_(nullptr),
      // -------------------- Bs2Dst0Kst0_D0gamma -------------------- //
      Bs2Dst0Kst0_D0gamma_a1Delta_(nullptr),
      Bs2Dst0Kst0_D0gamma_n1Delta_(nullptr),
      Bs2Dst0Kst0_D0gamma_a2Delta_(nullptr),
      Bs2Dst0Kst0_D0gamma_n2Delta_(nullptr),
      Bs2Dst0Kst0_D0gamma_fracPdf1Delta_(nullptr),
      Bs2Dst0Kst0_D0gamma_meanBu_(nullptr),
      Bs2Dst0Kst0_D0gamma_sigmaBu_(nullptr),
      Bs2Dst0Kst0_D0gamma_a1Bu_(nullptr),
      Bs2Dst0Kst0_D0gamma_n1Bu_(nullptr),
      pdfBu_Bs2Dst0Kst0_D0gamma_(),
      mcEff_Bs2Dst0Kst0_D0gamma_(Params::Get().CreateFixed(
          "mcEff_Bs2Dst0Kst0_D0gamma", uniqueId_, Neutral::pi0,
          ReturnMCEffs(Mode::Bs2Dst0Kst0_D0gamma, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bs2Dst0Kst0_D0gamma, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg, Sign::same)),
      orEffBs2Dst0Kst0_D0gamma_(Params::Get().CreateFixed(
          "orEffBs2Dst0Kst0_D0gamma_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma, Bachelor::k,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma, Bachelor::k,
                        Efficiency::orEffErr, false),
          Systematic::boxEffs_Bs2Dst0Kst0, Sign::same)),
      deltaEffBs2Dst0Kst0_D0gamma_(Params::Get().CreateFixed(
          "deltaEffBs2Dst0Kst0_D0gamma_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma, Bachelor::k,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma, Bachelor::k,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_Bs2Dst0Kst0, Sign::same)),
      buEffBs2Dst0Kst0_D0gamma_(Params::Get().CreateFixed(
          "buEffBs2Dst0Kst0_D0gamma_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma, Bachelor::k,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma, Bachelor::k,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_Bs2Dst0Kst0, Sign::same)),
      buPartialEffBs2Dst0Kst0_D0gamma_(nullptr),
      // -------------------- Bs2Dst0Kst0_comb -------------------- //
      mcEff_Bs2Dst0Kst0_comb_(),
      orEffBs2Dst0Kst0_comb_(),
      deltaEffBs2Dst0Kst0_comb_(),
      // Only true π0: no true gamma. In π0 mode, we consider WN fraction of π0
      // w.r.t. gamma
      Bs2Dst0Kst0_fracD0pi0_(),
      Bs2Dst0Kst0_fracD0pi0_Delta_(),
      // -------------------- Bs2Dst0Kst0_D0pi0_WN -------------------- //
      Bs2Dst0Kst0_D0pi0_WN_thresholdDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_WN_thresholdDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bs2Dst0Kst0_PdfDelta,
          Sign::same)),
      Bs2Dst0Kst0_D0pi0_WN_cDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0pi0_WN_cDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bs2Dst0Kst0_PdfDelta,
          Sign::same)),
      Bs2Dst0Kst0_D0pi0_WN_meanBu_(
          Params::Get().CreateFixed("Bs2Dst0Kst0_D0pi0_WN_meanBu", uniqueId_,
                                    Neutral::pi0, Mode::Bs2Dst0Kst0_D0pi0_WN,
                                    Systematic::Bs2Dst0Kst0_PdfBu, Sign::same)),
      Bs2Dst0Kst0_D0pi0_WN_sigmaBu_(
          Params::Get().CreateFixed("Bs2Dst0Kst0_D0pi0_WN_sigmaBu", uniqueId_,
                                    Neutral::pi0, Mode::Bs2Dst0Kst0_D0pi0_WN,
                                    Systematic::Bs2Dst0Kst0_PdfBu, Sign::same)),
      pdfBu_Bs2Dst0Kst0_D0pi0_WN_(
          ("pdfBu_Bs2Dst0Kst0_D0pi0_WN_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2Dst0Kst0_D0pi0_WN_meanBu_,
          *Bs2Dst0Kst0_D0pi0_WN_sigmaBu_),
      Bs2Dst0Kst0_D0pi0_WN_meanBuPartial_(nullptr),
      Bs2Dst0Kst0_D0pi0_WN_sigmaBuPartial_(nullptr),
      pdfBuPartial_Bs2Dst0Kst0_D0pi0_WN_(),
      mcEff_Bs2Dst0Kst0_D0pi0_WN_(Params::Get().CreateFixed(
          "mcEff_Bs2Dst0Kst0_D0pi0_WN", uniqueId_, Neutral::pi0,
          ReturnMCEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg, Sign::same)),
      orEffBs2Dst0Kst0_D0pi0_WN_(Params::Get().CreateFixed(
          "orEffBs2Dst0Kst0_D0pi0_WN_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Bachelor::k,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Bachelor::k,
                        Efficiency::orEffErr, false),
          Systematic::boxEffs_Bs2Dst0Kst0, Sign::same)),
      deltaEffBs2Dst0Kst0_D0pi0_WN_(Params::Get().CreateFixed(
          "deltaEffBs2Dst0Kst0_D0pi0_WN_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Bachelor::k,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Bachelor::k,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_Bs2Dst0Kst0, Sign::same)),
      buEffBs2Dst0Kst0_D0pi0_WN_(Params::Get().CreateFixed(
          "buEffBs2Dst0Kst0_D0pi0_WN_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Bachelor::k,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0pi0_WN, Bachelor::k,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_Bs2Dst0Kst0, Sign::same)),
      buPartialEffBs2Dst0Kst0_D0pi0_WN_(nullptr),
      // -------------------- Bs2Dst0Kst0_D0gamma_WN -------------------- //
      Bs2Dst0Kst0_D0gamma_WN_thresholdDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_WN_thresholdDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bs2Dst0Kst0_PdfDelta,
          Sign::same)),
      Bs2Dst0Kst0_D0gamma_WN_aDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_WN_aDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bs2Dst0Kst0_PdfDelta,
          Sign::none)),
      Bs2Dst0Kst0_D0gamma_WN_bDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_WN_bDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bs2Dst0Kst0_PdfDelta,
          Sign::none)),
      Bs2Dst0Kst0_D0gamma_WN_cDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_D0gamma_WN_cDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::Bs2Dst0Kst0_PdfDelta,
          Sign::same)),
      pdfDelta_Bs2Dst0Kst0_D0gamma_WN_(("pdfDelta_Bs2Dst0Kst0_D0gamma_WN_" +
                                        ComposeName(uniqueId_, Neutral::pi0))
                                           .c_str(),
                                       "", Configuration::Get().deltaMass(),
                                       *Bs2Dst0Kst0_D0gamma_WN_thresholdDelta_,
                                       *Bs2Dst0Kst0_D0gamma_WN_cDelta_,
                                       *Bs2Dst0Kst0_D0gamma_WN_aDelta_,
                                       *Bs2Dst0Kst0_D0gamma_WN_bDelta_),
      Bs2Dst0Kst0_D0gamma_WN_meanBu_(nullptr),
      Bs2Dst0Kst0_D0gamma_WN_sigmaBu_(nullptr),
      pdfBu_Bs2Dst0Kst0_D0gamma_WN_(),
      Bs2Dst0Kst0_D0gamma_WN_meanBuPartial_(nullptr),
      Bs2Dst0Kst0_D0gamma_WN_sigmaBuPartial_(nullptr),
      pdfBuPartial_Bs2Dst0Kst0_D0gamma_WN_(),
      mcEff_Bs2Dst0Kst0_D0gamma_WN_(Params::Get().CreateFixed(
          "mcEff_Bs2Dst0Kst0_D0gamma_WN", uniqueId_, Neutral::pi0,
          ReturnMCEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg, Sign::same)),
      orEffBs2Dst0Kst0_D0gamma_WN_(Params::Get().CreateFixed(
          "orEffBs2Dst0Kst0_D0gamma_WN_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Bachelor::k,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Bachelor::k,
                        Efficiency::orEffErr, false),
          Systematic::boxEffs_Bs2Dst0Kst0, Sign::same)),
      deltaEffBs2Dst0Kst0_D0gamma_WN_(Params::Get().CreateFixed(
          "deltaEffBs2Dst0Kst0_D0gamma_WN_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Bachelor::k,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Bachelor::k,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_Bs2Dst0Kst0, Sign::same)),
      buEffBs2Dst0Kst0_D0gamma_WN_(Params::Get().CreateFixed(
          "buEffBs2Dst0Kst0_D0gamma_WN_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Bachelor::k,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bs2Dst0Kst0_D0gamma_WN, Bachelor::k,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_Bs2Dst0Kst0, Sign::same)),
      buPartialEffBs2Dst0Kst0_D0gamma_WN_(nullptr),
      // -------------------- Bs2Dst0Kst0_WN -------------------- //
      Bs2Dst0Kst0_fracD0pi0_WN_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_fracD0pi0_WN", uniqueId_, Neutral::pi0,
          ReadPdfFracs<Neutral::pi0, Bachelor::k>("Bs2Dst0Kst0_fracD0pi0_WN",
                                                  ReturnType::val),
          ReadPdfFracs<Neutral::pi0, Bachelor::k>("Bs2Dst0Kst0_fracD0pi0_WN",
                                                  ReturnType::std),
          Systematic::Bs2Dst0Kst0_Frac, Sign::same)),
      // Only π0 compts in B mass dimn due to delta mass cut
      Bs2Dst0Kst0_fracD0pi0_WN_Bu_(nullptr),
      Bs2Dst0Kst0_fracD0pi0_WN_Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_fracD0pi0_WN_Delta", uniqueId_, Neutral::pi0,
          ReadPdfFracs<Neutral::pi0, Bachelor::k>(
              "Bs2Dst0Kst0_fracD0pi0_WN_Delta", ReturnType::val),
          ReadPdfFracs<Neutral::pi0, Bachelor::k>(
              "Bs2Dst0Kst0_fracD0pi0_WN_Delta", ReturnType::std),
          Systematic::Bs2Dst0Kst0_Frac, Sign::same)),
      Bs2Dst0Kst0_fracD0pi0_WN_BuPartial_(nullptr),
      pdfBu_Bs2Dst0Kst0_WN_(),
      pdfBuPartial_Bs2Dst0Kst0_WN_(),
      mcEff_Bs2Dst0Kst0_WN_(
          ("mcEff_Bs2Dst0Kst0_WN_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bs2Dst0Kst0_fracD0pi0_WN_, *mcEff_Bs2Dst0Kst0_D0pi0_WN_,
                     *mcEff_Bs2Dst0Kst0_D0gamma_WN_)),
      orEffBs2Dst0Kst0_WN_(
          ("orEffBs2Dst0Kst0_WN_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bs2Dst0Kst0_fracD0pi0_WN_, *orEffBs2Dst0Kst0_D0pi0_WN_,
                     *orEffBs2Dst0Kst0_D0gamma_WN_)),
      buEffBs2Dst0Kst0_WN_(),
      deltaEffBs2Dst0Kst0_WN_(
          ("deltaEffBs2Dst0Kst0_WN_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bs2Dst0Kst0_fracD0pi0_WN_, *deltaEffBs2Dst0Kst0_D0pi0_WN_,
                     *deltaEffBs2Dst0Kst0_D0gamma_WN_)),
      buPartialEffBs2Dst0Kst0_WN_(),
      // -------------------- Bu2Dst0h_D0pi0_D02pik -------------------- //
      Bu2Dst0h_D0pi0_D02pik_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_sigmaDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::D02pik_Pdfs, Sign::same)),
      Bu2Dst0h_D0pi0_D02pik_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_a2Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::D02pik_Pdfs, Sign::same)),
      Bu2Dst0h_D0pi0_D02pik_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_n2Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::D02pik_Pdfs, Sign::same)),
      Bu2Dst0h_D0pi0_D02pik_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_fracPdf1Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::D02pik_Pdfs, Sign::same)),
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
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::D02pik_Pdfs, Sign::same)),
      Bu2Dst0h_D0pi0_D02pik_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_D02pik_sigmaBu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_D02pik, Systematic::D02pik_Pdfs, Sign::same)),
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
          Systematic::boxEffs_D02pik, Sign::same)),
      deltaEffBu2Dst0h_D0pi0_D02pik_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_D02pik_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_D02pik, Sign::same)),
      buEffBu2Dst0h_D0pi0_D02pik_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_D02pik_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_D02pik, Sign::same)),
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
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::D02pik_Pdfs,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_D02pik_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_a2Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::D02pik_Pdfs,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_D02pik_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_n2Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::D02pik_Pdfs,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_D02pik_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_fracPdf1Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::D02pik_Pdfs,
          Sign::same)),
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
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::D02pik_Pdfs,
          Sign::same)),
      Bu2Dst0h_D0pi0_WN_D02pik_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_D02pik_sigmaBu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Systematic::D02pik_Pdfs,
          Sign::same)),
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
          Systematic::boxEffs_D02pik, Sign::same)),
      deltaEffBu2Dst0h_D0pi0_WN_D02pik_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_WN_D02pik_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_D02pik, Sign::same)),
      buEffBu2Dst0h_D0pi0_WN_D02pik_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_WN_D02pik_", uniqueId_, Neutral::pi0,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN_D02pik, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_D02pik, Sign::same)),
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
      // bkgFracGlobal_WN_(Params::Get().CreateFloating(
      //     "bkgFracGlobal_WN", uniqueId_, Neutral::pi0, 1, 0, 5)),
      bkgFracGlobal_WN_(Params::Get().CreateFixed("bkgFracGlobal_WN", uniqueId_,
                                                  Neutral::pi0, 1, 0.1,
                                                  Systematic::NA, Sign::same)),
      bkgFracFAV_Bd2Dsth_(Params::Get().CreateFloating(
          "bkgFracFAV_Bd2Dsth", uniqueId_, Neutral::pi0,
          ReadBkgFracs<Neutral::pi0>(Mode::Bd2Dstpi, ReturnType::val), 0, 5)),
      // Constrained relative to Bd2Dsth
      // bkgFracFAV_Bu2D0hst_(Params::Get().CreateFloating(
      //     "bkgFracFAV_Bu2D0hst", uniqueId_, Neutral::pi0,
      // ReadBkgFracs<Neutral::pi0>(Mode::Bu2D0rho, ReturnType::val),
      //     0, 5)),
      bkgFracFAV_Bu2D0hst_(Params::Get().CreateFixed(
          "bkgFracFAV_Bu2D0hst", uniqueId_, Neutral::pi0,
          ReadBkgFracs<Neutral::pi0>(Mode::Bu2D0rho, ReturnType::val),
          ReadBkgFracs<Neutral::pi0>(Mode::Bu2D0rho, ReturnType::std),
          Systematic::Bu2D0hst_BkgFrac, Sign::same)),
      bkgFracFAV_Bu2Dst0hst_(Params::Get().CreateFixed(
          "bkgFracFAV_Bu2Dst0hst", uniqueId_, Neutral::pi0,
          ReadBkgFracs<Neutral::pi0>(Mode::Bu2Dst0rho, ReturnType::val),
          ReadBkgFracs<Neutral::pi0>(Mode::Bu2Dst0rho, ReturnType::std),
          Systematic::Bu2Dst0hst_BkgFrac, Sign::same)),
      // bkgFracFAV_Bu2Dst0hst_(Params::Get().CreateFloating(
      //     "bkgFracFAV_Bu2Dst0hst", uniqueId_, Neutral::pi0,
      // ReadBkgFracs<Neutral::pi0>(Mode::Bu2Dst0rho, ReturnType::val),
      //     0, 5)),
      bkgFracKK_Lb2Omegach_Lcpi0_(Params::Get().CreateFloating(
          "bkgFracKK_Lb2Omegach_Lcpi0", uniqueId_, Neutral::pi0, 0.1, 0, 5)),
      bkgFracADS_Bs2D0Kst0_(Params::Get().CreateFloating(
          "bkgFracADS_Bs2D0Kst0", uniqueId_, Neutral::pi0,
          ReadBkgFracs<Neutral::pi0>(Mode::Bs2D0Kst0, ReturnType::val), -2,
          15)),
      // bkgFracADS_Bs2D0Kst0_(Params::Get().CreateFixed(
      //     "bkgFracADS_Bs2D0Kst0", uniqueId_, Neutral::pi0,
      //     ReadBkgFracs<Neutral::pi0>(Mode::Bs2D0Kst0, ReturnType::val),
      //     ReadBkgFracs<Neutral::pi0>(Mode::Bs2D0Kst0, ReturnType::std),
      //     Systematic::Bs2D0Kst0_BkgFrac, Sign::same)) {}
      bkgFracADS_Bs2Dst0Kst0_(Params::Get().CreateFloating(
          "bkgFracADS_Bs2Dst0Kst0", uniqueId_, Neutral::pi0,
          ReadBkgFracs<Neutral::pi0>(Mode::Bs2Dst0Kst0, ReturnType::val), 0,
          10)),
      BR_pi02gamma_eff_(nullptr),
      // -------------------- Bs2Dst0Kst0 -------------------- //
      Bs2Dst0Kst0_fracWN_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_fracWN", uniqueId_, Neutral::pi0,
          ReadPdfFracs<Neutral::pi0, Bachelor::k>("Bs2Dst0Kst0_fracWN",
                                                  ReturnType::val),
          ReadPdfFracs<Neutral::pi0, Bachelor::k>("Bs2Dst0Kst0_fracWN",
                                                  ReturnType::std),
          Systematic::Bs2Dst0Kst0_Frac, Sign::same)),
      Bs2Dst0Kst0_fracWN_Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_fracWN_Bu", uniqueId_, Neutral::pi0,
          ReadPdfFracs<Neutral::pi0, Bachelor::k>("Bs2Dst0Kst0_fracWN_Bu",
                                                  ReturnType::val),
          // 1.0,
          ReadPdfFracs<Neutral::pi0, Bachelor::k>("Bs2Dst0Kst0_fracWN_Bu",
                                                  ReturnType::std),
          Systematic::Bs2Dst0Kst0_Frac, Sign::same)),
      Bs2Dst0Kst0_fracWN_Delta_(Params::Get().CreateFixed(
          "Bs2Dst0Kst0_fracWN_Delta", uniqueId_, Neutral::pi0,
          ReadPdfFracs<Neutral::pi0, Bachelor::k>("Bs2Dst0Kst0_fracWN_Delta",
                                                  ReturnType::val),
          ReadPdfFracs<Neutral::pi0, Bachelor::k>("Bs2Dst0Kst0_fracWN_Delta",
                                                  ReturnType::std),
          Systematic::Bs2Dst0Kst0_Frac, Sign::same)),
      Bs2Dst0Kst0_fracWN_BuPartial_(nullptr),
      Bs2Dst0Kst0_floatingFracWN_Bu_(
          ("Bs2Dst0Kst0_floatingFracWN_Bu_" +
           ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "@0*@1", RooArgList(*Bs2Dst0Kst0_fracWN_Bu_, *bkgFracGlobal_WN_)),
      // "@0", RooArgList(*Bs2Dst0Kst0_fracWN_Bu_)),
      Bs2Dst0Kst0_floatingFracWN_Delta_(
          ("Bs2Dst0Kst0_floatingFracWN_Delta_" +
           ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "@0*@1", RooArgList(*Bs2Dst0Kst0_fracWN_Delta_, *bkgFracGlobal_WN_)),
      Bs2Dst0Kst0_floatingFracWN_BuPartial_(),
      pdfBu_Bs2Dst0Kst0_(
          ("pdfBu_Bs2Dst0Kst0_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", RooArgList(pdfBu_Bs2Dst0Kst0_D0pi0_WN_, pdfBu_Bs2Dst0Kst0_D0pi0_),
          Bs2Dst0Kst0_floatingFracWN_Bu_),
      pdfBuPartial_Bs2Dst0Kst0_(),
      mcEff_Bs2Dst0Kst0_(
          ("mcEff_Bs2Dst0Kst0_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "@2*(1-@0*@1)+@3*@0*@1",
          RooArgList(*Bs2Dst0Kst0_fracWN_, *bkgFracGlobal_WN_,
                     *mcEff_Bs2Dst0Kst0_D0pi0_, mcEff_Bs2Dst0Kst0_WN_)),
      orEffBs2Dst0Kst0_(
          ("orEffBs2Dst0Kst0_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "@2*(1-@0*@1)+@3*@0*@1",
          RooArgList(*Bs2Dst0Kst0_fracWN_, *bkgFracGlobal_WN_,
                     *orEffBs2Dst0Kst0_D0pi0_, orEffBs2Dst0Kst0_WN_)),
      buEffBs2Dst0Kst0_(
          ("buEffBs2Dst0Kst0_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "@2*(1-@0*@1)+@3*@0*@1",
          // "@0",
          RooArgList(*Bs2Dst0Kst0_fracWN_, *bkgFracGlobal_WN_,
                     *buEffBs2Dst0Kst0_D0pi0_, *buEffBs2Dst0Kst0_D0pi0_WN_)),
      // RooArgList(*buEffBs2Dst0Kst0_D0pi0_)),
      deltaEffBs2Dst0Kst0_(
          ("deltaEffBs2Dst0Kst0_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "@2*(1-@0*@1)+@3*@0*@1",
          RooArgList(*Bs2Dst0Kst0_fracWN_, *bkgFracGlobal_WN_,
                     *deltaEffBs2Dst0Kst0_D0pi0_, deltaEffBs2Dst0Kst0_WN_)),
      buPartialEffBs2Dst0Kst0_() {}
