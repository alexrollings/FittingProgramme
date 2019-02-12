#include "NeutralDaughtersVars.h"
#include "Configuration.h"
#include "DaughtersVars.h"
#include "NeutralVars.h"

template <Neutral neutral, Daughters daughters>
RooRealVar *Make_ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma(int unqueId) {
  return new RooRealVar(("ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_" +
                         ComposeName(neutral, daughters, uniqueId))
                            .c_str(),
                        "", 0.078, 0.05, 0.1);
}

RooRealVar *Make_ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0(int unqueId) {
  return new RooRealVar(("ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_" +
                         ComposeName(neutral, daughters, uniqueId))
                            .c_str(),
                        "", 0.078, 0.05, 0.1);
}

template <Neutral neutral, Daughters daughters>
RooRealVar *Make_ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0(int unqueId) {
  return new RooRealVar(("ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_" +
                         ComposeName(neutral, daughters, uniqueId))
                            .c_str(),
                        "", 0.078, 0.05, 0.1);
}

template <Neutral neutral, Daughters daughters>
RooRealVar *Make_ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma(int unqueId) {
  return new RooRealVar(("ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_" +
                         ComposeName(neutral, daughters, uniqueId))
                            .c_str(),
                        "", 0.078, 0.05, 0.1);
}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_Dst02D0gamma_(),
      R_CP_Bu2Dst0h_Dst02D0pi0_(),
      R_CP_Bu2Dst0hst_Dst02D0gamma_(),
      R_CP_Bu2Dst0hst_Dst02D0pi0_(),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_(
          Make_ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma<Neutral::pi0,
                                                      Daughters::kpi>(
              uniqueId)),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_(
          Make_ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0<Neutral::pi0,
                                                    Daughters::kpi>(uniqueId)),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_(
          Make_ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0<Neutral::pi0,
                                                      Daughters::kpi>(
              uniqueId)),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_(
          Make_ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma<Neutral::pi0,
                                                        Daughters::kpi>(
              uniqueId)) {}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_Dst02D0gamma_(
          ("R_CP_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(Neutral::pi0, Daughters::kk, uniqueId))
              .c_str(),
          "", 1, 0.5, 1.5),
      R_CP_Bu2Dst0h_Dst02D0pi0_(
          ("R_CP_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(Neutral::pi0, Daughters::kk, uniqueId))
              .c_str(),
          "", 1, 0.5, 1.5),
      R_CP_Bu2Dst0hst_Dst02D0gamma_(
          ("R_CP_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(Neutral::pi0, Daughters::kk, uniqueId))
              .c_str(),
          "", 1, 0.5, 1.5),
      R_CP_Bu2Dst0hst_Dst02D0pi0_(
          ("R_CP_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(Neutral::pi0, Daughters::kk, uniqueId))
              .c_str(),
          "", 1, 0.5, 1.5),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(Neutral::pi0, Daughters::kk, uniqueId))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get()
                         .ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma(),
                     R_CP_Bu2Dst0h_Dst02D0gamma_))),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(Neutral::pi0, Daughters::kk, uniqueId))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get()
                         .ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0(),
                     R_CP_Bu2Dst0h_Dst02D0pi0_))),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_(new RooFormulaVar(
          ("ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(Neutral::pi0, Daughters::kk, uniqueId))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get()
                         .ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma(),
                     R_CP_Bu2Dst0hst_Dst02D0gamma_))),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_(new RooFormulaVar(
          ("ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(Neutral::pi0, Daughters::kk, uniqueId))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get()
                         .ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0(),
                     R_CP_Bu2Dst0hst_Dst02D0pi0_))) {}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_Dst02D0gamma_(
          ("R_CP_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(Neutral::pi0, Daughters::pipi, uniqueId))
              .c_str(),
          "", 1, 0.5, 1.5),
      R_CP_Bu2Dst0h_Dst02D0pi0_(
          ("R_CP_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(Neutral::pi0, Daughters::pipi, uniqueId))
              .c_str(),
          "", 1, 0.5, 1.5),
      R_CP_Bu2Dst0hst_Dst02D0gamma_(
          ("R_CP_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(Neutral::pi0, Daughters::pipi, uniqueId))
              .c_str(),
          "", 1, 0.5, 1.5),
      R_CP_Bu2Dst0hst_Dst02D0pi0_(
          ("R_CP_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(Neutral::pi0, Daughters::pipi, uniqueId))
              .c_str(),
          "", 1, 0.5, 1.5),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(Neutral::pi0, Daughters::pipi, uniqueId))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get()
                         .ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma(),
                     R_CP_Bu2Dst0h_Dst02D0gamma_))),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(Neutral::pi0, Daughters::pipi, uniqueId))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get()
                         .ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0(),
                     R_CP_Bu2Dst0h_Dst02D0pi0_))),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_(new RooFormulaVar(
          ("ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(Neutral::pi0, Daughters::pipi, uniqueId))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get()
                         .ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma(),
                     R_CP_Bu2Dst0hst_Dst02D0gamma_))),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_(new RooFormulaVar(
          ("ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(Neutral::pi0, Daughters::pipi, uniqueId))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get()
                         .ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0(),
                     R_CP_Bu2Dst0hst_Dst02D0pi0_))) {}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_Dst02D0gamma_(),
      R_CP_Bu2Dst0h_Dst02D0pi0_(),
      R_CP_Bu2Dst0hst_Dst02D0gamma_(),
      R_CP_Bu2Dst0hst_Dst02D0pi0_(),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_(
          Make_ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma<Neutral::pi0,
                                                      Daughters::pik>(
              uniqueId)),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_(
          Make_ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0<Neutral::pi0,
                                                    Daughters::pik>(uniqueId)),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_(
          Make_ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0<Neutral::pi0,
                                                      Daughters::pik>(
              uniqueId)),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_(
          Make_ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma<Neutral::pi0,
                                                        Daughters::pik>(
              uniqueId)) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_Dst02D0gamma_(),
      R_CP_Bu2Dst0h_Dst02D0pi0_(),
      R_CP_Bu2Dst0hst_Dst02D0gamma_(),
      R_CP_Bu2Dst0hst_Dst02D0pi0_(),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_(
          Make_ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma<Neutral::gamma,
                                                      Daughters::kpi>(
              uniqueId)),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_(
          Make_ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0<Neutral::gamma,
                                                    Daughters::kpi>(uniqueId)),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_(
          Make_ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0<Neutral::gamma,
                                                      Daughters::kpi>(
              uniqueId)),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_(
          Make_ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma<Neutral::gamma,
                                                        Daughters::kpi>(
              uniqueId)) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_Dst02D0gamma_(
          ("R_CP_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(Neutral::gamma, Daughters::kk, uniqueId))
              .c_str(),
          "", 1, 0.5, 1.5),
      R_CP_Bu2Dst0h_Dst02D0pi0_(
          ("R_CP_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(Neutral::gamma, Daughters::kk, uniqueId))
              .c_str(),
          "", 1, 0.5, 1.5),
      R_CP_Bu2Dst0hst_Dst02D0gamma_(
          ("R_CP_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(Neutral::gamma, Daughters::kk, uniqueId))
              .c_str(),
          "", 1, 0.5, 1.5),
      R_CP_Bu2Dst0hst_Dst02D0pi0_(
          ("R_CP_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(Neutral::gamma, Daughters::kk, uniqueId))
              .c_str(),
          "", 1, 0.5, 1.5),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(Neutral::gamma, Daughters::kk, uniqueId))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get()
                         .ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma(),
                     R_CP_Bu2Dst0h_Dst02D0gamma_))),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(Neutral::gamma, Daughters::kk, uniqueId))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get()
                         .ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0(),
                     R_CP_Bu2Dst0h_Dst02D0pi0_))),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_(new RooFormulaVar(
          ("ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(Neutral::gamma, Daughters::kk, uniqueId))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get()
                         .ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma(),
                     R_CP_Bu2Dst0hst_Dst02D0gamma_))),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_(new RooFormulaVar(
          ("ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(Neutral::gamma, Daughters::kk, uniqueId))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get()
                         .ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0(),
                     R_CP_Bu2Dst0hst_Dst02D0pi0_))) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_Dst02D0gamma_(
          ("R_CP_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(Neutral::gamma, Daughters::pipi, uniqueId))
              .c_str(),
          "", 1, 0.5, 1.5),
      R_CP_Bu2Dst0h_Dst02D0pi0_(
          ("R_CP_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(Neutral::gamma, Daughters::pipi, uniqueId))
              .c_str(),
          "", 1, 0.5, 1.5),
      R_CP_Bu2Dst0hst_Dst02D0gamma_(
          ("R_CP_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(Neutral::gamma, Daughters::pipi, uniqueId))
              .c_str(),
          "", 1, 0.5, 1.5),
      R_CP_Bu2Dst0hst_Dst02D0pi0_(
          ("R_CP_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(Neutral::gamma, Daughters::pipi, uniqueId))
              .c_str(),
          "", 1, 0.5, 1.5),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(Neutral::gamma, Daughters::pipi, uniqueId))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get()
                         .ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma(),
                     R_CP_Bu2Dst0h_Dst02D0gamma_))),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(Neutral::gamma, Daughters::pipi, uniqueId))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get()
                         .ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0(),
                     R_CP_Bu2Dst0h_Dst02D0pi0_))),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_(new RooFormulaVar(
          ("ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(Neutral::gamma, Daughters::pipi, uniqueId))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get()
                         .ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma(),
                     R_CP_Bu2Dst0hst_Dst02D0gamma_))),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_(new RooFormulaVar(
          ("ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(Neutral::gamma, Daughters::pipi, uniqueId))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get()
                         .ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0(),
                     R_CP_Bu2Dst0hst_Dst02D0pi0_))) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_Dst02D0gamma_(),
      R_CP_Bu2Dst0h_Dst02D0pi0_(),
      R_CP_Bu2Dst0hst_Dst02D0gamma_(),
      R_CP_Bu2Dst0hst_Dst02D0pi0_(),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_(
          Make_ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma<Neutral::gamma,
                                                      Daughters::pik>(
              uniqueId)),
      ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_(
          Make_ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0<Neutral::gamma,
                                                    Daughters::pik>(uniqueId)),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_(
          Make_ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0<Neutral::gamma,
                                                      Daughters::pik>(
              uniqueId)),
      ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_(
          Make_ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma<Neutral::gamma,
                                                        Daughters::pik>(
              uniqueId)) {}
