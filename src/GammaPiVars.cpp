#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- A CP initial value -------------------- //
    : A_CP_init_(-0.003),
      // -------------------- Bu2Dst0h_D0gamma -------------------- //
      Bu2Dst0h_D0gamma_sigma1Bu_(
          new RooRealVar(("Bu2Dst0h_D0gamma_sigma1Bu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         "", 2.0271e+01, 15, 25)),
      // Fixed from data
      // "", 1.9360e+01)),
      // Fixed for partial box scan
      // "", 1.9913e+01)),
      Bu2Dst0h_D0gamma_sigma2Bu_(),
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
      Bu2Dst0h_D0gamma_sigmaBuPartial_(
          ("Bu2Dst0h_D0gamma_sigmaBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 3.0651e+01),
      pdfBuPartial_Bu2Dst0h_D0gamma_(
          ("pdfBuPartial_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0gamma_meanBuPartial(),
          Bu2Dst0h_D0gamma_sigmaBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0gamma_aBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0gamma_nBuPartial()),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_meanBu_(
          ("misId_Bu2Dst0h_D0gamma_meanBu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 5.2359e+03),
      misId_Bu2Dst0h_D0gamma_sigma1Bu_(
          ("misId_Bu2Dst0h_D0gamma_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 3.1411e+01),
      misId_Bu2Dst0h_D0gamma_sigma2Bu_(
          ("misId_Bu2Dst0h_D0gamma_sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 2.1604e+01),
      misId_Bu2Dst0h_D0gamma_a1Bu_(
          ("misId_Bu2Dst0h_D0gamma_a1Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 1.5167e-01),
      misId_Bu2Dst0h_D0gamma_a2Bu_(
          ("misId_Bu2Dst0h_D0gamma_a2Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 5.7501e-02),
      misId_Bu2Dst0h_D0gamma_n1Bu_(),
      misId_Bu2Dst0h_D0gamma_n2Bu_(),
      pdf1Bu_misId_Bu2Dst0h_D0gamma_(),
      pdf2Bu_misId_Bu2Dst0h_D0gamma_(),
      misId_Bu2Dst0h_D0gamma_fracPdf1Bu_(),
      pdfBu_misId_Bu2Dst0h_D0gamma_(new RooCruijff(
          ("pdfBu_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          misId_Bu2Dst0h_D0gamma_meanBu_, misId_Bu2Dst0h_D0gamma_sigma1Bu_,
          misId_Bu2Dst0h_D0gamma_sigma2Bu_, misId_Bu2Dst0h_D0gamma_a1Bu_,
          misId_Bu2Dst0h_D0gamma_a2Bu_)),
      orEffMisId_Bu2Dst0h_D0gamma_(
          ("orEffMisId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 1),
      boxEffMisId_Bu2Dst0h_D0gamma_(
          ("boxEffMisId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 1),
      buDeltaCutEffMisId_Bu2Dst0h_D0gamma_(
          ("buDeltaCutEffMisId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 1),
      deltaCutEffMisId_Bu2Dst0h_D0gamma_(
          ("deltaCutEffMisId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 1),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      Bu2Dst0h_D0pi0_sigma1Bu_(
          new RooRealVar(("Bu2Dst0h_D0pi0_sigma1Bu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         "", 4.5702e+01)),
      pdf1Bu_Bu2Dst0h_D0pi0_(),
      pdf2Bu_Bu2Dst0h_D0pi0_(),
      pdfBu_Bu2Dst0h_D0pi0_(new RooCBShape(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_n1Bu())),
      Bu2Dst0h_D0pi0_sigma1BuPartial_(
          new RooRealVar(("Bu2Dst0h_D0pi0_sigma1BuPartial_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         // Can't float this as shape tries to be too thin at
                         // top and wide at bottom (to account for wrong MisRec?
                         "", 2.5688e+01)),
      Bu2Dst0h_D0pi0_sigma2BuPartial_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_sigma2BuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "@0*@1",
          RooArgSet(*Bu2Dst0h_D0pi0_sigma1BuPartial_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                        .Bu2Dst0h_D0pi0_21SigmaBuPartial()))),
      Bu2Dst0h_D0pi0_sigma3BuPartial_(
          new RooRealVar(("Bu2Dst0h_D0pi0_sigma3BuPartial_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         // Can't float this as shape tries to be too thin at
                         // top and wide at bottom (to account for wrong MisRec?
                         "", 2.0737e+01, 15, 25)),
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
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0pi0_meanBu_(
          ("misId_Bu2Dst0h_D0pi0_meanBu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 5.3067e+03),
      misId_Bu2Dst0h_D0pi0_sigma1Bu_(
          ("misId_Bu2Dst0h_D0pi0_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 9.9388e+01),
      misId_Bu2Dst0h_D0pi0_sigma2Bu_(
          ("misId_Bu2Dst0h_D0pi0_sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 3.8744e+01),
      misId_Bu2Dst0h_D0pi0_a1Bu_(
          ("misId_Bu2Dst0h_D0pi0_a1Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 1.2847e-05),
      misId_Bu2Dst0h_D0pi0_a2Bu_(
          ("misId_Bu2Dst0h_D0pi0_a2Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 1.2601e-01),
      misId_Bu2Dst0h_D0pi0_n1Bu_(),
      misId_Bu2Dst0h_D0pi0_n2Bu_(),
      pdf1Bu_misId_Bu2Dst0h_D0pi0_(),
      pdf2Bu_misId_Bu2Dst0h_D0pi0_(),
      misId_Bu2Dst0h_D0pi0_fracPdf1Bu_(),
      pdfBu_misId_Bu2Dst0h_D0pi0_(new RooCruijff(
          ("pdfBu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), misId_Bu2Dst0h_D0pi0_meanBu_,
          misId_Bu2Dst0h_D0pi0_sigma1Bu_, misId_Bu2Dst0h_D0pi0_sigma2Bu_,
          misId_Bu2Dst0h_D0pi0_a1Bu_, misId_Bu2Dst0h_D0pi0_a2Bu_)),
      misId_Bu2Dst0h_D0pi0_meanBuPartial_(
          ("misId_Bu2Dst0h_D0pi0_meanBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 5.2386e+03),
      misId_Bu2Dst0h_D0pi0_sigma1BuPartial_(
          ("misId_Bu2Dst0h_D0pi0_sigma1BuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 5.3243e+01),
      misId_Bu2Dst0h_D0pi0_sigma2BuPartial_(
          ("misId_Bu2Dst0h_D0pi0_sigma2BuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 3.0186e+01),
      misId_Bu2Dst0h_D0pi0_a1BuPartial_(
          ("misId_Bu2Dst0h_D0pi0_a1BuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 2.8054e-07),
      misId_Bu2Dst0h_D0pi0_a2BuPartial_(
          ("misId_Bu2Dst0h_D0pi0_a2BuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 7.8747e-02),
      misId_Bu2Dst0h_D0pi0_n1BuPartial_(),
      misId_Bu2Dst0h_D0pi0_n2BuPartial_(),
      pdf1BuPartial_misId_Bu2Dst0h_D0pi0_(),
      pdf2BuPartial_misId_Bu2Dst0h_D0pi0_(),
      misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_(),
      pdfBuPartial_misId_Bu2Dst0h_D0pi0_(
          new RooCruijff(("pdfBuPartial_misId_Bu2Dst0h_D0pi0_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         "", Configuration::Get().buDeltaMass(),
                         misId_Bu2Dst0h_D0pi0_meanBuPartial_,
                         misId_Bu2Dst0h_D0pi0_sigma1BuPartial_,
                         misId_Bu2Dst0h_D0pi0_sigma2BuPartial_,
                         misId_Bu2Dst0h_D0pi0_a1BuPartial_,
                         misId_Bu2Dst0h_D0pi0_a2BuPartial_)),
      orEffMisId_Bu2Dst0h_D0pi0_(
          ("orEffMisId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 1),
      boxEffMisId_Bu2Dst0h_D0pi0_(
          ("boxEffMisId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 1),
      boxPartialEffMisId_Bu2Dst0h_D0pi0_(
          ("boxPartialEffMisId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 1),
      buDeltaCutEffMisId_Bu2Dst0h_D0pi0_(
          ("buDeltaCutEffMisId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 1),
      deltaCutEffMisId_Bu2Dst0h_D0pi0_(
          ("deltaCutEffMisId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 1),
      deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_(
          ("deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 1),
      // -------------------- MIS-REC -------------------- //
      MisRec_sigmaLBu_(("MisRec_sigmaLBu_" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                           .c_str(),
                       // "", 1.0404e+02, 50, 200),
                       // Fixed from data
                       // "", 1.3848e+02),
                       // Fixed from data
                       "", 1.3071e+02),
      MisRec_sigmaRBu_(("MisRec_sigmaRBu_" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                           .c_str(),
                       // "", 9.6206e+01, 50, 150),
                       // Fixed from data
                       // "", 8.3472e+01),
                       // Fixed from data
                       "", 8.4614e+01),
      pdfBu_MisRec_(("pdfBu_MisRec_" +
                     ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_meanBu(),
                    MisRec_sigmaLBu_, MisRec_sigmaRBu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aLBu(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aRBu()),
      MisRec_sigmaLBuPartial_(
          ("MisRec_sigmaLBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          // "", 8.6958e+01, 50, 150),
          // Fixed from data
          // "", 1.0871e+02),
          // Fixed from data
          "", 1.1831e+02),
      MisRec_sigmaRBuPartial_(
          ("MisRec_sigmaRBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          // "", 6.1290e+01, 10, 150),
          // Fixed from data
          // "", 5.1338e+01),
          // Fixed from data
          "", 4.6699e+01),
      pdfBuPartial_MisRec_(
          ("pdfBuPartial_MisRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_meanBuPartial(),
          MisRec_sigmaLBuPartial_, MisRec_sigmaRBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aRBuPartial()),
      // -------------------- Mis-ID ------------------- //
      misId_MisRec_mean1Bu_(),
      misId_MisRec_mean2Bu_(),
      misId_MisRec_sigma1Bu_(),
      misId_MisRec_sigma2Bu_(),
      misId_MisRec_a2Bu_(),
      misId_MisRec_a1Bu_(),
      misId_MisRec_n2Bu_(),
      misId_MisRec_n1Bu_(),
      pdf1Bu_misId_MisRec_(),
      pdf2Bu_misId_MisRec_(),
      misId_MisRec_fracPdf1Bu_(),
      pdfBu_misId_MisRec_(nullptr),
      misId_MisRec_meanBuPartial_(),
      misId_MisRec_sigmaLBuPartial_(),
      misId_MisRec_sigmaRBuPartial_(),
      misId_MisRec_aLBuPartial_(),
      misId_MisRec_aRBuPartial_(),
      pdfBuPartial_misId_MisRec_(),
      orEffMisId_MisRec_(),
      boxEffMisId_MisRec_(),
      boxPartialEffMisId_MisRec_(),
      buDeltaCutEffMisId_MisRec_(),
      deltaCutEffMisId_MisRec_(),
      deltaPartialCutEffMisId_MisRec_(),
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
      orEffMisId_Bu2D0h_(),
      boxEffMisId_Bu2D0h_(),
      boxPartialEffMisId_Bu2D0h_(),
      buDeltaCutEffMisId_Bu2D0h_(),
      deltaCutEffMisId_Bu2D0h_(),
      deltaPartialCutEffMisId_Bu2D0h_(),
      // -------------------- PART REC -------------------- //
      partRec_D0pi0_sigmaLBu_(
          ("partRec_D0pi0_sigmaLBu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 1.2119e+02),
      partRec_D0pi0_sigmaRBu_(
          ("partRec_D0pi0_sigmaRBu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 7.5601e+01),
      pdfBu_PartRec_D0pi0_(
          ("pdfBu_PartRec_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_D0pi0_meanBu(),
          partRec_D0pi0_sigmaLBu_, partRec_D0pi0_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_D0pi0_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_D0pi0_aRBu()),
      partRec_D0gamma_sigmaLBu_(
          ("partRec_D0gamma_sigmaLBu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 3.5619e+01),
      partRec_D0gamma_sigmaRBu_(
          ("partRec_D0gamma_sigmaRBu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 4.6552e+01),
      pdfBu_PartRec_D0gamma_(
          ("pdfBu_PartRec_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_D0gamma_meanBu(),
          partRec_D0gamma_sigmaLBu_, partRec_D0gamma_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_D0gamma_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_D0gamma_aRBu()),
      pdfBu_PartRec_(new RooAddPdf(
          ("pdfBu_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdfBu_PartRec_D0pi0_, pdfBu_PartRec_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_frac_D0pi0())),
      partRec_sigmaLBuPartial_(
          ("partRec_sigmaLBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 5.0477e+01),
      partRec_sigmaRBuPartial_(
          ("partRec_sigmaRBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 3.3665e+01),
      pdfBuPartial_PartRec_(
          ("pdfBuPartial_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_meanBuPartial(),
          partRec_sigmaLBuPartial_, partRec_sigmaRBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_aRBuPartial()),
      // -------------------- Mis-ID ------------------- //
      misId_PartRec_meanBu_(),
      misId_PartRec_sigmaLBu_(),
      misId_PartRec_sigmaRBu_(),
      misId_PartRec_aLBu_(),
      misId_PartRec_aRBu_(),
      pdfBu_misId_PartRec_(),
      misId_PartRec_meanBuPartial_(),
      misId_PartRec_sigmaLBuPartial_(),
      misId_PartRec_sigmaRBuPartial_(),
      misId_PartRec_aLBuPartial_(),
      misId_PartRec_aRBuPartial_(),
      pdfBuPartial_misId_PartRec_(),
      orEffMisId_PartRec_(),
      boxEffMisId_PartRec_(),
      boxPartialEffMisId_PartRec_(),
      buDeltaCutEffMisId_PartRec_(),
      deltaCutEffMisId_PartRec_(),
      deltaPartialCutEffMisId_PartRec_() {
  Configuration::Get().SetEfficiencies(
      Mode::Bu2Dst0K_D0gamma, Bachelor::pi, orEffMisId_Bu2Dst0h_D0gamma_,
      boxEffMisId_Bu2Dst0h_D0gamma_, buDeltaCutEffMisId_Bu2Dst0h_D0gamma_,
      deltaCutEffMisId_Bu2Dst0h_D0gamma_, true);
  if (Configuration::Get().fitBuPartial() == true) {
    Configuration::Get().SetEfficiencies(
        Mode::Bu2Dst0K_D0pi0, Bachelor::pi, orEffMisId_Bu2Dst0h_D0pi0_,
        boxEffMisId_Bu2Dst0h_D0pi0_, boxPartialEffMisId_Bu2Dst0h_D0pi0_,
        buDeltaCutEffMisId_Bu2Dst0h_D0pi0_, deltaCutEffMisId_Bu2Dst0h_D0pi0_,
        deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_, true);
  } else {
    Configuration::Get().SetEfficiencies(
        Mode::Bu2Dst0K_D0pi0, Bachelor::pi, orEffMisId_Bu2Dst0h_D0pi0_,
        boxEffMisId_Bu2Dst0h_D0pi0_, buDeltaCutEffMisId_Bu2Dst0h_D0pi0_,
        deltaCutEffMisId_Bu2Dst0h_D0pi0_, true);
  }
  // std::cout << "\t orEffMisId_Bu2Dst0h_D0pi0 = "
  //           << orEffMisId_Bu2Dst0h_D0pi0_.getVal() << "\n"
  //           << "\t boxEffMisId_Bu2Dst0h_D0pi0 = "
  //           << boxEffMisId_Bu2Dst0h_D0pi0_.getVal() << "\n"
  //           << "\t buDeltaCutEffMisId_Bu2Dst0h_D0pi0 = "
  //           << buDeltaCutEffMisId_Bu2Dst0h_D0pi0_.getVal() << "\n"
  //           << "\t deltaCutEffMisId_Bu2Dst0h_D0pi0 = "
  //           << deltaCutEffMisId_Bu2Dst0h_D0pi0_.getVal() << "\n"
  //           << "\t deltaPartialCutEffMisId_Bu2Dst0h_D0pi0 = "
  //           << deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_.getVal() << "\n";
}
