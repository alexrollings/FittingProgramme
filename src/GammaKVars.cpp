#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- Bu2Dst0h_D0gamma -------------------- //
    : Bu2Dst0h_D0gamma_sigmaBu_(new RooFormulaVar(
          ("Bu2Dst0h_D0gamma_sigmaBu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_D0gamma_sigmaBu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_D0gamma()))),
      pdf1Bu_Bu2Dst0h_D0gamma_(
          ("pdf1Bu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_meanBu(),
          *Bu2Dst0h_D0gamma_sigmaBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0gamma_(
          ("pdf2Bu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_meanBu(),
          *Bu2Dst0h_D0gamma_sigmaBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0gamma_n2Bu()),
      pdfBu_Bu2Dst0h_D0gamma_(
          ("pdfBu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0h_D0gamma_, pdf2Bu_Bu2Dst0h_D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_D0gamma_frac1PdfBu()),
      N_Bu2Dst0h_D0gamma_(new RooFormulaVar(
          ("N_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1*@2",
          RooArgSet(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .N_Bu2Dst0h_D0gamma(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .ratioKpi_Bu2Dst0h_D0gamma(),
              Configuration::Get().pidEff()))),
      N_Delta_Bu2Dst0h_D0gamma_(
          ("N_Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "(@0/@1)*@2", RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .buDeltaCutEffBu2Dst0pi_D0gamma(),
                                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .orEffBu2Dst0pi_D0gamma(),
                                   *N_Bu2Dst0h_D0gamma_)),
      N_BuDelta_Bu2Dst0h_D0gamma_(
          ("N_BuDelta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "(@0/@1)*@2", RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .deltaCutEffBu2Dst0pi_D0gamma(),
                                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .orEffBu2Dst0pi_D0gamma(),
                                   *N_Bu2Dst0h_D0gamma_)),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      Bu2Dst0h_D0pi0_sigmaBu_(("Bu2Dst0h_D0pi0_sigmaBu_" +
                               ComposeName(uniqueId, Neutral::gamma,
                                           Bachelor::k))
                                  .c_str(),
                              "", 4.6911e+01),
      pdfBu_Bu2Dst0h_D0pi0_(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_meanBu(),
          Bu2Dst0h_D0pi0_sigmaBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_aBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_D0pi0_nBu()),
      N_Bu2Dst0h_D0pi0_(new RooFormulaVar(
          ("N_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1*@2",
          RooArgSet(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .N_Bu2Dst0h_D0pi0(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .ratioKpi_Bu2Dst0h_D0pi0(),
              Configuration::Get().pidEff()))),
      N_Delta_Bu2Dst0h_D0pi0_(
          ("N_Delta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "(@0/@1)*@2", RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .buDeltaCutEffBu2Dst0pi_D0pi0(),
                                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .orEffBu2Dst0pi_D0pi0(),
                                   *N_Bu2Dst0h_D0pi0_)),
      N_BuDelta_Bu2Dst0h_D0pi0_(
          ("N_BuDelta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "(@0/@1)*@2", RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .deltaCutEffBu2Dst0pi_D0pi0(),
                                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .orEffBu2Dst0pi_D0pi0(),
                                   *N_Bu2Dst0h_D0pi0_)),
      // -------------------- MIS-REC -------------------- //
      MisRec_sigmaBu_(("MisRec_sigmaBu_" +
                       ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                          .c_str(),
                      "", 9.4812e+01),
      pdfBu_MisRec_(("pdfBu_MisRec_" +
                     ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_meanBu(),
                    MisRec_sigmaBu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aBu(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_nBu()),
      N_MisRec_(new RooFormulaVar(
          ("N_MisRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "", "@0*@1*@2",
          RooArgSet(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .N_MisRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).ratioKpi_MisRec(),
              Configuration::Get().pidEff()))),
      N_Delta_MisRec_(("N_Delta_MisRec_" +
                       ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                          .c_str(),
                      "(@0/@1)*@2",
                      RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                     .buDeltaCutEffBu2Dst0pi_D0gamma(),
                                 NeutralVars<Neutral::gamma>::Get(uniqueId)
                                     .orEffBu2Dst0pi_D0gamma(),
                                 *N_MisRec_)),
      N_BuDelta_MisRec_(("N_BuDelta_MisRec_" +
                         ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                            .c_str(),
                        "(@0/@1)*@2",
                        RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .deltaCutEffBu2Dst0pi_D0gamma(),
                                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .orEffBu2Dst0pi_D0gamma(),
                                   *N_MisRec_)) {}
