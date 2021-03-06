#pragma once
#include "RooAbsReal.h"
#include "RooUnblindUniform.h"

#include "BachelorDaughtersVars.h"
#include "Configuration.h"
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

template <Neutral neutral, Bachelor bachelor, Charge charge>
class NeutralBachelorChargeVars {
 public:
  // Inline Constructor
  NeutralBachelorChargeVars(int uniqueId_);
  // Inline Destructor - can both be implemented externally too:
  ~NeutralBachelorChargeVars() {}
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

  using This_t = NeutralBachelorChargeVars<neutral, bachelor, charge>;

  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId);

  // If RooShit wasn't so shit we would pass a const reference
  int uniqueId() { return uniqueId_; }
  RooRealVar &R_piK_Bu2Dst0h_D0gamma_Blind() {
    return *R_piK_Bu2Dst0h_D0gamma_Blind_;
  }
  RooAbsReal &R_piK_Bu2Dst0h_D0gamma() { return *R_piK_Bu2Dst0h_D0gamma_; }
  RooRealVar &R_piK_Bu2Dst0h_D0pi0_Blind() {
    return *R_piK_Bu2Dst0h_D0pi0_Blind_;
  }
  RooAbsReal &R_piK_Bu2Dst0h_D0pi0() { return *R_piK_Bu2Dst0h_D0pi0_; }

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
};

// Now we just need to define the constructors separately so the values are
// different

// ...by telling it exactly which specializations we are providing:
template <Neutral neutral, Bachelor bachelor, Charge charge>
NeutralBachelorChargeVars<neutral, bachelor, charge>::NeutralBachelorChargeVars(
    int uniqueId)
    : uniqueId_(uniqueId),
      R_piK_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_piK_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_piK_Bu2Dst0h_D0gamma_(nullptr),
      R_piK_Bu2Dst0h_D0pi0_(nullptr) {
  if (Configuration::Get().blindFit() == true) {
    R_piK_Bu2Dst0h_D0pi0_Blind_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "R_piK_Bu2Dst0h_D0pi0_Blind", uniqueId_, neutral, bachelor, charge,
            BachelorDaughtersVars<bachelor, Daughters::pik>::Get(uniqueId_)
                .kBR()
                .getVal(),
            -1, 1));
    R_piK_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("R_piK_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId_, neutral, bachelor, charge))
            .c_str(),
        BachelorDaughtersVars<bachelor, Daughters::pik>::Get(uniqueId_)
            .kBR()
            .getVal(),
        *R_piK_Bu2Dst0h_D0pi0_Blind_));
    if (neutral == Neutral::gamma) {
      R_piK_Bu2Dst0h_D0gamma_Blind_ =
          std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
              "R_piK_Bu2Dst0h_D0gamma_Blind", uniqueId_, neutral, bachelor,
              charge,
              BachelorDaughtersVars<bachelor, Daughters::pik>::Get(uniqueId_)
                  .kBR()
                  .getVal(),
              -1, 1));
      R_piK_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
          ("R_piK_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, neutral, bachelor, charge))
              .c_str(),
          BachelorDaughtersVars<bachelor, Daughters::pik>::Get(uniqueId_)
              .kBR()
              .getVal(),
          *R_piK_Bu2Dst0h_D0gamma_Blind_));
    }
  } else {
    R_piK_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "R_piK_Bu2Dst0h_D0pi0", uniqueId_, neutral, bachelor, charge,
            BachelorDaughtersVars<bachelor, Daughters::pik>::Get(uniqueId_)
                .kBR()
                .getVal(),
            -1, 1));
    if (neutral == Neutral::gamma) {
      R_piK_Bu2Dst0h_D0gamma_ =
          std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
              "R_piK_Bu2Dst0h_D0gamma", uniqueId_, neutral, bachelor, charge,
              BachelorDaughtersVars<bachelor, Daughters::pik>::Get(uniqueId_)
                  .kBR()
                  .getVal(),
              -1, 1));
    }
  }
}
