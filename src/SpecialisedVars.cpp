// #include "SpecialisedVars.h"
// #include "Configuration.h"
// #include "DaughtersVars.h"
// #include "NeutralDaughtersVars.h"
// #include "NeutralVars.h"
//
// template <>
// SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kpi>::SpecialisedVars()
//     : N_Dh_(new RooRealVar(
//           "N_Dpi_pi0_kpi", "Total number of Bu2Dst0pi-like events,"
//                            " for daughters=kpi, neutral=pi0",
//           (NeutralVars<Neutral::pi0>::Get().signalExpected() +
//            NeutralVars<Neutral::pi0>::Get().nonTmSignalExpected() +
//            NeutralVars<Neutral::pi0>::Get().crossFeedExpected()) *
//               DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::pi0>::Get().maxYield() *
//                  DaughtersVars<Daughters::kpi>::Get().daughtersSF())),
//       N_Dh_Bu2D0Hst_(new RooRealVar(
//           "N_Dpi_Bu2D0Hst_pi0_kpi", "Total number of Bu2D0rho-like events,"
//                            " for daughters=kpi, neutral=pi0",
//           NeutralVars<Neutral::pi0>::Get().bu2D0HstExpected() *
//               DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::pi0>::Get().maxYield() *
//                  DaughtersVars<Daughters::kpi>::Get().daughtersSF())),
//       N_Dh_Bd2DstH_(new RooRealVar(
//           "N_Dpi_Bd2DstH_pi0_kpi", "Total number of Bd2Dstpi-like events,"
//                            " for daughters=kpi, neutral=pi0",
//           NeutralVars<Neutral::pi0>::Get().bd2DstHExpected() *
//               DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::pi0>::Get().maxYield() *
//                  DaughtersVars<Daughters::kpi>::Get().daughtersSF())),
//       N_Dh_Bu2D0H_(new RooRealVar(
//           "N_Dpi_Bu2D0H_pi0_kpi", "Total number of Bu2D0pi-like events,"
//                            " for daughters=kpi, neutral=pi0",
//           NeutralVars<Neutral::pi0>::Get().bu2D0HExpected() *
//               DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::pi0>::Get().maxYield() *
//                  DaughtersVars<Daughters::kpi>::Get().daughtersSF())) {}
//
// template <>
// SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kpi>::SpecialisedVars()
//     : N_Dh_(new RooRealVar(
//           "N_Dpi_gamma_kpi", "Total number of Bu2Dst0pi-like events,"
//                              " for daughters=kpi, neutral=gamma",
//           (NeutralVars<Neutral::gamma>::Get().signalExpected() +
//            NeutralVars<Neutral::gamma>::Get().nonTmSignalExpected() +
//            NeutralVars<Neutral::gamma>::Get().crossFeedExpected()) *
//               DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::gamma>::Get().maxYield() *
//                  DaughtersVars<Daughters::kpi>::Get().daughtersSF())),
//       N_Dh_Bu2D0Hst_(new RooRealVar(
//           "N_Dpi_Bu2D0Hst_gamma_kpi", "Total number of Bu2D0rho-like events,"
//                            " for daughters=kpi, neutral=gamma",
//           NeutralVars<Neutral::gamma>::Get().bu2D0HstExpected() *
//               DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::gamma>::Get().maxYield() *
//                  DaughtersVars<Daughters::kpi>::Get().daughtersSF())),
//       N_Dh_Bd2DstH_(new RooRealVar(
//           "N_Dpi_Bd2DstH_gamma_kpi", "Total number of Bd2Dstpi-like events,"
//                            " for daughters=kpi, neutral=gamma",
//           NeutralVars<Neutral::gamma>::Get().bd2DstHExpected() *
//               DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::gamma>::Get().maxYield() *
//                  DaughtersVars<Daughters::kpi>::Get().daughtersSF())),
//       N_Dh_Bu2D0H_(new RooRealVar(
//           "N_Dpi_Bu2D0H_gamma_kpi", "Total number of Bu2D0pi-like events,"
//                            " for daughters=kpi, neutral=gamma",
//           NeutralVars<Neutral::gamma>::Get().bu2D0HExpected() *
//               DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::gamma>::Get().maxYield() *
//                  DaughtersVars<Daughters::kpi>::Get().daughtersSF())) {}
//
// template <>
// SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kpi>::SpecialisedVars()
//     : N_Dh_(new RooFormulaVar(
//           "N_Dk_pi0_kpi", "Total number of Bu2Dst0K-like events, for "
//                           "daughters=kpi, neutral=pi0",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Get()
//                   .N_Dh(),
//               NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get()
//                   .R_Dk_vs_Dpi()))),
//       N_Dh_Bu2D0Hst_(new RooFormulaVar(
//           "N_Dk_Bu2D0Hst_pi0_kpi", "Total number of Bu2D0Kst-like events, for "
//                           "daughters=kpi, neutral=pi0",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Get()
//                   .N_Dh_Bu2D0Hst(),
//               DaughtersVars<Daughters::kpi>::Get()
//                   .R_Dk_vs_Dpi_Bu2D0Hst()))),
//       N_Dh_Bd2DstH_(new RooFormulaVar(
//           "N_Dk_Bd2DstH_pi0_kpi", "Total number of Bd2DstK-like events, for "
//                           "daughters=kpi, neutral=pi0",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Get()
//                   .N_Dh_Bd2DstH(),
//               Configuration::Get()
//                   .R_Dk_vs_Dpi_Bd2DstH()))),
//       N_Dh_Bu2D0H_(new RooFormulaVar(
//           "N_Dk_Bu2D0H_pi0_kpi", "Total number of Bu2D0K-like events, for "
//                           "daughters=kpi, neutral=pi0",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Get()
//                   .N_Dh_Bu2D0H(),
//               DaughtersVars<Daughters::kpi>::Get()
//                   .R_Dk_vs_Dpi_Bu2D0H()))) {}
//
// template <>
// SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kpi>::SpecialisedVars()
//     : N_Dh_(new RooFormulaVar(
//           "N_Dk_gamma_kpi", "Total number of Bu2Dst0K-like events, for "
//                             "daughters=kpi, neutral=gamma",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::gamma, Bachelor::pi,
//                               Daughters::kpi>::Get()
//                   .N_Dh(),
//               NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get()
//                   .R_Dk_vs_Dpi()))),
//       N_Dh_Bu2D0Hst_(new RooFormulaVar(
//           "N_Dk_Bu2D0Hst_gamma_kpi", "Total number of Bu2D0Kst-like events, for "
//                           "daughters=kpi, neutral=gamma",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Get()
//                   .N_Dh_Bu2D0Hst(),
//               DaughtersVars<Daughters::kpi>::Get()
//                   .R_Dk_vs_Dpi_Bu2D0Hst()))),
//       N_Dh_Bd2DstH_(new RooFormulaVar(
//           "N_Dk_Bd2DstH_gamma_kpi", "Total number of Bd2DstK-like events, for "
//                           "daughters=kpi, neutral=gamma",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Get()
//                   .N_Dh_Bd2DstH(),
//               Configuration::Get()
//                   .R_Dk_vs_Dpi_Bd2DstH()))),
//       N_Dh_Bu2D0H_(new RooFormulaVar(
//           "N_Dk_Bu2D0H_gamma_kpi", "Total number of Bu2D0K-like events, for "
//                           "daughters=kpi, neutral=gamma",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Get()
//                   .N_Dh_Bu2D0H(),
//               DaughtersVars<Daughters::kpi>::Get()
//                   .R_Dk_vs_Dpi_Bu2D0H()))) {}
//
//
// template <>
// SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kk>::SpecialisedVars()
//     : N_Dh_(new RooRealVar(
//           "N_Dpi_pi0_kk", "Total number of Bu2Dst0pi-like events,"
//                            " for daughters=kk, neutral=pi0",
//           (NeutralVars<Neutral::pi0>::Get().signalExpected() +
//            NeutralVars<Neutral::pi0>::Get().nonTmSignalExpected() +
//            NeutralVars<Neutral::pi0>::Get().crossFeedExpected()) *
//               DaughtersVars<Daughters::kk>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::pi0>::Get().maxYield() *
//                  DaughtersVars<Daughters::kk>::Get().daughtersSF())),
//       N_Dh_Bu2D0Hst_(new RooRealVar(
//           "N_Dpi_Bu2D0Hst_pi0_kk", "Total number of Bu2D0rho-like events,"
//                            " for daughters=kk, neutral=pi0",
//           NeutralVars<Neutral::pi0>::Get().bu2D0HstExpected() *
//               DaughtersVars<Daughters::kk>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::pi0>::Get().maxYield() *
//                  DaughtersVars<Daughters::kk>::Get().daughtersSF())),
//       N_Dh_Bd2DstH_(new RooRealVar(
//           "N_Dpi_Bd2DstH_pi0_kk", "Total number of Bd2Dstpi-like events,"
//                            " for daughters=kk, neutral=pi0",
//           NeutralVars<Neutral::pi0>::Get().bd2DstHExpected() *
//               DaughtersVars<Daughters::kk>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::pi0>::Get().maxYield() *
//                  DaughtersVars<Daughters::kk>::Get().daughtersSF())),
//       N_Dh_Bu2D0H_(new RooRealVar(
//           "N_Dpi_Bu2D0H_pi0_kk", "Total number of Bu2D0pi-like events,"
//                            " for daughters=kk, neutral=pi0",
//           NeutralVars<Neutral::pi0>::Get().bu2D0HExpected() *
//               DaughtersVars<Daughters::kk>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::pi0>::Get().maxYield() *
//                  DaughtersVars<Daughters::kk>::Get().daughtersSF())) {}
//
// template <>
// SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kk>::SpecialisedVars()
//     : N_Dh_(new RooRealVar(
//           "N_Dpi_gamma_kk", "Total number of Bu2Dst0pi-like events,"
//                              " for daughters=kk, neutral=gamma",
//           (NeutralVars<Neutral::gamma>::Get().signalExpected() +
//            NeutralVars<Neutral::gamma>::Get().nonTmSignalExpected() +
//            NeutralVars<Neutral::gamma>::Get().crossFeedExpected()) *
//               DaughtersVars<Daughters::kk>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::gamma>::Get().maxYield() *
//                  DaughtersVars<Daughters::kk>::Get().daughtersSF())),
//       N_Dh_Bu2D0Hst_(new RooRealVar(
//           "N_Dpi_Bu2D0Hst_gamma_kk", "Total number of Bu2D0rho-like events,"
//                            " for daughters=kk, neutral=gamma",
//           NeutralVars<Neutral::gamma>::Get().bu2D0HstExpected() *
//               DaughtersVars<Daughters::kk>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::gamma>::Get().maxYield() *
//                  DaughtersVars<Daughters::kk>::Get().daughtersSF())),
//       N_Dh_Bd2DstH_(new RooRealVar(
//           "N_Dpi_Bd2DstH_gamma_kk", "Total number of Bd2Dstpi-like events,"
//                            " for daughters=kk, neutral=gamma",
//           NeutralVars<Neutral::gamma>::Get().bd2DstHExpected() *
//               DaughtersVars<Daughters::kk>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::gamma>::Get().maxYield() *
//                  DaughtersVars<Daughters::kk>::Get().daughtersSF())),
//       N_Dh_Bu2D0H_(new RooRealVar(
//           "N_Dpi_Bu2D0H_gamma_kk", "Total number of Bu2D0pi-like events,"
//                            " for daughters=kk, neutral=gamma",
//           NeutralVars<Neutral::gamma>::Get().bu2D0HExpected() *
//               DaughtersVars<Daughters::kk>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::gamma>::Get().maxYield() *
//                  DaughtersVars<Daughters::kk>::Get().daughtersSF())) {}
//
// template <>
// SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kk>::SpecialisedVars()
//     : N_Dh_(new RooFormulaVar(
//           "N_Dk_pi0_kk", "Total number of Bu2Dst0K-like events, for "
//                           "daughters=kk, neutral=pi0",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kk>::Get()
//                   .N_Dh(),
//               NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get()
//                   .R_Dk_vs_Dpi()))),
//       N_Dh_Bu2D0Hst_(new RooFormulaVar(
//           "N_Dk_Bu2D0Hst_pi0_kk", "Total number of Bu2D0Kst-like events, for "
//                           "daughters=kk, neutral=pi0",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kk>::Get()
//                   .N_Dh_Bu2D0Hst(),
//               DaughtersVars<Daughters::kk>::Get()
//                   .R_Dk_vs_Dpi_Bu2D0Hst()))),
//       N_Dh_Bd2DstH_(new RooFormulaVar(
//           "N_Dk_Bd2DstH_pi0_kk", "Total number of Bd2DstK-like events, for "
//                           "daughters=kk, neutral=pi0",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kk>::Get()
//                   .N_Dh_Bd2DstH(),
//               Configuration::Get()
//                   .R_Dk_vs_Dpi_Bd2DstH()))),
//       N_Dh_Bu2D0H_(new RooFormulaVar(
//           "N_Dk_Bu2D0H_pi0_kk", "Total number of Bu2D0K-like events, for "
//                           "daughters=kk, neutral=pi0",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kk>::Get()
//                   .N_Dh_Bu2D0H(),
//               DaughtersVars<Daughters::kk>::Get()
//                   .R_Dk_vs_Dpi_Bu2D0H()))) {}
//
// template <>
// SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kk>::SpecialisedVars()
//     : N_Dh_(new RooFormulaVar(
//           "N_Dk_gamma_kk", "Total number of Bu2Dst0K-like events, for "
//                             "daughters=kk, neutral=gamma",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::gamma, Bachelor::pi,
//                               Daughters::kk>::Get()
//                   .N_Dh(),
//               NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get()
//                   .R_Dk_vs_Dpi()))),
//       N_Dh_Bu2D0Hst_(new RooFormulaVar(
//           "N_Dk_Bu2D0Hst_gamma_kk", "Total number of Bu2D0Kst-like events, for "
//                           "daughters=kk, neutral=gamma",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kk>::Get()
//                   .N_Dh_Bu2D0Hst(),
//               DaughtersVars<Daughters::kk>::Get()
//                   .R_Dk_vs_Dpi_Bu2D0Hst()))),
//       N_Dh_Bd2DstH_(new RooFormulaVar(
//           "N_Dk_Bd2DstH_gamma_kk", "Total number of Bd2DstK-like events, for "
//                           "daughters=kk, neutral=gamma",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kk>::Get()
//                   .N_Dh_Bd2DstH(),
//               Configuration::Get()
//                   .R_Dk_vs_Dpi_Bd2DstH()))),
//       N_Dh_Bu2D0H_(new RooFormulaVar(
//           "N_Dk_Bu2D0H_gamma_kk", "Total number of Bu2D0K-like events, for "
//                           "daughters=kk, neutral=gamma",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kk>::Get()
//                   .N_Dh_Bu2D0H(),
//               DaughtersVars<Daughters::kk>::Get()
//                   .R_Dk_vs_Dpi_Bu2D0H()))) {}
//
//
// template <>
// SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pipi>::SpecialisedVars()
//     : N_Dh_(new RooRealVar(
//           "N_Dpi_pi0_pipi", "Total number of Bu2Dst0pi-like events,"
//                            " for daughters=pipi, neutral=pi0",
//           (NeutralVars<Neutral::pi0>::Get().signalExpected() +
//            NeutralVars<Neutral::pi0>::Get().nonTmSignalExpected() +
//            NeutralVars<Neutral::pi0>::Get().crossFeedExpected()) *
//               DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::pi0>::Get().maxYield() *
//                  DaughtersVars<Daughters::pipi>::Get().daughtersSF())),
//       N_Dh_Bu2D0Hst_(new RooRealVar(
//           "N_Dpi_Bu2D0Hst_pi0_pipi", "Total number of Bu2D0rho-like events,"
//                            " for daughters=pipi, neutral=pi0",
//           NeutralVars<Neutral::pi0>::Get().bu2D0HstExpected() *
//               DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::pi0>::Get().maxYield() *
//                  DaughtersVars<Daughters::pipi>::Get().daughtersSF())),
//       N_Dh_Bd2DstH_(new RooRealVar(
//           "N_Dpi_Bd2DstH_pi0_pipi", "Total number of Bd2Dstpi-like events,"
//                            " for daughters=pipi, neutral=pi0",
//           NeutralVars<Neutral::pi0>::Get().bd2DstHExpected() *
//               DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::pi0>::Get().maxYield() *
//                  DaughtersVars<Daughters::pipi>::Get().daughtersSF())),
//       N_Dh_Bu2D0H_(new RooRealVar(
//           "N_Dpi_Bu2D0H_pi0_pipi", "Total number of Bu2D0pi-like events,"
//                            " for daughters=pipi, neutral=pi0",
//           NeutralVars<Neutral::pi0>::Get().bu2D0HExpected() *
//               DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::pi0>::Get().maxYield() *
//                  DaughtersVars<Daughters::pipi>::Get().daughtersSF())) {}
//
// template <>
// SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pipi>::SpecialisedVars()
//     : N_Dh_(new RooRealVar(
//           "N_Dpi_gamma_pipi", "Total number of Bu2Dst0pi-like events,"
//                              " for daughters=pipi, neutral=gamma",
//           (NeutralVars<Neutral::gamma>::Get().signalExpected() +
//            NeutralVars<Neutral::gamma>::Get().nonTmSignalExpected() +
//            NeutralVars<Neutral::gamma>::Get().crossFeedExpected()) *
//               DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::gamma>::Get().maxYield() *
//                  DaughtersVars<Daughters::pipi>::Get().daughtersSF())),
//       N_Dh_Bu2D0Hst_(new RooRealVar(
//           "N_Dpi_Bu2D0Hst_gamma_pipi", "Total number of Bu2D0rho-like events,"
//                            " for daughters=pipi, neutral=gamma",
//           NeutralVars<Neutral::gamma>::Get().bu2D0HstExpected() *
//               DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::gamma>::Get().maxYield() *
//                  DaughtersVars<Daughters::pipi>::Get().daughtersSF())),
//       N_Dh_Bd2DstH_(new RooRealVar(
//           "N_Dpi_Bd2DstH_gamma_pipi", "Total number of Bd2Dstpi-like events,"
//                            " for daughters=pipi, neutral=gamma",
//           NeutralVars<Neutral::gamma>::Get().bd2DstHExpected() *
//               DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::gamma>::Get().maxYield() *
//                  DaughtersVars<Daughters::pipi>::Get().daughtersSF())),
//       N_Dh_Bu2D0H_(new RooRealVar(
//           "N_Dpi_Bu2D0H_gamma_pipi", "Total number of Bu2D0pi-like events,"
//                            " for daughters=pipi, neutral=gamma",
//           NeutralVars<Neutral::gamma>::Get().bu2D0HExpected() *
//               DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::gamma>::Get().maxYield() *
//                  DaughtersVars<Daughters::pipi>::Get().daughtersSF())) {}
//
// template <>
// SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pipi>::SpecialisedVars()
//     : N_Dh_(new RooFormulaVar(
//           "N_Dk_pi0_pipi", "Total number of Bu2Dst0K-like events, for "
//                           "daughters=pipi, neutral=pi0",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Get()
//                   .N_Dh(),
//               NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::Get()
//                   .R_Dk_vs_Dpi()))),
//       N_Dh_Bu2D0Hst_(new RooFormulaVar(
//           "N_Dk_Bu2D0Hst_pi0_pipi", "Total number of Bu2D0Kst-like events, for "
//                           "daughters=pipi, neutral=pi0",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Get()
//                   .N_Dh_Bu2D0Hst(),
//               DaughtersVars<Daughters::pipi>::Get()
//                   .R_Dk_vs_Dpi_Bu2D0Hst()))),
//       N_Dh_Bd2DstH_(new RooFormulaVar(
//           "N_Dk_Bd2DstH_pi0_pipi", "Total number of Bd2DstK-like events, for "
//                           "daughters=pipi, neutral=pi0",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Get()
//                   .N_Dh_Bd2DstH(),
//               Configuration::Get()
//                   .R_Dk_vs_Dpi_Bd2DstH()))),
//       N_Dh_Bu2D0H_(new RooFormulaVar(
//           "N_Dk_Bu2D0H_pi0_pipi", "Total number of Bu2D0K-like events, for "
//                           "daughters=pipi, neutral=pi0",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Get()
//                   .N_Dh_Bu2D0H(),
//               DaughtersVars<Daughters::pipi>::Get()
//                   .R_Dk_vs_Dpi_Bu2D0H()))) {}
//
// template <>
// SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pipi>::SpecialisedVars()
//     : N_Dh_(new RooFormulaVar(
//           "N_Dk_gamma_pipi", "Total number of Bu2Dst0K-like events, for "
//                             "daughters=pipi, neutral=gamma",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::gamma, Bachelor::pi,
//                               Daughters::pipi>::Get()
//                   .N_Dh(),
//               NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::Get()
//                   .R_Dk_vs_Dpi()))),
//       N_Dh_Bu2D0Hst_(new RooFormulaVar(
//           "N_Dk_Bu2D0Hst_gamma_pipi", "Total number of Bu2D0Kst-like events, for "
//                           "daughters=pipi, neutral=gamma",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Get()
//                   .N_Dh_Bu2D0Hst(),
//               DaughtersVars<Daughters::pipi>::Get()
//                   .R_Dk_vs_Dpi_Bu2D0Hst()))),
//       N_Dh_Bd2DstH_(new RooFormulaVar(
//           "N_Dk_Bd2DstH_gamma_pipi", "Total number of Bd2DstK-like events, for "
//                           "daughters=pipi, neutral=gamma",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Get()
//                   .N_Dh_Bd2DstH(),
//               Configuration::Get()
//                   .R_Dk_vs_Dpi_Bd2DstH()))),
//       N_Dh_Bu2D0H_(new RooFormulaVar(
//           "N_Dk_Bu2D0H_gamma_pipi", "Total number of Bu2D0K-like events, for "
//                           "daughters=pipi, neutral=gamma",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Get()
//                   .N_Dh_Bu2D0H(),
//               DaughtersVars<Daughters::pipi>::Get()
//                   .R_Dk_vs_Dpi_Bu2D0H()))) {}
//
//
// template <>
// SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pik>::SpecialisedVars()
//     : N_Dh_(new RooRealVar(
//           "N_Dpi_pi0_pik", "Total number of Bu2Dst0pi-like events,"
//                            " for daughters=pik, neutral=pi0",
//           (NeutralVars<Neutral::pi0>::Get().signalExpected() +
//            NeutralVars<Neutral::pi0>::Get().nonTmSignalExpected() +
//            NeutralVars<Neutral::pi0>::Get().crossFeedExpected()) *
//               DaughtersVars<Daughters::pik>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::pi0>::Get().maxYield() *
//                  DaughtersVars<Daughters::pik>::Get().daughtersSF())),
//       N_Dh_Bu2D0Hst_(new RooRealVar(
//           "N_Dpi_Bu2D0Hst_pi0_pik", "Total number of Bu2D0rho-like events,"
//                            " for daughters=pik, neutral=pi0",
//           NeutralVars<Neutral::pi0>::Get().bu2D0HstExpected() *
//               DaughtersVars<Daughters::pik>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::pi0>::Get().maxYield() *
//                  DaughtersVars<Daughters::pik>::Get().daughtersSF())),
//       N_Dh_Bd2DstH_(new RooRealVar(
//           "N_Dpi_Bd2DstH_pi0_pik", "Total number of Bd2Dstpi-like events,"
//                            " for daughters=pik, neutral=pi0",
//           NeutralVars<Neutral::pi0>::Get().bd2DstHExpected() *
//               DaughtersVars<Daughters::pik>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::pi0>::Get().maxYield() *
//                  DaughtersVars<Daughters::pik>::Get().daughtersSF())),
//       N_Dh_Bu2D0H_(new RooRealVar(
//           "N_Dpi_Bu2D0H_pi0_pik", "Total number of Bu2D0pi-like events,"
//                            " for daughters=pik, neutral=pi0",
//           NeutralVars<Neutral::pi0>::Get().bu2D0HExpected() *
//               DaughtersVars<Daughters::pik>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::pi0>::Get().maxYield() *
//                  DaughtersVars<Daughters::pik>::Get().daughtersSF())) {}
//
// template <>
// SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pik>::SpecialisedVars()
//     : N_Dh_(new RooRealVar(
//           "N_Dpi_gamma_pik", "Total number of Bu2Dst0pi-like events,"
//                              " for daughters=pik, neutral=gamma",
//           (NeutralVars<Neutral::gamma>::Get().signalExpected() +
//            NeutralVars<Neutral::gamma>::Get().nonTmSignalExpected() +
//            NeutralVars<Neutral::gamma>::Get().crossFeedExpected()) *
//               DaughtersVars<Daughters::pik>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::gamma>::Get().maxYield() *
//                  DaughtersVars<Daughters::pik>::Get().daughtersSF())),
//       N_Dh_Bu2D0Hst_(new RooRealVar(
//           "N_Dpi_Bu2D0Hst_gamma_pik", "Total number of Bu2D0rho-like events,"
//                            " for daughters=pik, neutral=gamma",
//           NeutralVars<Neutral::gamma>::Get().bu2D0HstExpected() *
//               DaughtersVars<Daughters::pik>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::gamma>::Get().maxYield() *
//                  DaughtersVars<Daughters::pik>::Get().daughtersSF())),
//       N_Dh_Bd2DstH_(new RooRealVar(
//           "N_Dpi_Bd2DstH_gamma_pik", "Total number of Bd2Dstpi-like events,"
//                            " for daughters=pik, neutral=gamma",
//           NeutralVars<Neutral::gamma>::Get().bd2DstHExpected() *
//               DaughtersVars<Daughters::pik>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::gamma>::Get().maxYield() *
//                  DaughtersVars<Daughters::pik>::Get().daughtersSF())),
//       N_Dh_Bu2D0H_(new RooRealVar(
//           "N_Dpi_Bu2D0H_gamma_pik", "Total number of Bu2D0pi-like events,"
//                            " for daughters=pik, neutral=gamma",
//           NeutralVars<Neutral::gamma>::Get().bu2D0HExpected() *
//               DaughtersVars<Daughters::pik>::Get().daughtersSF(),
//           0, NeutralVars<Neutral::gamma>::Get().maxYield() *
//                  DaughtersVars<Daughters::pik>::Get().daughtersSF())) {}
//
// template <>
// SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pik>::SpecialisedVars()
//     : N_Dh_(new RooFormulaVar(
//           "N_Dk_pi0_pik", "Total number of Bu2Dst0K-like events, for "
//                           "daughters=pik, neutral=pi0",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pik>::Get()
//                   .N_Dh(),
//               NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::Get()
//                   .R_Dk_vs_Dpi()))),
//       N_Dh_Bu2D0Hst_(new RooFormulaVar(
//           "N_Dk_Bu2D0Hst_pi0_pik", "Total number of Bu2D0Kst-like events, for "
//                           "daughters=pik, neutral=pi0",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pik>::Get()
//                   .N_Dh_Bu2D0Hst(),
//               DaughtersVars<Daughters::pik>::Get()
//                   .R_Dk_vs_Dpi_Bu2D0Hst()))),
//       N_Dh_Bd2DstH_(new RooFormulaVar(
//           "N_Dk_Bd2DstH_pi0_pik", "Total number of Bd2DstK-like events, for "
//                           "daughters=pik, neutral=pi0",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pik>::Get()
//                   .N_Dh_Bd2DstH(),
//               Configuration::Get()
//                   .R_Dk_vs_Dpi_Bd2DstH()))),
//       N_Dh_Bu2D0H_(new RooFormulaVar(
//           "N_Dk_Bu2D0H_pi0_pik", "Total number of Bu2D0K-like events, for "
//                           "daughters=pik, neutral=pi0",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pik>::Get()
//                   .N_Dh_Bu2D0H(),
//               DaughtersVars<Daughters::pik>::Get()
//                   .R_Dk_vs_Dpi_Bu2D0H()))) {}
//
// template <>
// SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pik>::SpecialisedVars()
//     : N_Dh_(new RooFormulaVar(
//           "N_Dk_gamma_pik", "Total number of Bu2Dst0K-like events, for "
//                             "daughters=pik, neutral=gamma",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::gamma, Bachelor::pi,
//                               Daughters::pik>::Get()
//                   .N_Dh(),
//               NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::Get()
//                   .R_Dk_vs_Dpi()))),
//       N_Dh_Bu2D0Hst_(new RooFormulaVar(
//           "N_Dk_Bu2D0Hst_gamma_pik", "Total number of Bu2D0Kst-like events, for "
//                           "daughters=pik, neutral=gamma",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pik>::Get()
//                   .N_Dh_Bu2D0Hst(),
//               DaughtersVars<Daughters::pik>::Get()
//                   .R_Dk_vs_Dpi_Bu2D0Hst()))),
//       N_Dh_Bd2DstH_(new RooFormulaVar(
//           "N_Dk_Bd2DstH_gamma_pik", "Total number of Bd2DstK-like events, for "
//                           "daughters=pik, neutral=gamma",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pik>::Get()
//                   .N_Dh_Bd2DstH(),
//               Configuration::Get()
//                   .R_Dk_vs_Dpi_Bd2DstH()))),
//       N_Dh_Bu2D0H_(new RooFormulaVar(
//           "N_Dk_Bu2D0H_gamma_pik", "Total number of Bu2D0K-like events, for "
//                           "daughters=pik, neutral=gamma",
//           "@0*@1",
//           RooArgList(
//               SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pik>::Get()
//                   .N_Dh_Bu2D0H(),
//               DaughtersVars<Daughters::pik>::Get()
//                   .R_Dk_vs_Dpi_Bu2D0H()))) {}
//
//
