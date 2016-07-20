#include "Skeleton.h"
#include "RooCBShape.h"

// Neutral specializations

template <>
NeutralVars<Neutral::gamma>::NeutralVars()
    : meanCrossFeed_("meanCrossFeedGamma", "Gamma cross feed mean", 0) {
}

template <>
NeutralVars<Neutral::pi0>::NeutralVars()
    : meanCrossFeed_("meanCrossFeedPi0", "Pi0 cross feed mean", 0) {}

// Bachelor specializations

template <>
BachelorVars<Neutral::gamma, Bachelor::pi>::BachelorVars()
  : sigmaCrossFeed_("sigmaCrossFeedGammaPi", "Gamma, Pi cross feed sigma", 2),
    bu2Dst0Hst_D0gamma_(new RooCBShape()) {}

template <>
void BachelorVars<Neutral::gamma, Bachelor::pi>::AddToPdf(
    RooArgList &yields, RooArgList &functions) {
  // Not yet implemented
}
