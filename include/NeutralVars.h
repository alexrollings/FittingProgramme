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

template <Neutral neutral> class NeutralVars {

  // One template specialization == One entirely separate class in practice
  // These will give two different instances:
  //   NeutralVars<Neutral::gamma>::Get()
  //   NeutralVars<Neutral::pi0>::Get()
  // All happens automatically :-)
  
public:  
  static NeutralVars<neutral> &Get() {
    static NeutralVars<neutral> singleton;
    return singleton;
  }

  // If RooShit wasn't so shit we would pass a const reference
  RooRealVar &meanSignal() { return meanSignal_; }

private:
  // When we DO need to specialize certain cases, we can still do that (see
  // below)...
  NeutralVars();
  ~NeutralVars() {}

  // Indicate if only used by one neutral

  RooRealVar meanSignal_;
};

// Now we just need to define the constructors separately so the values are
// different

// ...by telling it exactly which specializations we are providing:
template <> NeutralVars<Neutral::gamma>::NeutralVars();
template <> NeutralVars<Neutral::pi0>::NeutralVars();
// Then we can safely put these in the .cpp-file somewhere to be linked later.
