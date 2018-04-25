#pragma once
#include "Configuration.h"
#include "DaughtersVars.h"
#include "NeutralDaughtersVars.h"
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

namespace { // Anonymous namespace

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl;

template <Neutral neutral, Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, daughters> {
  NeutralBachelorDaughtersVarsImpl();
  std::unique_ptr<RooRealVar> N_Dst0h_;
};

template <Neutral neutral, Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, daughters> {
  NeutralBachelorDaughtersVarsImpl();
  std::unique_ptr<RooFormulaVar> N_Dst0h_;
};
}

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
class NeutralBachelorDaughtersVars {

  // One template specialization == One entirely separate class in practice
  // These will give two different instances:
  //   DaughtersVars<Daughters::gamma>::Get()
  //   DaughtersVars<Daughters::pi0>::Get()
  // All happens automatically :-)

public:
  static NeutralBachelorDaughtersVars<neutral, bachelor, daughters> &Get() {
    static NeutralBachelorDaughtersVars<neutral, bachelor, daughters> singleton;
    return singleton;
  }

  // If RooShit wasn't so shit we would pass a const reference
  RooAbsReal &N_Dst0h() { return *impl_.N_Dst0h_; }

private:
  // When we DO need to specialize certain cases, we can still do that (see
  // below)...
  NeutralBachelorDaughtersVars() {}
  ~NeutralBachelorDaughtersVars() {}

  // Indicate if only used by one daughters

  // N_Dpi is the total Bu2Dst0pi_D0neut events = signal + SCF + CF + missID
  NeutralBachelorDaughtersVarsImpl<neutral, bachelor, daughters> impl_;
};

// Now we just need to define the constructors separately so the values are
// different

template <Neutral neutral, Daughters daughters>
NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, daughters>::NeutralBachelorDaughtersVarsImpl()
    : N_Dst0h_(new RooRealVar(("N_Dst0pi_" + ComposeName(neutral, daughters)).c_str(),
                           ("Total number of Bu2Dst0pi-like events " +
                            ComposeName(neutral, daughters))
                               .c_str(), 1000, 0, 5000)) {}

template <Neutral neutral, Daughters daughters>
NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, daughters>::NeutralBachelorDaughtersVarsImpl()
    : N_Dst0h_(new RooFormulaVar(
          ("N_Dst0k_" + ComposeName(neutral, daughters)).c_str(),
          ("Total number of Bu2Dst0K-like events, for " +
           ComposeName(neutral, daughters))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorDaughtersVars<neutral, Bachelor::pi, daughters>::Get().N_Dst0h(),
              Configuration::Get().R_Dst0K_vs_Dst0pi()))) {}
