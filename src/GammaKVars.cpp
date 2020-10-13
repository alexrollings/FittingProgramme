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
      Bu2Dst0h_D0gamma_sigmaDelta_(new RooFormulaVar(
          ("Bu2Dst0h_D0gamma_sigmaDelta_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0h_D0gamma_sigmaDelta(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0h_D0gamma_KpiSigmaDelta()))),
      pdf1Delta_Bu2Dst0h_D0gamma_(
          ("pdf1Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_meanDelta(),
          *Bu2Dst0h_D0gamma_sigmaDelta_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_a1Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_n1Delta()),
      pdf2Delta_Bu2Dst0h_D0gamma_(
          ("pdf2Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_meanDelta(),
          *Bu2Dst0h_D0gamma_sigmaDelta_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_a2Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_n2Delta()),
      pdfDelta_Bu2Dst0h_D0gamma_(
          ("pdfDelta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0gamma_, pdf2Delta_Bu2Dst0h_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_fracPdf1Delta()),
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
      Bu2Dst0h_D0pi0_sigmaDelta_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_sigmaDelta_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_sigmaDelta(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_KpiSigmaDelta()))),
      pdf1Delta_Bu2Dst0h_D0pi0_(
          ("pdf1Delta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_meanDelta(),
          *Bu2Dst0h_D0pi0_sigmaDelta_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_a1Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_n1Delta()),
      pdf2Delta_Bu2Dst0h_D0pi0_(
          ("pdf2Delta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_meanDelta(),
          *Bu2Dst0h_D0pi0_sigmaDelta_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_a2Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_n2Delta()),
      pdfDelta_Bu2Dst0h_D0pi0_(
          ("pdfDelta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_fracPdf1Delta()),
      Bu2Dst0h_D0pi0_sigma1Bu_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_sigma1Bu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_sigma1Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_KpiSigmaBu()))),
      Bu2Dst0h_D0pi0_sigma2Bu_(
          ("Bu2Dst0h_D0pi0_sigma2Bu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_sigma2Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_KpiSigmaBu())),
      pdf1Bu_Bu2Dst0h_D0pi0_(
          ("pdf1Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_mean1Bu(),
          *Bu2Dst0h_D0pi0_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0pi0_(
          ("pdf2Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_mean2Bu(),
          Bu2Dst0h_D0pi0_sigma2Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_n2Bu()),
      pdfBu_Bu2Dst0h_D0pi0_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0h_D0pi0_, pdf2Bu_Bu2Dst0h_D0pi0_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_fracPdf1Bu())),
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
      misId_Bu2Dst0h_D0pi0_mean2BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_mean2BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBuPartial,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_sigma1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBuPartial,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_sigma2BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma2BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBuPartial,
          Sign::same)),
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
          *misId_Bu2Dst0h_D0pi0_mean2BuPartial_,
          *misId_Bu2Dst0h_D0pi0_sigma2BuPartial_,
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
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_WN_thresholdDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_thresholdDelta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::misIdGammaWNKPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_aDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_aDelta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::misIdGammaWNKPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_bDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_bDelta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::misIdGammaWNKPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_cDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_cDelta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::misIdGammaWNKPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_meanDelta_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_sigmaDelta_(nullptr),
      pdfDelta_misId_Bu2Dst0h_D0gamma_WN_(
          new RooDstD0BG(("pdfDelta_misId_Bu2Dst0h_D0gamma_WN_" +
                          ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", Configuration::Get().deltaMass(),
                         *misId_Bu2Dst0h_D0gamma_WN_thresholdDelta_,
                         *misId_Bu2Dst0h_D0gamma_WN_cDelta_,
                         *misId_Bu2Dst0h_D0gamma_WN_aDelta_,
                         *misId_Bu2Dst0h_D0gamma_WN_bDelta_)),
      misId_Bu2Dst0h_D0gamma_WN_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_meanBu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::misIdGammaWNKPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_sigmaBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_sigmaBu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::misIdGammaWNKPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_a1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::misIdGammaWNKPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_n1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::misIdGammaWNKPdfBu, Sign::same)),
      pdfBu_misId_Bu2Dst0h_D0gamma_WN_(new RooCBShape(
          ("pdfBu_misId_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0gamma_WN_meanBu_,
          *misId_Bu2Dst0h_D0gamma_WN_sigmaBu_, *misId_Bu2Dst0h_D0gamma_WN_a1Bu_,
          *misId_Bu2Dst0h_D0gamma_WN_n1Bu_)),
      misId_Bu2Dst0h_D0gamma_WN_meanBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_meanBu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::misIdGammaWNKPdfBuPartial, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_sigmaBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_sigmaBu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::misIdGammaWNKPdfBuPartial, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_a1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_a1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::misIdGammaWNKPdfBuPartial, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_n1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_n1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::misIdGammaWNKPdfBuPartial, Sign::same)),
      pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN_(
          new RooCBShape(("pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN_" +
                          ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", Configuration::Get().buDeltaMass(),
                         *misId_Bu2Dst0h_D0gamma_WN_meanBuPartial_,
                         *misId_Bu2Dst0h_D0gamma_WN_sigmaBuPartial_,
                         *misId_Bu2Dst0h_D0gamma_WN_a1BuPartial_,
                         *misId_Bu2Dst0h_D0gamma_WN_n1BuPartial_)),
      // -------------------- Bu2Dst0h_D0pi0_WN -------------------- //
      Bu2Dst0h_D0pi0_WN_aDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_aDelta", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2Dst0K_D0pi0_WN, Systematic::pi0WNDeltaPdf, Sign::none)),
      Bu2Dst0h_D0pi0_WN_bDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_bDelta", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2Dst0K_D0pi0_WN, Systematic::pi0WNDeltaPdf, Sign::none)),
      pdfDelta_Bu2Dst0h_D0pi0_WN_(
          ("pdfDelta_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_thresholdDelta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_cDelta(),
          *Bu2Dst0h_D0pi0_WN_aDelta_, *Bu2Dst0h_D0pi0_WN_bDelta_),
      Bu2Dst0h_D0pi0_WN_sigma1Bu_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_WN_sigma1Bu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_WN_sigma1Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_WN_KpiSigmaBu()))),
      Bu2Dst0h_D0pi0_WN_sigma2Bu_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_WN_sigma2Bu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0h_D0pi0_WN_sigma1Bu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0pi0_WN_sigmaRatio21Bu()))),
      pdf1Bu_Bu2Dst0h_D0pi0_WN_(
          ("pdf1Bu_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_mean1Bu(),
          *Bu2Dst0h_D0pi0_WN_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0pi0_WN_(
          ("pdf2Bu_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_mean2Bu(),
          *Bu2Dst0h_D0pi0_WN_sigma2Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_n2Bu()),
      pdfBu_Bu2Dst0h_D0pi0_WN_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0h_D0pi0_WN_, pdf2Bu_Bu2Dst0h_D0pi0_WN_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_fracPdf1Bu())),
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
      misId_Bu2Dst0h_D0pi0_WN_mean1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_mean1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_mean2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_mean2Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_mean3Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_sigma1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_sigma2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_sigma2Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_sigma3Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_a1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_n1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_a2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_a2Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_n2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_n2Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu,
          Sign::same)),
      pdf1Bu_misId_Bu2Dst0h_D0pi0_WN_(
          ("pdf1Bu_misId_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_WN_mean1Bu_, *misId_Bu2Dst0h_D0pi0_WN_sigma1Bu_,
          *misId_Bu2Dst0h_D0pi0_WN_a1Bu_, *misId_Bu2Dst0h_D0pi0_WN_n1Bu_),
      pdf2Bu_misId_Bu2Dst0h_D0pi0_WN_(new RooCBShape(
          ("pdf2Bu_misId_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_WN_mean2Bu_, *misId_Bu2Dst0h_D0pi0_WN_sigma2Bu_,
          *misId_Bu2Dst0h_D0pi0_WN_a2Bu_, *misId_Bu2Dst0h_D0pi0_WN_n2Bu_)),
      pdf3Bu_misId_Bu2Dst0h_D0pi0_WN_(),
      misId_Bu2Dst0h_D0pi0_WN_fracPdf1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_fracPdf1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_fracPdf2Bu_(nullptr),
      pdfBu_misId_Bu2Dst0h_D0pi0_WN_(
          new RooAddPdf(("pdfBu_misId_Bu2Dst0h_D0pi0_WN_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "",
                        RooArgSet(pdf1Bu_misId_Bu2Dst0h_D0pi0_WN_,
                                  *pdf2Bu_misId_Bu2Dst0h_D0pi0_WN_),
                        *misId_Bu2Dst0h_D0pi0_WN_fracPdf1Bu_)),
      misId_Bu2Dst0h_D0pi0_WN_meanBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_meanBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN,
          Systematic::misIdPi0WNKPdfBuPartial, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_sigmaBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN,
          Systematic::misIdPi0WNKPdfBuPartial, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_a1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_a1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN,
          Systematic::misIdPi0WNKPdfBuPartial, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_n1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_n1BuPartial", uniqueId_, Neutral::gamma,
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
      // -------------------- Bd2Dsth -------------------- //
      Bd2Dsth_sigma1Bu_(new RooFormulaVar(
          ("Bd2Dsth_sigma1Bu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bd2Dsth_sigma1Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bd2Dsth_KpiSigmaBu()))),
      Bd2Dsth_sigma2Bu_(("Bd2Dsth_sigma2Bu_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "@0*@1",
                        RooArgSet(*Bd2Dsth_sigma1Bu_,
                                  NeutralVars<Neutral::gamma>::Get(uniqueId_)
                                      .Bd2Dsth_sigmaRatio21Bu())),
      pdf1Bu_Bd2Dsth_(
          ("pdf1Bu_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_mean1Bu(),
          *Bd2Dsth_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_n1Bu()),
      pdf2Bu_Bd2Dsth_(
          ("pdf2Bu_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_mean2Bu(),
          Bd2Dsth_sigma2Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_n2Bu()),
      pdfBu_Bd2Dsth_(new RooAddPdf(
          ("pdfBu_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bd2Dsth_, pdf2Bu_Bd2Dsth_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_fracPdf1Bu())),
      Bd2Dsth_sigma1BuPartial_(new RooFormulaVar(
          ("Bd2Dsth_sigma1BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bd2Dsth_sigma1BuPartial(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bd2Dsth_KpiSigmaBuPartial()))),
      Bd2Dsth_sigma2BuPartial_(
          ("Bd2Dsth_sigma2BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bd2Dsth_sigma1BuPartial_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bd2Dsth_sigmaRatio21BuPartial())),
      pdf1BuPartial_Bd2Dsth_(
          ("pdf1BuPartial_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_mean1BuPartial(),
          *Bd2Dsth_sigma1BuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_a1BuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_n1BuPartial()),
      pdf2BuPartial_Bd2Dsth_(
          ("pdf2BuPartial_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_mean2BuPartial(),
          Bd2Dsth_sigma2BuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_a2BuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_n2BuPartial()),
      pdfBuPartial_Bd2Dsth_(
          ("pdfBuPartial_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", RooArgSet(pdf1BuPartial_Bd2Dsth_, pdf2BuPartial_Bd2Dsth_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bd2Dsth_fracPdf1BuPartial()),
      // -------------------- Mis-ID ------------------- //
      misId_Bd2Dsth_meanBu_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_meanBu", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bd2Dstpi, Systematic::misIdBd2DsthKPdfBu, Sign::same)),
      misId_Bd2Dsth_sigmaBu_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_sigmaBu", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bd2Dstpi, Systematic::misIdBd2DsthKPdfBu, Sign::same)),
      misId_Bd2Dsth_a1Bu_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_a1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bd2Dstpi, Systematic::misIdBd2DsthKPdfBu, Sign::same)),
      misId_Bd2Dsth_n1Bu_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_n1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bd2Dstpi, Systematic::misIdBd2DsthKPdfBu, Sign::same)),
      pdfBu_misId_Bd2Dsth_(new RooCBShape(
          ("pdfBu_misId_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_Bd2Dsth_meanBu_,
          *misId_Bd2Dsth_sigmaBu_, *misId_Bd2Dsth_a1Bu_, *misId_Bd2Dsth_n1Bu_)),
      misId_Bd2Dsth_thresholdDelta_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_thresholdDelta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bd2Dstpi, Systematic::misIdBd2DsthKPdfDelta,
          Sign::same)),
      misId_Bd2Dsth_aDelta_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_aDelta", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bd2Dstpi, Systematic::misIdBd2DsthKPdfDelta, Sign::same)),
      misId_Bd2Dsth_bDelta_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_bDelta", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bd2Dstpi, Systematic::misIdBd2DsthKPdfDelta, Sign::same)),
      misId_Bd2Dsth_cDelta_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_cDelta", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bd2Dstpi, Systematic::misIdBd2DsthKPdfDelta, Sign::same)),
      pdfDelta_misId_Bd2Dsth_(
          ("pdfDelta_misId_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), *misId_Bd2Dsth_thresholdDelta_,
          *misId_Bd2Dsth_cDelta_, *misId_Bd2Dsth_aDelta_,
          *misId_Bd2Dsth_bDelta_),
      misId_Bd2Dsth_meanBuPartial_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_meanBuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bd2Dstpi, Systematic::misIdBd2DsthKPdfBuPartial, Sign::same)),
      misId_Bd2Dsth_sigmaBuPartial_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bd2Dstpi, Systematic::misIdBd2DsthKPdfBuPartial,
          Sign::same)),
      misId_Bd2Dsth_a1BuPartial_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_a1BuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bd2Dstpi, Systematic::misIdBd2DsthKPdfBuPartial, Sign::same)),
      misId_Bd2Dsth_n1BuPartial_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_n1BuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bd2Dstpi, Systematic::misIdBd2DsthKPdfBuPartial, Sign::same)),
      pdfBuPartial_misId_Bd2Dsth_(
          ("pdfBuPartial_misId_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_Bd2Dsth_meanBuPartial_,
          *misId_Bd2Dsth_sigmaBuPartial_, *misId_Bd2Dsth_a1BuPartial_,
          *misId_Bd2Dsth_n1BuPartial_),
      // -------------------- Bu2D0hst -------------------- //
      Bu2D0hst_sigma1Bu_(new RooFormulaVar(
          ("Bu2D0hst_sigma1Bu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2D0hst_sigma1Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2D0hst_KpiSigmaBu()))),
      Bu2D0hst_sigma2Bu_(("Bu2D0hst_sigma2Bu_" +
                          ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "@0*@1",
                         RooArgSet(*Bu2D0hst_sigma1Bu_,
                                   NeutralVars<Neutral::gamma>::Get(uniqueId_)
                                       .Bu2D0hst_sigmaRatio21Bu())),
      pdf1Bu_Bu2D0hst_(
          ("pdf1Bu_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0hst_mean1Bu(),
          *Bu2D0hst_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0hst_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0hst_n1Bu()),
      pdf2Bu_Bu2D0hst_(
          ("pdf2Bu_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0hst_mean2Bu(),
          Bu2D0hst_sigma2Bu_),
      pdfBu_Bu2D0hst_(new RooAddPdf(
          ("pdfBu_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2D0hst_, pdf2Bu_Bu2D0hst_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0hst_fracPdf1Bu())),
      Bu2D0hst_sigmaBuPartial_(new RooFormulaVar(
          ("Bu2D0hst_sigmaBuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2D0hst_sigmaBuPartial(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2D0hst_KpiSigmaBuPartial()))),
      pdfBuPartial_Bu2D0hst_(
          ("pdfBuPartial_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0hst_meanBuPartial(),
          *Bu2D0hst_sigmaBuPartial_),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2D0hst_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_meanBu", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2D0rho, Systematic::misIdBu2D0hstKPdfBu, Sign::same)),
      misId_Bu2D0hst_sigmaBu_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_sigmaBu", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2D0rho, Systematic::misIdBu2D0hstKPdfBu, Sign::same)),
      misId_Bu2D0hst_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_a1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2D0rho, Systematic::misIdBu2D0hstKPdfBu, Sign::same)),
      misId_Bu2D0hst_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_n1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2D0rho, Systematic::misIdBu2D0hstKPdfBu, Sign::same)),
      pdfBu_misId_Bu2D0hst_(
          new RooCBShape(("pdfBu_misId_Bu2D0hst_" +
                          ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", Configuration::Get().buDeltaMass(),
                         *misId_Bu2D0hst_meanBu_, *misId_Bu2D0hst_sigmaBu_,
                         *misId_Bu2D0hst_a1Bu_, *misId_Bu2D0hst_n1Bu_)),
      misId_Bu2D0hst_thresholdDelta_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_thresholdDelta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2D0rho, Systematic::misIdBu2D0hstKPdfDelta,
          Sign::same)),
      misId_Bu2D0hst_aDelta_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_aDelta", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2D0rho, Systematic::misIdBu2D0hstKPdfDelta, Sign::same)),
      misId_Bu2D0hst_bDelta_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_bDelta", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2D0rho, Systematic::misIdBu2D0hstKPdfDelta, Sign::same)),
      misId_Bu2D0hst_cDelta_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_cDelta", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2D0rho, Systematic::misIdBu2D0hstKPdfDelta, Sign::same)),
      pdfDelta_misId_Bu2D0hst_(
          ("pdfDelta_misId_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), *misId_Bu2D0hst_thresholdDelta_,
          *misId_Bu2D0hst_cDelta_, *misId_Bu2D0hst_aDelta_,
          *misId_Bu2D0hst_bDelta_),
      misId_Bu2D0hst_meanBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_meanBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2D0rho, Systematic::misIdBu2D0hstKPdfBuPartial,
          Sign::same)),
      misId_Bu2D0hst_sigmaBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2D0rho, Systematic::misIdBu2D0hstKPdfBuPartial,
          Sign::same)),
      misId_Bu2D0hst_a1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_a1BuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2D0rho, Systematic::misIdBu2D0hstKPdfBuPartial, Sign::same)),
      misId_Bu2D0hst_n1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_n1BuPartial", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2D0rho, Systematic::misIdBu2D0hstKPdfBuPartial, Sign::same)),
      pdfBuPartial_misId_Bu2D0hst_(
          ("pdfBuPartial_misId_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2D0hst_meanBuPartial_, *misId_Bu2D0hst_sigmaBuPartial_,
          *misId_Bu2D0hst_a1BuPartial_, *misId_Bu2D0hst_n1BuPartial_),
      // -------------------- Bu2Dst0hst_D0gamma -------------------- //
      Bu2Dst0hst_D0gamma_sigma1Bu_(new RooFormulaVar(
          ("Bu2Dst0hst_D0gamma_sigma1Bu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0hst_D0gamma_sigma1Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0hst_D0gamma_KpiSigmaBu()))),
      Bu2Dst0hst_D0gamma_sigma2Bu_(
          ("Bu2Dst0hst_D0gamma_sigma2Bu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0hst_D0gamma_sigma1Bu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0hst_D0gamma_sigmaRatio21Bu())),
      pdf1Bu_Bu2Dst0hst_D0gamma_(
          ("pdf1Bu_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0hst_D0gamma_mean1Bu(),
          *Bu2Dst0hst_D0gamma_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0hst_D0gamma_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0hst_D0gamma_n1Bu()),
      pdf2Bu_Bu2Dst0hst_D0gamma_(
          ("pdf2Bu_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0hst_D0gamma_mean2Bu(),
          Bu2Dst0hst_D0gamma_sigma2Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0hst_D0gamma_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0hst_D0gamma_n2Bu()),
      pdfBu_Bu2Dst0hst_D0gamma_(new RooAddPdf(
          ("pdfBu_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0hst_D0gamma_, pdf2Bu_Bu2Dst0hst_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0hst_D0gamma_fracPdf1Bu())),
      Bu2Dst0hst_D0gamma_sigmaBuPartial_(new RooFormulaVar(
          ("Bu2Dst0hst_D0gamma_sigmaBuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0hst_D0gamma_sigmaBuPartial(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0hst_D0gamma_KpiSigmaBuPartial()))),
      pdfBuPartial_Bu2Dst0hst_D0gamma_(
          ("pdfBuPartial_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0hst_D0gamma_meanBuPartial(),
          *Bu2Dst0hst_D0gamma_sigmaBuPartial_),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0hst_D0gamma_mean1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0gamma_mean1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0gamma,
          Systematic::misIdBu2Dst0hst_D0gammaKPdfBu, Sign::same)),
      misId_Bu2Dst0hst_D0gamma_meanOffset21Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0gamma_meanOffset21Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0gamma,
          Systematic::misIdBu2Dst0hst_D0gammaKPdfBu, Sign::same)),
      misId_Bu2Dst0hst_D0gamma_mean2Bu_(
          ("misId_Bu2Dst0hst_D0gamma_mean2Bu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0+@1",
          RooArgSet(*misId_Bu2Dst0hst_D0gamma_mean1Bu_,
                    *misId_Bu2Dst0hst_D0gamma_meanOffset21Bu_)),
      misId_Bu2Dst0hst_D0gamma_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0gamma_sigma1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0gamma,
          Systematic::misIdBu2Dst0hst_D0gammaKPdfBu, Sign::same)),
      misId_Bu2Dst0hst_D0gamma_sigmaRatio21Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0gamma_sigmaRatio21Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0gamma,
          Systematic::misIdBu2Dst0hst_D0gammaKPdfBu, Sign::same)),
      misId_Bu2Dst0hst_D0gamma_sigma2Bu_(
          ("misId_Bu2Dst0hst_D0gamma_sigma2Bu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgSet(*misId_Bu2Dst0hst_D0gamma_sigma1Bu_,
                    *misId_Bu2Dst0hst_D0gamma_sigmaRatio21Bu_)),
      misId_Bu2Dst0hst_D0gamma_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0gamma_a1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0gamma,
          Systematic::misIdBu2Dst0hst_D0gammaKPdfBu, Sign::same)),
      misId_Bu2Dst0hst_D0gamma_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0gamma_n1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0gamma,
          Systematic::misIdBu2Dst0hst_D0gammaKPdfBu, Sign::same)),
      pdf1Bu_misId_Bu2Dst0hst_D0gamma_(
          ("pdf1Bu_misId_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0hst_D0gamma_mean1Bu_,
          *misId_Bu2Dst0hst_D0gamma_sigma1Bu_, *misId_Bu2Dst0hst_D0gamma_a1Bu_,
          *misId_Bu2Dst0hst_D0gamma_n1Bu_),
      pdf2Bu_misId_Bu2Dst0hst_D0gamma_(
          ("pdf2Bu_misId_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          misId_Bu2Dst0hst_D0gamma_mean2Bu_,
          misId_Bu2Dst0hst_D0gamma_sigma2Bu_),
      misId_Bu2Dst0hst_D0gamma_fracPdf1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0gamma_fracPdf1Bu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0gamma,
          Systematic::misIdBu2Dst0hst_D0gammaKPdfBu, Sign::same)),
      pdfBu_misId_Bu2Dst0hst_D0gamma_(
          new RooAddPdf(("pdfBu_misId_Bu2Dst0hst_D0gamma_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "",
                        RooArgSet(pdf1Bu_misId_Bu2Dst0hst_D0gamma_,
                                  pdf2Bu_misId_Bu2Dst0hst_D0gamma_),
                        *misId_Bu2Dst0hst_D0gamma_fracPdf1Bu_)),
      // For peaking delta PDF, fix all params except mean and sigma from mis ID
      // signal shape
      misId_Bu2Dst0hst_D0gamma_meanDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0gamma_meanDelta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0gamma,
          Systematic::misIdBu2Dst0hst_D0gammaKPdfDelta, Sign::same)),
      misId_Bu2Dst0hst_D0gamma_sigmaDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0gamma_sigmaDelta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0gamma,
          Systematic::misIdBu2Dst0hst_D0gammaKPdfDelta, Sign::same)),
      pdf1Delta_misId_Bu2Dst0hst_D0gamma_(
          ("pdf1Delta_misId_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0hst_D0gamma_meanDelta_,
          *misId_Bu2Dst0hst_D0gamma_sigmaDelta_,
          *misId_Bu2Dst0h_D0gamma_a1Delta_, *misId_Bu2Dst0h_D0gamma_n1Delta_),
      pdf2Delta_misId_Bu2Dst0hst_D0gamma_(
          ("pdf2Delta_misId_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0hst_D0gamma_meanDelta_,
          *misId_Bu2Dst0hst_D0gamma_sigmaDelta_,
          *misId_Bu2Dst0h_D0gamma_a2Delta_, *misId_Bu2Dst0h_D0gamma_n2Delta_),
      pdfPeakDelta_misId_Bu2Dst0hst_D0gamma_(
          ("pdfPeakDelta_misId_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgSet(pdf1Delta_misId_Bu2Dst0hst_D0gamma_,
                    pdf2Delta_misId_Bu2Dst0hst_D0gamma_),
          *misId_Bu2Dst0h_D0gamma_fracPdf1Delta_),
      // Share DstD0BG with D0gamma WN misID shape
      pdfFlatDelta_misId_Bu2Dst0hst_D0gamma_(
          ("pdfFlatDelta_misId_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0gamma_WN_thresholdDelta_,
          *misId_Bu2Dst0h_D0gamma_WN_cDelta_,
          *misId_Bu2Dst0h_D0gamma_WN_aDelta_,
          *misId_Bu2Dst0h_D0gamma_WN_bDelta_),
      misId_Bu2Dst0hst_D0gamma_fracPdfPeakDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0gamma_fracPdfPeakDelta", uniqueId_,
          Neutral::gamma, Bachelor::k, Mode::Bu2Dst0rho_D0gamma,
          Systematic::misIdBu2Dst0hst_D0gammaKPdfDelta, Sign::same)),
      pdfDelta_misId_Bu2Dst0hst_D0gamma_(
          new RooAddPdf(("pdfDelta_misId_Bu2Dst0hst_D0gamma_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "",
                        RooArgSet(pdfPeakDelta_misId_Bu2Dst0hst_D0gamma_,
                                  pdfFlatDelta_misId_Bu2Dst0hst_D0gamma_),
                        *misId_Bu2Dst0hst_D0gamma_fracPdfPeakDelta_)),
      misId_Bu2Dst0hst_D0gamma_meanBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0gamma_meanBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0gamma,
          Systematic::misIdBu2Dst0hst_D0gammaKPdfBuPartial, Sign::same)),
      misId_Bu2Dst0hst_D0gamma_sigmaBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0gamma_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0gamma,
          Systematic::misIdBu2Dst0hst_D0gammaKPdfBuPartial, Sign::same)),
      pdfBuPartial_misId_Bu2Dst0hst_D0gamma_(
          ("pdfBuPartial_misId_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0hst_D0gamma_meanBuPartial_,
          *misId_Bu2Dst0hst_D0gamma_sigmaBuPartial_),
      // -------------------- Bu2Dst0hst_D0pi0 -------------------- //
      Bu2Dst0hst_D0pi0_sigmaBu_(new RooFormulaVar(
          ("Bu2Dst0hst_D0pi0_sigmaBu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0hst_D0pi0_sigmaBu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0hst_D0pi0_KpiSigmaBu()))),
      pdfBu_Bu2Dst0hst_D0pi0_(
          ("pdfBu_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0hst_D0pi0_meanBu(),
          *Bu2Dst0hst_D0pi0_sigmaBu_),
      Bu2Dst0hst_D0pi0_sigmaBuPartial_(new RooFormulaVar(
          ("Bu2Dst0hst_D0pi0_sigmaBuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0hst_D0pi0_sigmaBuPartial(),
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0hst_D0pi0_KpiSigmaBuPartial()))),
      pdfBuPartial_Bu2Dst0hst_D0pi0_(
          ("pdfBuPartial_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0hst_D0pi0_meanBuPartial(),
          *Bu2Dst0hst_D0pi0_sigmaBuPartial_),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0hst_D0pi0_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_meanBu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfBu, Sign::same)),
      misId_Bu2Dst0hst_D0pi0_sigmaBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_sigmaBu", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfBu, Sign::same)),
      misId_Bu2Dst0hst_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_a1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2Dst0rho_D0pi0, Systematic::misIdBu2Dst0hst_D0pi0KPdfBu,
          Sign::same)),
      misId_Bu2Dst0hst_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_n1Bu", uniqueId_, Neutral::gamma, Bachelor::k,
          Mode::Bu2Dst0rho_D0pi0, Systematic::misIdBu2Dst0hst_D0pi0KPdfBu,
          Sign::same)),
      pdfBu_misId_Bu2Dst0hst_D0pi0_(
          ("pdfBu_misId_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0hst_D0pi0_meanBu_, *misId_Bu2Dst0hst_D0pi0_sigmaBu_,
          *misId_Bu2Dst0hst_D0pi0_a1Bu_, *misId_Bu2Dst0hst_D0pi0_n1Bu_),
      // For peaking delta PDF, fix all params except mean and sigma from mis ID
      // signal shape
      misId_Bu2Dst0hst_D0pi0_mean1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_mean1Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfDelta, Sign::same)),
      misId_Bu2Dst0hst_D0pi0_mean2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_mean2Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfDelta, Sign::same)),
      misId_Bu2Dst0hst_D0pi0_sigma1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_sigma1Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfDelta, Sign::same)),
      misId_Bu2Dst0hst_D0pi0_sigma2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_sigma2Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfDelta, Sign::same)),
      misId_Bu2Dst0hst_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_a1Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfDelta, Sign::same)),
      misId_Bu2Dst0hst_D0pi0_n1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_n1Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfDelta, Sign::same)),
      misId_Bu2Dst0hst_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_a2Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfDelta, Sign::same)),
      misId_Bu2Dst0hst_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_n2Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfDelta, Sign::same)),
      pdf1Delta_misId_Bu2Dst0hst_D0pi0_(
          ("pdf1Delta_misId_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0hst_D0pi0_mean1Delta_,
          *misId_Bu2Dst0hst_D0pi0_sigma1Delta_, *misId_Bu2Dst0h_D0pi0_a1Delta_,
          *misId_Bu2Dst0h_D0pi0_n1Delta_),
      pdf2Delta_misId_Bu2Dst0hst_D0pi0_(
          ("pdf2Delta_misId_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0hst_D0pi0_mean2Delta_,
          *misId_Bu2Dst0hst_D0pi0_sigma2Delta_, *misId_Bu2Dst0h_D0pi0_a2Delta_,
          *misId_Bu2Dst0h_D0pi0_n2Delta_),
      misId_Bu2Dst0hst_D0pi0_fracPdf1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_fracPdf1Delta", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfDelta, Sign::same)),
      pdfDelta_misId_Bu2Dst0hst_D0pi0_(
          ("pdfDelta_misId_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgSet(pdf1Delta_misId_Bu2Dst0hst_D0pi0_,
                    pdf2Delta_misId_Bu2Dst0hst_D0pi0_),
          *misId_Bu2Dst0hst_D0pi0_fracPdf1Delta_),
      misId_Bu2Dst0hst_D0pi0_mean1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_mean1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfBuPartial, Sign::same)),
      misId_Bu2Dst0hst_D0pi0_meanOffset21BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_meanOffset21BuPartial", uniqueId_,
          Neutral::gamma, Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfBuPartial, Sign::same)),
      misId_Bu2Dst0hst_D0pi0_mean2BuPartial_(
          ("misId_Bu2Dst0hst_D0pi0_mean2BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0+@1",
          RooArgSet(*misId_Bu2Dst0hst_D0pi0_mean1BuPartial_,
                    *misId_Bu2Dst0hst_D0pi0_meanOffset21BuPartial_)),
      misId_Bu2Dst0hst_D0pi0_sigma1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_sigma1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfBuPartial, Sign::same)),
      misId_Bu2Dst0hst_D0pi0_sigmaRatio21BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_sigmaRatio21BuPartial", uniqueId_,
          Neutral::gamma, Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfBuPartial, Sign::same)),
      misId_Bu2Dst0hst_D0pi0_sigma2BuPartial_(
          ("misId_Bu2Dst0hst_D0pi0_sigma2BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgSet(*misId_Bu2Dst0hst_D0pi0_sigma1BuPartial_,
                    *misId_Bu2Dst0hst_D0pi0_sigmaRatio21BuPartial_)),
      misId_Bu2Dst0hst_D0pi0_a1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_a1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfBuPartial, Sign::same)),
      misId_Bu2Dst0hst_D0pi0_n1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_n1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfBuPartial, Sign::same)),
      pdf1BuPartial_misId_Bu2Dst0hst_D0pi0_(
          ("pdf1BuPartial_misId_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0hst_D0pi0_mean1BuPartial_,
          *misId_Bu2Dst0hst_D0pi0_sigma1BuPartial_,
          *misId_Bu2Dst0hst_D0pi0_a1BuPartial_,
          *misId_Bu2Dst0hst_D0pi0_n1BuPartial_),
      pdf2BuPartial_misId_Bu2Dst0hst_D0pi0_(
          ("pdf2BuPartial_misId_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          misId_Bu2Dst0hst_D0pi0_mean2BuPartial_,
          misId_Bu2Dst0hst_D0pi0_sigma2BuPartial_),
      misId_Bu2Dst0hst_D0pi0_fracPdf1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0hst_D0pi0_fracPdf1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::k, Mode::Bu2Dst0rho_D0pi0,
          Systematic::misIdBu2Dst0hst_D0pi0KPdfBuPartial, Sign::same)),
      pdfBuPartial_misId_Bu2Dst0hst_D0pi0_(
          ("pdfBuPartial_misId_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgSet(pdf1BuPartial_misId_Bu2Dst0hst_D0pi0_,
                    pdf2BuPartial_misId_Bu2Dst0hst_D0pi0_),
          *misId_Bu2Dst0hst_D0pi0_fracPdf1BuPartial_),
      // -------------------- Bs2Dst0Kpi -------------------- //
      pdfPeakGamma1Delta_Bs2Dst0Kpi_(
          ("pdfPeakGamma1Delta_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_meanDelta(),
          *Bu2Dst0h_D0gamma_sigmaDelta_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_a1Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_n1Delta()),
      pdfPeakGamma2Delta_Bs2Dst0Kpi_(
          ("pdfPeakGamma2Delta_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_meanDelta(),
          *Bu2Dst0h_D0gamma_sigmaDelta_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_a2Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_n2Delta()),
      pdfPeakGammaDelta_Bs2Dst0Kpi_(
          ("pdfPeakGammaDelta_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgList(pdfPeakGamma1Delta_Bs2Dst0Kpi_,
                     pdfPeakGamma2Delta_Bs2Dst0Kpi_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_fracPdf1Delta()),
      pdfPeakPi01Delta_Bs2Dst0Kpi_(
          ("pdfPeakPi01Delta_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_meanDelta(),
          *Bu2Dst0h_D0pi0_sigmaDelta_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_a1Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_n1Delta()),
      pdfPeakPi02Delta_Bs2Dst0Kpi_(
          ("pdfPeakPi02Delta_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_meanDelta(),
          *Bu2Dst0h_D0pi0_sigmaDelta_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_a2Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_n2Delta()),
      pdfPeakPi0Delta_Bs2Dst0Kpi_(
          ("pdfPeakPi0Delta_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgList(pdfPeakPi01Delta_Bs2Dst0Kpi_,
                     pdfPeakPi02Delta_Bs2Dst0Kpi_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_fracPdf1Delta()),
      pdfDelta_Bs2Dst0Kpi_(
          ("pdfDelta_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgList(pdfPeakGammaDelta_Bs2Dst0Kpi_, pdfPeakPi0Delta_Bs2Dst0Kpi_,
                     NeutralVars<Neutral::gamma>::Get(uniqueId_)
                         .pdfFlatDelta_Bs2Dst0Kpi()),
          RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId_)
                         .Bs2Dst0Kpi_fracPdfGammaPeakDelta(),
                     NeutralVars<Neutral::gamma>::Get(uniqueId_)
                         .Bs2Dst0Kpi_fracPdfPi0PeakDelta())),
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
      // -------------------- Correct ID BOX EFFs -------------------- //
      orEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::k, Efficiency::orEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::k,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      orEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::k, Efficiency::orEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::k, Efficiency::orEffErr,
                        false),
          Systematic::NA, Sign::same)),
      orEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::k,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::k,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      orEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::k, Efficiency::orEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::k,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      orEffBd2Dsth_(Params::Get().CreateFixed(
          "orEffBd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::k, Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::k, Efficiency::orEffErr,
                        false),
          Systematic::NA, Sign::same)),
      orEffBu2D0hst_(Params::Get().CreateFixed(
          "orEffBu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::k, Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::k, Efficiency::orEffErr,
                        false),
          Systematic::NA, Sign::same)),
      orEffBu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "orEffBu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::k,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::k,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
      orEffBu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "orEffBu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::k, Efficiency::orEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::k,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::same)),
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
      buEffBd2Dsth_(Params::Get().CreateFixed(
          "buEffBd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::k, Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::k, Efficiency::buEffErr,
                        false),
          Systematic::NA, Sign::same)),
      buEffBu2D0hst_(Params::Get().CreateFixed(
          "buEffBu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::k, Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::k, Efficiency::buEffErr,
                        false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "buEffBu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::k,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::k,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::same)),
      buEffBu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "buEffBu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::k, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::k,
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
      deltaEffBd2Dsth_(Params::Get().CreateFixed(
          "deltaEffBd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::k, Efficiency::deltaEff,
                        false),
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::k, Efficiency::deltaEffErr,
                        false),
          Systematic::NA, Sign::same)),
      deltaEffBu2D0hst_(Params::Get().CreateFixed(
          "deltaEffBu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::k, Efficiency::deltaEff,
                        false),
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::k, Efficiency::deltaEffErr,
                        false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::k,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::k,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::same)),
      deltaEffBu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::k,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::k,
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
      buPartialEffBd2Dsth_(Params::Get().CreateFixed(
          "buPartialEffBd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::k, Efficiency::buPartialEff,
                        false),
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::k, Efficiency::buPartialEffErr,
                        false),
          Systematic::NA, Sign::same)),
      buPartialEffBu2D0hst_(Params::Get().CreateFixed(
          "buPartialEffBu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::k, Efficiency::buPartialEff,
                        false),
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::k,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::same)),
      buPartialEffBu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::k,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::k,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::same)),
      buPartialEffBu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::k,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::k,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::same)),
      // -------------------- Mis-ID BoxEffs ------------------- //
      orEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::k, Efficiency::orEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::k,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::same)),
      orEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::k, Efficiency::orEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::k,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::same)),
      orEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::k,
                        Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::k,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::same)),
      orEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::k,
                        Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::k,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::same)),
      orEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "orEffMisId_Bd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::k, Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::k, Efficiency::orEffErr,
                        true),
          Systematic::NA, Sign::positive)),
      orEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "orEffMisId_Bu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::k, Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::k, Efficiency::orEffErr,
                        true),
          Systematic::NA, Sign::positive)),
      orEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::k,
                        Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::k,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::positive)),
      orEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::k, Efficiency::orEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::k,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::positive)),
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
      buEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::k,
                        Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::k,
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
      buEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "buEffMisId_Bd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::k, Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::k, Efficiency::buEffErr,
                        true),
          Systematic::NA, Sign::positive)),
      buEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "buEffMisId_Bu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::k, Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::k, Efficiency::buEffErr,
                        true),
          Systematic::NA, Sign::positive)),
      buEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::k,
                        Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::k,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::positive)),
      buEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::k, Efficiency::buEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::k,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::positive)),
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
      deltaEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::k,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::k,
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
      deltaEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "deltaEffMisId_Bd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::k, Efficiency::deltaEff,
                        true),
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::k, Efficiency::deltaEffErr,
                        true),
          Systematic::NA, Sign::positive)),
      deltaEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::k, Efficiency::deltaEff,
                        true),
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::k, Efficiency::deltaEffErr,
                        true),
          Systematic::NA, Sign::positive)),
      deltaEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::k,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::k,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::positive)),
      deltaEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::k,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::k,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::positive)),
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
      buPartialEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::k,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::k,
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
      buPartialEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::k, Efficiency::buPartialEff,
                        true),
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::k,
                        Efficiency::buPartialEffErr, true),
          Systematic::NA, Sign::positive)),
      buPartialEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::k, Efficiency::buPartialEff,
                        true),
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::k,
                        Efficiency::buPartialEffErr, true),
          Systematic::NA, Sign::positive)),
      buPartialEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::k,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::k,
                        Efficiency::buPartialEffErr, true),
          Systematic::NA, Sign::positive)),
      buPartialEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::k,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::k,
                        Efficiency::buPartialEffErr, true),
          Systematic::NA, Sign::positive)),
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
      mcEff_Bd2Dsth_(Params::Get().CreateFixed(
          "mcEff_Bd2Dsth", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnMCEffs(Mode::Bd2DstK, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bd2DstK, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_Bu2D0hst_(Params::Get().CreateFixed(
          "mcEff_Bu2D0hst", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnMCEffs(Mode::Bu2D0Kst, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2D0Kst, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0hst_D0gamma", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnMCEffs(Mode::Bu2Dst0Kst_D0gamma, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0Kst_D0gamma, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEff_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0hst_D0pi0", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnMCEffs(Mode::Bu2Dst0Kst_D0pi0, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0Kst_D0pi0, Neutral::gamma, Bachelor::k,
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
      // -------------------- MC misId Efficiencies -------------------- //
      mcEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "mcEffMisId_Bd2Dsth", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnMCEffs(Mode::Bd2Dstpi, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bd2Dstpi, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2D0hst", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnMCEffs(Mode::Bu2D0rho, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2D0rho, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0hst_D0gamma", uniqueId_, Neutral::gamma,
          Bachelor::k,
          ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0hst_D0pi0", uniqueId_, Neutral::gamma, Bachelor::k,
          ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, Neutral::gamma, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      // -------------------- Bkg Fractions -------------------- //
      // bkgFracGlobal_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFloating(
      //     "bkgFracGlobal_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::gamma,
      //     (ReturnMCEffs(Mode::Bu2Dst0K_D0pi0_WN, Neutral::gamma,
      //     Bachelor::k,
      //                   Efficiency::mcEff) /
      //      ReturnMCEffs(Mode::Bu2Dst0K_D0pi0, Neutral::gamma, Bachelor::k,
      //                   Efficiency::mcEff)),
      //     0, 5)),
      bkgFrac_Bu2Dst0h_D0pi0_WN_(new RooFormulaVar(
          ("bkgFrac_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "(@0/@1)*(@2/@3)",
          RooArgList(*orEffBu2Dst0h_D0pi0_WN_, *orEffBu2Dst0h_D0pi0_,
                     *mcEff_Bu2Dst0h_D0pi0_WN_, *mcEff_Bu2Dst0h_D0pi0_))),
      // bkgFracGlobal_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFloating(
      //     "bkgFracGlobal_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::gamma,
      //     ReturnMCEffs(Mode::Bu2Dst0K_D0gamma_WN, Neutral::gamma,
      //     Bachelor::k,
      //                  Efficiency::mcEff) /
      //         ReturnMCEffs(Mode::Bu2Dst0K_D0gamma, Neutral::gamma,
      //                      Bachelor::k, Efficiency::mcEff),
      //     0, 5)),
      bkgFrac_Bu2Dst0h_D0gamma_WN_(new RooFormulaVar(
          ("bkgFrac_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::k))
              .c_str(),
          "(@0/@1)*(@2/@3)",
          RooArgList(*orEffBu2Dst0h_D0gamma_WN_, *orEffBu2Dst0h_D0gamma_,
                     *mcEff_Bu2Dst0h_D0gamma_WN_, *mcEff_Bu2Dst0h_D0gamma_))),
      bkgFrac_Bu2Dst0h_WN_(),
      // -------------------- Bu2Dst0h_WN -------------------- //
      Bu2Dst0hst_fracD0pi0_(),
      Bu2Dst0hst_fracD0pi0_Bu_(),
      Bu2Dst0hst_fracD0pi0_Delta_(),
      pdfBu_Bu2Dst0hst_(),
      pdfDelta_Bu2Dst0hst_(),
      orEffBu2Dst0hst_(),
      buEffBu2Dst0hst_(),
      deltaEffBu2Dst0hst_(),
      mcEff_Bu2Dst0hst_(),
      Bu2Dst0hst_misId_fracD0pi0_(),
      Bu2Dst0hst_misId_fracD0pi0_Bu_(),
      Bu2Dst0hst_misId_fracD0pi0_Delta_(),
      pdfBu_misId_Bu2Dst0hst_(),
      pdfDelta_misId_Bu2Dst0hst_(),
      orEffMisId_Bu2Dst0hst_(),
      buEffMisId_Bu2Dst0hst_(),
      deltaEffMisId_Bu2Dst0hst_(),
      mcEffMisId_Bu2Dst0hst_() {}
