#include "NeutralVars.h"
#include "Configuration.h"

// Neutral specializations

template <>
NeutralVars<Neutral::gamma>::NeutralVars()
    : meanSignal_(("meanSignal_" + ComposeName(Neutral::gamma)).c_str(),
                  ("Mean of Signal PDF " + ComposeName(Neutral::gamma)).c_str(), 5281,
                  5276, 5286) {}

template <>
NeutralVars<Neutral::pi0>::NeutralVars()
    : meanSignal_(("meanSignal_" + ComposeName(Neutral::pi0)).c_str(),
                  ("Mean of Signal PDF " + ComposeName(Neutral::pi0)).c_str(), 5279,
                  5274, 5284) {}
