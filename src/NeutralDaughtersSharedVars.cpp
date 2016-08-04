#include "NeutralDaughtersSharedVars.h"
#include "Configuration.h"
#include "NeutralVars.h"
#include "DaughtersVars.h"

// Daughters specializations

template <>
NeutralDaughtersSharedVars<Neutral::pi0,
                           Daughters::kpi>::NeutralDaughtersSharedVars()
    : N_Dpi_("N_Dpi_Pi0_kpi", "Total number of Bu2Dst0H-like events,"
                              " for daughters=kpi, neutral=pi0",
             (NeutralVars<Neutral::pi0>::Get().signalExpected() +
              NeutralVars<Neutral::pi0>::Get().nonTmSignalExpected() +
              NeutralVars<Neutral::pi0>::Get().crossFeedExpected()) *
                 DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
             0, NeutralVars<Neutral::pi0>::Get().maxYield() *
                    DaughtersVars<Daughters::kpi>::Get().daughtersSF()),
      R_Dk_vs_Dpi_("R_Dk_vs_Dpi_Pi0_kpi",
                   "Ratio of yields of Bu2Dst0H decay channel for K "
                   "w.r.t. pi bachelor, for daughters=kpi, neutral=pi0",
                   0.075, 0.02, 0.1) {}
template <>
NeutralDaughtersSharedVars<Neutral::pi0,
                           Daughters::kk>::NeutralDaughtersSharedVars()
    : N_Dpi_("N_Dpi_Pi0_kk", "Total number of Bu2Dst0H-like events,"
                             " for daughters=kk, neutral=pi0",
             (NeutralVars<Neutral::pi0>::Get().signalExpected() +
              NeutralVars<Neutral::pi0>::Get().nonTmSignalExpected() +
              NeutralVars<Neutral::pi0>::Get().crossFeedExpected()) *
                 DaughtersVars<Daughters::kk>::Get().daughtersSF(),
             0, NeutralVars<Neutral::pi0>::Get().maxYield() *
                    DaughtersVars<Daughters::kk>::Get().daughtersSF()),
      R_Dk_vs_Dpi_("R_Dk_vs_Dpi_Pi0_kk",
                   "Ratio of yields of Bu2Dst0H decay channel for K "
                   "w.r.t. pi bachelor, for daughters=kk, neutral=pi0",
                   0.075, 0.02, 0.1) {}
template <>
NeutralDaughtersSharedVars<Neutral::pi0,
                           Daughters::pipi>::NeutralDaughtersSharedVars()
    : N_Dpi_("N_Dpi_Pi0_pipi", "Total number of Bu2Dst0H-like events,"
                               " for daughters=pipi, neutral=pi0",
             (NeutralVars<Neutral::pi0>::Get().signalExpected() +
              NeutralVars<Neutral::pi0>::Get().nonTmSignalExpected() +
              NeutralVars<Neutral::pi0>::Get().crossFeedExpected()) *
                 DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
             0, NeutralVars<Neutral::pi0>::Get().maxYield() *
                    DaughtersVars<Daughters::pipi>::Get().daughtersSF()),
      R_Dk_vs_Dpi_("R_Dk_vs_Dpi_Pi0_pipi",
                   "Ratio of yields of Bu2Dst0H decay channel for K "
                   "w.r.t. pi bachelor, for daughters=pipi, neutral=pi0",
                   0.075, 0.02, 0.1) {}
template <>
NeutralDaughtersSharedVars<Neutral::pi0,
                           Daughters::pik>::NeutralDaughtersSharedVars()
    : N_Dpi_("N_Dpi_Pi0_pik", "Total number of Bu2Dst0H-like events,"
                              " for daughters=pik, neutral=pi0",
             (NeutralVars<Neutral::pi0>::Get().signalExpected() +
              NeutralVars<Neutral::pi0>::Get().nonTmSignalExpected() +
              NeutralVars<Neutral::pi0>::Get().crossFeedExpected()) *
                 DaughtersVars<Daughters::pik>::Get().daughtersSF(),
             0, NeutralVars<Neutral::pi0>::Get().maxYield() *
                    DaughtersVars<Daughters::pik>::Get().daughtersSF()),
      R_Dk_vs_Dpi_("R_Dk_vs_Dpi_Pi0_pik",
                   "Ratio of yields of Bu2Dst0H decay channel for K "
                   "w.r.t. pi bachelor, for daughters=pik, neutral=pi0",
                   0.075, 0.02, 0.1) {}

