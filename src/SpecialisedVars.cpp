#include "SpecialisedVars.h"
#include "Configuration.h"
#include "DaughtersVars.h"
#include "NeutralDaughtersSharedVars.h"
#include "NeutralVars.h"

template <>
SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kpi>::SpecialisedVars()
    : N_Dh_(new RooRealVar(
          "N_Dpi_pi0_kpi", "Total number of Bu2Dst0pi-like events,"
                           " for daughters=kpi, neutral=pi0",
          (NeutralVars<Neutral::pi0>::Get().signalExpected() +
           NeutralVars<Neutral::pi0>::Get().nonTmSignalExpected() +
           NeutralVars<Neutral::pi0>::Get().crossFeedExpected()) *
              DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
          0, NeutralVars<Neutral::pi0>::Get().maxYield() *
                 DaughtersVars<Daughters::kpi>::Get().daughtersSF())) {}

template <>
SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kpi>::SpecialisedVars()
    : N_Dh_(new RooRealVar(
          "N_Dpi_gamma_kpi", "Total number of Bu2Dst0pi-like events,"
                             " for daughters=kpi, neutral=gamma",
          (NeutralVars<Neutral::gamma>::Get().signalExpected() +
           NeutralVars<Neutral::gamma>::Get().nonTmSignalExpected() +
           NeutralVars<Neutral::gamma>::Get().crossFeedExpected()) *
              DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
          0, NeutralVars<Neutral::gamma>::Get().maxYield() *
                 DaughtersVars<Daughters::kpi>::Get().daughtersSF())) {}

template <>
SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kpi>::SpecialisedVars()
    : N_Dh_(new RooFormulaVar(
          "N_Dk_pi0_kpi", "Total number of Bu2Dst0K-like events, for "
                          "daughters=kpi, neutral=pi0",
          "@0*@1",
          RooArgList(
              SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Get()
                  .N_Dh(),
              NeutralDaughtersSharedVars<Neutral::pi0, Daughters::kpi>::Get()
                  .R_Dk_vs_Dpi()))) {}

template <>
SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kpi>::SpecialisedVars()
    : N_Dh_(new RooFormulaVar(
          "N_Dk_gamma_kpi", "Total number of Bu2Dst0K-like events, for "
                            "daughters=kpi, neutral=gamma",
          "@0*@1",
          RooArgList(
              SpecialisedVars<Neutral::gamma, Bachelor::pi,
                              Daughters::kpi>::Get()
                  .N_Dh(),
              NeutralDaughtersSharedVars<Neutral::gamma, Daughters::kpi>::Get()
                  .R_Dk_vs_Dpi()))) {}


template <>
SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kk>::SpecialisedVars()
    : N_Dh_(new RooRealVar(
          "N_Dpi_pi0_kk", "Total number of Bu2Dst0pi-like events,"
                           " for daughters=kk, neutral=pi0",
          (NeutralVars<Neutral::pi0>::Get().signalExpected() +
           NeutralVars<Neutral::pi0>::Get().nonTmSignalExpected() +
           NeutralVars<Neutral::pi0>::Get().crossFeedExpected()) *
              DaughtersVars<Daughters::kk>::Get().daughtersSF(),
          0, NeutralVars<Neutral::pi0>::Get().maxYield() *
                 DaughtersVars<Daughters::kk>::Get().daughtersSF())) {}

template <>
SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kk>::SpecialisedVars()
    : N_Dh_(new RooRealVar(
          "N_Dpi_gamma_kk", "Total number of Bu2Dst0pi-like events,"
                             " for daughters=kk, neutral=gamma",
          (NeutralVars<Neutral::gamma>::Get().signalExpected() +
           NeutralVars<Neutral::gamma>::Get().nonTmSignalExpected() +
           NeutralVars<Neutral::gamma>::Get().crossFeedExpected()) *
              DaughtersVars<Daughters::kk>::Get().daughtersSF(),
          0, NeutralVars<Neutral::gamma>::Get().maxYield() *
                 DaughtersVars<Daughters::kk>::Get().daughtersSF())) {}

template <>
SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kk>::SpecialisedVars()
    : N_Dh_(new RooFormulaVar(
          "N_Dk_pi0_kk", "Total number of Bu2Dst0K-like events, for "
                          "daughters=kk, neutral=pi0",
          "@0*@1",
          RooArgList(
              SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kk>::Get()
                  .N_Dh(),
              NeutralDaughtersSharedVars<Neutral::pi0, Daughters::kk>::Get()
                  .R_Dk_vs_Dpi()))) {}

template <>
SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kk>::SpecialisedVars()
    : N_Dh_(new RooFormulaVar(
          "N_Dk_gamma_kk", "Total number of Bu2Dst0K-like events, for "
                            "daughters=kk, neutral=gamma",
          "@0*@1",
          RooArgList(
              SpecialisedVars<Neutral::gamma, Bachelor::pi,
                              Daughters::kk>::Get()
                  .N_Dh(),
              NeutralDaughtersSharedVars<Neutral::gamma, Daughters::kk>::Get()
                  .R_Dk_vs_Dpi()))) {}


