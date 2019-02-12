#pragma once
#include "Configuration.h"
#include "RooFormulaVar.h"
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

template <Neutral neutral, Daughters daughters>
class NeutralDaughtersVars {

 public:
  // Inline Constructor
  NeutralDaughtersVars(int uniqueId_);
  // Inline Destructor - can both be implemented externally too:
  ~NeutralDaughtersVars() {}
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

  using This_t = NeutralDaughtersVars<neutral, daughters>;

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
  RooRealVar &R_CP_Bu2Dst0h_Dst02D0gamma() {
    return R_CP_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &R_CP_Bu2Dst0h_Dst02D0pi0() {
    return R_CP_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &R_CP_Bu2Dst0hst_Dst02D0gamma() {
    return R_CP_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &R_CP_Bu2Dst0hst_Dst02D0pi0() {
    return R_CP_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooAbsReal &ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma() {
    return *ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_;
  }
  RooAbsReal &ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0() {
    return *ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_;
  }
  RooAbsReal &ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma() {
    return *ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooAbsReal &ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0() {
    return *ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_;
  }

 private:
  // Indicate if only used by one daughters

  // N_Dpi is the total Bu2Dst0pi_D0neut events = signal + SCF + CF + missID
  // RooRealVar N_Dpi_;
  // RooFormulaVar N_Dk_;
  int uniqueId_;
  RooRealVar R_CP_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar R_CP_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar R_CP_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar R_CP_Bu2Dst0hst_Dst02D0pi0_;
  std::unique_ptr<RooAbsReal> ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooAbsReal> ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooAbsReal> ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_;
  std::unique_ptr<RooAbsReal> ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_;
};

// Now we just need to define the constructors separately so the values are
// different

// ...by telling it exactly which specializations we are providing:
template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::NeutralDaughtersVars(int uniqueId);
template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::NeutralDaughtersVars(int uniqueId);
template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::NeutralDaughtersVars(int uniqueId);
template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::NeutralDaughtersVars(int uniqueId);
template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::NeutralDaughtersVars(int uniqueId);
template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::NeutralDaughtersVars(int uniqueId);
template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::NeutralDaughtersVars(int uniqueId);
template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::NeutralDaughtersVars(int uniqueId);
// Then we can safely put these in the .cpp-file somewhere to be linked later.
