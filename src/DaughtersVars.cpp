#include "DaughtersVars.h"
#include "Configuration.h"

// Daughters specializations
// Make general and have a switch statement for daughtersSF()
template <>
DaughtersVars<Daughters::kpi>::DaughtersVars()
    : R_Dk_vs_Dpi_Bu2D0H_("R_Dk_vs_Dpi_Bu2D0H_kpi",
                          "Ratio of yields of Bu2D0H decay channel for K "
                          "w.r.t. pi bachelor, for daughters=kpi",
                          0.075, 0.02, 0.1),
      R_Dk_vs_Dpi_Bu2D0Hst_("R_Dk_vs_Dpi_Bu2D0Hst_kpi",
                            "Ratio of yields of Bu2D0Hst decay channel for K "
                            "w.r.t. pi bachelor, for daughters=kpi",
                            0.075, 0.02, 0.1),
      daughtersSF_(1.0) {}

template <>
DaughtersVars<Daughters::kk>::DaughtersVars()
    : R_Dk_vs_Dpi_Bu2D0H_("R_Dk_vs_Dpi_Bu2D0H_kk",
                          "Ratio of yields of Bu2D0H decay channel for K "
                          "w.r.t. pi bachelor, for daughters=kk",
                          0.075, 0.02, 0.1),
      R_Dk_vs_Dpi_Bu2D0Hst_("R_Dk_vs_Dpi_Bu2D0Hst_kk",
                            "Ratio of yields of Bu2D0Hst decay channel for K "
                            "w.r.t. pi bachelor, for daughters=kk",
                            0.075, 0.02, 0.1),
      daughtersSF_(0.102) {}

template <>
DaughtersVars<Daughters::pipi>::DaughtersVars()
    : R_Dk_vs_Dpi_Bu2D0H_("R_Dk_vs_Dpi_Bu2D0H_pipi",
                          "Ratio of yields of Bu2D0H decay channel for K "
                          "w.r.t. pi bachelor, for daughters=pipi",
                          0.075, 0.02, 0.1),
      R_Dk_vs_Dpi_Bu2D0Hst_("R_Dk_vs_Dpi_Bu2D0Hst_pipi",
                            "Ratio of yields of Bu2D0Hst decay channel for K "
                            "w.r.t. pi bachelor, for daughters=pipi",
                            0.075, 0.02, 0.1),
      daughtersSF_(0.0361) {}

template <>
DaughtersVars<Daughters::pik>::DaughtersVars()
    : R_Dk_vs_Dpi_Bu2D0H_("R_Dk_vs_Dpi_Bu2D0H_pik",
                          "Ratio of yields of Bu2D0H decay channel for K "
                          "w.r.t. pi bachelor, for daughters=pik",
                          0.075, 0.02, 0.1),
      R_Dk_vs_Dpi_Bu2D0Hst_("R_Dk_vs_Dpi_Bu2D0Hst_pik",
                            "Ratio of yields of Bu2D0Hst decay channel for K "
                            "w.r.t. pi bachelor, for daughters=pik",
                            0.075, 0.02, 0.1),
      daughtersSF_(0.00356) {}
