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
      Bu2Dst0h_D0pi0_sigmaBu_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_sigmaBu", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0pi_D0pi0, 17, 25)),
      pdf1Bu_Bu2Dst0h_D0pi0_(
          ("pdf1Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0pi0_(
          ("pdf2Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigmaBu_,
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
      Bu2Dst0h_D0pi0_WN_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_sigmaBu", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::same)),
      pdfBu_Bu2Dst0h_D0pi0_WN_(
          ("pdfBu_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_meanBu(),
          *Bu2Dst0h_D0pi0_WN_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_n1Bu()),
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
      misId_Bu2Dst0h_D0pi0_WN_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_meanBu", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN, Systematic::misIdPi0WNPiPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_sigmaBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_sigmaBu", uniqueId_, Neutral::pi0,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN, Systematic::misIdPi0WNPiPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_a1Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_n1Bu_(nullptr),
      pdfBu_misId_Bu2Dst0h_D0pi0_WN_(new RooGaussian(
          ("pdfBu_misId_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_WN_meanBu_, *misId_Bu2Dst0h_D0pi0_WN_sigmaBu_)),
      misId_Bu2Dst0h_D0pi0_WN_meanBuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_sigmaBuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_a1BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_n1BuPartial_(nullptr),
      pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN_(),
      // -------------------- Bu2Dst0h_D0gamma_WN -------------------- //
      Bu2Dst0h_D0gamma_WN_sigma1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_sigma1Bu", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNBuPdf, Sign::same)),
      Bu2Dst0h_D0gamma_WN_sigma2Bu_(),
      pdf1Bu_Bu2Dst0h_D0gamma_WN_(),
      pdf2Bu_Bu2Dst0h_D0gamma_WN_(),
      pdfBu_Bu2Dst0h_D0gamma_WN_(
          new RooGaussian(("pdfBu_Bu2Dst0h_D0gamma_WN_" +
                           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                              .c_str(),
                          "", Configuration::Get().buDeltaMass(),
                          NeutralVars<Neutral::pi0>::Get(uniqueId_)
                              .Bu2Dst0h_D0gamma_WN_mean1Bu(),
                          *Bu2Dst0h_D0gamma_WN_sigma1Bu_)),
      Bu2Dst0h_D0gamma_WN_sigmaBuPartial_(nullptr),
      pdfBuPartial_Bu2Dst0h_D0gamma_WN_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_WN_meanBu_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_sigmaBu_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_a1Bu_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_n1Bu_(nullptr),
      pdfBu_misId_Bu2Dst0h_D0gamma_WN_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_thresholdDelta_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_aDelta_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_bDelta_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_cDelta_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_meanDelta_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_sigmaDelta_(nullptr),
      pdfDelta_misId_Bu2Dst0h_D0gamma_WN_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_meanBuPartial_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_sigmaBuPartial_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_a1BuPartial_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_n1BuPartial_(nullptr),
      pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN_(),
      // -------------------- Bd2Dsth -------------------- //
      Bd2Dsth_sigmaBu_(Params::Get().CreateFixed(
          "Bd2Dsth_sigmaBu", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bd2Dstpi, Systematic::Bd2DsthBuPdf, Sign::same)),
      pdfBu_Bd2Dsth_(("pdfBu_Bd2Dsth_" +
                      ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                         .c_str(),
                     "", Configuration::Get().buDeltaMass(),
                     NeutralVars<Neutral::pi0>::Get(uniqueId_).Bd2Dsth_meanBu(),
                     *Bd2Dsth_sigmaBu_),
      Bd2Dsth_sigmaBuPartial_(nullptr),
      pdfBuPartial_Bd2Dsth_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bd2Dsth_meanBu_(nullptr),
      misId_Bd2Dsth_sigmaBu_(nullptr),
      pdfBu_misId_Bd2Dsth_(),
      misId_Bd2Dsth_thresholdDelta_(nullptr),
      misId_Bd2Dsth_aDelta_(nullptr),
      misId_Bd2Dsth_bDelta_(nullptr),
      misId_Bd2Dsth_cDelta_(nullptr),
      pdfDelta_misId_Bd2Dsth_(),
      misId_Bd2Dsth_meanBuPartial_(nullptr),
      misId_Bd2Dsth_sigmaBuPartial_(nullptr),
      pdfBuPartial_misId_Bd2Dsth_(),
      // -------------------- Bu2D0hst -------------------- //
      Bu2D0hst_sigma1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_sigma1Bu", uniqueId_, Neutral::pi0, Bachelor::pi,
          Mode::Bu2D0rho, Systematic::Bu2D0hstBuPdf, Sign::same)),
      Bu2D0hst_sigma2Bu_(),
      pdf1Bu_Bu2D0hst_(),
      pdf2Bu_Bu2D0hst_(),
      pdfBu_Bu2D0hst_(new RooGaussian(
          ("pdfBu_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2D0hst_mean1Bu(),
          *Bu2D0hst_sigma1Bu_)),
      Bu2D0hst_sigmaBuPartial_(nullptr),
      pdfBuPartial_Bu2D0hst_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2D0hst_meanBu_(nullptr),
      misId_Bu2D0hst_sigmaBu_(nullptr),
      pdfBu_misId_Bu2D0hst_(),
      misId_Bu2D0hst_thresholdDelta_(nullptr),
      misId_Bu2D0hst_aDelta_(nullptr),
      misId_Bu2D0hst_bDelta_(nullptr),
      misId_Bu2D0hst_cDelta_(nullptr),
      pdfDelta_misId_Bu2D0hst_(),
      misId_Bu2D0hst_meanBuPartial_(nullptr),
      misId_Bu2D0hst_sigmaBuPartial_(nullptr),
      pdfBuPartial_misId_Bu2D0hst_(),
      // -------------------- Bu2Dst0hst_D0gamma -------------------- //
      Bu2Dst0hst_D0gamma_sigma1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_sigma2Bu_(),
      Bu2Dst0hst_D0gamma_sigma3Bu_(),
      pdf1Bu_Bu2Dst0hst_D0gamma_(),
      pdf2Bu_Bu2Dst0hst_D0gamma_(),
      pdfFlatBu_Bu2Dst0hst_D0gamma_(),
      pdfBu_Bu2Dst0hst_D0gamma_(),
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
      pdfBu_misId_Bu2Dst0hst_D0gamma_(),
      misId_Bu2Dst0hst_D0gamma_meanDelta_(nullptr),
      misId_Bu2Dst0hst_D0gamma_sigmaDelta_(nullptr),
      pdf1Delta_misId_Bu2Dst0hst_D0gamma_(),
      pdf2Delta_misId_Bu2Dst0hst_D0gamma_(),
      misId_Bu2Dst0hst_D0gamma_fracPdf1Delta_(nullptr),
      pdfPeakDelta_misId_Bu2Dst0hst_D0gamma_(),
      pdfFlatDelta_misId_Bu2Dst0hst_D0gamma_(),
      misId_Bu2Dst0hst_D0gamma_fracPdfPeakDelta_(nullptr),
      pdfDelta_misId_Bu2Dst0hst_D0gamma_(),
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
      misId_Bu2Dst0hst_D0pi0_meanDelta_(nullptr),
      misId_Bu2Dst0hst_D0pi0_sigmaDelta_(nullptr),
      pdf1Delta_misId_Bu2Dst0hst_D0pi0_(),
      pdf2Delta_misId_Bu2Dst0hst_D0pi0_(),
      misId_Bu2Dst0hst_D0pi0_fracPdf1Delta_(nullptr),
      pdfPeakDelta_misId_Bu2Dst0hst_D0pi0_(),
      pdfFlatDelta_misId_Bu2Dst0hst_D0pi0_(),
      misId_Bu2Dst0hst_D0pi0_fracPdfPeakDelta_(nullptr),
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
      // -------------------- MIS-REC -------------------- //
      MisRec_sigmaLBu_(Params::Get().CreateFixed(
          "MisRec_sigmaLBu", uniqueId_, Neutral::pi0, Bachelor::pi, 5.6386e+01,
          1.67e+00, Systematic::misRecBuPdf, Sign::same)),
      // MisRec_sigmaLBu_(Params::Get().CreateFloating(
      //     "MisRec_sigmaLBu", uniqueId_, Neutral::pi0,
      //     Bachelor::pi, 5.6386e+01, 30, 70)),
      MisRec_sigmaRBu_(Params::Get().CreateFixed(
          "MisRec_sigmaRBu", uniqueId_, Neutral::pi0, Bachelor::pi, 5.7104e+01,
          7.42e-01, Systematic::misRecBuPdf, Sign::same)),
      // MisRec_sigmaRBu_(Params::Get().CreateFloating(
      //     "MisRec_sigmaRBu", uniqueId_, Neutral::pi0,
      //     Bachelor::pi, 5.7104e+01, 30, 70)),
      pdfBu_MisRec_(
          ("pdfBu_MisRec_" + ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).MisRec_meanBu(),
          *MisRec_sigmaLBu_, *MisRec_sigmaRBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).MisRec_aLBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).MisRec_aRBu()),
      MisRec_sigmaLBuPartial_(nullptr),
      MisRec_sigmaRBuPartial_(nullptr),
      pdfBuPartial_MisRec_(),
      // -------------------- Mis-ID ------------------- //
      misId_MisRec_mean1Bu_(nullptr),
      misId_MisRec_mean2Bu_(nullptr),
      misId_MisRec_sigma1Bu_(nullptr),
      misId_MisRec_sigma2Bu_(nullptr),
      misId_MisRec_a2Bu_(nullptr),
      misId_MisRec_a1Bu_(nullptr),
      misId_MisRec_n2Bu_(nullptr),
      misId_MisRec_n1Bu_(nullptr),
      pdf1Bu_misId_MisRec_(),
      pdf2Bu_misId_MisRec_(),
      misId_MisRec_fracPdf1Bu_(nullptr),
      pdfBu_misId_MisRec_(nullptr),
      misId_MisRec_meanBuPartial_(nullptr),
      misId_MisRec_sigmaLBuPartial_(nullptr),
      misId_MisRec_sigmaRBuPartial_(nullptr),
      misId_MisRec_aLBuPartial_(nullptr),
      misId_MisRec_aRBuPartial_(nullptr),
      pdfBuPartial_misId_MisRec_(),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_sigmaLBu_(("Bu2D0h_sigmaLBu_" +
                        ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                           .c_str(),
                       // "", 3.3137e+01, 10, 100),
                       // Fixed from data
                       // "", 4.7982e+01),
                       // Fixed from data
                       "", 4.0526e+01),
      Bu2D0h_sigmaRBu_(("Bu2D0h_sigmaRBu_" +
                        ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                           .c_str(),
                       // "", 4.0080e+01, 10, 80),
                       // Fixed from data
                       // "", 4.1667e+01),
                       // Fixed from data
                       "", 3.2923e+01),
      pdfBu_Bu2D0h_(
          ("pdfBu_Bu2D0h_" + ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2D0h_meanBu(),
          Bu2D0h_sigmaLBu_, Bu2D0h_sigmaRBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2D0h_aLBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2D0h_aRBu()),
      Bu2D0h_sigmaLBuPartial_(),
      Bu2D0h_sigmaRBuPartial_(),
      pdfBuPartial_Bu2D0h_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2D0h_meanBu_(),
      misId_Bu2D0h_sigmaLBu_(),
      misId_Bu2D0h_sigmaRBu_(),
      misId_Bu2D0h_aLBu_(),
      misId_Bu2D0h_aRBu_(),
      pdfBu_misId_Bu2D0h_(),
      misId_Bu2D0h_meanBuPartial_(),
      misId_Bu2D0h_sigmaLBuPartial_(),
      misId_Bu2D0h_sigmaRBuPartial_(),
      misId_Bu2D0h_aLBuPartial_(),
      misId_Bu2D0h_aRBuPartial_(),
      pdfBuPartial_misId_Bu2D0h_(),
      // -------------------- PART REC -------------------- //
      PartRec_D0pi0_sigmaLBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_sigmaLBu", uniqueId_, Neutral::pi0, Bachelor::pi,
          4.6660e+01, 1.94e+00, Systematic::partRecBuPdf, Sign::same)),
      PartRec_D0pi0_sigmaRBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_sigmaRBu", uniqueId_, Neutral::pi0, Bachelor::pi,
          4.4688e+01, 6.17e+00, Systematic::partRecBuPdf, Sign::same)),
      pdfBu_PartRec_D0pi0_(),
      PartRec_D0gamma_sigmaLBu_(nullptr),
      PartRec_D0gamma_sigmaRBu_(nullptr),
      pdfBu_PartRec_D0gamma_(),
      pdfBu_PartRec_(new RooCruijff(
          ("pdfBu_PartRec_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).PartRec_D0pi0_meanBu(),
          *PartRec_D0pi0_sigmaLBu_, *PartRec_D0pi0_sigmaRBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).PartRec_D0pi0_aLBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).PartRec_D0pi0_aRBu())),
      PartRec_sigmaLBuPartial_(nullptr),
      PartRec_sigmaRBuPartial_(nullptr),
      pdfBuPartial_PartRec_(),
      // -------------------- Mis-ID ------------------- //
      misId_PartRec_meanBu_(nullptr),
      misId_PartRec_sigmaLBu_(nullptr),
      misId_PartRec_sigmaRBu_(nullptr),
      misId_PartRec_aLBu_(nullptr),
      misId_PartRec_aRBu_(nullptr),
      pdfBu_misId_PartRec_(),
      misId_PartRec_meanBuPartial_(nullptr),
      misId_PartRec_sigmaLBuPartial_(nullptr),
      misId_PartRec_sigmaRBuPartial_(nullptr),
      misId_PartRec_aLBuPartial_(nullptr),
      misId_PartRec_aRBuPartial_(nullptr),
      pdfBuPartial_misId_PartRec_(),
      // -------------------- Correct ID BOX EFFs -------------------- //
      buEffBu2Dst0h_D0gamma_(nullptr),
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
      deltaEffBu2Dst0h_D0gamma_(nullptr),
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
      buEffMisId_Bu2Dst0h_D0gamma_(nullptr),
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
      deltaEffMisId_Bu2Dst0h_D0gamma_(nullptr),
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
      // -------------------- Mis-ID BoxEffs ------------------- //
      buDeltaCutEffMisId_Bu2Dst0h_D0gamma_(nullptr),
      buDeltaCutEffMisId_Bu2Dst0h_D0pi0_(nullptr),
      buDeltaCutEffMisId_MisRec_(nullptr),
      buDeltaCutEffMisId_Bu2D0h_(nullptr),
      buDeltaCutEffMisId_PartRec_(nullptr),
      deltaCutEffMisId_Bu2Dst0h_D0gamma_(nullptr),
      deltaCutEffMisId_Bu2Dst0h_D0pi0_(nullptr),
      deltaCutEffMisId_MisRec_(nullptr),
      deltaCutEffMisId_Bu2D0h_(nullptr),
      deltaCutEffMisId_PartRec_(nullptr),
      deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_(nullptr),
      deltaPartialCutEffMisId_MisRec_(nullptr),
      deltaPartialCutEffMisId_Bu2D0h_(nullptr),
      deltaPartialCutEffMisId_PartRec_(nullptr),
      // -------------------- Bs BoxEffs ------------------- //
      buDeltaCutEffBs2Dst0Kpi_(nullptr),
      buDeltaCutEffBs2D0Kpi_(nullptr),
      deltaCutEffBs2Dst0Kpi_(nullptr),
      deltaCutEffBs2D0Kpi_(nullptr),
      deltaPartialCutEffBs2Dst0Kpi_(nullptr),
      deltaPartialCutEffBs2D0Kpi_(nullptr),
      // -------------------- MC Efficiencies -------------------- //
      mcEff_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0pi0", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_Bu2Dst0h_D0gamma_(nullptr),
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
      mcEff_MisRec_(Params::Get().CreateFixed("mcEff_MisRec", uniqueId_,
                                              Neutral::pi0, Bachelor::pi, 1.0,
                                              0.0, Systematic::NA, Sign::same)),
      mcEff_Bu2D0h_(Params::Get().CreateFixed(
          "mcEff_Bu2D0h", uniqueId_, Neutral::pi0, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2D0pi, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2D0pi, Neutral::pi0, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_PartRec_(Params::Get().CreateFixed(
          "mcEff_PartRec", uniqueId_, Neutral::pi0, Bachelor::pi, 1.0, 0.0,
          Systematic::NA, Sign::same)),
      mcEff_Bs2Dst0Kpi_(Params::Get().CreateFixed(
          "mcEff_Bs2Dst0Kpi", uniqueId_, Neutral::pi0, Bachelor::pi, 1.0, 0.0,
          Systematic::NA, Sign::same)),
      mcEff_Bs2D0Kpi_(Params::Get().CreateFixed(
          "mcEff_Bs2D0Kpi", uniqueId_, Neutral::pi0, Bachelor::pi, 1.0, 0.0,
          Systematic::NA, Sign::same)),
      // -------------------- CP Observables -------------------- //
      A_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_CP_Bu2Dst0h_D0gamma_WN_Blind_(nullptr),
      A_CP_Bu2Dst0h_D0pi0_WN_Blind_(nullptr),
      A_CP_Bu2Dst0h_D0gamma_(nullptr),
      A_CP_Bu2Dst0h_D0pi0_(nullptr),
      A_CP_Bu2Dst0h_D0gamma_WN_(nullptr),
      A_CP_Bu2Dst0h_D0pi0_WN_(nullptr),
      A_CP_Bd2Dsth_(nullptr),
      A_CP_Bu2D0hst_(nullptr),
      A_CP_Bu2Dst0hst_D0gamma_(nullptr),
      A_CP_Bu2Dst0hst_D0pi0_(nullptr),
      R_ADS_Bu2Dst0h_D0gamma_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_(nullptr),
      R_ADS_Bu2Dst0h_D0gamma_WN_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_WN_(nullptr),
      R_ADS_Bd2Dsth_(nullptr),
      R_ADS_Bu2D0hst_(nullptr),
      R_ADS_Bu2Dst0hst_D0gamma_(nullptr),
      R_ADS_Bu2Dst0hst_D0pi0_(nullptr) {
  if (Configuration::Get().blindFit() == true) {
    A_CP_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0pi0_Blind", uniqueId_,
                                     Neutral::pi0, Bachelor::pi, 0.025, -1, 1));
    A_CP_Bu2Dst0h_D0gamma_WN_Blind_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0gamma_WN_Blind", uniqueId_, Neutral::pi0,
            Bachelor::pi, -0.003, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_WN_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0pi0_WN_Blind", uniqueId_,
                                     Neutral::pi0, Bachelor::pi, 0.025, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooUnblindUniform>(
        MakeBlind(("A_CP_Bu2Dst0h_D0pi0_" +
                   ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                      .c_str(),
                  0.03, *A_CP_Bu2Dst0h_D0pi0_Blind_));
    A_CP_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooUnblindUniform>(
        MakeBlind(("A_CP_Bu2Dst0h_D0gamma_WN_" +
                   ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                      .c_str(),
                  0.03, *A_CP_Bu2Dst0h_D0gamma_WN_Blind_));
    A_CP_Bu2Dst0h_D0pi0_WN_ = std::shared_ptr<RooUnblindUniform>(
        MakeBlind(("A_CP_Bu2Dst0h_D0pi0_WN_" +
                   ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi))
                      .c_str(),
                  0.03, *A_CP_Bu2Dst0h_D0pi0_WN_Blind_));
  } else {
    A_CP_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0pi0", uniqueId_,
                                     Neutral::pi0, Bachelor::pi, 0.025, -1, 1));
    A_CP_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::pi0, Bachelor::pi,
            -0.003, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_WN_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0pi0_WN", uniqueId_,
                                     Neutral::pi0, Bachelor::pi, 0.025, -1, 1));
  }
  A_CP_Bd2Dsth_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "A_CP_Bd2Dsth", uniqueId_, Neutral::pi0, Bachelor::pi, 0.0, 0.02,
      Systematic::NA, Sign::none));
  // Fixed from HFLAV: A_CP+
  A_CP_Bu2D0hst_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
      "A_CP_Bu2D0hst", uniqueId_, Neutral::pi0, Bachelor::pi, 0, -1, 1)),
  // No measured params for B->D*h* modes
      A_CP_Bu2Dst0hst_D0pi0_ = std::shared_ptr<RooRealVar>(
          Params::Get().CreateFloating("A_CP_Bu2Dst0hst_D0pi0", uniqueId_,
                                       Neutral::pi0, Bachelor::pi, 0, -1, 1));
  if (Configuration::Get().splitByCharge() == true) {
    R_ADS_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::pi0, Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_",
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::pi,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0(),
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::pi,
                                      Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
    R_ADS_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::pi0, Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::pi,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN(),
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::pi,
                                      Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN()));
    R_ADS_Bu2Dst0h_D0pi0_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::pi0, Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_WN_",
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::pi,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN(),
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::pi,
                                      Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN()));
  } else {
    R_ADS_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::pi0, Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_",
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::pi,
                                      Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
    R_ADS_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::pi0, Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::pi,
                                      Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN()));
    R_ADS_Bu2Dst0h_D0pi0_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::pi0, Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_WN_",
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::pi,
                                      Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN()));
  }
  R_ADS_Bd2Dsth_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "R_ADS_Bd2Dsth", uniqueId_, Neutral::pi0, Bachelor::k, 1.0, 0.02,
      Systematic::NA, Sign::none));
  // Float to allow B->Dππ to fall in this PDF (only in ADS mode) 
  R_ADS_Bu2D0hst_ = std::shared_ptr<RooRealVar>(
      Params::Get().CreateFloating("R_ADS_Bu2D0hst", uniqueId_,
                                   Neutral::pi0, Bachelor::k, 1, -5, 5));
  // No measured params for B->D*h* modes: just let float 
  R_ADS_Bu2Dst0hst_D0pi0_ = std::shared_ptr<RooRealVar>(
      Params::Get().CreateFloating("R_ADS_Bu2Dst0hst_D0pi0", uniqueId_,
                                   Neutral::pi0, Bachelor::k, 1, -5, 5));

  std::map<std::string, double> mapMisId_Bu2Dst0h_D0pi0;
  std::map<std::string, double> mapMisId_Bu2Dst0h_D0gamma;

  ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi, mapMisId_Bu2Dst0h_D0pi0,
                true);
  ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi, mapMisId_Bu2Dst0h_D0gamma,
                true);

  buDeltaCutEffMisId_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_Bu2Dst0h_D0pi0", uniqueId_, Neutral::pi0,
          mapMisId_Bu2Dst0h_D0pi0["buDeltaCutEff"],
          mapMisId_Bu2Dst0h_D0pi0["buDeltaCutEffErr"],
          Systematic::buDeltaMisIdCutEffs, Sign::same));
  buDeltaCutEffMisId_Bu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_Bu2Dst0h_D0gamma", uniqueId_, Neutral::pi0,
          mapMisId_Bu2Dst0h_D0gamma["buDeltaCutEff"],
          mapMisId_Bu2Dst0h_D0gamma["buDeltaCutEffErr"], Systematic::NA,
          Sign::same));

  deltaCutEffMisId_Bu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_Bu2Dst0h_D0gamma", uniqueId_, Neutral::pi0,
          mapMisId_Bu2Dst0h_D0gamma["deltaCutEff"],
          mapMisId_Bu2Dst0h_D0gamma["deltaCutEffErr"], Systematic::NA,
          Sign::same));
  deltaCutEffMisId_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_Bu2Dst0h_D0pi0", uniqueId_, Neutral::pi0,
          mapMisId_Bu2Dst0h_D0pi0["deltaCutEff"],
          mapMisId_Bu2Dst0h_D0pi0["deltaCutEffErr"],
          Systematic::deltaMisIdCutEffs, Sign::same));
}