template <>
NeutralDaughtersSharedVars<Neutral::gamma,
                           Daughters::kpi>::NeutralDaughtersSharedVars()
    : N_Dpi_("N_Dpi_Gamma_kpi", "Total number of Bu2Dst0H-like events,"
                                " for daughters=kpi, neutral=gamma",
             (NeutralVars<Neutral::gamma>::Get().signalExpected() +
              NeutralVars<Neutral::gamma>::Get().nonTmSignalExpected() +
              NeutralVars<Neutral::gamma>::Get().crossFeedExpected()) *
                 DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
             0, NeutralVars<Neutral::gamma>::Get().maxYield() *
                    DaughtersVars<Daughters::kpi>::Get().daughtersSF()),
      R_Dk_vs_Dpi_("R_Dk_vs_Dpi_Gamma_kpi",
                   "Ratio of yields of Bu2Dst0H decay channel for K "
                   "w.r.t. pi bachelor, for daughters=kpi, neutral=gamma",
                   0.075, 0.02, 0.1) {}

template <>
NeutralDaughtersSharedVars<Neutral::gamma,
                           Daughters::kk>::NeutralDaughtersSharedVars()
    : N_Dpi_("N_Dpi_Gamma_kk", "Total number of Bu2Dst0H-like events,"
                               " for daughters=kk, neutral=gamma",
             (NeutralVars<Neutral::gamma>::Get().signalExpected() +
              NeutralVars<Neutral::gamma>::Get().nonTmSignalExpected() +
              NeutralVars<Neutral::gamma>::Get().crossFeedExpected()) *
                 DaughtersVars<Daughters::kk>::Get().daughtersSF(),
             0, NeutralVars<Neutral::gamma>::Get().maxYield() *
                    DaughtersVars<Daughters::kk>::Get().daughtersSF()),
      R_Dk_vs_Dpi_("R_Dk_vs_Dpi_Gamma_kk",
                   "Ratio of yields of Bu2Dst0H decay channel for K "
                   "w.r.t. pi bachelor, for daughters=kk, neutral=gamma",
                   0.075, 0.02, 0.1) {}
template <>
NeutralDaughtersSharedVars<Neutral::gamma,
                           Daughters::pipi>::NeutralDaughtersSharedVars()
    : N_Dpi_("N_Dpi_Gamma_pipi", "Total number of Bu2Dst0H-like events,"
                                 " for daughters=pipi, neutral=gamma",
             (NeutralVars<Neutral::gamma>::Get().signalExpected() +
              NeutralVars<Neutral::gamma>::Get().nonTmSignalExpected() +
              NeutralVars<Neutral::gamma>::Get().crossFeedExpected()) *
                 DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
             0, NeutralVars<Neutral::gamma>::Get().maxYield() *
                    DaughtersVars<Daughters::pipi>::Get().daughtersSF()),
      R_Dk_vs_Dpi_("R_Dk_vs_Dpi_Gamma_pipi",
                   "Ratio of yields of Bu2Dst0H decay channel for K "
                   "w.r.t. pi bachelor, for daughters=pipi, neutral=gamma",
                   0.075, 0.02, 0.1) {}
template <>
NeutralDaughtersSharedVars<Neutral::gamma,
                           Daughters::pik>::NeutralDaughtersSharedVars()
    : N_Dpi_("N_Dpi_Gamma_pik", "Total number of Bu2Dst0H-like events,"
                                " for daughters=pik, neutral=gamma",
             (NeutralVars<Neutral::gamma>::Get().signalExpected() +
              NeutralVars<Neutral::gamma>::Get().nonTmSignalExpected() +
              NeutralVars<Neutral::gamma>::Get().crossFeedExpected()) *
                 DaughtersVars<Daughters::pik>::Get().daughtersSF(),
             0, NeutralVars<Neutral::gamma>::Get().maxYield() *
                    DaughtersVars<Daughters::pik>::Get().daughtersSF()),
      R_Dk_vs_Dpi_("R_Dk_vs_Dpi_Gamma_pik",
                   "Ratio of yields of Bu2Dst0H decay channel for K "
                   "w.r.t. pi bachelor, for daughters=pik, neutral=gamma",
                   0.075, 0.02, 0.1) {}
