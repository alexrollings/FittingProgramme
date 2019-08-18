#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : Bu2Dst0h_Dst02D0gamma_sigmaBu_(
          new RooRealVar(("Bu2Dst0h_Dst02D0gamma_sigmaBu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         "", 2.0051e+01, 15, 30)),
      pdf1Bu_Bu2Dst0h_Dst02D0gamma_(("pdf1Bu_Bu2Dst0h_Dst02D0gamma_" +
                                     ComposeName(uniqueId, Neutral::gamma,
                                                 Bachelor::pi))
                                        .c_str(),
                                    "", Configuration::Get().buDeltaMass(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0gamma_meanBu(),
                                    *Bu2Dst0h_Dst02D0gamma_sigmaBu_,
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0gamma_a1Bu(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0gamma_n1Bu()),
      pdf2Bu_Bu2Dst0h_Dst02D0gamma_(("pdf2Bu_Bu2Dst0h_Dst02D0gamma_" +
                                     ComposeName(uniqueId, Neutral::gamma,
                                                 Bachelor::pi))
                                        .c_str(),
                                    "", Configuration::Get().buDeltaMass(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0gamma_meanBu(),
                                    *Bu2Dst0h_Dst02D0gamma_sigmaBu_,
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0gamma_a2Bu(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0gamma_n2Bu()),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(("pdfBu_Bu2Dst0h_Dst02D0gamma_" +
                                    ComposeName(uniqueId, Neutral::gamma,
                                                Bachelor::pi))
                                       .c_str(),
                                   "", RooArgSet(pdf1Bu_Bu2Dst0h_Dst02D0gamma_,
                                                 pdf2Bu_Bu2Dst0h_Dst02D0gamma_),
                                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .Bu2Dst0h_Dst02D0gamma_frac1PdfBu()),
      N_Bu2Dst0h_Dst02D0gamma_(new RooRealVar(
          ("N_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", NeutralVars<Neutral::gamma>::Get(uniqueId).initYieldFAVSignal() *
                  NeutralVars<Neutral::gamma>::Get(uniqueId)
                      .orEffBu2Dst0pi_Dst02D0gamma()
                      .getVal(),
          -1000000, 1000000)),
      N_Delta_Bu2Dst0h_Dst02D0gamma_(
          ("N_Delta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "(@0/@1)*@2", RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .buDeltaCutEffBu2Dst0pi_Dst02D0gamma(),
                                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .orEffBu2Dst0pi_Dst02D0gamma(),
                                   *N_Bu2Dst0h_Dst02D0gamma_)),
      N_BuDelta_Bu2Dst0h_Dst02D0gamma_(
          ("N_BuDelta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "(@0/@1)*@2", RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .deltaCutEffBu2Dst0pi_Dst02D0gamma(),
                                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .orEffBu2Dst0pi_Dst02D0gamma(),
                                   *N_Bu2Dst0h_Dst02D0gamma_)),
      MisRec_sigmaBu_(("MisRec_sigmaBu_" +
                       ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                          .c_str(),
                      "", 9.4812e+01),
      pdfBu_MisRec_(("pdfBu_MisRec_" +
                     ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_meanBu(),
                    MisRec_sigmaBu_,
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_aBu(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).MisRec_nBu()),
      N_MisRec_(new RooRealVar(
          ("N_MisRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "", NeutralVars<Neutral::gamma>::Get(uniqueId).initYieldFAVMisRec() *
                  NeutralVars<Neutral::gamma>::Get(uniqueId)
                      .orEffBu2Dst0pi_Dst02D0gamma()
                      .getVal(),
          -1000000, 1000000)),
      N_Delta_MisRec_(
          ("N_Delta_MisRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "(@0/@1)*@2", RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .buDeltaCutEffBu2Dst0pi_Dst02D0gamma(),
                                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .orEffBu2Dst0pi_Dst02D0gamma(),
                                   *N_MisRec_)),
      N_BuDelta_MisRec_(
          ("N_BuDelta_MisRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          "(@0/@1)*@2", RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .deltaCutEffBu2Dst0pi_Dst02D0gamma(),
                                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                                       .orEffBu2Dst0pi_Dst02D0gamma(),
                                   *N_MisRec_)) {}
