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
          Systematic::misIdGammaPiPdfDelta, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_sigmaDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_sigmaDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::misIdGammaPiPdfDelta, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_a1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a1Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::misIdGammaPiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0gamma_n1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n1Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::misIdGammaPiPdfDelta, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_a2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a2Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::misIdGammaPiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0gamma_n2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n2Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma,
          Systematic::misIdGammaPiPdfDelta, Sign::positive)),
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
          Systematic::misIdGammaPiPdfDelta, Sign::positive)),
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
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma, Systematic::misIdGammaPiPdfBu,
          Sign::positive)),
      misId_Bu2Dst0h_D0gamma_sigmaBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_sigmaBu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma, Systematic::misIdGammaPiPdfBu,
          Sign::positive)),
      misId_Bu2Dst0h_D0gamma_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma, Systematic::misIdGammaPiPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0gamma_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma, Systematic::misIdGammaPiPdfBu,
          Sign::positive)),
      misId_Bu2Dst0h_D0gamma_a2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a2Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma, Systematic::misIdGammaPiPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0gamma_n2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n2Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma, Systematic::misIdGammaPiPdfBu,
          Sign::positive)),
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
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma, Systematic::misIdGammaPiPdfBu,
          Sign::positive)),
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
          Mode::Bu2Dst0pi_D0pi0, Systematic::crossFeedBuPdf, Sign::same)),
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
      //     Bachelor::pi, Mode::Bu2Dst0pi_D0pi0,
      //     Systematic::pi0BuPartialSigma1, Sign::positive)),
      Bu2Dst0h_D0pi0_sigma1BuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_sigma1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0pi_D0pi0, 20, 30)),
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
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfDelta,
          Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigmaDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigmaDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfDelta,
          Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfDelta,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_n1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfDelta,
          Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a2Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfDelta,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n2Delta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfDelta,
          Sign::positive)),
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
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfDelta,
          Sign::positive)),
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
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfBu,
          Sign::positive)),
      misId_Bu2Dst0h_D0pi0_mean2Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfBu,
          Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigma2Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1Bu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1Bu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2Dst0K_D0pi0, Systematic::misIdPi0PiPdfBu, Sign::positive)),
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
          Systematic::misIdPi0PiPdfBuPartial, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_mean2BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_mean2BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::misIdPi0PiPdfBuPartial, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigma1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::misIdPi0PiPdfBuPartial, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigma2BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma2BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::misIdPi0PiPdfBuPartial, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::misIdPi0PiPdfBuPartial, Sign::same)),
      misId_Bu2Dst0h_D0pi0_n1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::misIdPi0PiPdfBuPartial, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a2BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a2BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::misIdPi0PiPdfBuPartial, Sign::same)),
      misId_Bu2Dst0h_D0pi0_n2BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n2BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0,
          Systematic::misIdPi0PiPdfBuPartial, Sign::positive)),
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
          Systematic::misIdPi0PiPdfBuPartial, Sign::positive)),
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
          Bachelor::pi, Mode::Bu2Dst0pi_D0gamma_WN, Systematic::gammaWNBuPdf,
          Sign::same)),
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
      Bu2Dst0h_D0gamma_WN_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_WN_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0pi_D0gamma_WN,
          Systematic::gammaWNBuPartialPdf, Sign::positive)),
      pdfBuPartial_Bu2Dst0h_D0gamma_WN_(
          ("pdfBuPartial_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0gamma_WN_meanBuPartial(),
          *Bu2Dst0h_D0gamma_WN_sigmaBuPartial_),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_WN_thresholdDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_thresholdDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::misIdGammaWNPiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_aDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_aDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::misIdGammaWNPiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_bDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_bDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::misIdGammaWNPiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_cDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_cDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::misIdGammaWNPiPdfDelta, Sign::same)),
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
          Systematic::misIdGammaWNPiPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_sigmaBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_sigmaBu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::misIdGammaWNPiPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_a1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::misIdGammaWNPiPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_n1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::misIdGammaWNPiPdfBu, Sign::same)),
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
          Systematic::misIdGammaWNPiPdfBuPartial, Sign::same)),
      misId_Bu2Dst0h_D0gamma_WN_sigmaBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_WN_sigmaBu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0gamma_WN,
          Systematic::misIdGammaWNPiPdfBuPartial, Sign::same)),
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
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNDeltaPdf, Sign::none)),
      Bu2Dst0h_D0pi0_WN_bDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_bDelta", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNDeltaPdf, Sign::none)),
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
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::positive)),
      // Bu2Dst0h_D0pi0_WN_sigma1Bu_(Params::Get().CreateFixed(
      //     "Bu2Dst0h_D0pi0_WN_sigma1Bu", uniqueId_, Neutral::gamma,
      //     Bachelor::pi, 6.4774e+01, 1.23e+00, Systematic::pi0WNBuPdf,
      //     Sign::positive)),
      // Bu2Dst0h_D0pi0_WN_sigma1Bu_(Params::Get().CreateFloating(
      //     "Bu2Dst0h_D0pi0_WN_sigma1Bu", uniqueId_, Neutral::gamma,
      //     Bachelor::pi, Mode::Bu2Dst0pi_D0pi0_WN, 55, 75)),
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
          Bachelor::pi, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPartialPdf,
          Sign::positive)),
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
          Systematic::misIdPi0WNPiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_aDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_aDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::misIdPi0WNPiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_bDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_bDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::misIdPi0WNPiPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_cDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_cDelta", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::misIdPi0WNPiPdfDelta, Sign::same)),
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
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN, Systematic::misIdPi0WNPiPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_mean2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_mean2Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN, Systematic::misIdPi0WNPiPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_mean3Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_mean3Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN, Systematic::misIdPi0WNPiPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_sigma1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN, Systematic::misIdPi0WNPiPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_sigma2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_sigma2Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN, Systematic::misIdPi0WNPiPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_sigma3Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_sigma3Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN, Systematic::misIdPi0WNPiPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_a1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN, Systematic::misIdPi0WNPiPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_n1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN, Systematic::misIdPi0WNPiPdfBu,
          Sign::same)),
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
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN, Systematic::misIdPi0WNPiPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_fracPdf2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_fracPdf2Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN, Systematic::misIdPi0WNPiPdfBu,
          Sign::same)),
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
          Systematic::misIdPi0WNPiPdfBuPartial, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_sigmaBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::misIdPi0WNPiPdfBuPartial, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_a1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_a1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::misIdPi0WNPiPdfBuPartial, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_n1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_n1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0K_D0pi0_WN,
          Systematic::misIdPi0WNPiPdfBuPartial, Sign::same)),
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
          Mode::Bd2Dstpi, Systematic::Bd2DsthBuPdf, Sign::same)),
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
          Mode::Bd2Dstpi, Systematic::Bd2DsthBuPartialPdf, Sign::same)),
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
          "Bu2D0hst_sigma1Bu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2D0rho, Systematic::Bu2D0hstBuPdf, Sign::same)),
      // Bu2D0hst_sigma1Bu_(Params::Get().CreateFloating(
      //     "Bu2D0hst_sigma1Bu", uniqueId_, Neutral::gamma, Bachelor::pi,
      //     Mode::Bu2D0rho, 55, 75)),
      Bu2D0hst_sigma2Bu_(("Bu2D0hst_sigma2Bu_" +
                          ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         "@0*@1",
                         RooArgSet(*Bu2D0hst_sigma1Bu_,
                                   NeutralVars<Neutral::gamma>::Get(uniqueId_)
                                       .Bu2D0hst_sigmaRatio21Bu())),
      pdf1Bu_Bu2D0hst_(
          ("pdf1Bu_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0hst_mean1Bu(),
          *Bu2D0hst_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0hst_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0hst_n1Bu()),
      pdf2Bu_Bu2D0hst_(
          ("pdf2Bu_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0hst_mean2Bu(),
          Bu2D0hst_sigma2Bu_),
      pdfBu_Bu2D0hst_(new RooAddPdf(
          ("pdfBu_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2D0hst_, pdf2Bu_Bu2D0hst_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0hst_fracPdf1Bu())),
      Bu2D0hst_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2D0hst_sigmaBuPartial", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2D0rho, Systematic::Bu2D0hstBuPartialPdf, Sign::same)),
      pdfBuPartial_Bu2D0hst_(
          ("pdfBuPartial_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0hst_meanBuPartial(),
          *Bu2D0hst_sigmaBuPartial_),
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
          "Bu2Dst0hst_D0gamma_sigma1Bu", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0rho_D0gamma,
          Systematic::Bu2Dst0hst_D0gammaBuPdf, Sign::same)),
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
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
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
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
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
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0hst_D0gamma_, pdf2Bu_Bu2Dst0hst_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0hst_D0gamma_fracPdf1Bu())),
      Bu2Dst0hst_D0gamma_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0gamma_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0rho_D0gamma,
          Systematic::Bu2Dst0hst_D0gammaBuPartialPdf, Sign::same)),
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
          Mode::Bu2Dst0rho_D0pi0, Systematic::Bu2Dst0hst_D0pi0BuPdf,
          Sign::same)),
      pdfBu_Bu2Dst0hst_D0pi0_(
          ("pdfBu_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0hst_D0pi0_meanBu(),
          *Bu2Dst0hst_D0pi0_sigmaBu_),
      Bu2Dst0hst_D0pi0_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0hst_D0pi0_sigmaBuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0rho_D0pi0,
          Systematic::Bu2Dst0hst_D0pi0BuPartialPdf, Sign::same)),
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
      // -------------------- Bs2Dst0Kpi -------------------- //
      pdfPeakGamma1Delta_Bs2Dst0Kpi_(),
      pdfPeakGamma2Delta_Bs2Dst0Kpi_(),
      pdfPeakGammaDelta_Bs2Dst0Kpi_(),
      pdfPeakPi01Delta_Bs2Dst0Kpi_(),
      pdfPeakPi02Delta_Bs2Dst0Kpi_(),
      pdfPeakPi0Delta_Bs2Dst0Kpi_(),
      pdfDelta_Bs2Dst0Kpi_(),
      // -------------------- MIS-REC -------------------- //
      MisRec_sigmaLBu_(Params::Get().CreateFixed(
          "MisRec_sigmaLBu", uniqueId_, Neutral::gamma, Bachelor::pi,
          1.3446e+02, 1.27e+00, Systematic::misRecBuPdf, Sign::positive)),
      MisRec_sigmaRBu_(Params::Get().CreateFixed(
          "MisRec_sigmaRBu", uniqueId_, Neutral::gamma, Bachelor::pi,
          8.5469e+01, 5.55e-01, Systematic::misRecBuPdf, Sign::positive)),
      pdfBu_MisRec_(("pdfBu_MisRec_" +
                     ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId_).MisRec_meanBu(),
                    *MisRec_sigmaLBu_, *MisRec_sigmaRBu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_).MisRec_aLBu(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId_).MisRec_aRBu()),
      MisRec_sigmaLBuPartial_(Params::Get().CreateFixed(
          "MisRec_sigmaLBuPartial", uniqueId_, Neutral::gamma, Bachelor::pi,
          1.1613e+02, 1.29e+00, Systematic::misRecBuPartialPdf,
          Sign::positive)),
      MisRec_sigmaRBuPartial_(Params::Get().CreateFixed(
          "MisRec_sigmaRBuPartial", uniqueId_, Neutral::gamma, Bachelor::pi,
          4.5697e+01, 5.07e-01, Systematic::misRecBuPartialPdf,
          Sign::positive)),
      pdfBuPartial_MisRec_(
          ("pdfBuPartial_MisRec_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).MisRec_meanBuPartial(),
          *MisRec_sigmaLBuPartial_, *MisRec_sigmaRBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).MisRec_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).MisRec_aRBuPartial()),
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
                        ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                           .c_str(),
                       // "", 8.8989e+01, 10, 150),
                       // Fixed from data
                       "", 1.1076e+02),
      Bu2D0h_sigmaRBu_(("Bu2D0h_sigmaRBu_" +
                        ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                           .c_str(),
                       // "", 7.5978e+01, 10, 150),
                       // Fixed from data
                       "", 7.2807e+01),
      pdfBu_Bu2D0h_(("pdfBu_Bu2D0h_" +
                     ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0h_meanBu(),
                    Bu2D0h_sigmaLBu_, Bu2D0h_sigmaRBu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0h_aLBu(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0h_aRBu()),
      Bu2D0h_sigmaLBuPartial_(
          ("Bu2D0h_sigmaLBuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          // "", 4.8679e+01, 10, 90),
          // Fixed from data
          "", 5.8546e+01),
      Bu2D0h_sigmaRBuPartial_(
          ("Bu2D0h_sigmaRBuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          // "", 3.5437e+01, 10, 60),
          // Fixed from data
          "", 3.2674e+01),
      pdfBuPartial_Bu2D0h_(
          ("pdfBuPartial_Bu2D0h_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0h_meanBuPartial(),
          Bu2D0h_sigmaLBuPartial_, Bu2D0h_sigmaRBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0h_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2D0h_aRBuPartial()),
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
          "PartRec_D0pi0_sigmaLBu", uniqueId_, Neutral::gamma, Bachelor::pi,
          8.3682e+01, 3.46e+00, Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0pi0_sigmaRBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_sigmaRBu", uniqueId_, Neutral::gamma, Bachelor::pi,
          9.1998e+01, 3.41e+00, Systematic::partRecBuPdf, Sign::positive)),
      pdfBu_PartRec_D0pi0_(
          ("pdfBu_PartRec_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_D0pi0_meanBu(),
          *PartRec_D0pi0_sigmaLBu_, *PartRec_D0pi0_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_D0pi0_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_D0pi0_aRBu()),
      PartRec_D0gamma_sigmaLBu_(Params::Get().CreateFixed(
          "PartRec_D0gamma_sigmaLBu", uniqueId_, Neutral::gamma, Bachelor::pi,
          3.6387e+01, 4.42e+00, Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0gamma_sigmaRBu_(Params::Get().CreateFixed(
          "PartRec_D0gamma_sigmaRBu", uniqueId_, Neutral::gamma, Bachelor::pi,
          4.4390e+01, 4.55e+00, Systematic::partRecBuPdf, Sign::positive)),
      pdfBu_PartRec_D0gamma_(
          ("pdfBu_PartRec_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_D0gamma_meanBu(),
          *PartRec_D0gamma_sigmaLBu_, *PartRec_D0gamma_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_D0gamma_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_D0gamma_aRBu()),
      pdfBu_PartRec_(new RooAddPdf(
          ("pdfBu_PartRec_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdfBu_PartRec_D0pi0_, pdfBu_PartRec_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_frac_D0pi0())),
      PartRec_sigmaLBuPartial_(Params::Get().CreateFixed(
          "PartRec_sigmaLBuPartial", uniqueId_, Neutral::gamma, Bachelor::pi,
          4.7853e+01, 2.41e+00, Systematic::partRecBuPartialPdf,
          Sign::positive)),
      PartRec_sigmaRBuPartial_(Params::Get().CreateFixed(
          "PartRec_sigmaRBuPartial", uniqueId_, Neutral::gamma, Bachelor::pi,
          3.3489e+01, 1.46e+00, Systematic::partRecBuPartialPdf,
          Sign::positive)),
      pdfBuPartial_PartRec_(
          ("pdfBuPartial_PartRec_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_meanBuPartial(),
          *PartRec_sigmaLBuPartial_, *PartRec_sigmaRBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).PartRec_aRBuPartial()),
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
      orEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::positive)),
      orEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi, Efficiency::orEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::positive)),
      orEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::positive)),
      orEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "orEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::positive)),
      orEffBd2Dsth_(Params::Get().CreateFixed(
          "orEffBd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::orEffErr,
                        false),
          Systematic::NA, Sign::positive)),
      orEffBu2D0hst_(Params::Get().CreateFixed(
          "orEffBu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::orEffErr,
                        false),
          Systematic::NA, Sign::positive)),
      orEffBu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "orEffBu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::orEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::positive)),
      orEffBu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "orEffBu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi, Efficiency::orEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                        Efficiency::orEffErr, false),
          Systematic::NA, Sign::positive)),
      buEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::positive)),
      buEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::positive)),
      buEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::positive)),
      buEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::positive)),
      buEffBd2Dsth_(Params::Get().CreateFixed(
          "buEffBd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::buEffErr,
                        false),
          Systematic::NA, Sign::positive)),
      buEffBu2D0hst_(Params::Get().CreateFixed(
          "buEffBu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::buEffErr,
                        false),
          Systematic::NA, Sign::positive)),
      buEffBu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "buEffBu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::positive)),
      buEffBu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "buEffBu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::positive)),
      deltaEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::positive)),
      deltaEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::positive)),
      deltaEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::positive)),
      deltaEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::positive)),
      deltaEffBd2Dsth_(Params::Get().CreateFixed(
          "deltaEffBd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::deltaEff,
                        false),
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::deltaEffErr,
                        false),
          Systematic::NA, Sign::positive)),
      deltaEffBu2D0hst_(Params::Get().CreateFixed(
          "deltaEffBu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::deltaEff,
                        false),
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::deltaEffErr,
                        false),
          Systematic::NA, Sign::positive)),
      deltaEffBu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::positive)),
      deltaEffBu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::positive)),
      buPartialEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::positive)),
      buPartialEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::positive)),
      buPartialEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma_WN, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::positive)),
      buPartialEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::positive)),
      buPartialEffBd2Dsth_(Params::Get().CreateFixed(
          "buPartialEffBd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi, Efficiency::buPartialEff,
                        false),
          ReturnBoxEffs(Mode::Bd2Dstpi, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::positive)),
      buPartialEffBu2D0hst_(Params::Get().CreateFixed(
          "buPartialEffBu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi, Efficiency::buPartialEff,
                        false),
          ReturnBoxEffs(Mode::Bu2D0rho, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::positive)),
      buPartialEffBu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::positive)),
      buPartialEffBu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::positive)),
      // -------------------- Mis-ID BoxEffs ------------------- //
      orEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi, Efficiency::orEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::positive)),
      orEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi, Efficiency::orEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::positive)),
      orEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::positive)),
      orEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::positive)),
      orEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "orEffMisId_Bd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::orEffErr,
                        true),
          Systematic::NA, Sign::same)),
      orEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "orEffMisId_Bu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::orEffErr,
                        true),
          Systematic::NA, Sign::same)),
      orEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::orEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::same)),
      orEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "orEffMisId_Bu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi, Efficiency::orEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi,
                        Efficiency::orEffErr, true),
          Systematic::NA, Sign::same)),
      buEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi, Efficiency::buEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::positive)),
      buEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi, Efficiency::buEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::positive)),
      buEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::positive)),
      buEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::positive)),
      buEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "buEffMisId_Bd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::buEffErr,
                        true),
          Systematic::NA, Sign::same)),
      buEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "buEffMisId_Bu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::buEffErr,
                        true),
          Systematic::NA, Sign::same)),
      buEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::same)),
      buEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi, Efficiency::buEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::same)),
      deltaEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::positive)),
      deltaEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::positive)),
      deltaEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::positive)),
      deltaEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::positive)),
      deltaEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "deltaEffMisId_Bd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::deltaEff,
                        true),
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::deltaEffErr,
                        true),
          Systematic::NA, Sign::same)),
      deltaEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2D0hst_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::deltaEff,
                        true),
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::deltaEffErr,
                        true),
          Systematic::NA, Sign::same)),
      deltaEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::same)),
      deltaEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::same)),
      buPartialEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::NA, Sign::positive)),
      buPartialEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::NA, Sign::positive)),
      buPartialEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::NA, Sign::positive)),
      buPartialEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::NA, Sign::positive)),
      buPartialEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bd2Dsth_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi, Efficiency::buPartialEff,
                        true),
          ReturnBoxEffs(Mode::Bd2DstK, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::NA, Sign::same)),
      buPartialEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2D0hst_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi, Efficiency::buPartialEff,
                        true),
          ReturnBoxEffs(Mode::Bu2D0Kst, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::NA, Sign::same)),
      buPartialEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0hst_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::NA, Sign::same)),
      buPartialEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0hst_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0Kst_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::NA, Sign::same)),
      // -------------------- MC Efficiencies -------------------- //
      mcEff_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEff_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEff_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEff_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEff_Bd2Dsth_(Params::Get().CreateFixed(
          "mcEff_Bd2Dsth", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bd2Dstpi, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bd2Dstpi, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEff_Bu2D0hst_(Params::Get().CreateFixed(
          "mcEff_Bu2D0hst", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2D0rho, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2D0rho, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEff_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0hst_D0gamma", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEff_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0hst_D0pi0", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEff_MisRec_(Params::Get().CreateFixed(
          "mcEff_MisRec", uniqueId_, Neutral::gamma, Bachelor::pi, 1.0, 0.0,
          Systematic::NA, Sign::positive)),
      mcEff_Bu2D0h_(Params::Get().CreateFixed(
          "mcEff_Bu2D0h", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2D0pi, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2D0pi, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEff_PartRec_(Params::Get().CreateFixed(
          "mcEff_PartRec", uniqueId_, Neutral::gamma, Bachelor::pi, 1.0, 0.0,
          Systematic::NA, Sign::positive)),
      // -------------------- MC misId Efficiencies -------------------- //
      mcEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEffMisId_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEffMisId_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma_WN, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma_WN, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0_WN, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0_WN, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEffMisId_Bd2Dsth_(Params::Get().CreateFixed(
          "mcEffMisId_Bd2Dsth", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bd2DstK, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bd2DstK, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEffMisId_Bu2D0hst_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2D0hst", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2D0Kst, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2D0Kst, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEffMisId_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0hst_D0gamma", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0Kst_D0gamma, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0Kst_D0gamma, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
      mcEffMisId_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "mcEffMisId_Bu2Dst0hst_D0pi0", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0Kst_D0pi0, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0Kst_D0pi0, Neutral::gamma, Bachelor::pi,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::same)),
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
      Bu2Dst0hst_fracD0pi0_(
          ("Bu2Dst0hst_fracD0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*(@1*@2*@5)/(@1*@2*@5 + @3*@4*@6)",
          RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId_)
                         .Bu2Dst0hst_floatingFracD0pi0(),
                     *orEffBu2Dst0hst_D0pi0_, *mcEff_Bu2Dst0hst_D0pi0_,
                     *orEffBu2Dst0hst_D0gamma_, *mcEff_Bu2Dst0hst_D0gamma_,
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0(),
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma())),
      Bu2Dst0hst_fracD0pi0_Bu_(
          ("Bu2Dst0hst_fracD0pi0_Bu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*(@1*@2*@3*@7)/(@1*@2*@3*@7 + @4*@5*@6*@8)",
          RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId_)
                         .Bu2Dst0hst_floatingFracD0pi0(),
                     *buEffBu2Dst0hst_D0pi0_, *orEffBu2Dst0hst_D0pi0_,
                     *mcEff_Bu2Dst0hst_D0pi0_, *buEffBu2Dst0hst_D0gamma_,
                     *orEffBu2Dst0hst_D0gamma_, *mcEff_Bu2Dst0hst_D0gamma_,
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0(),
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma())),
      Bu2Dst0hst_fracD0pi0_Delta_(
          ("Bu2Dst0hst_fracD0pi0_Delta_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*(@1*@2*@3*@7)/(@1*@2*@3*@7 + @4*@5*@6*@8)",
          RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId_)
                         .Bu2Dst0hst_floatingFracD0pi0(),
                     *deltaEffBu2Dst0hst_D0pi0_, *orEffBu2Dst0hst_D0pi0_,
                     *mcEff_Bu2Dst0hst_D0pi0_, *deltaEffBu2Dst0hst_D0gamma_,
                     *orEffBu2Dst0hst_D0gamma_, *mcEff_Bu2Dst0hst_D0gamma_,
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0(),
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma())),
      Bu2Dst0hst_fracD0pi0_BuPartial_(
          ("Bu2Dst0hst_fracD0pi0_BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*(@1*@2*@3*@7)/(@1*@2*@3*@7 + @4*@5*@6*@8)",
          RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId_)
                         .Bu2Dst0hst_floatingFracD0pi0(),
                     *buPartialEffBu2Dst0hst_D0pi0_, *orEffBu2Dst0hst_D0pi0_,
                     *mcEff_Bu2Dst0hst_D0pi0_, *buPartialEffBu2Dst0hst_D0gamma_,
                     *orEffBu2Dst0hst_D0gamma_, *mcEff_Bu2Dst0hst_D0gamma_,
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0(),
                     GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma())),
      pdfBu_Bu2Dst0hst_(
          ("pdfBu_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdfBu_Bu2Dst0hst_D0pi0_, *pdfBu_Bu2Dst0hst_D0gamma_),
          Bu2Dst0hst_fracD0pi0_Bu_),
      pdfDelta_Bu2Dst0hst_(
          ("pdfDelta_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "",
          RooArgSet(NeutralVars<Neutral::gamma>::Get(uniqueId)
                        .pdfDelta_Bu2Dst0hst_D0pi0(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                        .pdfDelta_Bu2Dst0hst_D0gamma()),
          Bu2Dst0hst_fracD0pi0_Delta_),
      pdfBuPartial_Bu2Dst0hst_(
          ("pdfBuPartial_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "",
          RooArgSet(pdfBuPartial_Bu2Dst0hst_D0pi0_,
                    pdfBuPartial_Bu2Dst0hst_D0gamma_),
          Bu2Dst0hst_fracD0pi0_BuPartial_),
      orEffBu2Dst0hst_(
          ("orEffBu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0hst_fracD0pi0_, *orEffBu2Dst0hst_D0pi0_,
                     *orEffBu2Dst0hst_D0gamma_)),
      buEffBu2Dst0hst_(
          ("buEffBu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0hst_fracD0pi0_, *buEffBu2Dst0hst_D0pi0_,
                     *buEffBu2Dst0hst_D0gamma_)),
      deltaEffBu2Dst0hst_(
          ("deltaEffBu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0hst_fracD0pi0_, *deltaEffBu2Dst0hst_D0pi0_,
                     *deltaEffBu2Dst0hst_D0gamma_)),
      buPartialEffBu2Dst0hst_(
          ("buPartialEffBu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0hst_fracD0pi0_, *buPartialEffBu2Dst0hst_D0pi0_,
                     *buPartialEffBu2Dst0hst_D0gamma_)),
      mcEff_Bu2Dst0hst_(
          ("mcEff_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0hst_fracD0pi0_, *mcEff_Bu2Dst0hst_D0pi0_,
                     *mcEff_Bu2Dst0hst_D0gamma_)),
      Bu2Dst0hst_misId_fracD0pi0_(
          ("Bu2Dst0hst_misId_fracD0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*(@1*@2*@5)/(@1*@2*@5 + @3*@4*@6)",
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0hst_floatingFracD0pi0(),
              *orEffMisId_Bu2Dst0hst_D0pi0_, *mcEffMisId_Bu2Dst0hst_D0pi0_,
              *orEffMisId_Bu2Dst0hst_D0gamma_, *mcEffMisId_Bu2Dst0hst_D0gamma_,
              GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0(),
              GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma())),
      Bu2Dst0hst_misId_fracD0pi0_Bu_(
          ("Bu2Dst0hst_misId_fracD0pi0_Bu_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*(@1*@2*@3*@7)/(@1*@2*@3*@7 + @4*@5*@6*@8)",
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0hst_floatingFracD0pi0(),
              *buEffMisId_Bu2Dst0hst_D0pi0_, *orEffMisId_Bu2Dst0hst_D0pi0_,
              *mcEffMisId_Bu2Dst0hst_D0pi0_, *buEffMisId_Bu2Dst0hst_D0gamma_,
              *orEffMisId_Bu2Dst0hst_D0gamma_, *mcEffMisId_Bu2Dst0hst_D0gamma_,
              GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0(),
              GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma())),
      Bu2Dst0hst_misId_fracD0pi0_Delta_(
          ("Bu2Dst0hst_misId_fracD0pi0_Delta_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*(@1*@2*@3*@7)/(@1*@2*@3*@7 + @4*@5*@6*@8)",
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0hst_floatingFracD0pi0(),
              *deltaEffMisId_Bu2Dst0hst_D0pi0_, *orEffMisId_Bu2Dst0hst_D0pi0_,
              *mcEffMisId_Bu2Dst0hst_D0pi0_, *deltaEffMisId_Bu2Dst0hst_D0gamma_,
              *orEffMisId_Bu2Dst0hst_D0gamma_, *mcEffMisId_Bu2Dst0hst_D0gamma_,
              GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0(),
              GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma())),
      Bu2Dst0hst_misId_fracD0pi0_BuPartial_(
          ("Bu2Dst0hst_misId_fracD0pi0_BuPartial_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*(@1*@2*@3*@7)/(@1*@2*@3*@7 + @4*@5*@6*@8)",
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId_)
                  .Bu2Dst0hst_floatingFracD0pi0(),
              *buPartialEffMisId_Bu2Dst0hst_D0pi0_,
              *orEffMisId_Bu2Dst0hst_D0pi0_, *mcEffMisId_Bu2Dst0hst_D0pi0_,
              *buPartialEffMisId_Bu2Dst0hst_D0gamma_,
              *orEffMisId_Bu2Dst0hst_D0gamma_, *mcEffMisId_Bu2Dst0hst_D0gamma_,
              GlobalVars::Get(uniqueId_).kBF_Dst02D0pi0(),
              GlobalVars::Get(uniqueId_).kBF_Dst02D0gamma())),
      pdfBu_misId_Bu2Dst0hst_(),
      pdfDelta_misId_Bu2Dst0hst_(),
      pdfBuPartial_misId_Bu2Dst0hst_(),
      orEffMisId_Bu2Dst0hst_(
          ("orEffMisId_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0hst_misId_fracD0pi0_, *orEffMisId_Bu2Dst0hst_D0pi0_,
                     *orEffMisId_Bu2Dst0hst_D0gamma_)),
      buEffMisId_Bu2Dst0hst_(
          ("buEffMisId_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0hst_misId_fracD0pi0_, *buEffMisId_Bu2Dst0hst_D0pi0_,
                     *buEffMisId_Bu2Dst0hst_D0gamma_)),
      deltaEffMisId_Bu2Dst0hst_(
          ("deltaEffMisId_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0hst_misId_fracD0pi0_,
                     *deltaEffMisId_Bu2Dst0hst_D0pi0_,
                     *deltaEffMisId_Bu2Dst0hst_D0gamma_)),
      buPartialEffMisId_Bu2Dst0hst_(
          ("buPartialEffMisId_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0hst_misId_fracD0pi0_,
                     *buPartialEffMisId_Bu2Dst0hst_D0pi0_,
                     *buPartialEffMisId_Bu2Dst0hst_D0gamma_)),
      mcEffMisId_Bu2Dst0hst_(
          ("mcEffMisId_Bu2Dst0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1+(1-@0)*@2",
          RooArgList(Bu2Dst0hst_fracD0pi0_, *mcEffMisId_Bu2Dst0hst_D0pi0_,
                     *mcEffMisId_Bu2Dst0hst_D0gamma_)) {}
