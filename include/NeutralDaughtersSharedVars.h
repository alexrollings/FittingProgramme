#pragma once
#include "Configuration.h"

// Templated classes/functions mean that the compiler will automatically create
// a copy
// of the entire class for you for every permutation of template arguments it is
// called
// with. This is handy because often a lot of the code is identical except for a
// few
// details.
// However, everything the compiler needs to do so must be provided in the .h
// file,
// because otherwise it won't actually know how to cater to external callers to
// your
// class/function (unless you explicitly specialize, see below).

template <Neutral neutral, Daughters daughters> class NeutralDaughtersSharedVars {

  // One template specialization == One entirely separate class in practice
  // These will give two different instances:
  //   DaughtersVars<Daughters::gamma>::Get()
  //   DaughtersVars<Daughters::pi0>::Get()
  // All happens automatically :-)
  
public:  
  static NeutralDaughtersSharedVars<neutral, daughters> &Get() {
    static NeutralDaughtersSharedVars<neutral, daughters> singleton;
    return singleton;
  }

  // If RooShit wasn't so shit we would pass a const reference
  RooRealVar &N_Dpi() { return N_Dpi_; }
  RooRealVar &R_Dk_vs_Dpi() { return R_Dk_vs_Dpi_; }

private:
  // When we DO need to specialize certain cases, we can still do that (see
  // below)...
  NeutralDaughtersSharedVars();
  ~NeutralDaughtersSharedVars() {}

  // Indicate if only used by one daughters

  // N_Dpi is the total Bu2Dst0pi_D0neut events = signal + SCF + CF + missID
  RooRealVar N_Dpi_;
  RooRealVar R_Dk_vs_Dpi_;
};

// Now we just need to define the constructors separately so the values are
// different

// ...by telling it exactly which specializations we are providing:
template <> NeutralDaughtersSharedVars<Neutral::pi0, Daughters::kpi>::NeutralDaughtersSharedVars();
template <> NeutralDaughtersSharedVars<Neutral::pi0, Daughters::kk>::NeutralDaughtersSharedVars();
template <> NeutralDaughtersSharedVars<Neutral::pi0, Daughters::pipi>::NeutralDaughtersSharedVars();
template <> NeutralDaughtersSharedVars<Neutral::pi0, Daughters::pik>::NeutralDaughtersSharedVars();
template <> NeutralDaughtersSharedVars<Neutral::gamma, Daughters::kpi>::NeutralDaughtersSharedVars();
template <> NeutralDaughtersSharedVars<Neutral::gamma, Daughters::kk>::NeutralDaughtersSharedVars();
template <> NeutralDaughtersSharedVars<Neutral::gamma, Daughters::pipi>::NeutralDaughtersSharedVars();
template <> NeutralDaughtersSharedVars<Neutral::gamma, Daughters::pik>::NeutralDaughtersSharedVars();
// Then we can safely put these in the .cpp-file somewhere to be linked later.
