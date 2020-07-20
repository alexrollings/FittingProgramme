#include "NeutralBachelorVars.h"
#include "Params.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- PDF SHAPES -------------------- //
    // -------------------- Bu2Dst0h_D0gamma -------------------- //
    : uniqueId_(uniqueId),
      Bu2Dst0h_D0gamma_sigmaBu_(new RooFormulaVar(
          ("Bu2Dst0h_D0gamma_sigmaBu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0h_D0gamma_sigmaBu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0h_D0gamma_KpiSigmaBu()))),
      pdf1Bu_Bu2Dst0h_D0gamma_(
          ("pdf1Bu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0gamma_meanBu(),
          *Bu2Dst0h_D0gamma_sigmaBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0gamma_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0gamma_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0gamma_(
          ("pdf2Bu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0gamma_meanBu(),
          *Bu2Dst0h_D0gamma_sigmaBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0gamma_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0gamma_n2Bu()),
      pdfBu_Bu2Dst0h_D0gamma_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0h_D0gamma_, pdf2Bu_Bu2Dst0h_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_fracPdf1Bu())),
      pdfBuPartial_Bu2Dst0h_D0gamma_(
          ("pdfBuPartial_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_meanBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_sigmaBuPartial()),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_meanDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_meanDelta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma, Systematic::misIdGammaKPdfDelta,
          Sign::same)),
      misId_Bu2Dst0h_D0gamma_sigmaDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_sigmaDelta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma, Systematic::misIdGammaKPdfDelta,
          Sign::same)),
      misId_Bu2Dst0h_D0gamma_a1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a1Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma, Systematic::misIdGammaKPdfDelta,
          Sign::same)),
      misId_Bu2Dst0h_D0gamma_n1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n1Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma, Systematic::misIdGammaKPdfDelta,
          Sign::same)),
      misId_Bu2Dst0h_D0gamma_a2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a2Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma, Systematic::misIdGammaKPdfDelta,
          Sign::same)),
      misId_Bu2Dst0h_D0gamma_n2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n2Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma, Systematic::misIdGammaKPdfDelta,
          Sign::same)),
      pdf1Delta_misId_Bu2Dst0h_D0gamma_(
          ("pdf1Delta_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0gamma_meanDelta_,
          *misId_Bu2Dst0h_D0gamma_sigmaDelta_, *misId_Bu2Dst0h_D0gamma_a1Delta_,
          *misId_Bu2Dst0h_D0gamma_n1Delta_),
      pdf2Delta_misId_Bu2Dst0h_D0gamma_(
          ("pdf2Delta_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0gamma_meanDelta_,
          *misId_Bu2Dst0h_D0gamma_sigmaDelta_, *misId_Bu2Dst0h_D0gamma_a2Delta_,
          *misId_Bu2Dst0h_D0gamma_n2Delta_),
      misId_Bu2Dst0h_D0gamma_fracPdf1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_fracPdf1Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma, Systematic::misIdGammaKPdfDelta,
          Sign::same)),
      pdfDelta_misId_Bu2Dst0h_D0gamma_(
          new RooAddPdf(("pdfDelta_misId_Bu2Dst0h_D0gamma_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "",
                        RooArgSet(pdf1Delta_misId_Bu2Dst0h_D0gamma_,
                                  pdf2Delta_misId_Bu2Dst0h_D0gamma_),
                        *misId_Bu2Dst0h_D0gamma_fracPdf1Delta_)),
      misId_Bu2Dst0h_D0gamma_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_meanBu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma, Systematic::misIdGammaKPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0gamma_sigmaBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_sigmaBu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma, Systematic::misIdGammaKPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0gamma_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2Dst0pi_D0gamma, Systematic::misIdGammaKPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0gamma_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2Dst0pi_D0gamma, Systematic::misIdGammaKPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0gamma_a2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a2Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2Dst0pi_D0gamma, Systematic::misIdGammaKPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0gamma_n2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n2Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2Dst0pi_D0gamma, Systematic::misIdGammaKPdfBu, Sign::same)),
      pdf1Bu_misId_Bu2Dst0h_D0gamma_(
          ("pdf1Bu_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0gamma_meanBu_, *misId_Bu2Dst0h_D0gamma_sigmaBu_,
          *misId_Bu2Dst0h_D0gamma_a1Bu_, *misId_Bu2Dst0h_D0gamma_n1Bu_),
      pdf2Bu_misId_Bu2Dst0h_D0gamma_(
          ("pdf2Bu_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0gamma_meanBu_, *misId_Bu2Dst0h_D0gamma_sigmaBu_,
          *misId_Bu2Dst0h_D0gamma_a2Bu_, *misId_Bu2Dst0h_D0gamma_n2Bu_),
      misId_Bu2Dst0h_D0gamma_fracPdf1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_fracPdf1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma, Systematic::misIdGammaKPdfBu,
          Sign::same)),
      pdfBu_misId_Bu2Dst0h_D0gamma_(
          new RooAddPdf(("pdfBu_misId_Bu2Dst0h_D0gamma_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "",
                        RooArgSet(pdf1Bu_misId_Bu2Dst0h_D0gamma_,
                                  pdf2Bu_misId_Bu2Dst0h_D0gamma_),
                        *misId_Bu2Dst0h_D0gamma_fracPdf1Bu_)),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      Bu2Dst0h_D0pi0_sigmaBu_(nullptr),
      pdf1Bu_Bu2Dst0h_D0pi0_(),
      pdf2Bu_Bu2Dst0h_D0pi0_(),
      pdfBu_Bu2Dst0h_D0pi0_(new RooCBShape(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_meanBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_sigmaBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_n1Bu())),
      Bu2Dst0h_D0pi0_sigma1BuPartial_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_sigma1BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_sigma1BuPartial(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_KpiSigmaBuPartial()))),
      Bu2Dst0h_D0pi0_sigma2BuPartial_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_sigma2BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0h_D0pi0_sigma1BuPartial_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0pi0_sigmaRatio21BuPartial()))),
      Bu2Dst0h_D0pi0_sigma3BuPartial_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_sigma3BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0h_D0pi0_sigma1BuPartial_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0pi0_sigmaRatio31BuPartial()))),
      pdf1BuPartial_Bu2Dst0h_D0pi0_(
          ("pdf1BuPartial_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_mean1BuPartial(),
          *Bu2Dst0h_D0pi0_sigma1BuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_a1BuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_n1BuPartial()),
      pdf2BuPartial_Bu2Dst0h_D0pi0_(
          ("pdf2BuPartial_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_mean1BuPartial(),
          *Bu2Dst0h_D0pi0_sigma2BuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_a2BuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_n2BuPartial()),
      pdf3BuPartial_Bu2Dst0h_D0pi0_(
          ("pdf3BuPartial_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_mean3BuPartial(),
          *Bu2Dst0h_D0pi0_sigma3BuPartial_),
      pdfBuPartial_Bu2Dst0h_D0pi0_(
          ("pdfBuPartial_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgSet(pdf1BuPartial_Bu2Dst0h_D0pi0_,
                    pdf2BuPartial_Bu2Dst0h_D0pi0_,
                    pdf3BuPartial_Bu2Dst0h_D0pi0_),
          RooArgSet(NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0pi0_fracPdf1BuPartial(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0pi0_fracPdf2BuPartial())),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0pi0_meanDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_meanDelta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfDelta,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_sigmaDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigmaDelta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfDelta,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfDelta,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_n1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfDelta,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a2Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfDelta,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n2Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfDelta,
          Sign::same)),
      pdf1Delta_misId_Bu2Dst0h_D0pi0_(
          ("pdf1Delta_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0pi0_meanDelta_, *misId_Bu2Dst0h_D0pi0_sigmaDelta_,
          *misId_Bu2Dst0h_D0pi0_a1Delta_, *misId_Bu2Dst0h_D0pi0_n1Delta_),
      pdf2Delta_misId_Bu2Dst0h_D0pi0_(
          ("pdf2Delta_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0pi0_meanDelta_, *misId_Bu2Dst0h_D0pi0_sigmaDelta_,
          *misId_Bu2Dst0h_D0pi0_a2Delta_, *misId_Bu2Dst0h_D0pi0_n2Delta_),
      misId_Bu2Dst0h_D0pi0_fracPdf1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_fracPdf1Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfDelta,
          Sign::same)),
      pdfDelta_misId_Bu2Dst0h_D0pi0_(
          new RooAddPdf(("pdfDelta_misId_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "",
                        RooArgSet(pdf1Delta_misId_Bu2Dst0h_D0pi0_,
                                  pdf2Delta_misId_Bu2Dst0h_D0pi0_),
                        *misId_Bu2Dst0h_D0pi0_fracPdf1Delta_)),
      misId_Bu2Dst0h_D0pi0_mean1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_mean1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_mean2Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_sigma2Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0pi0_a2Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_n2Bu_(nullptr),
      pdf1Bu_misId_Bu2Dst0h_D0pi0_(nullptr),
      pdf2Bu_misId_Bu2Dst0h_D0pi0_(),
      misId_Bu2Dst0h_D0pi0_fracPdf1Bu_(nullptr),
      pdfBu_misId_Bu2Dst0h_D0pi0_(new RooCBShape(
          ("pdfBu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_mean1Bu_, *misId_Bu2Dst0h_D0pi0_sigma1Bu_,
          *misId_Bu2Dst0h_D0pi0_a1Bu_, *misId_Bu2Dst0h_D0pi0_n1Bu_)),
      misId_Bu2Dst0h_D0pi0_mean1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_mean1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBuPartial,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_mean2BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_sigma1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBuPartial,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_sigma2BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_a1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBuPartial,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_n1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBuPartial,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_a2BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a2BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBuPartial,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_n2BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n2BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBuPartial,
          Sign::same)),
      pdf1BuPartial_misId_Bu2Dst0h_D0pi0_(
          ("pdf1BuPartial_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_mean1BuPartial_,
          *misId_Bu2Dst0h_D0pi0_sigma1BuPartial_,
          *misId_Bu2Dst0h_D0pi0_a1BuPartial_,
          *misId_Bu2Dst0h_D0pi0_n1BuPartial_),
      pdf2BuPartial_misId_Bu2Dst0h_D0pi0_(
          ("pdf2BuPartial_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_mean1BuPartial_,
          *misId_Bu2Dst0h_D0pi0_sigma1BuPartial_,
          *misId_Bu2Dst0h_D0pi0_a2BuPartial_,
          *misId_Bu2Dst0h_D0pi0_n2BuPartial_),
      misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBuPartial,
          Sign::same)),
      pdfBuPartial_misId_Bu2Dst0h_D0pi0_(
          new RooAddPdf(("pdfBuPartial_misId_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "",
                        RooArgSet(pdf1BuPartial_misId_Bu2Dst0h_D0pi0_,
                                  pdf2BuPartial_misId_Bu2Dst0h_D0pi0_),
                        *misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_)),
      // -------------------- Bu2Dst0h_D0gamma_WN -------------------- //
      Bu2Dst0h_D0gamma_WN_sigma1Bu_(new RooFormulaVar(
          ("Bu2Dst0h_D0gamma_WN_sigma1Bu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0h_D0gamma_WN_sigma1Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0h_D0gamma_WN_KpiSigmaBu()))),
      Bu2Dst0h_D0gamma_WN_sigma2Bu_(
          ("Bu2Dst0h_D0gamma_WN_sigma2Bu" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0h_D0gamma_WN_sigma1Bu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0gamma_WN_sigmaRatio21Bu())),
      pdf1Bu_Bu2Dst0h_D0gamma_WN_(
          ("pdf1Bu_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_WN_mean1Bu(),
          *Bu2Dst0h_D0gamma_WN_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_WN_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_WN_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0gamma_WN_(
          ("pdf2Bu_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_WN_mean2Bu(),
          Bu2Dst0h_D0gamma_WN_sigma2Bu_),
      pdfBu_Bu2Dst0h_D0gamma_WN_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgSet(pdf1Bu_Bu2Dst0h_D0gamma_WN_, pdf2Bu_Bu2Dst0h_D0gamma_WN_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_WN_fracPdf1Bu())),
      Bu2Dst0h_D0gamma_WN_sigmaBuPartial_(new RooFormulaVar(
          ("Bu2Dst0h_D0gamma_WN_sigmaBuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0h_D0gamma_WN_sigmaBuPartial(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0h_D0gamma_WN_KpiSigmaBuPartial()))),
      pdfBuPartial_Bu2Dst0h_D0gamma_WN_(
          ("pdfBuPartial_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_WN_meanBuPartial(),
          *Bu2Dst0h_D0gamma_WN_sigmaBuPartial_),
      // -------------------- Bu2Dst0h_D0pi0_WN -------------------- //
      Bu2Dst0h_D0pi0_WN_sigmaBu_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_WN_sigmaBu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_WN_sigmaBu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_WN_KpiSigmaBu()))),
      pdf1Bu_Bu2Dst0h_D0pi0_WN_(),
      pdf2Bu_Bu2Dst0h_D0pi0_WN_(),
      pdfBu_Bu2Dst0h_D0pi0_WN_(new RooCBShape(
          ("pdfBu_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_meanBu(),
          *Bu2Dst0h_D0pi0_WN_sigmaBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_n1Bu())),
      Bu2Dst0h_D0pi0_WN_sigma1BuPartial_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_WN_sigma1BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_WN_sigma1BuPartial(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_WN_KpiSigmaBuPartial()))),
      Bu2Dst0h_D0pi0_WN_sigma2BuPartial_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_WN_sigma2BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0h_D0pi0_WN_sigma1BuPartial_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0pi0_WN_sigmaRatio21BuPartial()))),
      Bu2Dst0h_D0pi0_WN_sigma3BuPartial_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_WN_sigma3BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0h_D0pi0_WN_sigma1BuPartial_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0pi0_WN_sigmaRatio31BuPartial()))),
      pdf1BuPartial_Bu2Dst0h_D0pi0_WN_(
          ("pdf1BuPartial_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_mean1BuPartial(),
          *Bu2Dst0h_D0pi0_WN_sigma1BuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_a1BuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_n1BuPartial()),
      pdf2BuPartial_Bu2Dst0h_D0pi0_WN_(
          ("pdf2BuPartial_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_mean1BuPartial(),
          *Bu2Dst0h_D0pi0_WN_sigma2BuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_a2BuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_n2BuPartial()),
      pdf3BuPartial_Bu2Dst0h_D0pi0_WN_(
          ("pdf3BuPartial_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_mean3BuPartial(),
          *Bu2Dst0h_D0pi0_WN_sigma3BuPartial_),
      pdfBuPartial_Bu2Dst0h_D0pi0_WN_(
          ("pdfBuPartial_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgSet(pdf1BuPartial_Bu2Dst0h_D0pi0_WN_,
                    pdf2BuPartial_Bu2Dst0h_D0pi0_WN_,
                    pdf3BuPartial_Bu2Dst0h_D0pi0_WN_),
          RooArgSet(NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0pi0_WN_fracPdf1BuPartial(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0pi0_WN_fracPdf2BuPartial())),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0pi0_WN_thresholdDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_thresholdDelta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN,
          Systematic::misIdPi0WNKPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_aDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_aDelta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN,
          Systematic::misIdPi0WNKPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_bDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_bDelta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN,
          Systematic::misIdPi0WNKPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_cDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_cDelta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN,
          Systematic::misIdPi0WNKPdfDelta, Sign::same)),
      pdfDelta_misId_Bu2Dst0h_D0pi0_WN_(
          ("pdfDelta_misId_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0pi0_WN_thresholdDelta_,
          *misId_Bu2Dst0h_D0pi0_WN_cDelta_, *misId_Bu2Dst0h_D0pi0_WN_aDelta_,
          *misId_Bu2Dst0h_D0pi0_WN_bDelta_),
      misId_Bu2Dst0h_D0pi0_WN_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_meanBu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_sigmaBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_sigmaBu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_a1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_n1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu,
          Sign::same)),
      pdfBu_misId_Bu2Dst0h_D0pi0_WN_(new RooCBShape(
          ("pdfBu_misId_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_WN_meanBu_, *misId_Bu2Dst0h_D0pi0_WN_sigmaBu_,
          *misId_Bu2Dst0h_D0pi0_WN_a1Bu_, *misId_Bu2Dst0h_D0pi0_WN_n1Bu_)),
      misId_Bu2Dst0h_D0pi0_WN_meanBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_meanBu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN,
          Systematic::misIdPi0WNKPdfBuPartial, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_sigmaBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_sigmaBu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN,
          Systematic::misIdPi0WNKPdfBuPartial, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_a1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_a1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN,
          Systematic::misIdPi0WNKPdfBuPartial, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_n1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_n1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN,
          Systematic::misIdPi0WNKPdfBuPartial, Sign::same)),
      pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN_(
          ("pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_WN_meanBuPartial_,
          *misId_Bu2Dst0h_D0pi0_WN_sigmaBuPartial_,
          *misId_Bu2Dst0h_D0pi0_WN_a1BuPartial_,
          *misId_Bu2Dst0h_D0pi0_WN_n1BuPartial_),
      // -------------------- MIS-REC -------------------- //
      MisRec_sigmaLBu_(Params::Get().CreateFixed(
          "MisRec_sigmaLBu", uniqueId_, Neutral::gamma, Bachelor::k, 1.2599e+02,
          4.68e+00, Systematic::misRecBuPdf, Sign::same)),
      MisRec_sigmaRBu_(Params::Get().CreateFixed(
          "MisRec_sigmaRBu", uniqueId_, Neutral::gamma, Bachelor::k, 8.0741e+01,
          2.82e+00, Systematic::misRecBuPdf, Sign::same)),
      pdfBu_MisRec_(("pdfBu_MisRec_" +
                     ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId_).MisRec_meanBu(),
                    *MisRec_sigmaLBu_, *MisRec_sigmaRBu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_).MisRec_aLBu(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId_).MisRec_aRBu()),
      MisRec_sigmaLBuPartial_(Params::Get().CreateFixed(
          "MisRec_sigmaLBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          1.1875e+02, 5.43e+00, Systematic::misRecBuPartialPdf, Sign::same)),
      MisRec_sigmaRBuPartial_(Params::Get().CreateFixed(
          "MisRec_sigmaRBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          4.7343e+01, 2.81e+00, Systematic::misRecBuPartialPdf, Sign::same)),
      pdfBuPartial_MisRec_(
          ("pdfBuPartial_MisRec_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).MisRec_meanBuPartial(),
          *MisRec_sigmaLBuPartial_, *MisRec_sigmaRBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).MisRec_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).MisRec_aRBuPartial()),
      // -------------------- Mis-ID ------------------- //
      misId_MisRec_mean1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_mean1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          5.3348e+03, 5.74e-01, Systematic::misIdMisRecKPdfBu, Sign::same)),
      misId_MisRec_mean2Bu_(Params::Get().CreateFixed(
          "misId_MisRec_mean2Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          5.3417e+03, 1.91e-01, Systematic::misIdMisRecKPdfBu, Sign::same)),
      misId_MisRec_sigma1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_sigma1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          1.0688e+02, 1e00, Systematic::NA, Sign::same)),
      misId_MisRec_sigma2Bu_(Params::Get().CreateFixed(
          "misId_MisRec_sigma2Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          2.5076e+01, 1e00, Systematic::NA, Sign::same)),
      misId_MisRec_a1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_a1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          4.8433e+00, 1e00, Systematic::NA, Sign::same)),
      misId_MisRec_a2Bu_(Params::Get().CreateFixed(
          "misId_MisRec_a2Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          -2.9325e-01, 1e00, Systematic::NA, Sign::same)),
      misId_MisRec_n1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_n1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          9.6419e+00, 1e+00, Systematic::NA, Sign::same)),
      misId_MisRec_n2Bu_(Params::Get().CreateFixed(
          "misId_MisRec_n2Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          1.0000e+01, 1e01, Systematic::NA, Sign::same)),
      pdf1Bu_misId_MisRec_(("pdf1Bu_misId_MisRec_" +
                            ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                               .c_str(),
                           "", Configuration::Get().buDeltaMass(),
                           *misId_MisRec_mean1Bu_, *misId_MisRec_sigma1Bu_,
                           *misId_MisRec_a1Bu_, *misId_MisRec_n1Bu_),
      pdf2Bu_misId_MisRec_(("pdf2Bu_misId_MisRec_" +
                            ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                               .c_str(),
                           "", Configuration::Get().buDeltaMass(),
                           *misId_MisRec_mean2Bu_, *misId_MisRec_sigma1Bu_,
                           *misId_MisRec_a2Bu_, *misId_MisRec_n2Bu_),
      misId_MisRec_fracPdf1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_fracPdf1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          5.2164e-01, 3.41e-03, Systematic::misIdMisRecKPdfBu, Sign::same)),
      pdfBu_misId_MisRec_(new RooAddPdf(
          ("pdfBu_misId_MisRec_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", RooArgList(pdf1Bu_misId_MisRec_, pdf2Bu_misId_MisRec_),
          *misId_MisRec_fracPdf1Bu_)),
      misId_MisRec_meanBuPartial_(Params::Get().CreateFixed(
          "misId_MisRec_meanBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          5.3852e+03, 3.62e-04, Systematic::misIdMisRecKPdfBuPartial,
          Sign::same)),
      misId_MisRec_sigmaLBuPartial_(Params::Get().CreateFixed(
          "misId_MisRec_sigmaLBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, 1.0686e+02, 4.24e-01,
          Systematic::misIdMisRecKPdfBuPartial, Sign::same)),
      misId_MisRec_sigmaRBuPartial_(Params::Get().CreateFixed(
          "misId_MisRec_sigmaRBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, 6.8440e+01, 3.85e-01,
          Systematic::misIdMisRecKPdfBuPartial, Sign::same)),
      misId_MisRec_aLBuPartial_(Params::Get().CreateFixed(
          "misId_MisRec_aLBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          3.4482e-02, 1e00, Systematic::NA, Sign::same)),
      misId_MisRec_aRBuPartial_(Params::Get().CreateFixed(
          "misId_MisRec_aRBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          1.6765e-01, 1e00, Systematic::NA, Sign::same)),
      pdfBuPartial_misId_MisRec_(
          ("pdfBuPartial_misId_MisRec_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_MisRec_meanBuPartial_,
          *misId_MisRec_sigmaLBuPartial_, *misId_MisRec_sigmaRBuPartial_,
          *misId_MisRec_aLBuPartial_, *misId_MisRec_aRBuPartial_),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_sigmaLBu_(("Bu2D0h_sigmaLBu_" +
                        ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                           .c_str(),
                       // "", 8.8989e+01, 10, 150),
                       // Fixed from data
                       "", 1.1025e+02),
      Bu2D0h_sigmaRBu_(("Bu2D0h_sigmaRBu_" +
                        ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                           .c_str(),
                       // "", 7.5978e+01, 10, 150),
                       // Fixed from data
                       "", 7.2797e+01),
      pdfBu_Bu2D0h_(("pdfBu_Bu2D0h_" +
                     ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0h_meanBu(),
                    Bu2D0h_sigmaLBu_, Bu2D0h_sigmaRBu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0h_aLBu(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0h_aRBu()),
      Bu2D0h_sigmaLBuPartial_(
          ("Bu2D0h_sigmaLBuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          // "", 4.8679e+01, 10, 100),
          // Fixed from data
          "", 5.8654e+01),
      Bu2D0h_sigmaRBuPartial_(
          ("Bu2D0h_sigmaRBuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          // "", 3.5437e+01, 10, 60),
          // Fixed from data
          "", 2.8177e+01),
      pdfBuPartial_Bu2D0h_(
          ("pdfBuPartial_Bu2D0h_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0h_meanBuPartial(),
          Bu2D0h_sigmaLBuPartial_, Bu2D0h_sigmaRBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0h_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0h_aRBuPartial()),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2D0h_meanBu_(("misId_Bu2D0h_meanBu_" +
                            ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                               .c_str(),
                           "", 5.6025e+03),
      misId_Bu2D0h_sigmaLBu_(
          ("misId_Bu2D0h_sigmaLBu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 1.0153e+02),
      misId_Bu2D0h_sigmaRBu_(
          ("misId_Bu2D0h_sigmaRBu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 8.5936e+01),
      misId_Bu2D0h_aLBu_(("misId_Bu2D0h_aLBu_" +
                          ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", 1.9114e-10),
      misId_Bu2D0h_aRBu_(("misId_Bu2D0h_aRBu_" +
                          ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", 1.8313e-08),
      pdfBu_misId_Bu2D0h_(("pdfBu_misId_Bu2D0h_" +
                           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                              .c_str(),
                          "", Configuration::Get().buDeltaMass(),
                          misId_Bu2D0h_meanBu_, misId_Bu2D0h_sigmaLBu_,
                          misId_Bu2D0h_sigmaRBu_, misId_Bu2D0h_aLBu_,
                          misId_Bu2D0h_aRBu_),
      misId_Bu2D0h_meanBuPartial_(
          ("misId_Bu2D0h_meanBuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 5.5945e+03),
      misId_Bu2D0h_sigmaLBuPartial_(
          ("misId_Bu2D0h_sigmaLBuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 5.4608e+01),
      misId_Bu2D0h_sigmaRBuPartial_(
          ("misId_Bu2D0h_sigmaRBuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 4.5399e+01),
      misId_Bu2D0h_aLBuPartial_(
          ("misId_Bu2D0h_aLBuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 1.1435e-01),
      misId_Bu2D0h_aRBuPartial_(
          ("misId_Bu2D0h_aRBuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 2.6725e-01),
      pdfBuPartial_misId_Bu2D0h_(
          ("pdfBuPartial_misId_Bu2D0h_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), misId_Bu2D0h_meanBuPartial_,
          misId_Bu2D0h_sigmaLBuPartial_, misId_Bu2D0h_sigmaRBuPartial_,
          misId_Bu2D0h_aLBuPartial_, misId_Bu2D0h_aRBuPartial_),
      // -------------------- PART REC -------------------- //
      PartRec_D0pi0_sigmaLBu_(nullptr),
      PartRec_D0pi0_sigmaRBu_(nullptr),
      pdfBu_PartRec_D0pi0_(
          ("pdfBu_PartRec_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_D0pi0_meanBu(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
              .PartRec_D0pi0_sigmaLBu(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
              .PartRec_D0pi0_sigmaRBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_D0pi0_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_D0pi0_aRBu()),
      PartRec_D0gamma_sigmaLBu_(nullptr),
      PartRec_D0gamma_sigmaRBu_(nullptr),
      pdfBu_PartRec_D0gamma_(
          ("pdfBu_PartRec_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_D0gamma_meanBu(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
              .PartRec_D0gamma_sigmaLBu(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
              .PartRec_D0gamma_sigmaRBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_D0gamma_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_D0gamma_aRBu()),
      pdfBu_PartRec_(new RooAddPdf(
          ("pdfBu_PartRec_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", RooArgSet(pdfBu_PartRec_D0pi0_, pdfBu_PartRec_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_frac_D0pi0())),
      PartRec_sigmaLBuPartial_(nullptr),
      PartRec_sigmaRBuPartial_(nullptr),
      pdfBuPartial_PartRec_(
          ("pdfBuPartial_PartRec_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_meanBuPartial(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
              .PartRec_sigmaLBuPartial(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
              .PartRec_sigmaRBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_aRBuPartial()),
      // -------------------- Mis-ID ------------------- //
      misId_PartRec_meanBu_(Params::Get().CreateFixed(
          "misId_PartRec_meanBu", uniqueId_, Neutral::gamma, Bachelor::k,
          5.1777e+03, 1.60e+00, Systematic::misIdPartRecKPdfBu, Sign::same)),
      misId_PartRec_sigmaLBu_(Params::Get().CreateFixed(
          "misId_PartRec_sigmaLBu", uniqueId_, Neutral::gamma, Bachelor::k,
          7.5677e+01, 9.46e-01, Systematic::misIdPartRecKPdfBu, Sign::same)),
      misId_PartRec_sigmaRBu_(Params::Get().CreateFixed(
          "misId_PartRec_sigmaRBu", uniqueId_, Neutral::gamma, Bachelor::k,
          9.4379e+01, 1.81e+00, Systematic::misIdPartRecKPdfBu, Sign::same)),
      misId_PartRec_aLBu_(Params::Get().CreateFixed(
          "misId_PartRec_aLBu", uniqueId_, Neutral::gamma, Bachelor::k,
          1.4242e-07, 9.03e-04, Systematic::misIdPartRecKPdfBu, Sign::same)),
      misId_PartRec_aRBu_(Params::Get().CreateFixed(
          "misId_PartRec_aRBu", uniqueId_, Neutral::gamma, Bachelor::k,
          1.5130e-01, 6.63e-03, Systematic::misIdPartRecKPdfBu, Sign::same)),
      pdfBu_misId_PartRec_(("pdfBu_misId_PartRec_" +
                            ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                               .c_str(),
                           "", Configuration::Get().buDeltaMass(),
                           *misId_PartRec_meanBu_, *misId_PartRec_sigmaLBu_,
                           *misId_PartRec_sigmaRBu_, *misId_PartRec_aLBu_,
                           *misId_PartRec_aRBu_),
      misId_PartRec_meanBuPartial_(Params::Get().CreateFixed(
          "misId_PartRec_meanBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          5.1749e+03, 1.64e+00, Systematic::misIdPartRecKPdfBuPartial,
          Sign::same)),
      misId_PartRec_sigmaLBuPartial_(Params::Get().CreateFixed(
          "misId_PartRec_sigmaLBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, 4.4104e+01, 1.73e+00,
          Systematic::misIdPartRecKPdfBuPartial, Sign::same)),
      misId_PartRec_sigmaRBuPartial_(Params::Get().CreateFixed(
          "misId_PartRec_sigmaRBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, 8.2109e+01, 1.58e+00,
          Systematic::misIdPartRecKPdfBuPartial, Sign::same)),
      misId_PartRec_aLBuPartial_(Params::Get().CreateFixed(
          "misId_PartRec_aLBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          6.3065e-02, 1.62e-02, Systematic::misIdPartRecKPdfBuPartial,
          Sign::same)),
      misId_PartRec_aRBuPartial_(Params::Get().CreateFixed(
          "misId_PartRec_aRBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          1.7893e-01, 4.21e-03, Systematic::misIdPartRecKPdfBuPartial,
          Sign::same)),
      pdfBuPartial_misId_PartRec_(
          ("pdfBuPartial_misId_PartRec_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_PartRec_meanBuPartial_,
          *misId_PartRec_sigmaLBuPartial_, *misId_PartRec_sigmaRBuPartial_,
          *misId_PartRec_aLBuPartial_, *misId_PartRec_aRBuPartial_),
      // -------------------- Bs2Dst0Kpi -------------------- //
      Bs2Dst0Kpi_thresholdDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_thresholdDelta", uniqueId_, Neutral::gamma, Bachelor::k,
          5.3560e+02, 1e00, Systematic::NA, Sign::same)),
      Bs2Dst0Kpi_aDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_aDelta", uniqueId_, Neutral::gamma, Bachelor::k,
          -6.8532e-01, 1e00, Systematic::NA, Sign::none)),
      Bs2Dst0Kpi_bDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_bDelta", uniqueId_, Neutral::gamma, Bachelor::k,
          -1.1526e-01, 1e00, Systematic::NA, Sign::none)),
      Bs2Dst0Kpi_cDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_cDelta", uniqueId_, Neutral::gamma, Bachelor::k,
          3.4981e+01, 1e00, Systematic::NA, Sign::same)),
      pdfFlatDelta_Bs2Dst0Kpi_(
          ("pdfFlatDelta_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2Dst0Kpi_thresholdDelta_,
          *Bs2Dst0Kpi_cDelta_, *Bs2Dst0Kpi_aDelta_, *Bs2Dst0Kpi_bDelta_),
      Bs2Dst0Kpi_meanDeltaGamma_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_meanDeltaGamma", uniqueId_, Neutral::gamma, Bachelor::k,
          1.4798e+02, 8.42e-01, Systematic::Bs2Dst0KpiDeltaPdf, Sign::same)),
      Bs2Dst0Kpi_sigmaDeltaGamma_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigmaDeltaGamma", uniqueId_, Neutral::gamma, Bachelor::k,
          4.3913e+00, 1.26e+00, Systematic::Bs2Dst0KpiDeltaPdf, Sign::same)),
      pdfPeak1DeltaGamma_Bs2Dst0Kpi_(
          ("pdfPeak1DeltaGamma_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2Dst0Kpi_meanDeltaGamma_,
          *Bs2Dst0Kpi_sigmaDeltaGamma_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_a1Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_n1Delta()),
      pdfPeak2DeltaGamma_Bs2Dst0Kpi_(
          ("pdfPeak2DeltaGamma_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2Dst0Kpi_meanDeltaGamma_,
          *Bs2Dst0Kpi_sigmaDeltaGamma_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_a2Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_n2Delta()),
      pdfPeakDeltaGamma_Bs2Dst0Kpi_(
          ("pdfPeakDeltaGamma_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgList(pdfPeak1DeltaGamma_Bs2Dst0Kpi_,
                     pdfPeak2DeltaGamma_Bs2Dst0Kpi_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_fracPdf1Delta()),
      Bs2Dst0Kpi_fracPeakDeltaGamma_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_fracPeakDeltaGamma", uniqueId_, Neutral::gamma,
          Bachelor::k, 1.9825e-01, 1.54e-02, Systematic::Bs2Dst0KpiDeltaPdf,
          Sign::same)),
      Bs2Dst0Kpi_meanDeltaPi0_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_meanDeltaPi0", uniqueId_, Neutral::gamma, Bachelor::k,
          8.3246e+01, 1e00, Systematic::NA, Sign::same)),
      Bs2Dst0Kpi_sigmaDeltaPi0_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigmaDeltaPi0", uniqueId_, Neutral::gamma, Bachelor::k,
          7.1822e+00, 6.29e-01, Systematic::Bs2Dst0KpiDeltaPdf, Sign::same)),
      pdfPeak1DeltaPi0_Bs2Dst0Kpi_(
          ("pdfPeak1DeltaPi0_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2Dst0Kpi_meanDeltaPi0_,
          *Bs2Dst0Kpi_sigmaDeltaPi0_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_a1Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_n1Delta()),
      pdfPeak2DeltaPi0_Bs2Dst0Kpi_(
          ("pdfPeak2DeltaPi0_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2Dst0Kpi_meanDeltaPi0_,
          *Bs2Dst0Kpi_sigmaDeltaPi0_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_a2Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_n2Delta()),
      pdfPeakDeltaPi0_Bs2Dst0Kpi_(
          ("pdfPeakDeltaPi0_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgList(pdfPeak1DeltaPi0_Bs2Dst0Kpi_,
                     pdfPeak2DeltaPi0_Bs2Dst0Kpi_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_fracPdf1Delta()),
      Bs2Dst0Kpi_fracPeakDeltaPi0_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_fracPeakDeltaPi0", uniqueId_, Neutral::gamma, Bachelor::k,
          3.8063e-02, 9.22e-03, Systematic::Bs2Dst0KpiDeltaPdf, Sign::same)),
      pdfDelta_Bs2Dst0Kpi_(
          ("pdfDelta_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgList(pdfPeakDeltaGamma_Bs2Dst0Kpi_, pdfPeakDeltaPi0_Bs2Dst0Kpi_,
                     pdfFlatDelta_Bs2Dst0Kpi_),
          RooArgList(*Bs2Dst0Kpi_fracPeakDeltaGamma_,
                     *Bs2Dst0Kpi_fracPeakDeltaPi0_)),
      Bs2Dst0Kpi_mean1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_mean1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          5.2158e+03, 4.38e-01, Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_sigma1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigma1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          1.6977e+01, 3.42e-01, Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      Bs2Dst0Kpi_a1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_a1Bu", uniqueId_, Neutral::gamma, Bachelor::k, 4.8897e-01,
          1e00, Systematic::NA, Sign::same)),
      Bs2Dst0Kpi_n1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_n1Bu", uniqueId_, Neutral::gamma, Bachelor::k, 1.0000e+01,
          1e00, Systematic::NA, Sign::same)),
      Bs2Dst0Kpi_mean2Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_mean2Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          5.2082e+03, 1e00, Systematic::NA, Sign::same)),
      Bs2Dst0Kpi_sigma2Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigma2Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          8.5925e+01, 1e00, Systematic::NA, Sign::same)),
      pdf1Bu_Bs2Dst0Kpi_(("pdf1Bu_Bs2Dst0Kpi_" +
                          ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", Configuration::Get().buDeltaMass(),
                         *Bs2Dst0Kpi_mean1Bu_, *Bs2Dst0Kpi_sigma1Bu_,
                         *Bs2Dst0Kpi_a1Bu_, *Bs2Dst0Kpi_n1Bu_),
      pdf2Bu_Bs2Dst0Kpi_(("pdf2Bu_Bs2Dst0Kpi_" +
                          ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", Configuration::Get().buDeltaMass(),
                         *Bs2Dst0Kpi_mean2Bu_, *Bs2Dst0Kpi_sigma2Bu_),
      Bs2Dst0Kpi_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_fracPdf1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          6.4056e-01, 9.92e-03, Systematic::Bs2Dst0KpiBuPdf, Sign::same)),
      pdfBu_Bs2Dst0Kpi_(
          new RooAddPdf(("pdfBu_Bs2Dst0Kpi_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "", RooArgList(pdf1Bu_Bs2Dst0Kpi_, pdf2Bu_Bs2Dst0Kpi_),
                        *Bs2Dst0Kpi_fracPdf1Bu_)),
      Bs2Dst0Kpi_meanBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_meanBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          5.2177e+03, 1.30e+00, Systematic::Bs2Dst0KpiBuPartialPdf,
          Sign::same)),
      Bs2Dst0Kpi_sigmaLBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigmaLBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          3.2619e+01, 1.14e+00, Systematic::Bs2Dst0KpiBuPartialPdf,
          Sign::same)),
      Bs2Dst0Kpi_sigmaRBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigmaRBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          3.5797e+01, 1.09e+00, Systematic::Bs2Dst0KpiBuPartialPdf,
          Sign::same)),
      Bs2Dst0Kpi_aLBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_aLBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          1.3275e-01, 9.59e-03, Systematic::Bs2Dst0KpiBuPartialPdf,
          Sign::same)),
      Bs2Dst0Kpi_aRBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_aRBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          6.5298e-02, 8.39e-03, Systematic::Bs2Dst0KpiBuPartialPdf,
          Sign::same)),
      pdfBuPartial_Bs2Dst0Kpi_(
          ("pdfBuPartial_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2Dst0Kpi_meanBuPartial_,
          *Bs2Dst0Kpi_sigmaLBuPartial_, *Bs2Dst0Kpi_sigmaRBuPartial_,
          *Bs2Dst0Kpi_aLBuPartial_, *Bs2Dst0Kpi_aRBuPartial_),
      // -------------------- Bs2D0Kpi -------------------- //
      Bs2D0Kpi_thresholdDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_thresholdDelta", uniqueId_, Neutral::gamma, Bachelor::k,
          6.0000e+01, 2.39e-02, Systematic::Bs2D0KpiDeltaPdf, Sign::same)),
      Bs2D0Kpi_aDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_aDelta", uniqueId_, Neutral::gamma, Bachelor::k, 5.4698e-01,
          1.77e-01, Systematic::Bs2D0KpiDeltaPdf, Sign::none)),
      Bs2D0Kpi_bDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_bDelta", uniqueId_, Neutral::gamma, Bachelor::k,
          -5.5240e-01, 2.29e-01, Systematic::Bs2D0KpiDeltaPdf, Sign::none)),
      Bs2D0Kpi_cDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_cDelta", uniqueId_, Neutral::gamma, Bachelor::k, 4.7687e+01,
          1e00, Systematic::NA, Sign::same)),
      pdfDelta_Bs2D0Kpi_(("pdfDelta_Bs2D0Kpi_" +
                          ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", Configuration::Get().deltaMass(),
                         *Bs2D0Kpi_thresholdDelta_, *Bs2D0Kpi_cDelta_,
                         *Bs2D0Kpi_aDelta_, *Bs2D0Kpi_bDelta_),
      Bs2D0Kpi_mean1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_mean1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          5.2304e+03, 3.81e+01, Systematic::Bs2D0KpiBuPdf, Sign::same)),
      Bs2D0Kpi_sigma1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_sigma1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          9.3801e+01, 2.32e+01, Systematic::Bs2D0KpiBuPdf, Sign::same)),
      Bs2D0Kpi_a1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_a1Bu", uniqueId_, Neutral::gamma, Bachelor::k, 2.9093e+00,
          1e00, Systematic::NA, Sign::same)),
      Bs2D0Kpi_n1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_n1Bu", uniqueId_, Neutral::gamma, Bachelor::k, 1.4041e-01,
          1e00, Systematic::NA, Sign::same)),
      Bs2D0Kpi_mean2Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_mean2Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          9.9628e+01, 5.97e+00, Systematic::Bs2D0KpiBuPdf, Sign::same)),
      Bs2D0Kpi_sigma2Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_sigma2Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          1.4041e-01, 1e00, Systematic::NA, Sign::same)),
      pdf1Bu_Bs2D0Kpi_(("pdf1Bu_Bs2D0Kpi_" +
                        ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                           .c_str(),
                       "", Configuration::Get().buDeltaMass(),
                       *Bs2D0Kpi_mean1Bu_, *Bs2D0Kpi_sigma1Bu_, *Bs2D0Kpi_a1Bu_,
                       *Bs2D0Kpi_n1Bu_),
      pdf2Bu_Bs2D0Kpi_(("pdf2Bu_Bs2D0Kpi_" +
                        ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                           .c_str(),
                       "", Configuration::Get().buDeltaMass(),
                       *Bs2D0Kpi_mean2Bu_, *Bs2D0Kpi_sigma2Bu_),
      Bs2D0Kpi_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_fracPdf1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          1.2273e-01, 1e00, Systematic::NA, Sign::same)),
      pdfBu_Bs2D0Kpi_(
          new RooAddPdf(("pdfBu_Bs2D0Kpi_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "", RooArgList(pdf1Bu_Bs2D0Kpi_, pdf2Bu_Bs2D0Kpi_),
                        *Bs2D0Kpi_fracPdf1Bu_)),
      Bs2D0Kpi_meanBuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kpi_meanBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          5.3230e+03, 9.23e+00, Systematic::Bs2D0KpiBuPartialPdf, Sign::same)),
      Bs2D0Kpi_sigmaLBuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kpi_sigmaLBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          8.3476e+01, 5.23e+00, Systematic::Bs2D0KpiBuPartialPdf, Sign::same)),
      Bs2D0Kpi_sigmaRBuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kpi_sigmaRBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          1.0900e+02, 1.01e+01, Systematic::Bs2D0KpiBuPartialPdf, Sign::same)),
      Bs2D0Kpi_aLBuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kpi_aLBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          4.3590e-08, 2.85e-02, Systematic::Bs2D0KpiBuPartialPdf, Sign::same)),
      Bs2D0Kpi_aRBuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kpi_aRBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          2.6176e-10, 1.50e-01, Systematic::Bs2D0KpiBuPartialPdf, Sign::same)),
      pdfBuPartial_Bs2D0Kpi_(
          ("pdfBuPartial_Bs2D0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2D0Kpi_meanBuPartial_,
          *Bs2D0Kpi_sigmaLBuPartial_, *Bs2D0Kpi_sigmaRBuPartial_,
          *Bs2D0Kpi_aLBuPartial_, *Bs2D0Kpi_aRBuPartial_),
      // -------------------- Correct ID BOX EFFs -------------------- //
      buEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::k, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::k,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::k, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::k, Efficiency::buEffErr,
                        false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::k,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::k,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::k, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::k,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::k,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::k,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::k, Efficiency::deltaEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::k,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::k,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::k,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::k,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::k,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      buPartialEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::k,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::k,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::same)),
      buPartialEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::k,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::k,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::same)),
      buPartialEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::k,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::k,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::same)),
      buPartialEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::k,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::k,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::same)),
      // -------------------- Mis-ID BoxEffs ------------------- //
      buEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::k, Efficiency::buEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::k,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::same)),
      buEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::k, Efficiency::buEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::k,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::same)),
      buEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::k,
                        Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::k,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::same)),
      deltaEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::k,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::k,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::same)),
      deltaEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::k,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::k,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::same)),
      deltaEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::k,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::k,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::same)),
      buPartialEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::k,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::k,
                        Efficiency::buPartialEffErr, true),
          Systematic::NA, Sign::same)),
      buPartialEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::k,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::k,
                        Efficiency::buPartialEffErr, true),
          Systematic::NA, Sign::same)),
      buPartialEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::k,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::k,
                        Efficiency::buPartialEffErr, true),
          Systematic::NA, Sign::same)),
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
      mcEff_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma_WN, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma_WN, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0_WN, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0_WN, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_MisRec_(Params::Get().CreateFixed("mcEff_MisRec", uniqueId_,
                                              Neutral::gamma, Bachelor::k, 1.0,
                                              0.0, Systematic::NA, Sign::same)),
      mcEff_Bu2D0h_(Params::Get().CreateFixed(
          "mcEff_Bu2D0h", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnMCEffs(Mode::Bu2D0K, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2D0K, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_PartRec_(Params::Get().CreateFixed(
          "mcEff_PartRec", uniqueId_, Neutral::gamma, Bachelor::k, 1.0, 0.0,
          Systematic::NA, Sign::same)),
      mcEff_Bs2Dst0Kpi_(Params::Get().CreateFixed(
          "mcEff_Bs2Dst0Kpi", uniqueId_, Neutral::gamma, Bachelor::k, 1.0, 0.0,
          Systematic::NA, Sign::same)),
      mcEff_Bs2D0Kpi_(Params::Get().CreateFixed(
          "mcEff_Bs2D0Kpi", uniqueId_, Neutral::gamma, Bachelor::k, 1.0, 0.0,
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
      R_ADS_Bu2Dst0h_D0gamma_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_(nullptr),
      R_ADS_Bu2Dst0h_D0gamma_WN_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_WN_(nullptr) {
  if (Configuration::Get().blindFit() == true) {
    A_CP_Bu2Dst0h_D0gamma_Blind_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0gamma_Blind", uniqueId_, Neutral::gamma,
            Bachelor::k, 0.276, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_Blind_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0pi0_Blind", uniqueId_, Neutral::gamma, Bachelor::k,
            -0.151, -1, 1));
    A_CP_Bu2Dst0h_D0gamma_WN_Blind_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0gamma_WN_Blind", uniqueId_, Neutral::gamma,
            Bachelor::k, 0.276, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_WN_Blind_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0pi0_WN_Blind", uniqueId_, Neutral::gamma,
            Bachelor::k, -0.151, -1, 1));
    A_CP_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooUnblindUniform>(
        MakeBlind(("A_CP_Bu2Dst0h_D0gamma_" +
                   ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                      .c_str(),
                  0.03, *A_CP_Bu2Dst0h_D0gamma_Blind_));
    A_CP_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooUnblindUniform>(
        MakeBlind(("A_CP_Bu2Dst0h_D0pi0_" +
                   ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                      .c_str(),
                  0.03, *A_CP_Bu2Dst0h_D0pi0_Blind_));
    A_CP_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooUnblindUniform>(
        MakeBlind(("A_CP_Bu2Dst0h_D0gamma_WN_" +
                   ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                      .c_str(),
                  0.03, *A_CP_Bu2Dst0h_D0gamma_WN_Blind_));
    A_CP_Bu2Dst0h_D0pi0_WN_ = std::shared_ptr<RooUnblindUniform>(
        MakeBlind(("A_CP_Bu2Dst0h_D0pi0_WN_" +
                   ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                      .c_str(),
                  0.03, *A_CP_Bu2Dst0h_D0pi0_WN_Blind_));
  } else {
    A_CP_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma, Bachelor::k,
            0.276, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma, Bachelor::k,
            -0.151, -1, 1));
    A_CP_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::gamma, Bachelor::k,
            0.276, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_WN_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::gamma, Bachelor::k,
            -0.151, -1, 1));
  }
  if (Configuration::Get().splitByCharge() == true) {
    R_ADS_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::gamma, Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_",
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma(),
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k,
                                      Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma()));
    R_ADS_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::gamma, Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_",
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0(),
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k,
                                      Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
    R_ADS_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::gamma, Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN(),
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k,
                                      Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN()));
    R_ADS_Bu2Dst0h_D0pi0_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::gamma, Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_WN_",
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN(),
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k,
                                      Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN()));
  } else {
    R_ADS_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::gamma, Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_",
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k,
                                      Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma()));
    R_ADS_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::gamma, Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_",
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k,
                                      Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
    R_ADS_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::gamma, Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k,
                                      Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN()));
    R_ADS_Bu2Dst0h_D0pi0_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::gamma, Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_WN_",
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k,
                                      Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN()));
  }

  std::map<std::string, double> mapMisId_Bu2Dst0h_D0gamma;
  std::map<std::string, double> mapMisId_Bu2Dst0h_D0pi0;
  std::map<std::string, double> mapMisId_Bu2D0h;
  std::map<std::string, double> mapBs2Dst0Kpi;
  std::map<std::string, double> mapBs2D0Kpi;

  ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::k, mapMisId_Bu2Dst0h_D0gamma,
                true);
  ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::k, mapMisId_Bu2Dst0h_D0pi0,
                true);
  ReturnBoxEffs(Mode::Bu2D0pi, Bachelor::k, mapMisId_Bu2D0h, true);
  ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k, mapBs2Dst0Kpi, false);
  ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, mapBs2D0Kpi, false);

  std::map<Mode, double> misRecModesMap = {
      {Mode::Bu2Dst0pi_D0pi0_WN,
       NeutralVars<Neutral::gamma>::Get(uniqueId_)
               .fracMisRec_Bu2Dst0h_D0pi0_WN() /
           NeutralVars<Neutral::gamma>::Get(uniqueId_).fracMisRec()},
      {Mode::Bu2Dst0pi_D0gamma_WN,
       NeutralVars<Neutral::gamma>::Get(uniqueId_)
               .fracMisRec_Bu2Dst0h_D0gamma_WN() /
           NeutralVars<Neutral::gamma>::Get(uniqueId_).fracMisRec()},
      {Mode::Bu2D0rho,
       NeutralVars<Neutral::gamma>::Get(uniqueId_).fracMisRec_Bu2D0hst() /
           NeutralVars<Neutral::gamma>::Get(uniqueId_).fracMisRec()},
      {Mode::Bd2Dstpi,
       NeutralVars<Neutral::gamma>::Get(uniqueId_).fracMisRec_Bd2Dsth() /
           NeutralVars<Neutral::gamma>::Get(uniqueId_).fracMisRec()}};

  std::map<std::string, double> mapMisId_MisRec;
  unsigned int it = 0;
  for (auto &m : misRecModesMap) {
    std::map<std::string, double> mapMisId_MisRecTmp;
    ReturnBoxEffs(m.first, Bachelor::k, mapMisId_MisRecTmp, true);
    if (it == 0) {
      mapMisId_MisRec.insert(std::pair<std::string, double>(
          "buDeltaCutEff", mapMisId_MisRecTmp["buDeltaCutEff"] * m.second));
      mapMisId_MisRec.insert(std::pair<std::string, double>(
          "deltaCutEff", mapMisId_MisRecTmp["deltaCutEff"] * m.second));
      if (Configuration::Get().fitBuPartial() == true) {
        mapMisId_MisRec.insert(std::pair<std::string, double>(
            "deltaPartialCutEff",
            mapMisId_MisRecTmp["deltaPartialCutEff"] * m.second));
      }
    } else {
      mapMisId_MisRec["buDeltaCutEff"] +=
          mapMisId_MisRecTmp["buDeltaCutEff"] * m.second;
      mapMisId_MisRec["deltaCutEff"] +=
          mapMisId_MisRecTmp["deltaCutEff"] * m.second;
      if (Configuration::Get().fitBuPartial() == true) {
        mapMisId_MisRec["deltaPartialCutEff"] +=
            mapMisId_MisRecTmp["deltaPartialCutEff"] * m.second;
      }
    }
    ++it;
  }

  std::map<Mode, double> partRecModesMap = {
      {Mode::Bu2Dst0rho_D0pi0,
       NeutralVars<Neutral::gamma>::Get(uniqueId_)
               .fracPartRec_Bu2Dst0hst_D0pi0() /
           NeutralVars<Neutral::gamma>::Get(uniqueId_).fracPartRec()},
      {Mode::Bu2Dst0rho_D0gamma,
       NeutralVars<Neutral::gamma>::Get(uniqueId_)
               .fracPartRec_Bu2Dst0hst_D0gamma() /
           NeutralVars<Neutral::gamma>::Get(uniqueId_).fracPartRec()}};

  std::map<std::string, double> mapMisId_PartRec;
  it = 0;
  for (auto &m : misRecModesMap) {
    std::map<std::string, double> mapMisId_PartRecTmp;
    ReturnBoxEffs(m.first, Bachelor::k, mapMisId_PartRecTmp, true);
    if (it == 0) {
      mapMisId_PartRec.insert(std::pair<std::string, double>(
          "buDeltaCutEff", mapMisId_PartRecTmp["buDeltaCutEff"] * m.second));
      mapMisId_PartRec.insert(std::pair<std::string, double>(
          "deltaCutEff", mapMisId_PartRecTmp["deltaCutEff"] * m.second));
      if (Configuration::Get().fitBuPartial() == true) {
        mapMisId_PartRec.insert(std::pair<std::string, double>(
            "deltaPartialCutEff",
            mapMisId_PartRecTmp["deltaPartialCutEff"] * m.second));
      }
    } else {
      mapMisId_PartRec["buDeltaCutEff"] +=
          mapMisId_PartRecTmp["buDeltaCutEff"] * m.second;
      mapMisId_PartRec["deltaCutEff"] +=
          mapMisId_PartRecTmp["deltaCutEff"] * m.second;
      if (Configuration::Get().fitBuPartial() == true) {
        mapMisId_PartRec["deltaPartialCutEff"] +=
            mapMisId_PartRecTmp["deltaPartialCutEff"] * m.second;
      }
    }
    ++it;
  }

  buDeltaCutEffMisId_Bu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma,
          mapMisId_Bu2Dst0h_D0gamma["buDeltaCutEff"],
          mapMisId_Bu2Dst0h_D0gamma["buDeltaCutEffErr"],
          Systematic::buDeltaMisIdCutEffs, Sign::same));
  buDeltaCutEffMisId_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma,
          mapMisId_Bu2Dst0h_D0pi0["buDeltaCutEff"],
          mapMisId_Bu2Dst0h_D0pi0["buDeltaCutEffErr"],
          Systematic::buDeltaMisIdCutEffs, Sign::same));
  buDeltaCutEffMisId_Bu2D0h_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_Bu2D0h", uniqueId_, Neutral::gamma,
          mapMisId_Bu2D0h["buDeltaCutEff"], mapMisId_Bu2D0h["buDeltaCutEffErr"],
          Systematic::NA, Sign::same));
  buDeltaCutEffMisId_MisRec_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_MisRec", uniqueId_, Neutral::gamma,
          mapMisId_MisRec["buDeltaCutEff"], mapMisId_MisRec["buDeltaCutEffErr"],
          Systematic::buDeltaMisIdCutEffs, Sign::same));
  buDeltaCutEffMisId_PartRec_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_PartRec", uniqueId_, Neutral::gamma,
          mapMisId_PartRec["buDeltaCutEff"],
          mapMisId_PartRec["buDeltaCutEffErr"], Systematic::buDeltaMisIdCutEffs,
          Sign::same));
  buDeltaCutEffBs2Dst0Kpi_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffBs2Dst0Kpi", uniqueId_, Neutral::gamma, Bachelor::k,
          mapBs2Dst0Kpi["buDeltaCutEff"], mapBs2Dst0Kpi["buDeltaCutEffErr"],
          Systematic::buDeltaCutEffs, Sign::same));
  buDeltaCutEffBs2D0Kpi_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffBs2D0Kpi", uniqueId_, Neutral::gamma, Bachelor::k,
          mapBs2D0Kpi["buDeltaCutEff"], mapBs2D0Kpi["buDeltaCutEffErr"],
          Systematic::buDeltaCutEffs, Sign::same));
  deltaCutEffMisId_Bu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma,
          mapMisId_Bu2Dst0h_D0gamma["deltaCutEff"],
          mapMisId_Bu2Dst0h_D0gamma["deltaCutEffErr"],
          Systematic::deltaMisIdCutEffs, Sign::same));

  deltaCutEffMisId_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma,
          mapMisId_Bu2Dst0h_D0pi0["deltaCutEff"],
          mapMisId_Bu2Dst0h_D0pi0["deltaCutEffErr"],
          Systematic::deltaMisIdCutEffs, Sign::same));
  deltaCutEffMisId_Bu2D0h_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_Bu2D0h", uniqueId_, Neutral::gamma,
          mapMisId_Bu2D0h["deltaCutEff"], mapMisId_Bu2D0h["deltaCutEffErr"],
          Systematic::NA, Sign::same));
  deltaCutEffMisId_MisRec_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_MisRec", uniqueId_, Neutral::gamma,
          mapMisId_MisRec["deltaCutEff"], mapMisId_MisRec["deltaCutEffErr"],
          Systematic::deltaMisIdCutEffs, Sign::same));
  deltaCutEffMisId_PartRec_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_PartRec", uniqueId_, Neutral::gamma,
          mapMisId_PartRec["deltaCutEff"], mapMisId_PartRec["deltaCutEffErr"],
          Systematic::deltaMisIdCutEffs, Sign::same));
  deltaCutEffBs2Dst0Kpi_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffBs2Dst0Kpi", uniqueId_, Neutral::gamma, Bachelor::k,
          mapBs2Dst0Kpi["deltaCutEff"], mapBs2Dst0Kpi["deltaCutEffErr"],
          Systematic::deltaCutEffs, Sign::same));
  deltaCutEffBs2D0Kpi_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "deltaCutEffBs2D0Kpi", uniqueId_, Neutral::gamma, Bachelor::k,
      mapBs2D0Kpi["deltaCutEff"], mapBs2D0Kpi["deltaCutEffErr"],
      Systematic::deltaCutEffs, Sign::same));

  if (Configuration::Get().fitBuPartial() == true) {
    deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffMisId_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma,
            mapMisId_Bu2Dst0h_D0pi0["deltaPartialCutEff"],
            mapMisId_Bu2Dst0h_D0pi0["deltaPartialCutEffErr"],
            Systematic::deltaPartialMisIdCutEffs, Sign::same));
    deltaPartialCutEffMisId_Bu2D0h_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffMisId_Bu2D0h", uniqueId_, Neutral::gamma,
            mapMisId_Bu2D0h["deltaPartialCutEff"],
            mapMisId_Bu2D0h["deltaPartialCutEffErr"], Systematic::NA,
            Sign::same));
    deltaPartialCutEffMisId_MisRec_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffMisId_MisRec", uniqueId_, Neutral::gamma,
            mapMisId_MisRec["deltaPartialCutEff"],
            mapMisId_MisRec["deltaPartialCutEffErr"],
            Systematic::deltaPartialMisIdCutEffs, Sign::same));
    deltaPartialCutEffMisId_PartRec_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffMisId_PartRec", uniqueId_, Neutral::gamma,
            mapMisId_PartRec["deltaPartialCutEff"],
            mapMisId_PartRec["deltaPartialCutEffErr"],
            Systematic::deltaPartialMisIdCutEffs, Sign::same));
    deltaPartialCutEffBs2Dst0Kpi_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffBs2Dst0Kpi", uniqueId_, Neutral::gamma,
            Bachelor::k, mapBs2Dst0Kpi["deltaPartialCutEff"],
            mapBs2Dst0Kpi["deltaPartialCutEffErr"],
            Systematic::deltaPartialCutEffs, Sign::same));
    deltaPartialCutEffBs2D0Kpi_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffBs2D0Kpi", uniqueId_, Neutral::gamma,
            Bachelor::k, mapBs2D0Kpi["deltaPartialCutEff"],
            mapBs2D0Kpi["deltaPartialCutEffErr"],
            Systematic::deltaPartialCutEffs, Sign::same));
  }
}
