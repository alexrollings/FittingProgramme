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
      Bu2Dst0h_D0gamma_sigmaDelta_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0gamma_sigmaDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, 2, 15)),
      Bu2Dst0h_D0gamma_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::gammaDeltaTails, Sign::same)),
      Bu2Dst0h_D0gamma_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::gammaDeltaTails, Sign::same)),
      Bu2Dst0h_D0gamma_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a2Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::gammaDeltaTails, Sign::same)),
      Bu2Dst0h_D0gamma_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n2Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, Systematic::gammaDeltaTails, Sign::same)),
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
          Mode::Bu2Dst0pi_D0gamma, Systematic::gammaDeltaFrac, Sign::same)),
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
      Bu2Dst0h_D0gamma_meanBu_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0gamma_meanBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma, 5275, 5285)),
      Bu2Dst0h_D0gamma_KpiSigmaBu_(
          Params::Get().CreateFloating("Bu2Dst0h_D0gamma_KpiSigmaBu", uniqueId_,
                                       Neutral::gamma, 0.95, 0.5, 1.5)),
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
      Bu2Dst0h_D0pi0_sigmaDelta_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_sigmaDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, 5, 15)),
      Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::same)),
      Bu2Dst0h_D0pi0_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::same)),
      Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::same)),
      Bu2Dst0h_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::same)),
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
          "Bu2Dst0h_D0pi0_fracPdf1Delta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaFrac, Sign::same)),
      pdfDelta_Bu2Dst0h_D0pi0_(
          ("pdfDelta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          *Bu2Dst0h_D0pi0_fracPdf1Delta_),
      Bu2Dst0h_D0pi0_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_meanBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::crossFeedBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_sigmaBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::crossFeedBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_KpiSigmaBu_(nullptr),
      Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::crossFeedBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_a2Bu_(nullptr),
      Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::crossFeedBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_n2Bu_(nullptr),
      Bu2Dst0h_D0pi0_fracPdf1Bu_(nullptr),
      Bu2Dst0h_D0pi0_mean1BuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_mean1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, 5270, 5290)),
      Bu2Dst0h_D0pi0_meanOffset31BuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_meanOffset31BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, 10, 50)),
      Bu2Dst0h_D0pi0_mean3BuPartial_(
          ("Bu2Dst0h_D0pi0_mean3BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "@0+@1",
          RooArgSet(*Bu2Dst0h_D0pi0_mean1BuPartial_,
                    *Bu2Dst0h_D0pi0_meanOffset31BuPartial_)),
      Bu2Dst0h_D0pi0_KpiSigmaBuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_KpiSigmaBuPartial", uniqueId_, Neutral::gamma, 0.95,
          0.5, 1.5)),
      Bu2Dst0h_D0pi0_sigmaRatio21BuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_sigmaRatio21BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, 1, 2.5)),
      Bu2Dst0h_D0pi0_sigmaRatio31BuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_sigmaRatio31BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, 0.2, 1.5)),
      Bu2Dst0h_D0pi0_a1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0BuPartialTails, Sign::same)),
      Bu2Dst0h_D0pi0_n1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0BuPartialTails, Sign::same)),
      Bu2Dst0h_D0pi0_a2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0BuPartialTails, Sign::same)),
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
      pdf1Delta_Bu2Dst0h_D0gamma_WN_(
          ("pdf1Delta_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0gamma_meanDelta_,
          *Bu2Dst0h_D0gamma_sigmaDelta_, *Bu2Dst0h_D0gamma_a1Delta_,
          *Bu2Dst0h_D0gamma_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0gamma_WN_(
          ("pdf2Delta_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0gamma_meanDelta_,
          *Bu2Dst0h_D0gamma_sigmaDelta_, *Bu2Dst0h_D0gamma_a2Delta_,
          *Bu2Dst0h_D0gamma_n2Delta_),
      pdfPeakDelta_Bu2Dst0h_D0gamma_WN_(
          ("pdfPeakDelta_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0gamma_WN_,
                     pdf2Delta_Bu2Dst0h_D0gamma_WN_),
          *Bu2Dst0h_D0gamma_fracPdf1Delta_),
      Bu2Dst0h_D0gamma_WN_thresholdDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_thresholdDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNDeltaPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_aDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_aDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNDeltaPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_bDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_bDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNDeltaPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_cDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_cDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNDeltaPdf, Sign::same)),
      pdfFlatDelta_Bu2Dst0h_D0gamma_WN_(
          ("pdfFlatDelta_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0gamma_WN_thresholdDelta_, *Bu2Dst0h_D0gamma_WN_cDelta_,
          *Bu2Dst0h_D0gamma_WN_aDelta_, *Bu2Dst0h_D0gamma_WN_bDelta_),
      Bu2Dst0h_D0gamma_WN_fracPdfPeakDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_fracPdfPeakDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNDeltaPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_meanDelta_(nullptr),
      Bu2Dst0h_D0gamma_WN_sigmaDelta_(nullptr),
      Bu2Dst0h_D0gamma_WN_a1Delta_(nullptr),
      Bu2Dst0h_D0gamma_WN_n1Delta_(nullptr),
      pdfDelta_Bu2Dst0h_D0gamma_WN_(
          new RooAddPdf(("pdfDelta_Bu2Dst0h_D0gamma_WN_" +
                         ComposeName(uniqueId_, Neutral::gamma))
                            .c_str(),
                        "",
                        RooArgList(pdfPeakDelta_Bu2Dst0h_D0gamma_WN_,
                                   pdfFlatDelta_Bu2Dst0h_D0gamma_WN_),
                        *Bu2Dst0h_D0gamma_WN_fracPdfPeakDelta_)),
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
      Bu2Dst0h_D0gamma_WN_KpiSigmaBu_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0gamma_WN_KpiSigmaBu", uniqueId_, Neutral::gamma, 0.95,
          0.5, 1.5)),
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
      // Bu2Dst0h_D0pi0_WN_meanDelta_(nullptr),
      // Bu2Dst0h_D0pi0_WN_sigmaDelta_(nullptr),
      // Bu2Dst0h_D0pi0_WN_a1Delta_(nullptr),
      // Bu2Dst0h_D0pi0_WN_n1Delta_(nullptr),
      // Bu2Dst0h_D0pi0_WN_a2Delta_(nullptr),
      // Bu2Dst0h_D0pi0_WN_n2Delta_(nullptr),
      pdf1Delta_Bu2Dst0h_D0pi0_WN_(),
      pdf2Delta_Bu2Dst0h_D0pi0_WN_(),
      // Bu2Dst0h_D0pi0_WN_fracPdf1Delta_(nullptr),
      pdfPeakDelta_Bu2Dst0h_D0pi0_WN_(),
      Bu2Dst0h_D0pi0_WN_thresholdDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_thresholdDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNDeltaPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_aDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_aDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNDeltaPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_bDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_bDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNDeltaPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_cDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_cDelta", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNDeltaPdf, Sign::same)),
      pdfFlatDelta_Bu2Dst0h_D0pi0_WN_(),
      Bu2Dst0h_D0pi0_WN_fracPdfPeakDelta_(nullptr),
      pdfDelta_Bu2Dst0h_D0pi0_WN_(new RooDstD0BG(
          ("pdfDelta_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0pi0_WN_thresholdDelta_, *Bu2Dst0h_D0pi0_WN_cDelta_,
          *Bu2Dst0h_D0pi0_WN_aDelta_, *Bu2Dst0h_D0pi0_WN_bDelta_)),
      Bu2Dst0h_D0pi0_WN_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_meanBu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_KpiSigmaBu_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_WN_KpiSigmaBu", uniqueId_, Neutral::gamma, 0.95, 0.5,
          1.5)),
      Bu2Dst0h_D0pi0_WN_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_a1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_n1Bu", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_mean1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_mean1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
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
      Bu2Dst0h_D0pi0_WN_KpiSigmaBuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_WN_KpiSigmaBuPartial", uniqueId_, Neutral::gamma,
          0.95, 0.5, 1.5)),
      Bu2Dst0h_D0pi0_WN_sigmaRatio21BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_sigmaRatio21BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_sigmaRatio31BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_sigmaRatio31BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_a1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_a1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_n1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_n1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_a2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_a2BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_n2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_n2BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_fracPdf1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_fracPdf1BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
      Bu2Dst0h_D0pi0_WN_fracPdf2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_fracPdf2BuPartial", uniqueId_, Neutral::gamma,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf, Sign::same)),
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
      // -------------------- MIS-REC -------------------- //
      MisRec_thresholdDelta_(Params::Get().CreateFixed(
          "MisRec_thresholdDelta", uniqueId_, Neutral::gamma, 4.9426e+01,
          7.76e-01, Systematic::misRecDeltaPdf, Sign::same)),
      MisRec_aDelta_(Params::Get().CreateFloating(
          "MisRec_aDelta", uniqueId_, Neutral::gamma, 1.1334e+00, -5, 5)),
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
      // -------------------- Global Fractions: WN -------------------- //
      globalFrac_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFloating(
          "globalFrac_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::gamma,
          // ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, Neutral::gamma,
          // Bachelor::pi,
          //              Efficiency::mcEff) /
          //     ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::gamma,
          //     Bachelor::pi,
          //                  Efficiency::mcEff),
          2, -5, 5)),
      globalFrac_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFloating(
          "globalFrac_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::gamma,
          // ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN, Neutral::gamma,
          // Bachelor::pi,
          //              Efficiency::mcEff) /
          //     ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma, Neutral::gamma,
          //     Bachelor::pi,
          //                  Efficiency::mcEff),
          2, -5, 5)),
      // -------------------- CP Observables -------------------- //
      R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_WN_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_WN_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_WN_(nullptr) {
  std::cout << "\n\n\n"
            << ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, Neutral::gamma,
                            Bachelor::pi, Efficiency::mcEff)
            << "\n";
  std::cout << ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::gamma, Bachelor::pi,
                            Efficiency::mcEff)
            << "\n\n\n";
  if (Configuration::Get().blindFit() == true) {
    R_CP_Bu2Dst0h_D0gamma_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("R_CP_Bu2Dst0h_D0gamma_Blind", uniqueId_,
                                     Neutral::gamma, 0.902, -2, 2));
    R_CP_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("R_CP_Bu2Dst0h_D0pi0_Blind", uniqueId_,
                                     Neutral::gamma, 1.138, -2, 2));
    R_CP_Bu2Dst0h_D0gamma_WN_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("R_CP_Bu2Dst0h_D0gamma_WN_Blind",
                                     uniqueId_, Neutral::gamma, 0.902, -2, 2));
    R_CP_Bu2Dst0h_D0pi0_WN_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("R_CP_Bu2Dst0h_D0pi0_WN_Blind", uniqueId_,
                                     Neutral::gamma, 1.138, -2, 2));
    R_CP_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("R_CP_Bu2Dst0h_D0gamma_" + ComposeName(uniqueId_, Neutral::gamma))
            .c_str(),
        0.3, *R_CP_Bu2Dst0h_D0gamma_Blind_));
    R_CP_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("R_CP_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId_, Neutral::gamma))
            .c_str(),
        0.3, *R_CP_Bu2Dst0h_D0pi0_Blind_));
    R_CP_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("R_CP_Bu2Dst0h_D0gamma_WN_" + ComposeName(uniqueId_, Neutral::gamma))
            .c_str(),
        0.3, *R_CP_Bu2Dst0h_D0gamma_WN_Blind_));
    R_CP_Bu2Dst0h_D0pi0_WN_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("R_CP_Bu2Dst0h_D0pi0_WN_" + ComposeName(uniqueId_, Neutral::gamma))
            .c_str(),
        0.3, *R_CP_Bu2Dst0h_D0pi0_WN_Blind_));
  } else {
    R_CP_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "R_CP_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma, 0.902, -2, 2));
    R_CP_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "R_CP_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma, 1.138, -2, 2));
    R_CP_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("R_CP_Bu2Dst0h_D0gamma_WN", uniqueId_,
                                     Neutral::gamma, 0.902, -2, 2));
    R_CP_Bu2Dst0h_D0pi0_WN_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "R_CP_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::gamma, 1.138, -2, 2));
  }

  std::map<std::string, double> mapBu2Dst0h_D0gamma;
  std::map<std::string, double> mapBu2Dst0h_D0gamma_FAVasSUP;
  std::map<std::string, double> mapBu2Dst0h_D0pi0;
  std::map<std::string, double> mapBu2Dst0h_D0pi0_FAVasSUP;
  std::map<std::string, double> mapBu2D0h;

  ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi, mapBu2Dst0h_D0gamma,
                false);
  ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi,
                mapBu2Dst0h_D0gamma_FAVasSUP, false);
  ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi, mapBu2Dst0h_D0pi0, false);
  ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi,
                mapBu2Dst0h_D0pi0_FAVasSUP, false);
  ReturnBoxEffs(Mode::Bu2D0pi, Bachelor::pi, mapBu2D0h, false);

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
    ReturnBoxEffs(m.first, Bachelor::pi, mapMisRecTmp, false);
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
    ReturnBoxEffs(m.first, Bachelor::pi, mapPartRecTmp, false);
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
          Sign::same));
  buDeltaCutEffBu2Dst0h_D0gamma_FAVasSUP_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffBu2Dst0h_D0gamma_FAVasSUP", uniqueId_, Neutral::gamma,
          mapBu2Dst0h_D0gamma_FAVasSUP["buDeltaCutEff"],
          mapBu2Dst0h_D0gamma_FAVasSUP["buDeltaCutEffErr"],
          Systematic::buDeltaCutEffs, Sign::same));
  buDeltaCutEffBu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffBu2Dst0h_D0pi0", uniqueId_, Neutral::gamma,
          mapBu2Dst0h_D0pi0["buDeltaCutEff"],
          mapBu2Dst0h_D0pi0["buDeltaCutEffErr"], Systematic::buDeltaCutEffs,
          Sign::same));
  buDeltaCutEffBu2Dst0h_D0pi0_FAVasSUP_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffBu2Dst0h_D0pi0_FAVasSUP", uniqueId_, Neutral::gamma,
          mapBu2Dst0h_D0pi0_FAVasSUP["buDeltaCutEff"],
          mapBu2Dst0h_D0pi0_FAVasSUP["buDeltaCutEffErr"],
          Systematic::buDeltaCutEffs, Sign::same));
  buDeltaCutEffBu2D0h_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "buDeltaCutEffBu2D0h", uniqueId_, Neutral::gamma,
      mapBu2D0h["buDeltaCutEff"], mapBu2D0h["buDeltaCutEffErr"], Systematic::NA,
      Sign::same));
  buDeltaCutEffMisRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "buDeltaCutEffMisRec", uniqueId_, Neutral::gamma,
      mapMisRec["buDeltaCutEff"], mapMisRec["buDeltaCutEffErr"],
      Systematic::buDeltaCutEffs, Sign::same));
  buDeltaCutEffPartRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "buDeltaCutEffPartRec", uniqueId_, Neutral::gamma,
      mapPartRec["buDeltaCutEff"], mapPartRec["buDeltaCutEffErr"],
      Systematic::buDeltaCutEffs, Sign::same));

  deltaCutEffBu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffBu2Dst0h_D0gamma", uniqueId_, Neutral::gamma,
          mapBu2Dst0h_D0gamma["deltaCutEff"],
          mapBu2Dst0h_D0gamma["deltaCutEffErr"], Systematic::deltaCutEffs,
          Sign::same));
  deltaCutEffBu2Dst0h_D0gamma_FAVasSUP_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffBu2Dst0h_D0gamma_FAVasSUP", uniqueId_, Neutral::gamma,
          mapBu2Dst0h_D0gamma_FAVasSUP["deltaCutEff"],
          mapBu2Dst0h_D0gamma_FAVasSUP["deltaCutEffErr"],
          Systematic::deltaCutEffs, Sign::same));
  deltaCutEffBu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffBu2Dst0h_D0pi0", uniqueId_, Neutral::gamma,
          mapBu2Dst0h_D0pi0["deltaCutEff"], mapBu2Dst0h_D0pi0["deltaCutEffErr"],
          Systematic::deltaCutEffs, Sign::same));
  deltaCutEffBu2Dst0h_D0pi0_FAVasSUP_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffBu2Dst0h_D0pi0_FAVasSUP", uniqueId_, Neutral::gamma,
          mapBu2Dst0h_D0pi0_FAVasSUP["deltaCutEff"],
          mapBu2Dst0h_D0pi0_FAVasSUP["deltaCutEffErr"],
          Systematic::deltaCutEffs, Sign::same));
  deltaCutEffBu2D0h_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "deltaCutEffBu2D0h", uniqueId_, Neutral::gamma, mapBu2D0h["deltaCutEff"],
      mapBu2D0h["deltaCutEffErr"], Systematic::NA, Sign::same));
  deltaCutEffMisRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "deltaCutEffMisRec", uniqueId_, Neutral::gamma, mapMisRec["deltaCutEff"],
      mapMisRec["deltaCutEffErr"], Systematic::deltaCutEffs, Sign::same));
  deltaCutEffPartRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "deltaCutEffPartRec", uniqueId_, Neutral::gamma,
      mapPartRec["deltaCutEff"], mapPartRec["deltaCutEffErr"],
      Systematic::deltaCutEffs, Sign::same));

  if (Configuration::Get().fitBuPartial() == true) {
    deltaPartialCutEffBu2Dst0h_D0gamma_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffBu2Dst0h_D0gamma", uniqueId_, Neutral::gamma,
            mapBu2Dst0h_D0gamma["deltaPartialCutEff"],
            mapBu2Dst0h_D0gamma["deltaPartialCutEffErr"],
            Systematic::deltaPartialCutEffs, Sign::same));
    deltaPartialCutEffBu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffBu2Dst0h_D0pi0", uniqueId_, Neutral::gamma,
            mapBu2Dst0h_D0pi0["deltaPartialCutEff"],
            mapBu2Dst0h_D0pi0["deltaPartialCutEffErr"],
            Systematic::deltaPartialCutEffs, Sign::same));
    deltaPartialCutEffBu2Dst0h_D0pi0_FAVasSUP_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffBu2Dst0h_D0pi0_FAVasSUP", uniqueId_,
            Neutral::gamma, mapBu2Dst0h_D0pi0_FAVasSUP["deltaPartialCutEff"],
            mapBu2Dst0h_D0pi0_FAVasSUP["deltaPartialCutEffErr"],
            Systematic::deltaPartialCutEffs, Sign::same));
    deltaPartialCutEffBu2D0h_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffBu2D0h", uniqueId_, Neutral::gamma,
            mapBu2D0h["deltaPartialCutEff"], mapBu2D0h["deltaPartialCutEffErr"],
            Systematic::NA, Sign::same));
    deltaPartialCutEffMisRec_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffMisRec", uniqueId_, Neutral::gamma,
            mapMisRec["deltaPartialCutEff"], mapMisRec["deltaPartialCutEffErr"],
            Systematic::deltaPartialCutEffs, Sign::same));
    deltaPartialCutEffPartRec_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffPartRec", uniqueId_, Neutral::gamma,
            mapPartRec["deltaPartialCutEff"],
            mapPartRec["deltaPartialCutEffErr"],
            Systematic::deltaPartialCutEffs, Sign::same));
  }
}
