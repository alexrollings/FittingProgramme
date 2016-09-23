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
  RooConstVar &aSignal_1() { return aSignal_1_; }
  RooConstVar &aSignal_2() { return aSignal_2_; }
  RooConstVar &meanCrossFeed() { return meanCrossFeed_; }
  RooConstVar &aCrossFeed_1() { return aCrossFeed_1_; }
  RooConstVar &aCrossFeed_2() { return aCrossFeed_2_; }
  RooConstVar &meanNonTmSignal() { return meanNonTmSignal_; }
  RooConstVar &aNonTmSignal_1() { return aNonTmSignal_1_; }
  RooConstVar &aNonTmSignal_2() { return aNonTmSignal_2_; }
  RooAbsReal &meanBu2D0H_1() { return *meanBu2D0H_1_; }
  RooRealVar &meanBu2D0H_2() { return meanBu2D0H_2_; }
  RooConstVar &aBu2D0H_1() { return aBu2D0H_1_; }
  RooConstVar &aBu2D0H_2() { return aBu2D0H_2_; }
  RooConstVar &nBu2D0H_1() { return nBu2D0H_1_; }
  RooConstVar &nBu2D0H_2() { return nBu2D0H_2_; }
  RooRealVar &fracBu2D0H_1() { return fracBu2D0H_1_; }
  RooConstVar &meanBu2D0Hst() { return meanBu2D0Hst_; }
  RooConstVar &aBu2D0Hst() { return aBu2D0Hst_; }
  RooConstVar &nBu2D0Hst() { return nBu2D0Hst_; }
  RooConstVar &meanBd2DstH() { return meanBd2DstH_; }
  RooConstVar &aBd2DstH_1() { return aBd2DstH_1_; }
  RooConstVar &aBd2DstH_2() { return aBd2DstH_2_; }
  RooConstVar &relativeBu2D0HYield() { return relativeBu2D0HYield_; }
  RooConstVar &relativeBu2D0HstYield() { return relativeBu2D0HstYield_; }
  RooConstVar &relativeBd2DstHYield() { return relativeBd2DstHYield_; }
  RooRealVar &R_cp() { return R_cp_; }
  // Don't pass double as a reference: don't allow user to change numbers.
  double maxYield() { return maxYield_; }
  double bu2D0HExpected() { return bu2D0HExpected_; }
  double bd2DstHExpected() { return bd2DstHExpected_; }
  double bu2Dst0Hst_D0pi0Expected() { return bu2Dst0Hst_D0pi0Expected_; }
  double bu2Dst0Hst_D0gammaExpected() { return bu2Dst0Hst_D0gammaExpected_; }
  double bu2D0HstExpected() { return bu2D0HstExpected_; }
  double nonTmSignalExpected() { return nonTmSignalExpected_; }
  double signalExpected() { return signalExpected_; }
  double crossFeedExpected() { return crossFeedExpected_; }

private:
  // When we DO need to specialize certain cases, we can still do that (see
  // below)...
  NeutralVars();
  ~NeutralVars() {}

  // Indicate if only used by one neutral

  RooRealVar meanSignal_;
  RooConstVar aSignal_1_;
  RooConstVar aSignal_2_;
  RooConstVar meanCrossFeed_;
  RooConstVar aCrossFeed_1_; // pi0
  RooConstVar aCrossFeed_2_; // pi0
  RooConstVar meanNonTmSignal_;
  RooConstVar aNonTmSignal_1_;    // gamma
  RooConstVar aNonTmSignal_2_;    // gamma
  std::unique_ptr<RooAbsReal> meanBu2D0H_1_;
  RooRealVar meanBu2D0H_2_;
  RooConstVar aBu2D0H_1_;
  RooConstVar aBu2D0H_2_;
  RooConstVar nBu2D0H_1_;
  RooConstVar nBu2D0H_2_;
  RooRealVar fracBu2D0H_1_;
  RooConstVar meanBu2D0Hst_;
  RooConstVar aBu2D0Hst_;
  RooConstVar nBu2D0Hst_;
  RooConstVar meanBd2DstH_;
  RooConstVar aBd2DstH_1_;
  RooConstVar aBd2DstH_2_;
  RooConstVar relativeBu2D0HYield_;
  RooConstVar relativeBu2D0HstYield_;
  RooConstVar relativeBd2DstHYield_;
  RooRealVar R_cp_;
  double maxYield_;
  double bu2D0HExpected_;
  double bd2DstHExpected_;
  double bu2Dst0Hst_D0pi0Expected_;
  double bu2Dst0Hst_D0gammaExpected_;
  double bu2D0HstExpected_;
  double nonTmSignalExpected_;
  double signalExpected_;
  double crossFeedExpected_;
};

// Now we just need to define the constructors separately so the values are
// different

// ...by telling it exactly which specializations we are providing:
template <> NeutralVars<Neutral::gamma>::NeutralVars();
template <> NeutralVars<Neutral::pi0>::NeutralVars();
// Then we can safely put these in the .cpp-file somewhere to be linked later.
