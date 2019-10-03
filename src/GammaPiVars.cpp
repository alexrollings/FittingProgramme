#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- Bu2Dst0h_D0gamma -------------------- //
    : Bu2Dst0h_D0gamma_sigma1Bu_(
          new RooRealVar(("Bu2Dst0h_D0gamma_sigma1Bu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         "", 2.0271e+01)),
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
      N_tot_Bu2Dst0h_D0gamma_(("N_tot_Bu2Dst0h_D0gamma_" +
                               ComposeName(uniqueId, Neutral::gamma,
                                           Bachelor::pi))
                                  .c_str(),
                              "", NeutralVars<Neutral::gamma>::Get(uniqueId)
                                          .initYieldFAVBu2Dst0h_D0gamma() *
                                      NeutralVars<Neutral::gamma>::Get(uniqueId)
                                          .orEffBu2Dst0h_D0gamma()
                                          .getVal(),
                              -1000000, 1000000),
      pidEff_Bu2Dst0h_D0gamma_(("pidEff_Bu2Dst0h_D0gamma_" +
                                ComposeName(uniqueId, Neutral::gamma,
                                            Bachelor::pi))
                                   .c_str(),
                               "", 0.997043),
      N_Bu2Dst0h_D0gamma_(("N_Bu2Dst0h_D0gamma_" +
                           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                              .c_str(),
                          "@0*@1", RooArgList(N_tot_Bu2Dst0h_D0gamma_,
                                              pidEff_Bu2Dst0h_D0gamma_)),
      N_Delta_Bu2Dst0h_D0gamma_(
          ("N_Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "(@0/@1)*@2", RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .buDeltaCutEffBu2Dst0h_D0gamma(),
                                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .orEffBu2Dst0h_D0gamma(),
                                   N_Bu2Dst0h_D0gamma_)),
      N_Bu_Bu2Dst0h_D0gamma_(nullptr),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_meanBu_(("misId_Bu2Dst0h_D0gamma_meanBu_" +
                                      ComposeName(uniqueId, Neutral::gamma,
                                                  Bachelor::pi))
                                         .c_str(),
                                     "", 5.2359e+03),
      misId_Bu2Dst0h_D0gamma_sigma1Bu_(("misId_Bu2Dst0h_D0gamma_sigma1Bu_" +
                                        ComposeName(uniqueId, Neutral::gamma,
                                                    Bachelor::pi))
                                           .c_str(),
                                       "", 3.1411e+01),
      misId_Bu2Dst0h_D0gamma_sigma2Bu_(("misId_Bu2Dst0h_D0gamma_sigma2Bu_" +
                                        ComposeName(uniqueId, Neutral::gamma,
                                                    Bachelor::pi))
                                           .c_str(),
                                       "", 2.1604e+01),
      misId_Bu2Dst0h_D0gamma_a1Bu_(("misId_Bu2Dst0h_D0gamma_a1Bu_" +
                                    ComposeName(uniqueId, Neutral::gamma,
                                                Bachelor::pi))
                                       .c_str(),
                                   "", 1.5167e-01),
      misId_Bu2Dst0h_D0gamma_a2Bu_(("misId_Bu2Dst0h_D0gamma_a2Bu_" +
                                    ComposeName(uniqueId, Neutral::gamma,
                                                Bachelor::pi))
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
      orEffMisId_Bu2Dst0h_D0gamma_(("orEffMisId_Bu2Dst0h_D0gamma_" +
                                    ComposeName(uniqueId, Neutral::gamma,
                                                Bachelor::pi))
                                       .c_str(),
                                   "", 1),
      boxEffMisId_Bu2Dst0h_D0gamma_(("boxEffMisId_Bu2Dst0h_D0gamma_" +
                                     ComposeName(uniqueId, Neutral::gamma,
                                                 Bachelor::pi))
                                        .c_str(),
                                    "", 1),
      buDeltaCutEffMisId_Bu2Dst0h_D0gamma_(
          ("buDeltaCutEffMisId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", 1),
      deltaCutEffMisId_Bu2Dst0h_D0gamma_(("deltaCutEffMisId_Bu2Dst0h_D0gamma_" +
                                          ComposeName(uniqueId, Neutral::gamma,
                                                      Bachelor::pi))
                                             .c_str(),
                                         "", 1),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      Bu2Dst0h_D0pi0_sigma1Bu_(
          new RooRealVar(("Bu2Dst0h_D0pi0_sigma1Bu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         "", 4.3979e+01)),
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
      N_tot_Bu2Dst0h_D0pi0_(("N_tot_Bu2Dst0h_D0pi0_" +
                             ComposeName(uniqueId, Neutral::gamma,
                                         Bachelor::pi))
                                .c_str(),
                            "", NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .initYieldFAVBu2Dst0h_D0pi0() *
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .orEffBu2Dst0h_D0pi0()
                                        .getVal(),
                            -1000000, 1000000),
      pidEff_Bu2Dst0h_D0pi0_(("pidEff_Bu2Dst0h_D0pi0_" +
                              ComposeName(uniqueId, Neutral::gamma,
                                          Bachelor::pi))
                                 .c_str(),
                             "", 0.996942),
      N_Bu2Dst0h_D0pi0_(("N_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                            .c_str(),
                        "@0*@1", RooArgList(N_tot_Bu2Dst0h_D0pi0_,
                                            pidEff_Bu2Dst0h_D0pi0_)),
      N_Delta_Bu2Dst0h_D0pi0_(
          ("N_Delta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .buDeltaCutEffBu2Dst0h_D0pi0(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
              N_Bu2Dst0h_D0pi0_)),
      N_Bu_Bu2Dst0h_D0pi0_(nullptr),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0pi0_meanBu_(("misId_Bu2Dst0h_D0pi0_meanBu_" +
                                    ComposeName(uniqueId, Neutral::gamma,
                                                Bachelor::pi))
                                       .c_str(),
                                   "", 5.3067e+03),
      misId_Bu2Dst0h_D0pi0_sigma1Bu_(("misId_Bu2Dst0h_D0pi0_sigma1Bu_" +
                                      ComposeName(uniqueId, Neutral::gamma,
                                                  Bachelor::pi))
                                         .c_str(),
                                     "", 9.9388e+01),
      misId_Bu2Dst0h_D0pi0_sigma2Bu_(("misId_Bu2Dst0h_D0pi0_sigma2Bu_" +
                                      ComposeName(uniqueId, Neutral::gamma,
                                                  Bachelor::pi))
                                         .c_str(),
                                     "", 3.8744e+01),
      misId_Bu2Dst0h_D0pi0_a1Bu_(("misId_Bu2Dst0h_D0pi0_a1Bu_" +
                                  ComposeName(uniqueId, Neutral::gamma,
                                              Bachelor::pi))
                                     .c_str(),
                                 "", 1.2847e-05),
      misId_Bu2Dst0h_D0pi0_a2Bu_(("misId_Bu2Dst0h_D0pi0_a2Bu_" +
                                  ComposeName(uniqueId, Neutral::gamma,
                                              Bachelor::pi))
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
      orEffMisId_Bu2Dst0h_D0pi0_(("orEffMisId_Bu2Dst0h_D0pi0_" +
                                  ComposeName(uniqueId, Neutral::gamma,
                                              Bachelor::pi))
                                     .c_str(),
                                 "", 1),
      boxEffMisId_Bu2Dst0h_D0pi0_(("boxEffMisId_Bu2Dst0h_D0pi0_" +
                                   ComposeName(uniqueId, Neutral::gamma,
                                               Bachelor::pi))
                                      .c_str(),
                                  "", 1),
      buDeltaCutEffMisId_Bu2Dst0h_D0pi0_(("buDeltaCutEffMisId_Bu2Dst0h_D0pi0_" +
                                          ComposeName(uniqueId, Neutral::gamma,
                                                      Bachelor::pi))
                                             .c_str(),
                                         "", 1),
      deltaCutEffMisId_Bu2Dst0h_D0pi0_(("deltaCutEffMisId_Bu2Dst0h_D0pi0_" +
                                        ComposeName(uniqueId, Neutral::gamma,
                                                    Bachelor::pi))
                                           .c_str(),
                                       "", 1),
      // -------------------- MIS-REC -------------------- //
      MisRec_sigmaLBu_(("MisRec_sigmaLBu_" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                           .c_str(),
                       "", 1.0404e+02),
      MisRec_sigmaRBu_(("MisRec_sigmaRBu_" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                           .c_str(),
                       "", 9.6206e+01),
      pdfBu_MisRec_(("pdfBu_MisRec_" +
                     ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_meanBu(),
                    MisRec_sigmaLBu_, MisRec_sigmaRBu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aLBu(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aRBu()),
      N_tot_MisRec_(
          ("N_tot_MisRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "",
          NeutralVars<Neutral::gamma>::Get(uniqueId).initYieldFAVMisRec() *
              NeutralVars<Neutral::gamma>::Get(uniqueId).orEffMisRec().getVal(),
          -1000000, 1000000),
      pidEff_Bu2Dst0h_D0gamma_WN_(0.997109),
      pidEff_Bu2Dst0h_D0pi0_WN_(0.996147),
      pidEff_Bu2D0hst_(0.996808),
      pidEff_Bd2Dsth_(0.9974),
      pidEff_MisRec_(
          ("pidEff_MisRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", (pidEff_Bu2Dst0h_D0gamma_WN_ *
                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                       .fracMisRec_Bu2Dst0h_D0gamma_WN() +
               pidEff_Bu2Dst0h_D0pi0_WN_ *
                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                       .fracMisRec_Bu2Dst0h_D0pi0_WN() +
               pidEff_Bu2D0hst_ *
                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                       .fracMisRec_Bu2D0hst() +
               pidEff_Bd2Dsth_ *
                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                       .fracMisRec_Bd2Dsth()) /
                  NeutralVars<Neutral::gamma>::Get(uniqueId).fracMisRec()),
      N_MisRec_(("N_MisRec_" +
                 ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                    .c_str(),
                "@0*@1", RooArgList(N_tot_MisRec_, pidEff_MisRec_)),
      N_Delta_MisRec_(
          ("N_Delta_MisRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId).buDeltaCutEffMisRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).orEffMisRec(),
              N_MisRec_)),
      N_Bu_MisRec_(nullptr),
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
      orEffMisId_MisRec_(),
      boxEffMisId_MisRec_(),
      buDeltaCutEffMisId_MisRec_(),
      deltaCutEffMisId_MisRec_(),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_sigmaLBu_(new RooRealVar(("Bu2D0h_sigmaLBu_" +
                                       ComposeName(uniqueId, Neutral::gamma,
                                                   Bachelor::pi))
                                          .c_str(),
                                      "", 8.8989e+01)),
      Bu2D0h_sigmaRBu_(new RooRealVar(("Bu2D0h_sigmaRBu_" +
                                       ComposeName(uniqueId, Neutral::gamma,
                                                   Bachelor::pi))
                                          .c_str(),
                                      "", 7.5978e+01)),
      pdfBu_Bu2D0h_(("pdfBu_Bu2D0h_" +
                     ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_meanBu(),
                    *Bu2D0h_sigmaLBu_, *Bu2D0h_sigmaRBu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_aLBu(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2D0h_aRBu()),
      N_tot_Bu2D0h_(
          ("N_tot_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "",
          NeutralVars<Neutral::gamma>::Get(uniqueId).initYieldFAVBu2D0h() *
              NeutralVars<Neutral::gamma>::Get(uniqueId).orEffBu2D0h().getVal(),
          -1000000, 1000000),
      pidEff_Bu2D0h_(("pidEff_Bu2D0h_" +
                      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                         .c_str(),
                     "", 0.996587),
      N_Bu2D0h_(("N_Bu2D0h_" +
                 ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                    .c_str(),
                "@0*@1", RooArgList(N_tot_Bu2D0h_, pidEff_Bu2D0h_)),
      N_Delta_Bu2D0h_(
          ("N_Delta_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId).buDeltaCutEffBu2D0h(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).orEffBu2D0h(),
              N_Bu2D0h_)),
      N_Bu_Bu2D0h_(nullptr),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2D0h_meanBu_(),
      misId_Bu2D0h_sigmaLBu_(),
      misId_Bu2D0h_sigmaRBu_(),
      misId_Bu2D0h_aLBu_(),
      misId_Bu2D0h_aRBu_(),
      pdfBu_misId_Bu2D0h_(),
      orEffMisId_Bu2D0h_(),
      boxEffMisId_Bu2D0h_(),
      buDeltaCutEffMisId_Bu2D0h_(),
      deltaCutEffMisId_Bu2D0h_(),
      // -------------------- PART REC -------------------- //
      partRec_D0pi0_sigmaLBu_(("partRec_D0pi0_sigmaLBu_" +
                               ComposeName(uniqueId, Neutral::gamma,
                                           Bachelor::pi))
                                  .c_str(),
                              "", 1.0957e+02),//, 10, 150),
      partRec_D0pi0_sigmaRBu_(("partRec_D0pi0_sigmaRBu_" +
                               ComposeName(uniqueId, Neutral::gamma,
                                           Bachelor::pi))
                                  .c_str(),
                              "", 7.4595e+01),
      pdfBu_PartRec_D0pi0_(
          ("pdfBu_PartRec_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_D0pi0_meanBu(),
          partRec_D0pi0_sigmaLBu_, partRec_D0pi0_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_D0pi0_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).partRec_D0pi0_aRBu()),
      partRec_D0gamma_sigmaLBu_(("partRec_D0gamma_sigmaLBu_" +
                                 ComposeName(uniqueId, Neutral::gamma,
                                             Bachelor::pi))
                                    .c_str(),
                                "", 3.5619e+01),
      partRec_D0gamma_sigmaRBu_(("partRec_D0gamma_sigmaRBu_" +
                                 ComposeName(uniqueId, Neutral::gamma,
                                             Bachelor::pi))
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
      N_tot_PartRec_(
          ("N_tot_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", NeutralVars<Neutral::gamma>::Get(uniqueId).initYieldFAVPartRec() *
                  NeutralVars<Neutral::gamma>::Get(uniqueId)
                      .orEffPartRec()
                      .getVal(),
          // -1000000, 1000000),
          0, 100000),
      pidEff_Bu2Dst0hst_D0pi0_(0.999413),
      pidEff_Bu2Dst0hst_D0gamma_(0.998193),
      pidEff_PartRec_(
          ("pidEff_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", (pidEff_Bu2Dst0hst_D0gamma_ *
                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                       .fracPartRec_Bu2Dst0hst_D0gamma() +
               pidEff_Bu2Dst0hst_D0pi0_ *
                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                       .fracPartRec_Bu2Dst0hst_D0pi0()) /
                  NeutralVars<Neutral::gamma>::Get(uniqueId).fracPartRec()),
      N_PartRec_(("N_PartRec_" +
                  ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                     .c_str(),
                 "@0*@1", RooArgList(N_tot_PartRec_, pidEff_PartRec_)),
      N_Delta_PartRec_(
          ("N_Delta_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId).buDeltaCutEffPartRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).orEffPartRec(),
              N_PartRec_)),
      N_Bu_PartRec_(nullptr),
      // -------------------- Mis-ID ------------------- //
      misId_PartRec_meanBu_(),
      misId_PartRec_sigmaLBu_(),
      misId_PartRec_sigmaRBu_(),
      misId_PartRec_aLBu_(),
      misId_PartRec_aRBu_(),
      pdfBu_misId_PartRec_(),
      orEffMisId_PartRec_(),
      boxEffMisId_PartRec_(),
      buDeltaCutEffMisId_PartRec_(),
      deltaCutEffMisId_PartRec_() {
  if (Configuration::Get().fit1D() == false) {
    N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<Neutral::gamma>::Get(uniqueId)
                .deltaCutEffBu2Dst0h_D0gamma(),
            NeutralVars<Neutral::gamma>::Get(uniqueId).orEffBu2Dst0h_D0gamma(),
            N_Bu2Dst0h_D0gamma_)));
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<Neutral::gamma>::Get(uniqueId)
                .deltaCutEffBu2Dst0h_D0pi0(),
            NeutralVars<Neutral::gamma>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
            N_Bu2Dst0h_D0pi0_)));
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_MisRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<Neutral::gamma>::Get(uniqueId).deltaCutEffMisRec(),
            NeutralVars<Neutral::gamma>::Get(uniqueId).orEffMisRec(),
            N_MisRec_)));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2D0h_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<Neutral::gamma>::Get(uniqueId).deltaCutEffBu2D0h(),
            NeutralVars<Neutral::gamma>::Get(uniqueId).orEffBu2D0h(),
            N_Bu2D0h_)));
    N_Bu_PartRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_PartRec_" +
         ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
            .c_str(),
        "(@0/@1)*@2", RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                     .deltaCutEffPartRec(),
                                 NeutralVars<Neutral::gamma>::Get(uniqueId)
                                     .orEffPartRec(),
                                 N_PartRec_)));
  } else {
    N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
            .c_str(),
        "@0*@1",
        RooArgList(N_tot_Bu2Dst0h_D0gamma_, pidEff_Bu2Dst0h_D0gamma_)));
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
            .c_str(),
        "@0*@1", RooArgList(N_tot_Bu2Dst0h_D0pi0_, pidEff_Bu2Dst0h_D0pi0_)));
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_MisRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
            .c_str(),
        "@0*@1", RooArgList(N_tot_MisRec_, pidEff_MisRec_)));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2D0h_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
            .c_str(),
        "@0*@1", RooArgList(N_tot_Bu2D0h_, pidEff_Bu2D0h_)));
    N_Bu_PartRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_PartRec_" +
         ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
            .c_str(),
        "@0*@1",
        RooArgList(N_tot_PartRec_, pidEff_PartRec_)));
  }
}
