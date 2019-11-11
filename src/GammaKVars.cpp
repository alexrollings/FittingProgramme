#include "NeutralBachelorVars.h"

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
      Bu2Dst0h_D0gamma_sigmaBuPartial_(("Bu2Dst0h_D0gamma_sigmaBuPartial_" +
                                        ComposeName(uniqueId, Neutral::gamma,
                                                    Bachelor::k))
                                           .c_str(),
                                       "", 3.0651e+01),
      pdfBuPartial_Bu2Dst0h_D0gamma_(("pdfBuPartial_Bu2Dst0h_D0gamma_" +
                                      ComposeName(uniqueId, Neutral::gamma,
                                                  Bachelor::k))
                                         .c_str(),
                                     "", Configuration::Get().buDeltaMass(),
                                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                                         .Bu2Dst0h_D0gamma_meanBuPartial(),
                                     Bu2Dst0h_D0gamma_sigmaBuPartial_,
                                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                                         .Bu2Dst0h_D0gamma_aBuPartial(),
                                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                                         .Bu2Dst0h_D0gamma_nBuPartial()),
      N_tot_initVal_Bu2Dst0h_D0gamma_(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                          .initYieldFAVBu2Dst0h_D0gamma() *
                                      NeutralVars<Neutral::gamma>::Get(uniqueId)
                                          .orEffBu2Dst0h_D0gamma()
                                          .getVal() *
                                      0.07930),
      pidEff_Bu2Dst0h_D0gamma_(("pidEff_Bu2Dst0h_D0gamma_" +
                                ComposeName(uniqueId, Neutral::gamma,
                                            Bachelor::k))
                                   .c_str(),
                               "", 6.8493e-01),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_meanBu_(("misId_Bu2Dst0h_D0gamma_meanBu_" +
                                      ComposeName(uniqueId, Neutral::gamma,
                                                  Bachelor::k))
                                         .c_str(),
                                     "", 5.3424e+03),
      misId_Bu2Dst0h_D0gamma_sigma1Bu_(("misId_Bu2Dst0h_D0gamma_sigma1Bu_" +
                                        ComposeName(uniqueId, Neutral::gamma,
                                                    Bachelor::k))
                                           .c_str(),
                                       "", 2.7896e+01),
      misId_Bu2Dst0h_D0gamma_sigma2Bu_(),
      misId_Bu2Dst0h_D0gamma_a1Bu_(("misId_Bu2Dst0h_D0gamma_a1Bu_" +
                                    ComposeName(uniqueId, Neutral::gamma,
                                                Bachelor::k))
                                       .c_str(),
                                   "", 7.7160e-01),
      misId_Bu2Dst0h_D0gamma_a2Bu_(("misId_Bu2Dst0h_D0gamma_a2Bu_" +
                                    ComposeName(uniqueId, Neutral::gamma,
                                                Bachelor::k))
                                       .c_str(),
                                   "", -4.6919e-01),
      misId_Bu2Dst0h_D0gamma_n1Bu_(("misId_Bu2Dst0h_D0gamma_n1Bu_" +
                                    ComposeName(uniqueId, Neutral::gamma,
                                                Bachelor::k))
                                       .c_str(),
                                   "", 1.8491e+00),
      misId_Bu2Dst0h_D0gamma_n2Bu_(("misId_Bu2Dst0h_D0gamma_n2Bu_" +
                                    ComposeName(uniqueId, Neutral::gamma,
                                                Bachelor::k))
                                       .c_str(),
                                   "", 6.2054e+00),
      pdf1Bu_misId_Bu2Dst0h_D0gamma_(
          ("pdf1Bu_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          misId_Bu2Dst0h_D0gamma_meanBu_, misId_Bu2Dst0h_D0gamma_sigma1Bu_,
          misId_Bu2Dst0h_D0gamma_a1Bu_, misId_Bu2Dst0h_D0gamma_n1Bu_),
      pdf2Bu_misId_Bu2Dst0h_D0gamma_(
          ("pdf2Bu_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          misId_Bu2Dst0h_D0gamma_meanBu_, misId_Bu2Dst0h_D0gamma_sigma1Bu_,
          misId_Bu2Dst0h_D0gamma_a2Bu_, misId_Bu2Dst0h_D0gamma_n2Bu_),
      misId_Bu2Dst0h_D0gamma_fracPdf1Bu_(("misId_Bu2Dst0h_D0gamma_fracPdf1Bu_" +
                                          ComposeName(uniqueId, Neutral::gamma,
                                                      Bachelor::k))
                                             .c_str(),
                                         "", 5.3533e-02),
      pdfBu_misId_Bu2Dst0h_D0gamma_(
          new RooAddPdf(("pdfBu_misId_Bu2Dst0h_D0gamma_" +
                         ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "", RooArgList(pdf1Bu_misId_Bu2Dst0h_D0gamma_,
                                       pdf2Bu_misId_Bu2Dst0h_D0gamma_),
                        misId_Bu2Dst0h_D0gamma_fracPdf1Bu_)),
      orEffMisId_Bu2Dst0h_D0gamma_(("orEffMisId_Bu2Dst0h_D0gamma_" +
                                    ComposeName(uniqueId, Neutral::gamma,
                                                Bachelor::k))
                                       .c_str(),
                                   "", 1),
      boxEffMisId_Bu2Dst0h_D0gamma_(("boxEffMisId_Bu2Dst0h_D0gamma_" +
                                     ComposeName(uniqueId, Neutral::gamma,
                                                 Bachelor::k))
                                        .c_str(),
                                    "", 1),
      buDeltaCutEffMisId_Bu2Dst0h_D0gamma_(
          ("buDeltaCutEffMisId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 1),
      deltaCutEffMisId_Bu2Dst0h_D0gamma_(("deltaCutEffMisId_Bu2Dst0h_D0gamma_" +
                                          ComposeName(uniqueId, Neutral::gamma,
                                                      Bachelor::k))
                                             .c_str(),
                                         "", 1),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      Bu2Dst0h_D0pi0_sigma1Bu_(
          new RooRealVar(("Bu2Dst0h_D0pi0_sigma1Bu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", 4.6911e+01)),
      pdf1Bu_Bu2Dst0h_D0pi0_(),
      pdf2Bu_Bu2Dst0h_D0pi0_(),
      pdfBu_Bu2Dst0h_D0pi0_(new RooCBShape(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigma1Bu_,
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
      pdf1BuPartial_Bu2Dst0h_D0pi0_(("pdf1BuPartial_Bu2Dst0h_D0pi0_" +
                                     ComposeName(uniqueId, Neutral::gamma,
                                                 Bachelor::k))
                                        .c_str(),
                                    "", Configuration::Get().buDeltaMass(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_D0pi0_meanBuPartial(),
                                    *Bu2Dst0h_D0pi0_sigma1BuPartial_,
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_D0pi0_a1BuPartial(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_D0pi0_n1BuPartial()),
      pdf2BuPartial_Bu2Dst0h_D0pi0_(("pdf2BuPartial_Bu2Dst0h_D0pi0_" +
                                     ComposeName(uniqueId, Neutral::gamma,
                                                 Bachelor::k))
                                        .c_str(),
                                    "", Configuration::Get().buDeltaMass(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_D0pi0_meanBuPartial(),
                                    *Bu2Dst0h_D0pi0_sigma2BuPartial_,
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_D0pi0_a2BuPartial(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_D0pi0_n2BuPartial()),
      pdfBuPartial_Bu2Dst0h_D0pi0_(("pdfBuPartial_Bu2Dst0h_D0pi0_" +
                                    ComposeName(uniqueId, Neutral::gamma,
                                                Bachelor::k))
                                       .c_str(),
                                   "", RooArgSet(pdf1BuPartial_Bu2Dst0h_D0pi0_,
                                                 pdf2BuPartial_Bu2Dst0h_D0pi0_),
                                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .Bu2Dst0h_D0pi0_fracPdf1BuPartial()),
      N_tot_initVal_Bu2Dst0h_D0pi0_(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .initYieldFAVBu2Dst0h_D0pi0() *
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .orEffBu2Dst0h_D0pi0()
                                        .getVal() *
                                    0.07930),
      pidEff_Bu2Dst0h_D0pi0_(("pidEff_Bu2Dst0h_D0pi0_" +
                              ComposeName(uniqueId, Neutral::gamma,
                                          Bachelor::k))
                                 .c_str(),
                             "", 0.745534),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0pi0_meanBu_(("misId_Bu2Dst0h_D0pi0_meanBu_" +
                                    ComposeName(uniqueId, Neutral::gamma,
                                                Bachelor::k))
                                       .c_str(),
                                   "", 5.4162e+03),
      misId_Bu2Dst0h_D0pi0_sigma1Bu_(("misId_Bu2Dst0h_D0pi0_sigma1Bu_" +
                                      ComposeName(uniqueId, Neutral::gamma,
                                                  Bachelor::k))
                                         .c_str(),
                                     "", 7.8398e+01),
      misId_Bu2Dst0h_D0pi0_sigma2Bu_(),
      misId_Bu2Dst0h_D0pi0_a1Bu_(("misId_Bu2Dst0h_D0pi0_a1Bu_" +
                                  ComposeName(uniqueId, Neutral::gamma,
                                              Bachelor::k))
                                     .c_str(),
                                 "", 2.5079e+00),
      misId_Bu2Dst0h_D0pi0_a2Bu_(("misId_Bu2Dst0h_D0pi0_a2Bu_" +
                                  ComposeName(uniqueId, Neutral::gamma,
                                              Bachelor::k))
                                     .c_str(),
                                 "", -1.0082e+00),
      misId_Bu2Dst0h_D0pi0_n1Bu_(("misId_Bu2Dst0h_D0pi0_n1Bu_" +
                                  ComposeName(uniqueId, Neutral::gamma,
                                              Bachelor::k))
                                     .c_str(),
                                 "", 3.8304e-06),
      misId_Bu2Dst0h_D0pi0_n2Bu_(("misId_Bu2Dst0h_D0pi0_n2Bu_" +
                                  ComposeName(uniqueId, Neutral::gamma,
                                              Bachelor::k))
                                     .c_str(),
                                 "", 1.0000e+01),
      pdf1Bu_misId_Bu2Dst0h_D0pi0_(
          ("pdf1Bu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), misId_Bu2Dst0h_D0pi0_meanBu_,
          misId_Bu2Dst0h_D0pi0_sigma1Bu_, misId_Bu2Dst0h_D0pi0_a1Bu_,
          misId_Bu2Dst0h_D0pi0_n1Bu_),
      pdf2Bu_misId_Bu2Dst0h_D0pi0_(
          ("pdf2Bu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), misId_Bu2Dst0h_D0pi0_meanBu_,
          misId_Bu2Dst0h_D0pi0_sigma1Bu_, misId_Bu2Dst0h_D0pi0_a2Bu_,
          misId_Bu2Dst0h_D0pi0_n2Bu_),
      misId_Bu2Dst0h_D0pi0_fracPdf1Bu_(("misId_Bu2Dst0h_D0pi0_fracPdf1Bu_" +
                                        ComposeName(uniqueId, Neutral::gamma,
                                                    Bachelor::k))
                                           .c_str(),
                                       "", 1.8004e-01),
      pdfBu_misId_Bu2Dst0h_D0pi0_(
          new RooAddPdf(("pdfBu_misId_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "", RooArgList(pdf1Bu_misId_Bu2Dst0h_D0pi0_,
                                       pdf2Bu_misId_Bu2Dst0h_D0pi0_),
                        misId_Bu2Dst0h_D0pi0_fracPdf1Bu_)),
      misId_Bu2Dst0h_D0pi0_meanBuPartial_(
          ("misId_Bu2Dst0h_D0pi0_meanBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 5.3620e+03),
      misId_Bu2Dst0h_D0pi0_sigma1BuPartial_(
          ("misId_Bu2Dst0h_D0pi0_sigma1BuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 4.5215e+01),
      misId_Bu2Dst0h_D0pi0_sigma2BuPartial_(),
      misId_Bu2Dst0h_D0pi0_a1BuPartial_(("misId_Bu2Dst0h_D0pi0_a1BuPartial_" +
                                         ComposeName(uniqueId, Neutral::gamma,
                                                     Bachelor::k))
                                            .c_str(),
                                        "", 8.8800e-01),
      misId_Bu2Dst0h_D0pi0_a2BuPartial_(("misId_Bu2Dst0h_D0pi0_a2BuPartial_" +
                                         ComposeName(uniqueId, Neutral::gamma,
                                                     Bachelor::k))
                                            .c_str(),
                                        "", -5.8384e-01),
      misId_Bu2Dst0h_D0pi0_n1BuPartial_(("misId_Bu2Dst0h_D0pi0_n1BuPartial_" +
                                         ComposeName(uniqueId, Neutral::gamma,
                                                     Bachelor::k))
                                            .c_str(),
                                        "", 8.0992e+00),
      misId_Bu2Dst0h_D0pi0_n2BuPartial_(("misId_Bu2Dst0h_D0pi0_n2BuPartial_" +
                                         ComposeName(uniqueId, Neutral::gamma,
                                                     Bachelor::k))
                                            .c_str(),
                                        "", 1.0000e+01),
      pdf1BuPartial_misId_Bu2Dst0h_D0pi0_(
          ("pdf1BuPartial_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          misId_Bu2Dst0h_D0pi0_meanBuPartial_,
          misId_Bu2Dst0h_D0pi0_sigma1BuPartial_,
          misId_Bu2Dst0h_D0pi0_a1BuPartial_, misId_Bu2Dst0h_D0pi0_n1BuPartial_),
      pdf2BuPartial_misId_Bu2Dst0h_D0pi0_(
          ("pdf2BuPartial_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          misId_Bu2Dst0h_D0pi0_meanBuPartial_,
          misId_Bu2Dst0h_D0pi0_sigma1BuPartial_,
          misId_Bu2Dst0h_D0pi0_a2BuPartial_, misId_Bu2Dst0h_D0pi0_n2BuPartial_),
      misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_(
          ("misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 1.2836e-01),
      pdfBuPartial_misId_Bu2Dst0h_D0pi0_(
          new RooAddPdf(("pdfBuPartial_misId_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "", RooArgList(pdf1BuPartial_misId_Bu2Dst0h_D0pi0_,
                                       pdf2BuPartial_misId_Bu2Dst0h_D0pi0_),
                        misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_)),
      orEffMisId_Bu2Dst0h_D0pi0_(("orEffMisId_Bu2Dst0h_D0pi0_" +
                                  ComposeName(uniqueId, Neutral::gamma,
                                              Bachelor::k))
                                     .c_str(),
                                 "", 1),
      boxEffMisId_Bu2Dst0h_D0pi0_(("boxEffMisId_Bu2Dst0h_D0pi0_" +
                                   ComposeName(uniqueId, Neutral::gamma,
                                               Bachelor::k))
                                      .c_str(),
                                  "", 1),
      boxPartialEffMisId_Bu2Dst0h_D0pi0_(("boxPartialEffMisId_Bu2Dst0h_D0pi0_" +
                                          ComposeName(uniqueId, Neutral::gamma,
                                                      Bachelor::k))
                                             .c_str(),
                                         "", 1),
      buDeltaCutEffMisId_Bu2Dst0h_D0pi0_(("buDeltaCutEffMisId_Bu2Dst0h_D0pi0_" +
                                          ComposeName(uniqueId, Neutral::gamma,
                                                      Bachelor::k))
                                             .c_str(),
                                         "", 1),
      deltaCutEffMisId_Bu2Dst0h_D0pi0_(("deltaCutEffMisId_Bu2Dst0h_D0pi0_" +
                                        ComposeName(uniqueId, Neutral::gamma,
                                                    Bachelor::k))
                                           .c_str(),
                                       "", 1),
      deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_(
          ("deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 1),
      // -------------------- MIS-REC -------------------- //
      MisRec_sigmaLBu_(("MisRec_sigmaLBu_" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                           .c_str(),
                       "", 1.0404e+02),
      MisRec_sigmaRBu_(("MisRec_sigmaRBu_" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                           .c_str(),
                       "", 9.6206e+01),
      pdfBu_MisRec_(("pdfBu_MisRec_" +
                     ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_meanBu(),
                    MisRec_sigmaLBu_, MisRec_sigmaRBu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aLBu(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aRBu()),
      MisRec_sigmaLBuPartial_(("MisRec_sigmaLBuPartial_" +
                               ComposeName(uniqueId, Neutral::gamma,
                                           Bachelor::k))
                                  .c_str(),
                              "", 8.6958e+01),  //, 50, 150),
      MisRec_sigmaRBuPartial_(("MisRec_sigmaRBuPartial_" +
                               ComposeName(uniqueId, Neutral::gamma,
                                           Bachelor::k))
                                  .c_str(),
                              "", 6.1290e+01),  //, 50, 150),
      pdfBuPartial_MisRec_(
          ("pdfBuPartial_MisRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_meanBuPartial(),
          MisRec_sigmaLBuPartial_, MisRec_sigmaRBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aRBuPartial()),
      N_tot_initVal_MisRec_(
          NeutralVars<Neutral::gamma>::Get(uniqueId).initYieldFAVMisRec() *
          NeutralVars<Neutral::gamma>::Get(uniqueId).orEffMisRec().getVal() *
          0.06),
      pidEff_Bu2Dst0h_D0gamma_WN_(),
      pidEff_Bu2Dst0h_D0pi0_WN_(),
      pidEff_Bu2D0hst_(),
      pidEff_Bd2Dsth_(),
      pidEff_MisRec_(),
      // -------------------- Mis-ID ------------------- //
      misId_MisRec_mean1Bu_(("misId_MisRec_mean1Bu_" +
                             ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                                .c_str(),
                            "", 5.3330e+03),
      misId_MisRec_mean2Bu_(("misId_MisRec_mean2Bu_" +
                             ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                                .c_str(),
                            "", 5.3416e+03),
      misId_MisRec_sigma1Bu_(("misId_MisRec_sigma1Bu_" +
                              ComposeName(uniqueId, Neutral::gamma,
                                          Bachelor::k))
                                 .c_str(),
                             "", 1.0688e+02),
      misId_MisRec_sigma2Bu_(("misId_MisRec_sigma2Bu_" +
                              ComposeName(uniqueId, Neutral::gamma,
                                          Bachelor::k))
                                 .c_str(),
                             "", 2.5076e+01),
      misId_MisRec_a1Bu_(("misId_MisRec_a1Bu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", 4.8433e+00),
      misId_MisRec_a2Bu_(("misId_MisRec_a2Bu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", -2.9325e-01),
      misId_MisRec_n1Bu_(("misId_MisRec_n1Bu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", 9.6419e+00),
      misId_MisRec_n2Bu_(("misId_MisRec_n2Bu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", 1.0000e+01),
      pdf1Bu_misId_MisRec_(("pdf1Bu_misId_MisRec_" +
                            ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                               .c_str(),
                           "", Configuration::Get().buDeltaMass(),
                           misId_MisRec_mean1Bu_, misId_MisRec_sigma1Bu_,
                           misId_MisRec_a1Bu_, misId_MisRec_n1Bu_),
      pdf2Bu_misId_MisRec_(("pdf2Bu_misId_MisRec_" +
                            ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                               .c_str(),
                           "", Configuration::Get().buDeltaMass(),
                           misId_MisRec_mean2Bu_, misId_MisRec_sigma2Bu_,
                           misId_MisRec_a2Bu_, misId_MisRec_n2Bu_),
      misId_MisRec_fracPdf1Bu_(("misId_MisRec_fracPdf1Bu_" +
                                ComposeName(uniqueId, Neutral::gamma,
                                            Bachelor::k))
                                   .c_str(),
                               "", 5.0098e-01),
      pdfBu_misId_MisRec_(new RooAddPdf(
          ("pdfBu_misId_MisRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", RooArgList(pdf1Bu_misId_MisRec_, pdf2Bu_misId_MisRec_),
          misId_MisRec_fracPdf1Bu_)),
      misId_MisRec_meanBuPartial_(("misId_MisRec_meanBuPartial_" +
                                   ComposeName(uniqueId, Neutral::gamma,
                                               Bachelor::k))
                                      .c_str(),
                                  "", 5.3859e+03),
      misId_MisRec_sigmaLBuPartial_(("misId_MisRec_sigmaLBuPartial_" +
                                     ComposeName(uniqueId, Neutral::gamma,
                                                 Bachelor::k))
                                        .c_str(),
                                    "", 1.0754e+02),
      misId_MisRec_sigmaRBuPartial_(("misId_MisRec_sigmaRBuPartial_" +
                                     ComposeName(uniqueId, Neutral::gamma,
                                                 Bachelor::k))
                                        .c_str(),
                                    "", 6.7291e+01),
      misId_MisRec_aLBuPartial_(("misId_MisRec_aLBuPartial_" +
                                 ComposeName(uniqueId, Neutral::gamma,
                                             Bachelor::k))
                                    .c_str(),
                                "", 3.4482e-02),
      misId_MisRec_aRBuPartial_(("misId_MisRec_aRBuPartial_" +
                                 ComposeName(uniqueId, Neutral::gamma,
                                             Bachelor::k))
                                    .c_str(),
                                "", 1.6765e-01),
      pdfBuPartial_misId_MisRec_(
          ("pdfBuPartial_misId_MisRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), misId_MisRec_meanBuPartial_,
          misId_MisRec_sigmaLBuPartial_, misId_MisRec_sigmaRBuPartial_,
          misId_MisRec_aLBuPartial_, misId_MisRec_aRBuPartial_),
      orEffMisId_MisRec_(("orEffMisId_MisRec_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", 1),
      boxEffMisId_MisRec_(("boxEffMisId_MisRec_" +
                           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                              .c_str(),
                          "", 1),
      boxPartialEffMisId_MisRec_(("boxPartialEffMisId_MisRec_" +
                                  ComposeName(uniqueId, Neutral::gamma,
                                              Bachelor::k))
                                     .c_str(),
                                 "", 1),
      buDeltaCutEffMisId_MisRec_(("buDeltaCutEffMisId_MisRec_" +
                                  ComposeName(uniqueId, Neutral::gamma,
                                              Bachelor::k))
                                     .c_str(),
                                 "", 1),
      deltaCutEffMisId_MisRec_(("deltaCutEffMisId_MisRec_" +
                                ComposeName(uniqueId, Neutral::gamma,
                                            Bachelor::k))
                                   .c_str(),
                               "", 1),
      deltaPartialCutEffMisId_MisRec_(("deltaPartialCutEffMisId_MisRec_" +
                                       ComposeName(uniqueId, Neutral::gamma,
                                                   Bachelor::k))
                                          .c_str(),
                                      "", 1),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_sigmaLBu_(("Bu2D0h_sigmaLBu_" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                           .c_str(),
                       "", 8.8989e+01),  //, 50, 150)),
      Bu2D0h_sigmaRBu_(("Bu2D0h_sigmaRBu_" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                           .c_str(),
                       "", 7.5978e+01),
      // "", 7.5978e+01, 50, 150),
      pdfBu_Bu2D0h_(("pdfBu_Bu2D0h_" +
                     ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_meanBu(),
                    Bu2D0h_sigmaLBu_, Bu2D0h_sigmaRBu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_aLBu(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_aRBu()),
      Bu2D0h_sigmaLBuPartial_(("Bu2D0h_sigmaLBuPartial_" +
                               ComposeName(uniqueId, Neutral::gamma,
                                           Bachelor::k))
                                  .c_str(),
                              // "", 4.8679e+01, 10, 80),
                              // Fixed from data
                              "", 7.2622e+01),
      Bu2D0h_sigmaRBuPartial_(("Bu2D0h_sigmaRBuPartial_" +
                               ComposeName(uniqueId, Neutral::gamma,
                                           Bachelor::k))
                                  .c_str(),
                              // "", 3.5437e+01, 10, 60),
                              // Fixed from data
                              "", 3.2020e+01),
      pdfBuPartial_Bu2D0h_(
          ("pdfBuPartial_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_meanBuPartial(),
          Bu2D0h_sigmaLBuPartial_, Bu2D0h_sigmaRBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_aRBuPartial()),
      // No MC samples for Bu2D0K: no PID efficiency. OK as don't need R values,
      // just need to include fit components. N_K = N_tot. N_π = eff * N_tot
      N_tot_initVal_Bu2D0h_(
          NeutralVars<Neutral::gamma>::Get(uniqueId).initYieldFAVBu2D0h() *
          NeutralVars<Neutral::gamma>::Get(uniqueId).orEffBu2D0h().getVal() *
          0.07768),
      pidEff_Bu2D0h_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2D0h_meanBu_(("misId_Bu2D0h_meanBu_" +
                            ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                               .c_str(),
                           "", 5.6025e+03),
      misId_Bu2D0h_sigmaLBu_(("misId_Bu2D0h_sigmaLBu_" +
                              ComposeName(uniqueId, Neutral::gamma,
                                          Bachelor::k))
                                 .c_str(),
                             "", 1.0153e+02),
      misId_Bu2D0h_sigmaRBu_(("misId_Bu2D0h_sigmaRBu_" +
                              ComposeName(uniqueId, Neutral::gamma,
                                          Bachelor::k))
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
      misId_Bu2D0h_meanBuPartial_(("misId_Bu2D0h_meanBuPartial_" +
                                   ComposeName(uniqueId, Neutral::gamma,
                                               Bachelor::k))
                                      .c_str(),
                                  "", 5.5945e+03),
      misId_Bu2D0h_sigmaLBuPartial_(("misId_Bu2D0h_sigmaLBuPartial_" +
                                     ComposeName(uniqueId, Neutral::gamma,
                                                 Bachelor::k))
                                        .c_str(),
                                    "", 5.4608e+01),
      misId_Bu2D0h_sigmaRBuPartial_(("misId_Bu2D0h_sigmaRBuPartial_" +
                                     ComposeName(uniqueId, Neutral::gamma,
                                                 Bachelor::k))
                                        .c_str(),
                                    "", 4.5399e+01),
      misId_Bu2D0h_aLBuPartial_(("misId_Bu2D0h_aLBuPartial_" +
                                 ComposeName(uniqueId, Neutral::gamma,
                                             Bachelor::k))
                                    .c_str(),
                                "", 1.1435e-01),
      misId_Bu2D0h_aRBuPartial_(("misId_Bu2D0h_aRBuPartial_" +
                                 ComposeName(uniqueId, Neutral::gamma,
                                             Bachelor::k))
                                    .c_str(),
                                "", 2.6725e-01),
      pdfBuPartial_misId_Bu2D0h_(
          ("pdfBuPartial_misId_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), misId_Bu2D0h_meanBuPartial_,
          misId_Bu2D0h_sigmaLBuPartial_, misId_Bu2D0h_sigmaRBuPartial_,
          misId_Bu2D0h_aLBuPartial_, misId_Bu2D0h_aRBuPartial_),
      orEffMisId_Bu2D0h_(("orEffMisId_Bu2D0h_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", 1),
      boxEffMisId_Bu2D0h_(("boxEffMisId_Bu2D0h_" +
                           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                              .c_str(),
                          "", 1),
      boxPartialEffMisId_Bu2D0h_(("boxPartialEffMisId_Bu2D0h_" +
                                  ComposeName(uniqueId, Neutral::gamma,
                                              Bachelor::k))
                                     .c_str(),
                                 "", 1),
      buDeltaCutEffMisId_Bu2D0h_(("buDeltaCutEffMisId_Bu2D0h_" +
                                  ComposeName(uniqueId, Neutral::gamma,
                                              Bachelor::k))
                                     .c_str(),
                                 "", 1),
      deltaCutEffMisId_Bu2D0h_(("deltaCutEffMisId_Bu2D0h_" +
                                ComposeName(uniqueId, Neutral::gamma,
                                            Bachelor::k))
                                   .c_str(),
                               "", 1),
      deltaPartialCutEffMisId_Bu2D0h_(("deltaPartialCutEffMisId_Bu2D0h_" +
                                       ComposeName(uniqueId, Neutral::gamma,
                                                   Bachelor::k))
                                          .c_str(),
                                      "", 1),
      // -------------------- PART REC -------------------- //
      partRec_D0pi0_sigmaLBu_(("partRec_D0pi0_sigmaLBu_" +
                               ComposeName(uniqueId, Neutral::gamma,
                                           Bachelor::k))
                                  .c_str(),
                              "", 1.0957e+02),  //, 10, 150),
      partRec_D0pi0_sigmaRBu_(("partRec_D0pi0_sigmaRBu_" +
                               ComposeName(uniqueId, Neutral::gamma,
                                           Bachelor::k))
                                  .c_str(),
                              "", 7.4595e+01),
      pdfBu_PartRec_D0pi0_(
          ("pdfBu_PartRec_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_D0pi0_meanBu(),
          partRec_D0pi0_sigmaLBu_, partRec_D0pi0_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_D0pi0_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_D0pi0_aRBu()),
      partRec_D0gamma_sigmaLBu_(("partRec_D0gamma_sigmaLBu_" +
                                 ComposeName(uniqueId, Neutral::gamma,
                                             Bachelor::k))
                                    .c_str(),
                                "", 3.5619e+01),
      partRec_D0gamma_sigmaRBu_(("partRec_D0gamma_sigmaRBu_" +
                                 ComposeName(uniqueId, Neutral::gamma,
                                             Bachelor::k))
                                    .c_str(),
                                "", 4.6552e+01),
      pdfBu_PartRec_D0gamma_(
          ("pdfBu_PartRec_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_D0gamma_meanBu(),
          partRec_D0gamma_sigmaLBu_, partRec_D0gamma_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_D0gamma_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_D0gamma_aRBu()),
      pdfBu_PartRec_(new RooAddPdf(
          ("pdfBu_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", RooArgSet(pdfBu_PartRec_D0pi0_, pdfBu_PartRec_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_frac_D0pi0())),
      partRec_sigmaLBuPartial_(("partRec_sigmaLBuPartial_" +
                                ComposeName(uniqueId, Neutral::gamma,
                                            Bachelor::k))
                                   .c_str(),
                               "", 5.0477e+01),
      partRec_sigmaRBuPartial_(("partRec_sigmaRBuPartial_" +
                                ComposeName(uniqueId, Neutral::gamma,
                                            Bachelor::k))
                                   .c_str(),
                               "", 3.3665e+01),
      pdfBuPartial_PartRec_(
          ("pdfBuPartial_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_meanBuPartial(),
          partRec_sigmaLBuPartial_, partRec_sigmaRBuPartial_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_aLBuPartial(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_aRBuPartial()),
      N_tot_initVal_PartRec_(
          NeutralVars<Neutral::gamma>::Get(uniqueId).initYieldFAVPartRec() *
          NeutralVars<Neutral::gamma>::Get(uniqueId).orEffPartRec().getVal() *
          0.02),
      pidEff_Bu2Dst0hst_D0pi0_(),
      pidEff_Bu2Dst0hst_D0gamma_(),
      pidEff_PartRec_(),
      // -------------------- Mis-ID ------------------- //
      misId_PartRec_meanBu_(("misId_PartRec_meanBu_" +
                             ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                                .c_str(),
                            "", 5.1775e+03),
      misId_PartRec_sigmaLBu_(("misId_PartRec_sigmaLBu_" +
                               ComposeName(uniqueId, Neutral::gamma,
                                           Bachelor::k))
                                  .c_str(),
                              "", 7.7049e+01),
      misId_PartRec_sigmaRBu_(("misId_PartRec_sigmaRBu_" +
                               ComposeName(uniqueId, Neutral::gamma,
                                           Bachelor::k))
                                  .c_str(),
                              "", 9.7546e+01),
      misId_PartRec_aLBu_(("misId_PartRec_aLBu_" +
                           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                              .c_str(),
                          "", 9.2782e-08),
      misId_PartRec_aRBu_(("misId_PartRec_aRBu_" +
                           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                              .c_str(),
                          "", 1.4248e-01),
      pdfBu_misId_PartRec_(("pdfBu_misId_PartRec_" +
                            ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                               .c_str(),
                           "", Configuration::Get().buDeltaMass(),
                           misId_PartRec_meanBu_, misId_PartRec_sigmaLBu_,
                           misId_PartRec_sigmaRBu_, misId_PartRec_aLBu_,
                           misId_PartRec_aRBu_),
      misId_PartRec_meanBuPartial_(("misId_PartRec_meanBuPartial_" +
                                    ComposeName(uniqueId, Neutral::gamma,
                                                Bachelor::k))
                                       .c_str(),
                                   "", 5.1786e+03),
      misId_PartRec_sigmaLBuPartial_(("misId_PartRec_sigmaLBuPartial_" +
                                      ComposeName(uniqueId, Neutral::gamma,
                                                  Bachelor::k))
                                         .c_str(),
                                     "", 4.6971e+01),
      misId_PartRec_sigmaRBuPartial_(("misId_PartRec_sigmaRBuPartial_" +
                                      ComposeName(uniqueId, Neutral::gamma,
                                                  Bachelor::k))
                                         .c_str(),
                                     "", 8.1870e+01),
      misId_PartRec_aLBuPartial_(("misId_PartRec_aLBuPartial_" +
                                  ComposeName(uniqueId, Neutral::gamma,
                                              Bachelor::k))
                                     .c_str(),
                                 "", 2.1515e-02),
      misId_PartRec_aRBuPartial_(("misId_PartRec_aRBuPartial_" +
                                  ComposeName(uniqueId, Neutral::gamma,
                                              Bachelor::k))
                                     .c_str(),
                                 "", 1.7988e-01),
      pdfBuPartial_misId_PartRec_(
          ("pdfBuPartial_misId_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), misId_PartRec_meanBuPartial_,
          misId_PartRec_sigmaLBuPartial_, misId_PartRec_sigmaRBuPartial_,
          misId_PartRec_aLBuPartial_, misId_PartRec_aRBuPartial_),
      orEffMisId_PartRec_(("orEffMisId_PartRec_" +
                           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                              .c_str(),
                          "", 1),
      boxEffMisId_PartRec_(("boxEffMisId_PartRec_" +
                            ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                               .c_str(),
                           "", 1),
      boxPartialEffMisId_PartRec_(("boxPartialEffMisId_PartRec_" +
                                   ComposeName(uniqueId, Neutral::gamma,
                                               Bachelor::k))
                                      .c_str(),
                                  "", 1),
      buDeltaCutEffMisId_PartRec_(("buDeltaCutEffMisId_PartRec_" +
                                   ComposeName(uniqueId, Neutral::gamma,
                                               Bachelor::k))
                                      .c_str(),
                                  "", 1),
      deltaCutEffMisId_PartRec_(("deltaCutEffMisId_PartRec_" +
                                 ComposeName(uniqueId, Neutral::gamma,
                                             Bachelor::k))
                                    .c_str(),
                                "", 1),
      deltaPartialCutEffMisId_PartRec_(("deltaPartialCutEffMisId_PartRec_" +
                                        ComposeName(uniqueId, Neutral::gamma,
                                                    Bachelor::k))
                                           .c_str(),
                                       "", 1) {
  Configuration::Get().SetEfficiencies(
      Mode::Bu2Dst0pi_D0gamma, Bachelor::k, orEffMisId_Bu2Dst0h_D0gamma_,
      boxEffMisId_Bu2Dst0h_D0gamma_, buDeltaCutEffMisId_Bu2Dst0h_D0gamma_,
      deltaCutEffMisId_Bu2Dst0h_D0gamma_, true);

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

  double orEffMisId_MisRecVal = 0.0;
  double boxEffMisId_MisRecVal = 0.0;
  double buDeltaCutEffMisId_MisRecVal = 0.0;
  double deltaCutEffMisId_MisRecVal = 0.0;

  std::map<Mode, double> partRecModesMap = {
      {Mode::Bu2Dst0rho_D0pi0,
       NeutralVars<Neutral::gamma>::Get(uniqueId)
               .fracPartRec_Bu2Dst0hst_D0pi0() /
           NeutralVars<Neutral::gamma>::Get(uniqueId).fracPartRec()},
      {Mode::Bu2Dst0rho_D0gamma,
       NeutralVars<Neutral::gamma>::Get(uniqueId)
               .fracPartRec_Bu2Dst0hst_D0gamma() /
           NeutralVars<Neutral::gamma>::Get(uniqueId).fracPartRec()}};

  double orEffMisId_PartRecVal = 0.0;
  double boxEffMisId_PartRecVal = 0.0;
  double buDeltaCutEffMisId_PartRecVal = 0.0;
  double deltaCutEffMisId_PartRecVal = 0.0;

  RooRealVar orEffMisIdTemp(
      ("orEffMisIdTemp" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
      1);
  RooRealVar boxEffMisIdTemp(
      ("boxEffMisIdTemp" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
      1);
  RooRealVar buDeltaCutEffMisIdTemp(
      ("buDeltaCutEffMisIdTemp" + ComposeName(uniqueId, Neutral::gamma))
          .c_str(),
      "", 1);
  RooRealVar deltaCutEffMisIdTemp(
      ("deltaCutEffMisIdTemp" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
      "", 1);

  if (Configuration::Get().fitBuPartial() == true) {
    Configuration::Get().SetEfficiencies(
        Mode::Bu2Dst0pi_D0pi0, Bachelor::k, orEffMisId_Bu2Dst0h_D0pi0_,
        boxEffMisId_Bu2Dst0h_D0pi0_, boxPartialEffMisId_Bu2Dst0h_D0pi0_,
        buDeltaCutEffMisId_Bu2Dst0h_D0pi0_, deltaCutEffMisId_Bu2Dst0h_D0pi0_,
        deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_, true);

    RooRealVar boxPartialEffMisIdTemp(
        ("boxPartialEffMisIdTemp" + ComposeName(uniqueId, Neutral::gamma))
            .c_str(),
        "", 1);
    RooRealVar deltaPartialCutEffMisIdTemp(
        ("deltaPartialCutEffMisIdTemp" + ComposeName(uniqueId, Neutral::gamma))
            .c_str(),
        "", 1);

    double boxPartialEffMisId_MisRecVal = 0.0;
    double deltaPartialCutEffMisId_MisRecVal = 0.0;
    for (auto &m : misRecModesMap) {
      Configuration::Get().SetEfficiencies(
          m.first, Bachelor::k, orEffMisIdTemp, boxEffMisIdTemp,
          boxPartialEffMisIdTemp, buDeltaCutEffMisIdTemp, deltaCutEffMisIdTemp,
          deltaPartialCutEffMisIdTemp, true);

      orEffMisId_MisRecVal += orEffMisIdTemp.getVal() * m.second;
      boxEffMisId_MisRecVal += boxEffMisIdTemp.getVal() * m.second;
      boxPartialEffMisId_MisRecVal +=
          boxPartialEffMisIdTemp.getVal() * m.second;
      buDeltaCutEffMisId_MisRecVal +=
          buDeltaCutEffMisIdTemp.getVal() * m.second;
      deltaCutEffMisId_MisRecVal += deltaCutEffMisIdTemp.getVal() * m.second;
      deltaPartialCutEffMisId_MisRecVal +=
          deltaPartialCutEffMisIdTemp.getVal() * m.second;
    }
    boxPartialEffMisId_MisRec_.setVal(boxPartialEffMisId_MisRecVal);
    deltaPartialCutEffMisId_MisRec_.setVal(deltaPartialCutEffMisId_MisRecVal);

    Configuration::Get().SetEfficiencies(
        Mode::Bu2D0pi, Bachelor::k, orEffMisId_Bu2D0h_, boxEffMisId_Bu2D0h_,
        boxPartialEffMisId_Bu2D0h_, buDeltaCutEffMisId_Bu2D0h_,
        deltaCutEffMisId_Bu2D0h_, deltaPartialCutEffMisId_Bu2D0h_, true);

    double boxPartialEffMisId_PartRecVal = 0.0;
    double deltaPartialCutEffMisId_PartRecVal = 0.0;
    for (auto &m : misRecModesMap) {
      Configuration::Get().SetEfficiencies(
          m.first, Bachelor::k, orEffMisIdTemp, boxEffMisIdTemp,
          boxPartialEffMisIdTemp, buDeltaCutEffMisIdTemp, deltaCutEffMisIdTemp,
          deltaPartialCutEffMisIdTemp, true);

      orEffMisId_PartRecVal += orEffMisIdTemp.getVal() * m.second;
      boxEffMisId_PartRecVal += boxEffMisIdTemp.getVal() * m.second;
      boxPartialEffMisId_PartRecVal +=
          boxPartialEffMisIdTemp.getVal() * m.second;
      buDeltaCutEffMisId_PartRecVal +=
          buDeltaCutEffMisIdTemp.getVal() * m.second;
      deltaCutEffMisId_PartRecVal += deltaCutEffMisIdTemp.getVal() * m.second;
      deltaPartialCutEffMisId_PartRecVal +=
          deltaPartialCutEffMisIdTemp.getVal() * m.second;
    }
    boxPartialEffMisId_PartRec_.setVal(boxPartialEffMisId_PartRecVal);
    deltaPartialCutEffMisId_PartRec_.setVal(deltaPartialCutEffMisId_PartRecVal);
  } else {
    Configuration::Get().SetEfficiencies(
        Mode::Bu2Dst0pi_D0pi0, Bachelor::k, orEffMisId_Bu2Dst0h_D0pi0_,
        boxEffMisId_Bu2Dst0h_D0pi0_, buDeltaCutEffMisId_Bu2Dst0h_D0pi0_,
        deltaCutEffMisId_Bu2Dst0h_D0pi0_, true);

    for (auto &m : misRecModesMap) {
      Configuration::Get().SetEfficiencies(
          m.first, Bachelor::k, orEffMisIdTemp, boxEffMisIdTemp,
          buDeltaCutEffMisIdTemp, deltaCutEffMisIdTemp, true);

      orEffMisId_MisRecVal += orEffMisIdTemp.getVal() * m.second;
      boxEffMisId_MisRecVal += boxEffMisIdTemp.getVal() * m.second;
      buDeltaCutEffMisId_MisRecVal +=
          buDeltaCutEffMisIdTemp.getVal() * m.second;
      deltaCutEffMisId_MisRecVal += deltaCutEffMisIdTemp.getVal() * m.second;
    }

    Configuration::Get().SetEfficiencies(
        Mode::Bu2D0pi, Bachelor::k, orEffMisId_Bu2D0h_, boxEffMisId_Bu2D0h_,
        buDeltaCutEffMisId_Bu2D0h_, deltaCutEffMisId_Bu2D0h_, true);

    for (auto &m : misRecModesMap) {
      Configuration::Get().SetEfficiencies(
          m.first, Bachelor::k, orEffMisIdTemp, boxEffMisIdTemp,
          buDeltaCutEffMisIdTemp, deltaCutEffMisIdTemp, true);

      orEffMisId_PartRecVal += orEffMisIdTemp.getVal() * m.second;
      boxEffMisId_PartRecVal += boxEffMisIdTemp.getVal() * m.second;
      buDeltaCutEffMisId_PartRecVal +=
          buDeltaCutEffMisIdTemp.getVal() * m.second;
      deltaCutEffMisId_PartRecVal += deltaCutEffMisIdTemp.getVal() * m.second;
    }
  }
  orEffMisId_MisRec_.setVal(orEffMisId_MisRecVal);
  boxEffMisId_MisRec_.setVal(boxEffMisId_MisRecVal);
  buDeltaCutEffMisId_MisRec_.setVal(buDeltaCutEffMisId_MisRecVal);
  deltaCutEffMisId_MisRec_.setVal(deltaCutEffMisId_MisRecVal);

  orEffMisId_PartRec_.setVal(orEffMisId_PartRecVal);
  boxEffMisId_PartRec_.setVal(boxEffMisId_PartRecVal);
  buDeltaCutEffMisId_PartRec_.setVal(buDeltaCutEffMisId_PartRecVal);
  deltaCutEffMisId_PartRec_.setVal(deltaCutEffMisId_PartRecVal);

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
  //
  // std::cout << "\t orEffMisId_PartRec = " << orEffMisId_PartRec_.getVal()
  // <<
  // "\n"
  //           << "\t boxEffMisId_PartRec = " << boxEffMisId_PartRec_.getVal()
  //           << "\n"
  //           << "\t buDeltaCutEffMisId_PartRec = "
  //           << buDeltaCutEffMisId_PartRec_.getVal() << "\n"
  //           << "\t deltaCutEffMisId_PartRec = "
  //           << deltaCutEffMisId_PartRec_.getVal() << "\n"
  //           << "\t deltaPartialCutEffMisId_PartRec = "
  //           << deltaPartialCutEffMisId_PartRec_.getVal() << "\n";
  //
  // std::cout << "\t orEffMisId_MisRec = " << orEffMisId_MisRec_.getVal() <<
  // "\n"
  //           << "\t boxEffMisId_MisRec = " << boxEffMisId_MisRec_.getVal()
  //           << "\n"
  //           << "\t buDeltaCutEffMisId_MisRec = "
  //           << buDeltaCutEffMisId_MisRec_.getVal() << "\n"
  //           << "\t deltaCutEffMisId_MisRec = "
  //           << deltaCutEffMisId_MisRec_.getVal() << "\n"
  //           << "\t deltaPartialCutEffMisId_MisRec = "
  //           << deltaPartialCutEffMisId_MisRec_.getVal() << "\n";
  //
  // std::cout << "\t orEffMisId_Bu2D0h = " << orEffMisId_Bu2D0h_.getVal()
  // <<
  // "\n"
  //           << "\t boxEffMisId_Bu2D0h = " << boxEffMisId_Bu2D0h_.getVal()
  //           << "\n"
  //           << "\t buDeltaCutEffMisId_Bu2D0h = "
  //           << buDeltaCutEffMisId_Bu2D0h_.getVal() << "\n"
  //           << "\t deltaCutEffMisId_Bu2D0h = "
  //           << deltaCutEffMisId_Bu2D0h_.getVal() << "\n"
  //           << "\t deltaPartialCutEffMisId_Bu2D0h = "
  //           << deltaPartialCutEffMisId_Bu2D0h_.getVal() << "\n";
}
