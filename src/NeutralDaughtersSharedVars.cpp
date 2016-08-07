#include "NeutralDaughtersSharedVars.h"
#include "Configuration.h"
#include "NeutralVars.h"
#include "DaughtersVars.h"

// Daughters specializations

template <>
NeutralDaughtersSharedVars<Neutral::pi0,
                           Daughters::kpi>::NeutralDaughtersSharedVars()
    : R_Dk_vs_Dpi_(
          new RooRealVar("R_Dk_vs_Dpi_Pi0_kpi",
                         "Ratio of yields of Bu2Dst0pi decay channel for K "
                         "w.r.t. pi bachelor, for daughters=kpi, neutral=pi0",
                         0.075, 0.02, 0.1)) {}
template <>
NeutralDaughtersSharedVars<Neutral::pi0,
                           Daughters::kk>::NeutralDaughtersSharedVars()
    : R_Dk_vs_Dpi_(new RooFormulaVar(
          "R_Dk_vs_Dpi_Pi0_kk",
          "Ratio of yields of Bu2Dst0pi decay channel for K "
          "w.r.t. pi bachelor, for daughters=kk, neutral=pi0",
          "@0*@1",
          RooArgList(
              NeutralDaughtersSharedVars<Neutral::pi0, Daughters::kpi>::Get()
                  .R_Dk_vs_Dpi(),
              NeutralVars<Neutral::pi0>::Get().R_cp()))) {}
template <>
NeutralDaughtersSharedVars<Neutral::pi0,
                           Daughters::pipi>::NeutralDaughtersSharedVars()
    : R_Dk_vs_Dpi_(new RooRealVar("R_Dk_vs_Dpi_Pi0_pipi",
                   "Ratio of yields of Bu2Dst0pi decay channel for K "
                   "w.r.t. pi bachelor, for daughters=pipi, neutral=pi0",
                   0.075, 0.02, 0.1)) {}
template <>
NeutralDaughtersSharedVars<Neutral::pi0,
                           Daughters::pik>::NeutralDaughtersSharedVars()
    : R_Dk_vs_Dpi_(new RooRealVar("R_Dk_vs_Dpi_Pi0_pik",
                   "Ratio of yields of Bu2Dst0pi decay channel for K "
                   "w.r.t. pi bachelor, for daughters=pik, neutral=pi0",
                   0.075, 0.02, 0.1)) {}

template <>
NeutralDaughtersSharedVars<Neutral::gamma,
                           Daughters::kpi>::NeutralDaughtersSharedVars()
    : R_Dk_vs_Dpi_(new RooRealVar("R_Dk_vs_Dpi_Gamma_kpi",
                   "Ratio of yields of Bu2Dst0pi decay channel for K "
                   "w.r.t. pi bachelor, for daughters=kpi, neutral=gamma",
                   0.075, 0.02, 0.1)) {}

template <>
NeutralDaughtersSharedVars<Neutral::gamma,
                           Daughters::kk>::NeutralDaughtersSharedVars()
    : R_Dk_vs_Dpi_(new RooFormulaVar("R_Dk_vs_Dpi_Gamma_kk",
                   "Ratio of yields of Bu2Dst0pi decay channel for K "
                   "w.r.t. pi bachelor, for daughters=kk, neutral=gamma",
          "@0*@1",
          RooArgList(
              NeutralDaughtersSharedVars<Neutral::gamma, Daughters::kpi>::Get()
                  .R_Dk_vs_Dpi(),
              NeutralVars<Neutral::gamma>::Get().R_cp()))) {}
template <>
NeutralDaughtersSharedVars<Neutral::gamma,
                           Daughters::pipi>::NeutralDaughtersSharedVars()
    : R_Dk_vs_Dpi_(new RooRealVar("R_Dk_vs_Dpi_Gamma_pipi",
                   "Ratio of yields of Bu2Dst0pi decay channel for K "
                   "w.r.t. pi bachelor, for daughters=pipi, neutral=gamma",
                   0.075, 0.02, 0.1)) {}
                   
template <>
NeutralDaughtersSharedVars<Neutral::gamma,
                           Daughters::pik>::NeutralDaughtersSharedVars()
    : R_Dk_vs_Dpi_(new RooRealVar("R_Dk_vs_Dpi_Gamma_pik",
                   "Ratio of yields of Bu2Dst0pi decay channel for K "
                   "w.r.t. pi bachelor, for daughters=pik, neutral=gamma",
                   0.075, 0.02, 0.1)) {} 
