#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- Bu2Dst0h_D0pi0 -------------------- //
    : Bu2Dst0h_D0pi0_sigma1Bu_(new RooFormulaVar(
          ("Bu2Dst0h_D0pi0_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_D0pi0_sigma1Bu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .Bu2Dst0h_D0pi0_KpiSigmaBu()))),
      pdf1Bu_Bu2Dst0h_D0pi0_(
          ("pdf1Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigma1Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0pi0_(
          ("pdf2Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigma1Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_a2Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_n2Bu()),
      pdfBu_Bu2Dst0h_D0pi0_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0h_D0pi0_, pdf2Bu_Bu2Dst0h_D0pi0_),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_D0pi0_fracPdf1Bu())),
      Bu2Dst0h_D0pi0_sigma1BuPartial_(),
      Bu2Dst0h_D0pi0_sigma2BuPartial_(),
      pdf1BuPartial_Bu2Dst0h_D0pi0_(),
      pdf2BuPartial_Bu2Dst0h_D0pi0_(),
      pdfBuPartial_Bu2Dst0h_D0pi0_(),
      N_tot_initVal_Bu2Dst0h_D0pi0_(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .initYieldFAVBu2Dst0h_D0pi0() *
                                    NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .orEffBu2Dst0h_D0pi0()
                                        .getVal() *
                                    0.07930),
      pidEff_Bu2Dst0h_D0pi0_(("pidEff_Bu2Dst0h_D0pi0_" +
                              ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                                 .c_str(),
                             "", 6.8493e-01),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0pi0_meanBu_(("misId_Bu2Dst0h_D0pi0_meanBu_" +
                                    ComposeName(uniqueId, Neutral::pi0,
                                                Bachelor::k))
                                       .c_str(),
                                   "", 5.3492e+03),
      misId_Bu2Dst0h_D0pi0_sigma1Bu_(("misId_Bu2Dst0h_D0pi0_sigma1Bu_" +
                                      ComposeName(uniqueId, Neutral::pi0,
                                                  Bachelor::k))
                                         .c_str(),
                                     "", 2.7908e+01),
      misId_Bu2Dst0h_D0pi0_sigma2Bu_(("misId_Bu2Dst0h_D0pi0_sigma2Bu_" +
                                      ComposeName(uniqueId, Neutral::pi0,
                                                  Bachelor::k))
                                         .c_str(),
                                     "", 4.1672e+01),
      misId_Bu2Dst0h_D0pi0_a1Bu_(("misId_Bu2Dst0h_D0pi0_a1Bu_" +
                                  ComposeName(uniqueId, Neutral::pi0,
                                              Bachelor::k))
                                     .c_str(),
                                 "", 9.1443e+00),
      misId_Bu2Dst0h_D0pi0_a2Bu_(("misId_Bu2Dst0h_D0pi0_a2Bu_" +
                                  ComposeName(uniqueId, Neutral::pi0,
                                              Bachelor::k))
                                     .c_str(),
                                 "", -5.1399e-01),
      misId_Bu2Dst0h_D0pi0_n1Bu_(("misId_Bu2Dst0h_D0pi0_n1Bu_" +
                                  ComposeName(uniqueId, Neutral::pi0,
                                              Bachelor::k))
                                     .c_str(),
                                 "", 6.0954e+00),
      misId_Bu2Dst0h_D0pi0_n2Bu_(("misId_Bu2Dst0h_D0pi0_n2Bu_" +
                                  ComposeName(uniqueId, Neutral::pi0,
                                              Bachelor::k))
                                     .c_str(),
                                 "", 9.9998e+00),
      pdf1Bu_misId_Bu2Dst0h_D0pi0_(
          ("pdf1Bu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), misId_Bu2Dst0h_D0pi0_meanBu_,
          misId_Bu2Dst0h_D0pi0_sigma1Bu_, misId_Bu2Dst0h_D0pi0_a1Bu_,
          misId_Bu2Dst0h_D0pi0_n1Bu_),
      pdf2Bu_misId_Bu2Dst0h_D0pi0_(
          ("pdf2Bu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), misId_Bu2Dst0h_D0pi0_meanBu_,
          misId_Bu2Dst0h_D0pi0_sigma2Bu_, misId_Bu2Dst0h_D0pi0_a2Bu_,
          misId_Bu2Dst0h_D0pi0_n2Bu_),
      misId_Bu2Dst0h_D0pi0_fracPdf1Bu_(("misId_Bu2Dst0h_D0pi0_fracPdf1Bu_" +
                                        ComposeName(uniqueId, Neutral::pi0,
                                                    Bachelor::k))
                                           .c_str(),
                                       "", 1.6258e-01),
      pdfBu_misId_Bu2Dst0h_D0pi0_(
          new RooAddPdf(("pdfBu_misId_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                            .c_str(),
                        "", RooArgList(pdf1Bu_misId_Bu2Dst0h_D0pi0_,
                                       pdf2Bu_misId_Bu2Dst0h_D0pi0_),
                        misId_Bu2Dst0h_D0pi0_fracPdf1Bu_)),
      misId_Bu2Dst0h_D0pi0_meanBuPartial_(),
      misId_Bu2Dst0h_D0pi0_sigma1BuPartial_(),
      misId_Bu2Dst0h_D0pi0_sigma2BuPartial_(),
      misId_Bu2Dst0h_D0pi0_a2BuPartial_(),
      misId_Bu2Dst0h_D0pi0_a1BuPartial_(),
      misId_Bu2Dst0h_D0pi0_n2BuPartial_(),
      misId_Bu2Dst0h_D0pi0_n1BuPartial_(),
      pdf1BuPartial_misId_Bu2Dst0h_D0pi0_(),
      pdf2BuPartial_misId_Bu2Dst0h_D0pi0_(),
      misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_(),
      pdfBuPartial_misId_Bu2Dst0h_D0pi0_(nullptr),
      orEffMisId_Bu2Dst0h_D0pi0_(("orEffMisId_Bu2Dst0h_D0pi0_" +
                                  ComposeName(uniqueId, Neutral::pi0,
                                              Bachelor::k))
                                     .c_str(),
                                 "", 1),
      boxEffMisId_Bu2Dst0h_D0pi0_(("boxEffMisId_Bu2Dst0h_D0pi0_" +
                                   ComposeName(uniqueId, Neutral::pi0,
                                               Bachelor::k))
                                      .c_str(),
                                  "", 1),
      boxPartialEffMisId_Bu2Dst0h_D0pi0_(),
      buDeltaCutEffMisId_Bu2Dst0h_D0pi0_(("buDeltaCutEffMisId_Bu2Dst0h_D0pi0_" +
                                          ComposeName(uniqueId, Neutral::pi0,
                                                      Bachelor::k))
                                             .c_str(),
                                         "", 1),
      deltaCutEffMisId_Bu2Dst0h_D0pi0_(("deltaCutEffMisId_Bu2Dst0h_D0pi0_" +
                                        ComposeName(uniqueId, Neutral::pi0,
                                                    Bachelor::k))
                                           .c_str(),
                                       "", 1),
      deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_(),
      // -------------------- Bu2Dst0h_D0gamma -------------------- //
      Bu2Dst0h_D0gamma_sigma1Bu_(new RooFormulaVar(
          ("Bu2Dst0h_D0gamma_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_D0gamma_sigma1Bu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .Bu2Dst0h_D0gamma_KpiSigmaBu()))),
      Bu2Dst0h_D0gamma_sigma2Bu_(new RooFormulaVar(
          ("Bu2Dst0h_D0gamma_sigma2Bu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_D0gamma_sigma2Bu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .Bu2Dst0h_D0gamma_KpiSigmaBu()))),
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
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_a2Bu())),
      Bu2Dst0h_D0gamma_sigmaBuPartial_(),
      pdfBuPartial_Bu2Dst0h_D0gamma_(),
      N_tot_initVal_Bu2Dst0h_D0gamma_(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                          .initYieldFAVBu2Dst0h_D0gamma() *
                                      NeutralVars<Neutral::pi0>::Get(uniqueId)
                                          .orEffBu2Dst0h_D0gamma()
                                          .getVal() *
                                      0.07930),
      pidEff_Bu2Dst0h_D0gamma_(("pidEff_Bu2Dst0h_D0gamma_" +
                                ComposeName(uniqueId, Neutral::pi0,
                                            Bachelor::k))
                                   .c_str(),
                               "", 0.751547),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_meanBu_(("misId_Bu2Dst0h_D0gamma_meanBu_" +
                                      ComposeName(uniqueId, Neutral::pi0,
                                                  Bachelor::k))
                                         .c_str(),
                                     "", 5.3584e+03),
      misId_Bu2Dst0h_D0gamma_sigma1Bu_(("misId_Bu2Dst0h_D0gamma_sigma1Bu_" +
                                        ComposeName(uniqueId, Neutral::pi0,
                                                    Bachelor::k))
                                           .c_str(),
                                       "", 4.5510e+01),
      misId_Bu2Dst0h_D0gamma_sigma2Bu_(("misId_Bu2Dst0h_D0gamma_sigma2Bu_" +
                                        ComposeName(uniqueId, Neutral::pi0,
                                                    Bachelor::k))
                                           .c_str(),
                                       "", 7.6705e+01),
      misId_Bu2Dst0h_D0gamma_a1Bu_(("misId_Bu2Dst0h_D0gamma_a1Bu_" +
                                    ComposeName(uniqueId, Neutral::pi0,
                                                Bachelor::k))
                                       .c_str(),
                                   "", 8.9228e-02),
      misId_Bu2Dst0h_D0gamma_a2Bu_(("misId_Bu2Dst0h_D0gamma_a2Bu_" +
                                    ComposeName(uniqueId, Neutral::pi0,
                                                Bachelor::k))
                                       .c_str(),
                                   "", 1.6831e-01),
      misId_Bu2Dst0h_D0gamma_n1Bu_(),
      misId_Bu2Dst0h_D0gamma_n2Bu_(),
      pdf1Bu_misId_Bu2Dst0h_D0gamma_(),
      pdf2Bu_misId_Bu2Dst0h_D0gamma_(),
      misId_Bu2Dst0h_D0gamma_fracPdf1Bu_(),
      pdfBu_misId_Bu2Dst0h_D0gamma_(new RooCruijff(
          ("pdfBu_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          misId_Bu2Dst0h_D0gamma_meanBu_, misId_Bu2Dst0h_D0gamma_sigma1Bu_,
          misId_Bu2Dst0h_D0gamma_sigma2Bu_, misId_Bu2Dst0h_D0gamma_a1Bu_,
          misId_Bu2Dst0h_D0gamma_a2Bu_)),
      orEffMisId_Bu2Dst0h_D0gamma_(("orEffMisId_Bu2Dst0h_D0gamma_" +
                                    ComposeName(uniqueId, Neutral::pi0,
                                                Bachelor::k))
                                       .c_str(),
                                   "", 1),
      boxEffMisId_Bu2Dst0h_D0gamma_(("boxEffMisId_Bu2Dst0h_D0gamma_" +
                                     ComposeName(uniqueId, Neutral::pi0,
                                                 Bachelor::k))
                                        .c_str(),
                                    "", 1),
      buDeltaCutEffMisId_Bu2Dst0h_D0gamma_(
          ("buDeltaCutEffMisId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1),
      deltaCutEffMisId_Bu2Dst0h_D0gamma_(("deltaCutEffMisId_Bu2Dst0h_D0gamma_" +
                                          ComposeName(uniqueId, Neutral::pi0,
                                                      Bachelor::k))
                                             .c_str(),
                                         "", 1),
      // -------------------- MIS-REC -------------------- //
      MisRec_sigmaLBu_(("MisRec_sigmaLBu_" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                           .c_str(),
                       // "", 6.5198e+01, 20, 100),
                       // Fixed from data
                       "", 5.9863e+01),
      MisRec_sigmaRBu_(("MisRec_sigmaRBu_" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                           .c_str(),
                       // "", 4.7849e+01, 20, 100),
                       // Fixed from data
                       "", 4.9259e+01),
      pdfBu_MisRec_(("pdfBu_MisRec_" +
                     ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_meanBu(),
                    MisRec_sigmaLBu_, MisRec_sigmaRBu_,
                    NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_aLBu(),
                    NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_aRBu()),
      MisRec_sigmaLBuPartial_(),
      MisRec_sigmaRBuPartial_(),
      pdfBuPartial_MisRec_(),
      N_tot_initVal_MisRec_(
          NeutralVars<Neutral::pi0>::Get(uniqueId).initYieldFAVMisRec() *
          NeutralVars<Neutral::pi0>::Get(uniqueId).orEffMisRec().getVal() *
          0.06),
      pidEff_Bu2Dst0h_D0gamma_WN_(),
      pidEff_Bu2Dst0h_D0pi0_WN_(),
      pidEff_Bu2D0hst_(),
      pidEff_Bd2Dsth_(),
      pidEff_MisRec_(),
      // -------------------- Mis-ID ------------------- //
      misId_MisRec_mean1Bu_(("misId_MisRec_mean1Bu_" +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                                .c_str(),
                            "", 5.3332e+03),
      misId_MisRec_mean2Bu_(),
      misId_MisRec_sigma1Bu_(("misId_MisRec_sigma1Bu_" +
                              ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                                 .c_str(),
                             "", 2.6031e+01),
      misId_MisRec_sigma2Bu_(("misId_MisRec_sigma2Bu_" +
                              ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                                 .c_str(),
                             "", 6.2339e+01),
      misId_MisRec_a1Bu_(("misId_MisRec_a1Bu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                             .c_str(),
                         "", 2.5422e-01),
      misId_MisRec_a2Bu_(("misId_MisRec_a2Bu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                             .c_str(),
                         "", 2.4586e-01),
      misId_MisRec_n1Bu_(),
      misId_MisRec_n2Bu_(),
      pdf1Bu_misId_MisRec_(),
      pdf2Bu_misId_MisRec_(),
      misId_MisRec_fracPdf1Bu_(),
      pdfBu_misId_MisRec_(new RooCruijff(
          ("pdfBu_misId_MisRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), misId_MisRec_mean1Bu_,
          misId_MisRec_sigma1Bu_, misId_MisRec_sigma2Bu_, misId_MisRec_a1Bu_,
          misId_MisRec_a2Bu_)),
      misId_MisRec_meanBuPartial_(),
      misId_MisRec_sigmaLBuPartial_(),
      misId_MisRec_sigmaRBuPartial_(),
      misId_MisRec_aLBuPartial_(),
      misId_MisRec_aRBuPartial_(),
      pdfBuPartial_misId_MisRec_(),
      orEffMisId_MisRec_(("orEffMisId_MisRec_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                             .c_str(),
                         "", 1),
      boxEffMisId_MisRec_(("boxEffMisId_MisRec_" +
                           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                              .c_str(),
                          "", 1),
      boxPartialEffMisId_MisRec_(),
      buDeltaCutEffMisId_MisRec_(("buDeltaCutEffMisId_MisRec_" +
                                  ComposeName(uniqueId, Neutral::pi0,
                                              Bachelor::k))
                                     .c_str(),
                                 "", 1),
      deltaCutEffMisId_MisRec_(("deltaCutEffMisId_MisRec_" +
                                ComposeName(uniqueId, Neutral::pi0,
                                            Bachelor::k))
                                   .c_str(),
                               "", 1),
      deltaPartialCutEffMisId_MisRec_(),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_sigmaLBu_(("Bu2D0h_sigmaLBu_" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                           .c_str(),
                       // "", 3.3137e+01, 10, 100),
                       // Fixed from data
                       "", 2.5654e+01),
      Bu2D0h_sigmaRBu_(("Bu2D0h_sigmaRBu_" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                           .c_str(),
                       // "", 4.0080e+01, 10, 80),
                       // Fixed from data
                       "", 3.9920e+01),
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
      // No MC samples for Bu2D0K: no PID efficiency. OK as don't need R values,
      // just need to include fit components. N_K = N_tot. N_π = eff * N_tot
      N_tot_initVal_Bu2D0h_(
          NeutralVars<Neutral::pi0>::Get(uniqueId).initYieldFAVBu2D0h() *
          NeutralVars<Neutral::pi0>::Get(uniqueId).orEffBu2D0h().getVal() *
          0.07768),
      pidEff_Bu2D0h_(),
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
      orEffMisId_Bu2D0h_(("orEffMisId_Bu2D0h_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                             .c_str(),
                         "", 1),
      boxEffMisId_Bu2D0h_(("boxEffMisId_Bu2D0h_" +
                           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                              .c_str(),
                          "", 1),
      boxPartialEffMisId_Bu2D0h_(),
      buDeltaCutEffMisId_Bu2D0h_(("buDeltaCutEffMisId_Bu2D0h_" +
                                  ComposeName(uniqueId, Neutral::pi0,
                                              Bachelor::k))
                                     .c_str(),
                                 "", 1),
      deltaCutEffMisId_Bu2D0h_(("deltaCutEffMisId_Bu2D0h_" +
                                ComposeName(uniqueId, Neutral::pi0,
                                            Bachelor::k))
                                   .c_str(),
                               "", 1),
      deltaPartialCutEffMisId_Bu2D0h_(),
      // -------------------- PART REC -------------------- //
      partRec_D0pi0_sigmaLBu_(("partRec_D0pi0_sigmaLBu_" +
                               ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                                  .c_str(),
                              "", 4.8731e+01),
      partRec_D0pi0_sigmaRBu_(("partRec_D0pi0_sigmaRBu_" +
                               ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                                  .c_str(),
                              "", 4.4688e+01),
      pdfBu_PartRec_D0pi0_(),
      partRec_D0gamma_sigmaLBu_(),
      partRec_D0gamma_sigmaRBu_(),
      pdfBu_PartRec_D0gamma_(),
      pdfBu_PartRec_(new RooCruijff(
          ("pdfBu_PartRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).partRec_D0pi0_meanBu(),
          partRec_D0pi0_sigmaLBu_, partRec_D0pi0_sigmaRBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).partRec_D0pi0_aLBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).partRec_D0pi0_aRBu())),
      partRec_sigmaLBuPartial_(),
      partRec_sigmaRBuPartial_(),
      pdfBuPartial_PartRec_(),
      N_tot_initVal_PartRec_(
          NeutralVars<Neutral::pi0>::Get(uniqueId).initYieldFAVPartRec() *
          NeutralVars<Neutral::pi0>::Get(uniqueId).orEffPartRec().getVal() *
          0.02),
      pidEff_Bu2Dst0hst_D0pi0_(),
      pidEff_Bu2Dst0hst_D0gamma_(),
      pidEff_PartRec_(),
      // -------------------- Mis-ID ------------------- //
      misId_PartRec_meanBu_(("misId_PartRec_meanBu_" +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                                .c_str(),
                            "", 5.1585e+03),
      misId_PartRec_sigmaLBu_(("misId_PartRec_sigmaLBu_" +
                               ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                                  .c_str(),
                              "", 4.5703e+01),
      misId_PartRec_sigmaRBu_(("misId_PartRec_sigmaRBu_" +
                               ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                                  .c_str(),
                              "", 7.6861e+01),
      misId_PartRec_aLBu_(("misId_PartRec_aLBu_" +
                           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                              .c_str(),
                          "", 2.3408e-07),
      misId_PartRec_aRBu_(("misId_PartRec_aRBu_" +
                           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                              .c_str(),
                          "", 2.1596e-01),
      pdfBu_misId_PartRec_(("pdfBu_misId_PartRec_" +
                            ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                               .c_str(),
                           "", Configuration::Get().buDeltaMass(),
                           misId_PartRec_meanBu_, misId_PartRec_sigmaLBu_,
                           misId_PartRec_sigmaRBu_, misId_PartRec_aLBu_,
                           misId_PartRec_aRBu_),
      misId_PartRec_meanBuPartial_(),
      misId_PartRec_sigmaLBuPartial_(),
      misId_PartRec_sigmaRBuPartial_(),
      misId_PartRec_aLBuPartial_(),
      misId_PartRec_aRBuPartial_(),
      pdfBuPartial_misId_PartRec_(),
      orEffMisId_PartRec_(("orEffMisId_PartRec_" +
                           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                              .c_str(),
                          "", 1),
      boxEffMisId_PartRec_(("boxEffMisId_PartRec_" +
                            ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                               .c_str(),
                           "", 1),
      boxPartialEffMisId_PartRec_(),
      buDeltaCutEffMisId_PartRec_(("buDeltaCutEffMisId_PartRec_" +
                                   ComposeName(uniqueId, Neutral::pi0,
                                               Bachelor::k))
                                      .c_str(),
                                  "", 1),
      deltaCutEffMisId_PartRec_(("deltaCutEffMisId_PartRec_" +
                                 ComposeName(uniqueId, Neutral::pi0,
                                             Bachelor::k))
                                    .c_str(),
                                "", 1),
      deltaPartialCutEffMisId_PartRec_() {
  Configuration::Get().SetEfficiencies(
      Mode::Bu2Dst0pi_D0gamma, Bachelor::k, orEffMisId_Bu2Dst0h_D0gamma_,
      boxEffMisId_Bu2Dst0h_D0gamma_, buDeltaCutEffMisId_Bu2Dst0h_D0gamma_,
      deltaCutEffMisId_Bu2Dst0h_D0gamma_, true);
  Configuration::Get().SetEfficiencies(
      Mode::Bu2Dst0pi_D0pi0, Bachelor::k, orEffMisId_Bu2Dst0h_D0pi0_,
      boxEffMisId_Bu2Dst0h_D0pi0_, buDeltaCutEffMisId_Bu2Dst0h_D0pi0_,
      deltaCutEffMisId_Bu2Dst0h_D0pi0_, true);

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

  double orEffMisId_MisRecVal = 0.0;
  double boxEffMisId_MisRecVal = 0.0;
  double buDeltaCutEffMisId_MisRecVal = 0.0;
  double deltaCutEffMisId_MisRecVal = 0.0;

  for (auto &m : misRecModesMap) {
    RooRealVar orEffMisIdTemp(
        ("orEffMisIdTemp" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
        1);
    RooRealVar boxEffMisIdTemp(
        ("boxEffMisIdTemp" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
        1);
    RooRealVar buDeltaCutEffMisIdTemp(
        ("buDeltaCutEffMisIdTemp" + ComposeName(uniqueId, Neutral::pi0))
            .c_str(),
        "", 1);
    RooRealVar deltaCutEffMisIdTemp(
        ("deltaCutEffMisIdTemp" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
        "", 1);

    Configuration::Get().SetEfficiencies(
        m.first, Bachelor::k, orEffMisIdTemp, boxEffMisIdTemp,
        buDeltaCutEffMisIdTemp, deltaCutEffMisIdTemp, true);

    orEffMisId_MisRecVal += orEffMisIdTemp.getVal() * m.second;
    boxEffMisId_MisRecVal += boxEffMisIdTemp.getVal() * m.second;
    buDeltaCutEffMisId_MisRecVal += buDeltaCutEffMisIdTemp.getVal() * m.second;
    deltaCutEffMisId_MisRecVal += deltaCutEffMisIdTemp.getVal() * m.second;
  }
  boxEffMisId_MisRec_.setVal(boxEffMisId_MisRecVal);
  buDeltaCutEffMisId_MisRec_.setVal(buDeltaCutEffMisId_MisRecVal);
  deltaCutEffMisId_MisRec_.setVal(deltaCutEffMisId_MisRecVal);
  if (Configuration::Get().fit1D() == false) {
    orEffMisId_MisRec_.setVal(orEffMisId_MisRecVal);
  } else {
    orEffMisId_MisRec_.setVal(deltaCutEffMisId_MisRecVal);
  }
  // std::cout << "\t orEffMisId_MisRec = " << orEffMisId_MisRec_.getVal() <<
  // "\n"
  //           << "\t boxEffMisId_MisRec = " << boxEffMisId_MisRec_.getVal()
  //           << "\n"
  //           << "\t buDeltaCutEffMisId_MisRec = "
  //           << buDeltaCutEffMisId_MisRec_.getVal() << "\n"
  //           << "\t deltaCutEffMisId_MisRec = "
  //           << deltaCutEffMisId_MisRec_.getVal() << "\n";

  Configuration::Get().SetEfficiencies(
      Mode::Bu2D0pi, Bachelor::k, orEffMisId_Bu2D0h_, boxEffMisId_Bu2D0h_,
      buDeltaCutEffMisId_Bu2D0h_, deltaCutEffMisId_Bu2D0h_, true);
  Configuration::Get().SetEfficiencies(
      Mode::Bu2Dst0rho_D0pi0, Bachelor::k, orEffMisId_PartRec_,
      boxEffMisId_PartRec_, buDeltaCutEffMisId_PartRec_,
      deltaCutEffMisId_PartRec_, true);
}
