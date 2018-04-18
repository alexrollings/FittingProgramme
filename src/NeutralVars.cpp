#include "NeutralVars.h"
#include "Configuration.h"

// Neutral specializations

template <>
NeutralVars<Neutral::gamma>::NeutralVars()
   : meanSignal_("meanSignal_gamma", "Mean of Signal PDF gamma", 5281, 5276, 5286),

template <>
NeutralVars<Neutral::pi0>::NeutralVars()
   : meanSignal_("meanSignal_pi0", "Mean of Signal PDF pi0", 5279, 5274, 5284),
