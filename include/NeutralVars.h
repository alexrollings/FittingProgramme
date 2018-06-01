#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "RooDstD0BG.h"
#include "RooExponential.h"
#include "RooPolyVar.h"
#include "RooProdPdf.h"

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

template <Neutral neutral>
class NeutralVars {
  // One template specialization == One entirely separate class in practice
  // These will give two different instances:
  //   NeutralVars<Neutral::gamma>::Get()
  //   NeutralVars<Neutral::pi0>::Get()
  // All happens automatically :-)

 public:
  // Inline Constructor
  NeutralVars(int uniqueId_);
  // Inline Destructor - can both be implemented externally too:
  ~NeutralVars() {}
  // Class Human
  // {
  // public:
  //  ~Human(); //Destructor declaration
  // };
  //:: is the scoping operator. Destructor definition/implementation
  // Human::~Human();
  // { // code }
  // Invoked when a class is deleted or goes out of scope: good place to reset
  // variables/release dynamically allocated memory

  using This_t = NeutralVars<neutral>;

  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId_) {
    static std::map<int, std::shared_ptr<This_t>> singletons;
    // An iterator to a map is a std::pair<key, value>, so we need to call
    // i->second to get the value
    auto it = singletons.find(uniqueId_);  // Check if uniqueId_ already exists
    if (it == singletons.end()) {
      // If it doesn't, create it as a new unique_ptr by calling emplace, which
      // will forward the pointer to the constructor of std::unique_ptr
      it = singletons.emplace(uniqueId_, std::make_shared<This_t>(uniqueId_))
               .first;
    }
    return *it->second;
  }

  // If RooShit wasn't so shit we would pass a const reference
  int uniqueId() { return uniqueId_; }
  RooRealVar &meanDelta_Bu2Dst0h_Dst02D0pi0() {
    return meanDelta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a0MeanBu_Bu2Dst0h_Dst02D0pi0() {
    return a0MeanBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a1MeanBu_Bu2Dst0h_Dst02D0pi0() {
    return a1MeanBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a2MeanBu_Bu2Dst0h_Dst02D0pi0() {
    return a2MeanBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooPolyVar &meanBu_Bu2Dst0h_Dst02D0pi0() {
    return meanBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &meanDelta_Bu2Dst0h_Dst02D0gamma() {
    return meanDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a0MeanBu_Bu2Dst0h_Dst02D0gamma() {
    return a0MeanBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a1MeanBu_Bu2Dst0h_Dst02D0gamma() {
    return a1MeanBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a2MeanBu_Bu2Dst0h_Dst02D0gamma() {
    return a2MeanBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooPolyVar &meanBu_Bu2Dst0h_Dst02D0gamma() {
    return meanBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &thresholdDelta_Bu2D0h() { return thresholdDelta_Bu2D0h_; }
  RooRealVar &aDelta_Bu2D0h() { return aDelta_Bu2D0h_; }
  RooRealVar &bDelta_Bu2D0h() { return bDelta_Bu2D0h_; }
  RooRealVar &cDelta_Bu2D0h() { return cDelta_Bu2D0h_; }
  RooDstD0BG &pdfDelta_Bu2D0h() { return pdfDelta_Bu2D0h_; }
  RooRealVar &a0MeanBu_Bu2D0h() { return a0MeanBu_Bu2D0h_; }
  RooPolyVar &meanBu_Bu2D0h() { return meanBu_Bu2D0h_; }
  RooRealVar &meanDelta_partialRec() {
    return meanDelta_partialRec_;
  }
  RooRealVar &a0MeanBu_partialRec() { return a0MeanBu_partialRec_; }
  RooRealVar &a1MeanBu_partialRec() { return a1MeanBu_partialRec_; }
  RooRealVar &a2MeanBu_partialRec() { return a2MeanBu_partialRec_; }
  RooPolyVar &meanBu_partialRec() { return meanBu_partialRec_; }
  RooRealVar &thresholdDelta_Comb() { return thresholdDelta_Comb_; }
  RooRealVar &aDelta_Comb() { return aDelta_Comb_; }
  RooRealVar &bDelta_Comb() { return bDelta_Comb_; }
  RooRealVar &cDelta_Comb() { return cDelta_Comb_; }
  RooDstD0BG &pdfDelta_Comb() { return pdfDelta_Comb_; }
  RooRealVar &a0LambdaBu_Comb() { return a0LambdaBu_Comb_; }
  RooPolyVar &lambdaBu_Comb() { return lambdaBu_Comb_; }
  RooExponential &pdfBu_Comb() { return pdfBu_Comb_; }
  RooProdPdf &pdf_Comb() { return pdf_Comb_; }
  RooRealVar &neutralCrossFeedRate_Bu2Dst0h() {
    return neutralCrossFeedRate_Bu2Dst0h_;
  }

 private:
  // Indicate if only used by one neutral

  int uniqueId_;
  RooRealVar meanDelta_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a0MeanBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a1MeanBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a2MeanBu_Bu2Dst0h_Dst02D0pi0_;
  RooPolyVar meanBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar meanDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a0MeanBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a1MeanBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a2MeanBu_Bu2Dst0h_Dst02D0gamma_;
  RooPolyVar meanBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar thresholdDelta_Bu2D0h_;
  RooRealVar aDelta_Bu2D0h_;
  RooRealVar bDelta_Bu2D0h_;
  RooRealVar cDelta_Bu2D0h_;
  RooDstD0BG pdfDelta_Bu2D0h_;
  RooRealVar a0MeanBu_Bu2D0h_;
  RooPolyVar meanBu_Bu2D0h_;
  RooRealVar meanDelta_partialRec_;
  RooRealVar a0MeanBu_partialRec_;
  RooRealVar a1MeanBu_partialRec_;
  RooRealVar a2MeanBu_partialRec_;
  RooPolyVar meanBu_partialRec_;
  RooRealVar thresholdDelta_Comb_;
  RooRealVar aDelta_Comb_;
  RooRealVar bDelta_Comb_;
  RooRealVar cDelta_Comb_;
  RooDstD0BG pdfDelta_Comb_;
  RooRealVar a0LambdaBu_Comb_;
  RooPolyVar lambdaBu_Comb_;
  RooExponential pdfBu_Comb_;
  RooProdPdf pdf_Comb_;
  RooRealVar neutralCrossFeedRate_Bu2Dst0h_;
};

// When we DO need to specialize certain cases, we can still do that (see
// below)...
// Now we just need to define the constructors separately so the values are
// different

// ...by telling it exactly which specializations we are providing:
template <>
NeutralVars<Neutral::pi0>::NeutralVars(int uniqueId);
template <>
NeutralVars<Neutral::gamma>::NeutralVars(int uniqueId);
// Then we can safely put these in the .cpp-file somewhere to be linked later.
