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
      N_tot_Bu2Dst0h_D0gamma_(("N_tot_Bu2Dst0h_D0gamma_" +
                               ComposeName(uniqueId, Neutral::gamma,
                                           Bachelor::k))
                                  .c_str(),
                              "", NeutralVars<Neutral::gamma>::Get(uniqueId)
                                          .initYieldFAVBu2Dst0h_D0gamma() *
                                      NeutralVars<Neutral::gamma>::Get(uniqueId)
                                          .orEffBu2Dst0h_D0gamma()
                                          .getVal() *
                                      0.07930,
                              -1000000, 1000000),
      pidEff_Bu2Dst0h_D0gamma_(("pidEff_Bu2Dst0h_D0gamma_" +
                                ComposeName(uniqueId, Neutral::gamma,
                                            Bachelor::k))
                                   .c_str(),
                               "",  6.8493e-01),
      N_Bu2Dst0h_D0gamma_(("N_Bu2Dst0h_D0gamma_" +
                           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                              .c_str(),
                          "@0*@1", RooArgList(N_tot_Bu2Dst0h_D0gamma_,
                                              pidEff_Bu2Dst0h_D0gamma_)),
      N_Delta_Bu2Dst0h_D0gamma_(
          ("N_Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
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
      N_tot_Bu2Dst0h_D0pi0_(("N_tot_Bu2Dst0h_D0pi0_" +
                             ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                                .c_str(),
                            "", NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .initYieldFAVBu2Dst0h_D0pi0() *
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .orEffBu2Dst0h_D0pi0()
                                        .getVal() *
                                    0.07930,
                            -1000000, 1000000),
      pidEff_Bu2Dst0h_D0pi0_(("pidEff_Bu2Dst0h_D0pi0_" +
                              ComposeName(uniqueId, Neutral::gamma,
                                          Bachelor::k))
                                 .c_str(),
                             "", 0.745534),
      N_Bu2Dst0h_D0pi0_(("N_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "@0*@1", RooArgList(N_tot_Bu2Dst0h_D0pi0_,
                                            pidEff_Bu2Dst0h_D0pi0_)),
      N_Delta_Bu2Dst0h_D0pi0_(
          ("N_Delta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
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
      // -------------------- MIS-REC -------------------- //
      MisRec_sigmaLBu_(("MisRec_sigmaLBu_" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                           .c_str(),
                       "", 1.0404e+02),
      MisRec_sigmaRBu_(("MisRec_sigmaRBu_" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                           .c_str(),
                       "", 9.6206e+01),
      pdfBu_MisRec_(
          ("pdfBu_MisRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_meanBu(),
          MisRec_sigmaLBu_, MisRec_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aRBu()),
      N_tot_MisRec_(
          ("N_tot_MisRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", NeutralVars<Neutral::gamma>::Get(uniqueId).initYieldFAVMisRec() *
                  NeutralVars<Neutral::gamma>::Get(uniqueId)
                      .orEffMisRec()
                      .getVal() *
                  0.06,
          -1000000, 1000000),
      pidEff_Bu2Dst0h_D0gamma_WN_(),
      pidEff_Bu2Dst0h_D0pi0_WN_(),
      pidEff_Bu2D0hst_(),
      pidEff_Bd2Dsth_(),
      pidEff_MisRec_(),
      N_MisRec_(("N_MisRec_" +
                 ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                    .c_str(),
                "@0", RooArgList(N_tot_MisRec_)),
      N_Delta_MisRec_(
          ("N_Delta_MisRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId).buDeltaCutEffMisRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).orEffMisRec(),
              N_MisRec_)),
      N_Bu_MisRec_(nullptr),
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
      orEffMisId_MisRec_(("orEffMisId_MisRec_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", 1),
      boxEffMisId_MisRec_(("boxEffMisId_MisRec_" +
                           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
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
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_sigmaLBu_(("Bu2D0h_sigmaLBu_" +
                                       ComposeName(uniqueId, Neutral::gamma,
                                                   Bachelor::k))
                                          .c_str(),
                                      "", 8.8989e+01),//, 50, 150)),
      Bu2D0h_sigmaRBu_(("Bu2D0h_sigmaRBu_" +
                                       ComposeName(uniqueId, Neutral::gamma,
                                                   Bachelor::k))
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
      // No MC samples for Bu2D0K: no PID efficiency. OK as don't need R values,
      // just need to include fit components. N_K = N_tot. N_π = eff * N_tot
      N_tot_Bu2D0h_(
          ("N_tot_Bu2D0h_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", NeutralVars<Neutral::gamma>::Get(uniqueId).initYieldFAVBu2D0h() *
                  NeutralVars<Neutral::gamma>::Get(uniqueId)
                      .orEffBu2D0h()
                      .getVal() *
                  0.07768,
          -1000000, 1000000),
      pidEff_Bu2D0h_(),
      N_Bu2D0h_(("N_Bu2D0h_" +
                 ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                    .c_str(),
                "@0", RooArgList(N_tot_Bu2D0h_)),
      N_Delta_Bu2D0h_(
          ("N_Delta_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId).buDeltaCutEffBu2D0h(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).orEffBu2D0h(),
              N_Bu2D0h_)),
      N_Bu_Bu2D0h_(nullptr),
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
      orEffMisId_Bu2D0h_(("orEffMisId_Bu2D0h_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                             .c_str(),
                         "", 1),
      boxEffMisId_Bu2D0h_(("boxEffMisId_Bu2D0h_" +
                           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
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
      // -------------------- PART REC -------------------- //
      partRec_D0pi0_sigmaLBu_(("partRec_D0pi0_sigmaLBu_" +
                                    ComposeName(uniqueId, Neutral::gamma,
                                                Bachelor::k))
                                       .c_str(),
                                   "", 1.0957e+02),//, 10, 150),
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
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .partRec_frac_D0pi0())),
      N_tot_PartRec_(("N_tot_PartRec_" +
                                 ComposeName(uniqueId, Neutral::gamma,
                                             Bachelor::k))
                                    .c_str(),
                                "", NeutralVars<Neutral::gamma>::Get(uniqueId)
                                            .initYieldFAVPartRec() *
                                        NeutralVars<Neutral::gamma>::Get(uniqueId)
                                            .orEffPartRec()
                                            .getVal() *
                                        0.02,
                                // -1000000, 1000000),
                                0, 100000),
      pidEff_Bu2Dst0hst_D0pi0_(),
      pidEff_Bu2Dst0hst_D0gamma_(),
      pidEff_PartRec_(),
      N_PartRec_(("N_PartRec_" +
                             ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                                .c_str(),
                            "@0", RooArgList(N_tot_PartRec_)),
      N_Delta_PartRec_(
          ("N_Delta_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "(@0/@1)*@2", RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .buDeltaCutEffPartRec(),
                                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .orEffPartRec(),
                                   N_PartRec_)),
      N_Bu_PartRec_(nullptr),
      // -------------------- Mis-ID ------------------- //
      misId_PartRec_meanBu_(("misId_PartRec_meanBu_" +
                                        ComposeName(uniqueId, Neutral::gamma,
                                                    Bachelor::k))
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
                                      ComposeName(uniqueId, Neutral::gamma,
                                                  Bachelor::k))
                                         .c_str(),
                                     "", 9.2782e-08),
      misId_PartRec_aRBu_(("misId_PartRec_aRBu_" +
                                      ComposeName(uniqueId, Neutral::gamma,
                                                  Bachelor::k))
                                         .c_str(),
                                     "", 1.4248e-01),
      pdfBu_misId_PartRec_(
          ("pdfBu_misId_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          misId_PartRec_meanBu_, misId_PartRec_sigmaLBu_,
          misId_PartRec_sigmaRBu_, misId_PartRec_aLBu_,
          misId_PartRec_aRBu_),
      orEffMisId_PartRec_(("orEffMisId_PartRec_" +
                                      ComposeName(uniqueId, Neutral::gamma,
                                                  Bachelor::k))
                                         .c_str(),
                                     "", 1),
      boxEffMisId_PartRec_(("boxEffMisId_PartRec_" +
                                       ComposeName(uniqueId, Neutral::gamma,
                                                   Bachelor::k))
                                          .c_str(),
                                      "", 1),
      buDeltaCutEffMisId_PartRec_(
          ("buDeltaCutEffMisId_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 1),
      deltaCutEffMisId_PartRec_(
          ("deltaCutEffMisId_PartRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", 1) {
  SetMisIdEfficiencies(Mode::Bu2Dst0pi_D0gamma, orEffMisId_Bu2Dst0h_D0gamma_,
                       boxEffMisId_Bu2Dst0h_D0gamma_,
                       buDeltaCutEffMisId_Bu2Dst0h_D0gamma_,
                       deltaCutEffMisId_Bu2Dst0h_D0gamma_);
  SetMisIdEfficiencies(Mode::Bu2Dst0pi_D0pi0, orEffMisId_Bu2Dst0h_D0pi0_,
                       boxEffMisId_Bu2Dst0h_D0pi0_,
                       buDeltaCutEffMisId_Bu2Dst0h_D0pi0_,
                       deltaCutEffMisId_Bu2Dst0h_D0pi0_);

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

  for (auto &m : misRecModesMap) {
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
        ("deltaCutEffMisIdTemp" + ComposeName(uniqueId, Neutral::gamma))
            .c_str(),
        "", 1);

    SetMisIdEfficiencies(m.first, orEffMisIdTemp, boxEffMisIdTemp,
                         buDeltaCutEffMisIdTemp, deltaCutEffMisIdTemp);

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

  SetMisIdEfficiencies(Mode::Bu2D0pi, orEffMisId_Bu2D0h_, boxEffMisId_Bu2D0h_,
                       buDeltaCutEffMisId_Bu2D0h_, deltaCutEffMisId_Bu2D0h_);

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

  for (auto &m : partRecModesMap) {
    RooRealVar orEffMisIdPartRecTemp(
        ("orEffMisIdPartRecTemp" + ComposeName(uniqueId, Neutral::gamma))
            .c_str(),
        "", 1);
    RooRealVar boxEffMisIdPartRecTemp(
        ("boxEffMisIdPartRecTemp" + ComposeName(uniqueId, Neutral::gamma))
            .c_str(),
        "", 1);
    RooRealVar buDeltaCutEffMisIdPartRecTemp(
        ("buDeltaCutEffMisIdPartRecTemp" +
         ComposeName(uniqueId, Neutral::gamma))
            .c_str(),
        "", 1);
    RooRealVar deltaCutEffMisIdPartRecTemp(
        ("deltaCutEffMisIdPartRecTemp" + ComposeName(uniqueId, Neutral::gamma))
            .c_str(),
        "", 1);

    SetMisIdEfficiencies(m.first, orEffMisIdPartRecTemp, boxEffMisIdPartRecTemp,
                         buDeltaCutEffMisIdPartRecTemp,
                         deltaCutEffMisIdPartRecTemp);

    orEffMisId_PartRecVal += orEffMisIdPartRecTemp.getVal() * m.second;
    boxEffMisId_PartRecVal += boxEffMisIdPartRecTemp.getVal() * m.second;
    buDeltaCutEffMisId_PartRecVal +=
        buDeltaCutEffMisIdPartRecTemp.getVal() * m.second;
    deltaCutEffMisId_PartRecVal +=
        deltaCutEffMisIdPartRecTemp.getVal() * m.second;
  }
  boxEffMisId_PartRec_.setVal(boxEffMisId_PartRecVal);
  buDeltaCutEffMisId_PartRec_.setVal(buDeltaCutEffMisId_PartRecVal);
  deltaCutEffMisId_PartRec_.setVal(deltaCutEffMisId_PartRecVal);
  if (Configuration::Get().fit1D() == false) {
    orEffMisId_PartRec_.setVal(orEffMisId_PartRecVal);
  } else {
    orEffMisId_PartRec_.setVal(deltaCutEffMisId_PartRecVal);
  }
  // std::cout << "\t orEffMisId_PartRec = " << orEffMisId_PartRec_.getVal() <<
  // "\n"
  //           << "\t boxEffMisId_PartRec = " << boxEffMisId_PartRec_.getVal()
  //           << "\n"
  //           << "\t buDeltaCutEffMisId_PartRec = "
  //           << buDeltaCutEffMisId_PartRec_.getVal() << "\n"
  //           << "\t deltaCutEffMisId_PartRec = "
  //           << deltaCutEffMisId_PartRec_.getVal() << "\n";


  if (Configuration::Get().fit1D() == false) {
    N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<Neutral::gamma>::Get(uniqueId)
                .deltaCutEffBu2Dst0h_D0gamma(),
            NeutralVars<Neutral::gamma>::Get(uniqueId).orEffBu2Dst0h_D0gamma(),
            N_Bu2Dst0h_D0gamma_)));
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<Neutral::gamma>::Get(uniqueId)
                .deltaCutEffBu2Dst0h_D0pi0(),
            NeutralVars<Neutral::gamma>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
            N_Bu2Dst0h_D0pi0_)));
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_MisRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<Neutral::gamma>::Get(uniqueId).deltaCutEffMisRec(),
            NeutralVars<Neutral::gamma>::Get(uniqueId).orEffMisRec(),
            N_MisRec_)));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2D0h_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<Neutral::gamma>::Get(uniqueId).deltaCutEffBu2D0h(),
            NeutralVars<Neutral::gamma>::Get(uniqueId).orEffBu2D0h(),
            N_Bu2D0h_)));
    N_Bu_PartRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_PartRec_" +
         ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
            .c_str(),
        "(@0/@1)*@2", RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                     .deltaCutEffPartRec(),
                                 NeutralVars<Neutral::gamma>::Get(uniqueId)
                                     .orEffPartRec(),
                                 N_PartRec_)));
  } else {
    N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
            .c_str(),
        "@0*@1",
        RooArgList(N_tot_Bu2Dst0h_D0gamma_, pidEff_Bu2Dst0h_D0gamma_)));
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
            .c_str(),
        "@0*@1", RooArgList(N_tot_Bu2Dst0h_D0pi0_, pidEff_Bu2Dst0h_D0pi0_)));
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_MisRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
            .c_str(),
        "@0", RooArgList(N_tot_MisRec_)));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2D0h_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
            .c_str(),
        "@0", RooArgList(N_tot_Bu2D0h_)));
    N_Bu_PartRec_ = std::unique_ptr<RooFormulaVar>(
        new RooFormulaVar(("N_Bu_PartRec_" +
                           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                              .c_str(),
                          "@0", RooArgList(N_tot_PartRec_)));
  }
}
