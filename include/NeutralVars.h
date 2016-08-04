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
  RooRealVar &aSignal_1() { return aSignal_1_; }
  RooRealVar &aSignal_2() { return aSignal_2_; }
  RooRealVar &meanCrossFeed() { return meanCrossFeed_; }
  RooRealVar &aCrossFeed_1() { return aCrossFeed_1_; }
  RooRealVar &aCrossFeed_2() { return aCrossFeed_2_; }
  RooRealVar &meanNonTmSignal() { return meanNonTmSignal_; }
  RooRealVar &aNonTmSignal_1() { return aNonTmSignal_1_; }
  RooRealVar &aNonTmSignal_2() { return aNonTmSignal_2_; }
  RooRealVar &meanBu2D0H_1() { return meanBu2D0H_1_; }
  RooRealVar &meanBu2D0H_2() { return meanBu2D0H_2_; }
  RooRealVar &aBu2D0H_1() { return aBu2D0H_1_; }
  RooRealVar &aBu2D0H_2() { return aBu2D0H_2_; }
  RooRealVar &nBu2D0H_1() { return nBu2D0H_1_; }
  RooRealVar &nBu2D0H_2() { return nBu2D0H_2_; }
  RooRealVar &fracBu2D0H_1() { return fracBu2D0H_1_; }
  RooRealVar &meanBu2D0Hst() { return meanBu2D0Hst_; }
  RooRealVar &aBu2D0Hst() { return aBu2D0Hst_; }
  RooRealVar &nBu2D0Hst() { return nBu2D0Hst_; }
  RooRealVar &meanBd2DstH() { return meanBd2DstH_; }
  RooRealVar &aBd2DstH_1() { return aBd2DstH_1_; }
  RooRealVar &aBd2DstH_2() { return aBd2DstH_2_; }
  RooRealVar &nonTmRatio() { return nonTmRatio_; }
  RooRealVar &crossFeedRate() { return crossFeedRate_; }
  // Don't pass double as a reference: don't allow user to change numbers.
  double maxYield() { return maxYield_; }
  double bu2D0HExpected() { return bu2D0HExpected_; }
  double bd2DstHExpected() { return bd2DstHExpected_; }
  double bu2Dst0Hst_D0pi0Expected() { return bu2Dst0Hst_D0pi0Expected_; }
  double bu2Dst0Hst_D0gammaExpected() { return bu2Dst0Hst_D0gammaExpected_; }
  double bu2D0HstExpected() { return bu2D0HstExpected_; }
  double signalExpected() { return signalExpected_; }
  double crossFeedExpected() { return crossFeedExpected_; }

private:
  // When we DO need to specialize certain cases, we can still do that (see
  // below)...
  NeutralVars();
  ~NeutralVars() {}

  // Indicate if only used by one neutral

  RooRealVar meanSignal_;
  RooRealVar aSignal_1_;
  RooRealVar aSignal_2_;
  RooRealVar meanCrossFeed_;
  RooRealVar aCrossFeed_1_; // pi0
  RooRealVar aCrossFeed_2_; // pi0
  RooRealVar meanNonTmSignal_;
  RooRealVar aNonTmSignal_1_;    // gamma
  RooRealVar aNonTmSignal_2_;    // gamma
  RooRealVar meanBu2D0H_1_;
  RooRealVar meanBu2D0H_2_;
  RooRealVar aBu2D0H_1_;
  RooRealVar aBu2D0H_2_;
  RooRealVar nBu2D0H_1_;
  RooRealVar nBu2D0H_2_;
  RooRealVar fracBu2D0H_1_;
  RooRealVar meanBu2D0Hst_;
  RooRealVar aBu2D0Hst_;
  RooRealVar nBu2D0Hst_;
  RooRealVar meanBd2DstH_;
  RooRealVar aBd2DstH_1_;
  RooRealVar aBd2DstH_2_;
  RooRealVar nonTmRatio_;
  RooRealVar crossFeedRate_;
  double maxYield_;
  double bu2D0HExpected_;
  double bd2DstHExpected_;
  double bu2Dst0Hst_D0pi0Expected_;
  double bu2Dst0Hst_D0gammaExpected_;
  double bu2D0HstExpected_;
  double signalExpected_;
  double crossFeedExpected_;
};

// Now we just need to define the constructors separately so the values are
// different

// ...by telling it exactly which specializations we are providing:
template <> NeutralVars<Neutral::gamma>::NeutralVars();
template <> NeutralVars<Neutral::pi0>::NeutralVars();
// Then we can safely put these in the .cpp-file somewhere to be linked later.
