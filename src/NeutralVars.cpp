#include "NeutralVars.h"
#include "Configuration.h"

// Neutral specializations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::gamma>::NeutralVars()
    : meanDeltaSignal_(
          ("meanDeltaSignal" + ComposeName(Neutral::gamma)).c_str(),
          ("Mean of Signal m[Delta]" + ComposeName(Neutral::gamma)).c_str(),
          130, 125, 135),
      a0MeanBuSignal_(
          ("a0MeanBuSignal" + ComposeName(Neutral::gamma)).c_str(),
          ("a0 of mean of Signal m[Bu] PDF " + ComposeName(Neutral::gamma))
              .c_str(),
          5281, 5276, 5286),
      meanBuSignal_(
          ("meanBuSignal" + ComposeName(Neutral::gamma)).c_str(),
          ("Mean of Signal m[Bu]" + ComposeName(Neutral::gamma)).c_str(),
          Configuration::Get().deltaMass(), RooArgList(a0MeanBuSignal_)) {}

template <>
NeutralVars<Neutral::pi0>::NeutralVars()
    : meanDeltaSignal_(
          ("meanDeltaSignal" + ComposeName(Neutral::pi0)).c_str(),
          ("Mean of Signal m[Delta]" + ComposeName(Neutral::pi0)).c_str(), 135,
          130, 140),
      a0MeanBuSignal_(
          ("a0MeanBuSignal_" + ComposeName(Neutral::pi0)).c_str(),
          ("a0 of mean of Signal m[Bu] PDF " + ComposeName(Neutral::pi0))
              .c_str(),
          5279, 5274, 5284),
      meanBuSignal_(
          ("meanBuSignal" + ComposeName(Neutral::pi0)).c_str(),
          ("Mean of Signal m[Bu]" + ComposeName(Neutral::pi0)).c_str(),
          Configuration::Get().deltaMass(), RooArgList(a0MeanBuSignal_)) {}
