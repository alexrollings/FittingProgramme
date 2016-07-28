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

template <Daughters daughters> class DaughtersVars {

  // One template specialization == One entirely separate class in practice
  // These will give two different instances:
  //   DaughtersVars<Daughters::gamma>::Get()
  //   DaughtersVars<Daughters::pi0>::Get()
  // All happens automatically :-)
  
public:  
  static DaughtersVars<daughters> &Get() {
    static DaughtersVars<daughters> singleton;
    return singleton;
  }

  // If RooShit wasn't so shit we would pass a const reference
  RooRealVar &bachelorRatio_Bu2D0H() { return bachelorRatio_Bu2D0H_; }
  RooRealVar &bachelorRatio_Bu2D0Hst() { return bachelorRatio_Bu2D0Hst_; }

private:
  // When we DO need to specialize certain cases, we can still do that (see
  // below)...
  DaughtersVars();
  ~DaughtersVars() {}

  // Indicate if only used by one daughters

  RooRealVar bachelorRatio_Bu2D0H_;
  RooRealVar bachelorRatio_Bu2D0Hst_;
};

// Now we just need to define the constructors separately so the values are
// different

// ...by telling it exactly which specializations we are providing:
template <> DaughtersVars<Daughters::kpi>::DaughtersVars();
template <> DaughtersVars<Daughters::kk>::DaughtersVars();
template <> DaughtersVars<Daughters::pipi>::DaughtersVars();
template <> DaughtersVars<Daughters::pik>::DaughtersVars();
// Then we can safely put these in the .cpp-file somewhere to be linked later.
