#include "DaughtersVars.h"
#include "Configuration.h"
#include "GlobalVars.h"

// Daughters specializations
// Make general and have a switch statement for daughtersSF()
template <>
DaughtersVars<Daughters::kpi>::DaughtersVars(int uniqueId)
    : R_CP_overRec_(),
      ratioDst0KDst0pi_overRec_(new RooRealVar(
          ("ratioDst0KDst0pi_overRec_" + ComposeName(uniqueId, Daughters::kpi))
              .c_str(),
          "", 0.07768, -1, 1)),  // CHECK
      ratioDst0KDst0pi_misRec_(
          ("ratioDst0KDst0pi_misRec_" + ComposeName(uniqueId, Daughters::kpi))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n misRec mode " +
           ComposeName(uniqueId, Daughters::kpi))
              .c_str(),
          0.05, -1, 1),
      daughtersSF_(1.0) {}

template <>
DaughtersVars<Daughters::kk>::DaughtersVars(int uniqueId)
    : R_CP_overRec_(
          ("R_CP_overRec_" + ComposeName(uniqueId, Daughters::kk)).c_str(), "",
          1, -2, 2),
      ratioDst0KDst0pi_overRec_(new RooFormulaVar(
          ("ratioDst0KDst0pi_overRec_" + ComposeName(uniqueId, Daughters::kk))
              .c_str(),
          "", "@0*@1",
          RooArgList(DaughtersVars<Daughters::kpi>::Get(uniqueId)
                         .ratioDst0KDst0pi_overRec(),
                     R_CP_overRec_))),
      ratioDst0KDst0pi_misRec_(
          ("ratioDst0KDst0pi_misRec_" + ComposeName(uniqueId, Daughters::kk))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n misRec mode " +
           ComposeName(uniqueId, Daughters::kk))
              .c_str(),
          0.05, -1, 1),
      daughtersSF_(0.102) {}

template <>
DaughtersVars<Daughters::pipi>::DaughtersVars(int uniqueId)
    : R_CP_overRec_(
          ("R_CP_overRec_" + ComposeName(uniqueId, Daughters::pipi)).c_str(), "",
          1, -2, 2),
      ratioDst0KDst0pi_overRec_(new RooFormulaVar(
          ("ratioDst0KDst0pi_overRec_" + ComposeName(uniqueId, Daughters::pipi))
              .c_str(),
          "", "@0*@1",
          RooArgList(DaughtersVars<Daughters::kpi>::Get(uniqueId)
                         .ratioDst0KDst0pi_overRec(),
                     R_CP_overRec_))),
      ratioDst0KDst0pi_misRec_(
          ("ratioDst0KDst0pi_misRec_" + ComposeName(uniqueId, Daughters::pipi))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n misRec mode " +
           ComposeName(uniqueId, Daughters::pipi))
              .c_str(),
          0.05, -1, 1),
      daughtersSF_(0.0361) {}

template <>
DaughtersVars<Daughters::pik>::DaughtersVars(int uniqueId)
    : R_CP_overRec_(),
      ratioDst0KDst0pi_overRec_(new RooRealVar(
          ("ratioDst0KDst0pi_overRec_" + ComposeName(uniqueId, Daughters::pik))
              .c_str(),
          "", 0.07768, -1, 1)),  // CHECK
      ratioDst0KDst0pi_misRec_(
          ("ratioDst0KDst0pi_misRec_" + ComposeName(uniqueId, Daughters::pik))
              .c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi n misRec mode " +
           ComposeName(uniqueId, Daughters::pik))
              .c_str(),
          0.05, -1, 1),
      daughtersSF_(0.015) {}
    //   daughtersSF_(0.00356) {}
