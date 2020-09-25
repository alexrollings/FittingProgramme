#pragma once
#include "RooAbsReal.h"
#include "RooUnblindUniform.h"

#include "Configuration.h"
#include "GlobalVars.h"
#include "Params.h"
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

template <Bachelor bachelor, Charge charge>
class BachelorChargeVars {
 public:
  // Inline Constructor
  BachelorChargeVars(int uniqueId_);
  // Inline Destructor - can both be implemented externally too:
  ~BachelorChargeVars() {}
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

  using This_t = BachelorChargeVars<bachelor, charge>;

  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId);

  // If RooShit wasn't so shit we would pass a const reference
  int uniqueId() { return uniqueId_; }
  RooRealVar &R_piK_Bu2Dst0h_D0gamma_Blind() {
    return *R_piK_Bu2Dst0h_D0gamma_Blind_;
  }
  RooRealVar &R_piK_Bu2Dst0h_D0pi0_Blind() {
    return *R_piK_Bu2Dst0h_D0pi0_Blind_;
  }
  RooAbsReal &R_piK_Bu2Dst0h_D0gamma() { return *R_piK_Bu2Dst0h_D0gamma_; }
  RooAbsReal &R_piK_Bu2Dst0h_D0pi0() { return *R_piK_Bu2Dst0h_D0pi0_; }
  RooAbsReal &R_piK_Bu2Dst0h_WN() { return *R_piK_Bu2Dst0h_WN_; }

 private:
  // When we DO need to specialize certain cases, we can still do that (see
  // below)...

  // Indicate if only used by one daughters

  int uniqueId_;
  // BR for decay relative to FAV mode (π, Kπ)
  // Can add for different bkgs if necessary
  std::shared_ptr<RooRealVar> R_piK_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooRealVar> R_piK_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> R_piK_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> R_piK_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> R_piK_Bu2Dst0h_WN_;
};

// Now we just need to define the constructors separately so the values are
// different

// ...by telling it exactly which specializations we are providing:
template <Bachelor bachelor, Charge charge>
BachelorChargeVars<bachelor, charge>::BachelorChargeVars(int uniqueId)
    : uniqueId_(uniqueId),
      R_piK_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_piK_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_piK_Bu2Dst0h_D0gamma_(nullptr),
      R_piK_Bu2Dst0h_D0pi0_(nullptr),
      R_piK_Bu2Dst0h_WN_(nullptr) {
  double R_piK_init = GlobalVars::Get(uniqueId_).kBF_D02pik().getVal() /
                      GlobalVars::Get(uniqueId_).kBF_D02kpi().getVal();
  if (Configuration::Get().blindFit() == true) {
    R_piK_Bu2Dst0h_D0gamma_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("R_piK_Bu2Dst0h_D0gamma_Blind", uniqueId_,
                                     bachelor, charge, R_piK_init, -1, 1));
    R_piK_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("R_piK_Bu2Dst0h_D0pi0_Blind", uniqueId_,
                                     bachelor, charge, R_piK_init, -1, 1));
    R_piK_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("R_piK_Bu2Dst0h_D0gamma_" + ComposeName(uniqueId_, bachelor, charge))
            .c_str(),
        R_piK_init, *R_piK_Bu2Dst0h_D0gamma_Blind_));
    R_piK_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("R_piK_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId_, bachelor, charge))
            .c_str(),
        R_piK_init, *R_piK_Bu2Dst0h_D0pi0_Blind_));
  } else {
    R_piK_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("R_piK_Bu2Dst0h_D0gamma", uniqueId_,
                                     bachelor, charge, R_piK_init, -1, 1));
    R_piK_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("R_piK_Bu2Dst0h_D0pi0", uniqueId_,
                                     bachelor, charge, R_piK_init, -1, 1));
  }
  R_piK_Bu2Dst0h_WN_ = std::shared_ptr<RooRealVar>(
      Params::Get().CreateFloating("R_piK_Bu2Dst0h_WN", uniqueId_,
                                   bachelor, charge, R_piK_init, -1, 1));
}
