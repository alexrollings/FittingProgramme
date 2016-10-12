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
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma<Neutral::pi0, Daughters::kpi>()),
      selfCrossFeedRate_(new RooConstVar("selfCrossFeedRate_pi0_kpi",
                                         "Proportion of SCF in N_Dpi, pi0, kpi",
                                         0.31394)),
      crossFeedRate_(new RooConstVar("crossFeedRate_pi0_kpi",
                                     "Proportion of CF in N_Dpi, pi0, kpi",
                                     0.34005)) {}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(new RooFormulaVar(
          "R_Dk_vs_Dpi_Pi0_kk",
          "Ratio of yields of Bu2Dst0pi decay channel for K "
          "w.r.t. pi bachelor, for daughters=kk, neutral=pi0",
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get()
                         .R_Dk_vs_Dpi(),
                     NeutralVars<Neutral::pi0>::Get().R_cp_kk()))),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0<Neutral::pi0, Daughters::kk>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma<Neutral::pi0, Daughters::kk>()),
      selfCrossFeedRate_(new RooRealVar("selfCrossFeedRate_pi0_kk",
                                        "Proportion of SCF in N_Dpi, pi0, kk",
                                        0.3194)),
      crossFeedRate_(new RooRealVar("crossFeedRate_pi0_kk",
                                    "Proportion of CF in N_Dpi, pi0, kk",
                                    0.34005)) {}
template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(new RooFormulaVar(
          "R_Dk_vs_Dpi_Pi0_pipi",
          "Ratio of yields of Bu2Dst0pi decay channel for K "
          "w.r.t. pi bachelor, for daughters=pipi, neutral=pi0",
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get()
                         .R_Dk_vs_Dpi(),
                     NeutralVars<Neutral::pi0>::Get().R_cp_pipi()))),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0<Neutral::pi0, Daughters::pipi>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma<Neutral::pi0, Daughters::pipi>()),
      selfCrossFeedRate_(new RooRealVar("selfCrossFeedRate_pi0_pipi",
                                        "Proportion of SCF in N_Dpi, pi0, pipi",
                                        0.3194)),
      crossFeedRate_(new RooRealVar("crossFeedRate_pi0_pipi",
                                    "Proportion of CF in N_Dpi, pi0, pipi",
                                    0.34005)) {}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(Make_R_Dk_vs_Dpi<Neutral::pi0, Daughters::pik>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0<Neutral::pi0, Daughters::pik>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma<Neutral::pi0, Daughters::pik>()),
      selfCrossFeedRate_(new RooRealVar("selfCrossFeedRate_pi0_pik",
                                        "Proportion of SCF in N_Dpi, pi0, pik",
                                        0.3194)),
      crossFeedRate_(new RooRealVar("crossFeedRate_pi0_pik",
                                    "Proportion of CF in N_Dpi, pi0, pik",
                                    0.34005)) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(Make_R_Dk_vs_Dpi<Neutral::gamma, Daughters::kpi>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0<Neutral::gamma, Daughters::kpi>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma<Neutral::gamma,
                                              Daughters::kpi>()),
      selfCrossFeedRate_(
          new RooConstVar("selfCrossFeedRate_gamma_kpi",
                          "Proportion of SCF in N_Dpi, gamma, kpi", 0.26424)),
      crossFeedRate_(new RooConstVar("crossFeedRate_gamma_kpi",
                                     "Proportion of CF in N_Dpi, gamma, kpi",
                                     0.10187)) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(new RooFormulaVar(
          "R_Dk_vs_Dpi_Gamma_kk",
          "Ratio of yields of Bu2Dst0pi decay channel for K "
          "w.r.t. pi bachelor, for daughters=kk, neutral=gamma",
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get()
                         .R_Dk_vs_Dpi(),
                     NeutralVars<Neutral::gamma>::Get().R_cp_kk()))),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0<Neutral::gamma, Daughters::kk>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma<Neutral::gamma,
                                              Daughters::kk>()),
      selfCrossFeedRate_(new RooRealVar("selfCrossFeedRate_gamma_kk",
                                        "Proportion of SCF in N_Dpi, gamma, kk",
                                        0.26424)),
      crossFeedRate_(new RooRealVar("crossFeedRate_gamma_kk",
                                    "Proportion of CF in N_Dpi, gamma, kk",
                                    0.10187)) {}
template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(new RooFormulaVar(
          "R_Dk_vs_Dpi_gamma_pipi",
          "Ratio of yields of Bu2Dst0pi decay channel for K "
          "w.r.t. pi bachelor, for daughters=pipi, neutral=gamma",
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get()
                         .R_Dk_vs_Dpi(),
                     NeutralVars<Neutral::gamma>::Get().R_cp_pipi()))),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0<Neutral::gamma, Daughters::pipi>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma<Neutral::gamma,
                                              Daughters::pipi>()),
      selfCrossFeedRate_(new RooRealVar(
          "selfCrossFeedRate_gamma_pipi",
          "Proportion of SCF in N_Dpi, gamma, pipi", 0.26424)), 
      crossFeedRate_(new RooRealVar("crossFeedRate_gamma_pipi",
                                    "Proportion of CF in N_Dpi, gamma, pipi",
                                   0.10187)) {} 

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(Make_R_Dk_vs_Dpi<Neutral::gamma, Daughters::pik>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0<Neutral::gamma, Daughters::pik>()),
      R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma_(
          Make_R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma<Neutral::gamma,
                                              Daughters::pik>()),
      selfCrossFeedRate_(new RooRealVar(
          "selfCrossFeedRate_gamma_pik",
          "Proportion of SCF in N_Dpi, gamma, pik", 0.26424)), 
      crossFeedRate_(new RooRealVar("crossFeedRate_gamma_pik",
                                    "Proportion of CF in N_Dpi, gamma, pik",
                                   0.10187)) {} 
