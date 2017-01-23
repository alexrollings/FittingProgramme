#include "NeutralDaughtersVars.h"
#include "Configuration.h"
#include "DaughtersVars.h"
#include "NeutralVars.h"

// Daughters specializations
// MAKE GENERAL
template <Neutral neutral, Daughters daughters> RooRealVar *Make_R_Dk_vs_Dpi() {
  return new RooRealVar(
      ("R_Dk_vs_Dpi_" + ComposeName(neutral, daughters)).c_str(),
      ("Ratio of yields of Bu2Dst0pi decay channel for K w.r.t. pi bachelor, " +
       ComposeName(neutral, daughters))
          .c_str(),
      0.078, 0.05, 0.1);
}

template <Neutral neutral, Daughters daughters> RooRealVar *Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0() {
  return new RooRealVar(
      ("R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0_" + ComposeName(neutral, daughters)).c_str(),
      ("Ratio of yields of Bu2Dst0Hst_D0pi0 decay channel for K w.r.t. pi bachelor, " +
       ComposeName(neutral, daughters))
          .c_str(),
      0.078, 0.05, 0.1);
}

template <Neutral neutral, Daughters daughters> RooRealVar *Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma() {
  return new RooRealVar(
      ("R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma_" + ComposeName(neutral, daughters)).c_str(),
      ("Ratio of yields of Bu2Dst0Hst_D0gamma decay channel for K w.r.t. pi bachelor, " +
       ComposeName(neutral, daughters))
          .c_str(),
      0.078, 0.05, 0.1);
}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(Make_R_Dk_vs_Dpi<Neutral::pi0, Daughters::kpi>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0<Neutral::pi0, Daughters::kpi>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma<Neutral::pi0, Daughters::kpi>()) {}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::NeutralDaughtersVars()
    : R_cp_("R_cp_kk_Pi0", "R_dk_vs_dpi[kk]/R_dk_vs_dpi[kpi], Pi0", 1, 0.5,
            1.5),
      R_Dk_vs_Dpi_(new RooFormulaVar(
          "R_Dk_vs_Dpi_Pi0_kk",
          "Ratio of yields of Bu2Dst0pi decay channel for K "
          "w.r.t. pi bachelor, for daughters=kk, neutral=pi0",
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get()
                         .R_Dk_vs_Dpi(),
                     R_cp_))),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0<Neutral::pi0, Daughters::kk>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma<Neutral::pi0, Daughters::kk>()) {}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::NeutralDaughtersVars()
    : R_cp_("R_cp_pipi_Pi0", "R_dk_vs_dpi[pipi]/R_dk_vs_dpi[kpi], Pi0", 1, 0.5,
            1.5),
      R_Dk_vs_Dpi_(new RooFormulaVar(
          "R_Dk_vs_Dpi_Pi0_pipi",
          "Ratio of yields of Bu2Dst0pi decay channel for K "
          "w.r.t. pi bachelor, for daughters=pipi, neutral=pi0",
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get()
                         .R_Dk_vs_Dpi(),
                     R_cp_))),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0<Neutral::pi0, Daughters::pipi>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma<Neutral::pi0, Daughters::pipi>()) {}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(Make_R_Dk_vs_Dpi<Neutral::pi0, Daughters::pik>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0<Neutral::pi0, Daughters::pik>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma<Neutral::pi0, Daughters::pik>()) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(Make_R_Dk_vs_Dpi<Neutral::gamma, Daughters::kpi>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0<Neutral::gamma, Daughters::kpi>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma<Neutral::gamma,
                                              Daughters::kpi>()) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::NeutralDaughtersVars()
    : R_cp_("R_cp_kk_Gamma", "R_dk_vs_dpi[kk]/R_dk_vs_dpi[kpi], Gamma", 1, 0.5,
            1.5),
      R_Dk_vs_Dpi_(new RooFormulaVar(
          "R_Dk_vs_Dpi_Gamma_kk",
          "Ratio of yields of Bu2Dst0pi decay channel for K "
          "w.r.t. pi bachelor, for daughters=kk, neutral=gamma",
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get()
                         .R_Dk_vs_Dpi(), R_cp_))),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0<Neutral::gamma, Daughters::kk>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma<Neutral::gamma,
                                              Daughters::kk>()) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::NeutralDaughtersVars()
    : R_cp_("R_cp_pipi_Gamma", "R_dk_vs_dpi[pipi]/R_dk_vs_dpi[kpi], Gamma", 1, 0.5,
            1.5),
      R_Dk_vs_Dpi_(new RooFormulaVar(
          "R_Dk_vs_Dpi_gamma_pipi",
          "Ratio of yields of Bu2Dst0pi decay channel for K "
          "w.r.t. pi bachelor, for daughters=pipi, neutral=gamma",
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get()
                         .R_Dk_vs_Dpi(), R_cp_))),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0<Neutral::gamma, Daughters::pipi>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma<Neutral::gamma,
                                              Daughters::pipi>()) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(Make_R_Dk_vs_Dpi<Neutral::gamma, Daughters::pik>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0<Neutral::gamma, Daughters::pik>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma<Neutral::gamma,
                                              Daughters::pik>()) {}
