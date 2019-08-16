#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : Bu2Dst0h_Dst02D0gamma_sigmaBu_(
          new RooRealVar(("Bu2Dst0h_Dst02D0gamma_sigmaBu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         "", 2.0051e+01, 15, 30)),
      pdf1Bu_Bu2Dst0h_Dst02D0gamma_(
          ("pdf1Bu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_meanBu(),
          *Bu2Dst0h_Dst02D0gamma_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0gamma_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_n1Bu()),
      pdf2Bu_Bu2Dst0h_Dst02D0gamma_(
          ("pdf2Bu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_meanBu(),
          *Bu2Dst0h_Dst02D0gamma_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0gamma_a2Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_n2Bu()),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(("pdfBu_Bu2Dst0h_Dst02D0gamma_" +
                                    ComposeName(uniqueId, Neutral::pi0,
                                                Bachelor::pi))
                                       .c_str(),
                                   "", RooArgSet(pdf1Bu_Bu2Dst0h_Dst02D0gamma_,
                                                 pdf2Bu_Bu2Dst0h_Dst02D0gamma_),
                                   NeutralVars<Neutral::pi0>::Get(uniqueId)
                                       .Bu2Dst0h_Dst02D0gamma_frac1PdfBu()),
      N_Bu2Dst0h_Dst02D0gamma_(new RooRealVar(
          ("N_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", NeutralVars<Neutral::pi0>::Get(uniqueId).initYieldFAVSignal() *
                  NeutralVars<Neutral::pi0>::Get(uniqueId)
                      .orEffBu2Dst0pi_Dst02D0gamma()
                      .getVal(),
          -1000000, 1000000)),
      N_Delta_Bu2Dst0h_Dst02D0gamma_(
          ("N_Delta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "(@0/@1)*@2", RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                       .buDeltaCutEffBu2Dst0pi_Dst02D0gamma(),
                                   NeutralVars<Neutral::pi0>::Get(uniqueId)
                                       .orEffBu2Dst0pi_Dst02D0gamma(),
                                   *N_Bu2Dst0h_Dst02D0gamma_)),
      N_BuDelta_Bu2Dst0h_Dst02D0gamma_(
          ("N_BuDelta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "(@0/@1)*@2", RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                       .deltaCutEffBu2Dst0pi_Dst02D0gamma(),
                                   NeutralVars<Neutral::pi0>::Get(uniqueId)
                                       .orEffBu2Dst0pi_Dst02D0gamma(),
                                   *N_Bu2Dst0h_Dst02D0gamma_)) {}
