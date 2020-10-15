#include "NeutralBachelorVars.h"
#include "Params.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- PDF SHAPES -------------------- //
    // -------------------- Bu2Dst0h_D0pi0 -------------------- //
    : uniqueId_(uniqueId),
      Bu2Dst0h_D0pi0_sigmaDelta_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_sigmaDelta", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0pi_D0pi0, 0.1, 3)),
      pdf1Delta_Bu2Dst0h_D0pi0_(
          ("pdf1Delta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_meanDelta(),
          *Bu2Dst0h_D0pi0_sigmaDelta_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_a1Delta(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_n1Delta()),
      pdf2Delta_Bu2Dst0h_D0pi0_(
          ("pdf2Delta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_meanDelta(),
          *Bu2Dst0h_D0pi0_sigmaDelta_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_a2Delta(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_n2Delta()),
      pdfDelta_Bu2Dst0h_D0pi0_(
          ("pdfDelta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          NeutralVars<Neutral::pi0>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_fracPdf1Delta()),
      Bu2Dst0h_D0pi0_sigma1Bu_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_sigma1Bu", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0pi_D0pi0, 17, 25)),
      Bu2Dst0h_D0pi0_sigma2Bu_(),
      pdf1Bu_Bu2Dst0h_D0pi0_(
          ("pdf1Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_mean1Bu(),
          *Bu2Dst0h_D0pi0_sigma1Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0pi0_(
          ("pdf2Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_mean1Bu(),
          *Bu2Dst0h_D0pi0_sigma1Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_a2Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_n2Bu()),
      pdfBu_Bu2Dst0h_D0pi0_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0h_D0pi0_, pdf2Bu_Bu2Dst0h_D0pi0_),
          NeutralVars<Neutral::pi0>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_fracPdf1Bu())),
      Bu2Dst0h_D0pi0_sigma1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_sigma2BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_sigma3BuPartial_(nullptr),
      pdf1BuPartial_Bu2Dst0h_D0pi0_(),
      pdf2BuPartial_Bu2Dst0h_D0pi0_(),
      pdf3BuPartial_Bu2Dst0h_D0pi0_(),
      pdfBuPartial_Bu2Dst0h_D0pi0_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0pi0_meanDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_meanDelta", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfDelta,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_sigmaDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigmaDelta", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfDelta,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_n1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1Delta", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a2Delta", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n2Delta", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfDelta, Sign::same)),
      pdf1Delta_misId_Bu2Dst0h_D0pi0_(
          ("pdf1Delta_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0pi0_meanDelta_, *misId_Bu2Dst0h_D0pi0_sigmaDelta_,
          *misId_Bu2Dst0h_D0pi0_a1Delta_, *misId_Bu2Dst0h_D0pi0_n1Delta_),
      pdf2Delta_misId_Bu2Dst0h_D0pi0_(
          ("pdf2Delta_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0pi0_meanDelta_, *misId_Bu2Dst0h_D0pi0_sigmaDelta_,
          *misId_Bu2Dst0h_D0pi0_a2Delta_, *misId_Bu2Dst0h_D0pi0_n2Delta_),
      misId_Bu2Dst0h_D0pi0_fracPdf1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_fracPdf1Delta", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfDelta,
          Sign::same)),
      pdfDelta_misId_Bu2Dst0h_D0pi0_(
          new RooAddPdf(("pdfDelta_misId_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                            .c_str(),
                        "",
                        RooArgSet(pdf1Delta_misId_Bu2Dst0h_D0pi0_,
                                  pdf2Delta_misId_Bu2Dst0h_D0pi0_),
                        *misId_Bu2Dst0h_D0pi0_fracPdf1Delta_)),
      misId_Bu2Dst0h_D0pi0_mean1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_mean1Bu", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0pi0_mean2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_mean2Bu", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0pi0_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma1Bu", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_sigma2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma2Bu", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_a1Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_n1Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_a2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a2Bu", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0pi0_n2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n2Bu", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfBu, Sign::same)),
      pdf1Bu_misId_Bu2Dst0h_D0pi0_(new RooGaussian(
          ("pdf1Bu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_mean1Bu_, *misId_Bu2Dst0h_D0pi0_sigma1Bu_)),
      pdf2Bu_misId_Bu2Dst0h_D0pi0_(
          ("pdf2Bu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_mean2Bu_, *misId_Bu2Dst0h_D0pi0_sigma2Bu_,
          *misId_Bu2Dst0h_D0pi0_a2Bu_, *misId_Bu2Dst0h_D0pi0_n2Bu_),
      misId_Bu2Dst0h_D0pi0_fracPdf1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_fracPdf1Bu", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfBu,
          Sign::same)),
      pdfBu_misId_Bu2Dst0h_D0pi0_(
          new RooAddPdf(("pdfBu_misId_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                            .c_str(),
                        "",
                        RooArgSet(*pdf1Bu_misId_Bu2Dst0h_D0pi0_,
                                  pdf2Bu_misId_Bu2Dst0h_D0pi0_),
                        *misId_Bu2Dst0h_D0pi0_fracPdf1Bu_)),
      misId_Bu2Dst0h_D0pi0_mean1BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_mean2BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_sigma1BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_sigma2BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_a2BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_a1BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_n2BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_n1BuPartial_(nullptr),
      pdf1BuPartial_misId_Bu2Dst0h_D0pi0_(),
      pdf2BuPartial_misId_Bu2Dst0h_D0pi0_(),
      misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_(nullptr),
      pdfBuPartial_misId_Bu2Dst0h_D0pi0_(nullptr),
      // -------------------- Bu2Dst0h_D0gamma -------------------- //
      Bu2Dst0h_D0gamma_sigmaDelta_(nullptr),
      pdf1Delta_Bu2Dst0h_D0gamma_(),
      pdf2Delta_Bu2Dst0h_D0gamma_(),
      pdfDelta_Bu2Dst0h_D0gamma_(nullptr),
      Bu2Dst0h_D0gamma_sigmaBu_(nullptr),
      pdf1Bu_Bu2Dst0h_D0gamma_(),
      pdf2Bu_Bu2Dst0h_D0gamma_(),
      pdfBu_Bu2Dst0h_D0gamma_(nullptr),
      pdfBuPartial_Bu2Dst0h_D0gamma_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_meanBu_(nullptr),
      misId_Bu2Dst0h_D0gamma_sigmaBu_(nullptr),
      misId_Bu2Dst0h_D0gamma_a1Bu_(nullptr),
      misId_Bu2Dst0h_D0gamma_a2Bu_(nullptr),
      misId_Bu2Dst0h_D0gamma_n1Bu_(nullptr),
      misId_Bu2Dst0h_D0gamma_n2Bu_(nullptr),
      pdf1Bu_misId_Bu2Dst0h_D0gamma_(),
      pdf2Bu_misId_Bu2Dst0h_D0gamma_(),
      misId_Bu2Dst0h_D0gamma_fracPdf1Bu_(nullptr),
      pdfBu_misId_Bu2Dst0h_D0gamma_(nullptr),
      // -------------------- Bu2Dst0h_D0pi0_WN -------------------- //
      Bu2Dst0h_D0pi0_WN_aDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_aDelta", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNDeltaPdf, Sign::none)),
      // Bu2Dst0h_D0pi0_WN_aDelta_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_WN_aDelta", uniqueId_, Neutral::pi0, Bachelor::pi,
      //     -2.8370e+00, 1.20e-01, Systematic::pi0WNDeltaPdf, Sign::none)),
      // Bu2Dst0h_D0pi0_WN_aDelta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_aDelta", uniqueId_, Neutral::pi0, Bachelor::pi,
      //     Mode::Bu2Dst0pi_D0pi0_WN, -10, 10)),
      Bu2Dst0h_D0pi0_WN_bDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_bDelta", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNDeltaPdf, Sign::none)),
      // Bu2Dst0h_D0pi0_WN_sigmaBu_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_WN_sigmaBu", uniqueId_, Neutral::pi0, Bachelor::pi,
      //     Bachelor::pi, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf,
      //     Sign::same)),
      pdfDelta_Bu2Dst0h_D0pi0_WN_(
          ("pdfDelta_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_thresholdDelta(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_cDelta(),
          *Bu2Dst0h_D0pi0_WN_aDelta_, *Bu2Dst0h_D0pi0_WN_bDelta_),
      // Bu2Dst0h_D0pi0_WN_sigma1Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_sigma1Bu", uniqueId_, Neutral::pi0,
      //     Bachelor::pi, Mode::Bu2Dst0pi_D0pi0_WN, 40, 70)),
      Bu2Dst0h_D0pi0_WN_sigma1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_sigma1Bu", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::same)),
      // Bu2Dst0h_D0pi0_WN_sigma1Bu_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_WN_sigma1Bu", uniqueId_, Neutral::pi0,
      //     Bachelor::pi, 6.3682e+01, 9.94e-01, Systematic::pi0WNBuPdf,
      //     Sign::same)),
      Bu2Dst0h_D0pi0_WN_sigma2Bu_(nullptr),
      pdf1Bu_Bu2Dst0h_D0pi0_WN_(),
      pdf2Bu_Bu2Dst0h_D0pi0_WN_(),
      pdfBu_Bu2Dst0h_D0pi0_WN_(new RooCBShape(
          ("pdfBu_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_mean1Bu(),
          *Bu2Dst0h_D0pi0_WN_sigma1Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_n1Bu())),
      Bu2Dst0h_D0pi0_WN_sigma1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_WN_sigma2BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_WN_sigma3BuPartial_(nullptr),
      pdf1BuPartial_Bu2Dst0h_D0pi0_WN_(),
      pdf2BuPartial_Bu2Dst0h_D0pi0_WN_(),
      pdf3BuPartial_Bu2Dst0h_D0pi0_WN_(),
      pdfBuPartial_Bu2Dst0h_D0pi0_WN_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0pi0_WN_thresholdDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_thresholdDelta", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::misIdPi0WNPiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_aDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_aDelta", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::misIdPi0WNPiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_bDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_bDelta", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::misIdPi0WNPiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_cDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_cDelta", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::misIdPi0WNPiPdfDelta, Sign::same)),
      pdfDelta_misId_Bu2Dst0h_D0pi0_WN_(
          ("pdfDelta_misId_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0pi0_WN_thresholdDelta_,
          *misId_Bu2Dst0h_D0pi0_WN_cDelta_, *misId_Bu2Dst0h_D0pi0_WN_aDelta_,
          *misId_Bu2Dst0h_D0pi0_WN_bDelta_),
      misId_Bu2Dst0h_D0pi0_WN_mean1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_mean1Bu", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN, Systematic::misIdPi0WNPiPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_mean2Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_mean3Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_sigma1Bu", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN, Systematic::misIdPi0WNPiPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_sigma2Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_sigma3Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_a1Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_n1Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_a2Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_n2Bu_(nullptr),
      pdf1Bu_misId_Bu2Dst0h_D0pi0_WN_(),
      pdf2Bu_misId_Bu2Dst0h_D0pi0_WN_(nullptr),
      pdf3Bu_misId_Bu2Dst0h_D0pi0_WN_(),
      misId_Bu2Dst0h_D0pi0_WN_fracPdf1Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_fracPdf2Bu_(nullptr),
      pdfBu_misId_Bu2Dst0h_D0pi0_WN_(
          new RooGaussian(("pdfBu_misId_Bu2Dst0h_D0pi0_WN_" +
                           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                              .c_str(),
                          "", Configuration::Get().buDeltaMass(),
                          *misId_Bu2Dst0h_D0pi0_WN_mean1Bu_,
                          *misId_Bu2Dst0h_D0pi0_WN_sigma1Bu_)),
      misId_Bu2Dst0h_D0pi0_WN_meanBuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_sigmaBuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_a1BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_n1BuPartial_(nullptr),
      pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN_(),
      // -------------------- Bu2Dst0h_D0gamma_WN -------------------- //
      Bu2Dst0h_D0gamma_WN_sigma1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_sigma1Bu", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNBuPdf, Sign::same)),
      // Bu2Dst0h_D0gamma_WN_sigma1Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0gamma_WN_sigma1Bu", uniqueId_, Neutral::pi0,
      //     Bachelor::pi, Mode::Bu2Dst0pi_D0gamma_WN, 70, 90)),
      Bu2Dst0h_D0gamma_WN_sigma2Bu_(),
      pdf1Bu_Bu2Dst0h_D0gamma_WN_(),
      pdf2Bu_Bu2Dst0h_D0gamma_WN_(),
      pdfBu_Bu2Dst0h_D0gamma_WN_(new RooCBShape(
          ("pdfBu_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_WN_mean1Bu(),
          *Bu2Dst0h_D0gamma_WN_sigma1Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0gamma_WN_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_WN_n1Bu())),
      Bu2Dst0h_D0gamma_WN_sigmaBuPartial_(nullptr),
      pdfBuPartial_Bu2Dst0h_D0gamma_WN_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_WN_thresholdDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_thresholdDelta", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::misIdGammaWNPiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_aDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_aDelta", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::misIdGammaWNPiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_bDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_bDelta", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::misIdGammaWNPiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_cDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_cDelta", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::misIdGammaWNPiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_meanDelta_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_sigmaDelta_(nullptr),
      pdfDelta_misId_Bu2Dst0h_D0gamma_WN_(
          new RooDstD0BG(("pdfDelta_misId_Bu2Dst0h_D0gamma_WN_" +
                          ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         "", Configuration::Get().deltaMass(),
                         *misId_Bu2Dst0h_D0gamma_WN_thresholdDelta_,
                         *misId_Bu2Dst0h_D0gamma_WN_cDelta_,
                         *misId_Bu2Dst0h_D0gamma_WN_aDelta_,
                         *misId_Bu2Dst0h_D0gamma_WN_bDelta_)),
      misId_Bu2Dst0h_D0gamma_WN_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_meanBu", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::misIdGammaWNPiPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_sigmaBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_sigmaBu", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::misIdGammaWNPiPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_a1Bu_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_n1Bu_(nullptr),
      pdfBu_misId_Bu2Dst0h_D0gamma_WN_(
          new RooGaussian(("pdfBu_misId_Bu2Dst0h_D0gamma_WN_" +
                           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                              .c_str(),
                          "", Configuration::Get().buDeltaMass(),
                          *misId_Bu2Dst0h_D0gamma_WN_meanBu_,
                          *misId_Bu2Dst0h_D0gamma_WN_sigmaBu_)),
      misId_Bu2Dst0h_D0gamma_WN_meanBuPartial_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_sigmaBuPartial_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_a1BuPartial_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_n1BuPartial_(nullptr),
      pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN_(nullptr),
      // -------------------- Bd2Dsth -------------------- //
      Bd2Dsth_sigma1Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_sigma1Bu", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bd2Dstpi, Systematic::Bd2DsthBuPdf, Sign::same)),
      // Bd2Dsth_sigma1Bu_(Params::Get().CreateFloating(
      //     "Bd2Dsth_sigma1Bu", uniqueId_, Neutral::pi0, Bachelor::pi,
      //     Mode::Bd2Dstpi, 45, 65)),
      Bd2Dsth_sigma2Bu_(),
      pdf1Bu_Bd2Dsth_(),
      pdf2Bu_Bd2Dsth_(),
      pdfBu_Bd2Dsth_(new RooGaussian(
          ("pdfBu_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bd2Dsth_mean1Bu(),
          *Bd2Dsth_sigma1Bu_)),
      Bd2Dsth_sigma1BuPartial_(nullptr),
      Bd2Dsth_sigma2BuPartial_(),
      pdf1BuPartial_Bd2Dsth_(),
      pdf2BuPartial_Bd2Dsth_(),
      pdfBuPartial_Bd2Dsth_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bd2Dsth_meanBu_(nullptr),
      misId_Bd2Dsth_sigmaBu_(nullptr),
      misId_Bd2Dsth_a1Bu_(nullptr),
      misId_Bd2Dsth_n1Bu_(nullptr),
      pdfBu_misId_Bd2Dsth_(nullptr),
      misId_Bd2Dsth_thresholdDelta_(nullptr),
      misId_Bd2Dsth_aDelta_(nullptr),
      misId_Bd2Dsth_bDelta_(nullptr),
      misId_Bd2Dsth_cDelta_(nullptr),
      pdfDelta_misId_Bd2Dsth_(),
      misId_Bd2Dsth_meanBuPartial_(nullptr),
      misId_Bd2Dsth_sigmaBuPartial_(nullptr),
      misId_Bd2Dsth_a1BuPartial_(nullptr),
      misId_Bd2Dsth_n1BuPartial_(nullptr),
      pdfBuPartial_misId_Bd2Dsth_(),
      // -------------------- Bu2D0hst -------------------- //
      Bu2D0hst_sigma1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_sigma1Bu", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2D0rho, Systematic::Bu2D0hstBuPdf, Sign::same)),
      // Bu2D0hst_sigma1Bu_(Params::Get().CreateFloating(
      //     "Bu2D0hst_sigma1Bu", uniqueId_, Neutral::pi0, Bachelor::pi,
      //     Mode::Bu2D0rho, 65, 95)),
      Bu2D0hst_sigma2Bu_(),
      pdf1Bu_Bu2D0hst_(),
      pdf2Bu_Bu2D0hst_(),
      pdfBu_Bu2D0hst_(new RooCBShape(
          ("pdfBu_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2D0hst_mean1Bu(),
          *Bu2D0hst_sigma1Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2D0hst_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2D0hst_n1Bu())),
      Bu2D0hst_sigmaBuPartial_(nullptr),
      pdfBuPartial_Bu2D0hst_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2D0hst_meanBu_(nullptr),
      misId_Bu2D0hst_sigmaBu_(nullptr),
      misId_Bu2D0hst_a1Bu_(nullptr),
      misId_Bu2D0hst_n1Bu_(nullptr),
      pdfBu_misId_Bu2D0hst_(nullptr),
      misId_Bu2D0hst_thresholdDelta_(nullptr),
      misId_Bu2D0hst_aDelta_(nullptr),
      misId_Bu2D0hst_bDelta_(nullptr),
      misId_Bu2D0hst_cDelta_(nullptr),
      pdfDelta_misId_Bu2D0hst_(),
      misId_Bu2D0hst_meanBuPartial_(nullptr),
      misId_Bu2D0hst_sigmaBuPartial_(nullptr),
      misId_Bu2D0hst_a1BuPartial_(nullptr),
      misId_Bu2D0hst_n1BuPartial_(nullptr),
      pdfBuPartial_misId_Bu2D0hst_(),
      // -------------------- Bu2Dst0hst_D0gamma -------------------- //
      Bu2Dst0hst_D0gamma_sigma1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_sigma1Bu", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0rho_D0gamma, Systematic::Bu2Dst0hst_D0gammaBuPdf,
          Sign::same)),
      Bu2Dst0hst_D0gamma_sigma2Bu_(),
      pdf1Bu_Bu2Dst0hst_D0gamma_(),
      pdf2Bu_Bu2Dst0hst_D0gamma_(),
      pdfBu_Bu2Dst0hst_D0gamma_(
          new RooGaussian(("pdfBu_Bu2Dst0hst_D0gamma_" +
                           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                              .c_str(),
                          "", Configuration::Get().buDeltaMass(),
                          NeutralVars<Neutral::pi0>::Get(uniqueId_)
                              .Bu2Dst0hst_D0gamma_mean1Bu(),
                          *Bu2Dst0hst_D0gamma_sigma1Bu_)),
      Bu2Dst0hst_D0gamma_sigmaBuPartial_(nullptr),
      pdfBuPartial_Bu2Dst0hst_D0gamma_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0hst_D0gamma_mean1Bu_(nullptr),
      misId_Bu2Dst0hst_D0gamma_meanOffset21Bu_(nullptr),
      misId_Bu2Dst0hst_D0gamma_mean2Bu_(),
      misId_Bu2Dst0hst_D0gamma_sigma1Bu_(nullptr),
      misId_Bu2Dst0hst_D0gamma_sigmaRatio21Bu_(nullptr),
      misId_Bu2Dst0hst_D0gamma_sigma2Bu_(),
      misId_Bu2Dst0hst_D0gamma_a1Bu_(nullptr),
      misId_Bu2Dst0hst_D0gamma_n1Bu_(nullptr),
      pdf1Bu_misId_Bu2Dst0hst_D0gamma_(),
      pdf2Bu_misId_Bu2Dst0hst_D0gamma_(),
      misId_Bu2Dst0hst_D0gamma_fracPdf1Bu_(nullptr),
      pdfBu_misId_Bu2Dst0hst_D0gamma_(nullptr),
      misId_Bu2Dst0hst_D0gamma_meanDelta_(nullptr),
      misId_Bu2Dst0hst_D0gamma_sigmaDelta_(nullptr),
      pdf1Delta_misId_Bu2Dst0hst_D0gamma_(),
      pdf2Delta_misId_Bu2Dst0hst_D0gamma_(),
      misId_Bu2Dst0hst_D0gamma_fracPdf1Delta_(nullptr),
      pdfPeakDelta_misId_Bu2Dst0hst_D0gamma_(),
      pdfFlatDelta_misId_Bu2Dst0hst_D0gamma_(),
      misId_Bu2Dst0hst_D0gamma_fracPdfPeakDelta_(nullptr),
      pdfDelta_misId_Bu2Dst0hst_D0gamma_(nullptr),
      misId_Bu2Dst0hst_D0gamma_meanBuPartial_(nullptr),
      misId_Bu2Dst0hst_D0gamma_sigmaBuPartial_(nullptr),
      pdfBuPartial_misId_Bu2Dst0hst_D0gamma_(),
      // -------------------- Bu2Dst0hst_D0pi0 -------------------- //
      Bu2Dst0hst_D0pi0_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_sigmaBu", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0rho_D0pi0, Systematic::Bu2Dst0hst_D0pi0BuPdf,
          Sign::same)),
      pdfBu_Bu2Dst0hst_D0pi0_(
          ("pdfBu_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0hst_D0pi0_meanBu(),
          *Bu2Dst0hst_D0pi0_sigmaBu_),
      Bu2Dst0hst_D0pi0_sigmaBuPartial_(nullptr),
      pdfBuPartial_Bu2Dst0hst_D0pi0_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0hst_D0pi0_meanBu_(nullptr),
      misId_Bu2Dst0hst_D0pi0_sigmaBu_(nullptr),
      misId_Bu2Dst0hst_D0pi0_a1Bu_(nullptr),
      misId_Bu2Dst0hst_D0pi0_n1Bu_(nullptr),
      pdfBu_misId_Bu2Dst0hst_D0pi0_(),
      misId_Bu2Dst0hst_D0pi0_mean1Delta_(nullptr),
      misId_Bu2Dst0hst_D0pi0_mean2Delta_(nullptr),
      misId_Bu2Dst0hst_D0pi0_sigma1Delta_(nullptr),
      misId_Bu2Dst0hst_D0pi0_sigma2Delta_(nullptr),
      misId_Bu2Dst0hst_D0pi0_a1Delta_(nullptr),
      misId_Bu2Dst0hst_D0pi0_n1Delta_(nullptr),
      misId_Bu2Dst0hst_D0pi0_a2Delta_(nullptr),
      misId_Bu2Dst0hst_D0pi0_n2Delta_(nullptr),
      pdf1Delta_misId_Bu2Dst0hst_D0pi0_(),
      pdf2Delta_misId_Bu2Dst0hst_D0pi0_(),
      misId_Bu2Dst0hst_D0pi0_fracPdf1Delta_(nullptr),
      pdfPeakDelta_misId_Bu2Dst0hst_D0pi0_(),
      pdfFlatDelta_misId_Bu2Dst0hst_D0pi0_(),
      pdfDelta_misId_Bu2Dst0hst_D0pi0_(),
      misId_Bu2Dst0hst_D0pi0_mean1BuPartial_(nullptr),
      misId_Bu2Dst0hst_D0pi0_meanOffset21BuPartial_(nullptr),
      misId_Bu2Dst0hst_D0pi0_mean2BuPartial_(),
      misId_Bu2Dst0hst_D0pi0_sigma1BuPartial_(nullptr),
      misId_Bu2Dst0hst_D0pi0_sigmaRatio21BuPartial_(nullptr),
      misId_Bu2Dst0hst_D0pi0_sigma2BuPartial_(),
      misId_Bu2Dst0hst_D0pi0_a1BuPartial_(nullptr),
      misId_Bu2Dst0hst_D0pi0_n1BuPartial_(nullptr),
      pdf1BuPartial_misId_Bu2Dst0hst_D0pi0_(),
      pdf2BuPartial_misId_Bu2Dst0hst_D0pi0_(),
      misId_Bu2Dst0hst_D0pi0_fracPdf1BuPartial_(nullptr),
      pdfBuPartial_misId_Bu2Dst0hst_D0pi0_(),
      // -------------------- Bs2Dst0Kpi -------------------- //
      pdfPeakGamma1Delta_Bs2Dst0Kpi_(),
      pdfPeakGamma2Delta_Bs2Dst0Kpi_(),
      pdfPeakGammaDelta_Bs2Dst0Kpi_(),
      pdfPeakPi01Delta_Bs2Dst0Kpi_(),
      pdfPeakPi02Delta_Bs2Dst0Kpi_(),
      pdfPeakPi0Delta_Bs2Dst0Kpi_(),
      pdfDelta_Bs2Dst0Kpi_(),
      // -------------------- Correct ID BOX EFFs -------------------- //
      orEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      orEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi, Efficiency::orEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      orEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      orEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      orEffBd2Dsth_(Params::Get().CreateFixed(
          "orEffBd2Dsth_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEffErr,
                        false),
          Systematic::NA, Sign::same)),
      orEffBu2D0hst_(Params::Get().CreateFixed(
          "orEffBu2D0hst_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::orEffErr,
                        false),
          Systematic::NA, Sign::same)),
      orEffBu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "orEffBu2Dst0hst_D0gamma_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      orEffBu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "orEffBu2Dst0hst_D0pi0_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi, Efficiency::orEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      buEffBd2Dsth_(Params::Get().CreateFixed(
          "buEffBd2Dsth_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::buEffErr,
                        false),
          Systematic::NA, Sign::same)),
      buEffBu2D0hst_(Params::Get().CreateFixed(
          "buEffBu2D0hst_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::buEffErr,
                        false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "buEffBu2Dst0hst_D0gamma_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "buEffBu2Dst0hst_D0pi0_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBd2Dsth_(Params::Get().CreateFixed(
          "deltaEffBd2Dsth_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::deltaEff,
                        false),
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::deltaEffErr,
                        false),
          Systematic::NA, Sign::same)),
      deltaEffBu2D0hst_(Params::Get().CreateFixed(
          "deltaEffBu2D0hst_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::deltaEff,
                        false),
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::deltaEffErr,
                        false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0hst_D0gamma_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0hst_D0pi0_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      buPartialEffBu2Dst0h_D0gamma_(nullptr),
      buPartialEffBu2Dst0h_D0pi0_(nullptr),
      buPartialEffBu2Dst0h_D0gamma_WN_(nullptr),
      buPartialEffBu2Dst0h_D0pi0_WN_(nullptr),
      buPartialEffBd2Dsth_(nullptr),
      buPartialEffBu2D0hst_(nullptr),
      buPartialEffBu2Dst0hst_D0gamma_(nullptr),
      buPartialEffBu2Dst0hst_D0pi0_(nullptr),
      // -------------------- Mis-ID BoxEffs ------------------- //
      orEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0h_D0gamma_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi, Efficiency::orEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::same)),
      orEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi, Efficiency::orEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::same)),
      orEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::pi0,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::same)),
      orEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::pi0,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::same)),
      orEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "orEffMisId_Bd2Dsth_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::orEffErr,
                        true),
          Systematic::NA, Sign::same)),
      orEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "orEffMisId_Bu2D0hst_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::orEffErr,
                        true),
          Systematic::NA, Sign::same)),
      orEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0hst_D0gamma_", uniqueId_, Neutral::pi0,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::same)),
      orEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0hst_D0pi0_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi, Efficiency::orEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::same)),
      buEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0gamma_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi, Efficiency::buEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::same)),
      buEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi, Efficiency::buEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::same)),
      buEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::pi0,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::same)),
      buEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::pi0,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::same)),
      buEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "buEffMisId_Bd2Dsth_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::buEffErr,
                        true),
          Systematic::NA, Sign::same)),
      buEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "buEffMisId_Bu2D0hst_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::buEffErr,
                        true),
          Systematic::NA, Sign::same)),
      buEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0hst_D0gamma_", uniqueId_, Neutral::pi0,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::same)),
      buEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0hst_D0pi0_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi, Efficiency::buEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::same)),
      deltaEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0gamma_", uniqueId_, Neutral::pi0,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::same)),
      deltaEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::pi0,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::same)),
      deltaEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::pi0,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::same)),
      deltaEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::pi0,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::same)),
      deltaEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "deltaEffMisId_Bd2Dsth_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::deltaEff,
                        true),
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::deltaEffErr,
                        true),
          Systematic::NA, Sign::same)),
      deltaEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2D0hst_", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::deltaEff,
                        true),
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::deltaEffErr,
                        true),
          Systematic::NA, Sign::same)),
      deltaEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0hst_D0gamma_", uniqueId_, Neutral::pi0,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::same)),
      deltaEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0hst_D0pi0_", uniqueId_, Neutral::pi0,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::same)),
      buPartialEffMisId_Bu2Dst0h_D0gamma_(nullptr),
      buPartialEffMisId_Bu2Dst0h_D0pi0_(nullptr),
      buPartialEffMisId_Bu2Dst0h_D0gamma_WN_(nullptr),
      buPartialEffMisId_Bu2Dst0h_D0pi0_WN_(nullptr),
      buPartialEffMisId_Bd2Dsth_(nullptr),
      buPartialEffMisId_Bu2D0hst_(nullptr),
      buPartialEffMisId_Bu2Dst0hst_D0gamma_(nullptr),
      buPartialEffMisId_Bu2Dst0hst_D0pi0_(nullptr),
      // -------------------- MC Efficiencies -------------------- //
      mcEff_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0pi0", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0gamma", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_Bd2Dsth_(Params::Get().CreateFixed(
          "mcEff_Bd2Dsth", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnMCEffs(Mode::Bd2Dstpi, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bd2Dstpi, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_Bu2D0hst_(Params::Get().CreateFixed(
          "mcEff_Bu2D0hst", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2D0rho, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2D0rho, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0hst_D0gamma", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0hst_D0pi0", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      // -------------------- MC misId Efficiencies -------------------- //
      mcEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0h_D0pi0", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0h_D0gamma", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::pi0,
          Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma_WN, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma_WN, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0_WN, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0_WN, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "mcEffMisId_Bd2Dsth", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnMCEffs(Mode::Bd2DstK, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bd2DstK, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2D0hst", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2D0Kst, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2D0Kst, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0hst_D0gamma", uniqueId_, Neutral::pi0,
          Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0Kst_D0gamma, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0Kst_D0gamma, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0hst_D0pi0", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0Kst_D0pi0, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0Kst_D0pi0, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      // -------------------- Bkg Fractions -------------------- //
      // bkgFrac_Bu2Dst0h_D0pi0_WN_(nullptr),
      // bkgFrac_Bu2Dst0h_D0gamma_WN_(nullptr),
      bkgFrac_Bu2Dst0h_D0pi0_WN_(new RooFormulaVar(
          ("bkgFrac_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "(@0/@1)*(@2/@3)",
          RooArgList(*orEffBu2Dst0h_D0pi0_WN_, *orEffBu2Dst0h_D0pi0_,
                     *mcEff_Bu2Dst0h_D0pi0_WN_, *mcEff_Bu2Dst0h_D0pi0_))),
      // No global frac for gamma mode in π0: different physics
      bkgFrac_Bu2Dst0h_D0gamma_WN_(new RooFormulaVar(
          ("bkgFrac_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "(@0/@1)*(@2/@3)*(@4/@5)",
          RooArgList(*orEffBu2Dst0h_D0gamma_WN_, *orEffBu2Dst0h_D0pi0_,
                     *mcEff_Bu2Dst0h_D0gamma_WN_, *mcEff_Bu2Dst0h_D0pi0_,
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma(),
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0()))),
      bkgFrac_Bu2Dst0h_WN_(
          ("bkgFrac_Bu2Dst0h_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0*(@1*@2*@8+@3*@4*@7)/(@5*@6*@8)",
          RooArgList(
              NeutralVars<Neutral::pi0>::Get(uniqueId_).bkgFracGlobal_WN(),
              *orEffBu2Dst0h_D0pi0_WN_, *mcEff_Bu2Dst0h_D0pi0_WN_,
              *orEffBu2Dst0h_D0gamma_WN_, *mcEff_Bu2Dst0h_D0gamma_WN_,
              *orEffBu2Dst0h_D0pi0_, *mcEff_Bu2Dst0h_D0pi0_,
              GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma(),
              GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0())),
      // -------------------- Bu2Dst0h_WN -------------------- //
      Bu2Dst0h_WN_fracD0pi0_(
          ("Bu2Dst0h_WN_fracD0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0*(@1*@2*@5)/(@1*@2*@5 + @3*@4*@6)",
          RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId_)
                         .Bu2Dst0h_WN_floatingFracD0pi0(),
                     *orEffBu2Dst0h_D0pi0_WN_, *mcEff_Bu2Dst0h_D0pi0_WN_,
                     *orEffBu2Dst0h_D0gamma_WN_, *mcEff_Bu2Dst0h_D0gamma_WN_,
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0(),
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma())),
      Bu2Dst0h_WN_fracD0pi0_Bu_(
          ("Bu2Dst0h_WN_fracD0pi0_Bu_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0*(@1*@2*@3*@7)/(@1*@2*@3*@7 + @4*@5*@6*@8)",
          RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId_)
                         .Bu2Dst0h_WN_floatingFracD0pi0(),
                     *buEffBu2Dst0h_D0pi0_WN_, *orEffBu2Dst0h_D0pi0_WN_,
                     *mcEff_Bu2Dst0h_D0pi0_WN_, *buEffBu2Dst0h_D0gamma_WN_,
                     *orEffBu2Dst0h_D0gamma_WN_, *mcEff_Bu2Dst0h_D0gamma_WN_,
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0(),
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma())),
      Bu2Dst0h_WN_fracD0pi0_Delta_(
          ("Bu2Dst0h_WN_fracD0pi0_Delta_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0*(@1*@2*@3*@7)/(@1*@2*@3*@7 + @4*@5*@6*@8)",
          RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId_)
                         .Bu2Dst0h_WN_floatingFracD0pi0(),
                     *deltaEffBu2Dst0h_D0pi0_WN_, *orEffBu2Dst0h_D0pi0_WN_,
                     *mcEff_Bu2Dst0h_D0pi0_WN_, *deltaEffBu2Dst0h_D0gamma_WN_,
                     *orEffBu2Dst0h_D0gamma_WN_, *mcEff_Bu2Dst0h_D0gamma_WN_,
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0(),
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma())),
      pdfBu_Bu2Dst0h_WN_(
          ("pdfBu_Bu2Dst0h_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", RooArgSet(*pdfBu_Bu2Dst0h_D0pi0_WN_, *pdfBu_Bu2Dst0h_D0gamma_WN_),
          Bu2Dst0h_WN_fracD0pi0_Bu_),
      pdfDelta_Bu2Dst0h_WN_(("pdfDelta_Bu2Dst0h_WN_" +
                             ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                                .c_str(),
                            "",
                            RooArgSet(pdfDelta_Bu2Dst0h_D0pi0_WN_,
                                      NeutralVars<Neutral::pi0>::Get(uniqueId)
                                          .pdfDelta_Bu2Dst0h_D0gamma_WN()),
                            Bu2Dst0h_WN_fracD0pi0_Delta_),
      orEffBu2Dst0h_WN_(
          ("orEffBu2Dst0h_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0h_WN_fracD0pi0_, *orEffBu2Dst0h_D0pi0_WN_,
                     *orEffBu2Dst0h_D0gamma_WN_)),
      buEffBu2Dst0h_WN_(
          ("buEffBu2Dst0h_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0h_WN_fracD0pi0_, *buEffBu2Dst0h_D0pi0_WN_,
                     *buEffBu2Dst0h_D0gamma_WN_)),
      deltaEffBu2Dst0h_WN_(
          ("deltaEffBu2Dst0h_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0h_WN_fracD0pi0_, *deltaEffBu2Dst0h_D0pi0_WN_,
                     *deltaEffBu2Dst0h_D0gamma_WN_)),
      mcEff_Bu2Dst0h_WN_(
          ("mcEff_Bu2Dst0h_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0h_WN_fracD0pi0_, *mcEff_Bu2Dst0h_D0pi0_WN_,
                     *mcEff_Bu2Dst0h_D0gamma_WN_)),
      Bu2Dst0h_WN_misId_fracD0pi0_(
          ("Bu2Dst0h_WN_misId_fracD0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0*(@1*@2*@5)/(@1*@2*@5 + @3*@4*@6)",
          RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId_)
                         .Bu2Dst0h_WN_floatingFracD0pi0(),
                     *orEffMisId_Bu2Dst0h_D0pi0_WN_,
                     *mcEffMisId_Bu2Dst0h_D0pi0_WN_,
                     *orEffMisId_Bu2Dst0h_D0gamma_WN_,
                     *mcEffMisId_Bu2Dst0h_D0gamma_WN_,
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0(),
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma())),
      Bu2Dst0h_WN_misId_fracD0pi0_Bu_(
          ("Bu2Dst0h_WN_misId_fracD0pi0_Bu_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0*(@1*@2*@3*@7)/(@1*@2*@3*@7 + @4*@5*@6*@8)",
          RooArgList(
              NeutralVars<Neutral::pi0>::Get(uniqueId_)
                  .Bu2Dst0h_WN_floatingFracD0pi0(),
              *buEffMisId_Bu2Dst0h_D0pi0_WN_, *orEffMisId_Bu2Dst0h_D0pi0_WN_,
              *mcEffMisId_Bu2Dst0h_D0pi0_WN_, *buEffMisId_Bu2Dst0h_D0gamma_WN_,
              *orEffMisId_Bu2Dst0h_D0gamma_WN_,
              *mcEffMisId_Bu2Dst0h_D0gamma_WN_,
              GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0(),
              GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma())),
      Bu2Dst0h_WN_misId_fracD0pi0_Delta_(
          ("Bu2Dst0h_WN_misId_fracD0pi0_Delta_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0*(@1*@2*@3*@7)/(@1*@2*@3*@7 + @4*@5*@6*@8)",
          RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId_)
                         .Bu2Dst0h_WN_floatingFracD0pi0(),
                     *deltaEffMisId_Bu2Dst0h_D0pi0_WN_,
                     *orEffMisId_Bu2Dst0h_D0pi0_WN_,
                     *mcEffMisId_Bu2Dst0h_D0pi0_WN_,
                     *deltaEffMisId_Bu2Dst0h_D0gamma_WN_,
                     *orEffMisId_Bu2Dst0h_D0gamma_WN_,
                     *mcEffMisId_Bu2Dst0h_D0gamma_WN_,
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0(),
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma())),
      pdfBu_misId_Bu2Dst0h_WN_(
          ("pdfBu_misId_Bu2Dst0h_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "",
          RooArgSet(*pdfBu_misId_Bu2Dst0h_D0pi0_WN_,
                    *pdfBu_misId_Bu2Dst0h_D0gamma_WN_),
          Bu2Dst0h_WN_misId_fracD0pi0_Bu_),
      pdfDelta_misId_Bu2Dst0h_WN_(
          ("pdfDelta_misId_Bu2Dst0h_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "",
          RooArgSet(pdfDelta_misId_Bu2Dst0h_D0pi0_WN_,
                    *pdfDelta_misId_Bu2Dst0h_D0gamma_WN_),
          Bu2Dst0h_WN_misId_fracD0pi0_Delta_),
      orEffMisId_Bu2Dst0h_WN_(
          ("orEffMisId_Bu2Dst0h_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0h_WN_misId_fracD0pi0_,
                     *orEffMisId_Bu2Dst0h_D0pi0_WN_,
                     *orEffMisId_Bu2Dst0h_D0gamma_WN_)),
      buEffMisId_Bu2Dst0h_WN_(
          ("buEffMisId_Bu2Dst0h_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0h_WN_misId_fracD0pi0_,
                     *buEffMisId_Bu2Dst0h_D0pi0_WN_,
                     *buEffMisId_Bu2Dst0h_D0gamma_WN_)),
      deltaEffMisId_Bu2Dst0h_WN_(
          ("deltaEffMisId_Bu2Dst0h_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0h_WN_misId_fracD0pi0_,
                     *deltaEffMisId_Bu2Dst0h_D0pi0_WN_,
                     *deltaEffMisId_Bu2Dst0h_D0gamma_WN_)),
      mcEffMisId_Bu2Dst0h_WN_(
          ("mcEffMisId_Bu2Dst0h_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0h_WN_fracD0pi0_, *mcEffMisId_Bu2Dst0h_D0pi0_WN_,
                     *mcEffMisId_Bu2Dst0h_D0gamma_WN_)),
      // -------------------- Bu2Dst0hst -------------------- //
      Bu2Dst0hst_fracD0pi0_(),
      Bu2Dst0hst_fracD0pi0_Bu_(),
      Bu2Dst0hst_fracD0pi0_Delta_(),
      Bu2Dst0hst_fracD0pi0_BuPartial_(),
      // Just pdfBu_Bu2Dst0hst_D0pi0
      pdfBu_Bu2Dst0hst_(new RooGaussian(
          ("pdfBu_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0hst_D0pi0_meanBu(),
          *Bu2Dst0hst_D0pi0_sigmaBu_)),
      pdfDelta_Bu2Dst0hst_(),
      pdfBuPartial_Bu2Dst0hst_(),
      orEffBu2Dst0hst_(("orEffBu2Dst0hst_" +
                        ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                           .c_str(),
                       "@0", RooArgList(*orEffBu2Dst0hst_D0pi0_)),
      buEffBu2Dst0hst_(("buEffBu2Dst0hst_" +
                        ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                           .c_str(),
                       "@0", RooArgList(*buEffBu2Dst0hst_D0pi0_)),
      deltaEffBu2Dst0hst_(("deltaEffBu2Dst0hst_" +
                           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                              .c_str(),
                          "@0", RooArgList(*deltaEffBu2Dst0hst_D0pi0_)),
      buPartialEffBu2Dst0hst_(),
      mcEff_Bu2Dst0hst_(("mcEff_Bu2Dst0hst_" +
                         ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                            .c_str(),
                        "@0", RooArgList(*mcEff_Bu2Dst0hst_D0pi0_)),
      Bu2Dst0hst_misId_fracD0pi0_(),
      Bu2Dst0hst_misId_fracD0pi0_Bu_(),
      Bu2Dst0hst_misId_fracD0pi0_Delta_(),
      Bu2Dst0hst_misId_fracD0pi0_BuPartial_(),
      pdfBu_misId_Bu2Dst0hst_(nullptr),
      pdfDelta_misId_Bu2Dst0hst_(),
      pdfBuPartial_misId_Bu2Dst0hst_(),
      orEffMisId_Bu2Dst0hst_(
          ("orEffMisId_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0", RooArgList(*orEffMisId_Bu2Dst0hst_D0pi0_)),
      buEffMisId_Bu2Dst0hst_(
          ("buEffMisId_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0", RooArgList(*buEffMisId_Bu2Dst0hst_D0pi0_)),
      deltaEffMisId_Bu2Dst0hst_(
          ("deltaEffMisId_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0", RooArgList(*deltaEffMisId_Bu2Dst0hst_D0pi0_)),
      buPartialEffMisId_Bu2Dst0hst_(),
      mcEffMisId_Bu2Dst0hst_(
          ("mcEffMisId_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "@0", RooArgList(*mcEffMisId_Bu2Dst0hst_D0pi0_)) {}
