#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- Bu2Dst0h_D0pi0 -------------------- //
    : Bu2Dst0h_D0pi0_sigma1Bu_(
          new RooRealVar(("Bu2Dst0h_D0pi0_sigma1Bu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         "", 2.0023e+01, 15, 25)),
      Bu2Dst0h_D0pi0_sigma2Bu_(
          new RooRealVar(("Bu2Dst0h_D0pi0_sigma2Bu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         "", 2.2797e+01)),
      pdfBu_Bu2Dst0h_D0pi0_(new RooCruijff(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigma1Bu_, *Bu2Dst0h_D0pi0_sigma2Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_a2Bu())),
      N_tot_Bu2Dst0h_D0pi0_(("N_tot_Bu2Dst0h_D0pi0_" +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                .c_str(),
                            "", NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .initYieldFAVBu2Dst0h_D0pi0() *
                                    NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .orEffBu2Dst0h_D0pi0()
                                        .getVal(),
                            // -1000000, 1000000),
                            0, 100000),
      pidEff_Bu2Dst0h_D0pi0_(("pidEff_Bu2Dst0h_D0pi0_" +
                              ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                 .c_str(),
                             "", 0.996699),
      N_Bu2Dst0h_D0pi0_(("N_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                            .c_str(),
                        "@0*@1", RooArgList(N_tot_Bu2Dst0h_D0pi0_,
                                            pidEff_Bu2Dst0h_D0pi0_)),
      N_Delta_Bu2Dst0h_D0pi0_(
          ("N_Delta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .buDeltaCutEffBu2Dst0h_D0pi0(),
              NeutralVars<Neutral::pi0>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
              N_Bu2Dst0h_D0pi0_)),
      N_Bu_Bu2Dst0h_D0pi0_(nullptr),
      // -------------------- Bu2Dst0h_D0gamma -------------------- //
      Bu2Dst0h_D0gamma_sigma1Bu_(
          new RooRealVar(("Bu2Dst0h_D0gamma_sigma1Bu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         "", 4.3516e+01)),
      Bu2Dst0h_D0gamma_sigma2Bu_(
          new RooRealVar(("Bu2Dst0h_D0gamma_sigma2Bu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         "", 4.5327e+01)),
      pdf1Bu_Bu2Dst0h_D0gamma_(),
      pdf2Bu_Bu2Dst0h_D0gamma_(),
      pdfBu_Bu2Dst0h_D0gamma_(new RooCruijff(
          ("pdfBu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_meanBu(),
          *Bu2Dst0h_D0gamma_sigma1Bu_, *Bu2Dst0h_D0gamma_sigma2Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_a2Bu())),
      N_tot_Bu2Dst0h_D0gamma_(("N_tot_Bu2Dst0h_D0gamma_" +
                               ComposeName(uniqueId, Neutral::pi0,
                                           Bachelor::pi))
                                  .c_str(),
                              "", NeutralVars<Neutral::pi0>::Get(uniqueId)
                                          .initYieldFAVBu2Dst0h_D0gamma() *
                                      NeutralVars<Neutral::pi0>::Get(uniqueId)
                                          .orEffBu2Dst0h_D0gamma()
                                          .getVal(),
                              // -1000000, 1000000),
                              0, 100000),
      pidEff_Bu2Dst0h_D0gamma_(("pidEff_Bu2Dst0h_D0gamma_" +
                                ComposeName(uniqueId, Neutral::pi0,
                                            Bachelor::pi))
                                   .c_str(),
                               "", 0.993811),
      N_Bu2Dst0h_D0gamma_(("N_Bu2Dst0h_D0gamma_" +
                           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                              .c_str(),
                          "@0*@1", RooArgList(N_tot_Bu2Dst0h_D0gamma_,
                                              pidEff_Bu2Dst0h_D0gamma_)),
      N_Delta_Bu2Dst0h_D0gamma_(
          ("N_Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .buDeltaCutEffBu2Dst0h_D0gamma(),
              NeutralVars<Neutral::pi0>::Get(uniqueId).orEffBu2Dst0h_D0gamma(),
              N_Bu2Dst0h_D0gamma_)),
      N_Bu_Bu2Dst0h_D0gamma_(nullptr),
      // -------------------- MIS-REC -------------------- //
      MisRec_sigma1Bu_(("MisRec_sigma1Bu_" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                           .c_str(),
                       "", 5.3452e+01, 40, 90), //7.8797e+01),
      MisRec_sigma2Bu_(("MisRec_sigma2Bu_" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                           .c_str(),
                       "", 4.8696e+01, 30, 80), //6.4032e+01),
      pdfBu_MisRec_(new RooCruijff(
          ("pdfBu_MisRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_meanBu(),
          MisRec_sigma1Bu_, MisRec_sigma2Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_a2Bu())),
      N_tot_MisRec_(
          ("N_tot_MisRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "",
          NeutralVars<Neutral::pi0>::Get(uniqueId).initYieldFAVMisRec() *
              NeutralVars<Neutral::pi0>::Get(uniqueId).orEffMisRec().getVal(),
          // -1000000, 1000000),
          0, 100000),
      pidEff_Bu2Dst0h_D0gamma_WN_(0.99615),
      pidEff_Bu2Dst0h_D0pi0_WN_(0.996652),
      pidEff_Bu2D0hst_(0.996877),
      pidEff_Bd2Dsth_(0.997507),
      pidEff_MisRec_(
          ("pidEff_MisRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "",
          (pidEff_Bu2Dst0h_D0gamma_WN_ *
               NeutralVars<Neutral::pi0>::Get(uniqueId)
                   .fracMisRec_Bu2Dst0h_D0gamma_WN() +
           pidEff_Bu2Dst0h_D0pi0_WN_ *
               NeutralVars<Neutral::pi0>::Get(uniqueId)
                   .fracMisRec_Bu2Dst0h_D0pi0_WN() +
           pidEff_Bu2D0hst_ *
               NeutralVars<Neutral::pi0>::Get(uniqueId).fracMisRec_Bu2D0hst() +
           pidEff_Bd2Dsth_ *
               NeutralVars<Neutral::pi0>::Get(uniqueId).fracMisRec_Bd2Dsth()) /
              NeutralVars<Neutral::pi0>::Get(uniqueId).fracMisRec()),
      N_MisRec_(("N_MisRec_" +
                 ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                    .c_str(),
                "@0*@1", RooArgList(N_tot_MisRec_, pidEff_MisRec_)),
      N_Delta_MisRec_(
          ("N_Delta_MisRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<Neutral::pi0>::Get(uniqueId).buDeltaCutEffMisRec(),
              NeutralVars<Neutral::pi0>::Get(uniqueId).orEffMisRec(),
              N_MisRec_)),
      N_Bu_MisRec_(nullptr),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_sigmaLBu_(new RooRealVar(("Bu2D0h_sigmaLBu_" +
                                       ComposeName(uniqueId, Neutral::pi0,
                                                   Bachelor::pi))
                                          .c_str(),
                                      "", 3.3137e+01, 10, 50)), //7.0790e+01)),
      Bu2D0h_sigmaRBu_(new RooRealVar(("Bu2D0h_sigmaRBu_" +
                                       ComposeName(uniqueId, Neutral::pi0,
                                                   Bachelor::pi))
                                          .c_str(),
                                      "", 4.0080e+01, 10, 50)), // 7.9369e+01)),
      pdfBu_Bu2D0h_(("pdfBu_Bu2D0h_" +
                     ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0h_meanBu(),
                    *Bu2D0h_sigmaLBu_, *Bu2D0h_sigmaRBu_,
                    NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0h_aLBu(),
                    NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0h_aRBu()),
      N_tot_Bu2D0h_(
          ("N_tot_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "",
          NeutralVars<Neutral::pi0>::Get(uniqueId).initYieldFAVBu2D0h() *
              NeutralVars<Neutral::pi0>::Get(uniqueId).orEffBu2D0h().getVal(),
          // -1000000, 1000000),
          0, 100000),
      pidEff_Bu2D0h_(("pidEff_Bu2D0h_" +
                      ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                         .c_str(),
                     "", 0.994457),
      N_Bu2D0h_(("N_Bu2D0h_" +
                 ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                    .c_str(),
                "@0*@1", RooArgList(N_tot_Bu2D0h_, pidEff_Bu2D0h_)),
      N_Delta_Bu2D0h_(
          ("N_Delta_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<Neutral::pi0>::Get(uniqueId).buDeltaCutEffBu2D0h(),
              NeutralVars<Neutral::pi0>::Get(uniqueId).orEffBu2D0h(),
              N_Bu2D0h_)),
      N_Bu_Bu2D0h_(nullptr) {
  if (Configuration::Get().fit1D() == false) {
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<Neutral::pi0>::Get(uniqueId)
                .deltaCutEffBu2Dst0h_D0pi0(),
            NeutralVars<Neutral::pi0>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
            N_Bu2Dst0h_D0pi0_)));
    N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<Neutral::pi0>::Get(uniqueId)
                .deltaCutEffBu2Dst0h_D0gamma(),
            NeutralVars<Neutral::pi0>::Get(uniqueId).orEffBu2Dst0h_D0gamma(),
            N_Bu2Dst0h_D0gamma_)));
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_MisRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId).deltaCutEffMisRec(),
                   NeutralVars<Neutral::pi0>::Get(uniqueId).orEffMisRec(),
                   N_MisRec_)));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId).deltaCutEffBu2D0h(),
                   NeutralVars<Neutral::pi0>::Get(uniqueId).orEffBu2D0h(),
                   N_Bu2D0h_)));
  } else {
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
            .c_str(),
        "@0*@1", RooArgList(N_tot_Bu2Dst0h_D0pi0_, pidEff_Bu2Dst0h_D0pi0_)));
    N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
            .c_str(),
        "@0*@1",
        RooArgList(N_tot_Bu2Dst0h_D0gamma_, pidEff_Bu2Dst0h_D0gamma_)));
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_MisRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
            .c_str(),
        "@0*@1", RooArgList(N_tot_MisRec_, pidEff_MisRec_)));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
            .c_str(),
        "@0*@1", RooArgList(N_tot_Bu2D0h_, pidEff_Bu2D0h_)));
  }
}
