#include "DaughtersVars.h"
#include "Configuration.h"
#include "GlobalVars.h"

// Daughters specializations
// Make general and have a switch statement for daughtersSF()
template <>
DaughtersVars<Daughters::kpi>::DaughtersVars(int uniqueId)
    : daughtersSF_(1.0) {}

template <>
DaughtersVars<Daughters::kk>::DaughtersVars(int uniqueId)
    : daughtersSF_(0.12) {}

template <>
DaughtersVars<Daughters::pipi>::DaughtersVars(int uniqueId)
    : daughtersSF_(0.04) {}

// May have to edit this as bkgs could CP voilate, then rate SF k mode is
// ~0.001, more than π x 0.08
template <>
DaughtersVars<Daughters::pik>::DaughtersVars(int uniqueId)
    : daughtersSF_(0.0036) {}
