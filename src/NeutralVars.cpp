#include "NeutralVars.h"
#include "Configuration.h"

// Neutral specializations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::gamma>::NeutralVars(int uniqueId)
    : meanDeltaSignal_(
          ("meanDeltaSignal" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean of Signal m[Delta]" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          130, 125, 135),
      a0MeanBuSignal_(
          ("a0MeanBuSignal" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 of mean of Signal m[Bu] PDF " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5281, 5276, 5286),
      meanBuSignal_(
          ("meanBuSignal" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean of Signal m[Bu]" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          Configuration::Get(uniqueId).deltaMass(), RooArgList(a0MeanBuSignal_)) {}

template <>
NeutralVars<Neutral::pi0>::NeutralVars(int uniqueId)
    : meanDeltaSignal_(
          ("meanDeltaSignal" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Mean of Signal m[Delta]" + ComposeName(uniqueId, Neutral::pi0)).c_str(), 135,
          130, 140),
      a0MeanBuSignal_(
          ("a0MeanBuSignal_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 of mean of Signal m[Bu] PDF " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          5279, 5274, 5284),
      meanBuSignal_(
          ("meanBuSignal" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Mean of Signal m[Bu]" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          Configuration::Get(uniqueId).deltaMass(), RooArgList(a0MeanBuSignal_)) {}
