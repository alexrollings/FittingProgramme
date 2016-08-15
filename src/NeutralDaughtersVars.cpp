#include "NeutralDaughtersVars.h"
#include "Configuration.h"
#include "NeutralVars.h"
#include "DaughtersVars.h"

// Daughters specializations

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(
          new RooRealVar("R_Dk_vs_Dpi_Pi0_kpi",
                         "Ratio of yields of Bu2Dst0pi decay channel for K "
                         "w.r.t. pi bachelor, for daughters=kpi, neutral=pi0",
                         0.075, 0.02, 0.1)),
      selfCrossFeedRate_("selfCrossFeedRate_pi0_kpi",
                         "Proportion of SCF in N_Dpi, pi0, kpi", 0.3082),
      crossFeedRate_("crossFeedRate_pi0_kpi", "Proportion of CF in N_Dpi, pi0, kpi",
                     0.3521) {}

template <>
NeutralDaughtersVars<Neutral::pi0,
                           Daughters::kk>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(new RooFormulaVar(
          "R_Dk_vs_Dpi_Pi0_kk",
          "Ratio of yields of Bu2Dst0pi decay channel for K "
          "w.r.t. pi bachelor, for daughters=kk, neutral=pi0",
          "@0*@1",
          RooArgList(
              NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get()
                  .R_Dk_vs_Dpi(),
              NeutralVars<Neutral::pi0>::Get().R_cp()))),
      selfCrossFeedRate_("selfCrossFeedRate_pi0_kk",
                         "Proportion of SCF in N_Dpi, pi0, kk", 0.3082, 0, 1),
      crossFeedRate_("crossFeedRate_pi0_kk", "Proportion of CF in N_Dpi, pi0, kk", 0.3521, 0, 1) {}

template <>
NeutralDaughtersVars<Neutral::pi0,
                           Daughters::pipi>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(new RooRealVar("R_Dk_vs_Dpi_Pi0_pipi",
                   "Ratio of yields of Bu2Dst0pi decay channel for K "
                   "w.r.t. pi bachelor, for daughters=pipi, neutral=pi0",
                   0.075, 0.02, 0.1)),
      selfCrossFeedRate_("selfCrossFeedRate_pi0_pipi",
                         "Proportion of SCF in N_Dpi, pi0, pipi", 0.3082, 0.25, 0.35),
      crossFeedRate_("crossFeedRate_pi0_pipi", "Proportion of CF in N_Dpi, pi0, pipi", 0.3521, 0.3, 0.4) {}


template <>
NeutralDaughtersVars<Neutral::pi0,
                           Daughters::pik>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(new RooRealVar("R_Dk_vs_Dpi_Pi0_pik",
                   "Ratio of yields of Bu2Dst0pi decay channel for K "
                   "w.r.t. pi bachelor, for daughters=pik, neutral=pi0",
                   0.075, 0.02, 0.1)),
      selfCrossFeedRate_("selfCrossFeedRate_pi0_pik",
                         "Proportion of SCF in N_Dpi, pi0, pik", 0.3082, 0.25, 0.34),
      crossFeedRate_("crossFeedRate_pi0_pik", "Proportion of CF in N_Dpi, pi0, pik", 0.3521, 0.3, 0.4) {}

template <>
NeutralDaughtersVars<Neutral::gamma,
                           Daughters::kpi>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(new RooRealVar("R_Dk_vs_Dpi_Gamma_kpi",
                   "Ratio of yields of Bu2Dst0pi decay channel for K "
                   "w.r.t. pi bachelor, for daughters=kpi, neutral=gamma",
                   0.075, 0.02, 0.1)),
      selfCrossFeedRate_("selfCrossFeedRate_gamma_kpi", "Proportion of SCF in N_Dpi, gamma, kpi", 0.4046),
      crossFeedRate_("crossFeedRate_gamma_kpi", "Proportion of CF in N_Dpi, gamma, kpi", 0.0625) {}

template <>
NeutralDaughtersVars<Neutral::gamma,
                           Daughters::kk>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(new RooFormulaVar("R_Dk_vs_Dpi_Gamma_kk",
                   "Ratio of yields of Bu2Dst0pi decay channel for K "
                   "w.r.t. pi bachelor, for daughters=kk, neutral=gamma",
          "@0*@1",
          RooArgList(
              NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get()
                  .R_Dk_vs_Dpi(),
              NeutralVars<Neutral::gamma>::Get().R_cp()))),
      selfCrossFeedRate_("selfCrossFeedRate_gamma_kk", "Proportion of SCF in N_Dpi, gamma, kk", 0.4046, 0.35, 0.45),
      crossFeedRate_("crossFeedRate_gamma_kk", "Proportion of CF in N_Dpi, gamma, kk", 0.0625, 0.01, 0.15) {}

template <>
NeutralDaughtersVars<Neutral::gamma,
                           Daughters::pipi>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(new RooRealVar("R_Dk_vs_Dpi_Gamma_pipi",
                   "Ratio of yields of Bu2Dst0pi decay channel for K "
                   "w.r.t. pi bachelor, for daughters=pipi, neutral=gamma",
                   0.075, 0.02, 0.1)),
      selfCrossFeedRate_("selfCrossFeedRate_gamma_pipi", "Proportion of SCF in N_Dpi, gamma, pipi", 0.4046, 0.35, 0.45),
      crossFeedRate_("crossFeedRate_gamma_pipi", "Proportion of CF in N_Dpi, gamma, pipi", 0.0625, 0.01, 0.15) {}
                   
template <>
NeutralDaughtersVars<Neutral::gamma,
                           Daughters::pik>::NeutralDaughtersVars()
    : R_Dk_vs_Dpi_(new RooRealVar("R_Dk_vs_Dpi_Gamma_pik",
                   "Ratio of yields of Bu2Dst0pi decay channel for K "
                   "w.r.t. pi bachelor, for daughters=pik, neutral=gamma",
                   0.075, 0.02, 0.1)), 
      selfCrossFeedRate_("selfCrossFeedRate_gamma_pik", "Proportion of SCF in N_Dpi, gamma, pik", 0.4046, 0.35, 0.45),
      crossFeedRate_("crossFeedRate_gamma_pik", "Proportion of CF in N_Dpi, gamma, pik", 0.0625, 0.01, 0.15) {}
