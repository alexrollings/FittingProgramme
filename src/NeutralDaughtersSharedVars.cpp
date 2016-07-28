#include "NeutralDaughtersSharedVars.h"
#include "Configuration.h"

// Daughters specializations

template <>
NeutralDaughtersSharedVars<Neutral::pi0, Daughters::kpi>::NeutralDaughtersSharedVars()
    : bachelorRatio_Bu2Dst0H_("bachelorRatio_Bu2Dst0H_Pi0_kpi",
                            "Ratio of yields of Bu2Dst0H decay channel for K "
                            "w.r.t. pi bachelor, for daughters=kpi, neutral=pi0",
                            0.075, 0.02, 0.1), 
      bachelorRatio_Bu2Dst0Hst_("bachelorRatio_Bu2Dst0Hst_Pi0_kpi",
                            "Ratio of yields of Bu2Dst0Hst decay channel for K "
                            "w.r.t. pi bachelor, for daughters=kpi, neutral=pi0",
                            0.075, 0.02, 0.1) {} 

template <>
NeutralDaughtersSharedVars<Neutral::pi0, Daughters::kk>::NeutralDaughtersSharedVars()
    : bachelorRatio_Bu2Dst0H_("bachelorRatio_Bu2Dst0H_Pi0_kk",
                            "Ratio of yields of Bu2Dst0H decay channel for K "
                            "w.r.t. pi bachelor, for daughters=kk, neutral=pi0",
                            0.075, 0.02, 0.1), 
      bachelorRatio_Bu2Dst0Hst_("bachelorRatio_Bu2Dst0Hst_Pi0_kk",
                            "Ratio of yields of Bu2Dst0Hst decay channel for K "
                            "w.r.t. pi bachelor, for daughters=kk, neutral=pi0",
                            0.075, 0.02, 0.1) {} 
template <>
NeutralDaughtersSharedVars<Neutral::pi0, Daughters::pipi>::NeutralDaughtersSharedVars()
    : bachelorRatio_Bu2Dst0H_("bachelorRatio_Bu2Dst0H_Pi0_pipi",
                            "Ratio of yields of Bu2Dst0H decay channel for K "
                            "w.r.t. pi bachelor, for daughters=pipi, neutral=pi0",
                            0.075, 0.02, 0.1), 
      bachelorRatio_Bu2Dst0Hst_("bachelorRatio_Bu2Dst0Hst_Pi0_pipi",
                            "Ratio of yields of Bu2Dst0Hst decay channel for K "
                            "w.r.t. pi bachelor, for daughters=pipi, neutral=pi0",
                            0.075, 0.02, 0.1) {} 
template <>
NeutralDaughtersSharedVars<Neutral::pi0, Daughters::pik>::NeutralDaughtersSharedVars()
    : bachelorRatio_Bu2Dst0H_("bachelorRatio_Bu2Dst0H_Pi0_pik",
                            "Ratio of yields of Bu2Dst0H decay channel for K "
                            "w.r.t. pi bachelor, for daughters=pik, neutral=pi0",
                            0.075, 0.02, 0.1), 
      bachelorRatio_Bu2Dst0Hst_("bachelorRatio_Bu2Dst0Hst_Pi0_pik",
                            "Ratio of yields of Bu2Dst0Hst decay channel for K "
                            "w.r.t. pi bachelor, for daughters=pik, neutral=pi0",
                            0.075, 0.02, 0.1) {} 

template <>
NeutralDaughtersSharedVars<Neutral::gamma, Daughters::kpi>::NeutralDaughtersSharedVars()
    : bachelorRatio_Bu2Dst0H_("bachelorRatio_Bu2Dst0H_Gamma_kpi",
                            "Ratio of yields of Bu2Dst0H decay channel for K "
                            "w.r.t. pi bachelor, for daughters=kpi, neutral=gamma",
                            0.075, 0.02, 0.1), 
      bachelorRatio_Bu2Dst0Hst_("bachelorRatio_Bu2Dst0Hst_Gamma_kpi",
                            "Ratio of yields of Bu2Dst0Hst decay channel for K "
                            "w.r.t. pi bachelor, for daughters=kpi, neutral=gamma",
                            0.075, 0.02, 0.1) {} 

template <>
NeutralDaughtersSharedVars<Neutral::gamma, Daughters::kk>::NeutralDaughtersSharedVars()
    : bachelorRatio_Bu2Dst0H_("bachelorRatio_Bu2Dst0H_Gamma_kk",
                            "Ratio of yields of Bu2Dst0H decay channel for K "
                            "w.r.t. pi bachelor, for daughters=kk, neutral=gamma",
                            0.075, 0.02, 0.1), 
      bachelorRatio_Bu2Dst0Hst_("bachelorRatio_Bu2Dst0Hst_Gamma_kk",
                            "Ratio of yields of Bu2Dst0Hst decay channel for K "
                            "w.r.t. pi bachelor, for daughters=kk, neutral=gamma",
                            0.075, 0.02, 0.1) {} 
template <>
NeutralDaughtersSharedVars<Neutral::gamma, Daughters::pipi>::NeutralDaughtersSharedVars()
    : bachelorRatio_Bu2Dst0H_("bachelorRatio_Bu2Dst0H_Gamma_pipi",
                            "Ratio of yields of Bu2Dst0H decay channel for K "
                            "w.r.t. pi bachelor, for daughters=pipi, neutral=gamma",
                            0.075, 0.02, 0.1), 
      bachelorRatio_Bu2Dst0Hst_("bachelorRatio_Bu2Dst0Hst_Gamma_pipi",
                            "Ratio of yields of Bu2Dst0Hst decay channel for K "
                            "w.r.t. pi bachelor, for daughters=pipi, neutral=gamma",
                            0.075, 0.02, 0.1) {} 
template <>
NeutralDaughtersSharedVars<Neutral::gamma, Daughters::pik>::NeutralDaughtersSharedVars()
    : bachelorRatio_Bu2Dst0H_("bachelorRatio_Bu2Dst0H_Gamma_pik",
                            "Ratio of yields of Bu2Dst0H decay channel for K "
                            "w.r.t. pi bachelor, for daughters=pik, neutral=gamma",
                            0.075, 0.02, 0.1), 
      bachelorRatio_Bu2Dst0Hst_("bachelorRatio_Bu2Dst0Hst_Gamma_pik",
                            "Ratio of yields of Bu2Dst0Hst decay channel for K "
                            "w.r.t. pi bachelor, for daughters=pik, neutral=gamma",
                            0.075, 0.02, 0.1) {} 
