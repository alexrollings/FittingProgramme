#include "NeutralVars.h"
#include "GlobalVars.h"

// Neutral specializations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::gamma>::NeutralVars(int uniqueId)
    : meanDeltaSignal_(
          ("meanDeltaSignal" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean of Signal m[Delta]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          130, 125, 135),
      a0MeanBuSignal_(
          ("a0MeanBuSignal" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 of mean of Signal m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          5101.86875, 4879, 5579),
          // 2740.0, 1740.0, 3740.0),
      a1MeanBuSignal_(
          ("a1MeanBuSignal" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a1 of mean of Signal m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.1375, 0, 10),
          // 29.5, 0, 40),
      a2MeanBuSignal_(
          ("a2MeanBuSignal" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a2 of mean of Signal m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -0.0062, -1, 1),
          // -0.075, -1, 1),
      meanBuSignal_(
          ("meanBuSignal" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean of Signal m[Bu]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0MeanBuSignal_)) {}

template <>
NeutralVars<Neutral::pi0>::NeutralVars(int uniqueId)
    : meanDeltaSignal_(
          ("meanDeltaSignal" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Mean of Signal m[Delta]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          135, 130, 140),
      a0MeanBuSignal_(
          ("a0MeanBuSignal" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 of mean of Signal m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          5101.86875, 4879, 5579),
          // 2740.0, 1740.0, 3740.0),
      a1MeanBuSignal_(
          ("a1MeanBuSignal" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a1 of mean of Signal m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          2.1375, 0, 10),
          // 29.5, 0, 40),
      a2MeanBuSignal_(
          ("a2MeanBuSignal" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a2 of mean of Signal m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -0.0062, -1, 1),
          // -0.075, -1, 1),
      meanBuSignal_(
          ("meanBuSignal" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Mean of Signal m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0MeanBuSignal_)) {}
