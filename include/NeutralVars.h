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

  RooRealVar &meanBu2Dst0H_D0pi0() { return meanBu2Dst0H_D0pi0_; }
  RooRealVar &aBu2Dst0H_D0pi0() { return aBu2Dst0H_D0pi0_; }
  RooRealVar &nBu2Dst0H_D0pi0() { return nBu2Dst0H_D0pi0_; }
  RooRealVar &meanBu2Dst0H_D0gamma() { return meanBu2Dst0H_D0gamma_; }
  RooRealVar &aBu2Dst0H_D0gamma() { return aBu2Dst0H_D0gamma_; }
  RooRealVar &nBu2Dst0H_D0gamma() { return nBu2Dst0H_D0gamma_; }
  RooRealVar &meanNonTmSignal() { return meanNonTmSignal_; }
  RooRealVar &aNonTmSignal_1() { return aNonTmSignal_1_; }
  RooRealVar &nNonTmSignal_1() { return nNonTmSignal_1_; }
  RooRealVar &fracNonTmSignal_1() { return fracNonTmSignal_1_; }
  RooRealVar &aNonTmSignal_2() { return aNonTmSignal_2_; }
  RooRealVar &nNonTmSignal_2() { return nNonTmSignal_2_; }
  RooRealVar &meanBu2D0H() { return meanBu2D0H_; }
  RooRealVar &meanBu2D0Hst() { return meanBu2D0Hst_; }
  RooRealVar &aBu2D0Hst() { return aBu2D0Hst_; }
  RooRealVar &nBu2D0Hst() { return nBu2D0Hst_; }
  RooRealVar &meanBd2DstH() { return meanBd2DstH_; }
  RooRealVar &aBd2DstH() { return aBd2DstH_; }
  RooRealVar &nBd2DstH() { return nBd2DstH_; }
  RooRealVar &nonTmRatio() { return nonTmRatio_; }

private:
  // When we DO need to specialize certain cases, we can still do that (see
  // below)...
  NeutralVars();
  ~NeutralVars() {}

  // Indicate if only used by one neutral

  RooRealVar meanBu2Dst0H_D0pi0_;
  RooRealVar aBu2Dst0H_D0pi0_;
  RooRealVar nBu2Dst0H_D0pi0_;
  RooRealVar meanBu2Dst0H_D0gamma_;
  RooRealVar aBu2Dst0H_D0gamma_; // pi0
  RooRealVar nBu2Dst0H_D0gamma_; // pi0
  RooRealVar meanNonTmSignal_;
  RooRealVar aNonTmSignal_1_;    // gamma
  RooRealVar nNonTmSignal_1_;    // gamma
  RooRealVar fracNonTmSignal_1_; // gamma
  RooRealVar aNonTmSignal_2_;    // gamma
  RooRealVar nNonTmSignal_2_;    // gamma
  RooRealVar meanBu2D0H_;
  RooRealVar meanBu2D0Hst_;
  RooRealVar aBu2D0Hst_;
  RooRealVar nBu2D0Hst_;
  RooRealVar meanBd2DstH_;
  RooRealVar aBd2DstH_;
  RooRealVar nBd2DstH_;
  RooRealVar nonTmRatio_;
};

// Now we just need to define the constructors separately so the values are
// different

// ...by telling it exactly which specializations we are providing:
template <> NeutralVars<Neutral::gamma>::NeutralVars();
template <> NeutralVars<Neutral::pi0>::NeutralVars();
// Then we can safely put these in the .cpp-file somewhere to be linked later.
