#include "NeutralBachelorVars.h"
#include "Params.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- PDF SHAPES -------------------- //
    // -------------------- Bu2Dst0h_D0gamma -------------------- //
    : uniqueId_(uniqueId),
      Bu2Dst0h_D0gamma_sigmaDelta_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0gamma_sigmaDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0pi_D0gamma, 2, 15)),
      pdf1Delta_Bu2Dst0h_D0gamma_(
          ("pdf1Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
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
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
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
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0gamma_, pdf2Delta_Bu2Dst0h_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_fracPdf1Delta()),
      Bu2Dst0h_D0gamma_sigmaBu_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0gamma_sigmaBu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2Dst0pi_D0gamma, 15, 25)),
      pdf1Bu_Bu2Dst0h_D0gamma_(
          ("pdf1Bu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0gamma_meanBu(),
          *Bu2Dst0h_D0gamma_sigmaBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0gamma_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0gamma_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0gamma_(
          ("pdf2Bu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0gamma_meanBu(),
          *Bu2Dst0h_D0gamma_sigmaBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0gamma_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0gamma_n2Bu()),
      pdfBu_Bu2Dst0h_D0gamma_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0h_D0gamma_, pdf2Bu_Bu2Dst0h_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_fracPdf1Bu())),
      pdfBuPartial_Bu2Dst0h_D0gamma_(
          ("pdfBuPartial_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_meanBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_sigmaBuPartial()),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_meanDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_meanDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0gamma_sigmaDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_sigmaDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0gamma_a1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a1Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0gamma_n1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n1Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0gamma_a2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a2Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0gamma_n2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n2Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs, Sign::same)),
      pdf1Delta_misId_Bu2Dst0h_D0gamma_(
          ("pdf1Delta_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0gamma_meanDelta_,
          *misId_Bu2Dst0h_D0gamma_sigmaDelta_, *misId_Bu2Dst0h_D0gamma_a1Delta_,
          *misId_Bu2Dst0h_D0gamma_n1Delta_),
      pdf2Delta_misId_Bu2Dst0h_D0gamma_(
          ("pdf2Delta_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0gamma_meanDelta_,
          *misId_Bu2Dst0h_D0gamma_sigmaDelta_, *misId_Bu2Dst0h_D0gamma_a2Delta_,
          *misId_Bu2Dst0h_D0gamma_n2Delta_),
      misId_Bu2Dst0h_D0gamma_fracPdf1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_fracPdf1Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs, Sign::same)),
      pdfDelta_misId_Bu2Dst0h_D0gamma_(
          new RooAddPdf(("pdfDelta_misId_Bu2Dst0h_D0gamma_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                            .c_str(),
                        "",
                        RooArgSet(pdf1Delta_misId_Bu2Dst0h_D0gamma_,
                                  pdf2Delta_misId_Bu2Dst0h_D0gamma_),
                        *misId_Bu2Dst0h_D0gamma_fracPdf1Delta_)),
      misId_Bu2Dst0h_D0gamma_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_meanBu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0gamma_sigmaBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_sigmaBu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0gamma_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0gamma_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0gamma_a2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a2Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0gamma_n2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n2Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs, Sign::same)),
      pdf1Bu_misId_Bu2Dst0h_D0gamma_(
          ("pdf1Bu_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0gamma_meanBu_, *misId_Bu2Dst0h_D0gamma_sigmaBu_,
          *misId_Bu2Dst0h_D0gamma_a1Bu_, *misId_Bu2Dst0h_D0gamma_n1Bu_),
      pdf2Bu_misId_Bu2Dst0h_D0gamma_(
          ("pdf2Bu_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0gamma_meanBu_, *misId_Bu2Dst0h_D0gamma_sigmaBu_,
          *misId_Bu2Dst0h_D0gamma_a2Bu_, *misId_Bu2Dst0h_D0gamma_n2Bu_),
      misId_Bu2Dst0h_D0gamma_fracPdf1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_fracPdf1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs, Sign::same)),
      pdfBu_misId_Bu2Dst0h_D0gamma_(
          new RooAddPdf(("pdfBu_misId_Bu2Dst0h_D0gamma_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                            .c_str(),
                        "",
                        RooArgSet(pdf1Bu_misId_Bu2Dst0h_D0gamma_,
                                  pdf2Bu_misId_Bu2Dst0h_D0gamma_),
                        *misId_Bu2Dst0h_D0gamma_fracPdf1Bu_)),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      Bu2Dst0h_D0pi0_sigmaDelta_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_sigmaDelta", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2Dst0pi_D0pi0, 5, 15)),
      pdf1Delta_Bu2Dst0h_D0pi0_(
          ("pdf1Delta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_meanDelta(),
          *Bu2Dst0h_D0pi0_sigmaDelta_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_a1Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_n1Delta()),
      pdf2Delta_Bu2Dst0h_D0pi0_(
          ("pdf2Delta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_meanDelta(),
          *Bu2Dst0h_D0pi0_sigmaDelta_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_a2Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_n2Delta()),
      pdfDelta_Bu2Dst0h_D0pi0_(
          ("pdfDelta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_fracPdf1Delta()),
      Bu2Dst0h_D0pi0_sigma1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_sigma1Bu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2Dst0pi_D0pi0, Systematic::Bu2Dst0h_D0pi0_PdfBu, Sign::same)),
      Bu2Dst0h_D0pi0_sigma2Bu_(
          ("Bu2Dst0h_D0pi0_sigma2Bu" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1",
          RooArgList(*Bu2Dst0h_D0pi0_sigma1Bu_,
                     NeutralVars<Neutral::gamma>::Get(uniqueId_)
                         .Bu2Dst0h_D0pi0_sigmaRatio21Bu())),
      pdf1Bu_Bu2Dst0h_D0pi0_(
          ("pdf1Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_mean1Bu(),
          *Bu2Dst0h_D0pi0_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0pi0_(
          ("pdf2Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_mean2Bu(),
          Bu2Dst0h_D0pi0_sigma2Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_n2Bu()),
      pdfBu_Bu2Dst0h_D0pi0_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0h_D0pi0_, pdf2Bu_Bu2Dst0h_D0pi0_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_fracPdf1Bu())),
      // Bu2Dst0h_D0pi0_sigma1BuPartial_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_sigma1BuPartial", uniqueId_, Neutral::gamma,
      //     Bachelor::pi, 24.5653, 0.157787,
      //     Systematic::pi0BuPartialSigma1, Sign::same)),
      Bu2Dst0h_D0pi0_sigma1BuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_sigma1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0pi_D0pi0, 20, 35)),
      Bu2Dst0h_D0pi0_sigma2BuPartial_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_sigma2BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0h_D0pi0_sigma1BuPartial_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0pi0_sigmaRatio21BuPartial()))),
      Bu2Dst0h_D0pi0_sigma3BuPartial_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_sigma3BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0h_D0pi0_sigma1BuPartial_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0pi0_sigmaRatio31BuPartial()))),
      pdf1BuPartial_Bu2Dst0h_D0pi0_(
          ("pdf1BuPartial_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
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
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
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
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_mean3BuPartial(),
          *Bu2Dst0h_D0pi0_sigma3BuPartial_),
      pdfBuPartial_Bu2Dst0h_D0pi0_(
          ("pdfBuPartial_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
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
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_sigmaDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigmaDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_n1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a2Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n2Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      pdf1Delta_misId_Bu2Dst0h_D0pi0_(
          ("pdf1Delta_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0pi0_meanDelta_, *misId_Bu2Dst0h_D0pi0_sigmaDelta_,
          *misId_Bu2Dst0h_D0pi0_a1Delta_, *misId_Bu2Dst0h_D0pi0_n1Delta_),
      pdf2Delta_misId_Bu2Dst0h_D0pi0_(
          ("pdf2Delta_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0pi0_meanDelta_, *misId_Bu2Dst0h_D0pi0_sigmaDelta_,
          *misId_Bu2Dst0h_D0pi0_a2Delta_, *misId_Bu2Dst0h_D0pi0_n2Delta_),
      misId_Bu2Dst0h_D0pi0_fracPdf1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_fracPdf1Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      pdfDelta_misId_Bu2Dst0h_D0pi0_(
          new RooAddPdf(("pdfDelta_misId_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                            .c_str(),
                        "",
                        RooArgSet(pdf1Delta_misId_Bu2Dst0h_D0pi0_,
                                  pdf2Delta_misId_Bu2Dst0h_D0pi0_),
                        *misId_Bu2Dst0h_D0pi0_fracPdf1Delta_)),
      misId_Bu2Dst0h_D0pi0_mean1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_mean1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_mean2Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_sigma2Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1Bu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2Dst0K_D0pi0, Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs,
          Sign::none)),
      misId_Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1Bu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2Dst0K_D0pi0, Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_a2Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_n2Bu_(nullptr),
      pdf1Bu_misId_Bu2Dst0h_D0pi0_(nullptr),
      pdf2Bu_misId_Bu2Dst0h_D0pi0_(),
      misId_Bu2Dst0h_D0pi0_fracPdf1Bu_(nullptr),
      pdfBu_misId_Bu2Dst0h_D0pi0_(new RooCBShape(
          ("pdfBu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_mean1Bu_, *misId_Bu2Dst0h_D0pi0_sigma1Bu_,
          *misId_Bu2Dst0h_D0pi0_a1Bu_, *misId_Bu2Dst0h_D0pi0_n1Bu_)),
      misId_Bu2Dst0h_D0pi0_mean1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_mean1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_mean2BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_mean2BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_sigma1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_sigma2BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma2BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_a1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_n1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_a2BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a2BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_n2BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n2BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      pdf1BuPartial_misId_Bu2Dst0h_D0pi0_(
          ("pdf1BuPartial_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_mean1BuPartial_,
          *misId_Bu2Dst0h_D0pi0_sigma1BuPartial_,
          *misId_Bu2Dst0h_D0pi0_a1BuPartial_,
          *misId_Bu2Dst0h_D0pi0_n1BuPartial_),
      pdf2BuPartial_misId_Bu2Dst0h_D0pi0_(
          ("pdf2BuPartial_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_mean2BuPartial_,
          *misId_Bu2Dst0h_D0pi0_sigma2BuPartial_,
          *misId_Bu2Dst0h_D0pi0_a2BuPartial_,
          *misId_Bu2Dst0h_D0pi0_n2BuPartial_),
      misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs, Sign::same)),
      pdfBuPartial_misId_Bu2Dst0h_D0pi0_(
          new RooAddPdf(("pdfBuPartial_misId_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                            .c_str(),
                        "",
                        RooArgSet(pdf1BuPartial_misId_Bu2Dst0h_D0pi0_,
                                  pdf2BuPartial_misId_Bu2Dst0h_D0pi0_),
                        *misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_)),
      // -------------------- Bu2Dst0h_D0gamma_WN -------------------- //
      Bu2Dst0h_D0gamma_WN_sigma1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_sigma1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::Bu2Dst0h_D0gamma_WN_PdfBu, Sign::same)),
      // Bu2Dst0h_D0gamma_WN_sigma1Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0gamma_WN_sigma1Bu", uniqueId_, Neutral::gamma,
      //     Bachelor::pi, Mode::Bu2Dst0pi_D0gamma_WN, 80, 100)),
      Bu2Dst0h_D0gamma_WN_sigma2Bu_(
          ("Bu2Dst0h_D0gamma_WN_sigma2Bu" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0h_D0gamma_WN_sigma1Bu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0gamma_WN_sigmaRatio21Bu())),
      pdf1Bu_Bu2Dst0h_D0gamma_WN_(
          ("pdf1Bu_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
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
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_WN_mean2Bu(),
          Bu2Dst0h_D0gamma_WN_sigma2Bu_),
      pdfBu_Bu2Dst0h_D0gamma_WN_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "",
          RooArgSet(pdf1Bu_Bu2Dst0h_D0gamma_WN_, pdf2Bu_Bu2Dst0h_D0gamma_WN_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_WN_fracPdf1Bu())),
      Bu2Dst0h_D0gamma_WN_sigma1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_sigma1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::Bu2Dst0h_D0gamma_WN_PdfBuPartial, Sign::same)),
      // Bu2Dst0h_D0gamma_WN_sigma1BuPartial_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0gamma_WN_sigma1BuPartial", uniqueId_, Neutral::gamma,
      //     Bachelor::pi, Mode::Bu2Dst0pi_D0gamma_WN, 80, 100)),
      Bu2Dst0h_D0gamma_WN_sigma2BuPartial_(
          ("Bu2Dst0h_D0gamma_WN_sigma2BuPartial" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0h_D0gamma_WN_sigma1BuPartial_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0gamma_WN_sigmaRatio21BuPartial())),
      pdf1BuPartial_Bu2Dst0h_D0gamma_WN_(
          ("pdf1BuPartial_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_WN_mean1BuPartial(),
          *Bu2Dst0h_D0gamma_WN_sigma1BuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_WN_a1BuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_WN_n1BuPartial()),
      pdf2BuPartial_Bu2Dst0h_D0gamma_WN_(
          ("pdf2BuPartial_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_WN_mean2BuPartial(),
          Bu2Dst0h_D0gamma_WN_sigma2BuPartial_),
      pdfBuPartial_Bu2Dst0h_D0gamma_WN_(
          ("pdfBuPartial_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "",
          RooArgSet(pdf1BuPartial_Bu2Dst0h_D0gamma_WN_,
                    pdf2BuPartial_Bu2Dst0h_D0gamma_WN_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_WN_fracPdf1BuPartial()),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_WN_thresholdDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_thresholdDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_aDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_aDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::none)),
      misId_Bu2Dst0h_D0gamma_WN_bDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_bDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::none)),
      misId_Bu2Dst0h_D0gamma_WN_cDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_cDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_meanDelta_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_sigmaDelta_(nullptr),
      pdfDelta_misId_Bu2Dst0h_D0gamma_WN_(
          new RooDstD0BG(("pdfDelta_misId_Bu2Dst0h_D0gamma_WN_" +
                          ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         "", Configuration::Get().deltaMass(),
                         *misId_Bu2Dst0h_D0gamma_WN_thresholdDelta_,
                         *misId_Bu2Dst0h_D0gamma_WN_cDelta_,
                         *misId_Bu2Dst0h_D0gamma_WN_aDelta_,
                         *misId_Bu2Dst0h_D0gamma_WN_bDelta_)),
      misId_Bu2Dst0h_D0gamma_WN_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_meanBu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_sigmaBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_sigmaBu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_a1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::none)),
      misId_Bu2Dst0h_D0gamma_WN_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_n1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      pdfBu_misId_Bu2Dst0h_D0gamma_WN_(new RooCBShape(
          ("pdfBu_misId_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0gamma_WN_meanBu_,
          *misId_Bu2Dst0h_D0gamma_WN_sigmaBu_, *misId_Bu2Dst0h_D0gamma_WN_a1Bu_,
          *misId_Bu2Dst0h_D0gamma_WN_n1Bu_)),
      misId_Bu2Dst0h_D0gamma_WN_meanBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_meanBu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_sigmaBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_sigmaBu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_a1BuPartial_(nullptr),
      misId_Bu2Dst0h_D0gamma_WN_n1BuPartial_(nullptr),
      pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN_(
          new RooGaussian(("pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN_" +
                           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                              .c_str(),
                          "", Configuration::Get().buDeltaMass(),
                          *misId_Bu2Dst0h_D0gamma_WN_meanBuPartial_,
                          *misId_Bu2Dst0h_D0gamma_WN_sigmaBuPartial_)),
      // -------------------- Bu2Dst0h_D0pi0_WN -------------------- //
      Bu2Dst0h_D0pi0_WN_aDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_aDelta", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfDelta,
          Sign::none)),
      // Bu2Dst0h_D0pi0_WN_aDelta_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_aDelta", uniqueId_, Neutral::gamma,
      //     Bachelor::pi, Mode::Bu2Dst0pi_D0pi0_WN, 0, 1)),
      Bu2Dst0h_D0pi0_WN_bDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_bDelta", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfDelta,
          Sign::none)),
      pdfDelta_Bu2Dst0h_D0pi0_WN_(
          ("pdfDelta_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_thresholdDelta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_cDelta(),
          *Bu2Dst0h_D0pi0_WN_aDelta_, *Bu2Dst0h_D0pi0_WN_bDelta_),
      Bu2Dst0h_D0pi0_WN_sigma1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_sigma1Bu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::Bu2Dst0h_D0pi0_WN_PdfBu,
          Sign::same)),
      // Bu2Dst0h_D0pi0_WN_sigma1Bu_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_WN_sigma1Bu", uniqueId_, Neutral::gamma,
      //     Bachelor::pi, 6.4774e+01, 1.23e+00,
      //     Systematic::Bu2Dst0h_D0pi0_WN_PdfBu, Sign::same)),
      // Bu2Dst0h_D0pi0_WN_sigma1Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_sigma1Bu", uniqueId_, Neutral::gamma,
      //     Bachelor::pi, Mode::Bu2Dst0pi_D0pi0_WN, 20, 75)),
      Bu2Dst0h_D0pi0_WN_sigma2Bu_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_WN_sigma2Bu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0h_D0pi0_WN_sigma1Bu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0pi0_WN_sigmaRatio21Bu()))),
      pdf1Bu_Bu2Dst0h_D0pi0_WN_(
          ("pdf1Bu_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_mean1Bu(),
          *Bu2Dst0h_D0pi0_WN_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0pi0_WN_(
          ("pdf2Bu_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_mean2Bu(),
          *Bu2Dst0h_D0pi0_WN_sigma2Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_n2Bu()),
      pdfBu_Bu2Dst0h_D0pi0_WN_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0h_D0pi0_WN_, pdf2Bu_Bu2Dst0h_D0pi0_WN_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_fracPdf1Bu())),
      Bu2Dst0h_D0pi0_WN_sigma1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_sigma1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0pi_D0pi0_WN,
          Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial, Sign::same)),
      // Bu2Dst0h_D0pi0_WN_sigma1BuPartial_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_sigma1BuPartial", uniqueId_, Neutral::gamma,
      //     Bachelor::pi, Mode::Bu2Dst0pi_D0pi0_WN,
      //     20, 40)),
      // Bu2Dst0h_D0pi0_WN_sigma1BuPartial_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_WN_sigma1BuPartial", uniqueId_, Neutral::gamma,
      //     Bachelor::pi, 3.7198e+01, 1.58e+00,
      //     Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial, Sign::same)),
      Bu2Dst0h_D0pi0_WN_sigma2BuPartial_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_WN_sigma2BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0h_D0pi0_WN_sigma1BuPartial_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0pi0_WN_sigmaRatio21BuPartial()))),
      Bu2Dst0h_D0pi0_WN_sigma3BuPartial_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_WN_sigma3BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0h_D0pi0_WN_sigma1BuPartial_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0h_D0pi0_WN_sigmaRatio31BuPartial()))),
      pdf1BuPartial_Bu2Dst0h_D0pi0_WN_(
          ("pdf1BuPartial_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
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
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
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
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_mean3BuPartial(),
          *Bu2Dst0h_D0pi0_WN_sigma3BuPartial_),
      pdfBuPartial_Bu2Dst0h_D0pi0_WN_(
          ("pdfBuPartial_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
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
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_aDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_aDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::none)),
      misId_Bu2Dst0h_D0pi0_WN_bDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_bDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::none)),
      misId_Bu2Dst0h_D0pi0_WN_cDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_cDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      pdfDelta_misId_Bu2Dst0h_D0pi0_WN_(
          ("pdfDelta_misId_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0pi0_WN_thresholdDelta_,
          *misId_Bu2Dst0h_D0pi0_WN_cDelta_, *misId_Bu2Dst0h_D0pi0_WN_aDelta_,
          *misId_Bu2Dst0h_D0pi0_WN_bDelta_),
      misId_Bu2Dst0h_D0pi0_WN_mean1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_mean1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_mean2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_mean2Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_mean3Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_mean3Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_sigma1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_sigma2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_sigma2Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_sigma3Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_sigma3Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_a1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::none)),
      misId_Bu2Dst0h_D0pi0_WN_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_n1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_a2Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_n2Bu_(nullptr),
      pdf1Bu_misId_Bu2Dst0h_D0pi0_WN_(
          ("pdf1Bu_misId_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_WN_mean1Bu_, *misId_Bu2Dst0h_D0pi0_WN_sigma1Bu_,
          *misId_Bu2Dst0h_D0pi0_WN_a1Bu_, *misId_Bu2Dst0h_D0pi0_WN_n1Bu_),
      pdf2Bu_misId_Bu2Dst0h_D0pi0_WN_(
          new RooGaussian(("pdf2Bu_misId_Bu2Dst0h_D0pi0_WN_" +
                           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                              .c_str(),
                          "", Configuration::Get().buDeltaMass(),
                          *misId_Bu2Dst0h_D0pi0_WN_mean2Bu_,
                          *misId_Bu2Dst0h_D0pi0_WN_sigma2Bu_)),
      pdf3Bu_misId_Bu2Dst0h_D0pi0_WN_(
          ("pdf3Bu_misId_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_WN_mean3Bu_,
          *misId_Bu2Dst0h_D0pi0_WN_sigma3Bu_),
      misId_Bu2Dst0h_D0pi0_WN_fracPdf1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_fracPdf1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_fracPdf2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_fracPdf2Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      pdfBu_misId_Bu2Dst0h_D0pi0_WN_(
          new RooAddPdf(("pdfBu_misId_Bu2Dst0h_D0pi0_WN_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                            .c_str(),
                        "",
                        RooArgSet(pdf1Bu_misId_Bu2Dst0h_D0pi0_WN_,
                                  *pdf2Bu_misId_Bu2Dst0h_D0pi0_WN_,
                                  pdf3Bu_misId_Bu2Dst0h_D0pi0_WN_),
                        RooArgSet(*misId_Bu2Dst0h_D0pi0_WN_fracPdf1Bu_,
                                  *misId_Bu2Dst0h_D0pi0_WN_fracPdf2Bu_))),
      misId_Bu2Dst0h_D0pi0_WN_meanBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_meanBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_sigmaBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_a1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_a1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::none)),
      misId_Bu2Dst0h_D0pi0_WN_n1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_n1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::Bu2Dst0h_WN_misId_Pdfs, Sign::same)),
      pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN_(
          ("pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_WN_meanBuPartial_,
          *misId_Bu2Dst0h_D0pi0_WN_sigmaBuPartial_,
          *misId_Bu2Dst0h_D0pi0_WN_a1BuPartial_,
          *misId_Bu2Dst0h_D0pi0_WN_n1BuPartial_),
      // -------------------- Bd2Dsth -------------------- //
      Bd2Dsth_sigma1Bu_(Params::Get().CreateFixed(
          "Bd2Dsth_sigma1Bu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bd2Dstpi, Systematic::Bd2Dsth_PdfBu, Sign::same)),
      Bd2Dsth_sigma2Bu_(("Bd2Dsth_sigma2Bu_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                            .c_str(),
                        "@0*@1",
                        RooArgSet(*Bd2Dsth_sigma1Bu_,
                                  NeutralVars<Neutral::gamma>::Get(uniqueId_)
                                      .Bd2Dsth_sigmaRatio21Bu())),
      pdf1Bu_Bd2Dsth_(
          ("pdf1Bu_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_mean1Bu(),
          *Bd2Dsth_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_n1Bu()),
      pdf2Bu_Bd2Dsth_(
          ("pdf2Bu_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_mean2Bu(),
          Bd2Dsth_sigma2Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_n2Bu()),
      pdfBu_Bd2Dsth_(new RooAddPdf(
          ("pdfBu_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bd2Dsth_, pdf2Bu_Bd2Dsth_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_fracPdf1Bu())),
      Bd2Dsth_sigma1BuPartial_(Params::Get().CreateFixed(
          "Bd2Dsth_sigma1BuPartial", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bd2Dstpi, Systematic::Bd2Dsth_PdfBuPartial, Sign::same)),
      Bd2Dsth_sigma2BuPartial_(
          ("Bd2Dsth_sigma2BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bd2Dsth_sigma1BuPartial_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bd2Dsth_sigmaRatio21BuPartial())),
      pdf1BuPartial_Bd2Dsth_(
          ("pdf1BuPartial_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_mean1BuPartial(),
          *Bd2Dsth_sigma1BuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_a1BuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_n1BuPartial()),
      pdf2BuPartial_Bd2Dsth_(
          ("pdf2BuPartial_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_mean2BuPartial(),
          Bd2Dsth_sigma2BuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_a2BuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bd2Dsth_n2BuPartial()),
      pdfBuPartial_Bd2Dsth_(
          ("pdfBuPartial_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdf1BuPartial_Bd2Dsth_, pdf2BuPartial_Bd2Dsth_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bd2Dsth_fracPdf1BuPartial()),
      // -------------------- Mis-ID ------------------- //
      misId_Bd2Dsth_meanBu_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_meanBu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bd2DstK, Systematic::Bkg_misId_Pdfs, Sign::same)),
      misId_Bd2Dsth_sigmaBu_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_sigmaBu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bd2DstK, Systematic::Bkg_misId_Pdfs, Sign::same)),
      misId_Bd2Dsth_a1Bu_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_a1Bu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bd2DstK, Systematic::Bkg_misId_Pdfs, Sign::none)),
      misId_Bd2Dsth_n1Bu_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_n1Bu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bd2DstK, Systematic::Bkg_misId_Pdfs, Sign::same)),
      pdfBu_misId_Bd2Dsth_(new RooCBShape(
          ("pdfBu_misId_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_Bd2Dsth_meanBu_,
          *misId_Bd2Dsth_sigmaBu_, *misId_Bd2Dsth_a1Bu_, *misId_Bd2Dsth_n1Bu_)),
      misId_Bd2Dsth_thresholdDelta_(nullptr),
      misId_Bd2Dsth_aDelta_(nullptr),
      misId_Bd2Dsth_bDelta_(nullptr),
      misId_Bd2Dsth_cDelta_(nullptr),
      misId_Bd2Dsth_meanDelta_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_meanDelta", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bd2DstK, Systematic::Bkg_misId_Pdfs, Sign::same)),
      misId_Bd2Dsth_sigmaDelta_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_sigmaDelta", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bd2DstK, Systematic::Bkg_misId_Pdfs, Sign::same)),
      misId_Bd2Dsth_a1Delta_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_a1Delta", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bd2DstK, Systematic::Bkg_misId_Pdfs, Sign::none)),
      misId_Bd2Dsth_n1Delta_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_n1Delta", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bd2DstK, Systematic::Bkg_misId_Pdfs, Sign::same)),
      pdfDelta_misId_Bd2Dsth_(
          new RooDstD0BG(("pdfDelta_misId_Bd2Dsth_" +
                          ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         "", Configuration::Get().buDeltaMass(),
                         *misId_Bd2Dsth_meanDelta_, *misId_Bd2Dsth_sigmaDelta_,
                         *misId_Bd2Dsth_a1Delta_, *misId_Bd2Dsth_n1Delta_)),
      misId_Bd2Dsth_meanBuPartial_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_meanBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bd2DstK, Systematic::Bkg_misId_Pdfs, Sign::same)),
      misId_Bd2Dsth_sigmaBuPartial_(Params::Get().CreateFixed(
          "misId_Bd2Dsth_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bd2DstK, Systematic::Bkg_misId_Pdfs, Sign::same)),
      misId_Bd2Dsth_a1BuPartial_(nullptr),
      misId_Bd2Dsth_n1BuPartial_(nullptr),
      pdfBuPartial_misId_Bd2Dsth_(new RooGaussian(
          ("pdfBuPartial_misId_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_Bd2Dsth_meanBuPartial_,
          *misId_Bd2Dsth_sigmaBuPartial_)),
      // -------------------- Bu2D0hst -------------------- //
      Bu2D0hst_sigma1Bu_(Params::Get().CreateFixed(
          "Bu2D0hst_sigma1Bu", uniqueId, Neutral::gamma, Bachelor::pi,
          Mode::Bu2D0rho, Systematic::Bu2D0hst_PdfBu, Sign::same)),
      // Bu2D0hst_sigma1Bu_(Params::Get().CreateFloating(
      //     "Bu2D0hst_sigma1Bu", uniqueId, Neutral::gamma, Bachelor::pi,
      //     Mode::Bu2D0rho, 70, 110)),
      // Bu2D0hst_sigma1Bu_(Params::Get().CreateFixed(
      //     "Bu2D0hst_sigma1Bu", uniqueId, Neutral::gamma, Bachelor::pi,
      //     8.8970e+01, 1.06e+00, Systematic::Bu2D0hst_PdfBu, Sign::same)),
      Bu2D0hst_sigma2Bu_(("Bu2D0hst_sigma2Bu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         "@0*@1",
                         RooArgSet(*Bu2D0hst_sigma1Bu_,
                                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .Bu2D0hst_sigmaRatio21Bu())),
      pdf1Bu_Bu2D0hst_(
          ("pdf1Bu_Bu2D0hst_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0hst_mean1Bu(),
          *Bu2D0hst_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0hst_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0hst_n1Bu()),
      pdf2Bu_Bu2D0hst_(
          ("pdf2Bu_Bu2D0hst_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0hst_mean2Bu(),
          Bu2D0hst_sigma2Bu_),
      pdfBu_Bu2D0hst_(new RooAddPdf(
          ("pdfBu_Bu2D0hst_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2D0hst_, pdf2Bu_Bu2D0hst_),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0hst_fracPdf1Bu())),
      Bu2D0hst_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2D0hst_sigmaBuPartial", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2D0rho, Systematic::Bu2D0hst_PdfBuPartial, Sign::same)),
      // Bu2D0hst_sigmaBuPartial_(Params::Get().CreateFloating(
      //     "Bu2D0hst_sigmaBuPartial", uniqueId_, Neutral::gamma, Bachelor::pi,
      //     Mode::Bu2D0rho, 60, 100)),
      // Bu2D0hst_sigmaBuPartial_(Params::Get().CreateFixed(
      //     "Bu2D0hst_sigmaBuPartial", uniqueId_, Neutral::gamma, Bachelor::pi,
      //     7.9661e+01, 1.33e+00, Systematic::Bu2D0hst_PdfBuPartial,
      //     Sign::same)),
      pdfBuPartial_Bu2D0hst_(
          ("pdfBuPartial_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0hst_meanBuPartial(),
          *Bu2D0hst_sigmaBuPartial_),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2D0hst_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_meanBu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2D0Kst, Systematic::Bkg_misId_Pdfs, Sign::same)),
      misId_Bu2D0hst_sigmaBu_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_sigmaBu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2D0Kst, Systematic::Bkg_misId_Pdfs, Sign::same)),
      misId_Bu2D0hst_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_a1Bu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2D0Kst, Systematic::Bkg_misId_Pdfs, Sign::none)),
      misId_Bu2D0hst_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_n1Bu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2D0Kst, Systematic::Bkg_misId_Pdfs, Sign::same)),
      pdfBu_misId_Bu2D0hst_(
          new RooCBShape(("pdfBu_misId_Bu2D0hst_" +
                          ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         "", Configuration::Get().buDeltaMass(),
                         *misId_Bu2D0hst_meanBu_, *misId_Bu2D0hst_sigmaBu_,
                         *misId_Bu2D0hst_a1Bu_, *misId_Bu2D0hst_n1Bu_)),
      misId_Bu2D0hst_thresholdDelta_(nullptr),
      misId_Bu2D0hst_aDelta_(nullptr),
      misId_Bu2D0hst_bDelta_(nullptr),
      misId_Bu2D0hst_cDelta_(nullptr),
      misId_Bu2D0hst_meanDelta_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_meanDelta", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2D0Kst, Systematic::Bkg_misId_Pdfs, Sign::same)),
      misId_Bu2D0hst_sigmaDelta_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_sigmaDelta", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2D0Kst, Systematic::Bkg_misId_Pdfs, Sign::same)),
      misId_Bu2D0hst_a1Delta_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_a1Delta", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2D0Kst, Systematic::Bkg_misId_Pdfs, Sign::none)),
      misId_Bu2D0hst_n1Delta_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_n1Delta", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2D0Kst, Systematic::Bkg_misId_Pdfs, Sign::same)),
      pdfDelta_misId_Bu2D0hst_(new RooCBShape(
          ("pdfDelta_misId_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_Bu2D0hst_meanDelta_,
          *misId_Bu2D0hst_sigmaDelta_, *misId_Bu2D0hst_a1Delta_,
          *misId_Bu2D0hst_n1Delta_)),
      misId_Bu2D0hst_meanBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_meanBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2D0Kst, Systematic::Bkg_misId_Pdfs,
          Sign::same)),
      misId_Bu2D0hst_sigmaBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2D0Kst, Systematic::Bkg_misId_Pdfs,
          Sign::same)),
      misId_Bu2D0hst_a1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_a1BuPartial", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2D0Kst, Systematic::Bkg_misId_Pdfs, Sign::none)),
      misId_Bu2D0hst_n1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2D0hst_n1BuPartial", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2D0Kst, Systematic::Bkg_misId_Pdfs, Sign::same)),
      pdfBuPartial_misId_Bu2D0hst_(
          ("pdfBuPartial_misId_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2D0hst_meanBuPartial_, *misId_Bu2D0hst_sigmaBuPartial_,
          *misId_Bu2D0hst_a1BuPartial_, *misId_Bu2D0hst_n1BuPartial_),
      // -------------------- Bu2Dst0hst_D0gamma -------------------- //
      // Bu2Dst0hst_D0gamma_sigma1Bu_(Params::Get().CreateFixed(
      //     "Bu2Dst0hst_D0gamma_sigma1Bu", uniqueId_, Neutral::gamma,
      //     Bachelor::pi, Mode::Bu2Dst0rho_D0gamma,
      //     Systematic::Bu2Dst0hst_D0gamma_PdfBu, Sign::same)),
      // Bu2Dst0hst_D0gamma_sigma1Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0hst_D0gamma_sigma1Bu", uniqueId_, Neutral::gamma,
      //     Bachelor::pi, Mode::Bu2Dst0rho_D0gamma, 20, 35)),
      Bu2Dst0hst_D0gamma_sigma1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_sigma1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, 2.8608e+01, 2.08e+00,
          Systematic::Bu2Dst0hst_D0gamma_PdfBu, Sign::same)),
      Bu2Dst0hst_D0gamma_sigma2Bu_(
          ("Bu2Dst0hst_D0gamma_sigma2Bu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0hst_D0gamma_sigma1Bu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_)
                        .Bu2Dst0hst_D0gamma_sigmaRatio21Bu())),
      pdf1Bu_Bu2Dst0hst_D0gamma_(
          ("pdf1Bu_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0hst_D0gamma_mean1Bu(),
          *Bu2Dst0hst_D0gamma_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0hst_D0gamma_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0hst_D0gamma_n1Bu()),
      pdf2Bu_Bu2Dst0hst_D0gamma_(
          ("pdf2Bu_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0hst_D0gamma_mean2Bu(),
          Bu2Dst0hst_D0gamma_sigma2Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0hst_D0gamma_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0hst_D0gamma_n2Bu()),
      pdfBu_Bu2Dst0hst_D0gamma_(new RooAddPdf(
          ("pdfBu_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0hst_D0gamma_, pdf2Bu_Bu2Dst0hst_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0hst_D0gamma_fracPdf1Bu())),
      Bu2Dst0hst_D0gamma_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0rho_D0gamma,
          Systematic::Bu2Dst0hst_D0gamma_PdfBuPartial, Sign::same)),
      pdfBuPartial_Bu2Dst0hst_D0gamma_(
          ("pdfBuPartial_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0hst_D0gamma_meanBuPartial(),
          *Bu2Dst0hst_D0gamma_sigmaBuPartial_),
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
          "Bu2Dst0hst_D0pi0_sigmaBu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2Dst0rho_D0pi0, Systematic::Bu2Dst0hst_D0pi0_PdfBu,
          Sign::same)),
      pdfBu_Bu2Dst0hst_D0pi0_(
          ("pdfBu_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0hst_D0pi0_meanBu(),
          *Bu2Dst0hst_D0pi0_sigmaBu_),
      // Bu2Dst0hst_D0pi0_sigmaBuPartial_(Params::Get().CreateFixed(
      //     "Bu2Dst0hst_D0pi0_sigmaBuPartial", uniqueId_, Neutral::gamma,
      //     Bachelor::pi, Mode::Bu2Dst0rho_D0pi0,
      //     Systematic::Bu2Dst0hst_D0pi0_PdfBuPartial, Sign::same)),
      // Bu2Dst0hst_D0pi0_sigmaBuPartial_(Params::Get().CreateFloating(
      //     "Bu2Dst0hst_D0pi0_sigmaBuPartial", uniqueId_, Neutral::gamma,
      //     Bachelor::pi, Mode::Bu2Dst0rho_D0pi0, 30, 50)),
      Bu2Dst0hst_D0pi0_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, 4.2889e+01, 1.38e+00,
          Systematic::Bu2Dst0hst_D0pi0_PdfBuPartial, Sign::same)),
      pdfBuPartial_Bu2Dst0hst_D0pi0_(
          ("pdfBuPartial_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0hst_D0pi0_meanBuPartial(),
          *Bu2Dst0hst_D0pi0_sigmaBuPartial_),
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
      // -------------------- Correct ID BOX EFFs -------------------- //
      orEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::boxEffs_Bu2Dst0h_D0gamma, Sign::same)),
      orEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi, Efficiency::orEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::boxEffs_Bu2Dst0h_D0pi0, Sign::same)),
      orEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::boxEffs_WN, Sign::same)),
      orEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::boxEffs_WN, Sign::same)),
      orEffBd2Dsth_(Params::Get().CreateFixed(
          "orEffBd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEffErr,
                        false),
          Systematic::boxEffs_Bd2Dsth, Sign::same)),
      orEffBu2D0hst_(Params::Get().CreateFixed(
          "orEffBu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::orEffErr,
                        false),
          Systematic::boxEffs_Bu2D0hst, Sign::same)),
      orEffBu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "orEffBu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::boxEffs_Bu2Dst0hst, Sign::same)),
      orEffBu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "orEffBu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi, Efficiency::orEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::boxEffs_Bu2Dst0hst, Sign::same)),
      buEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_Bu2Dst0h_D0gamma, Sign::same)),
      // buEffBu2Dst0h_D0gamma_(Params::Get().CreateFloating(
      //     "buEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::pi,
      //     ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
      //                   Efficiency::buEff, false), 0, 1)),
      // buEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
      //     "buEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::pi,
      //     9.4214e-01, 9.4214e-01-9.2602e-01,
      //     Systematic::boxEffs_Bu2Dst0h_D0gamma, Sign::same)),
      buEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_Bu2Dst0h_D0pi0, Sign::same)),
      buEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_WN, Sign::same)),
      // buEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFloating(
      //     "buEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
      //     Bachelor::pi, ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN,
      //     Bachelor::pi,
      //                   Efficiency::buEff, false), 0, 1)),
      buEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_WN, Sign::same)),
      // buEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFloating(
      //     "buEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma, Bachelor::pi,
      //     ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
      //                   Efficiency::buEff, false), 0, 1)),
      buEffBd2Dsth_(Params::Get().CreateFixed(
          "buEffBd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::buEffErr,
                        false),
          Systematic::boxEffs_Bd2Dsth, Sign::same)),
      buEffBu2D0hst_(Params::Get().CreateFixed(
          "buEffBu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::buEffErr,
                        false),
          Systematic::boxEffs_Bu2D0hst, Sign::same)),
      buEffBu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "buEffBu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_Bu2Dst0hst, Sign::same)),
      buEffBu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "buEffBu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::boxEffs_Bu2Dst0hst, Sign::same)),
      deltaEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_Bu2Dst0h_D0gamma, Sign::same)),
      deltaEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_Bu2Dst0h_D0pi0, Sign::same)),
      deltaEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_WN, Sign::same)),
      deltaEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_WN, Sign::same)),
      deltaEffBd2Dsth_(Params::Get().CreateFixed(
          "deltaEffBd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::deltaEff,
                        false),
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::deltaEffErr,
                        false),
          Systematic::boxEffs_Bd2Dsth, Sign::same)),
      deltaEffBu2D0hst_(Params::Get().CreateFixed(
          "deltaEffBu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::deltaEff,
                        false),
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::deltaEffErr,
                        false),
          Systematic::boxEffs_Bu2D0hst, Sign::same)),
      deltaEffBu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_Bu2Dst0hst, Sign::same)),
      deltaEffBu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::boxEffs_Bu2Dst0hst, Sign::same)),
      buPartialEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_Bu2Dst0h_D0gamma, Sign::same)),
      buPartialEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_Bu2Dst0h_D0pi0, Sign::same)),
      // buPartialEffBu2Dst0h_D0pi0_(Params::Get().CreateFloating(
      //     "buPartialEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma,
      //     Bachelor::pi,
      //     ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
      //                   Efficiency::buPartialEff, false), 0, 1)),
      // buPartialEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
      //     "buPartialEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma,
      //     Bachelor::pi, 8.4080e-01, 8.7414e-01-8.4080e-01,
      //     Systematic::boxEffs_Bu2Dst0h_D0pi0, Sign::same)),
      buPartialEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_WN, Sign::same)),
      // buPartialEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFloating(
      //     "buPartialEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
      //     Bachelor::pi,
      //     ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
      //                   Efficiency::buPartialEff, false), 0, 1)),
      buPartialEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_WN, Sign::same)),
      // buPartialEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFloating(
      //     "buPartialEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma,
      //     Bachelor::pi,
      //     ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
      //                   Efficiency::buPartialEff, false), 0, 1)),
      buPartialEffBd2Dsth_(Params::Get().CreateFixed(
          "buPartialEffBd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::buPartialEff,
                        false),
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_Bd2Dsth, Sign::same)),
      buPartialEffBu2D0hst_(Params::Get().CreateFixed(
          "buPartialEffBu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::buPartialEff,
                        false),
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_Bu2D0hst, Sign::same)),
      buPartialEffBu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_Bu2Dst0hst, Sign::same)),
      buPartialEffBu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::boxEffs_Bu2Dst0hst, Sign::same)),
      // -------------------- Mis-ID BoxEffs ------------------- //
      orEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi, Efficiency::orEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::boxEffs_Bu2Dst0h_D0gamma_misId, Sign::same)),
      orEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi, Efficiency::orEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::boxEffs_Bu2Dst0h_D0pi0_misId, Sign::same)),
      orEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      orEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      orEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "orEffMisId_Bd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::orEffErr,
                        true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      orEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "orEffMisId_Bu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::orEffErr,
                        true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      orEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      orEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi, Efficiency::orEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      buEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi, Efficiency::buEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::boxEffs_Bu2Dst0h_D0gamma_misId, Sign::same)),
      buEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi, Efficiency::buEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::boxEffs_Bu2Dst0h_D0pi0_misId, Sign::same)),
      buEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      buEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      buEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "buEffMisId_Bd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::buEffErr,
                        true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      buEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "buEffMisId_Bu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::buEffErr,
                        true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      buEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      buEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi, Efficiency::buEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      deltaEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::boxEffs_Bu2Dst0h_D0gamma_misId, Sign::same)),
      deltaEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::boxEffs_Bu2Dst0h_D0pi0_misId, Sign::same)),
      deltaEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      deltaEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      deltaEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "deltaEffMisId_Bd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::deltaEff,
                        true),
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::deltaEffErr,
                        true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      deltaEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::deltaEff,
                        true),
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::deltaEffErr,
                        true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      deltaEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      deltaEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      buPartialEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::boxEffs_Bu2Dst0h_D0gamma_misId, Sign::same)),
      buPartialEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::boxEffs_Bu2Dst0h_D0pi0_misId, Sign::same)),
      buPartialEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      buPartialEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      buPartialEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::buPartialEff,
                        true),
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      buPartialEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2D0hst_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::buPartialEff,
                        true),
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      buPartialEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      buPartialEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::boxEffs_Bkg_misId, Sign::same)),
      // -------------------- MC Efficiencies -------------------- //
      mcEff_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bu2Dst0h_D0gamma, Sign::same)),
      mcEff_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bu2Dst0h_D0pi0, Sign::same)),
      mcEff_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg, Sign::same)),
      mcEff_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg, Sign::same)),
      mcEff_Bd2Dsth_(Params::Get().CreateFixed(
          "mcEff_Bd2Dsth", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bd2Dstpi, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bd2Dstpi, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg, Sign::same)),
      mcEff_Bu2D0hst_(Params::Get().CreateFixed(
          "mcEff_Bu2D0hst", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2D0rho, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2D0rho, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg, Sign::same)),
      mcEff_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0hst_D0gamma", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg, Sign::same)),
      mcEff_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0hst_D0pi0", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg, Sign::same)),
      // -------------------- MC misId Efficiencies -------------------- //
      mcEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bu2Dst0h_D0pi0_misId, Sign::same)),
      mcEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bu2Dst0h_D0gamma_misId, Sign::same)),
      mcEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma_WN, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma_WN, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg_misId, Sign::same)),
      mcEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0_WN, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0_WN, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg_misId, Sign::same)),
      mcEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "mcEffMisId_Bd2Dsth", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bd2DstK, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bd2DstK, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg_misId, Sign::same)),
      mcEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2D0hst", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2D0Kst, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2D0Kst, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg_misId, Sign::same)),
      mcEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0hst_D0gamma", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0Kst_D0gamma, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0Kst_D0gamma, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg_misId, Sign::same)),
      mcEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0hst_D0pi0", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0Kst_D0pi0, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0Kst_D0pi0, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs_Bkg_misId, Sign::same)),
      // -------------------- Bkg Fractions -------------------- //
      // bkgFracGlobal_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFloating(
      //     "bkgFracGlobal_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::gamma,
      //     (ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, Neutral::gamma,
      //     Bachelor::pi,
      //                   Efficiency::mcEff) /
      //      ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::gamma, Bachelor::pi,
      //                   Efficiency::mcEff)),
      //     0, 5)),
      bkgFrac_Bu2Dst0h_D0pi0_WN_(new RooFormulaVar(
          ("bkgFrac_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "(@0/@1)*(@2/@3)",
          RooArgList(*orEffBu2Dst0h_D0pi0_WN_, *orEffBu2Dst0h_D0pi0_,
                     *mcEff_Bu2Dst0h_D0pi0_WN_, *mcEff_Bu2Dst0h_D0pi0_))),
      // bkgFracGlobal_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFloating(
      //     "bkgFracGlobal_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::gamma,
      //     ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN, Neutral::gamma,
      //     Bachelor::pi,
      //                  Efficiency::mcEff) /
      //         ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma, Neutral::gamma,
      //                      Bachelor::pi, Efficiency::mcEff),
      //     0, 5)),
      bkgFrac_Bu2Dst0h_D0gamma_WN_(new RooFormulaVar(
          ("bkgFrac_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "(@0/@1)*(@2/@3)",
          RooArgList(*orEffBu2Dst0h_D0gamma_WN_, *orEffBu2Dst0h_D0gamma_,
                     *mcEff_Bu2Dst0h_D0gamma_WN_, *mcEff_Bu2Dst0h_D0gamma_))),
      bkgFrac_Bu2Dst0h_WN_(),
      // -------------------- Bu2Dst0h_WN -------------------- //
      Bu2Dst0h_WN_fracD0pi0_(),
      Bu2Dst0h_WN_fracD0pi0_Bu_(),
      Bu2Dst0h_WN_fracD0pi0_Delta_(),
      pdfBu_Bu2Dst0h_WN_(),
      pdfDelta_Bu2Dst0h_WN_(),
      orEffBu2Dst0h_WN_(),
      buEffBu2Dst0h_WN_(),
      deltaEffBu2Dst0h_WN_(),
      mcEff_Bu2Dst0h_WN_(),
      Bu2Dst0h_WN_misId_fracD0pi0_(),
      Bu2Dst0h_WN_misId_fracD0pi0_Bu_(),
      Bu2Dst0h_WN_misId_fracD0pi0_Delta_(),
      pdfBu_misId_Bu2Dst0h_WN_(),
      pdfDelta_misId_Bu2Dst0h_WN_(),
      orEffMisId_Bu2Dst0h_WN_(),
      buEffMisId_Bu2Dst0h_WN_(),
      deltaEffMisId_Bu2Dst0h_WN_(),
      mcEffMisId_Bu2Dst0h_WN_(),
      // -------------------- Bu2Dst0hst -------------------- //
      Bu2Dst0hst_fracD0pi0_(Params::Get().CreateFixed(
          "Bu2Dst0hst_fracD0pi0", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReadPdfFracs<Neutral::gamma, Bachelor::pi>("Bu2Dst0hst_fracD0pi0",
                                                     ReturnType::val),
          ReadPdfFracs<Neutral::gamma, Bachelor::pi>("Bu2Dst0hst_fracD0pi0",
                                                     ReturnType::std),
          Systematic::Bu2Dst0hst_Frac, Sign::same)),
      Bu2Dst0hst_fracD0pi0_Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_fracD0pi0_Bu", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReadPdfFracs<Neutral::gamma, Bachelor::pi>("Bu2Dst0hst_fracD0pi0_Bu",
                                                     ReturnType::val),
          ReadPdfFracs<Neutral::gamma, Bachelor::pi>("Bu2Dst0hst_fracD0pi0_Bu",
                                                     ReturnType::std),
          Systematic::Bu2Dst0hst_Frac, Sign::same)),
      Bu2Dst0hst_fracD0pi0_Delta_(Params::Get().CreateFixed(
          "Bu2Dst0hst_fracD0pi0_Delta", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReadPdfFracs<Neutral::gamma, Bachelor::pi>(
              "Bu2Dst0hst_fracD0pi0_Delta", ReturnType::val),
          ReadPdfFracs<Neutral::gamma, Bachelor::pi>(
              "Bu2Dst0hst_fracD0pi0_Delta", ReturnType::std),
          Systematic::Bu2Dst0hst_Frac, Sign::same)),
      Bu2Dst0hst_fracD0pi0_BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0hst_fracD0pi0_BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReadPdfFracs<Neutral::gamma, Bachelor::pi>(
              "Bu2Dst0hst_fracD0pi0_BuPartial", ReturnType::val),
          ReadPdfFracs<Neutral::gamma, Bachelor::pi>(
              "Bu2Dst0hst_fracD0pi0_BuPartial", ReturnType::std),
          Systematic::Bu2Dst0hst_Frac, Sign::same)),
      pdfBu_Bu2Dst0hst_(new RooAddPdf(
          ("pdfBu_Bu2Dst0hst_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdfBu_Bu2Dst0hst_D0pi0_, *pdfBu_Bu2Dst0hst_D0gamma_),
          *Bu2Dst0hst_fracD0pi0_Bu_)),
      pdfDelta_Bu2Dst0hst_(
          new RooAddPdf(("pdfDelta_Bu2Dst0hst_" +
                         ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                            .c_str(),
                        "",
                        RooArgSet(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                      .pdfDelta_Bu2Dst0hst_D0pi0(),
                                  NeutralVars<Neutral::gamma>::Get(uniqueId)
                                      .pdfDelta_Bu2Dst0hst_D0gamma()),
                        *Bu2Dst0hst_fracD0pi0_Delta_)),
      pdfBuPartial_Bu2Dst0hst_(
          ("pdfBuPartial_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "",
          RooArgSet(pdfBuPartial_Bu2Dst0hst_D0pi0_,
                    pdfBuPartial_Bu2Dst0hst_D0gamma_),
          *Bu2Dst0hst_fracD0pi0_BuPartial_),
      orEffBu2Dst0hst_(
          ("orEffBu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bu2Dst0hst_fracD0pi0_, *orEffBu2Dst0hst_D0pi0_,
                     *orEffBu2Dst0hst_D0gamma_)),
      buEffBu2Dst0hst_(
          ("buEffBu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bu2Dst0hst_fracD0pi0_, *buEffBu2Dst0hst_D0pi0_,
                     *buEffBu2Dst0hst_D0gamma_)),
      deltaEffBu2Dst0hst_(
          ("deltaEffBu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bu2Dst0hst_fracD0pi0_, *deltaEffBu2Dst0hst_D0pi0_,
                     *deltaEffBu2Dst0hst_D0gamma_)),
      buPartialEffBu2Dst0hst_(
          ("buPartialEffBu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bu2Dst0hst_fracD0pi0_, *buPartialEffBu2Dst0hst_D0pi0_,
                     *buPartialEffBu2Dst0hst_D0gamma_)),
      mcEff_Bu2Dst0hst_(
          ("mcEff_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bu2Dst0hst_fracD0pi0_, *mcEff_Bu2Dst0hst_D0pi0_,
                     *mcEff_Bu2Dst0hst_D0gamma_)),
      Bu2Dst0hst_misId_fracD0pi0_(Params::Get().CreateFixed(
          "Bu2Dst0hst_misId_fracD0pi0", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReadPdfFracs<Neutral::gamma, Bachelor::pi>(
              "Bu2Dst0hst_misId_fracD0pi0", ReturnType::val),
          ReadPdfFracs<Neutral::gamma, Bachelor::pi>(
              "Bu2Dst0hst_misId_fracD0pi0", ReturnType::std),
          Systematic::Bu2Dst0hst_Frac, Sign::same)),
      Bu2Dst0hst_misId_fracD0pi0_Bu_(Params::Get().CreateFixed(
          "Bu2Dst0hst_misId_fracD0pi0_Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReadPdfFracs<Neutral::gamma, Bachelor::pi>(
              "Bu2Dst0hst_misId_fracD0pi0_Bu", ReturnType::val),
          ReadPdfFracs<Neutral::gamma, Bachelor::pi>(
              "Bu2Dst0hst_misId_fracD0pi0_Bu", ReturnType::std),
          Systematic::Bu2Dst0hst_Frac, Sign::same)),
      Bu2Dst0hst_misId_fracD0pi0_Delta_(Params::Get().CreateFixed(
          "Bu2Dst0hst_misId_fracD0pi0_Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReadPdfFracs<Neutral::gamma, Bachelor::pi>(
              "Bu2Dst0hst_misId_fracD0pi0_Delta", ReturnType::val),
          ReadPdfFracs<Neutral::gamma, Bachelor::pi>(
              "Bu2Dst0hst_misId_fracD0pi0_Delta", ReturnType::std),
          Systematic::Bu2Dst0hst_Frac, Sign::same)),
      Bu2Dst0hst_misId_fracD0pi0_BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0hst_misId_fracD0pi0_BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReadPdfFracs<Neutral::gamma, Bachelor::pi>(
              "Bu2Dst0hst_misId_fracD0pi0_BuPartial", ReturnType::val),
          ReadPdfFracs<Neutral::gamma, Bachelor::pi>(
              "Bu2Dst0hst_misId_fracD0pi0_BuPartial", ReturnType::std),
          Systematic::Bu2Dst0hst_Frac, Sign::same)),
      pdfBu_misId_Bu2Dst0hst_(nullptr),
      pdfDelta_misId_Bu2Dst0hst_(),
      pdfBuPartial_misId_Bu2Dst0hst_(),
      orEffMisId_Bu2Dst0hst_(
          ("orEffMisId_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bu2Dst0hst_misId_fracD0pi0_,
                     *orEffMisId_Bu2Dst0hst_D0pi0_,
                     *orEffMisId_Bu2Dst0hst_D0gamma_)),
      buEffMisId_Bu2Dst0hst_(
          ("buEffMisId_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bu2Dst0hst_misId_fracD0pi0_,
                     *buEffMisId_Bu2Dst0hst_D0pi0_,
                     *buEffMisId_Bu2Dst0hst_D0gamma_)),
      deltaEffMisId_Bu2Dst0hst_(
          ("deltaEffMisId_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bu2Dst0hst_misId_fracD0pi0_,
                     *deltaEffMisId_Bu2Dst0hst_D0pi0_,
                     *deltaEffMisId_Bu2Dst0hst_D0gamma_)),
      buPartialEffMisId_Bu2Dst0hst_(
          ("buPartialEffMisId_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bu2Dst0hst_misId_fracD0pi0_,
                     *buPartialEffMisId_Bu2Dst0hst_D0pi0_,
                     *buPartialEffMisId_Bu2Dst0hst_D0gamma_)),
      mcEffMisId_Bu2Dst0hst_(
          ("mcEffMisId_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(*Bu2Dst0hst_fracD0pi0_, *mcEffMisId_Bu2Dst0hst_D0pi0_,
                     *mcEffMisId_Bu2Dst0hst_D0gamma_)),
      // -------------------- Bs2Dst0Kst0_D0pi0 -------------------- //
      pdf1Delta_Bs2Dst0Kst0_D0pi0_(),
      pdf2Delta_Bs2Dst0Kst0_D0pi0_(),
      pdfDelta_Bs2Dst0Kst0_D0pi0_(),
      // -------------------- Bs2Dst0Kst0_D0gamma -------------------- //
      pdf1Delta_Bs2Dst0Kst0_D0gamma_(),
      pdf2Delta_Bs2Dst0Kst0_D0gamma_(),
      pdfDelta_Bs2Dst0Kst0_D0gamma_(),
      // -------------------- Bs2Dst0Kst0_comb -------------------- //
      pdfDelta_Bs2Dst0Kst0_comb_(),
      // -------------------- Bs2Dst0Kst0_D0pi0_WN -------------------- //
      Bs2Dst0Kst0_D0pi0_WN_aDelta_(nullptr),
      Bs2Dst0Kst0_D0pi0_WN_bDelta_(nullptr),
      pdfDelta_Bs2Dst0Kst0_D0pi0_WN_(),
      // -------------------- Bs2Dst0Kst0_WN -------------------- //
      pdfDelta_Bs2Dst0Kst0_WN_(),
      // -------------------- Bs2Dst0Kst0 -------------------- //
      pdfDelta_Bs2Dst0Kst0_(),
      // -------------------- Combinatorial -------------------- //
      pdfDeltaPeak_D0pi0_comb_(
          ("pdfDeltaPeak_D0pi0_comb_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_fracPdf1Delta()),
      pdfDeltaPeak_D0gamma_comb_(
          ("pdfDeltaPeak_D0gamma_comb_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0gamma_, pdf2Delta_Bu2Dst0h_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_fracPdf1Delta()),
      fracPdfPeak_D0pi0_comb_(
          ("fracPdfPeak_D0pi0_comb_" + ComposeName(uniqueId_, Neutral::gamma))
              .c_str(),
          "", "(@0*(@1/@2))/(1+(@0*(@1/@2)))",
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId).BR_pi02gamma_eff(),
              *mcEff_Bu2Dst0h_D0pi0_, *mcEff_Bu2Dst0h_D0gamma_)),
      pdfDeltaPeak_comb_(
          ("pdfDeltaPeak_comb_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgList(pdfDeltaPeak_D0pi0_comb_, pdfDeltaPeak_D0gamma_comb_),
          fracPdfPeak_D0pi0_comb_),
      pdfDeltaFlat_comb_(("pdfDeltaFlat_comb_" +
                          ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         "", Configuration::Get().deltaMass(),
                         NeutralVars<Neutral::gamma>::Get(uniqueId_)
                             .Bu2Dst0h_D0pi0_WN_thresholdDelta(),
                         NeutralVars<Neutral::gamma>::Get(uniqueId_)
                             .Bu2Dst0h_D0pi0_WN_cDelta(),
                         *Bu2Dst0h_D0pi0_WN_aDelta_,
                         *Bu2Dst0h_D0pi0_WN_bDelta_),
      fracPdfFlat_comb_(
          ("fracPdfFlat_comb_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", "(@0*((@1+@2)/(@3+@4)))/(1+(@0*((@1+@2)/(@3+@4))))",
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId_).bkgFracGlobal_WN(),
              *mcEff_Bu2Dst0h_D0pi0_WN_, *mcEff_Bu2Dst0h_D0gamma_WN_,
              *mcEff_Bu2Dst0h_D0pi0_, *mcEff_Bu2Dst0h_D0gamma_)),
      pdfDelta_comb_(("pdfDelta_comb_" +
                      ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                         .c_str(),
                     "", RooArgList(pdfDeltaFlat_comb_, pdfDeltaPeak_comb_),
                     fracPdfFlat_comb_),
      buEff_comb_(
          ("buEff_comb_" + ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@2 + @1*(1-@2)",
          RooArgList(*buEffBu2Dst0h_D0pi0_WN_, *buEffBu2Dst0h_D0gamma_,
                     fracPdfFlat_comb_)),
      buPartialEff_comb_(
          ("buPartialEff_comb_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@2 + @1*(1-@2)",
          RooArgList(*buPartialEffBu2Dst0h_D0pi0_WN_,
                     *buPartialEffBu2Dst0h_D0pi0_, fracPdfFlat_comb_)) {
  std::cout << "WN FRAC COMB = \n";
  fracPdfFlat_comb_.Print();
}
