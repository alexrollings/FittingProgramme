#include "NeutralBachelorVars.h"
#include "Params.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- Bu2Dst0h_D0gamma -------------------- //
    : Bu2Dst0h_D0gamma_sigma1Bu_(new RooFormulaVar(
          ("Bu2Dst0h_D0gamma_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_D0gamma_sigma1Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .Bu2Dst0h_D0gamma_KpiSigmaBu()))),
      Bu2Dst0h_D0gamma_sigma2Bu_(nullptr),
      pdf1Bu_Bu2Dst0h_D0gamma_(
          ("pdf1Bu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_meanBu(),
          *Bu2Dst0h_D0gamma_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0gamma_(
          ("pdf2Bu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_meanBu(),
          *Bu2Dst0h_D0gamma_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_n2Bu()),
      pdfBu_Bu2Dst0h_D0gamma_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0h_D0gamma_, pdf2Bu_Bu2Dst0h_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0gamma_fracPdf1Bu())),
      Bu2Dst0h_D0gamma_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_sigmaBuPartial", uniqueId, Neutral::gamma,
          Bachelor::k, 2.9969e+01, 2.68e+00, Systematic::crossFeedBuPartialPdf,
          Sign::positive)),
      pdfBuPartial_Bu2Dst0h_D0gamma_(
          ("pdfBuPartial_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0gamma_meanBuPartial(),
          *Bu2Dst0h_D0gamma_sigmaBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0gamma_aBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0gamma_nBuPartial()),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_meanBu", uniqueId, Neutral::gamma,
          Bachelor::k, 5.3424e+03, 8.13e-01, Systematic::misIdGammaKPdfBu,
          Sign::positive)),
      misId_Bu2Dst0h_D0gamma_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_sigma1Bu", uniqueId, Neutral::gamma,
          Bachelor::k, 2.7653e+01, 7.10e-01, Systematic::misIdGammaKPdfBu,
          Sign::positive)),
      misId_Bu2Dst0h_D0gamma_sigma2Bu_(nullptr),
      misId_Bu2Dst0h_D0gamma_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a1Bu", uniqueId, Neutral::gamma, Bachelor::k,
          7.4617e-01, 2.93e-01, Systematic::misIdGammaKPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_a2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a2Bu", uniqueId, Neutral::gamma, Bachelor::k,
          -4.6112e-01, 2.88e-02, Systematic::misIdGammaKPdfBu, Sign::negative)),
      misId_Bu2Dst0h_D0gamma_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n1Bu", uniqueId, Neutral::gamma, Bachelor::k,
          1.5355e+00, 1.59e+00, Systematic::misIdGammaKPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_n2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n2Bu", uniqueId, Neutral::gamma, Bachelor::k,
          6.3489e+00, 8.41e-01, Systematic::misIdGammaKPdfBu, Sign::positive)),
      pdf1Bu_misId_Bu2Dst0h_D0gamma_(
          ("pdf1Bu_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0gamma_meanBu_, *misId_Bu2Dst0h_D0gamma_sigma1Bu_,
          *misId_Bu2Dst0h_D0gamma_a1Bu_, *misId_Bu2Dst0h_D0gamma_n1Bu_),
      pdf2Bu_misId_Bu2Dst0h_D0gamma_(
          ("pdf2Bu_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0gamma_meanBu_, *misId_Bu2Dst0h_D0gamma_sigma1Bu_,
          *misId_Bu2Dst0h_D0gamma_a2Bu_, *misId_Bu2Dst0h_D0gamma_n2Bu_),
      misId_Bu2Dst0h_D0gamma_fracPdf1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_fracPdf1Bu", uniqueId, Neutral::gamma,
          Bachelor::k, 4.9777e-02, 2.30e-02, Systematic::misIdGammaKPdfBu,
          Sign::positive)),
      pdfBu_misId_Bu2Dst0h_D0gamma_(
          new RooAddPdf(("pdfBu_misId_Bu2Dst0h_D0gamma_" +
                         ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "",
                        RooArgList(pdf1Bu_misId_Bu2Dst0h_D0gamma_,
                                   pdf2Bu_misId_Bu2Dst0h_D0gamma_),
                        *misId_Bu2Dst0h_D0gamma_fracPdf1Bu_)),
      buDeltaCutEffMisId_Bu2Dst0h_D0gamma_(nullptr),
      deltaCutEffMisId_Bu2Dst0h_D0gamma_(nullptr),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      Bu2Dst0h_D0pi0_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_sigmaBu", uniqueId, Neutral::gamma, Bachelor::k,
          4.4834e+01, 7.73e-01, Systematic::crossFeedBuPdf, Sign::positive)),
      pdf1Bu_Bu2Dst0h_D0pi0_(),
      pdf2Bu_Bu2Dst0h_D0pi0_(),
      pdfBu_Bu2Dst0h_D0pi0_(new RooCBShape(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigmaBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_n1Bu())),
      Bu2Dst0h_D0pi0_sigma1BuPartial_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_sigma1BuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_D0pi0_sigma1BuPartial(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .Bu2Dst0h_D0pi0_KpiSigmaBuPartial()))),
      Bu2Dst0h_D0pi0_sigma2BuPartial_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_sigma2BuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_D0pi0_sigma2BuPartial(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .Bu2Dst0h_D0pi0_KpiSigmaBuPartial()))),
      Bu2Dst0h_D0pi0_sigma3BuPartial_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_sigma3BuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_D0pi0_sigma3BuPartial(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .Bu2Dst0h_D0pi0_KpiSigmaBuPartial()))),
      pdf1BuPartial_Bu2Dst0h_D0pi0_(
          ("pdf1BuPartial_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0pi0_meanCbBuPartial(),
          *Bu2Dst0h_D0pi0_sigma1BuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0pi0_a1BuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0pi0_n1BuPartial()),
      pdf2BuPartial_Bu2Dst0h_D0pi0_(
          ("pdf2BuPartial_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0pi0_meanCbBuPartial(),
          *Bu2Dst0h_D0pi0_sigma2BuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0pi0_a2BuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0pi0_n2BuPartial()),
      pdf3BuPartial_Bu2Dst0h_D0pi0_(
          ("pdf3BuPartial_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0pi0_meanGausBuPartial(),
          *Bu2Dst0h_D0pi0_sigma3BuPartial_),
      pdfBuPartial_Bu2Dst0h_D0pi0_(
          ("pdfBuPartial_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgSet(pdf1BuPartial_Bu2Dst0h_D0pi0_,
                    pdf2BuPartial_Bu2Dst0h_D0pi0_,
                    pdf3BuPartial_Bu2Dst0h_D0pi0_),
          RooArgSet(NeutralVars<Neutral::gamma>::Get(uniqueId)
                        .Bu2Dst0h_D0pi0_fracPdfCb1BuPartial(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                        .Bu2Dst0h_D0pi0_fracPdfCb2BuPartial())),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0pi0_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_meanBu", uniqueId, Neutral::gamma, Bachelor::k,
          5.4141e+03, 1.26e+00, Systematic::misIdPi0KPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma1Bu", uniqueId, Neutral::gamma,
          Bachelor::k, 7.8343e+01, 9.86e-01, Systematic::misIdPi0KPdfBu,
          Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigma2Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1Bu", uniqueId, Neutral::gamma, Bachelor::k,
          2.5079e+00, 1e+00, Systematic::NA, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a2Bu", uniqueId, Neutral::gamma, Bachelor::k,
          -1.0082e+00, 1e+00, Systematic::NA, Sign::negative)),
      misId_Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1Bu", uniqueId, Neutral::gamma, Bachelor::k,
          3.8304e-06, 1e+00, Systematic::NA, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_n2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n2Bu", uniqueId, Neutral::gamma, Bachelor::k,
          10, 1e00, Systematic::NA, Sign::positive)),
      pdf1Bu_misId_Bu2Dst0h_D0pi0_(
          ("pdf1Bu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_Bu2Dst0h_D0pi0_meanBu_,
          *misId_Bu2Dst0h_D0pi0_sigma1Bu_, *misId_Bu2Dst0h_D0pi0_a1Bu_,
          *misId_Bu2Dst0h_D0pi0_n1Bu_),
      pdf2Bu_misId_Bu2Dst0h_D0pi0_(
          ("pdf2Bu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_Bu2Dst0h_D0pi0_meanBu_,
          *misId_Bu2Dst0h_D0pi0_sigma1Bu_, *misId_Bu2Dst0h_D0pi0_a2Bu_,
          *misId_Bu2Dst0h_D0pi0_n2Bu_),
      misId_Bu2Dst0h_D0pi0_fracPdf1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_fracPdf1Bu", uniqueId, Neutral::gamma,
          Bachelor::k, 1.7316e-01, 4.83e-02, Systematic::misIdPi0KPdfBu,
          Sign::positive)),
      pdfBu_misId_Bu2Dst0h_D0pi0_(
          new RooAddPdf(("pdfBu_misId_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "",
                        RooArgList(pdf1Bu_misId_Bu2Dst0h_D0pi0_,
                                   pdf2Bu_misId_Bu2Dst0h_D0pi0_),
                        *misId_Bu2Dst0h_D0pi0_fracPdf1Bu_)),
      misId_Bu2Dst0h_D0pi0_meanBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_meanBuPartial", uniqueId, Neutral::gamma,
          Bachelor::k, 5.3629e+03, 3.61e-01, Systematic::misIdPi0KPdfBuPartial,
          Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigma1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma1BuPartial", uniqueId, Neutral::gamma,
          Bachelor::k, 4.6576e+01, 3.64e-01, Systematic::misIdPi0KPdfBuPartial,
          Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigma2BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_a1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1BuPartial", uniqueId, Neutral::gamma,
          Bachelor::k, 7.9869e-01, 5.76e-02, Systematic::misIdPi0KPdfBuPartial,
          Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a2BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a2BuPartial", uniqueId, Neutral::gamma,
          Bachelor::k, -6.1441e-01, 9.71e-03, Systematic::misIdPi0KPdfBuPartial,
          Sign::negative)),
      misId_Bu2Dst0h_D0pi0_n1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1BuPartial", uniqueId, Neutral::gamma,
          Bachelor::k, 10, 1e+00, Systematic::NA, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_n2BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n2BuPartial", uniqueId, Neutral::gamma,
          Bachelor::k, 10, 1e00, Systematic::NA, Sign::positive)),
      pdf1BuPartial_misId_Bu2Dst0h_D0pi0_(
          ("pdf1BuPartial_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_meanBuPartial_,
          *misId_Bu2Dst0h_D0pi0_sigma1BuPartial_,
          *misId_Bu2Dst0h_D0pi0_a1BuPartial_,
          *misId_Bu2Dst0h_D0pi0_n1BuPartial_),
      pdf2BuPartial_misId_Bu2Dst0h_D0pi0_(
          ("pdf2BuPartial_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0pi0_meanBuPartial_,
          *misId_Bu2Dst0h_D0pi0_sigma1BuPartial_,
          *misId_Bu2Dst0h_D0pi0_a2BuPartial_,
          *misId_Bu2Dst0h_D0pi0_n2BuPartial_),
      misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial", uniqueId, Neutral::gamma,
          Bachelor::k, 1.1361e-01, 1.46e-02, Systematic::misIdPi0KPdfBuPartial,
          Sign::positive)),
      pdfBuPartial_misId_Bu2Dst0h_D0pi0_(
          new RooAddPdf(("pdfBuPartial_misId_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "",
                        RooArgList(pdf1BuPartial_misId_Bu2Dst0h_D0pi0_,
                                   pdf2BuPartial_misId_Bu2Dst0h_D0pi0_),
                        *misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_)),
      buDeltaCutEffMisId_Bu2Dst0h_D0pi0_(nullptr),
      deltaCutEffMisId_Bu2Dst0h_D0pi0_(nullptr),
      deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_(nullptr),
      // -------------------- MIS-REC -------------------- //
      MisRec_sigmaLBu_(Params::Get().CreateFixed(
          "MisRec_sigmaLBu", uniqueId, Neutral::gamma, Bachelor::k, 1.2599e+02,
          4.68e+00, Systematic::misRecBuPdf, Sign::positive)),
      MisRec_sigmaRBu_(Params::Get().CreateFixed(
          "MisRec_sigmaRBu", uniqueId, Neutral::gamma, Bachelor::k, 8.0741e+01,
          2.82e+00, Systematic::misRecBuPdf, Sign::positive)),
      pdfBu_MisRec_(
          ("pdfBu_MisRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_meanBu(),
          *MisRec_sigmaLBu_, *MisRec_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aRBu()),
      MisRec_sigmaLBuPartial_(Params::Get().CreateFixed(
          "MisRec_sigmaLBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          1.1875e+02, 5.43e+00, Systematic::misRecBuPartialPdf,
          Sign::positive)),
      MisRec_sigmaRBuPartial_(Params::Get().CreateFixed(
          "MisRec_sigmaRBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          4.7343e+01, 2.81e+00, Systematic::misRecBuPartialPdf,
          Sign::positive)),
      pdfBuPartial_MisRec_(
          ("pdfBuPartial_MisRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_meanBuPartial(),
          *MisRec_sigmaLBuPartial_, *MisRec_sigmaRBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aRBuPartial()),
      // -------------------- Mis-ID ------------------- //
      misId_MisRec_mean1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_mean1Bu", uniqueId, Neutral::gamma, Bachelor::k,
          5.3348e+03, 5.74e-01, Systematic::misIdMisRecKPdfBu, Sign::positive)),
      misId_MisRec_mean2Bu_(Params::Get().CreateFixed(
          "misId_MisRec_mean2Bu", uniqueId, Neutral::gamma, Bachelor::k,
          5.3417e+03, 1.91e-01, Systematic::misIdMisRecKPdfBu, Sign::positive)),
      misId_MisRec_sigma1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_sigma1Bu", uniqueId, Neutral::gamma, Bachelor::k,
          1.0688e+02, 1e00, Systematic::NA, Sign::positive)),
      misId_MisRec_sigma2Bu_(Params::Get().CreateFixed(
          "misId_MisRec_sigma2Bu", uniqueId, Neutral::gamma, Bachelor::k,
          2.5076e+01, 1e00, Systematic::NA, Sign::positive)),
      misId_MisRec_a1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_a1Bu", uniqueId, Neutral::gamma, Bachelor::k,
          4.8433e+00, 1e00, Systematic::NA, Sign::positive)),
      misId_MisRec_a2Bu_(Params::Get().CreateFixed(
          "misId_MisRec_a2Bu", uniqueId, Neutral::gamma, Bachelor::k,
          -2.9325e-01, 1e00, Systematic::NA, Sign::negative)),
      misId_MisRec_n1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_n1Bu", uniqueId, Neutral::gamma, Bachelor::k,
          9.6419e+00, 1e+00, Systematic::NA, Sign::positive)),
      misId_MisRec_n2Bu_(Params::Get().CreateFixed(
          "misId_MisRec_n2Bu", uniqueId, Neutral::gamma, Bachelor::k,
          1.0000e+01, 1e01, Systematic::NA, Sign::positive)),
      pdf1Bu_misId_MisRec_(("pdf1Bu_misId_MisRec_" +
                            ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                               .c_str(),
                           "", Configuration::Get().buDeltaMass(),
                           *misId_MisRec_mean1Bu_, *misId_MisRec_sigma1Bu_,
                           *misId_MisRec_a1Bu_, *misId_MisRec_n1Bu_),
      pdf2Bu_misId_MisRec_(("pdf2Bu_misId_MisRec_" +
                            ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                               .c_str(),
                           "", Configuration::Get().buDeltaMass(),
                           *misId_MisRec_mean2Bu_, *misId_MisRec_sigma1Bu_,
                           *misId_MisRec_a2Bu_, *misId_MisRec_n2Bu_),
      misId_MisRec_fracPdf1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_fracPdf1Bu", uniqueId, Neutral::gamma, Bachelor::k,
          5.2164e-01, 3.41e-03, Systematic::misIdMisRecKPdfBu, Sign::positive)),
      pdfBu_misId_MisRec_(new RooAddPdf(
          ("pdfBu_misId_MisRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", RooArgList(pdf1Bu_misId_MisRec_, pdf2Bu_misId_MisRec_),
          *misId_MisRec_fracPdf1Bu_)),
      misId_MisRec_meanBuPartial_(Params::Get().CreateFixed(
          "misId_MisRec_meanBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          5.3852e+03, 3.62e-04, Systematic::misIdMisRecKPdfBuPartial,
          Sign::positive)),
      misId_MisRec_sigmaLBuPartial_(Params::Get().CreateFixed(
          "misId_MisRec_sigmaLBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          1.0686e+02, 4.24e-01, Systematic::misIdMisRecKPdfBuPartial,
          Sign::positive)),
      misId_MisRec_sigmaRBuPartial_(Params::Get().CreateFixed(
          "misId_MisRec_sigmaRBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          6.8440e+01, 3.85e-01, Systematic::misIdMisRecKPdfBuPartial,
          Sign::positive)),
      misId_MisRec_aLBuPartial_(Params::Get().CreateFixed(
          "misId_MisRec_aLBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          3.4482e-02, 1e00, Systematic::NA, Sign::positive)),
      misId_MisRec_aRBuPartial_(Params::Get().CreateFixed(
          "misId_MisRec_aRBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          1.6765e-01, 1e00, Systematic::NA, Sign::positive)),
      pdfBuPartial_misId_MisRec_(
          ("pdfBuPartial_misId_MisRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_MisRec_meanBuPartial_,
          *misId_MisRec_sigmaLBuPartial_, *misId_MisRec_sigmaRBuPartial_,
          *misId_MisRec_aLBuPartial_, *misId_MisRec_aRBuPartial_),
      buDeltaCutEffMisId_MisRec_(nullptr),
      deltaCutEffMisId_MisRec_(nullptr),
      deltaPartialCutEffMisId_MisRec_(nullptr),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_sigmaLBu_(("Bu2D0h_sigmaLBu_" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                           .c_str(),
                       // "", 8.8989e+01, 10, 150),
                       // Fixed from data
                       "", 1.1025e+02),
      Bu2D0h_sigmaRBu_(("Bu2D0h_sigmaRBu_" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                           .c_str(),
                       // "", 7.5978e+01, 10, 150),
                       // Fixed from data
                       "", 7.2797e+01),
      pdfBu_Bu2D0h_(
          ("pdfBu_Bu2D0h_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_meanBu(),
          Bu2D0h_sigmaLBu_, Bu2D0h_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_aRBu()),
      Bu2D0h_sigmaLBuPartial_(
          ("Bu2D0h_sigmaLBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          // "", 4.8679e+01, 10, 100),
          // Fixed from data
          "", 5.8654e+01),
      Bu2D0h_sigmaRBuPartial_(
          ("Bu2D0h_sigmaRBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          // "", 3.5437e+01, 10, 60),
          // Fixed from data
          "", 2.8177e+01),
      pdfBuPartial_Bu2D0h_(
          ("pdfBuPartial_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_meanBuPartial(),
          Bu2D0h_sigmaLBuPartial_, Bu2D0h_sigmaRBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_aRBuPartial()),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2D0h_meanBu_(("misId_Bu2D0h_meanBu_" +
                            ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                               .c_str(),
                           "", 5.6025e+03),
      misId_Bu2D0h_sigmaLBu_(
          ("misId_Bu2D0h_sigmaLBu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 1.0153e+02),
      misId_Bu2D0h_sigmaRBu_(
          ("misId_Bu2D0h_sigmaRBu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 8.5936e+01),
      misId_Bu2D0h_aLBu_(("misId_Bu2D0h_aLBu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", 1.9114e-10),
      misId_Bu2D0h_aRBu_(("misId_Bu2D0h_aRBu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", 1.8313e-08),
      pdfBu_misId_Bu2D0h_(("pdfBu_misId_Bu2D0h_" +
                           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                              .c_str(),
                          "", Configuration::Get().buDeltaMass(),
                          misId_Bu2D0h_meanBu_, misId_Bu2D0h_sigmaLBu_,
                          misId_Bu2D0h_sigmaRBu_, misId_Bu2D0h_aLBu_,
                          misId_Bu2D0h_aRBu_),
      misId_Bu2D0h_meanBuPartial_(
          ("misId_Bu2D0h_meanBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 5.5945e+03),
      misId_Bu2D0h_sigmaLBuPartial_(
          ("misId_Bu2D0h_sigmaLBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 5.4608e+01),
      misId_Bu2D0h_sigmaRBuPartial_(
          ("misId_Bu2D0h_sigmaRBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 4.5399e+01),
      misId_Bu2D0h_aLBuPartial_(
          ("misId_Bu2D0h_aLBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 1.1435e-01),
      misId_Bu2D0h_aRBuPartial_(
          ("misId_Bu2D0h_aRBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 2.6725e-01),
      pdfBuPartial_misId_Bu2D0h_(
          ("pdfBuPartial_misId_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), misId_Bu2D0h_meanBuPartial_,
          misId_Bu2D0h_sigmaLBuPartial_, misId_Bu2D0h_sigmaRBuPartial_,
          misId_Bu2D0h_aLBuPartial_, misId_Bu2D0h_aRBuPartial_),
      buDeltaCutEffMisId_Bu2D0h_(nullptr),
      deltaCutEffMisId_Bu2D0h_(nullptr),
      deltaPartialCutEffMisId_Bu2D0h_(nullptr),
      // -------------------- PART REC -------------------- //
      PartRec_D0pi0_sigmaLBu_(nullptr),
      PartRec_D0pi0_sigmaRBu_(nullptr),
      pdfBu_PartRec_D0pi0_(
          ("pdfBu_PartRec_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_D0pi0_meanBu(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
              .PartRec_D0pi0_sigmaLBu(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
              .PartRec_D0pi0_sigmaRBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_D0pi0_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_D0pi0_aRBu()),
      PartRec_D0gamma_sigmaLBu_(nullptr),
      PartRec_D0gamma_sigmaRBu_(nullptr),
      pdfBu_PartRec_D0gamma_(
          ("pdfBu_PartRec_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_D0gamma_meanBu(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
              .PartRec_D0gamma_sigmaLBu(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
              .PartRec_D0gamma_sigmaRBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_D0gamma_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_D0gamma_aRBu()),
      pdfBu_PartRec_(new RooAddPdf(
          ("pdfBu_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", RooArgSet(pdfBu_PartRec_D0pi0_, pdfBu_PartRec_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_frac_D0pi0())),
      PartRec_sigmaLBuPartial_(nullptr),
      PartRec_sigmaRBuPartial_(nullptr),
      pdfBuPartial_PartRec_(
          ("pdfBuPartial_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_meanBuPartial(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
              .PartRec_sigmaLBuPartial(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
              .PartRec_sigmaRBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_aRBuPartial()),
      // -------------------- Mis-ID ------------------- //
      misId_PartRec_meanBu_(Params::Get().CreateFixed(
          "misId_PartRec_meanBu", uniqueId, Neutral::gamma, Bachelor::k,
          5.1777e+03, 1.60e+00, Systematic::misIdPartRecKPdfBu,
          Sign::positive)),
      misId_PartRec_sigmaLBu_(Params::Get().CreateFixed(
          "misId_PartRec_sigmaLBu", uniqueId, Neutral::gamma, Bachelor::k,
          7.5677e+01, 9.46e-01, Systematic::misIdPartRecKPdfBu,
          Sign::positive)),
      misId_PartRec_sigmaRBu_(Params::Get().CreateFixed(
          "misId_PartRec_sigmaRBu", uniqueId, Neutral::gamma, Bachelor::k,
          9.4379e+01, 1.81e+00, Systematic::misIdPartRecKPdfBu,
          Sign::positive)),
      misId_PartRec_aLBu_(Params::Get().CreateFixed(
          "misId_PartRec_aLBu", uniqueId, Neutral::gamma, Bachelor::k,
          1.4242e-07, 9.03e-04, Systematic::misIdPartRecKPdfBu,
          Sign::positive)),
      misId_PartRec_aRBu_(Params::Get().CreateFixed(
          "misId_PartRec_aRBu", uniqueId, Neutral::gamma, Bachelor::k,
          1.5130e-01, 6.63e-03, Systematic::misIdPartRecKPdfBu,
          Sign::positive)),
      pdfBu_misId_PartRec_(("pdfBu_misId_PartRec_" +
                            ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                               .c_str(),
                           "", Configuration::Get().buDeltaMass(),
                           *misId_PartRec_meanBu_, *misId_PartRec_sigmaLBu_,
                           *misId_PartRec_sigmaRBu_, *misId_PartRec_aLBu_,
                           *misId_PartRec_aRBu_),
      misId_PartRec_meanBuPartial_(Params::Get().CreateFixed(
          "misId_PartRec_meanBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          5.1749e+03, 1.64e+00, Systematic::misIdPartRecKPdfBuPartial,
          Sign::positive)),
      misId_PartRec_sigmaLBuPartial_(Params::Get().CreateFixed(
          "misId_PartRec_sigmaLBuPartial", uniqueId, Neutral::gamma,
          Bachelor::k, 4.4104e+01, 1.73e+00,
          Systematic::misIdPartRecKPdfBuPartial, Sign::positive)),
      misId_PartRec_sigmaRBuPartial_(Params::Get().CreateFixed(
          "misId_PartRec_sigmaRBuPartial", uniqueId, Neutral::gamma,
          Bachelor::k, 8.2109e+01, 1.58e+00,
          Systematic::misIdPartRecKPdfBuPartial, Sign::positive)),
      misId_PartRec_aLBuPartial_(Params::Get().CreateFixed(
          "misId_PartRec_aLBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          6.3065e-02, 1.62e-02, Systematic::misIdPartRecKPdfBuPartial,
          Sign::positive)),
      misId_PartRec_aRBuPartial_(Params::Get().CreateFixed(
          "misId_PartRec_aRBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          1.7893e-01, 4.21e-03, Systematic::misIdPartRecKPdfBuPartial,
          Sign::positive)),
      pdfBuPartial_misId_PartRec_(
          ("pdfBuPartial_misId_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_PartRec_meanBuPartial_,
          *misId_PartRec_sigmaLBuPartial_, *misId_PartRec_sigmaRBuPartial_,
          *misId_PartRec_aLBuPartial_, *misId_PartRec_aRBuPartial_),
      buDeltaCutEffMisId_PartRec_(nullptr),
      deltaCutEffMisId_PartRec_(nullptr),
      deltaPartialCutEffMisId_PartRec_(nullptr),
      // -------------------- Bs2Dst0Kpi -------------------- //
      Bs2Dst0Kpi_thresholdDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_thresholdDelta", uniqueId, Neutral::gamma, Bachelor::k,
          5.3560e+02, 1e00, Systematic::NA, Sign::positive)),
      Bs2Dst0Kpi_aDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_aDelta", uniqueId, Neutral::gamma, Bachelor::k,
          -6.8532e-01, 1e00, Systematic::NA, Sign::none)),
      Bs2Dst0Kpi_bDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_bDelta", uniqueId, Neutral::gamma, Bachelor::k,
          -1.1526e-01, 1e00, Systematic::NA, Sign::none)),
      Bs2Dst0Kpi_cDelta_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_cDelta", uniqueId, Neutral::gamma, Bachelor::k,
          3.4981e+01, 1e00, Systematic::NA, Sign::positive)),
      pdfFlatDelta_Bs2Dst0Kpi_(
          ("pdfFlatDelta_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2Dst0Kpi_thresholdDelta_,
          *Bs2Dst0Kpi_cDelta_, *Bs2Dst0Kpi_aDelta_, *Bs2Dst0Kpi_bDelta_),
      Bs2Dst0Kpi_meanDeltaGamma_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_meanDeltaGamma", uniqueId, Neutral::gamma, Bachelor::k,
          1.4798e+02, 8.42e-01, Systematic::Bs2Dst0KpiDeltaPdf,
          Sign::positive)),
      Bs2Dst0Kpi_sigmaDeltaGamma_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigmaDeltaGamma", uniqueId, Neutral::gamma, Bachelor::k,
          4.3913e+00, 1.26e+00, Systematic::Bs2Dst0KpiDeltaPdf,
          Sign::positive)),
      pdfPeak1DeltaGamma_Bs2Dst0Kpi_(
          ("pdfPeak1DeltaGamma_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2Dst0Kpi_meanDeltaGamma_,
          *Bs2Dst0Kpi_sigmaDeltaGamma_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_a1Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0gamma_n1Delta()),
      pdfPeak2DeltaGamma_Bs2Dst0Kpi_(
          ("pdfPeak2DeltaGamma_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2Dst0Kpi_meanDeltaGamma_,
          *Bs2Dst0Kpi_sigmaDeltaGamma_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_a2Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0gamma_n2Delta()),
      pdfPeakDeltaGamma_Bs2Dst0Kpi_(
          ("pdfPeakDeltaGamma_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgList(pdfPeak1DeltaGamma_Bs2Dst0Kpi_,
                     pdfPeak2DeltaGamma_Bs2Dst0Kpi_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0gamma_fracPdf1Delta()),
      Bs2Dst0Kpi_fracPeakDeltaGamma_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_fracPeakDeltaGamma", uniqueId, Neutral::gamma,
          Bachelor::k, 1.9825e-01, 1.54e-02, Systematic::Bs2Dst0KpiDeltaPdf,
          Sign::positive)),
      Bs2Dst0Kpi_meanDeltaPi0_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_meanDeltaPi0", uniqueId, Neutral::gamma, Bachelor::k,
          8.3246e+01, 1e00, Systematic::NA, Sign::positive)),
      Bs2Dst0Kpi_sigmaDeltaPi0_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigmaDeltaPi0", uniqueId, Neutral::gamma, Bachelor::k,
          7.1822e+00, 6.29e-01, Systematic::Bs2Dst0KpiDeltaPdf,
          Sign::positive)),
      pdfPeak1DeltaPi0_Bs2Dst0Kpi_(
          ("pdfPeak1DeltaPi0_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2Dst0Kpi_meanDeltaPi0_,
          *Bs2Dst0Kpi_sigmaDeltaPi0_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_a1Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_n1Delta()),
      pdfPeak2DeltaPi0_Bs2Dst0Kpi_(
          ("pdfPeak2DeltaPi0_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bs2Dst0Kpi_meanDeltaPi0_,
          *Bs2Dst0Kpi_sigmaDeltaPi0_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_a2Delta(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_n2Delta()),
      pdfPeakDeltaPi0_Bs2Dst0Kpi_(
          ("pdfPeakDeltaPi0_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgList(pdfPeak1DeltaPi0_Bs2Dst0Kpi_,
                     pdfPeak2DeltaPi0_Bs2Dst0Kpi_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0pi0_fracPdf1Delta()),
      Bs2Dst0Kpi_fracPeakDeltaPi0_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_fracPeakDeltaPi0", uniqueId, Neutral::gamma, Bachelor::k,
          3.8063e-02, 9.22e-03, Systematic::Bs2Dst0KpiDeltaPdf,
          Sign::positive)),
      pdfDelta_Bs2Dst0Kpi_(
          ("pdfDelta_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "",
          RooArgList(pdfPeakDeltaGamma_Bs2Dst0Kpi_, pdfPeakDeltaPi0_Bs2Dst0Kpi_,
                     pdfFlatDelta_Bs2Dst0Kpi_),
          RooArgList(*Bs2Dst0Kpi_fracPeakDeltaGamma_,
                     *Bs2Dst0Kpi_fracPeakDeltaPi0_)),
      Bs2Dst0Kpi_mean1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_mean1Bu", uniqueId, Neutral::gamma, Bachelor::k, 5.2158e+03,
          4.38e-01, Systematic::Bs2Dst0KpiBuPdf, Sign::positive)),
      Bs2Dst0Kpi_sigma1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigma1Bu", uniqueId, Neutral::gamma, Bachelor::k,
          1.6977e+01, 3.42e-01, Systematic::Bs2Dst0KpiBuPdf, Sign::positive)),
      Bs2Dst0Kpi_a1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_a1Bu", uniqueId, Neutral::gamma, Bachelor::k, 4.8897e-01,
          1e00, Systematic::NA, Sign::positive)),
      Bs2Dst0Kpi_n1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_n1Bu", uniqueId, Neutral::gamma, Bachelor::k, 1.0000e+01,
          1e00, Systematic::NA, Sign::positive)),
      Bs2Dst0Kpi_mean2Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_mean2Bu", uniqueId, Neutral::gamma, Bachelor::k, 5.2082e+03,
          1e00, Systematic::NA, Sign::positive)),
      Bs2Dst0Kpi_sigma2Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigma2Bu", uniqueId, Neutral::gamma, Bachelor::k,
          8.5925e+01, 1e00, Systematic::NA, Sign::positive)),
      pdf1Bu_Bs2Dst0Kpi_(("pdf1Bu_Bs2Dst0Kpi_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", Configuration::Get().buDeltaMass(),
                         *Bs2Dst0Kpi_mean1Bu_, *Bs2Dst0Kpi_sigma1Bu_,
                         *Bs2Dst0Kpi_a1Bu_, *Bs2Dst0Kpi_n1Bu_),
      pdf2Bu_Bs2Dst0Kpi_(("pdf2Bu_Bs2Dst0Kpi_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", Configuration::Get().buDeltaMass(),
                         *Bs2Dst0Kpi_mean2Bu_, *Bs2Dst0Kpi_sigma2Bu_),
      Bs2Dst0Kpi_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_fracPdf1Bu", uniqueId, Neutral::gamma, Bachelor::k,
          6.4056e-01, 9.92e-03, Systematic::Bs2Dst0KpiBuPdf, Sign::positive)),
      pdfBu_Bs2Dst0Kpi_(
          new RooAddPdf(("pdfBu_Bs2Dst0Kpi_" +
                         ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "", RooArgList(pdf1Bu_Bs2Dst0Kpi_, pdf2Bu_Bs2Dst0Kpi_),
                        *Bs2Dst0Kpi_fracPdf1Bu_)),
      Bs2Dst0Kpi_meanBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_meanBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          5.2177e+03, 1.30e+00, Systematic::Bs2Dst0KpiBuPartialPdf,
          Sign::positive)),
      Bs2Dst0Kpi_sigmaLBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigmaLBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          3.2619e+01, 1.14e+00, Systematic::Bs2Dst0KpiBuPartialPdf,
          Sign::positive)),
      Bs2Dst0Kpi_sigmaRBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_sigmaRBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          3.5797e+01, 1.09e+00, Systematic::Bs2Dst0KpiBuPartialPdf,
          Sign::positive)),
      Bs2Dst0Kpi_aLBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_aLBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          1.3275e-01, 9.59e-03, Systematic::Bs2Dst0KpiBuPartialPdf,
          Sign::positive)),
      Bs2Dst0Kpi_aRBuPartial_(Params::Get().CreateFixed(
          "Bs2Dst0Kpi_aRBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          6.5298e-02, 8.39e-03, Systematic::Bs2Dst0KpiBuPartialPdf,
          Sign::positive)),
      pdfBuPartial_Bs2Dst0Kpi_(
          ("pdfBuPartial_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2Dst0Kpi_meanBuPartial_,
          *Bs2Dst0Kpi_sigmaLBuPartial_, *Bs2Dst0Kpi_sigmaRBuPartial_,
          *Bs2Dst0Kpi_aLBuPartial_, *Bs2Dst0Kpi_aRBuPartial_),
      buDeltaCutEffBs2Dst0Kpi_(nullptr),
      deltaCutEffBs2Dst0Kpi_(nullptr),
      deltaPartialCutEffBs2Dst0Kpi_(nullptr),
      // -------------------- Bs2D0Kpi -------------------- //
      Bs2D0Kpi_thresholdDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_thresholdDelta", uniqueId, Neutral::gamma, Bachelor::k,
          6.0000e+01, 2.39e-02, Systematic::Bs2D0KpiDeltaPdf, Sign::positive)),
      Bs2D0Kpi_aDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_aDelta", uniqueId, Neutral::gamma, Bachelor::k,
          5.4698e-01, 1.77e-01, Systematic::Bs2D0KpiDeltaPdf, Sign::none)),
      Bs2D0Kpi_bDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_bDelta", uniqueId, Neutral::gamma, Bachelor::k,
          -5.5240e-01, 2.29e-01, Systematic::Bs2D0KpiDeltaPdf, Sign::none)),
      Bs2D0Kpi_cDelta_(Params::Get().CreateFixed(
          "Bs2D0Kpi_cDelta", uniqueId, Neutral::gamma, Bachelor::k,
          4.7687e+01, 1e00, Systematic::NA, Sign::positive)),
      pdfDelta_Bs2D0Kpi_(("pdfDelta_Bs2D0Kpi_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", Configuration::Get().deltaMass(),
                         *Bs2D0Kpi_thresholdDelta_, *Bs2D0Kpi_cDelta_,
                         *Bs2D0Kpi_aDelta_, *Bs2D0Kpi_bDelta_),
      Bs2D0Kpi_mean1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_mean1Bu", uniqueId, Neutral::gamma, Bachelor::k, 5.2304e+03,
          3.81e+01, Systematic::Bs2D0KpiBuPdf, Sign::positive)),
      Bs2D0Kpi_sigma1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_sigma1Bu", uniqueId, Neutral::gamma, Bachelor::k, 9.3801e+01,
          2.32e+01, Systematic::Bs2D0KpiBuPdf, Sign::positive)),
      Bs2D0Kpi_a1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_a1Bu", uniqueId, Neutral::gamma, Bachelor::k, 2.9093e+00,
          1e00, Systematic::NA, Sign::positive)),
      Bs2D0Kpi_n1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_n1Bu", uniqueId, Neutral::gamma, Bachelor::k, 1.4041e-01,
          1e00, Systematic::NA, Sign::positive)),
      Bs2D0Kpi_mean2Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_mean2Bu", uniqueId, Neutral::gamma, Bachelor::k, 9.9628e+01,
          5.97e+00, Systematic::Bs2D0KpiBuPdf, Sign::positive)),
      Bs2D0Kpi_sigma2Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_sigma2Bu", uniqueId, Neutral::gamma, Bachelor::k, 1.4041e-01,
          1e00, Systematic::NA, Sign::positive)),
      pdf1Bu_Bs2D0Kpi_(("pdf1Bu_Bs2D0Kpi_" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                           .c_str(),
                       "", Configuration::Get().buDeltaMass(),
                       *Bs2D0Kpi_mean1Bu_, *Bs2D0Kpi_sigma1Bu_, *Bs2D0Kpi_a1Bu_,
                       *Bs2D0Kpi_n1Bu_),
      pdf2Bu_Bs2D0Kpi_(("pdf2Bu_Bs2D0Kpi_" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                           .c_str(),
                       "", Configuration::Get().buDeltaMass(),
                       *Bs2D0Kpi_mean2Bu_, *Bs2D0Kpi_sigma2Bu_),
      Bs2D0Kpi_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bs2D0Kpi_fracPdf1Bu", uniqueId, Neutral::gamma, Bachelor::k, 1.2273e-01,
          1e00, Systematic::NA, Sign::positive)),
      pdfBu_Bs2D0Kpi_(
          new RooAddPdf(("pdfBu_Bs2D0Kpi_" +
                         ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "", RooArgList(pdf1Bu_Bs2D0Kpi_, pdf2Bu_Bs2D0Kpi_),
                        *Bs2D0Kpi_fracPdf1Bu_)),
      Bs2D0Kpi_meanBuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kpi_meanBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          5.3230e+03, 9.23e+00, Systematic::Bs2D0KpiBuPartialPdf,
          Sign::positive)),
      Bs2D0Kpi_sigmaLBuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kpi_sigmaLBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          8.3476e+01, 5.23e+00, Systematic::Bs2D0KpiBuPartialPdf,
          Sign::positive)),
      Bs2D0Kpi_sigmaRBuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kpi_sigmaRBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          1.0900e+02, 1.01e+01, Systematic::Bs2D0KpiBuPartialPdf,
          Sign::positive)),
      Bs2D0Kpi_aLBuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kpi_aLBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          4.3590e-08, 2.85e-02, Systematic::Bs2D0KpiBuPartialPdf,
          Sign::positive)),
      Bs2D0Kpi_aRBuPartial_(Params::Get().CreateFixed(
          "Bs2D0Kpi_aRBuPartial", uniqueId, Neutral::gamma, Bachelor::k,
          2.6176e-10, 1.50e-01, Systematic::Bs2D0KpiBuPartialPdf,
          Sign::positive)),
      pdfBuPartial_Bs2D0Kpi_(
          ("pdfBuPartial_Bs2D0Kpi_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *Bs2D0Kpi_meanBuPartial_,
          *Bs2D0Kpi_sigmaLBuPartial_, *Bs2D0Kpi_sigmaRBuPartial_,
          *Bs2D0Kpi_aLBuPartial_, *Bs2D0Kpi_aRBuPartial_),
      buDeltaCutEffBs2D0Kpi_(nullptr),
      deltaCutEffBs2D0Kpi_(nullptr),
      deltaPartialCutEffBs2D0Kpi_(nullptr) {
  std::map<std::string, double> mapMisId_Bu2Dst0h_D0gamma;
  Configuration::Get().ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::k,
                                     mapMisId_Bu2Dst0h_D0gamma, true);
  buDeltaCutEffMisId_Bu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_Bu2Dst0h_D0gamma", uniqueId, Neutral::gamma,
          mapMisId_Bu2Dst0h_D0gamma["buDeltaCutEff"],
          mapMisId_Bu2Dst0h_D0gamma["buDeltaCutEffErr"],
          Systematic::buDeltaMisIdCutEffs, Sign::positive));
  deltaCutEffMisId_Bu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_Bu2Dst0h_D0gamma", uniqueId, Neutral::gamma,
          mapMisId_Bu2Dst0h_D0gamma["deltaCutEff"],
          mapMisId_Bu2Dst0h_D0gamma["deltaCutEffErr"],
          Systematic::deltaMisIdCutEffs, Sign::positive));

  std::map<std::string, double> mapMisId_Bu2Dst0h_D0pi0;
  Configuration::Get().ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::k,
                                     mapMisId_Bu2Dst0h_D0pi0, true);
  buDeltaCutEffMisId_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_Bu2Dst0h_D0pi0", uniqueId, Neutral::gamma,
          mapMisId_Bu2Dst0h_D0pi0["buDeltaCutEff"],
          mapMisId_Bu2Dst0h_D0pi0["buDeltaCutEffErr"],
          Systematic::buDeltaMisIdCutEffs, Sign::positive));
  deltaCutEffMisId_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_Bu2Dst0h_D0pi0", uniqueId, Neutral::gamma,
          mapMisId_Bu2Dst0h_D0pi0["deltaCutEff"],
          mapMisId_Bu2Dst0h_D0pi0["deltaCutEffErr"],
          Systematic::deltaMisIdCutEffs, Sign::positive));

  std::map<std::string, double> mapMisId_Bu2D0h;
  Configuration::Get().ReturnBoxEffs(Mode::Bu2D0pi, Bachelor::k,
                                     mapMisId_Bu2D0h, true);
  buDeltaCutEffMisId_Bu2D0h_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_Bu2D0h", uniqueId, Neutral::gamma,
          mapMisId_Bu2D0h["buDeltaCutEff"], mapMisId_Bu2D0h["buDeltaCutEffErr"],
          Systematic::NA, Sign::positive));
  deltaCutEffMisId_Bu2D0h_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_Bu2D0h", uniqueId, Neutral::gamma,
          mapMisId_Bu2D0h["deltaCutEff"], mapMisId_Bu2D0h["deltaCutEffErr"],
          Systematic::NA, Sign::positive));

  std::map<Mode, double> misRecModesMap = {
      {Mode::Bu2Dst0pi_D0pi0_WN,
       NeutralVars<Neutral::gamma>::Get(uniqueId)
               .fracMisRec_Bu2Dst0h_D0pi0_WN() /
           NeutralVars<Neutral::gamma>::Get(uniqueId).fracMisRec()},
      {Mode::Bu2Dst0pi_D0gamma_WN,
       NeutralVars<Neutral::gamma>::Get(uniqueId)
               .fracMisRec_Bu2Dst0h_D0gamma_WN() /
           NeutralVars<Neutral::gamma>::Get(uniqueId).fracMisRec()},
      {Mode::Bu2D0rho,
       NeutralVars<Neutral::gamma>::Get(uniqueId).fracMisRec_Bu2D0hst() /
           NeutralVars<Neutral::gamma>::Get(uniqueId).fracMisRec()},
      {Mode::Bd2Dstpi,
       NeutralVars<Neutral::gamma>::Get(uniqueId).fracMisRec_Bd2Dsth() /
           NeutralVars<Neutral::gamma>::Get(uniqueId).fracMisRec()}};

  std::map<std::string, double> mapMisId_MisRec;
  unsigned int it = 0;
  for (auto &m : misRecModesMap) {
    std::map<std::string, double> mapMisId_MisRecTmp;
    Configuration::Get().ReturnBoxEffs(m.first, Bachelor::k, mapMisId_MisRecTmp,
                                       true);
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
  buDeltaCutEffMisId_MisRec_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_MisRec", uniqueId, Neutral::gamma,
          mapMisId_MisRec["buDeltaCutEff"], mapMisId_MisRec["buDeltaCutEffErr"],
          Systematic::buDeltaMisIdCutEffs, Sign::positive));
  deltaCutEffMisId_MisRec_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_MisRec", uniqueId, Neutral::gamma,
          mapMisId_MisRec["deltaCutEff"], mapMisId_MisRec["deltaCutEffErr"],
          Systematic::deltaMisIdCutEffs, Sign::positive));

  std::map<Mode, double> partRecModesMap = {
      {Mode::Bu2Dst0rho_D0pi0,
       NeutralVars<Neutral::gamma>::Get(uniqueId)
               .fracPartRec_Bu2Dst0hst_D0pi0() /
           NeutralVars<Neutral::gamma>::Get(uniqueId).fracPartRec()},
      {Mode::Bu2Dst0rho_D0gamma,
       NeutralVars<Neutral::gamma>::Get(uniqueId)
               .fracPartRec_Bu2Dst0hst_D0gamma() /
           NeutralVars<Neutral::gamma>::Get(uniqueId).fracPartRec()}};

  std::map<std::string, double> mapMisId_PartRec;
  it = 0;
  for (auto &m : misRecModesMap) {
    std::map<std::string, double> mapMisId_PartRecTmp;
    Configuration::Get().ReturnBoxEffs(m.first, Bachelor::k,
                                       mapMisId_PartRecTmp, true);
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
  buDeltaCutEffMisId_PartRec_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffMisId_PartRec", uniqueId, Neutral::gamma,
          mapMisId_PartRec["buDeltaCutEff"],
          mapMisId_PartRec["buDeltaCutEffErr"], Systematic::buDeltaMisIdCutEffs,
          Sign::positive));
  deltaCutEffMisId_PartRec_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffMisId_PartRec", uniqueId, Neutral::gamma,
          mapMisId_PartRec["deltaCutEff"], mapMisId_PartRec["deltaCutEffErr"],
          Systematic::deltaMisIdCutEffs, Sign::positive));

  std::map<std::string, double> mapBs2Dst0Kpi;
  Configuration::Get().ReturnBoxEffs(Mode::Bs2Dst0Kpi, Bachelor::k,
                                     mapBs2Dst0Kpi, false);
  buDeltaCutEffBs2Dst0Kpi_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffBs2Dst0Kpi", uniqueId, Neutral::gamma, Bachelor::k,
          mapBs2Dst0Kpi["buDeltaCutEff"], mapBs2Dst0Kpi["buDeltaCutEffErr"],
          Systematic::buDeltaCutEffs, Sign::positive));
  deltaCutEffBs2Dst0Kpi_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffBs2Dst0Kpi", uniqueId, Neutral::gamma, Bachelor::k,
          mapBs2Dst0Kpi["deltaCutEff"], mapBs2Dst0Kpi["deltaCutEffErr"],
          Systematic::deltaCutEffs, Sign::positive));

  std::map<std::string, double> mapBs2D0Kpi;
  Configuration::Get().ReturnBoxEffs(Mode::Bs2D0Kpi, Bachelor::k, mapBs2D0Kpi,
                                     false);
  buDeltaCutEffBs2D0Kpi_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffBs2D0Kpi", uniqueId, Neutral::gamma, Bachelor::k,
          mapBs2D0Kpi["buDeltaCutEff"], mapBs2D0Kpi["buDeltaCutEffErr"],
          Systematic::buDeltaCutEffs, Sign::positive));
  deltaCutEffBs2D0Kpi_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "deltaCutEffBs2D0Kpi", uniqueId, Neutral::gamma, Bachelor::k,
      mapBs2D0Kpi["deltaCutEff"], mapBs2D0Kpi["deltaCutEffErr"],
      Systematic::deltaCutEffs, Sign::positive));

  if (Configuration::Get().fitBuPartial() == true) {
    deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffMisId_Bu2Dst0h_D0pi0", uniqueId, Neutral::gamma,
            mapMisId_Bu2Dst0h_D0pi0["deltaPartialCutEff"],
            mapMisId_Bu2Dst0h_D0pi0["deltaPartialCutEffErr"],
            Systematic::deltaPartialMisIdCutEffs, Sign::positive));
    deltaPartialCutEffMisId_Bu2D0h_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffMisId_Bu2D0h", uniqueId, Neutral::gamma,
            mapMisId_Bu2D0h["deltaPartialCutEff"],
            mapMisId_Bu2D0h["deltaPartialCutEffErr"],
            Systematic::NA, Sign::positive));
    deltaPartialCutEffMisId_MisRec_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffMisId_MisRec", uniqueId, Neutral::gamma,
            mapMisId_MisRec["deltaPartialCutEff"],
            mapMisId_MisRec["deltaPartialCutEffErr"],
            Systematic::deltaPartialMisIdCutEffs, Sign::positive));
    deltaPartialCutEffMisId_PartRec_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffMisId_PartRec", uniqueId, Neutral::gamma,
            mapMisId_PartRec["deltaPartialCutEff"],
            mapMisId_PartRec["deltaPartialCutEffErr"],
            Systematic::deltaPartialMisIdCutEffs, Sign::positive));
    deltaPartialCutEffBs2Dst0Kpi_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffBs2Dst0Kpi", uniqueId, Neutral::gamma,
            Bachelor::k, mapBs2Dst0Kpi["deltaPartialCutEff"],
            mapBs2Dst0Kpi["deltaPartialCutEffErr"],
            Systematic::deltaPartialCutEffs, Sign::positive));
    deltaPartialCutEffBs2D0Kpi_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffBs2D0Kpi", uniqueId, Neutral::gamma, Bachelor::k,
            mapBs2D0Kpi["deltaPartialCutEff"],
            mapBs2D0Kpi["deltaPartialCutEffErr"],
            Systematic::deltaPartialCutEffs, Sign::positive));
  }
}
