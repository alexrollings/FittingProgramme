#include "NeutralBachelorVars.h"
#include "Params.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- Bu2Dst0h_D0gamma -------------------- //
    : Bu2Dst0h_D0gamma_sigma1Bu_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0gamma_sigma1Bu", uniqueId, Neutral::gamma, Bachelor::pi,
          2.0271e+01, 15, 25)),
      Bu2Dst0h_D0gamma_sigma2Bu_(nullptr),
      pdf1Bu_Bu2Dst0h_D0gamma_(
          ("pdf1Bu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_meanBu(),
          *Bu2Dst0h_D0gamma_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0gamma_(
          ("pdf2Bu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_meanBu(),
          *Bu2Dst0h_D0gamma_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_n2Bu()),
      pdfBu_Bu2Dst0h_D0gamma_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0h_D0gamma_, pdf2Bu_Bu2Dst0h_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0gamma_fracPdf1Bu())),
      Bu2Dst0h_D0gamma_sigmaBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_sigmaBuPartial", uniqueId, Neutral::gamma,
          Bachelor::pi, 2.9969e+01, 2.68e+00, Systematic::crossFeedBuPartialPdf,
          Sign::positive)),
      pdfBuPartial_Bu2Dst0h_D0gamma_(
          ("pdfBuPartial_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0gamma_meanBuPartial(),
          *Bu2Dst0h_D0gamma_sigmaBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0gamma_aBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0gamma_nBuPartial()),
      mcEff_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0gamma", uniqueId, Neutral::gamma, Bachelor::pi,
          Configuration::Get().ReturnMCEff(Mode::Bu2Dst0pi_D0gamma,
                                           Neutral::gamma, Bachelor::pi, true),
          Configuration::Get().ReturnMCEff(Mode::Bu2Dst0pi_D0gamma,
                                           Neutral::gamma, Bachelor::pi, false),
          Systematic::mcEffs, Sign::positive)),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_meanBu", uniqueId, Neutral::gamma,
          Bachelor::pi, 5.2342e+03, 1.95e+00, Systematic::misIdGammaPiPdfBu,
          Sign::positive)),
      misId_Bu2Dst0h_D0gamma_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_sigma1Bu", uniqueId, Neutral::gamma,
          Bachelor::pi, 3.1068e+01, 1.77e+00, Systematic::misIdGammaPiPdfBu,
          Sign::positive)),
      misId_Bu2Dst0h_D0gamma_sigma2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_sigma2Bu", uniqueId, Neutral::gamma,
          Bachelor::pi, 2.2742e+01, 1.61e+00, Systematic::misIdGammaPiPdfBu,
          Sign::positive)),
      misId_Bu2Dst0h_D0gamma_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a1Bu", uniqueId, Neutral::gamma, Bachelor::pi,
          1.5478e-01, 1.46e-02, Systematic::misIdGammaPiPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_a2Bu_(nullptr),
      misId_Bu2Dst0h_D0gamma_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n1Bu", uniqueId, Neutral::gamma, Bachelor::pi,
          5.2558e-02, 2.08e-02, Systematic::misIdGammaPiPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_n2Bu_(nullptr),
      pdf1Bu_misId_Bu2Dst0h_D0gamma_(),
      pdf2Bu_misId_Bu2Dst0h_D0gamma_(),
      misId_Bu2Dst0h_D0gamma_fracPdf1Bu_(nullptr),
      pdfBu_misId_Bu2Dst0h_D0gamma_(new RooCruijff(
          ("pdfBu_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          *misId_Bu2Dst0h_D0gamma_meanBu_, *misId_Bu2Dst0h_D0gamma_sigma1Bu_,
          *misId_Bu2Dst0h_D0gamma_sigma2Bu_, *misId_Bu2Dst0h_D0gamma_a1Bu_,
          *misId_Bu2Dst0h_D0gamma_n1Bu_)),
      buDeltaCutEffMisId_Bu2Dst0h_D0gamma_(nullptr),
      deltaCutEffMisId_Bu2Dst0h_D0gamma_(nullptr),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      Bu2Dst0h_D0pi0_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_sigmaBu", uniqueId, Neutral::gamma, Bachelor::pi,
          4.4834e+01, 7.73e-01, Systematic::crossFeedBuPdf, Sign::positive)),
      pdf1Bu_Bu2Dst0h_D0pi0_(),
      pdf2Bu_Bu2Dst0h_D0pi0_(),
      pdfBu_Bu2Dst0h_D0pi0_(new RooCBShape(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigmaBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_n1Bu())),
      Bu2Dst0h_D0pi0_sigma1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_sigma1BuPartial", uniqueId, Neutral::gamma,
          Bachelor::pi, 2.5688e+01, 5.89e-01, Systematic::pi0BuPartialSigma1,
          Sign::positive)),
      Bu2Dst0h_D0pi0_sigma2BuPartial_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_sigma2BuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0h_D0pi0_sigma1BuPartial_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                        .Bu2Dst0h_D0pi0_21SigmaBuPartial()))),
      Bu2Dst0h_D0pi0_sigma3BuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_sigma3BuPartial", uniqueId, Neutral::gamma,
          Bachelor::pi, 2.0737e+01, 15, 25)),
      pdf1BuPartial_Bu2Dst0h_D0pi0_(
          ("pdf1BuPartial_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
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
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
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
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0pi0_meanGausBuPartial(),
          *Bu2Dst0h_D0pi0_sigma3BuPartial_),
      pdfBuPartial_Bu2Dst0h_D0pi0_(
          ("pdfBuPartial_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "",
          RooArgSet(pdf1BuPartial_Bu2Dst0h_D0pi0_,
                    pdf2BuPartial_Bu2Dst0h_D0pi0_,
                    pdf3BuPartial_Bu2Dst0h_D0pi0_),
          RooArgSet(NeutralVars<Neutral::gamma>::Get(uniqueId)
                        .Bu2Dst0h_D0pi0_fracPdfCb1BuPartial(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                        .Bu2Dst0h_D0pi0_fracPdfCb2BuPartial())),
      mcEff_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "mcEff_Bu2Dst0h_D0pi0", uniqueId, Neutral::gamma, Bachelor::pi,
          Configuration::Get().ReturnMCEff(Mode::Bu2Dst0pi_D0pi0,
                                           Neutral::gamma, Bachelor::pi, true),
          Configuration::Get().ReturnMCEff(Mode::Bu2Dst0pi_D0pi0,
                                           Neutral::gamma, Bachelor::pi, false),
          Systematic::mcEffs, Sign::positive)),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0pi0_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_meanBu", uniqueId, Neutral::gamma, Bachelor::pi,
          5.3011e+03, 5.57e+00, Systematic::misIdPi0PiPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma1Bu", uniqueId, Neutral::gamma,
          Bachelor::pi, 9.7560e+01, 3.46e+00, Systematic::misIdPi0PiPdfBu,
          Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigma2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma2Bu", uniqueId, Neutral::gamma,
          Bachelor::pi, 3.8035e+01, 5.31e+00, Systematic::misIdPi0PiPdfBu,
          Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1Bu", uniqueId, Neutral::gamma, Bachelor::pi,
          5.1893e-10, 1.26e-02, Systematic::misIdPi0PiPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a2Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1Bu", uniqueId, Neutral::gamma, Bachelor::pi,
          1.2790e-01, 3.92e-02, Systematic::misIdPi0PiPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_n2Bu_(nullptr),
      pdf1Bu_misId_Bu2Dst0h_D0pi0_(),
      pdf2Bu_misId_Bu2Dst0h_D0pi0_(),
      misId_Bu2Dst0h_D0pi0_fracPdf1Bu_(nullptr),
      pdfBu_misId_Bu2Dst0h_D0pi0_(new RooCruijff(
          ("pdfBu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_Bu2Dst0h_D0pi0_meanBu_,
          *misId_Bu2Dst0h_D0pi0_sigma1Bu_, *misId_Bu2Dst0h_D0pi0_sigma2Bu_,
          *misId_Bu2Dst0h_D0pi0_a1Bu_, *misId_Bu2Dst0h_D0pi0_n1Bu_)),
      misId_Bu2Dst0h_D0pi0_meanBuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_meanBuPartial", uniqueId, Neutral::gamma,
          Bachelor::pi, 5.2399e+03, 1.04e+00,
          Systematic::misIdPi0PiPdfBuPartial, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigma1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma1BuPartial", uniqueId, Neutral::gamma,
          Bachelor::pi, 5.4885e+01, 6.37e-01,
          Systematic::misIdPi0PiPdfBuPartial, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigma2BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma2BuPartial", uniqueId, Neutral::gamma,
          Bachelor::pi, 2.9684e+01, 8.43e-01,
          Systematic::misIdPi0PiPdfBuPartial, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1BuPartial", uniqueId, Neutral::gamma,
          Bachelor::pi, 5.6081e-07, 1.87e-03,
          Systematic::misIdPi0PiPdfBuPartial, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a2BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_n1BuPartial_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1BuPartial", uniqueId, Neutral::gamma,
          Bachelor::pi, 8.8162e-02, 6.58e-03,
          Systematic::misIdPi0PiPdfBuPartial, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_n2BuPartial_(nullptr),
      pdf1BuPartial_misId_Bu2Dst0h_D0pi0_(),
      pdf2BuPartial_misId_Bu2Dst0h_D0pi0_(),
      misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_(nullptr),
      pdfBuPartial_misId_Bu2Dst0h_D0pi0_(
          new RooCruijff(("pdfBuPartial_misId_Bu2Dst0h_D0pi0_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         "", Configuration::Get().buDeltaMass(),
                         *misId_Bu2Dst0h_D0pi0_meanBuPartial_,
                         *misId_Bu2Dst0h_D0pi0_sigma1BuPartial_,
                         *misId_Bu2Dst0h_D0pi0_sigma2BuPartial_,
                         *misId_Bu2Dst0h_D0pi0_a1BuPartial_,
                         *misId_Bu2Dst0h_D0pi0_n1BuPartial_)),
      buDeltaCutEffMisId_Bu2Dst0h_D0pi0_(nullptr),
      deltaCutEffMisId_Bu2Dst0h_D0pi0_(nullptr),
      deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_(nullptr),
      // -------------------- MIS-REC -------------------- //
      MisRec_sigmaLBu_(Params::Get().CreateFixed(
          "MisRec_sigmaLBu", uniqueId, Neutral::gamma, Bachelor::pi, 1.3446e+02,
          1.27e+00, Systematic::misRecBuPdf, Sign::positive)),
      MisRec_sigmaRBu_(Params::Get().CreateFixed(
          "MisRec_sigmaRBu", uniqueId, Neutral::gamma, Bachelor::pi, 8.5469e+01,
          5.55e-01, Systematic::misRecBuPdf, Sign::positive)),
      pdfBu_MisRec_(("pdfBu_MisRec_" +
                     ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_meanBu(),
                    *MisRec_sigmaLBu_, *MisRec_sigmaRBu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aLBu(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aRBu()),
      MisRec_sigmaLBuPartial_(Params::Get().CreateFixed(
          "MisRec_sigmaLBuPartial", uniqueId, Neutral::gamma, Bachelor::pi,
          1.1613e+02, 1.29e+00, Systematic::misRecBuPartialPdf,
          Sign::positive)),
      MisRec_sigmaRBuPartial_(Params::Get().CreateFixed(
          "MisRec_sigmaRBuPartial", uniqueId, Neutral::gamma, Bachelor::pi,
          4.5697e+01, 5.07e-01, Systematic::misRecBuPartialPdf,
          Sign::positive)),
      pdfBuPartial_MisRec_(
          ("pdfBuPartial_MisRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_meanBuPartial(),
          *MisRec_sigmaLBuPartial_, *MisRec_sigmaRBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aRBuPartial()),
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
      buDeltaCutEffMisId_MisRec_(nullptr),
      deltaCutEffMisId_MisRec_(nullptr),
      deltaPartialCutEffMisId_MisRec_(nullptr),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_sigmaLBu_(("Bu2D0h_sigmaLBu_" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                           .c_str(),
                       // "", 8.8989e+01, 10, 150),
                       // Fixed from data
                       "", 1.1076e+02),
      Bu2D0h_sigmaRBu_(("Bu2D0h_sigmaRBu_" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                           .c_str(),
                       // "", 7.5978e+01, 10, 150),
                       // Fixed from data
                       "", 7.2807e+01),
      pdfBu_Bu2D0h_(("pdfBu_Bu2D0h_" +
                     ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_meanBu(),
                    Bu2D0h_sigmaLBu_, Bu2D0h_sigmaRBu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_aLBu(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_aRBu()),
      Bu2D0h_sigmaLBuPartial_(
          ("Bu2D0h_sigmaLBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          // "", 4.8679e+01, 10, 90),
          // Fixed from data
          "", 5.8546e+01),
      Bu2D0h_sigmaRBuPartial_(
          ("Bu2D0h_sigmaRBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          // "", 3.5437e+01, 10, 60),
          // Fixed from data
          "", 3.2674e+01),
      pdfBuPartial_Bu2D0h_(
          ("pdfBuPartial_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_meanBuPartial(),
          Bu2D0h_sigmaLBuPartial_, Bu2D0h_sigmaRBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_aRBuPartial()),
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
      buDeltaCutEffMisId_Bu2D0h_(nullptr),
      deltaCutEffMisId_Bu2D0h_(nullptr),
      deltaPartialCutEffMisId_Bu2D0h_(nullptr),
      // -------------------- PART REC -------------------- //
      PartRec_D0pi0_sigmaLBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_sigmaLBu", uniqueId, Neutral::gamma, Bachelor::pi,
          8.3682e+01, 3.46e+00, Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0pi0_sigmaRBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_sigmaRBu", uniqueId, Neutral::gamma, Bachelor::pi,
          9.1998e+01, 3.41e+00, Systematic::partRecBuPdf, Sign::positive)),
      pdfBu_PartRec_D0pi0_(
          ("pdfBu_PartRec_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_D0pi0_meanBu(),
          *PartRec_D0pi0_sigmaLBu_, *PartRec_D0pi0_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_D0pi0_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_D0pi0_aRBu()),
      PartRec_D0gamma_sigmaLBu_(Params::Get().CreateFixed(
          "PartRec_D0gamma_sigmaLBu", uniqueId, Neutral::gamma, Bachelor::pi,
          3.6387e+01, 4.42e+00, Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0gamma_sigmaRBu_(Params::Get().CreateFixed(
          "PartRec_D0gamma_sigmaRBu", uniqueId, Neutral::gamma, Bachelor::pi,
          4.4390e+01, 4.55e+00, Systematic::partRecBuPdf, Sign::positive)),
      pdfBu_PartRec_D0gamma_(
          ("pdfBu_PartRec_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_D0gamma_meanBu(),
          *PartRec_D0gamma_sigmaLBu_, *PartRec_D0gamma_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_D0gamma_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_D0gamma_aRBu()),
      pdfBu_PartRec_(new RooAddPdf(
          ("pdfBu_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdfBu_PartRec_D0pi0_, pdfBu_PartRec_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_frac_D0pi0())),
      PartRec_sigmaLBuPartial_(Params::Get().CreateFixed(
          "PartRec_sigmaLBuPartial", uniqueId, Neutral::gamma, Bachelor::pi,
          4.7853e+01, 2.41e+00, Systematic::partRecBuPartialPdf,
          Sign::positive)),
      PartRec_sigmaRBuPartial_(Params::Get().CreateFixed(
          "PartRec_sigmaRBuPartial", uniqueId, Neutral::gamma, Bachelor::pi,
          3.3489e+01, 1.46e+00, Systematic::partRecBuPartialPdf,
          Sign::positive)),
      pdfBuPartial_PartRec_(
          ("pdfBuPartial_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_meanBuPartial(),
          *PartRec_sigmaLBuPartial_, *PartRec_sigmaRBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).PartRec_aRBuPartial()),
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
      buDeltaCutEffMisId_PartRec_(nullptr),
      deltaCutEffMisId_PartRec_(nullptr),
      deltaPartialCutEffMisId_PartRec_(nullptr) {
  std::map<std::string, double> mapMisId_Bu2Dst0h_D0gamma;
  Configuration::Get().ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
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
  Configuration::Get().ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
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

  if (Configuration::Get().fitBuPartial() == true) {
    deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "deltaPartialCutEffMisId_Bu2Dst0h_D0pi0", uniqueId, Neutral::gamma,
            mapMisId_Bu2Dst0h_D0pi0["deltaPartialCutEff"],
            mapMisId_Bu2Dst0h_D0pi0["deltaPartialCutEffErr"],
            Systematic::deltaPartialMisIdCutEffs, Sign::positive));
  }
}
