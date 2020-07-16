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
      Bu2Dst0h_D0gamma_meanDelta_(
          Params::Get().CreateFloating("Bu2Dst0h_D0gamma_meanDelta", uniqueId_,
                                       Neutral::gamma, 1.4254e+02, 135, 150)),
      Bu2Dst0h_D0gamma_sigmaDelta_(
          Params::Get().CreateFloating("Bu2Dst0h_D0gamma_sigmaDelta", uniqueId_,
                                       Neutral::gamma, 8.4013e+00, 2, 15)),
      Bu2Dst0h_D0gamma_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a1Delta", uniqueId_, Neutral::gamma, 1.4638e+00,
          8.12e-02, Systematic::gammaDeltaTails, Sign::positive)),
      Bu2Dst0h_D0gamma_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n1Delta", uniqueId_, Neutral::gamma, 10, 0,
          Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0gamma_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a2Delta", uniqueId_, Neutral::gamma, -6.2499e-01,
          2.34e-02, Systematic::gammaDeltaTails, Sign::negative)),
      Bu2Dst0h_D0gamma_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n2Delta", uniqueId_, Neutral::gamma, 10, 0,
          Systematic::NA, Sign::positive)),
      pdf1Delta_Bu2Dst0h_D0gamma_(
          ("pdf1Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0gamma_meanDelta_,
          *Bu2Dst0h_D0gamma_sigmaDelta_, *Bu2Dst0h_D0gamma_a1Delta_,
          *Bu2Dst0h_D0gamma_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0gamma_(
          ("pdf2Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0gamma_meanDelta_,
          *Bu2Dst0h_D0gamma_sigmaDelta_, *Bu2Dst0h_D0gamma_a2Delta_,
          *Bu2Dst0h_D0gamma_n2Delta_),
      Bu2Dst0h_D0gamma_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_fracPdf1Delta", uniqueId_, Neutral::gamma,
          2.5654e-01, 3.91e-02, Systematic::gammaDeltaFrac, Sign::positive)),
      Bu2Dst0h_D0gamma_thresholdDelta_(nullptr),
      Bu2Dst0h_D0gamma_aDelta_(nullptr),
      Bu2Dst0h_D0gamma_bDelta_(nullptr),
      Bu2Dst0h_D0gamma_cDelta_(nullptr),
      pdfDelta_Bu2Dst0h_D0gamma_(new RooAddPdf(
          ("pdfDelta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0gamma_, pdf2Delta_Bu2Dst0h_D0gamma_),
          *Bu2Dst0h_D0gamma_fracPdf1Delta_)),
      pdfDelta_misId_Bu2Dst0h_D0gamma_(new RooAddPdf(
          ("pdfDelta_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0gamma_, pdf2Delta_Bu2Dst0h_D0gamma_),
          *Bu2Dst0h_D0gamma_fracPdf1Delta_)),
      Bu2Dst0h_D0gamma_meanBu_(
          Params::Get().CreateFloating("Bu2Dst0h_D0gamma_meanBu", uniqueId_,
                                       Neutral::gamma, 5.2814e+03, 5275, 5285)),
      Bu2Dst0h_D0gamma_KpiSigmaBu_(
          Params::Get().CreateFloating("Bu2Dst0h_D0gamma_KpiSigmaBu", uniqueId_,
                                       Neutral::gamma, 0.95, 0.5, 1.5)),
      Bu2Dst0h_D0gamma_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a1Bu", uniqueId_, Neutral::gamma, 1.5214e+00,
          3.08e-02, Systematic::gammaBuTails, Sign::positive)),
      Bu2Dst0h_D0gamma_a2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a2Bu", uniqueId_, Neutral::gamma, -1.9560e+00,
          7.54e-02, Systematic::gammaBuTails, Sign::negative)),
      Bu2Dst0h_D0gamma_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n1Bu", uniqueId_, Neutral::gamma, 8.6469e+00, 1e-01,
          Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0gamma_n2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n2Bu", uniqueId_, Neutral::gamma, 10, 1e-01,
          Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0gamma_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_fracPdf1Bu", uniqueId_, Neutral::gamma, 6.2860e-01,
          8.13e-02, Systematic::gammaBuFrac, Sign::positive)),
      Bu2Dst0h_D0gamma_meanBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_meanBuPartial", uniqueId_, Neutral::gamma,
          5.2602e+03, 3.68e+00, Systematic::crossFeedBuPartialPdf,
          Sign::positive)),
      Bu2Dst0h_D0gamma_aBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_aBuPartial", uniqueId_, Neutral::gamma, 2.5968e+00,
          3.45e-01, Systematic::crossFeedBuPartialPdf, Sign::none)),
      Bu2Dst0h_D0gamma_nBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_nBuPartial", uniqueId_, Neutral::gamma, 1.8178e-06,
          6.90e-02, Systematic::crossFeedBuPartialPdf, Sign::positive)),
      // -------------------- Bu2Dst0h_D0gamma_FAVasSUP -------------------- //
      Bu2Dst0h_D0gamma_FAVasSUP_meanDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_meanDelta", uniqueId_, Neutral::gamma,
          1.4448e+02, 8.73e-01, Systematic::gammaFAVasSUPDeltaPdf,
          Sign::positive)),
      Bu2Dst0h_D0gamma_FAVasSUP_sigmaDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_sigmaDelta", uniqueId_, Neutral::gamma,
          9.9175e+00, 9.85e-01, Systematic::gammaFAVasSUPDeltaPdf,
          Sign::positive)),
      Bu2Dst0h_D0gamma_FAVasSUP_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_a1Delta", uniqueId_, Neutral::gamma,
          1.0314e+00, 2.90e-01, Systematic::gammaFAVasSUPDeltaPdf,
          Sign::positive)),
      Bu2Dst0h_D0gamma_FAVasSUP_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_a2Delta", uniqueId_, Neutral::gamma,
          -4.9581e-01, 2.78e-01, Systematic::gammaFAVasSUPDeltaPdf,
          Sign::negative)),
      Bu2Dst0h_D0gamma_FAVasSUP_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_n1Delta", uniqueId_, Neutral::gamma,
          1.0000e+01, 1.00, Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0gamma_FAVasSUP_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_n2Delta", uniqueId_, Neutral::gamma,
          2.9165e+00, 1.00, Systematic::NA, Sign::positive)),
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
          3.9419e-01, 2.37e-01, Systematic::gammaFAVasSUPDeltaPdf,
          Sign::positive)),
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
          5.2790e+03, 2.62e+00, Systematic::gammaFAVasSUPBuPdf,
          Sign::positive)),
      Bu2Dst0h_D0gamma_FAVasSUP_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_sigmaBu", uniqueId_, Neutral::gamma,
          9.2045e+01, 1.95e+00, Systematic::gammaFAVasSUPBuPdf,
          Sign::positive)),
      Bu2Dst0h_D0gamma_FAVasSUP_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_a1Bu", uniqueId_, Neutral::gamma,
          2.6730e+00, 1.23e-01, Systematic::gammaFAVasSUPBuPdf, Sign::none)),
      Bu2Dst0h_D0gamma_FAVasSUP_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_FAVasSUP_n1Bu", uniqueId_, Neutral::gamma,
          7.5377e-07, 1.60e-01, Systematic::gammaFAVasSUPBuPdf,
          Sign::positive)),
      pdfBu_Bu2Dst0h_D0gamma_FAVasSUP_(("pdfBu_Bu2Dst0h_D0gamma_FAVasSUP_" +
                                        ComposeName(uniqueId_, Neutral::gamma))
                                           .c_str(),
                                       "", Configuration::Get().deltaMass(),
                                       *Bu2Dst0h_D0gamma_FAVasSUP_meanBu_,
                                       *Bu2Dst0h_D0gamma_FAVasSUP_sigmaBu_,
                                       *Bu2Dst0h_D0gamma_FAVasSUP_a1Bu_,
                                       *Bu2Dst0h_D0gamma_FAVasSUP_n1Bu_),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      Bu2Dst0h_D0pi0_meanDelta_(
          Params::Get().CreateFloating("Bu2Dst0h_D0pi0_meanDelta", uniqueId_,
                                       Neutral::gamma, 8.5344e+01, 75, 95)),
      Bu2Dst0h_D0pi0_sigmaDelta_(
          Params::Get().CreateFloating("Bu2Dst0h_D0pi0_sigmaDelta", uniqueId_,
                                       Neutral::gamma, 9.2449e+00, 5, 15)),
      Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::gamma, 1.9595e-01,
          1.06e-01, Systematic::pi0DeltaTails, Sign::positive)),
      Bu2Dst0h_D0pi0_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Delta", uniqueId_, Neutral::gamma, 10, 0,
          Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2Delta", uniqueId_, Neutral::gamma, -8.8827e-01,
          5.76e-02, Systematic::pi0DeltaTails, Sign::negative)),
      Bu2Dst0h_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2Delta", uniqueId_, Neutral::gamma, 4.5914e+00,
          4.94e-01, Systematic::pi0DeltaTails, Sign::positive)),
      pdf1Delta_Bu2Dst0h_D0pi0_(
          ("pdf1Delta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0pi0_meanDelta_,
          *Bu2Dst0h_D0pi0_sigmaDelta_, *Bu2Dst0h_D0pi0_a1Delta_,
          *Bu2Dst0h_D0pi0_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0pi0_(
          ("pdf2Delta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0pi0_meanDelta_,
          *Bu2Dst0h_D0pi0_sigmaDelta_, *Bu2Dst0h_D0pi0_a2Delta_,
          *Bu2Dst0h_D0pi0_n2Delta_),
      Bu2Dst0h_D0pi0_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf1Delta", uniqueId_, Neutral::gamma, 2.9205e-01,
          5.04e-02, Systematic::pi0DeltaFrac, Sign::positive)),
      pdfDelta_Bu2Dst0h_D0pi0_(
          ("pdfDelta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          *Bu2Dst0h_D0pi0_fracPdf1Delta_),
      pdfDelta_misId_Bu2Dst0h_D0pi0_(
          ("pdfDelta_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          *Bu2Dst0h_D0pi0_fracPdf1Delta_),
      Bu2Dst0h_D0pi0_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_meanBu", uniqueId_, Neutral::gamma, 5.3371e+03,
          2.22e+00, Systematic::crossFeedBuPdf, Sign::positive)),
      Bu2Dst0h_D0pi0_KpiSigmaBu_(nullptr),
      Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Bu", uniqueId_, Neutral::gamma, 9.4845e-01,
          6.81e-02, Systematic::crossFeedBuPdf, Sign::positive)),
      Bu2Dst0h_D0pi0_a2Bu_(nullptr),
      Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Bu", uniqueId_, Neutral::gamma, 10, 0,
          Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0pi0_n2Bu_(nullptr),
      Bu2Dst0h_D0pi0_fracPdf1Bu_(nullptr),
      Bu2Dst0h_D0pi0_meanCbBuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_meanCbBuPartial", uniqueId_, Neutral::gamma,
          5.2787e+03, 5270, 5290)),
      Bu2Dst0h_D0pi0_meanOffsetGausBuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_meanOffsetGausBuPartial", uniqueId_, Neutral::gamma,
          2.6745e+01, 10, 50)),
      Bu2Dst0h_D0pi0_meanGausBuPartial_(
          ("Bu2Dst0h_D0pi0_meanGausBuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0+@1",
          RooArgSet(*Bu2Dst0h_D0pi0_meanCbBuPartial_,
                    *Bu2Dst0h_D0pi0_meanOffsetGausBuPartial_)),
      Bu2Dst0h_D0pi0_KpiSigmaBuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_KpiSigmaBuPartial", uniqueId_, Neutral::gamma, 0.95,
          0.5, 1.5)),
      Bu2Dst0h_D0pi0_sigmaRatio21BuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_sigmaRatio21BuPartial", uniqueId_, Neutral::gamma,
          1.7568e+00,  // 1.00e-01
          1, 2.5)),
      Bu2Dst0h_D0pi0_sigmaRatio31BuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_sigmaRatio31BuPartial", uniqueId_, Neutral::gamma,
          7.0821e-01,  // 5.53e-02
          0.2, 1.5)),
      Bu2Dst0h_D0pi0_a1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1BuPartial", uniqueId_, Neutral::gamma, 1.9990e+00,
          0, Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0pi0_n1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1BuPartial", uniqueId_, Neutral::gamma, 2.3530e+00,
          0, Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0pi0_a2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2BuPartial", uniqueId_, Neutral::gamma, -2.7593e+00,
          0, Systematic::NA, Sign::negative)),
      Bu2Dst0h_D0pi0_n2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2BuPartial", uniqueId_, Neutral::gamma, 3.1306e+00,
          0, Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0pi0_fracPdfCb1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdfCb1BuPartial", uniqueId_, Neutral::gamma,
          2.0549e-01, 2.77e-02, Systematic::pi0BuPartialFrac, Sign::positive)),
      Bu2Dst0h_D0pi0_fracPdfCb2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdfCb2BuPartial", uniqueId_, Neutral::gamma,
          6.5515e-01, 2.56e-02, Systematic::pi0BuPartialFrac, Sign::positive)),
      // -------------------- Bu2Dst0h_D0pi0_FAVasSUP -------------------- //
      Bu2Dst0h_D0pi0_FAVasSUP_meanDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_meanDelta", uniqueId_, Neutral::gamma,
          8.0373e+01, 2.94e-01, Systematic::pi0FAVasSUPDeltaPdf,
          Sign::positive)),
      Bu2Dst0h_D0pi0_FAVasSUP_sigma1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_sigma1Delta", uniqueId_, Neutral::gamma,
          2.7182e+01, 1.27e+00, Systematic::pi0FAVasSUPDeltaPdf,
          Sign::positive)),
      Bu2Dst0h_D0pi0_FAVasSUP_sigma2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_sigma2Delta", uniqueId_, Neutral::gamma,
          1.5428e+01, 4.44e-01, Systematic::pi0FAVasSUPDeltaPdf,
          Sign::positive)),
      Bu2Dst0h_D0pi0_FAVasSUP_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_a1Delta", uniqueId_, Neutral::gamma,
          2.2712e+00, 1.00, Systematic::NA, Sign::none)),
      Bu2Dst0h_D0pi0_FAVasSUP_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_a2Delta", uniqueId_, Neutral::gamma,
          -1.1218e+00, 1.00, Systematic::NA, Sign::none)),
      Bu2Dst0h_D0pi0_FAVasSUP_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_n1Delta", uniqueId_, Neutral::gamma,
          2.0098e+00, 1.00, Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0pi0_FAVasSUP_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_n2Delta", uniqueId_, Neutral::gamma,
          2.0519e+00, 1.00, Systematic::NA, Sign::positive)),
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
          3.1093e-01, 3.19e-02, Systematic::pi0FAVasSUPDeltaPdf,
          Sign::positive)),
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
          5.2946e+03, 2.83e+00, Systematic::pi0FAVasSUPBuPdf, Sign::positive)),
      Bu2Dst0h_D0pi0_FAVasSUP_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_sigmaBu", uniqueId_, Neutral::gamma,
          1.0716e+02, 2.38e+00, Systematic::pi0FAVasSUPBuPdf, Sign::positive)),
      Bu2Dst0h_D0pi0_FAVasSUP_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_a1Bu", uniqueId_, Neutral::gamma, 1.3827e+00,
          1.13e-01, Systematic::pi0FAVasSUPBuPdf, Sign::none)),
      Bu2Dst0h_D0pi0_FAVasSUP_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_n1Bu", uniqueId_, Neutral::gamma, 1.0000e+01,
          1.00, Systematic::NA, Sign::positive)),
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
          Sign::positive)),
      Bu2Dst0h_D0pi0_FAVasSUP_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_sigmaBuPartial", uniqueId_, Neutral::gamma,
          9.7158e+01, 5.59e-01, Systematic::pi0FAVasSUPBuPartialPdf,
          Sign::positive)),
      Bu2Dst0h_D0pi0_FAVasSUP_a1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_a1BuPartial", uniqueId_, Neutral::gamma,
          2.7829e+00, 3.02e-01, Systematic::pi0FAVasSUPBuPartialPdf,
          Sign::none)),
      Bu2Dst0h_D0pi0_FAVasSUP_n1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_n1BuPartial", uniqueId_, Neutral::gamma,
          1.3591e+00, 1.00, Systematic::NA, Sign::positive)),
      pdfBuPartial_Bu2Dst0h_D0pi0_FAVasSUP_(
          ("pdfBuPartial_Bu2Dst0h_D0pi0_FAVasSUP_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0pi0_FAVasSUP_meanBuPartial_,
          *Bu2Dst0h_D0pi0_FAVasSUP_sigmaBuPartial_,
          *Bu2Dst0h_D0pi0_FAVasSUP_a1BuPartial_,
          *Bu2Dst0h_D0pi0_FAVasSUP_n1BuPartial_),
      // -------------------- MIS-REC -------------------- //
      MisRec_thresholdDelta_(Params::Get().CreateFixed(
          "MisRec_thresholdDelta", uniqueId_, Neutral::gamma, 4.9426e+01,
          7.76e-01, Systematic::misRecDeltaPdf, Sign::positive)),
      MisRec_aDelta_(Params::Get().CreateFloating(
          "MisRec_aDelta", uniqueId_, Neutral::gamma, 1.1334e+00, -5, 5)),
      MisRec_bDelta_(Params::Get().CreateFixed(
          "MisRec_bDelta", uniqueId_, Neutral::gamma, -1.5029e+00, 2.56e-03,
          Systematic::misRecDeltaPdf, Sign::none)),
      MisRec_cDelta_(Params::Get().CreateFixed(
          "MisRec_cDelta", uniqueId_, Neutral::gamma, 3.4954e+01, 2.08e-01,
          Systematic::misRecDeltaPdf, Sign::positive)),
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
          Systematic::misRecBuPdf, Sign::positive)),
      MisRec_aLBu_(Params::Get().CreateFixed(
          "MisRec_aLBu", uniqueId_, Neutral::gamma, 1.5419e-02, 1.27e-02,
          Systematic::misRecBuPdf, Sign::positive)),
      MisRec_aRBu_(Params::Get().CreateFixed(
          "MisRec_aRBu", uniqueId_, Neutral::gamma, 3.1182e-02, 7.38e-03,
          Systematic::misRecBuPdf, Sign::positive)),
      MisRec_meanBuPartial_(Params::Get().CreateFixed(
          "MisRec_meanBuPartial", uniqueId_, Neutral::gamma, 5.3344e+03,
          7.06e-01, Systematic::misRecBuPartialPdf, Sign::positive)),
      MisRec_aLBuPartial_(Params::Get().CreateFixed(
          "MisRec_aLBuPartial", uniqueId_, Neutral::gamma, 1.6586e-07, 1.10e-03,
          Systematic::misRecBuPartialPdf, Sign::positive)),
      MisRec_aRBuPartial_(Params::Get().CreateFixed(
          "MisRec_aRBuPartial", uniqueId_, Neutral::gamma, 1.1570e-08, 2.81e-03,
          Systematic::misRecBuPartialPdf, Sign::positive)),
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
          1.42e+00, Systematic::partRecDeltaPdf, Sign::positive)),
      PartRec_aDelta_(Params::Get().CreateFixed(
          "PartRec_aDelta", uniqueId_, Neutral::gamma, 5.7789e-01, 6.95e-03,
          Systematic::partRecDeltaPdf, Sign::none)),
      PartRec_bDelta_(Params::Get().CreateFixed(
          "PartRec_bDelta", uniqueId_, Neutral::gamma, -6.7459e-01, 8.51e-03,
          Systematic::partRecDeltaPdf, Sign::none)),
      PartRec_cDelta_(Params::Get().CreateFixed(
          "PartRec_cDelta", uniqueId_, Neutral::gamma, 9.9939e+01, 5.48e+00,
          Systematic::partRecDeltaPdf, Sign::positive)),
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
          3.68e+00, Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0pi0_aLBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_aLBu", uniqueId_, Neutral::gamma, 6.1807e-08, 1.45e-02,
          Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0pi0_aRBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_aRBu", uniqueId_, Neutral::gamma, 4.8226e-07, 8.40e-03,
          Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0gamma_meanBu_(Params::Get().CreateFixed(
          "PartRec_D0gamma_meanBu", uniqueId_, Neutral::gamma, 5.1068e+03,
          4.67e+00, Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0gamma_aLBu_(Params::Get().CreateFixed(
          "PartRec_D0gamma_aLBu", uniqueId_, Neutral::gamma, 8.6670e-02,
          3.96e-02, Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0gamma_aRBu_(Params::Get().CreateFixed(
          "PartRec_D0gamma_aRBu", uniqueId_, Neutral::gamma, 1.9464e-01,
          1.57e-02, Systematic::partRecBuPdf, Sign::positive)),
      PartRec_frac_D0pi0_(Params::Get().CreateFixed(
          "PartRec_frac_D0pi0", uniqueId_, Neutral::gamma, 3.8179e-01, 1.34e-02,
          Systematic::partRecBuPdf, Sign::positive)),
      PartRec_meanBuPartial_(Params::Get().CreateFixed(
          "PartRec_meanBuPartial", uniqueId_, Neutral::gamma, 5.1640e+03,
          2.20e+00, Systematic::partRecBuPartialPdf, Sign::positive)),
      PartRec_aLBuPartial_(Params::Get().CreateFixed(
          "PartRec_aLBuPartial", uniqueId_, Neutral::gamma, 4.6600e-02,
          1.90e-02, Systematic::partRecBuPartialPdf, Sign::positive)),
      PartRec_aRBuPartial_(Params::Get().CreateFixed(
          "PartRec_aRBuPartial", uniqueId_, Neutral::gamma, 1.3962e-01,
          6.78e-03, Systematic::partRecBuPartialPdf, Sign::positive)),
      // -------------------- Correct ID BOX EFFs -------------------- //
      buDeltaCutEffBu2Dst0h_D0gamma_(nullptr),
      buDeltaCutEffBu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      buDeltaCutEffBu2Dst0h_D0pi0_(nullptr),
      buDeltaCutEffBu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      buDeltaCutEffMisRec_(nullptr),
      buDeltaCutEffBu2D0h_(nullptr),
      buDeltaCutEffPartRec_(nullptr),
      deltaCutEffBu2Dst0h_D0gamma_(nullptr),
      deltaCutEffBu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      deltaCutEffBu2Dst0h_D0pi0_(nullptr),
      deltaCutEffBu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      deltaCutEffMisRec_(nullptr),
      deltaCutEffBu2D0h_(nullptr),
      deltaCutEffPartRec_(nullptr),
      deltaPartialCutEffBu2Dst0h_D0gamma_(nullptr),
      deltaPartialCutEffBu2Dst0h_D0pi0_(nullptr),
      deltaPartialCutEffBu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      deltaPartialCutEffMisRec_(nullptr),
      deltaPartialCutEffBu2D0h_(nullptr),
      deltaPartialCutEffPartRec_(nullptr),
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
      // -------------------- CP Observables -------------------- //
      R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr) {
  if (Configuration::Get().blindFit() == true) {
    R_CP_Bu2Dst0h_D0gamma_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("R_CP_Bu2Dst0h_D0gamma_Blind", uniqueId_,
                                     Neutral::gamma, 0.902, -2, 2));
    R_CP_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("R_CP_Bu2Dst0h_D0gamma_" + ComposeName(uniqueId_, Neutral::gamma))
            .c_str(),
        0.3, *R_CP_Bu2Dst0h_D0gamma_Blind_));
    R_CP_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("R_CP_Bu2Dst0h_D0pi0_Blind", uniqueId_,
                                     Neutral::gamma, 1.138, -2, 2));
    R_CP_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("R_CP_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId_, Neutral::gamma))
            .c_str(),
        0.3, *R_CP_Bu2Dst0h_D0pi0_Blind_));
  } else {
    R_CP_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "R_CP_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma, 0.902, -2, 2));
    R_CP_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "R_CP_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma, 1.138, -2, 2));
  }

  std::map<std::string, double> mapBu2Dst0h_D0gamma;
  std::map<std::string, double> mapBu2Dst0h_D0gamma_FAVasSUP;
  std::map<std::string, double> mapBu2Dst0h_D0pi0;
  std::map<std::string, double> mapBu2Dst0h_D0pi0_FAVasSUP;
  std::map<std::string, double> mapBu2D0h;

  Configuration::Get().ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                                     mapBu2Dst0h_D0gamma, false);
  Configuration::Get().ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_D02pik,
                                     Bachelor::pi, mapBu2Dst0h_D0gamma_FAVasSUP,
                                     false);
  Configuration::Get().ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                                     mapBu2Dst0h_D0pi0, false);
  Configuration::Get().ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                                     mapBu2Dst0h_D0pi0_FAVasSUP, false);
  Configuration::Get().ReturnBoxEffs(Mode::Bu2D0pi, Bachelor::pi, mapBu2D0h,
                                     false);

  std::map<Mode, double> misRecModesMap = {
      {Mode::Bu2Dst0pi_D0pi0_WN, fracMisRec_Bu2Dst0h_D0pi0_WN_ / fracMisRec_},
      {Mode::Bu2Dst0pi_D0gamma_WN,
       fracMisRec_Bu2Dst0h_D0gamma_WN_ / fracMisRec_},
      {Mode::Bu2D0rho, fracMisRec_Bu2D0hst_ / fracMisRec_},
      {Mode::Bd2Dstpi, fracMisRec_Bd2Dsth_ / fracMisRec_}};

  std::map<std::string, double> mapMisRec;
  unsigned int it = 0;
  for (auto &m : misRecModesMap) {
    std::map<std::string, double> mapMisRecTmp;
    Configuration::Get().ReturnBoxEffs(m.first, Bachelor::pi, mapMisRecTmp,
                                       false);
    if (it == 0) {
      mapMisRec.insert(std::pair<std::string, double>(
          "buDeltaCutEff", mapMisRecTmp["buDeltaCutEff"] * m.second));
      mapMisRec.insert(std::pair<std::string, double>(
          "deltaCutEff", mapMisRecTmp["deltaCutEff"] * m.second));
      if (Configuration::Get().fitBuPartial() == true) {
        mapMisRec.insert(std::pair<std::string, double>(
            "deltaPartialCutEff",
            mapMisRecTmp["deltaPartialCutEff"] * m.second));
      }
    } else {
      mapMisRec["buDeltaCutEff"] += mapMisRecTmp["buDeltaCutEff"] * m.second;
      mapMisRec["deltaCutEff"] += mapMisRecTmp["deltaCutEff"] * m.second;
      if (Configuration::Get().fitBuPartial() == true) {
        mapMisRec["deltaPartialCutEff"] +=
            mapMisRecTmp["deltaPartialCutEff"] * m.second;
      }
    }
    ++it;
  }

  std::map<Mode, double> partRecModesMap = {
      {Mode::Bu2Dst0rho_D0pi0, fracPartRec_Bu2Dst0hst_D0pi0_ / fracPartRec_},
      {Mode::Bu2Dst0rho_D0gamma,
       fracPartRec_Bu2Dst0hst_D0gamma_ / fracPartRec_}};

  std::map<std::string, double> mapPartRec;
  it = 0;
  for (auto &m : partRecModesMap) {
    std::map<std::string, double> mapPartRecTmp;
    Configuration::Get().ReturnBoxEffs(m.first, Bachelor::pi, mapPartRecTmp,
                                       false);
    if (it == 0) {
      mapPartRec.insert(std::pair<std::string, double>(
          "buDeltaCutEff", mapPartRecTmp["buDeltaCutEff"] * m.second));
      mapPartRec.insert(std::pair<std::string, double>(
          "deltaCutEff", mapPartRecTmp["deltaCutEff"] * m.second));
      if (Configuration::Get().fitBuPartial() == true) {
        mapPartRec.insert(std::pair<std::string, double>(
            "deltaPartialCutEff",
            mapPartRecTmp["deltaPartialCutEff"] * m.second));
      }
    } else {
      mapPartRec["buDeltaCutEff"] += mapPartRecTmp["buDeltaCutEff"] * m.second;
      mapPartRec["deltaCutEff"] += mapPartRecTmp["deltaCutEff"] * m.second;
      if (Configuration::Get().fitBuPartial() == true) {
        mapPartRec["deltaPartialCutEff"] +=
            mapPartRecTmp["deltaPartialCutEff"] * m.second;
      }
    }
    ++it;
  }

  buDeltaCutEffBu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffBu2Dst0h_D0gamma", uniqueId_, Neutral::gamma,
          mapBu2Dst0h_D0gamma["buDeltaCutEff"],
          mapBu2Dst0h_D0gamma["buDeltaCutEffErr"], Systematic::buDeltaCutEffs,
          Sign::positive));
  buDeltaCutEffBu2Dst0h_D0gamma_FAVasSUP_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffBu2Dst0h_D0gamma_FAVasSUP", uniqueId_, Neutral::gamma,
          mapBu2Dst0h_D0gamma_FAVasSUP["buDeltaCutEff"],
          mapBu2Dst0h_D0gamma_FAVasSUP["buDeltaCutEffErr"],
          Systematic::buDeltaCutEffs, Sign::positive));
  buDeltaCutEffBu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffBu2Dst0h_D0pi0", uniqueId_, Neutral::gamma,
          mapBu2Dst0h_D0pi0["buDeltaCutEff"],
          mapBu2Dst0h_D0pi0["buDeltaCutEffErr"], Systematic::buDeltaCutEffs,
          Sign::positive));
  buDeltaCutEffBu2Dst0h_D0pi0_FAVasSUP_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffBu2Dst0h_D0pi0_FAVasSUP", uniqueId_, Neutral::gamma,
          mapBu2Dst0h_D0pi0_FAVasSUP["buDeltaCutEff"],
          mapBu2Dst0h_D0pi0_FAVasSUP["buDeltaCutEffErr"],
          Systematic::buDeltaCutEffs, Sign::positive));
  buDeltaCutEffBu2D0h_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "buDeltaCutEffBu2D0h", uniqueId_, Neutral::gamma,
      mapBu2D0h["buDeltaCutEff"], mapBu2D0h["buDeltaCutEffErr"], Systematic::NA,
      Sign::positive));
  buDeltaCutEffMisRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "buDeltaCutEffMisRec", uniqueId_, Neutral::gamma,
      mapMisRec["buDeltaCutEff"], mapMisRec["buDeltaCutEffErr"],
      Systematic::buDeltaCutEffs, Sign::positive));
  buDeltaCutEffPartRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "buDeltaCutEffPartRec", uniqueId_, Neutral::gamma,
      mapPartRec["buDeltaCutEff"], mapPartRec["buDeltaCutEffErr"],
      Systematic::buDeltaCutEffs, Sign::positive));

  deltaCutEffBu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffBu2Dst0h_D0gamma", uniqueId_, Neutral::gamma,
          mapBu2Dst0h_D0gamma["deltaCutEff"],
          mapBu2Dst0h_D0gamma["deltaCutEffErr"], Systematic::deltaCutEffs,
          Sign::positive));
  deltaCutEffBu2Dst0h_D0gamma_FAVasSUP_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffBu2Dst0h_D0gamma_FAVasSUP", uniqueId_, Neutral::gamma,
          mapBu2Dst0h_D0gamma_FAVasSUP["deltaCutEff"],
          mapBu2Dst0h_D0gamma_FAVasSUP["deltaCutEffErr"],
          Systematic::deltaCutEffs, Sign::positive));
  deltaCutEffBu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffBu2Dst0h_D0pi0", uniqueId_, Neutral::gamma,
          mapBu2Dst0h_D0pi0["deltaCutEff"], mapBu2Dst0h_D0pi0["deltaCutEffErr"],
          Systematic::deltaCutEffs, Sign::positive));
  deltaCutEffBu2Dst0h_D0pi0_FAVasSUP_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffBu2Dst0h_D0pi0_FAVasSUP", uniqueId_, Neutral::gamma,
          mapBu2Dst0h_D0pi0_FAVasSUP["deltaCutEff"],
          mapBu2Dst0h_D0pi0_FAVasSUP["deltaCutEffErr"],
          Systematic::deltaCutEffs, Sign::positive));
  deltaCutEffBu2D0h_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "deltaCutEffBu2D0h", uniqueId_, Neutral::gamma, mapBu2D0h["deltaCutEff"],
      mapBu2D0h["deltaCutEffErr"], Systematic::NA, Sign::positive));
  deltaCutEffMisRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "deltaCutEffMisRec", uniqueId_, Neutral::gamma, mapMisRec["deltaCutEff"],
      mapMisRec["deltaCutEffErr"], Systematic::deltaCutEffs, Sign::positive));
  deltaCutEffPartRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "deltaCutEffPartRec", uniqueId_, Neutral::gamma, mapPartRec["deltaCutEff"],
      mapPartRec["deltaCutEffErr"], Systematic::deltaCutEffs, Sign::positive));

  if (Configuration::Get().fitBuPartial() == true) {
    deltaPartialCutEffBu2Dst0h_D0gamma_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffBu2Dst0h_D0gamma", uniqueId_, Neutral::gamma,
            mapBu2Dst0h_D0gamma["deltaPartialCutEff"],
            mapBu2Dst0h_D0gamma["deltaPartialCutEffErr"],
            Systematic::deltaPartialCutEffs, Sign::positive));
    deltaPartialCutEffBu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffBu2Dst0h_D0pi0", uniqueId_, Neutral::gamma,
            mapBu2Dst0h_D0pi0["deltaPartialCutEff"],
            mapBu2Dst0h_D0pi0["deltaPartialCutEffErr"],
            Systematic::deltaPartialCutEffs, Sign::positive));
    deltaPartialCutEffBu2Dst0h_D0pi0_FAVasSUP_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffBu2Dst0h_D0pi0_FAVasSUP", uniqueId_,
            Neutral::gamma, mapBu2Dst0h_D0pi0_FAVasSUP["deltaPartialCutEff"],
            mapBu2Dst0h_D0pi0_FAVasSUP["deltaPartialCutEffErr"],
            Systematic::deltaPartialCutEffs, Sign::positive));
    deltaPartialCutEffBu2D0h_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffBu2D0h", uniqueId_, Neutral::gamma,
            mapBu2D0h["deltaPartialCutEff"], mapBu2D0h["deltaPartialCutEffErr"],
            Systematic::NA, Sign::positive));
    deltaPartialCutEffMisRec_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffMisRec", uniqueId_, Neutral::gamma,
            mapMisRec["deltaPartialCutEff"], mapMisRec["deltaPartialCutEffErr"],
            Systematic::deltaPartialCutEffs, Sign::positive));
    deltaPartialCutEffPartRec_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffPartRec", uniqueId_, Neutral::gamma,
            mapPartRec["deltaPartialCutEff"],
            mapPartRec["deltaPartialCutEffErr"],
            Systematic::deltaPartialCutEffs, Sign::positive));
  }
}
