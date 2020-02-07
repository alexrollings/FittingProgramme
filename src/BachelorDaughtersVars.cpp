#include "BachelorDaughtersVars.h"
#include "Configuration.h"
#include "GlobalVars.h"

template <>
BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::BachelorDaughtersVars(
    int uniqueId)
    : kBR_(("kBR_" + ComposeName(uniqueId, Bachelor::pi, Daughters::kpi))
               .c_str(),
           "", 1.0) {}

template <>
BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::BachelorDaughtersVars(
    int uniqueId)
    : kBR_(
          ("kBR_" + ComposeName(uniqueId, Bachelor::pi, Daughters::kk)).c_str(),
          "", 0.00408 / 0.0395) {}

template <>
BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::BachelorDaughtersVars(
    int uniqueId)
    : kBR_(("kBR_" + ComposeName(uniqueId, Bachelor::pi, Daughters::pipi))
               .c_str(),
           "", 0.001455 / 0.0395) {}

template <>
BachelorDaughtersVars<Bachelor::pi, Daughters::pik>::BachelorDaughtersVars(
    int uniqueId)
    : kBR_(("kBR_" + ComposeName(uniqueId, Bachelor::pi, Daughters::pik))
               .c_str(),
           "", 0.0001364 / 0.0395) {}

template <>
BachelorDaughtersVars<Bachelor::k, Daughters::kpi>::BachelorDaughtersVars(
    int uniqueId)
    : kBR_(
          ("kBR_" + ComposeName(uniqueId, Bachelor::k, Daughters::kpi)).c_str(),
          "", 1.0 * (0.000397 / 0.00490)) {}

template <>
BachelorDaughtersVars<Bachelor::k, Daughters::kk>::BachelorDaughtersVars(
    int uniqueId)
    : kBR_(("kBR_" + ComposeName(uniqueId, Bachelor::k, Daughters::kk)).c_str(),
           "", (0.00408 / 0.0395) * (0.000397 / 0.00490)) {}

template <>
BachelorDaughtersVars<Bachelor::k, Daughters::pipi>::BachelorDaughtersVars(
    int uniqueId)
    : kBR_(("kBR_" + ComposeName(uniqueId, Bachelor::k, Daughters::pipi))
               .c_str(),
           "", (0.001455 / 0.0395) * (0.000397 / 0.00490)) {}

// Including R ADS
template <>
BachelorDaughtersVars<Bachelor::k, Daughters::pik>::BachelorDaughtersVars(
    int uniqueId)
    : kBR_(
          ("kBR_" + ComposeName(uniqueId, Bachelor::k, Daughters::pik)).c_str(),
          "", 0.0015) {}
