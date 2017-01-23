#include "DaughtersVars.h"
#include "Configuration.h"

// Daughters specializations
// Make general and have a switch statement for daughtersSF()
template <>
DaughtersVars<Daughters::kpi>::DaughtersVars()
    : R_cp_Bu2D0H_(), R_cp_Bu2D0Hst_(),
      R_Dk_vs_Dpi_Bu2D0H_(
          new RooRealVar("R_Dk_vs_Dpi_Bu2D0H_kpi",
                         "Ratio of yields of Bu2D0H decay channel for K "
                         "w.r.t. pi bachelor, for daughters=kpi",
                         0.078, 0.05, 0.15)),
      R_Dk_vs_Dpi_Bu2D0Hst_(
          new RooRealVar("R_Dk_vs_Dpi_Bu2D0Hst_kpi",
                         "Ratio of yields of Bu2D0Hst decay channel for K "
                         "w.r.t. pi bachelor, for daughters=kpi",
                         0.078, 0.05, 0.3)),
      daughtersSF_(1.0) {}

template <>
DaughtersVars<Daughters::kk>::DaughtersVars()
    : R_cp_Bu2D0H_("R_cp_Bu2D0H_kk",
                   "R_dk_vs_dpi_Bu2D0H[kk]/R_dk_vs_dpi_Bu2D0H[kpi]", 1, 0.5,
                   1.5),
      R_cp_Bu2D0Hst_("R_cp_Bu2D0Hst_kk",
                     "R_dk_vs_dpi_Bu2D0Hst[kk]/R_dk_vs_dpi_Bu2D0Hst[kpi]", 1.30),
      R_Dk_vs_Dpi_Bu2D0H_(new RooFormulaVar(
          "R_Dk_vs_Dpi_Bu2D0H_kk",
          "Ratio of yields of Bu2D0H decay channel for K "
          "w.r.t. pi bachelor, for daughters=kk",
          "@0*@1",
          RooArgList(DaughtersVars<Daughters::kpi>::Get().R_Dk_vs_Dpi_Bu2D0H(),
                     R_cp_Bu2D0H_))),
      R_Dk_vs_Dpi_Bu2D0Hst_(new RooFormulaVar(
          "R_Dk_vs_Dpi_Bu2D0Hst_kk",
          "Ratio of yields of Bu2D0Hst decay channel for K "
          "w.r.t. pi bachelor, for daughters=kk",
          "@0*@1",
          RooArgList(
              DaughtersVars<Daughters::kpi>::Get().R_Dk_vs_Dpi_Bu2D0Hst(),
              R_cp_Bu2D0Hst_))),
      daughtersSF_(0.102) {}

template <>
DaughtersVars<Daughters::pipi>::DaughtersVars()
    : R_cp_Bu2D0H_("R_cp_Bu2D0H_pipi",
                   "R_dk_vs_dpi_Bu2D0H[pipi]/R_dk_vs_dpi_Bu2D0H[kpi]", 1, 0.5,
                   1.5),
      R_cp_Bu2D0Hst_("R_cp_Bu2D0Hst_pipi",
                     "R_dk_vs_dpi_Bu2D0Hst[pipi]/R_dk_vs_dpi_Bu2D0Hst[kpi]", 0.96),
      R_Dk_vs_Dpi_Bu2D0H_(new RooFormulaVar(
          "R_Dk_vs_Dpi_Bu2D0H_pipi",
          "Ratio of yields of Bu2D0H decay channel for K "
          "w.r.t. pi bachelor, for daughters=pipi",
          "@0*@1",
          RooArgList(DaughtersVars<Daughters::kpi>::Get().R_Dk_vs_Dpi_Bu2D0H(),
                     R_cp_Bu2D0H_))),
      R_Dk_vs_Dpi_Bu2D0Hst_(new RooFormulaVar(
          "R_Dk_vs_Dpi_Bu2D0Hst_pipi",
          "Ratio of yields of Bu2D0Hst decay channel for K "
          "w.r.t. pi bachelor, for daughters=pipi",
          "@0*@1",
          RooArgList(
              DaughtersVars<Daughters::kpi>::Get().R_Dk_vs_Dpi_Bu2D0Hst(),
              R_cp_Bu2D0Hst_))),
      daughtersSF_(0.0361) {}

template <>
DaughtersVars<Daughters::pik>::DaughtersVars()
    : R_cp_Bu2D0H_(), R_cp_Bu2D0Hst_(),
      R_Dk_vs_Dpi_Bu2D0H_(
          new RooRealVar("R_Dk_vs_Dpi_Bu2D0H_pik",
                         "Ratio of yields of Bu2D0H decay channel for K "
                         "w.r.t. pi bachelor, for daughters=pik",
                         0.078, 0.05, 0.15)),
      R_Dk_vs_Dpi_Bu2D0Hst_(
          new RooRealVar("R_Dk_vs_Dpi_Bu2D0Hst_pik",
                         "Ratio of yields of Bu2D0Hst decay channel for K "
                         "w.r.t. pi bachelor, for daughters=pik",
                         0.078, 0.05, 0.3)),
      daughtersSF_(0.00356) {}
