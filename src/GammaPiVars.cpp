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
      Bu2Dst0h_D0pi0_sigmaBu_(nullptr),
      pdf1Bu_Bu2Dst0h_D0pi0_(),
      pdf2Bu_Bu2Dst0h_D0pi0_(),
      pdfBu_Bu2Dst0h_D0pi0_(new RooCBShape(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_meanBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_sigmaBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_n1Bu())),
      Bu2Dst0h_D0pi0_sigma1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_sigma1BuPartial", uniqueId_, Neutral::gamma,
          Bachelor::pi, Mode::Bu2Dst0pi_D0pi0, Systematic::pi0BuPartialSigma1,
          Sign::positive)),
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
      // -------------------- Bu2Dst0h_D0pi0_WN -------------------- //
      Bu2Dst0h_D0pi0_WN_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_WN_sigmaBu", uniqueId_, Neutral::gamma, Bachelor::pi,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::pi0WNBuPdf, Sign::same)),
      pdf1Bu_Bu2Dst0h_D0pi0_WN_(),
      pdf2Bu_Bu2Dst0h_D0pi0_WN_(),
      pdfBu_Bu2Dst0h_D0pi0_WN_(new RooCBShape(
          ("pdfBu_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_meanBu(),
          *Bu2Dst0h_D0pi0_WN_sigmaBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_n1Bu())),
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
      buEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::positive)),
      buEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::buEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::positive)),
      deltaEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::positive)),
      deltaEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::positive)),
      buPartialEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::positive)),
      buPartialEffBu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "buPartialEffBu2Dst0h_D0gamma_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                        Efficiency::buPartialEffErr, false),
          Systematic::NA, Sign::positive)),
      // -------------------- Mis-ID BoxEffs ------------------- //
      buEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi, Efficiency::buEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::positive)),
      deltaEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::positive)),
      buPartialEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buPartialEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::gamma,
          Bachelor::pi,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                        Efficiency::buPartialEffErr, true),
          Systematic::NA, Sign::positive)),
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
          "mcEff_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma, Neutral::gamma, Bachelor::pi,
                       true),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma, Neutral::gamma, Bachelor::pi,
                       false),
          Systematic::mcEffs, Sign::positive)),
      mcEff_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::gamma, Bachelor::pi,
                       true),
          ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, Neutral::gamma, Bachelor::pi,
                       false),
          Systematic::mcEffs, Sign::positive)),
      mcEff_MisRec_(Params::Get().CreateFixed(
          "mcEff_MisRec", uniqueId_, Neutral::gamma, Bachelor::pi, 1.0, 0.0,
          Systematic::NA, Sign::positive)),
      mcEff_Bu2D0h_(Params::Get().CreateFixed(
          "mcEff_Bu2D0h", uniqueId_, Neutral::gamma, Bachelor::pi,
          ReturnMCEffs(Mode::Bu2D0pi, Neutral::gamma, Bachelor::pi, true),
          ReturnMCEffs(Mode::Bu2D0pi, Neutral::gamma, Bachelor::pi, false),
          Systematic::mcEffs, Sign::positive)),
      mcEff_PartRec_(Params::Get().CreateFixed(
          "mcEff_PartRec", uniqueId_, Neutral::gamma, Bachelor::pi, 1.0, 0.0,
          Systematic::NA, Sign::positive)),
      mcEff_Bs2Dst0Kpi_(Params::Get().CreateFixed(
          "mcEff_Bs2Dst0Kpi", uniqueId_, Neutral::gamma, Bachelor::pi, 1.0, 0.0,
          Systematic::NA, Sign::positive)),
      mcEff_Bs2D0Kpi_(Params::Get().CreateFixed(
          "mcEff_Bs2D0Kpi", uniqueId_, Neutral::gamma, Bachelor::pi, 1.0, 0.0,
          Systematic::NA, Sign::positive)),
      // -------------------- CP Observables -------------------- //
      A_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_CP_Bu2Dst0h_D0gamma_(nullptr),
      A_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_ADS_Bu2Dst0h_D0gamma_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_(nullptr) {
  if (Configuration::Get().blindFit() == true) {
    A_CP_Bu2Dst0h_D0gamma_Blind_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0gamma_Blind", uniqueId_, Neutral::gamma,
            Bachelor::pi, -0.003, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_Blind_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0pi0_Blind", uniqueId_, Neutral::gamma,
            Bachelor::pi, 0.025, -1, 1));
    A_CP_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooUnblindUniform>(
        MakeBlind(("A_CP_Bu2Dst0h_D0gamma_" +
                   ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                      .c_str(),
                  0.03, *A_CP_Bu2Dst0h_D0gamma_Blind_));
    A_CP_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooUnblindUniform>(
        MakeBlind(("A_CP_Bu2Dst0h_D0pi0_" +
                   ComposeName(uniqueId_, Neutral::gamma, Bachelor::pi))
                      .c_str(),
                  0.03, *A_CP_Bu2Dst0h_D0pi0_Blind_));
  } else {
    A_CP_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma, Bachelor::pi,
            -0.003, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma, Bachelor::pi,
            0.025, -1, 1));
  }
  if (Configuration::Get().splitByCharge() == true) {
    R_ADS_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::gamma, Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_",
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::pi,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma(),
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::pi,
                                      Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma()));
    R_ADS_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::gamma, Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_",
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::pi,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0(),
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::pi,
                                      Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
  } else {
    R_ADS_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::gamma, Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_",
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::pi,
                                      Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma()));
    R_ADS_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::gamma, Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_",
            NeutralBachelorChargeVars<Neutral::gamma, Bachelor::pi,
                                      Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
  }

  std::map<std::string, double> mapMisId_Bu2Dst0h_D0gamma;
  std::map<std::string, double> mapMisId_Bu2Dst0h_D0pi0;

  ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                                     mapMisId_Bu2Dst0h_D0gamma, true);
  ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                                     mapMisId_Bu2Dst0h_D0pi0, true);

  buDeltaCutEffMisId_Bu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma,
          mapMisId_Bu2Dst0h_D0gamma["buDeltaCutEff"],
          mapMisId_Bu2Dst0h_D0gamma["buDeltaCutEffErr"],
          Systematic::buDeltaMisIdCutEffs, Sign::positive));
  buDeltaCutEffMisId_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma,
          mapMisId_Bu2Dst0h_D0pi0["buDeltaCutEff"],
          mapMisId_Bu2Dst0h_D0pi0["buDeltaCutEffErr"],
          Systematic::buDeltaMisIdCutEffs, Sign::positive));

  deltaCutEffMisId_Bu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma,
          mapMisId_Bu2Dst0h_D0gamma["deltaCutEff"],
          mapMisId_Bu2Dst0h_D0gamma["deltaCutEffErr"],
          Systematic::deltaMisIdCutEffs, Sign::positive));
  deltaCutEffMisId_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma,
          mapMisId_Bu2Dst0h_D0pi0["deltaCutEff"],
          mapMisId_Bu2Dst0h_D0pi0["deltaCutEffErr"],
          Systematic::deltaMisIdCutEffs, Sign::positive));

  if (Configuration::Get().fitBuPartial() == true) {
    deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffMisId_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma,
            mapMisId_Bu2Dst0h_D0pi0["deltaPartialCutEff"],
            mapMisId_Bu2Dst0h_D0pi0["deltaPartialCutEffErr"],
            Systematic::deltaPartialMisIdCutEffs, Sign::positive));
  }
}
