#include "NeutralDaughtersVars.h"
#include "Configuration.h"
#include "DaughtersVars.h"
#include "GlobalVars.h"
#include "NeutralVars.h"

// template <Neutral neutral, Daughters daughters>
// RooRealVar *Make_R_Dst0KDst0pi_Bu2Dst0h_D0gamma(int uniqueId) {
//   return new RooRealVar(("R_Dst0KDst0pi_Bu2Dst0h_D0gamma_" +
//                          ComposeName(uniqueId, neutral, daughters))
//                             .c_str(),
//                         "", 0.07930, -1, 1);
// }

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_D0gamma_(),
      R_CP_Bu2Dst0h_D0pi0_(),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(new RooRealVar(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Daughters::kpi))
              .c_str(),
          "", 0.07930, -1, 1)) {}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_D0gamma_(
          ("R_CP_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Daughters::kk))
              .c_str(),
          "", 1, -5, 5),
      R_CP_Bu2Dst0h_D0pi0_(
          ("R_CP_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Daughters::kk))
              .c_str(),
          "", 1, -5, 5),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Daughters::kk))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get(uniqueId)
                  .R_Dst0KDst0pi_Bu2Dst0h_D0pi0(),
              R_CP_Bu2Dst0h_D0pi0_))) {}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_D0gamma_(
          ("R_CP_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Daughters::pipi))
              .c_str(),
          "", 1, -5, 5),
      R_CP_Bu2Dst0h_D0pi0_(
          ("R_CP_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Daughters::pipi))
              .c_str(),
          "", 1, -5, 5),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Daughters::pipi))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get(uniqueId)
                  .R_Dst0KDst0pi_Bu2Dst0h_D0pi0(),
              R_CP_Bu2Dst0h_D0pi0_))) {}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_D0gamma_(),
      R_CP_Bu2Dst0h_D0pi0_(),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_D0gamma_(),
      R_CP_Bu2Dst0h_D0pi0_(),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(new RooRealVar(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Daughters::kpi))
              .c_str(),
          "", 0.07930, -1, 1)),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(new RooRealVar(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Daughters::kpi))
              .c_str(),
          "", 0.07930, -1, 1)) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_D0gamma_(
          ("R_CP_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Daughters::kk))
              .c_str(),
          "", 1, -5, 5),
      R_CP_Bu2Dst0h_D0pi0_(
          ("R_CP_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Daughters::kk))
              .c_str(),
          "", 1, -5, 5),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Daughters::kk))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(
                         uniqueId)
                         .R_Dst0KDst0pi_Bu2Dst0h_D0gamma(),
                     R_CP_Bu2Dst0h_D0gamma_))),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Daughters::kk))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(
                         uniqueId)
                         .R_Dst0KDst0pi_Bu2Dst0h_D0pi0(),
                     R_CP_Bu2Dst0h_D0pi0_))) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_D0gamma_(
          ("R_CP_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Daughters::pipi))
              .c_str(),
          "", 1, -5, 5),
      R_CP_Bu2Dst0h_D0pi0_(
          ("R_CP_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Daughters::pipi))
              .c_str(),
          "", 1, -5, 5),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Daughters::pipi))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(
                         uniqueId)
                         .R_Dst0KDst0pi_Bu2Dst0h_D0gamma(),
                     R_CP_Bu2Dst0h_D0gamma_))),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Daughters::pipi))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(
                         uniqueId)
                         .R_Dst0KDst0pi_Bu2Dst0h_D0pi0(),
                     R_CP_Bu2Dst0h_D0pi0_))) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_D0gamma_(),
      R_CP_Bu2Dst0h_D0pi0_(),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr) {}
