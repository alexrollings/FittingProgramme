#include "NeutralBachelorVars.h"
#include "Params.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- Bu2Dst0h_D0pi0 -------------------- //
    : Bu2Dst0h_D0pi0_sigmaBu_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_sigmaBu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_D0pi0_sigmaBu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .Bu2Dst0h_D0pi0_KpiSigmaBu()))),
      pdf1Bu_Bu2Dst0h_D0pi0_(
          ("pdf1Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0pi0_(
          ("pdf2Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_a2Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_n2Bu()),
      pdfBu_Bu2Dst0h_D0pi0_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0h_D0pi0_, pdf2Bu_Bu2Dst0h_D0pi0_),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_D0pi0_fracPdf1Bu())),
      Bu2Dst0h_D0pi0_sigma1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_sigma2BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_sigma3BuPartial_(nullptr),
      pdf1BuPartial_Bu2Dst0h_D0pi0_(),
      pdf2BuPartial_Bu2Dst0h_D0pi0_(),
      pdf3BuPartial_Bu2Dst0h_D0pi0_(),
      pdfBuPartial_Bu2Dst0h_D0pi0_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0pi0_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_meanBu", uniqueId, Neutral::pi0, Bachelor::k,
          5.3490e+03, 8.78e-01, Systematic::misIdPi0KPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma1Bu", uniqueId, Neutral::pi0, Bachelor::k,
          2.7590e+01, 2.03e+00, Systematic::misIdPi0KPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigma2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma2Bu", uniqueId, Neutral::pi0, Bachelor::k,
          4.1644e+01, 7.38e-01, Systematic::misIdPi0KPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1Bu", uniqueId, Neutral::pi0, Bachelor::k,
          8.5315e+00, 2.98e+00, Systematic::misIdPi0KPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a2Bu", uniqueId, Neutral::pi0, Bachelor::k,
          -5.1434e-01, 1.28e-02, Systematic::misIdPi0KPdfBu, Sign::negative)),
      misId_Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1Bu", uniqueId, Neutral::pi0, Bachelor::k,
          3.6223e+00, 6.58e+00, Systematic::misIdPi0KPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_n2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n2Bu", uniqueId, Neutral::pi0, Bachelor::k,
          10, 1, Systematic::NA, Sign::positive)),
      pdf1Bu_misId_Bu2Dst0h_D0pi0_(
          ("pdf1Bu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_Bu2Dst0h_D0pi0_meanBu_,
          *misId_Bu2Dst0h_D0pi0_sigma1Bu_, *misId_Bu2Dst0h_D0pi0_a1Bu_,
          *misId_Bu2Dst0h_D0pi0_n1Bu_),
      pdf2Bu_misId_Bu2Dst0h_D0pi0_(
          ("pdf2Bu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_Bu2Dst0h_D0pi0_meanBu_,
          *misId_Bu2Dst0h_D0pi0_sigma2Bu_, *misId_Bu2Dst0h_D0pi0_a2Bu_,
          *misId_Bu2Dst0h_D0pi0_n2Bu_),
      misId_Bu2Dst0h_D0pi0_fracPdf1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_fracPdf1Bu", uniqueId, Neutral::pi0, Bachelor::k,
          1.6070e-01, 1.94e-02, Systematic::misIdPi0KPdfBu, Sign::positive)),
      pdfBu_misId_Bu2Dst0h_D0pi0_(
          new RooAddPdf(("pdfBu_misId_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                            .c_str(),
                        "",
                        RooArgList(pdf1Bu_misId_Bu2Dst0h_D0pi0_,
                                   pdf2Bu_misId_Bu2Dst0h_D0pi0_),
                        *misId_Bu2Dst0h_D0pi0_fracPdf1Bu_)),
      misId_Bu2Dst0h_D0pi0_meanBuPartial_(nullptr),
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
      buDeltaCutEffMisId_Bu2Dst0h_D0pi0_(
          ("buDeltaCutEffMisId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1),
      deltaCutEffMisId_Bu2Dst0h_D0pi0_(
          ("deltaCutEffMisId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1),
      deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_(),
      // -------------------- Bu2Dst0h_D0gamma -------------------- //
      Bu2Dst0h_D0gamma_sigma1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_sigma1Bu", uniqueId, Neutral::pi0, Bachelor::k,
          3.3594e+01, 9.76e-01, Systematic::crossFeedBuPdf, Sign::positive)),
      Bu2Dst0h_D0gamma_sigma2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_sigma2Bu", uniqueId, Neutral::pi0, Bachelor::k,
          3.9267e+01, 1.22e+00, Systematic::crossFeedBuPdf, Sign::positive)),
      pdf1Bu_Bu2Dst0h_D0gamma_(),
      pdf2Bu_Bu2Dst0h_D0gamma_(),
      pdfBu_Bu2Dst0h_D0gamma_(new RooCruijff(
          ("pdfBu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_meanBu(),
          *Bu2Dst0h_D0gamma_sigma1Bu_, *Bu2Dst0h_D0gamma_sigma2Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_n1Bu())),
      Bu2Dst0h_D0gamma_sigmaBuPartial_(nullptr),
      pdfBuPartial_Bu2Dst0h_D0gamma_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_meanBu", uniqueId, Neutral::pi0, Bachelor::k,
          5.3601e+03, 2.18e+00, Systematic::misIdGammaKPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_sigma1Bu", uniqueId, Neutral::pi0, Bachelor::k,
          3.7321e+01, 1.90e+00, Systematic::misIdGammaKPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_sigma2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_sigma2Bu", uniqueId, Neutral::pi0, Bachelor::k,
          7.3708e+01, 2.55e+00, Systematic::misIdGammaKPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a1Bu", uniqueId, Neutral::pi0, Bachelor::k,
          1.2785e-01, 1.46e-02, Systematic::misIdGammaKPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_a2Bu_(nullptr),
      misId_Bu2Dst0h_D0gamma_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n1Bu", uniqueId, Neutral::pi0, Bachelor::k,
          1.6726e-01, 9.78e-03, Systematic::misIdGammaKPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_n2Bu_(nullptr),
      pdf1Bu_misId_Bu2Dst0h_D0gamma_(),
      pdf2Bu_misId_Bu2Dst0h_D0gamma_(),
      misId_Bu2Dst0h_D0gamma_fracPdf1Bu_(nullptr),
      pdfBu_misId_Bu2Dst0h_D0gamma_(new RooCruijff(
          ("pdfBu_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_Bu2Dst0h_D0gamma_meanBu_,
          *misId_Bu2Dst0h_D0gamma_sigma1Bu_, *misId_Bu2Dst0h_D0gamma_sigma2Bu_,
          *misId_Bu2Dst0h_D0gamma_a1Bu_, *misId_Bu2Dst0h_D0gamma_n1Bu_)),
      buDeltaCutEffMisId_Bu2Dst0h_D0gamma_(
          ("buDeltaCutEffMisId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1),
      deltaCutEffMisId_Bu2Dst0h_D0gamma_(
          ("deltaCutEffMisId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1),
      // -------------------- MIS-REC -------------------- //
      MisRec_sigmaLBu_(Params::Get().CreateFixed(
          "MisRec_sigmaLBu", uniqueId, Neutral::pi0, Bachelor::k, 5.7157e+01,
          6.09e+00, Systematic::misRecBuPdf, Sign::positive)),
      MisRec_sigmaRBu_(Params::Get().CreateFixed(
          "MisRec_sigmaRBu", uniqueId, Neutral::pi0, Bachelor::k, 5.5962e+01,
          4.14e+00, Systematic::misRecBuPdf, Sign::positive)),
      pdfBu_MisRec_(
          ("pdfBu_MisRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_meanBu(),
          *MisRec_sigmaLBu_, *MisRec_sigmaRBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_aLBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_aRBu()),
      MisRec_sigmaLBuPartial_(nullptr),
      MisRec_sigmaRBuPartial_(nullptr),
      pdfBuPartial_MisRec_(),
      // -------------------- Mis-ID ------------------- //
      misId_MisRec_mean1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_mean1Bu", uniqueId, Neutral::pi0, Bachelor::k,
          5.3333e+03, 7.09e-01, Systematic::misIdMisRecKPdfBu, Sign::positive)),
      misId_MisRec_mean2Bu_(nullptr),
      misId_MisRec_sigma1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_sigma1Bu", uniqueId, Neutral::pi0, Bachelor::k,
          2.6027e+01, 6.06e-01, Systematic::misIdMisRecKPdfBu, Sign::positive)),
      misId_MisRec_sigma2Bu_(Params::Get().CreateFixed(
          "misId_MisRec_sigma2Bu", uniqueId, Neutral::pi0, Bachelor::k,
          6.2136e+01, 8.88e-01, Systematic::misIdMisRecKPdfBu, Sign::positive)),
      misId_MisRec_a1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_a1Bu", uniqueId, Neutral::pi0, Bachelor::k,
          2.5413e-01, 6.21e-03, Systematic::misIdMisRecKPdfBu, Sign::positive)),
      misId_MisRec_a2Bu_(nullptr),
      misId_MisRec_n1Bu_(Params::Get().CreateFixed(
          "misId_MisRec_n1Bu", uniqueId, Neutral::pi0, Bachelor::k,
          2.4686e-01, 5.18e-03, Systematic::misIdMisRecKPdfBu, Sign::positive)),
      misId_MisRec_n2Bu_(nullptr),
      pdf1Bu_misId_MisRec_(),
      pdf2Bu_misId_MisRec_(),
      misId_MisRec_fracPdf1Bu_(nullptr),
      pdfBu_misId_MisRec_(new RooCruijff(
          ("pdfBu_misId_MisRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_MisRec_mean1Bu_,
          *misId_MisRec_sigma1Bu_, *misId_MisRec_sigma2Bu_,
          *misId_MisRec_a1Bu_, *misId_MisRec_n1Bu_)),
      misId_MisRec_meanBuPartial_(nullptr),
      misId_MisRec_sigmaLBuPartial_(nullptr),
      misId_MisRec_sigmaRBuPartial_(nullptr),
      misId_MisRec_aLBuPartial_(nullptr),
      misId_MisRec_aRBuPartial_(nullptr),
      pdfBuPartial_misId_MisRec_(),
      buDeltaCutEffMisId_MisRec_(
          ("buDeltaCutEffMisId_MisRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1),
      deltaCutEffMisId_MisRec_(
          ("deltaCutEffMisId_MisRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1),
      deltaPartialCutEffMisId_MisRec_(),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_sigmaLBu_(("Bu2D0h_sigmaLBu_" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                           .c_str(),
                       // "", 3.3137e+01, 10, 100),
                       // Fixed from data
                       // "", 4.1529e+01),
                       // Fixed from data
                       "", 4.8647e+01),
      Bu2D0h_sigmaRBu_(("Bu2D0h_sigmaRBu_" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                           .c_str(),
                       // "", 4.0080e+01, 10, 80),
                       // Fixed from data
                       // "", 3.4501e+01),
                       // Fixed from data
                       "", 3.2605e+01),
      pdfBu_Bu2D0h_(
          ("pdfBu_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0h_meanBu(),
          // NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
          //     .Bu2D0h_sigmaLBu(),
          // NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
          //     .Bu2D0h_sigmaRBu(),
          Bu2D0h_sigmaLBu_, Bu2D0h_sigmaRBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0h_aLBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0h_aRBu()),
      Bu2D0h_sigmaLBuPartial_(),
      Bu2D0h_sigmaRBuPartial_(),
      pdfBuPartial_Bu2D0h_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2D0h_meanBu_(("misId_Bu2D0h_meanBu_" +
                            ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                               .c_str(),
                           "", 5.5539e+03),
      misId_Bu2D0h_sigmaLBu_(("misId_Bu2D0h_sigmaLBu_" +
                              ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                                 .c_str(),
                             "", 3.5503e+01),
      misId_Bu2D0h_sigmaRBu_(("misId_Bu2D0h_sigmaRBu_" +
                              ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                                 .c_str(),
                             "", 6.4701e+01),
      misId_Bu2D0h_aLBu_(("misId_Bu2D0h_aLBu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                             .c_str(),
                         "", 1.4758e-01),
      misId_Bu2D0h_aRBu_(("misId_Bu2D0h_aRBu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                             .c_str(),
                         "", 1.2704e-01),
      pdfBu_misId_Bu2D0h_(("pdfBu_misId_Bu2D0h_" +
                           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
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
      buDeltaCutEffMisId_Bu2D0h_(
          ("buDeltaCutEffMisId_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1),
      deltaCutEffMisId_Bu2D0h_(
          ("deltaCutEffMisId_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1),
      deltaPartialCutEffMisId_Bu2D0h_(),
      // -------------------- PART REC -------------------- //
      PartRec_D0pi0_sigmaLBu_(nullptr),
      PartRec_D0pi0_sigmaRBu_(nullptr),
      pdfBu_PartRec_D0pi0_(),
      PartRec_D0gamma_sigmaLBu_(nullptr),
      PartRec_D0gamma_sigmaRBu_(nullptr),
      pdfBu_PartRec_D0gamma_(),
      pdfBu_PartRec_(new RooCruijff(
          ("pdfBu_PartRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).PartRec_D0pi0_meanBu(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
              .PartRec_D0pi0_sigmaLBu(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
              .PartRec_D0pi0_sigmaRBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).PartRec_D0pi0_aLBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).PartRec_D0pi0_aRBu())),
      PartRec_sigmaLBuPartial_(nullptr),
      PartRec_sigmaRBuPartial_(nullptr),
      pdfBuPartial_PartRec_(),
      // -------------------- Mis-ID ------------------- //
      misId_PartRec_meanBu_(Params::Get().CreateFixed(
          "misId_PartRec_meanBu", uniqueId, Neutral::pi0, Bachelor::k,
          5.1582e+03, 1.27e+00, Systematic::misIdPartRecKPdfBu, Sign::positive)),
      misId_PartRec_sigmaLBu_(Params::Get().CreateFixed(
          "misId_PartRec_sigmaLBu", uniqueId, Neutral::pi0, Bachelor::k,
          4.5612e+01, 2.40e+00, Systematic::misIdPartRecKPdfBu, Sign::positive)),
      misId_PartRec_sigmaRBu_(Params::Get().CreateFixed(
          "misId_PartRec_sigmaRBu", uniqueId, Neutral::pi0, Bachelor::k,
          7.7901e+01, 7.10e+00, Systematic::misIdPartRecKPdfBu, Sign::positive)),
      misId_PartRec_aLBu_(Params::Get().CreateFixed(
          "misId_PartRec_aLBu", uniqueId, Neutral::pi0, Bachelor::k,
          1.8171e-09, 3.43e-02, Systematic::misIdPartRecKPdfBu, Sign::positive)),
      misId_PartRec_aRBu_(Params::Get().CreateFixed(
          "misId_PartRec_aRBu", uniqueId, Neutral::pi0, Bachelor::k,
          2.1857e-01, 3.11e-02, Systematic::misIdPartRecKPdfBu, Sign::positive)),
      pdfBu_misId_PartRec_(
          ("pdfBu_misId_PartRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_PartRec_meanBu_,
          *misId_PartRec_sigmaLBu_, *misId_PartRec_sigmaRBu_,
          *misId_PartRec_aLBu_, *misId_PartRec_aRBu_),
      misId_PartRec_meanBuPartial_(nullptr),
      misId_PartRec_sigmaLBuPartial_(nullptr),
      misId_PartRec_sigmaRBuPartial_(nullptr),
      misId_PartRec_aLBuPartial_(nullptr),
      misId_PartRec_aRBuPartial_(nullptr),
      pdfBuPartial_misId_PartRec_(),
      buDeltaCutEffMisId_PartRec_(
          ("buDeltaCutEffMisId_PartRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1),
      deltaCutEffMisId_PartRec_(
          ("deltaCutEffMisId_PartRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1),
      deltaPartialCutEffMisId_PartRec_(),
      // -------------------- Bs2Dst0Kpi -------------------- //
      Bs2Dst0Kpi_thresholdDelta_(
          ("Bs2Dst0Kpi_thresholdDelta_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1.3627e+02),
      Bs2Dst0Kpi_aDelta_(("Bs2Dst0Kpi_aDelta_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                             .c_str(),
                         "", -7.8318e+00),
      Bs2Dst0Kpi_bDelta_(("Bs2Dst0Kpi_bDelta_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                             .c_str(),
                         "", 7.3621e-02),
      Bs2Dst0Kpi_cDelta_(("Bs2Dst0Kpi_cDelta_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                             .c_str(),
                         "", 1.5459e+01),
      pdfFlatDelta_Bs2Dst0Kpi_(
          ("pdfFlatDelta_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), Bs2Dst0Kpi_thresholdDelta_,
          Bs2Dst0Kpi_cDelta_, Bs2Dst0Kpi_aDelta_, Bs2Dst0Kpi_bDelta_),
      Bs2Dst0Kpi_meanDeltaPi0_(
          ("Bs2Dst0Kpi_meanDeltaPi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1.4249e+02),
      Bs2Dst0Kpi_sigmaDeltaPi0_(
          ("Bs2Dst0Kpi_sigmaDeltaPi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1.9311e+00),
      pdfPeak1DeltaPi0_Bs2Dst0Kpi_(
          ("pdfPeak1DeltaPi0_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), Bs2Dst0Kpi_meanDeltaPi0_,
          Bs2Dst0Kpi_sigmaDeltaPi0_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_a1Delta(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_n1Delta()),
      pdfPeak2DeltaPi0_Bs2Dst0Kpi_(
          ("pdfPeak2DeltaPi0_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().deltaMass(), Bs2Dst0Kpi_meanDeltaPi0_,
          Bs2Dst0Kpi_sigmaDeltaPi0_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_a2Delta(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_n2Delta()),
      pdfPeakDeltaPi0_Bs2Dst0Kpi_(
          ("pdfPeakDeltaPi0_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "",
          RooArgList(pdfPeak1DeltaPi0_Bs2Dst0Kpi_,
                     pdfPeak2DeltaPi0_Bs2Dst0Kpi_),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_D0pi0_fracPdf1Delta()),
      Bs2Dst0Kpi_fracPeakDeltaPi0_(
          ("Bs2Dst0Kpi_fracPeakDeltaPi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 6.4451e-01),
      pdfDelta_Bs2Dst0Kpi_(
          ("pdfDelta_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", RooArgList(pdfPeakDeltaPi0_Bs2Dst0Kpi_, pdfFlatDelta_Bs2Dst0Kpi_),
          Bs2Dst0Kpi_fracPeakDeltaPi0_),
      Bs2Dst0Kpi_meanDeltaGamma_(),
      Bs2Dst0Kpi_sigmaDeltaGamma_(),
      pdfPeak1DeltaGamma_Bs2Dst0Kpi_(),
      pdfPeak2DeltaGamma_Bs2Dst0Kpi_(),
      pdfPeakDeltaGamma_Bs2Dst0Kpi_(),
      Bs2Dst0Kpi_fracPeakDeltaGamma_(),
      Bs2Dst0Kpi_mean1Bu_(("Bs2Dst0Kpi_mean1Bu_" +
                           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                              .c_str(),
                          "", 5.2065e+03),
      Bs2Dst0Kpi_sigma1Bu_(("Bs2Dst0Kpi_sigma1Bu_" +
                            ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                               .c_str(),
                           "", 3.1366e+01),
      Bs2Dst0Kpi_sigma2Bu_(("Bs2Dst0Kpi_sigma2Bu_" +
                            ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                               .c_str(),
                           "", 2.3145e+01),
      Bs2Dst0Kpi_aLBu_(("Bs2Dst0Kpi_aLBu_" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                           .c_str(),
                       "", 6.0169e-02),
      Bs2Dst0Kpi_aRBu_(("Bs2Dst0Kpi_aRBu_" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                           .c_str(),
                       "", 7.1721e-02),
      pdfBu_Bs2Dst0Kpi_(new RooCruijff(
          ("pdfBu_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), Bs2Dst0Kpi_mean1Bu_,
          Bs2Dst0Kpi_sigma1Bu_, Bs2Dst0Kpi_sigma2Bu_, Bs2Dst0Kpi_aLBu_,
          Bs2Dst0Kpi_aRBu_)),
      Bs2Dst0Kpi_mean2Bu_(),
      Bs2Dst0Kpi_a1Bu_(),
      Bs2Dst0Kpi_n1Bu_(),
      pdf1Bu_Bs2Dst0Kpi_(),
      pdf2Bu_Bs2Dst0Kpi_(),
      Bs2Dst0Kpi_fracPdf1Bu_(),
      Bs2Dst0Kpi_meanBuPartial_(),
      Bs2Dst0Kpi_sigmaLBuPartial_(),
      Bs2Dst0Kpi_sigmaRBuPartial_(),
      Bs2Dst0Kpi_aLBuPartial_(),
      Bs2Dst0Kpi_aRBuPartial_(),
      pdfBuPartial_Bs2Dst0Kpi_(),
      buDeltaCutEffBs2Dst0Kpi_(
          ("buDeltaCutEffBs2Dst0Kpi_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1),  //, -1, 1),
      deltaCutEffBs2Dst0Kpi_(("deltaCutEffBs2Dst0Kpi_" +
                              ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                                 .c_str(),
                             "", 1),
      deltaPartialCutEffBs2Dst0Kpi_(),
      // -------------------- Bs2D0Kpi -------------------- //
      Bs2D0Kpi_thresholdDelta_(),
      Bs2D0Kpi_aDelta_(),
      Bs2D0Kpi_bDelta_(),
      Bs2D0Kpi_cDelta_(),
      pdfDelta_Bs2D0Kpi_(("pdfDelta_Bs2D0Kpi_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                             .c_str(),
                         "", Configuration::Get().deltaMass(),
                         Bs2Dst0Kpi_thresholdDelta_, Bs2Dst0Kpi_cDelta_,
                         Bs2Dst0Kpi_aDelta_, Bs2Dst0Kpi_bDelta_),
      Bs2D0Kpi_mean1Bu_(("Bs2D0Kpi_meanBu_" +
                         ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                            .c_str(),
                        "", 5.3384e+03),
      Bs2D0Kpi_sigma1Bu_(("Bs2D0Kpi_sigmaBu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                             .c_str(),
                         "", 8.2330e+01),
      pdfBu_Bs2D0Kpi_(new RooGaussian(
          ("pdfBu_Bs2D0Kpi_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), Bs2D0Kpi_mean1Bu_,
          Bs2D0Kpi_sigma1Bu_)),
      Bs2D0Kpi_mean2Bu_(),
      Bs2D0Kpi_sigma2Bu_(),
      Bs2D0Kpi_a1Bu_(),
      Bs2D0Kpi_n1Bu_(),
      pdf1Bu_Bs2D0Kpi_(),
      pdf2Bu_Bs2D0Kpi_(),
      Bs2D0Kpi_fracPdf1Bu_(),
      Bs2D0Kpi_meanBuPartial_(),
      Bs2D0Kpi_sigmaLBuPartial_(),
      Bs2D0Kpi_sigmaRBuPartial_(),
      Bs2D0Kpi_aLBuPartial_(),
      Bs2D0Kpi_aRBuPartial_(),
      pdfBuPartial_Bs2D0Kpi_(),
      buDeltaCutEffBs2D0Kpi_(("buDeltaCutEffBs2D0Kpi_" +
                              ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                                 .c_str(),
                             "", 1),  //, -1, 1),
      deltaCutEffBs2D0Kpi_(("deltaCutEffBs2D0Kpi_" +
                            ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                               .c_str(),
                           "", 1),
      deltaPartialCutEffBs2D0Kpi_() {
  std::map<std::string, double> mapMisId_Bu2Dst0h_D0pi0;
  Configuration::Get().ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::k,
                                       mapMisId_Bu2Dst0h_D0pi0, true);
  buDeltaCutEffMisId_Bu2Dst0h_D0pi0_.setVal(mapMisId_Bu2Dst0h_D0pi0["buDeltaCutEff"]);
  deltaCutEffMisId_Bu2Dst0h_D0pi0_.setVal(mapMisId_Bu2Dst0h_D0pi0["deltaCutEff"]);

  std::map<std::string, double> mapMisId_Bu2Dst0h_D0gamma;
  Configuration::Get().ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::k,
                                       mapMisId_Bu2Dst0h_D0gamma, true);
  buDeltaCutEffMisId_Bu2Dst0h_D0gamma_.setVal(mapMisId_Bu2Dst0h_D0gamma["buDeltaCutEff"]);
  deltaCutEffMisId_Bu2Dst0h_D0gamma_.setVal(mapMisId_Bu2Dst0h_D0gamma["deltaCutEff"]);

  std::map<Mode, double> misRecModesMap = {
      {Mode::Bu2Dst0pi_D0pi0_WN,
       NeutralVars<Neutral::pi0>::Get(uniqueId).fracMisRec_Bu2Dst0h_D0pi0_WN() /
           NeutralVars<Neutral::pi0>::Get(uniqueId).fracMisRec()},
      {Mode::Bu2Dst0pi_D0gamma,
       NeutralVars<Neutral::pi0>::Get(uniqueId).fracMisRec_Bu2Dst0h_D0gamma() /
           NeutralVars<Neutral::pi0>::Get(uniqueId).fracMisRec()},
      {Mode::Bu2Dst0pi_D0gamma_WN,
       NeutralVars<Neutral::pi0>::Get(uniqueId)
               .fracMisRec_Bu2Dst0h_D0gamma_WN() /
           NeutralVars<Neutral::pi0>::Get(uniqueId).fracMisRec()},
      {Mode::Bu2D0rho,
       NeutralVars<Neutral::pi0>::Get(uniqueId).fracMisRec_Bu2D0hst() /
           NeutralVars<Neutral::pi0>::Get(uniqueId).fracMisRec()},
      {Mode::Bd2Dstpi,
       NeutralVars<Neutral::pi0>::Get(uniqueId).fracMisRec_Bd2Dsth() /
           NeutralVars<Neutral::pi0>::Get(uniqueId).fracMisRec()}};

  double buDeltaCutEffMisId_MisRecVal = 0.0;
  double deltaCutEffMisId_MisRecVal = 0.0;

  for (auto &m : misRecModesMap) {
    RooRealVar buDeltaCutEffMisIdTemp(
        ("buDeltaCutEffMisIdTemp" + ComposeName(uniqueId, Neutral::pi0))
            .c_str(),
        "", 1);
    RooRealVar deltaCutEffMisIdTemp(
        ("deltaCutEffMisIdTemp" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
        "", 1);

    Configuration::Get().SetEfficiencies(m.first, Bachelor::k,
                                         buDeltaCutEffMisIdTemp,
                                         deltaCutEffMisIdTemp, true);

    buDeltaCutEffMisId_MisRecVal += buDeltaCutEffMisIdTemp.getVal() * m.second;
    deltaCutEffMisId_MisRecVal += deltaCutEffMisIdTemp.getVal() * m.second;
  }
  buDeltaCutEffMisId_MisRec_.setVal(buDeltaCutEffMisId_MisRecVal);
  deltaCutEffMisId_MisRec_.setVal(deltaCutEffMisId_MisRecVal);
  // std::cout << "\t buDeltaCutEffMisId_MisRec = "
  //           << buDeltaCutEffMisId_MisRec_.getVal() << "\n"
  //           << "\t deltaCutEffMisId_MisRec = "
  //           << deltaCutEffMisId_MisRec_.getVal() << "\n";

  Configuration::Get().SetEfficiencies(Mode::Bu2D0pi, Bachelor::k,
                                       buDeltaCutEffMisId_Bu2D0h_,
                                       deltaCutEffMisId_Bu2D0h_, true);
  Configuration::Get().SetEfficiencies(Mode::Bu2Dst0rho_D0pi0, Bachelor::k,
                                       buDeltaCutEffMisId_PartRec_,
                                       deltaCutEffMisId_PartRec_, true);

  Configuration::Get().SetEfficiencies(Mode::Bs2Dst0Kpi, Bachelor::k,
                                       buDeltaCutEffBs2Dst0Kpi_,
                                       deltaCutEffBs2Dst0Kpi_, false);
  Configuration::Get().SetEfficiencies(Mode::Bs2D0Kpi, Bachelor::k,
                                       buDeltaCutEffBs2D0Kpi_,
                                       deltaCutEffBs2D0Kpi_, false);
}
