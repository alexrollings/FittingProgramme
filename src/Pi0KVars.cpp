#include "NeutralBachelorVars.h"
#include "Params.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- PDF SHAPES -------------------- //
    // -------------------- Bu2Dst0h_D0pi0 -------------------- //
    : uniqueId_(uniqueId),
      Bu2Dst0h_D0pi0_sigmaBu_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_sigmaBu_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_sigmaBu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_KpiSigmaBu()))),
      pdf1Bu_Bu2Dst0h_D0pi0_(
          ("pdf1Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0pi0_(
          ("pdf2Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_a2Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_n2Bu()),
      pdfBu_Bu2Dst0h_D0pi0_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
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
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfDelta,
          Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigmaDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigmaDelta", uniqueId_, Neutral::pi0,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfDelta,
          Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::pi0, Bachelor::k,
          Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_n1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1Delta", uniqueId_, Neutral::pi0, Bachelor::k,
          Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfDelta,
          Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a2Delta", uniqueId_, Neutral::pi0, Bachelor::k,
          Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n2Delta", uniqueId_, Neutral::pi0, Bachelor::k,
          Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfDelta,
          Sign::positive)),
      pdf1Delta_misId_Bu2Dst0h_D0pi0_(
          ("pdf1Delta_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0pi0_meanDelta_, *misId_Bu2Dst0h_D0pi0_sigmaDelta_,
          *misId_Bu2Dst0h_D0pi0_a1Delta_, *misId_Bu2Dst0h_D0pi0_n1Delta_),
      pdf2Delta_misId_Bu2Dst0h_D0pi0_(
          ("pdf2Delta_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0pi0_meanDelta_, *misId_Bu2Dst0h_D0pi0_sigmaDelta_,
          *misId_Bu2Dst0h_D0pi0_a2Delta_, *misId_Bu2Dst0h_D0pi0_n2Delta_),
      misId_Bu2Dst0h_D0pi0_fracPdf1Delta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_fracPdf1Delta", uniqueId_, Neutral::pi0,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfDelta,
          Sign::positive)),
      pdfDelta_misId_Bu2Dst0h_D0pi0_(
          new RooAddPdf(("pdfDelta_misId_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
                            .c_str(),
                        "",
                        RooArgSet(pdf1Delta_misId_Bu2Dst0h_D0pi0_,
                                  pdf2Delta_misId_Bu2Dst0h_D0pi0_),
                        *misId_Bu2Dst0h_D0pi0_fracPdf1Delta_)),
      misId_Bu2Dst0h_D0pi0_mean1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_mean1Bu", uniqueId_, Neutral::pi0, Bachelor::k,
          Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_mean2Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma1Bu", uniqueId_, Neutral::pi0, Bachelor::k,
          Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigma2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma2Bu", uniqueId_, Neutral::pi0, Bachelor::k,
          Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1Bu", uniqueId_, Neutral::pi0, Bachelor::k,
          Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1Bu", uniqueId_, Neutral::pi0, Bachelor::k,
          Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a2Bu", uniqueId_, Neutral::pi0, Bachelor::k,
          Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0pi0_n2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n2Bu", uniqueId_, Neutral::pi0, Bachelor::k,
          Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBu, Sign::positive)),
      pdf1Bu_misId_Bu2Dst0h_D0pi0_(new RooCBShape(
          ("pdf1Bu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_mean1Bu_, *misId_Bu2Dst0h_D0pi0_sigma1Bu_,
          *misId_Bu2Dst0h_D0pi0_a1Bu_, *misId_Bu2Dst0h_D0pi0_n1Bu_)),
      pdf2Bu_misId_Bu2Dst0h_D0pi0_(
          ("pdf2Bu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_mean1Bu_, *misId_Bu2Dst0h_D0pi0_sigma2Bu_,
          *misId_Bu2Dst0h_D0pi0_a2Bu_, *misId_Bu2Dst0h_D0pi0_n2Bu_),
      misId_Bu2Dst0h_D0pi0_fracPdf1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_fracPdf1Bu", uniqueId_, Neutral::pi0,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0, Systematic::misIdPi0KPdfBu,
          Sign::positive)),
      pdfBu_misId_Bu2Dst0h_D0pi0_(
          new RooAddPdf(("pdfBu_misId_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
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
      Bu2Dst0h_D0pi0_WN_sigmaBu_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_WN_sigmaBu_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_WN_sigmaBu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId_)
                  .Bu2Dst0h_D0pi0_WN_KpiSigmaBu()))),
      pdf1Bu_Bu2Dst0h_D0pi0_WN_(
          ("pdf1Bu_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_meanBu(),
          *Bu2Dst0h_D0pi0_WN_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0pi0_WN_(
          ("pdf2Bu_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_meanBu(),
          *Bu2Dst0h_D0pi0_WN_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_a2Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_WN_n2Bu()),
      pdfBu_Bu2Dst0h_D0pi0_WN_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0h_D0pi0_WN_, pdf2Bu_Bu2Dst0h_D0pi0_WN_),
          NeutralVars<Neutral::pi0>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_WN_fracPdf1Bu())),
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
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN,
          Systematic::misIdPi0WNKPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_aDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_aDelta", uniqueId_, Neutral::pi0,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN,
          Systematic::misIdPi0WNKPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_bDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_bDelta", uniqueId_, Neutral::pi0,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN,
          Systematic::misIdPi0WNKPdfDelta, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_cDelta_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_cDelta", uniqueId_, Neutral::pi0,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN,
          Systematic::misIdPi0WNKPdfDelta, Sign::same)),
      pdfDelta_misId_Bu2Dst0h_D0pi0_WN_(
          ("pdfDelta_misId_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *misId_Bu2Dst0h_D0pi0_WN_thresholdDelta_,
          *misId_Bu2Dst0h_D0pi0_WN_cDelta_, *misId_Bu2Dst0h_D0pi0_WN_aDelta_,
          *misId_Bu2Dst0h_D0pi0_WN_bDelta_),
      misId_Bu2Dst0h_D0pi0_WN_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_meanBu", uniqueId_, Neutral::pi0,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_sigmaBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_sigmaBu", uniqueId_, Neutral::pi0,
          Bachelor::k, Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu,
          Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_a1Bu", uniqueId_, Neutral::pi0, Bachelor::k,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu, Sign::same)),
      misId_Bu2Dst0h_D0pi0_WN_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_WN_n1Bu", uniqueId_, Neutral::pi0, Bachelor::k,
          Mode::Bu2Dst0pi_D0pi0_WN, Systematic::misIdPi0WNKPdfBu, Sign::same)),
      pdfBu_misId_Bu2Dst0h_D0pi0_WN_(new RooCBShape(
          ("pdfBu_misId_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_WN_meanBu_, *misId_Bu2Dst0h_D0pi0_WN_sigmaBu_,
          *misId_Bu2Dst0h_D0pi0_WN_a1Bu_, *misId_Bu2Dst0h_D0pi0_WN_n1Bu_)),
      misId_Bu2Dst0h_D0pi0_WN_meanBuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_sigmaBuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_a1BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_WN_n1BuPartial_(nullptr),
      pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN_(),
      // -------------------- Bu2Dst0h_D0gamma_WN -------------------- //
      Bu2Dst0h_D0gamma_WN_sigma1Bu_(new RooFormulaVar(
          ("Bu2Dst0h_D0gamma_WN_sigma1Bu_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId_)
                  .Bu2Dst0h_D0gamma_WN_sigma1Bu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId_)
                  .Bu2Dst0h_D0gamma_WN_KpiSigmaBu()))),
      Bu2Dst0h_D0gamma_WN_sigma2Bu_(),
      pdf1Bu_Bu2Dst0h_D0gamma_WN_(),
      pdf2Bu_Bu2Dst0h_D0gamma_WN_(),
      pdfBu_Bu2Dst0h_D0gamma_WN_(
          new RooGaussian(("pdfBu_Bu2Dst0h_D0gamma_WN_" +
                           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
                              .c_str(),
                          "", Configuration::Get().buDeltaMass(),
                          NeutralVars<Neutral::pi0>::Get(uniqueId_)
                              .Bu2Dst0h_D0gamma_WN_mean1Bu(),
                          *Bu2Dst0h_D0gamma_WN_sigma1Bu_)),
      Bu2Dst0h_D0gamma_WN_sigmaBuPartial_(nullptr),
      pdfBuPartial_Bu2Dst0h_D0gamma_WN_(),
      // -------------------- MIS-REC -------------------- //
      MisRec_sigmaLBu_(Params::Get().CreateFixed(
          "MisRec_sigmaLBu", uniqueId_, Neutral::pi0, Bachelor::k, 5.7157e+01,
          6.09e+00, Systematic::misRecBuPdf, Sign::positive)),
      // MisRec_sigmaLBu_(Params::Get().CreateFloating(
      //     "MisRec_sigmaLBu", uniqueId_, Neutral::pi0,
      //     Bachelor::k, 5.7157e+01, 30, 70)),
      MisRec_sigmaRBu_(Params::Get().CreateFixed(
          "MisRec_sigmaRBu", uniqueId_, Neutral::pi0, Bachelor::k, 5.5962e+01,
          4.14e+00, Systematic::misRecBuPdf, Sign::positive)),
      // MisRec_sigmaRBu_(Params::Get().CreateFloating(
      //     "MisRec_sigmaRBu", uniqueId_, Neutral::pi0,
      //     Bachelor::k, 5.5962e+01, 30, 70)),
      pdfBu_MisRec_(
          ("pdfBu_MisRec_" + ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
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
      misId_MisRec_mean1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_mean1Bu", uniqueId_, Neutral::pi0, Bachelor::k,
          5.3333e+03, 7.09e-01, Systematic::misIdMisRecKPdfBu, Sign::positive)),
      misId_MisRec_mean2Bu_(nullptr),
      misId_MisRec_sigma1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_sigma1Bu", uniqueId_, Neutral::pi0, Bachelor::k,
          2.6027e+01, 6.06e-01, Systematic::misIdMisRecKPdfBu, Sign::positive)),
      misId_MisRec_sigma2Bu_(Params::Get().CreateFixed(
          "misId_MisRec_sigma2Bu", uniqueId_, Neutral::pi0, Bachelor::k,
          6.2136e+01, 8.88e-01, Systematic::misIdMisRecKPdfBu, Sign::positive)),
      misId_MisRec_a1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_a1Bu", uniqueId_, Neutral::pi0, Bachelor::k, 2.5413e-01,
          6.21e-03, Systematic::misIdMisRecKPdfBu, Sign::positive)),
      misId_MisRec_a2Bu_(nullptr),
      misId_MisRec_n1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_n1Bu", uniqueId_, Neutral::pi0, Bachelor::k, 2.4686e-01,
          5.18e-03, Systematic::misIdMisRecKPdfBu, Sign::positive)),
      misId_MisRec_n2Bu_(nullptr),
      pdf1Bu_misId_MisRec_(),
      pdf2Bu_misId_MisRec_(),
      misId_MisRec_fracPdf1Bu_(nullptr),
      pdfBu_misId_MisRec_(new RooCruijff(
          ("pdfBu_misId_MisRec_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_MisRec_mean1Bu_,
          *misId_MisRec_sigma1Bu_, *misId_MisRec_sigma2Bu_, *misId_MisRec_a1Bu_,
          *misId_MisRec_n1Bu_)),
      misId_MisRec_meanBuPartial_(nullptr),
      misId_MisRec_sigmaLBuPartial_(nullptr),
      misId_MisRec_sigmaRBuPartial_(nullptr),
      misId_MisRec_aLBuPartial_(nullptr),
      misId_MisRec_aRBuPartial_(nullptr),
      pdfBuPartial_misId_MisRec_(),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_sigmaLBu_(("Bu2D0h_sigmaLBu_" +
                        ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
                           .c_str(),
                       // "", 3.3137e+01, 10, 100),
                       // Fixed from data
                       // "", 4.1529e+01),
                       // Fixed from data
                       "", 4.8647e+01),
      Bu2D0h_sigmaRBu_(("Bu2D0h_sigmaRBu_" +
                        ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
                           .c_str(),
                       // "", 4.0080e+01, 10, 80),
                       // Fixed from data
                       // "", 3.4501e+01),
                       // Fixed from data
                       "", 3.2605e+01),
      pdfBu_Bu2D0h_(
          ("pdfBu_Bu2D0h_" + ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2D0h_meanBu(),
          // NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId_)
          //     .Bu2D0h_sigmaLBu(),
          // NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId_)
          //     .Bu2D0h_sigmaRBu(),
          Bu2D0h_sigmaLBu_, Bu2D0h_sigmaRBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2D0h_aLBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2D0h_aRBu()),
      Bu2D0h_sigmaLBuPartial_(),
      Bu2D0h_sigmaRBuPartial_(),
      pdfBuPartial_Bu2D0h_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2D0h_meanBu_(("misId_Bu2D0h_meanBu_" +
                            ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
                               .c_str(),
                           "", 5.5539e+03),
      misId_Bu2D0h_sigmaLBu_(("misId_Bu2D0h_sigmaLBu_" +
                              ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
                                 .c_str(),
                             "", 3.5503e+01),
      misId_Bu2D0h_sigmaRBu_(("misId_Bu2D0h_sigmaRBu_" +
                              ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
                                 .c_str(),
                             "", 6.4701e+01),
      misId_Bu2D0h_aLBu_(("misId_Bu2D0h_aLBu_" +
                          ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
                             .c_str(),
                         "", 1.4758e-01),
      misId_Bu2D0h_aRBu_(("misId_Bu2D0h_aRBu_" +
                          ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
                             .c_str(),
                         "", 1.2704e-01),
      pdfBu_misId_Bu2D0h_(("pdfBu_misId_Bu2D0h_" +
                           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
                              .c_str(),
                          "", Configuration::Get().buDeltaMass(),
                          misId_Bu2D0h_meanBu_, misId_Bu2D0h_sigmaLBu_,
                          misId_Bu2D0h_sigmaRBu_, misId_Bu2D0h_aLBu_,
                          misId_Bu2D0h_aRBu_),
      misId_Bu2D0h_meanBuPartial_(),
      misId_Bu2D0h_sigmaLBuPartial_(),
      misId_Bu2D0h_sigmaRBuPartial_(),
      misId_Bu2D0h_aLBuPartial_(),
      misId_Bu2D0h_aRBuPartial_(),
      pdfBuPartial_misId_Bu2D0h_(),
      // -------------------- PART REC -------------------- //
      PartRec_D0pi0_sigmaLBu_(nullptr),
      PartRec_D0pi0_sigmaRBu_(nullptr),
      pdfBu_PartRec_D0pi0_(),
      PartRec_D0gamma_sigmaLBu_(nullptr),
      PartRec_D0gamma_sigmaRBu_(nullptr),
      pdfBu_PartRec_D0gamma_(),
      pdfBu_PartRec_(new RooCruijff(
          ("pdfBu_PartRec_" + ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).PartRec_D0pi0_meanBu(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId_)
              .PartRec_D0pi0_sigmaLBu(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId_)
              .PartRec_D0pi0_sigmaRBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).PartRec_D0pi0_aLBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).PartRec_D0pi0_aRBu())),
      PartRec_sigmaLBuPartial_(nullptr),
      PartRec_sigmaRBuPartial_(nullptr),
      pdfBuPartial_PartRec_(),
      // -------------------- Mis-ID ------------------- //
      misId_PartRec_meanBu_(Params::Get().CreateFixed(
          "misId_PartRec_meanBu", uniqueId_, Neutral::pi0, Bachelor::k,
          5.1582e+03, 1.27e+00, Systematic::misIdPartRecKPdfBu,
          Sign::positive)),
      misId_PartRec_sigmaLBu_(Params::Get().CreateFixed(
          "misId_PartRec_sigmaLBu", uniqueId_, Neutral::pi0, Bachelor::k,
          4.5612e+01, 2.40e+00, Systematic::misIdPartRecKPdfBu,
          Sign::positive)),
      misId_PartRec_sigmaRBu_(Params::Get().CreateFixed(
          "misId_PartRec_sigmaRBu", uniqueId_, Neutral::pi0, Bachelor::k,
          7.7901e+01, 7.10e+00, Systematic::misIdPartRecKPdfBu,
          Sign::positive)),
      misId_PartRec_aLBu_(Params::Get().CreateFixed(
          "misId_PartRec_aLBu", uniqueId_, Neutral::pi0, Bachelor::k,
          1.8171e-09, 3.43e-02, Systematic::misIdPartRecKPdfBu,
          Sign::positive)),
      misId_PartRec_aRBu_(Params::Get().CreateFixed(
          "misId_PartRec_aRBu", uniqueId_, Neutral::pi0, Bachelor::k,
          2.1857e-01, 3.11e-02, Systematic::misIdPartRecKPdfBu,
          Sign::positive)),
      pdfBu_misId_PartRec_(("pdfBu_misId_PartRec_" +
                            ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
                               .c_str(),
                           "", Configuration::Get().buDeltaMass(),
                           *misId_PartRec_meanBu_, *misId_PartRec_sigmaLBu_,
                           *misId_PartRec_sigmaRBu_, *misId_PartRec_aLBu_,
                           *misId_PartRec_aRBu_),
      misId_PartRec_meanBuPartial_(nullptr),
      misId_PartRec_sigmaLBuPartial_(nullptr),
      misId_PartRec_sigmaRBuPartial_(nullptr),
      misId_PartRec_aLBuPartial_(nullptr),
      misId_PartRec_aRBuPartial_(nullptr),
      pdfBuPartial_misId_PartRec_(),
      // -------------------- Bs2Dst0Kpi -------------------- //
      Bs2Dst0Kpi_thresholdDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_thresholdDelta", uniqueId_, Neutral::pi0, Bachelor::k,
          1.3627e+02, 1e00, Systematic::NA, Sign::positive)),
      Bs2Dst0Kpi_aDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_aDelta", uniqueId_, Neutral::pi0, Bachelor::k,
          -7.8318e+00, 1e00, Systematic::NA, Sign::none)),
      Bs2Dst0Kpi_bDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_bDelta", uniqueId_, Neutral::pi0, Bachelor::k, 7.3621e-02,
          1e00, Systematic::NA, Sign::none)),
      Bs2Dst0Kpi_cDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_cDelta", uniqueId_, Neutral::pi0, Bachelor::k, 1.5459e+01,
          1e00, Systematic::NA, Sign::positive)),
      pdfFlatDelta_Bs2Dst0Kpi_(
          ("pdfFlatDelta_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2Dst0Kpi_thresholdDelta_,
          *Bs2Dst0Kpi_cDelta_, *Bs2Dst0Kpi_aDelta_, *Bs2Dst0Kpi_bDelta_),
      Bs2Dst0Kpi_meanDeltaPi0_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_meanDeltaPi0", uniqueId_, Neutral::pi0, Bachelor::k,
          1.4249e+02, 2.88e-01, Systematic::Bs2Dst0KpiDeltaPdf,
          Sign::positive)),
      Bs2Dst0Kpi_sigmaDeltaPi0_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigmaDeltaPi0", uniqueId_, Neutral::pi0, Bachelor::k,
          1.9311e+00, 2.68e-01, Systematic::Bs2Dst0KpiDeltaPdf,
          Sign::positive)),
      pdfPeak1DeltaPi0_Bs2Dst0Kpi_(
          ("pdfPeak1DeltaPi0_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2Dst0Kpi_meanDeltaPi0_,
          *Bs2Dst0Kpi_sigmaDeltaPi0_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_a1Delta(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_n1Delta()),
      pdfPeak2DeltaPi0_Bs2Dst0Kpi_(
          ("pdfPeak2DeltaPi0_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2Dst0Kpi_meanDeltaPi0_,
          *Bs2Dst0Kpi_sigmaDeltaPi0_,
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_a2Delta(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).Bu2Dst0h_D0pi0_n2Delta()),
      pdfPeakDeltaPi0_Bs2Dst0Kpi_(
          ("pdfPeakDeltaPi0_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "",
          RooArgList(pdfPeak1DeltaPi0_Bs2Dst0Kpi_,
                     pdfPeak2DeltaPi0_Bs2Dst0Kpi_),
          NeutralVars<Neutral::pi0>::Get(uniqueId_)
              .Bu2Dst0h_D0pi0_fracPdf1Delta()),
      Bs2Dst0Kpi_fracPeakDeltaPi0_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_fracPeakDeltaPi0", uniqueId_, Neutral::pi0, Bachelor::k,
          6.4451e-01, 5.83e-02, Systematic::Bs2Dst0KpiDeltaPdf,
          Sign::positive)),
      pdfDelta_Bs2Dst0Kpi_(
          ("pdfDelta_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", RooArgList(pdfPeakDeltaPi0_Bs2Dst0Kpi_, pdfFlatDelta_Bs2Dst0Kpi_),
          *Bs2Dst0Kpi_fracPeakDeltaPi0_),
      Bs2Dst0Kpi_meanDeltaGamma_(nullptr),
      Bs2Dst0Kpi_sigmaDeltaGamma_(nullptr),
      pdfPeak1DeltaGamma_Bs2Dst0Kpi_(),
      pdfPeak2DeltaGamma_Bs2Dst0Kpi_(),
      pdfPeakDeltaGamma_Bs2Dst0Kpi_(),
      Bs2Dst0Kpi_fracPeakDeltaGamma_(nullptr),
      Bs2Dst0Kpi_mean1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_mean1Bu", uniqueId_, Neutral::pi0, Bachelor::k,
          5.2065e+03, 1e00, Systematic::NA, Sign::positive)),
      Bs2Dst0Kpi_sigma1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigma1Bu", uniqueId_, Neutral::pi0, Bachelor::k,
          3.1366e+01, 3.25e+00, Systematic::Bs2Dst0KpiBuPdf, Sign::positive)),
      Bs2Dst0Kpi_sigma2Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigma2Bu", uniqueId_, Neutral::pi0, Bachelor::k,
          2.3145e+01, 2.42e+00, Systematic::Bs2Dst0KpiBuPdf, Sign::positive)),
      Bs2Dst0Kpi_aLBu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_aLBu", uniqueId_, Neutral::pi0, Bachelor::k, 6.0169e-02,
          5.12e-02, Systematic::Bs2Dst0KpiBuPdf, Sign::positive)),
      Bs2Dst0Kpi_aRBu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_aRBu", uniqueId_, Neutral::pi0, Bachelor::k, 7.1721e-02,
          4.68e-02, Systematic::Bs2Dst0KpiBuPdf, Sign::positive)),
      pdfBu_Bs2Dst0Kpi_(new RooCruijff(
          ("pdfBu_Bs2Dst0Kpi_" +
           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2Dst0Kpi_mean1Bu_,
          *Bs2Dst0Kpi_sigma1Bu_, *Bs2Dst0Kpi_sigma2Bu_, *Bs2Dst0Kpi_aLBu_,
          *Bs2Dst0Kpi_aRBu_)),
      Bs2Dst0Kpi_mean2Bu_(nullptr),
      Bs2Dst0Kpi_a1Bu_(nullptr),
      Bs2Dst0Kpi_n1Bu_(nullptr),
      pdf1Bu_Bs2Dst0Kpi_(),
      pdf2Bu_Bs2Dst0Kpi_(),
      Bs2Dst0Kpi_fracPdf1Bu_(nullptr),
      Bs2Dst0Kpi_meanBuPartial_(nullptr),
      Bs2Dst0Kpi_sigmaLBuPartial_(nullptr),
      Bs2Dst0Kpi_sigmaRBuPartial_(nullptr),
      Bs2Dst0Kpi_aLBuPartial_(nullptr),
      Bs2Dst0Kpi_aRBuPartial_(nullptr),
      pdfBuPartial_Bs2Dst0Kpi_(),
      // -------------------- Bs2D0Kpi -------------------- //
      Bs2D0Kpi_thresholdDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_thresholdDelta", uniqueId_, Neutral::pi0, Bachelor::k,
          1.3627e+02, 1e00, Systematic::NA, Sign::positive)),
      Bs2D0Kpi_aDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_aDelta", uniqueId_, Neutral::pi0, Bachelor::k, -4.4722e+00,
          2.09e+00, Systematic::Bs2D0KpiDeltaPdf, Sign::none)),
      Bs2D0Kpi_bDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_bDelta", uniqueId_, Neutral::pi0, Bachelor::k, 7.3621e-02,
          1e00, Systematic::NA, Sign::none)),
      Bs2D0Kpi_cDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_cDelta", uniqueId_, Neutral::pi0, Bachelor::k, 1.5459e+01,
          1e00, Systematic::NA, Sign::positive)),
      pdfDelta_Bs2D0Kpi_(("pdfDelta_Bs2D0Kpi_" +
                          ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
                             .c_str(),
                         "", Configuration::Get().deltaMass(),
                         *Bs2D0Kpi_thresholdDelta_, *Bs2D0Kpi_cDelta_,
                         *Bs2D0Kpi_aDelta_, *Bs2D0Kpi_bDelta_),
      Bs2D0Kpi_mean1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_mean1Bu", uniqueId_, Neutral::pi0, Bachelor::k, 5.3384e+03,
          2.11e+01, Systematic::Bs2D0KpiBuPdf, Sign::positive)),
      Bs2D0Kpi_sigma1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_sigma1Bu", uniqueId_, Neutral::pi0, Bachelor::k, 8.2330e+01,
          1.51e+01, Systematic::Bs2D0KpiBuPdf, Sign::positive)),
      pdfBu_Bs2D0Kpi_(
          new RooGaussian(("pdfBu_Bs2D0Kpi_" +
                           ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
                              .c_str(),
                          "", Configuration::Get().buDeltaMass(),
                          *Bs2D0Kpi_mean1Bu_, *Bs2D0Kpi_sigma1Bu_)),
      Bs2D0Kpi_mean2Bu_(nullptr),
      Bs2D0Kpi_sigma2Bu_(nullptr),
      Bs2D0Kpi_a1Bu_(nullptr),
      Bs2D0Kpi_n1Bu_(nullptr),
      pdf1Bu_Bs2D0Kpi_(),
      pdf2Bu_Bs2D0Kpi_(),
      Bs2D0Kpi_fracPdf1Bu_(),
      Bs2D0Kpi_meanBuPartial_(nullptr),
      Bs2D0Kpi_sigmaLBuPartial_(nullptr),
      Bs2D0Kpi_sigmaRBuPartial_(nullptr),
      Bs2D0Kpi_aLBuPartial_(nullptr),
      Bs2D0Kpi_aRBuPartial_(nullptr),
      pdfBuPartial_Bs2D0Kpi_(),
      // -------------------- Correct ID BOX EFFs -------------------- //
      buEffBu2Dst0h_D0gamma_(nullptr),
      buEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::pi0, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::k, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::k, Efficiency::buEffErr,
                        false),
          Systematic::NA, Sign::positive)),
      buEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::pi0, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::k, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::k,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::positive)),
      buEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "buEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::pi0, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::k, Efficiency::buEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::k,
                        Efficiency::buEffErr, false),
          Systematic::NA, Sign::positive)),
      deltaEffBu2Dst0h_D0gamma_(nullptr),
      deltaEffBu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_", uniqueId_, Neutral::pi0, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::k, Efficiency::deltaEff,
                        false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::k,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::positive)),
      deltaEffBu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0gamma_WN_", uniqueId_, Neutral::pi0, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::k,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma_WN, Bachelor::k,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::positive)),
      deltaEffBu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "deltaEffBu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::pi0, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::k,
                        Efficiency::deltaEff, false),
          ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0_WN, Bachelor::k,
                        Efficiency::deltaEffErr, false),
          Systematic::NA, Sign::positive)),
      buPartialEffBu2Dst0h_D0gamma_(nullptr),
      buPartialEffBu2Dst0h_D0pi0_(nullptr),
      buPartialEffBu2Dst0h_D0gamma_WN_(nullptr),
      buPartialEffBu2Dst0h_D0pi0_WN_(nullptr),
      // -------------------- Mis-ID BoxEffs ------------------- //
      buEffMisId_Bu2Dst0h_D0gamma_(nullptr),
      buEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::pi0, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::k, Efficiency::buEff,
                        true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::k,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::positive)),
      buEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "buEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::pi0, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::k,
                        Efficiency::buEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::k,
                        Efficiency::buEffErr, true),
          Systematic::NA, Sign::positive)),
      deltaEffMisId_Bu2Dst0h_D0gamma_(nullptr),
      deltaEffMisId_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0pi0_", uniqueId_, Neutral::pi0, Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::k,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::k,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::positive)),
      deltaEffMisId_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "deltaEffMisId_Bu2Dst0h_D0pi0_WN_", uniqueId_, Neutral::pi0,
          Bachelor::k,
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::k,
                        Efficiency::deltaEff, true),
          ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_WN, Bachelor::k,
                        Efficiency::deltaEffErr, true),
          Systematic::NA, Sign::positive)),
      buPartialEffMisId_Bu2Dst0h_D0gamma_(nullptr),
      buPartialEffMisId_Bu2Dst0h_D0pi0_(nullptr),
      buPartialEffMisId_Bu2Dst0h_D0pi0_WN_(nullptr),
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
          "mcEff_Bu2Dst0h_D0pi0", uniqueId_, Neutral::pi0, Bachelor::k,
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEff_Bu2Dst0h_D0gamma_(nullptr),
      mcEff_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::pi0, Bachelor::k,
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma_WN, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0gamma_WN, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEff_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::pi0, Bachelor::k,
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0_WN, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2Dst0K_D0pi0_WN, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEff_MisRec_(Params::Get().CreateFixed(
          "mcEff_MisRec", uniqueId_, Neutral::pi0, Bachelor::k, 1.0, 0.0,
          Systematic::NA, Sign::positive)),
      mcEff_Bu2D0h_(Params::Get().CreateFixed(
          "mcEff_Bu2D0h", uniqueId_, Neutral::pi0, Bachelor::k,
          ReturnMCEffs(Mode::Bu2D0K, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEff),
          ReturnMCEffs(Mode::Bu2D0K, Neutral::pi0, Bachelor::k,
                       Efficiency::mcEffErr),
          Systematic::mcEffs, Sign::positive)),
      mcEff_PartRec_(Params::Get().CreateFixed(
          "mcEff_PartRec", uniqueId_, Neutral::pi0, Bachelor::k, 1.0, 0.0,
          Systematic::NA, Sign::positive)),
      mcEff_Bs2Dst0Kpi_(Params::Get().CreateFixed(
          "mcEff_Bs2Dst0Kpi", uniqueId_, Neutral::pi0, Bachelor::k, 1.0, 0.0,
          Systematic::NA, Sign::positive)),
      mcEff_Bs2D0Kpi_(Params::Get().CreateFixed(
          "mcEff_Bs2D0Kpi", uniqueId_, Neutral::pi0, Bachelor::k, 1.0, 0.0,
          Systematic::NA, Sign::positive)),
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
    A_CP_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0pi0_Blind", uniqueId_,
                                     Neutral::pi0, Bachelor::k, -0.151, -1, 1));
    A_CP_Bu2Dst0h_D0gamma_WN_Blind_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0gamma_WN_Blind", uniqueId_, Neutral::pi0,
            Bachelor::k, 0.276, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_WN_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0pi0_WN_Blind", uniqueId_,
                                     Neutral::pi0, Bachelor::k, -0.151, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooUnblindUniform>(
        MakeBlind(("A_CP_Bu2Dst0h_D0pi0_" +
                   ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
                      .c_str(),
                  0.03, *A_CP_Bu2Dst0h_D0pi0_Blind_));
    A_CP_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooUnblindUniform>(
        MakeBlind(("A_CP_Bu2Dst0h_D0gamma_WN_" +
                   ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
                      .c_str(),
                  0.03, *A_CP_Bu2Dst0h_D0gamma_WN_Blind_));
    A_CP_Bu2Dst0h_D0pi0_WN_ = std::shared_ptr<RooUnblindUniform>(
        MakeBlind(("A_CP_Bu2Dst0h_D0pi0_WN_" +
                   ComposeName(uniqueId_, Neutral::pi0, Bachelor::k))
                      .c_str(),
                  0.03, *A_CP_Bu2Dst0h_D0pi0_WN_Blind_));
  } else {
    A_CP_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0pi0", uniqueId_,
                                     Neutral::pi0, Bachelor::k, -0.151, -1, 1));
    A_CP_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::pi0, Bachelor::k,
            0.276, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_WN_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0pi0_WN", uniqueId_,
                                     Neutral::pi0, Bachelor::k, -0.151, -1, 1));
  }
  if (Configuration::Get().splitByCharge() == true) {
    R_ADS_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::pi0, Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_",
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::k,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0(),
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::k,
                                      Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
    R_ADS_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::pi0, Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::k,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN(),
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::k,
                                      Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN()));
    R_ADS_Bu2Dst0h_D0pi0_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::pi0, Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_WN_",
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::k,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN(),
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::k,
                                      Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN()));
  } else {
    R_ADS_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::pi0, Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_",
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::k,
                                      Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
    R_ADS_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::pi0, Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::k,
                                      Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN()));
    R_ADS_Bu2Dst0h_D0pi0_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Neutral::pi0, Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_WN_",
            NeutralBachelorChargeVars<Neutral::pi0, Bachelor::k,
                                      Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN()));
  }
  std::map<std::string, double> mapMisId_Bu2Dst0h_D0pi0;
  std::map<std::string, double> mapMisId_Bu2Dst0h_D0gamma;
  std::map<std::string, double> mapMisId_Bu2D0h;
  std::map<std::string, double> mapMisId_PartRec;
  std::map<std::string, double> mapBs2Dst0Kpi;
  std::map<std::string, double> mapBs2D0Kpi;

  ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::k,
                                     mapMisId_Bu2Dst0h_D0pi0, true);
  ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::k,
                                     mapMisId_Bu2Dst0h_D0gamma, true);
  ReturnBoxEffs(Mode::Bu2D0pi, Bachelor::k,
                                     mapMisId_Bu2D0h, true);
  ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::k,
                                     mapMisId_PartRec, true);
  ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k,
                                     mapBs2Dst0Kpi, false);
  ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, mapBs2D0Kpi,
                                     false);

  std::map<Mode, double> misRecModesMap = {
      {Mode::Bu2Dst0pi_D0pi0_WN,
       NeutralVars<Neutral::pi0>::Get(uniqueId_)
               .fracMisRec_Bu2Dst0h_D0pi0_WN() /
           NeutralVars<Neutral::pi0>::Get(uniqueId_).fracMisRec()},
      {Mode::Bu2Dst0pi_D0gamma,
       NeutralVars<Neutral::pi0>::Get(uniqueId_).fracMisRec_Bu2Dst0h_D0gamma() /
           NeutralVars<Neutral::pi0>::Get(uniqueId_).fracMisRec()},
      {Mode::Bu2Dst0pi_D0gamma_WN,
       NeutralVars<Neutral::pi0>::Get(uniqueId_)
               .fracMisRec_Bu2Dst0h_D0gamma_WN() /
           NeutralVars<Neutral::pi0>::Get(uniqueId_).fracMisRec()},
      {Mode::Bu2D0rho,
       NeutralVars<Neutral::pi0>::Get(uniqueId_).fracMisRec_Bu2D0hst() /
           NeutralVars<Neutral::pi0>::Get(uniqueId_).fracMisRec()},
      {Mode::Bd2Dstpi,
       NeutralVars<Neutral::pi0>::Get(uniqueId_).fracMisRec_Bd2Dsth() /
           NeutralVars<Neutral::pi0>::Get(uniqueId_).fracMisRec()}};

  std::map<std::string, double> mapMisId_MisRec;
  unsigned int it = 0;
  for (auto &m : misRecModesMap) {
    std::map<std::string, double> mapMisId_MisRecTmp;
    ReturnBoxEffs(m.first, Bachelor::k, mapMisId_MisRecTmp,
                                       false);
    if (it == 0) {
      mapMisId_MisRec.insert(std::pair<std::string, double>(
          "buDeltaCutEff", mapMisId_MisRecTmp["buDeltaCutEff"] * m.second));
      mapMisId_MisRec.insert(std::pair<std::string, double>(
          "deltaCutEff", mapMisId_MisRecTmp["deltaCutEff"] * m.second));
    } else {
      mapMisId_MisRec["buDeltaCutEff"] +=
          mapMisId_MisRecTmp["buDeltaCutEff"] * m.second;
      mapMisId_MisRec["deltaCutEff"] +=
          mapMisId_MisRecTmp["deltaCutEff"] * m.second;
    }
    ++it;
  }

  buDeltaCutEffMisId_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_Bu2Dst0h_D0pi0", uniqueId_, Neutral::pi0,
          mapMisId_Bu2Dst0h_D0pi0["buDeltaCutEff"],
          mapMisId_Bu2Dst0h_D0pi0["buDeltaCutEffErr"],
          Systematic::buDeltaMisIdCutEffs, Sign::positive));
  buDeltaCutEffMisId_Bu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_Bu2Dst0h_D0gamma", uniqueId_, Neutral::pi0,
          mapMisId_Bu2Dst0h_D0gamma["buDeltaCutEff"],
          mapMisId_Bu2Dst0h_D0gamma["buDeltaCutEffErr"], Systematic::NA,
          Sign::positive));
  buDeltaCutEffMisId_MisRec_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_MisRec", uniqueId_, Neutral::pi0,
          mapMisId_MisRec["buDeltaCutEff"], mapMisId_MisRec["buDeltaCutEffErr"],
          Systematic::buDeltaMisIdCutEffs, Sign::positive));
  buDeltaCutEffMisId_Bu2D0h_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_Bu2D0h", uniqueId_, Neutral::pi0,
          mapMisId_Bu2D0h["buDeltaCutEff"], mapMisId_Bu2D0h["buDeltaCutEffErr"],
          Systematic::NA, Sign::positive));
  buDeltaCutEffMisId_PartRec_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_PartRec", uniqueId_, Neutral::pi0,
          mapMisId_PartRec["buDeltaCutEff"],
          mapMisId_PartRec["buDeltaCutEffErr"], Systematic::buDeltaMisIdCutEffs,
          Sign::positive));
  buDeltaCutEffBs2Dst0Kpi_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffBs2Dst0Kpi", uniqueId_, Neutral::pi0, Bachelor::k,
          mapBs2Dst0Kpi["buDeltaCutEff"], mapBs2Dst0Kpi["buDeltaCutEffErr"],
          Systematic::buDeltaCutEffs, Sign::positive));
  buDeltaCutEffBs2D0Kpi_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffBs2D0Kpi", uniqueId_, Neutral::pi0, Bachelor::k,
          mapBs2D0Kpi["buDeltaCutEff"], mapBs2D0Kpi["buDeltaCutEffErr"],
          Systematic::buDeltaCutEffs, Sign::positive));

  deltaCutEffMisId_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_Bu2Dst0h_D0pi0", uniqueId_, Neutral::pi0,
          mapMisId_Bu2Dst0h_D0pi0["deltaCutEff"],
          mapMisId_Bu2Dst0h_D0pi0["deltaCutEffErr"],
          Systematic::deltaMisIdCutEffs, Sign::positive));
  deltaCutEffMisId_Bu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_Bu2Dst0h_D0gamma", uniqueId_, Neutral::pi0,
          mapMisId_Bu2Dst0h_D0gamma["deltaCutEff"],
          mapMisId_Bu2Dst0h_D0gamma["deltaCutEffErr"], Systematic::NA,
          Sign::positive));
  deltaCutEffMisId_MisRec_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_MisRec", uniqueId_, Neutral::pi0,
          mapMisId_MisRec["deltaCutEff"], mapMisId_MisRec["deltaCutEffErr"],
          Systematic::deltaMisIdCutEffs, Sign::positive));
  deltaCutEffMisId_Bu2D0h_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_Bu2D0h", uniqueId_, Neutral::pi0,
          mapMisId_Bu2D0h["deltaCutEff"], mapMisId_Bu2D0h["deltaCutEffErr"],
          Systematic::NA, Sign::positive));
  deltaCutEffMisId_PartRec_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_PartRec", uniqueId_, Neutral::pi0,
          mapMisId_PartRec["deltaCutEff"], mapMisId_PartRec["deltaCutEffErr"],
          Systematic::deltaMisIdCutEffs, Sign::positive));
  deltaCutEffBs2Dst0Kpi_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffBs2Dst0Kpi", uniqueId_, Neutral::pi0, Bachelor::k,
          mapBs2Dst0Kpi["deltaCutEff"], mapBs2Dst0Kpi["deltaCutEffErr"],
          Systematic::deltaCutEffs, Sign::positive));
  deltaCutEffBs2D0Kpi_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "deltaCutEffBs2D0Kpi", uniqueId_, Neutral::pi0, Bachelor::k,
      mapBs2D0Kpi["deltaCutEff"], mapBs2D0Kpi["deltaCutEffErr"],
      Systematic::deltaCutEffs, Sign::positive));
}
