#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorDaughtersVars.h"
#include "NeutralVars.h"
#include "RooAbsReal.h"
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

namespace {  // Anonymous namespace

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl;

template <Neutral neutral, Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, daughters> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::unique_ptr<RooRealVar> N_Dst0h_;
  std::unique_ptr<RooRealVar> asym_;
};

template <Neutral neutral, Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, daughters> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::unique_ptr<RooFormulaVar> N_Dst0h_;
  std::unique_ptr<RooRealVar> asym_;
};
}  // namespace

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
class NeutralBachelorDaughtersVars {
  // One template specialization == One entirely separate class in practice
  // These will give two different instances:
  //   DaughtersVars<Daughters::gamma>::Get()
  //   DaughtersVars<Daughters::pi0>::Get()
  // All happens automatically :-)

 public:
  // Need to construct the Impl field here (don't HAVE to do this if imple_
  // doesn't take an argument, as it happens implicitly.
  NeutralBachelorDaughtersVars(int uniqueId_) : impl_(uniqueId_) {}
  ~NeutralBachelorDaughtersVars() {}

  using This_t = NeutralBachelorDaughtersVars<neutral, bachelor, daughters>;

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
  RooAbsReal &N_Dst0h() { return *impl_.N_Dst0h_; }
  RooRealVar &asym() { return *impl_.asym_; }

 private:
  // When we DO need to specialize certain cases, we can still do that (see
  // below)...

  // Indicate if only used by one daughters
  int uniqueId_;

  // N_Dpi is the total Bu2Dst0pi_D0neut events = signal + SCF + CF + missID
  NeutralBachelorDaughtersVarsImpl<neutral, bachelor, daughters> impl_;
};

// Now we just need to define the constructors separately so the values are
// different

template <Neutral neutral, Daughters daughters>
NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, daughters>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : N_Dst0h_(new RooRealVar(
          ("N_Dst0pi_" + ComposeName(uniqueId, neutral, daughters)).c_str(),
          ("Total number of Bu2Dst0pi-like events " +
           ComposeName(uniqueId, neutral, daughters))
              .c_str(),
          100000, 0, 500000)),
      asym_(new RooRealVar(
          ("asym_" + ComposeName(uniqueId, neutral, Bachelor::pi, daughters))
              .c_str(),
          ("asymmetry variable " +
           ComposeName(uniqueId, neutral, Bachelor::pi, daughters))
              .c_str(),
          0.001, -1.0, 1.0)) {}

template <Neutral neutral, Daughters daughters>
NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, daughters>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : N_Dst0h_(new RooFormulaVar(
          ("N_Dst0k_" + ComposeName(uniqueId, neutral, daughters)).c_str(),
          ("Total number of Bu2Dst0K-like events, for " +
           ComposeName(uniqueId, neutral, daughters))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<neutral, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_Dst0h(),
                     GlobalVars::Get(uniqueId).ratioDst0KDst0pi()))),
      asym_(new RooRealVar(
          ("asym_" + ComposeName(uniqueId, neutral, Bachelor::k, daughters))
              .c_str(),
          ("asymmetry variable " +
           ComposeName(uniqueId, neutral, Bachelor::k, daughters))
              .c_str(),
          0.01, -1.0, 1.0)) {}
