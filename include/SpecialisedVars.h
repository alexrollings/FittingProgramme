#pragma once
#include "Configuration.h"
#include "RooAbsReal.h"
#include "RooFormulaVar.h"
#include "NeutralDaughtersSharedVars.h"
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

template <Neutral neutral, Bachelor bachelor, Daughters daughters> class SpecialisedVars {

  // One template specialization == One entirely separate class in practice
  // These will give two different instances:
  //   DaughtersVars<Daughters::gamma>::Get()
  //   DaughtersVars<Daughters::pi0>::Get()
  // All happens automatically :-)
  
public:  
  static SpecialisedVars<neutral, bachelor, daughters> &Get() {
    static SpecialisedVars<neutral, bachelor, daughters> singleton;
    return singleton;
  }

  // If RooShit wasn't so shit we would pass a const reference
  RooAbsReal &N_Dh() { return *N_Dh_; }
  RooAbsReal &N_Dh_Bu2D0H() { return *N_Dh_Bu2D0H_; }
  RooAbsReal &N_Dh_Bu2D0Hst() { return *N_Dh_Bu2D0Hst_; }
  RooAbsReal &N_Dh_Bd2DstH() { return *N_Dh_Bd2DstH_; }

private:
  // When we DO need to specialize certain cases, we can still do that (see
  // below)...
  SpecialisedVars();
  ~SpecialisedVars() {}

  // Indicate if only used by one daughters

  // N_Dpi is the total Bu2Dst0pi_D0neut events = signal + SCF + CF + missID
  std::unique_ptr<RooAbsReal> N_Dh_;
  std::unique_ptr<RooAbsReal> N_Dh_Bu2D0H_;
  std::unique_ptr<RooAbsReal> N_Dh_Bu2D0Hst_;
  std::unique_ptr<RooAbsReal> N_Dh_Bd2DstH_;
};

// Now we just need to define the constructors separately so the values are
// different

// ...by telling it exactly which specializations we are providing:
template <> SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kpi>::SpecialisedVars();
template <> SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kk>::SpecialisedVars();
template <> SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pipi>::SpecialisedVars();
template <> SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pik>::SpecialisedVars();
template <> SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kpi>::SpecialisedVars();
template <> SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kk>::SpecialisedVars();
template <> SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pipi>::SpecialisedVars();
template <> SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pik>::SpecialisedVars();
template <> SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kpi>::SpecialisedVars();
template <> SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kk>::SpecialisedVars();
template <> SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pipi>::SpecialisedVars();
template <> SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pik>::SpecialisedVars();
template <> SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kpi>::SpecialisedVars();
template <> SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kk>::SpecialisedVars();
template <> SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pipi>::SpecialisedVars();
template <> SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pik>::SpecialisedVars();
// Then we can safely put these in the .cpp-file somewhere to be linked later.