template <>
SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pipi>::SpecialisedVars()
    : N_Dh_(new RooRealVar(
          "N_Dpi_pi0_pipi", "Total number of Bu2Dst0pi-like events,"
                           " for daughters=pipi, neutral=pi0",
          (NeutralVars<Neutral::pi0>::Get().signalExpected() +
           NeutralVars<Neutral::pi0>::Get().nonTmSignalExpected() +
           NeutralVars<Neutral::pi0>::Get().crossFeedExpected()) *
              DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
          0, NeutralVars<Neutral::pi0>::Get().maxYield() *
                 DaughtersVars<Daughters::pipi>::Get().daughtersSF())) {}

template <>
SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pipi>::SpecialisedVars()
    : N_Dh_(new RooRealVar(
          "N_Dpi_gamma_pipi", "Total number of Bu2Dst0pi-like events,"
                             " for daughters=pipi, neutral=gamma",
          (NeutralVars<Neutral::gamma>::Get().signalExpected() +
           NeutralVars<Neutral::gamma>::Get().nonTmSignalExpected() +
           NeutralVars<Neutral::gamma>::Get().crossFeedExpected()) *
              DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
          0, NeutralVars<Neutral::gamma>::Get().maxYield() *
                 DaughtersVars<Daughters::pipi>::Get().daughtersSF())) {}

template <>
SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pipi>::SpecialisedVars()
    : N_Dh_(new RooFormulaVar(
          "N_Dk_pi0_pipi", "Total number of Bu2Dst0K-like events, for "
                          "daughters=pipi, neutral=pi0",
          "@0*@1",
          RooArgList(
              SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Get()
                  .N_Dh(),
              NeutralDaughtersSharedVars<Neutral::pi0, Daughters::pipi>::Get()
                  .R_Dk_vs_Dpi()))) {}

template <>
SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pipi>::SpecialisedVars()
    : N_Dh_(new RooFormulaVar(
          "N_Dk_gamma_pipi", "Total number of Bu2Dst0K-like events, for "
                            "daughters=pipi, neutral=gamma",
          "@0*@1",
          RooArgList(
              SpecialisedVars<Neutral::gamma, Bachelor::pi,
                              Daughters::pipi>::Get()
                  .N_Dh(),
              NeutralDaughtersSharedVars<Neutral::gamma, Daughters::pipi>::Get()
                  .R_Dk_vs_Dpi()))) {}

template <>
SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pik>::SpecialisedVars()
    : N_Dh_(new RooRealVar(
          "N_Dpi_pi0_pik", "Total number of Bu2Dst0pi-like events,"
                           " for daughters=pik, neutral=pi0",
          (NeutralVars<Neutral::pi0>::Get().signalExpected() +
           NeutralVars<Neutral::pi0>::Get().nonTmSignalExpected() +
           NeutralVars<Neutral::pi0>::Get().crossFeedExpected()) *
              DaughtersVars<Daughters::pik>::Get().daughtersSF(),
          0, NeutralVars<Neutral::pi0>::Get().maxYield() *
                 DaughtersVars<Daughters::pik>::Get().daughtersSF())) {}

template <>
SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pik>::SpecialisedVars()
    : N_Dh_(new RooRealVar(
          "N_Dpi_gamma_pik", "Total number of Bu2Dst0pi-like events,"
                             " for daughters=pik, neutral=gamma",
          (NeutralVars<Neutral::gamma>::Get().signalExpected() +
           NeutralVars<Neutral::gamma>::Get().nonTmSignalExpected() +
           NeutralVars<Neutral::gamma>::Get().crossFeedExpected()) *
              DaughtersVars<Daughters::pik>::Get().daughtersSF(),
          0, NeutralVars<Neutral::gamma>::Get().maxYield() *
                 DaughtersVars<Daughters::pik>::Get().daughtersSF())) {}

template <>
SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pik>::SpecialisedVars()
    : N_Dh_(new RooFormulaVar(
          "N_Dk_pi0_pik", "Total number of Bu2Dst0K-like events, for "
                          "daughters=pik, neutral=pi0",
          "@0*@1",
          RooArgList(
              SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pik>::Get()
                  .N_Dh(),
              NeutralDaughtersSharedVars<Neutral::pi0, Daughters::pik>::Get()
                  .R_Dk_vs_Dpi()))) {}

template <>
SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pik>::SpecialisedVars()
    : N_Dh_(new RooFormulaVar(
          "N_Dk_gamma_pik", "Total number of Bu2Dst0K-like events, for "
                            "daughters=pik, neutral=gamma",
          "@0*@1",
          RooArgList(
              SpecialisedVars<Neutral::gamma, Bachelor::pi,
                              Daughters::pik>::Get()
                  .N_Dh(),
              NeutralDaughtersSharedVars<Neutral::gamma, Daughters::pik>::Get()
                  .R_Dk_vs_Dpi()))) {}


